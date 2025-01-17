/*
 * Dibbler - a portable DHCPv6
 *
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>
 *          Marek Senderski <msend@o2.pl>
 * changes: Michal Kowalczuk <michal@kowalczuk.eu>
 *          Petr Pisar <petr.pisar(at)atlas(dot)cz>
 *
 * released under GNU GPL v2 only licence
 *
 */

#include <sstream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#ifndef WIN32
#include <sys/socket.h>
#include <net/if.h>
#endif
#include "Portable.h"
#include "SmartPtr.h"
#include "SrvIfaceMgr.h"
#include "Msg.h"
#include "SrvMsg.h"
#include "Logger.h"
#include "SrvMsgSolicit.h"
#include "SrvMsgRequest.h"
#include "SrvMsgConfirm.h"
#include "SrvMsgRenew.h"
#include "SrvMsgRebind.h"
#include "SrvMsgRelease.h"
#include "SrvMsgDecline.h"
#include "SrvMsgInfRequest.h"
#include "SrvMsgLeaseQuery.h"
#include "SrvOptInterfaceID.h"
#include "IPv6Addr.h"
#include "AddrClient.h"
#include "SrvIfaceIface.h"
#include "OptOptionRequest.h"
#include "OptGeneric.h"
#include "OptVendorData.h"
#include "OptIAAddress.h"
#include "OptIAPrefix.h"
#include "DNSUpdate.h"

using namespace std;

TSrvIfaceMgr * TSrvIfaceMgr::Instance = 0;


/*
 * constructor.
 */
TSrvIfaceMgr::TSrvIfaceMgr(const std::string& xmlFile)
    : TIfaceMgr(xmlFile, false) {

    struct iface * ptr;
    struct iface * ifaceList;

    this->XmlFile = xmlFile;

    // get interface list
    ifaceList = if_list_get(); // external (C coded) function
    ptr = ifaceList;

    if  (!ifaceList) {
        IsDone = true;
        Log(Crit) << "Unable to read info interfaces. Make sure "
                  << "you are using proper port (i.e. win32 on WindowsXP or 2003)"
                  << " and you have IPv6 support enabled." << LogEnd;
        return;
    }

    while (ptr!=NULL) {
        Log(Notice) << "Detected iface " << ptr->name << "/" << ptr->id
                 // << ", flags=" << ptr->flags
                    << ", MAC=" << this->printMac(ptr->mac, ptr->maclen) << "." << LogEnd;

        SPtr<TIfaceIface> iface(new TSrvIfaceIface(ptr->name,ptr->id,
                                                       ptr->flags,
                                                       ptr->mac,
                                                       ptr->maclen,
                                                       ptr->linkaddr,
                                                       ptr->linkaddrcount,
                                                       ptr->globaladdr,
                                                       ptr->globaladdrcount,
                                                       ptr->hardwareType));
        this->IfaceLst.append((Ptr*) iface);
        ptr = ptr->next;
    }
    if_list_release(ifaceList); // allocated in pure C, and so release it there

    dump();
}

TSrvIfaceMgr::~TSrvIfaceMgr() {
    Log(Debug) << "SrvIfaceMgr cleanup." << LogEnd;
}

void TSrvIfaceMgr::dump()
{
    std::ofstream xmlDump;
    xmlDump.open( this->XmlFile.c_str() );
    xmlDump << *this;
    xmlDump.close();
}


/**
 * sends data to client. Uses multicast address as source
 * @param iface interface index
 * @param msg - buffer containing message ready to send
 * @param size - size of message
 * @param addr  destination IPv6 address
 * @param port  destination UDP port
 * @return true if message was send successfully
 */
bool TSrvIfaceMgr::send(int iface, char *msg, int size,
                        SPtr<TIPv6Addr> addr, int port) {
    // find this interface
    SPtr<TIfaceIface> ptrIface;
    ptrIface = this->getIfaceByID(iface);
    if (!ptrIface) {
            Log(Error)  << "Send failed: No such interface id=" << iface << LogEnd;
            return false;
    }

    // find this socket
    SPtr<TIfaceSocket> sock;
    ptrIface->firstSocket();
    while (sock = ptrIface->getSocket()) {
        if (sock->multicast())
            continue; // don't send anything via multicast sockets
        break;
    }
    if (!sock) {
        Log(Error) << "Send failed: interface " << ptrIface->getName()
                   << "/" << iface << " has no open sockets." << LogEnd;
        return false;
    }

    // send it!
    return (sock->send(msg,size,addr,port));
}

// @brief reads messages from all interfaces
// it's wrapper around IfaceMgr::select(...) method
//
// @param timeout how long can we wait for packets (in seconds)
// @return message object (or NULL)
SPtr<TSrvMsg> TSrvIfaceMgr::select(unsigned long timeout) {

    // static buffer speeds things up
    const int maxBufsize = 4096;
    int bufsize=maxBufsize;
    static char buf[maxBufsize];

    SPtr<TIPv6Addr> peer (new TIPv6Addr());
    int sockid;

    // read data
    sockid = TIfaceMgr::select(timeout,buf,bufsize,peer);
    if (sockid>0) {

        if (bufsize<4) {
            if (bufsize == 1 && buf[0] == CONTROL_MSG) {
                Log(Debug) << "Control message received." << LogEnd;
                return 0;
            }
            Log(Warning) << "Received message is too short (" << bufsize
                         << ") bytes, at least 4 bytes are required." << LogEnd;
            return 0; // NULL
        }

        // check message type
        int msgtype = buf[0];

        SPtr<TSrvIfaceIface> ptrIface;

        // get interface
        ptrIface = (Ptr*)getIfaceBySocket(sockid);

        Log(Debug) << "Received " << bufsize << " bytes on interface " << ptrIface->getName() << "/"
                   << ptrIface->getID() << " (socket=" << sockid << ", addr=" << *peer << "."
                   << ")." << LogEnd;

        // create specific message object
        SPtr<TSrvMsg> ptr;
        switch (msgtype) {
        case SOLICIT_MSG:
        case REQUEST_MSG:
        case CONFIRM_MSG:
        case RENEW_MSG:
        case REBIND_MSG:
        case RELEASE_MSG:
        case DECLINE_MSG:
        case INFORMATION_REQUEST_MSG:
        case LEASEQUERY_MSG:
        {
            ptr = decodeMsg(ptrIface, peer, buf, bufsize);
            if (!ptr->validateReplayDetection() ||
                !ptr->validateAuthInfo(buf, bufsize)) {
                Log(Error) << "Auth: Authorization failed, message dropped." << LogEnd;
                return 0;
            }
            return ptr;
        }
        case RELAY_FORW_MSG:
        {
            ptr = decodeRelayForw(ptrIface, peer, buf, bufsize);
            if (!ptr)
                return 0;
            if (!ptr->validateReplayDetection() ||
                !ptr->validateAuthInfo(buf, bufsize)) {
                Log(Error) << "Auth: validation failed, message dropped." << LogEnd;
                return 0;
            }
        }
        return ptr;
        case ADVERTISE_MSG:
        case REPLY_MSG:
        case RECONFIGURE_MSG:
        case RELAY_REPL_MSG:
        case LEASEQUERY_REPLY_MSG:
            Log(Warning) << "Illegal message type " << msgtype << " received." << LogEnd;
            return 0; //NULL;
        default:
            Log(Warning) << "Message type " << msgtype << " not supported. Ignoring." << LogEnd;
            return 0; //NULL
        }
    } else {
        return 0; //NULL
    }
}

bool TSrvIfaceMgr::setupRelay(std::string name, int ifindex, int underIfindex,
                              SPtr<TSrvOptInterfaceID> interfaceID) {
    SPtr<TSrvIfaceIface> under = (Ptr*)this->getIfaceByID(underIfindex);
    if (!under) {
        Log(Crit) << "Unable to setup " << name << "/" << ifindex
                  << " relay: underlaying interface with id=" << underIfindex
                  << " is not present in the system or does not support IPv6." << LogEnd;
        return false;
    }

    if (!under->flagUp()) {
        Log(Crit) << "Unable to setup " << name << "/" << ifindex
                  << " relay: underlaying interface " << under->getName() << "/" << underIfindex
                  << " is down." << LogEnd;
        return false;
    }

    SPtr<TSrvIfaceIface> relay = new TSrvIfaceIface((const char*)name.c_str(), ifindex,
                                                        IFF_UP | IFF_RUNNING | IFF_MULTICAST,   // flags
                                                        0,   // MAC
                                                        0,   // MAC length
                                                        0,0, // link address
                                                        0,0, // global addresses
                                                        0);  // hardware type
    relay->setUnderlaying(under);
    this->IfaceLst.append((Ptr*)relay);

    if (!under->appendRelay(relay, interfaceID)) {
        Log(Crit) << "Unable to setup " << name << "/" << ifindex
                  << " relay: underlaying interface " << under->getName() << "/" << underIfindex
                  << " already has " << HOP_COUNT_LIMIT << " relays defined." << LogEnd;
        return false;
    }

    Log(Notice) << "Relay " << name << "/" << ifindex << " (underlaying " << under->getName()
                << "/" << under->getID() << ") has been configured." << LogEnd;

    return true;
}

SPtr<TSrvMsg> TSrvIfaceMgr::decodeRelayForw(SPtr<TSrvIfaceIface> ptrIface,
                                                SPtr<TIPv6Addr> peer,
                                                char * buf, int bufsize) {

    SPtr<TIPv6Addr> linkAddrTbl[HOP_COUNT_LIMIT];
    SPtr<TIPv6Addr> peerAddrTbl[HOP_COUNT_LIMIT];
    SPtr<TSrvOptInterfaceID> interfaceIDTbl[HOP_COUNT_LIMIT];
    int hopTbl[HOP_COUNT_LIMIT];
    List(TOptGeneric) echoListTbl[HOP_COUNT_LIMIT];
    SPtr<TSrvIfaceIface> relayIface;
    int relays=0; // number of nested RELAY_FORW messages
    SPtr<TOptVendorData> remoteID = 0;
    SPtr<TOptOptionRequest> echo = 0;
    SPtr<TOptGeneric> gen = 0;

    char * relay_buf = buf;
    int relay_bufsize = bufsize;

    for (int j=0;j<HOP_COUNT_LIMIT; j++)
        echoListTbl[j].clear();

    while (bufsize>0 && buf[0]==RELAY_FORW_MSG) {
        /* decode RELAY_FORW message */
        if (bufsize < 34) {
            Log(Warning) << "Truncated RELAY_FORW message received." << LogEnd;
            return 0;
        }

        SPtr<TSrvOptInterfaceID> ptrIfaceID;
        ptrIfaceID = 0;

        char type = buf[0];
        if (type!=RELAY_FORW_MSG)
            return 0;
        int hopCount = buf[1];
        int optRelayCnt = 0;
        int optIfaceIDCnt = 0;

        SPtr<TIPv6Addr> linkAddr = new TIPv6Addr(buf+2,false);
        SPtr<TIPv6Addr> peerAddr = new TIPv6Addr(buf+18, false);
        buf+=34;
        bufsize-=34;

        // options: only INTERFACE-ID and RELAY_MSG are allowed
        while (bufsize>=4) {
            unsigned short code = readUint16(buf);
            buf += sizeof(uint16_t); bufsize -= sizeof(uint16_t);
            int len = readUint16(buf);
            buf += sizeof(uint16_t); bufsize -= sizeof(uint16_t);

            if (len > bufsize) {
                Log(Warning) << "Truncated option " << code << ": " << bufsize
                             << " bytes remaining, but length is " << len
                             << "." << LogEnd;
                return 0;
            }

            switch (code) {
            case OPTION_INTERFACE_ID:
                if (bufsize<4) {
                    Log(Warning) << "Truncated INTERFACE_ID option (length: " << bufsize
                                 << ") in RELAY_FORW message. Message dropped." << LogEnd;
                    return 0;
                }
                ptrIfaceID = new TSrvOptInterfaceID(buf, len, 0);
                optIfaceIDCnt++;
                break;
            case OPTION_RELAY_MSG:
                relay_buf = buf;
                relay_bufsize = len;
                optRelayCnt++;
                break;
            case OPTION_REMOTE_ID:
                remoteID = new TOptVendorData(OPTION_REMOTE_ID, buf, len, 0);
                break;
            case OPTION_ERO:
                Log(Debug) << "Echo Request received in RELAY_FORW." << LogEnd;
                echo = new TOptOptionRequest(OPTION_ERO, buf, len, 0);
                break;
            default:
                gen = new TOptGeneric(code, buf, len, 0);
                echoListTbl[relays].append(gen);

            }
            buf     += len;
            bufsize -= len;
        }

        // remember options to be echoed
        echoListTbl[relays].first();
        while (gen = echoListTbl[relays].get()) {
            if (!echo) {
                Log(Warning) << "Invalid option (" << gen->getOptType() << ") in RELAY_FORW message was ignored." << LogEnd;
                echoListTbl[relays].del();
            } else {
                if (!echo->isOption(gen->getOptType())) {
                    Log(Warning) << "Invalid option (" << gen->getOptType() << ") in RELAY_FORW message was ignored." << LogEnd;
                    echoListTbl[relays].del();
                } else {
                    Log(Info) << "Option " << gen->getOptType() << " will be echoed back." << LogEnd;
                }
            }

        }


        // remember those links
        linkAddrTbl[relays] = linkAddr;
        peerAddrTbl[relays] = peerAddr;
        interfaceIDTbl[relays] = ptrIfaceID;
        hopTbl[relays] = hopCount;
        relays++;

        if (relays> HOP_COUNT_LIMIT) {
            Log(Error) << "Message is nested more than allowed " << HOP_COUNT_LIMIT << " times. Message dropped." << LogEnd;
            return 0;
        }

        if (optRelayCnt!=1) {
            Log(Error) << optRelayCnt << " RELAY_MSG options received, but exactly one was expected. Message dropped." << LogEnd;
            return 0;
        }
        if (optIfaceIDCnt>1) {
            Log(Error) << "More than one (" << optIfaceIDCnt
                       << ") interface-ID options received, but at most 1 was expected. Message dropped." << LogEnd;
            return 0;
        }

        Log(Info) << "RELAY_FORW was decapsulated: link=" << linkAddr->getPlain() << ", peer=" << peerAddr->getPlain();

        bool guessMode = SrvCfgMgr().guessMode();

        if (ptrIfaceID) {
            // find relay interface based on the interface-id option
            Log(Cont) << ", interfaceID len=" << ptrIfaceID->getSize() << LogEnd;
            relayIface = ptrIface->getRelayByInterfaceID(ptrIfaceID);
            if (!relayIface) {
                if (!guessMode) {
                    Log(Error) << "Unable to find relay interface with interfaceID=" << ptrIfaceID->getPlain() << " defined on the "
                               << ptrIface->getName() << "/" << ptrIface->getID() << " interface." << LogEnd;
                    return 0;
                }
            }
        }
        else {
            // find relay interface based on the link address
            Log(Cont) << ", interfaceID option missing." << LogEnd;
            Log(Warning) << "InterfaceID option missing, trying to find proper interface using link address: "
                         << linkAddr->getPlain() << " (expect troubles)."<< LogEnd;
            relayIface = ptrIface->getRelayByLinkAddr(linkAddr);
            if (!relayIface) {
                Log(Error) << "Unable to find relay interface using link address: " << linkAddr->getPlain() << LogEnd;
                if (!guessMode) {
                  return 0;
                }
            }
        }
        if (!relayIface && guessMode) {
            relayIface = ptrIface->getAnyRelay();
            if (!relayIface) {
                Log(Error) << "Guess-mode: Unable to find any relays on " << ptrIface->getFullName() << LogEnd;
                return 0;
            }
            interfaceIDTbl[relays] = -1;
            Log(Notice) << "Guess-mode: Relayed interface guessed as " << relayIface->getFullName() << LogEnd;
        }

        // now switch to relay interface
        ptrIface = relayIface;
        buf = relay_buf;
        bufsize = relay_bufsize;
    }

    SPtr<TSrvMsg> msg = this->decodeMsg(ptrIface, peer, relay_buf, relay_bufsize);
    for (int i=0; i<relays; i++) {
        msg->addRelayInfo(linkAddrTbl[i], peerAddrTbl[i], hopTbl[i], interfaceIDTbl[i], echoListTbl[i]);
    }
    if (remoteID) {
        Log(Debug) << "RemoteID received: vendor=" << remoteID->getVendor()
                   << ", length=" << remoteID->getVendorDataLen() << "." << LogEnd;
        msg->setRemoteID(remoteID);
        remoteID = 0;
        remoteID = msg->getRemoteID();
        PrintHex("RemoteID:", remoteID->getVendorData(), remoteID->getVendorDataLen());
    }

    return (Ptr*)msg;
 }

SPtr<TSrvMsg> TSrvIfaceMgr::decodeMsg(SPtr<TSrvIfaceIface> ptrIface,
                                             SPtr<TIPv6Addr> peer,
                                             char * buf, int bufsize) {
    int ifaceid = ptrIface->getID();
    if (bufsize<4)
        return 0;
    switch (buf[0]) {
    case SOLICIT_MSG:
              return new TSrvMsgSolicit(ifaceid, peer, buf, bufsize);
    case REQUEST_MSG:
              return new TSrvMsgRequest(ifaceid, peer, buf, bufsize);
    case CONFIRM_MSG:
              return new TSrvMsgConfirm(ifaceid,  peer, buf, bufsize);
    case RENEW_MSG:
              return new TSrvMsgRenew  (ifaceid,  peer, buf, bufsize);
    case REBIND_MSG:
              return new TSrvMsgRebind (ifaceid, peer, buf, bufsize);
    case RELEASE_MSG:
              return new TSrvMsgRelease(ifaceid, peer, buf, bufsize);
    case DECLINE_MSG:
              return new TSrvMsgDecline(ifaceid, peer, buf, bufsize);
    case INFORMATION_REQUEST_MSG:
              return new TSrvMsgInfRequest(ifaceid, peer, buf, bufsize);
    case LEASEQUERY_MSG:
              return new TSrvMsgLeaseQuery(ifaceid, peer, buf, bufsize);
    default:
        Log(Warning) << "Illegal message type " << (int)(buf[0]) << " received." << LogEnd;
        return 0; //NULL;;
    }
}

/**
 * Compares current flags of interfaces with old flags. If change is detected,
 * stored flags of the interface are updated
 */
void TSrvIfaceMgr::redetectIfaces() {
    struct iface  * ptr;
    struct iface  * ifaceList;
    SPtr<TIfaceIface> iface;
    ifaceList = if_list_get(); // external (C coded) function
    ptr = ifaceList;

    if  (!ifaceList) {
        Log(Error) << "Unable to read interface info. Inactive mode failed." << LogEnd;
        return;
    }
    while (ptr!=NULL) {
        iface = getIfaceByID(ptr->id);
        if (iface && (ptr->flags!=iface->getFlags())) {
            Log(Notice) << "Flags on interface " << iface->getFullName() << " has changed (old=" << hex <<iface->getFlags()
                        << ", new=" << ptr->flags << ")." << dec << LogEnd;
            iface->updateState(ptr);
        }
        ptr = ptr->next;
    }

    if_list_release(ifaceList); // allocated in pure C, and so release it there
}

void TSrvIfaceMgr::instanceCreate(const std::string& xmlDumpFile)
{
    if (Instance) {
      Log(Crit) << "SrvIfaceMgr instance already created! Application error." << LogEnd;
      return; // don't create second instance
    }
    Instance = new TSrvIfaceMgr(xmlDumpFile);
}

TSrvIfaceMgr & TSrvIfaceMgr::instance()
{
    if (!Instance) {
        Log(Crit) << "SrvIfaceMgr not create yet. Application error. Emergency shutdown."
                  << LogEnd;
        exit(EXIT_FAILURE);
    }
    return *Instance;
}

bool TSrvIfaceMgr::addFQDN(int iface, SPtr<TIPv6Addr> dnsAddr, SPtr<TIPv6Addr> addr,
                           const std::string& name) {

    bool success = true;

#ifndef MOD_SRV_DISABLE_DNSUPDATE
    SPtr<TSrvCfgIface> cfgIface = SrvCfgMgr().getIfaceByID(iface);
    if (!cfgIface) {
        Log(Error) << "Unable find cfgIface with ifindex=" << iface << ", DDNS failed."
                   << LogEnd;
        return false;
    }

    DnsUpdateModeCfg FQDNMode = static_cast<DnsUpdateModeCfg>(cfgIface->getFQDNMode());

    SPtr<TSIGKey> key = SrvCfgMgr().getKey();

    TCfgMgr::DNSUpdateProtocol proto = SrvCfgMgr().getDDNSProtocol();
    DNSUpdate::DnsUpdateProtocol proto2 = DNSUpdate::DNSUPDATE_TCP;
    if (proto == TCfgMgr::DNSUPDATE_UDP)
        proto2 = DNSUpdate::DNSUPDATE_UDP;
    if (proto == TCfgMgr::DNSUPDATE_ANY)
        proto2 = DNSUpdate::DNSUPDATE_ANY;
    unsigned int timeout = SrvCfgMgr().getDDNSTimeout();

    // FQDNMode: 0 = NONE, 1 = PTR only, 2 = BOTH PTR and AAAA
    if ((FQDNMode == DNSUPDATE_MODE_PTR) || (FQDNMode == DNSUPDATE_MODE_BOTH)) {
        //Test for DNS update
        char zoneroot[128];
        doRevDnsZoneRoot(addr->getAddr(), zoneroot, cfgIface->getRevDNSZoneRootLength());
        /* add PTR only */
        DnsUpdateResult result = DNSUPDATE_SKIP;
        DNSUpdate *act = new DNSUpdate(dnsAddr->getPlain(), zoneroot, name, addr->getPlain(),
                                       DNSUPDATE_PTR, proto2);
	
	if (key) {
	    act->setTSIG(key->Name_, key->getPackedData(), key->getAlgorithmText(),
			 key->Fudge_);
	}

        result = act->run(timeout);
        act->showResult(result);
        delete act;

        success = (result == DNSUPDATE_SUCCESS);
    }

    if (FQDNMode == DNSUPDATE_MODE_BOTH) {
        DnsUpdateResult result = DNSUPDATE_SKIP;
        DNSUpdate *act = new DNSUpdate(dnsAddr->getPlain(), "", name,
                                       addr->getPlain(),
                                       DNSUPDATE_AAAA, proto2);

	if (key) {
	    act->setTSIG(key->Name_, key->getPackedData(), key->getAlgorithmText(),
			 key->Fudge_);
	}

        result = act->run(timeout);
        act->showResult(result);
        delete act;
        success = (result == DNSUPDATE_SUCCESS) && success;
    }
#else
    Log(Info) << "DNSUpdate not compiled in. Pretending success." << LogEnd;
#endif

    return success;
}

bool TSrvIfaceMgr::delFQDN(int iface, SPtr<TIPv6Addr> dnsAddr, SPtr<TIPv6Addr> addr,
                           const std::string& name) {

    bool success = true;

#ifndef MOD_SRV_DISABLE_DNSUPDATE
    SPtr<TSrvCfgIface> cfgIface = SrvCfgMgr().getIfaceByID(iface);
    if (!cfgIface) {
        Log(Error) << "Unable find cfgIface with ifindex=" << iface << ", DDNS failed."
                   << LogEnd;
        return false;
    }

    DnsUpdateModeCfg FQDNMode = static_cast<DnsUpdateModeCfg>(cfgIface->getFQDNMode());

    SPtr<TSIGKey> key = SrvCfgMgr().getKey();

    char zoneroot[128];
    doRevDnsZoneRoot(addr->getAddr(), zoneroot, cfgIface->getRevDNSZoneRootLength());

    // that's ugly but required. Otherwise we would have to include CfgMgr.h in DNSUpdate.h
    // and that would include both poslib and Dibbler headers in one place. Universe would
    // implode then.
    TCfgMgr::DNSUpdateProtocol proto = SrvCfgMgr().getDDNSProtocol();
    DNSUpdate::DnsUpdateProtocol proto2 = DNSUpdate::DNSUPDATE_TCP;
    if (proto == TCfgMgr::DNSUPDATE_UDP)
        proto2 = DNSUpdate::DNSUPDATE_UDP;
    if (proto == TCfgMgr::DNSUPDATE_ANY)
        proto2 = DNSUpdate::DNSUPDATE_ANY;
    unsigned int timeout = SrvCfgMgr().getDDNSTimeout();

    // FQDNMode: 0 = NONE, 1 = PTR only, 2 = BOTH PTR and AAAA
    if ((FQDNMode == DNSUPDATE_MODE_PTR) || (FQDNMode == DNSUPDATE_MODE_BOTH)) {
        /* PTR cleanup */
        // Log(Notice) << "FQDN: Attempting to clean up PTR record in DNS Server "
        //            << dnsAddr->getPlain() << ", IP = " << addr->getPlain()
        //            << " and FQDN=" << name << LogEnd;
        DNSUpdate *act = new DNSUpdate(dnsAddr->getPlain(), zoneroot, name, addr->getPlain(),
                                       DNSUPDATE_PTR_CLEANUP, proto2);

	if (key) {
	    act->setTSIG(key->Name_, key->getPackedData(), key->getAlgorithmText(),
			 key->Fudge_);
	}

        int result = act->run(timeout);
        act->showResult(result);
        delete act;
        success = (result == DNSUPDATE_SUCCESS);
    }

    if (FQDNMode == DNSUPDATE_MODE_BOTH) {
        /* AAAA Cleanup */
        //Log(Notice) << "FQDN: Attempting to clean up AAAA and PTR record in DNS Server "
        //            << dnsAddr->getPlain() << ", IP = " << addr->getPlain()
        //            << " and FQDN=" << name << LogEnd;

        DNSUpdate *act = new DNSUpdate(dnsAddr->getPlain(), "", name, addr->getPlain(),
                                       DNSUPDATE_AAAA_CLEANUP, proto2);

	if (key) {
	    act->setTSIG(key->Name_, key->getPackedData(), key->getAlgorithmText(),
			 key->Fudge_);
	}

        int result = act->run(timeout);
        act->showResult(result);
        delete act;

        success = (result == DNSUPDATE_SUCCESS) && success;

    }
#else
    Log(Info) << "DNSUpdate not compiled in. Pretending success." << LogEnd;
#endif

    return success;

}

void TSrvIfaceMgr::notifyScripts(const std::string& scriptName, SPtr<TMsg> question,
                                 SPtr<TMsg> answer) {
    TNotifyScriptParams* params = (TNotifyScriptParams*)answer->getNotifyScriptParams();

    // add info about relays
    SPtr<TSrvMsg> reply = (Ptr*)answer;

    const vector<TSrvMsg::RelayInfo> relayInfo = reply->getRelayInfo();

    stringstream relaysNum;
    relaysNum << relayInfo.size();
    params->addParam("RELAYS", relaysNum.str());

    int cnt = 1;
    for (vector<TSrvMsg::RelayInfo>::const_reverse_iterator relay = relayInfo.rbegin();
         relay != relayInfo.rend(); ++relay) {
        stringstream peer;
        stringstream link;
        peer << "RELAY" << cnt << "_PEER";
        link << "RELAY" << cnt << "_LINK";

        params->addParam(peer.str(), relay->PeerAddr_->getPlain());
        params->addParam(link.str(), relay->LinkAddr_->getPlain());
    }

    TIfaceMgr::notifyScripts(scriptName, question, answer);
}

ostream & operator <<(ostream & strum, TSrvIfaceMgr &x) {
    strum << "<SrvIfaceMgr>" << std::endl;
    SPtr<TSrvIfaceIface> ptr;
    x.IfaceLst.first();
    while ( ptr= (Ptr*) x.IfaceLst.get() ) {
        strum << *ptr;
    }
    strum << "</SrvIfaceMgr>" << std::endl;
    return strum;
}

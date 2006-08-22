/*
 * Dibbler - a portable DHCPv6
 *
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>
 *          Marek Senderski <msend@o2.pl>
 *
 * released under GNU GPL v2 or later licence
 *
 * $Id: Iface.cpp,v 1.21 2006-08-22 00:01:20 thomson Exp $
 *
 */

#include <iostream>
#include <sstream>
#include "Iface.h"
#include "Portable.h"
#include "Logger.h"

using namespace std;
/*
 * stores informations about interface
 */
TIfaceIface::TIfaceIface(const char * name, int id, unsigned int flags, char* mac, 
			 int maclen, char* llAddr, int llAddrCnt, char * globalAddr, int globalCnt, int hwType)
{
#ifdef LINUX
    snprintf(this->Name,MAX_IFNAME_LENGTH,"%s",name);
#endif
#ifdef WIN32
    _snprintf(this->Name,MAX_IFNAME_LENGTH,"%s",name);
#endif
    this->ID = id;
    this->Flags = flags;

    // store mac address
    this->Maclen=maclen;
    this->Mac=new char[maclen];
    memcpy(this->Mac,mac,maclen);
 
    // store all link-layer addresses
    this->LLAddrCnt=llAddrCnt;
    if (llAddrCnt>0)
    {
        this->LLAddr=new char[16*llAddrCnt];
        memcpy(this->LLAddr,llAddr,16*llAddrCnt);
    }
    else
        this->LLAddr=NULL;
    this->PresLLAddr=this->LLAddr;

    // store all global addresses
    for (int i=0; i<globalCnt; i++) {
	SmartPtr<TIPv6Addr> addr = new TIPv6Addr(globalAddr+16*i);
	this->GlobalAddrLst.append(addr);
    }

    // store hardware type
    this->HWType=hwType;
}

/*
 * returns interface name
 */
char* TIfaceIface::getName() {
    return this->Name;
}

/*
 * returns interface ID
 */
int TIfaceIface::getID() {
    return this->ID;
}

string TIfaceIface::getFullName() {
    ostringstream oss;
    oss << this->ID;
    return string(this->Name)
	+"/"
	+oss.str();
}

/*
 * return interface flags
 */
unsigned int TIfaceIface::getFlags() {
    return this->Flags;
}

/*
 * returns true if interface is UP
 */
bool TIfaceIface::flagUp() {
    return this->Flags&IF_UP;
}

/*
 * returns true if interface is RUNNING
 */
bool TIfaceIface::flagRunning() {
    return (bool)(this->Flags & IF_RUNNING);
}

/*
 * returns true is interface is MULTICAST capable
 */
bool TIfaceIface::flagMulticast() {
    return (bool)(this->Flags&IF_MULTICAST);
}

/*
 * returns true is interface is LOOPBACK
 */
bool TIfaceIface::flagLoopback() {
    return (bool)(this->Flags&IF_LOOPBACK);
}

/*
 * returns MAC length
 */
int TIfaceIface::getMacLen() {
    return this->Maclen;
}

/*
 * returns MAC
 */
char* TIfaceIface::getMac() {
    return this->Mac;
}

void TIfaceIface::firstGlobalAddr() {
    this->GlobalAddrLst.first();
}

SmartPtr<TIPv6Addr> TIfaceIface::getGlobalAddr() {
    return this->GlobalAddrLst.get();
}

unsigned int TIfaceIface::countGlobalAddr() {
    return this->GlobalAddrLst.count();
}

void TIfaceIface::addGlobalAddr(SmartPtr<TIPv6Addr> addr) {
    this->GlobalAddrLst.append(addr);
}

void TIfaceIface::delGlobalAddr(SmartPtr<TIPv6Addr> addr) {
    // FIXME: Implement this
}


/*
 * returns HW type 
 */
int TIfaceIface::getHardwareType() {
    return this->HWType;
}

// --------------------------------------------------------------------
// --- address related ------------------------------------------------
// --------------------------------------------------------------------

/*
 * adds address to this interface with prefered- and valid-lifetime
 * (wrapper around pure C function)
 */
bool TIfaceIface::addAddr(SmartPtr<TIPv6Addr> addr,long pref, long valid) {
    return (bool)ipaddr_add(this->Name, this->ID, addr->getPlain(), 
			    pref, valid, this->PrefixLen);
}

/*
 * deletes address from interface
 * (wrapper around pure C function)
 */
bool TIfaceIface::delAddr(SmartPtr<TIPv6Addr> addr) {
    return (bool)ipaddr_del( this->Name, this->ID, addr->getPlain(), this->PrefixLen);
}

/*
 * update address prefered- and valid-lifetime
 */
bool TIfaceIface::updateAddr(SmartPtr<TIPv6Addr> addr, long pref, long valid) {
#ifdef WIN32
    return (bool)ipaddr_add((char *)this->Name, this->ID, (char *)addr->getPlain(), 
			    pref, valid, this->PrefixLen);
#endif

#ifdef LINUX
  // FIXME: Linux kernel currently does not provide API for dynamic adresses
#endif
    return true;
}

/*
 * get first LL address
 */
char* TIfaceIface::firstLLAddress() {
    return PresLLAddr=LLAddr;
}

/*
 * get next LL address
 * (oh boy, this method stinks. Nobody uses it, anyway)
 */
char* TIfaceIface::getLLAddress() {
    char* retVal;
    if( (retVal=this->PresLLAddr) ) {
        if ( (this->PresLLAddr-this->LLAddr) < (16*this->LLAddrCnt) )
            this->PresLLAddr+=16;
        else
            this->PresLLAddr=NULL;
    }
    return retVal;
}

int TIfaceIface::countLLAddress() {
    return this->LLAddrCnt;
}

// --------------------------------------------------------------------
// --- socket related -------------------------------------------------
// --------------------------------------------------------------------

/*
 * binds socket to one address only
 */
bool TIfaceIface::addSocket(SmartPtr<TIPv6Addr> addr,int port, bool ifaceonly, bool reuse) {
    // Log(Debug) << "Creating socket on " << *addr << " address." << LogEnd;
    SmartPtr<TIfaceSocket> ptr = 
	new TIfaceSocket(this->Name, this->ID, port, addr, ifaceonly, reuse);
    if (ptr->getStatus()!=CONFIGURED) {
	return false;
    }
    SocketsLst.append(ptr);
    return true;
}

/*
 * binds socket on whole interface
 */
bool TIfaceIface::addSocket(int port, bool ifaceonly, bool reuse) {
    SmartPtr<TIfaceSocket> ptr = 
	new TIfaceSocket(this->Name, this->ID, port, ifaceonly, reuse);
    if (ptr->getStatus()!=CONFIGURED) {
	return false;
    }
    SocketsLst.append(ptr);
    return true;
}

/*
 * closes socket
 */
bool TIfaceIface::delSocket(int fd) {
    SmartPtr<TIfaceSocket> sock;
    SocketsLst.first();
    
    while ( sock = SocketsLst.get() ) {
	if (sock->getFD() == fd) {
	    SocketsLst.del();
	    return true;
	}
    }
    return false;
}

/*
 * rewinds sockets list to the beginning
 */
void TIfaceIface::firstSocket() {
    SocketsLst.first();
}

/*
 * returns next socket from list
 */
SmartPtr <TIfaceSocket> TIfaceIface::getSocket() {
    return SocketsLst.get();
}

/*
 * returns socket by FileDescriptor (or NULL, if no such socket exists)
 */
SmartPtr <TIfaceSocket> TIfaceIface::getSocketByFD(int fd) {
    SmartPtr<TIfaceSocket> ptr;
    SocketsLst.first();
    while ( ptr = SocketsLst.get() ) {
	if ( ptr->getFD()==fd )
	    return ptr;
    }
    return 0; // NULL
}

/*
 * returns sockets count
 */
int TIfaceIface::countSocket() {
    return SocketsLst.count();
}

/*
 *  releases data allocated for ll addresses
 */
TIfaceIface::~TIfaceIface() {
    if (this->LLAddrCnt>0) {
	delete this->LLAddr;
    }
}

SmartPtr<TIfaceSocket> TIfaceIface::getSocketByAddr(SmartPtr<TIPv6Addr> addr) {
    SmartPtr<TIfaceSocket> ptr;
    SocketsLst.first();
    while ( ptr = SocketsLst.get() ) {
	if ( *ptr->getAddr()==*addr )
	    return ptr;
    }
    return 0; // NULL
}

void TIfaceIface::setPrefixLength(int len) {
    if (len>128 || len<0) {
	Log(Error) << "Invalid length " << len << " set attempt was ignored on the " << this->getFullName() << " interface." << LogEnd;
	return;
    }
    this->PrefixLen = len;
}

// --------------------------------------------------------------------
// --- operators ------------------------------------------------------
// --------------------------------------------------------------------
/*
 * just prints important informations (debugging & logging)
 */
ostream & operator <<(ostream & strum, TIfaceIface &x) {
    char buf[48];

    strum << "  <IfaceIface";
    strum << " name=\"" << x.Name << "\"";
    strum << " id=\"" << x.ID << "\"";
    strum << " flags=\"" << x.Flags << "\">" << endl;
    strum << "    <!-- PrefixLength configured to " << x.PrefixLen << " -->" << endl;
    strum << "    <!-- " << x.LLAddrCnt << " link scoped addrs -->" << endl;

    for (int i=0; i<x.LLAddrCnt; i++) {
	inet_ntop6(x.LLAddr+i*16,buf);
	strum << "    <Addr>" << buf << "</Addr>" << endl;
    }

    strum << "    <!-- " << x.countGlobalAddr() << " non-local addrs -->" << endl;

    x.firstGlobalAddr();
    SmartPtr<TIPv6Addr> addr;
    while (addr = x.getGlobalAddr()) {
	strum << "    " << *addr;
    }

    strum << "    <Mac>";
    for (int i=0; i<x.Maclen; i++) {
	strum.fill('0');
	strum.width(2);
	strum << (hex) << (int) x.Mac[i];
	if (i<x.Maclen-1) strum  << ":";
    }
    strum << "</Mac>" << endl;

    SmartPtr<TIfaceSocket> sock;
    x.firstSocket();
    while (sock = x.getSocket() ) {
	strum << "    " << *sock;
    }
    strum << "  </IfaceIface>" << endl;
    return strum;
}

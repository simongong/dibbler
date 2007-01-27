/*                                                                           
 * Dibbler - a portable DHCPv6                                               
 *                                                                           
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>                           
 *          Marek Senderski <msend@o2.pl>                                    
 *                                                                           
 * released under GNU GPL v2 or later licence                                
 *                                                                           
 * $Id: DHCPClient.cpp,v 1.26 2007-01-27 17:07:04 thomson Exp $
 *                                                                           
 */

#include <iostream>
#include <stdlib.h>
#include "SmartPtr.h"
#include "DHCPClient.h"
#include "ClntTransMgr.h"

#include "IfaceMgr.h"
#include "ClntIfaceMgr.h"
#include "Logger.h"
#include "Portable.h"

volatile int serviceShutdown;

TDHCPClient::TDHCPClient(string config)
{
    serviceShutdown = 0;
    srand(now());
    this->IsDone = false;

    IfaceMgr = new TClntIfaceMgr(CLNTIFACEMGR_FILE);
    if ( this->IfaceMgr->isDone() ) {
 	  Log(Crit) << "Fatal error during IfaceMgr initialization." << LogEnd;
	  this->IsDone = true;
	  return;
    }

    this->CfgMgr = new TClntCfgMgr(IfaceMgr, config);
    if ( this->CfgMgr->isDone() ) {
	Log(Crit) << "Fatal error during CfgMgr initialization." << LogEnd;
	this->IsDone = true;
	return;
    }

    this->AddrMgr = new TClntAddrMgr(CfgMgr, CLNTADDRMGR_FILE, false);
    if ( this->AddrMgr->isDone() ) {
 	  Log(Crit) << "Fatal error during AddrMgr initialization." << LogEnd;
	  this->IsDone = true;
	  return;
    }

    this->TransMgr = new TClntTransMgr(IfaceMgr, AddrMgr, CfgMgr, CLNTTRANSMGR_FILE);
    if ( this->TransMgr->isDone() ) {
	Log(Crit) << "Fatal error during TransMgr initialization." << LogEnd;
	this->IsDone = true;
	return;
    }

    TransMgr->setContext(TransMgr);
}

void TDHCPClient::stop() {
    serviceShutdown = 1;

#ifdef WIN32
    // just to break select() in WIN32 systems
    SmartPtr<TIfaceIface> iface = IfaceMgr->getIfaceByID(TransMgr->getCtrlIface());
    Log(Warning) << "Sending SHUTDOWN packet on the " << iface->getName()
        << "/" << iface->getID() << " (addr=" << TransMgr->getCtrlAddr() << ")." << LogEnd;
    int fd = sock_add("", TransMgr->getCtrlIface(),"::",0,true, false); 
    char buf = CONTROL_MSG;
    int cnt=sock_send(fd,TransMgr->getCtrlAddr(),&buf,1,DHCPCLIENT_PORT,TransMgr->getCtrlIface());
    sock_del(fd);
#endif
}


void TDHCPClient::run()
{
    SmartPtr<TMsg> msg;
    while ( (!this->isDone()) && !TransMgr->isDone() )
    {
	if (serviceShutdown)
	    TransMgr->shutdown();
	
	TransMgr->doDuties();
	
	unsigned int timeout = TransMgr->getTimeout();

#if 1
	if (timeout == 0)
	    timeout = 1;
#endif
	
        Log(Debug) << "Sleeping for " << timeout << " second(s)." << LogEnd;
        SmartPtr<TClntMsg> msg=IfaceMgr->select(timeout);
	
        if (msg) {
	    int iface = msg->getIface();
	    SmartPtr<TIfaceIface> ptrIface;
	    ptrIface = IfaceMgr->getIfaceByID(iface);
            Log(Info) << "Received " << msg->getName() << " on " << ptrIface->getName() 
		      << "/" << iface	<< hex << ",TransID=0x" << msg->getTransID() 
		      << dec << ", " << msg->countOption() << " opts:";
            SmartPtr<TOpt> ptrOpt;
            msg->firstOption();
            while (ptrOpt = msg->getOption() )
                Log(Cont) << " " << ptrOpt->getOptType(); 
            Log(Cont) << LogEnd;
	    
            TransMgr->relayMsg(msg);
        }
    }
    Log(Notice) << "Bye bye." << LogEnd;
}

bool TDHCPClient::isDone() {
    return IsDone;
}

bool TDHCPClient::checkPrivileges() {
    // FIXME: check privileges
    return true;
}

void TDHCPClient::setWorkdir(std::string workdir) {
    if (this->CfgMgr)
        this->CfgMgr->setWorkdir(workdir);
    this->CfgMgr->dump();
}

TDHCPClient::~TDHCPClient()
{
    if (TransMgr)
	TransMgr->setContext(0);
    this->TransMgr = 0;
    this->AddrMgr  = 0;
    this->CfgMgr   = 0;
    this->IfaceMgr = 0;
}

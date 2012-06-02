/*
 * Dibbler - a portable DHCPv6
 *
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>
 *          Marek Senderski <msend@o2.pl>
 * changes: Krzysztof Wnuk
 *
 * released under GNU GPL v2 only licence
 *
 */

#ifndef SRVCFGOPTIONS_H
#define SRVCFGOPTIONS_H

#include <iostream>
#include <string>
#include <list>

#include "SmartPtr.h"
#include "Container.h"
#include "IPv6Addr.h"
#include "SrvParsGlobalOpt.h"

#include "OptVendorSpecInfo.h"
#include "OptVendorData.h"
#include "OptGeneric.h"

class TSrvCfgIface;

class TSrvCfgOptions 
{
    friend std::ostream& operator<<(std::ostream& out,TSrvCfgIface& iface);
    friend std::ostream& operator<<(std::ostream& out,TSrvCfgOptions& opt);

public:
    TSrvCfgOptions();
    TSrvCfgOptions(SPtr<TDUID> duid);
    TSrvCfgOptions(SPtr<TOptVendorData> remoteid);
    bool setOptions(SPtr<TSrvParsGlobalOpt> opt);
    SPtr<TDUID> getDuid() const;
    SPtr<TOptVendorData> getRemoteID() const;

    // address reservation
    void setAddr(SPtr<TIPv6Addr> addr);
    SPtr<TIPv6Addr> getAddr() const;

    // prefix reservation
    void setPrefix(SPtr<TIPv6Addr> prefix, int length);
    SPtr<TIPv6Addr> getPrefix();
    int getPrefixLen();

    // option: DNS Servers is now handled with extra options mechanism
    // option: Domain is now handled with extra options mechanism
    // option: NTP servers is now handled with extra options mechanism
    // option: Timezone is now handled with extra options mechanism
    // option: SIP servers is now handled with extra options mechanism
    // option: SIP domains is now handled with extra options mechanism
    // option: NIS servers is now handled with extra options mechanism
    // option: NIS+ servers is now handled with extra options mechanism
    // option: NIS domain is now handled with extra options mechanism
    // option: NIS+ domain is now handled with extra options mechanism
    // option: LIFETIME is now handled with extra options mechanism

    // option: VENDOR-SPEC
    List(TOptVendorSpecInfo) getVendorSpecLst(unsigned int vendor=0);

    void addExtraOption(SPtr<TOpt> extra, bool always);
    const TOptList& getExtraOptions();
    SPtr<TOpt> getExtraOption(uint16_t type);
    const TOptList& getForcedOptions();
    void addExtraOptions(const TOptList& extra);
    void addForcedOptions(const TOptList& extra);

private:
    // options
    bool VendorSpecSupport;

    // address reservation
    SPtr<TIPv6Addr> Addr;

    // prefix reservation
    SPtr<TIPv6Addr> Prefix_;
    int PrefixLen_;

    // options reservation
    TOptList ExtraOpts_;  // extra options ALWAYS sent to client (may also include ForcedOpts)
    TOptList ForcedOpts_; // list of options that are forced to client

    void SetDefaults();

    SPtr<TOptVendorData> RemoteID;
    SPtr<TDUID> Duid;
};

#endif

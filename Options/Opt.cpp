/*
 * Dibbler - a portable DHCPv6
 *
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>
 *          Marek Senderski <msend@o2.pl>
 *
 * released under GNU GPL v2 licence
 *
 * $Id: Opt.cpp,v 1.11 2009-03-24 23:17:18 thomson Exp $
 *
 */

#include "Opt.h"

int TOpt::getOptType()
{
    return OptType;
}

TOpt::~TOpt() {

}

TOpt::TOpt( int optType, TMsg *parent){	
    OptType=optType;    
    Parent=parent;
}
int TOpt::getSubOptSize() {
    int size = 0;    
    SubOptions.first();    
    SmartPtr<TOpt> ptr;    
    while (ptr = SubOptions.get()) 		
	size += ptr->getSize();    
    return size;
}
char* TOpt::storeSubOpt( char* buf){
    SmartPtr<TOpt> ptr;	
    SubOptions.first();    
    while ( ptr = SubOptions.get() ) {
	ptr->storeSelf(buf);
	buf += ptr->getSize();    
    }	
    return buf;
}

void TOpt::firstOption() {
    SubOptions.first();
}

SmartPtr<TOpt> TOpt::getOption() {
    return SubOptions.get();
}

SmartPtr<TOpt> TOpt::getOption(int optType) {
    firstOption();
    SmartPtr<TOpt> opt = 0;
    while(opt=getOption()) {
	if (opt->getOptType()==optType)
	    return opt;
    }
    return 0;
}

void TOpt::addOption(SmartPtr<TOpt> opt)
{
    SubOptions.append(opt);
}

int TOpt::countOption()
{
    return SubOptions.count();
}

void TOpt::setParent(TMsg* Parent)
{
    this->Parent=Parent;
}

void TOpt::delAllOptions()
{
    SubOptions.clear();
}

bool TOpt::isValid()
{   
    //for most of options it's enough
    return true;
}

SmartPtr<TDUID> TOpt::getDUID() {
    return this->DUID;
}
void TOpt::setDUID(SmartPtr<TDUID> duid) {
    this->DUID = duid;
}

//CHANGED here: this member function is added.
void TOpt::delOption()
{
  SubOptions.del();
}
     

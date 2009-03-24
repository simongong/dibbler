/*                                                                           
 * Dibbler - a portable DHCPv6                                               
 *                                                                           
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>                           
 *          Marek Senderski <msend@o2.pl>                                    
 *                                                                           
 * released under GNU GPL v2 only licence                                
 *                                                                           
 * $Id: Opt.h,v 1.12 2009-03-24 23:17:18 thomson Exp $
 *                                                                           
 */

#ifndef OPT_H
#define OPT_H

#include "SmartPtr.h"
#include "Container.h"
#include "DUID.h"

class TMsg;

class TOpt
{
  public:
    TOpt(int optType, TMsg* parent);
    virtual ~TOpt();

	/**
	 * Return the size of the option, including :
	 *  - Option number,
	 *  - Option size
	 *  - data
	 * 
	 * @return the size, I've already said that !
	 */
    virtual int getSize() = 0;
    
    /**
     * This method transform the instance of the option class into bytecode
     * ready to be sent to the client or server, conform to the RFC
     * 
     * @param buf The address where to store the option
     * @return The address where the option ends
     */
    virtual char * storeSelf(char* buf) = 0;
    virtual bool doDuties() = 0;
    
    /**
     * Validate the option
     * 
     * @return true if the option is valid.
     */
    virtual bool isValid();
    
    int getOptType();
    int getSubOptSize();
    
    char* storeSubOpt(char* buf);
    SmartPtr<TOpt> getOption(int optType);

    // suboptions management
    void firstOption();
    SmartPtr<TOpt> getOption();
    void addOption(SmartPtr<TOpt> opt);
    void delOption();
    int countOption();
    void delAllOptions();
    void setParent(TMsg* Parent);

    SmartPtr<TDUID> getDUID();
    void setDUID(SmartPtr<TDUID> duid);

 protected:
    TContainer< SmartPtr<TOpt> > SubOptions;
    int OptType;
    TMsg* Parent;
    SmartPtr<TDUID> DUID;
};

#endif

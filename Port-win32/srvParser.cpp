#define YY_SrvParser_h_included

/*  A Bison++ parser, made from SrvParser.y  */

 /* with Bison++ version bison++ Version 1.21-8, adapted from GNU bison by coetmeur@icdc.fr
  */

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* HEADER SECTION */
#if defined( _MSDOS ) || defined(MSDOS) || defined(__MSDOS__) 
#define __MSDOS_AND_ALIKE
#endif
#if defined(_WINDOWS) && defined(_MSC_VER)
#define __HAVE_NO_ALLOCA
#define __MSDOS_AND_ALIKE
#endif

#ifndef alloca
#if defined( __GNUC__)
#define alloca __builtin_alloca

#elif (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)  || defined (__sgi)
#include <alloca.h>

#elif defined (__MSDOS_AND_ALIKE)
#include <malloc.h>
#ifndef __TURBOC__
/* MS C runtime lib */
#define alloca _alloca
#endif

#elif defined(_AIX)
#include <malloc.h>
#pragma alloca

#elif defined(__hpux)
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */

#endif /* not _AIX  not MSDOS, or __TURBOC__ or _AIX, not sparc.  */
#endif /* alloca not defined.  */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif
#ifdef __cplusplus
#ifndef YY_USE_CLASS
#define YY_USE_CLASS
#endif
#else
#ifndef __STDC__
#define const
#endif
#endif
#include <stdio.h>
#define YYBISON 1  

#include <iostream>
#include <string>
#include "FlexLexer.h"
#include <malloc.h>
#include "DHCPConst.h"
#include "SmartPtr.h"
#include "Container.h"
#include "SrvParser.h"
#include "SrvParsGlobalOpt.h"
#include "SrvParsClassOpt.h"
#include "SrvParsIfaceOpt.h"
#include "SrvCfgAddrClass.h"
#include "SrvCfgIface.h"
#include "SrvCfgMgr.h"
#include "DUID.h"
#include "Logger.h"

#define YY_USE_CLASS
#define YY_SrvParser_MEMBERS  FlexLexer * lex;                                                   \
List(TSrvParsGlobalOpt) ParserOptStack;                                            \
/* List of parsed interfaces/IAs/Addresses, last    */                            \
/* interface/IA/address is just being parsing or have been just parsed */   \
/* FIXME:Don't forget to clear this lists in apropriate moment         */   \
List(TSrvCfgIface)          SrvCfgIfaceLst;   \
List(TSrvCfgAddrClass)  SrvCfgAddrClassLst;   \
/*Pointer to list which should contain either DNS servers or NTPServers*/   \
List(TIPv6Addr) PresentLst;  \
/*Pointer to list which should contain: rejected clients, accepted clients */ \
/*or addressess ranges */ \
List(TStationRange) PresentRangeLst; \
/*method check whether interface with id=ifaceNr has been already declared */ \
bool CheckIsIface(int ifaceNr);  \
/*method check whether interface with id=ifaceName has been already declared*/ \
bool CheckIsIface(string ifaceName); \
void StartIfaceDeclaration(); \
bool EndIfaceDeclaration(); \
void StartClassDeclaration(); \
bool EndClassDeclaration();
#define YY_SrvParser_CONSTRUCTOR_PARAM  yyFlexLexer * lex
#define YY_SrvParser_CONSTRUCTOR_CODE  \
    ParserOptStack.append(new TSrvParsGlobalOpt()); \
    ParserOptStack.getLast()->setUnicast(false);    \
   this->lex = lex;

typedef union    
{
    unsigned int ival;
  char                          *strval;
  struct                        SDuid
  {
    int                       length;
    char*                       duid;
    }                                   duidval;
  char                          addrval[16];
} yy_SrvParser_stype;
#define YY_SrvParser_STYPE yy_SrvParser_stype
/* %{ and %header{ and %union, during decl */
#define YY_SrvParser_BISON 1
#ifndef YY_SrvParser_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_SrvParser_COMPATIBILITY 1
#else
#define  YY_SrvParser_COMPATIBILITY 0
#endif
#endif

#if YY_SrvParser_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_SrvParser_LTYPE
#define YY_SrvParser_LTYPE YYLTYPE
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_SrvParser_STYPE 
#define YY_SrvParser_STYPE YYSTYPE
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_SrvParser_DEBUG
#define  YY_SrvParser_DEBUG YYDEBUG
#endif
#endif
#ifdef YY_SrvParser_STYPE
#ifndef yystype
#define yystype YY_SrvParser_STYPE
#endif
#endif
/* use goto to be compatible */
#ifndef YY_SrvParser_USE_GOTO
#define YY_SrvParser_USE_GOTO 1
#endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_SrvParser_USE_GOTO
#define YY_SrvParser_USE_GOTO 0
#endif

#ifndef YY_SrvParser_PURE
/*  YY_SrvParser_PURE */
#endif

/* section apres lecture def, avant lecture grammaire S2 */
/* prefix */
#ifndef YY_SrvParser_DEBUG
/* YY_SrvParser_DEBUG */
#endif


#ifndef YY_SrvParser_LSP_NEEDED
 /* YY_SrvParser_LSP_NEEDED*/
#endif



/* DEFAULT LTYPE*/
#ifdef YY_SrvParser_LSP_NEEDED
#ifndef YY_SrvParser_LTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YY_SrvParser_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
      /* We used to use `unsigned long' as YY_SrvParser_STYPE on MSDOS,
	 but it seems better to be consistent.
	 Most programs should declare their own type anyway.  */

#ifndef YY_SrvParser_STYPE
#define YY_SrvParser_STYPE int
#endif
/* DEFAULT MISCELANEOUS */
#ifndef YY_SrvParser_PARSE
#define YY_SrvParser_PARSE yyparse
#endif
#ifndef YY_SrvParser_LEX
#define YY_SrvParser_LEX yylex
#endif
#ifndef YY_SrvParser_LVAL
#define YY_SrvParser_LVAL yylval
#endif
#ifndef YY_SrvParser_LLOC
#define YY_SrvParser_LLOC yylloc
#endif
#ifndef YY_SrvParser_CHAR
#define YY_SrvParser_CHAR yychar
#endif
#ifndef YY_SrvParser_NERRS
#define YY_SrvParser_NERRS yynerrs
#endif
#ifndef YY_SrvParser_DEBUG_FLAG
#define YY_SrvParser_DEBUG_FLAG yydebug
#endif
#ifndef YY_SrvParser_ERROR
#define YY_SrvParser_ERROR yyerror
#endif
#ifndef YY_SrvParser_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_SrvParser_PARSE_PARAM
#ifndef YY_SrvParser_PARSE_PARAM_DEF
#define YY_SrvParser_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_SrvParser_PARSE_PARAM
#define YY_SrvParser_PARSE_PARAM void
#endif
#endif
#if YY_SrvParser_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YY_SrvParser_LTYPE
#ifndef YYLTYPE
#define YYLTYPE YY_SrvParser_LTYPE
#else
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
#endif
#endif
#ifndef YYSTYPE
#define YYSTYPE YY_SrvParser_STYPE
#else
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
#endif
#ifdef YY_SrvParser_PURE
#ifndef YYPURE
#define YYPURE YY_SrvParser_PURE
#endif
#endif
#ifdef YY_SrvParser_DEBUG
#ifndef YYDEBUG
#define YYDEBUG YY_SrvParser_DEBUG 
#endif
#endif
#ifndef YY_SrvParser_ERROR_VERBOSE
#ifdef YYERROR_VERBOSE
#define YY_SrvParser_ERROR_VERBOSE YYERROR_VERBOSE
#endif
#endif
#ifndef YY_SrvParser_LSP_NEEDED
#ifdef YYLSP_NEEDED
#define YY_SrvParser_LSP_NEEDED YYLSP_NEEDED
#endif
#endif
#endif
#ifndef YY_USE_CLASS
/* TOKEN C */
#define	IFACE_	258
#define	NO_CONFIG_	259
#define	CLASS_	260
#define	LOGNAME_	261
#define	LOGLEVEL_	262
#define	WORKDIR_	263
#define	NTP_SERVER_	264
#define	TIME_ZONE_	265
#define	DNS_SERVER_	266
#define	DOMAIN_	267
#define	ACCEPT_ONLY_	268
#define	REJECT_CLIENTS_	269
#define	POOL_	270
#define	T1_	271
#define	T2_	272
#define	PREF_TIME_	273
#define	VALID_TIME_	274
#define	UNICAST_	275
#define	PREFERENCE_	276
#define	RAPID_COMMIT_	277
#define	MAX_LEASE_	278
#define	CLNT_MAX_LEASE_	279
#define	STRING_	280
#define	HEXNUMBER_	281
#define	INTNUMBER_	282
#define	IPV6ADDR_	283
#define	DUID_	284

 /* #defines tokens */
#else
/* CLASS */
#ifndef YY_SrvParser_CLASS
#define YY_SrvParser_CLASS SrvParser
#endif
#ifndef YY_SrvParser_INHERIT
#define YY_SrvParser_INHERIT
#endif
#ifndef YY_SrvParser_MEMBERS
#define YY_SrvParser_MEMBERS 
#endif
#ifndef YY_SrvParser_LEX_BODY
#define YY_SrvParser_LEX_BODY  
#endif
#ifndef YY_SrvParser_ERROR_BODY
#define YY_SrvParser_ERROR_BODY  
#endif
#ifndef YY_SrvParser_CONSTRUCTOR_PARAM
#define YY_SrvParser_CONSTRUCTOR_PARAM
#endif
#ifndef YY_SrvParser_CONSTRUCTOR_CODE
#define YY_SrvParser_CONSTRUCTOR_CODE
#endif
#ifndef YY_SrvParser_CONSTRUCTOR_INIT
#define YY_SrvParser_CONSTRUCTOR_INIT
#endif
/* choose between enum and const */
#ifndef YY_SrvParser_USE_CONST_TOKEN
#define YY_SrvParser_USE_CONST_TOKEN 0
/* yes enum is more compatible with flex,  */
/* so by default we use it */ 
#endif
#if YY_SrvParser_USE_CONST_TOKEN != 0
#ifndef YY_SrvParser_ENUM_TOKEN
#define YY_SrvParser_ENUM_TOKEN yy_SrvParser_enum_token
#endif
#endif

class YY_SrvParser_CLASS YY_SrvParser_INHERIT
{
public: 
#if YY_SrvParser_USE_CONST_TOKEN != 0
/* static const int token ... */
static const int IFACE_;
static const int NO_CONFIG_;
static const int CLASS_;
static const int LOGNAME_;
static const int LOGLEVEL_;
static const int WORKDIR_;
static const int NTP_SERVER_;
static const int TIME_ZONE_;
static const int DNS_SERVER_;
static const int DOMAIN_;
static const int ACCEPT_ONLY_;
static const int REJECT_CLIENTS_;
static const int POOL_;
static const int T1_;
static const int T2_;
static const int PREF_TIME_;
static const int VALID_TIME_;
static const int UNICAST_;
static const int PREFERENCE_;
static const int RAPID_COMMIT_;
static const int MAX_LEASE_;
static const int CLNT_MAX_LEASE_;
static const int STRING_;
static const int HEXNUMBER_;
static const int INTNUMBER_;
static const int IPV6ADDR_;
static const int DUID_;

 /* decl const */
#else
enum YY_SrvParser_ENUM_TOKEN { YY_SrvParser_NULL_TOKEN=0
	,IFACE_=258
	,NO_CONFIG_=259
	,CLASS_=260
	,LOGNAME_=261
	,LOGLEVEL_=262
	,WORKDIR_=263
	,NTP_SERVER_=264
	,TIME_ZONE_=265
	,DNS_SERVER_=266
	,DOMAIN_=267
	,ACCEPT_ONLY_=268
	,REJECT_CLIENTS_=269
	,POOL_=270
	,T1_=271
	,T2_=272
	,PREF_TIME_=273
	,VALID_TIME_=274
	,UNICAST_=275
	,PREFERENCE_=276
	,RAPID_COMMIT_=277
	,MAX_LEASE_=278
	,CLNT_MAX_LEASE_=279
	,STRING_=280
	,HEXNUMBER_=281
	,INTNUMBER_=282
	,IPV6ADDR_=283
	,DUID_=284

 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_SrvParser_PARSE (YY_SrvParser_PARSE_PARAM);
 virtual void YY_SrvParser_ERROR(char *msg) YY_SrvParser_ERROR_BODY;
#ifdef YY_SrvParser_PURE
#ifdef YY_SrvParser_LSP_NEEDED
 virtual int  YY_SrvParser_LEX (YY_SrvParser_STYPE *YY_SrvParser_LVAL,YY_SrvParser_LTYPE *YY_SrvParser_LLOC) YY_SrvParser_LEX_BODY;
#else
 virtual int  YY_SrvParser_LEX (YY_SrvParser_STYPE *YY_SrvParser_LVAL) YY_SrvParser_LEX_BODY;
#endif
#else
 virtual int YY_SrvParser_LEX() YY_SrvParser_LEX_BODY;
 YY_SrvParser_STYPE YY_SrvParser_LVAL;
#ifdef YY_SrvParser_LSP_NEEDED
 YY_SrvParser_LTYPE YY_SrvParser_LLOC;
#endif
 int   YY_SrvParser_NERRS;
 int    YY_SrvParser_CHAR;
#endif
#if YY_SrvParser_DEBUG != 0
 int YY_SrvParser_DEBUG_FLAG;   /*  nonzero means print parse trace     */
#endif
public:
 YY_SrvParser_CLASS(YY_SrvParser_CONSTRUCTOR_PARAM);
public:
 YY_SrvParser_MEMBERS 
};
/* other declare folow */
#if YY_SrvParser_USE_CONST_TOKEN != 0
const int YY_SrvParser_CLASS::IFACE_=258;
const int YY_SrvParser_CLASS::NO_CONFIG_=259;
const int YY_SrvParser_CLASS::CLASS_=260;
const int YY_SrvParser_CLASS::LOGNAME_=261;
const int YY_SrvParser_CLASS::LOGLEVEL_=262;
const int YY_SrvParser_CLASS::WORKDIR_=263;
const int YY_SrvParser_CLASS::NTP_SERVER_=264;
const int YY_SrvParser_CLASS::TIME_ZONE_=265;
const int YY_SrvParser_CLASS::DNS_SERVER_=266;
const int YY_SrvParser_CLASS::DOMAIN_=267;
const int YY_SrvParser_CLASS::ACCEPT_ONLY_=268;
const int YY_SrvParser_CLASS::REJECT_CLIENTS_=269;
const int YY_SrvParser_CLASS::POOL_=270;
const int YY_SrvParser_CLASS::T1_=271;
const int YY_SrvParser_CLASS::T2_=272;
const int YY_SrvParser_CLASS::PREF_TIME_=273;
const int YY_SrvParser_CLASS::VALID_TIME_=274;
const int YY_SrvParser_CLASS::UNICAST_=275;
const int YY_SrvParser_CLASS::PREFERENCE_=276;
const int YY_SrvParser_CLASS::RAPID_COMMIT_=277;
const int YY_SrvParser_CLASS::MAX_LEASE_=278;
const int YY_SrvParser_CLASS::CLNT_MAX_LEASE_=279;
const int YY_SrvParser_CLASS::STRING_=280;
const int YY_SrvParser_CLASS::HEXNUMBER_=281;
const int YY_SrvParser_CLASS::INTNUMBER_=282;
const int YY_SrvParser_CLASS::IPV6ADDR_=283;
const int YY_SrvParser_CLASS::DUID_=284;

 /* const YY_SrvParser_CLASS::token */
#endif
/*apres const  */
YY_SrvParser_CLASS::YY_SrvParser_CLASS(YY_SrvParser_CONSTRUCTOR_PARAM) YY_SrvParser_CONSTRUCTOR_INIT
{
#if YY_SrvParser_DEBUG != 0
YY_SrvParser_DEBUG_FLAG=0;
#endif
YY_SrvParser_CONSTRUCTOR_CODE;
};
#endif


#define	YYFINAL		132
#define	YYFLAG		32768
#define	YYNTBASE	34

#define YYTRANSLATE(x) ((unsigned)(x) <= 284 ? yytranslate[x] : 75)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    32,    33,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    30,     2,    31,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29
};

#if YY_SrvParser_DEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     3,     5,     7,    10,    13,    14,    21,    22,
    29,    33,    37,    39,    42,    44,    47,    48,    54,    56,
    59,    61,    63,    65,    69,    71,    75,    79,    85,    87,
    91,    95,   101,   103,   107,   111,   117,   118,   122,   123,
   127,   128,   132,   135,   140,   143,   148,   151,   156,   159,
   164,   165,   169,   170,   174,   177,   180,   183,   186,   189,
   192,   195,   198,   201,   204,   207,   209,   211,   213,   215,
   217,   219,   221,   223,   225,   227,   229,   231,   233,   235,
   237,   239,   241,   243,   245,   247,   249
};

static const short yyrhs[] = {    35,
     0,     0,    72,     0,    36,     0,    35,    72,     0,    35,
    36,     0,     0,     3,    25,    30,    37,    39,    31,     0,
     0,     3,    43,    30,    38,    39,    31,     0,     3,    25,
     4,     0,     3,    43,     4,     0,    73,     0,    39,    73,
     0,    40,     0,    39,    40,     0,     0,     5,    30,    41,
    42,    31,     0,    74,     0,    42,    74,     0,    26,     0,
    27,     0,    28,     0,    44,    32,    28,     0,    28,     0,
    28,    33,    28,     0,    45,    32,    28,     0,    45,    32,
    28,    33,    28,     0,    28,     0,    28,    33,    28,     0,
    46,    32,    28,     0,    46,    32,    28,    33,    28,     0,
    29,     0,    29,    33,    29,     0,    46,    32,    29,     0,
    46,    32,    29,    33,    29,     0,     0,    14,    48,    46,
     0,     0,    13,    50,    46,     0,     0,    15,    52,    45,
     0,    18,    43,     0,    18,    43,    33,    43,     0,    19,
    43,     0,    19,    43,    33,    43,     0,    16,    43,     0,
    16,    43,    33,    43,     0,    17,    43,     0,    17,    43,
    33,    43,     0,     0,    11,    58,    44,     0,     0,     9,
    60,    44,     0,    12,    25,     0,    10,    25,     0,    24,
    43,     0,    20,    28,     0,    20,    43,     0,    22,    43,
     0,    21,    43,     0,    23,    43,     0,     7,    43,     0,
     6,    25,     0,     8,    25,     0,    73,     0,    69,     0,
    70,     0,    71,     0,    74,     0,    64,     0,    57,     0,
    59,     0,    61,     0,    62,     0,    53,     0,    54,     0,
    51,     0,    55,     0,    56,     0,    47,     0,    49,     0,
    65,     0,    66,     0,    67,     0,    68,     0,    63,     0
};

#endif

#if YY_SrvParser_DEBUG != 0
static const short yyrline[] = { 0,
    90,    91,    95,    96,    97,    98,   105,   110,   122,   127,
   135,   145,   155,   156,   157,   158,   162,   170,   177,   178,
   187,   188,   214,   218,   225,   229,   238,   242,   254,   258,
   267,   271,   281,   286,   298,   303,   318,   322,   328,   332,
   338,   343,   349,   354,   362,   367,   375,   380,   388,   393,
   401,   405,   411,   415,   428,   435,   442,   449,   457,   466,
   473,   482,   489,   498,   505,   512,   513,   514,   515,   519,
   520,   521,   522,   523,   524,   528,   529,   530,   531,   532,
   534,   535,   536,   537,   538,   539,   540
};

static const char * const yytname[] = {   "$","error","$illegal.","IFACE_","NO_CONFIG_",
"CLASS_","LOGNAME_","LOGLEVEL_","WORKDIR_","NTP_SERVER_","TIME_ZONE_","DNS_SERVER_",
"DOMAIN_","ACCEPT_ONLY_","REJECT_CLIENTS_","POOL_","T1_","T2_","PREF_TIME_",
"VALID_TIME_","UNICAST_","PREFERENCE_","RAPID_COMMIT_","MAX_LEASE_","CLNT_MAX_LEASE_",
"STRING_","HEXNUMBER_","INTNUMBER_","IPV6ADDR_","DUID_","'{'","'}'","','","'-'",
"Grammar","GlobalDeclarationList","InterfaceDeclaration","@1","@2","InterfaceDeclarationsList",
"ClassDeclaration","@3","ClassOptionDeclarationsList","Number","ADDRESSList",
"ADDRESSRangeList","ADDRESSDUIDRangeList","RejectClientsOption","@4","AcceptOnlyOption",
"@5","PoolOption","@6","PreferredTimeOption","ValidTimeOption","T1Option","T2Option",
"DNSServerOption","@7","NTPServerOption","@8","DomainOption","TimeZoneOption",
"ClntMaxLeaseOption","UnicastAddressOption","UnicastOption","RapidCommitOption",
"PreferenceOption","MaxLeaseOption","LogLevelOption","LogNameOption","WorkDirOption",
"GlobalOptionDeclaration","InterfaceOptionDeclaration","ClassOptionDeclaration",
""
};
#endif

static const short yyr1[] = {     0,
    34,    34,    35,    35,    35,    35,    37,    36,    38,    36,
    36,    36,    39,    39,    39,    39,    41,    40,    42,    42,
    43,    43,    44,    44,    45,    45,    45,    45,    46,    46,
    46,    46,    46,    46,    46,    46,    48,    47,    50,    49,
    52,    51,    53,    53,    54,    54,    55,    55,    56,    56,
    58,    57,    60,    59,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,    72,    72,    72,    72,    73,
    73,    73,    73,    73,    73,    74,    74,    74,    74,    74,
    74,    74,    74,    74,    74,    74,    74
};

static const short yyr2[] = {     0,
     1,     0,     1,     1,     2,     2,     0,     6,     0,     6,
     3,     3,     1,     2,     1,     2,     0,     5,     1,     2,
     1,     1,     1,     3,     1,     3,     3,     5,     1,     3,
     3,     5,     1,     3,     3,     5,     0,     3,     0,     3,
     0,     3,     2,     4,     2,     4,     2,     4,     2,     4,
     0,     3,     0,     3,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1
};

static const short yydefact[] = {     2,
     0,     0,     0,     0,    53,     0,    51,     0,    39,    37,
    41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     1,     4,    81,    82,    78,    76,    77,    79,    80,    72,
    73,    74,    75,    87,    71,    83,    84,    85,    86,    67,
    68,    69,     3,    66,    70,     0,    21,    22,     0,    64,
    63,    65,     0,    56,     0,    55,     0,     0,     0,    47,
    49,    43,    45,    58,    59,    61,    60,    62,    57,     6,
     5,    11,     7,    12,     9,    23,    54,    52,    29,    33,
    40,    38,    25,    42,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    48,    50,    44,    46,
     0,     0,    15,    13,     0,    24,    30,    34,    31,    35,
    26,    27,    17,     8,    16,    14,    10,     0,     0,     0,
     0,    32,    36,    28,     0,     0,    19,    18,    20,     0,
     0,     0
};

static const short yydefgoto[] = {   130,
    21,    22,    89,    90,   102,   103,   121,   126,    65,    77,
    84,    81,    23,    58,    24,    57,    25,    59,    26,    27,
    28,    29,    30,    55,    31,    53,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45
};

static const short yypact[] = {    85,
   -17,   -22,    18,   -20,-32768,    17,-32768,    40,-32768,-32768,
-32768,    18,    18,    18,    18,    -5,    18,    18,    18,    18,
    85,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,    11,-32768,-32768,    36,-32768,
-32768,-32768,    42,-32768,    42,-32768,    35,    35,    55,    57,
    78,    79,    80,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   100,   100,   101,   102,
   104,   104,   106,   108,    18,    18,    18,    18,   105,   105,
   109,   110,   112,    39,   114,   116,-32768,-32768,-32768,-32768,
   103,    15,-32768,-32768,    38,-32768,-32768,-32768,   126,   127,
-32768,   128,-32768,-32768,-32768,-32768,-32768,   117,   133,   135,
   134,-32768,-32768,-32768,    18,    58,-32768,-32768,-32768,   164,
   165,-32768
};

static const short yypgoto[] = {-32768,
-32768,   145,-32768,-32768,    77,   -98,-32768,-32768,    -1,   113,
-32768,   111,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   149,    41,  -120
};


#define	YYLAST		170


static const short yytable[] = {    49,
   127,    51,    50,   115,    52,   129,   115,    46,    47,    48,
    60,    61,    62,    63,    72,    66,    67,    68,    69,   101,
    47,    48,    64,     5,     6,     7,     8,     9,    10,    11,
    12,    13,    14,    15,    16,    17,    18,    19,    20,    74,
    73,    54,   101,    47,    48,   114,     5,     6,     7,     8,
     9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
    19,    20,    79,    80,    56,    75,   109,   110,   117,    76,
     9,    10,    11,    12,    13,    14,    15,   125,    17,    18,
    19,    20,    83,    97,    98,    99,   100,     1,   128,    85,
     2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
    12,    13,    14,    15,    16,    17,    18,    19,    20,   101,
    86,    87,    88,     5,     6,     7,     8,     9,    10,    11,
    12,    13,    14,    15,    16,    17,    18,    19,    20,   104,
   104,    91,   113,    92,    93,    94,   106,   107,    95,    96,
   108,   111,   116,   112,   122,   116,     9,    10,    11,    12,
    13,    14,    15,   125,    17,    18,    19,    20,   118,   119,
   120,   123,   124,   131,   132,    70,   105,    78,    82,    71
};

static const short yycheck[] = {     1,
   121,     3,    25,   102,    25,   126,   105,    25,    26,    27,
    12,    13,    14,    15,     4,    17,    18,    19,    20,     5,
    26,    27,    28,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,     4,
    30,    25,     5,    26,    27,    31,     9,    10,    11,    12,
    13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
    23,    24,    28,    29,    25,    30,    28,    29,    31,    28,
    13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
    23,    24,    28,    85,    86,    87,    88,     3,    31,    33,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,     5,
    33,    33,    33,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    89,
    90,    32,    30,    33,    33,    32,    28,    28,    33,    32,
    29,    28,   102,    28,    28,   105,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    33,    33,
    33,    29,    28,     0,     0,    21,    90,    55,    58,    21
};
 /* fattrs + tables */

/* parser code folow  */


/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: dollar marks section change
   the next  is replaced by the list of actions, each action
   as one case of the switch.  */ 

#if YY_SrvParser_USE_GOTO != 0
/* 
 SUPRESSION OF GOTO : on some C++ compiler (sun c++)
  the goto is strictly forbidden if any constructor/destructor
  is used in the whole function (very stupid isn't it ?)
 so goto are to be replaced with a 'while/switch/case construct'
 here are the macro to keep some apparent compatibility
*/
#define YYGOTO(lb) {yy_gotostate=lb;continue;}
#define YYBEGINGOTO  enum yy_labels yy_gotostate=yygotostart; \
                     for(;;) switch(yy_gotostate) { case yygotostart: {
#define YYLABEL(lb) } case lb: {
#define YYENDGOTO } } 
#define YYBEGINDECLARELABEL enum yy_labels {yygotostart
#define YYDECLARELABEL(lb) ,lb
#define YYENDDECLARELABEL  };
#else
/* macro to keep goto */
#define YYGOTO(lb) goto lb
#define YYBEGINGOTO 
#define YYLABEL(lb) lb:
#define YYENDGOTO
#define YYBEGINDECLARELABEL 
#define YYDECLARELABEL(lb)
#define YYENDDECLARELABEL 
#endif
/* LABEL DECLARATION */
YYBEGINDECLARELABEL
  YYDECLARELABEL(yynewstate)
  YYDECLARELABEL(yybackup)
/* YYDECLARELABEL(yyresume) */
  YYDECLARELABEL(yydefault)
  YYDECLARELABEL(yyreduce)
  YYDECLARELABEL(yyerrlab)   /* here on detecting error */
  YYDECLARELABEL(yyerrlab1)   /* here on error raised explicitly by an action */
  YYDECLARELABEL(yyerrdefault)  /* current state does not do anything special for the error token. */
  YYDECLARELABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */
  YYDECLARELABEL(yyerrhandle)  
YYENDDECLARELABEL
/* ALLOCA SIMULATION */
/* __HAVE_NO_ALLOCA */
#ifdef __HAVE_NO_ALLOCA
int __alloca_free_ptr(char *ptr,char *ref)
{if(ptr!=ref) free(ptr);
 return 0;}

#define __ALLOCA_alloca(size) malloc(size)
#define __ALLOCA_free(ptr,ref) __alloca_free_ptr((char *)ptr,(char *)ref)

#ifdef YY_SrvParser_LSP_NEEDED
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		    __ALLOCA_free(yyls,yylsa)+\
		   (num))
#else
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		   (num))
#endif
#else
#define __ALLOCA_return(num) return(num)
#define __ALLOCA_alloca(size) alloca(size)
#define __ALLOCA_free(ptr,ref) 
#endif

/* ENDALLOCA SIMULATION */

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (YY_SrvParser_CHAR = YYEMPTY)
#define YYEMPTY         -2
#define YYEOF           0
#define YYACCEPT        __ALLOCA_return(0)
#define YYABORT         __ALLOCA_return(1)
#define YYERROR         YYGOTO(yyerrlab1)
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL          YYGOTO(yyerrlab)
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                                                              \
  if (YY_SrvParser_CHAR == YYEMPTY && yylen == 1)                               \
    { YY_SrvParser_CHAR = (token), YY_SrvParser_LVAL = (value);                 \
      yychar1 = YYTRANSLATE (YY_SrvParser_CHAR);                                \
      YYPOPSTACK;                                               \
      YYGOTO(yybackup);                                            \
    }                                                           \
  else                                                          \
    { YY_SrvParser_ERROR ("syntax error: cannot back up"); YYERROR; }   \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YY_SrvParser_PURE
/* UNPURE */
#define YYLEX           YY_SrvParser_LEX()
#ifndef YY_USE_CLASS
/* If nonreentrant, and not class , generate the variables here */
int     YY_SrvParser_CHAR;                      /*  the lookahead symbol        */
YY_SrvParser_STYPE      YY_SrvParser_LVAL;              /*  the semantic value of the */
				/*  lookahead symbol    */
int YY_SrvParser_NERRS;                 /*  number of parse errors so far */
#ifdef YY_SrvParser_LSP_NEEDED
YY_SrvParser_LTYPE YY_SrvParser_LLOC;   /*  location data for the lookahead     */
			/*  symbol                              */
#endif
#endif


#else
/* PURE */
#ifdef YY_SrvParser_LSP_NEEDED
#define YYLEX           YY_SrvParser_LEX(&YY_SrvParser_LVAL, &YY_SrvParser_LLOC)
#else
#define YYLEX           YY_SrvParser_LEX(&YY_SrvParser_LVAL)
#endif
#endif
#ifndef YY_USE_CLASS
#if YY_SrvParser_DEBUG != 0
int YY_SrvParser_DEBUG_FLAG;                    /*  nonzero means print parse trace     */
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif
#endif



/*  YYINITDEPTH indicates the initial size of the parser's stacks       */

#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif


#if __GNUC__ > 1                /* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)       __builtin_memcpy(TO,FROM,COUNT)
#else                           /* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */

#ifdef __cplusplus
static void __yy_bcopy (char *from, char *to, int count)
#else
#ifdef __STDC__
static void __yy_bcopy (char *from, char *to, int count)
#else
static void __yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
#endif
#endif
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}
#endif

int
#ifdef YY_USE_CLASS
 YY_SrvParser_CLASS::
#endif
     YY_SrvParser_PARSE(YY_SrvParser_PARSE_PARAM)
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
/* parameter definition without protypes */
YY_SrvParser_PARSE_PARAM_DEF
#endif
#endif
#endif
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YY_SrvParser_STYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1=0;          /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YY_SrvParser_STYPE yyvsa[YYINITDEPTH];        /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YY_SrvParser_STYPE *yyvs = yyvsa;     /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YY_SrvParser_LSP_NEEDED
  YY_SrvParser_LTYPE yylsa[YYINITDEPTH];        /*  the location stack                  */
  YY_SrvParser_LTYPE *yyls = yylsa;
  YY_SrvParser_LTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YY_SrvParser_PURE
  int YY_SrvParser_CHAR;
  YY_SrvParser_STYPE YY_SrvParser_LVAL;
  int YY_SrvParser_NERRS;
#ifdef YY_SrvParser_LSP_NEEDED
  YY_SrvParser_LTYPE YY_SrvParser_LLOC;
#endif
#endif

  YY_SrvParser_STYPE yyval;             /*  the variable used to return         */
				/*  semantic values from the action     */
				/*  routines                            */

  int yylen;
/* start loop, in which YYGOTO may be used. */
YYBEGINGOTO

#if YY_SrvParser_DEBUG != 0
  if (YY_SrvParser_DEBUG_FLAG)
    fprintf(stderr, "Starting parse\n");
#endif
  yystate = 0;
  yyerrstatus = 0;
  YY_SrvParser_NERRS = 0;
  YY_SrvParser_CHAR = YYEMPTY;          /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YY_SrvParser_LSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
YYLABEL(yynewstate)

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YY_SrvParser_STYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YY_SrvParser_LSP_NEEDED
      YY_SrvParser_LTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YY_SrvParser_LSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YY_SrvParser_LSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  YY_SrvParser_ERROR("parser stack overflow");
	  __ALLOCA_return(2);
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) __ALLOCA_alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      __ALLOCA_free(yyss1,yyssa);
      yyvs = (YY_SrvParser_STYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
      __ALLOCA_free(yyvs1,yyvsa);
#ifdef YY_SrvParser_LSP_NEEDED
      yyls = (YY_SrvParser_LTYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
      __ALLOCA_free(yyls1,yylsa);
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YY_SrvParser_LSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YY_SrvParser_DEBUG != 0
      if (YY_SrvParser_DEBUG_FLAG)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YY_SrvParser_DEBUG != 0
  if (YY_SrvParser_DEBUG_FLAG)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  YYGOTO(yybackup);
YYLABEL(yybackup)

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* YYLABEL(yyresume) */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yydefault);

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (YY_SrvParser_CHAR == YYEMPTY)
    {
#if YY_SrvParser_DEBUG != 0
      if (YY_SrvParser_DEBUG_FLAG)
	fprintf(stderr, "Reading a token: ");
#endif
      YY_SrvParser_CHAR = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (YY_SrvParser_CHAR <= 0)           /* This means end of input. */
    {
      yychar1 = 0;
      YY_SrvParser_CHAR = YYEOF;                /* Don't call YYLEX any more */

#if YY_SrvParser_DEBUG != 0
      if (YY_SrvParser_DEBUG_FLAG)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(YY_SrvParser_CHAR);

#if YY_SrvParser_DEBUG != 0
      if (YY_SrvParser_DEBUG_FLAG)
	{
	  fprintf (stderr, "Next token is %d (%s", YY_SrvParser_CHAR, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, YY_SrvParser_CHAR, YY_SrvParser_LVAL);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    YYGOTO(yydefault);

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrlab);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrlab);

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YY_SrvParser_DEBUG != 0
  if (YY_SrvParser_DEBUG_FLAG)
    fprintf(stderr, "Shifting token %d (%s), ", YY_SrvParser_CHAR, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (YY_SrvParser_CHAR != YYEOF)
    YY_SrvParser_CHAR = YYEMPTY;

  *++yyvsp = YY_SrvParser_LVAL;
#ifdef YY_SrvParser_LSP_NEEDED
  *++yylsp = YY_SrvParser_LLOC;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  YYGOTO(yynewstate);

/* Do the default action for the current state.  */
YYLABEL(yydefault)

  yyn = yydefact[yystate];
  if (yyn == 0)
    YYGOTO(yyerrlab);

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
YYLABEL(yyreduce)
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YY_SrvParser_DEBUG != 0
  if (YY_SrvParser_DEBUG_FLAG)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 7:
{
      CheckIsIface(string(yyvsp[-1].strval)); //If no - everything is ok
      StartIfaceDeclaration();
  ;
    break;}
case 8:
{
    //Information about new interface has been read
    //Add it to list of read interfaces
      SrvCfgIfaceLst.append(new TSrvCfgIface(yyvsp[-4].strval));
      //FIXME:used of char * should be always realeased
      delete yyvsp[-4].strval;
      EndIfaceDeclaration();
  ;
    break;}
case 9:
{
        CheckIsIface(yyvsp[-1].ival);   //If no - everything is ok
        StartIfaceDeclaration();
  ;
    break;}
case 10:
{
      SrvCfgIfaceLst.append(new TSrvCfgIface(yyvsp[-4].ival));
      EndIfaceDeclaration();
  ;
    break;}
case 11:
{
      CheckIsIface(string(yyvsp[-1].strval));
      SrvCfgIfaceLst.append(new TSrvCfgIface(yyvsp[-1].strval));
      SrvCfgIfaceLst.getLast()->setOptions(ParserOptStack.getLast());
      SrvCfgIfaceLst.getLast()->setNoConfig();
    ;
    break;}
case 12:
{
        CheckIsIface(yyvsp[-1].ival);
      SrvCfgIfaceLst.append(new TSrvCfgIface(yyvsp[-1].ival));
      SrvCfgIfaceLst.getLast()->setOptions(ParserOptStack.getLast());
        SrvCfgIfaceLst.getLast()->setNoConfig();
    ;
    break;}
case 17:
{ 
        StartClassDeclaration();
    ;
    break;}
case 18:
{
            EndClassDeclaration();
        ;
    break;}
case 21:
{yyval.ival=yyvsp[0].ival;;
    break;}
case 22:
{yyval.ival=yyvsp[0].ival;;
    break;}
case 23:
{
    PresentLst.append(new TIPv6Addr(yyvsp[0].addrval));
  ;
    break;}
case 24:
{
    PresentLst.append(new TIPv6Addr(yyvsp[0].addrval));
  ;
    break;}
case 25:
{
        PresentRangeLst.append(new TStationRange(new TIPv6Addr(yyvsp[0].addrval),new TIPv6Addr(yyvsp[0].addrval)));
    ;
    break;}
case 26:
{
        SmartPtr<TIPv6Addr> addr1(new TIPv6Addr(yyvsp[-2].addrval));
        SmartPtr<TIPv6Addr> addr2(new TIPv6Addr(yyvsp[0].addrval));
        if (*addr1<=*addr2)
            PresentRangeLst.append(new TStationRange(addr1,addr2));
        else
            PresentRangeLst.append(new TStationRange(addr2,addr1));
    ;
    break;}
case 27:
{
        PresentRangeLst.append(new TStationRange(new TIPv6Addr(yyvsp[0].addrval),new TIPv6Addr(yyvsp[0].addrval)));
    ;
    break;}
case 28:
{
        SmartPtr<TIPv6Addr> addr1(new TIPv6Addr(yyvsp[-2].addrval));
        SmartPtr<TIPv6Addr> addr2(new TIPv6Addr(yyvsp[0].addrval));
        if (*addr1<=*addr2)
            PresentRangeLst.append(new TStationRange(addr1,addr2));
        else
            PresentRangeLst.append(new TStationRange(addr2,addr1));
    ;
    break;}
case 29:
{
        PresentRangeLst.append(new TStationRange(new TIPv6Addr(yyvsp[0].addrval),new TIPv6Addr(yyvsp[0].addrval)));
    ;
    break;}
case 30:
{
        SmartPtr<TIPv6Addr> addr1(new TIPv6Addr(yyvsp[-2].addrval));
        SmartPtr<TIPv6Addr> addr2(new TIPv6Addr(yyvsp[0].addrval));
        if (*addr1<=*addr2)
            PresentRangeLst.append(new TStationRange(addr1,addr2));
        else
            PresentRangeLst.append(new TStationRange(addr2,addr1));
    ;
    break;}
case 31:
{
        PresentRangeLst.append(new TStationRange(new TIPv6Addr(yyvsp[0].addrval),new TIPv6Addr(yyvsp[0].addrval)));
    ;
    break;}
case 32:
{
        SmartPtr<TIPv6Addr> addr1(new TIPv6Addr(yyvsp[-2].addrval));
        SmartPtr<TIPv6Addr> addr2(new TIPv6Addr(yyvsp[0].addrval));
        if (*addr1<=*addr2)
            PresentRangeLst.append(new TStationRange(addr1,addr2));
        else
            PresentRangeLst.append(new TStationRange(addr2,addr1));
    ;
    break;}
case 33:
{
        PresentRangeLst.append(new TStationRange(new TDUID(yyvsp[0].duidval.duid,yyvsp[0].duidval.length)));
        delete yyvsp[0].duidval.duid;
    ;
    break;}
case 34:
{   
        SmartPtr<TDUID> duid1(new TDUID(yyvsp[-2].duidval.duid,yyvsp[-2].duidval.length));
        SmartPtr<TDUID> duid2(new TDUID(yyvsp[0].duidval.duid,yyvsp[0].duidval.length));
        
        if (*duid1<=*duid2)
            PresentRangeLst.append(new TStationRange(duid1,duid2));
        else
            PresentRangeLst.append(new TStationRange(duid2,duid1));
        delete yyvsp[-2].duidval.duid;
        delete yyvsp[0].duidval.duid;
    ;
    break;}
case 35:
{
        PresentRangeLst.append(new TStationRange(new TDUID(yyvsp[0].duidval.duid,yyvsp[0].duidval.length)));
        delete yyvsp[0].duidval.duid;
    ;
    break;}
case 36:
{
        SmartPtr<TDUID> duid2(new TDUID(yyvsp[-2].duidval.duid,yyvsp[-2].duidval.length));
        SmartPtr<TDUID> duid1(new TDUID(yyvsp[0].duidval.duid,yyvsp[0].duidval.length));
        if (*duid1<=*duid2)
            PresentRangeLst.append(new TStationRange(duid1,duid2));
        else
            PresentRangeLst.append(new TStationRange(duid2,duid1));
        delete yyvsp[-2].duidval.duid;
        delete yyvsp[0].duidval.duid;
    ;
    break;}
case 37:
{
        PresentRangeLst.clear();    
    ;
    break;}
case 38:
{
        ParserOptStack.getLast()->setRejedClnt(&PresentRangeLst);
    ;
    break;}
case 39:
{
        PresentRangeLst.clear();    
    ;
    break;}
case 40:
{
        ParserOptStack.getLast()->setAcceptClnt(&PresentRangeLst);
    ;
    break;}
case 41:
{

            PresentRangeLst.clear();    
        ;
    break;}
case 42:
{
            ParserOptStack.getLast()->setPool(&PresentRangeLst);
        ;
    break;}
case 43:
{ 
        ParserOptStack.getLast()->setPrefBeg(yyvsp[0].ival);
        ParserOptStack.getLast()->setPrefEnd(yyvsp[0].ival);
    ;
    break;}
case 44:
{
        ParserOptStack.getLast()->setPrefBeg(yyvsp[-2].ival);
        ParserOptStack.getLast()->setPrefEnd(yyvsp[0].ival);   
    ;
    break;}
case 45:
{ 
        ParserOptStack.getLast()->setValidBeg(yyvsp[0].ival);
        ParserOptStack.getLast()->setValidEnd(yyvsp[0].ival);
    ;
    break;}
case 46:
{
        ParserOptStack.getLast()->setValidBeg(yyvsp[-2].ival);
        ParserOptStack.getLast()->setValidEnd(yyvsp[0].ival);  
    ;
    break;}
case 47:
{
        ParserOptStack.getLast()->setT1Beg(yyvsp[0].ival); 
        ParserOptStack.getLast()->setT1End(yyvsp[0].ival); 
    ;
    break;}
case 48:
{
        ParserOptStack.getLast()->setT1Beg(yyvsp[-2].ival); 
        ParserOptStack.getLast()->setT1End(yyvsp[0].ival); 
    ;
    break;}
case 49:
{ 
        ParserOptStack.getLast()->setT2Beg(yyvsp[0].ival); 
        ParserOptStack.getLast()->setT2End(yyvsp[0].ival); 
    ;
    break;}
case 50:
{
        ParserOptStack.getLast()->setT2Beg(yyvsp[-2].ival); 
        ParserOptStack.getLast()->setT2End(yyvsp[0].ival); 
    ;
    break;}
case 51:
{
        PresentLst.clear();
  ;
    break;}
case 52:
{
            ParserOptStack.getLast()->setDNSSrv(&PresentLst);
  ;
    break;}
case 53:
{
    PresentLst.clear();
  ;
    break;}
case 54:
{
        ParserOptStack.getLast()->setNTPSrv(&PresentLst);
    ;
    break;}
case 55:
{ 
        ParserOptStack.getLast()->setDomain(yyvsp[0].strval);
    ;
    break;}
case 56:
{ 
        ParserOptStack.getLast()->setTimeZone(yyvsp[0].strval); 
    ;
    break;}
case 57:
{ 
        ParserOptStack.getLast()->setMaxClientLease(yyvsp[0].ival);    
    ;
    break;}
case 58:
{
        ParserOptStack.getLast()->setUnicast(true);
        ParserOptStack.getLast()->setAddress(new TIPv6Addr(yyvsp[0].addrval));
    ;
    break;}
case 59:
{
        if((yyvsp[0].ival&&(!ParserOptStack.getLast()->getUnicast() ))||(yyvsp[0].ival>1))
            YYABORT; //there should be declared prior unicast address
        ParserOptStack.getLast()->setUnicast(yyvsp[0].ival);
    ;
    break;}
case 60:
{ 
        ParserOptStack.getLast()->setRapidCommit(yyvsp[0].ival); 
    ;
    break;}
case 61:
{ 
        if ((yyvsp[0].ival<0)||(yyvsp[0].ival>255))
            YYABORT; //FIXME:Exception or what kind of notification
        ParserOptStack.getLast()->setPreference(yyvsp[0].ival);    
    ;
    break;}
case 62:
{
        ParserOptStack.getLast()->setMaxLeases(yyvsp[0].ival);
    ;
    break;}
case 63:
{
        if (yyvsp[0].ival<5)
            ParserOptStack.getLast()->setLogLevel(yyvsp[0].ival);
        else
            YYABORT;
    ;
    break;}
case 64:
{
        ParserOptStack.getLast()->setLogName(yyvsp[0].strval);
    ;
    break;}
case 65:
{
        ParserOptStack.getLast()->setWorkDir(yyvsp[0].strval);
    ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign  */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YY_SrvParser_LSP_NEEDED
  yylsp -= yylen;
#endif

#if YY_SrvParser_DEBUG != 0
  if (YY_SrvParser_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YY_SrvParser_LSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = YY_SrvParser_LLOC.first_line;
      yylsp->first_column = YY_SrvParser_LLOC.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  YYGOTO(yynewstate);

YYLABEL(yyerrlab)   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++YY_SrvParser_NERRS;

#ifdef YY_SrvParser_ERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      YY_SrvParser_ERROR(msg);
	      free(msg);
	    }
	  else
	    YY_SrvParser_ERROR ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YY_SrvParser_ERROR_VERBOSE */
	YY_SrvParser_ERROR("parse error");
    }

  YYGOTO(yyerrlab1);
YYLABEL(yyerrlab1)   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (YY_SrvParser_CHAR == YYEOF)
	YYABORT;

#if YY_SrvParser_DEBUG != 0
      if (YY_SrvParser_DEBUG_FLAG)
	fprintf(stderr, "Discarding token %d (%s).\n", YY_SrvParser_CHAR, yytname[yychar1]);
#endif

      YY_SrvParser_CHAR = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;              /* Each real token shifted decrements this */

  YYGOTO(yyerrhandle);

YYLABEL(yyerrdefault)  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) YYGOTO(yydefault);
#endif

YYLABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YY_SrvParser_LSP_NEEDED
  yylsp--;
#endif

#if YY_SrvParser_DEBUG != 0
  if (YY_SrvParser_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

YYLABEL(yyerrhandle)

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yyerrdefault);

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    YYGOTO(yyerrdefault);

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrpop);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrpop);

  if (yyn == YYFINAL)
    YYACCEPT;

#if YY_SrvParser_DEBUG != 0
  if (YY_SrvParser_DEBUG_FLAG)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = YY_SrvParser_LVAL;
#ifdef YY_SrvParser_LSP_NEEDED
  *++yylsp = YY_SrvParser_LLOC;
#endif

  yystate = yyn;
  YYGOTO(yynewstate);
/* end loop, in which YYGOTO may be used. */
  YYENDGOTO
}

/* END */


/////////////////////////////////////////////////////////////////////////////
// programs section

//method check whether interface with id=ifaceNr has been 
//already declared
bool SrvParser::CheckIsIface(int ifaceNr)
{
  SmartPtr<TSrvCfgIface> ptr;
  SrvCfgIfaceLst.first();
  while (ptr=SrvCfgIfaceLst.get())
    if ((ptr->getID())==ifaceNr) YYABORT;
};
    
//method check whether interface with id=ifaceName has been
//already declared 
bool SrvParser::CheckIsIface(string ifaceName)
{
  SmartPtr<TSrvCfgIface> ptr;
  SrvCfgIfaceLst.first();
  while (ptr=SrvCfgIfaceLst.get())
  {
    string presName=ptr->getName();
    if (presName==ifaceName) YYABORT;
  };
};

//method creates new scope appropriately for interface options and declarations
//clears all lists except the list of interfaces and adds new group
void SrvParser::StartIfaceDeclaration()
{
  //Interface scope, so parameters associated with global scope are pushed on stack
  ParserOptStack.append(new TSrvParsGlobalOpt(*ParserOptStack.getLast()));
  SrvCfgAddrClassLst.clear();

}

bool SrvParser::EndIfaceDeclaration()
{

  SmartPtr<TSrvCfgAddrClass> ptrAddrClass;
  if (!SrvCfgAddrClassLst.count())
    YYABORT;
  SrvCfgAddrClassLst.first();
    while (ptrAddrClass=SrvCfgAddrClassLst.get())
      SrvCfgIfaceLst.getLast()->addAddrClass(ptrAddrClass);
  //setting interface options on the basis of just read information
  SrvCfgIfaceLst.getLast()->setOptions(ParserOptStack.getLast());
  //FIXED:Here should be add list of Groups to this iface and here it is
  
  //if (groupsCnt==0)
  //  EmptyIface();  //add one IA with one address to this iface
  //restore global options
  ParserOptStack.delLast();
    
}   

void SrvParser::StartClassDeclaration()
{
  ParserOptStack.append(new TSrvParsGlobalOpt(*ParserOptStack.getLast()));
}

bool SrvParser::EndClassDeclaration()
{
    if (!ParserOptStack.getLast()->countPool())
        YYABORT;
    SrvCfgAddrClassLst.append(new TSrvCfgAddrClass());
  //setting interface options on the basis of just read information
  SrvCfgAddrClassLst.getLast()->setOptions(ParserOptStack.getLast());
  //FIXED:Here should be add list of Groups to this iface and here it is
  ParserOptStack.delLast();
}

// <Linux>

extern yy_SrvParser_stype yylval;

int SrvParser::yylex()
{
    int x = this->lex->yylex();
    this->yylval=::yylval;
    return x;
}

void SrvParser::yyerror(char *m)
{
    // logging 
    std::clog << logger::logEmerg << "Config parse error: line " << lex->lineno() << ", unexpected [" 
	 << lex->YYText() << "] token." << logger::endl;
}
// </Linux>

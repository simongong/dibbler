SUBDIRS = .

if HAVE_GTEST
  SUBDIRS += tests
endif

noinst_LIBRARIES = libMisc.a

libMisc_a_CFLAGS = -std=c99

libMisc_a_CPPFLAGS = -I$(top_srcdir)

libMisc_a_SOURCES = addrpack.c base64.c base64.h Container.h
libMisc_a_SOURCES += DHCPConst.cpp DHCPConst.h DHCPDefaults.h
libMisc_a_SOURCES += DUID.cpp DUID.h FQDN.cpp FQDN.h hmac-sha-md5.h hmac-sha-md5.c
libMisc_a_SOURCES += IPv6Addr.cpp IPv6Addr.h KeyList.cpp KeyList.h Key.cpp Key.h
libMisc_a_SOURCES += Logger.cpp Logger.h long128.cpp long128.h md5-coreutils.c md5.h
libMisc_a_SOURCES += Portable.h sha1.c sha1.h sha256.c sha256.h sha512.c sha512.h
libMisc_a_SOURCES += SmartPtr.h ScriptParams.cpp ScriptParams.h lowlevel-posix.c



/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0499 */
/* at Tue Sep 30 17:17:18 2008
 */
/* Compiler settings for .\BDUpdateServiceCom.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IBDUpdateComInterface,0x4ABDD67C,0x44E3,0x42E0,0x81,0x6D,0xD7,0xF0,0xE5,0x47,0x61,0xDF);


MIDL_DEFINE_GUID(IID, LIBID_BDUpdateServiceComLib,0x34F4FEAF,0x4921,0x4B5D,0x8B,0xE5,0xCA,0x38,0x4B,0xFF,0xC2,0xCE);


MIDL_DEFINE_GUID(IID, DIID__IBDUpdateComInterfaceEvents,0xE8057EA1,0x41A4,0x41CA,0xB2,0x83,0xC0,0xE0,0x01,0x3C,0x07,0xCD);


MIDL_DEFINE_GUID(CLSID, CLSID_BDUpdateComInterface,0x94915A56,0x4D71,0x4F85,0xB5,0x9C,0xCC,0x04,0x0F,0x5A,0xC6,0xF0);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif






/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __BDUpdateServiceCom_h__
#define __BDUpdateServiceCom_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBDUpdateComInterface_FWD_DEFINED__
#define __IBDUpdateComInterface_FWD_DEFINED__
typedef interface IBDUpdateComInterface IBDUpdateComInterface;
#endif 	/* __IBDUpdateComInterface_FWD_DEFINED__ */


#ifndef ___IBDUpdateComInterfaceEvents_FWD_DEFINED__
#define ___IBDUpdateComInterfaceEvents_FWD_DEFINED__
typedef interface _IBDUpdateComInterfaceEvents _IBDUpdateComInterfaceEvents;
#endif 	/* ___IBDUpdateComInterfaceEvents_FWD_DEFINED__ */


#ifndef __BDUpdateComInterface_FWD_DEFINED__
#define __BDUpdateComInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class BDUpdateComInterface BDUpdateComInterface;
#else
typedef struct BDUpdateComInterface BDUpdateComInterface;
#endif /* __cplusplus */

#endif 	/* __BDUpdateComInterface_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IBDUpdateComInterface_INTERFACE_DEFINED__
#define __IBDUpdateComInterface_INTERFACE_DEFINED__

/* interface IBDUpdateComInterface */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IBDUpdateComInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4ABDD67C-44E3-42E0-816D-D7F0E54761DF")
    IBDUpdateComInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOptionInt( 
            /* [in] */ LONG iOptionName,
            /* [in] */ LONG iOptionValue,
            /* [out] */ LONG *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOptionBSTR( 
            /* [in] */ LONG iOptionName,
            /* [in] */ BSTR wszOptionValue,
            /* [out] */ LONG *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PerformUpdate( 
            /* [out] */ LONG *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PerformInstall( 
            /* [out] */ LONG *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopUpdate( 
            /* [out] */ LONG *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetAllSettings( 
            /* [out] */ LONG *retVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBDUpdateComInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBDUpdateComInterface * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBDUpdateComInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBDUpdateComInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBDUpdateComInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBDUpdateComInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBDUpdateComInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBDUpdateComInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOptionInt )( 
            IBDUpdateComInterface * This,
            /* [in] */ LONG iOptionName,
            /* [in] */ LONG iOptionValue,
            /* [out] */ LONG *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOptionBSTR )( 
            IBDUpdateComInterface * This,
            /* [in] */ LONG iOptionName,
            /* [in] */ BSTR wszOptionValue,
            /* [out] */ LONG *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PerformUpdate )( 
            IBDUpdateComInterface * This,
            /* [out] */ LONG *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PerformInstall )( 
            IBDUpdateComInterface * This,
            /* [out] */ LONG *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopUpdate )( 
            IBDUpdateComInterface * This,
            /* [out] */ LONG *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetAllSettings )( 
            IBDUpdateComInterface * This,
            /* [out] */ LONG *retVal);
        
        END_INTERFACE
    } IBDUpdateComInterfaceVtbl;

    interface IBDUpdateComInterface
    {
        CONST_VTBL struct IBDUpdateComInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBDUpdateComInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBDUpdateComInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBDUpdateComInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBDUpdateComInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBDUpdateComInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBDUpdateComInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBDUpdateComInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBDUpdateComInterface_SetOptionInt(This,iOptionName,iOptionValue,retVal)	\
    ( (This)->lpVtbl -> SetOptionInt(This,iOptionName,iOptionValue,retVal) ) 

#define IBDUpdateComInterface_SetOptionBSTR(This,iOptionName,wszOptionValue,retVal)	\
    ( (This)->lpVtbl -> SetOptionBSTR(This,iOptionName,wszOptionValue,retVal) ) 

#define IBDUpdateComInterface_PerformUpdate(This,retVal)	\
    ( (This)->lpVtbl -> PerformUpdate(This,retVal) ) 

#define IBDUpdateComInterface_PerformInstall(This,retVal)	\
    ( (This)->lpVtbl -> PerformInstall(This,retVal) ) 

#define IBDUpdateComInterface_StopUpdate(This,retVal)	\
    ( (This)->lpVtbl -> StopUpdate(This,retVal) ) 

#define IBDUpdateComInterface_ResetAllSettings(This,retVal)	\
    ( (This)->lpVtbl -> ResetAllSettings(This,retVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBDUpdateComInterface_INTERFACE_DEFINED__ */



#ifndef __BDUpdateServiceComLib_LIBRARY_DEFINED__
#define __BDUpdateServiceComLib_LIBRARY_DEFINED__

/* library BDUpdateServiceComLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_BDUpdateServiceComLib;

#ifndef ___IBDUpdateComInterfaceEvents_DISPINTERFACE_DEFINED__
#define ___IBDUpdateComInterfaceEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IBDUpdateComInterfaceEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IBDUpdateComInterfaceEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E8057EA1-41A4-41CA-B283-C0E0013C07CD")
    _IBDUpdateComInterfaceEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IBDUpdateComInterfaceEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IBDUpdateComInterfaceEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IBDUpdateComInterfaceEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IBDUpdateComInterfaceEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IBDUpdateComInterfaceEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IBDUpdateComInterfaceEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IBDUpdateComInterfaceEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IBDUpdateComInterfaceEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IBDUpdateComInterfaceEventsVtbl;

    interface _IBDUpdateComInterfaceEvents
    {
        CONST_VTBL struct _IBDUpdateComInterfaceEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IBDUpdateComInterfaceEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IBDUpdateComInterfaceEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IBDUpdateComInterfaceEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IBDUpdateComInterfaceEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IBDUpdateComInterfaceEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IBDUpdateComInterfaceEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IBDUpdateComInterfaceEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IBDUpdateComInterfaceEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_BDUpdateComInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("94915A56-4D71-4F85-B59C-CC040F5AC6F0")
BDUpdateComInterface;
#endif
#endif /* __BDUpdateServiceComLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



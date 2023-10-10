#pragma once
#ifdef OEMUNINSTALL_EXPORTS
#define OEMUNINSTALL_API __declspec(dllexport)
#else
#define OEMUNINSTALL_API __declspec(dllimport)
#endif

#define DBGTRACE_COMPNAME "OEMUninstall"

#define OEM_UNINSTALL_APIVERSION 3

typedef int OEMUNINSTALL_ERR;

#define	OEMUNINSTALL_ERR_NONE							0
#define	OEMUNINSTALL_ERR_LICENSE_INVALID				1
#define	OEMUNINSTALL_ERR_LICENSE_EXPIRED				2
#define	OEMUNINSTALL_ERR_PARAMETER_INVALID				3
#define	OEMUNINSTALL_ERR_INTERFACE_MISMATCH				4
#define	OEMUNINSTALL_ERR_NOMOREPRODUCTS					6
#define	OEMUNINSTALL_ERR_UNINSTALL_STRING_NOT_FOUND		7
#define	OEMUNINSTALL_ERR_UNINSTALLER_FAILED_TO_START	8
#define OEMUNINSTALL_ERR_UNINSTALLER_WAIT_TIMEOUT		9
#define	OEMUNINSTALL_ERR_XML_FILE_NOT_FOUND				10
#define	OEMUNINSTALL_ERR_XML_FILE_CORRUPT				11
#define	OEMUNINSTALL_ERR_XML_NO_PRODUCTS_FOUND			12
#define	OEMUNINSTALL_ERR_OPEN_FAILED_CUSTOM_DATAFILE	13
#define	OEMUNINSTALL_ERR_BDDATAFILE_FILE_NOT_FOUND		14
#define	OEMUNINSTALL_ERR_PARSE_ERROR            		15
#define	OEMUNINSTALL_ERR_COULD_NOT_OPEN_UNINSTALL_KEYS  16
#define	OEMUNINSTALL_ERR_NO_MEMORY                      17
#define	OEMUNINSTALL_ERR_BDDATAFILE_FILE_NOT_SIGNED		18
#define	OEMUNINSTALL_ERR_BDDATAFILE_FILE_NOT_LOADING	19
#define	OEMUNINSTALL_ERR_COULD_NOT_CONNECT_TO_WSC       20

#define	OEMUNINSTALL_PRODUCT_FLAG_MSI			        0x1
#define OEMUNINSTALL_PRODUCT_IS_WOW64                   0x2
#define OEMUNINSTALL_PRODUCT_NEEDS_RESTART              0x4
#define	OEMUNINSTALL_PRODUCT_FOUND_IN_WSC			    0x8
#define OEMUNINSTALL_PRODUCT_FOUND_IN_BDDATAFILE        0x10
#define OEMUNINSTALL_PRODUCT_FOUND_IN_CUSTOMDATAFILE    0x20

#define	OEMUNINSTALL_WSC_PRODUCT_TYPE_FLAG_ANTIVIRUS			0x1
#define	OEMUNINSTALL_WSC_PRODUCT_TYPE_FLAG_ANTISPYWARE	        0x2
#define OEMUNINSTALL_WSC_PRODUCT_TYPE_FLAG_FIREWALL             0x4

struct InstalledProduct
{
	wchar_t * wszDisplayName;
	wchar_t * wszVersionName;
	wchar_t * wszUninstallString;
	int iFlags;
};

struct InstalledProductEx
{
	int nStructSize;
	wchar_t * wszDisplayName;
	wchar_t * wszVersionName;
	wchar_t * wszUninstallString;
	wchar_t * unused;
	int iFlags;
    wchar_t * wszRegistryKey;
};

struct WscProduct
{
	int nStructSize;
	wchar_t * wszName;
	unsigned int nType;
};
typedef void * ProdEnumHandle;

typedef int(__cdecl *GET_PRODUCT_ENUM)(const wchar_t * wszXML, ProdEnumHandle *phPE);
typedef int(__cdecl *FREE_ENUM)(ProdEnumHandle pe);

typedef int(__cdecl *GET_NEXT_INSTALLED_PRODUCT)(ProdEnumHandle hPE, InstalledProduct ** product);
typedef int(__cdecl *FREE_PRODUCT)(InstalledProduct * product);

typedef int(__cdecl *UNINSTALL_PRODUCT)(const InstalledProduct *product, unsigned long * uninstRet, unsigned int uiWaitMilliseconds);
typedef int(__cdecl *UNINSTALL_PRODUCTEx)(const InstalledProductEx *product, unsigned long * uninstRet, unsigned int uiWaitMilliseconds);

typedef int(__cdecl *UNINSTALL_ALL)(const wchar_t * wszXML, int * pUninstCount, int * pFailCount, unsigned int waitMilliseconds);
typedef int(__cdecl *UNINSTALL_ALLEx)(const wchar_t * wszXML, int * pUninstCount, int * pFailCount, unsigned int waitMilliseconds, bool bSilent);

typedef int(__cdecl *GET_NEXT_INSTALLED_PRODUCTEx)(ProdEnumHandle hPE, InstalledProductEx ** product, bool bSilent);
typedef int(__cdecl *FREE_PRODUCTEx)(InstalledProductEx * product);

typedef int(__cdecl *GET_WSC_PRODUCTS)(WscProduct** wscProducts, unsigned int * size);
typedef int(__cdecl *FREE_WSC_PRODUCTS)(WscProduct * wscProducts, unsigned int size);

typedef struct _OemUninstallAPI
{
	int version;
	GET_PRODUCT_ENUM pf_getProductEnum;	
	GET_NEXT_INSTALLED_PRODUCT pf_getNextInstalledProduct;
	UNINSTALL_PRODUCT pf_uninstallProduct;
	UNINSTALL_ALL pf_uninstallAll;
	FREE_PRODUCT pf_freeProduct;
	FREE_ENUM pf_freeEnum;

	UNINSTALL_PRODUCTEx pf_uninstallProductEx;
	UNINSTALL_ALLEx pf_uninstallAllEx;
	GET_NEXT_INSTALLED_PRODUCTEx pf_getNextInstalledProductEx;
	FREE_PRODUCTEx pf_freeProductEx;

    GET_WSC_PRODUCTS pf_getWSCProducts;
    FREE_WSC_PRODUCTS pf_freeWSCProducts;

} OemUninstallAPI;

typedef struct _BDUninstallInitConfig
{
	int version;
    wchar_t* wszBDFilePath;
    wchar_t* wszAdditionalFilePath;
	wchar_t * wszLicenseSerial;
}BDUninstallInitConfig;

#ifdef __cplusplus
extern "C" {
#endif 


OEMUNINSTALL_API int __cdecl oemuninstall_init(OemUninstallAPI * api, BDUninstallInitConfig * initConfig);
OEMUNINSTALL_API int __cdecl oemuninstall_uninit();

#ifdef __cplusplus
}
#endif 

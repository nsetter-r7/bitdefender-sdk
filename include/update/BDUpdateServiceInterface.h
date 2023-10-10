/*! \file BDUpdateServiceInterface.h
 *  \brief  Update SDK Interface - please see also samples and UpdateSdk - howTo.txt
 *  \author Murgan Mihai Silviu
 *  \date   03.09.2008
*/

#ifndef __BD_UPDATE_INTERFACE_H
#define __BD_UPDATE_INTERFACE_H


/** \defgroup retCodes Returning Codes */
/*@{*/
/** No error.
	This is returned when no error appeared. This value should be returned by \ref BDUPDSDKCALLBACK callback function when COM interface is not used or by \ref BDUpdateServiceComLib::_IBDUpdateComInterfaceEvents::ReceiveEvents when COM interface is used.
*/ 
#define BD_UPD_RET_0                        0 
/** This is not an error; it is a status that can be returned only by the \ref BDUPDSDKCALLBACK callback function when COM interface is not used or by the \ref BDUpdateServiceComLib::_IBDUpdateComInterfaceEvents::ReceiveEvents when COM interface is used.
	This return code will never be returned by the SDK functions. This return code can be returned by the registered callback function(if COM not used) or interface(when COM used) in the following cases:\n
	\li \ref BD_UPD_EVENT_UPD_IO_TIMEOUT - there is an I/O timeout when transfering a file\n
	\li \ref BD_UPD_EVENT_UPD_MSG202 - this message appears when the web server replys with HTTP/1.1 202 Accepted
*/
#define BD_UPD_RET_Retry					1
/** An invalid option value was passed to SetOption() -when COM is not used or to SetOptionInt or SetOptionBSTR-when COM is used , for the latter two functions this value will be find in retVal parameter not as returned value.*/ 
#define BD_UPD_RET_Invalid_Opt			-1000
/** An invalid parameter was passed to SetOption() -when COM is not used or to SetOptionInt or SetOptionBSTR-when COM is used,  for the latter two functions this value will be find in retVal parameter not as returned value.*/ 
#define BD_UPD_RET_Invalid_Param		-1001
/** The server name or the complete location for update is not correct.For the COM interface this code will not be found as returned value, but in the retVal parameter.*/ 
#define BD_UPD_RET_BadServerName        -2000
/** The proxy set with SetOption was not valid */
#define BD_UP_RET_BadProxyName			-2001
/** The remote location is not valid.For the COM interface this code will not be found as returned value, but in the retVal parameter.*/ 
#define BD_UPD_RET_BadRemoteLocation    -2002
/** The local path is not valid.For the COM interface this code will not be found as returned value, but in the retVal parameter.*/  
#define BD_UPD_RET_BadLocalPath         -2003
/** The BDUpdateServiceInterface was not properly initialized, when COM is not used, or internal objects of the instantiated COM object were not properly initiated.
For the COM interface this code will not be found as returned value, but in the retVal parameter.*/ 
#define BD_UPD_RET_InvalidObject        -2004
/** The installation process has failed.For the COM interface this code will not be found as returned value, but in the retVal parameter.*/ 
#define BD_UPD_RET_InstallFailed        -2005
/** Creating symlink for bdcore failed*/
#define BD_UPD_RET_InstallCouldNotCreateSymlink	-2006
/** Connection to the specified server failed */
#define BD_UPD_RET_CouldNotConnect		-2100
/** The Http status code was 202 */
#define BD_UPD_RET_HttpError202			-2101
/** The Http status code was 403 */
#define BD_UPD_RET_HttpError403			-2102
/** The Http status code was 404 */
#define BD_UPD_RET_HttpError404			-2112  /*this should remain with this value because moving all other values will invalidate previous builds*/
/** The authentication info specified was not valid - the server/proxy sent a 401/407 code (meaning that the authentication info was not valid) */
#define BD_UPD_RET_CouldNotLogin		-2103
/** The url is invalid */
#define BD_UPD_RET_InvalidUrl			-2104
/** The Update SDK was unable to create some file - usually this happens when the local path does not have the proper directory structure */
#define BD_UPD_RET_InvalidWriteParam	-2105
/** Some other HTTP error, greater than 400 */
#define BD_UPD_RET_HTTPError			-2106
/** A write error has produced - when receiving a HTTP response (usually when downloading a file) */
#define BD_UPD_RET_WriteError			-2107
/** Some I/O operation timed out - when receiving a HTTP response (usually when downloading a file) */
#define BD_UPD_RET_IOTimeout			-2108
/** This might happen if the Windows HTTP Library is not functioning properly */
#define BD_UPD_RET_IO_RecvError			-2109
/** This might happen if the Windows HTTP Library is not functioning properly */
#define BD_UPD_RET_IO_SendError			-2110
/** The response from the server was invalid */
#define BD_UPD_RET_InvalidResponse		-2111
/** The service has been stopped */
#define BD_UPD_RET_ServiceStopped		-2200
/** An unknown error has occured. The best way is to set debug on and see what happen.For the COM interface this code will not be found as returned value, but in the retVal parameter.*/ 
#define BD_UPD_RET_Unknown_Error        -3000
/*@}*/

/** \defgroup optCodes Runtime Options */
/*@{*/
/** Option used to enable/disable debugging. When not using COM interface:
	\code
	int	iOn = 1, iOff = 0;
	pObj->SetOption(BD_UPD_Debugging, &iOn);// enables debug info
	pObj->SetOption(BD_UPD_Debugging, &iOff);// disables debug info
	\endcode
when using COM interface:
	\code
	int	iOn = 1, iOff = 0;
	LONG retVal;
	pObj->SetOptionInt(BD_UPD_Debugging, iOn, &retVal);// enables debug info
	pObj->SetOptionInt(BD_UPD_Debugging, iOff, &retVal);// disables debug info
	\endcode
*/ 
#define BD_UPD_Debugging					0
/** Option used to set proxy .
	When not using COM interface:
	\code
	const char * szProxy = "192.168.0.1:3128";
	pObj->SetOption(BD_UPD_Proxy, szProxy);
	\endcode
	When using COM interface:
	\code
	const wchar_t * proxy = L"192.168.0.1:3128";
	BSTR t = ::SysAllocString((OLECHAR *)proxy);
	pObj->SetOptionBSTR(BD_UPD_Proxy, t, &retVal);
	::SysFreeString(t);
	\endcode
*/ 
#define BD_UPD_Proxy						1
/** Option used to pass credential for proxy.
When not using COM interface:
	\code
	const char * szProxy = "192.168.0.1:3128";
	const char * szProxyAuth = "domain\\user:password";
	pObj->SetOption(BD_UPD_Proxy, szProxy);
	pObj->SetOption(BD_UPD_ProxyAuth, szProxyAuth);
	\endcode
When using COM interface:
	\code
	LONG retVal = 0;
	const wchar_t * wszProxy = L"192.168.0.1:3128";
	const wchar_t * wszProxyAuth = L"domain\\user:password";
	BSTR bproxy = ::SysAllocString((OLECHAR *)wszProxy);
	BSTR bauth = ::SysAllocString((OLECHAR *)wszProxyAuth);
	pObj->SetOptionBSTR(BD_UPD_Proxy, bproxy, &retVal);
	pObj->SetOptionBSTR(BD_UPD_ProxyAuth, bauth, &retVal);
	::SysFreeString(bproxy);
	::SysFreeString(bauth);
	\endcode
*/ 
#define BD_UPD_ProxyAuth					2


/* Options used to set cache directory
    - specify the cache directory used by the update mechanism for storing temporary files when necessary 

	When not using COM:
	\code
	#ifdef WIN32
	const wchar_t * tszCacheDir = L"C:\\Windows\\System32";
	#else
	const char * tszCacheDir = "/some/path";
	#endif

	pObj->SetOption(BD_UPD_CacheDir, tszCacheDir);
	\endcode
	When using COM:
	\code
	LONG retVal = 0;
	const wchar_t * tszCacheDir =  L"C:\\Windows\\System32";
	BSTR bconvert = ::SysAllocString((OLECHAR *)tszCacheDir);
	pObj->SetOptionBSTR(BD_UPD_CacheDir, bconvert, &retVal);
	::SysFreeString(bconvert);
	\endcode
*/
# define BD_UPD_CacheDir					6


/** Option used to pass credential for server
	- expects "user:password"
*/ 
# define BD_UPD_HttpAuth					19

/** Option used to set the connection timeout.
When COM is not used:
	\code
	int	iConnectTimeout = 15;// 15 seconds
	pObj->SetOption(BD_UPD_ConnectTimeout, &iConnectTimeout);
	\endcode
When COM is used:
\code
	LONG retVal;
	int	iConnectTimeout = 15;// 15 seconds
	pObj->SetOptionInt(BD_UPD_ConnectTimeout, iConnectTimeout, &retVal);
\endcode
*/
# define BD_UPD_ConnectTimeout	13
/** Option used to set i/o timeout
When COM is not used
	\code
	int	iIOTimeout = 15;// 15 seconds
	pObj->SetOption(BD_UPD_IOTimeout, &iIOTimeout);
	\endcode
When COM is used:
\code
	LONG retVal;
	int	iIOTimeout = 15;// 15 seconds
	pObj->SetOptionInt(BD_UPD_IOTimeout, iIOTimeout, &retVal);
\endcode
*/
# define BD_UPD_IOTimeout		14

/** Option used to set the user agent prefix. The default user agent will be appended after it.
When not using COM interface:
	\code
	const char * szUserAgentPrefix = "user-agent-prefix";
	pObj->SetOption(BD_UPD_UserAgentPrefix, szUserAgentPrefix);
	\endcode
When using COM interface:
	\code
	LONG retVal = 0;
	const wchar_t * wszUserAgentPrefix = L"user-agent-prefix";
	BSTR bUserAgentPrefix = ::SysAllocString((OLECHAR *)wszUserAgent);
	pObj->SetOptionBSTR(BD_UPD_UserAgentPrefix, bUserAgentPrefix, &retVal);
	::SysFreeString(bUserAgentPrefix);
	\endcode
*/ 
# define BD_UPD_UserAgentPrefix		12

/** Option used to set the server host or the complete update url.
	\remarks There are 2 ways in specifying the URL from which one can update.
	\remarks First is providing the full url
	When COM is not used:
	\code
	const char * szServer = "http://upgrade.bitdefender.com:8080/UpdateLocation";// no secured communication, http port 8080
	// const char * szServer = "https://upgrade.bitdefender.com:8083/UpdateLocation";
	pObj->SetOption(BD_UPD_Server, szServer);
	\endcode
	When COM is used:
	\code
	const wchar_t * wszServer = L"http://upgrade.bitdefender.com:8080/UpdateLocation";// no secured communication, http port 8080
	// const wchar_t * wszServer = L"https://upgrade.bitdefender.com:8083/UpdateLocation";
	BSTR t = ::SysAllocString((OLECHAR *)wszServer);
	pObj->SetOptionBSTR(BD_UPD_Server, t, &retVal);
	::SysFreeString(t);
	\endcode
	\remarks \anchor ServerSecondWay The second is providing the server host, remote location and use https or not.
	When COM is not used:
	\code
	const char * szServer = "upgrade.bitdefender.com:8080";
	const char * szLocation = "UpdateLocation";
	int	iUseHttps = 0;// no secured communication
	// int	iUseHttps = 1;// for secured communication
	pObj->SetOption(BD_UPD_Server, szServer);
	pObj->SetOption(BD_UPD_Remote_Location, szLocation);
	pObj->SetOption(BD_UPD_Use_Https, &iUseHttps);
	\endcode
	When COM is used:
	\code
	LONG retVal = 0;
	const wchar_t * wszServer = L"upgrade.bitdefender.com:8080";
	const wchar_t * wszLocation = L"UpdateLocation";
	int	iUseHttps = 0;// no secured communication
	// int	iUseHttps = 1;// for secured communication
	BSTR bserver = ::SysAllocString((OLECHAR *)wszServer);
	BSTR blocation = ::SysAllocString((OLECHAR *)wszLocation);
	pObj->SetOptionBSTR(BD_UPD_Server, bserver, &retVal);
	pObj->SetOptionBSTR(BD_UPD_Remote_Location, blocation, &retVal);
	pObj->SetOptionInt(BD_UPD_Use_Https, iUseHttps, &retVal);
	::SysFreeString(bserver);
	::SysFreeString(blocation);
	\endcode
*/ 
#define BD_UPD_Server					  600     

/** Option used to set the callback function. This is not applicable when using COM. When using COM see \ref BDUpdateServiceComLib::_IBDUpdateComInterfaceEvents::ReceiveEvents
	\code
	typedef struct {
		char*	m_lpszFileName;//< the name of the file being downloaded
		size_t	m_uSizeDownloaded;//< the size in bytes downloaded so far - from the begining of the update process
	} MyCallbackContext;
	
	int MyCallback(int iEvent, void* lpData, void * lpCtx)
	{
		MyCallbackContext * pPtr = (MyCallbackContext *)lpCtx;
		
		switch (iEvent)
		{
			case BD_UPD_EVENT_UPD_FILE_BEGIN:
				pPtr->m_lpszFileName = (char *)lpData;
				break;
			case BD_UPD_EVENT_UPD_DOWNLOADED_BYTES:
				pPtr->m_uSizeDownloaded = (size_t)*(int *)lpData;
				break;
			default:
				printf("iEvent = %03d, lpData = %p\n", iEvent, lpData);
		}
		
		return BD_UPD_RET_0;
	}
	
	// ...
	MyCallbackContext	globalContext;
	// ...
	pObj->SetOption(BD_UPD_Callback, (void *)(BDUPDSDKCALLBACK)MyCallback);
	pObj->SetOption(BD_UPD_CallbackCtx, & globalContext);
	// ...
	\endcode
*/ 
#define BD_UPD_Callback					  602
/** Option used to set the callback context pointer. This is not applicable when using COM. When using COM see \ref BDUpdateServiceComLib::_IBDUpdateComInterfaceEvents::ReceiveEvents
	See \ref BD_UPD_Callback "callback function option" for callback function context.
*/ 
#define BD_UPD_CallbackCtx                603
#define BD_UPD_UseVersionId               605
/** Option used to set the system directory.
	Specify the system directory in which the update mechanism may download and install files (usually common .dll files). It is important for windows products.
	It has to be set if any system files will be downloaded. Its current value is L".", but, of course this will not be
	the user system directory.
	When not using COM:
	\code
	#ifdef WIN32
	const wchar_t * tszSysDir = L"C:\\Windows\\System32";
	#else
	const char * tszSysDir = "/some/path";
	#endif
	
	pObj->SetOption(BD_UPD_SystemDir, tszSysDir);
	\endcode
	When using COM:
	\code
	LONG retVal = 0;
	const wchar_t * wszSysDir =  L"C:\\Windows\\System32";
	BSTR bconvert = ::SysAllocString((OLECHAR *)wszSysDir);
	pObj->SetOptionBSTR(BD_UPD_SystemDir, bconvert, &retVal);
	::SysFreeString(bconvert);
	\endcode
*/ 
#define BD_UPD_SystemDir				  606

#define BU_UPD_SaveInstall				  610
/** Option used to save install list for calling
    install from another update instance.
*/

#define BD_UPD_UsePatches				  615

/** Option used to enable/disable https.
	See \ref ServerSecondWay "the server option second way" to see how it is used.
*/ 
#define BD_UPD_Use_Https				  618
#ifdef WIN32

#define CALLING_CONVENTION_CDECL __cdecl 

/** Option used to enable/disable p2p. Default is 0.
*/ 
#define BD_UPD_Use_P2P					  619
/** Option used to configure p2p.
*/ 
#define BD_UPD_P2P_Options			      620
typedef struct __BDUP2PTorrentOpt
{
  double ul2dlratio;		/* Ratio between the allowed upload and amount downloaded 
				   - this value is a target, it is not guaranteed */
  int maxseedtime;		/* Maximum time in seconds to seed the files, if the upload limit
				   was not reached */
  int maxdlrate;		/* Maximum download rate in B/s */
  int maxulrate;		/* Maximum upload rate in B/s*/
  int maxconn;			/* Maximum number of simultaneous connections */
  int maxpeers;			/* Maximum number of peers the library will try to download from */
  int min_listening_port;       /* Minimum port number the torrent library will listen on */
  int max_listening_port;       /* Maximum port number the torrent library will listen on */
} BDUP2PTorrentOpt;

/** Option used to replace winhttp with curl on windows.
*/
#define BD_UPD_Use_Curl				      621

#else
	#define CALLING_CONVENTION_CDECL	   /*no cdecl on Linux*/
#if defined(__linux__)
	#define BD_UPD_Abstract_Unix_Socket	 621///< pOptionValue expects char * as abstract Unix domain socket
#endif
#endif

#define BD_UPD_UseWebProxyAutoDetection	 633

#define BD_UPD_PatchServer				 634///< pOptionValue expects char * as "server[:port]" - DEFAULT is the server set with BD_UPD_Server

#define BD_UPD_MaxPatchDownloadErrors	 635
 

#define BD_UPD_SourceFolder				 695

#define BD_UPD_RelativeWebPath			 696
/** Option used to set the original folder from where plugin will be copied */
#define BD_UPD_OriginalFolder			 697

/** Option used to set the remote location.
	See \ref ServerSecondWay "the server option second way" to see how it is used.
*/ 
#define BD_UPD_Remote_Location			  698
/** Option used to set the local path.
	This is the local path where BitDefender engines reside. When not using COM on windows one must provide wchar_t * and on linux & freebsd char *.
	When using COM one must use SetOptionBSTR. See \ref BD_UPD_SystemDir.
*/  
#define BD_UPD_Local_Path				  699
/*@}*/

/** \defgroup eventCodes Callback System */
/*@{*/
/** Callback function is called with this event when the update started - when not using COM lpData is NULL, when using COM 
iIntEventValue is 0 and wszStringEventValue is NULL*/ 
#define BD_UPD_EVENT_UPD_START					 0	//!fired when it starts checking for updates
/** Callback function is called with this event when update is done - when not using COM lpData is NULL, when using COM 
iIntEventValue is 0 and wszStringEventValue is NULL.*/  
#define BD_UPD_EVENT_UPD_DONE					10 //!fired when update finished
/** Callback function is called with this event when the update failed- when not using COM lpData is NULL, when using COM 
iIntEventValue is 0 and wszStringEventValue is NULL */ 
#define BD_UPD_EVENT_UPD_FAILED				    20	//!fired when update failed
/** Callback function is called with this event when the update failed with a http 403 error - when not using COM lpData is NULL, when using COM 
iIntEventValue is 0 and wszStringEventValue is NULL */ 
#define	BD_UPD_EVENT_UPD_FAILED_WITH403		    21	//!fired when update failed because of HTTP Response Code 403
/** Callback function is called with this event when the update failed with a http 404 error - when not using COM lpData is NULL, when using COM 
iIntEventValue is 0 and wszStringEventValue is NULL */ 
#define BD_UPD_EVENT_UPD_FAILED_WITH404		    22	//!fired when update failed because of HTTP Response Code 404
/** Callback function is called with this event when the update failed because it could not connect to server- when not using COM lpData is NULL, when using COM 
iIntEventValue is 0 and wszStringEventValue is NULL. */ 
#define BD_UPD_EVENT_UPD_FAILED_CANTCONTOSRV	24	//!fired when the update server is unavailable
/** Callback function is called with this event when the update failed with a http 202 message - when not using COM lpData is NULL, when using COM 
iIntEventValue is 0 and wszStringEventValue is NULL. If the callback function returns \ref BD_UPD_RET_Retry after receiving \ref BD_UPD_EVENT_UPD_MSG202 the library will retry to download the file. If the callback function does not return \ref BD_UPD_RET_Retry after receiving a \ref BD_UPD_EVENT_UPD_MSG202, the library will fail with this event.
*/ 
#define	BD_UPD_EVENT_UPD_FAILED_WITH202		    29	//!fired when a 202 response code was received and
/** Callback function is called with this event when no update is available - when not using COM lpData is NULL, when using COM 
iIntEventValue is 0 and wszStringEventValue is NULL.
	This means no update is available for downloading, and no files should be installed - the update files are brought initially local with .upd extension, it may happen that no update has to be downloaded, but there are files to install. 
*/  
#define BD_UPD_EVENT_UPD_NONE					30	//!fired when update finished, but nothing was upgraded
/** Callback function is called with this event when a new file is downloaded - when not using COM lpData is a char * indicating the file name,
when using COM iIntEventValue is 0 and wszStringEventValue is a BSTR indicating the file name*/  
#define BD_UPD_EVENT_UPD_FILE_BEGIN			    40  //!a new file is going to be downloaded
/** Callback function is called with this event when a file was downloaded - when not using COM lpData contains a int * containing the size of the downloaded file,
when using COM iIntEventValue is an int containing the size of the downloaded file, and wszStringEventValue is NULL.*/ 
#define BD_UPD_EVENT_UPD_FILE_END				50  //!size of the file that was downloaded
/** Callback function is called with this event to notify the total amount of the download, which has to be made to make the upgrade -when not using COM lpData is a int * containing the total download size, 
when using COM iIntEventValue is a int containing the total download size and wszStringEventValue is NULL*/ 
#define BD_UPD_EVENT_UPD_TOTAL_UPDATE_SIZE		60  //!whole size of update (all files together)
/** Callback function is called with this event to notify the total amount downloaded so far during the upgrade - when not using COM lpData is a int * containing the total amount downloaded so far,
when using COM iIntEventValue is a int containing the total amount of data downloaded so far, wszStringEventValue is NULL*/ 
#define BD_UPD_EVENT_UPD_DOWNLOADED_BYTES		70  //!size of update downloaded so far(all downloaded files and parts of files, together)
/** Callback function is called with this event when the web server responds with HTTP/1.1 202 Accepted -when not using COM lpData is a char * indicating the file name, when using COM
wszStringEventValue is a BSTR indicating the file name, and iIntEventValue is 0.
	Callback function is called with this event to notify that when trying to download a file it received 202 message. \n
	The 202 message can be used by the web server to handle the cases in which it does not have the requested file in the local cache (document root), thus allowing the client to retry after a period of time (waiting is done inside the callback function), time in which the server downloads the requested file. This message appears only when web server is modified to support HTTP/1.1 202 Accepted as specified before.\n
	The library will continue to try downloading the file as long as:\n
		\li the server does not respond with 202 http status code.
		\li the callback function returns a different value than \ref BD_UPD_RET_Retry.
		
	The library does not have an internal waiting mechanism. Once the callback function returns with \ref BD_UPD_RET_Retry, the library will try immediately to download the same file. This means that the callback function must implement a sleeping mechanism for this event.*/ 
#define BD_UPD_EVENT_UPD_MSG202				    80  //!fired when a 202 HTTP Response Code has been received.
/** Callback function is called with this event when an io timeout occurred when downloading a file - when not using COM lpData is a char * indicating the file name, when using COM
wszStringEventValue is a BSTR indicating the file name, and iIntEventValue is 0.
	If the callback function returns \ref BD_UPD_RET_Retry the library will retry to download the file; any other return value from the callback function will 
	make the library to fail returning BD_UPD_EVENT_UPD_FAILED.\n
*/
#define BD_UPD_EVENT_UPD_IO_TIMEOUT             81 //!fired when a IO Timeout occurred during downloading a file

#define BD_UPD_EVENT_UPD_INVALID_SERVER_RSP		82 //!fired when a invalid server response occurred during downloading a file - if the user wants to retry the user should return BD_UPD_RET_Retry in the callback

/** Callback function is called with this event when a downloaded file is invalid(the content could not be parsed or the md5 is not correct). 
lpData is a wchar_t * on windows and a char * on unices indicating the path to the invalid file  */
#define BD_UPD_EVENT_UPD_INVALID_FILE			83  //!fired when a invalid file is encountered during an update

/** Callback function is called with this event to notify the total number of files which has to be installed - when not using COM lpData is a int * indicating the number of files, when using COM
iIntEventValue is a int indicating the number of files, wszStringEventValue is NULL*/ 


#define BD_UPD_EVENT_UPD_NR_FILES_TO_INSTALL	90  //!int - number of files to be installed even without update

#define BD_UPD_EVENT_UPD_VERSION_AVAILABLE      91  //!int - the update version available. If you return -1 here, the update will be aborted

#define BD_UPD_EVENT_UPD_DOWNLOADINGTORRENT1		100  //!fired when torrent file 1 is being  downloaded
/** When not using COM lpData is a char * indicating the remote location, when using COM
iIntEventValue is 0, wszStringEventValue is a BSTR indicating the remote location.*/ 
#define BD_UPD_EVENT_UPD_DOWNLOADINGTORRENT7		101  //!fired when torrent file 7 is being  downloaded
/** When not using COM lpData is a char * indicating the remote location, when using COM
iIntEventValue is 0, wszStringEventValue is a BSTR indicating the remote location.*/ 
#define BD_UPD_EVENT_UPD_STARTDOWNLOADINGZIP1		102  //!fired when zip1 file starts downloading via P2P
/** When not using COM lpData is a int * indicating the file size, when using COM
iIntEventValue is set to the file size, wszStringEventValue is NULL.*/ 
#define BD_UPD_EVENT_UPD_PROGRESSDOWNLOADINGZIP1	103  //!updates the total progress for the zip1 file downloaded via P2P
/** When not using COM lpData is a int * indicating the size of the file downloaded so far, when using COM
iIntEventValue is set to the size of the file downloaded so far, wszStringEventValue is NULL.*/ 
#define BD_UPD_EVENT_UPD_ENDDOWNLOADINGZIP1			104	 //!fired when zip1 file finishes download via P2P
/** When not using COM lpData is a int * indicating the total file size, when using COM
iIntEventValue is set to the total file size, wszStringEventValue is NULL.*/ 
#define BD_UPD_EVENT_UPD_STARTDOWNLOADINGZIP7		105  //!fired when zip7 file starts downloading via P2P
/** When not using COM lpData is a int * indicating the file size, when using COM
iIntEventValue is set to the file size, wszStringEventValue is NULL.*/ 
#define BD_UPD_EVENT_UPD_PROGRESSDOWNLOADINGZIP7	106  //!updates the total progress for the zip7 file downloaded via P2P
/** When not using COM lpData is a int * indicating the size of the file downloaded so far, when using COM
iIntEventValue is set to the size of the file downloaded so far, wszStringEventValue is NULL.*/ 
#define BD_UPD_EVENT_UPD_ENDDOWNLOADINGZIP7			107  //!fired when zip7 file finishes download via P2P
/** When not using COM lpData is a int * indicating the total file size, when using COM
iIntEventValue is set to the total file size, wszStringEventValue is NULL.*/ 
#define BD_UPD_EVENT_UPD_P2PERROR					108  //!fired by a P2P error
/** When not using COM lpData is a int * indicating the P2P error number, when using COM
iIntEventValue is set to the P2P error number, wszStringEventValue is NULL.*/ 

/** Callback function pointer.
	@param[in] iEvent - the callback event. one of \ref eventCodes
	@param[in] lpData - the callback event associated data
	@param[in] lpCtx - the context specified by BD_UPD_CallbackCtx. this context may be NULL, depending on the needs of the integrator
	
	The return values of this function are evaluated only when iEvent is one of:
	\li \ref BD_UPD_EVENT_UPD_MSG202
	\li \ref BD_UPD_EVENT_UPD_IO_TIMEOUT
	
	The callback function MUST have this prototype.
	For a detalied list of possible events see \ref eventCodes.
	
	The possible event flow might be during a successfully download:
		\li \ref BD_UPD_EVENT_UPD_START - this is the first message received. lpData is NULL and the message is sent just to make the user aware that the update has just started.
		\li \ref BD_UPD_EVENT_UPD_TOTAL_UPDATE_SIZE - this is the message sent to tell the user how big is the update.
lpData will be a pointer to an int containing the total size of the update. (the total size which has to be downloaded).
Note: if no update has to be downloaded this message is never sent, and none of the messages below until \ref BD_UPD_EVENT_UPD_NONE
will not be sent. This does not mean that no update has to be installed. All the files downloaded are downloaded with extension .upd, and
if a previous update downloaded files which were not yet installed the user will be announced that has to perform the installation by receiving
message \ref BD_UPD_EVENT_UPD_NR_FILES_TO_INSTALL - see below.
		\li After this messages the download, if any, starts. During the update downloading the following messages will be sent to the
callback function:
		\li \ref BD_UPD_EVENT_UPD_FILE_BEGIN - this is the message sent when a new file starts to be downloaded. lpData will be a char * 
containing the file name.
		\li \ref BD_UPD_EVENT_UPD_DOWNLOADED_BYTES - this is the message sent when another chunk of a file, or an entire file was downloaded. lpData
will be an int pointer containing the total amount of data downloaded so far.
		\li \ref BD_UPD_EVENT_UPD_FILE_END - this is the message sent when a file was just downloaded. This message make pair with
BD_UPD_EVENT_UPD_FILE_BEGIN , so after BD_UPD_EVENT_UPD_FILE_BEGIN will follow an BD_UPD_EVENT_UPD_FILE_END (but not necessary as the next message)
saying that the file was downloaded complete. The lpData will be a pointer to an int which contains the size of the file just downloaded.
		\li \ref BD_UPD_EVENT_UPD_DONE - this message is sent when the download process completes. This message is sent only if any files were downloaded.
lpData is NULL.
		
		During the download of the files it may appear some of the following messages:
		\li \ref BD_UPD_EVENT_UPD_MSG202 - this message is sent to user to tell that we are currently synchronizing that location,
and that he (she) should retry after a short time again. If the user will return from the callback function \ref BD_UPD_RET_Retry, than the library
will retry to download the file, if any other value is returned by the user callback function, than the update process will be stopped. 
The user may decide to sleep after receiving this message, and to return \ref BD_UPD_RET_Retry to retry to download the file. lpData is a char * containing the name of the file
of which download generated this message.
		\li \ref BD_UPD_EVENT_UPD_IO_TIMEOUT - this message is sent to user when an IO Timeout occurred during downloading a file. The user can respond to
this message returning from the callback function \ref BD_UPD_RET_Retry, if the user wants to retry to download that file,
or can respond returning any other value (different than \ref BD_UPD_RET_Retry) if does not want to retry downloading the file.
lpData is a char * containing the file name of which download generated this message.
		\li \ref BD_UPD_EVENT_UPD_NONE - this message is sent to user when no update has to be downloaded. This does not mean that there are no
files to be installed. If there are files to be installed the user will receive BD_UPD_EVENT_UPD_NR_FILES_TO_INSTALL. lpData is NULL.
		\li \ref BD_UPD_EVENT_UPD_NR_FILES_TO_INSTALL - this message is sent when there are files to be installed. The downloading process will bring locally
the files with extension .upd. Using PerformInstall class function or exported function BDUpdSdkPerformInstall the .upd files will be installed. lpData will 
be a pointer to an int containing the number of files which have to be installed.
		
		During the update process - the normal flow described above may be interrupted by error messages :
		\li \ref BD_UPD_EVENT_UPD_FAILED_CANTCONTOSRV is sent when we could not connect to server. lpData is NULL.
		\li \ref BD_UPD_EVENT_UPD_FAILED_WITH404 is sent when the requested file could not be found on the server. lpData is NULL.
		\li \ref BD_UPD_EVENT_UPD_FAILED_WITH403 is sent when the user does not have permission to see that file. lpData is NULL.
		\li \ref BD_UPD_EVENT_UPD_FAILED_WITH202 is sent when a previous BD_UPD_EVENT_UPD_MSG202 was received by the user, and the user decided not to retry
downloading that file. lpData is NULL.
		\li \ref BD_UPD_EVENT_UPD_FAILED - is sent to announce the user that the update failed, but not because of the errors described above. lpData is NULL.
*/
typedef int (CALLING_CONVENTION_CDECL *BDUPDSDKCALLBACK)(int iEvent, void* lpData, void * lpCtx);

/*@}*/

#if defined __cplusplus
# define API_EXPORT		extern "C"
#else
# define API_EXPORT
#endif

typedef int BDUpdSdkRet;
typedef int BDUpdSdkOpt;

#if defined __cplusplus
/** \defgroup cppAPI C++ API */
/*@{*/

/** BDUpdateServerInterface is an abstract class that exports needed functions. */
class BDUpdateServiceInterface
{
	public:
		/** Used to set runtime options - not thread safe.
		@param[in] Option represents one of \ref optCodes Options.
		@param[in] pOptionValue represents the data needed for that option.
		
		\retval BD_UPD_RET_0 - everything is ok
		\retval BD_UPD_RET_Invalid_Opt - an unknown option was specified
		\retval BD_UPD_RET_Invalid_Param - an invalid option value was specified
		
		This function is used to set options needed for update process. Some of the \ref optCodes are mandatory, others are not.\n
		The \b MANDATORY options are:
		\li \ref BD_UPD_Server ["http://upgrade.bitdefender.com/UpdateLocation" or "upgrade.bitdefender.com:8080"]
		\li \ref BD_UPD_Remote_Location only if \ref BD_UPD_Server does not contain full URL
		\li \ref BD_UPD_Local_Path
		
		Other important options:
		\li \ref BD_UPD_Callback needed to obtain more feedback from the update process
		\li \ref BD_UPD_Proxy and \ref BD_UPD_ProxyAuth for proxy support
		\li \ref BD_UPD_ConnectTimeout and \ref BD_UPD_IOTimeout to handle timeouts
		
		More about options read \ref optCodes.
		*/
		virtual BDUpdSdkRet SetOption(BDUpdSdkOpt Option, const void * pOptionValue) = 0; 
		
		/** Runs the update process <b>without installing</b> the downloaded files - not thread safe.
			\retval BD_UPD_RET_0 - all was ok
			\retval BD_UPD_RET_BadServerName - when the server specified in SetOption() could not be parsed or the server host does not exist
			\retval BD_UPD_RET_BadRemoteLocation - when the remote location could not be parsed
			\retval BD_UPD_RET_BadLocalPath - when the local path could not be accessed.
			\retval BD_UPD_RET_Unknown_Error - check events received through callback function and enable debugging (\ref BD_UPD_Debugging)
		
			This function will be used after all runtime options are set. During the update process the callback function (\ref BD_UPD_Callback) is called for every event specified in \ref eventCodes.
		*/
		virtual BDUpdSdkRet PerformUpdate()                                          = 0;
		
		/** Runs the install process - not thread safe.
			\retval BD_UPD_RET_0 - all was ok
			\retval BD_UPD_RET_InstallFailed - enable debugging (\ref BD_UPD_Debugging)
			
			This function installs all the files that were downloaded during Update Process (PerformUpdate()).
		*/
		virtual BDUpdSdkRet PerformInstall()									     = 0;
		
		/** Stops the update process - thread safe.
			\retval BD_UPD_RET_0 only
			
			This function tries to stop the update process that runs on a different thread.
		*/
		virtual BDUpdSdkRet StopUpdate()											 = 0;
		
		/** Resets all internal runtime options - not thread safe.
			\retval BD_UPD_RET_0 
			\retval BD_UPD_RET_InvalidObject - when reset failed
			
			Use this function if you plan to reuse BDUpdateServiceInterface pointer to update from a different location. All the runtime options must be re-set after this function is called.
		*/
		virtual BDUpdSdkRet ResetAllSettings()									     = 0;

		/*
		 * Virtual destructor
		 */
		virtual ~BDUpdateServiceInterface() { };
};
/*@}*/
#else
typedef void BDUpdateServiceInterface;
#endif


/** \defgroup commonAPI C & C++ Common Functions */
/*@{*/
/** Creates an instance of BDUpdateServiceInterface.
	\retval BDUpdateServiceInterface* - pointer to an object that might be used in C and C++
	\retval NULL - when could not create an object
	
	Use this function to obtain a pointer that can be used with:
	\li \ref cppAPI
	\li \ref cAPI
*/
API_EXPORT BDUpdateServiceInterface * CALLING_CONVENTION_CDECL BDUpdSdkCreate();
/** BDUpdSdkCreate() function pointer */
typedef void * (CALLING_CONVENTION_CDECL *BDUPDSDKCREATE)();

/** Destroys and instance of BDUpdateServiceInterface.
	@param[in] p - an instance created with BDUpdateSdkCreate().
*/
API_EXPORT int CALLING_CONVENTION_CDECL BDUpdSdkDestroy(BDUpdateServiceInterface * p);
/** BDUpdSdkDestroy() function pointer */
typedef int (CALLING_CONVENTION_CDECL *BDUPDSDKDESTROY)(BDUpdateServiceInterface * p);

/*@}*/

/** \defgroup cAPI C API */
/*@{*/

/** Used to set runtime options - not thread safe.
	@param[in] pObj - a pointer obtained with BDUpdSdkCreate()
	@param[in] Option - an option from \ref optCodes
	@param[in] pOptionValue - the value for the option
	
	For more information please read BDUpdateServiceInterface::SetOption() function.
*/
API_EXPORT BDUpdSdkRet CALLING_CONVENTION_CDECL BDUpdSdkSetOption(BDUpdateServiceInterface * pObj,BDUpdSdkOpt Option, const void * pOptionValue);
/** BDUpdSdkSetOption() function pointer */
typedef BDUpdSdkRet (CALLING_CONVENTION_CDECL *BDUPDSDKSETOPTION)(BDUpdateServiceInterface * pObj,BDUpdSdkOpt Option, const void * pOptionValue);

/** Runs the update process <b>without installing</b> the downloaded files - not thread safe.
	@param[in] pObj - a pointer obtained from BDUpdSdkCreate()
	
	For more information please read BDUpdateServiceInterface::PerformUpdate() function.
*/
API_EXPORT BDUpdSdkRet CALLING_CONVENTION_CDECL BDUpdSdkPerformUpdate(BDUpdateServiceInterface * pObj);
/** BDUpdSdkPerformUpdate() function pointer */
typedef BDUpdSdkRet (CALLING_CONVENTION_CDECL *BDUPDSDKPERFORMUPDATE)(BDUpdateServiceInterface * pObj);

/** Runs the install process - not thread safe.
	@param[in] pObj - a pointer obtained from BDUpdSdkCreate()
	
	For more information please read BDUpdateServiceInterface::PerformInstall() function.
*/
API_EXPORT BDUpdSdkRet CALLING_CONVENTION_CDECL BDUpdSdkPerformInstall(BDUpdateServiceInterface * pObj);
/** BDUpdSdkPerformInstall() function pointer */
typedef BDUpdSdkRet (CALLING_CONVENTION_CDECL *BDUPDSDKPERFORMINSTALL)(BDUpdateServiceInterface * pObj);

/** Stops the update process - thread safe.
	@param[in] pObj - a pointer obtained from BDUpdSdkCreate()
	
	For more information please read BDUpdateServiceInterface::StopUpdate() function.
*/
API_EXPORT BDUpdSdkRet CALLING_CONVENTION_CDECL BDUpdSdkStop(BDUpdateServiceInterface * pObj);
/** BDUpdSdkStop() function pointer */
typedef BDUpdSdkRet (CALLING_CONVENTION_CDECL *BDUPDSDKSTOP)(BDUpdateServiceInterface * pObj);

/** Resets all internal runtime options - not thread safe.
	@param[in] pObj - a pointer obtained from BDUpdSdkCreate()
	
	For more information please read BDUpdateServiceInterface::ResetAllSettings() function.
*/
API_EXPORT BDUpdSdkRet CALLING_CONVENTION_CDECL BDUpdSdkResetAllSettings(BDUpdateServiceInterface * pObj);
/** BDUpdSdkResetAllSettings() function pointer */
typedef BDUpdSdkRet (CALLING_CONVENTION_CDECL *BDUPDSDKRESETALLSETTINGS)(BDUpdateServiceInterface * pObj);

/*@}*/

#endif

/**
\mainpage
This documentation presents BitDefender Update SDK.\n

The API consists in \ref cppAPI, \ref cAPI, \ref commonAPI and \ref ComInterface for creating and destroying instances of Update SDK.

Before using an instance of Update SDK one must create it:\n
<b> For C and C++ using exported dll function BDUpdSdkCreate(). </b>\n
\code
#ifdef __cplusplus
\endcode
	One can use \ref cppAPI that exports an abstract (BDUpdateServiceInterface) class or use \ref cAPI exported functions
\code
#else
\endcode
	One can use \ref cAPI that exports functions needed to use an instance of Update SDK
\code
#endif
\endcode

After an instance of Update SDK (BDUpdateServiceInterface) is obtained, one need to use BDUpdSdkSetOption() or BDUpdateServiceInterface::SetOption() to set runtime options such as the URL used to update and the local path where BitDefender engines and signatures reside.\n\n

With all options set, one can call BDUpdSdkPerformUpdate() or BDUpdateServiceInterface::PerformUpdate() to run the update process. During the update process one can obtain detailed information about it by registering a callback function (\ref BDUPDSDKCALLBACK) at the previous step - set options.\n\n

During an update, one can stop the update process by calling BDUpdSdkStop() or BDUpdateServiceInterface::StopUpdate().\n\n

After the update process finished with success (see \ref retCodes), one must call BDUpdSdkPerformInstall() or BDUpdateServiceInterface::PerformInstall() to install the newly downloaded plugins and engines. This step requires that the engines must be unloaded.\n\n

The instance might be reused by calling BDUpdSdkResetAllSettings() or BDUpdateServiceInterface::ResetAllSettings() and re-seting the options.\n\n

In order to destroy an Update SDK instance, one can call BDUpdSdkDestroy() to free memory.\n
<b> For COM Interface you have to obtain a pointer to a IBDUpdateComInterface. </b>
\code
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	HRESULT hres = S_OK;
	IBDUpdateComInterface * pTest;
	hres = ::CoCreateInstance(CLSID_BDUpdateComInterface, NULL, CLSCTX_INPROC_SERVER, IID_IBDUpdateComInterface, (void **)&pTest);
\endcode

After obtaining an instance of the COM object, one need to use \ref IBDUpdateComInterface::SetOptionBSTR and \ref IBDUpdateComInterface::SetOptionInt 
functions to set runtime options such as the URL used to update and the local path where BitDefender engines and signatures reside. \ref IBDUpdateComInterface::SetOptionBSTR
will be used to set runtime options which need a string as the option value and \ref IBDUpdateComInterface::SetOptionInt will be used to set runtime options which
need an int as the option value. (see \ref optCodes)\n

With all options set one can call \ref IBDUpdateComInterface::PerformUpdate to run the update process. During the update process one can obtain detailed information about it by registering a class which implements \ref BDUpdateServiceComLib::_IBDUpdateComInterfaceEvents.
The events will be passed via \ref BDUpdateServiceComLib::_IBDUpdateComInterfaceEvents::ReceiveEvents. (see \ref eventCodes)\n

During an update, one can stop the update process by calling \ref IBDUpdateComInterface::StopUpdate. This must be done from another thread because \ref IBDUpdateComInterface::PerformUpdate will
block until all the update will be brought.\n\n

After the update process finished with success (see \ref retCodes), one must call \ref IBDUpdateComInterface::PerformInstall to install the newly downloaded plugins and engines. This step requires that the engines must be unloaded.\n\n

The instance might be reused by calling \ref IBDUpdateComInterface::ResetAllSettings or BDUpdateServiceInterface::ResetAllSettings() and re-seting the options.\n\n
*/


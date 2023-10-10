#pragma once

#include "oemsdk_error.h"
#include "oemsdk_onaccess.h"
#include "oemsdk_atc.h"
#include "oemsdk_gemma.h"
#include "oemsdk_web.h"
#include "oemsdk_scanamsi.h"
#include "oemsdk_scansp.h"

#define EXPORT_BDOEMSDK __declspec(dllexport)

#define BDOEM_DLL_INTERFACE_VERSION 1

enum bdoem_module {
    bdoem_module_onaccess           = 0, //
    bdoem_module_scansp             = 1,
    bdoem_module_atc                = 2,
    bdoem_module_selfprotect        = 3,
    bdoem_module_enhdci             = 4,
    bdoem_module_ctc                = 5,
    bdoem_module_gemma              = 6,
    bdoem_module_scanamsi           = 7,
    bdoem_module_general            = 8,
    bdoem_module_edr                = 9,
    bdoem_module_update             = 10,
    bdoem_module_ransomware_protect = 11,
    bdoem_module_quarantine         = 12
};

enum bdoem_callback {
    bdoem_cbk_onaccess_on_pre_scan_file     = 0,
    bdoem_cbk_onaccess_on_post_scan_file    = 1,
    bdoem_cbk_onaccess_on_pre_rescan_file   = 2,
    bdoem_cbk_onaccess_on_post_rescan_file  = 3,
    bdoem_cbk_onaccess_on_pre_scan_process  = 4,
    bdoem_cbk_onaccess_on_post_scan_process = 5,

    bdoem_cbk_atc_on_process_notification = 10,
    bdoem_cbk_atc_on_process_detection    = 11,
    bdoem_cbk_atc_on_process_injection    = 12,

    bdoem_cbk_web_on_url                   = 20,
    bdoem_cbk_web_on_request_complete      = 21,
    bdoem_cbk_web_on_message_post_scan     = 22,
    bdoem_cbk_web_on_network_detection     = 23,
    bdoem_cbk_web_on_untrusted_certificate = 24,

    bdoem_cbk_gemma_on_process_notification = 30,
    bdoem_cbk_gemma_on_process_detection    = 31,

    bdoem_cbk_amsi_on_pre_scan_request  = 40,
    bdoem_cbk_amsi_on_post_scan_request = 41,

    bdoem_cbk_scansp_on_ondemand_pre_scan_object   = 50,
    bdoem_cbk_scansp_on_ondemand_post_scan_object  = 51,
    bdoem_cbk_scansp_on_ondemand_password_required = 52,
};

/*
this is the signature of an event notification function which you can register using json_register_notification()
and must unregister using json_unregister_notification when no longer needed
 */
typedef void (*fn_bdoem_on_notification)(bdoem_module module_id, const char* event_json, void* context);

extern "C" {

/*
    Some modules require special steps to execute before first run. You can find more information about these modules
    in the documentation and samples.
*/
EXPORT_BDOEMSDK int bdoem_install(const char* install_conf_json, char** response_json);
EXPORT_BDOEMSDK int bdoem_uninstall(const char* uninstall_conf_json, char** response_json);

/*
first function you must call before using the sdk. You can find more information about what modules are available and how to configure them
in the docs. You can find a model of usage in oemsample project oemsample.json
Release response_json memory bdoem_json_free_response after this function is called
*/
EXPORT_BDOEMSDK int bdoem_lib_init(int interface_version, const char* initial_conf_json, char** response_json);

/*
starts the sdk with the configuration provided on initialization above
after this function ends with success you can start using the sdk
Release response_json memory using bdoem_json_free_response after this function is called
*/
EXPORT_BDOEMSDK int bdoem_lib_start(char** response_json);

EXPORT_BDOEMSDK int bdoem_lib_stop();
EXPORT_BDOEMSDK int bdoem_lib_uninit();

// Send a json-like command to the sdk;
// The commands available are documented in each module header
// NOTE: if you receive a non-nullptr response_json, you must free its memory after you use it by calling bdoem_json_free_response
EXPORT_BDOEMSDK int bdoem_json_send_command(const char* method_name, const char* request_json, char** response_json);
// must be called after you use a non-nullptr response_json
EXPORT_BDOEMSDK int bdoem_json_free_response(char* response_json);

/*
Register to sdk notifications. Call this function only before initializing the library or you will get an error.
*/
EXPORT_BDOEMSDK int bdoem_json_register_notification(fn_bdoem_on_notification notification, void* notification_context);

/*
Set the callbacks you want to implement. Call this function only before initializing the library or you will get an error.
*/
EXPORT_BDOEMSDK int bdoem_set_callback(bdoem_callback cbk_id, void* cbk, void* context);

/*
Retrieves the version embedded into the SDK shared library.
The version is only changed when the shared library itself is updated by the partner. It is not updated during the database update.
*/
EXPORT_BDOEMSDK int bdoem_get_version(int* major_version, int* minor_version, int* revision_number, int* build_number);
}

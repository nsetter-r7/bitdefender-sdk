#pragma once

/*
Json request data
=================
{
    "request_type": string (powershell or office)
    "requestor_pid": int,
    "application_name": string,
    "loader_name": string,
    "threat_name": string
}
*/

#define BDOEM_AMSI_VERDICT_ALLOW 0      // returns allow to windows
#define BDOEM_AMSI_VERDICT_DENY 1       // returns deny to windows
#define BDOEM_AMSI_VERDICT_NO_VERDICT 2 // continue normal flow and let bd handle this case

typedef int (*cbk_bdoem_amsi_on_pre_scan_request)(const char* json, void* buffer, unsigned long long length, void* context);
typedef int (*cbk_bdoem_amsi_on_post_scan_request)(const char* json, void* buffer, unsigned long long length, void* context);

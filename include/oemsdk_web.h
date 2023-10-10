#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _bdoem_web_data bdoem_web_data;
typedef int(__cdecl* bdoem_http_set_custom_block_page)(bdoem_web_data* web_data, const unsigned char* body, int body_size,
                                                       const char* content_type);

typedef struct _bdoem_web_data {
    const char* info_json;

    // by default, bd provides a block page. you can also configure one in initial_config
    // if you need to configure it further(based on specific callback data), call this function
    bdoem_http_set_custom_block_page set_custom_block_page;
} bdoem_web_data;

// =======================================

#define BDOEM_WEB_VERDICT_DISCONNECT 0
#define BDOEM_WEB_VERDICT_INSERT_BLOCK_PAGE_AND_DISCONNECT 1
#define BDOEM_WEB_VERDICT_UNFILTER_CONNECTION 2
#define BDOEM_WEB_VERDICT_NO_VERDICT 3 // continue normal flow and let bd handle this case


#define BDOEM_WEB_UNTRUSTED_CERT_DECISION_ALLOW 0
#define BDOEM_WEB_UNTRUSTED_CERT_DECISION_BLOCK 1

/*
    Received as soon as we can obtain the url

    You can:
    * disconnect by returning BDOEM_WEB_VERDICT_DISCONNECT
    * unfilter this connection by returning BDOEM_WEB_VERDICT_UNFILTER_CONNECTION
    * take no action and let bd handle this case (as if this callback was never called) by returning BDOEM_WEB_VERDICT_NO_VERDICT
*/
typedef int(__cdecl* cbk_bdoem_web_on_url)(bdoem_web_data* web_data, void* context);

/*
    Received as soon as we have fully parsed a http request

    You can:
    * disconnect by returning BDOEM_WEB_VERDICT_DISCONNECT
    * create a custom block page and insert it (or force the usage of a preconfigured one) by returning
   BDOEM_WEB_VERDICT_INSERT_BLOCK_PAGE_AND_DISCONNECT
    * unfilter this connection by returning BDOEM_WEB_VERDICT_UNFILTER_CONNECTION
    * take no action and let bd handle this case (as if this callback was never called) by returning BDOEM_WEB_VERDICT_NO_VERDICT
*/
typedef int(__cdecl* cbk_bdoem_web_on_request_complete)(bdoem_web_data* web_data, const unsigned char* request_body,
                                                        unsigned long long request_body_size, void* context);
/*
    Received after we have scanned a http message

    You can:
    * disconnect by returning BDOEM_WEB_VERDICT_DISCONNECT
    * create a custom block page and insert it (or force the usage of a preconfigured one) by returning
   BDOEM_WEB_VERDICT_INSERT_BLOCK_PAGE_AND_DISCONNECT
    * unfilter this connection by returning BDOEM_WEB_VERDICT_UNFILTER_CONNECTION
    * take no action and let bd handle this case (as if this callback was never called) by returning BDOEM_WEB_VERDICT_NO_VERDICT
*/
typedef int(__cdecl* cbk_bdoem_web_on_message_post_scan)(bdoem_web_data* web_data, const unsigned char* response_body,
                                                         unsigned long long response_body_size, void* context);

/*
    Received as soon as we detected a generic network attack; it can occurr on any protocol

    You can:
    * disconnect by returning BDOEM_WEB_VERDICT_DISCONNECT
    * create a custom block page and insert it (or force the usage of a preconfigured one) by returning
   BDOEM_WEB_VERDICT_INSERT_BLOCK_PAGE_AND_DISCONNECT this will only work for http protocol and only in special cases. If a block page can't
   be inserted, it will just disconnect
    * unfilter this connection by returning BDOEM_WEB_VERDICT_UNFILTER_CONNECTION
    * take no action and let bd handle this case (as if this callback was never called) by returning BDOEM_WEB_VERDICT_NO_VERDICT
*/
typedef int(__cdecl* cbk_bdoem_web_on_network_detection)(bdoem_web_data* web_data, void* context);

typedef int(__cdecl* cbk_bdoem_web_on_untrusted_certificate)(bdoem_web_data* web_data, void* context);

#ifdef __cplusplus
}; // extern "C"
#endif

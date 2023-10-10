#pragma once

#define BDOEM_SCANSP_ONDEMAD_ACTION_NO_ACTION 0 // as if the callback was not called
#define BDOEM_SCANSP_ONDEMAD_ACTION_SKIP 1      // won't scan this file

struct BDOEM_ONDEMAND_DATA {
    const wchar_t* scan_id;
    int object_type; // from scanpi;
    unsigned int depth_level; // relevant only for containers, usually 0

    const wchar_t* object_path;
    const wchar_t* parent_containers; // can be nullptr; only for multi-level containers (depth > 1)
    const wchar_t* inner_object;      // can be nullptr; if container, contains actual object name
    const wchar_t* threat_name;       // always nullptr for pre_scan
};

struct BDOEM_ONDEMAND_PASSWORD_DATA {
    const wchar_t* scan_id;
    const wchar_t* object_path;
    wchar_t* password;
    int* password_length; // in chars, not bytes
};

/*
    Decisional callback; received on every ondemand scanned object, before bd engines scans it.

    You can return
        * BDOEM_SCANSP_ONDEMAD_ACTION_NO_ACTION which acts as if this callback was not called
        * BDOEM_SCANSP_ONDEMAD_ACTION_SKIP which will prevent engines from scanning this file

*/
typedef int (*cbk_bdoem_scansp_on_ondemand_pre_scan_object)(const BDOEM_ONDEMAND_DATA* object_data, void* context);

/*
    Decisional callback; received on every ondemand scanned object, after it was scanned by the engines.
    You can read the action from bd_action callback argument

    You can return
        * BDOEM_SCANSP_ONDEMAD_ACTION_NO_ACTION which acts as if this callback was not called
        * BDOEM_SCANSP_ONDEMAD_ACTION_SKIP which will ignore any engines action and skip this file
*/
typedef int (*cbk_bdoem_scansp_on_ondemand_post_scan_object)(const BDOEM_ONDEMAND_DATA* object_data, int bd_action, void* context);

/*
    Decisional callback; received on every ondemand scanned object which is password protected.
    You can send back the password using the password_buffer and password_buffer_length from password_data
*/
typedef int (*cbk_bdoem_scansp_on_ondemand_password_required)(BDOEM_ONDEMAND_PASSWORD_DATA* password_data, void* context);

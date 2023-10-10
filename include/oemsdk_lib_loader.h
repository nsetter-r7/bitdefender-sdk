#pragma once

#include "oemsdk.h"

namespace oem {

class bdoem_lib_loader {
public:
    inline static const wchar_t* get_dll_name()
    {
        return L"oemsdk";
    }

    using bdoem_install_fn_t                    = int (*)(const char* install_conf_json, char** response_json);
    using bdoem_uninstall_fn_t                  = int (*)(const char* uninstall_conf_json, char** response_json);
    using bdoem_lib_init_fn_t                   = int (*)(int interface_version, const char* initial_conf, char** response_json);
    using bdoem_lib_start_fn_t                  = int (*)(char** response_json);
    using bdoem_lib_stop_fn_t                   = int (*)();
    using bdoem_lib_uninit_fn_t                 = int (*)();
    using bdoem_json_send_command_fn_t          = int (*)(const char* method_name, const char* request_json, char** response_json);
    using bdoem_json_free_response_fn_t         = int (*)(char* response_json);
    using bdoem_json_register_notification_fn_t = int (*)(fn_bdoem_on_notification notification, void* notification_context);
    using bdoem_set_callback_fn_t               = int (*)(bdoem_callback cbk_id, void* cbk, void* context);
    using bdoem_get_version_fn_t                = int (*)(int* major_version, int* minor_version, int* revision_number, int* build_number);

    struct Api {
        bdoem_install_fn_t bdoem_install                                       = nullptr;
        bdoem_uninstall_fn_t bdoem_uninstall                                   = nullptr;
        bdoem_lib_init_fn_t bdoem_lib_init                                     = nullptr;
        bdoem_lib_start_fn_t bdoem_lib_start                                   = nullptr;
        bdoem_lib_stop_fn_t bdoem_lib_stop                                     = nullptr;
        bdoem_lib_uninit_fn_t bdoem_lib_uninit                                 = nullptr;
        bdoem_json_send_command_fn_t bdoem_json_send_command                   = nullptr;
        bdoem_json_free_response_fn_t bdoem_json_free_response                 = nullptr;
        bdoem_json_register_notification_fn_t bdoem_json_register_notification = nullptr;
        bdoem_set_callback_fn_t bdoem_set_callback                             = nullptr;
        bdoem_get_version_fn_t bdoem_get_version                               = nullptr;
    };

    bdoem_lib_loader(const wchar_t* dll_path = nullptr)
    {
        if (dll_path) {
            dll_load(dll_path);
        }
    }

    ~bdoem_lib_loader()
    {
        dll_unload();
    }

    int dll_load(const wchar_t* dllPath)
    {
        int err = ERROR_SUCCESS;

        do {
            _dll_lib_handle = LoadLibrary(dllPath);
            if (_dll_lib_handle == nullptr) {
                err = GetLastError();
                break;
            }

            _api.bdoem_install   = (bdoem_install_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_install");
            _api.bdoem_uninstall = (bdoem_uninstall_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_uninstall");

            _api.bdoem_lib_init   = (bdoem_lib_init_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_lib_init");
            _api.bdoem_lib_start  = (bdoem_lib_start_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_lib_start");
            _api.bdoem_lib_stop   = (bdoem_lib_stop_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_lib_stop");
            _api.bdoem_lib_uninit = (bdoem_lib_uninit_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_lib_uninit");

            _api.bdoem_json_send_command  = (bdoem_json_send_command_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_json_send_command");
            _api.bdoem_json_free_response = (bdoem_json_free_response_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_json_free_response");
            _api.bdoem_json_register_notification =
                (bdoem_json_register_notification_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_json_register_notification");
            _api.bdoem_set_callback = (bdoem_set_callback_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_set_callback");
            _api.bdoem_get_version  = (bdoem_get_version_fn_t)GetProcAddress(_dll_lib_handle, "bdoem_get_version");
            if (!_api.bdoem_lib_init || !_api.bdoem_lib_start || !_api.bdoem_lib_stop || !_api.bdoem_lib_uninit ||
                !_api.bdoem_json_send_command || !_api.bdoem_json_free_response || !_api.bdoem_json_register_notification ||
                !_api.bdoem_set_callback || !_api.bdoem_get_version || !_api.bdoem_install || !_api.bdoem_uninstall) {
                err = ERROR_INVALID_FUNCTION;
                break;
            }
        } while (false);

        if (err != ERROR_SUCCESS) {
            dll_unload();
        }

        return err;
    }

    void dll_unload()
    {
        _api.bdoem_install   = nullptr;
        _api.bdoem_uninstall = nullptr;

        _api.bdoem_lib_init   = nullptr;
        _api.bdoem_lib_start  = nullptr;
        _api.bdoem_lib_stop   = nullptr;
        _api.bdoem_lib_uninit = nullptr;

        _api.bdoem_json_send_command          = nullptr;
        _api.bdoem_json_free_response         = nullptr;
        _api.bdoem_json_register_notification = nullptr;

        _api.bdoem_set_callback = nullptr;
        _api.bdoem_get_version  = nullptr;

        if (_dll_lib_handle != nullptr) {
            FreeLibrary(_dll_lib_handle);
            _dll_lib_handle = nullptr;
        }
    }

    inline bool valid()
    {
        return _dll_lib_handle != nullptr;
    }

    inline Api* api()
    {
        return &_api;
    }

    operator bool()
    {
        return valid();
    }

    operator Api*()
    {
        return api();
    }

    Api* operator->()
    {
        return api();
    }

private:
    HMODULE _dll_lib_handle = nullptr;
    Api _api;
};

} // namespace oem

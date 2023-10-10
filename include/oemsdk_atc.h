#pragma once

#define BDOEM_ATC_EXCLUDE_NONE              0 // continue normal flow and let bd handle this case
#define BDOEM_ATC_EXCLUDE_SINGLE_PROCESS    1 // skip monitoring this process
#define BDOEM_ATC_EXCLUDE_PROCESS_TREE      2 // skip monitoring this process and its descendants

#define BDOEM_ATC_ACTION_NO_ACTION  0 // continue normal flow and let bd handle this case
#define BDOEM_ATC_ACTION_ALLOW      1 // allow the processes (group or injection) to continue running

#define BDOEM_ATC_INJECTION_WINDOWS_HOOK_MODULE     0 // Uses a system-wide hook (with SetWindowshook)
#define BDOEM_ATC_INJECTION_WINDOWS_HOOK_THREAD     1 // Uses a hook on a specific thread (with SetWindowsHook)
#define BDOEM_ATC_INJECTION_WRITE_PROCESS_MEMORY    2 // Uses WriteProcessMemory
#define BDOEM_ATC_INJECTION_MAPVIEWOFSECTION        3 // Uses MapViewOfsection
#define BDOEM_ATC_INJECTION_CREATETHREAD            4 // Creates a remote thread
#define BDOEM_ATC_INJECTION_SETTHREADCONTEXT        5 // Uses SetThreadContext
#define BDOEM_ATC_INJECTION_QUEUEAPC                6 // Uses an APC for injection
#define BDOEM_ATC_INJECTION_INJECTED_IMAGE          8 // One of the following functions was called from outside a known loaded image: GetProcAddress, LoadLibrary, CreateToolhelp32Snapshot
#define BDOEM_ATC_INJECTION_WOW64WIRTEPROCESSMEMORY 9 // Uses Wow64 version of WriteProcessMemory

#define BDOEM_ATC_INJECTION_REFLECTIVE_ASSEMBLY_LOAD            10 // Sent when Reflective assembly load is detected
#define BDOEM_ATC_INJECTION_REFLECTIVE_ASSEMBLY_LOAD_FROM_PATH  11 // A reflective assembly load inject notification where only the assembly path is available

struct BDOEM_ATC_PROCESS_DATA {
    const wchar_t* process_path;
    unsigned long pid;
    unsigned long parent_pid; // 0 if not available
    const wchar_t* command_line;   // nullptr if not available
    const wchar_t* user_sid;
};

struct BDOEM_ATC_PROCESS_DETECTION {
    const wchar_t* process_path;
    unsigned long pid;
    unsigned long internal_id;
    bool process_was_detected;
    bool process_was_first_in_group;
    bool process_was_added_in_group_by_injection;
};

struct BDOEM_ATC_PROCESS_GROUP {
    unsigned long group_id;
    int detected_group_array_size;
    BDOEM_ATC_PROCESS_DETECTION* detected_group_array;
};

struct BDOEM_ATC_PROCESS_INJECTION {
    const wchar_t* attacker_path;
    const wchar_t* victim_path;
    unsigned long attacker_pid;
    unsigned long victim_pid;
    int injection_method; // from BDOEM_ATC_INJECTION_* above
};

/*
    Decisional callback; received on every process creation
    You can:
    1) instruct atc to not monitor this process by returning BDOEM_ATC_EXCLUDE_SINGLE_PROCESS
    2) instruct atc to not monitor this process or any of its descendants by returning BDOEM_ATC_EXCLUDE_PROCESS_TREE
    3) take no action and let bd handle this case (as if this callback was never called) by returning BDOEM_ATC_NO_VERDICT

*/
typedef int (*cbk_bdoem_atc_on_process_notification)(const BDOEM_ATC_PROCESS_DATA* process_data, void* context);

/*
    Decisional callback; received on every atc detection. You can take actions globally regarding how atc will handle this group detection

    You can:
    1) instruct atc to ignore this group detection and take no actions by returning BDOEM_ATC_ACTION_ALLOW
    2) take no action and let bd handle this case depending on the globally configured action you initialized atc with
*/
typedef int (*cbk_bdoem_atc_on_process_detection)(const BDOEM_ATC_PROCESS_GROUP* process_group, void* context);


/*
    Decisional callback; received on every injection found on the system. You can take actions globally regarding how atc will handle this injection

    You can:
    1) instruct atc to ignore this injection and take no actions by returning BDOEM_ATC_ACTION_ALLOW
    2) take no action and let bd handle this case depending on the globally configured action you initialized atc with
*/
typedef int (*cbk_bdoem_atc_on_process_injection)(const BDOEM_ATC_PROCESS_INJECTION* injection, void* context);

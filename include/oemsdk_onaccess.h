#pragma once

#include <windows.h>

// scan_reason
#define SCAN_BOOT_SECTOR 1
#define SCAN_FILE_ON_CREATE 2
#define SCAN_FILE_ON_CLOSE 3

#define BDOEM_ONACCESS_PROCESS_START_SCAN 0
#define BDOEM_ONACCESS_PROCESS_MEMORY_SCAN 1
#define BDOEM_ONACCESS_PROCESS_CMDLINE_BUFFER 2
#define BDOEM_ONACCESS_PROCESS_CMDLINE_EXTRACTED_FILE 3

/*
enum FileSystem_FileFlags {
    FileSystem_FileFlags_Copied_File = 1, ///< Copied File - is set on FileSystem_Operation_NtClose or FileSystem_Notification_NtClose
    FileSystem_FileFlags_Copied_FileSourceNotScanned =
        2, ///< Copied File and source is not scanned - is set on FileSystem_Operation_NtClose or FileSystem_Notification_NtClose
    FileSystem_FileFlags_Stream_Ads = 4,       ///< Stream Ads - is set on post FileSystem_Operation_NtCreateFile or pre
                                               ///< FileSystem_Operation_NtClose, FileSystem_Notification_NtClose
    FileSystem_FileFlags_IntegrityFlagOff = 8, ///
    FileSystem_FileFlags_CreateUserProcess =
        16, ///< file is opened for CreateProcess , available on win 10 in post FileSystem_Operation_NtCreateFile
    FileSystem_FileFlags_MM_Mapped_RW = 32, ///< file was mapped with read/write access , is set on FileSystem_Operation_NtClose
};
*/

struct BDOEM_SCAN_DATA {
    unsigned long scan_reason;          // SCAN_BOOT_SECTOR or SCAN_FILE_ON_CREATE or SCAN_FILE_ON_CLOSE
    unsigned long long scan_attributes; // old gzflt file flags, now in vlflt, need to export them FileSystem_FileFlags commented above
    long long file_size;
    unsigned long thread_priority; // not set when rescanning
    unsigned long page_priority;   // not set when rescanning
    unsigned long process_id;
    unsigned long thread_id;
    unsigned long thread_index;         // internal unique thread id used in onaccess
    unsigned long file_attributes;      // FileSystem_VolumeFlags above
    unsigned long desired_access;       // from winnt.h ex: FILE_EXECUTE
    unsigned short device_name_size;    // set only for SCAN_BOOT_SECTOR
    wchar_t* device_name;               // set only for SCAN_BOOT_SECTOR
    unsigned short mini_transaction_id; // not set when rescanning
};

struct BDOEM_FILTER_HANDLE {
    long long stream_context;
    int scan_id; // unique
};

struct BDOEM_FILE_DATA {
    BDOEM_FILTER_HANDLE handle; // not set when rescanning
    long long file_id;
    long long usn;
    unsigned long device_characteristics;
    unsigned long volume_serial_number;
    const wchar_t* volume_guid;            // not set when rescanning
    unsigned long source_file_name_length; // not set when rescanning
    const wchar_t* source_file_name;       // not set when rescanning
    unsigned long file_name_length;
    const wchar_t* file_name;
};

struct BDOEM_RESCAN_THREAT_INFO {
    int threat_type;
    int initial_status;
    int final_status;
    const wchar_t* threat_name;
    const wchar_t* process_SSID;
    const char* detection_info;
};

struct BDOEM_RESCAN_DATA {
    BDOEM_SCAN_DATA scan_data;
    BDOEM_FILE_DATA file_data;
    BDOEM_RESCAN_THREAT_INFO threat_info;
};

struct BDOEM_BOOT_DATA {
    long long scan_id;          // unique
    long long sector_size;      // size of the buffer to scan
    unsigned char* sector_data; // data buffer pointer
};

// populated after bdoem_onaccess_create_section is called successfully
struct BDOEM_SECTION_HANDLE {
    int status;               // 0 if filter create_section call was successful, error otherwise
    long long section_handle; // used as first argument to MapViewOfFile
    long long file_size;
};

struct BDOEM_ONACCESS_DATA;
// returns ERROR_SUCCESS if a valid section is opened
typedef int (*fn_bdoem_onaccess_create_section)(const BDOEM_ONACCESS_DATA* file_access, BDOEM_SECTION_HANDLE* handle);

struct oem_filter_functions {
    /*
    call this function if you want to scan the file contents using custom engines;
    you'll pass the fileAccess structure and obtain an bdoem_section_handle(second argument)
    inside BDOEM_SECTION_HANDLE structure, you have a SectionHandle member that you will pass to MapViewOfFile;
    ex: MapViewOfFile((HANDLE)section.section_handle, FILE_MAP_READ, 0, 0, 0);
    */
    fn_bdoem_onaccess_create_section bdoem_onaccess_create_section;
};

struct BDOEM_ONACCESS_DATA {
    oem_filter_functions filterFunctions;
    BDOEM_SCAN_DATA scan_data;
    union { // choose which one to used based on ScanData.ScanReason
        BDOEM_FILE_DATA FileData;
        BDOEM_BOOT_DATA BootData;
    };
};

struct BDOEM_ONACCESS_PROCESS_DATA {
    int onaccess_process_scan_type;

    unsigned long process_id;
    unsigned long parent_process_id;
    int is_in_ntfs_transaction;
    const wchar_t* nt_filename;
    const wchar_t* filename;                    // might be nullptr
    const wchar_t* process_sid;                 // might be nullptr
    const wchar_t* process_command_line;        // might be nullptr
    const wchar_t* command_line_extracted_file; // might be nullptr
    const wchar_t* threat_name;                 // might be nullptr
};


#define BDOEM_ONACCESS_VERDICT_ALLOW 0 // returns allow to filter driver
#define BDOEM_ONACCESS_VERDICT_DENY 1 // returns deny to filter driver
#define BDOEM_ONACCESS_VERDICT_DENY_NO_RESCAN 2 // returns deny to filter driver and prevents rescanning
#define BDOEM_ONACCESS_VERDICT_NO_VERDICT 3 // continue normal flow and let bd handle this case
#define BDOEM_ONACCESS_VERDICT_ALLOW_CACHE 4 // returns allow to filter driver; the filter driver will cache the result, meaning you will not get a callback next time this file is accessed

/*
    Decisional callback; received on every file access, before bd engines scans this file.

    You can:

    1. bypass any bd scanning by returning BDOEM_ONACCESS_VERDICT_ALLOW (example: custom whitelist/cache/exclusions)
    2. block the file access by returning BDOEM_ONACCESS_VERDICT_DENY (custom blacklist) - we will also trigger rescan callbacks. Read more
   about them below or in the docs.
    3. block the file access by returning BBDOEM_ONACCESS_VERDICT_DENY_NO_RESCAN - we will just block the file and not send any rescan
   callbacks
    4. or scan the content of the file with custom engines and return the appropriate response
        To read the file contents you need to call fn_bdoem_onaccess_create_section. You have a pointer to this function in
        fileAccess->filterFunction.bdoem_onaccess_create_section. You will receveid a section handle which can be used to
        map this file in memory (using MapViewOfFile). There is no need to close the section for this file, we handle it internally

    NOTE: if you return BDOEM_ONACCESS_VERDICT_NO_VERDICT it's as if this callback was not called
*/
typedef int (*cbk_bdoem_onaccess_on_pre_scan_file)(const BDOEM_ONACCESS_DATA* fileAccess, void* context);

/*
    Decisional callback; received on every file access if it was not priorly skipped/blocked by you or internal bd mechanisms.
    The bd engines scanned the files. You can read this verdict from bdVerdict callback argument

    This may be useful if you want to ignore the bd verdict.
    For example bd may detect malware and bdVerdict is BDOEM_ONACCESS_VERDICT_DENY. However you decide it's false
   positive and don't want to block, but allow instead.
*/
typedef int (*cbk_bdoem_onaccess_on_post_scan_file)(const BDOEM_ONACCESS_DATA* file_access, void* context, int bd_verdict);

/*
    Received on every file access that had a detection and onaccess has actions to set configured(ex: disinfect, move to quarantine)
    The reason is that you probably want to execute these actions on a separate thread to not block driver decisional callback since they
   might be time consuming. The verdict send to driver in the decisional callback is Deny (and is cached)

    Here you can:
    1. return BDOEM_ONACCESS_VERDICT_ALLOW to bypass any bd rescanning
        => internally we will invalidate the driver cache for that file
    2. return BDOEM_ONACCESS_VERDICT_DENY to keep blocking the file and prevent bd from applying any actions from config
    3. or return BDOEM_ONACCESS_VERDICT_NO_VERDICT to let bd handle it (as if this callback was not called)
*/
typedef int (*cbk_bdoem_onaccess_on_pre_rescan_file)(const BDOEM_RESCAN_DATA* rescan_data, void* context);

/*
    Same as cbk_bdoem_onaccess_on_pre_rescan_file, but bd rescanned the file and applied the actions on it(ex: file might be clean after
   disinfection now, or it might have been deleted)
*/
typedef int (*cbk_bdoem_onaccess_on_post_rescan_file)(const BDOEM_RESCAN_DATA* rescan_data, void* context, int bd_verdict);


/*
    Decisional callback; received on every process start, before bd engines scans this file.

    You can:

    1. bypass any bd scanning by returning BDOEM_ONACCESS_VERDICT_ALLOW (example: custom whitelist/cache/exclusions)
    2. block the process start by returning BDOEM_ONACCESS_VERDICT_DENY (custom blacklist) - we will also trigger rescan callbacks. Read
   more about them below or in the docs.
    3. block the process start by returning BBDOEM_ONACCESS_VERDICT_DENY_NO_RESCAN - we will just block the process and not send any rescan
   callbacks

    NOTE: if you return BDOEM_ONACCESS_VERDICT_NO_VERDICT it's as if this callback was not called
*/
typedef int (*cbk_bdoem_onaccess_on_pre_scan_process)(const BDOEM_ONACCESS_PROCESS_DATA*, void* context);

/*
    Decisional callback; received on every process start if it was not priorly skipped/blocked by you or internal bd mechanisms.
    The bd engines scanned the files. You can read this verdict from bd_verdict callback argument

    This may be useful if you want to ignore the bd verdict.
    For example bd may detect malware and bd_verdict is BDOEM_ONACCESS_VERDICT_DENY. However you decide it's false
   positive and don't want to block, but allow instead.
*/
typedef int (*cbk_bdoem_onaccess_on_post_scan_process)(const BDOEM_ONACCESS_PROCESS_DATA*, void* context, int bd_verdict);
#pragma once

#define BDOEM_GEMMA_EXCLUDE_PROCESS 0 // skip monitoring this process
#define BDOEM_GEMMA_EXCLUDE_NONE 1    // continue normal flow and let bd handle this case

#define BDOEM_GEMMA_DETECTION_INGORE_DETECTION 0       // gemma ignores the detection and does nothing (continues execution)
#define BDOEM_GEMMA_DETECTION_KILL_PROCESS 1           // kill the process that generated this detection
#define BDOEM_GEMMA_DETECTION_BLOCK_DETECTION 2        // Block the action that triggered the detection, while keeping the process alive
                                                       // Most of the time this action behaves exactly as kill, as it cannot block the action in other ways
#define BDOEM_GEMMA_DETECTION_USE_RECOMMENDED_ACTION 3 // let gemma handle the case(recomended_response from BDOEM_GEMMA_PROCESS_DETECTION)

struct BDOEM_GEMMA_PROCESS_DATA {
    const wchar_t* process_path;
    unsigned long pid;
    unsigned long parent_pid;    // 0 if not available
    const wchar_t* command_line; // nullptr if not available
    const wchar_t* user_sid;
};

struct BDOEM_GEMMA_PROCESS_DETECTION {
    unsigned long pid;
    unsigned long parent_pid; // 0 if not available
    const wchar_t* process_path;
    const wchar_t* user_sid;
    int kernel_detection;
    int gemma_detection_id;
    const wchar_t* detection_name;
    int recomended_response; // from BDOEM_GEMMA_DETECTION_*
};

/*
    Decisional callback; received on every process creation for apps that are by default monitored by gemma.
    You can return any value from BDOEM_GEMMA_EXCLUDE_*
*/
typedef int (*cbk_bdoem_gemma_on_process_notification)(const BDOEM_GEMMA_PROCESS_DATA* process_data, void* context);


/*
    Decisional callback; received on every process detection.
    You can return any value from BDOEM_GEMMA_DETECTION_*
*/
typedef int (*cbk_bdoem_gemma_on_process_detection)(const BDOEM_GEMMA_PROCESS_DETECTION* process_detection, void* context);

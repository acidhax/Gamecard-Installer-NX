#ifndef _NS_H_
#define _NS_H_

#include <stdint.h>
#include <stdbool.h>
#include <switch.h>


typedef enum
{
    NsApplicationRecordType_Installed       = 0x3,
    NsApplicationRecordType_GamecardMissing = 0x5,
    NsApplicationRecordType_Archived        = 0xB,
} NsApplicationRecordType;


//
bool init_ns(void);

//
void exit_ns(void);

// returns the total size of the sd card.
size_t ns_get_storage_total_size(NcmStorageId storage_id);

// returns the free space on the sd card.
size_t ns_get_storage_free_space(NcmStorageId storage_id);

// store data found to out.
// make sure to set the size of the out large enough.
// returns the total stored.
int32_t ns_list_app_record(NsApplicationRecord *out, int32_t count, int32_t offset);

//
int32_t ns_list_app_cnmt_status(NsApplicationContentMetaStatus *out, int32_t count, uint64_t app_id);

// store data to out.
size_t ns_get_app_control_data(NsApplicationControlData *out, uint64_t app_id);

//
int32_t ns_get_app_delivery_info(NsApplicationDeliveryInfo *out, int32_t count, uint64_t app_id, uint32_t attr);

//
bool ns_check_app_delivery_info(const NsApplicationDeliveryInfo *info);

//
int32_t ns_compare_app_delivery_info(const NsApplicationDeliveryInfo *info0, const NsApplicationDeliveryInfo *info1);

//
bool ns_check_if_can_deliver_app_info(NsApplicationDeliveryInfo *info0, int32_t count0, NsApplicationDeliveryInfo *info1);

//
int32_t ns_list_content_meta_key(NcmContentMetaKey *meta, NsApplicationDeliveryInfo *info);


// seems to always return 4.
uint32_t ns_count_application_record(uint64_t app_id);

//
Result ns_delete_application_completely(uint64_t app_id);


// push an application record.
Result ns_push_application_record(uint64_t app_id, void *cnmt_storage_records, size_t data_size);

// delete an application record using the app_id.
Result ns_delete_application_record(uint64_t app_id);

// count the amount of content already installed.
uint32_t ns_count_application_content_meta(uint64_t app_id);

// write all existing content to void *out_buf. Call this after count_out > 1.
Result ns_list_application_record_content_meta(uint64_t offset, uint64_t app_id, void *out_buf, size_t out_buf_size, uint32_t count);

#endif
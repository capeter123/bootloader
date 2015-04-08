#pragma once


#include <stdint.h>
#include <stdlib.h>


typedef enum {
    CAN_OK = 0,
    CAN_ERROR
} can_error_t;


typedef enum {
    CAN_125KBAUD = 0,
    CAN_250KBAUD = 1,
    CAN_500KBAUD = 2,
    CAN_1MBAUD = 3
} can_speed_t;


/* UAVCAN message formats */
typedef enum {
    SERVICE_RESPONSE = 0,
    SERVICE_REQUEST = 1,
    MESSAGE_BROADCAST = 2,
    MESSAGE_UNICAST = 3
} uavcan_transfertype_t;

typedef struct {
    uint8_t transfer_id;
    uint8_t last_frame;
    uint8_t frame_index;
    uint8_t source_node_id;
    uavcan_transfertype_t transfer_type;
    uint16_t data_type_id;
} __attribute__((packed)) uavcan_frame_id_t;

typedef struct {
    uint32_t uptime_sec;
    uint8_t status_code;
    uint16_t vendor_specific_status_code;
} __attribute__((packed)) uavcan_nodestatus_t;

#define UAVCAN_NODESTATUS_DTID 550u
#define UAVCAN_NODESTATUS_PUBLICATION_CYCLES (72000000u / 2u)
#define UAVCAN_NODESTATUS_STATUS_OK 0u
#define UAVCAN_NODESTATUS_STATUS_INITIALIZING 1u
#define UAVCAN_NODESTATUS_STATUS_WARNING 2u
#define UAVCAN_NODESTATUS_STATUS_CRITICAL 3u


typedef struct {
    uint8_t major;
    uint8_t minor;
    uint8_t optional_field_mask;
    uint32_t vcs_commit;
    uint64_t image_crc;
} __attribute__((packed)) uavcan_softwareversion_t;

typedef struct {
    uint8_t major;
    uint8_t minor;
    uint8_t unique_id[16];
    uint8_t certificate_of_authenticity_length;
    uint8_t certificate_of_authenticity[255];
} __attribute__((packed)) uavcan_hardwareversion_t;

typedef struct {
    uint8_t nodestatus[6];

    uavcan_softwareversion_t software_version;
    uavcan_hardwareversion_t hardware_version;

    uint8_t name[80];
    uint8_t name_length;
} __attribute__((packed)) uavcan_getnodeinfo_response_t;

#define UAVCAN_GETNODEINFO_DTID 551u
#define UAVCAN_GETNODEINFO_CRC 0x14BBu


typedef struct {
    uint64_t short_unique_id;
    uint8_t node_id;
} __attribute__((packed)) uavcan_dynamicnodeidallocation_t;

#define UAVCAN_DYNAMICNODEIDALLOCATION_DTID 559u


typedef struct {
    uint8_t level;
    uint8_t message[2];
} __attribute__((packed)) uavcan_logmessage_t;

#define UAVCAN_LOGMESSAGE_DTID 1023u
#define UAVCAN_LOGMESSAGE_LEVEL_DEBUG 0u
#define UAVCAN_LOGMESSAGE_LEVEL_INFO 1u
#define UAVCAN_LOGMESSAGE_LEVEL_WARNING 2u
#define UAVCAN_LOGMESSAGE_LEVEL_ERROR 3u
#define UAVCAN_LOGMESSAGE_SOURCE_0 'B'
#define UAVCAN_LOGMESSAGE_SOURCE_1 'O'
#define UAVCAN_LOGMESSAGE_SOURCE_2 'O'
#define UAVCAN_LOGMESSAGE_SOURCE_3 'T'

#define UAVCAN_LOGMESSAGE_STAGE_INIT 'I'
#define UAVCAN_LOGMESSAGE_STAGE_GET_INFO 'G'
#define UAVCAN_LOGMESSAGE_STAGE_ERASE 'E'
#define UAVCAN_LOGMESSAGE_STAGE_READ 'R'
#define UAVCAN_LOGMESSAGE_STAGE_PROGRAM 'P'
#define UAVCAN_LOGMESSAGE_STAGE_VALIDATE 'V'
#define UAVCAN_LOGMESSAGE_STAGE_FINALIZE 'F'
#define UAVCAN_LOGMESSAGE_RESULT_START 's'
#define UAVCAN_LOGMESSAGE_RESULT_FAIL 'f'
#define UAVCAN_LOGMESSAGE_RESULT_OK 'o'


typedef struct {
    uint8_t source_node_id;
    uint8_t path[200];
    uint8_t path_length;
} __attribute__((packed)) uavcan_beginfirmwareupdate_request_t;

typedef struct {
    uint8_t error;
} __attribute__((packed)) uavcan_beginfirmwareupdate_response_t;

#define UAVCAN_BEGINFIRMWAREUPDATE_DTID 580u
#define UAVCAN_BEGINFIRMWAREUPDATE_CRC 0x729Eu
#define UAVCAN_BEGINFIRMWAREUPDATE_ERROR_OK 0u
#define UAVCAN_BEGINFIRMWAREUPDATE_ERROR_INVALID_MODE 1u
#define UAVCAN_BEGINFIRMWAREUPDATE_ERROR_IN_PROGRESS 2u
#define UAVCAN_BEGINFIRMWAREUPDATE_ERROR_UNKNOWN 255u


typedef struct {
    uint8_t path[200];
    uint8_t path_length;
} __attribute__((packed)) uavcan_getinfo_request_t;

typedef struct {
    uint64_t crc64;
    uint32_t size;
    uint16_t error;
    uint8_t entry_type;
} __attribute__((packed)) uavcan_getinfo_response_t;

#define UAVCAN_GETINFO_DTID 585u
#define UAVCAN_GETINFO_CRC 0x37A0u
#define UAVCAN_GETINFO_ENTRY_TYPE_FLAG_FILE 0x01u
#define UAVCAN_GETINFO_ENTRY_TYPE_FLAG_DIRECTORY 0x02u
#define UAVCAN_GETINFO_ENTRY_TYPE_FLAG_SYMLINK 0x04u
#define UAVCAN_GETINFO_ENTRY_TYPE_FLAG_READABLE 0x08u
#define UAVCAN_GETINFO_ENTRY_TYPE_FLAG_WRITEABLE 0x10u


typedef struct {
    uint32_t offset;
    uint8_t path[200];
    uint8_t path_length;
} __attribute__((packed)) uavcan_read_request_t;

typedef struct {
    uint16_t error;
    uint8_t data[250];
    uint8_t data_length;
} __attribute__((packed)) uavcan_read_response_t;

#define UAVCAN_READ_DTID 588u
#define UAVCAN_READ_CRC 0x2921u

#define UAVCAN_FILE_ERROR_OK 0u
/* Left the others out for now because we don't really care why it failed */


void uavcan_tx(
    const uavcan_frame_id_t *message_id,
    size_t length,
    const uint8_t *message,
    uint8_t mailbox
);
uint8_t uavcan_rx(
    uavcan_frame_id_t *out_message_id,
    size_t *out_length,
    uint8_t *out_message,
    uint8_t fifo
);
can_error_t uavcan_init(can_speed_t speed);
can_error_t uavcan_autobaud(void);
size_t uavcan_pack_nodestatus(
    uint8_t *data,
    const uavcan_nodestatus_t *payload
);
size_t uavcan_pack_dynamicnodeidallocation(
    uint8_t *data,
    const uavcan_dynamicnodeidallocation_t *payload
);
void uavcan_unpack_dynamicnodeidallocation(
    uavcan_dynamicnodeidallocation_t *payload,
    const uint8_t *data
);
size_t uavcan_pack_logmessage(
    uint8_t *data,
    const uavcan_logmessage_t *payload
);
uint32_t uavcan_make_frame_id(const uavcan_frame_id_t *metadata);
void uavcan_parse_frame_id(uavcan_frame_id_t *metadata, uint32_t frame_id);
void uavcan_tx_nodestatus(
    uint8_t node_id,
    uint32_t uptime_sec,
    uint8_t status_code
);
void uavcan_tx_getnodeinfo_response(
    uint8_t node_id,
    uavcan_getnodeinfo_response_t *response,
    uint8_t dest_node_id,
    uint8_t transfer_id
);
can_error_t uavcan_rx_beginfirmwareupdate_request(
    uint8_t node_id,
    uavcan_beginfirmwareupdate_request_t *request,
    uavcan_frame_id_t *out_message_id
);
void uavcan_tx_read_request(
    uint8_t node_id,
    const uavcan_read_request_t *request,
    uint8_t dest_node_id,
    uint8_t transfer_id
);
can_error_t uavcan_rx_read_response(
    uint8_t node_id,
    uavcan_read_response_t *response,
    uint8_t dest_node_id,
    uint8_t transfer_id,
    uint32_t timeout_ticks
);
void uavcan_tx_getinfo_request(
    uint8_t node_id,
    const uavcan_getinfo_request_t *request,
    uint8_t dest_node_id,
    uint8_t transfer_id
);
can_error_t uavcan_rx_getinfo_response(
    uint8_t node_id,
    uavcan_getinfo_response_t *response,
    uint8_t dest_node_id,
    uint8_t transfer_id,
    uint32_t timeout_ticks
);

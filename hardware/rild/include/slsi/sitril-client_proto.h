/*
 * Copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

/*
    RIL - RIL Client protocol
*/
#ifndef _RILC_PROTO_H
#define _RILC_PROTO_H

/*
    Defines
*/
#define RILC_SOCKET_NAME               "RIL-CLIENT"
#define RILC_TRANSACTION_NONE           0xFFFFFFFF
#define RILC_REQUEST_HEADER_SIZE        sizeof(rilc_request_t)
#define RILC_RESPONSE_HEADER_SIZE       sizeof(rilc_response_t)
#define RILC_MAX_RESPONSE_PAYLOAD_SIZE  ((1024*64)+16)        // 64K+RCM Header(16 byte)

/*
    Structures
*/
typedef struct _rilc_request {
    unsigned char   channel;
    unsigned int transaction;
    unsigned int msgId;
    unsigned int length;
    unsigned char data[0];
} __packed rilc_request_t;

typedef struct _rilc_response {
    unsigned char channel;
    unsigned int transaction;
    unsigned int msgId;
    unsigned int status;
    unsigned int length;
    unsigned char data[0];
} __packed rilc_response_t;

#endif   //_RILC_PROTO_H

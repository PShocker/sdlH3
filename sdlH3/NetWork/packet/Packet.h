#pragma once
#include <cstdint>

enum PACKET_TYPE {
  PACKET_ASK_HOST_RESPONSE = 8,
};

#pragma pack(push, 1)
struct NetworkAskHostRequest {
    // 场景id
    uint32_t scnId;
};
#pragma pack(pop)

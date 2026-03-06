#pragma once
#include <cstdint>

enum PACKET_TYPE {
  PACKET_HOST_REQUEST = 8,
};

#pragma pack(push, 1)
struct NetworkHostRequest {
  // 场景id
  uint32_t scene;
};
#pragma pack(pop)

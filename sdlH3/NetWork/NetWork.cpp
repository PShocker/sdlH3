#include "NetWork/NetWork.h"
#include <uv.h>

void NetWork::init() {
   auto loop = uv_default_loop();
      // 1. 创建UDP句柄
    uv_udp_t node = {};
    uv_udp_init(loop, &node);
    
    // 2. 绑定端口 - 这一步让它可以接收
    struct sockaddr_in local;
    uv_ip4_addr("0.0.0.0", 8888, &local);
    uv_udp_bind(&node, (const struct sockaddr*)&local, 0);
}
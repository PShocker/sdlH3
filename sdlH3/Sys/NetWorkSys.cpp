#include "NetWorkSys.h"
#include "Global/Global.h"
#include "HeroSys.h"
#include "NetWork/MushRoom.h"
#include "NetWork/NetWork.h"
#include "World/World.h"
#include <cstdlib>
#include <shared_mutex>

void NetWorkSys::init() {
  // recvHandler[]=
  recvHandler[NETWORK_EVENT_HERO_MOVE] = HeroSys::recvHeroMove;
}

void NetWorkSys::queuePacket(uint32_t ip, uint16_t port, NetworkPacket *packet) {
  std::unique_lock lock(NetWork::send_mutex); // 独占锁，写时互斥
  auto key = std::make_pair(ip, port);
  auto value = std::make_pair(key, packet);
  NetWork::sendVector.push_back(value);
}

void NetWorkSys::exitScene() {

}

void NetWorkSys::run() {
  {
    std::shared_lock lock(NetWork::send_mutex); // 读锁
    if (!NetWork::sendVector.empty()) {
      uv_async_send(&NetWork::async_handle);
    }
  }
  {
    std::shared_lock lock(NetWork::recv_mutex); // 读锁
    for (auto packet : NetWork::recvVector) {
      auto type = packet->type;
      recvHandler[type](packet);
      free(packet);
    }
  }
}
#include "NetWork/NetClient.h"
#include "NetWork/NetWork.h"
#include "NetWork/protocol/Protocol.h"
#include "protocol/Client.h"
#include "protocol/Protocol.h"

template <typename CreateFunc, typename... Args>
static void sendClientPacket(NetPayload type, CreateFunc func, Args &&...args) {
  auto payload = func(NetWork::builder, std::forward<Args>(args)...);
  auto packet = CreateNetPacket(NetWork::builder, type, payload.Union());
  NetWork::builder.Finish(packet);
  NetWork::sendUDP(NetWork::builder.GetBufferPointer(),
                   NetWork::builder.GetSize(), NetWork::host_ip,
                   NetWork::host_port);

  NetWork::builder.Clear();
}

void NetClient::sendHeartBeat() {
  static uint64_t last = 0;
  uint64_t now = static_cast<uint64_t>(time(nullptr));
  if (now - last < NetWork::heartbeat_interval) {
    return;
  }
  last = now;
  sendClientPacket(NetPayload_ClientHeartbeat, CreateClientHeartbeat, now);
  return;
}

void NetClient::sendInScene(uint32_t scene) {
  sendClientPacket(NetPayload_ClientInScene, CreateClientInScene, scene);
  return;
}

void NetClient::sendHeroMove(uint8_t por, uint8_t level, uint8_t x, uint8_t y) {
  if (NetWork::sceneHost[0] != NetWork::cId) {
    return;
  }
  sendClientPacket(NetPayload_ClientHeroMove, CreateClientHeroMove, por, level,
                   x, y);
  return;
}

void NetClient::sendHeroGoal(uint8_t por, uint8_t type, uint8_t level,
                             uint8_t x, uint8_t y) {
  if (NetWork::sceneHost[0] != NetWork::cId) {
    return;
  }
  sendClientPacket(NetPayload_ClientHeroGoal, CreateClientHeroGoal, por, type,
                   level, x, y);
  return;
}

void NetClient::sendHeroRecruit(uint8_t por, uint8_t level, uint8_t x,
                                uint8_t y) {
  if (NetWork::sceneHost[0] != NetWork::cId) {
    return;
  }
  sendClientPacket(NetPayload_ClientHeroRecruit, CreateClientHeroRecruit, por,
                   level, x, y);
  return;
}

void NetClient::sendHeroDismiss(uint8_t por) {
  if (NetWork::sceneHost[0] != NetWork::cId) {
    return;
  }
  sendClientPacket(NetPayload_ClientHeroDismiss, CreateClientHeroDismiss, por);
  return;
}

void NetClient::sendHeroTeleport(uint8_t por, uint8_t level, uint8_t x,
                                 uint8_t y) {
  if (NetWork::sceneHost[0] != NetWork::cId) {
    return;
  }
  sendClientPacket(NetPayload_ClientHeroTeleport, CreateClientHeroTeleport, por,
                   level, x, y);
  return;
}
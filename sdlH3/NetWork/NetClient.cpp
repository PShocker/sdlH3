#include "NetWork/NetClient.h"
#include "NetWork/NetWork.h"
#include "NetWork/protocol/Protocol.h"
#include "protocol/Client.h"
#include "protocol/Protocol.h"

void NetClient::sendLogin() {
  uint64_t now = static_cast<uint64_t>(time(nullptr));
  // 3. 创建Heartbeat表
  auto payload = CreateClientLogin(NetWork::builder, now);
  NetWork::sendPacket(payload, NetPayload_ClientLogin, NetWork::host_ip,
                      NetWork::host_port);
  return;
}

void NetClient::sendInScene(uint32_t scene) {
  // 3. 创建Heartbeat表
  auto payload = CreateClientInScene(NetWork::builder, scene);
  NetWork::sendPacket(payload, NetPayload_ClientInScene, NetWork::host_ip,
                      NetWork::host_port);
  return;
}

void NetClient::sendHeroMove(uint8_t por, uint8_t x, uint8_t y) {
  // 3. 创建Heartbeat表
  auto payload = CreateClientHeroMove(NetWork::builder, por, x, y);
  NetWork::sendPacket(payload, NetPayload_ClientHeroMove, NetWork::host_ip,
                      NetWork::host_port);
  return;
}
#include "NetWork/NetServer.h"
#include "Global/Global.h"
#include "NetEvent.h"
#include "NetWork.h"
#include "NetWork/NetClient.h"
#include "NetWork/NetWork.h"
#include "NetWork/protocol/Protocol.h"
#include "protocol/Protocol.h"
#include "protocol/Server.h"
#include <cstdint>
#include <vector>

template <typename CreateFunc, typename... Args>
static void sendServerPacket(uint64_t cId, NetPayload type, CreateFunc func,
                             Args &&...args) {
  auto payload = func(NetWork::builder, std::forward<Args>(args)...);
  auto packet = CreateNetPacket(NetWork::builder, type, payload.Union());
  NetWork::builder.Finish(packet);
  NetWork::sendUDP(NetWork::builder.GetBufferPointer(),
                   NetWork::builder.GetSize(), cId);
  NetWork::builder.Clear();
}

template <typename CreateFunc, typename... Args>
static void sendServerScenePacket(uint64_t cId, NetPayload type,
                                  CreateFunc func, Args &&...args) {
  auto payload = func(NetWork::builder, std::forward<Args>(args)...);
  auto packet = CreateNetPacket(NetWork::builder, type, payload.Union());
  NetWork::builder.Finish(packet);
  auto clients = NetWork::sceneClients[0];
  clients.erase(cId);
  for (auto otherId : clients) {
    NetWork::sendUDP(NetWork::builder.GetBufferPointer(),
                     NetWork::builder.GetSize(), otherId);
  }
  NetWork::builder.Clear();
}

void NetServer::sendInScene(uint64_t cId, uint32_t seed, uint32_t scene_id,
                            uint64_t scene_host) {
  sendServerPacket(cId, NetPayload_ServerInScene, CreateServerInScene, seed,
                   scene_host, scene_id, cId);
  return;
}

void NetServer::sendHeroMove(uint64_t cId, uint8_t por, uint8_t level,
                             uint8_t x, uint8_t y) {
  sendServerScenePacket(cId, NetPayload_ServerHeroMove, CreateServerHeroMove,
                        por, level, x, y);
  return;
}

void NetServer::sendHeroGoal(uint64_t cId, uint8_t por, uint8_t type,
                             uint8_t level, uint8_t x, uint8_t y) {
  sendServerScenePacket(cId, NetPayload_ServerHeroGoal, CreateServerHeroGoal,
                        por, type, level, x, y);
  return;
}

void NetServer::sendHeroRecruit(uint64_t cId, uint8_t por, uint8_t level,
                                uint8_t x, uint8_t y) {
  sendServerScenePacket(cId, NetPayload_ServerHeroRecruit,
                        CreateServerHeroRecruit, por, level, x, y);
  return;
}

void NetServer::sendHeroTeleport(uint64_t cId, uint8_t por, uint8_t level,
                                 uint8_t x, uint8_t y) {
  sendServerScenePacket(cId, NetPayload_ServerHeroTeleport,
                        CreateServerHeroTeleport, por, level, x, y);
  return;
}

void NetServer::sendOutScene(uint64_t cId) {
  sendServerScenePacket(cId, NetPayload_ServerOutScene, CreateServerOutScene,
                        cId);
  return;
}

void NetServer::sendEndTurn(uint64_t cId) {
  sendServerScenePacket(cId, NetPayload_ServerOutScene, CreateServerOutScene,
                        cId);
  return;
}

void NetServer::checkHeartBeat() {
  static uint64_t last = 0;
  uint64_t now = static_cast<uint64_t>(time(nullptr));
  if (now - last < NetWork::heartbeat_interval * 3) {
    return;
  }
  last = now;
  std::vector<uint64_t> to_remove;
  for (const auto &[key, client] : NetWork::clients) {
    auto duration = now - client.heartbeat;
    if (duration >= NetWork::heartbeat_interval * 3) {
      to_remove.push_back(key);
    }
  }
  for (auto key : to_remove) {
    auto &client = NetWork::clients[key];
    sendOutScene(client.id);
    NetWork::clients.erase(client.id);
  }
}
void NetServer::dispatchPacket(uint64_t cId, const NetPacket *packet) {
  // 4. 通过union的type判断具体类型
  switch (packet->payload_type()) {
  case NetPayload_ClientHeartbeat: {
    // 从union中获取NetHeartbeat
    auto payload = packet->payload_as_ClientHeartbeat();
    auto time = payload->client_time();
    NetWork::clients[cId].heartbeat = time;
    break;
  }
  case NetPayload_ClientInScene: {
    auto payload = packet->payload_as_ClientInScene();
    auto scene = payload->scene_id();
    NetWork::sceneClients[scene].insert(cId);
    uint64_t scene_host = cId;
    if (NetWork::sceneHost.contains(scene)) {
      scene_host = NetWork::sceneHost.at(scene);
    } else {
      NetWork::sceneHost[scene] = cId;
    }
    NetServer::sendInScene(cId, Global::seed, scene, scene_host);
    break;
  }
  case NetPayload_ClientHeroMove: {
    // 从union中获取NetHeartbeat
    auto payload = packet->payload_as_ClientHeroMove();
    auto por = payload->por();
    auto level = payload->level();
    auto x = payload->x();
    auto y = payload->y();
    //
    NetServer::sendHeroMove(cId, por, level, x, y);
    break;
  }
  case NetPayload_ClientHeroGoal: {
    // 从union中获取NetHeartbeat
    auto payload = packet->payload_as_ClientHeroGoal();
    auto por = payload->por();
    auto type = payload->type();
    auto level = payload->level();
    auto x = payload->x();
    auto y = payload->y();
    //
    NetServer::sendHeroGoal(cId, por, type, level, x, y);
    break;
  }
  case NetPayload_ClientHeroRecruit: {
    // 从union中获取NetHeartbeat
    auto payload = packet->payload_as_ClientHeroRecruit();
    auto por = payload->por();
    auto level = payload->level();
    auto x = payload->x();
    auto y = payload->y();
    //
    NetServer::sendHeroRecruit(cId, por, level, x, y);
    break;
  }
  case NetPayload_ClientHeroTeleport: {
    // 从union中获取NetHeartbeat
    auto payload = packet->payload_as_ClientHeroTeleport();
    auto por = payload->por();
    auto level = payload->level();
    auto x = payload->x();
    auto y = payload->y();
    //
    NetServer::sendHeroTeleport(cId, por, level, x, y);
    break;
  }
  case NetPayload_ClientEndTurn: {
    // 从union中获取NetHeartbeat
    auto payload = packet->payload_as_ClientHeroTeleport();
    auto por = payload->por();
    auto level = payload->level();
    auto x = payload->x();
    auto y = payload->y();
    //
    NetServer::sendHeroTeleport(cId, por, level, x, y);
    break;
  }
  case NetPayload_ServerInScene: {
    // 从union中获取NetHeartbeat
    auto payload = packet->payload_as_ServerInScene();
    //
    auto sId = payload->scene_id();
    auto seed = payload->seed();
    auto host = payload->scene_host();
    auto clientId = payload->client_id();
    NetEvent::inScene(sId, seed, host, clientId);
    break;
  }
  case NetPayload_ServerHeroMove: {
    // 从union中获取NetHeartbeat
    auto payload = packet->payload_as_ServerHeroMove();
    auto por = payload->por();
    auto level = payload->level();
    auto x = payload->x();
    auto y = payload->y();
    NetEvent::heroMove(por, level, x, y);
    break;
  }
  case NetPayload_ServerHeroGoal: {
    // 从union中获取NetHeartbeat
    auto payload = packet->payload_as_ServerHeroGoal();
    auto por = payload->por();
    auto type = payload->type();
    auto level = payload->level();
    auto x = payload->x();
    auto y = payload->y();
    NetEvent::heroGoal(por, type, level, x, y);
    break;
  }
  case NetPayload_ServerHeroRecruit: {
    auto payload = packet->payload_as_ServerHeroRecruit();
    auto por = payload->por();
    auto level = payload->level();
    auto x = payload->x();
    auto y = payload->y();
    NetEvent::heroRecruit(por, level, x, y);
    break;
  }
  case NetPayload_ServerHeroDismiss: {
    auto payload = packet->payload_as_ServerHeroDismiss();
    auto por = payload->por();
    NetEvent::heroDismiss(por);
    break;
  }
  case NetPayload_ServerHeroTeleport: {
    auto payload = packet->payload_as_ServerHeroTeleport();
    auto por = payload->por();
    auto level = payload->level();
    auto x = payload->x();
    auto y = payload->y();
    NetEvent::heroTeleport(por, level, x, y);
    break;
  }

  default:
    break;
  }
}

void NetServer::recordPacket(void *buf, ssize_t nread) {
  auto packet = GetNetPacket(buf);
  auto type = packet->payload_type();
  if (type == NetPayload_ServerHeroMove || type == NetPayload_ServerHeroGoal ||
      type == NetPayload_ServerHeroTeleport ||
      type == NetPayload_ServerHeroRecruit ||
      type == NetPayload_ServerHeroDismiss) {
    std::vector<uint8_t> data(static_cast<uint8_t *>(buf),
                              static_cast<uint8_t *>(buf) +
                                  static_cast<size_t>(nread));
    Global::replayNetPack.emplace_back(data);
  }
}

void NetServer::handlePacket(uint64_t cId, void *buf, ssize_t nread) {
  auto packet = GetNetPacket(buf);
  if (!packet) {
    printf("无效的数据包\n");
    return;
  }
  recordPacket(buf, nread);
  dispatchPacket(cId, packet);
}
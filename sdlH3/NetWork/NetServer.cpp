#include "NetWork/NetServer.h"
#include "Global/Global.h"
#include "NetWork/NetWork.h"
#include "protocol/Protocol.h"
#include "protocol/Server.h"

void NetServer::sendLogin(uint64_t cId) {
  // 3. 创建Heartbeat表
  auto payload = CreateServerLogin(NetWork::builder, cId);
  // 4. 创建网络包（最外层包装）
  NetWork::sendPacket(payload, NetPayload_ServerLogin, cId);
  return;
}

void NetServer::sendInScene(uint64_t cId, uint32_t scene_id,
                            uint64_t scene_host) {
  // 3. 创建Heartbeat表
  auto payload = CreateServerInScene(NetWork::builder, scene_host, scene_id);
  // 4. 创建网络包（最外层包装）
  NetWork::sendPacket(payload, NetPayload_ServerInScene, cId);
  return;
}

void NetServer::handlePacket(uint64_t cId, void *buf) {
  auto packet = GetNetPacket(buf);
  if (!packet) {
    printf("无效的数据包\n");
    return;
  }
  // 4. 通过union的type判断具体类型
  switch (packet->payload_type()) {
  case NetPayload_ClientLogin: {
    NetWork::clients[cId].heartbeat = static_cast<uint64_t>(time(nullptr));
    NetServer::sendLogin(cId);
    break;
  }
  case NetPayload_ServerLogin: {
    auto payload = packet->payload_as_ServerLogin();
    NetWork::cId = payload->client_id();
    Global::InScene(0);
    break;
  }
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
    NetServer::sendInScene(cId, scene, scene_host);
    break;
  }
  case NetPayload_ServerInScene: {
    // 从union中获取NetHeartbeat
    auto sceneAck = packet->payload_as_ServerInScene();
    auto sId = sceneAck->scene_id();
    //
    Global::InScene(sId);
    break;
  }
  default:
    break;
  }
}
#ifndef PACKET_HEADER_H
#define PACKET_HEADER_H


#include <cstdint>
#include <functional>

namespace Minecraft{

namespace Network {


template<typename...Args>
struct Packet {
    uint8_t packetId;
    char* name;
    std::function<bool(void* buffer)> readDataFunction;
    std::function<void*(Args...)> writePacket;
};



}
}
#endif
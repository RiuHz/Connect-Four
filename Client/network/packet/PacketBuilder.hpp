#ifndef PACKET_BUILDER_HPP
#define PACKET_BUILDER_HPP

#include <string>
#include <cstring>     
#include <arpa/inet.h> 
#include "../shared/protocol.h"

// Ci adeguiamo a questo oppure anche per l' encode oppure ci atteniamo esclusivamente a quello usato nel protocol come fatto per encode?
struct ParsedPacket {
    MessageType type;
    std::string payload;
    bool isValid; 
};

class PacketBuilder {
public:
    static std::string encode(MessageType type, const std::string& payload = "");
    static ParsedPacket decode(const std::string& rawData);
};

#endif
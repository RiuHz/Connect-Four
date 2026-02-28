#include "PacketBuilder.hpp"

std::string PacketBuilder::encode(MessageType type, const std::string& payload) {
    MessageHeader header;
    
    // Convertiamo i valori nel formato di rete (Big Endian).
    header.type = htonl(static_cast<uint32_t>(type));
    header.length = htonl(static_cast<uint32_t>(payload.length()));

    std::string packet;
    
    // Ridimensioniamo il buffer: 8 byte (Header) + N byte (Payload)
    packet.resize(sizeof(MessageHeader) + payload.length());

    // Copiamo  i byte dell'header all'inizio del buffer
    std::memcpy(&packet[0], &header, sizeof(MessageHeader));

    // Copiamo i byte del payload subito dopo l'header
    if (!payload.empty()) {
        std::memcpy(&packet[sizeof(MessageHeader)], payload.data(), payload.length());
    }

    return packet;
}

ParsedPacket PacketBuilder::decode(const std::string& rawData) {
    ParsedPacket result;
    result.isValid = false; // Partiamo dal presupposto che sia invalido

    //  Controllo di sicurezza
    if (rawData.length() < sizeof(MessageHeader)) {
        return result; // Pacchetto troppo corto, scartato
    }

    // Estraiamo l'header copiando i primi byte
    MessageHeader header;
    std::memcpy(&header, rawData.data(), sizeof(MessageHeader));

    uint32_t hostType = ntohl(header.type);
    uint32_t hostLength = ntohl(header.length);

    // Controllo di sicurezza sul payload: 
    if (rawData.length() >= sizeof(MessageHeader) + hostLength) {
        
        result.type = static_cast<MessageType>(hostType);
        
        // Estraiamo esattamente "hostLength" byte partendo da dopo l'header
        if (hostLength > 0) {
            result.payload = rawData.substr(sizeof(MessageHeader), hostLength); // posizione_inizio - lunghezza sottostringa
        } else {
            result.payload = ""; // Nessun payload per i pacchetti che non hanno payload
        }
        
        result.isValid = true; // Decodifica avvenuta con successo tutto ok brother
    }

    return result;
}
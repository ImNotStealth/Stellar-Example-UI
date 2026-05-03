#ifndef STELLAR_PACKET_H
#define STELLAR_PACKET_H

#include <SFML/Network.hpp>
#include <memory>
#include <unordered_map>
#include <iostream>

namespace Stellar {

    class Packet
    {
    public:
        // Serialize packet data to be sent
        virtual void Serialize(sf::Packet& _packet) {}

        // Deserialize received packet data
        virtual void Deserialize(sf::Packet& _packet) {}

        // Handle packet-specific logic
        virtual void Handle() {}

        // Identifier for each packet type
        virtual int GetPacketID() { return -1; }

        virtual std::unique_ptr<Packet> Clone() { return nullptr; }
    };
}

#endif
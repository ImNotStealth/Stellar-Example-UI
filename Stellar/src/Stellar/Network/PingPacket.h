#ifndef STELLAR_PING_PACKET_H
#define STELLAR_PING_PACKET_H

#include "Stellar/Network/Packet.h"

namespace Stellar {

	class PingPacket : public Packet
	{

    public:
        void Handle() override 
        {
            std::cout << "Hey from PingPacket!" << std::endl;
        }

        int GetPacketID() override
        {
            return 0;
        }

        std::unique_ptr<Packet> Clone() override
        {
            return std::make_unique<PingPacket>(*this);
        }
	};
}

#endif
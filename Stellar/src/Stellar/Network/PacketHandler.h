#ifndef STELLAR_PACKET_HANDLER_H
#define STELLAR_PACKET_HANDLER_H

#include "Stellar/Network/Packet.h"

namespace Stellar {

	class PacketHandler
	{
	public:
		void RegisterPacket(unsigned int _id, std::unique_ptr<Packet> _packet);

		bool ReceivePacket(sf::TcpSocket& _socket);

	private:
		std::unique_ptr<Packet> CreatePacket(unsigned int _id);

	private:
		std::unordered_map<unsigned int, std::unique_ptr<Packet>> registeredPackets;
	};
}

#endif
#include "PacketHandler.h"

namespace Stellar {

	void PacketHandler::RegisterPacket(unsigned int _id, std::unique_ptr<Packet> _packet)
	{
		registeredPackets[_id] = std::move(_packet);
	}

	bool PacketHandler::ReceivePacket(sf::TcpSocket& _socket)
	{
		sf::Packet sfmlPacket;
		sf::Socket::Status status = _socket.receive(sfmlPacket);
		if (status == sf::Socket::Done)
		{
			unsigned int packetID;
			sfmlPacket >> packetID;

			if (registeredPackets.find(packetID) != registeredPackets.end())
			{
				std::unique_ptr<Packet> packet = CreatePacket(packetID);
				packet->Deserialize(sfmlPacket);
				packet->Handle();
				return true;
			}
			else
			{
				std::cout << "Unknown packet ID: " << packetID << std::endl;
				return false;
			}
		}
		else if (status == sf::Socket::NotReady)
		{
			// Returning true becomes it's fine if the packet is not yet ready, it will be in the future.
			return true;
		}
		else
		{
			// Socket error or got disconnected.
			return false;
		}
	}

	std::unique_ptr<Packet> PacketHandler::CreatePacket(unsigned int _id)
	{
		if (registeredPackets.find(_id) != registeredPackets.end())
		{
			return registeredPackets[_id]->Clone();
		}

		throw std::runtime_error("Unknown packet ID");
	}
}

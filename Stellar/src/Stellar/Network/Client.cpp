#include "Client.h"

#include <thread>

namespace Stellar {

	void Client::Connect(std::shared_ptr<PacketHandler> _handler, const std::string& _ip, unsigned int _port)
	{
		if (socket.connect(_ip, _port) != sf::Socket::Done)
		{
			std::cout << "Failed to connect to server." << std::endl;
			std::lock_guard<std::mutex> lock(onDisconnectMutex);
			if (onDisconnectFunc != nullptr)
			{
				onDisconnectFunc("connect.failed");
			}
		}
		else
		{
			running = true;

			networkThread = std::thread([this, _handler]()
				{
					while (running)
					{
						if (running && !_handler->ReceivePacket(socket))
						{
							std::cout << "Disconnected from server." << std::endl;
							std::lock_guard<std::mutex> lock(onDisconnectMutex);
							if (onDisconnectFunc != nullptr)
							{
								onDisconnectFunc("connect.disconnected");
							}
							break;
						}
					}
				}
			);
			networkThread.detach();
		}
	}

	void Client::OnDisconnect(const std::function<void(const std::string&)>& _action)
	{
		onDisconnectFunc = _action;
	}

	void Client::SendToServer(Packet& _packet)
	{
		sf::Packet sfmlPacket;
		sfmlPacket << _packet.GetPacketID();
		_packet.Serialize(sfmlPacket);
		socket.send(sfmlPacket);
	}

	void Client::Stop()
	{
		std::cout << "Stopping Client" << std::endl;
		running = false;
		{
			std::lock_guard<std::mutex> lock(onDisconnectMutex);
			onDisconnectFunc = nullptr;
		}
		if (networkThread.joinable())
		{
			networkThread.join();
		}
	}
}

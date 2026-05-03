#ifndef STELLAR_CLIENT_H
#define STELLAR_CLIENT_H

#include "Stellar/Core/Common.h"
#include "Stellar/Network/PacketHandler.h"
#include "Stellar/Network/Server.h"

#include <functional>
#include <mutex>

namespace Stellar {

	class Client
	{
	public:
		void Connect(std::shared_ptr<PacketHandler> _handler, const std::string& _ip, unsigned int _port = DEFAULT_PORT);

		void OnDisconnect(const std::function<void(const std::string&)>& _action);

		void SendToServer(Packet& _packet);

		void Stop();

	private:
		sf::TcpSocket socket;
		bool running;
		std::mutex onDisconnectMutex;
		std::thread networkThread;
		std::function<void(const std::string&)> onDisconnectFunc = nullptr;
	};
}

#endif
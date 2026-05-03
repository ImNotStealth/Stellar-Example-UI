#ifndef STELLAR_SERVER_H
#define STELLAR_SERVER_H

#include "Stellar/Core/Common.h"
#include "Stellar/Network/PacketHandler.h"

#include <SFML/Network.hpp>
#include <unordered_map>
#include <mutex>
#include <functional>
#include <atomic>

#define DEFAULT_PORT 28644

namespace Stellar {

	class Server
	{
	public:
		void Start(std::shared_ptr<PacketHandler> _handler, unsigned short _maxConnections, unsigned short _port = DEFAULT_PORT);
		void Stop();

		void OnClientConnected(const std::function<void(unsigned int)> _action);
		void OnClientDisconnected(const std::function<void(unsigned int)> _action);

		void KickClient(unsigned int _clientID);
		void SendToClient(unsigned int _id, Packet& _packet);
		void Broadcast(Packet& _packet);

		inline std::unordered_map<unsigned int, std::shared_ptr<sf::TcpSocket>> GetClients() { return clients; }

	public:
		sf::TcpListener listener;

	private:
		void HandleConnections();
		void HandleClients(std::shared_ptr<PacketHandler> _handler);

	private:
		unsigned short maxConnections;
		unsigned short port;
		
		std::atomic<bool> running;
		std::thread connectThread;
		std::thread clientThread;

		std::function<void(unsigned int)> onClientConnectedFunc;
		std::function<void(unsigned int)> onClientDisconnectedFunc;
		
		std::unordered_map<unsigned int, std::shared_ptr<sf::TcpSocket>> clients;
		std::mutex mutex;
	};
}

#endif
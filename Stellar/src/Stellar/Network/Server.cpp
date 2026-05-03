#include "Server.h"

#include <thread>

namespace Stellar
{
	void Server::Start(std::shared_ptr<PacketHandler> _handler, unsigned short _maxConnections, unsigned short _port)
	{
		maxConnections = _maxConnections;
		port = _port;

		if (listener.listen(port) != sf::Socket::Done)
		{
			std::cout << "Failed to bind to port " << port << std::endl;
			return;
		}

		running = true;
		listener.setBlocking(true);

		std::cout << "Server started for " << _maxConnections << " players, listening on port " << port << std::endl;

		connectThread = std::thread(&Server::HandleConnections, this);
		clientThread = std::thread(&Server::HandleClients, this, _handler);
	}

	void Server::Stop()
	{
		running = false;

		listener.close();

		if (connectThread.joinable())
		{
			connectThread.join();
		}
		if (clientThread.joinable())
		{
			clientThread.join();
		}

		std::cout << "Server stopped." << std::endl;
	}

	void Server::OnClientConnected(const std::function<void(unsigned int)> _action)
	{
		onClientConnectedFunc = _action;
	}

	void Server::OnClientDisconnected(const std::function<void(unsigned int)> _action)
	{
		onClientDisconnectedFunc = _action;
	}

	void Server::KickClient(unsigned int _clientID)
	{
		if (clients.find(_clientID) == clients.end())
		{
			std::cout << "Failed to kick Client: " << _clientID << ", not connected." << std::endl;
		}
		else
		{
			if (onClientDisconnectedFunc)
			{
				onClientDisconnectedFunc(_clientID);
			}
			clients.at(_clientID)->disconnect();
			clients.erase(_clientID);
			std::cout << "Kicked Client: " << _clientID << std::endl;
		}
	}

	void Server::SendToClient(unsigned int _id, Packet& _packet)
	{
		if (clients.find(_id) != clients.end())
		{
			sf::Packet sfmlPacket;
			sfmlPacket << _packet.GetPacketID();
			_packet.Serialize(sfmlPacket);
			sf::Socket::Status sendStatus = clients[_id]->send(sfmlPacket);
			if (sendStatus != sf::Socket::Status::Done)
			{
				std::cout << "Failed to send Packet to Client: " << _id << " (Status: " << sendStatus << ")" << std::endl;
			}
		}
		else
		{
			std::cout << "Failed to find Client ID: " << _id << " to send packet." << std::endl;
		}
	}

	void Server::Broadcast(Packet& _packet)
	{
		for (const auto& pair : clients)
		{
			SendToClient(pair.first, _packet);
		}
	}

	void Server::HandleConnections()
	{
		unsigned int clientCount = 1; // Starting at 1 because server should count as well

		while (running)
		{
			std::shared_ptr<sf::TcpSocket> clientSocket = std::make_shared<sf::TcpSocket>();
			clientSocket->setBlocking(false);
			if (listener.accept(*clientSocket) == sf::Socket::Done)
			{
				std::lock_guard<std::mutex> lock(mutex);
				if (clients.size() >= maxConnections)
				{
					std::cout << "Server is full! Rejected connection from: " << clientSocket->getRemoteAddress() << std::endl;
					clientSocket->disconnect();
				}
				else
				{
					std::cout << "Client connected with ID: " << clientCount << std::endl;
					clients[clientCount] = std::move(clientSocket);
					if (onClientConnectedFunc)
					{
						onClientConnectedFunc(clientCount);
					}
					clientCount++;


					if (clients.size() >= maxConnections)
					{
						std::cout << "Server is full, will reject future connections." << std::endl;
					}
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}

		// Ensure proper cleanup when stopping
		std::lock_guard<std::mutex> lock(mutex);
		clients.clear();
	}

	void Server::HandleClients(std::shared_ptr<PacketHandler> _handler)
	{
		while (running)
		{
			// Create a local copy of the clients to process without holding the mutex
			std::vector<std::pair<unsigned int, std::shared_ptr<sf::TcpSocket>>> localClients;
			{
				std::lock_guard<std::mutex> lock(mutex);
				if (!running)
				{
					break;
				}
				for (const auto& client : clients)
				{
					localClients.push_back(client);
				}
			}

			// Process packets for each client
			for (auto& [clientID, clientSocket] : localClients)
			{
				if (!_handler->ReceivePacket(*clientSocket))
				{
					std::lock_guard<std::mutex> lock(mutex);
					auto it = clients.find(clientID);
					if (it != clients.end()) // Ensure client exists before erasing
					{
						std::cout << "Client disconnected with ID: " << clientID << std::endl;
						clients.erase(it);
						if (onClientDisconnectedFunc)
						{
							onClientDisconnectedFunc(clientID);
						}
					}
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}
}
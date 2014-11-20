#pragma once

class ClientManager {

	// ctor dtor
	public:
		ClientManager(void);
		~ClientManager(void);

	// move copy operators
	public:
		ClientManager(const ClientManager &) = delete;
		ClientManager(const ClientManager &&) = delete;
		const ClientManager &operator=(const ClientManager &) = delete;
		const ClientManager &operator=(const ClientManager &&) = delete;

};

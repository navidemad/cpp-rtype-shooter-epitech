#pragma once

class ClientManager {

	// ctor / dtor
	public:
        explicit ClientManager(void);
		~ClientManager(void);

	// copy / move operators
	public:
		ClientManager(const ClientManager &) = delete;
		ClientManager(const ClientManager &&) = delete;
		const ClientManager &operator=(const ClientManager &) = delete;
		const ClientManager &operator=(const ClientManager &&) = delete;

};

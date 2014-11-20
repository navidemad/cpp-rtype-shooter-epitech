#pragma once

class Client {

	// ctor dtor
	public:
		Client(void);
		~Client(void);

	// move copy operators
	public:
		Client(const Client &) = delete;
		Client(const Client &&) = delete;
		const Client &operator=(const Client &) = delete;
		const Client &operator=(const Client &&) = delete;

};

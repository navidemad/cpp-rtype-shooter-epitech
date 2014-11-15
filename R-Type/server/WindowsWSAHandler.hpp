#pragma once

class WindowsWSAHandler {

	public:
		static void init(void);
		static void cleanup(void);

	private:
		static int nbInstances;

};

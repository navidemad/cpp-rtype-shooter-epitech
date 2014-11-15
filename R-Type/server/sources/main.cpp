#include "UnixTcpClient.hpp"
int main(void) {
	UnixTcpClient c;
	c.connect("127.0.0.1", 4242);
	while(1);
}
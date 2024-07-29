#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Server-function.h"

#ifndef _ws2tcpip
#define ws2tcpip
#include <ws2tcpip.h>
#endif // !_ws2tcpip


int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
struct addrinfo hints, * servinfo;
int ListenSocket = INVALID_SOCKET;
char recvbuf[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;

TEST_CASE("initial") {
	int x = initialize_winsock();
	printf("initial=%d\n", x);
	CHECK(x == 0);
}

TEST_CASE("setup_addrinfo") {
	int x = get_server_info("192.168.55.188", "27015", &hints, &servinfo);
	printf("setup_addrinfo=%d\n", x);
	CHECK(x == 0);
}

TEST_CASE("bind_to_first") {
	int x = bind_to_first_available(sockfd, servinfo);
	printf("bind_to_first=%d\n", x);
	CHECK(x == 0);
}

TEST_CASE("start_listening") {
	int x = start_listening(sockfd);
	printf("start_listening=%d\n", x);
	CHECK(x == 0);
}

TEST_CASE("the central while") {
std::vector<int> clientSockets;
WSAPOLLFD fds[FD_SETSIZE];
	fds[0].fd = sockfd;
	fds[0].events = POLLRDNORM;
	int i = 0;
	while (true)
	{
		//printf("%d", ++i);
		int result = define_clients_sockets_and_poll(clientSockets,fds);
		if (result == 1) break;
		result = check_about_new_connection(sockfd, fds, clientSockets);
		if (result == 1) continue;
		checking_incoming_data_for_each_client(fds, clientSockets, recvbuf, recvbuflen);
	}

}

TEST_CASE("clean up") {
	cleanup(sockfd);
	printf("close_all\n");
}

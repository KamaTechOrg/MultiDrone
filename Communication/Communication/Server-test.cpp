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

TEST_CASE("initialize_winsock") {
	int x = initialize_winsock();
	printf("initialize_winsock=%d\n", x);
	CHECK(x == 0);
}

TEST_CASE("get_server_info") {
	int x = get_server_info(" ", &hints, &servinfo);
	printf("get_server_info=%d\n", x);
	CHECK(x == 0);
}

TEST_CASE("bind_to_first_available_socket") {
	int x = bind_to_first_available_socket(sockfd, servinfo);
	printf("bind_to_first_available_socket=%d\n", x);
	CHECK(x == 0);
}

TEST_CASE("start_listening") {
	int x = start_listening(sockfd);
	printf("start_listening=%d\n", x);
	CHECK(x == 0);
}

TEST_CASE("the central while") {
	std::vector<int> clientSockets;
	WSAPOLLFD activeConnections[FD_SETSIZE];
	activeConnections[0].fd = sockfd;
	activeConnections[0].events = POLLRDNORM;
	while (true)
	{
		int result = define_clients_sockets_and_poll(clientSockets, activeConnections);
		if (result == 1) break;
		result = check_about_new_client_connection(sockfd, activeConnections, clientSockets);
		if (result == 1) continue;
		checking_incoming_data_for_each_client(activeConnections, clientSockets, recvbuf, recvbuflen);
	}

}

TEST_CASE("clean up") {
	cleanup(sockfd);
	printf("close_all\n");
}

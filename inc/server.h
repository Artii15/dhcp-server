#ifndef SERVER_H
#define SERVER_H

class Server {
	private:
		int sock;
		void configureSocket();
		void configureAddress(struct sockaddr_in*);

	public:
		Server();
		~Server();

		void listen();
};

#endif

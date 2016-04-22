#ifndef SERVER_H
#define SERVER_H

class Server {
	private:
		int sock;
		void configureSocket();

	public:
		Server();
		~Server();
};

#endif

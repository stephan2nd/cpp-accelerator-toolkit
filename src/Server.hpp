#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <vector>
#include <string>



using namespace std;

class Server
{

public:

	Server(unsigned int port);

	virtual
	~Server();

private:

	void 
	runService(int client_socket);
	
	void
	processMessage(const vector<string>& message, int client_socket);
	
	vector<string>
	splitString(string str, string delimiter) const;
};

#endif /* SERVER_HPP_ */

#include "Server.hpp"

//#include <sstream>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>



Server::Server(unsigned int port)
{ 
    int socket_desc;
    int client_socket;
    int c;

    struct sockaddr_in server;
    struct sockaddr_in client;

     
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if( socket_desc == -1 ){
        cout << "Server error: Could not create socket." << endl;
        exit(0);
    }

    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons( port );
     
    if( ::bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0 ){
        cout << "Server error: Bind failed." << endl;
        exit(0);
    }
     
    listen(socket_desc , 3);
     
    cout << "Server started, waiting for incoming connections..." << endl;
    c = sizeof(struct sockaddr_in);
     
    client_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if( client_socket < 0 ){
        cout << "Server error: Client not accepted." << endl;;
        exit(0);
    }

	cout << "Client accepted." << endl;
	write(client_socket , "WHOAREYOU\n" , strlen("WHOAREYOU\n"));

	runService(client_socket);
	cout << "Shutting down server." << endl;	
}



Server::~Server()
{ }



void 
Server::runService(int client_socket)
{
    int read_size;
    char client_message[2000];

    while( (read_size = recv(client_socket , client_message , 2000 , 0)) > 0 ){
        string s(client_message);
        vector<string> message = splitString(s,";");
        if( message.size()>0 ){
	        cout << "Server, message received: >>" << message.at(0) << "<<" << endl;
	        string command = message.at(0);
	        vector<string> commandlist = splitString(command,",");
	        processMessage(commandlist, client_socket);
	    }
        
    }
     
    if( read_size == 0 ){
        cout << "Client disconnected" << endl;
    } else if( read_size == -1 ){
        cout << "Client message receive failure." << endl;
    }
}



void
Server::processMessage(const vector<string>& message, int client_socket)
{
	if( message.size() == 0 ){
		return;
	}
	if( message.at(0) == "EXIT" ){ 
		cout << "Client message EXIT, shutting down server." << endl;
		exit(0);
	} else {
		write(client_socket , "UNKNOWN COMMAND\n" , strlen("UNKNOWN COMMAND\n"));
	}
}
	


vector<string>
Server::splitString(string str, string delimiter) const
{
	vector<string> result;
    auto start = 0U;
    auto end = str.find(delimiter);
    
    while (end != string::npos)
    {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end   = str.find(delimiter, start);
    }
    
    return result;
}





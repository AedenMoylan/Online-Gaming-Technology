#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> //For std::cout, std::endl, std::cin.getline
#include "Player.h"

enum Packet
{
	P_ChatMessage,
	P_Test,
	P_Position,
	P_PlayerID,
	P_NumberOfPlayer
};

class Client
{
public: //Public functions
	Client(std::string IP, int PORT);
	bool Connect();

	bool SendString(std::string& _string);
	bool CloseConnection();
	bool GetString(std::string& _string);

	//Position 
	bool SendPosition(std::string& _string);
	std::string getPositionMessage();
	void setPositionMessage(std::string message);

	//Player ID
	bool Send_ID(std::string& _string);
	std::string getID_Message();
	void setID_Message(std::string message);

	//Number of player
	bool SendNum(std::string& _string);
	std::string getPlayerNum_Message();
	void setPlayerNum(std::string message);

private: //Private functions
	bool ProcessPacket(Packet _packettype);
	static void ClientThread();
	//Sending Funcs
	bool sendall(char* data, int totalbytes);
	bool SendInt(int _int);
	bool SendPacketType(Packet _packettype);

	//Getting Funcs
	bool recvall(char* data, int totalbytes);
	bool GetInt(int& _int);
	bool GetPacketType(Packet& _packettype);

	std::string positionMessage;
	std::string ID_Message;
	std::string PlayerNum_Message;

private:
	SOCKET Connection;//This client's connection to the server
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
};

static Client* clientptr; //This client ptr is necessary so that the ClientThread method can access the Client instance/methods. Since the ClientThread method is static, this is the simplest workaround I could think of since there will only be one instance of the client.
// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocket.h"

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
}

bool ClientSocket::InitSocket()
{

	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
		return false;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET) {
		UE_LOG(LogTemp, Error, TEXT("Socket is Invalid"));
		return false;
	}

	int ret;
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);

	ret = connect(Socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
	if (ret == SOCKET_ERROR) {
		UE_LOG(LogTemp, Error, TEXT("Socket Connect Fail"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Socket Init and Connect Success"));
	IsInit = true;


	return true;

}

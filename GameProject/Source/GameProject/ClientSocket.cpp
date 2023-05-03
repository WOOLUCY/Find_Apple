// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocket.h"

ClientSocket::ClientSocket()
{
	IsInit = false;
	memset(RecvBuf, BUFSIZE, 0);
	PrevRemain = 0;
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
	else {
		UE_LOG(LogTemp, Warning, TEXT("Socket Init and Connect Success"));
		IsInit = true;
		
	}

	u_long nonBlockingMode = 1;
	ioctlsocket(Socket, FIONBIO, &nonBlockingMode);



	return true;

}

void ClientSocket::SendLoginPacket()
{
}

void ClientSocket::SendMovePacket()
{
}

void ClientSocket::SendRegistOrPurchasePacket(bool Regist)
{
	if (Regist) {
		//등록했을때 패킷보내기
	}
	else {
		//구매했을때 패킷보내기
	}
}

void ClientSocket::SendTestPacket()
{
	SC_CS_TESTPACKET temp;
	temp.size = sizeof(SC_CS_TESTPACKET);
	temp.type = TESTPACKET;
	temp.test = rand();

	int retval = send(Socket, (const char*)&temp, temp.size,0);
	if (retval != 0) {
		UE_LOG(LogTemp, Warning, TEXT("Client To Server Send Success, [%d]"),temp.test);

	}

}

void ClientSocket::PacketRecv()
{

	int retval = recv(Socket, (char*)RecvBuf, BUFSIZE, 0);
	if (retval > 0) {

		int remain_data = retval + PrevRemain;

		UE_LOG(LogTemp, Warning, TEXT("PacketRecv recv Byte : %d"), retval);
		UE_LOG(LogTemp, Warning, TEXT("recv packet %d %d %d %d"), RecvBuf[0], RecvBuf[1], RecvBuf[2],remain_data);

		char* p = RecvBuf;

		while (remain_data > 0) {

			int packet_size = p[0];
			UE_LOG(LogTemp, Warning, TEXT("%d  %d"), RecvBuf[0],p[0]);

			if (packet_size <= remain_data) {
				ProcessPacket(p);
				p = p + packet_size;
				remain_data = remain_data - packet_size;
			}
			else break;

			PrevRemain = remain_data;
			if (remain_data > 0) {
				memcpy(RecvBuf, p, remain_data);
			}

		}


	}
	//패킷재조립하고
	
	//if (retval > 0) {
	//	UE_LOG(LogTemp, Warning, TEXT("noblocing socket get PACKET"));
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("noblocing socket doesnt get PACKET"));

	//}


	//종류에따라 받는거 처리하기 - 함수를 따로처리하자~~~~

}

void ClientSocket::ProcessPacket(char* packet)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessPacket??? %d %d "), packet[0], packet[1]);
	//packet type에따라 처리해주는거임 
	int PacketSize = packet[0];
	int PacketType = packet[1];

	//받은 패킷 처리하는거임 
	switch (PacketType)
	{ //패킷 type을 본다.

	case 10: 
	{
		//testpacket 왓다갓다할거임
		SC_CS_TESTPACKET* p = reinterpret_cast<SC_CS_TESTPACKET*>(packet);

		printf("[SC_CS_TESTPACKET 받음] %d %d %d \n", p->size, p->type, p->test);


	}

	}
}

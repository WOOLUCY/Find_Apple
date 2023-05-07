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
	UE_LOG(LogTemp, Warning, TEXT("CloseSocket"));
	Items.Reset();
	memset(RecvBuf, 0, sizeof(BUFSIZE));

	closesocket(Socket);
	WSACleanup();
	
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
	CS_LOGIN_PACKET login;
	login.size = sizeof(CS_LOGIN_PACKET);
	login.type = CS_LOGIN;
	const char* str = "helloword";
	strcpy(login.name, str);

	int retval = send(Socket, (const char*)&login, login.size, 0);
	if (retval != 0) {
		UE_LOG(LogTemp, Warning,TEXT("Client To Server LoginPacekt Send Success [%d %d]"), login.size, login.type);

	}


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
	temp.testNum = rand();

	int retval = send(Socket, (const char*)&temp, temp.size,0);
	if (retval != 0) {
		UE_LOG(LogTemp, Warning, TEXT("Client To Server Send Success, [%d]"),temp.testNum);

	}

}

void ClientSocket::SendTestSalePacket(int item, int num, int price)
{

	UE_LOG(LogTemp, Warning, TEXT("[SendTestSalePacket] %d %d"), num,price);

	SC_CS_TESTPACKET temp;
	temp.size = sizeof(SC_CS_TESTPACKET);
	temp.type = TESTPACKET;
	temp.item = item;
	temp.testNum = num;
	temp.testPrice = price;

	int retval = send(Socket, (const char*)&temp, temp.size, 0);
	if (retval != 0) {
		UE_LOG(LogTemp, Warning, TEXT("Client To Server Send Success,  [%d %d, %d]"),temp.item ,temp.testNum,temp.testPrice);

	}

}

void ClientSocket::RecvDataTest()
{
	for (int i{ 0 }; i < Items.Num(); ++i) {
		UE_LOG(LogTemp, Warning, TEXT("[RecvDataTest] : %d %d %d"), Items[i].Item, Items[i].Num, Items[i].Price);

	}
}

void ClientSocket::PacketRecv()
{

	int retval = recv(Socket, (char*)RecvBuf, BUFSIZE, 0);
	if (retval > 0) {

		int remain_data = retval + PrevRemain;

		UE_LOG(LogTemp, Warning, TEXT("PacketRecv recv Byte : %d"), retval);
		UE_LOG(LogTemp, Warning, TEXT("recv packet [size:%d] [type: %d] [remaindata: %d]"), RecvBuf[0], RecvBuf[1],remain_data);

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

}

void ClientSocket::ProcessPacket(char* packet)
{
	//packet type에따라 처리해주는거임 
	int PacketSize = packet[0];
	//int PacketType = ;

	//받은 패킷 type에 따라 처리하는거임 
	switch (packet[1])
	{ 

	case TESTPACKET:
	{
		//testpacket 왓다갓다할거임
		SC_CS_TESTPACKET* p = reinterpret_cast<SC_CS_TESTPACKET*>(packet);

		SalesItem temp1{ p->item,p->testNum,p->testPrice };
		Items.Add(temp1);
		UE_LOG(LogTemp, Warning, TEXT("[SC_CS_TESTPACKET] %d %d %d %d"), p->size, p->type, p->testNum, p->testPrice);

	}

	}
}

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
	UE_LOG(LogTemp, Warning, TEXT("CloseSocket????"));
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
	//흠...
}

void ClientSocket::SendMovePacket()
{
}

void ClientSocket::SendRegistOrPurchasePacket(bool Regist,void* packet)
{
	if (Regist) {
		//등록했을때 패킷보내기

		CS_SC_ITEM_PACKET temp = *(CS_SC_ITEM_PACKET*)packet;

		temp.size = sizeof(CS_SC_ITEM_PACKET);
		temp.type = SC_CS_ITEM_REGISTER;
		

		packet = (CS_SC_ITEM_PACKET*)packet;

		int retval = send(Socket, (const char*)&temp, temp.size, 0);
		if (retval != 0) {
			UE_LOG(LogTemp, Warning, TEXT("Client To Server Send Success,  [item:%d] [total:%d] [price:%d]"),
				temp.item, temp.total, temp.price);

		}

		//UE_LOG(LogTemp, Warning, TEXT("[CS_SC_ITEM_PACKET] %d %d"), num, price);


	

	}
	else {
		//구매했을때 패킷보내기
		CS_BUY_PACKET temp;
		temp.size = sizeof(CS_BUY_PACKET);
		temp.type = CS_CLICKED_BUY;
		temp.rId = *(int*)packet;


		int retval = send(Socket, (const char*)&temp, temp.size, 0);
		if (retval != 0) {
			UE_LOG(LogTemp, Warning, TEXT("[CS_BUY_PACKET] send Success, [rId:%d]"),temp.rId);

		}


	}
}


bool ClientSocket::SendIngamePacket()
{
	CS_INGAME_TEST_PACKET temp;
	temp.size = sizeof(CS_INGAME_TEST_PACKET);
	temp.type = CS_LOGIN_TEST;
	temp.isIn = true;

	int retval = send(Socket, (const char*)&temp, temp.size, 0);
	if (retval != 0) {
		UE_LOG(LogTemp, Warning, TEXT("Client To Server Send IsIngamePacket Success, [%d]"), temp.isIn);
		PacketRecv();
		return true;
	}

	return false;


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



		while (remain_data > 0) {
			char* p = RecvBuf;

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
//	UE_LOG(LogTemp, Warning, TEXT("ProcessPacket??? %d %d "), packet[0], packet[1]);
	//packet type에따라 처리해주는거임 
	int PacketSize = packet[0];
	//int PacketType = ;

	//받은 패킷 처리하는거임 
	switch (packet[1])
	{ //패킷 type을 본다.

	case SC_CS_ITEM_REGISTER:
	{
		//testpacket 왓다갓다할거임
		CS_SC_ITEM_PACKET* p = reinterpret_cast<CS_SC_ITEM_PACKET*>(packet);

		RegisterItems temp1{p->item,p->total,p->price,p->registerId};

		Items.Add(temp1);
		UE_LOG(LogTemp, Warning, TEXT("[CS_SC_ITEM_PACKET] %d %d %d %d"), p->type, p->item, p->total, p->price);

		break;
	}
	case SC_RECEIVE_GOLD:
	{


		break;
	}

	}
}

// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"


#include "Runtime/Core/Public/HAL/Runnable.h"

#include "CoreMinimal.h"

//프로토콜 추가하면 삭제해야함
#define SERVER_ADDR  "127.0.0.1"
#define SERVER_PORT  4000
#define BUFSIZE		 1024


/**
 * 
 */


//PROTOCL
constexpr char TESTPACKET = 10;
constexpr char CS_LOGIN_TEST = 11;

//constexpr int APPLE = 0;
//constexpr int ORANGE = 1;
//constexpr int TRUNK = 2;
//constexpr int ROCK = 3;
//constexpr int BRAHCN = 4;
//constexpr int SEED = 5;
//constexpr int IRON = 6;
//constexpr int RADISH = 7;
//constexpr int GOLD = 8;

#pragma pack (push, 1)

struct SC_CS_TESTPACKET {
	unsigned char size;
	char	type;
	int		item;
	int		testNum;
	int		testPrice;

};

struct CS_INGAME_TEST_PACKET {
	unsigned char size;
	char	type;
	bool	isIn;

};


#pragma pack (pop)


//PROTOCOL END



struct SalesItem {
	int Item;
	int Num;
	int Price;
};


class GAMEPROJECT_API ClientSocket
{
public:
	ClientSocket();
	~ClientSocket();

	SOCKET Socket;
	bool IsInit;
	TArray<SalesItem> Items;

	char RecvBuf[BUFSIZE];
	int PrevRemain;


public:
	bool InitSocket();

	void SendLoginPacket();
	void SendMovePacket();
	void SendRegistOrPurchasePacket(bool Regist);

	//이거 삭제해야하는 함수들 테스트 함수임
	bool SendIngamePacket();
	void SendTestPacket();
	void SendTestSalePacket(int item,int num, int price);
	void RecvDataTest();

	void PacketRecv();
	void ProcessPacket(char* packet);
	
	


};

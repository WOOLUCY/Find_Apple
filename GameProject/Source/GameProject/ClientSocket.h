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


//일단 이러고 왓다갓다해보자,,ㅅㅂ
constexpr char TESTPACKET = 10;
#pragma pack (push, 1)

struct SC_CS_TESTPACKET {
	unsigned char size;
	char	type;
	int		testNum;
	int		testPrice;

};
#pragma pack (pop)



class GAMEPROJECT_API ClientSocket
{
public:
	ClientSocket();
	~ClientSocket();

	SOCKET Socket;
	bool IsInit;

	char RecvBuf[BUFSIZE];
	int PrevRemain;


public:
	bool InitSocket();

	void SendLoginPacket();
	void SendMovePacket();
	void SendRegistOrPurchasePacket(bool Regist);

	//이거 삭제해야하는 함수들 테스트 함수임
	void SendTestPacket();
	void SendTestSalePacket(int num, int price);

	void PacketRecv();
	void ProcessPacket(char* packet);
	
	


};

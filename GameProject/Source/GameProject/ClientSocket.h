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

#include "../../../StudyIOCPServer/protocol.h"


//프로토콜 추가하면 삭제해야함
#define SERVER_ADDR  "127.0.0.1"
#define SERVER_PORT  4000
#define BUFSIZE		 1024




//얘도 손봐야함
struct RegisterItems {
	int Item;
	int Num;
	int Price;
	unsigned int RegisterId;		

};


class GAMEPROJECT_API ClientSocket
{
public:
	ClientSocket();
	~ClientSocket();

	SOCKET Socket;
	bool IsInit;
	TArray<RegisterItems> Items;

	char RecvBuf[BUFSIZE];
	int PrevRemain;


public:
	bool InitSocket();

	void SendLoginPacket();
	void SendMovePacket();

	void SendRegistOrPurchasePacket(bool Regist,void * packet); //true면 Resigter, false면 purchase??아님쪼개????




	//이거 삭제해야하는 함수들 테스트 함수임
	bool SendIngamePacket();
	void RecvDataTest();

	void PacketRecv();
	void ProcessPacket(char* packet);
	
	


};

// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <unordered_map>

#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"



#include "Runtime/Core/Public/HAL/Runnable.h"

#include "CoreMinimal.h"

#include "../../../StudyIOCPServer/protocol.h"


//�������� �߰��ϸ� �����ؾ���
#define SERVER_ADDR  "127.0.0.1"
#define SERVER_PORT  4000
#define BUFSIZE		 1024




//�굵 �պ�����
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
	TMap<unsigned int,RegisterItems> Items;
	//unordered_map<int, RegisterItems> Items;


	char RecvBuf[BUFSIZE];
	int PrevRemain;


public:
	bool InitSocket();

	void SendLoginPacket();
	void SendMovePacket();

	void SendRegistOrPurchasePacket(bool Regist,void * packet); //true�� Resigter, false�� purchase??�ƴ��ɰ�????




	//�̰� �����ؾ��ϴ� �Լ��� �׽�Ʈ �Լ���
	bool SendIngamePacket();
	void RecvDataTest();

	void PacketRecv();
	void ProcessPacket(char* packet);
	
	


};

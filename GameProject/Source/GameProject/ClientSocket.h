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
	int RegisterId;		

};


class GAMEPROJECT_API ClientSocket
{
public:
	ClientSocket();
	~ClientSocket();

	SOCKET Socket;
	bool IsInit;
	TMap<int,RegisterItems> Items;
	
	int AddGold;


	char RecvBuf[BUFSIZE];
	int PrevRemain;


public:
	bool InitSocket();


	void SendRegistOrPurchasePacket(bool Regist,void * packet); //true�� Resigter, false�� purchase??�ƴ��ɰ�????

	void PacketRecv();
	void ProcessPacket(char* packet);




	//�̰� �����ؾ��ϴ� �Լ��� �׽�Ʈ �Լ���
	bool SendIngamePacket();

	void SendLoginPacket();
	void SendMovePacket();



};

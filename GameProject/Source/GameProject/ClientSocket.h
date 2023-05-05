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

//�������� �߰��ϸ� �����ؾ���
#define SERVER_ADDR  "127.0.0.1"
#define SERVER_PORT  4000
#define BUFSIZE		 1024


/**
 * 
 */


//�ϴ� �̷��� �Ӵٰ����غ���,,����
constexpr char TESTPACKET = 10;

struct SC_CS_TESTPACKET {
	unsigned char size;
	char	type;
	char	test;

};


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

	void SendTestPacket();

	void PacketRecv();
	void ProcessPacket(char* packet);
	
	


};
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


/**
 * 
 */
class GAMEPROJECT_API ClientSocket
{
public:
	ClientSocket();
	~ClientSocket();

	SOCKET Socket;
	bool IsInit = false;

	bool InitSocket();
	

	



};

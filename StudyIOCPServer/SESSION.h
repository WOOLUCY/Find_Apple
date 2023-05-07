#pragma once
#include "stdafx.h"

#define BUFSIZE 256
#define NAMESIZE 10

enum COMP_TYPE { OP_ACCEPT, OP_RECV, OP_SEND };

class EXP_OVER
{
public:
	WSAOVERLAPPED Over;
	WSABUF wsaBuf;
	char sendBuf[BUFSIZE];
	COMP_TYPE comeType;

	EXP_OVER()
	{
		wsaBuf.len = BUFSIZE;
		wsaBuf.buf = sendBuf;
		comeType = OP_RECV;
		ZeroMemory(&Over, sizeof(Over));
	}

	EXP_OVER(char* packet)
	{
		wsaBuf.len = packet[0];
		wsaBuf.buf = sendBuf;

		ZeroMemory(&Over, sizeof(Over));
		comeType = OP_SEND;

		memcpy(sendBuf, packet, packet[0]);
	}

};

class SESSION
{
	EXP_OVER recvOver;
public:
	int id;
	SOCKET socket;
	short x, y, z;
	char name[NAMESIZE];
	
	int prevRemain;
public:
	SESSION() :socket(0)
	{
		id = -1;
		x = y = z = 0;
		name[0] = '\0';
		prevRemain = 0;
	}
	~SESSION(){}

	void recv();
	void send(void* packet);

	void SendMovePacket(int id);

	void send_login_info_packet()
	{
		SC_LOGIN_INFO_PACKET p;
		p.id = id;
		p.size = sizeof(SC_LOGIN_INFO_PACKET);
		p.type = SC_LOGIN_INFO;
		p.x = x;
		p.y = y;
		send(&p);
	}



};


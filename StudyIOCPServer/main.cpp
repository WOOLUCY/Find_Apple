#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "SESSION.h"
//#include "protocol.h"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 4000
#define BUFSIZE 256
#define MAX_USER 100

array<SESSION, MAX_USER> clients;
//테스트 벡터
struct TestStruc {
	int key;
	int recvNum;
};
vector<TestStruc> TestVector;

void process_packet(int c_id, char* packet);
int PlayerCount = 0;



void disconnect(int c_id)
{
	//for (auto& pl : clients) {
	//	{
	//		lock_guard<mutex> ll(pl._s_lock);
	//		if (ST_INGAME != pl._state) continue;
	//	}
	//	if (pl._id == c_id) continue;
	//	pl.send_remove_player_packet(c_id);
	//}

	printf("Disconnect Call\n");
	PlayerCount -= 1;
	closesocket(clients[c_id].socket);

//	lock_guard<mutex> ll(clients[c_id]._s_lock);
//	clients[c_id]._state = ST_FREE;
}


//using namespace std;
int main()
{
	int retval;

	HANDLE h_iocp;

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	SOCKET listenSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (listenSock == INVALID_SOCKET) {
		cout << "listensocket fail!" << endl;
	}

	SOCKADDR_IN server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;

	retval = bind(listenSock, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
	if (retval == SOCKET_ERROR) {
		cout << "listensocket bind fail!" << endl;
	}

	retval = listen(listenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR) {
		cout << "listensocket listen fail!" << endl;
	}

	SOCKADDR_IN cl_addr;
	int addr_size = sizeof(cl_addr);
	int client_id = 0;

	h_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(listenSock), h_iocp, 9999, 0);
	SOCKET ClientSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	EXP_OVER a_over;
	a_over.comeType = OP_ACCEPT;
	AcceptEx(listenSock, ClientSock, a_over.sendBuf, 0, addr_size + 16, addr_size + 16, 0, &a_over.Over);
	//
	while (true) {
		DWORD num_bytes;
		ULONG_PTR key;
		WSAOVERLAPPED* over = nullptr;
		BOOL ret = GetQueuedCompletionStatus(h_iocp, &num_bytes, &key, &over, INFINITE);
		EXP_OVER* ex_over = reinterpret_cast<EXP_OVER*>(over);

		if (FALSE == ret) {
			if (ex_over->comeType == OP_ACCEPT) cout << "Accept Error";
			else {
				
				cout << "GQCS Error on client[" << key << "]\n";
				disconnect(static_cast<int>(key));
				if (ex_over->comeType == OP_SEND) delete ex_over;
				continue;
			}
		}


		if ((0 == num_bytes) && ((ex_over->comeType == OP_RECV) || (ex_over->comeType == OP_SEND))) {
			disconnect(static_cast<int>(key));
			if (ex_over->comeType == OP_SEND) delete ex_over;
			continue;
		}



		switch (ex_over->comeType) {
		case OP_ACCEPT: {
			printf("OP_ACCETP함수 호출\n");

			int client_id = PlayerCount++;
			if (client_id != -1) {
				//	clients[client_id].in_use = true;
				clients[client_id].x = 0;
				clients[client_id].y = 0;
				clients[client_id].z = 0;

				clients[client_id].id = client_id;
				clients[client_id].name[0] = 0;
				clients[client_id].prevRemain = 0;
				clients[client_id].socket = ClientSock;
				CreateIoCompletionPort(reinterpret_cast<HANDLE>(ClientSock),
					h_iocp, client_id, 0);
				clients[client_id].recv();
				ClientSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
			}
			else {
				cout << "Max user exceeded.\n";
			}
			ZeroMemory(&a_over.Over, sizeof(a_over.Over));
			AcceptEx(listenSock, ClientSock, a_over.sendBuf, 0, addr_size + 16, addr_size + 16, 0, &a_over.Over);
			cout << "접속인원 총 : " << PlayerCount << endl;

			break;
		}
		case OP_RECV: {
			printf("[%d] OP_RECV함수 호출\n",(int)key);

			int remain_data = num_bytes + clients[key].prevRemain;
			char* p = ex_over->sendBuf;
			
			while (remain_data > 0) {
				int packet_size = p[0];
				if (packet_size <= remain_data) {
					process_packet(static_cast<int>(key), p);
					p = p + packet_size;
					remain_data = remain_data - packet_size;
				}
				else break;
			}
			clients[key].prevRemain = remain_data;
			if (remain_data > 0) {
				memcpy(ex_over->sendBuf, p, remain_data);
			}
			clients[key].recv();
			break;
		}
		case OP_SEND:
			printf("[%d] - OP_SEND함수 호출\n",key);

			delete ex_over;
			break;
		}
	}



}

void process_packet(int c_id, char* packet)
{
	//받은 패킷 처리하는거임 
	switch (packet[1]) { //패킷 type을 본다.
	case CS_LOGIN: {
		CS_LOGIN_PACKET* p = reinterpret_cast<CS_LOGIN_PACKET*>(packet);
		strcpy(clients[c_id].name, p->name);
		clients[c_id].send_login_info_packet();

		//로그인정보 모두에게 보내준다.ㄱ느데 우리는 필요없을듯??

		SC_ADD_PLAYER_PACKET add_packet;
		add_packet.id = c_id;
		strcpy_s(add_packet.name, p->name);
		add_packet.size = sizeof(add_packet);
		add_packet.type = SC_ADD_PLAYER;
		add_packet.x = clients[c_id].x;
		add_packet.y = clients[c_id].y;
		printf("CS_LOGIN 함수 호출함\n");

		break;
	}
	case CS_MOVE: {
		CS_MOVE_PACKET* p = reinterpret_cast<CS_MOVE_PACKET*>(packet);
		clients[c_id].x = p->direction;
		printf("[%d] x:%d\n", c_id, clients[c_id].x);
		break;
	}
	case CS_TEST: {

		CS_TEST_PACKET* p = reinterpret_cast<CS_TEST_PACKET*>(packet);

		SC_TEST_PACKET temp;
		temp.size = sizeof(SC_TEST_PACKET);
		temp.type = SC_TEST;
		temp.test = p->test;
		temp.id = c_id;

		TestStruc testTemp{ c_id,temp.test };
		TestVector.push_back(testTemp);

		for (TestStruc a : TestVector) {
			printf("[%d] - %d\n", a.key, a.recvNum);
		}
		printf("[CS_TEST패킷 받음] %d %d %d %d\n", temp.size, temp.type, temp.test, temp.id);

		//이제 클라이언트 모두에게 보내줘야함.
		for (auto& pl : clients) {
			//if (false == pl.in_use) continue;
			//if (pl._id == c_id) continue;
			pl.send(&temp);
			printf("[%d] SC_TEST패킷 전송\n", pl.id);
			//pl.do_send(&add_packet);
		}
	}
	case TESTPACKET: {
		//testpacket 왓다갓다할거임

		printf("어라ㅣ너라ㅣ어라닝eeㄹ");
		SC_CS_TESTPACKET* p = reinterpret_cast<SC_CS_TESTPACKET*>(packet);

		SC_CS_TESTPACKET temp;
		memcpy(&temp, p, sizeof(SC_CS_TESTPACKET));
		printf("[TEMP SC_CS_TESTPACKET 받음] %d %d %d %d %d\n", 
			temp.size, temp.type,temp.item, temp.testNum,temp.testPrice);

		//모든클라이언트에게 보내보자.
		for (auto& pl : clients) {
			if (pl.id >= 0) {
			//	if (pl.id == c_id) continue;
				pl.send(&temp);
				printf("[%d] - [SC_CS_TESTPACKET 보냄] %d %d %d %d %d\n", 
					pl.id, temp.size,temp.type, temp.item, temp.testNum,temp.testPrice);
			}
		}



		//clients[c_id].send(&temp);

	}

	}

}
			

	






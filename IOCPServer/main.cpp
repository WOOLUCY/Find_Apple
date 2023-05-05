#define _CRT_SECURE_NO_WARNINGS
#include "global.h"
#include "SESSION.h"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 4000
#define BUFSIZE 256
#define MAX_USER 100

array<SESSION, MAX_USER> clients;
//�׽�Ʈ ����
struct TestStruc {
	int key;
	int recvNum;
};
vector<TestStruc> TestVector;

void process_packet(int c_id, char* packet);


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

		static int count = 0;

		switch (ex_over->comeType) {
		case OP_ACCEPT: {
			printf("OP_ACCETP�Լ� ȣ��\n");

			int client_id = count++;
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
			cout << "�����ο� �� : " << count << endl;

			break;
		}
		case OP_RECV: {
			printf("[%d] OP_RECV�Լ� ȣ��\n", (int)key);

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
			printf("[%d] - OP_SEND�Լ� ȣ��\n", key);

			delete ex_over;
			break;
		}
	}



}

void process_packet(int c_id, char* packet)
{
	//���� ��Ŷ ó���ϴ°��� 
	switch (packet[1]) { //��Ŷ type�� ����.
	case CS_LOGIN: {
		CS_LOGIN_PACKET* p = reinterpret_cast<CS_LOGIN_PACKET*>(packet);
		strcpy(clients[c_id].name, p->name);
		clients[c_id].send_login_info_packet();

		//�α������� ��ο��� �����ش�.������ �츮�� �ʿ������??

		SC_ADD_PLAYER_PACKET add_packet;
		add_packet.id = c_id;
		strcpy_s(add_packet.name, p->name);
		add_packet.size = sizeof(add_packet);
		add_packet.type = SC_ADD_PLAYER;
		add_packet.x = clients[c_id].x;
		add_packet.y = clients[c_id].y;
		printf("CS_LOGIN �Լ� ȣ����\n");

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
		printf("[CS_TEST��Ŷ ����] %d %d %d %d\n", temp.size, temp.type, temp.test, temp.id);

		//���� Ŭ���̾�Ʈ ��ο��� ���������.
		for (auto& pl : clients) {
			//if (false == pl.in_use) continue;
			//if (pl._id == c_id) continue;
			pl.send(&temp);
			printf("[%d] SC_TEST��Ŷ ����\n", pl.id);
			//pl.do_send(&add_packet);
		}
		//

	}

	}



}





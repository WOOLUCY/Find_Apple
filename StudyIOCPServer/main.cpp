#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "SESSION.h"

#define SERVER_ADDR "10.30.1"
#define SERVER_PORT 4000
#define BUFSIZE 256
#define MAX_USER 100


array<SESSION, MAX_USER> clients;

unordered_map<int, CS_SC_ITEM_PACKET> ItemList;

void process_packet(int c_id, char* packet);
int PlayerCount = 0;



void disconnect(int c_id)
{


	printf("[%d] Disconnect Call\n",c_id);
	clients[c_id].ingame = false;
	closesocket(clients[c_id].socket);

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
			printf("OP_ACCETP�Լ� ȣ��\n");

			int client_id = PlayerCount++;
			if (client_id != -1) {
				//	clients[client_id].in_use = true;
				clients[client_id].x = 0;
				clients[client_id].y = 0;
				clients[client_id].z = 0;
				clients[client_id].ingame = true;

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
			cout << "�����ο� �� : " << PlayerCount << endl;

			break;
		}
		case OP_RECV: {
			printf("[%d] OP_RECV�Լ� ȣ��\n",(int)key);

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
			printf("[%d] - OP_SEND�Լ� ȣ��\n",key);

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

		printf("[CS_LOGIN] �Լ� ȣ����\n");

		CS_LOGIN_PACKET* p = reinterpret_cast<CS_LOGIN_PACKET*>(packet);
		strcpy(clients[c_id].name, p->name);
		clients[c_id].send_login_info_packet();

		//�α������� ��ο��� �����ش�.������ �츮�� �ʿ������??
		//�⺻��������

		SC_ADD_PLAYER_PACKET add_packet;
		add_packet.id = c_id;
		strcpy_s(add_packet.name, p->name);
		add_packet.size = sizeof(add_packet);
		add_packet.type = SC_ADD_PLAYER;
		add_packet.x = clients[c_id].x;
		add_packet.y = clients[c_id].y;

		break;
	}
	case CS_LOGIN_TEST: 
	{

		CS_INGAME_PACKET* p = reinterpret_cast<CS_INGAME_PACKET*>(packet);
		

		memcpy(&clients[c_id].name, p->name, NAME_LEN);

		printf("[CS_LOGIN_TEST ��Ŷ ������] %s \n", clients[c_id].name);

		for (auto& item : ItemList) {
			clients[c_id].send(&item.second);
			printf("[%d] item:%d pId:%d\n", c_id, item.second.item,item.second.playerId);

		}
		break;
	
	}
	case CS_MOVE: {
		CS_MOVE_PACKET* p = reinterpret_cast<CS_MOVE_PACKET*>(packet);
		clients[c_id].x = p->direction;
		printf("[%d] x:%d\n", c_id, clients[c_id].x);
		break;
	}

	case SC_CS_ITEM_REGISTER: {
		printf("[SC_CS_ITEM_REGISTER] ó��\n");
		
		CS_SC_ITEM_PACKET* p = reinterpret_cast<CS_SC_ITEM_PACKET*>(packet);

		CS_SC_ITEM_PACKET temp;
		memcpy(&temp, p, sizeof(CS_SC_ITEM_PACKET));
		
		static unsigned int rCount = 0;
		temp.registerId = rCount;
		temp.playerId = c_id; //�ϴ� c_id����µ� 

		printf("[TEMP CS_SC_ITEM_PACKET ����] [size:%d] [registerId:%d] [item:%d] [total:%d] [playerId:%d] [price:%d]\n",
			temp.size, temp.registerId, temp.item, temp.total , temp.playerId,temp.price);

		ItemList.insert({ rCount++,temp });

		//���Ŭ���̾�Ʈ���� ������Ʈ�� �����۸���Ʈ�� ��������.
		for (auto& pl : clients) {
			if (pl.ingame) {
				pl.send(&temp);
				printf("[TEMP CS_SC_ITEM_PACKET ����] [size:%d] [registerId:%d] [item:%d] [total:%d] [playerId:%d] [price:%d]\n",
					temp.size, temp.registerId, temp.item, temp.total, temp.playerId, temp.price);
			}
		}
		break;
	}
	case CS_CLICKED_BUY: {
		printf("[CS_CLICKED_BUY] ó��\n");
		CS_BUY_PACKET* p = reinterpret_cast<CS_BUY_PACKET*>(packet);

		//Ű���̿��ؼ� playerid �����ϰ�
		int pId = ItemList[p->rId].playerId;
	
		//�׸��� �������� SC_BUY_PACKET->�����ؾ���
		for (auto& pl : clients) {
			if (pl.id == pId) {
				SC_RECEIVE_GOLD_PACKET temp;
				temp.size = sizeof(SC_RECEIVE_GOLD_PACKET);
				temp.type = SC_RECEIVE_GOLD;
				temp.price = ItemList[p->rId].price;
				//send������ϴµ� �ϴ� ����
				pl.send(&temp);
				printf("[player : %d] ���� [price:%d]�� �ش�.\n", ItemList[p->rId].playerId, ItemList[p->rId].price);
				break; 
			}
		}



		//��� Ŭ�󿡰� �������� �� �˷���
		//Ŭ�� unordered_map���� �ٲٰ� id�� �˷��ִ� �������� ���°� ��������
		
		printf("[SC_DELETE_ITEM_PAKCET ��������� ���� ����] [registerId:%d] [total:%d]\n", p->rId, ItemList[p->rId].total );

		SC_DELETE_ITEM_PAKCET temp;
		temp.size = sizeof(SC_DELETE_ITEM_PAKCET);
		temp.type = SC_DELETE_ITEM;
		temp.rId = p->rId;
		temp.total = --ItemList[p->rId].total;
		printf("[SC_DELETE_ITEM_PAKCET ��������] [registerId:%d] [total:%d]\n", temp.rId, temp.total);

		for (auto& pl : clients) {
			if (pl.ingame) {
				pl.send(&temp);
				printf("[SC_DELETE_ITEM_PAKCET ����] [registerId:%d] [total:%d]\n", temp.rId,temp.total);
			}
		}
		if (ItemList[p->rId].total == 0) {
			ItemList.erase(p->rId);

		}
	
		break;
	}

	}

}
			

	






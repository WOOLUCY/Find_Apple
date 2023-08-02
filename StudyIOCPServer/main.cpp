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
			printf("OP_ACCETP함수 호출\n");

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

		printf("[CS_LOGIN] 함수 호출함\n");

		CS_LOGIN_PACKET* p = reinterpret_cast<CS_LOGIN_PACKET*>(packet);
		strcpy(clients[c_id].name, p->name);
		clients[c_id].send_login_info_packet();

		//로그인정보 모두에게 보내준다.ㄱ느데 우리는 필요없을듯??
		//기본정보를돈

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

		printf("[CS_LOGIN_TEST 패킷 도착함] %s \n", clients[c_id].name);

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
		printf("[SC_CS_ITEM_REGISTER] 처리\n");
		
		CS_SC_ITEM_PACKET* p = reinterpret_cast<CS_SC_ITEM_PACKET*>(packet);

		CS_SC_ITEM_PACKET temp;
		memcpy(&temp, p, sizeof(CS_SC_ITEM_PACKET));
		
		static unsigned int rCount = 0;
		temp.registerId = rCount;
		temp.playerId = c_id; //일단 c_id로줬는데 

		printf("[TEMP CS_SC_ITEM_PACKET 받음] [size:%d] [registerId:%d] [item:%d] [total:%d] [playerId:%d] [price:%d]\n",
			temp.size, temp.registerId, temp.item, temp.total , temp.playerId,temp.price);

		ItemList.insert({ rCount++,temp });

		//모든클라이언트에게 업데이트된 아이템리스트를 보내보자.
		for (auto& pl : clients) {
			if (pl.ingame) {
				pl.send(&temp);
				printf("[TEMP CS_SC_ITEM_PACKET 보냄] [size:%d] [registerId:%d] [item:%d] [total:%d] [playerId:%d] [price:%d]\n",
					temp.size, temp.registerId, temp.item, temp.total, temp.playerId, temp.price);
			}
		}
		break;
	}
	case CS_CLICKED_BUY: {
		printf("[CS_CLICKED_BUY] 처리\n");
		CS_BUY_PACKET* p = reinterpret_cast<CS_BUY_PACKET*>(packet);

		//키값이용해서 playerid 저장하고
		int pId = ItemList[p->rId].playerId;
	
		//그리고 돈보내줘 SC_BUY_PACKET->여기해야함
		for (auto& pl : clients) {
			if (pl.id == pId) {
				SC_RECEIVE_GOLD_PACKET temp;
				temp.size = sizeof(SC_RECEIVE_GOLD_PACKET);
				temp.type = SC_RECEIVE_GOLD;
				temp.price = ItemList[p->rId].price;
				//send해줘야하는데 일단 ㄱㄷ
				pl.send(&temp);
				printf("[player : %d] 에게 [price:%d]를 준다.\n", ItemList[p->rId].playerId, ItemList[p->rId].price);
				break; 
			}
		}



		//모든 클라에게 삭제정보 다 알려줘
		//클라도 unordered_map으로 바꾸고 id를 알려주는 방향으로 가는게 나을지도
		
		printf("[SC_DELETE_ITEM_PAKCET 보내기더더 빼기 더전] [registerId:%d] [total:%d]\n", p->rId, ItemList[p->rId].total );

		SC_DELETE_ITEM_PAKCET temp;
		temp.size = sizeof(SC_DELETE_ITEM_PAKCET);
		temp.type = SC_DELETE_ITEM;
		temp.rId = p->rId;
		temp.total = --ItemList[p->rId].total;
		printf("[SC_DELETE_ITEM_PAKCET 보내기전] [registerId:%d] [total:%d]\n", temp.rId, temp.total);

		for (auto& pl : clients) {
			if (pl.ingame) {
				pl.send(&temp);
				printf("[SC_DELETE_ITEM_PAKCET 보냄] [registerId:%d] [total:%d]\n", temp.rId,temp.total);
			}
		}
		if (ItemList[p->rId].total == 0) {
			ItemList.erase(p->rId);

		}
	
		break;
	}

	}

}
			

	






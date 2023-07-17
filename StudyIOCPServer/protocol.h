#pragma once
constexpr int PORT_NUM = 4000;
constexpr int BUF_SIZE = 256;
constexpr int NAME_LEN = 20;


// Packet ID, type
constexpr char CS_LOGIN = 0;
constexpr char CS_MOVE = 1; //�̰� �ʿ��Ѱ�??
constexpr char CS_GETITEM = 2;
constexpr char CS_THROWITEM = 3;
constexpr char CS_TEST = 8;


constexpr char SC_LOGIN_INFO = 4;
constexpr char SC_ADD_PLAYER = 5;
constexpr char SC_REMOVE_PLAYER = 6;
constexpr char SC_MOVE_PLAYER = 7;

//���� �ʿ��ѰŸ� �ؿ��ٰ� ��������

constexpr char SC_CS_ITEM_REGISTER = 10;	//���� testpacket�װ���
constexpr char CS_CLICKED_BUY = 12;			//Ŭ���̾�Ʈ���� ���ǻ�����
constexpr char SC_RECEIVE_GOLD = 13;


constexpr char CS_LOGIN_TEST = 11;

//Kind Of Item
constexpr int RADISH = 0;
constexpr int CARROT = 1;
constexpr int KOHLRABI = 2;
constexpr int WARTERMELON = 4;
constexpr int TOMATO = 5;
constexpr int CUCUMBER = 6;
constexpr int YELLOMELON = 7;
constexpr int CACTUS = 8;
constexpr int ORANGE = 9;
constexpr int APPLE = 100;

constexpr int GOLD = 11;
constexpr int IRON = 12;
constexpr int RUBBY = 13;
constexpr int SAPPHIRE = 14;
constexpr int ROCK = 15;
constexpr int TRUNK = 16;
constexpr int BRANCH = 17;
constexpr int  SEED = 18;


#pragma pack (push, 1)
//Client To Server Packets
struct CS_LOGIN_PACKET {
	unsigned char size;
	char	type; 
	char	name[NAME_LEN];
};

struct CS_MOVE_PACKET {
	unsigned char size;
	char	type;
	char	direction;  // 0 : UP, 1 : DOWN, 2 : LEFT, 3 : RIGHT
};

struct CS_ITEM_PACKET {
	unsigned char size;
	char	type;
	char	itemType;
};

struct CS_TEST_PACKET {
	unsigned char size;
	char	type;
	char	test;

};
struct CS_INGAME_TEST_PACKET {
	unsigned char size;
	char	type;
	bool	isIn;

};

//�����ϱ� �������� Ŭ�� ������ ������Ŷ
struct CS_BUY_PACKET {
	unsigned char size;
	char	type;
	unsigned int rId; //registerId

};


//Server To Client Packets
struct SC_LOGIN_INFO_PACKET {
	unsigned char size;
	char	type;
	short	id;
	short	x, y;
};

struct SC_ADD_PLAYER_PACKET {
	unsigned char size;
	char	type;
	short	id;
	short	x, y;
	char	name[NAME_LEN];
};

struct SC_REMOVE_PLAYER_PACKET {
	unsigned char size;
	char	type;
	short	id;
};

struct SC_MOVE_PLAYER_PACKET {
	unsigned char size;
	char	type;
	short	id;
	short	x, y;
};

struct SC_TEST_PACKET {
	unsigned char size;
	char	type;
	short	id; //������ ���̵� �����ϱ�
	char	test; 

};

struct CS_SC_ITEM_PACKET {
	unsigned char size;
	char			type = SC_CS_ITEM_REGISTER;
	unsigned int	registerId;	//�Ǹ��ϴ°͸��� ������ȣ��
	short			playerId;		//������� ���̵� ����
	short			item;		
	short			total;
	short			price;


};


struct SC_BUY_PACKET { //����Ѿ����� ������ �Ѵ�. �׷��� ���޴´�. 
	unsigned char size;
	char	type;
	short	price;

};



#pragma pack (pop)
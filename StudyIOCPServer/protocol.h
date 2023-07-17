#pragma once
constexpr int PORT_NUM = 4000;
constexpr int BUF_SIZE = 256;
constexpr int NAME_LEN = 20;


// Packet ID, type
constexpr char CS_LOGIN = 0;
constexpr char CS_MOVE = 1; //이거 필요한가??
constexpr char CS_GETITEM = 2;
constexpr char CS_THROWITEM = 3;
constexpr char CS_TEST = 8;


constexpr char SC_LOGIN_INFO = 4;
constexpr char SC_ADD_PLAYER = 5;
constexpr char SC_REMOVE_PLAYER = 6;
constexpr char SC_MOVE_PLAYER = 7;

//정말 필요한거를 밑에다가 적오보자

constexpr char SC_CS_ITEM_REGISTER = 10;	//원래 testpacket그거임
constexpr char CS_CLICKED_BUY = 12;			//클라이언트에서 물건샀을때
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

//구매하기 눌렀을때 클라가 서버에 보낼패킷
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
	short	id; //보낸쪽 아이디 저장하기
	char	test; 

};

struct CS_SC_ITEM_PACKET {
	unsigned char size;
	char			type = SC_CS_ITEM_REGISTER;
	unsigned int	registerId;	//판매하는것마다 고유번호임
	short			playerId;		//등록한쪽 아이디 저장
	short			item;		
	short			total;
	short			price;


};


struct SC_BUY_PACKET { //등록한애한테 보내야 한다. 그래야 돈받는다. 
	unsigned char size;
	char	type;
	short	price;

};



#pragma pack (pop)
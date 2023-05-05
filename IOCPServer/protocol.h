constexpr int PORTNUM = 4000;
constexpr int BUFSIZE = 256;
constexpr int NAMESIZE = 20;

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
constexpr char SC_TEST = 9;



enum ITEM_TYPE { BRANCH, BUNDLE, ROCK, SEED };

#pragma pack (push, 1)
//Client To Server Packets
struct CS_LOGIN_PACKET {
	unsigned char size;
	char	type;
	char	name[NAMESIZE];
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
	char	name[NAMESIZE];
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

//


#pragma pack (pop)
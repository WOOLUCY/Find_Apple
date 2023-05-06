constexpr int PORT_NUM = 4000;
constexpr int BUF_SIZE = 200;
constexpr int NAME_LEN = 20;
//
//constexpr int W_WIDTH = 8;
//constexpr int W_HEIGHT = 8;

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

constexpr char TESTPACKET = 10;


//enum ITEM_TYPE{BRANCH, BUNDLE,ROCK, SEED};
enum ITEM_TYPE{APPLE, ORANGE,FIREWOOD, ROCK, BRAHCN, SEED,GOLD, STEEL, RADISH };

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

struct SC_CS_TESTPACKET {
	unsigned char size;
	char	type = TESTPACKET;
	int		item;
	int		testNum;
	int		testPrice;

};

//


#pragma pack (pop)
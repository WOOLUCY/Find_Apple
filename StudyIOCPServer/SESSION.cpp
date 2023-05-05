#include "SESSION.h"

void SESSION::recv()
{
	DWORD recvFlag = 0; 
	memset(&recvOver.Over, 0, sizeof(recvOver.Over));
	recvOver.wsaBuf.len = BUFSIZE - prevRemain;
	recvOver.wsaBuf.buf = recvOver.sendBuf + prevRemain;
	WSARecv(socket, &recvOver.wsaBuf, 1, 0, &recvFlag,
		&recvOver.Over, 0);
	printf("SESSION::Recv완료\n");

}

void SESSION::send(void* packet)
{
	EXP_OVER* sdata = new EXP_OVER{ reinterpret_cast<char*>(packet) };
	WSASend(socket, &sdata->wsaBuf, 1, 0, 0, &sdata->Over, 0);

	printf("SESSION::send완료 \n");

}

void SESSION::SendMovePacket(int id)
{
	//send()무브패킷어쩌ㅜ저쩌구
	cout << "무브패킷" << endl;

	
}

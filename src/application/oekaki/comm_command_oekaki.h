#ifndef __COMM_COMMAND_OEKAKI_H__
#define __COMM_COMMAND_OEKAKI_H__


#include "communication/comm_command.h"
#include "../../field/comm_command_field.h"


// �T�l�ڑ��ʐM�̎��Ƀ��[�U�[���q�@�Ƃ��đ��M�ł���ő��M�o�C�g��
#define COMM_SEND_5TH_PACKET_MAX	(10)


extern void CommCommandOekakiBoardInitialize(void* pWork);

extern void CommOekakiBoardPicture(int netID, int size, void* pBuff, void* pWork);
extern void CommOekakiBoardLinePos(int netID, int size, void* pBuff, void* pWork);
extern void CommOekakiBoardLinePosServer(int netID, int size, void* pBuff, void* pWork);
extern void CommOekakiBoardYes(int netID, int size, void* pBuff, void* pWork);
extern void CommOekakiBoardNo(int netID, int size, void* pBuff, void* pWork);
extern void CommOekakiBoardStop(int netID, int size, void* pBuff, void* pWork);
extern void CommOekakiBoardReStart(int netID, int size, void* pBuff, void* pWork);
extern void CommOekakiBoardEndQuestion(int netID, int size, void* pBuff, void* pWork);
extern void CommOekakiBoardEndChild(int netID, int size, void* pBuff, void* pWork);
extern void CommOekakiBoardEnd(int netID, int size, void* pBuff, void* pWork);
extern void CommOekakiBoardChildJoin(int netID, int size, void* pBuff, void* pWork);


#endif

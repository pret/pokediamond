#ifndef __COMM_COMMAND_RECORD_H__
#define __COMM_COMMAND_RECORD_H__


#include "communication/comm_command.h"
#include "../../field/comm_command_field.h"



#define RECORD_BAN_NONE		( 0 )
#define RECORD_BAN_ON		( 1 )
#define RECORD_BAN_MOST_ON	( 2 )

extern void CommCommandRecordCornerInitialize(void* pWork);

extern void CommRecordCornerYes(int netID, int size, void* pBuff, void* pWork);
extern void CommRecordCornerNo(int netID, int size, void* pBuff, void* pWork);
extern void CommRecordCornerStop(int netID, int size, void* pBuff, void* pWork);
extern void CommRecordCornerReStart(int netID, int size, void* pBuff, void* pWork);
extern void CommRecordCornerEndChild(int netID, int size, void* pBuff, void* pWork);
extern void CommRecordCornerEnd(int netID, int size, void* pBuff, void* pWork);
extern void CommRecordCornerChildJoin(int netID, int size, void* pBuff, void* pWork);
extern void CommRecordStart(int netID, int size, void* pBuff, void* pWork);

#endif

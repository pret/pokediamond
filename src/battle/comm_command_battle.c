//=============================================================================
/**
 * @file	comm_command_battle.c
 * @brief	�f�[�^�𑗂邽�߂̃R�}���h���e�[�u�������Ă��܂�
 *          �o�g���p�ł�
 *          comm_command_battle.h �� enum �Ɠ������тł���K�v������܂�
 * @author	Katsumi Ohno
 * @date    2005.11.08
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_command_battle.h"
#include "savedata/perapvoice.h"
#include "savedata/friendlist_local.h"

#include "battle/fight_tool.h"

#ifdef DEBUG_ONLY_FOR_sogabe
//#define	SIO_COMMENT_ON
#define	RECV_COMMENT_ON
#endif

//==============================================================================
//  �e�[�u���ɏ����֐��̒�`
//==============================================================================

//==============================================================================
//  �v���g�^�C�v�錾
//==============================================================================

void CommCommandBattleSendData(BATTLE_WORK *bw,int access,int para,void *data,u8 size);
BOOL CommCommandBattleSendServerVersionData(BATTLE_SIO_WORK *bsw,u32 version);
BOOL CommCommandBattleSendMyStatusDataMake(BATTLE_SIO_WORK *bsw);
BOOL CommCommandBattleSendMyStatusDataWait(BATTLE_SIO_WORK *bsw);
BOOL CommCommandBattleSendTrainerDataMake(BATTLE_SIO_WORK *bsw);
BOOL CommCommandBattleSendTrainerDataWait(BATTLE_SIO_WORK *bsw);
BOOL CommCommandBattleSendPokeDataMake(BATTLE_SIO_WORK *bsw);
BOOL CommCommandBattleSendPokeDataWait(BATTLE_SIO_WORK *bsw);
BOOL CommCommandBattleSendPokeVoiceMake(BATTLE_SIO_WORK *bsw);
BOOL CommCommandBattleSendPokeVoiceWait(BATTLE_SIO_WORK *bsw);
BOOL CommCommandBattleSendTowerTrDataMake(BATTLE_SIO_WORK *bsw,int no);
BOOL CommCommandBattleSendTowerTrDataWait(BATTLE_SIO_WORK *bsw,int no,int sync_num);
BOOL CommCommandBattleSendTowerPokeDataMake(BATTLE_SIO_WORK *bsw,int no);
BOOL CommCommandBattleSendTowerPokeDataWait(BATTLE_SIO_WORK *bsw,int no,int sync_num);
void CommCommandBattleCPInitialize(void* pWork);

BOOL CommCommandBattleSendFriendListWait(BATTLE_SIO_WORK *bsw);
BOOL CommCommandBattleSendFriendListMake(BATTLE_SIO_WORK *bsw);


//==============================================================================
//  static��`
//==============================================================================
static int _getServerVersion(void);
static int _getMyStatus(void);
static int _getTrainerData(void);
static int _getPokeData(void);
static int _getPokeVoice(void);
static int _getTTData(void);
static int _getFriendListSize(void);

static u8	* _getMyStatusBufAdrs(int netID,void *pWork,int size);
static u8	* _getTrainerBufAdrs(int netID,void *pWork,int size);
static u8	* _getPokemonBufAdrs(int netID,void *pWork,int size);
static u8	* _getPokeVoiceBufAdrs(int netID,void *pWork,int size);
static u8	* _getTTData1BufAdrs(int netID,void *pWork,int size);
static u8	* _getTTData2BufAdrs(int netID,void *pWork,int size);
static u8	* _getTPData1BufAdrs(int netID,void *pWork,int size);
static u8	* _getTPData2BufAdrs(int netID,void *pWork,int size);
static u8   * _getFriendListBufAdrs( int netID, void *pWork, int size );

static	void CommCommandBattleRecvData(int id_no,int size,void *pData,void *work);
static	void CommCommandBattleRecvServerVersionData(int id_no,int size,void *pData,void *work);
static	void CommCommandBattleRecvMyStatusData(int id_no,int size,void *pData,void *work);
static	void CommCommandBattleRecvTrainerData(int id_no,int size,void *pData,void *work);
static	void CommCommandBattleRecvPokeData(int id_no,int size,void *pData,void *work);
static	void CommCommandBattleRecvPokeVoice(int id_no,int size,void *pData,void *work);
static	void CommCommandBattleRecvTTData(int id_no,int size,void *pData,void *work);
static	void CommCommandBattleRecvTPData(int id_no,int size,void *pData,void *work);
static	void CommCommandBattleEnd(int id_no,int size,void *pData,void *work);
static	void TCB_CommCommandBattleSendData(TCB_PTR tcb,void *work);
static	void TCB_CommCommandBattleRecvData(TCB_PTR tcb,void *work);
static  void CommCommandBattleRecvFriendList(int netID, int size, void* pBuff, void* pWork);
static  void CommCommandBattleMakeFriendList( MYSTATUS *mystatus, FRIEND_LIST *friendlist, FRIEND_LIST *sendbuf );

//==============================================================================
//	�e�[�u���錾
//  comm_command_battle.h �� enum �Ɠ����Ȃ�тɂ��Ă�������
//  CALLBACK���Ă΂ꂽ���Ȃ��ꍇ��NULL�������Ă�������
//  �R�}���h�̃T�C�Y��Ԃ��֐��������Ă��炦��ƒʐM���y���Ȃ�܂�
//  _getZero�̓T�C�Y�Ȃ���Ԃ��܂��B_getVariable�͉σf�[�^�g�p���Ɏg���܂�
//  comm_command_field.c���Q�l�ɂ��Ă݂Ă�������
//==============================================================================
static const CommPacketTbl _CommPacketTbl[] = {
    {CommCommandBattleEnd,					_getZero,			NULL},					// CB_EXIT_BATTLE
	{CommCommandBattleRecvData,				_getVariable,		NULL},					// CB_BATTLE_DATA
	{CommCommandBattleRecvServerVersionData,_getServerVersion,	NULL},					// CB_BATTLE_SERVER_VERSION_DATA
	{CommCommandBattleRecvMyStatusData,		_getMyStatus,		_getMyStatusBufAdrs},	// CB_BATTLE_MYSTATUS_DATA
	{CommCommandBattleRecvTrainerData,		_getTTData,			_getTrainerBufAdrs},	// CB_BATTLE_POKE_DATA
	{CommCommandBattleRecvPokeData,			_getPokeData,		_getPokemonBufAdrs},	// CB_BATTLE_POKE_DATA
	{CommCommandBattleRecvPokeVoice,		_getPokeVoice,		_getPokeVoiceBufAdrs},	// CB_BATTLE_POKE_VOICE
	{CommCommandBattleRecvTTData,			_getTTData,			_getTTData1BufAdrs},	// CB_BATTLE_TTDATA1
	{CommCommandBattleRecvTTData,			_getTTData,			_getTTData2BufAdrs},	// CB_BATTLE_TTDATA2
	{CommCommandBattleRecvTPData,			_getPokeData,		_getTPData1BufAdrs},	// CB_BATTLE_TPDATA1
	{CommCommandBattleRecvTPData,			_getPokeData,		_getTPData2BufAdrs},	// CB_BATTLE_TPDATA2
	{CommCommandBattleRecvFriendList,       _getFriendListSize, _getFriendListBufAdrs },// CB_BATTLE_FRIEND_LIST,	
};

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM�̏��������s���܂�
 * @param   pWork   �o�g���Ŏg�p���郏�[�N�̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

void CommCommandBattleInitialize(void* pWork)
{
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);
	BATTLE_WORK		*bw;
	TCB_SIO_SEND	*tss;
	TCB_SIO_RECV	*tsr;

	bw=(BATTLE_WORK *)pWork;
	tss=(TCB_SIO_SEND *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_SIO_SEND));
	tsr=(TCB_SIO_RECV *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_SIO_RECV));

    CommCommandInitialize(_CommPacketTbl, length, pWork);

	tss->bw=bw;
	tss->seq_no=0;
	tsr->bw=bw;
	tsr->seq_no=0;

	BattleWorkTSSSeqNoAdrsSet(bw,&tss->seq_no);
	BattleWorkTSRSeqNoAdrsSet(bw,&tsr->seq_no);

	TCB_Add(TCB_CommCommandBattleSendData,tss,0);
	TCB_Add(TCB_CommCommandBattleRecvData,tsr,0);
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM�̏��������s���܂��i�ŏ��̎莝���̌����p�j
 * @param   pWork   �o�g���Ŏg�p���郏�[�N�̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

void CommCommandBattleCPInitialize(void* pWork)
{
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);

    CommCommandInitialize(_CommPacketTbl, length, pWork);
}

//--------------------------------------------------------------
/**
 * @brief   �R�Ƃ��T�C�Y��Ԃ��܂�
 * @param   command         �R�}���h
 * @retval  �T�C�Y   �ςȂ� COMM_VARIABLE_SIZE Zero�͂O��Ԃ�
 */
//--------------------------------------------------------------
static int _getServerVersion(void)
{
    return 4;
}

static int _getMyStatus(void)
{
    return MyStatus_GetWorkSize();
}

static int _getPokeData(void)
{
    return PokeParty_GetWorkSize();
}

static int _getPokeVoice(void)
{
    return PERAPVOICE_LENGTH;
}

static int _getTTData(void)
{
	return sizeof(TRAINER_DATA);
}

static u8	* _getMyStatusBufAdrs(int netID,void *pWork,int size)
{
	BATTLE_SIO_WORK *bsw=pWork;

	if(bsw->bp->fight_type&FIGHT_TYPE_TOWER){
		return	(u8 *)bsw->bp->my_status[netID*2];
	}
	else{
		return	(u8 *)bsw->bp->my_status[netID];
	}
}

static u8	* _getTrainerBufAdrs(int netID,void *pWork,int size)
{
	BATTLE_SIO_WORK *bsw=pWork;

	if(bsw->bp->fight_type&FIGHT_TYPE_TOWER){
		return	(u8 *)&bsw->bp->trainer_data[netID*2];
	}
	else{
		return	(u8 *)&bsw->bp->trainer_data[netID];
	}
}

static u8	* _getPokemonBufAdrs(int netID,void *pWork,int size)
{
	BATTLE_SIO_WORK *bsw=pWork;

	if(bsw->bp->fight_type&FIGHT_TYPE_TOWER){
		return	(u8 *)bsw->bp->poke_party[netID*2];
	}
	else{
		return	(u8 *)bsw->bp->poke_party[netID];
	}
}

static u8	* _getPokeVoiceBufAdrs(int netID,void *pWork,int size)
{
	BATTLE_SIO_WORK *bsw=pWork;

	if(bsw->bp->fight_type&FIGHT_TYPE_TOWER){
		return	(u8 *)bsw->bp->poke_voice[netID*2];
	}
	else{
		return	(u8 *)bsw->bp->poke_voice[netID];
	}
}

static u8	* _getTTData1BufAdrs(int netID,void *pWork,int size)
{
	BATTLE_SIO_WORK *bsw=pWork;

	return	(u8 *)&bsw->bp->trainer_data[CLIENT_NO_ENEMY];
}

static u8	* _getTTData2BufAdrs(int netID,void *pWork,int size)
{
	BATTLE_SIO_WORK *bsw=pWork;

	return	(u8 *)&bsw->bp->trainer_data[CLIENT_NO_ENEMY2];
}

static u8	* _getTPData1BufAdrs(int netID,void *pWork,int size)
{
	BATTLE_SIO_WORK *bsw=pWork;

	return	(u8 *)bsw->bp->poke_party[CLIENT_NO_ENEMY];
}

static u8	* _getTPData2BufAdrs(int netID,void *pWork,int size)
{
	BATTLE_SIO_WORK *bsw=pWork;

	return	(u8 *)bsw->bp->poke_party[CLIENT_NO_ENEMY2];
}

static u8   * _getFriendListBufAdrs( int netID, void *pWork, int size )
{
	BATTLE_SIO_WORK *bsw=pWork;
	
	return (u8*)bsw->recv_flist[netID];
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���M����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
void CommCommandBattleSendData(BATTLE_WORK *bw,int access,int para,void *data,u8 size)
{
	int				i;
	SIO_SEND_DATA	*ssd;
	u8				*src;
	u8				*dest;
	u16				*write;
	u16				*over;

	ssd=(SIO_SEND_DATA *)sys_AllocMemory(HEAPID_BATTLE,sizeof(SIO_SEND_DATA));
	dest=BattleWorkSioSendBufGet(bw);
	write=BattleWorkSioSendWriteGet(bw);
	over=BattleWorkSioSendOverGet(bw);

	//�����Que�ւ̏������݂Ńo�b�t�@�I�[�o�[���邩�`�F�b�N
	if(write[0]+sizeof(SIO_SEND_DATA)+size+1>BATTLE_SIO_BUF_SIZE){
	//�I�[�o�[�����ꍇ�́Aover�o�b�t�@�ɂ��̎|���i�[
	//write�o�b�t�@��擪�ɖ߂�
		over[0]=write[0];
		write[0]=0;
	}

	ssd->access=access;
	ssd->para=para;
	ssd->size=size;

	src=(u8 *)ssd;

	for(i=0;i<sizeof(SIO_SEND_DATA);i++){
		dest[write[0]]=src[i];
		write[0]++;
	}

	src=(u8 *)data;

	for(i=0;i<size;i++){
		dest[write[0]]=src[i];
		write[0]++;
	}

#ifdef SIO_COMMENT_ON
	OS_Printf("���M�v������܂���: w->%04x o->%04x \n",write[0],over[0]);
#endif

	sys_FreeMemoryEz(ssd);
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM��M����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static	void CommCommandBattleRecvData(int id_no,int size,void *pData,void *work)
{
	BATTLE_WORK		*bw=(BATTLE_WORK *)work;
	int				i;
	u8				*src=(u8 *)pData;
	u8				*dest=BattleWorkSioRecvBufGet(bw);
	u16				*write=BattleWorkSioRecvWriteGet(bw);
	u16				*over=BattleWorkSioRecvOverGet(bw);

	//�����Que�ւ̏������݂Ńo�b�t�@�I�[�o�[���邩�`�F�b�N
	if(write[0]+size+1>BATTLE_SIO_BUF_SIZE){
	//�I�[�o�[�����ꍇ�́Aover�o�b�t�@�ɂ��̎|���i�[
	//write�o�b�t�@��擪�ɖ߂�
		over[0]=write[0];
		write[0]=0;
	}

#ifdef SIO_COMMENT_ON
	OS_Printf("��M�v������܂���: size->%d w->%04x o->%04x \n",size,write[0],over[0]);
#endif

	for(i=0;i<size;i++){
		dest[write[0]]=src[i];
		write[0]++;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���M����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
BOOL CommCommandBattleSendServerVersionData(BATTLE_SIO_WORK *bsw,u32 version)
{
	POKEPARTY	*ppt;

	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A���M���Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	//�����҂�
	if(CommIsTimingSync(COMM_BATTLE_SV_SYNC_NUM)==FALSE){
		return FALSE;
	}

#ifdef PM_DEBUG
	version+=((bsw->bp->battle_status_flag&0xf0000000)>>28);
#endif PM_DEBUG

	return CommSendData(CB_BATTLE_SERVER_VERSION_DATA,(void *)&version,4);
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���MTCB�p�V�[�P���X�i���o�[��`
 */
//--------------------------------------------------------------
static	void CommCommandBattleRecvServerVersionData(int id_no,int size,void *pData,void *work)
{
	BATTLE_SIO_WORK		*bsw=(BATTLE_SIO_WORK *)work;

	bsw->bp->server_version[id_no]=*((u32 *)pData);

#ifdef	RECV_COMMENT_ON
	OS_TPrintf("Recv:ServerVersion:%d\n",id_no);
#endif	RECV_COMMENT_ON

	bsw->send_count++;
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���M����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
BOOL CommCommandBattleSendMyStatusDataMake(BATTLE_SIO_WORK *bsw)
{
	MYSTATUS	*ms;

	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A�������Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	ms=(MYSTATUS *)&bsw->sio_send_buffer[0];

	MyStatus_Copy(bsw->bp->my_status[0],ms);

	return TRUE;
}

BOOL CommCommandBattleSendMyStatusDataWait(BATTLE_SIO_WORK *bsw)
{
	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A���M���Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	//�����҂�
	if(CommIsTimingSync(COMM_BATTLE_MS_SYNC_NUM)==FALSE){
		return FALSE;
	}

	return CommSendHugeData(CB_BATTLE_MYSTATUS_DATA,(void *)&bsw->sio_send_buffer[0],MyStatus_GetWorkSize());
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���MTCB�p�V�[�P���X�i���o�[��`
 */
//--------------------------------------------------------------
static	void CommCommandBattleRecvMyStatusData(int id_no,int size,void *pData,void *work)
{
	BATTLE_SIO_WORK		*bsw=(BATTLE_SIO_WORK *)work;

#ifdef	RECV_COMMENT_ON
	OS_TPrintf("Recv:MyStatus:%d\n",id_no);
#endif	RECV_COMMENT_ON

	bsw->send_count++;
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���M����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
BOOL CommCommandBattleSendTrainerDataMake(BATTLE_SIO_WORK *bsw)
{
	TRAINER_DATA	*td;

	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A�������Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	td=(TRAINER_DATA *)&bsw->sio_send_buffer[0];

	*td=bsw->bp->trainer_data[0];

	return TRUE;
}

BOOL CommCommandBattleSendTrainerDataWait(BATTLE_SIO_WORK *bsw)
{
	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A���M���Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	//�����҂�
	if(CommIsTimingSync(COMM_BATTLE_TR_SYNC_NUM)==FALSE){
		return FALSE;
	}

	return CommSendHugeData(CB_BATTLE_TRAINER_DATA,(void *)&bsw->sio_send_buffer[0],sizeof(TRAINER_DATA));
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���MTCB�p�V�[�P���X�i���o�[��`
 */
//--------------------------------------------------------------
static	void CommCommandBattleRecvTrainerData(int id_no,int size,void *pData,void *work)
{
	BATTLE_SIO_WORK		*bsw=(BATTLE_SIO_WORK *)work;

#ifdef	RECV_COMMENT_ON
	OS_TPrintf("Recv:TrainerData:%d\n",id_no);
#endif	RECV_COMMENT_ON

	bsw->send_count++;
}


//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���M����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
BOOL CommCommandBattleSendPokeDataMake(BATTLE_SIO_WORK *bsw)
{
	POKEPARTY	*ppt;

	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A�������Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	ppt=(POKEPARTY *)&bsw->sio_send_buffer[0];

	PokeParty_Copy(bsw->bp->poke_party[0],ppt);

	return TRUE;
}

BOOL CommCommandBattleSendPokeDataWait(BATTLE_SIO_WORK *bsw)
{
	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A���M���Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	//�����҂�
	if(CommIsTimingSync(COMM_BATTLE_POKE_SYNC_NUM)==FALSE){
		return FALSE;
	}

	return CommSendHugeData(CB_BATTLE_POKE_DATA,(void *)&bsw->sio_send_buffer[0],PokeParty_GetWorkSize());
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���MTCB�p�V�[�P���X�i���o�[��`
 */
//--------------------------------------------------------------
static	void CommCommandBattleRecvPokeData(int id_no,int size,void *pData,void *work)
{
	BATTLE_SIO_WORK		*bsw=(BATTLE_SIO_WORK *)work;

#ifdef	RECV_COMMENT_ON
	OS_TPrintf("Recv:PokeData:%d\n",id_no);
#endif	RECV_COMMENT_ON

	bsw->send_count++;
}

//--------------------------------------------------------------
/**
 * @brief   �y���b�v�{�C�X�ʐM���M����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
BOOL CommCommandBattleSendPokeVoiceMake(BATTLE_SIO_WORK *bsw)
{
	PERAPVOICE	*pv;

	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A�������Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	pv=(PERAPVOICE *)&bsw->sio_send_buffer[0];

	PERAPVOICE_CopyData(pv,bsw->bp->poke_voice[0]);

	return TRUE;
}

BOOL CommCommandBattleSendPokeVoiceWait(BATTLE_SIO_WORK *bsw)
{
	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A���M���Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	//�����҂�
	if(CommIsTimingSync(COMM_BATTLE_POKEV_SYNC_NUM)==FALSE){
		return FALSE;
	}

	return CommSendHugeData(CB_BATTLE_POKE_VOICE,(void *)&bsw->sio_send_buffer[0],PERAPVOICE_LENGTH);
}


//--------------------------------------------------------------
/**
 * @brief   �Ƃ������O���[�v�ʐM���M����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
BOOL CommCommandBattleSendFriendListMake(BATTLE_SIO_WORK *bsw)
{
	FRIEND_LIST	*fl;
	MYSTATUS    *status;

	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A�������Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	fl=(FRIEND_LIST *)&bsw->sio_send_buffer[0];

	OS_Printf("�Ƃ������O���[�v�f�[�^�쐬�O\n");

	// �ʐM�}���`�o�g���^���[�̎��̓X�e�[�^�X�̎擾���@�������Ⴄ
	if(bsw->bp->fight_type&FIGHT_TYPE_TOWER){
		status = bsw->bp->my_status[CommGetCurrentID()*2];
	}else{
		status = bsw->bp->my_status[CommGetCurrentID()];
	}
	
	// �F�B�O���[�v�f�[�^�쐬
	CommCommandBattleMakeFriendList( status, bsw->bp->friendlist, 
									(FRIEND_LIST*)bsw->sio_send_buffer );

	{
		int i;
		for(i=0;i<CLIENT_MAX;i++){
			bsw->recv_flist[i] = sys_AllocMemory( HEAPID_BATTLE, FRIEND_LIST_SIZE );
		}
	}
	
//	PERAPVOICE_CopyData(pv,bsw->bp->poke_voice[0]);

	return TRUE;
}

BOOL CommCommandBattleSendFriendListWait(BATTLE_SIO_WORK *bsw)
{
	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A���M���Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	//�����҂�
	if(CommIsTimingSync(COMM_BATTLE_FLIST_SYNC_NUM)==FALSE){
		return FALSE;
	}

	return CommSendHugeData(CB_BATTLE_FRIEND_LIST,(void *)bsw->sio_send_buffer,PERAPVOICE_LENGTH);
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���MTCB�p�V�[�P���X�i���o�[��`
 */
//--------------------------------------------------------------
static	void CommCommandBattleRecvPokeVoice(int id_no,int size,void *pData,void *work)
{
	BATTLE_SIO_WORK		*bsw=(BATTLE_SIO_WORK *)work;

#ifdef	RECV_COMMENT_ON
	OS_TPrintf("Recv:PokeVoice:%d\n",id_no);
#endif	RECV_COMMENT_ON

	bsw->send_count++;
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���M����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
BOOL CommCommandBattleSendTowerTrDataMake(BATTLE_SIO_WORK *bsw,int no)
{
	TRAINER_DATA	*tr_data;

	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A�������Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	tr_data=(TRAINER_DATA *)&bsw->sio_send_buffer[0];

	*tr_data=bsw->bp->trainer_data[no];

	return TRUE;
}

BOOL CommCommandBattleSendTowerTrDataWait(BATTLE_SIO_WORK *bsw,int no,int sync_num)
{
	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A���M���Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	//�����҂�
	if(CommIsTimingSync(sync_num)==FALSE){
		return FALSE;
	}

	if(no==CLIENT_NO_ENEMY){
		return CommSendHugeData(CB_BATTLE_TTDATA1,(void *)&bsw->sio_send_buffer[0],sizeof(TRAINER_DATA));
	}
	else{
		return CommSendHugeData(CB_BATTLE_TTDATA2,(void *)&bsw->sio_send_buffer[0],sizeof(TRAINER_DATA));
	}
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���MTCB�p�V�[�P���X�i���o�[��`
 */
//--------------------------------------------------------------
static	void CommCommandBattleRecvTTData(int id_no,int size,void *pData,void *work)
{
	BATTLE_SIO_WORK		*bsw=(BATTLE_SIO_WORK *)work;

#ifdef	RECV_COMMENT_ON
	OS_TPrintf("Recv:TTData:%d send_count:%d\n",id_no,bsw->send_count);
#endif	RECV_COMMENT_ON

	bsw->send_count++;
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���M����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
BOOL CommCommandBattleSendTowerPokeDataMake(BATTLE_SIO_WORK *bsw,int no)
{
	POKEPARTY	*ppt;

	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A�������Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	ppt=(POKEPARTY *)&bsw->sio_send_buffer[0];

	PokeParty_Copy(bsw->bp->poke_party[no],ppt);

	return TRUE;
}

BOOL CommCommandBattleSendTowerPokeDataWait(BATTLE_SIO_WORK *bsw,int no,int sync_num)
{
	//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A���M���Ȃ�
	if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
		return FALSE;
	}

	//�����҂�
	if(CommIsTimingSync(sync_num)==FALSE){
		return FALSE;
	}

	if(no==CLIENT_NO_ENEMY){
		return CommSendHugeData(CB_BATTLE_TPDATA1,(void *)&bsw->sio_send_buffer[0],PokeParty_GetWorkSize());
	}
	else{
		return CommSendHugeData(CB_BATTLE_TPDATA2,(void *)&bsw->sio_send_buffer[0],PokeParty_GetWorkSize());
	}
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���MTCB�p�V�[�P���X�i���o�[��`
 */
//--------------------------------------------------------------
static	void CommCommandBattleRecvTPData(int id_no,int size,void *pData,void *work)
{
	BATTLE_SIO_WORK		*bsw=(BATTLE_SIO_WORK *)work;

#ifdef	RECV_COMMENT_ON
	OS_TPrintf("Recv:TPData:%d\n",id_no);
#endif	RECV_COMMENT_ON

	bsw->send_count++;
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���MTCB�p�V�[�P���X�i���o�[��`
 */
//--------------------------------------------------------------
enum{
	TSS_SEQ_SEND,
	TSS_SEQ_END=0xff
};

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���MTCB
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
void TCB_CommCommandBattleSendData(TCB_PTR tcb,void *work)
{
	TCB_SIO_SEND	*tss=(TCB_SIO_SEND *)work;
	u8				*src;
	u16				*read;
	u16				*write;
	u16				*over;
	int				size;

	src=BattleWorkSioSendBufGet(tss->bw);
	read=BattleWorkSioSendReadGet(tss->bw);
	write=BattleWorkSioSendWriteGet(tss->bw);
	over=BattleWorkSioSendOverGet(tss->bw);

	switch(tss->seq_no){
	case TSS_SEQ_SEND:
		//���M�o�b�t�@����ł͂Ȃ��Ƃ��́A���M���Ȃ�
		if(CommGetSendRestSize()!=COMM_COMMAND_SEND_SIZE_MAX){
			break;
		}
		//�o�b�t�@�̓ǂݍ��݈ʒu�Ə������݈ʒu�������Ƃ��̓f�[�^���Ȃ��̂ŁA���M���Ȃ�
		if(read[0]==write[0]){
			break;
		}
		//�o�b�t�@�̓ǂݍ��݈ʒu�ƃI�[�o�[�o�b�t�@�������Ƃ��͐擪�ɖ߂�
		if(read[0]==over[0]){
			read[0]=0;
			over[0]=0;
		}
#ifdef SIO_COMMENT_ON
		OS_Printf("�o�b�t�@�c��F%d\n",CommGetSendRestSize());
#endif
		size=sizeof(SIO_SEND_DATA)+(src[read[0]+SIO_BUF_SIZE_LOW]|(src[read[0]+SIO_BUF_SIZE_HIGH]<<8));
		if(CommSendData(CB_BATTLE_DATA,(void *)&src[read[0]],size)==TRUE){
			read[0]+=size;
#ifdef SIO_COMMENT_ON
			OS_Printf("���M�o�b�t�@�A�h���X: src->%08x\n",&src[0]);
			OS_Printf("���M�o�b�t�@�A�h���X: bw->%08x\n",BattleWorkSioSendBufGet(tss->bw));
			OS_Printf("���M���܂���: size->%04x r->%04x w->%04x o->%04x\n",size,read[0],write[0],over[0]);
			OS_Printf("�o�b�t�@�c��F%d\n",CommGetSendRestSize());
#endif
		}
		break;
	default:
	case TSS_SEQ_END:
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM���MTCB�p�V�[�P���X�i���o�[��`
 */
//--------------------------------------------------------------
enum{
	TSR_SEQ_RECV,
	TSR_SEQ_END=0xff
};

//--------------------------------------------------------------
/**
 * @brief   �o�g���R�}���h�ʐM��MTCB
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
void TCB_CommCommandBattleRecvData(TCB_PTR tcb,void *work)
{
	TCB_SIO_RECV	*tsr=(TCB_SIO_RECV *)work;
	u8				*src;
	u16				*read;
	u16				*write;
	u16				*over;
	int				size;

	src=BattleWorkSioRecvBufGet(tsr->bw);
	read=BattleWorkSioRecvReadGet(tsr->bw);
	write=BattleWorkSioRecvWriteGet(tsr->bw);
	over=BattleWorkSioRecvOverGet(tsr->bw);

	switch(tsr->seq_no){
	case TSR_SEQ_RECV:
		//�o�b�t�@�̓ǂݍ��݈ʒu�Ə������݈ʒu�������Ƃ��̓f�[�^���Ȃ��̂ŁA��M���Ȃ�
		if(read[0]==write[0]){
			break;
		}
		//�o�b�t�@�̓ǂݍ��݈ʒu�ƃI�[�o�[�o�b�t�@�������Ƃ��͐擪�ɖ߂�
		if(read[0]==over[0]){
			read[0]=0;
			over[0]=0;
		}
		SCIO_CommRecvData(tsr->bw,(void *)&src[read[0]]);
		size=sizeof(SIO_SEND_DATA)+(src[read[0]+SIO_BUF_SIZE_LOW]|(src[read[0]+SIO_BUF_SIZE_HIGH]<<8));
		read[0]+=size;
#ifdef SIO_COMMENT_ON
		OS_Printf("��M���܂���; r->%04x w->%04x o->%04x\n",read[0],write[0],over[0]);
#endif
		break;
	default:
	case TSR_SEQ_END:
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�I������
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
static	void CommCommandBattleEnd(int id_no,int size,void *pData,void *work)
{
	BATTLE_WORK		*bw=(BATTLE_WORK *)work;

	BattleWorkTSSSeqNoSet(bw,TSS_SEQ_END);
	BattleWorkTSRSeqNoSet(bw,TSR_SEQ_END);

	BattleWorkFightEndFlagSet(bw,1);
}


//------------------------------------------------------------------
/**
 * $brief   ���肠���O���[�v�f�[�^�̑��M
 *
 * @param   mystatus		
 * @param   friendlist		
 * @param   sendbuf		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommCommandBattleMakeFriendList( MYSTATUS *mystatus, FRIEND_LIST *friendlist, FRIEND_LIST *sendbuf )
{
	int i;

	// ���M�f�[�^�̍쐬
	PM_strcpy( sendbuf->name, MyStatus_GetMyName( mystatus ));	// ���O
	sendbuf->id       = MyStatus_GetID(mystatus);				// ID
	sendbuf->region   = MyStatus_GetRegionCode(mystatus);		// ���[�W����
	sendbuf->rom_code = MyStatus_GetRomCode(mystatus);			// ROM
	sendbuf->sex      = MyStatus_GetMySex(mystatus);			// ����
	
	for(i=0;i<FRIENDLIST_FRIEND_MAX;i++){						// �����̒m�荇����ID��
		sendbuf->group_id[i]      = friendlist[i].id;			// �m�荇���̒m�荇���Ƃ��Ă͓n�����߂ɐ��`
		sendbuf->group_romcode[i] = friendlist[i].rom_code;
		sendbuf->group_region[i]  = friendlist[i].region;
		sendbuf->group_sex[i]     = friendlist[i].sex;
	}


	// ���M
//	CommSendHugeData( CB_FRINEDLIST, sendbuf, sizeof(FRIEND_LIST) );
	
}

//==============================================================================
/**
 * $brief   �Ƃ������O���[�v�ɓo�^���邽�߂̃f�[�^����M����
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommCommandBattleRecvFriendList(int netID, int size, void* pBuff, void* pWork)
{
	BATTLE_SIO_WORK		*bsw=(BATTLE_SIO_WORK *)pWork;
	
	OS_Printf("���肠���O���[�v�f�[�^����\n");
	
	if(CommGetCurrentID()!=netID){
		FriendList_Update( bsw->bp->friendlist, (FRIEND_LIST*)pBuff, 1, HEAPID_BATTLE );
	}

	bsw->send_count++;


}


//==============================================================================
/// FRIEND_LIST�̃T�C�Y��Ԃ�
//==============================================================================
static int _getFriendListSize(void)
{
    return FRIEND_LIST_SIZE;
}

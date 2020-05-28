//=============================================================================
/**
 * @file	comm_command_record.c
 * @brief	�f�[�^�𑗂邽�߂̃R�}���h���e�[�u�������Ă��܂�
 *          ���R�[�h�R�[�i�[�p�ł�
 * @author	Akito Mori
 * @date    2006.03.27
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "system/procsys.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/bmp_menu.h"
#include "application/record_corner.h"
#include "system/snd_tool.h"

typedef struct RECORD_WORK RECORD_WORK;

#include "record_corner_local.h"


#include "comm_command_record.h"

#include "communication/wh.h"



static int _getZero(void);
static int _getOne(void);
static int _getRecordSize(void);
static u8* _getRecordRecvBuf( int netID, void* pWork, int size );
static int _getCRECW(void);


static void RecordCorner_DataSend( RECORD_WORK *wk, int no);
void CommRecord_RecordData( int netID, int size, void* pBuff, void* pWork );
void CommRecordBanFlag( int netID, int size, void* pBuff, void* pWork );


// �Ή�����R�[���o�b�N�֐�
static const CommPacketTbl _CommPacketTbl[] = {
    { CommDummyCallBack, _getZero, NULL},// comm_command_field.c�œo�^����Ă���R�}���h�e�[�u���̖��������邽�߂�
    { CommDummyCallBack, _getZero, NULL},// �o�^����
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},	// comm_command_field.c�œo�^����Ă���R�}���h�e�[�u���̖��������邽�߂�
    { CommDummyCallBack, _getZero, NULL}, // �o�^����

	// ���R�[�h���g�p����R�}���h����
	{CommRecordCornerYes,   		_getOne},              	// CR_RECORD_YES  		 �͂�
	{CommRecordCornerNo,   	   	 	_getOne},             	// CR_RECORD_NO,		 ������
    {CommRecordCornerStop,			_getOne},             	// CR_RECORD_STOP,		 �����҂������̂ň�U�X�g�b�v
    {CommRecordCornerReStart,		_getZero},             	// CR_RECORD_RESTART,	 �����ҏ������I������̂ōĉ�
    {CommRecordCornerEndChild,		_getCRECW},            	// CR_RECORD_END_CHILD,	 �q�@�����E
    {CommRecordCornerEnd,			_getZero},              // CR_RECORD_END,		 �I��
	{CommRecordCornerChildJoin,		_getZero},				// CR_RECORD_CHILD_JOIN, �q�@��������錾
	{CommRecordStart,				_getZero},				// CR_RECORD_START, 	 ���R�[�h�����J�n��e���ʒB
	{CommRecord_RecordData,			_getRecordSize, _getRecordRecvBuf},// CR_RECORD_DATA, 	 ���R�[�h�����J�n��e���ʒB
	{CommRecordBanFlag,				_getOne},				// CR_RECORD_BAN		���E�֎~�ʒB

	// ���������̃R�}���h�𖳎����邽�߂̕���
	{ CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},

};


//==============================================================================
/**
 * ���G�����{�[�h�p�ʐM�R�}���h�o�^����
 *
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommCommandRecordInitialize(void* pWork)
{
	RECORD_WORK *wk = (RECORD_WORK *)pWork;

	int i;
	
	// ��M�R�[���o�b�N�ݒ�
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);
    CommCommandInitialize(_CommPacketTbl, length, pWork);


	// ����f�[�^��M�o�b�t�@�ݒ�
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
//		CommSetSpritDataRecvBuff( i, &wk->recv_data[i], sizeof(RECORD_DATA) );
	}
}


//==============================================================================
/**
 * $brief   ���R�[�h�f�[�^��M�R�[���o�b�N�֐�
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecord_RecordData( int netID, int size, void* pBuff, void* pWork )
{
	RECORD_WORK *wk = (RECORD_WORK *)pWork;

	wk->recv_count++;

	OS_Printf("���R�[�h�f�[�^��M���� id=%d\n",netID);
}

//==============================================================================
/**
 * @brief   ���E����t���O����
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordBanFlag( int netID, int size, void* pBuff, void* pWork )
{
	RECORD_WORK *wk = (RECORD_WORK *)pWork;
	u8  *flag        = (u8*)pBuff;

	if(netID==0){
		if(wk->banFlag != *flag){
			OS_Printf("�e�@����̗��E�֎~�t���O banFlag=%d\n",*flag);
		}
		wk->banFlag = *flag;
	}
	
}


//------------------------------------------------------------------
/**
 * $brief   ���R�[�h�����J�n
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void CommRecordStart(int netID, int size, void* pBuff, void* pWork)
{
	RECORD_WORK *wk = (RECORD_WORK*)pWork;

	wk->recv_count = 0;
	wk->record_execute = TRUE;
	
	// ���R�[�h�f�[�^���M�J�n
	RecordCorner_DataSend( wk, CommGetCurrentID());

	// ��ʏ㕔���u���R�[�h�������񂿂イ�I�v
	RecordCornerTitleChange( wk );

	RecordCorner_MainSeqForceChange( wk, RECORD_MODE_RECORD_SEND_DATA, netID );
	
    CommStateSetErrorCheck(TRUE,TRUE); // �����ȍ~�͐ؒf���G���[

	// ��������SE
	Snd_SePlay(SEQ_SE_DP_F209);

}


//==============================================================================
/**
 * �ʐM��ʂ��J�n����
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordCornerReStart(int netID, int size, void* pBuff, void* pWork)
{
	RECORD_WORK *wk = (RECORD_WORK*)pWork;

	OS_Printf("�e�@���烌�R�[�h��W�ĊJ�ʒm\n");
	RecordCorner_MainSeqForceChange( wk, RECORD_MODE_NEWMEMBER_END, 0 );
	
}
//==============================================================================
/**
 * $brief   �q�@�����E
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		�q(���E��)����̑��M��0:���E���m�F�B�@1:���E���s
 *						�e����̑��M�����4�r�b�g�F�e��shareNum(0xf�̏ꍇ�͗��ENG)
 * 									������4�r�b�g�F���E�҂�ID
 * @param   pWork		RECORD_WORK*
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordCornerEndChild(int netID, int size, void* pBuff, void* pWork)
{
	RECORD_WORK *wk = (RECORD_WORK*)pWork;
	COMM_RECORD_END_CHILD_WORK trans_work;
	COMM_RECORD_END_CHILD_WORK *recieve_work;
	
	recieve_work = pBuff;
	
	if(netID != 0){
		//�q�@(���E��)����̑��M
		//���E���܂��ʒm
		if(CommGetCurrentID()==0){
			// �q�@����(�e�@���󂯎��)
			// �q�@�����Ȃ��Ȃ�������S���ɒʒm����
			trans_work = *recieve_work;
			trans_work.ridatu_id = netID;
			trans_work.oya_share_num = wk->shareNum;
			switch(recieve_work->request){
			case CREC_REQ_RIDATU_CHECK:
				if(wk->shareNum != CommGetConnectNum() 
						|| wk->shareNum != RecordCorner_MyStatusGetNum()
						|| wk->shareNum != MATH_CountPopulation(WH_GetBitmap())){
					trans_work.ridatu_kyoka = FALSE;	//���ENG�I
				}
				else{
					wk->ridatu_bit |= 1 << netID;
					trans_work.ridatu_kyoka = TRUE;
					//���EOK�Ȃ̂ŎQ��������������(����������΂����瑤�Ő������͂������͂�)
					CommStateSetLimitNum(CommGetConnectNum());
				}
				break;
			case CREC_REQ_RIDATU_EXE:
				break;
			}

			CommSendData( CR_RECORD_END_CHILD, &trans_work, sizeof(COMM_RECORD_END_CHILD_WORK) );
			OS_Printf("�q�@%d���痣�E���󂯎���������M\n",netID);
		}
	}
	else{
		//�e����̑��M
		switch(recieve_work->request){
		case CREC_REQ_RIDATU_CHECK:
			//���E�m�F�Ȃ̂ŁA���E���悤�Ƃ����q�@�ɂ̂݌��ʂ𑗂�
			if(recieve_work->ridatu_id == CommGetCurrentID()){
				if(recieve_work->ridatu_kyoka == FALSE){
					RecordCorner_MainSeqForceChange( wk, RECORD_MODE_END_SELECT_ANSWER_NG, recieve_work->ridatu_id );
				}
				else{
					wk->oya_share_num = recieve_work->oya_share_num;
					RecordCorner_MainSeqForceChange( wk, RECORD_MODE_END_SELECT_ANSWER_OK, recieve_work->ridatu_id );
				}
			}
			break;
		case CREC_REQ_RIDATU_EXE:
			OS_Printf("�e�@���q�@%d�̗��E�ʒm����\n", recieve_work->ridatu_id);
		//	RecordCorner_MainSeqCheckChange( wk, RECORD_MODE_LOGOUT_CHILD, id );
			RecordCorner_MainSeqForceChange( wk, RECORD_MODE_LOGOUT_CHILD, recieve_work->ridatu_id );
			break;
		}
	}
}

//==============================================================================
/**
 * $brief   �u�q�@���������Ă����̂ň�U�G�𑗂��~�܂��Ăˁv
 *			�Ɛe�@�����M���Ă������̃R�[���o�b�N
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordCornerStop(int netID, int size, void* pBuff, void* pWork)
{

	RECORD_WORK *wk = (RECORD_WORK*)pWork;
	u8 id;

	id = *(u8*)pBuff;
	// ���C���V�[�P���X�ύX
	RecordCorner_MainSeqCheckChange( wk, RECORD_MODE_NEWMEMBER, id );

	// �e�@���摜�f�[�^���M���J�n����
	if(CommGetCurrentID()==0){
		wk->send_num = 0;

		// �����Ń��R�[�h�R�[�i�[�p�f�[�^���F�ő��M�J�n����(���낤)
		// RECORD_GraphicDataSend(wk, wk->send_num);
	}


	OS_Printf("�e�@����́u�q�@%d�ɊG�𑗂邩��~�܂��Ăˁv�ʒm\n",id);

}

void CommRecordCornerYes(int netID, int size, void* pBuff, void* pWork)
{
	
}
void CommRecordCornerNo(int netID, int size, void* pBuff, void* pWork)
{
	
}

//==============================================================================
/**
 * $brief   �e�@����߂�̂ŋ����I��������
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordCornerEnd(int netID, int size, void* pBuff, void* pWork)
{
	RECORD_WORK *wk = (RECORD_WORK*)pWork;
	OS_Printf("�e�@����̏I���ʒm�������̂ł�߂�\n");

	// �e�@�ȊO�͂��̃R�}���h�ŋ������イ��傤����
	if(CommGetCurrentID() != 0){
		RecordCorner_MainSeqForceChange( wk, RECORD_MODE_FORCE_END, 0  );
	}
}

//==============================================================================
/**
 * $brief   �R��ځE�S��ځE�T��ڂ̎q�@���u�G������[�����v�ƌ���
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordCornerChildJoin(int netID, int size, void* pBuff, void* pWork)
{
	u8 id;
//	GF_ASSERT(CommGetCurrentID()==0 && "�q�@�������Ƃ���");

	// �e�@���󂯎������(�Ƃ������e�����󂯎��Ȃ����ǁj
	if(CommGetCurrentID()==0){
		id  = netID;
		
		// �S��Ɂu���ꂩ��G�𑗂�̂Ŏ~�܂��Ă��������v�Ƒ��M����
		CommSendData( CR_RECORD_STOP, &id, 1 );
		OS_Printf("�q�@(%d = %d)����̗����^�G�̂��������ʒm\n",id,netID);
	}
	
}





//------------------------------------------------------------------
/**
 * $brief   �O���t�B�b�N�f�[�^�𕪊����M
 *
 * @param   wk		
 * @param   no		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void RecordCorner_DataSend( RECORD_WORK *wk, int no)
{
	// xor�擾�E�i�[
	{
		int i;
		u32 *p,result;
		p = (u32*)wk->send_data.data;
		for(result=0,i=0;i<RECORD_SEND_DATASIZE/4;i++){
			result ^= p[i];
		}
		wk->send_data._xor        = result;
	}

	// �����ԍ�����������(�e�@�̒l�������g�p�����j
	wk->send_data.seed = gf_rand();
	
	// ���M�J�n
//	CommSendSpritData( &wk->send_data, sizeof(RECORD_DATA) );
	CommSendHugeData(CR_RECORD_DATA, &wk->send_data, sizeof(RECORD_DATA) );
	

	OS_Printf("���M�f�[�^ no=%d, xor = %08x\n",  wk->send_data.seed,  wk->send_data._xor);
}


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// �p���b�g�T�C�Y�ʒm�֐��Q
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
// 0�o�C�g��\���֐�
//--------------------------------------------------------------------------------
static int _getZero(void)
{
    return 0;
}

//--------------------------------------------------------------------------------
// 1�o�C�g��\���֐�
//--------------------------------------------------------------------------------
static int _getOne(void)
{
    return 1;
}

//--------------------------------------------------------------------------------
// 1�o�C�g��\���֐�
//--------------------------------------------------------------------------------
static int _getCRECW(void)
{
	return sizeof(COMM_RECORD_END_CHILD_WORK);
}


//--------------------------------------------------------------------------------
// ���R�[�h�f�[�^�̎�M�o�b�t�@��ݒ肷��֐�
//--------------------------------------------------------------------------------
static u8* _getRecordRecvBuf( int netID, void* pWork, int size )
{
	RECORD_WORK *wk = (RECORD_WORK*)pWork;
	
	return (u8*)&wk->recv_data[netID];
}

//=============================================================================
/**
 * @file	comm_command_oekaki.c
 * @brief	�f�[�^�𑗂邽�߂̃R�}���h���e�[�u�������Ă��܂�
 *          ���G�����{�[�h�p�ł�
 * @author	Akito Mori
 * @date    2005.02.14
 */
//=============================================================================

#include "common.h"
#include "system/procsys.h"
#include "communication/communication.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "communication/communication.h"
#include "communication/wh.h"
#include "field/fieldobj.h"
#include "field/comm_union_beacon.h"
#include "field/comm_union_view_common.h"



typedef struct OEKAKI_WORK OEKAKI_WORK;

#include "application/oekaki.h"

#include "oekaki_local.h"


#include "comm_command_oekaki.h"



static int _getPictureSize(void);
static int _getLinePosSize(void);
static int _getLinePosServerSize(void);
static u8* _setPictureBuff( int netID, void* pWork, int size);
static int _getCRECW(void);
static int _getCOECW(void);

static void Oekaki_GraphicDataSend( OEKAKI_WORK *wk, int no);
static void CommOekakiBoardFreeze( int netID, int size, void* pBuff, void* pWork );


// CommCommandOekaki.c�����`����R�}���h�őΉ�����R�[���o�b�N�֐�
static const CommPacketTbl _CommPacketTbl[] = {

    { CommDummyCallBack, _getOne, NULL},// comm_command_field.c�œo�^����Ă���R�}���h�e�[�u���̖��������邽�߂�
    { CommDummyCallBack, _getOne, NULL},// �o�^����
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},	// comm_command_field.c�œo�^����Ă���R�}���h�e�[�u���̖��������邽�߂�
    { CommDummyCallBack, _getOne, NULL}, // �o�^����


	// ���R�[�h�̃R�}���h�e�[�u���𖳎����邽�߂̕���
	{ CommDummyCallBack, _getOne, NULL},
	{ CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getCRECW, NULL},
    { CommDummyCallBack, _getOne, NULL},
	{ CommDummyCallBack, _getOne, NULL},
	{ CommDummyCallBack, _getOne, NULL},
	{ CommDummyCallBack, _getOne, NULL},
	{ CommDummyCallBack, _getOne, NULL},

	// ���G���������镔��
	{CommOekakiBoardPicture, 		_getPictureSize, _setPictureBuff}, 		// CO_OEKAKI_GRAPHICDATA  �݂�Ȃŕ`���Ă����摜�f�[�^
	{CommOekakiBoardLinePos,   		_getLinePosSize},    	// CO_OEKAKI_LINEPOS,	  �^�b�`�p�l���Ŏ擾�����|�W�V�����f�[�^
	{CommOekakiBoardLinePosServer, _getLinePosServerSize}, 	// CO_OEKAKI_LINEPOS,	  �^�b�`�p�l���Ŏ擾�����|�W�V�����f�[�^
	{CommOekakiBoardYes,   			_getOne},              	// CO_OEKAKI_YES,		  �͂�
	{CommOekakiBoardNo,   	   	 	_getOne},             	// CO_OEKAKI_NO,		  ������
    {CommOekakiBoardStop,			_getOne},             	// CO_OEKAKI_STOP,		  �����҂������̂ň�U�X�g�b�v
    {CommOekakiBoardReStart,		_getZero},             	// CO_OEKAKI_RESTART,	  �����ҏ������I������̂ōĉ�
    {CommOekakiBoardEndQuestion,	_getZero},          	// CO_OEKAKI_END_QUESTION �I��
    {CommOekakiBoardEndChild,		_getCOECW},            	// CO_OEKAKI_END_CHILD,	  �q�@�����E
    {CommOekakiBoardEnd,			_getZero},              // CO_OEKAKI_END,		  �I��
	{CommOekakiBoardChildJoin,		_getZero},				// CO_OEKAKI_CHILD_JOIN	  �q�@��������錾
	{CommOekakiBoardFreeze,			_getZero},				// CO_OEKAKI_OUT_CONTROL	���E�֎~����
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
void CommCommandOekakiBoardInitialize(void* pWork)
{
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);
    CommCommandInitialize(_CommPacketTbl, length, pWork);
}


//==============================================================================
/**
 * �e�@���ڑ�����܂łɂ�����Ă����摜����C�ɑ��M����
 * 
 * 
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommOekakiBoardPicture(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK *)pWork;

	// �q�@�̏ꍇ�͐e�@�����������摜�f�[�^����荞��
	if(CommGetCurrentID()!=0){
		OEKAKIG_SPLIT_DATA *osd = (OEKAKIG_SPLIT_DATA *)pBuff;;
		OS_Printf("�摜�擾 no=%d, xor=%08x\n",osd->no, osd->_xor);
		if(osd->no*1000 > OEKAKI_GRAPHI_SIZE){
			MI_CpuCopyFast( osd->chara, &wk->canvas_buf[osd->no*1000], OEKAKI_GRAPHI_SIZE%1000);
		}else{
			MI_CpuCopyFast( osd->chara, &wk->canvas_buf[osd->no*1000],  1000);
		}
		// BMPWIN�̃o�b�t�@�ɃR�s�[����
		MI_CpuCopyFast( wk->canvas_buf, wk->OekakiBoard.chrbuf, OEKAKI_GRAPHI_SIZE);

		// ��ʂɔ��f
		GF_BGL_BmpWinOn( &wk->OekakiBoard );

	// �e�@�͎��̃f�[�^�𑗐M����
	}else{
		OEKAKIG_SPLIT_DATA *osd = (OEKAKIG_SPLIT_DATA *)pBuff;;
		OS_Printf("�摜�擾 no=%d, xor=%08x",osd->no, osd->_xor);
	
		if(wk->send_num*1000 < OEKAKI_GRAPHI_SIZE){
			wk->send_num++;
			Oekaki_GraphicDataSend(wk, wk->send_num);
		}else{
			CommSendData_ServerSide( CO_OEKAKI_RESTART, NULL, 0);
		}
	}

}


//==============================================================================
/**
 * �J�[�\���ʒu������M�����Ƃ��̃R�[���o�b�N
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommOekakiBoardLinePos(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk     = (OEKAKI_WORK*)pWork;
	TOUCH_INFO  *result = (TOUCH_INFO*)pBuff;

	// �q�@���������f�[�^���i�[����
	if(netID!=0){
		wk->ParentTouchResult[netID] = *result;
	}

}



//==============================================================================
/**
 * $brief   ���C���f�[�^��e�@�����M�����i�S���`��)
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommOekakiBoardLinePosServer( int netID, int size, void* pBuff, void* pWork )
{
	OEKAKI_WORK *wk     = (OEKAKI_WORK*)pWork;
	TOUCH_INFO  *result = (TOUCH_INFO*)pBuff;

    if(wk==NULL){  // ���̂Ƃ��͂��G�����������ł��Ă��Ȃ��̂Ŗ���
        return;
    }

    
	if(netID==0){	// ��΂ɐe���炵�����Ȃ��͂�����
		int i;
		for(i=0;i<OEKAKI_MEMBER_MAX;i++){
			wk->AllTouchResult[i] = result[i];
		}
	}
	
	if(wk->AllTouchResult[0].banFlag==OEKAKI_BAN_ON){
		OS_TPrintf("�e�@���瑀��֎~����\n");
	}
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
void CommOekakiBoardReStart(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;

	OS_Printf("�e�@���炨�G�����ĊJ�ʒm\n");
	OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_NEWMEMBER_END, 0 );
	
	MI_CpuClearFast( wk->canvas_buf, OEKAKI_GRAPHI_SIZE );
	
	if(CommGetCurrentID()==0){
		// �G�����L�����ڑ��l�����X�V
		wk->shareNum = CommGetConnectNum();
		wk->shareBit = WH_GetBitmap();
		wk->banFlag  = OEKAKI_BAN_OFF;
	}
}
//==============================================================================
/**
 * $brief   �q�@�����E
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		���E�҂�ID(�e����̑��M�ōŏ�ʃr�b�g�������Ă���ꍇ�͗��ENG)
 * @param   pWork		OEKAKI_WORK*
 *
 * @retval  none		
 */
//==============================================================================
void CommOekakiBoardEndChild(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;
	COMM_OEKAKI_END_CHILD_WORK trans_work;
	COMM_OEKAKI_END_CHILD_WORK *recieve_work;

	recieve_work = pBuff;
	
	// �e�@���炫���ꍇ�݂͂�ȂŁu�����������Ȃ��Ȃ�܂����v�Ƃ���
	if(netID!=0){
		//�q�@(���E��)����̑��M
		//���E���܂��ʒm
		if(CommGetCurrentID()==0){
			// �q�@����(�e�@���󂯎��)
			// �q�@�����Ȃ��Ȃ�������S���ɒʒm����
			trans_work = *recieve_work;
			trans_work.ridatu_id = netID;
			trans_work.oya_share_num = wk->shareNum;
			switch(recieve_work->request){
			case COEC_REQ_RIDATU_CHECK:
				if(wk->shareNum != CommGetConnectNum() 
						|| wk->shareNum != OekakiBoard_MyStatusGetNum()
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
			case COEC_REQ_RIDATU_EXE:
				break;
			}

			CommSendData_ServerSide( CO_OEKAKI_END_CHILD, &trans_work, 
				sizeof(COMM_OEKAKI_END_CHILD_WORK) );
			OS_Printf("�q�@%d���痣�E���󂯎���������M\n",netID);
		}
	
	}else{
	// �e�@����q�@���E�̒ʒm������
		switch(recieve_work->request){
		case COEC_REQ_RIDATU_CHECK:
			//���E�m�F�Ȃ̂ŁA���E���悤�Ƃ����q�@�ɂ̂݌��ʂ𑗂�
			if(recieve_work->ridatu_id == CommGetCurrentID()){
				if(recieve_work->ridatu_kyoka == FALSE){
					OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_END_SELECT_ANSWER_NG, recieve_work->ridatu_id );
				}
				else{
					wk->oya_share_num = recieve_work->oya_share_num;
					OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_END_SELECT_ANSWER_OK, recieve_work->ridatu_id );
				}
			}
			break;
		case COEC_REQ_RIDATU_EXE:
			OS_TPrintf("�e�@���q�@%d�̗��E�ʒm����\n", recieve_work->ridatu_id);
		//	OekakiBoard_MainSeqCheckChange( wk, OEKAKI_MODE_LOGOUT_CHILD, id );
			OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_LOGOUT_CHILD, recieve_work->ridatu_id );
			break;
		}
	}
}
void CommOekakiBoardEndQuestion(int netID, int size, void* pBuff, void* pWork)
{

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
void CommOekakiBoardStop(int netID, int size, void* pBuff, void* pWork)
{

	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;
	u8 id;

	id = *(u8*)pBuff;
	// ���C���V�[�P���X�ύX
	OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_NEWMEMBER, id );

	// �e�@���摜�f�[�^���M���J�n����
	if(CommGetCurrentID()==0 && wk->proc_seq == SEQ_MAIN){
		wk->send_num = 0;

		//�O���t�B�b�N�������M
		Oekaki_GraphicDataSend(wk, wk->send_num);
	}


	OS_Printf("�e�@����́u�q�@%d�ɊG�𑗂邩��~�܂��Ăˁv�ʒm\n",id);

}

void CommOekakiBoardYes(int netID, int size, void* pBuff, void* pWork)
{
	
}
void CommOekakiBoardNo(int netID, int size, void* pBuff, void* pWork)
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
void CommOekakiBoardEnd(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;
	OS_Printf("�e�@����̏I���ʒm�������̂ł�߂�\n");

	// �e�@�ȊO�͂��̃R�}���h�ŋ������イ��傤����
	if(CommGetCurrentID() != 0){
		OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_FORCE_END, 0  );
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
void CommOekakiBoardChildJoin(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;
	u8 id;
	GF_ASSERT(CommGetCurrentID()==0 && "�q�@�������Ƃ���");
OS_Printf("_�q�@(%d)����̗����^�G�̂��������ʒm\n",netID);
	// �e�@���󂯎������(�Ƃ������e�����󂯎��Ȃ����ǁj
	if(CommGetCurrentID()==0){
		if(wk->firstChild!=0){
			id  = netID;
		
			// �S��Ɂu���ꂩ��G�𑗂�̂Ŏ~�܂��Ă��������v�Ƒ��M����
			CommSendData_ServerSide( CO_OEKAKI_STOP, &id, 1 );
			OS_Printf("�q�@(%d = %d)����̗����^�G�̂��������ʒm\n",id,netID);
		}else{
			OS_Printf("�ŏ��̎q�@%d����̗����Ȃ̂Ŗ�������\n",netID);
			wk->firstChild = 1;
		}
	}
    // ���G�������ɂ͐ڑ��ؒf�ŃG���[�������Ȃ�(�r����TRUE,TRUE�ɖ߂鎖������̂ōēx�j
    CommStateSetErrorCheck(FALSE,TRUE);
	
}

//------------------------------------------------------------------
/**
 * @brief   ���E�֎~�R�}���h����
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommOekakiBoardFreeze( int netID, int size, void* pBuff, void* pWork )
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;

	// ���E�֎~
	wk->banFlag = 1;
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
static void Oekaki_GraphicDataSend( OEKAKI_WORK *wk, int no)
{
	// ���M�o�b�t�@�ɃR�s�[
	u8 *p = (u8*)wk->OekakiBoard.chrbuf;
	MI_CpuCopyFast( &p[no*1000], wk->send_buf.chara, 1000 ); 

	// xor�擾�E�i�[
	{
		int i;
		u32 *p,result;
		p = (u32*)wk->send_buf.chara;
		for(result=0,i=0;i<1000/4;i++){
			result ^= p[i];
		}
		wk->send_buf._xor        = result;
	}

	// �����ԍ�����������
	wk->send_buf.no = no;
	
	// ���M�J�n
	CommSendHugeData_ServerSide( CO_OEKAKI_GRAPHICDATA, &wk->send_buf, sizeof(OEKAKIG_SPLIT_DATA));
//	CommSendHugeData(CO_OEKAKI_GRAPHICDATA, &wk->send_buf, 1004);

	OS_Printf("���M�f�[�^ no=%d, xor = %08x\n",  wk->send_buf.no,  wk->send_buf._xor);
}




//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// �p���b�g�T�C�Y�ʒm�֐��Q
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------



//--------------------------------------------------------------------------------
// ��M�f�[�^�T�C�Y��Ԃ��֐�
//--------------------------------------------------------------------------------
static u8* _setPictureBuff( int netID, void* pWork, int size)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;

	return (u8*)&wk->split_temp[netID];
}

//--------------------------------------------------------------------------------
// �o�C�g��\���֐�
//--------------------------------------------------------------------------------
static int _getCRECW(void)
{
	return 4;
}

//--------------------------------------------------------------------------------
// �o�C�g��\���֐�
//--------------------------------------------------------------------------------
static int _getCOECW(void)
{
	return sizeof(COMM_OEKAKI_END_CHILD_WORK);
}

//=============================================================================
/**
 * @file	comm_tradelist.c
 * @brief	�f�[�^�𑗂邽�߂̃R�}���h���e�[�u�������Ă��܂�
 *          �t�B�[���h�p�ł�
 *          comm_command_field.h �� enum �Ɠ������тł���K�v������܂�
 * @author	Akito Mori
 * @date    2005.12.21
 */
//=============================================================================

#include "common.h"
#include "system/procsys.h"
#include "communication/communication.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/gra_tool.h"
#include "system/bmp_menu.h"
#include "savedata/friendlist.h"
#include "savedata/friendlist_local.h"


#include "application/tradelist.h"
#include "comm_command_tradelist.h"
#include "tradelist_def.h"

#include "field/fieldsys.h" //FIELDSYS_WORK
#include "system/mystatus.h"
#include "poketool/pokeparty.h"


void CommTradeListFriendList(int netID, int size, void* pBuff, void* pWork);
void CommTradeListPerapVoice(int netID, int size, void* pBuff, void* pWork);
void CommTradeListSaveWait(int netID, int size, void* pBuff, void* pWork);
void CommTradeListRibbonInfo(int netID, int size, void* pBuff, void* pWork);


static int PositionChangeLR(u8 pos);
static int _getPokePartySplitSize(void);
static int _getFriendListSize(void);
static u8* _getPokePartyRecvBuff( int netID, void* pWork, int size);
static u8* _getPerapVoiceRecvBuff( int netID, void* pWork, int size );
static int _getPerapVoiceSize(void);
static int _getSpRibbonSize(void);


static const CommPacketTbl _CommPacketTbl[] = {
	
{CommTradeListPokemonData,_getPokePartySplitSize, _getPokePartyRecvBuff}, // CT_POKEDATA
{CommTradeListCusorPos,   _getOne},               // CT_CURSOR_POS,		///< �J�[�\���ʒu���
{CommTradeListDecide,     _getOne},               // CT_TRADE_DECIDE,		///< ����
{CommTradeListResultYes,  _getOne},               // CT_TRADE_YES,		///< �͂�
{CommTradeListResultNo,	  _getOne},               // CT_TRADE_NO,			///< ������
{CommTradeListTradeStart, _getOne},               // CT_TRADE_START,		///< �����f����
{CommTradeListFriendList, _getFriendListSize,     _getPokePartyRecvBuff },	// CT_FRIENDLIST,	///< ���肠���O���[�v�f�[�^
{CommTradeListPerapVoice, _getPerapVoiceSize,     _getPokePartyRecvBuff },	// CT_FRIENDLIST,	///< �y���b�v�{�C�X�f�[�^
{CommTradeListEnd,		  _getZero},              // CT_TRADE_END,		///< �I��
{CommTradeListSaveWait,	  _getOne},               // CT_SAVE_WAIT_TIME,	///< �Z�[�u�܂ł̃E�F�C�g
{CommTradeListRibbonInfo, _getSpRibbonSize},      // CT_SP_RIBBON,		///< �g�����{�����

};


//==============================================================================
/**
 * 
 *
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommCommandTradeListInitialize(void* pWork)
{
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);
    CommCommandInitialize(_CommPacketTbl, length, pWork);
}

//------------------------------------------------------------------
/**
 * �ʐM�Ŏ擾�����J�[�\���ʒu�����E���]������i�u�����v�͂��̂܂܁j
 *
 * @param   pos		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int PositionChangeLR(u8 pos)
{
	// �����
	if(pos==12){
		return 12;
	}
	// �����͉E����
	if(pos<6){
		return pos+6;
	}
	//�c��E���Ȃ̂ō�����
	return pos-6;
}

//------------------------------------------------------------------
/**
 * �������đ����Ă���POKEPARTY���R�s�[����֐�
 *
 * @param   party		
 * @param   buf		
 * @param   no		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CopyPokePartySplitData(POKEPARTY *party, void *buf, int no)
{
	u32 adrs   = (u32)party+no*POKEPARTY_SEND_ONCE_SIZE;
	u32 total  = no*POKEPARTY_SEND_ONCE_SIZE+POKEPARTY_SEND_ONCE_SIZE;
	u32 offset = no*POKEPARTY_SEND_ONCE_SIZE;


	if(total > PokeParty_GetWorkSize()){
		int rest;

		rest = PokeParty_GetWorkSize() - offset;
		memcpy((void*)adrs,buf,rest);
	}else{
		memcpy((void*)adrs,buf,POKEPARTY_SEND_ONCE_SIZE);
	}
}

//==============================================================================
/**
 * �|�P�����f�[�^����M���i�[�B���̃f�[�^���M���Ăяo��(�e�q���݂̑��M�ɂȂ�j
 * ����q���ɂP�Q�̕��𑗐M���邱�ƂɂȂ�͂�
 * 
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListPokemonData(int netID, int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK  *fsys = (FIELDSYS_WORK*)pWork;
	TRADELIST_WORK *tlw  = fsys->tradelist_work;



	// ��M�����f�[�^�������̂h�c�ƈႤ�̂ł���Ύ�荞��
	if(netID!=CommGetCurrentID()){

		OS_Printf("�|�P���� netID = %d  no=%d, %d/%d  pokesize=%d\n",netID,tlw->exchange_friend_count,(tlw->exchange_friend_count+1)*POKEPARTY_SEND_ONCE_SIZE,PokeParty_GetWorkSize(),PokemonParam_GetWorkSize());

		// ���[�N��PokeParty�ɃR�s�[
//		PokeParty_Add(tlw->FriendPokeParty, (POKEMON_PARAM *)pBuff);
//		CopyPokePartySplitData(tlw->FriendPokeParty,pBuff,tlw->exchange_friend_count++);
		memcpy((void*)tlw->FriendPokeParty,pBuff,POKEPARTY_SEND_ONCE_SIZE);
		tlw->exchange_friend_count++;

		// �����̃f�[�^�𑗐M����
		if((tlw->exchange_friend_count)*POKEPARTY_SEND_ONCE_SIZE >= PokeParty_GetWorkSize()){
//			tlw->exchange_finish = 1;
			if(CommGetCurrentID()==1){
				TradeListCommDiffSend( tlw, CT_TRADE_START,0);
			}else{
				TradeListCommSendPokeData(CommGetCurrentID(), tlw->MyPokeParty, tlw->exchange_work);
			}
		}else{
			TradeListCommSendPokeData(CommGetCurrentID(), tlw->MyPokeParty, tlw->exchange_work);
		}
		tlw->exchange_work++;
	}

}


//==============================================================================
/**
 * �������X�g�̃J�[�\���ʒu����M�����Ƃ��̃R�[���o�b�N
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListCusorPos(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	u8 *pos = (u8*)pBuff;

	// �����ő������f�[�^����Ȃ��h�c�̂��̗p����
	if(netID!=CommGetCurrentID()){
		tlw->cursor_pos[1] =  PositionChangeLR( *pos );
	}
}
void CommTradeListDecide(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	u8 *data = (u8*)pBuff;

	OS_Printf("ID%d :�I���R�}���h����\n",netID);
	
	tlw->end_flag[netID] = *data;
}
void CommTradeListResultYes(int netID, int size, void* pBuff, void* pWork)
{
	
}
void CommTradeListResultNo(int netID, int size, void* pBuff, void* pWork)
{
	
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
void CommTradeListTradeStart(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	
	OS_Printf("�J�n�f�[�^\n");

	tlw->exchange_finish=2;

}


void CommTradeListEnd(int netID, int size, void* pBuff, void* pWork)
{

}

//==============================================================================
/**
 * @brief   �e�@���Z�[�u�܂ł̃E�F�C�g�𗐐��Ő������ēn���Ă����
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListSaveWait(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	u8 *wait = (u8*)pBuff;

	tlw->savePreWait = *wait;
	
	OS_TPrintf("�e�@����Z�[�u�܂ł̎��Ԃ�%dsync�҂Ăƒʒm������\n", *wait*2);
}

//==============================================================================
/**
 * @brief   �g�����{���������Ƃ�
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListRibbonInfo(int netID, int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK *fsys  = (FIELDSYS_WORK*)pWork;
	int i;
	u8 *mySpRibbon   = SaveData_GetSpRibbon( fsys->savedata );
	u8 *recvSpRibbon = (u8*)pBuff;

	OS_Printf("ID %d�̃��{��������M\n", netID);
	
	if(CommGetCurrentID()==netID){
		// �����̏��͂���Ȃ�
		return;
	}

	for(i=0;i<HAIFU_RIBBON_MAX;i++){
		// ��M�������0����Ȃ���
		if(recvSpRibbon[i]!=0){
			// �����̃��{���Ƒ���̏�񂪈Ⴄ�̂ł����
			if(mySpRibbon[i]!=recvSpRibbon[i]){
				// ���{����������������
				mySpRibbon[i]=recvSpRibbon[i];
			}
		}
	}
	
	
	
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
void CommTradeListFriendList(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	
	OS_Printf("���肠���O���[�v�f�[�^����\n");
	
	if(CommGetCurrentID()!=netID){
		FriendList_Update( tlw->friendlist, (FRIEND_LIST*)pBuff, 1, HEAPID_TRADELIST );
		tlw->exchange_finish = 3;
	}
}


//==============================================================================
/**
 * @brief   �y���b�v�{�C�X�f�[�^�̎�M
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListPerapVoice(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	
	OS_Printf("�y���b�v�{�C�X����\n");
	
	if(CommGetCurrentID()!=netID){
		MI_CpuCopyFast( pBuff, tlw->perap_buf[netID], PERAPVOICE_LENGTH );
		tlw->exchange_finish = 4;
        CommSetWifiBothNet(FALSE); // wifi�̒ʐM�𓯊�����񓯊��ɕς���
	}
	
}

//==============================================================================
/// FIELDSYS_WORK�Ɋm�ۍς݃��[�N�̃|�C���^��n�� 
//==============================================================================
void SetFieldSys_in_TradeWorkPtr(FIELDSYS_WORK* fsys, TRADELIST_WORK *tradelist_work)
{
	fsys->tradelist_work = tradelist_work;
}

//==============================================================================
/// PERAP_VOICE�̃T�C�Y��Ԃ�
//==============================================================================
static int _getPerapVoiceSize(void)
{
    return PERAPVOICE_DATA_LENGTH;
}

//==============================================================================
/// �g�����{�����̃T�C�Y��Ԃ�
//==============================================================================
static int _getSpRibbonSize(void)
{
	return HAIFU_RIBBON_MAX;

}

//==============================================================================
/// FRIEND_LIST�̃T�C�Y��Ԃ�
//==============================================================================
static int _getFriendListSize(void)
{
    return sizeof(FRIEND_LIST);
}

//==============================================================================
/// �莝���|�P�����̃T�C�Y��Ԃ�
//==============================================================================
static int _getPokePartySplitSize(void)
{
	return POKEPARTY_SEND_ONCE_SIZE;
}


//==============================================================================
/// ��M�o�b�t�@��n��
//==============================================================================
static u8* _getPokePartyRecvBuff( int netID, void* pWork, int size)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	
	return (u8*)tlw->recv_buf[netID];
}



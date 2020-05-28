#ifndef __COMM_COMMAND_TRADELIST_H__
#define __COMM_COMMAND_TRADELIST_H__


// �|�P�����p�[�e�B�[�𑗐M����Ƃ��̃f�[�^��
#define POKEPARTY_SEND_ONCE_SIZE	( 236*6+4*2 )	// sizeof(POKEPARTY)

#include "communication/comm_command.h"


/// �������X�g��p�ʐM�R�}���h�̒�`�B
enum CommCommandTradeList_e {

  CT_POKEDATA  = CS_COMMAND_MAX,	///< �|�P�����f�[�^�̑��M�R�}���h
  CT_CURSOR_POS,					///< �J�[�\���ʒu���
  CT_TRADE_DECIDE,					///< ����
  CT_TRADE_YES,						///< �͂�
  CT_TRADE_NO,						///< ������
  CT_TRADE_START,					///< �����f����
  CT_FRINEDLIST,					///< �F�B���X�g�f�[�^�𑗂�
  CT_PERAPVOICE,					///< �y���b�v���H�C�X�f�[�^�𑗂�
  CT_TRADE_END,						///< �I��
  CT_SAVE_WAIT_TIME,				///< �Z�[�u�܂ł̃E�F�C�g	
  CT_SP_RIBBON_INFO,				///< �g�����{�����
  
  //------------------------------------------------�����܂�
  CT_COMMAND_MAX   // �I�[--------------����͈ړ������Ȃ��ł�������
};

extern void CommTradeListPokemonData(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListCusorPos(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListDecide(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListResultYes(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListResultNo(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListTradeStart(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListFriendList(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListEnd(int netID, int size, void* pBuff, void* pWork);
extern void SetFieldSys_in_TradeWorkPtr(FIELDSYS_WORK* fsys, TRADELIST_WORK *tradelist_work);

extern void CommCommandTradeListInitialize(void* pWork);
#endif
#ifndef __COMM_MYSTERY_FUNC_H__
#define __COMM_MYSTERY_FUNC_H__

#include "savedata/fushigi_data.h"


#define RGB(r, g, b)		(((b)&31)<<10|((g)&31)<<5|((r)&31))


enum {
  COMMMYSTERYFUNC_ERROR_NONE = 0,
  COMMMYSTERYFUNC_ERROR_VERSION,	// �z�z�o�[�W�����Ɋ܂܂�Ă��Ȃ�����
  COMMMYSTERYFUNC_ERROR_HAVE,		// ���łɂ�����Ă���
  COMMMYSTERYFUNC_ERROR_FULLGIFT,	// �z�B������t
  COMMMYSTERYFUNC_ERROR_FULLCARD,	// �J�[�h����t
  COMMMYSTERYFUNC_ERROR_GROUNDCHILD,	// ����͑��z�M
  COMMMYSTERYFUNC_ERROR_MAX
};



//--------------------------------------------------------------------------------------------
/**
 * VRAM������
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void CommMysteryFunc_VramBankSet(void);

//--------------------------------------------------------------------------------------------
/**
 * @brief	BG������
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void CommMysteryFunc_BgInit( GF_BGL_INI * ini );

//------------------------------------------------------------------
/**
 * @brief	��������̂����炦�邩�`�F�b�N
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
extern int CommMysteryFunc_CheckGetGift(SAVEDATA *sv, GIFT_COMM_PACK *gcp);

#endif	// __COMM_MYSTERY_FUNC_H__
/*  */

//==============================================================================
/**
 * @file	wazatype_panel.c
 * @brief	�Z�^�C�v���̃p�l���f�[�^�̎�o���Ȃ�
 * @author	matsuda
 * @date	2005.12.02(��)
 */
//==============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/palanm.h"
#include "battle/wazatype_panel.h"
#include "graphic\batt_bg_def.h"

//==============================================================================
//	�萔��`
//==============================================================================
///�Z�^�C�v��CGR�f�[�^��X�����ɂ������邩
#define WAZATYPE_CGR_X_LEN	(18)
///�Z�^�C�v��CGR�f�[�^�ɓ����Ă���A�j����
#define WAZATYPE_CGR_ANM_NUM	(3)
///�Z�^�C�v��CGR�f�[�^��1�̃A�j����X�����T�C�Y
#define WAZATYPE_CGR_X_ONE	(WAZATYPE_CGR_X_LEN / WAZATYPE_CGR_ANM_NUM)
///�Z�^�C�v��CGR�f�[�^�����i�ɓn���ăf�[�^�����݂��Ă��邩
#define WAZATYPE_CGR_Y_LEN	(9)


//==============================================================================
//	�p���b�g�f�[�^
//==============================================================================
//�������̂��ߑf�f�[�^�Ŏ����Ă��܂��i�p���b�g�����炽�����ėe�ʂȂ����j
#include "graphic/battle_w_type12_ncl_txt.dat"
#include "graphic/battle_w_type04_ncl_txt.dat"
#include "graphic/battle_w_type14_ncl_txt.dat"
#include "graphic/battle_w_type10_ncl_txt.dat"
#include "graphic/battle_w_type08_ncl_txt.dat"
#include "graphic/battle_w_type02_ncl_txt.dat"
#include "graphic/battle_w_type17_ncl_txt.dat"
#include "graphic/battle_w_type06_ncl_txt.dat"
#include "graphic/battle_w_type13_ncl_txt.dat"
#include "graphic/battle_w_type18_ncl_txt.dat"
#include "graphic/battle_w_type15_ncl_txt.dat"
#include "graphic/battle_w_type16_ncl_txt.dat"
#include "graphic/battle_w_type05_ncl_txt.dat"
#include "graphic/battle_w_type09_ncl_txt.dat"
#include "graphic/battle_w_type03_ncl_txt.dat"
#include "graphic/battle_w_type07_ncl_txt.dat"
#include "graphic/battle_w_type11_ncl_txt.dat"
#include "graphic/battle_w_type01_ncl_txt.dat"
#include "graphic/battle_w_type00_ncl_txt.dat"


//==============================================================================
//	�f�[�^
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v����CGR�f�[�^
 */
//--------------------------------------------------------------
ALIGN4 static const u16 WazaTypeCgrID[] = {
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
};

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v���̃p���b�g�f�[�^
 */
//--------------------------------------------------------------
ALIGN4 static const u16 * const WazaTypePlttAdrs[] = {
	battle_w_type12_ncl,
	battle_w_type04_ncl,
	battle_w_type14_ncl,
	battle_w_type10_ncl,
	battle_w_type08_ncl,
	battle_w_type02_ncl,
	battle_w_type17_ncl,
	battle_w_type06_ncl,
	battle_w_type13_ncl,
	battle_w_type18_ncl,
	battle_w_type15_ncl,
	battle_w_type16_ncl,
	battle_w_type05_ncl,
	battle_w_type09_ncl,
	battle_w_type03_ncl,
	battle_w_type07_ncl,
	battle_w_type11_ncl,
	battle_w_type01_ncl,
};




//--------------------------------------------------------------
/**
 * @brief   �Z�p�l���̃O���t�B�b�N�������Ă���Arc��ID���擾
 * @retval  ARC_ID
 */
//--------------------------------------------------------------
int WazaPanel_ArcIDGet(void)
{
	return ARC_BATT_BG;
}

//--------------------------------------------------------------
/**
 * @brief   �Z�p�l���̃L�����N�^INDEX���擾
 * @param   waza_type		�Z�^�C�v(�莝�������̏ꍇ��-1)
 * @retval  �w�肵���Z�^�C�v�̃L�����N�^INDEX
 */
//--------------------------------------------------------------
u32 WazaPanel_CharIndexGet(int waza_type)
{
	u32 char_index;
	
	if(waza_type != -1){
		char_index = WazaTypeCgrID[waza_type];
	}
	else{
		char_index = BATTLE_W_TYPE00_NCGR_BIN;
	}
	return char_index;
}

//--------------------------------------------------------------
/**
 * @brief   �Z�p�l���̃p���b�g�f�[�^�A�h���X���擾
 * @param   waza_type		�Z�^�C�v(�莝�������̏ꍇ��-1)
 * @retval  �w�肵���Z�^�C�v�̃p���b�g�f�[�^�A�h���X
 */
//--------------------------------------------------------------
const u16 * WazaPanel_PalDataAdrsGet(int waza_type)
{
	const u16 *pal_data;
	
	if(waza_type != -1){
		pal_data = WazaTypePlttAdrs[waza_type];
	}
	else{
		pal_data = battle_w_type00_ncl;
	}
	return pal_data;
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�p�l���̃O���t�B�b�N�����[�h����
 *
 * @param   bgl				BGL�ւ̃|�C���^
 * @param   heap_id			�e���|�����Ŏg�p����q�[�v��ID
 * @param   frame_no		���[�h��̃t���[����
 * @param   trans_pos		���[�h��̓]���ʒu(��`�̍���̃L�����N�^�ԍ�)
 * @param   screen_type		GF_BGL_SCRSIZ_256x256 ��
 * @param   charcter		�W�J�ς݂̃L�����f�[�^�ւ̃A�h���X
 *
 * �]����͋Z�^�C�v�p�l���Ɠ����`��̗̈悪��`�Ŏ���Ă��鎖���O��ł��B
 * trans_pos�͂��̃��[�h��A��`�̍���̃L�����N�^�ʒu���w�肵�܂��B
 */
//--------------------------------------------------------------
void WazaPanel_CharLoad(GF_BGL_INI *bgl, int heap_id, int frame_no, u32 trans_pos, 
	int screen_type, const u8 *charcter)
{
	u32 y_len;
	int y;
	
	switch(screen_type){
	case GF_BGL_SCRSIZ_256x256:
	case GF_BGL_SCRSIZ_256x512:
		y_len = 32;
		break;
	case GF_BGL_SCRSIZ_512x256:
	case GF_BGL_SCRSIZ_512x512:
		y_len = 64;
		break;
	default:
		GF_ASSERT(0 && "�Ή����Ă��Ȃ��X�N���[���^�C�v�ł�\n");
		return;
	}
	
	//�L�����]��
	for(y = 0; y < WAZATYPE_CGR_Y_LEN; y++){
		GF_BGL_LoadCharacter(bgl, frame_no, 
			&charcter[WAZATYPE_CGR_X_LEN * 0x20 * y], 
			WAZATYPE_CGR_X_ONE * 0x20, trans_pos + (y_len*y));
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�p�l���̃L�����]�����g���₷���悤�ɂ܂Ƃ߂�����
 *
 * @param   bgl				BGL�ւ̃|�C���^
 * @param   waza_type		�Z�^�C�v(�莝�������̏ꍇ��-1)
 * @param   heap_id		�e���|�����Ŏg�p����q�[�vID
 * @param   frame_no		���[�h��̃t���[����
 * @param   trans_pos		���[�h��̓]���ʒu(��`�̍���̃L�����N�^�ԍ�)
 * @param   screen_type		GF_BGL_SCRSIZ_256x256 ��
 */
//--------------------------------------------------------------
void WazaPanel_EasyCharLoad(GF_BGL_INI *bgl, int waza_type, int heap_id, int frame_no, 
	u32 trans_pos, int screen_type)
{
	u32 arc_id, char_index;
	void *arc_data;
	NNSG2dCharacterData *char_data;
	
	arc_id = WazaPanel_ArcIDGet();
	char_index = WazaPanel_CharIndexGet(waza_type);

	arc_data = ArcUtil_CharDataGet(arc_id, char_index, 1, &char_data, heap_id);

	WazaPanel_CharLoad(bgl, heap_id, frame_no, trans_pos, screen_type, char_data->pRawData);

	sys_FreeMemoryEz(arc_data);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�p�l���̃L�����]���ŁA�����Z�^�C�v��CGR��A�����ăZ�b�g���܂��B
 * 			(�����Z�^�C�v��W�J����ꍇ�AWazaPanel_EasyCharLoad�ɔ�ׂ�FileOpen��
 *			��x�ōςނ悤�ɂȂ�܂�)
 *
 * @param   bgl				BGL�ւ̃|�C���^
 * @param   waza_type		�Z�^�C�v(�莝�������̏ꍇ��-1)
 * @param   heap_id			�e���|�����Ŏg�p����q�[�vID
 * @param   frame_no		���[�h��̃t���[����
 * @param   trans_pos		���[�h��̓]���ʒu(��`�̍���̃L�����N�^�ԍ�)(�]���Z����)
 * @param   trans_num		trans_pos�̔z��̐�
 * @param   screen_type		GF_BGL_SCRSIZ_256x256 ��
 */
//--------------------------------------------------------------
void WazaPanel_EasyCharLoad_ChainSet(GF_BGL_INI *bgl, int waza_type, int heap_id, int frame_no, 
	const u16 trans_pos[], int trans_num, int screen_type)
{
	u32 arc_id, char_index;
	void *arc_data;
	NNSG2dCharacterData *char_data;
	int i;
	
	arc_id = WazaPanel_ArcIDGet();
	char_index = WazaPanel_CharIndexGet(waza_type);

	arc_data = ArcUtil_CharDataGet(arc_id, char_index, 1, &char_data, heap_id);

	for(i = 0; i < trans_num; i++){
		WazaPanel_CharLoad(bgl, heap_id, frame_no, trans_pos[i], screen_type, char_data->pRawData);
	}

	sys_FreeMemoryEz(arc_data);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�p�l���̃p���b�g�]�����g���₷���悤�ɂ܂Ƃ߂�����
 *
 * @param   pfd				�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   waza_type		�Z�^�C�v(�莝�������̏ꍇ��-1)
 * @param   heap_id			�e���|�����Ŏg�p����q�[�vID
 * @param   req				���N�G�X�g�f�[�^�ԍ�
 * @param   palette_pos		�p���b�g�]���ʒu(�p���b�g�ԍ��Ŏw��)
 */
//--------------------------------------------------------------
void WazaPanel_EasyPalLoad(PALETTE_FADE_PTR pfd, int waza_type, int heap_id, 
	FADEREQ req, int palette_pos)
{
	const u16 *pal_data;
	
	pal_data = WazaPanel_PalDataAdrsGet(waza_type);
	PaletteWorkSet(pfd, pal_data, req, palette_pos * 16, 0x20);
}


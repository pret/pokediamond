//============================================================================================
/**
 * @file	app_tool.h
 * @brief	�c�[���֘A
 * @author	Hiroyuki Nakamura
 * @date	05.09.28
 *
 *	�K���ɒǉ����ĉ�����
 */
//============================================================================================
#ifndef APP_TOOL_H
#define APP_TOOL_H
#undef GLOBAL
#ifdef APP_TOOL_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
// HP�J���[
enum {
	HP_DOTTO_NULL = 0,		// HP=0
	HP_DOTTO_RED,			// ��
	HP_DOTTO_YELLOW,		// ��
	HP_DOTTO_GREEN,			// ��
	HP_DOTTO_MAX			// HP=MHP
};

// �P�x�ύX���N�G�X�gID
enum {
	APP_BRIGHT_IN = 0,	// �Á���
	APP_BRIGHT_OUT		// ������
};

enum {
	APP_WIPE_IN = 0,
	APP_WIPE_OUT,
};

//BMP�E�B���h�E�N���A�J���[�����}�N��
#define APP_WINCLR_COL(col)	(((col)<<4)|(col))

// ���I��߂�l
enum {
	APP_NUMSEL_NONE = 0,	// �}�O
	APP_NUMSEL_UP,			// �{
	APP_NUMSEL_DOWN,		// �|
};


//==============================================================================
//	�O���֐��錾
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   OAM�^�C�v����OAM�̃f�[�^�T�C�Y���擾����
 * @param   oam_type		OAM�^�C�v
 * @retval  �f�[�^�T�C�Y(Byte�P��)
 */
//--------------------------------------------------------------
GLOBAL int APP_OamTypeToSize(int oam_type);


//--------------------------------------------------------------
/**
 * @brief   �������������߂܂�
 *
 * @param   x		X�̋���
 * @param   y		Y�̋���
 *
 * @retval  int		��������
 *
 * ���W(0,0)���n�_�Ƃ��āA(x,y)�܂ł̒����������v�Z���܂�
 */
//--------------------------------------------------------------
GLOBAL u32 APP_StraightDistance(u32 x, u32 y);


//--------------------------------------------------------------------------------------------
/**
 * ���ݒl�̃Q�[�W�h�b�g�����擾
 *
 * @param	prm_now		���ݒl
 * @param	prm_max		�ő�l
 * @param	dot_max		�ő�h�b�g��
 *
 * @return	�h�b�g��
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 GetNumDotto( u32 prm_now, u32 prm_max, u8 dot_max );

//--------------------------------------------------------------
/**
 * @brief   �\���h�b�g�ƍő�h�b�g����HP�Q�[�W�̐F���擾����
 *
 * @param   put_dot		�\���h�b�g��
 * @param   max_dot		�ő�h�b�g��
 *
 * @retval  �Q�[�W�J���[
 */
//--------------------------------------------------------------
GLOBAL u8 GetGaugeDottoColor(u32 put_dot, u32 max_dot);

//--------------------------------------------------------------------------------------------
/**
 * HP�Q�[�W�̃J���[���擾
 *
 * @param	hp			���݂�HP
 * @param	mhp			�ő�HP
 * @param	max_dot		�ő�h�b�g��
 *
 * @return	�h�b�g��
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 GetHPGaugeDottoColor( u16 hp, u16 mhp, u32 max_dot );


//--------------------------------------------------------------------------------------------
/**
 * �P�x�ύX���N�G�X�g
 *
 * @param	req		���N�G�X�gID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void APP_BrightnessReq( u8 req );

//--------------------------------------------------------------------------------------------
/**
 * ���C�v�V�X�e���ɂ��t�F�[�h���N�G�X�g
 *
 * @param	req			���N�G�X�gID
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void APP_WipeStart( u8 req, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * ���ύX
 *
 * @param	num		��
 * @param	max		�ő�l
 *
 * @retval	"TRUE = �ύX����"
 * @retval	"FALSE = �ύX���ĂȂ�"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 NumSelectCheck( s16 * num, u16 max );

/**
 *	@brief	�A�[�J�C�u�n���h���E�t�@�C��idx���������ɁA
 *			�w��t���[���̃f�[�^��VRAM�֓]������
 *
 *	@param	bgl		�����ς݂�BGL�f�[�^
 *	@param	heapID	�e���|�����쐬�Ɏg���q�[�v�n���h��
 *	@param	handel	�I�[�v���ς݂̃A�[�J�C�u�t�@�C���n���h��
 *	@param	arcID	�A�[�J�C�u�t�@�C��ID
 *	@param	dataID	�A�[�J�C�u���f�[�^ID
 *	@param	frame	�f�[�^�]��GF_BGL_FRAME_***�w��
 *	@param	mode	0:�L����,1:�X�N���[��,2:�p���b�g
 *	@param	size	�]���T�C�Y�w��(0���w�肵���ꍇ�A�t�@�C���T�C�Y��)
 *	@param	ofs		�]���I�t�Z�b�g�w��
 */
extern void APP_ArcFileVramLoad(GF_BGL_INI* bgl,int heapID,
		ARCHANDLE* handle,int arcID,int fileID,int frame,int mode,u16 trans_siz,u16 ofs);

/**
 *	@brief	�I�[�v���ς݂̃A�[�J�C�u�t�@�C���n���h����n����
 *			�A�[�J�C�u���̃X�N���[���f�[�^��Unpack���Ď擾����
 *
 *	@param	handel	�I�[�v���ς݂̃A�[�J�C�u�t�@�C���n���h��
 *	@param	arcID	�A�[�J�C�u�t�@�C��ID
 *	@param	dataID	�A�[�J�C�u���f�[�^ID
 *	@param	heapID	�������m�ۂ���q�[�v�n���h��
 *
 *	@return void*	�m�ۂ����f�[�^�̈�̐擪�|�C���^
 *	
 *	��Unpack���邾���Ȃ̂ŁA����͎����ł�邱�ƁI
 */
extern void* APP_ArcScrFileUnpack(ARCHANDLE* handle,
	int arcID,int fileID,NNSG2dScreenData** pDat,int heapID);


#undef GLOBAL
#endif	/* APP_TOOL_H */

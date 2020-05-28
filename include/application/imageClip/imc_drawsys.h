//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_drawsys.h
 *	@brief		�C���[�W�N���b�v�`��V�X�e���f�[�^�Ǘ��V�X�e��
 *				���̃V�X�e�����g�p����΁A���ׂĕ`��o����悤�ɂ��܂��B
 *	@author		tomoya takahashi
 *	@data		2005.09.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_DRAWSYS_H__
#define __IMC_DRAWSYS_H__

#include <nnsys.h>
#include "include/system/swsprite.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "system/softsprite.h"
#include "res_manager.h"
#include "bg_system.h"
#include "clact.h"
#include "include/system/clact_util.h"
#include "include/system/clact_util_res.h"
#include "include/system/clact_util_vram.h"

#undef GLOBAL
#ifdef	__IMC_DRAWSYS_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define	IMC_DRAW_USE_RES_NUM	(4)		// �L�����N�^�@�p���b�g�@�Z���@�Z���A�j��

//-------------------------------------
//	
//	�L�����N�^�f�[�^�̎w��ʒu�ɐF��
//	param�Ŗ������`�F�b�N
//	�߂�l�p
//	
//=====================================
enum{
	IMC_DRAW_CHAR_CHECK_FALSE,
	IMC_DRAW_CHAR_CHECK_TRUE,
	IMC_DRAW_CHAR_CHECK_ERR,
};


//-------------------------------------
//	�L�����N�^�f�[�^�̃X�N���[���\�����W
//=====================================


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�`��f�[�^���܂Ƃ߂��\����
//	
//=====================================
typedef struct {
	// �X�v���C�g�f�[�^
	SWSP_SYS_PTR	SWSP_drawSys;		// �X�v���C�g�`��V�X�e��
	SWSP_CHAR_PTR*	SWSP_charData;		// �L�����N�^�f�[�^�z��
	int					SWSP_charNum;		// �o�^�\�ő吔
	int					SWSP_charNow;		// ���̓o�^��
	SWSP_PLTT_PTR*	SWSP_plttData;		// �p���b�g�f�[�^�z��
	int					SWSP_plttNum;		// �o�^�\�ő吔
	int					SWSP_plttNow;		// ���̓o�^��
	BOOL			SWSP_DrawFlag;			// �`��t���O

	SOFT_SPRITE_MANAGER* SSM_drawSys;		// �|�P�����`��p�X�v���C�g
	BOOL SSM_DrawFlag;						// �|�P�����`��t���O

	// �A�N�Z�T���p�p���b�g�I�t�Z�b�g�e�[�u��
	u8* accePlttOfsTbl;

	// �A�N�Z�T�����|�P�����p�A���p�b�N��̃L�����N�^�f�[�^
	RES_MANAGER_PTR		SWSP_charRes;		// �L�����N�^�f�[�^�̃��\�[�X	
	NNSG2dCharacterData** SWSP_UPchar;		// �A���p�b�N��̃f�[�^
	int					SWSP_UPcharNum;		// �A���p�b�N��̃f�[�^��

	// BG�f�[�^
	GF_BGL_INI*		BG_Ini;
	
	// OBJ�f�[�^
	CLACT_SET_PTR		clactSet;			// �Z���A�N�^�[�Z�b�g
	CLACT_U_RES_MANAGER_PTR	resMan[IMC_DRAW_USE_RES_NUM];	// ���\�[�X�}�l�[�W��
	CLACT_U_EASYRENDER_DATA		renddata;	// �ȈՃ����_�[�f�[�^

} IMC_DRAW_DATA;

//-------------------------------------
//	
//	���\�[�X�o�^�f�[�^
//	
//=====================================
typedef struct {
	// �X�v���C�g
	SWSP_CHARDATA* SWSP_charTbl;
	int	SWSP_charNum;
	SWSP_PLTTDATA* SWSP_plttTbl;
	int	SWSP_plttNum;

	// ���̏�Ŕj�����郊�\�[�X�̊i�[��
	RES_MANAGER_PTR		SWSP_charRes;		// �L�����N�^�f�[�^�̃��\�[�X	
	RES_MANAGER_PTR		SWSP_plttRes;		// �p���b�g�f�[�^�̃��\�[�X	
} IMC_DRAW_LOADRES_DATA;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e����`��o����悤�Ɋ���ݒ肵�܂�
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_SetUp( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ݒ肵�����f�[�^��j�����܂�
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_PutBack( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��p�V�X�e���̐ݒ���s���܂��B
 *
 *	@param	drawData	�`��f�[�^
 *
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_InitSys( IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���f�[�^��j������
 *
 *	@param	drawData	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DeleteSys( IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��֐��̂���`��V�X�e���̕`��
 *
 *	@param	drawData	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DrawSys( IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���\�[�X�̓ǂݍ��݂��s���܂�	�X��Vram��ɓW�J���܂�
 *
 *	@param	drawData	�`��f�[�^�i�[�̈�
 *	@param	loadData	�ǂݍ��ރ��\�[�X�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_LoadResource( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���\�[�X�̔j�����s���܂�
 *
 *	@param	drawData	�`��f�[�^�i�[�̈�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DeleteResource( IMC_DRAW_DATA* drawData );


//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[�o�^
 *
 *	@param	drawData	���[�N
 *	@param	contid		�Ǘ�ID
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	pri			�D�揇��
 *	@param	draw_area	�`��G���A
 *
 *	@return	�A�N�^�[���[�N
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_WORK_PTR IMC_DRAW_AddClact( IMC_DRAW_DATA* drawData, int contid, int x, int y, int pri, int draw_area );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�ǂݍ���
 *
 *	@param	drawData		�`��V�X�e���f�[�^
 *	@param	fileIdx			�t�@�C���C���f�b�N�X
 *	@param	dataIdx			�f�[�^�C���f�b�N�X
 *	@param	comp			���k�t���O
 *	@param	vramType		Vram�^�C�v
 *	@param	id				�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_LoadCharData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int vramType, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�ǂݍ���
 *
 *	@param	drawData		�`��V�X�e���f�[�^
 *	@param	fileIdx			�t�@�C���C���f�b�N�X
 *	@param	dataIdx			�f�[�^�C���f�b�N�X
 *	@param	comp			���k�t���O
 *	@param	vramType		Vram�^�C�v
 *	@param	load_num		�p���b�g�ǂݍ��ݐ�
 *	@param	id				�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_LoadPlttData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int vramType, int load_num, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���f�[�^�ǂݍ���
 *
 *	@param	drawData		�`��V�X�e���f�[�^
 *	@param	fileIdx			�t�@�C���C���f�b�N�X
 *	@param	dataIdx			�f�[�^�C���f�b�N�X
 *	@param	comp			���k�t���O
 *	@param	id				�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_LoadCellData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�j���f�[�^�ǂݍ���
 *
 *	@param	drawData		�`��V�X�e���f�[�^
 *	@param	fileIdx			�t�@�C���C���f�b�N�X
 *	@param	dataIdx			�f�[�^�C���f�b�N�X
 *	@param	comp			���k�t���O
 *	@param	id				�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_LoadCellAnmData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^���\�[�X�f�[�^�݂̂̔j��
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	id			�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_DeleteCharRes( IMC_DRAW_DATA* drawData, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g���\�[�X�f�[�^�݂̂̔j��
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	id			�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_DeletePlttRes( IMC_DRAW_DATA* drawData, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z�����\�[�X�f�[�^�݂̂̔j��
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	id			�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_DeleteCellRes( IMC_DRAW_DATA* drawData, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�j�����\�[�X�f�[�^�݂̂̔j��
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	id			�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_DeleteCellAnmRes( IMC_DRAW_DATA* drawData, int id );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�p�̓ǂݍ��ރt�@�C�����쐬
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	loadData	�쐬��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_MakeLoadSWSP_samp( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�p�̓ǂݍ��݃t�@�C����j������
 *
 *	@param	loadData	�ǂݍ��݃f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DestLoadSWSP( IMC_DRAW_LOADRES_DATA* loadData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�̓o�^
 *
 *	@param	drawData	�`��f�[�^�\����
 *	@param	buff		�L�����N�^�f�[�^�o�b�t�@
 *	@param	char_no		�o�^�L�����N�^�i���o�[�i�A�N�Z�T���i���o�[��Link�j
 *
 *	@return	�A���p�b�N��̃L�����N�^�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dCharacterData* IMC_DRAW_SetCharData( IMC_DRAW_DATA* drawData, void* buff, int char_no );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ʏ펞�̃E�B���h�E�}�X�N�ݒ�
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_WndMaskNormalSet( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F�N�g�𓮂����Ă���Ƃ��̃E�B���h�E�}�X�N��ݒ�
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_WndMaskObjMoveSet( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I���`�F�b�N���̕\���D�揇�ʐݒ�
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_EndCheckBGPri( void );

//-----------------------------------------------------------------------------
/**
*		�L�����N�^�f�[�^�����āA�ق�Ƃɂ��̈ʒu�ɔ����F�ȊO�̐F�ɂȂ���
*		���邩���`�F�b�N����
*/
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�̎w��ʒu�ɐF��param�Ŗ������`�F�b�N
 *
 *	@param	char_data		�`�F�b�N�Ɏg���L�����N�^�f�[�^
 *	@param	offs_x			x�I�t�Z�b�g
 *	@param	offs_y			y�I�t�Z�b�g
 *	@param	param			�`�F�b�N�F�i���o�[
 *
 *	@retval	IMC_DRAW_CHAR_CHECK_TRUE	param�̐F
 *	@retval	IMC_DRAW_CHAR_CHECK_FALSE	param�̐F����Ȃ�
 *	@retval	IMC_DRAW_CHAR_CHECK_ERR		�G���[
 *
 * �P�U�F����
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_DRAW_CharCheck( NNSG2dCharacterData* char_data, int offs_x, int offs_y, int param );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���pV�u�����N�֐�
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_VBlank( IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���p�\�t�g�E�F�A�X�v���C�g�f�[�^�������m��
 *
 *	@param	drawData	�ǂݍ��݃f�[�^���[�N	
 *	@param	heap 
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_SWSPResDataAllocMemory( IMC_DRAW_LOADRES_DATA* loadData, int heap );

//-----------------------------------------------------------------------------
/**
 *		�v���C���[�p�֐�	
 *			�C���[�W�N���b�v�ȊO�̃V�X�e������g�p���Ă��炤�Ƃ��́A�������̊֐��ŏ������Ȃǂ��s���B
 *			�܂��E�p���b�g�̕\���ɕK�v�ȕ��̂ݍ쐬����悤�ɂȂ��Ă��܂��B
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v�v���C���[�p	�������֐�
 *	@param	drawData	�`��f�[�^
 *	@param	cp_swsp		�C���[�W�N���b�v�p�\�t�g�E�F�A�X�v���C�g�V�X�e���������f�[�^
 *	@param	heap		�q�[�vID
 *
 *	@retval	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_InitSysPlayer( IMC_DRAW_DATA* drawData, const SWSP_SYSDATA* cp_swsp, int heap );
GLOBAL void IMC_DRAW_InitSysPlayerBG( IMC_DRAW_DATA* drawData, GF_BGL_INI* BG_Ini, int heap );



//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���f�[�^��j������
 *
 *	@param	drawData	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DeleteSysPlayer( IMC_DRAW_DATA* drawData );
GLOBAL void IMC_DRAW_DeleteSysPlayerBG( IMC_DRAW_DATA* drawData );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���pV�u�����N�֐�
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_VBlankPlayer( IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��֐��̂���`��V�X�e���̕`��
 *
 *	@param	drawData	�`��f�[�^
 *	@param	center_x	���S��
 *	@param	center_y	���S��
 *	@param	rota_num	��]�p
 *	@param	p_scale		�X�P�[���x�N�g��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DrawSysPlayer( IMC_DRAW_DATA* drawData, int center_x, int center_y, u16 rota_num, const VecFx32* p_scale );


//-----------------------------------------------------------------------------
/**
 *		preview�V�X�e����p
 */
//-----------------------------------------------------------------------------
// preview�V�X�e��
GLOBAL void IMC_DRAW_InitSysPrev( IMC_DRAW_DATA* drawData, int heap );
GLOBAL void IMC_DRAW_DeleteSysPrev( IMC_DRAW_DATA* drawData );
GLOBAL void IMC_DRAW_VBlankPrev( IMC_DRAW_DATA* drawData );
GLOBAL void IMC_DRAW_DrawSysPrev( IMC_DRAW_DATA* drawData );



#undef	GLOBAL
#endif		// __IMC_DRAWSYS_H__


//============================================================================================
/**
 * @file	poketch_view.h
 * @bfief	�|�P�b�`�i�`�敔���L�j�w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_VIEW_H_
#define _POKETCH_VIEW_H_

#include "system\arc_tool.h"
#include "system\arc_util.h"

#include "poketch_sound.h"
#include "poketch_act.h"
#include "poketch_arc.h"


//====================================================
// �`��R�}���h�e�[�u��
//====================================================
typedef struct {
	u32			cmd;
	TCB_FUNC	func;
	u32			work_size;
}POKETCH_VIEW_CMD;


//====================================================
// �`��R�}���h���[�N�̌^�錾
//====================================================
typedef	struct _POKETCH_CMD_WORK  POKETCH_CMD_WORK;

//====================================================
// �ғ����̃R�}���h�i���o�[��ۑ����Ă����z��̃^�C�v
//====================================================
typedef u32 POKETCH_CMD_STORE;

enum {
	CMD_STOREWK_MAX = 0,
	CMD_STOREWK_MAGICNUMBER,

	CMD_STORE_HEADER_SIZE,		// �z��͍Œ�ł����̗v�f�����K�v�i���w�b�_�Ƃ��Ďg���j
};

//====================================================
// ���̂��萔
//====================================================

enum {
	POKETCH_DEFAULTCOLOR_L1_POS = 0x04,		///< �P�Ԗڂɖ��邢�F�̔z�u�ԍ�
	POKETCH_DEFAULTCOLOR_L2_POS = 0x0f,		///< �Q�Ԗڂɖ��邢�F�̔z�u�ԍ�
	POKETCH_DEFAULTCOLOR_L3_POS = 0x08,		///< �R�Ԗڂɖ��邢�F�̔z�u�ԍ�
	POKETCH_DEFAULTCOLOR_L4_POS = 0x01,		///< �S�Ԗڂɖ��邢�F�̔z�u�ԍ�
};


#define USE_POKEICON_X2		// ���ꂪ�L�����ƃA�C�R���Q�{�T�C�Y�i��������1.5�{�j

//-----------------------------------------------
/**
 *	nanr�t�@�C���Œ�`����Ă���A�j���V�[�P���X
 */
//-----------------------------------------------
enum {
	POKETCH_POKEICON_ANM_OFF_15L,
	POKETCH_POKEICON_ANM_OFF_15R,
	POKETCH_POKEICON_ANM_NORMAL_15L,
	POKETCH_POKEICON_ANM_NORMAL_15R,
	POKETCH_POKEICON_ANM_OFF_20L,
	POKETCH_POKEICON_ANM_OFF_20R,
	POKETCH_POKEICON_ANM_NORMAL_20L,
	POKETCH_POKEICON_ANM_NORMAL_20R,
};

//-----------------------------------------------
/**
 *	�e�A�v�����g�p����A�j���V�[�P���X�V���{��
 */
//-----------------------------------------------
enum {
#ifdef USE_POKEICON_X2
	POKEICON_ANM_OFF_L = POKETCH_POKEICON_ANM_OFF_20L,
#else
	POKEICON_ANM_OFF_L = POKETCH_POKEICON_ANM_OFF_15L,
#endif

	POKEICON_ANM_OFF_R,
	POKEICON_ANM_NORMAL_L,
	POKEICON_ANM_NORMAL_R,
};

//-----------------------------------------------
/**
 *	�A�C�R���T�C�Y��`
 */
//-----------------------------------------------
enum {
#ifdef USE_POKEICON_X2
	POKEICON_WIDTH	= 64,
	POKEICON_HEIGHT	= 48,
#else
	POKEICON_WIDTH	= 48,
	POKEICON_HEIGHT	= 36,
#endif

	POKEICON_HALF_WIDTH		= POKEICON_WIDTH/2,
	POKEICON_HALF_HEIGHT	= POKEICON_HEIGHT/2,
};

//====================================================
// �v���g�^�C�v
//====================================================
extern void PoketchView_SetBaseColorPalette( u32 bg_palno, u32 obj_palno );
extern void PoketchView_SetHighColorPalette( u32 bg_palno, u32 obj_palno );
extern void PoketchView_GetColorPalette( u16* dst );
extern void PoketchView_SetColorPaletteNumber( u32 num );




extern void PoketchViewTool_CmdStoreInit(POKETCH_CMD_STORE *store, u32 max);
extern BOOL PoketchViewTool_WaitCommand(POKETCH_CMD_STORE *store, u32 cmd);
extern BOOL PoketchViewTool_WaitCommandAll(POKETCH_CMD_STORE *store);
extern void PoketchViewTool_SetCommand(const POKETCH_VIEW_CMD *cmd_tbl,u32 cmd, void *view_wk,
		const void *vpara, POKETCH_CMD_STORE *store, u32 taskpri, u32 heapID);
extern void PoketchViewTool_DelCommand(POKETCH_CMD_STORE *store, POKETCH_CMD_WORK *cwk);
extern void* PoketchViewTool_GetViewWork(POKETCH_CMD_WORK *cwk);
extern const void* PoketchViewTool_GetViewParam(POKETCH_CMD_WORK *cwk);
extern void* PoketchViewTool_GetCmdWork(POKETCH_CMD_WORK *cwk);
extern u32 PoketchViewTool_GetSeq(POKETCH_CMD_WORK *cwk);
extern void PoketchViewTool_FwdSeq(POKETCH_CMD_WORK *cwk);
extern void PoketchViewTool_SetSeq(POKETCH_CMD_WORK* cwk, u32 seq );

extern void PoketchViewTool_MakeWindowScrn( u16 *buf, u32 charno, u32 width, u32 height, u32 chardata_width, u32 palno );
extern void PoketchViewTool_MakeBlockScrn( u16 *buf, u32 scr_x, u32 scr_y, u32 scr_w, u32 charno, u32 chardata_width, u32 palno );
extern void PoketchViewTool_TransformColorData( u16* col, u32 max );
extern void PoketchViewTool_TransSingleColorData( u32 colno, u32 palno );
extern void PoketchViewTool_SetupPokeIconPalette( u32 offs );
extern void PoketchViewTool_SetupPokeIconCgx( u32 charno, const u32* datIdx, u32 max, BOOL anmFlag );

extern NNSG2dOamManagerInstance* PoketchGetOamm( void );
extern PACTSYS*  PoketchGetActSys( void );
extern GF_BGL_INI*  PoketchView_GetAppBglWork( void );

extern void PoketchView_TestScreenMake( GF_BGL_INI* bgl, u32  app_no , u32 bg_frame );

#endif


//=============================================================================
/**
 * @file	fieldsys.h	
 * @brief	�t�B�[���h�}�b�v�V�X�e��
 * @author	GAME FREAK inc.
 */
//=============================================================================
#ifndef	__FIELDSYS_H__
#define	__FIELDSYS_H__

//==============================================================================
//	include
//==============================================================================
#include "field_common.h"

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���
#include "system/pms_data.h"
#include "worldmap_def.h"
#include "mapresource_def.h"

#include "field_glb_state.h"
#include "fog_sys.h"
#include "field_light.h"
#include "weather_sys_def.h"
#include "field_anime_def.h"

#include "system\procsys.h"

#include "fieldobj.h"
#include "player.h"
#include "field/poketch.h"

#include "field_3d_anime.h"
#include "div_map.h"
#include "map_tool.h"
#include "ug_radar.h"

#include "place_name.h"

#include "field_effect.h"
#include "board.h"
#include "comm_union.h"
#include "comm_union_view.h"

#include "union_board.h"

#include "sway_grass_enc.h"

#include "field/location.h"

#include "application\tradelist.h"

#include "sp_attribute_def.h"
#include "floor_touch.h"
#include "honey_tree_enc.h"
#include "savedata/fnote_mem.h"

#include "itemtool/myitem.h"

#include "savedata/b_tower.h"
#include "b_tower_scr.h"

#include "savedata/regulation.h"

#include "map_mode.h"

#include "application/zukanlist/zkn_data_work.h"

//--------------------------------------------------------------
//	extern
//--------------------------------------------------------------
#undef GLOBAL
#ifdef __FIELDSYS_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	�r���{�[�h�A�N�^
//--------------------------------------------------------------
enum
{
	FIELDSYS_BLACTSET_FIELD_OBJ = 0,	///<�t�B�[���hOBJ add kaga
	FIELDSYS_BLACTSET_DEBUG_KUSA,		///<�����p add kaga
	FIELDSYS_BLACTSET_COMM,				///<�ʐM�G�t�F�N�g add ohno
	FIELDSYS_BLACTSET_FIELD_EFFECT,		///<�t�B�[���h�G�t�F�N�g add kaga
	
	FIELDSYS_BLACTSET_NUM,				///<�r���{�[�h�A�N�^�[�Z�b�g�o�^��
};

//--------------------------------------------------------------
//	�t�B�[���h�G�t�F�N�g
//--------------------------------------------------------------
#define FE_EFFECT_MAX			(FE_PROC_MAX)
#define FE_HEAP_SIZE			(0x18000)
//#define FE_EOA_MAX				(64)	///<�t�B�[���h�G�t�F�N�g�@EOA�ő吔
#define FE_EOA_MAX				(80)	///<�t�B�[���h�G�t�F�N�g�@EOA�ő吔
#define FE_BLACT_MAX			(32)	///<�t�B�[���h�G�t�F�N�g�@�r���{�[�h�ő吔
#define FE_BLACT_MDL_MAX		(32)
#define FE_BLACT_MDL_HEAP_SIZE	(0x0500*(FE_BLACT_MDL_MAX/2))
#define FE_BLACT_ANM_MAX		(32)
#define FE_BLACT_ANM_HEAP_SIZE	(0x0080*(FE_BLACT_ANM_MAX/2))
#define FE_BLACT_TEX_MAX		(32)
#define FE_BLACT_TEX_HEAP_SIZE	(0x0800*FE_BLACT_TEX_MAX)

//------------------------------------------------------------------
///	�T�u��ʂ̎��
//------------------------------------------------------------------
typedef enum {
	FIELD_SUBSCRN_POKETCH = 1,		///<�ʏ�i�|�P�b�`�j
	FIELD_SUBSCRN_UNDER,			///<�Y�z�i���[�_�[��ʁj
	FIELD_SUBSCRN_UNION,			///<���j�I�����[�� (�f�����)
	FIELD_SUBSCRN_NO_POKETCH,		///<�|�P�b�`�Ȃ��A�{�[���̂݉��

	FIELD_SUBSCRN_MAX,
}FIELD_SUBSCRN_TYPE;

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	���䃏�[�N�p��`
//--------------------------------------------------------------
typedef struct _CONTROL_WORK CONTROL_WORK;

//--------------------------------------------------------------
///	ENCOUNT_CHECK�\����
//--------------------------------------------------------------
typedef struct {
	u16	walk_count;		// �����J�E���^
//	u16	before_attr;	// �O��̃A�g���r���[�g
//	u16	plus_per;		// �m���v���X�l
	u16	WinPokeCount;
}ENCOUNT_CHECK;

//--------------------------------------------------------------
///EVENTDATA�\���̂ւ̃|�C���^
//--------------------------------------------------------------
typedef struct EVENT_DATA EVENT_DATA;

//--------------------------------------------------------------
//--------------------------------------------------------------
typedef struct MMDL_WORK MMDL_WORK;

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v�����胏�[�N
 *
 * FIELDSYS_WORK�̃����o�̒��ŁA�t�B�[���h�}�b�v���ł���
 * �A�N�Z�X���Ȃ����̂͂�����ֈڂ����ƁB
 */
//--------------------------------------------------------------
typedef struct FIELDMAP_WORK FIELDMAP_WORK;

//--------------------------------------------------------------
///�V�X�e���R���g���[�����[�N�\����
//--------------------------------------------------------------
struct _FIELDSYS_WORK	{

	CONTROL_WORK * ctrl;	///<����p���[�N

	FIELDMAP_WORK * fldmap;

	GF_BGL_INI * bgl;		///<BGL�f�[�^

	SAVEDATA * savedata;	///<�Z�[�u�����Q�[���i�s�f�[�^

	GMEVENT_CONTROL * event;	///<�C�x���g����

	EVENT_DATA * eventdata;		///<�]�[�����C�x���g�f�[�^

	FIELD_SUBSCRN_TYPE subscreen;	///<�T�u��ʂ̎�ގw��
	//fldmap�Ɉړ�	POKETCH_WORK * poketch;

	LOCATION_WORK * location;		///<�ʒu���

	GF_CAMERA_PTR	camera_ptr;		//�J�����|�C���^
	DMC_PTR	map_cont_dat;	//�������[�h�\���̂̌o�R�Q�Ɨp�|�C���^
	
	WORLD_MAP_PTR World;

	MAP_RESOURCE_PTR MapResource;	//�t�B�[���h�\�����\�[�X�Q�Ɨp�|�C���^
	MMDL_WORK * mmdl;			///<�G���A�ʓ��샂�f�����X�g�f�[�^�ւ̃|�C���^
	
	///PCD_PTR player_cont_dat;//���@���W�\���̂̌o�R�Q�Ɨp�|�C���^
	FIELD_OBJ_SYS_PTR fldobjsys;	//�t�B�[���hOBJ�Q��*
	PLAYER_STATE_PTR player;	//���@���Q�ƃ|�C���^
	
	FE_SYS *fes;				//�t�B�[���h�G�t�F�N�g�Q�ƃ|�C���^
	
	GLST_DATA_PTR		glst_data;		// ���C�g�E�}�e���A���̏�ԕۑ��̈�
	FOG_DATA_PTR		fog_data;		// �t�H�O�̏�ԕۑ��̈�
	LIGHT_CONT_PTR		light_cont_data;// �P���\�����C�g�E�}�e���A������f�[�^
	//fldmap�Ɉړ�	WEATHER_MANAGER_PTR weather_data;	// �V�C�f�[�^
	//fldmap�Ɉړ�	FIELD_ANIME_PTR		field_trans_anime;	// �]���A�j���V�X�e��
	FLD_3D_ANM_MNG_PTR		field_3d_anime;
	ANIME_CONT_MNG_PTR	AnimeContMng;
	SMD_PTR				SpMatData;
	MTL_CONST_PTR		map_tool_list;
///	DFL_CONST_PTR		div_func_list;
	DIV_MAP_MODE		DivMapMode;
	//fldmap�Ɉړ�	PNC_PTR				place_name_cont;//�n���\��

	BOARD_WORK * board;		// �Ŕ\��
	
	BOOL	main_mode_flag;

	UG_RADAR_WORK    *UnderGroundRadar;		// �Y�z���[�_�[���[�N�Q�Ɨp�|�C���^
	MAP_MODE MapMode;		//�n�ォ�n�����𔻕ʂ���̂Ɏg�p
	const MAP_MODE_DATA * MapModeData;

	ENCOUNT_CHECK	encount;	// �G���J�E���g�`�F�b�N�p���[�N
	COMM_UNIONROOM_WORK *union_work;			// ���j�I�����[���p���[�N�|�C���^
	COMM_UNIONROOM_VIEW *union_view;			// ���j�I�����[���`�揈���p���[�N
	UNION_BOARD_WORK    *union_board;			// ���j�I�����[���f���i�T�u��ʁj���[�N
	TRADELIST_WORK      *tradelist_work;

	TP_TO_3D_PTR		TpTo3DPtr;				//3D���ʂƂ̃^�b�`����p

	int	startmenu_pos;					//�t�B�[���h/�n���̃��j���[�̃J�[�\���ʒu

	SWAY_GRASS_PTR SwayGrass;
	BAG_CURSOR * bag_cursor;			//�o�b�O�̃J�[�\�����
	FNOTE_DATA * fnote;					//�Ώۖ`���m�[�g�y�[�W�ւ̃|�C���^
	EHL_PTR	ExHeightList;
	M3DOL_PTR Map3DObjExp;			//�g���z�u���f��

	HTD_PTR HoneyTreePtr;			//���h��p

	BTOWER_SCRWORK*	btower_wk;		///<�o�g���^���[����p���[�N�|�C���^
    const REGULATION* regulation;     ///< ����K�p����郌�M�����[�V�����|�C���^
	ZKN_DATA_WORK*	p_zukandata;	///<�}�ӃO���[�o���f�[�^
	BOOL scope_mode_flag;				///<�]�������[�h�t���O
};



//==============================================================================
//	�O���Q��
//==============================================================================
GLOBAL void FieldSystemProc_SeqHold(void);
GLOBAL void FieldSystemProc_SeqHoldEnd(void);


extern const PROC_DATA FieldProcData;

extern BOOL GameSystem_CheckSubProcExists(FIELDSYS_WORK * fsys);
extern void GameSystem_StartSubProc(FIELDSYS_WORK * fsys, const PROC_DATA * proc, void * param);

extern BOOL GameSystem_CheckFieldProcExists(FIELDSYS_WORK * fsys);
extern BOOL GameSystem_CheckFieldMain(FIELDSYS_WORK * fsys);
extern void GameSystem_CreateFieldProc(FIELDSYS_WORK * fsys);
extern void GameSystem_FinishFieldProc(FIELDSYS_WORK * fsys);

//���Ԃ�f�o�b�O�ł����g�p���Ȃ�
extern void GameSystem_FinishGame(FIELDSYS_WORK * fsys);


GLOBAL struct _POKETCH_WORK* GetPoketchMainWorkPtr(void);

extern GF_BGL_INI * FieldBglIniGet( void * fsys );
extern SAVEDATA * GameSystem_GetSaveData(void * fsys);


#undef GLOBAL


//�T�u�v���Z�X�̎Q�Ɛ錾�͂��̒��Ɂc
#include "field_subproc.h"

#endif	/* __FIELDSYS_H__ */

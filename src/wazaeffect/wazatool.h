//==============================================================================
/**
 * @file	wazatool.h
 * @brief	�Z�G�t�F�N�g�֘A�̔ėp�c�[���̃w�b�_
 * @author	matsuda
 * @date	2005.09.02(��)
 */
//==============================================================================
#ifndef __WAZATOOL_H__
#define __WAZATOOL_H__

#include "we_sys.h"
#include "system/clact_tool.h"
#include "system/laster.h"



//==============================================================================
//	�萔��`
//==============================================================================
//--------------------------------------------------------------
//	�q�[�v�ݒ�
//--------------------------------------------------------------
///�Z�G�t�F�N�g����֐��Œʏ�g�p����q�[�v�̈�
#define WAZAEFF_HEAP_AREA		(HEAPID_BATTLE)	//(APP_W_HEAP_AREA)

///GetWazaEffPos�֐��p
enum{
	PM_X,		///<�|�P�����X�̒��S���WX
	PM_Y,		///<�|�P�����X�̒��S���WY
	EFF_X,		///<�|�P�����̃I�t�Z�b�g�֌W�Ȃ��̃G�t�F�N�g�Œ蒆�S���WX
	EFF_Y,		///<�|�P�����̃I�t�Z�b�g�֌W�Ȃ��̃G�t�F�N�g�Œ蒆�S���WY
};

///�Z�G�t�F�N�g�ł̈ꉞ��Ƃ���A�N�^�[�\�t�g�E�F�A�v���C�I���e�B
#define WAZAEFF_ACT_SOFTPRI		(100)

///�Z�G�t�F�N�g�ł̈ꉞ��Ƃ���A�N�^�[BG�v���C�I���e�B
#define WAZAEFF_ACT_BGPRI		(1)

//--------------------------------------------------------------
//	���Z�G�t�F�N�g�\�[�X����̈��p��(������K�v���͌����_�ł͕s��)
//--------------------------------------------------------------
#define MINE_SIDE_OFFSET_Y	8	//�������̍��W�������̂ŋ����I�ɵ̾�Ăŉ��ɂ��炷

// -----------------------------------------
//
//	�I�t�Z�b�g�p�̒萔
//
// -----------------------------------------
enum EOFS_MODE {
	
	WAZAEFF_OFS_MODE_BOTTOM = 0,			///< ����
	WAZAEFF_OFS_MODE_TOP,					///< �㕔

};

//--------------------------------------------------------------
//	�c���p�萔
//--------------------------------------------------------------
//�c���v�Z�f�[�^�Ȃǂ̔z��Q�Ɨp
enum{
	WAZATOOL_ZANZOU_0,			// �c���P
	WAZATOOL_ZANZOU_1,			// �c���Q
	WAZATOOL_ZANZOU_2,			// �c���R
	WAZATOOL_ZANZOU_3,			// �c���S
	WAZATOOL_ZANZOU_MAX,		// �c���̃}�b�N�X
};

// �c�����f�^�C�v
enum{
	WAZATOOL_ZANZOU_TYPE_MATRIX,	// �^�C�v	���W
	WAZATOOL_ZANZOU_TYPE_SCALE,		// �^�C�v	�g��k��
};

//==============================================================================
//	�\���̒�`
//==============================================================================
///���A�N�^�[���ڐA���₷���悤�ɁA
///���A�N�^�[�̃��[�N�\�� �{ �ڐA���s���₷���悤�ɂ��������[�N���v���X��������
typedef struct{
	WE_SYS_PTR we_sys;
	CATS_SYS_PTR csp;
	CLACT_WORK_PTR act;
	TCB_PTR tcb;
	
	TCB_FUNC move;		///<TCB����֐�
	TCB_FUNC next_move;	///<SetWorkSeq�Ŋ֐��|�C���^��ėp���[�N�ɃZ�b�g���Ă����̂͂����ɕۑ�
	s16 x;				///<���A�N�^�[�ł͍��W�𒼂ł������Ă���������͂��ꂪ�o���Ȃ��̂ŁA
	s16 y;				///<������ɍ��W���R�s�[���Ă����邱�Ƃ�z��
	s16 dx;
	s16 dy;
	s16 work[8];		///<�A�N�^�[�X�������Ă����ėp���[�N
}OLDACT_WORK;

//-------------------------------------
//	
//	�ėp����v�Z�p�\����
//	
//	���W�v�Z
//	�g�k�v�Z
//=====================================
typedef struct{
	s16 x;				// ���v�Z����
	s16 y;				// ���v�Z����
	s32 work[8];		// ���샏�[�N
} WAZATOOL_CALCMOVE;
//==============================================================================
//	�^��`
//==============================================================================
// �ėp�v�Z�̊֐��|�C���^�^
typedef BOOL (*WAZATOOL_CALCFUNC)( WAZATOOL_CALCMOVE* p_wtc );


//-------------------------------------
//	
//	�ėp����v�Z�p�\����
//	�����v�Z
//	
//	��]�ȂǂɎg�p�ł��܂��B
//=====================================
typedef struct{
	s32 num;
	s32 work[4];
} WAZATOOL_CALCMOVE_ONE;

//-------------------------------------
//	
//	�c������V�X�e��
//	
//=====================================
typedef struct{
	// ����f�[�^
	s16	x;	// �f�t�H���g�ʒu
	s16 y;	// �f�t�H���g�ʒu�@
	WAZATOOL_CALCMOVE	move_param[ WAZATOOL_ZANZOU_MAX ];
	WAZATOOL_CALCFUNC	move_func;
	// �c���f�[�^
	CATS_ACT_PTR cap[ WAZATOOL_ZANZOU_MAX ];

	u16 wait;		// �e�I�u�W�F�N�g�𓮂����^�C�~���O
	u16 count;		// ����^�C�~���O�J�E���^
	u8 zanzou_num;	// �c����
	u8 zanzou_move;	// �����삵�Ă���c���̐�
	u8 type;		// ���W�ɔ��f�����邩�g�k�ɔ��f�����邩
	u8 dummy;
} WAZATOOL_ZANZOU;




//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void *WazaTool_AllocClearMemory(int heap_area, u32 size);
extern s16 GetWazaEffPos(WE_SYS_PTR we_sys, int client_no, int get_pos);
extern u32 GetPokeSoftPri(u8 client_no);
extern OLDACT_WORK* OldAct_Init(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, 
	CLACT_WORK_PTR act, TCB_FUNC func);
extern void OldAct_ParamUpdate(OLDACT_WORK *oldact);
extern void OldAct_Delete(OLDACT_WORK *oldact);
extern void OldAct_SetWorkSeq(OLDACT_WORK *oldact, TCB_FUNC func);
extern void OldAct_SetMoveSeq(OLDACT_WORK *oldact);

extern void WazaEffPosGet_Type(int fight_type, int type, s16* x, s16* y);
extern void WazaEffPosGet_ClientType(WE_SYS_PTR wsp, int client_no, s16*x, s16* y);
//-------------------------------------
//	
//	CATS_ACT_PTR�̃p���b�gNO�擾�֐�
//	
//=====================================
extern u8 WazaTool_CapPlttNoGet( CATS_ACT_PTR cap );

//-------------------------------------
//	
//	H�u�����N�֐��ݒ���p�b�N�����֐�
//
//	��X�g������Ƃ������邩���m��Ȃ����ߍ쐬
//	
//=====================================
enum{	// �߂�l
	WAZATOOL_HBLANK_FALSE,
	WAZATOOL_HBLANK_TRUE,
};
extern int WazaTool_HBlankSet( INTR_FUNC func, void * work );




//-------------------------------------
//	���G�t�F�N�g�����`�F���W
//	�@���Əc�̃x�N�g��������Ԃ��܂��B
//	�@�߂�l���|���邱�ƂŁA���̕����̃x�N�g���ɂȂ�܂��B
//	�@
//	�@��]������ς��鎞��WazaTool_VecChangeX��
//	�@�g���Ă��������B
//=====================================
extern int WazaTool_VecChangeX( WE_SYS_PTR we_sys, int client_no );
extern int WazaTool_VecChangeY( WE_SYS_PTR we_sys, int client_no );

//-------------------------------------
//	�ėp�v�Z�֐�
//=====================================
//�����⋗������K�v�ȃV���N�������擾����
//�����v�Z
extern fx32 WazaTool_GetDiff( fx32 a, fx32 an, u32 n );
extern u32 WazaTool_GetDiffSync( fx32 a, fx32 an, fx32 diff );


// �I�u�W�F�N�g�ɒl��ݒ肷��֐�
extern void WazaTool_SetCapMatrix( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap, s16 c_x, s16 c_y );
extern void WazaTool_SetCapScale( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap );
extern void WazaTool_SetSspMatrix( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp, s16 c_x, s16 c_y );
extern void WazaTool_SetSspScale( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp );

//WAZATOOL_CALCMOVE�\���̗p�֐��S
//
//��]����
extern void WazaTool_InitRotaFx( WAZATOOL_CALCMOVE* p_wtc, u16 r_sx, u16 r_ex, u16 r_sy, u16 r_ey, fx32 wx, fx32 wy, int sync );
extern void WazaTool_InitRotaSpeedFx( WAZATOOL_CALCMOVE* p_wtc, u16 r_sx, u16 r_ex, u16 r_sy, u16 r_ey, fx32 wx, fx32 wy, u16 speed_x );
extern BOOL WazaTool_CalcRotaFx( WAZATOOL_CALCMOVE* p_wtc );
extern BOOL WazaTool_CalcAndReflectRotaFxCap( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectRotaFxSsp( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, SOFT_SPRITE* ssp );

//���s�ړ�
//�萔�v�Z
extern void WazaTool_InitStraightSpeed( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 speed_x  );
extern void WazaTool_InitStraightSync( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync  );
extern BOOL WazaTool_CalcStraight( WAZATOOL_CALCMOVE* p_wtc );
//�Œ菭���v�Z
extern void WazaTool_InitStraightSpeedFx( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 speed_x  );
extern void WazaTool_InitStraightSyncFx( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync );
extern BOOL WazaTool_CalcStraightFx( WAZATOOL_CALCMOVE* p_wtc );
extern BOOL WazaTool_CalcAndReflectStraightFxCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectStraightFxSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp );

//�J�[�u����
extern void WazaTool_InitCurveYFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync, fx32 width );
extern void WazaTool_InitCurveXFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync, fx32 width );
extern BOOL WazaTool_CalcCurveFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt );
extern BOOL WazaTool_CalcAndReflectCurveFxCap( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectCurveFxSsp( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, SOFT_SPRITE* ssp );

//WAZATOOL_CALCMOVE_ONE�\���̗p�֐��S
//����
extern void WazaTool_InitMoveOneSync( WAZATOOL_CALCMOVE_ONE* p_wtc, s32 a, s32 an, u32 sync );
extern void WazaTool_InitMoveOneSpeed( WAZATOOL_CALCMOVE_ONE* p_wtc, s32 a, s32 an, s16 speed );
extern BOOL WazaTool_CalcMoveOne( WAZATOOL_CALCMOVE_ONE* p_wtc );
//�Œ菭��
extern void WazaTool_InitMoveOneSyncFx( WAZATOOL_CALCMOVE_ONE* p_wtc, s16 a, s16 an, u32 sync );
extern void WazaTool_InitMoveOneSpeedFx( WAZATOOL_CALCMOVE_ONE* p_wtc, s16 a, s16 an, fx32 speed );
extern BOOL WazaTool_CalcMoveOneFx( WAZATOOL_CALCMOVE_ONE* p_wtc );
//sin�gcos�g
extern void WazaTool_InitSinCosOneSyncFx( WAZATOOL_CALCMOVE_ONE* p_wtc, u16 s_r, u16 e_r, fx32 w, u32 sync );
extern BOOL WazaTool_CalcSinOne( WAZATOOL_CALCMOVE_ONE* p_wtc );
extern BOOL WazaTool_CalcCosOne( WAZATOOL_CALCMOVE_ONE* p_wtc );

// �g�k
extern void WazaTool_InitScaleRate(WAZATOOL_CALCMOVE* p_wtc, s16 ss, s16 ds, s16 es, u32 sync);
extern BOOL WazaTool_CalcScaleRate(WAZATOOL_CALCMOVE* p_wtc);
extern void WazaTool_InitScaleRateEx(WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, s16 ds, u32 sync);
extern BOOL WazaTool_CalcScaleRateEx(WAZATOOL_CALCMOVE* p_wtc);
extern void WazaTool_CalcScaleRateToClactScale(WAZATOOL_CALCMOVE* p_wtc, f32* x, f32* y);
extern s16	WazaTool_CalcScaleRateToYPos(s16 def_y, int poke_h, u32 sy);
extern s16	WazaTool_CalcScaleRateToYPosFX(s16 def_y, int poke_h, fx32 sy);
extern void WazaTool_PokeOffsetSet(SOFT_SPRITE* ssp, s16 def_y, s16 poke_height, fx32 scale, int mode);
extern void WazaTool_PokeOffsetSetOAM(CATS_ACT_PTR cap, s16 def_y, s16 poke_height, fx32 scale, int mode);
extern BOOL WazaTool_CalcAndReflectScaleRateCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectScaleRateSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp );
extern BOOL WazaTool_CalcAndReflectScaleRateExCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectScaleRateExSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp );

// �h�炵(�Ȉ�)
extern void WazaTool_InitShake(WAZATOOL_CALCMOVE* p_wtc, s16 x, s16 y, u32 sync, u32 num);
extern BOOL WazaTool_CalcShake(WAZATOOL_CALCMOVE* p_wtc);
extern BOOL WazaTool_CalcAndReflectShakeCap( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectShakeSsp( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, SOFT_SPRITE* ssp );

// �c������
extern void WazaTool_InitZanzou( WAZATOOL_ZANZOU* p_wtz, WAZATOOL_CALCMOVE* p_wtc, WAZATOOL_CALCFUNC p_func, s16 x, s16 y, u16 wait, u8 zanzou_num, u8 type, CATS_ACT_PTR cap_00, CATS_ACT_PTR cap_01, CATS_ACT_PTR cap_02, CATS_ACT_PTR cap_03 );
extern void WazaTool_ChangeMoveZanzou( WAZATOOL_ZANZOU* p_wtz, WAZATOOL_CALCMOVE* p_wtc, WAZATOOL_CALCFUNC p_func );
extern BOOL WazaTool_CalcZanzou( WAZATOOL_ZANZOU* p_wtz );

//-------------------------------------
//	
//	�ėp�I�Ɏg���铮�샏�[�N��
//	�쐬����֐��S
//
//	��]�ړ��Ȃǂ͋��ʂ̓�������邱�Ƃ��������ߍ쐬
//	
//=====================================
extern void WazaTool_MakeDefRota( WAZATOOL_CALCMOVE* p_wtc, int rota_num, int rota_one_sync );
#define WAZATOOL_DEF_ROTA_W_X	(32 * FX32_ONE)	// ��]����
#define WAZATOOL_DEF_ROTA_W_Y	(-8 * FX32_ONE)	// ��]�c��
// FX��int�ɕύX�����Ƃ��̒l
#define WAZATOOL_DEF_ROTA_W_X_INT	(32)	// ��]����
#define WAZATOOL_DEF_ROTA_W_Y_INT	(-8)	// ��]�c��

//-------------------------------------
//	
//	alpha�t�F�[�h�^�X�N
//	
//=====================================
typedef struct _WAZATOOL_ALPHA_FADE{
	WAZATOOL_CALCMOVE wtc;
	int	end_flag;
} WAZATOOL_ALPHA_FADE;
extern void WazaTool_StartAlphaFade( WAZATOOL_ALPHA_FADE* p_alfd, s16 sev1, s16 eev1, s16 sev2, s16 eev2, int sync );
extern BOOL WazaTool_EndCheckAlphaFade( const WAZATOOL_ALPHA_FADE* p_alfd );

//-------------------------------------
//	
//	�f�t�H���g���X�^�[�V�X�e��
//
//	�R�O���̂P�t���[��Var
//
//	���̃V�X�e������邱��
//		����������		���܂Ƃ߂čs��
//		�j������		���܂Ƃ߂čs��
//		VBlank���ԏ���	���܂Ƃ߂čs��
//
//	�g���l����邱��
//		�o�b�t�@�ւ̒l�̐ݒ�
//	
//=====================================
#define WAZATOOL_DEFLASTER_BUFF_SIZE	(192)
typedef struct _WAZATOOL_DEFLASTER*			WAZATOOL_DEFLASTER_PTR;
typedef const struct _WAZATOOL_DEFLASTER*	CONST_WAZATOOL_DEFLASTER_PTR;

extern WAZATOOL_DEFLASTER_PTR WazaTool_InitDefLaster( u32 addr, u32 init_num, int heap );
extern void WazaTool_DeleteDefLaster( WAZATOOL_DEFLASTER_PTR p_lst );
extern void* WazaTool_GetDefLasterWriteBuff( CONST_WAZATOOL_DEFLASTER_PTR cp_lst );
extern const void* WazaTool_GetDefLasterReadBuff( CONST_WAZATOOL_DEFLASTER_PTR cp_lst );
extern void WazaTool_StopDefLaster( WAZATOOL_DEFLASTER_PTR p_lst );
extern void WazaTool_StartDefLaster( WAZATOOL_DEFLASTER_PTR p_lst );
extern void WazaTool_SetDefLasterTransAddr( WAZATOOL_DEFLASTER_PTR p_lst, u32 addr );
extern u32	WazaTool_GetDefLasterTransAddr( WAZATOOL_DEFLASTER_PTR p_lst );

//-------------------------------------
//	
//	1/30�t���[���Ή�
//	
// ���X�^�[�X�N���[�����b�v�֐�
// SIN�J�[�u�X�N���[�������܂�
//	
//=====================================
typedef struct _WAZATOOL_SCRLASTER*			WAZATOOL_SCRLASTER_PTR;
typedef const struct _WAZATOOL_SCRLASTER*	CONST_WAZATOOL_SCRLASTER_PTR;

extern WAZATOOL_SCRLASTER_PTR WazaTool_InitScrLaster( u8 start, u8 end, u16 add_r, fx32 r_w, s16 scr_sp, u32 bg_no, u32 tsk_pri, u32 init_num, int heap );
extern void WazaTool_DeleteScrLaster( WAZATOOL_SCRLASTER_PTR p_lst );
extern void* WazaTool_GetScrLasterWriteBuff( CONST_WAZATOOL_SCRLASTER_PTR cp_lst );
extern const void* WazaTool_GetScrLasterReadBuff( CONST_WAZATOOL_SCRLASTER_PTR cp_lst );
extern void WazaTool_StopScrLaster( WAZATOOL_SCRLASTER_PTR p_lst );
extern void WazaTool_StartScrLaster( WAZATOOL_SCRLASTER_PTR p_lst );


// ��������̓��X�^�[���g�p����Ƃ��ɔėp�I�Ɏg�p�ł������
extern u32 WazaTool_GetLasterBuffMatrixData( u16 x, u16 y );
extern u32 WazaTool_GetLasterBGDestAddr( int bg_no );

extern void WazaTool_SetEffectBGPriority( WE_SYS_PTR we_sys, int pri );


// -----------------------------------------
//
//	�� �c�[���Ƃ�
//
// -----------------------------------------
extern void WazaTool_MiddlePointGet(s16 px1, s16 py1, s16 px2, s16 py2, s16* mx, s16* my);
extern void WazaTool_MiddlePointGetFx(s16 px1, s16 py1, s16 px2, s16 py2, fx32* mx, fx32* my);
extern void WazaTool_RangeGetFx(s16 x1, s16 y1, s16 x2, s16 y2, fx32* range);
extern void WazaTool_PointToPointAngleGet(s16 x1, s16 y1, s16 x2, s16 y2, u16* angle);
extern BOOL WazaTool_ParamCalc(int* p, int ep, s32 cp);


// -----------------------------------------
//
//	�� �����̃J���[�t�F�[�h����
//
// -----------------------------------------

// -----------------------------------------
//
//	�\�t�g�t�F�[�h����\���̃|�C���^
//
// -----------------------------------------
typedef struct _TPAL_SOFT_FADE_SYS * PAL_SFS_PTR;

extern BOOL IsPaletteSoftFade(PAL_SFS_PTR psp);
extern void PaletteSoftFadeDelete(PAL_SFS_PTR psp);
extern PAL_SFS_PTR PaletteSoftFade(PALETTE_FADE_PTR pfd, int heap_area, FADEREQ req,
								   u16 start_pos, u16 col_num, s8 wait, s8 param, 
								   u8 start_evy, u8 end_evy, u16 next_rgb, int tcb_pri);

#define RGBtoY(r,g,b)	(((r)*76 + (g)*151 + (b)*29) >> 8)
extern void WeTool_PalGrayScale(WE_SYS_PTR wsp);
extern void WeTool_PalNormal(WE_SYS_PTR wsp);

#endif	//__WAZATOOL_H__


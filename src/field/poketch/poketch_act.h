#ifndef __POKETCH_ACT_H__
#define __POKETCH_ACT_H__

typedef enum {
	PACT_AFFINE_NONE,		// �g�k�i�V
	PACT_AFFINE_NORMAL,		// �g�k����i���ʁj
	PACT_AFFINE_DOUBLE,		// �g�k����i�{�p�j
}PactAffType;

typedef enum {
	BGPRI0,
	BGPRI1,
	BGPRI2,
	BGPRI3,
}PACT_BGPRI;

//------------------------------------------------------------------
/**
 * �A�N�^�[�ǉ��p�̃p�����[�^�\����
 */
//------------------------------------------------------------------
typedef struct {
	NNSG2dFVec2  pos;			// �����ʒu
	u16          anmseq;		// �����A�j���V�[�P���X
	u8           flip;			// �t���b�v�w��(PACT_FLIP)
	u8   bgpri;					// BG�v���C�I���e�B
	u8   oampri;				// OAM�v���C�I���e�B
	u8   affine_flag;			// ��]�E�g�k�t���O
}PACT_ADD_PARAM;


#define FX32INT(x)		((x)<<FX32_SHIFT)

typedef enum {
	PACT_FLIP_OFF = 0,
	PACT_FLIP_H = 1,
	PACT_FLIP_V = 2,
	PACT_FLIP_HV = 4,
}PACT_FLIP;


/*	�Q�l�܂ł�

typedef struct NNSG2dFVec2
{
    fx32     x;		// fx32�� 1:19:12 �̌Œ菬�� 32bit�^
    fx32     y;		// SDK <nitro/fx/fx.h> �ɕ֗��ȃ}�N�����F�X�ł�

}NNSG2dFVec2;

*/

//------------------------------------------------------------------
/**
 * �Z�����A�j���f�[�^�ǂݍ��݂̂��߂̍\����
 */
//------------------------------------------------------------------
typedef struct {
	void*  cellfile;
	void*  anmfile;
	NNSG2dCellDataBank*  cellbank;
	NNSG2dAnimBankData*  anmbank;
	u32  heap;
}PACT_CLANM_PACK;


//------------------------------------------------------------------
/**
 * �V�X�e�����A�N�^�[�P�̂̍\���̐錾
 */
//------------------------------------------------------------------
typedef struct _PACTSYS  PACTSYS;
typedef struct _PACT     PACT;


//------------------------------------------------------------------
/**
 * �֐��v���g�^�C�v
 */
//------------------------------------------------------------------
extern PACTSYS* PACT_SysCreate( NNSG2dOamManagerInstance* oamm, u32 heap);
extern void PACT_SysDelete( PACTSYS* actsys );
extern void PACT_SysMain( PACTSYS* actsys );

extern PACT*  PACT_Add( PACTSYS* actsys, const PACT_ADD_PARAM* param,  const PACT_CLANM_PACK* pack );
extern void PACT_Del( PACTSYS* actsys, PACT* act );

extern void PACT_ChangeAnmSeq( PACT* act, u32 anmseq );
extern BOOL PACT_CheckAnmEnd( PACT* act );

extern void PACT_MovePos( PACT* act, fx32 x, fx32 y );
extern void PACT_SetPos( PACT* act, fx32 x, fx32 y );
extern void PACT_GetPos( const PACT* act, fx32* x, fx32* y );
extern void PACT_SetVanish( PACT* act, BOOL vanish );
extern void PACT_SetCharOffset( PACT* act, u32 offset );
extern void PACT_SetPalOffset( PACT* act, u32 offset );
extern void PACT_SetFlip( PACT* act, PACT_FLIP flip );
extern void PACT_SetMosaic( PACT* act, BOOL flag );
extern void PACT_SetRotate( PACT* act, u16 rotate );

extern void PACT_SetBGPri( PACTSYS* actsys, PACT* act, u32 bgpri );
extern void PACT_SetOamPri( PACTSYS* actsys, PACT* act, u32 oampri );





extern BOOL  PACT_TOOL_LoadCellDatas( PACT_CLANM_PACK* pack, u32 arcFileIdx, u32 cellDataIdx, u32 anmDataIdx, HEAPID heap );
extern void PACT_TOOL_UnloadCellDatas( PACT_CLANM_PACK* pack );





#ifdef PM_DEBUG
extern void PACT_DebugFlagOn( PACTSYS* actsys );
extern void PACT_DebugFlagOff( PACTSYS* actsys );
extern void PACT_PrintDebug( PACTSYS* actsys );
#endif

#endif

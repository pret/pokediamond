#ifndef __POKETCH_ACT_H__
#define __POKETCH_ACT_H__

typedef enum {
	PACT_AFFINE_NONE,		// 拡縮ナシ
	PACT_AFFINE_NORMAL,		// 拡縮あり（普通）
	PACT_AFFINE_DOUBLE,		// 拡縮あり（倍角）
}PactAffType;

typedef enum {
	BGPRI0,
	BGPRI1,
	BGPRI2,
	BGPRI3,
}PACT_BGPRI;

//------------------------------------------------------------------
/**
 * アクター追加用のパラメータ構造体
 */
//------------------------------------------------------------------
typedef struct {
	NNSG2dFVec2  pos;			// 初期位置
	u16          anmseq;		// 初期アニメシーケンス
	u8           flip;			// フリップ指定(PACT_FLIP)
	u8   bgpri;					// BGプライオリティ
	u8   oampri;				// OAMプライオリティ
	u8   affine_flag;			// 回転・拡縮フラグ
}PACT_ADD_PARAM;


#define FX32INT(x)		((x)<<FX32_SHIFT)

typedef enum {
	PACT_FLIP_OFF = 0,
	PACT_FLIP_H = 1,
	PACT_FLIP_V = 2,
	PACT_FLIP_HV = 4,
}PACT_FLIP;


/*	参考までに

typedef struct NNSG2dFVec2
{
    fx32     x;		// fx32は 1:19:12 の固定小数 32bit型
    fx32     y;		// SDK <nitro/fx/fx.h> に便利なマクロが色々です

}NNSG2dFVec2;

*/

//------------------------------------------------------------------
/**
 * セル＆アニメデータ読み込みのための構造体
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
 * システム＆アクター単体の構造体宣言
 */
//------------------------------------------------------------------
typedef struct _PACTSYS  PACTSYS;
typedef struct _PACT     PACT;


//------------------------------------------------------------------
/**
 * 関数プロトタイプ
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

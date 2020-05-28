//==============================================================================
/**
 * @file	particle.h
 * @brief	パーティクル制御ヘッダ
 * @author	matsuda
 * @date	2005.07.11(月)
 */
//==============================================================================
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "spl.h"

#define MATSUDA_TEST

//==============================================================================
//	定数定義
//==============================================================================
//--------------------------------------------------------------
//	Particle_ResourceSet関数のvram_free_mode
//--------------------------------------------------------------
///テクスチャ自動解放なし
#define PTC_AUTOTEX_NULL	(0)
///フレームテクスチャVRAMマネージャを使って解放
#define PTC_AUTOTEX_FRM		(1 << 0)
///リンクドリストテクスチャVRAMマネージャを使って解放
#define PTC_AUTOTEX_LNK		(1 << 1)

///パレット自動解放なし
#define PTC_AUTOPLTT_NULL	(0)
///フレームパレットVRAMマネージャを使って解放
#define PTC_AUTOPLTT_FRM	(1 << 2)
///リンクドリストパレットVRAMマネージャを使って解放
#define PTC_AUTOPLTT_LNK	(1 << 3)

//--------------------------------------------------------------
//	システムでSPLライブラリとやり取りする際に使用するグローバルワークの番号
//--------------------------------------------------------------
enum{
	PARTICLE_GLOBAL_0 = 0,
	PARTICLE_GLOBAL_1,
	PARTICLE_GLOBAL_2,
	//ボールカスタマイズが最大8個のspaを読み込むので増やした
	PARTICLE_GLOBAL_3,
	PARTICLE_GLOBAL_4,
	PARTICLE_GLOBAL_5,
	PARTICLE_GLOBAL_6,
	PARTICLE_GLOBAL_7,

	//ボールカスタマイズが2個同時に出るので2倍必要･･･。
	PARTICLE_GLOBAL_8,
	PARTICLE_GLOBAL_9,
	PARTICLE_GLOBAL_10,
	PARTICLE_GLOBAL_11,
	PARTICLE_GLOBAL_12,
	PARTICLE_GLOBAL_13,
	PARTICLE_GLOBAL_14,
	PARTICLE_GLOBAL_15,
	
	PARTICLE_GLOBAL_MAX,
};

//--------------------------------------------------------------
//	使用ヒープ領域
//--------------------------------------------------------------
///パーティクルシステムで使用するヒープ領域
#define PTC_SYS_HEAP		(HEAPID_BATTLE)	//(SYSTEM_W_HEAP_AREA)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///パーティクルシステム内でSPLライブラリが使用するヒープワークの標準サイズ
//#define PARTICLE_LIB_HEAP_SIZE		(0x4200)	///< EMIT_MAXを3から20に増やしたので、0x3800から変更
#define PARTICLE_LIB_HEAP_SIZE		(0x4800)	///< カスタムボール以外　元々0x4200
#define PARTICLE_LIB_HEAP_SIZE_CB	(0x4200)	///< カスタムボール 0x4200までいける0x41D8が限界


///< パーティクルで必須としてるメモリのサイズ
///< (0x419c)

//==============================================================================
//	型定義
//==============================================================================
///パーティクルシステムワークへのポインタ
typedef struct _PARTICLE_SYSTEM * PTC_PTR;


#ifdef PM_DEBUG

extern PTC_PTR gDebugPTC;

static inline PTC_PTR DEBUG_PTC_PTR_Get(void)
{
	return gDebugPTC;
}

#endif


///エミッタのポインタ型
typedef SPLEmitter * EMIT_PTR;

///テクスチャロード時にVRAMアドレスを返すためのコールバック関数の型
typedef u32 (*pTexCallback)(u32, BOOL);

///エミッタ生成時に呼ばれるコールバック関数の型
typedef void (*pEmitFunc)(EMIT_PTR);

//==============================================================================
//	外部関数宣言
//==============================================================================
extern PTC_PTR Particle_SystemCreate(pTexCallback tex_func, pTexCallback pltt_func, 
	void *work, int work_size, int personal_camera, int heap_id);
extern void Particle_SystemExit(PTC_PTR psys);
extern void * Particle_ResourceLoad(int heap_id, const char *path);
extern void * Particle_ArcResourceLoad(int file_kind, int index, int heap_id);
extern void Particle_ResourceSet(PTC_PTR psys, void *resource, int vram_free, int tex_at_once);
extern EMIT_PTR Particle_CreateEmitter(PTC_PTR psys, int res_no, const VecFx32 *init_pos);
extern void Particle_Draw(PTC_PTR psys);
extern void Particle_Calc(PTC_PTR psys);
extern s32 Particle_GetEmitterNum(PTC_PTR psys);
extern void Particle_EmitterDeleteAll(PTC_PTR psys);
extern void Particle_EmitterDelete(PTC_PTR psys, EMIT_PTR emit);
extern EMIT_PTR Particle_TempEmitterPtrGet(PTC_PTR psys);
extern EMIT_PTR Particle_CreateEmitterCallback(PTC_PTR psys, int res_no, 
	pEmitFunc callback, void *temp_ptr);
extern void * Particle_HeapPtrGet(PTC_PTR psys);
extern void Particle_SystemWorkInit(void);
extern int Particle_DrawAll(void);
extern int Particle_CalcAll(void);
extern void Particle_SystemExitAll(void);
extern void Particle_GetEye(PTC_PTR psys, VecFx32 *eye);
extern void Particle_SetEye(PTC_PTR psys, const VecFx32 *eye);
extern void Particle_GetVup(PTC_PTR psys, VecFx32 *up);
extern void Particle_SetVup(PTC_PTR psys, const VecFx32 *up);
extern void * Particle_GetTempPtr(void);
extern void Particle_GetDefaultEye(VecFx32 *eye);
extern void Particle_GetDefaultUp(VecFx32 *v_up);
extern void Particle_GetDefaultAt(VecFx32 *at);
extern int Particle_GetActionNum(void);
extern GF_CAMERA_PTR Particle_GetCameraPtr(PTC_PTR ptc);
extern void Particle_CameraTypeSet(PTC_PTR ptc, int camera_type);
extern u8 Particle_CameraTypeGet(PTC_PTR ptc);
extern void Particle_LnkTexKeySet(NNSGfdTexKey tex_key);
extern void Particle_PlttLnkTexKeySet(NNSGfdPlttKey pltt_key);

extern void SplSub_GetEmitterVelocity(EMIT_PTR emit, VecFx32 *vel);
extern void SplSub_SetEmitterVelocity(EMIT_PTR emit, const VecFx32 *vel);
extern void SplSub_GetEmitterAxis(EMIT_PTR emit, VecFx16 *vec);
extern fx32 SplSub_GetEmitterRadius(EMIT_PTR emit);
extern fx16 SplSub_GetEmitterInitVelocityPos(EMIT_PTR emit);
extern fx16 SplSub_GetEmitterInitVelocityAxis(EMIT_PTR emit);
extern fx16 SplSub_GetEmitterBaseScale(EMIT_PTR emit);
extern u16 SplSub_GetEmitterEmissionInterval(EMIT_PTR emit);
extern u16 SplSub_GetEmitterBaseAlpha(EMIT_PTR emit);
extern GXRgb SplSub_GetEmitterGlobalColor(EMIT_PTR emit);
extern void SplSub_SetEmitterGenerationRatio(EMIT_PTR emit, fx32 gen_num);
extern fx32 SplSub_GetEmitterGenerationRatio(EMIT_PTR emit);
extern void SplSub_GetEmitterPosition(EMIT_PTR emit, VecFx32 * p_pos);
extern void SplSub_GetEmitterBasePosition(EMIT_PTR emit, VecFx32 * p_pos);

extern void BattleParticle_TestInit(void);

// -----------------------------------------
//
//	Field param 操作関数
//
// -----------------------------------------
void SplSub_SetSPLField_GravityPos(EMIT_PTR emit, VecFx16 *mag);
void SplSub_GetSPLField_GravityPos(EMIT_PTR emit, VecFx16 *mag);
void SplSub_SetSPLField_RandomMag(EMIT_PTR emit, VecFx16* mag);
void SplSub_GetSPLField_RandomMag(EMIT_PTR emit, VecFx16* mag);
void SplSub_SetSPLField_RandomIntvl(EMIT_PTR emit, u16* mag);
void SplSub_GetSPLField_RandomIntvl(EMIT_PTR emit, u16* mag);
void SplSub_SetSPLField_MagnetPos(EMIT_PTR emit, VecFx32* p_pos);
void SplSub_GetSPLField_MagnetPos(EMIT_PTR emit, VecFx32* p_pos);
void SplSub_SetSPLField_MagnetMag(EMIT_PTR emit, fx16* mag);
void SplSub_GetSPLField_MagnetMag(EMIT_PTR emit, fx16* mag);
void SplSub_SetSPLField_SpinRad(EMIT_PTR emit, u16* rad);
void SplSub_GetSPLField_SpinRad(EMIT_PTR emit, u16* rad);
void SplSub_SetSPLField_SpinAxisType(EMIT_PTR emit, u16* axis_type);
void SplSub_GetSPLField_SpinAxisType(EMIT_PTR emit, u16* axis_type);
void SplSub_SetSPLField_SimpleCollisionYPos(EMIT_PTR emit, fx32* y);
void SplSub_GetSPLField_SimpleCollisionYPos(EMIT_PTR emit, fx32* y);
void SplSub_SetSPLField_SimpleCollisionCoeffBounce(EMIT_PTR emit, fx16* coeff_bounce);
void SplSub_GetSPLField_SimpleCollisionCoeffBounce(EMIT_PTR emit, fx16* coeff_bounce);
void SplSub_SetSPLField_SimpleCollisionEventType(EMIT_PTR emit, u16* ev_type);
void SplSub_GetSPLField_SimpleCollisionEventType(EMIT_PTR emit, u16* ev_type);
void SplSub_SetSPLField_SimpleCollisionGlobal(EMIT_PTR emit, u16* global);
void SplSub_GetSPLField_SimpleCollisionGlobal(EMIT_PTR emit, u16* global);
void SplSub_SetSPLField_ConvergencePos(EMIT_PTR emit, VecFx32* p_pos);
void SplSub_GetSPLField_ConvergencePos(EMIT_PTR emit, VecFx32* p_pos);
void SplSub_SetSPLField_ConvergenceRatio(EMIT_PTR emit, fx16* ratio);
void SplSub_GetSPLField_ConvergenceRatio(EMIT_PTR emit, fx16* ratio);

#endif	//__PARTICLE_H__


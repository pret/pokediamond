//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		encount_effect_sub.h
 *	@brief		エンカウントエフェクト
 *	@author		tomoya takahashi
 *	@data		2006.05.07
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ENCOUNT_EFFECT_SUB_H__
#define __ENCOUNT_EFFECT_SUB_H__

#undef GLOBAL
#ifdef	__ENCOUNT_EFFECT_SUB_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------

GLOBAL void EncountEffect_Field_GrassLevelLow(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_Field_GrassLevelHigh(TCB_PTR tcb, void* work);

GLOBAL void EncountEffect_Field_WaterLevelLow(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_Field_WaterLevelHigh(TCB_PTR tcb, void* work);

GLOBAL void EncountEffect_Field_DanLevelLow(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_Field_DanLevelHigh(TCB_PTR tcb, void* work);

GLOBAL void EncountEffect_Trainer_GrassLevelLow(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_Trainer_GrassLevelHigh(TCB_PTR tcb, void* work);

GLOBAL void EncountEffect_Trainer_WaterLevelLow(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_Trainer_WaterLevelHigh(TCB_PTR tcb, void* work);

GLOBAL void EncountEffect_Trainer_DanLevelLow(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_Trainer_DanLevelHigh(TCB_PTR tcb, void* work);

GLOBAL void EncountEffect_Special_Tower(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_Special_Double(TCB_PTR tcb, void* work);

GLOBAL void EncountEffect_Ginga_Normal(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_Ginga_Special(TCB_PTR tcb, void* work);

GLOBAL void EncountEffect_Legend_Normal(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_Legend_Package(TCB_PTR tcb, void* work);

GLOBAL void EncountEffect_SPTR_IwaGym(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_KusaGym(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_MizuGym(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_KakutouGym(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_GoosutoGym(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_KooriGym(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_HaganeGym(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_DenkiGym(TCB_PTR tcb, void* work);

GLOBAL void EncountEffect_SPTR_Siten00(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_Siten01(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_Siten02(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_Siten03(TCB_PTR tcb, void* work);
GLOBAL void EncountEffect_SPTR_Chanpion(TCB_PTR tcb, void* work);

#undef	GLOBAL
#endif		// __ENCOUNT_EFFECT_SUB_H__


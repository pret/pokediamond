/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_field.h

  フィールド（運動系への影響を及ぼすもの）処理

  処理自体はSPLFieldの配列か何かが行うフィールドの種類毎に
  処理を決めていたのでは効率が悪いかなということで、
  関数ポインタとキャストで処理を行う形に、、、

  $Id: spl_field.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_field.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPLライブラリが更新されたので更新

  Revision 1.7  2005/03/17 08:27:13  okane_shinji
  (none)

  Revision 1.6.2.1  2005/03/04 05:55:36  okane_shinji
  (none)

  Revision 1.6  2004/11/26 06:07:31  okane_shinji
  機能追加

  Revision 1.5  2004/07/02 06:24:03  okane_shinji
  (none)

  Revision 1.4  2004/07/02 06:21:37  okane_shinji
  反発係数追加

  Revision 1.3  2004/07/02 01:11:24  okane_shinji
  関数・変数名前変更

  Revision 1.2  2004/07/02 00:07:45  okane_shinji
  シンプルコリジョンフィールドと位置加算マグネットフィールドを追加

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_FIELD_H__
#define __SPL_FIELD_H__

#include "spl_particle.h"

struct SPLEmitter ;

/* 構造体 ------------------------------------------------------------------ */

// フィールド処理構造体
typedef struct SPLField
{
    void (*p_exec)(const void*, SPLParticle*, VecFx32*, struct SPLEmitter* p_emtr );
    const void* p_obj;
} SPLField;

// 重力フィールド
typedef struct SPLGravity
{
    VecFx16 mag;
    u16 reserved0;
} SPLGravity;

// ランダムフィールド
typedef struct SPLRandom
{
    VecFx16 mag;
    u16 intvl;
} SPLRandom;

// マグネットフィールド
typedef struct SPLMagnet
{
    VecFx32 pos;
    fx16    mag;
    u16     reserved0;
} SPLMagnet;

// スピンフィールド
typedef struct SPLSpin
{
    u16 radian;
    u16 axis_type;
} SPLSpin;

// シンプルコリジョンフィールド
typedef struct SPLSimpleCollisionField
{
    fx32 y ; // イベントが起こるy平面の値
    fx16 coeff_bounce ;
    
    struct
    {
        u16 eventtype:2 ;
        u16 global:1 ;
        u16 reserved:13 ;
    } etc ;
} SPLSimpleCollisionField ;

// 位置に加算フィールド（マグネットの亜種）
typedef struct SPLConvergence
{
    VecFx32 pos  ; // 吸い寄せられる場所
    fx16    ratio; // 吸い寄せられる強さ
    u16     reserved0;
} SPLConvergence ;



/* ------------------------------------------------------------------------- */


/* 定義など ---------------------------------------------------------------- */

#define SPL_FLD_TYPE_NUM  6 // フィールドの種類 TODO:6へ

#define SPL_FLD_SPIN_AXIS_TYPE_X   0
#define SPL_FLD_SPIN_AXIS_TYPE_Y   1
#define SPL_FLD_SPIN_AXIS_TYPE_Z   2


// シンプルコリジョンフィールドのイベントタイプ
#define SPL_FLD_SCF_EVENTTYPE_CESSER     0
#define SPL_FLD_SCF_EVENTTYPE_REFLECTION 1



/* ------------------------------------------------------------------------- */


/* 各種フィールド処理 ------------------------------------------------------ */

extern void spl_calc_gravity(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
extern void spl_calc_random(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
extern void spl_calc_magnet(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
extern void spl_calc_spin(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
extern void spl_calc_scfield(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
extern void spl_calc_convergence(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );


/* ------------------------------------------------------------------------- */

#endif

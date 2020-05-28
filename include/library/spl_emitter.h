/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_emitter.h

  エミッタ単位の処理関係

  $Id: spl_emitter.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_emitter.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPLライブラリが更新されたので更新

  Revision 1.36  2005/08/31 09:54:04  okane_shinji
  リストに機能追加

  Revision 1.35  2005/06/20 08:42:35  okane_shinji
  SPL_SetEmitterInitVelocityOffset､ﾉｲﾃ

  Revision 1.34  2005/06/15 23:47:42  okane_shinji
  (none)

  Revision 1.33  2005/03/17 08:27:13  okane_shinji
  (none)

  Revision 1.32.2.5  2005/03/16 09:47:52  okane_shinji
  ver.1.20

  Revision 1.32.2.4  2005/03/04 05:55:36  okane_shinji
  (none)

  Revision 1.32.2.3  2005/02/09 00:12:21  okane_shinji
  コールバック関数の仕様変更

  Revision 1.32.2.2  2005/02/07 01:25:49  okane_shinji
  計算サイクル指定が可能なバージョン

  Revision 1.32.2.1  2005/02/07 01:18:22  okane_shinji
  計算サイクル指定が可能なバージョン

  Revision 1.32  2005/01/13 06:07:09  okane_shinji
  (none)

  Revision 1.31  2004/12/28 00:44:28  okane_shinji
  位置設定関数の位置設定をオフセットとの加算に変更

  Revision 1.30  2004/12/21 02:01:33  okane_shinji
  (none)

  Revision 1.29  2004/12/10 07:27:24  okane_shinji
  ユーザフラグ取得関数SPL_Get_UserFlagを追加

  Revision 1.28  2004/11/26 06:07:31  okane_shinji
  機能追加

  Revision 1.27  2004/09/01 10:18:00  okane_shinji
  SPL_SetCalc SPL_SetDraw SPL_SetEmission の設定方法を変更

  Revision 1.26  2004/08/10 05:11:47  okane_shinji
  基本スケール、初速度の型をfx16からfx32に変更

  Revision 1.25  2004/08/09 10:47:12  okane_shinji
  SPL_SetCurrentPolygonID追加

  Revision 1.24  2004/08/04 05:55:42  okane_shinji
  構造体のパディングを整えました。

  Revision 1.23  2004/07/20 09:33:41  okane_shinji
  任意軸方向の円エミット対応

  Revision 1.22  2004/07/16 01:41:17  okane_shinji
  エミッタに関するパラメータをエミッタごとに変更できるように変更

  Revision 1.21  2004/07/15 02:47:37  okane_shinji
  エミッタの方向を変更できるように変更

  Revision 1.20  2004/07/06 05:10:40  okane_shinji
  アクセサ関数のバグ修正

  Revision 1.19  2004/07/02 00:07:45  okane_shinji
  シンプルコリジョンフィールドと位置加算マグネットフィールドを追加

  Revision 1.18  2004/06/28 07:22:04  okane_shinji
  不具合修正。関数名変更

  Revision 1.17  2004/06/28 07:02:54  okane_shinji
  関数名修正

  Revision 1.16  2004/06/28 04:45:07  okane_shinji
  アクセス関数のインライン化

  Revision 1.15  2004/06/23 07:21:21  okane_shinji
  カラーアニメ、ループ再生、ポリゴン、ディレクショナルビルボードの改良

  Revision 1.14  2004/06/15 01:41:06  okane_shinji
  パーティクル・エミッタの状態取得関数を追加

  Revision 1.13  2004/06/14 07:22:35  konoh
  ■SPL_SetEmtrVel引数修正

  Revision 1.12  2004/06/14 07:01:36  okane_shinji
  一つのエミッタを複数の位置で使用できるように修正

  Revision 1.11  2004/06/14 01:25:16  okane_shinji
  (none)

  Revision 1.10  2004/06/14 00:52:58  okane_shinji
  エミッタにコールバックを登録できるようにしました。

  Revision 1.9  2004/06/11 02:09:30  konoh
  (none)

  Revision 1.8  2004/06/11 02:07:09  konoh
  ■エミッタ操作関数群追加

  Revision 1.7  2004/06/11 00:51:19  konoh
  ■エミッタ速度機能追加

  Revision 1.6  2004/06/09 00:45:31  konoh
  ■エミッタレベルの計算停止・描画停止処理追加

  Revision 1.5  2004/06/08 08:24:14  konoh
  (none)

  Revision 1.4  2004/06/07 00:19:36  konoh
  ■空気抵抗の範囲変更

  Revision 1.3  2004/05/24 07:35:44  konoh
  (none)

  Revision 1.2  2004/05/11 04:38:18  konoh
  (none)

  Revision 1.1.2.2  2004/04/19 06:41:30  konoh
  ■生成ストップフラグの追加

  Revision 1.1.2.1  2004/04/15 07:24:00  konoh
  ■エミッタの状態フラグ追加

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_EMITTER_H__
#define __SPL_EMITTER_H__

#include "spl_particle.h"
#include "spl_resource.h"

/* 構造体 ------------------------------------------------------------------ */

// エミッタフラグ
typedef struct SPLEmitterFlag
{
    union
    {
        u32 all;
        struct
        {
            u32 terminate:1;
            u32 stop_generate:1;
            u32 stop_calc:1;
            u32 stop_draw:1;
            u32 started: 1 ;
            u32 reserved0:27;
        };
    };
} SPLEmitterFlag;


// エミッタ構造体
typedef struct SPLEmitter
{
    struct SPLEmitter* p_next; // for SPLNode
    struct SPLEmitter* p_prev; // for SPLNode

    SPLParticleList act_ptcl_list;
    SPLParticleList act_chld_list;

    // リソース
    SPLResource* p_res;

    // リソース非依存パラメータ
    SPLEmitterFlag flag;
    VecFx32 emtr_pos;
    VecFx32 emtr_vel;
    VecFx32 emtr_init_vel ;
    u16 age;
    fx16 gen_num_dec; // 毎フレーム生成数の小数部

    // ゲーム側で変更できるパラメータ。
    // リソースからコピーする
    VecFx16 axis ;
    u16 init_rtt ;  // 初期回転角度

    fx32 gen_num ; // 放出レート

    fx32 radius ;
    fx32 length ;
    fx32 init_vel_mag_pos ;
    fx32 init_vel_mag_axis ;
    fx32 base_scl ;
    u16  ptcl_life ;

    GXRgb clr; // グローバルカラー

    // シンプルコリジョン用のパラメータ。。
    fx32 simple_collision_y ;

    // テクスチャ座標
    fx16 tex_s ;
    fx16 tex_t ;
    fx16 chld_tex_s ;
    fx16 chld_tex_t ;

    struct
    {
        u32 gen_intvl:8;
        u32 base_alp:8;
        u32 calc_cycle:3 ;
        u32 reserved:13;
    } etc;

    // 軸方向に直交な二軸
    VecFx16 cross_to_axis_1 ;
    VecFx16 cross_to_axis_2 ;

    // コールバック関数
    void (*callbackfunc)(struct SPLEmitter*, unsigned int uFlag )  ;
    
    // ユーザが自由に使用できるデータ
    void* emtr_userdata ;
    
    // ユーザが自由に使用できるワーク領域
    union
    {
        u32 uw_u32;
        u16 uw_u16[2] ;
        u8  uw_u8[4] ;
    } userwork ;


} SPLEmitter;

// エミッタリスト
typedef struct SPLEmitterList
{
    SPLEmitter* p_begin; // for SPLList
    int node_num;        // for SPLList
    SPLEmitter* p_end;   // for SPLList
} SPLEmitterList;

/* ------------------------------------------------------------------------- */


/* 定義等 ------------------------------------------------------------------ */

#define SPL_EMTR_FOREVER  0 // 無限生成タイプ
#define SPL_PTCL_GEN      0 // 
#define SPL_CHLD_GEN      0 //

#define SPL_PTCL_ANM_FUNC_NUM 4 // 親パーティクルアニメ最大数
#define SPL_CHLD_ANM_FUNC_NUM 2 // 子パーティクルアニメ最大数

// 空気抵抗はこの係数を使って（１～３÷４）の範囲の値に
#define SPL_AIR_RESIST_OFST   (3 << 7) // 空気抵抗計算
#define SPL_AIR_RESIST_SHIFT        9  // 空気抵抗計算

#define SPL_EMITTER_CALLBACK_FRONT 0
#define SPL_EMITTER_CALLBACK_BACK  1

/* ------------------------------------------------------------------------- */

// メモリ確保コールバック
typedef void* (*SPLCallback)(SPLEmitter*);

/* アクセス用関数 -------------------------------------------------------------------- */

/* ------------------------------------------------------
 * エミッタの停止
 *------------------------------------------------------*/
static inline void SPL_Terminate(  SPLEmitter* p_emtr )
{
    p_emtr->flag.terminate = 1 ;
}

/* ------------------------------------------------------
 * 計算の停止/開始
 *------------------------------------------------------*/
static inline void SPL_StopCalc( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_calc = 1 ;
}
static inline void SPL_RestartCalc( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_calc = 0 ;
}
static inline void SPL_SetCalc( SPLEmitter* p_emtr, BOOL flag )
{
    p_emtr->flag.stop_calc = !flag ;
}

/* ------------------------------------------------------
 * 描画の停止/開始
 *------------------------------------------------------*/
static inline void SPL_StopDraw( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_draw = 1 ;
}
static inline void SPL_RestartDraw( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_draw = 0 ;
}
static inline void SPL_SetDraw( SPLEmitter* p_emtr, BOOL flag )
{
    p_emtr->flag.stop_draw = !flag ;
}

/* ------------------------------------------------------
 * 生成の停止/開始
 *------------------------------------------------------*/
static inline void SPL_StopEmission( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_generate = 1 ;
}
static inline void SPL_RestartEmission( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_generate = 0 ;
}
static inline void SPL_SetEmission( SPLEmitter* p_emtr, BOOL flag )
{
    p_emtr->flag.stop_generate = !flag ;
}

/* ------------------------------------------------------
 * エミッタの位置パラメータをセットする。オフセット値は常に反映される。
 *------------------------------------------------------*/
static inline void SPL_SetEmitterPosition( SPLEmitter* p_emtr, const VecFx32* p_pos )
{
    //p_emtr->emtr_pos = *( p_pos ) ;
    p_emtr->emtr_pos.x = p_pos->x + p_emtr->p_res->p_base->pos.x ;
    p_emtr->emtr_pos.y = p_pos->y + p_emtr->p_res->p_base->pos.y ;
    p_emtr->emtr_pos.z = p_pos->z + p_emtr->p_res->p_base->pos.z ;
}
static inline void SPL_SetEmitterPositionX(  SPLEmitter* p_emtr, fx32 x )
{
    p_emtr->emtr_pos.x = x + p_emtr->p_res->p_base->pos.x ;
}
static inline void SPL_SetEmitterPositionY(  SPLEmitter* p_emtr, fx32 y )
{
    p_emtr->emtr_pos.y = y + p_emtr->p_res->p_base->pos.y ;
}
static inline void SPL_SetEmitterPositionZ(  SPLEmitter* p_emtr, fx32 z )
{
    p_emtr->emtr_pos.z = z + p_emtr->p_res->p_base->pos.z ;
}


/* ------------------------------------------------------
 * エミッタの速度パラメータをセットする
 *------------------------------------------------------*/
static inline void SPL_SetEmitterVelocity( SPLEmitter* p_emtr, const VecFx32* p_vel )
{
    p_emtr->emtr_vel = *( p_vel ) ;
}
static inline void SPL_SetEmitterVelocityX( SPLEmitter* p_emtr, fx32 x )
{
    p_emtr->emtr_vel.x = x ;
}
static inline void SPL_SetEmitterVelocityY( SPLEmitter* p_emtr, fx32 y )
{
    p_emtr->emtr_vel.y = y ;
}
static inline void SPL_SetEmitterVelocityZ( SPLEmitter* p_emtr, fx32 z )
{
    p_emtr->emtr_vel.z = z ;
}

/* ------------------------------------------------------
 * エミッタの初期速度パラメータをセットする
 *------------------------------------------------------*/
static inline void SPL_SetEmitterInitVelocityOffset( SPLEmitter* p_emtr, const VecFx32* p_vel )
{
    p_emtr->emtr_init_vel = *( p_vel ) ;
}
static inline void SPL_SetEmitterInitVelocityOffsetX( SPLEmitter* p_emtr, fx32 x )
{
    p_emtr->emtr_init_vel.x = x ;
}
static inline void SPL_SetEmitterInitVelocityOffsetY( SPLEmitter* p_emtr, fx32 y )
{
    p_emtr->emtr_init_vel.y = y ;
}
static inline void SPL_SetEmitterInitVelocityOffsetZ( SPLEmitter* p_emtr, fx32 z )
{
    p_emtr->emtr_init_vel.z = z ;
}


/* ------------------------------------------------------
 * コールバック関数をセットする
 *------------------------------------------------------*/
static inline void SPL_SetCallbackFunc( SPLEmitter* p_emtr, void (*callbackfunc_)(struct SPLEmitter*, unsigned int uFlag ) )
{
    p_emtr->callbackfunc=callbackfunc_ ;
}

/* ------------------------------------------------------
 * エミッタに属するパーティクルの数を参照する
 *------------------------------------------------------*/
static inline s32 SPL_GetParticleNum( const SPLEmitter* p_emtr )
{
    return p_emtr->act_ptcl_list.node_num ;
}
static inline s32 SPL_GetChildParticleNum( const SPLEmitter* p_emtr )
{
    return p_emtr->act_chld_list.node_num ;
}
static inline s32 SPL_GetAllParticleNum( const SPLEmitter* p_emtr )
{
    return SPL_GetParticleNum(p_emtr)+SPL_GetChildParticleNum(p_emtr) ;
}

/* ------------------------------------------------------
 * ユーザデータのセット  / ゲット
 *------------------------------------------------------*/
static inline void SPL_SetUserData( SPLEmitter* p_emtr, void* p_data  )
{
    p_emtr->emtr_userdata = p_data ;
}
static inline void* SPL_GetUserData( const SPLEmitter* p_emtr )
{
    return p_emtr->emtr_userdata ;
}

/* ------------------------------------------------------
 * エミッタの向きをセット
 *------------------------------------------------------*/
static inline void SPL_SetEmitterAxis( SPLEmitter* p_emtr, const VecFx16* axis )
{
    p_emtr->axis = *axis ;
}

/* ------------------------------------------------------
 * エミッタの大きさをセット
 *------------------------------------------------------*/
static inline void SPL_SetEmitterRadius( SPLEmitter* p_emtr, fx32 radius )
{
    p_emtr->radius = radius ;
}

/* ------------------------------------------------------
 * エミッタの全方向初速をセット
 *------------------------------------------------------*/
static inline void SPL_SetEmitterInitVelocityPos( SPLEmitter* p_emtr, fx16 init_vel_mag_pos )
{
    p_emtr->init_vel_mag_pos = init_vel_mag_pos ;
}

/* ------------------------------------------------------
 * エミッタの軸方向初速をセット
 *------------------------------------------------------*/
static inline void SPL_SetEmitterInitVelocityAxis( SPLEmitter* p_emtr, fx16 init_vel_mag_axis )
{
    p_emtr->init_vel_mag_axis = init_vel_mag_axis ;
}

/* ------------------------------------------------------
 * エミッタの基本スケールをセット
 *------------------------------------------------------*/
static inline void SPL_SetEmitterBaseScale( SPLEmitter* p_emtr, fx16 base_scl )
{
    p_emtr->base_scl = base_scl ;
}

/* ------------------------------------------------------
 * エミッタのパーティクル寿命をセット
 *------------------------------------------------------*/
static inline void SPL_SetEmitterParticleLife( SPLEmitter* p_emtr, u16 ptcl_life )
{
    p_emtr->ptcl_life = ptcl_life ;
}

/* ------------------------------------------------------
 * エミッタの生成間隔をセット
 *------------------------------------------------------*/
static inline void SPL_SetEmitterEmissionInterval( SPLEmitter* p_emtr, u16 gen_intvl )
{
    p_emtr->etc.gen_intvl = (u8)gen_intvl ;
}

/* ------------------------------------------------------
 * エミッタの基本αをセット
 *------------------------------------------------------*/
static inline void SPL_SetEmitterBaseAlpha( SPLEmitter* p_emtr, u16 base_alp )
{
    p_emtr->etc.base_alp = (u8)base_alp ;
}

/* ------------------------------------------------------
 * エミッタのグローバル色をセット
 *------------------------------------------------------*/
static inline void SPL_SetEmitterGlobalColor( SPLEmitter* p_emtr, GXRgb color )
{
    p_emtr->clr = color ;
}

/* ------------------------------------------------------
 * エミッタから放出されるパーティクルの初期回転角度
 *------------------------------------------------------*/
static inline void SPL_SetEmitterInitialRotationAngle( SPLEmitter* p_emtr, u16 init_rtt )
{
    p_emtr->init_rtt = init_rtt ;
}



/* ------------------------------------------------------
 * エミッタの放出レートをセット
 *------------------------------------------------------*/
static inline void SPL_SetEmitterGenerationRatio( SPLEmitter* p_emtr, fx32 gen_num )
{
    p_emtr->gen_num = gen_num ;
}

/* ------------------------------------------------------
 * ユーザが自由に使用できるワーク領域の セット  / ゲット
 *------------------------------------------------------*/
static inline void SPL_SetUserWork( SPLEmitter* p_emtr, u32 user_work )
{
    p_emtr->userwork.uw_u32 = user_work ;
}
static inline u32 SPL_GetUserWork( const SPLEmitter* p_emtr )
{
    return p_emtr->userwork.uw_u32 ;
}

static inline void SPL_SetUserWorkU16( SPLEmitter* p_emtr, u16 index, u16 user_work )
{
    p_emtr->userwork.uw_u16[index] = user_work ;
}
static inline u16 SPL_GetUserWorkU16( SPLEmitter* p_emtr, u16 index )
{
    return p_emtr->userwork.uw_u16[index] ;
}

static inline void SPL_SetUserWorkU8( SPLEmitter* p_emtr, u16 index, u8 user_work )
{
    p_emtr->userwork.uw_u8[index] = user_work ;
}
static inline u8 SPL_GetUserWorkU8( SPLEmitter* p_emtr, u16 index )
{
    return p_emtr->userwork.uw_u8[index] ;
}

/* ------------------------------------------------------
 * 先頭のパーティクルを取得する
 *------------------------------------------------------*/
static inline SPLParticle* SPL_GetHeadParticle( const SPLEmitter* p_emtr )
{
    return p_emtr->act_ptcl_list.p_begin ;
}

static inline SPLParticle* SPL_GetChildHeadParticle( const SPLEmitter* p_emtr )
{
    return p_emtr->act_chld_list.p_begin ;
}

/* ------------------------------------------------------
 * 円柱エミッタの配置を座標指定するユーティリティ
 *------------------------------------------------------*/
void SPL_Util_SetCylinderEmiterDirection( SPLEmitter* p_emtr, const VecFx32* p1, const VecFx32* p2 ) ;


/* ------------------------------------------------------
 * ユーザフラグの取得
 *------------------------------------------------------*/
static inline u8 SPL_GetUserFlag( SPLEmitter* p_emtr )
{
    return (u8)p_emtr->p_res->p_base->usr.flag ;
}

/* ------------------------------------------------------
 * エミッタの計算サイクルを指定する
 *------------------------------------------------------*/
static inline void SPL_SetEmitterCalcCycle( SPLEmitter* p_emtr, u16 cycle )
{
    // cycleは0,1,2のどれかである必要がある。
    p_emtr->etc.calc_cycle = cycle ;
}

/* ------------------------------------------------------
 * エミッタのシンプルコリジョン高さを変更する
 *------------------------------------------------------*/
static inline void SPL_SetEmitterSimpleCollisionHeight( SPLEmitter* p_emtr, fx32 y )
{
    p_emtr->simple_collision_y = y ;
}





/* ------------------------------------------------------------------------- */

#endif

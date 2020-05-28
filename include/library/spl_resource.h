/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_resource.h

  （テクスチャ以外の）リソース関係

  $Id: spl_resource.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_resource.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPLライブラリが更新されたので更新

  Revision 1.31  2005/06/15 23:47:39  okane_shinji
  (none)

  Revision 1.30  2005/03/17 08:27:13  okane_shinji
  (none)

  Revision 1.29.2.1  2005/03/16 09:47:52  okane_shinji
  ver.1.20

  Revision 1.29  2005/01/13 06:07:09  okane_shinji
  (none)

  Revision 1.28  2004/11/26 06:07:31  okane_shinji
  機能追加

  Revision 1.27  2004/08/31 08:52:41  okane_shinji
  微修正

  Revision 1.26  2004/08/31 07:38:38  okane_shinji
  テクスチャパターンアニメのデータ構造修正

  Revision 1.25  2004/08/17 08:30:00  okane_shinji
  リソース中のテクスチャ情報取得関数追加

  Revision 1.24  2004/08/10 08:12:21  okane_shinji
  構造体構成を変更

  Revision 1.23  2004/08/10 06:06:18  okane_shinji
  子の放出数を設定できるように変更。

  Revision 1.22  2004/08/10 05:11:47  okane_shinji
  基本スケール、初速度の型をfx16からfx32に変更

  Revision 1.21  2004/08/04 05:55:42  okane_shinji
  構造体のパディングを整えました。

  Revision 1.20  2004/07/20 10:00:42  okane_shinji
  (none)

  Revision 1.19  2004/07/20 09:33:41  okane_shinji
  任意軸方向の円エミット対応

  Revision 1.18  2004/07/16 01:41:17  okane_shinji
  エミッタに関するパラメータをエミッタごとに変更できるように変更

  Revision 1.17  2004/07/02 01:33:19  okane_shinji
  マクロ修正

  Revision 1.16  2004/07/02 01:11:24  okane_shinji
  関数・変数名前変更

  Revision 1.15  2004/07/02 00:07:45  okane_shinji
  シンプルコリジョンフィールドと位置加算マグネットフィールドを追加

  Revision 1.14  2004/06/28 02:40:55  okane_shinji
  子へのスケール継承、リピート回数の指定、Dビルボードの引き伸ばし率の改良

  Revision 1.13  2004/06/25 07:37:29  okane_shinji
  円ボリューム、球ボリューム追加。ポリゴン表示時のXYZ回転の不具合修正

  Revision 1.12  2004/06/25 06:25:42  okane_shinji
  ポリゴン表示に関する修正。スケールアニメーションの追加

  Revision 1.11  2004/06/24 05:37:48  okane_shinji
  ４バイトアライメントルール違反を修正

  Revision 1.10  2004/06/24 05:00:12  okane_shinji
  SPLResInOut構造体を修正

  Revision 1.9  2004/06/24 04:22:45  okane_shinji
  アニメーションにてpeakを設定できるように変更。1ループ当たりのフレーム数を変えることができるように変更

  Revision 1.8  2004/06/23 07:21:21  okane_shinji
  カラーアニメ、ループ再生、ポリゴン、ディレクショナルビルボードの改良

  Revision 1.7  2004/05/26 06:13:51  konoh
  ■アスペクト比機能追加

  Revision 1.6  2004/05/25 08:06:36  konoh
  ■円系初期位置に軸指定追加

  Revision 1.5  2004/05/25 06:30:29  konoh
  ■ランダムカラー機能追加

  Revision 1.4  2004/05/25 02:04:57  konoh
  ■ランダムテクスチャ機能追加

  Revision 1.3  2004/05/24 07:35:44  konoh
  (none)

  Revision 1.2  2004/05/11 04:38:18  konoh
  (none)

  Revision 1.1.2.1  2004/04/15 07:23:37  konoh
  ■自滅フラグ追加

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_RESOURCE_H__
#define __SPL_RESOURCE_H__

#include "spl_field.h"

/* 定数など ---------------------------------------------------------------- */

// 初期位置関係
#define SPL_INIT_POS_TYPE_ZERO              0
#define SPL_INIT_POS_TYPE_SPHERE            1
#define SPL_INIT_POS_TYPE_CIRCLE            2
#define SPL_INIT_POS_TYPE_CIRCLE_RI         3
#define SPL_INIT_POS_TYPE_SPHERE_VOLUME     4
#define SPL_INIT_POS_TYPE_CIRCLE_VOLUME     5
#define SPL_INIT_POS_TYPE_CYLINDER          6
#define SPL_INIT_POS_TYPE_CYLINDER_RI       7
#define SPL_INIT_POS_TYPE_SEMISPHERE        8
#define SPL_INIT_POS_TYPE_SEMISPHERE_VOLUME 9


// 円系初期位置における軸指定
#define SPL_CIRCLE_AXIS_X   2
#define SPL_CIRCLE_AXIS_Y   1
#define SPL_CIRCLE_AXIS_Z   0
#define SPL_CIRCLE_AXIS_ARBITRARY 3

// 描画タイプ
#define SPL_DRAW_BB    0 // ビルボード
#define SPL_DRAW_DBB   1 // ディレクショナルビルボード
#define SPL_DRAW_POL   2 // ポリゴン
#define SPL_DRAW_DPL   3 // ディレクショナルポリゴン（進行方向をむく版）
#define SPL_DRAW_DPC   4 // ディレクショナルポリゴソ（中央をむく版）


// ポリゴン描画の際の基準平面
#define SPL_POLYGON_BASEPLANE_XY 0
#define SPL_POLYGON_BASEPLANE_XZ 1

// ポリゴン描画の際の回転軸
#define SPL_POLYGON_ROTAXIS_Y    0
#define SPL_POLYGON_ROTAXIS_XYZ  1

// スケールアニメが適用される方向
#define SPL_ANM_SCL_DIRECT_XY 0
#define SPL_ANM_SCL_DIRECT_X  1
#define SPL_ANM_SCL_DIRECT_Y  2

// 最大テクスチャパターン数
#define SPL_MAX_TEX_PTN_NUM  8

// チャイルド回転関係
#define SPL_CHLD_RTT_NONE  0 // 回転しない
#define SPL_CHLD_RTT_STILL 1 // 生んだ瞬間の親の角度を継承

// ８ビットで０～１を表現してるもの関係
#define SPL_FX8_SHIFT    8
#define SPL_FX8_MAX   0xff

// 使用しているフィールド数をフラグから取得
#define SPL_CHLD_RTT_MOVE  2 // 生んだ瞬間の親の角度と角速度を継承
#define SPL_GET_FLD_NUM(x) ((x).use_fld_grvt +\
                                                        (x).use_fld_rndm +\
                                                        (x).use_fld_mgnt +\
                                                        (x).use_fld_spin +\
                                                        (x).use_fld_scfld +\
                                                        (x).use_fld_cngc)
// ポリゴンのオフセット起点
#define SPL_OFFSET_CENTER 0
#define SPL_OFFSET_TOP    1
#define SPL_OFFSET_BUTTOM 2
#define SPL_OFFSET_RIGHT  3
#define SPL_OFFSET_LEFT   4


/* ------------------------------------------------------------------------- */

/* 構造体 ------------------------------------------------------------------ */

// ＳＰＡリソースヘッダ
typedef struct SPLArcHdr
{
    u32 id;
    u32 ver;
    u16 res_num;
    u16 tex_num;
    u32 reserved0;
    u32 res_size;
    u32 tex_size;
    u32 tex_offset;
    u32 reserved1;
} SPLArcHdr;

///////////////////////////////////////////////////////////////////////////////

// ベースフラグ
typedef union
{
    u32 all;
    struct
    {
        u32 init_pos_type:4;
        u32 draw_type:2;
        u32 circle_axis:2;

        u32 use_scl_anm:1;
        u32 use_clr_anm:1;
        u32 use_alp_anm:1;
        u32 use_tex_anm:1;
        u32 use_rtt_anm:1;
        u32 use_init_rtt_rndm:1;
        u32 self_dest:1;
        u32 follow_emtr:1;

        u32 use_chld:1;
        u32 pol_rot_axis:2;          // ポリゴン表示のときの回転軸
        u32 pol_baseplane:1;         // ポリゴン表示のときの基準平面
        u32 ptcl_random_loop_anm:1 ; // ループアニメのとき、開始タイミングをランダマイズする
        u32 draw_child_first:1 ;     // 親より子を先に書くときは1
        u32 draw_parent:1;           // 親を描画するかどうか0のときは描画する
        u32 camera_offset:1;         // オフセット座標をカメラ座標系で計算するかどうか

        u32 use_fld_grvt:1;
        u32 use_fld_rndm:1;
        u32 use_fld_mgnt:1;
        u32 use_fld_spin:1;
        u32 use_fld_scfld:1;
        u32 use_fld_cngc:1;
        
        u32 polygonID_fixed:1;
        u32 child_polygonID_fixed:1;
    };
} SPLResBaseFlag;

// チャイルドフラグ
typedef union
{
    u16 all;
    struct
    {
        u16 affect_fld:1;
        u16 use_scl_anm:1;
        u16 use_alp_anm:1;
        u16 rtt_type:2;
        u16 follow_emtr:1;
        u16 use_chld_clr:1;
        u16 draw_type:2;
        u16 pol_rot_axis:2;  // ポリゴン表示のときの回転軸
        u16 pol_baseplane:1; // ポリゴン表示のときの基準平面
        u16 reserved0:4;
    };
} SPLResChldFlag;

// イン・アウトタイミング
typedef union
{
    u16 all;
    struct
    {
        u16 in:8;
        u16 out:8;
    };
} SPLResInOut;

typedef union
{
    u32 all ;
    struct
    {
        u32 in:8;
        u32 peak:8;
        u32 out:8;
        u32 reserved:8;
    } ;
} SPLResInPeakOut ;

///////////////////////////////////////////////////////////////////////////////

// ＳＰＲベース
// ☆マークはエミッタでコピーされて使われる。それ以外は直に使われる
typedef struct SPLResBase
{
    SPLResBaseFlag flag;

    VecFx32 pos ;

    fx32 gen_num;
    fx32 radius; // ☆
    fx32 length; // ☆現時点では円柱の長さにしか使用されない

    VecFx16 axis;

    GXRgb clr_n;

    fx32 init_vel_mag_pos; // ☆
    fx32 init_vel_mag_axis;// ☆
    fx32 base_scl;         // ☆
    fx16 aspect;
    u16 start_offset ;// エミッタが開始するまでのタイミング

    s16 rtt_min;
    s16 rtt_max;

    u16 init_rtt ;
    u16 reserved0 ;

    u16 emtr_life;
    u16 ptcl_life; // ☆

    struct
    {
        u32 base_scl:8; 
        u32 ptcl_life:8; 
        u32 init_vel_mag:8;
        u32 reserved0:8;
    } rndm;

    struct
    {
        u32 gen_intvl:8; // ☆
        u32 base_alp:8;
        u32 air_resist:8;
        u32 tex_no:8;
        
        u32 loop_frame:8;  // １ループあたりのフレーム数
        u32 dbb_scale:16;  // Dビルボードの時の引き伸ばす割合（fx16扱い）
        u32 tex_repeat_num_s:2;
        u32 tex_repeat_num_t:2;
        u32 scl_anm_direct:3 ;
        u32 dpol_center:1;
        //u32 reserved:1;
        
        u32 reverse_tex_s:1 ; // テクスチャを反転するかどうか。。
        u32 reverse_tex_t:1 ;
        u32 offset_pos:3;     // オフセット場所(中上下左右)
        u32 reserved1:27 ; 
    } etc;

    // ポリゴンのオフセット位置
    fx16 offset_x ;
    fx16 offset_y ;

    struct
    {
        u32 flag:8 ;
        u32 reserved:24;
    } usr ; 

} SPLResBase;

// ＳＰＲスケールアニメ
typedef struct SPLResSclAnm
{
    fx16 scl_s;
    fx16 scl_n;
    fx16 scl_e;
    SPLResInOut in_out;
    struct
    {
        u16 loop:1 ;
        u16 reserved:15;
    } etc ;
    u16 reserved0 ;
} SPLResSclAnm;

// ＳＰＲカラーアニメ
typedef struct SPLResClrAnm
{
    GXRgb clr_s;
    GXRgb clr_e;
    SPLResInPeakOut in_peak_out;
    struct
    {
        u16 use_rndm:1;
        u16 loop:1;
        u16 interpolation:1;
        u16 reserved0:13;
    } etc;
    u16 reserved0;
} SPLResClrAnm;

// ＳＰＲアルファアニメ
typedef struct SPLResAlpAnm
{
    union
    {
        u16 all;
        struct
        {
            u16 s:5;
            u16 n:5;
            u16 e:5;
            u16 reserved0:1;
        };
    } alp;

    struct
    {
        u16 flick:8;
        u16 loop:1;
        u16 reserved0:7;
    } etc;

    SPLResInOut in_out;
    u16 reserved0;
} SPLResAlpAnm;

// ＳＰＲテクスチャパターンアニメ
typedef struct SPLResTexAnm
{
    u8 tex_no[SPL_MAX_TEX_PTN_NUM] ;

    struct
    {
        u32 use_num:8;
        u32 diff:8;
        u32 use_rndm:1;
        u32 loop:1;
        u32 reserved0:14;
    } etc;
} SPLResTexAnm;

// ＳＰＲチャイルド
typedef struct SPLResChld
{
    SPLResChldFlag flag;

    fx16 init_vel_mag_rndm;
    fx16 scl_e;

    u16 life;

    struct
    {
        u16 vel_ratio:8;
        u16 scl_ratio:8;
    } ratio;

    GXRgb clr;

    struct
    {
        u32 gen_num:8;
        u32 gen_start:8;
        u32 gen_intvl:8;
        u32 tex_no:8;
        u32 tex_repeat_num_s:2;
        u32 tex_repeat_num_t:2;
        
        u32 reverse_tex_s:1 ;
        u32 reverse_tex_t:1 ;
        u32 dpol_center:1 ; // Dポリゴンのとき中心を向くかどうか？
        u32 reserved0:25;
        //u32 reserved0:26;
    } etc;

} SPLResChld;

// リソース構造体
typedef struct SPLResource
{
    SPLResBase*   p_base;
    SPLResSclAnm* p_scl_anm;
    SPLResClrAnm* p_clr_anm;
    SPLResAlpAnm* p_alp_anm;
    SPLResTexAnm* p_tex_anm;
    SPLResChld*   p_chld;
    SPLField*     fld_ary;
    u16           fld_num;
    u16           reserved ;
} SPLResource;

/* ------------------------------------------------------------------------- */



/* ------------------------------------------------------
 * リソースにおけるテクスチャオフセット
 *------------------------------------------------------*/
static inline u32 SPL_GetTexOffsetOnResource( const void* p_spa )
{
    const SPLArcHdr* p_arc_hdr = (const SPLArcHdr*) p_spa;

    return p_arc_hdr->tex_offset ;
}

/* ------------------------------------------------------
 * リソースにおけるテクスチャサイズ
 *------------------------------------------------------*/
static inline u32 SPL_GetTexSizeOnResource( const void* p_spa )
{
    const SPLArcHdr* p_arc_hdr = (const SPLArcHdr*) p_spa;

    return p_arc_hdr->tex_size ;
}

/* ------------------------------------------------------
 * リソースにおけるリソースサイズ
 *------------------------------------------------------*/
static inline u32 SPL_GetResSizeOnResource( const void* p_spa )
{
    const SPLArcHdr* p_arc_hdr = (const SPLArcHdr*) p_spa;

    return p_arc_hdr->res_size ;
}




/* ------------------------------------------------------------------------- */










#endif

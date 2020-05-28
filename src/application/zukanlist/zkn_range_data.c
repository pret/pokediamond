//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		range_data.c
 *	@brief		分布データ取得関数
 *	@author		tomoya takahashi 
 *	@data		2006.02.11
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "system/arc_util.h"
#include "system/arc_tool.dat"

#include "gflib/clact.h"

#include "include/poketool/monsno.h"
#include "src/application/zukanlist/zkn_data/zukan_enc_diamond.naix"
#include "include/application/zukanlist/zkn_version.h"

#define __ZKN_RANGE_DATA_H_GLOBAL
#include "include/application/zukanlist/zkn_range_data.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	ポケモン分布データ各タイプ開始ナンバー
//=====================================
#define ZKN_RANGEDATA_DAN_MORNING_ARC_S	(NARC_zukan_enc_diamond_zkn_dan_range_morning_mons_000_mrang)
#define ZKN_RANGEDATA_DAN_NOON_ARC_S	(NARC_zukan_enc_diamond_zkn_dan_range_noon_mons_000_mrang)
#define ZKN_RANGEDATA_DAN_NIGHT_ARC_S	(NARC_zukan_enc_diamond_zkn_dan_range_night_mons_000_mrang)
#define ZKN_RANGEDATA_FLD_MORNING_ARC_S	(NARC_zukan_enc_diamond_zkn_fld_range_morning_mons_000_mrang)
#define ZKN_RANGEDATA_FLD_NOON_ARC_S	(NARC_zukan_enc_diamond_zkn_fld_range_noon_mons_000_mrang)
#define ZKN_RANGEDATA_FLD_NIGHT_ARC_S	(NARC_zukan_enc_diamond_zkn_fld_range_night_mons_000_mrang)
#define ZKN_RANGEDATA_DAN_SPECIAL_ARC_S	(NARC_zukan_enc_diamond_zkn_dan_range_special_mons_000_mrang)
#define ZKN_RANGEDATA_DAN_SPECIAL_COMP_ARC_S	(NARC_zukan_enc_diamond_zkn_dan_range_special_comp_mons_000_mrang)
#define ZKN_RANGEDATA_FLD_SPECIAL_ARC_S	(NARC_zukan_enc_diamond_zkn_fld_range_special_mons_000_mrang)
#define ZKN_RANGEDATA_FLD_SPECIAL_COMP_ARC_S	(NARC_zukan_enc_diamond_zkn_fld_range_special_comp_mons_000_mrang)


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
static int ZknRangeDataZoneLinkIdGet( int zone_id, int arc_dataidx, int heap );



//----------------------------------------------------------------------------
/**
 *	@brief	モンスターナンバー分布データ取得
 *
 *	@param	p_inbuff		データ格納先
 *	@param	mons_no			モンスターナンバー
 *	@param	type			分布タイプ
 *	@param	heap			使用ヒープ
 */
//-----------------------------------------------------------------------------
void ZKN_RANGEDATA_GetMonsNoRange( ZKN_RANGE_DATA_MONS* p_inbuff, int mons_no, int type, int heap )
{
	int arc_start;
	u32 data_size;
	
	switch( type ){
	// ダンジョン分布データ
	case ZKN_RANGEDATA_TYPE_DAN_MORNING:
		arc_start = ZKN_RANGEDATA_DAN_MORNING_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_DAN_NOON:
		arc_start = ZKN_RANGEDATA_DAN_NOON_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_DAN_NIGHT:
		arc_start = ZKN_RANGEDATA_DAN_NIGHT_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_DAN_SPECIAL:
		arc_start = ZKN_RANGEDATA_DAN_SPECIAL_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_DAN_SPECIAL_COMP:
		arc_start = ZKN_RANGEDATA_DAN_SPECIAL_COMP_ARC_S;
		break;
	
	// フィールド分布データ
	case ZKN_RANGEDATA_TYPE_FLD_MORNING:
		arc_start = ZKN_RANGEDATA_FLD_MORNING_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_FLD_NOON:
		arc_start = ZKN_RANGEDATA_FLD_NOON_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_FLD_NIGHT:
		arc_start = ZKN_RANGEDATA_FLD_NIGHT_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_FLD_SPECIAL:
		arc_start = ZKN_RANGEDATA_FLD_SPECIAL_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_FLD_SPECIAL_COMP:
		arc_start = ZKN_RANGEDATA_FLD_SPECIAL_COMP_ARC_S;
		break;
	}
	
	// アーカイブから読み込み
	p_inbuff->p_rangeid = (int *)ArcUtil_LoadEx( ZKN_ARC_DAT, arc_start + mons_no, FALSE, heap, ALLOC_TOP, &data_size );
	
	// データサイズから配列要素数を受け取る
	p_inbuff->num = data_size / sizeof(int);
}

//----------------------------------------------------------------------------
/**
 *	@brief	モンスターナンバー分布データ破棄
 *
 *	@param	p_inbuff 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RANGEDATA_DeleteMonsNoRange( ZKN_RANGE_DATA_MONS* p_inbuff )
{
	GF_ASSERT( p_inbuff );
	GF_ASSERT( p_inbuff->p_rangeid );
	
	sys_FreeMemoryEz( p_inbuff->p_rangeid );
	p_inbuff->p_rangeid = NULL;
	p_inbuff->num = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゾーンIDに対応するダンジョン分布IDを取得
 *
 *	@param	zone_id	ゾーンID
 *	@param	heap	ヒープ
 *
 *	@retval	ZKN_DAN_ID_NONE		対応するIDなし
 *	@retval	その他				対応するID
 */
//-----------------------------------------------------------------------------
int ZKN_RANGEDATA_GetZoneIDLinkDanRangeID( int zone_id, int heap )
{
	return ZknRangeDataZoneLinkIdGet( zone_id, NARC_zukan_enc_diamond_zkn_dan_id_rzidlink, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゾーンIDに対応するフィールド分布IDを取得
 *
 *	@param	zone_id	ゾーンID
 *	@param	heap	ヒープ
 *
 *	@retval	ZKN_FLD_ID_NONE		対応するIDなし
 *	@retval	その他				対応するID
 */
//-----------------------------------------------------------------------------
int ZKN_RANGEDATA_GetZoneIDLinkFldRangeID( int zone_id, int heap )
{
	return ZknRangeDataZoneLinkIdGet( zone_id, NARC_zukan_enc_diamond_zkn_fld_id_rzidlink, heap );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ダンジョングリッド座標データ取得
 *
 *	@param	heap		ヒープ
 *	@param	p_num		データ配列要素数格納先	intの変数	(NULL有効)
 *			この値はZKN_DAN_ID_MAXと同じ
 *
 *	@return	配列	破棄は各自
 */
//-----------------------------------------------------------------------------
ZKN_RANGE_DATA_DAN_GRID* ZKN_RANGEDATA_GetDanGridOamData( int heap, int* p_num )
{
	ZKN_RANGE_DATA_DAN_GRID* p_buff;
	u32 data_size;

	
	// アーカイブから読み込み
	p_buff = (ZKN_RANGE_DATA_DAN_GRID*)ArcUtil_LoadEx( ZKN_ARC_DAT, NARC_zukan_enc_diamond_zkn_dan_griddata_dangri, FALSE, heap, ALLOC_TOP, &data_size );


	// データサイズから配列用数を取得
	if( p_num ){
		*p_num = data_size / sizeof(ZKN_RANGE_DATA_DAN_GRID);
	}

	return p_buff;
}


//----------------------------------------------------------------------------
/**
 *	@brief	フィールドグリッド＆地形データ取得
 *
 *	@param	heap		ヒープ
 *	@param	p_num		データ配列要素数格納先	int の変数　（NULL有効）
 *			この値はZKN_FLD_ID_MAXと同じ
 *	
 *	@return	配列　破棄は各自
 */
//-----------------------------------------------------------------------------
ZKN_RANGE_DATA_FLD_GRID* ZKN_RANGEDATA_GetFldGridAraaData( int heap, int* p_num )
{
	ZKN_RANGE_DATA_FLD_GRID* p_buff;
	u32 data_size;

	
	// アーカイブから読み込み
	p_buff = (ZKN_RANGE_DATA_FLD_GRID*)ArcUtil_LoadEx( ZKN_ARC_DAT, NARC_zukan_enc_diamond_zkn_fld_griddata_fldgri, FALSE, heap, ALLOC_TOP, &data_size );


	// データサイズから配列用数を取得
	if( p_num ){
		*p_num = data_size / sizeof(ZKN_RANGE_DATA_FLD_GRID);
	}

	return p_buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フィールド分布図データを書き込む
 *
 *	@param	p_buff			書き込み先バッファ
 *	@param	buff_x			バッファｘサイズ
 *	@parm	buff_y			バッファｙサイズ
 *	@param	cp_write_data	書き込みデータ	(変数のポインタ)
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RANGE_DATA_FldGridDataWrite( u8* p_buff, u8 buff_x, u8 buff_y, const ZKN_RANGE_DATA_FLD_GRID* cp_write_data )
{
	int i,j;	// ループ

	GF_ASSERT( (cp_write_data->gridy + cp_write_data->sizey) < buff_y );
	GF_ASSERT( (cp_write_data->gridx + cp_write_data->sizex) < buff_x );

	for( i=cp_write_data->gridy; i<cp_write_data->gridy + cp_write_data->sizey; i++ ){

		for( j=cp_write_data->gridx; j<cp_write_data->gridx + cp_write_data->sizex; j++ ){

			p_buff[ (i*buff_x) + j ] |= cp_write_data->arry[ ((i-cp_write_data->gridy) * cp_write_data->sizex) + (j-cp_write_data->gridx)  ];
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	モンスター分布データのフィールド分布マップを作成
 *
 *	@param	p_buff				格納先
 *	@param	buff_x				格納先バッファｘサイズ
 *	@param	buff_y				格納先バッファｙサイズ
 *	@param	cp_write_data		フィールド地形データ（配列）
 *	@param	cp_mons_range		モンスター分布データ
 *	@param	cp_cut_rangeid		排除する分布ID　配列
 *	@param	cut_tbl_num			排除売るID配列数
 *
 *	@return	実際のデータ数	排除配列で排除される可能性があるため
 */
//-----------------------------------------------------------------------------
u32 ZKN_RANGE_DATA_FldGridDataWriteMonsRangeData( u8* p_buff, int buff_x, int buff_y, const ZKN_RANGE_DATA_FLD_GRID* cp_write_data, const ZKN_RANGE_DATA_MONS* cp_mons_range, const u8* cp_cut_randeid, u32 cut_tbl_num )
{
	int i;	// ループ用
	int j;
	u32 count = 0;

	for( i=0; i<cp_mons_range->num - 1; i++ ){	// モンスター分布最後はダミー

		GF_ASSERT( cp_mons_range->p_rangeid[i] );	// 0はおかしい

		// 除外チェック
		for( j = 0; j < cut_tbl_num; j++ ){
			if( cp_mons_range->p_rangeid[i] == cp_cut_randeid[j] ){
				break;
			}
		}

		// 排除以外なら書く
		if( j >= cut_tbl_num ){
			ZKN_RANGE_DATA_FldGridDataWrite( p_buff, buff_x, buff_y,
					&cp_write_data[ cp_mons_range->p_rangeid[i] ] );
			count ++;
		}
	}

	return count;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ダンジョン座標をOAMアクターに設定
 *
 *	@param	p_act			アクター
 *	@param	ofs_x			足しこむ座標値
 *	@param	ofs_y			足しこむ座標値
 *	@param	gridsizex		グリッドｘサイズ
 *	@param	gridsizey		グリッドｙサイズ
 *	@param	cp_write_data	ダンジョン情報
 *	@param	norm_seq		通常アニメシーケンス
 *	@param	sp_seq			特殊アニメシーケンス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RANGE_DATA_DanGridDataSet( CLACT_WORK_PTR p_act, int ofsx, int ofsy, int gridsizex, int gridsizey, const ZKN_RANGE_DATA_DAN_GRID* cp_write_data, int norm_seq, int sp_seq )
{
	VecFx32 mat;

	mat.x = (cp_write_data->gridx * gridsizex) + ofsx;
	mat.y = (cp_write_data->gridy * gridsizey) + ofsy;
	mat.x <<= FX32_SHIFT;
	mat.y <<= FX32_SHIFT;
	
	CLACT_SetMatrix( p_act, &mat );


	// 特殊OAM設定
	if( cp_write_data->oam_flg ){
		CLACT_AnmChg( p_act, sp_seq );
	}else{
		CLACT_AnmChg( p_act, norm_seq );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ダンジョン座標OAM設定関数
 *
 *	@param	pp_act				アクター配列
 *	@param	use_start			使用開始
 *	@param	act_max				アクター配列要素数
 *	@param	ofs_x				足しこむ座標値
 *	@param	ofs_y				足しこむ座標値
 *	@param	gridsizex			１グリッドXサイズ
 *	@param	gridsizey			１グリッドYサイズ
 *	@param	cp_write_data		ダンジョングリッドデータ配列
 *	@param	cp_mons_range		モンスター分布データ
 *	@param	norm_seq		通常アニメシーケンス
 *	@param	sp_seq				特殊OAMの場合のアニメシーケンス
 *	@param	cp_cut_rangeid		排除する分布ID　配列
 *	@param	cut_tbl_num			排除売るID配列数
 *	@param	p_count				実際のデータ数	排除配列で排除される可能性があるため 格納先
 *
 *	@return	使用アクター数
 */
//-----------------------------------------------------------------------------
int ZKN_RANGE_DATA_DanGridDataSetMonsRangeData( CLACT_WORK_PTR* pp_act, int use_start, int act_max, int ofs_x, int ofsy, int gridsizex, int gridsizey, const ZKN_RANGE_DATA_DAN_GRID* cp_write_data, const ZKN_RANGE_DATA_MONS* cp_mons_range, int norm_seq, int sp_seq, const u8* cp_cut_randeid, u32 cut_tbl_num, u32* p_count )
{
	int i, j;
	int act_count = use_start;
	int count = 0;

	for( i=0; i<cp_mons_range->num - 1; i++ ){	// モンスター分布最後はダミー

		GF_ASSERT( cp_mons_range->p_rangeid[i] );
		GF_ASSERT( act_count < act_max );

		// 除外チェック
		for( j = 0; j < cut_tbl_num; j++ ){
			if( cp_mons_range->p_rangeid[i] == cp_cut_randeid[j] ){
				break;
			}
		}

		// 排除以外なら書く
		if( j >= cut_tbl_num ){
		
			ZKN_RANGE_DATA_DanGridDataSet( pp_act[act_count], ofs_x, ofsy, gridsizex, gridsizey, &cp_write_data[ cp_mons_range->p_rangeid[i] ], norm_seq, sp_seq );
			act_count++;
			count ++;
		}

	}

	*p_count = count;

	return act_count;
}

//-----------------------------------------------------------------------------
/**
 *
 *		[プライベート関数]
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	ゾーンIDに対応するIDを返す
 *
 *	@param	zone_id		ゾーンID
 *	@param	arc_dataidx	アーカイブデータIND	（ダンジョンLinkデータORフィールドLINKデータ）
 *	@param	heap		ヒープ
 *
 *	@return	対応するID
 */
//-----------------------------------------------------------------------------
static int ZknRangeDataZoneLinkIdGet( int zone_id, int arc_dataidx, int heap )
{
	int* p_buff;
	u32 data_size;
	int num;
	int i;
	int ret;
	
	GF_ASSERT( (arc_dataidx == NARC_zukan_enc_diamond_zkn_dan_id_rzidlink)||
			(arc_dataidx == NARC_zukan_enc_diamond_zkn_fld_id_rzidlink) );
	
	// アーカイブから読み込み
	p_buff = (int *)ArcUtil_LoadEx( ZKN_ARC_DAT, arc_dataidx, FALSE, heap, ALLOC_BOTTOM, &data_size );
	
	// データサイズから配列要素数を受け取る
	num = data_size / sizeof(int);

	// 見つからないときは0を返すとそれぞれの分布IDのNONE定数になる
	ret = 0;
	// ループ	一緒のナンバーがあったらその配列の要素数が分布ID
	for( i=0; i<num; i++ ){
		if( p_buff[i] == zone_id ){

			ret = i;
			break;
		}
	}

	sys_FreeMemoryEz( p_buff );
	return ret;
}

//============================================================================================
/**
 * @file	zukanwork.c
 * @brief	図鑑状態アクセス用ソース
 * @author	tamada GAME FREAK inc.
 * @date	2005.12.15
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"
#include "poketool/poke_tool.h"

#include "savedata/zukanwork.h"

#include "poketool/monsno.h"
#include "include/application/zukanlist/zkn_world_text_data.h"
#include "src/application/zukanlist/zkn_worldtext.h"

//============================================================================================
//============================================================================================
enum {
	POKEZUKAN_ARRAY_LEN = 16,	///<ポケモン図鑑フラグ配列のおおきさ16 * 32 = 512まで大丈夫

	POKEZUKAN_UNKNOWN_NUM = UNK_END,///<アンノーン数

	MAGIC_NUMBER = 0xbeefcafe,

	POKEZUKAN_DEOKISISU_MSK = 0xf,	// bitマスク
};

//----------------------------------------------------------
/**
 * @brief	自分状態データ型定義
 */
//----------------------------------------------------------
struct _ZUKAN_WORK {
	u32 zukan_magic;						///<マジックナンバー
	u32 get_flag[POKEZUKAN_ARRAY_LEN];		///<捕まえたフラグ用ワーク
	u32 see_flag[POKEZUKAN_ARRAY_LEN];		///<見つけたフラグ用ワーク
	u32 sex_flag[2][POKEZUKAN_ARRAY_LEN];	///<オスメスフラグ用ワーク
	u32 PachiRandom;						///<パッチール用個性乱数保持ワーク
	u8 SiiusiTurn;							///<シーウシ用見つけた順保持ワーク		2bit必要	1bit*2種類
	u8 SiidorugoTurn;						///<シードルゴ用見つけた順保持ワーク	2bit必要	1bit*2種類
	u8 MinomuttiTurn;						///<ミノムッチ用見つけた順保持ワーク	6bit必要	2bit*3種類
	u8 MinomesuTurn;						///<ミノメス用見つけた順保持ワーク		6bit必要	2bit*3種類
	u8 UnknownTurn[ POKEZUKAN_UNKNOWN_NUM ];///<アンノーンを見つけた番号
	u8 GraphicVersionUp;					///<グラフィックバージョン用機能拡張フラグ
	u8 TextVersionUp[ ZKN_WORLD_TEXT_POKE_NUM ];	///<言語バージョンアップマスク
	u8 TextVersionUpMasterFlag;				///<言語バージョンアップMasterフラグ
	u8 zukan_get;							///<ずかん取得フラグ
	u8 zenkoku_flag;						///<全国図鑑保持フラグ
};

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ずかんデータ用ワークのサイズ取得
 * @return	int		ZUKAN_WORKのサイズ
 */
//----------------------------------------------------------
int ZukanWork_GetWorkSize(void)
{
	return sizeof(ZUKAN_WORK);
}
//----------------------------------------------------------
/**
 * @brief	ずかんデータ用ワークの生成処理
 * @param	heapID		使用するヒープの指定
 * @return	ZUKAN_WORK	生成したZUKAN_WORKへのポインタ
 */
//----------------------------------------------------------
ZUKAN_WORK * ZukanWork_AllocWork(u32 heapID)
{
	ZUKAN_WORK * zw;
	zw = sys_AllocMemory(heapID, sizeof(ZUKAN_WORK));
	ZukanWork_Init(zw);
	return zw;
}

//----------------------------------------------------------
/**
 * @brief	ずかんデータ用ワークのコピー
 * @param	from	コピー元ZUKAN_WORKへのポインタ
 * @param	to		コピー先ZUKAN_WORKへのポインタ
 */
//----------------------------------------------------------
void ZukanWork_Copy(const ZUKAN_WORK * from, ZUKAN_WORK * to)
{
	MI_CpuCopy8(from, to, sizeof(ZUKAN_WORK));
}

//============================================================================================
//
//				内部関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ずかんワークの整合性チェック
 */
//----------------------------------------------------------
static inline void zukan_incorrect(const ZUKAN_WORK * zw)
{
	GF_ASSERT(zw->zukan_magic == MAGIC_NUMBER);
}
//----------------------------------------------------------
/**
 * @brief	ポケモンナンバーの範囲チェック
 */
//----------------------------------------------------------
static inline BOOL monsno_incorrect(u16 monsno)
{
	if (monsno == 0 || monsno > MONSNO_END) {
		GF_ASSERT_MSG(0, "ポケモンナンバー異常：%d\n", monsno);
		return TRUE;
	} else {
		return FALSE;
	}
}

//----------------------------------------------------------
/**
 * @brief	汎用ビットチェック
 */
//----------------------------------------------------------
static inline BOOL check_bit(const u8 * array, u16 flag_id)
{
	flag_id --;
	return 0 != (array[flag_id >> 3] & (1 << (flag_id & 7)));
}
//----------------------------------------------------------
/**
 * @brief	汎用ビットセット
 */
//----------------------------------------------------------
static inline void set_bit(u8 * array, u16 flag_id)
{
	flag_id --;
	array[flag_id >> 3] |= 1 << (flag_id & 7);
}
//----------------------------------------------------------
/**
 * @brief	汎用1ビットデータセット
 * そのビットをクリーンにしてから設定します
 */
//----------------------------------------------------------
static inline void setnum_bit(u8 * array, u8 num, u16 flag_id)
{
	GF_ASSERT( num < 2 );
	flag_id --;

	array[flag_id >> 3] &= ~(1 << (flag_id & 7));
	array[flag_id >> 3] |= num << (flag_id & 7);
}

#if 0
static inline void reset_bit(u8 * array, u16 flag_id)
{
	array[flag_id >> 3] &= (1 << (flag_id & 7)) ^ 0xff;
}
#endif
//----------------------------------------------------------
/**
 * @brief	汎用ビット数カウント処理
 */
//----------------------------------------------------------
static inline u16 count_bit(const u32 * array, u32 array_max)
{
	int count, idx;
	u32 item;
	count = 0;
	for (idx = 0; idx < array_max; idx ++) {
		for (item = array[idx]; item != 0; item >>= 1) {
			if (item & 1) {
				count ++;
			}
		}
	}
	return count;
}

//----------------------------------------------------------
/**
 * @brief	汎用2ビットチェック
 * ＊1bit版は1～xを指定するようになっていたが
 * 2bit版は0～xを指定するようにする
 */
//----------------------------------------------------------
static inline u32 check_bit2(const u8 * array, u16 flag_id)
{
	return (array[flag_id >> 2] >> ((flag_id & 3)*2)) & 0x3;
}
//----------------------------------------------------------
/**
 * @brief	汎用2ビットデータセット
 * そのビットをクリーンにしてから設定します
 */
//----------------------------------------------------------
static inline void setnum_bit2(u8 * array, u8 num, u16 flag_id)
{
	GF_ASSERT( num < 4 );

	array[flag_id >> 2] &= ~(0x3 << ((flag_id & 3)*2) );
	array[flag_id >> 2] |= num << ((flag_id & 3)*2);
}


//----------------------------------------------------------
/**
 * @brief	みたビット設定
 */
//----------------------------------------------------------
static inline void set_see_bit(ZUKAN_WORK * zw, u16 flag_id)
{
	set_bit((u8*)zw->see_flag, flag_id);
}
//----------------------------------------------------------
/**
 * @brief	つかまえたビット設定
 */
//----------------------------------------------------------
static inline void set_get_bit(ZUKAN_WORK * zw, u16 flag_id)
{
	set_bit((u8*)zw->get_flag, flag_id);
}
//----------------------------------------------------------
/**
 * @brief	性別ビット設定	実際に設定
 * 最初の性別設定で2要素目の配列にも同じ値を設定する
 * これにより2要素目が同じ値の時は違う性別のポケモンをみていない
 * ということになる
 */
//----------------------------------------------------------
static inline void set_sex_bit_first_second(ZUKAN_WORK * zw, u8 num, u8 no, u16 flag_id)
{
	if( no == ZUKAN_WORK_SEX_FIRST ){
		setnum_bit((u8*)zw->sex_flag[ZUKAN_WORK_SEX_SECOND], num, flag_id);
	}
	setnum_bit((u8*)zw->sex_flag[no], num, flag_id);
}
//----------------------------------------------------------
/**
 * @brief	性別ビット設定
 */
//----------------------------------------------------------
static inline void set_sex_bit(ZUKAN_WORK * zw, u8 num, u8 no, u16 monsno)
{
	GF_ASSERT_MSG( num <= 2, "num = %d", num );	// 男　女　不明以外がきました
	if( num == PARA_UNK ){		// UNKNOWは
		num = PARA_MALE;		// 男にする
	}
	set_sex_bit_first_second(zw, num, no, monsno);
}
//----------------------------------------------------------
/**
 * @brief	みたビットONOFFチェック
 */
//----------------------------------------------------------
static inline BOOL check_see_bit(const ZUKAN_WORK * zw, u16 flag_id)
{
	return check_bit((const u8*)zw->see_flag, flag_id);
}
//----------------------------------------------------------
/**
 * @brief	つかまえたビットONOFFチェック
 */
//----------------------------------------------------------
static inline BOOL check_get_bit(const ZUKAN_WORK * zw, u16 flag_id)
{
	return check_bit((const u8*)zw->get_flag, flag_id);
}
//----------------------------------------------------------
/**
 * @brief	性別ビットONOFFチェック
 */
//----------------------------------------------------------
static inline u8 check_sex_bit(const ZUKAN_WORK * zw, u16 flag_id, u8 first_second)
{
	return check_bit((const u8*)zw->sex_flag[first_second], flag_id);
}

//----------------------------------------------------------
/**
 * @brief	固体乱数を設定
 */
//----------------------------------------------------------
static inline void SetZukanRandom(ZUKAN_WORK * zw, u16 monsno, u32 rand)
{
	if (monsno == MONSNO_PATTIIRU) {
		zw->PachiRandom = rand;
	}
}

//----------------------------------------------------------
/**
 * @brief	アンノーンの現在設定数を取得
 */
//----------------------------------------------------------
static inline int get_zukan_unknown_turn_num( const ZUKAN_WORK * zw )
{
	int i;
	for( i=0; i<POKEZUKAN_UNKNOWN_NUM; i++ ){
		if( zw->UnknownTurn[i] == 0xff ){
			break;
		}
	}
	return i;
}
//----------------------------------------------------------
/**
 * @brief	アンノーンフォーム設定済みかチェック
 */
//----------------------------------------------------------
static inline BOOL check_zukan_unknown_turn_set( const ZUKAN_WORK * zw, u8 form )
{
	int i;
	for( i=0; i<POKEZUKAN_UNKNOWN_NUM; i++ ){
		if( zw->UnknownTurn[i] == form ){
			return TRUE;
		}
	}
	return FALSE;
}
//----------------------------------------------------------
/**
 * @brief	アンノーン見つけた順データの最後に形状IDを設定
 */
//----------------------------------------------------------
static inline void SetZukanUnknownTurn( ZUKAN_WORK * zw, int form)
{
	int set_idx;

	// 設定済みかチェック
	if( check_zukan_unknown_turn_set( zw, form ) ){
		return;
	}

	set_idx = get_zukan_unknown_turn_num( zw );
	if( set_idx < POKEZUKAN_UNKNOWN_NUM ){
		zw->UnknownTurn[ set_idx ] = form;
	}
}

//----------------------------------------------------------
/**
 * @brief	シーウシ　シードルゴの現在設定数を取得
 */
//----------------------------------------------------------
static int get_zukan_siiusi_turn_num( const ZUKAN_WORK * zw, u32 monsno )
{
	u32 first_form;
	u32 second_form;
	const u8* arry;
	GF_ASSERT( (monsno == MONSNO_SIIUSI) || (monsno == MONSNO_SIIDORUGO) );
	
	// 見てもいないときは0
	if( ZukanWork_GetPokeSeeFlag( zw, monsno ) == FALSE ){	
		return 0;
	}

	if( monsno == MONSNO_SIIUSI ){
		arry = &zw->SiiusiTurn;
	}else{
		arry = &zw->SiidorugoTurn;
	}
	first_form = check_bit( arry, 1 );	
	second_form = check_bit( arry, 2 );	

	if( first_form == second_form ){	// 最初と２個めが一緒なら１回だけ
		return 1;
	}
	return 2;
}
//----------------------------------------------------------
/**
 * @brief	ミノムッチ　ミノメス　フォーム設定済みかチェック
 * @param	form	0 or 1
 * *注意 0or1限定で作成しています。
 */
//----------------------------------------------------------
static BOOL check_zukan_siiusi_turn_set( const ZUKAN_WORK * zw, u32 monsno, u8 form )
{
	u32 get_form;
	u32 i;
	u32 roop_num;
	const u8* arry;
	GF_ASSERT( (monsno == MONSNO_SIIUSI) || (monsno == MONSNO_SIIDORUGO) );
	
	// 見てもいないときは設定されているわけがない
	if( ZukanWork_GetPokeSeeFlag( zw, monsno ) == FALSE ){	
		return FALSE;
	}

	if( monsno == MONSNO_SIIUSI ){
		arry = &zw->SiiusiTurn;
	}else{
		arry = &zw->SiidorugoTurn;
	}

	// 設定数分チェック
	// １回しか見ていないときは２つ目のビットは、
	// ダミーデータなので、ちぇっくしない
	roop_num = get_zukan_siiusi_turn_num( zw, monsno );
	for( i=0; i<roop_num; i++ ){
		get_form = check_bit( arry, i+1 );	
		if( get_form == form ){
			return TRUE;
		}
	}
	return FALSE;
}
//----------------------------------------------------------
/**
 * @brief	シーウシ　シードラゴ見つけた順データの最後に形状IDを設定
 * *注意 0or1限定で作成しています。
 */
//----------------------------------------------------------
static void SetZukanSiiusiTurn( ZUKAN_WORK * zw, u32 monsno, int form)
{
	int set_idx;
	u8* arry;
	GF_ASSERT( (monsno == MONSNO_SIIUSI) || (monsno == MONSNO_SIIDORUGO) );

	// 設定済みかチェック
	if( check_zukan_siiusi_turn_set( zw, monsno, form ) ){
		return;
	}

	if( monsno == MONSNO_SIIUSI ){
		arry = &zw->SiiusiTurn;
	}else{
		arry = &zw->SiidorugoTurn;
	}

	set_idx = get_zukan_siiusi_turn_num( zw, monsno );
	if( set_idx < 2 ){	// 0引きなら最初に設定　1なら2つめに設定 2なら設定しない
		setnum_bit( arry, form, set_idx+1 );
		if( set_idx == 0 ){
			setnum_bit( arry, form, set_idx+2 );	// 次も同じ絵で保存する
		}
	}
}

//----------------------------------------------------------
/**
 * @brief	ミノムッチ　ミノメスの現在設定数を取得
 * ＊形状が0～2限定
 */
//----------------------------------------------------------
static int get_zukan_minomutti_turn_num( const ZUKAN_WORK * zw, u32 monsno )
{
	u32 get_form;
	int i;
	const u8* arry;

	GF_ASSERT( (monsno == MONSNO_MINOMUTTI) || (monsno == MONSNO_MINOMESU) );
	// 見てもいないときは0
	if( ZukanWork_GetPokeSeeFlag( zw, monsno ) == FALSE ){	
		return 0;
	}

	if( monsno == MONSNO_MINOMUTTI ){
		arry = &zw->MinomuttiTurn;
	}else{
		arry = &zw->MinomesuTurn;
	}
	for( i=0; i<3; i++ ){
		get_form = check_bit2( arry, i );
		if( get_form == 3 ){
			break;
		}
	}
	return i;
}
//----------------------------------------------------------
/**
 * @brief	ミノムッチ　ミノメス　フォーム設定済みかチェック
 * @param	form	0 or 1 or 2
 * ＊形状が0～2限定
 */
//----------------------------------------------------------
static BOOL check_zukan_minomutti_turn_set( const ZUKAN_WORK * zw, u32 monsno, u8 form )
{
	u32 get_form;
	int i;
	const u8* arry;

	GF_ASSERT( (monsno == MONSNO_MINOMUTTI) || (monsno == MONSNO_MINOMESU) );
	// 見てもいないときはFALSE
	if( ZukanWork_GetPokeSeeFlag( zw, monsno ) == FALSE ){	
		return FALSE;
	}

	if( monsno == MONSNO_MINOMUTTI ){
		arry = &zw->MinomuttiTurn;
	}else{
		arry = &zw->MinomesuTurn;
	}
	for( i=0; i<3; i++ ){
		get_form = check_bit2( arry, i );
		if( get_form == form ){
			return TRUE;
		}
	}
	return FALSE;
}
//----------------------------------------------------------
/**
 * @brief	ミノムッチ　ミノメス見つけた順データの最後に形状IDを設定
 * ＊形状が0～2限定
 */
//----------------------------------------------------------
static void SetZukanMinomuttiTurn( ZUKAN_WORK * zw, u32 monsno, int form)
{
	int set_idx;
	u8* arry;
	GF_ASSERT( (monsno == MONSNO_MINOMUTTI) || (monsno == MONSNO_MINOMESU) );

	// 設定済みかチェック
	if( check_zukan_minomutti_turn_set( zw, monsno, form ) ){
		return;
	}

	if( monsno == MONSNO_MINOMUTTI ){
		arry = &zw->MinomuttiTurn;
	}else{
		arry = &zw->MinomesuTurn;
	}

	set_idx = get_zukan_minomutti_turn_num( zw, monsno );
	if( set_idx < 3 ){
		setnum_bit2( arry, form, set_idx );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	デオキシスフォルム設定
 *
 *	@param	p_arry	格納領域
 *	@param	no	デオキシスフォルム
 *	@param	num	見つけた順番設定
 */
//-----------------------------------------------------------------------------
static inline void setDeokisisuFormNoCore( u32* p_arry, u8 no, u8 num )
{
	u32 shift = (24 + (num * 4));
	u32 msk = ~(POKEZUKAN_DEOKISISU_MSK << shift);
	p_arry[ POKEZUKAN_ARRAY_LEN - 1 ] &= msk;
	p_arry[ POKEZUKAN_ARRAY_LEN - 1 ] |= (no << shift);
}

//----------------------------------------------------------------------------
/**
 *	@brief	デオキシスフォルム設定
 *
 *	@param	zw	図鑑ワーク
 *	@param	no	デオキシスフォルム
 *	@param	num	見つけた順番設定
 */
//-----------------------------------------------------------------------------
static void setDEOKISISUFormNo( ZUKAN_WORK * zw, u8 no, u8 num )
{
	GF_ASSERT( num < ZUKAN_WORK_DEOKISISU_FORM_NUM );
	GF_ASSERT( no <= POKEZUKAN_DEOKISISU_INIT );
	// デオキシスナンバーを設定
	// 捕まえたフラグの後ろ15bit空いているので
	// 後ろ4bitずつにデータを登録しておく
	if( num < ZUKAN_WORK_DEOKISISU_FORM_SAVEDATA_CUTNUM ){
		setDeokisisuFormNoCore( zw->get_flag, no, num );
	}else{
		setDeokisisuFormNoCore( zw->see_flag, no, num-ZUKAN_WORK_DEOKISISU_FORM_SAVEDATA_CUTNUM );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	デオキシスフォルム取得
 *
 *	@param	p_arry	格納領域
 *	@param	num	見つけた順番設定
 *
 *	@retval	フォルムナンバー
 */
//-----------------------------------------------------------------------------
static inline u32 getDeokisisuFormNoCore( const u32* p_arry, u8 num )
{
	u32 shift = (24 + (num * 4));
	u32 ret = (p_arry[ POKEZUKAN_ARRAY_LEN - 1 ] >> shift) & POKEZUKAN_DEOKISISU_MSK;
	return ret;
}
//----------------------------------------------------------------------------
/**
 *	@brief	デオキシスフォルム取得
 *
 *	@param	zw	図鑑ワーク
 *	@retval	デオキシスフォルム
 */
//-----------------------------------------------------------------------------
static inline u32 getDEOKISISUFormNo( const ZUKAN_WORK * zw, u8 num )
{
	u32 form;
	// デオキシスナンバーを設定
	// 捕まえたフラグの後ろ15bit空いているので
	// 後ろ4bitにデータを登録しておく
	if( num < ZUKAN_WORK_DEOKISISU_FORM_SAVEDATA_CUTNUM ){
		form = getDeokisisuFormNoCore( zw->get_flag, num );
	}else{
		form = getDeokisisuFormNoCore( zw->see_flag, num - ZUKAN_WORK_DEOKISISU_FORM_SAVEDATA_CUTNUM );
	}
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	今までに見たデオキシスの数を返す
 *
 *	@param	zw	図鑑ワーク
 *
 *	@return	今までに見たデオキシスの数を返す
 */
//-----------------------------------------------------------------------------
static u32 nowGetDeokisisuFormNum( const ZUKAN_WORK * zw )
{
	int i;

	for( i=0; i<ZUKAN_WORK_DEOKISISU_FORM_NUM; i++ ){
		if( getDEOKISISUFormNo( zw, i ) == POKEZUKAN_DEOKISISU_INIT  ){
			break;
		}
	}
	return i;
}

//----------------------------------------------------------------------------
/**
 *	@brief	以前にこの形状のデオキシスを見ているかチェック
 *
 *	@param	zw	図鑑ワーク
 *	@param	formno 形状
 *
 *	@retval	TRUE	見た
 *	@retval	FALSE	見ていない
 */
//-----------------------------------------------------------------------------
static BOOL checkSeeDeokisisuFormNo( const ZUKAN_WORK * zw, u32 formno )
{
	int i;
	for( i=0; i<ZUKAN_WORK_DEOKISISU_FORM_NUM; i++ ){
		if( getDEOKISISUFormNo( zw, i ) == formno  ){
			return TRUE;
		}
	}
	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *	@brief	フォームナンバー設定　パック
 */
//-----------------------------------------------------------------------------
static void SetDeokisisuFormNo( ZUKAN_WORK * zw, u16 monsno, POKEMON_PARAM* pp  )
{
	u8 form = PokeParaGet( pp, ID_PARA_form_no, NULL );
	u32 setno;

	if( monsno == MONSNO_DEOKISISU ){
		// まだ見ていないかチェック
		if( checkSeeDeokisisuFormNo( zw, form ) == FALSE ){
			setno = nowGetDeokisisuFormNum( zw );	// 設定位置
			setDEOKISISUFormNo( zw, form, setno );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	デオキシスフォルムナンバーバッファ初期化
 *
 *	@param	zw	図鑑ワーク
 */
//-----------------------------------------------------------------------------
static void InitDeokisisuFormNo( ZUKAN_WORK * zw )
{
	int i;
	for( i=0; i<ZUKAN_WORK_DEOKISISU_FORM_NUM; i++ ){
		setDEOKISISUFormNo( zw, 0xf, i );	// 0xfで初期化する
	}
}





//----------------------------------------------------------
/**
 * @brief	いろんなポケモンの見つけた順データの保存
 */
//----------------------------------------------------------
static void SetZukanSpecialTurn(ZUKAN_WORK * zw, u16 monsno, POKEMON_PARAM* pp)
{
	int form;
	
	// アンノーン　ウミウシ　ミノムシの順番の設定
	if( monsno == MONSNO_ANNOON ){
		form = PokeParaUnknownFormGet( pp );
		SetZukanUnknownTurn( zw, form );
	}else if( monsno == MONSNO_MINOMUTTI ){
		form = PokeParaGet( pp, ID_PARA_form_no, NULL );
		SetZukanMinomuttiTurn( zw, monsno, form );
	}else if( monsno == MONSNO_MINOMESU ){
		form = PokeParaGet( pp, ID_PARA_form_no, NULL );
		SetZukanMinomuttiTurn( zw, monsno, form );
	}else if( monsno == MONSNO_SIIUSI ){
		form = PokeParaGet( pp, ID_PARA_form_no, NULL );
		SetZukanSiiusiTurn( zw, monsno, form );
	}else if( monsno == MONSNO_SIIDORUGO ){
		form = PokeParaGet( pp, ID_PARA_form_no, NULL );
		SetZukanSiiusiTurn( zw, monsno, form );
	}else if( monsno == MONSNO_DEOKISISU ){
		SetDeokisisuFormNo( zw, monsno, pp );	// デオキシスのフォルムを保存
	}
}

//----------------------------------------------------------
/**
 * @brief	テキストバージョン配列インデックスをモンスターナンバーから取得
 */
//----------------------------------------------------------
static inline int get_zukan_textversion_idx(u16 monsno)
{
	return ZKN_WT_GetMonsNo_TEXTVERPokeNum( monsno );
}
//----------------------------------------------------------
/**
 * @brief	テキストバージョンフラグ設定
 */
//----------------------------------------------------------
static void SetZukanTextVersionUp(ZUKAN_WORK * zw, u16 monsno, u32 lang)
{
	int idx;
	int zkn_world_text_code;
	
	
	idx = get_zukan_textversion_idx( monsno );
	zkn_world_text_code = ZKN_WT_GetLANG_Code_ZKN_WORLD_TEXT_Code( lang );

	// そのポケモンに外国語データはない
	if(idx == ZKN_WORLD_TEXT_POKE_NUM){ return; }

	// その国の外国語データはない
	if(zkn_world_text_code == ZKN_WORLD_TEXT_NUM){ return; }

	zw->TextVersionUp[ idx ] |= 1 << zkn_world_text_code;
}
//----------------------------------------------------------
/**
 * @brief	通常のポケモン性別取得
 */
//----------------------------------------------------------
static u32 get_normal_poke_sex( const ZUKAN_WORK * zw, u16 monsno, int first_second )
{
	u32 sex_first, sex_second;
	u32 ret_sex;

	// 絶対に不明なポケモンはfirstは不明をsecondはエラーを返す
	if( PokePersonalParaGet(monsno,ID_PER_sex) == MONS_UNKNOWN ){
		if( first_second == ZUKAN_WORK_SEX_FIRST ){
			return PARA_UNK;
		}else{
			return ZUKAN_WORK_GET_SEX_ERR;
		}
	}
	
	// 次に見た性別が設定されているのかチェックするために
	// どっちの場合でも最初に見た性別を取得
	sex_first = check_sex_bit( zw, monsno, ZUKAN_WORK_SEX_FIRST );

	// 次に見た性別を取得するなら次に見た性別を取得
	if( first_second == ZUKAN_WORK_SEX_SECOND ){
		sex_second = check_sex_bit( zw, monsno, ZUKAN_WORK_SEX_SECOND );

		// 最初に見た性別と一緒==まだ見ていない
		if( sex_second == sex_first ){
			ret_sex = ZUKAN_WORK_GET_SEX_ERR;
		}else{
			ret_sex = sex_second;
		}
	}else{
		ret_sex = sex_first;
	}

	return ret_sex;
}

//----------------------------------------------------------
/**
 * @brief	アンノーン見つけた順番取得
 */
//----------------------------------------------------------
static inline int get_unknown_see_form( const ZUKAN_WORK * zw, int idx )
{
	return zw->UnknownTurn[ idx ];
}

//----------------------------------------------------------
/**
 * @brief	シーウシ　シードラゴ見つけた順番取得
 *注意 0or1限定で作成しています。
 */
//----------------------------------------------------------
static inline int get_siiusi_see_form( const ZUKAN_WORK * zw, u32 monsno, int idx )
{
	const u8* arry;
	GF_ASSERT( (monsno == MONSNO_SIIUSI) || (monsno == MONSNO_SIIDORUGO) );
	GF_ASSERT( idx < 2 );
	
	if( monsno == MONSNO_SIIUSI ){
		arry = &zw->SiiusiTurn;
	}else{
		arry = &zw->SiidorugoTurn;
	}
	return check_bit( arry, idx+1 );
}

//----------------------------------------------------------
/**
 * @brief	ミノムッチ　ミノメス見つけた順番取得
 *注意 0～2限定で作成しています。
 */
//----------------------------------------------------------
static inline int get_minomutti_see_form( const ZUKAN_WORK * zw, u32 monsno, int idx )
{
	const u8* arry;
	GF_ASSERT( (monsno == MONSNO_MINOMUTTI) || (monsno == MONSNO_MINOMESU) );
	GF_ASSERT( idx < 3 );
	
	if( monsno == MONSNO_MINOMUTTI ){
		arry = &zw->MinomuttiTurn;
	}else{
		arry = &zw->MinomesuTurn;
	}
	return check_bit2( arry, idx );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ゼンコク図鑑完成に必要なポケモンかチェック
 */
//-----------------------------------------------------------------------------
static BOOL check_ZenkokuCompMonsno( u16 monsno )
{
	int i;
	BOOL cut_check;
	static const u16 cut_check_monsno[ ZUKAN_WORK_ZENKOKU_COMP_NOPOKE_NUM ] = {
		MONSNO_MYUU,
		MONSNO_RUGIA,
		MONSNO_HOUOU,
		MONSNO_SEREBHI,
		MONSNO_ZIRAATI,
		MONSNO_DEOKISISU,
		MONSNO_ERUFI,
		MONSNO_MANAFI,
		MONSNO_DAAKU,
		MONSNO_EURISU,
		MONSNO_AUSU,
	};

	// チェック除外ポケモンチェック
	cut_check = TRUE;
	for( i=0; i<ZUKAN_WORK_ZENKOKU_COMP_NOPOKE_NUM; i++ ){
		if( cut_check_monsno[ i ] == monsno ){
			cut_check = FALSE;
		}
	}
	return cut_check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	シンオウ図鑑完成に必要なポケモンかチェック
 */
//-----------------------------------------------------------------------------
static BOOL check_ShinouCompMonsno( u16 monsno )
{
	int i;
	BOOL cut_check;
	static const u16 cut_check_monsno[ZUKAN_WORK_SHINOU_COMP_NOPOKE_NUM] = {
		MONSNO_MANAFI,
	};

	// チェック除外ポケモンチェック
	cut_check = TRUE;
	for( i=0; i<ZUKAN_WORK_SHINOU_COMP_NOPOKE_NUM; i++ ){
		if( cut_check_monsno[ i ] == monsno ){
			cut_check = FALSE;
		}
	}
	return cut_check;
}

//============================================================================================
//
//			ずかん情報操作用の外部公開関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief		ずかんワークの初期化
 * @param	zw		ずかんワークへのポインタ
 */
//----------------------------------------------------------
void ZukanWork_Init(ZUKAN_WORK * zw)
{
	memset(zw, 0, sizeof(ZUKAN_WORK));
	zw->zukan_magic = MAGIC_NUMBER;
	zw->zenkoku_flag = FALSE;

	// 捕まえた順番フラグにダミーデータ設定
	memset( zw->UnknownTurn, 0xff, sizeof(u8) *  POKEZUKAN_UNKNOWN_NUM );
	zw->SiiusiTurn = 0xff;		
	zw->SiidorugoTurn = 0xff;	
	zw->MinomuttiTurn = 0xff;	
	zw->MinomesuTurn = 0xff;	

	// デオキシスフォルムタイプ保存領域の初期化
	InitDeokisisuFormNo( zw );
}

//----------------------------------------------------------
/**
 * @brief	ポケモンをつかまえた数の取得
 * @param	zw		ずかんワークへのポインタ
 * @return	u16		捕まえた数
 */
//----------------------------------------------------------
u16 ZukanWork_GetPokeGetCount(const ZUKAN_WORK * zw)
{
	int i;
	int count;

	zukan_incorrect(zw);
	count= 0;
	for( i=1; i<=MONSNO_END; i++ ){
		if( ZukanWork_GetPokeGetFlag( zw, i ) == TRUE ){
			count ++;
		}
	}
	return count;

	// 高速ですが、デオキシスフラグをget_flagの後ろに入れたので、使用できません
//	return count_bit(zw->get_flag, POKEZUKAN_ARRAY_LEN);

}

//----------------------------------------------------------
/**
 * @brief	ポケモンを見つけた数の取得
 * @param	zw		ずかんワークへのポインタ
 * @return	u16		見つけた数
 */
//----------------------------------------------------------
u16 ZukanWork_GetPokeSeeCount(const ZUKAN_WORK * zw)
{
	int i;
	int count;

	zukan_incorrect(zw);
	count= 0;
	for( i=1; i<=MONSNO_END; i++ ){
		if( ZukanWork_GetPokeSeeFlag( zw, i ) == TRUE ){
			count ++;
		}
	}
	return count;

	// 高速ですが、デオキシスフラグをget_flagの後ろに入れたので、使用できません
//	return count_bit(zw->see_flag, POKEZUKAN_ARRAY_LEN);
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在の図鑑ﾓｰﾄﾞのポケモンを捕まえた数取得
 *	@param	zw		図鑑ワークへのポインタ
 *	@return	捕まえた数
 */
//-----------------------------------------------------------------------------
u16 ZukanWork_GetZukanPokeGetCount(const ZUKAN_WORK * zw)
{
	if( ZukanWork_GetZenkokuZukanFlag( zw ) ){
		return ZukanWork_GetPokeGetCount( zw );
	}
	return ZukanWork_GetShinouPokeGetCount( zw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在の図鑑ﾓｰﾄﾞのポケモンを見た数取得
 *	@param	zw		図鑑ワークへのポインタ
 *	@return 見た数
 */
//-----------------------------------------------------------------------------
u16 ZukanWork_GetZukanPokeSeeCount(const ZUKAN_WORK * zw)
{
	if( ZukanWork_GetZenkokuZukanFlag( zw ) ){
		return ZukanWork_GetPokeSeeCount( zw );
	}
	return ZukanWork_GetShinouPokeSeeCount( zw );
}

//----------------------------------------------------------
/**
 * 【シンオウ】
 * @brief	ポケモンをつかまえた数の取得
 * @param	zw		ずかんワークへのポインタ
 * @return	u16		捕まえた数
 */
//----------------------------------------------------------
u16 ZukanWork_GetShinouPokeGetCount(const ZUKAN_WORK * zw)
{
	int i;
	int count;
	zukan_incorrect(zw);
	count= 0;
	for( i=1; i<=MONSNO_END; i++ ){
		if( ZukanWork_GetPokeGetFlag( zw, i ) == TRUE ){
			// ｼﾝｵｳｽﾞｶﾝにいるかチェック
			if( PokeZenkokuNo2ShinouNo( i ) != 0 ){
				count ++;
			}
		}
	}
	return count;
}

//----------------------------------------------------------
/**
 * 【シンオウ】
 * @brief	ポケモンを見つけた数の取得
 * @param	zw		ずかんワークへのポインタ
 * @return	u16		見つけた数
 */
//----------------------------------------------------------
u16 ZukanWork_GetShinouPokeSeeCount(const ZUKAN_WORK * zw)
{
	int i;
	int count;
	zukan_incorrect(zw);
	count= 0;
	for( i=1; i<=MONSNO_END; i++ ){
		if( ZukanWork_GetPokeSeeFlag( zw, i ) == TRUE ){
			// ｼﾝｵｳｽﾞｶﾝにいるかチェック
			if( PokeZenkokuNo2ShinouNo( i ) != 0 ){
				count ++;
			}
		}
	}
	return count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	全国図鑑が完成したかチェックする
 *
 *	@param	zw	図鑑ワーク
 *
 *	@retval	TRUE	完成
 *	@retval	FALSE	未完成
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_CheckZenkokuComp(const ZUKAN_WORK * zw)
{
	u16 num;

	// ゼンコク図鑑完成に必要なポケモンを何匹捕まえたか
	num = ZukanWork_GetZenkokuGetCompCount( zw );

	if( num >= ZUKAN_WORK_ZENKOKU_COMP_NUM ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	シンオウ図鑑が完成したかチェックする
 *
 *	@param	zw	図鑑ワーク
 *
 *	@retval	TRUE	完成
 *	@retval	FALSE	未完成
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_CheckShinouComp(const ZUKAN_WORK * zw)
{
	u16 num;

	// シンオウ図鑑完成に必要なポケモンを何匹見つけたか
	num = ZukanWork_GetShinouSeeCompCount( zw );

	if( num >= ZUKAN_WORK_SHINOU_COMP_NUM ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゼンコク図鑑　完成に必要なポケモンを捕まえた数
 *
 *	@param	zw		図鑑ワーク
 *	@return	完成に必要なポケモンを捕まえた数
 */
//-----------------------------------------------------------------------------
u16 ZukanWork_GetZenkokuGetCompCount(const ZUKAN_WORK * zw)
{
	int i;
	u16 num;
	// エルフィ　マナフィ　ダーク　エリウス　アウス
	// 以外を捕まえていたらOK
	num = 0;
	for( i=1; i<=ZUKAN_WORK_ZENKOKU_MONSMAX; i++ ){
		if( ZukanWork_GetPokeGetFlag( zw, i ) == TRUE ){
			if( check_ZenkokuCompMonsno( i ) == TRUE ){
				num ++;
			}
		}
	}
	return num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	シンオウ図鑑　完成に必要なポケモンを見つけた数
 *
 *	@param	zw		図鑑ワーク
 *	@return	完成に必要なポケモンを見つけた数
 */
//-----------------------------------------------------------------------------
u16 ZukanWork_GetShinouSeeCompCount(const ZUKAN_WORK * zw)
{
	int i;
	u16 num;
	u32 monsno;

	// エルフィ　マナフィ　ダーク　エリウス　アウス
	// 以外を捕まえていたらOK
	num = 0;
	for( i=1; i<=ZUKAN_WORK_ZENKOKU_MONSMAX; i++ ){
		if( ZukanWork_GetPokeSeeFlag( zw, i ) == TRUE ){
			monsno = PokeZenkokuNo2ShinouNo( i );
			if( monsno != 0 ){
				if( check_ShinouCompMonsno( i ) == TRUE ){
					num ++;
				}
			}
		}
	}
	return num;
}

//----------------------------------------------------------
/**
 * @brief	ポケモンを捕まえたかどうかのフラグ取得
 * @param	zw		ずかんワークへのポインタ
 * @param	monsno	ポケモンナンバー
 * @return	BOOL	フラグ結果
 */
//----------------------------------------------------------
BOOL ZukanWork_GetPokeGetFlag(const ZUKAN_WORK * zw, u16 monsno)
{
	zukan_incorrect(zw);
	if (monsno_incorrect(monsno)) {
		return FALSE;
	}
	if (check_get_bit(zw, monsno) && check_see_bit(zw, monsno)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//----------------------------------------------------------
/**
 * @brief	ポケモンを見つけたかどうかのフラグ取得
 * @param	zw		ずかんワークへのポインタ
 * @param	monsno	ポケモンナンバー
 * @return	BOOL	フラグ結果
 */
//----------------------------------------------------------
BOOL ZukanWork_GetPokeSeeFlag(const ZUKAN_WORK * zw, u16 monsno)
{
	zukan_incorrect(zw);
	if (monsno_incorrect(monsno)) {
		return FALSE;
	}
	return check_see_bit(zw, monsno);
}

//----------------------------------------------------------------------------
/**
 *	@brief	特殊ポケモンの個性乱数取得
 *
 *	@param	zw			図鑑ワークへのポインタ
 *	@param	random_poke	取得するポケモン個性乱数
 *
 *	@return	個性乱数
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeRandomFlag(const ZUKAN_WORK * zw, u8 random_poke)
{
	u32 random;
	
	zukan_incorrect(zw);

	switch( random_poke ){
	case ZUKAN_WORK_RANDOM_PACHI:		// パッチール個性乱数
		random = zw->PachiRandom;
		break;
		
	default:
		GF_ASSERT_MSG( 0, "random_poke = %d\n", random_poke );
		break;
	}

	return random;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンを表示するときの性別取得
 *
 *	@param	zw				ずかんワークへのポインタ
 *	@param	monsno			ポケモンナンバー
 *	@param	first_second	最初に見た性別か次に見た性別か
 *
 *	@retval	PARA_MALE		オス
 *	@retval	PARA_FEMALE		メス
 *	@retval	PARA_UNK		不明	
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	見た性別がまだ無い
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeSexFlag(const ZUKAN_WORK * zw, u16 monsno, int first_second )
{
	zukan_incorrect(zw);
	if (monsno_incorrect(monsno)) {
		return ZUKAN_WORK_GET_SEX_ERR;
	}
	// 見てないときはエラーコードを返す
	if( !check_see_bit(zw, monsno) ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}

	// ノーマルポケモン
	return get_normal_poke_sex( zw, monsno, first_second );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アンノーン見つけた順設定
 *
 *	@param	zw		図鑑ワーク
 *	@param	count	アンノーン順番	(0～27)
 *	
 *	@retval	アンノーンフォームナンバー
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	見つけていない
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeAnoonForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);
	// その数のアンノーンフォルムを見ているかチェック
	if( get_zukan_unknown_turn_num( zw ) <= count ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}

	// フォルム数を返す
	return get_unknown_see_form( zw, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アンノーンを見た数
 *
 *	@param	zw		図鑑ワーク
 *
 *	@return	見た数
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeAnoonSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return get_zukan_unknown_turn_num( zw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	シーウシフォルム取得
 *
 *	@param	zw		図鑑ワーク
 *	@param	count	見つけた順番数	
 *
 *	@retval	その順番に見つけたフォルム
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	見つけていない
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeSiiusiForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);

	// その数のシーウシフォルムを見ているかチェック
	if( get_zukan_siiusi_turn_num( zw, MONSNO_SIIUSI ) <= count ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}
	return get_siiusi_see_form( zw, MONSNO_SIIUSI, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	シーウシのフォルムを見た数
 *
 *	@param	zw	図鑑ワーク
 *
 *	@return	フォルムを見た数
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeSiiusiSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return get_zukan_siiusi_turn_num( zw, MONSNO_SIIUSI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	シードルゴフォルムナンバー取得
 *
 *	@param	zw		図鑑ワーク
 *	@param	count	見つけた順番数	
 *
 *	@retval	その順番に見つけたフォルムナンバー
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	見つけていない
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeSiidorugoForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);
	
	// その数のシードルゴフォルムを見ているかチェック
	if( get_zukan_siiusi_turn_num( zw, MONSNO_SIIDORUGO ) <= count ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}
	return get_siiusi_see_form( zw, MONSNO_SIIDORUGO, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	シードルゴのフォルムを見た数
 *
 *	@param	zw	図鑑ワーク
 *
 *	@return	フォルムを見た数
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeSiidorugoSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return get_zukan_siiusi_turn_num( zw, MONSNO_SIIDORUGO );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ミノムッチフォルムナンバー取得
 *
 *	@param	zw		図鑑ワーク
 *	@param	count	見つけた順番数	
 *
 *	@retval	その順番に見つけたフォルムナンバー
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	見つけていない
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeMinomuttiForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);

	// その数のミノムッチフォルムを見ているかチェック
	if( get_zukan_minomutti_turn_num( zw, MONSNO_MINOMUTTI ) <= count ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}
	return get_minomutti_see_form( zw, MONSNO_MINOMUTTI, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ミノムッチのフォルムを見た数
 *
 *	@param	zw	図鑑ワーク
 *
 *	@return	フォルムを見た数
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeMinomuttiSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return get_zukan_minomutti_turn_num( zw, MONSNO_MINOMUTTI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ミノメス地形フォルムナンバー取得
 *
 *	@param	zw		図鑑ワーク
 *	@param	count	見つけた順番数	
 *
 *	@retval	その順番に見つけたフォルムナンバー
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	見つけていない
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeMinomesuForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);

	// その数のミノメスフォルムを見ているかチェック
	if( get_zukan_minomutti_turn_num( zw, MONSNO_MINOMESU ) <= count ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}
	return get_minomutti_see_form( zw, MONSNO_MINOMESU, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ミノメスのフォルムを見た数
 *
 *	@param	zw	図鑑ワーク
 *
 *	@return	フォルムを見た数
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeMinomesuSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return get_zukan_minomutti_turn_num( zw, MONSNO_MINOMESU );
}

//----------------------------------------------------------------------------
/**
 *	@brief	デオキシスフォルム　を取得する
 *
 *	@param	zw	図鑑ワーク
 *	@param	countカウント
 *
 *	@return	デオキシスフォルムナンバー
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeDeokisisuForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);
	return getDEOKISISUFormNo( zw, count );
}

//----------------------------------------------------------------------------
/**	
 *	@brief	デオキシスフォルム　を見た数取得
 *
 *	@param	zw	図鑑ワーク
 *
 *	@return	見た数
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeDeokisisuFormSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return nowGetDeokisisuFormNum( zw );
}


//----------------------------------------------------------
/**
 * @brief	ずかんデータセット（見つけた）
 * @param	zw		ずかんワークへのポインタ
 * @param	pp		見つけたポケモンのPOKEMON_PARAMへのポインタ
 */
//----------------------------------------------------------
void ZukanWork_SetPokeSee(ZUKAN_WORK * zw, POKEMON_PARAM * pp)
{
	u16 monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
	u32 rand = PokeParaGet(pp, ID_PARA_personal_rnd, NULL);
	u32 sex = PokeSexGet(pp);
	u32 first_sex;	// 最初に見た性別

	zukan_incorrect(zw);
	if (monsno_incorrect(monsno)) {
		return;
	}
	if (!check_see_bit(zw, monsno)) {
		SetZukanRandom(zw, monsno, rand);			// 固体乱数
		set_sex_bit( zw, sex, ZUKAN_WORK_SEX_FIRST, monsno );			// 最初に見た性別
	}else{
		// 最初に見た性別と違うときセカンドに登録する
		first_sex = check_sex_bit( zw, monsno, ZUKAN_WORK_SEX_FIRST );
		if( first_sex != sex ){
			set_sex_bit( zw, sex, ZUKAN_WORK_SEX_SECOND, monsno );			// 次に見た性別
		}
	}
	SetZukanSpecialTurn(zw, monsno, pp);		// 特殊ポケモンの見つけた順番設定
	set_see_bit(zw, monsno);
}

//----------------------------------------------------------
/**
 * @brief	ずかんデータセット（捕まえた）
 * @param	zw		ずかんワークへのポインタ
 * @param	pp		捕まえたポケモンのPOKEMON_PARAMへのポインタ
 */
//----------------------------------------------------------
void ZukanWork_SetPokeGet(ZUKAN_WORK * zw, POKEMON_PARAM * pp)
{
	u16 monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
	u32 lang = PokeParaGet(pp, ID_PARA_country_code, NULL);
	u32 rand = PokeParaGet(pp, ID_PARA_personal_rnd, NULL);
	u32 sex = PokeSexGet(pp);
	u32 first_sex;	// 最初に見た性別

	zukan_incorrect(zw);
	if (monsno_incorrect(monsno)) {
		return;
	}
	if (!check_see_bit(zw, monsno)) {
		SetZukanRandom(zw, monsno, rand);			// 固体乱数
		set_sex_bit( zw, sex, ZUKAN_WORK_SEX_FIRST, monsno );			// 表示性別
	}else{
		// 最初に見た性別と違うときセカンドに登録する
		first_sex = check_sex_bit( zw, monsno, ZUKAN_WORK_SEX_FIRST );
		if( first_sex != sex ){
			set_sex_bit( zw, sex, ZUKAN_WORK_SEX_SECOND, monsno );			// 表示性別
		}
	}
	SetZukanSpecialTurn(zw, monsno, pp);		// 特殊ポケモンの見つけた順番設定
	SetZukanTextVersionUp(zw, monsno, lang);	// 国コード
	set_get_bit(zw, monsno);
	set_see_bit(zw, monsno);
}

//----------------------------------------------------------
/**
 * @brief	全国ずかんモードをセット
 * @param	zw		ずかんワークへのポインタ
 */
//----------------------------------------------------------
void ZukanWork_SetZenkokuZukanFlag(ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	zw->zenkoku_flag = TRUE;
}

//----------------------------------------------------------
/**
 * @brief	全国ずかんモードかどうか？の問い合わせ
 * @param	zw		ずかんワークへのポインタ
 * @retval	TRUE	全国ずかんモードオープン
 * @retval	FALSE	シンオウずかんモード
 */
//----------------------------------------------------------
BOOL ZukanWork_GetZenkokuZukanFlag(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return zw->zenkoku_flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィックバージョン用機能拡張フラグ取得
 *
 *	@param	zw		ずかんワークへのポインタ
 *
 *	@retval	TRUE	バージョンアップ完了
 *	@retval	FALSE	バージョンアップ未完了
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_GetGraphicVersionUpFlag(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return zw->GraphicVersionUp;
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィックバージョン用機能拡張フラグ設定
 *
 *	@param	zw		図鑑ワークへのポインタ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZukanWork_SetGraphicVersionUpFlag(ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	zw->GraphicVersionUp = 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑テキストバージョンチェック
 *
 *	@param	zw
 *	@param	monsno
 *	@param	country_code		国コード
 *
 *	@retval	TRUE	その国のバージョンを表示してよい
 *	@retval	FALSE	その国のバージョンを表示してはいけない
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_GetTextVersionUpFlag(const ZUKAN_WORK * zw, u16 monsno, u32 country_code)
{
	int idx;


	GF_ASSERT( country_code < 8 );		// 国コード最大数
	
	zukan_incorrect(zw);
	// テキストバージョンのあるポケモンかチェック
	idx = get_zukan_textversion_idx(monsno);
	if( idx == ZKN_WORLD_TEXT_POKE_NUM ){ return FALSE; }

	// 外国語テキスト用ナンバーに変換
	country_code = ZKN_WT_GetLANG_Code_ZKN_WORLD_TEXT_Code( country_code );

	// その言語のフラグがたっているかチェック
	return (zw->TextVersionUp[idx] & (1<<country_code));
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑外国語バージョン　Masterフラグ
 *
 *	@param	zw	図鑑ワーク
 *	このフラグがたっていないと、外国語図鑑はオープンされない
 */
//-----------------------------------------------------------------------------
void ZukanWork_SetTextVersionUpMasterFlag( ZUKAN_WORK * zw )
{
	zw->TextVersionUpMasterFlag = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑外国語バージョン　Masterフラグ取得
 *
 *	@param	zw	図鑑ワーク
 *
 *	@retval	TRUE	バージョンアップ済み
 *	@retval	FALSE	バージョンアップされてない
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_GetTextVersionUpMasterFlag(const ZUKAN_WORK * zw)
{
	return zw->TextVersionUpMasterFlag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑保持フラグ取得
 *
 *	@param	zw	図鑑ワークへのポインタ
 *
 *	@retval	TRUE	保持
 *	@retval	FALSE	保持していない
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_GetZukanGetFlag(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return zw->zukan_get;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑保持フラグ設定
 *
 *	@param	zw	図鑑ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZukanWork_SetZukanGetFlag(ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	zw->zukan_get = TRUE;
}

//============================================================================================
//
//	セーブデータ取得のための関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	自分状態データへのポインタ取得
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	ZUKAN_WORK	ずかんワークへのポインタ
 */
//----------------------------------------------------------
ZUKAN_WORK * SaveData_GetZukanWork(SAVEDATA * sv)
{
	ZUKAN_WORK * zs;
	zs = SaveData_Get(sv, GMDATA_ID_ZUKANWORK);
	return zs;
}

//============================================================================================
//============================================================================================
// アンノーン　ウミウシ　ミノムシ　の見つけた順番せってい
static void set_debag_special_poke_see_no( ZUKAN_WORK * zw, int monsno )
{
	int i;
	
	// アンノーン　ウミウシ　ミノムシの順番の設定
	if( monsno == MONSNO_ANNOON ){
		for( i=0; i<POKEZUKAN_UNKNOWN_NUM; i++ ){
			SetZukanUnknownTurn( zw, i );
		}
	}else if( (monsno == MONSNO_MINOMUTTI) || (monsno == MONSNO_MINOMESU) ){
		for( i=ZUKAN_WORK_MINOMUSHI_FORM_NUM - 1; i>=0; i-- ){
			SetZukanMinomuttiTurn( zw, monsno, i );
		}
	}else if( (monsno == MONSNO_SIIUSI) || (monsno == MONSNO_SIIDORUGO) ){
		for( i=ZUKAN_WORK_UMIUSHI_FORM_NUM - 1; i>=0; i-- ){
			SetZukanSiiusiTurn( zw, monsno, i );
		}
	}else if( (monsno == MONSNO_DEOKISISU) ){
		for( i=ZUKAN_WORK_DEOKISISU_FORM_NUM - 1; i>=0; i-- ){
			setDEOKISISUFormNo( zw, i, ZUKAN_WORK_DEOKISISU_FORM_NUM-(i+1) );
		}
	}
	
}

// 性別設定
static void set_debug_poke_sex( ZUKAN_WORK * zw, int monsno )
{
	int sex = PokePersonalParaGet( monsno, ID_PER_sex );
	
	if( sex == MONS_MALE ){
		// 性別設定
		set_sex_bit( zw, PARA_MALE, ZUKAN_WORK_SEX_FIRST, monsno );
		return;
	}
	if( sex == MONS_FEMALE ){
		// 性別設定
		set_sex_bit( zw, PARA_FEMALE, ZUKAN_WORK_SEX_FIRST, monsno );
		return;
	}
	if( sex == MONS_UNKNOWN ){
		// 性別設定
		set_sex_bit( zw, PARA_UNK, ZUKAN_WORK_SEX_FIRST, monsno );
		return;
	}

	// 性別設定
	if( monsno % 2 ){
		set_sex_bit( zw, PARA_MALE, ZUKAN_WORK_SEX_FIRST, monsno );
		set_sex_bit( zw, PARA_FEMALE, ZUKAN_WORK_SEX_SECOND, monsno );
	}else{
		set_sex_bit( zw, PARA_FEMALE, ZUKAN_WORK_SEX_FIRST, monsno );
		set_sex_bit( zw, PARA_MALE, ZUKAN_WORK_SEX_SECOND, monsno );
	}
}

//----------------------------------------------------------
/**
 * @brief	デバッグ用：ずかんデータ生成
 * @param	zw			ずかんワークへのポインタ
 * @param	option
 */
//----------------------------------------------------------
extern void Debug_ZukanWork_Make(ZUKAN_WORK * zw, int start, int end, BOOL see_flg)
{
	int i;
	zukan_incorrect(zw);

	GF_ASSERT( start > 0 );
	GF_ASSERT( end <= MONSNO_END );
	
	for (i = start; i <= end; i++) {
		if( see_flg == TRUE ){
			set_see_bit(zw, i);
		}else{
		
			set_get_bit(zw, i);
			set_see_bit(zw, i);

			// 外国図鑑設定
			SetZukanTextVersionUp(zw, i, LANG_JAPAN);
			SetZukanTextVersionUp(zw, i, LANG_ENGLISH);
			SetZukanTextVersionUp(zw, i, LANG_FRANCE);
			SetZukanTextVersionUp(zw, i, LANG_ITALY);
			SetZukanTextVersionUp(zw, i, LANG_GERMANY);
			SetZukanTextVersionUp(zw, i, LANG_SPAIN);
		}

		// 個性乱数設定
		SetZukanRandom( zw, i, 0 );

		// 特殊見つけた順番設定
		set_debag_special_poke_see_no( zw, i );

		// 性別	
		set_debug_poke_sex( zw, i );
	}

	// グラフィックバージョンアップ
	ZukanWork_SetGraphicVersionUpFlag(zw);
	ZukanWork_SetTextVersionUpMasterFlag(zw);
}

//----------------------------------------------------------------------------
/**
 *	@brief	デオキシスバックアップ
 *
 *	@param	zw	図鑑ワーク
 */
//-----------------------------------------------------------------------------
void Debug_ZukanWork_DeokisisuBuckUp( ZUKAN_WORK * zw )
{
	// デオキシスフォルムIDバッファ初期化
	InitDeokisisuFormNo( zw );
		
	// デオキシス保持しているかチェック
	if( ZukanWork_GetPokeSeeFlag( zw, MONSNO_DEOKISISU ) == TRUE ){
		// フォルムナンバー０でセーブ
		setDEOKISISUFormNo( zw, 0, 0 );
	}
}


// 外部参照インデックスを作る時のみ有効(ゲーム中は無効)
#ifdef CREATE_INDEX
void *Index_Get_Zukan_Offset(ZUKAN_WORK *zw){ return &zw->zukan_get; }
void *Index_Get_Zenkoku_Zukan_Offset(ZUKAN_WORK *zw){ return &zw->zenkoku_flag; }
void *Index_Get_Get_Flag_Offset(ZUKAN_WORK *zw){ return &zw->get_flag; }
void *Index_Get_See_Flag_Offset(ZUKAN_WORK *zw){ return &zw->see_flag; }
void *Index_Get_Sex_Flag_Offset(ZUKAN_WORK *zw){ return &zw->sex_flag; }
#endif




//------------------------------------------------------------------
/**
 * 全ポケモンの、捕まえた順フォルムナンバーを返す
 *
 * @param   zw			
 * @param   monsno		
 * @param   count		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 ZukanWork_GetPokeForm( const ZUKAN_WORK* zw, int monsno, int count )
{
	OS_TPrintf("monsno:%d\n", monsno);
	switch( monsno ){
	case MONSNO_ANNOON:
		OS_TPrintf("  Annoon\n");
		if( count < ZukanWork_GetPokeAnoonSeeNum(zw) )
		{
			OS_TPrintf("   CheckForm\n");
			return ZukanWork_GetPokeAnoonForm( zw, count );
		}
		break;

	case MONSNO_SIIUSI:
		if( count < ZukanWork_GetPokeSiiusiSeeNum(zw) )
		{
			return ZukanWork_GetPokeSiiusiForm( zw, count );
		}
		break;

	case MONSNO_SIIDORUGO:
		if( count < ZukanWork_GetPokeSiidorugoSeeNum(zw) )
		{
			return ZukanWork_GetPokeSiidorugoForm( zw, count );
		}
		break;

	case MONSNO_MINOMUTTI:
		if( count < ZukanWork_GetPokeMinomuttiSeeNum(zw) )
		{
			return ZukanWork_GetPokeMinomuttiForm( zw, count );
		}
		break;

	case MONSNO_MINOMESU:
		if( count < ZukanWork_GetPokeMinomesuSeeNum(zw) )
		{
			return ZukanWork_GetPokeMinomesuForm( zw, count );
		}
		break;

	case MONSNO_DEOKISISU:
		if( count < ZukanWork_GetPokeDeokisisuFormSeeNum(zw) )
		{
			return ZukanWork_GetPokeDeokisisuForm( zw, count );
		}
		break;

	}

	return 0;

}

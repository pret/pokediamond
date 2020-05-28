//============================================================================================
/**
 * @file	pm_str.c
 * @brief	文字列関連処理
 * @author	Hiroyuki Nakamura
 * @date	2004.11.02
 *
 *	ポケモンＡＧＢから移植
 *
 */
//============================================================================================
#define PM_STR_H_GLOBAL

#include "common.h"
//#include "fntsys.h"

#include "system/pm_str.h"


//============================================================================================
//	シンボル定義
//============================================================================================
#define	TEMP_BUF_MAX	( 16 )
#define	MSG_EXP_BUF_MAX	( 64 )


//============================================================================================
//	プロトタイプ宣言
//============================================================================================


//============================================================================================
//	グローバル変数
//============================================================================================
static const STRCODE* TmpBufAdrs[TEMP_BUF_MAX] = {};
STRCODE	MsgExpandBuffer[MSG_EXP_BUF_MAX] = {};

static const STRCODE n_ch[] = {n0_,n1_,n2_,n3_,n4_,n5_,n6_,n7_,n8_,n9_,A__,B__,C__,D__,E__,F__};

static const int n_max[] = 
{
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000,
	10000000,
	100000000,
	1000000000,
};


//============================================================================================
//	文字列操作
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 文字列コピー
 *
 * @param	to_str		コピー先バッファ
 * @param	from_str	文字列データ
 *
 * @return	バッファにコピーしたデータ最後のEOM_へのポインタ
 *
 *	データがない(文字列データ先頭がEOM_だった)場合、
 *	EOM_をバッファ先頭に書きこみ、そこへのポインタを返す
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strcpy( STRCODE* to_str, const STRCODE* from_str )
{
	while( *from_str != EOM_ ){
		*to_str = *from_str;
		to_str++;
		from_str++;
	}
	*to_str = EOM_;
	return to_str;
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列コピー（文字数指定）
 *
 * @param	to_str		コピー先バッファ
 * @param	from_str	文字列データ
 * @param	len			コピーする文字数
 *
 * @return	「コピー先バッファ + コピーする文字数」へのポインタ
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strncpy( STRCODE* to_str, const STRCODE* from_str, u32 len )
{
	u32	i;

	for( i=0; i<len; i++ ){
		to_str[i] = from_str[i];
	}
	return &to_str[len];
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列連結
 *
 * @param	to_str		連結されるデータ（ram上にあること！！）
 * @param	from_str	連結するデータ
 *
 * @return	連結後のバッファ上のデータ末のEOM_へのポインタ
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strcat( STRCODE* to_str, const STRCODE* from_str )
{
	while( *to_str != EOM_ ){
		to_str++;
	}
	return PM_strcpy( to_str, from_str );
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列連結（文字数指定）
 *
 * @param	to_str		連結されるデータ（ram上にあること！！）
 * @param	from_str	連結するデータ
 * @param	len			連結する文字数
 *
 * @return	連結後のバッファ上のデータ末へのポインタを返す
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strncat( STRCODE* to_str, const STRCODE* from_str, u32 len )
{
	while( *to_str != EOM_ ){
		to_str++;
	}
	return PM_strncpy( to_str, from_str, len );
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列長取得
 *
 * @param	str		対象文字列へのポインタ
 *
 * @return	対象文字列の長さ（EOM_までの文字数）を返す
 */
//--------------------------------------------------------------------------------------------
u32 PM_strlen( const STRCODE* str )
{
	u32 len = 0;

	while( str[len] != EOM_ ){
		len++;
	}
	return len;
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列比較
 *
 * @param	s		対象文字列へのポインタ
 * @param	t		対象文字列へのポインタ
 *
 * @retval	"0 = 一致"
 * @retval	"1 = 不一致"
 *
 * @li	Ｃ標準関数と違い長さの比較はしていない
 */
//--------------------------------------------------------------------------------------------
BOOL PM_strcmp( const STRCODE* s, const STRCODE* t )
{
	while( *s == *t ){
		if( *s == EOM_ ){ return 0; }
		s++;
		t++;
	}
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列比較（文字数指定）
 *
 * @param	s		対象文字列へのポインタ
 * @param	t		対象文字列へのポインタ
 * @param	n		比較する文字数
 *
 * @retval	"0 = 一致"
 * @retval	"1 = 不一致"
 *
 * @li	Ｃ標準関数と違い長さの比較はしていない
 */
//--------------------------------------------------------------------------------------------
BOOL PM_strncmp( const STRCODE* s, const STRCODE* t, u32 n )
{
	while( *s == *t ){
		if( n == 0 ){ return 0; }
		if( *s == EOM_ && *t == EOM_ ){ return 0; }
		n--;
		s++;
		t++;
	}
	return 1;
}

//--------------------------------------------------------------------------------------------
/**	
 * 文字列入力チェック
 *
 * @param	str		対象文字列へのポインタ
 * @param	n		チェックする文字数
 *
 * 
 * @retval	"1 = 入力あり"
 * @retval	"0 = 入力なし"
 *
 * @li	指定されたバッファに空白とEOM以外のコードが含まれているかチェック
 */
//--------------------------------------------------------------------------------------------
BOOL PM_strnchk( STRCODE* str, u32 n )
{
	u32	i;

	for( i=0; i<n; i++ ){
		if( (str[i] != spc_) && (str[i] != EOM_) ){
			return 1;
		}
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列バッファを指定文字コードでクリア
 *
 * @param	str		文字列バッファ
 * @param	code	文字コード
 * @param	len		クリアする文字数
 *
 * @return	EOM_ アドレス
*/
//--------------------------------------------------------------------------------------------
STRCODE* PM_strclear( STRCODE* str, STRCODE code, u32 len )
{
	u32 i;

	for( i=0; i<len; i++ ){
		str[i] = code;
	}
//	str[i] = EOM_;	//文字数+1の場所に書き込みに行くのでコメントアウト
					//05.11.18 by iwasawa

	return &str[i];
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列バッファをEOM_コードでクリア
 *
 * @param	str		文字列バッファ
 * @param	len		クリアする文字数
 *
 * @return	クリア終端のEOM_ アドレス
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strclearEOM_( STRCODE* str, u32 len )
{
	return PM_strclear( str, EOM_, len );
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列コピー後、指定文字数に満たない分だけ、指定文字コードでクリア
 *
 * @param	to		コピー先文字列バッファ
 * @param	from	コピー元文字列
 * @param	code	クリア文字コード
 * @param	len		全体の文字数
 *
 * @return	EOM_ アドレス
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strcpy_clear( STRCODE* to, const STRCODE* from, STRCODE code, u32 len )
{
	while( *from != EOM_ ){
		if( len == 0 ){ break; }
		*to = *from;
		to++;
		from++;
		len--;
	}
	if( len != 0 ){
		while( len-- ){
			*to = code;
			to++;
		}
	}
	*to = EOM_;

	return to;
}


//============================================================================================
//	数値→文字列
//============================================================================================
#define NUM_STR(n)	( n>=10 ? hate_ : n_ch[n] )		///<10進表示文字取得
#define HEX_STR(n)	( n>=16 ? hate_ : n_ch[n] )		///<16進表示文字取得

//--------------------------------------------------------------------------------------------
/**
 * 数値を文字列に変換（１０進）
 *
 * @param	buf		文字列展開場所
 * @param	num		数値
 * @param	type	変換方式
 * @param	keta	桁数
 *
 * @return	数値の後ろに書きこんだEOM_へのポインタ
 *
 * @li	type = NUM_MODE_LEFT	左詰
 * @li	type = NUM_MODE_SPACE	右詰、足りない部分は空白
 * @li	type = NUM_MODE_ZERO	右詰、足りない部分は数字のゼロ
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_NumMsgSet( STRCODE* buf, s32 num, u32 type, u32 keta )
{
	u32	i;
	u32 num_f;
	u32	num_i;

	for( i=n_max[keta-1]; i>0; i/=10 ){
		num_i = (u16)( num / i );
		num_f = (u32)( num - ( i * num_i ) );
		if( type == NUM_MODE_ZERO ){
			*buf = (u16)NUM_STR( num_i );
			buf++;
		}else if( num_i != 0 || i==1 ){
			type = NUM_MODE_ZERO;
			*buf = (u16)NUM_STR( num_i );
			buf++;
		}else if( type == NUM_MODE_SPACE ){
			*buf = spc_;
			buf++;
		}
		num = num_f;
	}
	*buf = EOM_;

	return buf;
}

//--------------------------------------------------------------------------------------------
/**
 * 数値を文字列に変換（１０進、マイナスはなし）
 *
 * @param	buf		文字列展開場所
 * @param	num		数値
 * @param	type	変換方式
 * @param	keta	桁数
 *
 * @return	数値の後ろに書きこんだEOM_へのポインタ
 *
 * @li	type = NUM_MODE_LEFT	左詰
 * @li	type = NUM_MODE_SPACE	右詰、足りない部分は空白
 * @li	type = NUM_MODE_ZERO	右詰、足りない部分は数字のゼロ
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_NumMsgSetUnsigned( STRCODE* buf, u32 num, u32 type, u32 keta )
{
	u32	i;
	u32 num_f;
	u16	num_i;

	for( i=n_max[keta-1]; i>0; i/=10 ){
		num_i = (u16)( num / i );
		num_f = (u32)( num - ( i * num_i ) );
		if( type == NUM_MODE_ZERO ){
			*buf = (u16)NUM_STR( num_i );
			buf++;
		}else if( num_i != 0 || i==1 ){
			type = NUM_MODE_ZERO;
			*buf = (u16)NUM_STR( num_i );
			buf++;
		}else if( type == NUM_MODE_SPACE ){
			*buf = spc_;
			buf++;
		}
		num = num_f;
	}
	*buf = EOM_;

	return buf;
}

//--------------------------------------------------------------------------------------------
/**
 * 数値を文字列に変換（１６進）
 *
 * @param	buf		文字列展開場所
 * @param	num		数値
 * @param	type	変換方式
 * @param	keta	桁数
 *
 * @return	数値の後ろに書きこんだEOM_へのポインタ
 *
 * @li	type = NUM_MODE_LEFT	左詰
 * @li	type = NUM_MODE_SPACE	右詰、足りない部分は空白
 * @li	type = NUM_MODE_ZERO	右詰、足りない部分は数字のゼロ
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_HexNumMsgSet( STRCODE* buf, s32 num, u32 type, u32 keta )
{
	u32	i,max;
	u32	num_i,num_f;

	max = 1;
	for( i=1; i<keta; i++ ){
		max *= 16;
	}

	for( i=max; i>0; i/=16 ){
		num_i = num / i;
		num_f = num % i;
		if( type == NUM_MODE_ZERO ){
			*buf = (STRCODE)HEX_STR( num_i );
			buf++;
		}else if( num_i != 0 || i==1 ){
			type = NUM_MODE_ZERO;
			*buf = (STRCODE)HEX_STR( num_i );
			buf++;
		}else if( type == NUM_MODE_SPACE ){
			*buf = spc_;
			buf++;
		}
		num = num_f;
	}
	*buf = EOM_;

	return buf;
}


//============================================================================================
//	メッセージ展開ルーチン
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * メッセージ展開処理（S_MSG_込み）
 *
 * @param	buf		展開先
 * @param	data	元メッセージ
 *
 * @return	EOM_のアドレス
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_MsgExpand( STRCODE* buf, const STRCODE* data )
{
	STRCODE	c;

	while(1){
		c = *data;
		data++;
		switch( c ){
		case EOM_:
			*buf = EOM_;
			return buf;
/*
		case I_MSG_:
			buf = PM_MsgExpand( buf, GetIndirectString( *data ) );
			data++;
			break;
*/
		case S_MSG_:
			buf = PM_MsgExpand( buf, TmpBufAdrs[*data] );
			data++;
			break;
/*
		case CTRL_:
			*(buf++) = c;
			c = *data; data++;
			*(buf++) = c;
			switch ( c ) {
			// パラメータなし
			case C_FNML_:
			case C_TRGWAIT_:
			case C_CLR_:
			case C_LANG_JP:
			case C_LANG_DEF:
			case C_MUSPAUSE_:
			case C_MUSCONTINUE_:
				break;
			// パラメータ3つ
			case C_ACOL_:
				*(buf++) = *(data++);
				*(buf++) = *(data++);
				*(buf++) = *(data++);
				break;
			// パラメータ2つ
			case C_MUSPLAY_:
				*(buf++) = *(data++);
				*(buf++) = *(data++);
				break;
			// 通常はパラメータ1つ
			default:
				*(buf++) = *(data++);
				break;
			}
			break;
*/
		default:
			*buf = c;
			buf++;
		}
	}
	return NULL;
}


//============================================================================================
//	S_MSG_処理
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * S_MSG_初期化処理
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MsgExp_Init(void)
{
	MI_CpuFill32( (void *)TmpBufAdrs, NULL, TEMP_BUF_MAX * 4 );
}

//--------------------------------------------------------------------------------------------
/**
 * S_MSG_設定処理
 *
 * @param	id		ID
 * @param	str		セットする文字列
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MsgExp_AdrsSet( u32 id, const STRCODE* str )
{
	if( id >= TEMP_BUF_MAX ){
#ifdef	OSP_ERR_MSGEXP_ADRS_SET		// S_MSG_の設定失敗
		OS_Printf( "Error : MsgExp_AdrsSet(...) / id >= TEMP_BUF_MAX\n" );
#endif	// OSP_ERR_MSGEXP_ADRS_SET
		return;
	}
	TmpBufAdrs[id] = str;
}











//============================================================================================
//	str関連の処理
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 数値を文字列に変換 ( str )
 *
 * @param	str		文字列格納場所
 * @param	num		変換する数値
 * @param	keta	桁
 *
 * @return	none
 *
 * @li	ファイル名の作成などに使用する関数。
 * @li	keta = 0  : 左詰め
 * @li	keta != 0 : 0で埋める
 */
//--------------------------------------------------------------------------------------------
void StrNumSet( char * str, u32 num, u32 keta )
{
	char zero[10];
	u32	num_i;
	u32	i;

	if( keta == 0 ){
		sprintf( str, "%d", num );
	}else{
		memset( zero, '\0', 10 );
		for( i=n_max[keta-1]; i>0; i/=10 ){
			num_i = num / i;
			sprintf( zero, "%d", num_i );
			strcat( str, zero );
			num = num - ( i * num_i );
		}
	}
}












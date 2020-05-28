//============================================================================================
/**
 * @file	strbuf.c
 * @brief	汎用文字列バッファ型オブジェクト
 * @author	taya
 * @date	2005.11.02
 */
//============================================================================================
#include <stdlib.h>
#include <string.h>
#include "gflib/assert.h"
#include "gflib/msg_print.h"
#include "gflib/strcode.h"
#include "gflib/fntsys.h"
#include "gflib/heapsys.h"

#include "gflib/strbuf_family.h"


//--------------------------------------------------------------
/**
 * 定数                                                      
 */
//--------------------------------------------------------------
#define STRBUF_MAGIC_NUMBER		(0xb6f8d2ec)
#define STRBUF_MAX_SIZE			(1024)

//--------------------------------------------------------------
/**
 * 文字列バッファオブジェクト型定義
 */
//--------------------------------------------------------------
struct _STRBUF {
	u16  size;			///< 配列サイズ
	u16  strlen;		///< 文字列長（EOMを含まない）
	u32  magicNumber;	///< 正常に初期化済みであることをチェックするためのナンバー

	STRCODE  buffer[1];	///< 配列本体
};

/** ヘッダサイズ */
#define STRBUF_HEADER_SIZE	(sizeof(STRBUF) - sizeof(STRCODE))

//--------------------------------------------------------------
/**
 * 状態異常チェックマクロ
 */
//--------------------------------------------------------------
#define  STRBUF_CHECK_STATE(pbuf)	{\
	GF_ASSERT((pbuf)!=NULL)	\
	GF_ASSERT((pbuf)->magicNumber == STRBUF_MAGIC_NUMBER);	\
}



//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * 文字列バッファオブジェクト作成
 *
 * @param   size		格納できる文字数（EOMを含む）
 * @param   heapID		作成先ヒープID
 *
 * @retval  STRBUF*		オブジェクトへのポインタ
 */
//------------------------------------------------------------------
STRBUF* STRBUF_Create( u32 size, u32 heapID )
{
	STRBUF* strbuf;

	strbuf = sys_AllocMemory( heapID, STRBUF_HEADER_SIZE + sizeof(STRCODE)*size );

	if( strbuf )
	{
		strbuf->magicNumber = STRBUF_MAGIC_NUMBER;
		strbuf->size = size;
		strbuf->strlen = 0;
		strbuf->buffer[0] = EOM_;
	}

	return strbuf;
}
//------------------------------------------------------------------
/**
 * 文字列バッファオブジェクト削除
 *
 * @param   strbuf		オブジェクトへのポインタ
 *
 */
//------------------------------------------------------------------
void STRBUF_Delete( STRBUF* strbuf )
{
	STRBUF_CHECK_STATE(strbuf);

	// Free 直後に同じアドレスで呼び出されるとMagicNumberがそのまま残ってたりするので
	strbuf->magicNumber = STRBUF_MAGIC_NUMBER+1;

	sys_FreeMemoryEz( strbuf );
}
//------------------------------------------------------------------
/**
 * 内容をクリアして空文字列にする
 * （Create 直後はクリアされているので呼ぶ必要は無い）
 *
 * @param   strbuf		オブジェクトへのポインタ
 *
 */
//------------------------------------------------------------------
void STRBUF_Clear( STRBUF* strbuf )
{
	STRBUF_CHECK_STATE(strbuf);

	strbuf->strlen = 0;
	strbuf->buffer[0] = EOM_;
}

//------------------------------------------------------------------
/**
 * バッファ間の文字列コピー
 *
 * @param   dst		コピー先バッファオブジェクト
 * @param   src		コピー元バッファオブジェクト
 *
 */
//------------------------------------------------------------------
void STRBUF_Copy( STRBUF* dst, const STRBUF* src )
{
	STRBUF_CHECK_STATE( dst );
	STRBUF_CHECK_STATE( src );

	if( dst->size > src->strlen )
	{
		memcpy( dst->buffer, src->buffer, (src->strlen+1)*sizeof(STRCODE) );
		dst->strlen = src->strlen;
		return;
	}

	GF_ASSERT_MSG(0, "STRBUF overflow : dstsize=%d,  srclen=%d", dst->size, src->strlen);
}

//------------------------------------------------------------------
/**
 * 同じ内容のバッファを複製する
 *
 * @param   strbuf		複製元のバッファオブジェクト
 *
 * @retval  STRBUF*		複製されたバッファオブジェクト
 */
//------------------------------------------------------------------
STRBUF* STRBUF_CreateBufferCopy( const STRBUF* origin, u32 heapID )
{
	STRBUF* copy;

	STRBUF_CHECK_STATE( origin );

	copy = STRBUF_Create( origin->strlen+1, heapID );
	if( copy )
	{
		STRBUF_Copy( copy, origin );
	}

	return copy;
}

//------------------------------------------------------------------
/**
 * バッファに数字をセット
 *
 * @param   dst			[out] バッファオブジェクトへのポインタ
 * @param   number		数値
 * @param   keta		最大桁数
 * @param   dispType	表示タイプ
 * @param   codeType	文字コードタイプ
 *
 */
//------------------------------------------------------------------
void STRBUF_SetNumber( STRBUF* dst, int number, u32 keta, NUMBER_DISPTYPE dispType, NUMBER_CODETYPE codeType )
{
	static const u32 n_max[] = 
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
	int minus;
    static const STRCODE sc_zen[] = {n0_,n1_,n2_,n3_,n4_,n5_,n6_,n7_,n8_,n9_};
    static const STRCODE sc_han[] = {h_n0_,h_n1_,h_n2_,h_n3_,h_n4_,h_n5_,h_n6_,h_n7_,h_n8_,h_n9_};


	STRBUF_CHECK_STATE( dst );

	minus = (number < 0);

	if( dst->size > (keta+minus) )
	{
		u32  num_f, num_i, i;
		const STRCODE* sctbl = (codeType==NUMBER_CODETYPE_ZENKAKU)? sc_zen : sc_han;

		STRBUF_Clear(dst);

		if(minus)
		{
			number *= -1;
			dst->buffer[dst->strlen++] = (codeType==NUMBER_CODETYPE_ZENKAKU)? bou_ : h_bou_;
		}


		for(i=n_max[keta-1]; i>0; i/=10)
		{
			num_i = (u16)( number / i );
			num_f = (u32)( number - ( i * num_i ) );

			if( dispType == NUMBER_DISPTYPE_ZERO )
			{
				dst->buffer[dst->strlen++] = (num_i<10)? sctbl[num_i] : hate_;
			}
			else if( num_i != 0 || i==1 )
			{
				dispType = NUMBER_DISPTYPE_ZERO;
				dst->buffer[dst->strlen++] = (num_i<10)? sctbl[num_i] : hate_;
			}
			else if( dispType == NUMBER_DISPTYPE_SPACE )
			{
				dst->buffer[dst->strlen++] = (codeType==NUMBER_CODETYPE_ZENKAKU)? spc_ : h_spc_;
			}

			number = num_f;
		}

		dst->buffer[dst->strlen] = EOM_;
		return;
	}

//	GF_ASSERT_MSG(0, "STRBUF overflow!");
	GF_ASSERT_MSG(0, "STRBUF overflow: bufsize=%d, keta=%d", dst->size, keta);
}

//------------------------------------------------------------------
/**
 * 文字数字を数字に変換する  18けた対応  この関数は文字コードに左右される
 *
 * @param   src			変換したい数字が入っているバッファ
 * @param   pbFlag      変換できたかどうか
 * @return  成功した場合変換数字
 *
 */
//------------------------------------------------------------------
u64 STRBUF_GetNumber( const STRBUF* src, BOOL* pbFlag  )
{
    u64 num = 0,add = 0, digit = 1;
    int i;
    STRCODE code;
    STRCODE zenNum = n0_;
    STRCODE hanNum = h_n0_;

    if(src->strlen > 18){
        return FALSE;  // 変換失敗
    }
    for(i = (src->strlen - 1); i >= 0; i--){
        code = src->buffer[i];
        num = code - zenNum;
        if(num >= 10){  // 全角の０～９でない
            num = code - hanNum;
            if(num >= 10){  // 半角の０～９でない
                *pbFlag = FALSE;
                return add;  // 変換失敗
            }
        }
        num = num * digit;
        add += num;
        digit *= 10;  // 桁アップ
    }
    *pbFlag = TRUE;
    return add;  // 変換成功
}

//------------------------------------------------------------------
/**
 * 文字列を比較する
 *
 * @param   str1		文字列１
 * @param   str2		文字列２
 *
 * @retval  int			"0 = 一致"
 * @retval  int			"1 = 不一致"
 */
//------------------------------------------------------------------
int STRBUF_Compare( const STRBUF* str1, const STRBUF* str2 )
{
	STRBUF_CHECK_STATE( str1 );
	STRBUF_CHECK_STATE( str2 );

	{
		int i;


		for(i=0; str1->buffer[i] == str2->buffer[i]; i++)
		{
			if( str1->buffer[i] == EOM_ )
			{
				return 0;
			}
		}

		return 1;
	}
}

//------------------------------------------------------------------
/**
 * 格納されている文字数を返す
 *
 * @param   strbuf		文字列バッファオブジェクト
 *
 * @retval  u32		文字数
 */
//------------------------------------------------------------------
u32 STRBUF_GetLen( const STRBUF* str )
{
	STRBUF_CHECK_STATE( str );

	return str->strlen;
}


//------------------------------------------------------------------
/**
 * 格納されている文字列が何行あるかを調べる
 *
 * @param   strbuf		文字列バッファオブジェクト
 *
 * @retval  u32		文字列の行数
 */
//------------------------------------------------------------------
u32 STRBUF_GetLines( const STRBUF* str )
{
	STRBUF_CHECK_STATE( str );

	{
		int i;
		u32 cnt;

		for(i=0, cnt=1; i<str->strlen; i++)
		{
			if( str->buffer[i] == CR_ )
			{
				cnt++;
			}
		}
		return cnt;
	}
}

//------------------------------------------------------------------
/**
 * 文字列の、指定行のみを別バッファへコピーする
 *
 * @param   dst		コピー先バッファ
 * @param   src		コピー元バッファ
 * @param   line	行番号（0 origin）
 *
 */
//------------------------------------------------------------------
void STRBUF_CopyLine( STRBUF* dst, const STRBUF* src, u32 line )
{
	STRBUF_CHECK_STATE( src );
	STRBUF_CHECK_STATE( dst );

	{
		int i = 0;

		if( line )
		{
			for(i=0; i<src->strlen; i++)
			{
				if( src->buffer[i] == CR_ )
				{
					if( --line == 0 )
					{
						i++;
						break;
					}
				}
			}
		}

		STRBUF_Clear( dst );
		for( ; i<src->strlen; i++)
		{
			if( src->buffer[i] == CR_ )
			{
				break;
			}
			STRBUF_AddChar( dst, src->buffer[i] );
		}
	}
}


//==============================================================================================
// 生の文字配列を取り扱う関数群
// これらを利用できるモジュールは出来る限り限定する
//==============================================================================================

//------------------------------------------------------------------
/**
 * 生の文字列（EOM終端）をバッファオブジェクトにセットする
 *
 * @param   strbuf		[out] バッファオブジェクトへのポインタ
 * @param   sz			[in]  EOM で終わる文字配列
 *
 */
//------------------------------------------------------------------
void STRBUF_SetStringCode( STRBUF* strbuf, const STRCODE* sz )
{
	STRBUF_CHECK_STATE(strbuf);

	strbuf->strlen = 0;
	while( *sz != EOM_ )
	{
		if( strbuf->strlen >= (strbuf->size-1) )
		{
			GF_ASSERT_MSG( 0, "STRBUF overflow: busize=%d", strbuf->size);
			break;
		}
		strbuf->buffer[ strbuf->strlen++ ] = *sz++;
	}

	strbuf->buffer[strbuf->strlen] = EOM_;
}
//------------------------------------------------------------------
/**
 * 生の文字列（長さ指定）をバッファオブジェクトにセットする
 *
 * @param   strbuf		[out] バッファオブジェクトへのポインタ
 * @param   str			[in]  文字配列の先頭ポインタ
 * @param   len			[in]  セットする文字数（EOMを含む）
 *
 */
//------------------------------------------------------------------
void STRBUF_SetStringCodeOrderLength( STRBUF* strbuf, const STRCODE* str, u32 len )
{
	STRBUF_CHECK_STATE(strbuf);

	if( len <= strbuf->size )
	{
		u32 i;

		memcpy( strbuf->buffer, str, len*sizeof(STRCODE) );

		for(i=0; i<len; i++)
		{
			if(strbuf->buffer[i] == EOM_)
			{
				break;
			}
		}
		strbuf->strlen = i;

		// EOM付きじゃない文字列だったら付けておく
		if( i==len )
		{
			strbuf->buffer[len-1] = EOM_;
		}
		return;
	}

	GF_ASSERT_MSG(0, "STRBUF overflow: bufsize=%d, strlen=%d", strbuf->size, len);
}

//------------------------------------------------------------------
/**
 * バッファから生の文字配列をコピーする
 *
 * @param   strbuf		[in]  バッファオブジェクトへのポインタ
 * @param   ary			[out] コピー先配列
 * @param   arysize		[in]  コピー先配列の要素数
 *
 */
//------------------------------------------------------------------
void STRBUF_GetStringCode( const STRBUF* strbuf, STRCODE* ary, u32 arysize )
{
	STRBUF_CHECK_STATE(strbuf);

	if( (strbuf->strlen+1) <= arysize )
	{
		memcpy( ary, strbuf->buffer, (strbuf->strlen+1)*sizeof(STRCODE) );
		return;
	}

	GF_ASSERT_MSG(0, "STRBUF overflow: strlen=%d, arysize=%d", strbuf->strlen, arysize);
}
//------------------------------------------------------------------
/**
 * バッファオブジェクトが内包する文字配列のアドレスを返す
 * ※この関数を呼び出す箇所は超限定。たぶん文字出力系のみ。
 *
 * @param   strbuf				[in] バッファオブジェクトへのポインタ
 *
 * @retval  const STRCODE*		文字配列のアドレス
 */
//------------------------------------------------------------------
const STRCODE* STRBUF_GetStringCodePointer( const STRBUF* strbuf )
{
	STRBUF_CHECK_STATE(strbuf);

	return strbuf->buffer;
}


//==============================================================================================
// 文字列の連結操作を行う関数。【【 原則使用禁止 】】
// 使って良いのはローカライズを考慮した文字列処理モジュールのみ。
//==============================================================================================

//------------------------------------------------------------------
/**
 * 文字列連結
 *
 * @param   dst		連結されるバッファオブジェクト
 * @param   src		連結する文字列を持つバッファオブジェクト
 *
 */
//------------------------------------------------------------------
void STRBUF_AddStr( STRBUF* dst, const STRBUF* src )
{
	STRBUF_CHECK_STATE(dst);
	STRBUF_CHECK_STATE(src);

	if( (dst->strlen + src->strlen + 1) <= dst->size )
	{
		memcpy( &(dst->buffer[dst->strlen]), src->buffer, (src->strlen+1)*sizeof(STRCODE) );
		dst->strlen += src->strlen;
		return;
	}

	GF_ASSERT_MSG(0, "STRBUF overflow: bufsize=%d, src_len=%d, dst_len=%d", dst->size, src->strlen, dst->strlen);
}

//------------------------------------------------------------------
/**
 * １文字連結
 *
 * @param   dst			連結されるバッファオブジェクト
 * @param   code		連結する文字コード
 *
 */
//------------------------------------------------------------------
void STRBUF_AddChar( STRBUF* dst, STRCODE code )
{
	STRBUF_CHECK_STATE( dst );

	if( (dst->strlen + 1) < dst->size )
	{
		dst->buffer[dst->strlen++] = code;
		dst->buffer[dst->strlen] = EOM_;
		return;
	}

	GF_ASSERT_MSG(0, "STRBUF overflow: busize=%d", dst->size);
}

//==============================================================================================
// デバッグ用
//==============================================================================================
#ifdef PM_DEBUG

//------------------------------------------------------------------
/**
 * 指定されたポインタがSTRBUFとして有効なものであるかチェック
 *
 * @param   ptr		ポインタ
 *
 * @retval  BOOL	TRUEで有効である
 */
//------------------------------------------------------------------
BOOL STRBUF_CheckValid(const void* ptr)
{
	return ( (ptr!=NULL) && (((const STRBUF*)ptr)->magicNumber == STRBUF_MAGIC_NUMBER) );
}

//--------------------------------------------------------------------------------------------
/**
 * 数値を文字列に変換（１６進）デバッグ専用
 *
 * @param   dst			[out] バッファオブジェクトへのポインタ
 * @param   number		数値
 * @param   keta		最大桁数
 * @param   dispType	表示タイプ
 * @param   codeType	文字コードタイプ
 *
 * @return	none
 *
 * @li	type = NUMBER_DISPTYPE_LEFT		左詰
 * @li	type = NUMBER_DISPTYPE_SPACE	右詰、足りない部分は空白
 * @li	type = NUMBER_DISPTYPE_ZERO		右詰、足りない部分は数字のゼロ
 */
//--------------------------------------------------------------------------------------------
void STRBUF_SetHexNumber(	STRBUF* dst, int num, u32 keta,
							NUMBER_DISPTYPE dispType, NUMBER_CODETYPE codeType )
{
	u32	i,max;
	u32	num_i,num_f;

	u32 temp;
	
	static const STRCODE sc_zen[] = {n0_,n1_,n2_,n3_,n4_,n5_,n6_,n7_,n8_,n9_,
												A__,B__,C__,D__,E__,F__};
	static const STRCODE sc_han[] = {h_n0_,h_n1_,h_n2_,h_n3_,h_n4_,h_n5_,h_n6_,h_n7_,h_n8_,h_n9_,
												h_A__,h_B__,h_C__,h_D__,h_E__,h_F__};

	temp = num;
	if( dst->size > (keta) ){						
		const STRCODE* sctbl = (codeType==NUMBER_CODETYPE_ZENKAKU)? sc_zen : sc_han;

		STRBUF_Clear(dst);

		max = 1;
		for( i=1; i<keta; i++ ){
			max *= 16;
		}

		for( i=max; i>0; i/=16 ){
			num_i = temp / i;
			num_f = temp % i;
			if( dispType == NUMBER_DISPTYPE_ZERO ){
				dst->buffer[dst->strlen++] = ( num_i<16 )? sctbl[num_i] : hate_;
			}else if( num_i != 0 || i==1 ){
				dispType = NUMBER_DISPTYPE_ZERO;
				dst->buffer[dst->strlen++] = ( num_i<16 )? sctbl[num_i] : hate_;
			}else if( dispType == NUMBER_DISPTYPE_SPACE ){
				dst->buffer[dst->strlen++] = spc_;
			}
			temp = num_f;
		}
		dst->buffer[dst->strlen] = EOM_;

		return;
	}
	GF_ASSERT_MSG(0, "STRBUF overflow: bufsize=%d, keta=%d", dst->size, keta);
}

#endif

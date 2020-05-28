//============================================================================================
/**
 * @file	perapvoice.c
 * @brief
 * @date	2006.04.06
 */
//============================================================================================


#include "savedata/savedata.h"
#include "savedata/perapvoice.h"
#include "perapvoice_local.h"

#include "gflib/assert.h"
#include "gflib/heapsys.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	オウムポケモンの声データセーブワークの定義
 */
//----------------------------------------------------------
struct PERAPVOICE {
	BOOL exist_flag;
	s8 voicedata[PERAPVOICE_LENGTH];
};

//============================================================================================
//
//	セーブデータシステムが依存する関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ぺラップの声ワークのサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int PERAPVOICE_GetWorkSize(void)
{
	return sizeof(PERAPVOICE);
}

//----------------------------------------------------------
/**
 * @brief	ぺラップの声ワークの初期化
 * @param	pv		PERAPVOICEデータへのポインタ
 */
//----------------------------------------------------------
void PERAPVOICE_Init(PERAPVOICE * pv)
{
	MI_CpuClear32(pv, sizeof(PERAPVOICE));
	pv->exist_flag = FALSE;
}

//----------------------------------------------------------
/**
 * @brief	ぺラップの声ワークの初期化
 * @param	heapID		メモリ確保をおこなうヒープ指定
 * @return	PERAPVOICE	取得したワークへのポインタ
 */
//----------------------------------------------------------
PERAPVOICE * PERAPVOICE_AllocWork(int heapID)
{
	PERAPVOICE *pv = sys_AllocMemory(heapID, sizeof(PERAPVOICE));
	PERAPVOICE_Init(pv);
	return pv;
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ぺラップの声セーブデータの取得
 * @param	sv		セーブデータへのポインタ
 * @return	PERAPVOICEデータへのポインタ
 */
//----------------------------------------------------------
PERAPVOICE * SaveData_GetPerapVoice(SAVEDATA * sv)
{
	return (PERAPVOICE*)SaveData_Get(sv, GMDATA_ID_PERAPVOICE);
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	声データが存在するかどうかのチェック
 * @param	pv		声データへのポインタ
 * @return	BOOL	TRUE：存在する、FALSE：存在しない
 */
//----------------------------------------------------------
BOOL PERAPVOICE_GetExistFlag(const PERAPVOICE * pv)
{
	return pv->exist_flag;
}

//==============================================================================
/**
 * @brief   声データの存在フラグを落とす
 *
 * @param   pv		声データへのポインタ
 *
 * @retval  none		
 */
//==============================================================================
void PERAPVOICE_ClearExistFlag( PERAPVOICE * pv )
{
	pv->exist_flag = 0;
}

//----------------------------------------------------------
/**
 * @brief	声データの取得
 * @param	pv		声データへのポインタ
 * @return	声データへのポインタ
 */
//----------------------------------------------------------
const void * PERAPVOICE_GetVoiceData(const PERAPVOICE * pv)
{
	return pv->voicedata;
}

//==============================================================================
/**
 * $brief   声データの展開
 *
 * @param   des		展開先
 * @param   src		ペラップボイスのポインタ
 *
 * @retval  none		
 *
 * 06/04/15時点ではペラップボイスは4bit,2khz,1秒サンプリング=1k
 * このデータを8bitに伸ばして2kにして格納する
 */
//==============================================================================
void PERAPVOICE_ExpandVoiceData( s8 *des, const s8 *src )
{
	int i,count=0;
	s8 tmp;
	u8 dat;

	// 4bit1kbyteを8bit2kbyteに伸ばす
	for(i=0;i<PERAPVOICE_LENGTH;i++){
		dat = src[i]&0x0f;
		tmp = dat-8;
		
		des[count]   = tmp*16;

		dat = src[i]>>4;
		tmp = dat-8;
		des[count+1]   = tmp*16;


//		des[count  ] = src[i];
//		des[count+1] = src[i]>>4;
		count += 2;
	}
}

//----------------------------------------------------------
/**
 * @brief	声データのセット
 * @param	pv		声データへのポインタ
 * @param	src		セットするデータへのポインタ
 *
 * 06/04/15時点ではペラップボイスは8bit,2khz,1秒サンプリング=2k
 * このデータを4bitに縮めて1kにして格納する
 *
 */
//----------------------------------------------------------
void PERAPVOICE_SetVoiceData(PERAPVOICE * pv, const s8 * src)
{
	int i,count;
	s8 tmp;
	u8 dat;

	// 格納フラグを立てる
	pv->exist_flag = TRUE;

	// 2khz8bitを4bitにして格納
	count = 0;
	for(i=0;i<PERAPVOICE_LENGTH*2;i+=2){
		tmp = (src[i]/16);
		dat = tmp+8;
		pv->voicedata[count]   = dat;
//		pv->voicedata[count]  =  src[i];

		tmp = (src[i+1]/16);
		dat = tmp+8;

		pv->voicedata[count] |= (dat<<4);
//		pv->voicedata[count] |= (src[i+1]<<4);
		count++;
	}

//	MI_CpuCopy32(src, (void *)pv->voicedata, PERAPVOICE_LENGTH);
}

//==============================================================================
/**
 * $brief   声データのコピー
 *
 * @param   des		コピー先声データのポインタ
 * @param   src		コピー元声データのポインタ
 *
 * @retval  none	
 */
//==============================================================================
void PERAPVOICE_CopyData(PERAPVOICE * des, const PERAPVOICE * src)
{
	MI_CpuCopyFast(src, des,  sizeof(PERAPVOICE));
}

//===================================================================
/**
 * @file	agbdownload.c
 * @bfief	AGBカセットからのふしぎデータダウンロード
 * @author	Satoshi Mitsuhara
 * @date	06.06.09
 *
 * <pre>
 * ＡＧＢカセット側のメモリマップ
 *	0x08000000	プログラム＋データ
 *	     |
 *	0x08100000	転送データのサイズ(４バイト)
 *	0x08100010	ビーコン情報
 *	0x08100100	ふしぎなおくりものデータ開始
 *	     |
 *	0x081xxxxx	終了
 * </pre>
 *
 * $Id: agbdownload.c,v 1.3 2006/07/15 08:47:20 mitsuhara Exp $
 */
//===================================================================

#include "agbdownload.h"

// アクセス可能カートリッジのゲームコード
static u32 AgbCartridgeTable[] = {
#if 0
  // ※注意※
  // ここはダイヤモンド／パール用に変更されなければなりません！
  'ZP3J',  'ZP4J',  'ZP5J',  'ZP6J',  'ZP7J',
  'ZR3J',  'ZR4J',  'ZR5J',  'ZR6J',  'ZR7J',
#else
  'B5BJ', 'B5CJ', 'B5DJ', 'B5EJ', 'B5FJ',
  'B5GJ', 'B5HJ', 'B5IJ', 'B5JJ', 'B5KJ',
  'B5LJ', 'B5MJ', 'B5PJ', 'B5QJ', 'B5RJ',
  'B5SJ', 'B5TJ', 'B5UJ', 'B5VJ', 'B5WJ',
#endif
  0,
};


//------------------------------------------------------------------
/**
 * @brief	ふしぎデータを含むカセットか調査する
 * @param	NONE
 * @return	TRUE: ふしぎカセット   FALSE: なし
 */
//------------------------------------------------------------------
static BOOL CheckAgbCartridgeInitialCode(void)
{
  int i;
  u32 init_code = CTRDG_GetAgbGameCode();
  // AgbCartridgeTableはu32として扱っていてリトルエンディアンになってしまうから
  // そのつじつまあわせでinit_codeをひっくり返す
  init_code = (((init_code >>  0) & 255) << 24 |
	       ((init_code >>  8) & 255) << 16 |
	       ((init_code >> 16) & 255) <<  8 |
	       ((init_code >> 24) & 255) <<  0);

  for(i = 0; i < AgbCartridgeTable[i]; i++){
    if(AgbCartridgeTable[i] == init_code){
#ifdef DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("AGB配布カセットを認識しました [GAMECODE:%c%c%c%c]\n",
		 (init_code >> 24) & 255,
		 (init_code >> 16) & 255,
		 (init_code >>  8) & 255,
		 (init_code >>  0) & 255);
#endif
      return TRUE;
    }
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	ＡＧＢカセットのアクセス条件が整っているか調査
 * @param	NONE
 * @return	TRUE: アクセス可能   FALSE: なし
 */
//------------------------------------------------------------------
static BOOL IsExistAgbCartridge(void)
{
  // ＡＧＢカートリッジ初期化(OS_Initで処理されているはず？)
  CTRDG_Init();
  // ＡＧＢカートリッジが存在しなければFALSE
  if(CTRDG_IsAgbCartridge() == FALSE)
    return FALSE;
  // 任天堂以外のカセットならばFALSE
  if(CTRDG_GetAgbMakerCode() != AGB_MAKER_CODE)
    return FALSE;
  // 指定されたイニシャルコード以外はFALSE
  if(CheckAgbCartridgeInitialCode() == FALSE)
    return FALSE;
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	ＡＧＢカートリッジ内にあるデータのサイズを返す
 * @param	NONE
 * @return	サイズ(0ならばカートリッジが刺さっていない
 */
//------------------------------------------------------------------
int GetAgbCartridgeDataSize(void)
{
  u32 size;

  // カセットの条件をチェック
  if(IsExistAgbCartridge() == FALSE)
    return 0;

  CTRDG_Enable(TRUE);
  CTRDG_Read32((const u32 *)AGBMISSIONDATASIZE, &size);
  CTRDG_Enable(FALSE);
  
  return size;
}


//------------------------------------------------------------------
/**
 * @brief	ＡＧＢカートリッジ内にあるビーコンデータをコピー
 * @param	NONE
 * @return	TRUE: コピー成功  : FALSE: 失敗
 */
//------------------------------------------------------------------
BOOL GetAgbCartridgeBeaconData(void *dist, int size)
{
  BOOL flag;

  // カセットの条件をチェック
  if(IsExistAgbCartridge() == FALSE)
    return FALSE;

  // ゲームデータを指定領域にコピーする
  if(size == 0)
    return FALSE;

  CTRDG_Enable(TRUE);
  flag = (BOOL)CTRDG_CpuCopy16((const void *)AGBBEACONDATAPTR, dist, size);
  CTRDG_Enable(FALSE);

  // 最後にカートリッジ抜き判定を行う
  if(CTRDG_IsExisting() == FALSE)
    return FALSE;

  return flag;
}


//------------------------------------------------------------------
/**
 * @brief	ＡＧＢカートリッジからデータを読み出す
 * @param	NONE
 * @return	TRUE: 成功   FALSE: 失敗
 */
//------------------------------------------------------------------
BOOL ReadAgbCartridgeData(void *dist, int size)
{
  BOOL flag;

  // カセットの条件をチェック
  if(IsExistAgbCartridge() == FALSE)
    return FALSE;

  // ゲームデータを指定領域にコピーする
  if(size == 0)
    size = GetAgbCartridgeDataSize();
  CTRDG_Enable(TRUE);
  flag = (BOOL)CTRDG_CpuCopy16((const void *)AGBMISSIONDATAPTR, dist, size);
  CTRDG_Enable(FALSE);

  OS_TPrintf("AGBカセットに入ってるデータのサイズは%d [%08X\n", size, dist);

  
  // 最後にカートリッジ抜き判定を行う
  if(CTRDG_IsExisting() == FALSE)
    return FALSE;

  return flag;
}

/*  */

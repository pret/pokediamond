/*---------------------------------------------------------------------------*
  Project:  Wireless PassBy Library - include
  File:     wpbpokemon.h

  2005 Ambrella
 *---------------------------------------------------------------------------*/
#ifndef WPBPOKEMON_H_
#define WPBPOKEMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include <nitro/types.h>
#include <nitro/wm.h>

/*---------------------------------------------------------------------------*
    構造体定義
 *---------------------------------------------------------------------------*/

// ゲーム間共通情報
typedef struct WPBPokemonInfo {
	u32 version;        // ポケモンDSソフトとしてのID番号
	u32 tryTime;        // 今回すれ違うまでにかかった時間 (秒) (不明は -1)
	u32 tryCount;       // 現在までのすれ違い試行回数 (不明は -1)
	u32 successCount;   // 現在までのすれ違い成功回数 (不明は -1)
	u32 totalTime;      // 現在までの総すれ違い試行時間 (秒) (不明は -1)
	u16 gameName[128];  // ゲーム名 (UTF-16LE)
	u8  image[32*32/2]; // アイコンデータ
	u8  pltt[16*2];     // アイコンパレット
	u8  macAddress[WM_SIZE_BSSID]; // 自分のmacAddress
	u8  present;        // プレゼント
	u8  favoriteColor;  // お気に入りの色 ( 0 ～ 15 )
	u16 sex_birth;      // 性別、誕生日、年齢情報
	u16 nickName[ 10 ]; // ニックネーム (UTF16)
	u16 nickNameLength; // ニックネーム文字数( 0 ～ 10 )
	u16 comment[ 39 ];  // コメント (UTF16)
	u16 commentLength;  // コメント文字数( 0 ～ 39 )
} WPBPokemonInfo;

/*---------------------------------------------------------------------------*
    関数定義
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         WPB_ToPresentID

  Description:  ゲーム内のアイテムの番号を 0～255 の present IDに変換する。

  Arguments:    totalItems  - ゲーム内のアイテムの総数
                salt        - ゲームによって固有の、なるべく他のゲームと重複しない値 ( 1 - 255 )
                itemNo      - ゲーム内のアイテム番号 ( 0 - totalItems )

  Returns:      present ID。
 *---------------------------------------------------------------------------*/
u8 WPB_ToPresentID(u8 totalItems, u8 salt, u8 itemNo);

/*---------------------------------------------------------------------------*
  Name:         WPB_FromPresentID

  Description:  0～255 の present ID をゲーム内のアイテムの番号に変換する。

  Arguments:    totalItems  - ゲーム内のアイテムの総数
                salt        - ゲームによって固有の、なるべく他のゲームと重複しない値 ( 1 - 255 )
                presentID   - present ID ( 0 - 255 )

  Returns:      ゲーム内のアイテム番号 ( 0 - totalItems )
 *---------------------------------------------------------------------------*/
u8 WPB_FromPresentID(u8 totalItems, u8 salt, u8 presentID);

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* WPBPOKEMON_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/

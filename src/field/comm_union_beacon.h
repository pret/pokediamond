//=============================================================================
/**
 * @file	comm_union_beacon.h
 * @brief	ユニオンルームビーコン設定処理
 * @author	Akito Mori
 * @date    2005.12.10
 */
//=============================================================================

#ifndef	__COMM_UNION_BEACON_H__
#define	__COMM_UNION_BEACON_H__


#define UNION_PARENT_MODE_FREE			(  0 )
#define UNION_PARENT_MODE_OEKAKI_FREE	(  1 )
#define UNION_PARENT_MODE_RECORD_FREE	(  2 )
#define UNION_PARENT_MODE_GURUGURU_FREE	(  3 )
#define UNION_PARENT_MODE_BUSY			(  4 )
#define UNION_PARENT_MODE_CARDNOW		(  5 )
#define UNION_PARENT_MODE_BATTLENOW		(  6 )
#define UNION_PARENT_MODE_TRADENOW		(  7 )
#define UNION_PARENT_MODE_OEKAKINOW		(  8 )
#define UNION_PARENT_MODE_RECORDNOW		(  9 )
#define UNION_PARENT_MODE_GURUGURUNOW	( 10 )
#define UNION_PARENT_MODE_PARTY			( 11 )


#ifndef	__ASM_NO_DEF_	// ↓これ以降は、アセンブラでは無視


#include "system/pms_data.h"

// ビーコンに含まれるユニオンルーム用情報構造体
// この情報はWMBssDec.gameDataInfo.userGameInfoの中をキャストして参照する
// _GF_BSS_DATA_INFO.regulationBuffをまたもやキャストして使っている
// regulationBuffは戦闘用のレギュレーションなので、ユニオンではまったく使用していないから
typedef struct{
	u32 c_id[4];		// 子機のID			16
	u8  c_rom[4];		// 子機のROM		20
	u8  c_region[4];	// 子機の国コード	24
	u8  c_face[4];		// 子機の姿番号		28
	u8  mode;			// 親機の状態（フリー・おえかきでフリー・忙しい・こうかん・バトル）	29
	u8  nation;			// 住んでいる国   30
	u8	area;			// 住んでいる都市・場所 31
	u8  etc;			// 余り（もうこの１バイトだけ…）32 
}UNION_BEACON_STATE;


// ユニオン用ビーコン書き換え関数
extern void Union_BeaconChange( int flag );
extern void Union_PMSReWrite( PMS_DATA *pms );

extern u16 *UnionView_GetPalNo( u16 * table, int sex, int view_type );
extern int UnionView_GetCharaNo( int sex, int view_type );
extern u16 *UnionView_PalleteTableAlloc( int heapID );



#endif	__ASM_NO_DEF_


#endif
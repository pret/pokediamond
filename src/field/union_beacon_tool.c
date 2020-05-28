//=============================================================================
/**
 * @file	union_beacon_tool.c
 * @brief	ユニオンルームビーコン処理
 * @author	Akito Mori
 * @date    	2006.03.16
 */
//=============================================================================
#include "common.h"

#include "gflib/strbuf.h"
#include "system/wordset.h"
#include "system/arc_tool.h"
#include "system/arc_tool.dat"
#include "system/arc_util.h"
#include "../application/record/record.naix"
#include "fieldobj_code.h"
#include "msgdata/msg_trtype.h"
#include "comm_union_beacon.h"
#include "battle/trtype_def.h"
#include "field/union_beacon_tool.h"


#define UNION_VIEW_TYPE_NUM	( 16 )

// ユニオンルームで表示するトレーナーのタイプ見た目＆名前＆トレーナーグラフィックテーブル
static const int UnionViewTable[][3]={

	{ BOY1,			MSG_TRTYPE_SCHOOLB, 	TRTYPE_SCHOOLB    },	///< じゅくがえり
	{ BOY3,			MSG_TRTYPE_MUSHI,   	TRTYPE_MUSHI      },	///< むしとりしょうねん
	{ MAN3,			MSG_TRTYPE_ELITEM,  	TRTYPE_ELITEM     },	///< エリートトレーナー♂
	{ BADMAN,		MSG_TRTYPE_HEADS,   	TRTYPE_HEADS      },	///< スキンヘッズ
	{ EXPLORE,		MSG_TRTYPE_ISEKI,   	TRTYPE_ISEKI      },	///< いせきマニア
	{ FIGHTER,		MSG_TRTYPE_KARATE,  	TRTYPE_KARATE     },	///< からておう
	{ GORGGEOUSM,	MSG_TRTYPE_PRINCE,  	TRTYPE_PRINCE     },	///< おぼっちゃま
	{ MYSTERY,		MSG_TRTYPE_ESPM,    	TRTYPE_ESPM       },	///< サイキッカー

	{ GIRL1,		MSG_TRTYPE_MINI,  		TRTYPE_MINI       },	///< ミニスカート
	{ GIRL2,		MSG_TRTYPE_BATTLEG, 	TRTYPE_BATTLEG    },	///< バトルガール
	{ WOMAN2,		MSG_TRTYPE_SISTER, 		TRTYPE_SISTER     },	///< おとなのおねえさん
	{ WOMAN3,		MSG_TRTYPE_ELITEW,  	TRTYPE_ELITEW 	  },	///< エリートトレーナー♀
	{ IDOL,			MSG_TRTYPE_IDOL,    	TRTYPE_IDOL       },	///< アイドル
	{ LADY,			MSG_TRTYPE_MADAM, 		TRTYPE_MADAM      },	///< マダム
	{ COWGIRL,		MSG_TRTYPE_COWGIRL, 	TRTYPE_COWGIRL    },	///< カウガール
	{ GORGGEOUSW,	MSG_TRTYPE_PRINCESS,	TRTYPE_PRINCESS   },	///< おじょうさま

};

// 見た目変更おやじ用のテーブル（IDを８で割ったあまりに対応する）
static const int UnionViewNameTable[][4]={
	{0,1,2,3,},
	{1,6,7,0,},

	{2,3,4,5,},
	{3,0,5,6,},

	{4,1,2,7,},
	{5,2,7,0,},

	{6,3,4,1,},
	{7,4,5,6,},
};

#define UNION_VIEW_SELECT_NUM	( 4 )
#define UNION_VIEW_SELECT_TYPE	( 8 )

//==============================================================================
/**
 * $brief   IDと性別から選択できる４つのトレーナータイプの文字列を格納する
 *
 * @param   id			ユーザーID
 * @param   sex			性別
 * @param   wordset		文字列格納バッファ
 *
 * @retval  none		
 */
//==============================================================================
void UnionView_SetUpTrainerTypeSelect( u32 id, int sex, WORDSET *wordset )
{
	int key    = id%8;
	int i;

	// IDを８で割った余りで、対応する4つの選択肢を性別ごとに用意する

	for(i=0; i<UNION_VIEW_SELECT_NUM; i++){
		int patern = UnionViewNameTable[key][i] + UNION_VIEW_SELECT_TYPE * sex;
		WORDSET_RegisterTrTypeName( 	  wordset, i, UnionViewTable[patern][1] );
	}


}


//==============================================================================
/**
 * $brief   選択結果から決定したトレーナータイプの番号そのものを算出する
 *
 * @param   id			ユーザーID
 * @param   sex			性別
 * @param   select		選択結果（0-3)
 *
 * @retval  int		
 */
//==============================================================================
int UnionView_GetTrainerType( u32 id, int sex, u32 select )
{
	int key    = id%8;
	int patern = UnionViewNameTable[key][select] + UNION_VIEW_SELECT_TYPE * sex;

	return UnionViewTable[patern][0];
}

//------------------------------------------------------------------
/**
 * $brief   ユニオンルーム用の見た目番号テーブルを検索して添え字を返す
 *
 * @param   sex			性別
 * @param   view_type	見た目番号
 *
 * @retval  int			添え字番号
 */
//------------------------------------------------------------------
static int Search_ViewNo( int sex, int view_type )
{
	int i;
	for(i=0;i<UNION_VIEW_TYPE_NUM/2;i++){
		if(UnionViewTable[i+(sex*(UNION_VIEW_TYPE_NUM/2))][0]==view_type){
			return i + (sex*(UNION_VIEW_TYPE_NUM/2));
		}	
	}
	return 0;
}
//==============================================================================
/**
 * $brief   見た目番号と性別から2Dキャラの位置を取得する
 *
 * @param   sex		
 * @param   view_type		
 *
 * @retval  int		
 */
//==============================================================================
int UnionView_GetCharaNo( int sex, int view_type )
{

	return Search_ViewNo( sex, view_type );
}


//==============================================================================
/**
 * $brief   トレーナーVIEWTYPEと性別から情報を引き出す
 *
 * @param   sex			性別
 * @param   view_type	MyStatus_GetTrainerViewで取得できるコード
 * @param   info		欲しいデータのタイプ
 *                      UNIONVIEW_ICONINDEX:	0詰めで何番目か
 *						UNIONVIEW_MSGTYPE:		メッセージデータ番号（ex 「じゅくがえり」のMSGNO）
 *						UNIONVIEW_TRTYPE:		トレーナーグラフィック番号
 *
 * @retval  int			0から詰めた時に何番目のキャラか
 */
//==============================================================================
int UnionView_GetTrainerInfo( int sex, int view_type, int info )
{
    int i = Search_ViewNo( sex, view_type );

    switch(info){
      case UNIONVIEW_ICONINDEX:
        return i;
		break;
      case UNIONVIEW_MSGTYPE:
        return UnionViewTable[i][1];
		break;
      case UNIONVIEW_TRTYPE:
        return UnionViewTable[i][2];
		break;
      default:
	    GF_ASSERT(0);
    }

	// ここまで抜けるのはおかしい
	return 0;
}


//==============================================================================
/**
 * $brief   指定のOBJに必要なパレットのポインタを返す
 *
 * @param   sex		
 * @param   view_type		
 *
 * @retval  u16 *		
 */
//==============================================================================
u16 *UnionView_GetPalNo( u16 * table, int sex, int view_type )
{
	int ret;
	ret = Search_ViewNo( sex, view_type );
	
	return &table[16*2*ret];
}

//==============================================================================
/**
 * $brief   18体分のパレットのテーブルをAlloc＆ﾛｰﾄﾞして返す
 *
 * @param   heapID		ヒープID
 *
 * @retval  u16 *		OBJ用のパレットテーブル（解放は各自で）
 */
//==============================================================================
u16 *UnionView_PalleteTableAlloc( int heapID )
{
	u8 *data1, *data2;
	NNSG2dPaletteData *pal1,*pal2;
	u16 *palette_table,*src;
	int i;
	
	data1 = ArcUtil_PalDataGet( ARC_RECORD_GRA, NARC_record_union_chara_nclr, &pal1, heapID );

	palette_table = sys_AllocMemory( heapID, 16*18*2 );
	OS_Printf("allocwork = %08x srcpallette = %08x\n",palette_table, pal1->pRawData);

	src = (u16*)pal1->pRawData;
	for(i=0;i<16*16;i++){
		palette_table[i] = src[i];
	}
//	MI_CpuCopyFast(pal1->pRawData, &palette_table[    0], 16*16*2);
//	MI_CpuCopyFast(pal2->pRawData, &palette_table[16*16], 2*16*2);
	
	sys_FreeMemoryEz(data1);
	
	return palette_table;
}


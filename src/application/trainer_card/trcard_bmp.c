//============================================================================================
/**
 * @file	trcard_bmp.c
 * @bfief	トレーナーカード画面BMP関連
 * @author	Nozomu Saito
 * @date	05.11.15
 */
//============================================================================================
#include "common.h"
#include "savedata/playtime.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "strbuf_family.h"

#include "trcard_bmp.h"
#include "trcard_cgx_def.h"

#include "msgdata/msg_trainerscard.h"
#include "msgdata/msg.naix"

#define FONT_BG	(GF_BGL_FRAME3_S)

#define HOUR_DISP_MAX	(999)


////////////////////////////////////////////////////////////////
//表面
////////////////////////////////////////////////////////////////
//トレーナーNO					:34
#define WIN_TR_NO_PX	(2)
#define WIN_TR_NO_PY	(4)
#define WIN_TR_NO_SX	(17)
#define WIN_TR_NO_SY	(2)
#define WIN_TR_NO_CGX	(TR_BG_BASE+TR_BG_SIZE)

//名前							:34
#define WIN_NAME_PX	(2)
#define WIN_NAME_PY	(6)
#define WIN_NAME_SX	(17)
#define WIN_NAME_SY	(2)
#define WIN_NAME_CGX	(WIN_TR_NO_CGX+WIN_TR_NO_SX*WIN_TR_NO_SY)

//おこづかい					:34
#define WIN_MONEY_PX	(2)
#define WIN_MONEY_PY	(9)
#define WIN_MONEY_SX	(17)
#define WIN_MONEY_SY	(2)
#define WIN_MONEY_CGX	(WIN_NAME_CGX+WIN_NAME_SX*WIN_NAME_SY)

//ずかん						:34
#define WIN_BOOK_PX	(2)
#define WIN_BOOK_PY	(12)
#define WIN_BOOK_SX	(17)
#define WIN_BOOK_SY	(2)
#define WIN_BOOK_CGX	(WIN_MONEY_CGX+WIN_MONEY_SX*WIN_MONEY_SY)

//スコア						:34
#define WIN_SCORE_PX	(2)
#define WIN_SCORE_PY	(15)
#define WIN_SCORE_SX	(17)
#define WIN_SCORE_SY	(2)
#define WIN_SCORE_CGX	(WIN_BOOK_CGX+WIN_BOOK_SX*WIN_BOOK_SY)

//プレイ時間					:56
#define WIN_TIME_PX	(2)
#define WIN_TIME_PY	(18)
#define WIN_TIME_SX	(28)
#define WIN_TIME_SY	(2)
#define WIN_TIME_CGX	(WIN_SCORE_CGX+WIN_SCORE_SX*WIN_SCORE_SY)

//スタート時間					:56
#define WIN_S_TIME_PX	(2)
#define WIN_S_TIME_PY	(20)
#define WIN_S_TIME_SX	(28)
#define WIN_S_TIME_SY	(2)
#define WIN_S_TIME_CGX	(WIN_TIME_CGX+WIN_TIME_SX*WIN_TIME_SY)
//////////////////////////////////////////////////////////////
//裏面
//////////////////////////////////////////////////////////////
//でんどういり					:112
#define WIN_CLEAR_PX	(2)
#define WIN_CLEAR_PY	(2)
#define WIN_CLEAR_SX	(28)
#define WIN_CLEAR_SY	(4)
#define WIN_CLEAR_CGX	(SIGN_CGX+TR_SIGN_SIZE)
//つうしん回数					:56
#define WIN_COMM_PX	(2)
#define WIN_COMM_PY	(7)
#define WIN_COMM_SX	(28)
#define WIN_COMM_SY	(2)
#define WIN_COMM_CGX	(WIN_CLEAR_CGX+WIN_CLEAR_SX*WIN_CLEAR_SY)

//通信対戦						:56
#define WIN_BATTLE_PX	(2)
#define WIN_BATTLE_PY	(9)
#define WIN_BATTLE_SX	(28)
#define WIN_BATTLE_SY	(2)
#define WIN_BATTLE_CGX	(WIN_COMM_CGX+WIN_COMM_SX*WIN_COMM_SY)

//通信交換						:56
#define WIN_TRADE_PX	(2)
#define WIN_TRADE_PY	(11)
#define WIN_TRADE_SX	(28)
#define WIN_TRADE_SY	(2)
#define WIN_TRADE_CGX	(WIN_BATTLE_CGX+WIN_BATTLE_SX*WIN_BATTLE_SY)

#define TR_STRING_LEN	(32)		//ローカライズを考え多めに。

#define TR_MSGCOLOR			(GF_PRINTCOLOR_MAKE( 1, 2, FBMP_COL_NULL ))
#define BMP_WIDTH_TYPE1	(8*17)
#define BMP_WIDTH_TYPE2	(8*28)

#define SEC_DISP_OFS	(2)		//適当。いい感じに見える値で。
#define YEN_OFS			(8*2)	//「円」表示分右スペース
#define HIKI_OFS		(8*3)	//「ひき」表示分右スペース

#define SEC_DISP_POS_X	(8*25)
#define MINITE_DISP_POS_X	(8*26)
#define HOUR_DISP_POS_X	(8*21)
#define MINITE_DISP_W	(8*2)
#define HOUR_DISP_W	(8*4)

static const BMPWIN_DAT TrCardBmpData[] =
{
	
	{	// 0:トレーナーNO
		FONT_BG, WIN_TR_NO_PX, WIN_TR_NO_PY,
		WIN_TR_NO_SX, WIN_TR_NO_SY, TR_FONT_PAL, WIN_TR_NO_CGX
	},	
	{	// 1:名前
		FONT_BG, WIN_NAME_PX, WIN_NAME_PY,
		WIN_NAME_SX, WIN_NAME_SY, TR_FONT_PAL, WIN_NAME_CGX
	},
	{	// 2:おこづかい
		FONT_BG, WIN_MONEY_PX, WIN_MONEY_PY,
		WIN_MONEY_SX, WIN_MONEY_SY, TR_FONT_PAL, WIN_MONEY_CGX
	},	
	{	// 3:ずかん
		FONT_BG, WIN_BOOK_PX, WIN_BOOK_PY,
		WIN_BOOK_SX, WIN_BOOK_SY, TR_FONT_PAL, WIN_BOOK_CGX
	},
	{	// 4:スコア
		FONT_BG, WIN_SCORE_PX, WIN_SCORE_PY,
		WIN_SCORE_SX, WIN_SCORE_SY, TR_FONT_PAL, WIN_SCORE_CGX
	},
	{	//　5:プレイ時間
		FONT_BG, WIN_TIME_PX, WIN_TIME_PY,
		WIN_TIME_SX, WIN_TIME_SY, TR_FONT_PAL, WIN_TIME_CGX
	},
	{	//　6:開始時間
		FONT_BG, WIN_S_TIME_PX, WIN_S_TIME_PY,
		WIN_S_TIME_SX, WIN_S_TIME_SY, TR_FONT_PAL, WIN_S_TIME_CGX
	},
	
	{	//　7:でんどういり
		FONT_BG, WIN_CLEAR_PX, WIN_CLEAR_PY,
		WIN_CLEAR_SX, WIN_CLEAR_SY, TR_FONT_PAL, WIN_CLEAR_CGX
	},

	{	//　8:通信回数
		FONT_BG, WIN_COMM_PX, WIN_COMM_PY,
		WIN_COMM_SX, WIN_COMM_SY, TR_FONT_PAL, WIN_COMM_CGX
	},
	{	//　9:通信対戦
		FONT_BG, WIN_BATTLE_PX, WIN_BATTLE_PY,
		WIN_BATTLE_SX, WIN_BATTLE_SY, TR_FONT_PAL, WIN_BATTLE_CGX
	},
	{	//　10:通信交換
		FONT_BG, WIN_TRADE_PX, WIN_TRADE_PY,
		WIN_TRADE_SX, WIN_TRADE_SY, TR_FONT_PAL, WIN_TRADE_CGX
	},
};

static void WriteNumData(	GF_BGL_BMPWIN *inWin,
							const u32 inBmpWidth,
							const u32 inRightSpace,
							const u32 inStartY,
							STRBUF *buff,
							const u32 inNum,
							const u8 inDigit,
							const NUMBER_DISPTYPE inDisptype);
static void WriteNumDataFill(	GF_BGL_BMPWIN *inWin,
								const u32 inBmpWidth,
								const u32 inRightSpace,
								const u32 inStartY,
								STRBUF *buff,
								const u32 inNum,
								const u8 inDigit,
								const NUMBER_DISPTYPE inDisptype,
								const u32 inFillSatrt,
								const u32 inFillWidth);
static void WriteStrData(	GF_BGL_BMPWIN *inWin,
							const u32 inBmpWidth,
							const u32 inRightSpace,
							const u32 inStartY,
							const STRBUF *buff);

//--------------------------------------------------------------------------------------------
/**
 * BMPウィンドウ追加
 *
 * @param	bgl		bgl
 * @param	win		BmpWin
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCBmp_AddTrCardBmp( GF_BGL_INI * bgl, GF_BGL_BMPWIN	*win )
{
#if 1
	u8 i;
	const BMPWIN_DAT * dat =TrCardBmpData;
	for(i=0;i<TR_CARD_WIN_MAX;i++){
		GF_BGL_BmpWinAddEx( bgl, &win[i], &dat[i] );
	}
	//先頭キャラをクリア（スクリーンクリアされてるところは、このキャラで埋まる）
	GF_BGL_CharFill( bgl, FONT_BG, 0, 1, 0 );
#endif
}


//--------------------------------------------------------------------------------------------
/**
 * BMPウィンドウ破棄
 *
 * @param	win		BmpWin
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCBmp_ExitTrCardBmpWin( GF_BGL_BMPWIN	*win )
{
	u16	i;

	for( i=0; i<TR_CARD_WIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &win[i] );
	}
}

static const int MsgList[] = {
	MSG_TCARD_01,
	MSG_TCARD_02,
	MSG_TCARD_03,
	MSG_TCARD_04,
	MSG_TCARD_05,
	MSG_TCARD_06,
	MSG_TCARD_07,
	MSG_TCARD_08,
	MSG_TCARD_09,
	MSG_TCARD_10,
	MSG_TCARD_11,
};

//--------------------------------------------------------------------------------------------
/**
 * 情報表示（表面）
 *
 * @param	win				BmpWin
 * @param	inTrCardData	トレーナーカードデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCBmp_WriteTrWinInfo( GF_BGL_BMPWIN	*win, const TR_CARD_DATA *inTrCardData )
{
	u8 i;
	MSGDATA_MANAGER* man;
	STRBUF *msg_buf;
	
	GF_BGL_BmpWinFill(
		&win[0], 0, 0, 0,  WIN_TR_NO_SX*8,  WIN_TR_NO_SY*8 );
	GF_BGL_BmpWinFill(
		&win[1], 0, 0, 0,  WIN_NAME_SX*8,  WIN_NAME_SY*8 );
	GF_BGL_BmpWinFill(
		&win[2], 0, 0, 0,  WIN_MONEY_SX*8,  WIN_MONEY_SY*8 );
	GF_BGL_BmpWinFill(
		&win[3], 0, 0, 0,  WIN_BOOK_SX*8,  WIN_BOOK_SY*8 );
	GF_BGL_BmpWinFill(
		&win[4], 0, 0, 0,  WIN_SCORE_SX*8,  WIN_SCORE_SY*8 );
	GF_BGL_BmpWinFill(
		&win[5], 0, 0, 0,  WIN_TIME_SX*8,  WIN_TIME_SY*8 );
	GF_BGL_BmpWinFill(
		&win[6], 0, 0, 0,  WIN_S_TIME_SX*8,  WIN_S_TIME_SY*8 );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_trainerscard_dat, HEAPID_TR_CARD);
	msg_buf = STRBUF_Create(TR_STRING_LEN, HEAPID_TR_CARD);
	for(i=0;i<7;i++){
		if ( (i!=3) ||
				(i==3)&&(inTrCardData->PokeBookFlg) ){	//ずかんのみ持っているときだけ表示
			MSGMAN_GetString(man, MsgList[i] ,msg_buf);
			GF_STR_PrintColor(&win[i], FONT_SYSTEM, msg_buf, 0, 0, MSG_ALLPUT, TR_MSGCOLOR, NULL);
		}
	}
	
	{
		STRBUF* str = STRBUF_Create(TR_DIGIT_MAX+1, HEAPID_TR_CARD);
		STRBUF* name_str = STRBUF_Create(BUFLEN_PERSON_NAME, HEAPID_TR_CARD);
		
		//ID
		WriteNumData(	&win[TRC_BMPWIN_TR_ID],
						BMP_WIDTH_TYPE1, 0, 0, str, inTrCardData->TrainerID, TR_ID_DIGIT,
						NUMBER_DISPTYPE_ZERO);
		
		//なまえ
		STRBUF_SetStringCode( name_str, inTrCardData->TrainerName );
		WriteStrData(	&win[TRC_BMPWIN_TR_NAME],
						BMP_WIDTH_TYPE1, 0, 0, name_str );

		//おこづかい
		WriteNumData(	&win[TRC_BMPWIN_MONEY],
						BMP_WIDTH_TYPE1, YEN_OFS, 0, str, inTrCardData->Money, MONEY_DIGIT,
						NUMBER_DISPTYPE_SPACE);

		//ずかん
		if (inTrCardData->PokeBookFlg){	//表示フラグがたっているときのみ表示	
			WriteNumData(	&win[TRC_BMPWIN_BOOK],
							BMP_WIDTH_TYPE1, HIKI_OFS, 0, str, inTrCardData->PokeBook, MONS_NUM_DIGIT,
							NUMBER_DISPTYPE_SPACE);
		}
		
		//スコア
		WriteNumData(	&win[TRC_BMPWIN_SCORE],
						BMP_WIDTH_TYPE1, 0, 0, str, inTrCardData->Score, SCORE_DIGIT,
						NUMBER_DISPTYPE_SPACE);
		
		//プレイ時間
		if ( inTrCardData->TimeUpdate ){	//通常
			WriteNumData(	&win[TRC_BMPWIN_PLAY_TIME],
						BMP_WIDTH_TYPE2, 0, 0, str, PLAYTIME_GetMinute(inTrCardData->PlayTime),
						TIME_M_DIGIT,
						NUMBER_DISPTYPE_ZERO);		//分
			WriteNumData(	&win[TRC_BMPWIN_PLAY_TIME],
						BMP_WIDTH_TYPE2, 3*8, 0, str, PLAYTIME_GetHour(inTrCardData->PlayTime),
						TIME_H_DIGIT,
						NUMBER_DISPTYPE_SPACE);		//時
		}else{						//時間更新しない場合のみ、固定で「：」表示
			WriteNumData(	&win[TRC_BMPWIN_PLAY_TIME],
							BMP_WIDTH_TYPE2, 0, 0, str, inTrCardData->PlayTime_m, TIME_M_DIGIT,
							NUMBER_DISPTYPE_ZERO);		//分
			WriteNumData(	&win[TRC_BMPWIN_PLAY_TIME],
							BMP_WIDTH_TYPE2, 3*8, 0, str, inTrCardData->PlayTime_h, TIME_H_DIGIT,
							NUMBER_DISPTYPE_SPACE);		//時
			
			MSGMAN_GetString(man, MSG_TCARD_12 ,str);
			GF_STR_PrintColor(&win[TRC_BMPWIN_PLAY_TIME], FONT_SYSTEM, str,
					SEC_DISP_POS_X+SEC_DISP_OFS, 0, MSG_ALLPUT, TR_MSGCOLOR, NULL);
		}
		
		//スタート時間
		WriteNumData(	&win[TRC_BMPWIN_START_TIME],
						BMP_WIDTH_TYPE2, 1*8, 0, str, inTrCardData->Start_d, DAY_DIGIT,
						NUMBER_DISPTYPE_ZERO);	//日
		WriteNumData(	&win[TRC_BMPWIN_START_TIME],
						BMP_WIDTH_TYPE2, 4*8, 0, str, inTrCardData->Start_m, MONTH_DIGIT,
						NUMBER_DISPTYPE_ZERO);	//月
		WriteNumData(	&win[TRC_BMPWIN_START_TIME],
						BMP_WIDTH_TYPE2, 7*8, 0, str, inTrCardData->Start_y, YEAR_DIGIT,
						NUMBER_DISPTYPE_ZERO);	//年
		STRBUF_Delete( name_str );
		STRBUF_Delete( str );

	}
	STRBUF_Delete( msg_buf );
	MSGMAN_Delete( man );
}

//--------------------------------------------------------------------------------------------
/**
 * 情報表示（裏面）
 *
 * @param	win				BmpWin
 * @param	inTrCardData	トレーナーカードデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCBmp_WriteTrWinInfoRev( GF_BGL_BMPWIN	*win, const TR_CARD_DATA *inTrCardData  )
{
	u8 i;
	MSGDATA_MANAGER* man;
	STRBUF *msg_buf;

	GF_BGL_BmpWinFill(
		&win[7], 0, 0, 0,  WIN_CLEAR_SX*8,  WIN_CLEAR_SY*8 );
	GF_BGL_BmpWinFill(
		&win[8], 0, 0, 0,  WIN_COMM_SX*8,  WIN_COMM_SY*8 );
	GF_BGL_BmpWinFill(
		&win[9], 0, 0, 0,  WIN_BATTLE_SX*8,  WIN_BATTLE_SY*8 );
	GF_BGL_BmpWinFill(
		&win[10], 0, 0, 0,  WIN_TRADE_SX*8,  WIN_TRADE_SY*8 );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_trainerscard_dat, HEAPID_TR_CARD);
	msg_buf = STRBUF_Create(TR_STRING_LEN, HEAPID_TR_CARD);
	
	for(i=7;i<TR_CARD_WIN_MAX;i++){
		MSGMAN_GetString(man, MsgList[i] ,msg_buf);
		GF_STR_PrintColor(&win[i], FONT_SYSTEM, msg_buf, 0, 0, MSG_ALLPUT, TR_MSGCOLOR, NULL);
	}
	{
		STRBUF* str = STRBUF_Create(TR_DIGIT_MAX+1, HEAPID_TR_CARD);
		//殿堂入り

		if (inTrCardData->Clear_m != 0){	//月が0月でなければ、クリアしたとみなす
			WriteNumData(	&win[TRC_BMPWIN_CLEAR_TIME],
							BMP_WIDTH_TYPE2, 8*1, 0, str, inTrCardData->Clear_d, DAY_DIGIT,
							NUMBER_DISPTYPE_ZERO);		//日
			WriteNumData(	&win[TRC_BMPWIN_CLEAR_TIME],
							BMP_WIDTH_TYPE2, 8*4, 0, str, inTrCardData->Clear_m, MONTH_DIGIT,
							NUMBER_DISPTYPE_ZERO);		//月
			WriteNumData(	&win[TRC_BMPWIN_CLEAR_TIME],
							BMP_WIDTH_TYPE2, 8*7, 0, str, inTrCardData->Clear_y, YEAR_DIGIT,
							NUMBER_DISPTYPE_ZERO);		//年
			WriteNumData(	&win[TRC_BMPWIN_CLEAR_TIME],
							BMP_WIDTH_TYPE2, 0, 16, str, inTrCardData->ClearTime_m, TIME_M_DIGIT,
							NUMBER_DISPTYPE_ZERO);		//分
			WriteNumData(	&win[TRC_BMPWIN_CLEAR_TIME],
							BMP_WIDTH_TYPE2, 8*3, 16, str, inTrCardData->ClearTime_h, TIME_H_DIGIT,
							NUMBER_DISPTYPE_SPACE);	//時
		}else{
			MSGMAN_GetString(man, MSG_TCARD_13 ,str);
			GF_STR_PrintColor(&win[TRC_BMPWIN_CLEAR_TIME], FONT_SYSTEM, str,
						BMP_WIDTH_TYPE2-(8*9), 0, MSG_ALLPUT, TR_MSGCOLOR, NULL);	//年
			GF_STR_PrintColor(&win[TRC_BMPWIN_CLEAR_TIME], FONT_SYSTEM, str,
						BMP_WIDTH_TYPE2-(8*6), 0, MSG_ALLPUT, TR_MSGCOLOR, NULL);	//月
			GF_STR_PrintColor(&win[TRC_BMPWIN_CLEAR_TIME], FONT_SYSTEM, str,
						BMP_WIDTH_TYPE2-(8*3), 0, MSG_ALLPUT, TR_MSGCOLOR, NULL);	//日

			GF_STR_PrintColor(&win[TRC_BMPWIN_CLEAR_TIME], FONT_SYSTEM, str,
						BMP_WIDTH_TYPE2-(8*5), 16, MSG_ALLPUT, TR_MSGCOLOR, NULL);	//時
			GF_STR_PrintColor(&win[TRC_BMPWIN_CLEAR_TIME], FONT_SYSTEM, str,
						BMP_WIDTH_TYPE2-(8*2), 16, MSG_ALLPUT, TR_MSGCOLOR, NULL);	//分
		}
		MSGMAN_GetString(man, MSG_TCARD_12 ,str);
		GF_STR_PrintColor(&win[TRC_BMPWIN_CLEAR_TIME], FONT_SYSTEM, str,
					SEC_DISP_POS_X+SEC_DISP_OFS, 16, MSG_ALLPUT, TR_MSGCOLOR, NULL);
		
		//通信回数
		WriteNumData(	&win[TRC_BMPWIN_COMM_INFO],
						BMP_WIDTH_TYPE2, 8*2, 0, str, inTrCardData->CommNum, COMM_DIGIT,
						NUMBER_DISPTYPE_SPACE);
		
		//通信対戦
		WriteNumData(	&win[TRC_BMPWIN_BATTLE_INFO],
						BMP_WIDTH_TYPE2, 0, 0, str, inTrCardData->CommBattleLose, BATTLE_DIGIT,
						NUMBER_DISPTYPE_SPACE);
		WriteNumData(	&win[TRC_BMPWIN_BATTLE_INFO],
						BMP_WIDTH_TYPE2, 8*8, 0, str, inTrCardData->CommBattleWin, BATTLE_DIGIT,
						NUMBER_DISPTYPE_SPACE);
		
		//通信交換
		WriteNumData(	&win[TRC_BMPWIN_TRADE_INFO],
						BMP_WIDTH_TYPE2, 8*2, 0, str, inTrCardData->CommTrade, TRADE_DIGIT,
						NUMBER_DISPTYPE_SPACE);
		STRBUF_Delete( str );
	}
	STRBUF_Delete( msg_buf );
	MSGMAN_Delete( man );
}

//--------------------------------------------------------------------------------------------
/**
 * BMPウィンドウ非表示
 *
 * @param	win				BmpWin
 * @param	start			対象ウィンドウ開始インデックス
 * @param	end				対象ウィンドウ最終インデックス
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCBmp_NonDispWinInfo(GF_BGL_BMPWIN	*win, const u8 start, const u8 end)
{
	u8 i;
	for(i=start;i<=end;i++){
		GF_BGL_BmpWinOff( &win[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 数字表示
 *
 * @param	win				BmpWin
 * @param	inBmpWidth		幅
 * @param	inRightSpace	右空白
 * @param	inStartY		表示開始Y位置
 * @param	buff			バッファ
 * @param	inNum			数字
 * @param	inDigit			桁数
 * @param	inDispType		表示タイプ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void 
WriteNumData(	GF_BGL_BMPWIN *inWin,
							const u32 inBmpWidth,
							const u32 inRightSpace,
							const u32 inStartY,
							STRBUF *buff,
							const u32 inNum,
							const u8 inDigit,
							const NUMBER_DISPTYPE inDisptype)
{
	u32 len;

	STRBUF_SetNumber( buff, inNum, inDigit, inDisptype, NUMBER_CODETYPE_DEFAULT );
	len = FontProc_GetPrintStrWidth(FONT_SYSTEM,buff,0);

	GF_STR_PrintColor(	inWin, FONT_SYSTEM, buff,
						inBmpWidth-(len+inRightSpace), inStartY,
						MSG_ALLPUT, TR_MSGCOLOR, NULL);	
}

//--------------------------------------------------------------------------------------------
/**
 * 数字表示(上書き用)
 *
 * @param	win				BmpWin
 * @param	inBmpWidth		幅
 * @param	inRightSpace	右空白
 * @param	inStartY		表示開始Y位置
 * @param	buff			バッファ
 * @param	inNum			数字
 * @param	inDigit			桁数
 * @param	inDispType		表示タイプ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void 
WriteNumDataFill(	GF_BGL_BMPWIN *inWin,
					const u32 inBmpWidth,
					const u32 inRightSpace,
					const u32 inStartY,
					STRBUF *buff,
					const u32 inNum,
					const u8 inDigit,
					const NUMBER_DISPTYPE inDisptype,
					const u32 inFillSatrt,
					const u32 inFillWidth)
{
	u32 len;
	
	STRBUF_SetNumber( buff, inNum, inDigit, inDisptype, NUMBER_CODETYPE_DEFAULT );
	len = FontProc_GetPrintStrWidth(FONT_SYSTEM,buff,0);

	GF_BGL_BmpWinFill( inWin, 0, inFillSatrt, 0,  inFillWidth,  2*8 );

	GF_STR_PrintColor(	inWin, FONT_SYSTEM, buff,
						inBmpWidth-(len+inRightSpace), inStartY,
						MSG_ALLPUT, TR_MSGCOLOR, NULL);	
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列表示
 *
 * @param	win				BmpWin
 * @param	inBmpWidth		幅
 * @param	inRightSpace	右空白
 * @param	inStartY		表示開始Y位置
 * @param	buff			バッファ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WriteStrData(	GF_BGL_BMPWIN *inWin,
							const u32 inBmpWidth,
							const u32 inRightSpace,
							const u32 inStartY,
							const STRBUF *buff)
{
	u32 len;
	len = FontProc_GetPrintStrWidth(FONT_SYSTEM,buff,0);
	GF_STR_PrintColor(	inWin, FONT_SYSTEM, buff,
						inBmpWidth-(len+inRightSpace), inStartY,
						MSG_ALLPUT, TR_MSGCOLOR, NULL);
}

//--------------------------------------------------------------------------------------------
/**
 * プレイ時間描画
 *
 * @param	win				BmpWin
 * @param	inTrCardData	トレーナーカードデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCBmp_WritePlayTime(GF_BGL_BMPWIN	*win, const TR_CARD_DATA *inTrCardData, STRBUF *str)
{
	int hour;
	
	GF_ASSERT(inTrCardData->PlayTime!=NULL&&"ERROR:PlayTimeData is NULL!!");

	hour = PLAYTIME_GetHour(inTrCardData->PlayTime);

	if (hour>HOUR_DISP_MAX){
		hour = HOUR_DISP_MAX;
	}

	WriteNumDataFill(	&win[TRC_BMPWIN_PLAY_TIME],
						BMP_WIDTH_TYPE2, 0, 0, str,
						PLAYTIME_GetMinute(inTrCardData->PlayTime),
						TIME_M_DIGIT, NUMBER_DISPTYPE_ZERO,
						MINITE_DISP_POS_X,
						MINITE_DISP_W);		//分
	WriteNumDataFill(	&win[TRC_BMPWIN_PLAY_TIME],
						BMP_WIDTH_TYPE2, 3*8, 0, str,
						hour,
						TIME_H_DIGIT, NUMBER_DISPTYPE_SPACE,
						HOUR_DISP_POS_X,
						HOUR_DISP_W);		//時
}

//--------------------------------------------------------------------------------------------
/**
 * 秒表示
 *
 * @param	win				BmpWin
 * @param	inDisp			表示フラグ
 * @param	inSecBuf		文字列（コロン）
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCBmp_WriteSec(GF_BGL_BMPWIN	*win, const BOOL inDisp, STRBUF *inSecBuf)
{
	if (inDisp){
		GF_STR_PrintColor(win, FONT_SYSTEM, inSecBuf, SEC_DISP_POS_X+SEC_DISP_OFS, 0, MSG_ALLPUT, TR_MSGCOLOR, NULL);
	}else{
		GF_BGL_BmpWinFill( win, 0, SEC_DISP_POS_X, 0,  8,  WIN_S_TIME_SY*8 );
		GF_BGL_BmpWinOn( win );
	}
}


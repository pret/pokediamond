//============================================================================================
/**
 * @file	place_name.c	
 * @bfief	地名表示
 * @author	Nozomu Saito
 * @date	01.03.29
 *
 */
//============================================================================================
#include "common.h"
#include "place_name.h"
#include "zonedata.h"
#include "system/bmp_menu.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "fld_bmp.h"
#include "system/msgdata.h"
#include "msgdata/msg.naix"				//NARC_msg_??_dat
#include "msgdata/msg_place_name.h"

#include "fieldmap_work.h"

#define PAL_ONE_SIZE	( 32 )		// 通常パレット 16x2
#define ONE_CHAR_SIZE	(8)
#define PLACE_NAME_FRAME	(GF_BGL_FRAME3_M)

#define PLACE_NAME_OFS_MIN	(0)
#define PLACE_NAME_OFS_MAX	(38)
#define PLANE_NAME_SCROLL_SPEED	(4)
#define PLACE_NAME_HOLD_TIME	(60)

//↓これより下の定義はパレット、キャラデータに依存します
#define PLACE_NAME_PAL_WHITE	(0x0f)

#define PLACE_NAME_CHAR_LU		(1)
#define PLACE_NAME_CHAR_UP		(2)
#define PLACE_NAME_CHAR_RU		(3)
#define PLACE_NAME_CHAR_LD		(4)
#define PLACE_NAME_CHAR_DOWN	(5)
#define PLACE_NAME_CHAR_RD		(6)
#define PLACE_NAME_CHAR_LEFT	(7)
#define PLACE_NAME_CHAR_RIGHT	(8)
#define PLACE_NAME_CHAR_CENTER	(9)

//企画意図的な空白
#define WIN_WHITE_SPACE			(8)

//↓デザイン上、フレームの書いてあるキャラで文字のかけるスペース（ドット）
#define WIN_CAN_USE_SPACE				(4)
//↓デザイン上、フレームの書いてあるキャラの文字のかけないスペース（ドット）
#define WIN_DEAD_SPACE			(ONE_CHAR_SIZE-WIN_CAN_USE_SPACE)	
#define WRITE_NAME_POS_Y	(4)

typedef enum {
	NAME_STATE_NONE = 0,
	NAME_STATE_DOWN,
	NAME_STATE_UP,
	NAME_STATE_DOWN_HOLD
} PLACE_NAME_STATE;

typedef struct PLACE_NAME_CONT_tag
{
	BOOL			Moving;				//タスクは稼動中か？
	u8				State;				//表示状態
	TCB_PTR			Task;				//タスクポインタ
	int				Offset;				//スクロール値
	u16				WaitCount;
	BOOL			IsNext;
	int				NameID;
	GF_BGL_INI		*WinIni;
	GF_BGL_BMPWIN	Win;
	u8				WriteOffs;
	NNSG2dCharacterData *CharDat;
	void * CharBuff;
	MSGDATA_MANAGER* MsgDataManager;
	STRBUF			*NameBuff; 
}PLACE_NAME_CONT;

static void SetPlaceNameGraphic(PNC_PTR outPlaceNameCont);
static void SetPlaceNameWinGraphic( PNC_PTR outPlaceNameCont,
									u8 frmnum,
									u16 cgx,
									u8 pal,
									u8 win_num );
static void CleanPlaceNameCont(PNC_PTR outPlaceNameCont);
static void SetUpPlaceNameCont(PNC_PTR, GF_BGL_INI *bgl);
static void PlaceNameTask(TCB_PTR tcb,void *work);
static void SetupPlaceNameWin(PNC_PTR outPlaceNameCont, const int inLen);
static void SetUPState(PNC_PTR outPlaceNameCont);
static void WritePlaceName(PNC_PTR ioPlaceNameCont,const STRBUF* inName);
static u32 GetPlaceName(MSGDATA_MANAGER* manager, const int inNameID, STRBUF *outName);

//------------------------------------------------------------------
/**
 * @brief	パレットセット
 * @param	buf		バッファ		
 * @param	siz		サイズ
 * @param	ofs		オフセット
 * @return	none
 */
//------------------------------------------------------------------
static void SetPlaceNameWinPalette( void * buf, u16 siz, u16 ofs )
{
	DC_FlushRange( (void *)buf, siz * PAL_ONE_SIZE );
	GX_LoadBGPltt( (const void *)buf, ofs * PAL_ONE_SIZE, siz * PAL_ONE_SIZE );
}

//------------------------------------------------------------------
/**
 * @brief	グラフィックセット
 * @param	outPlaceNameCont	地名構造体へのポインタ		
 * @return	none
 */
//------------------------------------------------------------------
static void SetPlaceNameGraphic(PNC_PTR outPlaceNameCont)
{
	GF_BGL_BmpWinAdd(
			outPlaceNameCont->WinIni, &outPlaceNameCont->Win,
			FLD_MBGFRM_FONT,  FLD_PLACE_WIN_PX,  FLD_PLACE_WIN_PY,
			FLD_PLACE_WIN_SX, FLD_PLACE_WIN_SY, PLACE_WIN_PAL, FLD_PLACE_WIN_CGX );
	SetPlaceNameWinGraphic( outPlaceNameCont,
							FLD_MBGFRM_FONT,
							PLACE_WIN_CGX_NUM,
							PLACE_WIN_PAL,
							0 );
}

//------------------------------------------------------------------
/**
 * @brief	ウィンドウグラフィックセット
 * @param	ioPlaceNameCont	地名構造体へのポインタ
 * @param	frmnum			フレームナンバー
 * @param	cgx				キャラ
 * @param	pal				パレット
 * @param	win_num			ウィンドウナンバー
 * @return	none
 */
//------------------------------------------------------------------
static void SetPlaceNameWinGraphic( PNC_PTR ioPlaceNameCont,
									u8 frmnum,
									u16 cgx,
									u8 pal,
									u8 win_num )
{
	void * buf;
	u32	size;
	NNSG2dPaletteData * pal_dat;

	ioPlaceNameCont->CharDat = GF_BGL_NTRCHR_CharGet(	&ioPlaceNameCont->CharBuff,
														HEAPID_FIELD,
														"/data/dp_areawindow.NCGR" );
	GF_BGL_LoadCharacter(	ioPlaceNameCont->WinIni,
							frmnum,
							ioPlaceNameCont->CharDat->pRawData,
							ioPlaceNameCont->CharDat->szByte,
							cgx );
	pal_dat = GF_BGL_NTRCHR_PalLoad(&buf,HEAPID_FIELD, "/data/dp_areawindow.NCLR");
	
	SetPlaceNameWinPalette( pal_dat->pRawData, 1, pal );
	sys_FreeMemoryEz( buf );
}

//------------------------------------------------------------------
/**
 * @brief	ウィンドウセットアップ
 * @param	ioPlaceNameCont	地名構造体へのポインタ
 * @param	len				文字列長さ
 * @return	none
 */
//------------------------------------------------------------------
static void SetupPlaceNameWin(PNC_PTR ioPlaceNameCont, const int inLen)
{
	int bmp_len;	//フレーム両端部分を含まない、必要なBMPドットサイズ
	int char_w;		//キャラサイズ
	int plus_ofs;	//フレーム両端の文字が書けないオフセット値からのオフセット

	int total_dot;
	int rest_dot;
	int plus;
	u8 plus_char;
	u8 i;			//汎用カウンタ

	total_dot = (inLen+ONE_CHAR_SIZE)/ONE_CHAR_SIZE*ONE_CHAR_SIZE;
	rest_dot = total_dot-inLen;
	plus = rest_dot/2;
 
	if ( WIN_WHITE_SPACE <= (WIN_CAN_USE_SPACE+plus) ){
		plus_char = 0;
	}else{
		int temp;
		temp = WIN_WHITE_SPACE - (WIN_CAN_USE_SPACE+plus);	//空白を作るのに足りない片側のドット数
		temp*=2;											//空白を作るのに足りないドット数合計
		plus_char = (temp+(ONE_CHAR_SIZE-1))/ONE_CHAR_SIZE;	//必要キャラ
	}

	bmp_len = inLen;
	if (bmp_len <=0 ){
		char_w = 0;
		plus_ofs = 0;
	}else{
		char_w = (bmp_len+ONE_CHAR_SIZE)/ONE_CHAR_SIZE;	//フレーム部分を除いた必要キャラ数
		char_w += plus_char;
		//↓加算オフセット＝（文字を書くことができるドット数-地名文字ドット数）/2
		plus_ofs = ( ((char_w*ONE_CHAR_SIZE)+(WIN_CAN_USE_SPACE*2) ) - inLen ) / 2;
	}
	
	ioPlaceNameCont->WriteOffs = WIN_DEAD_SPACE+plus_ofs;
	///OS_Printf("name =%d,%d,%d,%d\n",total_dot,inLen,char_w,plus_ofs);

	//クリーン処理
	{
		GF_BGL_BmpWinDataFill( &ioPlaceNameCont->Win, 0 );	//ＢＭＰウィンドウをクリア
		
		//ＢＭＰウィンドウを作成
		{
			//左上フレーム
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_LU*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					0, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			//右上フレーム
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_RU*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					(char_w+1)*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			//左フレーム
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_LEFT*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					0, ONE_CHAR_SIZE, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			//右フレーム
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_RIGHT*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					(char_w+1)*ONE_CHAR_SIZE, ONE_CHAR_SIZE, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			//左下フレーム
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_LD*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					0, ONE_CHAR_SIZE*2, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			//右下フレーム
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_RD*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					(char_w+1)*ONE_CHAR_SIZE, ONE_CHAR_SIZE*2, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			for(i=0;i<char_w;i++){
				//上フレーム
				GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_UP*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					ONE_CHAR_SIZE*(1+i), 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
				//ウィンドウ中
				GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_CENTER*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					ONE_CHAR_SIZE*(1+i), ONE_CHAR_SIZE, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
				//下フレーム
				GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_DOWN*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					ONE_CHAR_SIZE*(1+i), ONE_CHAR_SIZE*2, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			}
			GF_BGL_BmpWinOn( &ioPlaceNameCont->Win );
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief	構造体クリーン
 * @param	outPlaceNameCont	地名構造体へのポインタ
 * @return	none
 */
//------------------------------------------------------------------
static void CleanPlaceNameCont(PNC_PTR outPlaceNameCont)
{
	outPlaceNameCont->Moving = FALSE;
	outPlaceNameCont->State = NAME_STATE_NONE;
	outPlaceNameCont->Task = NULL;
	outPlaceNameCont->Offset = 0;
	outPlaceNameCont->WaitCount = 0;
	outPlaceNameCont->IsNext = FALSE;
	outPlaceNameCont->NameID = 0;
	outPlaceNameCont->WinIni = NULL;
}

//------------------------------------------------------------------
/**
 * @brief	構造体セットアップ
 * @param	outPlaceNameCont	地名構造体へのポインタ
 * @param	bgl	BGL
 * @return	none
 */
//------------------------------------------------------------------
static void SetUpPlaceNameCont(PNC_PTR outPlaceNameCont, GF_BGL_INI *bgl)
{
	CleanPlaceNameCont(outPlaceNameCont);
	outPlaceNameCont->WinIni = bgl;
}

//------------------------------------------------------------------
/**
 * @brief	地名表示タスク
 * @param	tcb			タスクポインタ
 * @param	work		ワーク
 * @return	none
 */
//------------------------------------------------------------------
static void PlaceNameTask(TCB_PTR tcb,void *work)
{
	STRCODE name[BUFLEN_PLACE_NAME];
	u32 len;
	PLACE_NAME_CONT *place_name = (PLACE_NAME_CONT *)(work);
	switch(place_name->State){
	case NAME_STATE_DOWN:			//降下中
		place_name->Offset-=PLANE_NAME_SCROLL_SPEED;

		if (place_name->Offset < PLACE_NAME_OFS_MIN){
			place_name->Offset = PLACE_NAME_OFS_MIN;
		}
		
		GF_BGL_ScrollSet( place_name->WinIni, PLACE_NAME_FRAME, GF_BGL_SCROLL_Y_SET, place_name->Offset );
		if (place_name->Offset == PLACE_NAME_OFS_MIN){
			
			place_name->WaitCount = 0;
			place_name->State = NAME_STATE_DOWN_HOLD;
		}
		break;
	case NAME_STATE_DOWN_HOLD:		//降下後上昇待ち
		place_name->WaitCount++;
		if (place_name->WaitCount>=PLACE_NAME_HOLD_TIME){
			place_name->WaitCount = 0;
			place_name->State = NAME_STATE_UP;
		}
		break;
	case NAME_STATE_UP:				//上昇中
		place_name->Offset+=PLANE_NAME_SCROLL_SPEED;
		if (place_name->Offset > PLACE_NAME_OFS_MAX){
			place_name->Offset = PLACE_NAME_OFS_MAX;
		}
		GF_BGL_ScrollSet( place_name->WinIni, PLACE_NAME_FRAME, GF_BGL_SCROLL_Y_SET, place_name->Offset );
		if (place_name->Offset == PLACE_NAME_OFS_MAX){
			if (place_name->IsNext){
				place_name->IsNext = FALSE;

				//名前セット
				len = PNC_GetPlaceName(place_name->MsgDataManager, place_name->NameID, place_name->NameBuff);
				
				SetupPlaceNameWin(place_name,len);
				
				WritePlaceName(place_name,place_name->NameBuff);
				place_name->State = NAME_STATE_DOWN;
			}else{
				StopPlaceName(place_name);	//<<内部でタスク解放してる
				return;
			}
		}
		break;
	case NAME_STATE_NONE:
	default:
		//アサーション
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief	地名のライト
 * @param	ioPlaceNameCont	地名構造体へのポインタ
 * @param	inName			地名
 * @return	none
 */
//------------------------------------------------------------------
static void WritePlaceName(PNC_PTR ioPlaceNameCont, const STRBUF *inName)
{	
	GF_PRINTCOLOR col;
	col = GF_PRINTCOLOR_MAKE(1,2,0);
	GF_STR_PrintColor(	&ioPlaceNameCont->Win,
						FONT_SYSTEM,
						inName,
						ioPlaceNameCont->WriteOffs, WRITE_NAME_POS_Y,
						MSG_ALLPUT,
						col,
						NULL );
}

//------------------------------------------------------------------
/**
 * @brief	地名表示状況のセット
 * @param	outPlaceNameCont	地名構造体へのポインタ
 * @return	none
 */
//------------------------------------------------------------------
static void SetUPState(PNC_PTR outPlaceNameCont)
{
	outPlaceNameCont->State = NAME_STATE_UP;
	outPlaceNameCont->WaitCount = 0;
}

//------------------------------------------------------------------
/**
 * @brief	メモリアロケーション
 * @param	bgl	BGL
 * @return	none
 */
//------------------------------------------------------------------
PNC_PTR	AllocPlaceNameCont(GF_BGL_INI *bgl)
{
	PLACE_NAME_CONT *place_name_cont;
	place_name_cont = sys_AllocMemory( HEAPID_FIELD, sizeof(PLACE_NAME_CONT) );
	place_name_cont->NameBuff = STRBUF_Create( BUFLEN_PLACE_NAME, HEAPID_FIELD );
	SetUpPlaceNameCont(place_name_cont,bgl);
	SetPlaceNameGraphic(place_name_cont);
	place_name_cont->MsgDataManager = MSGMAN_Create(	MSGMAN_TYPE_DIRECT,
														ARC_MSG,
														NARC_msg_place_name_dat,
														HEAPID_FIELD );
	return place_name_cont;
}

//------------------------------------------------------------------
/**
 * @brief	メモリフリー
 * @param	outPlaceNameCont	地名構造体へのポインタ
 * @return	none
 */
//------------------------------------------------------------------
void FreePlaceNameCont(PNC_PTR outPlaceNameCont)
{
	MSGMAN_Delete( outPlaceNameCont->MsgDataManager );
	GF_BGL_BmpWinDel( &outPlaceNameCont->Win );
	STRBUF_Delete( outPlaceNameCont->NameBuff );
	sys_FreeMemoryEz(outPlaceNameCont->CharBuff);
	sys_FreeMemoryEz( outPlaceNameCont );
	outPlaceNameCont = NULL;
}

//------------------------------------------------------------------
/**
 * @brief	地名表示リクエスト
 * @param	ioPlaceNameCont	地名構造体へのポインタ
 * @param	inZoneID	地名ID
 * @return	none
 */
//------------------------------------------------------------------
void PlaceNameRequest(PNC_PTR ioPlaceNameCont,const int inPlaceID)
{
	STRCODE name[BUFLEN_PLACE_NAME];
	u32 len;	
	ioPlaceNameCont->NameID = inPlaceID;//ZoneData_GetPlaceNameID(inZoneID);
	if (ioPlaceNameCont->Moving == FALSE){	//稼動していない
		ioPlaceNameCont->Moving = TRUE;	//稼動中にする
		//ＢＧオフセットをつける
		GF_BGL_ScrollSet( ioPlaceNameCont->WinIni, PLACE_NAME_FRAME, GF_BGL_SCROLL_Y_SET, PLACE_NAME_OFS_MAX );
		//カウンタ0セット
		ioPlaceNameCont->Offset = PLACE_NAME_OFS_MAX;
		//タスク作成
		ioPlaceNameCont->Task = TCB_Add(PlaceNameTask, ioPlaceNameCont, 0);
		//ステートセット
		ioPlaceNameCont->State = NAME_STATE_DOWN;
		//名前セット
		len = PNC_GetPlaceName(ioPlaceNameCont->MsgDataManager, ioPlaceNameCont->NameID, ioPlaceNameCont->NameBuff);
		SetupPlaceNameWin(ioPlaceNameCont,len);
		WritePlaceName(ioPlaceNameCont,ioPlaceNameCont->NameBuff);
	}else{									//すでに稼動している
		//稼動状況を見る
		switch(ioPlaceNameCont->State){
		case NAME_STATE_DOWN:			//降下中
		case NAME_STATE_DOWN_HOLD:		//降下後上昇待ち
			//ステートを上昇に変更し、次の地名をセットする
			SetUPState(ioPlaceNameCont);
			ioPlaceNameCont->IsNext = TRUE;
			break;
		case NAME_STATE_UP:				//上昇中
			//ステートはそのまま、次の地名をセットする
			ioPlaceNameCont->IsNext = TRUE;
			break;
		case NAME_STATE_NONE:
		default:
			//アサーション
			GF_ASSERT(0);
			break;
		}
	}	
}

//------------------------------------------------------------------
/**
 * @brief	地名表示中止
 * @param	ioPlaceNameCont	地名構造体へのポインタ
 * @return	none
 */
//------------------------------------------------------------------
void StopPlaceName(PNC_PTR ioPlaceNameCont)
{
	if (ioPlaceNameCont->Task!=NULL){
		//タスク削除
		TCB_Delete(ioPlaceNameCont->Task);
	}
	GF_BGL_BmpWinOff( &ioPlaceNameCont->Win );
	//GF_BGL_BmpWinDel( &ioPlaceNameCont->Win );

	//ＢＧオフセット復帰
	GF_BGL_ScrollSet( ioPlaceNameCont->WinIni, PLACE_NAME_FRAME, GF_BGL_SCROLL_Y_SET, 0 );

	{
		GF_BGL_INI *bgl = ioPlaceNameCont->WinIni;	//退避
		//構造体再セットアップ
		SetUpPlaceNameCont(ioPlaceNameCont,bgl);
	}
}

//------------------------------------------------------------------
/**
 * @brief	フィールドシステムポインタによる地名表示リクエスト(部屋の中は、リクエスト拒否)
 * @param	ioPlaceNameCont	地名構造体へのポインタ
 * @param	inZoneID	地名ID
 * @return	none
 */
//------------------------------------------------------------------
void PlaceNameRequestByFsys(FIELDSYS_WORK * fsys)
{
	int place_id;
	if ( !ZoneData_IsRoom(fsys->location->zone_id) ){
		place_id = ZoneData_GetPlaceNameID(fsys->location->zone_id);
		PlaceNameRequest(fsys->fldmap->place_name_cont, place_id); //地名表示
	}
}

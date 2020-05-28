//============================================================================================
/**
 * @file	ug_base.c
 * @brief	秘密基地
 * @author	saito
 * @date	2006.02.21
 *
 */
//============================================================================================

#include "common.h"
#include "../fieldsys.h"
#include "../field_event.h"

#include "savedata/undergrounddata.h"

#include "ug_base_bmp.h"

#include "../goods_data.h"

#include "../floor_touch.h"

#include "msgdata/msg_uwedit.h"
#include "ug_manager.h"
#include "fielddata/base_goods/goods_id_def.h"
#include "ug_base_se_def.h"

#include "../fieldmap_work.h"
#include "../fieldmap_func.h"

#include "ug_base.h"

#define GOODS_HIT_LIST_MAX	(32)	//パソコン1、グッズ15、岩16

#define BASE_EDIT_BLOCK_OFS_X	(0)	//基地編集時の地下ブロックX座標
#define BASE_EDIT_BLOCK_OFS_Z	(0) //基地編集時の地下ブロックZ座標
#define BASE_EDIT_GRID_OFS_X	(BASE_EDIT_BLOCK_OFS_X*32)
#define BASE_EDIT_GRID_OFS_Z	(BASE_EDIT_BLOCK_OFS_Z*32)
#define EDIT_START_X	(16)		//編集基点X座標
#define EDIT_START_Z	(13)		//編集基点Z座標

#define BASE_LX			(10)
#define BASE_LZ			(12)
#define BASE_RX			(21)
#define BASE_RZ			(23)

#define PASO_LX			(15)
#define PASO_LZ			(13)
#define PASO_RX			(16)
#define PASO_RZ			(13)

#define EXIT_LX			(15)
#define EXIT_LZ			(23)
#define EXIT_RX			(15)
#define EXIT_RZ			(23)

#define PUT_BLINK_TIME	(4)
#define COLLECT_BLINK_TIME	(8)

#define GOODS_PUT_MAX	(15)	//置くことができるグッズの最大数

#define MSG_WAIT	(30)
#define MSG_DEL_WAIT	(10)

#define ROCK_MAX	(16)

#define KEY_RAG		(8)

typedef enum {
	BASE_SEQ_SETUP,
	BASE_SEQ_MAIN_MENU,
	BASE_SEQ_PUT_CONT,
	BASE_SEQ_COLLECT_CONT,
	BASE_SEQ_REPUT_CONT,
	BASE_SEQ_REPUT_SET_CONT,
	BASE_SEQ_MSG_WAIT,
	BASE_SEQ_END
};

//各機能毎のシーケンス
//設置
enum {
	PUT_SEQ_GOODS_LIST = 0,
	PUT_SEQ_INIT,
	PUT_SEQ_MAIN,
	PUT_SEQ_PUT_NG,
	PUT_SEQ_PUT_OK,
	PUT_SEQ_PUT_ALREADY,
};

//回収
enum {
	COL_SEQ_INIT = 0,
	COL_SEQ_MAIN,
	COL_SEQ_COL_ROCK,
	COL_SEQ_COL_OK,
	COL_SEQ_COL_NG,
	COL_SEQ_ROCK_REST_BEFORE,
	COL_SEQ_ROCK_REST,
};

//再配置（ターゲット指定）
enum {
	REPUT_SEQ_INIT = 0,
	REPUT_SEQ_MAIN,
	REPUT_SEQ_COL_NG,
};

//再配置（設置）
enum {
	REPUTSET_SEQ_INIT = 0,
	REPUTSET_SEQ_MAIN,
	REPUTSET_SEQ_PUT_NG,
	REPUTSET_SEQ_PUT_OK,
};

typedef struct KEY_CONT_tag
{
	int OldKey;
	u8 Count;
}KEY_CONT;

typedef struct BLINK_DATA_tag
{
	int TargetIndex;
	int Count;
	int CountMax;
	BOOL Vanish;
	BOOL Valid;
}BLINK_DATA;

typedef struct RECT_DATA_tag
{
	int GridLX;	//左上グリッド座標X
	int GridLZ;	//左上グリッド座標Z
	int GridRX;	//右下グリッド座標X
	int GridRZ;	//右下グリッド座標Z
}RECT_DATA;

typedef struct GOODS_HIT_DAT_tag
{
	RECT_DATA	Rect;
/**	
	int GridLX;	//左上グリッド座標X
	int GridLZ;	//左上グリッド座標Z
	int GridRX;	//右下グリッド座標X
	int GridRZ;	//右下グリッド座標Z
*/
	int ObjEntryIndex;	//OBJエントリインデックス
	int No;		//グッズナンバー
	int Width;
	int Depth;
}GOODS_HIT_DAT;

typedef struct GOODS_OLD_POS_INFO_tag
{
	int TargetIndex;
	VecFx32 Trans;
	GOODS_HIT_DAT Data;
}GOODS_OLD_POS_INFO;

typedef struct GOODS_HIT_LIST_ITEM_tag
{
	BOOL Valid;	//データ有効フラグ
	GOODS_HIT_DAT Data;
}GOODS_HIT_LIST_ITEM;


//選択スクエア
typedef struct UG_BASE_PANEL_tag
{
	NNSG3dRenderObj			renderobj;
	NNSG3dResFileHeader* 	resfileheader;

	VecFx32 trans;	//座標
	int GridX;
	int GridZ;
	BOOL DrawFlg;
}UG_BASE_PANEL;

typedef struct UG_BASE_TP_tag
{
	int TpX;//現在のタッチ保存座標
	int TpY;
	BOOL TrgFlg;//現在のタッチ状況（離されている、押されている）
}UG_BASE_TP;

typedef struct EVENT_BASE_EDIT_WORK_tag
{
	int seq;
	int SubSeq;
	int MesIndex;
	GOODS_OLD_POS_INFO OldPosInfo;
	GOODS_HIT_DAT	EditGoodsData;
	GOODS_HIT_LIST_ITEM	GoodsHitList[GOODS_HIT_LIST_MAX];
	BLINK_DATA	BlinkData;
	UG_BASE_TP	BaseTp;
	UG_BASE_PANEL *Panel;		//フィールドマップファンクのワークポインタ
	FIELDSYS_WORK * fsys;
	UG_BASE_MENU *MainMenu;
	UG_BASE_LIST *GoodsList;
	FLDMAPFUNC_WORK* FldMapFunc;
	KEY_CONT	KeyCont;
	u16	MainMenuLine;
	u16	GoodsListLine;
	u16	MainMenuCurPos;
	u16	GoodsListCurPos;

	u8 MesWait;
	u8 GoodsCount;	//置いてあるグッズ数
	u8 RockCount;	//秘密基地にある岩の数
	u8 RockLimit;	//置いておかなければならない岩の数
	u8 GoodsLimit;	//置けるグッズ数
}EVENT_BASE_EDIT_WORK;

static BOOL MenuEvent(GMEVENT_CONTROL * event);
static BOOL EditLayoutEvent(GMEVENT_CONTROL * event);

static BOOL PutControl(GMEVENT_CONTROL * event);
static BOOL CollectControl(GMEVENT_CONTROL * event);
static BOOL ReputControl(GMEVENT_CONTROL * event);
static BOOL ReputSetControl(GMEVENT_CONTROL * event);
static void EntryNewGoods(FIELDSYS_WORK * fsys, const int inGoodsNo, EVENT_BASE_EDIT_WORK *work);
static void CancelGoodsEntry(FIELDSYS_WORK * fsys, /*const int inCode,*/ const int inEntryIndex);
static void CopyEditDataFromList(const int inIndex, EVENT_BASE_EDIT_WORK *ebew);
static BOOL CheckPutGoods(const GOODS_HIT_DAT *inData, const GOODS_HIT_LIST_ITEM *inList);
static BOOL CheckCollectGoods(	const int inGridX, const int inGridZ,
								const GOODS_HIT_LIST_ITEM *inList,
								int *outIndex);
static int EntryGoodsList(const GOODS_HIT_DAT *inData, GOODS_HIT_LIST_ITEM *ioList);
static void EntryGoodsListByIndex(const GOODS_HIT_DAT *inData, const int inIndex, GOODS_HIT_LIST_ITEM *ioList);
static void ClearGoodListByIndex(const int inIndex, GOODS_HIT_LIST_ITEM *outList);
static BOOL CheckRectHit(const RECT_DATA *inData1, const RECT_DATA *inData2);
static BOOL CheckPointHit(const RECT_DATA *inData, const int inX, const int inZ);
static BOOL CheckHitWall(const RECT_DATA *inData);

static void MakeGoodsHitList(FIELDSYS_WORK * fsys, EVENT_BASE_EDIT_WORK *ebew, GOODS_HIT_LIST_ITEM *outList);
static void MakeGoodsHitData(	const int inIndex, const int inGoodsNo,
								const int inX, const int inZ,
								GOODS_HIT_LIST_ITEM *outList	);
static void MakeGoodsMap3DObj(FIELDSYS_WORK *fsys, GOODS_HIT_LIST_ITEM *ioList);
static void WriteSaveData(FIELDSYS_WORK *fsys, const GOODS_HIT_LIST_ITEM *inList);

static const int GetGoodsObjID(FIELDSYS_WORK *fsys, const int inGoodsNo);
static void SetGoodsOldPos(const int inIndex, EVENT_BASE_EDIT_WORK * ebew);
static void PutGoodsOldPos(EVENT_BASE_EDIT_WORK * ebew);

static void SetNextSeqCall(const int inSeq, EVENT_BASE_EDIT_WORK * ebew);

static void SetupPanel(UG_BASE_PANEL *outPanel);
static void ReleasePanel(UG_BASE_PANEL *outPanel);
static void DispOnPanelFlgOnly(UG_BASE_PANEL *outPanel);
static void SetPanelPos(const int inGridX, const int inGridZ, UG_BASE_PANEL *outPanel);
//static void DispOnPanel(void);
static void DispOffPanel(UG_BASE_PANEL *outPanel);

static BOOL TpGoodsPutControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outPut);
static BOOL TpGoodsCollectControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outCollect);
static BOOL TpGoodsReputControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outReput);
static BOOL TpGoodsReputSetControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outReput);

static void InitBlinkData(BLINK_DATA *outBlinkData);
static void SetBlinkTarget(const int inTarget, const int inCountMax, BLINK_DATA *outBlinkData);
static void BlinkTarget(FIELDSYS_WORK *fsys, BLINK_DATA *ioBlinkData);
static void StopBlink(FIELDSYS_WORK *fsys, BLINK_DATA *inBlinkData);
static const int GetBlinkTarget(BLINK_DATA *inBlinkData);

static void InitBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work);
static void BasePanelDummy(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work);
static void EndBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work);
static void DrawBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work);

static const FLDMAPFUNC_DATA BasePanelData = {
	FLDMAP_PRI_BASE_PANEL,
	sizeof(UG_BASE_PANEL),
	InitBasePanel,
	EndBasePanel,
	BasePanelDummy,
	DrawBasePanel,
};


//今から置く物を配置モデルとして登録
static void EntryNewGoods(FIELDSYS_WORK * fsys, const int inGoodsNo, EVENT_BASE_EDIT_WORK *ebew)
{
	GOODS_HIT_DAT *data;
	VecFx32 trans;

	GF_ASSERT(inGoodsNo!=0&&"ナンバー0のグッズはありません");
	
	//今から置く物をセット
	data = &ebew->EditGoodsData;

	//グッズ情報にアクセスして、縦横サイズを取得
	data->Width = GOODS_GetGoodsSizeX(inGoodsNo);
	data->Depth = GOODS_GetGoodsSizeZ(inGoodsNo);

///	OS_Printf("Goods:%d,size = %d,%d\n",inGoodsNo,data->Width,data->Depth);	
	
	trans.x = (FX32_ONE*16)*(BASE_EDIT_GRID_OFS_X+EDIT_START_X)+((FX32_ONE*8)*data->Width);
	trans.y = /*0*/FX32_ONE;
	trans.z = (FX32_ONE*16)*(BASE_EDIT_GRID_OFS_Z+EDIT_START_Z)+((FX32_ONE*8)*data->Depth);

	data->ObjEntryIndex =  
		M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
							fsys->MapResource,
							GetGoodsObjID(fsys, inGoodsNo),
							&trans,	NULL,		//
							fsys->field_3d_anime);

	
	//基地がどこ名配置されようと、管理は0,0基点で行う
	data->Rect.GridLX = EDIT_START_X;
	data->Rect.GridLZ = EDIT_START_Z;
	data->Rect.GridRX = EDIT_START_X+(data->Width-1);
	data->Rect.GridRZ = EDIT_START_Z+(data->Depth-1);
	data->No = inGoodsNo;//グッズナンバーセット
}

//エントリを解除
static void CancelGoodsEntry(FIELDSYS_WORK * fsys, const int inEntryIndex)
{
	M3DO_CleanMap3DObj(inEntryIndex, fsys->Map3DObjExp);
}

//リストの指定データを編集バッファにコピーする
static void CopyEditDataFromList(const int inIndex, EVENT_BASE_EDIT_WORK *ebew)
{
	GOODS_HIT_DAT *data;
	GF_ASSERT(ebew->GoodsHitList[inIndex].Valid&&"データは無効状態です");
	data = &(ebew->GoodsHitList[inIndex].Data);
	ebew->EditGoodsData = (*data);
}

//秘密基地レイアウト変更制御イベントの発行
static BOOL EditLayoutEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);
	switch(ebew->seq){
	case BASE_SEQ_SETUP:
		sys_KeyRepeatSpeedSet( 4, 8 );
		//基地メインメニュー設定
		ebew->MainMenu = BMENU_AllocUgBaseMenu();
		BMENU_InitBaseMainMenu(	ebew->MainMenu, fsys,
								&ebew->MainMenuLine, &ebew->MainMenuCurPos);

		//グッズリスト設定
		ebew->GoodsList = BMENU_AllocUgBaseGoodsList();
		BMENU_InitBaseGoodsList(ebew->GoodsList, fsys,
								&ebew->GoodsListLine, &ebew->GoodsListCurPos);
		
		//メニューコントロール
///		OS_Printf("セーブデータを読んでリスト作成\n");
		MakeGoodsHitList(fsys, ebew, ebew->GoodsHitList);
///		OS_Printf("Map3DObjをクリアして、エディット用に再セット\n");
		MakeGoodsMap3DObj(fsys, ebew->GoodsHitList);	
		
		SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);
		break;
	case BASE_SEQ_MAIN_MENU:
///		OS_Printf("メニューウィンドウ\n");
		FieldEvent_Call(event, MenuEvent, ebew);
		break;
	case BASE_SEQ_PUT_CONT:
		//設置
		FieldEvent_Call(event, PutControl, ebew);
		break;
	case BASE_SEQ_COLLECT_CONT:
		//回収
		FieldEvent_Call(event, CollectControl, ebew);
		break;
	case BASE_SEQ_REPUT_CONT:
		//再配置(グッズ指定)
		FieldEvent_Call(event, ReputControl, ebew);
		break;
	case BASE_SEQ_REPUT_SET_CONT:
		//再配置（設置）
		FieldEvent_Call(event, ReputSetControl, ebew);
		break;
	case BASE_SEQ_MSG_WAIT:
		//メッセージ待ち
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);
			}
		}	
		break;
	case BASE_SEQ_END:
		//終了
///		OS_Printf("基地処理終了\n");
		
		//グッズリスト解放
		BMENU_FreeUgBaseGoodsList(ebew->GoodsList);

		//基地メインメニュー解放
		BMENU_FreeUgBaseMenu(ebew->MainMenu);

		//フィールドマップファンク解放
		FLDMAPFUNC_Delete(ebew->FldMapFunc);
		
		sys_FreeMemoryEz(ebew);
		return TRUE;
	}
	return FALSE;
}

//メニューイベント
static BOOL MenuEvent(GMEVENT_CONTROL * event)
{
	BOOL rc;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);

	//エディットメインメニュー
	rc = BMENU_EditMainMenuControl(ebew->MainMenu);

	if (rc){
		//メニューのインデックスを見てどのモードに飛ばすかを判定
		switch(BMENU_GetReturnIndex(ebew->MainMenu)){
		case 0:		//設置モード
			{
				//個数チェック
				UNDERGROUNDDATA* pUGData;
				int count;
				pUGData = SaveData_GetUnderGroundData(fsys->savedata);
				count = UnderGroundGetNumGoodsPCItem(pUGData);
				if (count == 0){//今もってるグッズがあるか？
					//メッセージ：グッズが　ありません
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_20);
					ebew->MesWait = 0;
					SetNextSeqCall(BASE_SEQ_MSG_WAIT, ebew);
					return TRUE;
				}
				if (ebew->GoodsCount>GOODS_PUT_MAX){
///					OS_Printf("これ以上は置けません\n");
					//メッセージ：これいじょう　グッズは　おけません
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_21);
					ebew->MesWait = 0;
					SetNextSeqCall(BASE_SEQ_MSG_WAIT, ebew);
					return TRUE;
				}
				if (ebew->GoodsCount+1>ebew->GoodsLimit){
///					OS_Printf("グッズを置くには、レベルが足りない\n");
					//メッセージ：これいじょう　グッズは　おけません
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_21);
					ebew->MesWait = 0;
					SetNextSeqCall(BASE_SEQ_MSG_WAIT, ebew);
					return TRUE;
				}
			}
			//エントリ
///			OS_Printf("設置モード\n");
			//置けるグッズ数と置いてあるグッズ数をリストにセット
			BMENU_SetGoodsNumToList(ebew->GoodsList, ebew->GoodsCount, ebew->GoodsLimit);
			
			SetNextSeqCall(BASE_SEQ_PUT_CONT, ebew);
			return TRUE;
		case 1:		//回収モード
			//回収
///			OS_Printf("回収モード\n");
			//初回のみパネル位置セット
			SetPanelPos(EDIT_START_X, EDIT_START_Z, ebew->Panel);
			SetNextSeqCall(BASE_SEQ_COLLECT_CONT, ebew);
			return TRUE;
		case 2:		//再配置モード
			//再配置
///			OS_Printf("再配置モード\n");
			//初回のみパネル位置セット
			SetPanelPos(EDIT_START_X, EDIT_START_Z, ebew->Panel);
			SetNextSeqCall(BASE_SEQ_REPUT_CONT, ebew);
			return TRUE;
		default:	//終了
			//セーブに書く
			WriteSaveData(fsys, ebew->GoodsHitList)	;
			SetNextSeqCall(BASE_SEQ_END, ebew);
			return TRUE;
			break;
		}
	}
	return FALSE;
}

//イベントCALL
void UGBase_CallBaseEditEvent(FIELDSYS_WORK * fsys,GMEVENT_CONTROL* mainEvent)
{
	//基地エディット用ワーク
	EVENT_BASE_EDIT_WORK * ebew = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_BASE_EDIT_WORK));
	MI_CpuClear8(ebew, sizeof(EVENT_BASE_EDIT_WORK));

	SetNextSeqCall(BASE_SEQ_SETUP, ebew);
	ebew->fsys = fsys;

	//パネル描画用フィールドマップファンク作成
	ebew->FldMapFunc = FLDMAPFUNC_Create(fsys->fldmap->fmapfunc_sys, &BasePanelData);
	//パネル描画用フィールドマップファンクのポインタを取得
	ebew->Panel = FLDMAPFUNC_GetFreeWork(ebew->FldMapFunc);

	//マップジャンプイベントを作成
	FieldEvent_Call(mainEvent, EditLayoutEvent, ebew);
}

static BOOL PutControl(GMEVENT_CONTROL * event)
{
	
	fx32 plus_x, plus_z;
	M3DO_PTR ptr;
	BOOL tp_touch;
	BOOL put;

	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);

	switch(ebew->SubSeq){
	case PUT_SEQ_GOODS_LIST:
		{
			BOOL rc;
			//エディットメインメニュー
			rc = BMENU_EditGoodsListControl(ebew->GoodsList);
			if (rc){
				u32 idx;
				int goods_no;
				UNDERGROUNDDATA* pUGData;
				pUGData = SaveData_GetUnderGroundData(ebew->fsys->savedata);

				//リターンコードを調べる
				idx = BMENU_GetReturnListIdx(ebew->GoodsList);
				if (idx == LIST_CANCEL_CODE){	//キャンセルの場合
					//シーケンスをメインメニューへ
					SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//メインメニュー
					return TRUE;
				}
				
				goods_no = UnderGroundGetGoodsPCItem(pUGData,idx);
				if (goods_no!=GOODS_INVALID){	//グッズの場合
					//すでに基地においているかをチェック
					BOOL check;
					check = UnderGroundIsEntryGoodsPCItem(pUGData, idx);
					if (!check){//配置されていない
						//配置物として登録する
						EntryNewGoods(fsys, goods_no, ebew);
						ebew->SubSeq = PUT_SEQ_INIT;
					}else{	//置いている
						//メッセージ：そのグッズは　もう　おかれています
						ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_22);
						ebew->MesWait = 0;
						ebew->SubSeq = PUT_SEQ_PUT_ALREADY;
					}
				}else{			
					GF_ASSERT(0&&"グッズが識別できません");
				}
			}
		}
		break;	
	case PUT_SEQ_INIT:
		InitBlinkData(&ebew->BlinkData);
		SetBlinkTarget(ebew->EditGoodsData.ObjEntryIndex, PUT_BLINK_TIME, &ebew->BlinkData);
		ebew->SubSeq = PUT_SEQ_MAIN;
		break;
	case PUT_SEQ_MAIN:
		//点滅処理
		BlinkTarget(fsys, &ebew->BlinkData);
	
		tp_touch = TpGoodsPutControl(ebew, fsys, &put);
	
		if (!tp_touch){	//タッチしていない場合
			BOOL edit;
			RECT_DATA rect;
			edit = TRUE;
			rect = ebew->EditGoodsData.Rect;
			if (sys.repeat & PAD_KEY_LEFT){
				plus_x = -(FX32_ONE*16);
				plus_z = 0;
				rect.GridLX--;
				rect.GridRX--;
			}else if (sys.repeat & PAD_KEY_RIGHT){
				plus_x = (FX32_ONE*16);
				plus_z = 0;
				rect.GridLX++;
				rect.GridRX++;
			}else if (sys.repeat & PAD_KEY_UP){
				plus_x = 0;
				plus_z = -(FX32_ONE*16);
				rect.GridLZ--;
				rect.GridRZ--;
			}else if (sys.repeat & PAD_KEY_DOWN){
				plus_x = 0;
				plus_z = (FX32_ONE*16);
				rect.GridLZ++;
				rect.GridRZ++;
			}else{
				edit = FALSE;
			}

			if (edit != FALSE){
				if ( !CheckHitWall(&rect) ){
					VecFx32 vec;
					ebew->EditGoodsData.Rect = rect;
					ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, ebew->EditGoodsData.ObjEntryIndex);
					vec = M3DO_GetGlobalVec(ptr);
					vec.x += (plus_x);
					vec.z += (plus_z);
					vec.y = FX32_ONE;
					M3DO_SetGlobalVec(ptr, &vec);
				}
			}

			if (sys.trg & PAD_BUTTON_DECIDE){
				put = TRUE;
			}else if(sys.trg & PAD_BUTTON_CANCEL){
				//マップ3DOBJからエントリクリア
				CancelGoodsEntry(fsys, ebew->EditGoodsData.ObjEntryIndex);
				//メニューへ
				ebew->SubSeq = PUT_SEQ_GOODS_LIST;
				return FALSE;
			}
		}

		if (put){
			BOOL rc;
			//置けるかチェック
			rc = CheckPutGoods(&ebew->EditGoodsData, ebew->GoodsHitList);
			if (rc){		//設置OK
				u32 idx;
				int pos;
				UNDERGROUNDDATA* pUGData;
				pUGData = SaveData_GetUnderGroundData(ebew->fsys->savedata);
				pos = EntryGoodsList(&ebew->EditGoodsData, ebew->GoodsHitList);
				idx = BMENU_GetReturnListIdx(ebew->GoodsList);	
				//配置物として登録する
				UnderGroundEntryGoodsPCItem(pUGData, idx, pos);

				Snd_SePlay( UG_BASE_SE_PUT );		//グッズ置く音
				
				UgSecretBaseTalkRegisterGoodsName(ebew->EditGoodsData.No);
				//メッセージ：～　を　せっちした！
				ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_12);
				
				//点滅を解除
				StopBlink(fsys, &ebew->BlinkData);
				ebew->GoodsCount++;
/**				
				//シーケンスをメインメニューへ
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//メインメニュー//<<060306move
				return TRUE;
*/
				ebew->MesWait = 0;
				ebew->SubSeq = PUT_SEQ_PUT_OK;
				break;
			}else{
				Snd_SePlay( UG_BASE_SE_PUT_NG );		//グッズ置けない音
				//メッセージ：その　ばしょには　おけません
				ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_13);
				ebew->MesWait = 0;
				ebew->SubSeq = PUT_SEQ_PUT_NG;
			}
		}
		break;
	case PUT_SEQ_PUT_NG:	//置けないとき
		//メッセージ待ち
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				ebew->SubSeq = PUT_SEQ_MAIN;
			}
		}
		break;
	case PUT_SEQ_PUT_OK:	//置けたとき
		//メッセージ待ち
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				//シーケンスをメインメニューへ
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//メインメニュー
				return TRUE;
			}
		}
		break;
	case PUT_SEQ_PUT_ALREADY:	//すでに置いていたときのメッセージウェイト
		//メッセージ待ち
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				ebew->SubSeq = PUT_SEQ_GOODS_LIST;
			}
		}
		break;
	}//end switch
	return FALSE;
}

//回収コントロール
static BOOL CollectControl(GMEVENT_CONTROL * event)
{
	BOOL edit;
	RECT_DATA rect;
	fx32 trans_x,trans_z;
	BOOL tp_touch;
	BOOL collect;
	
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);
	
	switch(ebew->SubSeq){
	case COL_SEQ_INIT:
		InitBlinkData(&ebew->BlinkData);
		DispOnPanelFlgOnly(ebew->Panel); //<2003.04.28 add
		//初期位置に物が置いてある場合、点滅状態を作る
		{
			BOOL hit;
			int list_idx;
			hit = CheckCollectGoods(ebew->Panel->GridX, ebew->Panel->GridZ, ebew->GoodsHitList, &list_idx);
			if (hit){
				SetBlinkTarget(	ebew->GoodsHitList[list_idx].Data.ObjEntryIndex,
								COLLECT_BLINK_TIME,
								&ebew->BlinkData	);
			}
		}
		ebew->SubSeq = COL_SEQ_MAIN;
		break;
	case COL_SEQ_MAIN:
		edit = TRUE;
		//点滅処理
		BlinkTarget(fsys, &ebew->BlinkData);
		
		tp_touch = TpGoodsCollectControl(ebew, fsys, &collect);
		rect.GridLX = ebew->Panel->GridX;
		rect.GridRX = ebew->Panel->GridX;
		rect.GridLZ = ebew->Panel->GridZ;
		rect.GridRZ = ebew->Panel->GridZ;
		trans_x = ebew->Panel->trans.x;
		trans_z = ebew->Panel->trans.z;
		if (!tp_touch){	//タッチしていない場合
			if (sys.repeat & PAD_KEY_LEFT){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_x-=(FX32_ONE*16);
				rect.GridLX--;
				rect.GridRX--;
			}else if (sys.repeat & PAD_KEY_RIGHT){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_x+=(FX32_ONE*16);
				rect.GridLX++;
				rect.GridRX++;
			}else if (sys.repeat & PAD_KEY_UP){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_z-=(FX32_ONE*16);
				rect.GridLZ--;
				rect.GridRZ--;
			}else if (sys.repeat & PAD_KEY_DOWN){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_z+=(FX32_ONE*16);
				rect.GridLZ++;
				rect.GridRZ++;
			}else{
				edit = FALSE;
			}

			if (sys.trg & PAD_BUTTON_DECIDE){
				collect = TRUE;
			}else if(sys.trg & PAD_BUTTON_CANCEL){
				//キャンセル
///				OS_Printf("回収をキャンセルしました\n");
				DispOffPanel(ebew->Panel);

				//今点滅しているかもしれないOBJの点滅をストップ
				StopBlink(fsys, &ebew->BlinkData);
				
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//メインメニュー
				return TRUE;
			}
		}//end if(!tp_touch)

		if (edit){
			if ( !CheckHitWall(&rect) ){
				BOOL hit;
				int list_idx;

				ebew->Panel->trans.x = trans_x;
				ebew->Panel->trans.z = trans_z;
				ebew->Panel->GridX = rect.GridLX;
				ebew->Panel->GridZ = rect.GridLZ;
				
				hit = CheckCollectGoods(ebew->Panel->GridX, ebew->Panel->GridZ, ebew->GoodsHitList, &list_idx);
				if (hit){
					int idx;
					idx = GetBlinkTarget( &ebew->BlinkData );
					if (ebew->GoodsHitList[list_idx].Data.ObjEntryIndex != idx){
						//今点滅しているかもしれないOBJの点滅をストップ
						StopBlink(fsys, &ebew->BlinkData);
						//前回と違うものにヒットした場合はセットし直す
						SetBlinkTarget(	ebew->GoodsHitList[list_idx].Data.ObjEntryIndex,
										COLLECT_BLINK_TIME,
										&ebew->BlinkData	);
					}
				}else{
					StopBlink(fsys, &ebew->BlinkData);
					InitBlinkData(&ebew->BlinkData);
				}
			}
		}

		if (collect){	
			BOOL rc;
			int x,z;
			int index;
			GF_ASSERT(ebew->Panel->GridX<32&&"グリッド値が不正");
			GF_ASSERT(ebew->Panel->GridZ<32&&"グリッド値が不正");

			x = ebew->Panel->GridX;
			z = ebew->Panel->GridZ;

			//物体チェック
			rc = CheckCollectGoods(x, z, ebew->GoodsHitList, &index);
			if (rc){
				if (index!=SECRETBASE_PC_INDEX_NO){	//パソコン判定
					UgSecretBaseTalkRegisterGoodsName(ebew->GoodsHitList[index].Data.No);
					if (ebew->GoodsHitList[index].Data.No == GOODS_UG_IWA){	//岩判定
						//岩を撤去できるかをチェック
						if (ebew->RockLimit == ROCK_MAX){
							//レベル０なので岩破壊無理
							////メッセージ：いわを　かいしゅう　することは	 できません
							ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_16);
							ebew->MesWait = 0;
							ebew->SubSeq = COL_SEQ_COL_NG;
							break;
						}
						else if (ebew->RockCount-1<ebew->RockLimit){
							//レベルが足らなくて回収不可
							//メッセージ：これいじょう　いわを	かいしゅう　することは　できません
							ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_19);
							ebew->MesWait = 0;
							ebew->SubSeq = COL_SEQ_COL_NG;
							break;
						}else{
							Snd_SePlay( UG_BASE_SE_BREAK );		//岩壊し音
							//メッセージ：いわを　かいしゅう　して　こわしました！
							ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_15);
							GF_ASSERT(ebew->RockCount>0);
							ebew->RockCount--;	//岩数デクリメント
							ebew->MesWait = 0;
							ebew->SubSeq = COL_SEQ_COL_ROCK;
						}
					}else{
						UNDERGROUNDDATA* pUGData;
						pUGData = SaveData_GetUnderGroundData(ebew->fsys->savedata);
						Snd_SePlay( UG_BASE_SE_PICK );		//グッズ戻し音
						//パソコンに戻す
						UnderGroundTrashGoodsPCItem(pUGData, index);
						//メッセージ：～　を　パソコンに　もどした
						ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_14);
						GF_ASSERT(ebew->GoodsCount>0);
						ebew->GoodsCount--;//グッズ数デクリメント
						ebew->MesWait = 0;
						ebew->SubSeq = COL_SEQ_COL_OK;
					}
					//マップ3DOBJからエントリクリア
					CancelGoodsEntry(fsys, ebew->GoodsHitList[index].Data.ObjEntryIndex);
					//リストからはずす
					ClearGoodListByIndex(index, ebew->GoodsHitList);
///					OS_Printf("回収します\n");
									
					DispOffPanel(ebew->Panel);
/**
					SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//メインメニュー<060306move
					return TRUE;
*/
					ebew->MesWait = 0;
				}else{
///					OS_Printf("パソコンは回収対象外です\n");
					//メッセージ：パソコンは　もどせません
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_23);
					ebew->MesWait = 0;
					ebew->SubSeq = COL_SEQ_COL_NG;
				}
			}else{
///				OS_Printf("物がありません\n");
			}		
		}
		break;
	case COL_SEQ_COL_ROCK:
		//メッセージ待ち
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				int num;
				UgSecretBaseTalkEnd();
				num = ebew->RockCount-ebew->RockLimit;
				GF_ASSERT(num>=0);
				if (num == 0){	//メッセージなし
					SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//メインメニュー
					return TRUE;
				}else{
					/**
					UgSecretBaseTalkRegisterNum2(num, 0);
					//メッセージ：あと	～こ	かいしゅう	できます
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_18);
					ebew->MesWait = 0;
					ebew->SubSeq = COL_SEQ_ROCK_REST;
					*/
					ebew->MesWait = 0;
					ebew->SubSeq = COL_SEQ_ROCK_REST_BEFORE;
				}
			}
		}
		break;
	case COL_SEQ_COL_OK:	//回収成功
		//メッセージ待ち
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
//				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//メインメニュー
				//↑継続で回収できるように変更	2006.04.28
				ebew->SubSeq = COL_SEQ_INIT;
				return TRUE;
			}
		}	
		break;
	case COL_SEQ_COL_NG:	//回収失敗
		//メッセージ待ち
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				ebew->SubSeq = COL_SEQ_MAIN;
			}
		}
		break;
	case COL_SEQ_ROCK_REST_BEFORE:
		if ((ebew->MesWait++)>=MSG_DEL_WAIT){
			int num;
			num = ebew->RockCount-ebew->RockLimit;
			UgSecretBaseTalkRegisterNum2(num, 0);
			//メッセージ：あと	～こ	かいしゅう	できます
			ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_18);
			ebew->MesWait = 0;
			ebew->SubSeq = COL_SEQ_ROCK_REST;
		}
		break;
	case COL_SEQ_ROCK_REST:
		//メッセージ待ち
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//メインメニュー
				return TRUE;
			}
		}
		break;
	}	//end switch
	return FALSE;
}

//再設置コントロール
static BOOL ReputControl(GMEVENT_CONTROL * event)
{
	BOOL edit;
	RECT_DATA rect;
	fx32 trans_x,trans_z;
	BOOL tp_touch;
	BOOL reput;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);

	switch(ebew->SubSeq){
	case REPUT_SEQ_INIT:
		InitBlinkData(&ebew->BlinkData);
		DispOnPanelFlgOnly(ebew->Panel);
		//初回以外のときは、パネルがOBJにヒットしているので、
		//点滅状態を作る(何か置いてあれば、初回もヒットする)
		{
			BOOL hit;
			int list_idx;
			hit = CheckCollectGoods(ebew->Panel->GridX, ebew->Panel->GridZ, ebew->GoodsHitList, &list_idx);
			if (hit){
				SetBlinkTarget(	ebew->GoodsHitList[list_idx].Data.ObjEntryIndex,
								COLLECT_BLINK_TIME,
								&ebew->BlinkData	);
			}
		}
		ebew->SubSeq = REPUT_SEQ_MAIN;
		break;
	case REPUT_SEQ_MAIN:
		edit = TRUE;
		//点滅処理
		BlinkTarget(fsys, &ebew->BlinkData);
		
		tp_touch = TpGoodsReputControl(ebew, fsys, &reput);
		rect.GridLX = ebew->Panel->GridX;
		rect.GridRX = ebew->Panel->GridX;
		rect.GridLZ = ebew->Panel->GridZ;
		rect.GridRZ = ebew->Panel->GridZ;
		trans_x = ebew->Panel->trans.x;
		trans_z = ebew->Panel->trans.z;
		if (!tp_touch){	//タッチしていない場合
			if (sys.repeat & PAD_KEY_LEFT){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_x-=(FX32_ONE*16);
				rect.GridLX--;
				rect.GridRX--;
			}else if (sys.repeat & PAD_KEY_RIGHT){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_x+=(FX32_ONE*16);
				rect.GridLX++;
				rect.GridRX++;
			}else if (sys.repeat & PAD_KEY_UP){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_z-=(FX32_ONE*16);
				rect.GridLZ--;
				rect.GridRZ--;
			}else if (sys.repeat & PAD_KEY_DOWN){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_z+=(FX32_ONE*16);
				rect.GridLZ++;
				rect.GridRZ++;
			}else{
				edit = FALSE;
			}
			if (sys.trg & PAD_BUTTON_DECIDE){
				reput = TRUE;
			}else if(sys.trg & PAD_BUTTON_CANCEL){
				//キャンセル
///				OS_Printf("再配置をキャンセルしました\n");
				DispOffPanel(ebew->Panel);
				
				//今点滅しているかもしれないOBJの点滅をストップ
				StopBlink(fsys, &ebew->BlinkData);
				
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);	//メインメニュー
				return TRUE;
			}
		}//end if(!tp_touch)

		if (edit){
			if ( !CheckHitWall(&rect) ){
				BOOL hit;
				int list_idx;

				ebew->Panel->trans.x = trans_x;
				ebew->Panel->trans.z = trans_z;
				ebew->Panel->GridX = rect.GridLX;
				ebew->Panel->GridZ = rect.GridLZ;

				hit = CheckCollectGoods(ebew->Panel->GridX, ebew->Panel->GridZ, ebew->GoodsHitList, &list_idx);
				if (hit){
					int idx;
					idx = GetBlinkTarget( &ebew->BlinkData );
					if (ebew->GoodsHitList[list_idx].Data.ObjEntryIndex != idx){
						//今点滅しているかもしれないOBJの点滅をストップ
						StopBlink(fsys, &ebew->BlinkData);
						//前回と違うものにヒットした場合はセットし直す
						SetBlinkTarget(	ebew->GoodsHitList[list_idx].Data.ObjEntryIndex,
										COLLECT_BLINK_TIME,
										&ebew->BlinkData	);
					}
				}else{
					StopBlink(fsys, &ebew->BlinkData);
					InitBlinkData(&ebew->BlinkData);
				}
			}
		}

		if (reput){	
			BOOL rc;
			int x,z;
			int index;
			GF_ASSERT(ebew->Panel->GridX<32&&"グリッド値が不正");
			GF_ASSERT(ebew->Panel->GridZ<32&&"グリッド値が不正");

			x = ebew->Panel->GridX;
			z = ebew->Panel->GridZ;
		
			//物体チェック
			rc = CheckCollectGoods(x, z, ebew->GoodsHitList, &index);
			if (rc){
				if (index!=SECRETBASE_PC_INDEX_NO){	//パソコン判定
					if (ebew->GoodsHitList[index].Data.No == GOODS_UG_IWA){	//岩判定
						//岩なので、移動不可
						//メッセージ：いわを　いどうさせることは　できません
						ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_17);
						ebew->MesWait = 0;
						ebew->SubSeq = REPUT_SEQ_COL_NG;
					}else{
						//編集バッファにデータコピー
						CopyEditDataFromList(index, ebew);
						SetGoodsOldPos(index,ebew);				//現在位置を旧位置として保存
						//元の位置の情報をクリア
						ClearGoodListByIndex(index, ebew->GoodsHitList);
						
						Snd_SePlay( UG_BASE_SE_PICK );	//グッズ持ちあげ音
						
///						OS_Printf("再配置モードに移行します\n");
						DispOffPanel(ebew->Panel);
						SetNextSeqCall(BASE_SEQ_REPUT_SET_CONT, ebew);	//再設置モードへ
						return TRUE;
					}
				}else{
///					OS_Printf("パソコンは対象外です\n");
					//メッセージ：パソコンは　いどう　できません
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_24);
					ebew->MesWait = 0;
					ebew->SubSeq = REPUT_SEQ_COL_NG;
				}
			}else{
///				OS_Printf("物がありません\n");
			}		
		}
		break;
	case REPUT_SEQ_COL_NG:
		//メッセージ待ち
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				ebew->SubSeq = REPUT_SEQ_MAIN;
			}
		}
		break;
	}	//end switch
	return FALSE;
}

//再設置コントロール
static BOOL ReputSetControl(GMEVENT_CONTROL * event)
{
	fx32 plus_x, plus_z;
	M3DO_PTR ptr;

	BOOL tp_touch;
	BOOL reput;
	
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);

	switch(ebew->SubSeq){
	case REPUTSET_SEQ_INIT:
		InitBlinkData(&ebew->BlinkData);
		SetBlinkTarget(ebew->EditGoodsData.ObjEntryIndex, PUT_BLINK_TIME, &ebew->BlinkData);
		ebew->SubSeq = REPUTSET_SEQ_MAIN;
		break;
	case REPUTSET_SEQ_MAIN:
		//点滅処理
		BlinkTarget(fsys, &ebew->BlinkData);
		tp_touch = TpGoodsReputSetControl(ebew, fsys, &reput);

		if (!tp_touch){	//タッチされていない場合
			BOOL edit;
			RECT_DATA rect;
			edit = TRUE;
			rect = ebew->EditGoodsData.Rect;
			if (sys.repeat & PAD_KEY_LEFT){
				plus_x = -(FX32_ONE*16);
				plus_z = 0;
				rect.GridLX--;
				rect.GridRX--;
			}else if (sys.repeat & PAD_KEY_RIGHT){
				plus_x = (FX32_ONE*16);
				plus_z = 0;
				rect.GridLX++;
				rect.GridRX++;
			}else if (sys.repeat & PAD_KEY_UP){
				plus_x = 0;
				plus_z = -(FX32_ONE*16);
				rect.GridLZ--;
				rect.GridRZ--;
			}else if (sys.repeat & PAD_KEY_DOWN){
				plus_x = 0;
				plus_z = (FX32_ONE*16);
				rect.GridLZ++;
				rect.GridRZ++;
			}else{
				edit = FALSE;
			}

			if (edit != FALSE){
				if ( !CheckHitWall(&rect) ){
					VecFx32 vec;
					ebew->EditGoodsData.Rect = rect;
					ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, ebew->EditGoodsData.ObjEntryIndex);
					vec = M3DO_GetGlobalVec(ptr);
					vec.x += (plus_x);
					vec.z += (plus_z);
					vec.y = FX32_ONE;
					M3DO_SetGlobalVec(ptr, &vec);
				}
			}

			if (sys.trg & PAD_BUTTON_DECIDE){
				reput = TRUE;
			}else if(sys.trg & PAD_BUTTON_CANCEL){
				//元の位置に、リスト登録
				EntryGoodsListByIndex(&ebew->OldPosInfo.Data, ebew->OldPosInfo.TargetIndex, ebew->GoodsHitList);
				//キャンセルされたので元の表示座標に戻す
				PutGoodsOldPos(ebew);
		
///				OS_Printf("キャンセル。元の位置に戻す\n");
				//点滅を解除
				StopBlink(fsys, &ebew->BlinkData);
				
				//再配置モードへ
				SetNextSeqCall(BASE_SEQ_REPUT_CONT, ebew);
				return TRUE;
			}
		}//end if(!tp_touch)
	

		if (reput){
			BOOL rc;
			//置けるかチェック
			rc = CheckPutGoods(&ebew->EditGoodsData, ebew->GoodsHitList);
			if (rc){
				//元の位置に、リスト登録
				EntryGoodsListByIndex(&ebew->EditGoodsData, ebew->OldPosInfo.TargetIndex, ebew->GoodsHitList);
///				OS_Printf("置けました\n");

				Snd_SePlay( UG_BASE_SE_PUT );		//グッズ置く音
#if 0			//<<メッセージはいらないらしい2006.04.28
				UgSecretBaseTalkRegisterGoodsName(ebew->EditGoodsData.No);
				//メッセージ：～　を　せっちした！
				ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_12);
#endif				
				//パネルの移動
				SetPanelPos(ebew->EditGoodsData.Rect.GridLX, ebew->EditGoodsData.Rect.GridLZ, ebew->Panel);
				//点滅を解除
				StopBlink(fsys, &ebew->BlinkData);
				ebew->MesWait = 0;
				ebew->SubSeq = REPUTSET_SEQ_PUT_OK;
				break;
			}else{
				Snd_SePlay( UG_BASE_SE_PUT_NG );	//グッズ置けない音
				//メッセージ：その　ばしょには　おけません
				ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_13);
				ebew->MesWait = 0;
				ebew->SubSeq = REPUTSET_SEQ_PUT_NG;
			}
		}
		break;
	case REPUTSET_SEQ_PUT_NG:
		//メッセージ待ち
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				ebew->SubSeq = REPUTSET_SEQ_MAIN;
			}
		}
		break;
	case REPUTSET_SEQ_PUT_OK:
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				//再配置モードへ
				SetNextSeqCall(BASE_SEQ_REPUT_CONT, ebew);
				return TRUE;
			}
		}
		break;
	}//end switch

	return FALSE;
}

//置けるかチェック
static BOOL CheckPutGoods(const GOODS_HIT_DAT *inData, const GOODS_HIT_LIST_ITEM *inList)
{
	int i;
	//リストと照合
	for (i=0;i<GOODS_HIT_LIST_MAX;i++){
		if (inList[i].Valid == TRUE){
///			OS_Printf("%d:チェック開始\n",i);
			if ( CheckRectHit(&inList[i].Data.Rect,&inData->Rect) ){
				return FALSE;	//衝突したので物は置けない
			}
		}
	}

	//パソコン手前も置けないことにする
	{
		RECT_DATA paso_front_rect = {PASO_LX,PASO_LZ,PASO_RX,PASO_RZ};
		if ( CheckRectHit(&inData->Rect,&paso_front_rect) ){
			return FALSE;	//衝突したので物は置けない
		}
	}

	//出口も置けないことにする
	{
		RECT_DATA exit_rect = {EXIT_LX,EXIT_LZ,EXIT_RX,EXIT_RZ};
		if ( CheckRectHit(&inData->Rect,&exit_rect) ){
			return FALSE;	//衝突したので物は置けない
		}
	}
	
	return TRUE;	//物置ける
}

//指定座標に物体があるかをチェック
static BOOL CheckCollectGoods(	const int inGridX, const int inGridZ,
								const GOODS_HIT_LIST_ITEM *inList,
								int *outIndex)
{
	int i;
	for (i=0;i<GOODS_HIT_LIST_MAX;i++){
		if (inList[i].Valid == TRUE){
			if ( CheckPointHit(&(inList[i].Data.Rect), inGridX, inGridZ) ){
				//ヒットしたので撤去可能
				(*outIndex) = i;
				return TRUE;
			}
		}
	}
	(*outIndex) = GOODS_HIT_LIST_MAX;
	return FALSE;	//物がない
}

//壁チェック
static BOOL CheckHitWall(const RECT_DATA *inData)
{
	
	if ( (BASE_LX<=inData->GridLX)&&(inData->GridRX<=BASE_RX) &&
			(BASE_LZ<=inData->GridLZ)&&(inData->GridRZ<=BASE_RZ) ){
		return FALSE;	//NOHIT
	}else{
		return TRUE;	//HIT
	};
}

//リストにエントリ
static int EntryGoodsList(const GOODS_HIT_DAT *inData, GOODS_HIT_LIST_ITEM *ioList)
{
	int i;

	for(i=0;i<GOODS_HIT_LIST_MAX;i++){
		if (ioList[i].Valid == FALSE){
			//エントリ
			ioList[i].Valid = TRUE;
			ioList[i].Data = (*inData);
///			OS_Printf("%dにエントリ\n",i);
			return i;
		}
	}
	GF_ASSERT(0&&"エントリ数オーバー");
	return 0;
}

//リストにエントリ(場所指定)
static void EntryGoodsListByIndex(const GOODS_HIT_DAT *inData, const int inIndex, GOODS_HIT_LIST_ITEM *ioList)
{
	GF_ASSERT((inIndex<GOODS_HIT_LIST_MAX)&&"インデックスオーバー");
	GF_ASSERT((!ioList[inIndex].Valid)&&"指定インデックスにはすでに登録されています");

	//エントリ
	ioList[inIndex].Valid = TRUE;
	ioList[inIndex].Data = (*inData);
///	OS_Printf("%dにエントリ\n",inIndex);
}

//指定インデックスデータをリストから削除
static void ClearGoodListByIndex(const int inIndex, GOODS_HIT_LIST_ITEM *outList)
{
	GF_ASSERT_MSG((inIndex<GOODS_HIT_LIST_MAX),"インデックスオーバー");
	GF_ASSERT_MSG((inIndex!=0),"インデックス0のパソコンは撤去できません");
	GF_ASSERT_MSG(outList[inIndex].Valid,"すでに無効となっています");
	{
		outList[inIndex].Data.ObjEntryIndex = 0;
		outList[inIndex].Data.Rect.GridLX = 0;
		outList[inIndex].Data.Rect.GridLZ = 0;
		outList[inIndex].Data.Rect.GridRX = 0;
		outList[inIndex].Data.Rect.GridRZ = 0;
		outList[inIndex].Data.No = 0;
		outList[inIndex].Valid = FALSE;
	}
}

//矩形当たり判定
static BOOL CheckRectHit(const RECT_DATA *inData1, const RECT_DATA *inData2)
{
	if ( (inData1->GridLX<=inData2->GridRX)&&(inData2->GridLX<=inData1->GridRX) &&
			(inData1->GridLZ<=inData2->GridRZ)&&(inData2->GridLZ<=inData1->GridRZ) ){
		return TRUE;	//HIT
	}else{
		return FALSE;	//NOHIT
	}	
}

//指定点が矩形内にあるかを判定
static BOOL CheckPointHit(const RECT_DATA *inData, const int inX, const int inZ)
{
	if ( (inData->GridLX<=inX)&&(inX<=inData->GridRX) &&
			(inData->GridLZ<=inZ)&&(inZ<=inData->GridRZ) ){
		return TRUE;	//HIT
	}else{
		return FALSE;	//NOHIT
	}
}

//セーブデータから、管理リストを作成する
static void MakeGoodsHitList(FIELDSYS_WORK *fsys, EVENT_BASE_EDIT_WORK *ebew, GOODS_HIT_LIST_ITEM *outList)
{
	int i;
	int goods_no;
	int x,z;
	SECRETBASEDATA *s_data;
	s_data = SaveData_GetSecretBaseData(fsys->savedata);
	ebew->GoodsCount = 0;
	ebew->RockCount = 0;
	//岩リミットセット
	ebew->RockLimit = SecretBaseData_GetPlaceRockLimit(s_data);
	//グッズリミットセット
	ebew->GoodsLimit = SecretBaseData_GetPlaceGoodsLimit(s_data);
	for(i=0;i<GOODS_HIT_LIST_MAX;i++){
		goods_no = SecretBaseData_GetGoodsType(s_data, i);
		if (goods_no != GOODS_INVALID){
			//岩カウント
			if (goods_no == GOODS_UG_IWA){
				ebew->RockCount++;	//岩数インクリメント
			}else if( (goods_no != GOODS_UG_TABLE_L01)&&
						(goods_no != GOODS_UG_TABLE_L02)&&
						(goods_no != GOODS_UG_TABLE_L03)&&
						(goods_no != GOODS_UG_TABLE_L04)&&
						(goods_no != GOODS_UG_TABLE_L05)){
				ebew->GoodsCount++;	//グッズのインクリメント
			}
			x = SecretBaseData_GetGoodsXPos(s_data, i);
			z = SecretBaseData_GetGoodsZPos(s_data, i);
			//エントリ
///			OS_Printf("%d:セーブデータからグッズ番号%dをエントリ\n",i,goods_no);
///			OS_Printf("座標%d,%d\n",x,z);
			MakeGoodsHitData(i, goods_no, x, z, outList);
		}
	}
}

//データ作成
static void MakeGoodsHitData(	const int inIndex, const int inGoodsNo,
								const int inX, const int inZ,
								GOODS_HIT_LIST_ITEM *outList	)
{
	GOODS_HIT_DAT data;
	int w,d;
	
	data.ObjEntryIndex = 0;//後の処理で、OBJのエントリインデックスをセット
	data.No = inGoodsNo;	//グッズナンバー
	data.Rect.GridLX = inX;
	data.Rect.GridLZ = inZ;
	//グッズタイプから幅、奥行きを取得
	data.Width = GOODS_GetGoodsSizeX(inGoodsNo);
	data.Depth = GOODS_GetGoodsSizeZ(inGoodsNo);

	data.Rect.GridRX = inX+(data.Width-1);
	data.Rect.GridRZ = inZ+(data.Depth-1);

	outList[inIndex].Data = data;
	outList[inIndex].Valid = TRUE;	//データを有効
}

//データリストをもとに、マップ3DOBJを作成
static void MakeGoodsMap3DObj(FIELDSYS_WORK *fsys, GOODS_HIT_LIST_ITEM *ioList)
{
	int obj_id;
	int w,d;
	int i;
	VecFx32 trans;

	GOODS_HIT_DAT *data;

	//地下マップ3DOBJをクリア
	M3DO_CleanMap3DObjList(fsys->Map3DObjExp);
	
	for(i=0;i<GOODS_HIT_LIST_MAX;i++){
		if (!ioList[i].Valid){
			continue;
		}
		data = &ioList[i].Data;
		//OBJIDを取得(マップリソースのファイルテーブルとグッズナンバーから、OBJIDを取得)
		obj_id = GetGoodsObjID(fsys, data->No);
		w = data->Width;
		d = data->Depth;
		
		//描画位置を算出
		trans.x = (FX32_ONE*16)*(data->Rect.GridLX)+(FX32_ONE*8)*w;
		trans.z = (FX32_ONE*16)*(data->Rect.GridLZ)+(FX32_ONE*8)*d;
		trans.y = FX32_ONE/*0*/;
		data->ObjEntryIndex = M3DO_SetMap3DObjExp(	fsys->Map3DObjExp,
													fsys->MapResource,
													obj_id,			
													&trans, NULL,
													fsys->field_3d_anime);
	}
}

//セーブに書く
static void WriteSaveData(FIELDSYS_WORK *fsys, const GOODS_HIT_LIST_ITEM *inList)
{
	int i;
	int goods_no;
	int x,z;
	
	SECRETBASEDATA *s_data;
	s_data = SaveData_GetSecretBaseData(fsys->savedata);
	
	for(i=0;i<GOODS_HIT_LIST_MAX;i++){
		if (inList[i].Valid == TRUE){
			goods_no = inList[i].Data.No;
			x = inList[i].Data.Rect.GridLX;
			z = inList[i].Data.Rect.GridLZ;
///			OS_Printf("有効　%d:save_pos=%d,%d no=%d\n",i,x,z,goods_no);
		}else{
			goods_no = GOODS_INVALID;
			x = 0;
			z = 0;
///			OS_Printf("無効　%d:save_pos=%d,%d no=%d\n",i,x,z,goods_no);
		}
		SecretBaseData_SetGoodsPosition(s_data, i, goods_no, x, z);
	}
}

//OBJIDの取得
static const int GetGoodsObjID(FIELDSYS_WORK *fsys, const int inGoodsNo)
{
	int obj_id;

	GF_ASSERT(inGoodsNo!=0&&"ナンバー0のグッズはありません");

	obj_id = MAPRES_GetObjIDFromModelFile(fsys->MapResource, inGoodsNo);
	/**
	M3DO_PTR ptr;
	ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, inData->ObjEntryIndex);
	obj_id = M3DO_GetObjID(ptr);*/
	return obj_id;
}

//元の位置の記憶
static void SetGoodsOldPos(const int inIndex, EVENT_BASE_EDIT_WORK * ebew)
{
	M3DO_PTR ptr;
	GOODS_HIT_DAT *data;
	GF_ASSERT(ebew->GoodsHitList[inIndex].Valid&&"データは無効状態です");
	data = &(ebew->GoodsHitList[inIndex].Data);
	
	ptr = M3DO_GetMap3DObjDataFromIndex(ebew->fsys->Map3DObjExp, data->ObjEntryIndex);
	ebew->OldPosInfo.Trans = M3DO_GetGlobalVec(ptr);
	ebew->OldPosInfo.TargetIndex = inIndex;
	ebew->OldPosInfo.Data = (*data);
	
}
//元の位置座標に物を置く
static void PutGoodsOldPos(EVENT_BASE_EDIT_WORK * ebew)
{
	M3DO_PTR ptr;
	GOODS_HIT_DAT *data;
	int list_index;
	
	list_index = ebew->OldPosInfo.TargetIndex;
	GF_ASSERT(ebew->GoodsHitList[list_index].Valid&&"データは無効状態です");
	data = &(ebew->OldPosInfo.Data);

	ptr = M3DO_GetMap3DObjDataFromIndex(ebew->fsys->Map3DObjExp, data->ObjEntryIndex);
	M3DO_SetGlobalVec(ptr, &ebew->OldPosInfo.Trans);
}

static void SetNextSeqCall(const int inSeq, EVENT_BASE_EDIT_WORK * ebew)
{
	ebew->seq = inSeq;
	ebew->SubSeq = 0;
}

static void SetupPanel(UG_BASE_PANEL *outPanel)
{
	NNSG3dResMdl *resmodel;
	simple_3DModelSet(	HEAPID_FIELD,
						"data/ug_base_cur.nsbmd",
						&outPanel->renderobj,
						&resmodel,
						&outPanel->resfileheader);
	outPanel->trans.x = 0;
	outPanel->trans.y = 0;
	outPanel->trans.z = 0;
	outPanel->GridX = 0;
	outPanel->GridZ = 0;
	outPanel->DrawFlg = FALSE;
}

static void ReleasePanel(UG_BASE_PANEL *outPanel)
{
	sys_FreeMemoryEz(outPanel->resfileheader);
}

static void DispOnPanelFlgOnly(UG_BASE_PANEL *outPanel)
{
	outPanel->DrawFlg = TRUE;
}

static void SetPanelPos(const int inGridX, const int inGridZ, UG_BASE_PANEL *outPanel)
{
	outPanel->GridX = inGridX;
	outPanel->GridZ = inGridZ;
	outPanel->trans.x = (FX32_ONE*16)*(BASE_EDIT_GRID_OFS_X+inGridX)+((FX32_ONE*8));
	outPanel->trans.y = FX32_ONE;
	outPanel->trans.z = (FX32_ONE*16)*(BASE_EDIT_GRID_OFS_Z+inGridZ)+((FX32_ONE*8));
}

static void DispOffPanel(UG_BASE_PANEL *outPanel)
{
	outPanel->DrawFlg = FALSE;
}

static void GetTouchPos(const int inTpX, const int inTpY, UG_BASE_TP *outBaseTp)
{
	if (inTpX != 0xffff){
		outBaseTp->TpX = inTpX;
	}
	if (inTpY != 0xffff){
		outBaseTp->TpY = inTpY;
	}
}

static void TpUpdateGoodsPos(FIELDSYS_WORK * fsys, GOODS_HIT_DAT *ioData, UG_BASE_TP *outBaseTp)
{
	RECT_DATA rect;
	VecFx32 vec;
	int grid_x,grid_z;
	int w,d;
	TP_TO_3D_PTR tp_to_3d_ptr;
	tp_to_3d_ptr = fsys->TpTo3DPtr;
	
	//タッチ座標取得
	GetTouchPos(sys.tp_x, sys.tp_y, outBaseTp);
	//タッチグリッド取得
	vec = FTouch_CalcTpXYTo3D(outBaseTp->TpX, outBaseTp->TpY, tp_to_3d_ptr);
	grid_x = vec.x/(FX32_ONE*16);
	grid_z = vec.z/(FX32_ONE*16);

	//サイズ取得
	w = ioData->Width;
	d = ioData->Depth;

	rect.GridLX = grid_x%32;
	rect.GridLZ = grid_z%32;
	rect.GridRX = rect.GridLX+(w-1);
	rect.GridRZ = rect.GridLZ+(d-1);

	//基地内ならば、移動可能
	if ( !CheckHitWall(&rect) ){
		ioData->Rect = rect;
/**
	ioData->Rect.GridLX = grid_x%32;
	ioData->Rect.GridLZ = grid_z%32;
	ioData->Rect.GridRX = ioData->Rect.GridLX+(w-1);
	ioData->Rect.GridRZ = ioData->Rect.GridLZ+(d-1);
*/
		vec.x = grid_x*(FX32_ONE*16);
		vec.z = grid_z*(FX32_ONE*16);
		//物体のサイズ別にオフセット計算
		vec.x += (FX32_ONE*8)*w;
		vec.z += (FX32_ONE*8)*d;
		vec.y = FX32_ONE;
		{
			M3DO_PTR ptr;
			ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, ioData->ObjEntryIndex);
			M3DO_SetGlobalVec(ptr, &vec);
		}
	}
}

static void TpUpdatePanelPos(FIELDSYS_WORK * fsys, UG_BASE_TP *outBaseTp, UG_BASE_PANEL *outPanel)
{
	RECT_DATA rect;
	VecFx32 vec;
	int grid_x,grid_z;
	
	TP_TO_3D_PTR tp_to_3d_ptr;
	tp_to_3d_ptr = fsys->TpTo3DPtr;
	
	//タッチ座標取得
	GetTouchPos(sys.tp_x, sys.tp_y, outBaseTp);
	//タッチグリッド取得
	vec = FTouch_CalcTpXYTo3D(outBaseTp->TpX, outBaseTp->TpY, tp_to_3d_ptr);
	grid_x = vec.x/(FX32_ONE*16);
	grid_z = vec.z/(FX32_ONE*16);

	rect.GridLX = grid_x%32;
	rect.GridLZ = grid_z%32;
	rect.GridRX = rect.GridLX;
	rect.GridRZ = rect.GridLZ;

	//基地内ならば、移動可能
	if ( !CheckHitWall(&rect) ){
		vec.x = grid_x*(FX32_ONE*16)+(FX32_ONE*8);
		vec.z = grid_z*(FX32_ONE*16)+(FX32_ONE*8);
		vec.y = FX32_ONE;

		outPanel->trans = vec;
		outPanel->GridX = grid_x;
		outPanel->GridZ = grid_z;
	}
}

//設置時のタッチパネル制御
static BOOL TpGoodsPutControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outPut)
{
	VecFx32 vec;
	BOOL rc;	//タッチパネルに触っているかを返す
	rc = FALSE;
	*outPut = FALSE;
	
	if ( sys.tp_trg ){	//トリガー
		if (!sys.cont){		//キーが全く押されていなければ
			//トリガーフラグオン
			ebew->BaseTp.TrgFlg = TRUE;

			TpUpdateGoodsPos(fsys, &(ebew->EditGoodsData), &ebew->BaseTp);
		
		}//end if
		rc = TRUE;
	}else if(sys.tp_cont){	//ベタ
		if (ebew->BaseTp.TrgFlg){
			TpUpdateGoodsPos(fsys, &(ebew->EditGoodsData), &ebew->BaseTp);
			
		}
		rc = TRUE;
	}else{
		if (ebew->BaseTp.TrgFlg){
			ebew->BaseTp.TrgFlg = FALSE;
			//離したときに設置
			*outPut = TRUE;	//置く
		}
	}
	return rc;
}

//回収時のタッチパネル制御
static BOOL TpGoodsCollectControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outCollect)
{
	VecFx32 vec;
	BOOL rc;	//タッチパネルに触っているかを返す
	rc = FALSE;
	*outCollect = FALSE;
	
	if ( sys.tp_trg ){	//トリガー
		if (!sys.cont){		//キーが全く押されていなければ
			//トリガーフラグオン
			ebew->BaseTp.TrgFlg = TRUE;

			TpUpdatePanelPos(fsys, &ebew->BaseTp, ebew->Panel);
		
		}//end if
		rc = TRUE;
	}else if(sys.tp_cont){	//ベタ
		if (ebew->BaseTp.TrgFlg){
			TpUpdatePanelPos(fsys, &ebew->BaseTp, ebew->Panel);
			
		}
		rc = TRUE;
	}else{
		if (ebew->BaseTp.TrgFlg){
			ebew->BaseTp.TrgFlg = FALSE;
			//離したときに回収
			*outCollect = TRUE;	//回収
		}
	}
	return rc;
}

//再配置時（ターゲット指定時）のタッチパネル制御
static BOOL TpGoodsReputControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outReput)
{
	VecFx32 vec;
	BOOL rc;	//タッチパネルに触っているかを返す
	rc = FALSE;
	*outReput = FALSE;
	
	if ( sys.tp_trg ){	//トリガー
		if (!sys.cont){		//キーが全く押されていなければ
			//トリガーフラグオン
			ebew->BaseTp.TrgFlg = TRUE;
			//押したときに決定
			*outReput = TRUE;	//ターゲット決定
			TpUpdatePanelPos(fsys, &ebew->BaseTp, ebew->Panel);
		}//end if
		rc = TRUE;
	}else{
		ebew->BaseTp.TrgFlg = FALSE;
	}
			
	return rc;
}

//再配置時（設置時）のタッチパネル制御
static BOOL TpGoodsReputSetControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outReput)
{
	VecFx32 vec;
	BOOL rc;	//タッチパネルに触っているかを返す
	rc = FALSE;
	*outReput = FALSE;
	
	if ( sys.tp_trg ){	//トリガー
		if (!sys.cont){		//キーが全く押されていなければ
			//トリガーフラグオン
			ebew->BaseTp.TrgFlg = TRUE;

			TpUpdateGoodsPos(fsys, &(ebew->EditGoodsData), &ebew->BaseTp);
		
		}//end if
		rc = TRUE;
	}else if(sys.tp_cont){	//ベタ
		if (ebew->BaseTp.TrgFlg){
			TpUpdateGoodsPos(fsys, &(ebew->EditGoodsData), &ebew->BaseTp);			
		}
		rc = TRUE;
	}else{
		if (ebew->BaseTp.TrgFlg){
			ebew->BaseTp.TrgFlg = FALSE;
			//離したときに設置
			*outReput = TRUE;	//置く
		}
	}
	return rc;
}

static void InitBlinkData(BLINK_DATA *outBlinkData)
{
	outBlinkData->Count = 0;
	outBlinkData->CountMax = 0;
	outBlinkData->TargetIndex = 0xffff;
	outBlinkData->Vanish = FALSE;
	outBlinkData->Valid = FALSE;
}

static void SetBlinkTarget(const int inTarget, const int inCountMax, BLINK_DATA *outBlinkData)
{
	outBlinkData->Count = 0;
	outBlinkData->CountMax = inCountMax;
	outBlinkData->TargetIndex = inTarget;
	outBlinkData->Vanish = FALSE;
	outBlinkData->Valid = TRUE;
}

static void BlinkTarget(FIELDSYS_WORK *fsys, BLINK_DATA *ioBlinkData)
{
	M3DO_PTR ptr;
	if (!ioBlinkData->Valid){
		return;
	}
	//内部カウンタアップ
	ioBlinkData->Count++;
	if (ioBlinkData->Count >= ioBlinkData->CountMax){
		ioBlinkData->Count = 0;
		ioBlinkData->Vanish = (ioBlinkData->Vanish+1)%2;
		ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, ioBlinkData->TargetIndex);
		//バニッシュフラッグセット
		M3DO_SetVanish(ptr, ioBlinkData->Vanish);
	}
}

static void StopBlink(FIELDSYS_WORK *fsys, BLINK_DATA *inBlinkData)
{
	M3DO_PTR ptr;
	if (!inBlinkData->Valid){
		return;
	}
	ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, inBlinkData->TargetIndex);
	//バニッシュフラッグ落とす
	M3DO_SetVanish(ptr, FALSE);
}

static const int GetBlinkTarget(BLINK_DATA *inBlinkData)
{
	return inBlinkData->TargetIndex;
}

//グッズリストイベント
static BOOL GoodsListEvent(GMEVENT_CONTROL * event)
{
	BOOL rc;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);

	//エディットメインメニュー
	rc = BMENU_EditGoodsListControl(ebew->GoodsList);
	
	return FALSE;
}

static void InitBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	UG_BASE_PANEL *panel = (UG_BASE_PANEL*)(work);
	//パネル登録
	SetupPanel(panel);
}

static void BasePanelDummy(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	;
}

static void EndBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	UG_BASE_PANEL *panel = (UG_BASE_PANEL*)(work);
	//パネル削除
	ReleasePanel(panel);
}

static void DrawBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	UG_BASE_PANEL *panel = (UG_BASE_PANEL*)(work);	
	if (!(panel->DrawFlg)){
		return ;
	}
	{
		MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
		VecFx32 scale = {FX32_ONE,FX32_ONE,FX32_ONE};
		simple_3DModelDraw(	&panel->renderobj,
							&panel->trans,
							&rotate_tmp,
							&scale);
	}
}

//=============================================================================
/**
 * @file	comm_union_view.c
 * @brief	ユニオンルーム制御処理
 * @author	Akito Mori
 * @date    2005.12.15
 */
//=============================================================================

#ifdef PM_DEBUG
// 有効にするとDEBUGボタンでビーコン０番のIDを書き換えられる
//#define UNION_VIEW_DEBUG
#endif

// WMBssDecの内訳はcommuniocation.hにある

#include "common.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "system/pms_data.h"
#include "fieldsys.h"
#include "field/field.h"
#include "fieldobj.h"
#include "field_effect.h"
#include "savedata/savedata.h"
#include "savedata/friendlist.h"
#include "system/snd_tool.h"

#include "comm_command_field.h"
#include "comm_union.h"
#include "comm_union_view.h"
#include "comm_union_view_def.h"
#include "comm_union_beacon.h"


#define _TCB_UNIONVIEW_PRT	( 11 )

// ユニオンルームに存在する通信親の最大（グループの中心になるOBJの最大数）
#define UNIONROOM_PARENT_NUM	( 10 )


/*** 関数プロトタイプ ***/
static void commUnionViewTask( TCB_PTR tcb, void* work);
static void UnionObjView_Control( COMM_UNIONROOM_VIEW *view, COMM_UNIONROOM_WORK *cuw, FIELD_OBJ_SYS_PTR fldobjsys, FRIEND_LIST *friendlist );
static int  UnionObjView_ChildControl( COMM_UNIONROOM_VIEW *view, int no, WMBssDesc *beacon,  FRIEND_LIST *friendlist);
static void UnionObjView_Draw( COMM_UNIONROOM_VIEW *view, FIELD_OBJ_SYS_PTR  fldobjsys );
static void UnionViewObjWorkClear( COMM_UNIONROOM_VIEW *view);
static void Delete_Effect( OBJ_VIEW_WORK *objwork, int shadow_flag );
static void EffectControl( OBJ_VIEW_WORK *objwork);
static void UnionObjFall_Req( OBJ_VIEW_WORK *objview, FIELD_OBJ_PTR fldobj, int jiki_x, int jiki_z );
static void UnionObjRise_Req( OBJ_VIEW_WORK *objview, FIELD_OBJ_PTR fldobj );
static void UnionObj_EffectCheck(OBJ_VIEW_WORK *objwork, FIELD_OBJ_PTR fldobj);
static void FieldObjVanish( FIELD_OBJ_SYS_PTR fldobjsys, int start, int end );
static void UnionObjRequest( OBJ_VIEW_WORK objwork[], int idx,  int request  );

void UnionBoard_ChatDataDelete( UNION_CHAT_RINGBUF *ucr );
UNION_CHAT_RINGBUF *UnionBoard_ChatAllocInit( int heapID );
static void UnionChatAllFree( UNION_CHAT_RINGBUF *chatbuf);
static void UnionChatFree(UNION_CHAT *chat);
static void UnionChatAllocInit( UNION_CHAT_RINGBUF *chatbuf);
static void UnionChatInit(UNION_CHAT *chat);



//static void DebugObjFall( FIELD_OBJ_SYS_PTR fldobjsys );




COMM_UNIONROOM_VIEW *debug_view;
//==============================================================================
/**
 * OBJ制御処理初期化
 *
 * @param   cuw		
 *
 * @retval  COMM_UNIONROOM_VIEW *		
 */
//==============================================================================
COMM_UNIONROOM_VIEW *Comm_UnionRoomViewInit(COMM_UNIONROOM_WORK *cuw)
{
	COMM_UNIONROOM_VIEW *view;
    view = (COMM_UNIONROOM_VIEW*)sys_AllocMemory(HEAPID_UNIONROOM, sizeof(COMM_UNIONROOM_VIEW));

	MI_CpuClearFast( view, sizeof(COMM_UNIONROOM_VIEW) );
	view->cuw            = cuw;
	view->nowobj         = 1;
	view->viewTask       = TCB_Add(commUnionViewTask, view, _TCB_UNIONVIEW_PRT);
	view->fsys           = Union_FielsSysPtrGet(cuw);
	view->friendlist     = SaveData_Get(view->fsys->savedata, GMDATA_ID_FRIEND);
	view->jiki			 = view->fsys->player;

	sys_CreateHeapLo( HEAPID_WORLD, HEAPID_UNIONBOARD, 10000 );
	view->unionBoardChat = UnionBoard_ChatAllocInit(HEAPID_UNIONBOARD);
//	view->unionBoardChat = NULL;

	UnionRoomView_ObjInit( view );
//	OS_Printf("COMM_UNION_VIEW size = %d\n",sizeof(COMM_UNIONROOM_VIEW));

	debug_view = view;
	return view;
}


//==============================================================================
/**
 * @brief   一旦全員登る
 *
 * @param   view		
 *
 * @retval  none		
 */
//==============================================================================
void UnionRoomView_ObjAllRise( COMM_UNIONROOM_VIEW *view )
{
	int i;
	for(i=0;i<UNION_BEACON_OBJ_MAX+1;i++){
		if(view->objwork[i].appear!=OBJ_NO_APPEAR){
			view->objwork[i].request = OBJ_REQ_RISE;
		}
	}
	OS_Printf("\n");
}

//==============================================================================
/**
 * $brief   表示OBJ情報をクリアする
 *
 * @param   view		
 *
 * @retval  none		
 */
//==============================================================================
void UnionRoomView_ObjInit( COMM_UNIONROOM_VIEW *view )
{
	int i;
	for(i=0;i<UNION_BEACON_OBJ_MAX+1;i++){
		view->objwork[i].request        = OBJ_REQ_NO;
		view->objwork[i].appear         = OBJ_NO_APPEAR;
		view->objwork[i].friend         = 0;
//		view->objwork[i].effect_onflag  = 0;
		view->objwork[i].effect         = 0;
//		view->objwork[i].wait			= 0;
//		view->objwork[i].effect_ptr     = NULL;
//		view->objwork[i].shadow_ptr     = NULL;
		
	}

}

//==============================================================================
/**
 * ユニオンルーム描画処理ワークを解放する
 *
 * @param   view		
 *
 * @retval  none		
 */
//==============================================================================
void Comm_UnionRoomViewEnd(COMM_UNIONROOM_VIEW *view)
{
	TCB_Delete(view->viewTask);
	
	UnionBoard_ChatDataDelete( view->unionBoardChat );

	sys_DeleteHeap( HEAPID_UNIONBOARD );

	sys_FreeMemoryEz(view);
}


//==============================================================================
/**
 * $brief   ユニオンルームを見た目復帰を行う
 *
 * @param   cuw		
 * @param   view		
 *
 * @retval  none		
 */
//==============================================================================
void Comm_UnionRoomViewReturn( FIELDSYS_WORK *fsys )
{
	COMM_UNIONROOM_WORK *cuw   = fsys->union_work;
	COMM_UNIONROOM_VIEW *view  = fsys->union_view;

	

	if( CommStateIsUnionConnectSuccess() ==1 ){
		if(CommIsChildsConnecting()){
			view->objwork[Union_ConnectIndexGet(cuw)].request = OBJ_REQ_FALL_NOMOVE;
		}else{
			
		}
	}
}


static const arrowtbl[]={AC_WARP_UP, AC_WARP_DOWN};


//------------------------------------------------------------------
/**
 * ビーコンが見つかったらOBJを出現、いなくなったら消失させる処理
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void commUnionViewTask(TCB_PTR tcb, void* work)
{
	COMM_UNIONROOM_VIEW *view = (COMM_UNIONROOM_VIEW*)work;
	COMM_UNIONROOM_WORK *cuw  = view->cuw;

	FIELD_OBJ_PTR fldobj;
	int i;
	
	// イベント中でないことを確認
	if(!FieldEvent_Check(view->fsys)){

//		DebugObjFall(fsys->fldobjsys);

#ifdef UNION_VIEW_DEBUG
		if(sys.trg&PAD_BUTTON_DEBUG){
			view->objwork[0].trainerId = 0x12345667;
		}
#endif
		// ビーコン確認出現リクエスト発行処理
		UnionObjView_Control( view, cuw, view->fsys->fldobjsys, view->friendlist );
		
		// OBJ描画・話しかけ判定ON処理
		UnionObjView_Draw( view, view->fsys->fldobjsys );
		
		
		
	}
//	}else{	// イベント中はワークをクリアする
//		UnionRoomView_ObjInit( work );
//	}

}


//------------------------------------------------------------------
/**
 * $brief   子機コントロール・OBJコントルール
 *
 * @param   view		
 * @param   no		
 * @param   beacon		
 *
 * @retval  int			1:子機を落とした	0:落とさなかった
 */
//------------------------------------------------------------------
static int UnionObjView_ChildControl( COMM_UNIONROOM_VIEW *view, int no, WMBssDesc *beacon,  FRIEND_LIST *friendlist)
{
	int i,r,ret=0;
	_GF_BSS_DATA_INFO *gfbssdata;
	UNION_BEACON_STATE *beaconState;
	FIELD_OBJ_PTR fldobj;
	
	
	// ビーコンが無くなっているか、内容が書き換わっている場合は子機は全て引き上げる
	if(beacon==NULL ){
		for(i=0;i<4;i++){
			r = Union_GroupObjTable[no]+i;
			UnionObjRequest( view->objwork, r, OBJ_REQ_RISE );
		}
		return 0;
	}
	
	gfbssdata   = (_GF_BSS_DATA_INFO *)beacon->gameInfo.userGameInfo;
	beaconState = (UNION_BEACON_STATE*)gfbssdata->regulationBuff;

	if(view->objwork[no].trainerId!=gfbssdata->pokeID){
		for(i=0;i<4;i++){
			r = Union_GroupObjTable[no]+i;
			UnionObjRequest( view->objwork, r, OBJ_REQ_RISE );
		}
		return 0;
	}

	// 親がビーコン内に子機の存在をうめこんでいたら表示させる
	for(i=0;i<4;i++){
		r = Union_GroupObjTable[no]+i;
		switch(view->objwork[r].appear){

		// でていない
		case OBJ_NO_APPEAR:
			if(beaconState->c_face[i]!=0){
				view->objwork[r].request = OBJ_REQ_FALL_NOMOVE;
				view->objwork[r].view    = (beaconState->c_face[i] & 0x7f);	// 最上位ビットは性別なのでマスクする
				view->objwork[r].friend  = FriendList_IdFullCheck( friendlist, beaconState->c_id[i] );
				OS_Printf("子機登場 %d  OBJNO %d みため %d\n", i, r,beaconState->c_face[i]&0x7f);
//				OS_Printf("子機 %d番リクエスト objno = %d\n",i,view->objwork[r].friend );
				ret = 1;	// 子機をくっつけた
			}
			break;

		// 出現した
		case OBJ_OK:
			// ビーコン内の子機情報がなくなっていたら
			if(beaconState->c_face[i]==0){
				UnionObjRequest( view->objwork, r, OBJ_REQ_RISE );
				{
					int m;
					OS_Printf("child ");
					for(m=0;m<4;m++){
						OS_Printf("%d ",beaconState->c_face[m]);
					}
					OS_Printf("\n");
				}
				OS_Printf("離脱 %d  OBJNO %d\n", i, r);
//				view->objwork[r].request = OBJ_REQ_RISE;
			}else{
				ret = 1;
			}
			break;

		// 登りきった
		case OBJ_RISED:
			view->objwork[r].request = OBJ_REQ_NO;
			break;
		}
	}

	return ret;
}

//------------------------------------------------------------------
/**
 * @brief   OBJ管理構造体に予約宣言を入れる
 *
 * @param   objwork[]		
 * @param   idx		
 * @param   request		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionObjRequest( OBJ_VIEW_WORK objwork[], int idx,  int request  )
{
	u32 adr = (u32)debug_view->fsys;

	objwork[idx].request = request;

	if(adr!=(u32)debug_view->fsys){
		OS_Printf("i=%d, objptr = %x\n", idx, &objwork[idx]);

		GF_ASSERT(0);
	}
}


//------------------------------------------------------------------
/**
 * $brief   ユニオン親機・OBJコントルール
 *
 * @param   view		
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionObjView_Control( COMM_UNIONROOM_VIEW *view, COMM_UNIONROOM_WORK *cuw, FIELD_OBJ_SYS_PTR fldobjsys, FRIEND_LIST *friendlist )
{
	WMBssDesc     		*beacon;
	int  		  		i;
	_GF_BSS_DATA_INFO 	*gfbssdata;
	MYSTATUS 			*status;
	
	for(i=0;i<UNIONROOM_PARENT_NUM;i++){
		beacon    = Union_BeaconPtrGet(cuw,i);
		gfbssdata = (_GF_BSS_DATA_INFO *)beacon->gameInfo.userGameInfo;
		status    = (MYSTATUS*)gfbssdata->myStatusBuff;

		switch(view->objwork[i].appear){
		// OBJがいない場所のビーコンを受け取ったら出現させる
		case OBJ_NO_APPEAR:
			if(beacon!=NULL){
				view->objwork[i].view      = MyStatus_GetTrainerView( status );
				view->objwork[i].friend    = FriendList_IdFullCheck( friendlist, MyStatus_GetID( status ) );
				view->objwork[i].trainerId = gfbssdata->pokeID;

				// ビーコンで子機情報を持っているか監視
				if(UnionObjView_ChildControl( view, i, beacon, friendlist )){
						OS_Printf("%d 動かない登場\n",i);
						view->objwork[i].request = OBJ_REQ_FALL_NOMOVE;	// 動かない
				}else{
					OS_Printf("%d 動く登場を期待\n",i);
					view->objwork[i].request = OBJ_REQ_FALL;		// 動く
				}
				OS_TPrintf("親機%d リクエスト\n", i);
			}
			break;
		// 落ちきった
		case OBJ_OK:
			if(beacon==NULL || view->objwork[i].trainerId!=gfbssdata->pokeID){
				UnionObjRequest( view->objwork, i, OBJ_REQ_RISE );
//				view->objwork[i].request = OBJ_REQ_RISE;
			}
			if(UnionObjView_ChildControl( view, i, beacon, friendlist )){
				if(view->objwork[i].appearmode==OBJ_MOVE_WALK){
						OS_Printf("%d 動かなくなって再登場を期待\n",i);
						view->objwork[i].request = OBJ_REQ_RISE;	// 動かないになってくれる事を期待
				}
			}
			break;
		case OBJ_RISED:
				view->objwork[i].request = OBJ_REQ_NO;
			break;
		}
	}



}
//------------------------------------------------------------------
/**
 * $brief   ユニオンルーム内話しかけOBJ表示制御
 *
 * @param   view		
 * @param   fldobj		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionObjView_Draw( COMM_UNIONROOM_VIEW *view, FIELD_OBJ_SYS_PTR  fldobjsys )
{
	FIELD_OBJ_PTR fldobj;
	int i,x,z;
	
	x = Player_NowGPosXGet( view->jiki );
	z = Player_NowGPosZGet( view->jiki );
	
		// 50人全員分ぐるぐる回す
		for(i=0;i<50;i++){
			fldobj = FieldOBJSys_OBJIDSearch( fldobjsys, i+1);
			if( fldobj == NULL ){
				OS_Printf( "該当のIDが登録されていません ID=0x%x\n", i );
				GF_ASSERT( 0 );
			}

			switch(view->objwork[i].appear){
			// OBJがいない場所のビーコンを受け取ったら出現させる
			case OBJ_NO_APPEAR:
				if(FieldOBJ_AcmdSetCheck(fldobj)==TRUE){
					int request = view->objwork[i].request;
					if(request==OBJ_REQ_FALL || request == OBJ_REQ_FALL_NOMOVE){
						UnionObjFall_Req( &view->objwork[i], fldobj, x, z );
//						OS_Printf( "fall request obj id = %d\n", i+1);
					}
				}
				break;
			// 落ちてる
			case OBJ_FALL_WAIT:
				if(FieldOBJ_AcmdSetCheck(fldobj)==TRUE){			// 落ちきったら中に

					// メニュー呼び出し等で「落ちきった」はずなのにOBJ_REQ_RISEが入っている
					if(view->objwork[i].request==OBJ_REQ_RISE){
						// NO_APPEARからやりなおし
						view->objwork[i].appear  = OBJ_NO_APPEAR;
						view->objwork[i].request = OBJ_REQ_NO;
						Delete_Effect( &view->objwork[i], 1 );

						continue;
					}

					FieldOBJ_AcmdEnd(fldobj);
					FieldOBJ_StatusBitSet_TalkOFF( fldobj, FALSE );	// 話しかけられるようにフラグ変更
			
					// 一人で降りてくるときは、その後歩く
					if(view->objwork[i].request==OBJ_REQ_FALL && view->objwork[i].appearmode==OBJ_MOVE_STAND){
						OS_Printf("%d あるかせる\n",i);
					 	FieldOBJ_MoveCodeChange( fldobj, MV_RND );		// 移動開始
					 	FieldOBJ_MoveLimitXSet( fldobj, 1);				// 3x3の範囲で
					 	FieldOBJ_MoveLimitZSet( fldobj, 1);
					 	view->objwork[i].appearmode = OBJ_MOVE_WALK;
					}

					// 落下リクエスト解除
					view->objwork[i].appear  = OBJ_OK;
					view->objwork[i].request = OBJ_REQ_NO;

				}
				break;
			// 話しかけられる
			case OBJ_OK:
				if(FieldOBJ_AcmdSetCheck(fldobj)==TRUE){
//					if(sys.trg&PAD_BUTTON_A){
					// サブ画面でチャットをタッチされたら赤枠を出す
					UnionObj_EffectCheck(&view->objwork[i], fldobj);
					
					// さよならリクエスト
					if(view->objwork[i].request==OBJ_REQ_RISE){
						OS_Printf("上へのぼらせるリクエスト %d\n",i);
						UnionObjRise_Req( &view->objwork[i], fldobj );
					}
					// エフェクト管理
					EffectControl( &view->objwork[i] );
				}
				break;
			// 登ってる
			case OBJ_RISE_WAIT:
				if(FieldOBJ_AcmdSetCheck(fldobj)==TRUE){			// 登りきった
					FieldOBJ_AcmdEnd(fldobj);
					view->objwork[i].appear  = OBJ_RISED;
					view->objwork[i].request = OBJ_REQ_NO;
					view->objwork[i].appearmode = OBJ_MOVE_STAND;
					FieldOBJ_StatusBitSet_Vanish(fldobj,TRUE);		// 隠す
					FieldOBJ_StatusBitSet_FellowHit(fldobj,FALSE);	// 当たり判定もなくす
				}
				break;
			// 登りきった
			case OBJ_RISED:
				view->objwork[i].appear = OBJ_NO_APPEAR;
				break;

			}
		}
	// 主人公用の処理
	UnionObj_EffectCheck( &view->objwork[50], Player_FieldOBJGet(view->jiki) );
	EffectControl( &view->objwork[50] );

}

//------------------------------------------------------------------
/**
 * $brief   OBJ表示管理ワーククリア
 *
 * @param   view		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionViewObjWorkClear( COMM_UNIONROOM_VIEW *view)
{
	int i;
	
	for(i=0;i<UNION_BEACON_OBJ_MAX+1;i++){
		view->objwork[i].appear = OBJ_NO_APPEAR;
	}
}
//------------------------------------------------------------------
/**
 * $brief   人物の周りにだしているエフェクトを消す
 *
 * @param   effect_ptr		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Delete_Effect( OBJ_VIEW_WORK *objwork, int shadow_flag )
{
	// 赤枠消去
	if( objwork->effect_ptr != NULL){
		if(EOA_StatusBit_UseCheck( objwork->effect_ptr )){
			EOA_Delete( objwork->effect_ptr );
		}
		objwork->effect_ptr = NULL;
	}
	
	// 赤影・青影消去
	if(shadow_flag){
		if( objwork->shadow_ptr != NULL){
			if(EOA_StatusBit_UseCheck( objwork->shadow_ptr )){
				EOA_Delete( objwork->shadow_ptr );
			}
			objwork->shadow_ptr = NULL;
		}
	}
}

//------------------------------------------------------------------
/**
 * $brief   エフェクトの管理
 *
 * @param   objwork		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EffectControl( OBJ_VIEW_WORK *objwork)
{
	// エフェクトを帯びている場合
	if(objwork->effect_onflag){
		objwork->wait--;		// ウェイトを減らす
		if(objwork->wait==0){	
			// 終了時にエフェクト消去
			OS_Printf( "赤枠消去 objwork = %08x, effect = %08x\n",  objwork, objwork->effect_ptr);
			Delete_Effect( objwork, 0 );
			objwork->effect_onflag=0;
			
		}
	}
}



//------------------------------------------------------------------
/**
 * $brief   OBJを落とす処理
 *
 * @param   view		
 * @param   fldobjsys		
 * @param   no		
 * @param   gfbssdata		
 * @param   status		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionObjFall_Req( OBJ_VIEW_WORK *objview, FIELD_OBJ_PTR fldobj, int jiki_x, int jiki_z )
{
	int x,y,z;
	// 登場場所をマップ初期登録座標に設定しなおす
	x = FieldOBJ_InitPosGX_Get( fldobj );
	y = FieldOBJ_InitPosGY_Get( fldobj );
	z = FieldOBJ_InitPosGZ_Get( fldobj );

	// 自機の座標と落下座標が一致しているなら今回は落下させない
	if(x==jiki_x && z==jiki_z){
		return;
	}

	// 落ちてきたSE
	Snd_SePlay(SE_UNION_FALL);

	// 落下設定
	FieldOBJ_DrawReset( fldobj, objview->view );

	OS_Printf("再登録 消去枠=%08x\n", objview->effect_ptr);
	Delete_Effect( objview, 0 );

	// 登場初期位置取得
	FieldOBJ_GPosDirInit( fldobj, x, y, z, DIR_DOWN );
	
	FieldOBJ_DirDispSetForce( fldobj, DIR_DOWN     );
	FieldOBJ_AcmdSet(         fldobj, AC_WARP_DOWN );
	FieldOBJ_StatusBitSet_Vanish(    fldobj, FALSE );
	FieldOBJ_StatusBitSet_FellowHit( fldobj, TRUE  );
	objview->appear = OBJ_FALL_WAIT;

	// 知り合いなら赤い影、知り合いの知り合いなら青い影をつける
	if(objview->friend!=0){
		// SHADOW_RED・SHADOW_BLUEはfldeff_shadow.hを参照
		if(objview->friend==DIRECT_FRIEND){
			objview->shadow_ptr = FE_FldOBJShadowSet( fldobj, SHADOW_RED );
		}else if(objview->friend>=INDIRECT_FRIEND){
			objview->shadow_ptr = FE_FldOBJShadowSet( fldobj, SHADOW_BLUE );
		}
		objview->friend     = 0;
	}

}


//------------------------------------------------------------------
/**
 * $brief   OBJを登らせる処理
 *
 * @param   view		
 * @param   fldobjsys		
 * @param   no		
 * @param   gfbssdata		
 * @param   status		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionObjRise_Req( OBJ_VIEW_WORK *objview, FIELD_OBJ_PTR fldobj )
{

	FieldOBJ_AcmdSet(              fldobj, AC_WARP_UP );
	FieldOBJ_StatusBitSet_TalkOFF( fldobj, TRUE       );
 	FieldOBJ_MoveCodeChange(       fldobj, MV_DMY     );	// 移動ストップ

	// 終了時にエフェクト消去
	Delete_Effect( objview, 1 );
	objview->effect_onflag=0;
	objview->wait = 0;

	objview->appear = OBJ_RISE_WAIT;

}

//------------------------------------------------------------------
/**
 * $brief   下画面でタッチされた時に赤枠を出す
 *
 * @param   objwork		
 * @param   fldobj		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionObj_EffectCheck(OBJ_VIEW_WORK *objwork, FIELD_OBJ_PTR fldobj)
{
	// 下画面でフラグを立てられていたら
	if(objwork->effect==1){

		// 既にエフェクト起動していなければ赤枠エフェクトON
		if(objwork->effect_onflag==0){

			// 赤枠表示開始
			objwork->effect_ptr   = FE_FldOBJRedFrame_Add( fldobj );
			OS_Printf( "赤枠発生 objwork = %08x, effect = %08x\n",  fldobj, objwork->effect_ptr);

//			objwork->effect_ptr   = FE_FldOBJShadowSet( fldobj, SHADOW_RED );
//			FieldOBJ_AcmdSet(fldobj, AC_MARK_GYOE);
			objwork->wait          = 30;
			objwork->effect        = 0;
			objwork->effect_onflag = 1;
		}
	}


}


//------------------------------------------------------------------
/**
 * @brief   ユニオンＯＢＪの表示済み情報をすべて初期化する
 *
 * @param   fldobjsys	
 * @param   start		
 * @param   end			
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FieldObjVanish( FIELD_OBJ_SYS_PTR fldobjsys, int start, int end )
{
	int i;
	FIELD_OBJ_PTR fldobj;

	for(i=start; i<end;i++){
		fldobj = FieldOBJSys_OBJIDSearch(fldobjsys, i);
		if( fldobj == NULL ){
			OS_Printf( "該当のIDが登録されていません ID=0x%x\n", i );
			GF_ASSERT( 0 );
		}


		// 表示をOFF
		FieldOBJ_StatusBitSet_Vanish(fldobj,TRUE);
		// 当たり判定をOFF
		FieldOBJ_StatusBitSet_FellowHit(fldobj,FALSE);
		// 話しかけ判定をOFF
		FieldOBJ_StatusBitSet_TalkOFF( fldobj, TRUE );
	}
}

//==============================================================================
/**
 * 初期化時にすべてのOBJを隠す
 *
 * @param   fldobj		
 *
 * @retval  none		
 */
//==============================================================================
void Union_BeaconObjAllVanish( FIELD_OBJ_SYS_PTR fldobjsys, COMM_UNIONROOM_VIEW *view )
{
	FIELD_OBJ_PTR fldobj;
	OBJ_VIEW_WORK *objview;
	
	fldobj = FieldOBJSys_OBJIDSearch(fldobjsys, 0);
	if( fldobj == NULL ){
		GF_ASSERT( 0 );
	}

	if(FieldOBJ_AcmdSetCheck(fldobj)==TRUE){

		// 通信はしていない時
		if(CommStateIsUnionParentConnectSuccess() || CommStateIsUnionConnectSuccess()){
			int i;
			for(i=0;i<UNIONROOM_PARENT_NUM;i++){
				objview = &view->objwork[i];
				if(objview->appear!=OBJ_REQ_FALL){
					continue;
				}
				fldobj = FieldOBJSys_OBJIDSearch(fldobjsys, i+1);
				if( fldobj == NULL ){
					OS_Printf( "該当のIDが登録されていません ID=0x%x\n", i );
					GF_ASSERT( 0 );
				}

				// 落下設定
				//見た目変更
				FieldOBJ_DrawReset( fldobj, objview->view );
	
				FieldOBJ_DirDispSetForce( fldobj, DIR_DOWN     );
				FieldOBJ_AcmdSet(         fldobj, AC_WARP_DOWN );
				FieldOBJ_StatusBitSet_Vanish(    fldobj, FALSE );
				FieldOBJ_StatusBitSet_FellowHit( fldobj, TRUE  );
				objview->appear = OBJ_FALL_WAIT;

				// 知り合いなら赤い影、知り合いの知り合いなら青い影をつける
				if(objview->friend!=0){
					// SHADOW_RED・SHADOW_BLUEはfldeff_shadow.hを参照
					if(objview->friend==DIRECT_FRIEND){
						objview->shadow_ptr = FE_FldOBJShadowSet( fldobj, SHADOW_RED );
					}else if(objview->friend>=INDIRECT_FRIEND){
						objview->shadow_ptr = FE_FldOBJShadowSet( fldobj, SHADOW_BLUE );
					}
					objview->friend     = 0;
				}
			}
			FieldObjVanish( fldobjsys, 11,51);
		}else{
			FieldObjVanish( fldobjsys, 1, 51 );
		}
	}
}

//------------------------------------------------------------------
/**
 * ユニオンメッセージ初期化
 *
 * @param   fifo	UNION_CHAT構造体のポインタ
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void UnionChatInit(UNION_CHAT *chat)
{
	chat->name    = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, HEAPID_UNIONBOARD );
	chat->message = NULL;
	chat->friend  = NULL;
	PMSDAT_Init( &chat->PmsData, 0 );
	chat->sex     = 0;
	chat->id      = 0;
}

//------------------------------------------------------------------
/**
 * $brief   まとめて初期化
 *
 * @param   chatbuf 
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void UnionChatAllocInit( UNION_CHAT_RINGBUF *chatbuf)
{
	int i;
	for(i=0;i<UNION_CHAT_MAX;i++){
		UnionChatInit( &chatbuf->mes[i] );
	}
	chatbuf->num   = 0;
	chatbuf->start = 0;
}


//------------------------------------------------------------------
/**
 * $brief   メッセージ用STRBUF解放
 *
 * @param   message		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionChatFree(UNION_CHAT *chat)
{
	// 名前領域は必ず確保しているので解放
	sys_FreeMemoryEz( chat->name );

	// 文字列バッファを確保している場合は解放する
	if(chat->message!=NULL){
		STRBUF_Delete(chat->message);
	}
	if(chat->friend!=NULL){
		STRBUF_Delete(chat->friend);
	}
}

//------------------------------------------------------------------
/**
 * $brief   ユニオンチャットリングバッファをまとめて解放
 *
 * @param   messages		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionChatAllFree( UNION_CHAT_RINGBUF *chatbuf)
{
	int i;
	
	for(i=0;i<UNION_CHAT_MAX;i++){
		UnionChatFree( &chatbuf->mes[i] );
	}
	
}


//==============================================================================
/**
 * @brief   ユニオンチャット領域確保（comm_union_view.cで呼ばれる）
 *
 * @param   heapID		
 *
 * @retval  UNION_CHAT_RINGBUF *		
 */
//==============================================================================
UNION_CHAT_RINGBUF *UnionBoard_ChatAllocInit( int heapID )
{
	// 領域確保
	UNION_CHAT_RINGBUF *ucr = sys_AllocMemory( heapID, sizeof(UNION_CHAT_RINGBUF) );

	// 初期化
	UnionChatAllocInit( ucr );

	return ucr;
}

//==============================================================================
/**
 * @brief   ユニオンチャット領域解放（comm_union_view.cで呼ばれる）
 *
 * @param   ucr		
 *
 * @retval  none		
 */
//==============================================================================
void UnionBoard_ChatDataDelete( UNION_CHAT_RINGBUF *ucr )
{
	// チャットデータ個別解放
	UnionChatAllFree( ucr );

	// チャット領域解放
	sys_FreeMemoryEz( ucr );
}


#if 0
static debug_obj_count=1;

static void DebugObjFall( FIELD_OBJ_SYS_PTR fldobjsys )
{
	FIELD_OBJ_PTR fldobj = FieldOBJSys_OBJIDSearch(fldobjsys, debug_obj_count );
	if(sys.trg&PAD_BUTTON_Y){
		FieldOBJ_DirDispSetForce( fldobj, DIR_DOWN );
		FieldOBJ_AcmdSet(fldobj, AC_WARP_DOWN);
		FieldOBJ_StatusBitSet_Vanish(fldobj,FALSE);
		FieldOBJ_StatusBitSet_FellowHit(fldobj,TRUE);
		debug_obj_count++;
	}
}
#endif

//=============================================================================
/**
 * @file	comm_union_view.c
 * @brief	���j�I�����[�����䏈��
 * @author	Akito Mori
 * @date    2005.12.15
 */
//=============================================================================

#ifdef PM_DEBUG
// �L���ɂ����DEBUG�{�^���Ńr�[�R���O�Ԃ�ID��������������
//#define UNION_VIEW_DEBUG
#endif

// WMBssDec�̓����communiocation.h�ɂ���

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

// ���j�I�����[���ɑ��݂���ʐM�e�̍ő�i�O���[�v�̒��S�ɂȂ�OBJ�̍ő吔�j
#define UNIONROOM_PARENT_NUM	( 10 )


/*** �֐��v���g�^�C�v ***/
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
 * OBJ���䏈��������
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
 * @brief   ��U�S���o��
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
 * $brief   �\��OBJ�����N���A����
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
 * ���j�I�����[���`�揈�����[�N���������
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
 * $brief   ���j�I�����[���������ڕ��A���s��
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
 * �r�[�R��������������OBJ���o���A���Ȃ��Ȃ�������������鏈��
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
	
	// �C�x���g���łȂ����Ƃ��m�F
	if(!FieldEvent_Check(view->fsys)){

//		DebugObjFall(fsys->fldobjsys);

#ifdef UNION_VIEW_DEBUG
		if(sys.trg&PAD_BUTTON_DEBUG){
			view->objwork[0].trainerId = 0x12345667;
		}
#endif
		// �r�[�R���m�F�o�����N�G�X�g���s����
		UnionObjView_Control( view, cuw, view->fsys->fldobjsys, view->friendlist );
		
		// OBJ�`��E�b����������ON����
		UnionObjView_Draw( view, view->fsys->fldobjsys );
		
		
		
	}
//	}else{	// �C�x���g���̓��[�N���N���A����
//		UnionRoomView_ObjInit( work );
//	}

}


//------------------------------------------------------------------
/**
 * $brief   �q�@�R���g���[���EOBJ�R���g���[��
 *
 * @param   view		
 * @param   no		
 * @param   beacon		
 *
 * @retval  int			1:�q�@�𗎂Ƃ���	0:���Ƃ��Ȃ�����
 */
//------------------------------------------------------------------
static int UnionObjView_ChildControl( COMM_UNIONROOM_VIEW *view, int no, WMBssDesc *beacon,  FRIEND_LIST *friendlist)
{
	int i,r,ret=0;
	_GF_BSS_DATA_INFO *gfbssdata;
	UNION_BEACON_STATE *beaconState;
	FIELD_OBJ_PTR fldobj;
	
	
	// �r�[�R���������Ȃ��Ă��邩�A���e������������Ă���ꍇ�͎q�@�͑S�Ĉ����グ��
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

	// �e���r�[�R�����Ɏq�@�̑��݂����߂���ł�����\��������
	for(i=0;i<4;i++){
		r = Union_GroupObjTable[no]+i;
		switch(view->objwork[r].appear){

		// �łĂ��Ȃ�
		case OBJ_NO_APPEAR:
			if(beaconState->c_face[i]!=0){
				view->objwork[r].request = OBJ_REQ_FALL_NOMOVE;
				view->objwork[r].view    = (beaconState->c_face[i] & 0x7f);	// �ŏ�ʃr�b�g�͐��ʂȂ̂Ń}�X�N����
				view->objwork[r].friend  = FriendList_IdFullCheck( friendlist, beaconState->c_id[i] );
				OS_Printf("�q�@�o�� %d  OBJNO %d �݂��� %d\n", i, r,beaconState->c_face[i]&0x7f);
//				OS_Printf("�q�@ %d�ԃ��N�G�X�g objno = %d\n",i,view->objwork[r].friend );
				ret = 1;	// �q�@����������
			}
			break;

		// �o������
		case OBJ_OK:
			// �r�[�R�����̎q�@��񂪂Ȃ��Ȃ��Ă�����
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
				OS_Printf("���E %d  OBJNO %d\n", i, r);
//				view->objwork[r].request = OBJ_REQ_RISE;
			}else{
				ret = 1;
			}
			break;

		// �o�肫����
		case OBJ_RISED:
			view->objwork[r].request = OBJ_REQ_NO;
			break;
		}
	}

	return ret;
}

//------------------------------------------------------------------
/**
 * @brief   OBJ�Ǘ��\���̂ɗ\��錾������
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
 * $brief   ���j�I���e�@�EOBJ�R���g���[��
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
		// OBJ�����Ȃ��ꏊ�̃r�[�R�����󂯎������o��������
		case OBJ_NO_APPEAR:
			if(beacon!=NULL){
				view->objwork[i].view      = MyStatus_GetTrainerView( status );
				view->objwork[i].friend    = FriendList_IdFullCheck( friendlist, MyStatus_GetID( status ) );
				view->objwork[i].trainerId = gfbssdata->pokeID;

				// �r�[�R���Ŏq�@���������Ă��邩�Ď�
				if(UnionObjView_ChildControl( view, i, beacon, friendlist )){
						OS_Printf("%d �����Ȃ��o��\n",i);
						view->objwork[i].request = OBJ_REQ_FALL_NOMOVE;	// �����Ȃ�
				}else{
					OS_Printf("%d �����o�������\n",i);
					view->objwork[i].request = OBJ_REQ_FALL;		// ����
				}
				OS_TPrintf("�e�@%d ���N�G�X�g\n", i);
			}
			break;
		// ����������
		case OBJ_OK:
			if(beacon==NULL || view->objwork[i].trainerId!=gfbssdata->pokeID){
				UnionObjRequest( view->objwork, i, OBJ_REQ_RISE );
//				view->objwork[i].request = OBJ_REQ_RISE;
			}
			if(UnionObjView_ChildControl( view, i, beacon, friendlist )){
				if(view->objwork[i].appearmode==OBJ_MOVE_WALK){
						OS_Printf("%d �����Ȃ��Ȃ��čēo�������\n",i);
						view->objwork[i].request = OBJ_REQ_RISE;	// �����Ȃ��ɂȂ��Ă���鎖������
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
 * $brief   ���j�I�����[�����b������OBJ�\������
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
	
		// 50�l�S�������邮���
		for(i=0;i<50;i++){
			fldobj = FieldOBJSys_OBJIDSearch( fldobjsys, i+1);
			if( fldobj == NULL ){
				OS_Printf( "�Y����ID���o�^����Ă��܂��� ID=0x%x\n", i );
				GF_ASSERT( 0 );
			}

			switch(view->objwork[i].appear){
			// OBJ�����Ȃ��ꏊ�̃r�[�R�����󂯎������o��������
			case OBJ_NO_APPEAR:
				if(FieldOBJ_AcmdSetCheck(fldobj)==TRUE){
					int request = view->objwork[i].request;
					if(request==OBJ_REQ_FALL || request == OBJ_REQ_FALL_NOMOVE){
						UnionObjFall_Req( &view->objwork[i], fldobj, x, z );
//						OS_Printf( "fall request obj id = %d\n", i+1);
					}
				}
				break;
			// �����Ă�
			case OBJ_FALL_WAIT:
				if(FieldOBJ_AcmdSetCheck(fldobj)==TRUE){			// �����������璆��

					// ���j���[�Ăяo�����Łu�����������v�͂��Ȃ̂�OBJ_REQ_RISE�������Ă���
					if(view->objwork[i].request==OBJ_REQ_RISE){
						// NO_APPEAR������Ȃ���
						view->objwork[i].appear  = OBJ_NO_APPEAR;
						view->objwork[i].request = OBJ_REQ_NO;
						Delete_Effect( &view->objwork[i], 1 );

						continue;
					}

					FieldOBJ_AcmdEnd(fldobj);
					FieldOBJ_StatusBitSet_TalkOFF( fldobj, FALSE );	// �b����������悤�Ƀt���O�ύX
			
					// ��l�ō~��Ă���Ƃ��́A���̌����
					if(view->objwork[i].request==OBJ_REQ_FALL && view->objwork[i].appearmode==OBJ_MOVE_STAND){
						OS_Printf("%d ���邩����\n",i);
					 	FieldOBJ_MoveCodeChange( fldobj, MV_RND );		// �ړ��J�n
					 	FieldOBJ_MoveLimitXSet( fldobj, 1);				// 3x3�͈̔͂�
					 	FieldOBJ_MoveLimitZSet( fldobj, 1);
					 	view->objwork[i].appearmode = OBJ_MOVE_WALK;
					}

					// �������N�G�X�g����
					view->objwork[i].appear  = OBJ_OK;
					view->objwork[i].request = OBJ_REQ_NO;

				}
				break;
			// �b����������
			case OBJ_OK:
				if(FieldOBJ_AcmdSetCheck(fldobj)==TRUE){
//					if(sys.trg&PAD_BUTTON_A){
					// �T�u��ʂŃ`���b�g���^�b�`���ꂽ��Ԙg���o��
					UnionObj_EffectCheck(&view->objwork[i], fldobj);
					
					// ����Ȃ烊�N�G�X�g
					if(view->objwork[i].request==OBJ_REQ_RISE){
						OS_Printf("��ւ̂ڂ点�郊�N�G�X�g %d\n",i);
						UnionObjRise_Req( &view->objwork[i], fldobj );
					}
					// �G�t�F�N�g�Ǘ�
					EffectControl( &view->objwork[i] );
				}
				break;
			// �o���Ă�
			case OBJ_RISE_WAIT:
				if(FieldOBJ_AcmdSetCheck(fldobj)==TRUE){			// �o�肫����
					FieldOBJ_AcmdEnd(fldobj);
					view->objwork[i].appear  = OBJ_RISED;
					view->objwork[i].request = OBJ_REQ_NO;
					view->objwork[i].appearmode = OBJ_MOVE_STAND;
					FieldOBJ_StatusBitSet_Vanish(fldobj,TRUE);		// �B��
					FieldOBJ_StatusBitSet_FellowHit(fldobj,FALSE);	// �����蔻����Ȃ���
				}
				break;
			// �o�肫����
			case OBJ_RISED:
				view->objwork[i].appear = OBJ_NO_APPEAR;
				break;

			}
		}
	// ��l���p�̏���
	UnionObj_EffectCheck( &view->objwork[50], Player_FieldOBJGet(view->jiki) );
	EffectControl( &view->objwork[50] );

}

//------------------------------------------------------------------
/**
 * $brief   OBJ�\���Ǘ����[�N�N���A
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
 * $brief   �l���̎���ɂ����Ă���G�t�F�N�g������
 *
 * @param   effect_ptr		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Delete_Effect( OBJ_VIEW_WORK *objwork, int shadow_flag )
{
	// �Ԙg����
	if( objwork->effect_ptr != NULL){
		if(EOA_StatusBit_UseCheck( objwork->effect_ptr )){
			EOA_Delete( objwork->effect_ptr );
		}
		objwork->effect_ptr = NULL;
	}
	
	// �ԉe�E�e����
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
 * $brief   �G�t�F�N�g�̊Ǘ�
 *
 * @param   objwork		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EffectControl( OBJ_VIEW_WORK *objwork)
{
	// �G�t�F�N�g��ттĂ���ꍇ
	if(objwork->effect_onflag){
		objwork->wait--;		// �E�F�C�g�����炷
		if(objwork->wait==0){	
			// �I�����ɃG�t�F�N�g����
			OS_Printf( "�Ԙg���� objwork = %08x, effect = %08x\n",  objwork, objwork->effect_ptr);
			Delete_Effect( objwork, 0 );
			objwork->effect_onflag=0;
			
		}
	}
}



//------------------------------------------------------------------
/**
 * $brief   OBJ�𗎂Ƃ�����
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
	// �o��ꏊ���}�b�v�����o�^���W�ɐݒ肵�Ȃ���
	x = FieldOBJ_InitPosGX_Get( fldobj );
	y = FieldOBJ_InitPosGY_Get( fldobj );
	z = FieldOBJ_InitPosGZ_Get( fldobj );

	// ���@�̍��W�Ɨ������W����v���Ă���Ȃ獡��͗��������Ȃ�
	if(x==jiki_x && z==jiki_z){
		return;
	}

	// �����Ă���SE
	Snd_SePlay(SE_UNION_FALL);

	// �����ݒ�
	FieldOBJ_DrawReset( fldobj, objview->view );

	OS_Printf("�ēo�^ �����g=%08x\n", objview->effect_ptr);
	Delete_Effect( objview, 0 );

	// �o�ꏉ���ʒu�擾
	FieldOBJ_GPosDirInit( fldobj, x, y, z, DIR_DOWN );
	
	FieldOBJ_DirDispSetForce( fldobj, DIR_DOWN     );
	FieldOBJ_AcmdSet(         fldobj, AC_WARP_DOWN );
	FieldOBJ_StatusBitSet_Vanish(    fldobj, FALSE );
	FieldOBJ_StatusBitSet_FellowHit( fldobj, TRUE  );
	objview->appear = OBJ_FALL_WAIT;

	// �m�荇���Ȃ�Ԃ��e�A�m�荇���̒m�荇���Ȃ���e������
	if(objview->friend!=0){
		// SHADOW_RED�ESHADOW_BLUE��fldeff_shadow.h���Q��
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
 * $brief   OBJ��o�点�鏈��
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
 	FieldOBJ_MoveCodeChange(       fldobj, MV_DMY     );	// �ړ��X�g�b�v

	// �I�����ɃG�t�F�N�g����
	Delete_Effect( objview, 1 );
	objview->effect_onflag=0;
	objview->wait = 0;

	objview->appear = OBJ_RISE_WAIT;

}

//------------------------------------------------------------------
/**
 * $brief   ����ʂŃ^�b�`���ꂽ���ɐԘg���o��
 *
 * @param   objwork		
 * @param   fldobj		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionObj_EffectCheck(OBJ_VIEW_WORK *objwork, FIELD_OBJ_PTR fldobj)
{
	// ����ʂŃt���O�𗧂Ă��Ă�����
	if(objwork->effect==1){

		// ���ɃG�t�F�N�g�N�����Ă��Ȃ���ΐԘg�G�t�F�N�gON
		if(objwork->effect_onflag==0){

			// �Ԙg�\���J�n
			objwork->effect_ptr   = FE_FldOBJRedFrame_Add( fldobj );
			OS_Printf( "�Ԙg���� objwork = %08x, effect = %08x\n",  fldobj, objwork->effect_ptr);

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
 * @brief   ���j�I���n�a�i�̕\���ςݏ������ׂď���������
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
			OS_Printf( "�Y����ID���o�^����Ă��܂��� ID=0x%x\n", i );
			GF_ASSERT( 0 );
		}


		// �\����OFF
		FieldOBJ_StatusBitSet_Vanish(fldobj,TRUE);
		// �����蔻���OFF
		FieldOBJ_StatusBitSet_FellowHit(fldobj,FALSE);
		// �b�����������OFF
		FieldOBJ_StatusBitSet_TalkOFF( fldobj, TRUE );
	}
}

//==============================================================================
/**
 * ���������ɂ��ׂĂ�OBJ���B��
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

		// �ʐM�͂��Ă��Ȃ���
		if(CommStateIsUnionParentConnectSuccess() || CommStateIsUnionConnectSuccess()){
			int i;
			for(i=0;i<UNIONROOM_PARENT_NUM;i++){
				objview = &view->objwork[i];
				if(objview->appear!=OBJ_REQ_FALL){
					continue;
				}
				fldobj = FieldOBJSys_OBJIDSearch(fldobjsys, i+1);
				if( fldobj == NULL ){
					OS_Printf( "�Y����ID���o�^����Ă��܂��� ID=0x%x\n", i );
					GF_ASSERT( 0 );
				}

				// �����ݒ�
				//�����ڕύX
				FieldOBJ_DrawReset( fldobj, objview->view );
	
				FieldOBJ_DirDispSetForce( fldobj, DIR_DOWN     );
				FieldOBJ_AcmdSet(         fldobj, AC_WARP_DOWN );
				FieldOBJ_StatusBitSet_Vanish(    fldobj, FALSE );
				FieldOBJ_StatusBitSet_FellowHit( fldobj, TRUE  );
				objview->appear = OBJ_FALL_WAIT;

				// �m�荇���Ȃ�Ԃ��e�A�m�荇���̒m�荇���Ȃ���e������
				if(objview->friend!=0){
					// SHADOW_RED�ESHADOW_BLUE��fldeff_shadow.h���Q��
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
 * ���j�I�����b�Z�[�W������
 *
 * @param   fifo	UNION_CHAT�\���̂̃|�C���^
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
 * $brief   �܂Ƃ߂ď�����
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
 * $brief   ���b�Z�[�W�pSTRBUF���
 *
 * @param   message		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionChatFree(UNION_CHAT *chat)
{
	// ���O�̈�͕K���m�ۂ��Ă���̂ŉ��
	sys_FreeMemoryEz( chat->name );

	// ������o�b�t�@���m�ۂ��Ă���ꍇ�͉������
	if(chat->message!=NULL){
		STRBUF_Delete(chat->message);
	}
	if(chat->friend!=NULL){
		STRBUF_Delete(chat->friend);
	}
}

//------------------------------------------------------------------
/**
 * $brief   ���j�I���`���b�g�����O�o�b�t�@���܂Ƃ߂ĉ��
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
 * @brief   ���j�I���`���b�g�̈�m�ہicomm_union_view.c�ŌĂ΂��j
 *
 * @param   heapID		
 *
 * @retval  UNION_CHAT_RINGBUF *		
 */
//==============================================================================
UNION_CHAT_RINGBUF *UnionBoard_ChatAllocInit( int heapID )
{
	// �̈�m��
	UNION_CHAT_RINGBUF *ucr = sys_AllocMemory( heapID, sizeof(UNION_CHAT_RINGBUF) );

	// ������
	UnionChatAllocInit( ucr );

	return ucr;
}

//==============================================================================
/**
 * @brief   ���j�I���`���b�g�̈����icomm_union_view.c�ŌĂ΂��j
 *
 * @param   ucr		
 *
 * @retval  none		
 */
//==============================================================================
void UnionBoard_ChatDataDelete( UNION_CHAT_RINGBUF *ucr )
{
	// �`���b�g�f�[�^�ʉ��
	UnionChatAllFree( ucr );

	// �`���b�g�̈���
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

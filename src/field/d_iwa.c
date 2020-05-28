/**
 *	@file	d_iwa.c
 *	@brief	���V�f�o�b�O�p�\�[�X
 *	@author	Miyuki Iwasawa
 *	@date	04.12.04
 * */

#ifdef PM_DEBUG

#include "common.h"
#include "fld_bmp.h"
#include "fntsys.h"
#include "talk_msg.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/wipe.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"
#include "field/fieldsys.h"
#include "field/field.h"
#include "field/ev_mapchange.h"
#include "field/fieldmap.h"
#include "field/zonedata.h"
#include "field/field_event.h"
#include "field/field_matrix.h"
#include "field/fld_mailbox.h"
#include "field/b_tower_ev.h"
#include "fielddata/maptable/zone_id.h"
#include "application/townmap.h"
#include "application/mailtool.h"
#include "application/poru_tool.h"
#include "application/nutmixer.h"
#include "field/fld_nmixer.h"
#include "script.h"
#include "fielddata/script/poruto_scr_def.h"
#include "fielddata/script/d31r0201_def.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_miyuki.h"
#include "savedata/guinness.h"

#include "d_iwa.h"

extern void FieldBitMapWinCgxSet( GF_BGL_INI * ini );
extern void DebugWifiBTower_DummyDataMake(SAVEDATA* sv);

#define DW0_CGX	(1)
#define DW0_SX	(12)
#define DW0_SY	(14)
#define DW0_CGXNUM	(DW0_SX*DW0_SY)
#define DW0_PAL	(FLD_SYSFONT_PAL)

static const BMPWIN_DAT d_miyuki_BmpDat[] = {
 {GF_BGL_FRAME3_M,  1,  1, DW0_SX, DW0_SY, DW0_PAL, DW0_CGX },
 { 0xFF, 0, 0, 0, 0, 0, 0 },
};

static void DebugMenuExit(TCB_PTR tcb,void* work);
//tmap
static void DebugSub_TMapNormalInit(void* work);
static void DebugSub_TMapJumpInit(void* work);
static void DebugSub_TMapBGInit(void* work);

//mail system
static void DebugSubMenu_MailBoxCall(TCB_PTR tcb,void* work);
static void DebugSub_MailCreateInit(void* work);
static void DebugSub_MailViewInit(void* work);

//poruto
static void DebugSub_PoruCaseInit(void* work);
static void DebugSub_PorutoDataMake(void* work,int mode);

//nut mixer
static void DebugSub_NutMixerLocal(void* work);

//------------------------------------------------------------------
///	���j���[���X�g�f�[�^
//------------------------------------------------------------------
typedef struct{
	u32	str_id;
	u32	param;
}MENU_PARAM;

static const MENU_PARAM MiyukiMenuList[] = {
	{ msg_label_script,	 BMPLIST_RABEL},			//���x��01
	{ msg_tower_rndseed, 9},		//00:�^���[�����_���̂��˂����Ȃ蓯��
	{ msg_tower_roomf_clear, 10},		//00:�^���[Wifi���[���t���O�N���A
	{ msg_tower_guinness, 11},		//00:�^���[ �M�l�X�z�[���f�[�^���_�~�[�Ŗ��߂�
	{ msg_tower_wifidata, 12},		//00:�^���[ wifi�_�~�[�A�b�v�f�[�g�f�[�^�쐬 
	{ msg_tower_bpget, 13},		//00:�^���[ 500BP�Q�b�g
	{ msg_tower_bpget2, 14},		//00:�^���[ 9998BP�Q�b�g
	{ msg_label_tmap,	 BMPLIST_RABEL},			//���x��01
	{ msg_dtmapN, (u32)DebugSub_TMapNormalInit},	//00:���[���h�}�b�v
	{ msg_dtmapJ, (u32)DebugSub_TMapJumpInit},		//00:���[���h�}�b�v
	{ msg_dtmapB, (u32)DebugSub_TMapBGInit},		//00:���[���h�}�b�v
	{ msg_label_mail,	 BMPLIST_RABEL},			//���x��02
	{ msg_dmailV, 2},		//00:���[������
	{ msg_dmailC, 3},		//00:���[���쐬
	{ msg_label_poruto,	 BMPLIST_RABEL},			//���x��03
	{ msg_porucase,4},		//00:�|���g�P�[�X
	{ msg_poru_allmake,5},	//00:�|���g
	{ msg_poru_alldel,6},		//00:�|���g�P�[�X
	{ msg_label_nutmixer,	 BMPLIST_RABEL},			//���x��04
	{ msg_nmixer_local,7},		//00:�i�b�c�~�L�T�[���[�J��
	{ msg_nmixer_scr,8},		//00:�i�b�c�~�L�T�[�X�N���v�g
	{ msg_exit,		 0x00000001},		//00:����
	{ msg_label_end,	 BMPLIST_RABEL},			//���x��02
};

#define BLIST_NUM	NELEMS(MiyukiMenuList)

///	���X�g�V�X�e������̃R�[���o�b�N����s�\������
static void	InfoCallBack(BMPLIST_WORK* lw,u32 param,u8 y)
{
	if(param == BMPLIST_RABEL){
		BmpListTmpColorChange(lw,FBMP_COL_BLU_SDW,FBMP_COL_BLACK,FBMP_COL_BLUE);
	}else{
		BmpListTmpColorChange(lw,FBMP_COL_WHITE,FBMP_COL_BLACK,FBMP_COL_BLK_SDW);
	}
}

//------------------------------------------------------------------
///	���ڃ��X�g�f�[�^
//------------------------------------------------------------------
static const BMPLIST_HEADER DebugListHeader = {
	NULL,			//�\�������f�[�^�|�C���^
	NULL,				//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	InfoCallBack,		//�P�s���Ƃ̃R�[���o�b�N�֐�

	NULL,				//GF_BGL_BMPWIN�\���̃f�[�^�ւ̃|�C���^
	BLIST_NUM,			//���X�g���ڐ�
	6,					//�\���ő區�ڐ�
	2,					//���x���\���w���W
	12,					//���ڕ\���w���W
	1,					//�J�[�\���\���w���W
	2,					//�\���x���W
	FBMP_COL_WHITE,		//�����F
	FBMP_COL_BLACK,		//�w�i�F
	FBMP_COL_BLK_SDW,	//�����e�F
	0,					//�����Ԋu�w
	1,					//�����Ԋu�x
	BMPLIST_LRKEY_SKIP,	//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,		//�����w��
	0,					//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
	NULL,				//���[�N�|�C���^
};

//�v���g�^�C�v
void DebugMiyukiInit(void* fsys);
static void DebugMiyukiEnd(TCB_PTR tcb,void* work);

/**
 *	@brief	���X�g������
 */
void DebugMiyukiViewInit(_DebugIwaWork* wp,void* fsys,u8 list,u8 cursor)
{
	int i;

	const MENU_PARAM* menuParam = MiyukiMenuList;
	int	size = NELEMS(MiyukiMenuList);
	wp->fsys =fsys;
	
	//BMP�E�B���h�E������(FieldSys�̏������f�[�^���擾)
	wp->pBglIni = FieldBglIniGet(fsys);
	
	//�E�B���h�E�L�����N�^�Z�b�g
	FieldBitMapWinCgxSet(wp->pBglIni);

	GF_BGL_ScrFill(wp->pBglIni,GF_BGL_FRAME3_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_LoadScreenV_Req(wp->pBglIni,GF_BGL_FRAME3_M);

	//�N���A
	memset(&(wp->bmpwin),0,sizeof(GF_BGL_BMPWIN));
	wp->List = list;

	//BMPMAP���j���[�ǉ�
	wp->menulist = BMP_MENULIST_Create(size,HEAPID_BASE_DEBUG);
	GF_BGL_BmpWinAddEx(wp->pBglIni,&(wp->bmpwin),d_miyuki_BmpDat);

	if(menuParam != NULL){
		MSGDATA_MANAGER* msgman;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
					NARC_msg_debug_miyuki_dat,HEAPID_BASE_DEBUG);

		for(i = 0;i < size;i++){
			BMP_MENULIST_AddArchiveString(wp->menulist,
				msgman, menuParam[i].str_id, menuParam[i].param );
		}
		MSGMAN_Delete(msgman);
	}else{
		STRCODE	tmpbuf[128];
		STRBUF	*mstr = STRBUF_Create(128,HEAPID_BASE_DEBUG);
		for(i = 0;i < size;i++){
			PM_strclear(tmpbuf,EOM_,128);
			STRBUF_Clear(mstr);
			
			//�]�[�����擾
			if(ASCIIcode2DSuni(0,(u8*)ZoneData_GetZoneName(i+2),tmpbuf)){
				tmpbuf[0] = EOM_;
			}
			STRBUF_SetStringCode(mstr,tmpbuf);
			BMP_MENULIST_AddString(wp->menulist,mstr,i+2);
		}
		STRBUF_Delete(mstr);
	}
	
	//BMP���X�g�ݒ�
	memcpy(&(wp->bmplist_h),&DebugListHeader,sizeof(BMPLIST_HEADER));
	wp->Cursor = cursor;
	wp->bmplist_h.win = &(wp->bmpwin);
	wp->bmplist_h.list = wp->menulist;
	wp->bmplist_h.work = (void*)wp->blistWk;
	wp->bmplist_h.count = size;
	wp->blistWk = BmpListSet(&(wp->bmplist_h),wp->List,wp->Cursor,HEAPID_BASE_DEBUG);
}

/**
 *	@brief	���X�g���
 */
void DebugMiyukiViewEnd(_DebugIwaWork* wp)
{
	//BMPWIN�j��
	GF_BGL_BmpWinOff(&(wp->bmpwin));	//WindowOFF
	//BMP���X�g�̊J��
	BmpListExit(wp->blistWk,&(wp->List),&(wp->Cursor));	//���X�g�j��
	BMP_MENULIST_Delete(wp->menulist);	//���j���[������j��
	GF_BGL_BmpWinDel(&(wp->bmpwin));	//BMPWindowDel
}

/**
 *	�f�o�b�O�V�X�e��������
 *
 *	u8	DebugMiyukiInit(void* fsys)
 *
 *	@param	void* FLD_DEB_DAT�ւ̃|�C���^
 *	@return none
 */
void DebugMiyukiInit(void* fsys)
{
	TCB_PTR	pTcb = NULL;
	_DebugIwaWork *wp = NULL;
	GF_BGL_INI *ini = NULL;

	//�f�o�b�O�V�X�e���������m��
	wp = sys_AllocMemory(HEAPID_BASE_DEBUG,sizeof(_DebugIwaWork));

	if(wp == NULL){
		//���[�N���m�ۂł��Ȃ�Ή������Ȃ�
		OS_Printf("iwasawa debug menu create field\n");
		return;
	}
	memset(wp,0,sizeof(_DebugIwaWork));

	DebugMiyukiViewInit(wp,fsys,0,1);
	wp->seq = DMSEQ_FADEOUT;

	pTcb = TCB_Add(DebugMiyukiMain,wp,0);
}

//=============================================================================
/**
 *	�f�o�b�O�V�X�e���L�[�擾(���C���^�X�N)
 *	void DebugMiyukiMain(u8 id);
 *
 *	@param	tcb	TCB_PTR	�^�X�N�u���b�N�|�C���^	
 *	@param	work	�^�X�N���[�N�|�C���^	
 *	@return	none
 */
//=============================================================================
void DebugMiyukiMain(TCB_PTR tcb,void* work)
{
	s32	ret_code;
	TCB_FUNC	func;
	_DebugIwaWork	*wp;

	wp = (_DebugIwaWork*)work;

	ret_code = BmpListMain(wp->blistWk);

	//�L�[���씻��
	if(sys.trg & PAD_BUTTON_DECIDE){
		switch(ret_code){
		case BMPMENU_NULL:
		case BMPMENU_CANCEL:
			DebugMiyukiEnd(tcb,work);
			return;
		default:
			switch(ret_code){
			case 0:
				return;
			case 1:	//���j���[�I��
				DebugMiyukiEnd(tcb,work);
				return;
			case 2:	//���[��
			case 3:
				wp->ret_val = ret_code-1;
				DebugSubMenu_MailBoxCall(tcb,work);
				return;
			case 4:	//�|���g�P�[�X
				wp->UserFunc = DebugSub_PoruCaseInit;
				TCB_ChangeFunc(tcb,DebugMiyukiFuncCall);
				wp->func_mode = 2;
				return;
			case 5:	//�|���g���^��
				DebugSub_PorutoDataMake(wp,0);
				DebugMiyukiEnd(tcb,work);
				return;
			case 6:	//�|���g�����
				DebugSub_PorutoDataMake(wp,1);
				DebugMiyukiEnd(tcb,work);
				return;
			case 7:	//�i�b�c�~�L�T�[���[�J��
				wp->UserFunc = DebugSub_NutMixerLocal;
				TCB_ChangeFunc(tcb,DebugMiyukiFuncCall);
				wp->func_mode = 0;
				return;
			case 8:	//�i�b�c�~�L�T�[�X�N���v�g
				EventSet_Script(wp->fsys,SCRID_PORUTO_SCR,NULL);
				DebugMiyukiEnd(tcb,work);
				return;
			case 9:	//�^���[�X�N���v�g�@�����_���̎킢���Ȃ蓯��
				BtlTower_UpdateDayRndSeed(wp->fsys->savedata);
	//			EventSet_Script(wp->fsys,SCRID_TOWER_GATE_LOCAL_01,NULL);
//				EventSet_Script(wp->fsys,SCRID_D31R0201_GIRL2_01,NULL);
				DebugMiyukiEnd(tcb,work);
				return;
			case 10:	//�^���[ wifi���[���t���O�N���A
				TowerWifiData_ClearRoomDataFlag(
					SaveData_GetTowerWifiData(wp->fsys->savedata));
				DebugMiyukiEnd(tcb,work);
				return;
			case 11:	//�M�l�X�z�[���@�f�o�b�O�@�L�^��t
				DebugGNSRank_MakeDmyRankingData(
					SaveData_GetGuinnessData(wp->fsys->savedata));
				return;
			case 12:	//wifi�^���[�_�~�[�A�b�v�f�[�g�f�[�^�쐬
				DebugWifiBTower_DummyDataMake(wp->fsys->savedata);
				return;
			case 13:	//500BP�Q�b�g
				TowerScoreData_SetBattlePoint(
					SaveData_GetTowerScoreData(wp->fsys->savedata),500,BTWR_DATA_add);
				return;
			case 14:	//9998BP�Q�b�g
				TowerScoreData_SetBattlePoint(
					SaveData_GetTowerScoreData(wp->fsys->savedata),9998,BTWR_DATA_set);
				return;
			default:
				//�֐��|�C���^�ۑ�
				wp->UserFunc = (void*)ret_code;
				TCB_ChangeFunc(tcb,DebugMiyukiFuncCall);

				if(	ret_code == (u32)DebugSub_TMapNormalInit ||
					ret_code == (u32)DebugSub_TMapJumpInit ||
					ret_code == (u32)DebugSub_TMapBGInit){
					wp->func_mode = 1;
				}
			}
			return;
		}
		return;
	}
	//���j���[�L�����Z��
	if(sys.trg & PAD_BUTTON_B){
		DebugMiyukiEnd(tcb,work);
		return;
	}
}

/**
 *	@brief	�f�o�b�O���j���[�̏I������
 *
 *	�f�o�b�O���j���[�p���[�N�ƃ��X�g�̔j�����s��
 *	@param	tcb		TCB_PTR:�Ăяo�����^�X�N�u���b�N�ւ̃|�C���^
 *	@param	work	void*:�Ăяo�����^�X�N�u���b�N���[�N�ւ̃|�C���^
 */
static void DebugMiyukiEnd(TCB_PTR tcb,void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;

	DebugMiyukiViewEnd(wp);

	//�f�o�b�O���[�N�������J��
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);

	//OBJ���̓����~����
	FieldSystemProc_SeqHoldEnd();
	return;
}

#if 0
static void DebugMiyukiSubMenuWait(TCB_PTR tcb,void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;
	
	if(!wp->ret_val){
		return;
	}
	wp->ret_val = 0;
	//�f�o�b�O���j���[���A
	DebugMiyukiViewInit(wp,wp->fsys,wp->List,wp->Cursor);
	TCB_ChangeFunc(tcb,DebugMiyukiMain);
}
#endif
/**
 *	@brief	�f�o�b�O���j���[�����
 */
static void DebugMenuExit(TCB_PTR tcb,void* work)
{
	DebugMiyukiEnd(tcb,work);	
}

/**
 *	@brief	�f�o�b�O���j���[�@�^�E���}�b�v�Ăяo��
 */
//extern void FieldTMap_CallDataSet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,int mode);

static void* DebugTMapCall(FIELDSYS_WORK* fsys,u8 mode)
{
	TOWNMAP_PARAM * tp;
	tp = sys_AllocMemoryLo(HEAPID_BASE_DEBUG, sizeof(TOWNMAP_PARAM));

	FieldTMap_CallDataSet(fsys,tp,mode);
	FieldTMap_SetProc( fsys, tp );
	return tp;
}
/**
 *	@brief	�f�o�b�O���j���[�@�^�E���}�b�v�Ăяo���V�[�P���X������
 */
static void DebugSub_TMapNormalInit(void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;

	wp->subWork = DebugTMapCall(wp->fsys,TMAP_MNORMAL);
}
/**
 *	@brief	�f�o�b�O���j���[�@�^�E���}�b�v�Ăяo���V�[�P���X������
 */
static void DebugSub_TMapJumpInit(void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;

	wp->subWork = DebugTMapCall(wp->fsys,TMAP_MJUMP);
}
/**
 *	@brief	�f�o�b�O���j���[�@�^�E���}�b�v�Ăяo���V�[�P���X������
 */
static void DebugSub_TMapBGInit(void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;

	wp->subWork = DebugTMapCall(wp->fsys,TMAP_MBG);
}

static void DebugSubMenu_MailBoxCall(TCB_PTR tcb,void* work)
{
	_DebugIwaWork *wp  =(_DebugIwaWork*)work;
	
	//�f�o�b�O���j���[�E�B���h�E�j��
	DebugMiyukiViewEnd(wp);

	//���[���{�b�N�X�^�X�N�o�^
	MailBox_Call(wp->fsys,&(wp->ret_val));
	TCB_ChangeFunc(tcb,DebugMiyukiSubMenuWait);
	FieldSystemProc_SeqHold();
}

/**
 *	@brief	�f�o�b�O���j���[�@���[���쐬�Ăяo��
 */
static void DebugSub_MailCreateInit(void* work)
{
	_DebugIwaWork *wp  =(_DebugIwaWork*)work;

	wp->subWork =  FieldMailCreate_InitCall( wp->fsys ,
		MAILBLOCK_TEMOTI,0,0,HEAPID_BASE_DEBUG);
}

/**
 *	@brief	�f�o�b�O���j���[�@���[���`��Ăяo��
 */
static void DebugSub_MailViewInit(void* work)
{
	_DebugIwaWork *wp  = (_DebugIwaWork*)work;

	wp->subWork =  FieldMailView_InitCall(wp->fsys,
		MAILBLOCK_TEMOTI,0,HEAPID_BASE_DEBUG);
}

/**
 *	@brief	�f�o�b�O���j���[�@�|���g�P�[�X�Ăяo��
 */
static void DebugSub_PoruCaseInit(void* work)
{
	_DebugIwaWork *wp  = (_DebugIwaWork*)work;
	wp->subWork = FieldPorutoCase_InitCall(wp->fsys,HEAPID_BASE_DEBUG);
}

/**
 *	@brief	�f�o�b�O���j���[�@�|���g�f�[�^�쐬
 */
static void DebugSub_PorutoDataMake(void* work,int mode)
{
	_DebugIwaWork *wp  = (_DebugIwaWork*)work;
	PORUTO_BLOCK* block = NULL;

	block = SaveData_GetPorutoBlock(GameSystem_GetSaveData(wp->fsys));

	if(mode == 0){
		PorutoDebug_AddRndData(block,100);
	}else{
		PorutoDebug_AllDataDelete(block);
	}
}

/**
 *	@brief	�i�b�c�~�L�T�[�@���[�J��
 */
static void DebugSub_NutMixerLocal(void* work)
{
	_DebugIwaWork *wp  = (_DebugIwaWork*)work;
	wp->subWork = FieldNutMixer_InitCall(wp->fsys,NUTMIXER_CALL_LOCAL,HEAPID_BASE_DEBUG);
}

#endif	//PM_DEBUG

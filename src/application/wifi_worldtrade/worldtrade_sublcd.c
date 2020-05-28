//============================================================================================
/**
 * @file	worldtrade_sublcd.c
 * @bfief	���E�����T�u��ʏ���
 * @author	Akito Mori
 * @date	06.04.16
 */
//============================================================================================
#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_tr.h"
#include "gflib/touchpanel.h"
#include "gflib/tcb.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "system/bmp_menu.h"
#include "system/lib_pack.h"
#include "system/snd_tool.h"
#include "field/comm_union_beacon.h"

#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "../record/record.naix"			// �O���t�B�b�N�A�[�J�C�u��`


//==============================================================================
// �\���̒�`
//==============================================================================
typedef struct{
	int seq;
	int heroy;
	int sex;
	WORLDTRADE_WORK *wk;
}HERO_DEMO_WORK;


//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
static void HeroDemoTask(  TCB_PTR tcb, void *work  );
static void HeroReturnDemoTask(  TCB_PTR tcb, void *work  );
static void SetSubLcdObj_Pos( CLACT_WORK_PTR act, int x, int y );
static void HeroAnimeChange( HERO_DEMO_WORK *hdw, int animeno );
static void LoadFieldObjData( WORLDTRADE_WORK *wk );
static void TransFieldObjData( NNSG2dCharacterData *CharaData, NNSG2dPaletteData *PalData, int id, int view, int sex );
static int ObjAppearNoGet( int objno );



//==============================================================================
// �萔��`
//==============================================================================

#define HERO_START_POSX	( 128 )
#define HERO_START_POSY	( -40 )

#define HERO_LAND_POSY	( 160 )

#define HERO_STOP_POSY	( 130 )

#define OBJPOS1_X	( 128 )
#define OBJPOS2_X	(  88+8 )
#define OBJPOS3_X	( 168-8 )
#define OBJPOS4_X	(  56+8 )
#define OBJPOS5_X	( 200-8 )
#define OBJPOS6_X	(  40+8 )
#define OBJPOS7_X	( 216-8 )

#define OBJPOS1_Y	( 40 +16-2 )
#define OBJPOS2_Y	( 44 +16-5 )
#define OBJPOS3_Y	( 56 +16-2 )
#define OBJPOS4_Y	( 88 +16-2 )


#define FIELD_OBJ_NO_START			( 14 )
#define FIELD_OBJ_STAND_NO_START	( 17 )

// �l��OBJ�L�����O���t�B�b�N�t�@�C���̃o�C�g��
#define FIELDOBJ_NCG_SIZE	(256*256/2)

//==============================================================================
// �������ʂn�a�i�̍��W
//==============================================================================
static const u16 obj_postable[][2]={
	{ OBJPOS1_X,  OBJPOS1_Y },
	{ OBJPOS2_X,  OBJPOS2_Y },
	{ OBJPOS3_X,  OBJPOS2_Y },
	{ OBJPOS4_X,  OBJPOS3_Y },
	{ OBJPOS5_X,  OBJPOS3_Y },
	{ OBJPOS6_X,  OBJPOS4_Y },
	{ OBJPOS7_X,  OBJPOS4_Y },
};


//==============================================================================
/**
 * @brief   ����ʃZ���A�N�^�[�\���o�^
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SubLcdActorAdd( WORLDTRADE_WORK *wk, int sex )
{
	CLACT_ADD add;
	int i;

	
	// ���łɃt�B�[���h�n�a�i�O���t�B�b�N�ǂݍ���
	LoadFieldObjData( wk );

	WorldTrade_MakeCLACT( &add,  wk, &wk->clActHeader_sub, NNS_G2D_VRAM_TYPE_2DSUB );

	// ��l���A�N�^�[�o�^
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.mat.x = FX32_ONE *   HERO_START_POSX;
	add.mat.y = FX32_ONE * ( 130 ) + NAMEIN_SUB_ACTOR_DISTANCE;
	wk->SubActWork[0] = CLACT_Add(&add);
	CLACT_SetAnmFlag(wk->SubActWork[0],1);

	// ��������ė���
	CLACT_AnmChg( wk->SubActWork[0], 3+sex*7 );
	CLACT_SetDrawFlag( wk->SubActWork[0], 1 );
	
	// �������ʂn�a�i�o�^���B��
	for(i=0;i<7;i++){
		wk->SubActWork[i+1] = CLACT_Add(&add);
		CLACT_SetAnmFlag(wk->SubActWork[i+1],1);
		CLACT_AnmChg( wk->SubActWork[i+1], FIELD_OBJ_NO_START+i*4 );
		CLACT_SetDrawFlag( wk->SubActWork[i+1], 0 );
		SetSubLcdObj_Pos( wk->SubActWork[i+1], obj_postable[i][0], obj_postable[i][1] );
	}

}

//==============================================================================
/**
 * @brief   ��l���o��f��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_HeroDemo( WORLDTRADE_WORK *wk, int sex )
{
	
	// ��l�����������ʂn�a�i�o�^
	WorldTrade_SubLcdActorAdd( wk, sex );
	
	// �f���^�X�N�o�^
	{
		HERO_DEMO_WORK *hdw;

		wk->demotask = PMDS_taskAdd( HeroDemoTask, sizeof(HERO_DEMO_WORK), 5, HEAPID_WORLDTRADE);
		hdw          = TCB_GetWork(wk->demotask);
		hdw->seq     = 0;
		hdw->heroy   = HERO_START_POSY;
		hdw->sex     = sex;
		hdw->wk      = wk;

		// ���邭����
		HeroAnimeChange( hdw, 0 );
		Snd_SePlay( SE_GTC_PLAYER_IN );
	}
}


//------------------------------------------------------------------
/**
 * @brief   ��l���̐��ʂɍ��킹�ăA�j���ύX��������
 *
 * @param   wk		
 * @param   animeno		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroAnimeChange( HERO_DEMO_WORK *hdw, int animeno )
{
	CLACT_AnmChg( hdw->wk->SubActWork[0], animeno+hdw->sex*7 );
}

enum{
	HERO_DEMO_FALL=0,
	HERO_DEMO_FALL_STOP,
	HERO_DEMO_WALK,
	HERO_DEMO_WALK_STOP,
};

//------------------------------------------------------------------
/**
 * @brief   ��l���̓����^�X�N
 *          (���邭��~��Ă��遨�������~�܂遨��ɂނ����ĕ����j
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroDemoTask(  TCB_PTR tcb, void *work  )
{
	int i;
	HERO_DEMO_WORK *hdw = (HERO_DEMO_WORK *)work;
	WORLDTRADE_WORK *wk = hdw->wk;

	switch(hdw->seq){
	// ��l�������Ă���
	case HERO_DEMO_FALL:
		if( hdw->heroy > HERO_LAND_POSY ){
			hdw->heroy = HERO_LAND_POSY;
			hdw->seq = HERO_DEMO_FALL_STOP;
			// ��]���������ɂȂ��Ď~�܂�
			HeroAnimeChange( hdw, 1 );
		}
		hdw->heroy+=5;
		SetSubLcdObj_Pos( wk->SubActWork[0], HERO_START_POSX, hdw->heroy );
		break;

	// ��l����]�I��
	case HERO_DEMO_FALL_STOP:
		if( !CLACT_AnmActiveCheck( wk->SubActWork[0] ) ){
			HeroAnimeChange( hdw, 2 );
			hdw->seq = HERO_DEMO_WALK;
		}
		break;

	// ��Ɍ������ĕ���
	case HERO_DEMO_WALK:
		if( hdw->heroy <HERO_STOP_POSY ){
			hdw->heroy = HERO_STOP_POSY;
			hdw->seq = HERO_DEMO_WALK_STOP;
			// ��]���������ɂȂ��Ď~�܂�
			HeroAnimeChange( hdw, 3 );

		}
		hdw->heroy-=2;
		SetSubLcdObj_Pos( wk->SubActWork[0], HERO_START_POSX, hdw->heroy );
		
		break;

	// �f���I���i���Ԃ�@�B�̃X�C�b�`�n�m�Ƃ�������j
	case HERO_DEMO_WALK_STOP:

		Snd_SePlay( SE_GTC_ON );
		hdw->wk->demo_end = 1;
		PMDS_taskDel(tcb);
		break;
	}


}

//==============================================================================
/**
 * @brief   ��l�����悤�Ȃ�f��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_ReturnHeroDemo( WORLDTRADE_WORK *wk, int sex )
{

	// �f���^�X�N�o�^
	{
		HERO_DEMO_WORK *hdw;

		wk->demotask = PMDS_taskAdd( HeroReturnDemoTask, sizeof(HERO_DEMO_WORK), 5, HEAPID_WORLDTRADE);
		hdw          = TCB_GetWork(wk->demotask);
		hdw->seq     = 0;
		hdw->heroy   = HERO_STOP_POSY;
		hdw->sex     = sex;
		hdw->wk      = wk;

		// ���Ɍ������ĕ���
		HeroAnimeChange( hdw, 5 );
		Snd_SePlay( SE_GTC_OFF );

	}
}


enum{
	R_HERO_DEMO_WALK=0,
	R_HERO_DEMO_WALK_STOP,
	R_HERO_DEMO_RISE,
	R_HERO_DEMO_RISE_END,
};

//------------------------------------------------------------------
/**
 * @brief   ��l���̓����^�X�N
 *          (���邭��~��Ă��遨�������~�܂遨��ɂނ����ĕ����j
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroReturnDemoTask(  TCB_PTR tcb, void *work  )
{
	int i;
	HERO_DEMO_WORK *hdw = (HERO_DEMO_WORK *)work;
	WORLDTRADE_WORK *wk = hdw->wk;

	switch(hdw->seq){
	// ��l�����Ɍ������ĕ���
	case R_HERO_DEMO_WALK:
		if( hdw->heroy > HERO_LAND_POSY ){
			hdw->heroy = HERO_LAND_POSY;
			hdw->seq = R_HERO_DEMO_WALK_STOP;
			// ��]���n�߂�
			HeroAnimeChange( hdw, 6 );
		}
		hdw->heroy+=2;
		SetSubLcdObj_Pos( wk->SubActWork[0], HERO_START_POSX, hdw->heroy );
		break;

	// ��l����]���n�߂�
	case R_HERO_DEMO_WALK_STOP:
		if( !CLACT_AnmActiveCheck( wk->SubActWork[0] ) ){
			HeroAnimeChange( hdw, 0 );
			hdw->seq = R_HERO_DEMO_RISE;
			Snd_SePlay( SE_GTC_PLAYER_OUT );
		}
		break;

	// ��l���o���Ă���
	case R_HERO_DEMO_RISE:
		if( hdw->heroy <-20 ){
			hdw->seq = R_HERO_DEMO_RISE_END;
			// ������ʊO�Ȃ̂łȂ�ł�����
			HeroAnimeChange( hdw, 3 );
		}
		hdw->heroy-=5;
		SetSubLcdObj_Pos( wk->SubActWork[0], HERO_START_POSX, hdw->heroy );
		
		break;

	// ��ʂ����������B���ďI��
	case R_HERO_DEMO_RISE_END:

		hdw->wk->demo_end = 1;
		PMDS_taskDel(tcb);
		break;
	}


}



//------------------------------------------------------------------
/**
 * @brief   �T�u��ʃA�N�^�[�̍��W��������
 *
 * @param   act		�A�N�^�[�̃|�C���^
 * @param   x		
 * @param   y		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetSubLcdObj_Pos( CLACT_WORK_PTR act, int x, int y )
{
	VecFx32 mat;

	mat.x = FX32_CONST( x );
	mat.y = FX32_CONST( y - 8 ) + NAMEIN_SUB_ACTOR_DISTANCE;
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}

// �������ʂn�a�i���^�b�`���邽�߂̍��W�e�[�u��
static const RECT_HIT_TBL obj_touchtbl[]={
	{	OBJPOS1_Y-16, OBJPOS1_Y+16, OBJPOS1_X-16, OBJPOS1_X+16,},
	{	OBJPOS2_Y-16, OBJPOS2_Y+16, OBJPOS2_X-16, OBJPOS2_X+16,},
	{	OBJPOS2_Y-16, OBJPOS2_Y+16, OBJPOS3_X-16, OBJPOS3_X+16,},
	{	OBJPOS3_Y-16, OBJPOS3_Y+16, OBJPOS4_X-16, OBJPOS4_X+16,},
	{	OBJPOS3_Y-16, OBJPOS3_Y+16, OBJPOS5_X-16, OBJPOS5_X+16,},
	{	OBJPOS4_Y-16, OBJPOS4_Y+16, OBJPOS6_X-16, OBJPOS6_X+16,},
	{	OBJPOS4_Y-16, OBJPOS4_Y+16, OBJPOS7_X-16, OBJPOS7_X+16,},
	{RECT_HIT_END,0,0,0},		// �I���f�[�^
};

//------------------------------------------------------------------
/**
 * @brief   ����ʂ̂n�a�i�^�b�`�`�F�b�N
 *
 * @param   max		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
int WorldTrade_SubLcdObjHitCheck( int max )
{
	int button=GF_TP_RectHitTrg( obj_touchtbl );
	if( button != RECT_HIT_NONE ){
		if(button<max){
			return button;
		}
	}
	

	return -1;
}

//==============================================================================
/**
 * @brief   �������ʂ̐������n�a�i��\��������
 *
 * @param   wk		
 * @param   num		����Hit�����l��
 * @param   flag	0:�o��A�j������Ȃ�	1:�o��A�j��������
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SubLcdMatchObjAppear( WORLDTRADE_WORK *wk, int num, int flag )
{
	int i;

	// �o��SE
	if(num!=0 && flag==1){
		Snd_SePlay( SE_GTC_APPEAR );
	}

	// �����l����
	for(i=0;i<SEARCH_POKE_MAX;i++){

		if(i<num){
			// HIT��������o�ꂳ����
			int view = wk->DownloadPokemonData[i].trainerType;
			int sex  = wk->DownloadPokemonData[i].gender;

			OS_TPrintf("OBJ�o�� view=%02x, sex=%d\n", view, sex);
		
			TransFieldObjData( wk->FieldObjCharaData, wk->FieldObjPalData, i, view, sex );

			// �A�j�������邩�����Ȃ���
			if(flag){
				CLACT_AnmChg( wk->SubActWork[i+1], FIELD_OBJ_NO_START+i*4 );
			}else{
				CLACT_AnmChg( wk->SubActWork[i+1], FIELD_OBJ_STAND_NO_START+i*4 );
			}
			CLACT_SetDrawFlag( wk->SubActWork[i+1], 1 );
		}else{

			// �\��OFF
			CLACT_SetDrawFlag( wk->SubActWork[i+1], 0 );
		}
	}
	
}


//------------------------------------------------------------------
/**
 * @brief   �j�g���L�����N�^�[���OBJ�������Ă���Z���A�j���͉��Ԃ��H
 *
 * @param   objno		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ObjAppearNoGet( int objno )
{
	return FIELD_OBJ_NO_START + objno*4;
}

//==============================================================================
/**
 * @brief   �������ʂn�a�i��S�ĂЂ����߂�
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SubLcdMatchObjHide( WORLDTRADE_WORK *wk )
{
	int i;
	for(i=0;i<7;i++){
		if(CLACT_GetDrawFlag(wk->SubActWork[i+1])){
			if(CLACT_AnmGet(wk->SubActWork[i+1]) != ObjAppearNoGet( i )+1){
				CLACT_AnmChg( wk->SubActWork[i+1], ObjAppearNoGet( i )+1 );
			}
		}
	}
}


//------------------------------------------------------------------
/**
 * @brief   �t�B�[���hOBJ�摜�ǂݍ��݁i���j�I���Ǝ��@�j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LoadFieldObjData( WORLDTRADE_WORK *wk )
{
	// �p���b�g�ǂݍ���
	wk->FieldObjPalBuf = ArcUtil_PalDataGet( ARC_RECORD_GRA, NARC_record_union_chara_nclr, &(wk->FieldObjPalData), HEAPID_WORLDTRADE );

	// �摜�ǂݍ���
	wk->FieldObjCharaBuf = ArcUtil_CharDataGet( ARC_RECORD_GRA, NARC_record_union_chara_lz_ncgr,  1, &(wk->FieldObjCharaData), HEAPID_WORLDTRADE );
	DC_FlushRange( wk->FieldObjCharaData, FIELDOBJ_NCG_SIZE );

}

#define OBJ_TRANS_SIZE	( 4*4 )
static const u16 obj_offset[]={
	( 32*9                    )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*1 )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*2 )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*3 )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*4 )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*5 )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*6 )*0x20,
};


//------------------------------------------------------------------
/**
 * @brief   �n���ꂽ���j�I�������ڃR�[�h����t�B�[���hOBJ�̃L������]������
 *
 * @param   id		
 * @param   view		
 * @param   sex		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransFieldObjData( NNSG2dCharacterData *CharaData, NNSG2dPaletteData *PalData, int id, int view, int sex )
{
	int pos;
	u8 *chara, *pal;
	
	// ���j�I���L������]��

	pos   = UnionView_GetCharaNo( sex, view );

	chara = (u8*)CharaData->pRawData;
	pal   = (u8*)PalData->pRawData;

	GXS_LoadOBJ( &chara[(OBJ_TRANS_SIZE*3)*pos*0x20], obj_offset[id], OBJ_TRANS_SIZE*0x20 );
	GXS_LoadOBJPltt( &pal[pos*32], (id+2)*32, 32 );

	OS_Printf("ID=%d �̃��j�I�������ڂ� %d �A�C�R���ԍ��� %d\n", id, view, pos);



	
	
}

//------------------------------------------------------------------
/**
 * @brief   �t�B�[���hOBJ�摜���
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void FreeFieldObjData( WORLDTRADE_WORK *wk )
{
	if(wk->demo_end){
		sys_FreeMemoryEz( wk->FieldObjPalBuf  );
                      
		sys_FreeMemoryEz( wk->FieldObjCharaBuf );
	}
}

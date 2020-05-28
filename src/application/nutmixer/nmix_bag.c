/**
 *	@file	nmix_bag.c
 *	@brief	�i�b�c�~�L�T�[�@�؂̎��܎Q��
 *	@author	Miyuki Iwasawa
 *	@date	06.04.07
 */

#include "common.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "system/savedata.h"
#include "system/gamedata.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "application/bag.h"
#include "application/nuts_tag.h"

#include "application/nutmixer.h"
#include "nutmixer_sys.h"

///�o�b�O��ʃv���Z�X�R���g���[��
typedef enum{
 BAGSEQ_BAG_CALL,
 BAGSEQ_BAG_WAIT,
 BAGSEQ_TAG_CALL,
 BAGSEQ_TAG_WAIT,
 BAGSEQ_BAG_COMM_WAIT,
 BAGSEQ_BAG_END,
 BAGSEQ_END,
};

//======================================================
///�v���g�^�C�v�錾
static int bagseq_bagCall(NUTMIXER_WORK* mp);
static int bagseq_bagWait(NUTMIXER_WORK* mp);
static int bagseq_tagCall(NUTMIXER_WORK* mp);
static int bagseq_tagWait(NUTMIXER_WORK* mp);

extern PROC_RESULT NMixGameProc_Init(PROC* proc,int *seq);
extern PROC_RESULT NMixGameProc_Main(PROC* proc,int *seq);
extern PROC_RESULT NMixGameProc_End(PROC* proc,int *seq);

//======================================================
///���C���֐�
/**
 *	@brief	���C���R�}���h�@�؂̎��I���t���[
 */
int NMixMainSeq_Bag(NUTMIXER_WORK* mp,int* seq)
{
	switch(*seq){
	case BAGSEQ_BAG_CALL:
		*seq = bagseq_bagCall(mp);
		break;
	case BAGSEQ_BAG_WAIT:
		*seq = bagseq_bagWait(mp);
		break;
	case BAGSEQ_TAG_CALL:
		*seq = bagseq_tagCall(mp);
		break;
	case BAGSEQ_TAG_WAIT:
		*seq = bagseq_tagWait(mp);
		break;
	case BAGSEQ_BAG_COMM_WAIT:	// �ʐM����
		CommTimingSyncStart( SYNCHROID_BAG_END );
		(*seq) = BAGSEQ_BAG_END;
		break;
	case BAGSEQ_BAG_END:
		if( CommIsTimingSync( SYNCHROID_BAG_END ) ){
			return NMSEQ_MAIN_END;
		}
		break;
	}
	return NMSEQ_BAG_MAIN;
}

/**
 *	@brief	���C���R�}���h�@�Q�[�����C���v���Z�X�R�[��
 */
int NMixMainSeq_GameCall(NUTMIXER_WORK* mp,int* seq)
{
	// �I�[�o�[���CID�錾
//	FS_EXTERN_OVERLAY(nuts_tag);

	// �v���Z�X��`�f�[�^
	const PROC_DATA NMixGameProcData = {
		NMixGameProc_Init,
		NMixGameProc_Main,
		NMixGameProc_End,
//		FS_OVERLAY_ID(nuts_tag)
		NO_OVERLAY_ID
	};
	mp->proc = PROC_Create(&NMixGameProcData,mp,mp->heapID);
	return NMSEQ_GAME_WAIT;
}

/**
 *	@brief	���C���R�}���h�@�Q�[�����C���v���Z�X�I���҂�
 */
int NMixMainSeq_GameWait(NUTMIXER_WORK* mp,int *seq)
{
	if(!NutMixerProcCall(&mp->proc)){
		return NMSEQ_GAME_WAIT;
	}
	return NMSEQ_GAME_END;
}

/**
 *	@brief	���C���R�}���h�@�Q�[�����C���v���Z�X�I������
 */
int NMixMainSeq_GameEnd(NUTMIXER_WORK* mp,int *seq)
{
	return NMSEQ_MAIN_END;
}

//======================================================
///���[�J���T�u�֐�

/**
 *	@brief	�o�b�O��ʌĂяo��
 */
static int bagseq_bagCall(NUTMIXER_WORK* mp)
{
	void * buf;

	static const u8 NMixerBagList[] = {
		BAG_POKE_NUTS, 0xff
	};

	buf = MyItem_MakeBagData( mp->param->itemSave, NMixerBagList,mp->heapID);

//	BagSystemDataSet( buf, 0, BAG_MODE_ITEMSET, mp->param->mySave );
//	BagSystemDataSet( buf, 0, BAG_MODE_FIELD, mp->param->mySave );

/*
	if( Player_FormGet( fsys->player ) == HERO_FORM_CYCLE ){
		BagCycleFlagSet( buf );
	}

	if( !(ZoneData_IsSinouField(fsys->location->zone_id)) ){
		BagUnderCheckFlagSet( buf );
	}
*/
	mp->proc = PROC_Create(&BagProcData,buf,mp->heapID);
	
	mp->app_wk = buf;
	return BAGSEQ_BAG_WAIT;
}

/**
 *	@brief	�o�b�O��ʏI���҂�
 */
static int bagseq_bagWait(NUTMIXER_WORK* mp)
{
	BAG_DATA* dat = NULL;

	if(!NutMixerProcCall(&mp->proc)){
		return BAGSEQ_BAG_WAIT;
	}

	dat = BagSystemDataAlloc( mp->heapID);
	memcpy( dat, mp->app_wk, BagSystemDataSizeGet() );
	sys_FreeMemoryEz( mp->app_wk );
	mp->app_wk = NULL;

	mp->itemno = BagSysReturnItemGet( dat );
	sys_FreeMemoryEz( dat );

	switch( BagSysReturnModeGet( dat ) ){
	case BAG_RET_TAG:		// �^�O���݂�
		return BAGSEQ_TAG_CALL;
	
	case BAG_RET_USE:		// ����
	case BAG_RET_ITEMSET:	// ��������
	case BAG_RET_POKEITEMSET:	// �|�P�������X�g�u��������v
		break;
	case BAG_RET_CANCEL:
	default:
		//�{���͂����ɂ͂��Ȃ��̂ŁA�_�~�[���d����
		mp->itemno = ITEM_KURABONOMI;
		break;
	}
	return BAGSEQ_BAG_COMM_WAIT;
}

/**
 *	@breif	�^�O��ʌĂяo��
 */
static int bagseq_tagCall(NUTMIXER_WORK* mp)
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(nuts_tag);

	// �v���Z�X��`�f�[�^
	const PROC_DATA NutsTagProcData = {
		NutsTagProc_Init,
		NutsTagProc_Main,
		NutsTagProc_End,
		FS_OVERLAY_ID(nuts_tag)
	};
	
	mp->app_wk = NutsTagSystemDataAlloc( mp->heapID );
	NutsTagPutDataSet( mp->app_wk, mp->itemno, TAG_ON );

	mp->proc = PROC_Create(&NutsTagProcData,mp->app_wk,mp->heapID);
	return BAGSEQ_TAG_WAIT;
}

/**
 *	@brief	�؂̎��^�O�I���҂�
 */
static int bagseq_tagWait(NUTMIXER_WORK* mp)
{
	if(!NutMixerProcCall(&mp->proc)){
		return BAGSEQ_TAG_WAIT;
	}
	sys_FreeMemoryEz(mp->app_wk);
	mp->app_wk = NULL;
	return BAGSEQ_BAG_CALL;
}

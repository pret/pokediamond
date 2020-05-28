//==============================================================================================
/**
 * @file	usescript.h
 * @brief	�X�N���v�g�Ŏg�p����t�@�C���̃C���N���[�h�Ȃ�
 * @author	Satoshi Nohara
 * @date	2005.10.04
 */
//==============================================================================================
#ifndef __USESCRIPT_H__
#define __USESCRIPT_H__

#define	__ASM_NO_DEF_

#define ASM_CPP							//pm_version.h


//==============================================================================================
//
//	
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
//(�G�������h�ł�vmstat.h�ɒ�`���Ă�����)
//----------------------------------------------------------------------------------------------
#define	LT				0				/* <	*/
#define	EQ				1				/* ==	*/
#define	GT				2				/* >	*/
#define	LE				3				/* <=	*/
#define	GE				4				/* >=	*/
#define	NE				5				/* !=	*/
#define	EQUAL			EQ
#define	LITTLER			LT
#define	GREATER			GT
#define	LT_EQ			LE
#define	GT_EQ			GE

#define	FLGON			1
#define	FLGOFF			0

//nitro/type.h�Œ�`����Ă��邪�C���N���[�h�ł��Ȃ��̂Ŏ��͂Œ�`
#define	TRUE			1
#define	FALSE			0

//�X�N���v�g�ʐM��t�̔��ʒ�`
#define SCR_COMM_ID_NOTHING	(0)			//�����Ȃ�
#define SCR_COMM_ID_BATTLE	(1)			//�o�g��
#define SCR_COMM_ID_UNION	(2)			//���j�I��
#define SCR_COMM_ID_WIFI	(3)			//WiFi
#define SCR_COMM_ID_RECORD	(4)			//���R�[�h(sp_***.ev�ɖ��ߍ���ł��܂����̂Ŏc���Ă���)
#define SCR_COMM_ID_CONTEST	(5)			//�R���e�X�g
#define SCR_COMM_ID_GTC		(6)			//GTC

//----------------------------------------------------------------------------------------------
//*.ev�̒��Ŏg�p�����`
//----------------------------------------------------------------------------------------------
//�X�N���v�g�ƃv���O�����̃f�[�^�����p
#define	SCWK_PARAM0		( 0x8000 )
#define SCWK_PARAM1		( 0x8001 )
#define SCWK_PARAM2		( 0x8002 )
#define SCWK_PARAM3		( 0x8003 )

//�X�N���v�g�ł̃e���|����
#define SCWK_TEMP0		( 0x8004 )
#define SCWK_TEMP1		( 0x8005 )
#define SCWK_TEMP2		( 0x8006 )
#define SCWK_TEMP3		( 0x8007 )

//�X�N���v�g�����ł̏����p
#define SCWK_REG0		( 0x8008 )
#define SCWK_REG1		( 0x8009 )
#define SCWK_REG2		( 0x800a )
#define SCWK_REG3		( 0x800b )

//�X�N���v�g�ɓ�����Ԃ��ėp���[�N
#define SCWK_ANSWER		( 0x800c )

//�b�������Ώ�OBJID���[�N(�ύX�s��)
#define SCWK_TARGET_OBJID	( 0x800d )

/*
	// �b������������ێ����郏�[�N
	u16 TalkSiteWork = 0;

	// �莝���������ς��ło�b�ɓ]�����ꂽ��
	u16 BoxNoWork = 0;			//���Ԃ�BOX��
	u16 PasoNoWork = 0;			//����BOX�̉��Ԗڂ�

	//���j�I�����[���ł̃C�x���g��Ԑ���p���[�N
	u16 UnionRoomWork = 0;
*/

/*�A���m�[��������*/
#define ANOON_SEE_NUM_1	(10)
#define ANOON_SEE_NUM_2	(26)


//==============================================================================================
//
//	
//
//==============================================================================================
#include "common_scr_def.h"							//���ʃX�N���v�g�f�[�^ID

#include "saveflag.h"								//�t���O�A���[�N��`
#include "savework.h"

#include "../../../include/pm_version.h"

//include/field
#include "../../../include/field/evwkdef.h"
#include "../../../include/field/poketch_app_no.h"	//�|�P�b�`�A�v���i���o�[

#include "../../../include/system/brightness.h"		//�P�x
#include "../../../include/system/window.h"			//�E�B���h�E
#include "../../../include/system/wipe.h"			//���C�v
#include "../../../include/system/timezone.h"		//���ԑ�

#include "../../../include/poketool/monsno.h"		//�|�P�����i���o�[
#include "../../../include/battle/battle_common.h"	//�퓬�֘A
#include "../../../include/battle/trno_def.h"		//�g���[�i�[�i���o�[��`

#include "../../../include/application/wifi_p2pmatch_def.h"	//P2P�ΐ�}�b�`���O�{�[�h
#include "../../../include/application/imageClip/imc_itemid_define.h"	//�C���[�W�N���b�v��`
#include "../../../include/application/box_mode.h"	//�{�b�N�X���[�h��`
#include "../../../include/application/bag_def.h"	//�|�P�b�g��`
#include "../../../include/application/seal_id.h"	//�V�[����`
#include "../../../include/contest/contest_def.h"	//�R���e�X�g
#include "../../../include/itemtool/itemsym.h"		//�A�C�e���i���o�[��`
#include "../../../include/communication/comm_def.h"//�ʐM

#include "../../../include/battle/wazano_def.h"		//���UNo

//include/savedata
#include "../../../include/savedata/fnote_mem.h"	//�`���m�[�g
#include "../../../include/savedata/score_def.h"	//�X�R�A
#include "../../../include/savedata/record.h"	//�X�R�A

//src/field
#include "../../field/script_def.h"					//����X�N���v�g��`
#include "../../field/ev_win.h"						//�C�x���g�E�B���h�E��`
#include "../../field/comm_union_def.h"				//���j�I����`
#include "../../field/comm_union_beacon.h"			//���j�I�����[���p�r�[�R����`
#include "../../field/comm_direct_counter_def.h"	//�ʐM�_�C���N�g�R�[�i�[
#include "../../field/fieldobj_code.h"				//�t�B�[���hOBJ�Ŏg�p����V���{���A�R�[�h�錾
#include "../../field/player_code.h"				//REQBIT
#include "../../field/board.h"						//�Ŕ�
#include "../../field/honey_tree_def.h"				//���؃X�e�[�g��`
#include "../../field/sysflag_def.h"				//�V�X�e���t���O��`
#include "../../field/syswork_def.h"				//�V�X�e�����[�N��`
#include "../../field/gym_def.h"					//�W���֘A��`
#include "../../field/safari_train_def.h"
#include "../../field/field_trade.h"				//�Q�[��������

#include "../../data/sound/sound_data.sadl"			//�T�E���h�i���o�[��`
#include "../../../include/system/snd_def.h"		//�T�E���h��`�̒u��������`
#include "../maptable/zone_id.h"					//�]�[��ID��`
#include "../shopdata/fs_item_def.h"				//�Œ�A�C�e���V���b�v��`
#include "../shopdata/fs_goods_def.h"				//�Œ�O�b�Y�V���b�v��`
#include "../shopdata/fs_seal_def.h"				//�Œ�V�[���V���b�v��`

#include "../../field/move_pokemon_def.h"			//�ړ��|�P������`
#include "../../field/elevator_anm_def.h"			//�G���x�[�^�֘A��`
#include "../../field/ship_demo_def.h"				//�D�f���֘A��`



//���C�v�t�F�[�h�̊�{�̒l
#define SCR_WIPE_DIV				(WIPE_DEF_DIV)
#define SCR_WIPE_SYNC				(WIPE_DEF_SYNC)


//==============================================================================================
//
//	���ʃ��b�Z�[�W�֘A
//
//==============================================================================================
#include "../../../include/msgdata/msg_common_scr.h"
#include "../../../include/msgdata/msg_ev_win.h"
#include "../../../include/msgdata/msg_gameover.h"
//#include "msglist.h"


#endif



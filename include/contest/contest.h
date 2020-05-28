//==============================================================================
/**
 * @file	contest.h
 * @brief	�R���e�X�g�̃w�b�_
 * @author	matsuda
 * @date	2005.11.16(��)
 */
//==============================================================================
#ifndef __CONTEST_H__
#define __CONTEST_H__

#include "battle/battle_common.h"
#include "system/buflen.h"
#include "field/field_common.h"
#include "poketool/poke_tool.h"
#include "system/wordset.h"
#include "savedata/mystatus.h"
#include "contest/actin_ex.h"

#include "contest/contest_def.h"

#include "include/application/imageClip/imc_playsys.h"

#include "contest/contest_conv.h"


//--------------------------------------------------------------
//	�f�o�b�O��`
//--------------------------------------------------------------
///�����쐬�҂�
#define WAIT_FIX		(0)		///<1:�쐬��A�L���B�@0:�܂��쐬���ĂȂ��̂Ŗ���

#define DEBUG_SIO_WAIT	(0)		///<1:�ʐM�p�ɋ����ŃE�F�C�g�����

///�f�o�b�O���j���[����̑I�����[�h
enum{
	DEBUG_CON_VISUAL,
	DEBUG_CON_CLIP_VISUAL,
	DEBUG_CON_DANCE,
	DEBUG_CON_ACTIN,
	DEBUG_CON_RESULT,
//	DEBUG_CON_SIO,
};


//==============================================================================
//	�萔��`
//==============================================================================
///�R���e�X�g�o�[�W����
#define CONTEST_VERSION			(100)

///�R���e�X�g�V�X�e����M�o�b�t�@�T�C�Y
///(�e����̎�M�o�b�t�@�ł͂Ȃ��R���e�X�g�V�X�e���̎�M�o�b�t�@�ł��邱�Ƃɒ���!)
#define CC_RECIEVE_BUF_MAX		(256)

///�R���e�X�g�̋��ʂŎg�p���郁�b�Z�[�W�I����̃E�B���h�E�����܂ł̃E�F�C�g(��) ��check
#define CONTEST_MESSAGE_END_WAIT	0	//(20)

///�ʐM���̃��b�Z�[�W���x
#define CONTEST_SIO_MSG_SPEED		(1)	//(4)

//--------------------------------------------------------------
//	���쒆�̕���
//--------------------------------------------------------------
enum{
	CON_CLASS_VISUAL,		///<�r�W���A������
	CON_CLASS_DANCE,		///<�_���X����
	CON_CLASS_ACTIN,		///<���Z����
	CON_CLASS_RESULT,		///<���ʔ��\���
};

//--------------------------------------------------------------
//	�q�[�v
//--------------------------------------------------------------
///�R���e�X�g�S�̃V�X�e���Ŏg�p����q�[�v�T�C�Y
#define CONTEST_ALLOC_SIZE		(0x3000 + 0x1000)	//+0x1000=�؃��b�v�{�C�X���ǉ�
///���Z�͕���Ŏg�p����q�[�v�T�C�Y
#define ACTIN_ALLOC_SIZE		(0x70000)
///�r�W���A������Ŏg�p����q�[�v�T�C�Y
#define VISUAL_ALLOC_SIZE		(0x70000)
///�_���X����Ŏg�p����q�[�v�T�C�Y
#define DANCE_ALLOC_SIZE		(0xa0000)
///���ʔ��\�Ŏg�p����q�[�v�T�C�Y
#define CONRES_ALLOC_SIZE		(0x70000)

///����f�[�^����M�p�o�b�t�@�T�C�Y
#define CON_HUGEBUF_SIZE		(1024)

///�Q�X�g�R���̍ő�Q����
#define GUEST_JUDGE_MAX			(1)
///���ʂ̐R���̍ő�Q����
#define NORMAL_JUDGE_MAX		(2)
///�R���̍ő�Q����
#define JUDGE_MAX				(GUEST_JUDGE_MAX + NORMAL_JUDGE_MAX)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///AP�l�n�[�g�A�N�^�[�̍ő吔
#define APP_HEART_MAX				(6)
///AP�l�̃n�[�g��1�Ŏ����Ă���|�C���g��
#define APP_APPEAL_ICON_ONE_POINT		(10)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///OBJ�p���b�g�FPFD�Ǘ��{��(�p���b�g�P��)
#define CONTEST_MAIN_OBJPAL_NUM				(16 - 2)	//-2 = �ʐM�A�C�R���{���[�J���C�Y�p
///OBJ�p���b�g�FPFD�Ǘ��{��(�J���[�P��)
#define CONTEST_MAIN_OBJPAL_COLOR_NUM		(CONTEST_MAIN_OBJPAL_NUM * 16)
///OBJ�p���b�g�F�o�C�g�T�C�Y
#define CONTEST_MAIN_OBJPAL_SIZE			(CONTEST_MAIN_OBJPAL_COLOR_NUM * sizeof(u16))
///OBJ�p���b�g�F�t�F�[�hbit
#define CONTEST_MAIN_OBJPAL_FADEBIT			(0x3fff)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�J�����̃t���b�V���G�t�F�N�g��EVY�l
#define CON_CAMERA_FLASH_EVY			(4)	//12
///�J�����̃t���b�V���G�t�F�N�g�ɂ�����t���[����
#define CON_CAMERA_FLASH_FRAME			(6)


//==============================================================================
//	�\���̒�`
//==============================================================================

///���M�p�̌Œ蒷�ׂ̍����f�[�^�Q
typedef struct{
	u8 player_sex;		///<�v���C���[�̐���
	u8 character;		///<���i
	u8 popularity;		///<�l�C
	u16 obj_code;		///<OBJ�R�[�h
}CON_ETC_SIO_DATA;

//--------------------------------------------------------------
/**
 * �R���e�X�g�p�C���[�W�N���b�v�֘A���܂Ƃ߂��\����
 */
//--------------------------------------------------------------
typedef struct{
	IMC_PLAYERSYS_PTR imc_ptr;	///<�C���[�W�N���b�v�v���C���[�V�X�e���ւ̃|�C���^
	int x;						///<���WX
	int y;						///<���WY(�������W)
	int z;						///<���WZ
}CONTEST_IMC_WORK;

//--------------------------------------------------------------
/**
 * CON_IMC_LOCAL�\���̓��̒ʐM����M�f�[�^��
 *
 * ���̒��g���S�đ���M����܂�
 */
//--------------------------------------------------------------
typedef struct{
	//-- ����M�Ŏg����o�b�t�@ --//
	u32 counter;			///<�J�E���g�_�E����M�p�o�b�t�@
	
	//-- ���M�݂̂Ɏg����o�b�t�@ --//
	u8 force_end;			///<�����I���t���O(TRUE:�����I��)
}CON_IMC_LOCAL_SIO;

//--------------------------------------------------------------
/**
 * �C���[�W�N���b�v���Ŏg�p���郏�[�N��(�R���e�X�g�V�X�e���Ŏ����Ă����K�v�̂��镨�̂�)
 * ��{�I�ɒʐM�p�ł��B
 * ����M����̂�CON_IMC_LOCAL_SIO�\���̂̃f�[�^�݂̂ł��B
 */
//--------------------------------------------------------------
typedef struct{
	CON_IMC_LOCAL_SIO recieve_sio;		///<��M�o�b�t�@
	CON_IMC_LOCAL_SIO trans_sio;		///<���M�o�b�t�@

	//-- �}�V�����̌ʂ̎�M�p�o�b�t�@ --//
	u8 recieve_force_end[BREEDER_MAX];	///<�����I���t���O(TRUE:�����I��)

	//-- �V�X�e���I�ȃf�[�^�� --//
	u8 server_no;				///<�T�[�o�[��netID
	u8 my_net_id;				///<������netID
	u8 sio_flag;				///<�ʐM�t���O TRUE �ʐM��
	u8 player_num;				///<�v���C���[�l��

//	u8 dummy[1];	///<4�o�C�g���E�I�t�Z�b�g
}CON_IMC_LOCAL;

//--------------------------------------------------------------
/**
 * �R���e�X�g�̊e����Ŏ擾�������_
 */
//--------------------------------------------------------------
typedef struct{
	s16 bp;				///<�u���[�_�[�|�C���g(�|���b�N�œ�����h���Â�h��)
	s16 clip;			///<�N���b�v�|�C���g
	s16 dance;			///<�_���X����Ŋl�������|�C���g
	s16 actin;			///<���Z�͕���Ŋl�������|�C���g
	
	u8 final_ranking;	///<�ŏI�I�ȏ���
	
	u8 dummy[3];
}CONTEST_SCORE;

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g:�Q�[���i�s�p�����[�^
 *
 * �R���e�X�g��i�s����ׂ̃p�����[�^�������Ă��܂��B
 * �ʐM���̓T�[�o�[����q�@�̓f�[�^���󂯎�鎖�ɂȂ�܂��B
 */
//--------------------------------------------------------------
typedef struct{
	POKEMON_PARAM *pp[BREEDER_MAX];	///<�o�ꂷ��u���[�_�[�̃|�P�����f�[�^
	BREEDER_DATA bd[BREEDER_MAX];	///<�u���[�_�[�f�[�^
	JUDGE_DATA jd[JUDGE_MAX];		///<�R���f�[�^
	STRBUF *breeder_name_str[BREEDER_MAX];	///<�u���[�_�[��(�v���C���[��)
	IMC_CONTEST_SAVEDATA *imc_data[BREEDER_MAX];	///<�e�u���[�_�[�̃N���b�v�f�[�^
	
	u8 player_sex[BREEDER_MAX];		///<�u���[�_�[�̐���
	u8 character[BREEDER_MAX];		///<�u���[�_�[�̐��i
	u8 popularity[BREEDER_MAX];		///<�u���[�_�[�̐l�C
	u16 obj_code[BREEDER_MAX];		///<OBJ�R�[�h
	
	u8 server_no;					///<�T�[�o�[�̃u���[�_�[�ԍ�
	u8 server_version;				///<�T�[�o�[�̃R���e�X�g�o�[�W����
	u8 special_judge_no;			///<�����R�����o����R������No
	
	//-- �������牺�͎����Ŏ擾�\�ȃf�[�^�B��͒ʐM�ŖႤ�f�[�^ --//
	u8 type;						///<CONTYPE_???
	u8 rank;						///<CONRANK_???
	u8 mode;						///<CONMODE_???
	u8 theme;						///<CON_IMAGE_THEME_???
	u8 my_breeder_no;				///<�����̃u���[�_�[�ԍ�
	u8 my_net_id;					///<������netID
	u8 my_version;					///<�����̃R���e�X�g�o�[�W����
	u8 cpu_num;						///<CPU�̐�
	u8 player_num;					///<�v���C���[�̐�

	//-- ���_�F�T�[�o�[�̂݌v�Z���ĕێ��B�q�@�͊�{�I�Ɏ����Ă��Ȃ��B --//
	//-- ���ʔ��\��Ɍ��ʂƂ��āA�e���瑗���Ă��܂� --//
	//-- (�C�x���g�ŏ��ʂ⓾�_���g�p���邾�낤���� --//
	CONTEST_SCORE score[BREEDER_MAX];	///<�e����Ŋl���������_
	
}CONTEST_GAME_PARAM;

///�J�����̃t���b�V�����䃏�[�N�F�X�N���v�g��Ŏg�p
typedef struct{
	TCB_PTR tcb;
	const u8 *wait_tbl;		///<�t���b�V���̃E�F�C�g�e�[�u���ւ̃|�C���^
	s16 wait;
	u8 count;
	u8 seq;
	u8 breeder_no;
}CONSCR_CAMERA_FLASH;

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�V�X�e�����[�N
 *
 * �R���e�X�g�S�̂̐i�s���Ǘ�����ׂ̃��[�N�ł��B
 * �e�}�V�����Ɍʂɍ쐬����܂��B
 */
//--------------------------------------------------------------
typedef struct{
	CONTEST_GAME_PARAM c_game;		///<�R���e�X�g�F�Q�[���i�s�p�����[�^
	POKEPARTY *poke_party;			///<�莝���|�P�����̍\����
	void *perap_voice[BREEDER_MAX];	///<�؃��b�v�̖����f�[�^�ւ̃|�C���^
	void *class_proc;				///<���݂̕���̊Ǘ����[�N�ւ̃|�C���^
	u8 class_flag;					///<���ݎ��s���̕���(CON_CLASS_???)
	u8 sio_flag;					///<TRUE�F�ʐM��
	u8 actin_sort[BREEDER_MAX];		///<���Z�͕���J�n���̕��я�
	
	u8 seq;
	int work;
	int wait;
	TCB_PTR sio_tcb;
	
	//�ʐM�̑���M�o�b�t�@
	u8 recieve_buf[CC_NETID_MAX][CC_RECIEVE_BUF_MAX];	///<��M�o�b�t�@
	u8 recieve_count;				///<��M�f�[�^���󂯎�����l�����J�E���g
	u8 huge_buf[CON_HUGEBUF_SIZE];				///<����f�[�^���M�p�o�b�t�@
	u8 recieve_huge_buf[CC_NETID_MAX][CON_HUGEBUF_SIZE];		///<����f�[�^��M�p�o�b�t�@
	
	//�R���t�B�O
	const CONFIG *config;		///<�R���t�B�O�f�[�^�ւ̃|�C���^
	//�Z�[�u�f�[�^
	SAVEDATA *sv;				///<�Z�[�u�f�[�^�ւ̃|�C���^
	POKEMON_PARAM *my_pp;		///<�o�ꂳ���鎩���̎莝���|�P�����ւ̃|�C���^(�t�B�[���h���)
								///<�Ō�Ƀ��{���Ȃǂ��Z�b�g������ׂɎ����Ă��܂��B
	const MYSTATUS *my_status;	///<�}�C�X�e�[�^�X�ւ̃|�C���^
	u8 temoti_pos;				///<�o�ꂳ����|�P�����̎莝���ʒu
	u8 hof_flag;				///<�a������t���O
	u8 zenkoku_zukan_flag;		///<�S���}�Ӄt���O
	
	//�C���[�W�N���b�v��ʗp(�R���e�X�g�����ł͎g�p���܂���)
	IMC_SAVEDATA *imc_save;		///<�C���[�W�N���b�v�̃Z�[�u�f�[�^�ւ̃|�C���^
	CON_IMC_LOCAL imc_local;	///<�C���[�W�N���b�v���Ŏg�p���郏�[�N
	void *icpw;					///<�C���[�W�N���b�v��ʍ\���p�������f�[�^�ւ̃|�C���^
	
	//�X�N���v�g��Ŏg�p���郏�[�N
	CONSCR_CAMERA_FLASH *conscr_flash;		///<�J�����̃t���b�V�����䃏�[�N
	
	//�����_���̎�ޔ�p���[�N
	u32 push_random_seed;		///<�C�x���g�i�s���̃����_���̎�ޔ�p���[�N
}CONTEST_SYSTEM;


//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�V�X�e���쐬�����f�[�^
 */
//--------------------------------------------------------------
typedef struct{
	u8 type;							///<CONTYPE_???
	u8 rank;							///<CONRANK_???
	u8 mode;							///<CONMODE_???
	u8 hof_flag;						///<�a������t���O(TRUE:�a�����肵�Ă���)
	u8 zenkoku_zukan_flag;				///<�S���}�ӓ���t���O(TRUE:���肵�Ă���)
	u8 temoti_pos;				///<�o�ꂳ����|�P�����̎莝���ʒu
	POKEMON_PARAM *my_pp;				///<�o�ꂳ���鎩���̎莝���|�P�����ւ̃|�C���^
	const STRBUF *player_name_str;		///<�v���C���[���ւ̃|�C���^
	const MYSTATUS *my_status;			///<�}�C�X�e�[�^�X�ւ̃|�C���^
	IMC_SAVEDATA *imc_save;				///<�C���[�W�N���b�v�Z�[�u�f�[�^���[�N�ւ̃|�C���^
	const CONFIG *config;				///<�R���t�B�O�ւ̃|�C���^
	SAVEDATA *sv;						///<�Z�[�u�f�[�^�ւ̃|�C���^
	void *perap_voice;					///<�؃��b�v�{�C�X�ւ̃|�C���^
}CONTEST_INIT_DATA;



//==============================================================================
//	�O���֐��錾
//==============================================================================
extern u16 contest_rand(CONTEST_SYSTEM *consys);
extern u16 contest_fix_rand(u32 seed, u32 *new_seed);
extern CONTEST_SYSTEM * Contest_SystemCreate(const CONTEST_INIT_DATA *cid);
extern void Contest_SystemExit(CONTEST_SYSTEM *consys);
extern void ConScr_JudgeNameGet(CONTEST_SYSTEM *consys, int judge_no, 
	WORDSET *wordset, u32 buf_id);
extern void ConScr_BreederNameGet(CONTEST_SYSTEM *consys, int entry_no, WORDSET *wordset, 
	u32 buf_id);
extern void ConScr_NickNameGet(CONTEST_SYSTEM *consys, int entry_no, WORDSET *wordset, u32 buf_id);
extern void ConScr_RankNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id);
extern void ConScr_TypeNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id);
extern void ConScr_VictoryBreederNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id);
extern u32 ConScr_VictoryItemNoGet(CONTEST_SYSTEM *consys);
extern BOOL Contest_SioParamInitSet(CONTEST_SYSTEM *consys);
extern BOOL Contest_SioFastDataEndCheck(CONTEST_SYSTEM *consys);
extern void EventCmd_ContestProc(GMEVENT_CONTROL * event, CONTEST_SYSTEM *consys);
extern void ConScr_SioTimingSend(CONTEST_SYSTEM *consys, u8 timing_no);
extern BOOL ConScr_SioTimingCheck(CONTEST_SYSTEM *consys, u8 timing_no);
extern int ConScr_RankingCheck(CONTEST_SYSTEM *consys);
extern void ConScr_EndParamSet(CONTEST_SYSTEM *consys, SAVEDATA *sv, u32 place_id, 
	FNOTE_DATA *f_note);
extern void ConScr_VictoryNickNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id);
extern int ConScr_VictoryEntryNoGet(CONTEST_SYSTEM *consys);
extern int ConScr_MyEntryNoGet(CONTEST_SYSTEM *consys);
extern int ConScr_OBJCodeGet(CONTEST_SYSTEM *consys, int entry_no);
extern int ConScr_PopularityGet(CONTEST_SYSTEM *consys, int entry_no);
extern int ConScr_DeskModeGet(CONTEST_SYSTEM *consys);
extern void ConScr_MsgPrintFlagSet(CONTEST_SYSTEM *consys);
extern void ConScr_MsgPrintFlagReset(CONTEST_SYSTEM *consys);
extern void ConScr_FlashTaskCreate(CONTEST_SYSTEM *consys, int entry_no);
extern BOOL ConScr_FlashTaskCheck(CONTEST_SYSTEM *consys);
extern void ConScr_VictoryParamGet(CONTEST_SYSTEM *consys, 
	int *victory_entry, int *sio_flag, int *cpu_flag, int *tutorial, int *practice);
extern void ConScr_EntryParamGet(CONTEST_SYSTEM *consys, u16 *rank, u16 *type, u16 *mode, 
	u16 *temoti_pos);
extern BOOL ConScr_HaveRibbonCheck(CONTEST_SYSTEM *consys);
extern void ConScr_RibbonItemNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, 
	u32 buf_id, int heap_id);
extern u32 ConScr_AcceNoGet(CONTEST_SYSTEM *consys);

//-- con_record.c --//
extern void * ContestSioRecord_Create( void * fsys );
extern void ContestSioRecord_Delete(void *con_rec);
extern void EventCmd_ConRecordDisp(GMEVENT_CONTROL *event);

//-- con_tool.c --//
extern void ConTool_MsgPrintFlagSet(int sio_flag);
extern void ConTool_MsgPrintFlagReset(void);

//-- con_battle.c --//
extern BOOL ContestPokeFlipCheck(u32 monsno);


#ifdef PM_DEBUG
extern void DebugContest_FieldConnectStart(FIELDSYS_WORK *fsys, int debug_mode);
#endif


#endif	//__CONTEST_H__


//==============================================================================
/**
 * @file	slot_local.c
 * @brief	�~�j�Q�[���@�X���b�g�@���[�J��
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef SLOT_MAIN_H_FILE
#define SLOT_MAIN_H_FILE

#include "system/render_oam.h"
#include "system/clact_util.h"
#include "system/arc_tool.h"
#include "..\..\field\eoa.h"
#include "system/snd_tool.h"

#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/wordset.h"
#include "system\fontproc.h"
#include "system\window.h"
#include "msgdata/msg.naix"

#include "poketool\monsno.h"

#include "slot.naix"	//ARC_SLOT
#include "msgdata/msg_slot.h"
#include "application\slot.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	debug
//--------------------------------------------------------------
//----
#ifdef PM_DEBUG
//----
#define DEBUG_ON_SLOT			//��`�Ńf�o�b�O�@�\ON
#define DEBUG_SLOT_PARAM_INIT	//��`�ŋU�p�����^������
//----
#endif	//PM_DEBUG
//----

//----
#ifdef DEBUG_ON_SLOT
//----
//----
#endif 	//DEBUG_ON_SLOT
//----

//--------------------------------------------------------------
//	fx
//--------------------------------------------------------------
#define NUM_FX32(a)	(FX32_ONE*(a))							///<����->FX32�^��
#define FX32_NUM(a)	((a)/FX32_ONE)							///<FX32->������
#define NUM_FX16(a)	(FX16_ONE*(a))							///<����->FX16�^��
#define FX16_NUM(a)	((a)/FX16_ONE)							///<FX16->������

#define SUBD_NFX32(a) (NUM_FX32(192)+NUM_FX32(a))			///<����ʕ␳ ����->FX32

//--------------------------------------------------------------
///	CLACT
//--------------------------------------------------------------
#define G2D_2DMAIN (NNS_G2D_VRAM_TYPE_2DMAIN)	//����
#define G2D_2DSUB  (NNS_G2D_VRAM_TYPE_2DSUB)	//�����
#define G2D_2DMAX  (NNS_G2D_VRAM_TYPE_MAX)		//����

///CELLTYPE
typedef enum
{
	CELL_VRAM = FALSE,		///<�Z���@VRAM�풓�^
	CELL_TRANS = TRUE,		///<�Z���@VRAM�]���^
}CELLTYPE;

//--------------------------------------------------------------
///	BG�v���C�I���e�B
//--------------------------------------------------------------
typedef enum
{
	BGPRI0 = 0,
	BGPRI1,
	BGPRI2,
	BGPRI3,
}BGPRI;

//--------------------------------------------------------------
///	�V�X�e��
//--------------------------------------------------------------
#define SLOT_HEAPSIZE (0x00080000)			///<�q�[�v�T�C�Y
#define SLOT_VRAMTRANSM_REG_MAX (0x08)		///<VRAM�]���}�l�[�W���@�o�^�ő�

#define STR_BUF_SIZE (256)		///<�����o�b�t�@�T�C�Y

#define SLOT_EOA_MAX (128)	///<EOA�ő�

//--------------------------------------------------------------
//	BG
//--------------------------------------------------------------
#define BGPLTTNO_MOUNT_SKY		(0x01)	///<��p���b�g
#define BGPLTTNO_LINE_1			(0x02)
#define BGPLTTNO_LINE_2_0		(0x03)
#define BGPLTTNO_LINE_2_1		(0x0c)
#define BGPLTTNO_LINE_3_0		(0x04)
#define BGPLTTNO_LINE_3_1		(0x0b)

#define BGFRAME_KAIWA			(GF_BGL_FRAME0_M)
#define BGFRAME_SLOT			(GF_BGL_FRAME1_M)
#define BGFRAME_SLOT_SHADOW		(GF_BGL_FRAME2_M)
#define BGFRAME_BGSUB			(GF_BGL_FRAME3_S)
#define BGFRAME_SUB_DEBUG		(GF_BGL_FRAME0_S)

#define BG_SLOT_CHAR_SIZE	(32)	//color 256

#define BGF_SLOT_PLTT_SIZE		(32*13)
#define BGF_SLOT_PLTT_OFFSET	(32*0)
#define BGF_SLOT_CHAR_OFFSET	(BG_SLOT_CHAR_SIZE*0)

#define BGF_SLOT_PANO	(0)

#define BGF_SLOT_PANO_FONT	(15)
#define BGF_SLOT_PANO_TALK	(14)
#define BGF_SLOT_CHAR_NO_WIN (1)
#define BGF_SLOT_CHAR_NO_TALK (BGF_SLOT_CHAR_NO_WIN+TALK_WIN_CGX_SIZ)

//--------------------------------------------------------------
///	�Z���A�N�^�[
//--------------------------------------------------------------
#define SLOT_CLACT_MAX (64)
#define SLOT_CLACT_TRANS_MAX (32)

#define CHAR_MANAGER_MAX (32)
#define CHAR_VRAMTRANS_M_SIZE (0x4000)	//512
#define CHAR_VRAMTRANS_S_SIZE (0x4000)	//512

#define PLTT_MANAGER_MAX (16)

#define SLOT_CHAR_MAX (64)
#define SLOT_PLTT_MAX (16)
#define SLOT_CELL_MAX (64)
#define SLOT_ANM_MAX (32)


//--------------------------------------------------------------
///	�G�����
//--------------------------------------------------------------
typedef enum
{
	REEL_RED7 = 0,		///<�ԂV
	REEL_BLACK7,		///<���V
	REEL_REPLAY,		///<���v���C
	REEL_CHERRY,		///<�`�F���[
	REEL_BELL,			///<�x��
	REEL_SUIKA,			///<�X�C�J
	REEL_PATTERN_MAX,	///<�G���ő�
}REEL_PATTERN;

//--------------------------------------------------------------
///�@���[���ԍ�
//--------------------------------------------------------------
typedef enum
{
	REEL_0,
	REEL_1,
	REEL_2,
	REEL_MAX,
}REEL_NUM;

//--------------------------------------------------------------
///	���C���ԍ�
//--------------------------------------------------------------
typedef enum
{
	LINE_1 = 0,
	LINE_2_0,
	LINE_2_1,
	LINE_3_0,
	LINE_3_1,
	LINE_MAX,
}LINENO;

//--------------------------------------------------------------
///	���C���r�b�g
//--------------------------------------------------------------
#define LINEBIT_NON (0)
#define LINEBIT_1	(1<<0)
#define LINEBIT_2_0 (1<<1)
#define LINEBIT_2_1 (1<<2)
#define LINEBIT_3_0 (1<<3)
#define LINEBIT_3_1 (1<<4)

//--------------------------------------------------------------
///	���[�����
//--------------------------------------------------------------
typedef enum
{
	REEL_ST_STOP = 0,
	REEL_ST_SCROLL,
	REEL_ST_WAIT,
}REEL_ST;

//--------------------------------------------------------------
///	�p�����_�E���^�C�v
//--------------------------------------------------------------
typedef enum 
{
	CONT_BONUS_DOWN_10 = 0,
	CONT_BONUS_DOWN_5,
	CONT_BONUS_DOWN_MAX,
}CONTBONUSDOWN;

//--------------------------------------------------------------
///	�{�[�����
//--------------------------------------------------------------
typedef enum
{
	BALL_MON = 0,
	BALL_SUP,
	BALL_HYP,
	BALL_SAF,
	BALL_PRE,
	BALL_MAX,
}BALLTYPE;

//--------------------------------------------------------------
///	MBALL TYPE �����X�^�[�{�[������^�C�v
//--------------------------------------------------------------
typedef enum
{
	MBALLMT_INIT = 0,		///<�{�[��������
	MBALLMT_SPIN_START,		///<�]����J�n
	MBALLMT_OPEN,			///<�J��
	MBALLMT_CLOSE,			///<����
	MBALLMT_SPIN_OUT,		///<��ʊO�֓]����
	MBALLMT_SHAKE,			///<����
	MBALLMT_STOP,			///<��~
	MBALLMT_MAX,
}MBALLMT;

//--------------------------------------------------------------
///	�{�[���A�j���ԍ�
//--------------------------------------------------------------
enum
{
	MBALLANMNO_START,
	MBALLANMNO_OPEN,
	MBALLANMNO_STOP,
	MBALLANMNO_CLOSE,
	MBALLANMNO_BACK,
};

//--------------------------------------------------------------
///	�s�b�s�Z���A�j���ԍ�
//--------------------------------------------------------------
enum
{
	PIPANMNO_STOP,
	PIPANMNO_START,
	PIPANMNO_PATAPATA,
	PIPANMNO_RIGHT,
	PIPANMNO_LEFT,
	PIPANMNO_NAKA,
};

//--------------------------------------------------------------
///	�s�b�s
//--------------------------------------------------------------
typedef enum
{
	PIP_NORMAL = 0,
	PIP_META,
	PIP_RARE,
	PIP_MAX,
}PIPTYPE;

//--------------------------------------------------------------
///	PIPMT�@�s�b�s����^�C�v
//--------------------------------------------------------------
typedef enum
{
	PIPMT_INIT,		///<������
	PIPMT_START,	///<�o��
	PIPMT_BACK,		///<�߂�
	PIPMT_STAND,	///<����
	PIPMT_PATAPATA,	///<�p�^�p�^
	PIPMT_NAKA,		///<�����w��
	PIPMT_LEFT,		///<���w��
	PIPMT_RIGHT,	///<�E�w��
	PIPMT_BANZAI,	///<����
	PIPMT_MAX,		///<����ő�
}PIPMT;

//--------------------------------------------------------------
///	�{�[�i�X�p�����o
//--------------------------------------------------------------
typedef enum
{
	BCEFF_NON = 0,		///<��������
	BCEFF_BACK,			///<�߂�
	BCEFF_ANENCORE,		///<�A���R�[��
	BCEFF_MAX,			///<�ő�
}BCEFF;

//--------------------------------------------------------------
///	�l����or��
//--------------------------------------------------------------
typedef enum
{
	BIGFONT_COUNT = 0,
	BIGFONT_GET,
}BIGFONTTYPE;

//--------------------------------------------------------------
///	�Q�[��
//--------------------------------------------------------------
#define BET_LOWEST	(3)						///<�x�b�g�ɍŒ���K�v�ȃN���W�b�g
#define BET_LOWEST_BONUS	(1)				///<�{�[�i�X���A�x�b�g�ɍŒ���K�v�ȃN���W�b�g

//--------------------------------------------------------------
//	���[��
//--------------------------------------------------------------
#define REEL_PT_MAX      (21)							// �G���ő� 21�G��

#define REEL_PT_V_SIZE   (32)							// �G������ �h�b�g
#define REEL_PT_V_OFFSET (16)							// �G���̾��

#define REEL_PT_V_MAX    (160)							// �G���c�ő�
#define REEL_PT_V_DG(v)  ((v)/REEL_PT_V_SIZE)			// �ޯ� -> ��د��
#define REEL_PT_V_DG32(v)  ((FX32_NUM(v))/REEL_PT_V_SIZE)// �ޯ� -> ��د�� fx32
#define REEL_PT_V_GD(v)  ((v)*REEL_PT_V_SIZE)			// ��د�� -> �ޯ�
#define REEL_PT_V_GD32(v)  (NUM_FX32((v)*REEL_PT_V_SIZE))	// ��د�� -> �ޯ�
#define REEL_SCROLL_MAX  (REEL_PT_MAX*REEL_PT_V_SIZE)	// ذٽ�۰ٍő�
#define REEL_CENTERN_V   ((0x09*8)+4)					// ذْ���

#define MCREEL_PT_MAX		(0x06)						// ϼ�ذيG���ő�
#define MCREEL_PT_V_SIZE	(0x14)						// ϼ�ذيG������
#define MCREEL_PT_V_OFFSET	((0x06*0x08)+4+8)			// ϼ�ذيG���̾��
#define MCREEL_PT_V_MAX		(0x02*MCREEL_PT_V_SIZE)		// ϼ�ذُc�ő�
#define MCREEL_PT_V_GP(v)	((v)/MCREEL_PT_V_SIZE)		// ���W->��د��
#define MCREEL_SCROLL_MAX	(MCREEL_PT_MAX*MCREEL_PT_V_SIZE)

//--------------------------------------------------------------
///	���I
//--------------------------------------------------------------
#define LOTTERY_HITBIT_NON			(0)				///<����
#define LOTTERY_HITBIT_REPLAY		(1<<0)			///<���v���C
#define LOTTERY_HITBIT_REPLAY_B		(1<<1)			///<���v���C�@�r�b�O
#define LOTTERY_HITBIT_CHERRY		(1<<2)			///<�`�F���[
#define LOTTERY_HITBIT_CHERRY_B		(1<<3)			///<�`�F���[�@�r�b�O
#define LOTTERY_HITBIT_BELL			(1<<4)			///<�x��
#define LOTTERY_HITBIT_BELL_B		(1<<5)			///<�x���@�r�b�O
#define LOTTERY_HITBIT_SUIKA		(1<<6)			///<�X�C�J
#define LOTTERY_HITBIT_SUIKA_B		(1<<7)			///<�X�C�J�@�r�b�O
#define LOTTERY_HITBIT_BLACK7		(1<<8)			///<��7
#define LOTTERY_HITBIT_RED7			(1<<9)			///<��7

#define LOTTERY_NUM_MAX (10)				

///7�r�b�g
#define LOTTERY_HITBIT_SEVEN_AND \
(LOTTERY_HITBIT_BLACK7|LOTTERY_HITBIT_RED7)
///�{�[�i�X�r�b�g
#define LOTTERY_HITBIT_BONUS_AND \
(LOTTERY_HITBIT_REPLAY_B|LOTTERY_HITBIT_CHERRY_B|LOTTERY_HITBIT_BELL_B|LOTTERY_HITBIT_SUIKA_B)

///�q��A�I�[�g�r�b�g
#define LOTTERY_HITBIT_AUTO_AND \
(LOTTERY_HITBIT_REPLAY|LOTTERY_HITBIT_REPLAY_B|LOTTERY_HITBIT_BELL|LOTTERY_HITBIT_BELL_B)

///�q��A�{�[�i�X�m��r�b�g
#define LOTTERY_HITBIT_BONUSMODE \
(LOTTERY_HITBIT_SUIKA_B|LOTTERY_HITBIT_CHERRY_B)

//--------------------------------------------------------------
///	������
//--------------------------------------------------------------
#define BIT_CHERRY		0x0001							// ˯��׸�
#define BIT_CHERRY_4	0x0002
#define BIT_REPLAY		0x0004
#define BIT_BELL		0x0008
#define BIT_SUIKA		0x0010
#define BIT_REGULAR		0x0020
#define BIT_BIG_RED		0x0040

//--------------------------------------------------------------
///	�p�������
//--------------------------------------------------------------
typedef enum
{
	CONT_777_50 = 0,
	CONT_777_70,
	CONT_777_90,
	CONT_GGG_50,
	CONT_GGG_70,
	CONT_GGG_90,
	CONT_BONUS_TYPE_MAX,
}CONTBONUSTYPE;

//--------------------------------------------------------------
///	�p����
//--------------------------------------------------------------
typedef enum
{
	CONT_BONUS_50 = 0,
	CONT_BONUS_70,
	CONT_BONUS_90,
	CONT_BONUS_MAX,
}CONTBONUS;

//--------------------------------------------------------------
///	�I���p����
//--------------------------------------------------------------
typedef enum
{
	CONT_BONUSEND_0 = 0,
	CONT_BONUSEND_5 = 5,
	CONT_BONUSEND_15 = 15,
	CONT_BONUSEND_25 = 25,
	CONT_BONUSEND_35 = 35,
	CONT_BONUSEND_45 = 45,
	CONT_BONUSEND_55 = 55,
	CONT_BONUSEND_65 = 65,
	CONT_BONUSEND_100_75 = 75,
	CONT_BONUSEND_NUM_MAX = 9,
}CONT_BONUSEND;

//--------------------------------------------------------------
///	tcb	�v���C�I���e�B
//--------------------------------------------------------------
enum
{
	TCBPRI_SLOT_BASE = 0x80,							///<�X���b�g�x�[�X
	TCBPRI_REELCONTROL0,								///<���[������ 0
	TCBPRI_REELCONTROL1,								///<���[������ 1
	TCBPRI_REELCONTROL2,								///<���[������ 2
	TCBPRI_DDISPCONTROL,								///<����ʐ���
	TCBPRI_PLTTCONTROL,									///<�p���b�g����
	TCBPRI_MBALL,										///<�����X�^�[�{�[��
	TCBPRI_BALLEFF,										///<�{�[���G�t�F�N�g
	TCBPRI_PIKA,										///<�s�J�`���E
	TCBPRI_PIP,											///<�s�b�s
	TCBPRI_PAYOUTCONTROL,								///<�y�C�A�E�g����
	TCBPRI_REEL,										///<���[���G
	TCBPRI_REEL_BIGHIT,									///<�哖���胊�[���G
	TCBPRI_CREDITFONT,									///<�R�C������
	TCBPRI_BONUSFONT,									///<�{�[�i�X����
	TCBPRI_PLTTEFF,										///<�p���b�g�G�t�F�N�g
	TCBPRI_BGM,											///<BGM
};

//--------------------------------------------------------------
///	tcb	VIntr�u�����N�v���C�I���e�B
//--------------------------------------------------------------
enum
{
	VINTRTCBPRI_SLOT_BASE = 0x100,							///<�X���b�g�x�[�X
	VINTRTCBPRI_MBALLTRANS,									///<�{�[���ǉ�
};

//--------------------------------------------------------------
///	tcb	VWait�u�����N�v���C�I���e�B
//--------------------------------------------------------------
enum
{
	VWAITTCBPRI_SLOT_BASE = 0x100,							///<�X���b�g�x�[�X
	VWAITTCBPRI_MBALLTRANS,									///<�{�[���ǉ�
};

//--------------------------------------------------------------
///	�Z���A�N�^�[�v���C�I���e�B
//--------------------------------------------------------------
enum
{
	CAPRI_BIGHIT_REEL,									///<�r�b�O�q�b�g�G��
	CAPRI_CREDITFONT,									///<�R�C������
	CAPRI_REEL,											///<���[��
	CAPRI_BONUS_FONT,									///<�{�[�i�X�t�H���g
	CAPRI_PIKA,											///<�s�J�`���E
	CAPRI_BALLEFF,										///<�{�[����
	CAPRI_PIP,											///<�s�b�s
	CAPRI_MBALL,										///<�����X�^�[�{�[��
};

//--------------------------------------------------------------
///	�Z���A�N�^�[�@�L����ID
//--------------------------------------------------------------
enum
{
	SLOT_CHARID_REEL,
	SLOT_CHARID_CREDITFONT,
	SLOT_CHARID_MBALL,
	SLOT_CHARID_BALLEFF,
	SLOT_CHARID_PIP,
	SLOT_CHARID_PIKA,
	SLOT_CHARID_BONUSFONT,
	SLOT_CHARID_GETFONT,
	SLOT_CHARID_BONUSGETFONT,
	SLOT_CHARID_MOONFONT,
	SLOT_CHARID_BIGHIT,
	SLOT_CHARID_MAX,
};

//--------------------------------------------------------------
///	�Z���A�N�^�[�@OBJ�p���b�gID
//--------------------------------------------------------------
enum
{
	SLOT_PLTTID_REEL,
	SLOT_PLTTID_CREDITFONT,
	SLOT_PLTTID_MBALL,
	SLOT_PLTTID_BALLEFF,
	SLOT_PLTTID_PIP,
	SLOT_PLTTID_PIKA,
	SLOT_PLTTID_BONUSFONT,
	SLOT_PLTTID_MOONFONT,
	SLOT_PLTTID_MAX,
};

//--------------------------------------------------------------
///	�Z���A�N�^�[�@�Z��ID
//--------------------------------------------------------------
enum
{
	SLOT_CELLID_REEL,
	SLOT_CELLID_CREDITFONT,
	SLOT_CELLID_MBALL,
	SLOT_CELLID_BALLEFF,
	SLOT_CELLID_PIP,
	SLOT_CELLID_PIKA,
	SLOT_CELLID_BONUSFONT,
	SLOT_CELLID_GETFONT,
	SLOT_CELLID_BONUSGETFONT,
	SLOT_CELLID_MOONFONT,
	SLOT_CELLID_BIGHIT,
	SLOT_CELLID_MAX,
};

//--------------------------------------------------------------
///	�Z���A�N�^�[�@�A�j��ID
//--------------------------------------------------------------
enum
{
	SLOT_ANMID_REEL,
	SLOT_ANMID_CREDITFONT,
	SLOT_ANMID_MBALL,
	SLOT_ANMID_BALLEFF,
	SLOT_ANMID_PIP,
	SLOT_ANMID_PIKA,
	SLOT_ANMID_BONUSFONT,
	SLOT_ANMID_GETFONT,
	SLOT_ANMID_BONUSGETFONT,
	SLOT_ANMID_MOONFONT,
	SLOT_ANMID_BIGHIT,
	SLOT_ANMID_MAX,
};

//--------------------------------------------------------------
///	�E�B���h�E���X�g
//--------------------------------------------------------------
enum
{
	SLOTWIN_TALK = 0,		///<��b�E�B���h�E
	SLOTWIN_MAX,
};

//--------------------------------------------------------------
///	���b�Z�[�W�ԍ�
//--------------------------------------------------------------
#define MSGNO_SANMAI		(msg_00)
#define MSGNO_CREDIT_MAX	(msg_01)

//--------------------------------------------------------------
///	BGM
//--------------------------------------------------------------
typedef enum
{
	BGM_NORMAL,
	BGM_HIT,
	BGM_BIGHIT,
	BGM_MAX,
}BGMTYPE;

//==============================================================================
//	typedef struct
//==============================================================================
typedef struct _TAG_SLOTMAIN SLOTMAIN;			///<SLOTMAIN �X���b�g���C�����[�N
typedef struct _TAG_CLACTSETDATA CLACTSETDATA;	///<CLACTSETDATA �Z���A�N�^�[

//--------------------------------------------------------------
///	MSGWORK
//--------------------------------------------------------------
typedef struct
{
	MSGDATA_MANAGER *msgman;
	WORDSET *wordset;
	GF_BGL_BMPWIN bmpwin[SLOTWIN_MAX];
	void *strbuf;
}MSGWORK;

//--------------------------------------------------------------
///	CLACT_WORK_EX
//--------------------------------------------------------------
typedef struct
{
	CELLTYPE trans_flag;
	CLACT_WORK_PTR act;
	const NNSG2dImageProxy *pImageProxy;
}CLACT_WORK_EX;

//--------------------------------------------------------------
///	CELLARCDATA OAM�G�f�[�^
//--------------------------------------------------------------
typedef struct
{
	u32 char_id;
	u32 pltt_id;
	u32 cell_id;
	u32 anm_id;
}CELLARCDATA;

//--------------------------------------------------------------
///	LT_CONT_BONUS
//--------------------------------------------------------------
typedef struct
{
	u32 prob;
	CONTBONUSTYPE type;
	CONTBONUS prob_type;
}LT_CONT_BONUS;

//--------------------------------------------------------------
///	LT_SMALLBONUS
//--------------------------------------------------------------
typedef struct
{
	u16 lt_bonus;
	u16 lt_small;
}LT_SMALLBONUS;

//--------------------------------------------------------------
///	LT_POKE_ENTRY
//--------------------------------------------------------------
typedef struct
{
	u32 prob;
	PIPTYPE type;
}LT_POKE_ENTRY;

//--------------------------------------------------------------
///	LT_SMALLDATA
//--------------------------------------------------------------
typedef struct
{
	LT_SMALLBONUS cherry;
	LT_SMALLBONUS suika;
	LT_SMALLBONUS bell;
	LT_SMALLBONUS replay;
}LT_SMALLDATA;

//--------------------------------------------------------------
///	LT_CONTBONUSEND
//--------------------------------------------------------------
typedef struct
{
	CONT_BONUSEND prec_bonus;
	u32 prec_back;
	u32 prec_non;
	u32 prec_anencore;
}LT_CONTBONUSEND;

//--------------------------------------------------------------
///	REELCONTROL
//--------------------------------------------------------------
typedef struct
{
	u32 seq_no;
	int scroll_flag;
	fx32 slip_dot_y;
	int frame;
	REEL_NUM reel_no;
	int reel_hit_grid_y;
	int reel_slip_grid_y;
	TCB_PTR tcb;
	SLOTMAIN *main;
}REELCONTROL;

//--------------------------------------------------------------
///	PAYOUTCONTROL
//--------------------------------------------------------------
typedef struct
{
	u32 seq_no;
	u32 end_flag;
	int frame;
	SLOTMAIN *main;
	TCB_PTR tcb;
	EOA_PTR eoa_reelanm0;
	EOA_PTR eoa_reelanm1;
}PAYOUTCONTROL;

//--------------------------------------------------------------
///	BGM
//--------------------------------------------------------------
typedef struct
{
	u32 seq_no;
	int chg_flag;
	BGMTYPE now_play;
	BGMTYPE next_play;
	TCB_PTR tcb;
}SLOTBGM;

//--------------------------------------------------------------
///	DDISPCONTROL ����ʃR���g���[���\����
//--------------------------------------------------------------
typedef struct
{
	u32 move_type;
	u32 seq_no;
	u32 end_flag;
	u32 bonus_font_vanish_flag;
	int frame;
	int count;
	BALLTYPE balltype;
	PIPTYPE piptype;
	SLOTMAIN *main;
	TCB_PTR tcb;
	EOA_PTR eoa_mball;
	EOA_PTR eoa_balleff;
	EOA_PTR eoa_pip;
	EOA_PTR eoa_pika;
	EOA_PTR eoa_font_bonus;
	EOA_PTR eoa_font_get;
	EOA_PTR eoa_font_bcount;
	EOA_PTR eoa_font_getcoin;
}DDISPCONTROL;

//--------------------------------------------------------------
///	PLTTCONTROL�\����
//--------------------------------------------------------------
typedef struct
{
	SLOTMAIN *main;
	
	u16 plttbase_mount[16];
	u16 plttkurai_mount[16];
	u16 plttflash_mount[16];
	u16 plttflash_red_mount[16];
	u16 plttbuf_mount[16];
	
	u16 plttbase_line[LINE_MAX][16];
	u16 plttflash_line[LINE_MAX][16];
	u16 plttbuf_line[LINE_MAX][16];
}PLTTCONTROL;

#ifdef DEBUG_ON_SLOT
//--------------------------------------------------------------
//	D_SLOTWORK
//--------------------------------------------------------------
typedef struct
{
	u32 seq_no;
	u32 auto_flag;		//�����v���C
	u32 auto_play_replay_avoid_flag;
	u32 debug_lottery_bit;
	u32 debug_auto_set;
	u32 debug_bonus_end;
	PIPTYPE debug_pip_type;
	u32 debug_moon_light;
	u32 debug_moon_red;
	BCEFF debug_bonus_end_effect;
	int auto_stop_count;
	int auto_stop_frame;
	u32 lottery_no;
	u32 hitline[LINE_MAX];
}D_SLOTWORK;
#endif

//--------------------------------------------------------------
///	SLOTMAIN�\����
//--------------------------------------------------------------
typedef struct _TAG_SLOTMAIN
{
	u32 seq_no;								///<�V�[�P���X
	u32 next_seq_no;						///<���V�[�P���X�ԍ�
	u32 bonus_game_flag;					///<�{�[�i�X�Q�[���t���O
	u32 bonus_hit_count;					///<�{�[�i�X�q�b�g��
	u32 bonus_count;						///<�{�[�i�X��
	u32 bonus_get_coin;						///<�{�[�i�X�Ŋl�������R�C������
	u32 bonus_continue_prob;				///<�{�[�i�X�p����
	u32 bonus_continue_count;				///<�{�[�i�X�p����
	u32 bonus_continue_count_max;			///<�{�[�i�X�p�����ő�
	u32 bonus_moonlight_flag;				///<�����t���O
	u32 bonus_moonlight_red_flag;			///<�Ԃ����t���O
	u32 bonus_game_end_flag;				///<�{�[�i�X�Q�[���I���t���O
	u32 reel_slip_hit_flag;					///<���[���q�b�g�t���O
	u32 yubisashi_type;						///<�w�����^�C�v
	u32 data_game_count;					///<�Q�[���J�E���g
	u32 data_miss_count;					///<�O�ꂽ��
	u32 data_hit_count;						///<����������
	REEL_PATTERN reel_hit_pattern;			///<�q�b�g�������[���p�^�[��
	u32 reel_hit_line_bit;
	CONTBONUS bonus_continue_prob_type;		///<�{�[�i�X�p�������
	CONTBONUSTYPE bonus_continue_type;		///<�{�[�i�X�p�����^�C�v
	u32 reel_stop_btn[REEL_MAX];			///<�X�g�b�v�{�^���i�[
	int credit;								///<�N���W�b�g
	int payout;								///<�x����
	int bet;								///<�x�b�g
	fx32 frame;								///<�ėp�t���[��
	int auto_hit_flag;						///<�I�[�g�q�b�g�t���O
	u32 lottery_bit;						///<���I�t���O
	u32 hit_bit;							///<�q�b�g�r�b�g
	REEL_ST reel_status[REEL_MAX];			///<���[���X�e�[�^�X
	SLOT_HARD hard;							///<��ݒ�
	
	fx32 reel_speed;						///<���[���@���x
	fx32 reel_dot_y[REEL_MAX];				///<���[���@�h�b�g
	fx32 reel_offs_y[REEL_MAX];				///<���[���@�I�t�Z�b�g
	int  reel_grid_y[REEL_MAX];				///<���[���@�O���b�h
	
	REELCONTROL reelcont[REEL_MAX];			///<REELCONTROL
	PAYOUTCONTROL payoutcont;				///<PAYOUTCONTROL
	DDISPCONTROL ddispcont;					///<DDISPCONTROL
	PLTTCONTROL plttcont;					///<PLTTCONTROL
	MSGWORK msgwork;						///<MSGWORK
	SLOTBGM bgm;							///<SLOTBGM
	
	ARCHANDLE *arc_handle;
	GF_BGL_INI *bgl;
	
	NNSG2dScreenData *bg_pScr;
	NNSG2dCharacterData *bg_pChar;
	NNSG2dPaletteData *bg_pPltt;
	
	EOA_SYS_PTR eoa_sys;
	CLACTSETDATA *clactset;
	EOA_PTR eoa_reel_bighit;

	u32 payout_total;
	u32 bet_total;
	u32 game_count;
	u32 ngame_count;
	u32 bmode_count;
	u32 bgame_count;
	u32 kihon_a_count;
	u32 kihon_b_count;
	u32 keizoku_50_count;
	u32 keizoku_70_count;
	u32 keizoku_90_count;
	u32 metamon_count;
	u32 pippi_count;
	u32 rare_pippi_count;
	u32 navi_hit_count;
	u32 replay_hit_count;
	u32 replay_hit_b_count;
	u32 cherry_hit_count;
	u32 cherry_hit_b_count;
	u32 bell_hit_count;
	u32 bell_hit_b_count;
	u32 suika_hit_count;
	u32 suika_hit_b_count;
	u32 ginga_hit_count;
	u32 seven_hit_count;
	u32 moonlight_count;
	u32 moonred_count;
	
	WINTYPE win_type;
#ifdef DEBUG_ON_SLOT
	D_SLOTWORK d_work;
#endif
};

#define SLOTMAIN_SIZE (sizeof(SLOTMAIN))

//==============================================================================
//	�O���Q��
//==============================================================================
//--------------------------------------------------------------
//	slot.c
//--------------------------------------------------------------
extern void SlotTalkWinFont_Init( SLOTMAIN *main );
static void SlotTalkWinFont_Delete( SLOTMAIN *main );
extern void SlotTalkWin_Write( SLOTMAIN *main, u32 type );
extern void SlotTalkWin_Clear( SLOTMAIN *main );

extern void SlotBGM_Play( SLOTMAIN *main, BGMTYPE type );

extern void * Slot_AllocMemory( u32 size );
extern void * Slot_AllocMemoryLo( u32 size );
extern void * SlotArc_DataLoad( SLOTMAIN *main, u32 id, int fb );

//--------------------------------------------------------------
///	slot_main.c
//--------------------------------------------------------------
extern void SlotMain_GameInit( SLOTMAIN *main );
extern void SlotMain_GameDelete( SLOTMAIN *main );

extern int SlotMain_Game( SLOTMAIN *main );

static void ReelControlTcb( TCB_PTR tcb, void *wk );

extern REEL_PATTERN Slot_ReelPatternGet( SLOTMAIN *main, REEL_NUM no, int offs );
extern REEL_PATTERN Slot_ReelPatternGridGet( SLOTMAIN *main, REEL_NUM no, int offs );

//--------------------------------------------------------------
//	slot_sub.c
//--------------------------------------------------------------
extern void SlotSubEoa_ReelPatternInit( SLOTMAIN *main );
extern void SlotSubEoa_CreditFontInit( SLOTMAIN *main );
extern void SlotSubEoa_PayOutFontInit( SLOTMAIN *main );
//extern void SlotSubEoa_WinLoseFontInit( SLOTMAIN *main );

extern EOA_PTR SlotSubEoa_MBallSet( SLOTMAIN *main, BALLTYPE type );
extern void SlotSubEoa_MBallMoveTypeChange( EOA_PTR eoa, MBALLMT type );
extern void SlotSubEoa_MBallVanishSet( EOA_PTR eoa, int vanish );
extern int SlotSubEoa_MBallMoveEndCheck( EOA_PTR eoa );

extern EOA_PTR SlotSubEoa_BallEffSet( SLOTMAIN *main );
extern int SlotSubEoa_BallEffEndCheck( EOA_PTR eoa );

extern EOA_PTR SlotSubEoa_PipSet( SLOTMAIN *main, PIPTYPE type );
extern void SlotSubEoa_PipMoveTypeChange( EOA_PTR eoa, PIPMT type );
extern int SlotSubEoa_PipMoveEndCheck( EOA_PTR eoa );

extern EOA_PTR SlotSubEoa_PikaSet( SLOTMAIN *main );
extern int SlotSubEoa_PikaEndCheck( EOA_PTR eoa );

extern EOA_PTR SlotSubEoa_BonusFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_BigBonusFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_GetFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_BigGetFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_BCountFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_GetCountFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_BigCountFont( SLOTMAIN *main, BIGFONTTYPE type );
extern EOA_PTR SlotSubEoa_MoonFontInit( SLOTMAIN *main, u32 count );

extern EOA_PTR SlotSubEoa_ReelBigHitInit( SLOTMAIN *main );

//--------------------------------------------------------------
//	slot_data.c
//--------------------------------------------------------------
extern const REEL_PATTERN DATA_SlotDataReelPattern[REEL_MAX][REEL_PT_MAX];
extern const int DATA_SlotPayOutSmall[REEL_PATTERN_MAX];
extern const int DATA_SlotPayOutBonus[REEL_PATTERN_MAX];
extern const u32 DATA_SlotBasicLotteryA[SLOT_HARD_MAX];
extern const LT_SMALLDATA DATA_SlotSmallLotteryA[SLOT_HARD_MAX];
extern const u32 DATA_LotteryNavi[SLOT_HARD_MAX];
extern const LT_CONT_BONUS DATA_LotteryContinueBonus[SLOT_HARD_MAX][CONT_BONUS_TYPE_MAX];
extern const LT_POKE_ENTRY DATA_LotteryPokeEntry[SLOT_HARD_MAX][CONT_BONUS_MAX][PIP_MAX];
extern const u32 DATA_ContinueBonusTypeParam[CONT_BONUS_TYPE_MAX];
extern const u32 DATA_SlotBasicLotteryB[SLOT_HARD_MAX];
extern const u32 DATA_SlotSmallLotteryB[SLOT_HARD_MAX][4];
extern const u32 DATA_LotteryMoonLight[SLOT_HARD_MAX];
extern const u32 DATA_LotteryMoonLightRed[SLOT_HARD_MAX];
extern const u32 DATA_LotteryBonusContinue[SLOT_HARD_MAX][CONT_BONUS_DOWN_MAX];
extern const LT_CONTBONUSEND DATA_LotteryContinueBonusEnd[SLOT_HARD_MAX][CONT_BONUSEND_NUM_MAX];

//--------------------------------------------------------------
//	slot_clact.c
//--------------------------------------------------------------
extern CLACTSETDATA * ClActSetDataInit(
		u32 heap_id,
		u32 actmax, u32 transmax,
		u32 charmax, u32 plttmax, u32 cellmax, u32 anmmax,
		u32 charnonid, u32 plttnonid, u32 cellnonid, u32 anmnonid );
extern void ClActSetDataDelete( CLACTSETDATA *set );
extern void ClActSetDataDraw( CLACTSETDATA *set );
extern void ClActCharAdd( CLACTSETDATA *set, u32 type, ARCHANDLE *hand, u32 arcid, u32 id );
extern void ClActCharVramAreaSet( CLACTSETDATA *set, u32 id );
extern void ClActCharResDelete( CLACTSETDATA *set, u32 id );
extern void ClActPlttAdd( CLACTSETDATA *set, u32 type, ARCHANDLE *hand, u32 arcid, u32 id );
extern void ClActPlttVramAreaSet( CLACTSETDATA *set, u32 id );
extern void ClActPlttResDelete( CLACTSETDATA *set, u32 id );
extern const NNSG2dImagePaletteProxy * ClActPlttProxyGet( CLACTSETDATA *set, u32 id );
extern void ClActCellAdd( CLACTSETDATA *set, ARCHANDLE *hand, u32 arcid, u32 id );
extern void ClActAnmAdd( CLACTSETDATA *set, ARCHANDLE *hand, u32 arcid, u32 id );
extern void ClActGraphicDelete(CLACTSETDATA *set,u32 charid,u32 plttid,u32 cellid,u32 anmid );
extern void ClActAdd( CLACTSETDATA *set, CLACT_WORK_EX *actwork,
		const VecFx32 *vec, u32 drawtype, int celltrans,
		u32 char_id, u32 pltt_id, u32 cell_id, u32 cellanm_id, int bg_pri, int act_pri );
extern void ClActDelete( CLACT_WORK_EX *actwork );
extern void ClActMatrixGet( CLACT_WORK_PTR act, VecFx32 *mtx );
extern void ClActScaleGet( CLACT_WORK_PTR act, VecFx32 *scale );

#endif //SLOT_MAIN_H_FILE

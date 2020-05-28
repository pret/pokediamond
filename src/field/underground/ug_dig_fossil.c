//=============================================================================
/**
 * @file	comm_dig_fossil.c
 * @brief	���΂ƃ~�j�Q�[���̃N���X
 * @author	Katsumi Ohno
 * @date    2005.12.06
 */
//=============================================================================


#include <nitro/os.h>
#include "common.h"
//
//����
//
#include "communication/communication.h"
#include "../comm_field_state.h"
#include "ug_manager.h"
#include "../fieldsys.h"
#include "system/arc_util.h"
#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/window.h"      //TalkWinGraphicSet
#include "system/wipe.h"
#include "ug_fossil.naix"
#include "ug_parts.naix"
#include "ug_anim.naix"
#include "ug_trap.naix"

#include "system/wordset.h"
#include "msgdata/msg_underworld.h"
#include "system/bmp_menu.h"  //yesno menu
#include "../syswork.h"
#include "../fieldmap.h"   //yesno menu
#include "../fld_bmp.h"
#include "../talk_msg.h"
#include "../fieldmap_work.h"  // FLDHBLANK_SYS_Start
#include "field/eventflag.h"
#include "../sysflag.h"
#include "../tv_topic.h"

//==============================================================================
// ��`
//==============================================================================

#define _PICTTEST (0)

#define _FOSSIL_NUM_MAX  (250)  ///< ���΃|�C���g����
#define _SETUP_NUM_MAX   (25)   ///< �P�O�g�Z�b�g����
#define _UG_BLOCK_MAX (30)

#define _PARTS_NUM_MAX   (8)          ///< ���܂��Ă�����̂̌��E
#define _PARTS_TREASURE_NUM_MAX (4)  ///< ��̌��E �c��͍d����
#define _EVWIN_MSG_BUF_SIZE		(50*2)			//���b�Z�[�W�o�b�t�@�T�C�Y

#define _DIGMAP_WIDTH    (13)    ///< ����
#define _DIGMAP_HEIGHT   (10)    ///< ����
#define _DIGMAP_INVALID  (0xff)   ///< �@�邱�Ƃ��ł��Ȃ��ꏊ
#define _FRIEND_DIG_AREA  (10)   ///< �ǂ̂��炢�߂���Ύ�`���Ă����̂�

#define _DIG_GAUGE_START (200-4)   ///< �@��Q�[�W�̃X�^�[�g

#define _PUSH_START (2)

#define _FAILED_BRIGHTNESS_SYNC   (15)  // ���Ό@�莸�s

typedef enum {
    _HUMMER_BUTTON,
    _PIC_BUTTON,
    _END_BUTTON,
};

#define _COST_DIG_HUMMER   (8)   ///< �n���}�[�̏����
#define _COST_DIG_PIC   (4)   ///< �m�~�̏����

// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐�
#define CLACT_OBJ_NUM (2)
#define CLACT_RESOURCE_NUM		(  4*CLACT_OBJ_NUM )
#define SUB_LCD  (1)
#define MAIN_LCD  (0)
#define BOTH_LCD  (2)


typedef enum{
    _CLACT_HUMMER,  // ACTID
    _CLACT_HIBI,  // ACTID
    _CLACT_EFFECT, //
    _CLACT_HIT, //
    _CLACT_KIRA_SINGLE,  //

    _CLACT_KIRA_P1,  //
    _CLACT_KIRA_P2,  //
    _CLACT_KIRA_P3,  //

    _CLACT_MAX,
} _ClactWorkType_e;

//==============================================================================
//	�^�錾
//==============================================================================

typedef struct{  // �X�N���[���pRECT�\����
    u8 lt_x;
    u8 lt_y;
    u8 rb_x;
    u8 rb_y;
} _SCR_RECT;

typedef struct{
    u16 xpos;
    u16 zpos;
    u8 netID;
} _RESULT_RADAR;

typedef struct{
    int seq;
    int subseq;
    int timer;
    int _PARTS_TREASURE_NUM;
    FIELDSYS_WORK* pFSys;
    int kiraTimer;
    void* pPalBuff[_PARTS_TREASURE_NUM_MAX];  // �p���b�g�������s���̂�
    NNSG2dPaletteData* palData[_PARTS_TREASURE_NUM_MAX];
    int digTimer[_PARTS_TREASURE_NUM_MAX];
    int digCarat;
    u8 bSuccess;
} FossilEventTask;

typedef struct{
    u16 xpos;
    u16 zpos;
    u8 digCreatureNetID;
    u8 savedataPos;
} FossilPoint;

typedef struct{
    void* attribute;     // �A�g���r���[�g�f�[�^�ւ̃|�C���^  ��������NULL
    u16 random;
    u16 random1;
    u16 random2;
    u16 random3;
    u8 width;
    u8 height;
    u8 partsType;           // �p�[�c���
    u16 ncg;
    u16 ncl;
} FossilParts;


typedef struct{
    FossilParts* pParts;  // ���f�[�^�Q�ƃ|�C���^
    u8 partsType;           // �p�[�c���
    u8 x;
    u8 y;
    u8 dir;
    u8 bGetItem;
} FossilPartsData;

typedef struct{
    _RESULT_RADAR pcRadar[_FOSSIL_NUM_MAX]; // �p�\�R�����[�_�[�p
    u8 pcRadarIndex;  //�p�\�R�����[�_�[��M�p
    u16 pcRadarTimer;  //�p�\�R�����[�_�[�\���p
} _EVENT_PCRADAR_WORK;

// ���ΑS��
typedef struct{
    FIELDSYS_WORK* pFSys;   //
    GF_BGL_INI* bgl;   // ���΃~�j�Q�[���pBGL
    MATHRandContext32 sRand;
	CLACT_SET_PTR 			clactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	resMan[4];				// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	resObjTbl[CLACT_RESOURCE_NUM];// ���\�[�X�I�u�W�F�e�[�u��
	CLACT_HEADER			clActHeader_m;							// �Z���A�N�^�[�w�b�_�[
	CLACT_HEADER			clActHeader_s[CLACT_OBJ_NUM];	// �Z���A�N�^�[�w�b�_�[
    CLACT_WORK_PTR			clActWork[_CLACT_MAX];          // �Z���A�N�^�[���[�N�|�C���^�z��

    FossilPoint aFossilPoint[_FOSSIL_NUM_MAX];  //
    BMPMENU_WORK* pYesNoWork;
    FossilPoint* pEntryFossil[COMM_MACHINE_MAX]; ///< �@��\�񒆂̉���
    u8 bEntryFossil[COMM_MACHINE_MAX]; ///< �@��\�񒆂̉���
    FossilPartsData aDeposit[_PARTS_NUM_MAX];  // ������ _partsData �̃|�C���^
    u8 radarIndex[COMM_MACHINE_MAX];
    TCB_PTR pPcRadar;
    TCB_PTR pDigStart;
    TCB_PTR pDFETCB;
    _EVENT_PCRADAR_WORK* pPcRadarWork;
    _RESULT_RADAR pcRadarInter[8];   //5x5�O���b�h���Ε\���p
    u8 radarIntervalTimer[COMM_MACHINE_MAX];
    void* pAlloc;  // �A���P�[�^�[
    u8 logMsgFossil[COMM_MACHINE_MAX];
    u8 friendDigPointX[COMM_MACHINE_MAX];
    u8 friendDigPointZ[COMM_MACHINE_MAX];
    u8 depositMap[ _DIGMAP_HEIGHT ][ _DIGMAP_WIDTH ];   // ����MAP  ��������index+1������ 0�͖������Ă��Ȃ�
    u8 buildupMap[ _DIGMAP_HEIGHT ][ _DIGMAP_WIDTH ];   // �͐�MAP
    int winIndex;
    u8 bPic;   // �݂̂��ǂ���
    u8 touchPanelRelease; // �^�b�`�p�l���𗣂����� 1
    u8 touchButton;
    u8 digGauge;   // �@��Q�[�W
    u8 shakeCount; // ��ʗh�炵
    s8 shakeX;
    s8 shakeZ;
    u8 resObjCount;
    u8 setNumT;   // TRAP�𖄂߂���
} CommFossilWork;


//==============================================================================
// ���[�N
//==============================================================================
// �V���O���g��
static CommFossilWork* _pCommFossilWork = NULL;

//==============================================================================
// static�錾
//==============================================================================

// ���������邩�ǂ�����MAP  �������Ȃ��̂Ŏ菑���@�����ɖ����͎̂l�p�`�S��������


static u8 _attribute_bone[6][3]={
    {'x','x','x'},
    {'o','x','o'},
    {'o','x','o'},
    {'o','x','o'},
    {'o','x','o'},
    {'x','x','x'},
};

static u8 _attribute_bone90[3][6]={
    {'x','o','o','o','o','x'},
    {'x','x','x','x','x','x'},
    {'x','o','o','o','o','x'},
};

static u8 _attribute_iwa03[2][3]={
    {'x','x','x'},
    {'o','x','o'},
};

static u8 _attribute_iwa0390[3][2]={
    {'o','x'},
    {'x','x'},
    {'o','x'},
};

static u8 _attribute_iwa03180[2][3]={
    {'o','x','o'},
    {'x','x','x'},
};

static u8 _attribute_iwa03270[3][2]={
    {'x','o'},
    {'x','x'},
    {'x','o'},
};

static u8 _attribute_iwa04[2][3]={
    {'x','x','o'},
    {'o','x','x'},
};

static u8 _attribute_iwa0490[3][2]={
    {'o','x'},
    {'x','x'},
    {'x','o'},
};

static u8 _attribute_iwa05[2][3]={
    {'o','x','x'},
    {'x','x','o'},
};

static u8 _attribute_iwa0590[3][2]={
    {'x','o'},
    {'x','x'},
    {'o','x'},
};


static u8 _attribute_kai[4][4]={
    {'o','x','x','x'},
    {'x','x','x','x'},
    {'x','x','x','x'},
    {'x','x','x','o'},
};

static u8 _attribute_kai90[4][4]={
    {'x','x','x','o'},
    {'x','x','x','x'},
    {'x','x','x','x'},
    {'o','x','x','x'},
};

static u8 _attribute_kaminari[3][3]={
    {'o','x','x'},
    {'x','x','x'},
    {'x','x','o'},
};

static u8 _attribute_kohaku[4][4]={
    {'o','x','x','x'},
    {'x','x','x','x'},
    {'x','x','x','x'},
    {'x','x','x','o'},
};

static u8 _attribute_kohaku90[4][4]={
    {'x','x','x','o'},
    {'x','x','x','x'},
    {'x','x','x','x'},
    {'o','x','x','x'},
};

static u8 _attribute_koura[4][5]={
    {'x','x','x','x','x'},
    {'x','x','x','x','x'},
    {'x','x','x','x','x'},
    {'o','x','x','x','o'},
};

static u8 _attribute_mizu[3][3]={
    {'x','x','x'},
    {'x','x','x'},
    {'x','x','o'},
};

static u8 _attribute_moon[2][4]={
    {'o','x','x','x'},
    {'x','x','x','o'},
};

static u8 _attribute_moon90[4][2]={
    {'x','o'},
    {'x','x'},
    {'x','x'},
    {'o','x'},
};

static u8 _attribute_tsume[5][4]={
    {'o','o','x','x'},
    {'o','x','x','x'},
    {'o','x','x','x'},
    {'x','x','x','o'},
    {'x','x','o','o'},
};

static u8 _attribute_tsume90[4][5]={
    {'x','x','o','o','o'},
    {'x','x','x','x','o'},
    {'o','x','x','x','x'},
    {'o','o','x','x','x'},
};

static u8 _attribute_tsume180[5][4]={
    {'o','o','x','x'},
    {'o','x','x','x'},
    {'x','x','x','o'},
    {'x','x','x','o'},
    {'x','x','o','o'},
};

static u8 _attribute_tsume270[4][5]={
    {'x','x','x','o','o'},
    {'x','x','x','x','o'},
    {'o','x','x','x','x'},
    {'o','o','o','x','x'},
};

static u8 _attribute_sun[3][3]={
    {'o','x','o'},
    {'x','x','x'},
    {'x','x','x'},
};

static u8 _attribute_star[3][3]={
    {'o','x','o'},
    {'x','x','x'},
    {'o','x','o'},
};

static u8 _attribute_reaf90[3][4]={
    {'o','x','x','o'},
    {'x','x','x','x'},
    {'o','x','x','o'},
};

static u8 _attribute_reaf[4][3]={
    {'o','x','o'},
    {'x','x','x'},
    {'x','x','x'},
    {'o','x','o'},
};

static u8 _attribute_nekko[5][5]={
    {'x','x','x','x','o'},
    {'x','x','x','x','x'},
    {'x','x','o','x','x'},
    {'o','o','o','x','x'},
    {'o','o','x','x','o'},
};

static u8 _attribute_nekko90[5][5]={
    {'o','o','x','x','x'},
    {'o','o','x','x','x'},
    {'x','o','o','x','x'},
    {'x','x','x','x','x'},
    {'o','x','x','x','o'},
};

static u8 _attribute_nekko180[5][5]={
    {'o','x','x','o','o'},
    {'x','x','o','o','o'},
    {'x','x','o','x','x'},
    {'x','x','x','x','x'},
    {'o','x','x','x','x'},
};


static u8 _attribute_nekko270[5][5]={
    {'o','x','x','x','o'},
    {'x','x','x','x','x'},
    {'x','x','o','o','x'},
    {'x','x','x','o','o'},
    {'x','x','x','o','o'},
};

static u8 _attribute_kakera_red[3][3]={
    {'x','x','x'},
    {'x','x','o'},
    {'x','x','x'},
};
static u8 _attribute_kakera_blue[3][3]={
    {'x','x','x'},
    {'x','x','x'},
    {'x','x','o'},
};
static u8 _attribute_kakera_yellow[3][4]={
    {'x','o','x','o'},
    {'x','x','x','o'},
    {'x','x','x','x'},
};
static u8 _attribute_kakera_green[3][4]={
    {'x','x','x','x'},
    {'x','x','x','x'},
    {'x','x','o','x'},
};

static u8 _attribute_heart[2][2]={
    {'x','o'},
    {'x','x'},
};

static u8 _attribute_shield[4][5]={
    {'o','x','x','x','o'},
    {'o','x','x','x','o'},
    {'x','x','x','x','x'},
    {'o','x','x','x','o'},
};


static u8 _attribute_zugai[4][4]={
    {'x','x','x','x'},
    {'x','x','x','x'},
    {'x','x','x','x'},
    {'o','x','x','o'},
};

static u8 _attribute_cray[4][4]={
    {'x','o','x','o'},
    {'x','x','x','x'},
    {'x','x','x','x'},
    {'o','x','o','x'},
};

static u8 _attribute_cold[4][4]={
    {'o','x','x','o'},
    {'x','x','x','x'},
    {'x','x','x','x'},
    {'x','o','o','x'},
};

static u8 _attribute_heat[3][4]={
    {'x','o','x','o'},
    {'x','x','x','x'},
    {'x','x','x','x'},
};

static u8 _attribute_sara[4][4]={
    {'o','o','x','o'},
    {'x','x','x','o'},
    {'o','x','x','x'},
    {'o','x','o','o'},
};

static u8 _attribute_wet[3][4]={
    {'x','x','x'},
    {'x','x','x'},
    {'x','o','x'},
};

    
// ���΃p�[�c
static FossilParts _partsData[]={
    //���񂲂�����	kaseki_kongou_s    
    {NULL, 30, 22, 27, 20, 4,4, DIG_PARTS_KONGOU_S,
        NARC_ug_parts_kaseki_kongou_s_NCGR,
        NARC_ug_parts_kaseki_kongou_NCLR},
    //���炽��	kaseki_siratama_s
    {NULL, 22, 30, 20, 27, 4,4, DIG_PARTS_SIRATAMA_S,
        NARC_ug_parts_kaseki_siratama_s_NCGR,
        NARC_ug_parts_kaseki_siratama_NCLR},
    //����������
    {NULL, 166,192,122,150, 4,4, DIG_PARTS_RED_S,
        NARC_ug_parts_kaseki_akatama_s_NCGR,
        NARC_ug_parts_kaseki_akatama_NCLR},
    //����������
    {NULL, 192,166,150,122, 4,4,  DIG_PARTS_BLUE_S,
        NARC_ug_parts_kaseki_aotama_s_NCGR,
        NARC_ug_parts_kaseki_aotama_NCLR},
    //�݂ǂ�̂���
    {NULL, 150,150,106,106, 4,4, DIG_PARTS_GREEN_S,
        NARC_ug_parts_kaseki_midotama_s_NCGR,
        NARC_ug_parts_kaseki_midotama_NCLR},
    //�������񂲂�����	kaseki_kongou_l
    {NULL, 15, 13, 13, 10, 6,6, DIG_PARTS_KONGOU_L,
        NARC_ug_parts_kaseki_kongou_l_NCGR,
        NARC_ug_parts_kaseki_kongou_NCLR},
    //�������炽��	kaseki_siratama_l
    {NULL, 13, 15, 10, 13, 6,6, DIG_PARTS_SIRATAMA_L,
        NARC_ug_parts_kaseki_siratama_l_NCGR,
        NARC_ug_parts_kaseki_siratama_NCLR},
    //������������	kaseki_akatama_l
    {NULL, 83, 96, 61, 75, 6,6, DIG_PARTS_RED_L,
        NARC_ug_parts_kaseki_akatama_l_NCGR,
        NARC_ug_parts_kaseki_akatama_NCLR},
    //������������	kaseki_aotama_l
    {NULL, 96, 83, 75, 61, 6,6, DIG_PARTS_BLUE_L,
        NARC_ug_parts_kaseki_aotama_l_NCGR,
        NARC_ug_parts_kaseki_aotama_NCLR},
    //�����݂ǂ肽��	kaseki_midotama_l
    {NULL, 75, 75, 53, 53, 6,6, DIG_PARTS_GREEN_L,
        NARC_ug_parts_kaseki_midotama_l_NCGR,
        NARC_ug_parts_kaseki_midotama_NCLR},
    //�܂�܂�	kaseki_manmaru
    {NULL,  0,0,0,0, 6,6, DIG_PARTS_CIRCLE,
        NARC_ug_parts_kaseki_manmaru_NCGR,
        NARC_ug_parts_kaseki_manmaru_NCLR},
    //���Ȃ�	kaseki_kaname                              
    {NULL,  0,0,2,2, 8,8, DIG_PARTS_KEYSTONE,
        NARC_ug_parts_kaseki_kaname_NCGR,
        NARC_ug_parts_kaseki_kaname_NCLR},
    //�����悤�̂���	kaseki_sun
    {_attribute_sun, 4,1,15,3, 6,6, DIG_PARTS_SUN,
        NARC_ug_parts_kaseki_sun_NCGR,
        NARC_ug_parts_kaseki_sun_NCLR},
    //�ق��̂�����	kaseki_star                            ��
    {_attribute_star, 2,2,10,10, 6,6, DIG_PARTS_STAR,
        NARC_ug_parts_kaseki_star_NCGR,
        NARC_ug_parts_kaseki_star_NCLR},
    //���̂���	kaseki_moon                            ��
    {_attribute_moon, 1,2,1,8, 8,4, DIG_PARTS_MOON,
        NARC_ug_parts_kaseki_moon_NCGR,
        NARC_ug_parts_kaseki_moon_NCLR},
    //���̂���90	kaseki_moon90
    {_attribute_moon90, 1,2,2,7, 4,8, DIG_PARTS_MOON,
        NARC_ug_parts_kaseki_moon90_NCGR,
        NARC_ug_parts_kaseki_moon_NCLR},
    //����������	kaseki_hard
    {NULL, 4,4,20,20, 4,4, DIG_PARTS_HARD,
        NARC_ug_parts_kaseki_hard_NCGR,
        NARC_ug_parts_kaseki_hard_NCLR},
    //���݂Ȃ�̂���	kaseki_kaminari                   ��
    {_attribute_kaminari, 4,1,30,5, 6,6,DIG_PARTS_KAMINARI,
        NARC_ug_parts_kaseki_kaminari_NCGR,
        NARC_ug_parts_kaseki_kaminari_NCLR},
    //����炸�̂���	kaseki_kawarazu
    {NULL, 4,4,20,20, 8,4, DIG_PARTS_KAWARAZU,
        NARC_ug_parts_kaseki_kawarazu_NCGR,
        NARC_ug_parts_kaseki_kawarazu_NCLR},
    //�ق̂��̂���	kaseki_honoo                          
    {NULL, 4,1,30,5, 6,6, DIG_PARTS_HONOO,
        NARC_ug_parts_kaseki_honoo_NCGR,
        NARC_ug_parts_kaseki_honoo_NCLR},
    //�݂��̂���	kaseki_mizu
    {_attribute_mizu, 1,4,5,30, 6,6, DIG_PARTS_MIZU,
        NARC_ug_parts_kaseki_mizu_NCGR,
        NARC_ug_parts_kaseki_mizu_NCLR},
    //���[�t�̂���	kaseki_reaf                       
    {_attribute_reaf, 1,2,3,15, 6,8, DIG_PARTS_REAF,
        NARC_ug_parts_kaseki_reaf_NCGR,
        NARC_ug_parts_kaseki_reaf_NCLR},
    //���[�t�̂���	kaseki_reaf
    {_attribute_reaf90, 1,2,2,15, 8,6, DIG_PARTS_REAF,
        NARC_ug_parts_kaseki_reaf90_NCGR,
        NARC_ug_parts_kaseki_reaf_NCLR},
    //�����̃J�Z�L	kaseki_kai
    {_attribute_kai, 0,0,3,1, 8,8, DIG_PARTS_KAI,
        NARC_ug_parts_kaseki_kai_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�����̃J�Z�L	kaseki_kai90
    {_attribute_kai90, 0,0,3,1, 8,8, DIG_PARTS_KAI,
        NARC_ug_parts_kaseki_kai90_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�����̃J�Z�L	kaseki_kai180
    {_attribute_kai, 0,0,3,1, 8,8, DIG_PARTS_KAI,
        NARC_ug_parts_kaseki_kai180_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�����̃J�Z�L	kaseki_kai270
    {_attribute_kai90, 0,0,3,1, 8,8, DIG_PARTS_KAI,
        NARC_ug_parts_kaseki_kai270_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //������̃J�Z�L	kaseki_koura
    {_attribute_koura, 0,0,1,13, 10,8, DIG_PARTS_KOURA,
        NARC_ug_parts_kaseki_koura_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�c���̃J�Z�L	kaseki_tsume
    {_attribute_tsume, 0,0,3,1, 8,10, DIG_PARTS_TSUME,
        NARC_ug_parts_kaseki_tsume_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�c���̃J�Z�L	kaseki_tsume90
    {_attribute_tsume90, 0,0,3,1, 10,8, DIG_PARTS_TSUME,
        NARC_ug_parts_kaseki_tsume90_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�c���̃J�Z�L	kaseki_tsume180
    {_attribute_tsume180, 0,0,3,1, 8,10, DIG_PARTS_TSUME,
        NARC_ug_parts_kaseki_tsume180_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�c���̃J�Z�L	kaseki_tsume270
    {_attribute_tsume270, 0,0,3,1, 10,8, DIG_PARTS_TSUME,
        NARC_ug_parts_kaseki_tsume270_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�˂����̃J�Z�L	kaseki_nekko
    {_attribute_nekko, 0,0,1,3, 10,10, DIG_PARTS_NEKKO,
        NARC_ug_parts_kaseki_nekko_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�˂����̃J�Z�L	kaseki_nekko90
    {_attribute_nekko90, 0,0,1,3, 10,10, DIG_PARTS_NEKKO,
        NARC_ug_parts_kaseki_nekko90_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�˂����̃J�Z�L	kaseki_nekko180
    {_attribute_nekko180, 0,0,1,3, 10,10, DIG_PARTS_NEKKO,
        NARC_ug_parts_kaseki_nekko180_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�˂����̃J�Z�L	kaseki_nekko270
    {_attribute_nekko270, 0,0,1,3, 10,10, DIG_PARTS_NEKKO,
        NARC_ug_parts_kaseki_nekko270_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�Ђ݂̃R�n�N	kaseki_kohaku
    {_attribute_kohaku, 0,0,2,2, 8,8, DIG_PARTS_KOHAKU,
        NARC_ug_parts_kaseki_kohaku_NCGR,
        NARC_ug_parts_kaseki_kohaku_NCLR},
    //�Ђ݂̃R�n�N	kaseki_kohaku90
    {_attribute_kohaku90, 0,0,3,3, 8,8, DIG_PARTS_KOHAKU,
        NARC_ug_parts_kaseki_kohaku90_NCGR,
        NARC_ug_parts_kaseki_kohaku_NCLR},
    //�����傤�Ȃق�	kaseki_bone                           ��
    {_attribute_bone, 1,1,5,5, 6,12, DIG_PARTS_BONE,
        NARC_ug_parts_kaseki_bone_NCGR,
        NARC_ug_parts_kaseki_bone_NCLR},
    //�����傤�Ȃق�	kaseki_bone90
    {_attribute_bone90, 1,1,5,5, 12,6, DIG_PARTS_BONE,
        NARC_ug_parts_kaseki_bone90_NCGR,
        NARC_ug_parts_kaseki_bone_NCLR},
//���񂫂̂�����
    {_attribute_star, 10,10,10,10, 6,6, DIG_PARTS_GENKI_S,
        NARC_ug_parts_kaseki_genki_s_NCGR,
        NARC_ug_parts_kaseki_genki_NCLR},
//���񂫂̂����܂�
    {NULL, 1,1,2,2, 6,6, DIG_PARTS_GENKI_L,
        NARC_ug_parts_kaseki_genki_l_NCGR,
        NARC_ug_parts_kaseki_genki_NCLR},
    //������������
    {_attribute_kakera_red, 10,15,12,22, 6,6, DIG_PARTS_PLA_RED,
        NARC_ug_parts_kaseki_pla_r_NCGR,
        NARC_ug_parts_kaseki_pla_fire_NCLR},
    //������������
    {_attribute_kakera_blue, 15,10,25,15, 6,6, DIG_PARTS_PLA_BLUE,
        NARC_ug_parts_kaseki_pla_b_NCGR,
        NARC_ug_parts_kaseki_pla_water_NCLR},
    //�����낢������
    {_attribute_kakera_yellow, 15,10,22,12, 8,6, DIG_PARTS_PLA_YELLOW,
        NARC_ug_parts_kaseki_pla_y_NCGR,
        NARC_ug_parts_kaseki_pla_thunder_NCLR},
    //�݂ǂ�̂�����
    {_attribute_kakera_green, 10,15,12,22, 8,6, DIG_PARTS_PLA_GREEN,
        NARC_ug_parts_kaseki_pla_g_NCGR,
        NARC_ug_parts_kaseki_pla_reef_NCLR},
    //�n�[�g�̃E���R
    {_attribute_heart, 33,33,30,30, 4,4, DIG_PARTS_HEART,
        NARC_ug_parts_kaseki_hart_NCGR,
        NARC_ug_parts_kaseki_hart_NCLR},
    //���ẴJ�Z�L
    {_attribute_shield, 0,25,0,12, 10,8, DIG_PARTS_SHIELD,
        NARC_ug_parts_kaseki_tate_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�������̃J�Z�L
    {_attribute_zugai, 25,0,12,0, 8, 8, DIG_PARTS_ZUGAI,
        NARC_ug_parts_kaseki_zugai_NCGR,
        NARC_ug_parts_kaseki_kaseki_NCLR},
    //�Ђ���̂˂��
    {_attribute_cray, 1,1,5,2, 8, 8, DIG_PARTS_CRAY,
        NARC_ug_parts_kaseki_nendo_NCGR,
        NARC_ug_parts_kaseki_nendo_NCLR},
    //���낢�Ă����イ
    {NULL, 1,1,2,5, 6, 6, DIG_PARTS_IRONBALL,
        NARC_ug_parts_kaseki_black_NCGR,
        NARC_ug_parts_kaseki_black_NCLR},
    //�߂�������
    {_attribute_cold, 2,1,11,5, 8, 8, DIG_PARTS_COLD,
        NARC_ug_parts_kaseki_cold_NCGR,
        NARC_ug_parts_kaseki_cold_NCLR},
    //���炳�炢��
    {_attribute_sara, 1,2,5,11, 8, 8, DIG_PARTS_SARA,
        NARC_ug_parts_kaseki_sara_NCGR,
        NARC_ug_parts_kaseki_sara_NCLR},
    //��������
    {_attribute_heat, 2,1,11,5, 8, 6, DIG_PARTS_HEAT,
        NARC_ug_parts_kaseki_heet_NCGR,
        NARC_ug_parts_kaseki_heet_NCLR},
    //���߂�������
    {_attribute_wet, 1,2,5,11, 6, 6, DIG_PARTS_WET,
        NARC_ug_parts_kaseki_wet_NCGR,
        NARC_ug_parts_kaseki_wet_NCLR},
//�Ђ̂��܃v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_FIRE,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_fire_NCLR},
//�������v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_WATER,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_water_NCLR},
//�����Â��v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_THUNDER,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_thunder_NCLR},
//�݂ǂ�̃v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_GREEN,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_reef_NCLR},
//���̃v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_ICICLE ,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_ice_NCLR},
//���Ԃ��̃v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_KNUCKLE ,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_fist_NCLR},
//�����ǂ��v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_POISON,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_poison_NCLR},
//�������̃v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_GROUND,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_ground_NCLR},
//��������v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_SKY,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_sky_NCLR},
//�ӂ����̃v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_WONDER,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_wonder_NCLR},
//���܂ނ��v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_IRIDESCENCE ,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_beetle_NCLR},
//���񂹂��v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_ROCK,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_rock_NCLR},
//���̂̂��v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_GHOST,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_ghost_NCLR},
//��イ�̃v���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_DRAGON,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_dragon_NCLR},
//������ăv���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_DARK,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_dark_NCLR},
//�����Ăv���[�g
    {NULL, 1,1,1,1, 8, 6, DIG_PARTS_PLATE_IRON,
        NARC_ug_parts_kaseki_pla_n_NCGR,
        NARC_ug_parts_kaseki_pla_iron_NCLR},

    
    //�@��Ȃ���	kaseki_iwa01	�ʐς��S�}�X	�_�`�̐^�����̐�
    {NULL, 1,1,1,1, 8, 2, DIG_PARTS_NODIG1,
        NARC_ug_parts_kaseki_iwa01_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa01	�ʐς��S�}�X	�_�`�̐^�����̐�
    {NULL, 1,1,1,1, 2, 8, DIG_PARTS_NODIG1,
        NARC_ug_parts_kaseki_iwa0190_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa02	�ʐς��S�}�X	�l�p�^�̐^�����̐�
    {NULL, 1,1,1,1, 4, 4, DIG_PARTS_NODIG2,
        NARC_ug_parts_kaseki_iwa02_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa03	�ʐς��S�}�X	T�^�̐^�����̐�
    {_attribute_iwa03, 1,1,1,1, 6, 4, DIG_PARTS_NODIG3,
        NARC_ug_parts_kaseki_iwa03_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa0390	�ʐς��S�}�X	T�^�̐^�����̐�
    {_attribute_iwa0390, 1,1,1,1, 4, 6, DIG_PARTS_NODIG3,
        NARC_ug_parts_kaseki_iwa0390_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa03180	�ʐς��S�}�X	T�^�̐^�����̐�
    {_attribute_iwa03180, 1,1,1,1, 6, 4, DIG_PARTS_NODIG3,
        NARC_ug_parts_kaseki_iwa03180_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa03270	�ʐς��S�}�X	T�^�̐^�����̐�
    {_attribute_iwa03270, 1,1,1,1, 4, 6, DIG_PARTS_NODIG3,
        NARC_ug_parts_kaseki_iwa03270_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa04	�ʐς��S�}�X	Z�^�̐^�����̐�
    {_attribute_iwa04, 1,1,1,1, 6, 4, DIG_PARTS_NODIG4,
        NARC_ug_parts_kaseki_iwa04_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa0490	�ʐς��S�}�X	Z�^�̐^�����̐�
    {_attribute_iwa0490, 1,1,1,1, 4, 6, DIG_PARTS_NODIG4,
        NARC_ug_parts_kaseki_iwa0490_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa05	�ʐς��S�}�X	S�^�̐^�����̐�
    {_attribute_iwa05, 1,1,1,1, 6, 4, DIG_PARTS_NODIG5,
        NARC_ug_parts_kaseki_iwa05_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa0590	�ʐς��S�}�X	S�^�̐^�����̐�
    {_attribute_iwa0590, 1,1,1,1, 4, 6, DIG_PARTS_NODIG5,
        NARC_ug_parts_kaseki_iwa0590_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa06	�ʐς��X�}�X	�l�p�^�̐^�����̐�
    {NULL, 1,1,1,1, 6, 6, DIG_PARTS_NODIG6,
        NARC_ug_parts_kaseki_iwa06_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa07	�ʐς��W�}�X	�_�`�̐^�����̐�
    {NULL, 1,1,1,1, 4, 8, DIG_PARTS_NODIG7,
        NARC_ug_parts_kaseki_iwa07_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
    //�@��Ȃ���	kaseki_iwa07	�ʐς��W�}�X	�_�`�̐^�����̐�
    {NULL, 1,1,1,1, 8, 4, DIG_PARTS_NODIG7,
        NARC_ug_parts_kaseki_iwa0790_NCGR,
        NARC_ug_parts_kaseki_iwa_NCLR},
};


static void _gaugeDisp(GF_BGL_INI* bgl);
static void _setSetup(MATHRandContext16* pRand, int setIndex);
static FossilPoint* _getFreeFossilPoint(void);
static FossilPoint* _searchFossilPoint(u16 xpos, u16 zpos);
static void _yesnoMenuFunc(TCB_PTR tcb, void* work);
static void _commFossilGameInitialize1(FossilEventTask* pFET);
static void _commFossilGameInitialize2(void);
static void _digFossilEventStart(FIELDSYS_WORK* pFSys);
static BOOL _isEnd(void);
static void _randomDeposit(GF_BGL_INI* bgl,int charByte,FossilEventTask* pFET);
static void _depositBGInit(int idx, GF_BGL_INI* bgl, int charByte,FossilEventTask* pFET);
static void _randomBuildup(GF_BGL_INI* bgl);
static void _buildupBGDraw(GF_BGL_INI* bgl);
static BOOL _gameProcess(FossilEventTask* pFET);
static void _touchButtonInitialize(GF_BGL_INI* bgl);
static void _touchButtonProcess(GF_BGL_INI* bgl,int x, int y, int level);
static BOOL _treasureCheck(FossilEventTask* pFET);
static BOOL _fossilGetMessage(FossilEventTask* pFET);
static BOOL _fossilGetMessageBagIn(FossilEventTask* pFET);
static void _initCellActor(void);
static void _setCellActor(void);
static void char_pltt_manager_init(void);
static void vBlankFunc(void * work);
static void _pcRadarFunc(void);
static  FossilPoint* _addFossil(int xpos, int zpos);
static void _partsDigColor(FossilEventTask* pFET);
static void _shakeProcess(GF_BGL_INI* bgl);
static void _turnAroundSignalSend(void);
static void _reload(void);

static const BMPWIN_DAT _yesNoBmpDat = {
    FLD_MBGFRM_FONT, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };



//==============================================================================
// �֐�
//==============================================================================

//==============================================================================
/**
 * ���Ό@��Q�[���ɕK�v�Ȃ��̂̏�����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _initializeDigGame(void)
{
    int i;

    
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        _pCommFossilWork->friendDigPointX[i] = _DIGMAP_INVALID;
        _pCommFossilWork->friendDigPointZ[i] = _DIGMAP_INVALID;
    }
    _pCommFossilWork->bPic = TRUE;
    _pCommFossilWork->touchPanelRelease = 0;
    _pCommFossilWork->digGauge = _DIG_GAUGE_START;

    for(i = 0 ; i < _PARTS_NUM_MAX; i++){
        _pCommFossilWork->aDeposit[i].pParts = NULL;
        _pCommFossilWork->aDeposit[i].bGetItem = FALSE;
    }
    for(i = 0 ; i < _DIGMAP_WIDTH * _DIGMAP_HEIGHT; i++){
        _pCommFossilWork->depositMap[i / _DIGMAP_WIDTH][i % _DIGMAP_WIDTH] = 0;
        _pCommFossilWork->buildupMap[i / _DIGMAP_WIDTH][i % _DIGMAP_WIDTH] = 2;
    }
}

//==============================================================================
/**
 * ���Ό@��Ǘ��̏�����
 * @param   pWork   ��ƃ������[
 * @retval  none
 */
//==============================================================================

void CommFossilInitialize(void* pWork, FIELDSYS_WORK* pFSys)
{
    int i,num;
    UNDERGROUNDDATA* pUGData;
    if(_pCommFossilWork){
        return;
    }
    _pCommFossilWork = pWork;
    MI_CpuFill8(_pCommFossilWork, 0, sizeof(CommFossilWork));
    CommRandSeedInitialize(&_pCommFossilWork->sRand);
    
    _pCommFossilWork->pFSys = pFSys;
    for(i = 0; i < _FOSSIL_NUM_MAX; i++){
        _pCommFossilWork->aFossilPoint[i].digCreatureNetID = INVALID_NETID;
        _pCommFossilWork->aFossilPoint[i].xpos = COMM_UG_INVALID_GRID;
        _pCommFossilWork->aFossilPoint[i].zpos = COMM_UG_INVALID_GRID;
    }
    _initializeDigGame();

    _pCommFossilWork->winIndex = -1;
    
    pUGData = SaveData_GetUnderGroundData(_pCommFossilWork->pFSys->savedata);

    // �f�t�H���g�ŉ��Δz�u
    if(UnderGroundIsNewDay(pUGData)){
        MATHRandContext16 sRand;

        OHNO_PRINT("���΍Ĕz�u %d \n",UnderGroundGetDayRandSeed(pUGData));
        MATH_InitRand16(&sRand, UnderGroundGetDayRandSeed(pUGData));
        for(i = 0; i < UG_FOSSIL_PLACE_NUM_MAX; i++){
            UnderGroundDelFossilGroundItem(pUGData, i);  // �S����
        }
        for(i = 0; i < UG_NATURETRAP_PLACE_NUM_MAX; i++){
            UnderGroundAddNatureTrapGroundItem(pUGData, 0, i, 0, 0);
        }
        num = UgDigStoneSetOneFossil(&sRand);// �΂̋߂��ɉ��΂�u��
        num = _SETUP_NUM_MAX - (num / 10) - 1;
        for(i = 0; i < num; i++){   // num�Z�b�g���Δz�u
            _setSetup(&sRand, i);
        }
        UnderGroundResetNewDay(pUGData);  // ����ύX���Ȃ��t���O���Z�b�g

    }
    else{
        _reload();
        UgTrapNatureReload();
    }
}

//==============================================================================
/**
 * �Ό@��̃��[�N�T�C�Y�𓾂�
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

int CommFossilGetWorkSize(void)
{
    return sizeof(CommFossilWork);
}

//==============================================================================
/**
 * �Ό@��̃��Z�b�g
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFossilReset(void)
{
}

//==============================================================================
/**
 * �Ό@��̕��A����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFossilReboot(void)
{
}

//==============================================================================
/**
 * �Ό@��̏I��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFossilFinalize(void)
{
    if(_pCommFossilWork){
        if(_pCommFossilWork->pDigStart){
            TCB_Delete(_pCommFossilWork->pDigStart);
            _pCommFossilWork->pDigStart = NULL;
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            if(_pCommFossilWork->pYesNoWork){
                BmpYesNoWinDel(_pCommFossilWork->pYesNoWork,HEAPID_FIELD);
            }
            CommPlayerHoldEnd();
        }
        sys_FreeMemoryEz(_pCommFossilWork);
        _pCommFossilWork = NULL;
    }
}

//==============================================================================
/**
 * ���΂̃`�F�b�N�̏���
 * @param   netID   netID
 * @param   pTouch    �����ʒu
 * @retval  ���΂���������TRUE
 */
//==============================================================================

BOOL CommFossilCheck(int netID, Grid* pTouch)
{
    FossilPoint* pFP = _searchFossilPoint(pTouch->xpos, pTouch->zpos);
    u8 data;
    data = netID;

    if((pFP != NULL) && (pFP->digCreatureNetID==INVALID_NETID)){
        if(CommPlayerFlagDigCheck(netID)){   // �����̊�����
            return TRUE;
        }
        OHNO_PRINT("�܂��@���Ă��Ȃ��ꍇ �����M���𑗂� %d\n",pFP->savedataPos);
        CommSendData_ServerSide(CF_FIND_FOSSIL, &data, 1);
        CommPlayerSetMoveControl_Server(netID,FALSE);
        _pCommFossilWork->pEntryFossil[netID] = pFP;
        return TRUE;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * ���΂𖄂߂Ă����ꏊ���ǂ���
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static BOOL _isFillUpPoint(FIELDSYS_WORK* pFSys, int xpos, int zpos)
{
    if(UgSecretBaseIsSecretBasePlace(xpos,zpos)){
        OHNO_PRINT("���Δz�u���Ȃ� %d %d\n",xpos,zpos);
        return FALSE;
    }
    if(zpos > 478){
        OHNO_PRINT("���Δz�u���Ȃ� %d %d\n",xpos,zpos);
        return FALSE;
    }
    if(xpos > 478){
        OHNO_PRINT("���Δz�u���Ȃ� %d %d\n",xpos,zpos);
        return FALSE;
    }
    if(GetHitAttr(pFSys, xpos, zpos)){
        if(!GetHitAttr(pFSys, xpos, zpos+1)){
            return TRUE;
        }
        if(!GetHitAttr(pFSys, xpos, zpos-1)){
            return TRUE;
        }
        if(!GetHitAttr(pFSys, xpos+1, zpos)){
            return TRUE;
        }
        if(!GetHitAttr(pFSys, xpos-1, zpos)){
            return TRUE;
        }
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * ���΂P�Z�b�g��z�u����
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static void _setSetup(MATHRandContext16* pRand,int setIndex)
{
    int digNum,i,try,flg;
    u16 xpos,xpos2,xbase;
    u16 zpos,zpos2,zbase;
    FossilPoint* pFP;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(_pCommFossilWork->pFSys->savedata);

    xbase = (GetWorldMapMatrixW(_pCommFossilWork->pFSys->World)-2)*BLOCK_GRID_W;
    zbase = (GetWorldMapMatrixH(_pCommFossilWork->pFSys->World)-2)*BLOCK_GRID_H;
    do{  // �J���Ă���ꏊ��������
        xpos = MATH_Rand16(pRand, xbase)+BLOCK_GRID_W;
        zpos = MATH_Rand16(pRand, zbase)+BLOCK_GRID_H*2;
    } while(_isFillUpPoint(_pCommFossilWork->pFSys, xpos, zpos)==FALSE);

    digNum = MATH_Rand16(pRand, 6) + 6;  // ���΂����񖄂߂鐔
    for(i = 0; i < digNum; i++){
        flg = FALSE;
        for(try = 0 ; try < 100; try++){
            xpos2 = MATH_Rand16(pRand, 20) + xpos - 10;
            zpos2 = MATH_Rand16(pRand, 20) + zpos - 10;
            if(_isFillUpPoint(_pCommFossilWork->pFSys, xpos2, zpos2)){
                flg = TRUE;
                break;
            }
        }
        if( flg ){
            pFP = _getFreeFossilPoint();
            if( pFP == NULL){
                break;  // �����͂���Ȃ�
            }
            pFP = _addFossil(xpos2,zpos2);
            pFP->savedataPos = UnderGroundAddFossilGroundItem(pUGData, xpos2, zpos2);
        }
    }

    digNum = MATH_Rand16(pRand, 6);  // 㩂����񖄂߂鐔

    for(i = 0; i < digNum; i++){
        for(try = 0 ; try < 100; try++){
            xpos2 = MATH_Rand16(pRand, 20) + xpos - 10;
            zpos2 = MATH_Rand16(pRand, 20) + zpos - 10;
            if(!GetHitAttr(_pCommFossilWork->pFSys, xpos2, zpos2)){
                int type = UgTrapAddNatureTrap(xpos2,zpos2,pRand,_pCommFossilWork->setNumT);
                if(UG_TRAPTYPE_NONE != type){
                    _pCommFossilWork->setNumT++;
                    break;
                }
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * ���΂P����z�u����
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgFossilOneSetup(int xbase,int zbase,MATHRandContext16* pRand)
{
    int digNum,i,try,flg;
    u16 xpos2,zpos2;
    FossilPoint* pFP;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(_pCommFossilWork->pFSys->savedata);

    flg = FALSE;
    for(try = 0 ; try < 100; try++){
        xpos2 = MATH_Rand16(pRand, 20) + xbase - 10;
        zpos2 = MATH_Rand16(pRand, 20) + zbase - 10;
        if(_isFillUpPoint(_pCommFossilWork->pFSys, xpos2, zpos2)){
            flg = TRUE;
            break;
        }
    }
    if( flg ){
        pFP = _getFreeFossilPoint();
        if( pFP ){
            pFP = _addFossil(xpos2,zpos2);
            OHNO_SP_PRINT("���������� %d %d \n",xpos2,zpos2);
            pFP->savedataPos = UnderGroundAddFossilGroundItem(pUGData, xpos2, zpos2);
        }
    }
}

//--------------------------------------------------------------
/**
 * �J���Ă��鉻�΍\���̃A�h���X��Ԃ�
 * @param    none
 * @retval   ���΍\���̃A�h���X
 */
//--------------------------------------------------------------

static FossilPoint* _getFreeFossilPoint(void)
{
    int i;

    for(i = 0; i < _FOSSIL_NUM_MAX; i++){
        if((_pCommFossilWork->aFossilPoint[i].xpos == COMM_UG_INVALID_GRID) &&
           (_pCommFossilWork->aFossilPoint[i].zpos == COMM_UG_INVALID_GRID)){
            return &_pCommFossilWork->aFossilPoint[i];
        }
    }
    return NULL;
}


//--------------------------------------------------------------
/**
 * ���XY���߂Ď��[����
 * @param    none
 * @retval   ���΍\���̃A�h���X
 */
//--------------------------------------------------------------

static FossilPoint* _addFossil(int xpos, int zpos)
{
    int ins = -1, i, b = zpos * _UG_BLOCK_MAX * BLOCK_GRID_W + xpos;
    int a;

    for(i = 0; i < _FOSSIL_NUM_MAX; i++){
        if((_pCommFossilWork->aFossilPoint[i].xpos != COMM_UG_INVALID_GRID) &&
           (_pCommFossilWork->aFossilPoint[i].zpos != COMM_UG_INVALID_GRID)){
            a = _pCommFossilWork->aFossilPoint[i].zpos * _UG_BLOCK_MAX * BLOCK_GRID_W + _pCommFossilWork->aFossilPoint[i].xpos;
            if(b < a){
                ins = i;
                break;
            }
        }
        else{
            _pCommFossilWork->aFossilPoint[i].xpos = xpos;
            _pCommFossilWork->aFossilPoint[i].zpos = zpos;
            return &_pCommFossilWork->aFossilPoint[i];
        }
    }
    if(ins != -1){
        for(i = _FOSSIL_NUM_MAX - 2; i >= ins;i--){
            _pCommFossilWork->aFossilPoint[i+1].xpos = _pCommFossilWork->aFossilPoint[i].xpos;
            _pCommFossilWork->aFossilPoint[i+1].zpos = _pCommFossilWork->aFossilPoint[i].zpos;
            _pCommFossilWork->aFossilPoint[i+1].savedataPos = _pCommFossilWork->aFossilPoint[i].savedataPos;
        }
        _pCommFossilWork->aFossilPoint[ins].xpos = xpos;
        _pCommFossilWork->aFossilPoint[ins].zpos = zpos;
    }
    return &_pCommFossilWork->aFossilPoint[ins];
}

#ifdef PM_DEBUG
extern void DebugUGDigFossilAddFossil(void);
void DebugUGDigFossilAddFossil(void)
{
    if(_pCommFossilWork){
        _addFossil( Player_NowGPosXGet(_pCommFossilWork->pFSys->player), Player_NowGPosZGet(_pCommFossilWork->pFSys->player)+1);
    }
}
#endif


//==============================================================================
/**
 *  �Z�[�u�f�[�^��p���Ė��߂Ȃ���
 * @param   none
 * @retval  none
 */
//==============================================================================


static void _reload(void)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(_pCommFossilWork->pFSys->savedata);
    int i;
    int xpos,zpos;
    FossilPoint* pFP;

    for(i = 0; i < UG_FOSSIL_PLACE_NUM_MAX; i++){
        xpos =UnderGroundGetFossilGroundItemX(pUGData, i);
        zpos =UnderGroundGetFossilGroundItemZ(pUGData, i);
        if((xpos != 0) && (zpos != 0)){
            pFP = _addFossil(xpos,zpos);
            pFP->savedataPos = i;
        }
    }
}


//==============================================================================
/**
 *  ���t���[���s����������
 * @param   none
 * @retval  none
 */
//==============================================================================

void UgFossilProcess(void)
{
    int i;

    if(CommGetCurrentID() == COMM_PARENT_ID){
        _turnAroundSignalSend();// �e�@�Ȃ�256�����Ńf�[�^�]��
        _pcRadarFunc(); // �p�\�R������₢���킹�̂��������Α��M
    }
}

//--------------------------------------------------------------
/**
 * ���̏ꏊ�ɂ��鉻�΍\���̃A�h���X��Ԃ�
 * @param    none
 * @retval   ���΍\���̃A�h���X
 */
//--------------------------------------------------------------

static FossilPoint* _searchFossilPoint(u16 xpos, u16 zpos)
{
    int i;

    for(i = 0; i < _FOSSIL_NUM_MAX; i++){
        if((_pCommFossilWork->aFossilPoint[i].xpos == xpos) &&
           (_pCommFossilWork->aFossilPoint[i].zpos == zpos)){
            OHNO_PRINT("���Δ��� %d %d %d\n",xpos, zpos, _pCommFossilWork->aFossilPoint[i].savedataPos);
            return &_pCommFossilWork->aFossilPoint[i];
        }
    }
    return NULL;
}



//--------------------------------------------------------------
/**
 * �P�U�O���P�U�O�͈̔͂ŉ��΂�T���o�� ���������烉���_���ŕԂ�
 * @param    xpos,zpos  �ʒu
 * @param    
 * @retval   ����������aFossilPoint��index
 */
//--------------------------------------------------------------

static int _searchFossilRadarPoint(u16 xpos, u16 zpos)
{
    int i, zMin = zpos - 80, zMax = zpos + 80, xMin = xpos - 80, xMax = xpos + 80;
    int num = 0,hit;
    //MATHRandContext32 sRand;

    if(UgSecretBaseIsSecretBasePlace( xpos, zpos)){
        return -1;
    }
    if(xMin < 64){
        xMin = 64;
    }
    if(xMax > 512){
        xMax = 512;
    }
    if(zMin < 32){
        zMin = 32;
    }
    if(zMax > 480){
        zMax = 480;
    }
    for(i = 0; i < _FOSSIL_NUM_MAX; i++){
        if((_pCommFossilWork->aFossilPoint[i].zpos < zMin) || (_pCommFossilWork->aFossilPoint[i].zpos > zMax)){
            continue;
        }
        if((_pCommFossilWork->aFossilPoint[i].xpos > xMin) && (_pCommFossilWork->aFossilPoint[i].xpos < xMax)){
            num++;
        }
    }
    if(num == 0){
        return -1;
    }
    hit = gf_rand() % num;
    num = 0;
    for(i = 0; i < _FOSSIL_NUM_MAX; i++){
        if((_pCommFossilWork->aFossilPoint[i].zpos < zMin) || (_pCommFossilWork->aFossilPoint[i].zpos > zMax)){
            continue;
        }
        if((_pCommFossilWork->aFossilPoint[i].xpos > xMin) && (_pCommFossilWork->aFossilPoint[i].xpos < xMax)){
            if(num == hit){
                return i;
            }
            num++;
        }
    }
    
    return -1;
}

//==============================================================================
/**
 * ���Δ������N���C�A���g�ɕ\���{�@�邩�ǂ����₢���킹��^�X�N������
 * @param   netID    ���M���Ă���ID
 * @retval  none
 */
//==============================================================================

static void _forceDeleteFossilFind(TCB_PTR tcb,void* work)
{
    if(_pCommFossilWork->pYesNoWork){
        BmpYesNoWinDel(_pCommFossilWork->pYesNoWork,HEAPID_FIELD);
    }
    _pCommFossilWork->pYesNoWork = NULL;
    _pCommFossilWork->pDigStart = NULL;
    TCB_Delete(tcb);
}

//==============================================================================
/**
 * ���Δ������N���C�A���g�ɕ\���{�@�邩�ǂ����₢���킹�� CF_FIND_FOSSIL
 * @param   netID    ���M���Ă���ID
 * @retval  none
 */
//==============================================================================

void CommFossilRecvFind(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    
    if(pBuff[0] == CommGetCurrentID()  && CommIsSendMoveData()){
        _pCommFossilWork->winIndex =
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                   msg_underworld_20, FALSE, NULL);
        _pCommFossilWork->pDigStart = TCB_Add(_yesnoMenuFunc, _pCommFossilWork, 0);
        // �t�B�[���h�̓������~�߂�

        UgMgrSetNowTCB(NULL,_pCommFossilWork->pDigStart,_forceDeleteFossilFind);

        CommPlayerHold();
    }
}

//==============================================================================
/**
 * �@�邩�ǂ����₢���킹
 * @param   tcb  �^�X�N�|�C���^
 * @param   work  ���[�N�|�C���^
 * @retval  none
 */
//==============================================================================

static void _yesnoMenuFunc(TCB_PTR tcb, void* work)
{
    u8 flg;
    
    if(_pCommFossilWork->winIndex != -1){
        if( GF_MSG_PrintEndCheck( _pCommFossilWork->winIndex ) == 0 ){
            // �͂��������E�C���h�E���o��
            _pCommFossilWork->pYesNoWork =
                BmpYesNoSelectInit( _pCommFossilWork->pFSys->bgl,
                                    &_yesNoBmpDat,
                                    MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                    HEAPID_FIELD );
            _pCommFossilWork->winIndex = -1;
        }
    }
    else{
        int ret = BmpYesNoSelectMain(_pCommFossilWork->pYesNoWork, HEAPID_FIELD);
        if(ret == BMPMENU_NULL){  // �܂��I��
            return;
        }else if(ret == 0){ // �͂���I�������ꍇ
            flg = TRUE;  // �T�[�o�[�Ɋm�F�����
        }
        else{  // ��������I�������ꍇ
            flg = FALSE;
            CommPlayerHoldEnd();  // �����ŏI��
        }
        CommSendFixSizeData(CF_DIG_FOSSIL_START_REQ,&flg);  // �T�[�o�[�Ɋm�F�����
        _pCommFossilWork->pYesNoWork = NULL;
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        TCB_Delete(tcb);
        UgMgrEndNowTCB();
        _pCommFossilWork->pDigStart = NULL;
    }
}

//==============================================================================
/**
 * ���Δ������N���C�A���g�ɕ\���{�@�邩�ǂ����₢���킹�� CF_DIG_FOSSIL_START_REQ
 * @param   netID    ���M���Ă���ID
 * @retval  none
 */
//==============================================================================

void CommFossilRecvDigStartReq(int netID, int size, void* pData, void* pWork)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(_pCommFossilWork->pFSys->savedata);
    FossilPoint* pFP =_pCommFossilWork->pEntryFossil[netID];
    u8 id = netID;
    u8* pBuff = pData;

    if((pBuff[0] != 0) && pFP){
        if(pFP->digCreatureNetID == INVALID_NETID){
            CommSendData_ServerSide(CF_DIG_FOSSIL_START, &id, 1);
            pFP->digCreatureNetID = INVALID_NETID;
            pFP->xpos = COMM_UG_INVALID_GRID;
            pFP->zpos = COMM_UG_INVALID_GRID;
            UnderGroundDelFossilGroundItem(pUGData, pFP->savedataPos);
            _pCommFossilWork->bEntryFossil[netID] = TRUE;
            _pCommFossilWork->pEntryFossil[netID] = NULL;
        }
    }
    else{
        _pCommFossilWork->bEntryFossil[netID] = FALSE;
        _pCommFossilWork->pEntryFossil[netID] = NULL;
    }
}

//==============================================================================
/**
 * ���Δ��@�J�n
 * @param   netID    ���M���Ă���ID
 * @retval  none
 */
//==============================================================================

void CommFossilRecvDigStart(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    
    if(pBuff[0] == CommGetCurrentID()){
        OHNO_PRINT("���΃X�^�[�g\n");
        CommPlayerHold();
        _digFossilEventStart(_pCommFossilWork->pFSys);
    }
    _pCommFossilWork->logMsgFossil[pBuff[0]] = TRUE;  // �@��o����
}

//==============================================================================
/**
 * ���Δ��@�I�����q���瑗���Ă���
 * @param   netID    ���M���Ă���ID
 * @retval  none
 */
//==============================================================================

void CommFossilRecvDigEndReq(int netID, int size, void* pData, void* pWork)
{
    _pCommFossilWork->bEntryFossil[netID]=FALSE;
}

//==============================================================================
/**
 * ���Δ��@���̈ʒu�������Ă���
 * @param   netID    ���M���Ă���ID
 * @retval  none
 */
//==============================================================================

void CommFossilRecvDigPos(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    u8 returnBuff[3];
    int i;

    returnBuff[0] = netID;
    returnBuff[1] = pBuff[0];
    returnBuff[2] = pBuff[1];
    OHNO_PRINT("CommFossilRecvDigPos \n");
    CommSendFixSizeData_ServerSide(CF_DIG_FOSSIL_POS_RETURN, returnBuff);
}

//==============================================================================
/**
 * ���Δ��@���̈ʒu�𑗂�R�}���h�̃T�C�Y
 * @param   none
 * @retval  �p�P�b�g�T�C�Y
 */
//==============================================================================

int CommFossilGetDigPosSize(void)
{
    return 2;
}

//==============================================================================
/**
 * ���Δ��@���̈ʒu���q�@�ɑ����Ă���  CF_DIG_FOSSIL_POS_RETURN
 * @param   netID    ���M���Ă���ID
 * @retval  none
 */
//==============================================================================

void CommFossilRecvDigPosReturn(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    u8 returnBuff[3];
    int i;

    if(pBuff[0] == CommGetCurrentID()){
        return;  // �������g
    }

    _pCommFossilWork->friendDigPointX[pBuff[0]] = pBuff[1];
    _pCommFossilWork->friendDigPointZ[pBuff[0]] = pBuff[2];
}

//==============================================================================
/**
 * ���Δ��@���̈ʒu��e�@���瑗��ꍇ�̃R�}���h�̃T�C�Y
 * @param   none
 * @retval  �p�P�b�g�T�C�Y
 */
//==============================================================================

int CommFossilGetDigPosReturnSize(void)
{
    return 3;
}

//--------------------------------------------------------------------------------------------
/**
 * BG�ݒ�
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void _fossilBgSet( GF_BGL_INI * ini )
{
    //VRAM�ݒ�
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
			GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
			GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
			GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
			GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
			GX_VRAM_TEX_01_BC,				// �e�N�X�`���C���[�W�X���b�g
			GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
		};
		GF_Disp_SetBank( &vramSetTable );
	}
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

    {	// BASE
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xc000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, FLD_MBGFRM_MAP, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_MAP, 32, 0, HEAPID_DIGFOSSIL);
		GF_BGL_ScrClear( ini, FLD_MBGFRM_MAP );
	}

	{	// PARTS
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, FLD_MBGFRM_EFFECT1, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_EFFECT1, 32, 0, HEAPID_DIGFOSSIL);
		GF_BGL_ScrClear( ini, FLD_MBGFRM_EFFECT1 );
	}
	{	// GROUND
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_23,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, FLD_MBGFRM_EFFECT2, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_EFFECT2, 32, 0, HEAPID_DIGFOSSIL);
		GF_BGL_ScrClear( ini, FLD_MBGFRM_EFFECT2 );
	}
	{	// MAIN DISP�i���b�Z�[�W�j
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_23,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, FLD_MBGFRM_FONT, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_FONT, 32, 0, HEAPID_DIGFOSSIL);
		GF_BGL_ScrClear( ini, FLD_MBGFRM_FONT );
	}

    
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_DIGFOSSIL );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_DIGFOSSIL);
}

//--------------------------------------------------------------
/**
 * @brief   �n���}�[anim�J�n
 * @param   none
 * @return  none
 */
//--------------------------------------------------------------
static void _hammerStart(int x,int y, BOOL bPic, BOOL bHard, BOOL bFossil)
{
    void* heap;
	GF_CAMERA_PTR camera_ptr;
	void *resource;
    VecFx32 tmpVex;

    // anim�J�n
    if(bPic){
        CLACT_AnmChg( _pCommFossilWork->clActWork[_CLACT_HUMMER], 0 );
    }
    else{
        CLACT_AnmChg( _pCommFossilWork->clActWork[_CLACT_HUMMER], 1 );
    }
    if(bHard){
        CLACT_AnmChg( _pCommFossilWork->clActWork[_CLACT_HIT], 2 );
        Snd_SePlay(UG_SE_HARD_ROCK);
    }
    else if(bPic){
        CLACT_AnmChg( _pCommFossilWork->clActWork[_CLACT_HIT], 3 );
        Snd_SePlay(UG_SE_PICK);
    }
    else{
        CLACT_AnmChg( _pCommFossilWork->clActWork[_CLACT_HIT], 4 );
        Snd_SePlay(UG_SE_HUMMER);
    }
    CLACT_SetAnmFlag(_pCommFossilWork->clActWork[_CLACT_HUMMER], 1 );
    CLACT_SetAnmFlag(_pCommFossilWork->clActWork[_CLACT_HIT], 1 );
    tmpVex.x = FX32_ONE * (x + 8);
    tmpVex.y = FX32_ONE * (y + 8);
    CLACT_SetMatrix(_pCommFossilWork->clActWork[_CLACT_HUMMER], &tmpVex);
    CLACT_SetMatrix(_pCommFossilWork->clActWork[_CLACT_HIT], &tmpVex);

    if(bFossil){
        CLACT_AnmChg( _pCommFossilWork->clActWork[_CLACT_KIRA_SINGLE], 5 );
        CLACT_SetAnmFlag(_pCommFossilWork->clActWork[_CLACT_KIRA_SINGLE], 1 );
        CLACT_SetMatrix(_pCommFossilWork->clActWork[_CLACT_KIRA_SINGLE], &tmpVex);
    }


}

//--------------------------------------------------------------
/**
 * ���Ό@��t���[���̏�����
 * @param    GF_BGL_INI bgl�ԍ�
 * @retval   none
 */
//--------------------------------------------------------------

static void _commFossilGameInitialize1(FossilEventTask* pFET)
{
    int charByte;
    GF_BGL_INI* bgl;
    void* heap;
	GF_CAMERA_PTR camera_ptr;
	void *resource;
    int i;

    Snd_DataSetByScene(SND_SCENE_SUB_DIG,0,0);
    _initializeDigGame(); 

    GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
    GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
    GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
    GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );

    sys_CreateHeap( HEAPID_BASE_APP, HEAPID_DIGFOSSIL, 0x50000 );

//    simple_3DBGInit(HEAPID_DIGFOSSIL);
    
	bgl = GF_BGL_BglIniAlloc( HEAPID_DIGFOSSIL );
    _pCommFossilWork->bgl = bgl;
 	//V�u�����N�֐��Z�b�g
	sys_VBlankFuncChange(vBlankFunc, bgl);

    CommMsgSetBgl(CommUnderGetMsgUnderWorld(),bgl);
    _fossilBgSet(bgl);

    GF_BGL_ScrClear( bgl, GF_BGL_FRAME0_M );
    GF_BGL_ScrClear( bgl, GF_BGL_FRAME1_M);
    GF_BGL_ScrClear( bgl, GF_BGL_FRAME2_M );

    TalkWinGraphicSet(
        bgl, GF_BGL_FRAME3_M, COMM_TALK_WIN_CGX_NUM,
        COMM_MESFRAME_PAL, WINTYPE_01, HEAPID_DIGFOSSIL );

    // ���n 32+108+1
    ArcUtil_PalSet( ARC_UG_FOSSIL_GRA, NARC_ug_fossil_kaseki_board_NCLR,
                    PALTYPE_MAIN_BG, 0, 32*3,  HEAPID_DIGFOSSIL);
    charByte = ArcUtil_BgCharSet( ARC_UG_FOSSIL_GRA, NARC_ug_fossil_kaseki_board_NCGR,
                                  bgl, GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_DIGFOSSIL);
    ArcUtil_ScrnSet( ARC_UG_FOSSIL_GRA, NARC_ug_fossil_kaseki_board_NSCR,
                     bgl, GF_BGL_FRAME0_M, 0,
                     0,
                     0, HEAPID_DIGFOSSIL);
    ArcUtil_PalSet(ARC_UG_TRAP_GRA, NARC_ug_trap_ug_menu_NCLR, PALTYPE_MAIN_BG, FLD_MESFRAME_PAL*0x20, 4*0x20,  HEAPID_DIGFOSSIL);

    _randomDeposit(bgl,charByte,pFET);  // �z�u���𗐐��Ō��߂�
}

//--------------------------------------------------------------
/**
 * ���Ό@��t���[���̏�����
 * @param    GF_BGL_INI bgl�ԍ�
 * @retval   none
 */
//--------------------------------------------------------------

static void _commFossilGameInitialize2(void)
{
    int charByte;
    GF_BGL_INI* bgl;
    void* heap;
	GF_CAMERA_PTR camera_ptr;
	void *resource;
    int i;

    _touchButtonInitialize(_pCommFossilWork->bgl);
    GF_BGL_LoadScreenReq(_pCommFossilWork->bgl, GF_BGL_FRAME1_M);

    _randomBuildup(_pCommFossilWork->bgl);  // �͐ϕ��𗐐��Ō��߂�

//    ArcUtil_PalSet( ARC_UG_PARTS_GRA, NARC_ug_parts_kaseki_board_NCLR,
//                    PALTYPE_MAIN_BG, 14*32, 32,  HEAPID_DIGFOSSIL);
    ArcUtil_BgCharSet( ARC_UG_PARTS_GRA, NARC_ug_parts_kaseki_board_wall_NCGR,
                       _pCommFossilWork->bgl, GF_BGL_FRAME2_M, 1, 0, 0, HEAPID_DIGFOSSIL);
    _buildupBGDraw(_pCommFossilWork->bgl);

    GF_BGL_PrioritySet(GF_BGL_FRAME0_M , 3);  //�͂�����
    GF_BGL_PrioritySet(GF_BGL_FRAME1_M , 2);   // ���� �ڂ���
    GF_BGL_PrioritySet(GF_BGL_FRAME2_M , 1);   // ��
    GF_BGL_PrioritySet(GF_BGL_FRAME3_M , 0);  // ���b�Z�[�W

    _initCellActor();
    _setCellActor();
    _gaugeDisp(_pCommFossilWork->bgl);//�Q�[�W�ŏ��\��

}

//--------------------------------------------------------------
/**
 * ���Ό@��t���[���̊J��
 * @param    GF_BGL_INI bgl�ԍ�
 * @retval   none
 */
//--------------------------------------------------------------

static void _commFossilGameFinalize(FossilEventTask* pFET)
{
    void* heap;
    int i;

    GF_BGL_BGControlExit( _pCommFossilWork->bgl, GF_BGL_FRAME0_M );
    GF_BGL_BGControlExit( _pCommFossilWork->bgl, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( _pCommFossilWork->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( _pCommFossilWork->bgl, GF_BGL_FRAME3_M );
	// �Z���A�N�^�[���\�[�X���

	// �L�����]���}�l�[�W���[�j��
	CLACT_U_CharManagerDelete(_pCommFossilWork->resObjTbl[0]);
	CLACT_U_CharManagerDelete(_pCommFossilWork->resObjTbl[4]);
	// �p���b�g�]���}�l�[�W���[�j��
	CLACT_U_PlttManagerDelete(_pCommFossilWork->resObjTbl[1]);
	CLACT_U_PlttManagerDelete(_pCommFossilWork->resObjTbl[5]);
		
	// �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j�� �}���`�͖���
	for(i=0;i < 4;i++){
		CLACT_U_ResManagerDelete(_pCommFossilWork->resMan[i]);
	}

    for(i = 0;i < _PARTS_TREASURE_NUM_MAX;i++){
        if(pFET->pPalBuff[i]!=NULL){
            sys_FreeMemoryEz(pFET->pPalBuff[i]);
            pFET->pPalBuff[i]=NULL;
        }
    }
	// �Z���A�N�^�[�Z�b�g�j��
	CLACT_DestSet(_pCommFossilWork->clactSet);
	//OAM�����_���[�j��
	REND_OAM_Delete();

    DeleteCharManager();
	DeletePlttManager();

    sys_VBlankFuncChange(NULL, NULL);
    
    sys_FreeMemoryEz( _pCommFossilWork->bgl );
    _pCommFossilWork->bgl = NULL;
    sys_DeleteHeap(HEAPID_DIGFOSSIL);
    CommMsgSetBgl(CommUnderGetMsgUnderWorld(),_pCommFossilWork->pFSys->bgl);
}

//--------------------------------------------------------------
/**
 * ���Ό@��C�x���g���� SEQ
 * @param    GMEVENT_CONTROL * event �C�x���g�R���g���[��
 * @retval   �������I����TRUE
 */
//--------------------------------------------------------------

typedef enum{
    _SEQ_START,
    _SEQ_START_WAIT,
    _SEQ_RADAR_FADEOUT,
    _SEQ_FIELD_FADEOUT,
    _SEQ_GAME_INIT1,
    _SEQ_GAME_INIT2,
    _SEQ_GAME_FADE_IN,
    _SEQ_GAME_FADE_IN_WAIT,
    _SEQ_RADAR,
    _SEQ_MESSAGE,
    _SEQ_MESSAGE_WAIT,
    _SEQ_MESSAGE_FIRST,
    _SEQ_MESSAGE_FIRST_WAIT,
    _SEQ_GAME,
    _SEQ_SUCCESS_WAIT,
    _SEQ_KEY_WAIT,
    _SEQ_RESULT_MSG,
    _SEQ_KEY_WAIT2,
    _SEQ_FAINALIZE,
    _SEQ_UG_REBOOT,
    _SEQ_UG_REBOOT_WAIT,
    _SEQ_END,
    _SEQ_QUAKE,
    _SEQ_WIPE,
    _SEQ_WIPE_CHANGE,
    _SEQ_WIPE_CHANGE2,
    _SEQ_WIPE_MES,
    _SEQ_KEY_WAIT_FAILED,    
};

static void GMEVENT_DigFossil(TCB_PTR tcb, void *work)
{
    FossilEventTask* pFET = work;
    FIELDSYS_WORK * fsys = pFET->pFSys;

    switch (pFET->seq) {
      case _SEQ_START:
        UgSecretBaseBootOn(FALSE);
        CommDigStoneManagerReset();
        CommPlayerManagerReset();
        CommSecretBaseInfoReset();
    //        if( CommStateJumpUnderGround() ){
            //CommStateUnderGroundDigFossilStart();
            (pFET->seq) ++;
//        }
		break;
      case _SEQ_START_WAIT:
        UnderGround_RadarEnd(fsys->UnderGroundRadar);
        WIPE_SYS_Start(WIPE_PATTERN_FSAM,
                       WIPE_TYPE_HOLEOUT,WIPE_TYPE_TUNNELOUT,
                       WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                       1,HEAPID_FIELD);
		(pFET->seq) ++;
        break;
      case _SEQ_RADAR_FADEOUT:
        if(WIPE_SYS_EndCheck()){
            if (fsys->UnderGroundRadar == NULL){
                GameSystem_FinishFieldProc(fsys);
                (pFET->seq) ++;
            }
        }
        break;
      case _SEQ_FIELD_FADEOUT:
        if(!GameSystem_CheckFieldProcExists(fsys)){		// �v���b�NChange
            WirelessIconEasyEnd();
            (pFET->seq) ++;
        }
		break;
      case _SEQ_GAME_INIT1:    // ���������d�����̂ŕ�����ɕ���
        _commFossilGameInitialize1(pFET);
        (pFET->seq) ++;
        break;
      case _SEQ_GAME_INIT2:
        _commFossilGameInitialize2();
        (pFET->seq) ++;
        break;
      case _SEQ_GAME_FADE_IN:
        WirelessIconEasy();
        WIPE_SYS_Start(WIPE_PATTERN_M,
                   WIPE_TYPE_HOLEIN,
                   WIPE_TYPE_HOLEIN, WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                   1,HEAPID_DIGFOSSIL);
        GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
        GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
        GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
        GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
        (pFET->seq) ++;
        break;
      case _SEQ_GAME_FADE_IN_WAIT:
        if( WIPE_SYS_EndCheck() ){
            pFET->timer = 0;
            Snd_SePlay(UG_SE_RADAR_ECHO);
            pFET->seq = _SEQ_RADAR;
        }
        break;
      case _SEQ_RADAR:
        pFET->timer++;
        if(pFET->timer  > 20){
            pFET->seq = _SEQ_MESSAGE;
        }
        break;
      case _SEQ_MESSAGE:
        CommMsgRegisterNumber1Index(CommUnderGetMsgUnderWorld(), 0, pFET->_PARTS_TREASURE_NUM);
        _pCommFossilWork->winIndex =
            CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderWorld(),
                                      msg_underworld_62, FALSE, NULL);
        pFET->timer = 0;
        (pFET->seq) ++;
        break;
      case _SEQ_MESSAGE_WAIT:
        pFET->timer++;
        if(pFET->timer  > 80){
            UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommFossilWork->pFSys));
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            if(UnderGroundIsFirstFossil(pUGData)){
                pFET->seq++;
            }
            else{
                pFET->seq=_SEQ_GAME;
            }
        }
        break;
      case _SEQ_MESSAGE_FIRST:
        _pCommFossilWork->winIndex =
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                   msg_underworld_85, FALSE, NULL);
        pFET->timer = 0;
        (pFET->seq) ++;
        break;
      case _SEQ_MESSAGE_FIRST_WAIT:
        if( GF_MSG_PrintEndCheck( _pCommFossilWork->winIndex ) == 0 ){
            if( sys.tp_trg || (sys.trg & PAD_BUTTON_DECIDE) ) {
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
                pFET->seq++;
            }
        }
        break;
      case _SEQ_GAME:
#ifdef PM_DEBUG
        if(sys.cont & PAD_BUTTON_B){
            GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
        }
        else{
            GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
        }
#endif
        _gameProcess(pFET);
        _shakeProcess(_pCommFossilWork->bgl);
        _partsDigColor(pFET);
        CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
        break;
      case _SEQ_SUCCESS_WAIT: // ���΃Q�[���I���҂�
        _partsDigColor(pFET);
        CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
        pFET->timer--;
        if(pFET->timer==0){
            _pCommFossilWork->winIndex =
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_64,FALSE,NULL);
            Snd_SePlay(UG_SE_FOSSIL_CLEAR);
            pFET->seq = _SEQ_KEY_WAIT;
        }
        break;
      case _SEQ_KEY_WAIT:
        CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
        // A�L�[orTouch�҂�
//        if(Snd_MePlayCheckBgmPlay() == 0){
        if( GF_MSG_PrintEndCheck( _pCommFossilWork->winIndex ) == 0 ){
            if( sys.tp_trg || (sys.trg & PAD_BUTTON_DECIDE) ) {
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
                pFET->seq = _SEQ_RESULT_MSG;
            }
        }
        //        }
        break;
      case _SEQ_RESULT_MSG:
        CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
        if(_fossilGetMessage(pFET)){
            pFET->seq = _SEQ_KEY_WAIT2;
        }
        else{
            pFET->seq = _SEQ_FAINALIZE;
        }
        break;
      case _SEQ_KEY_WAIT2:
        CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
        // A�L�[orTouch�҂�
        if( GF_MSG_PrintEndCheck( _pCommFossilWork->winIndex ) == 0 ){
            if( sys.tp_trg || (sys.trg & PAD_BUTTON_DECIDE) ) {
                if(_fossilGetMessageBagIn(pFET)){
                    pFET->seq = _SEQ_KEY_WAIT;
                }
                else{
                    pFET->seq = _SEQ_RESULT_MSG;
                }
            }
        }
        break;
      case _SEQ_FAINALIZE:
        CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        WIPE_SYS_Start(WIPE_PATTERN_M,
                   WIPE_TYPE_HOLEOUT,
                   WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                   1,HEAPID_DIGFOSSIL);
        
        (pFET->seq) ++;
        break;
      case _SEQ_UG_REBOOT:
        CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
        if(WIPE_SYS_EndCheck()){         //�t�B�[���h�}�b�v�v���Z�X���A
            WirelessIconEasyEnd();
            _commFossilGameFinalize(pFET);
            FieldEvent_Cmd_SetMapProc( fsys );
            (pFET->seq) ++;
        }
        break;
      case _SEQ_UG_REBOOT_WAIT:
        //�t�B�[���h�}�b�v�v���Z�X�J�n�҂�
        OHNO_PRINT("�t�B�[���h�}�b�v�v���Z�X�J�n�҂�\n");
        if (FieldEvent_Cmd_WaitMapProcStart(fsys)) {
            fsys->UnderGroundRadar = UnderGround_RadarInit(fsys);		//�Y�z���[�_�[��ʂn�m
            WirelessIconEasy();
            CommPlayerHold();
            FLDHBLANK_SYS_Stop(pFET->pFSys->fldmap->hblanksys);
            WIPE_SYS_Start(WIPE_PATTERN_FMAS,
                           WIPE_TYPE_HOLEIN, WIPE_TYPE_TUNNELIN,
                           WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                           1,HEAPID_FIELD);
            (pFET->seq) ++;
			break;
		}
		break;
      case _SEQ_END:
        WIPE_ResetBrightness(WIPE_DISP_MAIN);
        if(WIPE_SYS_EndCheck()){         //�t�B�[���h�}�b�v�v���Z�X���A
            FLDHBLANK_SYS_Stop(pFET->pFSys->fldmap->hblanksys);
            FLDHBLANK_SYS_Start(pFET->pFSys->fldmap->hblanksys);
            // �Â��t�H���g�p���b�g�]��
            ArcUtil_PalSet(ARC_UG_TRAP_GRA, NARC_ug_trap_ug_menu_NCLR, PALTYPE_MAIN_BG, FLD_MESFRAME_PAL*0x20, 4*0x20,  HEAPID_FIELD);
            MenuWinGraphicSet(
                pFET->pFSys->bgl, GF_BGL_FRAME3_M, MENU_WIN_CGX_NUM,
                MENU_WIN_PAL, MENU_TYPE_UG, HEAPID_FIELD );
            
            //CommStateJumpEndUnderGround(); // �ړ��I������ꍇ�̒ʐM�֘A����
            CommPlayerManagerReboot();
            CommSecretBaseInfoReboot();
            CommDigStoneManagerReboot();

            CommSendFixSizeData(CF_DIG_FOSSIL_END_REQ,&pFET->bSuccess);  // ���Ζx���I���������e�ɒʒm
            CommPlayerHoldEnd();
            _pCommFossilWork->pDFETCB = NULL;
            sys_FreeMemoryEz(pFET);
            TCB_Delete(tcb);
            UgSecretBaseBootOn(TRUE);

            //CommStateUnderGroundDigFossilEnd();
        }
        break;
      case _SEQ_QUAKE:
        _pCommFossilWork->shakeCount = 1;
        pFET->timer--;
        if(pFET->timer  == 0){
            _pCommFossilWork->shakeCount = 100;
            pFET->seq = _SEQ_WIPE;
        }
        _shakeProcess(_pCommFossilWork->bgl);
        CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
        break;
      case _SEQ_WIPE:
        CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
        WIPE_SYS_Start(WIPE_PATTERN_M,
                   WIPE_TYPE_SHUTTEROUT_DOWN,
                   WIPE_TYPE_SHUTTEROUT_DOWN, WIPE_FADE_BLACK,_FAILED_BRIGHTNESS_SYNC,
                   1,HEAPID_DIGFOSSIL);
        Snd_SePlay(UG_SE_BLOKEN_WALL);
        pFET->seq = _SEQ_WIPE_CHANGE;
        break;
      case _SEQ_WIPE_CHANGE:
        if(WIPE_SYS_EndCheck()){
            int i;
            for(i = 0 ; i < _CLACT_MAX;i++){
                CLACT_SetDrawFlag(_pCommFossilWork->clActWork[ i ] ,0);
            }
            pFET->seq = _SEQ_WIPE_CHANGE2;
        }
        else{
            CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
        }
        break;
      case _SEQ_WIPE_CHANGE2:
        ChangeBrightnessRequest(1,BRIGHTNESS_BLACK,BRIGHTNESS_BLACK,
                                PLANEMASK_BG0|PLANEMASK_BG1|PLANEMASK_BG2,
                                MASK_MAIN_DISPLAY);
        pFET->seq = _SEQ_WIPE_MES;
        break;
      case _SEQ_WIPE_MES:
        WIPE_ResetWndMask(WIPE_DISP_MAIN);
        WIPE_ResetBrightness( WIPE_DISP_MAIN );
        _pCommFossilWork->winIndex =
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                   msg_underworld_63,FALSE,NULL);
        pFET->seq = _SEQ_KEY_WAIT; //_SEQ_KEY_WAIT_FAILED;
        break;
      case _SEQ_KEY_WAIT_FAILED:
        if( GF_MSG_PrintEndCheck( _pCommFossilWork->winIndex ) == 0 ){
            if( sys.tp_trg || (sys.trg & PAD_BUTTON_DECIDE) ) {
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
                pFET->seq = _SEQ_UG_REBOOT;
            }
        }
        break;
	}
//	return FALSE;
}


//--------------------------------------------------------------
/**
 * ���Ό@��C�x���g�J�n
 * @param    GF_BGL_INI bgl�ԍ�
 * @retval   none
 */
//--------------------------------------------------------------

static void _digFossilEventStart(FIELDSYS_WORK* pFSys)
{
    FossilEventTask* pFET;
    void* pBuf = FNOTE_ActionUGFossilDataMake(HEAPID_WORLD);

    FNOTE_DataSave(pFSys->fnote, pBuf, FNOTE_TYPE_ACTION);
    pFET = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(FossilEventTask));
    MI_CpuFill8(pFET, 0, sizeof(FossilEventTask));
    pFET->pFSys = pFSys;

    FLDHBLANK_SYS_Stop(pFSys->fldmap->hblanksys);
    
    SysFlag_UgDigSet(SaveData_GetEventWork(pFSys->savedata));
    _pCommFossilWork->pDFETCB = TCB_Add(GMEVENT_DigFossil, pFET,100);
}

static BOOL _isFreeDiposit(void)
{
    int i;

    for(i = 0; i < _PARTS_NUM_MAX; i++){
        if(_pCommFossilWork->aDeposit[i].pParts == NULL){
            return TRUE;
        }
    }
    return FALSE;
}


//--------------------------------------------------------------
/**
 * �󂫍\���̂ɖ��߂�p�[�c�f�[�^������
 * @param    parts   �p�[�c
 * @param    x  ���ׂ�ʒu
 * @param    y  
 * @retval   �����肪����ꍇTRUE  �����ꍇFALSE
 */
//--------------------------------------------------------------

static int _setDiposit(int partsIndex, int x, int y)
{
    int i;

    for(i = 0; i < _PARTS_NUM_MAX; i++){
        if(_pCommFossilWork->aDeposit[i].pParts == NULL){
            _pCommFossilWork->aDeposit[i].pParts = &_partsData[partsIndex];
            _pCommFossilWork->aDeposit[i].partsType = _partsData[partsIndex].partsType;
            _pCommFossilWork->aDeposit[i].x = x;
            _pCommFossilWork->aDeposit[i].y = y;
            _pCommFossilWork->aDeposit[i].bGetItem = FALSE;
            return i+1;
        }
    }
    GF_ASSERT(0 && "�󂫊m�F���ĂȂ�");
    return 0;
}

//--------------------------------------------------------------
/**
 * �����肪���邩�ǂ�����������
 * @param    parts   �p�[�c
 * @param    x  ���ׂ�ʒu
 * @param    y  
 * @retval   �����肪����ꍇTRUE  �����ꍇFALSE
 */
//--------------------------------------------------------------
static BOOL _isAttribute(FossilParts* pParts, int x, int y)
{
    u8* attr = pParts->attribute;
    int xpos,ypos,width;

    if(attr==NULL){
        return TRUE;  // �S�ʂ�����̂�
    }
    ypos = y / 2;
    xpos = x / 2;
    width = pParts->width / 2;
    if(attr[ ypos * width + xpos] == 'o'){
        return FALSE;
    }
    return TRUE;
}

/**
 * �p�[�c�𖄂߂�i�d�����ǂ����֌W�Ȃ��j
 * @param    partsIndex   ���߂�p�[�c�e�[�u���h�m�c�d�w
 * @param    x  ����X
 * @param    y  ����Y
 * @param    dir �㉺���E ->  ��]  
 * @retval   none
 */

static BOOL _partsDeposit(int partsIndex, int x, int y)
{
    int i, j, xParts, yParts, idx;

    if(!_isFreeDiposit()){
        return FALSE;
    }

    xParts = _partsData[partsIndex].width / 2 + x;
    yParts = _partsData[partsIndex].height / 2 + y;


    if(xParts > _DIGMAP_WIDTH){  // �݂͂����Ă܂�
        return FALSE;
    }
    if(yParts > _DIGMAP_HEIGHT){  // �݂͂����Ă܂�
        return FALSE;
    }

    
    for(i = x; i < xParts; i++){
        for(j = y; j < yParts; j++){
            if(_isAttribute(&_partsData[partsIndex], (i - x) * 2, (j - y) * 2) ){
                if(_pCommFossilWork->depositMap[j][i]!=0){
                    return FALSE;
                }
            }
        }
    }
    idx = _setDiposit(partsIndex, x, y);
    for(i = x; i < xParts; i++){
        for(j = y; j < yParts; j++){
            // �z�u�l�`�o�쐬
            if(_isAttribute(&_partsData[partsIndex], (i - x) * 2, (j - y) * 2) ){
                _pCommFossilWork->depositMap[j][i] = idx;
            }
        }
    }
    
    return TRUE;
}


/**
 * �����ɍ��킹���������������
 * @retval   �������
 */


static int _fossilRandGet(FossilParts* pParts)
{
    SAVEDATA* pSave = GameSystem_GetSaveData(_pCommFossilWork->pFSys);
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);
    BOOL bEvent = UnderGroundIsDiamondPearlEvent(pUGData);
    BOOL bZenkoku = ZukanWork_GetZenkokuZukanFlag(SaveData_GetZukanWork(pSave));
    int treasureRand = 0;

    if(bZenkoku){
#if ( PM_VERSION == VERSION_DIAMOND )
        treasureRand += pParts->random2;
#else
        treasureRand += pParts->random3;
#endif
    }
    else{
#if ( PM_VERSION == VERSION_DIAMOND )
        treasureRand += pParts->random;
#else
        treasureRand += pParts->random1;
#endif
    }
    if(bEvent){
#if ( PM_VERSION == VERSION_DIAMOND )
        if(pParts->partsType == DIG_PARTS_KONGOU_L){
            treasureRand += 33;
        }
        if(pParts->partsType == DIG_PARTS_KONGOU_S){
            treasureRand += 66;
        }
#else
        if(pParts->partsType == DIG_PARTS_SIRATAMA_L){
            treasureRand += 33;
        }
        if(pParts->partsType == DIG_PARTS_SIRATAMA_S){
            treasureRand += 66;
        }
#endif
    }
    return treasureRand;
}


//--------------------------------------------------------------
/**
 * �󕨂̏o���������v�l
 * @param    none
 * @retval   �󕨂̏o���������v�l
 */
//--------------------------------------------------------------

static int _getTreasurePartsRandomMax(void)
{
    int i, treasureRand=0;

    for(i = 0; i < NELEMS(_partsData) ; i++){
        if(DIG_PARTS_NODIG1 == _partsData[i].partsType){
            break;
        }
        treasureRand += _fossilRandGet(&_partsData[i]);
    }
    return treasureRand;
}

//--------------------------------------------------------------
/**
 * �󕨂̗����ɂ��I�o
 * @param    none
 * @retval   ��no
 */
//--------------------------------------------------------------

static int _getTreasurePartsRandom(int random)
{
    int i, treasureRand = random;

    for(i = 0; i < NELEMS(_partsData) ; i++){
        if(DIG_PARTS_NODIG1 == _partsData[i].partsType){
            break;
        }
        treasureRand -= _fossilRandGet(&_partsData[i]);
        if(treasureRand < 0){
            return i;
        }
    }
    GF_ASSERT(0 && "�����ɂ͂��Ȃ��͂� �v�C��");
    return 0;
}

//--------------------------------------------------------------
/**
 * �z�u�f�[�^����ق�Ȃ��p�[�c�̃f�[�^���𓾂�
 * @param    none
 * @retval   �󕨂̏o���������v�l
 */
//--------------------------------------------------------------

static int _getTreasurePartsNoDigNum(void)
{
    int i, j = 0;

    for(i = 0; i < NELEMS(_partsData) ; i++){
        if(_partsData[i].partsType >= DIG_PARTS_NODIG1){
            j++;
        }
    }
    return j;
}


#if _PICTTEST
//--------------------------------------------------------------
/**
 * �ł��邾���p�[�c�𖄂߂�  �G�̊m�F�p�f�o�b�O
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static void _randomDeposit(GF_BGL_INI* bgl, int charByte,FossilEventTask* pFET)
{
//    MATHRandContext32 sRand;
    int i, treasureRand = _getTreasurePartsRandomMax();
    int rand, parts, x, y, limit=0, partsIndex;
    int noDigNum = _getTreasurePartsNoDigNum();
    static int dummy = 0;
    
   // CommRandSeedInitialize(&sRand);

    pFET->_PARTS_TREASURE_NUM = _PARTS_TREASURE_NUM_MAX;
    for(i = dummy; i < dummy+_PARTS_TREASURE_NUM_MAX; ){
//        rand = MATH_Rand32(&sRand, treasureRand);  // ����̉��𖄂߂邩���߂�
        partsIndex = i;
        x = MATH_Rand32(&_pCommFossilWork->sRand, _DIGMAP_WIDTH);
        y = MATH_Rand32(&_pCommFossilWork->sRand, _DIGMAP_HEIGHT);
        if(_partsDeposit(partsIndex, x, y)){
            OHNO_PRINT("parts %d x=%d y=%d %d\n",partsIndex, x, y);
            i++;
        }
    }

    _depositBGInit(_PARTS_TREASURE_NUM_MAX, bgl, charByte, pFET);
    dummy+=_PARTS_TREASURE_NUM_MAX;
#ifdef PM_DEBUG
    OHNO_PRINT("�z�uMAP \n");
    for(y = 0; y < _DIGMAP_HEIGHT; y++){
        for(x = 0; x < _DIGMAP_WIDTH ; x++){
            OHNO_PRINT("%2d ", _pCommFossilWork->depositMap[y][x]);
        }
        OHNO_PRINT(" \n");
    }
#endif
}
#else
//--------------------------------------------------------------
/**
 * �ł��邾���p�[�c�𖄂߂�
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static void _randomDeposit(GF_BGL_INI* bgl, int charByte,FossilEventTask* pFET)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommFossilWork->pFSys));
 //   MATHRandContext32 sRand;
    int i,j, treasureRand = _getTreasurePartsRandomMax();
    int rand, parts, x, y, limit=0, partsIndex, type;
    int noDigNum = _getTreasurePartsNoDigNum();
    int plate[_PARTS_TREASURE_NUM_MAX];
    

    pFET->_PARTS_TREASURE_NUM = MATH_Rand32(&_pCommFossilWork->sRand, (_PARTS_TREASURE_NUM_MAX-1)) + 2;

    if(UnderGroundIsFirstFossil(pUGData)){
        pFET->_PARTS_TREASURE_NUM=3;
    }
    for(i = 0; i < pFET->_PARTS_TREASURE_NUM; ){
        rand = MATH_Rand32(&_pCommFossilWork->sRand, treasureRand);  // ����̉��𖄂߂邩���߂�
        partsIndex = _getTreasurePartsRandom(rand);
        type = _partsData[partsIndex].partsType;
        if(!UnderGroundIsFossilAdvent(pUGData,_partsData[partsIndex].partsType)){
            OHNO_PRINT("%d�̓��A�ł��߂�܂���\n",type);
            continue;
        }
        if((DIG_PARTS_PLATE_FIRE <= type) && (type <= DIG_PARTS_PLATE_IRON)){
            BOOL dbl = FALSE;
            plate[i] = type;  //���A�o�^
            for(j = 0;j < i;j++){
                if(plate[j] == type){
                    dbl = TRUE;
                }
            }
            if(dbl){
                OHNO_PRINT("%d��double�ł��߂�܂���\n",type);
                continue;
            }
        }
        else{
            plate[i] = DIG_PARTS_BONE;
        }
        
        
        x = MATH_Rand32(&_pCommFossilWork->sRand, _DIGMAP_WIDTH);
        y = MATH_Rand32(&_pCommFossilWork->sRand, _DIGMAP_HEIGHT);
        if(_partsDeposit(partsIndex, x, y)){
            OHNO_PRINT("parts %d x=%d y=%d %d\n",partsIndex, x, y);
            i++;
        }
    }
    if(!UnderGroundIsFirstFossil(pUGData)){
        for(limit = 0; limit < 100 ; limit++){
            partsIndex = MATH_Rand32(&_pCommFossilWork->sRand, noDigNum);  // �ז�����d���΂𖄂߂�
            partsIndex += NELEMS(_partsData) - noDigNum;
            x = MATH_Rand32(&_pCommFossilWork->sRand, _DIGMAP_WIDTH);
            y = MATH_Rand32(&_pCommFossilWork->sRand, _DIGMAP_HEIGHT);
            if(_partsDeposit(partsIndex, x, y)){
                OHNO_PRINT("parts %d x=%d y=%d %d\n",partsIndex, x, y);
                i++;
            }
            if(i > 12){
                break;
            }
        }
    }
    _depositBGInit(i, bgl, charByte, pFET);

#ifdef PM_DEBUG
    OHNO_SP_PRINT("�z�uMAP \n");
    for(y = 0; y < _DIGMAP_HEIGHT; y++){
        for(x = 0; x < _DIGMAP_WIDTH ; x++){
            OHNO_SP_PRINT("%2d ", _pCommFossilWork->depositMap[y][x]);
        }
        OHNO_SP_PRINT(" \n");
    }
#endif
}
#endif

//--------------------------------------------------------------
/**
 * �����p�[�c�ɏ]���L�����]�� + BG����������
 * @param    none
 * @retval   nextCharOffset
 */
//--------------------------------------------------------------
#define _PALLET_INDEX (3)

static int _depositBGInitParts(int idx, GF_BGL_INI* bgl, int charOffset, FossilEventTask* pFET)
{
    FossilPartsData* pFPD = &_pCommFossilWork->aDeposit[idx];
    u16* pScrAddr = GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME1_M );
    int xini = pFPD->x * 2;
    int yini = pFPD->y * 2;
    int xend = xini + pFPD->pParts->width;
    int yend = yini + pFPD->pParts->height;
    int y,x,scr,i=charOffset;
    u32 sendByte;
    int pidx = idx;

    if(idx >= pFET->_PARTS_TREASURE_NUM){   // �d���΂̐���
        pidx = _PARTS_TREASURE_NUM_MAX;  // �d���΂̃p���b�g�ʒu�������ɂȂ�
    }
    if(idx >= pFET->_PARTS_TREASURE_NUM){   // �d���΂̐���
        ArcUtil_PalSet( ARC_UG_PARTS_GRA, pFPD->pParts->ncl, PALTYPE_MAIN_BG, (pidx + _PALLET_INDEX)*32, 32,  HEAPID_DIGFOSSIL);
    }
    else{
        pFET->pPalBuff[idx] = ArcUtil_PalDataGet(
            ARC_UG_PARTS_GRA, pFPD->pParts->ncl, &pFET->palData[idx], HEAPID_DIGFOSSIL );
        DC_FlushRange( pFET->palData[idx]->pRawData, 32 );
        GX_LoadBGPltt( pFET->palData[idx]->pRawData, (pidx + _PALLET_INDEX)*32, 32 );
    }

    sendByte = ArcUtil_BgCharSet( ARC_UG_PARTS_GRA, pFPD->pParts->ncg, bgl,
                                  GF_BGL_FRAME1_M, charOffset, 0, 0, HEAPID_DIGFOSSIL);

    OHNO_PRINT("scr disp %d %d %d %d  %d \n",xini,yini,xend,yend,charOffset);

    for(y = yini; y < yend; y++){
        for(x = xini; x < xend; x++){
            i++;
            if(!_isAttribute( pFPD->pParts, x - xini, y - yini )){
                continue;
            }
            scr = x + ((y + 4) * 32);
            pScrAddr[scr] = ((pidx + _PALLET_INDEX)*0x1000) + i - 1;
        }
    }
    return sendByte;
}

//--------------------------------------------------------------
/**
 * �p�[�c��BG�J���[�A�j������
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static u8 _palPattern[]={32,0xfe,64,0xfe,32,0xfe,0,0xfe,32,0xfe,64,0xfe,32,0xfe,0,0xff};

static void _partsDigColor(FossilEventTask* pFET)
{
    int i,x,y,j;
    VecFx32 tmpVex;
//    MATHRandContext32 sRand;

    // �@��͂��߂�SE�ƃA�j����ݒ�
    for(i = 0 ; i < _PARTS_TREASURE_NUM_MAX;i++){
        if(pFET->digTimer[i]==1){
            Snd_SePlay(UG_SE_DIG_FOSSIL);
            for(j = 0; j < 3;j++){
                x = MATH_Rand32(&_pCommFossilWork->sRand,_pCommFossilWork->aDeposit[i].pParts->width*8);
                y = MATH_Rand32(&_pCommFossilWork->sRand,_pCommFossilWork->aDeposit[i].pParts->height*8);
                x += _pCommFossilWork->aDeposit[i].x*2*8;
                y += _pCommFossilWork->aDeposit[i].y*2*8;
                y += 8*4;
                OHNO_SP_PRINT("�`��ꏊ  %d %d \n",x,y);
                tmpVex.x = FX32_ONE * x;
                tmpVex.y = FX32_ONE * y;
                CLACT_AnmChg( _pCommFossilWork->clActWork[_CLACT_KIRA_P1+j], 8+j );
                CLACT_SetMatrix(_pCommFossilWork->clActWork[_CLACT_KIRA_P1+j], &tmpVex);
            }
        }
    }

    
    for(i = 0 ; i < _PARTS_TREASURE_NUM_MAX;i++){
        if(pFET->digTimer[i]){
            u16* pPal = pFET->palData[i]->pRawData;
            u8 pattern = _palPattern[pFET->digTimer[i]-1];
            if(pattern==0xff){
                pFET->digTimer[i]=0;
                continue;
            }
            pFET->digTimer[i]++;
            if(pattern==0xfe){
                continue;
            }
            GX_LoadBGPltt( &pPal[pattern], (i + _PALLET_INDEX)*32, 32 );
        }
    }
}

//--------------------------------------------------------------
/**
 * �����p�[�c�ɏ]���L�����]�� + BG����������
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static void _depositBGInit(int partsMax, GF_BGL_INI* bgl, int charByte, FossilEventTask* pFET)
{
    int i,charOffset = 512 + 24*3 + 32 + 1; //1 + charByte/32;
    u32 sendByte;

    for(i = 0 ; i < partsMax; i++){
        sendByte = _depositBGInitParts(i, bgl , charOffset, pFET);
        charOffset += sendByte/32;
    }
}

//--------------------------------------------------------------
/**
 * �͐ϕ��𗐐��Ō��߂�
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static void _randomBuildup(GF_BGL_INI* bgl)
{
    static const u8 B1MAX = 8;
    static const u8 B2MAX = 5;

    static u8 buildup1[B1MAX][B1MAX]={{0,0,4,4,4,4,0,0},{0,4,4,4,4,4,4,0},{4,4,4,4,4,4},{4,4,4,4,4,4},
        {4,4,4,4,4,4},{4,4,4,4,4,4},{0,4,4,4,4,4,4,0},{0,0,4,4,4,4,0,0}};
    static u8 buildup2[B2MAX][B2MAX]={{0,6,6,6,0},{6,6,6,6,6},{6,6,6,6,6},{6,6,6,6,6},{0,6,6,6,0}};
//    MATHRandContext32 sRand;
    int rand, parts, x, y, xini, yini,i;
    BOOL bBuildup = TRUE;
    
//    CommRandSeedInitialize(&sRand);
    for(i = 0; i < 10; i++){   // A�y���P�O��d�˂�
        xini = MATH_Rand32(&_pCommFossilWork->sRand, _DIGMAP_WIDTH+B1MAX)-B1MAX;
        yini = MATH_Rand32(&_pCommFossilWork->sRand, _DIGMAP_HEIGHT+B1MAX)-B2MAX;
        for(y = yini; y < yini+B1MAX; y++){
            if( (y >= _DIGMAP_HEIGHT) || (y < 0)){
                continue;
            }
            for(x = xini; x < xini+B1MAX; x++){
                if( (x >= _DIGMAP_WIDTH)  || (x < 0)){
                    continue;
                }
                if(buildup1[y-yini][x-xini]==0){
                    continue;
                }
                 _pCommFossilWork->buildupMap[y][x]=buildup1[y-yini][x-xini];
            }
        }
    }
    for(i = 0; i < 15; i++){   // B�y15��d�˂�
        xini = MATH_Rand32(&_pCommFossilWork->sRand, _DIGMAP_WIDTH+B2MAX)-B2MAX;
        yini = MATH_Rand32(&_pCommFossilWork->sRand, _DIGMAP_HEIGHT+B2MAX)-B2MAX;
        bBuildup = TRUE;
        for(y = yini; y < yini+B2MAX; y++){
            if( (y >= _DIGMAP_HEIGHT) || (y < 0)){
                continue;
            }
            for(x = xini; x < xini+B2MAX; x++){
                if( (x >= _DIGMAP_WIDTH)  || (x < 0)){
                    continue;
                }
                if(buildup1[y-yini][x-xini]==0){
                    continue;
                }
                if(_pCommFossilWork->buildupMap[y][x]<4){
                    bBuildup = FALSE;
                    break;
                }
            }
            if(bBuildup == FALSE){
                break;
            }
        }
        if(!bBuildup){
            continue;
        }
        for(y = yini; y < yini+B2MAX; y++){
            if( (y >= _DIGMAP_HEIGHT) || (y < 0)){
                continue;
            }
            for(x = xini; x < xini+B2MAX; x++){
                if( (x >= _DIGMAP_WIDTH)  || (x < 0)){
                    continue;
                }
                if(buildup2[y-yini][x-xini]==0){
                    continue;
                }
                _pCommFossilWork->buildupMap[y][x]=buildup2[y-yini][x-xini];
            }
        }
    }


#if 1
    OHNO_PRINT("�͐�MAP \n");
    for(y = 0; y < _DIGMAP_HEIGHT; y++){
        for(x = 0; x < _DIGMAP_WIDTH ; x++){
            OHNO_PRINT("%2d ", _pCommFossilWork->buildupMap[y][x]);
        }
        OHNO_PRINT(" \n");
    }
#endif

}

//--------------------------------------------------------------
/**
 * �y�𐷂�BG�������_�����O
 * @param    none
 * @retval   nextCharOffset
 */
//--------------------------------------------------------------

static void _buildupBGDraw(GF_BGL_INI* bgl)
{
    static u8 lv0[]={0xe,0xf,0x1e,0x1f};
    static u8 lv1[]={0xa,0xb,0x1a,0x1b};
    static u8 lv2[]={0x8,0x9,0x18,0x19};
    static u8 lv3[]={0x6,0x7,0x16,0x17};
    static u8 lv4[]={0x4,0x5,0x14,0x15};
    static u8 lv5[]={0x2,0x3,0x12,0x13};
    static u8 lv6[]={0x0,0x1,0x10,0x11};
    static u8* lvlTbl[]={lv0,lv1,lv2,lv3,lv4,lv5,lv6};
    u16* pScrAddr = GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME2_M );
    int y,x,scr;

    for(y = 0; y < _DIGMAP_HEIGHT; y++){
        for(x = 0; x < _DIGMAP_WIDTH ; x++){
            u8* pTbl = lvlTbl[_pCommFossilWork->buildupMap[y][x]];
            scr = x*2+((y*2+4)*32);
            pScrAddr[scr] =  pTbl[0]+0x2001;
            pScrAddr[scr+1] =  pTbl[1]+0x2001;
            pScrAddr[scr+32] =  pTbl[2]+0x2001;
            pScrAddr[scr+33] =  pTbl[3]+0x2001;
        }
    }
    GF_BGL_LoadScreenReq(bgl, GF_BGL_FRAME2_M);
}

//--------------------------------------------------------------
/**
 * ���΂��ǂ����H
 * @param    x,y   �@��ʒu
 * @retval   ���΂�TRUE
 */
//--------------------------------------------------------------

static BOOL _isFossil(int x, int y)
{
    int type;
    int idx = _pCommFossilWork->depositMap[y][x];
    if(idx==0){
        return FALSE;
    }
    type = _pCommFossilWork->aDeposit[idx-1].partsType;
    if((type != DIG_PARTS_NONE) && (type < DIG_PARTS_TREASURE_MAX)){  //�d����
        return TRUE;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * �d���΂��ǂ����H
 * @param    x,y   �@��ʒu
 * @retval   �d�����TRUE
 */
//--------------------------------------------------------------

static BOOL _isHardStone(int x, int y)
{
    int idx = _pCommFossilWork->depositMap[y][x];
    if(idx==0){
        return FALSE;
    }
    if(_pCommFossilWork->aDeposit[idx-1].partsType >= DIG_PARTS_TREASURE_MAX){  //�d����
        return TRUE;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * �y���@��
 * @param    x,y   �@��ʒu
 * @param    bPic   �@��type
 * @retval   �@�����R�X�g
 */
//--------------------------------------------------------------

static void _digWall(int x, int y,BOOL bPic,FossilEventTask* pFET)
{
    static s8 ham1X[]={1,-1,-1, 1};  // �n���}�[���@��
    static s8 ham1Y[]={1,-1, 1,-1};
    static s8 picX[]={0,0,-1,1};   // �n���}�[�Ȃ�Q��ق��
    static s8 picY[]={1,-1,0,0};
    int mapX,mapY,idx,i;
    BOOL bHard = FALSE, bFossil = FALSE;

    // �@��MAP���W�֕ϊ�
    mapX = x / 16;
    mapY = y / 16 - 2;

    if((mapX < 0) || (mapX >= _DIGMAP_WIDTH) || (mapY < 0) || (mapY >= _DIGMAP_HEIGHT)){
        return;
    }
    if(_pCommFossilWork->buildupMap[mapY][mapX] != 0){
        _pCommFossilWork->buildupMap[mapY][mapX] -= 1;
    }
    if(_pCommFossilWork->buildupMap[mapY][mapX] != 0){
        _pCommFossilWork->buildupMap[mapY][mapX] -= 1;
    }
    if(_isHardStone(mapX, mapY) && (_pCommFossilWork->buildupMap[mapY][mapX]==0)){  //�d���΂̏ꍇ
        bHard = TRUE;
    }
    if(_isFossil(mapX, mapY) && (_pCommFossilWork->buildupMap[mapY][mapX]==0) ){
        bFossil = TRUE;
        pFET->kiraTimer = 15;
    }
    _hammerStart(mapX*16, (mapY+2)*16, bPic, bHard, bFossil);
    if(bHard){
        return;
    }
    if(!bPic){
        for(i = 0 ; i < 4; i++){
            int cy = mapY+ham1Y[i];
            int cx = mapX+ham1X[i];
            if((cy >= 0) && (cy < _DIGMAP_HEIGHT)){
                if((cx >= 0) && (cx < _DIGMAP_WIDTH)){
                    if(_pCommFossilWork->buildupMap[cy][cx] != 0){
                        _pCommFossilWork->buildupMap[cy][cx] -= 1;
                    }
                }
            }
        }
    }
    for(i = 0 ; i < 4; i++){
        int cy = mapY+picY[i];
        int cx = mapX+picX[i];
        if((cy >= 0) && (cy < _DIGMAP_HEIGHT)){
            if((cx >= 0) && (cx < _DIGMAP_WIDTH)){
                if(_pCommFossilWork->buildupMap[cy][cx] != 0){
                    _pCommFossilWork->buildupMap[cy][cx] -= 1;
                }
                if( !bPic ){
                    if(_pCommFossilWork->buildupMap[cy][cx] != 0){
                        _pCommFossilWork->buildupMap[cy][cx] -= 1;
                    }
                }
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * �w��͈͂̃X�N���[����^����ꂽ�l�ő�������
 * @param    pScrTop    �X�N���[���̃|�C���^
 * @param    xIni,yIni,xEnd,yEnd  ����������X�N���[���̍��W
 * @param    bPush  �������̂��������̂�
 * @retval   none
 */
//--------------------------------------------------------------

static void _scrDataChange(u16* pScrTop,_SCR_RECT* pRect,int changeNum, int plusNum)
{
    int scr,y,x,pos,i;

    for(y = pRect->lt_y, i = 0; y < pRect->rb_y; y++, i++){
        pos = plusNum * i + changeNum;
        for(x = pRect->lt_x; x < pRect->rb_x; x++){
            scr = x + (y * 32);
            pScrTop[scr] = (pScrTop[scr]&0xfc00) + pos;
            pos++;
        }
    }
}


//--------------------------------------------------------------
/**
 * �E���̃^�b�`�p�l���{�^������
 * @param    none
 * @retval   nextCharOffset
 */
//--------------------------------------------------------------

static _SCR_RECT hummerPos[] ={ 0x1a,0x06,0x20,0x0e  };
static _SCR_RECT picPos[] ={ 0x1a,0x0f,0x20,0x17  };
static _SCR_RECT endPos[] ={ 0x1a,0x00,0x20,0x04  };


static void _touchButtonInitialize(GF_BGL_INI* bgl)
{
    u16* pScrAddr;

    _pCommFossilWork->touchButton = _PIC_BUTTON;
    _pCommFossilWork->bPic = TRUE;
    pScrAddr = GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME1_M );
    _scrDataChange(pScrAddr, picPos, 0x30, 54);  // �������G
    // �X�N���[���ւ̓]���͌�ł܂Ƃ߂�
}

static void _touchButtonProcess(GF_BGL_INI* bgl,int x, int y, int level)
{
    VecFx32 tmpVex;
    u8* pPos;
    u16* pScrAddr;

    if(level < _PUSH_START){
        return;
    }
    if(level == _PUSH_START){   // �����ꂽ���͈ʒu����{�^����ނ����߂�
        if((x > (0x1a*8+6)) &&  ((0x1f*8+4) > x)){
            if((y > (5*8+3)) && ((0xd*8+6) > y)){  //�n���}�[
                _pCommFossilWork->touchButton = _HUMMER_BUTTON;
                _pCommFossilWork->bPic = FALSE;
            }
            else if((y > (0xe*8+2)) && ((0x15*8+6) > y)){  //�̂�
                _pCommFossilWork->touchButton = _PIC_BUTTON;
                _pCommFossilWork->bPic = TRUE;
            }
            else{
                return;
            }
        }
        else{
            return;
        }
    }

    pScrAddr = GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME1_M );
    switch( _pCommFossilWork->touchButton ){
      case _HUMMER_BUTTON:
        if(_PUSH_START == level){
            _scrDataChange(pScrAddr, hummerPos, 0x18, 54);  // level1
            _scrDataChange(pScrAddr, picPos, 0x24, 54);  // �߂��G
            Snd_SePlay(UG_SE_TOUCH_BUTTON);
        }
        else if(_PUSH_START+1 == level){
            _scrDataChange(pScrAddr, hummerPos, 0x1e, 54);  // �������G
        }
        if(_PUSH_START == level){
            CLACT_AnmChg( _pCommFossilWork->clActWork[_CLACT_EFFECT], 6 );
            CLACT_SetAnmFlag(_pCommFossilWork->clActWork[_CLACT_EFFECT],1);
            tmpVex.x = FX32_ONE * (232);
            tmpVex.y = FX32_ONE * (80);
            CLACT_SetMatrix(_pCommFossilWork->clActWork[_CLACT_EFFECT], &tmpVex);
        }
        break;
      case _PIC_BUTTON:
        if(_PUSH_START == level){
            _scrDataChange(pScrAddr, hummerPos, 0x12, 54);  // �߂��G
            _scrDataChange(pScrAddr, picPos, 0x2a, 54);  // �����G
            Snd_SePlay(UG_SE_TOUCH_BUTTON);
        }
        else if(_PUSH_START+1 == level){
            _scrDataChange(pScrAddr, picPos, 0x30, 54);  // �������G
        }
        if(_PUSH_START == level){
            CLACT_AnmChg( _pCommFossilWork->clActWork[_CLACT_EFFECT], 7 );
            CLACT_SetAnmFlag(_pCommFossilWork->clActWork[_CLACT_EFFECT],1);
            tmpVex.x = FX32_ONE * (232);
            tmpVex.y = FX32_ONE * (152);
            CLACT_SetMatrix(_pCommFossilWork->clActWork[_CLACT_EFFECT], &tmpVex);
        }
        break;
    }
    GF_BGL_LoadScreenReq(bgl, GF_BGL_FRAME1_M);  // �X�N���[���ɍX�V
}

//--------------------------------------------------------------
/**
 * �q�r�Q�[�W�̈ʒu���o��
 * @param    none
 * @retval   nextCharOffset
 */
//--------------------------------------------------------------

static void _setHibiMatrix(VecFx32* mtx)
{
    int i;
    int gauge = _pCommFossilWork->digGauge;

    gauge = (gauge / 4) * 4;  //gauge�͂S�̔{��
    gauge = gauge+8;
    mtx->x = FX32_ONE * ((gauge+8));
    mtx->y = FX32_ONE * (16);
}

//--------------------------------------------------------------
/**
 * �ǌ@��Q�[�W�̕\��
 * @param    none
 * @retval   nextCharOffset
 */
//--------------------------------------------------------------

static void _gaugeDisp(GF_BGL_INI* bgl)
{
    VecFx32 tmpVex;
    int gauge = _pCommFossilWork->digGauge;
    int changeBlock,i,pattern;
    u16* pScrAddr = GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME0_M );

    gauge = (gauge / 4) * 4;  //gauge�͂S�̔{��
    pattern = 6 - (gauge % 24) / 4;
    _setHibiMatrix(&tmpVex);
    CLACT_AnmChg( _pCommFossilWork->clActWork[_CLACT_HIBI], pattern );
 //   CLACT_SetMatrix(_pCommFossilWork->clActWork[_CLACT_HIBI], &tmpVex);
    gauge = gauge+8;

    changeBlock = ((26 * 8) - gauge) / 8;

    for(i = 0; i < changeBlock;i++){
        pScrAddr[0x19-i] = (pScrAddr[0x19-i]&0xfc00) + 0x0b - (i % 3);
        pScrAddr[0x39-i] = (pScrAddr[0x39-i]&0xfc00) + 0x41 - (i % 3);
        pScrAddr[0x59-i] = (pScrAddr[0x59-i]&0xfc00) + 0x77 - (i % 3);
        pScrAddr[0x79-i] = (pScrAddr[0x79-i]&0xfc00) + 0xad - (i % 3);
    }

    GF_BGL_LoadScreenReq(bgl, GF_BGL_FRAME0_M);  // �X�N���[���ɍX�V
    

}

//--------------------------------------------------------------
/**
 * �F�l�̎�`���Ō@��i�߂���
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static void _friendDig(FossilEventTask* pFET)
{
    BOOL bChange = FALSE;
    int i;

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if((_pCommFossilWork->friendDigPointX[i] != _DIGMAP_INVALID) &&
           (_pCommFossilWork->friendDigPointZ[i] != _DIGMAP_INVALID)){
            int x = CommPlayerGetPosX(CommGetCurrentID());
            int y = CommPlayerGetPosZ(CommGetCurrentID());
            int ox = CommPlayerGetPosDigFossilX(i);
            int oz = CommPlayerGetPosDigFossilZ(i);
            if((ox > (x - _FRIEND_DIG_AREA)) && (ox < (x + _FRIEND_DIG_AREA))){
                if((oz > (y - _FRIEND_DIG_AREA)) && (oz < (y + _FRIEND_DIG_AREA))){
                    _digWall(_pCommFossilWork->friendDigPointX[i],
                             _pCommFossilWork->friendDigPointZ[i], TRUE, pFET);
                    bChange = TRUE;
                    _pCommFossilWork->friendDigPointX[i] = _DIGMAP_INVALID;
                    _pCommFossilWork->friendDigPointZ[i] = _DIGMAP_INVALID;
                }
            }
        }
    }
    if(bChange){
        _buildupBGDraw(_pCommFossilWork->bgl);
    }
}

//--------------------------------------------------------------
/**
 * �@�������̂̃J���b�g�v�Z
 * @param    type   �@�������
 * @retval   carat�̑傫��
 */
//--------------------------------------------------------------

static int _calcDigStoneCarat(int no)
{
 //   MATHRandContext32 sRand;
    int carat = 0;
    int stone = no;
    
//    CommRandSeedInitialize(&sRand);
    if(CommDigIsStone(stone)){
        if((stone == DIG_PARTS_KONGOU_L) || (stone == DIG_PARTS_SIRATAMA_L) ||
           (stone == DIG_PARTS_KONGOU_S) || (stone == DIG_PARTS_SIRATAMA_S)){
            carat = MATH_Rand32(&_pCommFossilWork->sRand, 1)+1;
        }
        else{
            carat = MATH_Rand32(&_pCommFossilWork->sRand, 4)+1;
        }
        if((stone == DIG_PARTS_KONGOU_L) || (stone == DIG_PARTS_SIRATAMA_L) ||
           (stone == DIG_PARTS_RED_L) || (stone == DIG_PARTS_BLUE_L) || (stone == DIG_PARTS_GREEN_L)){
            stone = stone - DIG_PARTS_KONGOU_L + STONE_TYPE_DIAMOND;
            carat += 10;
        }
        carat += _pCommFossilWork->digGauge / (_DIG_GAUGE_START / 5);
        if(_pCommFossilWork->digGauge != 0){  // �Q�[�W���c���Ă��遁���ɂقꂽ
            carat += 5;
        }
    }
    return carat;
}

//--------------------------------------------------------------
/**
 * �@�������̂��o�b�O�ɓ����
 * @param    type   �@�������
 * @retval   carat�̑傫��
 */
//--------------------------------------------------------------

static void _bagAddFossil(int no, int carat)
{
 //   MATHRandContext32 sRand;
    int stone = no;
    SB_RECORD_DATA* pRec = SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(_pCommFossilWork->pFSys));
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommFossilWork->pFSys));
    
 //   CommRandSeedInitialize(&sRand);
    if(CommDigIsStone(stone)){
        CommUnderBagAddStone(stone, carat);
    }
    else{
        CommUnderBagAddTreasure(stone);
        UnderGroundSetFossilDig(pUGData,stone);
    }
}

//--------------------------------------------------------------
/**
 * �@�������̂��o�b�O�ɓ��邩����
 * @param    type   �@�������
 * @retval   none
 */
//--------------------------------------------------------------

static BOOL _bagIsIn(int no)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommFossilWork->pFSys));

    if(CommDigIsStone(no)){
        if(UG_ITEM_BAG_NUM_MAX == UnderGroundGetNumStoneBagItem(pUGData)){
            return FALSE;
        }
        return TRUE;
    }
    else{
        if(UG_ITEM_BAG_NUM_MAX == UnderGroundGetNumTreasureBagItem(pUGData)){
            return FALSE;
        }
        return TRUE;
    }

}

//--------------------------------------------------------------
/**
 * ���Δ��@����  ���b�Z�[�W�͕ʂɏ�������K�v������
 * @param    none
 * @retval   �S���قꂽ�ꍇTRUE
 */
//--------------------------------------------------------------

static BOOL _treasureCheck(FossilEventTask* pFET)
{
    int y,x,i;
    BOOL bTreasure[_PARTS_TREASURE_NUM_MAX];
    BOOL bRet = TRUE;

    //depositMap��1����_PARTS_TREASURE_NUM�܂ł���
    // ���̔ԍ��̏�ɑ͐ϕ�����������@��ĂȂ�
    for(i = 0; i < pFET->_PARTS_TREASURE_NUM; i++){
        bTreasure[i] = TRUE;
    }
    for(y = 0; y < _DIGMAP_HEIGHT; y++){
        for(x = 0; x < _DIGMAP_WIDTH; x++){
            i = _pCommFossilWork->depositMap[ y ][ x ];
            if((i <= pFET->_PARTS_TREASURE_NUM) && (i != 0)){   // ����MAP  ��������index+1������ 0�͖������Ă��Ȃ�
                if(_pCommFossilWork->buildupMap[ y ][ x ] != 0){
                    bTreasure[i-1] = FALSE;
                }
            }
        }
    }

    for(i = 0; i < pFET->_PARTS_TREASURE_NUM; i++){
        if(!bTreasure[i]){
            bRet = FALSE;
        }
        else if(_pCommFossilWork->aDeposit[i].bGetItem==FALSE){
            // �@�ꂽ
            pFET->digTimer[i] = 1;
            _pCommFossilWork->aDeposit[i].bGetItem = TRUE;
        }
    }
    return bRet;
}

//--------------------------------------------------------------
/**
 * ���ΐ��ʕ����b�Z�[�W
 * @param    none
 * @retval   �������b�Z�[�W�������ꍇFALSE
 */
//--------------------------------------------------------------

static BOOL _fossilGetMessage(FossilEventTask* pFET)
{
    int i,msgno;
    
    for(i = 0; i < pFET->_PARTS_TREASURE_NUM; i++){
        if(_pCommFossilWork->aDeposit[i].bGetItem == TRUE){
            pFET->digCarat = _calcDigStoneCarat(_pCommFossilWork->aDeposit[i].partsType);
            if(CommDigIsStone(_pCommFossilWork->aDeposit[i].partsType)){
                msgno = msg_underworld_69;
                CommMsgRegisterNumber2Index(CommUnderGetMsgUnderWorld(), 1, pFET->digCarat);
            }
            else{
                msgno = msg_underworld_18;
            }
            CommMsgRegisterUGItemName(CommUnderGetMsgUnderWorld(),
                                      _pCommFossilWork->aDeposit[i].partsType);
            _pCommFossilWork->winIndex =
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                       msgno,FALSE,NULL);
            return TRUE;
        }
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * ���ΐ��ʕ����b�Z�[�W
 * @param    none
 * @retval   �������b�Z�[�W�������ꍇFALSE
 */
//--------------------------------------------------------------

static BOOL _fossilGetMessageBagIn(FossilEventTask* pFET)
{
    int i,msgno,type;
    SB_RECORD_DATA* pRec = SaveData_GetSecretBaseRecord((_pCommFossilWork->pFSys->savedata));
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData((_pCommFossilWork->pFSys->savedata));
    
    for(i = 0; i < pFET->_PARTS_TREASURE_NUM; i++){
        if(_pCommFossilWork->aDeposit[i].bGetItem == TRUE){
            _pCommFossilWork->aDeposit[i].bGetItem = FALSE;
            // �@�������̂���������
            type = _pCommFossilWork->aDeposit[i].partsType;

            // ���Ό@�����񐔂̓o�b�O�ɓ��ꂽ���ǂ����͊֌W�Ȃ��ŃJ�E���g
            if(CommDigIsStone(type)){
                SecretBaseRecordSetStoneNum(pRec ,1);
            }
            else{
                TVTOPIC_Entry_Watch_DigFossil(_pCommFossilWork->pFSys, type, 1);
                
                if((type >= DIG_PARTS_TYPE_FOSSIL_MIN) && (DIG_PARTS_TYPE_FOSSIL_MAX > type) ||
                   (type == DIG_PARTS_SHIELD) || (type == DIG_PARTS_ZUGAI)){
                    SecretBaseRecordSetFossilNum(pRec ,1);
                    {  // ���Ό@�����񐔃J�E���g
                        EVENTWORK* pEV = SaveData_GetEventWork( _pCommFossilWork->pFSys->savedata );
                        SysWork_UGKasekiDigCountSet(pEV,SysWork_UGKasekiDigCountGet(pEV)+1);
                    }
                }
                else{
                    SecretBaseRecordSetTreasureNum(pRec ,1); //�@�������Ƃ��ăJ�E���g
                }
            }

            if(_bagIsIn(type)){  // ���΂�ɓ���ꍇ
                _bagAddFossil(type, pFET->digCarat);
                break;
            }
            else{
                _pCommFossilWork->winIndex =
                    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                           msg_underworld_65,FALSE,NULL);
                return TRUE;
            }
        }
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * ��ʂ�h�炷
 * @param    bgl      GF_BGL_INI
 * @param    bVBlank  �Ăяo���悪��ӏ����� �u�����N�Ăяo�����ǂ���
 * @retval   none
 */
//--------------------------------------------------------------

static void _shakeProcess(GF_BGL_INI* bgl)
{
//    MATHRandContext32 sRand;
    int i,num,wave;
    VecFx32 tmpVex;

    if(_pCommFossilWork->shakeCount==0){
        return;
    }
    num = ((_DIG_GAUGE_START - _pCommFossilWork->digGauge) / 15);
    wave = ((_DIG_GAUGE_START - _pCommFossilWork->digGauge) / 50);

    
    _pCommFossilWork->shakeCount++;
    if(_pCommFossilWork->shakeCount > num){
        _pCommFossilWork->shakeX = _pCommFossilWork->shakeZ = 0;
    }
    else{
//        CommRandSeedInitialize(&sRand);
        _pCommFossilWork->shakeX = MATH_Rand32(&_pCommFossilWork->sRand,3+wave) - (3+wave)/2;
        _pCommFossilWork->shakeZ = MATH_Rand32(&_pCommFossilWork->sRand,3+wave) - (3+wave)/2;
        }
    _setHibiMatrix(&tmpVex);
    tmpVex.x -= _pCommFossilWork->shakeX*FX32_ONE;
    tmpVex.y -= _pCommFossilWork->shakeZ*FX32_ONE;
    CLACT_SetMatrix(_pCommFossilWork->clActWork[_CLACT_HIBI], &tmpVex);
}

//--------------------------------------------------------------
/**
 * ��ʂ�h�炷
 * @param    bgl      GF_BGL_INI
 * @param    bVBlank  �Ăяo���悪��ӏ����� �u�����N�Ăяo�����ǂ���
 * @retval   none
 */
//--------------------------------------------------------------

static void _shakeProcessVBlank(GF_BGL_INI* bgl)
{
    int i,num,wave;
    VecFx32 tmpVex;

    if(_pCommFossilWork->shakeCount==0){
        return;
    }
    num = ((_DIG_GAUGE_START - _pCommFossilWork->digGauge) / 10);

    if(_pCommFossilWork->shakeCount > num){
        _pCommFossilWork->shakeCount = 0;
    }
    for(i = 0;i < 3;i++){
        GF_BGL_ScrollSet(bgl, i, GF_BGL_SCROLL_X_SET, _pCommFossilWork->shakeX);
        GF_BGL_ScrollSet(bgl, i, GF_BGL_SCROLL_Y_SET, _pCommFossilWork->shakeZ);
    }
}

//--------------------------------------------------------------
/**
 * �~�j�Q�[���̃v���Z�X
 * @param    none
 * @retval   nextCharOffset
 */
//--------------------------------------------------------------

static BOOL _gameProcess(FossilEventTask* pFET)
{
    u8 posBuff[2];
    int cost;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommFossilWork->pFSys));

    if(_pCommFossilWork->touchPanelRelease == 1){
        _pCommFossilWork->touchPanelRelease = 0;
    }
    if(sys.tp_trg){
        if((sys.tp_x < 2*8*_DIGMAP_WIDTH) && (sys.tp_y >= 4*8)){
            posBuff[0] = sys.tp_x;
            posBuff[1] = sys.tp_y;
            _digWall(sys.tp_x, sys.tp_y,_pCommFossilWork->bPic,pFET);
            if(_pCommFossilWork->bPic){
                cost = _COST_DIG_PIC;
            }
            else{
                cost = _COST_DIG_HUMMER;
            }
            CommSendFixSizeData(CF_DIG_FOSSIL_POS, posBuff);
            if(_pCommFossilWork->digGauge > cost){
                _pCommFossilWork->digGauge -= cost;
            }
            else{
                _pCommFossilWork->digGauge=0;
            }
            _buildupBGDraw(_pCommFossilWork->bgl);
            _gaugeDisp(_pCommFossilWork->bgl);
            _pCommFossilWork->shakeCount = 1;
        }
        else if(sys.tp_x >= (2*8*_DIGMAP_WIDTH)){
            _pCommFossilWork->touchPanelRelease = 2;
        }
    }
    if(pFET->kiraTimer){
        pFET->kiraTimer--;
        if(pFET->kiraTimer == 0){
            Snd_SePlay(UG_SE_FIND_FOSSIL);
        }
    }
    _touchButtonProcess(_pCommFossilWork->bgl,
                        sys.tp_x, sys.tp_y, _pCommFossilWork->touchPanelRelease);  // �{�^������
    if(_pCommFossilWork->touchPanelRelease >= 2){
        _pCommFossilWork->touchPanelRelease++;
    }
    _friendDig(pFET);
//	CLACT_Draw( _pCommFossilWork->clactSet );									// �Z���A�N�^�[�풓�֐�
    if(_treasureCheck(pFET)){  // �S���@����
        UnderGroundSetFirstFossil(pUGData);
        RECORD_Score_Add(SaveData_GetRecord(_pCommFossilWork->pFSys->savedata), SCORE_ID_GET_FOSSIL);
//        _pCommFossilWork->logMsgFossil[CommGetCurrentID()] = TRUE;
        pFET->seq = _SEQ_SUCCESS_WAIT;
        pFET->timer = 25;
        pFET->bSuccess = TRUE;
        return TRUE;
    }
    else if((_pCommFossilWork->digGauge == 0)){  // �Q�[�W�������Ȃ���

        UnderGroundSetFirstFossil(pUGData);

        pFET->bSuccess = FALSE;
        pFET->timer = 45;
        pFET->seq = _SEQ_QUAKE;
        return TRUE;
    }
    return FALSE;
}

static void _setResObjTbl(CLACT_U_RES_OBJ_PTR pRes)
{
    _pCommFossilWork->resObjTbl[_pCommFossilWork->resObjCount] = pRes;
    _pCommFossilWork->resObjCount++;
}

//------------------------------------------------------------------
/**
 * �n���}�p�Z���A�N�^�[������
 * @param   none
 * @retval  none		
 */
//------------------------------------------------------------------
#define _CLACT_OAMNUM  (5)

static void _initCellActor(void)
{
    int i;

    _pCommFossilWork->resObjCount = 0;
    // OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();
	// ���LOAM�}�l�[�W���쐬
	// �����_���pOAM�}�l�[�W���쐬
	// �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
	REND_OAMInit( 
			0, 124,		// ���C�����OAM�Ǘ��̈�
			0, 31,		// ���C����ʃA�t�B���Ǘ��̈�
			0, 124,		// �T�u���OAM�Ǘ��̈�
			0, 31,		// �T�u��ʃA�t�B���Ǘ��̈�
			HEAPID_DIGFOSSIL);
/*	REND_OAMInit(
			0, 128,		// ���C�����OAM�Ǘ��̈�
			0, 32,		// ���C����ʃA�t�B���Ǘ��̈�
			0, 128,		// �T�u���OAM�Ǘ��̈�
			0, 32,		// �T�u��ʃA�t�B���Ǘ��̈�
			HEAPID_DIGFOSSIL); */
    char_pltt_manager_init();
	// �Z���A�N�^�[������
	_pCommFossilWork->clactSet = CLACT_U_SetEasyInit( 26, &_pCommFossilWork->renddata, HEAPID_DIGFOSSIL );

    CLACT_U_SetSubSurfaceMatrix( &_pCommFossilWork->renddata, SUB_SURFACE_X, SUB_SURFACE_Y*2 );
    
	//���\�[�X�}�l�[�W���[������
	for(i = 0; i < 4; i++){		//���\�[�X�}�l�[�W���[�쐬
		_pCommFossilWork->resMan[i] = CLACT_U_ResManagerInit(CLACT_OBJ_NUM, i, HEAPID_DIGFOSSIL);
	}
    _setResObjTbl(
        CLACT_U_ResManagerResAddArcChar(_pCommFossilWork->resMan[CLACT_U_CHAR_RES], 
                                        ARC_UG_ANIM_GRA, NARC_ug_anim_kaseki_obj_NCGR,
                                        0, _CLACT_HUMMER, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_DIGFOSSIL));
	// Chara�]��
	CLACT_U_CharManagerSet( _pCommFossilWork->resObjTbl[_pCommFossilWork->resObjCount-1] );
    _setResObjTbl(
        CLACT_U_ResManagerResAddArcPltt(_pCommFossilWork->resMan[CLACT_U_PLTT_RES],
                                        ARC_UG_ANIM_GRA, NARC_ug_anim_kaseki_obj_NCLR,
                                        0, _CLACT_HUMMER, NNS_G2D_VRAM_TYPE_2DMAIN, 1, HEAPID_DIGFOSSIL));
	// �p���b�g�]��
	CLACT_U_PlttManagerSetCleanArea( _pCommFossilWork->resObjTbl[_pCommFossilWork->resObjCount-1] );
	_setResObjTbl(
        CLACT_U_ResManagerResAddArcKindCell(_pCommFossilWork->resMan[CLACT_U_CELL_RES],
                                            ARC_UG_ANIM_GRA, NARC_ug_anim_kaseki_obj_NCER,
                                            0, _CLACT_HUMMER, CLACT_U_CELL_RES,HEAPID_DIGFOSSIL));
    _setResObjTbl(
        CLACT_U_ResManagerResAddArcKindCell(_pCommFossilWork->resMan[CLACT_U_CELLANM_RES],
                                            ARC_UG_ANIM_GRA, NARC_ug_anim_kaseki_obj_NANR,
                                            0, _CLACT_HUMMER, CLACT_U_CELLANM_RES,HEAPID_DIGFOSSIL));
    _setResObjTbl(
        CLACT_U_ResManagerResAddArcChar(_pCommFossilWork->resMan[CLACT_U_CHAR_RES], 
                                        ARC_UG_ANIM_GRA, NARC_ug_anim_kaseki_hibi_NCGR, 0, _CLACT_HIBI, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_DIGFOSSIL));
	// Chara�]��
	CLACT_U_CharManagerSet( _pCommFossilWork->resObjTbl[_pCommFossilWork->resObjCount-1] );
    _setResObjTbl(
        CLACT_U_ResManagerResAddArcPltt(_pCommFossilWork->resMan[CLACT_U_PLTT_RES],
                                        ARC_UG_FOSSIL_GRA, NARC_ug_fossil_kaseki_board_NCLR, 0, _CLACT_HIBI, NNS_G2D_VRAM_TYPE_2DMAIN, 3, HEAPID_DIGFOSSIL));
	// �p���b�g�]��
	CLACT_U_PlttManagerSetCleanArea( _pCommFossilWork->resObjTbl[_pCommFossilWork->resObjCount-1] );
    _setResObjTbl(
        CLACT_U_ResManagerResAddArcKindCell(_pCommFossilWork->resMan[CLACT_U_CELL_RES],
							ARC_UG_ANIM_GRA, NARC_ug_anim_kaseki_hibi_NCER, 0, _CLACT_HIBI, CLACT_U_CELL_RES,HEAPID_DIGFOSSIL));
    _setResObjTbl(
        CLACT_U_ResManagerResAddArcKindCell(_pCommFossilWork->resMan[CLACT_U_CELLANM_RES],
                                            ARC_UG_ANIM_GRA, NARC_ug_anim_kaseki_hibi_NANR, 0, _CLACT_HIBI, CLACT_U_CELLANM_RES,HEAPID_DIGFOSSIL));

}

//------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 * @param   none
 * @retval  none		
 */
//------------------------------------------------------------------
static void _setCellActor(void)
{
	// �Z���A�N�^�[�w�b�_�쐬
    int i,j;
    //�o�^���i�[
    CLACT_ADD add;

    for(i = 0; i < CLACT_OBJ_NUM;i++){
        CLACT_U_MakeHeader(&_pCommFossilWork->clActHeader_s[i],
                           i, i, i, i,
                           CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
                           0, 0,
                           _pCommFossilWork->resMan[CLACT_U_CHAR_RES],
                           _pCommFossilWork->resMan[CLACT_U_PLTT_RES],
                           _pCommFossilWork->resMan[CLACT_U_CELL_RES],
                           _pCommFossilWork->resMan[CLACT_U_CELLANM_RES],
                           NULL,NULL);
		add.ClActSet	= _pCommFossilWork->clactSet;
		add.ClActHeader	= &_pCommFossilWork->clActHeader_s[i];

		add.mat.x		= FX32_CONST(32) ;
		add.mat.y		= FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���iMAIN����ASUB�����j
		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 0;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_DIGFOSSIL;

		//�Z���A�N�^�[�\���J�n

		// ���ʗp
        add.mat.x = FX32_ONE * 0;
        add.mat.y = FX32_ONE * 240;
        if(i == _CLACT_HUMMER){
            for(j = _CLACT_EFFECT;j <= _CLACT_KIRA_P3; j++){
                _pCommFossilWork->clActWork[ j ] = CLACT_Add(&add);
                CLACT_SetAnmFlag(_pCommFossilWork->clActWork[ j ],1);
            }
        }
        _pCommFossilWork->clActWork[i] = CLACT_Add(&add);
        CLACT_SetAnmFlag(_pCommFossilWork->clActWork[i],1);
	}
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_ON);	//OBJ�ʂn�m
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
	
}

//** CharManager PlttManager�p **//
#define _CHAR_CONT_NUM				(20)
#define _CHAR_VRAMTRANS_MAIN_SIZE		(2048*2)
#define _CHAR_VRAMTRANS_SUB_SIZE		(2048*2)
#define _PLTT_CONT_NUM				(20)


//-------------------------------------
//
//	�L�����N�^�}�l�[�W���[
//	�p���b�g�}�l�[�W���[�̏�����
//
//=====================================
static void char_pltt_manager_init(void)
{
	// �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			_CHAR_CONT_NUM,
			_CHAR_VRAMTRANS_MAIN_SIZE,
			_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_DIGFOSSIL
		};
		InitCharManagerReg(&cm, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_128K );
	}
    // �p���b�g�}�l�[�W���[������
	InitPlttManager(_PLTT_CONT_NUM, HEAPID_DIGFOSSIL);

	// �ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();
	//�ʐM�A�C�R���p�ɃL�������p���b�g����
	CLACT_U_WmIcon_SetReserveAreaCharManager(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
	CLACT_U_WmIcon_SetReserveAreaPlttManager(NNS_G2D_VRAM_TYPE_2DMAIN);
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�pVBLANK�֐�
 * @param	work
 */
//------------------------------------------------------------------
static void vBlankFunc(void * work)
{
	GF_BGL_INI * bgl = work;

    _shakeProcessVBlank(bgl);
	// BG��������
	GF_BGL_VBlankFunc( bgl );

	// Vram�]���}�l�[�W���[���s
	DoVramTransferManager();

	// �����_�����LOAM�}�l�[�W��Vram�]��
	REND_OAMTrans();	
}


//------------------------------------------------------------------
/**
 * @brief	���΂����邩�ǂ������ׂ�
 * @param   ���ׂ������W��X���W
   @param   ���ׂ������W��Z���W
 * @retval  ���������ǂ���
 */
//------------------------------------------------------------------
BOOL UGFossileCheck(int x,int z)
{
    if(_searchFossilPoint(x,z)){
        return TRUE;
    }
    return FALSE;
}


int UgFossilGetIntervalRadarPointX(int index)
{
    if(_pCommFossilWork){
        return _pCommFossilWork->pcRadarInter[index].xpos;
    }
    return 0;
}

int UgFossilGetIntervalRadarPointZ(int index)
{
    if(_pCommFossilWork){
        return _pCommFossilWork->pcRadarInter[index].zpos;
    }
    return 0;
}


#define _DTIME  (1)  // ���[�_�[�𑁂�������ׂ̊Ԋu

//--------------------------------------------------------------
/**
 * ���[�_�[�p���΂̈ʒuX���W�𓾂�
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

int UgFossilGetRadarPointX(int index)
{
    if(_pCommFossilWork && _pCommFossilWork->pPcRadarWork){
        int a = _pCommFossilWork->pPcRadarWork->pcRadarTimer;
        a = (a + index) % (_FOSSIL_NUM_MAX/3);
        return _pCommFossilWork->pPcRadarWork->pcRadar[a].xpos;
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * ���[�_�[�p���΂̈ʒuZ���W�𓾂�
 * @param    index
 * @retval   Z���W
 */
//--------------------------------------------------------------

int UgFossilGetRadarPointZ(int index)
{
    if(_pCommFossilWork && _pCommFossilWork->pPcRadarWork){
        int a = _pCommFossilWork->pPcRadarWork->pcRadarTimer;
        a = (a + index) % (_FOSSIL_NUM_MAX/3);
        return _pCommFossilWork->pPcRadarWork->pcRadar[a].zpos;
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * �p�\�R�����[�_�[�N���C�A���g�^�X�N
 * @param    tcb   tcb
 * @param    work   _EVENT_PCRADAR_WORK
 * @retval   none
 */
//--------------------------------------------------------------

static void _GMEVENT_PcRadar(TCB_PTR tcb, void *work)
{
    _EVENT_PCRADAR_WORK* pWork = work;

    pWork->pcRadarTimer++;
    if((_FOSSIL_NUM_MAX/3) < pWork->pcRadarTimer){
        Snd_SePlay(UG_SE_RADAR_ECHO);
        pWork->pcRadarTimer=0;
    }
}

//--------------------------------------------------------------
/**
 * �p�\�R�����[�_�[�X�^�[�g
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgFossilPcRadarStart(void)
{
    _EVENT_PCRADAR_WORK* mdw;
    GF_ASSERT_RETURN(!_pCommFossilWork->pPcRadarWork,);  // ��d�N���֎~
    GF_ASSERT_RETURN(!_pCommFossilWork->pPcRadar,);

    mdw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(_EVENT_PCRADAR_WORK));
    MI_CpuFill8(mdw, 0, sizeof(_EVENT_PCRADAR_WORK));
    CommSendFixData(CF_DIG_FOSSIL_PCRADAR);  // �T�[�o�[�ɍ��W���˗�
    mdw->pcRadarTimer = _FOSSIL_NUM_MAX/3-10; // �����x�点�ċN��
    _pCommFossilWork->pPcRadarWork = mdw;
    _pCommFossilWork->pPcRadar = TCB_Add(_GMEVENT_PcRadar , mdw,TCB_PRIORITY_NORMAL);

    
}

//--------------------------------------------------------------
/**
 * �p�\�R�����[�_�[�G���h
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgFossilPcRadarEnd(void)
{
    if(_pCommFossilWork->pPcRadar){
        TCB_Delete(_pCommFossilWork->pPcRadar);
        sys_FreeMemoryEz(_pCommFossilWork->pPcRadarWork);
        _pCommFossilWork->pPcRadar = NULL;
        _pCommFossilWork->pPcRadarWork = NULL;
    }
}

//--------------------------------------------------------------
/**
 * �p�\�R�����牻�΃��[�_�[�̖₢���킹������ CF_DIG_FOSSIL_PCRADAR
 * @param    index
 * @retval   Z���W
 */
//--------------------------------------------------------------

void UgFossilRecvPcRadar(int netID, int size, void* pData, void* pWork)
{
    if(_pCommFossilWork->radarIndex[netID] == 0){
        _pCommFossilWork->radarIndex[netID] = 1;
    }
}

//--------------------------------------------------------------
/**
 * ���΃��[�_�[�𑗐M����
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static void _pcRadarFunc(void)
{
    int i,sendNo = 0;

    
    for(i = 0;i < COMM_MACHINE_MAX;i++){
        int index = _pCommFossilWork->radarIndex[i] - 1;
        if(_pCommFossilWork->radarIndex[i]){
            while(1){
                FossilPoint* pFos = &_pCommFossilWork->aFossilPoint[index];
                if((pFos->xpos != COMM_UG_INVALID_GRID) && (pFos->zpos != COMM_UG_INVALID_GRID)){
                    _RESULT_RADAR tr;
                    tr.xpos = pFos->xpos;
                    tr.zpos = pFos->zpos;
                    tr.netID = i;
                    CommSendFixSizeData_ServerSide(CF_DIG_FOSSIL_PCRADAR_ANS, &tr);
                    _pCommFossilWork->radarIndex[i] = index + 3;
                    break;
                }
                index++;
                index++;
                index++;
                if(index >= _FOSSIL_NUM_MAX){
                    _pCommFossilWork->radarIndex[i] = 0; // ���M�I��
                    break;
                }
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * �T�[�o��������㩍��W�𑗂�Ԃ��Ă��炤 CF_DIG_FOSSIL_PCRADAR_ANS
 * @param    pData   _RESULT_TRAP_RADAR
 * @retval   none
 */
//--------------------------------------------------------------

void UgFossilRecvPcRadarPos(int netID, int size, void* pData, void* pWork)
{
    _RESULT_RADAR* pTr = pData;
    int index,id;

    if(_pCommFossilWork==NULL){
        return;
    }
    id = pTr->netID & 0x0f;
    if(_pCommFossilWork->pPcRadarWork==NULL){
        if(CommGetCurrentID() == id){
            index = (pTr->netID>>4) & 0x0f;
            if((index > 0) && (index <= 8)){
                MI_CpuCopy8(pData, &_pCommFossilWork->pcRadarInter[index-1],
                            sizeof(_RESULT_RADAR));
            }
        }
    }
    else{
        if(id == CommGetCurrentID()){
            MI_CpuCopy8(pData,&_pCommFossilWork->pPcRadarWork->pcRadar[_pCommFossilWork->pPcRadarWork->pcRadarIndex],
                        sizeof(_RESULT_RADAR));
            _pCommFossilWork->pPcRadarWork->pcRadarIndex++;
            if(_pCommFossilWork->pPcRadarWork->pcRadarIndex >= _FOSSIL_NUM_MAX){
                _pCommFossilWork->pPcRadarWork->pcRadarIndex=0;
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * �T�[�o��������㩍��W�𑗂�Ԃ��Ă��炤���̃T�C�Y
 * @param    none
 * @retval   _RESULT_TRAP_RADAR�̂�����
 */
//--------------------------------------------------------------

int UgFossilGetPcRadarSize(void)
{
    return sizeof(_RESULT_RADAR);
}

//==============================================================================
/**
 * �e�@���̃v���O����
 *    �ړ���~��Ԃ̏ꍇ ���Έʒu���T���T�O���b�h�������_���ŕԂ�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _turnAroundSignalSend(void)
{
    FossilPoint* pFos;
    int i,num;

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        if(!CommIsConnect(i)){
            continue;
        }
        if(CommPlayerGetWalkCount(i)){
            _pCommFossilWork->radarIntervalTimer[i] = 0;
            continue;
        }
        if(_pCommFossilWork->radarIntervalTimer[i] >= 28){
            continue;
        }
        _pCommFossilWork->radarIntervalTimer[i]++;
        if(_pCommFossilWork->radarIntervalTimer[i] < 20){
            continue;
        }
        num = _searchFossilRadarPoint(CommPlayerGetPosSX(i), CommPlayerGetPosSZ(i));
        if(num != -1){
            pFos = &_pCommFossilWork->aFossilPoint[num];
            if((pFos->xpos != COMM_UG_INVALID_GRID) && (pFos->zpos != COMM_UG_INVALID_GRID)){
                _RESULT_RADAR tr;
                tr.netID = i + ((_pCommFossilWork->radarIntervalTimer[i] - 20 + 1) << 4);
                tr.xpos = pFos->xpos;
                tr.zpos = pFos->zpos;
                CommSendFixSizeData_ServerSide(CF_DIG_FOSSIL_PCRADAR_ANS, &tr);
            }
        }
    }
}



//==============================================================================
/**
 * ����log���b�Z�[�W��Ԃ�
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

BOOL UgDigFossilGetActionMessage(STRBUF* pStrBuf)
{
    int i;
    MYSTATUS* pMy;
    MYSTATUS* pTarget;

    if(!_pCommFossilWork){
        return FALSE;
    }
    for(i = 0; i< COMM_MACHINE_MAX; i++){
        if(_pCommFossilWork->logMsgFossil[i]){
            pMy = CommInfoGetMyStatus(i);
            _pCommFossilWork->logMsgFossil[i] = FALSE;
            if(UgMgrRadarLogSingle(pMy, 0, UGFinishFossil, pStrBuf)){
                return TRUE;
            }
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �@���Ă邩�ǂ���
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

BOOL UgDigFossilIsDig(int netID)
{
    if(_pCommFossilWork){
        return _pCommFossilWork->bEntryFossil[netID];
    }
    return FALSE;
}

//==============================================================================
/**
 * ���E�����q�@�̕ϐ������Z�b�g
 * @param   netID  ID
 * @retval  none
 */
//==============================================================================

void UgDigFossilResetPlayer(int netID)
{
    if(_pCommFossilWork){
        _pCommFossilWork->bEntryFossil[netID]=FALSE;
    }
}

//==============================================================================
/**
 * �q�@���牻�Ό@���Ă��邱�Ƃ��ʒm
 * @param   netID  ID
 * @retval  none
 */
//==============================================================================
/*
void CommFossilRecvInit(int netID, int size, void* pData, void* pWork)
{
    OHNO_PRINT("���܂������ق��Ă܂� ��M\n");
    if(_pCommFossilWork){
        _pCommFossilWork->bEntryFossil[netID] = TRUE;
        OHNO_PRINT("���܂������ق��Ă܂� ��M%d\n",netID);
    }
}
*/
//==============================================================================
/**
 * 
 * @param   netID  ID
 * @retval  none
 */
//==============================================================================
/*
void UgDigFossilPlayerInit(void)
{
    if(_pCommFossilWork){
        if(_pCommFossilWork->pDFETCB){
            OHNO_PRINT("���܂������ق��Ă܂� ��������%d\n",(u32)_pCommFossilWork);
            CommSendFixData(CF_DIG_FOSSIL_INIT);
        }
    }
}
*/
//==============================================================================
/**
 * �����΂��@���Ă��邩�ǂ��� �N���C�A���g���
 * @param   netID  ID
 * @retval  none
 */
//==============================================================================

BOOL UgDigFossilIsNow(void)
{
    if(_pCommFossilWork){
        if(_pCommFossilWork->pDFETCB){
            OHNO_PRINT("���܂������ق��Ă܂� \n");
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �����΂��@���Ă��邩�ǂ��� �T�[�o�[��ԂƂ��ĕۑ�
 * @param   netID  ID
 * @retval  none
 */
//==============================================================================

void UgDigFossilSetNow(int netID, int bDig)
{
    if(_pCommFossilWork){
        _pCommFossilWork->bEntryFossil[netID] = bDig;
    }
}


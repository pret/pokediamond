//=============================================================================
/**
 * @file	ug_trap.c
 * @brief	�n����㩏���ۑ�����N���X
 * @author	Katsumi Ohno
 * @date    2005.09.28
 */
//=============================================================================


#include <nitro/os.h>
#include "common.h"
#include "../map_tool.h"
#include "../floor_touch.h"

#include "communication/communication.h"
#include "ug_manager.h"

#include "system/gamedata.h"
#include "system/pm_str.h"
#include "system/snd_tool.h"
#include "system/wordset.h"
#include "system/wipe.h"
#include "msgdata/msg_underworld.h"

#include "../field_effect.h"
#include "system/arc_util.h"
#include "system/clact_util.h"
#include "system/render_oam.h"
#include "ug_trap.naix"

#include "system/snd_tool.h"

#include "system/brightness.h"
#include "../tv_topic.h"
#include "../syswork.h"

#include "ug_trap_balance.h"

//==============================================================================
// ��`
//==============================================================================

#define _TRAP_NUM_NATURE   (TRAP_NUM_SINGLE_MAX*4)   ///< �V�R���̃g���b�v
#define _TRAP_ID_NATURE  (COMM_MACHINE_MAX)  // �V�R�g���b�v�̓}�V���ԍ��ȍ~�ɂ���
#define _EVWIN_MSG_BUF_SIZE		(50*2)			//���b�Z�[�W�o�b�t�@�T�C�Y

#define _TRAP_NUM_SINGLE_MAX (TRAP_NUM_SINGLE_MAX)       ///< ��l�̏ꍇ�̃g���b�v�ő吔
#define _TRAP_NUM_MAX (_TRAP_NUM_SINGLE_MAX * COMM_MACHINE_MAX + _TRAP_NUM_NATURE )  ///< �g���b�v�ő吔
#define _TRAP_TYEP_INVALID (0)    ///< �s���ȃg���b�v�^�C�v
#define _TRAP_INDEX_INVALID (-1)    ///< �s���ȃg���b�v�C���f�b�N�X

#define _TRAP_TOPIC_NUM (10)  ///< �P�O�ȏ��TV����

enum _result_e {
    _RESULT_NONE,
    _RESULT_OK,
    _RESULT_OK2,
    _RESULT_NG,
    _RESULT_SECRETBASE,
    _RESULT_PEOPLE,
    _RESULT_HIT_ATTR,
    _RESULT_NONE_PLACE,
};

enum _trapInfo_e {
    _TRAP_INFO_NONE,
    _TRAP_INFO_START,
    _TRAP_INFO_END
};

#define _RESULT_CMD_SIZE (2) // 㩃f�[�^����M�̌��ʂ�Ԃ����̃f�[�^�o�C�g��
#define _INTERVAL_OBJ_MAX  (12)  // ����I��㩂�\������
#define _INTERVAL_TRAPDISP  (12)  // 㩕\������
#define _TOUCH_OBJ_MAX (8)  //Touch�������ɕ\������㩂̌��E��

#define _TRAP_START_PAUSE_TIME  (30)  // 㩂ɂ������Ă����ɒ�~���鎞��

#define _RADAR_TRAP_MAX (16)

#define _TRAPTYPE_MAX  (32)    //���i�^�C�v��MAX
#define _MODEL_TRANS_PRI (10)  // ���f���̃e�N�X�`���[�̓]���^�X�NPRI

//#define _MIC_BLOW_VOL (100)
#define _MSG_TIME (60)

// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐�
#define CLACT_RESOURCE_NUM		(  4 )
#define _CLACT_ROCK_OAMNUM             (15)   // ��ʂɏo��ROCK��OAM��
#define _CLACT_FIRE_OAMNUM             (1)   // ��ʂɏo��FIRE��OAM��
#define _CLACT_TOUCHRADAR_OAMNUM      (25)
#define _CLACT_OAMNUM             (_CLACT_BLOSSOMS_OAMNUM)   // ��ʂɏo��OAM��  MAX
#define TOUCH_RES  (1)
#define MAIN_RES  (0)

#define EOA_HOLE_NO (_TRAPTYPE_MAX)  // ���Ȃ̊G�̔ԍ�

//#define BOTH_LCD  (2)


#define _BLOW_FRAME   (40)   // �Ԃт�t���[������
#define _TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL   (_FIRST_FLASH_LEVEL)   // �Ԃт�̕��ŏ��̃t�F�[�h���x�� -16�Ő^����
#define _TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV   (_TRAP_DARK_LEVEL)   // �Ԃт�̕��t�F�[�h���x�� -16�Ő^����

typedef void (*PTRStateFunc)(GF_BGL_INI* bgl);

//==============================================================================
//	�^�錾
//==============================================================================

// 㩂̍\���̃f�[�^
typedef struct{
    u16 xpos;
    u16 zpos;
    u8 trapType;
    u8 order;  // ��������
} TrapInfo;


typedef struct{
    TrapInfo trap;
    u8 assailantNetID;
    u8 victimNetID:4;
    u8 dir:2;
    u8 message:1;
    u8 bGoodsTrap:1;
} _HitTrap;

typedef struct{
    TrapInfo trap;
    u8 netID;
    u8 result;
} _TrapResult;

typedef struct{
    u16 xpos;
    u16 zpos;
    u8 netID;
} _RESULT_TRAP_RADAR;

typedef struct{
    int index;
    int distance;
} _TouchScan;

typedef struct{
    fx32 xpos;
    fx32 zpos;
} GridFX32;

//-------------------------------------
//	3D���f��
//=====================================
typedef struct {
    void*					pResMdl;		// ���f���ް�
    NNSG3dResMdlSet*		pModelSet;		// ���f���Z�b�g
    NNSG3dResMdl*			pModel;			// ���f�����\�[�X
    NNSG3dResTex*			pMdlTex;		// ���f���ɓ\��t����e�N�X�`��
} _3DOBJ_MDL;


typedef struct{
    _RESULT_TRAP_RADAR pcRadar[_TRAP_NUM_SINGLE_MAX + _TRAP_NUM_NATURE]; // �p�\�R�����[�_�[�p
    u8 pcRadarIndex;  //�p�\�R�����[�_�[��M�p
    u16 pcRadarTimer;  //�p�\�R�����[�_�[�\���p
} _EVENT_PCRADAR_WORK;

typedef struct{
    int seq;
    int timer;
    int netID;
    int type;
} _EVENT_TURNDISP_WORK;

// 㩑S��
typedef struct{
    _EVENT_TURNDISP_WORK*  turnWork[COMM_MACHINE_MAX];
    TCB_PTR turnTask[COMM_MACHINE_MAX];
    FIELDSYS_WORK* pFSys;
    CLACT_SET_PTR 			clactSet;								// �Z���A�N�^�[�Z�b�g
    CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
    CLACT_U_RES_MANAGER_PTR	resMan[2][CLACT_RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
    CLACT_U_RES_OBJ_PTR 	resObjTbl[2][CLACT_RESOURCE_NUM];// ���\�[�X�I�u�W�F�e�[�u��
    CLACT_HEADER			clActHeader_m;							// �Z���A�N�^�[�w�b�_�[
    CLACT_HEADER			clActHeader_s;							// �Z���A�N�^�[�w�b�_�[
    CLACT_WORK_PTR			clActWork[_CLACT_OAMNUM];				// �Z���A�N�^�[���[�N�|�C���^�z��
    CLACT_WORK_PTR			SubLCDIconActWork[4];
    GMEVENT_CONTROL* pTouchEvent;  // �^�b�`�Ɋւ��ẴC�x���g�Ǘ�
//    GMEVENT_CONTROL* pEvent;  // 㩂̒��g���C�x���g�Ǘ�
    TCB_PTR pRadar;
    TCB_PTR pTchRadar;
    TCB_PTR pPcRadar;
    _EVENT_PCRADAR_WORK* pPcRadarWork;
    void* pTCBWork;   // �C�x���g�ł͑g�߂Ȃ��ړ��n�̊Ǘ�
    PTRStateFunc trapProc;   // 㩎��s�֐��i�N���C�A���g���j
    TrapInfo myTrapData[_TRAP_NUM_SINGLE_MAX];  //�������g�̃g���b�v�f�[�^
    EOA_PTR myTrapPic[_TRAP_NUM_SINGLE_MAX];
    TrapInfo trapData[_TRAP_NUM_MAX];
    TrapInfo* pTrapTbl[_TRAP_NUM_MAX];  // �����̂��߂̃e�[�u��
    _HitTrap hitTrap[COMM_MACHINE_MAX];
    u8 logResque[COMM_MACHINE_MAX];
    u16 radarTrapIndex[COMM_MACHINE_MAX];   // ���[�_�[�p�C���f�b�N�X
    u8 msgTrapEnd[COMM_MACHINE_MAX];    //msg�p㩏I���
    u8 msgMsgTrap[COMM_MACHINE_MAX];  //msg�p ���b�Z�[�W�g���b�v
    u8 msgTrapDefuse[COMM_MACHINE_MAX];  //msg�p 㩉���
    u16 myTrapDefuseNum;
    u8 myTrapDefuseType;
    u16 oldCell;
    s8 mic;  // �}�C�N
    u8 nowTrapType;   // �����쒆�̃g���b�v�^�C�v
    u8 nowTrapTypeServer[COMM_MACHINE_MAX];   // �����쒆�̃g���b�v�^�C�v
    u8 touchIntervalDownTimer;
    u8 result;  // �f�[�^������ꂽ����1�A�G���[�ł�2�ɂȂ�
    u8 bHalt;    // �@�\��~��
} CommTrapWork;


typedef struct{
    int seq;
    int index;
    u16 turntime[_CLACT_OAMNUM];  // ���鎞��
    Grid oamGrid[_CLACT_OAMNUM];
    u8 blowRing[_BLOW_FRAME];   // 30�t���[���ŊO�~
    u8 blowPos[_CLACT_OAMNUM];  // �t���ς���~���Ă��鎞�ɂ��̈ʒu���L�� �x�[�X���C�����炱�̈ʒu�ɑ�LV�˂�����
    u8 blowBase;   // �C���N�������g�����̂�
    u8 timer;
    u8 dir;
    u8 bGoodsTrap;
    u8 num;
    int msgTimer;
    FIELDSYS_WORK* pFSys;
} _EVENT_DIRTYBLOSSOMS_WORK;

#define _ROCK_PATTERN_NUM (7)

typedef struct{
    int seq;
    int index;
    int partsX[_CLACT_ROCK_OAMNUM];
    int partsY[_CLACT_ROCK_OAMNUM];
    int partsXAdd[_CLACT_ROCK_OAMNUM];
    int partsYAdd[_CLACT_ROCK_OAMNUM];
    CLACT_U_RES_OBJ_PTR rockCharRes[_ROCK_PATTERN_NUM];
    EOA_PTR eoaShadow;
    int damage;
    int yAdd;
    int yPos;
    u8 timer;
    u8 subSeq;
    u8 dir;
    u8 bGoodsTrap;
    int msgTimer;
    int rot;
} _EVENT_ROCK_WORK;


typedef struct{
    int seq;
    int index;
    int scale;
    int timer;
    u8 dir;
    u8 bGoodsTrap;
    u8 subSeq;
} _EVENT_MESSAGE_WORK;

typedef struct{
    int seq;
    int index;
    u8 mic[_MIC_SAMPLE_NUM];
    int micCount;
    GridFX32 oamGrid[_CLACT_FIRE_OAMNUM];
    int scale;
    int timer;
    u8 subSeq;
    u8 dir;
    u8 bGoodsTrap;
    int msgTimer;
} _EVENT_FIRE_WORK;

typedef struct{
    int seq;
    int index;
    u8 size[_CLACT_BUBBLE_OAMNUM];
    u16 dirIdx[_CLACT_BUBBLE_OAMNUM];
    GridFX32 oamGrid[_CLACT_BUBBLE_OAMNUM];
    BOOL bEnd[_CLACT_BUBBLE_OAMNUM];
    u16 scaletime[_CLACT_BUBBLE_OAMNUM];  // ���鎞��
    u8 timer;
    u8 dir;
    u8 bGoodsTrap;
    int msgTimer;
} _EVENT_BUBBLE_WORK;


typedef struct{
    int seq;
    int index;
    u8* pTouchBuff[3];
    int touchSize[3];
    int touchXpos;
    int touchZpos;
    int scrXpos;
    int scrZpos;
    int timer;
} _EVENT_TOUCHRADAR_WORK;

typedef struct{
    int seq;
    int index;
    BOOL bRev;
    u8 bGoodsTrap;
    int startTime;
} _EVENT_GIDDY_WORK;


typedef struct{
    int seq;
    int index;
    BOOL bBig;
    u8 dir;
    u8 bGoodsTrap;
    int startTime;
    EOA_PTR eoa;  // ����
    int dispDir;
    int timer;
    int msgTimer;
} _EVENT_HOLE_WORK;

typedef struct{
    int seq;
    int index;
    u16 oldXpos;
    u16 oldZpos;
    int timer;
    GF_BGL_INI* bgl;
    FIELDSYS_WORK* pFSys;
    u8 dir;
    u8 bGoodsTrap;
    int msgTimer;
} _EVENT_SMOG_WORK;


typedef struct{
    int seq;
    int index;
    FIELDSYS_WORK* pFSys;
    int victimNetID;
    int dir;
    int timer;
    BOOL bBig;
} _EVENT_DIR_WORK;


// �V���O���g��
static CommTrapWork* _pCTW = NULL;

//==============================================================================
// static�錾
//==============================================================================

static void _myTrapAdd(TrapInfo* pTrap);
static int _getTrapNetID(TrapInfo* pTrap);
static TrapInfo* _addTrap(int x, int y, TrapInfo* pTrapTbl, int trapType);
static void _delTrapTbls(int netID);

static void _turnAroundSignalSend(void);

static TrapInfo* _checkTrap(int x, int z);

static EOA_PTR _trapPictAdd(int x, int z, int scale,int type);

static void _touchRadarInitialize(void);
static void _touchRadarFinalize(void);
static void _intervalTrapPictAdd(int x, int z, int type);
//static void _touchTrapPictAdd(int x, int z, int index);
static void _trapPictWrite( void );
static void _trapPictDel( int index );
static void _myTrapDel(TrapInfo* pTrap);
static void _trapRecvNatureRadarFunc(void);


static void _trapServerStart(int victimNetID, int trapType);
static void _trapServerExit(int victimNetID, int trapType);
static void _startServerReverse(int victimNetID);
static void _startServerGiddy(int victimNetID);
static void _startServerSmog(int victimNetID);
static void _startServerDirtyBlossoms(int victimNetID);
static void _startServerBigDirRight(int victimNetID);
static void _startServerBigDirLeft(int victimNetID);
static void _startServerBigDirUp(int victimNetID);
static void _startServerBigDirDown(int victimNetID);
static void _startServerDirRight(int victimNetID);
static void _startServerDirLeft(int victimNetID);
static void _startServerDirUp(int victimNetID);
static void _startServerDirDown(int victimNetID);
static void _startServerDir(int victimNetID);
static void _startServerDrill(int victimNetID);

static void _endClientDir(int netID,BOOL bGoodsTrap);
static void _forceEndClientDir(int netID, BOOL bGoods);
static void _trapClientStart(int victimNetID, int trapType, BOOL bGoodsTrap,int dir);
static void _startClientReverse(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientGiddy(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientSmog(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientBigDirRight(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientBigDirLeft(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientBigDirUp(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientBigDirDown(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientDirRight(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientDirLeft(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientDirUp(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientDirDown(int victimNetID, BOOL bGoodsTrap,int dir);
static void _startClientDrill(int victimNetID,BOOL bGoodsTrap,int dir);
static void _startClientDirtyBlossoms(int victimNetID,BOOL bGoodsTrap,int dir);
//static int _getLastOrder(TrapInfo* pTrapTbl);

static void _endClientSmog(int victimNetID,BOOL bGoodsTrap);
static void _endClientForceDirtyBlossoms(int victimNetID,BOOL bGoodsTrap);
static void _endClientGiddy(int netID,BOOL bGoods);
static void _forceEndClientGiddy(int netID,BOOL bGoods);

static TrapInfo* _getOldOrderData(TrapInfo* pTrapTbl);
static void _resetOrderNo(TrapInfo* pTrapTbl);

static void _trapDirStart(FIELDSYS_WORK* pFSys, int victimNetID, int dir, BOOL bBig);
static void _trapSmogInitialize(FIELDSYS_WORK* pFSys, BOOL bGoodsTrap, int dir);
static BOOL _trapSmogTouch(Grid* pGrid, GF_BGL_INI * bgl,_EVENT_SMOG_WORK* wk);
static BOOL _commTrapSmogDelete(int xpos, int zpos, u8* pScrAddr);
static void _procSmog(TCB_PTR tcb, void *work);
static void _smogTouchNone(_EVENT_SMOG_WORK* wk);

static void _trapGiddyInitialize(BOOL bRev);

static void _dirtyBlossomsInitialize(FIELDSYS_WORK* pFSys, BOOL bGoodsTrap,int dir);
static BOOL _procDirtyBlossoms(GF_BGL_INI * bgl,_EVENT_DIRTYBLOSSOMS_WORK * mdw);
static void _dartyBlossomsStart(int x,int y);

static void _initCellActor(void);
static void _endCellActor(int oamNum);
static void _setCellActor(int num);




static void _bubbleAddPetal(_EVENT_BUBBLE_WORK* mdw);
static void _GMEVENT_Bubble(TCB_PTR tcb, void *work);
static void _bubbleInitialize(GF_BGL_INI * bgl,BOOL bGoodsTrap,int dir);
static void _setCellActorBubble(_EVENT_BUBBLE_WORK* mdw);
static void _bubblePos(int index, _EVENT_BUBBLE_WORK* mdw);
static BOOL _procBubble(GF_BGL_INI * bgl, _EVENT_BUBBLE_WORK* mdw);
static void _startClientBubble(int victimNetID,BOOL bGoods,int dir);
static void _startServerBubble(int victimNetID);
//static void _endClientBubble(int victimNetID,BOOL bGoods);
static void _endForceClientBubble(int victimNetID,BOOL bGoods);

static void _exitServerDir(int victimNetID);
static void _exitServerGiddy(int victimNetID);


static void _endForceClientHole(int netID,BOOL bGoods);
static void _priEndClientHole(int victimNetID);
static void _endClientHole(int netID,BOOL bGoods);
static void _startClientBigHole(int victimNetID,BOOL bGoods,int dir);
static void _startClientHole(int victimNetID,BOOL bGoods,int dir);
static void _exitServerHole(int victimNetID);
static void _startServerBigHole(int victimNetID);
static void _startServerHole(int victimNetID);


static void _startClientRock(int victimNetID,BOOL bGoods,int dir);
static void _endClientRock(int victimNetID,BOOL bGoods);
static void _startServerRock(int victimNetID);
static void _startClientFire(int victimNetID,BOOL bGoods,int dir);
static void _endClientFire(int victimNetID,BOOL bGoods);
static void _startServerFire(int victimNetID);
static void _startClientMessage(int victimNetID,BOOL bGoods,int dir);
static void _endClientMessage(int victimNetID,BOOL bGoods);
static void _startServerMessage(int victimNetID);

static void UgTrapTurnDispStart(int netID,int type);
static void _turnTaskAllDelete(void);

typedef void (*ClientTrapEndFunc)(int victimNetID,BOOL bGoods);
typedef void (*ClientTrapFunc)(int victimNetID,BOOL bGoods,int dir);
typedef void (*ServerTrapFunc)(int victimNetID);

#ifdef PM_DEBUG
static void DEBUG_TrapTBLPrint(char* msg);
#endif

static const ClientTrapEndFunc _clientTrapExit[] = {
    NULL,                    //UG_TRAPTYPE_NONE = 0,
    _endClientDir,       //UG_TRAPTYPE_DIR_UP,
    _endClientDir,    //UG_TRAPTYPE_DIR_RIGHT,
    _endClientDir,     //UG_TRAPTYPE_DIR_DOWN,
    _endClientDir,     //UG_TRAPTYPE_DIR_LEFT,
    _endClientDir,    //UG_TRAPTYPE_BIGDIR_UP,
    _endClientDir,  //UG_TRAPTYPE_BIGDIR_DOWN,
    _endClientDir,  //UG_TRAPTYPE_BIGDIR_LEFT,
    _endClientDir, //UG_TRAPTYPE_BIGDIR_RIGHT,
    NULL,                    //UG_TRAPTYPE_WARP,
    NULL,                    //UG_TRAPTYPE_TELEPORT,
    _endClientHole,                    //UG_TRAPTYPE_HOLE,
    _endClientHole,                    //UG_TRAPTYPE_BIG_HOLE,
    _endClientGiddy,                    //UG_TRAPTYPE_REVERSE,
    _endClientGiddy,       //UG_TRAPTYPE_GIDDY,
    NULL,                    //UG_TRAPTYPE_RUNNING,
    NULL,                    //UG_TRAPTYPE_INVISIBLE,
    NULL,                    //UG_TRAPTYPE_SLOW,
    _endClientSmog,        //UG_TRAPTYPE_SMOG,
    _endClientSmog,        //UG_TRAPTYPE_BIG_SMOG,
    _endClientRock,           //UG_TRAPTYPE_ROCK,
    _endClientRock,           //UG_TRAPTYPE_RACKFALL,
    _endForceClientBubble,                    //UG_TRAPTYPE_SUDS
    _endForceClientBubble,                    //UG_TRAPTYPE_BUBBLE,
    _endClientMessage,                    //UG_TRAPTYPE_PARALYZE,
    _endClientMessage,                    //UG_TRAPTYPE_ELECTROMAGNETIC_WAVE,
    _endClientMessage,                    //UG_TRAPTYPE_ALARM,
    _endClientMessage,                    //UG_TRAPTYPE_SIREN,
    _endClientForceDirtyBlossoms,                    //UG_TRAPTYPE_LEAF,
    _endClientForceDirtyBlossoms,                    //UG_TRAPTYPE_DIRTY_BLOSSOMS,
    _endClientFire,                    //UG_TRAPTYPE_FIRE,
    _endClientFire,                    //UG_TRAPTYPE_BLAZE,
    NULL,                    //UG_TRAPTYPE_RADAR,
    NULL,        //UG_TRAPTYPE_DRILL,
    NULL,                    //UG_TRAPTYPE_MAX,
};



static const ClientTrapEndFunc _clientTrapForceExit[] = {
    NULL,                    //UG_TRAPTYPE_NONE = 0,
    _forceEndClientDir,       //UG_TRAPTYPE_DIR_UP,
    _forceEndClientDir,    //UG_TRAPTYPE_DIR_RIGHT,
    _forceEndClientDir,     //UG_TRAPTYPE_DIR_DOWN,
    _forceEndClientDir,     //UG_TRAPTYPE_DIR_LEFT,
    _forceEndClientDir,    //UG_TRAPTYPE_BIGDIR_UP,
    _forceEndClientDir,  //UG_TRAPTYPE_BIGDIR_DOWN,
    _forceEndClientDir,  //UG_TRAPTYPE_BIGDIR_LEFT,
    _forceEndClientDir, //UG_TRAPTYPE_BIGDIR_RIGHT,
    NULL,                    //UG_TRAPTYPE_WARP,
    NULL,                    //UG_TRAPTYPE_TELEPORT,
    _endForceClientHole,                    //UG_TRAPTYPE_HOLE,
    _endForceClientHole,                    //UG_TRAPTYPE_BIG_HOLE,
    _forceEndClientGiddy,                    //UG_TRAPTYPE_REVERSE,
    _forceEndClientGiddy,       //UG_TRAPTYPE_GIDDY,
    NULL,                    //UG_TRAPTYPE_RUNNING,
    NULL,                    //UG_TRAPTYPE_INVISIBLE,
    NULL,                    //UG_TRAPTYPE_SLOW,
    _endClientSmog,        //UG_TRAPTYPE_SMOG,
    _endClientSmog,        //UG_TRAPTYPE_BIG_SMOG,
    _endClientRock,           //UG_TRAPTYPE_ROCK,
    _endClientRock,           //UG_TRAPTYPE_RACKFALL,
    _endForceClientBubble,                    //UG_TRAPTYPE_SUDS
    _endForceClientBubble,                    //UG_TRAPTYPE_BUBBLE,
    _endClientMessage,                    //UG_TRAPTYPE_PARALYZE,
    _endClientMessage,                    //UG_TRAPTYPE_ELECTROMAGNETIC_WAVE,
    _endClientMessage,                    //UG_TRAPTYPE_ALARM,
    _endClientMessage,                    //UG_TRAPTYPE_SIREN,
    _endClientForceDirtyBlossoms,                    //UG_TRAPTYPE_LEAF,
    _endClientForceDirtyBlossoms,                    //UG_TRAPTYPE_DIRTY_BLOSSOMS,
    _endClientFire,                    //UG_TRAPTYPE_FIRE,
    _endClientFire,                    //UG_TRAPTYPE_BLAZE,
    NULL,                    //UG_TRAPTYPE_RADAR,
    NULL,        //UG_TRAPTYPE_DRILL,
    NULL,                    //UG_TRAPTYPE_MAX,
};


static const ClientTrapFunc _clientTrapFunc[] = {
    NULL,                    //UG_TRAPTYPE_NONE = 0,
    _startClientDirUp,       //UG_TRAPTYPE_DIR_UP,
    _startClientDirRight,    //UG_TRAPTYPE_DIR_RIGHT,
    _startClientDirDown,     //UG_TRAPTYPE_DIR_DOWN,
    _startClientDirLeft,     //UG_TRAPTYPE_DIR_LEFT,
    _startClientBigDirUp,    //UG_TRAPTYPE_BIGDIR_UP,
    _startClientBigDirRight, //UG_TRAPTYPE_BIGDIR_RIGHT,
    _startClientBigDirDown,  //UG_TRAPTYPE_BIGDIR_DOWN,
    _startClientBigDirLeft,  //UG_TRAPTYPE_BIGDIR_LEFT,
    NULL,                    //UG_TRAPTYPE_WARP,
    NULL,                    //UG_TRAPTYPE_TELEPORT,
    _startClientHole,        //UG_TRAPTYPE_HOLE,
    _startClientBigHole,     //UG_TRAPTYPE_BIG_HOLE,
    _startClientReverse,     //UG_TRAPTYPE_REVERSE,
    _startClientGiddy,       //UG_TRAPTYPE_GIDDY,
    NULL,                    //UG_TRAPTYPE_RUNNING,
    NULL,                    //UG_TRAPTYPE_INVISIBLE,
    NULL,                    //UG_TRAPTYPE_SLOW,
    _startClientSmog,        //UG_TRAPTYPE_SMOG,
    _startClientSmog,        //UG_TRAPTYPE_BIG_SMOG,
    _startClientRock,        //UG_TRAPTYPE_ROCK,
    _startClientRock,        //UG_TRAPTYPE_RACKFALL,
    _startClientBubble,                    //UG_TRAPTYPE_SUDS
    _startClientBubble,      //UG_TRAPTYPE_BUBBLE,
    _startClientMessage,                    //UG_TRAPTYPE_PARALYZE,
    _startClientMessage,                    //UG_TRAPTYPE_ELECTROMAGNETIC_WAVE,
    _startClientMessage,                    //UG_TRAPTYPE_ALARM,
    _startClientMessage,                    //UG_TRAPTYPE_SIREN,
    _startClientDirtyBlossoms,                    //UG_TRAPTYPE_LEAF,
    _startClientDirtyBlossoms, //UG_TRAPTYPE_DIRTY_BLOSSOMS,
    _startClientFire,                    //UG_TRAPTYPE_FIRE,
    _startClientFire,                    //UG_TRAPTYPE_BLAZE,
    NULL,                    //UG_TRAPTYPE_RADAR,
    _startClientDrill,        //UG_TRAPTYPE_DRILL,
    NULL,                    //UG_TRAPTYPE_MAX,
};

static const ServerTrapFunc _serverTrapFunc[] = {
    NULL,                    //UG_TRAPTYPE_NONE = 0,
    _startServerDir,       //UG_TRAPTYPE_DIR_UP,
    _startServerDir,    //UG_TRAPTYPE_DIR_RIGHT,
    _startServerDir,     //UG_TRAPTYPE_DIR_DOWN,
    _startServerDir,     //UG_TRAPTYPE_DIR_LEFT,
    _startServerDir,    //UG_TRAPTYPE_BIGDIR_UP,
    _startServerDir,  //UG_TRAPTYPE_BIGDIR_DOWN,
    _startServerDir,  //UG_TRAPTYPE_BIGDIR_LEFT,
    _startServerDir, //UG_TRAPTYPE_BIGDIR_RIGHT,
    NULL,                    //UG_TRAPTYPE_WARP,
    NULL,                    //UG_TRAPTYPE_TELEPORT,
    _startServerHole,                    //UG_TRAPTYPE_HOLE,
    _startServerBigHole,                    //UG_TRAPTYPE_BIG_HOLE,
    _startServerReverse,                    //UG_TRAPTYPE_REVERSE,
    _startServerGiddy,       //UG_TRAPTYPE_GIDDY,
    NULL,                    //UG_TRAPTYPE_RUNNING,
    NULL,                    //UG_TRAPTYPE_INVISIBLE,
    NULL,                    //UG_TRAPTYPE_SLOW,
    _startServerSmog,        //UG_TRAPTYPE_SMOG,
    _startServerSmog,        //UG_TRAPTYPE_BIG_SMOG,
    _startServerRock,        //UG_TRAPTYPE_ROCK,
    _startServerRock,        //UG_TRAPTYPE_RACKFALL,
    _startServerBubble,                    //UG_TRAPTYPE_SUDS
    _startServerBubble,      //UG_TRAPTYPE_BUBBLE,
    _startServerMessage,                    //UG_TRAPTYPE_PARALYZE,
    _startServerMessage,                    //UG_TRAPTYPE_ELECTROMAGNETIC_WAVE,
    _startServerMessage,                    //UG_TRAPTYPE_ALARM,
    _startServerMessage,                    //UG_TRAPTYPE_SIREN,
    _startServerDirtyBlossoms,                    //UG_TRAPTYPE_LEAF,
    _startServerDirtyBlossoms,                    //UG_TRAPTYPE_DIRTY_BLOSSOMS,
    _startServerFire,                    //UG_TRAPTYPE_FIRE,
    _startServerFire,                    //UG_TRAPTYPE_BLAZE,
    NULL,                    //UG_TRAPTYPE_RADAR,
    _startServerDrill,       //UG_TRAPTYPE_DRILL,
    NULL,                    //UG_TRAPTYPE_MAX,
};

static const ServerTrapFunc _serverTrapSecondFunc[] = {
    NULL,                    //UG_TRAPTYPE_NONE = 0,
    _startServerDirUp,       //UG_TRAPTYPE_DIR_UP,
    _startServerDirRight,    //UG_TRAPTYPE_DIR_RIGHT,
    _startServerDirDown,     //UG_TRAPTYPE_DIR_DOWN,
    _startServerDirLeft,     //UG_TRAPTYPE_DIR_LEFT,
    _startServerBigDirUp,    //UG_TRAPTYPE_BIGDIR_UP,
    _startServerBigDirRight, //UG_TRAPTYPE_BIGDIR_RIGHT,
    _startServerBigDirDown,  //UG_TRAPTYPE_BIGDIR_DOWN,
    _startServerBigDirLeft,  //UG_TRAPTYPE_BIGDIR_LEFT,
    NULL,                    //UG_TRAPTYPE_WARP,
    NULL,                    //UG_TRAPTYPE_TELEPORT,
    NULL,                    //UG_TRAPTYPE_HOLE,
    NULL,                    //UG_TRAPTYPE_BIG_HOLE,
    NULL,                    //UG_TRAPTYPE_REVERSE,
    NULL,       //UG_TRAPTYPE_GIDDY,
    NULL,                    //UG_TRAPTYPE_RUNNING,
    NULL,                    //UG_TRAPTYPE_INVISIBLE,
    NULL,                    //UG_TRAPTYPE_SLOW,
    NULL,        //UG_TRAPTYPE_SMOG,
    NULL,        //UG_TRAPTYPE_BIG_SMOG,
    NULL,                    //UG_TRAPTYPE_ROCK,
    NULL,                    //UG_TRAPTYPE_RACKFALL,
    NULL,                    //UG_TRAPTYPE_SUDS
    NULL,      //UG_TRAPTYPE_BUBBLE,
    NULL,                    //UG_TRAPTYPE_PARALYZE,
    NULL,                    //UG_TRAPTYPE_ELECTROMAGNETIC_WAVE,
    NULL,                    //UG_TRAPTYPE_ALARM,
    NULL,                    //UG_TRAPTYPE_SIREN,
    NULL,                    //UG_TRAPTYPE_LEAF,
    NULL,                    //UG_TRAPTYPE_DIRTY_BLOSSOMS,
    NULL,                    //UG_TRAPTYPE_FIRE,
    NULL,                    //UG_TRAPTYPE_BLAZE,
    NULL,                    //UG_TRAPTYPE_RADAR,
    NULL,       //UG_TRAPTYPE_DRILL,
    NULL,                    //UG_TRAPTYPE_MAX,
};

static const ServerTrapFunc _serverTrapExit[] = {
    NULL,                    //UG_TRAPTYPE_NONE = 0,
    _exitServerDir,          //UG_TRAPTYPE_DIR_UP,
    _exitServerDir,          //UG_TRAPTYPE_DIR_DOWN,
    _exitServerDir,          //UG_TRAPTYPE_DIR_LEFT,
    _exitServerDir,          //UG_TRAPTYPE_DIR_RIGHT,
    _exitServerDir,          //UG_TRAPTYPE_BIGDIR_UP,
    _exitServerDir,          //UG_TRAPTYPE_BIGDIR_DOWN,
    _exitServerDir,          //UG_TRAPTYPE_BIGDIR_LEFT,
    _exitServerDir,          //UG_TRAPTYPE_BIGDIR_RIGHT,
    NULL,                    //UG_TRAPTYPE_WARP,
    NULL,                    //UG_TRAPTYPE_TELEPORT,
    _exitServerHole,                    //UG_TRAPTYPE_HOLE,
    _exitServerHole,                    //UG_TRAPTYPE_BIG_HOLE,
    _exitServerGiddy,        //UG_TRAPTYPE_REVERSE,
    _exitServerGiddy,        //UG_TRAPTYPE_GIDDY,
    NULL,                    //UG_TRAPTYPE_RUNNING,
    NULL,                    //UG_TRAPTYPE_INVISIBLE,
    NULL,                    //UG_TRAPTYPE_SLOW,
    NULL,        //UG_TRAPTYPE_SMOG,
    NULL,        //UG_TRAPTYPE_BIG_SMOG,
    NULL,                    //UG_TRAPTYPE_ROCK,
    NULL,                    //UG_TRAPTYPE_RACKFALL,
    NULL,                    //UG_TRAPTYPE_SUDS
    NULL,      //UG_TRAPTYPE_BUBBLE,
    NULL,                    //UG_TRAPTYPE_PARALYZE,
    NULL,                    //UG_TRAPTYPE_ELECTROMAGNETIC_WAVE,
    NULL,                    //UG_TRAPTYPE_ALARM,
    NULL,                    //UG_TRAPTYPE_SIREN,
    NULL,                    //UG_TRAPTYPE_LEAF,
    NULL,                    //UG_TRAPTYPE_DIRTY_BLOSSOMS,
    NULL,                    //UG_TRAPTYPE_FIRE,
    NULL,                    //UG_TRAPTYPE_BLAZE,
    NULL,                    //UG_TRAPTYPE_RADAR,
    NULL,       //UG_TRAPTYPE_DRILL,
    NULL,                    //UG_TRAPTYPE_MAX,
};


//==============================================================================
// ���[�N
//==============================================================================

//==============================================================================
// �֐�
//==============================================================================



static void _myTrapInit(void)
{
    int i;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCTW->pFSys));

    for(i = 0; i < _TRAP_NUM_SINGLE_MAX; i++){
        _pCTW->myTrapData[i].trapType = UnderGroundGetTrapGroundItemType(pUGData,i);
        _pCTW->myTrapData[i].xpos = UnderGroundGetTrapGroundItemX(pUGData,i);
        _pCTW->myTrapData[i].zpos = UnderGroundGetTrapGroundItemZ(pUGData,i);
        _pCTW->myTrapData[i].order = UnderGroundGetTrapGroundItemOrder(pUGData,i);
        if(!_pCTW->bHalt){
            if(_pCTW->myTrapData[i].trapType != UG_TRAPTYPE_NONE){
                _pCTW->myTrapPic[i] = _trapPictAdd(_pCTW->myTrapData[i].xpos, _pCTW->myTrapData[i].zpos, 1,_pCTW->myTrapData[i].trapType); //�G��\��
            }
        }
    }
}


//==============================================================================
/**
 * �g���b�v��񏉊���
 * @param   ���[�N�|�C���^
 * @param   �t�B�[���h�V�X�e���̃|�C���^
 * @retval  none
 */
//==============================================================================

void CommTrapInfoInitialize(void* pWork, FIELDSYS_WORK* pFSys)
{
    int i;
    UNDERGROUNDDATA* pUGData;

    if(_pCTW){  // ���̂Ƃ��뉽�x�������������̂�
        return;
    }
    _pCTW = (CommTrapWork*)pWork;
    MI_CpuFill8(_pCTW,0,sizeof(CommTrapWork));

    _pCTW->pFSys = pFSys;

    pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pFSys));

    _pCTW->pRadar = NULL;
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        _pCTW->logResque[i] = INVALID_NETID;
    }
    pFSys->TpTo3DPtr = FTouch_AllocUnderGroundTP(pFSys->camera_ptr);
    _touchRadarInitialize();

    _myTrapInit();
}

//==============================================================================
/**
 * �g���b�v���Z�b�g ��ʂ��؂�ւ��ۂɊG�̏���S�Ď̂Ă�K�v������
 *   �ʐM���̂͊J�����Ȃ�
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommTrapInfoReset(void)
{
    int i;
    FTouch_FreeUnderGroundTP(&(_pCTW->pFSys->TpTo3DPtr));
    _touchRadarFinalize();
    _turnTaskAllDelete();

    for(i = 0; i < _TRAP_NUM_SINGLE_MAX; i++){
        if(_pCTW->myTrapPic[i]){
            _pCTW->myTrapPic[i] = NULL;
        }
    }
    if(_pCTW->pRadar){
        TCB_Delete(_pCTW->pRadar);
        _pCTW->pRadar = NULL;
    }
    if(_pCTW->pTCBWork){
        sys_FreeMemoryEz(_pCTW->pTCBWork);
        _pCTW->pTCBWork = NULL;
    }

    _pCTW->bHalt = TRUE;
}

//==============================================================================
/**
 * �g���b�v���u�[�g �G�̏��𕜋A����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommTrapInfoReboot(void)
{
    int i;

    _pCTW->pFSys->TpTo3DPtr = FTouch_AllocUnderGroundTP(_pCTW->pFSys->camera_ptr);
    _pCTW->bHalt = FALSE;

    _myTrapInit();
    _touchRadarInitialize();
}

//==============================================================================
/**
 * �g���b�v���J��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommTrapInfoFinalize(void)
{
    int i;

    for(i = 0; i < _TRAP_NUM_SINGLE_MAX; i++){
        if(_pCTW->myTrapPic[i]){
            EOA_Delete(_pCTW->myTrapPic[i]);
            _pCTW->myTrapPic[i] = NULL;
        }
    }
    _turnTaskAllDelete();
    _touchRadarFinalize();
    FTouch_FreeUnderGroundTP(&(_pCTW->pFSys->TpTo3DPtr));

    if(_pCTW->myTrapDefuseNum >= _TRAP_TOPIC_NUM ){
        TVTOPIC_Entry_Record_RemoveTrap(_pCTW->pFSys,_pCTW->myTrapDefuseType, _pCTW->myTrapDefuseNum);
    }
    if(_pCTW->pRadar){
        TCB_Delete(_pCTW->pRadar);
    }
    if(_pCTW->pTCBWork){
        sys_FreeMemoryEz(_pCTW->pTCBWork);
    }
    sys_FreeMemoryEz(_pCTW);
    _pCTW=NULL;
}

//==============================================================================
/**
 * �g���b�v���ēx������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommTrapInfoReInit(FIELDSYS_WORK* pFSys)
{
    int i;
    UNDERGROUNDDATA* pUGData;

    for(i = 0; i < _TRAP_NUM_SINGLE_MAX; i++){
        if(_pCTW->myTrapPic[i]){
            EOA_Delete(_pCTW->myTrapPic[i]);
            _pCTW->myTrapPic[i] = NULL;
        }
    }
    _turnTaskAllDelete();
    _myTrapInit();

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        _pCTW->nowTrapTypeServer[i] = _TRAP_TYEP_INVALID;
    }

    MI_CpuFill8(_pCTW->trapData, 0, sizeof(_pCTW->trapData));
    MI_CpuFill8(_pCTW->pTrapTbl, 0, sizeof(_pCTW->pTrapTbl));
    UgTrapNatureReload();
}

//==============================================================================
/**
 * �������l�̃g���b�v��������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommTrapDeletePlayer_Server(int netID)
{
    TrapInfo* pTrap = &_pCTW->trapData[netID * _TRAP_NUM_SINGLE_MAX];
    int i;

    for(i = 0; i< _TRAP_NUM_SINGLE_MAX; i++){  // �������Ă�����̂�����
        pTrap->trapType = _TRAP_TYEP_INVALID;
        pTrap++;
    }
    _delTrapTbls(netID);

    if(_pCTW->nowTrapTypeServer[netID] != _TRAP_TYEP_INVALID){
        CommPlayerResetCondition(netID);
        _trapServerExit(netID,_pCTW->nowTrapTypeServer[netID]);
        _pCTW->nowTrapTypeServer[netID] = _TRAP_TYEP_INVALID;
    }
}


//==============================================================================
/**
 * �^�b�`���[�_�[�̑f�ޏ�����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _touchRadarInitialize(void)
{
    int i;
    //���\�[�X�}�l�[�W���[������
    for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
        _pCTW->resMan[TOUCH_RES][i] = CLACT_U_ResManagerInit(1, i, HEAPID_FIELD);
    }

    _pCTW->resObjTbl[TOUCH_RES][CLACT_U_CHAR_RES] =
        CLACT_U_ResManagerResAddArcChar(_pCTW->resMan[TOUCH_RES][CLACT_U_CHAR_RES],
                                        ARC_UG_TRAP_GRA, NARC_ug_trap_touchcircle_NCGR,
                                        0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD);
    _pCTW->resObjTbl[TOUCH_RES][CLACT_U_PLTT_RES] =
        CLACT_U_ResManagerResAddArcPltt(_pCTW->resMan[TOUCH_RES][CLACT_U_PLTT_RES],
                                        ARC_UG_TRAP_GRA, NARC_ug_trap_touchcircle_NCLR,
                                        0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAPID_FIELD);
    _pCTW->resObjTbl[TOUCH_RES][CLACT_U_CELL_RES] =
        CLACT_U_ResManagerResAddArcKindCell(_pCTW->resMan[TOUCH_RES][CLACT_U_CELL_RES],
                                            ARC_UG_TRAP_GRA, NARC_ug_trap_touchcircle_NCER,
                                            0, 0, CLACT_U_CELL_RES,HEAPID_FIELD);
    _pCTW->resObjTbl[TOUCH_RES][CLACT_U_CELLANM_RES] =
        CLACT_U_ResManagerResAddArcKindCell(_pCTW->resMan[TOUCH_RES][CLACT_U_CELLANM_RES],
                                            ARC_UG_TRAP_GRA, NARC_ug_trap_touchcircle_NANR,
                                            0, 0, CLACT_U_CELLANM_RES,HEAPID_FIELD);
}

//==============================================================================
/**
 * �^�b�`���[�_�[�̑f�ފJ��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _touchRadarFinalize()
{
    int i;


    // �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
    for(i=0;i < CLACT_RESOURCE_NUM ; i++){
        CLACT_U_ResManagerDelete(_pCTW->resMan[TOUCH_RES][i]);
    }

}


//--------------------------------------------------------------
/**
 * @brief   ���b�Z�[�W�������\�������ꍇ�̏I�����R�[���o�b�N
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
static void _msgEndCallBack(int num)
{
    CommPlayerHoldEnd();
}

//==============================================================================
/**
 * �g���b�v���Ǘ��p�f�[�^�T�C�Y��Ԃ�
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

int CommTrapInfoGetWorkSize(void)
{
    return sizeof(CommTrapWork);
}

//==============================================================================
/**
 * �ʐM�p㩃f�[�^�T�C�Y��Ԃ�
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

int CommTrapInfoGetTrapDataSize(void)
{
    return sizeof(TrapInfo)*_TRAP_NUM_SINGLE_MAX;
}

//==============================================================================
/**
 * �e�[�u����ɂ���㩂̈ʒu��Ԃ�
 * @param   pGrid  �Ԃ��ʒu
 * @param   index  ��������index
 * @retval  none�T�C�Y
 */
//==============================================================================

static Grid* _getTrapTblPos(Grid* pGrid, int index)
{
    if(_pCTW->pTrapTbl[index]==NULL){
        return NULL;
    }
    pGrid->xpos = _pCTW->pTrapTbl[index]->xpos;
    pGrid->zpos = _pCTW->pTrapTbl[index]->zpos;
    return pGrid;
}

//==============================================================================
/**
 * �e�[�u����㩂�}������
 * @param   pGrid  �Ԃ��ʒu
 * @param   index  ��������index
 * @retval  none�T�C�Y
 */
//==============================================================================

static void _insertTrapTbl(TrapInfo* pTrap)
{
    int ins,j,i;
    TrapInfo* pBigTrap;
    Grid grid;

    grid.xpos = pTrap->xpos;
    grid.zpos = pTrap->zpos;
    CommUnderItemSearchInitialize(_TRAP_NUM_MAX, _getTrapTblPos);
    ins = CommUnderSearchItemTbl(&grid);

    if(ins >= _TRAP_NUM_MAX){
        return;
    }


    for(i = 0; i < _TRAP_NUM_MAX;i++){
        if(_pCTW->pTrapTbl[i] == pTrap){ // ���łɂ�����
            return;
        }
    }
    for(j = _TRAP_NUM_MAX - 2; j >= ins; j--){
        _pCTW->pTrapTbl[j+1] = _pCTW->pTrapTbl[j];
    }
    /*    memmove(&_pCTW->pTrapTbl[ins+1],
            &_pCTW->pTrapTbl[ins],
            (_TRAP_NUM_MAX - ins - 1) * sizeof(u32)); */
    //OHNO_PRINT("�����̃e�[�u���ɍ������݂܂� %d  %x\n",ins,(int) pTrap);
    _pCTW->pTrapTbl[ins] = pTrap;
//    OHNO_PRINT("�����̃e�[�u���ɍ������݂܂� %d  %x\n",ins,(u32) pTrap);

#ifdef DEBUG_ONLY_FOR_ohno
    for(i = 0;i < _TRAP_NUM_MAX;i++){
        if(_pCTW->pTrapTbl[i]){
            if(_pCTW->pTrapTbl[i]->trapType != _TRAP_TYEP_INVALID){ // ���łɂ�����
                OHNO_SP_PRINT("tbl %d = %d %d \n", i,
                           _pCTW->pTrapTbl[i]->xpos,_pCTW->pTrapTbl[i]->zpos);
            }
        }
    }
#endif

    _pCTW->pTrapTbl[ins] = pTrap;

}


static void _delTrapTbl(TrapInfo* pTrap)
{
    int match = -1,j;
    Grid grid;

    for(j = 0; j < _TRAP_NUM_MAX; j++){
        if(_pCTW->pTrapTbl[j] == pTrap){
            match = j;
            break;
        }
    }
    if(match == -1){
        return;
    }
    for(j = match; j < _TRAP_NUM_MAX - 1; j++){
        _pCTW->pTrapTbl[j] = _pCTW->pTrapTbl[j+1];
    }
    _pCTW->pTrapTbl[_TRAP_NUM_MAX-1] = NULL;
}

static void _delTrapTbls(int netID)
{
    int match,j,i;
    Grid grid;

#ifdef PM_DEBUG
//    DEBUG_TrapTBLPrint("2");
#endif
    for(i = 0 ; i < _TRAP_NUM_SINGLE_MAX; i++){
        _delTrapTbl(&_pCTW->trapData[i+netID*_TRAP_NUM_SINGLE_MAX]);
    }
#ifdef PM_DEBUG
//    DEBUG_TrapTBLPrint("3");
#endif
    for(i = 0; i < _TRAP_NUM_SINGLE_MAX; i++){
        if(_pCTW->trapData[i+netID*_TRAP_NUM_SINGLE_MAX].trapType != _TRAP_TYEP_INVALID){
            _insertTrapTbl(&_pCTW->trapData[i+netID*_TRAP_NUM_SINGLE_MAX]);
        }
    }
#ifdef PM_DEBUG
//    DEBUG_TrapTBLPrint("4");
#endif
}


//==============================================================================
/**
 * �����Ă�㩃o�b�t�@��Ԃ�
 * @param   netID     ID
 * @retval  TrapInfo*
 */
//==============================================================================

static TrapInfo* _getFreeTrap( TrapInfo* pTrapTbl )
{
    int i;

    for(i = 0; i < _TRAP_NUM_SINGLE_MAX; i++){
        if(pTrapTbl->trapType == _TRAP_TYEP_INVALID){
            return pTrapTbl;
        }
        pTrapTbl++;
    }
    return NULL;
}

//==============================================================================
/**
 * �����Ă�㩃o�b�t�@index��Ԃ�
 * @param   netID     ID
 * @retval  TrapInfo*
 */
//==============================================================================

static int _getFreeTrapIndex( TrapInfo* pTrapTbl )
{
    int i;

    for(i = 0; i < _TRAP_NUM_SINGLE_MAX; i++){
        if(pTrapTbl->trapType == _TRAP_TYEP_INVALID){
            return i;
        }
        pTrapTbl++;
    }
    return -1;
}

//==============================================================================
/**
 * 㩂̏���
 * @param   TrapInfo* pTrap �
 * @retval  none
 */
//==============================================================================

static void _delTrap(TrapInfo* pTrap)
{
    int i;
    u32 baseAddr = (u32)&_pCTW->trapData[0];
    u32 nowTrap = (u32)pTrap;
    u32 trapNo = (nowTrap-baseAddr)/sizeof(TrapInfo);
    u32 id = trapNo / _TRAP_NUM_SINGLE_MAX;
    u32 trapMax = (id+1) * _TRAP_NUM_SINGLE_MAX;

    _pCTW->trapData[trapNo].trapType = _TRAP_TYEP_INVALID;
//    _delTrapTbls(id);

    for(i = trapNo ; i < (trapMax-1); i++){
        MI_CpuCopy8(&_pCTW->trapData[i+1],&_pCTW->trapData[i],sizeof(TrapInfo));
    }
    _pCTW->trapData[trapMax-1].trapType = _TRAP_TYEP_INVALID;

    _delTrapTbls(id);

    //   _resetOrderNo(&_pCTW->trapData[id]);
    //   OHNO_PRINT("㩂������܂��� id=%d no=%d\n", id,trapNo);
}

//==============================================================================
/**
 * 㩂�ǉ�����
 * @param   netID     ID
 * @param   trapIndex 㩔ԍ�
 * @retval  none
 */
//==============================================================================

static TrapInfo* _addTrap(int x, int y, TrapInfo* pTrapTbl, int trapType)
{
    int index = 0;
    TrapInfo* pFreeTrap;

    if(GetHitAttr(_pCTW->pFSys,x,y)){  // �����肪����ꍇ
        // �z�u�ł��Ȃ�
        return NULL;
    }
    pFreeTrap = _getFreeTrap(pTrapTbl); //netID);
    if(pFreeTrap == NULL){  // ���������ꍇ
        pTrapTbl = _getOldOrderData(pTrapTbl);
        _delTrap( pTrapTbl );
        pFreeTrap = _getFreeTrap(pTrapTbl); //netID);
    }
    pFreeTrap->xpos = x;
    pFreeTrap->zpos = y;
    pFreeTrap->trapType = trapType;
    _insertTrapTbl(pFreeTrap);
    // �������Ԃ𖄂ߍ���
//    pFreeTrap->order = _getLastOrder(pTrapTbl) + 1;
  //  _resetOrderNo(pTrapTbl);  // �ԍ��U��Ȃ���

    //    OHNO_PRINT("㩐ݒu %d %d\n",x,y);
    return pFreeTrap;
}

//==============================================================================
/**
 * 㩂�ǉ�����
 * @param   trapType 㩎��
 * @param   func     �ǉ����ɌĂ΂��R�[���o�b�N
 * @retval  none
 */
//==============================================================================

void CommTrapInfoAddTrap(u8 trapType)
{
    CommSendFixSizeData(CF_TRAP_DATA,&trapType);
}

//==============================================================================
/**
 *  ���t���[���s����������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommTrapInfoProcess(void)
{
    int i;

    _trapRecvNatureRadarFunc(); // �p�\�R������₢���킹�̂�����㩑��M

}

//==============================================================================
/**
 * �e�@���̃v���O����
     �ʒu�f�[�^���M�̍ۂ̃T�C�Y��Ԃ�
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

int CommTrapInfoGetTrapPosSize(void)
{
    return sizeof(TrapInfo);
}


// �q�@���̃v���O����

//==============================================================================
/**
 * �q�@���̃v���O����  �e�@��㩂𑗂�
 * @param   netID   �Ō�ɐڑ����Ă����q�@��ID
 * @retval  none
 */
//==============================================================================

void CommTrapInfoChildSendStart(void)
{
    int i;
    u8 num=0;

    /// �܂Ƃ߂đ��M����
    CommSetSendQueue(CF_TRAP_ARRAY_DATA,
                     &_pCTW->myTrapData[0] ,
                     sizeof(TrapInfo)*_TRAP_NUM_SINGLE_MAX);

}

//==============================================================================
/**
 * 㩂�ǉ�����R�}���h����M   CF_TRAP_DATA
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @retval  none
 */
//==============================================================================

void CommTrapInfoRecvTrapData(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = (u8*)pData;
    int gx,gy;
    TrapInfo* pFreeTrap;
    _TrapResult trapResult;

    if(_pCTW==NULL){
        return;
    }

    trapResult.netID = netID;
    trapResult.result = _RESULT_NG;
    gx = CommPlayerGetPosSXDirAdd(netID);
    gy = CommPlayerGetPosSZDirAdd(netID);

    //�����ɉ����Ȃ����Ƃ�����
    OHNO_PRINT("�����ɉ����Ȃ����Ƃ�����\n");

    if( (CommPlayerGetPosSX(netID) == COMM_PLAYER_INVALID_GRID) &&
        ( CommPlayerGetPosSZ(netID) == COMM_PLAYER_INVALID_GRID)){  // ���W�s��̏ꍇ
        trapResult.result = _RESULT_NONE_PLACE;
        CommSendData_ServerSide(CF_TRAP_DATA_RESULT,&trapResult,sizeof(_TrapResult));
        return;
    }
    
    if(COMM_INVALID_ID != CommPlayerIsAlive(gx,gy)){
        OHNO_PRINT("�ڂ̑O�ɐl������  %d %d %d\n", CommPlayerIsAlive(gx,gy),gx,gy);
        // ���ʂ�Ԃ�
        trapResult.result = _RESULT_PEOPLE;
        CommSendData_ServerSide(CF_TRAP_DATA_RESULT,&trapResult,sizeof(_TrapResult));
        return;
    }
    if(CommPlayerNPCHitCheck(gx, gy)){
        OHNO_PRINT("�ڂ̑O�ɐl������  %d %d %d\n", CommPlayerIsAlive(gx,gy),gx,gy);
        // ���ʂ�Ԃ�
        trapResult.result = _RESULT_PEOPLE;
        CommSendData_ServerSide(CF_TRAP_DATA_RESULT,&trapResult,sizeof(_TrapResult));
        return;
    }    
    if(UgSecretBaseIsSecretBasePlace(gx,gy)){
        trapResult.result = _RESULT_SECRETBASE;
        CommSendData_ServerSide(CF_TRAP_DATA_RESULT,&trapResult,sizeof(_TrapResult));
        return;
    }
    if(GetHitAttr(_pCTW->pFSys,gx,gy)){  // �����肪����ꍇ
        // �z�u�ł��Ȃ�
        trapResult.result = _RESULT_HIT_ATTR;
        CommSendData_ServerSide(CF_TRAP_DATA_RESULT,&trapResult,sizeof(_TrapResult));
        return;
    }
    if(FALSE == CommUnderCheckPlace(gx,gy)){
        pFreeTrap = _addTrap(gx, gy,
                             &_pCTW->trapData[netID*_TRAP_NUM_SINGLE_MAX], pBuff[0]);
        if(pFreeTrap){
            trapResult.result = _RESULT_OK;
            MI_CpuCopy8( pFreeTrap, &trapResult.trap, sizeof(TrapInfo));
        }
    }
    // ���ʂ�Ԃ�
    CommSendData_ServerSide(CF_TRAP_DATA_RESULT,&trapResult,sizeof(_TrapResult));
}

//==============================================================================
/**
 * 㩂�ǉ�����R�}���h�̌��ʃR�}���h�̃o�C�g����Ԃ�
 * @param   none
 * @retval  �o�C�g��
 */
//==============================================================================

int CommTrapInfoGetTrapDataResultSize(void)
{
    return sizeof(_TrapResult);
}


//==============================================================================
/**
 * �V�R��㩂�u��
 * @param   type
 * @retval  none
 */
//==============================================================================

int UgTrapAddNatureTrap(int gx,int gy,MATHRandContext16* pRand, int index)
{
    static const u8 tbl[] = {
        UG_TRAPTYPE_DIR_UP,
        UG_TRAPTYPE_DIR_RIGHT,
        UG_TRAPTYPE_DIR_DOWN,
        UG_TRAPTYPE_DIR_LEFT,
        UG_TRAPTYPE_BIGDIR_UP,
        UG_TRAPTYPE_BIGDIR_RIGHT,
        UG_TRAPTYPE_BIGDIR_DOWN,
        UG_TRAPTYPE_BIGDIR_LEFT,
        UG_TRAPTYPE_HOLE,
        UG_TRAPTYPE_BIG_HOLE,
        UG_TRAPTYPE_REVERSE,
        UG_TRAPTYPE_GIDDY,  // ����
        UG_TRAPTYPE_SMOG,  // ��ʂɖ�
        UG_TRAPTYPE_BIG_SMOG,  // ��ʂɖ�
        UG_TRAPTYPE_BUBBLE,
        UG_TRAPTYPE_DIRTY_BLOSSOMS,
        UG_TRAPTYPE_ALART1,
        UG_TRAPTYPE_ALART2,
        UG_TRAPTYPE_ALART3,
        UG_TRAPTYPE_ALART4,
        UG_TRAPTYPE_FIRE,
        UG_TRAPTYPE_BLAZE,
        UG_TRAPTYPE_ROCK,
        UG_TRAPTYPE_ROCKFALL,
        UG_TRAPTYPE_SUDS,
        UG_TRAPTYPE_LEAF,
    };

    u8 type;
    int netID,pos;
    TrapInfo* pFreeTrap;
    TrapInfo* pTrapTbl;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(_pCTW->pFSys->savedata);

    if(index >= UG_NATURETRAP_PLACE_NUM_MAX){
        return UG_TRAPTYPE_NONE;
    }

    netID = COMM_MACHINE_MAX + (index / _TRAP_NUM_SINGLE_MAX);
    pos = netID * _TRAP_NUM_SINGLE_MAX;
    pTrapTbl = &_pCTW->trapData[pos];

    type = MATH_Rand16(pRand, NELEMS(tbl));  //�ł��Ă�㩂��烉���_���I��
    type = tbl[type];

#if defined(DEBUG_ONLY_FOR_ohno) | defined(DEBUG_ONLY_FOR_mituhara)
    type = UG_TRAPTYPE_ALART4;
#endif    

    if(FALSE == CommUnderCheckPlace(gx,gy)){
        pFreeTrap = _getFreeTrap(pTrapTbl);
        if(pFreeTrap != NULL){
            TrapInfo* pTrap = _addTrap(gx, gy, pTrapTbl,type);
            if(pTrap){
                pTrap->order = index;
                // backup�ɕۑ�
                UnderGroundAddNatureTrapGroundItem(pUGData, type, index,
                                                   gx, gy);
                return type;
            }
        }
    }
    return UG_TRAPTYPE_NONE;
}

//==============================================================================
/**
 * �V�R��㩂��Ĕz�u����
 * @param   type
 * @retval  none
 */
//==============================================================================

void UgTrapNatureReload(void)
{

    int i;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(_pCTW->pFSys->savedata);

    for(i = 0; i < UG_NATURETRAP_PLACE_NUM_MAX; i++){
        int type = UnderGroundGetNatureTrapGroundItemType(pUGData, i);
        if(type != UG_TRAPTYPE_NONE){
            int xp = UnderGroundGetNatureTrapGroundItemX(pUGData, i);
            int zp = UnderGroundGetNatureTrapGroundItemZ(pUGData, i);
            int netID = COMM_MACHINE_MAX + i / _TRAP_NUM_SINGLE_MAX;
            int pos = netID * _TRAP_NUM_SINGLE_MAX;
            TrapInfo* pTrapTbl = &_pCTW->trapData[pos];
            TrapInfo* pTrap = _addTrap(xp, zp, pTrapTbl,type);
            if(pTrap){
                pTrap->order = i;
            }
        }
    }
}

//==============================================================================
/**
 * ������㩂��o�b�N�A�b�v����
 * @param   pTrap    㩃f�[�^
 * @retval  none
 */
//==============================================================================

static void _myTrapBackup(void)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCTW->pFSys));
    int i;
    for(i = 0; i < _TRAP_NUM_SINGLE_MAX; i++){
        UnderGroundAddTrapGroundItem( pUGData, _pCTW->myTrapData[i].trapType,i,
                                      _pCTW->myTrapData[i].xpos,
                                      _pCTW->myTrapData[i].zpos,
                                      _pCTW->myTrapData[i].order);
    }
}

//==============================================================================
/**
 * ������㩂�ǉ�����+�G���ǉ�����
 * @param   pTrap    㩃f�[�^
 * @retval  none
 */
//==============================================================================

static void _myTrapAdd(TrapInfo* pTrap)
{
    TrapInfo* pFreeTrap = _getFreeTrap(_pCTW->myTrapData);
    int index;

    if(pFreeTrap==NULL){
        pFreeTrap = _getOldOrderData(_pCTW->myTrapData);
        _myTrapDel(pFreeTrap);  // �Â��̂�����
        pFreeTrap = _getFreeTrap(_pCTW->myTrapData);
    }
    index = _getFreeTrapIndex(_pCTW->myTrapData);
    MI_CpuCopy8( pTrap, pFreeTrap, sizeof(TrapInfo));

    _myTrapBackup();
    _pCTW->myTrapPic[index] = _trapPictAdd(pFreeTrap->xpos, pFreeTrap->zpos, 1, pFreeTrap->trapType);
}

//==============================================================================
/**
 * ������㩂�����+�G������
 * @param   pTrap    㩃f�[�^
 * @retval  none
 */
//==============================================================================

static void _myTrapDel(TrapInfo* pTrap)
{
    TrapInfo* pFreeTrap;
    int index = -1,i;

    OHNO_PRINT("㩂����� %d %d \n", pTrap->xpos, pTrap->zpos);
    
    for(i = 0; i< _TRAP_NUM_SINGLE_MAX; i++){
        pFreeTrap = &_pCTW->myTrapData[i];
        if((pTrap->xpos == pFreeTrap->xpos) && (pTrap->zpos == pFreeTrap->zpos)){
            index = i;
            break;
        }
    }
    if(index == -1){
        return;
    }

    for(i = index ; i < (_TRAP_NUM_SINGLE_MAX-1); i++){
        MI_CpuCopy8(&_pCTW->myTrapData[i+1],&_pCTW->myTrapData[i],sizeof(TrapInfo));
    }
    _pCTW->myTrapData[_TRAP_NUM_SINGLE_MAX-1].trapType = _TRAP_TYEP_INVALID;

    if(_pCTW->myTrapPic[index]!=NULL){
        EOA_Delete(_pCTW->myTrapPic[index]);
    }
    for(i = index ; i < (_TRAP_NUM_SINGLE_MAX-1); i++){
        _pCTW->myTrapPic[i] = _pCTW->myTrapPic[i+1];
    }
    _pCTW->myTrapPic[_TRAP_NUM_SINGLE_MAX-1] = NULL;
}

//==============================================================================
/**
 * 㩂�ǉ�����R�}���h�̌��ʂ���M CF_TRAP_DATA_RESULT
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @retval  none
 */
//==============================================================================

void CommTrapInfoRecvTrapDataResult(int netID, int size, void* pData, void* pWork)
{
    _TrapResult* pTrapResult = (_TrapResult*)pData;
    int index;
    TrapInfo* pFreeTrap;

//    GF_ASSERT_RETURN((pTrapResult->netID < COMM_MACHINE_MAX),);
    if(CommGetCurrentID() == pTrapResult->netID){
        CommPlayerHold();
        if(pTrapResult->result == _RESULT_OK){
            // �T�[�o�[�̓����𓾂Ă��玩���̃o�b�t�@�Ɋi�[
            _myTrapAdd(&pTrapResult->trap);
            CommUnderBagDeleteTrap(pTrapResult->trap.trapType);
            CommMsgRegisterUGTrapName(CommUnderGetMsgUnderWorld(),pTrapResult->trap.trapType);
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), mes_uw_item_08, TRUE, _msgEndCallBack);
            Snd_SePlay(UG_SE_SMOKE);  // 㩐ݒu
        }
        else if(pTrapResult->result == _RESULT_SECRETBASE){
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_73, TRUE, _msgEndCallBack);
        }
        else if(pTrapResult->result == _RESULT_PEOPLE){
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_55, TRUE, _msgEndCallBack);
        }
        else if(pTrapResult->result == _RESULT_HIT_ATTR){
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_60, TRUE, _msgEndCallBack);
        }
        else if(pTrapResult->result == _RESULT_NONE_PLACE){
            _msgEndCallBack(0);  // ���W���܂������ꍇ�Ȃɂ����Ȃ�
        }
        else{
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_59, TRUE, _msgEndCallBack);
        }
    }
}

//==============================================================================
/**
 *  㩂���������R�}���h����M                CF_TRAP_DATA_DEL
 * @param   sendDSID        �����Ă���DS��ID
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @retval  none
 */
//==============================================================================

void CommTrapInfoRecvTrapDataDel(int netID, int size, void* pData, void* pWork)
{
    u16* pBuff = pData;
    int index = pBuff[0];

    _delTrap(&_pCTW->trapData[index]);

}

int CommTrapInfoGetTrapDataDelSize(void)
{
    return 2;
}

//==============================================================================
/**
 *  㩃f�[�^ARRAY DATA������   CF_TRAP_ARRAY_DATA
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @retval  none
 */
//==============================================================================

void CommTrapInfoRecvArrayData(int netID, int size, void* pData, void* pWork)
{
    u8 resultBuff[_RESULT_CMD_SIZE];
    TrapInfo* pTrap = &_pCTW->trapData[netID * _TRAP_NUM_SINGLE_MAX];
    int i;

    if(CommGetCurrentID() != COMM_PARENT_ID){
        return;
    }

    GF_ASSERT_RETURN(size == (sizeof(TrapInfo) * _TRAP_NUM_SINGLE_MAX),);
    // �f�[�^��M
    for(i = 0; i< _TRAP_NUM_SINGLE_MAX; i++){  // �������Ă�����̂�����
        pTrap->trapType = _TRAP_TYEP_INVALID;
        pTrap++;
    }
    pTrap = pData;  // �V�����o�^
    for(i = 0; i< _TRAP_NUM_SINGLE_MAX; i++){
        if(pTrap->trapType != _TRAP_TYEP_INVALID){
            _addTrap(pTrap->xpos, pTrap->zpos,
                     &_pCTW->trapData[netID * _TRAP_NUM_SINGLE_MAX],
                     pTrap->trapType);
        }
        pTrap++;
    }
    resultBuff[0] = netID;
    resultBuff[1] = _RESULT_OK;
    OHNO_PRINT("array�m�F�@�t���M\n");
    CommSendData_ServerSide(CF_TRAP_ARRAY_RESULT,resultBuff,_RESULT_CMD_SIZE);
    CommTrapSendTrapingArray();
}

//==============================================================================
/**
 *  �q�@��������㩏���e�ɑ��M�ł��������Ԃ��Ă��� CF_TRAP_ARRAY_RESULT
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommTrapInfoRecvResult(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = (u8*)pData;

    OHNO_PRINT("CommTrapInfoRecvResult %d %d\n",pBuff[0],pBuff[1]);
    if(_pCTW){
        if(CommGetCurrentID() == pBuff[0]){
            _pCTW->result = pBuff[1];
        }
    }
}

//==============================================================================
/**
 *  �q�@��������㩏���e�ɑ��M�ł���������Ԃ��R�}���h�̃T�C�Y
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

int CommTrapInfoGetResultSize(void)
{
    return _RESULT_CMD_SIZE;
}

//==============================================================================
/**
 *  ��������M�ł������ǂ���
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

BOOL CommTrapInfoIsParentRecv(void)
{
    return (_pCTW->result == _RESULT_OK);
}

//==============================================================================
/**
 *  ���ʂ����Z�b�g����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

void CommTrapInfoResetParentRecv(void)
{
    _pCTW->result = _RESULT_NONE;
}

//==============================================================================
/**
 *  �^�b�`�f�[�^�̑��M�T�C�Y��Ԃ�
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

int CommTrapInfoGetTouchSize(void)
{
    return sizeof(Grid);
}

//==============================================================================
/**
 *  㩂��ڂ̑O�ɂ��������������
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @retval  㩂������ĉ�������=TRUE
 */
//==============================================================================

BOOL CommTrapFrontTrapDefuse(int netID, Grid* pTouch, u8 bTrapFull)
{
    int x,z;
    u8 result = netID;
    TrapInfo* pTrap;
    _HitTrap hitTrap;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCTW->pFSys));

    x = CommPlayerGetPosSXDirAdd(netID);
    z = CommPlayerGetPosSZDirAdd(netID);

    pTrap = _checkTrap(x, z);
    if(pTrap){
        if(CommPlayerFlagDigCheck(netID)){   // �����̊�����
            return TRUE;
        }
        hitTrap.victimNetID = netID;                 // ���ꂪ���������̂�
        hitTrap.assailantNetID = _getTrapNetID(pTrap);  // ����̂�Ȃɂ���������
        MI_CpuCopy8(pTrap, &hitTrap.trap, sizeof(TrapInfo));
        if(bTrapFull & _NOTGET_TRAP_RESERVE){  // ���łɏE���Ȃ�
            hitTrap.message = 1;
        }
        else{
            hitTrap.message = 0;
            _delTrap(pTrap);  //㩂�����
        }
        if(hitTrap.assailantNetID >= _TRAP_ID_NATURE){ //�V�R��㩂̏ꍇ
            UnderGroundDelNatureTrapGroundItem(pUGData,hitTrap.trap.order);//�����ŏ�����
        }
        
        CommPlayerSetMoveControl_Server(netID,FALSE);
        CommSendData_ServerSide(CF_TRAP_DEFUSE, &hitTrap, sizeof(_HitTrap));
        return TRUE;
    }
    return FALSE;
}

int CommTrapInfoRecvTrapDefuseSize(void)
{
    return sizeof(_HitTrap);
}

//==============================================================================
/**
 *  㩉����������Ă���   CF_TRAP_DEFUSE
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @param   pWork    ���������ɓn�������[�N�|�C���^
 * @retval  none
 */
//==============================================================================

void CommTrapInfoRecvTrapDefuse(int netID, int size, void* pData, void* pWork)
{
    _HitTrap* pHitTrap = (_HitTrap*)pData;

    OHNO_PRINT("㩉���--\n");
    GF_ASSERT_RETURN(pHitTrap->victimNetID < COMM_MACHINE_MAX,);

    if(pHitTrap->message == 1){
        if(CommGetCurrentID() == pHitTrap->victimNetID){  // �E���Ȃ�
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_78, TRUE, _msgEndCallBack);
            CommPlayerHold();
        }
        return;
    }
    _pCTW->msgTrapDefuse[pHitTrap->victimNetID] = _RESULT_OK;  //LOG
    if(CommGetCurrentID() == pHitTrap->assailantNetID){ // �d�|�����l��㩂�����
        _myTrapDel(&pHitTrap->trap);
        _myTrapBackup();
    }
    if(CommGetCurrentID() == pHitTrap->victimNetID){  // �E�����l�͕\���{�o�b�O����
        if(CommUnderBagAddTrap(pHitTrap->trap.trapType)){   // ������
            if(CommGetCurrentID() != pHitTrap->assailantNetID){ // �d�|�����l�͎����łȂ�
                if(_pCTW->myTrapDefuseNum==0){
                    _pCTW->myTrapDefuseType = pHitTrap->trap.trapType;
                }
                if(_pCTW->myTrapDefuseNum != 0xffff){ //u16�Ȃ̂�
                    _pCTW->myTrapDefuseNum++;
                }
            }
            Snd_SePlay(UG_SE_FIND);
            CommMsgRegisterMyName(CommUnderGetMsgUnderWorld(),CommInfoGetMyStatus(pHitTrap->victimNetID));
            CommMsgRegisterUGTrapName(CommUnderGetMsgUnderWorld(),pHitTrap->trap.trapType);
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_19, TRUE, _msgEndCallBack);
            CommMsgTalkWindowMeWait(CommUnderGetMsgUnderWorld());  //ME�̏I���҂�ON
        }
        else{
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_78, TRUE, _msgEndCallBack);
        }
        CommPlayerHold();
    }
}

//==============================================================================
/**
 *  㩂�NETID���t�Ђ�����
 * @param   ���ׂ���pTrap
 * @retval  netID
 */
//==============================================================================

static int _getTrapNetID(TrapInfo* pTrap)
{
    int i;

    for(i = 0; i < _TRAP_NUM_MAX; i++){
        if( pTrap == &_pCTW->trapData[i]){
            return i / _TRAP_NUM_SINGLE_MAX;
        }
    }
    GF_ASSERT(0 && "�Ȃ�㩂���������");
    return 0;  // �����ɂ��Ă͂�������
}

//==============================================================================
/**
 *  㩂Ɉ��������������ǂ�����Ԃ�
 * @param   ���ׂ������W��X���W
   @param   ���ׂ������W��Z���W
 * @retval  �������������
 */
//==============================================================================

static TrapInfo* _checkTrap(int x, int z)
{
    Grid grid;
    int ret;

    grid.xpos = x;
    grid.zpos = z;
    CommUnderItemSearchInitialize(_TRAP_NUM_MAX, _getTrapTblPos);
    ret = CommUnderMatchItemTbl(&grid);

    if(-1 == ret){
        return NULL;
    }
    return _pCTW->pTrapTbl[ret];
}

//==============================================================================
/**
 *  㩂Ɉ��������������ǂ�����Ԃ�
 * @param   ���ׂ������W��X���W
   @param   ���ׂ������W��Z���W
 * @retval  ����������ꍇTRUE
 */
//==============================================================================

BOOL CommTrapCheck(int x,int z)
{
    if(_checkTrap(x, z)==NULL){
        return FALSE;
    }
    return TRUE;
}

//==============================================================================
/**
 *  㩂Ɉ������������ꍇ�̒ʐM�T�C�Y��Ԃ�
 * @param   none
 * @retval  size
 */
//==============================================================================

int CommTrapGetStartSize(void)
{
    return sizeof(_HitTrap);
}

//==============================================================================
/**
 *  㩂Ɉ������������ꍇ�ʐM���b�Z�[�W�𑗐M����
 * @param   ���������邩�ǂ������ׂ���ID
 * @retval  none
 */
//==============================================================================

static BOOL _checkAndSendMessage(int netID)
{
    _HitTrap hitTrap;
    TrapInfo* pTrap;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(_pCTW->pFSys->savedata);

    if(UgDigFossilIsDig(netID)){
        return FALSE;
    }
    pTrap = _checkTrap( CommPlayerGetPosSX(netID), CommPlayerGetPosSZ(netID));
    if(!pTrap){
        return FALSE;
    }

    if(_pCTW->nowTrapTypeServer[netID] != _TRAP_TYEP_INVALID){
        CommPlayerResetCondition(netID);
        _trapServerExit(netID,_pCTW->nowTrapTypeServer[netID]);
    }
    _trapServerStart(netID, pTrap->trapType);// 㩏���
    hitTrap.bGoodsTrap = FALSE;
    hitTrap.victimNetID = netID;                 // ���ꂪ����������
    hitTrap.assailantNetID = _getTrapNetID(pTrap);  // ����̂�Ȃɂ���������
    MI_CpuCopy8(pTrap, &hitTrap.trap, sizeof(TrapInfo));

    OHNO_PRINT("--+㩂����� %d %d \n", pTrap->trapType, hitTrap.assailantNetID);

    if(hitTrap.assailantNetID >= _TRAP_ID_NATURE){ //�V�R��㩂̏ꍇ
        UnderGroundDelNatureTrapGroundItem(pUGData,hitTrap.trap.order); //�����ŏ�����
    }

    CommSendData_ServerSide(CF_TRAP_START, &hitTrap, sizeof(_HitTrap)); // ���M
    _pCTW->nowTrapTypeServer[netID] = pTrap->trapType;
    // 㩂���������
    //pTrap->trapType = _TRAP_TYEP_INVALID;

    _delTrap(pTrap);

  //  _delTrapTbls(_getTrapNetID(pTrap));
 //   CommPlayerSetMoveControl_Server(netID,FALSE);
    return TRUE;
}

//==============================================================================
/**
 *  㩂Ɉ������������ӂ������ ���u���L�̊֐�
 * @param   netID      ���������鐶��
 * @param   trapType   㩃^�C�v ���݂͂��Ă��Ȃ�
 * @retval  none
 */
//==============================================================================

void UgTrapGoodsBind(int netID,int assailantNetID,int trapType,int xpos,int zpos,int dir)
{
    _HitTrap hitTrap;

    if(_pCTW->nowTrapTypeServer[netID] != _TRAP_TYEP_INVALID){
        _trapServerExit(netID,_pCTW->nowTrapTypeServer[netID]);
    }
    _trapServerStart(netID, trapType);// 㩏���
    hitTrap.victimNetID = netID;                 // ���ꂪ����������
    hitTrap.assailantNetID = assailantNetID;
    hitTrap.bGoodsTrap = TRUE;
    hitTrap.trap.trapType = trapType;
    hitTrap.trap.xpos = xpos;
    hitTrap.trap.zpos = zpos;
    hitTrap.dir = dir;  // �i��������

    CommSendData_ServerSide(CF_TRAP_START, &hitTrap, sizeof(_HitTrap)); // ���M
    _pCTW->nowTrapTypeServer[netID] = trapType;
}

//==============================================================================
/**
 *  㩂Ɉ������������ꍇ�̊Ǘ�
 * @param   ���������邩�ǂ������ׂ���ID
 * @retval  none
 */
//==============================================================================

BOOL CommTrapCheckAndSendMessage(int netID)
{
    if(_pCTW){
        if(CommPlayerGetMoveControl(netID)){
            return _checkAndSendMessage(netID);
        }
    }
    return FALSE;
}


//==============================================================================
/**
 *  ���u�Ɉ����������Ă��邩�ǂ�����Ԃ�
 * @param   netID    �l�b�gID
 * @param   size     �f�[�^�T�C�Y
 * @param   *pData   �f�[�^
 * @retval  none
 */
//==============================================================================

BOOL CommTrapIsGoodsTrap(int netID)
{
    return _pCTW->hitTrap[netID].bGoodsTrap;
}

//==============================================================================
/**
 *  㩂Ɉ��������������Ƃ���M����  CF_TRAP_START
 * @param   netID    �l�b�gID
 * @param   size     �f�[�^�T�C�Y
 * @param   *pData   �f�[�^
 * @retval  none
 */
//==============================================================================

void CommTrapRecvStart(int netID, int size, void* pData, void* pWork)
{
    _HitTrap* pHitTrap = (_HitTrap*)pData;
    SB_RECORD_DATA* pRec;

    OHNO_PRINT("CommTrapRecvStart       ^^^^^^^^%d\n",pHitTrap->trap.trapType);
    
    if(!_pCTW){
        return;
    }
    pRec = SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(_pCTW->pFSys));
    // 㩃G�t�F�N�g�\��
    Snd_SePlay( UG_SE_ALARM );
    MI_CpuCopy8(pHitTrap, &_pCTW->hitTrap[pHitTrap->victimNetID],
                sizeof(_HitTrap));

    switch(pHitTrap->trap.trapType){  // �O���Ɏ����Ă��ă��b�Z�[�W�����炷
      case UG_TRAPTYPE_ALART1:
        _pCTW->msgMsgTrap[pHitTrap->victimNetID] = UGTrap_msg01;
        break;
      case UG_TRAPTYPE_ALART2:
        _pCTW->msgMsgTrap[pHitTrap->victimNetID] = UGTrap_msg02;
        break;
      case UG_TRAPTYPE_ALART3:
        _pCTW->msgMsgTrap[pHitTrap->victimNetID] = UGTrap_msg03;
        break;
      case UG_TRAPTYPE_ALART4:
        _pCTW->msgMsgTrap[pHitTrap->victimNetID] = UGTrap_msg04;
        break;
      default:
        _pCTW->hitTrap[pHitTrap->victimNetID].message = 1;
//        _pCTW->msgTrapEnd[pRet->netID] = _RESULT_OK;
        break;
    }

    if(CommGetCurrentID() == pHitTrap->victimNetID){
        _trapClientStart(pHitTrap->victimNetID, pHitTrap->trap.trapType, pHitTrap->bGoodsTrap,pHitTrap->dir);
    }
    else{
        UgTrapTurnDispStart(pHitTrap->victimNetID, pHitTrap->trap.trapType);
    }
    CommPlayerSetFEExclamationAdd(pHitTrap->victimNetID);
    if(CommGetCurrentID() == pHitTrap->victimNetID){
        SecretBaseRecordSetTrapTumbleNum(pRec);  // 㩂ɂ����������Ƃ��J�E���g
    }
    if(CommGetCurrentID() == pHitTrap->assailantNetID){
        if(pHitTrap->assailantNetID != pHitTrap->victimNetID){
            SecretBaseRecordSetTrapConquerNum(pRec);  // 㩂ɂ��������Ƃ��J�E���g
        }
        {
            EVENTWORK* pEV = SaveData_GetEventWork( _pCTW->pFSys->savedata );
            SysWork_UGTrapHitCountSet(pEV,SysWork_UGTrapHitCountGet(pEV)+1);
        }
        _myTrapDel(&pHitTrap->trap);
        _myTrapBackup();
    }
}


//CF_TRAP_SECOND_START

void CommTrapRecvSecondStart(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    ServerTrapFunc pFunc = _serverTrapSecondFunc[pBuff[0]];

    if(pBuff[0] != _pCTW->nowTrapTypeServer[netID]){
        CommSetErrorReset(COMM_ERROR_RESET_SAVEPOINT);
        return;
    }

    if(pFunc){
        pFunc( netID );
    }
}


void CommTrapRecvSecondStartRet(int netID, int size, void* pData, void* pWork)
{
    u8 *pBuff = pData;

    if(pBuff[0] != CommGetCurrentID()){
        CommPlayerBlowAnimStart( pBuff[0], pBuff[1] , pBuff[2]);
    }
}


//==============================================================================
/**
 * ����㩂Ɉ����������Ă���l�𑗐M
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

void CommTrapSendTrapingArray(void)
{
    u8 bit=0;
    int i;

    if(_pCTW){
        for(i = 0; i < COMM_MACHINE_MAX;i++){
            if(_pCTW->nowTrapTypeServer[i]!=UG_TRAPTYPE_NONE){
                bit = bit | (0x01 << i);
            }
        }
        CommSendFixSizeData_ServerSide(CF_TRAP_NOWARRAY,&bit);
    }
}

//==============================================================================
/**
 * ����㩂Ɉ����������Ă���lARRAY������
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

void CommTrapRecvTrapingArray(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    u8 bit = pBuff[0];
    int i;

    if(_pCTW->nowTrapType!=UG_TRAPTYPE_NONE){
        return;
    }
    
    for(i = 0; i < COMM_MACHINE_MAX;i++){
        if(bit & (0x01 << i)){
//            UgTrapTurnDispStart(i,UG_TRAPTYPE_BIG_SMOG);  // �c�O�Ȃ���TRAPTYPE�͉��ʐM�ʂ�����
            CommPlayerSetFEExclamationAdd(i); // �Ȃ̂ŁI�̂�
        }
    }
}

//==============================================================================
/**
 *  㩂Ɉ������������󋵃��b�Z�[�W��Ԃ�
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

BOOL CommTrapGetActionMessage(STRBUF* pStrBuf)
{
    int i,msgNo;
    MYSTATUS* pMy;
    MYSTATUS* pTarget;

    if(!_pCTW){
        return FALSE;
    }

    for(i = 0; i< COMM_MACHINE_MAX; i++){
        if(_pCTW->hitTrap[i].message == 1){
            _pCTW->hitTrap[i].message = 0;
            if(_pCTW->hitTrap[i].assailantNetID >= _TRAP_ID_NATURE){
                pMy = CommInfoGetMyStatus(i);
                if(UgMgrRadarLogSingle(pMy, 0, UGDecoyNatural, pStrBuf)){
                    return TRUE;
                }
            }
            else{
                pMy = CommInfoGetMyStatus(_pCTW->hitTrap[i].assailantNetID);
                pTarget = CommInfoGetMyStatus(i);
                if(UgMgrRadarLogDouble(pTarget,pMy,UGDecoy01,pStrBuf)){
                    return TRUE;
                }
            }
        }
        if(_pCTW->logResque[i] != INVALID_NETID){
            pMy = CommInfoGetMyStatus(i);
            pTarget = CommInfoGetMyStatus(_pCTW->logResque[i]);
            _pCTW->logResque[i] = INVALID_NETID;
            if(UgMgrRadarLogDouble(pMy,pTarget,UGhelp01,pStrBuf)){
                return TRUE;
            }
        }
    }
    return FALSE;
}

//==============================================================================
/**
 *  㩐ݒu�󋵃��b�Z�[�W��Ԃ�
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

BOOL CommTrapSetActionMessage(STRBUF* pStrBuf)
{
    int i,msg;
    MYSTATUS* pMy;
    MYSTATUS* pTarget;

    if(!_pCTW){
        return FALSE;
    }
    for(i = 0; i< COMM_MACHINE_MAX; i++){
        if(_pCTW->msgMsgTrap[i] != 0){
            msg = _pCTW->msgMsgTrap[i];
            _pCTW->msgMsgTrap[i] = 0;
            pMy = CommInfoGetMyStatus(i);
            if(UgMgrRadarLogSingle(pMy, 0, msg, pStrBuf)){
                return TRUE;
            }
        }
        if(_pCTW->msgTrapDefuse[i] == _RESULT_OK){
            _pCTW->msgTrapDefuse[i] = _RESULT_NONE;
            pMy = CommInfoGetMyStatus(i);
            if(UgMgrRadarLogSingle(pMy, 0, UGTrapFind02, pStrBuf)){
                return TRUE;
            }
        }
        if(_pCTW->msgTrapEnd[i] == _RESULT_OK){
            pMy = CommInfoGetMyStatus(i);
            _pCTW->msgTrapEnd[i] = _RESULT_NONE;
            if(UgMgrRadarLogSingle(pMy, 0, UGUnConfused, pStrBuf)){
                return TRUE;
            }
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * 㩏������J�n
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _trapServerStart(int victimNetID, int trapType)
{
    ServerTrapFunc pFunc = _serverTrapFunc[trapType];
    if(pFunc){
        pFunc( victimNetID );
    }
}

static void _trapServerExit(int victimNetID, int trapType)
{
    ServerTrapFunc pFunc = _serverTrapExit[trapType];
    if(pFunc){
        pFunc( victimNetID );
    }
}


//==============================================================================
/**
 * 㩏�Ԃ̋����I��
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

void UgTrapForceExit(int victimNetID, int bMove)
{
    ClientTrapEndFunc pEndFunc;
    if(_pCTW->nowTrapType!=UG_TRAPTYPE_NONE){  // ����㩂̉���
        OHNO_SP_PRINT("��������------%d\n",_pCTW->nowTrapType);

        pEndFunc = _clientTrapForceExit[_pCTW->nowTrapType];
        if(pEndFunc){
            pEndFunc( victimNetID, bMove );
        }
        if(CommGetCurrentID() != COMM_PARENT_ID){
            CommPlayerResetCondition(victimNetID);
        }
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        Snd_SePlay(UGT_SE_TRAPEND);
        _pCTW->trapProc = NULL;
        CommPlayerSetFENoneAdd(victimNetID);
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        _pCTW->nowTrapType=UG_TRAPTYPE_NONE;
    }
}

//==============================================================================
/**
 * 㩃G�t�F�N�g���J�n
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _trapClientStart(int victimNetID, int trapType, BOOL bGoodsTrap, int dir)
{
    ClientTrapEndFunc pEndFunc;
    ClientTrapFunc pFunc;

    UgTrapForceExit(victimNetID, TRUE);

    _pCTW->nowTrapType = trapType;   // �����쒆�̃g���b�v�^�C�v
    pFunc = _clientTrapFunc[trapType];
    if(pFunc){
        pFunc( victimNetID, bGoodsTrap, dir );  // ������
        //   _pCTW->trapProc = _trapProc[trapType];  // ����֐��Z�b�g
        //        _pCTW->nowTrapType = trapType;   // �����쒆�̃g���b�v�^�C�v
    }
}

//==============================================================================
/**
 * �O�b�Y㩂̈ړ��߂�w��
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================


static void _goodsTrapReverse(int paramDir)
{
    int x,z,dir;

    dir = CommPlayerGetReverseDir(paramDir);
    Player_DirSet(_pCTW->pFSys->player, dir);
    x = _pCTW->hitTrap[CommGetCurrentID()].trap.xpos;
    z = _pCTW->hitTrap[CommGetCurrentID()].trap.zpos;
    x = x + FieldOBJ_DirAddValueGX(dir);
    z = z + FieldOBJ_DirAddValueGZ(dir);
    CommPlayerSendPosXZ(FALSE,x,z);
}

//==============================================================================
/**
 * �O�b�Y㩂̈ړ��߂�w�茟��
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================


static BOOL _goodsTrapReverseCheck(int paramDir, BOOL bGoodsPos)
{
    int x,z,x2,z2,dir;

    x = Player_NowGPosXGet( _pCTW->pFSys->player );
    z = Player_NowGPosZGet( _pCTW->pFSys->player );
    dir = CommPlayerGetReverseDir(paramDir);
    x2 = _pCTW->hitTrap[CommGetCurrentID()].trap.xpos;
    z2 = _pCTW->hitTrap[CommGetCurrentID()].trap.zpos;
    if(!bGoodsPos){
        x2 = x2 + FieldOBJ_DirAddValueGX(dir);
        z2 = z2 + FieldOBJ_DirAddValueGZ(dir);
    }

    if((x == x2) && (z == z2)){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �͂�Ă��㩂��J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startServerReverse(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_GIDDY);
    CommPlayerSetGiddyStep(victimNetID,_REVERSE_STEP_NUM);
}

//==============================================================================
/**
 * ������㩂��J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startServerGiddy(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_GIDDY);
    CommPlayerSetGiddyStep(victimNetID,_GIDDY_STEP_NUM);
}


static void _exitServerGiddy(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_NONE);
    CommPlayerResetGiddyStep(victimNetID);
}

//==============================================================================
/**
 * ����㩂��J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startServerSmog(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
}

//==============================================================================
/**
 * �Ԃт�̕����J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startServerDirtyBlossoms(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
}



//==============================================================================
/**
 * ������΂����J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================


static void _startServerDir(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_FORCE_MOVE);
    CommPlayerBlowFirst(victimNetID);
}

static void _startServerDirUp(int victimNetID)
{
    CommPlayerBlowStart(victimNetID, DIR_UP, FALSE);
}
static void _startServerDirDown(int victimNetID)
{
    CommPlayerBlowStart(victimNetID, DIR_DOWN, FALSE);
}
static void _startServerDirLeft(int victimNetID)
{
    CommPlayerBlowStart(victimNetID, DIR_LEFT, FALSE);
}
static void _startServerDirRight(int victimNetID)
{
    CommPlayerBlowStart(victimNetID, DIR_RIGHT, FALSE);
}
static void _startServerBigDirUp(int victimNetID)
{
    CommPlayerBlowStart(victimNetID, DIR_UP, TRUE);
}
static void _startServerBigDirDown(int victimNetID)
{
    CommPlayerBlowStart(victimNetID, DIR_DOWN, TRUE);
}
static void _startServerBigDirLeft(int victimNetID)
{
    CommPlayerBlowStart(victimNetID, DIR_LEFT, TRUE);
}
static void _startServerBigDirRight(int victimNetID)
{
    CommPlayerBlowStart(victimNetID, DIR_RIGHT, TRUE);
}

static void _exitServerDir(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_NONE);
    CommPlayerBlowExit(victimNetID);
}

//==============================================================================
/**
 * �h�����Ō����@��
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startServerDrill(int victimNetID)
{
    // �T�[�o�[���͂����ł͉������Ȃ�
}

//==============================================================================
/**
 * ���]��㩂��J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startClientReverse(int victimNetID, BOOL bGoodsTrap,int dir)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_GIDDY);
    if(CommGetCurrentID() == victimNetID){
        _trapGiddyInitialize(TRUE);
    }
}

//==============================================================================
/**
 * ������㩂��J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startClientGiddy(int victimNetID, BOOL bGoodsTrap, int dir)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_GIDDY);
    if(CommGetCurrentID() == victimNetID){
        _trapGiddyInitialize(FALSE);
    }
}

//==============================================================================
/**
 * ����㩂��J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startClientSmog(int victimNetID, BOOL bGoodsTrap,int dir)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
    if(CommGetCurrentID() == victimNetID){
        _trapSmogInitialize(_pCTW->pFSys,bGoodsTrap, dir);
    }
}

//==============================================================================
/**
 * �Ԃт�̕���㩂��J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startClientDirtyBlossoms(int victimNetID, BOOL bGoodsTrap, int dir)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
    if(CommGetCurrentID() == victimNetID){
        _dirtyBlossomsInitialize(_pCTW->pFSys, bGoodsTrap, dir);
    }
}

//==============================================================================
/**
 * �N���C�A���g��������΂����J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startClientDirUp(int victimNetID, BOOL bGoodsTrap, int dir)
{
    //   CommPlayerBlowAnimStart(victimNetID, DIR_UP, FALSE);
    _trapDirStart(_pCTW->pFSys, victimNetID, DIR_UP, FALSE);
}
static void _startClientDirDown(int victimNetID, BOOL bGoodsTrap, int dir)
{
    _trapDirStart(_pCTW->pFSys, victimNetID, DIR_DOWN, FALSE);
}
static void _startClientDirLeft(int victimNetID, BOOL bGoodsTrap, int dir)
{
    _trapDirStart(_pCTW->pFSys, victimNetID, DIR_LEFT, FALSE);

}
static void _startClientDirRight(int victimNetID, BOOL bGoodsTrap, int dir)
{
    _trapDirStart(_pCTW->pFSys, victimNetID, DIR_RIGHT, FALSE);
}
static void _startClientBigDirUp(int victimNetID, BOOL bGoodsTrap, int dir)
{
    _trapDirStart(_pCTW->pFSys, victimNetID, DIR_UP, TRUE);
}
static void _startClientBigDirDown(int victimNetID, BOOL bGoodsTrap, int dir)
{
    _trapDirStart(_pCTW->pFSys, victimNetID, DIR_DOWN, TRUE);
}
static void _startClientBigDirLeft(int victimNetID, BOOL bGoodsTrap, int dir)
{
    _trapDirStart(_pCTW->pFSys, victimNetID, DIR_LEFT, TRUE);
}
static void _startClientBigDirRight(int victimNetID, BOOL bGoodsTrap, int dir)
{
    _trapDirStart(_pCTW->pFSys, victimNetID, DIR_RIGHT, TRUE);
}


static int _trapStartSet(void)
{
    int index,x,z;

    x = Player_NowGPosXGet(_pCTW->pFSys->player);
    z = Player_NowGPosZGet(_pCTW->pFSys->player);
    FE_FldOBJTrapsmogSet(_pCTW->pFSys, x, 0, z);
    CommMsgRegisterUGTrapNameIndex(CommUnderGetMsgUnderWorld(),0,_pCTW->nowTrapType);
    index = CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderWorld(), msg_underworld_70, FALSE, NULL);
    CommPlayerHoldBit(_HOLD_TRAP);
    //CommPlayerHold();
    return index;
}

//==============================================================================
/**
 * �N���C�A���g��������΂����s�֐�
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

enum{
    _DIR_START,
    _DIR_CHAR,
    _DIR_PAL,
    _DIR_SCR,
    _DIR_WAIT,
    _DIR_FUNC,
    _DIR_ENDWAIT,
    _DIR_END,
};


static void _procDir(TCB_PTR tcb,void* work)
{
    _EVENT_DIR_WORK* wk = work;
    int i;

    switch(wk->seq){
      case _DIR_START:
        wk->index = _trapStartSet();
        wk->seq++;
        break;
      case _DIR_CHAR:
        ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        wk->seq++;
        break;
      case _DIR_PAL:
        wk->seq++;
        break;
      case _DIR_SCR:
        ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        wk->seq++;
        break;
      case _DIR_WAIT:
            wk->timer++;
            if(wk->timer == 28){
                u8 type = _pCTW->nowTrapType;
                CommSendFixSizeData(CF_TRAP_SECOND_START,&type);
            }
            if(wk->timer > 30){
                CommPlayerHoldBitEnd(_HOLD_TRAP);
                ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV,BRIGHTNESS_NORMAL,
                                        PLANEMASK_BG0,MASK_MAIN_DISPLAY);
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
                CommPlayerBlowAnimStart(wk->victimNetID, wk->dir, wk->bBig);
                Snd_SePlay(SE_TRAP_MOVE);
                wk->seq = _DIR_FUNC;
            }
        break;
      case _DIR_FUNC:
        wk->seq = _DIR_ENDWAIT;
        break;
      case _DIR_ENDWAIT:
        break;
      case _DIR_END:
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        //        ChangeBrightnessRequest(0, BRIGHTNESS_NORMAL, _TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV,
        //                              PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        sys_FreeMemoryEz(wk);
        TCB_Delete(tcb);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
        Snd_SeStopBySeqNo(SE_TRAP_MOVE, 0);
        OHNO_PRINT("_DIR_END\n");
        break;
    }
}


static void _trapDirStart(FIELDSYS_WORK* pFSys, int victimNetID, int dir, BOOL bBig)
{
    _EVENT_DIR_WORK* wk;
    wk = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_DIR_WORK));
    MI_CpuFill8(wk, 0, sizeof(_EVENT_DIR_WORK));
    GF_ASSERT(_pCTW->pTCBWork == NULL);
    _pCTW->pTCBWork = wk;
    wk->pFSys = pFSys;
    wk->victimNetID = victimNetID;
    wk->dir = dir;
    wk->bBig = bBig;
    OHNO_PRINT("_trapDirStart\n");
    _pCTW->pRadar = TCB_Add(_procDir, wk, TCB_PRIORITY_NORMAL);
}

//==============================================================================
/**
 * dir�I��
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _endClientDir(int netID,BOOL bGoods)
{
    CommPlayerBlowAnimStop(netID);
    if(_pCTW->pTCBWork){
        _EVENT_DIR_WORK* wk = _pCTW->pTCBWork;
        wk->seq = _DIR_END;
        _pCTW->pTCBWork = NULL;
        OHNO_PRINT("_endClientDir\n");
        Snd_SeStopBySeqNo(SE_TRAP_MOVE, 0);
    }
}


static void _forceEndClientDir(int netID, BOOL bGoods)
{
    CommPlayerBlowAnimStop(netID);
    if(_pCTW->pTCBWork){
        _EVENT_DIR_WORK* wk = _pCTW->pTCBWork;
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        sys_FreeMemoryEz(wk);
        TCB_Delete(_pCTW->pRadar);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
        Snd_SeStopBySeqNo(SE_TRAP_MOVE, 0);
    }
}


//==============================================================================
/**
 * �h�����Ō����@��
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startClientDrill(int victimNetID, BOOL bGoodsTrap,int dir)
{
    // �����ł��������Ȃ�
}


//--------------------------------------------------------------
/**
 * 㩊G���o��
 * @param
 * @retval
 */
//--------------------------------------------------------------
static EOA_PTR _trapPictAdd(int x, int z, int scale, int type)
{
    EOA_PTR eoa;

    if(!_pCTW->bHalt){
        eoa = FE_Hole_Add(_pCTW->pFSys, x, z, scale, type-1);
        return( eoa );
    }
    return NULL;
}

//--------------------------------------------------------------
/**
 * �ŏ��ɐ�������㩂𓾂�
 * @param    netID  �@��ԍ�
 * @retval   �����ԍ�
 */
//--------------------------------------------------------------
static TrapInfo* _getOldOrderData(TrapInfo* pTrapTbl)
{
    return pTrapTbl;  // �擪����ԌÂ�
}

//--------------------------------------------------------------
/**
 * �X���b�O��㩂̏�����
 * @param    GF_BGL_INI bgl�ԍ�
 * @retval   none
 */
//--------------------------------------------------------------

// ����
typedef enum{
    _INIT,
    _CHAR_READ,
    _PAL_READ,
    _CELL_READ,
    _ANIM_READ,
    _SET_CLACT,
    _MESSAGE_LOOP,
    _FUNC,
    _ENDCMD,
    _END,
    _END2,
    _GOODS_END_START,
    _GOODS_END_WALK,
    _GOODS_END_END,
    _HOLE_ENDING,
};


static void _trapSmogInitialize(FIELDSYS_WORK* pFSys, BOOL bGoodsTrap, int dir)
{
    _EVENT_SMOG_WORK* wk;
    wk = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_SMOG_WORK));
    MI_CpuFill8(wk, 0, sizeof(_EVENT_SMOG_WORK));
    _pCTW->pTCBWork = wk;
    _smogTouchNone(wk);  // ���W���Z�b�g
    wk->bgl = pFSys->bgl;
    wk->pFSys = pFSys;
    wk->bGoodsTrap = bGoodsTrap;
    wk->dir = dir;
    _pCTW->pRadar = TCB_Add(_procSmog, wk, TCB_PRIORITY_NORMAL);
}

//--------------------------------------------------------------
/**
 * �X���b�O���  ����`��
 * @param    none
 * @retval   ���쒆��TRUE
 */
//--------------------------------------------------------------


static void _drawLine(int x0, int y0, int x1, int y1,u8* pScrAddr){

    int E, x=x0, y=y0, dx, dy, wx=abs(x0-x1), wy=abs(y1-y0);
    BOOL bDraw=FALSE;

    dx=(x0<x1)?1:-1;
    dy=(y0<y1)?1:-1;

    if(wx >= wy){ /* �X����1��菬�����H */
        E = -wx;  /* E�̏����� */
        while(x != x1){
            bDraw += _commTrapSmogDelete(x,y,pScrAddr);
            x += dx;
            E += 2*wy;
            if(E >= 0){
                E -= 2*wx;
                y += dy;
            }
        }
    }else{ /* �X����1���傫���ꍇ(or-1��菬�����ꍇ) */
        E = -wy;  /* E�̏����� */
        while(y != y1){
            bDraw += _commTrapSmogDelete(x,y,pScrAddr);
            y += dy;
            E += 2*wx;
            if(E >= 0){
                E -= 2*wy;
                x += dx;
            }
        }
    }
    if(bDraw){
        if(!Snd_SePlayCheck(UGT_SE_SMOG)){
            Snd_SePlay(UGT_SE_SMOG);
        }
    }
}

//--------------------------------------------------------------
/**
 * �X���b�O��㩂��I��点��
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static void _endClientSmog(int victimNetID,BOOL bGoods)
{
    if(_pCTW->pTCBWork){
        _EVENT_SMOG_WORK* wk = _pCTW->pTCBWork;

        if(wk->bGoodsTrap && bGoods){
//        if(wk->bGoodsTrap){
            _goodsTrapReverse(wk->dir);
        }
        G2_BlendNone();
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
//        ChangeBrightnessRequest(1, BRIGHTNESS_NORMAL, _TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV,
//                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        {
            int i;
            u8* pScrAddr = GF_BGL_ScreenAdrsGet( _pCTW->pFSys->bgl, GF_BGL_FRAME2_M );
            for(i = 0; i< 0x800; i+=2 ){
                pScrAddr[i] = 0;
            }
            GF_BGL_PrioritySet(GF_BGL_FRAME2_M , 3);
            GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
        }
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        TCB_Delete(_pCTW->pRadar);
        sys_FreeMemoryEz(wk);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
    }
}

//--------------------------------------------------------------
/**
 * �X���b�O��㩂����삵�Ă��邩�ǂ���
 * @param    none
 * @retval   ���쒆��TRUE
 */
//--------------------------------------------------------------

static BOOL _trapSmogTouch(Grid* pGrid, GF_BGL_INI * bgl,_EVENT_SMOG_WORK* wk)
{
    int i,cnt=0;
    u8* pScrAddr = GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME2_M );

    if(pScrAddr==NULL){
        return FALSE;
    }
    if((wk->oldXpos != 0xffff)&&(wk->oldZpos != 0xffff)){
        _drawLine(pGrid->xpos, pGrid->zpos,
                  wk->oldXpos,wk->oldZpos,
                  pScrAddr);
        // �Ƃ肠�����S�]��
        GF_BGL_LoadScreenReq(bgl, GF_BGL_FRAME2_M);

    }
    wk->oldXpos = pGrid->xpos;
    wk->oldZpos = pGrid->zpos;

    // ��ʌ������v�Z
    for(i = 0; i< 0x800; i+=2 ){
        if(pScrAddr[i] != 0){
            cnt++;
        }
    }
    if( cnt < 13 ){
        return TRUE;
    }
    return FALSE;
}


//--------------------------------------------------------------
/**
 * ��ӏ�����
 * @param    xpos,zpos  ���W
 * @retval   none
 */
//--------------------------------------------------------------

static BOOL _commTrapSmogDelete(int xpos, int zpos, u8* pScrAddr)
{
    u16 cell = (xpos/8 + zpos/8 * (256/8)) *2;
    s32 bothDeleteTbl[]={-66,-64,-62,-2,0,2,62,64,66};   // �����ɏ���CELL    �̃e�[�u��
    int i;
    BOOL bDraw = FALSE;

    if(cell > 0x800){
        return bDraw;
    }
    for(i = 0; i < sizeof(bothDeleteTbl)/sizeof(s32); i++){
        s32 bothCell = cell + bothDeleteTbl[i];
        if((cell % 64) == 62){// �E�[
            if(i % 3 == 2){
                continue;
            }
        }
        if(cell % 64 == 0){// ���[
            if(i % 3 == 0){
                continue;
            }
        }
        if((bothCell < 0x800) && (bothCell >= 0)  &&(pScrAddr[bothCell]!=0)){
            bDraw = TRUE;
            switch(i){
              case 4:
                pScrAddr[bothCell] = pScrAddr[bothCell] + 3;
                break;
              case 1:
              case 3:
              case 5:
              case 7:
                pScrAddr[bothCell] = pScrAddr[bothCell] + 2;
                break;
              default:
                pScrAddr[bothCell] = pScrAddr[bothCell] + 1;
                break;
            }
            if(pScrAddr[bothCell] > 5){
                pScrAddr[bothCell] = 0;
            }
        }
    }
    return bDraw;
}



//--------------------------------------------------------------
/**
 * �X���b�O��㩃��C��������
 * @param    none
 * @retval   ���쒆��TRUE
 */
//--------------------------------------------------------------

static void _smogTouchNone(_EVENT_SMOG_WORK* wk)
{
    wk->oldXpos = 0xffff;
    wk->oldZpos = 0xffff;
}

//--------------------------------------------------------------
/**
 * @brief   ���  ���s����
 * @param   bgl  GF_BGL_INI
 * @retval  none
 */
//--------------------------------------------------------------

static void _procSmog(TCB_PTR tcb, void *work)
{
    _EVENT_SMOG_WORK* wk = work;
    int i;

    switch(wk->seq){
      case _INIT:
        GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
        wk->index = _trapStartSet();
        wk->seq++;
        break;
      case _CHAR_READ:
        ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                            PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        ArcUtil_BgCharSet( ARC_UG_TRAP_GRA, NARC_ug_trap_t_kemuri_NCGR, wk->bgl, GF_BGL_FRAME2_M, 0, 8*6*6, 0, HEAPID_FIELD);
        wk->seq++;
        break;
      case _PAL_READ:
        ArcUtil_PalSet( ARC_UG_TRAP_GRA, NARC_ug_trap_t_kemuri_NCLR, PALTYPE_MAIN_BG, 0, 32,  HEAPID_FIELD);
        wk->seq++;
        break;
      case _CELL_READ:
        ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        // �X�N���[���͂S��ލ����
        if(_pCTW->nowTrapType == UG_TRAPTYPE_BIG_SMOG){
            ArcUtil_ScrnSet(   ARC_UG_TRAP_GRA, NARC_ug_trap_t_full_NSCR, wk->bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 0, HEAPID_FIELD);
        }
        else{
            u16 scrTbl[]={NARC_ug_trap_t_kemuri_NSCR,
                NARC_ug_trap_tk2_NSCR,
                NARC_ug_trap_tk3_NSCR,
                NARC_ug_trap_tk4_NSCR
            };
            u16 i = gf_rand() % 4;
            ArcUtil_ScrnSet(   ARC_UG_TRAP_GRA, scrTbl[i], wk->bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 0, HEAPID_FIELD);
        }
        GF_BGL_PrioritySet(GF_BGL_FRAME0_M , 3);
        GF_BGL_PrioritySet(GF_BGL_FRAME1_M , 2);
        GF_BGL_PrioritySet(GF_BGL_FRAME2_M , 1);
        GF_BGL_PrioritySet(GF_BGL_FRAME3_M , 0);
        wk->seq++;
        break;
      case _ANIM_READ:
      case _SET_CLACT:
      case _MESSAGE_LOOP:
            wk->timer++;
            if(wk->timer > 30){
                ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV,BRIGHTNESS_NORMAL,
                                        PLANEMASK_BG0,MASK_MAIN_DISPLAY);
                GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
                wk->seq = _FUNC;
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_77,FALSE,NULL);
                wk->msgTimer = 0;
                Snd_SePlay(SE_TRAP_KEMURI);
            }
        break;
      case _FUNC:
        if(sys.tp_cont){
            Grid grid;
            grid.xpos = sys.tp_x;
            grid.zpos = sys.tp_y;
            if(_trapSmogTouch(&grid, wk->bgl,wk )){
                if(wk->bGoodsTrap){
                    wk->seq = _GOODS_END_START;
                }
                else{
                    CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
                    wk->seq = _ENDCMD;
                }
            }
        }
        else{
            _smogTouchNone(wk);  // ���W��������
        }
        if(wk->msgTimer < _MSG_TIME){
            wk->msgTimer++;
            if(wk->msgTimer == _MSG_TIME){
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            }
        }
        break;
      case _ENDCMD:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        break;
      case _END:
        _endClientSmog(CommGetCurrentID(), wk->bGoodsTrap);
        
        break;
      case _GOODS_END_START:
        wk->bGoodsTrap=FALSE;
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        _goodsTrapReverse(wk->dir);
        wk->timer=0;
        wk->seq = _GOODS_END_WALK;
        break;
      case _GOODS_END_WALK:
        wk->timer++;
        if(wk->timer > 8){
            CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
            wk->seq = _ENDCMD;
        }
        break;
    }
}

//--------------------------------------------------------------
/**
 * �g���b�v�I���R�}���h�̃T�C�Y
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

typedef struct {
    u8 trapType;
    u8 netID;
    u8 bResult;  //TRUE���� FALSE �����I��
    u8 bGoods;  // ���u�̏ꍇ
} TrapEndResult_t;


int CommTrapGetEndResultSize(void)
{
    return sizeof(TrapEndResult_t);
}


//--------------------------------------------------------------
/**
 * �g���b�v�I�����q�@���瑗���Ă���  CF_TRAP_END
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @param   pWork    �g�p���������[�N
 * @retval   none
 */
//--------------------------------------------------------------

void CommTrapRecvEnd(int netID, int size, void* pData, void* pWork)
{
    u8 id = netID;
    TrapEndResult_t ret;

    CommPlayerResetCondition(netID);
    _trapServerExit(netID,_pCTW->nowTrapTypeServer[netID]);
    ret.bGoods = UgSecretBaseTrapGoodsReset(netID);
    ret.trapType = _pCTW->nowTrapTypeServer[netID];
    ret.netID = netID;
    ret.bResult = TRUE;
    CommSendFixSizeData_ServerSide(CF_TRAP_END_RESULT,&ret);
    _pCTW->nowTrapTypeServer[netID] = _TRAP_TYEP_INVALID;
}

// ������͋����I�ɉ���  CF_TRAP_END_FORCE
void CommTrapRecvForceEnd(int netID, int size, void* pData, void* pWork)
{
    u8 id = netID;
    TrapEndResult_t ret;

    CommPlayerResetCondition(netID);
    if(_pCTW->nowTrapTypeServer[netID] != _TRAP_TYEP_INVALID){
        _trapServerExit(netID,_pCTW->nowTrapTypeServer[netID]);
    }
    _pCTW->nowTrapTypeServer[netID] = _TRAP_TYEP_INVALID;
    _pCTW->hitTrap[netID].bGoodsTrap = FALSE;
    UgSecretBaseTrapGoodsReset(netID);

}



//--------------------------------------------------------------
/**
 * �g���b�v�I�����e�@���瑗���Ă���  CF_TRAP_END_RESULT
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @param   pWork    �g�p���������[�N
 * @retval   none
 */
//--------------------------------------------------------------

void CommTrapRecvEndResult(int netID, int size, void* pData, void* pWork)
{
    TrapEndResult_t *pRet = pData;
    int trapType = pRet->trapType;   // �����쒆�̃g���b�v�^�C�v
    ClientTrapEndFunc pEndFunc;

    if(pRet->bResult){
        CommPlayerSetFEOkAdd( pRet->netID );
    }
    else{
        CommPlayerSetFENoneAdd( pRet->netID );
    }
    UgTrapTurnDispEnd(pRet->netID);

    if(pRet->netID == CommGetCurrentID()){
        pEndFunc = _clientTrapExit[trapType];
        if(pEndFunc){
            pEndFunc( pRet->netID, pRet->bGoods );
        }
        _pCTW->nowTrapType = UG_TRAPTYPE_NONE;
    }
    switch(trapType){  // �I�����̃��b�Z�[�W
      case UG_TRAPTYPE_ALART1:
      case UG_TRAPTYPE_ALART2:
      case UG_TRAPTYPE_ALART3:
      case UG_TRAPTYPE_ALART4:
        break;
      default:
        _pCTW->msgTrapEnd[pRet->netID] = _RESULT_OK;
        break;
    }
    if(CommGetCurrentID()!=COMM_PARENT_ID){
        CommPlayerResetCondition(pRet->netID);
    }
}

//--------------------------------------------------------------
/**
 * �T�[�o�[�����牉�o�̃^�C�~���O���킹�Ŕ��ł��閽�� ���̏�HOLE�̂�
 * @param
 * @retval  none
 */
//--------------------------------------------------------------

void CommTrapRecvPriEnd(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int trapType = _pCTW->nowTrapType;   // �����쒆�̃g���b�v�^�C�v

    if((trapType == UG_TRAPTYPE_HOLE) || (trapType == UG_TRAPTYPE_BIG_HOLE)){
        _priEndClientHole(pBuff[0]);
    }
}

//--------------------------------------------------------------
/**
 * �g���b�v���f
 * @param   netID    ���f����l
 * @param   targetID    㩂ɂ������Ă���l
 * @retval  none
 */
//--------------------------------------------------------------

typedef struct{
    u8 netID;
    u8 targetID;
    u8 trapID;
} _TrapRelease;

void CommTrapSendRelease(int netID, int targetID)
{
    _TrapRelease tr;

    CommPlayerResetCondition(targetID);
    _trapServerExit(targetID,_pCTW->nowTrapTypeServer[targetID]);

    tr.targetID = targetID;
    tr.netID = netID;
    tr.trapID = _pCTW->nowTrapTypeServer[targetID];
    OHNO_PRINT("---㩏���  %d %d %d\n",netID,targetID,_pCTW->nowTrapTypeServer[targetID]);
    CommSendFixSizeData_ServerSide(CF_TRAP_RELEASE, &tr);
    _pCTW->nowTrapTypeServer[targetID] = _TRAP_TYEP_INVALID;
    CommPlayerSetMoveControl_Server(netID,FALSE);

}


//--------------------------------------------------------------
/**
 * �g���b�v�������e�@���瑗���Ă���   CF_TRAP_RELEASE
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @param   pWork    �g�p���������[�N
 * @retval   none
 */
//--------------------------------------------------------------

void CommTrapRecvRelease(int netID, int size, void* pData, void* pWork)
{
    _TrapRelease* pTr = pData;
    SB_RECORD_DATA* pRec = SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(_pCTW->pFSys));

    CommPlayerSetFEOkAdd( pTr->targetID );

    if(pTr->netID == CommGetCurrentID()){
        SecretBaseRecordSetTrapRescueNum(pRec);   // 㩂�����[����������
        RECORD_Score_Add(SaveData_GetRecord(_pCTW->pFSys->savedata), SCORE_ID_RESCUE);

        CommPlayerHold();
        CommMsgRegisterTargetName(CommUnderGetMsgUnderWorld(),CommInfoGetMyStatus(pTr->targetID));
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                               msg_underworld_71,TRUE,_msgEndCallBack);

    }
    UgTrapTurnDispEnd(pTr->targetID);
    if((pTr->targetID == CommGetCurrentID()) && (_pCTW->nowTrapType != UG_TRAPTYPE_NONE)){
        int trapType = _pCTW->nowTrapType;   // �����쒆�̃g���b�v�^�C�v
        ClientTrapEndFunc pFunc = _clientTrapForceExit[trapType];
        if(pFunc){
            pFunc( pTr->targetID,FALSE );
        }
        _pCTW->trapProc = NULL;
        _pCTW->nowTrapType = UG_TRAPTYPE_NONE;
        OHNO_SP_PRINT("�g���b�v�����������܂�\n");
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
    }
    if(CommGetCurrentID() != COMM_PARENT_ID){
        CommPlayerResetCondition(pTr->targetID);
    }
    _pCTW->logResque[pTr->netID] = pTr->targetID;
}

//--------------------------------------------------------------
/**
 * �R�}���h�̃T�C�Y��Ԃ�
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

int CommTrapGetReleaseSize(void)
{
    return sizeof(_TrapRelease);
}

//--------------------------------------------------------------
/**
 * �����̃g���b�v�̈ʒuX���W�𓾂�
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

int CommTrapGetMyTrapX(int index)
{
    if(_pCTW  &&
       (_pCTW->myTrapData[index].trapType != _TRAP_TYEP_INVALID) ){
        return _pCTW->myTrapData[index].xpos;
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * �����̃g���b�v�̈ʒuZ���W�𓾂�
 * @param    index
 * @retval   Z���W
 */
//--------------------------------------------------------------

int CommTrapGetMyTrapZ(int index)
{
    if(_pCTW  &&
       (_pCTW->myTrapData[index].trapType != _TRAP_TYEP_INVALID) ){
        return _pCTW->myTrapData[index].zpos;
    }
    return 0;
}

#define _DTIME  (2)  // ���[�_�[��������茩����ׂ̊Ԋu

//--------------------------------------------------------------
/**
 * �����̃g���b�v�{���R��TRAP�̈ʒuX���W�𓾂�
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

int UgTrapGetNatureTrapX(int index)
{
    if(_pCTW && _pCTW->pPcRadarWork){
        int a = _pCTW->pPcRadarWork->pcRadarTimer / _DTIME;
        a = (a + index) % (_TRAP_NUM_SINGLE_MAX + _TRAP_NUM_NATURE);
        return _pCTW->pPcRadarWork->pcRadar[a].xpos;
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * �����̃g���b�v�{���R��TRAP�̈ʒuZ���W�𓾂�
 * @param    index
 * @retval   Z���W
 */
//--------------------------------------------------------------

int UgTrapGetNatureTrapZ(int index)
{
    if(_pCTW && _pCTW->pPcRadarWork){
        int a = _pCTW->pPcRadarWork->pcRadarTimer / _DTIME;
        a = (a + index) % (_TRAP_NUM_SINGLE_MAX + _TRAP_NUM_NATURE);
        return _pCTW->pPcRadarWork->pcRadar[a].zpos;
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * �p�\�R��㩃��[�_�[�N���C�A���g�^�X�N
 * @param    tcb   tcb
 * @param    work   _EVENT_PCRADAR_WORK
 * @retval   none
 */
//--------------------------------------------------------------

static void _GMEVENT_PcRadar(TCB_PTR tcb, void *work)
{
    _EVENT_PCRADAR_WORK* pWork = work;

    pWork->pcRadarTimer++;
    if(((_TRAP_NUM_SINGLE_MAX + _TRAP_NUM_NATURE)*_DTIME) < pWork->pcRadarTimer){
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

void UgTrapRecvNatureRadarStart(void)
{
    _EVENT_PCRADAR_WORK* mdw;

    if(_pCTW->pPcRadarWork){  // ��d�N���֎~
        return;
    }
    if(_pCTW->pPcRadar){
        return;
    }

    mdw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_PCRADAR_WORK));
    MI_CpuFill8(mdw, 0, sizeof(_EVENT_PCRADAR_WORK));
    CommSendFixData(CF_TRAP_RADAR_REQ);  // �T�[�o�[�ɍ��W���˗�

    _pCTW->pPcRadarWork = mdw;
    _pCTW->pPcRadar = TCB_Add(_GMEVENT_PcRadar , mdw,TCB_PRIORITY_NORMAL);


}

//--------------------------------------------------------------
/**
 * �p�\�R�����[�_�[�G���h
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgTrapRecvNatureRadarEnd(void)
{
    if(_pCTW->pPcRadar){
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        G2_BlendNone();
        GX_SetMasterBrightness(BRIGHTNESS_NORMAL);
        TCB_Delete(_pCTW->pPcRadar);
        sys_FreeMemoryEz(_pCTW->pPcRadarWork);
        _pCTW->pPcRadar=NULL;
        _pCTW->pPcRadarWork=NULL;
    }
}

//--------------------------------------------------------------
/**
 * �p�\�R������㩃��[�_�[�̖₢���킹������
 * @param    index
 * @retval   Z���W
 */
//--------------------------------------------------------------

void UgTrapRecvNatureRadar(int netID, int size, void* pData, void* pWork)
{
    if(_pCTW->radarTrapIndex[netID] == 0){
        _pCTW->radarTrapIndex[netID] = 1;
    }
}

//--------------------------------------------------------------
/**
 * 㩃��[�_�[�𑗐M����
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

static void _trapRecvNatureRadarFunc(void)
{
    int i,sendNo = 0;


    for(i = 0;i < COMM_MACHINE_MAX;i++){
        int index = _pCTW->radarTrapIndex[i] - 1;
        if(_pCTW->radarTrapIndex[i]){
            while(1){
                TrapInfo* pTrap = _pCTW->pTrapTbl[index];
                if(pTrap && (pTrap->trapType != _TRAP_TYEP_INVALID)){
                    int trapNetID = _getTrapNetID(pTrap);
                    if((trapNetID == i) || (trapNetID >= COMM_MACHINE_MAX)){
                        _RESULT_TRAP_RADAR tr;
                        tr.xpos = pTrap->xpos;
                        tr.zpos = pTrap->zpos;
                        tr.netID = i;
                        CommSendFixSizeData_ServerSide(CF_TRAP_RADAR_ANS, &tr);
                        _pCTW->radarTrapIndex[i] = index + 2;
                        break;
                    }
                }
                index++;
                if(index >= _TRAP_NUM_MAX){
                    _pCTW->radarTrapIndex[i] = 0; // ���M�I��
                    break;
                }
                if(index == _pCTW->radarTrapIndex[i] - 1){
                    break;
                }
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * �T�[�o��������㩍��W�𑗂�Ԃ��Ă��炤
 * @param    pData   _RESULT_TRAP_RADAR
 * @retval   none
 */
//--------------------------------------------------------------

void UgTrapRecvNatureRadarPos(int netID, int size, void* pData, void* pWork)
{
    _RESULT_TRAP_RADAR* pTr = pData;

    if(_pCTW->pPcRadarWork==NULL){
        return;
    }

    if(pTr->netID == CommGetCurrentID()){
        MI_CpuCopy8(pData,&_pCTW->pPcRadarWork->pcRadar[_pCTW->pPcRadarWork->pcRadarIndex],
                    sizeof(_RESULT_TRAP_RADAR));
        _pCTW->pPcRadarWork->pcRadarIndex++;
        if(_pCTW->pPcRadarWork->pcRadarIndex >= (_TRAP_NUM_SINGLE_MAX + _TRAP_NUM_NATURE)){
            _pCTW->pPcRadarWork->pcRadarIndex=0;
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

int UgTrapGetNatureTrapRadarSize(void)
{
    return sizeof(_RESULT_TRAP_RADAR);
}


///---------------------diggy

enum{
    _GIDDY_INIT,
    _GIDDY_FUNC,
    _GIDDY_END,
};

//--------------------------------------------------------------
/**
 * @brief    ������E�͂�Ă���I��点��֐�
 * @param    event  �C�x���g�R���g���[���[
 * @retval   �I�������TRUE
 */
//--------------------------------------------------------------

static void _endClientGiddy(int netID,BOOL bGoods)
{
    if(CommGetCurrentID() == netID){
        if(_pCTW->pTCBWork){
            _EVENT_GIDDY_WORK * mdw = _pCTW->pTCBWork;
            mdw->seq = _GIDDY_END;
            _pCTW->pTCBWork = NULL;
        }
    }
}

static void _forceEndClientGiddy(int netID,BOOL bGoods)
{
    if(_pCTW->pTCBWork){
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        G2_BlendNone();
        GX_SetMasterBrightness(BRIGHTNESS_NORMAL);
        CommResetKeyRandMode();
        TCB_Delete(_pCTW->pRadar);
        sys_FreeMemoryEz(_pCTW->pTCBWork);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
    }
}

//--------------------------------------------------------------
/**
 * @brief    ������E�͂�Ă�̃C�x���g�֐�
 * @param    event  �C�x���g�R���g���[���[
 * @retval   �I�������TRUE
 */
//--------------------------------------------------------------

static void _GMEVENT_Giddy(TCB_PTR tcb, void *work)
{
    _EVENT_GIDDY_WORK * mdw = work;
    int i;

    switch(mdw->seq){
      case _GIDDY_INIT:
        mdw->startTime++;

        if(mdw->startTime==1){
            mdw->index = _trapStartSet();
        }
        else if(mdw->startTime==2){
            ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                    PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        }
        else if(mdw->startTime==4){
            ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,
                                    PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        }
        if(_TRAP_START_PAUSE_TIME < mdw->startTime){
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            mdw->seq = _GIDDY_FUNC;
            if(mdw->bRev){
                CommSetKeyReverseMode();
            }
            else{
                CommSetKeyRandMode();
            }
            CommPlayerHoldBitEnd(_HOLD_TRAP);
        }
        break;
      case _GIDDY_FUNC:
        // �����������̓T�[�o�[�ŊǗ�
        break;
      case _GIDDY_END:
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        G2_BlendNone();
        GX_SetMasterBrightness(BRIGHTNESS_NORMAL);
        CommResetKeyRandMode();
        sys_FreeMemoryEz(work);
        TCB_Delete(tcb);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
        //     return TRUE;
        break;
    }
    //return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief    ������E�͂�Ă��㩏�����
 * @param    bRev   ���]�Ȃ�TRUE
 * @retval   none
 */
//--------------------------------------------------------------

static void _trapGiddyInitialize(BOOL bRev)
{
    int i;
    _EVENT_GIDDY_WORK* mdw;

    mdw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_GIDDY_WORK));
    MI_CpuClear8(mdw, sizeof(_EVENT_GIDDY_WORK));
    mdw->seq = 0;
    mdw->bRev = bRev;  // ���������]���̃t���O
    mdw->startTime = 0;
    _pCTW->pTCBWork = mdw;
    _pCTW->pRadar = TCB_Add(_GMEVENT_Giddy,mdw,TCB_PRIORITY_NORMAL);
    CommPlayerHoldBit(_HOLD_TRAP);
    //CommPlayerHold();
}

///---------------------hole


//--------------------------------------------------------------
/**
 * @brief    ���Ȃ��I��点��֐�
 * @param    event  �C�x���g�R���g���[���[
 * @retval   �I�������TRUE
 */
//--------------------------------------------------------------

static void _endClientHole(int netID,BOOL bGoods)
{
    if(CommGetCurrentID() == netID){
        if(_pCTW->pTCBWork){
            _EVENT_HOLE_WORK * mdw = _pCTW->pTCBWork;
            Player_VecPosYSet( _pCTW->pFSys->player,0);
            TCB_Delete(_pCTW->pRadar);
            sys_FreeMemoryEz(mdw);
            _pCTW->pRadar = NULL;
            _pCTW->pTCBWork = NULL;
        }
    }
}


//--------------------------------------------------------------
/**
 * @brief    ���Ȃ������I�ɏI��点��֐�  ���h������
 * @param    event  �C�x���g�R���g���[���[
 * @retval   �I�������TRUE
 */
//--------------------------------------------------------------

static void _endForceClientHole(int netID, BOOL bGoods)
{
    if(_pCTW->pTCBWork){
        _EVENT_HOLE_WORK * mdw = _pCTW->pTCBWork;
        if(mdw->eoa){
            EOA_Delete(mdw->eoa);
            mdw->eoa=NULL;
        }
        if(mdw->bGoodsTrap && bGoods){
            _goodsTrapReverse(mdw->dir);
        }
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        G2_BlendNone();
        GX_SetMasterBrightness(BRIGHTNESS_NORMAL);
        Player_VecPosYSet( _pCTW->pFSys->player,0);
        TCB_Delete(_pCTW->pRadar);
        sys_FreeMemoryEz(mdw);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
    }
}


//==============================================================================
/**
 * ���Ȃ�㩂��I���̊J�n������
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _priEndClientHole(int victimNetID)
{
    if(CommGetCurrentID() == victimNetID){
        if(_pCTW->pTCBWork){
            _EVENT_HOLE_WORK * mdw = _pCTW->pTCBWork;
            mdw->seq = _HOLE_ENDING;
            Snd_SePlay(SE_TRAP_HOLE_FALL_OUT);
        }
    }
}


//--------------------------------------------------------------
/**
 * @brief    ���Ȃ̃C�x���g�֐�
 * @param    event  �C�x���g�R���g���[���[
 * @retval   �I�������TRUE
 */
//--------------------------------------------------------------

static void _GMEVENT_Hole(TCB_PTR tcb, void *work)
{
    _EVENT_HOLE_WORK * mdw = work;
    int i,xpos,zpos;
    const s8 jumpTbl[]={-1,3,7,11,15,14,13,12,11,9,7,5,3,1,-10};

    switch(mdw->seq){
      case _INIT:
        mdw->index = _trapStartSet();
        mdw->timer = 0;
        mdw->seq++;
        break;
      case _CHAR_READ:
        ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        mdw->seq++;
        break;
      case _PAL_READ:
        mdw->seq++;
        break;
      case _CELL_READ:
        ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        mdw->seq++;
        break;
      case _ANIM_READ:
        mdw->timer++;
        if(mdw->timer > 60){
            mdw->seq++;
            mdw->timer = 0;
        }
        else if(_goodsTrapReverseCheck( mdw->dir,TRUE )){
            mdw->seq++;
            mdw->timer = 0;
        }
        break;
      case _SET_CLACT:
      case _MESSAGE_LOOP:
        mdw->timer++;
        if(mdw->timer > 30){
            CommPlayerHoldBitEnd(_HOLD_TRAP);
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            mdw->seq = _FUNC;
            xpos = Player_NowGPosXGet( _pCTW->pFSys->player );
            zpos = Player_NowGPosZGet( _pCTW->pFSys->player );
            if(!mdw->bBig){
                mdw->eoa = FE_Hole_Add(_pCTW->pFSys,xpos,zpos,
                                       2, EOA_HOLE_NO);//_pCTW->trapMarkModel[EOA_HOLE_NO].pModel);
                Player_VecPosYSet( _pCTW->pFSys->player, -2*FX32_ONE);  // ����
            }
            else{
                mdw->eoa = FE_Hole_Add(_pCTW->pFSys,xpos,zpos,
                                       3, EOA_HOLE_NO);//_pCTW->trapMarkModel[EOA_HOLE_NO].pModel);
                Player_VecPosYSet( _pCTW->pFSys->player, -3*FX32_ONE);
            }
        }
        break;
      case _FUNC:
        // �����������̓T�[�o�[�ŊǗ�
        { // �����������
            int dir = Player_DirGet( _pCTW->pFSys->player );
            if(mdw->dispDir != dir){
                Snd_SePlay(SE_TRAP_HOLE_DIR);
            }
            mdw->dispDir = dir;
        }
        mdw->startTime=0;
        break;
      case _ENDCMD:
        break;
      case _END:
        Player_VecPosYSet( _pCTW->pFSys->player,0);
        sys_FreeMemoryEz(work);
        TCB_Delete(tcb);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
        break;
      case _END2:
        break;
      case _GOODS_END_START:
        mdw->bGoodsTrap = FALSE;
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        _goodsTrapReverse(mdw->dir);
        mdw->timer=0;
        mdw->seq = _GOODS_END_WALK;
        break;
      case _GOODS_END_WALK:
        mdw->timer++;
        if(_goodsTrapReverseCheck( mdw->dir,FALSE ) || (mdw->timer > 60)){
            CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
            mdw->seq = _ENDCMD;
        }
        break;
      case _HOLE_ENDING:
        if(-10 != jumpTbl[mdw->startTime]){
            Player_VecPosYSet( _pCTW->pFSys->player,jumpTbl[mdw->startTime]*FX32_ONE);
            mdw->startTime++;
            if(mdw->startTime == 5){
                if(mdw->eoa){
                    EOA_Delete(mdw->eoa);
                    mdw->eoa=NULL;
                }
                if(mdw->bGoodsTrap){
                    mdw->seq = _GOODS_END_START;
                }
                else{
                    CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
                    mdw->seq = _END;
                }
            }
        }
        break;
    }
}

//--------------------------------------------------------------
/**
 * @brief    ���Ȃ�㩏�����
 * @param    bBig   �������ȂȂ�TRUE
 * @retval   none
 */
//--------------------------------------------------------------

static void _trapHoleInitialize(BOOL bBig,BOOL bGoodsTrap, int dir)
{
    int i;
    _EVENT_HOLE_WORK* mdw;

    mdw = sys_AllocMemory(HEAPID_FIELD, sizeof(_EVENT_HOLE_WORK));
    MI_CpuClear8(mdw, sizeof(_EVENT_HOLE_WORK));
    mdw->seq = 0;
    mdw->bBig = bBig;  // �傫�������ǂ���
    mdw->startTime = 0;
    mdw->bGoodsTrap = bGoodsTrap;
    mdw->dispDir = Player_DirGet( _pCTW->pFSys->player );
    mdw->dir = dir;
    _pCTW->pTCBWork = mdw;
    _pCTW->pRadar = TCB_Add(_GMEVENT_Hole,mdw,TCB_PRIORITY_NORMAL);
}


//==============================================================================
/**
 * ���Ȃ�㩂��J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startClientHole(int victimNetID,BOOL bGoodsTrap, int dir)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_HOLE);
    if(CommGetCurrentID() == victimNetID){
        _trapHoleInitialize(FALSE,bGoodsTrap,dir);
    }
}

//==============================================================================
/**
 * �������Ȃ�㩂��J�n����
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _startClientBigHole(int victimNetID,BOOL bGoodsTrap, int dir)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_HOLE);
    if(CommGetCurrentID() == victimNetID){
        _trapHoleInitialize(TRUE,bGoodsTrap,dir);
    }
}

//==============================================================================
/**
 * �������Ȃ�㩂��I������
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

static void _exitServerHole(int victimNetID)
{
    CommPlayerResetCondition(victimNetID);
    CommPlayerResetHole(victimNetID);
}

static void _startServerHole(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_HOLE);
    CommPlayerSetHole(victimNetID,_HOLE_STEP_NUM);
}

static void _startServerBigHole(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_HOLE);
    CommPlayerSetHole(victimNetID,_BIGHOLE_STEP_NUM);
}




//---------------blossoms

//--------------------------------------------------------------
/**
 * �Ԃт��u���ꏊ���e�[�u���Ɨ����Ō��߂�
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------
/*
static u8 _pictureTableA[]={2,3,3,2,2,4,4,2,2,3,3,2};
static u8 _pictureTableB[]={3,2,2,3,3,2,2,3,4,2,2,4};
static u8 _pictureTableC[]={3,2,3,3,2,3,2,3,3,3,3,2};
*/
static void _dirtyBlossomsAddPetal(_EVENT_DIRTYBLOSSOMS_WORK * mdw)
{
    int i, j , index, x,z,num;
    u8* pTable=NULL;
    MATHRandContext32 sRand;
    const int _WIDTH = 256;
    const int _HEIGHT = 192;

    CommRandSeedInitialize(&sRand);

    index = 0;
    for(i = 0; i < mdw->num; i++){
        mdw->oamGrid[i].xpos = MATH_Rand32(&sRand, _WIDTH);
        mdw->oamGrid[i].zpos = MATH_Rand32(&sRand, _HEIGHT);
        mdw->turntime[i] = MATH_Rand32(&sRand,0xffff);
    }



#if 0

    int i, j , index, x,z;
    u8* pTable=NULL;
    MATHRandContext32 sRand;
    const int _WIDTH = 64;
    const int _HEIGHT = 60;

    CommRandSeedInitialize(&sRand);
    switch(MATH_Rand32(&sRand, 2)){
      case 0:
        pTable = _pictureTableA;
        break;
      case 1:
        pTable = _pictureTableB;
        break;
      case 2:
        pTable = _pictureTableC;
        break;
    }

    index = 0;
    for(i = 0; i < 12; i++){
        x = i % 4;
        z = i / 4;
        for(j = 0; j < pTable[i]; j++){
            mdw->oamGrid[index].xpos = MATH_Rand32(&sRand, _WIDTH) + x * _WIDTH;
            mdw->oamGrid[index].zpos = MATH_Rand32(&sRand, _HEIGHT) + z * _HEIGHT;
            mdw->turntime[index] = MATH_Rand32(&sRand,0xffff);
            index++;
        }
    }
#endif

}

//--------------------------------------------------------------
/**
 * �Ԃт�̕��C�x���g���s
 * @param
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _GMEVENT_DirtyBlossoms(TCB_PTR tcb, void *work)
//static BOOL _GMEVENT_DirtyBlossoms(GMEVENT_CONTROL* event)
{
    _EVENT_DIRTYBLOSSOMS_WORK * mdw = work;
    int i,pic;

    switch(mdw->seq){
      case _INIT:
        mdw->index = _trapStartSet();
        mdw->timer = 0;
        _initCellActor();
        mdw->seq++;
        break;
      case _CHAR_READ: 	//chr�ǂݍ���
        ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        if(_pCTW->nowTrapType == UG_TRAPTYPE_DIRTY_BLOSSOMS){
            pic = NARC_ug_trap_blossoms_NCGR;
        }
        else{
            pic = NARC_ug_trap_ug_ef_leaf_NCGR;
        }
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES] =
            CLACT_U_ResManagerResAddArcChar(_pCTW->resMan[MAIN_RES][CLACT_U_CHAR_RES],
                                            ARC_UG_TRAP_GRA, pic,
                                            0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD);
        mdw->seq++;
        break;
      case _PAL_READ: 	//pal�ǂݍ���
        if(_pCTW->nowTrapType == UG_TRAPTYPE_DIRTY_BLOSSOMS){
            pic = NARC_ug_trap_blossoms_NCLR;
        }
        else{
            pic = NARC_ug_trap_ug_ef_leaf_NCLR;
        }
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES] =
            CLACT_U_ResManagerResAddArcPltt(_pCTW->resMan[MAIN_RES][CLACT_U_PLTT_RES],
                                            ARC_UG_TRAP_GRA, pic,
                                            0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAPID_FIELD);
        mdw->seq++;
        break;
      case _CELL_READ:	//cell�ǂݍ���
        ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        if(_pCTW->nowTrapType == UG_TRAPTYPE_DIRTY_BLOSSOMS){
            pic = NARC_ug_trap_blossoms_NCER;
        }
        else{
            pic = NARC_ug_trap_ug_ef_leaf_NCER;
        }
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CELL_RES] =
            CLACT_U_ResManagerResAddArcKindCell(_pCTW->resMan[MAIN_RES][CLACT_U_CELL_RES],
                                                ARC_UG_TRAP_GRA, pic,
                                                0, 0, CLACT_U_CELL_RES,HEAPID_FIELD);
        mdw->seq++;
        break;
      case _ANIM_READ:	//�����֐���anim�ǂݍ���
        if(_pCTW->nowTrapType == UG_TRAPTYPE_DIRTY_BLOSSOMS){
            pic = NARC_ug_trap_blossoms_NANR;
        }
        else{
            pic = NARC_ug_trap_ug_ef_leaf_NANR;
        }
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CELLANM_RES] =
            CLACT_U_ResManagerResAddArcKindCell(_pCTW->resMan[MAIN_RES][CLACT_U_CELLANM_RES],
                                                ARC_UG_TRAP_GRA, pic,
                                                0, 0, CLACT_U_CELLANM_RES,HEAPID_FIELD);
        mdw->seq++;
        break;
      case _SET_CLACT:
        // ���\�[�X�}�l�[�W���[����]��
        // Chara�]��
        CLACT_U_CharManagerSetCharModeAdjustAreaCont( _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES] );
        // �p���b�g�]��  CLACT_U_PlttManagerSetCleanArea
        CLACT_U_PlttManagerSetCleanArea( _pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES] );
        _setCellActor(mdw->num);
        _dirtyBlossomsAddPetal(mdw); // �z�u�v�Z
        mdw->seq++;
        break;
      case _MESSAGE_LOOP:
            mdw->timer++;
            if(mdw->timer > 30){
                ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV,BRIGHTNESS_NORMAL,
                                        PLANEMASK_BG0,MASK_MAIN_DISPLAY);
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_76,FALSE,NULL);
                mdw->seq = _FUNC;
                mdw->msgTimer = 0;
            }
        break;
      case _FUNC:
        if(_procDirtyBlossoms(_pCTW->pFSys->bgl,mdw)){
            if(mdw->bGoodsTrap){
                mdw->seq = _GOODS_END_START;
            }
            else{
                CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
                mdw->seq = _ENDCMD;
            }
        }
        if(mdw->msgTimer < _MSG_TIME){
            mdw->msgTimer++;
            if(mdw->msgTimer == _MSG_TIME){
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            }
        }
        break;
      case _ENDCMD:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        break;
      case _END:
        _endClientForceDirtyBlossoms(CommGetCurrentID(),mdw->bGoodsTrap);
        break;
      case _GOODS_END_START:
        mdw->bGoodsTrap=FALSE;
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        _goodsTrapReverse(mdw->dir);
        mdw->timer=0;
        mdw->seq = _GOODS_END_WALK;
        break;
      case _GOODS_END_WALK:
        mdw->timer++;
        if(mdw->timer > 8){
            CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
            mdw->seq = _ENDCMD;
        }
        break;
    }
}

//--------------------------------------------------------------
/**
 * @brief    �Ԃт�̕��I������
 * @param    victimNetID ����
 * @retval   none
 */
//--------------------------------------------------------------
/*
static void _endClientDirtyBlossoms(int victimNetID,BOOL bGoods)
{
    if(_pCTW->pTCBWork){
        _EVENT_DIRTYBLOSSOMS_WORK* wk = _pCTW->pTCBWork;
        wk->seq = _END;
        _pCTW->pTCBWork = NULL;
    }
}

*/
//--------------------------------------------------------------
/**
 * @brief    �Ԃт�̕��I������
 * @param    victimNetID ����
 * @retval   none
 */
//--------------------------------------------------------------

static void _endClientForceDirtyBlossoms(int victimNetID,BOOL bGoods)
{
    if(_pCTW->pTCBWork){
        _EVENT_DIRTYBLOSSOMS_WORK* wk = _pCTW->pTCBWork;
//        if(wk->bGoodsTrap){
        if(wk->bGoodsTrap && bGoods){
            _goodsTrapReverse(wk->dir);
        }
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        _endCellActor(wk->num);
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        TCB_Delete(_pCTW->pRadar);
        sys_FreeMemoryEz(_pCTW->pTCBWork);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
    }
}


//--------------------------------------------------------------
/**
 * �Ԃт�̕�������
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _dirtyBlossomsInitialize(FIELDSYS_WORK* pFSys, BOOL bGoodsTrap, int dir)
{
    int i;
    _EVENT_DIRTYBLOSSOMS_WORK* mdw;

    mdw = sys_AllocMemory(HEAPID_FIELD, sizeof(_EVENT_DIRTYBLOSSOMS_WORK));
    MI_CpuFill8(mdw, 0, sizeof(_EVENT_DIRTYBLOSSOMS_WORK));
    mdw->bGoodsTrap = bGoodsTrap;
    mdw->pFSys = pFSys;
    if(_pCTW->nowTrapType == UG_TRAPTYPE_DIRTY_BLOSSOMS){
        mdw->num = _CLACT_BLOSSOMS_OAMNUM;
    }
    else{
        mdw->num = _CLACT_LEAF_OAMNUM;
    }
    mdw->dir = dir;

    _pCTW->pTCBWork = mdw;
    _pCTW->pRadar = TCB_Add(_GMEVENT_DirtyBlossoms,mdw,TCB_PRIORITY_NORMAL);
    
//    _pCTW->pEvent = FieldEvent_Set(_pCTW->pFSys, _GMEVENT_DirtyBlossoms, mdw);
}

//------------------------------------------------------------------
/**
 * 㩗p�Z���A�N�^�[������
 * @param   none
 * @retval  none
 */
//------------------------------------------------------------------

static void _initCellActor(void)
{
    int i;
    // �Z���A�N�^�[������
    _pCTW->clactSet = CLACT_U_SetEasyInit( _CLACT_OAMNUM, &_pCTW->renddata, HEAPID_FIELD );

    CLACT_U_SetSubSurfaceMatrix( &_pCTW->renddata, SUB_SURFACE_X, SUB_SURFACE_Y*2 );

    //���\�[�X�}�l�[�W���[������
    for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
        _pCTW->resMan[MAIN_RES][i] = CLACT_U_ResManagerInit(2, i, HEAPID_FIELD);
    }
}

//------------------------------------------------------------------
/**
 * 㩗p�Z���A�N�^�[�I������
 * @param   none
 * @retval  none
 */
//------------------------------------------------------------------

static void _endCellActor(int oamNum)
{
    int i;

    for(i = 0; i < oamNum ; i++){
        if(_pCTW->clActWork[i]!=NULL){
            CLACT_Delete(_pCTW->clActWork[i]);
            _pCTW->clActWork[i] = NULL;
        }
    }
    // �L�����]���}�l�[�W���[�j��
    if(_pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES]){
        if(CheckCharID(CLACT_U_ResManagerGetResObjID(_pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES]))){
            CLACT_U_CharManagerDelete(_pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES]);
        }
    }
    _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES]=NULL;
    // �p���b�g�]���}�l�[�W���[�j��
    if(_pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES]){
        if(CheckPlttID(CLACT_U_ResManagerGetResObjID(_pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES]))){
            CLACT_U_PlttManagerDelete(_pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES]);
        }
    }
    _pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES]=NULL;
    // �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
    for(i=0;i < CLACT_RESOURCE_NUM ; i++){
        if(_pCTW->resMan[MAIN_RES][i])
            CLACT_U_ResManagerDelete(_pCTW->resMan[MAIN_RES][i]);
        _pCTW->resMan[MAIN_RES][i]=NULL;
    }
    // �Z���A�N�^�[�Z�b�g�j��
    if(_pCTW->clactSet)
        CLACT_DestSet(_pCTW->clactSet);
    _pCTW->clactSet=NULL;
}

//------------------------------------------------------------------
/**
 * 㩃Z���A�N�^�[�o�^
 * @param   none
 * @retval  none
 */
//------------------------------------------------------------------
static void _setCellActor(int num)
{
    // �Z���A�N�^�[�w�b�_�쐬

    CLACT_U_MakeHeader(&_pCTW->clActHeader_s,
                       0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
                       0, 0,
                       _pCTW->resMan[MAIN_RES][CLACT_U_CHAR_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_PLTT_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_CELL_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_CELLANM_RES],
                       NULL,NULL);

    {
        //�o�^���i�[
        CLACT_ADD add;
        int i;

        add.ClActSet	= _pCTW->clactSet;
        add.ClActHeader	= &_pCTW->clActHeader_s;

        add.mat.x		= FX32_CONST(32) ;
        add.mat.y		= FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���iMAIN�����H�ASUB����H�j
        add.mat.z		= 0;
        add.sca.x		= FX32_ONE;
        add.sca.y		= FX32_ONE;
        add.sca.z		= FX32_ONE;
        add.rot			= 0;
        add.pri			= 0;
        add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
        add.heap		= HEAPID_FIELD;

        //�Z���A�N�^�[�\���J�n

        // ���ʗp
        for(i = 0; i < num ; i++){
            add.mat.x = FX32_ONE*300;
            add.mat.y = FX32_ONE*300;
            _pCTW->clActWork[i] = CLACT_Add(&add);
            CLACT_AnmChg( _pCTW->clActWork[i],  0 );
            CLACT_SetAnmFlag(_pCTW->clActWork[i], 0);
            CLACT_AnmFrameSet(_pCTW->clActWork[i],0);
            CLACT_BGPriorityChg(_pCTW->clActWork[i],1);
        }
    }
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_ON);	//OBJ�ʂn�m
    GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
}

//--------------------------------------------------------------
/**
 * @brief   CELLACTOR�p�[�c����
 * @param   index
 * @return  none
 */
//--------------------------------------------------------------

static void _delCellActor(int index)
{

    if(_pCTW->clActWork[index]){
        CLACT_Delete(_pCTW->clActWork[index]);
        _pCTW->clActWork[index] = NULL;
    }
}

//--------------------------------------------------------------
/**
 * @brief   �Ԃт�anim�ʒu����
 * @param   none
 * @return  none
 */
//--------------------------------------------------------------
static void _dartyBlossomsPos(int index,_EVENT_DIRTYBLOSSOMS_WORK* mdw, int pow)
{
    void* heap;
    GF_CAMERA_PTR camera_ptr;
    void *resource;
    VecFx32 tmpVex;
    fx32 ansx,ansz;
    int x = mdw->oamGrid[index].xpos;
    int y = mdw->oamGrid[index].zpos;

    if(pow == 0){
        mdw->turntime[index] += 0x400;  // ���鎞�ԂƂ������p�x�Ƃ�����
    }
    ansx = FX_Mul(FX_SinIdx(mdw->turntime[index]) , 4 * FX32_ONE + FX32_ONE / 2);
    ansz = FX_Mul(FX_CosIdx(mdw->turntime[index]) , 2 * FX32_ONE + FX32_ONE / 2);
    ansz = MATH_ABS(ansz);

    if(_pCTW->clActWork[index]){
        tmpVex.x = FX32_ONE * (x) + ansx;
        tmpVex.y = FX32_ONE * (y) + ansz;
        CLACT_SetMatrix(_pCTW->clActWork[index], &tmpVex);
    }
}

//------------------------------------------------------------------
/**
 * @brief   �}�C�N�蓮�擾�̃R�[���o�b�N
 * @param   none
 * @retval  none
 */
//------------------------------------------------------------------

static s8 _mic ATTRIBUTE_ALIGN(32);  // �A���C�����g��؂��Ă����Ȃ��Ƃ����Ȃ�����

static void _micCallBack( MICResult result, void* arg )
{
    if(result == MIC_RESULT_SUCCESS){
        _pCTW->mic = _mic;
    }
}

//--------------------------------------------------------------
/**
 * @brief    �Ԃт�̕�����
 * @param    bgl    GF_BGL_INI
 * @param    mdw    _EVENT_DIRTYBLOSSOMS_WORK
 * @retval   ��������=TRUE
 */
//--------------------------------------------------------------
// �I�[�g�A�j���[�V�����t���[��
#define		CLACT_AUTO_ANM_FRAME		(FX32_ONE * 2)

static BOOL _procDirtyBlossoms(GF_BGL_INI * bgl, _EVENT_DIRTYBLOSSOMS_WORK* mdw)
{
    int i;
    int pow=0,pos, ans,delCnt,powPos;
    fx32 x,z,alpha;

    // �蓮�T���v�����O
    Snd_MicManualSampling(MIC_SAMPLING_TYPE_SIGNED_8BIT,&_mic,_micCallBack,NULL);

    {  // �����������̗��� �����߂�
        if(_pCTW->nowTrapType == UG_TRAPTYPE_DIRTY_BLOSSOMS){
            pow = abs(_pCTW->mic) / 33;  // ������R�R�ł����Ă���
            mdw->blowRing[ mdw->blowBase ] = pow;
        }
        else{
            pow = abs(_pCTW->mic) / 25;
            mdw->blowRing[ mdw->blowBase ] = pow;
        }
    }

    for(i = 0; i < mdw->num;i++){
        if(_pCTW->clActWork[i]){
            break;
        }
    }
    if(i == mdw->num){  // ����
        return TRUE;
    }
    for(i = 0; i < mdw->num;i++){// �����������ɂ��ړ�
        // �ړ���������
        if((mdw->oamGrid[i].xpos <= 0) || (mdw->oamGrid[i].xpos >= 256) ||
           (mdw->oamGrid[i].zpos <= 0) || (mdw->oamGrid[i].zpos >= 192)){
            _delCellActor(i);
            continue;
        }
        powPos = mdw->blowBase - mdw->blowPos[ i ];
        if(powPos < 0){
            powPos += _BLOW_FRAME;
        }
        pow = mdw->blowRing[ powPos ];
        x = mdw->oamGrid[i].xpos - 128;
        z = mdw->oamGrid[i].zpos - 96;
        x *= FX32_ONE;
        z *= FX32_ONE;
        alpha = FX_Mul(x , x) + FX_Mul(z , z);
        alpha = FX_Sqrt(alpha);


        if(pow == 0){   // ��~��  �ʒu����o��
            x = FX_Mul( FX_Div( alpha, (160 * FX32_ONE)), (_BLOW_FRAME-2) * FX32_ONE);
            mdw->blowPos[ i ] = FX_Whole(x);
        }
        else{
            fx32 x = mdw->oamGrid[i].xpos - 128;
            fx32 z = mdw->oamGrid[i].zpos - 96;
            if(z == 0){
                if(x < 0){
                    mdw->oamGrid[i].xpos -= pow;
                }
                else{
                    mdw->oamGrid[i].xpos += pow;
                }
            }
            else if(x == 0){
                if(z < 0){
                    mdw->oamGrid[i].zpos -= pow;
                }
                else{
                    mdw->oamGrid[i].zpos += pow;
                }
            }
            else{
                {
                    u16 radIdx = FX_Atan2Idx(z , x);
                    alpha += pow * FX32_ONE;
                    ans = FX_Whole(FX_Mul(FX_SinIdx(radIdx) , alpha));
                    mdw->oamGrid[i].zpos = ans + 96;
                    ans = FX_Whole(FX_Mul(FX_CosIdx(radIdx) , alpha));
                    mdw->oamGrid[i].xpos = ans + 128;
                }
            }
        }
        _dartyBlossomsPos(i,  mdw, pow);
    }
    mdw->blowBase++;
    if(mdw->blowBase >= _BLOW_FRAME){
        mdw->blowBase = 0;
    }



    CLACT_Draw( _pCTW->clactSet );									// �Z���A�N�^�[�풓�֐�
    return FALSE;
}

//--------------------------------------------------------------
/**
 * 㩓��실�ʎ��s�֐�
 * @param    bgl  GF_BGL_INI
 * @retval   none
 */
//--------------------------------------------------------------

void UgTrapProcess(GF_BGL_INI* bgl)
{

    if(_pCTW->trapProc){
        _pCTW->trapProc(bgl);
    }
}

//--------------------------------------bubble

static int _bubbleNum(void)
{
    int max;
    
    if(_pCTW->nowTrapType == UG_TRAPTYPE_BUBBLE){
        max = _CLACT_BUBBLE_OAMNUM;
    }
    else{
        max = _CLACT_SUDS_OAMNUM;
    }
    return max;
}

//--------------------------------------------------------------
/**
 * �A��u���ꏊ���e�[�u���Ɨ����Ō��߂�
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

//static u8 _pictureTableA_Bubble[]={2,2,1,2,1,2,2,2,2,1,2,1};
static const int _BUBBLE_HALFSIZE[]={32,28,24};

static void _bubbleAddPetal(_EVENT_BUBBLE_WORK* mdw)
{
    int index, x,z,bigNum = 0,middleNum,size,max,id;
    MATHRandContext32 sRand;
    const int _WIDTH = 256;
    const int _HEIGHT = 192;

    CommRandSeedInitialize(&sRand);

    max = _bubbleNum();
    if(_pCTW->nowTrapType == UG_TRAPTYPE_BUBBLE){
        bigNum = MATH_Rand32(&sRand,2) + 1;
    }
    middleNum = MATH_Rand32(&sRand,3) + bigNum + 5;

    for(index = 0; index < max; index++){
        id = max - index - 1;
        if( index < bigNum){
            mdw->size[id] = 0;
        }
        else if(index < middleNum){
            mdw->size[id] = 1;
        }
        else{
            mdw->size[id] = 2;
        }
        size = _BUBBLE_HALFSIZE[mdw->size[id]];
        x = _WIDTH - size*2;
        z = _HEIGHT - size*2;
        mdw->oamGrid[id].xpos = (MATH_Rand32(&sRand, x) + size) * FX32_ONE;
        mdw->oamGrid[id].zpos = (MATH_Rand32(&sRand, z) + size) * FX32_ONE;
        mdw->dirIdx[id] = MATH_Rand32(&sRand,0xffff);
        mdw->scaletime[id] = MATH_Rand32(&sRand,0xffff);
    }
}

//--------------------------------------------------------------
/**
 * BUBBLE�C�x���g���s
 * @param
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _GMEVENT_Bubble(TCB_PTR tcb, void *work)
{
    _EVENT_BUBBLE_WORK* mdw = work;
    int i;

    switch(mdw->seq){
      case _INIT:
        mdw->index = _trapStartSet();
        mdw->timer = 0;
        _initCellActor();
        mdw->seq++;
        break;
      case _CHAR_READ: 	//chr�ǂݍ���
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES] =
            CLACT_U_ResManagerResAddArcChar(_pCTW->resMan[MAIN_RES][CLACT_U_CHAR_RES],
                                            ARC_UG_TRAP_GRA, NARC_ug_trap_bubble_NCGR,
                                            0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD);
        ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        mdw->seq++;
        break;
      case _PAL_READ: 	//pal�ǂݍ���
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES] =
            CLACT_U_ResManagerResAddArcPltt(_pCTW->resMan[MAIN_RES][CLACT_U_PLTT_RES],
                                            ARC_UG_TRAP_GRA, NARC_ug_trap_bubble_NCLR,
                                            0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAPID_FIELD);
        mdw->seq++;
        break;
      case _CELL_READ:	//cell�ǂݍ���
        ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CELL_RES] =
            CLACT_U_ResManagerResAddArcKindCell(_pCTW->resMan[MAIN_RES][CLACT_U_CELL_RES],
                                                ARC_UG_TRAP_GRA, NARC_ug_trap_bubble_NCER,
                                                0, 0, CLACT_U_CELL_RES,HEAPID_FIELD);
        mdw->seq++;
        break;
      case _ANIM_READ:	//�����֐���anim�ǂݍ���
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CELLANM_RES] =
            CLACT_U_ResManagerResAddArcKindCell(_pCTW->resMan[MAIN_RES][CLACT_U_CELLANM_RES],
                                                ARC_UG_TRAP_GRA, NARC_ug_trap_bubble_NANR,
                                                0, 0, CLACT_U_CELLANM_RES,HEAPID_FIELD);
        mdw->seq++;
        break;
      case _SET_CLACT:
        _bubbleAddPetal(mdw); // �z�u�v�Z
        _setCellActorBubble(mdw);
        mdw->seq++;
        break;
      case _MESSAGE_LOOP:
            mdw->timer++;
            if(mdw->timer > 30){
                GX_SetMasterBrightness(_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV);
                mdw->seq = _FUNC;
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_77,FALSE,NULL);
                mdw->msgTimer = 0;
                Snd_SePlay(SE_TRAP_BUBBLE);
            }
        break;
      case _FUNC:
        G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ,GX_BLEND_PLANEMASK_BG0, 14, 7);
        if(_procBubble(_pCTW->pFSys->bgl,mdw)){
            Snd_SeStopBySeqNo(SE_TRAP_BUBBLE,0);
            if(mdw->bGoodsTrap){
                mdw->seq = _GOODS_END_START;
            }
            else{
                CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
                mdw->seq = _ENDCMD;
            }
        }
        if(mdw->msgTimer < _MSG_TIME){
            mdw->msgTimer++;
            if(mdw->msgTimer == _MSG_TIME){
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            }
        }
        break;
      case _ENDCMD:
        Snd_SeStopBySeqNo(SE_TRAP_BUBBLE, 0);
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        break;
      case _END:
        mdw->seq = _END2;
        _endForceClientBubble(CommGetCurrentID(), mdw->bGoodsTrap);
        break;
      case _END2:
        break;
      case _GOODS_END_START:
        mdw->bGoodsTrap=FALSE;
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        _goodsTrapReverse(mdw->dir);
        mdw->timer=0;
        mdw->seq = _GOODS_END_WALK;
        break;
      case _GOODS_END_WALK:
        mdw->timer++;
        if(mdw->timer > 8){
            CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
            mdw->seq = _ENDCMD;
        }
        break;
    }
}

//--------------------------------------------------------------
/**
 * bubble������
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _bubbleInitialize(GF_BGL_INI * bgl,BOOL bGoodsTrap,int dir)
{
    int i;
    _EVENT_BUBBLE_WORK* mdw;

    mdw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_BUBBLE_WORK));
    MI_CpuFill8(mdw,0,sizeof(_EVENT_BUBBLE_WORK));
    mdw->bGoodsTrap = bGoodsTrap;

    _pCTW->pTCBWork = mdw;
    _pCTW->pRadar = TCB_Add(_GMEVENT_Bubble,mdw,TCB_PRIORITY_NORMAL);
    mdw->dir = dir;

//    _pCTW->pEvent = FieldEvent_Set(_pCTW->pFSys, _GMEVENT_Bubble, mdw);
}

//------------------------------------------------------------------
/**
 * 㩃Z���A�N�^�[�o�^
 * @param   none
 * @retval  none
 */
//------------------------------------------------------------------
static void _setCellActorBubble(_EVENT_BUBBLE_WORK* mdw)
{
    // ���\�[�X�}�l�[�W���[����]��
    // Chara�]��
    CLACT_U_CharManagerSetCharModeAdjustAreaCont( _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES] );
    // �p���b�g�]��  CLACT_U_PlttManagerSetCleanArea
    CLACT_U_PlttManagerSetCleanArea( _pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES] );
    // �Z���A�N�^�[�w�b�_�쐬
    CLACT_U_MakeHeader(&_pCTW->clActHeader_s,
                       0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
                       0, 0,
                       _pCTW->resMan[MAIN_RES][CLACT_U_CHAR_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_PLTT_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_CELL_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_CELLANM_RES],
                       NULL,NULL);

    {
        //�o�^���i�[
        CLACT_ADD add;
        int i;

        add.ClActSet	= _pCTW->clactSet;
        add.ClActHeader	= &_pCTW->clActHeader_s;

        add.mat.x		= FX32_CONST(32) ;
        add.mat.y		= FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���iMAIN�����H�ASUB����H�j
        add.mat.z		= 0;
        add.sca.x		= FX32_ONE;
        add.sca.y		= FX32_ONE;
        add.sca.z		= FX32_ONE;
        add.rot			= 0;
        add.pri			= 0;
        add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
        add.heap		= HEAPID_FIELD;

        //�Z���A�N�^�[�\���J�n

        // ���ʗp
        for(i = 0; i < _bubbleNum() ; i++){
            add.mat.x = FX32_ONE*300;
            add.mat.y = FX32_ONE*300;
            _pCTW->clActWork[i] = CLACT_Add(&add);
            CLACT_SetAffineParam(_pCTW->clActWork[i],CLACT_AFFINE_NORMAL);
            CLACT_AnmChg( _pCTW->clActWork[i], (mdw->size[i]*2));
            CLACT_SetAnmFlag(_pCTW->clActWork[i],1);
            CLACT_AnmFrameSet(_pCTW->clActWork[i], i*4 );
            CLACT_ObjModeSet(_pCTW->clActWork[i], GX_OAM_MODE_XLU );
            CLACT_BGPriorityChg(_pCTW->clActWork[i],1);
        }
    }
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_ON);	//OBJ�ʂn�m
    GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
}

//--------------------------------------------------------------
/**
 * @brief   �o�u���ʒu����
 * @param   none
 * @return  none
 */
//--------------------------------------------------------------
static void _bubblePos(int i,_EVENT_BUBBLE_WORK* mdw)
{
    void* heap;
    GF_CAMERA_PTR camera_ptr;
    void *resource;
    VecFx32 tmpVex;
    fx32 ans;
    fx16 sin;


    if(_pCTW->clActWork[i]){
        tmpVex.x = mdw->oamGrid[i].xpos;
        tmpVex.y = mdw->oamGrid[i].zpos;
        CLACT_SetMatrix(_pCTW->clActWork[i], &tmpVex);
        mdw->scaletime[i] += 0x250 + i*100;  // ���鎞��
        sin = FX_SinIdx(mdw->scaletime[i]) + FX32_ONE;
        ans = FX_Div(sin , (20*FX32_ONE) );
        tmpVex.x = FX32_ONE - ans;
        tmpVex.y = FX32_ONE - ans;
        tmpVex.z = FX32_ONE - ans;
        CLACT_SetScale(_pCTW->clActWork[i],&tmpVex);
    }
}

//--------------------------------------------------------------
/**
 * @brief    BUBBLE����
 * @param    bgl    GF_BGL_INI
 * @param    mdw    _EVENT_BUBBLE_WORK
 * @retval   ��������=TRUE
 */
//--------------------------------------------------------------

static BOOL _procBubble(GF_BGL_INI * bgl, _EVENT_BUBBLE_WORK* mdw)
{
    int i;
    int pow=0,pos, delCnt,powPos,size,zint,xint;
    fx32 x,z,alpha,ans;

    delCnt=0;
    for(i = 0; i < _bubbleNum(); i++){
        if(mdw->bEnd[i]==FALSE){
            _bubblePos(i, mdw);
        }
        else{
            delCnt++;
        }
    }
    if(delCnt == _bubbleNum()){  // ����
        return TRUE;
    }

    if(sys.tp_trg){
        for(i = 0; i < _bubbleNum() ;i++){
            if(mdw->bEnd[i]){
                continue;
            }
            x = sys.tp_x * FX32_ONE - mdw->oamGrid[i].xpos;
            z = sys.tp_y * FX32_ONE - mdw->oamGrid[i].zpos;
            ans = FX_Mul(x,x)+FX_Mul(z,z);
            ans = FX_Sqrt(ans);
            if((_BUBBLE_HALFSIZE[mdw->size[i]] * FX32_ONE) > ans){
                Snd_SePlay(UGT_SE_BUBBLE);
                CLACT_AnmChg( _pCTW->clActWork[i], mdw->size[i]*2+1); // �A�j���ύX
                mdw->bEnd[i]=TRUE;
                break;
            }
        }
    }
    for(i = 0; i < _bubbleNum();i++){// �ӂ��ӂ��ړ�
        if(mdw->bEnd[i]){
            continue;
        }
        // �ړ���������
        ans = FX_SinIdx(mdw->dirIdx[i]);
        mdw->oamGrid[i].zpos -= ans;
        ans = FX_CosIdx(mdw->dirIdx[i]);
        mdw->oamGrid[i].xpos += ans;
        size = _BUBBLE_HALFSIZE[mdw->size[i]];
        if(mdw->oamGrid[i].zpos < ((0+size)*FX32_ONE)){
            mdw->dirIdx[i] = 0xffff - mdw->dirIdx[i];
        }
        else if(mdw->oamGrid[i].zpos >= ((192-size)*FX32_ONE)){
            mdw->dirIdx[i] = 0xffff - mdw->dirIdx[i];
        }
        if(mdw->oamGrid[i].xpos < ((0+size)*FX32_ONE)){
            mdw->dirIdx[i] = 0xffff - (mdw->dirIdx[i] - 0x8000);
        }
        else if(mdw->oamGrid[i].xpos >= ((256-size)*FX32_ONE) ){
            mdw->dirIdx[i] = 0xffff - (mdw->dirIdx[i] - 0x8000);
        }
    }


    CLACT_Draw( _pCTW->clactSet );									// �Z���A�N�^�[�풓�֐�
    return FALSE;
}

//==============================================================================
/**
 * bubble㩂��J�n����
 * @param   victimNetID  㩔�Q��
 * @retval  none
 */
//==============================================================================

static void _startClientBubble(int victimNetID,BOOL bGoodsTrap, int dir)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
    if(CommGetCurrentID() == victimNetID){
        _bubbleInitialize(_pCTW->pFSys->bgl, bGoodsTrap, dir);
    }
}

//--------------------------------------------------------------
/**
 * BUBBLE�T�[�o�[�����J�n����
 * @param   victimNetID   㩔�Q��
 * @retval  none
 */
//--------------------------------------------------------------

static void _startServerBubble(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
}

//--------------------------------------------------------------
/**
 * @brief    babble�I������
 * @param    victimNetID ����
 * @retval   none
 */
//--------------------------------------------------------------
/*
static void _endClientBubble(int victimNetID,BOOL bGoods)
{
    if(_pCTW->pTCBWork){
        _EVENT_BUBBLE_WORK* wk = _pCTW->pTCBWork;
        wk->seq = _END;
        _pCTW->pTCBWork = NULL;
        OHNO_PRINT("㩋����I��\n");
    }
}
*/

//--------------------------------------------------------------
/**
 * @brief    babble�����I������
 * @param    victimNetID ����
 * @retval   none
 */
//--------------------------------------------------------------

static void _endForceClientBubble(int victimNetID,BOOL bGoods)
{
    if(_pCTW->pTCBWork){
        _EVENT_BUBBLE_WORK* wk = _pCTW->pTCBWork;
        Snd_SeStopBySeqNo(SE_TRAP_BUBBLE,0);
        if(wk->bGoodsTrap && bGoods){
//        if(wk->bGoodsTrap){
            _goodsTrapReverse(wk->dir);
        }
        G2_BlendNone();
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        GX_SetMasterBrightness(BRIGHTNESS_NORMAL);
        _endCellActor(_bubbleNum());
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        TCB_Delete(_pCTW->pRadar);
        sys_FreeMemoryEz(_pCTW->pTCBWork);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
    }
}


//--------------------------------------rock
//------------------------------------------------------------------
/**
 * 㩃Z���A�N�^�[�o�^
 * @param   none
 * @retval  none
 */
//------------------------------------------------------------------
static void _setCellActorRock(_EVENT_ROCK_WORK* mdw)
{
    // ���\�[�X�}�l�[�W���[����]��
    // Chara�]��
    CLACT_U_CharManagerSetCharModeAdjustAreaCont( _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES] );
    //    CLACT_U_CharManagerSetAreaCont( _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES] );

    // �p���b�g�]��  CLACT_U_PlttManagerSetCleanArea
    CLACT_U_PlttManagerSetCleanArea( _pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES] );
    // �Z���A�N�^�[�w�b�_�쐬
    CLACT_U_MakeHeader(&_pCTW->clActHeader_s,
                       0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
                       0, 0,
                       _pCTW->resMan[MAIN_RES][CLACT_U_CHAR_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_PLTT_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_CELL_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_CELLANM_RES],
                       NULL,NULL);

    {
        //�o�^���i�[
        CLACT_ADD add;
        int i;

        add.ClActSet	= _pCTW->clactSet;
        add.ClActHeader	= &_pCTW->clActHeader_s;

        add.mat.x		= FX32_CONST(32) ;
        add.mat.y		= FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���iMAIN�����H�ASUB����H�j
        add.mat.z		= 0;
        add.sca.x		= FX32_ONE;
        add.sca.y		= FX32_ONE;
        add.sca.z		= FX32_ONE;
        add.rot			= 0;
        add.pri			= 0;
        add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
        add.heap		= HEAPID_FIELD;

        //�Z���A�N�^�[�\���J�n

        // ���ʗp
        for(i = 0; i < _CLACT_ROCK_OAMNUM ; i++){
            add.mat.x = FX32_ONE*100;
            add.mat.y = FX32_ONE*100;
            _pCTW->clActWork[i] = CLACT_Add(&add);
            CLACT_AnmChg( _pCTW->clActWork[i], 2);
            CLACT_SetAnmFlag(_pCTW->clActWork[i], 1);
            CLACT_SetDrawFlag(_pCTW->clActWork[i], 0);
            CLACT_AnmFrameSet(_pCTW->clActWork[i], 0 );
            CLACT_DrawPriorityChg(_pCTW->clActWork[i],_CLACT_ROCK_OAMNUM - i);
            CLACT_BGPriorityChg(_pCTW->clActWork[i],1);
        }
    }
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_ON);	//OBJ�ʂn�m
    GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
}

//--------------------------------------------------------------
/**
 * @brief    �_���[�W�A�j���Đ�
 * @param    mdw    _EVENT_ROCK_WORK
 * @retval   none
 */
//--------------------------------------------------------------

static void _rockAnimLoad(_EVENT_ROCK_WORK* mdw,int id,int x,int y,int xadd,int yadd)
{
    mdw->partsX[id] = x;
    mdw->partsXAdd[id] = xadd;
    mdw->partsY[id] = y;
    mdw->partsYAdd[id] = yadd;
    CLACT_SetDrawFlag(_pCTW->clActWork[id], 1);
}

static void _damageAnim(_EVENT_ROCK_WORK* mdw, int damage)
{
    switch(damage){
      default:
      case 4:
        _rockAnimLoad(mdw,11, 105, mdw->yPos - 5,  2, -4);
        _rockAnimLoad(mdw,12, 140, mdw->yPos - 15, -2, -4);
        _rockAnimLoad(mdw,13, 135, mdw->yPos - 20  ,   -2, -2);
        _rockAnimLoad(mdw,14, 120, mdw->yPos -11,  2, 0);
        // �������܂P�T��
      case 3:
        _rockAnimLoad(mdw, 7, 128, mdw->yPos - 5, 3, -4);
        _rockAnimLoad(mdw, 8, 132, mdw->yPos - 15, -3, -4);
        _rockAnimLoad(mdw, 9, 112, mdw->yPos , 1, -2);
        _rockAnimLoad(mdw,10, 115, mdw->yPos +2, 1, -2);
      case 2:
        _rockAnimLoad(mdw, 4, 140, mdw->yPos - 10, 2, -3);
        _rockAnimLoad(mdw, 5, 140, mdw->yPos - 20, -2, -3);
        _rockAnimLoad(mdw, 6, 110, mdw->yPos , -1, -2);
      case 1:
        _rockAnimLoad(mdw, 2, 120, mdw->yPos - 30, -2, -3);
        _rockAnimLoad(mdw, 3, 100, mdw->yPos - 10, -2, -3);
      case 0:
        _rockAnimLoad(mdw, 1, 128, mdw->yPos - 30, 2, -3);
    }
}


static void _damageAnimLoop(_EVENT_ROCK_WORK* mdw)
{
    int i;
    VecFx32 tmpVex;

    for(i = 0;i < _CLACT_ROCK_OAMNUM;i++){
        if(mdw->partsXAdd[i] != 0){
            mdw->partsX[i] += mdw->partsXAdd[i];
            mdw->partsY[i] += mdw->partsYAdd[i];
            mdw->partsYAdd[i] += mdw->timer;
            tmpVex.x = mdw->partsX[i] * FX32_ONE;
            tmpVex.y = mdw->partsY[i] * FX32_ONE;
            CLACT_SetMatrix(_pCTW->clActWork[i], &tmpVex);
            if(mdw->partsY[i] > (mdw->yPos+35)){
                CLACT_SetDrawFlag(_pCTW->clActWork[i], 0);
                mdw->partsXAdd[i] = 0;
            }
        }
    }
}


//--------------------------------------------------------------
/**
 * @brief    ROCK����
 * @param    bgl    GF_BGL_INI
 * @param    mdw    _EVENT_ROCK_WORK
 * @retval   ��������=TRUE
 */
//--------------------------------------------------------------

static BOOL _procRock(GF_BGL_INI * bgl, _EVENT_ROCK_WORK* mdw)
{
    int i;
    int pow=0,pos,powPos,size,xpos,zpos;
    fx32 x,z,alpha,ans;
    VecFx32 tmpVex;

    enum{
        _ROCK_SHADOW_INIT,
        _ROCK_SHADOW,
        _ROCK_DOWN,
        _ROCK_BLOKEN,
        _ROCK_ANIM,
        _ROCK_ENDING,
        _ROCK_END,
    };

    switch(mdw->subSeq){
      case _ROCK_SHADOW_INIT:
        mdw->timer = 0;
        xpos = Player_NowGPosXGet( _pCTW->pFSys->player );
        zpos = Player_NowGPosZGet( _pCTW->pFSys->player );
        mdw->eoaShadow = FE_ScaleHole_Add(_pCTW->pFSys,xpos,zpos, 5, EOA_HOLE_NO);
        mdw->subSeq = _ROCK_SHADOW;
        Snd_SePlay(SE_TRAP_ROCK_SHADOW);
        break;
      case _ROCK_SHADOW:
        mdw->timer++;
        if(mdw->timer > 20){
            mdw->subSeq = _ROCK_DOWN;
            mdw->yPos = 0;
            mdw->yAdd = 5;
            CLACT_AnmChg( _pCTW->clActWork[0], 0);
        }
        break;
      case _ROCK_DOWN:
        tmpVex.x = 128 * FX32_ONE;
        tmpVex.y = mdw->yPos * FX32_ONE;
        CLACT_SetMatrix(_pCTW->clActWork[0], &tmpVex);
        CLACT_SetDrawFlag(_pCTW->clActWork[0], 1);
        if( mdw->yPos > 65){
            mdw->subSeq = _ROCK_BLOKEN;
            Snd_SePlay(SE_TRAP_ROCK_FALL);
            if(_pCTW->nowTrapType == UG_TRAPTYPE_ROCKFALL){
                mdw->damage = -1;
            }
            else{
                mdw->damage = 5;
            }
            if(mdw->eoaShadow){
                EOA_Delete(mdw->eoaShadow);
                mdw->eoaShadow=NULL;
            }
        }
        else{
            mdw->yPos += mdw->yAdd;
            mdw->yAdd += 3;
        }
        break;
      case _ROCK_BLOKEN:
        if(sys.tp_trg){
            x = (sys.tp_x - 128)*FX32_ONE ;
            z = (sys.tp_y - mdw->yPos)*FX32_ONE;
            ans = FX_Mul(x,x)+FX_Mul(z,z);
            ans = FX_Sqrt(ans);
            if( (48*FX32_ONE) > ans ){
                mdw->rot = 3;
                Snd_SePlay(UGT_SE_HUMMER);
                mdw->damage++;
                if((mdw->damage % 3) == 2){
                    int a = mdw->damage/3;
                    CLACT_U_CharManagerChg( mdw->rockCharRes[0], mdw->rockCharRes[a + 1] );
                    mdw->timer = 0;
                    mdw->subSeq = _ROCK_ANIM;
                }
            }
        }
        if(mdw->damage > 15){
            mdw->timer = 0;
            mdw->subSeq = _ROCK_ENDING;
            mdw->rot = 0;
        }
        if(mdw->rot != 0){
            if(mdw->rot < 0){
                mdw->rot++;
            }
            mdw->rot = 0 - mdw->rot;
        }
        tmpVex.x = (128 + mdw->rot) * FX32_ONE;
        tmpVex.y = mdw->yPos * FX32_ONE;
        CLACT_SetMatrix(_pCTW->clActWork[0], &tmpVex);
        break;
      case _ROCK_ANIM:  // ����A�j���[�V����
        if(mdw->timer == 0){
            _damageAnim(mdw,mdw->damage/3);
        }
        mdw->timer++;
        _damageAnimLoop(mdw);
        if(mdw->timer == 20){
            mdw->subSeq = _ROCK_BLOKEN;
        }
        if(mdw->rot != 0){
            if(mdw->rot < 0){
                mdw->rot++;
            }
            mdw->rot = 0 - mdw->rot;
        }
        tmpVex.x = (128 + mdw->rot) * FX32_ONE;
        tmpVex.y = mdw->yPos * FX32_ONE;
        CLACT_SetMatrix(_pCTW->clActWork[0], &tmpVex);
        break;
      case _ROCK_ENDING:
        if(mdw->timer == 0){
            Snd_SePlay(UGT_SE_BLOKEN);
            CLACT_U_CharManagerChg( mdw->rockCharRes[0], mdw->rockCharRes[6] );
            for(i = 1;i < 9;i++){
                CLACT_AnmChg( _pCTW->clActWork[i], 1);
                tmpVex.x = (70 + 12 * i ) * FX32_ONE;
                tmpVex.y = (mdw->yPos + 39 + i%2) * FX32_ONE;
                CLACT_SetMatrix(_pCTW->clActWork[i], &tmpVex);
                CLACT_SetDrawFlag(_pCTW->clActWork[i], 1);
            }

            CLACT_AnmChg( _pCTW->clActWork[10], 1);
            tmpVex.x = 100 * FX32_ONE;
            tmpVex.y = (mdw->yPos + 21) * FX32_ONE;
            CLACT_SetMatrix(_pCTW->clActWork[10], &tmpVex);
            CLACT_SetDrawFlag(_pCTW->clActWork[10], 1);
            CLACT_AnmChg( _pCTW->clActWork[11], 1);
            tmpVex.x = 122 * FX32_ONE;
            tmpVex.y = mdw->yPos  * FX32_ONE;
            CLACT_SetMatrix(_pCTW->clActWork[11], &tmpVex);
            CLACT_SetDrawFlag(_pCTW->clActWork[11], 1);

        }
        mdw->timer++;
//        tmpVex.x = 128 * FX32_ONE;
        tmpVex.x = (128 - (10 / 2) + (gf_rand() % 10)) * FX32_ONE;
        tmpVex.y = mdw->yPos * FX32_ONE;
        CLACT_SetMatrix(_pCTW->clActWork[0], &tmpVex);
        mdw->yPos += 1;

        if(mdw->timer % 8){
            CLACT_AnmChg( _pCTW->clActWork[0], 3 + mdw->timer / 8);
        }

        if(mdw->timer == 75){
            mdw->subSeq = _ROCK_END;
        }
        break;
      case _ROCK_END:
        if(mdw->eoaShadow){
            EOA_Delete(mdw->eoaShadow);
            mdw->eoaShadow=NULL;
        }
        CLACT_SetDrawFlag(_pCTW->clActWork[0], 0);
        return TRUE;
    }
    CLACT_Draw( _pCTW->clactSet );			// �Z���A�N�^�[�풓�֐�
    return FALSE;
}


static void _rockRscRead(_EVENT_ROCK_WORK* mdw)
{
    int file[]={
        NARC_ug_trap_ug_ef_r2_NCGR,
        NARC_ug_trap_ug_ef_r3_NCGR,
        NARC_ug_trap_ug_ef_r4_NCGR,
        NARC_ug_trap_ug_ef_r5_NCGR,
        NARC_ug_trap_ug_ef_r6_NCGR,
        NARC_ug_trap_ug_ef_r7_NCGR,
    };
    int id = mdw->timer - 1;

    if(id < (_ROCK_PATTERN_NUM-1)){
        mdw->rockCharRes[id+1] =
            CLACT_U_ResManagerResAddArcChar(_pCTW->resMan[MAIN_RES][CLACT_U_CHAR_RES],
                                            ARC_UG_TRAP_GRA, file[id],
                                            0, id + 1, NNS_G2D_VRAM_TYPE_2DMAIN,
                                            HEAPID_FIELD);
    }
}


static void _rockRscDelete(_EVENT_ROCK_WORK* mdw)
{
    int i;

    for(i = 1; i < _ROCK_PATTERN_NUM;i++){
        if(mdw->rockCharRes[i]){
            CLACT_U_ResManagerResDelete(_pCTW->resMan[MAIN_RES][CLACT_U_CHAR_RES], mdw->rockCharRes[i]);
        }
    }
}

//--------------------------------------------------------------
/**
 * ROCK�C�x���g���s
 * @param
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _GMEVENT_Rock(TCB_PTR tcb, void *work)
//static BOOL _GMEVENT_Rock(GMEVENT_CONTROL* event)
{
 //   FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork(event);
    _EVENT_ROCK_WORK* mdw = work;
    int i;

    switch(mdw->seq){
      case _INIT:
        mdw->index = _trapStartSet();
        mdw->timer = 0;
        {
            int i;
            _pCTW->clactSet = CLACT_U_SetEasyInit( _CLACT_OAMNUM, &_pCTW->renddata, HEAPID_FIELD );
            CLACT_U_SetSubSurfaceMatrix( &_pCTW->renddata, SUB_SURFACE_X, SUB_SURFACE_Y*2 );
            for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
                _pCTW->resMan[MAIN_RES][i] = CLACT_U_ResManagerInit(_ROCK_PATTERN_NUM+1, i, HEAPID_FIELD);
            }
        }
        mdw->seq++;
        break;
      case _CHAR_READ: 	//chr�ǂݍ���
        ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES] =
            CLACT_U_ResManagerResAddArcChar(_pCTW->resMan[MAIN_RES][CLACT_U_CHAR_RES],
                                            ARC_UG_TRAP_GRA, NARC_ug_trap_ug_ef_r1_NCGR,
                                            0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD);
        mdw->rockCharRes[0] = _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES];
        mdw->seq++;
        break;
      case _PAL_READ: 	//pal�ǂݍ���
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES] =
            CLACT_U_ResManagerResAddArcPltt(_pCTW->resMan[MAIN_RES][CLACT_U_PLTT_RES],
                                            ARC_UG_TRAP_GRA, NARC_ug_trap_ug_ef_rock_NCLR,
                                            0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAPID_FIELD);
        mdw->seq++;
        break;
      case _CELL_READ:	//cell�ǂݍ���
        ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CELL_RES] =
            CLACT_U_ResManagerResAddArcKindCell(_pCTW->resMan[MAIN_RES][CLACT_U_CELL_RES],
                                                ARC_UG_TRAP_GRA, NARC_ug_trap_ug_ef_r1_NCER,
                                                0, 0, CLACT_U_CELL_RES,HEAPID_FIELD);
        mdw->seq++;
        break;
      case _ANIM_READ:	//�����֐���anim�ǂݍ���
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CELLANM_RES] =
            CLACT_U_ResManagerResAddArcKindCell(_pCTW->resMan[MAIN_RES][CLACT_U_CELLANM_RES],
                                                ARC_UG_TRAP_GRA, NARC_ug_trap_ug_ef_r1_NANR,
                                                0, 0, CLACT_U_CELLANM_RES,HEAPID_FIELD);
        mdw->seq++;
        break;
      case _SET_CLACT:
        _setCellActorRock(mdw);
        mdw->seq++;
        break;
      case _MESSAGE_LOOP:
            mdw->timer++;
            _rockRscRead(mdw);
            if(mdw->timer > 30){
                if(_pCTW->nowTrapType == UG_TRAPTYPE_ROCK){
                    CLACT_U_CharManagerChg( mdw->rockCharRes[0], mdw->rockCharRes[2] );
                }
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_77,FALSE,NULL);
                mdw->msgTimer = 0;
                mdw->seq = _FUNC;
            }
        break;
      case _FUNC:
        if(_procRock(_pCTW->pFSys->bgl,mdw)){
            if(mdw->bGoodsTrap){
                mdw->seq = _GOODS_END_START;
            }
            else{
                CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
                mdw->seq = _ENDCMD;
            }
        }
        if(mdw->msgTimer < _MSG_TIME){
            mdw->msgTimer++;
            if(mdw->msgTimer == _MSG_TIME){
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            }
        }
        break;
      case _ENDCMD:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        break;
      case _END:
        _endClientRock(CommGetCurrentID(), mdw->bGoodsTrap);
        break;
      case _GOODS_END_START:
        mdw->bGoodsTrap = FALSE;
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        _goodsTrapReverse(mdw->dir);
        mdw->timer=0;
        mdw->seq = _GOODS_END_WALK;
        break;
      case _GOODS_END_WALK:
        mdw->timer++;
        if(mdw->timer > 8){
            CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
            mdw->seq = _ENDCMD;
        }
        break;
    }
}

//--------------------------------------------------------------
/**
 * rock������
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _rockInitialize(GF_BGL_INI * bgl,BOOL bGoodsTrap,int dir)
{
    int i;
    _EVENT_ROCK_WORK* mdw;

    mdw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_ROCK_WORK));
    MI_CpuFill8(mdw,0,sizeof(_EVENT_ROCK_WORK));
    mdw->bGoodsTrap = bGoodsTrap;
    mdw->dir = dir;
    _pCTW->pTCBWork = mdw;
    _pCTW->pRadar = TCB_Add(_GMEVENT_Rock,mdw,TCB_PRIORITY_NORMAL);
//    _pCTW->pEvent = FieldEvent_Set(_pCTW->pFSys, _GMEVENT_Rock, mdw);
}

//==============================================================================
/**
 * rock㩂��J�n����
 * @param   victimNetID  㩔�Q��
 * @retval  none
 */
//==============================================================================

static void _startClientRock(int victimNetID, BOOL bGoodsTrap,int dir)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
    if(CommGetCurrentID() == victimNetID){
        _rockInitialize(_pCTW->pFSys->bgl, bGoodsTrap, dir);
    }
}

//--------------------------------------------------------------
/**
 * rock�T�[�o�[�����J�n����
 * @param   victimNetID   㩔�Q��
 * @retval  none
 */
//--------------------------------------------------------------

static void _startServerRock(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
}

//--------------------------------------------------------------
/**
 * @brief    rock�I������
 * @param    victimNetID ����
 * @retval   none
 */
//--------------------------------------------------------------

static void _endClientRock(int victimNetID,BOOL bGoods)
{
    if(_pCTW->pTCBWork){
        _EVENT_ROCK_WORK* wk = _pCTW->pTCBWork;

        if(wk->eoaShadow){
            EOA_Delete(wk->eoaShadow);
            wk->eoaShadow=NULL;
        }
        if(wk->bGoodsTrap && bGoods){
//        if(wk->bGoodsTrap){
            _goodsTrapReverse(wk->dir);
        }
        _rockRscDelete(wk);
        _endCellActor(_CLACT_ROCK_OAMNUM);
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        TCB_Delete(_pCTW->pRadar);
        sys_FreeMemoryEz(wk);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
    }
}



//--------------------------------------fire
//------------------------------------------------------------------
/**
 * 㩃Z���A�N�^�[�o�^
 * @param   none
 * @retval  none
 */
//------------------------------------------------------------------
static void _setCellActorFire(_EVENT_FIRE_WORK* mdw)
{
    // ���\�[�X�}�l�[�W���[����]��
    // Chara�]��
    CLACT_U_CharManagerSetCharModeAdjustAreaCont( _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES] );
    //    CLACT_U_CharManagerSetAreaCont( _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES] );

    // �p���b�g�]��  CLACT_U_PlttManagerSetCleanArea
    CLACT_U_PlttManagerSetCleanArea( _pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES] );
    // �Z���A�N�^�[�w�b�_�쐬
    CLACT_U_MakeHeader(&_pCTW->clActHeader_s,
                       0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
                       0, 0,
                       _pCTW->resMan[MAIN_RES][CLACT_U_CHAR_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_PLTT_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_CELL_RES],
                       _pCTW->resMan[MAIN_RES][CLACT_U_CELLANM_RES],
                       NULL,NULL);

    {
        //�o�^���i�[
        CLACT_ADD add;
        int i;

        add.ClActSet	= _pCTW->clactSet;
        add.ClActHeader	= &_pCTW->clActHeader_s;

        add.mat.x		= FX32_CONST(32) ;
        add.mat.y		= FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���iMAIN�����H�ASUB����H�j
        add.mat.z		= 0;
        add.sca.x		= FX32_ONE;
        add.sca.y		= FX32_ONE;
        add.sca.z		= FX32_ONE;
        add.rot			= 0;
        add.pri			= 0;
        add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
        add.heap		= HEAPID_FIELD;

        //�Z���A�N�^�[�\���J�n

        // ���ʗp
        for(i = 0; i < _CLACT_FIRE_OAMNUM ; i++){
            add.mat.x = FX32_ONE * 128;
            add.mat.y = FX32_ONE * 84;
            _pCTW->clActWork[i] = CLACT_Add(&add);
            CLACT_SetAffineParam(_pCTW->clActWork[i], CLACT_AFFINE_DOUBLE);
            CLACT_AnmChg( _pCTW->clActWork[i], 0);
            CLACT_SetAnmFlag(_pCTW->clActWork[i], 1);
            CLACT_AnmFrameSet(_pCTW->clActWork[i], 0 );
            CLACT_BGPriorityChg(_pCTW->clActWork[i],1);
            //            CLACT_ObjModeSet(_pCTW->clActWork[0], GX_OAM_MODE_XLU );
        }
    }
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_ON);	//OBJ�ʂn�m
    GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
}

//--------------------------------------------------------------
/**
 * @brief    FIRE����
 * @param    bgl    GF_BGL_INI
 * @param    mdw    _EVENT_ROCK_WORK
 * @retval   ��������=TRUE
 */
//--------------------------------------------------------------

static BOOL _procFire(GF_BGL_INI * bgl, _EVENT_FIRE_WORK* mdw)
{
    int i,pattern,j,total=0;
    float ds;
    int pow=0,pos,powPos,size,zint,xint;
    //    fx32 x,z,alpha,ans;
    VecFx32 tmpVex;

    enum{
        _FIRE_INIT,
        _FIRE_PROC,
        _FIRE_END,
    };
    switch(mdw->subSeq){
      case _FIRE_INIT:
        if(_pCTW->nowTrapType == UG_TRAPTYPE_BLAZE){
            mdw->scale = 4;
        }
        else{
            mdw->scale = 2;
        }
        mdw->timer = 0;
        mdw->subSeq = _FIRE_PROC;
        //        break;    // �K�v�Ȃ�
      case _FIRE_PROC:
        // �蓮�T���v�����O
        Snd_MicManualSampling(MIC_SAMPLING_TYPE_SIGNED_8BIT,&_mic,_micCallBack,NULL);
        mdw->micCount++;
        mdw->mic[mdw->micCount % _MIC_SAMPLE_NUM] = abs(_pCTW->mic); // �}�C�N�T���v�����O����
        for(j = 0; j < _MIC_SAMPLE_NUM ; j++){
            total += mdw->mic[j];
        }

        if(total > _MIC_TOTAL_NUM){
            mdw->timer++;
            Snd_SePlay(UGT_SE_FIER);
        }
        else{
            mdw->subSeq = _FIRE_INIT;
        }
        if((mdw->timer % _MIC_SCALEDOWN_TIME) == (_MIC_SCALEDOWN_TIME-1)){
            mdw->scale--;
        }
        if(mdw->scale == 0){
            mdw->subSeq = _FIRE_END;
            return TRUE;    // �I��
        }

        if(_pCTW->nowTrapType == UG_TRAPTYPE_BLAZE){
            switch(mdw->scale){
              case 4:
                ds = 2;
                break;
              case 3:
                ds = 1.5;
                break;
              case 2:
                ds = 1;
                break;
              default:  //1
                ds = 0.5;
                break;
            }
        }
        else{
            switch(mdw->scale){
              case 2:
                ds = 2;
                break;
              default: //1
                ds = 1.5;
                break;
            }
        }
        pattern = 0;
        if(mdw->timer){
            pattern += 1;
        }

        tmpVex.x = FX32_ONE*ds;
        tmpVex.y = FX32_ONE*ds;
        tmpVex.z = FX32_ONE*ds;
        CLACT_SetScale(_pCTW->clActWork[0],&tmpVex);
        CLACT_AnmChgCheck( _pCTW->clActWork[0], pattern);
        break;
      case _FIRE_END:
        break;
    }
    CLACT_Draw( _pCTW->clactSet );			// �Z���A�N�^�[�풓�֐�
    return FALSE;
}

//--------------------------------------------------------------
/**
 * FIRE�C�x���g���s
 * @param
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _GMEVENT_Fire(TCB_PTR tcb, void *work)
//static BOOL _GMEVENT_Fire(GMEVENT_CONTROL* event)
{
//    FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork(event);
    _EVENT_FIRE_WORK* mdw = work;
    int i,picNo;

    switch(mdw->seq){
      case _INIT:
        mdw->index = _trapStartSet();
        mdw->timer = 0;
        _initCellActor();
        mdw->seq++;
        break;
      case _CHAR_READ: 	//chr�ǂݍ���
        ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        if(_pCTW->nowTrapType == UG_TRAPTYPE_BLAZE){
            picNo = NARC_ug_trap_ug_ef_fire1_NCGR;
        }
        else{
            picNo = NARC_ug_trap_ug_ef_fire2_NCGR;
        }
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CHAR_RES] =
            CLACT_U_ResManagerResAddArcChar(_pCTW->resMan[MAIN_RES][CLACT_U_CHAR_RES],
                                            ARC_UG_TRAP_GRA, picNo,
                                            0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD);
        mdw->seq++;
        break;
      case _PAL_READ: 	//pal�ǂݍ���
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_PLTT_RES] =
            CLACT_U_ResManagerResAddArcPltt(_pCTW->resMan[MAIN_RES][CLACT_U_PLTT_RES],
                                            ARC_UG_TRAP_GRA, NARC_ug_trap_ug_ef_fire_NCLR,
                                            0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAPID_FIELD);
        mdw->seq++;
        break;
      case _CELL_READ:	//cell�ǂݍ���
        ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        if(_pCTW->nowTrapType == UG_TRAPTYPE_BLAZE){
            picNo = NARC_ug_trap_ug_ef_fire1_NCER;
        }
        else{
            picNo = NARC_ug_trap_ug_ef_fire2_NCER;
        }
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CELL_RES] =
            CLACT_U_ResManagerResAddArcKindCell(_pCTW->resMan[MAIN_RES][CLACT_U_CELL_RES],
                                                ARC_UG_TRAP_GRA, picNo,
                                                0, 0, CLACT_U_CELL_RES,HEAPID_FIELD);
        mdw->seq++;
        break;
      case _ANIM_READ:	//anim�ǂݍ���
        if(_pCTW->nowTrapType == UG_TRAPTYPE_BLAZE){
            picNo = NARC_ug_trap_ug_ef_fire1_NANR;
        }
        else{
            picNo = NARC_ug_trap_ug_ef_fire2_NANR;
        }
        _pCTW->resObjTbl[MAIN_RES][CLACT_U_CELLANM_RES] =
            CLACT_U_ResManagerResAddArcKindCell(_pCTW->resMan[MAIN_RES][CLACT_U_CELLANM_RES],
                                                ARC_UG_TRAP_GRA, picNo,
                                                0, 0, CLACT_U_CELLANM_RES,HEAPID_FIELD);
        mdw->seq++;
        break;
      case _SET_CLACT:
        _setCellActorFire(mdw);
        mdw->seq++;
        break;
      case _MESSAGE_LOOP:
            mdw->timer++;
            if(mdw->timer > 30){
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_76,FALSE,NULL);
                GX_SetMasterBrightness(_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV);
                mdw->seq = _FUNC;
                mdw->msgTimer = 0;
            }
        break;
      case _FUNC:
        G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ,GX_BLEND_PLANEMASK_BG0, 14, 7);
        if(_procFire(_pCTW->pFSys->bgl, mdw)){
            if(mdw->bGoodsTrap){
                mdw->seq = _GOODS_END_START;
            }
            else{
                CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
                mdw->seq = _ENDCMD;
            }
        }
        if(mdw->msgTimer < _MSG_TIME){
            mdw->msgTimer++;
            if(mdw->msgTimer == _MSG_TIME){
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            }
        }
        break;
      case _ENDCMD:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        break;
      case _END:
        _endClientFire(CommGetCurrentID(), mdw->bGoodsTrap);
        break;
      case _GOODS_END_START:
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        mdw->bGoodsTrap = FALSE;
        _goodsTrapReverse(mdw->dir);
        mdw->timer=0;
        mdw->seq = _GOODS_END_WALK;
        break;
      case _GOODS_END_WALK:
        mdw->timer++;
        if(mdw->timer > 8){
            CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
            mdw->seq = _ENDCMD;
        }
        break;
    }
//    return FALSE;
}

//--------------------------------------------------------------
/**
 * fire������
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _fireInitialize(GF_BGL_INI * bgl, BOOL bGoodsTrap, int dir)
{
    int i;
    _EVENT_FIRE_WORK* mdw;

    mdw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_FIRE_WORK));
    MI_CpuFill8(mdw,0,sizeof(_EVENT_FIRE_WORK));
    mdw->bGoodsTrap = bGoodsTrap;
    mdw->dir = dir;
//    _pCTW->pEvent = FieldEvent_Set(_pCTW->pFSys, _GMEVENT_Fire, mdw);
    _pCTW->pTCBWork = mdw;
    _pCTW->pRadar = TCB_Add( _GMEVENT_Fire, mdw, TCB_PRIORITY_NORMAL);
}

//==============================================================================
/**
 * FIRE㩂��J�n����
 * @param   victimNetID  㩔�Q��
 * @retval  none
 */
//==============================================================================

static void _startClientFire(int victimNetID,BOOL bGoodsTrap, int dir)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
    if(CommGetCurrentID() == victimNetID){
        _fireInitialize(_pCTW->pFSys->bgl, bGoodsTrap, dir);
    }
}

//--------------------------------------------------------------
/**
 * FIRE�T�[�o�[�����J�n����
 * @param   victimNetID   㩔�Q��
 * @retval  none
 */
//--------------------------------------------------------------

static void _startServerFire(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
}

//--------------------------------------------------------------
/**
 * @brief    fire�I������
 * @param    victimNetID ����
 * @retval   none
 */
//--------------------------------------------------------------

static void _endClientFire(int victimNetID, BOOL bGoods)
{
    if(_pCTW->pTCBWork){
        _EVENT_FIRE_WORK* wk = _pCTW->pTCBWork;
        if(wk->bGoodsTrap && bGoods){
//        if(wk->bGoodsTrap){
            _goodsTrapReverse(wk->dir);
        }
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        G2_BlendNone();
        GX_SetMasterBrightness(BRIGHTNESS_NORMAL);
        _endCellActor(_CLACT_FIRE_OAMNUM);
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        TCB_Delete(_pCTW->pRadar);
        sys_FreeMemoryEz(wk);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
    }
}



//--------------------------------------message

//--------------------------------------------------------------
/**
 * MESSAGE�C�x���g���s
 * @param
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _GMEVENT_Message(TCB_PTR tcb, void *work)
//static BOOL _GMEVENT_Message(GMEVENT_CONTROL* event)
{
    //FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork(event);
    _EVENT_MESSAGE_WORK* mdw = work;
    int i;

    switch(mdw->seq){
      case _INIT:
        mdw->index = _trapStartSet();
        mdw->timer = 0;
        mdw->seq++;
        break;
      case _CHAR_READ:
        ChangeBrightnessRequest(1,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        mdw->seq++;
        break;
      case _PAL_READ:
        mdw->seq++;
        break;
      case _CELL_READ:
        ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_FL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        mdw->seq++;
        break;
      case _ANIM_READ:
        mdw->seq++;
        break;
      case _SET_CLACT:
        mdw->seq++;
        break;
      case _MESSAGE_LOOP:
            mdw->timer++;
            if(mdw->timer > 30){
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
                GX_SetMasterBrightness(_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV);
                mdw->seq = _FUNC;
            }
        break;
      case _FUNC:
        if(mdw->bGoodsTrap){
            mdw->seq = _GOODS_END_START;
        }
        else{
            CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
            mdw->seq = _ENDCMD;
        }
        break;
      case _ENDCMD:
        break;
      case _END:
        _endClientMessage(CommGetCurrentID(), mdw->bGoodsTrap);
        break;
      case _END2:
        break;
      case _GOODS_END_START:
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        mdw->bGoodsTrap = FALSE;
        _goodsTrapReverse(mdw->dir);
        mdw->timer=0;
        mdw->seq = _GOODS_END_WALK;
        break;
      case _GOODS_END_WALK:
        mdw->timer++;
        if(mdw->timer > 8){
            CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
            mdw->seq = _ENDCMD;
        }
        break;
    }
}

//--------------------------------------------------------------
/**
 * messageTrap������
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _messageInitialize(GF_BGL_INI * bgl, BOOL bGoodsTrap, int dir)
{
    int i;
    _EVENT_MESSAGE_WORK* mdw;

    mdw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_MESSAGE_WORK));
    MI_CpuFill8(mdw,0,sizeof(_EVENT_MESSAGE_WORK));
    mdw->bGoodsTrap = bGoodsTrap;
    mdw->dir = dir;
//    _pCTW->pEvent = FieldEvent_Set(_pCTW->pFSys, _GMEVENT_Message, mdw);
    _pCTW->pTCBWork = mdw;
    _pCTW->pRadar = TCB_Add( _GMEVENT_Message, mdw, TCB_PRIORITY_NORMAL);

}

//==============================================================================
/**
 * MESSAGE㩂��J�n����
 * @param   victimNetID  㩔�Q��
 * @retval  none
 */
//==============================================================================

static void _startClientMessage(int victimNetID,BOOL bGoodsTrap, int dir)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
    if(CommGetCurrentID() == victimNetID){
        _messageInitialize(_pCTW->pFSys->bgl, bGoodsTrap, dir);
    }
}

//--------------------------------------------------------------
/**
 * MESSAGE�T�[�o�[�����J�n����
 * @param   victimNetID   㩔�Q��
 * @retval  none
 */
//--------------------------------------------------------------

static void _startServerMessage(int victimNetID)
{
    CommPlayerSetCondition(victimNetID, PLAYER_COND_SMOG);
}

//--------------------------------------------------------------
/**
 * @brief    message�I������
 * @param    victimNetID ����
 * @retval   none
 */
//--------------------------------------------------------------

static void _endClientMessage(int victimNetID,BOOL bGoodsTrap)
{
    if(_pCTW->pTCBWork){
        _EVENT_MESSAGE_WORK* wk = _pCTW->pTCBWork;
        if(wk->bGoodsTrap && bGoodsTrap){
//        if(wk->bGoodsTrap){
            _goodsTrapReverse(wk->dir);
        }
        SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        G2_BlendNone();
        GX_SetMasterBrightness(BRIGHTNESS_NORMAL);
        CommPlayerHoldBitEnd(_HOLD_TRAP);
        TCB_Delete(_pCTW->pRadar);
        sys_FreeMemoryEz(wk);
        _pCTW->pRadar = NULL;
        _pCTW->pTCBWork = NULL;
    }
}


///-----------------------touch

//--------------------------------------------------------------
/**
 * @brief    TouchRadar����
 * @param    bgl    GF_BGL_INI
 * @param    mdw    _EVENT_BUBBLE_WORK
 * @retval   ��������=TRUE
 */
//--------------------------------------------------------------

#define ONE_GRID_SIZE	(16)

static BOOL _procTouchRadar(GF_BGL_INI * bgl, _EVENT_TOUCHRADAR_WORK* mdw)
{
    int i,j;
    VecFx32 tmpVex;
    int x,z,efX,efZ;

    tmpVex.x = mdw->scrXpos * FX32_ONE;
    tmpVex.y = mdw->scrZpos * FX32_ONE;
    CLACT_SetMatrix(_pCTW->clActWork[0], &tmpVex);
    tmpVex.x = (mdw->timer * FX32_ONE) / 10;
    tmpVex.y = tmpVex.z = tmpVex.x;
    CLACT_SetScale(_pCTW->clActWork[0], &tmpVex);
    CLACT_ObjModeSet(_pCTW->clActWork[0], GX_OAM_MODE_XLU );
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ,GX_BLEND_PLANEMASK_BG0,16-(mdw->timer/2),16);

    for(j = 0; j < 3;j++){
        for(i = 0; i < mdw->touchSize[j]; i++){
            efZ = mdw->pTouchBuff[j][i] / 16;
            efX = mdw->pTouchBuff[j][i] % 16;

            tmpVex.x = (mdw->touchXpos - 6 + efX) * FX32_ONE * ONE_GRID_SIZE + (FX32_ONE*ONE_GRID_SIZE/2);
            tmpVex.y = 0;
            tmpVex.z = (mdw->touchZpos - 6 + efZ) * FX32_ONE * ONE_GRID_SIZE + (FX32_ONE*ONE_GRID_SIZE/2);

            NNS_G3dWorldPosToScrPos(&tmpVex, &x, &z);

            tmpVex.x = x * FX32_ONE;
            tmpVex.y = z * FX32_ONE;
            CLACT_SetMatrix(_pCTW->clActWork[i+1+j*8], &tmpVex);
        }
    }
    mdw->timer++;
    if(mdw->timer > 20){
        return TRUE;
    }
    CLACT_Draw( _pCTW->clactSet );									// �Z���A�N�^�[�풓�֐�
    return FALSE;
}


//------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 * @param   none
 * @retval  none
 */
//------------------------------------------------------------------
static void _setCellActorTouchRadar(_EVENT_TOUCHRADAR_WORK* mdw)
{
    // ���\�[�X�}�l�[�W���[����]��
    // Chara�]��
    CLACT_U_CharManagerSetCharModeAdjustAreaCont( _pCTW->resObjTbl[TOUCH_RES][CLACT_U_CHAR_RES] );
    // �p���b�g�]��  CLACT_U_PlttManagerSetCleanArea
    CLACT_U_PlttManagerSetCleanArea( _pCTW->resObjTbl[TOUCH_RES][CLACT_U_PLTT_RES] );
    // �Z���A�N�^�[�w�b�_�쐬
    CLACT_U_MakeHeader(&_pCTW->clActHeader_s,
                       0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
                       0, 0,
                       _pCTW->resMan[TOUCH_RES][CLACT_U_CHAR_RES],
                       _pCTW->resMan[TOUCH_RES][CLACT_U_PLTT_RES],
                       _pCTW->resMan[TOUCH_RES][CLACT_U_CELL_RES],
                       _pCTW->resMan[TOUCH_RES][CLACT_U_CELLANM_RES],
                       NULL,NULL);

    {
        //�o�^���i�[
        CLACT_ADD add;
        int i;

        add.ClActSet	= _pCTW->clactSet;
        add.ClActHeader	= &_pCTW->clActHeader_s;

        add.mat.x		= FX32_CONST(32) ;
        add.mat.y		= FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���iMAIN�����H�ASUB����H�j
        add.mat.z		= 0;
        add.sca.x		= FX32_ONE;
        add.sca.y		= FX32_ONE;
        add.sca.z		= FX32_ONE;
        add.rot			= 0;
        add.pri			= 0;
        add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
        add.heap		= HEAPID_FIELD;

        //�Z���A�N�^�[�\���J�n

        // ���ʗp
        for(i = 0; i < _CLACT_TOUCHRADAR_OAMNUM ; i++){
            add.mat.x = FX32_ONE*300;
            add.mat.y = FX32_ONE*300;
            _pCTW->clActWork[i] = CLACT_Add(&add);
            if(i == 0){
                CLACT_SetAffineParam(_pCTW->clActWork[i],CLACT_AFFINE_DOUBLE);
                CLACT_AnmChg( _pCTW->clActWork[i], 0);
            }
            else if (i < 9){
                CLACT_AnmChg( _pCTW->clActWork[i], 1);
            }
            else{
                CLACT_AnmChg( _pCTW->clActWork[i], 2);
            }
            CLACT_SetAnmFlag(_pCTW->clActWork[i],1);
            CLACT_AnmFrameSet(_pCTW->clActWork[i],0);
        }
    }
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_ON);	//OBJ�ʂn�m
    GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
}

//--------------------------------------------------------------
/**
 * TouchRadar�C�x���g���s
 * @param
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _GMEVENT_Touch(TCB_PTR tcb, void *work)
{
    _EVENT_TOUCHRADAR_WORK* mdw = work;
    int i;

    switch(mdw->seq){
      case _INIT:
        GX_SetMasterBrightness(_TRAP_DIRTYBLOSSOMS_BRIGHTNESS_LV);
        CommPlayerHold();
        Snd_SePlay(UG_SE_RADAR_ECHO);
        // �Z���A�N�^�[������
        _pCTW->clactSet = CLACT_U_SetEasyInit( _CLACT_OAMNUM, &_pCTW->renddata, HEAPID_FIELD );
        CLACT_U_SetSubSurfaceMatrix( &_pCTW->renddata, SUB_SURFACE_X, SUB_SURFACE_Y*2 );
        mdw->seq = _SET_CLACT;
        break;
      case _SET_CLACT:
        _setCellActorTouchRadar(mdw);
        mdw->seq = _FUNC;
        break;
      case _FUNC:
        if(_procTouchRadar(_pCTW->pFSys->bgl,mdw)){
            mdw->seq = _END;
        }
        break;
      case _END:
        G2_BlendNone();
        GX_SetMasterBrightness(BRIGHTNESS_NORMAL);
        // �L�����]���}�l�[�W���[�j��
        CLACT_U_CharManagerDelete(_pCTW->resObjTbl[TOUCH_RES][CLACT_U_CHAR_RES]);
        // �p���b�g�]���}�l�[�W���[�j��
        CLACT_U_PlttManagerDelete(_pCTW->resObjTbl[TOUCH_RES][CLACT_U_PLTT_RES]);
        for(i = 0; i < _CLACT_TOUCHRADAR_OAMNUM ; i++){
            if(_pCTW->clActWork[i]!=NULL){
                CLACT_Delete(_pCTW->clActWork[i]);
            }
            _pCTW->clActWork[i]=NULL;
        }
        // �Z���A�N�^�[�Z�b�g�j��
        CLACT_DestSet(_pCTW->clactSet);
        TCB_Delete(tcb);
        sys_FreeMemoryEz(mdw);
        _pCTW->pTchRadar = NULL;
        CommPlayerHoldBitEnd(_HOLD_TOUCH);
        break;
      default:
        break;
    }
}

//--------------------------------------------------------------
/**
 * touch�i��Ȃł͂Ȃ��j���s
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

void UgTouchRadarStart(FIELDSYS_WORK* pFSys,int xpos,int zpos,int scrxpos,int scrzpos,
                       u8* touchBuff1,int size1,u8* touchBuff2,int size2,u8* touchBuff3,int size3)
{
    int i;
    _EVENT_TOUCHRADAR_WORK* mdw;

    if(_pCTW->pTchRadar){
        OHNO_PRINT("�̂����Ă���\n");
        return;
    }

    mdw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_TOUCHRADAR_WORK));
    MI_CpuFill8(mdw, 0, sizeof(_EVENT_TOUCHRADAR_WORK));

    mdw->seq = _INIT;
    mdw->timer = 0;
    mdw->touchXpos = xpos;
    mdw->touchZpos = zpos;
    mdw->scrXpos = scrxpos;
    mdw->scrZpos = scrzpos;
    mdw->pTouchBuff[0] = touchBuff1;
    mdw->pTouchBuff[1] = touchBuff2;
    mdw->pTouchBuff[2] = touchBuff3;
    mdw->touchSize[0] = size1;
    mdw->touchSize[1] = size2;
    mdw->touchSize[2] = size3;

    _pCTW->pTchRadar = TCB_Add(_GMEVENT_Touch , mdw,TCB_PRIORITY_NORMAL);
    CommPlayerHoldBit(_HOLD_TOUCH);
}


//--------------------------------------------------------------
/**
 * 㩂ɂ������Ă���l�����邮�����Ă���
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

static void _GMEVENT_Turn(TCB_PTR tcb, void *work)
{
    _EVENT_TURNDISP_WORK* mdw = work;
    int i,dir,id;

    if(!_pCTW){
        TCB_Delete(tcb);
        sys_FreeMemoryEz(mdw);
        return;
    }
    id = mdw->netID;
    dir = CommPlayerGetClientDir(id);
    if((mdw->seq == 1) || (dir == DIR_NOT)){
        _pCTW->turnWork[id] = NULL;
        _pCTW->turnTask[id] = NULL;
        TCB_Delete(tcb);
        sys_FreeMemoryEz(mdw);
        CommPlayerBlowAnimStop(id);
        return;
    }
    switch(mdw->type){
//      case UG_TRAPTYPE_HOLE:
//      case UG_TRAPTYPE_BIG_HOLE:
      case UG_TRAPTYPE_REVERSE:
      case UG_TRAPTYPE_GIDDY:
      case UG_TRAPTYPE_DIR_LEFT:
      case UG_TRAPTYPE_DIR_RIGHT:
      case UG_TRAPTYPE_DIR_UP:
      case UG_TRAPTYPE_DIR_DOWN:
      case UG_TRAPTYPE_BIGDIR_LEFT:
      case UG_TRAPTYPE_BIGDIR_RIGHT:
      case UG_TRAPTYPE_BIGDIR_UP:
      case UG_TRAPTYPE_BIGDIR_DOWN:
        return;
    }


    mdw->timer++;
    if((mdw->timer % 8) == 0){
        switch(dir){
          case DIR_UP:
            dir = DIR_RIGHT;
            break;
          case DIR_DOWN:
            dir = DIR_LEFT;
            break;
          case DIR_LEFT:
            dir = DIR_UP;
            break;
          case DIR_RIGHT:
            dir = DIR_DOWN;
            break;
        }
        CommPlayerSetClientDir(id, dir);
    }
}

//--------------------------------------------------------------
/**
 * 㩂ɂ������Ă���l�����邮�����Ă���
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------
static void UgTrapTurnDispStart(int netID,int type)
{
    int i;
    _EVENT_TURNDISP_WORK* mdw;

    if(!_pCTW){
        return;
    }
    else if(_pCTW->bHalt){
        return;
    }
    if(_pCTW->turnWork[netID]==NULL){
        mdw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_TURNDISP_WORK));
        MI_CpuFill8(mdw, 0, sizeof(_EVENT_TURNDISP_WORK));
        _pCTW->turnWork[netID] = mdw;
        _pCTW->turnTask[netID] = TCB_Add(_GMEVENT_Turn , mdw,TCB_PRIORITY_NORMAL);
    }
    else{
        mdw = _pCTW->turnWork[netID];
    }
    mdw->netID = netID;
    mdw->type = type;
}

//--------------------------------------------------------------
/**
 * 㩂ɂ������Ă���l�����邮�����Ă���̂��I��点��
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------
void UgTrapTurnDispEnd(int netID)
{
    if(!_pCTW->turnWork[netID]){
        return;
    }
    CommPlayerSetFENoneAdd( netID );
    _pCTW->turnWork[netID]->seq = 1;
    _pCTW->turnWork[netID] = NULL;
    _pCTW->turnTask[netID] = NULL;
    CommPlayerBlowAnimStop(netID);
}

//--------------------------------------------------------------
/**
 * ���邮��܂��G�t�F�N�g��S��������
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------
static void _turnTaskAllDelete(void)
{
    int i;

    for(i = 0; i < COMM_MACHINE_MAX;i++){
        if(_pCTW->turnTask[i]){
            TCB_Delete(_pCTW->turnTask[i]);
            sys_FreeMemoryEz(_pCTW->turnWork[i]);
            _pCTW->turnTask[i] = NULL;
            _pCTW->turnWork[i] = NULL;
        }
    }
}

#ifdef PM_DEBUG
static void DEBUG_TrapTBLPrint(char* msg)
{
    int i;

    OHNO_PRINT("--> %s\n",msg);
    for(i = 0 ; i < _TRAP_NUM_MAX; i++){
        TrapInfo* pTrap = _pCTW->pTrapTbl[i];
        if(pTrap && (pTrap->trapType != _TRAP_TYEP_INVALID)){
            OHNO_PRINT(" � %d %d\n",pTrap->xpos,pTrap->zpos);
        }
    }
}

#endif

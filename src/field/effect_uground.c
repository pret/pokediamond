//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		effect_uground.c
 *@brief	�n���}�b�v�t�F�[�h�G���J�E���g
 *@author	tomoya takahashi 
 *@data		2005.08.03
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define CLACT_OLD_NONE
#include "common.h"
#include "system/lib_pack.h"
#include "system/brightness.h"
#include "system/snd_tool.h"
#include "field_event.h"
#include "system/palanm.h"
#include "system/mystatus.h"


#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/wipe.h"

#include "player.h"


#define __EFFECT_UGROUND_H_GLOBAL
#include "effect_uground.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define UNDER_TCB_PRI	(5)




////////////////////////////////////////////////////////////
//
//	�`��V�X�e���p
//
///////////////////////////////////////////////////////////
#define DRAW_2D_RES_NUM		(4)		// �Ǘ����郊�\�[�X�̎��
#define DRAW_2D_OBJ_TBL_NUM	(2)		// �Ǘ�����I�u�W�F�e�[�u����


//-------------------------------------
//	
//	����֐��߂�l
//	
//=====================================
enum{
	EFCT_SYSRET_END,		// �G���[�R�[�h
	EFCT_SYSRET_OK,			// ����
	EFCT_SYSRET_FADE,		// �t�F�[�h�J�n
} EFCT_UG_SYSRET;


//-------------------------------------
//	
//	�S�̂ɋ���
//	
//=====================================
#define EFECT_UGCOMMON_OBJ_MAT_X	(112*FX32_ONE)
#define EFECT_UGCOMMON_OBJ_MAT_Y	(69*FX32_ONE)


//-------------------------------------
//	
//	�^�X�N�O�O
//	�n���}�b�v�ւ̃t�F�[�h�P
//	
//=====================================
enum{
	EFCT_UG00_PLAYER_OFF,	// �v���C���[������
	EFCT_UG00_SHADOW,		// �e�쐬
	EFCT_UG00_OBJ_MOVE,		// �I�u�W�F�N�g�ړ�
	EFCT_UG00_FADE_WAIT,	// �u���b�N�t�F�[�h�҂�
	EFCT_UG00_OAMCLEAN,		// OAMCLEAN
	EFCT_UG00_DELETE,		// �j��
};
#define EFCT_UG00_SHADOW_COUNT	(7)		// ����ɂȂ�����I��
#define EFCT_UG00_OBJ_JUMP_DIS	(16*FX32_ONE)	// �W�����v��
#define	EFCT_UG00_OBJ_CNNUM		(0x8000/16)	// �J�E���^�����l
#define EFCT_UG00_OBJ_END		(0x8000)	// �J�E���^�I��
#define EFCT_UG00_FADE_START	(EFCT_UG00_OBJ_CNNUM*16)	// �t�F�[�h�J�n

#define EFCT_UG00_BR_MSK		( PLANEMASK_BG0| PLANEMASK_BG2| PLANEMASK_BG3| PLANEMASK_BD )
#define EFCT_UG00_BR_SYNC		( 2 )
#define EFCT_UG00_BR_S			( 0 )
#define EFCT_UG00_BR_E			( -8 )

#define EFCT_UG00_BR_WAIT		( 6 )


//-------------------------------------
//	
//	�^�X�N�O�P
//	�n���}�b�v�ւ̃t�F�[�h�Q
//	
//=====================================
enum{
	EFCT_UG01_OBJ_OFF,
	EFCT_UG01_START,		// �J�n
	EFCT_UG01_OBJ_MOVE,		// �I�u�W�F�N�g�ړ�
	EFCT_UG01_BG_FADE,		// BG���t�F�[�h�C��������
	EFCT_UG01_OAMCLEAN,		// OAMCLEAN
	EFCT_UG01_DELETE,		// �j��
};
#define EFCT_UG01_END	(EFECT_UGCOMMON_OBJ_MAT_Y)			// �I�u�W�F�̍���������ɂȂ�����I�u�W�F�̈ړ��I��
#define EFCT_UG01_REST	(384*FX32_ONE)			// �I�u�W�F�̍���������ɂȂ�����I�u�W�F�̈ړ��I��
#define EFCT_UG01_MOVE	(FX32_ONE*8)			// �ړ��X�s�[�h
#define EFCT_UG01_BG	(16)						// BG�ʂ𓮂����X�s�[�h
#define EFCT_UG01_OBJ_MAT_Y	(192*FX32_ONE)		// �I�u�W�F�N�g�J�n�ʒu
#define EFCT_UG01_OBJ_MAT_REST_Y	(-32*FX32_ONE)	// �I�u�W�F�N�g�J�n�ʒu

//-------------------------------------
//	
//	�^�X�N�O�Q
//	�n���}�b�v�ւ̃t�F�[�h�R
//	
//=====================================
enum{
	EFCT_UG02_PLAYER_OFF,	// �v���C���[������
	EFCT_UG02_START,		// �J�n
	EFCT_UG02_BG_FADE,		// BG���t�F�[�h�C��������
	EFCT_UG02_OBJ_MOVE,		// �I�u�W�F�N�g�ړ�
	EFCT_UG02_FADE_WAIT,	// �t�F�[�h�A�E�g
	EFCT_UG02_OAMCLEAN,		// OAM������
	EFCT_UG02_DELETE,		// �j��
};
#define EFCT_UG02_REST	(-32*FX32_ONE)			// �I�u�W�F�̍���������ɂȂ�����I�u�W�F�̈ړ��I��
#define EFCT_UG02_END	(192*FX32_ONE)			// �I�u�W�F�̍���������ɂȂ�����I�u�W�F�̈ړ��I��
#define EFCT_UG02_MOVE	(FX32_ONE*8)			// �ړ��X�s�[�h
#define EFCT_UG02_BG	(32)					// BG�ʂ𓮂����X�s�[�h
#define EFCT_UG02_FADE_S	(300*FX32_ONE)		// �z���C�g�A�E�g�͂��߂�^�C�~���O
#define EFCT_UG02_ROTA_SA	(FX32_CONST(0.20f))	// ��]�����x
#define EFCT_UG02_ROTA_SE	(2*FX32_ONE)		// ��]�����ő�

#define EFCT_UG02_OBJ_MAT_REST_Y (384*FX32_ONE)		// �I�u�W�F�N�g�J�n�ʒu

//-------------------------------------
//	
//	�^�X�N�O�R
//	�n���}�b�v�ւ̃t�F�[�h�S
//	
//=====================================
enum{
	EFCT_UG03_START,		// �J�n
	EFCT_UG03_FADEIN_M,		// ���C����ʃt�F�[�h�C��
	EFCT_UG03_FADEIN_MW,	// �t�F�[�h�C���҂�
	EFCT_UG03_OBJ_MOVE,		// �I�u�W�F�N�g����
	EFCT_UG03_OBJ_SHADOW,	// �I�u�W�F�N�g����
	EFCT_UG03_OAMCLEAN,		// OAMCLEAN
	EFCT_UG03_DELETE,		// �j��
};

#define EFCT_UG03_ROTA_S	(2*FX32_ONE)		// ��]����
#define EFCT_UG03_ROTA_SA	(FX32_CONST(0.40f))	// ��]�����x
#define EFCT_UG03_ROTA_SE	(0)					// ��]�����ő�
#define EFCT_UG03_SHADOW_COUNT	(8)		// ����ɂȂ�����I��
#define EFCT_UG03_OBJ_JUMP_DIS	(32*FX32_ONE)	// �W�����v��
#define	EFCT_UG03_OBJ_CNNUM		(0x8000/8)	// �J�E���^�����l
#define EFCT_UG03_OBJ_END		(0x8000)	// �J�E���^�I��
#define EFCT_UG03_FADE_START	(EFCT_UG00_OBJ_CNNUM*10)	// �t�F�[�h�J�n
#define EFCT_UG03_OBJ_DEL_WAIT	( 6 )

#define EFCT_UG03_BR_MSK		( PLANEMASK_BG0| PLANEMASK_BG2| PLANEMASK_BG3| PLANEMASK_BD )
#define EFCT_UG03_BR_SYNC		( 2 )
#define EFCT_UG03_BR_S			( -8 )
#define EFCT_UG03_BR_E			( 0 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�`��V�X�e���f�[�^
//	
//=====================================
typedef struct {
	/* �Q���V�X�e���f�[�^  */
	CLACT_SET_PTR			clactSet;						// �Z���A�N�^�[�Z�b�g
	CLACT_HEADER_TBL_PTR	clactHeader;					// �w�b�_�[
	CLACT_U_RES_MANAGER_PTR	resMan[DRAW_2D_RES_NUM];		// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_TBL*	resObjTbl[DRAW_2D_OBJ_TBL_NUM];	// ���\�[�X�I�u�W�F�e�[�u��
	int						resObjNum[DRAW_2D_RES_NUM];		// ���ꂼ��̃��\�[�X�I�u�W�F��
	CLACT_U_EASYRENDER_DATA	renddata;						// �ȈՃ����_�[�f�[�^
	

	/* 3d�V�X�e���f�[�^�i���͂Ȃ��j */

} EFCT_UG_DRAWSYS;

//-------------------------------------
//	
//	�n���}�b�v�t�F�[�h�G�t�F�N�g
//	�I�u�W�F�N�g�\����
//	
//=====================================
typedef struct _EFCT_UG_OBJ{
	void*		data;		// ���̃T�C�Y���Ɋe�f�[�^������
	
	/* �f�[�^�쐬�֐� */
	void (*init)(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);

	/* �f�[�^�j���֐� */
	void (*delete)(struct _EFCT_UG_OBJ* data);
	
	/* ����֐� */
	int (*move)(struct _EFCT_UG_OBJ* data);
} EFCT_UG_OBJ;


//-------------------------------------
//	
//	�n���}�b�v�t�F�[�h�G�t�F�N�g�\����
//	
//=====================================
typedef struct _EFCT_UG_DATA{
	/* �t�B�[���h�V�X�e�����[�N */
	FIELDSYS_WORK* fsys;

	/* �`��V�X�e���f�[�^ */
	EFCT_UG_DRAWSYS	drawsys;
	
	/* �I�u�W�F�N�g�f�[�^ */
	EFCT_UG_OBJ	objdata[2];
	int			obj_num;	// �I�u�W�F�N�g��
	
	/* �V�[�P���X�f�[�^ */
	int			seq;

	/* �t�F�[�h�Ȃǂ̏I�����m�̈� */
	int			wait;

	BOOL*	end;
} EFCT_UG_DATA;


//-----------------------------------------------------------------------------
//
//		�X�̃I�u�W�F�N�g�p
//
//=============================================================================
//-------------------------------------
//	
//	��l���I�u�W�F�N�g
//	
//=====================================
typedef struct {
	VecFx32			matrix;		// ���W
	CLACT_WORK_PTR	cl;			// �Z���A�N�^�[
	int				count;		// ����J�E���^
} EFCT_UG_HERO;

typedef struct {
	VecFx32			matrix;		// ���W
	CLACT_WORK_PTR	cl;			// �Z���A�N�^�[
	int				seq;		// �V�[�P���X
	int				count;		// ����J�E���^
} EFCT_UG_HERO_EX;

//-------------------------------------
//	
//	�e�I�u�W�F�N�g
//	
//=====================================
typedef struct {
	VecFx32			matrix;		// ���W
	CLACT_WORK_PTR	cl;			// �Z���A�N�^�[
	int				count;		// ����J�E���^
} EFCT_UG_SHADOW;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void UGround00(TCB_PTR tcb, void* work);		// �n���}�b�v�t�F�[�h00	�n�ʂɂ������Ă�
static void UGround01(TCB_PTR tcb, void* work);		// �n���}�b�v�t�F�[�h01	�n���ɍ~���
static void UGround02(TCB_PTR tcb, void* work);		// �n���}�b�v�t�F�[�h02	�n��������
static void UGround03(TCB_PTR tcb, void* work);		// �n���}�b�v�t�F�[�h03	�n��ɏo��

static EFCT_UG_DATA* UGroundAdd(TCB_FUNC func, FIELDSYS_WORK* fsys, u32 resload_vram);
static void UGroundDelete(TCB_PTR tcb, EFCT_UG_DATA* data);
void initDrawSys(EFCT_UG_DRAWSYS* data, int boy_girl, u32 resload_vram);
static void deleteDrawSys(EFCT_UG_DRAWSYS* data);		// �`��V�X�e���̔j��
static void makeObj(EFCT_UG_DATA* data, EFCT_UG_OBJ* obj, int num);	// �I�u�W�F�N�g�f�[�^�̍쐬
static CLACT_WORK_PTR addCellAct(EFCT_UG_DRAWSYS* drawsys, int act_no, VecFx32* mat,int pri, int drawarea);
static void deleteObj(EFCT_UG_OBJ* obj);// �I�u�W�F�N�g�f�[�^�̔j��
static void initBG(GF_BGL_INI* bgl);	// BG�ʂ̏�����
static void destBG(GF_BGL_INI* bgl);		// BG�ʂ̏�����
static void loadBG(GF_BGL_INI* bgl, const char* p_char, const char* p_pltt,const char* p_screen, int pltt_no, int frame, int charoffs);

//static void maskBGScrollInit(int sc_mask, int other_mask);
//static void maskBGScroll(GF_BGL_INI* bgl,int plane_mask, int h, int v);
//static void maskBGScrollDelete(void);

/////////////////////////////////////////////////////////////////////
//
//		�Q���\���V�X�e���p�֐��S
//
////////////////////////////////////////////////////////////////////
static void init2DDrawSys(EFCT_UG_DRAWSYS* data);	// �Q���̕`��V�X�e��������
static void load2DResFile(EFCT_UG_DRAWSYS* data, int boy_girl, u32 resload_vram);
static int loadOneData(CLACT_U_RES_MANAGER_PTR resMan, CLACT_U_RES_OBJ_TBL** resObjTbl, const char* path);

static void delete2DDrawSys(EFCT_UG_DRAWSYS* data);	// �Q���̕`��V�X�e��������
//---------------------------------------------------------
//
//	�X�̃I�u�W�F�N�g�p
//
//=========================================================
//---------�n���t�F�[�h�W�����v��l��
static void initObj00(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj00(struct _EFCT_UG_OBJ* data);
static int  moveObj00(struct _EFCT_UG_OBJ* data);
//---------�n���t�F�[�h�L����e
static void initObj01(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj01(struct _EFCT_UG_OBJ* data);
static int  moveObj01(struct _EFCT_UG_OBJ* data);
//---------�n���t�F�[�h�������l��
static void initObj02(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj02(struct _EFCT_UG_OBJ* data);
static int  moveObj02(struct _EFCT_UG_OBJ* data);
//---------�n���t�F�[�h����l��
static void initObj03(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj03(struct _EFCT_UG_OBJ* data);
static int  moveObj03(struct _EFCT_UG_OBJ* data);
//---------�n���t�F�[�h�n��ɏo�Ă����l��
static void initObj04(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj04(struct _EFCT_UG_OBJ* data);
static int  moveObj04(struct _EFCT_UG_OBJ* data);
//---------�n���t�F�[�h�k�މe
static void initObj05(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj05(struct _EFCT_UG_OBJ* data);
static int  moveObj05(struct _EFCT_UG_OBJ* data);


// �j���L�����N�^�@CLACT�@�f�[�^�p�X
const static char* BoyGirlCharPathTbl[ 2 ] = {
	"data/uground_char.resdat",
	"data/uground_char2.resdat",
};

const static char* BoyGirlPlttPathTbl[ 2 ] = {
	"data/uground_pltt.resdat",
	"data/uground_pltt2.resdat",
};


const static u8 UnderGroundEff_VramTbl[ 4 ] = {
	NNS_G2D_VRAM_TYPE_2DMAIN,
	NNS_G2D_VRAM_TYPE_MAX,
	NNS_G2D_VRAM_TYPE_MAX,
	NNS_G2D_VRAM_TYPE_2DMAIN,
};


//----------------------------------------------------------------------------
/**
 *
 *@brief	�n���}�b�v�t�F�[�h00
 *
 *@param	tcb		�^�X�N�f�[�^
 *@param	work	�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UGround00(TCB_PTR tcb, void* work)
{
	EFCT_UG_DATA* data = (EFCT_UG_DATA*)work;
	int ret[2];		// �Q�I�u�W�F�p�߂�l
	int i;			// ���[�v�p
	int last_seq;

	last_seq = data->seq; 

	if(data->drawsys.clactSet){
		// �Z���A�N�^�[���C���֐�
		CLACT_Draw(data->drawsys.clactSet);
	}

	switch(data->seq){
	case EFCT_UG00_PLAYER_OFF:
		// �C�x���glock�N���A
		FieldOBJ_MovePauseClear( Player_FieldOBJGet( data->fsys->player ) );
		// �v���C���[������
		Player_DispON_OFF_Set( data->fsys->player, FALSE );
		data->seq++;
		break;

	case EFCT_UG00_SHADOW:		// �e�쐬
		makeObj(data, &data->objdata[0], 0);		// ��l���쐬
		makeObj(data, &data->objdata[1], 1);		// �e�쐬
		data->obj_num = 2;
		data->seq ++;
		break;

	case EFCT_UG00_OBJ_MOVE:		// �I�u�W�F�N�g�𓮍삳����
		for(i=0;i<data->obj_num;i++){
			ret[i] = data->objdata[i].move(&data->objdata[i]);
		}
		// �u���b�N�t�F�[�h�J�n�����m
		if(ret[0] == EFCT_SYSRET_FADE){
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_FIELD );
		}

		// �I�����m
		for(i=0;i<data->obj_num;i++){
			if(ret[i] != EFCT_SYSRET_END ){
				break;
			}
		}
		if(i == data->obj_num){
			data->seq++;		// ����
		}
		break;

	case EFCT_UG00_FADE_WAIT:	// �t�F�[�h�҂�
		if( WIPE_SYS_EndCheck() ){
			data->seq++;
		}
		break;

	case EFCT_UG00_OAMCLEAN:
		for(i=0;i<data->obj_num;i++){
			deleteObj(&data->objdata[i]);
		}
		data->seq++;
		break;

	case EFCT_UG00_DELETE:
		*(data->end) = TRUE;

		// ��{�V�X�e�����j��
		UGroundDelete(tcb, data);
		break;
	}

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�n���}�b�v�t�F�[�h01
 *
 *@param	tcb		�^�X�N�f�[�^
 *@param	work	�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UGround01(TCB_PTR tcb, void* work)
{
	EFCT_UG_DATA* data = (EFCT_UG_DATA*)work;
	int ret;
	int last_seq;
	u16 clearPal=0;

	last_seq = data->seq; 

	if(last_seq != EFCT_UG01_DELETE){
		// �Z���A�N�^�[���C���֐�
		CLACT_Draw(data->drawsys.clactSet);
	}

	switch(data->seq){
	case EFCT_UG01_OBJ_OFF:
		// �v���C���[������
		Player_DispON_OFF_Set( data->fsys->player, FALSE );
		data->seq++;
		break;

	case EFCT_UG01_START:
		//maskBGScrollInit(GX_WND_PLANEMASK_BG2, GX_WND_PLANEMASK_BG3);
//		maskBGScrollInit(GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_OBJ, GX_WND_PLANEMASK_BG1|GX_WND_PLANEMASK_OBJ);
//		maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, -255, 0);
		
		GF_BGL_PaletteSet( GF_BGL_FRAME0_S, &clearPal, 2, 0 );	// �p���b�g�N���A
		
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_OFF);		// BG0�ʃI�t
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);		// BG1�ʃI�t
	
		
		// OBJ�̂݃u���C�g�l�X����	
		makeObj(data, &data->objdata[0], 2);		// ��l���쐬
	
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_FIELD );
		
		// ������
		Snd_SePlay( SE_UG_CHG_DOWN );

		data->obj_num = 1;
		data->seq++;
		break;
	

	case EFCT_UG01_OBJ_MOVE:		// �I�u�W�F�N�g�𓮍삳����
		ret = data->objdata[0].move(&data->objdata[0]);

		// �I�����m
		if((ret == EFCT_SYSRET_END) && (WIPE_SYS_EndCheck())){
			// ���n��
			Snd_SePlay( SE_LANDING );
			data->seq++;		// ����
			data->wait = -255;
		}
		break;
		
	case EFCT_UG01_BG_FADE:
//		maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, data->wait, 0);
		data->wait += EFCT_UG01_BG;
		if(data->wait > 0){
//			maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, 0, 0);
			data->seq++;
			// �v���C���[��\��
			Player_DispON_OFF_Set( data->fsys->player, TRUE );
		
		}
		break;

	case EFCT_UG01_OAMCLEAN:
		deleteObj(&data->objdata[0]);
		data->seq++;
		break;

	case EFCT_UG01_DELETE:		// �I���Ȃ̂Ńf�[�^�j��
		*(data->end) = TRUE;
		// ��{�V�X�e�����j��
		UGroundDelete(tcb, data);
//		maskBGScrollDelete();
		break;
	}

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�n���}�b�v�t�F�[�h02	�n��ւ̃t�F�[�h
 *
 *@param	tcb		�^�X�N�f�[�^
 *@param	work	�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UGround02(TCB_PTR tcb, void* work)
{
	EFCT_UG_DATA* data = (EFCT_UG_DATA*)work;
	int ret;
	int last_seq;

	last_seq = data->seq;

	if(last_seq != EFCT_UG02_DELETE){
		// �Z���A�N�^�[���C���֐�
		CLACT_Draw(data->drawsys.clactSet);
	}

	switch(data->seq){
	case EFCT_UG02_PLAYER_OFF:
		// �v���C���[������
		Player_DispON_OFF_Set( data->fsys->player, FALSE );
		data->seq++;
		break;

	case EFCT_UG02_START:
//		maskBGScrollInit(GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_OBJ, GX_WND_PLANEMASK_BG1|GX_WND_PLANEMASK_OBJ);
//		maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, 0, 0);
		
		makeObj(data, &data->objdata[0], 3);		// ��l���쐬

		// ���㉹
		Snd_SePlay( SE_UG_CHG_UP );

		data->obj_num = 1;
		data->seq++;
		break;

	case EFCT_UG02_BG_FADE:		// BG�ʃt�F�[�h
//		maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, data->wait, 0);
		data->wait -= EFCT_UG02_BG;
		if(data->wait < -255){
//			maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, 0, 0);
//			maskBGScrollDelete();
			GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_OFF);

			data->seq++;
		}
		break;

	case EFCT_UG02_OBJ_MOVE:
		ret = data->objdata[0].move(&data->objdata[0]);

		// �z���C�g�t�F�[�h�J�n�����m
		if(ret == EFCT_SYSRET_FADE){
			data->wait = 0;
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_FIELD );
		}
		
		// �I�����m
		if(ret == EFCT_SYSRET_END){
			data->seq++;		// ����
		}
		break;

	case EFCT_UG02_FADE_WAIT:		// �t�F�[�h�҂�
		if( WIPE_SYS_EndCheck() ){
			data->wait = 0;
			data->seq++;
		}
		break;

	case EFCT_UG02_OAMCLEAN:
		deleteObj(&data->objdata[0]);
		data->seq++;
		break;
	
	case EFCT_UG02_DELETE:		// �I���Ȃ̂Ńf�[�^�j��
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);

		*(data->end) = TRUE;
		
		// ��{�V�X�e�����j��
		UGroundDelete(tcb, data);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�n���}�b�v�t�F�[�h03
 *
 *@param	tcb		�^�X�N�f�[�^
 *@param	work	�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UGround03(TCB_PTR tcb, void* work)
{
	EFCT_UG_DATA* data = (EFCT_UG_DATA*)work;
	int ret[2];		// �Q�I�u�W�F�p�߂�l
	int i;			// ���[�v�p
	int last_seq;

	last_seq = data->seq;

	if(last_seq != EFCT_UG03_DELETE){
		// �Z���A�N�^�[���C���֐�
		CLACT_Draw(data->drawsys.clactSet);
	}
	
	switch(data->seq){
	case EFCT_UG03_START:
		// �v���C���[������
		Player_DispON_OFF_Set( data->fsys->player, FALSE );

		makeObj(data, &data->objdata[0], 4);		// ��l���쐬
		makeObj(data, &data->objdata[1], 5);		// �e�쐬
		data->obj_num = 2;
		data->seq++;
		break;

	case EFCT_UG03_FADEIN_M:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_WHITE, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_FIELD );
		data->seq++;
		break;
		
	case EFCT_UG03_FADEIN_MW:	// �T�u�t�F�[�h�C���҂�
		if( WIPE_SYS_EndCheck() ){
			// ��l����]��
			Snd_SePlay( SE_UG_CHG_TURN );
			data->seq++;
		}
		break;


	case EFCT_UG03_OBJ_MOVE:		// �I�u�W�F�N�g�𓮍삳����
		ret[0] = data->objdata[0].move(&data->objdata[0]);

		if( ret[0] == EFCT_SYSRET_END ){
			// �v���C���[��\��
			Player_DispON_OFF_Set( data->fsys->player, TRUE );

			data->wait = EFCT_UG03_OBJ_DEL_WAIT;
			data->seq++;		// ����
		}
		break;

	case EFCT_UG03_OBJ_SHADOW:
		ret[1] = data->objdata[1].move(&data->objdata[1]);

		if( data->wait <= 0 ){
			if( data->wait == 0 ){
				deleteObj(&data->objdata[0]);
				data->wait --;
			}
		}else{
			data->wait--;
		}

		if( ret[1] == EFCT_SYSRET_END ){
			data->seq++;		// ����
		}
		break;

	case EFCT_UG03_OAMCLEAN:
		deleteObj(&data->objdata[1]);
		data->seq++;
		break;

	case EFCT_UG03_DELETE:		// �I���Ȃ̂Ńf�[�^�j��

		*(data->end) = TRUE;
		// ��{�V�X�e�����j��
		UGroundDelete(tcb, data);
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�n���}�b�v�t�F�[�h�G�t�F�N�g
 *
 *@param	fsys	�t�B�[���h�V�X�e�����[�N
 *@param	no		�G�t�F�N�g�i���o�[
 *@param	end		�I���`�F�b�N�t���O
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void StartUnderGroundEffect(FIELDSYS_WORK* fsys, int no, BOOL* end)
{
	EFCT_UG_DATA* data;
		
	/* �I�u�W�F�N�g�쐬 */
	switch(no){
	case EFCT_UG_DOWN00:
		data = UGroundAdd(UGround00, fsys, UnderGroundEff_VramTbl[ no ]);
		break;
	case EFCT_UG_DOWN01:
		data = UGroundAdd(UGround01, fsys, UnderGroundEff_VramTbl[ no ]);
		break;
	case EFCT_UG_UP00:
		data = UGroundAdd(UGround02, fsys, UnderGroundEff_VramTbl[ no ]);
		break;
	case EFCT_UG_UP01:
		data = UGroundAdd(UGround03, fsys, UnderGroundEff_VramTbl[ no ]);
		break;
	}

	data->end = end;
	data->fsys = fsys;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�n���G�t�F�N�g�f�[�^�쐬
 *
 *@param	func	����^�X�N
 *@param	fsys	�t�B�[���h�V�X�e��
 *@param	resload_vram	���\�[�X�ǂݍ���VRAM
 *
 *@return	EFCT_UG_DATA*	�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
EFCT_UG_DATA* UGroundAdd(TCB_FUNC func, FIELDSYS_WORK* fsys, u32 resload_vram )
{
	EFCT_UG_DATA* data;
	TCB_PTR tcb;
	int boy_girl;
	MYSTATUS* status;

		
	/* �I�u�W�F�N�g�쐬 */
	tcb = PMDS_taskAdd(func, sizeof(EFCT_UG_DATA), UNDER_TCB_PRI, HEAPID_FIELD);
	data = TCB_GetWork(tcb);

	/* ��l�����j�������擾 */
	status = SaveData_GetMyStatus( fsys->savedata );
	boy_girl = MyStatus_GetMySex( status );
	
	/* �`��V�X�e���쐬 */
	initDrawSys(&data->drawsys, boy_girl, resload_vram );

	return data;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�n���}�b�v�t�F�[�h�f�[�^�j��
 *
 *@param	tcb		�^�X�N�|�C���^
 *@param	data	�j���f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UGroundDelete(TCB_PTR tcb, EFCT_UG_DATA* data)
{
	// �`��V�X�e���j��
	deleteDrawSys(&data->drawsys);

	PMDS_taskDel(tcb);	//�^�X�N�I��	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��V�X�e�������������f�[�^�̓ǂݍ���
 *
 *@param	data		�`��V�X�e���f�[�^
 *@param	boy_girl	�j������
 *@param	resload_vram	�ǂݍ���VRAM
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initDrawSys(EFCT_UG_DRAWSYS* data, int boy_girl, u32 resload_vram)
{
	// �`��V�X�e��������
	init2DDrawSys(data);

	// ���\�[�X�ǂݍ���
	load2DResFile(data, boy_girl, resload_vram);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��f�[�^�̔j��
 *
 *@param	data		�`��V�X�e���f�[�^
 *
 *@return	none 
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteDrawSys(EFCT_UG_DRAWSYS* data)
{
	delete2DDrawSys(data);
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	�Q���`��V�X�e���쐬
 *
 *@param	data		�`��V�X�e���f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void init2DDrawSys(EFCT_UG_DRAWSYS* data)
{
	// �ȈՃZ���A�N�^�[�Z�b�g�쐬
	// ��ō쐬�������LOAM�}�l�[�W�����g�p���ă����_���[���쐬���A
	// �Z���A�N�^�[�Z�b�g�̍쐬���s��
	data->clactSet = CLACT_U_SetEasyInit( 2, &data->renddata, HEAPID_FIELD );
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Q�����\�[�X��ǂݍ���
 *
 *@param	data
 *@param	boy_girl	�j������
 *@param	resload_vram	�ǂݍ���VRAM
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void load2DResFile(EFCT_UG_DRAWSYS* data, int boy_girl, u32 resload_vram)
{
	int i;
	void* buff;
	
	// ���\�[�X�}�l�[�W���쐬
	for(i=0;i<DRAW_2D_RES_NUM;i++){
		data->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_FIELD);
	}

	// ���\�[�X�ǂݍ���
	// �L�����N�^
	data->resObjNum[ CLACT_U_CHAR_RES ] = loadOneData(
			data->resMan[ CLACT_U_CHAR_RES ], 
			&data->resObjTbl[ CLACT_U_CHAR_RES ],
			BoyGirlCharPathTbl[ boy_girl ] );

	// �ǂݍ���VRAM�ݒ�
	for( i=0; i<data->resObjTbl[ CLACT_U_CHAR_RES ]->tbl_now; i++ ){
		CLACT_U_ResManagerSetResObjVramType( data->resObjTbl[ CLACT_U_CHAR_RES ]->tbl[ i ], resload_vram );
	}
	
	// �p���b�g
	data->resObjNum[ CLACT_U_PLTT_RES ] = loadOneData(
			data->resMan[ CLACT_U_PLTT_RES ], 
			&data->resObjTbl[ CLACT_U_PLTT_RES ],
			BoyGirlPlttPathTbl[ boy_girl ] );

	// �ǂݍ���VRAM�ݒ�
	for( i=0; i<data->resObjTbl[ CLACT_U_PLTT_RES ]->tbl_now; i++ ){
		CLACT_U_ResManagerSetResObjVramType( data->resObjTbl[ CLACT_U_PLTT_RES ]->tbl[ i ], resload_vram );
	}


	// �Z��
	data->resObjNum[ CLACT_U_CELL_RES ] = loadOneData(
			data->resMan[ CLACT_U_CELL_RES ], 
			NULL,
			"data/uground_cell.resdat");
	// �Z���A�j��
	data->resObjNum[ CLACT_U_CELLANM_RES ] = loadOneData(
			data->resMan[ CLACT_U_CELLANM_RES ], 
			NULL,
			"data/uground_cellanm.resdat");

	// �L�����N�^�}�l�[�W���ɓo�^
	// Vram�ɔz�u���܂��B
	CLACT_U_CharManagerSetsAreaCont(data->resObjTbl[0]);

	// �p���b�g�}�l�[�W���ɓo�^
	// Vram�ɔz�u���܂��B
	CLACT_U_PlttManagerSetsCleanArea(data->resObjTbl[1]);


	// �Z���A�N�^�[�w�b�_�ǂݍ���
	buff = sys_LoadFile( HEAPID_FIELD, "data/uground_clact.cldat" );
	data->clactHeader = CLACT_U_MakeHeaderBinary(
			buff, HEAPID_FIELD,
			data->resMan[ CLACT_U_CHAR_RES ], 
			data->resMan[ CLACT_U_PLTT_RES ], 
			data->resMan[ CLACT_U_CELL_RES ],
			data->resMan[ CLACT_U_CELLANM_RES ],
			NULL, NULL);
	sys_FreeMemoryEz( buff );
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�^�C�v�̃��\�[�X���w�b�_�[�f�[�^����ǂݍ���
 *
 *@param	resMan		���\�[�X�}�l�[�W��(�쐬�ς�)
 *@param	resObjTbl	���\�[�X�I�u�W�F�e�[�u���󂯎���
 *@param	path		�����w�b�_�p�X
 *
 *@return	int		�e�[�u����
 *
 *
 */
//-----------------------------------------------------------------------------
static int loadOneData(CLACT_U_RES_MANAGER_PTR resMan, CLACT_U_RES_OBJ_TBL** resObjTbl, const char* path)
{
	CLACT_U_RES_HEADER_PTR res_head;		// ���\�[�X�w�b�_
	CLACT_U_RES_OBJ_TBL* work;
	int	tbl_num;							// �w�b�_���e�[�u����
	void* buff;
	

	res_head = sys_AllocMemoryLo( HEAPID_FIELD, CLACT_U_ResManagerGetHeaderSize() );

	// �w�b�_�ǂݍ���
	buff = sys_LoadFile( HEAPID_FIELD, path );
	CLACT_U_ResManagerHeaderLoadBinary(buff, res_head, HEAPID_FIELD);
	sys_FreeMemoryEz( buff );

	// �w�b�_�����̃��\�[�X�I�u�W�F�e�[�u���쐬
	if(resObjTbl != NULL){
		tbl_num		= CLACT_U_ResManagerHeaderSetDataNum(res_head);
		*resObjTbl	= CLACT_U_ResManagerResObjTblMake(tbl_num, HEAPID_FIELD);
		work = *resObjTbl;
	}else{
		work = NULL;
	}

	// ���\�[�X�ǂݍ���
	// �L�����N�^�f�[�^�ǂݍ���
	tbl_num = CLACT_U_ResManagerResAddsHd(
				resMan,
				res_head,
				work,
				HEAPID_FIELD);

	// �w�b�_�j��
	CLACT_U_ResManagerHeaderFree(res_head);

	// �w�b�_�Ŋm�ۂ������[�N�j��
	sys_FreeMemoryEz(res_head);

	return tbl_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�QD�`��V�X�e���f�[�^�j��
 *
 *@param	data		�`��V�X�e���f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delete2DDrawSys(EFCT_UG_DRAWSYS* data)
{
	int i;
	
	// �Z�b�g�̔j��
	CLACT_DestSet(data->clactSet);
	data->clactSet = NULL;
	
	// �Z���A�N�^�[�w�b�_�[�j��
	CLACT_U_CLACT_HeaderTblDelete(data->clactHeader);
	data->clactHeader = NULL;

	// �L�����N�^�f�[�^�j��
	CLACT_U_CharManagerDeletes( data->resObjTbl[ CLACT_U_CHAR_RES ] );
	
	// �p���b�g�f�[�^�j��
	CLACT_U_PlttManagerDeletes( data->resObjTbl[ CLACT_U_PLTT_RES ] );

	// �L�����N�^�ƃp���b�g�̃��\�[�X�I�u�W�F�e�[�u����j��
	for(i=0;i<2;i++){
		CLACT_U_ResManagerResObjTblDelete(data->resObjTbl[i]);
	}

	// ���\�[�X�}�l�[�W���j��
	for(i=0;i< DRAW_2D_RES_NUM;i++){
		CLACT_U_ResManagerDelete(data->resMan[i]);
	}
	
//	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
//	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�u�W�F�N�g�̍쐬
 *
 *@param	data	�G�t�F�N�g�f�[�^
 *@param	obj		�f�[�^���͂���I�u�W�F
 *@param	num		��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void makeObj(EFCT_UG_DATA* data, EFCT_UG_OBJ* obj, int num)
{
	memset(obj, 0, sizeof(EFCT_UG_OBJ));

	switch(num){
	case 0:
		obj->init	= initObj00;
		obj->delete = deleteObj00;
		obj->move	= moveObj00;
		break;
	case 1:
		obj->init	= initObj01;
		obj->delete = deleteObj01;
		obj->move	= moveObj01;
		break;
	case 2:
		obj->init	= initObj02;
		obj->delete = deleteObj02;
		obj->move	= moveObj02;
		break;
	case 3:
		obj->init	= initObj03;
		obj->delete = deleteObj03;
		obj->move	= moveObj03;
		break;
	case 4:
		obj->init	= initObj04;
		obj->delete = deleteObj04;
		obj->move	= moveObj04;
		break;
	case 5:
		obj->init	= initObj05;
		obj->delete = deleteObj05;
		obj->move	= moveObj05;
		break;
	}

	obj->init(&data->drawsys, obj);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�ɓo�^
 *
 *@param	drawsys		�`��V�X�e��
 *@param	act_no		�A�N�^�[�i���o�[
 *@param	mat			���W
 *@param	pri			�\���D�揇��
 *@param	drawarea	�`��G���A(�ŏ��́j
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_WORK_PTR addCellAct(EFCT_UG_DRAWSYS* drawsys, int act_no, VecFx32* mat, int pri, int drawarea)
{
	CLACT_ADD ca;
	CLACT_WORK_PTR obj;
	VecFx32 sca = {FX32_ONE, FX32_ONE, FX32_ONE};
	
	memset(&ca,0,sizeof(CLACT_ADD));
	ca.ClActSet		= drawsys->clactSet;
	ca.ClActHeader	= &drawsys->clactHeader->tbl[act_no];
	ca.mat			= *mat;
	ca.sca			= sca;
	ca.pri			= pri;
	ca.DrawArea		= drawarea;
	ca.heap			= HEAPID_FIELD;
	
	obj = CLACT_Add(&ca);
	GF_ASSERT(obj&&("�Z���A�N�^�[�o�^���s\n"));

	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�u�W�F�N�g
 *
 *@param	data
 *@param	obj
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteObj(EFCT_UG_OBJ* obj)
{
	obj->delete( obj);
	memset(obj, 0, sizeof(EFCT_UG_OBJ));
}

//---------------------------------------------------------
//
//	�X�̃I�u�W�F�N�g�p
//
//=========================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	��l���I�u�W�F�N�g�̓o�^
 *
 *@param	drawsys		�`��f�[�^
 *@param	data		�I�u�W�F�N�g�f�[�^�o�^�e�[�u��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj00(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO* obj_w;
	
	// �I�u�W�F�N�g�̍쐬
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_HERO));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_HERO));
	
	obj_w = (EFCT_UG_HERO*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = EFECT_UGCOMMON_OBJ_MAT_Y;
	
	// �Z���̓o�^
	obj_w->cl = addCellAct(drawsys, 0, &obj_w->matrix, 0, 1);
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	��l���I�u�W�F��j��
 *
 *@param	data		�I�u�W�F�f�[�^
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteObj00(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO* obj_w = (EFCT_UG_HERO*)data->data;
	
	if(data->data != NULL){
		// �Z���A�N�^�[�폜
		CLACT_Delete(obj_w->cl);

		// �I�u�W�F�N�g�j��
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	��l���I�u�W�F�N�g�̓���֐�
 *
 *@param	data	��l���I�u�W�F�N�g
 *
 *@retval	EFCT_SYSRET_OK		����
 *@retval	EFCT_SYSRET_FADE	�t�F�[�h�J�n
 *@retval	EFCT_SYSRET_END		�I��
 *
 *
 */
//-----------------------------------------------------------------------------
int moveObj00(struct _EFCT_UG_OBJ* data)
{
	VecFx32	mat;	// �Z���`����W
	EFCT_UG_HERO* obj_w = (EFCT_UG_HERO*)data->data;
	
	// �W�����v������
	// ����t�߂Ńt�F�[�h�J�n
	// �n�ʂɓ��B������I��
	if(obj_w->count <= EFCT_UG00_OBJ_END){
		mat = obj_w->matrix;
		mat.y -= FX_Mul(FX_SinIdx(obj_w->count), EFCT_UG00_OBJ_JUMP_DIS);
		CLACT_SetMatrix(obj_w->cl, &mat);		// ���W��ݒ�
		obj_w->count += EFCT_UG00_OBJ_CNNUM;
		CLACT_AnmFrameChg(obj_w->cl, FX32_ONE);
	
		if(obj_w->count == EFCT_UG00_FADE_START){	//����Ńt�F�[�h�J�n
			return EFCT_SYSRET_FADE;
		}else{
			return EFCT_SYSRET_OK;
		}
	}
	
	return EFCT_SYSRET_END;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�쐬
 *
 *@param	drawsys		�`��f�[�^
 *@param	data		�I�u�W�F�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj01(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w;
	
	// �I�u�W�F�N�g�̍쐬
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_SHADOW));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_SHADOW));
	
	obj_w = (EFCT_UG_SHADOW*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = 96*FX32_ONE;
	
	// �Z���̓o�^
	obj_w->cl = addCellAct(drawsys, 1, &obj_w->matrix,1, 1);
}
void deleteObj01(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w = (EFCT_UG_SHADOW*)data->data;
	
	if(data->data != NULL){
		// �Z���A�N�^�[�폜
		CLACT_Delete(obj_w->cl);

		// �I�u�W�F�N�g�j��
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�𓮂���
 *
 *@param	data
 *
 *@retval	EFCT_SYSRET_OK		����
 *@retval	EFCT_SYSRET_FADE	�t�F�[�h�J�n
 *@retval	EFCT_SYSRET_END		�I��
 *
 *
 */
//-----------------------------------------------------------------------------
int moveObj01(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w = (EFCT_UG_SHADOW*)data->data;
	
	// �e��傫�����āA�Ō�܂ő傫���Ȃ�����I��
	if(obj_w->count < EFCT_UG00_SHADOW_COUNT){
		CLACT_AnmFrameChg(obj_w->cl, FX32_ONE);
		obj_w->count++;
		return EFCT_SYSRET_OK;	
	}

	return EFCT_SYSRET_END;	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����Ă����I�u�W�F�N�g
 *
 *@param	drawsys		�`��f�[�^
 *@param	data		�I�u�W�F�N�g�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj02(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO* obj_w;
	
	// �I�u�W�F�N�g�̍쐬
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_HERO));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_HERO));
	
	obj_w = (EFCT_UG_HERO*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = EFCT_UG01_OBJ_MAT_Y;
	
	// �Z���̓o�^
	obj_w->cl = addCellAct(drawsys, 0, &obj_w->matrix, 0, 1);
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	������I�u�W�F�j���֐�
 *
 *@param	data
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteObj02(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO* obj_w = (EFCT_UG_HERO*)data->data;
	
	if(data->data != NULL){
		// �Z���A�N�^�[�폜
		CLACT_Delete(obj_w->cl);

		// �I�u�W�F�N�g�j��
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	������I�u�W�F�N�g
 *
 *@param	data
 *
 *@retval	EFCT_SYSRET_OK		����
 *@retval	EFCT_SYSRET_FADE	�t�F�[�h�J�n
 *@retval	EFCT_SYSRET_END		�I��
 *
 *
 */
//-----------------------------------------------------------------------------
int  moveObj02(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO* obj_w = (EFCT_UG_HERO*)data->data;
	

	obj_w->matrix.y += EFCT_UG01_MOVE;
	CLACT_SetMatrix(obj_w->cl, &obj_w->matrix);		// ���W��ݒ�
	CLACT_AnmFrameChg(obj_w->cl, FX32_ONE);

	if(obj_w->count == 0){
		if(obj_w->matrix.y >= EFCT_UG01_REST){
			obj_w->matrix.y = EFCT_UG01_OBJ_MAT_REST_Y;
			obj_w->count++;
		}
	}else{
		if(obj_w->matrix.y >= EFCT_UG01_END){
			obj_w->matrix.y = EFCT_UG01_END;
			CLACT_SetMatrix(obj_w->cl, &obj_w->matrix);		// ���W��ݒ�
			return EFCT_SYSRET_END;
		}
	}
	
	return EFCT_SYSRET_OK;

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�u�W�F�N�g������
 *
 *@param	drawsys		�`��f�[�^
 *@param	data		�I�u�W�F�N�g�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj03(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO_EX* obj_w;
	
	// �I�u�W�F�N�g�̍쐬
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_HERO_EX));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_HERO_EX));
	
	obj_w = (EFCT_UG_HERO_EX*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = EFECT_UGCOMMON_OBJ_MAT_Y;
	
	// �Z���̓o�^
	obj_w->cl = addCellAct(drawsys, 0, &obj_w->matrix, 0, 1);

	//�A�j���[�V����Sequence�ύX
	CLACT_AnmChg(obj_w->cl, 1);
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�j���֐�
 *
 *@param	data
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteObj03(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO_EX* obj_w = (EFCT_UG_HERO_EX*)data->data;
	
	if(data->data != NULL){
		// �Z���A�N�^�[�폜
		CLACT_Delete(obj_w->cl);

		// �I�u�W�F�N�g�j��
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	����֐�
 *
 *@param	data
 *
 *@retval	EFCT_SYSRET_OK		����
 *@retval	EFCT_SYSRET_FADE	�t�F�[�h�J�n
 *@retval	EFCT_SYSRET_END		�I��
 *
 *
 */
//-----------------------------------------------------------------------------
int  moveObj03(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO_EX* obj_w = (EFCT_UG_HERO_EX*)data->data;
	int	ret	= EFCT_SYSRET_OK;	// �߂�l

	switch(obj_w->seq){
	case 0:		// ��]�𑁂�����
		obj_w->count += EFCT_UG02_ROTA_SA;
		CLACT_AnmFrameChg(obj_w->cl, obj_w->count);
		
		if(obj_w->count >= EFCT_UG02_ROTA_SE){
			obj_w->seq++;
		}
		break;
	
	case 1:
		if(obj_w->matrix.y > EFCT_UG02_REST){
			obj_w->matrix.y -= EFCT_UG02_MOVE;
			CLACT_SetMatrix(obj_w->cl, &obj_w->matrix);		// ���W��ݒ�
			CLACT_AnmFrameChg(obj_w->cl, obj_w->count);
		}else{
			obj_w->matrix.y = EFCT_UG02_OBJ_MAT_REST_Y;
			obj_w->seq++;
		}	
		break;
	
	case 2:
		obj_w->matrix.y -= EFCT_UG02_MOVE;
		CLACT_SetMatrix(obj_w->cl, &obj_w->matrix);		// ���W��ݒ�
		CLACT_AnmFrameChg(obj_w->cl, obj_w->count);
		if((obj_w->matrix.y < EFCT_UG02_FADE_S)){
			ret = EFCT_SYSRET_FADE;
			obj_w->seq++;
		}
		break;

	case 3:
		if(obj_w->matrix.y > EFCT_UG02_END){
			obj_w->matrix.y -= EFCT_UG02_MOVE;
			CLACT_SetMatrix(obj_w->cl, &obj_w->matrix);		// ���W��ݒ�
			CLACT_AnmFrameChg(obj_w->cl, obj_w->count);
		}else{
			obj_w->seq++;
		}
		break;

	case 4:
		ret = EFCT_SYSRET_END;
		break;
	}
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	��l���I�u�W�F�N�g�̓o�^
 *
 *@param	drawsys		�`��f�[�^
 *@param	data		�I�u�W�F�N�g�f�[�^�o�^�e�[�u��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj04(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO_EX* obj_w;
	
	// �I�u�W�F�N�g�̍쐬
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_HERO_EX));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_HERO_EX));
	
	obj_w = (EFCT_UG_HERO_EX*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = EFECT_UGCOMMON_OBJ_MAT_Y;
	
	// �Z���̓o�^
	obj_w->cl = addCellAct(drawsys, 0, &obj_w->matrix, 0, 1);
	
	//�A�j���[�V����Sequence�ύX
	CLACT_AnmChg(obj_w->cl, 1);
	obj_w->count = EFCT_UG03_ROTA_S;

	// �`��t���O�I�t
	CLACT_SetDrawFlag(obj_w->cl, 0);
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	��l���I�u�W�F��j��
 *
 *@param	data		�I�u�W�F�f�[�^
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteObj04(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO_EX* obj_w = (EFCT_UG_HERO_EX*)data->data;
	
	if(data->data != NULL){
		// �Z���A�N�^�[�폜
		CLACT_Delete(obj_w->cl);

		// �I�u�W�F�N�g�j��
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	��l���I�u�W�F�N�g�̓���֐�
 *
 *@param	data	��l���I�u�W�F�N�g
 *
 *@retval	EFCT_SYSRET_OK		����
 *@retval	EFCT_SYSRET_FADE	�t�F�[�h�J�n
 *@retval	EFCT_SYSRET_END		�I��
 *
 *
 */
//-----------------------------------------------------------------------------
int moveObj04(struct _EFCT_UG_OBJ* data)
{
	VecFx32	mat;	// �Z���`����W
	EFCT_UG_HERO_EX* obj_w = (EFCT_UG_HERO_EX*)data->data;
	int	ret	= EFCT_SYSRET_OK;	// �߂�l
	
	switch(obj_w->seq){
	case 0:
		// �`��t���O�I��
		CLACT_SetDrawFlag(obj_w->cl, 1);
		obj_w->seq++;
		break;
	case 1:
		if(obj_w->count <= EFCT_UG03_OBJ_END){
			mat = obj_w->matrix;
			mat.y -= FX_Mul(FX_SinIdx(obj_w->count), EFCT_UG03_OBJ_JUMP_DIS);
			CLACT_SetMatrix(obj_w->cl, &mat);		// ���W��ݒ�
			obj_w->count += EFCT_UG03_OBJ_CNNUM;
			CLACT_AnmFrameChg(obj_w->cl, FX32_ONE);
	
		}else{
			obj_w->seq++;
		}
		break;
	case 2:		// ��]��x������
		obj_w->count -= EFCT_UG03_ROTA_SA;
		CLACT_AnmFrameChg(obj_w->cl, obj_w->count);
		
		if(obj_w->count <= EFCT_UG03_ROTA_SE){
			obj_w->seq++;
		}
		break;
	case 3:
		ret = EFCT_SYSRET_END;
		break;
	}
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�쐬
 *
 *@param	drawsys		�`��f�[�^
 *@param	data		�I�u�W�F�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj05(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w;
	
	// �I�u�W�F�N�g�̍쐬
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_SHADOW));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_SHADOW));
	
	obj_w = (EFCT_UG_SHADOW*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = 96*FX32_ONE;
	
	// �Z���̓o�^
	obj_w->cl = addCellAct(drawsys, 1, &obj_w->matrix, 1, 1);

	//�A�j���[�V����Sequence�ύX
	CLACT_AnmChg(obj_w->cl, 1);
}
void deleteObj05(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w = (EFCT_UG_SHADOW*)data->data;
	
	if(data->data != NULL){
		// �Z���A�N�^�[�폜
		CLACT_Delete(obj_w->cl);

		// �I�u�W�F�N�g�j��
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�𓮂���
 *
 *@param	data
 *
 *@retval	EFCT_SYSRET_OK		����
 *@retval	EFCT_SYSRET_FADE	�t�F�[�h�J�n
 *@retval	EFCT_SYSRET_END		�I��
 *
 *
 */
//-----------------------------------------------------------------------------
int moveObj05(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w = (EFCT_UG_SHADOW*)data->data;
	
	// �e��傫�����āA�Ō�܂ő傫���Ȃ�����I��
	if(obj_w->count < EFCT_UG03_SHADOW_COUNT){
		CLACT_AnmFrameChg(obj_w->cl, FX32_ONE);
		obj_w->count++;
		return EFCT_SYSRET_OK;	
	}

	return EFCT_SYSRET_END;	
}

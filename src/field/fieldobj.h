//==============================================================================
/**
 * @file	fieldobj.h
 * @brief	�t�B�[���h�I�u�W�F�N�g
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FIELD_OBJ_H_FILE
#define FIELD_OBJ_H_FILE

#include "system/arc_tool.h"
#include "localres.h"

#include "field_common.h"
#include "fieldobj_header.h"
#include "fieldobj_code.h"

#include "eoa.h"

//==============================================================================
//	debug
//==============================================================================
//----
#ifdef PM_DEBUG
//----
//#define DEBUG_ALIES			//��`�ŃG�C���A�X�e�X�g
//----
#endif	//PM_DEBUG
//----

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	fx
//--------------------------------------------------------------
#define NUM_FX32(a)	(FX32_ONE*(a))							///<����->FX32�^��
#define FX32_NUM(a)	((a)/FX32_ONE)							///<FX32->������
#define NUM_FX16(a)	(FX16_ONE*(a))							///<����->FX16�^��
#define FX16_NUM(a)	((a)/FX16_ONE)							///<FX16->������

//--------------------------------------------------------------
//	�O���b�h
//--------------------------------------------------------------
#define GRID_ONE	(1)										///<1�O���b�h
#define GRID		(16)									///<1�O���b�h�P�ʁB�����W16
#define GRID_HALF	(GRID>>1)								///<1/2�O���b�h
#define GRID_SHIFT	(4)									///<�O���b�h�����W�ϊ��ɕK�v�ȃV�t�g��
#define GRID_SIZE(a) ((a)<<GRID_SHIFT)						///<�O���b�h���T�C�Y�ϊ�
#define SIZE_GRID(a) ((a)>>GRID_SHIFT)						///<���T�C�Y�O���b�h�ϊ�
#define GRID_SIZE_FX32(a) (GRID_SIZE(a)*FX32_ONE)			///<�O���b�h���T�C�YFX32�ϊ�
#define SIZE_GRID_FX32(a) (SIZE_GRID(a)/FX32_ONE)			///<���T�C�Y�O���b�hFX32�ϊ�
#define GRID_FX32 (GRID*FX32_ONE)							///<1�O���b�h����
#define GRID_HALF_FX32 (GRID_FX32>>1)						///<1/2�O���b�h����

//--------------------------------------------------------------
//	�����O���b�h
//--------------------------------------------------------------
#define H_GRID_ONE	(1)										///<1�O���b�h
#define H_GRID		(8)										///<1�O���b�h�P�ʁB�����W8
#define H_GRID_HALF	(H_GRID>>1)								///<1/2�O���b�h
#define H_GRID_SHIFT	(3)								///<�O���b�h�����W�ϊ��ɕK�v�ȃV�t�g��
#define H_GRID_SIZE(a) ((a)<<H_GRID_SHIFT)					///<�O���b�h���T�C�Y�ϊ�
#define SIZE_H_GRID(a) ((a)>>H_GRID_SHIFT)					///<���T�C�Y�O���b�h�ϊ�
#define H_GRID_SIZE_FX32(a) (H_GRID_SIZE(a)*FX32_ONE)		///<�O���b�h���T�C�YFX32�ϊ�
#define SIZE_H_GRID_FX32(a) (SIZE_H_GRID(a)/FX32_ONE)		///<���T�C�Y�O���b�hFX32�ϊ�
#define H_GRID_FX32 (H_GRID*FX32_ONE)						///<1�O���b�h����

#define H_GRID_FELLOW_SIZE (H_GRID_ONE*2)			///<OBJ���m�̓����蔻��@�����q�b�g�T�C�Y

//--------------------------------------------------------------
//	�ړ�����
//--------------------------------------------------------------
//#define	MOVE_LIMIT_NOT (0xffff)				///<�ړ���������->�Z�[�u�f�[�^s8�ׁ̈A�ύX
#define	MOVE_LIMIT_NOT (-1)								///<�ړ���������

//--------------------------------------------------------------
//	���x
//--------------------------------------------------------------
#define FRAME_1	(1)											///<1�t���[��
#define FRAME_1_SYNC (2)									///<1�t���[����V�V���N��
#define GRID_FRAME_1_FX32 (FX32_ONE/FRAME_1_SYNC)			///<�O���b�h1�t���[���ړ���

#define GRID_FRAME_32 (32)
#define GRID_FRAME_16 (16)
#define GRID_FRAME_8 (8)
#define GRID_FRAME_4 (4)
#define GRID_FRAME_2 (2)
#define GRID_FRAME_1 (1)

#define GRID_VALUE_SPEED_32 (GRID_FX32/GRID_FRAME_32)
#define GRID_VALUE_SPEED_16 (GRID_FX32/GRID_FRAME_16)
#define GRID_VALUE_SPEED_8 (GRID_FX32/GRID_FRAME_8)
#define GRID_VALUE_SPEED_4 (GRID_FX32/GRID_FRAME_4)
#define GRID_VALUE_SPEED_2 (GRID_FX32/GRID_FRAME_2)
#define GRID_VALUE_SPEED_1 (GRID_FX32/GRID_FRAME_1)

#define GRID_VALUE_SPEED_FRAME(g,f) ((GRID_FX32*g)/f)

//--------------------------------------------------------------
//	�r���{�[�h�A�N�^�[�A�j���[�V�����t���[��
//--------------------------------------------------------------
#define BLACTANM_FRAME_1 (FX32_ONE)							///<1�t���[�����x
#define BLACTANM_FRAME_2 (BLACTANM_FRAME_1 * 2)				///<2�t���[�����x
#define BLACTANM_FRAME_3 (BLACTANM_FRAME_1 * 3)				///<2�t���[�����x
#define BLACTANM_FRAME_4 (BLACTANM_FRAME_1 * 4)				///<4�t���[�����x
#define BLACTANM_FRAME_8 (BLACTANM_FRAME_1 * 8)				///<8�t���[�����x

#define BLACTANM_FRAME_05 (BLACTANM_FRAME_1/2)				///<1/2�t���[�����x

#define BLACTANM_STEP_FRAME (8)								///<����ړ��A�j���̃t���[����
#define BLACTANM_STEP_DASH_FRAME (4)						///<�_�b�V������ړ��A�j���t���[����

//--------------------------------------------------------------
//	���W�␮
//--------------------------------------------------------------
#define FLDOBJ_VEC_X_GRID_OFFS_FX32 (GRID_HALF_FX32)		///<X�����O���b�h�␮
#define FLDOBJ_VEC_Y_GRID_OFFS_FX32 (0)						///<Y�����O���b�h�␮
#define FLDOBJ_VEC_Z_GRID_OFFS_FX32 (GRID_HALF_FX32)		///<Z�����O���b�h�␮

//--------------------------------------------------------------
//	�\�����W�␮
//--------------------------------------------------------------
#define FLDOBJ_BLACT_X_GROUND_OFFS_FX32 (0)					///<X�����n�ʕ␮
#define FLDOBJ_BLACT_Y_GROUND_OFFS_FX32 (0)					///<Y�����n�ʕ␮
#define FLDOBJ_BLACT_Z_GROUND_OFFS_FX32 (FX32_ONE*6)		///<Z�����n�ʕ␮

//Y�����n�ʕ␮<<20050901 del saito
//#define FLDOBJ_BLACT_Y_GROUND_OFFS_FX32 (FX32_ONE*7)
//Z�����n�ʕ␮<<20050901 del saito
//#define FLDOBJ_BLACT_Z_GROUND_OFFS_FX32 (-(FX32_ONE*4))

//--------------------------------------------------------------
///	�t�B�[���hOBJ���������o�^FieldOBJ_AddFile()��
///	1�t���[���ɒǉ��ł���ő吔�B
/// 05.07.29 ����ł�1�t���[����4��ȏ�r���{�[�h��ǉ����鎖���o���Ȃ��B
/// 05.08.04 ������...��?
//--------------------------------------------------------------
//#define FLDOBJ_ADD_1FRAME_MAX (4)

//--------------------------------------------------------------
///	�t�B�[���hOBJ�@V�u�����N���̃e�N�X�`���]���ő��
//--------------------------------------------------------------
//#define FLDOBJ_BLACT_VINTR_TEX_LOAD_MAX (6)
#define FLDOBJ_BLACT_VINTR_TEX_LOAD_MAX (32)

//--------------------------------------------------------------
///	�t�B�[���hOBJ�@�Q�X�g�ǉ��Ǘ�������1�t���[������
///	�r���{�[�h�A�N�^�[��ǉ��ł���ő吔
/// 05.09.16 ����͈�̂ň�t�B�������ׂ��B
//--------------------------------------------------------------
//#define FLDOBJ_GUEST_BLACT_ADD_ONE_FRAME_MAX (1)
#define FLDOBJ_GUEST_BLACT_ADD_ONE_FRAME_MAX (4)

//--------------------------------------------------------------
///	���M�����[�@�Q�X�g����
//--------------------------------------------------------------
typedef enum
{
	REGULAR = 0,											///<���M�����[
	GUEST,													///<�Q�X�g
	NOT_REGULAR_GUEST,										///<���M�����[�ł��Q�X�g�ł�����
}REGULAR_GUEST;

//--------------------------------------------------------------
///	�e�N�X�`���o�^����
//--------------------------------------------------------------
typedef enum
{
	TEX_NON = 0,
	TEX_REGULAR,
	TEX_GUEST,
	TEX_REGULAR_RESERVE,
	TEX_GUEST_RESERVE,
}TEXREG_TYPE;

//--------------------------------------------------------------
//	���\�[�X�}�l�[�W���Ǘ���
//--------------------------------------------------------------
#define FLDOBJ_RESM_REG_MAX_MDL (4)							///<���M�����[���f��ID�Ǘ���
#define FLDOBJ_RESM_GST_MAX_MDL (4)							///<�Q�X�g���f��ID�Ǘ���
#define FLDOBJ_RESM_REG_MAX_ANM (4)							///<���M�����[�A�j��ID�Ǘ���
#define FLDOBJ_RESM_GST_MAX_ANM (4)							///<�Q�X�g�A�j��ID�Ǘ���
#define FLDOBJ_RESM_REG_MAX_TEX (24)						///<���M�����[�e�N�X�`��ID�Ǘ���
#define FLDOBJ_RESM_GST_MAX_TEX (8)							///<�Q�X�g�e�N�X�`��ID�Ǘ���

#define FLDOBJ_RESM_MAX_MDL (8)								///<���f��ID�Ǘ��ő吔
#define FLDOBJ_RESM_MAX_ANM (8)								///<�A�j��ID�Ǘ��ő吔
#define FLDOBJ_RESM_MAX_TEX (32)							///<�e�N�X�`��ID�Ǘ��ő吔

#define FLDOBJ_LRES_SIZE_MDL (0x1000)						///<���f�����O�f�[�^�T�C�Y �W��
#define FLDOBJ_LRES_SIZE_ANM (0x0080)						///<�A�j���f�[�^�T�C�Y�@�W��
#define FLDOBJ_LRES_MAXSIZE_MDL (FLDOBJ_LRES_SIZE_MDL*FLDOBJ_RESM_MAX_MDL)
#define FLDOBJ_LRES_MAXSIZE_ANM (FLDOBJ_LRES_SIZE_ANM*FLDOBJ_RESM_MAX_ANM)

//--------------------------------------------------------------
///	���M�����[�ŕK���풓���鐔
//--------------------------------------------------------------
enum
{
	FLDOBJ_RESM_REG_ALWAYS_HERO = 0,						///<���@
	FLDOBJ_RESM_REG_ALWAYS_KANBAN,							///<�Ŕ�
	FLDOBJ_RESM_REG_ALWAYS_ETC,								///<���̑�
	
	FLDOBJ_RESM_REG_ALWAYS_NUM,								///<�ő�
};

//--------------------------------------------------------------
//	FIELD_OBJ_SYS �X�e�[�^�X�r�b�g
//--------------------------------------------------------------
#define FLDOBJSYS_STA_BIT_NON				(0)				///<�X�e�[�^�X����
#define FLDOBJSYS_STA_BIT_DRAW_INIT_COMP	(1<<0)			///<�`�揉��������
#define FLDOBJSYS_STA_BIT_MOVE_PROC_STOP	(1<<1)	///<���쏈����~ �X�̓��쏈�����s��Ȃ�
#define FLDOBJSYS_STA_BIT_DRAW_PROC_STOP	(1<<2)	///<�`�揈����~ �X�̕`�揈�����s��Ȃ�
#define FLDOBJSYS_STA_BIT_SHADOW_JOIN_NOT	(1<<3)			///<�e��t���Ȃ�

//--------------------------------------------------------------
//	FIELD_OBJ �X�e�[�^�X�r�b�g
//--------------------------------------------------------------
#define FLDOBJ_STA_BIT_NON					(0)				///<�X�e�[�^�X����
#define FLDOBJ_STA_BIT_USE					(1<<0)			///<�g�p����\��
#define FLDOBJ_STA_BIT_MOVE					(1<<1)			///<�ړ�����\��
#define FLDOBJ_STA_BIT_MOVE_START			(1<<2)			///<�ړ��J�n��\��
#define FLDOBJ_STA_BIT_MOVE_END				(1<<3)			///<�ړ��I����\��
#define FLDOBJ_STA_BIT_ACMD					(1<<4)			///<�A�j���[�V�����R�}���h��
#define FLDOBJ_STA_BIT_ACMD_END				(1<<5)			///<�A�j���[�V�����R�}���h�I��
#define FLDOBJ_STA_BIT_PAUSE_MOVE			(1<<6)			///<�ړ��ꎞ��~
#define FLDOBJ_STA_BIT_PAUSE_DIR			(1<<7)			///<�\�������ꎞ��~
#define FLDOBJ_STA_BIT_PAUSE_ANM			(1<<8)			///<�A�j���ꎞ��~
#define FLDOBJ_STA_BIT_VANISH				(1<<9)			///<��\��
#define FLDOBJ_STA_BIT_ZONE_DEL_NOT			(1<<10)			///<�]�[���؂�ւ��ɂ��폜�֎~
#define FLDOBJ_STA_BIT_ATTR_GET_ERROR		(1<<11)			///<�A�g���r���[�g�擾���s
#define FLDOBJ_STA_BIT_HEIGHT_GET_ERROR		(1<<12)			///<�����擾���s
#define FLDOBJ_STA_BIT_HEIGHT_VANISH_OFF	(1<<13)			///<�����擾�s���̔�\����OFF
#define FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP	(1<<14)			///<�`�揉��������
#define FLDOBJ_STA_BIT_SHADOW_SET			(1<<15)			///<�e�Z�b�g�ς�
#define FLDOBJ_STA_BIT_JUMP_START			(1<<16)			///<�W�����v�J�n
#define FLDOBJ_STA_BIT_JUMP_END				(1<<17)			///<�W�����v�I��
#define FLDOBJ_STA_BIT_FELLOW_HIT_NON		(1<<18)			///<OBJ���m�̓����蔻�薳��
#define FLDOBJ_STA_BIT_TALK_OFF				(1<<19)			///<�b����������
#define FLDOBJ_STA_BIT_SHADOW_VANISH		(1<<20)			///<�e�\���A��\��
#define FLDOBJ_STA_BIT_DRAW_PUSH			(1<<21)			///<�`�揈����ޔ�
#define FLDOBJ_STA_BIT_BLACT_ADD_PRAC		(1<<22)			///<�r���{�[�h�A�N�^�[�ǉ���
#define FLDOBJ_STA_BIT_HEIGHT_GET_OFF		(1<<23)			///<�����擾�����Ȃ�
#define FLDOBJ_STA_BIT_REFLECT_SET			(1<<24)			///<�f�荞�݂��Z�b�g����
#define FLDOBJ_STA_BIT_ALIES				(1<<25)			///<�G�C���A�X�ł���
#define FLDOBJ_STA_BIT_EFFSET_SHOAL			(1<<26)			///<�󐣃G�t�F�N�g���Z�b�g
#define FLDOBJ_STA_BIT_ATTR_OFFS_OFF		(1<<27)			///<�A�g���r���[�g�I�t�Z�b�g�ݒ�OFF
#define FLDOBJ_STA_BIT_BRIDGE				(1<<28)			///<���ړ����ł���
#define FLDOBJ_STA_BIT_HEIGHT_EXPAND		(1<<29)			///<�g�������ɔ�������

//--------------------------------------------------------------
///	FIELD_OBJ ����r�b�g
//--------------------------------------------------------------
#define FLDOBJ_MOVE_BIT_NON					(0)				///<����
#define FLDOBJ_MOVE_BIT_SHADOW_SET			(1<<0)			///<�e���Z�b�g����
#define FLDOBJ_MOVE_BIT_GRASS_SET			(1<<1)			///<�����Z�b�g����

//--------------------------------------------------------------
//	�q�b�g�`�F�b�N�r�b�g
//--------------------------------------------------------------
#define FLDOBJ_MOVE_HIT_BIT_NON		(0)						///<�q�b�g����
#define FLDOBJ_MOVE_HIT_BIT_LIM		(1<<0)					///<�ړ������ɂ��q�b�g
#define FLDOBJ_MOVE_HIT_BIT_ATTR	(1<<1)					///<�A�g���r���[�g�ɂ��q�b�g
#define FLDOBJ_MOVE_HIT_BIT_OBJ		(1<<2)					///<OBJ���m�̏Փ�
#define FLDOBJ_MOVE_HIT_BIT_HEIGHT	(1<<3)					///<���፷�ɂ��q�b�g

//--------------------------------------------------------------
///	�t�B�[���hOBJ�w�b�_�[��������
//--------------------------------------------------------------
typedef enum
{
	FLDOBJ_PARAM_0 = 0,
	FLDOBJ_PARAM_1,
	FLDOBJ_PARAM_2,
}FLDOBJ_H_PARAM;

//--------------------------------------------------------------
///	�`��^�C�v
//--------------------------------------------------------------
typedef enum
{
	FLDOBJ_DRAWTYPE_NON = 0,		///<�`�斳��
	FLDOBJ_DRAWTYPE_BLACT,			///<�r���{�[�h�`��
	FLDOBJ_DRAWTYPE_MDL,			///<���f�����O�`��
}FLDOBJ_DRAWTYPE;

//--------------------------------------------------------------
///	�e���
//--------------------------------------------------------------
typedef enum
{
	FLDOBJ_SHADOW_NON = 0,			///<�e����
	FLDOBJ_SHADOW_ON,				///<�e�A��
}FLDOBJ_SHADOWTYPE;

//--------------------------------------------------------------
///	���Վ��
//--------------------------------------------------------------
typedef enum
{
	FLDOBJ_FOOTMARK_NON = 0,		///<���Ֆ���
	FLDOBJ_FOOTMARK_NORMAL,			///<�Q�{��
	FLDOBJ_FOOTMARK_CYCLE,			///<���]��
}FLDOBJ_FOOTMARKTYPE;

//--------------------------------------------------------------
///	�f�肱�ݎ��
//--------------------------------------------------------------
typedef enum
{
	FLDOBJ_REFLECT_NON = 0,			///<�f�肱�ݖ���
	FLDOBJ_REFLECT_BLACT,			///<�r���{�[�h�f�肱��
}FLDOBJ_REFLECTTYPE;

//--------------------------------------------------------------
///	�t�B�[���hOBJ����v���C�I���e�B�I�t�Z�b�g
//--------------------------------------------------------------
enum
{
	FLDOBJ_TCBPRI_OFFS_ST = 0,		///<��{
	FLDOBJ_TCBPRI_OFFS_PAIR = 1,	///<�y�A����
	FLDOBJ_TCBPRI_OFFS_AFTER,		///<�t�B�[���hOBJ������
};

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
//	�^�Ē�`
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_H						FIELD_OBJ_H;
typedef struct _TAG_FIELD_OBJ_MOVE_PROC_LIST		FIELD_OBJ_MOVE_PROC_LIST;
typedef struct _TAG_FIELD_OBJ_DRAW_PROC_LIST		FIELD_OBJ_DRAW_PROC_LIST;
typedef struct _TAG_FIELD_OBJ_DRAW_PROC_LIST_REG	FIELD_OBJ_DRAW_PROC_LIST_REG;
typedef struct _TAG_FIELD_OBJ_BLACTANM_PUSH			FIELD_OBJ_BLACTANM_PUSH;
typedef struct _TAG_FIELD_OBJ_BLACT_HEADER			FIELD_OBJ_BLACT_HEADER;
typedef struct _TAG_FIELD_OBJ_BLACT_ADD_TBL			FIELD_OBJ_BLACT_ADD_TBL;
typedef struct _TAG_FIELD_OBJ_BLACT_CONT			FIELD_OBJ_BLACT_CONT;
typedef struct _TAG_FIELD_OBJ_RESMH					FIELD_OBJ_RESMH;
typedef struct _TAG_FIELD_OBJ_RESMNARC				FIELD_OBJ_RESMNARC;
typedef struct _TAG_FIELD_OBJ_BLACT_HEADER_ID		FIELD_OBJ_BLACT_HEADER_ID;
typedef struct _TAG_FIELD_OBJ_ACMD_LIST				FIELD_OBJ_ACMD_LIST;

typedef struct _TAG_FIELD_OBJ_RENDER_CONT * FIELD_OBJ_RENDER_CONT_PTR;

//--------------------------------------------------------------
///	FIELD_OBJ_STS_PTR
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_SYS * FIELD_OBJ_SYS_PTR;

//--------------------------------------------------------------
///	const FIELD_OBJ_STS_PTR
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_SYS const * CONST_FIELD_OBJ_SYS_PTR;

//--------------------------------------------------------------
///	FIELD_OBJ_PTR
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ * FIELD_OBJ_PTR;

//--------------------------------------------------------------
///	const FIELD_OBJ_PTR
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ const * CONST_FIELD_OBJ_PTR;

//--------------------------------------------------------------
///	�֐���`
//--------------------------------------------------------------
typedef void (*FIELD_OBJ_MOVE_PROC_INIT)( FIELD_OBJ_PTR );		///<���쏉�����֐�
typedef void (*FIELD_OBJ_MOVE_PROC)( FIELD_OBJ_PTR );			///<����֐�
typedef void (*FIELD_OBJ_MOVE_PROC_DEL)( FIELD_OBJ_PTR );		///<����폜�֐�
typedef void (*FIELD_OBJ_MOVE_PROC_RET)( FIELD_OBJ_PTR );		///<���앜�A�֐�
typedef void (*FIELD_OBJ_DRAW_PROC_INIT)( FIELD_OBJ_PTR );		///<�`�揉�����֐�
typedef void (*FIELD_OBJ_DRAW_PROC)( FIELD_OBJ_PTR );			///<�`��֐�
typedef void (*FIELD_OBJ_DRAW_PROC_DEL)( FIELD_OBJ_PTR );		///<�`��폜�֐�
typedef void (*FIELD_OBJ_DRAW_PROC_PUSH)( FIELD_OBJ_PTR );		///<�`��ޔ��֐�
typedef void (*FIELD_OBJ_DRAW_PROC_POP)( FIELD_OBJ_PTR );		///<�`�敜�A�֐�

//--------------------------------------------------------------
///	FIELD_OBJ_MOVE_PROC_LIST�\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_MOVE_PROC_LIST
{
	int move_code;											///<����R�[�h
	FIELD_OBJ_MOVE_PROC_INIT init_proc;						///<�������֐�
	FIELD_OBJ_MOVE_PROC move_proc;							///<����֐�
	FIELD_OBJ_MOVE_PROC_DEL delete_proc;					///<�폜�֐�
	FIELD_OBJ_MOVE_PROC_RET return_proc;					///<���앜�A�֐�
};
															///FIELD_OBJ_MOVE_PROC_LIST�T�C�Y
#define FIELD_OBJ_MOVE_PROC_LIST_SIZE (sizeof(FIELD_OBJ_MOVE_PROC_LIST))

//--------------------------------------------------------------
///	FIELD_OBJ_DRAW_PROC_LIST�\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_DRAW_PROC_LIST
{
	FIELD_OBJ_DRAW_PROC_INIT init_proc;						///<�������֐�
	FIELD_OBJ_DRAW_PROC draw_proc;							///<�`��֐�
	FIELD_OBJ_DRAW_PROC_DEL delete_proc;					///<�폜�֐�
	FIELD_OBJ_DRAW_PROC_PUSH push_proc;						///<�ޔ��֐�
	FIELD_OBJ_DRAW_PROC_POP pop_proc;						///<���A�֐�
};
															///FIELD_OBJ_DRAW_PROC_LIST�T�C�Y
#define FIELD_OBJ_DRAW_PROC_LIST_SIZE (sizeof(FIELD_OBJ_DRAW_PROC_LIST))

//--------------------------------------------------------------
///	FIELD_OBJ_DRAW_PROC_LIST_CODE_REG �\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_DRAW_PROC_LIST_REG
{
	u32 code;												///<�o�^�R�[�h
	const FIELD_OBJ_DRAW_PROC_LIST *list;					///<�`��֐����X�g
};
														///FIELD_OBJ_DRAW_PROC_LIST_REG�T�C�Y
#define FIELD_OBJ_DRAW_PROC_LIST_REG_SIZE (sizeof(FIELD_OBJ_DRAW_PROC_LIST_REG))

//--------------------------------------------------------------
///	FIELD_OBJ_BLACTANM_PUSH �\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_BLACTANM_PUSH
{
	u32 vanish;												///<�\���A��\��
	u16 anm_set;											///<�A�j���Z�b�g
	u16 anm_offs;											///<�A�j���I�t�Z�b�g
	fx32 frame;												///<�t���[��
};

#define FIELD_OBJ_BLACTANM_PUSH_SIZE (sizeof(FIELD_OBJ_BLACTANM_PUSH))

//--------------------------------------------------------------
///	FIELD_OBJ_BLACT_HEADER �\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_BLACT_HEADER
{
	u32 obj_code;											///<OBJ�R�[�h
	BLACT_HEADER *head;										///<�r���{�[�h�A�N�^�[�w�b�_
};
										///FIELD_OBJ_BLACT_HEADER�T�C�Y
#define FIELD_OBJ_BLACT_HEADER_SIZE (sizeof(FIELD_OBJ_BLACT_HEADER))

//--------------------------------------------------------------
///	BLACTADD_RESERVE_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int code;												///<�\������OBJ�R�[�h
	FIELD_OBJ_PTR	fldobj;									///<�ǉ�����Ώۂ�FIELD_OBJ_PTR
	BLACT_WORK_PTR	*act;									///<�ǉ����ꂽ�r���{�[�h *�i�[��
}BLACTADD_RESERVE;

#define BLACTADD_RESERVE_SIZE (sizeof(BLACTADD_RESERVE))

//--------------------------------------------------------------
///	TEXLOAD_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	u32 arc_id;												///<���[�h����A�[�J�C�uID
	int resm_tex_id;										///<�o�^ID
	REGULAR_GUEST reg_type;									///<�o�^�^�C�v REGULAR? GUEST?
	TEXRES_MANAGER_PTR resm_tex;							///<�o�^RES(�󎯕�
}TEXLOAD_WORK;

#define TEXLOAD_WORK_SIZE (sizeof(TEXLOAD_WORK))

//--------------------------------------------------------------
///	VTEX_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	vu32 trans_end;											///<�]���I���t���O
	int resm_tex_id;										///<�o�^ID
	TEXRES_MANAGER_PTR resm_tex;							///<�o�^RES
}VTEX_WORK;

#define VTEX_WORK_SIZE (sizeof(VTEX_WORK))

//--------------------------------------------------------------
///	BLACT_VTRANS_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	s16 max;												///<�e�����o�[�ő吔
	s16 load_max;											///<���[�h�ő吔
	vs16 load_count;										///<���[�h��
	vu16 access_flag;										///<�A�N�Z�X���t���O
	BLACTADD_RESERVE *blact_reserve_work_tbl;				///<BLACTA
	TEXLOAD_WORK *tex_load_work_tbl;						///<TEXLOAD_WORK *
	VTEX_WORK *vtex_work_tbl;								///<VTEX_WORK *
	FIELD_OBJ_BLACT_CONT *cont;								///<FIELD_OBJ_BLACT_CONT *
	TCB_PTR tcb_load;										///<TCB �f�[�^���[�h
	TCB_PTR tcb_blactadd;									///<TCB �r���{�[�h�ǉ�
	TCB_PTR tcb_vintr;										///<TCB VIntr
	TCB_PTR tcb_vwait;										///<TCB VWait
}BLACT_VTRANS_WORK;

#define BLACT_VTRANS_WORK_SIZE (sizeof(BLACT_VTRANS_WORK))

//--------------------------------------------------------------
///	FIELD_OBJ_BLACT_CONT �\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_BLACT_CONT
{
	int idx;											///<�r���{�[�h�A�N�^�[�C���f�b�N�X
	int max;											///<�r���{�[�h�A�N�^�[�ő吔
	
	int resm_id_reg_max_mdl;							///<���\�[�XID���M�����[�Ǘ������f��
	int resm_id_gst_max_mdl;							///<���\�[�XID�Q�X�g�Ǘ������f��
	int resm_id_reg_max_anm;							///<���\�[�XID���M�����[�Ǘ����A�j��
	int resm_id_gst_max_anm;							///<���\�[�XID�Q�X�g�Ǘ����A�j��
	int resm_id_reg_max_tex;							///<���\�[�XID���M�����[�Ǘ����e�N�X�`��
	int resm_id_gst_max_tex;							///<���\�[�XID �Q�X�g�Ǘ��� �e�N�X�`��
	int resm_id_tbl_mdl[FLDOBJ_RESM_MAX_MDL];			///<���\�[�XID���f���i�[�e�[�u��
	int resm_id_tbl_anm[FLDOBJ_RESM_MAX_ANM];			///<���\�[�XID�A�j���i�[�e�[�u��
	int resm_id_tbl_tex[FLDOBJ_RESM_MAX_TEX];			///<���\�[�XID�e�N�X�`���i�[�e�[�u��
	
//	TCB_PTR tcb_ptr_blact_add;							///<�r���{�[�h�A�N�^�[�ǉ��Ǘ�TCB_PTR
//	TCB_PTR tcb_ptr_vintr;								///<V�u�����N���荞�ݏ���TCB_PTR
	BLACT_SET_PTR blact_setptr;							///<�r���{�[�h�A�N�^�[�Z�b�g�|�C���^
	BLACT_HEADER *blact_head_tbl;						///<�r���{�[�h�A�N�^�[�w�b�_�[�e�[�u��
	RES_MANAGER_PTR	mdl_res_manage;						///<���f�����\�[�X�}�l�[�W���[
	RES_MANAGER_PTR	anm_res_manage;						///<�A�j�����\�[�X�}�l�[�W���[
	TEXRES_MANAGER_PTR	tex_res_manage;					///<�e�N�X�`�����\�[�X�}�l�[�W���[
	FIELD_OBJ_BLACT_HEADER *head_manage;				///<�A�N�^�[�w�b�_�[�Ǘ�
	
	LRES *lres_mdl;										///<���f�����O�p���\�[�X
	LRES *lres_anm;										///<�A�j���p���\�[�X
	
	BLACT_VTRANS_WORK *vtrans_work;						///<BLACT_VTRANS_WORK
	
	CONST_FIELD_OBJ_SYS_PTR fos;						///<FIELD_OBJ_SYS_PTR
};
														//FIELD_OBJ_BLACT_CONT�T�C�Y
#define FIELD_OBJ_BLACT_CONT_SIZE (sizeof(FIELD_OBJ_BLACT_CONT))

//--------------------------------------------------------------
///	FIELD_OBJ_RESMH �\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_RESMH
{
	int id;												///<�o�^����ID
	const char *path;									///<�o�^����f�[�^�ւ̃p�X
};

#define FIELD_OBJ_RESMH_SIZE (sizeof(FIELD_OBJ_RESMH))

//--------------------------------------------------------------
///	FIELD_OBJ_RESMNARC �\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_RESMNARC
{
	int id;
	int narc_id;
};

#define FIELD_OBJ_RESMNARC_SIZE (sizeof(FIELD_OBJ_RESMNARC))

//--------------------------------------------------------------
///	FIELD_OBJ_BLACT_HEADER_ID�\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_BLACT_HEADER_ID
{
	int tex_id;											///<�e�N�X�`��ID
	int mdl_id;											///<���f��ID
	int anm_id;											///<�A�j��ID
//	const char * const head_path;						///<�w�b�_�[�p�X
	const BLACT_ANIME_TBL *anm_tbl;						///<�A�j���e�[�u�� *
};

#define FIELD_OBJ_BLACT_HEADER_ID_SIZE (sizeof(FIELD_OBJ_BLACT_HEADER_ID))

//--------------------------------------------------------------
///	FIELD_OBJ_ACMD_LIST�\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_ACMD_LIST
{
	u16 code;											///<���s����A�j���[�V�����R�}���h�R�[�h
	u16 num;											///<code���s��
};

#define FIELD_OBJ_ACMD_LIST_SIZE (sizeof(FIELD_OBJ_ACMD_LIST))

//--------------------------------------------------------------
//	OBJCODE_SEEDDATA�\����
//--------------------------------------------------------------
typedef struct
{
	u32 code_miki;			///<��OBJCODE
	u32 code_flower;		///<��OBJCODE
	u32 code_fruit;			///<��OBJCODE
}OBJCODE_SEEDDATA;

//--------------------------------------------------------------
///	OBJCODE_STATE�\����
//--------------------------------------------------------------
typedef struct
{
	int code;				///<OBJ�R�[�h
	u32 type_draw:4;		///<FLDOBJ_DRAWTYPE
	u32 type_shadow:2;		///<FLDOBJ_SHADOWTYPE
	u32 type_footmark:4;	///<FLDOBJ_FOOTMARKTYPE
	u32 type_reflect:2;		///<FLDOBJ_REFLECTTYPE;
	u32 dmy:20;				///<bit�]��
}OBJCODE_STATE;

//==============================================================================
//	extern
//==============================================================================
//--------------------------------------------------------------
//	fieldobj.c
//--------------------------------------------------------------
extern FIELD_OBJ_SYS_PTR  FieldOBJSys_Init( FIELDSYS_WORK *fsys, int max, int pri );
extern void FieldOBJSys_DrawInit( FIELD_OBJ_SYS_PTR fos,
		int tex_max, int reg_tex_max, const int *tex_tbl );
extern void FieldOBJSys_Delete( FIELD_OBJ_SYS_PTR sys );
extern void FieldOBJSys_DrawDelete( FIELD_OBJ_SYS_PTR fos );
extern void FieldOBJSys_DeleteAll( FIELD_OBJ_SYS_PTR sys );

extern FIELD_OBJ_PTR  FieldOBJ_AddH(
		CONST_FIELD_OBJ_SYS_PTR sys, const FIELD_OBJ_H *head, int zone_id );
extern FIELD_OBJ_PTR  FieldOBJ_AddHMake(
		CONST_FIELD_OBJ_SYS_PTR sys, int x, int z, int dir, int obj, int move, int zone_id );
extern FIELD_OBJ_PTR FieldOBJ_AddHEvent(
		CONST_FIELD_OBJ_SYS_PTR fos, int id, int max, int zone, const FIELD_OBJ_H *head );
extern void FieldOBJ_DrawResetAlone( FIELD_OBJ_PTR fldobj, int code );
extern void FieldOBJ_DrawReset( FIELD_OBJ_PTR fldobj, int code );
extern void FieldOBJ_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DeleteEvent( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawDelete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DeleteAll( FIELD_OBJ_SYS_PTR sys );
extern void FieldOBJ_PushAll( FIELD_OBJ_SYS_PTR sys );
extern void FieldOBJ_DrawProcPushAll( FIELD_OBJ_SYS_PTR fos );
extern void FieldOBJ_PopAll( FIELD_OBJ_SYS_PTR sys );
extern void FieldOBJ_DrawProcPopAll( FIELD_OBJ_SYS_PTR fos );

extern void FieldOBJSys_DataSaveAll(
		FIELDSYS_WORK *fsys, CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_SAVE_DATA_PTR save, int max );
extern void FieldOBJSys_DataLoadAll(
		CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_SAVE_DATA_PTR save, int max );

//extern void FieldOBJ_AddFile( CONST_FIELD_OBJ_SYS_PTR sys, int zone, const char *name );
extern void FieldOBJ_AddBin(
		CONST_FIELD_OBJ_SYS_PTR sys, int zone, int max, const FIELD_OBJ_H *bin );

extern FIELD_OBJ_PTR FieldOBJSys_OBJIDSearch( CONST_FIELD_OBJ_SYS_PTR fos, int id );
extern FIELD_OBJ_PTR FieldOBJSys_MoveCodeSearch( CONST_FIELD_OBJ_SYS_PTR fos, int mv_code );
extern int FieldOBJSys_FieldOBJSearch(
	CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_PTR *fldobj, int *no, u32 check_bit );
extern int FieldOBJ_OBJCodeUseSearch( CONST_FIELD_OBJ_PTR fldobj, int code );
extern int FieldOBJ_EventIDAliesCheck( CONST_FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_TCBPriGet( CONST_FIELD_OBJ_PTR fldobj, int offset );
extern int FieldOBJ_CheckSameID( CONST_FIELD_OBJ_PTR fldobj, int obj_id, int zone_id );
extern int FieldOBJ_CheckSameIDOBJCodeIn(
		CONST_FIELD_OBJ_PTR fldobj, int code, int obj_id, int zone_id );

extern void FieldOBJSys_ZoneUpdateDelete(
		FIELD_OBJ_SYS_PTR fos, int old_zone, int new_zone, int max, const FIELD_OBJ_H *head );

extern FIELD_OBJ_PTR FieldOBJSys_OBJIDMoveCodeSearch(
		CONST_FIELD_OBJ_SYS_PTR fos, int obj_id, int mv_code );

extern void FieldOBJSys_OBJMaxSet( FIELD_OBJ_SYS_PTR sys, int max );
extern int FieldOBJSys_OBJMaxGet( CONST_FIELD_OBJ_SYS_PTR sys );
extern int FieldOBJSys_OBJCountGet( CONST_FIELD_OBJ_SYS_PTR sys );
extern void FieldOBJSys_StatusBit_Init( FIELD_OBJ_SYS_PTR sys, u32 bit );
extern void FieldOBJSys_StatusBit_ON( FIELD_OBJ_SYS_PTR sys, u32 bit );
extern void FieldOBJSys_StatusBit_OFF( FIELD_OBJ_SYS_PTR sys, u32 bit );
extern u32 FieldOBJSys_StatusBit_Check( CONST_FIELD_OBJ_SYS_PTR sys, u32 bit );
extern void FieldOBJSys_TCBStandardPrioritySet( FIELD_OBJ_SYS_PTR sys, int pri );
extern int FieldOBJSys_TCBStandardPriorityGet( CONST_FIELD_OBJ_SYS_PTR sys );
extern FIELD_OBJ_BLACT_CONT * FieldOBJSys_BlActContGet( CONST_FIELD_OBJ_SYS_PTR sys );
extern void FieldOBJSys_RenderContSet( FIELD_OBJ_SYS_PTR sys, FIELD_OBJ_RENDER_CONT_PTR render);
extern FIELD_OBJ_RENDER_CONT_PTR FieldOBJSys_RenderContGet( CONST_FIELD_OBJ_SYS_PTR sys );
extern void FieldOBJSys_FieldOBJWorkSet( FIELD_OBJ_SYS_PTR sys, FIELD_OBJ_PTR ptr );
extern CONST_FIELD_OBJ_PTR  FieldOBJSys_FieldOBJWorkGet( CONST_FIELD_OBJ_SYS_PTR sys );
extern FIELD_OBJ_PTR  FieldOBJSys_FldOBJWorkGet( CONST_FIELD_OBJ_SYS_PTR sys );
extern void FieldOBJSys_FieldOBJWorkInc( CONST_FIELD_OBJ_PTR *fldobj );
extern void FieldOBJSys_FldOBJWorkInc( FIELD_OBJ_PTR *fldobj );
extern void FieldOBJSys_FieldSysWorkSet( FIELD_OBJ_SYS_PTR fos, FIELDSYS_WORK *fsys );
extern FIELDSYS_WORK * FieldOBJSys_FieldSysWorkGet( CONST_FIELD_OBJ_SYS_PTR fos );
extern void FieldOBJSys_ArcHandleSet( FIELD_OBJ_SYS_PTR fos, ARCHANDLE *handle );
extern ARCHANDLE * FieldOBJSys_ArcHandleGet( CONST_FIELD_OBJ_SYS_PTR fos );

extern void FieldOBJ_StatusBit_Init( FIELD_OBJ_PTR fldobj, u32 bit );
extern u32 FieldOBJ_StatusBit_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBit_ON( FIELD_OBJ_PTR fldobj, u32 bit );
extern void FieldOBJ_StatusBit_OFF( FIELD_OBJ_PTR fldobj, u32 bit );
extern u32 FieldOBJ_StatusBit_Check( CONST_FIELD_OBJ_PTR fldobj, u32 bit );
extern u32 FieldOBJ_StatusBit_CheckEasy( CONST_FIELD_OBJ_PTR fldobj, u32 bit );
extern void FieldOBJ_MoveBit_Init( FIELD_OBJ_PTR fldobj, u32 bit );
extern u32 FieldOBJ_MoveBit_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveBit_ON( FIELD_OBJ_PTR fldobj, u32 bit );
extern void FieldOBJ_MoveBit_OFF( FIELD_OBJ_PTR fldobj, u32 bit );
extern u32 FieldOBJ_MoveBit_Check( CONST_FIELD_OBJ_PTR fldobj, u32 bit );
extern void FieldOBJ_OBJIDSet( FIELD_OBJ_PTR fldobj, u32 obj_id );
extern u32 FieldOBJ_OBJIDGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_ZoneIDSet( FIELD_OBJ_PTR fldobj, int zone_id );
extern int FieldOBJ_ZoneIDGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_OBJCodeSet( FIELD_OBJ_PTR fldobj, u32 code );
extern u32 FieldOBJ_OBJCodeGet( CONST_FIELD_OBJ_PTR fldobj );
extern u32 FieldOBJ_OBJCodeGetSeedIn( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveCodeSet( FIELD_OBJ_PTR fldobj, u32 code );
extern u32 FieldOBJ_MoveCodeGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_EventTypeSet( FIELD_OBJ_PTR fldobj, u32 type );
extern u32 FieldOBJ_EventTypeGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_EventFlagSet( FIELD_OBJ_PTR fldobj, u32 type );
extern u32 FieldOBJ_EventFlagGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_EventIDSet( FIELD_OBJ_PTR fldobj, u32 id );
extern u32 FieldOBJ_EventIDGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DirHeaderSet( FIELD_OBJ_PTR fldobj, int dir );
extern u32 FieldOBJ_DirHeaderGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DirDispSetForce( FIELD_OBJ_PTR fldobj, int dir );
extern void FieldOBJ_DirDispCheckSet( FIELD_OBJ_PTR fldobj, int dir );
extern int FieldOBJ_DirDispGet( CONST_FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_DirDispOldGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DirMoveSet( FIELD_OBJ_PTR fldobj, int dir );
extern int FieldOBJ_DirMoveGet( CONST_FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_DirMoveOldGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DirMoveDispCheckSet( FIELD_OBJ_PTR fldobj, int dir );
extern void FieldOBJ_ParamSet( FIELD_OBJ_PTR fldobj, int param, FLDOBJ_H_PARAM no );
extern int FieldOBJ_ParamGet( CONST_FIELD_OBJ_PTR fldobj, FLDOBJ_H_PARAM param );
extern void FieldOBJ_MoveLimitXSet( FIELD_OBJ_PTR fldobj, int x );
extern int FieldOBJ_MoveLimitXGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveLimitZSet( FIELD_OBJ_PTR fldobj, int z );
extern int FieldOBJ_MoveLimitZGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawStatusSet( FIELD_OBJ_PTR fldobj, u32 st );
extern u32 FieldOBJ_DrawStatusGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveTcbPtrSet( FIELD_OBJ_PTR fldobj, TCB_PTR tcb );
extern TCB_PTR FieldOBJ_MoveTcbPtrGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveTcbDelete( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_FieldOBJSysSet( FIELD_OBJ_PTR fldobj, CONST_FIELD_OBJ_SYS_PTR sys );
extern CONST_FIELD_OBJ_SYS_PTR  FieldOBJ_FieldOBJSysGet( CONST_FIELD_OBJ_PTR fldobj );
extern void * FieldOBJ_MoveProcWorkInit( FIELD_OBJ_PTR fldobj, int size );
extern void * FieldOBJ_MoveProcWorkGet( FIELD_OBJ_PTR fldobj );
extern void * FieldOBJ_MoveSubProcWorkInit( FIELD_OBJ_PTR fldobj, int size );
extern void * FieldOBJ_MoveSubProcWorkGet( FIELD_OBJ_PTR fldobj );
extern void * FieldOBJ_MoveCmdWorkInit( FIELD_OBJ_PTR fldobj, int size );
extern void * FieldOBJ_MoveCmdWorkGet( FIELD_OBJ_PTR fldobj );
extern void * FieldOBJ_DrawProcWorkInit( FIELD_OBJ_PTR fldobj, int size );
extern void * FieldOBJ_DrawProcWorkGet( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveInitProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC_INIT init );
extern void FieldOBJ_MoveInitProcCall( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC move );
extern void FieldOBJ_MoveProcCall( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDeleteProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC_DEL del );
extern void FieldOBJ_MoveDeleteProcCall( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveReturnProcCall( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawInitProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_INIT init );
extern void FieldOBJ_DrawInitProcCall( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC draw );
extern void FieldOBJ_DrawProcCall( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawDeleteProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_DEL del );
extern void FieldOBJ_DrawDeleteProcCall( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawPushProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_PUSH push );
extern void FieldOBJ_DrawPushProcCall( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawPopProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_POP pop );
extern void FieldOBJ_DrawPopProcCall( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_AcmdCodeSet( FIELD_OBJ_PTR fldobj, int code );
extern int FieldOBJ_AcmdCodeGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_AcmdSeqSet( FIELD_OBJ_PTR fldobj, int no );
extern void FieldOBJ_AcmdSeqInc( FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_AcmdSeqGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_NowMapAttrSet( FIELD_OBJ_PTR fldobj, u32 attr );
extern u32 FieldOBJ_NowMapAttrGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_OldMapAttrSet( FIELD_OBJ_PTR fldobj, u32 attr );
extern u32 FieldOBJ_OldMapAttrGet( CONST_FIELD_OBJ_PTR fldobj );
extern FIELDSYS_WORK * FieldOBJ_FieldSysWorkGet( CONST_FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_TCBStandardPriorityGet( CONST_FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_ZoneIDGetAlies( CONST_FIELD_OBJ_PTR fldobj );

#if 0
extern void FieldOBJSys_StatusBitON_PauseAll( FIELD_OBJ_SYS_PTR fos );
extern void FieldOBJSys_StatusBitOFF_PauseAll( FIELD_OBJ_SYS_PTR fos );
#else
extern void FieldOBJSys_MoveStopAll( FIELD_OBJ_SYS_PTR fos );
extern void FieldOBJSys_MoveStopAllClear( FIELD_OBJ_SYS_PTR fos );
extern void FieldOBJSys_MovePauseAll( FIELD_OBJ_SYS_PTR fos );
extern void FieldOBJSys_MovePauseAllClear( FIELD_OBJ_SYS_PTR fos );
#endif
extern int FieldOBJSys_DrawInitCompCheck( CONST_FIELD_OBJ_SYS_PTR fos );
extern u32 FieldOBJ_FieldOBJSysStatusBitCheck( CONST_FIELD_OBJ_PTR fldobj, u32 bit );
extern void FieldOBJSys_ShadowJoinSet( FIELD_OBJ_SYS_PTR fos, int flag );
extern int FieldOBJSys_ShadowJoinCheck( CONST_FIELD_OBJ_SYS_PTR fos );

extern int FieldOBJ_StatusBitCheck_Use( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitON_Move( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitOFF_Move( FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_StatusBitCheck_Move( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitON_MoveStart( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitOFF_MoveStart( FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_StatusBitCheck_MoveStart( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitON_MoveEnd( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitOFF_MoveEnd( FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_StatusBitCheck_MoveEnd( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitON_DrawProcInitComp( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitOFF_DrawProcInitComp( FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_StatusBitCheck_DrawProcInitComp( CONST_FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_StatusBitCheck_Vanish( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitSet_Vanish( FIELD_OBJ_PTR fldobj, int flag );
extern void FieldOBJ_StatusBitSet_FellowHit( FIELD_OBJ_PTR fldobj, int flag );
extern void FieldOBJ_StatusBitSet_Move( FIELD_OBJ_PTR fldobj, int flag );
extern int FieldOBJ_StatusBitCheck_Talk( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitSet_TalkOFF( FIELD_OBJ_PTR fldobj, int flag );
extern void FieldOBJ_MovePause( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MovePauseClear( FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_MovePauseCheck( CONST_FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_StatusBit_DrawInitCompCheck( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitSet_HeightGetOFF( FIELD_OBJ_PTR fldobj, int flag );
extern int FieldOBJ_HeightOFFCheck( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_NotZoneDeleteSet( FIELD_OBJ_PTR fldobj, int flag );
extern void FieldOBJ_StatusBitSet_Alies( FIELD_OBJ_PTR fldobj, int flag );
extern int FieldOBJ_StatusBitCheck_Alies( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitSet_ShoalEffectSet( FIELD_OBJ_PTR fldobj, int flag );
extern int FieldOBJ_StatusBitCheck_ShoalEffectSet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitSet_AttrOffsOFF( FIELD_OBJ_PTR fldobj, int flag );
extern int FieldOBJ_StatusBitCheck_AttrOffsOFF( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitSet_Bridge( FIELD_OBJ_PTR fldobj, int flag );
extern int FieldOBJ_StatusBitCheck_Bridge( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitSet_Reflect( FIELD_OBJ_PTR fldobj, int flag );
extern int FieldOBJ_StatusBitCheck_Reflect( CONST_FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_StatusBitCheck_Acmd( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_StatusBitSet_HeightExpand( FIELD_OBJ_PTR fldobj, int flag );
extern int FieldOBJ_StatusBitCheck_HeightExpand( CONST_FIELD_OBJ_PTR fldobj );

extern int FieldOBJ_InitPosGX_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_InitPosGX_Set( FIELD_OBJ_PTR fldobj, int x );
extern int FieldOBJ_InitPosGY_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_InitPosGY_Set( FIELD_OBJ_PTR fldobj, int y );
extern int FieldOBJ_InitPosGZ_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_InitPosGZ_Set( FIELD_OBJ_PTR fldobj, int z );
extern int FieldOBJ_OldPosGX_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_OldPosGX_Set( FIELD_OBJ_PTR fldobj, int x );
extern int FieldOBJ_OldPosGY_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_OldPosGY_Set( FIELD_OBJ_PTR fldobj, int y );
extern int FieldOBJ_OldPosGZ_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_OldPosGZ_Set( FIELD_OBJ_PTR fldobj, int z );
extern int FieldOBJ_NowPosGX_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_NowPosGX_Set( FIELD_OBJ_PTR fldobj, int x );
extern void FieldOBJ_NowPosGX_Add( FIELD_OBJ_PTR fldobj, int x );
extern int FieldOBJ_NowPosGY_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_NowPosGY_Set( FIELD_OBJ_PTR fldobj, int y );
extern void FieldOBJ_NowPosGY_Add( FIELD_OBJ_PTR fldobj, int y );
extern int FieldOBJ_NowPosGZ_Get( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_NowPosGZ_Set( FIELD_OBJ_PTR fldobj, int z );
extern void FieldOBJ_NowPosGZ_Add( FIELD_OBJ_PTR fldobj, int z );
extern void FieldOBJ_VecPosGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec );
extern void FieldOBJ_VecPosSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec );
extern const VecFx32 * FieldOBJ_VecPosPtrGet( CONST_FIELD_OBJ_PTR fldobj );
extern fx32 FieldOBJ_VecPosYGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_VecDrawOffsGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec );
extern void FieldOBJ_VecDrawOffsSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec );
extern VecFx32 * FieldOBJ_VecDrawOffsPtrGet( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_VecDrawOffsOutSideGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec );
extern void FieldOBJ_VecDrawOffsOutSideSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec );
extern void FieldOBJ_VecAttrOffsGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec );
extern void FieldOBJ_VecAttrOffsSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec );
extern int FieldOBJ_HeightGridGet( CONST_FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_H_IDSet( FIELD_OBJ_H *head, int id );
extern int FieldOBJ_H_IDGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_OBJCodeSet( FIELD_OBJ_H *head, int code );
extern int FieldOBJ_H_OBJCodeGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_MoveCodeSet( FIELD_OBJ_H *head, int code );
extern int FieldOBJ_H_MoveCodeGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_EventTypeSet( FIELD_OBJ_H *head, int type );
extern int FieldOBJ_H_EventTypeGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_EventFlagSet( FIELD_OBJ_H *head, int flag );
extern int FieldOBJ_H_EventFlagGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_EventIDSet( FIELD_OBJ_H *head, int id );
extern int FieldOBJ_H_EventIDGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_DirSet( FIELD_OBJ_H *head, int dir );
extern int FieldOBJ_H_DirGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_ParamSet( FIELD_OBJ_H *head, int param, FLDOBJ_H_PARAM no );
extern int FieldOBJ_H_ParamGet( const FIELD_OBJ_H *head, FLDOBJ_H_PARAM no );
extern void FieldOBJ_H_MoveLimitXSet( FIELD_OBJ_H *head, int x );
extern int FieldOBJ_H_MoveLimitXGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_MoveLimitZSet( FIELD_OBJ_H *head, int z );
extern int FieldOBJ_H_MoveLimitZGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_PosXSet( FIELD_OBJ_H *head, int x );
extern int FieldOBJ_H_PosXGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_PosYSet( FIELD_OBJ_H *head, int y );
extern int FieldOBJ_H_PosYGet( const FIELD_OBJ_H *head );
extern void FieldOBJ_H_PosZSet( FIELD_OBJ_H *head, int z );
extern int FieldOBJ_H_PosZGet( const FIELD_OBJ_H *head );

extern FIELD_OBJ_PTR FieldOBJ_SearchGPos( CONST_FIELD_OBJ_SYS_PTR sys, int x, int z );
extern void FieldOBJ_VecPosDirInit( FIELD_OBJ_PTR fldobj, const VecFx32 *vec, int dir );
extern void FieldOBJ_GPosDirInit( FIELD_OBJ_PTR fldobj, int x, int y, int z, int dir );
extern void FieldOBJ_MoveCodeChange( FIELD_OBJ_PTR fldobj, u32 code );
extern void FieldOBJ_OBJIDChange( FIELD_OBJ_PTR fldobj, int id );

extern void FieldOBJ_MoveInitProcDummy( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveProcDummy( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDeleteProcDummy( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveReturnProcDummy( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawInitProcDummy( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawProcDummy( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawDeleteProcDummy( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawPushProcDummy( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawPopProcDummy( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
//	fieldobj_movedata.c
//--------------------------------------------------------------
extern const FIELD_OBJ_MOVE_PROC_LIST * const DATA_FieldOBJMoveProcListTbl[];
extern int (* const * const DATA_AcmdActionTbl[ACMD_MAX])( FIELD_OBJ_PTR  );
const int * const DATA_AcmdCodeDirChangeTbl[];

//--------------------------------------------------------------
//	fieldobj_drawdata.c
//--------------------------------------------------------------
extern const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_Non;

extern const FIELD_OBJ_DRAW_PROC_LIST_REG DATA_FieldOBJDrawProcListRegTbl[];

extern const FIELD_OBJ_RESMNARC DATA_FieldOBJ_ResmNArcTbl_RenderOBJ[];
extern const int DATA_FIELDOBJ_RenderOBJMax;

extern const FIELD_OBJ_RESMNARC DATA_FieldOBJ_ResmNArcTbl_Tex[];
extern const FIELD_OBJ_RESMNARC DATA_FieldOBJ_ResmNArcTbl_Mdl[];
extern const FIELD_OBJ_RESMNARC DATA_FieldOBJ_ResmNArcTbl_Anm[];
extern const int DATA_FieldOBJ_Regular_Tex[];
extern const int DATA_FieldOBJ_Regular_Mdl[];
extern const int DATA_FieldOBJ_Regular_Anm[];
extern const FIELD_OBJ_BLACT_HEADER_ID DATA_FieldOBJ_BlActHeaderPathIDTbl[];

extern const OBJCODE_STATE DATA_FieldOBJCodeDrawStateTbl[];

extern const OBJCODE_SEEDDATA DATA_OBJCodeSeedDataTbl[];

//--------------------------------------------------------------
//	fieldobj_blact.c
//--------------------------------------------------------------
extern void FieldOBJ_BlActCont_Init( FIELD_OBJ_BLACT_CONT *cont,
		CONST_FIELD_OBJ_SYS_PTR fos, 
		int max, int pri,
		int tex_max, int reg_tex_max, const int *rg_tex_tbl );
extern void FieldOBJ_BlActCont_Delete( FIELD_OBJ_BLACT_CONT *cont );

extern TEXREG_TYPE FieldOBJ_BlActAddRegularGuestCode(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act, int code );
extern TEXREG_TYPE FieldOBJ_BlActAddRegularGuest( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act );
extern BLACT_WORK_PTR FieldOBJ_BlActAddCode( FIELD_OBJ_PTR fldobj, int code );
extern void FieldOBJ_BlActDeleteCode(
		CONST_FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act, int code );
extern void FieldOBJ_BlActDelete( CONST_FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act );
extern void FieldOBJ_BlActDeleteCodeCancel( CONST_FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act, int code );
extern void FieldOBJ_BlActAnmPush( BLACT_WORK_PTR act, FIELD_OBJ_BLACTANM_PUSH *push );
extern void FieldOBJ_BlActAnmPop( BLACT_WORK_PTR act, FIELD_OBJ_BLACTANM_PUSH *push );

extern int FieldOBJ_BlActHeaderGetOBJCode( CONST_FIELD_OBJ_SYS_PTR fos,
		u32 code, BLACT_HEADER *head );

extern void FieldOBJ_BlActAdd_Guest( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act, int code );
extern void FieldOBJ_BlActResmRegularAdd_Tex( CONST_FIELD_OBJ_SYS_PTR fos, int id );
extern void FieldOBJ_BlActResmRegularDelete_Tex( CONST_FIELD_OBJ_SYS_PTR fos, int id );
extern void FieldOBJ_BlActResm_MdlIDCheckDelete_Guest( CONST_FIELD_OBJ_SYS_PTR fos, int id );
extern int FieldOBJ_BlActResManage_MdlIDRegistCheck( CONST_FIELD_OBJ_SYS_PTR fos, int id );
extern void FieldOBJ_BlActCont_ResmGuestDeleteAll(
		FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_BLACT_CONT *cont );
extern int FieldOBJ_BlActCont_FldOBJSearch_OBJCode(
	FIELD_OBJ_SYS_PTR fos, int code, CONST_FIELD_OBJ_PTR ignore_obj );
extern int FieldOBJ_BlActCont_FldOBJSearch_MdlID(
	CONST_FIELD_OBJ_SYS_PTR fos, int mdl_id, CONST_FIELD_OBJ_PTR ignore_obj );
extern int FieldOBJ_BlActCont_FldOBJSearch_AnmID(
	FIELD_OBJ_SYS_PTR fos, int anm_id, CONST_FIELD_OBJ_PTR ignore_obj );
extern void FieldOBJ_BlActResmRegularAdd_Anm( CONST_FIELD_OBJ_SYS_PTR fos, int id );
extern void FieldOBJ_BlActResmRegularDelete_Anm( CONST_FIELD_OBJ_SYS_PTR fos, int id );
extern void FieldOBJ_BlActResm_ResIDGuestUseCheckDelete(
		CONST_FIELD_OBJ_SYS_PTR fos, int code, FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_BlActCont_SetPtrSet( FIELD_OBJ_BLACT_CONT *cont, BLACT_SET_PTR set );
extern BLACT_SET_PTR FieldOBJ_BlActCont_SetPtrGet( FIELD_OBJ_BLACT_CONT *cont );
extern void FieldOBJ_BlActCont_MaxSet( FIELD_OBJ_BLACT_CONT *cont, int max );
extern int FieldOBJ_BlActCont_MaxGet( const FIELD_OBJ_BLACT_CONT *cont );
extern void FieldOBJ_BlActCont_MdlResManageSet(
		FIELD_OBJ_BLACT_CONT *cont, RES_MANAGER_PTR mdl );
extern RES_MANAGER_PTR FieldOBJ_BlActCont_MdlResManageGet( const FIELD_OBJ_BLACT_CONT *cont );
extern void FieldOBJ_BlActCont_AnmResManageSet(
		FIELD_OBJ_BLACT_CONT *cont, RES_MANAGER_PTR anm );
extern RES_MANAGER_PTR FieldOBJ_BlActCont_AnmResManageGet( const FIELD_OBJ_BLACT_CONT *cont );
extern void FieldOBJ_BlActCont_TexResManageSet(
		FIELD_OBJ_BLACT_CONT *cont, TEXRES_MANAGER_PTR tex );
extern TEXRES_MANAGER_PTR FieldOBJ_BlActCont_TexResManageGet(
		const FIELD_OBJ_BLACT_CONT *cont );

extern int FieldOBJ_BlActOBJCodeMdlIDGet( int code );
extern int FieldOBJ_BlActOBJCodeAnmIDGet( int code );

#if 0
BLACT_WORK_PTR FieldOBJ_MakeBlActAdd(
		u32 code, const VecFx32 *vec, BLACT_SET_PTR set, BLACT_HEADER *head );
#endif

extern void FieldOBJ_BlActAddPracFlagSet( FIELD_OBJ_PTR fldobj, int flag );
extern int FieldOBJ_BlActAddPracFlagCheck( FIELD_OBJ_PTR fldobj );

extern BOOL FieldOBJ_BlActPosSet( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act );
extern void FieldOBJ_BlActFlagVanishSet( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act );

extern int FieldOBJ_BlActAnmOffsNo_DirWalkGet( int dir );
extern int FieldOBJ_BlActAnmOffsNo_DirDashGet( int dir );
extern int FieldOBJ_BlActAnmOffsNo_DirTakeOFFGet( int dir );

extern void FieldOBJ_BlActDummyDrawReset( FIELD_OBJ_PTR fldobj, int code );

//--------------------------------------------------------------
//	fieldobj_move.c
//--------------------------------------------------------------
extern void FieldOBJ_MoveInit( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_Move( FIELD_OBJ_PTR fldobj );

extern u32 FieldOBJ_PosHitCheck( CONST_FIELD_OBJ_SYS_PTR fos, int x, int z );
extern u32 FieldOBJ_MoveHitCheck(
		CONST_FIELD_OBJ_PTR fldobj, const VecFx32 *vec, int x, int y, int z, int dir );
extern u32 FieldOBJ_MoveHitCheckNow( CONST_FIELD_OBJ_PTR fldobj, int x, int y, int z, int dir );
extern u32 FieldOBJ_MoveHitCheckDir( CONST_FIELD_OBJ_PTR fldobj, int dir );
extern int FieldOBJ_MoveHitCheckFellow( CONST_FIELD_OBJ_PTR fldobj, int x, int y, int z );
extern int FieldOBJ_MoveHitCheckLimit( CONST_FIELD_OBJ_PTR fldobj, int x, int y, int z );
extern int FieldOBJ_MoveHitCheckAttr( CONST_FIELD_OBJ_PTR fldobj, int x, int z, int dir );
extern int FieldOBJ_MapAttrKindCheck_Water( FIELD_OBJ_PTR fldobj, u32 attr );
extern int FieldOBJ_MapAttrKindCheck_Sand( FIELD_OBJ_PTR fldobj, u32 attr );
extern int FieldOBJ_MapAttrKindCheck_Snow( FIELD_OBJ_PTR fldobj, u32 attr );
extern int FieldOBJ_MapAttrKindCheck_MostShallowSnow( FIELD_OBJ_PTR fldobj, u32 attr );
extern int FieldOBJ_MapAttrKindCheck_Bridge( FIELD_OBJ_PTR fldobj, u32 attr );
extern int FieldOBJ_MapAttrKindCheck_BridgeV( FIELD_OBJ_PTR fldobj, u32 attr );
extern int FieldOBJ_MapAttrKindCheck_BridgeH( FIELD_OBJ_PTR fldobj, u32 attr );

extern int FieldOBJ_DirAddValueGX( int dir );
extern int FieldOBJ_DirAddValueGZ( int dir );

extern void FieldOBJ_NowGPosDirAdd( FIELD_OBJ_PTR fldobj, int dir );
extern void FieldOBJ_GPosUpdate( FIELD_OBJ_PTR fldobj );
extern u32 FieldOBJ_NextDirAttrGet( FIELD_OBJ_PTR fldobj, int dir );

extern void FieldOBJ_VecPosAdd( FIELD_OBJ_PTR fldobj, const VecFx32 *val );
extern void FieldOBJ_VecPosDirAdd( FIELD_OBJ_PTR fldobj, int dir, fx32 val );
extern int FieldOBJ_VecPosNowHeightGetSet( FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_NowPosMapAttrSet( FIELD_OBJ_PTR fldobj );
extern void FieldOBJTool_VecPosDirAdd( int dir, VecFx32 *vec, fx32 val );
extern void FieldOBJTool_GridCenterPosGet( int gx, int gz, VecFx32 *vec );
extern void FieldOBJTool_VectorGridPosGet( int *gx, int *gy, int *gz, const VecFx32 *vec );

extern int FieldOBJTool_DirFlip( int dir );
extern int FieldOBJTool_DirRange( int ax, int az, int bx, int bz );
extern int FieldOBJTool_GetHeight( FIELDSYS_WORK *fsys, VecFx32 *vec );
extern int FieldOBJTool_GetHeightExpand( FIELDSYS_WORK *fsys, VecFx32 *vec, int eflag );

//--------------------------------------------------------------
//	fieldobj_move_0.c
//--------------------------------------------------------------
extern void FieldOBJ_MoveDirRnd_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRndUL_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRndUR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRndDL_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRndDR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRndUDL_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRndUDR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRndULR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRndDLR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRndUD_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRndLR_Init( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveDirRnd_Move( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDirRnd_Delete( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveRnd_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRndV_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRndH_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRndRect_Init( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MvRnd_Move( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveDir_Move( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveUp_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveDown_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveLeft_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRight_Init( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveSpin_Move( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveSpinLeft_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveSpinRight_Init( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveRewar_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRewar_Move( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveRoute2_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRoute2_Move( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveRouteURLD_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteRLDU_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteDURL_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteLDUR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteULRD_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteLRDU_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteDULR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteRDUL_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteLUDR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteUDRL_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteRLUD_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteDRLU_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteRUDL_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteUDLR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteLRUD_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteDLRU_Init( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveRouteUL_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteDR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteLD_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteRU_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteUR_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteDL_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteLU_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveRouteRD_Init( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveRoute3_Move( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
//	fieldobj_move_1.c
//--------------------------------------------------------------
extern void FieldOBJ_MoveSubProcInit( FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_MoveSub( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
//	fieldobj_move_2.c
//--------------------------------------------------------------
extern void FieldOBJ_MovePair_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MovePair_Move( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MovePair_Delete( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MovePairTr_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MovePairTr_Move( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MovePairTr_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MovePairTr_Return( FIELD_OBJ_PTR fldobj );
extern FIELD_OBJ_PTR FieldOBJ_MovePairSearch( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveHideSnow_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveHideSand_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveHideGround_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveHideKusa_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveHide_Move( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveHide_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveHide_Return( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveHideEoaPtrSet( FIELD_OBJ_PTR fldobj, EOA_PTR eoa );
extern EOA_PTR FieldOBJ_MoveHideEoaPtrGet( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveHidePullOffFlagSet( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
//	fieldobj_draw.c
//--------------------------------------------------------------
extern void FieldOBJ_Draw( FIELD_OBJ_PTR fldobj );

extern const OBJCODE_STATE * FieldOBJ_OBJCodeDrawStateGet( CONST_FIELD_OBJ_PTR fldobj );

extern int FieldOBJ_DrawPauseCheck( CONST_FIELD_OBJ_PTR fldobj );
extern void * FieldOBJ_DrawArcDataAlloc( CONST_FIELD_OBJ_SYS_PTR fos, u32 datID, int fb );
extern void FieldOBJ_DrawVecPosTotalGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec );
extern void FieldOBJ_DirDispDrawSet( FIELD_OBJ_PTR fldobj, int dir );

extern void FieldOBJ_DrawNon_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawNon_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawNon_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawNon_Push( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawNon_Pop( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
///	fieldobj_draw_0.c
//--------------------------------------------------------------
extern BLACT_WORK_PTR FieldOBJ_DrawBlAct00_BlActPtrGet( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_DrawBlAct00_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlAct00_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlAct00AnmNon_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlAct00AnmOneP_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlAct00_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlAct00_Push( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlAct00_Pop( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_DrawBlActPcWoman_Draw( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_DrawBlActKoiking_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActKoiking_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActKoiking_Push( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActKoiking_Pop( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActKoiking_Draw( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_DrawBlActBird_Draw( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_DrawBlActHero_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActHero_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActHeroAnmNon_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActHero_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActHero_Push( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActHero_Pop( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_DrawBlActHeroCycle_Draw( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_DrawBlActHeroSwim_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActHeroSp_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActHeroWater_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActHeroFishing_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActHeroPoketch_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawBlActHeroBanzai_Draw( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_DrawModel00_Board_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawModel00_SnowBall_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawModel00_Book_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawModel00_Door2_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawModel00_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawModel00_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawModel00_Push( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawModel00_Board_Pop( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawModel00_SnowBall_Pop( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawModel00_Book_Pop( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawModel00_Door2_Pop( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_DrawSnowBallBreakSet( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
///	fieldobj_draw_legendpoke.c
//--------------------------------------------------------------
extern void FieldOBJ_DrawLegend_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawLegend_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawLegend_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawLegend_Push( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawLegend_Pop( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawReiAiHai_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawReiAiHai_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawReiAiHai_Draw( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
//	fieldobj_acmd.c
//--------------------------------------------------------------
extern int FieldOBJ_AcmdSetCheck( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_AcmdSet( FIELD_OBJ_PTR fldobj, int code );
extern void FieldOBJ_CmdSet( FIELD_OBJ_PTR fldobj, int code );
extern int FieldOBJ_AcmdEndCheck( CONST_FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_AcmdEnd( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_AcmdFree( FIELD_OBJ_PTR fldobj );

extern TCB_PTR FieldOBJ_AcmdListSet( FIELD_OBJ_PTR fldobj, const FIELD_OBJ_ACMD_LIST *list );
extern int FieldOBJ_AcmdListEndCheck( TCB_PTR tcb );
extern void FieldOBJ_AcmdListEnd( TCB_PTR tcb );

extern int FieldOBJ_AcmdCodeDirChange( int dir, int code );
extern int FieldOBJ_AcmdCodeDirGet( int code );

extern void FieldOBJ_AcmdAction( FIELD_OBJ_PTR fldobj );
extern int FieldOBJ_CmdAction( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
//	fieldobj_seed.c
//--------------------------------------------------------------
extern int FieldOBJ_OBJCodeSeedCheck( int code );
extern int FieldOBJ_OBJCodeSeedGet( CONST_FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_SeedHarvestFlagSet( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_MoveSeed_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveSeed_Move( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_MoveSeed_Delete( FIELD_OBJ_PTR fldobj );

extern void FieldOBJ_DrawSeed_Init( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawSeed_Draw( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawSeed_Delete( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawSeed_Push( FIELD_OBJ_PTR fldobj );
extern void FieldOBJ_DrawSeed_Pop( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
///	fieldobj_render.c
//--------------------------------------------------------------
extern FIELD_OBJ_RENDER_CONT_PTR FieldOBJ_RenderCont_Init(
		CONST_FIELD_OBJ_SYS_PTR fos, u32 heap_id );
extern void FieldOBJ_RenderCont_Delete( FIELD_OBJ_RENDER_CONT_PTR rdcont );

extern void FieldOBJ_RenderCont_RegistInit( FIELD_OBJ_RENDER_CONT_PTR rdcont, int max );

extern int FieldOBJ_RenderCont_OBJRegSimple( FIELD_OBJ_RENDER_CONT_PTR rdcont, 
		int code, ARCHANDLE *handle, u32 data_id, u32 heap_id );
extern void FieldOBJ_RenderCont_OBJRegFree( FIELD_OBJ_RENDER_CONT_PTR rdcont, int code );
extern NNSG3dRenderObj * FieldOBJ_RenderCont_OBJRenderGet(
		FIELD_OBJ_RENDER_CONT_PTR rdcont, int code );
extern NNSG3dResMdl * FldOBJrdcont_OBJModelGet( FIELD_OBJ_RENDER_CONT_PTR rdcont, int code );

extern BLACT_WORK_PTR FieldOBJ_DrawLegend_GetBlActWorkPtr( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
///	fieldobj_debug.c
//--------------------------------------------------------------
//----
#ifdef PM_DEBUG
//----
#ifdef DEBUG_ALIES
extern FIELD_OBJ_H * DEBUG_FieldOBJ_ZoneUpdateDeleteAliesHeader(
		int new_zone_id, int *head_max, const FIELD_OBJ_H *head );
extern void DEBUG_FieldOBJ_ZoneUpdateDeleteAliesHeaderDelete( FIELD_OBJ_H *head );
extern FIELD_OBJ_H * DEBUG_FieldOBJ_AddBinHeaderAlies(
		int zone_id, int *head_max, const FIELD_OBJ_H *head );
extern void DEBUG_FieldOBJ_AddBinHeaderAliesDelete( FIELD_OBJ_H *head );
#endif
//----
#endif	//PM_DEBUG
//----

#endif	//FIELD_OBJ_H_FILE

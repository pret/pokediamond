//=============================================================================
/**
 * @file	union_beacon_tool.c
 * @brief	���j�I�����[���r�[�R������
 * @author	Akito Mori
 * @date    	2006.03.16
 */
//=============================================================================
#include "common.h"

#include "gflib/strbuf.h"
#include "system/wordset.h"
#include "system/arc_tool.h"
#include "system/arc_tool.dat"
#include "system/arc_util.h"
#include "../application/record/record.naix"
#include "fieldobj_code.h"
#include "msgdata/msg_trtype.h"
#include "comm_union_beacon.h"
#include "battle/trtype_def.h"
#include "field/union_beacon_tool.h"


#define UNION_VIEW_TYPE_NUM	( 16 )

// ���j�I�����[���ŕ\������g���[�i�[�̃^�C�v�����ځ����O���g���[�i�[�O���t�B�b�N�e�[�u��
static const int UnionViewTable[][3]={

	{ BOY1,			MSG_TRTYPE_SCHOOLB, 	TRTYPE_SCHOOLB    },	///< ���キ������
	{ BOY3,			MSG_TRTYPE_MUSHI,   	TRTYPE_MUSHI      },	///< �ނ��Ƃ肵�傤�˂�
	{ MAN3,			MSG_TRTYPE_ELITEM,  	TRTYPE_ELITEM     },	///< �G���[�g�g���[�i�[��
	{ BADMAN,		MSG_TRTYPE_HEADS,   	TRTYPE_HEADS      },	///< �X�L���w�b�Y
	{ EXPLORE,		MSG_TRTYPE_ISEKI,   	TRTYPE_ISEKI      },	///< �������}�j�A
	{ FIGHTER,		MSG_TRTYPE_KARATE,  	TRTYPE_KARATE     },	///< ����Ă���
	{ GORGGEOUSM,	MSG_TRTYPE_PRINCE,  	TRTYPE_PRINCE     },	///< ���ڂ������
	{ MYSTERY,		MSG_TRTYPE_ESPM,    	TRTYPE_ESPM       },	///< �T�C�L�b�J�[

	{ GIRL1,		MSG_TRTYPE_MINI,  		TRTYPE_MINI       },	///< �~�j�X�J�[�g
	{ GIRL2,		MSG_TRTYPE_BATTLEG, 	TRTYPE_BATTLEG    },	///< �o�g���K�[��
	{ WOMAN2,		MSG_TRTYPE_SISTER, 		TRTYPE_SISTER     },	///< ���ƂȂ̂��˂�����
	{ WOMAN3,		MSG_TRTYPE_ELITEW,  	TRTYPE_ELITEW 	  },	///< �G���[�g�g���[�i�[��
	{ IDOL,			MSG_TRTYPE_IDOL,    	TRTYPE_IDOL       },	///< �A�C�h��
	{ LADY,			MSG_TRTYPE_MADAM, 		TRTYPE_MADAM      },	///< �}�_��
	{ COWGIRL,		MSG_TRTYPE_COWGIRL, 	TRTYPE_COWGIRL    },	///< �J�E�K�[��
	{ GORGGEOUSW,	MSG_TRTYPE_PRINCESS,	TRTYPE_PRINCESS   },	///< �����傤����

};

// �����ڕύX���₶�p�̃e�[�u���iID���W�Ŋ��������܂�ɑΉ�����j
static const int UnionViewNameTable[][4]={
	{0,1,2,3,},
	{1,6,7,0,},

	{2,3,4,5,},
	{3,0,5,6,},

	{4,1,2,7,},
	{5,2,7,0,},

	{6,3,4,1,},
	{7,4,5,6,},
};

#define UNION_VIEW_SELECT_NUM	( 4 )
#define UNION_VIEW_SELECT_TYPE	( 8 )

//==============================================================================
/**
 * $brief   ID�Ɛ��ʂ���I���ł���S�̃g���[�i�[�^�C�v�̕�������i�[����
 *
 * @param   id			���[�U�[ID
 * @param   sex			����
 * @param   wordset		������i�[�o�b�t�@
 *
 * @retval  none		
 */
//==============================================================================
void UnionView_SetUpTrainerTypeSelect( u32 id, int sex, WORDSET *wordset )
{
	int key    = id%8;
	int i;

	// ID���W�Ŋ������]��ŁA�Ή�����4�̑I�����𐫕ʂ��Ƃɗp�ӂ���

	for(i=0; i<UNION_VIEW_SELECT_NUM; i++){
		int patern = UnionViewNameTable[key][i] + UNION_VIEW_SELECT_TYPE * sex;
		WORDSET_RegisterTrTypeName( 	  wordset, i, UnionViewTable[patern][1] );
	}


}


//==============================================================================
/**
 * $brief   �I�����ʂ��猈�肵���g���[�i�[�^�C�v�̔ԍ����̂��̂��Z�o����
 *
 * @param   id			���[�U�[ID
 * @param   sex			����
 * @param   select		�I�����ʁi0-3)
 *
 * @retval  int		
 */
//==============================================================================
int UnionView_GetTrainerType( u32 id, int sex, u32 select )
{
	int key    = id%8;
	int patern = UnionViewNameTable[key][select] + UNION_VIEW_SELECT_TYPE * sex;

	return UnionViewTable[patern][0];
}

//------------------------------------------------------------------
/**
 * $brief   ���j�I�����[���p�̌����ڔԍ��e�[�u�����������ēY������Ԃ�
 *
 * @param   sex			����
 * @param   view_type	�����ڔԍ�
 *
 * @retval  int			�Y�����ԍ�
 */
//------------------------------------------------------------------
static int Search_ViewNo( int sex, int view_type )
{
	int i;
	for(i=0;i<UNION_VIEW_TYPE_NUM/2;i++){
		if(UnionViewTable[i+(sex*(UNION_VIEW_TYPE_NUM/2))][0]==view_type){
			return i + (sex*(UNION_VIEW_TYPE_NUM/2));
		}	
	}
	return 0;
}
//==============================================================================
/**
 * $brief   �����ڔԍ��Ɛ��ʂ���2D�L�����̈ʒu���擾����
 *
 * @param   sex		
 * @param   view_type		
 *
 * @retval  int		
 */
//==============================================================================
int UnionView_GetCharaNo( int sex, int view_type )
{

	return Search_ViewNo( sex, view_type );
}


//==============================================================================
/**
 * $brief   �g���[�i�[VIEWTYPE�Ɛ��ʂ�����������o��
 *
 * @param   sex			����
 * @param   view_type	MyStatus_GetTrainerView�Ŏ擾�ł���R�[�h
 * @param   info		�~�����f�[�^�̃^�C�v
 *                      UNIONVIEW_ICONINDEX:	0�l�߂ŉ��Ԗڂ�
 *						UNIONVIEW_MSGTYPE:		���b�Z�[�W�f�[�^�ԍ��iex �u���キ������v��MSGNO�j
 *						UNIONVIEW_TRTYPE:		�g���[�i�[�O���t�B�b�N�ԍ�
 *
 * @retval  int			0����l�߂����ɉ��Ԗڂ̃L������
 */
//==============================================================================
int UnionView_GetTrainerInfo( int sex, int view_type, int info )
{
    int i = Search_ViewNo( sex, view_type );

    switch(info){
      case UNIONVIEW_ICONINDEX:
        return i;
		break;
      case UNIONVIEW_MSGTYPE:
        return UnionViewTable[i][1];
		break;
      case UNIONVIEW_TRTYPE:
        return UnionViewTable[i][2];
		break;
      default:
	    GF_ASSERT(0);
    }

	// �����܂Ŕ�����̂͂�������
	return 0;
}


//==============================================================================
/**
 * $brief   �w���OBJ�ɕK�v�ȃp���b�g�̃|�C���^��Ԃ�
 *
 * @param   sex		
 * @param   view_type		
 *
 * @retval  u16 *		
 */
//==============================================================================
u16 *UnionView_GetPalNo( u16 * table, int sex, int view_type )
{
	int ret;
	ret = Search_ViewNo( sex, view_type );
	
	return &table[16*2*ret];
}

//==============================================================================
/**
 * $brief   18�̕��̃p���b�g�̃e�[�u����Alloc��۰�ނ��ĕԂ�
 *
 * @param   heapID		�q�[�vID
 *
 * @retval  u16 *		OBJ�p�̃p���b�g�e�[�u���i����͊e���Łj
 */
//==============================================================================
u16 *UnionView_PalleteTableAlloc( int heapID )
{
	u8 *data1, *data2;
	NNSG2dPaletteData *pal1,*pal2;
	u16 *palette_table,*src;
	int i;
	
	data1 = ArcUtil_PalDataGet( ARC_RECORD_GRA, NARC_record_union_chara_nclr, &pal1, heapID );

	palette_table = sys_AllocMemory( heapID, 16*18*2 );
	OS_Printf("allocwork = %08x srcpallette = %08x\n",palette_table, pal1->pRawData);

	src = (u16*)pal1->pRawData;
	for(i=0;i<16*16;i++){
		palette_table[i] = src[i];
	}
//	MI_CpuCopyFast(pal1->pRawData, &palette_table[    0], 16*16*2);
//	MI_CpuCopyFast(pal2->pRawData, &palette_table[16*16], 2*16*2);
	
	sys_FreeMemoryEz(data1);
	
	return palette_table;
}


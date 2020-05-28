//============================================================================================
/**
 * @file	pms_input_data.c
 * @bfief	�ȈՉ�b���͉�ʁi�J�e�S���E�C�j�V�������̃f�[�^�Ǘ��j
 * @author	taya
 * @date	06.01.28
 */
//============================================================================================
#include "common.h"
#include "gflib\heapsys.h"
#include "system\pms_word.h"
#include "savedata\zukanwork.h"
#include "msgdata\msg.naix"

#include "application\pms_input_data.h"
#include "pms_input_param.h"


#define __PMS_INPUT_RES__
#include "pms_input.res"


#define  WORD_ENABLE_FLAG_SIZE		((PMS_WORDNUM_MAX>>3)+1)	// �P��P�� =1bit���Z��

#define  INITIAL_MAX	(NELEMS(PMS_InitialTable))


//--------------------------------------------------------------
/**
 *	�f�[�^�Ǘ��I�u�W�F�N�g����
 */
//--------------------------------------------------------------
struct _PMS_INPUT_DATA {
	const PMSI_PARAM*	input_param;
	PMSW_MAN*			word_man;

	u32  GroupEnableWordCnt[ CATEGORY_GROUP_MAX ];
	u32  GroupEnableWordPos[ CATEGORY_GROUP_MAX ];
	PMS_WORD	GroupEnableWord[PMS_WORDNUM_MAX];

	u32  InitialEnableWordCnt[ INITIAL_MAX ];
	u32  InitialEnableWordPos[ INITIAL_MAX ];
	PMS_WORD  InitialEnableWord[ PMS_WORDNUM_MAX ];

	u8  word_enable_flag[ WORD_ENABLE_FLAG_SIZE ];

};

//==============================================================
// Prototype
//==============================================================
static void SetupGroupEnableFlag( PMS_INPUT_DATA* pmsi );
static inline void SetWordEnableFlag( PMS_INPUT_DATA* data, u32 pos );
static inline BOOL GetWordEnableFlag( const PMS_INPUT_DATA* data, u32 pos );
static u32 CountupGruopPokemon( PMS_INPUT_DATA* pmsi, const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl );
static u32 CountupGruopSkill( PMS_INPUT_DATA* pmsi,  const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl );
static u32 CountupGroupNankai( PMS_INPUT_DATA* pmsi,  const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl );
static u32 CountupGroupAisatsu( PMS_INPUT_DATA* pmsi,  const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl );
static u32 CountupGruopDefault( PMS_INPUT_DATA* pmsi,  const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl );
static u32 CountCategoryZero( PMS_INPUT_DATA* pmsi,  const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl );
static void SetupInitialEnableFlag( PMS_INPUT_DATA* pmsi );
static u32 CountupInitialWord( PMS_INPUT_DATA* pmsi, const PMS_WORD* src_tbl, PMS_WORD* dst_tbl, u32 dst_pos );


/*====================================================================================================*/
/*                                                                                                    */
/*  �I�u�W�F�N�g�̍\�z�E�j��                                                                          */
/*                                                                                                    */
/*====================================================================================================*/
//------------------------------------------------------------------
/**
 * �f�[�^�Ǘ��I�u�W�F�N�g�\�z
 *
 * @param   heapID		
 *
 * @retval  PMS_INPUT_DATA*		
 */
//------------------------------------------------------------------
PMS_INPUT_DATA* PMSI_DATA_Create( u32 heapID, const PMSI_PARAM* input_param )
{
	PMS_INPUT_DATA*  pmsi;
	int i;

	pmsi = sys_AllocMemory( heapID, sizeof(PMS_INPUT_DATA) );

	pmsi->input_param = input_param;
	pmsi->word_man = PMSW_MAN_Create( heapID );

	for(i=0; i<WORD_ENABLE_FLAG_SIZE; i++)
	{
		pmsi->word_enable_flag[i] = 0;
	}

	SetupGroupEnableFlag( pmsi );
	SetupInitialEnableFlag( pmsi );

	return pmsi;
}
//------------------------------------------------------------------
/**
 * �f�[�^�Ǘ��I�u�W�F�N�g�j��
 *
 * @param   heapID		
 *
 * @retval  PMS_INPUT_DATA*		
 */
//------------------------------------------------------------------
void PMSI_DATA_Delete( PMS_INPUT_DATA* pmsi )
{
	if( pmsi )
	{
		PMSW_MAN_Delete( pmsi->word_man );
		sys_FreeMemoryEz( pmsi );
	}
}


/*====================================================================================================*/
/*                                                                                                    */
/*  �J�e�S�����Ƃ̗L���P��J�E���g�֐��e�[�u��                                                        */
/*                                                                                                    */
/*====================================================================================================*/
typedef u32 (*CountupFunc)( PMS_INPUT_DATA*, const PMS_WORD*, u32, PMS_WORD* );

static const struct {
	CountupFunc      func;			///< �P��J�E���g�֐�
	const PMS_WORD*  src_tbl;		///< �P��e�[�u���A�h���X
	u32              tbl_elems;		///< �P��e�[�u���v�f��
}EnableWordCountupParam[] = {
	{ CountupGruopPokemon,  PMS_CategoryTable_01,  PMS_Category_01_MaxNum },	// �|�P����
	{ CountupGruopPokemon,  PMS_CategoryTable_02,  PMS_Category_02_MaxNum },	// �|�P�����Q
	{ CountupGruopSkill,    PMS_CategoryTable_03,  PMS_Category_03_MaxNum },	// �킴
	{ CountupGruopSkill,    PMS_CategoryTable_04,  PMS_Category_04_MaxNum },	// �킴�Q
	{ CountupGruopDefault,  PMS_CategoryTable_05,  PMS_Category_05_MaxNum },	// �X�e�[�^�X
	{ CountupGruopDefault,  PMS_CategoryTable_06,  PMS_Category_06_MaxNum },	// �g���[�i�[
	{ CountupGruopDefault,  PMS_CategoryTable_07,  PMS_Category_07_MaxNum },	// �Ђ�
	{ CountupGroupAisatsu,  PMS_CategoryTable_08,  PMS_Category_08_MaxNum },	// ��������
	{ CountupGruopDefault,  PMS_CategoryTable_09,  PMS_Category_09_MaxNum },	// ��������
	{ CountupGruopDefault,  PMS_CategoryTable_10,  PMS_Category_10_MaxNum },	// ������
	{ CountupGroupNankai,   PMS_CategoryTable_11,  PMS_Category_11_MaxNum },	// �Ȃ񂩂����Ƃ�
	{ CountupGruopDefault,  PMS_CategoryTable_12,  PMS_Category_12_MaxNum },	// ���j�I��
};

/*====================================================================================================*/
/*                                                                                                    */
/*  �J�e�S�����Ƃ̗L���P�ꐔ�J�E���g���P��ID�e�[�u����                                                */
/*                                                                                                    */
/*====================================================================================================*/
//------------------------------------------------------------------
/**
 * 
 *
 * @param   pmsi		
 *
 */
//------------------------------------------------------------------
static void SetupGroupEnableFlag( PMS_INPUT_DATA* pmsi )
{
	int i, cnt;

	for(i=0, cnt=0; i<CATEGORY_GROUP_MAX; i++)
	{
		pmsi->GroupEnableWordPos[i] = cnt;
		pmsi->GroupEnableWordCnt[i] = EnableWordCountupParam[i].func(
				pmsi, EnableWordCountupParam[i].src_tbl,
				EnableWordCountupParam[i].tbl_elems,
				&pmsi->GroupEnableWord[cnt] );
		cnt += pmsi->GroupEnableWordCnt[i];
	}

}

static inline void SetWordEnableFlag( PMS_INPUT_DATA* data, u32 pos )
{
	data->word_enable_flag[ (pos >> 3) ] |= (1 << (pos & 7));
}

static inline BOOL GetWordEnableFlag( const PMS_INPUT_DATA* data, u32 pos )
{
	return (data->word_enable_flag[ (pos >> 3) ] & (1 << (pos & 7))) != 0;
}

static u32 CountupGruopPokemon( PMS_INPUT_DATA* pmsi, const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl )
{
	const ZUKAN_WORK* zw;
	u32 i, cnt;

	cnt = 0;
	zw = PMSI_PARAM_GetZukanSaveData( pmsi->input_param );
	for(i=0; i<tbl_elems; i++)
	{
		if( ZukanWork_GetPokeSeeFlag( zw, src_tbl[i] ) )
		{
			SetWordEnableFlag( pmsi, src_tbl[i] );
			*dst_tbl++ = src_tbl[i];
			cnt++;
		}
	}

	return cnt;
}

static u32 CountupGruopSkill( PMS_INPUT_DATA* pmsi,  const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl )
{
	u32 i;

	// �N���A���Ă���S��OK
	if( PMSI_PARAM_GetGameClearFlag(pmsi->input_param) )
	{
		for(i=0; i<tbl_elems; i++)
		{
			SetWordEnableFlag( pmsi, *src_tbl );
			*dst_tbl++ = *src_tbl++;
		}
		return tbl_elems;
	}
	else
	{
		return 0;
	}
}

static u32 CountupGroupNankai( PMS_INPUT_DATA* pmsi,  const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl )
{
	const PMSW_SAVEDATA* sv = PMSI_PARAM_GetPMSW_SaveData(pmsi->input_param);
	u32 i, cnt;

	for(i=0, cnt=0; i<tbl_elems; i++)
	{
		if( PMSW_GetNankaiFlag(sv, i) )
		{
			SetWordEnableFlag( pmsi, src_tbl[i] );
			*dst_tbl++ = src_tbl[i];
			cnt++;
		}
	}
	return cnt;
}

static u32 CountupGroupAisatsu( PMS_INPUT_DATA* pmsi,  const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl )
{
	const PMSW_SAVEDATA* sv = PMSI_PARAM_GetPMSW_SaveData(pmsi->input_param);
	PMS_WORD  aisatsu_top, aisatsu_end;
	u32 i, cnt;

	aisatsu_top = PMSW_GetWordNumberByGmmID( NARC_msg_pms_word08_dat, 0 );
	aisatsu_end = aisatsu_top + PMSW_AISATSU_HIDE_MAX - 1;

	cnt = 0;

	for(i=0; i<tbl_elems; i++)
	{
		if( (src_tbl[i] >= aisatsu_top) && (src_tbl[i] <= aisatsu_end) )
		{
			u32 id = src_tbl[i] - aisatsu_top;
			if( PMSW_GetAisatsuFlag(sv, id) == FALSE)
			{
				continue;
			}
		}
		SetWordEnableFlag( pmsi, src_tbl[i] );
		*dst_tbl++ = src_tbl[i];
		cnt++;
	}
	return cnt;
}

static u32 CountupGruopDefault( PMS_INPUT_DATA* pmsi,  const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl )
{
	u32 i;

	for(i=0; i<tbl_elems; i++)
	{
		if( *src_tbl == PMS_WORDID_DUP )
		{
			u32 dup;

			src_tbl++;
			dup = *src_tbl++;
			*dst_tbl = *src_tbl;
			while( dup )
			{
				SetWordEnableFlag( pmsi, *src_tbl++ );
				dup--;
			}
		}
		else
		{
			SetWordEnableFlag( pmsi, *src_tbl );
			*dst_tbl++ = *src_tbl++;
		}
	}

	return tbl_elems;
}
#ifdef PM_DEBUG
static u32 CountCategoryZero( PMS_INPUT_DATA* pmsi,  const PMS_WORD* src_tbl, u32 tbl_elems, PMS_WORD* dst_tbl )
{
	return 0;
}
#endif

/*====================================================================================================*/
/*                                                                                                    */
/*  ���������Ƃ̗L���P�ꐔ�J�E���g���P��ID�e�[�u����                                                  */
/*  �i�J�e�S���e�[�u���쐬���ɍ�����P��L���t���O���Q�Ƃ���j                                        */
/*                                                                                                    */
/*====================================================================================================*/
static void SetupInitialEnableFlag( PMS_INPUT_DATA* pmsi )
{
	int i, pos = 0;

	for(i=0; i<NELEMS(PMS_InitialTable); i++)
	{
		pmsi->InitialEnableWordPos[i] = pos;
		pmsi->InitialEnableWordCnt[i] = CountupInitialWord(pmsi, PMS_InitialTable[i], pmsi->InitialEnableWord, pos);
		pos += pmsi->InitialEnableWordCnt[i];
	}
}

static u32 CountupInitialWord( PMS_INPUT_DATA* pmsi, const PMS_WORD* src_tbl, PMS_WORD* dst_tbl, u32 dst_pos )
{
	u32 cnt = 0;

	while( *src_tbl != PMS_WORDID_END )
	{
		if( *src_tbl == PMS_WORDID_DUP )
		{
			u32  dup, i;

			src_tbl++;
			dup = *src_tbl++;
			for(i=0; i<dup; i++)
			{
				if( GetWordEnableFlag(pmsi, src_tbl[i]) )
				{
					dst_tbl[dst_pos++] = src_tbl[i];
					cnt++;
					break;
				}
			}
			src_tbl += dup;
		}
		else
		{
			if( GetWordEnableFlag(pmsi, *src_tbl) )
			{
				dst_tbl[dst_pos++] = *src_tbl;
				cnt++;
			}

			src_tbl++;
		}
	}

	return cnt;
}

/*====================================================================================================*/
/*                                                                                                    */
/*  �A�v���P�[�V�����ւ̏���                                                                      */
/*                                                                                                    */
/*====================================================================================================*/

//------------------------------------------------------------------
/**
 * �J�e�S���O���[�v�Ɋ܂܂��L���P�ꐔ
 *
 * @param   pmsi		�f�[�^�Ǘ��I�u�W�F�N�g
 * @param   group		�O���[�v�i���o�[
 *
 * @retval  u32			�L���P�ꐔ�i�O�������炻�̃J�e�S�����̂������j
 */
//------------------------------------------------------------------
u32 PMSI_DATA_GetGroupEnableWordCount( const PMS_INPUT_DATA* pmsi, u32 group )
{
	return pmsi->GroupEnableWordCnt[group];
}
//------------------------------------------------------------------
/**
 * �J�e�S���O���[�v�̗L���P��𕶎��񉻂��ăo�b�t�@�ɃR�s�[
 *
 * @param   pmsi			�f�[�^�Ǘ��I�u�W�F�N�g
 * @param   group			�O���[�v�i���o�[
 * @param   word_idx		�P��C���f�b�N�X�i0�`�j
 *
 */
//------------------------------------------------------------------
void PMSI_DATA_GetGroupEnableWord( const PMS_INPUT_DATA* pmsi, u32 group, u32 word_idx, STRBUF* buf )
{
	u32 pos = pmsi->GroupEnableWordPos[group];
	PMSW_MAN_CopyStr( pmsi->word_man, pmsi->GroupEnableWord[pos+word_idx], buf );
}

//------------------------------------------------------------------
/**
 * �J�e�S���O���[�v�̗L���P��̓��A�w��Ԃ̒P��R�[�h��Ԃ�
 *
 * @param   pmsi			�f�[�^�Ǘ��I�u�W�F�N�g
 * @param   group			�O���[�v�i���o�[
 * @param   word_idx		�P��C���f�b�N�X
 *
 * @retval  PMS_WORD		�P��R�[�h
 */
//------------------------------------------------------------------
PMS_WORD  PMSI_DATA_GetGroupEnableWordCode( const PMS_INPUT_DATA* pmsi, u32 group, u32 word_idx )
{
	u32 pos = pmsi->GroupEnableWordPos[group];
	return pmsi->GroupEnableWord[pos+word_idx];
}

//------------------------------------------------------------------
/**
 * �C�j�V�����O���[�v�Ɋ܂܂��L���P�ꐔ
 *
 * @param   pmsi			�f�[�^�Ǘ��I�u�W�F�N�g
 * @param   initial			�C�j�V�����i���o�[
 *
 * @retval  u32			�L���P�ꐔ�i�O�������炻�̃C�j�V�������̂������j
 */
//------------------------------------------------------------------
u32 PMSI_DATA_GetInitialEnableWordCount( const PMS_INPUT_DATA* pmsi, u32 initial )
{
	return pmsi->InitialEnableWordCnt[initial];
}

//------------------------------------------------------------------
/**
 * �C�j�V�����O���[�v�̗L���P��𕶎��񉻂��ăo�b�t�@�ɃR�s�[
 *
 * @param   pmsi			�f�[�^�Ǘ��I�u�W�F�N�g
 * @param   initial			�C�j�V�����i���o�[
 * @param   word_idx		�P��C���f�b�N�X�i0�`�j
 *
 */
//------------------------------------------------------------------
void PMSI_DATA_GetInitialEnableWord( const PMS_INPUT_DATA* pmsi, u32 initial, u32 word_idx, STRBUF* buf )
{
	if( pmsi->InitialEnableWordCnt[initial] )
	{
		PMS_WORD  word_code = PMSI_DATA_GetInitialEnableWordCode(pmsi, initial, word_idx);
		PMSW_MAN_CopyStr( pmsi->word_man, word_code, buf );
	}
}

//------------------------------------------------------------------
/**
 * �C�j�V�����O���[�v�̗L���P��̓��A�w��Ԃ̒P��R�[�h��Ԃ�
 *
 * @param   pmsi			�f�[�^�Ǘ��I�u�W�F�N�g
 * @param   initial			�C�j�V�����i���o�[
 * @param   word_idx		�P��C���f�b�N�X�i0�`�j
 *
 */
//------------------------------------------------------------------
PMS_WORD PMSI_DATA_GetInitialEnableWordCode( const PMS_INPUT_DATA* pmsi, u32 initial, u32 word_idx )
{
	if( pmsi->InitialEnableWordCnt[initial] )
	{
		u32 pos = pmsi->InitialEnableWordPos[initial] + word_idx;
		return pmsi->InitialEnableWord[pos];
	}
	else
	{
		return PMS_WORD_NULL;
	}
}



//======================================================================================
// �{�b�N�X�ǎ��p�X���[�h�p����
//======================================================================================
static const u8 BoxPwdSrcGroup[] = {
	CATEGORY_GROUP_STATUS,
	CATEGORY_GROUP_TRAINER,
	CATEGORY_GROUP_PERSON,
	CATEGORY_GROUP_LIFE,
	CATEGORY_GROUP_MIND,
};



int PMSI_DAT_GetBoxPwdMax(void)
{
	int i, max;
	for(i=0, max=0; i<NELEMS(BoxPwdSrcGroup); i++)
	{
		max += EnableWordCountupParam[ BoxPwdSrcGroup[i] ].tbl_elems;
	}
	return max;
}



int PMSI_DAT_WordToBoxPwdID( PMS_WORD word )
{
	int i, w, tbl_max, pwd_id = 0;
	const PMS_WORD* tbl;

	for(i=0; i<NELEMS(BoxPwdSrcGroup); i++)
	{
		tbl = EnableWordCountupParam[ BoxPwdSrcGroup[i] ].src_tbl;
		tbl_max = EnableWordCountupParam[ BoxPwdSrcGroup[i] ].tbl_elems;

		for(w=0; w<tbl_max; w++)
		{
			if( tbl[w] == word )
			{
				return pwd_id;
			}
			pwd_id++;
		}
	}

	return -1;
}

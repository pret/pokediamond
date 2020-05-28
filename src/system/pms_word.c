//============================================================================================
/**
 * @file	pms_word.c
 * @bfief	�ȈՉ�b�p�P��f�[�^��舵��
 * @author	taya
 * @date	06.01.20
 */
//============================================================================================
#include "common.h"
#include "gflib\strbuf.h"
#include "system\msgdata.h"
#include "msgdata\msg.naix"

#include "system\pms_data.h"
#include "system\pms_word.h"
#include "application\pms_input_data.h"

#define __PMS_WORD_RES__
#include "pms_word.res"


#define    WORDNUM_MASK		(0x0fff)	// ���4bit�̓��[�J���C�Y�p�^����12bit���P��i���o�[


struct _PMSW_MAN {
	u32 heapID;
	MSGDATA_MANAGER*   msgman[PMS_SRCFILE_MAX];
};

//==============================================================
// Prototype
//==============================================================
static void GetWordSorceID( PMS_WORD pms_word, u32* fileID, u32* wordID );





//------------------------------------------------------------------
/**
 * 
 *
 * @param   heapID		
 *
 * @retval  PMSW_MAN		
 */
//------------------------------------------------------------------
PMSW_MAN* PMSW_MAN_Create(u32 heapID)
{
	int i;
	PMSW_MAN* man = sys_AllocMemory( heapID, sizeof(PMSW_MAN) );

	for(i=0; i<PMS_SRCFILE_MAX; i++)
	{
		man->heapID = heapID;
		man->msgman[i] = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, PMS_SrcFileID[i], heapID);
	}

	return man;
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   dat		
 *
 */
//------------------------------------------------------------------
void PMSW_MAN_Delete( PMSW_MAN* man )
{
	int i;

	for(i=0; i<PMS_SRCFILE_MAX; i++)
	{
		MSGMAN_Delete( man->msgman[i] );
	}

	sys_FreeMemoryEz(man);
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   dat			
 * @param   pms_word	
 * @param   buf			
 *
 */
//------------------------------------------------------------------
void PMSW_MAN_CopyStr( PMSW_MAN* man, PMS_WORD  pms_word, STRBUF* buf )
{
	u32 fileID, wordID;

	GetWordSorceID( pms_word, &fileID, &wordID );
	MSGMAN_GetString( man->msgman[fileID], wordID, buf );
}


//------------------------------------------------------------------
/**
 * �}�l�[�W��������A�P��𕶎��񉻂���
 *
 * @param   pms_word		
 * @param   dst		
 *
 */
//------------------------------------------------------------------
void PMSW_GetStr( PMS_WORD pms_word, STRBUF* dst )
{
	if( pms_word != PMS_WORD_NULL)
	{
		u32 fileID, strID;

		GetWordSorceID( pms_word, &fileID, &strID );
		fileID = PMS_SrcFileID[ fileID ];

		MSGDAT_GetStrDirect( ARC_MSG, fileID, strID, HEAPID_BASE_SYSTEM, dst );
	}
	else
	{
		STRBUF_Clear( dst );
	}
}

//------------------------------------------------------------------
/**
 * GMM, �P���ID����A�P��R�[�h�𐶐�
 *
 * @param   gmmID		
 * @param   wordID		
 *
 * @retval  PMS_WORD		
 */
//------------------------------------------------------------------
PMS_WORD  PMSW_GetWordNumberByGmmID( u32 gmmID, u32 wordID )
{
	u32 i;

	for(i=0; i<NELEMS(PMS_SrcFileID); i++)
	{
		if( PMS_SrcFileID[i] == gmmID )
		{
			u16 word, j;
			for(j=0, word=0; j<i; j++)
			{
				word += PMS_SrcElems[j];
			}
			return word + wordID;
		}
	}
	return PMS_WORD_NULL;
}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   pms_word		
 * @param   fileID		
 * @param   wordID		
 *
 */
//------------------------------------------------------------------
static void GetWordSorceID( PMS_WORD pms_word, u32* fileID, u32* wordID )
{
	u32 i, id_max, word;

	word = pms_word & WORDNUM_MASK;
	id_max = 0;

	for(i=0; i<PMS_SRCFILE_MAX; i++)
	{
		id_max += PMS_SrcElems[i];
		if( word < id_max )
		{
			*fileID = i;
			*wordID = (word - (id_max - PMS_SrcElems[i]));
			return;
		}
	}
}
//======================================================================================
// �Z�[�u�f�[�^�Ǘ�
//======================================================================================

#include "savedata\savedata.h"


struct _PMSW_SAVEDATA{

	u32  aisatsuBit;
	u32  nankaiBit;

};

//------------------------------------------------------------------
/**
 * �y�Z�[�u�f�[�^�V�X�e���z�T�C�Y�擾
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 PMSW_GetSaveDataSize(void)
{
	return sizeof(PMSW_SAVEDATA);
}
//------------------------------------------------------------------
/**
 * �y�Z�[�u�f�[�^�V�X�e���z�̈揉����
 *
 * @param   wk_ptr		�̈�|�C���^
 *
 */
//------------------------------------------------------------------
void PMSW_InitSaveData( void* wk_ptr )
{
	static const struct {
		u8   lang_code;
		u8   aisatsu_id;
	}langTbl[] = {
		{ LANG_JAPAN,	PMSW_AISATSU_JP },
		{ LANG_ENGLISH,	PMSW_AISATSU_EN },
		{ LANG_FRANCE,	PMSW_AISATSU_FR },
		{ LANG_ITALY,	PMSW_AISATSU_IT },
		{ LANG_GERMANY,	PMSW_AISATSU_GE },
		{ LANG_SPAIN,	PMSW_AISATSU_SP },
	};

	PMSW_SAVEDATA* wk = wk_ptr;
	int i;

	wk->aisatsuBit = 0;
	wk->nankaiBit = 0;

	// ������̂������͏�����ԂŃZ�b�g���Ă���
	for(i=0; i<NELEMS(langTbl); i++)
	{
		if( PM_LANG == langTbl[i].lang_code )
		{
			PMSW_SetAisatsuFlag( wk, langTbl[i].aisatsu_id );
			break;
		}
	}
}


//------------------------------------------------------------------
/**
 * �ȈՉ�b�P��Z�[�u�f�[�^�擾
 *
 * @param   sv		
 *
 * @retval  PMSW_SAVEDATA*		
 */
//------------------------------------------------------------------
PMSW_SAVEDATA* SaveData_GetPMSW( SAVEDATA* sv )
{
	return SaveData_Get( sv, GMDATA_ID_PMS );
}


//------------------------------------------------------------------
/**
 * ����̓�����Ƃ΂��o���Ă��邩�`�F�b�N
 *
 * @param   saveData		�ȈՉ�b�P��Z�[�u�f�[�^�|�C���^
 * @param   id				�P��ID�i0�`31�j
 *
 * @retval  BOOL			TRUE�Ȃ�o���Ă���
 */
//------------------------------------------------------------------
BOOL PMSW_GetNankaiFlag( const PMSW_SAVEDATA* saveData, u32 id )
{
	return ((saveData->nankaiBit >> id) & 1);
}

//------------------------------------------------------------------
/**
 * ������Ƃ΂������_���łЂƂo��������
 *
 * @param   saveData		�ȈՉ�b�P��Z�[�u�f�[�^�|�C���^
 *
 * @retval	int				�����S�Ċo���Ă���ꍇ:PMSW_NANKAI_WORD_MAX
 *							�V�K�ɂ��Ƃ΂��o�����ꍇ�F�P��ID�i0 �` PMSW_NANKAI_WORD_MAX-1�j
 */
//------------------------------------------------------------------
u32 PMSW_SetNewNankaiWord( PMSW_SAVEDATA* saveData )
{
	u32 i, cnt;
	for(i=0, cnt=0; i<PMSW_NANKAI_WORD_MAX; i++)
	{
		if( ((saveData->nankaiBit >> i) & 1) == 0 )
		{
			cnt++;
		}
	}
	if( cnt )
	{
		int p = gf_rand() % cnt;
		for(i=0; i<PMSW_NANKAI_WORD_MAX; i++)
		{
			if( ((saveData->nankaiBit >> i) & 1) == 0 )
			{
				if( p == 0 )
				{
					saveData->nankaiBit |= (1 << i);
					return i;
				}
				else
				{
					p--;
				}
			}
		}
	}
	return PMSW_NANKAI_WORD_MAX;
}
//------------------------------------------------------------------
/**
 * ������Ƃ΂�S�Ċo���Ă��邩�H
 *
 * @param   saveData		
 *
 * @retval  BOOL		TRUE�őS���o���Ă�B
 */
//------------------------------------------------------------------
BOOL PMSW_CheckNankaiWordComplete( PMSW_SAVEDATA* saveData )
{
	u32 i;
	for(i=0; i<PMSW_NANKAI_WORD_MAX; i++)
	{
		if( ((saveData->nankaiBit >> i) & 1) == 0 )
		{
			return FALSE;
		}
	}
	return TRUE;
}

//------------------------------------------------------------------
/**
 * ������Ƃ�ID��PMS_WORD�ɕϊ�
 *
 * @param   id		
 *
 * @retval  PMS_WORD		
 */
//------------------------------------------------------------------
PMS_WORD  PMSW_NankaiWord_to_PMSWORD( u32 id )
{
	int i;
	PMS_WORD word = 0;

	for(i=0; i<PMSW_SRC_NANKAI; i++)
	{
		word += PMS_SrcElems[i];
	}
	return word + id;
}




BOOL PMSW_GetAisatsuFlag( const PMSW_SAVEDATA* saveData, PMSW_AISATSU_ID id )
{
	return ((saveData->aisatsuBit >> id) & 1);
}

void PMSW_SetAisatsuFlag( PMSW_SAVEDATA* saveData, PMSW_AISATSU_ID id )
{
	saveData->aisatsuBit |= (1 << id);
}




//======================================================================================
// �{�b�N�X�ǎ��p�X���[�h�Ή�����
//======================================================================================


//------------------------------------------------------------------
/**
 * ����P��i���o�[����ɁA�������e�i������j�̒P�ꂪ�������邩�`�F�b�N
 *
 * @param   word	�P��i���o�[
 *
 * @retval  int		�������e�̒P�ꂪ�������邩
 */
//------------------------------------------------------------------
int PMSW_GetDupWordCount( PMS_WORD word )
{
	int  i, j;

	for(i=0; i<NELEMS(DupWordTable); i++)
	{
		for(j=0; j<DupWordTable[i].count; j++)
		{
			if( DupWordTable[i].data[j] == word )
			{
				return DupWordTable[i].count - 1;
			}
		}
	}
	return 0;
}
//------------------------------------------------------------------
/**
 * ����P��i���o�[�Ɠ������e�i������j�̒P��i���o�[��Ԃ�
 *
 * @param   word		�P��i���o�[
 * @param   idx			0�`
 *
 * @retval  PMS_WORD	�������e�̒P��i���o�[������΁A���̃i���o�[
 *						�Ȃ���΁A���������̂܂ܕԂ�
 */
//------------------------------------------------------------------
PMS_WORD PMSW_GetDupWord( PMS_WORD word, int idx )
{
	int  i, j;

	for(i=0; i<NELEMS(DupWordTable); i++)
	{
		for(j=0; j<DupWordTable[i].count; j++)
		{
			if( DupWordTable[i].data[j] == word )
			{
				int p;
				for(p=0; DupWordTable[i].count; p++)
				{
					if( idx == 0 )
					{
						return DupWordTable[i].data[p];
					}
					idx--;
				}
				GF_ASSERT_MSG(0, "word=%d, idx=%d", word, idx);
				return PMS_WORD_NULL;
			}
		}
	}
	return word;
}




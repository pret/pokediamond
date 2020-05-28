//============================================================================================
/**
 * @file	pms_data.c
 * @bfief	�ȈՕ��́i�ȈՉ�b�f�[�^�ƒ�^����g�ݍ��킹�����́j
 * @author	taya
 * @date	05.02.03
 */
//============================================================================================
#include "common.h"
#include "gflib\strbuf_family.h"
#include "system\buflen.h"
#include "system\wordset.h"
#include "system\pms_word.h"
#include "system\msgdata_util.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_pmss_union.h"
#include "msgdata\msg_pmss_ready.h"
#include "msgdata\msg_pmss_won.h"
#include "msgdata\msg_pmss_lost.h"
#include "msgdata\msg_pms_word06.h"
#include "msgdata\msg_pms_word07.h"
#include "msgdata\msg_pms_word08.h"
#include "msgdata\msg_pms_word09.h"
#include "msgdata\msg_pms_word10.h"
#include "msgdata\msg_pms_word11.h"
#include "msgdata\msg_pms_word12.h"


#include "system\pms_data.h"


//--------------------------------------------------------------
/**
 *	�萔
 */
//--------------------------------------------------------------
#define SENTENCE_ID_DEFAULT		(0)
#define SENTENCE_TYPE_CLEAR		(0xffff)


//--------------------------------------------------------------
/**
 *
 */
//--------------------------------------------------------------
static const u16 SentenceDatID[] = {
	NARC_msg_pmss_ready_dat,
	NARC_msg_pmss_won_dat,
	NARC_msg_pmss_lost_dat,
	NARC_msg_pmss_mail_dat,
	NARC_msg_pmss_union_dat,

};

//==============================================================
// Prototype
//==============================================================
static u32 get_include_word_max( u32 sentence_type, u32 sentence_id );




//------------------------------------------------------------------
/**
 * ��̕��͂Ƃ��ăN���A����
 *
 * @param   pms		
 *
 */
//------------------------------------------------------------------
void PMSDAT_Clear( PMS_DATA* pms )
{
	int i;

	pms->sentence_type = SENTENCE_TYPE_CLEAR;

	for(i=0; i<PMS_WORD_MAX; i++)
	{
		pms->word[i] = PMS_WORD_NULL;
	}
}


//------------------------------------------------------------------
/**
 * ���e�̂��镶�͂Ƃ��ď���������
 *
 * @param   pms		�ȈՕ��͍\���̂ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void PMSDAT_Init( PMS_DATA* pms, u32 sentence_type )
{
	int i;

	pms->sentence_type = sentence_type;
	pms->sentence_id = SENTENCE_ID_DEFAULT;

	for(i=0; i<PMS_WORD_MAX; i++)
	{
		pms->word[i] = PMS_WORD_NULL;
	}
}

//------------------------------------------------------------------
/**
 * ���j�I�����[���f�t�H���g�������Ƃ��ď���������
 *
 * @param   pms		�ȈՕ��͍\���̂ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void PMSDAT_SetupDefaultUnionMessage( PMS_DATA* pms )
{
	PMSDAT_Init( pms, PMS_TYPE_UNION );
	pms->sentence_id = pmss_union_06;
}


//------------------------------------------------------------------
/**
 * �o�g���^���[�f�t�H���g�������Ƃ��ď���������
 *
 * @param   pms			
 * @param   msgType		
 *
 */
//------------------------------------------------------------------
void PMSDAT_SetupDefaultBattleTowerMessage( PMS_DATA* pms, BTWR_PLAYER_MSG_ID msgType )
{
	static const struct {
		u8  sentenceType;
		u8  sentenceID;
		s16 word1_gmmID;
		u16 word1_wordID;
		s16 word2_gmmID;
		u16 word2_wordID;
	}sentenceDataTbl[] = {
		// BTWR_MSG_PLAYER_READY = �ΐ�O
		{
			PMS_TYPE_BATTLE_READY, pmss_ready_01,
			NARC_msg_pms_word06_dat, pms_word06_08,
			-1, 0,
		},
		// BTWR_MSG_PLAYER_WIN = ��������
		{
			PMS_TYPE_BATTLE_WON, pmss_won_01,
			NARC_msg_pms_word06_dat, pms_word06_34,
			-1, 0,
		},
		// BTWR_MSG_PLAYER_LOSE = ��������
		{
			PMS_TYPE_BATTLE_LOST, pmss_lost_01,
			NARC_msg_pms_word10_dat, pms_word10_11,
			-1, 0,
		},
		// BTWR_MSG_LEADER = ���[�_�[�ɂȂ�����
		{
			PMS_TYPE_BATTLE_WON, pmss_won_05,
			NARC_msg_pms_word06_dat, pms_word06_02,
			-1, 0,
		}
	};

	GF_ASSERT(msgType<NELEMS(sentenceDataTbl));

	if( msgType < NELEMS(sentenceDataTbl) )
	{
		PMSDAT_Init( pms, sentenceDataTbl[msgType].sentenceType );
		pms->sentence_id = sentenceDataTbl[msgType].sentenceID;
		if( sentenceDataTbl[msgType].word1_gmmID != -1)
		{
			pms->word[0] = PMSW_GetWordNumberByGmmID(
				 sentenceDataTbl[msgType].word1_gmmID, sentenceDataTbl[msgType].word1_wordID );
		}
		if( sentenceDataTbl[msgType].word2_gmmID != -1)
		{
			pms->word[1] = PMSW_GetWordNumberByGmmID(
				 sentenceDataTbl[msgType].word2_gmmID, sentenceDataTbl[msgType].word2_wordID );
		}
	}


}



//------------------------------------------------------------------
/**
 * �ȈՕ��̓f�[�^����A���̂܂ܕ\���ł��镶����𐶐�����
 *
 * @param   pms		
 * @param   heapID		
 *
 * @retval  STRBUF*		������
 */
//------------------------------------------------------------------
STRBUF* PMSDAT_ToString( const PMS_DATA* pms, u32 heapID )
{
	STRBUF*  sentence;
	WORDSET*  wordset;
	MSGDATA_MANAGER*   msgman;
	int i;

	wordset = WORDSET_Create(heapID);

	for(i=0; i<PMS_WORD_MAX; i++)
	{
		if( pms->word[i] != PMS_WORD_NULL )
		{
			WORDSET_RegisterPMSWord( wordset, i, pms->word[i] );
		}
		else
		{
			break;
		}
	}

	msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, SentenceDatID[pms->sentence_type], heapID );
	sentence = MSGDAT_UTIL_AllocExpandString( wordset, msgman, pms->sentence_id, heapID );

	MSGMAN_Delete(msgman);
	WORDSET_Delete(wordset);

	return sentence;
}

//------------------------------------------------------------------
/**
 * �ȈՉ�b���̓f�[�^����A�^�O�W�J�O�̕�������擾
 * �i�����炭������g���͓̂��͉�ʂ̂݁j
 *
 * @param   pms		
 * @param   heapID		
 *
 * @retval  STRBUF*		
 */
//------------------------------------------------------------------
STRBUF*  PMSDAT_GetSourceString( const PMS_DATA* pms, u32 heapID )
{
	return MSGDAT_GetStrDirectAlloc( ARC_MSG, SentenceDatID[pms->sentence_type], pms->sentence_id, heapID );
}


//------------------------------------------------------------------
/**
 * �󕶏͂ɂȂ��Ă��Ȃ����`�F�b�N
 *
 * @param   pms		
 *
 * @retval  BOOL	
 */
//------------------------------------------------------------------
BOOL PMSDAT_IsEnabled( const PMS_DATA* pms )
{
	return (pms->sentence_type != SENTENCE_TYPE_CLEAR);
}

//------------------------------------------------------------------
/**
 * ���͂Ƃ��Ċ������Ă��邩�`�F�b�N
 *
 * @param   pms		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL PMSDAT_IsComplete( const PMS_DATA* pms )
{
	u32 word_max, i;

	word_max = get_include_word_max( pms->sentence_type, pms->sentence_id );
	for(i=0; i<word_max; i++)
	{
		if( pms->word[i] == PMS_WORD_NULL )
		{
			return FALSE;
		}
	}
	return TRUE;
}

//------------------------------------------------------------------
/**
 * ���͂Ɋ܂܂��P�ꐔ��Ԃ�
 *
 * @param   sentence_type		
 * @param   sentence_id		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
static u32 get_include_word_max( u32 sentence_type, u32 sentence_id )
{
	STRBUF  *buf;
	const STRCODE* cp;
	u32 cnt;

	GF_ASSERT( sentence_type < PMS_TYPE_MAX );
	GF_ASSERT( sentence_id < PMSDAT_GetSentenceIdMax( sentence_type ) );

	buf = MSGDAT_GetStrDirectAlloc( ARC_MSG, SentenceDatID[sentence_type], sentence_id, HEAPID_BASE_SYSTEM );
	cp = STRBUF_GetStringCodePointer( buf );
	cnt = 0;
	while( *cp != EOM_ )
	{
		if( *cp == _CTRL_TAG )
		{
			if( STRCODE_CheckWordSetTagType( cp ) )
			{
				cnt++;
			}
			cp = STRCODE_SkipTag( cp );
		}
		else
		{
			cp++;
		}
	}
	STRBUF_Delete(buf);
	return cnt;
}

//------------------------------------------------------------------
/**
 * �P��i���o�[��Ԃ�
 *
 * @param   pms		
 * @param   pos		
 *
 * @retval  PMS_WORD		
 */
//------------------------------------------------------------------
PMS_WORD  PMSDAT_GetWordNumber( const PMS_DATA* pms, int pos )
{
	return pms->word[ pos ];
}
//------------------------------------------------------------------
/**
 * �ݒ肳��Ă��镶�̓^�C�v���擾
 *
 * @param   pms		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32  PMSDAT_GetSentenceType( const PMS_DATA* pms )
{
	return pms->sentence_type;
}
//------------------------------------------------------------------
/**
 * �ݒ肳��Ă��镶��ID��Ԃ�
 *
 * @param   pms		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 PMSDAT_GetSentenceID( const PMS_DATA* pms )
{
	return pms->sentence_id;
}

//------------------------------------------------------------------
/**
 * ���e��r
 *
 * @param   pms1		���͌^�ւ̃|�C���^�P
 * @param   pms2		���͌^�ւ̃|�C���^�Q
 *
 * @retval  BOOL		��v���Ă����TRUE
 */
//------------------------------------------------------------------
BOOL PMSDAT_Compare( const PMS_DATA* pms1, const PMS_DATA* pms2 )
{
	int i;

	if(	(pms1->sentence_type != pms2->sentence_type)
	||	(pms1->sentence_id != pms2->sentence_id)
	){
		return FALSE;
	}

	for(i=0; i<PMS_WORD_MAX; i++)
	{
		if( pms1->word[i] != pms2->word[i] )
		{
			return FALSE;
		}
	}

	return TRUE;
}


//------------------------------------------------------------------
/**
 * ���̓f�[�^�̃R�s�[
 *
 * @param   dst		�R�s�[��|�C���^
 * @param   src		�R�s�[���|�C���^
 */
//------------------------------------------------------------------
void PMSDAT_Copy( PMS_DATA* dst, const PMS_DATA* src )
{
	*dst = *src;
}

//==============================================================================================
//==============================================================================================
u32 PMSDAT_GetSentenceIdMax( u32 sentence_type )
{
	if( sentence_type < NELEMS(SentenceDatID) )
	{
		// �Ƃ肠��������͑S�^�C�v20�ɂȂ��Ă���̂�...
		return 20;
	}
	return 0;
}

void PMSDAT_SetSentence( PMS_DATA* pms, u32 sentence_type, u32 sentence_id )
{
	GF_ASSERT( sentence_type < PMS_TYPE_MAX );

	pms->sentence_type = sentence_type;
	pms->sentence_id = sentence_id;
}

void PMSDAT_SetWord( PMS_DATA* pms, u32 pos, PMS_WORD word )
{
	GF_ASSERT( pos < PMS_WORD_MAX );
	pms->word[pos] = word;
}


//------------------------------------------------------------------
/**
 * �g��Ȃ��P��̈��PMS_WORD_NULL�ŃN���A���Ă���
 *
 * @param   pms		
 *
 */
//------------------------------------------------------------------
void PMSDAT_ClearUnnecessaryWord( PMS_DATA* pms )
{
	u32 max, i;

	max = get_include_word_max( pms->sentence_type, pms->sentence_id );
	for(i=max; i<PMS_WORD_MAX; i++)
	{
		pms->word[i] = PMS_WORD_NULL;
	}
}




//==============================================================================================
//==============================================================================================


#ifdef PM_DEBUG
void PMSDAT_SetDebug( PMS_DATA* pms )
{
	// ���͉�ʂ���������܂ŁA�K���Ɏ��̂�^���Ă���

	pms->sentence_type = PMS_TYPE_MAIL;
	pms->sentence_id = 5;
	pms->word[0] = 933;
	pms->word[1] = 1041;
}


void PMSDAT_SetDebugRandom( PMS_DATA* pms )
{
	// �����_���ɊȈՉ�b�f�[�^��������

	pms->sentence_type = gf_rand()%4;
	pms->sentence_id = gf_rand()%5;
	pms->word[0] = gf_rand()%500;
	pms->word[1] = gf_rand()%500;

}

#endif

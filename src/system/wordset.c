//============================================================================================
/**
 * @file	wordset.c
 * @brief	�P�ꃂ�W���[������
 * @author	taya
 * @date	2005.09.28
 */
//============================================================================================
#include "common.h"

#include "gflib\msg_print.h"
#include "gflib\fntsys.h"
#include "gflib\strbuf_family.h"
#include "system\gamedata.h"
#include "system\msgdata.h"
#include "system\pm_str.h"
#include "system\placename.h"
#include "application\wifi_country.h"
#include "savedata\mystatus.h"
#include "savedata\randomgroup.h"
#include "savedata\misc.h"
#include "msgdata\msg_sodateya.h"
#include "msgdata\msg_common_scr.h"
#include "msgdata\msg_supportname.h"

#include "battle\battle_common.h"

#include "msgdata\msg.naix"
#include "system\wordset.h"


/*----------------------------------*/
/** ���@��                          */
/*----------------------------------*/
enum {
	WORDSET_GRAMMER_NONE,		///< �g�p���Ȃ�
	WORDSET_GRAMMER_MALE,		///< �j��
	WORDSET_GRAMMER_FEMALE,		///< ����
	WORDSET_GRAMMER_NEUTRAL,	///< ����
};


/*----------------------------------*/
/** �P��p�����[�^                  */
/*----------------------------------*/
typedef struct {
	u8  def_article;		///< �芥���h�c
	u8  indef_article;		///< �s�芥���h�c
	u8  preposition;		///< �O�u���h�c
	u8  grammer : 7;		///< ���@��
	u8  form : 1;			///< �P���E�����i0 = �P���j
}WORDSET_PARAM;


typedef struct {
	WORDSET_PARAM	param;
	STRBUF*			str;
}WORD;



struct _WORDSET{

	u32			max;
	u32			heapID;
	WORD*		word;
	STRBUF*		tmpBuf;

};




//==============================================================
// Prototype
//==============================================================
static void RegisterWord( WORDSET* wordset, u32 bufID, const STRBUF* str, const WORDSET_PARAM* param );
static void InitParam(WORDSET_PARAM* param);
static void RegistWord(u32 idx, const STRBUF* str, const WORDSET_PARAM* param);

//======================================================================================================
// �V�X�e���������E�I��
//======================================================================================================

//------------------------------------------------------------------
/**
 * �P��Z�b�g���W���[���쐬
 *
 * @param   heapID			�쐬��q�[�v�h�c
 *
 * @retval  WORDSET*		�P��Z�b�g
 */
//------------------------------------------------------------------
WORDSET*  WORDSET_Create( u32 heapID )
{
	return WORDSET_CreateEx( WORDSET_DEFAULT_SETNUM, WORDSET_DEFAULT_BUFLEN, heapID );
}

//------------------------------------------------------------------
/**
 * �P��Z�b�g���W���[���쐬�i�o�^�P�ꐔ�E�����񒷂̎w��Łj
 *
 * @param   word_max		
 * @param   buflen			
 * @param   heapID			
 *
 * @retval  WORDSET*		
 */
//------------------------------------------------------------------
WORDSET* WORDSET_CreateEx( u32 word_max, u32 buflen, u32 heapID )
{
	WORDSET* wordset = NULL;
	u32 i;

	GF_ASSERT_RETURN(word_max, NULL);
	GF_ASSERT_RETURN(buflen, NULL);

	do {
		WORDSET* wordset = sys_AllocMemoryLo( heapID, sizeof(WORDSET) );
		if( wordset == NULL ){ break; }

		wordset->max = word_max;
		wordset->heapID = heapID;

		wordset->tmpBuf = STRBUF_Create(buflen, heapID );
		if( wordset->tmpBuf == NULL ){ break; }

		wordset->word = sys_AllocMemoryLo( heapID, sizeof(WORD)*word_max );
		if( wordset->word == NULL ){ break; }

		for(i=0; i<word_max; i++)
		{
			InitParam(&(wordset->word[i].param));
			wordset->word[i].str = STRBUF_Create( buflen, heapID );
			if( wordset->word[i].str == NULL ){
				break;
			}
		}

		if( i == word_max )
		{
			return wordset;
		}

	}while(0);

	if( wordset )
	{
		WORDSET_Delete(wordset);
	}
	return NULL;
}

//------------------------------------------------------------------
/**
 * �P��Z�b�g�j��
 *
 * @param   wordset		
 *
 */
//------------------------------------------------------------------
void WORDSET_Delete( WORDSET* wordset )
{
	u32 i;

	GF_ASSERT(wordset->max);

	if( wordset->word )
	{
		for(i=0; i<wordset->max; i++)
		{
			if( wordset->word[i].str )
			{
				STRBUF_Delete( wordset->word[i].str );
			}
			else
			{
				break;
			}
		}
		sys_FreeMemoryEz(wordset->word);
	}

	if( wordset->tmpBuf )
	{
		STRBUF_Delete(wordset->tmpBuf);
	}

	wordset->max = 0;
	sys_FreeMemoryEz(wordset);
}


//------------------------------------------------------------------
/**
 * �P��p�����[�^������
 *
 * @param   param		�p�����[�^�\���̂ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
static void InitParam(WORDSET_PARAM* param)
{
	// ����Ȃɂ����Ă��Ȃ�
}

//======================================================================================================
// �P��Z�b�g���W���[���Ɋe��P���o�^����
//======================================================================================================

//------------------------------------------------------------------
/**
 * �P�ꕶ���񁕃p�����[�^���w��o�b�t�@�ɓo�^
 *
 * @param   wordset		�P��Z�b�g���W���[��
 * @param   bufID		�o�b�t�@�h�c
 * @param   str			������
 * @param   param		������ɕt������p�����[�^
 *
 */
//------------------------------------------------------------------
static void RegisterWord( WORDSET* wordset, u32 bufID, const STRBUF* str, const WORDSET_PARAM* param )
{
	GF_ASSERT_MSG( bufID < wordset->max, "bufID=%d, wordmax=%d", bufID, wordset->max );

	if( bufID < wordset->max )
	{
		if( param != NULL )
		{
			wordset->word[bufID].param = *param;
		}
		STRBUF_Copy( wordset->word[bufID].str, str );
	}
}



//------------------------------------------------------------------
/**
 * �C�ӕ�������p�����[�^�t���œo�^
 *
 * @param   wordset			�P��Z�b�g
 * @param   bufID			�o�b�t�@ID
 * @param   word			������
 * @param   sex				���ʃR�[�h
 * @param	singular_flag	�P�^���iTRUE�ŒP���j
 * @param   lang			����R�[�h
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterWord( WORDSET* wordset, u32 bufID, const STRBUF* word, u32 sex, BOOL singular_flag, u32 lang )
{
	RegisterWord( wordset, bufID, word, NULL );
}


//------------------------------------------------------------------
/**
 * �v���C���[����o�^
 *
 * @param   wordset		�P��Z�b�g�I�u�W�F�N�g
 * @param   bufID		�o�b�t�@ID
 * @param   status		
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPlayerName( WORDSET* wordset, u32 bufID, const MYSTATUS* status )
{
	const STRCODE * name;
	name = MyStatus_GetMyName( status );

	STRBUF_SetStringCode( wordset->tmpBuf, name );

	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * ���C�o������o�^
 *
 * @param   wordset		�P��Z�b�g���W���[��
 * @param   bufID			�o�b�t�@ID
 * @param   savedata		�Z�[�u�f�[�^�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterRivalName( WORDSET* wordset,  u32 bufID, const SAVEDATA * savedata )
{
#if 0
	static const STRCODE name[] = {
		PA_, bou_, RU_, EOM_,
	};

	// [[[ ���͌Œ薼���R�s�[���Ă��邾���B������g���[�i�[�����Q�Ƃ��Ă��낢����B
	STRBUF_SetStringCode( wordset->tmpBuf, name );
#endif
	const STRCODE * rivalname = MISC_GetRivalName(SaveData_GetMiscReadOnly(savedata));
	STRBUF_SetStringCode( wordset->tmpBuf, rivalname );

	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * �T�|�[�g�L���������w��o�b�t�@�ɓo�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   savedata		�Z�[�u�f�[�^�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSupportName( WORDSET* wordset, u32 bufID, const SAVEDATA * savedata )
{
	const MYSTATUS*  myStatus = SaveData_GetMyStatus( (SAVEDATA*)savedata );

	MSGDATA_MANAGER* man;

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_supportname_dat, wordset->heapID );

	if( MyStatus_GetMySex( myStatus ) == PM_MALE )
	{
		MSGMAN_GetString( man, support_name_female, wordset->tmpBuf );
	}
	else
	{
		MSGMAN_GetString( man, support_name_male, wordset->tmpBuf );
	}

	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
	MSGMAN_Delete(man);
}
//------------------------------------------------------------------
/**
 * �Δ�̖��O���w��o�b�t�@�ɓo�^
 *
 * @param	wordset	
 * @param   bufID			�o�b�t�@ID
 * @param   savedata		�Z�[�u�f�[�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
void WORDSET_RegisterMonumentName( WORDSET* wordset, u32 bufID, const SAVEDATA * savedata )
{
	const MISC * misc = SaveData_GetMiscReadOnly( savedata );
	STRBUF_SetStringCode( wordset->tmpBuf, MISC_GetMonumentName( misc ) );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|�P��������o�^
 *
 * @param   bufID		�o�b�t�@ID
 * @param   ppp		�|�P�����p�����[�^
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeMonsName( WORDSET* wordset, u32 bufID, POKEMON_PASO_PARAM* ppp )
{
	MSGDATA_MANAGER* man;
	u32 monsno;

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, wordset->heapID );

	// [[[�����Ń|�P�����̐��ʓ����`�F�b�N�ł���]]]
	monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
	MSGMAN_GetString( man, monsno, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);

	MSGMAN_Delete(man);
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|�P�����̃j�b�N�l�[����o�^
 *
 * @param   bufID		�o�b�t�@ID
 * @param   ppp		�|�P�����p�����[�^
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeNickName( WORDSET* wordset, u32 bufID, POKEMON_PASO_PARAM* ppp )
{
	// [[[�����Ń|�P�����̐��ʓ����`�F�b�N�ł���]]]
	PokePasoParaGet( ppp, ID_PARA_nickname_buf, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|�P�����̐e����o�^
 *
 * @param   bufID		�o�b�t�@ID
 * @param   ppp		�|�P�����p�����[�^
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeOyaName( WORDSET* wordset,  u32 bufID, POKEMON_PASO_PARAM* ppp )
{
	// [[[�����Őe�̐��ʂ��`�F�b�N�ł���]]]
	PokePasoParaGet( ppp, ID_PARA_oyaname_buf, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);

}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɐ�����o�^
 *
 * @param   bufID		�o�b�t�@ID
 * @param   number		���l
 * @param   keta		����
 * @param   dispType	���`�^�C�v
 * @param   codeType	�����R�[�h�^�C�v
 *
 * dispType :  NUMBER_DISPTYPE_LEFT    ���l��
 *             NUMBER_DISPTYPE_SPACE   �E�l�߁i�X�y�[�X���߁j
 *             NUMBER_DISPTYPE_ZERO    �E�l�߁i�[�����߁j
 *
 *
 * codeType :  NUMBER_CODETYPE_DEFAULT  ���[�J���C�Y���̃f�t�H���g���i���{���S�p���^�C�O�����p���j�ɂȂ�
 *             NUMBER_CODETYPE_ZENKAKU  �S�p���w��
 *             NUMBER_CODETYPE_HANKAKU  ���p���w��
 */
//------------------------------------------------------------------
void WORDSET_RegisterNumber( WORDSET* wordset, u32 bufID, s32 number, u32 keta, NUMBER_DISPTYPE dispType, NUMBER_CODETYPE codeType )
{
	STRBUF_SetNumber( wordset->tmpBuf, number, keta, dispType, codeType );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ��U����o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   wazaID			���UID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterWazaName( WORDSET* wordset, u32 bufID, u32 wazaID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wazaname_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString(man, wazaID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ��{������o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   ribbonID		���{��ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterRibbonName( WORDSET* wordset, u32 bufID, u32 ribbonID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_ribbon_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString(man, ribbonID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|�P�����̂Ƃ���������o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   tokuseiID		�Ƃ�����ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTokuseiName( WORDSET* wordset, u32 bufID, u32 tokuseiID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_tokusei_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString(man, tokuseiID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|�P�����̂���������o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   seikakuID		��������ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSeikaku( WORDSET * wordset, u32 bufID, u32 seikakuID )
{
	MSGDATA_MANAGER * man;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_chr_dat, wordset->heapID );
	
	MSGMAN_GetString( man, seikakuID, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );

	MSGMAN_Delete(man);
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɃA�C�e������o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   itemID			�A�C�e��ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterItemName( WORDSET* wordset, u32 bufID, u32 itemID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_itemname_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, itemID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɃA�C�e��������|�P�b�g����o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   wazaID			�|�P�b�gID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterItemPocketName( WORDSET* wordset, u32 bufID, u32 pocketID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_itempocket_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, pocketID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɃA�C�e��������|�P�b�g���i�A�C�R���t���j��o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   wazaID			�|�P�b�gID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterItemPocketWithIcon( WORDSET* wordset, u32 bufID, u32 pocketID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_itempocket_icon_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, pocketID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}


//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|�P�����i���U�j�^�C�v����o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   typeID			�^�C�vID
 * @param   msgManager		�^�C�v��GMM�𑀍삷��}�l�[�W���|�C���^
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeTypeName( WORDSET* wordset, u32 bufID, u32 typeID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_typename_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, typeID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}
//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|�P�����X�e�[�^�X����o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   statusID		�X�e�[�^�XID
 * @param   msgManager		�X�e�[�^�X��GMM�𑀍삷��}�l�[�W���|�C���^
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeStatusName( WORDSET* wordset, u32 bufID, u32 statusID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_status_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, statusID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}
//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɏ�Ԉُ햼��o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   conditionID		��Ԉُ�ID
 * @param   msgManager		��Ԉُ햼GMM�𑀍삷��}�l�[�W���|�C���^
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterBadConditionName( WORDSET* wordset, u32 bufID, u32 conditionID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_condition_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, conditionID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɖ؂̎��̖�����o�^
 *
 * @param   bufID			�o�b�t�@ID
 * @param   tasteID			�؂̎��̖�ID
 * @param   msgManager		�؂̎��̖���GMM�𑀍삷��}�l�[�W���|�C���^
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSeedTasteName( WORDSET* wordset, u32 bufID, u32 tasteID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_taste_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, tasteID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɒn����o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�n��ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPlaceName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_place_name_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|�P�b�`�A�v������o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�A�v����ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPoketchAppName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_poketch_app_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀg���[�i�[��ʂ�o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�g���[�i�[���ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTrTypeName( WORDSET* wordset, u32 bufID, u32 strID )
{
	//poketool/tr_tool.h���C���N���[�h����
	//TT_TrainerTypeSexGet(strID)�Ƃ��邱�ƂŃg���[�i�[�̐��ʂ��擾�ł��܂�
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_trtype_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀg���[�i�[��ʂ�o�^�i�퓬��p�j
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�g���[�i�[���ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTrTypeNameBattle( WORDSET* wordset, u32 bufID, TRAINER_DATA *tr_data )
{
	//poketool/tr_tool.h���C���N���[�h����
	//TT_TrainerTypeSexGet(tr_data->tr_type)�Ƃ��邱�ƂŃg���[�i�[�̐��ʂ��擾�ł��܂�
	
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_trtype_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, tr_data->tr_type, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀg���[�i�[����o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�g���[�i�[���ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTrainerName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_trname_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀg���[�i�[����o�^�i�퓬��p�j
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�g���[�i�[���ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTrainerNameBattle( WORDSET* wordset, u32 bufID, TRAINER_DATA *tr_data )
{
	//poketool/tr_tool.h���C���N���[�h����
	//TT_TrainerTypeSexGet(tr_data->tr_type)�Ƃ��邱�ƂŃg���[�i�[�̐��ʂ��擾�ł��܂�

	STRBUF_SetStringCode( wordset->tmpBuf, &tr_data->name[0] );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɒn���A�C�e���i���΁j����o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�n���A�C�e���i���΁jID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterUGItemName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_undergrounditem_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɒn��㩖���o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�n�����ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterUGTrapName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_undergroundtrap_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɐR������o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�R����ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterJudgeName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_cmsg_judge_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɃR���e�X�g�����N����o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�����NID(CAMSG_CONRANK_NORMAL, CAMSG_CONRANK_SUPER, ��)
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterContestRank( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_cmsg_acting_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �R���e�X�g�^�C�v(�R���e�X�g����)�Ƀ^�C�v����o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�^�C�vID(CAMSG_CONTYPE_STYLE, ��)
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterContestType( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_cmsg_acting_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɔ閧�̎����o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�閧�̎���ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSecretQuestion( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_undersecretquestion_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɔ閧�̎���̓�����o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�閧�̎���̓���ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSecretAnswer( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_undersecretanswer_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɃO�b�Y����o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�O�b�Y��ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterUGGoodsName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_undergroundgoods_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|�P�������ʖ���o�^
 *
 * @param   bufID		�o�b�t�@ID
 * @param   sex			����
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeMonsSex( WORDSET* wordset, u32 bufID, u8 sex)
{
	MSGDATA_MANAGER* man;

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_common_scr_dat, wordset->heapID );

	switch(sex){
	case PARA_MALE:
		MSGMAN_GetString( man, msg_mons_sex_osu, wordset->tmpBuf );
		break;
	case PARA_FEMALE:
		MSGMAN_GetString( man, msg_mons_sex_mesu, wordset->tmpBuf );
		break;
	default:
		STRBUF_Clear( wordset->tmpBuf );
	}
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
	MSGMAN_Delete(man);

}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ{�b�N�X�̃g���C����o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g�|�C���^
 * @param   bufID		�o�b�t�@ID
 * @param   boxData		�{�b�N�X�f�[�^�|�C���^
 * @param   u32         �g���C�i���o�[
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterBoxTrayName( WORDSET* wordset, u32 bufID, const BOX_DATA* boxData, u32 trayNumber )
{
	BOXDAT_GetBoxName( boxData, trayNumber, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɃW������o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�O�b�Y��ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterGymName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_gym_name_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ɏ��ԑт�o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�O�b�Y��ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTimeType( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_time_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɍ�����o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		��ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterCountryName( WORDSET* wordset, u32 bufID, u32 countryID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wifi_place_msg_world_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, countryID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɒn�於��o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   countryID	��ID
 * @param   placeID		�n��ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterLocalPlaceName( WORDSET* wordset, u32 bufID, u32 countryID, u32 placeID )
{
	u32  datID;

	datID = WIFI_COUNTRY_CountryCodeToPlaceMsgDataID(countryID);
	if( datID )
	{
		if( placeID )
		{
			MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, datID, wordset->heapID);
			if( man )
			{
				MSGMAN_GetString( man, placeID, wordset->tmpBuf );
				RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
				MSGMAN_Delete(man);
			}
		}
	}
}


//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɊȈՉ�b�P���o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   word		�ȈՉ�b�P��i���o�[
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPMSWord( WORDSET* wordset, u32 bufID, PMS_WORD word )
{
	PMSW_GetStr( word, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
}


//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɃV�[������o�^
 *
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   strID		�V�[����ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSealName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_bc_seal_name_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}
//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|�P�����ߊl�ꏊ����o�^
 *
 * @param   wordset			���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID			���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   placeNumber		�ߊl�ꏊ�i���o�[
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeGetPlace( WORDSET* wordset, u32 bufID, u32 placeNumber )
{
	static const u16 placenameFileID[] = {
		NARC_msg_place_name_dat,
		NARC_msg_place_name_tokusyu_dat,
		NARC_msg_place_name_haihu_dat,
	};

	PLACENAME_TYPE type;
	int strID;
	MSGDATA_MANAGER* man;

	type = PlaceName_GetType( placeNumber );
	strID = PlaceName_GetIndex( placeNumber );

	man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, placenameFileID[type], wordset->heapID);
	if( man )
	{
		if( strID < MSGMAN_GetMessageCount(man) )
		{
			MSGMAN_GetString( man, strID, wordset->tmpBuf );
			RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
			MSGMAN_Delete( man );
		}
		else
		{
			MSGMAN_Delete( man );
			man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, placenameFileID[0], wordset->heapID);
			if( man )
			{
				MSGMAN_GetString( man, 0, wordset->tmpBuf );
				RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
				MSGMAN_Delete( man );
			}
		}
	}
}


//------------------------------------------------------------------
/**
 * �w��o�b�t�@�Ƀ|���g����o�^
 *
 * @param   wordset			���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID			���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   porutoID		�|���gID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPorutoName( WORDSET* wordset, u32 bufID, u32 porutoID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_porutoname_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, porutoID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɃA�N�Z�T�����i�C���[�W�N���b�v�j��o�^
 *
 * @param   wordset			���[�h�Z�b�g�I�u�W�F�N�g
 * @param   bufID			���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   porutoID		�A�N�Z�T��ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterAccessoryName( WORDSET* wordset, u32 bufID, u32 acID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_imageclip_acce_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, acID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * �w��o�b�t�@�ɃC���[�W�N���b�v�w�i�̖��O��o�^
 *
 * @param   wordset		
 * @param   bufID		
 * @param   bgID		
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterImageClibBgName( WORDSET* wordset, u32 bufID, u32 bgID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_imageclip_bg_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, bgID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * @brief	�O���[�v���E���[�_�[���̒P��o�^
 * @param	ws			WORDSET�ւ̃|�C���^
 * @param	sv			�Z�[�u�f�[�^�ւ̃|�C���^
 * @param	gid			�O���[�v�w��ID
 * @param	bufID		�o�b�t�@�w��ID
 * @param	name_type	RANDOMGROUP_NAME_GROUP or RANDOMGROUP_NAME_LEADER
 */
//------------------------------------------------------------------
void WORDSET_RegisterGroupName(WORDSET * ws, SAVEDATA * sv, int gid, int bufID, int name_type)
{
	int sex, region_code;
	STRBUF * strbuf;
	RANDOM_GROUP * rg = SaveData_GetRandomGroup(sv);
	sex = RandomGroup_GetSex(rg, gid);
	region_code = RandomGroup_GetRegionCode(rg, gid);
	strbuf = STRBUF_Create(64, HEAPID_FIELD);	//�o�b�t�@���Ă��Ɓ[
	STRBUF_SetStringCode(strbuf, RandomGroup_GetNamePtr(rg, gid, name_type));
	WORDSET_RegisterWord(ws, bufID, strbuf, sex, TRUE, region_code);
	STRBUF_Delete(strbuf);
}


//======================================================================================================
// ������W�J
//======================================================================================================

//------------------------------------------------------------------
/**
 * �o�^���ꂽ�P����g���ĕ�����W�J����
 *
 * @param   dst		�W�J��o�b�t�@
 * @param   src		�W�J��������
 *
 */
//------------------------------------------------------------------
void WORDSET_ExpandStr( const WORDSET* wordset, STRBUF* dstbuf, const STRBUF* srcbuf )
{
	const STRCODE* src;
	STRCODE *dst;

	src = STRBUF_GetStringCodePointer(srcbuf);
	STRBUF_Clear( dstbuf );

	while( *src != EOM_ )
	{
		if( *src == _CTRL_TAG )
		{
			if( STRCODE_CheckWordSetTagType(src) )
			{
				u32 word_id;

				word_id = STRCODE_GetTagParam(src, 0);

				GF_ASSERT( word_id < wordset->max );

				// [[[�C�O�łł̓p�����[�^�̉��߂��K�v]]]
				STRBUF_AddStr( dstbuf, wordset->word[ word_id ].str );
				src = STRCODE_SkipTag(src);
			}
			else
			{
				const STRCODE* p = src;

				src = STRCODE_SkipTag(src);
				while(p < src)
				{
					STRBUF_AddChar( dstbuf, *p++ );
				}
				
			}
		}
		else
		{
			STRBUF_AddChar( dstbuf, *src++ );
		}
	}
}




//======================================================================================================
// �o�b�t�@�N���A
//======================================================================================================

//------------------------------------------------------------------
/**
 * �����o�b�t�@��S�ċ󕶎���ŃN���A����
 *
 * @param   wordset		WORDSET�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void WORDSET_ClearAllBuffer( WORDSET* wordset )
{
	u32 i;
	for(i=0; i<wordset->max; i++)
	{
		STRBUF_Clear( wordset->word[i].str );
	}
}





//============================================================================================
/**
 * @file	sodateyadata.c
 * @brief	�}�ӏ�ԃA�N�Z�X�p�\�[�X
 * @author	mori GAME FREAK inc.
 * @date	2005.12.21
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "common.h"

#include "system/gamedata.h"
#include "savedata/mail.h"

#include "savedata/savedata.h"

#include "poketool/poke_tool.h"
#include "poketool/poke_tool_def.h"
#include "savedata/sodateyadata.h"

#include "poketool/monsno.h"

//============================================================================================
//============================================================================================

//----------------------------------------------------------
/**
 * @brief	��ĉ��f�[�^�^��`
 */
//----------------------------------------------------------

// �ʐM���[��
struct SIO_MAIL_DATA{									//���R�[�h�R�[�i�[�Ή����[���\����
	MAIL_DATA	Mail;							//���[���f�[�^
	STRCODE oyaname[PERSON_NAME_SIZE+1];		//���[���̎�����̖��O
	STRCODE pokename[MONS_NAME_SIZE+1];		//���[���̂��Ă��|�P�����̖��O
	u8 bLang:4;
	u8 bLangPoke:4;
};

// ��ĉ��|�P������̕�
struct SODATEYA_POKE{
	POKEMON_PASO_PARAM	Poke;					///<�a�����Ă�|�P����
	SIO_MAIL_DATA		Mail;                   ///<���R�[�h�R�[�i�[�p���[���\����
	u32					WalkCount;              ///<�����J�E���g
};

// ��ĉ����[�N
struct SODATEYA_WORK{
	SODATEYA_POKE		SodatePoke[SODATEYA_POKE_MAX];			///<��ĉ��|�P�������[�N
	u32					Egg;					///<�^�}�S(0=���� 0�ȊO=�L��=�����̃^�l
	u8					EggCount;				///<�^�}�S�z���J�E���g
};




//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	��ĉ��f�[�^�p���[�N�̃T�C�Y�擾
 * @return	int		ZUKAN_WORK�̃T�C�Y
 */
//----------------------------------------------------------
int SodateyaWork_GetWorkSize(void)
{
	return sizeof(SODATEYA_WORK);
}
//----------------------------------------------------------
/**
 * @brief	��ĉ��f�[�^�p���[�N�̐�������
 * @param	heapID		�g�p����q�[�v�̎w��
 * @return	ZUKAN_WORK	��������SODATEAYA_WORK�ւ̃|�C���^
 */
//----------------------------------------------------------
SODATEYA_WORK * SodateyaWork_AllocWork(u32 heapID)
{
	SODATEYA_WORK * sw;
	sw = sys_AllocMemory(heapID, sizeof(SODATEYA_WORK));
	SodateyaWork_Init(sw);
	return sw;
}

//----------------------------------------------------------
/**
 * @brief	��ĉ��f�[�^�p���[�N�̃R�s�[
 * @param	from	�R�s�[��ZUKAN_WORK�ւ̃|�C���^
 * @param	to		�R�s�[��ZUKAN_WORK�ւ̃|�C���^
 */
//----------------------------------------------------------
void SodateyaWork_Copy(const SODATEYA_WORK * from, SODATEYA_WORK * to)
{
	MI_CpuCopy8(from, to, sizeof(SODATEYA_WORK));
}

//============================================================================================
//
//				�����֐�
//
//============================================================================================

//============================================================================================
//
//			��ĉ��f�[�^��񑀍�p�̊O�����J�֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief		��ĉ����[�N�̏�����
 * @param	zw	��ĉ����[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void SodateyaWork_Init(SODATEYA_WORK * sw)
{
	memset(sw, 0, sizeof(SODATEYA_WORK));

	PokePasoParaInit(&sw->SodatePoke[0].Poke);
	PokePasoParaInit(&sw->SodatePoke[1].Poke);

	sw->Egg      = 0;
	sw->EggCount = 0;
}


//==============================================================================
/**
 * �a�����Ă���POKE_PASO_PARAM�̃|�C���^��Ԃ�
 *
 * @param   sw		��ĉ����[�N�ւ̃|�C���^
 *
 * @retval  int		�a���Ă���|�P�����̐�
 */
//==============================================================================
SODATEYA_POKE *SodateyaWork_GetSodateyaPokePointer( SODATEYA_WORK *sw, int no )
{
	return &(sw->SodatePoke[no]);
}

//==============================================================================
/**
 * �a�����Ă���POKE_PASO_PARAM�̃|�C���^��Ԃ�
 *
 * @param   sw		��ĉ����[�N�ւ̃|�C���^
 *
 * @retval  int		�a���Ă���|�P�����̐�
 */
//==============================================================================
POKEMON_PASO_PARAM *SodateyaPoke_GetPokePasoPointer( SODATEYA_POKE *sp )
{
	return &(sp->Poke);
}


SIO_MAIL_DATA *SodateyaPoke_GetSioMailPointer( SODATEYA_POKE *sp )
{
	return &(sp->Mail);
}

//==============================================================================
/**
 * �|�P������a���ĉ����ڂ��̎擾
 *
 * @param   sw		
 * @param   no		
 *
 * @retval  int		
 */
//==============================================================================
u32 SodateyaPoke_GetWalkCount( const SODATEYA_POKE *sp )
{
	return sp->WalkCount;
}




//==============================================================================
/**
 * ��ĉ��|�P�f�[�^����ʐM�p���[���f�[�^�|�C���^���擾����
 *
 * @param   mail		
 *
 * @retval  MAIL_DATA *		
 */
//==============================================================================
MAIL_DATA *SodateyaMail_GetMailPointer( SIO_MAIL_DATA *mail )
{
	return &(mail->Mail);
}

//==============================================================================
/**
 * �ʐM�p���[���f�[�^�̒����疼�O��������擾����
 *
 * @param   mail		
 * @param   flag		SIOMAIL_FLAG_OYA(�e���j��SIOMAIL_FLAG_POKE(�|�P�������j
 *
 * @retval  STRCODE *		
 */
//==============================================================================
STRCODE *SodateyaMail_GetNamePointer( SIO_MAIL_DATA *mail, int flag )
{
	if( flag == SIOMAIL_FLAG_OYA ){
		return mail->oyaname;
	}
	// SIOMAIL_FLAG_POKE
	return mail->pokename;
}

//==============================================================================
/**
 * ��ĉ����[���̒��ɂ��閼�O�̍��R�[�h���擾����
 *
 * @param   mail		
 * @param   flag		SIOMAIL_FLAG_OYA(�e���j��SIOMAIL_FLAG_POKE(�|�P�������j
 *
 * @retval  int		
 */
//==============================================================================
int SodateyaMail_GetLanguage( SIO_MAIL_DATA *mail, int flag )
{
	if( flag == SIOMAIL_FLAG_OYA ){
		return mail->bLang;
	}
	// SIOMAIL_FLAG_POKE
	return mail->bLangPoke;
	
}

//==============================================================================
/**
 * �^�}�S�����܂�Ă��邩�̎擾
 *
 * @param   sw		
 *
 * @retval  int		
 */
//==============================================================================
int SodateyaWork_GetEggFlag( const SODATEYA_WORK *sw )
{
	return sw->Egg;
}

//==============================================================================
/**
 * ���z�������̎擾
 *
 * @param   sw		
 *
 * @retval  int		
 */
//==============================================================================
int SodateyaWork_GetEggCount( const SODATEYA_WORK *sw )
{
	return sw->EggCount;
}


//==============================================================================
//==============================================================================
//==============================================================================
//
// �ݒ�֐��Q
//
//==============================================================================



//==============================================================================
/**
 * POKE_PASO_PARAM���R�s�[����
 *
 * @param   sw		��ĉ����[�N�ւ̃|�C���^
 *
 * @retval  int		�a���Ă���|�P�����̐�
 */
//==============================================================================
void SodateyaWork_CopyPokePasoParam( SODATEYA_WORK *sw, const POKEMON_PARAM *pp, int no )
{
	sw->SodatePoke[no].Poke = pp->ppp;


//	memcpy(&(sw->SodatePoke[no].Poke), &(pp->ppp), PokemonPasoParamSizeGet());
}

//==============================================================================
/**
 * �|�P������a���ĉ����ڂ��ݒ�
 *
 * @param   sw		
 * @param   no		
 *
 * @retval  int		
 */
//==============================================================================
void SodateyaPoke_SetWalkCount( SODATEYA_POKE *sp, int num )
{
	sp->WalkCount = num;
}

//==============================================================================
/**
 * �����J�E���g�i�o���n�j�𑫂�
 *
 * @param   sp		
 * @param   num		
 *
 * @retval  none		
 */
//==============================================================================
void SodateyaPoke_AddWalkCount( SODATEYA_POKE *sp, int num )
{
	sp->WalkCount += num;
}


//==============================================================================
/**
 * �^�}�S�����܂�Ă��邩�ݒ�
 *
 * @param   sw		
 *
 * @retval  int		
 */
//==============================================================================
void SodateyaWork_SetEggFlag( SODATEYA_WORK *sw, int Flag)
{
	sw->Egg = Flag;
}

//==============================================================================
/**
 * ���z�������̐ݒ�
 *
 * @param   sw		
 *
 * @retval  int		
 */
//==============================================================================
void SodateyaWork_SetEggCount( SODATEYA_WORK *sw, int Count )
{
	sw->EggCount = Count;
}


//==============================================================================
/**
 * @brief   ��ĉ��ɗa�����Ă���|�P�����ɈႤ���̃|�P���������邩�H
 *
 * @param   sw		
 *
 * @retval  BOOL	TRUE:�Ⴄ���|�P�������a���Ă���
 */
//==============================================================================
BOOL  SodateyaWork_GetRareFlag( SODATEYA_WORK *sw )
{
	int country1, country2;
	country1 = PokePasoParaGet( &sw->SodatePoke[0].Poke, ID_PARA_country_code, NULL);
	country2 = PokePasoParaGet( &sw->SodatePoke[1].Poke, ID_PARA_country_code, NULL);

	// ���̂Q�C�͈Ⴄ����R�[�h�̃|�P�������H
	if(country1!=country2){
		return TRUE;
	}
	
	return FALSE;
}

//==============================================================================
/**
 * @brief   ��ĉ����̃|�P���������R�s�[
 *
 * @param   des		
 * @param   src		
 *
 * @retval  none		
 */
//==============================================================================
void SodateyaPoke_Copy( SODATEYA_POKE *des, const SODATEYA_POKE *src)
{
	*des = *src;
}



// =================================================================
/**
 * @brief �ʐM���[���\���̏�����
 * @param  smd
 * @retval  none
 */
// =================================================================
void SioMailDataInit( SIO_MAIL_DATA	*smd )
{
	int i;
	
	for(i=0;i<PERSON_NAME_SIZE+EOM_SIZE;i++) {
		smd->oyaname[i] = 0;						//�e�̖��O������
	}
	for(i=0;i<MONS_NAME_SIZE+EOM_SIZE;i++){	
		smd->pokename[i] = 0;						//�|�P�����̖��O������
	}
	smd->oyaname[0]  = EOM_;
	smd->pokename[0] = EOM_;

//	MailDataInit(&smd->Mail);						//���[���f�[�^


}

//--------------------------------------------------------------------------
/**
 * ��ĉ��|�P�����f�[�^������
 *
 * @param   poke		
 *
 * @retval  none		
 *
 *
 */
//--------------------------------------------------------------------------
void SodateyaPoke_Init(SODATEYA_POKE *poke)
{

	PokePasoParaInit(&poke->Poke);
	poke->WalkCount = 0;
	SioMailDataInit(&poke->Mail);
	
}


//============================================================================================
//
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	������ԃf�[�^�ւ̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	ZUKAN_WORK	�����񃏁[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
SODATEYA_WORK * SaveData_GetSodateyaWork(SAVEDATA * sv)
{
	SODATEYA_WORK * sw;
	sw = SaveData_Get(sv, GMDATA_ID_SODATEYA);
	return sw;
}

//============================================================================================
//============================================================================================




//===============================================================
//
//
//==============
/**
 * @file	sodateya.c
 * @brief	�����ĉ��E�^�}�S����
 * @author	Akito Mori
 * @date	05.12.10 
 *
 * Copyright (C) 2005 GAME FREAK inc.
*/
//=============================================================================


//����ł܂����݂��Ă��Ȃ����m
//	EventFlagSet(FE_SODATE_TAMAGO);											//�����������ړ��t���Oset
//				if(ksw->dadlist[i] == GetWazaNoItem(ITEM_WAZAMASIN01+w)){	//�q���͋Z�}�V���ł��邱�Ƃ��ł���Ȃ�
//					if(PokeWazaMachineCheck(p,w)){							// �Z�}�V���ŋZ���o���邩
//		event = POS_EVENT_EGG;												// POS_EVENT_EGG�Ƃ�����`���Ȃ�
//					ScriptParameter0 = i;									// �^�}�S���z��Ƃ��̃f���ւ̎w����@���Ȃ�
//				if(PokeParaGet( pp, ID_PARA_fusei_tamago_flag,NULL)){		//����̓_���^�}�S����Ȃ����H
//		PokePasoParaGet( ppp, ID_PARA_monsname, buf );						// �J���m�n�̖��O�����Ȃ�

//	zukanno = PokeMonsNo2ZukanNoGet(monsno);							//�}�ӂm�n�֕ϊ�
//	ZukanCheck(zukanno,Z_SEE_SET);										//�}�ӌ����t���O�Z�b�g
//	ZukanCheck(zukanno,Z_GET_SET);										//�}�ӃQ�b�g�t���O�Z�b�g
//	mappos = GetNowWorldPos();											//�z�������ꏊ��ݒ�
//	PokePPMaxSet(&PokeParaMine[no]);									//PP����
//	SodateyaMsgPrint(bmpid,buf,12+11*7,y);

//#define  SODATEYA_DEBUG
#define SODATEYA_MAIN
//#define RARE_DEBUG		// �R�����g���͂����ƃ^�}�S���K�����A�ɂȂ�

#include "common.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"
#include "gflib/calctool.h"
#include "system/wordset.h"
#include "system\msgdata.h"
#include "system\msgdata_util.h"
#include "fieldsys.h"
#include "system/fontproc.h"
#include "gflib/msg_print.h"
#include "poketool/poke_tool.h"
#include "itemtool/itemsym.h"
#include "poketool/monsno.h"
#include "battle/wazano_def.h"
#include "battle\tokusyu_def.h"
#include "poketool/pokeparty.h"
#include "savedata/savedata.h"
#include "savedata/mystatus.h"
#include "savedata/mail.h"
#include "savedata/record.h"
#include "savedata/perapvoice.h"
#include "itemtool/item.h"
#include "poketool/poke_memo.h"
#include "ev_time.h"

#include "system/gamedata.h"
#include "kowaza.h"
#include "savedata/sodateyadata.h"
#include "sodateya.h"

#include "msgdata/msg_sodateya.h"

#include "system/placename.h"
//#include "msgdata/msg_place_name.h"�������W���[�����Ȃ炢��Ȃ��͂�
#include "msgdata/msg_place_name_haihu.h"
#include "msgdata/msg_place_name_tokusyu.h" //�������W���[�����Ȃ炢��Ȃ��͂�


// =================================================================
// ��`
// =================================================================
#define WAZA_MACHINE_MAX 	(100)				///< �Z�}�V���̐�
#define	BIRTH_LEVEL			(1)					///< �^�}�S���琶�܂ꂽ���̃|�P�����̃��x��
#define METAMON_NO			(MONSNO_METAMON)	///< ���^�����̊J��NO
#define HUKA_FIRST_NATUKIDO (120)				///< �^�}�S���琶�܂ꂽ���̂Ȃ��x
#define NON_ITEM			( 0 )
#define POKE_KOWAZA_MAX		( 16 )				///< �q�Z�̃}�b�N�X


// =================================================================
// extern
// =================================================================
extern s16 BoxTumeMineData();					///< �莝�����l�߂�



// =================================================================
// �v���g�^�C�v�錾
// =================================================================
void PokemonTamagoSet(POKEMON_PARAM *pp, u16 monsno, SODATEYA_WORK *sodateya, u32 id, u8 form_no);
void SioMailDataInit(SIO_MAIL_DATA	*smd);
static  u8 SodateyaPokeAffinity(SODATEYA_WORK	*sodateya);
static void	TamagoDemoMsgSet(u8 w_index, const void* msg,u8 x,u8 y,u8 wait);
static int GetGrowthSpeed( POKEPARTY *party );
static u8 CalcAffinity( POKEMON_PASO_PARAM** ppp );

void PokeMakeNidoranOsuTamago(SODATEYA_WORK *sodateya);
void DelSodateyaTamagoSub(SODATEYA_WORK *sodateya);
int PokeHikitoriRyoukinSub(SODATEYA_WORK *sodateya, u8 no, WORDSET *wordset);
u8 SodatePokeLevelSet( SODATEYA_WORK *sodateya, int pos, WORDSET *wordset );
u16	SodateyaAzukeName( POKEPARTY *party, int pos, WORDSET *wordset );
u8 SodateyaZiisannCheck( SODATEYA_WORK *sodateya );
void SodateyaNameSet(SODATEYA_WORK *sodateya, WORDSET *wordset);
static void PokeSodateSetOne( POKEPARTY *party, int pos, SODATEYA_POKE *sodate,  SAVEDATA *sv);
static int GetEggCountSpeed( FIELDSYS_WORK *fsys );


// =================================================================
// �����萔��`
// =================================================================
//�Q�Ђ��̂Ȃ���
//�Ƃ��Ă��悢�悤����

//�Q�Ђ��̂Ȃ���
//�܂��܂��̂悤����

//�Q�Ђ��̂Ȃ���
//����قǂ悭�Ȃ����Ȃ�

//�Q�Ђ��͂���������
//�������|�P����������
//������ł��邪�Ȃ�

static const int AffinityMsg[]={		//����������e�[�u��
	msg_sodateya_01,
	msg_sodateya_02,
	msg_sodateya_03,
	msg_sodateya_04,
};

//static const u8 level_msg[]		= {EXFONT1_,Lv__,EOM_};		//�uLV�v
//level_msg��gmm�f�[�^�Ɏ�荞�񂾂̂ŏ���MakeSodateLevelPut�֐��Ŏg�p����K�v�A��


static POKEMON_PASO_PARAM *SodateyaWork_GetPokePasoPointer( SODATEYA_WORK *sodateya, int pos)
{
	
	return SodateyaPoke_GetPokePasoPointer( SodateyaWork_GetSodateyaPokePointer(sodateya, pos) );
}


static SODATEYA_WORK *debug_sodateya;
// =================================================================
/**
 * @brief �a���Ă���|�P�����̐���Ԃ�
 * @param  none
 * @retval  u8
 */
// =================================================================
u8 PokeAzukeruCheck( SODATEYA_WORK *sodateya )
{
	u8 result,i;
	POKEMON_PASO_PARAM *paso;
	
	result=0;
	for(i=0;i<SODATEYA_POKE_MAX;i++){		//�a�����Ă���|�P�����̐����J�E���g
		paso = SodateyaPoke_GetPokePasoPointer( SodateyaWork_GetSodateyaPokePointer(sodateya, i) );
		if(PokePasoParaGet(paso,ID_PARA_monsno, NULL)!=0){
			result++;
		}
	}
	return result;
}


// =================================================================
/**
 * @brief �a������Ȃ�󂢂Ă�ԍ���Ԃ�
 * @param  none
 * @retval  s8	0,1=�󂢂Ă�ԍ�	-1=����
 */
// =================================================================
int PokeAzukeruCheckGet(SODATEYA_WORK *sodateya)
{	
	u8 i;
	POKEMON_PASO_PARAM *para;

	debug_sodateya = sodateya;

	for(i=0;i<SODATEYA_POKE_MAX;i++){					//�a���ĂȂ��̈悪������
		para = SodateyaPoke_GetPokePasoPointer( SodateyaWork_GetSodateyaPokePointer(sodateya, i) );
		if(PokePasoParaGet(para,ID_PARA_monsno,NULL)==0){
			return i;
		}
	}
	return -1;							//�����a�����Ă�
}


//------------------------------------------------------------------
/**
 * @brief   �|�P�����̎����Ă���A�C�e���̓��[����
 *
 * @param   pp		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int  PokeMailCheck(POKEMON_PASO_PARAM *ppp)
{
	int item = PokePasoParaGet(ppp, ID_PARA_item, NULL);

	return ItemMailCheck( item );

}
//--------------pokemon_dp--------------

//--------------------------------------------------------------------------
/**
 * ��ĉ��|�P�������[�N�Ƀ|�P������a����(�J���g�[�E�i�i�V�}����)
 *
 * @param   p		
 * @param   sodate		
 *
 * @retval  none		
 *
 *
 */
//--------------------------------------------------------------------------
static void PokeSodateSetOne( POKEPARTY *party, int pos, SODATEYA_POKE *sodate,  SAVEDATA *sv)
{
	int           mail;
	POKEMON_PARAM *pp = PokeParty_GetMemberPointer( party, pos);
	const STRCODE *myname;
	STRCODE       pokename[MONS_NAME_SIZE + 1];

	SIO_MAIL_DATA      *smd = SodateyaPoke_GetSioMailPointer( sodate );
	POKEMON_PASO_PARAM *ppp = SodateyaPoke_GetPokePasoPointer( sodate );

	MYSTATUS *mystatus = SaveData_GetMyStatus( sv );
	myname             = MyStatus_GetMyName( mystatus );
	PokeParaGet( pp , ID_PARA_nickname, pokename );

	// ���[���`�F�b�N
	if(PokeMailCheck(PPPPointerGet(pp))){
		PokeParaGet( pp, ID_PARA_mail_data, SodateyaMail_GetMailPointer( smd ) );
	}

	PokeCopyPPtoPPP( pp, ppp);
	SodateyaPoke_SetWalkCount(sodate, 0);	//����������
	PokeParty_Delete( party, pos );

	// �Ă�������y���b�v�����Ȃ��Ȃ����琺�f�[�^����������
	if(PokeParty_PokemonCheck( party, MONSNO_PERAPPU )==0){
		PERAPVOICE *pv = SaveData_GetPerapVoice( sv );
		PERAPVOICE_ClearExistFlag( pv );
	}
	
//	OS_Printf("MAIL_DATA size = %d\n", sizeof(MAIL_DATA));
}


// =================================================================
/**
 * @brief �|�P������a����T�u
 * @param  p
 * @retval  none
 */
// =================================================================
void PokeSodateSet(POKEPARTY *party, int pos, SODATEYA_WORK *sodateya, SAVEDATA *sv)
{
	int work;
	RECORD *record = SaveData_GetRecord( sv );
		
	// ��ĉ��ɗa�����񐔂��{�P
	RECORD_Inc( record, RECID_SODATEYA_CNT );

	//�󂢂Ă�ꏊ��T��
	work = PokeAzukeruCheckGet(sodateya);				
	
	//�|�P�����a������
	PokeSodateSetOne(party, pos, SodateyaWork_GetSodateyaPokePointer(sodateya, work), sv);	
}

// =================================================================
/**
 * @brief ��ĉ����[�N�̃|�P�������l�߂�
 * @param  sodateya
 * @retval  none
 */
// =================================================================
static void SodateBoxTume(SODATEYA_WORK *sodateya)
{
	SODATEYA_POKE *sp1, *sp2;
	POKEMON_PASO_PARAM *ppp1, *ppp2;

	
	sp1 = SodateyaWork_GetSodateyaPokePointer( sodateya, 0 );
	sp2 = SodateyaWork_GetSodateyaPokePointer( sodateya, 1 );
	ppp1 = SodateyaPoke_GetPokePasoPointer( sp1 );
	ppp2 = SodateyaPoke_GetPokePasoPointer( sp2 );

	OS_Printf("�R�s�[�O\n");
	OS_Printf("1�C�� = %d\n",PokePasoParaGet(ppp1,ID_PARA_monsno,NULL));
	OS_Printf("2�C�� = %d\n",PokePasoParaGet(ppp2,ID_PARA_monsno,NULL));
	
	if(PokePasoParaGet(ppp1,ID_PARA_monsno,NULL)==0){			//Pokemon[1]���߹�݂�����
		if(PokePasoParaGet(ppp2,ID_PARA_monsno,NULL)!=0){		//Pokemon[0]�ɂ��Ȃ�
			SodateyaPoke_Copy(sp1,sp2);							//pokemon[1]����[0]�ɃR�s�[
			SodateyaPoke_Init(sp2);								//[1]��������	
//			SioMailDataInit(&sodateya->SodatePoke[1].Mail);	
		}
	}

	OS_Printf("�R�s�[��\n");
	OS_Printf("1�C�� = %d\n",PokePasoParaGet(ppp1,ID_PARA_monsno,NULL));
	OS_Printf("2�C�� = %d\n",PokePasoParaGet(ppp2,ID_PARA_monsno,NULL));
}

// =================================================================
/**
 * @brief �Z�o���������I�ɍs�����x���A�b�v����
 * @param  pp
 * @retval  none
 */
// =================================================================
static void PokeAutoLevelUp(POKEMON_PARAM *pp)
{
	int i,count=0,r;
	u16 waza;
	u16 result;
	
	for(i=0;i<100;i++){							//�ǂ����P�O�O�܂ł������x���͂Ȃ���
		if(PokeLevelUpCheck(pp)){				//���x���A�b�v�������H
			OS_Printf("Level Up - level %d\n", PokeParaGet(pp,ID_PARA_level, NULL));
			count=0;
			while((result=PokeWazaOboeCheck(pp,&count,&waza))!=0){		//�Z���o���邩
				OS_Printf( "LevelUpCheck result=%d, count=%d\n", result, count );

				// �Z�������ς��Ŋo�����Ȃ�����
				if(result==NO_WAZA_SET){
					OS_Printf( "OboeWaza =%d, \n", waza );
					//�Z�������ς��ł�������艟������
					PokeWazaOboeOshidashi( pp, waza );	
				}
			}
		}else{									//���x���A�b�v���Ȃ��������I��
			break;
		}
	}
	PokeParaCalc(pp);
}


#if 0
		if(PokeLevelUpCheck(pp)){				//���x���A�b�v�������H
			while((result=PokeWazaOboeCheck(pp,&count,&waza))){		//�Z���o���邩
//				count = 0;
//				result=PokeWazaOboeCheck(pp,&count,waza);
				OS_Printf( "LevelUpCheck result=%d, count=%d\n", result, count );

				// �Z�������ς��Ŋo�����Ȃ�����
				if(result==NO_WAZA_SET){
					OS_Printf( "OboeWaza =%d, \n", waza );
					//�Z�������ς��ł�������艟������
//					for(r=0;r<count;r++){
						PokeWazaOboeOshidashi( pp, waza );	
//					}
				}
//			}
		}else{									//���x���A�b�v���Ȃ��������I��
			break;
		}

#endif

//--------------------------------------------------------------------------
/**
 * �莝���Ƀ|�P�����f�[�^��߂�(�J���g�[�E�i�i�V�}����)
 *
 * @param   party		�Ă����|�P�����\����
 * @param   sp			��ĉ��|�P�����\����
 * @param   wordset		�����W�J�o�b�t�@�|�C���^
 *
 * @retval  u16		�莝���ɖ߂����|�P�����̊J���m�n
 *
 *
 */
//--------------------------------------------------------------------------
static int PokeHikitoriOne(POKEPARTY *party, SODATEYA_POKE *sp, WORDSET *wordset)
{
	POKEMON_PARAM		*pp = PokemonParam_AllocWork( HEAPID_FIELD );
	POKEMON_PASO_PARAM  *ppp = SodateyaPoke_GetPokePasoPointer(sp);
	SIO_MAIL_DATA       *smd = SodateyaPoke_GetSioMailPointer( sp );
	u32 exp;
	u16 monsno;

	WORDSET_RegisterPokeNickName( wordset, 0, ppp );		//���O�Z�b�g

	monsno = PokePasoParaGet(ppp,ID_PARA_monsno,NULL);

	PokeReplace(ppp,pp);								//���̃|�P�����p�����[�^���擾
	if(PokeParaGet(pp,ID_PARA_level,NULL)!=100){
		exp =  PokeParaGet(pp,ID_PARA_exp,NULL);						//�o���l�𑫂�
		exp += SodateyaPoke_GetWalkCount( sp );
		PokeParaPut(pp,ID_PARA_exp,(u8*)&exp);
		PokeAutoLevelUp(pp);								//���ٱ��ߏ���
	}

	if(PokeMailCheck(ppp)){
		PokeParaPut( pp, ID_PARA_mail_data, SodateyaMail_GetMailPointer( smd ) );	// ���[����߂�
	}

	
	PokeParty_Add( party, pp );									// �莝���|�P�����ɒǉ�
//	if(sp->Mail.Mail.design_no!=NON_ITEM){						//���[������������
//		PokeAddWrittenMail(&PokeParaMine[5], &sp->Mail.Mail);	//�莝���Ƀ��[�����Z�b�g
//		SioMailDataInit(&sp->Mail);								//��ĉ��̃��[����������
//	}
	// ���[���`�F�b�N


	PokePasoParaInit(ppp);										//��ĉ����[�N�������
	
	SodateyaPoke_SetWalkCount( sp, 0 );							//�����J�E���g������
	
	sys_FreeMemoryEz(pp);
	
	return monsno;
}



// =================================================================
/**
 * @brief �|�P�������������T�u
 * @param  sodateya ��ĉ����[�N
 * @param  no       ��ĉ����[�N�̂ǂ���������o����(0��1)
 * @retval  u16 ����������|�P������monsno
 */
// =================================================================
u16 PokeHikitoriSub(POKEPARTY *party, WORDSET *wordset, SODATEYA_WORK *sodateya,u8 no)
{
	u16 monsno;
	SODATEYA_POKE *sp = SodateyaWork_GetSodateyaPokePointer(sodateya,no);

	monsno = PokeHikitoriOne( party, sp, wordset);	//�莝���Ƀ|�P������߂�
	SodateBoxTume(sodateya);						//��ĉ��̃f�[�^����l�߂ɂ���

	return monsno;									//�Ђ��Ƃ����|�P�����̔ԍ�
}

// =================================================================
/**
 * @brief �����J�E���g���������̃|�P�����̃��x����Ԃ�
 * @param  p		�|�P�����\����
 * @param  walk		����
 * @retval  u8
 */
// =================================================================
int GetSinkaPokeLevel(POKEMON_PASO_PARAM *ppp, u32 walk)
{
	POKEMON_PARAM	   *tmp     = PokemonParam_AllocWork(HEAPID_FIELD);
	POKEMON_PASO_PARAM *tmp_ppp = PPPPointerGet(tmp);
	int level;

	u32	exp;

	
	PokeCopyPPPtoPPP( ppp,tmp_ppp);
	exp   = PokePasoParaGet(tmp_ppp,ID_PARA_exp,NULL);	//�ŏ��̌o���l���Z�o
	exp   += walk;										//����������
	PokePasoParaPut(tmp_ppp,ID_PARA_exp,(u8*)&exp);		//�V�����o���l�Ƃ��ăZ�b�g
	level = PokePasoLevelCalc(tmp_ppp);				//�V�������x�����Z�o
	sys_FreeMemoryEz(tmp);

	return level;
	
}


//--------------------------------------------------------------------------
/**
 * ����������Ă��郌�x���̍���Ԃ��i�J���g�[�E�i�i�V�}�Ή�)
 *
 * @param   p		
 *
 * @retval  u8		
 *
 *
 */
//--------------------------------------------------------------------------
int GetSodatePokeLevel(SODATEYA_POKE *sp)
{
	u8 level1,level2;
	POKEMON_PASO_PARAM *ppp;

	ppp = SodateyaPoke_GetPokePasoPointer( sp );

	level1 = PokePasoLevelCalc( ppp );								//�ŏ��̃��x�����Z�o
	level2 = GetSinkaPokeLevel( ppp ,SodateyaPoke_GetWalkCount(sp));//�V�������x�����Z�o
	return level2-level1;											//���x������Ԃ�
	
}

//--------------------------------------------------------------------------
/**
 * ����������Ă��郌�x���̍���Ԃ��i�J���g�[�E�i�i�V�}�Ή�)
 *
 * @param   p		
 *
 * @retval  u8		
 *
 *
 */
//--------------------------------------------------------------------------
int GetSodatePokeLevelDirect(SODATEYA_POKE *sp)
{
	u8 level;
	POKEMON_PASO_PARAM *ppp;

	ppp   = SodateyaPoke_GetPokePasoPointer( sp );
	level = GetSinkaPokeLevel( ppp ,SodateyaPoke_GetWalkCount(sp));//�V�������x�����Z�o

	return level;											//��������x�����̂܂܂�Ԃ�
	
}


// =================================================================
/**
 * @brief ��ĂĂ�|�P�����̖��O�ƃ��x�����̕�������Z�b�g
 * @param  sp ��ĉ����[�N
 * @retval  none
 */
// =================================================================
u8 SodatePokeLevelSetSub(SODATEYA_POKE *sp, WORDSET *wordset)
{
	int sa;
	STRBUF *strbuf;
	STRCODE tmpname[MONS_NAME_SIZE+1];
	POKEMON_PASO_PARAM *ppp = SodateyaPoke_GetPokePasoPointer(sp);
	
	sa = GetSodatePokeLevel(sp);						//��Ă����x�������Z�b�g
	WORDSET_RegisterNumber( wordset, 1, sa, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	WORDSET_RegisterPokeNickName( wordset, 0, ppp );	//�|�P�����̖��O���Z�b�g
	
	return sa;
}



//--------------------------------------------------------------------------
/**
 * ������藿����Ԃ��i�J���g�[�E�i�i�V�}����)
 *
 * @param   sp		��ĉ��|�P�������[�N
 *
 * @retval  u16		��ĉ��Ɏx�������z
 *
 *
 */
//--------------------------------------------------------------------------
int PokehikitoriRyoukinOne(SODATEYA_POKE *sp, WORDSET *wordset )
{
	u16 sa;
	POKEMON_PASO_PARAM *ppp = SodateyaPoke_GetPokePasoPointer(sp);

	sa = GetSodatePokeLevel(sp);						// ��Ă����x�������擾

	WORDSET_RegisterPokeNickName( wordset, 0, ppp );	// �|�P�����̖��O���Z�b�g

	sa = sa*100+100;									// ���z�𕶎���ŃZ�b�g
	WORDSET_RegisterNumber( wordset, 1, sa, 5, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	return sa;
	
}


// =================================================================
/**
 * @brief PokeHikitoriRyoukin�̃T�u���[�`��
 * @param  none
 * @retval  u16 ��Ă�����
 */
// =================================================================
int PokeHikitoriRyoukinSub(SODATEYA_WORK *sodateya, u8 no, WORDSET *wordset)
{
	//�|�P��������Ă��������Z�b�g
	SODATEYA_POKE *spoke;

	spoke = SodateyaWork_GetSodateyaPokePointer( sodateya, no );

	return PokehikitoriRyoukinOne(spoke, wordset);	
	
}




// =================================================================
/**
 * @brief �w��������������Ƃɂ���
 * @param  count
 * @retval  none
 */
// =================================================================
void	SodateyaPlusWalk( SODATEYA_WORK *sodateya, u16 count)
{
	SODATEYA_POKE *spoke;
	int i,walkcount;
	
	for(i=0;i<2;i++){
		spoke = SodateyaWork_GetSodateyaPokePointer( sodateya, i );
		walkcount = SodateyaPoke_GetWalkCount(spoke);
		walkcount += count;
		SodateyaPoke_SetWalkCount(spoke, walkcount);
	}

}


// =================================================================
/**
 * @brief �|�P�����̖��O�ƃ��x���̕�������Z�b�g����
 * @param  none(������PARAM0������)
 * @retval  none
 */
// =================================================================
u8 SodatePokeLevelSet( SODATEYA_WORK *sodateya, int pos, WORDSET *wordset )
{
	SODATEYA_POKE *sp       = SodateyaWork_GetSodateyaPokePointer( sodateya, pos);
	POKEMON_PASO_PARAM *ppp = SodateyaPoke_GetPokePasoPointer(sp);

	if(PokePasoParaGet( ppp, ID_PARA_monsno, NULL)){
		return SodatePokeLevelSetSub( sp, wordset );
	}
	return 0;
}




//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// �^�}�S����
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------





//------------------------------------------------------------------
/**
 * @brief   ��ĉ����[�N����|�P�����̃|�C���^��n��
 *
 * @param   sodateya		
 * @param   ppp[]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SodateyaWork_GetPokePasoPointerArray( SODATEYA_WORK *sodateya, POKEMON_PASO_PARAM *ppp[] )
{
	ppp[0] = SodateyaWork_GetPokePasoPointer( sodateya, 0);
	ppp[1] = SodateyaWork_GetPokePasoPointer( sodateya, 1);
	
}

//------------------------------------------------------------------
/**
 * ���i�������p�����`�F�b�N
 *
 * @param   sodateya	fld->SodateyaWork�̃|�C���^
 * @retval  int		
 */
//------------------------------------------------------------------
static int PokeMakeCheck(SODATEYA_WORK *sodateya)
{
	int i;
	int monsno[2],mother=-1,metamon;
	POKEMON_PASO_PARAM *ppp[2];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	for(i=0;i<2;i++){
		if(PokePasoSexGet( ppp[i] )==PARA_FEMALE){		//��e�̃|�P������T��
			mother = i;
		}
	}
	
	for(metamon=0,i=0;i<2;i++){
		if((monsno[i]=PokePasoParaGet( ppp[i], ID_PARA_monsno, NULL ))==METAMON_NO){	//���^�����`�F�b�N
			metamon++;		//���^�����̐����`�F�b�N
			mother = i;		//���^�����̈ʒu��ۑ�
		}
	}

	if(metamon==2){								//���^�������Q�̂���ꍇ�͂ǂ��炩���I�Ō��߂�
		if(gf_rand()>=(GF_RAND_MAX/2)){
			mother = 0;
		}else{
			mother = 1;
		}
	}											//���^�������P�̂��鎞�͊��Ƀ��^�����̈ʒu���i�[����Ă���̂ł�����g��

	OS_Printf("ppp[0]=%08x, ppp[1]=%08x, mother=%d\n",ppp[0],ppp[1],mother);

	if(PokePasoParaGet(ppp[mother],ID_PARA_item, NULL)==ITEM_KAWARAZUNOISI){		//����炸�̐΂������Ă��邩�`�F�b�N
		if(gf_rand()>=(GF_RAND_MAX/2)){			//���i���p�����邩���I
			return -1;
		}
	}else{
		return -1;
	}
	
	return mother;								//���i���p��������̓Y������Ԃ�
}



// =================================================================
/**
 * @brief �^�}�S�����
 * @param  sodateya
 * @retval  none
 */
// =================================================================
void PokeMakeTamago(SODATEYA_WORK *sodateya)
{
	u32 oya_personal_rnd = 0, personal_rnd;
	int kawarazu,seikaku;
	int limitcounter=0;

	if((kawarazu=PokeMakeCheck(sodateya)) < 0){			//�u����炸�̐΁v�������Ă��邩�H���I�Ő��i���󂯌p�����Ƃɂ��邩�H
		SodateyaWork_SetEggFlag( sodateya, gf_mtRand() );
	}else{
		POKEMON_PASO_PARAM *ppp = SodateyaWork_GetPokePasoPointer( sodateya, kawarazu );

		oya_personal_rnd=PokePasoParaGet( ppp ,ID_PARA_personal_rnd,NULL);		//�������擾
		seikaku = PokeSeikakuGetRnd( oya_personal_rnd );						//���i�擾

		for(;;){
			personal_rnd = gf_mtRand();
			if(seikaku==PokeSeikakuGetRnd(personal_rnd) && personal_rnd!=0){	//�e�̐��i�Ɠ��������ɂȂ�܂Ŗ������[�v
				break;
			}
			if(++limitcounter>2400){											//�������[�v�͂��Ȃ��悤�ɂ������̂Łi���~�b�g�J�E���^�[��݂����j
				break;															//�����s����Ȃ�����ƌ��炵�܂�
			}
		}
		SodateyaWork_SetEggFlag( sodateya, personal_rnd );
	}

	OS_Printf("eggflag=%08x\n",SodateyaWork_GetEggFlag( sodateya ));

//	EventFlagSet(FE_SODATE_TAMAGO);					//�����������ړ��t���Oset
	

	//��e�Ɠ����|�P����
	//���x���̓p�[�\�i���̐��܂�Ă��郌�x��
	//�p���[������6���ڒ��A�����_����3���ڂ𕃐e����e�Ɠ������l�ɂ��܂�
	//����\�͕͂�e�Ɠ���
	//�Z�͒ʏ�Ƀf�[�^�����A���ꂩ��p���Z�������Ă����܂�
	//�^�}�S�r�b�g�𗧂Ă܂��B
	//�^�}�S���z��܂ł̕������Ȃ��x�̏ꏊ�ɂ���܂�
}



void PokeMakeNidoranOsuTamago(SODATEYA_WORK *sodateya)
{
	SodateyaWork_SetEggFlag( sodateya, gf_rand() | 0x8000 );

//	EventFlagSet(FE_SODATE_TAMAGO);					//�����������ړ��t���Oset
}


#define BOX_MAX	6

// =================================================================
/**
 * @brief �����l�߂�i���I�p�j
 * @param  box �������n�񂪓����Ă���z��
 * @param  num �������o���Ȃ��z��̔ԍ�
 * @retval  u8 ������o�����z��̔ԍ�
 */
// =================================================================
static void SelectBoxTumeru(u8 *box, u8 num)
{
	int i,w;
	u8  work[6];
	
	box[num] = 0xff;				//�w�肳�ꂽ�a�n�w���e�e�Ŗ��߂�
	
	for(i=0;i<BOX_MAX;i++){			//���̂܂܃R�s�[
		work[i] = box[i];
	}
	w = 0;
	for(i=0;i<BOX_MAX;i++){			//0xff�������Ă��Ȃ��������l�߂ē���Ȃ���
		if(work[i]!=0xff){
			box[w++] = work[i];
		}
	}
}



// =================================================================
/**
 * @brief �q����p�̗������Z�b�g
 * @param  p			�|�P�����\����
 * @param  sodateya		��ĉ����[�N
 * @retval  none
 */
// =================================================================
static void PokeChildRandSet(POKEMON_PARAM *pp,SODATEYA_WORK *sodateya)
{
	u8 select[3],i,box[6],oya[3],work;

	for(i=0;i<6;i++) box[i] = i;			//�O�`�T�̔���p��

	for(i=0;i<3;i++){						
		select[i] = box[gf_rand()%(6-i)];	//�O�`�T�̂����R�I�ԁi�ǂ̃p���[������ύX���邩�j
		SelectBoxTumeru(box,i);				//�l�b�g�Ŏw�E����Ă����o�O�ɑΏ�
	}
	
	for(i=0;i<3;i++) oya[i] = gf_rand()%2;	//3�O���P�̗�����I�ԁi���E��ǂ��炩�痐�������o�����j

	for(i=0;i<3;i++){						//���I�̌��ʂ���R�p���[������e����R�s�[����
		POKEMON_PASO_PARAM *ppp = SodateyaWork_GetPokePasoPointer( sodateya, oya[i] );
		switch(select[i]){
			case 0:
				work = PokePasoParaGet( ppp, ID_PARA_hp_rnd,NULL);
				PokeParaPut(pp,ID_PARA_hp_rnd,(u8*)&work);
				break;
			case 1:
				work = PokePasoParaGet( ppp, ID_PARA_pow_rnd,NULL);
				PokeParaPut(pp,ID_PARA_pow_rnd,(u8*)&work);
				break;
			case 2:
				work = PokePasoParaGet( ppp,ID_PARA_def_rnd,NULL);
				PokeParaPut(pp,ID_PARA_def_rnd,(u8*)&work);
				break;
			case 3:
				work = PokePasoParaGet( ppp,ID_PARA_agi_rnd,NULL);
				PokeParaPut(pp,ID_PARA_agi_rnd,(u8*)&work);
				break;
			case 4:
				work = PokePasoParaGet( ppp, ID_PARA_spepow_rnd,NULL);
				PokeParaPut(pp,ID_PARA_spepow_rnd,(u8*)&work);
				break;
			case 5:
				work = PokePasoParaGet( ppp, ID_PARA_spedef_rnd,NULL);
				PokeParaPut(pp,ID_PARA_spedef_rnd,(u8*)&work);
				break;
		}
	}
}


// =================================================================
/**
 * @brief �p���Z�e�[�u�����擾����
 * @param  p		�|�P�����\����
 * @param  list		�p���Z���i�[����z��̃|�C���^
 * @retval u8		�z��Ɋi�[�����p���Z�̐�
 */
// =================================================================
static u8 KowazaListGet(POKEMON_PARAM *p, u16 *list)
{
	u16 monsno,startno,num,i;

	num = 0;
	startno = 0;
		
	monsno = PokeParaGet(p,ID_PARA_monsno,NULL);			//������monsno���擾
	for(i=0;i<KOWAZA_TABLE_MAX;i++){			//�q�Z�e�[�u���̎����̏ꏊ���T�[�`
		if(KowazaTable[i]==(20000+monsno)){
			startno = i+1;
			break;
		}
	}
	
	for(i=0;i<POKE_KOWAZA_MAX;i++){							//�ō��W�����Ȃ��̂ŁA�ꉞ�������P�O�܂�
		if(KowazaTable[startno+i]>20000){		//���̃|�P�����̐擪��������I��
			break;
		}else{
			list[i] = KowazaTable[startno+i];	//�Z���X�g��o�^
			num++;
		}
	}

	return num;
}

typedef struct{
	int dadlist[4];
	int commonlist[4];
	int mamlist[4];
	u16 wazalist[50];
	u16 kowazalist[POKE_KOWAZA_MAX];
}KOWAZA_SEARCH_WORK;


// =================================================================
/**
 * @brief �p���Z���Z�b�g
 * @param  p		:�^�}�S�̃|�C���^
 * @param  dad		:���|�P����
 * @param  mam		:��|�P����
 * @retval  none
 */
// =================================================================
static void KowazaSet(POKEMON_PARAM *pp, POKEMON_PASO_PARAM *dad, POKEMON_PASO_PARAM *mam)
{
	u16 i,w,n,monsno,levelwazanum,kowazanum,form;
//	PokemonParam wp;
	KOWAZA_SEARCH_WORK *ksw = sys_AllocMemory(HEAPID_FIELD, sizeof(KOWAZA_SEARCH_WORK));

	n=0;
	// �N���A
	MI_CpuClearFast(ksw, sizeof(KOWAZA_SEARCH_WORK));
	
	monsno = PokeParaGet(pp,ID_PARA_monsno,NULL);
	form   = PokeParaGet(pp,ID_PARA_form_no,NULL);
//	PokeParaSet(&wp,monsno,100,POW_RND,RND_NO_SET,0,ID_NO_SET,0);
	levelwazanum = PokeOboeruWazaAllGet( monsno, form, ksw->wazalist );		//���x���A�b�v�Ŋo����Z�����ׂă��X�g�A�b�v

	for(i=0;i<4;i++){											//�e�̎����Ă���Z���擾
		ksw->dadlist[i] = PokePasoParaGet(dad,ID_PARA_waza1+i,NULL);
		ksw->mamlist[i] = PokePasoParaGet(mam,ID_PARA_waza1+i,NULL);
	}

	kowazanum = KowazaListGet( pp, ksw->kowazalist );			//�p���Z���X�g���擾
	
	//�p���Z�v�Z
	for(i=0;i<4;i++){											//���e�̎����Ă���Z�Ǝq�̌p���Z���r
		if(ksw->dadlist[i]!=0){							
			for(w=0;w<kowazanum;w++){							//�q�Z�̐�����r
				if(ksw->dadlist[i]==ksw->kowazalist[w]){
					if(PokeWazaSet(pp,ksw->dadlist[i])==NO_WAZA_SET){	//�Z���o���邩
						PokeWazaOboeOshidashi(pp,ksw->dadlist[i]);	//�Z�������ς��ł�������艟������
					}
					break;
				}
			}
		}else{
			break;
		}
	}
	
	//���e�̊o���Ă���Z���q�����Z�}�V���Ŋo������Z�̏ꍇ
	for(i=0;i<4;i++){
		if(ksw->dadlist[i]!=0){												//���e�̎����Ă���Z��
			for(w=0;w<WAZA_MACHINE_MAX;w++){								//�Z�}�V���ɂ���A
				if(ksw->dadlist[i] == GetWazaNoItem(ITEM_WAZAMASIN01+w)){	//�q���͋Z�}�V���ł��邱�Ƃ��ł���Ȃ�
					if(PokeWazaMachineCheck(monsno,form,w)){				//�Z���o���邩
						if(PokeWazaSet( pp, ksw->dadlist[i] )==NO_WAZA_SET){		//�Z���o����
							PokeWazaOboeOshidashi( pp, ksw->dadlist[i] );			//�Z�������ς��ł�������艟������
						}
					}
				}
			}
		}
	}


	//���E��̋��ʂ��Ă�Z�Ŏq�������x���A�b�v�o������Z���擾
	for(i=0;i<4;i++){													//���E��̋��ʂ̋Z���擾
		if(ksw->dadlist[i]==0){
			break;
		}
		for(w=0;w<4;w++){
			if(ksw->dadlist[i]==ksw->mamlist[w] && ksw->dadlist[i]!=0){
				ksw->commonlist[n++] = ksw->dadlist[i];
			}
		}
	}
	
	for(i=0;i<4;i++){													//���ʋZ�̌p��
		if(ksw->commonlist[i]==0){
			break;														//����̋��ʋZ��
		}
		for(w=0;w<levelwazanum;w++){
			if(ksw->wazalist[w]!=0){											//�q���̃��x���A�b�v�Ŋo����Z��
				if(ksw->commonlist[i] == ksw->wazalist[w]){						//�����Ȃ�
					if(PokeWazaSet(pp,ksw->commonlist[i])==NO_WAZA_SET){		//�Z���o���邩
						PokeWazaOboeOshidashi(pp,ksw->commonlist[i]);			//�Z�������ς��ł�������艟������
					}
					break;
				}
			}
		}
	
	}
	
	sys_FreeMemoryEz( ksw );
}


// =================================================================
/**
 * @brief �^�}�S������
 * @param  none
 * @retval  none
 */
// =================================================================
void DelSodateyaTamagoSub(SODATEYA_WORK *sodateya)
{
	//�^�}�S�����̌�n��
	SodateyaWork_SetEggFlag( sodateya, 0 );
	SodateyaWork_SetEggCount( sodateya, 0 );
}

// =================================================================
// �A�C�e�������Ă�Ƃ��ɐ��܂��^�}�S���ς��|�P�����̃e�[�u��
// =================================================================
#define ITEM_EVELUTION_MAX		( 9 )
static const u16 ItemPokeEvoTable[ITEM_EVELUTION_MAX][3]={
	{MONSNO_SOONANO,	ITEM_NONKINOOKOU,	MONSNO_SOONANSU		},	// �\�[�i�m�@�@�̂񂫂̂������@�\�[�i���X
	{MONSNO_RURIRI,		ITEM_USIONOOKOU,	MONSNO_MARIRU		},	// �������@�@�@�������̂������@�}����
	{MONSNO_MANENE,		ITEM_AYASIIOKOU,	MONSNO_BARIYAADO,	},	// �}�l�l�@�@�@���₵���������@�o�����[�h
	{MONSNO_USOHATI,	ITEM_GANSEKIOKOU,	MONSNO_USOKKII,		},	// �E�\�n�`�@�@���񂹂��������@�E�\�b�L�[
	{MONSNO_GONBE,		ITEM_MANPUKUOKOU,	MONSNO_KABIGON,		},	// �S���x�@�@�@�܂�Ղ��������@�J�r�S��
	{MONSNO_TAMANTA,	ITEM_SAZANAMINOOKOU,MONSNO_MANTAIN,		},	// �^�}���^�@�@�����Ȃ݂������@�}���^�C��
	{MONSNO_SUBOMII,	ITEM_OHANANOOKOU,	MONSNO_ROZERIA,		},	// �X�{�~�[�@�@���͂Ȃ̂������@���[���A
	{MONSNO_KORAKKII,	ITEM_KOUUNNOOKOU,	MONSNO_RAKKII,		},	// �R���b�L�[�@�������񂨂����@���b�L�[
	{MONSNO_RIRIIN,		ITEM_KIYOMENOOKOU,	MONSNO_TIRIIN		},	// �����[���@�@����߂��������@�`���[��
};

// =================================================================
/**
 * @brief �A�C�e�������Ă���Ɛ��܂��|�P�������ς�鏈��
 * @param  no      :���܂��^�}�S�̃|�P�����i���o�[
 * @param  sodateya:��ĉ����[�N
 * @retval none
 */
// =================================================================
static u16 ItemEvolutionCheck( u16 no, SODATEYA_WORK *sodateya )
{
	u16 item1,item2,index,i;
	POKEMON_PASO_PARAM *ppp[2];
	
	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	OS_Printf("���̃|�P���� = %d\n", no);

	// ���܂��|�P�������A�C�e���ŕς�鐫���̂��̂��`�F�b�N
	for(i=0;i<ITEM_EVELUTION_MAX;i++){				
		if(no==ItemPokeEvoTable[i][0]){
			index = i;
			break;
		}
	}

	// �`�F�b�N����O�ꂽ��I��
	if(i==ITEM_EVELUTION_MAX){
		return no;
	}

	//�a���Ă���|�P�����̃A�C�e�����m�F
	item1 = PokePasoParaGet( ppp[0], ID_PARA_item, NULL);
	item2 = PokePasoParaGet( ppp[1], ID_PARA_item, NULL);

	// �e�̃A�C�e���������ɍ��v���Ă��Ȃ��ꍇ�͌��̃|�P�����ɖ߂�
	if( item1 != ItemPokeEvoTable[index][1] && item2 != ItemPokeEvoTable[index][1]){
		no = ItemPokeEvoTable[index][2];
	}

	OS_Printf("������������|�P���� = %d\n",no);

	return no;
}

#if 0
static u16 ItemEvolutionCheck( u16 no, SODATEYA_WORK *sodateya )
{
	u16 flag,item1,item2;
	POKEMON_PASO_PARAM *ppp[2];
	
	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	flag = 0;
	if( no != MONSNO_SOONANO && no != MONSNO_RURIRI){				//���܂��|�P�������\�[�i�m��������
		return no;														//�������I��
	}
	for(i=0;i<ITEM_EVELUTION_MAX;i++){				// ���܂��|�P�������A�C�e���ŕς��
		if(no==ItemPokeEvoTable[i][0]){				// �����̂��̂��`�F�b�N
			break;
		}
	}
	if(i==ITEM_EVELUTION_MAX){
		return no;
	}
		
	item1 = PokePasoParaGet( ppp[0], ID_PARA_item, NULL);	//�a���Ă���|�P�����̃A�C�e�����m�F
	item2 = PokePasoParaGet( ppp[1], ID_PARA_item, NULL);

	if( no == MONSNO_SOONANO){										//�\�[�i�m�ɂ̂񂫂̂��������Ȃ�������
		if(item1 != ITEM_NONKINOOKOU && item2 != ITEM_NONKINOOKOU){
			no = MONSNO_SOONANSU;									//�\�[�i���X��
		}
	}
	if( no == MONSNO_RURIRI){										//�������ɂ������̂��������Ȃ�������
		if(item1 != ITEM_USIONOOKOU && item2 != ITEM_USIONOOKOU){
			no = MONSNO_MARIRU;									//�}������
		}
	}

	return no;
}

#endif

//------------------------------------------------------------------
/**
 * �s�`���[�̓��ʏ���(�ł񂫂��܂������Ă���ƃ{���e�b�J�[���o����)
 *
 * @param   p			�|�P�����\���̂̃|�C���^
 * @param   sodateya	��Ă⃏�[�N
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static void PichuExtraCheck(POKEMON_PARAM *pp, SODATEYA_WORK *sodateya)
{
	int item1,item2;
	POKEMON_PASO_PARAM *ppp[2];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	item1 = PokePasoParaGet( ppp[0], ID_PARA_item,NULL );		//�e�|�P�����̃A�C�e�����m�F
	item2 = PokePasoParaGet( ppp[1], ID_PARA_item,NULL );

	if( item1==ITEM_DENKIDAMA || item2==ITEM_DENKIDAMA ){					//�ł񂫂��܂������Ă�����
		if(PokeWazaSet( pp, WAZANO_BORUTEKKAA )==NO_WAZA_SET){				//�u�{���e�b�J�[�v���o����
			PokeWazaOboeOshidashi( pp, WAZANO_BORUTEKKAA );				//�����o���Ăł��o����
		}
	}

}

#define SODATEYA_MOTHER	( 0 )
#define SODATEYA_FATHER  ( 1 )

// =================================================================
/**
 * @brief �^�}�S�ɂ͉�������邩
 * @param  sodateya		��ĉ����[�N
 * @param  oya[2]		oya[0]�ɕ�e,oya[1]�ɕ��e���i�[
 * @retval u16			�i�[�����|�P�����̊J��NO
 */
// =================================================================
static u16 PokemonBotaiCheck(SODATEYA_WORK *sodateya, u8 oya[])
{
	u16 oyamonsno[2],i,flag,monsno,tamagono,temp;
	POKEMON_PASO_PARAM *ppp[2];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	flag = 0;
	for(i=0;i<2;i++){
		if((oyamonsno[i]=PokePasoParaGet( ppp[i], ID_PARA_monsno,NULL))==METAMON_NO){	//���^�����`�F�b�N
			oya[SODATEYA_MOTHER] = i^1;
			oya[SODATEYA_FATHER] = i;
		}else if(PokePasoSexGet( ppp[i])==PARA_FEMALE){		//��e�̃|�P������T��
			oya[SODATEYA_MOTHER] = i;
			oya[SODATEYA_FATHER] = i^1;
		}
	}

	monsno   = oyamonsno[oya[SODATEYA_MOTHER]];				//��e�����ɂȂ�
	tamagono = PokeSearchChild(monsno);			//�q����{��

	if(tamagono==MONSNO_NIDORAN_F){				//�j�h�����v�Z
		if(SodateyaWork_GetEggFlag( sodateya ) & 0x8000){				//�^�}�S�����̍ŏ�ʃr�b�g�������Ă���@�j�h������
			tamagono = MONSNO_NIDORAN_M;
		}else{									//�t�̓j�h������
			tamagono = MONSNO_NIDORAN_F;
		}
	}
	if(tamagono == MONSNO_IRUMIIZE){			//�o���r�[�g�E�C���~�[�[�v�Z
		if(SodateyaWork_GetEggFlag( sodateya ) & 0x8000){
			tamagono = MONSNO_BARUBIITO;
		}else{
			tamagono = MONSNO_IRUMIIZE;
		}
	}
	
	if( tamagono == MONSNO_MANAFI){				// �^�}�S���琶�܂��ƃ}�i�t�B�̓G���t�B�ɂȂ�
		tamagono = MONSNO_ERUFI;
	}
	
	//���^�����̔��Α����e�Ƃ��Ďq������������A���ۂ́��␫�ʂȂ��̎��͂��̌�
	//���e�Ƃ��Ĉ���Ȃ��Ƃ����Ȃ����ɕ���𔽓]������
	if(oyamonsno[oya[SODATEYA_FATHER]]==METAMON_NO && PokePasoSexGet( ppp[oya[SODATEYA_MOTHER]] )!=PARA_FEMALE){
		temp   = oya[SODATEYA_FATHER];
		oya[SODATEYA_FATHER] = oya[SODATEYA_MOTHER];
		oya[SODATEYA_MOTHER] = temp;
	}
	
	return tamagono;

}




	

//==============================================================================
/**
 * @brief   �^�}�S�����(�C�x���g�E�ӂ����Ȃł����Ɨp�B�i�}�i�t�B�܂ށj
 *			��ĉ��ł͎g���܂���
 *
 * @param   pp			�|�C���^
 * @param   monsno		�J��NO
 * @param   eventflag	�C�x���g�t���O�𗧂Ă�Ȃ�P
 * @param   status		������MYSTATUS
 * @param   setid		poke_memo.h�Q�Ƃ̏�i�[���郁���̃^�C�v���w��
 * @param   placeid		��ɓ��ꂽ�ꏊ�������̓|�P���������W���[�Ȃǂ�ID
 *
 * @retval  none		
 */
//==============================================================================
void PokemonTamagoSet_forEvent(POKEMON_PARAM *pp, u16 monsno, u8 eventflag, MYSTATUS *status, int setid, int placeid )
{
	u8  level,event,flag;
	u16 ball;
	u8  egg_birth = PokePersonalParaGet( monsno, ID_PER_egg_birth );
	STRBUF *tamagoname;

	//���x��1�̃|�P����
#ifdef RARE_DEBUG
	PokeParaSet(pp,monsno,BIRTH_LEVEL,POW_RND,RND_SET,MyStatus_GetID(status),ID_NO_SET,0);	//���x��1�̃|�P����
#else
	PokeParaSet(pp,monsno,BIRTH_LEVEL,POW_RND,RND_NO_SET,0,ID_NO_SET,0);	
#endif

	level = 0;
	ball  = ITEM_MONSUTAABOORU;
	PokeParaPut( pp, ID_PARA_get_ball,  &ball );		//�擾�{�[���������X�^�[�{�[����
	PokeParaPut( pp, ID_PARA_friend,    &egg_birth );	//�z���܂ŃJ�E���^���Z�b�g
	PokeParaPut( pp, ID_PARA_get_level, &level );		//�^�}�S�͎擾�����x����0��

	//�^�}�S�����C�x���g�̎���
	if(eventflag){													
//		event = POS_EVENT_EGG;
		PokeParaPut( pp, ID_PARA_get_place, &eventflag );
	}
	flag = 1;
	PokeParaPut( pp, ID_PARA_tamago_flag, &flag );		//�^�}�S�t���O�Z�b�g

	tamagoname = MSGDAT_UTIL_GetMonsName( MONSNO_TAMAGO, HEAPID_FIELD );

	PokeParaPut( pp, ID_PARA_nickname_buf,  tamagoname);

	STRBUF_Delete(tamagoname);

	if(setid == TRMEMO_FUSHIGI_PLACESET){
	  // ���炩���ߐe�̖��O�A���ʁAID���R�s�[���Ă���
	  u32 oyaid = MyStatus_GetID( status );
	  u32 oyasex = MyStatus_GetMySex( status );
	  STRBUF *oyaname = MyStatus_CreateNameString( status, HEAPID_EVENT );
	  // �e����ύX����ꍇ
	  PokeParaPut(pp, ID_PARA_oyaname_buf, oyaname);
	  // �e��ID���R�s�[
	  PokeParaPut(pp, ID_PARA_id_no, &oyaid);
	  // �e�̐��ʂ��R�s�[
	  PokeParaPut(pp, ID_PARA_oyasex, &oyasex);
	  STRBUF_Delete(oyaname);
	}
	
	// �g���[�i�[������񏑂�����
	TrainerMemoSetPP( pp,status,setid,placeid, HEAPID_BASE_SYSTEM );
}


#define RARE_RANDOM_TRY_NUM	(4)
// =================================================================
/**
 * @brief �^�}�S�����
 * @param  poke			:�i�[����ꏊ�̃|�C���^
 * @param  monsno		:�|�P�����̔ԍ��i�J���i���o�[�j
 * @param  sodateya		:��ĉ����[�N
 * @retval  none
 */
// =================================================================
void PokemonTamagoSet(POKEMON_PARAM *pp, u16 monsno, SODATEYA_WORK *sodateya, u32 id, u8 form_no)
{
	u8  level;
	u16 ball;
	u32 personal_rnd;
	STRBUF *tamagoname;
	u8  egg_birth = PokePersonalParaGet( monsno, ID_PER_egg_birth );

	personal_rnd =  SodateyaWork_GetEggFlag( sodateya );	//�^�}�S�쐬�p�̌��������擾

	// ��������ĉ��ɗa���Ă���|�P���������A�̐��܂�₷����ԁi�O���̃|�P�������a���Ă���j�Ȃ�
	if(SodateyaWork_GetRareFlag(sodateya)){
		int i;

		OS_Printf("��ĉ����A���[�`������\n");
		// �������Ă闐�������A���B
		if(PokeRareGetPara( id, personal_rnd )==FALSE){
			// �c��̂S��̓��A���H
			for(i=0;i<RARE_RANDOM_TRY_NUM;i++){
				personal_rnd = gf_fix_rand( personal_rnd );
				if(PokeRareGetPara( id, personal_rnd )){
					OS_Printf("���A�m��\n");
					break;
				}
			}
		}else{
			OS_Printf("���A�m��\n");
		}
	}


#ifdef RARE_DEBUG
	PokeParaSet(pp,monsno,BIRTH_LEVEL,POW_RND,RND_SET,id,ID_NO_SET,0);	//���x��1�̃|�P����
#else
	PokeParaSet(pp,monsno,BIRTH_LEVEL,POW_RND,RND_SET,personal_rnd,ID_NO_SET,0);	//���x��1�̃|�P����
#endif
	level = 0;
	ball  = ITEM_MONSUTAABOORU;

	PokeParaPut( pp, ID_PARA_get_ball,  &ball );					//�擾�{�[���������X�^�[�{�[����
	PokeParaPut( pp, ID_PARA_friend,    &egg_birth );				//�z���܂ŃJ�E���^���Z�b�g
	PokeParaPut( pp, ID_PARA_get_level, &level );					//�^�}�S�͎擾�����x����0��
	PokeParaPut( pp, ID_PARA_form_no,   &form_no );					//�^�}�S�͎擾�����x����0��

	tamagoname = MSGDAT_UTIL_GetMonsName( MONSNO_TAMAGO, HEAPID_FIELD );
	PokeParaPut( pp, ID_PARA_nickname_buf,  tamagoname);
	STRBUF_Delete(tamagoname);
}



// =================================================================
/**
 * @brief	�^�}�S��Ⴄ=���܂��|�P���������
 * @param  sodateya
 * @retval  none
 */
// =================================================================
void PokeTamagoDel(SODATEYA_WORK *sodateya, POKEPARTY *party, MYSTATUS *my )
{
	u16 tamagono;
	u8 oya[2],flag;
	POKEMON_PARAM *poke = PokemonParam_AllocWork(HEAPID_FIELD);

	//��̂Ƃ���|�P������T��
	tamagono = PokemonBotaiCheck( sodateya, oya );					

	//�A�C�e���ŕ�̂��ς��|�P�����̏���
    //�i�������Ƃ��\�[�i�m�Ƃ��j
	tamagono = ItemEvolutionCheck( tamagono, sodateya );			
																	
	
	//�^�}�S���쐬
	{																
		u32 id = MyStatus_GetID(my);
		POKEMON_PASO_PARAM *ppp = SodateyaWork_GetPokePasoPointer( sodateya, oya[SODATEYA_MOTHER] );
		u8 form_no = PokePasoParaGet( ppp, ID_PARA_form_no, NULL );
		PokemonTamagoSet( poke, tamagono, sodateya, id, form_no );			
	}
	//�q����p�̗����Z�b�g
	PokeChildRandSet( poke,sodateya );								
	
	//�p���Z���Z�b�g
	KowazaSet( poke, 												
				SodateyaWork_GetPokePasoPointer( sodateya, oya[SODATEYA_FATHER] ),
				SodateyaWork_GetPokePasoPointer( sodateya, oya[SODATEYA_MOTHER] )
	);	

	// �g���[�i�[�����𖄂ߍ���
	TrainerMemoSetPP( poke,my,TRMEMO_SODATEYA_PLACESET,
							  PlaceName_IndexToParamNumber( PLACENAME_TYPE_GAME_EVENT, MAPNAME_SODATEYA ),
							  HEAPID_FIELD );

	//�s�`���[�̓��ʏ���
	if(tamagono==MONSNO_PITYUU){
		PichuExtraCheck( poke, sodateya );							
	}

	//�^�}�S�t���O�Z�b�g
	flag = 1;
	PokeParaPut( poke, ID_PARA_tamago_flag, &flag);					

	//�莝���ɉ�����
	PokeParty_Add( party, poke );									

	// ��ĉ����[�N����^�}�S�t���O����
	DelSodateyaTamagoSub( sodateya );								


	sys_FreeMemoryEz( poke );
}


// =================================================================
/**  �������}�O�}�̂�낢�A�������́A�ق̂��̂��炾�̃|�P������
 * 			�莝���ɂ���ꍇ�͂��܂��̛z��X�s�[�h���͂₭�Ȃ�
 *
 * @param  none
 * @retval u8	�^�}�S�z���J�E���g�������l
 */
// =================================================================
static int GetGrowthSpeed( POKEPARTY *party )
{
	u8 i;
	u8 spa;
	int total;

	total = PokeParty_GetPokeCount( party );
	for(i=0;i<total;i++){
		// �|�P�������^�}�S�łȂ�
		if( PokeParaGet( PokeParty_GetMemberPointer( party, i), ID_PARA_tamago_exist, NULL ) == 0 ){
			spa = PokeParaGet(PokeParty_GetMemberPointer( party, i), ID_PARA_speabino, NULL);	// ����\�͎擾
			if( (spa == TOKUSYU_MAGUMANOYOROI)||(spa == TOKUSYU_HONOONOKARADA) ){//�}�O�}�̂�낢�A�ق̂��̂��炾
				return 2;	//������2�{
			}
		}
	}
	return 1;//�������ς��Ȃ�
}


// =================================================================
/**
 * @brief �^�}�S�O���[�v���������̂����邩��r����
 * @param  p1	�^�}�S�O���[�v�ԍ��z��P�ip1[2])
 * @param  p2	�^�}�S�O���[�v�ԍ��z��Q(p2[2])
 * @retval  u8  �����O���[�v��������
 */
// =================================================================
static u8 TamagoGroupCheck(u16 *p1, u16 *p2)
{
	int i,w;
	
	for(i=0;i<2;i++){
		for(w=0;w<2;w++){
			if(p1[i]==p2[w]) return 1;
		}
	}
	return 0;
}


#define NO_TAMAGO_GROUP		(15)
#define METAMON_GROUP		(13)

// =================================================================
/**
 * @brief   �|�P�����Q�̂̑����i�����ł���m���j��Ԃ�
 * @param   ppp		�|�P�����Q�̕��� POKEMON_PASO_PARAM* �z��
 * @retval  u8		0�`70 �O���Ɛ�΂ɗ��͂ł��Ȃ�
 */
// =================================================================
static u8 CalcAffinity( POKEMON_PASO_PARAM** ppp )
{
	u16 group[2][2],monsno[2];
	u32	id[2],sex[2],rnd,i;

	for(i=0;i<2;i++){
		monsno[i] = PokePasoParaGet( ppp[i], ID_PARA_monsno,NULL);			//�����X�^�[�m�n
		id[i]     = PokePasoParaGet( ppp[i], ID_PARA_id_no,NULL);		//�h�c�@�m�n

		rnd    = PokePasoParaGet( ppp[i], ID_PARA_personal_rnd,NULL);		//������
		sex[i] = PokeSexGetMonsNo(monsno[i],rnd);							//���ʎ擾
		group[i][0] = PokePersonalParaGet(monsno[i], ID_PER_egg_group1);	//�^�}�S�O���[�v�P
		group[i][1] = PokePersonalParaGet(monsno[i], ID_PER_egg_group2);	//�^�}�S�O���[�v�Q

//		group[i][0] = PPD[monsno[i]].egg_group1;							
//		group[i][1] = PPD[monsno[i]].egg_group2;							
	}

	
	if(group[0][0]==NO_TAMAGO_GROUP||group[1][0]==NO_TAMAGO_GROUP){	//�����B�O���[�v�Ƃ͐��܂�Ȃ�
		return 0;													
	}
	if(group[0][0]==METAMON_GROUP && group[1][0]==METAMON_GROUP){	//���^�����ƃ��^��������͐��܂�Ȃ�
		return 0;
	}
	if(group[0][0]==METAMON_GROUP||group[1][0]==METAMON_GROUP){		//���^�������Е��ɂ���
		if(id[0]==id[1]) {
			return 20;								//�h�c�������Ȃ�Q�O��
		}else{
			return 50;								//�Ⴄ�Ȃ�T�O��
		}
	}
	if(sex[0]==sex[1]){
		return 0;									//�������ʂ͑����[��
	}
	if(sex[0]==PARA_UNK || sex[1]==PARA_UNK){				//���^�����`�F�b�N��͐��ʖ����͑����[��
		return 0;
	}
	
	if(TamagoGroupCheck(group[0],group[1])==0){
		return 0;			//�O���[�v��������瑊���[��
	}
	
	if(monsno[0]==monsno[1]){										//�|�P�����̎�ނ�����
		if(id[0]!=id[1]){
			return 70;								//�h�c���Ⴄ
		}else{
			return 50;
		}
	}else{															//�|�P�����̎�ނ��Ⴄ
		if(id[0]!=id[1]){
			return 50;								//�h�c���Ⴄ
		}else{
			return 20;
		}
	}
	return 0;
}
// =================================================================
/**
 * @brief �|�P�������Q�̂���Ƃ��ɑ�����Ԃ�
 * @param  sodateya	��ĉ����[�N
 * @retval  u8		0�`70 �O���Ɛ�΂ɗ��͂ł��Ȃ�
 */
// =================================================================
static  u8 SodateyaPokeAffinity( SODATEYA_WORK	*sodateya )
{
	POKEMON_PASO_PARAM *ppp[2];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	return CalcAffinity( ppp );
}

// �L�O���f�[�^(���{�����H�j
static const u16 GrowSpeedUpDay[]={
	112,	// �a
	214,	// �o�����^�C���f�[
	303,	// �ЂȍՂ�
	401,	// ���w��
	501,	// ���[�f�[
	611,	// �_�~�[
	707,	// ���[
	821,	// �_�~�[
	928,	// �c�o������
	1031,	// �n���E�B��
	1121,	// �q���r������
	1224,	// �N���X�}�X�C�u
	1225,	// �N���X�}�X
	
};


//------------------------------------------------------------------
/**
 * @brief   1�N�ɂP�Q�񂾂��^�}�S����̂�������������
 *
 * @param   fsys		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int GetEggCountSpeed( FIELDSYS_WORK *fsys )
{
	int month_day = EVTIME_GetMonth(fsys)*100+EVTIME_GetDay(fsys);
	int i;

	// ���ԏ��������ňᔽ��ԂɂȂ��Ă��Ȃ���
	if(EVTIME_IsPenaltyMode( fsys )){
		return 255;
	}	

	// ���ʂȓ��̓^�}�S�z���J�E���g������̂��Q�T������
	for(i=0;i<NELEMS(GrowSpeedUpDay);i++){
		if(GrowSpeedUpDay[i]==month_day){
			return 230;
		}
	}

	return 255;
}

// =================================================================
/**
 * @brief ��ĉ�����	�i����������ɏ�������܂��j
 * @param  none
 * @retval  u8   		�^�}�S���z�邩�H 0:������	1:�͂��i�^�}�S�f���J�n)
 */
// =================================================================
BOOL PokeSodateya( SODATEYA_WORK *sodateya, POKEPARTY *party, FIELDSYS_WORK *fsys )
{
	u32 i,work,flag,affinity,lottery;
	u32 walkcount=0,eggcount;
	int GrowthSpeed;
	POKEMON_PASO_PARAM *ppp[2];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	flag = 0;
	for(i=0;i<2;i++){			
		if(PokePasoParaGet( ppp[i], ID_PARA_poke_exist,NULL)!=0){	//�|�P�������a�����Ă�����
			SodateyaPoke_AddWalkCount(SodateyaWork_GetSodateyaPokePointer(sodateya,i),1);	//�����J�E���g++
			flag++;
		}
	}
	if(SodateyaWork_GetEggFlag( sodateya )==0 && flag==2){									//���܂�������������
		if((SodateyaPoke_GetWalkCount(SodateyaWork_GetSodateyaPokePointer(sodateya,1))&0xff)==0xff){				
			affinity = SodateyaPokeAffinity( sodateya );			//�����擾
			lottery  = gf_rand();
			lottery  = (lottery*100)/GF_RAND_MAX;
			if(affinity>lottery){
				PokeMakeTamago( sodateya );							//�^�}�S�����Z�b�g
			}
		}
	}


	
	eggcount = SodateyaWork_GetEggCount( sodateya );				
	SodateyaWork_SetEggCount(sodateya, ++eggcount);

	//���܂��z���`�F�b�N
	if(eggcount == GetEggCountSpeed(fsys)){	
		SodateyaWork_SetEggCount(sodateya, 0);
		GrowthSpeed = GetGrowthSpeed( party );
		for(i=0;i<PokeParty_GetPokeCount( party );i++){
			POKEMON_PARAM *pp = PokeParty_GetMemberPointer( party, i);
			if(PokeParaGet( pp, ID_PARA_tamago_flag,NULL)){			//���܂��������Ă��邩
				if(PokeParaGet( pp, ID_PARA_fusei_tamago_flag,NULL)){	//����̓_���^�}�S����Ȃ����H
					continue;											//��������
				}
				work=PokeParaGet( pp, ID_PARA_friend,NULL);
				if(work!=0){											//�z���E�F�C�g�����炷
					if (work>=GrowthSpeed){
						work-=GrowthSpeed;
					}else{
						work--;
					}
					//�f�N�������g�����Ȃ��x���Z�b�g���Ȃ���
					PokeParaPut( pp, ID_PARA_friend,(u8*)&work);
				}else{													//�^�}�S���z��
//					ScriptParameter0 = i;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

// =================================================================
/**
 * @brief	�Y�܂��|�P������T��
 * @param	party	�莝���|�P�����f�[�^�ւ̃|�C���^
 * @return	POKEMON_PARAM	���܂��^�}�S�ւ̃|�C���^
 *
 * �Y�܂��^�}�S�����݂��Ȃ��ꍇ�ANULL��Ԃ�
 */
// =================================================================
POKEMON_PARAM * SodateyaSearchHatchingEgg(POKEPARTY * party)
{
	int i;
	POKEMON_PARAM * pp;
	int num = PokeParty_GetPokeCount(party);
	for (i = 0; i < num; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (PokeParaGet(pp, ID_PARA_tamago_flag, NULL)
				&& PokeParaGet(pp, ID_PARA_friend, NULL) == 0) {
			//�^�}�S�ł��Ȃ��x�i�^�}�S�̏ꍇ�͛z���J�E���^�j���O�̏ꍇ
			return pp;
		}
	}
	return NULL;
}



// =================================================================
/**
 * @brief ��������̌��t�p�ɕ�����𖄂߂���
 * @param  sodateya
 * @retval  none
 */
// =================================================================
void SodateyaNameSet(SODATEYA_WORK *sodateya, WORDSET *wordset)
{
	POKEMON_PASO_PARAM *ppp[2];
	u16 strbuf[MONS_NAME_SIZE+EOM_SIZE];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	if(PokePasoParaGet( ppp[0], ID_PARA_monsno, NULL)!=0){			//��Ԗڂ̃|�P�����̖��O
		WORDSET_RegisterPokeNickName( wordset, 0, ppp[0] );
		WORDSET_RegisterPokeOyaName( wordset,  2, ppp[0] );			//�e�̖��O
	}

	if(PokePasoParaGet( ppp[1], ID_PARA_monsno, NULL)!=0){			//��Ԗڂ̃|�P�����̖��O
		WORDSET_RegisterPokeNickName( wordset, 1, ppp[1] );
	}
}
// =================================================================
/**
 * @brief  ��ĉ��ɗa���Ă���|�P������,���ʁA���x���擾
 * @param  sodateya
 * @retval  none
 */
// =================================================================
void SodateyaListNameSet(SODATEYA_WORK *sodateya,u32 buf_id,u32 buf2_id,u32 buf3_id,u8 no,WORDSET *wordset)
{
	SODATEYA_POKE      *sp;
	POKEMON_PASO_PARAM *ppp;
	u8 level,sex;
	u16 monsno;
	
	sp  = SodateyaWork_GetSodateyaPokePointer(sodateya, no);
	ppp = SodateyaWork_GetPokePasoPointer( sodateya, no);

	WORDSET_RegisterPokeNickName( wordset, buf_id, ppp );

	level = GetSinkaPokeLevel( ppp ,SodateyaPoke_GetWalkCount(sp));//�V�������x�����Z�o
	WORDSET_RegisterNumber( wordset, buf2_id, level, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	sex = PokePasoParaGet( ppp, ID_PARA_sex, NULL);

	if(sex != PARA_UNK){
		monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL);
		if(((monsno == MONSNO_NIDORAN_F)||(monsno == MONSNO_NIDORAN_M))
				&&(PokePasoParaGet( ppp, ID_PARA_nickname_flag, NULL) == 0)){	//�j�b�N�l�[�������Ă��Ȃ��j�h����
			sex = PARA_UNK;	//���ɐ��ʋL��������̂ŁA���������ɂ���
		}
	}
	WORDSET_RegisterPokeMonsSex( wordset, buf3_id, sex );
}

// =================================================================
/**
 * @brief �|�P�������X�g�őI�������|�P�����̖��O���Z�b�g����
 * @param  none
 * @retval  monsno��Ԃ�
 */
// =================================================================
u16	SodateyaAzukeName( POKEPARTY *party, int pos, WORDSET *wordset )
{
	POKEMON_PARAM *pp = PokeParty_GetMemberPointer( party, pos );

	WORDSET_RegisterPokeNickName( wordset, 0, PPPPointerGet( pp ) );

	return PokeParaGet( pp, ID_PARA_monsno, NULL);
}

// =================================================================
/**
 * @brief ��������ɘb���������Ƃ��Ƀ`�F�b�N
 * @param  none
 * @retval  u8	0:�Ȃ�	1:�^�}�S����	2:1�C�a���Ă�	3:2�C�a���Ă�
 */
// =================================================================
u8 SodateyaZiisannCheck( SODATEYA_WORK *sodateya )
{ 
	u8 num;
 	if(SodateyaWork_GetEggFlag( sodateya )){			//�^�}�S�`�F�b�N
		return 1;
	}
	if((num=PokeAzukeruCheck(  sodateya ))){		//�a���Ă邩�`�F�b�N
		return num+1;
	}
	return 0;											//����
}

//------------------------------------------------------------------
/**
 * �����Y�܂��m���i�S�����j���A�A���������l�i0�`3�j�ɕϊ�
 * ���m���� 0, 20, 50, 70% �̂S�p�^�[��������������
 *
 * @param   percentage		�m���i�S�����j
 *
 * @retval  u8       0:70%  1:50%  2:20%  3:0%
 */
//------------------------------------------------------------------
u8 GetAffinityLevel( u32 percentage )
{
	switch( percentage ){
	case 0: return 3;		//�ׂׂɂ�����ǂ邪�Ȃ�
	case 20: return 2;		//����قǂ悭�Ȃ����Ȃ�
	case 50: return 1;		//�܂��܂��̂悤����
	case 70: return 0;		//�Ƃ��Ă��悢�悤����
	}
	return 0;
}



// =================================================================
/**
 * @brief �Q�����̑����ɂ���Ă�������̕Ԃ����t���Z�b�g����
 * @param  none
 * @retval  u8
 */
// =================================================================
static int SodateyaPokeAffinityMsgSet( SODATEYA_WORK *sodateya )
{
	
	u8 work,result;
	work = SodateyaPokeAffinity( sodateya );		//��̂̑������擾
	result = GetAffinityLevel( work );

	//	PM_strcpy(MsgExpandBuffer,AffinityMsg[result]);	//�������Ƃ̕��͂��Z�b�g

	return result;
}

//------------------------------------------------------------------
/**
 * �C�ӂ̃|�P�����p�����[�^���痑�������x�����Z�o(�ȈՔ�)
 *
 * ����  : sodateya
 *
 * @retval  u32		3�i�����Œ�j�` 0�i�����ō��j
 */
//------------------------------------------------------------------
extern u32 SodateyaGetAffinity(SODATEYA_WORK *sodateya)
{
	u8 work,result;
	work = SodateyaPokeAffinity( sodateya );		//��̂̑������擾
	result = GetAffinityLevel( work );
	return result;
}


// =================================================================
/**
 * @brief ������̂Ȃ��ɗv�����鐫�ʋL���͂�������
 * @param  buf	�������镶����
 * @param  sex	�|�P�����̐���
 * @retval  static u8	1:������	0:�Ȃ������E�������͗���������
 */
// =================================================================
static int SexSymbolCheck(STRCODE *buf, int sex)
{
	u8 i,check[2];
	check[0] = check[1] = 0;
	i = 0;
	
	while(buf[i]!=EOM_){
		if(buf[i]==osu_ ){
			check[0]++;	//���L��������
		}
		if(buf[i]==mesu_){
			check[1]++;	//���L��������
		}
		i++;
	}
	
	if(sex==PARA_MALE){
		if(check[0]!=0 && check[1]==0){
			return 1;
		}
	}
	if(sex==PARA_FEMALE){
		if(check[1]!=0 && check[0]==0){
			return 1;
		}
	}
	
	return 0;
}


#if 0

// =================================================================
/**
 * @brief ������̍Ō�ɐ��ʋL����ǉ�����i������������̒��ɐ��ʋL�������ɂȂ������`�F�b�N����j
 * @param  buf	�ǋL���镶����
 * @param  sex	�|�P�����̐���
 * @retval  u8 * ������̃|�C���^
 */
// =================================================================
u8 *PM_SexStrcat(u8 *buf,u8 sex)
{
	if(sex==PARA_MALE){								//��
		if(SexSymbolCheck(buf,PARA_MALE)==0){		//���Ɏg���Ă��Ȃ���
			return PM_strcat(buf,sex_msg[0]);
		}
	}else if(sex==PARA_FEMALE){						//��
		if(SexSymbolCheck(buf,PARA_FEMALE)==0){		//���Ɏg���Ă��Ȃ���
			return PM_strcat(buf,sex_msg[1]);		
		}
	}
	return PM_strcat(buf,sex_msg[2]);				//���ʖ����E�������͊��ɐ��ʂ���
	
}



// =================================================================
/**
 * @brief ���ʂ̋L�������Ă�A�j�h�����΍��
 * @param  buf		:������o�b�t�@
 * @param  pokemon	:�|�P�����f�[�^�\����
 * @retval  u8 *		:������̍Ō�̃|�C���^
 */
// =================================================================
u8 *PPP_SexStrcat(u8 *buf, PokemonPasoParam *pokemon)
{
	u8 sex;
	//����
	sex=PokePasoSexGet(pokemon);						
	return PM_SexStrcat(buf, sex);
}

#endif

static void SodateyaMsgPrint( GF_BGL_BMPWIN *bmpwin, STRCODE *msg, int x, int y)
{
	MSG_PRINT_HEADER mph;

	mph.msg			= msg;
	mph.bmpwin	    = bmpwin;			//�\���E�C���h�EINDEX
	mph.fnt_index	= FONT_SYSTEM;		//�g�p�t�H���gINDEX
	mph.start_x		= x;				//�`��x�I�t�Z�b�g
	mph.start_y		= y;				//�`��x�I�t�Z�b�g
	mph.write_x		= x;				//�������l��start_x�Ɠ���
	mph.write_y		= y;				//�������l��start_y�Ɠ���
	mph.style		= 0;
//	msg_print_flag.cursor_type = CURSOR_FIELD;

	mph.space_x		= 0;				//�����Ԋu�w
	mph.space_y		= 1;				//�����Ԋu�x(�P�s�\��:���g�p)
	mph.f_col		= FBMP_COL_BLACK;	//�����F�i���o�[
	mph.b_col		= FBMP_COL_WHITE;	//�w�i�F�i���o�[
	mph.s_col		= FBMP_COL_BLK_SDW;	//�e�F�@�i���o�[

//	MSG_PrintExpand(&mph,MSG_NO_PUT,NULL);
	GF_STR_Print( &mph, MSG_NO_PUT, NULL );

}


static void MakeSodateNamePut(SODATEYA_WORK *sodateya, GF_BGL_BMPWIN *bmpwin, int no, int y)
{
	STRCODE buf[20];
	POKEMON_PASO_PARAM *ppp;
	
	ppp = SodateyaWork_GetPokePasoPointer( sodateya, no);
	
	PokePasoParaGet( ppp, ID_PARA_nickname, buf );
	
//	PPP_SexStrcat(buf,&sodateya->SodatePoke[no].Poke);

	SodateyaMsgPrint(bmpwin,buf,12,y);

}

//--------------------------------------------------------------------------
/**
 * 
 *
 * @param   sodateya		
 * @param   bmpid		
 * @param   no		
 * @param   y		
 *
 * @retval  none		
 *
 *
 */
//--------------------------------------------------------------------------
static void MakeSodateLevelPut(SODATEYA_WORK *sodateya,u8 bmpid,int no,int y, WORDSET *wordset)
{
	STRCODE buf[10],strtmp[5];
	u8 level;
	SODATEYA_POKE      *sp;
	POKEMON_PASO_PARAM *ppp;
	
	sp  = SodateyaWork_GetSodateyaPokePointer(sodateya, no);
	ppp = SodateyaWork_GetPokePasoPointer( sodateya, no);
	
//	strcpy(buf,level_msg);
	level = GetSinkaPokeLevel( ppp, SodateyaPoke_GetWalkCount(sp) );	
	WORDSET_RegisterNumber( wordset, 0, level, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
//	PM_NumMsgSet(strtmp, level, NUM_MODE_LEFT, 3);
//	PM_strcat(buf,strtmp);

//	SodateyaMsgPrint(bmpid,buf,12+11*7,y);
	
}


//--------------------------------------------------------------------------
/**
 * �������|�P�����I�����X�g�\���̃R�[���o�b�N�֐�
 *
 * @param   index	BitmapID
 * @param   param	���X�g�s�ԍ��i���̍s�̏��������̊֐��͂���j
 * @param   y		Bitmap�����w�肷��y���W
 *
 * @retval  none		
 *
 *
 */
//--------------------------------------------------------------------------
static void SodateyaSelectListPut( GF_BGL_BMPWIN *bmpwin, u32 param, u8 y )
{

	if(param < 2){				//�u��߂�v�ɂ͖��O�E���x���\���͕K�v�Ȃ�
//		MakeSodateNamePut(  &fld->SodateyaWork,index,param,y);		//	���O�\��
//		MakeSodateLevelPut( &fld->SodateyaWork,index,param,y);		//	���x���\��
	}
}




// =================================================================
/**
 * @brief �^�}�S���|�P�����ɖ߂�
 *         ���l���������^�}�S�͂h�c�ƌ������̂�����
 *         �^�}�S�t���O�𗎂Ƃ������ł͏����ł��Ȃ��̂�
 *         �K�v�ȃp�����[�^���i�[�����|�P�������\�z���Ȃ������Ƃɂ���
 *
 * @param  p	�|�P�����\����
 * @param  temp	�ޔ�p�̃|�P�����\����
 * @retval  none
 */
// =================================================================
static void Tamago2Pokemon( POKEMON_PARAM *p, int heap )
{
	//���l����^�}�S���������A�^�}�S����z�������|�P�����͑O�̐l�̂��̂ł͂Ȃ�
	//�z���������l�̂h�c�ɂȂ�B����ɑΉ����邽�߂Ɉ�U�Í�������Ă���
	//�f�[�^�����ׂēW�J���Ċi�[���Ȃ������Ƃɂ���

	u16 monsno;
	u16 waza[4];
	u8  pp[4];
	u32 personal_rnd, id;
	u8	rnds[6], pokerus;
	u8  i,country_code,get_cassette,mark,friend,event,form_no,oyasex;
	STRBUF *oyaname = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, heap );

	POKEMON_PARAM *temp = PokemonParam_AllocWork( heap );


	monsno = PokeParaGet(p,ID_PARA_monsno,NULL);					//�|�P�����i���o�[
	for(i=0;i<4;i++){
		waza[i] = PokeParaGet(p,ID_PARA_waza1+i,NULL);				//�Z�擾
		pp[i]   = PokeParaGet(p,ID_PARA_pp1+i,  NULL);				//�Zpp�擾
	}
	personal_rnd = PokeParaGet(p,ID_PARA_personal_rnd,NULL);		//�������擾
	for(i=0;i<6;i++){
		rnds[i] = PokeParaGet(p,ID_PARA_hp_rnd+i,NULL);				//�U�̗����擾
	}
	country_code = PokeParaGet(p,ID_PARA_country_code,NULL);		//���R�[�h
	get_cassette = PokeParaGet(p,ID_PARA_get_cassette,NULL);		//�ߊl�J�Z�b�g
	mark         = PokeParaGet(p,ID_PARA_mark,NULL);				//�}�[�N
	pokerus      = PokeParaGet(p,ID_PARA_pokerus,NULL);				//�|�P���X���
	event		 = PokeParaGet(p,ID_PARA_event_get_flag,NULL);		//�C�x���g�z�z���H
	PokeParaGet(p, ID_PARA_oyaname_buf, oyaname);
	oyasex       = PokeParaGet(p,ID_PARA_oyasex,NULL);
	id           = PokeParaGet(p,ID_PARA_id_no,NULL);
	form_no      = PokeParaGet(p,ID_PARA_form_no,NULL);


	// �����W���[�}�i�t�B��p����(�����W���[�����������}�i�t�B�̓��A�ɂȂ�Ȃ��j
	if(monsno==MONSNO_MANAFI){
		int getplace = PokeParaGet( p, ID_PARA_get_place, NULL);
		OS_Printf("�}�i�t�B�[�z������\n");
		if (getplace == PlaceName_IndexToParamNumber( PLACENAME_TYPE_EXT_EVENT, MAPNAME_RENJA )){
			// ���A����Ȃ��Ȃ�܂ŗ������܂킷
			while(PokeRareGetPara( id, personal_rnd)){
				personal_rnd = gf_fix_rand( personal_rnd );
			}
		}
	
	}
	//��������|�P�����쐬

	PokeParaSet(temp,monsno,BIRTH_LEVEL,POW_RND,RND_SET,personal_rnd,ID_NO_SET,0);	//���x���T�̃|�P����

	for(i=0;i<4;i++){
		PokeParaPut(temp,ID_PARA_waza1+i,&(waza[i]));		//�Z�i�[
		PokeParaPut(temp,ID_PARA_pp1+i,  &(pp[i]));			//�Zpp�i�[
	}
	for(i=0;i<6;i++){
		PokeParaPut(temp, ID_PARA_hp_rnd+i,&(rnds[i]));		//�U�̗����i�[
	}
	PokeParaPut(temp,ID_PARA_country_code,&country_code);	//���R�[�h
    PokeParaPut(temp,ID_PARA_get_cassette,&get_cassette);	//�ߊl�J�Z�b�g
	PokeParaPut(temp,ID_PARA_mark,&mark);					//�}�[�N
	friend = HUKA_FIRST_NATUKIDO;							//�^�}�S���炤�܂ꂽ�ꍇ�Ȃ��x��120���Z�b�g����
	PokeParaPut(temp,ID_PARA_friend,&friend);				//�Ȃ��x��120��
	PokeParaPut(temp,ID_PARA_pokerus,&pokerus);				//�|�P���X��Ԃ��Z�b�g
	PokeParaPut(temp,ID_PARA_event_get_flag,&event);		//�C�x���g�z�z�t���O�Z�b�g
	PokeParaPut(temp,ID_PARA_oyaname_buf, oyaname);			// �e��
	PokeParaPut(temp,ID_PARA_oyasex, &oyasex);			// �e�̐���
	PokeParaPut(temp,ID_PARA_id_no,       &id);
	PokeParaPut(temp,ID_PARA_form_no,     &form_no);
	
	///< �g���[�i�[�����ŃL�[�ɂ��Ă���f�[�^�̎󂯓n��
	{
		u16 id;
		u8  y, m, d;
		
		id = PokeParaGet(p, ID_PARA_get_place, NULL);
		y  = PokeParaGet(p, ID_PARA_get_year, NULL);
		m  = PokeParaGet(p, ID_PARA_get_month, NULL);
		d  = PokeParaGet(p, ID_PARA_get_day, NULL);
		PokeParaPut(temp, ID_PARA_get_place, &id);
		PokeParaPut(temp, ID_PARA_get_year,  &y);
		PokeParaPut(temp, ID_PARA_get_month, &m);
		PokeParaPut(temp, ID_PARA_get_day,   &d);
			
		id = PokeParaGet(p, ID_PARA_birth_place, NULL);
		y  = PokeParaGet(p, ID_PARA_birth_year, NULL);
		m  = PokeParaGet(p, ID_PARA_birth_month, NULL);
		d  = PokeParaGet(p, ID_PARA_birth_day, NULL);
		PokeParaPut(temp, ID_PARA_birth_place, &id);
		PokeParaPut(temp, ID_PARA_birth_year,  &y);
		PokeParaPut(temp, ID_PARA_birth_month, &m);
		PokeParaPut(temp, ID_PARA_birth_day,   &d);		
	}

	PokeCopyPPtoPP( temp, p );								//�f�[�^���R�s�[

	STRBUF_Delete(oyaname);
	sys_FreeMemoryEz( temp );
}


// =================================================================
/**
 * @brief �^�}�S���|�P�����ɂ�����
 * @param  no = �莝���m�n
 * @retval  none
 */
// =================================================================
void SodateTamagoHuka( POKEMON_PARAM *pp, int heap )
{
	u8 	natsuki, nickname_flag;
	u8	ball, level;
	u16	monsno;
	STRCODE	namebuf[ 11 ];
	
	natsuki       = 70;
	nickname_flag = 0;
	ball          = ITEM_MONSUTAABOORU;
	level         = 0;

	Tamago2Pokemon( pp, heap );				//�^�}�S���|�P�����ɖ߂�

	PokeParaPut( pp, ID_PARA_tamago_flag, &natsuki);			//�Ȃ��x�������l��

	monsno  = PokeParaGet( pp, ID_PARA_monsno, NULL);					//�|�P�����m�n���擾

	MSGDAT_MonsNameGet(monsno,HEAPID_BASE_SYSTEM,namebuf);					// �f�t�H���g�l�[���擾
	PokeParaPut( pp, ID_PARA_nickname,	namebuf );
	PokeParaPut( pp, ID_PARA_nickname_flag, &nickname_flag );
	
	PokeParaPut( pp, ID_PARA_get_ball,  &ball);							//�擾�{�[���������X�^�[�{�[����
	PokeParaPut( pp, ID_PARA_get_level, &level);						//�^�}�S�͎擾�����x����0��

	PokeParaCalc( pp );
}

#if 0
//------------------------------------------------------------------
/**
 * ��ĉ����[���������̕��ƈႤ���[���ɕς���Ă��Ȃ����`�F�b�N
 *
 * @param   sodateya	��ĉ��\����
 * @param   no			���[���{�b�N�XNO(0-1)
 *
 * @retval  u8			0:�ς���ĂȂ�	1:�ς���Ă���
 */
//------------------------------------------------------------------
static u8 SodateyaMailCheckSub(SODATEYA_WORK *sodateya, u8 no, WORDSET *wordset, SAVEDATA *sv )
{
	STRCODE pokename[30], myname[32];
	STRBUF *oyaname, *fpokename;
	SODATEYA_POKE      *sp    = SodateyaWork_GetSodateyaPokePointer( sodateya, no );
	POKEMON_PASO_PARAM *ppp   = SodateyaPoke_GetPokePasoPointer( sp );
	SIO_MAIL_DATA      *smail = SodateyaPoke_GetSioMailPointer( sp );
	MAIL_DATA          *mail  = SodateyaMail_GetMailPointer( smail );
	MYSTATUS		   *my    = SaveData_GetMyStatus( sv );

//	PM_stcpy(&sodateya->SodatePoke[no].Poke,pokename);	
	PokePasoParaGet( ppp, ID_PARA_nickname, pokename );						//�|�P�����̖��O�擾
	MyStatus_SetMyName( my, myname );

	if( mail->design==NON_ITEM){
		return 0;	//���[���������Ȃ�I��
	}
	
	if((PM_strcmp(pokename, SodateyaMail_GetNamePointer( smail, SIOMAIL_FLAG_POKE ))!=0)||	//�|�P�����̖��O�����[���ƈႤ��
	(PM_strcmp( myname, SodateyaMail_GetNamePointer( smail, SIOMAIL_FLAG_OYA ))!=0)){		//���[���������e�̖��O�Ǝ������Ⴄ�Ȃ�
//		PM_strcpy(StrTempBuffer0,pokename);								
//		PM_strcpy(StrTempBuffer1,sodateya->SodatePoke[no].Mail.oyaname);		
//		PM_strcpy(StrTempBuffer2,sodateya->SodatePoke[no].Mail.pokename);		
		WORDSET_RegisterPokeNickName( wordset, 0, ppp );
		oyaname = STRBUF_Create(HEAPID_FIELD, 20);
		fpokename = STRBUF_Create(HEAPID_FIELD, 20);
		STRBUF_SetStringCodeOrderLength( oyaname, SodateyaMail_GetNamePointer( smail, SIOMAIL_FLAG_OYA ), 10 );
		STRBUF_SetStringCodeOrderLength( fpokename, SodateyaMail_GetNamePointer( smail, SIOMAIL_FLAG_POKE ), 10 );

		STRBUF_Delete(oyaname);
		STRBUF_Delete(fpokename);

		return 1;
	}
	return 0;
}

#endif


//======================================================================================
//======================================================================================

//------------------------------------------------------------------
/**
 * �C�ӂ̃|�P�����p�����[�^���痑�������x�����Z�o
 *
 * @param   ppp		�|�P�����Q�̕��� POKEMON_PASO_PARAM* �^�z��
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 Sodateya_GetAffinityLevel( POKEMON_PASO_PARAM** ppp )
{
	return GetAffinityLevel( CalcAffinity(ppp) );
}


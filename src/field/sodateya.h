// =================================================================
//
//	sodateya.h
//
//	��ĉ��p��`
//
//
// =================================================================

#ifndef __SODATEYA_H__
#define __SODATEYA_H__

#include "savedata\sodateyadata.h"
#include "poketool\pokeparty.h"
#include "system\wordset.h"
// =================================================================
// �萔��`
// =================================================================


// =================================================================
// �\���̒�`
// =================================================================
/* ��ĉ��� (���R�[�h�R�[�i�[�p)*/
typedef struct{
//	SIO_MAIL_DATA 	SioMail[SODATEYA_POKE_MAX];		//��ĉ��ɒu����郁�[���f�[�^
	u8				SioMail[100];
	u32				PokeNum;						//��ĉ��ɂ���|�P�����̐�
	u16				PokeFlag[SODATEYA_POKE_MAX];	//�|�P�������A�C�e���������Ă��邩�ǂ����̃t���O
}SODATEYA_MAIL;

// =================================================================
// PokeAzukeruCheck
// �T�v  : �a���Ă���|�P�����̐���Ԃ�
// ����  : none
// �߂�l: u8
// =================================================================
extern u8 PokeAzukeruCheck(SODATEYA_WORK *sodateya);

// =================================================================
// PokeAzukeruCheckGet
// �T�v  : �a������Ȃ�󂢂Ă�ԍ���Ԃ�
// ����  : none
// �߂�l: s8	0,1=�󂢂Ă�ԍ�	-1=����
// =================================================================
extern int PokeAzukeruCheckGet(SODATEYA_WORK *sodateya);

extern void PokeTamagoDel(SODATEYA_WORK *sodateya, POKEPARTY *party, MYSTATUS *my );


// =================================================================
// PokeSodateSet
// �T�v  : �|�P������a����
// ����  : p
// �߂�l: none
// =================================================================
extern void PokeSodateSet(POKEPARTY *party, int pos, SODATEYA_WORK *sodateya, SAVEDATA *sv);


// =================================================================
// PokeSodateyaInit
// �T�v  : ��ĉ����[�N������
// ����  : none
// �߂�l: none
// =================================================================
extern void PokeSodateyaInit(SODATEYA_WORK *sodateya);

// =================================================================
// PokeMakeTamago
// �T�v  : �^�}�S�����
// ����  : sodateya
// �߂�l: none
// =================================================================
extern void PokeMakeTamago(SODATEYA_WORK *sodateya);


// =================================================================
// u8	PokeSodateya
// �T�v  : ����������Ɍo���l�����Z
// ����  : none
// �߂�l: BOOL  TRUE�̎��̓^�}�S���z������
// =================================================================
extern BOOL	PokeSodateya( SODATEYA_WORK *sodateya, POKEPARTY *party, FIELDSYS_WORK *fsys );

// =================================================================
// POKEMON_PARAM * SodateyaSearchHatchingEgg
// �T�v�@�F���܂��^�}�S�ւ̃|�C���^���擾
// �����@�Fparty	�莝���ւ̃|�C���^
// �߂�l�FPOKEMON_PARAM�ւ̃|�C���^�A���݂��Ȃ��ꍇNULL��Ԃ�
// =================================================================
extern POKEMON_PARAM * SodateyaSearchHatchingEgg(POKEPARTY * party);

// =================================================================
// PokeTamagoSet
// �T�v  : �^�}�S���Z�b�g����
// ����  : none
// �߂�l: none
// =================================================================
extern void PokeTamagoSet();

// =================================================================
// void	SodateyaPlusWalk
// �T�v  : �w��������������Ƃɂ���
// ����  : none
// �߂�l: none
// =================================================================
extern void	SodateyaPlusWalk( SODATEYA_WORK *sodateya, u16 count);

// =================================================================
// SodateTamagoHuka
// �T�v  : �^�}�S���|�P�����ɂ�����
// ����  : none(������ScriptParameter0�Ɏ莝���̔ԍ��������Ă�)
// �߂�l: none
// =================================================================
extern void SodateTamagoHuka( POKEMON_PARAM *pp, int heap );


// =================================================================
// SioMailDataInit
// �T�v  : ��ĉ����[�����[�N��������
// ����  : smd
// �߂�l: none
// =================================================================
extern void SioMailDataInit(SIO_MAIL_DATA	*smd);


// =================================================================
// TamagoFlagsSet
// �T�v  : �^�}�S�����
// ����  : poke			:�i�[����ꏊ�̃|�C���^
//       : monsno		:�|�P�����̔ԍ��i�J���i���o�[�j
//		 : flag			:�Q�[�����C�x���g�ł���������H�i1:�͂�  0:��ĉ��j
// �߂�l: none
// =================================================================
extern void PokemonTamagoSet(POKEMON_PARAM *pp, u16 monsno, SODATEYA_WORK *sodateya, u32 id, u8 form_no);

	
// =================================================================
// TamagoFlagsSet_forEvent
// �T�v  : �^�}�S�����(�C�x���g�p�j
// ����  : poke			:�i�[����ꏊ�̃|�C���^
//       : monsno		:�|�P�����̔ԍ��i�J���i���o�[�j
//		 : flag			:�Q�[�����C�x���g�ł���������H�i1:�͂�  0:��ĉ��j
// �߂�l: none
// =================================================================
void PokemonTamagoSet_forEvent(POKEMON_PARAM *pp, u16 monsno, u8 eventflag, MYSTATUS *status, int setid, int placeid );


// =================================================================
// PokeAzukeInfoCheck
// �T�v  : ��ĉ��ɗa���Ă���|�P�����̃A�C�e���󋵂𒲂ׂ�
// ����  : sodateya
//       : mailinfo
// �߂�l: none
// =================================================================
extern void PokeAzukeInfoCheck(SODATEYA_WORK *sodateya, SODATEYA_MAIL *mailinfo);

// =================================================================
// SodateyaZiisannCheck
// �T�v  : ��ĉ���������̏�Ԏ擾
// ����  : sodateya
// �߂�l: u8	0:�Ȃ�	1:�^�}�S����	2:1�C�a���Ă�	3:2�C�a���Ă�
// =================================================================
extern u8 SodateyaZiisannCheck( SODATEYA_WORK *sodateya );

// =================================================================
// SodateyaNameSet
// �T�v  : ��ĉ��ɗa���Ă���|�P�������擾
// ����  : sodateya
// �߂�l: none
// =================================================================
extern void SodateyaNameSet(SODATEYA_WORK *sodateya, WORDSET *wordset);

// =================================================================
// SodateyaListNameSet
// �T�v  : ��ĉ��ɗa���Ă���|�P������,���ʁA���x���擾
// ����  : sodateya
// �߂�l: none
// =================================================================
extern void SodateyaListNameSet(SODATEYA_WORK *sodateya,u32 buf_id,u32 buf2_id,u32 buf3_id,u8 no,WORDSET *wordset);

// =================================================================
/**
 * @brief ��ĂĂ�|�P�����̖��O�ƃ��x�����̕�������Z�b�g
 * @param  sp ��ĉ����[�N
 * @retval  none
 */
// =================================================================
extern u8 SodatePokeLevelSet( SODATEYA_WORK *sodateya, int pos, WORDSET *wordset );

extern u16 PokeHikitoriSub(POKEPARTY *party, WORDSET *wordset, SODATEYA_WORK *sodateya,u8 no);
extern int GetSinkaPokeLevel(POKEMON_PASO_PARAM *ppp, u32 walk);
extern int GetSodatePokeLevel(SODATEYA_POKE *sp);
extern int GetSodatePokeLevelDirect(SODATEYA_POKE *sp);
extern u8  SodatePokeLevelSetSub(SODATEYA_POKE *sp, WORDSET *wordset);
extern int PokehikitoriRyoukinOne(SODATEYA_POKE *sp, WORDSET *wordset );


//------------------------------------------------------------------
/**
 * �C�ӂ̃|�P�����p�����[�^���痑�������x�����Z�o
 *
 * @param   ppp		�|�P�����Q�̕��� POKEMON_PASO_PARAM* �^�z��
 *
 * @retval  u32		3�i�����Œ�j�` 0�i�����ō��j
 */
//------------------------------------------------------------------
extern u32 Sodateya_GetAffinityLevel( POKEMON_PASO_PARAM** ppp );

//------------------------------------------------------------------
/**
 * �C�ӂ̃|�P�����p�����[�^���痑�������x�����Z�o(�ȈՔ�)
 *
 * ����  : sodateya
 *
 * @retval  u32		3�i�����Œ�j�` 0�i�����ō��j
 */
//------------------------------------------------------------------
extern u32 SodateyaGetAffinity(SODATEYA_WORK *sodateya); 

//------------------------------------------------------------------
/**
 * �C�ӂ̃|�P�����p�����[�^���痑�������x�����Z�o
 *
 * @param   percentage		�m���i�S�����j
 *
 * @retval  u8		3�i�����Œ�j�` 0�i�����ō��j
 */
//------------------------------------------------------------------
extern u8 GetAffinityLevel( u32 percentage );

// =================================================================
/**
 * @brief PokeHikitoriRyoukin�̃T�u���[�`��
 * @param  none
 * @retval  u16 ��Ă�����
 */
// =================================================================
extern int PokeHikitoriRyoukinSub(SODATEYA_WORK *sodateya, u8 no, WORDSET *wordset);

// =================================================================
/**
 * @brief �|�P�������X�g�őI�������|�P�����̖��O���Z�b�g����
 * @param  none
 * @retval  monsno��Ԃ�
 */
// =================================================================
extern u16	SodateyaAzukeName( POKEPARTY *party, int pos, WORDSET *wordset );

// =================================================================
/**
 * @brief �^�}�S������
 * @param  none
 * @retval  none
 */
// =================================================================
extern void DelSodateyaTamagoSub(SODATEYA_WORK *sodateya);

#endif 

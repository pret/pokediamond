#ifndef _ENCOUNT_DAT_H_
#define _ENCOUNT_DAT_H_

//#include "enc_def.h"
//�G���J�E���g�f�[�^�R���o�[�^�ł��܂��W�J�ł��Ȃ��Ȃ��Ă���̂�
//�C�����邽�߂�enc_def.h�𒼐ړW�J

#define ENC_MONS_NUM_NORMAL		(12)
#define ENC_MONS_NUM_GENERATE	(2)
#define ENC_MONS_NUM_NOON		(2)
#define ENC_MONS_NUM_NIGHT		(2)
#define ENC_MONS_NUM_SWAY_GRASS	(4)
#define ENC_FORM_PROB_NUM		(5)
#define ENC_MONS_NUM_AGB		(2)

#define ENC_MONS_NUM_SEA		(5)
#define ENC_MONS_NUM_ROCK		(5)
#define ENC_MONS_NUM_FISH		(5)	

typedef struct ENC_MONSTER_DAT_tag
{
	char Level;
	int MonsterNo;
}GROUND_ENC_MONSTER_DAT;

typedef struct NON_GROUND_ENC_MONSTER_DAT_tag
{
	char MaxLevel;
	char MinLevel;
	int MonsterNo;
}NON_GROUND_ENC_MONSTER_DAT;

typedef struct ENCOUNT_DATA_tag
{
	//int PlaceCode;<<�폜
	int EncProbGround;
	GROUND_ENC_MONSTER_DAT NormalEnc[ENC_MONS_NUM_NORMAL];
	int GenerateEnc[ENC_MONS_NUM_GENERATE];
	int NoonEnc[ENC_MONS_NUM_NOON];
	int NightEnc[ENC_MONS_NUM_NIGHT];
	int SwayEnc[ENC_MONS_NUM_SWAY_GRASS];
	int FormProb[ENC_FORM_PROB_NUM];		//�C���f�b�N�X�@0:�V�[�E�V�@1�F�V�[�h���S�@2�`4�F���g�p
	int AnnoonTable;						//�A���m�[���o���e�[�u���i0�F�A���m�[���퓬�����@1�`8�F�e�[�u���ԍ��j
	int RubyEnc[ENC_MONS_NUM_AGB];
	int SapphireEnc[ENC_MONS_NUM_AGB];
	int EmeraldEnc[ENC_MONS_NUM_AGB];
	int FireEnc[ENC_MONS_NUM_AGB];
	int LeafEnc[ENC_MONS_NUM_AGB];
	int EncProbSea;
	NON_GROUND_ENC_MONSTER_DAT	EncSea[ENC_MONS_NUM_SEA];
	int EncProbRock;
	NON_GROUND_ENC_MONSTER_DAT	EncRock[ENC_MONS_NUM_ROCK];
	int EncProbFish1;
	NON_GROUND_ENC_MONSTER_DAT EncFish1[ENC_MONS_NUM_FISH];
	int EncProbFish2;
	NON_GROUND_ENC_MONSTER_DAT EncFish2[ENC_MONS_NUM_FISH];
	int EncProbFish3;
	NON_GROUND_ENC_MONSTER_DAT EncFish3[ENC_MONS_NUM_FISH];
}ENCOUNT_DATA;

#endif	//_ENCOUNT_DAT_H_

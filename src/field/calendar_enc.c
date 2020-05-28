//============================================================================================
/**
 * @file	calendar_enc.c
 * @brief	�J�����_�[����݂̃G���J�E���g
 * @author	Nozomu Saito
 * @date	2006.05.16
 */
//============================================================================================
#include "common.h"
#include "system/pm_rtc.h"

#include "calendar_enc.h"

#define DAY_DATA(day,prob_no)		( (day<<8) | (prob_no&0xff) )
#define GET_DAY(data)				( (data>>8)&0xff )
#define GET_PROB_NO(data)			( data&0xff )

enum {
	JAN_DAT_MAX = 4,
	FEB_DAT_MAX = 4,
	MAR_DAT_MAX = 4,
	APR_DAT_MAX = 3,
	MAY_DAT_MAX = 6,
	JUN_DAT_MAX = 2,
	JUL_DAT_MAX = 4,
	AUG_DAT_MAX = 7,
	SEP_DAT_MAX = 4,
	OCT_DAT_MAX = 4,
	NOV_DAT_MAX = 5,
	DEC_DAT_MAX = 7,
};

#define MONTH_NUM	(12)


typedef u16 CAL_ENC_DAY_DATA;

//1��
static const CAL_ENC_DAY_DATA JanData[JAN_DAT_MAX] = {
	DAY_DATA( 1,3),			//���U		New Year's Day�i�k�āE�C�M�E�C�^�E�X�E�t�E�h�j
	DAY_DATA( 6,2),			//			������̏j���i�C�^�j�E�匰�߁i�X�j�E�O�������i�h�j
	DAY_DATA(11,2),			//���J��
	DAY_DATA(12,4)			//�o�����^�C���f�[	Valentine's Day�i�k�āj
};

//2��
static const CAL_ENC_DAY_DATA FebData[FEB_DAT_MAX] = {
	DAY_DATA( 3,2),			//�ߕ�
	DAY_DATA(11,2),			//�����L�O��
	DAY_DATA(12,2),			//			�����J�[���̒a�����i�k�āj
	DAY_DATA(14,0)			//
};

//3��
static const CAL_ENC_DAY_DATA MarData[MAR_DAT_MAX] = {
	DAY_DATA( 3,2),			//�ЂȍՂ�
	DAY_DATA(17,2),			//			�Z���g�p�g���b�N�̓��i�k�āj
	DAY_DATA(21,3),			//�t���̓�
	DAY_DATA(25,2)			//			�����j���i�X�j
};

//4��
static const CAL_ENC_DAY_DATA AprData[APR_DAT_MAX] = {
	DAY_DATA( 1,2),			//���w��
	DAY_DATA(25,2),			//			�C�^���A����L�O���i�C�^�j
	DAY_DATA(29,2),			//�݂ǂ�̓�
};

//5��
static const CAL_ENC_DAY_DATA MayData[MAY_DAT_MAX] = {
	DAY_DATA( 1,0),			//�l�x		���[�f�[(�܌���)�i�k�āE�C�M�E�C�^�E�X�E�t�E�h�j
	DAY_DATA( 3,2),			//���@�L�O��
	DAY_DATA( 4,0),			//�����̋x��
	DAY_DATA( 5,2),			//���ǂ��̓�
	DAY_DATA( 8,2),			//			��񎟑��I��L�O���i�t�j
	DAY_DATA(29,2),			//			�z�C�b�g�}���f�[�i�C�M�j
};

//6��
static const CAL_ENC_DAY_DATA JunData[JUN_DAT_MAX] = {
	DAY_DATA( 2,2),			//			���a�������L�O���i�C�^�j
	DAY_DATA(21,2),			//DUMMY
};

//7��
static const CAL_ENC_DAY_DATA JulData[JUL_DAT_MAX] = {
	DAY_DATA( 4,2),			//			�Ɨ��L�O���i�k�āj
	DAY_DATA( 7,4),			//���[
	DAY_DATA(14,2),			//			�v���L�O��(�p����)�i�t�j
	DAY_DATA(24,2)			//DUMMY
};

//8��
static const CAL_ENC_DAY_DATA AugData[AUG_DAT_MAX] = {
	DAY_DATA( 6,3),			//�L������
	DAY_DATA( 9,3),			//���茴��
	DAY_DATA(13,1),			//���~
	DAY_DATA(14,1),			//���~
	DAY_DATA(15,2),			//���~�E�I��L�O��	����폸�V�Ձi�C�^�E�X�j�E���ꏸ�Ձi�t�j�E�}���A���V�Ձi�h�j
	DAY_DATA(16,1),			//���~
	DAY_DATA(28,2),			//			�T�}�[�o���N�z���f�[�i�C�M�j
};

//9��
static const CAL_ENC_DAY_DATA SepData[SEP_DAT_MAX] = {
	DAY_DATA(11,3),			//			911�e��
	DAY_DATA(15,2),			//�\�ܖ�
	DAY_DATA(20,2),			//
	DAY_DATA(23,3)			//�H���̓�
};

//10��
static const CAL_ENC_DAY_DATA OctData[OCT_DAT_MAX] = {
	DAY_DATA( 3,2),			//			�h�C�c����̓��i�h�j
	DAY_DATA(12,2),			//			�C�X�p�j�A�f�[�i�X�j
	DAY_DATA(30,2),			//
	DAY_DATA(31,0)			//			�n���E�B�[���i�k�āj�E�@�����v�L�O���i�h�j
};

//11��
static const CAL_ENC_DAY_DATA NovData[NOV_DAT_MAX] = {
	DAY_DATA( 1,2),			//			�����l�̓��i�C�^�E�X�y�E�h�j�E�����l�̏j���i�t�j
	DAY_DATA( 3,1),			//�����̓�
	DAY_DATA(11,2),			//			�ޖ��R�l�̓��i�k�āj�E��ꎟ���x��L�O���i�t�j
	DAY_DATA(16,2),			//			�܍߂̓��i�h�j
	DAY_DATA(23,0)			//�ΘJ���ӂ̓�
};

//12��
static const CAL_ENC_DAY_DATA DecData[DEC_DAT_MAX] = {
	DAY_DATA( 6,2),			//			���@�̓��i�X�j
	DAY_DATA( 8,2),			//			���ꖳ���߂̌�h��̓��i�C�^�j�E�����ق̓��i�X�j�E���ꖳ�C��ٍՁi�h�j
	DAY_DATA(23,2),			//�V�c�a����
	DAY_DATA(24,2),			//�N���X�}�X�C�u	�N���X�}�X�i�k�āE�C�M�E�C�^�E�X�E�t�E�h�j
	DAY_DATA(25,1),			//�N���X�}�X	�N���X�}�X�i�k�āE�C�M�E�C�^�E�X�E�t�E�h�j
	DAY_DATA(26,0),			//			�{�N�V���O�f�[�i�C�M�j�E���X�e�[�t�@�m�̓��i�C�^�j
	DAY_DATA(31,1),			//��A��
};

typedef struct CAL_ENC_MONTH_DATA_tag{
	int Num;
	const CAL_ENC_DAY_DATA *DayData;
}CAL_ENC_MONTH_DATA;


static const CAL_ENC_MONTH_DATA CalEncMonthData[MONTH_NUM] = {
	{JAN_DAT_MAX,JanData},{FEB_DAT_MAX,FebData},{MAR_DAT_MAX,MarData},
	{APR_DAT_MAX,AprData},{MAY_DAT_MAX,MayData},{JUN_DAT_MAX,JunData},
	{JUL_DAT_MAX,JulData},{AUG_DAT_MAX,AugData},{SEP_DAT_MAX,SepData},
	{OCT_DAT_MAX,OctData},{NOV_DAT_MAX,NovData},{DEC_DAT_MAX,DecData}
};

static const int ProbTbl[] = 
{
	0,-5,5,-10,10
};
/**
static void DebugPrint(void);
*/
//-----------------------------------------------------------------------------
/**
 * ���ɂ��ɂ��m���v�Z
 *
 * @param	inProb			���݃G���J�E���g�m��
 *
 * @return	int				�G���J�E���g�m��
 */
//-----------------------------------------------------------------------------
int CalEnc_GetProb(const int inProb, const BOOL inPenalty)
{
	u8 i;
	int prob;
	RTCDate date;
	const CAL_ENC_MONTH_DATA * data;

	//���ԕs���ύX���ꂽ�ꍇ�́A�������Ȃ�
	if (inPenalty){
		return inProb;
	}
	
	if (inProb == 0){
		return 0;
	}

//	DebugPrint();
	
	GF_RTC_GetDate(&date);

	GF_ASSERT(date.month>0);
	GF_ASSERT(date.month<=12);

	data = &(CalEncMonthData[date.month-1]);

	for(i=0;i<data->Num;i++){
		if ( date.day == GET_DAY(data->DayData[i]) ){
			prob = inProb + ProbTbl[ GET_PROB_NO(data->DayData[i]) ];
			if (prob < 0){
				prob = 1;
			}
			return prob;
		}
	}
	return inProb;
}

/**
static void DebugPrint(void)
{
	int i,j;
	const CAL_ENC_MONTH_DATA * data;
	for(j=0;j<MONTH_NUM;j++){
		data = &(CalEncMonthData[j]);
		OS_Printf("Month:%d DayNum:%d\n",j+1,data->Num);
		for(i=0;i<data->Num;i++){
			OS_Printf(" Day:%d Prob:%d\n",GET_DAY(data->DayData[i]),GET_PROB_NO(data->DayData[i]));
		}
	}
}
*/

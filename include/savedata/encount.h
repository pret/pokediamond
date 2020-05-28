//=============================================================================
/**
 * @file	encount.h
 * @bfief	�G���J�E���g�֘A�Z�[�u�f�[�^�A�N�Z�X�֘A
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================
#ifndef __ENCOUNT_H__
#define __ENCOUNT_H__
#include "savedata/savedata_def.h"
#include "savedata/honeytree_data.h"
#include "field/sway_grass_hist_def.h"

#define	ENC_RND_SEED_SAFARI		(1)
#define ENC_RND_SEED_GENERATE	(2)
#define ENC_RND_SEED_UNKNOWN	(0)		//�g��Ȃ����ǈꉞ

//�ړ��|�P�����p�����[�^�h�c
#define MP_PARAM_ZONE_ID	(1)		//�]�[���h�c
#define MP_PARAM_POW_RND	(2)		//�p���[����
#define MP_PARAM_PER_RND	(3)		//������
#define MP_PARAM_MONSNO		(4)		//�����X�^�[�i���o�[
#define MP_PARAM_HP			(5)		//�g�o
#define MP_PARAM_LV			(6)		//�k�u
#define MP_PARAM_COND		(7)		//��Ԉُ�
#define MP_PARAM_ENC		(8)		//�G���J�E���g�t���O�i���݈ړ������ǂ����j

#define HILL_BACK_POKE_NONE	(0xffff)	//���R�|�P�������Ȃ����

typedef struct ENC_SV_DATA_tag * ENC_SV_PTR;
typedef struct MV_POKE_DATA_tag * MPD_PTR;

extern int EncDataSave_GetWorkSize(void);
extern void EncDataSave_InitSaveData(ENC_SV_PTR outEncData);
extern void EncDataSave_UpdateRandSeed(ENC_SV_PTR ioEncData, const u32 inRandSeed);
extern u32 EncDataSave_GetRandSeed(ENC_SV_PTR inEncData, const u8 inSeedType);
extern ENC_SV_PTR EncDataSave_GetSaveDataPtr(SAVEDATA * sv);
extern SWAY_GRASS_HIST *  EncDataSave_GetSwayGrassHist(ENC_SV_PTR outEncData);
extern HT_PTR EncDataSave_GetHoneyTree(ENC_SV_PTR inEncData);
extern void EncDataSave_StartGenerate( SAVEDATA * sv );
extern u8 EncDataSave_IsGenerate( ENC_SV_PTR inEncData );
extern void EncDataSave_UpdatePlayerZoneHist(ENC_SV_PTR ioEncData, const int inZoneID);
extern int EncDataSave_GetPlayerOldZone(ENC_SV_PTR inEncData);
extern u8 EncDataSave_GetMovePokeZoneIdx(ENC_SV_PTR inEncData, const u8 inTargetPoke);
extern void EncDataSave_SetMovePokeZoneIdx(	ENC_SV_PTR outEncData,
											const u8 inTargetPoke,
											const u8 inZoneIndex	);
extern u8 EncDataSave_IsMovePokeValid(ENC_SV_PTR inEncData, const u8 inTargetPoke);
extern void EncDataSave_ClearMovePokeData(MPD_PTR *outMPData);
extern MPD_PTR	EncDataSave_GetMovePokeDataPtr(ENC_SV_PTR inEncData, const u8 inTargetPoke);
extern u32 EncDataSave_GetMovePokeDataParam(const MPD_PTR inMPData,
											const u8 inParamID);
extern void EncDataSave_SetMovePokeDataParam(	MPD_PTR outMPData,
												const u8 inParamID,
												const u32 inVal	);
extern u8 *EncDataSave_GetPokeSearcherCharge(ENC_SV_PTR inEncData);
extern u8 *EncDataSave_GetSprayCnt(ENC_SV_PTR inEncData);
extern BOOL EncDataSave_CanUseSpray(ENC_SV_PTR inEncData);
extern void EncDataSave_SetVidro(ENC_SV_PTR outEncData, const u8 inType);
extern u8 EncDataSave_GetVidro(ENC_SV_PTR inEncData);

extern void EncDataSave_GetHillBackPokeIdx(SAVEDATA *sv, u16 *outIndex1, u16 *outIndex2);
extern void EncDataSave_SetHillBackPokeIdx(SAVEDATA *sv, const u16 inIndex);
#endif	//__ENCOUNT_H__

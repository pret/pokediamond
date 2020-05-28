//============================================================================================
/**
 * @file	wifi_earth.h
 * @brief
 * @date	
 */
//============================================================================================

#ifndef	__WIFIEARTH_H__
#define	__WIFIEARTH_H__

//============================================================================================
/**
 * @brief	Proc �Ăяo���̍ۂɈ����n����郏�[�N�\����
 */
//============================================================================================
#if 0
typedef struct WIFI_EARTH_PARAM_tag
{
	SAVEDATA* savedata;
}WIFI_EARTH_PARAM;
#endif

extern PROC_RESULT Earth_Demo_Init(PROC * proc, int * seq);
extern PROC_RESULT Earth_Demo_Main(PROC * proc, int * seq);
extern PROC_RESULT Earth_Demo_Exit(PROC * proc, int * seq);
//============================================================================================
/**
 * @brief	Proc �Ăяo���p�e�[�u��
 */
//============================================================================================
extern const PROC_DATA Earth_Demo_proc_data;

//============================================================================================
/**
 *	�n��f�[�^�������i�Z�[�u���[�N�̏������j
 *
 * @param[in]	savedata	�Z�[�u�f�[�^�ւ̃|�C���^	
 * @retval
 */
//============================================================================================
extern void	WIFI_RegistratonInit(SAVEDATA* savedata);

//============================================================================================
/**
 *	�����擾
 *
 * @param[in]	nationID	���h�c
 * @param[in]	areaID		�n��h�c
 * @param[in]	nation_str	�����i�[�o�b�t�@�|�C���^
 * @param[in]	area_str	�n�於�i�[�o�b�t�@�|�C���^
 * @param[in]	heapID		�e���|�����q�[�v�h�c
 *
 * @retval	FALSE:�n�悪�Ȃ����@TRUE:�n�悪���鍑
 */
//============================================================================================
extern BOOL	WIFI_NationAreaNameGet
			(int nationID,int areaID,STRBUF* nation_str,STRBUF* area_str,int heapID);

//============================================================================================
/**
 *	���[�J���G���A���݃`�F�b�N
 *
 * @param[in]	nationID	���h�c
 *
 * @retval	FALSE:�n��Ȃ��@TRUE:�n�悠��
 */
//============================================================================================
extern BOOL	WIFI_LocalAreaExistCheck(int nationID);

#endif

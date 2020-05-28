//=============================================================================
/**
 * @file	comm_union_beacon.h
 * @brief	���j�I�����[���r�[�R���ݒ菈��
 * @author	Akito Mori
 * @date    2005.12.10
 */
//=============================================================================

#ifndef	__COMM_UNION_BEACON_H__
#define	__COMM_UNION_BEACON_H__


#define UNION_PARENT_MODE_FREE			(  0 )
#define UNION_PARENT_MODE_OEKAKI_FREE	(  1 )
#define UNION_PARENT_MODE_RECORD_FREE	(  2 )
#define UNION_PARENT_MODE_GURUGURU_FREE	(  3 )
#define UNION_PARENT_MODE_BUSY			(  4 )
#define UNION_PARENT_MODE_CARDNOW		(  5 )
#define UNION_PARENT_MODE_BATTLENOW		(  6 )
#define UNION_PARENT_MODE_TRADENOW		(  7 )
#define UNION_PARENT_MODE_OEKAKINOW		(  8 )
#define UNION_PARENT_MODE_RECORDNOW		(  9 )
#define UNION_PARENT_MODE_GURUGURUNOW	( 10 )
#define UNION_PARENT_MODE_PARTY			( 11 )


#ifndef	__ASM_NO_DEF_	// ������ȍ~�́A�A�Z���u���ł͖���


#include "system/pms_data.h"

// �r�[�R���Ɋ܂܂�郆�j�I�����[���p���\����
// ���̏���WMBssDec.gameDataInfo.userGameInfo�̒����L���X�g���ĎQ�Ƃ���
// _GF_BSS_DATA_INFO.regulationBuff���܂�����L���X�g���Ďg���Ă���
// regulationBuff�͐퓬�p�̃��M�����[�V�����Ȃ̂ŁA���j�I���ł͂܂������g�p���Ă��Ȃ�����
typedef struct{
	u32 c_id[4];		// �q�@��ID			16
	u8  c_rom[4];		// �q�@��ROM		20
	u8  c_region[4];	// �q�@�̍��R�[�h	24
	u8  c_face[4];		// �q�@�̎p�ԍ�		28
	u8  mode;			// �e�@�̏�ԁi�t���[�E���������Ńt���[�E�Z�����E��������E�o�g���j	29
	u8  nation;			// �Z��ł��鍑   30
	u8	area;			// �Z��ł���s�s�E�ꏊ 31
	u8  etc;			// �]��i�������̂P�o�C�g�����c�j32 
}UNION_BEACON_STATE;


// ���j�I���p�r�[�R�����������֐�
extern void Union_BeaconChange( int flag );
extern void Union_PMSReWrite( PMS_DATA *pms );

extern u16 *UnionView_GetPalNo( u16 * table, int sex, int view_type );
extern int UnionView_GetCharaNo( int sex, int view_type );
extern u16 *UnionView_PalleteTableAlloc( int heapID );



#endif	__ASM_NO_DEF_


#endif
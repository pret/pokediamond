//============================================================================================
/**
 * @file	townmap_footmark.h
 * @brief	�^�E���}�b�v��ŕ\��������l���̈ړ��󋵋L�^
 * @author	saitou GAME FREAK inc.
 *
 * 2005.12.19	�F�X�C��
 */
//============================================================================================
#ifndef	__TOWNMAP_FOOTMARK_H__
#define	__TOWNMAP_FOOTMARK_H__

//--------------------------------------------------------------
//	�^�E���}�b�v
//--------------------------------------------------------------
#define FOOTMARK_NUM	(6)			///<�^�E���}�b�v���Ղ̐�

//--------------------------------------------------------------
///	TOWN_MAP_FOOTMARK_PARAM�\����
//--------------------------------------------------------------
typedef struct {
	u8 BlockX;
	u8 BlockZ;
	u8 Dir;
	u8 Valied;
}TOWN_MAP_FOOTMARK_PARAM;

//--------------------------------------------------------------
///	TOWN_MAP_FOOTMARK�\����
//--------------------------------------------------------------
typedef struct {
	int NowPoint;
	u8 NowBlockX;
	u8 NowBlockZ;
	TOWN_MAP_FOOTMARK_PARAM Param[FOOTMARK_NUM];
}TOWN_MAP_FOOTMARK;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
extern void TMFootMark_Init(TOWN_MAP_FOOTMARK *outFootMark);
extern void TMFootMark_SetNoDir(TOWN_MAP_FOOTMARK *ioFootMark, int x, int z);
extern void TMFootMark_Update(TOWN_MAP_FOOTMARK *ioFootMark, int x, int z, int dir);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifdef	PM_DEBUG
extern void TMFootMark_Init_Debug(TOWN_MAP_FOOTMARK * footmark);
#endif

#endif	//__TOWNMAP_FOOTMARK_H__

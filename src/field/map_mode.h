//============================================================================================
/**
 * @file	map_mode.h
 * @brief	�}�b�v���Ƃ̒�`
 * @date	2006.04.23
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================
#ifndef	__MAP_MODE_H__
#define	__MAP_MODE_H__

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�̑�ʎw��
 */
//-----------------------------------------------------------------------------
typedef enum {
	MAP_MODE_GROUND,		///<�ʏ�
	MAP_MODE_UNDER,			///<�Y�z
	MAP_MODE_UNION,			///<���j�I�����[��
	MAP_MODE_COLOSSEUM,		///<�ʐM�ΐ핔��
	MAP_MODE_BTOWER,		///<�o�g���^���[

	MAP_MODE_MAX,			///<���~�b�g��`
}MAP_MODE;


//-----------------------------------------------------------------------------
/**
 * @brief	MAP_MODE���Ƃ̌ʃp�����[�^
 */
//-----------------------------------------------------------------------------
typedef struct {
	u32 subscreen:4;				///<�T�u��ʃA�v���w��
	u32 DivMapMode:4;				///<DivMap�p�w��
	u32 MapToolMode:4;				///<MapTool�p�w��
	u32 disp3DSW:4;					///<�T�u�E���C����ʈʒu�w��
	u32 SpecialAttrFlag:4;			///<����A�g���r���[�g�����w��
	u32 UseOverlayFlag:4;			///<�t�B�[���h�I�[�o�[���C�g�p�w��
	u32 SpecialAttrNum:8;			///<����A�g���r���[�g�����œǂݍ��ރf�[�^��

	u32 HeapSize;					///<�t�B�[���h�}�b�v�Ŋm�ۂ���q�[�v�̃T�C�Y
}MAP_MODE_DATA;

#endif	/* __MAP_MODE_H__ */

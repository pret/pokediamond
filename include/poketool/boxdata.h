//==============================================================================
/**
 *
 *@file		boxdata.h
 *@brief	�|�P�����{�b�N�X�f�[�^�Ǘ�
 *@author	taya
 *@data		2005.09.8
 *
 */
//==============================================================================
#ifndef __BOXDATA_H__
#define __BOXDATA_H__

#include  "system\savedata_def.h"
#include  "gflib\strbuf.h"
#include  "poketool\poke_tool.h"	// POKEMON_PASO_PARAM �Q�Ƃ̂���

//------------------------------------------------------------
/**
 * @brief	�{�b�N�X�f�[�^�Q�Ɨp�s���S�^�|�C���^
 *
 *   ����̃|�C���^�o�R�ŏ������s��
 */
//------------------------------------------------------------
typedef struct _BOX_DATA	BOX_DATA;

//------------------------------------------------------------
/**
 *   �萔
 */
//------------------------------------------------------------
#define BOX_MAX_RAW				(5)
#define BOX_MAX_COLUMN			(6)
#define BOX_MAX_TRAY			(18)
#define BOX_TRAYNAME_MAXLEN		(8)
#define BOX_TRAYNAME_BUFSIZE	(20)	// ���{��W�����{EOM�B�C�O�ŗp�̗]�T�����Ă��̒��x�B
#define BOX_MAX_POS				(BOX_MAX_RAW*BOX_MAX_COLUMN)


#define BOX_NORMAL_WALLPAPER_MAX	(16)
#define BOX_EX_WALLPAPER_MAX		(8)
#define BOX_TOTAL_WALLPAPER_MAX		(BOX_NORMAL_WALLPAPER_MAX+BOX_EX_WALLPAPER_MAX)

#define BOXDAT_TRAYNUM_CURRENT		(0xffffffff)	///< �g���C�i���o�[�������Ɏ��֐��Ŏw�肷��ƁA�J�����g���w�肵�����ƂɂȂ�B
#define BOXDAT_TRAYNUM_ERROR		(BOX_MAX_TRAY)	///< �󂫂̂���g���C�T�[�`�ŁA������Ȃ��������Ȃǂ̖߂�l


extern BOX_DATA * SaveData_GetBoxData(SAVEDATA * sv);

//------------------------------------------------------------------
/**
 * �{�b�N�X�f�[�^�̈���쐬�i�Z�[�u�f�[�^�ǂݍ��ݎ��ɂP�񂾂��j
 *
 * @param   heapID		�쐬��q�[�v�h�c
 *
 * @retval  BOX_DATA*	�쐬���ꂽ�{�b�N�X�f�[�^�̃|�C���^
 */
//------------------------------------------------------------------
extern BOX_DATA* BOXDAT_Create( u32 heapID );


//------------------------------------------------------------------
/**
 * �{�b�N�X�f�[�^�̓��e������������
 *
 * @param   boxdat		�{�b�N�X�f�[�^�̃|�C���^
 */
//------------------------------------------------------------------
extern void BOXDAT_Init( BOX_DATA* boxdat );

//------------------------------------------------------------------
/**
 * �{�b�N�X�f�[�^�̈�̑��T�C�Y��Ԃ��i�Z�[�u�f�[�^�Ǘ��p�j
 *
 * @retval  u32		�{�b�N�X�f�[�^���T�C�Y
 */
//------------------------------------------------------------------
extern u32 BOXDAT_GetTotalSize( void );


//------------------------------------------------------------------
/**
 * �{�b�N�X�S�̂��炩��󂫗̈��T���ă|�P�����f�[�^���i�[
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   poke		�|�P�����f�[�^
 *
 * @retval  BOOL		TRUE=�i�[���ꂽ�^FALSE=�󂫂�����
 */
//------------------------------------------------------------------
extern BOOL BOXDAT_PutPokemon( BOX_DATA* box, POKEMON_PASO_PARAM* poke );

//------------------------------------------------------------------
/**
 * �{�b�N�X���w�肵�ă|�P�����f�[�^�i�[
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   boxNum		���Ԗڂ̃{�b�N�X�Ɋi�[���邩
 * @param   poke		�|�P�����f�[�^
 *
 * @retval  BOOL		TRUE=�i�[���ꂽ�^FALSE=�󂫂�����
 */
//------------------------------------------------------------------
extern BOOL BOXDAT_PutPokemonBox( BOX_DATA* box, u32 boxNum, POKEMON_PASO_PARAM* poke );

//------------------------------------------------------------------
/**
 * �{�b�N�X�A�ʒu���w�肵�ă|�P�����f�[�^�i�[
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   boxNum		���Ԗڂ̃{�b�N�X�Ɋi�[���邩
 * @param   x			�{�b�N�X���̈ʒu�w
 * @param   y			�{�b�N�X���̈ʒu�x
 * @param   poke		�|�P�����f�[�^
 *
 * @retval  BOOL		TRUE=�i�[���ꂽ�^FALSE=�󂫂�����
 */
//------------------------------------------------------------------
extern BOOL BOXDAT_PutPokemonPos( BOX_DATA* box, u32 boxNum, u32 pos, POKEMON_PASO_PARAM* poke );


//------------------------------------------------------------------
/**
 * �P�ł��󂫂̂���g���C�i���o�[��Ԃ��i�J�����g���猟���J�n����j
 *
 * @param   box		�{�b�N�X�f�[�^�|�C���^
 *
 * @retval  u32		�󂫂̂���g���C�i���o�[�^������Ȃ���� BOXDAT_TRAYNUM_ERROR ���Ԃ�
 */
//------------------------------------------------------------------
extern u32 BOXDAT_GetEmptyTrayNumber( const BOX_DATA* box );


//------------------------------------------------------------------
/**
 * �ʒu���w�肵�ăJ�����g�{�b�N�X�̃|�P�����f�[�^�N���A
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   trayNumber	���Ԗڂ̃{�b�N�X��
 * @param   pos			�{�b�N�X���̈ʒu
 *
 */
//------------------------------------------------------------------
extern void BOXDAT_ClearPokemon( BOX_DATA* box, u32 trayNum, u32 pos );

//------------------------------------------------------------------
/**
 * �{�b�N�X�S�̂Ɋ܂܂��|�P��������Ԃ�
 *
 * @param   box		�{�b�N�X�f�[�^�|�C���^
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
extern u32 BOXDAT_GetPokeExistCountTotal( const BOX_DATA* box );
extern u32 BOXDAT_GetPokeExistCount2Total( const BOX_DATA* box );

extern u32 BOXDAT_GetEmptySpaceTotal( const BOX_DATA* box );
extern u32 BOXDAT_GetEmptySpaceTray( const BOX_DATA* box, u32 trayNum );

extern u32 BOXDAT_GetCureentTrayNumber( const BOX_DATA* box );
extern void BOXDAT_SetCureentTrayNumber( BOX_DATA* box, u32 num );
extern u32 BOXDAT_GetWallPaperNumber( const BOX_DATA* box, u32 trayNumber );
extern void BOXDAT_SetWallPaperNumber( BOX_DATA* box, u32 trayNum, u32 wallPaperNumber );
extern void BOXDAT_GetBoxName( const BOX_DATA* box, u32 trayNumber, STRBUF* buf );
extern void BOXDAT_SetBoxName( BOX_DATA* box, u32 trayNumber, const STRBUF* src );
extern u32 BOXDAT_GetPokeExistCount( const BOX_DATA* box, u32 trayNumber );
extern u32 BOXDAT_GetPokeExistCount2( const BOX_DATA* box, u32 trayNumber );
extern POKEMON_PASO_PARAM* BOXDAT_GetPokeDataAddress( const BOX_DATA* box, u32 boxNum, u32 pos );
extern BOOL BOXDAT_GetEmptyTrayNumberAndPos( const BOX_DATA* box, int* trayNum, int* pos );
extern u32 BOXDAT_PokeParaGet( const BOX_DATA* box, u32 trayNum, u32 pos, int param, void* buf );
extern void BOXDAT_PokeParaPut( BOX_DATA* box, u32 trayNum, u32 pos, int param, void* buf );


//==============================================================================================
// ���������N���u�ǎ�
//==============================================================================================
extern void BOXDAT_SetDaisukiKabegamiFlag( BOX_DATA* box, u32 number );
extern BOOL BOXDAT_GetDaisukiKabegamiFlag( const BOX_DATA* box, u32 number );
extern u32  BOXDAT_GetDaiukiKabegamiCount( const BOX_DATA* box );

#endif

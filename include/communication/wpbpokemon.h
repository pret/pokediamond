/*---------------------------------------------------------------------------*
  Project:  Wireless PassBy Library - include
  File:     wpbpokemon.h

  2005 Ambrella
 *---------------------------------------------------------------------------*/
#ifndef WPBPOKEMON_H_
#define WPBPOKEMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include <nitro/types.h>
#include <nitro/wm.h>

/*---------------------------------------------------------------------------*
    �\���̒�`
 *---------------------------------------------------------------------------*/

// �Q�[���ԋ��ʏ��
typedef struct WPBPokemonInfo {
	u32 version;        // �|�P����DS�\�t�g�Ƃ��Ă�ID�ԍ�
	u32 tryTime;        // ���񂷂�Ⴄ�܂łɂ����������� (�b) (�s���� -1)
	u32 tryCount;       // ���݂܂ł̂���Ⴂ���s�� (�s���� -1)
	u32 successCount;   // ���݂܂ł̂���Ⴂ������ (�s���� -1)
	u32 totalTime;      // ���݂܂ł̑�����Ⴂ���s���� (�b) (�s���� -1)
	u16 gameName[128];  // �Q�[���� (UTF-16LE)
	u8  image[32*32/2]; // �A�C�R���f�[�^
	u8  pltt[16*2];     // �A�C�R���p���b�g
	u8  macAddress[WM_SIZE_BSSID]; // ������macAddress
	u8  present;        // �v���[���g
	u8  favoriteColor;  // ���C�ɓ���̐F ( 0 �` 15 )
	u16 sex_birth;      // ���ʁA�a�����A�N����
	u16 nickName[ 10 ]; // �j�b�N�l�[�� (UTF16)
	u16 nickNameLength; // �j�b�N�l�[��������( 0 �` 10 )
	u16 comment[ 39 ];  // �R�����g (UTF16)
	u16 commentLength;  // �R�����g������( 0 �` 39 )
} WPBPokemonInfo;

/*---------------------------------------------------------------------------*
    �֐���`
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         WPB_ToPresentID

  Description:  �Q�[�����̃A�C�e���̔ԍ��� 0�`255 �� present ID�ɕϊ�����B

  Arguments:    totalItems  - �Q�[�����̃A�C�e���̑���
                salt        - �Q�[���ɂ���ČŗL�́A�Ȃ�ׂ����̃Q�[���Əd�����Ȃ��l ( 1 - 255 )
                itemNo      - �Q�[�����̃A�C�e���ԍ� ( 0 - totalItems )

  Returns:      present ID�B
 *---------------------------------------------------------------------------*/
u8 WPB_ToPresentID(u8 totalItems, u8 salt, u8 itemNo);

/*---------------------------------------------------------------------------*
  Name:         WPB_FromPresentID

  Description:  0�`255 �� present ID ���Q�[�����̃A�C�e���̔ԍ��ɕϊ�����B

  Arguments:    totalItems  - �Q�[�����̃A�C�e���̑���
                salt        - �Q�[���ɂ���ČŗL�́A�Ȃ�ׂ����̃Q�[���Əd�����Ȃ��l ( 1 - 255 )
                presentID   - present ID ( 0 - 255 )

  Returns:      �Q�[�����̃A�C�e���ԍ� ( 0 - totalItems )
 *---------------------------------------------------------------------------*/
u8 WPB_FromPresentID(u8 totalItems, u8 salt, u8 presentID);

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* WPBPOKEMON_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/

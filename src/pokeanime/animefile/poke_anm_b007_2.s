//==============================================================================
/**
 * @file	poke_anm_b007_2.s
 * @brief	�c���Ɉ�������
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B007_2
	
// =============================================================================
//
//
//	�w��	�c���Ɉ�������m�[�}��
//
//
// =============================================================================
PAST_ANIME_B007_2:
	//15��̃��[�v��180���i0x8000�j����
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_RY,0x3c,0x8000,0,15
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_RX,0x3c,0x8000,0,15
	//�E�F�C�g4�@7��̃��[�v��4��0x40000�j������
	CALL_MF_CURVE_DIVTIME APPLY_SYNTHE,4,CURVE_SIN,TARGET_RY,0xc,0x40000,0,7
	CALL_MF_CURVE_DIVTIME APPLY_SYNTHE,4,CURVE_SIN,TARGET_RX,0xc,0x40000,0,7
	HOLD_CMD
	
	END_ANM

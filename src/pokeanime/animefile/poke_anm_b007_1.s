//==============================================================================
/**
 * @file	poke_anm_b007_1.s
 * @brief	�c���Ɉ�������
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B007_1
	
// =============================================================================
//
//
//	�w��	�c���Ɉ�������N�C�b�N
//
//
// =============================================================================
PAST_ANIME_B007_1:
	START_LOOP	2
		//10��̃��[�v��180���i0x8000�j����
		CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_RY,0x46,0x8000,0,10
		CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_RX,0x46,0x8000,0,10
		//�E�F�C�g2�@6��̃��[�v��4��0x40000�j������
		CALL_MF_CURVE_DIVTIME APPLY_SYNTHE,2,CURVE_SIN,TARGET_RY,0xe,0x40000,0,6
		CALL_MF_CURVE_DIVTIME APPLY_SYNTHE,2,CURVE_SIN,TARGET_RX,0xe,0x40000,0,6
		HOLD_CMD
	END_LOOP
	
	END_ANM

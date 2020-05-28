//==============================================================================
/**
 * @file	past.h
 * @brief	�|�P�����A�j���}�N����`
 * @author	saito
 * @date	2006.04.03
 *
 */
//==============================================================================

// =============================================================================
//
//	�}�N����`
//
// =============================================================================
	.macro	INIT_CMD
		DEF_CMD_COUNT	=	0;
	.endm

	.macro	DEF_CMD	symname
		\symname		= DEF_CMD_COUNT
		DEF_CMD_COUNT	= (DEF_CMD_COUNT + 1)
	.endm
	
	INIT_CMD
	DEF_CMD		PAST_END
	DEF_CMD		PAST_SET_REQUEST
	DEF_CMD		PAST_SET_DEFAULT
	DEF_CMD		PAST_SET_IF_WORK_VAL
	DEF_CMD		PAST_SET_WORK_VAL
	DEF_CMD		PAST_COPY_WORK_VAL
	DEF_CMD		PAST_ADD_WORK_VAL
	DEF_CMD		PAST_MUL_WORK_VAL
	DEF_CMD		PAST_SUB_WORK_VAL
	DEF_CMD		PAST_DIV_WORK_VAL
	DEF_CMD		PAST_MOD_WORK_VAL
	DEF_CMD		PAST_START_LOOP
	DEF_CMD		PAST_END_LOOP
	DEF_CMD		PAST_SET_VAL
	DEF_CMD		PAST_ADD_VAL
	DEF_CMD		PAST_SET_ADD_VAL
	DEF_CMD		PAST_SET_WORK_VAL_SIN
	DEF_CMD		PAST_SET_WORK_VAL_COS
	DEF_CMD		PAST_SET_TRANS
	DEF_CMD		PAST_ADD_TRANS
	DEF_CMD		PAST_SET_ADD_PARAM
	DEF_CMD		PAST_APPLY_TRANS
	DEF_CMD		PAST_APPLY_AFFINE
	DEF_CMD		PAST_SET_D

	DEF_CMD		PAST_HOLD_CMD
	DEF_CMD		PAST_SET_DY_CORRECT
	DEF_CMD		PAST_CALL_MF_CURVE
	DEF_CMD		PAST_CALL_MF_CURVE_DIVTIME
	DEF_CMD		PAST_CALL_MF_LINE
	DEF_CMD		PAST_CALL_MF_LINE_DIVTIME
	DEF_CMD		PAST_CALL_MF_LINE_DST
	
	DEF_CMD		PAST_SET_WAIT
	DEF_CMD		PAST_PALETTE_FADE
	DEF_CMD		PAST_WAIT_PALETTE_FADE

// -----------------------------------------
//
//	�A�j���I���}�N��
//
// -----------------------------------------
	.macro	END_ANM
	.long	PAST_END
	.endm
	
// -----------------------------------------
//
//	�A�j�����N�G�X�g�}�N��
//
// -----------------------------------------
	.macro	SET_REQUEST
	.long	PAST_SET_REQUEST
	.endm

// -----------------------------------------
//
//	�\�t�g�E�F�A�X�v���C�g�̈ʒu�A��]�A�g�k��߂��}�N��
//
// -----------------------------------------
	.macro	SET_DEFAULT
	.long	PAST_SET_DEFAULT
	.endm

// -----------------------------------------
//
//	�������Ń��[�N�Ƀ��[�N���Z�b�g����}�N��
//
// -----------------------------------------
	.macro SET_IFWORKVAL use1,v1,v2,comp,use2,v3,v4
	.long	PAST_SET_IF_WORK_VAL
	.long	\use1
	.long	\v1
	.long	\v2
	.long	\comp
	.long	\use2
	.long	\v3
	.long	\v4
	.endm
	
// -----------------------------------------
//
//	���[�N�Z�b�g�}�N��
//
// -----------------------------------------
	.macro	SET_WORK_VAL	idx,val
	.long	PAST_SET_WORK_VAL
	.long	\idx
	.long	\val
	.endm

// -----------------------------------------
//
//	���[�N�R�s�[�}�N��
//
// -----------------------------------------
	.macro	COPY_WORK_VAL	idx1,idx2
	.long	PAST_COPY_WORK_VAL
	.long	\idx1
	.long	\idx2
	.endm

// -----------------------------------------
//
//	���[�N���Z�}�N��
//
// -----------------------------------------
	.macro	ADD_WORK_VAL	dst_idx,calc,v1,v2
	.long	PAST_ADD_WORK_VAL
	.long	\dst_idx
	.long	\calc
	.long	\v1
	.long	\v2
	.endm

// -----------------------------------------
//
//	���[�N��Z�}�N��
//
// -----------------------------------------
	.macro	MUL_WORK_VAL	dst_idx,calc,v1,v2
	.long	PAST_MUL_WORK_VAL
	.long	\dst_idx
	.long	\calc
	.long	\v1
	.long	\v2
	.endm

// -----------------------------------------
//
//	���[�N���Z�}�N��
//
// -----------------------------------------
	.macro	SUB_WORK_VAL	dst_idx,calc1,calc2,v1,v2
	.long	PAST_SUB_WORK_VAL
	.long	\dst_idx
	.long	\calc1
	.long	\calc2
	.long	\v1
	.long	\v2
	.endm

// -----------------------------------------
//
//	���[�N���Z�}�N��
//
// -----------------------------------------
	.macro	DIV_WORK_VAL	dst_idx,calc1,calc2,v1,v2
	.long	PAST_DIV_WORK_VAL
	.long	\dst_idx
	.long	\calc1
	.long	\calc2
	.long	\v1
	.long	\v2
	.endm

// -----------------------------------------
//
//	���[�N�]��v�Z�}�N��
//
// -----------------------------------------
	.macro	MOD_WORK_VAL	dst_idx,calc1,calc2,v1,v2
	.long	PAST_MOD_WORK_VAL
	.long	\dst_idx
	.long	\calc1
	.long	\calc2
	.long	\v1
	.long	\v2
	.endm
	
// -----------------------------------------
//
//	���[�v�X�^�[�g�}�N��
//
// -----------------------------------------
	.macro	START_LOOP	loop
	.long	PAST_START_LOOP
	.long	\loop
	.endm

// -----------------------------------------
//
//	���[�v�I���}�N��
//
// -----------------------------------------
	.macro	END_LOOP
	.long	PAST_END_LOOP
	.endm
	
// -----------------------------------------
//
//	�Z�b�g�}�N��
//
// -----------------------------------------
	.macro	SET_VAL	ss_param,idx
	.long	PAST_SET_VAL
	.long	\ss_param
	.long	\idx
	.endm
	
// -----------------------------------------
//
//	�������݃}�N��
//
// -----------------------------------------
	.macro	ADD_VAL	ss_param,idx
	.long	PAST_ADD_VAL
	.long	\ss_param
	.long	\idx
	.endm
	
// -----------------------------------------
//
//	�X�v���C�g�ɒl���Z�b�g�E�A�b�h����}�N��
//
// -----------------------------------------	
	.macro	SET_ADD_VAL	ss_param,use,v,ss_calc
	.long	PAST_SET_ADD_VAL
	.long	\ss_param
	.long	\use
	.long	\v
	.long	\ss_calc
	.endm

	
// -----------------------------------------
//
//	���[�N�Z�b�g(sin)�}�N��
//
// -----------------------------------------
	.macro	SET_WORK_VAL_SIN	idx,rad_idx,use1,l,use2,ofs
	.long	PAST_SET_WORK_VAL_SIN
	.long	\idx
	.long	\rad_idx
	.long	\use1
	.long	\l
	.long	\use2
	.long	\ofs
	.endm

// -----------------------------------------
//
//	���[�N�Z�b�g(cos)�}�N��
//
// -----------------------------------------
	.macro	SET_WORK_VAL_COS	idx,rad_idx,use1,l,use2,ofs
	.long	PAST_SET_WORK_VAL_COS
	.long	\idx
	.long	\rad_idx
	.long	\use1
	.long	\l
	.long	\use2
	.long	\ofs
	.endm

// -----------------------------------------
//
//	�g�����X�Z�b�g�}�N��
//
// -----------------------------------------
	.macro	SET_TRANS	idx,trans
	.long	PAST_SET_TRANS
	.long	\idx
	.long	\trans
	.endm

// -----------------------------------------
//
//	�g�����X�A�b�h�}�N��
//
// -----------------------------------------
	.macro	ADD_TRANS	idx,trans
	.long	PAST_ADD_TRANS
	.long	\idx
	.long	\trans
	.endm

// -----------------------------------------
//
//	�p�����[�^�Z�b�g�E�A�b�h�}�N��
//
// -----------------------------------------
	.macro	SET_ADD_PARAM	param,use,v,calc
	.long	PAST_SET_ADD_PARAM
	.long	\param
	.long	\use
	.long	\v
	.long	\calc
	.endm
	
// -----------------------------------------
//
//	�g�����X�K�p�}�N��
//
// -----------------------------------------
	.macro	APPLY_TRANS
	.long	PAST_APPLY_TRANS
	.endm

// -----------------------------------------
//
//	�A�t�B���K�p�}�N��
//
// -----------------------------------------
	.macro	APPLY_AFFINE
	.long	PAST_APPLY_AFFINE
	.endm

// -----------------------------------------
//
//	�I�t�Z�b�g�}�N��
//
// -----------------------------------------
	.macro	SET_D	idx,trans
	.long	PAST_SET_D
	.long	\idx
	.long	\trans
	.endm

// -----------------------------------------
//
//	�A�j���R�}���h���߃z�[���h�}�N��
//
// -----------------------------------------
	.macro	HOLD_CMD
	.long	PAST_HOLD_CMD
	.endm
	
// -----------------------------------------
//
//	DY�␳�L���t���O�R���g���[���}�N��
//
// -----------------------------------------
	.macro	SET_DY_CORRECT	flg
	.long	PAST_SET_DY_CORRECT
	.long	\flg
	.endm

// -----------------------------------------
//
//	����֐��F�J�[�u�v�Z�}�N��
//
// -----------------------------------------
	.macro	CALL_MF_CURVE	apply,wait,type,target,l,rad,ofs,loop
	.long	PAST_CALL_MF_CURVE
	.long	\apply
	.long	\wait
	.long	\type
	.long	\target
	.long	\l
	.long	\rad
	.long	\ofs
	.long	\loop
	.endm

// -----------------------------------------
//
//	����֐��F�J�[�u�񐔕����v�Z�}�N��
//
// -----------------------------------------
	.macro	CALL_MF_CURVE_DIVTIME	apply,wait,type,target,l,rad,ofs,loop
	.long	PAST_CALL_MF_CURVE_DIVTIME
	.long	\apply
	.long	\wait
	.long	\type
	.long	\target
	.long	\l
	.long	\rad
	.long	\ofs
	.long	\loop
	.endm

// -----------------------------------------
//
//	����֐��F���C���v�Z�}�N��
//
// -----------------------------------------
	.macro	CALL_MF_LINE	apply,wait,target,v,a,loop
	.long	PAST_CALL_MF_LINE
	.long	\apply
	.long	\wait
	.long	\target
	.long	\v
	.long	\a
	.long	\loop
	.endm

// -----------------------------------------
//
//	����֐��F���C���񐔕����v�Z�}�N��
//
// -----------------------------------------
	.macro	CALL_MF_LINE_DIVTIME	apply,wait,target,move,loop
	.long	PAST_CALL_MF_LINE_DIVTIME
	.long	\apply
	.long	\wait
	.long	\target
	.long	\move
	.long	\loop
	.endm

// -----------------------------------------
//
//	����֐��F���C���v�Z�}�N���@�ړI�l�w��
//
// -----------------------------------------
	.macro	CALL_MF_LINE_DST	apply,wait,target,v,a,dst
	.long	PAST_CALL_MF_LINE_DST
	.long	\apply
	.long	\wait
	.long	\target
	.long	\v
	.long	\a
	.long	\dst
	.endm

// -----------------------------------------
//
//	�E�F�C�g�Z�b�g�}�N��
//
// -----------------------------------------
	.macro	SET_WAIT	wait
	.long	PAST_SET_WAIT
	.long	\wait
	.endm

// -----------------------------------------
//
//	�p���b�g�t�F�[�h�}�N��
//
// -----------------------------------------
	.macro	SET_PALETTE_FADE	start,end,wait,rgb
	.long	PAST_PALETTE_FADE
	.long	\start
	.long	\end,
	.long	\wait
	.long	\rgb
	.endm

// -----------------------------------------
//
//	�p���b�g�t�F�[�h�҂��}�N��
//
// -----------------------------------------
	.macro	WAIT_PALETTE_FADE
	.long	PAST_WAIT_PALETTE_FADE
	.endm

//==============================================================================
/**
 * @file	past.h
 * @brief	ポケモンアニメマクロ定義
 * @author	saito
 * @date	2006.04.03
 *
 */
//==============================================================================

// =============================================================================
//
//	マクロ定義
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
//	アニメ終了マクロ
//
// -----------------------------------------
	.macro	END_ANM
	.long	PAST_END
	.endm
	
// -----------------------------------------
//
//	アニメリクエストマクロ
//
// -----------------------------------------
	.macro	SET_REQUEST
	.long	PAST_SET_REQUEST
	.endm

// -----------------------------------------
//
//	ソフトウェアスプライトの位置、回転、拡縮を戻すマクロ
//
// -----------------------------------------
	.macro	SET_DEFAULT
	.long	PAST_SET_DEFAULT
	.endm

// -----------------------------------------
//
//	条件つきでワークにワークをセットするマクロ
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
//	ワークセットマクロ
//
// -----------------------------------------
	.macro	SET_WORK_VAL	idx,val
	.long	PAST_SET_WORK_VAL
	.long	\idx
	.long	\val
	.endm

// -----------------------------------------
//
//	ワークコピーマクロ
//
// -----------------------------------------
	.macro	COPY_WORK_VAL	idx1,idx2
	.long	PAST_COPY_WORK_VAL
	.long	\idx1
	.long	\idx2
	.endm

// -----------------------------------------
//
//	ワーク加算マクロ
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
//	ワーク乗算マクロ
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
//	ワーク減算マクロ
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
//	ワーク除算マクロ
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
//	ワーク余り計算マクロ
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
//	ループスタートマクロ
//
// -----------------------------------------
	.macro	START_LOOP	loop
	.long	PAST_START_LOOP
	.long	\loop
	.endm

// -----------------------------------------
//
//	ループ終了マクロ
//
// -----------------------------------------
	.macro	END_LOOP
	.long	PAST_END_LOOP
	.endm
	
// -----------------------------------------
//
//	セットマクロ
//
// -----------------------------------------
	.macro	SET_VAL	ss_param,idx
	.long	PAST_SET_VAL
	.long	\ss_param
	.long	\idx
	.endm
	
// -----------------------------------------
//
//	足しこみマクロ
//
// -----------------------------------------
	.macro	ADD_VAL	ss_param,idx
	.long	PAST_ADD_VAL
	.long	\ss_param
	.long	\idx
	.endm
	
// -----------------------------------------
//
//	スプライトに値をセット・アッドするマクロ
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
//	ワークセット(sin)マクロ
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
//	ワークセット(cos)マクロ
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
//	トランスセットマクロ
//
// -----------------------------------------
	.macro	SET_TRANS	idx,trans
	.long	PAST_SET_TRANS
	.long	\idx
	.long	\trans
	.endm

// -----------------------------------------
//
//	トランスアッドマクロ
//
// -----------------------------------------
	.macro	ADD_TRANS	idx,trans
	.long	PAST_ADD_TRANS
	.long	\idx
	.long	\trans
	.endm

// -----------------------------------------
//
//	パラメータセット・アッドマクロ
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
//	トランス適用マクロ
//
// -----------------------------------------
	.macro	APPLY_TRANS
	.long	PAST_APPLY_TRANS
	.endm

// -----------------------------------------
//
//	アフィン適用マクロ
//
// -----------------------------------------
	.macro	APPLY_AFFINE
	.long	PAST_APPLY_AFFINE
	.endm

// -----------------------------------------
//
//	オフセットマクロ
//
// -----------------------------------------
	.macro	SET_D	idx,trans
	.long	PAST_SET_D
	.long	\idx
	.long	\trans
	.endm

// -----------------------------------------
//
//	アニメコマンド解釈ホールドマクロ
//
// -----------------------------------------
	.macro	HOLD_CMD
	.long	PAST_HOLD_CMD
	.endm
	
// -----------------------------------------
//
//	DY補正有効フラグコントロールマクロ
//
// -----------------------------------------
	.macro	SET_DY_CORRECT	flg
	.long	PAST_SET_DY_CORRECT
	.long	\flg
	.endm

// -----------------------------------------
//
//	動作関数：カーブ計算マクロ
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
//	動作関数：カーブ回数分割計算マクロ
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
//	動作関数：ライン計算マクロ
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
//	動作関数：ライン回数分割計算マクロ
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
//	動作関数：ライン計算マクロ　目的値指定
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
//	ウェイトセットマクロ
//
// -----------------------------------------
	.macro	SET_WAIT	wait
	.long	PAST_SET_WAIT
	.long	\wait
	.endm

// -----------------------------------------
//
//	パレットフェードマクロ
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
//	パレットフェード待ちマクロ
//
// -----------------------------------------
	.macro	WAIT_PALETTE_FADE
	.long	PAST_WAIT_PALETTE_FADE
	.endm

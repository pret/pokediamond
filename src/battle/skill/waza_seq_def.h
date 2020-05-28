//=============================================================================
/**
 * @file	waza_seq.def
 * @bfief	技シーケンス用のマクロ定義ファイル
 * @author	HisashiSogabe
 * @date	2005.05.24
 */
//=============================================================================
//
#define	__ASM_NO_DEF_
	.include	"../../../include/battle/battle_common.h"
	.include	"../../../include/battle/battle_server.h"
	.include	"../../../include/battle/wazano_def.h"
	.include	"../../../include/battle/tokusyu_def.h"
	.include	"../../../include/msgdata/msg_fightmsg_dp.h"
	.include	"../../../include/poketool/poke_tool.h"
	.include	"../../../include/poketool/tr_tool.h"
	.include	"../../../include/poketool/waza_tool.h"
	.include	"../../../include/itemtool/itemequip.h"
	.include	"../../../include/savedata/record.h"
	.include	"../battle_snd_def.h"
	.include	"../../data/sound/sound_data.sadl"

	.macro	INIT_CMD
DEF_CMD_COUNT	=	0
	.endm
		
	.macro	DEF_CMD	symname
\symname	=	DEF_CMD_COUNT
DEF_CMD_COUNT	=	( DEF_CMD_COUNT + 1 )
	.endm

//命令シンボル宣言
	INIT_CMD
	DEF_CMD	WS_ENCOUNT_EFFECT
	DEF_CMD	WS_POKEMON_ENCOUNT
	DEF_CMD	WS_POKEMON_ENCOUNT_APPEAR
	DEF_CMD	WS_POKEMON_APPEAR
	DEF_CMD	WS_POKEMON_RETURN
	DEF_CMD	WS_POKEMON_DELETE
	DEF_CMD	WS_TRAINER_ENCOUNT
	DEF_CMD	WS_TRAINER_THROW
	DEF_CMD	WS_TRAINER_OUT
	DEF_CMD	WS_TRAINER_IN
	DEF_CMD	WS_TRAINER_BG_SLIDEIN
	DEF_CMD	WS_HP_GAUGE_IN
	DEF_CMD	WS_HP_GAUGE_IN_WAIT
	DEF_CMD	WS_HP_GAUGE_OUT
	DEF_CMD	WS_SERVER_WAIT
	DEF_CMD	WS_DAMAGE_CALC
	DEF_CMD	WS_DAMAGE_CALC_NO_LOSS
	DEF_CMD	WS_ATTACK_MESSAGE
	DEF_CMD	WS_MESSAGE
	DEF_CMD	WS_MESSAGE_NO_DIR
	DEF_CMD	WS_MESSAGE_WORK
	DEF_CMD	WS_MESSAGE_PARAM
	DEF_CMD	WS_MESSAGE_DIR
	DEF_CMD	WS_WAZA_EFFECT
	DEF_CMD	WS_WAZA_EFFECT2
	DEF_CMD	WS_POKEMON_BLINK
	DEF_CMD	WS_HP_CALC					//0x10
	DEF_CMD	WS_HP_GAUGE_CALC
	DEF_CMD	WS_KIZETSU_CHECK
	DEF_CMD	WS_KIZETSU_EFFECT
	DEF_CMD	WS_WAIT
	DEF_CMD	WS_SE_PLAY
	DEF_CMD	WS_IF
	DEF_CMD	WS_IF_PSP
	DEF_CMD	WS_FADE_OUT
	DEF_CMD	WS_JUMP
	DEF_CMD	WS_JUMP_BE_SEQ
	DEF_CMD	WS_JUMP_WAZA_WORK
	DEF_CMD	WS_CRITICAL_CHECK
	DEF_CMD	WS_GET_EXP_CHECK
	DEF_CMD	WS_GET_EXP_INIT
	DEF_CMD	WS_GET_EXP
	DEF_CMD	WS_GET_EXP_LOOP
	DEF_CMD	WS_POKEMON_LIST
	DEF_CMD	WS_POKEMON_LIST_WAIT
	DEF_CMD	WS_POKEMON_RESHUFFLE
	DEF_CMD	WS_POKEMON_RESHUFFLE_LOOP
	DEF_CMD	WS_POKEMON_GET_INIT
	DEF_CMD	WS_POKEMON_GET
	DEF_CMD	WS_RENZOKU
	DEF_CMD	WS_VALUE
	DEF_CMD	WS_ABICNT_CALC
	DEF_CMD	WS_PSP_VALUE
	DEF_CMD	WS_CONDITION2_OFF
	DEF_CMD	WS_VANISH_ON_OFF
	DEF_CMD	WS_TOKUSEI_CHECK
	DEF_CMD	WS_RANDOM_GET
	DEF_CMD	WS_VALUE_WORK
	DEF_CMD	WS_PSP_VALUE_WORK
	DEF_CMD	WS_BRANCH
	DEF_CMD	WS_GOSUB
	DEF_CMD	WS_GOSUB_WORK
	DEF_CMD	WS_OUMU_CHECK
	DEF_CMD	WS_KUROIKIRI
	DEF_CMD	WS_KEEP_ON
	DEF_CMD	WS_KEEP_OFF
	DEF_CMD	WS_STATUS_SET
	DEF_CMD	WS_TRAINER_MESSAGE
	DEF_CMD	WS_OKODUKAI_CALC
	DEF_CMD	WS_STATUS_EFFECT
	DEF_CMD	WS_STATUS_EFFECT2
	DEF_CMD	WS_STATUS_EFFECT_WORK
	DEF_CMD	WS_MODOSU_MESSAGE
	DEF_CMD	WS_KURIDASU_MESSAGE
	DEF_CMD	WS_ENCOUNT_MESSAGE
	DEF_CMD	WS_ENCOUNT_KURIDASU_MESSAGE
	DEF_CMD	WS_TRAINER_MESSAGE_WORK
	DEF_CMD	WS_TEXTURE
	DEF_CMD	WS_IF_WORK
	DEF_CMD	WS_IF_PSP_WORK
	DEF_CMD	WS_KOBAN_CHECK
	DEF_CMD	WS_HIKARINOKABE
	DEF_CMD	WS_RIHUREKUTAA
	DEF_CMD	WS_SIROIKIRI
	DEF_CMD	WS_ICHIGEKI
	DEF_CMD	WS_DAMAGE_DIV
	DEF_CMD	WS_DAMAGE_DIV_WORK
	DEF_CMD	WS_MONOMANE
	DEF_CMD	WS_YUBIWOHURU
	DEF_CMD	WS_KANASIBARI
	DEF_CMD	WS_COUNTER
	DEF_CMD	WS_MIRROR_CORT
	DEF_CMD	WS_ENCORE
	DEF_CMD	WS_TEXTURE2
	DEF_CMD	WS_SKETCH
	DEF_CMD	WS_NEGOTO
	DEF_CMD	WS_JITABATA
	DEF_CMD	WS_URAMI
	DEF_CMD	WS_IYASINOSUZU
	DEF_CMD	WS_DOROBOU
	DEF_CMD	WS_GUARD_SUCCESS_CHECK
	DEF_CMD	WS_MIGAWARI
	DEF_CMD	WS_HUKITOBASI
	DEF_CMD	WS_HENSIN
	DEF_CMD	WS_MAKIBISI
	DEF_CMD	WS_MAKIBISI_CHECK
	DEF_CMD	WS_HOROBINOUTA
	DEF_CMD	WS_CLIENT_NO_GET_AGI
	DEF_CMD	WS_CLIENT_SET_MAX_LOOP
	DEF_CMD	WS_TENKOU_DAMAGE
	DEF_CMD	WS_KOROGARU
	DEF_CMD	WS_RENZOKUGIRI
	DEF_CMD	WS_MEROMERO
	DEF_CMD	WS_SHINPI
	DEF_CMD	WS_PRESENT
	DEF_CMD	WS_MAGNITUDE
	DEF_CMD	WS_RESHUFFLE_CHECK
	DEF_CMD	WS_KOUSOKUSPIN
	DEF_CMD	WS_WEATHER_KAIFUKU
	DEF_CMD	WS_MEZAMERU_POWER
	DEF_CMD	WS_JIKOANJI
	DEF_CMD	WS_MIRAIYOCHI
	DEF_CMD	WS_HITCHECK
	DEF_CMD	WS_TELEPORT
	DEF_CMD	WS_HUKURODATAKI
	DEF_CMD	WS_KONOYUBITOMARE
	DEF_CMD	WS_TEDASUKE
	DEF_CMD	WS_TRICK
	DEF_CMD	WS_NEGAIGOTO
	DEF_CMD	WS_NEKONOTE
	DEF_CMD	WS_MAGIC_CORT
	DEF_CMD	WS_MAGIC_CORT_A_D
	DEF_CMD	WS_REVENGE
	DEF_CMD	WS_KAWARAWARI
	DEF_CMD	WS_AKUBI
	DEF_CMD	WS_HATAKIOTOSU
	DEF_CMD	WS_HUNKA
	DEF_CMD	WS_HUUIN
	DEF_CMD	WS_ONNEN
	DEF_CMD	WS_YOKODORI
	DEF_CMD	WS_KETAGURI
	DEF_CMD	WS_WEATHER_BALL
	DEF_CMD	WS_OIUCHI_CHECK
	DEF_CMD	WS_TYPE_CHECK
	DEF_CMD	WS_OTF_CHECK
	DEF_CMD	WS_OTF_SET
	DEF_CMD	WS_GIROBALL
	DEF_CMD	WS_METALMIRROR
	DEF_CMD	WS_TAMEUCHI
	DEF_CMD	WS_KIRIHUDA
	DEF_CMD	WS_SIBORITORU
	DEF_CMD	WS_SAKIDORI
	DEF_CMD	WS_MANEKKO
	DEF_CMD	WS_OSIOKI
	DEF_CMD	WS_HUIUCHI
	DEF_CMD	WS_SIDE_CONDITION_CHECK
	DEF_CMD	WS_FEINT
	DEF_CMD	WS_SURIKOMI
	DEF_CMD	WS_TOTTEOKI
	DEF_CMD	WS_DOKUBISI
	DEF_CMD	WS_DOKUBISI_CHECK
	DEF_CMD	WS_KATAYABURI_TOKUSEI_CHECK
	DEF_CMD	WS_SIDE_CHECK
	DEF_CMD	WS_MONOHIROI
	DEF_CMD	WS_TRICKROOM
	DEF_CMD	WS_WAZA_OUT_CHECK
	DEF_CMD	WS_SOUBI_CHECK
	DEF_CMD	WS_SOUBI_EQP_GET
	DEF_CMD	WS_SOUBI_ATK_GET
	DEF_CMD	WS_HOGOSYOKU
	DEF_CMD	WS_SHIZENNOCHIKARA
	DEF_CMD	WS_HIMITSUNOCHIKARA
	DEF_CMD	WS_SHIZENNOMEGUMI
	DEF_CMD	WS_TSUIBAMU
	DEF_CMD	WS_NAGETSUKERU
	DEF_CMD	WS_YES_NO_SELECT
	DEF_CMD	WS_YES_NO_SELECT_WAIT
	DEF_CMD	WS_POKEMON_LIST_CALL
	DEF_CMD	WS_POKEMON_LIST_CALL_WAIT
	DEF_CMD	WS_WIN_LOSE_SET
	DEF_CMD	WS_STEALTHROCK_CHECK
	DEF_CMD	WS_ADD_STATUS_CHECK
	DEF_CMD	WS_OSYABERI
	DEF_CMD	WS_WAZA_PARAM_GET
	DEF_CMD	WS_MOSAIC
	DEF_CMD	WS_FORM_CHG
	DEF_CMD	WS_BG_CHG
	DEF_CMD	WS_STATUS_RECOVER
	DEF_CMD	WS_ESCAPE_ACT_CHECK
	DEF_CMD	WS_BALL_GAUGE_ENCOUNT_SET
	DEF_CMD	WS_BALL_GAUGE_ENCOUNT_OUT
	DEF_CMD	WS_BALL_GAUGE_SET
	DEF_CMD	WS_BALL_GAUGE_OUT
	DEF_CMD	WS_BALL_GAUGE_RESOURCE_LOAD
	DEF_CMD	WS_BALL_GAUGE_RESOURCE_DELETE
	DEF_CMD	WS_INC_RECORD
	DEF_CMD	WS_CHR_POP
	DEF_CMD	WS_WAZA_HIT_TOKUSEI_CHECK
	DEF_CMD	WS_SS_TO_OAM_CALL
	DEF_CMD	WS_OAM_TO_SS_CALL
	DEF_CMD	WS_ZENMETSU_CHECK
	DEF_CMD	WS_TUBOWOTUKU
	DEF_CMD	WS_KILL_ITEM
	DEF_CMD	WS_RECYCLE
	DEF_CMD	WS_WAZA_HIT_SOUBI_ITEM_CHECK
	DEF_CMD	WS_WIN_LOSE_MESSAGE
	DEF_CMD	WS_ESCAPE_MESSAGE
	DEF_CMD	WS_GIVEUP_MESSAGE
	DEF_CMD	WS_HP1_CHECK
	DEF_CMD	WS_SIZENKAIHUKU_CHECK
	DEF_CMD	WS_MIGAWARI_CHECK
	DEF_CMD	WS_NOOTENKI_CHECK
	DEF_CMD	WS_DIR_CLIENT_GET
	DEF_CMD	WS_WAZA_HIT_SOUBI_ITEM_CHECK_TONBOGAERI
	DEF_CMD	WS_MIGAWARI_CHR_SET
	DEF_CMD	WS_WAZAKOUKA_SE
	DEF_CMD	WS_BGM_PLAY
	DEF_CMD	WS_SAFARI_END_CHECK

	DEF_CMD	WS_SEQ_END

//命令マクロ定義
//=============================================================================
/**
 *	エンカウントエフェクトセット
 */
//=============================================================================
	.macro	ENCOUNT_EFFECT
	.long	WS_ENCOUNT_EFFECT
	.endm

//=============================================================================
/**
 *	ポケモンエンカウントセット
 *
 *	@param	side	ポケモンをセットする側
 */
//=============================================================================
	.macro	POKEMON_ENCOUNT	side
	.long	WS_POKEMON_ENCOUNT
	.long	\side
	.endm

//=============================================================================
/**
 *	ポケモン登場エフェクトセット（エンカウント時専用）
 *
 *	@param	side	ポケモンをセットする側
 */
//=============================================================================
	.macro	POKEMON_ENCOUNT_APPEAR		side
	.long	WS_POKEMON_ENCOUNT_APPEAR
	.long	\side
	.endm

//=============================================================================
/**
 *	ポケモン登場エフェクトセット
 *
 *	@param	side	ポケモンをセットする側
 */
//=============================================================================
	.macro	POKEMON_APPEAR	side
	.long	WS_POKEMON_APPEAR
	.long	\side
	.endm

//=============================================================================
/**
 *	ポケモン引っ込めるエフェクトセット
 *
 *	@param	side	エフェクトをセットする側
 */
//=============================================================================
	.macro	POKEMON_RETURN	side
	.long	WS_POKEMON_RETURN
	.long	\side
	.endm

//=============================================================================
/**
 *	ポケモンを削除
 *
 *	@param	side	削除する側
 */
//=============================================================================
	.macro	POKEMON_DELETE	side
	.long	WS_POKEMON_DELETE
	.long	\side
	.endm

//=============================================================================
/**
 *	トレーナーエンカウントセット
 *
 *	@param	side	トレーナーをセットする側
 */
//=============================================================================
	.macro	TRAINER_ENCOUNT	side
	.long	WS_TRAINER_ENCOUNT
	.long	\side
	.endm

//=============================================================================
/**
 *	トレーナーボール投げつつフレームアウト
 *
 *	@param	side	エフェクトを指示する側
 *	@param	type	エフェクトタイプ
 */
//=============================================================================
	.macro	TRAINER_THROW	side,type
	.long	WS_TRAINER_THROW
	.long	\side
	.long	\type
	.endm

//=============================================================================
/**
 *	トレーナー画面外エフェクトセット
 *
 *	@param	side	エフェクトを指示する側
 */
//=============================================================================
	.macro	TRAINER_OUT	side
	.long	WS_TRAINER_OUT
	.long	\side
	.endm

//=============================================================================
/**
 *	トレーナー画面内エフェクトセット
 *
 *	@param	side	エフェクトを指示する側
 */
//=============================================================================
	.macro	TRAINER_IN	side,pos
	.long	WS_TRAINER_IN
	.long	\side
	.long	\pos
	.endm

//=============================================================================
/**
 *	タッチパネルにトレーナーBGをSlideIn
 */
//=============================================================================
	.macro	TRAINER_BG_SLIDEIN
	.long	WS_TRAINER_BG_SLIDEIN
	.endm

//=============================================================================
/**
 *	HPゲージ画面INエフェクトセット
 *
 *	@param	side	エフェクトを指示する側
 */
//=============================================================================
	.macro	HP_GAUGE_IN	side
	.long	WS_HP_GAUGE_IN
	.long	\side
	.endm

//=============================================================================
/**
 *	HPゲージ画面INエフェクトセット
 *
 *	@param	side	エフェクトを指示する側
 */
//=============================================================================
	.macro	HP_GAUGE_IN_WAIT_SET	side
	.long	WS_HP_GAUGE_IN_WAIT
	.long	\side
	.endm

//=============================================================================
/**
 *	HPゲージ画面OUTエフェクトセット
 *
 *	@param	side	エフェクトを指示する側
 */
//=============================================================================
	.macro	HP_GAUGE_OUT	side
	.long	WS_HP_GAUGE_OUT
	.long	\side
	.endm

//=============================================================================
/**
 *	処理の終了までサーバが待つ
 */
//=============================================================================
	.macro	SERVER_WAIT
	.long	WS_SERVER_WAIT
	.endm

//=============================================================================
/**
 *	ダメージ計算マクロ
 *
 *	ダメージ計算した後、サーバのダメージワークに代入
 */
//=============================================================================
	.macro	DAMAGE_CALC
	.long	WS_DAMAGE_CALC
	.endm

//=============================================================================
/**
 *	ダメージ計算マクロ（ダメージロス計算をしない）
 *
 *	ダメージ計算した後、サーバのダメージワークに代入
 */
//=============================================================================
	.macro	DAMAGE_CALC_NO_LOSS
	.long	WS_DAMAGE_CALC_NO_LOSS
	.endm

//=============================================================================
/**
 *	技の攻撃メッセージを表示
 */
//=============================================================================
	.macro	ATTACK_MESSAGE
	.long	WS_ATTACK_MESSAGE
	.endm

//=============================================================================
/**
 *	メッセージを表示
 *
 *	@param	msg_id			表示するメッセージID
 *	@param	tag				表示するメッセージのタグ
 *	@param	para1～para6	タグに付随するパラメータ
 */
//=============================================================================
	.macro	MESSAGE	msg_id,tag,para1,para2,para3,para4,para5,para6
	.long	WS_MESSAGE
	.long	\msg_id
	.long	\tag
.if \tag<TAG_NONE_DIR
.elseif \tag<TAG_NICK_NICK
	.long	\para1
.elseif \tag<TAG_NICK_NICK_WAZA
	.long	\para1
	.long	\para2
.elseif \tag<TAG_NICK_TOKU_NICK_WAZA
	.long	\para1
	.long	\para2
	.long	\para3
.elseif \tag<TAG_TRTYPE_TRNAME_NICKx2
	.long	\para1
	.long	\para2
	.long	\para3
	.long	\para4
.else
	.long	\para1
	.long	\para2
	.long	\para3
	.long	\para4
	.long	\para5
	.long	\para6
.endif
	.endm

//=============================================================================
/**
 *	メッセージを表示
 *
 *	@param	msg_id			表示するメッセージID
 *	@param	tag				表示するメッセージのタグ
 *	@param	para1～para6	タグに付随するパラメータ
 */
//=============================================================================
	.macro	MESSAGE_NO_DIR	msg_id,tag,para1,para2,para3,para4,para5,para6
	.long	WS_MESSAGE_NO_DIR
	.long	\msg_id
	.long	\tag
.if \tag<TAG_NONE_DIR
.elseif \tag<TAG_NICK_NICK
	.long	\para1
.elseif \tag<TAG_NICK_NICK_WAZA
	.long	\para1
	.long	\para2
.elseif \tag<TAG_NICK_TOKU_NICK_WAZA
	.long	\para1
	.long	\para2
	.long	\para3
.elseif \tag<TAG_TRTYPE_TRNAME_NICKx2
	.long	\para1
	.long	\para2
	.long	\para3
	.long	\para4
.else
	.long	\para1
	.long	\para2
	.long	\para3
	.long	\para4
	.long	\para5
	.long	\para6
.endif
	.endm

//=============================================================================
/**
 *	メッセージを表示（MESSAGE_PARAMで設定された情報を元に表示）
 */
//=============================================================================
	.macro	MESSAGE_WORK
	.long	WS_MESSAGE_WORK
	.endm

//=============================================================================
/**
 *	メッセージ表示用パラメータ生成
 *
 *	@param	msg_id			表示するメッセージID
 *	@param	tag				表示するメッセージのタグ
 *	@param	para1～para6	タグに付随するパラメータ
 */
//=============================================================================
	.macro	MESSAGE_PARAM	msg_id,tag,para1,para2,para3,para4,para5,para6
	.long	WS_MESSAGE_PARAM
	.long	\msg_id
	.long	\tag
.if \tag<TAG_NONE_DIR
.elseif \tag<TAG_NICK_NICK
	.long	\para1
.elseif \tag<TAG_NICK_NICK_WAZA
	.long	\para1
	.long	\para2
.elseif \tag<TAG_NICK_TOKU_NICK_WAZA
	.long	\para1
	.long	\para2
	.long	\para3
.elseif \tag<TAG_TRTYPE_TRNAME_NICKx2
	.long	\para1
	.long	\para2
	.long	\para3
	.long	\para4
.else
	.long	\para1
	.long	\para2
	.long	\para3
	.long	\para4
	.long	\para5
	.long	\para6
.endif
	.endm

//=============================================================================
/**
 *	メッセージを表示
 *
 *	@param	side			DIRチェックする側を指定
 *	@param	msg_id			表示するメッセージID
 *	@param	tag				表示するメッセージのタグ
 *	@param	para1～para6	タグに付随するパラメータ
 */
//=============================================================================
	.macro	MESSAGE_DIR		side,msg_id,tag,para1,para2,para3,para4,para5,para6
	.long	WS_MESSAGE_DIR
	.long	\side
	.long	\msg_id
	.long	\tag
.if \tag<TAG_NONE_DIR
.elseif \tag<TAG_NICK_NICK
	.long	\para1
.elseif \tag<TAG_NICK_NICK_WAZA
	.long	\para1
	.long	\para2
.elseif \tag<TAG_NICK_TOKU_NICK_WAZA
	.long	\para1
	.long	\para2
	.long	\para3
.elseif \tag<TAG_TRTYPE_TRNAME_NICKx2
	.long	\para1
	.long	\para2
	.long	\para3
	.long	\para4
.else
	.long	\para1
	.long	\para2
	.long	\para3
	.long	\para4
	.long	\para5
	.long	\para6
.endif
	.endm

//=============================================================================
/**
 *	技エフェクトを表示
 */
//=============================================================================
	.macro	WAZA_EFFECT		side
	.long	WS_WAZA_EFFECT
	.long	\side
	.endm

//=============================================================================
/**
 *	技エフェクトを表示
 */
//=============================================================================
	.macro	WAZA_EFFECT2	side,attack,defence
	.long	WS_WAZA_EFFECT2
	.long	\side
	.long	\attack
	.long	\defence
	.endm

//=============================================================================
/**
 *	ポケモンを点滅させる
 *
 *	@param	side	ポケモンを点滅する側
 */
//=============================================================================
	.macro	POKEMON_BLINK	side
	.long	WS_POKEMON_BLINK
	.long	\side
	.endm

//=============================================================================
/**
 *	HP計算をする
 *
 *	@param	side	計算する側
 */
//=============================================================================
	.macro	HP_CALC	side
	.long	WS_HP_CALC
	.long	\side
	.endm

//=============================================================================
/**
 *	HPゲージ計算をする
 *
 *	@param	side	計算する側
 */
//=============================================================================
	.macro	HP_GAUGE_CALC	side
	.long	WS_HP_GAUGE_CALC
	.long	\side
	.endm

//=============================================================================
/**
 *	気絶チェックをする
 *
 *	@param	side	チェックする側
 */
//=============================================================================
	.macro	KIZETSU_CHECK	side
	.long	WS_KIZETSU_CHECK
	.long	\side
	.endm

//=============================================================================
/**
 *	気絶エフェクト
 */
//=============================================================================
	.macro	KIZETSU_EFFECT
	.long	WS_KIZETSU_EFFECT
	.endm

//=============================================================================
/**
 *	指定分WAIT
 *
 *	@param	wait	WAIT_TIME（１につき、1/30秒）
 */
//=============================================================================
	.macro	WAIT	wait
	.long	WS_WAIT
	.long	\wait
	.endm

//=============================================================================
/**
 *	指定SEを鳴らす
 *
 *	@param	side	鳴らす側
 *	@param	se_no	鳴らすSE
 */
//=============================================================================
	.macro	SE_PLAY		side,se_no
	.long	WS_SE_PLAY
	.long	\side
	.long	\se_no
	.endm

//=============================================================================
/**
 *	条件分岐マクロ
 *
 *	@param	act		条件分岐の種類
 *	@param	src		比較される値（ワークに対するインデックス）
 *	@param	dest	比較する値（直値4バイト）
 *	@param	adrs	条件と一致したときの飛び先
 */
//=============================================================================
	.macro	IF	act,src,dest,adrs
	.long	WS_IF
	.long	\act
	.long	\src
	.long	\dest
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	条件分岐マクロ（PokemonServerParam構造体のメンバ限定）
 *
 *	@param	act		条件分岐の種類
 *	@param	side	client_no
 *	@param	src		比較される値（構造体メンバに対するインデックス）
 *	@param	dest	比較する値（直値4バイト）
 *	@param	adrs	条件と一致したときの飛び先
 */
//=============================================================================
	.macro	IF_PSP	act,side,src,dest,adrs
	.long	WS_IF_PSP
	.long	\act
	.long	\side
	.long	\src
	.long	\dest
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	画面フェードアウト
 */
//=============================================================================
	.macro	FADE_OUT
	.long	WS_FADE_OUT
	.endm

//=============================================================================
/**
 *	SUBシーケンスジャンプ（SUB_SEQナンバーを指定してジャンプ）
 */
//=============================================================================
	.macro	JUMP	be_seq_no
	.long	WS_JUMP
	.long	\be_seq_no
	.endm

//=============================================================================
/**
 *	戦闘効果シーケンスジャンプ（技NoからWazaTableDataのbattleeffectを取り出してジャンプ）
 */
//=============================================================================
	.macro	JUMP_BE_SEQ
	.long	WS_JUMP_BE_SEQ
	.endm

//=============================================================================
/**
 *	戦闘効果シーケンスジャンプ（sp->waza_workからWazaTableDataのbattleeffectを取り出してジャンプ）
 *
 *	@param	flag	動作フラグ（JWW_FLAG_NORMAL：通常動作　JWW_FLAG_SET_DEFENCE：すでにDefenceはセット済み）
 */
//=============================================================================
	.macro	JUMP_WAZA_WORK		flag
	.long	WS_JUMP_WAZA_WORK
	.long	\flag
	.endm

//=============================================================================
/**
 *	クリティカルヒットチェック
 */
//=============================================================================
	.macro	CRITICAL_CHECK
	.long	WS_CRITICAL_CHECK
	.endm

//=============================================================================
/**
 *	経験値ゲットチェック処理
 *
 *	@param	adrs	経験値ゲット処理をしないときのとび先
 */
//=============================================================================
	.macro	GET_EXP_CHECK	adrs
	.long	WS_GET_EXP_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	経験値ゲット初期化処理
 */
//=============================================================================
	.macro	GET_EXP_INIT
	.long	WS_GET_EXP_INIT
	.endm

//=============================================================================
/**
 *	経験値ゲット処理
 */
//=============================================================================
	.macro	GET_EXP
	.long	WS_GET_EXP
	.endm

//=============================================================================
/**
 *	経験値ゲットループ処理
 *
 *	@param	adrs	経験値ゲット処理を繰り返すときのとび先
 */
//=============================================================================
	.macro	GET_EXP_LOOP	adrs
	.long	WS_GET_EXP_LOOP
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ポケモンリスト処理
 */
//=============================================================================
	.macro	POKEMON_LIST
	.long	WS_POKEMON_LIST
	.endm

//=============================================================================
/**
 *	ポケモンリストからの帰りを待つ
 */
//=============================================================================
	.macro	POKEMON_LIST_WAIT
	.long	WS_POKEMON_LIST_WAIT
	.endm

//=============================================================================
/**
 *	ポケモン入れ替え処理（入れ替えたポケモンのデータをpspにロード）
 *
 *	@param	side	データをロードする側
 */
//=============================================================================
	.macro	POKEMON_RESHUFFLE	side
	.long	WS_POKEMON_RESHUFFLE
	.long	\side
	.endm

//=============================================================================
/**
 *	CLIENT_STATUSのRESHUFFLE_FLAGを見てループするか判断
 *
 *	@param	adrs	ループするときのとび先
 */
//=============================================================================
	.macro	POKEMON_RESHUFFLE_LOOP	adrs
	.long	WS_POKEMON_RESHUFFLE_LOOP
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ポケモン捕獲シーケンス初期化
 *
 *	@param	flag	捕獲シーケンスの種類（GET_NORMAL:通常捕獲　GET_SAFARI:サファリゾーンorポケパーク）
 */
//=============================================================================
	.macro	POKEMON_GET_INIT	flag
	.long	WS_POKEMON_GET_INIT
	.long	\flag
	.endm

//=============================================================================
/**
 *	ポケモン捕獲シーケンス
 */
//=============================================================================
	.macro	POKEMON_GET
	.long	WS_POKEMON_GET
	.endm

//=============================================================================
/**
 *	連続攻撃時のループ回数を決定
 *
 *	@param	para	0:ループする回数２～５　0以外:指定された回数
 *	@param	flag	ループした時のHITCHECKをどうするか（HITCHECK_ON：チェックする　HITCHECK_OFF：しない）
 */
//=============================================================================
	.macro	RENZOKU	para,flag
	.long	WS_RENZOKU
	.long	\para
	.long	\flag
	.endm

//=============================================================================
/**
 *	変数操作
 *
 *	@param	act		操作パラメータ（battle_common.hに定義）
 *	@param	src		操作対象変数（battle_common.hに定義）
 *	@param	value	操作する値
 */
//=============================================================================
	.macro	VALUE	act,src,value
	.long	WS_VALUE
	.long	\act
	.long	\src
	.long	\value
	.endm

//=============================================================================
/**
 *	AbirityCountを操作する
 *
 *	@param	adrs1	操作出来なかったときのとび先を指定（直接、特性）
 *	@param	adrs2	操作出来なかったときのとび先を指定（間接）
 *	@param	adrs3	みがわりなどで防がれた時のとび先を指定
 */
//=============================================================================
	.macro	ABICNT_CALC		adrs1,adrs2,adrs3
	.long	WS_ABICNT_CALC
	.long	(\adrs1-.)/4-3
	.long	(\adrs2-.)/4-2
	.long	(\adrs3-.)/4-1
	.endm

//=============================================================================
/**
 *	変数操作（PokemonServerParam限定）
 *
 *	@param	act		操作パラメータ（battle_common.hに定義）
 *	@param	side	操作するClient（battle_common.hに定義）
 *	@param	src		操作対象変数（battle_common.hに定義）
 *	@param	value	操作する値
 */
//=============================================================================
	.macro	PSP_VALUE	act,side,src,value
	.long	WS_PSP_VALUE
	.long	\act
	.long	\side
	.long	\src
	.long	\value
	.endm

//=============================================================================
/**
 *	psp構造体のcondition2フラグの削除要求
 *
 *	@param	side	要求するClient（battle_common.hに定義）
 *	@param	value	要求するフラグ
 */
//=============================================================================
	.macro	CONDITION2_OFF	side,value
	.long	WS_CONDITION2_OFF
	.long	\side
	.long	\value
	.endm

//=============================================================================
/**
 *	ポケモン表示のON/OFF
 *
 *	@param	side	ON/OFFするClient（battle_common.hに定義）
 *	@param	sw		ON/OFFフラグ
 */
//=============================================================================
	.macro	VANISH_ON_OFF		side,sw
	.long	WS_VANISH_ON_OFF
	.long	\side
	.long	\sw
	.endm

//=============================================================================
/**
 *	特性のチェック
 *
 *	@param	side	チェックするClient（battle_common.hに定義）
 *	@param	tokusei	チェックする特性
 *	@param	adrs	sideで指定したClientがtokuseiで指定した特性を持っていたときの飛び先
 */
//=============================================================================
	.macro	TOKUSEI_CHECK	flag,side,tokusei,adrs
	.long	WS_TOKUSEI_CHECK
	.long	\flag
	.long	\side
	.long	\tokusei
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/*
 *	乱数の取得（sp->calc_workに格納）
 *
 *	@param	range	０からいくつまでの幅にするか？
 *	@param	ofs		取得した乱数に対するオフセット(range=3でofs=2なら、２～５の乱数を取得する）
 */
//=============================================================================
	.macro	RANDOM_GET	range,ofs
	.long	WS_RANDOM_GET
	.long	\range
	.long	\ofs
	.endm

//=============================================================================
/**
 *	変数操作（直値ではなく別のワークから）
 *
 *	@param	act		操作パラメータ（battle_common.hに定義）
 *	@param	src		操作対象変数（battle_common.hに定義）
 *	@param	dest	操作する値が格納されたワークのインデックス
 */
//=============================================================================
	.macro	VALUE_WORK	act,src,dest
	.long	WS_VALUE_WORK
	.long	\act
	.long	\src
	.long	\dest
	.endm

//=============================================================================
/**
 *	変数操作（PokemonServerParam限定、直値ではなく別のワークから）
 *
 *	@param	act		操作パラメータ（battle_common.hに定義）
 *	@param	side	操作するClient（battle_common.hに定義）
 *	@param	src		操作対象変数（battle_common.hに定義）
 *	@param	dest	操作する値が格納されたワークのインデックス
 */
//=============================================================================
	.macro	PSP_VALUE_WORK	act,side,src,dest
	.long	WS_PSP_VALUE_WORK
	.long	\act
	.long	\side
	.long	\src
	.long	\dest
	.endm

//=============================================================================
/**
 *	同一シーケンスデータ内でのジャンプ（アセンブラのブランチ命令）
 *
 *	@param	adrs	飛び先
 */
//=============================================================================
	.macro	BRANCH	adrs
	.long	WS_BRANCH
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	サブルーチンジャンプ（BASICのGOSUB命令）
 *
 *	@param	seq_no	飛び先シーケンスナンバー
 */
//=============================================================================
	.macro	GOSUB	seq_no
	.long	WS_GOSUB
	.long	\seq_no
	.endm

//=============================================================================
/**
 *	サブルーチンジャンプ（BASICのGOSUB命令）ワークの中身を参照
 *
 *	@param	para	飛び先シーケンスナンバーが格納されたワークへのインデックス
 */
//=============================================================================
	.macro	GOSUB_WORK	para
	.long	WS_GOSUB_WORK
	.long	\para
	.endm

//=============================================================================
/**
 *	オウムがえしチェック（オウム返し失敗の時はそのまま次のシーケンスへ）
 */
//=============================================================================
	.macro	OUMU_CHECK
	.long	WS_OUMU_CHECK
	.endm

//=============================================================================
/**
 *	くろいきりの効果発動
 */
//=============================================================================
	.macro	KUROIKIRI
	.long	WS_KUROIKIRI
	.endm

//=============================================================================
/**
 *	ため系のフラグを立てる
 *
 *	@param	side	操作するClient（battle_common.hに定義）
 */
//=============================================================================
	.macro	KEEP_ON		side
	.long	WS_KEEP_ON
	.long	\side
	.endm

//=============================================================================
/**
 *	ため系のフラグを落とす
 *
 *	@param	side	操作するClient（battle_common.hに定義）
 */
//=============================================================================
	.macro	KEEP_OFF		side
	.long	WS_KEEP_OFF
	.long	\side
	.endm

//=============================================================================
/**
 *	状態異常アイコンをセット
 *
 *	@param	side	セットするClient（battle_common.hに定義）
 *	@param	status	状態異常No
 */
//=============================================================================
	.macro	STATUS_SET	side,status
	.long	WS_STATUS_SET
	.long	\side
	.long	\status
	.endm

//=============================================================================
/**
 *	トレーナーメッセージを表示
 *
 *	@param	side	表示するするClient（battle_common.hに定義）
 *	@param	type	メッセージタイプ（tr_tool.hに定義）
 */
//=============================================================================
	.macro	TRAINER_MESSAGE		side,type
	.long	WS_TRAINER_MESSAGE
	.long	\side
	.long	\type
	.endm

//=============================================================================
/**
 *	おこづかい計算をする
 */
//=============================================================================
	.macro	OKODUKAI_CALC
	.long	WS_OKODUKAI_CALC
	.endm

//=============================================================================
/**
 *	状態異常エフェクトをセット
 *
 *	@param	side	表示するするClient（battle_common.hに定義）
 *	@param	type	セットする状態異常の種類（battle_tool.hに定義）
 */
//=============================================================================
	.macro	STATUS_EFFECT		side,status
	.long	WS_STATUS_EFFECT
	.long	\side
	.long	\status
	.endm

//=============================================================================
/**
 *	状態異常エフェクトをセット（AttackとDefenceを指定）
 *
 *	@param	side1	表示するするClient（battle_common.hに定義）
 *	@param	side2	表示するするClient（battle_common.hに定義）
 *	@param	type	セットする状態異常の種類（battle_tool.hに定義）
 */
//=============================================================================
	.macro	STATUS_EFFECT2		side1,side2,type
	.long	WS_STATUS_EFFECT2
	.long	\side1
	.long	\side2
	.long	\type
	.endm

//=============================================================================
/**
 *	状態異常エフェクトをセット
 *
 *	@param	side	表示するするClient（battle_common.hに定義）
 *	@param	type	セットする状態異常の種類（battle_tool.hに定義）
 */
//=============================================================================
	.macro	STATUS_EFFECT_WORK	side,status
	.long	WS_STATUS_EFFECT_WORK
	.long	\side
	.long	\status
	.endm

//=============================================================================
/**
 *	戻すメッセージを表示
 *
 *	@param	side	表示するするClient（battle_common.hに定義）
 */
//=============================================================================
	.macro	MODOSU_MESSAGE		side
	.long	WS_MODOSU_MESSAGE
	.long	\side
	.endm

//=============================================================================
/**
 *	繰り出すメッセージを表示
 *
 *	@param	side	表示するするClient（battle_common.hに定義）
 */
//=============================================================================
	.macro	KURIDASU_MESSAGE	side
	.long	WS_KURIDASU_MESSAGE
	.long	\side
	.endm

//=============================================================================
/**
 *	エンカウントメッセージを表示
 *
 *	@param	side	表示するするClient（battle_common.hに定義）
 */
//=============================================================================
	.macro	ENCOUNT_MESSAGE		side
	.long	WS_ENCOUNT_MESSAGE
	.long	\side
	.endm

//=============================================================================
/**
 *	エンカウント時の繰り出しメッセージを表示
 *
 *	@param	side	表示するするClient（battle_common.hに定義）
 */
//=============================================================================
	.macro	ENCOUNT_KURIDASU_MESSAGE		side
	.long	WS_ENCOUNT_KURIDASU_MESSAGE
	.long	\side
	.endm

//=============================================================================
/**
 *	トレーナーメッセージを表示（タイプはワーク指定）
 *
 *	@param	side	表示するするClient（battle_common.hに定義）
 */
//=============================================================================
	.macro	TRAINER_MESSAGE_WORK	side
	.long	WS_TRAINER_MESSAGE_WORK
	.long	\side
	.endm

//=============================================================================
/**
 *	テクスチャー効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	TEXTURE		adrs
	.long	WS_TEXTURE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	条件分岐マクロ
 *
 *	@param	act		条件分岐の種類
 *	@param	src		比較される値（ワークに対するインデックス）
 *	@param	dest	比較する値（ワークに対するインデックス）
 *	@param	adrs	条件と一致したときの飛び先
 */
//=============================================================================
	.macro	IF_WORK	act,src,dest,adrs
	.long	WS_IF_WORK
	.long	\act
	.long	\src
	.long	\dest
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	条件分岐マクロ（PokemonServerParam構造体のメンバ限定）
 *
 *	@param	act		条件分岐の種類
 *	@param	side	client_no
 *	@param	src		比較される値（構造体メンバに対するインデックス）
 *	@param	dest	比較する値（ワークに対するインデックス）
 *	@param	adrs	条件と一致したときの飛び先
 */
//=============================================================================
	.macro	IF_PSP_WORK	act,side,src,dest,adrs
	.long	WS_IF_PSP_WORK
	.long	\act
	.long	\side
	.long	\src
	.long	\dest
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	こばんカウンタをチェックしてお金を取得
 */
//=============================================================================
	.macro	KOBAN_CHECK
	.long	WS_KOBAN_CHECK
	.endm

//=============================================================================
/**
 *	ひかりのかべ効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	HIKARINOKABE	adrs
	.long	WS_HIKARINOKABE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	リフレクター効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	RIHUREKUTAA		adrs
	.long	WS_RIHUREKUTAA
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	しろいきり効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	SIROIKIRI		adrs
	.long	WS_SIROIKIRI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	一撃必殺命中率計算
 */
//=============================================================================
	.macro	ICHIGEKI
	.long	WS_ICHIGEKI
	.endm

//=============================================================================
/**
 *	valueで割った結果が０の時は、1or-1にする処理が入る
 *
 *	@param	para	valueで割る対象
 *	@param	value	割る対象
 */
//=============================================================================
	.macro	DAMAGE_DIV	para,value
	.long	WS_DAMAGE_DIV
	.long	\para
	.long	\value
	.endm

//=============================================================================
/**
 *	valueで割った結果が０の時は、1or-1にする処理が入る
 *
 *	@param	para	valueで割る対象
 *	@param	value	割る対象
 */
//=============================================================================
	.macro	DAMAGE_DIV_WORK	para,value
	.long	WS_DAMAGE_DIV_WORK
	.long	\para
	.long	\value
	.endm

//=============================================================================
/**
 *	ものまね効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	MONOMANE	adrs
	.long	WS_MONOMANE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ゆびをふる効果発動
 */
//=============================================================================
	.macro	YUBIWOHURU
	.long	WS_YUBIWOHURU
	.endm

//=============================================================================
/**
 *	かなしばり効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	KANASIBARI	adrs
	.long	WS_KANASIBARI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	カウンター効果発動
 */
//=============================================================================
	.macro	COUNTER
	.long	WS_COUNTER
	.endm

//=============================================================================
/**
 *	ミラーコート効果発動
 */
//=============================================================================
	.macro	MIRROR_CORT
	.long	WS_MIRROR_CORT
	.endm

//=============================================================================
/**
 *	アンコール効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	ENCORE		adrs
	.long	WS_ENCORE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	テクスチャー２効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	TEXTURE2	adrs
	.long	WS_TEXTURE2
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	スケッチ効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	SKETCH		adrs
	.long	WS_SKETCH
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ねごと効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	NEGOTO		adrs
	.long	WS_NEGOTO
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	じたばた攻撃力計算
 */
//=============================================================================
	.macro	JITABATA
	.long	WS_JITABATA
	.endm

//=============================================================================
/**
 *	うらみ効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	URAMI		adrs
	.long	WS_URAMI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	いやしのすず効果発動
 */
//=============================================================================
	.macro	IYASINOSUZU
	.long	WS_IYASINOSUZU
	.endm

//=============================================================================
/**
 *	どろぼう効果発動
 *
 *	@param	adrs1	発動できない時のとび先
 *	@param	adrs2	発動できない時のとび先（特性）
 */
//=============================================================================
	.macro	DOROBOU		adrs1,adrs2
	.long	WS_DOROBOU
	.long	(\adrs1-.)/4-2
	.long	(\adrs2-.)/4-1
	.endm

//=============================================================================
/**
 *	まもる、こらえる等連続で使用すると成功率が下がる系のチェック
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	GUARD_SUCCESS_CHECK		adrs
	.long	WS_GUARD_SUCCESS_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	みがわり効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	MIGAWARI	adrs
	.long	WS_MIGAWARI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ふきとばし効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	HUKITOBASI		adrs
	.long	WS_HUKITOBASI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	へんしん効果発動
 */
//=============================================================================
	.macro	HENSIN
	.long	WS_HENSIN
	.endm

//=============================================================================
/**
 *	まきびし効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	MAKIBISI		adrs
	.long	WS_MAKIBISI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	まきびしダメージ効果発動
 *
 *	@param	side	チェックする側
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	MAKIBISI_CHECK		side,adrs
	.long	WS_MAKIBISI_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ほろびのうた効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	HOROBINOUTA		adrs
	.long	WS_HOROBINOUTA
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	すばやさ順でClientNoを取得
 *
 *	@param	para2	取得したClientNoを格納するワークINDEX（BUF_PARA系）
 */
//=============================================================================
	.macro	CLIENT_NO_GET_AGI	para
	.long	WS_CLIENT_NO_GET_AGI
	.long	\para
	.endm

//=============================================================================
/**
 *	指定したワークの値がclient_set_maxになるまでLOOP
 *
 *	@param	para	client_set_maxと比較する値が格納されたワークINDEX（BUF_PARA系）
 *	@param	adrs	client_set_maxになっていなかった時のとび先
 */
//=============================================================================
	.macro	CLIENT_SET_MAX_LOOP		para,adrs
	.long	WS_CLIENT_SET_MAX_LOOP
	.long	\para
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	天候ダメージ計算
 *
 *	@param	side	ダメージを受けるClientNo
 */
//=============================================================================
	.macro	TENKOU_DAMAGE	side
	.long	WS_TENKOU_DAMAGE
	.long	\side
	.endm

//=============================================================================
/**
 *	ころがるダメージ計算
 */
//=============================================================================
	.macro	KOROGARU
	.long	WS_KOROGARU
	.endm

//=============================================================================
/**
 *	れんぞくぎりダメージ計算
 */
//=============================================================================
	.macro	RENZOKUGIRI
	.long	WS_RENZOKUGIRI
	.endm

//=============================================================================
/**
 *	メロメロ追加効果
 *
 *	@param	adrs	メロメロにできない時のとび先
 */
//=============================================================================
	.macro	MEROMERO		adrs
	.long	WS_MEROMERO
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	メロメロ追加効果
 *
 *	@param	adrs	技効果が発動できない時のとび先
 */
//=============================================================================
	.macro	SHINPI			adrs
	.long	WS_SHINPI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	プレゼント追加効果
 *
 *	@param	adrs	HP回復動作時のとび先
 */
//=============================================================================
	.macro	PRESENT			adrs
	.long	WS_PRESENT
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	マグニチュードダメージ計算
 */
//=============================================================================
	.macro	MAGNITUDE
	.long	WS_MAGNITUDE
	.endm

//=============================================================================
/**
 *	入れ替えられるポケモンがいるかチェック
 *
 *	@param	side	チェックする側
 *	@param	flag	入れ替えられる時にポケモンリスト呼び出しようのフラグを立てるかどうか
 *	@param	adrs	いなかった時のとび先
 */
//=============================================================================
	.macro	RESHUFFLE_CHECK		side,flag,adrs
	.long	WS_RESHUFFLE_CHECK
	.long	\side
	.long	\flag
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	こうそくスピン追加効果
 */
//=============================================================================
	.macro	KOUSOKUSPIN
	.long	WS_KOUSOKUSPIN
	.endm

//=============================================================================
/**
 *	天候によってHP回復量が変化する追加効果
 */
//=============================================================================
	.macro	WEATHER_KAIFUKU
	.long	WS_WEATHER_KAIFUKU
	.endm

//=============================================================================
/**
 *	めざめるパワー
 */
//=============================================================================
	.macro	MEZAMERU_POWER
	.long	WS_MEZAMERU_POWER
	.endm

//=============================================================================
/**
 *	じこあんじ
 */
//=============================================================================
	.macro	JIKOANJI
	.long	WS_JIKOANJI
	.endm

//=============================================================================
/**
 *	みらいよち
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	MIRAIYOCHI		adrs
	.long	WS_MIRAIYOCHI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	命中率チェックをする
 *
 *	@param	side_a	攻撃側
 *	@param	side_d	防御側
 *	@param	waza 	チェックする技
 *	@param	adrs	外れた時のとび先
 */
//=============================================================================
	.macro	HITCHECK	side_a,side_d,waza,adrs
	.long	WS_HITCHECK
	.long	\side_a
	.long	\side_d
	.long	\waza
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	テレポート
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	TELEPORT		adrs
	.long	WS_TELEPORT
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ふくろだたき
 */
//=============================================================================
	.macro	HUKURODATAKI
	.long	WS_HUKURODATAKI
	.endm

//=============================================================================
/**
 *	このゆびとまれ
 */
//=============================================================================
	.macro	KONOYUBITOMARE
	.long	WS_KONOYUBITOMARE
	.endm

//=============================================================================
/**
 *	てだすけ
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	TEDASUKE	adrs
	.long	WS_TEDASUKE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	トリック
 *
 *	@param	adrs1	発動できない時のとび先
 *	@param	adrs2	特性で発動できない時のとび先
 */
//=============================================================================
	.macro	TRICK		adrs1,adrs2
	.long	WS_TRICK
	.long	(\adrs1-.)/4-2
	.long	(\adrs2-.)/4-1
	.endm

//=============================================================================
/**
 *	ねがいごと
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	NEGAIGOTO	adrs
	.long	WS_NEGAIGOTO
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ねこのて
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	NEKONOTE	adrs
	.long	WS_NEKONOTE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	マジックコート
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	MAGIC_CORT	adrs
	.long	WS_MAGIC_CORT
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	マジックコート発動によるAttackとDefenceの入れ替え
 */
//=============================================================================
	.macro	MAGIC_CORT_A_D
	.long	WS_MAGIC_CORT_A_D
	.endm

//=============================================================================
/**
 *	リベンジ
 */
//=============================================================================
	.macro	REVENGE
	.long	WS_REVENGE
	.endm

//=============================================================================
/**
 *	かわらわり
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	KAWARAWARI		adrs
	.long	WS_KAWARAWARI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	あくび
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	AKUBI		adrs
	.long	WS_AKUBI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	はたきおとす
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	HATAKIOTOSU		adrs
	.long	WS_HATAKIOTOSU
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ふんか威力計算
 */
//=============================================================================
	.macro	HUNKA
	.long	WS_HUNKA
	.endm

//=============================================================================
/**
 *	ふういん
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	HUUIN			adrs
	.long	WS_HUUIN
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	おんねん
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	ONNEN		adrs
	.long	WS_ONNEN
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	よこどり
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	YOKODORI		adrs
	.long	WS_YOKODORI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	けたぐり
 */
//=============================================================================
	.macro	KETAGURI
	.long	WS_KETAGURI
	.endm

//=============================================================================
/**
 *	ウエザーボール
 */
//=============================================================================
	.macro	WEATHER_BALL
	.long	WS_WEATHER_BALL
	.endm

//=============================================================================
/**
 *	おいうちチェック
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	OIUCHI_CHECK		adrs
	.long	WS_OIUCHI_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	タイプチェック
 */
//=============================================================================
	.macro	TYPE_CHECK
	.long	WS_TYPE_CHECK
	.endm

//=============================================================================
/**
 *	OneTurnFlagチェック
 *
 *	@param	side	チェックする側
 *	@param	flag	チェックするフラグ
 *	@param	value	チェックする値（ 0 or 1 ）
 *	@param	adrs	チェックする値と一致した時のとび先
 */
//=============================================================================
	.macro	OTF_CHECK	side,flag,value,adrs
	.long	WS_OTF_CHECK
	.long	\side
	.long	\flag
	.long	\value
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	OneTurnFlagセット
 *
 *	@param	side	セットする側
 *	@param	flag	セットするフラグ
 *	@param	value	セットする値（ 0 or 1 ）
 */
//=============================================================================
	.macro	OTF_SET		side,flag,value
	.long	WS_OTF_SET
	.long	\side
	.long	\flag
	.long	\value
	.endm

//=============================================================================
/**
 *	ジャイロボール
 */
//=============================================================================
	.macro	GIROBALL
	.long	WS_GIROBALL
	.endm

//=============================================================================
/**
 *	メタルミラー
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	METALMIRROR		adrs
	.long	WS_METALMIRROR
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ためうち
 */
//=============================================================================
	.macro	TAMEUCHI
	.long	WS_TAMEUCHI
	.endm

//=============================================================================
/**
 *	きりふだ
 */
//=============================================================================
	.macro	KIRIHUDA
	.long	WS_KIRIHUDA
	.endm

//=============================================================================
/**
 *	しぼりとる
 */
//=============================================================================
	.macro	SIBORITORU
	.long	WS_SIBORITORU
	.endm

//=============================================================================
/**
 *	さきどり
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	SAKIDORI		adrs
	.long	WS_SAKIDORI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	まねっこ
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	MANEKKO		adrs
	.long	WS_MANEKKO
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	おしおき
 */
//=============================================================================
	.macro	OSIOKI
	.long	WS_OSIOKI
	.endm

//=============================================================================
/**
 *	ふいうち
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	HUIUCHI			adrs
	.long	WS_HUIUCHI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	side_condition_workを調べてmodeによって指定されたとび先へJUMP
 *
 *	@param	side	調べる側
 *	@param	mode	調べるモード
 *	@param	flag	調べるside_condition_work
 *	@param	adrs	modeによってのとび先
 *
 *	mode,flagは、battle_server.hのSCC_～で定義
 */
//=============================================================================
	.macro	SIDE_CONDITION_CHECK	side,mode,flag,adrs
	.long	WS_SIDE_CONDITION_CHECK
	.long	\side
	.long	\mode
	.long	\flag
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	フェイント
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	FEINT			adrs
	.long	WS_FEINT
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	すりこみ
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	SURIKOMI		adrs
	.long	WS_SURIKOMI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	とっておき
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	TOTTEOKI		adrs
	.long	WS_TOTTEOKI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	どくびし効果発動
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	DOKUBISI		adrs
	.long	WS_DOKUBISI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	どくびし効果発動
 *
 *	@param	side	チェックする側
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	DOKUBISI_CHECK		side,adrs
	.long	WS_DOKUBISI_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	特性のチェック（かたやぶり有）
 *
 *	@param	side	チェックするClient（battle_common.hに定義）
 *	@param	tokusei	チェックする特性
 *	@param	adrs	sideで指定したClientがtokuseiで指定した特性を持っていたときの飛び先
 */
//=============================================================================
	.macro	KATAYABURI_TOKUSEI_CHECK	flag,side,tokusei,adrs
	.long	WS_KATAYABURI_TOKUSEI_CHECK
	.long	\flag
	.long	\side
	.long	\tokusei
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	自分側、相手側のチェック
 *
 *	@param	src		チェックするClient
 *	@param	dest	チェックするClient
 *	@param	adrs	チェックしたClientが同じ側だった時の飛び先
 */
//=============================================================================
	.macro	SIDE_CHECK		src,dest,adrs
	.long	WS_SIDE_CHECK
	.long	\src
	.long	\dest
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	特性ものひろいチェック
 */
//=============================================================================
	.macro	MONOHIROI
	.long	WS_MONOHIROI
	.endm

//=============================================================================
/**
 *	トリックルーム
 */
//=============================================================================
	.macro	TRICKROOM
	.long	WS_TRICKROOM
	.endm

//=============================================================================
/**
 *	対象が技を出し終えているかチェック
 *
 *	@param	side	チェックする対象
 *	@param	adrs	チェックした対象が技を出し終えていた時のとび先
 */
//=============================================================================
	.macro	WAZA_OUT_CHECK	side,adrs
	.long	WS_WAZA_OUT_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	装備アイテム効果を持っているかチェック
 *
 *	@param	flag	持っているor持っていない
 *	@param	side	チェックする対象
 *	@param	eqp		チェックする装備効果
 *	@param	adrs	flagで指定した条件の時のとび先
 */
//=============================================================================
	.macro	SOUBI_CHECK	flag,side,eqp,adrs
	.long	WS_SOUBI_CHECK
	.long	\flag
	.long	\side
	.long	\eqp
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	装備アイテムの装備効果パラメータを取得
 *
 *	@param	side	取得する対象
 *	@param	para	取得した値の格納先
 */
//=============================================================================
	.macro	SOUBI_EQP_GET		side,para
	.long	WS_SOUBI_EQP_GET
	.long	\side
	.long	\para
	.endm

//=============================================================================
/**
 *	装備アイテムの威力パラメータを取得
 *
 *	@param	side	取得する対象
 *	@param	para	取得した値の格納先
 */
//=============================================================================
	.macro	SOUBI_ATK_GET		side,para
	.long	WS_SOUBI_ATK_GET
	.long	\side
	.long	\para
	.endm

//=============================================================================
/**
 *	ほごしょく
 *
 *	@param	adrs	発動できなかった時のとび先
 */
//=============================================================================
	.macro	HOGOSYOKU		adrs
	.long	WS_HOGOSYOKU
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	しぜんのちから
 */
//=============================================================================
	.macro	SHIZENNOCHIKARA
	.long	WS_SHIZENNOCHIKARA
	.endm
	
//=============================================================================
/**
 *	ひみつのちから
 */
//=============================================================================
	.macro	HIMITSUNOCHIKARA
	.long	WS_HIMITSUNOCHIKARA
	.endm

//=============================================================================
/**
 *	しぜんのめぐみ
 *
 *	@param	adrs	発動できなかった時のとび先
 */
//=============================================================================
	.macro	SHIZENNOMEGUMI		adrs
	.long	WS_SHIZENNOMEGUMI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ついばむ
 *
 *	@param	adrs1	特性で発動できなかった時のとび先
 *	@param	adrs2	発動できなかった時のとび先
 */
//=============================================================================
	.macro	TSUIBAMU		adrs1,adrs2
	.long	WS_TSUIBAMU
	.long	(\adrs1-.)/4-2
	.long	(\adrs2-.)/4-1
	.endm

//=============================================================================
/**
 *	なげつける
 *
 *	@param	adrs	発動できなかった時のとび先
 */
//=============================================================================
	.macro	NAGETSUKERU		adrs
	.long	WS_NAGETSUKERU
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	Yes/No選択を呼び出す
 *
 *	@param	type	Yes/No選択の種類
 */
//=============================================================================
	.macro	YES_NO_SELECT		type
	.long	WS_YES_NO_SELECT
	.long	\type
	.endm

//=============================================================================
/**
 *	Yes/No選択を待つ
 *
 *	@param	adrs1	Yesの時のとび先
 *	@param	adrs2	Noの時のとび先
 */
//=============================================================================
	.macro	YES_NO_SELECT_WAIT		adrs1,adrs2
	.long	WS_YES_NO_SELECT_WAIT
	.long	(\adrs1-.)/4-2
	.long	(\adrs2-.)/4-1
	.endm

//=============================================================================
/**
 *	ポケモンリスト選択を呼び出す（入れ替え戦専用）
 */
//=============================================================================
	.macro	POKEMON_LIST_CALL
	.long	WS_POKEMON_LIST_CALL
	.endm

//=============================================================================
/**
 *	ポケモンリスト選択を待つ（入れ替え戦専用）
 *
 *	@param	adrs	入れ替えなかった時のとび先
 */
//=============================================================================
	.macro	POKEMON_LIST_CALL_WAIT		adrs
	.long	WS_POKEMON_LIST_CALL_WAIT
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	win_lose_flagのセット（通信対戦専用）
 */
//=============================================================================
	.macro	WIN_LOSE_SET
	.long	WS_WIN_LOSE_SET
	.endm

//=============================================================================
/**
 *	ステルスロックダメージ効果発動
 *
 *	@param	side	チェックする側
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	STEALTHROCK_CHECK		side,adrs
	.long	WS_STEALTHROCK_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	現在の技の追加効果発動をチェック
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	ADD_STATUS_CHECK		adrs
	.long	WS_ADD_STATUS_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	おしゃべりの追加効果発動をチェック
 *
 *	@param	adrs	発動できない時のとび先
 */
//=============================================================================
	.macro	OSYABERI		adrs
	.long	WS_OSYABERI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	技のパラメータを取得（sp->waza_no_nowのパラメータをsp->calc_workに代入）
 *
 *	@param	id	取得するパラメータのID
 */
//=============================================================================
	.macro	WAZA_PARAM_GET		id
	.long	WS_WAZA_PARAM_GET
	.long	\id
	.endm

//=============================================================================
/**
 *	ソフトウエアスプライトにモザイクをかける
 *
 *	@param	side	モザイクをかける側
 *	@param	para	モザイク段階
 *	@param	wait	モザイクをかけるスピード（0：最速）
 */
//=============================================================================
	.macro	MOSAIC		side,para,wait
	.long	WS_MOSAIC
	.long	\side
	.long	\para
	.long	\wait
	.endm

//=============================================================================
/**
 *	フォルムをチェンジ（form_noはsp->calc_workに代入）
 *
 *	@param	side	チェンジする側
 */
//=============================================================================
	.macro	FORM_CHG	side
	.long	WS_FORM_CHG
	.long	\side
	.endm

//=============================================================================
/**
 *	地形OBJをBGに書き換え
 */
//=============================================================================
	.macro	BG_CHG
	.long	WS_BG_CHG
	.endm

//=============================================================================
/**
 *	BattleWorkStatusRecoverを呼び出し
 */
//=============================================================================
	.macro	STATUS_RECOVER		side
	.long	WS_STATUS_RECOVER
	.long	\side
	.endm

//=============================================================================
/**
 *	逃げられるかチェック
 *
 *	@param	side	チェックする側
 *	@param	adrs	逃げれる時のとび先
 */
//=============================================================================
	.macro	ESCAPE_ACT_CHECK		side,adrs
	.long	WS_ESCAPE_ACT_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ボールゲージをセット（エンカウント時）
 *
 *	@param	side	セットする側
 */
//=============================================================================
	.macro	BALL_GAUGE_ENCOUNT_SET	side
	.long	WS_BALL_GAUGE_ENCOUNT_SET
	.long	\side
	.endm

//=============================================================================
/**
 *	ボールゲージを消す（エンカウント時）
 *
 *	@param	side	セットする側
 */
//=============================================================================
	.macro	BALL_GAUGE_ENCOUNT_OUT	side
	.long	WS_BALL_GAUGE_ENCOUNT_OUT
	.long	\side
	.endm

//=============================================================================
/**
 *	ボールゲージをセット
 *
 *	@param	side	セットする側
 */
//=============================================================================
	.macro	BALL_GAUGE_SET	side
	.long	WS_BALL_GAUGE_SET
	.long	\side
	.endm

//=============================================================================
/**
 *	ボールゲージを消す
 *
 *	@param	side	セットする側
 */
//=============================================================================
	.macro	BALL_GAUGE_OUT	side
	.long	WS_BALL_GAUGE_OUT
	.long	\side
	.endm

//=============================================================================
/**
 *	ボールゲージのリソースをロード
 */
//=============================================================================
	.macro	BALL_GAUGE_RESOURCE_LOAD
	.long	WS_BALL_GAUGE_RESOURCE_LOAD
	.endm

//=============================================================================
/**
 *	ボールゲージのリソースを消去
 */
//=============================================================================
	.macro	BALL_GAUGE_RESOURCE_DELETE
	.long	WS_BALL_GAUGE_RESOURCE_DELETE
	.endm

//=============================================================================
/**
 *	カウントアップ
 *
 *	@param	side	カウントアップ対象行為をした側
 *	@param	flag	カウントアップ対象行為をした側の制御フラグ
 *	@param	id		カウントアップするID
 */
//=============================================================================
	.macro	INC_RECORD	side,flag,id
	.long	WS_INC_RECORD
	.long	\side
	.long	\flag
	.long	\id
	.endm

//=============================================================================
/**
 *	退避していたキャラを復帰
 *
 *	@param	side	復帰させる側
 */
//=============================================================================
	.macro	CHR_POP		side
	.long	WS_CHR_POP
	.long	\side
	.endm

//=============================================================================
/**
 *	技がヒットした時にチェックする特性のチェック
 *
 *	@param	adrs	特性が発動しなかった時のとび先
 */
//=============================================================================
	.macro	WAZA_HIT_TOKUSEI_CHECK	adrs
	.long	WS_WAZA_HIT_TOKUSEI_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ソフトスプライトからOAMに変換を指示
 *
 *	@param	side	指示する側
 */
//=============================================================================
	.macro	SS_TO_OAM_CALL		side
	.long	WS_SS_TO_OAM_CALL
	.long	\side
	.endm

//=============================================================================
/**
 *	ソフトスプライトからOAMに変換を指示
 *
 *	@param	side	指示する側
 */
//=============================================================================
	.macro	OAM_TO_SS_CALL		side
	.long	WS_OAM_TO_SS_CALL
	.long	\side
	.endm

//=============================================================================
/**
 *	全滅チェック
 *
 *	@param	side	指示する側
 *	@param	adrs	全滅時の飛び先
 */
//=============================================================================
	.macro	ZENMETSU_CHECK		side,adrs
	.long	WS_ZENMETSU_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	つぼをつく
 *
 *	@param	adrs	発動できない時の飛び先
 */
//=============================================================================
	.macro	TUBOWOTUKU		adrs
	.long	WS_TUBOWOTUKU
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	アイテムを消去
 *
 *	@param	side	消去する側
 */
//=============================================================================
	.macro	KILL_ITEM		side
	.long	WS_KILL_ITEM
	.long	\side
	.endm

//=============================================================================
/**
 *	リサイクル
 *
 *	@param	adrs	リサイクルできない時のとび先
 */
//=============================================================================
	.macro	RECYCLE		adrs
	.long	WS_RECYCLE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	技がヒットした時にチェックする装備アイテムのチェック
 *
 *	@param	adrs	装備アイテムが発動しなかった時のとび先
 */
//=============================================================================
	.macro	WAZA_HIT_SOUBI_ITEM_CHECK	adrs
	.long	WS_WAZA_HIT_SOUBI_ITEM_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	通信対戦時の勝敗メッセージ表示
 */
//=============================================================================
	.macro	WIN_LOSE_MESSAGE
	.long	WS_WIN_LOSE_MESSAGE
	.endm

//=============================================================================
/**
 *	通信対戦時のにげるメッセージ表示
 */
//=============================================================================
	.macro	ESCAPE_MESSAGE
	.long	WS_ESCAPE_MESSAGE
	.endm

//=============================================================================
/**
 *	バトルタワーでのリタイアメッセージ表示
 */
//=============================================================================
	.macro	GIVEUP_MESSAGE
	.long	WS_GIVEUP_MESSAGE
	.endm

//=============================================================================
/**
 *	HP１で耐える系のアイテムチェック
 *	
 *	@param	side	チェックする側
 */
//=============================================================================
	.macro	HP1_CHECK		side
	.long	WS_HP1_CHECK
	.long	\side
	.endm

//=============================================================================
/**
 *	しぜんかいふく系チェック
 *	
 *	@param	side	チェックする側
 *	@param	adrs	発動しない時のとび先
 */
//=============================================================================
	.macro	SIZENKAIHUKU_CHECK		side,adrs
	.long	WS_SIZENKAIHUKU_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	みがわりチェック
 *	
 *	@param	side	チェックする側
 *	@param	adrs	みがわりがいた時のとび先
 */
//=============================================================================
	.macro	MIGAWARI_CHECK		side,adrs
	.long	WS_MIGAWARI_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	ノーてんきチェック
 *	
 *	@param	adrs	ノーてんきがいた時のとび先
 */
//=============================================================================
	.macro	NOOTENKI_CHECK		adrs
	.long	WS_NOOTENKI_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	攻撃対象の再抽選
 *	
 *	@param	side	攻撃側
 */
//=============================================================================
	.macro	DIR_CLIENT_GET		side
	.long	WS_DIR_CLIENT_GET
	.long	\side
	.endm

//=============================================================================
/**
 *	技がヒットした時にチェックする装備アイテムのチェック（とんぼがえり専用）
 *
 *	@param	adrs	装備アイテムが発動しなかった時のとび先
 */
//=============================================================================
	.macro	WAZA_HIT_SOUBI_ITEM_CHECK_TONBOGAERI	adrs
	.long	WS_WAZA_HIT_SOUBI_ITEM_CHECK_TONBOGAERI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	みがわりのキャラをセット
 *
 *	@param	side	セットする側
 */
//=============================================================================
	.macro	MIGAWARI_CHR_SET		side
	.long	WS_MIGAWARI_CHR_SET
	.long	\side
	.endm

//=============================================================================
/**
 *	技効果SEをならす
 *
 *	@param	side	鳴らす側
 */
//=============================================================================
	.macro	WAZAKOUKA_SE		side
	.long	WS_WAZAKOUKA_SE
	.long	\side
	.endm

//=============================================================================
/**
 *	曲をならす
 *
 *	@param	side	鳴らす側
 *	@param	bgm_no	鳴らす曲ナンバー
 */
//=============================================================================
	.macro	BGM_PLAY		side,bgm_no
	.long	WS_BGM_PLAY
	.long	\side
	.long	\bgm_no
	.endm

//=============================================================================
/**
 *	サファリ終了チェック
 *
 *	@param	adrs	終了じゃない時のとび先
 */
//=============================================================================
	.macro	SAFARI_END_CHECK		adrs
	.long	WS_SAFARI_END_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	シーケンス終了マクロ
 */
//=============================================================================
	.macro	SEQ_END
	.long	WS_SEQ_END
	.endm


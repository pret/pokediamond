//=============================================================================
/**
 * @file	waza_seq.def
 * @bfief	�Z�V�[�P���X�p�̃}�N����`�t�@�C��
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

//���߃V���{���錾
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

//���߃}�N����`
//=============================================================================
/**
 *	�G���J�E���g�G�t�F�N�g�Z�b�g
 */
//=============================================================================
	.macro	ENCOUNT_EFFECT
	.long	WS_ENCOUNT_EFFECT
	.endm

//=============================================================================
/**
 *	�|�P�����G���J�E���g�Z�b�g
 *
 *	@param	side	�|�P�������Z�b�g���鑤
 */
//=============================================================================
	.macro	POKEMON_ENCOUNT	side
	.long	WS_POKEMON_ENCOUNT
	.long	\side
	.endm

//=============================================================================
/**
 *	�|�P�����o��G�t�F�N�g�Z�b�g�i�G���J�E���g����p�j
 *
 *	@param	side	�|�P�������Z�b�g���鑤
 */
//=============================================================================
	.macro	POKEMON_ENCOUNT_APPEAR		side
	.long	WS_POKEMON_ENCOUNT_APPEAR
	.long	\side
	.endm

//=============================================================================
/**
 *	�|�P�����o��G�t�F�N�g�Z�b�g
 *
 *	@param	side	�|�P�������Z�b�g���鑤
 */
//=============================================================================
	.macro	POKEMON_APPEAR	side
	.long	WS_POKEMON_APPEAR
	.long	\side
	.endm

//=============================================================================
/**
 *	�|�P�����������߂�G�t�F�N�g�Z�b�g
 *
 *	@param	side	�G�t�F�N�g���Z�b�g���鑤
 */
//=============================================================================
	.macro	POKEMON_RETURN	side
	.long	WS_POKEMON_RETURN
	.long	\side
	.endm

//=============================================================================
/**
 *	�|�P�������폜
 *
 *	@param	side	�폜���鑤
 */
//=============================================================================
	.macro	POKEMON_DELETE	side
	.long	WS_POKEMON_DELETE
	.long	\side
	.endm

//=============================================================================
/**
 *	�g���[�i�[�G���J�E���g�Z�b�g
 *
 *	@param	side	�g���[�i�[���Z�b�g���鑤
 */
//=============================================================================
	.macro	TRAINER_ENCOUNT	side
	.long	WS_TRAINER_ENCOUNT
	.long	\side
	.endm

//=============================================================================
/**
 *	�g���[�i�[�{�[�������t���[���A�E�g
 *
 *	@param	side	�G�t�F�N�g���w�����鑤
 *	@param	type	�G�t�F�N�g�^�C�v
 */
//=============================================================================
	.macro	TRAINER_THROW	side,type
	.long	WS_TRAINER_THROW
	.long	\side
	.long	\type
	.endm

//=============================================================================
/**
 *	�g���[�i�[��ʊO�G�t�F�N�g�Z�b�g
 *
 *	@param	side	�G�t�F�N�g���w�����鑤
 */
//=============================================================================
	.macro	TRAINER_OUT	side
	.long	WS_TRAINER_OUT
	.long	\side
	.endm

//=============================================================================
/**
 *	�g���[�i�[��ʓ��G�t�F�N�g�Z�b�g
 *
 *	@param	side	�G�t�F�N�g���w�����鑤
 */
//=============================================================================
	.macro	TRAINER_IN	side,pos
	.long	WS_TRAINER_IN
	.long	\side
	.long	\pos
	.endm

//=============================================================================
/**
 *	�^�b�`�p�l���Ƀg���[�i�[BG��SlideIn
 */
//=============================================================================
	.macro	TRAINER_BG_SLIDEIN
	.long	WS_TRAINER_BG_SLIDEIN
	.endm

//=============================================================================
/**
 *	HP�Q�[�W���IN�G�t�F�N�g�Z�b�g
 *
 *	@param	side	�G�t�F�N�g���w�����鑤
 */
//=============================================================================
	.macro	HP_GAUGE_IN	side
	.long	WS_HP_GAUGE_IN
	.long	\side
	.endm

//=============================================================================
/**
 *	HP�Q�[�W���IN�G�t�F�N�g�Z�b�g
 *
 *	@param	side	�G�t�F�N�g���w�����鑤
 */
//=============================================================================
	.macro	HP_GAUGE_IN_WAIT_SET	side
	.long	WS_HP_GAUGE_IN_WAIT
	.long	\side
	.endm

//=============================================================================
/**
 *	HP�Q�[�W���OUT�G�t�F�N�g�Z�b�g
 *
 *	@param	side	�G�t�F�N�g���w�����鑤
 */
//=============================================================================
	.macro	HP_GAUGE_OUT	side
	.long	WS_HP_GAUGE_OUT
	.long	\side
	.endm

//=============================================================================
/**
 *	�����̏I���܂ŃT�[�o���҂�
 */
//=============================================================================
	.macro	SERVER_WAIT
	.long	WS_SERVER_WAIT
	.endm

//=============================================================================
/**
 *	�_���[�W�v�Z�}�N��
 *
 *	�_���[�W�v�Z������A�T�[�o�̃_���[�W���[�N�ɑ��
 */
//=============================================================================
	.macro	DAMAGE_CALC
	.long	WS_DAMAGE_CALC
	.endm

//=============================================================================
/**
 *	�_���[�W�v�Z�}�N���i�_���[�W���X�v�Z�����Ȃ��j
 *
 *	�_���[�W�v�Z������A�T�[�o�̃_���[�W���[�N�ɑ��
 */
//=============================================================================
	.macro	DAMAGE_CALC_NO_LOSS
	.long	WS_DAMAGE_CALC_NO_LOSS
	.endm

//=============================================================================
/**
 *	�Z�̍U�����b�Z�[�W��\��
 */
//=============================================================================
	.macro	ATTACK_MESSAGE
	.long	WS_ATTACK_MESSAGE
	.endm

//=============================================================================
/**
 *	���b�Z�[�W��\��
 *
 *	@param	msg_id			�\�����郁�b�Z�[�WID
 *	@param	tag				�\�����郁�b�Z�[�W�̃^�O
 *	@param	para1�`para6	�^�O�ɕt������p�����[�^
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
 *	���b�Z�[�W��\��
 *
 *	@param	msg_id			�\�����郁�b�Z�[�WID
 *	@param	tag				�\�����郁�b�Z�[�W�̃^�O
 *	@param	para1�`para6	�^�O�ɕt������p�����[�^
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
 *	���b�Z�[�W��\���iMESSAGE_PARAM�Őݒ肳�ꂽ�������ɕ\���j
 */
//=============================================================================
	.macro	MESSAGE_WORK
	.long	WS_MESSAGE_WORK
	.endm

//=============================================================================
/**
 *	���b�Z�[�W�\���p�p�����[�^����
 *
 *	@param	msg_id			�\�����郁�b�Z�[�WID
 *	@param	tag				�\�����郁�b�Z�[�W�̃^�O
 *	@param	para1�`para6	�^�O�ɕt������p�����[�^
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
 *	���b�Z�[�W��\��
 *
 *	@param	side			DIR�`�F�b�N���鑤���w��
 *	@param	msg_id			�\�����郁�b�Z�[�WID
 *	@param	tag				�\�����郁�b�Z�[�W�̃^�O
 *	@param	para1�`para6	�^�O�ɕt������p�����[�^
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
 *	�Z�G�t�F�N�g��\��
 */
//=============================================================================
	.macro	WAZA_EFFECT		side
	.long	WS_WAZA_EFFECT
	.long	\side
	.endm

//=============================================================================
/**
 *	�Z�G�t�F�N�g��\��
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
 *	�|�P������_�ł�����
 *
 *	@param	side	�|�P������_�ł��鑤
 */
//=============================================================================
	.macro	POKEMON_BLINK	side
	.long	WS_POKEMON_BLINK
	.long	\side
	.endm

//=============================================================================
/**
 *	HP�v�Z������
 *
 *	@param	side	�v�Z���鑤
 */
//=============================================================================
	.macro	HP_CALC	side
	.long	WS_HP_CALC
	.long	\side
	.endm

//=============================================================================
/**
 *	HP�Q�[�W�v�Z������
 *
 *	@param	side	�v�Z���鑤
 */
//=============================================================================
	.macro	HP_GAUGE_CALC	side
	.long	WS_HP_GAUGE_CALC
	.long	\side
	.endm

//=============================================================================
/**
 *	�C��`�F�b�N������
 *
 *	@param	side	�`�F�b�N���鑤
 */
//=============================================================================
	.macro	KIZETSU_CHECK	side
	.long	WS_KIZETSU_CHECK
	.long	\side
	.endm

//=============================================================================
/**
 *	�C��G�t�F�N�g
 */
//=============================================================================
	.macro	KIZETSU_EFFECT
	.long	WS_KIZETSU_EFFECT
	.endm

//=============================================================================
/**
 *	�w�蕪WAIT
 *
 *	@param	wait	WAIT_TIME�i�P�ɂ��A1/30�b�j
 */
//=============================================================================
	.macro	WAIT	wait
	.long	WS_WAIT
	.long	\wait
	.endm

//=============================================================================
/**
 *	�w��SE��炷
 *
 *	@param	side	�炷��
 *	@param	se_no	�炷SE
 */
//=============================================================================
	.macro	SE_PLAY		side,se_no
	.long	WS_SE_PLAY
	.long	\side
	.long	\se_no
	.endm

//=============================================================================
/**
 *	��������}�N��
 *
 *	@param	act		��������̎��
 *	@param	src		��r�����l�i���[�N�ɑ΂���C���f�b�N�X�j
 *	@param	dest	��r����l�i���l4�o�C�g�j
 *	@param	adrs	�����ƈ�v�����Ƃ��̔�ѐ�
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
 *	��������}�N���iPokemonServerParam�\���̂̃����o����j
 *
 *	@param	act		��������̎��
 *	@param	side	client_no
 *	@param	src		��r�����l�i�\���̃����o�ɑ΂���C���f�b�N�X�j
 *	@param	dest	��r����l�i���l4�o�C�g�j
 *	@param	adrs	�����ƈ�v�����Ƃ��̔�ѐ�
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
 *	��ʃt�F�[�h�A�E�g
 */
//=============================================================================
	.macro	FADE_OUT
	.long	WS_FADE_OUT
	.endm

//=============================================================================
/**
 *	SUB�V�[�P���X�W�����v�iSUB_SEQ�i���o�[���w�肵�ăW�����v�j
 */
//=============================================================================
	.macro	JUMP	be_seq_no
	.long	WS_JUMP
	.long	\be_seq_no
	.endm

//=============================================================================
/**
 *	�퓬���ʃV�[�P���X�W�����v�i�ZNo����WazaTableData��battleeffect�����o���ăW�����v�j
 */
//=============================================================================
	.macro	JUMP_BE_SEQ
	.long	WS_JUMP_BE_SEQ
	.endm

//=============================================================================
/**
 *	�퓬���ʃV�[�P���X�W�����v�isp->waza_work����WazaTableData��battleeffect�����o���ăW�����v�j
 *
 *	@param	flag	����t���O�iJWW_FLAG_NORMAL�F�ʏ퓮��@JWW_FLAG_SET_DEFENCE�F���ł�Defence�̓Z�b�g�ς݁j
 */
//=============================================================================
	.macro	JUMP_WAZA_WORK		flag
	.long	WS_JUMP_WAZA_WORK
	.long	\flag
	.endm

//=============================================================================
/**
 *	�N���e�B�J���q�b�g�`�F�b�N
 */
//=============================================================================
	.macro	CRITICAL_CHECK
	.long	WS_CRITICAL_CHECK
	.endm

//=============================================================================
/**
 *	�o���l�Q�b�g�`�F�b�N����
 *
 *	@param	adrs	�o���l�Q�b�g���������Ȃ��Ƃ��̂Ƃѐ�
 */
//=============================================================================
	.macro	GET_EXP_CHECK	adrs
	.long	WS_GET_EXP_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�o���l�Q�b�g����������
 */
//=============================================================================
	.macro	GET_EXP_INIT
	.long	WS_GET_EXP_INIT
	.endm

//=============================================================================
/**
 *	�o���l�Q�b�g����
 */
//=============================================================================
	.macro	GET_EXP
	.long	WS_GET_EXP
	.endm

//=============================================================================
/**
 *	�o���l�Q�b�g���[�v����
 *
 *	@param	adrs	�o���l�Q�b�g�������J��Ԃ��Ƃ��̂Ƃѐ�
 */
//=============================================================================
	.macro	GET_EXP_LOOP	adrs
	.long	WS_GET_EXP_LOOP
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�|�P�������X�g����
 */
//=============================================================================
	.macro	POKEMON_LIST
	.long	WS_POKEMON_LIST
	.endm

//=============================================================================
/**
 *	�|�P�������X�g����̋A���҂�
 */
//=============================================================================
	.macro	POKEMON_LIST_WAIT
	.long	WS_POKEMON_LIST_WAIT
	.endm

//=============================================================================
/**
 *	�|�P��������ւ������i����ւ����|�P�����̃f�[�^��psp�Ƀ��[�h�j
 *
 *	@param	side	�f�[�^�����[�h���鑤
 */
//=============================================================================
	.macro	POKEMON_RESHUFFLE	side
	.long	WS_POKEMON_RESHUFFLE
	.long	\side
	.endm

//=============================================================================
/**
 *	CLIENT_STATUS��RESHUFFLE_FLAG�����ă��[�v���邩���f
 *
 *	@param	adrs	���[�v����Ƃ��̂Ƃѐ�
 */
//=============================================================================
	.macro	POKEMON_RESHUFFLE_LOOP	adrs
	.long	WS_POKEMON_RESHUFFLE_LOOP
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�|�P�����ߊl�V�[�P���X������
 *
 *	@param	flag	�ߊl�V�[�P���X�̎�ށiGET_NORMAL:�ʏ�ߊl�@GET_SAFARI:�T�t�@���]�[��or�|�P�p�[�N�j
 */
//=============================================================================
	.macro	POKEMON_GET_INIT	flag
	.long	WS_POKEMON_GET_INIT
	.long	\flag
	.endm

//=============================================================================
/**
 *	�|�P�����ߊl�V�[�P���X
 */
//=============================================================================
	.macro	POKEMON_GET
	.long	WS_POKEMON_GET
	.endm

//=============================================================================
/**
 *	�A���U�����̃��[�v�񐔂�����
 *
 *	@param	para	0:���[�v����񐔂Q�`�T�@0�ȊO:�w�肳�ꂽ��
 *	@param	flag	���[�v��������HITCHECK���ǂ����邩�iHITCHECK_ON�F�`�F�b�N����@HITCHECK_OFF�F���Ȃ��j
 */
//=============================================================================
	.macro	RENZOKU	para,flag
	.long	WS_RENZOKU
	.long	\para
	.long	\flag
	.endm

//=============================================================================
/**
 *	�ϐ�����
 *
 *	@param	act		����p�����[�^�ibattle_common.h�ɒ�`�j
 *	@param	src		����Ώەϐ��ibattle_common.h�ɒ�`�j
 *	@param	value	���삷��l
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
 *	AbirityCount�𑀍삷��
 *
 *	@param	adrs1	����o���Ȃ������Ƃ��̂Ƃѐ���w��i���ځA�����j
 *	@param	adrs2	����o���Ȃ������Ƃ��̂Ƃѐ���w��i�Ԑځj
 *	@param	adrs3	�݂����ȂǂŖh���ꂽ���̂Ƃѐ���w��
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
 *	�ϐ�����iPokemonServerParam����j
 *
 *	@param	act		����p�����[�^�ibattle_common.h�ɒ�`�j
 *	@param	side	���삷��Client�ibattle_common.h�ɒ�`�j
 *	@param	src		����Ώەϐ��ibattle_common.h�ɒ�`�j
 *	@param	value	���삷��l
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
 *	psp�\���̂�condition2�t���O�̍폜�v��
 *
 *	@param	side	�v������Client�ibattle_common.h�ɒ�`�j
 *	@param	value	�v������t���O
 */
//=============================================================================
	.macro	CONDITION2_OFF	side,value
	.long	WS_CONDITION2_OFF
	.long	\side
	.long	\value
	.endm

//=============================================================================
/**
 *	�|�P�����\����ON/OFF
 *
 *	@param	side	ON/OFF����Client�ibattle_common.h�ɒ�`�j
 *	@param	sw		ON/OFF�t���O
 */
//=============================================================================
	.macro	VANISH_ON_OFF		side,sw
	.long	WS_VANISH_ON_OFF
	.long	\side
	.long	\sw
	.endm

//=============================================================================
/**
 *	�����̃`�F�b�N
 *
 *	@param	side	�`�F�b�N����Client�ibattle_common.h�ɒ�`�j
 *	@param	tokusei	�`�F�b�N�������
 *	@param	adrs	side�Ŏw�肵��Client��tokusei�Ŏw�肵�������������Ă����Ƃ��̔�ѐ�
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
 *	�����̎擾�isp->calc_work�Ɋi�[�j
 *
 *	@param	range	�O���炢���܂ł̕��ɂ��邩�H
 *	@param	ofs		�擾���������ɑ΂���I�t�Z�b�g(range=3��ofs=2�Ȃ�A�Q�`�T�̗������擾����j
 */
//=============================================================================
	.macro	RANDOM_GET	range,ofs
	.long	WS_RANDOM_GET
	.long	\range
	.long	\ofs
	.endm

//=============================================================================
/**
 *	�ϐ�����i���l�ł͂Ȃ��ʂ̃��[�N����j
 *
 *	@param	act		����p�����[�^�ibattle_common.h�ɒ�`�j
 *	@param	src		����Ώەϐ��ibattle_common.h�ɒ�`�j
 *	@param	dest	���삷��l���i�[���ꂽ���[�N�̃C���f�b�N�X
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
 *	�ϐ�����iPokemonServerParam����A���l�ł͂Ȃ��ʂ̃��[�N����j
 *
 *	@param	act		����p�����[�^�ibattle_common.h�ɒ�`�j
 *	@param	side	���삷��Client�ibattle_common.h�ɒ�`�j
 *	@param	src		����Ώەϐ��ibattle_common.h�ɒ�`�j
 *	@param	dest	���삷��l���i�[���ꂽ���[�N�̃C���f�b�N�X
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
 *	����V�[�P���X�f�[�^���ł̃W�����v�i�A�Z���u���̃u�����`���߁j
 *
 *	@param	adrs	��ѐ�
 */
//=============================================================================
	.macro	BRANCH	adrs
	.long	WS_BRANCH
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�T�u���[�`���W�����v�iBASIC��GOSUB���߁j
 *
 *	@param	seq_no	��ѐ�V�[�P���X�i���o�[
 */
//=============================================================================
	.macro	GOSUB	seq_no
	.long	WS_GOSUB
	.long	\seq_no
	.endm

//=============================================================================
/**
 *	�T�u���[�`���W�����v�iBASIC��GOSUB���߁j���[�N�̒��g���Q��
 *
 *	@param	para	��ѐ�V�[�P���X�i���o�[���i�[���ꂽ���[�N�ւ̃C���f�b�N�X
 */
//=============================================================================
	.macro	GOSUB_WORK	para
	.long	WS_GOSUB_WORK
	.long	\para
	.endm

//=============================================================================
/**
 *	�I�E���������`�F�b�N�i�I�E���Ԃ����s�̎��͂��̂܂܎��̃V�[�P���X�ցj
 */
//=============================================================================
	.macro	OUMU_CHECK
	.long	WS_OUMU_CHECK
	.endm

//=============================================================================
/**
 *	���낢����̌��ʔ���
 */
//=============================================================================
	.macro	KUROIKIRI
	.long	WS_KUROIKIRI
	.endm

//=============================================================================
/**
 *	���ߌn�̃t���O�𗧂Ă�
 *
 *	@param	side	���삷��Client�ibattle_common.h�ɒ�`�j
 */
//=============================================================================
	.macro	KEEP_ON		side
	.long	WS_KEEP_ON
	.long	\side
	.endm

//=============================================================================
/**
 *	���ߌn�̃t���O�𗎂Ƃ�
 *
 *	@param	side	���삷��Client�ibattle_common.h�ɒ�`�j
 */
//=============================================================================
	.macro	KEEP_OFF		side
	.long	WS_KEEP_OFF
	.long	\side
	.endm

//=============================================================================
/**
 *	��Ԉُ�A�C�R�����Z�b�g
 *
 *	@param	side	�Z�b�g����Client�ibattle_common.h�ɒ�`�j
 *	@param	status	��Ԉُ�No
 */
//=============================================================================
	.macro	STATUS_SET	side,status
	.long	WS_STATUS_SET
	.long	\side
	.long	\status
	.endm

//=============================================================================
/**
 *	�g���[�i�[���b�Z�[�W��\��
 *
 *	@param	side	�\�����邷��Client�ibattle_common.h�ɒ�`�j
 *	@param	type	���b�Z�[�W�^�C�v�itr_tool.h�ɒ�`�j
 */
//=============================================================================
	.macro	TRAINER_MESSAGE		side,type
	.long	WS_TRAINER_MESSAGE
	.long	\side
	.long	\type
	.endm

//=============================================================================
/**
 *	�����Â����v�Z������
 */
//=============================================================================
	.macro	OKODUKAI_CALC
	.long	WS_OKODUKAI_CALC
	.endm

//=============================================================================
/**
 *	��Ԉُ�G�t�F�N�g���Z�b�g
 *
 *	@param	side	�\�����邷��Client�ibattle_common.h�ɒ�`�j
 *	@param	type	�Z�b�g�����Ԉُ�̎�ށibattle_tool.h�ɒ�`�j
 */
//=============================================================================
	.macro	STATUS_EFFECT		side,status
	.long	WS_STATUS_EFFECT
	.long	\side
	.long	\status
	.endm

//=============================================================================
/**
 *	��Ԉُ�G�t�F�N�g���Z�b�g�iAttack��Defence���w��j
 *
 *	@param	side1	�\�����邷��Client�ibattle_common.h�ɒ�`�j
 *	@param	side2	�\�����邷��Client�ibattle_common.h�ɒ�`�j
 *	@param	type	�Z�b�g�����Ԉُ�̎�ށibattle_tool.h�ɒ�`�j
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
 *	��Ԉُ�G�t�F�N�g���Z�b�g
 *
 *	@param	side	�\�����邷��Client�ibattle_common.h�ɒ�`�j
 *	@param	type	�Z�b�g�����Ԉُ�̎�ށibattle_tool.h�ɒ�`�j
 */
//=============================================================================
	.macro	STATUS_EFFECT_WORK	side,status
	.long	WS_STATUS_EFFECT_WORK
	.long	\side
	.long	\status
	.endm

//=============================================================================
/**
 *	�߂����b�Z�[�W��\��
 *
 *	@param	side	�\�����邷��Client�ibattle_common.h�ɒ�`�j
 */
//=============================================================================
	.macro	MODOSU_MESSAGE		side
	.long	WS_MODOSU_MESSAGE
	.long	\side
	.endm

//=============================================================================
/**
 *	�J��o�����b�Z�[�W��\��
 *
 *	@param	side	�\�����邷��Client�ibattle_common.h�ɒ�`�j
 */
//=============================================================================
	.macro	KURIDASU_MESSAGE	side
	.long	WS_KURIDASU_MESSAGE
	.long	\side
	.endm

//=============================================================================
/**
 *	�G���J�E���g���b�Z�[�W��\��
 *
 *	@param	side	�\�����邷��Client�ibattle_common.h�ɒ�`�j
 */
//=============================================================================
	.macro	ENCOUNT_MESSAGE		side
	.long	WS_ENCOUNT_MESSAGE
	.long	\side
	.endm

//=============================================================================
/**
 *	�G���J�E���g���̌J��o�����b�Z�[�W��\��
 *
 *	@param	side	�\�����邷��Client�ibattle_common.h�ɒ�`�j
 */
//=============================================================================
	.macro	ENCOUNT_KURIDASU_MESSAGE		side
	.long	WS_ENCOUNT_KURIDASU_MESSAGE
	.long	\side
	.endm

//=============================================================================
/**
 *	�g���[�i�[���b�Z�[�W��\���i�^�C�v�̓��[�N�w��j
 *
 *	@param	side	�\�����邷��Client�ibattle_common.h�ɒ�`�j
 */
//=============================================================================
	.macro	TRAINER_MESSAGE_WORK	side
	.long	WS_TRAINER_MESSAGE_WORK
	.long	\side
	.endm

//=============================================================================
/**
 *	�e�N�X�`���[���ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	TEXTURE		adrs
	.long	WS_TEXTURE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	��������}�N��
 *
 *	@param	act		��������̎��
 *	@param	src		��r�����l�i���[�N�ɑ΂���C���f�b�N�X�j
 *	@param	dest	��r����l�i���[�N�ɑ΂���C���f�b�N�X�j
 *	@param	adrs	�����ƈ�v�����Ƃ��̔�ѐ�
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
 *	��������}�N���iPokemonServerParam�\���̂̃����o����j
 *
 *	@param	act		��������̎��
 *	@param	side	client_no
 *	@param	src		��r�����l�i�\���̃����o�ɑ΂���C���f�b�N�X�j
 *	@param	dest	��r����l�i���[�N�ɑ΂���C���f�b�N�X�j
 *	@param	adrs	�����ƈ�v�����Ƃ��̔�ѐ�
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
 *	���΂�J�E���^���`�F�b�N���Ă������擾
 */
//=============================================================================
	.macro	KOBAN_CHECK
	.long	WS_KOBAN_CHECK
	.endm

//=============================================================================
/**
 *	�Ђ���̂��׌��ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	HIKARINOKABE	adrs
	.long	WS_HIKARINOKABE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	���t���N�^�[���ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	RIHUREKUTAA		adrs
	.long	WS_RIHUREKUTAA
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	���낢������ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	SIROIKIRI		adrs
	.long	WS_SIROIKIRI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�ꌂ�K�E�������v�Z
 */
//=============================================================================
	.macro	ICHIGEKI
	.long	WS_ICHIGEKI
	.endm

//=============================================================================
/**
 *	value�Ŋ��������ʂ��O�̎��́A1or-1�ɂ��鏈��������
 *
 *	@param	para	value�Ŋ���Ώ�
 *	@param	value	����Ώ�
 */
//=============================================================================
	.macro	DAMAGE_DIV	para,value
	.long	WS_DAMAGE_DIV
	.long	\para
	.long	\value
	.endm

//=============================================================================
/**
 *	value�Ŋ��������ʂ��O�̎��́A1or-1�ɂ��鏈��������
 *
 *	@param	para	value�Ŋ���Ώ�
 *	@param	value	����Ώ�
 */
//=============================================================================
	.macro	DAMAGE_DIV_WORK	para,value
	.long	WS_DAMAGE_DIV_WORK
	.long	\para
	.long	\value
	.endm

//=============================================================================
/**
 *	���̂܂ˌ��ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	MONOMANE	adrs
	.long	WS_MONOMANE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	��т��ӂ���ʔ���
 */
//=============================================================================
	.macro	YUBIWOHURU
	.long	WS_YUBIWOHURU
	.endm

//=============================================================================
/**
 *	���Ȃ��΂���ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	KANASIBARI	adrs
	.long	WS_KANASIBARI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�J�E���^�[���ʔ���
 */
//=============================================================================
	.macro	COUNTER
	.long	WS_COUNTER
	.endm

//=============================================================================
/**
 *	�~���[�R�[�g���ʔ���
 */
//=============================================================================
	.macro	MIRROR_CORT
	.long	WS_MIRROR_CORT
	.endm

//=============================================================================
/**
 *	�A���R�[�����ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	ENCORE		adrs
	.long	WS_ENCORE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�e�N�X�`���[�Q���ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	TEXTURE2	adrs
	.long	WS_TEXTURE2
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�X�P�b�`���ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	SKETCH		adrs
	.long	WS_SKETCH
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�˂��ƌ��ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	NEGOTO		adrs
	.long	WS_NEGOTO
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�����΂��U���͌v�Z
 */
//=============================================================================
	.macro	JITABATA
	.long	WS_JITABATA
	.endm

//=============================================================================
/**
 *	����݌��ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	URAMI		adrs
	.long	WS_URAMI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	���₵�̂������ʔ���
 */
//=============================================================================
	.macro	IYASINOSUZU
	.long	WS_IYASINOSUZU
	.endm

//=============================================================================
/**
 *	�ǂ�ڂ����ʔ���
 *
 *	@param	adrs1	�����ł��Ȃ����̂Ƃѐ�
 *	@param	adrs2	�����ł��Ȃ����̂Ƃѐ�i�����j
 */
//=============================================================================
	.macro	DOROBOU		adrs1,adrs2
	.long	WS_DOROBOU
	.long	(\adrs1-.)/4-2
	.long	(\adrs2-.)/4-1
	.endm

//=============================================================================
/**
 *	�܂���A���炦�铙�A���Ŏg�p����Ɛ�������������n�̃`�F�b�N
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	GUARD_SUCCESS_CHECK		adrs
	.long	WS_GUARD_SUCCESS_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�݂������ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	MIGAWARI	adrs
	.long	WS_MIGAWARI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�ӂ��Ƃ΂����ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	HUKITOBASI		adrs
	.long	WS_HUKITOBASI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�ւ񂵂���ʔ���
 */
//=============================================================================
	.macro	HENSIN
	.long	WS_HENSIN
	.endm

//=============================================================================
/**
 *	�܂��т����ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	MAKIBISI		adrs
	.long	WS_MAKIBISI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�܂��т��_���[�W���ʔ���
 *
 *	@param	side	�`�F�b�N���鑤
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	MAKIBISI_CHECK		side,adrs
	.long	WS_MAKIBISI_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�ق�т̂������ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	HOROBINOUTA		adrs
	.long	WS_HOROBINOUTA
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	���΂₳����ClientNo���擾
 *
 *	@param	para2	�擾����ClientNo���i�[���郏�[�NINDEX�iBUF_PARA�n�j
 */
//=============================================================================
	.macro	CLIENT_NO_GET_AGI	para
	.long	WS_CLIENT_NO_GET_AGI
	.long	\para
	.endm

//=============================================================================
/**
 *	�w�肵�����[�N�̒l��client_set_max�ɂȂ�܂�LOOP
 *
 *	@param	para	client_set_max�Ɣ�r����l���i�[���ꂽ���[�NINDEX�iBUF_PARA�n�j
 *	@param	adrs	client_set_max�ɂȂ��Ă��Ȃ��������̂Ƃѐ�
 */
//=============================================================================
	.macro	CLIENT_SET_MAX_LOOP		para,adrs
	.long	WS_CLIENT_SET_MAX_LOOP
	.long	\para
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�V��_���[�W�v�Z
 *
 *	@param	side	�_���[�W���󂯂�ClientNo
 */
//=============================================================================
	.macro	TENKOU_DAMAGE	side
	.long	WS_TENKOU_DAMAGE
	.long	\side
	.endm

//=============================================================================
/**
 *	���낪��_���[�W�v�Z
 */
//=============================================================================
	.macro	KOROGARU
	.long	WS_KOROGARU
	.endm

//=============================================================================
/**
 *	��񂼂�����_���[�W�v�Z
 */
//=============================================================================
	.macro	RENZOKUGIRI
	.long	WS_RENZOKUGIRI
	.endm

//=============================================================================
/**
 *	���������ǉ�����
 *
 *	@param	adrs	���������ɂł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	MEROMERO		adrs
	.long	WS_MEROMERO
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	���������ǉ�����
 *
 *	@param	adrs	�Z���ʂ������ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	SHINPI			adrs
	.long	WS_SHINPI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�v���[���g�ǉ�����
 *
 *	@param	adrs	HP�񕜓��쎞�̂Ƃѐ�
 */
//=============================================================================
	.macro	PRESENT			adrs
	.long	WS_PRESENT
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�}�O�j�`���[�h�_���[�W�v�Z
 */
//=============================================================================
	.macro	MAGNITUDE
	.long	WS_MAGNITUDE
	.endm

//=============================================================================
/**
 *	����ւ�����|�P���������邩�`�F�b�N
 *
 *	@param	side	�`�F�b�N���鑤
 *	@param	flag	����ւ����鎞�Ƀ|�P�������X�g�Ăяo���悤�̃t���O�𗧂Ă邩�ǂ���
 *	@param	adrs	���Ȃ��������̂Ƃѐ�
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
 *	���������X�s���ǉ�����
 */
//=============================================================================
	.macro	KOUSOKUSPIN
	.long	WS_KOUSOKUSPIN
	.endm

//=============================================================================
/**
 *	�V��ɂ����HP�񕜗ʂ��ω�����ǉ�����
 */
//=============================================================================
	.macro	WEATHER_KAIFUKU
	.long	WS_WEATHER_KAIFUKU
	.endm

//=============================================================================
/**
 *	�߂��߂�p���[
 */
//=============================================================================
	.macro	MEZAMERU_POWER
	.long	WS_MEZAMERU_POWER
	.endm

//=============================================================================
/**
 *	��������
 */
//=============================================================================
	.macro	JIKOANJI
	.long	WS_JIKOANJI
	.endm

//=============================================================================
/**
 *	�݂炢�悿
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	MIRAIYOCHI		adrs
	.long	WS_MIRAIYOCHI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�������`�F�b�N������
 *
 *	@param	side_a	�U����
 *	@param	side_d	�h�䑤
 *	@param	waza 	�`�F�b�N����Z
 *	@param	adrs	�O�ꂽ���̂Ƃѐ�
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
 *	�e���|�[�g
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	TELEPORT		adrs
	.long	WS_TELEPORT
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�ӂ��낾����
 */
//=============================================================================
	.macro	HUKURODATAKI
	.long	WS_HUKURODATAKI
	.endm

//=============================================================================
/**
 *	���̂�тƂ܂�
 */
//=============================================================================
	.macro	KONOYUBITOMARE
	.long	WS_KONOYUBITOMARE
	.endm

//=============================================================================
/**
 *	�Ă�����
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	TEDASUKE	adrs
	.long	WS_TEDASUKE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�g���b�N
 *
 *	@param	adrs1	�����ł��Ȃ����̂Ƃѐ�
 *	@param	adrs2	�����Ŕ����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	TRICK		adrs1,adrs2
	.long	WS_TRICK
	.long	(\adrs1-.)/4-2
	.long	(\adrs2-.)/4-1
	.endm

//=============================================================================
/**
 *	�˂�������
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	NEGAIGOTO	adrs
	.long	WS_NEGAIGOTO
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�˂��̂�
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	NEKONOTE	adrs
	.long	WS_NEKONOTE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�}�W�b�N�R�[�g
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	MAGIC_CORT	adrs
	.long	WS_MAGIC_CORT
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�}�W�b�N�R�[�g�����ɂ��Attack��Defence�̓���ւ�
 */
//=============================================================================
	.macro	MAGIC_CORT_A_D
	.long	WS_MAGIC_CORT_A_D
	.endm

//=============================================================================
/**
 *	���x���W
 */
//=============================================================================
	.macro	REVENGE
	.long	WS_REVENGE
	.endm

//=============================================================================
/**
 *	�������
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	KAWARAWARI		adrs
	.long	WS_KAWARAWARI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	������
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	AKUBI		adrs
	.long	WS_AKUBI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�͂������Ƃ�
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	HATAKIOTOSU		adrs
	.long	WS_HATAKIOTOSU
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�ӂ񂩈З͌v�Z
 */
//=============================================================================
	.macro	HUNKA
	.long	WS_HUNKA
	.endm

//=============================================================================
/**
 *	�ӂ�����
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	HUUIN			adrs
	.long	WS_HUUIN
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	����˂�
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	ONNEN		adrs
	.long	WS_ONNEN
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�悱�ǂ�
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	YOKODORI		adrs
	.long	WS_YOKODORI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	��������
 */
//=============================================================================
	.macro	KETAGURI
	.long	WS_KETAGURI
	.endm

//=============================================================================
/**
 *	�E�G�U�[�{�[��
 */
//=============================================================================
	.macro	WEATHER_BALL
	.long	WS_WEATHER_BALL
	.endm

//=============================================================================
/**
 *	���������`�F�b�N
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	OIUCHI_CHECK		adrs
	.long	WS_OIUCHI_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�^�C�v�`�F�b�N
 */
//=============================================================================
	.macro	TYPE_CHECK
	.long	WS_TYPE_CHECK
	.endm

//=============================================================================
/**
 *	OneTurnFlag�`�F�b�N
 *
 *	@param	side	�`�F�b�N���鑤
 *	@param	flag	�`�F�b�N����t���O
 *	@param	value	�`�F�b�N����l�i 0 or 1 �j
 *	@param	adrs	�`�F�b�N����l�ƈ�v�������̂Ƃѐ�
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
 *	OneTurnFlag�Z�b�g
 *
 *	@param	side	�Z�b�g���鑤
 *	@param	flag	�Z�b�g����t���O
 *	@param	value	�Z�b�g����l�i 0 or 1 �j
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
 *	�W���C���{�[��
 */
//=============================================================================
	.macro	GIROBALL
	.long	WS_GIROBALL
	.endm

//=============================================================================
/**
 *	���^���~���[
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	METALMIRROR		adrs
	.long	WS_METALMIRROR
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	���߂���
 */
//=============================================================================
	.macro	TAMEUCHI
	.long	WS_TAMEUCHI
	.endm

//=============================================================================
/**
 *	����ӂ�
 */
//=============================================================================
	.macro	KIRIHUDA
	.long	WS_KIRIHUDA
	.endm

//=============================================================================
/**
 *	���ڂ�Ƃ�
 */
//=============================================================================
	.macro	SIBORITORU
	.long	WS_SIBORITORU
	.endm

//=============================================================================
/**
 *	�����ǂ�
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	SAKIDORI		adrs
	.long	WS_SAKIDORI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�܂˂���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	MANEKKO		adrs
	.long	WS_MANEKKO
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	��������
 */
//=============================================================================
	.macro	OSIOKI
	.long	WS_OSIOKI
	.endm

//=============================================================================
/**
 *	�ӂ�����
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	HUIUCHI			adrs
	.long	WS_HUIUCHI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	side_condition_work�𒲂ׂ�mode�ɂ���Ďw�肳�ꂽ�Ƃѐ��JUMP
 *
 *	@param	side	���ׂ鑤
 *	@param	mode	���ׂ郂�[�h
 *	@param	flag	���ׂ�side_condition_work
 *	@param	adrs	mode�ɂ���Ă̂Ƃѐ�
 *
 *	mode,flag�́Abattle_server.h��SCC_�`�Œ�`
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
 *	�t�F�C���g
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	FEINT			adrs
	.long	WS_FEINT
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	���肱��
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	SURIKOMI		adrs
	.long	WS_SURIKOMI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�Ƃ��Ă���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	TOTTEOKI		adrs
	.long	WS_TOTTEOKI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�ǂ��т����ʔ���
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	DOKUBISI		adrs
	.long	WS_DOKUBISI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�ǂ��т����ʔ���
 *
 *	@param	side	�`�F�b�N���鑤
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	DOKUBISI_CHECK		side,adrs
	.long	WS_DOKUBISI_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�����̃`�F�b�N�i������Ԃ�L�j
 *
 *	@param	side	�`�F�b�N����Client�ibattle_common.h�ɒ�`�j
 *	@param	tokusei	�`�F�b�N�������
 *	@param	adrs	side�Ŏw�肵��Client��tokusei�Ŏw�肵�������������Ă����Ƃ��̔�ѐ�
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
 *	�������A���葤�̃`�F�b�N
 *
 *	@param	src		�`�F�b�N����Client
 *	@param	dest	�`�F�b�N����Client
 *	@param	adrs	�`�F�b�N����Client�����������������̔�ѐ�
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
 *	�������̂Ђ낢�`�F�b�N
 */
//=============================================================================
	.macro	MONOHIROI
	.long	WS_MONOHIROI
	.endm

//=============================================================================
/**
 *	�g���b�N���[��
 */
//=============================================================================
	.macro	TRICKROOM
	.long	WS_TRICKROOM
	.endm

//=============================================================================
/**
 *	�Ώۂ��Z���o���I���Ă��邩�`�F�b�N
 *
 *	@param	side	�`�F�b�N����Ώ�
 *	@param	adrs	�`�F�b�N�����Ώۂ��Z���o���I���Ă������̂Ƃѐ�
 */
//=============================================================================
	.macro	WAZA_OUT_CHECK	side,adrs
	.long	WS_WAZA_OUT_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�����A�C�e�����ʂ������Ă��邩�`�F�b�N
 *
 *	@param	flag	�����Ă���or�����Ă��Ȃ�
 *	@param	side	�`�F�b�N����Ώ�
 *	@param	eqp		�`�F�b�N���鑕������
 *	@param	adrs	flag�Ŏw�肵�������̎��̂Ƃѐ�
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
 *	�����A�C�e���̑������ʃp�����[�^���擾
 *
 *	@param	side	�擾����Ώ�
 *	@param	para	�擾�����l�̊i�[��
 */
//=============================================================================
	.macro	SOUBI_EQP_GET		side,para
	.long	WS_SOUBI_EQP_GET
	.long	\side
	.long	\para
	.endm

//=============================================================================
/**
 *	�����A�C�e���̈З̓p�����[�^���擾
 *
 *	@param	side	�擾����Ώ�
 *	@param	para	�擾�����l�̊i�[��
 */
//=============================================================================
	.macro	SOUBI_ATK_GET		side,para
	.long	WS_SOUBI_ATK_GET
	.long	\side
	.long	\para
	.endm

//=============================================================================
/**
 *	�ق����傭
 *
 *	@param	adrs	�����ł��Ȃ��������̂Ƃѐ�
 */
//=============================================================================
	.macro	HOGOSYOKU		adrs
	.long	WS_HOGOSYOKU
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	������̂�����
 */
//=============================================================================
	.macro	SHIZENNOCHIKARA
	.long	WS_SHIZENNOCHIKARA
	.endm
	
//=============================================================================
/**
 *	�Ђ݂̂�����
 */
//=============================================================================
	.macro	HIMITSUNOCHIKARA
	.long	WS_HIMITSUNOCHIKARA
	.endm

//=============================================================================
/**
 *	������̂߂���
 *
 *	@param	adrs	�����ł��Ȃ��������̂Ƃѐ�
 */
//=============================================================================
	.macro	SHIZENNOMEGUMI		adrs
	.long	WS_SHIZENNOMEGUMI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	���΂�
 *
 *	@param	adrs1	�����Ŕ����ł��Ȃ��������̂Ƃѐ�
 *	@param	adrs2	�����ł��Ȃ��������̂Ƃѐ�
 */
//=============================================================================
	.macro	TSUIBAMU		adrs1,adrs2
	.long	WS_TSUIBAMU
	.long	(\adrs1-.)/4-2
	.long	(\adrs2-.)/4-1
	.endm

//=============================================================================
/**
 *	�Ȃ�����
 *
 *	@param	adrs	�����ł��Ȃ��������̂Ƃѐ�
 */
//=============================================================================
	.macro	NAGETSUKERU		adrs
	.long	WS_NAGETSUKERU
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	Yes/No�I�����Ăяo��
 *
 *	@param	type	Yes/No�I���̎��
 */
//=============================================================================
	.macro	YES_NO_SELECT		type
	.long	WS_YES_NO_SELECT
	.long	\type
	.endm

//=============================================================================
/**
 *	Yes/No�I����҂�
 *
 *	@param	adrs1	Yes�̎��̂Ƃѐ�
 *	@param	adrs2	No�̎��̂Ƃѐ�
 */
//=============================================================================
	.macro	YES_NO_SELECT_WAIT		adrs1,adrs2
	.long	WS_YES_NO_SELECT_WAIT
	.long	(\adrs1-.)/4-2
	.long	(\adrs2-.)/4-1
	.endm

//=============================================================================
/**
 *	�|�P�������X�g�I�����Ăяo���i����ւ����p�j
 */
//=============================================================================
	.macro	POKEMON_LIST_CALL
	.long	WS_POKEMON_LIST_CALL
	.endm

//=============================================================================
/**
 *	�|�P�������X�g�I����҂i����ւ����p�j
 *
 *	@param	adrs	����ւ��Ȃ��������̂Ƃѐ�
 */
//=============================================================================
	.macro	POKEMON_LIST_CALL_WAIT		adrs
	.long	WS_POKEMON_LIST_CALL_WAIT
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	win_lose_flag�̃Z�b�g�i�ʐM�ΐ��p�j
 */
//=============================================================================
	.macro	WIN_LOSE_SET
	.long	WS_WIN_LOSE_SET
	.endm

//=============================================================================
/**
 *	�X�e���X���b�N�_���[�W���ʔ���
 *
 *	@param	side	�`�F�b�N���鑤
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	STEALTHROCK_CHECK		side,adrs
	.long	WS_STEALTHROCK_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	���݂̋Z�̒ǉ����ʔ������`�F�b�N
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	ADD_STATUS_CHECK		adrs
	.long	WS_ADD_STATUS_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	������ׂ�̒ǉ����ʔ������`�F�b�N
 *
 *	@param	adrs	�����ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	OSYABERI		adrs
	.long	WS_OSYABERI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�Z�̃p�����[�^���擾�isp->waza_no_now�̃p�����[�^��sp->calc_work�ɑ���j
 *
 *	@param	id	�擾����p�����[�^��ID
 */
//=============================================================================
	.macro	WAZA_PARAM_GET		id
	.long	WS_WAZA_PARAM_GET
	.long	\id
	.endm

//=============================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g�Ƀ��U�C�N��������
 *
 *	@param	side	���U�C�N�������鑤
 *	@param	para	���U�C�N�i�K
 *	@param	wait	���U�C�N��������X�s�[�h�i0�F�ő��j
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
 *	�t�H�������`�F���W�iform_no��sp->calc_work�ɑ���j
 *
 *	@param	side	�`�F���W���鑤
 */
//=============================================================================
	.macro	FORM_CHG	side
	.long	WS_FORM_CHG
	.long	\side
	.endm

//=============================================================================
/**
 *	�n�`OBJ��BG�ɏ�������
 */
//=============================================================================
	.macro	BG_CHG
	.long	WS_BG_CHG
	.endm

//=============================================================================
/**
 *	BattleWorkStatusRecover���Ăяo��
 */
//=============================================================================
	.macro	STATUS_RECOVER		side
	.long	WS_STATUS_RECOVER
	.long	\side
	.endm

//=============================================================================
/**
 *	�������邩�`�F�b�N
 *
 *	@param	side	�`�F�b�N���鑤
 *	@param	adrs	������鎞�̂Ƃѐ�
 */
//=============================================================================
	.macro	ESCAPE_ACT_CHECK		side,adrs
	.long	WS_ESCAPE_ACT_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�{�[���Q�[�W���Z�b�g�i�G���J�E���g���j
 *
 *	@param	side	�Z�b�g���鑤
 */
//=============================================================================
	.macro	BALL_GAUGE_ENCOUNT_SET	side
	.long	WS_BALL_GAUGE_ENCOUNT_SET
	.long	\side
	.endm

//=============================================================================
/**
 *	�{�[���Q�[�W�������i�G���J�E���g���j
 *
 *	@param	side	�Z�b�g���鑤
 */
//=============================================================================
	.macro	BALL_GAUGE_ENCOUNT_OUT	side
	.long	WS_BALL_GAUGE_ENCOUNT_OUT
	.long	\side
	.endm

//=============================================================================
/**
 *	�{�[���Q�[�W���Z�b�g
 *
 *	@param	side	�Z�b�g���鑤
 */
//=============================================================================
	.macro	BALL_GAUGE_SET	side
	.long	WS_BALL_GAUGE_SET
	.long	\side
	.endm

//=============================================================================
/**
 *	�{�[���Q�[�W������
 *
 *	@param	side	�Z�b�g���鑤
 */
//=============================================================================
	.macro	BALL_GAUGE_OUT	side
	.long	WS_BALL_GAUGE_OUT
	.long	\side
	.endm

//=============================================================================
/**
 *	�{�[���Q�[�W�̃��\�[�X�����[�h
 */
//=============================================================================
	.macro	BALL_GAUGE_RESOURCE_LOAD
	.long	WS_BALL_GAUGE_RESOURCE_LOAD
	.endm

//=============================================================================
/**
 *	�{�[���Q�[�W�̃��\�[�X������
 */
//=============================================================================
	.macro	BALL_GAUGE_RESOURCE_DELETE
	.long	WS_BALL_GAUGE_RESOURCE_DELETE
	.endm

//=============================================================================
/**
 *	�J�E���g�A�b�v
 *
 *	@param	side	�J�E���g�A�b�v�Ώۍs�ׂ�������
 *	@param	flag	�J�E���g�A�b�v�Ώۍs�ׂ��������̐���t���O
 *	@param	id		�J�E���g�A�b�v����ID
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
 *	�ޔ����Ă����L�����𕜋A
 *
 *	@param	side	���A�����鑤
 */
//=============================================================================
	.macro	CHR_POP		side
	.long	WS_CHR_POP
	.long	\side
	.endm

//=============================================================================
/**
 *	�Z���q�b�g�������Ƀ`�F�b�N��������̃`�F�b�N
 *
 *	@param	adrs	�������������Ȃ��������̂Ƃѐ�
 */
//=============================================================================
	.macro	WAZA_HIT_TOKUSEI_CHECK	adrs
	.long	WS_WAZA_HIT_TOKUSEI_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�\�t�g�X�v���C�g����OAM�ɕϊ����w��
 *
 *	@param	side	�w�����鑤
 */
//=============================================================================
	.macro	SS_TO_OAM_CALL		side
	.long	WS_SS_TO_OAM_CALL
	.long	\side
	.endm

//=============================================================================
/**
 *	�\�t�g�X�v���C�g����OAM�ɕϊ����w��
 *
 *	@param	side	�w�����鑤
 */
//=============================================================================
	.macro	OAM_TO_SS_CALL		side
	.long	WS_OAM_TO_SS_CALL
	.long	\side
	.endm

//=============================================================================
/**
 *	�S�Ń`�F�b�N
 *
 *	@param	side	�w�����鑤
 *	@param	adrs	�S�Ŏ��̔�ѐ�
 */
//=============================================================================
	.macro	ZENMETSU_CHECK		side,adrs
	.long	WS_ZENMETSU_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�ڂ���
 *
 *	@param	adrs	�����ł��Ȃ����̔�ѐ�
 */
//=============================================================================
	.macro	TUBOWOTUKU		adrs
	.long	WS_TUBOWOTUKU
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�A�C�e��������
 *
 *	@param	side	�������鑤
 */
//=============================================================================
	.macro	KILL_ITEM		side
	.long	WS_KILL_ITEM
	.long	\side
	.endm

//=============================================================================
/**
 *	���T�C�N��
 *
 *	@param	adrs	���T�C�N���ł��Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	RECYCLE		adrs
	.long	WS_RECYCLE
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�Z���q�b�g�������Ƀ`�F�b�N���鑕���A�C�e���̃`�F�b�N
 *
 *	@param	adrs	�����A�C�e�����������Ȃ��������̂Ƃѐ�
 */
//=============================================================================
	.macro	WAZA_HIT_SOUBI_ITEM_CHECK	adrs
	.long	WS_WAZA_HIT_SOUBI_ITEM_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�ʐM�ΐ펞�̏��s���b�Z�[�W�\��
 */
//=============================================================================
	.macro	WIN_LOSE_MESSAGE
	.long	WS_WIN_LOSE_MESSAGE
	.endm

//=============================================================================
/**
 *	�ʐM�ΐ펞�̂ɂ��郁�b�Z�[�W�\��
 */
//=============================================================================
	.macro	ESCAPE_MESSAGE
	.long	WS_ESCAPE_MESSAGE
	.endm

//=============================================================================
/**
 *	�o�g���^���[�ł̃��^�C�A���b�Z�[�W�\��
 */
//=============================================================================
	.macro	GIVEUP_MESSAGE
	.long	WS_GIVEUP_MESSAGE
	.endm

//=============================================================================
/**
 *	HP�P�őς���n�̃A�C�e���`�F�b�N
 *	
 *	@param	side	�`�F�b�N���鑤
 */
//=============================================================================
	.macro	HP1_CHECK		side
	.long	WS_HP1_CHECK
	.long	\side
	.endm

//=============================================================================
/**
 *	�����񂩂��ӂ��n�`�F�b�N
 *	
 *	@param	side	�`�F�b�N���鑤
 *	@param	adrs	�������Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	SIZENKAIHUKU_CHECK		side,adrs
	.long	WS_SIZENKAIHUKU_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�݂����`�F�b�N
 *	
 *	@param	side	�`�F�b�N���鑤
 *	@param	adrs	�݂���肪�������̂Ƃѐ�
 */
//=============================================================================
	.macro	MIGAWARI_CHECK		side,adrs
	.long	WS_MIGAWARI_CHECK
	.long	\side
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�m�[�Ă񂫃`�F�b�N
 *	
 *	@param	adrs	�m�[�Ă񂫂��������̂Ƃѐ�
 */
//=============================================================================
	.macro	NOOTENKI_CHECK		adrs
	.long	WS_NOOTENKI_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�U���Ώۂ̍Ē��I
 *	
 *	@param	side	�U����
 */
//=============================================================================
	.macro	DIR_CLIENT_GET		side
	.long	WS_DIR_CLIENT_GET
	.long	\side
	.endm

//=============================================================================
/**
 *	�Z���q�b�g�������Ƀ`�F�b�N���鑕���A�C�e���̃`�F�b�N�i�Ƃ�ڂ������p�j
 *
 *	@param	adrs	�����A�C�e�����������Ȃ��������̂Ƃѐ�
 */
//=============================================================================
	.macro	WAZA_HIT_SOUBI_ITEM_CHECK_TONBOGAERI	adrs
	.long	WS_WAZA_HIT_SOUBI_ITEM_CHECK_TONBOGAERI
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�݂����̃L�������Z�b�g
 *
 *	@param	side	�Z�b�g���鑤
 */
//=============================================================================
	.macro	MIGAWARI_CHR_SET		side
	.long	WS_MIGAWARI_CHR_SET
	.long	\side
	.endm

//=============================================================================
/**
 *	�Z����SE���Ȃ炷
 *
 *	@param	side	�炷��
 */
//=============================================================================
	.macro	WAZAKOUKA_SE		side
	.long	WS_WAZAKOUKA_SE
	.long	\side
	.endm

//=============================================================================
/**
 *	�Ȃ��Ȃ炷
 *
 *	@param	side	�炷��
 *	@param	bgm_no	�炷�ȃi���o�[
 */
//=============================================================================
	.macro	BGM_PLAY		side,bgm_no
	.long	WS_BGM_PLAY
	.long	\side
	.long	\bgm_no
	.endm

//=============================================================================
/**
 *	�T�t�@���I���`�F�b�N
 *
 *	@param	adrs	�I������Ȃ����̂Ƃѐ�
 */
//=============================================================================
	.macro	SAFARI_END_CHECK		adrs
	.long	WS_SAFARI_END_CHECK
	.long	(\adrs-.)/4-1
	.endm

//=============================================================================
/**
 *	�V�[�P���X�I���}�N��
 */
//=============================================================================
	.macro	SEQ_END
	.long	WS_SEQ_END
	.endm


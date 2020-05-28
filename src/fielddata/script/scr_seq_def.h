//=============================================================================
/**
 * @file	scr_seq_def.def
 * @bfief	�X�N���v�g�R�}���h�̃}�N����`�t�@�C��
 * @author	HisashiSogabe
 * @date	2005.05.24
 *
 * 05.08.04 Satoshi Nohara
 *
 * �Z�V�[�P���X�p�̃}�N����`�t�@�C�������ɂ��Ă���
 */
//=============================================================================
#define	__ASM_NO_DEF_

//�X�N���v�g�Ŏg�p����w�b�_�[�t�@�C��
	.include	"usescript.h"

//�f�[�^�����R�ȋ��E�ɃA���C�����邩�̐ݒ�
	.option alignment off

	.macro	INIT_CMD
DEF_CMD_COUNT	=	0
	.endm
		
	.macro	DEF_CMD	symname
\symname	=	DEF_CMD_COUNT
DEF_CMD_COUNT	=	( DEF_CMD_COUNT + 1 )
	.endm

//���߃V���{���錾
	INIT_CMD
	DEF_CMD	EV_SEQ_NOP
	DEF_CMD	EV_SEQ_DUMMY
	DEF_CMD	EV_SEQ_END
	DEF_CMD	EV_SEQ_TIME_WAIT

	DEF_CMD	EV_SEQ_LD_REG_VAL
	DEF_CMD	EV_SEQ_LD_REG_WDATA
	DEF_CMD	EV_SEQ_LD_REG_ADR
	DEF_CMD	EV_SEQ_LD_ADR_VAL
	DEF_CMD	EV_SEQ_LD_ADR_REG
	DEF_CMD	EV_SEQ_LD_REG_REG
	DEF_CMD	EV_SEQ_LD_ADR_ADR

	DEF_CMD	EV_SEQ_CP_REG_REG
	DEF_CMD	EV_SEQ_CP_REG_VAL
	DEF_CMD	EV_SEQ_CP_REG_ADR
	DEF_CMD	EV_SEQ_CP_ADR_REG
	DEF_CMD	EV_SEQ_CP_ADR_VAL
	DEF_CMD	EV_SEQ_CP_ADR_ADR
	DEF_CMD	EV_SEQ_CP_WK_VAL
	DEF_CMD	EV_SEQ_CP_WK_WK

	DEF_CMD EV_SEQ_VM_ADD
	DEF_CMD EV_SEQ_CHG_COMMON_SCR
	DEF_CMD EV_SEQ_CHG_LOCAL_SCR

	DEF_CMD EV_SEQ_JUMP
	DEF_CMD EV_SEQ_OBJ_ID_JUMP
	DEF_CMD EV_SEQ_BG_ID_JUMP
	DEF_CMD EV_SEQ_PLAYER_DIR_JUMP
	DEF_CMD EV_SEQ_CALL
	DEF_CMD EV_SEQ_RET
	DEF_CMD EV_SEQ_IF_JUMP
	DEF_CMD EV_SEQ_IF_CALL

	DEF_CMD	EV_SEQ_FLAG_SET
	DEF_CMD	EV_SEQ_FLAG_RESET
	DEF_CMD	EV_SEQ_FLAG_CHECK			//32
	DEF_CMD	EV_SEQ_FLAG_CHECK_WK
	DEF_CMD	EV_SEQ_FLAG_SET_WK

	DEF_CMD	EV_SEQ_TRAINER_FLAG_SET
	DEF_CMD	EV_SEQ_TRAINER_FLAG_RESET
	DEF_CMD	EV_SEQ_TRAINER_FLAG_CHECK

	DEF_CMD	EV_SEQ_ADD_WK
	DEF_CMD	EV_SEQ_SUB_WK

	DEF_CMD	EV_SEQ_LD_WK_VAL			//40
	DEF_CMD	EV_SEQ_LD_WK_WK
	DEF_CMD	EV_SEQ_LD_WK_WKVAL

	DEF_CMD	EV_SEQ_MSG_ALLPUT
	DEF_CMD	EV_SEQ_MSG
	DEF_CMD	EV_SEQ_MSG_SP
	DEF_CMD	EV_SEQ_MSG_NOSKIP
	DEF_CMD	EV_SEQ_MSG_CON_SIO
	DEF_CMD	EV_SEQ_ABKEYWAIT
	DEF_CMD	EV_SEQ_LASTKEYWAIT
	DEF_CMD	EV_SEQ_NEXT_ANM_LASTKEYWAIT	
	DEF_CMD	EV_SEQ_WIN_OPEN				//50
	DEF_CMD	EV_SEQ_WIN_CLOSE
	DEF_CMD	EV_SEQ_WIN_CLOSE_NO_CLEAR

	DEF_CMD	EV_SEQ_BOARD_MAKE
	DEF_CMD	EV_SEQ_INFOBOARD_MAKE
	DEF_CMD	EV_SEQ_BOARD_REQ
	DEF_CMD	EV_SEQ_BOARD_REQ_WAIT
	DEF_CMD	EV_SEQ_BOARD_MSG
	DEF_CMD	EV_SEQ_BOARD_END_WAIT

	DEF_CMD	EV_SEQ_MENU_REQ			// ���j���[���N�G�X�g
	DEF_CMD	EV_SEQ_BG_SCROLL			//60

	DEF_CMD	EV_SEQ_YES_NO_WIN
	DEF_CMD	EV_SEQ_GUINNESS_WIN

	DEF_CMD	EV_SEQ_BMPMENU_INIT
	DEF_CMD	EV_SEQ_BMPMENU_INIT_EX
	DEF_CMD	EV_SEQ_BMPMENU_MAKE_LIST
	DEF_CMD	EV_SEQ_BMPMENU_START
	//DEF_CMD EV_SEQ_SEL_WIN_JUMP

	DEF_CMD	EV_SEQ_BMPLIST_INIT
	DEF_CMD	EV_SEQ_BMPLIST_INIT_EX
	DEF_CMD	EV_SEQ_BMPLIST_MAKE_LIST
	DEF_CMD	EV_SEQ_BMPLIST_START		//70

	DEF_CMD	EV_SEQ_BMPMENU_HV_START

	DEF_CMD	EV_SEQ_SE_PLAY
	DEF_CMD	EV_SEQ_SE_STOP
	DEF_CMD	EV_SEQ_SE_WAIT
	DEF_CMD	EV_SEQ_VOICE_PLAY
	DEF_CMD	EV_SEQ_VOICE_WAIT
	DEF_CMD	EV_SEQ_ME_PLAY
	DEF_CMD	EV_SEQ_ME_WAIT
	DEF_CMD	EV_SEQ_BGM_PLAY
	DEF_CMD	EV_SEQ_BGM_STOP				//80
	DEF_CMD	EV_SEQ_BGM_NOW_MAP_PLAY
	DEF_CMD	EV_SEQ_BGM_SPECIAL_SET
	DEF_CMD	EV_SEQ_BGM_FADEOUT
	DEF_CMD	EV_SEQ_BGM_FADEIN
	DEF_CMD	EV_SEQ_BGM_PLAYER_PAUSE
	DEF_CMD	EV_SEQ_PLAYER_FIELD_DEMO_BGM_PLAY
	DEF_CMD	EV_SEQ_CTRL_BGM_FLAG_SET
	DEF_CMD	EV_SEQ_PERAP_DATA_CHECK
	DEF_CMD	EV_SEQ_PERAP_REC_START
	DEF_CMD	EV_SEQ_PERAP_REC_STOP		//90
	DEF_CMD	EV_SEQ_PERAP_SAVE
	DEF_CMD	EV_SEQ_SND_CLIMAX_DATA_LOAD

	DEF_CMD	EV_SEQ_OBJ_ANIME			
	DEF_CMD	EV_SEQ_OBJ_ANIME_WAIT
	DEF_CMD	EV_SEQ_OBJ_PAUSE_ALL
	DEF_CMD	EV_SEQ_OBJ_PAUSE_CLEAR_ALL
	DEF_CMD	EV_SEQ_OBJ_PAUSE
	DEF_CMD	EV_SEQ_OBJ_PAUSE_CLEAR
	DEF_CMD	EV_SEQ_OBJ_ADD
	DEF_CMD	EV_SEQ_OBJ_DEL

	DEF_CMD	EV_SEQ_VANISH_DUMMY_OBJ_ADD	//100
	DEF_CMD	EV_SEQ_VANISH_DUMMY_OBJ_DEL

	DEF_CMD	EV_SEQ_OBJ_TURN				//102
	DEF_CMD	EV_SEQ_PLAYER_POS_GET
	DEF_CMD	EV_SEQ_OBJ_POS_GET
	DEF_CMD	EV_SEQ_PLAYER_POS_OFFSET_SET

	DEF_CMD	EV_SEQ_NOT_ZONE_DEL_SET
	DEF_CMD	EV_SEQ_MOVE_CODE_CHANGE
	DEF_CMD	EV_SEQ_PAIR_OBJID_SET

	DEF_CMD	EV_SEQ_ADD_GOLD				//�����֘A���ׂ�
	DEF_CMD	EV_SEQ_SUB_GOLD
	DEF_CMD	EV_SEQ_COMP_GOLD
	DEF_CMD	EV_SEQ_GOLD_WIN_WRITE
	DEF_CMD	EV_SEQ_GOLD_WIN_DEL
	DEF_CMD	EV_SEQ_GOLD_WRITE			//�����֘A�����܂�

	DEF_CMD	EV_SEQ_COIN_WIN_WRITE		//�R�C���֘A���ׂ�
	DEF_CMD	EV_SEQ_COIN_WIN_DEL			
	DEF_CMD	EV_SEQ_COIN_WRITE
	DEF_CMD	EV_SEQ_GET_COIN_NUM
	DEF_CMD	EV_SEQ_ADD_COIN
	DEF_CMD	EV_SEQ_SUB_COIN				//�R�C���֘A�����܂�

	DEF_CMD	EV_SEQ_ADD_ITEM
	DEF_CMD	EV_SEQ_SUB_ITEM
	DEF_CMD	EV_SEQ_ADD_ITEM_CHK
	DEF_CMD	EV_SEQ_ITEM_CHK
	DEF_CMD	EV_SEQ_WAZA_ITEM_CHK

	DEF_CMD	EV_SEQ_GET_POCKET_NO
	DEF_CMD	EV_SEQ_ADD_BOX_ITEM			//�g�p����060630
	DEF_CMD	EV_SEQ_CHK_BOX_ITEM			//�g�p����060630

	DEF_CMD	EV_SEQ_ADD_GOODS			//�O�b�Y�֘A���ׂ�			�쐬��060602
	DEF_CMD	EV_SEQ_SUB_GOODS
	DEF_CMD	EV_SEQ_ADD_GOODS_CHK
	DEF_CMD	EV_SEQ_GOODS_CHK			//�O�b�Y�֘A�����܂�

	DEF_CMD	EV_SEQ_ADD_TRAP				//�g���b�v�֘A���ׂ�
	DEF_CMD	EV_SEQ_SUB_TRAP
	DEF_CMD	EV_SEQ_ADD_TRAP_CHK
	DEF_CMD	EV_SEQ_TRAP_CHK				//�g���b�v�֘A�����܂�

	DEF_CMD	EV_SEQ_ADD_TREASURE			//����
	DEF_CMD	EV_SEQ_SUB_TREASURE
	DEF_CMD	EV_SEQ_ADD_TREASURE_CHK
	DEF_CMD	EV_SEQ_TREASURE_CHK			//����֘A�����܂�

	DEF_CMD	EV_SEQ_ADD_TAMA				//�^�}�֘A���ׂ�
	DEF_CMD	EV_SEQ_SUB_TAMA
	DEF_CMD	EV_SEQ_ADD_TAMA_CHK
	DEF_CMD	EV_SEQ_TAMA_CHK				//�^�}�֘A�����܂�

	DEF_CMD	EV_SEQ_CB_ITEM_NUM_GET
	DEF_CMD	EV_SEQ_CB_ITEM_NUM_ADD
	DEF_CMD	EV_SEQ_UNKNOWN_FORM_GET

	DEF_CMD	EV_SEQ_ADD_POKEMON			//�|�P�����֘A���ׂ�
	DEF_CMD	EV_SEQ_ADD_TAMAGO
	DEF_CMD	EV_SEQ_CHG_POKE_WAZA
	DEF_CMD	EV_SEQ_CHK_POKE_WAZA
	DEF_CMD	EV_SEQ_CHK_POKE_WAZA_GROUP		//�|�P�����֘A�����܂�

	DEF_CMD	EV_SEQ_REVENGE_TRAINER_SEARCH

	DEF_CMD	EV_SEQ_INIT_WEATHER			//�V��֘A���ׂ�			���Ή�
	DEF_CMD	EV_SEQ_SET_WEATHER
	DEF_CMD	EV_SEQ_UPDATE_WEATHER		//�V��֘A�����܂�

	DEF_CMD	EV_SEQ_GET_MAP_POS			//���݂̃}�b�v�ʒu���擾	���Ή�
	DEF_CMD	EV_SEQ_GET_TEMOTI_POKE_NUM	//�莝���̃|�P���������擾	���Ή� ���ʖ��߂����ɂ��肢��Ȃ�060224tomo

	DEF_CMD	EV_SEQ_SET_MAP_PROC

	DEF_CMD	EV_SEQ_WIFI_AUTO_REG
	DEF_CMD	EV_SEQ_WIFI_P2P_MATCH_EVENT_CALL
	DEF_CMD	EV_SEQ_WIFI_P2P_MATCH_SET_DEL
	DEF_CMD	EV_SEQ_MSG_BOY_EVENT
	DEF_CMD	EV_SEQ_IMAGE_CLIP_SET_PROC
	DEF_CMD	EV_SEQ_IMAGE_CLIPVIEW_TV_SET_PROC
	DEF_CMD	EV_SEQ_IMAGE_CLIPVIEW_CON_SET_PROC
	DEF_CMD	EV_SEQ_CUSTOM_BALL_EVENT_CALL
	DEF_CMD	EV_SEQ_TMAP_BG_SET_PROC
	DEF_CMD	EV_SEQ_BOX_SET_PROC
	DEF_CMD	EV_SEQ_OEKAKI_BOARD_SET_PROC
	DEF_CMD	EV_SEQ_TR_CARD_SET_PROC
	DEF_CMD	EV_SEQ_TRADE_LIST_SET_PROC
	DEF_CMD	EV_SEQ_RECORD_CORNER_SET_PROC
	DEF_CMD	EV_SEQ_DENDOU_SET_PROC
	DEF_CMD	EV_SEQ_PC_DENDOU_SET_PROC
	DEF_CMD	EV_SEQ_WORLDTRADE_SET_PROC
	DEF_CMD	EV_SEQ_DPW_INIT_PROC

	DEF_CMD	EV_SEQ_FIRST_POKE_SELECT_PROC
	DEF_CMD	EV_SEQ_FIRST_POKE_SELECT_SET_AND_DEL

	DEF_CMD	EV_SEQ_EYE_TRAINER_MOVE_SET
	DEF_CMD	EV_SEQ_EYE_TRAINER_MOVE_CHECK
	DEF_CMD	EV_SEQ_EYE_TRAINER_TYPE_GET
	DEF_CMD	EV_SEQ_EYE_TRAINER_ID_GET
	DEF_CMD	EV_SEQ_NAMEIN
	DEF_CMD	EV_SEQ_NAMEIN_POKE

	DEF_CMD	EV_SEQ_WIPE_FADE_START
	DEF_CMD	EV_SEQ_WIPE_FADE_END_CHECK

	DEF_CMD	EV_SEQ_MAP_CHANGE
	DEF_CMD	EV_SEQ_KABENOBORI
	DEF_CMD	EV_SEQ_NAMINORI
	DEF_CMD	EV_SEQ_TAKINOBORI
	DEF_CMD	EV_SEQ_SORAWOTOBU
	DEF_CMD EV_SEQ_HIDEN_FLASH
	DEF_CMD EV_SEQ_HIDEN_KIRIBARAI
	DEF_CMD	EV_SEQ_CUTIN
	DEF_CMD	EV_SEQ_CON_HERO_CHANGE
	DEF_CMD	EV_SEQ_BICYCLE_CHECK
	DEF_CMD	EV_SEQ_BICYCLE_REQ
	DEF_CMD	EV_SEQ_CYCLING_ROAD_SET

	DEF_CMD	EV_SEQ_PLAYER_FORM_GET
	DEF_CMD	EV_SEQ_PLAYER_REQ_BIT_ON
	DEF_CMD	EV_SEQ_PLAYER_REQ_START

	DEF_CMD	EV_SEQ_PLAYER_NAME
	DEF_CMD	EV_SEQ_RIVAL_NAME
	DEF_CMD	EV_SEQ_SUPPORT_NAME
	DEF_CMD	EV_SEQ_POKEMON_NAME
	DEF_CMD	EV_SEQ_ITEM_NAME
	DEF_CMD	EV_SEQ_POCKET_NAME
	DEF_CMD	EV_SEQ_ITEM_WAZA_NAME
	DEF_CMD	EV_SEQ_WAZA_NAME
	DEF_CMD	EV_SEQ_NUMBER_NAME
	DEF_CMD	EV_SEQ_NICK_NAME
	DEF_CMD	EV_SEQ_POKETCH_NAME
	DEF_CMD	EV_SEQ_TR_TYPE_NAME
	DEF_CMD	EV_SEQ_MY_TR_TYPE_NAME
	DEF_CMD	EV_SEQ_POKEMON_NAME_EXTRA
	DEF_CMD	EV_SEQ_FIRST_POKEMON_NAME
	DEF_CMD	EV_SEQ_RIVAL_POKEMON_NAME
	DEF_CMD	EV_SEQ_SUPPORT_POKEMON_NAME
	DEF_CMD	EV_SEQ_FIRST_POKE_NO_GET
	DEF_CMD	EV_SEQ_GOODS_NAME
	DEF_CMD	EV_SEQ_TRAP_NAME
	DEF_CMD	EV_SEQ_TAMA_NAME
	DEF_CMD	EV_SEQ_ZONE_NAME
	DEF_CMD	EV_SEQ_GENERATE_INFO_GET

	DEF_CMD	EV_SEQ_TRAINER_ID_GET
	DEF_CMD	EV_SEQ_TRAINER_BTL_SET
	DEF_CMD	EV_SEQ_TRAINER_MSG_SET
	DEF_CMD	EV_SEQ_TRAINER_TALK_TYPE_GET
	DEF_CMD	EV_SEQ_REVENGE_TRAINER_TALK_TYPE_GET
	DEF_CMD	EV_SEQ_TRAINER_TYPE_GET
	DEF_CMD	EV_SEQ_TRAINER_BGM_SET
	DEF_CMD	EV_SEQ_LOSE
	DEF_CMD	EV_SEQ_LOSE_CHECK
	DEF_CMD	EV_SEQ_SEACRET_POKE_RETRY_CHECK
	DEF_CMD	EV_SEQ_2VS2_BATTLE_CHECK
	DEF_CMD	EV_SEQ_DEBUG_BTL_SET
	DEF_CMD	EV_SEQ_DEBUG_TRAINER_FLAG_SET
	DEF_CMD	EV_SEQ_DEBUG_TRAINER_FLAG_ON_JUMP

	DEF_CMD	EV_SEQ_CONNECT_SEL_PARENT_WIN
	DEF_CMD	EV_SEQ_CONNECT_SEL_CHILD_WIN
	DEF_CMD	EV_SEQ_CONNECT_DEBUG_PARENT_WIN
	DEF_CMD	EV_SEQ_CONNECT_DEBUG_CHILD_WIN

	DEF_CMD	EV_SEQ_DEBUG_SIO_ENCOUNT
	DEF_CMD	EV_SEQ_DEBUG_SIO_CONTEST

	DEF_CMD	EV_SEQ_CONSIO_TIMING_SEND
	DEF_CMD	EV_SEQ_CONSIO_TIMING_CHECK
	DEF_CMD	EV_SEQ_CON_SYSTEM_CREATE
	DEF_CMD	EV_SEQ_CON_SYSTEM_EXIT
	DEF_CMD	EV_SEQ_CON_JUDGE_NAME_GET
	DEF_CMD	EV_SEQ_CON_BREEDER_NAME_GET
	DEF_CMD	EV_SEQ_CON_NICK_NAME_GET
	DEF_CMD	EV_SEQ_CON_NUM_TAG_SET
	DEF_CMD	EV_SEQ_CON_SIO_PARAM_INIT_SET
	DEF_CMD	EV_SEQ_CONTEST_PROC
	DEF_CMD	EV_SEQ_CON_RANK_NAME_GET
	DEF_CMD	EV_SEQ_CON_TYPE_NAME_GET
	DEF_CMD	EV_SEQ_CON_VICTORY_BREEDER_NAME_GET
	DEF_CMD	EV_SEQ_CON_VICTORY_ITEM_NO_GET
	DEF_CMD	EV_SEQ_CON_VICTORY_NICK_NAME_GET
	DEF_CMD	EV_SEQ_CON_RANKING_CHECK
	DEF_CMD	EV_SEQ_CON_VICTORY_ENTRY_NO_GET
	DEF_CMD	EV_SEQ_CON_MY_ENTRY_NO_GET
	DEF_CMD	EV_SEQ_CON_OBJ_CODE_GET
	DEF_CMD	EV_SEQ_CON_POPULARITY_GET
	DEF_CMD	EV_SEQ_CON_DESK_MODE_GET
	DEF_CMD	EV_SEQ_CON_HAVE_RIBBON_CHECK
	DEF_CMD	EV_SEQ_CON_RIBBON_NAME_GET
	DEF_CMD	EV_SEQ_CON_ACCE_NO_GET
	DEF_CMD	EV_SEQ_CON_ENTRY_PARAM_GET
	DEF_CMD	EV_SEQ_CON_CAMERA_FLASH_SET
	DEF_CMD	EV_SEQ_CON_CAMERA_FLASH_CHECK
	DEF_CMD	EV_SEQ_CON_HBLANK_STOP
	DEF_CMD	EV_SEQ_CON_HBLANK_START
	DEF_CMD	EV_SEQ_CON_ENDING_SKIP_CHECK
	DEF_CMD	EV_SEQ_CON_RECORD_DISP
	DEF_CMD	EV_SEQ_CON_MSGPRINT_FLAG_SET
	DEF_CMD	EV_SEQ_CON_MSGPRINT_FLAG_RESET

	DEF_CMD	EV_SEQ_CHK_TEMOTI_POKERUS
	DEF_CMD	EV_SEQ_TEMOTI_POKE_SEX_GET

	DEF_CMD	EV_SEQ_SP_LOCATION_SET

	DEF_CMD	EV_SEQ_ELEVATOR_FLOOR_GET
	DEF_CMD	EV_SEQ_ELEVATOR_FLOOR_WRITE

	DEF_CMD	EV_SEQ_SHINOU_ZUKAN_SEE_NUM
	DEF_CMD	EV_SEQ_SHINOU_ZUKAN_GET_NUM
	DEF_CMD	EV_SEQ_ZENKOKU_ZUKAN_SEE_NUM
	DEF_CMD	EV_SEQ_ZENKOKU_ZUKAN_GET_NUM
	DEF_CMD	EV_SEQ_CHK_ZENKOKU_ZUKAN
	DEF_CMD	EV_SEQ_GET_HYOUKA_MSGID

	DEF_CMD	EV_SEQ_WILD_BTL_SET
	DEF_CMD	EV_SEQ_FIRST_BTL_SET
	DEF_CMD	EV_SEQ_CAPTURE_BTL_SET

	DEF_CMD	EV_SEQ_HONEY_TREE
	DEF_CMD	EV_SEQ_GET_HONEY_TREE_STATE
	DEF_CMD	EV_SEQ_SET_HONEY_TREE_BTL
	DEF_CMD	EV_SEQ_SET_AFTER_HONEY_TREE_BTL

	DEF_CMD	EV_SEQ_TSIGN_SET_PROC

	DEF_CMD	EV_SEQ_REPORT_SAVE_CHECK
	DEF_CMD	EV_SEQ_REPORT_SAVE

	DEF_CMD	EV_SEQ_CLIP_TVSAVEDATA_CHECK
	DEF_CMD	EV_SEQ_CLIP_CONSAVEDATA_CHECK
	DEF_CMD	EV_SEQ_CLIP_TV_TITLE_SAVE

	DEF_CMD	EV_SEQ_GET_POKETCH
	DEF_CMD	EV_SEQ_GET_POKETCH_FLAG
	DEF_CMD	EV_SEQ_POKETCH_ADD
	DEF_CMD	EV_SEQ_POKETCH_CHECK

	DEF_CMD	EV_SEQ_COMM_TIMING_SYNC_START
	DEF_CMD	EV_SEQ_COMM_TEMP_DATA_RESET

	DEF_CMD	EV_SEQ_UNION_PARENT_CARD_TALK_NO
	DEF_CMD	EV_SEQ_UNION_GET_INFO_TALK_NO
	DEF_CMD	EV_SEQ_UNION_BEACON_CHANGE

	DEF_CMD	EV_SEQ_UNION_CONNECT_TALK_DENIED
	DEF_CMD	EV_SEQ_UNION_CONNECT_TALK_OK

	DEF_CMD	EV_SEQ_UNION_TRAINER_NAME_REGIST
	DEF_CMD	EV_SEQ_UNION_RETURN_SETUP
	DEF_CMD	EV_SEQ_UNION_CONNECT_CUT_RESTART
	DEF_CMD	EV_SEQ_UNION_GET_TALK_NUMBER
	DEF_CMD	EV_SEQ_UNION_ID_SET
	DEF_CMD	EV_SEQ_UNION_RESULT_GET
	DEF_CMD	EV_SEQ_UNION_OBJ_ALL_VANISH
	DEF_CMD	EV_SEQ_UNION_SCRIPT_RESULT_SET
	DEF_CMD	EV_SEQ_UNION_PARENT_START_COMMAND_SET
	DEF_CMD	EV_SEQ_UNION_CHILD_SELECT_COMMAND_SET
	DEF_CMD	EV_SEQ_UNION_CONNECT_START

	DEF_CMD	EV_SEQ_SHOP_CALL
	DEF_CMD	EV_SEQ_FIX_SHOP_CALL
	DEF_CMD	EV_SEQ_FIX_GOODS_CALL
	DEF_CMD	EV_SEQ_FIX_SEAL_CALL

	DEF_CMD	EV_SEQ_GAME_OVER_CALL

	DEF_CMD	EV_SEQ_SET_WARP_ID
	DEF_CMD	EV_SEQ_GET_MY_SEX
	DEF_CMD	EV_SEQ_PC_KAIFUKU

	DEF_CMD	EV_SEQ_UG_MAN_SHOP_NPC_RAND_PLACE
	DEF_CMD	EV_SEQ_COMM_DIRECT_END
	DEF_CMD	EV_SEQ_COMM_DIRECT_ENTER_BTL_ROOM
	DEF_CMD	EV_SEQ_COMM_PLAYER_SET_DIR

	DEF_CMD EV_SEQ_UNION_MAP_CHANGE
	DEF_CMD	EV_SEQ_UNION_VIEW_TR_SEL_SET
	DEF_CMD	EV_SEQ_UNION_VIEW_TR_TYPE_MSG_GET
	DEF_CMD	EV_SEQ_UNION_VIEW_MY_STATUS_SET

	DEF_CMD	EV_SEQ_SYS_FLAG_ZUKAN_GET
	DEF_CMD	EV_SEQ_SYS_FLAG_ZUKAN_SET
	DEF_CMD	EV_SEQ_SYS_FLAG_SHOES_GET
	DEF_CMD	EV_SEQ_SYS_FLAG_SHOES_SET
	DEF_CMD	EV_SEQ_SYS_FLAG_BADGE_GET
	DEF_CMD	EV_SEQ_SYS_FLAG_BADGE_SET
	DEF_CMD	EV_SEQ_SYS_FLAG_BADGE_COUNT
	DEF_CMD	EV_SEQ_SYS_FLAG_BAG_GET
	DEF_CMD	EV_SEQ_SYS_FLAG_BAG_SET
	DEF_CMD	EV_SEQ_SYS_FLAG_PAIR_GET
	DEF_CMD	EV_SEQ_SYS_FLAG_PAIR_SET
	DEF_CMD	EV_SEQ_SYS_FLAG_PAIR_RESET
	DEF_CMD	EV_SEQ_SYS_FLAG_ONE_STEP_GET
	DEF_CMD	EV_SEQ_SYS_FLAG_ONE_STEP_SET
	DEF_CMD	EV_SEQ_SYS_FLAG_ONE_STEP_RESET
	DEF_CMD	EV_SEQ_SYS_FLAG_GAME_CLEAR_GET
	DEF_CMD	EV_SEQ_SYS_FLAG_GAME_CLEAR_SET

	DEF_CMD EV_SEQ_SET_UP_DOOR_ANIME
	DEF_CMD EV_SEQ_WAIT_3D_ANIME
	DEF_CMD EV_SEQ_FREE_3D_ANIME
	DEF_CMD EV_SEQ_OPEN_DOOR
	DEF_CMD EV_SEQ_CLOSE_DOOR

	DEF_CMD EV_SEQ_GET_SODATE_NAME
	DEF_CMD EV_SEQ_GET_SODATEYA_ZIISAN

	DEF_CMD	EV_SEQ_INIT_WATER_GYM			//���W��������
	DEF_CMD EV_SEQ_PUSH_WATER_GYM_BUTTON	//���W���{�^���v�b�V��

	DEF_CMD	EV_SEQ_INIT_GHOST_GYM			//�S�[�X�g�W��������
	DEF_CMD EV_SEQ_MOVE_GHOST_GYM_LIFT		//�S�[�X�g�W�����t�g���[�u
	DEF_CMD EV_SEQ_INIT_STEEL_GYM			//�|�W��������
	DEF_CMD EV_SEQ_INIT_COMBAT_GYM			//�i���W��������
	DEF_CMD EV_SEQ_INIT_ELEC_GYM			//�d�C�W��������
	DEF_CMD EV_SEQ_ROT_ELEC_GYM_GEAR		//�d�C�W���M�A��]

	DEF_CMD EV_SEQ_GET_POKE_COUNT			//�|�P�������擾

	DEF_CMD EV_SEQ_BAG_SET_PROC
	DEF_CMD EV_SEQ_BAG_GET_RESULT

	DEF_CMD EV_SEQ_POCKET_CHK
	DEF_CMD EV_SEQ_NUTS_NAME
	DEF_CMD EV_SEQ_SEIKAKU_NAME

	DEF_CMD EV_SEQ_SEED_GET_STATUS
	DEF_CMD EV_SEQ_SEED_GET_TYPE
	DEF_CMD EV_SEQ_SEED_GET_COMPOST
	DEF_CMD EV_SEQ_SEED_GET_GROUND
	DEF_CMD EV_SEQ_SEED_GET_NUTSCOUNT

	DEF_CMD EV_SEQ_SEED_SET_COMPOST
	DEF_CMD EV_SEQ_SEED_SET_NUTS
	DEF_CMD EV_SEQ_SEED_SET_WATER
	DEF_CMD EV_SEQ_SEED_TAKE_NUTS

	DEF_CMD EV_SEQ_SXY_POS_CHANGE
	DEF_CMD EV_SEQ_OBJ_POS_CHANGE
	DEF_CMD EV_SEQ_SXY_MV_CHANGE
	DEF_CMD EV_SEQ_SXY_DIR_CHANGE
	DEF_CMD EV_SEQ_SXY_EXIT_POS_CHANGE
	DEF_CMD EV_SEQ_SXY_BG_POS_CHANGE
	DEF_CMD EV_SEQ_OBJ_DIR_CHANGE

	DEF_CMD EV_SEQ_WAITICON_ADD
	DEF_CMD EV_SEQ_WAITICON_DEL

	DEF_CMD EV_SEQ_RETURN_SCRIPT_WK_SET

	DEF_CMD	EV_SEQ_ABKEY_TIMEWAIT

	DEF_CMD EV_SEQ_POKELIST_SET_PROC
	DEF_CMD EV_SEQ_UNION_POKELIST_SET_PROC
	DEF_CMD EV_SEQ_POKELIST_GET_RESULT

	DEF_CMD EV_SEQ_CON_POKELIST_SET_PROC
	DEF_CMD EV_SEQ_CON_POKELIST_GET_RESULT

	DEF_CMD EV_SEQ_CON_POKESTATUS_SET_PROC
	DEF_CMD EV_SEQ_POKESTATUS_GET_RESULT

	DEF_CMD EV_SEQ_TEMOTI_MONSNO
	DEF_CMD EV_SEQ_MONS_OWN_CHK

	DEF_CMD EV_SEQ_GET_POKE_COUNT2			//�|�P�������擾(�^�}�S������)
	DEF_CMD EV_SEQ_GET_POKE_COUNT3			//�|�P�������擾(�^�}�S�ƕm��������)
	DEF_CMD EV_SEQ_GET_POKE_COUNT4			//�|�P�������擾(�莝�����o�b���܂߂Đ킦��|�P���������̂��邩)
	DEF_CMD EV_SEQ_GET_TAMAGO_COUNT			//�^�}�S���擾�i�_�����܂��܂܂��j

	DEF_CMD EV_SEQ_UG_SHOP_MENU_INIT		//�n���̂��X�̃��j���[���J��
	DEF_CMD EV_SEQ_UG_SHOP_TALK_START		//�n���̂��X�̉�b�J�n
	DEF_CMD EV_SEQ_UG_SHOP_TALK_END			//�n���̂��X�̉�b�I��
	DEF_CMD EV_SEQ_UG_SHOP_ITEM_NAME		//�n���̂��X�̃A�C�e���̖��O��o�^
	DEF_CMD EV_SEQ_UG_SHOP_TRAP_NAME		//�n���̂��X�̃g���b�v�̖��O��o�^

	DEF_CMD EV_SEQ_SUB_MY_GOLD				//�����������i���[�N�Łj
	DEF_CMD EV_SEQ_HIKITORI_POKE			//�����Ă₩��|�P�������������
	DEF_CMD EV_SEQ_HIKITORI_LIST			//�Q�̂̃|�P�����̈������I���E�C���h�E�i�����Ă�j
	DEF_CMD EV_SEQ_MSG_SODATEYA_AISHOU		//�������b�Z�[�W�Z�b�g
	DEF_CMD EV_SEQ_MSGEXPANDBUF				//���b�Z�[�W���o��
	DEF_CMD EV_SEQ_DEL_SODATEYA_EGG			//�������ꂽ�^�}�S�̎󂯎�苑��
	DEF_CMD EV_SEQ_GET_SODATEYA_EGG			//�������ꂽ�^�}�S���󂯎��
	DEF_CMD EV_SEQ_HIKITORI_RYOUKIN			//�Ђ��Ƃ藿���Z�b�g
	DEF_CMD EV_SEQ_COMP_MY_GOLD				//�������r�i���[�N�Łj
	DEF_CMD EV_SEQ_TAMAGO_DEMO				//�^�}�S�z���f��
	DEF_CMD EV_SEQ_SODATEYA_POKELIST		//�����Ă�|�P�������X�g
	DEF_CMD EV_SEQ_SODATE_POKE_LEVEL_STR	//���x�����𕶎���Ŏ擾
	DEF_CMD EV_SEQ_MSG_AZUKE_SET			//�a����|�P�������Z�b�g�{�ԍ��擾
	DEF_CMD EV_SEQ_SET_SODATEYA_POKE		//�|�P������a����
	DEF_CMD EV_SEQ_OBJ_VISIBLE				//�L����������Ԃ�
	DEF_CMD EV_SEQ_OBJ_INVISIBLE			//�L������s����Ԃ�
	DEF_CMD	EV_SEQ_MAILBOX					//���[���{�b�N�X
	DEF_CMD	EV_SEQ_GET_MAILBOX_DATANUM		//���[���{�b�N�X���̃f�[�^���擾
	DEF_CMD	EV_SEQ_RANKING_VIEW				//�M�l�X�z�[�������L���O��ʌĂяo��

	DEF_CMD	EV_SEQ_GET_TIME_ZONE			//���ԑю擾
	DEF_CMD	EV_SEQ_GET_RND					//�����_�����擾
	DEF_CMD	EV_SEQ_GET_RND_NEXT				//�����_�����擾

	DEF_CMD	EV_SEQ_GET_NATSUKI				//�Ȃ��x�擾
	DEF_CMD	EV_SEQ_ADD_NATSUKI				//�Ȃ��x�𑝂₷
	DEF_CMD	EV_SEQ_SUB_NATSUKI				//�Ȃ��x�����炷

	DEF_CMD EV_SEQ_HIKITORI_NAME_SET		//�Ђ��Ƃ�Q�̖̂��O�Z�b�g

	DEF_CMD	EV_SEQ_PLAYER_DIR_GET			//���@�̕����擾

	DEF_CMD	EV_SEQ_GET_SODATEYA_AISHOU		//�����Ă�2�̂̑����Q�b�g
	DEF_CMD	EV_SEQ_SODATEYA_TAMAGO_CHK	//�^�}�S���Y�܂�Ă��邩�`�F�b�N

	DEF_CMD	EV_SEQ_TEMOTI_POKE_CHK			//�莝���ɓ���̃|�P���������邩���`�F�b�N
	DEF_CMD	EV_SEQ_OOKISA_RECORD_CHK		//�L�^�Ǝ莝���|�P�����̔�r
	DEF_CMD	EV_SEQ_OOKISA_RECORD_SET		//�莝���̃|�P�����ŋL�^�X�V
	DEF_CMD	EV_SEQ_OOKISA_TEMOTI_SET_BUF	//�莝���̃|�P�����̑傫���𐔒l�ɂ��ĕ����o�b�t�@�փZ�b�g
	DEF_CMD	EV_SEQ_OOKISA_KIROKU_SET_BUF	//�L�^�|�P�����̑傫���𐔒l�ɂ��ĕ����o�b�t�@�փZ�b�g
	DEF_CMD	EV_SEQ_OOKISA_KURABE_INIT		//�傫����׏�����

	DEF_CMD	EV_SEQ_WAZALIST_SET_PROC		//���U�I����ʌĂяo��
	DEF_CMD	EV_SEQ_WAZALIST_GET_RESULT		//���U�I����ʌ��ʎ��o��
	DEF_CMD	EV_SEQ_WAZA_COUNT				//�����Ă��郏�U�����J�E���g
	DEF_CMD	EV_SEQ_WAZA_DEL					//���U������
	DEF_CMD	EV_SEQ_TEMOTI_WAZANO			//�莝���̃��U�̔ԍ��擾
	DEF_CMD	EV_SEQ_TEMOTI_WAZA_NAME			//�莝�����U�����o�b�t�@��

	DEF_CMD	EV_SEQ_FNOTE_START_SET			//�`���m�[�g�J�n�f�[�^�Z�b�g
	DEF_CMD	EV_SEQ_FNOTE_DATA_MAKE			//�`���m�[�g�f�[�^�쐬
	DEF_CMD	EV_SEQ_FNOTE_DATA_SAVE			//�`���m�[�g�f�[�^�Z�[�u

	DEF_CMD	EV_SEQ_SYS_FLAG_KAIRIKI
	DEF_CMD EV_SEQ_SYS_FLAG_FLASH
	DEF_CMD EV_SEQ_SYS_FLAG_KIRIBARAI

	DEF_CMD	EV_SEQ_IMC_ACCE_ADD_ITEM
	DEF_CMD	EV_SEQ_IMC_ACCE_ADD_ITEM_CHK
	DEF_CMD	EV_SEQ_IMC_ACCE_ITEM_CHK
	DEF_CMD	EV_SEQ_IMC_BG_ADD_ITEM
	DEF_CMD	EV_SEQ_IMC_BG_ITEM_CHK
	
	DEF_CMD	EV_SEQ_NUTMIXER_CALL			//�܂��܂������Ăяo��
	DEF_CMD	EV_SEQ_NUTMIXER_PLAY_CHECK		//�܂��܂������v���C���ł��邩�`�F�b�N
	
	DEF_CMD	EV_SEQ_BTOWER_APP_CALL			//�o�g���^���[�A�v���P�[�V�����R�[��
	
	//��������o�g���^���[
	DEF_CMD	EV_SEQ_BATTLE_TOWER_WORK_CLEAR		//�o�g���^���[���[�N������
	DEF_CMD	EV_SEQ_BATTLE_TOWER_WORK_INIT		//�o�g���^���[���[�N�m��
	DEF_CMD	EV_SEQ_BATTLE_TOWER_WORK_RELEASE	//�o�g���^���[���[�N���
	DEF_CMD	EV_SEQ_BATTLE_TOWER_TOOLS			//�o�g���^���[�c�[��
	DEF_CMD	EV_SEQ_BATTLE_TOWER_GET_SEVEN_POKE	//5�l�O�̃|�P�����f�[�^�Q�b�g
	DEF_CMD	EV_SEQ_BATTLE_TOWER_IS_PRIZE_GET	//�o�g���^���[�@�v���C�Y�擾
	DEF_CMD	EV_SEQ_BATTLE_TOWER_IS_PRIZEMAN_SET	//�o�g���^���[�@�v���C�Y�������q�g
	DEF_CMD	EV_SEQ_BATTLE_TOWER_SEND_BUF		//�o�g���^���[�@�ėp�f�[�^���M
	DEF_CMD	EV_SEQ_BATTLE_TOWER_RECV_BUF		//�o�g���^���[�@�ėp�f�[�^��M
	DEF_CMD	EV_SEQ_BATTLE_TOWER_GET_LEADER_ROOM_ID	//�o�g���^���[�@���[�_�[�f�[�^��RoomID�擾
	DEF_CMD	EV_SEQ_BATTLE_TOWER_IS_READER_DATA_EXIST	//�o�g���^���[�@���[�_�[�f�[�^�̗L��
	
	//�������܂Ńo�g���^���[
	DEF_CMD	EV_SEQ_RECORD_INC					//���R�[�h�C���N�������g
	DEF_CMD	EV_SEQ_RECORD_GET					//���R�[�h�Q�b�g
	DEF_CMD	EV_SEQ_RECORD_SET					//���R�[�h�Z�b�g
	

	DEF_CMD	EV_SEQ_ZUKAN_CHK_SHINOU				//�V���I�E�}�ӂ��������Ă��邩�`�F�b�N
	DEF_CMD	EV_SEQ_ZUKAN_CHK_NATIONAL			//�S���}�ӂ��������Ă��邩�`�F�b�N
	DEF_CMD	EV_SEQ_ZUKAN_RECONGNIZE_SHINOU		//�V���I�E�}�Ӂh�Ђ傤���傤�h
	DEF_CMD	EV_SEQ_ZUKAN_RECONGNIZE_NATIONAL	//�S���}�Ӂh�Ђ傤���傤�h

	DEF_CMD	EV_SEQ_URAYAMA_ENCOUNT_SET			//�E�����}�G���J�E���g�Z�b�g
	DEF_CMD	EV_SEQ_URAYAMA_ENCOUNT_NO_CHK		//�E�����}�G���J�E���g�`�F�b�N�i���݂̊Y������|�P�����ԍ��擾�j

	DEF_CMD	EV_SEQ_POKE_MAIL_CHK
	DEF_CMD	EV_SEQ_PAPERPLANE_SET
	DEF_CMD	EV_SEQ_POKE_MAIL_DEL
	DEF_CMD	EV_SEQ_KASEKI_COUNT	
	DEF_CMD	EV_SEQ_ITEMLIST_SET_PROC
	DEF_CMD	EV_SEQ_ITEMLIST_GET_RESULT
	DEF_CMD	EV_SEQ_ITEMNO_TO_MONSNO
	DEF_CMD	EV_SEQ_KASEKI_ITEMNO

	DEF_CMD	EV_SEQ_POKE_LEVEL_CHK

	DEF_CMD EV_SEQ_APPROVE_POISON_DEAD

	DEF_CMD	EV_SEQ_FINISH_MAP_PROC

	DEF_CMD EV_SEQ_DEBUG_WATCH_VALUE

	DEF_CMD	EV_SEQ_MSG_ALLPUT_ARC
	DEF_CMD	EV_SEQ_MSG_ARC
	DEF_CMD	EV_SEQ_MSG_ALLPUT_PMS
	DEF_CMD	EV_SEQ_MSG_PMS
	DEF_CMD	EV_SEQ_MSG_BTOWER_APPEAR
	DEF_CMD	EV_SEQ_MSG_NG_POKE_NAME

	DEF_CMD EV_SEQ_GET_BEFORE_ZONEID
	DEF_CMD EV_SEQ_GET_NOW_ZONEID

	DEF_CMD	EV_SEQ_SAFARI_CTRL

	DEF_CMD	EV_SEQ_COLOSSEUM_MAP_CHANGE_IN
	DEF_CMD	EV_SEQ_COLOSSEUM_MAP_CHANGE_OUT

	DEF_CMD	EV_SEQ_WIFI_EARTH_SET_PROC

	DEF_CMD EV_SEQ_CALL_SAFARI_SCOPE

	DEF_CMD	EV_SEQ_COMM_GET_CURRENT_ID

	DEF_CMD	EV_SEQ_POKE_WINDOW_PUT
	DEF_CMD	EV_SEQ_POKE_WINDOW_DEL
	DEF_CMD	EV_SEQ_BTL_SEARCHER_EVENT_CALL
	DEF_CMD	EV_SEQ_BTL_SEARCHER_DIR_MV_SET

	DEF_CMD EV_SEQ_MSG_AUTOGET

	DEF_CMD EV_SEQ_CLIMAXDEMO

	DEF_CMD	EV_SEQ_INIT_SAFARI_TRAIN
	DEF_CMD	EV_SEQ_MOVE_SAFARI_TRAIN
	DEF_CMD	EV_SEQ_CHECK_SAFARI_TRAIN

	DEF_CMD	EV_SEQ_PLAYER_HEGIHT_VALID

	DEF_CMD	EV_SEQ_GET_POKE_SEIKAKU
	DEF_CMD	EV_SEQ_CHK_POKE_SEIKAKU_ALL
	DEF_CMD	EV_SEQ_UNDERGROUND_TALK_COUNT

	DEF_CMD	EV_SEQ_NATURAL_PARK_WALK_COUNT_CLEAR
	DEF_CMD	EV_SEQ_NATURAL_PARK_WALK_COUNT_GET
	DEF_CMD	EV_SEQ_NATURAL_PARK_ACCESSORY_NO_GET

	DEF_CMD	EV_SEQ_GET_NEWS_POKE_NO
	DEF_CMD	EV_SEQ_NEWS_COUNT_SET
	DEF_CMD	EV_SEQ_NEWS_COUNT_CHK

	DEF_CMD	EV_SEQ_START_GENERATE
	DEF_CMD	EV_SEQ_ADD_MOVE_POKE

	DEF_CMD	EV_SEQ_GROUP

	DEF_CMD	EV_SEQ_OSHIE_WAZA_COUNT					/*�d�l�ύX�ɂ�薢����*/
	DEF_CMD	EV_SEQ_REMAIND_WAZA_COUNT
	DEF_CMD	EV_SEQ_OSHIE_WAZALIST_SET_PROC			/*�d�l�ύX�ɂ�薢����*/
	DEF_CMD	EV_SEQ_REMAIND_WAZALIST_SET_PROC
	DEF_CMD	EV_SEQ_OSHIE_WAZALIST_GET_RESULT		/*�d�l�ύX�ɂ�薢����*/
	DEF_CMD	EV_SEQ_REMAIND_WAZALIST_GET_RESULT
	DEF_CMD	EV_SEQ_NORMAL_WAZALIST_SET_PROC
	DEF_CMD	EV_SEQ_NORMAL_WAZALIST_GET_RESULT

	DEF_CMD	EV_SEQ_FLD_TRADE_ALLOC
	DEF_CMD	EV_SEQ_FLD_TRADE_MONSNO
	DEF_CMD	EV_SEQ_FLD_TRADE_CHG_MONSNO
	DEF_CMD	EV_SEQ_FLD_TRADE_EVENT
	DEF_CMD	EV_SEQ_FLD_TRADE_DEL
	DEF_CMD	EV_SEQ_ZUKAN_TEXT_VER_UP
	DEF_CMD	EV_SEQ_ZUKAN_SEX_VER_UP
	DEF_CMD	EV_SEQ_ZENKOKU_ZUKAN_FLAG

	DEF_CMD	EV_SEQ_CHK_RIBBON_COUNT
	DEF_CMD	EV_SEQ_CHK_RIBBON_COUNT_ALL
	DEF_CMD	EV_SEQ_CHK_RIBBON
	DEF_CMD	EV_SEQ_SET_RIBBON
	DEF_CMD	EV_SEQ_RIBBON_NAME
	DEF_CMD	EV_SEQ_CHK_PRMEXP
	DEF_CMD	EV_SEQ_CHK_WEEK

	DEF_CMD	EV_SEQ_TV
	DEF_CMD	EV_SEQ_TV_ENTRY_WATCH_HIDE_ITEM
	DEF_CMD	EV_SEQ_TV_INTERVIEW
	DEF_CMD	EV_SEQ_TV_INTERVIEW_CHK

	DEF_CMD	EV_SEQ_REGULATION_LIST_CALL

	DEF_CMD	EV_SEQ_ASHIATO_CHK
	DEF_CMD	EV_SEQ_PC_RECOVER_ANM
	DEF_CMD	EV_SEQ_ELEVATOR_ANM
	DEF_CMD	EV_SEQ_CALL_SHIP_DENO

	DEF_CMD EV_SEQ_MYSTERY_POSTMAN

	DEF_CMD EV_SEQ_DEBUG_PRINT_WORK	
	DEF_CMD EV_SEQ_DEBUG_PRINT_FLAG
	DEF_CMD EV_SEQ_DEBUG_PRINT_WORK_STATIONED
	DEF_CMD EV_SEQ_DEBUG_PRINT_FLAG_STATIONED

	DEF_CMD	EV_SEQ_PMS_INPUT_SINGLE
	DEF_CMD	EV_SEQ_PMS_INPUT_DOUBLE
	DEF_CMD	EV_SEQ_PMS_BUF

	DEF_CMD	EV_SEQ_PM_VERSION_GET

	DEF_CMD	EV_SEQ_FRONT_POKEMON

	DEF_CMD	EV_SEQ_TEMOTI_POKE_TYPE	

	DEF_CMD	EV_SEQ_AIKOTOBA_KABEGAMI_SET
	DEF_CMD	EV_SEQ_GET_UG_HATA_NUM

	DEF_CMD	EV_SEQ_SETUP_PASO_ANM
	DEF_CMD	EV_SEQ_START_PASO_ON_ANM
	DEF_CMD	EV_SEQ_START_PASO_OFF_ANM

	DEF_CMD	EV_SEQ_GET_KUJI_ATARI_NUM
	DEF_CMD	EV_SEQ_KUJI_ATARI_CHK
	DEF_CMD	EV_SEQ_KUJI_ATARI_INIT
	DEF_CMD	EV_SEQ_NICK_NAME_PC

	DEF_CMD EV_SEQ_COUNT_POKEBOX_SPACE

	DEF_CMD EV_SEQ_POKEPARK_CONTROL
	DEF_CMD EV_SEQ_COUNT_POKEPARK_BOX
	DEF_CMD EV_SEQ_TRANS_POKEPARK_MONS
	DEF_CMD EV_SEQ_GET_POKEPARK_SCORE

	DEF_CMD EV_SEQ_ACCE_SHOP
	
	DEF_CMD EV_SEQ_PLAYER_REPORT_DRAW_SET
	DEF_CMD EV_SEQ_PLAYER_REPORT_DRAW_DEL

	DEF_CMD EV_SEQ_DENDOU_BALL_ANM
	DEF_CMD EV_SEQ_INIT_FLD_LIFT
	DEF_CMD EV_SEQ_MOVE_FLD_LIFT
	DEF_CMD EV_SEQ_CHECK_FLD_LIFT

	DEF_CMD EV_SEQ_SETUP_RAH_CYL
	DEF_CMD EV_SEQ_START_RAH_CYL

	DEF_CMD EV_SEQ_ADD_SCORE
	DEF_CMD EV_SEQ_ACCE_NAME

	DEF_CMD EV_SEQ_PARTY_MONSNO_CHECK			// �p�[�e�B�Ɉ����P�̃|�P���������邩�`�F�b�N
	DEF_CMD EV_SEQ_PARTY_DEOKISISUFORM_CHANGE	// �p�[�e�B���̃f�I�L�V�X�̃t�H������ύX
	DEF_CMD EV_SEQ_CHECKMINOMUCHICOMP	// �~�m���b�`3�킻�������

	DEF_CMD EV_SEQ_POKETCH_HOOK_SET
	DEF_CMD EV_SEQ_POKETCH_HOOK_RESET

	DEF_CMD	EV_SEQ_SLOT_MACHINE

	DEF_CMD	EV_SEQ_GET_NOW_HOUR
	
	DEF_CMD	EV_SEQ_FLDOBJ_SHAKE_ANM		//�t�B�[���hOBJ��h�炷�A�j��
	DEF_CMD	EV_SEQ_FLDOBJ_BLINK_ANM		//�t�B�[���hOBJ��Blink������A�j��
	DEF_CMD	EV_SEQ_D20R0106_LEGEND_IS_UNSEAL	//���W�L���O����`�F�b�N

	DEF_CMD	EV_SEQ_DRESSING_IMC_ACCE_CHECK
	DEF_CMD	EV_SEQ_UNKNOWN_MSG
	DEF_CMD	EV_SEQ_AGB_CARTRIDGE_VER_GET	// �������Ă���AGB�J�[�g���b�WVer�擾

	DEF_CMD	EV_SEQ_UNDERGROUND_TALK_COUNT_CLEAR		//��b�����J�E���g���N���A(�J�i���퓬�p�j

	DEF_CMD	EV_SEQ_HIDEMAP_STATE_CHANGE		//�B���}�b�v�X�e�[�^�X�`�F���W
	DEF_CMD	EV_SEQ_NAMEIN_MONUMENT			//r224�Δ薼����
	DEF_CMD	EV_SEQ_MONUMENT_NAME			//r224�Δ薼�^�O�W�J

	DEF_CMD EV_SEQ_IMC_BG_NAME_SET			// imc�̔w�i����ݒ�
	DEF_CMD	EV_SEQ_COMP_COIN
	DEF_CMD	EV_SEQ_SLOT_RENTYAN_CHK			//�X���b�g�Ń����`�������Ă��邩
	DEF_CMD	EV_SEQ_ADD_COIN_CHK
	DEF_CMD	EV_SEQ_LEVEL_JIJII_NO 
	DEF_CMD	EV_SEQ_POKE_LEVEL_GET
	DEF_CMD	EV_SEQ_IMC_ACCE_SUB_ITEM
	DEF_CMD	EV_SEQ_C08R0801SCOPECAMERASET
	DEF_CMD	EV_SEQ_LEVEL_JIJII_INIT

	DEF_CMD	EV_SEQ_TV_ENTRY_PARKINFO
	
	DEF_CMD EV_SEQ_NEW_NANKAI_WORD_SET
	DEF_CMD EV_SEQ_REGULAR_CHECK		
	DEF_CMD	EV_SEQ_NANKAI_WORD_COMPLETE_CHECK
	DEF_CMD EV_SEQ_NUMBER_NAME_EX			//���l�^�O�W�J�@�f�B�X�v���C���[�h�w��ver
	DEF_CMD EV_SEQ_TEMOTI_POKE_CONTEST_STATUS_GET

	DEF_CMD	EV_SEQ_BIRTH_DAY_CHECK
	DEF_CMD	EV_SEQ_SND_INITIAL_VOL_SET
	DEF_CMD	EV_SEQ_ANOON_SEE_NUM
	DEF_CMD EV_SEQ_D17SYSTEM_MAP_SELECT		//D17�߂炸�̓��A�@�}�b�v���I
	DEF_CMD EV_SEQ_UNDERGROUND_TOOL_GIVE_COUNT
	DEF_CMD EV_SEQ_UNDERGROUND_KASEKI_DIG_COUNT
	DEF_CMD EV_SEQ_UNDERGROUND_TRAP_HIT_COUNT
	DEF_CMD	EV_SEQ_POFIN_ADD
	DEF_CMD	EV_SEQ_POFIN_ADD_CHK

	DEF_CMD	EV_SEQ_IS_HAIHU_EVENT_ENABLE	//�z�z�C�x���g�L���`�F�b�N

	DEF_CMD	EV_SEQ_POKE_WINDOW_PUT_PP
	DEF_CMD	EV_SEQ_POKE_WINDOW_ANM
	DEF_CMD	EV_SEQ_POKE_WINDOW_ANM_WAIT
	DEF_CMD	EV_SEQ_DENDOU_NUM_GET

	DEF_CMD	EV_SEQ_SODATEYA_POKELIST_SET_PROC
	DEF_CMD	EV_SEQ_SODATEYA_POKELIST_GET_RESULT
	
	DEF_CMD	EV_SEQ_GET_RANDOM_HIT	//�w�肵���m����TRUE,FALSE��Ԃ�

	DEF_CMD	EV_SEQ_UNDERGROUND_TALK_COUNT2

	//�o�g���|�C���g�֘A��������
	DEF_CMD	EV_SEQ_BTL_POINT_WIN_WRITE
	DEF_CMD	EV_SEQ_BTL_POINT_WIN_DEL
	DEF_CMD	EV_SEQ_BTL_POINT_WRITE
	DEF_CMD	EV_SEQ_GET_BTL_POINT
	DEF_CMD	EV_SEQ_BTL_POINT_ADD
	DEF_CMD	EV_SEQ_BTL_POINT_SUB
	DEF_CMD	EV_SEQ_COMP_BTL_POINT
	DEF_CMD	EV_SEQ_GET_BP_GIFT
	//�o�g���|�C���g�֘A�����܂�
	DEF_CMD	EV_SEQ_UNION_VIEW_TR_TYPE_NO_GET

	DEF_CMD	EV_SEQ_BMPMENU_MAKE_LIST16
	
	DEF_CMD	EV_SEQ_HIDENEFF_START
	DEF_CMD	EV_SEQ_ZISHIN

	DEF_CMD	EV_SEQ_TRAINER_MULTI_BTL_SET

	DEF_CMD	EV_SEQ_OBJ_ANIME_POS

	DEF_CMD EV_SEQ_UG_BALL_CHECK

	DEF_CMD EV_SEQ_CHECK_MY_GSID
	DEF_CMD EV_SEQ_FRIEND_DATA_NUM
	DEF_CMD EV_SEQ_NPC_TRADE_POKELIST_SET_PROC

	DEF_CMD EV_SEQ_GET_COIN_GIFT
	DEF_CMD EV_SEQ_AUSU_ITEM_CHECK
	DEF_CMD EV_SEQ_SUB_WK_COIN
	DEF_CMD EV_SEQ_COMP_WK_COIN
	DEF_CMD EV_SEQ_AIKOTOBA_OKURIMONO_CHK

	DEF_CMD	EV_SEQ_CB_SEAL_KIND_NUM_GET

	DEF_CMD	EV_SEQ_WIFI_HUSIGINAOKURIMONO_OPEN_FLAG_SET
	DEF_CMD	EV_SEQ_MOVE_CODE_GET

	DEF_CMD	EV_SEQ_BGM_PLAY_CHECK
	DEF_CMD	EV_SEQ_UNION_GET_CARD_TALK_NO

	DEF_CMD	EV_SEQ_WIRELESS_ICON_EASY
	DEF_CMD	EV_SEQ_WIRELESS_ICON_EASY_END

	DEF_CMD	EV_SEQ_SAVE_FIELD_OBJ
	
	DEF_CMD	EV_SEQ_SEAL_NAME

	DEF_CMD EV_SEQ_TALK_OBJ_PAUSE_ALL

	DEF_CMD	EV_SEQ_SET_ESCAPE_LOCATION
	DEF_CMD	EV_SEQ_FIELDOBJ_BITSET_FELLOWHIT

	DEF_CMD	EV_SEQ_DAME_TAMAGO_CHK_ALL

	DEF_CMD EV_SEQ_TV_ENTRY_WATCH_CHANGE_NAME

	DEF_CMD	EV_SEQ_UNION_BMPMENU_START
	DEF_CMD	EV_SEQ_UNION_BATTLE_START_CHECK
	DEF_CMD	EV_SEQ_COMM_DIRECT_END_TIMING
	DEF_CMD	EV_SEQ_HAIFU_POKE_RETRY_CHECK
	DEF_CMD	EV_SEQ_SP_WILD_BTL_SET
	DEF_CMD EV_SEQ_GET_TRCARD_RANK 
	DEF_CMD	EV_SEQ_BICYCLE_REQ_NON_BGM

	DEF_CMD	EV_SEQ_MSG_SP_AUTO

	DEF_CMD	EV_SEQ_REPORT_WIN_OPEN
	DEF_CMD EV_SEQ_REPORT_WIN_CLOSE

	DEF_CMD	EV_SEQ_FIELD_SCOPE_MODE_SET

//=============================================================================
/**
 *	��{�R�}���h
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�������Ȃ�
 */
//-----------------------------------------------------------------------------
	.macro	_NOP
	.short	EV_SEQ_NOP
	.endm

//-----------------------------------------------------------------------------
/**
 *	�_�~�[
 */
//-----------------------------------------------------------------------------
	.macro	_DUMMY
	.short	EV_SEQ_DUMMY
	.endm

//-----------------------------------------------------------------------------
/**
 *	�X�N���v�g�̏I��
 */
//-----------------------------------------------------------------------------
	.macro	_END
	.short	EV_SEQ_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	�E�F�C�g
 */
//-----------------------------------------------------------------------------
	.macro	_TIME_WAIT time,ret_wk
	.short	EV_SEQ_TIME_WAIT
	.short	\time
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	�f�[�^���[�h�E�X�g�A�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 * ���z�}�V���̔ėp���W�X�^��1byte�̒l���i�[
 */
//-----------------------------------------------------------------------------
	.macro	_LD_REG_VAL	r,val
	.short	EV_SEQ_LD_REG_VAL
	.byte	\r
	.byte	\val
	.endm

//-----------------------------------------------------------------------------
/**
 * ���z�}�V���̔ėp���W�X�^��4byte�̒l���i�[
 */
//-----------------------------------------------------------------------------
	.macro	_LD_REG_WDATA	r,wdata
	.short	EV_SEQ_LD_REG_WDATA
	.byte	\r
	.long	\wdata
	.endm

//-----------------------------------------------------------------------------
/**
 * ���z�}�V���̔ėp���W�X�^�ɃA�h���X���i�[
 */
//-----------------------------------------------------------------------------
	.macro	_LD_REG_ADR	reg,ADDRESS
	.short	EV_SEQ_LD_REG_ADR
	.byte	\reg
	.long	\ADDRESS
	.endm

//-----------------------------------------------------------------------------
/**
 * �A�h���X�̒��g�ɒl����
 */
//-----------------------------------------------------------------------------
	.macro	_LD_ADR_VAL	adrs,val
	.short	EV_SEQ_LD_ADR_VAL
	.long	\adrs
	.byte	\val
	.endm

//-----------------------------------------------------------------------------
/**
 * �A�h���X�̒��g�ɉ��z�}�V���̔ėp���W�X�^�̒l����
 */
//-----------------------------------------------------------------------------
	.macro	_LD_ADR_REG	adrs,reg
	.short	EV_SEQ_LD_ADR_REG
	.long	\adrs
	.byte	\reg
	.endm

//-----------------------------------------------------------------------------
/**
 * ���z�}�V���̔ėp���W�X�^�̒l��ėp���W�X�^�ɃR�s�[
 */
//-----------------------------------------------------------------------------
	.macro	_LD_REG_REG	r1,r2
	.short	EV_SEQ_LD_REG_REG
	.byte	\r1,\r2
	.endm

//-----------------------------------------------------------------------------
/**
 * �A�h���X�̒��g�ɃA�h���X�̒��g����
 */
//-----------------------------------------------------------------------------
	.macro	_LD_ADR_ADR	adr1,adr2
	.short	EV_SEQ_LD_ADR_ADR
	.long	\adr1
	.long	\adr2
	.endm


//=============================================================================
/**
 *	��r�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	���z�}�V���̔ėp���W�X�^���r
 */
//-----------------------------------------------------------------------------
	.macro	_CP_REG_REG	r1,r2
	.short	EV_SEQ_CP_REG_REG
	.byte	\r1,\r2
	.endm

//-----------------------------------------------------------------------------
/**
 *	���z�}�V���̔ėp���W�X�^�ƒl���r
 */
//-----------------------------------------------------------------------------
	.macro	_CP_REG_VAL	r1,val
	.short	EV_SEQ_CP_REG_VAL
	.byte	\r1,\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	���z�}�V���̔ėp���W�X�^�ƃA�h���X�̒��g���r
 */
//-----------------------------------------------------------------------------
	.macro	_CP_REG_ADR	r1,adrs
	.short	EV_SEQ_CP_REG_ADR
	.byte	\r1
	.long	\adrs
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�h���X�̒��g�Ɖ��z�}�V���̔ėp���W�X�^���r
 */
//-----------------------------------------------------------------------------
	.macro	_CP_ADR_REG	adrs,r1
	.short	EV_SEQ_CP_ADR_REG
	.long	\adrs
	.byte	\r1
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�h���X�̒��g�ƒl���r
 */
//-----------------------------------------------------------------------------
	.macro	_CP_ADR_VAL	adrs,val
	.short	EV_SEQ_CP_ADR_VAL
	.long	\adrs
	.byte	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�h���X�̒��g�ƃA�h���X�̒��g���r
 */
//-----------------------------------------------------------------------------
	.macro	_CP_ADR_ADR	adr1,adr2
	.short	EV_SEQ_CP_ADR_ADR
	.long	\adr1
	.long	\adr2
	.endm

//-----------------------------------------------------------------------------
/**
 *	���[�N�ƒl�̔�r
 */
//-----------------------------------------------------------------------------
	.macro	_CMPVAL	wk,val
	.short	EV_SEQ_CP_WK_VAL
	.short	\wk
	.short	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	���[�N�ƃ��[�N�̔�r
 */
//-----------------------------------------------------------------------------
	.macro	_CMPWK	wk1,wk2
	.short	EV_SEQ_CP_WK_WK
	.short	\wk1
	.short	\wk2
	.endm

//-----------------------------------------------------------------------------
/**
 * �f�o�b�O�p�F���[�N���\��
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_WATCH_WORK	wk
	.short	EV_SEQ_DEBUG_WATCH_VALUE
	.short	\wk
	.endm

//=============================================================================
/**
 *	���z�}�V���֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	���z�}�V���ǉ�(�؂�ւ��͂����A����œ��삵�܂��I)
 */
//-----------------------------------------------------------------------------
	.macro	_VM_ADD id
	.short	EV_SEQ_VM_ADD
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 * ���[�J���X�N���v�g���E�F�C�g��Ԃɂ��āA���ʃX�N���v�g�𓮍삳���܂�
 */
//-----------------------------------------------------------------------------
	.macro	_CHG_COMMON_SCR id
	.short	EV_SEQ_CHG_COMMON_SCR
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	���ʃX�N���v�g���I�����āA���[�J���X�N���v�g���ĊJ�����܂�
 */
//-----------------------------------------------------------------------------
	.macro	_CHG_LOCAL_SCR
	.short	EV_SEQ_CHG_LOCAL_SCR
	.endm


//=============================================================================
/**
 *	�W�����v�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�W�����v
 */
//-----------------------------------------------------------------------------
	.macro	_JUMP adrs
	.short	EV_SEQ_JUMP
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ_ID�@�W�����v
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_ID_JUMP act,adrs
	.short	EV_SEQ_OBJ_ID_JUMP
	.byte	\act
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	BG_ID�@�W�����v
 */
//-----------------------------------------------------------------------------
	.macro	_BG_ID_JUMP act,adrs
	.short	EV_SEQ_BG_ID_JUMP
	.byte	\act
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C�x���g�N�����̎�l���̌�����r�W�����v
 *	(���݂̌����ł͂Ȃ��̂Œ��ӁI)
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_DIR_JUMP dir,adrs
	.short	EV_SEQ_PLAYER_DIR_JUMP
	.byte	\dir
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�[��
 */
//-----------------------------------------------------------------------------
	.macro	_CALL adrs
	.short	EV_SEQ_CALL
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�[�����Ăяo�����A�h���X�ɖ߂�
 */
//-----------------------------------------------------------------------------
	.macro	_RET
	.short	EV_SEQ_RET
	.endm

//-----------------------------------------------------------------------------
/**
 *	IF�W�����v
 */
//-----------------------------------------------------------------------------
	.macro	_IF_JUMP cond,adrs
	.short	EV_SEQ_IF_JUMP
	.byte	\cond
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	IF�R�[��
 */
//-----------------------------------------------------------------------------
	.macro	_IF_CALL cond,adrs
	.short	EV_SEQ_IF_CALL
	.byte	\cond
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	�l���r�A�����ǂ���̏ꍇ����(�W�����v)
 */
//-----------------------------------------------------------------------------
	.macro	_IFVAL_JUMP wk,cond,val,adrs
	_CMPVAL	\wk,\val
	.short	EV_SEQ_IF_JUMP
	.byte	\cond
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	�l���r�A�����ǂ���̏ꍇ����(�R�[��)
 */
//-----------------------------------------------------------------------------
	.macro	_IFVAL_CALL wk,cond,val,adrs
	_CMPVAL	\wk,\val
	.short	EV_SEQ_IF_CALL
	.byte	\cond
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	���[�N���r�A�����ǂ���̏ꍇ����(�W�����v)
 */
//-----------------------------------------------------------------------------
	.macro	_IFWK_JUMP wk1,cond,wk2,adrs
	_CMPWK	\wk1,\wk2
	.short	EV_SEQ_IF_JUMP
	.byte	\cond
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	���[�N���r�A�����ǂ���̏ꍇ����(�R�[��)
 */
//-----------------------------------------------------------------------------
	.macro	_IFWK_CALL wk1,cond,wk2,adrs
	_CMPWK	\wk1,\wk2
	.short	EV_SEQ_IF_CALL
	.byte	\cond
	.long	((\adrs-.)-4)
	.endm

//=============================================================================
/**
 *	switch�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	switch �` case �\��
 *
 *  �X�N���v�g���䃏�[�N�Ŋm�ۂ���郏�[�N(SCWK_REG0)���g�p���Ă���̂ŁA
 *	FLAG_CHANGE,INIT_CHANGE�Ȃǂł͎g�p�ł��܂���I
 *	SCENE_CHANGE�͎g�p�ł��܂��B
 */
//-----------------------------------------------------------------------------
	.macro	_SWITCH wk
	_LDWK	SCWK_REG0,\wk
	.endm

	.macro	_CASE_JUMP	val,adr
	_CMPVAL	SCWK_REG0,\val
	_IF_JUMP	EQ,\adr
	.endm

//-----------------------------------------------------------------------------
/**
 * �X�N���v�g�E�B���h�E�\������B�L�����Z��
 */
//-----------------------------------------------------------------------------
	.macro	_CASE_CANCEL	adr
	_CMPVAL	SCWK_REG0,EV_WIN_B_CANCEL
	_IF_JUMP	EQ,\adr
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ҋ@�A�C�R���\��
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_WAITICON
	.short	EV_SEQ_WAITICON_ADD
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ҋ@�A�C�R������
 */
//-----------------------------------------------------------------------------
	.macro	_DEL_WAITICON
	.short	EV_SEQ_WAITICON_DEL
	.endm

//=============================================================================
/**
 *	�C�x���g�t���O�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�t���O�̃Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_SET num
	.short	EV_SEQ_FLAG_SET
	.short	\num
	.endm

	//�����t���O�Z�b�g
	.macro	_ARRIVE_FLAG_SET num
	_FLAG_SET	(\num + SYS_FLAG_ARRIVE_START)
	.endm

//-----------------------------------------------------------------------------
/**
 *	�t���O�̃��Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_RESET num
	.short	EV_SEQ_FLAG_RESET
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	�t���O�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_CHECK num
	.short	EV_SEQ_FLAG_CHECK
	.short	\num
	.endm

	//�t���OON�̎��ɕ���(JUMP)
	.macro	_IF_FLAGON_JUMP num,adrs
	_FLAG_CHECK \num
	_IF_JUMP	FLGON,\adrs
	.endm

	//�t���OOFF�̎��ɕ���(JUMP)
	.macro	_IF_FLAGOFF_JUMP num,adrs
	_FLAG_CHECK \num
	_IF_JUMP	FLGOFF,\adrs
	.endm

	//�t���OON�̎��ɕ���(CALL)
	.macro	_IF_FLAGON_CALL num,adrs
	_FLAG_CHECK \num
	_IF_CALL	FLGON,\adrs
	.endm

	//�t���OOFF�̎��ɕ���(CALL)
	.macro	_IF_FLAGOFF_CALL num,adrs
	_FLAG_CHECK \num
	_IF_CALL	FLGOFF,\adrs
	.endm

//-----------------------------------------------------------------------------
/**
 * ���[�N�̒l���t���O�i���o�[�Ƃ��ă`�F�b�N����I
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_CHECK_WK wk,ret_wk
	.short	EV_SEQ_FLAG_CHECK_WK
	.short	\wk
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ���[�N�̒l���t���O�i���o�[�Ƃ��ăZ�b�g����I
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_SET_WK wk
	.short	EV_SEQ_FLAG_SET_WK
	.short	\wk
	.endm


//=============================================================================
/**
 *	�g���[�i�[�t���O�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[�t���O�̃Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_FLAG_SET tr_id
	.short	EV_SEQ_TRAINER_FLAG_SET
	.short	\tr_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[�t���O�̃��Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_FLAG_RESET tr_id
	.short	EV_SEQ_TRAINER_FLAG_RESET
	.short	\tr_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[�t���O�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_FLAG_CHECK tr_id
	.short	EV_SEQ_TRAINER_FLAG_CHECK
	.short	\tr_id
	.endm

	//�t���OON�̎��ɕ���(JUMP)
	.macro	_IF_TR_FLAGON_JUMP tr_id,adrs
	_TRAINER_FLAG_CHECK \tr_id
	_IF_JUMP	FLGON,\adrs
	.endm

	//�t���OOFF�̎��ɕ���(JUMP)
	.macro	_IF_TR_FLAGOFF_JUMP tr_id,adrs
	_TRAINER_FLAG_CHECK \tr_id
	_IF_JUMP	FLGOFF,\adrs
	.endm

	//�t���OON�̎��ɕ���(CALL)
	.macro	_IF_TR_FLAGON_CALL tr_id,adrs
	_TRAINER_FLAG_CHECK \tr_id
	_IF_CALL	FLGON,\adrs
	.endm

	//�t���OOFF�̎��ɕ���(CALL)
	.macro	_IF_TR_FLAGOFF_CALL tr_id,adrs
	_TRAINER_FLAG_CHECK \tr_id
	_IF_CALL	FLGOFF,\adrs
	.endm


//=============================================================================
/**
 *	���[�N����֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	���[�N�ɒl�𑫂�
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_WK wk,num
	.short	EV_SEQ_ADD_WK
	.short	\wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	���[�N����l������
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_WK wk,num
	.short	EV_SEQ_SUB_WK
	.short	\wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	���[�N�ɒl����
 */
//-----------------------------------------------------------------------------
	.macro	_LDVAL	wk,val
	.short	EV_SEQ_LD_WK_VAL
	.short	\wk
	.short	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	���[�N�Ƀ��[�N�̒l����
 */
//-----------------------------------------------------------------------------
	.macro	_LDWK	wk1,wk2
	.short	EV_SEQ_LD_WK_WK
	.short	\wk1
	.short	\wk2
	.endm

//-----------------------------------------------------------------------------
/**
 *	���[�N�ɒl�����[�N�̒l����
 */
//-----------------------------------------------------------------------------
	.macro	_LDWKVAL	wk1,wk2
	.short	EV_SEQ_LD_WK_WKVAL
	.short	\wk1
	.short	\wk2
	.endm


//=============================================================================
/**
 *	��b�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�W�J���b�Z�[�W��\��(1byte)
 *
 *	@param	msg_id	�\�����郁�b�Z�[�WID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_ALLPUT msg_id
	.short	EV_SEQ_MSG_ALLPUT
	.byte	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�W�J���b�Z�[�W��\��(msg_id=work�w��L,arc_id=work�w��L)
 *
 *	@param	msg_id	�\�����郁�b�Z�[�WID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_ALLPUT_ARC	arc_id, msg_id
	.short	EV_SEQ_MSG_ALLPUT_ARC
	.short	\arc_id
	.short	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�W�J���b�Z�[�W��\��(msg_id=work�w��L,arc_id=work�w��L)
 *  @param	arc_id	�\�����郁�b�Z�[�W�A�[�J�C�uID
 *	@param	msg_id	�\�����郁�b�Z�[�WID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_ARC	arc_id, msg_id
	.short	EV_SEQ_MSG_ARC
	.short	\arc_id
	.short	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ȈՉ�b���b�Z�[�W��\��(stype=2byte,sid=2byte)
 *  @param	stype	�ȈՉ�b�̕��̓^�C�v
 *  @param	sid		�ȈՉ�b�̕��̓^�C�v��ID
 *	@param	word0	�P��R�[�h0
 *	@param	word1	�P��R�[�h1
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_ALLPUT_PMS	stype,sid,word0,word1	
	.short	EV_SEQ_MSG_ALLPUT_PMS
	.short	\stype
	.short	\sid
	.short	\word0
	.short	\word1
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ȈՉ�b���b�Z�[�W��\��(stype=2byte,sid=2byte)
 *  @param	stype	�ȈՉ�b�̕��̓^�C�v
 *  @param	sid		�ȈՉ�b�̕��̓^�C�v��ID
 *	@param	word0	�P��R�[�h0
 *	@param	word1	�P��R�[�h1
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_PMS	stype,sid,word0,word1	
	.short	EV_SEQ_MSG_PMS
	.short	\stype
	.short	\sid
	.short	\word0
	.short	\word1
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^���[�ΐ�O���b�Z�[�W��\��(tr_idx)
 *  @param	tr_idx	��l�ڂ���l�ڂ��H
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_BTOWER_APPEAR	tr_id	
	.short	EV_SEQ_MSG_BTOWER_APPEAR
	.byte	\tr_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^���[�pNG�|�P�������W�J(�������Ƃ���z����)
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_NG_POKE_NAME	msg_id,num,sex,flag
	.short	EV_SEQ_MSG_NG_POKE_NAME
	.byte	\msg_id
	.short	\num
	.short	\sex
	.byte	\flag
	.endm


//-----------------------------------------------------------------------------
/**
 *	�W�J���b�Z�[�W��\��(1byte)
 *
 *	@param	msg_id	�\�����郁�b�Z�[�WID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG msg_id
	.short	EV_SEQ_MSG
	.byte	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�W�J���b�Z�[�W��\��(����F�����Ƀ��[�N���w��ł���)
 *
 *	@param	msg_id	�\�����郁�b�Z�[�WID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_SP msg_id
	.short	EV_SEQ_MSG_SP
	.short	\msg_id
	.endm


//-----------------------------------------------------------------------------
/**
 *	�W�J���b�Z�[�W���I�[�g�ŕ\��(����F�����Ƀ��[�N���w��ł���)
 *
 *	@param	msg_id	�\�����郁�b�Z�[�WID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_SP_AUTO msg_id
	.short	EV_SEQ_MSG_SP_AUTO
	.short	\msg_id
	.endm


//-----------------------------------------------------------------------------
/**
 *	�W�J���b�Z�[�W��\��(�X�L�b�v�s��)
 *
 *	@param	msg_id	�\�����郁�b�Z�[�WID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_NOSKIP msg_id
	.short	EV_SEQ_MSG_NOSKIP
	.short	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�W�J���b�Z�[�W��\��(�R���e�X�g�p�A�ʐM�A��ʐM�𔻒肵�ă��b�Z�[�W����̐ݒ��ύX)
 *
 *	@param	msg_id	�\�����郁�b�Z�[�WID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_CON_SIO msg_id
	.short	EV_SEQ_MSG_CON_SIO
	.byte	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 * OBJ���烁�b�Z�[�WID���擾���ĕ\��
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_AUTOGET
	.short	EV_SEQ_MSG_AUTOGET
	.endm


//-----------------------------------------------------------------------------
/**
 *	�L�[�҂�
 */
//-----------------------------------------------------------------------------
	.macro	_AB_KEYWAIT
	.short	EV_SEQ_ABKEYWAIT
	.endm

//-----------------------------------------------------------------------------
/**
 * �L�[�҂��@OR�@���ԑ҂�
 */
//-----------------------------------------------------------------------------
	.macro	_AB_KEY_TIME_WAIT	wait
	.short	EV_SEQ_ABKEY_TIMEWAIT
	.short	\wait
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C�x���g�̍Ō�̃L�[�҂�
 *		�X�^�[�g�{�^��	�X�N���v�g�I�����Ƀ��j���[���J�����N�G�X�g�Z�b�g
 *		�\���L�[		��l���̌�����ύX
 *		���ǉ������
 */
//-----------------------------------------------------------------------------
	.macro	_LAST_KEYWAIT
	.short	EV_SEQ_LASTKEYWAIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C�x���g�̍Ō�̃L�[�҂�(���̌�ɃA�j�����������Ɏg�p)
 *		�\���L�[		���b�Z�[�W�I��
 *		���ǉ������
 */
//-----------------------------------------------------------------------------
	.macro	_NEXT_ANM_LAST_KEYWAIT
	.short	EV_SEQ_NEXT_ANM_LASTKEYWAIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	��b�E�B���h�E�J��
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_OPEN
	.short	EV_SEQ_WIN_OPEN
	.endm

//-----------------------------------------------------------------------------
/**
 *	��b�E�B���h�E����
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_CLOSE
	.short	EV_SEQ_WIN_CLOSE
	.endm

//-----------------------------------------------------------------------------
/**
 *	��b�E�B���h�E����(�N���A�Ȃ�)
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_CLOSE_NO_CLEAR
	.short	EV_SEQ_WIN_CLOSE_NO_CLEAR
	.endm

//-----------------------------------------------------------------------------
/**
 *	�W�J���b�Z�[�W�\���{�L�[�҂�
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_KEYWAIT msg_id
	_TALKMSG \msg_id
	//_AB_KEYWAIT			//06.04.07 ���b�Z�[�W����d�l�ɍ��킹�č폜
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ȉ�OBJ�ɑ΂��Ęb���|��
 */
//-----------------------------------------------------------------------------
	.macro	_EASY_OBJ_MSG msg_id
	_TALK_OBJ_START
	//_TALK_KEYWAIT \msg_id
	_TALKMSG	 \msg_id
	_LAST_KEYWAIT				//���ӁI
	_TALK_CLOSE
	_TALK_OBJ_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ȉ�BG�ɑ΂��Ęb���|��
 */
//-----------------------------------------------------------------------------
	.macro	_EASY_MSG msg_id
	_TALK_START
	//_TALK_KEYWAIT \msg_id
	_TALKMSG	 \msg_id
	_LAST_KEYWAIT				//���ӁI
	_TALK_CLOSE
	_TALK_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ŕ쐬�i�^�E���}�b�v�A�W���A�\�D�j
 */
//-----------------------------------------------------------------------------
	.macro	_BOARD_MAKE msg_id,type,map,ret_wk
	.short	EV_SEQ_BOARD_MAKE
	.byte	\msg_id
	.byte	\type
	.short	\map
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ŕ쐬�i�f���j(ret_wk=SCWK_ANSWER�Œ�I)
 */
//-----------------------------------------------------------------------------
	.macro	_INFOBOARD_MAKE type,map
	.short	EV_SEQ_INFOBOARD_MAKE
	.byte	\type
	.short	\map
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ŕ��N�G�X�g
 */
//-----------------------------------------------------------------------------
	.macro	_BOARD_REQ req
	.short	EV_SEQ_BOARD_REQ
	.byte	\req
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ŕ��N�G�X�g�I���҂�
 */
//-----------------------------------------------------------------------------
	.macro	_BOARD_REQ_WAIT
	.short	EV_SEQ_BOARD_REQ_WAIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ŕ��b�Z�[�W�\��(ret_wk=SCWK_ANSWER�Œ�I)
 */
//-----------------------------------------------------------------------------
	.macro	_BOARD_MSG msg_id,ret_wk
	.short	EV_SEQ_BOARD_MSG
	.byte	\msg_id
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ŔI���҂�(ret_wk=SCWK_ANSWER�Œ�I)
 */
//-----------------------------------------------------------------------------
	.macro	_BOARD_END_WAIT ret_wk
	.short	EV_SEQ_BOARD_END_WAIT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ȈՊŔɑ΂��Ęb���|���i�^�E���}�b�v�A�W���A�\�D�j(SCWK_ANSWER�Œ�I)
 */
//-----------------------------------------------------------------------------
	.macro	_EASY_BOARD_MSG msg_id,type,map
	_BOARD_MAKE		\msg_id,\type,\map,SCWK_ANSWER
	_BOARD_REQ		BOARD_REQ_UP
	_BOARD_REQ_WAIT
	_BOARD_END_WAIT	SCWK_ANSWER
	_CHG_COMMON_SCR	SCRID_COMMON_BOARD
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ȈՊŔɑ΂��Ęb���|���i�f���j(SCWK_ANSWER�Œ�I)
 */
//-----------------------------------------------------------------------------
	.macro	_EASY_INFOBOARD_MSG msg_id,type,map
	_INFOBOARD_MAKE	\type,\map
	_BOARD_REQ		BOARD_REQ_UP
	_BOARD_REQ_WAIT
	_BOARD_MSG		\msg_id,SCWK_ANSWER
	_CHG_COMMON_SCR	SCRID_COMMON_BOARD
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C�x���g�؂�ւ�
 */
//-----------------------------------------------------------------------------
	.macro	_MENU_REQ
	.short	EV_SEQ_MENU_REQ
	.endm

//-----------------------------------------------------------------------------
/**
 *	BG�X�N���[��
 */
//-----------------------------------------------------------------------------
	.macro	_BG_SCROLL	scroll_x,count_x,mv_x,scroll_y,count_y,mv_y
	.short	EV_SEQ_BG_SCROLL
	.byte	\scroll_x
	.byte	\count_x
	.byte	\mv_x
	.byte	\scroll_y
	.byte	\count_y
	.byte	\mv_y
	.endm

//=============================================================================
/**
 *	�u�͂��A�������v�E�B���h�E�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�͂��A�������I��
 */
//-----------------------------------------------------------------------------
	.macro	_YES_NO_WIN ret_wk
	.short	EV_SEQ_YES_NO_WIN
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	�M�l�X�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�M�l�X�E�B���h�E�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_GUINNESS_WIN
	.short	EV_SEQ_GUINNESS_WIN
	.endm


//=============================================================================
/**
 *	BMP���j���[�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	BMP���j���[�@������
 */
//-----------------------------------------------------------------------------
	.macro	_BMPMENU_INIT x,y,cursor,cancel,ret_wk
	.short	EV_SEQ_BMPMENU_INIT
	.byte	\x
	.byte	\y
	.byte	\cursor
	.byte	\cancel
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	BMP���j���[�@������(�ǂݍ���ł���gmm�t�@�C�����g�p����)
 */
//-----------------------------------------------------------------------------
	.macro	_BMPMENU_INIT_EX x,y,cursor,cancel,ret_wk
	.short	EV_SEQ_BMPMENU_INIT_EX
	.byte	\x
	.byte	\y
	.byte	\cursor
	.byte	\cancel
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	BMP���j���[�@���X�g�쐬
 */
//-----------------------------------------------------------------------------
	.macro	_BMPMENU_MAKE_LIST msg_id,param
	.short	EV_SEQ_BMPMENU_MAKE_LIST
	.byte	\msg_id
	.byte	\param
	.endm

//-----------------------------------------------------------------------------
/**
 *	BMP���j���[�@���X�g�쐬(short�o�[�W����)
 */
//-----------------------------------------------------------------------------
	.macro	_BMPMENU_MAKE_LIST16 msg_id,param
	.short	EV_SEQ_BMPMENU_MAKE_LIST16
	.short	\msg_id
	.short	\param
	.endm

//-----------------------------------------------------------------------------
/**
 *	BMP���j���[�@�J�n
 */
//-----------------------------------------------------------------------------
	.macro	_BMPMENU_START
	.short	EV_SEQ_BMPMENU_START
	.endm

//-----------------------------------------------------------------------------
/**
 *	�I���E�B���h�E�@�W�����v
 */
//-----------------------------------------------------------------------------
//	.macro	_SEL_WIN_JUMP act,adrs
//	.short	EV_SEQ_SEL_WIN_JUMP
//	.byte	\act
//	.long	((\adrs-.)-4)
//	.endm


//=============================================================================
/**
 *	BMP���X�g�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	BMP���X�g�@������
 */
//-----------------------------------------------------------------------------
	.macro	_BMPLIST_INIT	x,y,cursor,cancel,ret_wk
	.short	EV_SEQ_BMPLIST_INIT
	.byte	\x
	.byte	\y
	.byte	\cursor
	.byte	\cancel
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	BMP���X�g�@������(�ǂݍ���ł���gmm�t�@�C�����g�p����)
 */
//-----------------------------------------------------------------------------
	.macro	_BMPLIST_INIT_EX	x,y,cursor,cancel,ret_wk
	.short	EV_SEQ_BMPLIST_INIT_EX
	.byte	\x
	.byte	\y
	.byte	\cursor
	.byte	\cancel
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	BMP���X�g�@���X�g�쐬
 */
//-----------------------------------------------------------------------------
	.macro	_BMPLIST_MAKE_LIST	msg_id_wk,talk_msg_id_wk,param_wk
	.short	EV_SEQ_BMPLIST_MAKE_LIST
	.short	\msg_id_wk
	.short	\talk_msg_id_wk
	.short	\param_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	BMP���X�g�@�J�n
 */
//-----------------------------------------------------------------------------
	.macro	_BMPLIST_START
	.short	EV_SEQ_BMPLIST_START
	.endm


//=============================================================================
/**
 *	BMP���j���[�c���֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	BMP���j���[�c���@�J�n
 */
//-----------------------------------------------------------------------------
	.macro	_BMPMENU_HV_START	x_max
	.short	EV_SEQ_BMPMENU_HV_START
	.byte	\x_max
	.endm


//=============================================================================
/**
 *	�T�E���h�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	SE��炷
 */
//-----------------------------------------------------------------------------
	.macro	_SE_PLAY no
	.short	EV_SEQ_SE_PLAY
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	SE���~�߂�
 */
//-----------------------------------------------------------------------------
	.macro	_SE_STOP no
	.short	EV_SEQ_SE_STOP
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	SE�I���҂�
 */
//-----------------------------------------------------------------------------
	.macro	_SE_WAIT	no
	.short	EV_SEQ_SE_WAIT
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	������炷
 */
//-----------------------------------------------------------------------------
	.macro	_VOICE_PLAY no,ptn
	.short	EV_SEQ_VOICE_PLAY
	.short	\no
	.short	\ptn
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����I���҂�
 */
//-----------------------------------------------------------------------------
	.macro	_VOICE_WAIT
	.short	EV_SEQ_VOICE_WAIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ȈՖ������b�Z�[�W�\��
 */
//-----------------------------------------------------------------------------
	.macro	_EASY_VOICE_MSG msg_id,no,ptn
	_TALK_OBJ_START
	_SE_WAIT	SEQ_SE_DP_SELECT
	_VOICE_PLAY \no,\ptn
	_TALKMSG	\msg_id
	_VOICE_WAIT
	_LAST_KEYWAIT
	_TALK_CLOSE
	_TALK_OBJ_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	ME��炷
 */
//-----------------------------------------------------------------------------
	.macro	_ME_PLAY no
	.short	EV_SEQ_ME_PLAY
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	ME�I���҂�
 */
//-----------------------------------------------------------------------------
	.macro	_ME_WAIT
	.short	EV_SEQ_ME_WAIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	���ʃZ�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SND_INITIAL_VOL_SET seq_no,vol
	.short	EV_SEQ_SND_INITIAL_VOL_SET
	.short	\seq_no
	.short	\vol
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGM��炷
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_PLAY no
	.short	EV_SEQ_BGM_PLAY
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGM���I���҂�
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_PLAY_CHECK no,ret_wk
	.short	EV_SEQ_BGM_PLAY_CHECK
	.short	\no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGM���~�߂�
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_STOP no
	.short	EV_SEQ_BGM_STOP
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	���݂̃}�b�v��BGM��炷
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_NOW_MAP_PLAY
	.short	EV_SEQ_BGM_NOW_MAP_PLAY
	.endm

//-----------------------------------------------------------------------------
/**
 *	�}�b�v�������BGM�w�肪�Z�b�g�����
 *	���]��BGM�̐���ȂǂɎg�p
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_SPECIAL_SET no
	.short	EV_SEQ_BGM_SPECIAL_SET
	.short	\no
	.endm

	.macro	_BGM_SPECIAL_CLR
	_BGM_SPECIAL_SET	0
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGM�t�F�[�h�A�E�g
 *
 *	vol		= �{�����[��
 *	frame	= ���t���[�������ăt�F�[�h���邩
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_FADEOUT vol,frame
	.short	EV_SEQ_BGM_FADEOUT
	.short	\vol
	.short	\frame
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGM�t�F�[�h�A�E�g�@���@�w�肵��BGM���Đ�
 *	�g�p���Ȃ������킩��₷�������B�B�B
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_FADEOUT_PLAY frame,no
	_BGM_FADEOUT \frame
	_BGM_PLAY	 \no
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGM�t�F�[�h�C��
 *
 *	frame = ���t���[�������ăt�F�[�h���邩
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_FADEIN frame
	.short	EV_SEQ_BGM_FADEIN
	.short	\frame
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V�[�P���X���ꎞ��~�܂��͍ĊJ(1=��~�A0=�ĊJ)
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_PLAYER_PAUSE player,flag
	.short	EV_SEQ_BGM_PLAYER_PAUSE
	.byte	\player
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *	���oBGM�Đ�(���C�o���E�T�|�[�g�E��Ă�)
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_FIELD_DEMO_BGM_PLAY	no
	.short	EV_SEQ_PLAYER_FIELD_DEMO_BGM_PLAY
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�t�B�[���hBGM���Œ�ɂ���t���O�Z�b�g(�Z�[�u���Ȃ�)
 */
//-----------------------------------------------------------------------------
	.macro	_CTRL_BGM_FLAG_SET
	.short	EV_SEQ_CTRL_BGM_FLAG_SET
	.byte	1
	.endm

//-----------------------------------------------------------------------------
/**
 *	�t�B�[���hBGM���Œ�ɂ���t���O���Z�b�g(�Z�[�u���Ȃ�)
 */
//-----------------------------------------------------------------------------
	.macro	_CTRL_BGM_FLAG_RESET
	.short	EV_SEQ_CTRL_BGM_FLAG_SET
	.byte	0
	.endm

//-----------------------------------------------------------------------------
/**
 *	�y���b�v�f�[�^�����邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_PERAP_DATA_CHECK	ret_wk
	.short	EV_SEQ_PERAP_DATA_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�y���b�v�^���J�n
 */
//-----------------------------------------------------------------------------
	.macro	_PERAP_REC_START	ret_wk
	.short	EV_SEQ_PERAP_REC_START
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�y���b�v�^����~
 */
//-----------------------------------------------------------------------------
	.macro	_PERAP_REC_STOP
	.short	EV_SEQ_PERAP_REC_STOP
	.endm

//-----------------------------------------------------------------------------
/**
 *	�y���b�v�^�������f�[�^���Z�[�u
 */
//-----------------------------------------------------------------------------
	.macro	_PERAP_SAVE
	.short	EV_SEQ_PERAP_SAVE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�T�E���h�f�[�^�ǉ����[�h�F�N���C�}�b�N�X
 */
//-----------------------------------------------------------------------------
	.macro	_SND_CLIMAX_DATA_LOAD
	.short	EV_SEQ_SND_CLIMAX_DATA_LOAD
	.endm


//=============================================================================
/**
 *	�A�j���[�V�����֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�A�j��
 *
 *	���ӁI �����~���Z�b�g���������́A_OBJ_PAUSE_ALL��������x�Ă΂Ȃ��Ƃ����Ȃ��I
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_ANIME	obj_id,adrs
	.short	EV_SEQ_OBJ_ANIME
	.short	\obj_id
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_OBJ_ANIME_POS	obj_id, x, z
	.short	EV_SEQ_OBJ_ANIME_POS
	.short	\obj_id
	.short	\x
	.short	\z
	.endm
//-----------------------------------------------------------------------------
/**
 *	�A�j���[�V�����f�[�^���x��
 */
//-----------------------------------------------------------------------------
	.macro	_ANIME_LABEL label
	.align	4
	\label:
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�j���[�V�����f�[�^(fieldobj_code.h�Q��)
 */
//-----------------------------------------------------------------------------
	.macro	_ANIME_DATA	code,num
	.short	\code
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�j���E�F�C�g
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_ANIME_WAIT
	.short	EV_SEQ_OBJ_ANIME_WAIT
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_TALK_OBJ_PAUSE_ALL
	.short	EV_SEQ_TALK_OBJ_PAUSE_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����~
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_PAUSE_ALL
	.short	EV_SEQ_OBJ_PAUSE_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	����ĊJ
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_PAUSE_CLEAR_ALL
	.short	EV_SEQ_OBJ_PAUSE_CLEAR_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�X�̓����~
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_PAUSE	obj_id
	.short	EV_SEQ_OBJ_PAUSE
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�X�̓���ĊJ
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_PAUSE_CLEAR	obj_id
	.short	EV_SEQ_OBJ_PAUSE_CLEAR
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ�o��
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_ADD	obj_id
	.short	EV_SEQ_OBJ_ADD
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ����
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_DEL	obj_id
	.short	EV_SEQ_OBJ_DEL
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����_�~�[OBJ�ǉ�
 */
//-----------------------------------------------------------------------------
	.macro	_VANISH_DUMMY_OBJ_ADD	x,z
	.short	EV_SEQ_VANISH_DUMMY_OBJ_ADD
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����_�~�[OBJ�폜
 */
//-----------------------------------------------------------------------------
	.macro	_VANISH_DUMMY_OBJ_DEL
	.short	EV_SEQ_VANISH_DUMMY_OBJ_DEL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�b��������OBJ�����@�����֐U�����
 */
//-----------------------------------------------------------------------------
	.macro	_TURN_HERO_SITE
	.short	EV_SEQ_OBJ_TURN
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ�ɑ΂��Ęb���|���J�n(��l���ɑ΂��ĐU������L��)
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_OBJ_START
	_SE_PLAY SEQ_SE_DP_SELECT
	//_SE_PLAY SEQ_SE_DP_SELECT11
	//_SE_PLAY SEQ_SE_DP_TALK2
	_OBJ_PAUSE_ALL
	_TURN_HERO_SITE
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ�ɑ΂��Ęb���|���J�n(��l���ɑ΂��ĐU���������)
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_OBJ_START_TURN_NOT
	_SE_PLAY SEQ_SE_DP_SELECT
	//_SE_PLAY SEQ_SE_DP_SELECT11
	_OBJ_PAUSE_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ�ɑ΂��Ęb���|���I��
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_OBJ_END
	_OBJ_PAUSE_CLEAR_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	BJ�ɑ΂��Ęb���|���J�n
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_START
	_SE_PLAY SEQ_SE_DP_SELECT
	//_SE_PLAY SEQ_SE_DP_SELECT11
	_OBJ_PAUSE_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	POS,SCENE_CHANGE_LABEL�ɑ΂��ĊJ�n
 *	(TALK_START���g�p����ƁA��b�J�n�̉����Ȃ��Ă��܂��̂ŕ�����)
 */
//-----------------------------------------------------------------------------
	.macro	_EVENT_START
	_OBJ_PAUSE_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	BJ�ɑ΂��Ęb���|���I��
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_END
	_OBJ_PAUSE_CLEAR_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	POS,SCENE_CHANGE_LABEL�ɑ΂��ďI��
 */
//-----------------------------------------------------------------------------
	.macro	_EVENT_END
	_OBJ_PAUSE_CLEAR_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	��l���̈ʒu�擾
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_POS_GET	x,z
	.short	EV_SEQ_PLAYER_POS_GET
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ�̈ʒu�擾
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_POS_GET	obj_id,x,z
	.short	EV_SEQ_OBJ_POS_GET
	.short	\obj_id
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	��l���̈ʒu�I�t�Z�b�g�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_POS_OFFSET_SET	x,y,z
	.short	EV_SEQ_PLAYER_POS_OFFSET_SET
	.short	\x
	.short	\y
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 * ��l���̕����擾
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_DIR_GET	dir
	.short	EV_SEQ_PLAYER_DIR_GET
	.short	\dir
	.endm

//-----------------------------------------------------------------------------
/**
 *	�]�[���؂�ւ����̍폜�֎~(TRUE=�֎~�AFALSE=�֎~���Ȃ�)
 */
//-----------------------------------------------------------------------------
	.macro	_NOT_ZONE_DEL_SET	obj_id,flag
	.short	EV_SEQ_NOT_ZONE_DEL_SET
	.short	\obj_id
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *	����R�[�h�ύX
 */
//-----------------------------------------------------------------------------
	.macro	_MOVE_CODE_CHANGE	obj_id,code
	.short	EV_SEQ_MOVE_CODE_CHANGE
	.short	\obj_id
	.short	\code
	.endm

//-----------------------------------------------------------------------------
/**
 *	����R�[�h�擾
 */
//-----------------------------------------------------------------------------
	.macro	_MOVE_CODE_GET	ret_wk,obj_id
	.short	EV_SEQ_MOVE_CODE_GET
	.short	\ret_wk
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�����OBJID�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_PAIR_OBJID_SET
	.short	EV_SEQ_PAIR_OBJID_SET
	.endm


//=============================================================================
/**
 *	�C�x���g�f�[�^�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�C�x���g�f�[�^�@�e�[�u���錾
 */
//-----------------------------------------------------------------------------
	.macro	_EVENT_DATA	adrs
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C�x���g�f�[�^�@�e�[�u���I��
 */
//-----------------------------------------------------------------------------
#define EV_DATA_END_CODE	(0xfd13)	//�K���Ȓl
	.macro	_EVENT_DATA_END
	.short	EV_DATA_END_CODE
	.endm


//=============================================================================
/**
 *	����X�N���v�g�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	����X�N���v�g�L�q�I��
 */
//-----------------------------------------------------------------------------
	.macro	_SP_EVENT_DATA_END
	.byte	SP_SCRID_NONE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V�[���C�x���g�F��ɊĎ����Ă������X�N���v�g
 */
//-----------------------------------------------------------------------------
	.macro	_SCENE_CHANGE_LABEL	adrs
	.byte	SP_SCRID_SCENE_CHANGE
	.long	((\adrs-.)-4)
	.endm

	//�N�������L�q
	.macro	_SCENE_CHANGE_DATA		wk,num,scr_id
	.short	\wk
	.short	\num
	.short	\scr_id
	.endm

	//�L�q�I��(�Z�[�u���[�N��`��SVWK_START�̃I�t�Z�b�g�𑫂��Ă���̂�0���w�肵�Ă悢)
	.macro	_SCENE_CHANGE_END
	.short	0
	.endm

//-----------------------------------------------------------------------------
/**
 *	�t���O����F�}�b�v�J�ڂň�x�̂݌Ă΂�����X�N���v�g
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_CHANGE_LABEL	scr_id
	.byte	SP_SCRID_FLAG_CHANGE
	.short	\scr_id
	.short	0		//4byte�ɍ��킹�邽�߂Ƀ_�~�[
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ����F�}�b�v�J�ڂň�x�̂݌Ă΂�����X�N���v�g
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_CHANGE_LABEL	scr_id
	.byte	SP_SCRID_OBJ_CHANGE
	.short	\scr_id
	.short	0		//4byte�ɍ��킹�邽�߂Ƀ_�~�[
	.endm

//-----------------------------------------------------------------------------
/**
 *	����������F�}�b�v���������ƂɌĂ΂�����X�N���v�g
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_CHANGE_LABEL	scr_id
	.byte	SP_SCRID_INIT_CHANGE
	.short	\scr_id
	.short	0		//4byte�ɍ��킹�邽�߂Ƀ_�~�[
	.endm


//=============================================================================
/**
 *	�����֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	������������
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_GOLD val
	.short	EV_SEQ_ADD_GOLD
	.long	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	���������炷
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_GOLD val
	.short	EV_SEQ_SUB_GOLD
	.long	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	���z�𒲂ׂ�
 */
//-----------------------------------------------------------------------------
	.macro	_COMP_GOLD ret_wk,val
	.short	EV_SEQ_COMP_GOLD
	.short	\ret_wk
	.long	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	�������E�B���h�E�\��
 */
//-----------------------------------------------------------------------------
	.macro	_GOLD_WIN_WRITE		x,z
	.short	EV_SEQ_GOLD_WIN_WRITE
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	�������E�B���h�E�폜
 */
//-----------------------------------------------------------------------------
	.macro	_GOLD_WIN_DEL
	.short	EV_SEQ_GOLD_WIN_DEL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�������\��
 */
//-----------------------------------------------------------------------------
	.macro	_GOLD_WRITE
	.short	EV_SEQ_GOLD_WRITE
	.endm


//=============================================================================
/**
 *	�R�C���֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�R�C���E�B���h�E�\��
 */
//-----------------------------------------------------------------------------
	.macro	_COIN_WIN_WRITE	x,z
	.short	EV_SEQ_COIN_WIN_WRITE
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�C���E�B���h�E�폜
 */
//-----------------------------------------------------------------------------
	.macro	_COIN_WIN_DEL
	.short	EV_SEQ_COIN_WIN_DEL	
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�C���\��
 */
//-----------------------------------------------------------------------------
	.macro	_COIN_WRITE
	.short	EV_SEQ_COIN_WRITE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�C�����擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_COIN_NUM	ret_wk
	.short	EV_SEQ_GET_COIN_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�C��������
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_COIN		val
	.short	EV_SEQ_ADD_COIN
	.short	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�C�����炷
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_COIN		val
	.short	EV_SEQ_SUB_COIN
	.short	\val
	.endm


//=============================================================================
/**
 *	�A�C�e���֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�t�B�[���h�A�C�e���Q�b�g����
 *
 *	ANSWER�Ɍ��ʂ���
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_ITEM_EVENT	no,num
	_LDVAL	SCWK_REG0,\no
	_LDVAL	SCWK_REG1,\num
	_JUMP	ev_fld_item2
	.endm

//-----------------------------------------------------------------------------
/**
 *	�B���A�C�e���Q�b�g����
 *
 *	ANSWER�Ɍ��ʂ���
 */
//-----------------------------------------------------------------------------
#if 0
	.macro	_HIDE_ITEM_EVENT	no,num,flagno
	_LDVAL	SCWK_REG0,\no
	_LDVAL	SCWK_REG1,\num
	_LDVAL	SCWK_REG2,\flagno
	_CHG_COMMON_SCR	SCRID_HIDE_ITEM
	.endm
#endif

//-----------------------------------------------------------------------------
/**
 *	�A�C�e����������
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_ITEM	item_no,num,ret_wk
	.short	EV_SEQ_ADD_ITEM
	.short	\item_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�C�e�������炷
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_ITEM	item_no,num,ret_wk
	.short	EV_SEQ_SUB_ITEM
	.short	\item_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�C�e�����������邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_ITEM_CHK	item_no,num,ret_wk
	.short	EV_SEQ_ADD_ITEM_CHK
	.short	\item_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�b�O�̃A�C�e���`�F�b�N
 *
 *	ANSWER�Ɍ��ʂ���
 */
//-----------------------------------------------------------------------------
	.macro	_ITEM_CHK		item_no,num,ret_wk
	.short	EV_SEQ_ITEM_CHK
	.short	\item_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Z�}�V���̃A�C�e���i���o�[���`�F�b�N
 *
 *	ANSWER�Ɍ��ʂ���
 */
//-----------------------------------------------------------------------------
	.macro	_WAZA_ITEM_CHK		item_no,ret_wk
	.short	EV_SEQ_WAZA_ITEM_CHK
	.short	\item_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�b�g�i���o�[�擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POCKET_NO	item_no,ret_wk
	.short	EV_SEQ_GET_POCKET_NO
	.short	\item_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �w��|�P�b�g�ɉ������邩�ǂ����̃`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CHECK_POCKET	pocket_no,ret_wk
	.short	EV_SEQ_POCKET_CHK
	.short	\pocket_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�p�\�R���ɃA�C�e����������
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_BOX_ITEM
	.short	EV_SEQ_ADD_BOX_ITEM
	.endm

//-----------------------------------------------------------------------------
/**
 *	�p�\�R���̃A�C�e���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_BOX_ITEM
	.short	EV_SEQ_CHK_BOX_ITEM
	.endm


//=============================================================================
/**
 *	�O�b�Y�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�O�b�Y��������(PC)
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_GOODS	goods_no,num,ret_wk
	.short	EV_SEQ_ADD_GOODS
	.short	\goods_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�O�b�Y�����炷(PC)
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_GOODS	goods_no,num,ret_wk
	.short	EV_SEQ_SUB_GOODS
	.short	\goods_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�O�b�Y���������邩�̃`�F�b�N(PC)
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_GOODS_CHK	goods_no,num,ret_wk
	.short	EV_SEQ_ADD_GOODS_CHK
	.short	\goods_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�b�O�̃O�b�Y�`�F�b�N(PC)
 */
//-----------------------------------------------------------------------------
	.macro	_GOODS_CHK goods_no,num,ret_wk
	.short	EV_SEQ_GOODS_CHK
	.short	\goods_no
	.short	\num
	.short	\ret_wk
	.endm

//=============================================================================
/**
 *	㩊֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	㩂�������
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_TRAP	trap_no,num,ret_wk
	.short	EV_SEQ_ADD_TRAP
	.short	\trap_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	㩂����炷
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_TRAP	trap_no,num,ret_wk
	.short	EV_SEQ_SUB_TRAP
	.short	\trap_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	㩂��������邩�̃`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_TRAP_CHK	trap_no,num,ret_wk
	.short	EV_SEQ_ADD_TRAP_CHK
	.short	\trap_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�b�O��㩃`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_TRAP_CHK trap_no,num,ret_wk
	.short	EV_SEQ_TRAP_CHK
	.short	\trap_no
	.short	\num
	.short	\ret_wk
	.endm

//=============================================================================
/**
 *	����֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�����������
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_TREASURE	treasure_no,num,ret_wk
	.short	EV_SEQ_ADD_TREASURE
	.short	\treasure_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	��������炷
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_TREASURE	treasure_no,num,ret_wk
	.short	EV_SEQ_SUB_TREASURE
	.short	\treasure_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	������������邩�̃`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_TREASURE_CHK	treasure_no,num,ret_wk
	.short	EV_SEQ_ADD_TREASURE_CHK
	.short	\treasure_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�b�O�̂���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_TREASURE_CHK treasure_no,num,ret_wk
	.short	EV_SEQ_TREASURE_CHK
	.short	\treasure_no
	.short	\num
	.short	\ret_wk
	.endm

//=============================================================================
/**
 *	�^�}�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�^�}��������
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_TAMA	tama_no,num,ret_wk
	.short	EV_SEQ_ADD_TAMA
	.short	\tama_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^�}�����炷
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_TAMA	tama_no,num,ret_wk
	.short	EV_SEQ_SUB_TAMA
	.short	\tama_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^�}���������邩�̃`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_TAMA_CHK	tama_no,num,ret_wk
	.short	EV_SEQ_ADD_TAMA_CHK
	.short	\tama_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�b�O�̃^�}�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_TAMA_CHK tama_no,num,ret_wk
	.short	EV_SEQ_TAMA_CHK
	.short	\tama_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V�[���̎�ސ����擾
 */
//-----------------------------------------------------------------------------
	.macro	_CB_SEAL_KIND_NUM_GET	ret_wk
	.short	EV_SEQ_CB_SEAL_KIND_NUM_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V�[���̐����擾
 */
//-----------------------------------------------------------------------------
	.macro	_CB_ITEM_NUM_GET	seal_id,ret_wk
	.short	EV_SEQ_CB_ITEM_NUM_GET
	.short	\seal_id
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V�[����ǉ�
 */
//-----------------------------------------------------------------------------
	.macro	_CB_ITEM_NUM_ADD	seal_id,num
	.short	EV_SEQ_CB_ITEM_NUM_ADD
	.short	\seal_id
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���̃A���m�[���̌`����擾
 */
//-----------------------------------------------------------------------------
	.macro	_UNKNOWN_FORM_GET	pos,ret_wk
	.short	EV_SEQ_UNKNOWN_FORM_GET
	.short	\pos
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	�|�P�����֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�|�P�������莝���ɉ�����
 */
//-----------------------------------------------------------------------------
	//.macro	_ADD_POKEMON	monsno,lv,itemno,adrs1,adrs2,name_sw
	.macro	_ADD_POKEMON	monsno,lv,itemno,ret_wk
	.short	EV_SEQ_ADD_POKEMON
	.short	\monsno
	.short	\lv
	.short	\itemno
	.short	\ret_wk
	//.word	\adrs1,\adrs2
	//.byte	\name_sw
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^�}�S���莝���ɉ�����
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_TAMAGO		monsno,msgid
	.short	EV_SEQ_ADD_TAMAGO
	.short	\monsno
	.short	\msgid
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���|�P�����̋Z��u��������
 */
//-----------------------------------------------------------------------------
	.macro	_CHG_POKE_WAZA pos,waza_pos,wazano
	.short	EV_SEQ_CHG_POKE_WAZA
	.byte	\pos
	.byte	\waza_pos
	.short	\wazano
	.endm

//-----------------------------------------------------------------------------
/**
 *	�w�肳�ꂽ�Z���o���Ă��邩���ׂ�(1�́j
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_POKE_WAZA	ret_wk,wazano,tno
	.short	EV_SEQ_CHK_POKE_WAZA
	.short	\ret_wk
	.short	\wazano
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�w�肳�ꂽ�Z���o���Ă���莝���|�P�����𒲂ׂ�(�S�́j
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_POKE_WAZA_GROUP	ret_wk,wazano
	.short	EV_SEQ_CHK_POKE_WAZA_GROUP
	.short	\ret_wk
	.short	\wazano
	.endm

//-----------------------------------------------------------------------------
/**
 * �|�P�������łŋC�₵�����ǂ����̃`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_APPROVE_POISON_DEAD	ret_wk, num
	.short	EV_SEQ_APPROVE_POISON_DEAD
	.short	\ret_wk
	.short	\num
	.endm

//=============================================================================
/**
 *	�|�P�T�[�`���[�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�n���ꂽ�g���[�i�[���Đ�\���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_REVENGE_TRAINER_SEARCH	tr_id,ret_wk1
	.short	EV_SEQ_REVENGE_TRAINER_SEARCH
	.short	\tr_id
	.short	\ret_wk1
	.endm


//=============================================================================
/**
 *	�V��֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�V��R�[�h�̏�����
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_WEATHER
	.short	EV_SEQ_INIT_WEATHER
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V��R�[�h�̃Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SET_WEATHER id
	.short	EV_SEQ_SET_WEATHER
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V��R�[�h�̔��f
 */
//-----------------------------------------------------------------------------
	.macro	_UPDATE_WEATHER
	.short	EV_SEQ_UPDATE_WEATHER
	.endm


//=============================================================================
/**
 *	�c�[���֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	���݂̃}�b�v�ʒu���擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_MAP_POS
	.short	EV_SEQ_GET_MAP_POS
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���̃|�P���������擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_TEMOTI_POKE_NUM
	.short	EV_SEQ_GET_TEMOTI_POKE_NUM
	.endm


//=============================================================================
/**
 *	�v���O�����֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�t�B�[���h�v���Z�X���A
 */
//-----------------------------------------------------------------------------
	.macro	_SET_MAP_PROC
	.short	EV_SEQ_SET_MAP_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�t�B�[���h�v���Z�X�I��
 */
//-----------------------------------------------------------------------------
	.macro	_FINISH_MAP_PROC
	.short	EV_SEQ_FINISH_MAP_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ƃ������R�[�h�o�^�C�x���g
 */
//-----------------------------------------------------------------------------
	.macro	_WIFI_AUTO_REG
	.short	EV_SEQ_WIFI_AUTO_REG
	.endm

//-----------------------------------------------------------------------------
/**
 *	P2P�ΐ�}�b�`���O�{�[�h�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_WIFI_P2P_MATCH_EVENT_CALL
	.short	EV_SEQ_WIFI_P2P_MATCH_EVENT_CALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	P2P�ΐ�}�b�`���O�{�[�h�̖߂�l�擾�A�m�ۂ����������폜
 */
//-----------------------------------------------------------------------------
	.macro	_WIFI_P2P_MATCH_SET_DEL	ret_wk
	.short	EV_SEQ_WIFI_P2P_MATCH_SET_DEL
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	������NET_ID��Ԃ�
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_GET_CURRENT_ID	ret_wk
	.short	EV_SEQ_COMM_GET_CURRENT_ID
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�a������񐔂��擾
 */
//-----------------------------------------------------------------------------
	.macro	_DENDOU_NUM_GET	ret_wk
	.short	EV_SEQ_DENDOU_NUM_GET
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	�|�P�����E�B���h�E�\��
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_WINDOW_PUT	monsno,sex
	.short	EV_SEQ_POKE_WINDOW_PUT
	.short	\monsno
	.short	\sex
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�����E�B���h�E�\��(POKEMON_PARAM)
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_WINDOW_PUT_PP	pos
	.short	EV_SEQ_POKE_WINDOW_PUT_PP
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�����E�B���h�E�폜
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_WINDOW_DEL
	.short	EV_SEQ_POKE_WINDOW_DEL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�����E�B���h�E�A�j��
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_WINDOW_ANM
	.short	EV_SEQ_POKE_WINDOW_ANM
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�����E�B���h�E�A�j���E�F�C�g
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_WINDOW_ANM_WAIT	ret_wk
	.short	EV_SEQ_POKE_WINDOW_ANM_WAIT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���T�[�`���[�C�x���g�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_SEARCHER_EVENT_CALL	ret_wk
	.short	EV_SEQ_BTL_SEARCHER_EVENT_CALL
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���T�[�`���[�F�퓬��ɕ\�������Œ�̓���R�[�h���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_SEARCHER_DIR_MV_SET
	.short	EV_SEQ_BTL_SEARCHER_DIR_MV_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	���b�Z�[�W�o�^���N
 */
//-----------------------------------------------------------------------------
	.macro	_MSG_BOY_EVENT
	.short	EV_SEQ_MSG_BOY_EVENT
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C���[�W�N���b�v�Ăяo��
 *	pos	�Z�[�u�L�����A��܂�
 *	refe	REFERENCE����̎� 1
 */
//-----------------------------------------------------------------------------
	.macro	_IMAGE_CLIP_SET_PROC	pos,ret_wk,refe
	.short	EV_SEQ_IMAGE_CLIP_SET_PROC
	.short	\pos
	.short	\ret_wk
	.short	\refe
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C���[�W�N���b�vViewer�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_IMAGE_CLIP_VIEW_TV_SET_PROC	pos,ret_work
	.short	EV_SEQ_IMAGE_CLIPVIEW_TV_SET_PROC
	.short	\pos
	.short	\ret_work
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C���[�W�N���b�vViewer�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_IMAGE_CLIP_VIEW_CON_SET_PROC	pos,ret_work
	.short	EV_SEQ_IMAGE_CLIPVIEW_CON_SET_PROC
	.short	\pos
	.short	\ret_work
	.endm

//-----------------------------------------------------------------------------
/**
 *	�J�X�^���{�[���Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_CUSTOM_BALL_EVENT_CALL
	.short	EV_SEQ_CUSTOM_BALL_EVENT_CALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^�E���}�b�vBG���[�h�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_TMAP_BG_SET_PROC
	.short	EV_SEQ_TMAP_BG_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�{�b�N�X�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_BOX_SET_PROC	mode
	.short	EV_SEQ_BOX_SET_PROC
	.byte	\mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	���������Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_OEKAKI_BOARD_SET_PROC
	.short	EV_SEQ_OEKAKI_BOARD_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�J�[�h�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_TR_CARD_SET_PROC
	.short	EV_SEQ_TR_CARD_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	��������Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_TRADE_LIST_SET_PROC
	.short	EV_SEQ_TRADE_LIST_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	���R�[�h�R�[�i�[�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_RECORD_CORNER_SET_PROC
	.short	EV_SEQ_RECORD_CORNER_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�a������Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_DENDOU_SET_PROC
	.short	EV_SEQ_DENDOU_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�p�\�R���a������Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_PC_DENDOU_SET_PROC
	.short	EV_SEQ_PC_DENDOU_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	���E������ʌĂяo��
 */
//-----------------------------------------------------------------------------
	.macro	_WORLDTRADE_SET_PROC	no,ret_wk
	.short	EV_SEQ_WORLDTRADE_SET_PROC
	.short	\no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	WIFI�ڑ��������ID�擾
 */
//-----------------------------------------------------------------------------
	.macro	_DPW_INIT_PROC	ret_wk
	.short	EV_SEQ_DPW_INIT_PROC
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ŏ��̃|�P�����I���Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_FIRST_POKE_SELECT_PROC
	.short	EV_SEQ_FIRST_POKE_SELECT_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ŏ��̃|�P�����I���őI�������|�P�����i���o�[���擾���āA�m�ۂ����������폜
 */
//-----------------------------------------------------------------------------
	.macro	_FIRST_POKE_SELECT_SET_AND_DEL
	.short	EV_SEQ_FIRST_POKE_SELECT_SET_AND_DEL
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_BAG_SET_PROC_NORMAL
	.short	EV_SEQ_BAG_SET_PROC
	.byte	0
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_BAG_SET_PROC_KINOMI
	.short	EV_SEQ_BAG_SET_PROC
	.byte	1
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_BAG_GET_RESULT ret_wk
	.short	EV_SEQ_BAG_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�����I����ʌĂяo��
 */
//-----------------------------------------------------------------------------
	.macro	_POKELIST_SET_PROC
	.short	EV_SEQ_POKELIST_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�����I����ʌĂяo��(�Q�[��������)
 */
//-----------------------------------------------------------------------------
	.macro	_NPC_TRADE_POKELIST_SET_PROC
	.short	EV_SEQ_NPC_TRADE_POKELIST_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	���j�I���|�P�����I����ʌĂяo��
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_POKELIST_SET_PROC
	.short	EV_SEQ_UNION_POKELIST_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 * �|�P�����I����ʌ��ʎ��o��
 */
//-----------------------------------------------------------------------------
	.macro	_POKELIST_GET_RESULT	ret_wk
	.short	EV_SEQ_POKELIST_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�|�P�����I����ʌĂяo��
 */
//-----------------------------------------------------------------------------
	.macro	_CON_POKELIST_SET_PROC	pos,rank,type,sio_flag
	.short	EV_SEQ_CON_POKELIST_SET_PROC
	.short	\pos
	.short	\rank
	.short	\type
	.short	\sio_flag
	.endm

//-----------------------------------------------------------------------------
/**
 * �R���e�X�g �|�P�����I����ʌ��ʎ��o��
 */
//-----------------------------------------------------------------------------
	.macro	_CON_POKELIST_GET_RESULT	ret_wk,ret_mode
	.short	EV_SEQ_CON_POKELIST_GET_RESULT
	.short	\ret_wk
	.short	\ret_mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g �|�P�����X�e�[�^�X��ʌĂяo��
 */
//-----------------------------------------------------------------------------
	.macro	_CON_POKESTATUS_SET_PROC	pos
	.short	EV_SEQ_CON_POKESTATUS_SET_PROC
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 * �|�P�����X�e�[�^�X��ʌ��ʎ��o��(�ꉞ_CON_POKESTATUS_SET_PROC�p�ō����)
 */
//-----------------------------------------------------------------------------
	.macro	_POKESTATUS_GET_RESULT	ret_wk
	.short	EV_SEQ_POKESTATUS_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���V��ʌĂяo��
 */
//-----------------------------------------------------------------------------
	.macro	_WIFI_EARTH_SET_PROC
	.short	EV_SEQ_WIFI_EARTH_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����F�g���[�i�[�ړ��Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_EYE_TRAINER_MOVE_SET	pos
	.short	EV_SEQ_EYE_TRAINER_MOVE_SET
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����F�g���[�i�[�ړ��I���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_EYE_TRAINER_MOVE_CHECK	pos,ret_wk
	.short	EV_SEQ_EYE_TRAINER_MOVE_CHECK
	.short	\pos
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����F�g���[�i�[�^�C�v�擾
 */
//-----------------------------------------------------------------------------
	.macro	_EYE_TRAINER_TYPE_GET ret_wk
	.short	EV_SEQ_EYE_TRAINER_TYPE_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����F�g���[�i�[ID�擾
 */
//-----------------------------------------------------------------------------
	.macro	_EYE_TRAINER_ID_GET	pos,ret_wk
	.short	EV_SEQ_EYE_TRAINER_ID_GET
	.short	\pos
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���O���͌Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_NAMEIN ret_wk
	.short	EV_SEQ_NAMEIN
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�������O���͌Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_NAMEIN_POKE	pos,ret_wk
	.short	EV_SEQ_NAMEIN_POKE
	.short	\pos
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	�P�x�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	���C�v�t�F�[�h�X�^�[�g
 *
 *	���ӁI�@�t�F�[�h�ɂ�����LCD�ABG�ʂ̐ݒ�͌Œ�ɂ��Ă���
 */
//-----------------------------------------------------------------------------
	.macro	_WIPE_FADE_START		div,sync,type,color
	.short	EV_SEQ_WIPE_FADE_START
	.short	\div
	.short	\sync
	.short	\type
	.short	\color
	.endm

//-----------------------------------------------------------------------------
/**
 *	���C�v�t�F�[�h�I���`�F�b�N
 *
 *	���ӁI�@�`�F�b�N����LCD�̐ݒ�͌Œ�ɂ��Ă���
 */
//-----------------------------------------------------------------------------
	.macro	_WIPE_FADE_END_CHECK
	.short	EV_SEQ_WIPE_FADE_END_CHECK
	.endm

//-----------------------------------------------------------------------------
/**
 *	�z���C�g�A�E�g
 *
 *	���ӁI�@�t�F�[�h�ɂ�����LCD�ABG�ʂ̐ݒ�͌Œ�ɂ��Ă���
 */
//-----------------------------------------------------------------------------
	.macro	_WHITE_OUT	div,sync
	_WIPE_FADE_START	\div,\sync,WIPE_TYPE_FADEOUT,WIPE_FADE_WHITE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�z���C�g�C��
 *
 *	���ӁI�@�t�F�[�h�ɂ�����LCD�ABG�ʂ̐ݒ�͌Œ�ɂ��Ă���
 */
//-----------------------------------------------------------------------------
	.macro	_WHITE_IN	div,sync
	_WIPE_FADE_START	\div,\sync,WIPE_TYPE_FADEIN,WIPE_FADE_WHITE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�u���b�N�A�E�g
 *
 *	���ӁI�@�t�F�[�h�ɂ�����LCD�ABG�ʂ̐ݒ�͌Œ�ɂ��Ă���
 */
//-----------------------------------------------------------------------------
	.macro	_BLACK_OUT	div,sync
	_WIPE_FADE_START	\div,\sync,WIPE_TYPE_FADEOUT,WIPE_FADE_BLACK
	.endm

//-----------------------------------------------------------------------------
/**
 *	�u���b�N�C��
 *
 *	���ӁI�@�t�F�[�h�ɂ�����LCD�ABG�ʂ̐ݒ�͌Œ�ɂ��Ă���
 */
//-----------------------------------------------------------------------------
	.macro	_BLACK_IN	div,sync
	_WIPE_FADE_START	\div,\sync,WIPE_TYPE_FADEIN,WIPE_FADE_BLACK
	.endm


//=============================================================================
/**
 *	�}�b�v�J�ڊ֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�}�b�v�J��
 */
//-----------------------------------------------------------------------------
	.macro	_MAP_CHANGE		zone_id,door_id,x,z,dir
	_BLACK_OUT	SCR_WIPE_DIV,SCR_WIPE_SYNC
	_WIPE_FADE_END_CHECK
	.short	EV_SEQ_MAP_CHANGE
	.short	\zone_id
	.short	\door_id
	.short	\x
	.short	\z
	.short	\dir
	_BLACK_IN	SCR_WIPE_DIV,SCR_WIPE_SYNC
	_WIPE_FADE_END_CHECK
	.endm

//-----------------------------------------------------------------------------
/**
 *	�}�b�v�J��(�t�F�[�h�Ȃ�)
 */
//-----------------------------------------------------------------------------
	.macro	_MAP_CHANGE_NONE_FADE		zone_id,door_id,x,z,dir
	.short	EV_SEQ_MAP_CHANGE
	.short	\zone_id
	.short	\door_id
	.short	\x
	.short	\z
	.short	\dir
	.endm

//-----------------------------------------------------------------------------
/**
 *	�}�b�v�J��(�R���V�A��)�C��
 */
//-----------------------------------------------------------------------------
	.macro	_COLOSSEUM_MAP_CHANGE_IN		zone_id,door_id,x,z,dir
	.short	EV_SEQ_COLOSSEUM_MAP_CHANGE_IN
	.short	\zone_id
	.short	\door_id
	.short	\x
	.short	\z
	.short	\dir
	.endm

//-----------------------------------------------------------------------------
/**
 *	�}�b�v�J��(�R���V�A��)�A�E�g
 */
//-----------------------------------------------------------------------------
	.macro	_COLOSSEUM_MAP_CHANGE_OUT
	.short	EV_SEQ_COLOSSEUM_MAP_CHANGE_OUT
	.endm

//-----------------------------------------------------------------------------
/**
 *	�O�̃]�[��ID�擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_BEFORE_ZONE_ID	ret_wk
	.short	EV_SEQ_GET_BEFORE_ZONEID
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���݂̃]�[��ID�擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_NOW_ZONE_ID	ret_wk
	.short	EV_SEQ_GET_NOW_ZONEID
	.short	\ret_wk
	.endm

//=============================================================================
/**
 *	��`�Z�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�ǂ̂ڂ�
 */
//-----------------------------------------------------------------------------
	.macro	_KABENOBORI	wk
	.short	EV_SEQ_KABENOBORI
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ȃ݂̂�
 */
//-----------------------------------------------------------------------------
	.macro	_NAMINORI	wk
	.short	EV_SEQ_NAMINORI
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���]�Ԃɏ���Ă��邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_BICYCLE_CHECK	ret_wk
	.short	EV_SEQ_BICYCLE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	1=���]�ԁA0=���s�`�ԂɕύX
 */
//-----------------------------------------------------------------------------
	.macro	_BICYCLE_REQ	flag
	.short	EV_SEQ_BICYCLE_REQ
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *	���]�Ԍ`�ԂɕύX(BGM�͕ύX���Ȃ��A�}�b�v�L���t���O�͗���)
 *	���̃R�}���h�̌�Ɂu_BGM_PLAY	SEQ_BICYCLE�v���Ă�
 *	�T�C�N�����O���[�h��p
 */
//-----------------------------------------------------------------------------
	.macro	_BICYCLE_REQ_NON_BGM
	.short	EV_SEQ_BICYCLE_REQ_NON_BGM
	.endm

//-----------------------------------------------------------------------------
/**
 *	�T�C�N�����O���[�h�Z�b�g(1=�T�C�N�����O���[�h�A0=�Ȃ�)
 */
//-----------------------------------------------------------------------------
	.macro	_CYCLING_ROAD_SET	flag
	.short	EV_SEQ_CYCLING_ROAD_SET
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *	���@�̌`�Ԃ��擾
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_FORM_GET	ret_wk
	.short	EV_SEQ_PLAYER_FORM_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���@�փ��N�G�X�g
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_REQ_BIT_ON	bit
	.short	EV_SEQ_PLAYER_REQ_BIT_ON
	.short	\bit
	.endm

//-----------------------------------------------------------------------------
/**
 *	���@���N�G�X�g���s
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_REQ_START
	.short	EV_SEQ_PLAYER_REQ_START
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����̂ڂ�
 */
//-----------------------------------------------------------------------------
	.macro	_TAKINOBORI	wk
	.short	EV_SEQ_TAKINOBORI
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	������Ƃ�
 */
//-----------------------------------------------------------------------------
	.macro	_SORAWOTOBU	zone_id,x,z
	.short	EV_SEQ_SORAWOTOBU
	.short	\zone_id
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 * ��`�킴�F�t���b�V��
 */
//-----------------------------------------------------------------------------
	.macro	_HIDEN_FLASH
	.short	EV_SEQ_HIDEN_FLASH
	.endm

//-----------------------------------------------------------------------------
/**
 * ��`�킴�F����΂炢
 */
//-----------------------------------------------------------------------------
	.macro	_HIDEN_KIRIBARAI
	.short	EV_SEQ_HIDEN_KIRIBARAI
	.endm

//-----------------------------------------------------------------------------
/**
 *	�J�b�g�C��
 */
//-----------------------------------------------------------------------------
	.macro	_CUTIN	wk
	.short	EV_SEQ_CUTIN
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�@���ւ�
 */
//-----------------------------------------------------------------------------
	.macro	_CON_HERO_CHANGE
	.short	EV_SEQ_CON_HERO_CHANGE
	.endm


//=============================================================================
/**
 *	������֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	��l����
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_NAME	idx
	.short	EV_SEQ_PLAYER_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	���C�o����
 */
//-----------------------------------------------------------------------------
	.macro	_RIVAL_NAME	idx
	.short	EV_SEQ_RIVAL_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	�T�|�[�g��
 */
//-----------------------------------------------------------------------------
	.macro	_SUPPORT_NAME	idx
	.short	EV_SEQ_SUPPORT_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���|�P������
 */
//-----------------------------------------------------------------------------
	.macro	_POKEMON_NAME	idx,pos
	.short	EV_SEQ_POKEMON_NAME
	.byte	\idx
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�C�e����
 */
//-----------------------------------------------------------------------------
	.macro	_ITEM_NAME	idx,itemno
	.short	EV_SEQ_ITEM_NAME
	.byte	\idx
	.short	\itemno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�b�g��
 */
//-----------------------------------------------------------------------------
	.macro	_POCKET_NAME	idx,pocket
	.short	EV_SEQ_POCKET_NAME
	.byte	\idx
	.short	\pocket
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Z��
 */
//-----------------------------------------------------------------------------
	.macro	_ITEM_WAZA_NAME	idx,itemno
	.short	EV_SEQ_ITEM_WAZA_NAME
	.byte	\idx
	.short	\itemno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Z��
 */
//-----------------------------------------------------------------------------
	.macro	_WAZA_NAME	idx,waza
	.short	EV_SEQ_WAZA_NAME
	.byte	\idx
	.short	\waza
	.endm

//-----------------------------------------------------------------------------
/**
 *	���l��
 */
//-----------------------------------------------------------------------------
	.macro	_NUMBER_NAME	idx,number
	.short	EV_SEQ_NUMBER_NAME
	.byte	\idx
	.short	\number
	.endm

//-----------------------------------------------------------------------------
/**
 *	���l��	�f�B�X�v���C���[�h�w���
 */
//-----------------------------------------------------------------------------
	.macro	_NUMBER_NAME_EX	idx,number,dtype,keta
	.short	EV_SEQ_NUMBER_NAME_EX
	.byte	\idx
	.short	\number
	.byte	\dtype
	.byte	\keta
	.endm

//-----------------------------------------------------------------------------
/**
 *	�a�������`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_BIRTH_DAY_CHECK	ret_wk
	.short	EV_SEQ_BIRTH_DAY_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A���m�[���`��̌��������擾
 */
//-----------------------------------------------------------------------------
	.macro	_ANOON_SEE_NUM	ret_wk
	.short	EV_SEQ_ANOON_SEE_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�j�b�N�l�[��
 */
//-----------------------------------------------------------------------------
	.macro	_NICK_NAME	idx,pos
	.short	EV_SEQ_NICK_NAME
	.byte	\idx
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�b�`�\�t�g��
 */
//-----------------------------------------------------------------------------
	.macro	_POKETCH_NAME	idx,app_id
	.short	EV_SEQ_POKETCH_NAME
	.byte	\idx
	.short	\app_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[��ʖ�
 */
//-----------------------------------------------------------------------------
	.macro	_TR_TYPE_NAME	idx,type
	.short	EV_SEQ_TR_TYPE_NAME
	.byte	\idx
	.short	\type
	.endm

//-----------------------------------------------------------------------------
/**
 *	��l���̃g���[�i�[��ʖ�
 */
//-----------------------------------------------------------------------------
	.macro	_MY_TR_TYPE_NAME	idx
	.short	EV_SEQ_MY_TR_TYPE_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����X�^�[�i���o�[����|�P������
 */
//-----------------------------------------------------------------------------
	.macro	_POKEMON_NAME_EXTRA	idx,mons,sex,flag
	.short	EV_SEQ_POKEMON_NAME_EXTRA
	.byte	\idx
	.short	\mons
	.short	\sex
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ŏ��̃|�P������
 */
//-----------------------------------------------------------------------------
	.macro	_FIRST_POKEMON_NAME	idx
	.short	EV_SEQ_FIRST_POKEMON_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	���C�o���̃|�P������
 */
//-----------------------------------------------------------------------------
	.macro	_RIVAL_POKEMON_NAME	idx
	.short	EV_SEQ_RIVAL_POKEMON_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	�T�|�[�g�̃|�P������
 */
//-----------------------------------------------------------------------------
	.macro	_SUPPORT_POKEMON_NAME	idx
	.short	EV_SEQ_SUPPORT_POKEMON_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ŏ��̃|�P�����i���o�[�擾
 */
//-----------------------------------------------------------------------------
	.macro	_FIRST_POKE_NO_GET	ret_wk
	.short	EV_SEQ_FIRST_POKE_NO_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���݂̖̂��O
 *	@param	idx			�Z�b�g����WORDSET�̈ʒu
 *	@param	itemno		���݂̂̎w��i�A�C�e���i���o�[�Łj
 *	@param	count		���݂̂̐�
 */
//-----------------------------------------------------------------------------
	.macro	_NUTS_NAME	idx, itemno, count
	.short	EV_SEQ_NUTS_NAME
	.byte	\idx
	.short	\itemno
	.short	\count
	.endm

//-----------------------------------------------------------------------------
/**
 *	���i�̖��O
 *	@param	idx			�Z�b�g����WORDSET�̈ʒu
 *	@param	seikaku		���i
 */
//-----------------------------------------------------------------------------
	.macro	_SEIKAKU_NAME	idx,seikaku
	.short	EV_SEQ_SEIKAKU_NAME
	.byte	\idx
	.short	\seikaku
	.endm

//-----------------------------------------------------------------------------
/**
 *	�O�b�Y�̖��O
 *	@param	idx			�Z�b�g����WORDSET�̈ʒu
 *	@param	itemno		�O�b�Y�̎w��
 */
//-----------------------------------------------------------------------------
	.macro	_GOODS_NAME	idx, goodsno
	.short	EV_SEQ_GOODS_NAME
	.byte	\idx
	.short	\goodsno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���b�v�̖��O
 *	@param	idx			�Z�b�g����WORDSET�̈ʒu
 *	@param	itemno		�O�b�Y�̎w��
 */
//-----------------------------------------------------------------------------
	.macro	_TRAP_NAME	idx, trapno
	.short	EV_SEQ_TRAP_NAME
	.byte	\idx
	.short	\trapno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^�}�̖��O
 *	@param	idx			�Z�b�g����WORDSET�̈ʒu
 *	@param	itemno		�O�b�Y�̎w��
 */
//-----------------------------------------------------------------------------
	.macro	_TAMA_NAME	idx, tamano
	.short	EV_SEQ_TAMA_NAME
	.byte	\idx
	.short	\tamano
	.endm

//-----------------------------------------------------------------------------
/**
 *	�]�[���̖��O
 *	@param	idx			�Z�b�g����WORDSET�̈ʒu
 *	@param	zone_id		�]�[��ID
 */
//-----------------------------------------------------------------------------
	.macro	_ZONE_NAME	idx, zone_id
	.short	EV_SEQ_ZONE_NAME
	.byte	\idx
	.short	\zone_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	��ʔ������̎擾
 *	@param	zone		�]�[��ID�i�[�o�b�t�@
 *	@param	poke		�����X�^�[�i���o�[�i�[�o�b�t�@
 */
//-----------------------------------------------------------------------------
	.macro	_GENERATE_INFO_GET	zone, poke
	.short	EV_SEQ_GENERATE_INFO_GET
	.short	\zone
	.short	\poke
	.endm


//=============================================================================
/**
 *	�퓬�֘A(����)
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[ID�擾
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_ID_GET	wk
	.short	EV_SEQ_TRAINER_ID_GET
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[�퓬�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_BTL_SET	tr_id_0,tr_id_1
	.short	EV_SEQ_TRAINER_BTL_SET
	.short	\tr_id_0
	.short	\tr_id_1
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[�퓬�i�}���`�o�g���j�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_MULTI_BTL_SET	partner_id, tr_id_0, tr_id_1
	.short	EV_SEQ_TRAINER_MULTI_BTL_SET
	.short	\partner_id
	.short	\tr_id_0
	.short	\tr_id_1
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[��b�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_MSG_SET	tr_id,kind_id
	.short	EV_SEQ_TRAINER_MSG_SET
	.short	\tr_id
	.short	\kind_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[��b�̎�ގ擾
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_TALK_TYPE_GET	wk1,wk2,wk3
	.short	EV_SEQ_TRAINER_TALK_TYPE_GET
	.short	\wk1
	.short	\wk2
	.short	\wk3
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Đ�g���[�i�[��b�̎�ގ擾
 */
//-----------------------------------------------------------------------------
	.macro	_REVENGE_TRAINER_TALK_TYPE_GET	wk1,wk2,wk3
	.short	EV_SEQ_REVENGE_TRAINER_TALK_TYPE_GET
	.short	\wk1
	.short	\wk2
	.short	\wk3
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[�^�C�v�擾
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_TYPE_GET	ret_wk
	.short	EV_SEQ_TRAINER_TYPE_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[BGM�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_BGM_SET	tr_id
	.short	EV_SEQ_TRAINER_BGM_SET
	.short	\tr_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[�s�k
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_LOSE
	.short	EV_SEQ_LOSE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g���[�i�[�s�k�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_LOSE_CHECK ret_wk
	.short	EV_SEQ_LOSE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�s�k����
 */
//-----------------------------------------------------------------------------
	.macro	_NORMAL_LOSE
	.short	EV_SEQ_LOSE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�s�k�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_LOSE_CHECK	ret_wk
	.short	EV_SEQ_LOSE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�B���|�P�����Đ�s�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_SEACRET_POKE_RETRY_CHECK ret_wk
	.short	EV_SEQ_SEACRET_POKE_RETRY_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�z�z�|�P�����Đ�s�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_HAIFU_POKE_RETRY_CHECK ret_wk
	.short	EV_SEQ_HAIFU_POKE_RETRY_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���`�F�b�N 2vs2���\���擾
 */
//-----------------------------------------------------------------------------
	.macro	_2VS2_BATTLE_CHECK ret_wk
	.short	EV_SEQ_2VS2_BATTLE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�f�o�b�N�퓬�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_BTL_SET
	.short	EV_SEQ_DEBUG_BTL_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	�f�o�b�N�g���[�i�[�t���O�Z�b�g(��ō폜���܂��I)
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_TRAINER_FLAG_SET
	.short	EV_SEQ_DEBUG_TRAINER_FLAG_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	�f�o�b�N�g���[�i�[�t���OON�W�����v(��ō폜���܂��I)
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_TRAINER_FLAG_ON_JUMP	adrs
	.short	EV_SEQ_DEBUG_TRAINER_FLAG_ON_JUMP
	.long	((\adrs-.)-4)
	.endm
	//.macro	_DEBUG_TRAINER_FLAG_ON_JUMP
	//.short	EV_SEQ_DEBUG_TRAINER_FLAG_ON_JUMP
	//.endm

	//10����ROM�p�I�g���[�i�[�Ƃ̉�b���t���O�Z�b�g���퓬
	.macro	_DEBUG_TR_TALK_BTL msg_id,adrs
	//.macro	_DEBUG_TR_TALK_BTL msg_id
	_DEBUG_TRAINER_FLAG_ON_JUMP	\adrs
	//_DEBUG_TRAINER_FLAG_ON_JUMP
	_TALK_OBJ_START
	_TALK_KEYWAIT \msg_id
	_TALK_CLOSE
	_DEBUG_TRAINER_FLAG_SET
	_DEBUG_BTL_SET
	_TALK_OBJ_END
	.endm


//=============================================================================
/**
 *	�ʐM�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�e�@��I������E�B���h�E���J��
 */
//-----------------------------------------------------------------------------
	.macro	_SEL_PARENT_WIN	mode,type,type2,ret_wk
	.short	EV_SEQ_CONNECT_SEL_PARENT_WIN
	.short	\mode
	.short	\type
	.short	\type2
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�q�@��I������E�B���h�E���J��
 */
//-----------------------------------------------------------------------------
	.macro	_SEL_CHILD_WIN	mode,type,type2,ret_wk
	.short	EV_SEQ_CONNECT_SEL_CHILD_WIN
	.short	\mode
	.short	\type
	.short	\type2
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�f�o�b�N�e�@��I������E�B���h�E���J��
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_PARENT_WIN ret_wk
	.short	EV_SEQ_CONNECT_DEBUG_PARENT_WIN
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�f�o�b�N�q�@��I������E�B���h�E���J��
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_CHILD_WIN ret_wk
	.short	EV_SEQ_CONNECT_DEBUG_CHILD_WIN
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�f�o�b�N�p�@�ʐM�퓬�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_SIO_ENCOUNT
	.short	EV_SEQ_DEBUG_SIO_ENCOUNT
	.endm

//-----------------------------------------------------------------------------
/**
 *	�f�o�b�N�p�@�ʐM�R���e�X�g�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_SIO_CONTEST
	.short	EV_SEQ_DEBUG_SIO_CONTEST
	.endm


//=============================================================================
/**
 *	�R���e�X�g�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	���M
 */
//-----------------------------------------------------------------------------
	.macro	_CONSIO_TIMING_SEND	timing_no
	.short	EV_SEQ_CONSIO_TIMING_SEND
	.short	\timing_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����҂�
 */
//-----------------------------------------------------------------------------
	.macro	_CONSIO_TIMING_CHECK	timing_no
	.short	EV_SEQ_CONSIO_TIMING_CHECK
	.short	\timing_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V�X�e�����[�N�쐬
 */
//-----------------------------------------------------------------------------
	.macro	_CON_SYSTEM_CREATE	rank,type,mode,pos
	.short	EV_SEQ_CON_SYSTEM_CREATE
	.short	\rank
	.short	\type
	.short	\mode
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V�X�e�����[�N�폜
 */
//-----------------------------------------------------------------------------
	.macro	_CON_SYSTEM_EXIT	wk
	.short	EV_SEQ_CON_SYSTEM_EXIT
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�����擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_JUDGE_NAME_GET	judge_no,idex
	.short	EV_SEQ_CON_JUDGE_NAME_GET
	.short	\judge_no
	.short	\idex
	.endm

//-----------------------------------------------------------------------------
/**
 *	�u���[�_�[���擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_BREEDER_NAME_GET	entry_no,idex
	.short	EV_SEQ_CON_BREEDER_NAME_GET
	.short	\entry_no
	.short	\idex
	.endm

//-----------------------------------------------------------------------------
/**
 *	�j�b�N�l�[���擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_NICK_NAME_GET	entry_no,idex
	.short	EV_SEQ_CON_NICK_NAME_GET
	.short	\entry_no
	.short	\idex
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�F�ꌅ���l���^�O�ɃZ�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_CON_NUM_TAG_SET	num,idex
	.short	EV_SEQ_CON_NUM_TAG_SET
	.short	\num
	.short	\idex
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ʐM�p�Ƀ��[�N�̏����ݒ�ƍŏ��̒ʐM���s���^�X�N�𐶐�
 */
//-----------------------------------------------------------------------------
	.macro	_CON_SIO_PARAM_INIT_SET
	.short	EV_SEQ_CON_SIO_PARAM_INIT_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_CONTEST_PROC
	.short	EV_SEQ_CONTEST_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����N���擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_RANK_NAME_GET	idx
	.short	EV_SEQ_CON_RANK_NAME_GET
	.short	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^�C�v���擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_TYPE_NAME_GET	idx
	.short	EV_SEQ_CON_TYPE_NAME_GET
	.short	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	�D���Җ��擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_VICTORY_BREEDER_NAME_GET	idx
	.short	EV_SEQ_CON_VICTORY_BREEDER_NAME_GET
	.short	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	�D�����i�i���o�[�擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_VICTORY_ITEM_NO_GET	ret_wk
	.short	EV_SEQ_CON_VICTORY_ITEM_NO_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�D�������u���[�_�[�̃|�P�����j�b�N�l�[�����擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_VICTORY_NICK_NAME_GET	buf_id
	.short	EV_SEQ_CON_VICTORY_NICK_NAME_GET
	.short	\buf_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	���Q�����Ă����R���e�X�g�Ŏ��������ʂ����������擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_RANKING_CHECK	ret_wk
	.short	EV_SEQ_CON_RANKING_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�D�������u���[�_�[�̃G���g���[�ԍ����擾����
 */
//-----------------------------------------------------------------------------
	.macro	_CON_VICTORY_ENTRY_NO_GET	ret_wk
	.short	EV_SEQ_CON_VICTORY_ENTRY_NO_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����̃G���g���[�ԍ����擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_MY_ENTRY_NO_GET	ret_wk
	.short	EV_SEQ_CON_MY_ENTRY_NO_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ�R�[�h���擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_OBJ_CODE_GET	entry_no,ret_wk
	.short	EV_SEQ_CON_OBJ_CODE_GET
	.short	\entry_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�l�C���擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_POPULARITY_GET	entry_no,ret_wk
	.short	EV_SEQ_CON_POPULARITY_GET
	.short	\entry_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�F��t�i���o�[���擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_DESK_MODE_GET	ret_wk
	.short	EV_SEQ_CON_DESK_MODE_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�F�Q�����Ă���R���e�X�g�ŗD���������ɖႦ�郊�{�������Ɏ����Ă��邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CON_HAVE_RIBBON_CHECK	ret_wk
	.short	EV_SEQ_CON_HAVE_RIBBON_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Q�����Ă���R���e�X�g�ŗD���������ɖႦ�郊�{���̖��O���擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_RIBBON_NAME_GET	buf_id
	.short	EV_SEQ_CON_RIBBON_NAME_GET
	.short	\buf_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�ŗD���������ɖႦ��A�N�Z�T���ԍ����擾
 */
//-----------------------------------------------------------------------------
	.macro	_CON_ACCE_NO_GET	ret_wk
	.short	EV_SEQ_CON_ACCE_NO_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�F�R���e�X�g�V�X�e�����[�N���烉���N�⃂�[�h�Ȃǂ��擾����
 */
//-----------------------------------------------------------------------------
	.macro	_CON_ENTRY_PARAM_GET	ret_rank,ret_type,ret_mode,ret_temoti_pos
	.short	EV_SEQ_CON_ENTRY_PARAM_GET
	.short	\ret_rank
	.short	\ret_type
	.short	\ret_mode
	.short	\ret_temoti_pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�F�J�����̃t���b�V���G�t�F�N�g�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_CON_CAMERA_FLASH_SET	entry_no
	.short	EV_SEQ_CON_CAMERA_FLASH_SET
	.short	\entry_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�F�J�����̃t���b�V���G�t�F�N�g�I���҂�
 */
//-----------------------------------------------------------------------------
	.macro	_CON_CAMERA_FLASH_CHECK
	.short	EV_SEQ_CON_CAMERA_FLASH_CHECK
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�F�t�B�[���h��H�u�����N��~
 */
//-----------------------------------------------------------------------------
	.macro	_CON_HBLANK_STOP
	.short	EV_SEQ_CON_HBLANK_STOP
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�F�t�B�[���h��H�u�����N�ĊJ
 */
//-----------------------------------------------------------------------------
	.macro	_CON_HBLANK_START
	.short	EV_SEQ_CON_HBLANK_START
	.endm

//-----------------------------------------------------------------------------
/**
 *  �G���f�B���O�X�L�b�v�����m�F
 *		CPU���D���A���͒ʐM�ΐ�̂ǂ��炩�̏����𖞂������`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CON_ENDING_SKIP_CHECK	ret_wk
	.short	EV_SEQ_CON_ENDING_SKIP_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�ʐM�ΐ퐬�ѕ\��
 */
//-----------------------------------------------------------------------------
	.macro	_CON_RECORD_DISP
	.short	EV_SEQ_CON_RECORD_DISP
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�F���b�Z�[�W����t���O�ݒ�
 */
//-----------------------------------------------------------------------------
	.macro	_CON_MSGPRINT_FLAG_SET
	.short	EV_SEQ_CON_MSGPRINT_FLAG_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R���e�X�g�F���b�Z�[�W����t���O�ݒ�
 */
//-----------------------------------------------------------------------------
	.macro	_CON_MSGPRINT_FLAG_RESET
	.short	EV_SEQ_CON_MSGPRINT_FLAG_RESET
	.endm


//=============================================================================
/**
 *	����ڑ��֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	����ڑ����Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SP_LOCATION_SET	zone,door,x,z,dir
	.short	EV_SEQ_SP_LOCATION_SET
	.short	\zone
	.short	\door
	.short	\x
	.short	\z
	.short	\dir
	.endm


//=============================================================================
/**
 *	�G���x�[�^�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	BMP���j���[�@�G���x�[�^�t���A
 */
//-----------------------------------------------------------------------------
	.macro	_ELEVATOR_FLOOR_GET wk
	.short	EV_SEQ_ELEVATOR_FLOOR_GET
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	BMP���j���[�@�G���x�[�^�t���A
 */
//-----------------------------------------------------------------------------
	.macro	_ELEVATOR_FLOOR_WRITE x,y,wk
	.short	EV_SEQ_ELEVATOR_FLOOR_WRITE
	.byte	\x
	.byte	\y
	.short	\wk
	.endm


//=============================================================================
/**
 *	�}�ӕ]���֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�V���I�E�}�Ӂ@�����������擾
 */
//-----------------------------------------------------------------------------
	.macro	_SHINOU_ZUKAN_SEE_NUM	ret_wk
	.short	EV_SEQ_SHINOU_ZUKAN_SEE_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V���I�E�}�Ӂ@�߂܂��������擾
 */
//-----------------------------------------------------------------------------
	.macro	_SHINOU_ZUKAN_GET_NUM	ret_wk
	.short	EV_SEQ_SHINOU_ZUKAN_GET_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�S���}�Ӂ@�����������擾
 */
//-----------------------------------------------------------------------------
	.macro	_ZENKOKU_ZUKAN_SEE_NUM	ret_wk
	.short	EV_SEQ_ZENKOKU_ZUKAN_SEE_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�S���}�Ӂ@�߂܂��������擾
 */
//-----------------------------------------------------------------------------
	.macro	_ZENKOKU_ZUKAN_GET_NUM	ret_wk
	.short	EV_SEQ_ZENKOKU_ZUKAN_GET_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�S���}�ӂ��`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_ZENKOKU_ZUKAN
	.short	EV_SEQ_CHK_ZENKOKU_ZUKAN
	.endm

//-----------------------------------------------------------------------------
/**
 *	�]�����b�Z�[�WID�擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_HYOUKA_MSGID	mode,ret_wk
	.short	EV_SEQ_GET_HYOUKA_MSGID
	.byte	\mode
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	�쐶�퓬�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�|�P�����i���o�[�ƃ��x�����w�肵�Ė쐶�퓬
 */
//-----------------------------------------------------------------------------
	.macro	_WILD_BTL_SET	monsno,level
	.short	EV_SEQ_WILD_BTL_SET
	.short	\monsno
	.short	\level
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�����i���o�[�ƃ��x�����w�肵�ăC�x���g�쐶�퓬
 */
//-----------------------------------------------------------------------------
	.macro	_SP_WILD_BTL_SET	monsno,level
	.short	EV_SEQ_SP_WILD_BTL_SET
	.short	\monsno
	.short	\level
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ŏ��̃C�x���g�퓬
 */
//-----------------------------------------------------------------------------
	.macro	_FIRST_BTL_SET	monsno,level
	.short	EV_SEQ_FIRST_BTL_SET
	.short	\monsno
	.short	\level
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ŏ��̃C�x���g�퓬
 */
//-----------------------------------------------------------------------------
	.macro	_CAPTURE_BTL_SET
	.short	EV_SEQ_CAPTURE_BTL_SET
	.endm


//=============================================================================
/**
 *	�n�j�[�c���[
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�n�j�[�c���[
 */
//-----------------------------------------------------------------------------
	.macro	_HONEY_TREE
	.short	EV_SEQ_HONEY_TREE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n�j�[�c���[�X�e�[�g�擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_HONEY_TREE_STATE ret_wk
	.short	EV_SEQ_GET_HONEY_TREE_STATE
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n�j�[�c���[�퓬
 */
//-----------------------------------------------------------------------------
	.macro	_HONEY_TREE_BTL_SET
	.short	EV_SEQ_SET_HONEY_TREE_BTL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n�j�[�c���[�퓬�I����
 */
//-----------------------------------------------------------------------------
	.macro	_HONEY_TREE_AFTER_SET
	.short	EV_SEQ_SET_AFTER_HONEY_TREE_BTL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�T�C���Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_TSIGN_SET_PROC
	.short	EV_SEQ_TSIGN_SET_PROC
	.endm


//=============================================================================
/**
 *	���|�[�g
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	���|�[�g�f�[�^�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_REPORT_SAVE_CHECK ret_wk
	.short	EV_SEQ_REPORT_SAVE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���|�[�g��������
 */
//-----------------------------------------------------------------------------
	.macro	_REPORT_SAVE	ret_wk
	.short	EV_SEQ_REPORT_SAVE
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_REPORT_WIN_OPEN
	.short	EV_SEQ_REPORT_WIN_OPEN
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_REPORT_WIN_CLOSE
	.short	EV_SEQ_REPORT_WIN_CLOSE
	.endm

//-----------------------------------------------------------------------------
/**
 *		�N���b�v�@�e���r�ǃf�[�^�L���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CLIP_TVSAVEDATA_CHECK pos,ret_wk
	.short	EV_SEQ_CLIP_TVSAVEDATA_CHECK
	.short	\pos
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *		�N���b�v�@�R���e�X�g�f�[�^�L���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CLIP_CONSAVEDATA_CHECK pos,ret_wk
	.short	EV_SEQ_CLIP_CONSAVEDATA_CHECK
	.short	\pos
	.short	\ret_wk
	.endm
	

//-----------------------------------------------------------------------------
/**
 *		�N���b�v�@�e���r�ǃ^�C�g������
 */
//-----------------------------------------------------------------------------
	.macro	_CLIP_TV_TITLE_SAVE	pos
	.short	EV_SEQ_CLIP_TV_TITLE_SAVE
	.short	\pos
	.endm

//=============================================================================
/**
 *	�|�P�b�`
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�|�P�b�g�Q�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKETCH
	.short	EV_SEQ_GET_POKETCH
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�b�g����t���O�ς݃t���O�擾
 *
 *	ANSWER�Ɍ��ʑ��
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKETCH_FLAG ret_wk
	.short	EV_SEQ_GET_POKETCH_FLAG
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�b�`�\�t�g�ǉ�
 */
//-----------------------------------------------------------------------------
	.macro	_POKETCH_ADD	app_id
	.short	EV_SEQ_POKETCH_ADD
	.short	\app_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�b�`�\�t�g�ǉ��ς݃`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_POKETCH_CHECK	app_id,ret_wk
	.short	EV_SEQ_POKETCH_CHECK
	.short	\app_id
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	�ʐM
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	����
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_SYNCHRONIZE	no
	.short	EV_SEQ_COMM_TIMING_SYNC_START
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 * �@���Z�b�g	
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_RESET
	.short	EV_SEQ_COMM_TEMP_DATA_RESET
	.endm


//=============================================================================
/**
 *	���j�I�����[��
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 * ���j�I�����[���@�ʐM�̐e�@���ŃJ�[�h������O�̉�b�ԍ����擾
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_PARENT_CARD_TALK_NO	ret_wk
	.short	EV_SEQ_UNION_PARENT_CARD_TALK_NO
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ���j�I�����[���@����̐l�̘b�����b�Z�[�WID���擾
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_GET_INFO_TALK_NO	ret_wk
	.short	EV_SEQ_UNION_GET_INFO_TALK_NO
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ���j�I�����[���@�r�[�R����������
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_BEACON_CHANGE	flag
	.short	EV_SEQ_UNION_BEACON_CHANGE
	.short	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 * ���j�I�����[���@�b���������Ȃ���Ԃɂ���
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_CONNECT_TALK_DENIED
	.short	EV_SEQ_UNION_CONNECT_TALK_DENIED
	.endm

//-----------------------------------------------------------------------------
/**
 * ���j�I�����[���@�b�����������Ԃɂ���
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_CONNECT_TALK_OK
	.short	EV_SEQ_UNION_CONNECT_TALK_OK
	.endm

//-----------------------------------------------------------------------------
/**
 * ���j�I�����[�����Ŏg�p�����b�p�Ƀg���[�i�[�����Z�b�g����
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_TRAINER_NAME_REGIST	type
	.short	EV_SEQ_UNION_TRAINER_NAME_REGIST
	.short	\type
	.endm

//-----------------------------------------------------------------------------
/**
 *	�t�B�[���h�p�̃R�}���h�̌n�ɏ�����
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_RETURN_SETUP
	.short	EV_SEQ_UNION_RETURN_SETUP
	.endm

//-----------------------------------------------------------------------------
/**
 *	�r�[�R�����W���ĊJ����
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_CONNECT_CUT_RESTART
	.short	EV_SEQ_UNION_CONNECT_CUT_RESTART
	.endm

//-----------------------------------------------------------------------------
/**
 *	�b�|���ŒʐM�ڑ��ł��Ȃ����ɏo����b�̃C���f�b�N�X���擾
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_GET_TALK_NUMBER	type,ret_wk
	.short	EV_SEQ_UNION_GET_TALK_NUMBER
	.short	\type
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�b������OBJ��ID���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_ID_SET	ret_wk
	.short	EV_SEQ_UNION_ID_SET
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	�b�������Őڑ����Ă݂����ʂ�Ԃ�
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_RESULT_GET ret_wk
	.short	EV_SEQ_UNION_RESULT_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ���j�I�����[����OBJ���B��
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_OBJ_ALL_VANISH
	.short	EV_SEQ_UNION_OBJ_ALL_VANISH
	.endm

//-----------------------------------------------------------------------------
/**
 * �I�������l�����j�I�����[�N�ɓn��
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_SCRIPT_RESULT_SET	type,num
	.short	EV_SEQ_UNION_SCRIPT_RESULT_SET
	.short	\type
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 * �e�@�̃X�^�[�g��҂�
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_PARENT_START_COMMAND_SET	ret_wk
	.short	EV_SEQ_UNION_PARENT_START_COMMAND_SET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �q�@�̑I����҂�
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_CHILD_SELECT_COMMAND_SET	ret_wk
	.short	EV_SEQ_UNION_CHILD_SELECT_COMMAND_SET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���j�I���b�������ڑ��J�n
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_CONNECT_START type, ret_wk
	.short	EV_SEQ_UNION_CONNECT_START
	.short	\type
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ���j�I�����[���ƕ��ʂ̃}�b�v�̊Ԃ̃}�b�v�ړ�
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_MAP_CHANGE
	.short	EV_SEQ_UNION_MAP_CHANGE
	.endm

//-----------------------------------------------------------------------------
/**
 * 4�̑I�����̃g���[�i�[�̖��O��wordset�Ɋi�[����
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_VIEW_TR_SEL_SET
	.short	EV_SEQ_UNION_VIEW_TR_SEL_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * �I������1-4�̐������g���[�i�[�̌����ڔԍ��ɕϊ����� �� �g���[�i�[������ID���擾
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_VIEW_TR_TYPE_MSG_GET	sel,ret_wk
	.short	EV_SEQ_UNION_VIEW_TR_TYPE_MSG_GET
	.short	\sel
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �I������1-4�̐������g���[�i�[�̌����ڔԍ��ɕϊ�����
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_VIEW_TR_TYPE_NO_GET	sel,ret_wk
	.short	EV_SEQ_UNION_VIEW_TR_TYPE_NO_GET
	.short	\sel
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �������g���[�i�[�Ƃ��Č����鎞�̔ԍ����Z�b�g(���j�I�����[���p)
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_VIEW_MY_STATUS_SET	type
	.short	EV_SEQ_UNION_VIEW_MY_STATUS_SET
	.short	\type
	.endm


//=============================================================================
/**
 *	�V�X�e���t���O�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�}�ӓ���ς݂��擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_ZUKAN_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_ZUKAN_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�}�ӃZ�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_ZUKAN_SET
	.short	EV_SEQ_SYS_FLAG_ZUKAN_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�V���[�Y����ς݂��擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_SHOES_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_SHOES_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�V���[�Y�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_SHOES_SET
	.short	EV_SEQ_SYS_FLAG_SHOES_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�o�b�W����ς݂��擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_BADGE_GET	no,ret_wk
	.short	EV_SEQ_SYS_FLAG_BADGE_GET
	.short	\no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�o�b�W�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_BADGE_SET	no
	.short	EV_SEQ_SYS_FLAG_BADGE_SET
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�o�b�W���萔�擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_BADGE_COUNT	ret_wk
	.short	EV_SEQ_SYS_FLAG_BADGE_COUNT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�o�b�O����ς݂��擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_BAG_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_BAG_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�o�b�O�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_BAG_SET
	.short	EV_SEQ_SYS_FLAG_BAG_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�A������t���O�擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_PAIR_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_PAIR_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�A������t���O�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_PAIR_SET
	.short	EV_SEQ_SYS_FLAG_PAIR_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�A������t���O���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_PAIR_RESET
	.short	EV_SEQ_SYS_FLAG_PAIR_RESET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	������������t���O�擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_ONE_STEP_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_ONE_STEP_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	������������t���O�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_ONE_STEP_SET
	.short	EV_SEQ_SYS_FLAG_ONE_STEP_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	������������t���O���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_ONE_STEP_RESET
	.short	EV_SEQ_SYS_FLAG_ONE_STEP_RESET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�Q�[���N���A�t���O�擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_GAME_CLEAR_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_GAME_CLEAR_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�Q�[���N���A�t���O�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_GAME_CLEAR_SET
	.short	EV_SEQ_SYS_FLAG_GAME_CLEAR_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�����肫�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KAIRIKI_SET
	.short	EV_SEQ_SYS_FLAG_KAIRIKI
	.byte	FLAG_MODE_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�����肫���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KAIRIKI_RESET
	.short	EV_SEQ_SYS_FLAG_KAIRIKI
	.byte	FLAG_MODE_RESET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�����肫�擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KAIRIKI_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_KAIRIKI
	.byte	FLAG_MODE_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�t���b�V���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_FLASH_SET
	.short	EV_SEQ_SYS_FLAG_FLASH
	.byte	FLAG_MODE_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�t���b�V�����Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_FLASH_RESET
	.short	EV_SEQ_SYS_FLAG_FLASH
	.byte	FLAG_MODE_RESET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	�t���b�V���擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_FLASH_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_FLASH
	.byte	FLAG_MODE_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	����΂炢�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KIRIBARAI_SET
	.short	EV_SEQ_SYS_FLAG_KIRIBARAI
	.byte	FLAG_MODE_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	����΂炢���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KIRIBARAI_RESET
	.short	EV_SEQ_SYS_FLAG_KIRIBARAI
	.byte	FLAG_MODE_RESET
	.endm

//-----------------------------------------------------------------------------
/**
 * �V�X�e���t���O	����΂炢�擾
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KIRIBARAI_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_KIRIBARAI
	.byte	FLAG_MODE_GET
	.short	\ret_wk
	.endm

//=============================================================================
/**
 *	�t�����h���V���b�v
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�ϓ��t�����h���V���b�v�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_SHOP_CALL	id
	.short	EV_SEQ_SHOP_CALL
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Œ�t�����h���V���b�v�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_FIX_SHOP_CALL	id
	.short	EV_SEQ_FIX_SHOP_CALL
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Œ�O�b�Y�V���b�v�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_FIX_GOODS_CALL	id
	.short	EV_SEQ_FIX_GOODS_CALL
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Œ�V�[���V���b�v�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_FIX_SEAL_CALL	id
	.short	EV_SEQ_FIX_SEAL_CALL
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 * �A�N�Z�T���[�V���b�v�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_ACCE_SHOP_CALL
	.short	EV_SEQ_ACCE_SHOP
	.endm

//-----------------------------------------------------------------------------
/**
 * ���|�[�g���@�`�Ԓǉ�
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_REPORT_DRAW_SET
	.short	EV_SEQ_PLAYER_REPORT_DRAW_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * ���|�[�g���@�`�ԍ폜
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_REPORT_DRAW_DEL
	.short	EV_SEQ_PLAYER_REPORT_DRAW_DEL
	.endm


//=============================================================================
/**
 *	�Q�[���I�[�o�[
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�Q�[���I�[�o�[�Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_GAME_OVER_CALL
	.short	EV_SEQ_GAME_OVER_CALL
	.endm


//=============================================================================
/**
 *	���[�v�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	���[�vID�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SET_WARP_ID	id
	.short	EV_SEQ_SET_WARP_ID
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	��l���̐��ʎ擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_MY_SEX ret_wk
	.short	EV_SEQ_GET_MY_SEX
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�Z����
 */
//-----------------------------------------------------------------------------
	.macro	_PC_KAIFUKU
	.short	EV_SEQ_PC_KAIFUKU
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n����NPC�������_���ɔz�u����
 */
//-----------------------------------------------------------------------------
	.macro	_UG_MAN_SHOP_NPC_RAND_PLACE
	.short	EV_SEQ_UG_MAN_SHOP_NPC_RAND_PLACE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ʐM�_�C���N�g�R�[�i�[�̏I���������J�n����
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_DIRECT_END
	.short	EV_SEQ_COMM_DIRECT_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	�I�������葱���@�^�C�~���O������
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_DIRECT_END_TIMING
	.short	EV_SEQ_COMM_DIRECT_END_TIMING
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ʐM�o�g�����畜�A�������ɌĂ�(������x�������̒ʐM���J�n)
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_DIRECT_ENTER_BTL_ROOM
	.short	EV_SEQ_COMM_DIRECT_ENTER_BTL_ROOM
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ʐM������Ńv���C���[�̕�����ύX(�n���p)
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_PLAYER_SET_DIR	dir
	.short	EV_SEQ_COMM_PLAYER_SET_DIR
	.short	\dir
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	3D�A�j���֘A�@�h�A�A�j���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SET_UP_DOOR_ANIME	bx,bz,lx,lz,id
	.short	EV_SEQ_SET_UP_DOOR_ANIME
	.short \bx
	.short \bz
	.short \lx
	.short \lz
	.byte \id
	.endm

//-----------------------------------------------------------------------------
/**
 *	3D�A�j���֘A�@�A�j���E�G�C�g
 */
//-----------------------------------------------------------------------------
	.macro	_WAIT_3D_ANIME	id
	.short	EV_SEQ_WAIT_3D_ANIME
	.byte \id
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	3D�A�j���֘A�@�A�j�����
 */
//-----------------------------------------------------------------------------
	.macro	_FREE_3D_ANIME	id
	.short	EV_SEQ_FREE_3D_ANIME
	.byte \id
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	3D�A�j���֘A�@�h�A�I�[�v���A�j��
 */
//-----------------------------------------------------------------------------
	.macro	_SEQ_OPEN_DOOR	id
	.short	EV_SEQ_OPEN_DOOR
	.byte \id
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	3D�A�j���֘A�@�h�A�N���[�Y�A�j��
 */
//-----------------------------------------------------------------------------
	.macro	_SEQ_CLOSE_DOOR	id
	.short	EV_SEQ_CLOSE_DOOR
	.byte \id
	.endm

//=============================================================================
//
//		�ȈՉ�b�Ăяo��
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 * �ȈՉ�b�Ăяo���i�P���j
 */
//-----------------------------------------------------------------------------
	.macro	_PMS_INPUT_SINGLE		ret_wk, ans_wk
	.short	EV_SEQ_PMS_INPUT_SINGLE
	.short	0	//�_�~�[
	.short	\ret_wk
	.short	\ans_wk
	.endm
//-----------------------------------------------------------------------------
/**
 * �ȈՉ�b�Ăяo���i�P���j
 */
//-----------------------------------------------------------------------------
	.macro	_PMS_INPUT_DOUBLE		ret_wk, ans_wk1, ans_wk2
	.short	EV_SEQ_PMS_INPUT_DOUBLE
	.short	0	//�_�~�[
	.short	\ret_wk
	.short	\ans_wk1
	.short	\ans_wk2
	.endm

//-----------------------------------------------------------------------------
/**
 * �ȈՉ�b���b�Z�[�W���o�b�t�@�փZ�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_PMS_BUF		buf_no,wk
	.short	EV_SEQ_PMS_BUF
	.short	\buf_no
	.short	\wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	���̂݁F��Ԏ擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SEED_STATUS	ret_wk
	.short	EV_SEQ_SEED_GET_STATUS
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ���̂݁F��ގ擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SEED_TYPE		ret_wk
	.short	EV_SEQ_SEED_GET_TYPE
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ���̂݁F�엿�̎�ގ擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SEED_COMPOST		ret_wk
	.short	EV_SEQ_SEED_GET_COMPOST
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_GET_SEED_GROUND			ret_wk
	.short	EV_SEQ_SEED_GET_GROUND
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ���̂݁F���������̐����擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SEED_COUNT			ret_wk
	.short	EV_SEQ_SEED_GET_NUTSCOUNT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_SET_SEED_COMPOST		item
	.short	EV_SEQ_SEED_SET_COMPOST
	.short	\item
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_SET_SEED_NUTS		item
	.short	EV_SEQ_SEED_SET_NUTS
	.short	\item
	.endm


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_SET_SEED_WATER		cmd
	.short	EV_SEQ_SEED_SET_WATER
	.short	\cmd
	.endm
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_TAKE_SEED
	.short	EV_SEQ_SEED_TAKE_NUTS
	.endm


//-----------------------------------------------------------------------------
/**
 *	SXY�f�[�^�̍��W����ύX
 */
//-----------------------------------------------------------------------------
	.macro	_SXY_POS_CHANGE	id,gx,gz
	.short	EV_SEQ_SXY_POS_CHANGE
	.short	\id
	.short	\gx
	.short	\gz
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ�f�[�^�̍��W����ύX
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_POS_CHANGE	id,gx,gy,gz,dir
	.short	EV_SEQ_OBJ_POS_CHANGE
	.short	\id
	.short	\gx
	.short	\gy
	.short	\gz
	.short	\dir
	.endm

//-----------------------------------------------------------------------------
/**
 *	SXY�f�[�^�̓���R�[�h����ύX
 */
//-----------------------------------------------------------------------------
	.macro	_SXY_MV_CHANGE	id,mv
	.short	EV_SEQ_SXY_MV_CHANGE
	.short	\id
	.short	\mv
	.endm

//-----------------------------------------------------------------------------
/**
 *	SXY�f�[�^�̕�������ύX
 */
//-----------------------------------------------------------------------------
	.macro	_SXY_DIR_CHANGE	id,dir
	.short	EV_SEQ_SXY_DIR_CHANGE
	.short	\id
	.short	\dir
	.endm

//-----------------------------------------------------------------------------
/**
 *	SXY �ڑ��f�[�^�̍��W����ύX
 */
//-----------------------------------------------------------------------------
	.macro	_SXY_EXIT_POS_CHANGE	id,x,z
	.short	EV_SEQ_SXY_EXIT_POS_CHANGE
	.short	\id
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	SXY BG�f�[�^�̍��W����ύX
 */
//-----------------------------------------------------------------------------
	.macro	_SXY_BG_POS_CHANGE	id,x,z
	.short	EV_SEQ_SXY_BG_POS_CHANGE
	.short	\id
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ�f�[�^�̕�������ύX
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_DIR_CHANGE	id,dir
	.short	EV_SEQ_OBJ_DIR_CHANGE
	.short	\id
	.short	\dir
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C�x���g���ʂ������郏�[�N�ɒl���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_RETURN_SCRIPT_WK_SET	num
	.short	EV_SEQ_RETURN_SCRIPT_WK_SET
	.short	\num
	.endm


//-----------------------------------------------------------------------------
/**
 *	FieldMsgSet(MsgExpandBuffer)
 */
//-----------------------------------------------------------------------------
	.macro	_MSGEXPANDBUF
	.short	EV_SEQ_MSGEXPANDBUF
	.endm

//-----------------------------------------------------------------------------
/**
 *	��ĉ��ɂ���|�P�����̖��O���Z�b�g����
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SODATE_NAME
	.short	EV_SEQ_GET_SODATE_NAME
	.endm

//-----------------------------------------------------------------------------
/**
 *	��ĉ��̏�ԃ`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SODATEYA_ZIISAN	ret_wk
	.short	EV_SEQ_GET_SODATEYA_ZIISAN
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���W��������
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_WATER_GYM
	.short	EV_SEQ_INIT_WATER_GYM
	.endm

//-----------------------------------------------------------------------------
/**
 *	���W���M�~�b�N�{�^��
 */
//-----------------------------------------------------------------------------
	.macro	_PUSH_WATER_GYM_BUTTON
	.short	EV_SEQ_PUSH_WATER_GYM_BUTTON
	.endm

//-----------------------------------------------------------------------------
/**
 *	�S�[�X�g�W��������
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_GHOST_GYM
	.short	EV_SEQ_INIT_GHOST_GYM
	.endm

//-----------------------------------------------------------------------------
/**
 *	�S�[�X�g�W���M�~�b�N���t�g
 */
//-----------------------------------------------------------------------------
	.macro	_MOVE_GHOST_GYM_LIFT
	.short	EV_SEQ_MOVE_GHOST_GYM_LIFT
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�W��������
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_STEEL_GYM
	.short	EV_SEQ_INIT_STEEL_GYM
	.endm

//-----------------------------------------------------------------------------
/**
 *	�i���W��������
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_COMBAT_GYM
	.short	EV_SEQ_INIT_COMBAT_GYM
	.endm

//-----------------------------------------------------------------------------
/**
 *	�d�C�W��������
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_ELEC_GYM	room
	.short	EV_SEQ_INIT_ELEC_GYM
	.byte	\room
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	�d�C�W���M�~�b�N�M�A
 */
//-----------------------------------------------------------------------------
	.macro	_ROTATE_ELEC_GYM_GEAR	rot
	.short	EV_SEQ_ROT_ELEC_GYM_GEAR
	.byte	\rot
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	�|�P�������擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKE_COUNT	ret_wk
	.short	EV_SEQ_GET_POKE_COUNT			//�|�P�������擾
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^�}�S���������莝���̃|�P������
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKE_COUNT2	ret_wk
	.short	EV_SEQ_GET_POKE_COUNT2			//�|�P�������擾
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^�}�S�ƕm�����������莝���̃|�P������(�퓬�\�ȃ|�P�������j
 *	no = ��������莝���ԍ�(6:�Ȃ��A0�`5)
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKE_COUNT3	ret_wk,no
	.short	EV_SEQ_GET_POKE_COUNT3			//�|�P�������擾
	.short	\ret_wk
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���E�p�\�R�����܂߂Đ킦��|�P���������̂��邩�B
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKE_COUNT4	ret_wk
	.short	EV_SEQ_GET_POKE_COUNT4			//�|�P�������擾
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���^�}�S�̐����擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_TAMAGO_COUNT	ret_wk
	.short	EV_SEQ_GET_TAMAGO_COUNT
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	�n�����X�֘A
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	�n���̂��X�̃��j���[���J��
 */
//-----------------------------------------------------------------------------
	.macro	_UG_SHOP_MENU_INIT	type,ret_wk
	.short	EV_SEQ_UG_SHOP_MENU_INIT
	.short	\type
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���̉�b�J�n
 */
//-----------------------------------------------------------------------------
	.macro	_UG_SHOP_TALK_START	msg
	.short	EV_SEQ_UG_SHOP_TALK_START
	.short	\msg
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���̉�b�I��
 */
//-----------------------------------------------------------------------------
	.macro	_UG_SHOP_TALK_END
	.short	EV_SEQ_UG_SHOP_TALK_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���̃A�C�e�����Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_UG_SHOP_ITEM_NAME	idx,type
	.short	EV_SEQ_UG_SHOP_ITEM_NAME
	.byte	\idx
	.short	\type
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���̃g���b�v���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_UG_SHOP_TRAP_NAME	idx,type
	.short	EV_SEQ_UG_SHOP_TRAP_NAME
	.byte	\idx
	.short	\type
	.endm


//-----------------------------------------------------------------------------
/**
 *	
 */
//-----------------------------------------------------------------------------
	.macro	_DEL_SODATEYA_EGG
	.short	EV_SEQ_DEL_SODATEYA_EGG
	.endm

//-----------------------------------------------------------------------------
/**
 *	 �������ꂽ�^�}�S���󂯎��
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SODATEYA_EGG
	.short	EV_SEQ_GET_SODATEYA_EGG
	.endm

//-----------------------------------------------------------------------------
/**
 *	
 */
//-----------------------------------------------------------------------------
	.macro	_MSG_SODATEYA_AISHOU
	.short	EV_SEQ_MSG_SODATEYA_AISHOU
	.endm

//-----------------------------------------------------------------------------
/**
 *	
 */
//-----------------------------------------------------------------------------
	.macro	_MSG_AZUKE_SET no,wk,ret_wk
	.short	EV_SEQ_MSG_AZUKE_SET
	.short	\no
	.short	\wk
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	
 */
//-----------------------------------------------------------------------------
	.macro	_SET_SODATEYA_POKE wk
	.short	EV_SEQ_SET_SODATEYA_POKE
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	
 */
//-----------------------------------------------------------------------------
	.macro	_SODATEYA_POKELIST ret_wk
	.short	EV_SEQ_SODATEYA_POKELIST
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	
 */
//-----------------------------------------------------------------------------
	.macro	_HIKITORI_LIST ret_wk
	.short	EV_SEQ_HIKITORI_LIST
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	��ĂĂ���|�P�����̈�������x�������o�b�t�@�փZ�b�g�A�܂����̒l��Ԃ�
 */
//-----------------------------------------------------------------------------
	.macro	_SODATE_POKE_LEVEL_STR ret_wk,no
	.short	EV_SEQ_SODATE_POKE_LEVEL_STR
	.short	\ret_wk
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	
 */
//-----------------------------------------------------------------------------
	.macro	_HIKITORI_RYOUKIN ret_wk,wk
	.short	EV_SEQ_HIKITORI_RYOUKIN
	.short	\ret_wk
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	������菈��
 *	ret_wk �������|�P����
 *	no �ǂ����������邩
 */
//-----------------------------------------------------------------------------
	.macro	_HIKITORI_POKE ret_wk,no
	.short	EV_SEQ_HIKITORI_POKE
	.short	\ret_wk
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�^�}�S���܂�f��
 */
//-----------------------------------------------------------------------------
	.macro	_TAMAGO_DEMO
	.short	EV_SEQ_TAMAGO_DEMO
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���̈ʒu�i���o�[����A�|�P�����ԍ��֕ϊ�
 *	IN:wk_in	�莝���ԍ���n�����[�N
 *	OUT:wk_out	�|�P�����ԍ����󂯎�郏�[�N
 *	    OUT��"0"�̂Ƃ��^�}�S
 */
//-----------------------------------------------------------------------------
	.macro	_TEMOTI_MONSNO	wk_in,wk_out
	.short	EV_SEQ_TEMOTI_MONSNO
	.short	\wk_in
	.short	\wk_out
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���|�P�����̂���l�l�`�F�b�N
 *	IN:wk_in	�莝���ԍ���n�����[�N
 *	OUT:wk_out	���L�ҏ��(0:�����̃|�P�����A1:���l�̃|�P����)
 */
//-----------------------------------------------------------------------------
	.macro	_MONS_OWN_CHK	wk_in,wk_out
	.short	EV_SEQ_MONS_OWN_CHK
	.short	\wk_in
	.short	\wk_out
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P���X�Ɋ������Ă��邩�̃`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_TEMOTI_POKERUS	wk
	.short	EV_SEQ_CHK_TEMOTI_POKERUS
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���|�P�����̐��ʎ擾
 */
//-----------------------------------------------------------------------------
	.macro	_TEMOTI_POKE_SEX_GET	pos,ret_wk
	.short	EV_SEQ_TEMOTI_POKE_SEX_GET
	.short	\pos
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_MY_GOLD wk
	.short	EV_SEQ_SUB_MY_GOLD
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	
 */
//-----------------------------------------------------------------------------
	.macro	_COMP_MY_GOLD ret_wk,wk
	.short	EV_SEQ_COMP_MY_GOLD
	.short	\ret_wk
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�L����������Ԃ�
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_VISIBLE obj_id
	.short	EV_SEQ_OBJ_VISIBLE
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�L������s����Ԃ�
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_INVISIBLE obj_id
	.short	EV_SEQ_OBJ_INVISIBLE
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	���[���{�b�N�X
 */
//-----------------------------------------------------------------------------
	.macro	_MAILBOX
	.short	EV_SEQ_MAILBOX
	.endm

//-----------------------------------------------------------------------------
/**
 *	���[���{�b�N�X���̃��[�������擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_MAILBOX_DATANUM	ret_wk
	.short	EV_SEQ_GET_MAILBOX_DATANUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �@�M�l�X�z�[�������L���O��ʌĂяo��	
 */
//-----------------------------------------------------------------------------
	.macro	_RANKING_VIEW	mode
	.short	EV_SEQ_RANKING_VIEW
	.short	\mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	���ԑю擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_TIME_ZONE ret_wk
	.short	EV_SEQ_GET_TIME_ZONE
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����_�����擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_RND ret_wk,num
	.short	EV_SEQ_GET_RND
	.short	\ret_wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����_�����擾
 *  GET_RAND�̃^�l�𗬗p�����܂܌Ăт����Ƃ� or Vsync�ɕω����������ԗp
 */
//-----------------------------------------------------------------------------
	.macro	_GET_RND_NEXT ret_wk,num
	.short	EV_SEQ_GET_RND_NEXT
	.short	\ret_wk
	.short	\num
	.endm


//-----------------------------------------------------------------------------
/**
 *	�Ȃ��x�擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_NATSUKI ret_wk,tno
	.short	EV_SEQ_GET_NATSUKI
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ȃ��x�𑝂₷
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_NATSUKI wk,tno
	.short	EV_SEQ_ADD_NATSUKI
	.short	\wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ȃ��x�����炷
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_NATSUKI wk,tno
	.short	EV_SEQ_SUB_NATSUKI
	.short	\wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�Ђ��Ƃ薼�O(+���ʁALV)�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_HIKITORI_LIST_NAME_SET buf_no,buf2_no,buf3_no,list_no
	.short	EV_SEQ_HIKITORI_NAME_SET
	.short	\buf_no
	.short	\buf2_no
	.short	\buf3_no
	.short	\list_no
	.endm

//-----------------------------------------------------------------------------
/**
 *�@�����Ă⑊���x�������擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SODATEYA_AISHOU ret_wk
	.short	EV_SEQ_GET_SODATEYA_AISHOU
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *�@�^�}�S���Y�܂�Ă��邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_SODATEYA_TAMAGO_CHK ret_wk
	.short	EV_SEQ_SODATEYA_TAMAGO_CHK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *�@�莝���ɓ���̃|�P���������邩���`�F�b�N
 *  �����FTRUE�@���Ȃ��FFALSE
 */
//-----------------------------------------------------------------------------
	.macro	_TEMOTI_POKE_CHK	ret_wk,num
	.short	EV_SEQ_TEMOTI_POKE_CHK
	.short	\ret_wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *�@������������ׁF�L�^�Ǝ莝���|�P�����̔�r
 */
//-----------------------------------------------------------------------------
	.macro	_OOKISA_RECORD_CHK	ret_wk,num
	.short	EV_SEQ_OOKISA_RECORD_CHK
	.short	\ret_wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *�@������������ׁF�莝���̃|�P�����ŋL�^�X�V
 */
//-----------------------------------------------------------------------------
	.macro	_OOKISA_RECORD_SET	num
	.short	EV_SEQ_OOKISA_RECORD_SET
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *�@������������ׁF�莝���̃|�P�����̑傫���𐔒l�ɂ��ĕ����o�b�t�@�փZ�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_OOKISA_TEMOTI_SET_BUF	buf1,buf2,num
	.short	EV_SEQ_OOKISA_TEMOTI_SET_BUF
	.short	\buf1
	.short	\buf2
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *�@������������ׁF�L�^�|�P�����̑傫���𐔒l�ɂ��ĕ����o�b�t�@�փZ�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_OOKISA_KIROKU_SET_BUF	buf1,buf2,monsno
	.short	EV_SEQ_OOKISA_KIROKU_SET_BUF
	.short	\buf1
	.short	\buf2
	.short	\monsno
	.endm

//-----------------------------------------------------------------------------
/**
 *�@������������ׁF�������B���R�[�h���N���A
 */
//-----------------------------------------------------------------------------
	.macro	_OOKISA_KURABE_INIT
	.short	EV_SEQ_OOKISA_KURABE_INIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	���U�I����ʌĂяo��
 */
//-----------------------------------------------------------------------------
	.macro	_WAZALIST_SET_PROC	wk
	.short	EV_SEQ_WAZALIST_SET_PROC
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ���U�I����ʌ��ʎ��o��
 */
//-----------------------------------------------------------------------------
	.macro	_WAZALIST_GET_RESULT	ret_wk
	.short	EV_SEQ_WAZALIST_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����Ă��郏�U�����J�E���g
 */
//-----------------------------------------------------------------------------
	.macro	_WAZA_COUNT				ret_wk,num
	.short	EV_SEQ_WAZA_COUNT
	.short	\ret_wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	���U������
 */
//-----------------------------------------------------------------------------
	.macro	_WAZA_DEL	t_num,w_num
	.short	EV_SEQ_WAZA_DEL
	.short	\t_num
	.short	\w_num
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���̃��U�ԍ����擾
 */
//-----------------------------------------------------------------------------
	.macro	_TEMOTI_WAZANO		wk,t_num,w_num
	.short	EV_SEQ_TEMOTI_WAZANO
	.short	\wk
	.short	\t_num
	.short	\w_num
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���̃��U���o�b�t�@��
 */
//-----------------------------------------------------------------------------
	.macro	_TEMOTI_WAZA_NAME		idx,t_num,w_num
	.short	EV_SEQ_TEMOTI_WAZA_NAME
	.byte	\idx
	.short	\t_num
	.short	\w_num
	.endm


//============================================================================================
//
//	�`���m�[�g�֘A
//
//============================================================================================

//-----------------------------------------------------------------------------
/**
 *	�`���m�[�g�J�n�f�[�^�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_FNOTE_START_SET
	.short	EV_SEQ_FNOTE_START_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	�`���m�[�g�f�[�^�쐬
 */
//-----------------------------------------------------------------------------
	.macro	_FNOTE_DATA_MAKE	id,wk1,wk2,wk3,wk4
	.short	EV_SEQ_FNOTE_DATA_MAKE
	.short	\id
	.short	\wk1
	.short	\wk2
	.short	\wk3
	.short	\wk4
	.endm

//-----------------------------------------------------------------------------
/**
 *	���g�p
 */
//-----------------------------------------------------------------------------
	.macro	_FNOTE_DATA_SAVE
	.short	EV_SEQ_FNOTE_DATA_SAVE
	.endm


//============================================================================================
//
//	�C���[�W�N���b�v�A�C�e���֘A
//
//============================================================================================

//-----------------------------------------------------------------------------
/**
 *	�C���[�W�N���b�v�F�A�N�Z�T���[�F�A�C�e����������
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_ACCE_ADD_ITEM	acce_no,num
	.short	EV_SEQ_IMC_ACCE_ADD_ITEM
	.short	\acce_no
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C���[�W�N���b�v�F�A�N�Z�T���[�F�A�C�e�����������邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_ACCE_ADD_ITEM_CHK	acce_no,num,ret_wk
	.short	EV_SEQ_IMC_ACCE_ADD_ITEM_CHK
	.short	\acce_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C���[�W�N���b�v�F�A�N�Z�T���[�F�o�b�O�̃A�C�e���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_ACCE_ITEM_CHK		acce_no,num,ret_wk
	.short	EV_SEQ_IMC_ACCE_ITEM_CHK
	.short	\acce_no
	.short	\num
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C���[�W�N���b�v�F�w�i�F�A�C�e����������
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_BG_ADD_ITEM	bg_no
	.short	EV_SEQ_IMC_BG_ADD_ITEM
	.short	\bg_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C���[�W�N���b�v�F�w�i�F�o�b�O�̃A�C�e���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_BG_ITEM_CHK		bg_no,ret_wk
	.short	EV_SEQ_IMC_BG_ITEM_CHK
	.short	\bg_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�܂��܂������F�Ăяo���}�N��
 */
//-----------------------------------------------------------------------------
	.macro	_NUTMIXER_CALL			mode
	.short	EV_SEQ_NUTMIXER_CALL
	.short	\mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	�܂��܂������v���C�\���`�F�b�N�F�Ăяo���}�N��
 */
//-----------------------------------------------------------------------------
	.macro	_NUTMIXER_PLAY_CHECK	retwk
	.short	EV_SEQ_NUTMIXER_PLAY_CHECK
	.short	\retwk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V���I�E�}�ӂ��������Ă��邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_CHK_SHINOU		ret_wk
	.short	EV_SEQ_ZUKAN_CHK_SHINOU
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�S���}�ӂ��������Ă��邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_CHK_NATIONAL		ret_wk
	.short	EV_SEQ_ZUKAN_CHK_NATIONAL
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V���I�E�}�ӕ\��
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_RECONGNIZE_SHINOU
	.short	EV_SEQ_ZUKAN_RECONGNIZE_SHINOU
	.endm

//-----------------------------------------------------------------------------
/**
 *	�S���}�ӕ\��
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_RECONGNIZE_NATIONAL
	.short	EV_SEQ_ZUKAN_RECONGNIZE_NATIONAL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�E�����}�G���J�E���g�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_URAYAMA_ENCOUNT_SET
	.short	EV_SEQ_URAYAMA_ENCOUNT_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	�E�����}�G���J�E���g�`�F�b�N�i���݂̊Y������|�P�����ԍ��擾�j
 */
//-----------------------------------------------------------------------------
	.macro	_URAYAMA_ENCOUNT_NO_CHK				ret_wk
	.short	EV_SEQ_URAYAMA_ENCOUNT_NO_CHK
	.short	\ret_wk
	.endm



//-----------------------------------------------------------------------------
/**
 *	���[���������Ă��邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_MAIL_CHK		ret_wk,tno
	.short	EV_SEQ_POKE_MAIL_CHK
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	���Ƃ��ꏊ�����߂�
 */
//-----------------------------------------------------------------------------
	.macro	_PAPERPLANE_SET			ret_wk
	.short	EV_SEQ_PAPERPLANE_SET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����Ă��郁�[�����폜
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_MAIL_DEL			tno
	.short	EV_SEQ_POKE_MAIL_DEL
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	���΂������邩�̃`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_KASEKI_COUNT			ret_wk
	.short	EV_SEQ_KASEKI_COUNT	
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�C�e���I��
 */
//-----------------------------------------------------------------------------
	.macro	_ITEMLIST_SET_PROC
	.short	EV_SEQ_ITEMLIST_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	�I�������A�C�e���ԍ��擾
 */
//-----------------------------------------------------------------------------
	.macro	_ITEMLIST_GET_RESULT		ret_wk
	.short	EV_SEQ_ITEMLIST_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�A�C�e���i���΁j�ԍ����A�����X�^�[�ԍ��֕ϊ�(0:���΂ł͂Ȃ��Ƃ��͂O�j
 */
//-----------------------------------------------------------------------------
	.macro	_ITEMNO_TO_MONSNO		ret_wk,itemno
	.short	EV_SEQ_ITEMNO_TO_MONSNO
	.short	\ret_wk
	.short	\itemno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝����xxx�Ԗڂ̉��΂������ăA�C�e���ԍ��ɂ��ĕԂ�(0:�ŏ���1��)
 */
//-----------------------------------------------------------------------------
	.macro	_KASEKI_ITEMNO		ret_wk,ret_wk_mes,no
	.short	EV_SEQ_KASEKI_ITEMNO
	.short	\ret_wk
	.short	\ret_wk_mes
	.short	\no
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *	�|�P�������x���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_LEVEL_CHK		ret_wk,level
	.short	EV_SEQ_POKE_LEVEL_CHK
	.short	\ret_wk
	.short	\level
	.endm



//======================================
//��������o�g���^���[�֘A
//======================================
//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[�A�v���Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_APP_CALL	main,sub
	.short	EV_SEQ_BTOWER_APP_CALL
	.short	\main
	.short	\sub
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[���[�N������
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_WORK_CLEAR
	.short	EV_SEQ_BATTLE_TOWER_WORK_CLEAR
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[���[�N�m�ہ�������
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_WORK_INIT		init,mode
	.short	EV_SEQ_BATTLE_TOWER_WORK_INIT
	.short	\init
	.short	\mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[���[�N���
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_WORK_RELEASE
	.short	EV_SEQ_BATTLE_TOWER_WORK_RELEASE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[ �R�}���h�c�[���Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_TOOLS	cmd,param,ret_wk
	.short	EV_SEQ_BATTLE_TOWER_TOOLS
	.short	\cmd
	.short	\param
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[ 5�l�O�̃|�P�����f�[�^�擾
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_SEVEN_POKE_GET	id,idx,ret_poke,ret_waza
	.short	EV_SEQ_BATTLE_TOWER_GET_SEVEN_POKE	//5�l�O�̃|�P�����f�[�^�Q�b�g
	.short	\id
	.short	\idx
	.short	\ret_poke
	.short	\ret_waza
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[ �v���C�Y���擾
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_PRIZE_GET	ret_wk
	.short	EV_SEQ_BATTLE_TOWER_IS_PRIZE_GET	//�o�g���^���[�@�v���C�Y�擾
	.short	\ret_wk
	.endm
//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[ �v���C�Y�������l�����Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_PRIZEMAN_SET	ret_wk
	.short	EV_SEQ_BATTLE_TOWER_IS_PRIZEMAN_SET
	.short	\ret_wk
	.endm
//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[ �ėp�f�[�^���M
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_SEND_BUF	mode,param
	.short	EV_SEQ_BATTLE_TOWER_SEND_BUF
	.short	\mode
	.short	\param
	.endm
//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[ �ėp�f�[�^��M
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_RECV_BUF	mode,ret_wk
	.short	EV_SEQ_BATTLE_TOWER_RECV_BUF
	.short	\mode
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[ ���[�_�[�f�[�^RoomID�擾
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_GET_LEADER_ROOMID	ret_rank,ret_no
	.short	EV_SEQ_BATTLE_TOWER_GET_LEADER_ROOM_ID
	.short	\ret_rank
	.short	\ret_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���^���[ ���[�_�[�f�[�^�����݂��邩�ǂ����H
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_IS_LEADER_EXIST	ret_wk
	.short	EV_SEQ_BATTLE_TOWER_IS_READER_DATA_EXIST	//�o�g���^���[�@���[�_�[�f�[�^�̗L��
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
//���R�[�h�֘A
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *	���R�[�h�C���N�������g
 */
//-----------------------------------------------------------------------------
//	.macro	_RECORD_INC	cmd,recid
	.macro	_RECORD_INC	recid
	.short	EV_SEQ_RECORD_INC
	.short	\recid
	.endm
//-----------------------------------------------------------------------------
/**
 *	���R�[�h�Q�b�g
 *
 *	recid:RECID_XXXXX
 *	h_wk:��ʃo�C�g�擾���[�N
 *	l_wk:���ʃo�C�g�擾���[�N
 */
//-----------------------------------------------------------------------------
	.macro	_RECORD_GET	cmd,recid,h_wk,l_wk
	.short	EV_SEQ_RECORD_GET
	.short	\recid
	.short	\h_wk
	.short	\l_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���R�[�hAdd
 *
 *	recid:RECID_XXXXX
 *	h_val:��ʃo�C�g
 *	l_val:���ʃo�C�g
 */
//-----------------------------------------------------------------------------
	.macro	_RECORD_ADD	cmd,recid,h_val,l_val
	.short	EV_SEQ_RECORD_SET
	.short	\recid
	.short	\h_val
	.short	\l_val
	.byte	0
	.endm
//-----------------------------------------------------------------------------
/**
 *	���R�[�hSet
 *
 *	recid:RECID_XXXXX
 *	h_val:��ʃo�C�g
 *	l_val:���ʃo�C�g
 */
//-----------------------------------------------------------------------------
	.macro	_RECORD_SET	cmd,recid,h_val,l_val
	.short	EV_SEQ_RECORD_SET
	.short	\recid
	.short	\h_val
	.short	\l_val
	.byte	1
	.endm
//-----------------------------------------------------------------------------
/**
 *	���R�[�hSetIfLarge
 *
 *	recid:RECID_XXXXX
 *	h_val:��ʃo�C�g
 *	l_val:���ʃo�C�g
 */
//-----------------------------------------------------------------------------
	.macro	_RECORD_SETIFLARGE	cmd,recid,h_val,l_val
	.short	EV_SEQ_RECORD_SET
	.short	\recid
	.short	\h_val
	.short	\l_val
	.byte	2
	.endm

//============================================================================================
//
//		�T�t�@���֘A
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 *	�T�t�@���J�n	
 */
//-----------------------------------------------------------------------------
	.macro	_SAFARI_START
	.short	EV_SEQ_SAFARI_CTRL
	.byte	0
	.endm

//-----------------------------------------------------------------------------
/**
 *	�T�t�@���I��
 */
//-----------------------------------------------------------------------------
	.macro	_SAFARI_END
	.short	EV_SEQ_SAFARI_CTRL
	.byte	1
	.endm

//-----------------------------------------------------------------------------
/**
 *	�T�t�@���]����
 */
//-----------------------------------------------------------------------------
	.macro	_CALL_SAFARI_SCOPE
	.short	EV_SEQ_CALL_SAFARI_SCOPE
	.endm


//============================================================================================
//
//		�e���K���U���R���f��
//
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_CLIMAX_DEMO	id, ret_wk
	.short	EV_SEQ_CLIMAXDEMO
	.byte	\id
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�T�t�@���d�ԏ�����
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_SAFARI_TRAIN
	.short	EV_SEQ_INIT_SAFARI_TRAIN
	.endm

//-----------------------------------------------------------------------------
/**
 *	�T�t�@���d�Ԉړ�
 */
//-----------------------------------------------------------------------------
	.macro	_MOVE_SAFARI_TRAIN	pos, type
	.short	EV_SEQ_MOVE_SAFARI_TRAIN
	.short	\pos
	.short	\type
	.endm

//-----------------------------------------------------------------------------
/**
 *	�T�t�@���d�Ԉʒu�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CHECK_SAFARI_TRAIN	pos, ret_wk
	.short	EV_SEQ_CHECK_SAFARI_TRAIN
	.short	\pos
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���@�����擾�L���L��
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_HEGIHT_VALID valid
	.short	EV_SEQ_PLAYER_HEGIHT_VALID
	.byte	\valid
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�����̐��i���Q�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKE_SEIKAKU ret_wk,tno
	.short	EV_SEQ_GET_POKE_SEIKAKU
	.short \ret_wk
	.short \tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	����̐��i�̃|�P���������邩���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_POKE_SEIKAKU_ALL ret_wk,seikaku_no
	.short	EV_SEQ_CHK_POKE_SEIKAKU_ALL
	.short \ret_wk
	.short \seikaku_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���ŉ�b�����l���̗݌v(�~�J�Q��p�Łj
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_TALK_COUNT	ret_wk
	.short	EV_SEQ_UNDERGROUND_TALK_COUNT
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���R���������J�E���g�N���A
 */
//-----------------------------------------------------------------------------
	.macro	_NATURAL_PARK_WALK_COUNT_CLEAR
	.short	EV_SEQ_NATURAL_PARK_WALK_COUNT_CLEAR
	.endm

//-----------------------------------------------------------------------------
/**
 *	���R���������`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_NATURAL_PARK_WALK_COUNT_GET	ret_wk
	.short	EV_SEQ_NATURAL_PARK_WALK_COUNT_GET
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���R�����ŖႦ��A�N�Z�T���[�ԍ��擾
 */
//-----------------------------------------------------------------------------
	.macro	_NATURAL_PARK_ACCESSORY_NO_GET		ret_wk,mon_wk
	.short	EV_SEQ_NATURAL_PARK_ACCESSORY_NO_GET
	.short \ret_wk
	.short \mon_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V���ЁF��Ă���|�P�����ԍ��擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_NEWS_POKE_NO				ret_wk
	.short	EV_SEQ_GET_NEWS_POKE_NO
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V���ЁF���ߐ؂�܂ł̎c������Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_NEWS_COUNT_SET		no
	.short	EV_SEQ_NEWS_COUNT_SET
	.short \no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V���ЁF���ߐ؂�܂ł̎c������`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_NEWS_COUNT_CHK				ret_wk
	.short	EV_SEQ_NEWS_COUNT_CHK
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	��ʔ����J�n
 */
//-----------------------------------------------------------------------------
	.macro	_START_GENERATE
	.short	EV_SEQ_START_GENERATE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�ړ��|�P�����o�^
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_MOVE_POKE		poke
	.short	EV_SEQ_ADD_MOVE_POKE
	.byte	\poke
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�����ɋ�������킴�����擾	���d�l�ύX�ɂ�薢����
 */
//-----------------------------------------------------------------------------
	.macro	_OSHIE_WAZA_COUNT		ret_wk,tno
	.short	EV_SEQ_OSHIE_WAZA_COUNT
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�������v���o����킴�����擾
 */
//-----------------------------------------------------------------------------
	.macro	_REMAIND_WAZA_COUNT		ret_wk,tno
	.short	EV_SEQ_REMAIND_WAZA_COUNT
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�킴�����I����ʌĂяo��	���d�l�ύX�ɂ�薢����
 */
//-----------------------------------------------------------------------------
	.macro	_OSHIE_WAZALIST_SET_PROC	wk
	.short	EV_SEQ_OSHIE_WAZALIST_SET_PROC
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�킴�v���o���I����ʌĂяo��
 */
//-----------------------------------------------------------------------------
	.macro	_REMAIND_WAZALIST_SET_PROC	wk
	.short	EV_SEQ_REMAIND_WAZALIST_SET_PROC
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�킴�����I����ʌ��ʎ��o�����d�l�ύX�ɂ�薢����
 */
//-----------------------------------------------------------------------------
	.macro	_OSHIE_WAZALIST_GET_RESULT	ret_wk
	.short	EV_SEQ_OSHIE_WAZALIST_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�킴�v���o���I����ʌ��ʎ��o��
 */
//-----------------------------------------------------------------------------
	.macro	_REMAIND_WAZALIST_GET_RESULT	ret_wk
	.short	EV_SEQ_REMAIND_WAZALIST_GET_RESULT
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	1�݂̂̂킴�����I����ʌĂяo��
 */
//-----------------------------------------------------------------------------
	.macro	_NORMAL_WAZALIST_SET_PROC	wk,waza
	.short	EV_SEQ_NORMAL_WAZALIST_SET_PROC
	.short	\wk
	.short	\waza
	.endm

//-----------------------------------------------------------------------------
/**
 *	1�݂̂̂킴�����I����ʌ��ʎ��o��
 */
//-----------------------------------------------------------------------------
	.macro	_NORMAL_WAZALIST_GET_RESULT	ret_wk
	.short	EV_SEQ_NORMAL_WAZALIST_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����f�[�^�쐬
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_TRADE_ALLOC	tradeno
	.short	EV_SEQ_FLD_TRADE_ALLOC
	.byte	\tradeno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����|�P�����i���o�[�擾
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_TRADE_MONSNO	ret_wk
	.short	EV_SEQ_FLD_TRADE_MONSNO
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�킽���|�P�����i���o�[�擾
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_TRADE_CHG_MONSNO	ret_wk
	.short	EV_SEQ_FLD_TRADE_CHG_MONSNO
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����f�[�^�C�x���g
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_TRADE_EVENT	pos
	.short	EV_SEQ_FLD_TRADE_EVENT
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����f�[�^�폜
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_TRADE_DEL
	.short	EV_SEQ_FLD_TRADE_DEL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�}�Ӄe�L�X�gVerUp
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_TEXT_VER_UP
	.short	EV_SEQ_ZUKAN_TEXT_VER_UP
	.endm

//-----------------------------------------------------------------------------
/**
 *	�}�Ӑ���VerUp
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_SEX_VER_UP
	.short	EV_SEQ_ZUKAN_SEX_VER_UP
	.endm

//-----------------------------------------------------------------------------
/**
 *	�S���}�Ӄt���O����
 */
//-----------------------------------------------------------------------------
	.macro	_ZENKOKU_ZUKAN_FLAG	mode,ret_wk
	.short	EV_SEQ_ZENKOKU_ZUKAN_FLAG
	.byte	\mode
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�u���{���v�̎擾���i�P�|�P�����j
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_RIBBON_COUNT		ret_wk,tno
	.short	EV_SEQ_CHK_RIBBON_COUNT
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�u���{���v�̎擾���i�S�莝���|�P�������v�̎�ށj
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_RIBBON_COUNT_ALL		ret_wk
	.short	EV_SEQ_CHK_RIBBON_COUNT_ALL
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�u���{���v�������Ă��邩
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_RIBBON		ret_wk,tno,rno
	.short	EV_SEQ_CHK_RIBBON
	.short	\ret_wk
	.short	\tno
	.short	\rno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�u���{���v���Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_SET_RIBBON		tno,rno
	.short	EV_SEQ_SET_RIBBON
	.short	\tno
	.short	\rno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�u���{���v�����o�b�t�@�փZ�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_RIBBON_NAME		idx,rno
	.short	EV_SEQ_RIBBON_NAME
	.byte	\idx
	.short	\rno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�w�͒l���擾
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_PRMEXP	ret_wk,tno
	.short	EV_SEQ_CHK_PRMEXP
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�j���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_WEEK	ret_wk
	.short	EV_SEQ_CHK_WEEK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g�s�b�N�����F�B���A�C�e�������I
 */
//-----------------------------------------------------------------------------
	.macro	_TV_ENTRY_WATCH_HIDE_ITEM	item_no
	.short	EV_SEQ_TV_ENTRY_WATCH_HIDE_ITEM
	.short	\item_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	�g�s�b�N�����F�������f
 */
//-----------------------------------------------------------------------------
	.macro	_TV_ENTRY_WATCH_CHANGE_NAME	mons_pos
	.short	EV_SEQ_TV_ENTRY_WATCH_CHANGE_NAME
	.short	\mons_pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	���M�����[�V�������[���u�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_REGULATION_LIST_CALL	ret_wk
	.short	EV_SEQ_REGULATION_LIST_CALL
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	���Ճ`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_ASHIATO_CHK	ret_wk,ret2_wk,tno
	.short	EV_SEQ_ASHIATO_CHK
	.short	\ret_wk
	.short	\ret2_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�Z���񕜃}�V���A�j��
 */
//-----------------------------------------------------------------------------
	.macro	_PC_RECOVER_ANM	ball_num
	.short	EV_SEQ_PC_RECOVER_ANM
	.short	\ball_num
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	�G���x�[�^�[�A�j��
 */
//-----------------------------------------------------------------------------
	.macro	_ELEVATOR_ANM	dir, loop
	.short	EV_SEQ_ELEVATOR_ANM
	.short	\dir
	.short	\loop
	.endm

//-----------------------------------------------------------------------------
/**
 *	�D�f���R�[��
 */
//-----------------------------------------------------------------------------
	.macro	_CALL_SHIP_DEMO	ship_dir, play_dir, zone, x, z
	.short	EV_SEQ_CALL_SHIP_DENO
	.byte	\ship_dir
	.byte	\play_dir
	.short	\zone
	.short	\x
	.short	\z
	.endm


//-----------------------------------------------------------------------------
/**
 *	�f�o�b�O��p���߁@���[�N�̒��g
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_PRINT_WORK	wk
	.short	EV_SEQ_DEBUG_PRINT_WORK	
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�f�o�b�O��p���߁@�t���O�̒l��\��
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_PRINT_FLAG	num
	.short	EV_SEQ_DEBUG_PRINT_FLAG
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	�f�o�b�O��p����(�풓�̈�ŁB���ł��g�pOK�j�@���[�N�̒��g
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_PRINT_WORK_STATIONED	wk
	.short	EV_SEQ_DEBUG_PRINT_WORK_STATIONED
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�f�o�b�O��p����(�풓�̈�ŁB���ł��g�pOK�j�@�t���O�̒��g
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_PRINT_FLAG_STATIONED	num
	.short	EV_SEQ_DEBUG_PRINT_FLAG_STATIONED
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�[�W�����擾
 */
//-----------------------------------------------------------------------------
	.macro	_PM_VERSION_GET	ret_wk
	.short	EV_SEQ_PM_VERSION_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�擪�̃|�P������Ԃ��i�^�}�S�𔲂������j
 */
//-----------------------------------------------------------------------------
	.macro	_FRONT_POKEMON	ret_wk
	.short	EV_SEQ_FRONT_POKEMON	
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���̃|�P�����^�C�v�擾
 */
//-----------------------------------------------------------------------------
	.macro	_TEMOTI_POKE_TYPE	ret_wk1,ret_wk2,tno
	.short	EV_SEQ_TEMOTI_POKE_TYPE	
	.short	\ret_wk1
	.short	\ret_wk2
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�������Ƃ΂ɊY������ǎ���L����
 */
//-----------------------------------------------------------------------------
	.macro	_AIKOTOBA_KABEGAMI_SET		ret_wk,wk1,wk2,wk3,wk4
	.short	EV_SEQ_AIKOTOBA_KABEGAMI_SET
	.short	\ret_wk
	.short	\wk1
	.short	\wk2
	.short	\wk3
	.short	\wk4
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���Ŏ擾�����n�^�̑����擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_UG_HATA_NUM		ret_wk
	.short	EV_SEQ_GET_UG_HATA_NUM
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	�p�\�R���A�j���Z�b�g�A�b�v
 */
//-----------------------------------------------------------------------------
	.macro	_SETUP_PASO_ANM		id
	.short	EV_SEQ_SETUP_PASO_ANM
	.byte \id
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	�p�\�R������A�j��
 */
//-----------------------------------------------------------------------------
	.macro	_START_PASO_ON_ANM	id
	.short	EV_SEQ_START_PASO_ON_ANM
	.byte \id
	.endm

//-----------------------------------------------------------------------------
/**
 *	�p�\�R�������A�j��
 */
//-----------------------------------------------------------------------------
	.macro	_START_PASO_OFF_ANM id
	.short	EV_SEQ_START_PASO_OFF_ANM
	.byte \id
	.endm

//-----------------------------------------------------------------------------
/**
 *	����������ԍ��Q�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_GET_KUJI_ATARI_NUM	ret_wk
	.short	EV_SEQ_GET_KUJI_ATARI_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	����������`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_KUJI_ATARI_CHK	ret_wk1,ret_wk2,ret_wk3,num
	.short	EV_SEQ_KUJI_ATARI_CHK
	.short	\ret_wk1
	.short	\ret_wk2
	.short	\ret_wk3
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	����������ԍ�������
 */
//-----------------------------------------------------------------------------
	.macro	_KUJI_ATARI_INIT
	.short	EV_SEQ_KUJI_ATARI_INIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	PC��̃|�P�����̃j�b�N�l�[��
 */
//-----------------------------------------------------------------------------
	.macro	_NICK_NAME_PC	idx,pos
	.short	EV_SEQ_NICK_NAME_PC
	.byte	\idx
	.short	\pos
	.endm

//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * �C���^�r���A�[�̏o���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_TV_INTERVIEWER_CHECK	id, ret_wk
	.short	EV_SEQ_TV_INTERVIEW_CHK
	.short	\id
	.short	\ret_wk
	.endm	

//============================================================================================
//
//
//			�|�P�p�[�N�֘A
//
//
//============================================================================================
//-----------------------------------------------------------------------------
///		�{�b�N�X�̋󂫂𐔂���
//-----------------------------------------------------------------------------
	.macro	_COUNT_MONSBOX_SPACE	ret_wk
	.short	EV_SEQ_COUNT_POKEBOX_SPACE
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
///		�|�P�p�[�N�Q�[������
//-----------------------------------------------------------------------------
	.macro	_POKEPARK_CONTROL	id
	.short	EV_SEQ_POKEPARK_CONTROL
	.short	\id
	.endm

//-----------------------------------------------------------------------------
///		�|�P�p�[�N�ɗa���Ă���|�P�����̐��𐔂���
//-----------------------------------------------------------------------------
	.macro	_POKEPARK_DEPOSIT_COUNT	ret_wk
	.short EV_SEQ_COUNT_POKEPARK_BOX
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
///		�|�P�p�[�N�ɗa�����|�P�������{�b�N�X�ɓ]��
//-----------------------------------------------------------------------------
	.macro	_POKEPARK_TRANS_MONS
	.short	EV_SEQ_TRANS_POKEPARK_MONS
	.endm

//-----------------------------------------------------------------------------
///		�|�P�p�[�N�Q�[���̌��ʃX�R�A�擾
//-----------------------------------------------------------------------------
	.macro	_POKEPARK_GET_SCORE		type, ret_wk
	.short	EV_SEQ_GET_POKEPARK_SCORE
	.short	\type
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
///		�a���}�V����{�[���A�j��
//-----------------------------------------------------------------------------
	.macro	_DENDOU_BALL_ANM	ball_num
	.short	EV_SEQ_DENDOU_BALL_ANM
	.short	\ball_num
	.endm
	
//-----------------------------------------------------------------------------
///		�t�B�[���h���t�g������
//-----------------------------------------------------------------------------
	.macro	_INIT_FLD_LIFT
	.short	EV_SEQ_INIT_FLD_LIFT
	.endm

//-----------------------------------------------------------------------------
///		�t�B�[���h���t�g�ړ�
//-----------------------------------------------------------------------------
	.macro	_MOVE_FLD_LIFT
	.short	EV_SEQ_MOVE_FLD_LIFT
	.endm

//-----------------------------------------------------------------------------
///		�t�B�[���h���t�g�`�F�b�N
//-----------------------------------------------------------------------------
	.macro	_CHECK_FLD_LIFT		ret_wk
	.short	EV_SEQ_CHECK_FLD_LIFT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
///		���C�A�C�n�C�@�V�����_�[�A�j���Z�b�g�A�b�v
//-----------------------------------------------------------------------------
	.macro	_SETUP_RAH_CYL
	.short	EV_SEQ_SETUP_RAH_CYL
	.endm

//-----------------------------------------------------------------------------
///		���C�A�C�n�C�@�V�����_�[�A�j���X�^�[�g
//-----------------------------------------------------------------------------
	.macro	_START_RAH_CYL
	.short	EV_SEQ_START_RAH_CYL
	.endm

//-----------------------------------------------------------------------------
///		�X�R�A���Z
//-----------------------------------------------------------------------------
	.macro	_ADD_SCORE	score_id
	.short	EV_SEQ_ADD_SCORE
	.short	\score_id
	.endm
//-----------------------------------------------------------------------------
/**
 *	�u�A�N�Z�T���[�v�����o�b�t�@�փZ�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_ACCE_NAME		idx,acceno
	.short	EV_SEQ_ACCE_NAME
	.byte	\idx
	.short	\acceno
	.endm


//-----------------------------------------------------------------------------
///		�p�[�e�B���Ɏw�肵���|�P���������邩�`�F�b�N
//-----------------------------------------------------------------------------
	.macro	_PARTY_MONSNO_CHECK	monsno, ret_wk
	.short	EV_SEQ_PARTY_MONSNO_CHECK
	.short	\monsno
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
///		�p�[�e�B���̃f�I�L�V�X�̃t�H������ύX
//-----------------------------------------------------------------------------
	.macro	_PARTY_DEOKISISUFORM_CHANGE	form
	.short	EV_SEQ_PARTY_DEOKISISUFORM_CHANGE
	.short	\form
	.endm

//-----------------------------------------------------------------------------
///		�p�[�e�B���Ƀ~�m���b�`3�`�Ԃ���������`�F�b�N
//-----------------------------------------------------------------------------
	.macro	_CHECKMINOMUCHICOMP	ret_wk
	.short	EV_SEQ_CHECKMINOMUCHICOMP
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�b�`���t�b�N����
 */
//-----------------------------------------------------------------------------
	.macro	_POKETCH_HOOK_SET
	.short	EV_SEQ_POKETCH_HOOK_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�P�b�`�̃t�b�N����������
 */
//-----------------------------------------------------------------------------
	.macro	_POKETCH_HOOK_RESET
	.short	EV_SEQ_POKETCH_HOOK_RESET
	.endm


//-----------------------------------------------------------------------------
/**
 * �X���b�g�}�V�[��
 */
//-----------------------------------------------------------------------------
	.macro	_SLOT_MACHINE	id
	.short	EV_SEQ_SLOT_MACHINE
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 * ���݂̎����i����:0-23)
 */
//-----------------------------------------------------------------------------
	.macro	_GET_NOW_HOUR	ret_wk
	.short	EV_SEQ_GET_NOW_HOUR
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �t�B�[���hOBJ��h�炷�A�j���[�V����
 */
//-----------------------------------------------------------------------------
	.macro	_FLDOBJ_SHAKE_ANM	objid,count,spd,ofsx,ofsz
	.short	EV_SEQ_FLDOBJ_SHAKE_ANM		//�t�B�[���hOBJ��h�炷�A�j��
	.short	\objid
	.short	\count
	.short	\spd
	.short	\ofsx
	.short	\ofsz
	.endm

//-----------------------------------------------------------------------------
/**
 * �t�B�[���hOBJ��blink������A�j��
 */
//-----------------------------------------------------------------------------
	.macro	_FLDOBJ_BLINK_ANM	objid,count,time
	.short	EV_SEQ_FLDOBJ_BLINK_ANM		//�t�B�[���hOBJ��blink�A�j��
	.short	\objid
	.short	\count
	.short	\time
	.endm

//-----------------------------------------------------------------------------
/**
 * d20r0106 ���W�L���O��������`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_D20R0106_LEGEND_IS_UNSEAL	ret_val
	.short	EV_SEQ_D20R0106_LEGEND_IS_UNSEAL	//���W�L���O����`�F�b�N
	.short	\ret_val
	.endm


//-----------------------------------------------------------------------------
/**
 * ���������o����F�����_���ŃC���[�W�N���b�v�̃A�N�Z�T���[�擾
 *  ret_wk = �擾�����A�N�Z�T���[�̔ԍ��A�@0xffff���擾�o���Ȃ�����
 */
//-----------------------------------------------------------------------------
	.macro	_DRESSING_IMC_ACCE_CHECK	ret_wk
	.short	EV_SEQ_DRESSING_IMC_ACCE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �A���m�[�������Ń��b�Z�[�W�\��
 */
//-----------------------------------------------------------------------------
	.macro		_UNKNOWN_MSG	msg_id
	.short		EV_SEQ_UNKNOWN_MSG
	.short		\msg_id
	.endm



//-----------------------------------------------------------------------------
/**
 *	�������Ă���AGB�J�[�g���b�W�o�[�W�����擾
 */
//-----------------------------------------------------------------------------
	.macro	_AGB_CARTRIDGE_VER_GET	ret_val
	.short	EV_SEQ_AGB_CARTRIDGE_VER_GET
	.short	\ret_val
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���ŉ�b�����l���̗݌v���N���A
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_TALK_COUNT_CLEAR
	.short	EV_SEQ_UNDERGROUND_TALK_COUNT_CLEAR
	.endm

//-----------------------------------------------------------------------------
/**
 *	�B���}�b�v�X�e�[�^�X�`�F���W
 */
//-----------------------------------------------------------------------------
	.macro	_HIDEMAP_STATE_CHG	hidemap_id,flag
	.short	EV_SEQ_HIDEMAP_STATE_CHANGE		//�B���}�b�v�X�e�[�^�X�`�F���W
	.short	\hidemap_id
	.byte	\flag
	.endm
//-----------------------------------------------------------------------------
/**
 *	r224�Δ薼���͌Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_NAMEIN_MONUMENT	ret_wk
	.short	EV_SEQ_NAMEIN_MONUMENT			//r224�Δ薼����
	.short	\ret_wk
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	r224�Δ薼�^�O�W�J
 */
//-----------------------------------------------------------------------------
	.macro	_MONUMENT_NAME	idx
	.short	EV_SEQ_MONUMENT_NAME			//r224�Δ薼�^�O�W�J
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C���[�W�N���b�v�u�w�i�v�����o�b�t�@�փZ�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_BG_NAME		idx,bgno
	.short	EV_SEQ_IMC_BG_NAME_SET
	.byte	\idx
	.short	\bgno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�C���𒲂ׂ�i�����������Ă��邩��Ԃ��j
 */
//-----------------------------------------------------------------------------
	.macro	_COMP_COIN ret_wk,val
	.short	EV_SEQ_COMP_COIN
	.short	\ret_wk
	.long	\val
	.endm

//-----------------------------------------------------------------------------
/**
 * �X���b�g�Ń����`�������Ă��邩
 * TRUE=10��ȏ� FALSE=10��艺
 */
//-----------------------------------------------------------------------------
	.macro	_SLOT_RENTYAN_CHK ret_wk
	.short	EV_SEQ_SLOT_RENTYAN_CHK 
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�C���𑝂₹�邩�ǂ������`�F�b�N
 *	TRUE�@���₹�� / FALSE ���₹�Ȃ�
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_COIN_CHK ret_wk,val
	.short	EV_SEQ_ADD_COIN_CHK
	.short	\ret_wk
	.long	\val
	.endm

//-----------------------------------------------------------------------------
/**
 * �����ƃ��x������v������A�C�e����������̃i���o�[
 * 
 */
//-----------------------------------------------------------------------------
	.macro	_LEVEL_JIJII_NO ret_wk
	.short	EV_SEQ_LEVEL_JIJII_NO 
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���|�P�������x���Q�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_LEVEL_GET		ret_wk,tno
	.short	EV_SEQ_POKE_LEVEL_GET
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�C���[�W�N���b�v�F�A�N�Z�T���[�F�A�C�e�������炷
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_ACCE_SUB_ITEM	acce_no,num
	.short	EV_SEQ_IMC_ACCE_SUB_ITEM
	.short	\acce_no
	.short	\num
	.endm


//-----------------------------------------------------------------------------
/**
 *	�i�M�T�V�e�B�@�V���x�m����@�J�����ݒ�
 */
//-----------------------------------------------------------------------------
	.macro	_C08R0801SCOPECAMERASET
	.short	EV_SEQ_C08R0801SCOPECAMERASET
	.endm

//-----------------------------------------------------------------------------
/**
 *	���x���W�W�C������
 */
//-----------------------------------------------------------------------------
	.macro	_LEVEL_JIJII_INIT
	.short	EV_SEQ_LEVEL_JIJII_INIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	������Ƃ΂������_���łЂƂo��������
 */
//-----------------------------------------------------------------------------
	.macro	_NEW_NANKAI_WORD_SET	ret_wk,buf_id
	.short	EV_SEQ_NEW_NANKAI_WORD_SET
	.short	\ret_wk
	.short	\buf_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	��A�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_REGULAR_CHECK		ret_wk
	.short	EV_SEQ_REGULAR_CHECK		
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	������Ƃ΂�S�Ċo���Ă��邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_NEW_NANKAI_WORD_COMPLETE_CHECK	ret_wk
	.short	EV_SEQ_NANKAI_WORD_COMPLETE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�莝���|�P�����̃R���e�X�g�X�e�[�^�X�擾(�������悳�A���킢����)
 */
//-----------------------------------------------------------------------------
	.macro	_TEMOTI_POKE_CONTEST_STATUS_GET	pos,con_type,ret_wk
	.short	EV_SEQ_TEMOTI_POKE_CONTEST_STATUS_GET
	.short	\pos
	.short  \con_type
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	d17�߂炸�̓��A�@�}�b�v���I
 */
//-----------------------------------------------------------------------------
	.macro	_D17SYSTEM_MAP_SELECT	point,total
	.short	EV_SEQ_D17SYSTEM_MAP_SELECT		//D17�߂炸�̓��A�@�}�b�v���I
	.short	\point
	.short	\total
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���œ�����������l���̗݌v
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_TOOL_GIVE_COUNT	ret_wk
	.short	EV_SEQ_UNDERGROUND_TOOL_GIVE_COUNT
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���ł��������@�����񐔂̗݌v
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_KASEKI_DIG_COUNT	ret_wk
	.short	EV_SEQ_UNDERGROUND_KASEKI_DIG_COUNT
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���Ńg���b�v�ɂ������񐔂̗݌v
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_TRAP_HIT_COUNT	ret_wk
	.short	EV_SEQ_UNDERGROUND_TRAP_HIT_COUNT
	.short \ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	�|�t�B���ǉ�
 */
//-----------------------------------------------------------------------------
	.macro	_POFIN_ADD	ret_wk,spicy,astr,sweet,bitter,sour,taste
	.short	EV_SEQ_POFIN_ADD
	.short	\ret_wk
	.byte	\spicy		//�h��
	.byte	\astr		//�a��
	.byte	\sweet		//�Â�
	.byte	\bitter		//�ꂢ
	.byte	\sour		//�_���ς�
	.byte	\taste		//�|��
	.endm

//-----------------------------------------------------------------------------
/**
 *	�|�t�B�����ǉ��o���邩�`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_POFIN_ADD_CHK	ret_wk
	.short	EV_SEQ_POFIN_ADD_CHK
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	�z�z�C�x���g�L���`�F�b�N
 */
//-----------------------------------------------------------------------------
	.macro	_IS_HAIHU_EVENT_ENABLE	id,ret_wk
	.short	EV_SEQ_IS_HAIHU_EVENT_ENABLE	//�z�z�C�x���g�L���`�F�b�N
	.byte	\id
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����Ă�|�P�����I����ʌĂяo��
 */
//-----------------------------------------------------------------------------
	.macro	_SODATEYA_POKELIST_SET_PROC		pos
	.short	EV_SEQ_SODATEYA_POKELIST_SET_PROC
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 * �����Ă�|�P�����I����ʌ��ʎ��o��
 */
//-----------------------------------------------------------------------------
	.macro	_SODATEYA_POKELIST_GET_RESULT	ret_wk,ret_mode
	.short	EV_SEQ_SODATEYA_POKELIST_GET_RESULT
	.short	\ret_wk
	.short	\ret_mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	�w�肵���m����TRUE,FALSE��Ԃ�
 */
//-----------------------------------------------------------------------------
	.macro	_GET_RANDOM_HIT	per,ret_wk
	.short	EV_SEQ_GET_RANDOM_HIT	//�w�肵���m����TRUE,FALSE��Ԃ�
	.byte	\per			//0-100%
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n���ŉ�b�����l���̗݌v
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_TALK_COUNT2	ret_wk
	.short	EV_SEQ_UNDERGROUND_TALK_COUNT2
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�q�f���Z�J�n
 */
//-----------------------------------------------------------------------------
	.macro _HIDENEFF_START	eff_no, ret_wk
	.short EV_SEQ_HIDENEFF_START
	.short \eff_no
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�n�k�J�n
 */
//-----------------------------------------------------------------------------
	.macro _ZISHIN	no
	.short EV_SEQ_ZISHIN
	.short	\no
	.endm


//-----------------------------------------------------------------------------
/**
 *	�o�g���|�C���g�E�B���h�E�\��
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_POINT_WIN_WRITE	x,y
	.short	EV_SEQ_BTL_POINT_WIN_WRITE
	.byte	\x
	.byte	\y
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���|�C���g�E�B���h�E�폜
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_POINT_WIN_DEL
	.short	EV_SEQ_BTL_POINT_WIN_DEL
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���|�C���g�E�B���h�E�ĕ`��
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_POINT_WRITE
	.short	EV_SEQ_BTL_POINT_WRITE
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����o�g���|�C���g�擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_BTL_POINT	ret_wk
	.short	EV_SEQ_GET_BTL_POINT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����o�g���|�C���g���Z
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_POINT_ADD	value
	.short	EV_SEQ_BTL_POINT_ADD
	.short	\value
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����o�g���|�C���g���Z
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_POINT_SUB	value
	.short	EV_SEQ_BTL_POINT_SUB
	.short	\value
	.endm

//-----------------------------------------------------------------------------
/**
 *	�����o�g���|�C���g���w��l�Ɣ�r
 */
//-----------------------------------------------------------------------------
	.macro	_COMP_BTL_POINT	value,ret_wk
	.short	EV_SEQ_COMP_BTL_POINT
	.short	\value
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�o�g���|�C���g�ƈ��������\�ȃA�C�e�������擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_BP_GIFT	list_id,item_idx,ret_item,ret_bp
	.short	EV_SEQ_GET_BP_GIFT
	.short	\list_id
	.short	\item_idx
	.short	\ret_item
	.short	\ret_bp
	.endm

//-----------------------------------------------------------------------------
/**
 * �n���p����A�C�e���̃`�F�b�N
 * ���A�C�e���{�[���擾���̐�p����
 */
//-----------------------------------------------------------------------------
	.macro	_UG_BALLITEM_CHECK	item
	.short	EV_SEQ_UG_BALL_CHECK
	.short	\item
	.endm

//-----------------------------------------------------------------------------
/**
 * �A�E�X�̃v���[�g�̃`�F�b�N
 * ���A�C�e���{�[���擾���̐�p����
 */
//-----------------------------------------------------------------------------
	.macro	_AUSU_ITEM_CHECK	item,ret_wk
	.short	EV_SEQ_AUSU_ITEM_CHECK
	.short	\item
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 * 
 */
//-----------------------------------------------------------------------------
	.macro	_CHECK_MY_GSID	ret_wk
	.short	EV_SEQ_CHECK_MY_GSID
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * 
 */
//-----------------------------------------------------------------------------
	.macro	_FRIEND_DATA_NUM	ret_wk
	.short	EV_SEQ_FRIEND_DATA_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�C���ƈ��������\�ȃA�C�e�������擾
 */
//-----------------------------------------------------------------------------
	.macro	_GET_COIN_GIFT	item_idx,ret_item,ret_bp
	.short	EV_SEQ_GET_COIN_GIFT
	.short	\item_idx
	.short	\ret_item
	.short	\ret_bp
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�C�����炷(���[�N��p�Łj
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_WK_COIN		wk
	.short	EV_SEQ_SUB_WK_COIN
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�R�C���𒲂ׂ�i�����������Ă��邩��Ԃ��j�@���[�N��p��
 */
//-----------------------------------------------------------------------------
	.macro	_COMP_WK_COIN ret_wk,wk
	.short	EV_SEQ_COMP_WK_COIN
	.short	\ret_wk
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	�������Ƃ΂��I�N�����m�t���O�L���ɊY�����邩
 */
//-----------------------------------------------------------------------------
	.macro	_AIKOTOBA_OKURIMONO_CHK		ret_wk,wk1,wk2,wk3,wk4
	.short	EV_SEQ_AIKOTOBA_OKURIMONO_CHK
	.short	\ret_wk
	.short	\wk1
	.short	\wk2
	.short	\wk3
	.short	\wk4
	.endm

//-----------------------------------------------------------------------------
/**
 *	WIFI�ӂ����Ȃ�������̃I�[�v���t���O�Z�b�g
 */
//-----------------------------------------------------------------------------
	.macro	_WIFI_HUSIGINAOKURIMONO_OPEN_FLAG_SET
	.short	EV_SEQ_WIFI_HUSIGINAOKURIMONO_OPEN_FLAG_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	���j�I���֘A
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_GET_CARD_TALK_NO ret_wk
	.short	EV_SEQ_UNION_GET_CARD_TALK_NO
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *		WirelessIconEasy�֐��Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_WIRELESS_ICON_EASY
	.short	EV_SEQ_WIRELESS_ICON_EASY
	.endm

//-----------------------------------------------------------------------------
/**
 *		WirelessIconEasyEnd�֐��Ăяo��
 */
//-----------------------------------------------------------------------------
	.macro	_WIRELESS_ICON_EASY_END
	.short	EV_SEQ_WIRELESS_ICON_EASY_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	��l���̈ʒu�𐳂����L�^���邽�߂Ƀt�B�[���h����SAVEDATA�ɔ��f������
 */
//-----------------------------------------------------------------------------
	.macro	_SAVE_FIELD_OBJ
	.short	EV_SEQ_SAVE_FIELD_OBJ
	.endm

//-----------------------------------------------------------------------------
/**
 *	�V�[���̖��O
 *	@param	idx			�Z�b�g����WORDSET�̈ʒu
 *	@param	itemno		�V�[���̎w��
 */
//-----------------------------------------------------------------------------
	.macro	_SEAL_NAME	idx, sealno
	.short	EV_SEQ_SEAL_NAME
	.byte	\idx
	.short	\sealno
	.endm

//-----------------------------------------------------------------------------
/**
 *	�G�X�P�[�v���P�[�V�����𒼐ڏ���������
 */
//-----------------------------------------------------------------------------
	.macro	_SET_ESCAPE_LOCATION	zone_id,grid_x,grid_z	
	.short	EV_SEQ_SET_ESCAPE_LOCATION
	.short	\zone_id
	.short	\grid_x
	.short	\grid_z
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ���m�̓����蔻��t���O��ݒ�
 */
//-----------------------------------------------------------------------------
	.macro	_FIELDOBJ_BITSET_FELLOWHIT	obj_id,flag
	.short	EV_SEQ_FIELDOBJ_BITSET_FELLOWHIT
	.short	\obj_id
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *�@�_���^�}�S�`�F�b�N�S�̔�(�莝���ɂ���:TRUE,���Ȃ�:FALSE)
 */
//-----------------------------------------------------------------------------
	.macro	_DAME_TAMAGO_CHK_ALL ret_wk
	.short	EV_SEQ_DAME_TAMAGO_CHK_ALL
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *�@���j�I�����[���pBMPLIST�i�ʐM�f�[�^��M�ɂ��L�����Z�����ł���j
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_BMPMENU_START
	.short	EV_SEQ_UNION_BMPMENU_START
	.endm
	

//-----------------------------------------------------------------------------
/**
 *�@���j�I�����[���퓬�p�J�n�O�|�P�������X�g�I�����ʎ擾
 */
//-----------------------------------------------------------------------------
	.macro  _UNION_BATTLE_START_CHECK ret_wk
	.short  EV_SEQ_UNION_BATTLE_START_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h�����N�擾
 */
//-----------------------------------------------------------------------------
	.macro  _GET_TRCARD_RANK ret_wk
	.short  EV_SEQ_GET_TRCARD_RANK 
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_FLD_SCOPE_MODE_ON
	.short	EV_SEQ_FIELD_SCOPE_MODE_SET
	.byte	TRUE
	.endm


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	.macro	_FLD_SCOPE_MODE_OFF
	.short	EV_SEQ_FIELD_SCOPE_MODE_SET
	.byte	FALSE
	.endm



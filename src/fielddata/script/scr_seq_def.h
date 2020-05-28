//=============================================================================
/**
 * @file	scr_seq_def.def
 * @bfief	スクリプトコマンドのマクロ定義ファイル
 * @author	HisashiSogabe
 * @date	2005.05.24
 *
 * 05.08.04 Satoshi Nohara
 *
 * 技シーケンス用のマクロ定義ファイルを元にしている
 */
//=============================================================================
#define	__ASM_NO_DEF_

//スクリプトで使用するヘッダーファイル
	.include	"usescript.h"

//データを自然な境界にアラインするかの設定
	.option alignment off

	.macro	INIT_CMD
DEF_CMD_COUNT	=	0
	.endm
		
	.macro	DEF_CMD	symname
\symname	=	DEF_CMD_COUNT
DEF_CMD_COUNT	=	( DEF_CMD_COUNT + 1 )
	.endm

//命令シンボル宣言
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

	DEF_CMD	EV_SEQ_MENU_REQ			// メニューリクエスト
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

	DEF_CMD	EV_SEQ_ADD_GOLD				//お金関連すべて
	DEF_CMD	EV_SEQ_SUB_GOLD
	DEF_CMD	EV_SEQ_COMP_GOLD
	DEF_CMD	EV_SEQ_GOLD_WIN_WRITE
	DEF_CMD	EV_SEQ_GOLD_WIN_DEL
	DEF_CMD	EV_SEQ_GOLD_WRITE			//お金関連ここまで

	DEF_CMD	EV_SEQ_COIN_WIN_WRITE		//コイン関連すべて
	DEF_CMD	EV_SEQ_COIN_WIN_DEL			
	DEF_CMD	EV_SEQ_COIN_WRITE
	DEF_CMD	EV_SEQ_GET_COIN_NUM
	DEF_CMD	EV_SEQ_ADD_COIN
	DEF_CMD	EV_SEQ_SUB_COIN				//コイン関連ここまで

	DEF_CMD	EV_SEQ_ADD_ITEM
	DEF_CMD	EV_SEQ_SUB_ITEM
	DEF_CMD	EV_SEQ_ADD_ITEM_CHK
	DEF_CMD	EV_SEQ_ITEM_CHK
	DEF_CMD	EV_SEQ_WAZA_ITEM_CHK

	DEF_CMD	EV_SEQ_GET_POCKET_NO
	DEF_CMD	EV_SEQ_ADD_BOX_ITEM			//使用せず060630
	DEF_CMD	EV_SEQ_CHK_BOX_ITEM			//使用せず060630

	DEF_CMD	EV_SEQ_ADD_GOODS			//グッズ関連すべて			作成中060602
	DEF_CMD	EV_SEQ_SUB_GOODS
	DEF_CMD	EV_SEQ_ADD_GOODS_CHK
	DEF_CMD	EV_SEQ_GOODS_CHK			//グッズ関連ここまで

	DEF_CMD	EV_SEQ_ADD_TRAP				//トラップ関連すべて
	DEF_CMD	EV_SEQ_SUB_TRAP
	DEF_CMD	EV_SEQ_ADD_TRAP_CHK
	DEF_CMD	EV_SEQ_TRAP_CHK				//トラップ関連ここまで

	DEF_CMD	EV_SEQ_ADD_TREASURE			//お宝
	DEF_CMD	EV_SEQ_SUB_TREASURE
	DEF_CMD	EV_SEQ_ADD_TREASURE_CHK
	DEF_CMD	EV_SEQ_TREASURE_CHK			//お宝関連ここまで

	DEF_CMD	EV_SEQ_ADD_TAMA				//タマ関連すべて
	DEF_CMD	EV_SEQ_SUB_TAMA
	DEF_CMD	EV_SEQ_ADD_TAMA_CHK
	DEF_CMD	EV_SEQ_TAMA_CHK				//タマ関連ここまで

	DEF_CMD	EV_SEQ_CB_ITEM_NUM_GET
	DEF_CMD	EV_SEQ_CB_ITEM_NUM_ADD
	DEF_CMD	EV_SEQ_UNKNOWN_FORM_GET

	DEF_CMD	EV_SEQ_ADD_POKEMON			//ポケモン関連すべて
	DEF_CMD	EV_SEQ_ADD_TAMAGO
	DEF_CMD	EV_SEQ_CHG_POKE_WAZA
	DEF_CMD	EV_SEQ_CHK_POKE_WAZA
	DEF_CMD	EV_SEQ_CHK_POKE_WAZA_GROUP		//ポケモン関連ここまで

	DEF_CMD	EV_SEQ_REVENGE_TRAINER_SEARCH

	DEF_CMD	EV_SEQ_INIT_WEATHER			//天候関連すべて			未対応
	DEF_CMD	EV_SEQ_SET_WEATHER
	DEF_CMD	EV_SEQ_UPDATE_WEATHER		//天候関連ここまで

	DEF_CMD	EV_SEQ_GET_MAP_POS			//現在のマップ位置を取得	未対応
	DEF_CMD	EV_SEQ_GET_TEMOTI_POKE_NUM	//手持ちのポケモン数を取得	未対応 ※別命令が既にありいらない060224tomo

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

	DEF_CMD	EV_SEQ_INIT_WATER_GYM			//水ジム初期化
	DEF_CMD EV_SEQ_PUSH_WATER_GYM_BUTTON	//水ジムボタンプッシュ

	DEF_CMD	EV_SEQ_INIT_GHOST_GYM			//ゴーストジム初期化
	DEF_CMD EV_SEQ_MOVE_GHOST_GYM_LIFT		//ゴーストジムリフトムーブ
	DEF_CMD EV_SEQ_INIT_STEEL_GYM			//鋼ジム初期化
	DEF_CMD EV_SEQ_INIT_COMBAT_GYM			//格闘ジム初期化
	DEF_CMD EV_SEQ_INIT_ELEC_GYM			//電気ジム初期化
	DEF_CMD EV_SEQ_ROT_ELEC_GYM_GEAR		//電気ジムギア回転

	DEF_CMD EV_SEQ_GET_POKE_COUNT			//ポケモン数取得

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

	DEF_CMD EV_SEQ_GET_POKE_COUNT2			//ポケモン数取得(タマゴを除く)
	DEF_CMD EV_SEQ_GET_POKE_COUNT3			//ポケモン数取得(タマゴと瀕死を除く)
	DEF_CMD EV_SEQ_GET_POKE_COUNT4			//ポケモン数取得(手持ち＆ＰＣを含めて戦えるポケモンが何体いるか)
	DEF_CMD EV_SEQ_GET_TAMAGO_COUNT			//タマゴ数取得（ダメたまご含まず）

	DEF_CMD EV_SEQ_UG_SHOP_MENU_INIT		//地下のお店のメニューを開く
	DEF_CMD EV_SEQ_UG_SHOP_TALK_START		//地下のお店の会話開始
	DEF_CMD EV_SEQ_UG_SHOP_TALK_END			//地下のお店の会話終了
	DEF_CMD EV_SEQ_UG_SHOP_ITEM_NAME		//地下のお店のアイテムの名前を登録
	DEF_CMD EV_SEQ_UG_SHOP_TRAP_NAME		//地下のお店のトラップの名前を登録

	DEF_CMD EV_SEQ_SUB_MY_GOLD				//お金を引く（ワーク版）
	DEF_CMD EV_SEQ_HIKITORI_POKE			//そだてやからポケモンを引き取る
	DEF_CMD EV_SEQ_HIKITORI_LIST			//２体のポケモンの引き取り選択ウインドウ（そだてや）
	DEF_CMD EV_SEQ_MSG_SODATEYA_AISHOU		//相性メッセージセット
	DEF_CMD EV_SEQ_MSGEXPANDBUF				//メッセージを出す
	DEF_CMD EV_SEQ_DEL_SODATEYA_EGG			//発見されたタマゴの受け取り拒否
	DEF_CMD EV_SEQ_GET_SODATEYA_EGG			//発見されたタマゴを受け取る
	DEF_CMD EV_SEQ_HIKITORI_RYOUKIN			//ひきとり料金セット
	DEF_CMD EV_SEQ_COMP_MY_GOLD				//お金を比較（ワーク版）
	DEF_CMD EV_SEQ_TAMAGO_DEMO				//タマゴ孵化デモ
	DEF_CMD EV_SEQ_SODATEYA_POKELIST		//そだてやポケモンリスト
	DEF_CMD EV_SEQ_SODATE_POKE_LEVEL_STR	//レベル差を文字列で取得
	DEF_CMD EV_SEQ_MSG_AZUKE_SET			//預けるポケモン名セット＋番号取得
	DEF_CMD EV_SEQ_SET_SODATEYA_POKE		//ポケモンを預ける
	DEF_CMD EV_SEQ_OBJ_VISIBLE				//キャラを可視状態へ
	DEF_CMD EV_SEQ_OBJ_INVISIBLE			//キャラを不可視状態へ
	DEF_CMD	EV_SEQ_MAILBOX					//メールボックス
	DEF_CMD	EV_SEQ_GET_MAILBOX_DATANUM		//メールボックス内のデータ数取得
	DEF_CMD	EV_SEQ_RANKING_VIEW				//ギネスホールランキング画面呼び出し

	DEF_CMD	EV_SEQ_GET_TIME_ZONE			//時間帯取得
	DEF_CMD	EV_SEQ_GET_RND					//ランダム数取得
	DEF_CMD	EV_SEQ_GET_RND_NEXT				//ランダム数取得

	DEF_CMD	EV_SEQ_GET_NATSUKI				//なつき度取得
	DEF_CMD	EV_SEQ_ADD_NATSUKI				//なつき度を増やす
	DEF_CMD	EV_SEQ_SUB_NATSUKI				//なつき度を減らす

	DEF_CMD EV_SEQ_HIKITORI_NAME_SET		//ひきとり２体の名前セット

	DEF_CMD	EV_SEQ_PLAYER_DIR_GET			//自機の方向取得

	DEF_CMD	EV_SEQ_GET_SODATEYA_AISHOU		//そだてや2体の相性ゲット
	DEF_CMD	EV_SEQ_SODATEYA_TAMAGO_CHK	//タマゴが産まれているかチェック

	DEF_CMD	EV_SEQ_TEMOTI_POKE_CHK			//手持ちに特定のポケモンがいるかをチェック
	DEF_CMD	EV_SEQ_OOKISA_RECORD_CHK		//記録と手持ちポケモンの比較
	DEF_CMD	EV_SEQ_OOKISA_RECORD_SET		//手持ちのポケモンで記録更新
	DEF_CMD	EV_SEQ_OOKISA_TEMOTI_SET_BUF	//手持ちのポケモンの大きさを数値にして文字バッファへセット
	DEF_CMD	EV_SEQ_OOKISA_KIROKU_SET_BUF	//記録ポケモンの大きさを数値にして文字バッファへセット
	DEF_CMD	EV_SEQ_OOKISA_KURABE_INIT		//大きさ比べ初期化

	DEF_CMD	EV_SEQ_WAZALIST_SET_PROC		//ワザ選択画面呼び出し
	DEF_CMD	EV_SEQ_WAZALIST_GET_RESULT		//ワザ選択画面結果取り出し
	DEF_CMD	EV_SEQ_WAZA_COUNT				//持っているワザ数をカウント
	DEF_CMD	EV_SEQ_WAZA_DEL					//ワザを消す
	DEF_CMD	EV_SEQ_TEMOTI_WAZANO			//手持ちのワザの番号取得
	DEF_CMD	EV_SEQ_TEMOTI_WAZA_NAME			//手持ちワザ名をバッファへ

	DEF_CMD	EV_SEQ_FNOTE_START_SET			//冒険ノート開始データセット
	DEF_CMD	EV_SEQ_FNOTE_DATA_MAKE			//冒険ノートデータ作成
	DEF_CMD	EV_SEQ_FNOTE_DATA_SAVE			//冒険ノートデータセーブ

	DEF_CMD	EV_SEQ_SYS_FLAG_KAIRIKI
	DEF_CMD EV_SEQ_SYS_FLAG_FLASH
	DEF_CMD EV_SEQ_SYS_FLAG_KIRIBARAI

	DEF_CMD	EV_SEQ_IMC_ACCE_ADD_ITEM
	DEF_CMD	EV_SEQ_IMC_ACCE_ADD_ITEM_CHK
	DEF_CMD	EV_SEQ_IMC_ACCE_ITEM_CHK
	DEF_CMD	EV_SEQ_IMC_BG_ADD_ITEM
	DEF_CMD	EV_SEQ_IMC_BG_ITEM_CHK
	
	DEF_CMD	EV_SEQ_NUTMIXER_CALL			//まぜまぜ料理呼び出し
	DEF_CMD	EV_SEQ_NUTMIXER_PLAY_CHECK		//まぜまぜ料理プレイができるかチェック
	
	DEF_CMD	EV_SEQ_BTOWER_APP_CALL			//バトルタワーアプリケーションコール
	
	//ここからバトルタワー
	DEF_CMD	EV_SEQ_BATTLE_TOWER_WORK_CLEAR		//バトルタワーワーク初期化
	DEF_CMD	EV_SEQ_BATTLE_TOWER_WORK_INIT		//バトルタワーワーク確保
	DEF_CMD	EV_SEQ_BATTLE_TOWER_WORK_RELEASE	//バトルタワーワーク解放
	DEF_CMD	EV_SEQ_BATTLE_TOWER_TOOLS			//バトルタワーツール
	DEF_CMD	EV_SEQ_BATTLE_TOWER_GET_SEVEN_POKE	//5人衆のポケモンデータゲット
	DEF_CMD	EV_SEQ_BATTLE_TOWER_IS_PRIZE_GET	//バトルタワー　プライズ取得
	DEF_CMD	EV_SEQ_BATTLE_TOWER_IS_PRIZEMAN_SET	//バトルタワー　プライズをくれるヒト
	DEF_CMD	EV_SEQ_BATTLE_TOWER_SEND_BUF		//バトルタワー　汎用データ送信
	DEF_CMD	EV_SEQ_BATTLE_TOWER_RECV_BUF		//バトルタワー　汎用データ受信
	DEF_CMD	EV_SEQ_BATTLE_TOWER_GET_LEADER_ROOM_ID	//バトルタワー　リーダーデータのRoomID取得
	DEF_CMD	EV_SEQ_BATTLE_TOWER_IS_READER_DATA_EXIST	//バトルタワー　リーダーデータの有無
	
	//↑ここまでバトルタワー
	DEF_CMD	EV_SEQ_RECORD_INC					//レコードインクリメント
	DEF_CMD	EV_SEQ_RECORD_GET					//レコードゲット
	DEF_CMD	EV_SEQ_RECORD_SET					//レコードセット
	

	DEF_CMD	EV_SEQ_ZUKAN_CHK_SHINOU				//シンオウ図鑑が完成しているかチェック
	DEF_CMD	EV_SEQ_ZUKAN_CHK_NATIONAL			//全国図鑑が完成しているかチェック
	DEF_CMD	EV_SEQ_ZUKAN_RECONGNIZE_SHINOU		//シンオウ図鑑”ひょうしょう”
	DEF_CMD	EV_SEQ_ZUKAN_RECONGNIZE_NATIONAL	//全国図鑑”ひょうしょう”

	DEF_CMD	EV_SEQ_URAYAMA_ENCOUNT_SET			//ウラヤマエンカウントセット
	DEF_CMD	EV_SEQ_URAYAMA_ENCOUNT_NO_CHK		//ウラヤマエンカウントチェック（現在の該当するポケモン番号取得）

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

	DEF_CMD	EV_SEQ_OSHIE_WAZA_COUNT					/*仕様変更により未完成*/
	DEF_CMD	EV_SEQ_REMAIND_WAZA_COUNT
	DEF_CMD	EV_SEQ_OSHIE_WAZALIST_SET_PROC			/*仕様変更により未完成*/
	DEF_CMD	EV_SEQ_REMAIND_WAZALIST_SET_PROC
	DEF_CMD	EV_SEQ_OSHIE_WAZALIST_GET_RESULT		/*仕様変更により未完成*/
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

	DEF_CMD EV_SEQ_PARTY_MONSNO_CHECK			// パーティに引数１のポケモンがいるかチェック
	DEF_CMD EV_SEQ_PARTY_DEOKISISUFORM_CHANGE	// パーティ内のデオキシスのフォルムを変更
	DEF_CMD EV_SEQ_CHECKMINOMUCHICOMP	// ミノムッチ3種そろったか

	DEF_CMD EV_SEQ_POKETCH_HOOK_SET
	DEF_CMD EV_SEQ_POKETCH_HOOK_RESET

	DEF_CMD	EV_SEQ_SLOT_MACHINE

	DEF_CMD	EV_SEQ_GET_NOW_HOUR
	
	DEF_CMD	EV_SEQ_FLDOBJ_SHAKE_ANM		//フィールドOBJを揺らすアニメ
	DEF_CMD	EV_SEQ_FLDOBJ_BLINK_ANM		//フィールドOBJをBlinkさせるアニメ
	DEF_CMD	EV_SEQ_D20R0106_LEGEND_IS_UNSEAL	//レジキング解放チェック

	DEF_CMD	EV_SEQ_DRESSING_IMC_ACCE_CHECK
	DEF_CMD	EV_SEQ_UNKNOWN_MSG
	DEF_CMD	EV_SEQ_AGB_CARTRIDGE_VER_GET	// ささっているAGBカートリッジVer取得

	DEF_CMD	EV_SEQ_UNDERGROUND_TALK_COUNT_CLEAR		//会話したカウントをクリア(カナメ戦闘用）

	DEF_CMD	EV_SEQ_HIDEMAP_STATE_CHANGE		//隠しマップステータスチェンジ
	DEF_CMD	EV_SEQ_NAMEIN_MONUMENT			//r224石碑名入力
	DEF_CMD	EV_SEQ_MONUMENT_NAME			//r224石碑名タグ展開

	DEF_CMD EV_SEQ_IMC_BG_NAME_SET			// imcの背景名を設定
	DEF_CMD	EV_SEQ_COMP_COIN
	DEF_CMD	EV_SEQ_SLOT_RENTYAN_CHK			//スロットでレンチャンしているか
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
	DEF_CMD EV_SEQ_NUMBER_NAME_EX			//数値タグ展開　ディスプレイモード指定ver
	DEF_CMD EV_SEQ_TEMOTI_POKE_CONTEST_STATUS_GET

	DEF_CMD	EV_SEQ_BIRTH_DAY_CHECK
	DEF_CMD	EV_SEQ_SND_INITIAL_VOL_SET
	DEF_CMD	EV_SEQ_ANOON_SEE_NUM
	DEF_CMD EV_SEQ_D17SYSTEM_MAP_SELECT		//D17戻らずの洞窟　マップ抽選
	DEF_CMD EV_SEQ_UNDERGROUND_TOOL_GIVE_COUNT
	DEF_CMD EV_SEQ_UNDERGROUND_KASEKI_DIG_COUNT
	DEF_CMD EV_SEQ_UNDERGROUND_TRAP_HIT_COUNT
	DEF_CMD	EV_SEQ_POFIN_ADD
	DEF_CMD	EV_SEQ_POFIN_ADD_CHK

	DEF_CMD	EV_SEQ_IS_HAIHU_EVENT_ENABLE	//配布イベント有効チェック

	DEF_CMD	EV_SEQ_POKE_WINDOW_PUT_PP
	DEF_CMD	EV_SEQ_POKE_WINDOW_ANM
	DEF_CMD	EV_SEQ_POKE_WINDOW_ANM_WAIT
	DEF_CMD	EV_SEQ_DENDOU_NUM_GET

	DEF_CMD	EV_SEQ_SODATEYA_POKELIST_SET_PROC
	DEF_CMD	EV_SEQ_SODATEYA_POKELIST_GET_RESULT
	
	DEF_CMD	EV_SEQ_GET_RANDOM_HIT	//指定した確立でTRUE,FALSEを返す

	DEF_CMD	EV_SEQ_UNDERGROUND_TALK_COUNT2

	//バトルポイント関連ここから
	DEF_CMD	EV_SEQ_BTL_POINT_WIN_WRITE
	DEF_CMD	EV_SEQ_BTL_POINT_WIN_DEL
	DEF_CMD	EV_SEQ_BTL_POINT_WRITE
	DEF_CMD	EV_SEQ_GET_BTL_POINT
	DEF_CMD	EV_SEQ_BTL_POINT_ADD
	DEF_CMD	EV_SEQ_BTL_POINT_SUB
	DEF_CMD	EV_SEQ_COMP_BTL_POINT
	DEF_CMD	EV_SEQ_GET_BP_GIFT
	//バトルポイント関連ここまで
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
 *	基本コマンド
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	何もしない
 */
//-----------------------------------------------------------------------------
	.macro	_NOP
	.short	EV_SEQ_NOP
	.endm

//-----------------------------------------------------------------------------
/**
 *	ダミー
 */
//-----------------------------------------------------------------------------
	.macro	_DUMMY
	.short	EV_SEQ_DUMMY
	.endm

//-----------------------------------------------------------------------------
/**
 *	スクリプトの終了
 */
//-----------------------------------------------------------------------------
	.macro	_END
	.short	EV_SEQ_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	ウェイト
 */
//-----------------------------------------------------------------------------
	.macro	_TIME_WAIT time,ret_wk
	.short	EV_SEQ_TIME_WAIT
	.short	\time
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	データロード・ストア関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタに1byteの値を格納
 */
//-----------------------------------------------------------------------------
	.macro	_LD_REG_VAL	r,val
	.short	EV_SEQ_LD_REG_VAL
	.byte	\r
	.byte	\val
	.endm

//-----------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタに4byteの値を格納
 */
//-----------------------------------------------------------------------------
	.macro	_LD_REG_WDATA	r,wdata
	.short	EV_SEQ_LD_REG_WDATA
	.byte	\r
	.long	\wdata
	.endm

//-----------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタにアドレスを格納
 */
//-----------------------------------------------------------------------------
	.macro	_LD_REG_ADR	reg,ADDRESS
	.short	EV_SEQ_LD_REG_ADR
	.byte	\reg
	.long	\ADDRESS
	.endm

//-----------------------------------------------------------------------------
/**
 * アドレスの中身に値を代入
 */
//-----------------------------------------------------------------------------
	.macro	_LD_ADR_VAL	adrs,val
	.short	EV_SEQ_LD_ADR_VAL
	.long	\adrs
	.byte	\val
	.endm

//-----------------------------------------------------------------------------
/**
 * アドレスの中身に仮想マシンの汎用レジスタの値を代入
 */
//-----------------------------------------------------------------------------
	.macro	_LD_ADR_REG	adrs,reg
	.short	EV_SEQ_LD_ADR_REG
	.long	\adrs
	.byte	\reg
	.endm

//-----------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタの値を汎用レジスタにコピー
 */
//-----------------------------------------------------------------------------
	.macro	_LD_REG_REG	r1,r2
	.short	EV_SEQ_LD_REG_REG
	.byte	\r1,\r2
	.endm

//-----------------------------------------------------------------------------
/**
 * アドレスの中身にアドレスの中身を代入
 */
//-----------------------------------------------------------------------------
	.macro	_LD_ADR_ADR	adr1,adr2
	.short	EV_SEQ_LD_ADR_ADR
	.long	\adr1
	.long	\adr2
	.endm


//=============================================================================
/**
 *	比較関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	仮想マシンの汎用レジスタを比較
 */
//-----------------------------------------------------------------------------
	.macro	_CP_REG_REG	r1,r2
	.short	EV_SEQ_CP_REG_REG
	.byte	\r1,\r2
	.endm

//-----------------------------------------------------------------------------
/**
 *	仮想マシンの汎用レジスタと値を比較
 */
//-----------------------------------------------------------------------------
	.macro	_CP_REG_VAL	r1,val
	.short	EV_SEQ_CP_REG_VAL
	.byte	\r1,\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	仮想マシンの汎用レジスタとアドレスの中身を比較
 */
//-----------------------------------------------------------------------------
	.macro	_CP_REG_ADR	r1,adrs
	.short	EV_SEQ_CP_REG_ADR
	.byte	\r1
	.long	\adrs
	.endm

//-----------------------------------------------------------------------------
/**
 *	アドレスの中身と仮想マシンの汎用レジスタを比較
 */
//-----------------------------------------------------------------------------
	.macro	_CP_ADR_REG	adrs,r1
	.short	EV_SEQ_CP_ADR_REG
	.long	\adrs
	.byte	\r1
	.endm

//-----------------------------------------------------------------------------
/**
 *	アドレスの中身と値を比較
 */
//-----------------------------------------------------------------------------
	.macro	_CP_ADR_VAL	adrs,val
	.short	EV_SEQ_CP_ADR_VAL
	.long	\adrs
	.byte	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	アドレスの中身とアドレスの中身を比較
 */
//-----------------------------------------------------------------------------
	.macro	_CP_ADR_ADR	adr1,adr2
	.short	EV_SEQ_CP_ADR_ADR
	.long	\adr1
	.long	\adr2
	.endm

//-----------------------------------------------------------------------------
/**
 *	ワークと値の比較
 */
//-----------------------------------------------------------------------------
	.macro	_CMPVAL	wk,val
	.short	EV_SEQ_CP_WK_VAL
	.short	\wk
	.short	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	ワークとワークの比較
 */
//-----------------------------------------------------------------------------
	.macro	_CMPWK	wk1,wk2
	.short	EV_SEQ_CP_WK_WK
	.short	\wk1
	.short	\wk2
	.endm

//-----------------------------------------------------------------------------
/**
 * デバッグ用：ワーク情報表示
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_WATCH_WORK	wk
	.short	EV_SEQ_DEBUG_WATCH_VALUE
	.short	\wk
	.endm

//=============================================================================
/**
 *	仮想マシン関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	仮想マシン追加(切り替えはせず、並列で動作します！)
 */
//-----------------------------------------------------------------------------
	.macro	_VM_ADD id
	.short	EV_SEQ_VM_ADD
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 * ローカルスクリプトをウェイト状態にして、共通スクリプトを動作させます
 */
//-----------------------------------------------------------------------------
	.macro	_CHG_COMMON_SCR id
	.short	EV_SEQ_CHG_COMMON_SCR
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	共通スクリプトを終了して、ローカルスクリプトを再開させます
 */
//-----------------------------------------------------------------------------
	.macro	_CHG_LOCAL_SCR
	.short	EV_SEQ_CHG_LOCAL_SCR
	.endm


//=============================================================================
/**
 *	ジャンプ関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	ジャンプ
 */
//-----------------------------------------------------------------------------
	.macro	_JUMP adrs
	.short	EV_SEQ_JUMP
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ_ID　ジャンプ
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_ID_JUMP act,adrs
	.short	EV_SEQ_OBJ_ID_JUMP
	.byte	\act
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	BG_ID　ジャンプ
 */
//-----------------------------------------------------------------------------
	.macro	_BG_ID_JUMP act,adrs
	.short	EV_SEQ_BG_ID_JUMP
	.byte	\act
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	イベント起動時の主人公の向き比較ジャンプ
 *	(現在の向きではないので注意！)
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_DIR_JUMP dir,adrs
	.short	EV_SEQ_PLAYER_DIR_JUMP
	.byte	\dir
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	コール
 */
//-----------------------------------------------------------------------------
	.macro	_CALL adrs
	.short	EV_SEQ_CALL
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	コールを呼び出したアドレスに戻る
 */
//-----------------------------------------------------------------------------
	.macro	_RET
	.short	EV_SEQ_RET
	.endm

//-----------------------------------------------------------------------------
/**
 *	IFジャンプ
 */
//-----------------------------------------------------------------------------
	.macro	_IF_JUMP cond,adrs
	.short	EV_SEQ_IF_JUMP
	.byte	\cond
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	IFコール
 */
//-----------------------------------------------------------------------------
	.macro	_IF_CALL cond,adrs
	.short	EV_SEQ_IF_CALL
	.byte	\cond
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	値を比較、条件どおりの場合分岐(ジャンプ)
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
 *	値を比較、条件どおりの場合分岐(コール)
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
 *	ワークを比較、条件どおりの場合分岐(ジャンプ)
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
 *	ワークを比較、条件どおりの場合分岐(コール)
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
 *	switch関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	switch ～ case 構文
 *
 *  スクリプト制御ワークで確保されるワーク(SCWK_REG0)を使用しているので、
 *	FLAG_CHANGE,INIT_CHANGEなどでは使用できません！
 *	SCENE_CHANGEは使用できます。
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
 * スクリプトウィンドウ表示中にBキャンセル
 */
//-----------------------------------------------------------------------------
	.macro	_CASE_CANCEL	adr
	_CMPVAL	SCWK_REG0,EV_WIN_B_CANCEL
	_IF_JUMP	EQ,\adr
	.endm

//-----------------------------------------------------------------------------
/**
 *	待機アイコン表示
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_WAITICON
	.short	EV_SEQ_WAITICON_ADD
	.endm

//-----------------------------------------------------------------------------
/**
 *	待機アイコン消去
 */
//-----------------------------------------------------------------------------
	.macro	_DEL_WAITICON
	.short	EV_SEQ_WAITICON_DEL
	.endm

//=============================================================================
/**
 *	イベントフラグ関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	フラグのセット
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_SET num
	.short	EV_SEQ_FLAG_SET
	.short	\num
	.endm

	//到着フラグセット
	.macro	_ARRIVE_FLAG_SET num
	_FLAG_SET	(\num + SYS_FLAG_ARRIVE_START)
	.endm

//-----------------------------------------------------------------------------
/**
 *	フラグのリセット
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_RESET num
	.short	EV_SEQ_FLAG_RESET
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	フラグチェック
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_CHECK num
	.short	EV_SEQ_FLAG_CHECK
	.short	\num
	.endm

	//フラグONの時に分岐(JUMP)
	.macro	_IF_FLAGON_JUMP num,adrs
	_FLAG_CHECK \num
	_IF_JUMP	FLGON,\adrs
	.endm

	//フラグOFFの時に分岐(JUMP)
	.macro	_IF_FLAGOFF_JUMP num,adrs
	_FLAG_CHECK \num
	_IF_JUMP	FLGOFF,\adrs
	.endm

	//フラグONの時に分岐(CALL)
	.macro	_IF_FLAGON_CALL num,adrs
	_FLAG_CHECK \num
	_IF_CALL	FLGON,\adrs
	.endm

	//フラグOFFの時に分岐(CALL)
	.macro	_IF_FLAGOFF_CALL num,adrs
	_FLAG_CHECK \num
	_IF_CALL	FLGOFF,\adrs
	.endm

//-----------------------------------------------------------------------------
/**
 * ワークの値をフラグナンバーとしてチェックする！
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_CHECK_WK wk,ret_wk
	.short	EV_SEQ_FLAG_CHECK_WK
	.short	\wk
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ワークの値をフラグナンバーとしてセットする！
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_SET_WK wk
	.short	EV_SEQ_FLAG_SET_WK
	.short	\wk
	.endm


//=============================================================================
/**
 *	トレーナーフラグ関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	トレーナーフラグのセット
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_FLAG_SET tr_id
	.short	EV_SEQ_TRAINER_FLAG_SET
	.short	\tr_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	トレーナーフラグのリセット
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_FLAG_RESET tr_id
	.short	EV_SEQ_TRAINER_FLAG_RESET
	.short	\tr_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	トレーナーフラグチェック
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_FLAG_CHECK tr_id
	.short	EV_SEQ_TRAINER_FLAG_CHECK
	.short	\tr_id
	.endm

	//フラグONの時に分岐(JUMP)
	.macro	_IF_TR_FLAGON_JUMP tr_id,adrs
	_TRAINER_FLAG_CHECK \tr_id
	_IF_JUMP	FLGON,\adrs
	.endm

	//フラグOFFの時に分岐(JUMP)
	.macro	_IF_TR_FLAGOFF_JUMP tr_id,adrs
	_TRAINER_FLAG_CHECK \tr_id
	_IF_JUMP	FLGOFF,\adrs
	.endm

	//フラグONの時に分岐(CALL)
	.macro	_IF_TR_FLAGON_CALL tr_id,adrs
	_TRAINER_FLAG_CHECK \tr_id
	_IF_CALL	FLGON,\adrs
	.endm

	//フラグOFFの時に分岐(CALL)
	.macro	_IF_TR_FLAGOFF_CALL tr_id,adrs
	_TRAINER_FLAG_CHECK \tr_id
	_IF_CALL	FLGOFF,\adrs
	.endm


//=============================================================================
/**
 *	ワーク操作関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	ワークに値を足す
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_WK wk,num
	.short	EV_SEQ_ADD_WK
	.short	\wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	ワークから値を引く
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_WK wk,num
	.short	EV_SEQ_SUB_WK
	.short	\wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	ワークに値を代入
 */
//-----------------------------------------------------------------------------
	.macro	_LDVAL	wk,val
	.short	EV_SEQ_LD_WK_VAL
	.short	\wk
	.short	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	ワークにワークの値を代入
 */
//-----------------------------------------------------------------------------
	.macro	_LDWK	wk1,wk2
	.short	EV_SEQ_LD_WK_WK
	.short	\wk1
	.short	\wk2
	.endm

//-----------------------------------------------------------------------------
/**
 *	ワークに値かワークの値を代入
 */
//-----------------------------------------------------------------------------
	.macro	_LDWKVAL	wk1,wk2
	.short	EV_SEQ_LD_WK_WKVAL
	.short	\wk1
	.short	\wk2
	.endm


//=============================================================================
/**
 *	会話関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	展開メッセージを表示(1byte)
 *
 *	@param	msg_id	表示するメッセージID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_ALLPUT msg_id
	.short	EV_SEQ_MSG_ALLPUT
	.byte	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	展開メッセージを表示(msg_id=work指定有,arc_id=work指定有)
 *
 *	@param	msg_id	表示するメッセージID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_ALLPUT_ARC	arc_id, msg_id
	.short	EV_SEQ_MSG_ALLPUT_ARC
	.short	\arc_id
	.short	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	展開メッセージを表示(msg_id=work指定有,arc_id=work指定有)
 *  @param	arc_id	表示するメッセージアーカイブID
 *	@param	msg_id	表示するメッセージID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_ARC	arc_id, msg_id
	.short	EV_SEQ_MSG_ARC
	.short	\arc_id
	.short	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	簡易会話メッセージを表示(stype=2byte,sid=2byte)
 *  @param	stype	簡易会話の文章タイプ
 *  @param	sid		簡易会話の文章タイプ内ID
 *	@param	word0	単語コード0
 *	@param	word1	単語コード1
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
 *	簡易会話メッセージを表示(stype=2byte,sid=2byte)
 *  @param	stype	簡易会話の文章タイプ
 *  @param	sid		簡易会話の文章タイプ内ID
 *	@param	word0	単語コード0
 *	@param	word1	単語コード1
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
 *	タワー対戦前メッセージを表示(tr_idx)
 *  @param	tr_idx	一人目か二人目か？
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_BTOWER_APPEAR	tr_id	
	.short	EV_SEQ_MSG_BTOWER_APPEAR
	.byte	\tr_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	タワー用NGポケモン名展開(見たことある奴だけ)
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
 *	展開メッセージを表示(1byte)
 *
 *	@param	msg_id	表示するメッセージID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG msg_id
	.short	EV_SEQ_MSG
	.byte	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	展開メッセージを表示(特殊：引数にワークを指定できる)
 *
 *	@param	msg_id	表示するメッセージID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_SP msg_id
	.short	EV_SEQ_MSG_SP
	.short	\msg_id
	.endm


//-----------------------------------------------------------------------------
/**
 *	展開メッセージをオートで表示(特殊：引数にワークを指定できる)
 *
 *	@param	msg_id	表示するメッセージID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_SP_AUTO msg_id
	.short	EV_SEQ_MSG_SP_AUTO
	.short	\msg_id
	.endm


//-----------------------------------------------------------------------------
/**
 *	展開メッセージを表示(スキップ不可)
 *
 *	@param	msg_id	表示するメッセージID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_NOSKIP msg_id
	.short	EV_SEQ_MSG_NOSKIP
	.short	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	展開メッセージを表示(コンテスト用、通信、非通信を判定してメッセージ送りの設定を変更)
 *
 *	@param	msg_id	表示するメッセージID
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_CON_SIO msg_id
	.short	EV_SEQ_MSG_CON_SIO
	.byte	\msg_id
	.endm

//-----------------------------------------------------------------------------
/**
 * OBJからメッセージIDを取得して表示
 */
//-----------------------------------------------------------------------------
	.macro	_TALKMSG_AUTOGET
	.short	EV_SEQ_MSG_AUTOGET
	.endm


//-----------------------------------------------------------------------------
/**
 *	キー待ち
 */
//-----------------------------------------------------------------------------
	.macro	_AB_KEYWAIT
	.short	EV_SEQ_ABKEYWAIT
	.endm

//-----------------------------------------------------------------------------
/**
 * キー待ち　OR　時間待ち
 */
//-----------------------------------------------------------------------------
	.macro	_AB_KEY_TIME_WAIT	wait
	.short	EV_SEQ_ABKEY_TIMEWAIT
	.short	\wait
	.endm

//-----------------------------------------------------------------------------
/**
 *	イベントの最後のキー待ち
 *		スタートボタン	スクリプト終了時にメニューが開くリクエストセット
 *		十字キー		主人公の向きを変更
 *		が追加される
 */
//-----------------------------------------------------------------------------
	.macro	_LAST_KEYWAIT
	.short	EV_SEQ_LASTKEYWAIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	イベントの最後のキー待ち(その後にアニメが続く時に使用)
 *		十字キー		メッセージ終了
 *		が追加される
 */
//-----------------------------------------------------------------------------
	.macro	_NEXT_ANM_LAST_KEYWAIT
	.short	EV_SEQ_NEXT_ANM_LASTKEYWAIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	会話ウィンドウ開く
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_OPEN
	.short	EV_SEQ_WIN_OPEN
	.endm

//-----------------------------------------------------------------------------
/**
 *	会話ウィンドウ閉じる
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_CLOSE
	.short	EV_SEQ_WIN_CLOSE
	.endm

//-----------------------------------------------------------------------------
/**
 *	会話ウィンドウ閉じる(クリアなし)
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_CLOSE_NO_CLEAR
	.short	EV_SEQ_WIN_CLOSE_NO_CLEAR
	.endm

//-----------------------------------------------------------------------------
/**
 *	展開メッセージ表示＋キー待ち
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_KEYWAIT msg_id
	_TALKMSG \msg_id
	//_AB_KEYWAIT			//06.04.07 メッセージ送り仕様に合わせて削除
	.endm

//-----------------------------------------------------------------------------
/**
 *	簡易OBJに対して話し掛け
 */
//-----------------------------------------------------------------------------
	.macro	_EASY_OBJ_MSG msg_id
	_TALK_OBJ_START
	//_TALK_KEYWAIT \msg_id
	_TALKMSG	 \msg_id
	_LAST_KEYWAIT				//注意！
	_TALK_CLOSE
	_TALK_OBJ_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	簡易BGに対して話し掛け
 */
//-----------------------------------------------------------------------------
	.macro	_EASY_MSG msg_id
	_TALK_START
	//_TALK_KEYWAIT \msg_id
	_TALKMSG	 \msg_id
	_LAST_KEYWAIT				//注意！
	_TALK_CLOSE
	_TALK_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	看板作成（タウンマップ、標識、表札）
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
 *	看板作成（掲示板）(ret_wk=SCWK_ANSWER固定！)
 */
//-----------------------------------------------------------------------------
	.macro	_INFOBOARD_MAKE type,map
	.short	EV_SEQ_INFOBOARD_MAKE
	.byte	\type
	.short	\map
	.endm

//-----------------------------------------------------------------------------
/**
 *	看板リクエスト
 */
//-----------------------------------------------------------------------------
	.macro	_BOARD_REQ req
	.short	EV_SEQ_BOARD_REQ
	.byte	\req
	.endm

//-----------------------------------------------------------------------------
/**
 *	看板リクエスト終了待ち
 */
//-----------------------------------------------------------------------------
	.macro	_BOARD_REQ_WAIT
	.short	EV_SEQ_BOARD_REQ_WAIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	看板メッセージ表示(ret_wk=SCWK_ANSWER固定！)
 */
//-----------------------------------------------------------------------------
	.macro	_BOARD_MSG msg_id,ret_wk
	.short	EV_SEQ_BOARD_MSG
	.byte	\msg_id
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	看板終了待ち(ret_wk=SCWK_ANSWER固定！)
 */
//-----------------------------------------------------------------------------
	.macro	_BOARD_END_WAIT ret_wk
	.short	EV_SEQ_BOARD_END_WAIT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	簡易看板に対して話し掛け（タウンマップ、標識、表札）(SCWK_ANSWER固定！)
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
 *	簡易看板に対して話し掛け（掲示板）(SCWK_ANSWER固定！)
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
 *	イベント切り替え
 */
//-----------------------------------------------------------------------------
	.macro	_MENU_REQ
	.short	EV_SEQ_MENU_REQ
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGスクロール
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
 *	「はい、いいえ」ウィンドウ関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	はい、いいえ選択
 */
//-----------------------------------------------------------------------------
	.macro	_YES_NO_WIN ret_wk
	.short	EV_SEQ_YES_NO_WIN
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	ギネス関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	ギネスウィンドウ呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_GUINNESS_WIN
	.short	EV_SEQ_GUINNESS_WIN
	.endm


//=============================================================================
/**
 *	BMPメニュー関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	BMPメニュー　初期化
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
 *	BMPメニュー　初期化(読み込んでいるgmmファイルを使用する)
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
 *	BMPメニュー　リスト作成
 */
//-----------------------------------------------------------------------------
	.macro	_BMPMENU_MAKE_LIST msg_id,param
	.short	EV_SEQ_BMPMENU_MAKE_LIST
	.byte	\msg_id
	.byte	\param
	.endm

//-----------------------------------------------------------------------------
/**
 *	BMPメニュー　リスト作成(shortバージョン)
 */
//-----------------------------------------------------------------------------
	.macro	_BMPMENU_MAKE_LIST16 msg_id,param
	.short	EV_SEQ_BMPMENU_MAKE_LIST16
	.short	\msg_id
	.short	\param
	.endm

//-----------------------------------------------------------------------------
/**
 *	BMPメニュー　開始
 */
//-----------------------------------------------------------------------------
	.macro	_BMPMENU_START
	.short	EV_SEQ_BMPMENU_START
	.endm

//-----------------------------------------------------------------------------
/**
 *	選択ウィンドウ　ジャンプ
 */
//-----------------------------------------------------------------------------
//	.macro	_SEL_WIN_JUMP act,adrs
//	.short	EV_SEQ_SEL_WIN_JUMP
//	.byte	\act
//	.long	((\adrs-.)-4)
//	.endm


//=============================================================================
/**
 *	BMPリスト関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	BMPリスト　初期化
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
 *	BMPリスト　初期化(読み込んでいるgmmファイルを使用する)
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
 *	BMPリスト　リスト作成
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
 *	BMPリスト　開始
 */
//-----------------------------------------------------------------------------
	.macro	_BMPLIST_START
	.short	EV_SEQ_BMPLIST_START
	.endm


//=============================================================================
/**
 *	BMPメニュー縦横関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	BMPメニュー縦横　開始
 */
//-----------------------------------------------------------------------------
	.macro	_BMPMENU_HV_START	x_max
	.short	EV_SEQ_BMPMENU_HV_START
	.byte	\x_max
	.endm


//=============================================================================
/**
 *	サウンド関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	SEを鳴らす
 */
//-----------------------------------------------------------------------------
	.macro	_SE_PLAY no
	.short	EV_SEQ_SE_PLAY
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	SEを止める
 */
//-----------------------------------------------------------------------------
	.macro	_SE_STOP no
	.short	EV_SEQ_SE_STOP
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	SE終了待ち
 */
//-----------------------------------------------------------------------------
	.macro	_SE_WAIT	no
	.short	EV_SEQ_SE_WAIT
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	鳴き声を鳴らす
 */
//-----------------------------------------------------------------------------
	.macro	_VOICE_PLAY no,ptn
	.short	EV_SEQ_VOICE_PLAY
	.short	\no
	.short	\ptn
	.endm

//-----------------------------------------------------------------------------
/**
 *	鳴き声終了待ち
 */
//-----------------------------------------------------------------------------
	.macro	_VOICE_WAIT
	.short	EV_SEQ_VOICE_WAIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	簡易鳴き声メッセージ表示
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
 *	MEを鳴らす
 */
//-----------------------------------------------------------------------------
	.macro	_ME_PLAY no
	.short	EV_SEQ_ME_PLAY
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	ME終了待ち
 */
//-----------------------------------------------------------------------------
	.macro	_ME_WAIT
	.short	EV_SEQ_ME_WAIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	音量セット
 */
//-----------------------------------------------------------------------------
	.macro	_SND_INITIAL_VOL_SET seq_no,vol
	.short	EV_SEQ_SND_INITIAL_VOL_SET
	.short	\seq_no
	.short	\vol
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGMを鳴らす
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_PLAY no
	.short	EV_SEQ_BGM_PLAY
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGMを終了待ち
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_PLAY_CHECK no,ret_wk
	.short	EV_SEQ_BGM_PLAY_CHECK
	.short	\no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGMを止める
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_STOP no
	.short	EV_SEQ_BGM_STOP
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	現在のマップのBGMを鳴らす
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_NOW_MAP_PLAY
	.short	EV_SEQ_BGM_NOW_MAP_PLAY
	.endm

//-----------------------------------------------------------------------------
/**
 *	マップ内限定のBGM指定がセットされる
 *	自転車BGMの制御などに使用
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
 *	BGMフェードアウト
 *
 *	vol		= ボリューム
 *	frame	= 何フレームかけてフェードするか
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_FADEOUT vol,frame
	.short	EV_SEQ_BGM_FADEOUT
	.short	\vol
	.short	\frame
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGMフェードアウト　→　指定したBGMを再生
 *	使用しない方がわかりやすいかも。。。
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_FADEOUT_PLAY frame,no
	_BGM_FADEOUT \frame
	_BGM_PLAY	 \no
	.endm

//-----------------------------------------------------------------------------
/**
 *	BGMフェードイン
 *
 *	frame = 何フレームかけてフェードするか
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_FADEIN frame
	.short	EV_SEQ_BGM_FADEIN
	.short	\frame
	.endm

//-----------------------------------------------------------------------------
/**
 *	シーケンスを一時停止または再開(1=停止、0=再開)
 */
//-----------------------------------------------------------------------------
	.macro	_BGM_PLAYER_PAUSE player,flag
	.short	EV_SEQ_BGM_PLAYER_PAUSE
	.byte	\player
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *	演出BGM再生(ライバル・サポート・つれてけ)
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_FIELD_DEMO_BGM_PLAY	no
	.short	EV_SEQ_PLAYER_FIELD_DEMO_BGM_PLAY
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	フィールドBGMを固定にするフラグセット(セーブしない)
 */
//-----------------------------------------------------------------------------
	.macro	_CTRL_BGM_FLAG_SET
	.short	EV_SEQ_CTRL_BGM_FLAG_SET
	.byte	1
	.endm

//-----------------------------------------------------------------------------
/**
 *	フィールドBGMを固定にするフラグリセット(セーブしない)
 */
//-----------------------------------------------------------------------------
	.macro	_CTRL_BGM_FLAG_RESET
	.short	EV_SEQ_CTRL_BGM_FLAG_SET
	.byte	0
	.endm

//-----------------------------------------------------------------------------
/**
 *	ペラップデータがあるかチェック
 */
//-----------------------------------------------------------------------------
	.macro	_PERAP_DATA_CHECK	ret_wk
	.short	EV_SEQ_PERAP_DATA_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ペラップ録音開始
 */
//-----------------------------------------------------------------------------
	.macro	_PERAP_REC_START	ret_wk
	.short	EV_SEQ_PERAP_REC_START
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ペラップ録音停止
 */
//-----------------------------------------------------------------------------
	.macro	_PERAP_REC_STOP
	.short	EV_SEQ_PERAP_REC_STOP
	.endm

//-----------------------------------------------------------------------------
/**
 *	ペラップ録音したデータをセーブ
 */
//-----------------------------------------------------------------------------
	.macro	_PERAP_SAVE
	.short	EV_SEQ_PERAP_SAVE
	.endm

//-----------------------------------------------------------------------------
/**
 *	サウンドデータ追加ロード：クライマックス
 */
//-----------------------------------------------------------------------------
	.macro	_SND_CLIMAX_DATA_LOAD
	.short	EV_SEQ_SND_CLIMAX_DATA_LOAD
	.endm


//=============================================================================
/**
 *	アニメーション関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	アニメ
 *
 *	注意！ 動作停止をセットしたい時は、_OBJ_PAUSE_ALLをもう一度呼ばないといけない！
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
 *	アニメーションデータラベル
 */
//-----------------------------------------------------------------------------
	.macro	_ANIME_LABEL label
	.align	4
	\label:
	.endm

//-----------------------------------------------------------------------------
/**
 *	アニメーションデータ(fieldobj_code.h参照)
 */
//-----------------------------------------------------------------------------
	.macro	_ANIME_DATA	code,num
	.short	\code
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	アニメウェイト
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
 *	動作停止
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_PAUSE_ALL
	.short	EV_SEQ_OBJ_PAUSE_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	動作再開
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_PAUSE_CLEAR_ALL
	.short	EV_SEQ_OBJ_PAUSE_CLEAR_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	個々の動作停止
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_PAUSE	obj_id
	.short	EV_SEQ_OBJ_PAUSE
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	個々の動作再開
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_PAUSE_CLEAR	obj_id
	.short	EV_SEQ_OBJ_PAUSE_CLEAR
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ出す
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_ADD	obj_id
	.short	EV_SEQ_OBJ_ADD
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ消す
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_DEL	obj_id
	.short	EV_SEQ_OBJ_DEL
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	透明ダミーOBJ追加
 */
//-----------------------------------------------------------------------------
	.macro	_VANISH_DUMMY_OBJ_ADD	x,z
	.short	EV_SEQ_VANISH_DUMMY_OBJ_ADD
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	透明ダミーOBJ削除
 */
//-----------------------------------------------------------------------------
	.macro	_VANISH_DUMMY_OBJ_DEL
	.short	EV_SEQ_VANISH_DUMMY_OBJ_DEL
	.endm

//-----------------------------------------------------------------------------
/**
 *	話しかけたOBJを自機方向へ振り向き
 */
//-----------------------------------------------------------------------------
	.macro	_TURN_HERO_SITE
	.short	EV_SEQ_OBJ_TURN
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJに対して話し掛け開始(主人公に対して振り向き有り)
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
 *	OBJに対して話し掛け開始(主人公に対して振り向き無し)
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_OBJ_START_TURN_NOT
	_SE_PLAY SEQ_SE_DP_SELECT
	//_SE_PLAY SEQ_SE_DP_SELECT11
	_OBJ_PAUSE_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJに対して話し掛け終了
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_OBJ_END
	_OBJ_PAUSE_CLEAR_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	BJに対して話し掛け開始
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_START
	_SE_PLAY SEQ_SE_DP_SELECT
	//_SE_PLAY SEQ_SE_DP_SELECT11
	_OBJ_PAUSE_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	POS,SCENE_CHANGE_LABELに対して開始
 *	(TALK_STARTを使用すると、会話開始の音がなってしまうので分けた)
 */
//-----------------------------------------------------------------------------
	.macro	_EVENT_START
	_OBJ_PAUSE_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	BJに対して話し掛け終了
 */
//-----------------------------------------------------------------------------
	.macro	_TALK_END
	_OBJ_PAUSE_CLEAR_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	POS,SCENE_CHANGE_LABELに対して終了
 */
//-----------------------------------------------------------------------------
	.macro	_EVENT_END
	_OBJ_PAUSE_CLEAR_ALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	主人公の位置取得
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_POS_GET	x,z
	.short	EV_SEQ_PLAYER_POS_GET
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJの位置取得
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
 *	主人公の位置オフセットセット
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
 * 主人公の方向取得
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_DIR_GET	dir
	.short	EV_SEQ_PLAYER_DIR_GET
	.short	\dir
	.endm

//-----------------------------------------------------------------------------
/**
 *	ゾーン切り替え時の削除禁止(TRUE=禁止、FALSE=禁止しない)
 */
//-----------------------------------------------------------------------------
	.macro	_NOT_ZONE_DEL_SET	obj_id,flag
	.short	EV_SEQ_NOT_ZONE_DEL_SET
	.short	\obj_id
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *	動作コード変更
 */
//-----------------------------------------------------------------------------
	.macro	_MOVE_CODE_CHANGE	obj_id,code
	.short	EV_SEQ_MOVE_CODE_CHANGE
	.short	\obj_id
	.short	\code
	.endm

//-----------------------------------------------------------------------------
/**
 *	動作コード取得
 */
//-----------------------------------------------------------------------------
	.macro	_MOVE_CODE_GET	ret_wk,obj_id
	.short	EV_SEQ_MOVE_CODE_GET
	.short	\ret_wk
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	連れ歩きOBJIDセット
 */
//-----------------------------------------------------------------------------
	.macro	_PAIR_OBJID_SET
	.short	EV_SEQ_PAIR_OBJID_SET
	.endm


//=============================================================================
/**
 *	イベントデータ関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	イベントデータ　テーブル宣言
 */
//-----------------------------------------------------------------------------
	.macro	_EVENT_DATA	adrs
	.long	((\adrs-.)-4)
	.endm

//-----------------------------------------------------------------------------
/**
 *	イベントデータ　テーブル終了
 */
//-----------------------------------------------------------------------------
#define EV_DATA_END_CODE	(0xfd13)	//適当な値
	.macro	_EVENT_DATA_END
	.short	EV_DATA_END_CODE
	.endm


//=============================================================================
/**
 *	特殊スクリプト関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	特殊スクリプト記述終了
 */
//-----------------------------------------------------------------------------
	.macro	_SP_EVENT_DATA_END
	.byte	SP_SCRID_NONE
	.endm

//-----------------------------------------------------------------------------
/**
 *	シーンイベント：常に監視している特殊スクリプト
 */
//-----------------------------------------------------------------------------
	.macro	_SCENE_CHANGE_LABEL	adrs
	.byte	SP_SCRID_SCENE_CHANGE
	.long	((\adrs-.)-4)
	.endm

	//起動条件記述
	.macro	_SCENE_CHANGE_DATA		wk,num,scr_id
	.short	\wk
	.short	\num
	.short	\scr_id
	.endm

	//記述終了(セーブワーク定義はSVWK_STARTのオフセットを足しているので0を指定してよい)
	.macro	_SCENE_CHANGE_END
	.short	0
	.endm

//-----------------------------------------------------------------------------
/**
 *	フラグ操作：マップ遷移で一度のみ呼ばれる特殊スクリプト
 */
//-----------------------------------------------------------------------------
	.macro	_FLAG_CHANGE_LABEL	scr_id
	.byte	SP_SCRID_FLAG_CHANGE
	.short	\scr_id
	.short	0		//4byteに合わせるためにダミー
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJ操作：マップ遷移で一度のみ呼ばれる特殊スクリプト
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_CHANGE_LABEL	scr_id
	.byte	SP_SCRID_OBJ_CHANGE
	.short	\scr_id
	.short	0		//4byteに合わせるためにダミー
	.endm

//-----------------------------------------------------------------------------
/**
 *	初期化操作：マップ初期化ごとに呼ばれる特殊スクリプト
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_CHANGE_LABEL	scr_id
	.byte	SP_SCRID_INIT_CHANGE
	.short	\scr_id
	.short	0		//4byteに合わせるためにダミー
	.endm


//=============================================================================
/**
 *	お金関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	お金を加える
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_GOLD val
	.short	EV_SEQ_ADD_GOLD
	.long	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	お金を減らす
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_GOLD val
	.short	EV_SEQ_SUB_GOLD
	.long	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	金額を調べる
 */
//-----------------------------------------------------------------------------
	.macro	_COMP_GOLD ret_wk,val
	.short	EV_SEQ_COMP_GOLD
	.short	\ret_wk
	.long	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	所持金ウィンドウ表示
 */
//-----------------------------------------------------------------------------
	.macro	_GOLD_WIN_WRITE		x,z
	.short	EV_SEQ_GOLD_WIN_WRITE
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	所持金ウィンドウ削除
 */
//-----------------------------------------------------------------------------
	.macro	_GOLD_WIN_DEL
	.short	EV_SEQ_GOLD_WIN_DEL
	.endm

//-----------------------------------------------------------------------------
/**
 *	所持金表示
 */
//-----------------------------------------------------------------------------
	.macro	_GOLD_WRITE
	.short	EV_SEQ_GOLD_WRITE
	.endm


//=============================================================================
/**
 *	コイン関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	コインウィンドウ表示
 */
//-----------------------------------------------------------------------------
	.macro	_COIN_WIN_WRITE	x,z
	.short	EV_SEQ_COIN_WIN_WRITE
	.short	\x
	.short	\z
	.endm

//-----------------------------------------------------------------------------
/**
 *	コインウィンドウ削除
 */
//-----------------------------------------------------------------------------
	.macro	_COIN_WIN_DEL
	.short	EV_SEQ_COIN_WIN_DEL	
	.endm

//-----------------------------------------------------------------------------
/**
 *	コイン表示
 */
//-----------------------------------------------------------------------------
	.macro	_COIN_WRITE
	.short	EV_SEQ_COIN_WRITE
	.endm

//-----------------------------------------------------------------------------
/**
 *	コイン数取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_COIN_NUM	ret_wk
	.short	EV_SEQ_GET_COIN_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	コイン加える
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_COIN		val
	.short	EV_SEQ_ADD_COIN
	.short	\val
	.endm

//-----------------------------------------------------------------------------
/**
 *	コイン減らす
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_COIN		val
	.short	EV_SEQ_SUB_COIN
	.short	\val
	.endm


//=============================================================================
/**
 *	アイテム関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	フィールドアイテムゲット処理
 *
 *	ANSWERに結果を代入
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_ITEM_EVENT	no,num
	_LDVAL	SCWK_REG0,\no
	_LDVAL	SCWK_REG1,\num
	_JUMP	ev_fld_item2
	.endm

//-----------------------------------------------------------------------------
/**
 *	隠しアイテムゲット処理
 *
 *	ANSWERに結果を代入
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
 *	アイテムを加える
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
 *	アイテムを減らす
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
 *	アイテムを加えられるかチェック
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
 *	バッグのアイテムチェック
 *
 *	ANSWERに結果を代入
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
 *	技マシンのアイテムナンバーかチェック
 *
 *	ANSWERに結果を代入
 */
//-----------------------------------------------------------------------------
	.macro	_WAZA_ITEM_CHK		item_no,ret_wk
	.short	EV_SEQ_WAZA_ITEM_CHK
	.short	\item_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケットナンバー取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POCKET_NO	item_no,ret_wk
	.short	EV_SEQ_GET_POCKET_NO
	.short	\item_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * 指定ポケットに何かあるかどうかのチェック
 */
//-----------------------------------------------------------------------------
	.macro	_CHECK_POCKET	pocket_no,ret_wk
	.short	EV_SEQ_POCKET_CHK
	.short	\pocket_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	パソコンにアイテムを加える
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_BOX_ITEM
	.short	EV_SEQ_ADD_BOX_ITEM
	.endm

//-----------------------------------------------------------------------------
/**
 *	パソコンのアイテムチェック
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_BOX_ITEM
	.short	EV_SEQ_CHK_BOX_ITEM
	.endm


//=============================================================================
/**
 *	グッズ関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	グッズを加える(PC)
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
 *	グッズを減らす(PC)
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
 *	グッズを加えられるかのチェック(PC)
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
 *	バッグのグッズチェック(PC)
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
 *	罠関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	罠を加える
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
 *	罠を減らす
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
 *	罠を加えられるかのチェック
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
 *	バッグの罠チェック
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
 *	お宝関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	お宝を加える
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
 *	お宝を減らす
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
 *	お宝を加えられるかのチェック
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
 *	バッグのお宝チェック
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
 *	タマ関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	タマを加える
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
 *	タマを減らす
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
 *	タマを加えられるかのチェック
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
 *	バッグのタマチェック
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
 *	シールの種類数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_CB_SEAL_KIND_NUM_GET	ret_wk
	.short	EV_SEQ_CB_SEAL_KIND_NUM_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	シールの数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_CB_ITEM_NUM_GET	seal_id,ret_wk
	.short	EV_SEQ_CB_ITEM_NUM_GET
	.short	\seal_id
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	シールを追加
 */
//-----------------------------------------------------------------------------
	.macro	_CB_ITEM_NUM_ADD	seal_id,num
	.short	EV_SEQ_CB_ITEM_NUM_ADD
	.short	\seal_id
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちのアンノーンの形状を取得
 */
//-----------------------------------------------------------------------------
	.macro	_UNKNOWN_FORM_GET	pos,ret_wk
	.short	EV_SEQ_UNKNOWN_FORM_GET
	.short	\pos
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	ポケモン関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	ポケモンを手持ちに加える
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
 *	タマゴを手持ちに加える
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_TAMAGO		monsno,msgid
	.short	EV_SEQ_ADD_TAMAGO
	.short	\monsno
	.short	\msgid
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちポケモンの技を置き換える
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
 *	指定された技を覚えているか調べる(1体）
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
 *	指定された技を覚えている手持ちポケモンを調べる(全体）
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_POKE_WAZA_GROUP	ret_wk,wazano
	.short	EV_SEQ_CHK_POKE_WAZA_GROUP
	.short	\ret_wk
	.short	\wazano
	.endm

//-----------------------------------------------------------------------------
/**
 * ポケモンが毒で気絶したかどうかのチェック
 */
//-----------------------------------------------------------------------------
	.macro	_APPROVE_POISON_DEAD	ret_wk, num
	.short	EV_SEQ_APPROVE_POISON_DEAD
	.short	\ret_wk
	.short	\num
	.endm

//=============================================================================
/**
 *	ポケサーチャー関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	渡されたトレーナーが再戦可能かチェック
 */
//-----------------------------------------------------------------------------
	.macro	_REVENGE_TRAINER_SEARCH	tr_id,ret_wk1
	.short	EV_SEQ_REVENGE_TRAINER_SEARCH
	.short	\tr_id
	.short	\ret_wk1
	.endm


//=============================================================================
/**
 *	天候関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	天候コードの初期化
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_WEATHER
	.short	EV_SEQ_INIT_WEATHER
	.endm

//-----------------------------------------------------------------------------
/**
 *	天候コードのセット
 */
//-----------------------------------------------------------------------------
	.macro	_SET_WEATHER id
	.short	EV_SEQ_SET_WEATHER
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	天候コードの反映
 */
//-----------------------------------------------------------------------------
	.macro	_UPDATE_WEATHER
	.short	EV_SEQ_UPDATE_WEATHER
	.endm


//=============================================================================
/**
 *	ツール関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	現在のマップ位置を取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_MAP_POS
	.short	EV_SEQ_GET_MAP_POS
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちのポケモン数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_TEMOTI_POKE_NUM
	.short	EV_SEQ_GET_TEMOTI_POKE_NUM
	.endm


//=============================================================================
/**
 *	プログラム関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	フィールドプロセス復帰
 */
//-----------------------------------------------------------------------------
	.macro	_SET_MAP_PROC
	.short	EV_SEQ_SET_MAP_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	フィールドプロセス終了
 */
//-----------------------------------------------------------------------------
	.macro	_FINISH_MAP_PROC
	.short	EV_SEQ_FINISH_MAP_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	ともだちコード登録イベント
 */
//-----------------------------------------------------------------------------
	.macro	_WIFI_AUTO_REG
	.short	EV_SEQ_WIFI_AUTO_REG
	.endm

//-----------------------------------------------------------------------------
/**
 *	P2P対戦マッチングボード呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_WIFI_P2P_MATCH_EVENT_CALL
	.short	EV_SEQ_WIFI_P2P_MATCH_EVENT_CALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	P2P対戦マッチングボードの戻り値取得、確保したメモリ削除
 */
//-----------------------------------------------------------------------------
	.macro	_WIFI_P2P_MATCH_SET_DEL	ret_wk
	.short	EV_SEQ_WIFI_P2P_MATCH_SET_DEL
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	自分のNET_IDを返す
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_GET_CURRENT_ID	ret_wk
	.short	EV_SEQ_COMM_GET_CURRENT_ID
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	殿堂入り回数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_DENDOU_NUM_GET	ret_wk
	.short	EV_SEQ_DENDOU_NUM_GET
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	ポケモンウィンドウ表示
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_WINDOW_PUT	monsno,sex
	.short	EV_SEQ_POKE_WINDOW_PUT
	.short	\monsno
	.short	\sex
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケモンウィンドウ表示(POKEMON_PARAM)
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_WINDOW_PUT_PP	pos
	.short	EV_SEQ_POKE_WINDOW_PUT_PP
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケモンウィンドウ削除
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_WINDOW_DEL
	.short	EV_SEQ_POKE_WINDOW_DEL
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケモンウィンドウアニメ
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_WINDOW_ANM
	.short	EV_SEQ_POKE_WINDOW_ANM
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケモンウィンドウアニメウェイト
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_WINDOW_ANM_WAIT	ret_wk
	.short	EV_SEQ_POKE_WINDOW_ANM_WAIT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルサーチャーイベント呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_SEARCHER_EVENT_CALL	ret_wk
	.short	EV_SEQ_BTL_SEARCHER_EVENT_CALL
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルサーチャー：戦闘後に表示方向固定の動作コードをセット
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_SEARCHER_DIR_MV_SET
	.short	EV_SEQ_BTL_SEARCHER_DIR_MV_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	メッセージ登録少年
 */
//-----------------------------------------------------------------------------
	.macro	_MSG_BOY_EVENT
	.short	EV_SEQ_MSG_BOY_EVENT
	.endm

//-----------------------------------------------------------------------------
/**
 *	イメージクリップ呼び出し
 *	pos	セーブ有無が帰ります
 *	refe	REFERENCEありの時 1
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
 *	イメージクリップViewer呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_IMAGE_CLIP_VIEW_TV_SET_PROC	pos,ret_work
	.short	EV_SEQ_IMAGE_CLIPVIEW_TV_SET_PROC
	.short	\pos
	.short	\ret_work
	.endm

//-----------------------------------------------------------------------------
/**
 *	イメージクリップViewer呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_IMAGE_CLIP_VIEW_CON_SET_PROC	pos,ret_work
	.short	EV_SEQ_IMAGE_CLIPVIEW_CON_SET_PROC
	.short	\pos
	.short	\ret_work
	.endm

//-----------------------------------------------------------------------------
/**
 *	カスタムボール呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_CUSTOM_BALL_EVENT_CALL
	.short	EV_SEQ_CUSTOM_BALL_EVENT_CALL
	.endm

//-----------------------------------------------------------------------------
/**
 *	タウンマップBGモード呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_TMAP_BG_SET_PROC
	.short	EV_SEQ_TMAP_BG_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	ボックス呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_BOX_SET_PROC	mode
	.short	EV_SEQ_BOX_SET_PROC
	.byte	\mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	おえかき呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_OEKAKI_BOARD_SET_PROC
	.short	EV_SEQ_OEKAKI_BOARD_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	カード呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_TR_CARD_SET_PROC
	.short	EV_SEQ_TR_CARD_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	こうかん呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_TRADE_LIST_SET_PROC
	.short	EV_SEQ_TRADE_LIST_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	レコードコーナー呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_RECORD_CORNER_SET_PROC
	.short	EV_SEQ_RECORD_CORNER_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	殿堂入り呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_DENDOU_SET_PROC
	.short	EV_SEQ_DENDOU_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	パソコン殿堂入り呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_PC_DENDOU_SET_PROC
	.short	EV_SEQ_PC_DENDOU_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	世界交換画面呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_WORLDTRADE_SET_PROC	no,ret_wk
	.short	EV_SEQ_WORLDTRADE_SET_PROC
	.short	\no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	WIFI接続し初回のID取得
 */
//-----------------------------------------------------------------------------
	.macro	_DPW_INIT_PROC	ret_wk
	.short	EV_SEQ_DPW_INIT_PROC
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	最初のポケモン選択呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_FIRST_POKE_SELECT_PROC
	.short	EV_SEQ_FIRST_POKE_SELECT_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	最初のポケモン選択で選択したポケモンナンバーを取得して、確保したメモリ削除
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
 *	ポケモン選択画面呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_POKELIST_SET_PROC
	.short	EV_SEQ_POKELIST_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケモン選択画面呼び出し(ゲーム内交換)
 */
//-----------------------------------------------------------------------------
	.macro	_NPC_TRADE_POKELIST_SET_PROC
	.short	EV_SEQ_NPC_TRADE_POKELIST_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	ユニオンポケモン選択画面呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_POKELIST_SET_PROC
	.short	EV_SEQ_UNION_POKELIST_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 * ポケモン選択画面結果取り出し
 */
//-----------------------------------------------------------------------------
	.macro	_POKELIST_GET_RESULT	ret_wk
	.short	EV_SEQ_POKELIST_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテストポケモン選択画面呼び出し
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
 * コンテスト ポケモン選択画面結果取り出し
 */
//-----------------------------------------------------------------------------
	.macro	_CON_POKELIST_GET_RESULT	ret_wk,ret_mode
	.short	EV_SEQ_CON_POKELIST_GET_RESULT
	.short	\ret_wk
	.short	\ret_mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト ポケモンステータス画面呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_CON_POKESTATUS_SET_PROC	pos
	.short	EV_SEQ_CON_POKESTATUS_SET_PROC
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 * ポケモンステータス画面結果取り出し(一応_CON_POKESTATUS_SET_PROC用で作った)
 */
//-----------------------------------------------------------------------------
	.macro	_POKESTATUS_GET_RESULT	ret_wk
	.short	EV_SEQ_POKESTATUS_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	地球儀画面呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_WIFI_EARTH_SET_PROC
	.short	EV_SEQ_WIFI_EARTH_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	視線：トレーナー移動呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_EYE_TRAINER_MOVE_SET	pos
	.short	EV_SEQ_EYE_TRAINER_MOVE_SET
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	視線：トレーナー移動終了チェック
 */
//-----------------------------------------------------------------------------
	.macro	_EYE_TRAINER_MOVE_CHECK	pos,ret_wk
	.short	EV_SEQ_EYE_TRAINER_MOVE_CHECK
	.short	\pos
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	視線：トレーナータイプ取得
 */
//-----------------------------------------------------------------------------
	.macro	_EYE_TRAINER_TYPE_GET ret_wk
	.short	EV_SEQ_EYE_TRAINER_TYPE_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	視線：トレーナーID取得
 */
//-----------------------------------------------------------------------------
	.macro	_EYE_TRAINER_ID_GET	pos,ret_wk
	.short	EV_SEQ_EYE_TRAINER_ID_GET
	.short	\pos
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	名前入力呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_NAMEIN ret_wk
	.short	EV_SEQ_NAMEIN
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケモン名前入力呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_NAMEIN_POKE	pos,ret_wk
	.short	EV_SEQ_NAMEIN_POKE
	.short	\pos
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	輝度関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	ワイプフェードスタート
 *
 *	注意！　フェードにかかるLCD、BG面の設定は固定にしている
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
 *	ワイプフェード終了チェック
 *
 *	注意！　チェックするLCDの設定は固定にしている
 */
//-----------------------------------------------------------------------------
	.macro	_WIPE_FADE_END_CHECK
	.short	EV_SEQ_WIPE_FADE_END_CHECK
	.endm

//-----------------------------------------------------------------------------
/**
 *	ホワイトアウト
 *
 *	注意！　フェードにかかるLCD、BG面の設定は固定にしている
 */
//-----------------------------------------------------------------------------
	.macro	_WHITE_OUT	div,sync
	_WIPE_FADE_START	\div,\sync,WIPE_TYPE_FADEOUT,WIPE_FADE_WHITE
	.endm

//-----------------------------------------------------------------------------
/**
 *	ホワイトイン
 *
 *	注意！　フェードにかかるLCD、BG面の設定は固定にしている
 */
//-----------------------------------------------------------------------------
	.macro	_WHITE_IN	div,sync
	_WIPE_FADE_START	\div,\sync,WIPE_TYPE_FADEIN,WIPE_FADE_WHITE
	.endm

//-----------------------------------------------------------------------------
/**
 *	ブラックアウト
 *
 *	注意！　フェードにかかるLCD、BG面の設定は固定にしている
 */
//-----------------------------------------------------------------------------
	.macro	_BLACK_OUT	div,sync
	_WIPE_FADE_START	\div,\sync,WIPE_TYPE_FADEOUT,WIPE_FADE_BLACK
	.endm

//-----------------------------------------------------------------------------
/**
 *	ブラックイン
 *
 *	注意！　フェードにかかるLCD、BG面の設定は固定にしている
 */
//-----------------------------------------------------------------------------
	.macro	_BLACK_IN	div,sync
	_WIPE_FADE_START	\div,\sync,WIPE_TYPE_FADEIN,WIPE_FADE_BLACK
	.endm


//=============================================================================
/**
 *	マップ遷移関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	マップ遷移
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
 *	マップ遷移(フェードなし)
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
 *	マップ遷移(コロシアム)イン
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
 *	マップ遷移(コロシアム)アウト
 */
//-----------------------------------------------------------------------------
	.macro	_COLOSSEUM_MAP_CHANGE_OUT
	.short	EV_SEQ_COLOSSEUM_MAP_CHANGE_OUT
	.endm

//-----------------------------------------------------------------------------
/**
 *	前のゾーンID取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_BEFORE_ZONE_ID	ret_wk
	.short	EV_SEQ_GET_BEFORE_ZONEID
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	現在のゾーンID取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_NOW_ZONE_ID	ret_wk
	.short	EV_SEQ_GET_NOW_ZONEID
	.short	\ret_wk
	.endm

//=============================================================================
/**
 *	秘伝技関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	壁のぼり
 */
//-----------------------------------------------------------------------------
	.macro	_KABENOBORI	wk
	.short	EV_SEQ_KABENOBORI
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	なみのり
 */
//-----------------------------------------------------------------------------
	.macro	_NAMINORI	wk
	.short	EV_SEQ_NAMINORI
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	自転車に乗っているかチェック
 */
//-----------------------------------------------------------------------------
	.macro	_BICYCLE_CHECK	ret_wk
	.short	EV_SEQ_BICYCLE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	1=自転車、0=歩行形態に変更
 */
//-----------------------------------------------------------------------------
	.macro	_BICYCLE_REQ	flag
	.short	EV_SEQ_BICYCLE_REQ
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *	自転車形態に変更(BGMは変更しない、マップ有効フラグは立つ)
 *	このコマンドの後に「_BGM_PLAY	SEQ_BICYCLE」を呼ぶ
 *	サイクリングロード専用
 */
//-----------------------------------------------------------------------------
	.macro	_BICYCLE_REQ_NON_BGM
	.short	EV_SEQ_BICYCLE_REQ_NON_BGM
	.endm

//-----------------------------------------------------------------------------
/**
 *	サイクリングロードセット(1=サイクリングロード、0=なし)
 */
//-----------------------------------------------------------------------------
	.macro	_CYCLING_ROAD_SET	flag
	.short	EV_SEQ_CYCLING_ROAD_SET
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *	自機の形態を取得
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_FORM_GET	ret_wk
	.short	EV_SEQ_PLAYER_FORM_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	自機へリクエスト
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_REQ_BIT_ON	bit
	.short	EV_SEQ_PLAYER_REQ_BIT_ON
	.short	\bit
	.endm

//-----------------------------------------------------------------------------
/**
 *	自機リクエスト実行
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_REQ_START
	.short	EV_SEQ_PLAYER_REQ_START
	.endm

//-----------------------------------------------------------------------------
/**
 *	たきのぼり
 */
//-----------------------------------------------------------------------------
	.macro	_TAKINOBORI	wk
	.short	EV_SEQ_TAKINOBORI
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	そらをとぶ
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
 * 秘伝わざ：フラッシュ
 */
//-----------------------------------------------------------------------------
	.macro	_HIDEN_FLASH
	.short	EV_SEQ_HIDEN_FLASH
	.endm

//-----------------------------------------------------------------------------
/**
 * 秘伝わざ：きりばらい
 */
//-----------------------------------------------------------------------------
	.macro	_HIDEN_KIRIBARAI
	.short	EV_SEQ_HIDEN_KIRIBARAI
	.endm

//-----------------------------------------------------------------------------
/**
 *	カットイン
 */
//-----------------------------------------------------------------------------
	.macro	_CUTIN	wk
	.short	EV_SEQ_CUTIN
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト　着替え
 */
//-----------------------------------------------------------------------------
	.macro	_CON_HERO_CHANGE
	.short	EV_SEQ_CON_HERO_CHANGE
	.endm


//=============================================================================
/**
 *	文字列関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	主人公名
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_NAME	idx
	.short	EV_SEQ_PLAYER_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	ライバル名
 */
//-----------------------------------------------------------------------------
	.macro	_RIVAL_NAME	idx
	.short	EV_SEQ_RIVAL_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	サポート名
 */
//-----------------------------------------------------------------------------
	.macro	_SUPPORT_NAME	idx
	.short	EV_SEQ_SUPPORT_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちポケモン名
 */
//-----------------------------------------------------------------------------
	.macro	_POKEMON_NAME	idx,pos
	.short	EV_SEQ_POKEMON_NAME
	.byte	\idx
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	アイテム名
 */
//-----------------------------------------------------------------------------
	.macro	_ITEM_NAME	idx,itemno
	.short	EV_SEQ_ITEM_NAME
	.byte	\idx
	.short	\itemno
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケット名
 */
//-----------------------------------------------------------------------------
	.macro	_POCKET_NAME	idx,pocket
	.short	EV_SEQ_POCKET_NAME
	.byte	\idx
	.short	\pocket
	.endm

//-----------------------------------------------------------------------------
/**
 *	技名
 */
//-----------------------------------------------------------------------------
	.macro	_ITEM_WAZA_NAME	idx,itemno
	.short	EV_SEQ_ITEM_WAZA_NAME
	.byte	\idx
	.short	\itemno
	.endm

//-----------------------------------------------------------------------------
/**
 *	技名
 */
//-----------------------------------------------------------------------------
	.macro	_WAZA_NAME	idx,waza
	.short	EV_SEQ_WAZA_NAME
	.byte	\idx
	.short	\waza
	.endm

//-----------------------------------------------------------------------------
/**
 *	数値名
 */
//-----------------------------------------------------------------------------
	.macro	_NUMBER_NAME	idx,number
	.short	EV_SEQ_NUMBER_NAME
	.byte	\idx
	.short	\number
	.endm

//-----------------------------------------------------------------------------
/**
 *	数値名	ディスプレイモード指定版
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
 *	誕生日かチェック
 */
//-----------------------------------------------------------------------------
	.macro	_BIRTH_DAY_CHECK	ret_wk
	.short	EV_SEQ_BIRTH_DAY_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	アンノーン形状の見た数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_ANOON_SEE_NUM	ret_wk
	.short	EV_SEQ_ANOON_SEE_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ニックネーム
 */
//-----------------------------------------------------------------------------
	.macro	_NICK_NAME	idx,pos
	.short	EV_SEQ_NICK_NAME
	.byte	\idx
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケッチソフト名
 */
//-----------------------------------------------------------------------------
	.macro	_POKETCH_NAME	idx,app_id
	.short	EV_SEQ_POKETCH_NAME
	.byte	\idx
	.short	\app_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	トレーナー種別名
 */
//-----------------------------------------------------------------------------
	.macro	_TR_TYPE_NAME	idx,type
	.short	EV_SEQ_TR_TYPE_NAME
	.byte	\idx
	.short	\type
	.endm

//-----------------------------------------------------------------------------
/**
 *	主人公のトレーナー種別名
 */
//-----------------------------------------------------------------------------
	.macro	_MY_TR_TYPE_NAME	idx
	.short	EV_SEQ_MY_TR_TYPE_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	モンスターナンバーからポケモン名
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
 *	最初のポケモン名
 */
//-----------------------------------------------------------------------------
	.macro	_FIRST_POKEMON_NAME	idx
	.short	EV_SEQ_FIRST_POKEMON_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	ライバルのポケモン名
 */
//-----------------------------------------------------------------------------
	.macro	_RIVAL_POKEMON_NAME	idx
	.short	EV_SEQ_RIVAL_POKEMON_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	サポートのポケモン名
 */
//-----------------------------------------------------------------------------
	.macro	_SUPPORT_POKEMON_NAME	idx
	.short	EV_SEQ_SUPPORT_POKEMON_NAME
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	最初のポケモンナンバー取得
 */
//-----------------------------------------------------------------------------
	.macro	_FIRST_POKE_NO_GET	ret_wk
	.short	EV_SEQ_FIRST_POKE_NO_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	きのみの名前
 *	@param	idx			セットするWORDSETの位置
 *	@param	itemno		きのみの指定（アイテムナンバーで）
 *	@param	count		きのみの数
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
 *	性格の名前
 *	@param	idx			セットするWORDSETの位置
 *	@param	seikaku		性格
 */
//-----------------------------------------------------------------------------
	.macro	_SEIKAKU_NAME	idx,seikaku
	.short	EV_SEQ_SEIKAKU_NAME
	.byte	\idx
	.short	\seikaku
	.endm

//-----------------------------------------------------------------------------
/**
 *	グッズの名前
 *	@param	idx			セットするWORDSETの位置
 *	@param	itemno		グッズの指定
 */
//-----------------------------------------------------------------------------
	.macro	_GOODS_NAME	idx, goodsno
	.short	EV_SEQ_GOODS_NAME
	.byte	\idx
	.short	\goodsno
	.endm

//-----------------------------------------------------------------------------
/**
 *	トラップの名前
 *	@param	idx			セットするWORDSETの位置
 *	@param	itemno		グッズの指定
 */
//-----------------------------------------------------------------------------
	.macro	_TRAP_NAME	idx, trapno
	.short	EV_SEQ_TRAP_NAME
	.byte	\idx
	.short	\trapno
	.endm

//-----------------------------------------------------------------------------
/**
 *	タマの名前
 *	@param	idx			セットするWORDSETの位置
 *	@param	itemno		グッズの指定
 */
//-----------------------------------------------------------------------------
	.macro	_TAMA_NAME	idx, tamano
	.short	EV_SEQ_TAMA_NAME
	.byte	\idx
	.short	\tamano
	.endm

//-----------------------------------------------------------------------------
/**
 *	ゾーンの名前
 *	@param	idx			セットするWORDSETの位置
 *	@param	zone_id		ゾーンID
 */
//-----------------------------------------------------------------------------
	.macro	_ZONE_NAME	idx, zone_id
	.short	EV_SEQ_ZONE_NAME
	.byte	\idx
	.short	\zone_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	大量発生情報の取得
 *	@param	zone		ゾーンID格納バッファ
 *	@param	poke		モンスターナンバー格納バッファ
 */
//-----------------------------------------------------------------------------
	.macro	_GENERATE_INFO_GET	zone, poke
	.short	EV_SEQ_GENERATE_INFO_GET
	.short	\zone
	.short	\poke
	.endm


//=============================================================================
/**
 *	戦闘関連(実験)
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	トレーナーID取得
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_ID_GET	wk
	.short	EV_SEQ_TRAINER_ID_GET
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	トレーナー戦闘呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_BTL_SET	tr_id_0,tr_id_1
	.short	EV_SEQ_TRAINER_BTL_SET
	.short	\tr_id_0
	.short	\tr_id_1
	.endm

//-----------------------------------------------------------------------------
/**
 *	トレーナー戦闘（マルチバトル）呼び出し
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
 *	トレーナー会話呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_MSG_SET	tr_id,kind_id
	.short	EV_SEQ_TRAINER_MSG_SET
	.short	\tr_id
	.short	\kind_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	トレーナー会話の種類取得
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
 *	再戦トレーナー会話の種類取得
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
 *	トレーナータイプ取得
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_TYPE_GET	ret_wk
	.short	EV_SEQ_TRAINER_TYPE_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	トレーナーBGMセット
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_BGM_SET	tr_id
	.short	EV_SEQ_TRAINER_BGM_SET
	.short	\tr_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	トレーナー敗北
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_LOSE
	.short	EV_SEQ_LOSE
	.endm

//-----------------------------------------------------------------------------
/**
 *	トレーナー敗北チェック
 */
//-----------------------------------------------------------------------------
	.macro	_TRAINER_LOSE_CHECK ret_wk
	.short	EV_SEQ_LOSE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	敗北処理
 */
//-----------------------------------------------------------------------------
	.macro	_NORMAL_LOSE
	.short	EV_SEQ_LOSE
	.endm

//-----------------------------------------------------------------------------
/**
 *	敗北チェック
 */
//-----------------------------------------------------------------------------
	.macro	_LOSE_CHECK	ret_wk
	.short	EV_SEQ_LOSE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	隠しポケモン再戦可不可チェック
 */
//-----------------------------------------------------------------------------
	.macro	_SEACRET_POKE_RETRY_CHECK ret_wk
	.short	EV_SEQ_SEACRET_POKE_RETRY_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	配布ポケモン再戦可不可チェック
 */
//-----------------------------------------------------------------------------
	.macro	_HAIFU_POKE_RETRY_CHECK ret_wk
	.short	EV_SEQ_HAIFU_POKE_RETRY_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちチェック 2vs2が可能か取得
 */
//-----------------------------------------------------------------------------
	.macro	_2VS2_BATTLE_CHECK ret_wk
	.short	EV_SEQ_2VS2_BATTLE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	デバック戦闘呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_BTL_SET
	.short	EV_SEQ_DEBUG_BTL_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	デバックトレーナーフラグセット(後で削除します！)
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_TRAINER_FLAG_SET
	.short	EV_SEQ_DEBUG_TRAINER_FLAG_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	デバックトレーナーフラグONジャンプ(後で削除します！)
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_TRAINER_FLAG_ON_JUMP	adrs
	.short	EV_SEQ_DEBUG_TRAINER_FLAG_ON_JUMP
	.long	((\adrs-.)-4)
	.endm
	//.macro	_DEBUG_TRAINER_FLAG_ON_JUMP
	//.short	EV_SEQ_DEBUG_TRAINER_FLAG_ON_JUMP
	//.endm

	//10月末ROM用！トレーナーとの会話→フラグセット→戦闘
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
 *	通信関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	親機を選択するウィンドウを開く
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
 *	子機を選択するウィンドウを開く
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
 *	デバック親機を選択するウィンドウを開く
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_PARENT_WIN ret_wk
	.short	EV_SEQ_CONNECT_DEBUG_PARENT_WIN
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	デバック子機を選択するウィンドウを開く
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_CHILD_WIN ret_wk
	.short	EV_SEQ_CONNECT_DEBUG_CHILD_WIN
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	デバック用　通信戦闘呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_SIO_ENCOUNT
	.short	EV_SEQ_DEBUG_SIO_ENCOUNT
	.endm

//-----------------------------------------------------------------------------
/**
 *	デバック用　通信コンテスト呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_SIO_CONTEST
	.short	EV_SEQ_DEBUG_SIO_CONTEST
	.endm


//=============================================================================
/**
 *	コンテスト関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	送信
 */
//-----------------------------------------------------------------------------
	.macro	_CONSIO_TIMING_SEND	timing_no
	.short	EV_SEQ_CONSIO_TIMING_SEND
	.short	\timing_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	同期待ち
 */
//-----------------------------------------------------------------------------
	.macro	_CONSIO_TIMING_CHECK	timing_no
	.short	EV_SEQ_CONSIO_TIMING_CHECK
	.short	\timing_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	システムワーク作成
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
 *	システムワーク削除
 */
//-----------------------------------------------------------------------------
	.macro	_CON_SYSTEM_EXIT	wk
	.short	EV_SEQ_CON_SYSTEM_EXIT
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	審判名取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_JUDGE_NAME_GET	judge_no,idex
	.short	EV_SEQ_CON_JUDGE_NAME_GET
	.short	\judge_no
	.short	\idex
	.endm

//-----------------------------------------------------------------------------
/**
 *	ブリーダー名取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_BREEDER_NAME_GET	entry_no,idex
	.short	EV_SEQ_CON_BREEDER_NAME_GET
	.short	\entry_no
	.short	\idex
	.endm

//-----------------------------------------------------------------------------
/**
 *	ニックネーム取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_NICK_NAME_GET	entry_no,idex
	.short	EV_SEQ_CON_NICK_NAME_GET
	.short	\entry_no
	.short	\idex
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト：一桁数値をタグにセット
 */
//-----------------------------------------------------------------------------
	.macro	_CON_NUM_TAG_SET	num,idex
	.short	EV_SEQ_CON_NUM_TAG_SET
	.short	\num
	.short	\idex
	.endm

//-----------------------------------------------------------------------------
/**
 *	通信用にワークの初期設定と最初の通信を行うタスクを生成
 */
//-----------------------------------------------------------------------------
	.macro	_CON_SIO_PARAM_INIT_SET
	.short	EV_SEQ_CON_SIO_PARAM_INIT_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_CONTEST_PROC
	.short	EV_SEQ_CONTEST_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	ランク名取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_RANK_NAME_GET	idx
	.short	EV_SEQ_CON_RANK_NAME_GET
	.short	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	タイプ名取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_TYPE_NAME_GET	idx
	.short	EV_SEQ_CON_TYPE_NAME_GET
	.short	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	優勝者名取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_VICTORY_BREEDER_NAME_GET	idx
	.short	EV_SEQ_CON_VICTORY_BREEDER_NAME_GET
	.short	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	優勝商品ナンバー取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_VICTORY_ITEM_NO_GET	ret_wk
	.short	EV_SEQ_CON_VICTORY_ITEM_NO_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	優勝したブリーダーのポケモンニックネームを取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_VICTORY_NICK_NAME_GET	buf_id
	.short	EV_SEQ_CON_VICTORY_NICK_NAME_GET
	.short	\buf_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	今参加していたコンテストで自分が何位だったかを取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_RANKING_CHECK	ret_wk
	.short	EV_SEQ_CON_RANKING_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	優勝したブリーダーのエントリー番号を取得する
 */
//-----------------------------------------------------------------------------
	.macro	_CON_VICTORY_ENTRY_NO_GET	ret_wk
	.short	EV_SEQ_CON_VICTORY_ENTRY_NO_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	自分のエントリー番号を取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_MY_ENTRY_NO_GET	ret_wk
	.short	EV_SEQ_CON_MY_ENTRY_NO_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	OBJコードを取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_OBJ_CODE_GET	entry_no,ret_wk
	.short	EV_SEQ_CON_OBJ_CODE_GET
	.short	\entry_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	人気を取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_POPULARITY_GET	entry_no,ret_wk
	.short	EV_SEQ_CON_POPULARITY_GET
	.short	\entry_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト：受付ナンバーを取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_DESK_MODE_GET	ret_wk
	.short	EV_SEQ_CON_DESK_MODE_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト：参加しているコンテストで優勝した時に貰えるリボンを既に持っているかチェック
 */
//-----------------------------------------------------------------------------
	.macro	_CON_HAVE_RIBBON_CHECK	ret_wk
	.short	EV_SEQ_CON_HAVE_RIBBON_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	参加しているコンテストで優勝した時に貰えるリボンの名前を取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_RIBBON_NAME_GET	buf_id
	.short	EV_SEQ_CON_RIBBON_NAME_GET
	.short	\buf_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテストで優勝した時に貰えるアクセサリ番号を取得
 */
//-----------------------------------------------------------------------------
	.macro	_CON_ACCE_NO_GET	ret_wk
	.short	EV_SEQ_CON_ACCE_NO_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト：コンテストシステムワークからランクやモードなどを取得する
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
 *	コンテスト：カメラのフラッシュエフェクトセット
 */
//-----------------------------------------------------------------------------
	.macro	_CON_CAMERA_FLASH_SET	entry_no
	.short	EV_SEQ_CON_CAMERA_FLASH_SET
	.short	\entry_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト：カメラのフラッシュエフェクト終了待ち
 */
//-----------------------------------------------------------------------------
	.macro	_CON_CAMERA_FLASH_CHECK
	.short	EV_SEQ_CON_CAMERA_FLASH_CHECK
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト：フィールドのHブランク停止
 */
//-----------------------------------------------------------------------------
	.macro	_CON_HBLANK_STOP
	.short	EV_SEQ_CON_HBLANK_STOP
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト：フィールドのHブランク再開
 */
//-----------------------------------------------------------------------------
	.macro	_CON_HBLANK_START
	.short	EV_SEQ_CON_HBLANK_START
	.endm

//-----------------------------------------------------------------------------
/**
 *  エンディングスキップ条件確認
 *		CPUが優勝、又は通信対戦のどちらかの条件を満たすかチェック
 */
//-----------------------------------------------------------------------------
	.macro	_CON_ENDING_SKIP_CHECK	ret_wk
	.short	EV_SEQ_CON_ENDING_SKIP_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト通信対戦成績表示
 */
//-----------------------------------------------------------------------------
	.macro	_CON_RECORD_DISP
	.short	EV_SEQ_CON_RECORD_DISP
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト：メッセージ送りフラグ設定
 */
//-----------------------------------------------------------------------------
	.macro	_CON_MSGPRINT_FLAG_SET
	.short	EV_SEQ_CON_MSGPRINT_FLAG_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	コンテスト：メッセージ送りフラグ設定
 */
//-----------------------------------------------------------------------------
	.macro	_CON_MSGPRINT_FLAG_RESET
	.short	EV_SEQ_CON_MSGPRINT_FLAG_RESET
	.endm


//=============================================================================
/**
 *	特殊接続関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	特殊接続情報セット
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
 *	エレベータ関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	BMPメニュー　エレベータフロア
 */
//-----------------------------------------------------------------------------
	.macro	_ELEVATOR_FLOOR_GET wk
	.short	EV_SEQ_ELEVATOR_FLOOR_GET
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	BMPメニュー　エレベータフロア
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
 *	図鑑評価関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	シンオウ図鑑　見つけた数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_SHINOU_ZUKAN_SEE_NUM	ret_wk
	.short	EV_SEQ_SHINOU_ZUKAN_SEE_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	シンオウ図鑑　捕まえた数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_SHINOU_ZUKAN_GET_NUM	ret_wk
	.short	EV_SEQ_SHINOU_ZUKAN_GET_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	全国図鑑　見つけた数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_ZENKOKU_ZUKAN_SEE_NUM	ret_wk
	.short	EV_SEQ_ZENKOKU_ZUKAN_SEE_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	全国図鑑　捕まえた数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_ZENKOKU_ZUKAN_GET_NUM	ret_wk
	.short	EV_SEQ_ZENKOKU_ZUKAN_GET_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	全国図鑑かチェック
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_ZENKOKU_ZUKAN
	.short	EV_SEQ_CHK_ZENKOKU_ZUKAN
	.endm

//-----------------------------------------------------------------------------
/**
 *	評価メッセージID取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_HYOUKA_MSGID	mode,ret_wk
	.short	EV_SEQ_GET_HYOUKA_MSGID
	.byte	\mode
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	野生戦闘関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	ポケモンナンバーとレベルを指定して野生戦闘
 */
//-----------------------------------------------------------------------------
	.macro	_WILD_BTL_SET	monsno,level
	.short	EV_SEQ_WILD_BTL_SET
	.short	\monsno
	.short	\level
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケモンナンバーとレベルを指定してイベント野生戦闘
 */
//-----------------------------------------------------------------------------
	.macro	_SP_WILD_BTL_SET	monsno,level
	.short	EV_SEQ_SP_WILD_BTL_SET
	.short	\monsno
	.short	\level
	.endm

//-----------------------------------------------------------------------------
/**
 *	最初のイベント戦闘
 */
//-----------------------------------------------------------------------------
	.macro	_FIRST_BTL_SET	monsno,level
	.short	EV_SEQ_FIRST_BTL_SET
	.short	\monsno
	.short	\level
	.endm

//-----------------------------------------------------------------------------
/**
 *	最初のイベント戦闘
 */
//-----------------------------------------------------------------------------
	.macro	_CAPTURE_BTL_SET
	.short	EV_SEQ_CAPTURE_BTL_SET
	.endm


//=============================================================================
/**
 *	ハニーツリー
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	ハニーツリー
 */
//-----------------------------------------------------------------------------
	.macro	_HONEY_TREE
	.short	EV_SEQ_HONEY_TREE
	.endm

//-----------------------------------------------------------------------------
/**
 *	ハニーツリーステート取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_HONEY_TREE_STATE ret_wk
	.short	EV_SEQ_GET_HONEY_TREE_STATE
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ハニーツリー戦闘
 */
//-----------------------------------------------------------------------------
	.macro	_HONEY_TREE_BTL_SET
	.short	EV_SEQ_SET_HONEY_TREE_BTL
	.endm

//-----------------------------------------------------------------------------
/**
 *	ハニーツリー戦闘終了後
 */
//-----------------------------------------------------------------------------
	.macro	_HONEY_TREE_AFTER_SET
	.short	EV_SEQ_SET_AFTER_HONEY_TREE_BTL
	.endm

//-----------------------------------------------------------------------------
/**
 *	サイン呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_TSIGN_SET_PROC
	.short	EV_SEQ_TSIGN_SET_PROC
	.endm


//=============================================================================
/**
 *	レポート
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	レポートデータチェック
 */
//-----------------------------------------------------------------------------
	.macro	_REPORT_SAVE_CHECK ret_wk
	.short	EV_SEQ_REPORT_SAVE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	レポート書き込み
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
 *		クリップ　テレビ局データ有無チェック
 */
//-----------------------------------------------------------------------------
	.macro	_CLIP_TVSAVEDATA_CHECK pos,ret_wk
	.short	EV_SEQ_CLIP_TVSAVEDATA_CHECK
	.short	\pos
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *		クリップ　コンテストデータ有無チェック
 */
//-----------------------------------------------------------------------------
	.macro	_CLIP_CONSAVEDATA_CHECK pos,ret_wk
	.short	EV_SEQ_CLIP_CONSAVEDATA_CHECK
	.short	\pos
	.short	\ret_wk
	.endm
	

//-----------------------------------------------------------------------------
/**
 *		クリップ　テレビ局タイトル入力
 */
//-----------------------------------------------------------------------------
	.macro	_CLIP_TV_TITLE_SAVE	pos
	.short	EV_SEQ_CLIP_TV_TITLE_SAVE
	.short	\pos
	.endm

//=============================================================================
/**
 *	ポケッチ
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	ポケットゲット
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKETCH
	.short	EV_SEQ_GET_POKETCH
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケット入手フラグ済みフラグ取得
 *
 *	ANSWERに結果代入
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKETCH_FLAG ret_wk
	.short	EV_SEQ_GET_POKETCH_FLAG
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケッチソフト追加
 */
//-----------------------------------------------------------------------------
	.macro	_POKETCH_ADD	app_id
	.short	EV_SEQ_POKETCH_ADD
	.short	\app_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケッチソフト追加済みチェック
 */
//-----------------------------------------------------------------------------
	.macro	_POKETCH_CHECK	app_id,ret_wk
	.short	EV_SEQ_POKETCH_CHECK
	.short	\app_id
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	通信
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	同期
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_SYNCHRONIZE	no
	.short	EV_SEQ_COMM_TIMING_SYNC_START
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 * 　リセット	
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_RESET
	.short	EV_SEQ_COMM_TEMP_DATA_RESET
	.endm


//=============================================================================
/**
 *	ユニオンルーム
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 * ユニオンルーム　通信の親機側でカードを見る前の会話番号を取得
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_PARENT_CARD_TALK_NO	ret_wk
	.short	EV_SEQ_UNION_PARENT_CARD_TALK_NO
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ユニオンルーム　左上の人の話すメッセージIDを取得
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_GET_INFO_TALK_NO	ret_wk
	.short	EV_SEQ_UNION_GET_INFO_TALK_NO
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ユニオンルーム　ビーコン書き換え
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_BEACON_CHANGE	flag
	.short	EV_SEQ_UNION_BEACON_CHANGE
	.short	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 * ユニオンルーム　話しかけられない状態にする
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_CONNECT_TALK_DENIED
	.short	EV_SEQ_UNION_CONNECT_TALK_DENIED
	.endm

//-----------------------------------------------------------------------------
/**
 * ユニオンルーム　話しかけられる状態にする
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_CONNECT_TALK_OK
	.short	EV_SEQ_UNION_CONNECT_TALK_OK
	.endm

//-----------------------------------------------------------------------------
/**
 * ユニオンルーム内で使用する会話用にトレーナー名をセットする
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_TRAINER_NAME_REGIST	type
	.short	EV_SEQ_UNION_TRAINER_NAME_REGIST
	.short	\type
	.endm

//-----------------------------------------------------------------------------
/**
 *	フィールド用のコマンド体系に初期化
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_RETURN_SETUP
	.short	EV_SEQ_UNION_RETURN_SETUP
	.endm

//-----------------------------------------------------------------------------
/**
 *	ビーコン収集を再開する
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_CONNECT_CUT_RESTART
	.short	EV_SEQ_UNION_CONNECT_CUT_RESTART
	.endm

//-----------------------------------------------------------------------------
/**
 *	話掛けで通信接続できない時に出す会話のインデックスを取得
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_GET_TALK_NUMBER	type,ret_wk
	.short	EV_SEQ_UNION_GET_TALK_NUMBER
	.short	\type
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	話しかけOBJのIDをセット
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_ID_SET	ret_wk
	.short	EV_SEQ_UNION_ID_SET
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	話しかけで接続してみた結果を返す
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_RESULT_GET ret_wk
	.short	EV_SEQ_UNION_RESULT_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ユニオンルームのOBJを隠す
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_OBJ_ALL_VANISH
	.short	EV_SEQ_UNION_OBJ_ALL_VANISH
	.endm

//-----------------------------------------------------------------------------
/**
 * 選択した値をユニオンワークに渡す
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_SCRIPT_RESULT_SET	type,num
	.short	EV_SEQ_UNION_SCRIPT_RESULT_SET
	.short	\type
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 * 親機のスタートを待つ
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_PARENT_START_COMMAND_SET	ret_wk
	.short	EV_SEQ_UNION_PARENT_START_COMMAND_SET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * 子機の選択を待つ
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_CHILD_SELECT_COMMAND_SET	ret_wk
	.short	EV_SEQ_UNION_CHILD_SELECT_COMMAND_SET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ユニオン話しかけ接続開始
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_CONNECT_START type, ret_wk
	.short	EV_SEQ_UNION_CONNECT_START
	.short	\type
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ユニオンルームと普通のマップの間のマップ移動
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_MAP_CHANGE
	.short	EV_SEQ_UNION_MAP_CHANGE
	.endm

//-----------------------------------------------------------------------------
/**
 * 4つの選択肢のトレーナーの名前をwordsetに格納する
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_VIEW_TR_SEL_SET
	.short	EV_SEQ_UNION_VIEW_TR_SEL_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * 選択した1-4の数字をトレーナーの見た目番号に変換する → トレーナー文字列IDを取得
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_VIEW_TR_TYPE_MSG_GET	sel,ret_wk
	.short	EV_SEQ_UNION_VIEW_TR_TYPE_MSG_GET
	.short	\sel
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * 選択した1-4の数字をトレーナーの見た目番号に変換する
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_VIEW_TR_TYPE_NO_GET	sel,ret_wk
	.short	EV_SEQ_UNION_VIEW_TR_TYPE_NO_GET
	.short	\sel
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * 自分がトレーナーとして見られる時の番号をセット(ユニオンルーム用)
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_VIEW_MY_STATUS_SET	type
	.short	EV_SEQ_UNION_VIEW_MY_STATUS_SET
	.short	\type
	.endm


//=============================================================================
/**
 *	システムフラグ関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 * システムフラグ	図鑑入手済みか取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_ZUKAN_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_ZUKAN_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	図鑑セット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_ZUKAN_SET
	.short	EV_SEQ_SYS_FLAG_ZUKAN_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	シューズ入手済みか取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_SHOES_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_SHOES_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	シューズセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_SHOES_SET
	.short	EV_SEQ_SYS_FLAG_SHOES_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	バッジ入手済みか取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_BADGE_GET	no,ret_wk
	.short	EV_SEQ_SYS_FLAG_BADGE_GET
	.short	\no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	バッジセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_BADGE_SET	no
	.short	EV_SEQ_SYS_FLAG_BADGE_SET
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	バッジ入手数取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_BADGE_COUNT	ret_wk
	.short	EV_SEQ_SYS_FLAG_BADGE_COUNT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	バッグ入手済みか取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_BAG_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_BAG_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	バッグセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_BAG_SET
	.short	EV_SEQ_SYS_FLAG_BAG_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	連れ歩きフラグ取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_PAIR_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_PAIR_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	連れ歩きフラグセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_PAIR_SET
	.short	EV_SEQ_SYS_FLAG_PAIR_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	連れ歩きフラグリセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_PAIR_RESET
	.short	EV_SEQ_SYS_FLAG_PAIR_RESET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	一歩動いたかフラグ取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_ONE_STEP_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_ONE_STEP_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	一歩動いたかフラグセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_ONE_STEP_SET
	.short	EV_SEQ_SYS_FLAG_ONE_STEP_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	一歩動いたかフラグリセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_ONE_STEP_RESET
	.short	EV_SEQ_SYS_FLAG_ONE_STEP_RESET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	ゲームクリアフラグ取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_GAME_CLEAR_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_GAME_CLEAR_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	ゲームクリアフラグセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_GAME_CLEAR_SET
	.short	EV_SEQ_SYS_FLAG_GAME_CLEAR_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	かいりきセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KAIRIKI_SET
	.short	EV_SEQ_SYS_FLAG_KAIRIKI
	.byte	FLAG_MODE_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	かいりきリセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KAIRIKI_RESET
	.short	EV_SEQ_SYS_FLAG_KAIRIKI
	.byte	FLAG_MODE_RESET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	かいりき取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KAIRIKI_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_KAIRIKI
	.byte	FLAG_MODE_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	フラッシュセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_FLASH_SET
	.short	EV_SEQ_SYS_FLAG_FLASH
	.byte	FLAG_MODE_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	フラッシュリセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_FLASH_RESET
	.short	EV_SEQ_SYS_FLAG_FLASH
	.byte	FLAG_MODE_RESET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	フラッシュ取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_FLASH_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_FLASH
	.byte	FLAG_MODE_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	きりばらいセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KIRIBARAI_SET
	.short	EV_SEQ_SYS_FLAG_KIRIBARAI
	.byte	FLAG_MODE_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	きりばらいリセット
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KIRIBARAI_RESET
	.short	EV_SEQ_SYS_FLAG_KIRIBARAI
	.byte	FLAG_MODE_RESET
	.endm

//-----------------------------------------------------------------------------
/**
 * システムフラグ	きりばらい取得
 */
//-----------------------------------------------------------------------------
	.macro	_SYS_FLAG_KIRIBARAI_GET	ret_wk
	.short	EV_SEQ_SYS_FLAG_KIRIBARAI
	.byte	FLAG_MODE_GET
	.short	\ret_wk
	.endm

//=============================================================================
/**
 *	フレンドリショップ
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	変動フレンドリショップ呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_SHOP_CALL	id
	.short	EV_SEQ_SHOP_CALL
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	固定フレンドリショップ呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_FIX_SHOP_CALL	id
	.short	EV_SEQ_FIX_SHOP_CALL
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	固定グッズショップ呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_FIX_GOODS_CALL	id
	.short	EV_SEQ_FIX_GOODS_CALL
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	固定シールショップ呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_FIX_SEAL_CALL	id
	.short	EV_SEQ_FIX_SEAL_CALL
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 * アクセサリーショップ呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_ACCE_SHOP_CALL
	.short	EV_SEQ_ACCE_SHOP
	.endm

//-----------------------------------------------------------------------------
/**
 * レポート自機形態追加
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_REPORT_DRAW_SET
	.short	EV_SEQ_PLAYER_REPORT_DRAW_SET
	.endm

//-----------------------------------------------------------------------------
/**
 * レポート自機形態削除
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_REPORT_DRAW_DEL
	.short	EV_SEQ_PLAYER_REPORT_DRAW_DEL
	.endm


//=============================================================================
/**
 *	ゲームオーバー
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	ゲームオーバー呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_GAME_OVER_CALL
	.short	EV_SEQ_GAME_OVER_CALL
	.endm


//=============================================================================
/**
 *	ワープ関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	ワープIDセット
 */
//-----------------------------------------------------------------------------
	.macro	_SET_WARP_ID	id
	.short	EV_SEQ_SET_WARP_ID
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 *	主人公の性別取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_MY_SEX ret_wk
	.short	EV_SEQ_GET_MY_SEX
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケセン回復
 */
//-----------------------------------------------------------------------------
	.macro	_PC_KAIFUKU
	.short	EV_SEQ_PC_KAIFUKU
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下のNPCをランダムに配置する
 */
//-----------------------------------------------------------------------------
	.macro	_UG_MAN_SHOP_NPC_RAND_PLACE
	.short	EV_SEQ_UG_MAN_SHOP_NPC_RAND_PLACE
	.endm

//-----------------------------------------------------------------------------
/**
 *	通信ダイレクトコーナーの終了処理を開始する
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_DIRECT_END
	.short	EV_SEQ_COMM_DIRECT_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	終了処理手続き　タイミング同期版
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_DIRECT_END_TIMING
	.short	EV_SEQ_COMM_DIRECT_END_TIMING
	.endm

//-----------------------------------------------------------------------------
/**
 *	通信バトルから復帰した時に呼ぶ(もう一度歩き回りの通信を開始)
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_DIRECT_ENTER_BTL_ROOM
	.short	EV_SEQ_COMM_DIRECT_ENTER_BTL_ROOM
	.endm

//-----------------------------------------------------------------------------
/**
 *	通信した上でプレイヤーの方向を変更(地下用)
 */
//-----------------------------------------------------------------------------
	.macro	_COMM_PLAYER_SET_DIR	dir
	.short	EV_SEQ_COMM_PLAYER_SET_DIR
	.short	\dir
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	3Dアニメ関連　ドアアニメセット
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
 *	3Dアニメ関連　アニメウエイト
 */
//-----------------------------------------------------------------------------
	.macro	_WAIT_3D_ANIME	id
	.short	EV_SEQ_WAIT_3D_ANIME
	.byte \id
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	3Dアニメ関連　アニメ解放
 */
//-----------------------------------------------------------------------------
	.macro	_FREE_3D_ANIME	id
	.short	EV_SEQ_FREE_3D_ANIME
	.byte \id
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	3Dアニメ関連　ドアオープンアニメ
 */
//-----------------------------------------------------------------------------
	.macro	_SEQ_OPEN_DOOR	id
	.short	EV_SEQ_OPEN_DOOR
	.byte \id
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	3Dアニメ関連　ドアクローズアニメ
 */
//-----------------------------------------------------------------------------
	.macro	_SEQ_CLOSE_DOOR	id
	.short	EV_SEQ_CLOSE_DOOR
	.byte \id
	.endm

//=============================================================================
//
//		簡易会話呼び出し
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 * 簡易会話呼び出し（単語一つ）
 */
//-----------------------------------------------------------------------------
	.macro	_PMS_INPUT_SINGLE		ret_wk, ans_wk
	.short	EV_SEQ_PMS_INPUT_SINGLE
	.short	0	//ダミー
	.short	\ret_wk
	.short	\ans_wk
	.endm
//-----------------------------------------------------------------------------
/**
 * 簡易会話呼び出し（単語一つ）
 */
//-----------------------------------------------------------------------------
	.macro	_PMS_INPUT_DOUBLE		ret_wk, ans_wk1, ans_wk2
	.short	EV_SEQ_PMS_INPUT_DOUBLE
	.short	0	//ダミー
	.short	\ret_wk
	.short	\ans_wk1
	.short	\ans_wk2
	.endm

//-----------------------------------------------------------------------------
/**
 * 簡易会話メッセージをバッファへセット
 */
//-----------------------------------------------------------------------------
	.macro	_PMS_BUF		buf_no,wk
	.short	EV_SEQ_PMS_BUF
	.short	\buf_no
	.short	\wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	きのみ：状態取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SEED_STATUS	ret_wk
	.short	EV_SEQ_SEED_GET_STATUS
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * きのみ：種類取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SEED_TYPE		ret_wk
	.short	EV_SEQ_SEED_GET_TYPE
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * きのみ：肥料の種類取得
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
 * きのみ：生った実の数を取得
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
 *	SXYデータの座標情報を変更
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
 *	OBJデータの座標情報を変更
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
 *	SXYデータの動作コード情報を変更
 */
//-----------------------------------------------------------------------------
	.macro	_SXY_MV_CHANGE	id,mv
	.short	EV_SEQ_SXY_MV_CHANGE
	.short	\id
	.short	\mv
	.endm

//-----------------------------------------------------------------------------
/**
 *	SXYデータの方向情報を変更
 */
//-----------------------------------------------------------------------------
	.macro	_SXY_DIR_CHANGE	id,dir
	.short	EV_SEQ_SXY_DIR_CHANGE
	.short	\id
	.short	\dir
	.endm

//-----------------------------------------------------------------------------
/**
 *	SXY 接続データの座標情報を変更
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
 *	SXY BGデータの座標情報を変更
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
 *	OBJデータの方向情報を変更
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_DIR_CHANGE	id,dir
	.short	EV_SEQ_OBJ_DIR_CHANGE
	.short	\id
	.short	\dir
	.endm

//-----------------------------------------------------------------------------
/**
 *	イベント結果を代入するワークに値をセット
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
 *	育て屋にいるポケモンの名前をセットする
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SODATE_NAME
	.short	EV_SEQ_GET_SODATE_NAME
	.endm

//-----------------------------------------------------------------------------
/**
 *	育て屋の状態チェック
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SODATEYA_ZIISAN	ret_wk
	.short	EV_SEQ_GET_SODATEYA_ZIISAN
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	水ジム初期化
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_WATER_GYM
	.short	EV_SEQ_INIT_WATER_GYM
	.endm

//-----------------------------------------------------------------------------
/**
 *	水ジムギミックボタン
 */
//-----------------------------------------------------------------------------
	.macro	_PUSH_WATER_GYM_BUTTON
	.short	EV_SEQ_PUSH_WATER_GYM_BUTTON
	.endm

//-----------------------------------------------------------------------------
/**
 *	ゴーストジム初期化
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_GHOST_GYM
	.short	EV_SEQ_INIT_GHOST_GYM
	.endm

//-----------------------------------------------------------------------------
/**
 *	ゴーストジムギミックリフト
 */
//-----------------------------------------------------------------------------
	.macro	_MOVE_GHOST_GYM_LIFT
	.short	EV_SEQ_MOVE_GHOST_GYM_LIFT
	.endm

//-----------------------------------------------------------------------------
/**
 *	鋼ジム初期化
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_STEEL_GYM
	.short	EV_SEQ_INIT_STEEL_GYM
	.endm

//-----------------------------------------------------------------------------
/**
 *	格闘ジム初期化
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_COMBAT_GYM
	.short	EV_SEQ_INIT_COMBAT_GYM
	.endm

//-----------------------------------------------------------------------------
/**
 *	電気ジム初期化
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_ELEC_GYM	room
	.short	EV_SEQ_INIT_ELEC_GYM
	.byte	\room
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	電気ジムギミックギア
 */
//-----------------------------------------------------------------------------
	.macro	_ROTATE_ELEC_GYM_GEAR	rot
	.short	EV_SEQ_ROT_ELEC_GYM_GEAR
	.byte	\rot
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	ポケモン数取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKE_COUNT	ret_wk
	.short	EV_SEQ_GET_POKE_COUNT			//ポケモン数取得
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	タマゴを除いた手持ちのポケモン数
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKE_COUNT2	ret_wk
	.short	EV_SEQ_GET_POKE_COUNT2			//ポケモン数取得
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	タマゴと瀕死を除いた手持ちのポケモン数(戦闘可能なポケモン数）
 *	no = 無視する手持ち番号(6:なし、0～5)
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKE_COUNT3	ret_wk,no
	.short	EV_SEQ_GET_POKE_COUNT3			//ポケモン数取得
	.short	\ret_wk
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ち・パソコンを含めて戦えるポケモンが何体いるか。
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKE_COUNT4	ret_wk
	.short	EV_SEQ_GET_POKE_COUNT4			//ポケモン数取得
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちタマゴの数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_TAMAGO_COUNT	ret_wk
	.short	EV_SEQ_GET_TAMAGO_COUNT
	.short	\ret_wk
	.endm


//=============================================================================
/**
 *	地下お店関連
 */
//=============================================================================

//-----------------------------------------------------------------------------
/**
 *	地下のお店のメニューを開く
 */
//-----------------------------------------------------------------------------
	.macro	_UG_SHOP_MENU_INIT	type,ret_wk
	.short	EV_SEQ_UG_SHOP_MENU_INIT
	.short	\type
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下の会話開始
 */
//-----------------------------------------------------------------------------
	.macro	_UG_SHOP_TALK_START	msg
	.short	EV_SEQ_UG_SHOP_TALK_START
	.short	\msg
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下の会話終了
 */
//-----------------------------------------------------------------------------
	.macro	_UG_SHOP_TALK_END
	.short	EV_SEQ_UG_SHOP_TALK_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下のアイテム名セット
 */
//-----------------------------------------------------------------------------
	.macro	_UG_SHOP_ITEM_NAME	idx,type
	.short	EV_SEQ_UG_SHOP_ITEM_NAME
	.byte	\idx
	.short	\type
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下のトラップ名セット
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
 *	 発見されたタマゴを受け取る
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
 *	育てているポケモンの育ったレベル差をバッファへセット、またその値を返す
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
 *	引き取り処理
 *	ret_wk 引き取るポケモン
 *	no どちらを引き取るか
 */
//-----------------------------------------------------------------------------
	.macro	_HIKITORI_POKE ret_wk,no
	.short	EV_SEQ_HIKITORI_POKE
	.short	\ret_wk
	.short	\no
	.endm

//-----------------------------------------------------------------------------
/**
 *	タマゴ生まれデモ
 */
//-----------------------------------------------------------------------------
	.macro	_TAMAGO_DEMO
	.short	EV_SEQ_TAMAGO_DEMO
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちの位置ナンバーから、ポケモン番号へ変換
 *	IN:wk_in	手持ち番号を渡すワーク
 *	OUT:wk_out	ポケモン番号を受け取るワーク
 *	    OUTが"0"のときタマゴ
 */
//-----------------------------------------------------------------------------
	.macro	_TEMOTI_MONSNO	wk_in,wk_out
	.short	EV_SEQ_TEMOTI_MONSNO
	.short	\wk_in
	.short	\wk_out
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちポケモンのご主人様チェック
 *	IN:wk_in	手持ち番号を渡すワーク
 *	OUT:wk_out	所有者情報(0:自分のポケモン、1:他人のポケモン)
 */
//-----------------------------------------------------------------------------
	.macro	_MONS_OWN_CHK	wk_in,wk_out
	.short	EV_SEQ_MONS_OWN_CHK
	.short	\wk_in
	.short	\wk_out
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケルスに感染しているかのチェック
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_TEMOTI_POKERUS	wk
	.short	EV_SEQ_CHK_TEMOTI_POKERUS
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちポケモンの性別取得
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
 *	キャラを可視状態へ
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_VISIBLE obj_id
	.short	EV_SEQ_OBJ_VISIBLE
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	キャラを不可視状態へ
 */
//-----------------------------------------------------------------------------
	.macro	_OBJ_INVISIBLE obj_id
	.short	EV_SEQ_OBJ_INVISIBLE
	.short	\obj_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	メールボックス
 */
//-----------------------------------------------------------------------------
	.macro	_MAILBOX
	.short	EV_SEQ_MAILBOX
	.endm

//-----------------------------------------------------------------------------
/**
 *	メールボックス内のメール数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_MAILBOX_DATANUM	ret_wk
	.short	EV_SEQ_GET_MAILBOX_DATANUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * 　ギネスホールランキング画面呼び出し	
 */
//-----------------------------------------------------------------------------
	.macro	_RANKING_VIEW	mode
	.short	EV_SEQ_RANKING_VIEW
	.short	\mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	時間帯取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_TIME_ZONE ret_wk
	.short	EV_SEQ_GET_TIME_ZONE
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ランダム数取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_RND ret_wk,num
	.short	EV_SEQ_GET_RND
	.short	\ret_wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	ランダム数取得
 *  GET_RANDのタネを流用したまま呼びたいとき or Vsyncに変化が無い期間用
 */
//-----------------------------------------------------------------------------
	.macro	_GET_RND_NEXT ret_wk,num
	.short	EV_SEQ_GET_RND_NEXT
	.short	\ret_wk
	.short	\num
	.endm


//-----------------------------------------------------------------------------
/**
 *	なつき度取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_NATSUKI ret_wk,tno
	.short	EV_SEQ_GET_NATSUKI
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	なつき度を増やす
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_NATSUKI wk,tno
	.short	EV_SEQ_ADD_NATSUKI
	.short	\wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	なつき度を減らす
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_NATSUKI wk,tno
	.short	EV_SEQ_SUB_NATSUKI
	.short	\wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	ひきとり名前(+性別、LV)セット
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
 *　そだてや相性度合いを取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_SODATEYA_AISHOU ret_wk
	.short	EV_SEQ_GET_SODATEYA_AISHOU
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *　タマゴが産まれているかチェック
 */
//-----------------------------------------------------------------------------
	.macro	_SODATEYA_TAMAGO_CHK ret_wk
	.short	EV_SEQ_SODATEYA_TAMAGO_CHK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *　手持ちに特定のポケモンがいるかをチェック
 *  いた：TRUE　いない：FALSE
 */
//-----------------------------------------------------------------------------
	.macro	_TEMOTI_POKE_CHK	ret_wk,num
	.short	EV_SEQ_TEMOTI_POKE_CHK
	.short	\ret_wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *　おおきさくらべ：記録と手持ちポケモンの比較
 */
//-----------------------------------------------------------------------------
	.macro	_OOKISA_RECORD_CHK	ret_wk,num
	.short	EV_SEQ_OOKISA_RECORD_CHK
	.short	\ret_wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *　おおきさくらべ：手持ちのポケモンで記録更新
 */
//-----------------------------------------------------------------------------
	.macro	_OOKISA_RECORD_SET	num
	.short	EV_SEQ_OOKISA_RECORD_SET
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *　おおきさくらべ：手持ちのポケモンの大きさを数値にして文字バッファへセット
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
 *　おおきさくらべ：記録ポケモンの大きさを数値にして文字バッファへセット
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
 *　おおきさくらべ：初期化。レコードをクリア
 */
//-----------------------------------------------------------------------------
	.macro	_OOKISA_KURABE_INIT
	.short	EV_SEQ_OOKISA_KURABE_INIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	ワザ選択画面呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_WAZALIST_SET_PROC	wk
	.short	EV_SEQ_WAZALIST_SET_PROC
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 * ワザ選択画面結果取り出し
 */
//-----------------------------------------------------------------------------
	.macro	_WAZALIST_GET_RESULT	ret_wk
	.short	EV_SEQ_WAZALIST_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	持っているワザ数をカウント
 */
//-----------------------------------------------------------------------------
	.macro	_WAZA_COUNT				ret_wk,num
	.short	EV_SEQ_WAZA_COUNT
	.short	\ret_wk
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	ワザを消す
 */
//-----------------------------------------------------------------------------
	.macro	_WAZA_DEL	t_num,w_num
	.short	EV_SEQ_WAZA_DEL
	.short	\t_num
	.short	\w_num
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちのワザ番号を取得
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
 *	手持ちのワザをバッファへ
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
//	冒険ノート関連
//
//============================================================================================

//-----------------------------------------------------------------------------
/**
 *	冒険ノート開始データセット
 */
//-----------------------------------------------------------------------------
	.macro	_FNOTE_START_SET
	.short	EV_SEQ_FNOTE_START_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	冒険ノートデータ作成
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
 *	未使用
 */
//-----------------------------------------------------------------------------
	.macro	_FNOTE_DATA_SAVE
	.short	EV_SEQ_FNOTE_DATA_SAVE
	.endm


//============================================================================================
//
//	イメージクリップアイテム関連
//
//============================================================================================

//-----------------------------------------------------------------------------
/**
 *	イメージクリップ：アクセサリー：アイテムを加える
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_ACCE_ADD_ITEM	acce_no,num
	.short	EV_SEQ_IMC_ACCE_ADD_ITEM
	.short	\acce_no
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	イメージクリップ：アクセサリー：アイテムを加えられるかチェック
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
 *	イメージクリップ：アクセサリー：バッグのアイテムチェック
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
 *	イメージクリップ：背景：アイテムを加える
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_BG_ADD_ITEM	bg_no
	.short	EV_SEQ_IMC_BG_ADD_ITEM
	.short	\bg_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	イメージクリップ：背景：バッグのアイテムチェック
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_BG_ITEM_CHK		bg_no,ret_wk
	.short	EV_SEQ_IMC_BG_ITEM_CHK
	.short	\bg_no
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	まぜまぜ料理：呼び出しマクロ
 */
//-----------------------------------------------------------------------------
	.macro	_NUTMIXER_CALL			mode
	.short	EV_SEQ_NUTMIXER_CALL
	.short	\mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	まぜまぜ料理プレイ可能かチェック：呼び出しマクロ
 */
//-----------------------------------------------------------------------------
	.macro	_NUTMIXER_PLAY_CHECK	retwk
	.short	EV_SEQ_NUTMIXER_PLAY_CHECK
	.short	\retwk
	.endm

//-----------------------------------------------------------------------------
/**
 *	シンオウ図鑑が完成しているかチェック
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_CHK_SHINOU		ret_wk
	.short	EV_SEQ_ZUKAN_CHK_SHINOU
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	全国図鑑が完成しているかチェック
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_CHK_NATIONAL		ret_wk
	.short	EV_SEQ_ZUKAN_CHK_NATIONAL
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	シンオウ図鑑表彰
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_RECONGNIZE_SHINOU
	.short	EV_SEQ_ZUKAN_RECONGNIZE_SHINOU
	.endm

//-----------------------------------------------------------------------------
/**
 *	全国図鑑表彰
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_RECONGNIZE_NATIONAL
	.short	EV_SEQ_ZUKAN_RECONGNIZE_NATIONAL
	.endm

//-----------------------------------------------------------------------------
/**
 *	ウラヤマエンカウントセット
 */
//-----------------------------------------------------------------------------
	.macro	_URAYAMA_ENCOUNT_SET
	.short	EV_SEQ_URAYAMA_ENCOUNT_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	ウラヤマエンカウントチェック（現在の該当するポケモン番号取得）
 */
//-----------------------------------------------------------------------------
	.macro	_URAYAMA_ENCOUNT_NO_CHK				ret_wk
	.short	EV_SEQ_URAYAMA_ENCOUNT_NO_CHK
	.short	\ret_wk
	.endm



//-----------------------------------------------------------------------------
/**
 *	メールを持っているかチェック
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_MAIL_CHK		ret_wk,tno
	.short	EV_SEQ_POKE_MAIL_CHK
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	落とす場所を決める
 */
//-----------------------------------------------------------------------------
	.macro	_PAPERPLANE_SET			ret_wk
	.short	EV_SEQ_PAPERPLANE_SET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	持っているメールを削除
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_MAIL_DEL			tno
	.short	EV_SEQ_POKE_MAIL_DEL
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	化石が何個あるかのチェック
 */
//-----------------------------------------------------------------------------
	.macro	_KASEKI_COUNT			ret_wk
	.short	EV_SEQ_KASEKI_COUNT	
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	アイテム選択
 */
//-----------------------------------------------------------------------------
	.macro	_ITEMLIST_SET_PROC
	.short	EV_SEQ_ITEMLIST_SET_PROC
	.endm

//-----------------------------------------------------------------------------
/**
 *	選択したアイテム番号取得
 */
//-----------------------------------------------------------------------------
	.macro	_ITEMLIST_GET_RESULT		ret_wk
	.short	EV_SEQ_ITEMLIST_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	アイテム（化石）番号を、モンスター番号へ変換(0:化石ではないときは０）
 */
//-----------------------------------------------------------------------------
	.macro	_ITEMNO_TO_MONSNO		ret_wk,itemno
	.short	EV_SEQ_ITEMNO_TO_MONSNO
	.short	\ret_wk
	.short	\itemno
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちのxxx番目の化石を見つけてアイテム番号にして返す(0:最初の1個)
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
 *	ポケモンレベルチェック
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_LEVEL_CHK		ret_wk,level
	.short	EV_SEQ_POKE_LEVEL_CHK
	.short	\ret_wk
	.short	\level
	.endm



//======================================
//ここからバトルタワー関連
//======================================
//-----------------------------------------------------------------------------
/**
 *	バトルタワーアプリ呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_APP_CALL	main,sub
	.short	EV_SEQ_BTOWER_APP_CALL
	.short	\main
	.short	\sub
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルタワーワーク初期化
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_WORK_CLEAR
	.short	EV_SEQ_BATTLE_TOWER_WORK_CLEAR
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルタワーワーク確保＆初期化
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_WORK_INIT		init,mode
	.short	EV_SEQ_BATTLE_TOWER_WORK_INIT
	.short	\init
	.short	\mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルタワーワーク解放
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_WORK_RELEASE
	.short	EV_SEQ_BATTLE_TOWER_WORK_RELEASE
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルタワー コマンドツール呼び出し
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
 *	バトルタワー 5人衆のポケモンデータ取得
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_SEVEN_POKE_GET	id,idx,ret_poke,ret_waza
	.short	EV_SEQ_BATTLE_TOWER_GET_SEVEN_POKE	//5人衆のポケモンデータゲット
	.short	\id
	.short	\idx
	.short	\ret_poke
	.short	\ret_waza
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルタワー プライズを取得
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_PRIZE_GET	ret_wk
	.short	EV_SEQ_BATTLE_TOWER_IS_PRIZE_GET	//バトルタワー　プライズ取得
	.short	\ret_wk
	.endm
//-----------------------------------------------------------------------------
/**
 *	バトルタワー プライズをくれる人物をセット
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_PRIZEMAN_SET	ret_wk
	.short	EV_SEQ_BATTLE_TOWER_IS_PRIZEMAN_SET
	.short	\ret_wk
	.endm
//-----------------------------------------------------------------------------
/**
 *	バトルタワー 汎用データ送信
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_SEND_BUF	mode,param
	.short	EV_SEQ_BATTLE_TOWER_SEND_BUF
	.short	\mode
	.short	\param
	.endm
//-----------------------------------------------------------------------------
/**
 *	バトルタワー 汎用データ受信
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_RECV_BUF	mode,ret_wk
	.short	EV_SEQ_BATTLE_TOWER_RECV_BUF
	.short	\mode
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルタワー リーダーデータRoomID取得
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_GET_LEADER_ROOMID	ret_rank,ret_no
	.short	EV_SEQ_BATTLE_TOWER_GET_LEADER_ROOM_ID
	.short	\ret_rank
	.short	\ret_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルタワー リーダーデータが存在するかどうか？
 */
//-----------------------------------------------------------------------------
	.macro	_BTOWER_IS_LEADER_EXIST	ret_wk
	.short	EV_SEQ_BATTLE_TOWER_IS_READER_DATA_EXIST	//バトルタワー　リーダーデータの有無
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
//レコード関連
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *	レコードインクリメント
 */
//-----------------------------------------------------------------------------
//	.macro	_RECORD_INC	cmd,recid
	.macro	_RECORD_INC	recid
	.short	EV_SEQ_RECORD_INC
	.short	\recid
	.endm
//-----------------------------------------------------------------------------
/**
 *	レコードゲット
 *
 *	recid:RECID_XXXXX
 *	h_wk:上位バイト取得ワーク
 *	l_wk:下位バイト取得ワーク
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
 *	レコードAdd
 *
 *	recid:RECID_XXXXX
 *	h_val:上位バイト
 *	l_val:下位バイト
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
 *	レコードSet
 *
 *	recid:RECID_XXXXX
 *	h_val:上位バイト
 *	l_val:下位バイト
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
 *	レコードSetIfLarge
 *
 *	recid:RECID_XXXXX
 *	h_val:上位バイト
 *	l_val:下位バイト
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
//		サファリ関連
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 *	サファリ開始	
 */
//-----------------------------------------------------------------------------
	.macro	_SAFARI_START
	.short	EV_SEQ_SAFARI_CTRL
	.byte	0
	.endm

//-----------------------------------------------------------------------------
/**
 *	サファリ終了
 */
//-----------------------------------------------------------------------------
	.macro	_SAFARI_END
	.short	EV_SEQ_SAFARI_CTRL
	.byte	1
	.endm

//-----------------------------------------------------------------------------
/**
 *	サファリ望遠鏡
 */
//-----------------------------------------------------------------------------
	.macro	_CALL_SAFARI_SCOPE
	.short	EV_SEQ_CALL_SAFARI_SCOPE
	.endm


//============================================================================================
//
//		テンガンザン山頂デモ
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
 *	サファリ電車初期化
 */
//-----------------------------------------------------------------------------
	.macro	_INIT_SAFARI_TRAIN
	.short	EV_SEQ_INIT_SAFARI_TRAIN
	.endm

//-----------------------------------------------------------------------------
/**
 *	サファリ電車移動
 */
//-----------------------------------------------------------------------------
	.macro	_MOVE_SAFARI_TRAIN	pos, type
	.short	EV_SEQ_MOVE_SAFARI_TRAIN
	.short	\pos
	.short	\type
	.endm

//-----------------------------------------------------------------------------
/**
 *	サファリ電車位置チェック
 */
//-----------------------------------------------------------------------------
	.macro	_CHECK_SAFARI_TRAIN	pos, ret_wk
	.short	EV_SEQ_CHECK_SAFARI_TRAIN
	.short	\pos
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	自機高さ取得有効有無
 */
//-----------------------------------------------------------------------------
	.macro	_PLAYER_HEGIHT_VALID valid
	.short	EV_SEQ_PLAYER_HEGIHT_VALID
	.byte	\valid
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケモンの性格をゲット
 */
//-----------------------------------------------------------------------------
	.macro	_GET_POKE_SEIKAKU ret_wk,tno
	.short	EV_SEQ_GET_POKE_SEIKAKU
	.short \ret_wk
	.short \tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	特定の性格のポケモンがいるかをチェック
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_POKE_SEIKAKU_ALL ret_wk,seikaku_no
	.short	EV_SEQ_CHK_POKE_SEIKAKU_ALL
	.short \ret_wk
	.short \seikaku_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下で会話した人数の累計(ミカゲ専用版）
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_TALK_COUNT	ret_wk
	.short	EV_SEQ_UNDERGROUND_TALK_COUNT
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	自然公園歩数カウントクリア
 */
//-----------------------------------------------------------------------------
	.macro	_NATURAL_PARK_WALK_COUNT_CLEAR
	.short	EV_SEQ_NATURAL_PARK_WALK_COUNT_CLEAR
	.endm

//-----------------------------------------------------------------------------
/**
 *	自然公園歩数チェック
 */
//-----------------------------------------------------------------------------
	.macro	_NATURAL_PARK_WALK_COUNT_GET	ret_wk
	.short	EV_SEQ_NATURAL_PARK_WALK_COUNT_GET
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	自然公園で貰えるアクセサリー番号取得
 */
//-----------------------------------------------------------------------------
	.macro	_NATURAL_PARK_ACCESSORY_NO_GET		ret_wk,mon_wk
	.short	EV_SEQ_NATURAL_PARK_ACCESSORY_NO_GET
	.short \ret_wk
	.short \mon_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	新聞社：つれてくるポケモン番号取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_NEWS_POKE_NO				ret_wk
	.short	EV_SEQ_GET_NEWS_POKE_NO
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	新聞社：締め切りまでの残り日数セット
 */
//-----------------------------------------------------------------------------
	.macro	_NEWS_COUNT_SET		no
	.short	EV_SEQ_NEWS_COUNT_SET
	.short \no
	.endm

//-----------------------------------------------------------------------------
/**
 *	新聞社：締め切りまでの残り日数チェック
 */
//-----------------------------------------------------------------------------
	.macro	_NEWS_COUNT_CHK				ret_wk
	.short	EV_SEQ_NEWS_COUNT_CHK
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	大量発生開始
 */
//-----------------------------------------------------------------------------
	.macro	_START_GENERATE
	.short	EV_SEQ_START_GENERATE
	.endm

//-----------------------------------------------------------------------------
/**
 *	移動ポケモン登録
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_MOVE_POKE		poke
	.short	EV_SEQ_ADD_MOVE_POKE
	.byte	\poke
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケモンに教えられるわざ個数を取得	※仕様変更により未完成
 */
//-----------------------------------------------------------------------------
	.macro	_OSHIE_WAZA_COUNT		ret_wk,tno
	.short	EV_SEQ_OSHIE_WAZA_COUNT
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケモンが思い出せるわざ個数を取得
 */
//-----------------------------------------------------------------------------
	.macro	_REMAIND_WAZA_COUNT		ret_wk,tno
	.short	EV_SEQ_REMAIND_WAZA_COUNT
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	わざ教え選択画面呼び出し	※仕様変更により未完成
 */
//-----------------------------------------------------------------------------
	.macro	_OSHIE_WAZALIST_SET_PROC	wk
	.short	EV_SEQ_OSHIE_WAZALIST_SET_PROC
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	わざ思い出し選択画面呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_REMAIND_WAZALIST_SET_PROC	wk
	.short	EV_SEQ_REMAIND_WAZALIST_SET_PROC
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	わざ教え選択画面結果取り出し※仕様変更により未完成
 */
//-----------------------------------------------------------------------------
	.macro	_OSHIE_WAZALIST_GET_RESULT	ret_wk
	.short	EV_SEQ_OSHIE_WAZALIST_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	わざ思い出し選択画面結果取り出し
 */
//-----------------------------------------------------------------------------
	.macro	_REMAIND_WAZALIST_GET_RESULT	ret_wk
	.short	EV_SEQ_REMAIND_WAZALIST_GET_RESULT
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	1個のみのわざ教え選択画面呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_NORMAL_WAZALIST_SET_PROC	wk,waza
	.short	EV_SEQ_NORMAL_WAZALIST_SET_PROC
	.short	\wk
	.short	\waza
	.endm

//-----------------------------------------------------------------------------
/**
 *	1個のみのわざ教え選択画面結果取り出し
 */
//-----------------------------------------------------------------------------
	.macro	_NORMAL_WAZALIST_GET_RESULT	ret_wk
	.short	EV_SEQ_NORMAL_WAZALIST_GET_RESULT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	交換データ作成
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_TRADE_ALLOC	tradeno
	.short	EV_SEQ_FLD_TRADE_ALLOC
	.byte	\tradeno
	.endm

//-----------------------------------------------------------------------------
/**
 *	くれるポケモンナンバー取得
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_TRADE_MONSNO	ret_wk
	.short	EV_SEQ_FLD_TRADE_MONSNO
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	わたすポケモンナンバー取得
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_TRADE_CHG_MONSNO	ret_wk
	.short	EV_SEQ_FLD_TRADE_CHG_MONSNO
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	交換データイベント
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_TRADE_EVENT	pos
	.short	EV_SEQ_FLD_TRADE_EVENT
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	交換データ削除
 */
//-----------------------------------------------------------------------------
	.macro	_FLD_TRADE_DEL
	.short	EV_SEQ_FLD_TRADE_DEL
	.endm

//-----------------------------------------------------------------------------
/**
 *	図鑑テキストVerUp
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_TEXT_VER_UP
	.short	EV_SEQ_ZUKAN_TEXT_VER_UP
	.endm

//-----------------------------------------------------------------------------
/**
 *	図鑑性別VerUp
 */
//-----------------------------------------------------------------------------
	.macro	_ZUKAN_SEX_VER_UP
	.short	EV_SEQ_ZUKAN_SEX_VER_UP
	.endm

//-----------------------------------------------------------------------------
/**
 *	全国図鑑フラグ操作
 */
//-----------------------------------------------------------------------------
	.macro	_ZENKOKU_ZUKAN_FLAG	mode,ret_wk
	.short	EV_SEQ_ZENKOKU_ZUKAN_FLAG
	.byte	\mode
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	「リボン」の取得数（１ポケモン）
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_RIBBON_COUNT		ret_wk,tno
	.short	EV_SEQ_CHK_RIBBON_COUNT
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	「リボン」の取得数（全手持ちポケモン合計の種類）
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_RIBBON_COUNT_ALL		ret_wk
	.short	EV_SEQ_CHK_RIBBON_COUNT_ALL
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	「リボン」をもっているか
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
 *	「リボン」をセット
 */
//-----------------------------------------------------------------------------
	.macro	_SET_RIBBON		tno,rno
	.short	EV_SEQ_SET_RIBBON
	.short	\tno
	.short	\rno
	.endm

//-----------------------------------------------------------------------------
/**
 *	「リボン」名をバッファへセット
 */
//-----------------------------------------------------------------------------
	.macro	_RIBBON_NAME		idx,rno
	.short	EV_SEQ_RIBBON_NAME
	.byte	\idx
	.short	\rno
	.endm

//-----------------------------------------------------------------------------
/**
 *	努力値を取得
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_PRMEXP	ret_wk,tno
	.short	EV_SEQ_CHK_PRMEXP
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	曜日チェック
 */
//-----------------------------------------------------------------------------
	.macro	_CHK_WEEK	ret_wk
	.short	EV_SEQ_CHK_WEEK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	トピック生成：隠しアイテム発見！
 */
//-----------------------------------------------------------------------------
	.macro	_TV_ENTRY_WATCH_HIDE_ITEM	item_no
	.short	EV_SEQ_TV_ENTRY_WATCH_HIDE_ITEM
	.short	\item_no
	.endm

//-----------------------------------------------------------------------------
/**
 *	トピック生成：姓名判断
 */
//-----------------------------------------------------------------------------
	.macro	_TV_ENTRY_WATCH_CHANGE_NAME	mons_pos
	.short	EV_SEQ_TV_ENTRY_WATCH_CHANGE_NAME
	.short	\mons_pos
	.endm

//-----------------------------------------------------------------------------
/**
 *	レギュレーションルールブック
 */
//-----------------------------------------------------------------------------
	.macro	_REGULATION_LIST_CALL	ret_wk
	.short	EV_SEQ_REGULATION_LIST_CALL
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	足跡チェック
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
 *	ポケセン回復マシンアニメ
 */
//-----------------------------------------------------------------------------
	.macro	_PC_RECOVER_ANM	ball_num
	.short	EV_SEQ_PC_RECOVER_ANM
	.short	\ball_num
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	エレベーターアニメ
 */
//-----------------------------------------------------------------------------
	.macro	_ELEVATOR_ANM	dir, loop
	.short	EV_SEQ_ELEVATOR_ANM
	.short	\dir
	.short	\loop
	.endm

//-----------------------------------------------------------------------------
/**
 *	船デモコール
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
 *	デバッグ専用命令　ワークの中身
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_PRINT_WORK	wk
	.short	EV_SEQ_DEBUG_PRINT_WORK	
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	デバッグ専用命令　フラグの値を表示
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_PRINT_FLAG	num
	.short	EV_SEQ_DEBUG_PRINT_FLAG
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	デバッグ専用命令(常駐領域版。いつでも使用OK）　ワークの中身
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_PRINT_WORK_STATIONED	wk
	.short	EV_SEQ_DEBUG_PRINT_WORK_STATIONED
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	デバッグ専用命令(常駐領域版。いつでも使用OK）　フラグの中身
 */
//-----------------------------------------------------------------------------
	.macro	_DEBUG_PRINT_FLAG_STATIONED	num
	.short	EV_SEQ_DEBUG_PRINT_FLAG_STATIONED
	.short	\num
	.endm

//-----------------------------------------------------------------------------
/**
 *	バージョン取得
 */
//-----------------------------------------------------------------------------
	.macro	_PM_VERSION_GET	ret_wk
	.short	EV_SEQ_PM_VERSION_GET
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	先頭のポケモンを返す（タマゴを抜かした）
 */
//-----------------------------------------------------------------------------
	.macro	_FRONT_POKEMON	ret_wk
	.short	EV_SEQ_FRONT_POKEMON	
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちのポケモンタイプ取得
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
 *	あいことばに該当する壁紙を有効に
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
 *	地下で取得したハタの総数取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_UG_HATA_NUM		ret_wk
	.short	EV_SEQ_GET_UG_HATA_NUM
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	パソコンアニメセットアップ
 */
//-----------------------------------------------------------------------------
	.macro	_SETUP_PASO_ANM		id
	.short	EV_SEQ_SETUP_PASO_ANM
	.byte \id
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	パソコンつけるアニメ
 */
//-----------------------------------------------------------------------------
	.macro	_START_PASO_ON_ANM	id
	.short	EV_SEQ_START_PASO_ON_ANM
	.byte \id
	.endm

//-----------------------------------------------------------------------------
/**
 *	パソコン消すアニメ
 */
//-----------------------------------------------------------------------------
	.macro	_START_PASO_OFF_ANM id
	.short	EV_SEQ_START_PASO_OFF_ANM
	.byte \id
	.endm

//-----------------------------------------------------------------------------
/**
 *	くじあたり番号ゲット
 */
//-----------------------------------------------------------------------------
	.macro	_GET_KUJI_ATARI_NUM	ret_wk
	.short	EV_SEQ_GET_KUJI_ATARI_NUM
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	くじあたりチェック
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
 *	くじあたり番号初期化
 */
//-----------------------------------------------------------------------------
	.macro	_KUJI_ATARI_INIT
	.short	EV_SEQ_KUJI_ATARI_INIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	PC上のポケモンのニックネーム
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
 * インタビュアーの出現チェック
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
//			ポケパーク関連
//
//
//============================================================================================
//-----------------------------------------------------------------------------
///		ボックスの空きを数える
//-----------------------------------------------------------------------------
	.macro	_COUNT_MONSBOX_SPACE	ret_wk
	.short	EV_SEQ_COUNT_POKEBOX_SPACE
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
///		ポケパークゲーム制御
//-----------------------------------------------------------------------------
	.macro	_POKEPARK_CONTROL	id
	.short	EV_SEQ_POKEPARK_CONTROL
	.short	\id
	.endm

//-----------------------------------------------------------------------------
///		ポケパークに預けているポケモンの数を数える
//-----------------------------------------------------------------------------
	.macro	_POKEPARK_DEPOSIT_COUNT	ret_wk
	.short EV_SEQ_COUNT_POKEPARK_BOX
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
///		ポケパークに預けたポケモンをボックスに転送
//-----------------------------------------------------------------------------
	.macro	_POKEPARK_TRANS_MONS
	.short	EV_SEQ_TRANS_POKEPARK_MONS
	.endm

//-----------------------------------------------------------------------------
///		ポケパークゲームの結果スコア取得
//-----------------------------------------------------------------------------
	.macro	_POKEPARK_GET_SCORE		type, ret_wk
	.short	EV_SEQ_GET_POKEPARK_SCORE
	.short	\type
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
///		殿堂マシン上ボールアニメ
//-----------------------------------------------------------------------------
	.macro	_DENDOU_BALL_ANM	ball_num
	.short	EV_SEQ_DENDOU_BALL_ANM
	.short	\ball_num
	.endm
	
//-----------------------------------------------------------------------------
///		フィールドリフト初期化
//-----------------------------------------------------------------------------
	.macro	_INIT_FLD_LIFT
	.short	EV_SEQ_INIT_FLD_LIFT
	.endm

//-----------------------------------------------------------------------------
///		フィールドリフト移動
//-----------------------------------------------------------------------------
	.macro	_MOVE_FLD_LIFT
	.short	EV_SEQ_MOVE_FLD_LIFT
	.endm

//-----------------------------------------------------------------------------
///		フィールドリフトチェック
//-----------------------------------------------------------------------------
	.macro	_CHECK_FLD_LIFT		ret_wk
	.short	EV_SEQ_CHECK_FLD_LIFT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
///		レイアイハイ　シリンダーアニメセットアップ
//-----------------------------------------------------------------------------
	.macro	_SETUP_RAH_CYL
	.short	EV_SEQ_SETUP_RAH_CYL
	.endm

//-----------------------------------------------------------------------------
///		レイアイハイ　シリンダーアニメスタート
//-----------------------------------------------------------------------------
	.macro	_START_RAH_CYL
	.short	EV_SEQ_START_RAH_CYL
	.endm

//-----------------------------------------------------------------------------
///		スコア加算
//-----------------------------------------------------------------------------
	.macro	_ADD_SCORE	score_id
	.short	EV_SEQ_ADD_SCORE
	.short	\score_id
	.endm
//-----------------------------------------------------------------------------
/**
 *	「アクセサリー」名をバッファへセット
 */
//-----------------------------------------------------------------------------
	.macro	_ACCE_NAME		idx,acceno
	.short	EV_SEQ_ACCE_NAME
	.byte	\idx
	.short	\acceno
	.endm


//-----------------------------------------------------------------------------
///		パーティ内に指定したポケモンがいるかチェック
//-----------------------------------------------------------------------------
	.macro	_PARTY_MONSNO_CHECK	monsno, ret_wk
	.short	EV_SEQ_PARTY_MONSNO_CHECK
	.short	\monsno
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
///		パーティ内のデオキシスのフォルムを変更
//-----------------------------------------------------------------------------
	.macro	_PARTY_DEOKISISUFORM_CHANGE	form
	.short	EV_SEQ_PARTY_DEOKISISUFORM_CHANGE
	.short	\form
	.endm

//-----------------------------------------------------------------------------
///		パーティ内にミノムッチ3形態そろったかチェック
//-----------------------------------------------------------------------------
	.macro	_CHECKMINOMUCHICOMP	ret_wk
	.short	EV_SEQ_CHECKMINOMUCHICOMP
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケッチをフックする
 */
//-----------------------------------------------------------------------------
	.macro	_POKETCH_HOOK_SET
	.short	EV_SEQ_POKETCH_HOOK_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポケッチのフックを解除する
 */
//-----------------------------------------------------------------------------
	.macro	_POKETCH_HOOK_RESET
	.short	EV_SEQ_POKETCH_HOOK_RESET
	.endm


//-----------------------------------------------------------------------------
/**
 * スロットマシーン
 */
//-----------------------------------------------------------------------------
	.macro	_SLOT_MACHINE	id
	.short	EV_SEQ_SLOT_MACHINE
	.short	\id
	.endm

//-----------------------------------------------------------------------------
/**
 * 現在の時刻（時間:0-23)
 */
//-----------------------------------------------------------------------------
	.macro	_GET_NOW_HOUR	ret_wk
	.short	EV_SEQ_GET_NOW_HOUR
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * フィールドOBJを揺らすアニメーション
 */
//-----------------------------------------------------------------------------
	.macro	_FLDOBJ_SHAKE_ANM	objid,count,spd,ofsx,ofsz
	.short	EV_SEQ_FLDOBJ_SHAKE_ANM		//フィールドOBJを揺らすアニメ
	.short	\objid
	.short	\count
	.short	\spd
	.short	\ofsx
	.short	\ofsz
	.endm

//-----------------------------------------------------------------------------
/**
 * フィールドOBJをblinkさせるアニメ
 */
//-----------------------------------------------------------------------------
	.macro	_FLDOBJ_BLINK_ANM	objid,count,time
	.short	EV_SEQ_FLDOBJ_BLINK_ANM		//フィールドOBJをblinkアニメ
	.short	\objid
	.short	\count
	.short	\time
	.endm

//-----------------------------------------------------------------------------
/**
 * d20r0106 レジキング解放条件チェック
 */
//-----------------------------------------------------------------------------
	.macro	_D20R0106_LEGEND_IS_UNSEAL	ret_val
	.short	EV_SEQ_D20R0106_LEGEND_IS_UNSEAL	//レジキング解放チェック
	.short	\ret_val
	.endm


//-----------------------------------------------------------------------------
/**
 * お洒落お姉さん：ランダムでイメージクリップのアクセサリー取得
 *  ret_wk = 取得したアクセサリーの番号、　0xffff＝取得出来なかった
 */
//-----------------------------------------------------------------------------
	.macro	_DRESSING_IMC_ACCE_CHECK	ret_wk
	.short	EV_SEQ_DRESSING_IMC_ACCE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * アンノーン文字でメッセージ表示
 */
//-----------------------------------------------------------------------------
	.macro		_UNKNOWN_MSG	msg_id
	.short		EV_SEQ_UNKNOWN_MSG
	.short		\msg_id
	.endm



//-----------------------------------------------------------------------------
/**
 *	ささっているAGBカートリッジバージョン取得
 */
//-----------------------------------------------------------------------------
	.macro	_AGB_CARTRIDGE_VER_GET	ret_val
	.short	EV_SEQ_AGB_CARTRIDGE_VER_GET
	.short	\ret_val
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下で会話した人数の累計をクリア
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_TALK_COUNT_CLEAR
	.short	EV_SEQ_UNDERGROUND_TALK_COUNT_CLEAR
	.endm

//-----------------------------------------------------------------------------
/**
 *	隠しマップステータスチェンジ
 */
//-----------------------------------------------------------------------------
	.macro	_HIDEMAP_STATE_CHG	hidemap_id,flag
	.short	EV_SEQ_HIDEMAP_STATE_CHANGE		//隠しマップステータスチェンジ
	.short	\hidemap_id
	.byte	\flag
	.endm
//-----------------------------------------------------------------------------
/**
 *	r224石碑名入力呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_NAMEIN_MONUMENT	ret_wk
	.short	EV_SEQ_NAMEIN_MONUMENT			//r224石碑名入力
	.short	\ret_wk
	.endm
	
//-----------------------------------------------------------------------------
/**
 *	r224石碑名タグ展開
 */
//-----------------------------------------------------------------------------
	.macro	_MONUMENT_NAME	idx
	.short	EV_SEQ_MONUMENT_NAME			//r224石碑名タグ展開
	.byte	\idx
	.endm

//-----------------------------------------------------------------------------
/**
 *	イメージクリップ「背景」名をバッファへセット
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_BG_NAME		idx,bgno
	.short	EV_SEQ_IMC_BG_NAME_SET
	.byte	\idx
	.short	\bgno
	.endm

//-----------------------------------------------------------------------------
/**
 *	コインを調べる（引数分持っているかを返す）
 */
//-----------------------------------------------------------------------------
	.macro	_COMP_COIN ret_wk,val
	.short	EV_SEQ_COMP_COIN
	.short	\ret_wk
	.long	\val
	.endm

//-----------------------------------------------------------------------------
/**
 * スロットでレンチャンしているか
 * TRUE=10回以上 FALSE=10より下
 */
//-----------------------------------------------------------------------------
	.macro	_SLOT_RENTYAN_CHK ret_wk
	.short	EV_SEQ_SLOT_RENTYAN_CHK 
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	コインを増やせるかどうかをチェック
 *	TRUE　増やせる / FALSE 増やせない
 */
//-----------------------------------------------------------------------------
	.macro	_ADD_COIN_CHK ret_wk,val
	.short	EV_SEQ_ADD_COIN_CHK
	.short	\ret_wk
	.long	\val
	.endm

//-----------------------------------------------------------------------------
/**
 * 数字とレベルが一致したらアイテムをくれる爺のナンバー
 * 
 */
//-----------------------------------------------------------------------------
	.macro	_LEVEL_JIJII_NO ret_wk
	.short	EV_SEQ_LEVEL_JIJII_NO 
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちポケモンレベルゲット
 */
//-----------------------------------------------------------------------------
	.macro	_POKE_LEVEL_GET		ret_wk,tno
	.short	EV_SEQ_POKE_LEVEL_GET
	.short	\ret_wk
	.short	\tno
	.endm

//-----------------------------------------------------------------------------
/**
 *	イメージクリップ：アクセサリー：アイテムを減らす
 */
//-----------------------------------------------------------------------------
	.macro	_IMC_ACCE_SUB_ITEM	acce_no,num
	.short	EV_SEQ_IMC_ACCE_SUB_ITEM
	.short	\acce_no
	.short	\num
	.endm


//-----------------------------------------------------------------------------
/**
 *	ナギサシティ　シルベノ灯台　カメラ設定
 */
//-----------------------------------------------------------------------------
	.macro	_C08R0801SCOPECAMERASET
	.short	EV_SEQ_C08R0801SCOPECAMERASET
	.endm

//-----------------------------------------------------------------------------
/**
 *	レベルジジイ初期化
 */
//-----------------------------------------------------------------------------
	.macro	_LEVEL_JIJII_INIT
	.short	EV_SEQ_LEVEL_JIJII_INIT
	.endm

//-----------------------------------------------------------------------------
/**
 *	難解ことばをランダムでひとつ覚えさせる
 */
//-----------------------------------------------------------------------------
	.macro	_NEW_NANKAI_WORD_SET	ret_wk,buf_id
	.short	EV_SEQ_NEW_NANKAI_WORD_SET
	.short	\ret_wk
	.short	\buf_id
	.endm

//-----------------------------------------------------------------------------
/**
 *	常連チェック
 */
//-----------------------------------------------------------------------------
	.macro	_REGULAR_CHECK		ret_wk
	.short	EV_SEQ_REGULAR_CHECK		
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	難解ことばを全て覚えているかチェック
 */
//-----------------------------------------------------------------------------
	.macro	_NEW_NANKAI_WORD_COMPLETE_CHECK	ret_wk
	.short	EV_SEQ_NANKAI_WORD_COMPLETE_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	手持ちポケモンのコンテストステータス取得(かっこよさ、かわいさ等)
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
 *	d17戻らずの洞窟　マップ抽選
 */
//-----------------------------------------------------------------------------
	.macro	_D17SYSTEM_MAP_SELECT	point,total
	.short	EV_SEQ_D17SYSTEM_MAP_SELECT		//D17戻らずの洞窟　マップ抽選
	.short	\point
	.short	\total
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下で道具をあげた人数の累計
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_TOOL_GIVE_COUNT	ret_wk
	.short	EV_SEQ_UNDERGROUND_TOOL_GIVE_COUNT
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下でかせきを掘った回数の累計
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_KASEKI_DIG_COUNT	ret_wk
	.short	EV_SEQ_UNDERGROUND_KASEKI_DIG_COUNT
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下でトラップにかけた回数の累計
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_TRAP_HIT_COUNT	ret_wk
	.short	EV_SEQ_UNDERGROUND_TRAP_HIT_COUNT
	.short \ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	ポフィン追加
 */
//-----------------------------------------------------------------------------
	.macro	_POFIN_ADD	ret_wk,spicy,astr,sweet,bitter,sour,taste
	.short	EV_SEQ_POFIN_ADD
	.short	\ret_wk
	.byte	\spicy		//辛い
	.byte	\astr		//渋い
	.byte	\sweet		//甘い
	.byte	\bitter		//苦い
	.byte	\sour		//酸っぱい
	.byte	\taste		//旨み
	.endm

//-----------------------------------------------------------------------------
/**
 *	ポフィンが追加出来るかチェック
 */
//-----------------------------------------------------------------------------
	.macro	_POFIN_ADD_CHK	ret_wk
	.short	EV_SEQ_POFIN_ADD_CHK
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *	配布イベント有効チェック
 */
//-----------------------------------------------------------------------------
	.macro	_IS_HAIHU_EVENT_ENABLE	id,ret_wk
	.short	EV_SEQ_IS_HAIHU_EVENT_ENABLE	//配布イベント有効チェック
	.byte	\id
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	そだてやポケモン選択画面呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_SODATEYA_POKELIST_SET_PROC		pos
	.short	EV_SEQ_SODATEYA_POKELIST_SET_PROC
	.short	\pos
	.endm

//-----------------------------------------------------------------------------
/**
 * そだてやポケモン選択画面結果取り出し
 */
//-----------------------------------------------------------------------------
	.macro	_SODATEYA_POKELIST_GET_RESULT	ret_wk,ret_mode
	.short	EV_SEQ_SODATEYA_POKELIST_GET_RESULT
	.short	\ret_wk
	.short	\ret_mode
	.endm

//-----------------------------------------------------------------------------
/**
 *	指定した確立でTRUE,FALSEを返す
 */
//-----------------------------------------------------------------------------
	.macro	_GET_RANDOM_HIT	per,ret_wk
	.short	EV_SEQ_GET_RANDOM_HIT	//指定した確立でTRUE,FALSEを返す
	.byte	\per			//0-100%
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	地下で会話した人数の累計
 */
//-----------------------------------------------------------------------------
	.macro	_UNDERGROUND_TALK_COUNT2	ret_wk
	.short	EV_SEQ_UNDERGROUND_TALK_COUNT2
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	ヒデン技開始
 */
//-----------------------------------------------------------------------------
	.macro _HIDENEFF_START	eff_no, ret_wk
	.short EV_SEQ_HIDENEFF_START
	.short \eff_no
	.short \ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	地震開始
 */
//-----------------------------------------------------------------------------
	.macro _ZISHIN	no
	.short EV_SEQ_ZISHIN
	.short	\no
	.endm


//-----------------------------------------------------------------------------
/**
 *	バトルポイントウィンドウ表示
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_POINT_WIN_WRITE	x,y
	.short	EV_SEQ_BTL_POINT_WIN_WRITE
	.byte	\x
	.byte	\y
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルポイントウィンドウ削除
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_POINT_WIN_DEL
	.short	EV_SEQ_BTL_POINT_WIN_DEL
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルポイントウィンドウ再描画
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_POINT_WRITE
	.short	EV_SEQ_BTL_POINT_WRITE
	.endm

//-----------------------------------------------------------------------------
/**
 *	所持バトルポイント取得
 */
//-----------------------------------------------------------------------------
	.macro	_GET_BTL_POINT	ret_wk
	.short	EV_SEQ_GET_BTL_POINT
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	所持バトルポイント加算
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_POINT_ADD	value
	.short	EV_SEQ_BTL_POINT_ADD
	.short	\value
	.endm

//-----------------------------------------------------------------------------
/**
 *	所持バトルポイント減算
 */
//-----------------------------------------------------------------------------
	.macro	_BTL_POINT_SUB	value
	.short	EV_SEQ_BTL_POINT_SUB
	.short	\value
	.endm

//-----------------------------------------------------------------------------
/**
 *	所持バトルポイントを指定値と比較
 */
//-----------------------------------------------------------------------------
	.macro	_COMP_BTL_POINT	value,ret_wk
	.short	EV_SEQ_COMP_BTL_POINT
	.short	\value
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	バトルポイントと引き換え可能なアイテム情報を取得
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
 * 地下用特殊アイテムのチェック
 * ※アイテムボール取得時の専用命令
 */
//-----------------------------------------------------------------------------
	.macro	_UG_BALLITEM_CHECK	item
	.short	EV_SEQ_UG_BALL_CHECK
	.short	\item
	.endm

//-----------------------------------------------------------------------------
/**
 * アウスのプレートのチェック
 * ※アイテムボール取得時の専用命令
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
 *	コインと引き換え可能なアイテム情報を取得
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
 *	コイン減らす(ワーク専用版）
 */
//-----------------------------------------------------------------------------
	.macro	_SUB_WK_COIN		wk
	.short	EV_SEQ_SUB_WK_COIN
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	コインを調べる（引数分持っているかを返す）　ワーク専用版
 */
//-----------------------------------------------------------------------------
	.macro	_COMP_WK_COIN ret_wk,wk
	.short	EV_SEQ_COMP_WK_COIN
	.short	\ret_wk
	.short	\wk
	.endm

//-----------------------------------------------------------------------------
/**
 *	あいことばがオクリモノフラグ有効に該当するか
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
 *	WIFIふしぎなおくりものオープンフラグセット
 */
//-----------------------------------------------------------------------------
	.macro	_WIFI_HUSIGINAOKURIMONO_OPEN_FLAG_SET
	.short	EV_SEQ_WIFI_HUSIGINAOKURIMONO_OPEN_FLAG_SET
	.endm

//-----------------------------------------------------------------------------
/**
 *	ユニオン関連
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_GET_CARD_TALK_NO ret_wk
	.short	EV_SEQ_UNION_GET_CARD_TALK_NO
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 *		WirelessIconEasy関数呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_WIRELESS_ICON_EASY
	.short	EV_SEQ_WIRELESS_ICON_EASY
	.endm

//-----------------------------------------------------------------------------
/**
 *		WirelessIconEasyEnd関数呼び出し
 */
//-----------------------------------------------------------------------------
	.macro	_WIRELESS_ICON_EASY_END
	.short	EV_SEQ_WIRELESS_ICON_EASY_END
	.endm

//-----------------------------------------------------------------------------
/**
 *	主人公の位置を正しく記録するためにフィールド情報をSAVEDATAに反映させる
 */
//-----------------------------------------------------------------------------
	.macro	_SAVE_FIELD_OBJ
	.short	EV_SEQ_SAVE_FIELD_OBJ
	.endm

//-----------------------------------------------------------------------------
/**
 *	シールの名前
 *	@param	idx			セットするWORDSETの位置
 *	@param	itemno		シールの指定
 */
//-----------------------------------------------------------------------------
	.macro	_SEAL_NAME	idx, sealno
	.short	EV_SEQ_SEAL_NAME
	.byte	\idx
	.short	\sealno
	.endm

//-----------------------------------------------------------------------------
/**
 *	エスケープロケーションを直接書き換える
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
 *	OBJ同士の当たり判定フラグを設定
 */
//-----------------------------------------------------------------------------
	.macro	_FIELDOBJ_BITSET_FELLOWHIT	obj_id,flag
	.short	EV_SEQ_FIELDOBJ_BITSET_FELLOWHIT
	.short	\obj_id
	.byte	\flag
	.endm

//-----------------------------------------------------------------------------
/**
 *　ダメタマゴチェック全体版(手持ちにいる:TRUE,いない:FALSE)
 */
//-----------------------------------------------------------------------------
	.macro	_DAME_TAMAGO_CHK_ALL ret_wk
	.short	EV_SEQ_DAME_TAMAGO_CHK_ALL
	.short	\ret_wk
	.endm


//-----------------------------------------------------------------------------
/**
 *　ユニオンルーム用BMPLIST（通信データ受信によりキャンセルができる）
 */
//-----------------------------------------------------------------------------
	.macro	_UNION_BMPMENU_START
	.short	EV_SEQ_UNION_BMPMENU_START
	.endm
	

//-----------------------------------------------------------------------------
/**
 *　ユニオンルーム戦闘用開始前ポケモンリスト選択結果取得
 */
//-----------------------------------------------------------------------------
	.macro  _UNION_BATTLE_START_CHECK ret_wk
	.short  EV_SEQ_UNION_BATTLE_START_CHECK
	.short	\ret_wk
	.endm

//-----------------------------------------------------------------------------
/**
 * トレーナーカードランク取得
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



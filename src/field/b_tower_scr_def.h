/**
 *	@file	db_tower_scr_def.h
 *	@brief	�o�g���^���[�X�N���v�g�@�萔��`
 *	@author	Miyuki Iwasawa
 *	@date	06.04.18
 */

#define BTOWER_SCRWORK_MAGIC	(0x12345678)
#define BTWR_NULL_POKE	(0xFF)
#define BTWR_NULL_TRAINER	(0xFFFF)
#define BTWR_NULL_PARAM	(0)

///�o�g���^���[���������[�h
#define BTWR_PLAY_NEW		(0)
#define BTWR_PLAY_CONTINUE	(1)

///�o�g���^���[�@�N���A���E���h��
#define BTWR_CLEAR_WINCNT	(7)

//�o�g���^���[�@�A���L�^���E���h��
#define BTWR_20_RENSHOU_CNT			(20)
#define BTWR_50_RENSHOU_CNT			(50)
#define BTWR_100_RENSHOU_CNT		(100)

#define LEADER_SET_1ST	(20)	//21�l�ڂ̂Ƃ����݂̘A������20
#define LEADER_SET_2ND	(48)	//49�l�ڂ̂Ƃ����݂̘A������48

#define BTWR_FIVE_NUM		(5)	///<5�l�O�̐�
#define TOWER_FIVE_FIRST	(300)	///<5�l�O�f�[�^�̃X�^�[�gindex

///�o�g���^���[�v���C���[�h�X�N���v�g�p��`
#define BTWR_MODE_NULL		(0xFFFF)
#define BTWR_MODE_SINGLE	(0)
#define BTWR_MODE_DOUBLE	(1)
#define BTWR_MODE_MULTI		(2)
#define BTWR_MODE_COMM_MULTI	(3)
#define BTWR_MODE_WIFI			(4)
#define BTWR_MODE_RETRY			(5)

///�o�g���^���[�@�p�[�g�i�[�R�[�h
#define BTWR_PTCODE_OBJ		(2)
#define BTWR_PTCODE_MINE2	(1)
#define BTWR_PTCODE_MINE	(0)

///�o�g���^���[ WIFI�ڑ����[�h��`
#define BTWR_WIFI_DL_PLAY		(0)
#define BTWR_WIFI_UP_PLAY		(1)
#define BTWR_WIFI_DL_LEADER		(2)

///�ʐM�}���`����M�o�b�t�@�T�C�Y
#define BTWR_SIO_BUF_LEN	(70)

//���炦��O�b�Y
#define BTWR_GOODS_COPPER	(GOODS_UG_TROPH_14)
#define BTWR_GOODS_SILVER	(GOODS_UG_TROPH_15)
#define BTWR_GOODS_GOLD		(GOODS_UG_TROPH_16)

//���炦��o�g���|�C���g
#define BTLPOINT_VAL_TOWER_LEADER	(20)
#define BTLPOINT_VAL_TOWER_WIFI1	(3)
#define BTLPOINT_VAL_TOWER_WIFI2	(4)
#define BTLPOINT_VAL_TOWER_WIFI3	(5)
#define BTLPOINT_VAL_TOWER_WIFI4	(6)
#define BTLPOINT_VAL_TOWER_WIFI5	(7)
#define BTLPOINT_VAL_TOWER_WIFI6	(8)
#define BTLPOINT_VAL_TOWER_WIFI7	(9)
#define BTLPOINT_VAL_TOWER_WIFI8	(10)
#define BTLPOINT_VAL_TOWER_WIFI9	(10)
#define BTLPOINT_VAL_TOWER_WIFI10	(10)
#define BTLPOINT_VAL_TOWER_STAGE1	(3)
#define BTLPOINT_VAL_TOWER_STAGE2	(3)
#define BTLPOINT_VAL_TOWER_STAGE3	(4)
#define BTLPOINT_VAL_TOWER_STAGE4	(4)
#define BTLPOINT_VAL_TOWER_STAGE5	(5)
#define BTLPOINT_VAL_TOWER_STAGE6	(5)
#define BTLPOINT_VAL_TOWER_STAGE7	(6)
#define BTLPOINT_VAL_TOWER_STAGE8	(7)

///�X�R�A�t���O�A�N�Z�XID
#define BTWR_SF_SILVER	(0)
#define BTWR_SF_GOLD	(1)
#define BTWR_SF_S50		(2)
#define BTWR_SF_S100	(3)
#define BTWR_SF_D50		(4)
#define BTWR_SF_M50		(5)
#define BTWR_SF_CM50	(6)
#define BTWR_SF_W50		(7)

///�o�g���^���[�R�}���h�c�[��ID
#define BTWR_TOOL_GET_MEMBER_NUM		(0)
#define BTWR_TOOL_CHK_ENTRY_POKE_NUM	(1)
#define BTWR_TOOL_SYSTEM_RESET			(2)
#define BTWR_TOOL_CLEAR_PLAY_DATA		(3)
#define BTWR_TOOL_IS_SAVE_DATA_ENABLE	(4)
#define BTWR_TOOL_PUSH_NOW_LOCATION		(5)
#define BTWR_TOOL_POP_NOW_LOCATION		(6)
#define BTWR_TOOL_GET_RENSHOU_RECORD	(8)
#define BTWR_TOOL_WIFI_RANK_DOWN		(9)
#define BTWR_TOOL_GET_WIFI_RANK			(10)
#define BTWR_TOOL_SET_WIFI_UPLOAD_FLAG	(11)
#define BTWR_TOOL_GET_WIFI_UPLOAD_FLAG	(12)
#define BTWR_TOOL_SET_NG_SCORE			(14)
#define BTWR_TOOL_IS_PLAYER_DATA_ENABLE	(15)
#define BTWR_TOOL_WIFI_CONNECT			(16)

#define BTWR_SUB_START					(30)
#define BTWR_SUB_SELECT_POKE			(BTWR_SUB_START+0)
#define BTWR_SUB_GET_ENTRY_POKE			(BTWR_SUB_START+1)
#define BTWR_SUB_CHK_ENTRY_POKE			(BTWR_SUB_START+2)
#define BTWR_SUB_GET_NOW_ROUND			(BTWR_SUB_START+3)
#define BTWR_SUB_INC_ROUND				(BTWR_SUB_START+4)
#define BTWR_SUB_IS_CLEAR				(BTWR_SUB_START+5)
#define BTWR_SUB_GET_RENSHOU_CNT		(BTWR_SUB_START+6)
#define BTWR_SUB_SET_LOSE_SCORE			(BTWR_SUB_START+7)
#define BTWR_SUB_SET_CLEAR_SCORE		(BTWR_SUB_START+8)
#define BTWR_SUB_SAVE_REST_PLAY_DATA	(BTWR_SUB_START+9)
#define BTWR_SUB_CHOICE_BTL_PARTNER		(BTWR_SUB_START+10)
#define BTWR_SUB_GET_ENEMY_OBJ			(BTWR_SUB_START+11)
#define BTWR_SUB_LOCAL_BTL_CALL			(BTWR_SUB_START+12)
#define BTWR_SUB_GET_PLAY_MODE			(BTWR_SUB_START+13)
#define BTWR_SUB_SET_LEADER_CLEAR_FLAG	(BTWR_SUB_START+14)
#define BTWR_SUB_GET_LEADER_CLEAR_FLAG	(BTWR_SUB_START+15)
#define BTWR_SUB_ADD_BATTLE_POINT		(BTWR_SUB_START+16)
#define BTWR_SUB_GOODS_FLAG_SET			(BTWR_SUB_START+17)
#define BTWR_SUB_LEADER_RIBBON_SET		(BTWR_SUB_START+18)
#define BTWR_SUB_RENSHOU_RIBBON_SET		(BTWR_SUB_START+19)
#define BTWR_SUB_SET_PARTNER_NO			(BTWR_SUB_START+20)
#define BTWR_SUB_GET_PARTNER_NO			(BTWR_SUB_START+21)
#define BTWR_SUB_BTL_TRAINER_SET		(BTWR_SUB_START+22)
#define BTWR_SUB_GET_SELPOKE_IDX		(BTWR_SUB_START+23)
#define BTWR_SUB_WIFI_RANK_UP			(BTWR_SUB_START+24)
#define BTWR_SUB_GET_MINE_OBJ			(BTWR_SUB_START+25)
#define BTWR_SUB_CHOICE_BTL_SEVEN		(BTWR_SUB_START+26)
#define BTWR_SUB_UPDATE_RANDOM			(BTWR_SUB_START+27)

#define BTWR_DEB_IS_WORK_NULL			(100)


//========================================================
//�ʐM�}���`�@�����R�[�h
//========================================================
#define TOWER_COMM_MULTI_POKE_SELECT		1
#define TOWER_COMM_MULTI_BTL_TRAINER_SET	2
#define TOWER_COMM_MULTI_AUTO_SAVE			3
#define TOWER_COMM_MULTI_BATTLE_START		4
#define TOWER_COMM_MULTI_NEXT_SELECT		5
#define TOWER_COMM_MULTI_EXIT_WAIT			6
#define TOWER_COMM_MULTI_RETIRE_WAIT		7
#define TOWER_COMM_MULTI_SIO_END			8

//========================================================
//�X�N���v�g�@��ѐ���W�w��n
//========================================================
//���@ �V���O��/�_�u�� ��t��ѐ�w��
#define SB_GATE_ZONE	ZONEID_D31R0201

//���@ �G���x�[�^�[ ��ѐ�
#define SB_EV_ZONE		ZONEID_D31R0202
#define SB_EV_PLAYER_SX			(3)
#define SB_EV_PLAYER_SY			(6)

//���@ �V���O���ʘH ��ѐ�
#define SB_WAYS_ZONE	ZONEID_D31R0203
#define SB_WAYS_PLAYER_SX		(2)
#define SB_WAYS_PLAYER_SY		(1)

//���@ �V���O���o�g�����[�� ������ѐ�
#define SB_ROOMS_ZONE	ZONEID_D31R0205
#define SB_ROOMS_PLAYER_SX		(7)
#define SB_ROOMS_PLAYER_SY		(6)

//���@ �}���`�ʘH ��ѐ�
#define SB_WAYD_ZONE	ZONEID_D31R0204
#define SB_WAYD_PLAYER_SX		(8)
#define SB_WAYD_PLAYER_SY		(3)

//���@ �}���`�o�g�����[�� ��ѐ�
#define SB_ROOMD_ZONE	ZONEID_D31R0206
#define SB_ROOMD_PLAYER_SX		(7)
#define SB_ROOMD_PLAYER_SY		(5)

//���@ �T���� ��ѐ�
#define SB_SALON_ZONE	ZONEID_D31R0207
#define SB_SALON_PLAYER_SX		(8)
#define SB_SALON_PLAYER_SY		(2)





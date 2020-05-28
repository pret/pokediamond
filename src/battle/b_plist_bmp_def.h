//============================================================================================
/**
 * @file	b_plist_bmp_def.h
 * @brief	�퓬�p�|�P�������X�g��� BMP�E�B���h�E��`�t�@�C��
 * @author	Hiroyuki Nakamura
 * @date	05.02.01
 */
//============================================================================================
#define TALK_WIN_CGX_POS	( 1 )	// ��b�E�B���h�ECGX�ʒu

// �R�����g�\��
#define	WIN_P1_COMMENT_PX	( 2 )
#define	WIN_P1_COMMENT_PY	( 21 )
#define	WIN_P1_COMMENT_SX	( 22 )
#define	WIN_P1_COMMENT_SY	( 2 )
#define	WIN_P1_COMMENT_PAL	( BPL_PAL_TALK_FONT )
#define	WIN_P1_COMMENT_CGX	( TALK_WIN_CGX_POS + TALK_WIN_CGX_SIZ )
// ���b�Z�[�W�\��
#define	WIN_TALK_PX		( 2 )
#define	WIN_TALK_PY		( 19 )
#define	WIN_TALK_SX		( 27 )
#define	WIN_TALK_SY		( 4 )
#define	WIN_TALK_PAL	( BPL_PAL_TALK_FONT )
#define	WIN_TALK_CGX	( TALK_WIN_CGX_POS + TALK_WIN_CGX_SIZ )


//============================================================================================
//	����ւ��y�[�W
//============================================================================================
// ���O
#define	WIN_CHG_NAME_PX		( 10 )
#define	WIN_CHG_NAME_PY		( 4 )
#define	WIN_CHG_NAME_SX		( 12 )
#define	WIN_CHG_NAME_SY		( 3 )
#define	WIN_CHG_NAME_PAL	( BPL_PAL_HPGAGE )
#define	WIN_CHG_NAME_CGX	( 1 )
// �u���ꂩ����v
#define	WIN_CHG_IREKAE_PX	( 11 )
#define	WIN_CHG_IREKAE_PY	( 12 )
#define	WIN_CHG_IREKAE_SX	( 10 )
#define	WIN_CHG_IREKAE_SY	( 3 )
#define	WIN_CHG_IREKAE_PAL	( BPL_PAL_HPGAGE )
#define	WIN_CHG_IREKAE_CGX	( WIN_CHG_NAME_CGX + WIN_CHG_NAME_SX * WIN_CHG_NAME_SY )
// �u�悳���݂�v
#define	WIN_CHG_STATUS_PX	( 1 )
#define	WIN_CHG_STATUS_PY	( 20 )
#define	WIN_CHG_STATUS_SX	( 11 )
#define	WIN_CHG_STATUS_SY	( 3 )
#define	WIN_CHG_STATUS_PAL	( BPL_PAL_HPGAGE )
#define	WIN_CHG_STATUS_CGX	( WIN_CHG_IREKAE_CGX + WIN_CHG_IREKAE_SX * WIN_CHG_IREKAE_SY )
// �u�킴���݂�v
#define	WIN_CHG_WAZACHECK_PX	( 14 )
#define	WIN_CHG_WAZACHECK_PY	( 20 )
#define	WIN_CHG_WAZACHECK_SX	( 11 )
#define	WIN_CHG_WAZACHECK_SY	( 3 )
#define	WIN_CHG_WAZACHECK_PAL	( BPL_PAL_HPGAGE )
#define	WIN_CHG_WAZACHECK_CGX	( WIN_CHG_STATUS_CGX + WIN_CHG_STATUS_SX * WIN_CHG_STATUS_SY )

//============================================================================================
//	�y�[�W�P
//============================================================================================
#define	WIN_PS_CGX_START	( WIN_CHG_WAZACHECK_CGX+WIN_CHG_WAZACHECK_SX*WIN_CHG_WAZACHECK_SY )

// �|�P�����P
#define	WIN_P1_POKE1_PX		( 0 )
#define	WIN_P1_POKE1_PY		( 0 )
#define	WIN_P1_POKE1_SX		( 15 )
#define	WIN_P1_POKE1_SY		( 5 )
#define	WIN_P1_POKE1_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P1_POKE1_CGX	( WIN_PS_CGX_START )
// �|�P�����Q
#define	WIN_P1_POKE2_PX		( 16 )
#define	WIN_P1_POKE2_PY		( 1 )
#define	WIN_P1_POKE2_SX		( 15 )
#define	WIN_P1_POKE2_SY		( 5 )
#define	WIN_P1_POKE2_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P1_POKE2_CGX	( WIN_P1_POKE1_CGX + WIN_P1_POKE1_SX * WIN_P1_POKE1_SY )
// �|�P�����R
#define	WIN_P1_POKE3_PX		( 0 )
#define	WIN_P1_POKE3_PY		( 6 )
#define	WIN_P1_POKE3_SX		( 15 )
#define	WIN_P1_POKE3_SY		( 5 )
#define	WIN_P1_POKE3_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P1_POKE3_CGX	( WIN_P1_POKE2_CGX + WIN_P1_POKE2_SX * WIN_P1_POKE2_SY )
// �|�P�����S
#define	WIN_P1_POKE4_PX		( 16 )
#define	WIN_P1_POKE4_PY		( 7 )
#define	WIN_P1_POKE4_SX		( 15 )
#define	WIN_P1_POKE4_SY		( 5 )
#define	WIN_P1_POKE4_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P1_POKE4_CGX	( WIN_P1_POKE3_CGX + WIN_P1_POKE3_SX * WIN_P1_POKE3_SY )
// �|�P�����T
#define	WIN_P1_POKE5_PX		( 0 )
#define	WIN_P1_POKE5_PY		( 12 )
#define	WIN_P1_POKE5_SX		( 15 )
#define	WIN_P1_POKE5_SY		( 5 )
#define	WIN_P1_POKE5_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P1_POKE5_CGX	( WIN_P1_POKE4_CGX + WIN_P1_POKE4_SX * WIN_P1_POKE4_SY )
// �|�P�����U
#define	WIN_P1_POKE6_PX		( 16 )
#define	WIN_P1_POKE6_PY		( 13 )
#define	WIN_P1_POKE6_SX		( 15 )
#define	WIN_P1_POKE6_SY		( 5 )
#define	WIN_P1_POKE6_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P1_POKE6_CGX	( WIN_P1_POKE5_CGX + WIN_P1_POKE5_SX * WIN_P1_POKE5_SY )


//============================================================================================
//	�X�e�[�^�X���C���ƋZ�I���y�[�W
//============================================================================================
#define	WIN_ST_CGX_START	( WIN_PS_CGX_START )

// �uHP�v
#define	WIN_STM_HP_PX		( 21 )
#define	WIN_STM_HP_PY		( 4 )
#define	WIN_STM_HP_SX		( 2 )
#define	WIN_STM_HP_SY		( 2 )
#define	WIN_STM_HP_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_STM_HP_CGX		( WIN_ST_CGX_START )
// �u���������v
#define	WIN_STM_POW_PX		( 21 )
#define	WIN_STM_POW_PY		( 7 )
#define	WIN_STM_POW_SX		( 6 )
#define	WIN_STM_POW_SY		( 2 )
#define	WIN_STM_POW_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_STM_POW_CGX		( WIN_STM_HP_CGX + WIN_STM_HP_SX * WIN_STM_HP_SY )
// �u�ڂ�����v
#define	WIN_STM_DEF_PX		( 21 )
#define	WIN_STM_DEF_PY		( 9 )
#define	WIN_STM_DEF_SX		( 6 )
#define	WIN_STM_DEF_SY		( 2 )
#define	WIN_STM_DEF_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_STM_DEF_CGX		( WIN_STM_POW_CGX + WIN_STM_POW_SX * WIN_STM_POW_SY )
// �u���΂₳�v
#define	WIN_STM_AGI_PX		( 21 )
#define	WIN_STM_AGI_PY		( 15 )
#define	WIN_STM_AGI_SX		( 6 )
#define	WIN_STM_AGI_SY		( 2 )
#define	WIN_STM_AGI_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_STM_AGI_CGX		( WIN_STM_DEF_CGX + WIN_STM_DEF_SX * WIN_STM_DEF_SY )
// �u�Ƃ������v
#define	WIN_STM_SPP_PX		( 21 )
#define	WIN_STM_SPP_PY		( 11 )
#define	WIN_STM_SPP_SX		( 6 )
#define	WIN_STM_SPP_SY		( 2 )
#define	WIN_STM_SPP_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_STM_SPP_CGX		( WIN_STM_AGI_CGX + WIN_STM_AGI_SX * WIN_STM_AGI_SY )
// �u�Ƃ��ڂ��v
#define	WIN_STM_SPD_PX		( 21 )
#define	WIN_STM_SPD_PY		( 13 )
#define	WIN_STM_SPD_SX		( 6 )
#define	WIN_STM_SPD_SY		( 2 )
#define	WIN_STM_SPD_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_STM_SPD_CGX		( WIN_STM_SPP_CGX + WIN_STM_SPP_SX * WIN_STM_SPP_SY )
// �uLv.�v
#define	WIN_STM_LV_PX		( 1 )
#define	WIN_STM_LV_PY		( 4 )
#define	WIN_STM_LV_SX		( 4 )
#define	WIN_STM_LV_SY		( 2 )
#define	WIN_STM_LV_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_STM_LV_CGX		( WIN_STM_SPD_CGX + WIN_STM_SPD_SX * WIN_STM_SPD_SY )
// �u���̃��x���܂Łv
#define	WIN_STM_NEXT_PX		( 1 )
#define	WIN_STM_NEXT_PY		( 6 )
#define	WIN_STM_NEXT_SX		( 11 )
#define	WIN_STM_NEXT_SY		( 2 )
#define	WIN_STM_NEXT_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_NEXT_CGX	( WIN_STM_LV_CGX + WIN_STM_LV_SX * WIN_STM_LV_SY )
// �u�킴���݂�v
#define	WIN_STM_WAZACHECK_PX	( 13 )
#define	WIN_STM_WAZACHECK_PY	( 20 )
#define	WIN_STM_WAZACHECK_SX	( 11 )
#define	WIN_STM_WAZACHECK_SY	( 3 )
#define	WIN_STM_WAZACHECK_PAL	( BPL_PAL_HPGAGE )
#define	WIN_STM_WAZACHECK_CGX	( WIN_STM_NEXT_CGX + WIN_STM_NEXT_SX * WIN_STM_NEXT_SY )
// �u�悳���݂�v
#define	WIN_STW_STATUS_PX	( 13 )
#define	WIN_STW_STATUS_PY	( 20 )
#define	WIN_STW_STATUS_SX	( 11 )
#define	WIN_STW_STATUS_SY	( 3 )
#define	WIN_STW_STATUS_PAL	( BPL_PAL_HPGAGE )
#define	WIN_STW_STATUS_CGX	( WIN_STM_WAZACHECK_CGX+WIN_STM_WAZACHECK_SX*WIN_STM_WAZACHECK_SY )

// ���O
#define	WIN_ST_NAME_PX		( 5 )
#define	WIN_ST_NAME_PY		( 1 )
#define	WIN_ST_NAME_SX		( 9 )
#define	WIN_ST_NAME_SY		( 2 )
#define	WIN_ST_NAME_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_ST_NAME_CGX		( WIN_STW_STATUS_CGX+WIN_STW_STATUS_SX*WIN_STW_STATUS_SY )
// ���O�i�X���b�v�j
#define	WIN_ST_NAME_S_CGX	( WIN_ST_NAME_CGX + WIN_ST_NAME_SX * WIN_ST_NAME_SY )

// �p�����[�^�������ݗ̈�J�n�P
#define	WIN_ST_PARAM1_CGX	( WIN_ST_NAME_S_CGX + WIN_ST_NAME_SX * WIN_ST_NAME_SY )

// �Z�P
#define	WIN_STW_SKILL1_PX	( 1 )
#define	WIN_STW_SKILL1_PY	( 6 )
#define	WIN_STW_SKILL1_SX	( 14 )
#define	WIN_STW_SKILL1_SY	( 5 )
#define	WIN_STW_SKILL1_PAL	( BPL_PAL_HPGAGE )
#define	WIN_STW_SKILL1_CGX	( WIN_ST_PARAM1_CGX )
// �Z�Q
#define	WIN_STW_SKILL2_PX	( 17 )
#define	WIN_STW_SKILL2_PY	( 6 )
#define	WIN_STW_SKILL2_SX	( 14 )
#define	WIN_STW_SKILL2_SY	( 5 )
#define	WIN_STW_SKILL2_PAL	( BPL_PAL_HPGAGE )
#define	WIN_STW_SKILL2_CGX	( WIN_STW_SKILL1_CGX + WIN_STW_SKILL1_SX * WIN_STW_SKILL1_SY )
// �Z�R
#define	WIN_STW_SKILL3_PX	( 1 )
#define	WIN_STW_SKILL3_PY	( 12 )
#define	WIN_STW_SKILL3_SX	( 14 )
#define	WIN_STW_SKILL3_SY	( 5 )
#define	WIN_STW_SKILL3_PAL	( BPL_PAL_HPGAGE )
#define	WIN_STW_SKILL3_CGX	( WIN_STW_SKILL2_CGX + WIN_STW_SKILL2_SX * WIN_STW_SKILL2_SY )
// �Z�S
#define	WIN_STW_SKILL4_PX	( 17 )
#define	WIN_STW_SKILL4_PY	( 12 )
#define	WIN_STW_SKILL4_SX	( 14 )
#define	WIN_STW_SKILL4_SY	( 5 )
#define	WIN_STW_SKILL4_PAL	( BPL_PAL_HPGAGE )
#define	WIN_STW_SKILL4_CGX	( WIN_STW_SKILL3_CGX + WIN_STW_SKILL3_SX * WIN_STW_SKILL3_SY )

// �p�����[�^�������ݗ̈�J�n�Q
#define	WIN_ST_PARAM2_CGX	( WIN_STW_SKILL4_CGX + WIN_STW_SKILL4_SX * WIN_STW_SKILL4_SY )

// �Z�P�i�X���b�v�j
#define	WIN_STW_SKILL1_S_CGX	( WIN_ST_PARAM2_CGX )
// �Z�Q�i�X���b�v�j
#define	WIN_STW_SKILL2_S_CGX	( WIN_STW_SKILL1_S_CGX+WIN_STW_SKILL1_SX*WIN_STW_SKILL1_SY )
// �Z�R�i�X���b�v�j
#define	WIN_STW_SKILL3_S_CGX	( WIN_STW_SKILL2_S_CGX+WIN_STW_SKILL2_SX*WIN_STW_SKILL2_SY )
// �Z�S�i�X���b�v�j
#define	WIN_STW_SKILL4_S_CGX	( WIN_STW_SKILL3_S_CGX+WIN_STW_SKILL3_SX*WIN_STW_SKILL3_SY )

// ������
#define	WIN_STM_SPANAME_PX	( 1 )
#define	WIN_STM_SPANAME_PY	( 9 )
#define	WIN_STM_SPANAME_SX	( 11 )
#define	WIN_STM_SPANAME_SY	( 2 )
#define	WIN_STM_SPANAME_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_SPANAME_CGX	( WIN_ST_PARAM1_CGX )
// ��������
#define	WIN_STM_SPAINFO_PX	( 1 )
#define	WIN_STM_SPAINFO_PY	( 11 )
#define	WIN_STM_SPAINFO_SX	( 18 )
#define	WIN_STM_SPAINFO_SY	( 4 )
#define	WIN_STM_SPAINFO_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_SPAINFO_CGX	( WIN_STM_SPANAME_CGX + WIN_STM_SPANAME_SX * WIN_STM_SPANAME_SY )
// ���
#define	WIN_STM_ITEMNAME_PX		( 4 )
#define	WIN_STM_ITEMNAME_PY		( 16 )
#define	WIN_STM_ITEMNAME_SX		( 12 )
#define	WIN_STM_ITEMNAME_SY		( 2 )
#define	WIN_STM_ITEMNAME_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_ITEMNAME_CGX	( WIN_STM_SPAINFO_CGX + WIN_STM_SPAINFO_SX * WIN_STM_SPAINFO_SY )
// HP�l
#define	WIN_STM_HPNUM_PX	( 24 )
#define	WIN_STM_HPNUM_PY	( 4 )
#define	WIN_STM_HPNUM_SX	( 7 )
#define	WIN_STM_HPNUM_SY	( 2 )
#define	WIN_STM_HPNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_HPNUM_CGX	( WIN_STM_ITEMNAME_CGX + WIN_STM_ITEMNAME_SX * WIN_STM_ITEMNAME_SY )
// �U���l
#define	WIN_STM_POWNUM_PX	( 28 )
#define	WIN_STM_POWNUM_PY	( 7 )
#define	WIN_STM_POWNUM_SX	( 3 )
#define	WIN_STM_POWNUM_SY	( 2 )
#define	WIN_STM_POWNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_POWNUM_CGX	( WIN_STM_HPNUM_CGX + WIN_STM_HPNUM_SX * WIN_STM_HPNUM_SY )
// �h��l
#define	WIN_STM_DEFNUM_PX	( 28 )
#define	WIN_STM_DEFNUM_PY	( 9 )
#define	WIN_STM_DEFNUM_SX	( 3 )
#define	WIN_STM_DEFNUM_SY	( 2 )
#define	WIN_STM_DEFNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_DEFNUM_CGX	( WIN_STM_POWNUM_CGX + WIN_STM_POWNUM_SX * WIN_STM_POWNUM_SY )
// �f�����l
#define	WIN_STM_AGINUM_PX	( 28 )
#define	WIN_STM_AGINUM_PY	( 15 )
#define	WIN_STM_AGINUM_SX	( 3 )
#define	WIN_STM_AGINUM_SY	( 2 )
#define	WIN_STM_AGINUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_AGINUM_CGX	( WIN_STM_DEFNUM_CGX + WIN_STM_DEFNUM_SX * WIN_STM_DEFNUM_SY )
// ���U�l
#define	WIN_STM_SPPNUM_PX	( 28 )
#define	WIN_STM_SPPNUM_PY	( 11 )
#define	WIN_STM_SPPNUM_SX	( 3 )
#define	WIN_STM_SPPNUM_SY	( 2 )
#define	WIN_STM_SPPNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_SPPNUM_CGX	( WIN_STM_AGINUM_CGX + WIN_STM_AGINUM_SX * WIN_STM_AGINUM_SY )
// ���h�l
#define	WIN_STM_SPDNUM_PX	( 28 )
#define	WIN_STM_SPDNUM_PY	( 13 )
#define	WIN_STM_SPDNUM_SX	( 3 )
#define	WIN_STM_SPDNUM_SY	( 2 )
#define	WIN_STM_SPDNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_SPDNUM_CGX	( WIN_STM_SPPNUM_CGX + WIN_STM_SPPNUM_SX * WIN_STM_SPPNUM_SY )
// HP�Q�[�W
#define	WIN_STM_HPGAGE_PX	( 25 )
#define	WIN_STM_HPGAGE_PY	( 6 )
#define	WIN_STM_HPGAGE_SX	( 6 )
#define	WIN_STM_HPGAGE_SY	( 1 )
#define	WIN_STM_HPGAGE_PAL	( BPL_PAL_HPGAGE )
#define	WIN_STM_HPGAGE_CGX	( WIN_STM_SPDNUM_CGX + WIN_STM_SPDNUM_SX * WIN_STM_SPDNUM_SY )
// ���x���l
#define	WIN_STM_LVNUM_PX	( 5 )
#define	WIN_STM_LVNUM_PY	( 4 )
#define	WIN_STM_LVNUM_SX	( 3 )
#define	WIN_STM_LVNUM_SY	( 2 )
#define	WIN_STM_LVNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_LVNUM_CGX	( WIN_STM_HPGAGE_CGX + WIN_STM_HPGAGE_SX * WIN_STM_HPGAGE_SY )
// ���̃��x���l
#define	WIN_STM_NEXTNUM_PX	( 13 )
#define	WIN_STM_NEXTNUM_PY	( 6 )
#define	WIN_STM_NEXTNUM_SX	( 6 )
#define	WIN_STM_NEXTNUM_SY	( 2 )
#define	WIN_STM_NEXTNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_STM_NEXTNUM_CGX	( WIN_STM_LVNUM_CGX + WIN_STM_LVNUM_SX * WIN_STM_LVNUM_SY )

// ������
#define	WIN_STM_SPANAME_S_CGX	( WIN_ST_PARAM2_CGX )
// ��������
#define	WIN_STM_SPAINFO_S_CGX	( WIN_STM_SPANAME_S_CGX+WIN_STM_SPANAME_SX*WIN_STM_SPANAME_SY )
// ���
#define	WIN_STM_ITEMNAME_S_CGX	( WIN_STM_SPAINFO_S_CGX+WIN_STM_SPAINFO_SX*WIN_STM_SPAINFO_SY )
// HP�l
#define	WIN_STM_HPNUM_S_CGX		( WIN_STM_ITEMNAME_S_CGX+WIN_STM_ITEMNAME_SX*WIN_STM_ITEMNAME_SY )
// �U���l
#define	WIN_STM_POWNUM_S_CGX	( WIN_STM_HPNUM_S_CGX + WIN_STM_HPNUM_SX * WIN_STM_HPNUM_SY )
// �h��l
#define	WIN_STM_DEFNUM_S_CGX	( WIN_STM_POWNUM_S_CGX + WIN_STM_POWNUM_SX * WIN_STM_POWNUM_SY )
// �f�����l
#define	WIN_STM_AGINUM_S_CGX	( WIN_STM_DEFNUM_S_CGX + WIN_STM_DEFNUM_SX * WIN_STM_DEFNUM_SY )
// ���U�l
#define	WIN_STM_SPPNUM_S_CGX	( WIN_STM_AGINUM_S_CGX + WIN_STM_AGINUM_SX * WIN_STM_AGINUM_SY )
// ���h�l
#define	WIN_STM_SPDNUM_S_CGX	( WIN_STM_SPPNUM_S_CGX + WIN_STM_SPPNUM_SX * WIN_STM_SPPNUM_SY )
// HP�Q�[�W
#define	WIN_STM_HPGAGE_S_CGX	( WIN_STM_SPDNUM_S_CGX + WIN_STM_SPDNUM_SX * WIN_STM_SPDNUM_SY )
// ���x���l
#define	WIN_STM_LVNUM_S_CGX		( WIN_STM_HPGAGE_S_CGX + WIN_STM_HPGAGE_SX * WIN_STM_HPGAGE_SY )
// ���̃��x���l
#define	WIN_STM_NEXTNUM_S_CGX	( WIN_STM_LVNUM_S_CGX + WIN_STM_LVNUM_SX * WIN_STM_LVNUM_SY )


//============================================================================================
//	�X�e�[�^�X�Z�ڍ׃y�[�W
//============================================================================================
#define	WIN_SWI_CGX_START	( WIN_TALK_CGX + WIN_TALK_SX * WIN_TALK_SY )

// ���O
#define	WIN_P4_NAME_PX		( 5 )
#define	WIN_P4_NAME_PY		( 1 )
#define	WIN_P4_NAME_SX		( 9 )
#define	WIN_P4_NAME_SY		( 2 )
#define	WIN_P4_NAME_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P4_NAME_CGX		( WIN_SWI_CGX_START )
// �Z��
#define	WIN_P4_SKILL_PX		( 4 )
#define	WIN_P4_SKILL_PY		( 5 )
#define	WIN_P4_SKILL_SX		( 11 )
#define	WIN_P4_SKILL_SY		( 2 )
#define	WIN_P4_SKILL_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P4_SKILL_CGX	( WIN_P4_NAME_CGX + WIN_P4_NAME_SX * WIN_P4_NAME_SY )
// PP
#define	WIN_P4_PP_PX		( 20 )
#define	WIN_P4_PP_PY		( 5 )
#define	WIN_P4_PP_SX		( 2 )
#define	WIN_P4_PP_SY		( 2 )
#define	WIN_P4_PP_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P4_PP_CGX		( WIN_P4_SKILL_CGX + WIN_P4_SKILL_SX * WIN_P4_SKILL_SY )
// PP/PP
#define	WIN_P4_PPNUM_PX		( 23 )
#define	WIN_P4_PPNUM_PY		( 5 )
#define	WIN_P4_PPNUM_SX		( 5 )
#define	WIN_P4_PPNUM_SY		( 2 )
#define	WIN_P4_PPNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P4_PPNUM_CGX	( WIN_P4_PP_CGX + WIN_P4_PP_SX * WIN_P4_PP_SY )
// �u�߂����イ�v
#define	WIN_P4_HIT_PX		( 1 )
#define	WIN_P4_HIT_PY		( 16 )
#define	WIN_P4_HIT_SX		( 8 )
#define	WIN_P4_HIT_SY		( 2 )
#define	WIN_P4_HIT_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P4_HIT_CGX		( WIN_P4_PPNUM_CGX + WIN_P4_PPNUM_SX * WIN_P4_PPNUM_SY )
// �u����傭�v
#define	WIN_P4_POW_PX		( 1 )
#define	WIN_P4_POW_PY		( 13 )
#define	WIN_P4_POW_SX		( 8 )
#define	WIN_P4_POW_SY		( 2 )
#define	WIN_P4_POW_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P4_POW_CGX		( WIN_P4_HIT_CGX + WIN_P4_HIT_SX * WIN_P4_HIT_SY )
// �����l
#define	WIN_P4_HITNUM_PX	( 10 )
#define	WIN_P4_HITNUM_PY	( 16 )
#define	WIN_P4_HITNUM_SX	( 3 )
#define	WIN_P4_HITNUM_SY	( 2 )
#define	WIN_P4_HITNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P4_HITNUM_CGX	( WIN_P4_POW_CGX + WIN_P4_POW_SX * WIN_P4_POW_SY )
// �З͒l
#define	WIN_P4_POWNUM_PX	( 10 )
#define	WIN_P4_POWNUM_PY	( 13 )
#define	WIN_P4_POWNUM_SX	( 3 )
#define	WIN_P4_POWNUM_SY	( 2 )
#define	WIN_P4_POWNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P4_POWNUM_CGX	( WIN_P4_HITNUM_CGX + WIN_P4_HITNUM_SX * WIN_P4_HITNUM_SY )
// �Z����
#define	WIN_P4_INFO_PX		( 16 )
#define	WIN_P4_INFO_PY		( 8 )
#define	WIN_P4_INFO_SX		( 15 )
#define	WIN_P4_INFO_SY		( 10 )
#define	WIN_P4_INFO_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P4_INFO_CGX		( WIN_P4_POWNUM_CGX + WIN_P4_POWNUM_SX * WIN_P4_POWNUM_SY )
// �u�Ԃ�邢�v
#define	WIN_P4_BUNRUI_PX	( 1 )
#define	WIN_P4_BUNRUI_PY	( 8 )
#define	WIN_P4_BUNRUI_SX	( 12 )
#define	WIN_P4_BUNRUI_SY	( 2 )
#define	WIN_P4_BUNRUI_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P4_BUNRUI_CGX	( WIN_P4_INFO_CGX + WIN_P4_INFO_SX * WIN_P4_INFO_SY )
// ���ޖ�
#define	WIN_P4_BRNAME_PX	( 6 )
#define	WIN_P4_BRNAME_PY	( 10 )
#define	WIN_P4_BRNAME_SX	( 8 )
#define	WIN_P4_BRNAME_SY	( 2 )
#define	WIN_P4_BRNAME_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P4_BRNAME_CGX	( WIN_P4_BUNRUI_CGX + WIN_P4_BUNRUI_SX * WIN_P4_BUNRUI_SY )

// �Z���i�X���b�v�j
#define	WIN_P4_SKILL_S_CGX	( WIN_P4_BRNAME_CGX + WIN_P4_BRNAME_SX * WIN_P4_BRNAME_SY )
// PP/PP�i�X���b�v�j
#define	WIN_P4_PPNUM_S_CGX	( WIN_P4_SKILL_S_CGX + WIN_P4_SKILL_SX * WIN_P4_SKILL_SY )
// �����l�i�X���b�v�j
#define	WIN_P4_HITNUM_S_CGX	( WIN_P4_PPNUM_S_CGX + WIN_P4_PPNUM_SX * WIN_P4_PPNUM_SY )
// �З͒l�i�X���b�v�j
#define	WIN_P4_POWNUM_S_CGX	( WIN_P4_HITNUM_S_CGX + WIN_P4_HITNUM_SX * WIN_P4_HITNUM_SY )
// �Z�����i�X���b�v�j
#define	WIN_P4_INFO_S_CGX	( WIN_P4_POWNUM_S_CGX + WIN_P4_POWNUM_SX * WIN_P4_POWNUM_SY )
// ���ޖ��i�X���b�v�j
#define	WIN_P4_BRNAME_S_CGX	( WIN_P4_INFO_S_CGX + WIN_P4_INFO_SX * WIN_P4_INFO_SY )


//============================================================================================
//	�Z�񕜃y�[�W
//============================================================================================
#define	WIN_PPR_CGX_START	( WIN_TALK_CGX + WIN_TALK_SX * WIN_TALK_SY )

// ���O
#define	WIN_P7_NAME_PX		( 5 )
#define	WIN_P7_NAME_PY		( 1 )
#define	WIN_P7_NAME_SX		( 9 )
#define	WIN_P7_NAME_SY		( 2 )
#define	WIN_P7_NAME_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P7_NAME_CGX		( WIN_PPR_CGX_START )
// �Z�P
#define	WIN_P7_SKILL1_PX	( 1 )
#define	WIN_P7_SKILL1_PY	( 6 )
#define	WIN_P7_SKILL1_SX	( 14 )
#define	WIN_P7_SKILL1_SY	( 5 )
#define	WIN_P7_SKILL1_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P7_SKILL1_CGX	( WIN_P7_NAME_CGX + WIN_P7_NAME_SX * WIN_P7_NAME_SY )
// �Z�Q
#define	WIN_P7_SKILL2_PX	( 17 )
#define	WIN_P7_SKILL2_PY	( 6 )
#define	WIN_P7_SKILL2_SX	( 14 )
#define	WIN_P7_SKILL2_SY	( 5 )
#define	WIN_P7_SKILL2_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P7_SKILL2_CGX	( WIN_P7_SKILL1_CGX + WIN_P7_SKILL1_SX * WIN_P7_SKILL1_SY )
// �Z�R
#define	WIN_P7_SKILL3_PX	( 1 )
#define	WIN_P7_SKILL3_PY	( 12 )
#define	WIN_P7_SKILL3_SX	( 14 )
#define	WIN_P7_SKILL3_SY	( 5 )
#define	WIN_P7_SKILL3_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P7_SKILL3_CGX	( WIN_P7_SKILL2_CGX + WIN_P7_SKILL2_SX * WIN_P7_SKILL2_SY )
// �Z�S
#define	WIN_P7_SKILL4_PX	( 17 )
#define	WIN_P7_SKILL4_PY	( 12 )
#define	WIN_P7_SKILL4_SX	( 14 )
#define	WIN_P7_SKILL4_SY	( 5 )
#define	WIN_P7_SKILL4_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P7_SKILL4_CGX	( WIN_P7_SKILL3_CGX + WIN_P7_SKILL3_SX * WIN_P7_SKILL3_SY )


//============================================================================================
//	�Z�Y��I���y�[�W
//============================================================================================
#define	WIN_WDL_CGX_START	( WIN_CHG_WAZACHECK_CGX+WIN_CHG_WAZACHECK_SX*WIN_CHG_WAZACHECK_SY )

// ���O
#define	WIN_P5_NAME_PX		( 5 )
#define	WIN_P5_NAME_PY		( 1 )
#define	WIN_P5_NAME_SX		( 9 )
#define	WIN_P5_NAME_SY		( 2 )
#define	WIN_P5_NAME_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P5_NAME_CGX		( WIN_WDL_CGX_START )
// �Z�P
#define	WIN_P5_SKILL1_PX	( 1 )
#define	WIN_P5_SKILL1_PY	( 6 )
#define	WIN_P5_SKILL1_SX	( 14 )
#define	WIN_P5_SKILL1_SY	( 5 )
#define	WIN_P5_SKILL1_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P5_SKILL1_CGX	( WIN_P5_NAME_CGX + WIN_P5_NAME_SX * WIN_P5_NAME_SY )
// �Z�Q
#define	WIN_P5_SKILL2_PX	( 17 )
#define	WIN_P5_SKILL2_PY	( 6 )
#define	WIN_P5_SKILL2_SX	( 14 )
#define	WIN_P5_SKILL2_SY	( 5 )
#define	WIN_P5_SKILL2_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P5_SKILL2_CGX	( WIN_P5_SKILL1_CGX + WIN_P5_SKILL1_SX * WIN_P5_SKILL1_SY )
// �Z�R
#define	WIN_P5_SKILL3_PX	( 1 )
#define	WIN_P5_SKILL3_PY	( 12 )
#define	WIN_P5_SKILL3_SX	( 14 )
#define	WIN_P5_SKILL3_SY	( 5 )
#define	WIN_P5_SKILL3_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P5_SKILL3_CGX	( WIN_P5_SKILL2_CGX + WIN_P5_SKILL2_SX * WIN_P5_SKILL2_SY )
// �Z�S
#define	WIN_P5_SKILL4_PX	( 17 )
#define	WIN_P5_SKILL4_PY	( 12 )
#define	WIN_P5_SKILL4_SX	( 14 )
#define	WIN_P5_SKILL4_SY	( 5 )
#define	WIN_P5_SKILL4_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P5_SKILL4_CGX	( WIN_P5_SKILL3_CGX + WIN_P5_SKILL3_SX * WIN_P5_SKILL3_SY )
// �Z�T
#define	WIN_P5_SKILL5_PX	( 9 )
#define	WIN_P5_SKILL5_PY	( 18 )
#define	WIN_P5_SKILL5_SX	( 14 )
#define	WIN_P5_SKILL5_SY	( 5 )
#define	WIN_P5_SKILL5_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P5_SKILL5_CGX	( WIN_P5_SKILL4_CGX + WIN_P5_SKILL4_SX * WIN_P5_SKILL4_SY )


//============================================================================================
//	�Z�Y��퓬�Z�����y�[�W
//============================================================================================
// ���O
#define	WIN_P6_NAME_PX		( 5 )
#define	WIN_P6_NAME_PY		( 1 )
#define	WIN_P6_NAME_SX		( 9 )
#define	WIN_P6_NAME_SY		( 2 )
#define	WIN_P6_NAME_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P6_NAME_CGX		( 1 )
// �Z��
#define	WIN_P6_SKILL_PX		( 4 )
#define	WIN_P6_SKILL_PY		( 5 )
#define	WIN_P6_SKILL_SX		( 11 )
#define	WIN_P6_SKILL_SY		( 2 )
#define	WIN_P6_SKILL_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P6_SKILL_CGX	( WIN_P6_NAME_CGX + WIN_P6_NAME_SX * WIN_P6_NAME_SY )
// PP
#define	WIN_P6_PP_PX		( 20 )
#define	WIN_P6_PP_PY		( 5 )
#define	WIN_P6_PP_SX		( 2 )
#define	WIN_P6_PP_SY		( 2 )
#define	WIN_P6_PP_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P6_PP_CGX		( WIN_P6_SKILL_CGX + WIN_P6_SKILL_SX * WIN_P6_SKILL_SY )
// PP/PP
#define	WIN_P6_PPNUM_PX		( 23 )
#define	WIN_P6_PPNUM_PY		( 5 )
#define	WIN_P6_PPNUM_SX		( 5 )
#define	WIN_P6_PPNUM_SY		( 2 )
#define	WIN_P6_PPNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P6_PPNUM_CGX	( WIN_P6_PP_CGX + WIN_P6_PP_SX * WIN_P6_PP_SY )
// �u�킷���v
#define	WIN_P6_WASURERU_PX	( 7 )
#define	WIN_P6_WASURERU_PY	( 20 )
#define	WIN_P6_WASURERU_SX	( 12 )
#define	WIN_P6_WASURERU_SY	( 3 )
#define	WIN_P6_WASURERU_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P6_WASURERU_CGX	( WIN_P6_PPNUM_CGX + WIN_P6_PPNUM_SX * WIN_P6_PPNUM_SY )
// �u�߂����イ�v
#define	WIN_P6_HIT_PX		( 1 )
#define	WIN_P6_HIT_PY		( 16 )
#define	WIN_P6_HIT_SX		( 8 )
#define	WIN_P6_HIT_SY		( 2 )
#define	WIN_P6_HIT_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P6_HIT_CGX		( WIN_P6_WASURERU_CGX + WIN_P6_WASURERU_SX * WIN_P6_WASURERU_SY )
// �u����傭�v
#define	WIN_P6_POW_PX		( 1 )
#define	WIN_P6_POW_PY		( 13 )
#define	WIN_P6_POW_SX		( 8 )
#define	WIN_P6_POW_SY		( 2 )
#define	WIN_P6_POW_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P6_POW_CGX		( WIN_P6_HIT_CGX + WIN_P6_HIT_SX * WIN_P6_HIT_SY )
// �����l
#define	WIN_P6_HITNUM_PX	( 10 )
#define	WIN_P6_HITNUM_PY	( 16 )
#define	WIN_P6_HITNUM_SX	( 3 )
#define	WIN_P6_HITNUM_SY	( 2 )
#define	WIN_P6_HITNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P6_HITNUM_CGX	( WIN_P6_POW_CGX + WIN_P6_POW_SX * WIN_P6_POW_SY )
// �З͒l
#define	WIN_P6_POWNUM_PX	( 10 )
#define	WIN_P6_POWNUM_PY	( 13 )
#define	WIN_P6_POWNUM_SX	( 3 )
#define	WIN_P6_POWNUM_SY	( 2 )
#define	WIN_P6_POWNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P6_POWNUM_CGX	( WIN_P6_HITNUM_CGX + WIN_P6_HITNUM_SX * WIN_P6_HITNUM_SY )
// �Z����
#define	WIN_P6_INFO_PX		( 16 )
#define	WIN_P6_INFO_PY		( 8 )
#define	WIN_P6_INFO_SX		( 15 )
#define	WIN_P6_INFO_SY		( 10 )
#define	WIN_P6_INFO_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P6_INFO_CGX		( WIN_P6_POWNUM_CGX + WIN_P6_POWNUM_SX * WIN_P6_POWNUM_SY )
// �u�Ԃ�邢�v
#define	WIN_P6_BUNRUI_PX	( 1 )
#define	WIN_P6_BUNRUI_PY	( 8 )
#define	WIN_P6_BUNRUI_SX	( 12 )
#define	WIN_P6_BUNRUI_SY	( 2 )
#define	WIN_P6_BUNRUI_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P6_BUNRUI_CGX	( WIN_P6_INFO_CGX + WIN_P6_INFO_SX * WIN_P6_INFO_SY )
// ���ޖ�
#define	WIN_P6_BRNAME_PX	( 6 )
#define	WIN_P6_BRNAME_PY	( 10 )
#define	WIN_P6_BRNAME_SX	( 8 )
#define	WIN_P6_BRNAME_SY	( 2 )
#define	WIN_P6_BRNAME_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P6_BRNAME_CGX	( WIN_P6_BUNRUI_CGX + WIN_P6_BUNRUI_SX * WIN_P6_BUNRUI_SY )


//============================================================================================
//	�Z�Y��R���e�X�g�Z�����y�[�W
//============================================================================================
// ���O
#define	WIN_P8_NAME_PX		( 5 )
#define	WIN_P8_NAME_PY		( 1 )
#define	WIN_P8_NAME_SX		( 9 )
#define	WIN_P8_NAME_SY		( 2 )
#define	WIN_P8_NAME_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P8_NAME_CGX		( WIN_P6_NAME_CGX )
// �Z��
#define	WIN_P8_SKILL_PX		( 4 )
#define	WIN_P8_SKILL_PY		( 8 )
#define	WIN_P8_SKILL_SX		( 11 )
#define	WIN_P8_SKILL_SY		( 2 )
#define	WIN_P8_SKILL_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P8_SKILL_CGX	( WIN_P6_SKILL_CGX )
// PP
#define	WIN_P8_PP_PX		( 20 )
#define	WIN_P8_PP_PY		( 8 )
#define	WIN_P8_PP_SX		( 2 )
#define	WIN_P8_PP_SY		( 2 )
#define	WIN_P8_PP_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P8_PP_CGX		( WIN_P6_PP_CGX )
// PP/PP
#define	WIN_P8_PPNUM_PX		( 23 )
#define	WIN_P8_PPNUM_PY		( 8 )
#define	WIN_P8_PPNUM_SX		( 5 )
#define	WIN_P8_PPNUM_SY		( 2 )
#define	WIN_P8_PPNUM_PAL	( BPL_PAL_SYS_FONT )
#define	WIN_P8_PPNUM_CGX	( WIN_P6_PPNUM_CGX )
// �u�킷���v
#define	WIN_P8_WASURERU_PX	( 7 )
#define	WIN_P8_WASURERU_PY	( 20 )
#define	WIN_P8_WASURERU_SX	( 12 )
#define	WIN_P8_WASURERU_SY	( 3 )
#define	WIN_P8_WASURERU_PAL	( BPL_PAL_HPGAGE )
#define	WIN_P8_WASURERU_CGX	( WIN_P6_WASURERU_CGX )
// �u�A�s�[���|�C���g�v
#define	WIN_P8_APP_PX		( 2 )
#define	WIN_P8_APP_PY		( 11 )
#define	WIN_P8_APP_SX		( 12 )
#define	WIN_P8_APP_SY		( 2 )
#define	WIN_P8_APP_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P8_APP_CGX		( WIN_P6_BRNAME_CGX + WIN_P6_BRNAME_SX * WIN_P6_BRNAME_SY )
// �Z����
#define	WIN_P8_INFO_PX		( 16 )
#define	WIN_P8_INFO_PY		( 11 )
#define	WIN_P8_INFO_SX		( 15 )
#define	WIN_P8_INFO_SY		( 6 )
#define	WIN_P8_INFO_PAL		( BPL_PAL_SYS_FONT )
#define	WIN_P8_INFO_CGX		( WIN_P8_APP_CGX + WIN_P8_APP_SX * WIN_P8_APP_SY )

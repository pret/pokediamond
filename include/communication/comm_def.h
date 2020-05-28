//=============================================================================
/**
 * @file	comm_def.h
 * @brief	�ʐM�֘A�ŃC�x���g���ł̎󂯓n�����K�v�Ȓ�`���W�߂��t�@�C��
            define���������Ȃ��Ƃ̎�
 * @author	Katsumi Ohno
 * @date    2005.11.09
 */
//=============================================================================
#ifndef _COMM_DEF_H_
#define _COMM_DEF_H_

// �����Ŏg�p����DMA�ԍ�
#define COMM_DMA_NO                 (2)
//WM�̃p���[���[�h
#define COMM_POWERMODE       (1)
//SSL�����̃X���b�h�D�揇��
#define COMM_SSL_PRIORITY     (20)



// �e�@��I���ł��鐔�B
#define  SCAN_PARENT_COUNT_MAX ( 16 )

// �q�@�ő吔
#define  COMM_CHILD_MAX  ( 7 )

// ���肦�Ȃ�ID
#define COMM_INVALID_ID  (0xff)


// �@�ő吔
#define  COMM_MACHINE_MAX  (COMM_CHILD_MAX+1)

// ������R�}���h�̎�M�ő�T�C�Y
#define  COMM_COMMAND_RECV_SIZE_MAX  (256)
// ������R�}���h�̑��M�ő�T�C�Y  (ringbuff�Ɠ����傫��)
#define  COMM_COMMAND_SEND_SIZE_MAX  (264)



// �e��ID
#define COMM_PARENT_ID    (0)

// �ʐM�Ń��j���[���o�����ꍇ�̖߂�l
#define  COMM_RETVAL_NULL    (0)     ///< �I��
#define  COMM_RETVAL_CANCEL  (1)   ///< user�L�����Z��
#define  COMM_RETVAL_OK      (2)              ///< �I������
#define  COMM_RETVAL_ERROR   (3)              ///< �ʐM�G���[
#define  COMM_RETVAL_DIFFER_REGULATION   (4)              ///< ���M�����[�V�������قȂ�


// �ʐM�̎��  
#define  COMM_MODE_TRADE    (0)     // 1on1 �|�P��������
#define  COMM_MODE_BATTLE_SINGLE (1)    // 1vs1 �o�g��
#define  COMM_MODE_BATTLE_DOUBLE (2)    // 1vs1 �_�u���o�g��
#define  COMM_MODE_BATTLE_MIX_1ON1 (3)  // 1vs1 �~�b�N�X�o�g��
#define  COMM_MODE_BATTLE_MULTI (4)     // 2vs2 �}���`�o�g��
#define  COMM_MODE_BATTLE_MIX_2ON2 (5)  // 2vs2 �~�b�N�X�o�g��
#define  COMM_MODE_NUT_CRASH (6)        // 2-5  �؂̎��N���b�V��
#define  COMM_MODE_RECORD (7)           // 2-4  ���R�[�h�R�[�i�[
#define  COMM_MODE_CONTEST (8)           // 2-4  �R���e�X�g
#define  COMM_MODE_UNION (9)            // ���j�I�����[��
#define  COMM_MODE_UNDERGROUND (10)      // 16  �n��
#define  COMM_MODE_POLLOCK4 (11)           // 4�l�|���b�N
#define  COMM_MODE_POLLOCK16 (12)           // 16�l�|���b�N
#define  COMM_MODE_PICTURE (13)            // ���j�I�����[��->���G����
#define  COMM_MODE_POKETCH (14)            // �ۂ�����
#define  COMM_MODE_MYSTERY (15)            // �s�v�c�ʐM
#define  COMM_MODE_TOWER_MULTI (16)            // �o�g���^���[�}���`
#define  COMM_MODE_PARTY (17)          // �p�[�e�B�[�Q�[���X�L����
#define  COMM_MODE_UNION_APP (18)            // ���j�I�����[���A�v���P�[�V����
#define  COMM_MODE_BATTLE_SINGLE_WIFI (19)    // 1vs1 WIFI �o�g��
#define  COMM_MODE_BATTLE_DOUBLE_WIFI (20)    // 1vs1 WIFI �_�u��
#define  COMM_MODE_TRADE_WIFI (21)    // WIFI����
#define  COMM_MODE_VCHAT_WIFI (22)    // WIFI VCT
#define  COMM_MODE_LOGIN_WIFI (23)    // WIFI LOGIN
#define  COMM_MODE_DPW_WIFI (24)    // DPW WIFI
#define  COMM_MODE_FUSIGI_WIFI (25)    // �ӂ��� WIFI
#define  COMM_MODE_MAX (26)
#define  COMM_MODE_NONE (27)   // �T�[�r�X�؂�ւ����s��Ȃ����Ɏg�p

// �ʐM�̎�� �ɑΉ������q�@MIN��
#define  COMM_MODE_TRADE_NUM_MIN    (1)     // 1on1 �|�P��������
#define  COMM_MODE_BATTLE_SINGLE_NUM_MIN (1)    // 1vs1 �o�g��
#define  COMM_MODE_BATTLE_DOUBLE_NUM_MIN (1)    // 1vs1 �_�u���o�g��
#define  COMM_MODE_BATTLE_MIX_1ON1_NUM_MIN (1)  // 1vs1 �~�b�N�X�o�g��
#define  COMM_MODE_BATTLE_MULTI_NUM_MIN (3)     // 2vs2 �}���`�o�g��
#define  COMM_MODE_BATTLE_MIX_2ON2_NUM_MIN (3)  // 2vs2 �~�b�N�X�o�g��
#define  COMM_MODE_NUT_CRASH_NUM_MIN (1)        // 2-5  �؂̎��N���b�V��
#define  COMM_MODE_RECORD_NUM_MIN (1)           // 2-4  ���R�[�h�R�[�i�[
#define  COMM_MODE_CONTEST_NUM_MIN (1)           // 2-4  �R���e�X�g
#define  COMM_MODE_UNION_NUM_MIN (1)            // ���j�I�����[��
#define  COMM_MODE_UNDERGROUND_NUM_MIN (1)      // 16  �n��
#define  COMM_MODE_POLLOCK4_NUM_MIN (1)           // 4�l�|���b�N
#define  COMM_MODE_POLLOCK16_NUM_MIN (1)           // 16�l�|���b�N
#define  COMM_MODE_PICTURE_NUM_MIN (1)            // ���j�I�����[��->���G����
#define  COMM_MODE_POKETCH_NUM_MIN (1)            // �ۂ�����
#define  COMM_MODE_MYSTERY_NUM_MIN (1)            // �s�v�c�ʐM
#define  COMM_MODE_TOWER_MULTI_NUM_MIN (1)            // �o�g���^���[�}���`
#define  COMM_MODE_PARTY_NUM_MIN (1)            // party
#define  COMM_MODE_UNION_APP_NUM_MIN (1)            // ���j�I�����[��APP
#define  COMM_MODE_BATTLE_SINGLE_WIFI_NUM_MIN (1)    // 1vs1 WIFI�o�g��
#define  COMM_MODE_BATTLE_DOUBLE_WIFI_NUM_MIN (1)    // 1vs1 WIFI�o�g��
#define  COMM_MODE_TRADE_WIFI_NUM_MIN (1)    // �g���[�h
#define  COMM_MODE_VCHAT_WIFI_NUM_MIN (1)    // �{�C�X�`���b�g
#define  COMM_MODE_LOGIN_WIFI_NUM_MIN (1)    // LOGIN�̂�
#define  COMM_MODE_DPW_WIFI_NUM_MIN (0)    // ���E����,�o�g���^���[
#define  COMM_MODE_FUSIGI_WIFI_NUM_MIN (0)    // �ӂ���WIFI

// �ʐM�̎�� �ɑΉ������q�@MAX��
#define  COMM_MODE_TRADE_NUM_MAX    (1)     // 1on1 �|�P��������
#define  COMM_MODE_BATTLE_SINGLE_NUM_MAX (1)    // 1vs1 �o�g��
#define  COMM_MODE_BATTLE_DOUBLE_NUM_MAX (1)    // 1vs1 �_�u���o�g��
#define  COMM_MODE_BATTLE_MIX_1ON1_NUM_MAX (1)  // 1vs1 �~�b�N�X�o�g��
#define  COMM_MODE_BATTLE_MULTI_NUM_MAX (3)     // 2vs2 �}���`�o�g��
#define  COMM_MODE_BATTLE_MIX_2ON2_NUM_MAX (3)  // 2vs2 �~�b�N�X�o�g��
#define  COMM_MODE_NUT_CRASH_NUM_MAX (3)        // 2-5  �؂̎��N���b�V��
#define  COMM_MODE_RECORD_NUM_MAX (4)           // 2-4  ���R�[�h�R�[�i�[
#define  COMM_MODE_CONTEST_NUM_MAX (3)           // 2-4  �R���e�X�g
#define  COMM_MODE_UNION_NUM_MAX (4)            // ���j�I�����[��
#define  COMM_MODE_UNDERGROUND_NUM_MAX (COMM_CHILD_MAX)      // 16  �n��
#define  COMM_MODE_POLLOCK4_NUM_MAX (3)           // 4�l�|���b�N
#define  COMM_MODE_POLLOCK16_NUM_MAX (COMM_CHILD_MAX)           // 16�l�|���b�N
#define  COMM_MODE_PICTURE_NUM_MAX (COMM_MODE_UNION_NUM_MAX)            // ���j�I�����[��->���G����
#define  COMM_MODE_POKETCH_NUM_MAX (1)           // �ۂ�����
#define  COMM_MODE_MYSTERY_NUM_MAX (4)           // �s�v�c�ʐM
#define  COMM_MODE_TOWER_MULTI_NUM_MAX (1)            // �o�g���^���[�}���`
#define  COMM_MODE_PARTY_NUM_MAX (1)           // party
#define  COMM_MODE_UNION_APP_NUM_MAX (4)           // unionapp
#define  COMM_MODE_BATTLE_SINGLE_WIFI_NUM_MAX (1)    // 1vs1 WIFI �o�g��
#define  COMM_MODE_BATTLE_DOUBLE_WIFI_NUM_MAX (1)    // 1vs1 WIFI �o�g��
#define  COMM_MODE_TRADE_WIFI_NUM_MAX (1)    // �g���[�h
#define  COMM_MODE_VCHAT_WIFI_NUM_MAX (1)    // �{�C�X�`���b�g
#define  COMM_MODE_LOGIN_WIFI_NUM_MAX (1)    // LOGIN�̂�
#define  COMM_MODE_DPW_WIFI_NUM_MAX (0)    // ���E����,�o�g���^���[
#define  COMM_MODE_FUSIGI_WIFI_NUM_MAX (0)    // �ӂ���WIFI


// �o�g�����M�����[�V�����̎��  
#define  COMM_REG_NORMAL     (0)
#define  COMM_REG_FANCY      (1)
#define  COMM_REG_YELLOW     (2)
#define  COMM_REG_PEARL      (3)
#define  COMM_REG_DIAMOND    (4)
#define  COMM_REG_ORIGINAL1  (5)
#define  COMM_REG_ORIGINAL2  (6)
#define  COMM_REG_ORIGINAL3  (7)
#define  COMM_REG_ORIGINAL4  (8)
#define  COMM_REG_ORIGINAL5  (9)
#define  COMM_REG_ORIGINAL6  (10)
#define  COMM_REG_ORIGINAL7  (11)
#define  COMM_REG_ORIGINAL8  (12)
#define  COMM_REG_ORIGINAL9  (13)
#define  COMM_REG_MAX        (14)


#define CURRENT_PLAYER_WORD_IDX    (0)    // �����̖��O������o�b�t�@�̏ꏊ
#define TARGET_PLAYER_WORD_IDX     (1)     // �ΏۂƂȂ閼�O������o�b�t�@�̏ꏊ
#define ASSAILANT_PLAYER_WORD_IDX  (2)     // ��Q�҂ƂȂ閼�O������o�b�t�@�̏ꏊ


#define CC_NOT_FOUND_PARENT_INFO (0) // �e�@��񂪂Ȃ��ꍇ  
#define CC_BUSY_STATE  (1)  //�ʐM�̓�����Ԃ��J�ڒ��ŁA�ڑ��ɂ����Ȃ��ꍇ
#define CC_CONNECT_STARTING (2) // �ڑ��֐����Ăяo������


// MYSTATUS�𑗂邽�߂̗̈�
#define COMM_SEND_MYSTATUS_SIZE   (32)
#define COMM_SEND_REGULATION_SIZE (32)

#endif// _COMM_DEF_H_


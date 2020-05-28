//=============================================================================
/**
 * @file	heapdefine.h
 * @brief	�|�P�����c�o �q�[�v��ʎw��
 * @author	taya  GAME FREAK Inc.
 */
//=============================================================================
#ifndef __HEAPDEFINE_H__
#define __HEAPDEFINE_H__



//----------------------------------------------------------------------------
/**
 *  ��{�q�[�v��`  
 *
 *  �V�X�e���A�A�v���ȂǑ�܂��Ȑݒ�̂ݍs���B
 *  �ŏ��ɃA���[�i���烁�������m�ۂ���̂͂����̃q�[�v�O���[�v�̂݁B
 *
 *  �e��A�v���͂����̃q�[�v���璼�ڃ��������A���P�[�g����̂ł͂Ȃ��A
 *  �A�v���p�̑傫�ȃq�[�v���ɂ���Ƀq�[�v���쐬���A��������A���P�[�g����B
 *
 */
//----------------------------------------------------------------------------
typedef enum {
	HEAPID_BASE_SYSTEM,
	HEAPID_BASE_SAVE,
	_HEAPID_BASE_DEBUG,
	HEAPID_BASE_APP,

	HEAPID_BASE_MAX,
}BASE_HEAPID;

#define HEAPID_BASE_DEBUG  (HEAPID_BASE_APP)

//----------------------------------------------------------------------------
/**
 *  ���[�U�[�q�[�v��`  
 *
 *  �e�A�v�����ƂɌŗL�̃q�[�v�h�c��؂�B
 *  �A���[�i���烁�������m�ۂ���̂ł͂Ȃ��A��L�̊�{�q�[�v�̒����炳���
 *  �q�[�v���쐬���āA���̃q�[�v���烁�����u���b�N���A���P�[�g����B
 */
//----------------------------------------------------------------------------
typedef enum {
	HEAPID_FIELD = HEAPID_BASE_MAX,		// �t�B�[���h
	HEAPID_BATTLE,						// �퓬
	HEAPID_BAG,							// �o�b�O
	HEAPID_POKETCH_MAIN,				// �|�P�b�`�i���C���j
	HEAPID_POKETCH_APP,					// �|�P�b�`�i�A�v���j
	HEAPID_BOX_SYSTEM,					// �{�b�N�X�i�V�X�e������j
	HEAPID_BOX_VIEW,					// �{�b�N�X�i�`�惏�[�N�j
	HEAPID_WORLD,						//���[���h
	HEAPID_POKELIST,					// �|�P�������X�g
	HEAPID_IMAGECLIP_DATA,				// �C���[�W�N���b�v�f�[�^���[�N
	HEAPID_IMAGECLIP_DRAW,				// �C���[�W�N���b�v�`�惏�[�N
    HEAPID_COMMUNICATION,               // �ʐM
	HEAPID_TITLE,						// �^�C�g�����
	HEAPID_TOWNMAP,						// �^�E���}�b�v
	HEAPID_NAMEIN,						// ���O����
	HEAPID_POKESTATUS,					// �|�P�����X�e�[�^�X���
	HEAPID_CONTEST,						// �R���e�X�g�S�̃V�X�e��
	HEAPID_ACTIN,						// �R���e�X�g�F���Z�͕���
	HEAPID_VISUAL,						// �R���e�X�g�F�r�W���A������
	HEAPID_DANCE,						// �R���e�X�g�F�_���X����
	HEAPID_CONRES,						// �R���e�X�g�F���ʔ��\���
	HEAPID_TR_CARD,						// �g���[�i�[�J�[�h
	HEAPID_TRADELIST,					// �|�P�����������X�g���
	HEAPID_DEBUG_APPLICATION,			// �f�o�b�O�A�v���P�[�V�����p
	HEAPID_OPENING,						// �I�[�v�j���O
    HEAPID_DIGFOSSIL,                   // ���Ό@��
    HEAPID_TITLE_DEMO,                  // �^�C�g���f��30
	HEAPID_UNIONROOM,					// ���j�I�����[���p
	HEAPID_EVENT,						// �C�x���g�p
	HEAPID_UNDERGROUND,					// �n���ł̉�b�p
	HEAPID_PMS_INPUT_SYSTEM,			// �ȈՉ�b���͉�ʁi�V�X�e������j
	HEAPID_PMS_INPUT_VIEW,				// �ȈՉ�b���͉�ʁi�`�惏�[�N�j
	HEAPID_NUTSTAG,						// �؂̎��^�O���
	HEAPID_ZUKAN,						// �}�ӗp
	HEAPID_CONFIG,						// �R���t�B�O�p
	HEAPID_OEKAKI,						// ���G�����{�[�h�p
	HEAPID_MAILSYS,						// ���[���p
	HEAPID_MAILVIEW,					// ���[���{���p
	HEAPID_FANTASYNOTE,					// �`���m�[�g�p
	HEAPID_MAILBOX,						// ���[���{�b�N�X�p
	HEAPID_PORUTO,						// �|���g�R���g���[���p
	HEAPID_PORUTO_CASE,					// �|���g�P�[�X�p
	HEAPID_PORUTO_DEMO,					// �|���g�f���p
	HEAPID_EV_POKESELECT,				// �J�n�|�P�����Z���N�g�p
	HEAPID_MYSIGN,						// �g���[�i�[�T�C���p
    HEAPID_WIFIMENU,                    // WIFI���j���[
    HEAPID_WIFIEARTH,                   // ���E�ʐM����
	HEAPID_RECORD,						// ���R�[�h�R�[�i�[�p
    HEAPID_WIFINOTE,                    // WIFI�F�B�蒠
	HEAPID_CUSTOM_BALL,					// �J�X�^���{�[��
    HEAPID_WIFIP2PMATCH,                // WIFI P2P �}�b�`���O��ʗp
	HEAPID_NUT_MIXER,					// �؂̎��܂��܂��V�X�e��
	HEAPID_NMIXER_GM,					// �؂̎��܂��܂��{��
	HEAPID_DEMO_TRADE_MAIN,				// �|�P���������f���i���C���j
	HEAPID_DEMO_TRADE_SUB,				// �|�P���������f���i�T�u�j
	HEAPID_BTLTOWER_SCR,				// �o�g���^���[�X�N���v�g
	HEAPID_DENDOU_PC,					// �a������PC��ʁi�V�X�e���j
	HEAPID_DENDOU_PC_VIEW,				// �a������PC��ʁi�`��j
	HEAPID_WORLDTRADE,					// wifi���E�������
	HEAPID_DENDOU_DEMO,					// �a������f��
	HEAPID_FIELD_FLDOBJ_MDL,			// �t�B�[���h�@�t�B�[���hOBJ�@���f��
	HEAPID_FIELD_FLDOBJ_ANM,			// �t�B�[���h�@�t�B�[���hOBJ�@�A�j��
	HEAPID_FIELD_FE,					// �t�B�[���h�@�t�B�[���h�G�t�F�N�g
	HEAPID_WAZAOSHIE,					// �Z����/�v���o�����
	HEAPID_WIFI_BATTLETOWER,			// WIFI�o�g���^���[�ڑ����
	HEAPID_FIELD_FE_BLACT_MDL,			// �t�B�[���h�@�t�B�[���h�G�t�F�N�g�@���f��
	HEAPID_FIELD_FE_BLACT_ANM,			// �t�B�[���h�@�t�B�[���h�G�t�F�N�g�@�A�j��
	HEAPID_EGG_DEMO,					// ���܂��z���f��
	HEAPID_SHIPDEMO,					// �D�f��
	HEAPID_ITEMSHINKA,					// �A�C�e���i���p
	HEAPID_BTOWER_APP,					// �^���[�֘A�A�v��
	HEAPID_ENDING_DEMO,					// �G���f�B���O�f��
	HEAPID_OP_DEMO,						// �I�[�v�j���O�f��
	HEAPID_GAMEINIT,					// �Q�[������������
	HEAPID_AGBCARTRIDGE,					// �`�f�a�J�[�g���b�W��������Ă�����
	HEAPID_SLOT,						// �X���b�g
	HEAPID_RANKING_VIEW,				// �M�l�X�z�[�������L���O���
	HEAPID_STARTMENU,					// �X�^�[�g���j���[���
	HEAPID_INTRO,						// �����f��
	HEAPID_INTRO_TV,					// �����f���s�u
	HEAPID_SYOUJYOU,					// �\����
	HEAPID_POKEMONRANGER,					// �|�P���������W���[�Ƃ̐ڑ����
	HEAPID_MYSTERYGIFT,					// �ӂ����Ȃ�������̉��
	HEAPID_MYSTERYCARD,					// �ӂ����Ȃ�������� �J�[�h��������
	HEAPID_BACKUPCONT,					// �o�b�N�A�b�v�R���g���[���p
	HEAPID_UNIONBOARD,
	HEAPID_GAMECLEAR,					// �Q�[���N���A���̃f�[�^�Z�[�u���
    HEAPID_COMMICON,                    // �ʐM�A�C�R��
	HEAPID_MAX,
}HEAPID;


#endif

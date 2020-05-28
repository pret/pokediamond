//==============================================================================
/**
 * @file	field_effect_code.h
 * @brief	�t�B�[���h�G�t�F�N�g�p�V���{����`
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FIELD_EFFECT_CODE_H_FILE
#define FIELD_EFFECT_CODE_H_FILE

//==============================================================================
//	�G�t�F�N�g
//==============================================================================
//--------------------------------------------------------------
///	�G�t�F�N�gID
//--------------------------------------------------------------
enum
{
	FE_FLD_SHADOW = 0,								///<�t�B�[���hOBJ�@�e
	FE_FLD_REFLECT,									///<�t�B�[���hOBJ�@�f�荞��
	FE_UG_TRAP,										///<�n���@�
	FE_UG_TRAP_HOLE,								///<�n���@㩁@��
	FE_UG_TRAP_DIR,									///<�n���@㩁@����
	FE_UG_TRAP_FLAG,								///<�n���@㩁@��
	FE_UG_TRAP_EXCLAMATION,							///<�n���@㩁@!�}�[�N
	FE_UG_TRAP_OK,									///<�n���@㩁@OK�}�[�N
	FE_UG_TRAP_SMOG,								///<�n���@㩁@��
	FE_UG_TRAP_GFLASH,								///<�n���@㩁@���܃}�[�N
	FE_UG_DRILL,									///<�n���@�h�������o
	FE_FLD_FOOTMARK,								///<�t�B�[���hOBJ�@����
	FE_FLD_BOARD,									///<�t�B�[���hOBJ�@�Ŕ�
	FE_FLD_SEEDGROUND,								///<�t�B�[���hOBJ�@�؂̎��y
	FE_FLD_SNOWBALL,								///<�t�B�[���hOBJ�@�ዅ
	FE_FLD_BOOK,									///<�t�B�[���hOBJ�@�{
	FE_FLD_ARROW,									///<�t�B�[���hOBJ�@���
	FE_FLD_NAMIPOKE,								///<�t�B�[���hOBJ�@�g���|�P����
	FE_FLD_ROCKRIDE,								///<�t�B�[���hOBJ�@�ǂ̂ڂ�|�P����
	FE_FLD_RIPPLE,									///<�t�B�[���hOBJ�@���g��
	FE_FLD_NRIPPLE,									///<�t�B�[���hOBJ�@���g��
	FE_FLD_GRASS,									///<�t�B�[���hOBJ�@���폜
	FE_FLD_GYOE,									///<�t�B�[���hOBJ�@�M���G�[
	FE_FLD_SPLASH,									///<�t�B�[���hOBJ�@�����Ԃ�
	FE_UG_REDFRAME,									///<�n���@�g
	FE_FLD_KEMURI,									///<�t�B�[���hOBJ�@�y��
	FE_FLD_LGRASS,									///<�t�B�[���hOBJ�@������
	FE_FLD_NGRASS,									///<�t�B�[���hOBJ�@����
	FE_FLD_HIDE,									///<�t�B�[���hOBJ�@�B�ꖪ
	FE_FLD_HKEMURI,									///<�t�B�[���hOBJ�@�B�ꖪ��
	FE_FLD_SEED_EFF,								///<�t�B�[���hOBJ�@�؂̎��G�t�F�N�g
	FE_FLD_DOOR2,									///<�t�B�[���hOBJ�@�h�A�Q
	
	FE_PROC_MAX,									///<�ő�
};

//==============================================================================
//	�r���{�[�h
//==============================================================================
//--------------------------------------------------------------
///	�r���{�[�h�w�b�_�[ID
//--------------------------------------------------------------
enum
{
	FE_BLACT_H_ID_GRASS = 0,								///<��
	FE_BLACT_H_ID_GYOE,										///<�M���G�[
	FE_BLACT_H_ID_REFLECT,									///<�f�肱��
	FE_BLACT_H_ID_SPLASH,									///<����
	FE_BLACT_H_ID_REDFRAME,									///<�Ԙg
	FE_BLACT_H_ID_GRASS_ENCOUNT_SMALL,						///<�G���J�E���g���h�ꏬ
	FE_BLACT_H_ID_GRASS_ENCOUNT_BIG,						///<�G���J�E���g���h���
	FE_BLACT_H_ID_GRASS_ENCOUNT_KIRAKIRA,					///<�G���J�E���g���h�ꂫ�炫��
	FE_BLACT_H_ID_KEMURI,									///<�y��
	FE_BLACT_H_ID_LGRASS,									///<������
	FE_BLACT_H_ID_NGRASS,									///<����
	FE_BLACT_H_ID_HKEMURI,									///<�B�ꖪ�y��
	FE_BLACT_H_ID_GYOE_SAISEN,								///<�Đ�M���G�[
	FE_BLACT_H_ID_SEED_EFF,									///<�؂̎��G�t�F�N�g
	
	FE_BLACT_H_ID_NOT,										///<����ID
};

//--------------------------------------------------------------
///	�r���{�[�h���\�[�X�@���f��ID
//--------------------------------------------------------------
enum
{
	FE_RESID_MDL_GRASS = 0,									///<��
	FE_RESID_MDL_GYOE,										///<�M���G�[
	FE_RESID_MDL_REFLECT,									///<�f�肱��
	FE_RESID_MDL_SPLASH,									///<����
	FE_RESID_MDL_REDFRAME,									///<�Ԙg
	FE_RESID_MDL_GRASS_ENCOUNT,								///<���G���J�E���g
	FE_RESID_MDL_KEMURI,									///<�y��
	FE_RESID_MDL_LGRASS,									///<������
	FE_RESID_MDL_NGRASS,									///<����
	FE_RESID_MDL_HKEMURI,									///<�B�ꖪ�y��
	FE_RESID_MDL_GYOE_SAISEN,								///<�Đ�M���G�[
	FE_RESID_MDL_SEED_EFF,									///<�؂̎��G�t�F�N�g
};

//--------------------------------------------------------------
///	�r���{�[�h���\�[�X�@�A�j��ID
//--------------------------------------------------------------
enum
{
	FE_RESID_ANM_GRASS = 0,									///<��
	FE_RESID_ANM_GYOE,										///<�M���G�[
	FE_RESID_ANM_SPLASH,									///<����
	FE_RESID_ANM_GRASS_ENCOUNT_SMALL,						///<�G���J�E���g���h�ꏬ
	FE_RESID_ANM_GRASS_ENCOUNT_BIG,							///<�G���J�E���g���h���
	FE_RESID_ANM_GRASS_ENCOUNT_KIRAKIRA,					///<�G���J�E���g���h�ꂫ�炫��
	FE_RESID_ANM_KEMURI,									///<�y��
	FE_RESID_ANM_LGRASS,									///<������
	FE_RESID_ANM_NGRASS,									///<����
	FE_RESID_ANM_HKEMURI,									///<�B�ꖪ�y��
	FE_RESID_ANM_GYOE_SAISEN,								///<�Đ�M���G�[
	FE_RESID_ANM_SEED_EFF,									///<�؂̎��G�t�F�N�g
};

//--------------------------------------------------------------
///	�r���{�[�h���\�[�X�@�e�N�X�`��ID
//--------------------------------------------------------------
enum
{
	FE_RESID_TEX_GRASS = 0,									///<��
	FE_RESID_TEX_GYOE,										///<�M���G�[
	FE_RESID_TEX_SPLASH,									///<����
	FE_RESID_TEX_REDFRAME,									///<�Ԙg
	FE_RESID_TEX_GRASS_ENCOUNT_SMALL,						///<�G���J�E���g���h�ꏬ
	FE_RESID_TEX_GRASS_ENCOUNT_BIG,							///<�G���J�E���g���h���
	FE_RESID_TEX_GRASS_ENCOUNT_KIRAKIRA,					///<�G���J�E���g���h�ꂫ�炫��
	FE_RESID_TEX_KEMURI,									///<�y��
	FE_RESID_TEX_LGRASS,									///<������
	FE_RESID_TEX_NGRASS,									///<����
	FE_RESID_TEX_HKEMURI,									///<�B�ꖪ�y��
	FE_RESID_TEX_GYOE_SAISEN,								///<�Đ�M���G�[
	FE_RESID_TEX_SEED_EFF,									///<�؂̎��G�t�F�N�g
	
	FE_RESID_TEX_MAX,										///<�ő�
};

#endif //FIELD_EFFECT_CODE_H_FILE

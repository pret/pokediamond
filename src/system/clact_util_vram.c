//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util_vram.c
 *@brief	�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���[���g�p���L�����N�^�f�[�^�A�p���b�g�f�[�^��Vram�ɓ]������V�X�e��
 *@author	tomoya takahashi
 *@data		2005.09.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "assert.h"

#include "char_manager.h"
#include "pltt_manager.h"

#define __CLACT_UTIL_VRAM_H_GLOBAL
#include "include/system/clact_util_vram.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////////
// �L�����N�^�f�[�^�]���֐�
// �I�t�Z�b�g�^�C�v
// �ォ�珇�ɋl�߂�Vram�ɓ]�����Ă����܂��B
// ����������Ȃǂ��Ă���������̈��F�����āA
// ���̗̈�ɍēx�Ⴄ�L�����N�^��]������Ȃǂ��ł��܂���B
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_CharManagerSet( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	CHAR_MANAGER_HEADER char_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	// �L�����N�^�f�[�^�擾
	char_data.res_file = CLACT_U_ResManagerGetResObjResChar(resObj);

	char_data.type = CLACT_U_ResManagerGetResObjVramType(resObj);
	char_data.id	= CLACT_U_ResManagerGetResObjID(resObj);
	char_data.cont_type = CHARM_CONT_OFFSET;

	// �o�^
	return CharSet(&char_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�i�����j
 *
 *@param	resTbl		���\�[�X�I�u�W�F�e�[�u���̃|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerSets( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ���[�v�p
	BOOL check;
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){

		if( resTbl->tbl[i] ){
			check = CLACT_U_CharManagerSet(resTbl->tbl[i]);
			GF_ASSERT_MSG( check, "�L�����N�^�f�[�^�o�^���s\n" );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�
 *				�}�b�s���O���[�h�����̏�ԂɕύX���郂�[�h
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_CharManagerSetCharModeAdjust( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	CHAR_MANAGER_HEADER char_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	// �L�����N�^�f�[�^�擾
	char_data.res_file = CLACT_U_ResManagerGetResObjResChar(resObj);

	char_data.type = CLACT_U_ResManagerGetResObjVramType(resObj);
	char_data.id	= CLACT_U_ResManagerGetResObjID(resObj);
	char_data.cont_type = CHARM_CONT_OFFSET;

	// �o�^
	return CharSetCharModeAdjust(&char_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�i�����j
 *				�}�b�s���O���[�h�����̏�ԂɕύX���郂�[�h
 *
 *@param	resTbl		���\�[�X�I�u�W�F�z��̃|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerSetsCharModeAdjust( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ���[�v�p
	BOOL check;	// �����p
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){
		if( resTbl->tbl[ i ] ){
			check = CLACT_U_CharManagerSetCharModeAdjust(resTbl->tbl[i]);
			GF_ASSERT_MSG( check, "�L�����N�^�f�[�^�o�^���s\n" );
		}
	}
}



//////////////////////////////////////////////////////////////////////////////
// �L�����N�^�f�[�^�]���֐�
// �G���A�R���g���[���^�C�v
// vram�G���A���P�L�������ƂɊǗ�����z����쐬���āA
// �󂫗̈悩��g�p�ł���vram�G���A���������܂��B
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_CharManagerSetAreaCont( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	CHAR_MANAGER_HEADER char_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	// �L�����N�^�f�[�^�擾
	char_data.res_file = CLACT_U_ResManagerGetResObjResChar(resObj);

	char_data.type = CLACT_U_ResManagerGetResObjVramType(resObj);
	char_data.id	= CLACT_U_ResManagerGetResObjID(resObj);
	char_data.cont_type = CHARM_CONT_AREACONT;

	// �o�^
	return CharSet(&char_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�i�����j
 *
 *@param	resTbl		���\�[�X�I�u�W�F�e�[�u���̃|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerSetsAreaCont( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ���[�v�p
	BOOL check;	// �����p
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){

		if( resTbl->tbl[i] ){
			check = CLACT_U_CharManagerSetAreaCont(resTbl->tbl[i]);
			GF_ASSERT_MSG( check, "�L�����N�^�f�[�^�o�^���s" );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�
 *				�}�b�s���O���[�h�����̏�ԂɕύX���郂�[�h
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_CharManagerSetCharModeAdjustAreaCont( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	CHAR_MANAGER_HEADER char_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	// �L�����N�^�f�[�^�擾
	char_data.res_file = CLACT_U_ResManagerGetResObjResChar(resObj);

	char_data.type = CLACT_U_ResManagerGetResObjVramType(resObj);
	char_data.id	= CLACT_U_ResManagerGetResObjID(resObj);
	char_data.cont_type = CHARM_CONT_AREACONT;

	// �o�^
	return CharSetCharModeAdjust(&char_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�i�����j
 *				�}�b�s���O���[�h�����̏�ԂɕύX���郂�[�h
 *
 *@param	resTbl		���\�[�X�I�u�W�F�z��̃|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerSetsCharModeAdjustAreaCont( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ���[�v�p
	BOOL check;	// �����p
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){
		if( resTbl->tbl[ i ] ){
			check = CLACT_U_CharManagerSetCharModeAdjustAreaCont(resTbl->tbl[i]);
			GF_ASSERT_MSG( check, "�L�����N�^�f�[�^�o�^���s\n" );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^��ύX����
 *
 *	@param	nowTbl		���̃L�����N�^�f�[�^
 *	@param	newTbl		�ύX����L�����N�^�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerChg( CONST_CLACT_U_RES_OBJ_PTR nowTbl, CONST_CLACT_U_RES_OBJ_PTR newTbl )
{
	int id;
	NNSG2dCharacterData* data;
	
	GF_ASSERT(nowTbl);
	GF_ASSERT(newTbl);

	// �v���N�V�ƃL�����N�^�f�[�^�擾
	id = CLACT_U_ResManagerGetResObjID( nowTbl );
	data = CLACT_U_ResManagerGetResObjResChar( newTbl );

	// ����ւ���
	CharDataChg(id, data);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�̍ē]�����s��
 *
 *	@param	resObj	���\�[�X�I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerReTrans( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	int id;
	NNSG2dCharacterData* data;

	GF_ASSERT(resObj);

	// �v���N�V�ƃL�����N�^�f�[�^�擾
	id = CLACT_U_ResManagerGetResObjID( resObj );
	data = CLACT_U_ResManagerGetResObjResChar( resObj );
	
	CharDataChg(id, data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[���烊�\�[�X�I�u�W�F��ID�̃L�����N�^�f�[�^��j��
 *
 *@param	resObj		���\�[�X�I�u�W�F�̃|�C���^
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerDelete( CLACT_U_RES_OBJ_PTR resObj )
{
	int id;
	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	id = CLACT_U_ResManagerGetResObjID(resObj);
	DelChar(id);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[���烊�\�[�X�I�u�W�F�e�[�u���ɑΉ�����f�[�^��j��
 *
 *@param	resTbl		���\�[�X�I�u�W�F�e�[�u��
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerDeletes( CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ���[�v�p
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){
		if( resTbl->tbl[ i ] ){
			CLACT_U_CharManagerDelete(resTbl->tbl[i]);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�C���[�W�v���N�V���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@return	NNSG2dImageProxy*	�C���[�W�v���N�V
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy* CLACT_U_CharManagerGetProxy( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	int id;
	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);

	id = CLACT_U_ResManagerGetResObjID(resObj);
	return GetCharIDProxy( id );	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�QD�}�b�v�L�����N�^��ǂݍ���
 *
 *	@param	resObj		���\�[�X�I�u�W�F
 *	@param	proxy		�]���f�[�^���i�[����v���N�V
 *	@param	base_addr	Vram�x�[�X�A�h���X
 * 
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_2DmapCharLoad( CONST_CLACT_U_RES_OBJ_PTR resObj, NNSG2dImageProxy* proxy, int base_addr )
{
	NNSG2dCharacterData* char_data;
	int	vram_type;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	// �L�����N�^�f�[�^�擾
	char_data = CLACT_U_ResManagerGetResObjResChar(resObj);
	vram_type = CLACT_U_ResManagerGetResObjVramType(resObj);

	
	// �ǂݍ���
	NNS_G2dLoadImage2DMapping( 
			char_data,
			base_addr,
			vram_type,
			proxy );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram�]���p�̃C���[�W�v���N�V���擾
 *
 *@param	charObj	�L�����N�^���\�[�X�I�u�W�F
 *@param	cellObj	�Z�����\�[�X�I�u�W�F
 *
 *@return	NNSG2dImageProxy*	�C���[�W�v���N�V
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy* CLACT_U_CharManagerGetVramTransferProxy( CONST_CLACT_U_RES_OBJ_PTR charObj, CONST_CLACT_U_RES_OBJ_PTR cellObj )
{
	int id;
	NNSG2dCellDataBank* cellData;
	NNSG2dImageProxy* proxy;
	
	GF_ASSERT(charObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(charObj) == CLACT_U_CHAR_RES);
	GF_ASSERT(cellObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(cellObj) == CLACT_U_CELL_RES);
	
	
	// �L�����N�^�f�[�^ID�擾
	id = CLACT_U_ResManagerGetResObjID(charObj);

	// �Z���f�[�^�擾
	cellData = CLACT_U_ResManagerGetResObjResCell(cellObj);
	
	proxy = GetCharVramTransData( id, cellData->pVramTransferData->szByteMax );	
	if(proxy == NULL){
		NNSG2dImageProxy* org;
		org = GetCharIDProxy( id );
		// �R�s�[�쐬
		proxy = GetCharVramTransProxyCopy( org );
	}

	return proxy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z��Vram�]���A�j����Vram�̈���J��
 *
 *@param	pImage		Vram�]���p�ɍ쐬���ꂽ�C���[�W�v���N�V
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerDeleteVramTransferProxy( const NNSG2dImageProxy* pImage )
{
	GF_ASSERT(pImage);
	
	DelVramTransData( pImage );	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�[�W���[�Ƀ��\�[�X�I�u�W�F���̃p���b�g�f�[�^��ݒ�
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_PlttManagerSet( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	PLTT_MANAGER_HEADER pltt_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_PLTT_RES);
	
	// ���\�[�X�擾
	pltt_data.res_file = CLACT_U_ResManagerGetResObjResPltt(resObj);

	pltt_data.type		= CLACT_U_ResManagerGetResObjVramType(resObj);
	pltt_data.id		= CLACT_U_ResManagerGetResObjID(resObj);
	pltt_data.pltt_num	= CLACT_U_ResManagerGetResObjPlttNum(resObj);

	// �o�^
	return PlttSet(&pltt_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃p���b�g�f�[�^��ݒ�i�����j
	 *
 *@param	resTbl		���\�[�X�I�u�W�F�e�[�u���|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerSets( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;
	BOOL check;
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){
		if( resTbl->tbl[ i ] ){
			check = CLACT_U_PlttManagerSet(resTbl->tbl[i]);
			GF_ASSERT_MSG( check ,"�p���b�g�]�����s\n" );
		}
	}
}

// �󂫗̈���������ē]�����܂�
// �������A��̓]���֐����g�p���Ă��̌�ɓ]�������
// �㏑������܂��B
//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�[�W���[�Ƀ��\�[�X�I�u�W�F���̃p���b�g�f�[�^��ݒ�
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 * CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F
 * CLACT_U_ResManagerResAddPltt�֐��Ȃǂ̖߂�l
 * �ǂݍ��񂾃��\�[�X�̃f�[�^�@�Ǘ�ID�Ȃǂ��i�[����Ă��܂��B
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_PlttManagerSetCleanArea( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	PLTT_MANAGER_HEADER pltt_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_PLTT_RES);
	
	// ���\�[�X�擾
	pltt_data.res_file = CLACT_U_ResManagerGetResObjResPltt(resObj);

	pltt_data.type		= CLACT_U_ResManagerGetResObjVramType(resObj);
	pltt_data.id		= CLACT_U_ResManagerGetResObjID(resObj);
	pltt_data.pltt_num	= CLACT_U_ResManagerGetResObjPlttNum(resObj);

	// �o�^
	return PlttSetCleanArea(&pltt_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃p���b�g�f�[�^��ݒ�i�����j
 *
 *@param	resTbl		���\�[�X�I�u�W�F�e�[�u���|�C���^
 *
 *@return	none
 *
 * CLACT_U_RES_OBJ_TBL�@���\�[�X�I�u�W�F�e�[�u��
	typedef struct {
		CLACT_U_RES_OBJ_PTR*	tbl;// �|�C���^���i�[����e�[�u���̃|�C���^
		int		tbl_num;			// �e�[�u���v�f��
		int		tbl_now;			// ���݊i�[��
	} CLACT_U_RES_OBJ_TBL;
	��̍\���̂����̊֐��ō쐬�ł��܂��B
	GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerSetsCleanArea( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;
	BOOL check;
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){
		if( resTbl->tbl[ i ] ){
			check = CLACT_U_PlttManagerSetCleanArea(resTbl->tbl[i]);
			GF_ASSERT_MSG( check, "�p���b�g�]�����s\n" );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�ύX
 *
 *	@param	nowObj		���̃p���b�g�f�[�^�̃��\�[�X�I�u�W�F
 *	@param	newObj		�ύX����p���b�g�̃��\�[�X�I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerChg( CONST_CLACT_U_RES_OBJ_PTR nowObj, CONST_CLACT_U_RES_OBJ_PTR newObj )
{
	NNSG2dPaletteData* data;
	int id;
	int trans_num;
	
	GF_ASSERT(nowObj);
	GF_ASSERT(newObj);

	// �v���N�V�ƃp���b�g�f�[�^�擾
	id = CLACT_U_ResManagerGetResObjID( nowObj );
	
	data = CLACT_U_ResManagerGetResObjResPltt( newObj );
	
	// ����ւ���
	PlttDataChg(id, data );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�̍ē]�����s��
 *
 *	@param	resObj	���\�[�X�I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerReTrans( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	NNSG2dPaletteData* data;
	int id;
	int trans_num;
	
	GF_ASSERT(resObj);

	// �v���N�V�ƃp���b�g�f�[�^�擾
	id = CLACT_U_ResManagerGetResObjID( resObj );
	
	data = CLACT_U_ResManagerGetResObjResPltt( resObj );

	// ����ւ���
	PlttDataChg(id, data );

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�W���[���烊�\�[�X�I�u�W�F��ID�̃p���b�g�f�[�^��j��
 *
 *@param	resObj		���\�[�X�I�u�W�F�̃|�C���^
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerDelete( CLACT_U_RES_OBJ_PTR resObj )
{
	int id;
	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_PLTT_RES);
	
	id = CLACT_U_ResManagerGetResObjID(resObj);
	DelPltt(id);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�W���[���烊�\�[�X�I�u�W�F��ID�̃p���b�g�f�[�^��j��
 *
 *@param	resTbl		���\�[�X�I�u�W�F�e�[�u���̃|�C���^
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerDeletes( CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ���[�v�p
	
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){

		if( resTbl->tbl[ i ] ){
			CLACT_U_PlttManagerDelete(resTbl->tbl[i]);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�v���N�V���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F�p�����[�^
 *@param	pImage	�֘A������C���[�W�v���N�V
 *
 *@return	�p���b�g�v���N�V
 *
 *
 */
//-----------------------------------------------------------------------------
const NNSG2dImagePaletteProxy* CLACT_U_PlttManagerGetProxy( CONST_CLACT_U_RES_OBJ_PTR resObj, NNSG2dImageProxy* pImage )
{
	int id;
	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_PLTT_RES);

	id = CLACT_U_ResManagerGetResObjID(resObj);

	if( pImage ){
		return GetPlttIDProxyJoin(id, pImage);
	}

	return GetPlttIDProxy( id );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�^����Ă���p���b�g�����Ԃ̃p���b�g�ɓ]������Ă��邩��Ԃ�
 *
 *	@param	resObj		���\�[�X�I�u�W�F
 *	@param	vram		vram�^�C�v
 *
 *	@retval	CLACT_U_PLTT_NO_NONE�ȊO	�]�����ꂽ�p���b�g�ԍ�
 *	@retval	CLACT_U_PLTT_NO_NONE		�p���b�g�]������Ă��Ȃ�
 *
 * vram�^�C�v
 *	NNS_G2D_VRAM_TYPE_2DMAIN    �Q�c�O���t�B�b�N�X�G���W���`�p
 *  NNS_G2D_VRAM_TYPE_2DSUB     �Q�c�O���t�B�b�N�X�G���W���a�p
 *
 * resObj
 *	GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerGetIDResObjPtr(CONST_CLACT_U_RES_MANAGER_PTR resm, int id);
 *	�֐��Ŏ擾���Ă��������B
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CLACT_U_PlttManagerGetPlttNo( CONST_CLACT_U_RES_OBJ_PTR resObj, NNS_G2D_VRAM_TYPE type )
{
	int no;
	const NNSG2dImagePaletteProxy* imgpltt;

	imgpltt = CLACT_U_PlttManagerGetProxy( resObj, NULL );
	no =  NNS_G2dGetImagePaletteLocation( imgpltt, type );

	// addr->no�ɂ���
	if( no != CLACT_U_PLTT_NO_NONE ){
		no /= 32;
	}

	return no;
}

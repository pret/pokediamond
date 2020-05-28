//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util.c
 *@brief	�Z���A�N�^�[�̓o�^���ȒP�ɍs���V�X�e��
 *@author	tomoya takahashi
 *@data		2005.09.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#include "include/system/render_oam.h"

#include "include/communication/wm_icon.h"

#include "include/gflib/char_manager.h"
#include "include/gflib/pltt_manager.h"

#define __CLACT_UTIL_H_GLOBAL
#include "include/system/clact_util.h"


//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define	CLACT_U_HEADER_DATA_NONE	(0xffffffff)	// ��Ƀ}���`�Z���̗L���ɂ��悤

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�����f�[�^�ꎞ�ǂݍ��ݗp�e�[�u��
//	
//=====================================
typedef struct {
	int char_id;		// �L�����N�^ID
	int pltt_id;		// �p���b�gID
	int cell_id;		// �Z��ID
	int cellanm_id;		// �Z���A�j��ID
	int multicell_id;	// �}���`�Z��ID
	int multicellanm_id;// �}���`�Z���A�j��ID
	int vram_trans;		// Vram�]���t���O
	int	priority;		// BG�D�揇��
} CLACT_HEADER_DATA_TMP;



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static int getHeaderTblNum(char* buff);
static void loadHeaderTbl(char* buff, CLACT_HEADER_DATA_TMP* tbl, int num);
static void loadHeaderOne(char* buff, char** char_id, char** pltt_id, char** cell_id, char** cellanm_id, char** multicell_id, char** multicellanm_id, char** vram_trans, char** priority);
static void setHeaderOne(CLACT_HEADER_DATA_TMP* tbl, char* char_id, char* pltt_id, char* cell_id, char* cellanm_id, char* multicell_id, char* multicellanm_id, char* vram_trans, char* priority);

static char* makeStrCopy(const char* tmp, int heap);
static void	delStrCopy(char* data);


//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�w�b�_�[���쐬	�i�P�́j
 *
 *@param	tbl					�w�b�_�[�f�[�^�i�[��
 *@param	charID				�L�����N�^�f�[�^ID
 *@param	plttID				�p���b�g�f�[�^ID
 *@param	cellID				�Z���f�[�^ID
 *@param	cellAnmID			�Z���A�j���[�V����ID"�����Ƃ���CLACT_U_HEADER_DATA_NONE"
 *@param	MultiID				�}���`�Z��ID		"�����Ƃ���CLACT_U_HEADER_DATA_NONE"
 *@param	MultiAnmID			�}���`�Z���A�j��ID	"�����Ƃ���CLACT_U_HEADER_DATA_NONE"
 *@param	vram_trans			Vram�]�����t���O
 *@param	priority			BG�Ƃ̗D�揇��
 *@param	charResMan			�L�����N�^�f�[�^���i�[����Ă郊�\�[�X�}�l�[�W��
 *@param	plttResMan			�p���b�g�f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellResMan			�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellAnmResMan		�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	multiCellResMan		�}���`�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	multiCellAnmResMan	�}���`�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *
 *@return	none
 *
 *
	 */
//-----------------------------------------------------------------------------
void CLACT_U_MakeHeader(CLACT_HEADER_PTR tbl, int charID, int plttID, int cellID,
		int cellAnmID, int MultiID, int MultiAnmID, int vram_trans, int priority,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan)
{
	CLACT_U_RES_OBJ_PTR char_o;
	CLACT_U_RES_OBJ_PTR pltt_o;
	CLACT_U_RES_OBJ_PTR cell_o;
	CLACT_U_RES_OBJ_PTR cellanm_o = NULL;
	CLACT_U_RES_OBJ_PTR multi_o = NULL;
	CLACT_U_RES_OBJ_PTR multianm_o = NULL;
	NNSG2dImageProxy*	img_prox;

	GF_ASSERT(charResMan);		// �K�{���\�[�X�}�l�[�W���[
	GF_ASSERT(plttResMan);
	GF_ASSERT(cellAnmResMan);
	GF_ASSERT(cellResMan);
	GF_ASSERT(tbl);				// �e�[�u���I�u�W�F�͊m�ۍς݂�
	
	// �e�f�[�^�A�N�Z�X�p�I�u�W�F�N�g�쐬
	char_o = CLACT_U_ResManagerGetIDResObjPtr( charResMan, charID );
	GF_ASSERT(char_o);
	pltt_o = CLACT_U_ResManagerGetIDResObjPtr( plttResMan, plttID );
	GF_ASSERT(pltt_o);
	cell_o = CLACT_U_ResManagerGetIDResObjPtr( cellResMan, cellID );
	GF_ASSERT(cell_o);
	
	// �A�j���f�[�^�͂���Ƃ��̂�
	if( cellAnmResMan ){
		if( cellAnmID != CLACT_U_HEADER_DATA_NONE ){
			cellanm_o = CLACT_U_ResManagerGetIDResObjPtr( cellAnmResMan, cellAnmID );
			GF_ASSERT(cellanm_o);
		}
	}

	// �}���`�Z���̓��\�[�X�}�l�[�W���[������Ƃ��̂ݐݒ�
	if(multiCellResMan != NULL){
		if(MultiID != CLACT_U_HEADER_DATA_NONE){
			multi_o = CLACT_U_ResManagerGetIDResObjPtr( multiCellResMan, MultiID );
		}
		if(MultiAnmID != CLACT_U_HEADER_DATA_NONE){
			multianm_o = CLACT_U_ResManagerGetIDResObjPtr( multiCellAnmResMan, MultiAnmID );
		}
	}
	
	// �L�����N�^�}�l�[�W���[����v���N�V���擾
	// Vram�]�����`�F�b�N
	if(vram_trans){
		img_prox = CLACT_U_CharManagerGetVramTransferProxy(char_o, cell_o);
		GF_ASSERT(img_prox);
		
		// �L�����N�^�f�[�^�擾
		tbl->pCharData = CLACT_U_ResManagerGetResObjResChar(char_o);
	}else{
		img_prox = CLACT_U_CharManagerGetProxy(char_o);
		GF_ASSERT(img_prox);

		tbl->pCharData = NULL;	// Vram�]���ȊO�ł͂���Ȃ�
	}
	// �p���b�g�v���N�V���擾
	tbl->pPaletteProxy = CLACT_U_PlttManagerGetProxy(pltt_o,img_prox);
	tbl->pImageProxy = img_prox;

	// �Z���f�[�^�o���N
	tbl->pCellBank = CLACT_U_ResManagerGetResObjResCell(cell_o);

	// �Z���A�j���f�[�^�o���N
	if(cellanm_o){
		tbl->pAnimBank = CLACT_U_ResManagerGetResObjResCellAnm(cellanm_o);	
	}else{
		tbl->pAnimBank = NULL;
	}

	// �}���`�Z���f�[�^���擾����K�v�����邩�`�F�b�N
	if(multi_o){
		// �}���`�Z���f�[�^�o���N
		tbl->pMCBank = CLACT_U_ResManagerGetResObjResMultiCell(multi_o);
		// �}���`�Z���A�j���f�[�^�o���N
		tbl->pMCABank = CLACT_U_ResManagerGetResObjResMultiCellAnim(multianm_o);
	}else{
		// �}���`�Z���f�[�^�o���N
		tbl->pMCBank = NULL;
		// �}���`�Z���A�j���f�[�^�o���N
		tbl->pMCABank = NULL;
	}

	// �]���t���O
	tbl->flag = vram_trans;

	// BG�\���D�揇��
	tbl->priority = priority;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�̃��������������O�ɁA�w�b�_�[���̃f�[�^�Ŋm�ۂ�����������j������
 *
 *@param	tbl		���g�̃f�[�^��j������w�b�_�[
 *
 *@return	none
 *
 * Vram�]���p�Ɋm�ۂ���Vram�̈��j������
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_DeleteInHeaderVramTransferArea(CLACT_HEADER_PTR tbl)
{
	// Vram�]�����[�h�̎���Vram�̈���J������
	CLACT_U_CharManagerDeleteVramTransferProxy(tbl->pImageProxy);

	// �e�[�u������clean����
	memset(tbl, 0, sizeof(CLACT_HEADER));
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�w�b�_�[�e�[�u������������ǂݍ���	�i�����j
 *
 *@param	path				�p�X
 *@param	heap				�q�[�v
 *@param	charResMan			�L�����N�^�f�[�^���i�[����Ă郊�\�[�X�}�l�[�W��
 *@param	plttResMan			�p���b�g�f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellResMan			�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellAnmResMan		�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	multiCellResMan		�}���`�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	multiCellAnmResMan	�}���`�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *
 *@return	CLACT_HEADER_TBL_PTR	�w�b�_�[�̃e�[�u�����i�[�����\���̂̃|�C���^
 *									�A�N�Z�X�֐��ŌX�̃w�b�_�[���擾���邱�Ƃ��o���܂��B
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_HEADER_TBL_PTR CLACT_U_LoadHeaderTbl(
		const char* path, int heap,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan)
{
	int i;					// ���[�v�p
	char* buff;				// ��Ɨp�o�b�t�@
	char* tmp;				// �ǂݍ��ݍς݃t�@�C��	
	int tbl_num;			// �e�[�u����
	CLACT_HEADER_TBL_PTR	ret_tbl;	// �Z���A�N�^�[�w�b�_�[�e�[�u��
	CLACT_HEADER_DATA_TMP*	data_tmp;	// �f�[�^�ꎞ�ۑ��̈�

	// �t�@�C���ǂݍ���
	tmp = sys_LoadFile(heap, path);
	GF_ASSERT(tmp);

	// �e�[�u�������擾
	buff = makeStrCopy(tmp, heap);
	tbl_num = getHeaderTblNum(buff);
	delStrCopy(buff);

	// �Z���A�N�^�[�w�b�_�[�e�[�u���쐬
	ret_tbl = sys_AllocMemory(heap, sizeof(CLACT_HEADER_TBL));
	GF_ASSERT(ret_tbl);
	
	if(tbl_num > 0){
		ret_tbl->tbl = sys_AllocMemory(heap, sizeof(CLACT_HEADER)*tbl_num);
		GF_ASSERT(ret_tbl->tbl);
	}else{
		ret_tbl->tbl = NULL;
	}
	
	ret_tbl->tbl_num = tbl_num;	// �e�[�u����

	// �ꎞ�f�[�^�ǂݍ��݂悤�e�[�u���쐬
	if(tbl_num > 0){
		data_tmp = sys_AllocMemoryLo(heap, sizeof(CLACT_HEADER_DATA_TMP)* tbl_num);
		GF_ASSERT(data_tmp);
	}else{
		data_tmp = NULL;
	}
	
	// ROM�w�b�_�[�f�[�^�ǂݍ���
	if(data_tmp != NULL){
		buff = makeStrCopy(tmp, heap);
		loadHeaderTbl(buff, data_tmp, tbl_num);
		delStrCopy(buff);
	}

	// ���ꎞ�f�[�^�ۑ��̈�ɓǂ݂��񂾃f�[�^�ŃZ���A�N�^�[�w�b�_�[���쐬����
	for(i=0;i<ret_tbl->tbl_num;i++){
		CLACT_U_MakeHeader(ret_tbl->tbl + i, 
				data_tmp[i].char_id, data_tmp[i].pltt_id,
				data_tmp[i].cell_id, data_tmp[i].cellanm_id,
				data_tmp[i].multicell_id, data_tmp[i].multicellanm_id,
				data_tmp[i].vram_trans, data_tmp[i].priority,
				charResMan, plttResMan, cellResMan, cellAnmResMan, 
				multiCellResMan, multiCellAnmResMan);
	}

	// 	�ꎞ�t�@�C���j��
	if(data_tmp){
		sys_FreeMemoryEz(data_tmp);
	}

	// �ǂݍ��݃t�@�C���j��
	sys_FreeMemoryEz(tmp);

	return ret_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�w�b�_�[�e�[�u�����o�C�i���f�[�^����쐬	�i�����j
 *
 *@param	bindata				�o�C�i���f�[�^
 *@param	p_header_tbl		�w�b�_�[�e�[�u��
 *@param	heap				�q�[�v
 *@param	charResMan			�L�����N�^�f�[�^���i�[����Ă郊�\�[�X�}�l�[�W��
 *@param	plttResMan			�p���b�g�f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellResMan			�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellAnmResMan		�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	multiCellResMan		�}���`�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	multiCellAnmResMan	�}���`�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *
 *@return	CLACT_HEADER_TBL_PTR	�w�b�_�[�̃e�[�u�����i�[�����\���̂̃|�C���^
 *									�A�N�Z�X�֐��ŌX�̃w�b�_�[���擾���邱�Ƃ��o���܂��B
 *
 * �o�C�i���f�[�^����		�e�f�[�^2byte���̔z�u�ƂȂ��Ă��܂��B
 *	�L�����N�^ID,		�i���\�[�X�}�l�[�W���[�Ɗ֘A�t�����ꂽID�j
 *	�p���b�gID,
 *	�Z��ID,
 *	�Z���A�j��ID,
 *	�}���`�Z��ID,		�i�}���`�Z���A�}���`�Z���A�j���������Ƃ���'CLACT_U_HEADER_MAKE_NONE_CODE'�j
 *	�}���`�Z���A�j��ID,
 *	Vram�]���A�j���m�F�t���O,
 *	BG�ʂƂ̗D��x
 *	���̃e�[�u����������
 *	0x0000,0x0001,0x0000,0x0002,CLACT_U_HEADER_MAKE_NONE_CODE, CLACT_U_HEADER_MAKE_NONE_CODE, 0,0			<-�P�̃f�[�^
 *	0x0001,0x0002,0x0003,0x0002,0x0000,0x0000,0x0001,0x0002
 *	�I���R�[�h
 *	CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE			���̃f�[�^���o�Ă�����I��	
 *
 */
//-----------------------------------------------------------------------------
CLACT_HEADER_TBL_PTR CLACT_U_MakeHeaderBinary(const CLACT_U_HEADER_MAKE_BINDATA* bindata,
		int heap,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan)
{
	int i;					// ���[�v�p
	int tbl_num;			// �e�[�u����
	CLACT_HEADER_TBL_PTR p_header_tbl;	// �w�b�_�[�e�[�u��
	int multicell, multicell_anm;

	// �o�C�i���f�[�^�̃e�[�u���������߂�
	tbl_num = 0;
	while( bindata[ tbl_num ].char_id != CLACT_U_HEADER_MAKE_END_CODE ){
		tbl_num ++;
	}

	// �e�[�u���쐬
	p_header_tbl			= sys_AllocMemory( heap, sizeof(CLACT_HEADER_TBL) );
	p_header_tbl->tbl		= sys_AllocMemory( heap, sizeof(CLACT_HEADER) * tbl_num );
	p_header_tbl->tbl_num	= tbl_num;
	

	for(i=0;i<p_header_tbl->tbl_num;i++){

		CLACT_U_MakeHeader(p_header_tbl->tbl + i, 
				bindata[i].char_id, bindata[i].pltt_id,
				bindata[i].cell_id, bindata[i].cellanime_id,
				bindata[i].multicell_id, bindata[i].multicellanime_id,
				bindata[i].vram_trans, bindata[i].bg_priority,
				charResMan, plttResMan, cellResMan, cellAnmResMan, 
				multiCellResMan, multiCellAnmResMan);
	}

	return p_header_tbl;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�e�[�u����j������
 *
 *@param	data	�w�b�_�[�e�[�u��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CLACT_HeaderTblDelete(CLACT_HEADER_TBL_PTR data)
{
	GF_ASSERT(data);
	
	if(data->tbl){
		sys_FreeMemoryEz(data->tbl);
	}
	sys_FreeMemoryEz(data);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�Z�b�g�̊ȒP������
 *
 *@param	work_num	�Z���A�N�^�[�ɐݒ肷��ő�A�N�^�[��
 *@param	data		�Z���A�N�^�[�ȒP�ݒ�Ɏg�p���郌���_�[�f�[�^
 *						(���Ԃ̃|�C���^)
 *@param	heap		�������m�ۂɎg�p����q�[�v��
 *
 *@return	CLACT_SET_PTR	�쐬���ꂽ�Z���A�N�^�[�Z�b�g
 *
 * ���e
 * �������_���̏������A�T�[�t�F�[�X�̐ݒ�Ȃǂ��s��
 * ���Z���A�N�^�[�Z�b�g�쐬
 * ���Z���A�N�^�[�Z�b�g�ɏ��������������_����ݒ�
 *
 * �j���͕��ʂ̃Z���A�N�^�[�̔j���֐��ő��v�ł��B
 *
 */
//-----------------------------------------------------------------------------
CLACT_SET_PTR CLACT_U_SetEasyInit( int work_num, CLACT_U_EASYRENDER_DATA* data, int heap )
{
	CLACT_SETDATA	set;
	NNSG2dViewRect rect;
	
	RNDP_InitRenderer(&data->Rend, -FX32_ONE);
	
	// �T�[�t�F�[�X�o�^
	// ���C���p�T�[�t�F�[�X
	rect.posTopLeft.x	= MAIN_SURFACE_X;
	rect.posTopLeft.y	= MAIN_SURFACE_Y;
	rect.sizeView.x		= SURFACE_WIDTH;
	rect.sizeView.y		= SURFACE_HEIGHT;
	REND_OAM_SetSurface(&data->surface[0],
			&rect,
			NNS_G2D_SURFACETYPE_MAIN2D,
			&data->Rend);
	
	// �T�u�p�T�[�t�F�[�X
	rect.posTopLeft.x	= SUB_SURFACE_X;
	rect.posTopLeft.y	= SUB_SURFACE_Y;
	rect.sizeView.x		= SURFACE_WIDTH;
	rect.sizeView.y		= SURFACE_HEIGHT;
	REND_OAM_SetSurface(&data->surface[1],
			&rect,
			NNS_G2D_SURFACETYPE_SUB2D,
			&data->Rend);
	set.WorkNum = work_num;
	set.pRender	= &data->Rend;
	set.heap	= heap;
	
	return CLACT_InitSet( &set );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����_���[��	���C����ʂ̃T�[�t�F�[�X�ʒu��ݒ�
 *
 *	@param	data	�ȒP�Z���A�N�^�[�Z�b�g�p�����_���f�[�^
 *	@param	x		���C����ʃT�[�t�F�[�X�����W
 *	@param	y		���C����ʃT�[�t�F�[�X�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_SetMainSurfaceMatrix( CLACT_U_EASYRENDER_DATA* data, fx32 x, fx32 y )
{
	NNSG2dViewRect rect;
	
	rect.posTopLeft.x	= x;
	rect.posTopLeft.y	= y;
	rect.sizeView.x		= SURFACE_WIDTH;
	rect.sizeView.y		= SURFACE_HEIGHT;
	
	RNDP_SetSurfaceRect( &data->surface[ 0 ], &rect );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����_���[��	�T�u��ʂ̃T�[�t�F�[�X�ʒu��ݒ�
 *
 *	@param	data	�ȒP�Z���A�N�^�[�Z�b�g�p�����_���f�[�^
 *	@param	x		�T�u��ʃT�[�t�F�[�X�����W
 *	@param	y		�T�u��ʃT�[�t�F�[�X�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_SetSubSurfaceMatrix( CLACT_U_EASYRENDER_DATA* data, fx32 x, fx32 y )
{
	NNSG2dViewRect rect;
	
	rect.posTopLeft.x	= x;
	rect.posTopLeft.y	= y;
	rect.sizeView.x		= SURFACE_WIDTH;
	rect.sizeView.y		= SURFACE_HEIGHT;
	
	RNDP_SetSurfaceRect( &data->surface[ 1 ], &rect );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ʐM�A�C�R���̃L�����N�^�f�[�^�g�p�̈��\��
 *
 *	@param	disp	�ݒ���	
 *	@param	mode	�I�u�W�F�}�b�s���OӰ��
 *	@return	none
 *
 *	disp
 *		main��ʁFNNS_G2D_VRAM_TYPE_2DMAIN = 1
 *		sub��� �FNNS_G2D_VRAM_TYPE_2DSUB = 2
 *
 *	mode
 *		GX_OBJVRAMMODE_CHAR_1D_32K 
 *		GX_OBJVRAMMODE_CHAR_1D_64K 
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_WmIcon_SetReserveAreaCharManager( u32 disp, GXOBJVRamModeChar mode )
{
	switch( mode ){
	case GX_OBJVRAMMODE_CHAR_1D_32K:
        if((GX_GetBankForOBJ() == GX_VRAM_OBJ_16_G) || (GX_GetBankForOBJ() == GX_VRAM_OBJ_16_F)){
            SetReserveAreaContCharManager( WM_ICON_CHAR_OFFSET16, 16*32, disp );
        }
        else{
            SetReserveAreaContCharManager( WM_ICON_CHAR_OFFSET32, 16*32, disp );
        }
		break;

	case GX_OBJVRAMMODE_CHAR_1D_64K:
		SetReserveAreaContCharManager( WM_ICON_CHAR_OFFSET64, 16*32, disp );
		break;

	case GX_OBJVRAMMODE_CHAR_1D_128K:
        if((GX_GetBankForOBJ() == GX_VRAM_OBJ_80_EF) || (GX_GetBankForOBJ() == GX_VRAM_OBJ_80_EG)){
			SetReserveAreaContCharManager( WM_ICON_CHAR_OFFSET80, 16*32, disp );
		}else{
			SetReserveAreaContCharManager( WM_ICON_CHAR_OFFSET128, 16*32, disp );
		}
		break;

	default:
		// ���̃I�u�W�F�}�b�s���OӰ�ނɂ͑Ή����Ă��܂���
		GF_ASSERT(0);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ʐM�A�C�R���̃p���b�g�f�[�^�g�p�̈��\��
 *
 *	@param	none
 *	@return	none
 */
//-----------------------------------------------------------------------------
#define CLACT_U_WMICON_PLTT_USE_MSK		(PLTTMAN_RESERVE_PLT14|PLTTMAN_RESERVE_PLT15)
void CLACT_U_WmIcon_SetReserveAreaPlttManager( u32 disp )
{
	SetReserveCleanAreaPlttManager( CLACT_U_WMICON_PLTT_USE_MSK, disp );
}




//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�e�[�u�������擾
 *
 *@param	buff	�o�b�t�@
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderTblNum(char* buff)
{
	int count;		// �e�[�u�����J�E���^
	char* data[8];
	
	count = 0;
	loadHeaderOne(buff, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7] );

	// 'e'���o�Ă�����e�[�u���I��
	while(data[0][0] != 'e'){
		count ++;
		loadHeaderOne(NULL, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7] );
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�e�[�u����ǂݍ���
 *
 *@param	buff	�f�[�^
 *@param	tbl		�i�[��
 *@param	num		�i�[��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadHeaderTbl(char* buff, CLACT_HEADER_DATA_TMP* tbl, int num)
{
	int	i;			// ���[�v�p
	char* data[8];	// �i�[�p�f�[�^
	
	// �ǂݍ���Ńe�[�u���Ɋi�[
	loadHeaderOne(buff, &data[0], &data[1], &data[2], &data[3],
			&data[4], &data[5], &data[6], &data[7] );
	
	setHeaderOne(tbl, data[0], data[1], data[2], data[3],
			data[4], data[5], data[6], data[7] );

	for(i=1;i<num;i++){
		loadHeaderOne(NULL, &data[0], &data[1], &data[2], &data[3],
				&data[4], &data[5], &data[6], &data[7] );
		setHeaderOne(tbl + i, data[0], data[1], data[2], data[3],
				data[4], data[5], data[6], data[7] );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�P�̃f�[�^���擾
 *
 *@param	buff			�o�b�t�@
 *@param	char_id			�L�����N�^ID�i�[��
 *@param	pltt_id			�p���b�gID�i�[��
 *@param	cell_id			�Z��ID�i�[��
 *@param	cellanm_id		�Z���A�j��ID�i�[��
 *@param	multicell_id	�}���`�Z��ID�i�[��
 *@param	multicellanm_id	�}���`�Z���A�j��ID�i�[��
 *@param	vram_trans		Vram�]���m�F�t���O�i�[��
 *@param	priority		BG�ʂƂ̕\���D�揇�ʊi�[��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadHeaderOne(char* buff, char** char_id, char** pltt_id, char** cell_id, char** cellanm_id, char** multicell_id, char** multicellanm_id, char** vram_trans, char** priority)
{
	*char_id	= strtok(buff, ",");
	*pltt_id	= strtok(NULL, ",");
	*cell_id	= strtok(NULL, ",");
	*cellanm_id	= strtok(NULL, ",");
	*multicell_id	= strtok(NULL, ",");
	*multicellanm_id= strtok(NULL, ",");
	*vram_trans	= strtok(NULL, ",");
	*priority	= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�[�u���Ƀf�[�^��ݒ肷��
 *
 *@param	tbl					�f�[�^�i�[��
 *@param	char_id				�L�����N�^ID
 *@param	pltt_id				�p���b�gID
 *@param	cell_id				�Z��ID
 *@param	cellanm_id			�Z���A�j��ID
 *@param	multicell_id		�}���`�Z��ID
 *@param	multicellanm_id		�}���`�Z���A�j��ID
 *@param	vram_trans			Vram�]���m�F�t���O
 *@param	priority			BG�ʂƂ̕\���D�揇��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setHeaderOne(CLACT_HEADER_DATA_TMP* tbl, char* char_id, char* pltt_id, char* cell_id, char* cellanm_id, char* multicell_id, char* multicellanm_id, char* vram_trans, char* priority)
{
	tbl->char_id		= atoi(char_id);
	tbl->pltt_id		= atoi(pltt_id);
	tbl->cell_id		= atoi(cell_id);
	tbl->cellanm_id		= atoi(cellanm_id);
	if(multicell_id[0] != 'n'){
		tbl->multicell_id	= atoi(multicell_id);
		tbl->multicellanm_id = atoi(multicellanm_id);
	}else{
		tbl->multicell_id	 = CLACT_U_HEADER_DATA_NONE; 
		tbl->multicellanm_id = CLACT_U_HEADER_DATA_NONE;
	}
	tbl->vram_trans		= atoi(vram_trans);
	tbl->priority		= atoi(priority);
	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�R�s�[���쐬
 *
 *@param	tmp		�R�s�[�f�[�^
 *@param	heap	�g�p�q�[�v
 *
 *@return	char* �쐬�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static char* makeStrCopy(const char* tmp, int heap)
{
	int len;
	char* copy;
	
	len = strlen(tmp);
	len++;

	copy = sys_AllocMemoryLo(heap, len);
	strcpy(copy, tmp);

	return copy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	makeStrCopy�ō쐬�����f�[�^�j��
 *
 *@param	data	�j���f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void	delStrCopy(char* data)
{
	sys_FreeMemoryEz(data);
}


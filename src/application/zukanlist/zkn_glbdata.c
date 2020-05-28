//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_glbdata.c
 *	@brief		�}�ӃO���[�o���f�[�^
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/system/arc_util.h"
#include "src/application/zukanlist/zkn_data/zukan_data.naix"

#include "include/application/zukanlist/zkn_glbdata.h"
#include "include/poketool/poke_tool.h"



//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define ZKN_SORTDATA_START_IDX	( NARC_zukan_data_zkn_sort_zenkoku_dat )
#define ZKN_SORTDATA_ONESIZE	( sizeof(u16) )
enum{
	// ��{
	ZKN_SORTDATA_ZENKOKU,
	ZKN_SORTDATA_SHINOH,
	
	// �\�[�g�ް�
	ZKN_SORTDATA_AIUEO,
	ZKN_SORTDATA_HEAVY,
	ZKN_SORTDATA_LIGHT,
	ZKN_SORTDATA_TALL,
	ZKN_SORTDATA_SMALL,
	
	// ���O����
	ZKN_SORTDATA_NAME_A,
	ZKN_SORTDATA_NAME_KA,
	ZKN_SORTDATA_NAME_SA,
	ZKN_SORTDATA_NAME_TA,
	ZKN_SORTDATA_NAME_NA,
	ZKN_SORTDATA_NAME_HA,
	ZKN_SORTDATA_NAME_MA,
	ZKN_SORTDATA_NAME_RA,
	ZKN_SORTDATA_NAME_YAWA,

	// �^�C�v����
	ZKN_SORTDATA_TYPE_NORMAL,
	ZKN_SORTDATA_TYPE_BATTLE,	
	ZKN_SORTDATA_TYPE_HIKOU,	
	ZKN_SORTDATA_TYPE_POISON,	
	ZKN_SORTDATA_TYPE_JIMEN,	
	ZKN_SORTDATA_TYPE_IWA,		
	ZKN_SORTDATA_TYPE_MUSHI,	
	ZKN_SORTDATA_TYPE_GHOST,	
	ZKN_SORTDATA_TYPE_METAL,	
	ZKN_SORTDATA_TYPE_FIRE,	
	ZKN_SORTDATA_TYPE_WATER,	
	ZKN_SORTDATA_TYPE_KUSA,	
	ZKN_SORTDATA_TYPE_ELECTRIC,
	ZKN_SORTDATA_TYPE_SP,		
	ZKN_SORTDATA_TYPE_KOORI,	
	ZKN_SORTDATA_TYPE_DRAGON,	
	ZKN_SORTDATA_TYPE_AKU,	

	// �`����
	ZKN_SORTDATA_FORM_FOUR_LEGS,
	ZKN_SORTDATA_FORM_TWO_LEGS,
	ZKN_SORTDATA_FORM_TAIL,
	ZKN_SORTDATA_FORM_HARABAI,
	ZKN_SORTDATA_FORM_FOUR_WING,
	ZKN_SORTDATA_FORM_TWO_WING,
	ZKN_SORTDATA_FORM_HAITSUKUBARI,
	ZKN_SORTDATA_FORM_STRAIGHT,
	ZKN_SORTDATA_FORM_ARM,
	ZKN_SORTDATA_FORM_LEGS,
	ZKN_SORTDATA_FORM_MANY_LEGS,
	ZKN_SORTDATA_FORM_WATER,
	ZKN_SORTDATA_FORM_CIRCLE,
	ZKN_SORTDATA_FORM_COMP,
	ZKN_SORTDATA_NUM
};







//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void ZknPokeListTblMakeSortData( u16* p_buff, int* p_count, const ZUKAN_WORK* cp_zukansave_data, const u16* cp_tbl, int num );
static void ZknPokeListTblMakeSarch( u16* p_buff, int* p_count, const u16* cp_tbl, int num, const u16* cp_sarch_tbl, int sarch_num, BOOL see_ok_flg, const ZUKAN_WORK* cp_zukansave_data );
static void ZknPokeListTblMake( ZKN_POKELIST_TBL* p_poke_list, const ZUKAN_WORK* cp_zukansave_data, const u16* cp_tbl, int tbl_num );
static void ZknPokeListDrawTblMake( ZKN_POKELIST_TBL* p_poke_list, const u16* cp_all_tbl, int all_tbl_num );
static void ZknPokeListDrawTblCopy( ZKN_POKELIST_TBL* p_poke_list );
static void ZknPokeListTblSeeGetNumCount( ZKN_POKELIST_TBL* p_poke_list, int* p_see_num, int* p_get_num );

static u16* ZKN_SORTDATA_Get( int heap, int idx, int* p_arry_num );

static void ZknPokeListSort_Core( int sort_type, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data );
static void ZknPokeListSarchName_Core( int search_name, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data );
static void ZknPokeListSarchType_Core( int search_type, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data );
static void ZknPokeListSarchForm_Core( int search_form, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data );

//-----------------------------------------------------------------------------
/**
 *	�O���[�o���ϐ�
 *
 */
//-----------------------------------------------------------------------------
#define ZENKOKU_POKEON_TBL_NUM	(MONSNO_END)
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�O���[�o���f�[�^������
 *
 *	@param	p_glb				�O���[�o���f�[�^
 *	@param	p_init				�������f�[�^
 *	@param	heap				�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_Init( ZKN_GLB_DATA* p_glb, ZKN_GLB_DATA_INIT* p_init, int heap )
{
	int sort_type;
	int search_name;
	int search_type1;
	int search_type2;
	int search_form;
	BOOL check;
	u32 zkn_mode;
	
	memset( p_glb, 0, sizeof(ZKN_GLB_DATA) );

	// �}�ӃZ�[�u�f�[�^�ݒ�
	p_glb->cp_zukansave_data = p_init->cp_zukansave_data;

	// ���ԑ�
	p_glb->time_zone = p_init->time_zone;

	// �[���R�N�}�ӕێ��t���O�ݒ�
	if( ZukanWork_GetZenkokuZukanFlag( p_glb->cp_zukansave_data ) ){
		p_glb->zkn_allmap_get = TRUE;
	}else{
		p_glb->zkn_allmap_get = FALSE;
	}


	// �S���}�ӂ�����Ȃ�S���}�Ӄ��[�h�ŊJ�n
	if( p_init->zkn_mode == ZKN_MODE_NAZO ){
		// �[���R�N
		if( p_glb->zkn_allmap_get ){
			zkn_mode = ZKN_MODE_ZENKOKU;
		}else{
			zkn_mode = ZKN_MODE_SHINOH;
		}
	}else{
		zkn_mode = p_init->zkn_mode;
	}

	if( zkn_mode == ZKN_MODE_ZENKOKU ){
		p_glb->zkn_mode = ZKN_MODE_ZENKOKU;

		// �|�P�������X�g�f�[�^�쐬
		sort_type	= ZKN_POKELIST_SORT_NORMAL;
		search_name = ZKN_POKELIST_SEARCH_NAME_NONE;
		search_type1= ZKN_POKELIST_SEARCH_TYPE_NONE;
		search_type2= ZKN_POKELIST_SEARCH_TYPE_NONE;
		search_form = ZKN_POKELIST_SEARCH_FORM_NONE;
	}else{
		// �V���I�E���[�h�ŊJ�n
		p_glb->zkn_mode = ZKN_MODE_SHINOH;

		// �|�P�������X�g�f�[�^�쐬
		sort_type	= ZKN_POKELIST_SORT_NORMAL;
		search_name = ZKN_POKELIST_SEARCH_NAME_NONE;
		search_type1= ZKN_POKELIST_SEARCH_TYPE_NONE;
		search_type2= ZKN_POKELIST_SEARCH_TYPE_NONE;
		search_form = ZKN_POKELIST_SEARCH_FORM_NONE;
	}
	// �|�P�������X�g�쐬
	check = ZKN_GLBDATA_PokeListTblMake( p_glb, sort_type, 
			search_name, search_type1, search_type2, search_form,
			p_glb->zkn_mode, heap );
	// ���X�g�쐬���ʂ�0��
	GF_ASSERT( check );

	// �����X�^�[�i���o�[�Ń��X�g�Q�Ɛ��ݒ�
	ZKN_GLBDATA_PokeListTblNoSet_Monsno( p_glb, p_init->init_list_monsno );
	ZKN_GLBDATA_PokeTextSeeSetMonsno( p_glb, p_init->init_list_monsno );
	ZKN_GLBDATA_PokeTextSeeSetZknMode( p_glb, p_init->zkn_mode );
/*
	// ���������擾
	p_glb->see_num = ZukanWork_GetPokeSeeCount( p_glb->cp_zukansave_data );
	
	// �ߊl���擾
	p_glb->get_num = ZukanWork_GetPokeGetCount( p_glb->cp_zukansave_data );
//*/

	// �����R�[�h
	p_glb->rom_code = MyStatus_GetRomCode( p_init->cp_hero_data );

	// ��l������
	p_glb->hero_sex = MyStatus_GetMySex( p_init->cp_hero_data );	

	// ��l�����O
	p_glb->hero_name = MyStatus_CreateNameString( p_init->cp_hero_data, heap );

	// �����d���f�[�^�擾
	p_glb->height_gram = ZKN_HEIGHTGRAM_Alloc( heap );
	// �j�������`�F�b�N
	if( p_glb->hero_sex == 0 ){
		ZKN_HEIGHTGRAM_Load( p_glb->height_gram, ZKN_HEIGHT_GRAM_TYPE_MAN, heap );
	}else{
		ZKN_HEIGHTGRAM_Load( p_glb->height_gram, ZKN_HEIGHT_GRAM_TYPE_GIRL, heap );
	}

	// �B���}�b�v
	p_glb->hidemap_id_D15 = p_init->hidemap_id_D15;
	p_glb->hidemap_id_D30 = p_init->hidemap_id_D30;
	p_glb->hidemap_id_L04 = p_init->hidemap_id_L04;
	p_glb->hidemap_id_D18 = p_init->hidemap_id_D18;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�O���[�o���f�[�^�j��
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_Delete( ZKN_GLB_DATA* p_glb )
{

	// ��l����
	STRBUF_Delete( p_glb->hero_name );
	
	// �����f�[�^
	ZKN_HEIGHTGRAM_Release( p_glb->height_gram );
	ZKN_HEIGHTGRAM_Free( p_glb->height_gram );
	p_glb->height_gram = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����i���o�[�̃|�P������\�����鐫�ʂ��擾
 *
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	monsno		�����X�^�[�i���o�[
 *	@param	count		ZUKAN_WORK_SEX_FIRST�@ZUKAN_WORK_SEX_SECOND
 *
 *	@retval	PARA_MALE		�I�X
 *	@retval	PARA_FEMALE		���X
 *	@retval	PARA_UNK		�s��
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SexGet( const ZKN_GLB_DATA* cp_glb, int monsno, int count )
{
	u32 sex;
	sex = ZukanWork_GetPokeSexFlag( cp_glb->cp_zukansave_data, monsno, count );
	return sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A���m�[���t�H�[���̎擾
 *
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	count		(0�`27)
 *
 *	@return	�t�H�����i���o�[
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_AnoonFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	int form;
	GF_ASSERT( count < 28 );

	form = ZukanWork_GetPokeAnoonForm( cp_glb->cp_zukansave_data, count );

	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�[�E�V�@�t�H�����擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	count	����	0or1
 *
 *	@return	�t�H����
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SiiusiFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	u32 form;
	GF_ASSERT( count < 2 );
	
	form = ZukanWork_GetPokeSiiusiForm( cp_glb->cp_zukansave_data, count );
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�[�h���S
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	count	����	0or1
 *
 *	@return	�t�H����
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SiidorugoFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	u32 form;
	GF_ASSERT( count < 2 );
	
	form = ZukanWork_GetPokeSiidorugoForm( cp_glb->cp_zukansave_data, count );
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�m���b�`
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	count	����	0or1or2
 *
 *	@return	�t�H����
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_MinomuttiFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	u32 form;
	GF_ASSERT( count < 3 );
	
	form = ZukanWork_GetPokeMinomuttiForm( cp_glb->cp_zukansave_data, count );
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�m���X
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	count	����	0or1or2
 *
 *	@return	�t�H����
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_MinomesuFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	u32 form;
	GF_ASSERT( count < 3 );
	
	form = ZukanWork_GetPokeMinomesuForm( cp_glb->cp_zukansave_data, count );
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ŏ��Ɍ����`���Ԃ�
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	monsno	�����X�^�[�i���o�[
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_FirstFormGet( const ZKN_GLB_DATA* cp_glb, u32 monsno )
{
	u32 form;
	
	switch( monsno ){
	case MONSNO_ANNOON:
		form = ZKN_GLBDATA_SaveData_AnoonFormGet( cp_glb, 0 );
		break;

	case MONSNO_SIIUSI:
		form = ZKN_GLBDATA_SaveData_SiiusiFormGet( cp_glb, 0 );
		break;
		
	case MONSNO_SIIDORUGO:
		form = ZKN_GLBDATA_SaveData_SiidorugoFormGet( cp_glb, 0 );
		break;
		
	case MONSNO_MINOMUTTI:
		form = ZKN_GLBDATA_SaveData_MinomuttiFormGet( cp_glb, 0 );
		break;
		
	case MONSNO_MINOMESU:
		form = ZKN_GLBDATA_SaveData_MinomesuFormGet( cp_glb, 0 );
		break;

	case MONSNO_DEOKISISU:
		form = ZKN_GLBDATA_SaveData_DeokisisuFormGet( cp_glb, 0 );
		break;
		
	default:
		form = 0;	
		break;
	}

	return form;
}


//----------------------------------------------------------------------------
/**	
 *	@brief	�������ʂ̐����擾
 *
 *	@param	cp_glb	�`��O���[�o��
 *	@param	monsno	�����X�^�[�i���o�[
 *
 *	@return	�������ʂ̐�
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SexNumGet( const ZKN_GLB_DATA* cp_glb, int monsno )
{
	int sex = ZKN_GLBDATA_SaveData_SexGet( cp_glb, monsno, ZUKAN_WORK_SEX_SECOND );
	
	
	// 2�ڂ̐��ʂ��݂����`�F�b�N
	if( sex == ZUKAN_WORK_GET_SEX_ERR ){
		return 1;
	}

	return 2;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A���m�[���̎�ނ����������擾
 *
 *	@param	cp_glb	�O���[�o��
 *
 *	@return	��������
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_AnoonNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeAnoonSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�[�E�V�@��ގ擾
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SiiusiNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeSiiusiSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�[�h���S�@��ގ擾
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SiidorugoNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeSiidorugoSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�m���b�`�@��ގ擾
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_MinomuttiNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeMinomuttiSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�m���X�@��ގ擾
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_MinomesuNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeMinomesuSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p�b�`�[���ő̗����擾
 *
 *	@param	cp_glb	�O���[�o�����[�N
 *
 *	@return	�ő̗���
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_PattiruRndGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeRandomFlag( cp_glb->cp_zukansave_data, ZUKAN_WORK_RANDOM_PACHI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�t�H�����擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	�t�H�����i���o�[
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_DeokisisuFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	return ZukanWork_GetPokeDeokisisuForm( cp_glb->cp_zukansave_data, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�`�󌩂����擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	�f�I�L�V�X�`�󌩂���
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_DeokisisuFormSeeNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeDeokisisuFormSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�[���R�N�}�ӊ������Ă��邩�`�F�b�N
 * 
 *	@param	cp_glb	���[�N
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	������
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_SaveData_ZenkokuZukanComp( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_CheckZenkokuComp( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�[���R�N�}�ӎ擾���Ă��邩�`�F�b�N
 * 
 *	@param	cp_glb	���[�N
 *
 *	@retval	TRUE	�擾
 *	@retval	FALSE	���擾
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_SaveData_ZenkokuZukanGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetZenkokuZukanFlag( cp_glb->cp_zukansave_data );
}



//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����e�L�X�g�����t���O
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *	@param	monsno		�����X�^�[�i���o�[
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_PokeTextSeeSetMonsno( ZKN_GLB_DATA* p_glb, u32 monsno )
{
	p_glb->last_see_monsno = monsno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Ō�Ɍ����|�P�����i���o�[�擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_PokeTextSeeGetMonsno( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->last_see_monsno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����e�L�X�g�����t���O
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *	@param	zkn_mode	�}��Ӱ��
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_PokeTextSeeSetZknMode( ZKN_GLB_DATA* p_glb, u32 zkn_mode )
{
	p_glb->last_see_zkn_mode = zkn_mode;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Ō�Ɍ����|�P�����i���o�[�擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_PokeTextSeeGetZknMode( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->last_see_zkn_mode;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�o�[�W�����t���O�擾
 *
 *	@param	cp_glb	�O���[�o��
 *
 *	@retval	TRUE	�o�[�W�����A�b�v����
 *	@retval	FALSE	�o�[�W�����A�b�v������
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_SaveData_GraModeGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetGraphicVersionUpFlag( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	����o�[�W�����t���O�擾
 *
 *	@param	cp_glb		�O���[�o��
 *	@param	country		���R�[�h 
 *
 *	@retval	TRUE	�o�[�W�����A�b�v����
 *	@retval	FALSE	�o�[�W�����A�b�v������
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_SaveData_TextModeGet( const ZKN_GLB_DATA* cp_glb, int country )
{
//	return ZukanWork_GetTextVersionUpFlag( cp_glb->cp_zukansave_data, country );
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�e�[�u���̍쐬
 *
 *	@param	p_glb			�O���[�o���f�[�^
 *	@param	sort_type		�\�[�g�^�C�v
 *	@param	search_name		���O�T�[�`
 *	@param	search_type1	�^�C�v�T�[�`
 *	@param	search_type2	�^�C�v�T�[�`
 *	@param	search_form		�t�H�[���T�[�`
 *	@param	shinoh			�V���I�E�}�ӂȂ�TRUE
 *	@param	heap			�g�p�q�[�v
 *	@param	dummy_list_cut	�_�~�[���X�g�J�b�g�t���O
 *	
 *	@retval	TRUE	�쐬����
 *	@retval	FALSE	�쐬���ʃ��X�g���O��
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblMake_DummyListCutFlg( ZKN_GLB_DATA* p_glb, int sort_type, int search_name, int search_type1, int search_type2, int search_form, int shinoh, int heap, BOOL dummy_list_cut )
{
	u16* p_buff0;	// �������ް��p�e�[�u���o�b�t�@
	int count0;
	u16* p_buff1;	// �������ʎ󂯎��p�e�[�u���o�b�t�@
	int count1;
	u16* p_all_list_data;	// ��đO�S�߹��ؽ��ް�
	int all_list_data_count;
	BOOL ret;

	// �o�b�t�@�̈���m��
	p_buff0 = sys_AllocMemoryLo( heap, sizeof(u16) * POKEMON_LIST_TBL_NUM );
	GF_ASSERT( p_buff0 );
	memset( p_buff0, 0, sizeof(u16) * POKEMON_LIST_TBL_NUM );
	count0 = 0;
	p_buff1 = sys_AllocMemoryLo( heap, sizeof(u16) * POKEMON_LIST_TBL_NUM );
	GF_ASSERT( p_buff1 );
	memset( p_buff1, 0, sizeof(u16) * POKEMON_LIST_TBL_NUM );
	count1 = 0;

	// �|�P�����f�[�^���V���I�E�e�[�u�����玝���Ă���̂�
	// �S���}�ӂ�������Ă���̂�
	if( shinoh == ZKN_MODE_SHINOH ){
		// �V���I�E
		p_all_list_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_SHINOH, &all_list_data_count );
		ZknPokeListTblMakeSortData( p_buff0, &count0, p_glb->cp_zukansave_data, p_all_list_data, all_list_data_count );
	}else{
		// �S��
		p_all_list_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_ZENKOKU, &all_list_data_count );
		ZknPokeListTblMakeSortData( p_buff0, &count0, p_glb->cp_zukansave_data, p_all_list_data, all_list_data_count );
	}
	
	// ���
	ZknPokeListSort_Core( sort_type, p_buff1, &count1, p_buff0, count0, heap, p_glb->cp_zukansave_data );
	memcpy( p_buff0, p_buff1, sizeof(u16) * count1 );	// �f�[�^�R�s�[
	count0 = count1;
	memset( p_buff1, 0, sizeof(u16) * count1 );
	count1 = 0;
	
	// ��������
	do{
		// �Ȃ܂����񂳂�
		ZknPokeListSarchName_Core( search_name, p_buff1, &count1, p_buff0, count0, heap, p_glb->cp_zukansave_data );
		if( count1 == 0 ){
			ret = FALSE;
			break;
		}
		memcpy( p_buff0, p_buff1, sizeof(u16) * count1 );	// �f�[�^�R�s�[
		count0 = count1;
		memset( p_buff1, 0, sizeof(u16) * count1 );
		count1 = 0;

		// �^�C�v
		ZknPokeListSarchType_Core( search_type1, p_buff1, &count1, p_buff0, count0, heap, p_glb->cp_zukansave_data );
		if( count1 == 0 ){
			ret = FALSE;
			break;
		}
		memcpy( p_buff0, p_buff1, sizeof(u16) * count1 );	// �f�[�^�R�s�[
		count0 = count1;
		memset( p_buff1, 0, sizeof(u16) * count1 );
		count1 = 0;

		// ����2
		ZknPokeListSarchType_Core( search_type2, p_buff1, &count1, p_buff0, count0, heap, p_glb->cp_zukansave_data );
		if( count1 == 0 ){
			ret = FALSE;
			break;
		}
		memcpy( p_buff0, p_buff1, sizeof(u16) * count1 );	// �f�[�^�R�s�[
		count0 = count1;
		memset( p_buff1, 0, sizeof(u16) * count1 );
		count1 = 0;

		// ������
		ZknPokeListSarchForm_Core( search_form, p_buff1, &count1, p_buff0, count0, heap, p_glb->cp_zukansave_data );
		if( count1 == 0 ){
			ret = FALSE;
			break;
		}
		memcpy( p_buff0, p_buff1, sizeof(u16) * count1 );	// �f�[�^�R�s�[
		count0 = count1;
		memset( p_buff1, 0, sizeof(u16) * count1 );
		count1 = 0;


		// �ް����������烊�X�g�쐬
		// �|�P�������X�g�f�[�^�쐬
		ZknPokeListTblMake( &p_glb->poke_list, p_glb->cp_zukansave_data, p_buff0, count0 );

		// �����\�[�g�����������Ƃ��̓R�s�[����̂�
		// �����X�^�[�i���o�[�Ń��X�g�쐬�����Ƃ��̓����X�^�[�i���o�[�ŕ`�惊�X�g���쐬����
		if( ((sort_type != ZKN_POKELIST_SORT_NORMAL) ||
			(search_name != ZKN_POKELIST_SEARCH_NAME_NONE) ||
			(search_type1 != ZKN_POKELIST_SEARCH_TYPE_NONE) ||
			(search_type2 != ZKN_POKELIST_SEARCH_TYPE_NONE) ||
			(search_form != ZKN_POKELIST_SEARCH_FORM_NONE)) ){
			dummy_list_cut = TRUE;
		}

		if( dummy_list_cut == FALSE ){
			ZknPokeListDrawTblMake( &p_glb->poke_list, p_all_list_data, all_list_data_count );
		}else{
			ZknPokeListDrawTblCopy( &p_glb->poke_list );
		}
		ret = TRUE;
	}while(0);
	

	// �݂��������@�߂܂������v�Z
	ZknPokeListTblSeeGetNumCount( &p_glb->poke_list, &p_glb->see_num, &p_glb->get_num );
	

	// �o�b�t�@�j��
	sys_FreeMemoryEz( p_buff0 );
	sys_FreeMemoryEz( p_buff1 );
	sys_FreeMemoryEz( p_all_list_data );

	return ret;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�e�[�u���̍쐬
 *
 *	@param	p_glb			�O���[�o���f�[�^
 *	@param	sort_type		�\�[�g�^�C�v
 *	@param	search_name		���O�T�[�`
 *	@param	search_type1	�^�C�v�T�[�`
 *	@param	search_type2	�^�C�v�T�[�`
 *	@param	search_form		�t�H�[���T�[�`
 *	@param	shinoh			�V���I�E�}�ӂȂ�TRUE
 *	@param	heap			�g�p�q�[�v
 *	@param	dummy_list_cut	�_�~�[���X�g�J�b�g�t���O
 *	
 *	@retval	TRUE	�쐬����
 *	@retval	FALSE	�쐬���ʃ��X�g���O��
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblMake( ZKN_GLB_DATA* p_glb, int sort_type, int search_name, int search_type1, int search_type2, int search_form, int shinoh, int heap )
{
	return ZKN_GLBDATA_PokeListTblMake_DummyListCutFlg( p_glb, sort_type, search_name, search_type1, search_type2, search_form, shinoh, heap, FALSE );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�S���}�Ӄ��[�h�ɕύX�ł��邩�`�F�b�N
 *
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	zkn_mode	�ύX����}�Ӄ��[�h
 *
 *	@retval	TRUE	�o����
 *	@retval FALSE	�o���Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeZknModeChengeCheck( const ZKN_GLB_DATA* cp_glb, int zkn_mode )
{
	// �V���I�E�}�ӂ͖�����
	if( zkn_mode == ZKN_MODE_SHINOH ){
		return TRUE;
	}

	// �S���͑S���}�ӂ������Ă�����OK
	if( cp_glb->zkn_allmap_get ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄ��[�h�ύX
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *	@param	zkn_mode	�}�Ӄ��[�h
 *
 *	@retval	TRUE		�ύX�ł���
 *	@retval	FALSE		�ύX�ł��Ȃ�����
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeZknModeChenge( ZKN_GLB_DATA* p_glb, int zkn_mode )
{
	BOOL check;

	check = ZKN_GLBDATA_PokeZknModeChengeCheck( p_glb, zkn_mode );

	if( check ){
		p_glb->zkn_mode = zkn_mode;
	}


	return check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄ��[�h���擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	�}�Ӄ��[�h
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeZknModeGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->zkn_mode;
}

//----------------------------------------------------------------------------
/**	
 *	@brief	�|�P�������X�g�e�[�u���i���o�[�ݒ�\����
 *
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	no			�`�F�b�N�i���o�[
 *
 *	@retval	TRUE	�ݒ�\
 *	@retval	FALSE	�ݒ�s�\
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblNoSetCheck( const ZKN_GLB_DATA* cp_glb, int no )
{
	// �ݒ�\���`�F�b�N
	if( ((no) >= 0) &&
		((no) < cp_glb->poke_list.tbl_poke_num) ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�e�[�u���i���o�[�ݒ�
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *	@param	no			�ݒ�i���o�[
 *
 *	@retval	TRUE	�ݒ萬��
 *	@retval	FALSE	�ݒ莸�s	�i�l���s���j
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblNoSet( ZKN_GLB_DATA* p_glb, int no )
{
	// �ݒ�\���`�F�b�N
	if( ZKN_GLBDATA_PokeListTblNoSetCheck( p_glb, no ) ){
		p_glb->poke_list.tbl_no = no;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����Z
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	no		�����l
 *
 *	@retval	TRUE	�ݒ萬��
 *	@retval	FALSE	�ݒ莸�s		0���ő吔�ɂȂ��Ă��܂�
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblNoAdd( ZKN_GLB_DATA* p_glb, int no )
{
	if( ZKN_GLBDATA_PokeListTblNoSetCheck( p_glb, p_glb->poke_list.tbl_no + no ) ){
		p_glb->poke_list.tbl_no += no;
		return TRUE;
	}

	if( no >= 0 ){
		p_glb->poke_list.tbl_no = p_glb->poke_list.tbl_poke_num - 1;
	}else{
		p_glb->poke_list.tbl_no = 0;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e�[�u���i���o�[�擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	���݂̃e�[�u���i���o�[
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListTblNoGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.tbl_no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�e�[�u�����擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	�e�[�u����
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListTblNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.tbl_poke_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����X�^�[�i���o�[���烊�X�g�e�[�u���i���o�[���擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	monsno	�����X�^�[�i���o�[
 *
 *	@return	�e�[�u���i���o�[  �e�[�u���ő吔�̂Ƃ��́A���������Ƃ�
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListTblNoGet_Monsno( const ZKN_GLB_DATA* cp_glb, u32 monsno )
{
	int i;
	int tbl_num = ZKN_GLBDATA_PokeListTblNumGet( cp_glb );
	int tbl_mons;

	for( i=0; i<tbl_num; i++ ){
		tbl_mons = cp_glb->poke_list.zkn_pokelist_tbl[ i ].mons_no;
		if( tbl_mons == monsno ){
			break;
		}
	}
	return i;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����X�^�[�i���o�[�ɑΉ��������X�g��ݒ肷��
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	monsno	�ݽ�����ް
 *
 *	@retval	TRUE		�ݒ萬��
 *	@retval	FALSE		�ݒ莸�s
 */	
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblNoSet_Monsno( ZKN_GLB_DATA* p_glb, int monsno )
{
	u32 tbl_num = ZKN_GLBDATA_PokeListTblNumGet( p_glb );
	u32 tbl_no	= ZKN_GLBDATA_PokeListTblNoGet_Monsno( p_glb, monsno );

	if( tbl_num > tbl_no ){
		return ZKN_GLBDATA_PokeListTblNoSet( p_glb, tbl_no );
	}
	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����i���o�[�擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	�|�P�����i���o�[
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeMonsNoGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.zkn_pokelist_tbl[ cp_glb->poke_list.tbl_no ].mons_no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����@�ߊl�@�����^�C�v�擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@retval	ZKN_POKELIST_TYPE_NONE,	// �킩��Ȃ�
 *	@retval ZKN_POKELIST_TYPE_SEE,	// ������
 *	@retval	ZKN_POKELIST_TYPE_GET,	// �߂܂���
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeMonsTypeGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.zkn_pokelist_tbl[ cp_glb->poke_list.tbl_no ].type;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�e�[�u���擾
 *
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	tbl_no		�e�[�[�u���i���o�[
 *
 *	@return	�e�[�u���|�C���^
 */
//-----------------------------------------------------------------------------
const ZKN_POKELIST_DATA* ZKN_GLBDATA_PokeListTblGet( const ZKN_GLB_DATA* cp_glb, int tbl_no )
{
	//�擾�\������ 
	if( ZKN_GLBDATA_PokeListTblNoSetCheck( cp_glb, tbl_no ) ){
		return &cp_glb->poke_list.zkn_pokelist_tbl[ tbl_no ];
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��|�P�������X�g�̃e�[�u���i���o�[�ݒ�`�F�b�N
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	no		�ݒ�i���o�[
 *
 *	@retval	TRUE ����
 *	@retval	FALSE ���s
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListDrawTblNoSetCheck( const ZKN_GLB_DATA* cp_glb, int no )
{
	if( (cp_glb->poke_list.draw_tbl_poke_num > no) && (no >= 0) ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��|�P�������X�g�i���o�[�ݒ�
 *
 *	@param	p_glb	�O���[�o��
 *	@param	no		�|�P�������X�g�e�[�u���i���o�[
 *	
 *	@retval	TRUE ����
 *	@retval	FALSE ���s
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListDrawTblNoSet( ZKN_GLB_DATA* p_glb, int no )
{
	if( ZKN_GLBDATA_PokeListDrawTblNoSetCheck( p_glb, no ) ){
		p_glb->poke_list.draw_tbl_no = no;

		// �|�P�������X�g�ɂ����f
		ZKN_GLBDATA_PokeListTblNoSet( p_glb, p_glb->poke_list.zkn_pokelistdraw_tbl[ p_glb->poke_list.draw_tbl_no ] );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��|�P�������X�g�i���o�[�����Z
 *
 *	@param	p_glb
 *	@param	no 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListDrawTblNoAdd( ZKN_GLB_DATA* p_glb, int no )
{
	if( ZKN_GLBDATA_PokeListDrawTblNoAddCheck( p_glb, no ) ){
		p_glb->poke_list.draw_tbl_no += no;

		// �|�P�������X�g�ɂ����f
		ZKN_GLBDATA_PokeListTblNoSet( p_glb, p_glb->poke_list.zkn_pokelistdraw_tbl[ p_glb->poke_list.draw_tbl_no ] );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����Z�ł��邩�`�F�b�N
 *
 *	@param	p_glb
 *	@param	no 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListDrawTblNoAddCheck( ZKN_GLB_DATA* p_glb, int no )
{
	if( ZKN_GLBDATA_PokeListDrawTblNoSetCheck( p_glb, p_glb->poke_list.draw_tbl_no + no ) ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��e�[�u���i���o�[�擾
 *
 *	@param	cp_glb	���ݕ`��O���[�o���i���o�[�ݒ�
 *
 *	@return	
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListDrawTblNoGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.draw_tbl_no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��e�[�u�����擾
 *
 *	@param	cp_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListDrawTblNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.draw_tbl_poke_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\���f�[�^�e�[�u���i���o�[�擾
 *
 *	@param	cp_glb
 *	@param	no 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListDrawTblDataGet( const ZKN_GLB_DATA* cp_glb, int no )
{
	return cp_glb->poke_list.zkn_pokelistdraw_tbl[ no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̃|�P���X�g�I���ʒu�ɕ`�惊�X�g�ʒu�����킹��
 *
 *	@param	cp_glb	�O���[�o��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_PokeListDrawTblSetNowTblNo( ZKN_GLB_DATA* p_glb )
{
	int i;

	for( i=0; i<p_glb->poke_list.draw_tbl_poke_num; i++ ){

		if( ZKN_GLBDATA_PokeListDrawTblDataGet( p_glb, i ) == ZKN_GLBDATA_PokeListTblNoGet( p_glb ) ){
			
			ZKN_GLBDATA_PokeListDrawTblNoSet( p_glb, i );
			break;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����������擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	������
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeSeeNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->see_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����ߊl���擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^�v
 *
 *	@return	�ߊl��
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeGetNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->get_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	0�_�C�� 1�p�[��
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_RomDataGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->rom_code;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��l����
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	��l����
 */
//-----------------------------------------------------------------------------
STRBUF* ZKN_GLBDATA_HeroNameGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->hero_name;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��l������
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	����
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_HeroSexGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->hero_sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O����e�L�X�g�o�[�W�����t���O�擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	lang	����R�[�h
 *
 *	@retval	TRUE	�t���O�������Ă���
 *	@retval	FALSE	�t���O�������Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeTextVersionFlagGet( const ZKN_GLB_DATA* cp_glb, int lang )
{
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb );

	// �����O����}�Ӄ}�X�^�[�o�[�W�����A�b�v����Ă��Ȃ���΁AFALSE�����Ԃ��Ȃ�
	if( ZukanWork_GetTextVersionUpMasterFlag( cp_glb->cp_zukansave_data ) == FALSE ){
		return FALSE;
	}
	return ZukanWork_GetTextVersionUpFlag( cp_glb->cp_zukansave_data, monsno, lang );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�o�[�W�����t���O
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@retval	TRUE �o�[�W�����A�b�v�ς�
 *	@retval	FALSE �o�[�W�����A�b�v����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeGraphicVersionFlagGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetGraphicVersionUpFlag( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�^�b�`�p�l���@�J�[�\���t���O��؂�ւ���
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_TouchCursorFlagSet( ZKN_GLB_DATA* cp_glb )
{
	// �^�b�`�p�l���D��
	if( sys.tp_cont ){
		cp_glb->touch_cursor_flag = ZKN_TCHCUSO_TOUCHPANEL;
		return ;
	}

	// �L�[�͗D��x�Ⴂ
	if( sys.cont ){
		cp_glb->touch_cursor_flag = ZKN_TCHCUSO_CURSOR;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�^�b�`�p�l���J�[�\���t���O�擾
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@retval	ZKN_TCHCUSO_TOUCHPANEL		�^�b�`�p�l���ōs��
 *	@retval ZKN_TCHCUSO_CURSOR			�J�[�\���ōs��
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_TouchCursorFlagGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->touch_cursor_flag;
}




//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V���I�E�@�S���@���X�g���獡�߂܂��Ă���|�P�������X�g���쐬
 *
 *	@param	p_buff				���X�g�쐬��		(�e�[�u�����ȏ゠�邱��)
 *	@param	p_count				�J�E���g
 *	@param	cp_zukansave_data	�}�ӃZ�[�u�f�[�^
 *	@param	cp_tbl				�\�[�g�e�[�u��
 *	@param	num					�e�[�u����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknPokeListTblMakeSortData( u16* p_buff, int* p_count, const ZUKAN_WORK* cp_zukansave_data, const u16* cp_tbl, int num )
{
	int i;			// ���[�v�p

	*p_count = 0;
	for( i=0; i<num; i++ ){
		
		// �߂܂������Ƃ��邩�`�F�b�N
		if( ZukanWork_GetPokeSeeFlag( cp_zukansave_data, cp_tbl[ i ] ) ){
			p_buff[ *p_count ] = cp_tbl[ i ];
			(*p_count) ++;
		}
		
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�[�g����Ă���e�[�u���Ȃ����炳��ɍi�荞��
 *
 *	@param	p_buff		�f�[�^�i�[��
 *	@param	p_count		�J�E���^
 *	@param	cp_tbl		�\�[�g�ς݃f�[�^�e�[�u��
 *	@param	num			�e�[�u����
 *	@param	cp_sarch_tbl�@�T�[�`�e�[�u��
 *	@param	sarch_num	�T�[�`�e�[�u����
 *	@param	see_ok_flg	���������|�P������OK���`�F�b�N
 *	@param	cp_zukansave_data	�}�ӃZ�[�u�f�[�^
 *
 *	@return	none
 *		��������
 */
//-----------------------------------------------------------------------------
static void ZknPokeListTblMakeSarch( u16* p_buff, int* p_count, const u16* cp_tbl, int num, const u16* cp_sarch_tbl, int sarch_num, BOOL see_ok_flg, const ZUKAN_WORK* cp_zukansave_data )
{
	int i,j;			// ���[�v�p

	*p_count = 0;
	for( i=0; i<num; i++ ){
		
		for( j=0; j<sarch_num; j++ ){
			if( cp_tbl[i] == cp_sarch_tbl[j] ){
				if( see_ok_flg == TRUE ){	// ���������ł����X�g�ɓ���Ă��Ƃ�
					break;
				}else{
					// �݂������͋�����Ȃ��Ƃ�
					// �߂܂��Ă��邩�`�F�b�N
					if( ZukanWork_GetPokeGetFlag( cp_zukansave_data, cp_tbl[ i ] ) ){
						break;
					}
				}
			}
		}
		
		// �T�[�`�e�[�u�����ɂ�������ݒ�
		if( j < sarch_num ){
			p_buff[ *p_count ] = cp_tbl[ i ];
			(*p_count) ++;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӄ|�P�������X�g�e�[�u���쐬�֐�
 *
 *	@param	p_poke_list			�쐬��
 *	@param	cp_zukansave_data	�}�ӃZ�[�u�f�[�^
 *	@param	cp_tbl				�������|�P�����Ń\�[�g�ς݃e�[�u��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknPokeListTblMake( ZKN_POKELIST_TBL* p_poke_list, const ZUKAN_WORK* cp_zukansave_data, const u16* cp_tbl, int tbl_num )
{
	int i;	// ���[�v�p

	p_poke_list->tbl_poke_num = 0;
	for( i=0; i<tbl_num; i++ ){
		
		// �߂܂������Ƃ����邩�`�F�b�N
		if( ZukanWork_GetPokeGetFlag( cp_zukansave_data, cp_tbl[ i ] ) ){
			p_poke_list->zkn_pokelist_tbl[ p_poke_list->tbl_poke_num ].type = ZKN_POKELIST_TYPE_GET;
		}else{
			p_poke_list->zkn_pokelist_tbl[ p_poke_list->tbl_poke_num ].type = ZKN_POKELIST_TYPE_SEE;
		}

		p_poke_list->zkn_pokelist_tbl[ p_poke_list->tbl_poke_num ].mons_no = cp_tbl[ i ];

		p_poke_list->tbl_poke_num ++;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӄ|�P�������X�g�`��e�[�u���쐬�֐�
 *
 *	@param	p_poke_list			�쐬��
 *	@param	cp_all_tbl			�\�[�g���f�[�^
 *	@param	tbl_num				�e�[�u����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknPokeListDrawTblMake( ZKN_POKELIST_TBL* p_poke_list, const u16* cp_all_tbl, int all_tbl_num )
{
	int i;	// ���[�v�p
	int count;

	// ���f�[�^����`��f�[�^�쐬		��̏Ȃ����f�[�^���_�~�[�Ƃ��Ċi�[����
	count = 0;
	p_poke_list->draw_tbl_poke_num = 0;
	for( i=0; i<all_tbl_num; i++ ){
		
		// �e�[�u���ȏ�ɂȂ�����I���
		if( count < p_poke_list->tbl_poke_num ){
			if( p_poke_list->zkn_pokelist_tbl[ count ].mons_no == cp_all_tbl[ i ] ){
				p_poke_list->zkn_pokelistdraw_tbl[ p_poke_list->draw_tbl_poke_num ] = count;
				count ++;
				p_poke_list->draw_tbl_poke_num++;

			}else{
				p_poke_list->zkn_pokelistdraw_tbl[ p_poke_list->draw_tbl_poke_num ] = POKEMON_LIST_DRAWTBL_DUMMY;
				p_poke_list->draw_tbl_poke_num++;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�`��e�[�u���R�s�[
 *
 *	@param	p_poke_list		�|�P�������X�g�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListDrawTblCopy( ZKN_POKELIST_TBL* p_poke_list )
{
	int i;	// ���[�v�p

	p_poke_list->draw_tbl_poke_num = 0;
	for( i=0; i<p_poke_list->tbl_poke_num; i++ ){
		
		p_poke_list->zkn_pokelistdraw_tbl[ p_poke_list->draw_tbl_poke_num ] = i;
		p_poke_list->draw_tbl_poke_num++;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�\�[�g�ް��擾
 *
 *	@param	heap		�q�[�v
 *	@param	idx			�ް����ޯ��
 *	@param	p_arry_num	�z��v�f���擾��
 *
 *	@return	�ް��o�b�t�@		�v�f����p_arry_num�Ɋi�[
 */
//-----------------------------------------------------------------------------
static u16* ZKN_SORTDATA_Get( int heap, int idx, int* p_arry_num )
{
	u32 size;
	u16* p_buf;
	
	GF_ASSERT( ZKN_SORTDATA_NUM > idx );
	

	// �ǂݍ���
	p_buf = ArcUtil_LoadEx( ARC_ZUKAN_DATA, ZKN_SORTDATA_START_IDX + idx, FALSE, heap, ALLOC_TOP, &size );

	*p_arry_num = size / ZKN_SORTDATA_ONESIZE;

	return p_buf;
}


//----------------------------------------------------------------------------
/**
 *	@brief	��ď����@���s��
 *
 *	@param	sort_type		�������
 *	@param	p_buff			���ʊi�[��
 *	@param	p_count			���ʂ̗v�f���i�[��
 *	@param	cp_tbl			���ް�
 *	@param	num				���ް���
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSort_Core( int sort_type, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data )
{
	u16* p_sort_data;	// ����ް�
	int sort_data_count;
	BOOL see_ok_flg = FALSE;
	

	// ���т���I������
	switch( sort_type ){
	case ZKN_POKELIST_SORT_NORMAL:		// �|�P�����i���o�[
		// ���̂܂�
		p_sort_data = NULL;
		break;
		
	case ZKN_POKELIST_SORT_GOZYUUON:		// �܏\��
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_AIUEO, &sort_data_count );
		see_ok_flg = TRUE;
		break;
		
	case ZKN_POKELIST_SORT_GRAM_L:		// �d��
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_HEAVY, &sort_data_count );
		break;
		
	case ZKN_POKELIST_SORT_GRAM_S:		// �y��
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_LIGHT, &sort_data_count );
		break;
		
	case ZKN_POKELIST_SORT_HIGH_L:		// ����
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TALL, &sort_data_count );
		break;
		
	case ZKN_POKELSIT_SOTT_HIGH_S:		// �Ⴂ
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_SMALL, &sort_data_count );
		break;
		
	default:
		GF_ASSERT(0);
		break;
	}

	if( p_sort_data != NULL ){
		ZknPokeListTblMakeSarch( p_buff, p_count,  p_sort_data, sort_data_count, cp_tbl, num, see_ok_flg, cp_zukansave_data );
		sys_FreeMemoryEz( p_sort_data );
	}else{

		// ���̂܂܃R�s�[
		memcpy( p_buff, cp_tbl, ZKN_SORTDATA_ONESIZE * num );
		*p_count = num;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���O����
 *
 *	@param	search_name		��������
 *	@param	p_buff			�i�[��o�b�t�@
 *	@param	p_count			�o�b�t�@�v�f��
 *	@param	cp_tbl			���ް�
 *	@param	num				���ް��v�f��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSarchName_Core( int search_name, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data )
{
	u16* p_sort_data;	// ����ް�
	int sort_data_count;

	// �Ȃ܂�
	switch( search_name ){
	case ZKN_POKELIST_SEARCH_NAME_NONE:
		// ���̂܂�
		p_sort_data = NULL;
		break;
	case ZKN_POKELIST_SEARCH_NAME_A:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_A, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_KA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_KA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_SA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_SA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_TA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_TA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_NA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_NA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_HA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_HA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_MA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_MA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_RA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_RA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_YAWA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_YAWA, &sort_data_count );
		break;
	default:
		GF_ASSERT(0);
		break;
	}

	if( p_sort_data != NULL ){
		ZknPokeListTblMakeSarch( p_buff, p_count, cp_tbl, num,  p_sort_data, sort_data_count, TRUE, cp_zukansave_data );
		sys_FreeMemoryEz( p_sort_data );
	}else{

		// ���̂܂܃R�s�[
		memcpy( p_buff, cp_tbl, ZKN_SORTDATA_ONESIZE * num );
		*p_count = num;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ߌ���
 *
 *	@param	search_type		��������
 *	@param	p_buff			�i�[��o�b�t�@
 *	@param	p_count			�o�b�t�@�v�f��
 *	@param	cp_tbl			���ް�
 *	@param	num				���ް��v�f��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSarchType_Core( int search_type, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data )
{
	u16* p_sort_data;	// ����ް�
	int sort_data_count;

	// ����
	switch( search_type ){
	case ZKN_POKELIST_SEARCH_TYPE_NONE:
		p_sort_data = NULL;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_NORMAL:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_NORMAL, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_BATTLE:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_BATTLE, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_HIKOU:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_HIKOU, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_POISON:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_POISON, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_JIMEN:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_JIMEN, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_IWA:		
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_IWA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_MUSHI:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_MUSHI, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_GHOST:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_GHOST, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_METAL:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_METAL, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_FIRE:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_FIRE, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_WATER:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_WATER, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KUSA:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_KUSA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_ELECTRIC:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_ELECTRIC, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_SP:		
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_SP, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KOORI:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_KOORI, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_DRAGON:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_DRAGON, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_AKU:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_AKU, &sort_data_count );
		break;

	default:
		GF_ASSERT(0);
		break;
	}

	if( p_sort_data != NULL ){
		ZknPokeListTblMakeSarch( p_buff, p_count, cp_tbl, num,  p_sort_data, sort_data_count, FALSE, cp_zukansave_data );
		sys_FreeMemoryEz( p_sort_data );
	}else{

		// ���̂܂܃R�s�[
		memcpy( p_buff, cp_tbl, ZKN_SORTDATA_ONESIZE * num );
		*p_count = num;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`����
 *
 *	@param	search_form		��������
 *	@param	p_buff			�i�[��o�b�t�@
 *	@param	p_count			�o�b�t�@�v�f��
 *	@param	cp_tbl			���ް�
 *	@param	num				���ް��v�f��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSarchForm_Core( int search_form, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data )
{
	u16* p_sort_data;	// ����ް�
	int sort_data_count;

	// ����
	switch( search_form ){
	case ZKN_POKELIST_SEARCH_FORM_NONE:
		p_sort_data = NULL;
		break;
	case ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_FOUR_LEGS, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_TWO_LEGS:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_TWO_LEGS, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_TAIL:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_TAIL, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_HARABAI:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_HARABAI, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_FOUR_WING:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_FOUR_WING, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_TWO_WING:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_TWO_WING, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_HAITSUKUBARI, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_STRAIGHT:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_STRAIGHT, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_ARM:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_ARM, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_LEGS:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_LEGS, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_MANY_LEGS:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_MANY_LEGS, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_WATER:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_WATER, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_CIRCLE:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_CIRCLE, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_COMP:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_COMP, &sort_data_count );
		break;
	default:
		GF_ASSERT(0);
		break;
	}

	if( p_sort_data != NULL ){
		ZknPokeListTblMakeSarch( p_buff, p_count, cp_tbl, num,  p_sort_data, sort_data_count, TRUE, cp_zukansave_data );
		sys_FreeMemoryEz( p_sort_data );
	}else{

		// ���̂܂܃R�s�[
		memcpy( p_buff, cp_tbl, ZKN_SORTDATA_ONESIZE * num );
		*p_count = num;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�߹��ؽē��̌��������@�������������J�E���g
 *
 *	@param	p_poke_list		�߹��ؽăe�[�u��
 *	@param	p_see_num		���������i�[��
 *	@param	p_get_num		�����������i�[��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknPokeListTblSeeGetNumCount( ZKN_POKELIST_TBL* p_poke_list, int* p_see_num, int* p_get_num )
{
	int i;	// ���[�v�p

	*p_see_num = 0;
	*p_get_num = 0;
	
	for( i=0; i<p_poke_list->tbl_poke_num; i++ ){
		if(p_poke_list->zkn_pokelist_tbl[ i ].type == ZKN_POKELIST_TYPE_GET	){

			(*p_get_num)++;
		}
		(*p_see_num)++;
	}
}

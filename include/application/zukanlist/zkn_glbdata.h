//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_glbdata.h
 *	@brief		�}�ӃA�v���P�[�V�������L�f�[�^
 *	@author		tomoya takahashi
 *	@data		2006.01.19
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_GLBDATA_H__
#define __ZKN_GLBDATA_H__

#include "include/poketool/monsno.h"
#include "include/savedata/zukanwork.h"
#include "include/savedata/mystatus.h"

#include "include/application/zukanlist/zkn_height_gram.h"

#undef GLOBAL
#ifdef	__ZKN_GLBDATA_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	�|�P�����^�C�v
//=====================================
enum{
	ZKN_POKELIST_TYPE_NONE,	// �킩��Ȃ�
	ZKN_POKELIST_TYPE_SEE,	// ������
	ZKN_POKELIST_TYPE_GET,	// �߂܂���
};

//-------------------------------------
//	�|�P�������X�g
//=====================================
#define POKEMON_LIST_TBL_NUM	(MONSNO_END)	// �e�[�u���� = �S�|�P�����̐�
#define POKEMON_LIST_DRAWTBL_DUMMY	( POKEMON_LIST_TBL_NUM + 1 )

//-------------------------------------
//	�|�P�������X�g�\�[�g
//=====================================
enum{
	ZKN_POKELIST_SORT_NORMAL,		// �|�P�����i���o�[
	ZKN_POKELIST_SORT_GOZYUUON,		// �܏\��
	ZKN_POKELIST_SORT_GRAM_L,		// �d��
	ZKN_POKELIST_SORT_GRAM_S,		// �y��
	ZKN_POKELIST_SORT_HIGH_L,		// ����
	ZKN_POKELSIT_SOTT_HIGH_S,		// �Ⴂ
	ZKN_POKELIST_SORT_NUM,
};

//-------------------------------------
//	�|�P���������}�X�N
//=====================================
// ���O
enum{
	ZKN_POKELIST_SEARCH_NAME_NONE,
	ZKN_POKELIST_SEARCH_NAME_A,
	ZKN_POKELIST_SEARCH_NAME_KA,
	ZKN_POKELIST_SEARCH_NAME_SA,
	ZKN_POKELIST_SEARCH_NAME_TA,
	ZKN_POKELIST_SEARCH_NAME_NA,
	ZKN_POKELIST_SEARCH_NAME_HA,
	ZKN_POKELIST_SEARCH_NAME_MA,
	ZKN_POKELIST_SEARCH_NAME_RA,
	ZKN_POKELIST_SEARCH_NAME_YAWA,
	ZKN_POKELIST_SEARCH_NAME_NUM
};
// �^�C�v
enum{
	ZKN_POKELIST_SEARCH_TYPE_NONE,
	ZKN_POKELIST_SEARCH_TYPE_NORMAL,
	ZKN_POKELIST_SEARCH_TYPE_BATTLE,	
	ZKN_POKELIST_SEARCH_TYPE_HIKOU,	
	ZKN_POKELIST_SEARCH_TYPE_POISON,	
	ZKN_POKELIST_SEARCH_TYPE_JIMEN,	
	ZKN_POKELIST_SEARCH_TYPE_IWA,		
	ZKN_POKELIST_SEARCH_TYPE_MUSHI,	
	ZKN_POKELIST_SEARCH_TYPE_GHOST,	
	ZKN_POKELIST_SEARCH_TYPE_METAL,	
	ZKN_POKELIST_SEARCH_TYPE_FIRE,	
	ZKN_POKELIST_SEARCH_TYPE_WATER,	
	ZKN_POKELIST_SEARCH_TYPE_KUSA,	
	ZKN_POKELIST_SEARCH_TYPE_ELECTRIC,
	ZKN_POKELIST_SEARCH_TYPE_SP,		
	ZKN_POKELIST_SEARCH_TYPE_KOORI,	
	ZKN_POKELIST_SEARCH_TYPE_DRAGON,	
	ZKN_POKELIST_SEARCH_TYPE_AKU,	
	ZKN_POKELIST_SEARCH_TYPE_NUM
};
// �`
enum{
	ZKN_POKELIST_SEARCH_FORM_NONE,
	ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS,
	ZKN_POKELIST_SEARCH_FORM_TWO_LEGS,
	ZKN_POKELIST_SEARCH_FORM_TAIL,
	ZKN_POKELIST_SEARCH_FORM_HARABAI,
	ZKN_POKELIST_SEARCH_FORM_FOUR_WING,
	ZKN_POKELIST_SEARCH_FORM_TWO_WING,
	ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI,
	ZKN_POKELIST_SEARCH_FORM_STRAIGHT,
	ZKN_POKELIST_SEARCH_FORM_ARM,
	ZKN_POKELIST_SEARCH_FORM_LEGS,
	ZKN_POKELIST_SEARCH_FORM_MANY_LEGS,
	ZKN_POKELIST_SEARCH_FORM_WATER,
	ZKN_POKELIST_SEARCH_FORM_CIRCLE,
	ZKN_POKELIST_SEARCH_FORM_COMP,
	ZKN_POKELIST_SEARCH_FORM_NUM
};

//-------------------------------------
//	�}�Ӄ��[�h
//=====================================
enum {
	ZKN_MODE_SHINOH,	// �V���I�E�}��
	ZKN_MODE_ZENKOKU,	// �S���}��
	ZKN_MODE_NAZO,		// �s��	�i�܂�1����}�ӂ��J���Ă��Ȃ��Ƃ��j
} ;

//-------------------------------------
//	�����\�[�g�؂�ւ��悤
//=====================================
enum {
	ZKN_SORTSEARCH_NONE,
	ZKN_SORTSEARCH_SORT,
} ;

//-------------------------------------
//	�^�b�`�p�l���@�J�[�\���t���O
//=====================================
enum{
	ZKN_TCHCUSO_TOUCHPANEL,
	ZKN_TCHCUSO_CURSOR,
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�|�P�������X�g�\����
//=====================================
typedef struct {
	int mons_no;	// �|�P�����i���o�[
	int type;		// ������ �߂܂���
} ZKN_POKELIST_DATA;

//-------------------------------------
//	�|�P�������X�g�e�[�u���\����
//=====================================
typedef struct {
	ZKN_POKELIST_DATA zkn_pokelist_tbl[ POKEMON_LIST_TBL_NUM ];
	int	tbl_no;			// ���I�𒆂̃e�[�u���i���o�[
	int tbl_poke_num;	// ���̃e�[�u���̑���

	// �\���p
	int zkn_pokelistdraw_tbl[ POKEMON_LIST_TBL_NUM ];
	int	draw_tbl_no;			// ���I�𒆂̃e�[�u���i���o�[
	int draw_tbl_poke_num;		// ���̃e�[�u���̑���
} ZKN_POKELIST_TBL;


//-------------------------------------
//	�}�ӃO���[�o���f�[�^
//
//	�����A�v���P�[�V�����ŋ��L�������f�[�^
//=====================================
typedef struct{
	// �}�Ӊ�ʃf�[�^
	const ZUKAN_WORK*	cp_zukansave_data;
	
	// �|�P�������X�g�e�[�u���\����
	ZKN_POKELIST_TBL poke_list;			// �\���f�[�^

	// �}�Ӄ��[�h
	int zkn_mode;

	// �S���}�ӏ����t���O
	BOOL zkn_allmap_get;

	// ������
	int	see_num;

	// �ߊl��
	int get_num;

	// �����\�[�g�؂�ւ��悤
	int sort_search_flag;

	// �}�ӂ��J�����Ƃ��̎��ԑ�
	int time_zone;

	// �����d���f�[�^
	ZKN_HEIGHT_GRAM_PTR height_gram;

	// ROM�R�[�h
	u32 rom_code;
	
	// ��l�����j������
	u32 hero_sex; 
	
	// ��l���̖��O
	STRBUF*	hero_name;

	// �^�b�`�p�l���@�J�[�\���t���O
	int touch_cursor_flag;
	
	// �Ō�ɐ}�Ӄe�L�X�g�������|�P����
	u16 last_see_monsno;
	u16 last_see_zkn_mode;

	// �B���}�b�v
	BOOL hidemap_id_D15;
	BOOL hidemap_id_D30;
	BOOL hidemap_id_L04;
	BOOL hidemap_id_D18;
} ZKN_GLB_DATA;


//-------------------------------------
//	�O���[�o���f�[�^�������\����
//=====================================
typedef struct {
	const ZUKAN_WORK* cp_zukansave_data;
	const MYSTATUS* cp_hero_data;
	int time_zone;
	BOOL hidemap_id_D15;
	BOOL hidemap_id_D30;
	BOOL hidemap_id_L04;
	BOOL hidemap_id_D18;
	u32 init_list_monsno;
	u32 zkn_mode;
} ZKN_GLB_DATA_INIT;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------

GLOBAL void ZKN_GLBDATA_Init( ZKN_GLB_DATA* p_glb, ZKN_GLB_DATA_INIT* p_init, int heap );
GLOBAL void ZKN_GLBDATA_Delete( ZKN_GLB_DATA* p_glb );

GLOBAL u32 ZKN_GLBDATA_SaveData_SexGet( const ZKN_GLB_DATA* cp_glb, int monsno, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_AnoonFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_SiiusiFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_SiidorugoFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_MinomuttiFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_MinomesuFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_FirstFormGet( const ZKN_GLB_DATA* cp_glb, u32 monsno );
GLOBAL u32 ZKN_GLBDATA_SaveData_SexNumGet( const ZKN_GLB_DATA* cp_glb, int monsno );
GLOBAL u32 ZKN_GLBDATA_SaveData_AnoonNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_SiiusiNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_SiidorugoNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_MinomuttiNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_MinomesuNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_PattiruRndGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_DeokisisuFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_DeokisisuFormSeeNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL BOOL ZKN_GLBDATA_SaveData_ZenkokuZukanComp( const ZKN_GLB_DATA* cp_glb );
GLOBAL BOOL ZKN_GLBDATA_SaveData_ZenkokuZukanGet( const ZKN_GLB_DATA* cp_glb );


GLOBAL void ZKN_GLBDATA_PokeTextSeeSetMonsno( ZKN_GLB_DATA* p_glb, u32 monsno );
GLOBAL u32 ZKN_GLBDATA_PokeTextSeeGetMonsno( const ZKN_GLB_DATA* cp_glb );
GLOBAL void ZKN_GLBDATA_PokeTextSeeSetZknMode( ZKN_GLB_DATA* p_glb, u32 zkn_mode );
GLOBAL u32 ZKN_GLBDATA_PokeTextSeeGetZknMode( const ZKN_GLB_DATA* cp_glb );

GLOBAL BOOL ZKN_GLBDATA_SaveData_GraModeGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL BOOL ZKN_GLBDATA_SaveData_TextModeGet( const ZKN_GLB_DATA* cp_glb, int country );

GLOBAL BOOL ZKN_GLBDATA_PokeListTblMake_DummyListCutFlg( ZKN_GLB_DATA* p_glb, int sort_type, int search_name, int search_type1, int search_type2, int search_form, int shinoh, int heap, BOOL dummy_list_cut );

GLOBAL BOOL ZKN_GLBDATA_PokeListTblMake( ZKN_GLB_DATA* p_glb, int sort_type, int search_name, int search_type1, int search_type2, int search_form, int shinoh, int heap );

GLOBAL BOOL ZKN_GLBDATA_PokeZknModeChengeCheck( const ZKN_GLB_DATA* cp_glb, int zkn_mode );
GLOBAL BOOL ZKN_GLBDATA_PokeZknModeChenge( ZKN_GLB_DATA* p_glb, int zkn_mode );
GLOBAL int ZKN_GLBDATA_PokeZknModeGet( const ZKN_GLB_DATA* cp_glb );

GLOBAL BOOL ZKN_GLBDATA_PokeListTblNoSetCheck( const ZKN_GLB_DATA* cp_glb, int no );
GLOBAL BOOL ZKN_GLBDATA_PokeListTblNoSet_Monsno( ZKN_GLB_DATA* p_glb, int monsno );
GLOBAL BOOL ZKN_GLBDATA_PokeListTblNoSet( ZKN_GLB_DATA* p_glb, int no );
GLOBAL BOOL ZKN_GLBDATA_PokeListTblNoAdd( ZKN_GLB_DATA* p_glb, int no );
GLOBAL int ZKN_GLBDATA_PokeListTblNoGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeListTblNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeListTblNoGet_Monsno( const ZKN_GLB_DATA* cp_glb, u32 monsno );
GLOBAL int ZKN_GLBDATA_PokeMonsNoGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeMonsTypeGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL const ZKN_POKELIST_DATA* ZKN_GLBDATA_PokeListTblGet( const ZKN_GLB_DATA* cp_glb, int tbl_no );
GLOBAL BOOL ZKN_GLBDATA_PokeListDrawTblNoSetCheck( const ZKN_GLB_DATA* cp_glb, int no );
GLOBAL BOOL ZKN_GLBDATA_PokeListDrawTblNoSet( ZKN_GLB_DATA* p_glb, int no );
GLOBAL BOOL ZKN_GLBDATA_PokeListDrawTblNoAdd( ZKN_GLB_DATA* p_glb, int no );
GLOBAL BOOL ZKN_GLBDATA_PokeListDrawTblNoAddCheck( ZKN_GLB_DATA* p_glb, int no );
GLOBAL int ZKN_GLBDATA_PokeListDrawTblNoGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeListDrawTblNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeListDrawTblDataGet( const ZKN_GLB_DATA* cp_glb, int no );
GLOBAL void ZKN_GLBDATA_PokeListDrawTblSetNowTblNo( ZKN_GLB_DATA* p_glb );

GLOBAL int ZKN_GLBDATA_PokeSeeNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeGetNumGet( const ZKN_GLB_DATA* cp_glb );

GLOBAL int ZKN_GLBDATA_RomDataGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL STRBUF* ZKN_GLBDATA_HeroNameGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_HeroSexGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL BOOL ZKN_GLBDATA_PokeTextVersionFlagGet( const ZKN_GLB_DATA* cp_glb, int lang );
GLOBAL BOOL ZKN_GLBDATA_PokeGraphicVersionFlagGet( const ZKN_GLB_DATA* cp_glb );

GLOBAL void ZKN_GLBDATA_TouchCursorFlagSet( ZKN_GLB_DATA* cp_glb );
GLOBAL BOOL ZKN_GLBDATA_TouchCursorFlagGet( const ZKN_GLB_DATA* cp_glb );

#undef	GLOBAL
#endif		// __ZKN_GLBDATA_H__


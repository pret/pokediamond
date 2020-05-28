//******************************************************************************
/**
 *
 * @file	fieldobj_drawdata.c
 * @brief	フィールドOBJ描画データ
 * @author	kagaya
 * @data	05.07.20
 *
 */
//******************************************************************************

//==============================================================================
/*
	＜新規OBJの追加＞
	１：fieldobj_code.hに表示コードを追加
	２：ビルボードであればDATA_FieldOBJ_ResmNArcTbl_Tex[]へ表示コードに対応したテクスチャを指定
	３：FIELD_OBJ_DRAW_PROC_LIST型の初期化、描画、削除、退避復帰関数を追加
	４：DATA_FieldOBJDrawProcListRegTbl[]へ３で作成した関数の定義
	５：DATA_FieldOBJ_BlActHeaderPathIDTbl[]へ表示コードに対応した情報を追加
	６：DATA_FieldOBJCodeDrawStateTbl[]へ表示コードのステータスを追加
	
	＜新規モデリングの追加＞
	１：fieldobj_code.hにモデルIDを追加
	２：DATA_FieldOBJ_ResmNArcTbl_Mdl[]へモデルIDに対応したモデリングを指定
	３：常駐する必要がある場合、DATA_FieldOBJ_Regular_Mdl[]へ登録
	
	＜新規アニメの追加＞
	１：fieldobj_code.hにアニメIDを追加
	２：DATA_FieldOBJ_ResmNArcTbl_Anm[]へアニメIDに対応したモデリングを指定
	３：常駐する必要がある場合、DATA_FieldOBJ_Regular_Anm[]へ登録
*/
//==============================================================================

#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"

#include "..\data\mmodel\mmodel.naix"	//アーカイブID

//==============================================================================
//	extern
//==============================================================================

//==============================================================================
//	フィールドOBJ 描画関数定義
//==============================================================================
//--------------------------------------------------------------
///	HERO
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_Hero =
{
	FieldOBJ_DrawBlActHero_Init,
	FieldOBJ_DrawBlActHero_Draw,
	FieldOBJ_DrawBlActHero_Delete,
	FieldOBJ_DrawBlActHero_Push,
	FieldOBJ_DrawBlActHero_Pop,
};

//--------------------------------------------------------------
///	CYCLEHERO
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_HeroCycle = 
{
	FieldOBJ_DrawBlActHero_Init,
	FieldOBJ_DrawBlActHeroCycle_Draw,
	FieldOBJ_DrawBlActHero_Delete,
	FieldOBJ_DrawBlActHero_Push,
	FieldOBJ_DrawBlActHero_Pop,
};

//--------------------------------------------------------------
///	SWIMHERO
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_HeroSwim =
{
	FieldOBJ_DrawBlActHero_Init,
	FieldOBJ_DrawBlActHeroSwim_Draw,
	FieldOBJ_DrawBlActHero_Delete,
	FieldOBJ_DrawBlActHero_Push,
	FieldOBJ_DrawBlActHero_Pop,
};

//--------------------------------------------------------------
///	SPHERO
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_HeroSp =
{
	FieldOBJ_DrawBlActHero_Init,
	FieldOBJ_DrawBlActHeroSp_Draw,
	FieldOBJ_DrawBlActHero_Delete,
	FieldOBJ_DrawBlActHero_Push,
	FieldOBJ_DrawBlActHero_Pop,
};

//--------------------------------------------------------------
///	WATERHERO
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_HeroWater =
{
	FieldOBJ_DrawBlActHero_Init,
	FieldOBJ_DrawBlActHeroWater_Draw,
	FieldOBJ_DrawBlActHero_Delete,
	FieldOBJ_DrawBlActHero_Push,
	FieldOBJ_DrawBlActHero_Pop,
};

//--------------------------------------------------------------
///	FISHINGHERO
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_HeroFishing =
{
	FieldOBJ_DrawBlActHero_Init,
	FieldOBJ_DrawBlActHeroFishing_Draw,
	FieldOBJ_DrawBlActHero_Delete,
	FieldOBJ_DrawBlActHero_Push,
	FieldOBJ_DrawBlActHero_Pop,
};

//--------------------------------------------------------------
///	POKEHERO
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_HeroPoketch =
{
	FieldOBJ_DrawBlActHero_Init,
	FieldOBJ_DrawBlActHeroPoketch_Draw,
	FieldOBJ_DrawBlActHero_Delete,
	FieldOBJ_DrawBlActHero_Push,
	FieldOBJ_DrawBlActHero_Pop,
};

//--------------------------------------------------------------
///	BANZAIHERO
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_HeroBanzai =
{
	FieldOBJ_DrawBlActHero_Init,
	FieldOBJ_DrawBlActHeroBanzai_Draw,
	FieldOBJ_DrawBlActHero_Delete,
	FieldOBJ_DrawBlActHero_Push,
	FieldOBJ_DrawBlActHero_Pop,
};

//--------------------------------------------------------------
///	ビルボードアクター使用　一般人標準00
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_BlAct00 =
{
	FieldOBJ_DrawBlAct00_Init,
	FieldOBJ_DrawBlAct00_Draw,
	FieldOBJ_DrawBlAct00_Delete,
	FieldOBJ_DrawBlAct00_Push,
	FieldOBJ_DrawBlAct00_Pop,
};

//--------------------------------------------------------------
///	ビルボードアクター使用　一般人標準00　アニメなし
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_BlAct00AnmNon =
{
	FieldOBJ_DrawBlAct00_Init,
	FieldOBJ_DrawBlAct00AnmNon_Draw,
	FieldOBJ_DrawBlAct00_Delete,
	FieldOBJ_DrawBlAct00_Push,
	FieldOBJ_DrawBlAct00_Pop,
};

//--------------------------------------------------------------
///	ビルボードアクター使用　一般人標準00　１パターンアニメ
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_BlAct00AnmOneP =
{
	FieldOBJ_DrawBlAct00_Init,
	FieldOBJ_DrawBlAct00AnmOneP_Draw,
	FieldOBJ_DrawBlAct00_Delete,
	FieldOBJ_DrawBlAct00_Push,
	FieldOBJ_DrawBlAct00_Pop,
};

//--------------------------------------------------------------
///	ビルボードアクター使用　PCWOMAN
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_BlActPcwoman =
{
	FieldOBJ_DrawBlAct00_Init,
	FieldOBJ_DrawBlActPcWoman_Draw,
	FieldOBJ_DrawBlAct00_Delete,
	FieldOBJ_DrawBlAct00_Push,
	FieldOBJ_DrawBlAct00_Pop,
};

//--------------------------------------------------------------
///	ビルボードアクター使用　KOIKING
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_BlActKoiking =
{
	FieldOBJ_DrawBlActKoiking_Init,
	FieldOBJ_DrawBlActKoiking_Draw,
	FieldOBJ_DrawBlActKoiking_Delete,
	FieldOBJ_DrawBlActKoiking_Push,
	FieldOBJ_DrawBlActKoiking_Pop,
};

//--------------------------------------------------------------
///	3Dモデル使用　標準00　看板
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_Model00Board =
{
	FieldOBJ_DrawModel00_Board_Init,
	FieldOBJ_DrawModel00_Draw,
	FieldOBJ_DrawModel00_Delete,
	FieldOBJ_DrawModel00_Push,
	FieldOBJ_DrawModel00_Board_Pop,
};

//--------------------------------------------------------------
///	木の実
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_Seed =
{
	FieldOBJ_DrawSeed_Init,
	FieldOBJ_DrawSeed_Draw,
	FieldOBJ_DrawSeed_Delete,
	FieldOBJ_DrawSeed_Push,
	FieldOBJ_DrawSeed_Pop,
};

//--------------------------------------------------------------
///	ビルボードアクター使用　鳥
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_BlActBird =
{
	FieldOBJ_DrawBlAct00_Init,
	FieldOBJ_DrawBlActBird_Draw,
	FieldOBJ_DrawBlAct00_Delete,
	FieldOBJ_DrawBlAct00_Push,
	FieldOBJ_DrawBlAct00_Pop,
};

//--------------------------------------------------------------
///	3Dモデル使用　標準00　雪玉
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_Model00SnowBall =
{
	FieldOBJ_DrawModel00_SnowBall_Init,
	FieldOBJ_DrawModel00_Draw,
	FieldOBJ_DrawModel00_Delete,
	FieldOBJ_DrawModel00_Push,
	FieldOBJ_DrawModel00_SnowBall_Pop,
};

//--------------------------------------------------------------
///	3Dモデル使用　標準00　本
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_Model00Book =
{
	FieldOBJ_DrawModel00_Book_Init,
	FieldOBJ_DrawModel00_Draw,
	FieldOBJ_DrawModel00_Delete,
	FieldOBJ_DrawModel00_Push,
	FieldOBJ_DrawModel00_Book_Pop,
};

//--------------------------------------------------------------
///	3Dモデル使用　標準00　ドア２
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_Model00Door2 =
{
	FieldOBJ_DrawModel00_Door2_Init,
	FieldOBJ_DrawModel00_Draw,
	FieldOBJ_DrawModel00_Delete,
	FieldOBJ_DrawModel00_Push,
	FieldOBJ_DrawModel00_Door2_Pop,
};

//--------------------------------------------------------------
///	NONDRAW
//--------------------------------------------------------------
const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_Non =
{
	FieldOBJ_DrawNon_Init,
	FieldOBJ_DrawNon_Draw,
	FieldOBJ_DrawNon_Delete,
	FieldOBJ_DrawNon_Push,
	FieldOBJ_DrawNon_Pop,
};

//--------------------------------------------------------------
// @author	tomoya katahashi
///	LEGENDPOKE		伝説ポケモン　イア　エア
//--------------------------------------------------------------
const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_Legend =
{
	FieldOBJ_DrawLegend_Init,
	FieldOBJ_DrawLegend_Draw,
	FieldOBJ_DrawLegend_Delete,
	FieldOBJ_DrawLegend_Push,
	FieldOBJ_DrawLegend_Pop,
};

//--------------------------------------------------------------
// @author	tomoya katahashi
///	LEGENDPOKE		伝説ポケモン　レイ　アイ　ハイ
//--------------------------------------------------------------
const FIELD_OBJ_DRAW_PROC_LIST DATA_FieldOBJDraw_ReiAiHai =
{
	FieldOBJ_DrawReiAiHai_Init,
	FieldOBJ_DrawReiAiHai_Draw,
	FieldOBJ_DrawReiAiHai_Delete,
	FieldOBJ_DrawLegend_Push,
	FieldOBJ_DrawLegend_Pop,
};

//==============================================================================
//	フィールドOBJ 描画関数まとめ
//==============================================================================
//--------------------------------------------------------------
///	描画関数まとめ　並びはOBJコードと一致->不順にした
//--------------------------------------------------------------
const FIELD_OBJ_DRAW_PROC_LIST_REG DATA_FieldOBJDrawProcListRegTbl[] =
{
	{ HERO,			&DATA_FieldOBJDraw_Hero },
	{ BABYBOY1,		&DATA_FieldOBJDraw_BlAct00 },
	{ BABYGIRL1,	&DATA_FieldOBJDraw_BlAct00 },
	{ BOY1,			&DATA_FieldOBJDraw_BlAct00 },
	{ BOY2,			&DATA_FieldOBJDraw_BlAct00 },
	{ BOY3,			&DATA_FieldOBJDraw_BlAct00 },
	{ GIRL1,		&DATA_FieldOBJDraw_BlAct00 },
	{ GIRL2,		&DATA_FieldOBJDraw_BlAct00 },
	{ GIRL3,		&DATA_FieldOBJDraw_BlAct00 },
	{ MAN1,			&DATA_FieldOBJDraw_BlAct00 },
	{ MAN2,			&DATA_FieldOBJDraw_BlAct00 },
	{ MAN3,			&DATA_FieldOBJDraw_BlAct00 },
	{ WOMAN1,		&DATA_FieldOBJDraw_BlAct00 },
	{ WOMAN2,		&DATA_FieldOBJDraw_BlAct00 },
	{ WOMAN3,		&DATA_FieldOBJDraw_BlAct00 },
	{ MIDDLEMAN1,	&DATA_FieldOBJDraw_BlAct00 },
	{ MIDDLEWOMAN1,	&DATA_FieldOBJDraw_BlAct00 },
	{ OLDMAN1,		&DATA_FieldOBJDraw_BlAct00 },
	{ OLDWOMAN1,	&DATA_FieldOBJDraw_BlAct00 },
	{ BIGMAN,		&DATA_FieldOBJDraw_BlAct00 },
	{ MOUNT,		&DATA_FieldOBJDraw_BlAct00 },
	{ CYCLEHERO,	&DATA_FieldOBJDraw_HeroCycle },
	{REPORTER,	&DATA_FieldOBJDraw_BlAct00 },
	{CAMERAMAN,	&DATA_FieldOBJDraw_BlAct00 },
	{SHOPM1,	&DATA_FieldOBJDraw_BlAct00 },
	{SHOPW1,	&DATA_FieldOBJDraw_BlAct00 },
	{PCWOMAN1,	&DATA_FieldOBJDraw_BlActPcwoman },
	{PCWOMAN2,	&DATA_FieldOBJDraw_BlAct00 },
	{PCWOMAN3,	&DATA_FieldOBJDraw_BlAct00 },
	{ASSISTANTM,	&DATA_FieldOBJDraw_BlAct00 },
	{ASSISTANTW,	&DATA_FieldOBJDraw_BlAct00 },
	{BADMAN,	&DATA_FieldOBJDraw_BlAct00 },
	{SKIERM,	&DATA_FieldOBJDraw_BlAct00 },
	{SKIERW,	&DATA_FieldOBJDraw_BlAct00 },
	{POLICEMAN,	&DATA_FieldOBJDraw_BlAct00 },
	{IDOL,	&DATA_FieldOBJDraw_BlAct00 },
	{GENTLEMAN,	&DATA_FieldOBJDraw_BlAct00 },
	{LADY,	&DATA_FieldOBJDraw_BlAct00 },
	{CYCLEM,	&DATA_FieldOBJDraw_BlAct00 },
	{CYCLEW,	&DATA_FieldOBJDraw_BlAct00 },
	{WORKMAN,	&DATA_FieldOBJDraw_BlAct00 },
	{FARMER,	&DATA_FieldOBJDraw_BlAct00 },
	{COWGIRL,	&DATA_FieldOBJDraw_BlAct00 },
	{CLOWN,	&DATA_FieldOBJDraw_BlAct00 },
	{ARTIST,	&DATA_FieldOBJDraw_BlAct00 },
	{SPORTSMAN,	&DATA_FieldOBJDraw_BlAct00 },
	{SWIMMERM,	&DATA_FieldOBJDraw_BlAct00 },
	{SWIMMERW,	&DATA_FieldOBJDraw_BlAct00 },
	{BEACHGIRL,	&DATA_FieldOBJDraw_BlAct00 },
	{BEACHBOY,	&DATA_FieldOBJDraw_BlAct00 },
	{EXPLORE,	&DATA_FieldOBJDraw_BlAct00 },
	{FIGHTER,	&DATA_FieldOBJDraw_BlAct00 },
	{CAMPBOY,	&DATA_FieldOBJDraw_BlAct00 },
	{PICNICGIRL,	&DATA_FieldOBJDraw_BlAct00 },
	{FISHING,	&DATA_FieldOBJDraw_BlAct00 },
	{AMBRELLA,	&DATA_FieldOBJDraw_BlAct00 },
	{SEAMAN,	&DATA_FieldOBJDraw_BlAct00 },
	{BRINGM,	&DATA_FieldOBJDraw_BlAct00 },
	{BRINGW,	&DATA_FieldOBJDraw_BlAct00 },
	{WAITER,	&DATA_FieldOBJDraw_BlAct00 },
	{WAITRESS,	&DATA_FieldOBJDraw_BlAct00 },
	{VETERAN,	&DATA_FieldOBJDraw_BlAct00 },
	{GORGGEOUSM,	&DATA_FieldOBJDraw_BlAct00 },
	{GORGGEOUSW,	&DATA_FieldOBJDraw_BlAct00 },
	{BOY4,	&DATA_FieldOBJDraw_BlAct00 },
	{GIRL4,	&DATA_FieldOBJDraw_BlAct00 },
	{MAN4,	&DATA_FieldOBJDraw_BlAct00 },
	{WOMAN4,	&DATA_FieldOBJDraw_BlAct00 },
	{MAN5,	&DATA_FieldOBJDraw_BlAct00 },
	{WOMAN5,	&DATA_FieldOBJDraw_BlAct00 },
	{MYSTERY,	&DATA_FieldOBJDraw_BlAct00 },
	{PIKACHU,	&DATA_FieldOBJDraw_BlAct00 },
	{PIPPI,	&DATA_FieldOBJDraw_BlAct00 },
	{PURIN,	&DATA_FieldOBJDraw_BlAct00 },
	{KODUCK,	&DATA_FieldOBJDraw_BlAct00 },
	{PRASLE,	&DATA_FieldOBJDraw_BlAct00 },
	{MINUN,	&DATA_FieldOBJDraw_BlAct00 },
	{MARIL,	&DATA_FieldOBJDraw_BlAct00 },
	{ACHAMO,	&DATA_FieldOBJDraw_BlAct00 },
	{ENECO,	&DATA_FieldOBJDraw_BlAct00 },
	{GONBE,	&DATA_FieldOBJDraw_BlAct00 },
	{BABY,	&DATA_FieldOBJDraw_BlAct00 },
	{MIDDLEMAN2,	&DATA_FieldOBJDraw_BlAct00 },
	{MIDDLEWOMAN2,	&DATA_FieldOBJDraw_BlAct00 },
	{ROCK,	&DATA_FieldOBJDraw_BlAct00AnmNon },
	{BREAKROCK,	&DATA_FieldOBJDraw_BlAct00AnmNon },
	{TREE,	&DATA_FieldOBJDraw_BlAct00AnmNon },
	{MONATERBALL,	&DATA_FieldOBJDraw_BlAct00AnmNon },
	{SHADOW,	&DATA_FieldOBJDraw_BlAct00 },
	{BOUGH,	&DATA_FieldOBJDraw_BlAct00 },
	{FALLTREE,	&DATA_FieldOBJDraw_BlAct00 },
	{ BOARD_A, &DATA_FieldOBJDraw_Model00Board },
	{ BOARD_B, &DATA_FieldOBJDraw_Model00Board },
	{ BOARD_C, &DATA_FieldOBJDraw_Model00Board },
	{ BOARD_D, &DATA_FieldOBJDraw_Model00Board },
	{ BOARD_E, &DATA_FieldOBJDraw_Model00Board },
	{ BOARD_F, &DATA_FieldOBJDraw_Model00Board },
	{ HEROINE,	&DATA_FieldOBJDraw_Hero },
	{ CYCLEHEROINE,	&DATA_FieldOBJDraw_HeroCycle },
	{ DOCTOR,	&DATA_FieldOBJDraw_BlAct00 },
	{ SEED, &DATA_FieldOBJDraw_Seed },
	{ SNOWBALL, &DATA_FieldOBJDraw_Model00SnowBall },
	{ GINGABOSS, &DATA_FieldOBJDraw_BlAct00 },
	{ GKANBU1, &DATA_FieldOBJDraw_BlAct00 },
	{ GKANBU2, &DATA_FieldOBJDraw_BlAct00 },
	{ GKANBU3, &DATA_FieldOBJDraw_BlAct00 },
	{ GINGAM, &DATA_FieldOBJDraw_BlAct00 },
	{ GINGAW, &DATA_FieldOBJDraw_BlAct00 },
	{ LEADER1, &DATA_FieldOBJDraw_BlAct00 },
	{ LEADER2, &DATA_FieldOBJDraw_BlAct00 },
	{ LEADER3, &DATA_FieldOBJDraw_BlAct00 },
	{ LEADER4, &DATA_FieldOBJDraw_BlAct00 },
	{ LEADER5, &DATA_FieldOBJDraw_BlAct00 },
	{ LEADER6, &DATA_FieldOBJDraw_BlAct00 },
	{ LEADER7, &DATA_FieldOBJDraw_BlAct00 },
	{ LEADER8, &DATA_FieldOBJDraw_BlAct00 },
	{ BIGFOUR1, &DATA_FieldOBJDraw_BlAct00 },
	{ BIGFOUR2, &DATA_FieldOBJDraw_BlAct00 },
	{ BIGFOUR3, &DATA_FieldOBJDraw_BlAct00 },
	{ BIGFOUR4, &DATA_FieldOBJDraw_BlAct00 },
	{ CHAMPION, &DATA_FieldOBJDraw_BlAct00 },
	{ PAPA, &DATA_FieldOBJDraw_BlAct00 },
	{ MAMA, &DATA_FieldOBJDraw_BlAct00 },
	{ SEVEN1, &DATA_FieldOBJDraw_BlAct00 },
	{ SEVEN2, &DATA_FieldOBJDraw_BlAct00 },
	{ SEVEN3, &DATA_FieldOBJDraw_BlAct00 },
	{ SEVEN4, &DATA_FieldOBJDraw_BlAct00 },
	{ SEVEN5, &DATA_FieldOBJDraw_BlAct00 },
	{ SEVEN6, &DATA_FieldOBJDraw_BlAct00 },
	{ SEVEN7, &DATA_FieldOBJDraw_BlAct00 },
	{ RIVEL, &DATA_FieldOBJDraw_BlAct00 },
	{ BOAT, &DATA_FieldOBJDraw_BlAct00 },
	{ TRAIN, &DATA_FieldOBJDraw_BlAct00 },
	{ SPPOKE1, &DATA_FieldOBJDraw_ReiAiHai },
	{ SPPOKE2, &DATA_FieldOBJDraw_ReiAiHai },
	{ SPPOKE3, &DATA_FieldOBJDraw_ReiAiHai },
	{ SPPOKE4, &DATA_FieldOBJDraw_Legend },
	{ SPPOKE5, &DATA_FieldOBJDraw_Legend },
	{ SPPOKE6, &DATA_FieldOBJDraw_BlAct00AnmOneP },
	{ SPPOKE7, &DATA_FieldOBJDraw_BlAct00AnmOneP },
	{ SPPOKE8, &DATA_FieldOBJDraw_BlAct00 },
	{ SPPOKE9, &DATA_FieldOBJDraw_BlAct00AnmOneP },
	{ SPPOKE10, &DATA_FieldOBJDraw_BlAct00AnmOneP },
	{ SPPOKE11, &DATA_FieldOBJDraw_BlAct00AnmOneP },
	{ OBAKE, &DATA_FieldOBJDraw_BlAct00 },
	{ WOMAN6, &DATA_FieldOBJDraw_BlAct00 },
	{ OLDMAN2, &DATA_FieldOBJDraw_BlAct00 },
	{ OLDWOMAN2, &DATA_FieldOBJDraw_BlAct00 },
	{ OOKIDO, &DATA_FieldOBJDraw_BlAct00 },
	{ MIKAN, &DATA_FieldOBJDraw_BlAct00 },
	{ SUNGLASSES, &DATA_FieldOBJDraw_BlAct00 },
	{ TOWERBOSS, &DATA_FieldOBJDraw_BlAct00 },
	{ SNOWCOVER, &DATA_FieldOBJDraw_BlAct00 },
	{ TREECOVER, &DATA_FieldOBJDraw_BlAct00 },
	{ ROCKCOVER, &DATA_FieldOBJDraw_BlAct00 },
	{ BIRD, &DATA_FieldOBJDraw_BlActBird },
	{ BAG, &DATA_FieldOBJDraw_BlAct00 },
	{ MAID, &DATA_FieldOBJDraw_BlAct00 },
	{ SPHERO, &DATA_FieldOBJDraw_HeroSp },
	{ SPHEROINE, &DATA_FieldOBJDraw_HeroSp },
	{ WATERHERO, &DATA_FieldOBJDraw_HeroWater },
	{ WATERHEROINE, &DATA_FieldOBJDraw_HeroWater },
	{ SWIMHERO, &DATA_FieldOBJDraw_HeroSwim },
	{ SWIMHEROINE, &DATA_FieldOBJDraw_HeroSwim },
	{ VENTHOLE, &DATA_FieldOBJDraw_BlAct00AnmNon },
	{ BOOK, &DATA_FieldOBJDraw_Model00Book },
	{ SPPOKE12, &DATA_FieldOBJDraw_BlAct00AnmNon },
	{ BALLOON, &DATA_FieldOBJDraw_BlAct00 },
	{ CONTESTHERO,	&DATA_FieldOBJDraw_Hero },
	{ CONTESTHEROINE,	&DATA_FieldOBJDraw_Hero },
	{ FISHINGHERO,	&DATA_FieldOBJDraw_HeroFishing },
	{ FISHINGHEROINE,	&DATA_FieldOBJDraw_HeroFishing },
	{ MOSS, &DATA_FieldOBJDraw_BlAct00 },
	{ FREEZES, &DATA_FieldOBJDraw_BlAct00 },
	{ POLE, &DATA_FieldOBJDraw_BlAct00 },
	{ DELIVERY, &DATA_FieldOBJDraw_BlAct00 },
	{ DSBOY, &DATA_FieldOBJDraw_BlAct00 },
	{ KOIKING, &DATA_FieldOBJDraw_BlActKoiking },
	{ POKEHERO, &DATA_FieldOBJDraw_HeroPoketch },
	{ POKEHEROINE, &DATA_FieldOBJDraw_HeroPoketch },
	{ SAVEHERO, &DATA_FieldOBJDraw_HeroSp },
	{ SAVEHEROINE, &DATA_FieldOBJDraw_HeroSp },
	{ BANZAIHERO, &DATA_FieldOBJDraw_HeroBanzai },
	{ BANZAIHEROINE, &DATA_FieldOBJDraw_HeroBanzai },
	{DOOR, &DATA_FieldOBJDraw_BlAct00AnmNon },
	{MONUMENT, &DATA_FieldOBJDraw_BlAct00AnmNon },
	{ PATIRITUSU, &DATA_FieldOBJDraw_BlAct00 },
	{ KINOCOCO, &DATA_FieldOBJDraw_BlAct00 },
	{ MIMITUTO, &DATA_FieldOBJDraw_BlAct00 },
	{ KOLUCKY, &DATA_FieldOBJDraw_BlAct00 },
	{ WANRIKY, &DATA_FieldOBJDraw_BlAct00 },
	{ DOOR2, &DATA_FieldOBJDraw_Model00Door2 },
	
	{ OBJCODEMAX, NULL },	//終端
};

//==============================================================================
//	フィールドOBJ レンダOBJまとめ
//==============================================================================
//--------------------------------------------------------------
///	レンダリングOBJデータ
//--------------------------------------------------------------
const FIELD_OBJ_RESMNARC DATA_FieldOBJ_ResmNArcTbl_RenderOBJ[] =
{
	{ BOARD_A, NARC_mmodel_board_a_nsbmd },
	{ BOARD_B, NARC_mmodel_board_b_nsbmd },
	{ BOARD_C, NARC_mmodel_board_c_nsbmd },
	{ BOARD_D, NARC_mmodel_board_d_nsbmd },
	{ BOARD_E, NARC_mmodel_board_e_nsbmd },
	{ BOARD_F, NARC_mmodel_board_f_nsbmd },
	{ SNOWBALL, NARC_mmodel_gym06_o1_nsbmd },
	
	{ OBJCODEMAX, 0 },	//終端
};

#define FIELD_OBJ_RENDER_MAX (NELEMS(DATA_FieldOBJ_ResmNArcTbl_RenderOBJ))

//--------------------------------------------------------------
///	レンダリングOBJ総数
//--------------------------------------------------------------
const int DATA_FIELDOBJ_RenderOBJMax = FIELD_OBJ_RENDER_MAX - 1;

//==============================================================================
//	フィールドOBJ テクスチャまとめ
//==============================================================================
//--------------------------------------------------------------
///	テクスチャID,アーカイブID
///	並びは不順
//--------------------------------------------------------------
const FIELD_OBJ_RESMNARC DATA_FieldOBJ_ResmNArcTbl_Tex[] =
{
	{ HERO, NARC_mmodel_hero_nsbtx },
	{ BABYBOY1, NARC_mmodel_babyboy1_nsbtx },
	{ BABYGIRL1, NARC_mmodel_babygirl1_nsbtx },
	{ BOY1, NARC_mmodel_boy1_nsbtx },
	{ BOY2, NARC_mmodel_boy2_nsbtx },
	{ BOY3, NARC_mmodel_boy3_nsbtx },
	{ GIRL1, NARC_mmodel_girl1_nsbtx },
	{ GIRL2, NARC_mmodel_girl2_nsbtx },
	{ GIRL3, NARC_mmodel_girl3_nsbtx },
	{ MAN1, NARC_mmodel_man1_nsbtx },
	{ MAN2, NARC_mmodel_man2_nsbtx },
	{ MAN3, NARC_mmodel_man3_nsbtx },
	{ WOMAN1, NARC_mmodel_woman1_nsbtx },
	{ WOMAN2, NARC_mmodel_woman2_nsbtx },
	{ WOMAN3, NARC_mmodel_woman3_nsbtx },
	{ MIDDLEMAN1, NARC_mmodel_middleman1_nsbtx },
	{ MIDDLEWOMAN1, NARC_mmodel_middlewoman1_nsbtx },
	{ OLDMAN1, NARC_mmodel_oldman1_nsbtx },
	{ OLDWOMAN1, NARC_mmodel_oldwoman1_nsbtx },
	{ BIGMAN, NARC_mmodel_bigman_nsbtx },
	{ MOUNT, NARC_mmodel_mount_nsbtx },
	{ CYCLEHERO, NARC_mmodel_cyclehero_nsbtx },
	{ REPORTER, NARC_mmodel_reporter_nsbtx },
	{ CAMERAMAN,NARC_mmodel_cameraman_nsbtx  },
	{ SHOPM1, NARC_mmodel_shopm1_nsbtx },
	{ SHOPW1, NARC_mmodel_shopw1_nsbtx },
	{ PCWOMAN1, NARC_mmodel_pcwoman1_nsbtx },
	{ PCWOMAN2, NARC_mmodel_pcwoman2_nsbtx },
	{ PCWOMAN3, NARC_mmodel_pcwoman3_nsbtx },
	{ ASSISTANTM, NARC_mmodel_assistantm_nsbtx },
	{ ASSISTANTW, NARC_mmodel_assistantw_nsbtx },
	{ BADMAN, NARC_mmodel_badman_nsbtx },
	{ SKIERM,NARC_mmodel_skierm_nsbtx  },
	{ SKIERW, NARC_mmodel_skierw_nsbtx },
	{ POLICEMAN, NARC_mmodel_policeman_nsbtx },
	{ IDOL, NARC_mmodel_idol_nsbtx },
	{ GENTLEMAN, NARC_mmodel_gentleman_nsbtx },
	{ LADY, NARC_mmodel_lady_nsbtx },
	{ CYCLEM, NARC_mmodel_cyclem_nsbtx },
	{ CYCLEW, NARC_mmodel_cyclew_nsbtx },
	{ WORKMAN, NARC_mmodel_workman_nsbtx },
	{ FARMER, NARC_mmodel_farmer_nsbtx },
	{ COWGIRL, NARC_mmodel_cowgirl_nsbtx },
	{ CLOWN, NARC_mmodel_clown_nsbtx },
	{ ARTIST, NARC_mmodel_artist_nsbtx },
	{ SPORTSMAN, NARC_mmodel_sportsman_nsbtx },
	{ SWIMMERM,NARC_mmodel_swimmerm_nsbtx  },
	{ SWIMMERW, NARC_mmodel_swimmerw_nsbtx },
	{ BEACHGIRL, NARC_mmodel_beachgirl_nsbtx },
	{ BEACHBOY, NARC_mmodel_beachboy_nsbtx },
	{ EXPLORE, NARC_mmodel_explore_nsbtx },
	{ FIGHTER, NARC_mmodel_fighter_nsbtx },
	{ CAMPBOY, NARC_mmodel_campboy_nsbtx },
	{ PICNICGIRL, NARC_mmodel_picnicgirl_nsbtx },
	{ FISHING, NARC_mmodel_fishing_nsbtx },
	{ AMBRELLA, NARC_mmodel_ambrella_nsbtx },
	{ SEAMAN,NARC_mmodel_seaman_nsbtx  },
	{ BRINGM, NARC_mmodel_bringm_nsbtx },
	{ BRINGW, NARC_mmodel_bringw_nsbtx },
	{ WAITER, NARC_mmodel_waiter_nsbtx },
	{ WAITRESS, NARC_mmodel_waitress_nsbtx },
	{ VETERAN, NARC_mmodel_veteran_nsbtx },
	{ GORGGEOUSM, NARC_mmodel_gorggeousm_nsbtx },
	{ GORGGEOUSW, NARC_mmodel_gorggeousw_nsbtx },
	{ BOY4,NARC_mmodel_boy4_nsbtx  },
	{ GIRL4, NARC_mmodel_girl4_nsbtx },
	{ MAN4, NARC_mmodel_man4_nsbtx },
	{ WOMAN4,NARC_mmodel_woman4_nsbtx  },
	{ MAN5, NARC_mmodel_man5_nsbtx },
	{ WOMAN5, NARC_mmodel_woman5_nsbtx },
	{ MYSTERY, NARC_mmodel_mystery_nsbtx },
	{ PIKACHU, NARC_mmodel_pikachu_nsbtx },
	{ PIPPI,NARC_mmodel_pippi_nsbtx  },
	{ PURIN, NARC_mmodel_purin_nsbtx },
	{ KODUCK, NARC_mmodel_koduck_nsbtx },
	{ PRASLE, NARC_mmodel_prasle_nsbtx },
	{ MINUN, NARC_mmodel_minun_nsbtx },
	{ MARIL,NARC_mmodel_maril_nsbtx  },
	{ ACHAMO, NARC_mmodel_achamo_nsbtx },
	{ ENECO,NARC_mmodel_eneco_nsbtx  },
	{ GONBE, NARC_mmodel_gonbe_nsbtx },
	{ BABY, NARC_mmodel_baby_nsbtx },
	{ MIDDLEMAN2, NARC_mmodel_middleman2_nsbtx },
	{ MIDDLEWOMAN2,NARC_mmodel_middlewoman2_nsbtx  },
	{ ROCK, NARC_mmodel_rock_nsbtx },
	{ BREAKROCK, NARC_mmodel_breakrock_nsbtx },
	{ TREE, NARC_mmodel_tree_nsbtx },
	{ MONATERBALL, NARC_mmodel_monaterball_nsbtx },
	{ SHADOW, NARC_mmodel_shadow_nsbtx },
	{ BOUGH, NARC_mmodel_bough_nsbtx },
	{ FALLTREE, NARC_mmodel_falltree_nsbtx },
	{ HEROINE, NARC_mmodel_heroine_nsbtx },
	{ CYCLEHEROINE, NARC_mmodel_cycleheroine_nsbtx },
	{ DOCTOR, NARC_mmodel_doctor_nsbtx },
	{ SEED00, NARC_mmodel_seed00_a_nsbtx },
	{ SEED01A, NARC_mmodel_seed01_a_nsbtx },
	{ SEED01B, NARC_mmodel_seed01_b_nsbtx },
	{ SEED01C, NARC_mmodel_seed01_c_nsbtx },
	{ GINGABOSS,NARC_mmodel_gingaboss_nsbtx }, 
	{ GKANBU1,NARC_mmodel_gkanbu1_nsbtx }, 
	{ GKANBU2,NARC_mmodel_gkanbu2_nsbtx }, 
	{ GKANBU3,NARC_mmodel_gkanbu3_nsbtx }, 
	{ GINGAM,NARC_mmodel_gingam_nsbtx }, 
	{ GINGAW,NARC_mmodel_gingaw_nsbtx }, 
	{ LEADER1,NARC_mmodel_leader1_nsbtx }, 
	{ LEADER2,NARC_mmodel_leader2_nsbtx }, 
	{ LEADER3,NARC_mmodel_leader3_nsbtx }, 
	{ LEADER4,NARC_mmodel_leader4_nsbtx }, 
	{ LEADER5,NARC_mmodel_leader5_nsbtx }, 
	{ LEADER6,NARC_mmodel_leader6_nsbtx }, 
	{ LEADER7,NARC_mmodel_leader7_nsbtx }, 
	{ LEADER8,NARC_mmodel_leader8_nsbtx }, 
	{ BIGFOUR1,NARC_mmodel_bigfour1_nsbtx }, 
	{ BIGFOUR2,NARC_mmodel_bigfour2_nsbtx }, 
	{ BIGFOUR3,NARC_mmodel_bigfour3_nsbtx }, 
	{ BIGFOUR4,NARC_mmodel_bigfour4_nsbtx }, 
	{ CHAMPION,NARC_mmodel_champion_nsbtx }, 
	{ PAPA,NARC_mmodel_papa_nsbtx }, 
	{ MAMA,NARC_mmodel_mama_nsbtx }, 
	{ SEVEN1,NARC_mmodel_seven1_nsbtx }, 
	{ SEVEN2,NARC_mmodel_seven2_nsbtx }, 
	{ SEVEN3,NARC_mmodel_seven3_nsbtx }, 
	{ SEVEN4,NARC_mmodel_seven4_nsbtx }, 
	{ SEVEN5,NARC_mmodel_seven5_nsbtx }, 
	{ SEVEN6,NARC_mmodel_seven6_nsbtx }, 
	{ SEVEN7,NARC_mmodel_seven7_nsbtx }, 
	{ RIVEL,NARC_mmodel_rivel_nsbtx }, 
	{ BOAT,NARC_mmodel_boat_nsbtx }, 
	{ TRAIN,NARC_mmodel_train_nsbtx }, 
	{ SPPOKE1,NARC_mmodel_sppoke1_nsbtx }, 
	{ SPPOKE2,NARC_mmodel_sppoke2_nsbtx }, 
	{ SPPOKE3,NARC_mmodel_sppoke3_nsbtx }, 
	{ SPPOKE4,NARC_mmodel_sppoke4_nsbtx }, 
	{ SPPOKE5,NARC_mmodel_sppoke5_nsbtx }, 
	{ SPPOKE6,NARC_mmodel_sppoke6_nsbtx }, 
	{ SPPOKE7,NARC_mmodel_sppoke7_nsbtx }, 
	{ SPPOKE8,NARC_mmodel_sppoke8_nsbtx }, 
	{ SPPOKE9,NARC_mmodel_sppoke9_nsbtx }, 
	{ SPPOKE10,NARC_mmodel_sppoke10_nsbtx }, 
	{ SPPOKE11,NARC_mmodel_sppoke11_nsbtx }, 
	{ OBAKE,NARC_mmodel_obake_nsbtx }, 
	{ WOMAN6,NARC_mmodel_woman6_nsbtx }, 
	{ OLDMAN2,NARC_mmodel_oldman2_nsbtx }, 
	{ OLDWOMAN2,NARC_mmodel_oldwoman2_nsbtx }, 
	{ OOKIDO,NARC_mmodel_ookido_nsbtx }, 
	{ MIKAN,NARC_mmodel_mikan_nsbtx }, 
	{ SUNGLASSES,NARC_mmodel_sunglasses_nsbtx }, 
	{ TOWERBOSS,NARC_mmodel_towerboss_nsbtx }, 
	{ SNOWCOVER,NARC_mmodel_snowcover_nsbtx }, 
	{ TREECOVER,NARC_mmodel_treecover_nsbtx }, 
	{ ROCKCOVER,NARC_mmodel_rockcover_nsbtx }, 
	{ BIRD,NARC_mmodel_bird_nsbtx }, 
	{ BAG,NARC_mmodel_bag_nsbtx }, 
	{ MAID,NARC_mmodel_maid_nsbtx }, 
	{ SPHERO, NARC_mmodel_sphero_nsbtx },
	{ SPHEROINE, NARC_mmodel_spheroine_nsbtx },
	{ WATERHERO, NARC_mmodel_waterhero_nsbtx },
	{ WATERHEROINE, NARC_mmodel_waterheroine_nsbtx },
	{ SWIMHERO, NARC_mmodel_swimhero_nsbtx },
	{ SWIMHEROINE, NARC_mmodel_swimheroine_nsbtx },
	{ VENTHOLE, NARC_mmodel_venthole_nsbtx },
	{ SPPOKE12, NARC_mmodel_sppoke12_nsbtx },
	{ BALLOON, NARC_mmodel_balloon_nsbtx },
	{ CONTESTHERO, NARC_mmodel_contesthero_nsbtx },
	{ CONTESTHEROINE, NARC_mmodel_cont_heroine_nsbtx },
	{ FISHINGHERO, NARC_mmodel_fishinghero_nsbtx },
	{ FISHINGHEROINE, NARC_mmodel_fish_heroine_nsbtx },
	{ MOSS, NARC_mmodel_moss_nsbtx },
	{ FREEZES, NARC_mmodel_freezes_nsbtx },
	{ POLE, NARC_mmodel_pole_nsbtx },
	{ SEED02A, NARC_mmodel_seed02_a_nsbtx },
	{ SEED02B, NARC_mmodel_seed02_b_nsbtx },
	{ SEED02C, NARC_mmodel_seed02_c_nsbtx },
	{ SEED03A, NARC_mmodel_seed03_a_nsbtx },
	{ SEED03B, NARC_mmodel_seed03_b_nsbtx },
	{ SEED03C, NARC_mmodel_seed03_c_nsbtx },
	{ SEED04A, NARC_mmodel_seed04_a_nsbtx },
	{ SEED04B, NARC_mmodel_seed04_b_nsbtx },
	{ SEED04C, NARC_mmodel_seed04_c_nsbtx },
	{ SEED05A, NARC_mmodel_seed05_a_nsbtx },
	{ SEED05B, NARC_mmodel_seed05_b_nsbtx },
	{ SEED05C, NARC_mmodel_seed05_c_nsbtx },
	{ SEED06A, NARC_mmodel_seed06_a_nsbtx },
	{ SEED06B, NARC_mmodel_seed06_b_nsbtx },
	{ SEED06C, NARC_mmodel_seed06_c_nsbtx },
	{ SEED07A, NARC_mmodel_seed07_a_nsbtx },
	{ SEED07B, NARC_mmodel_seed07_b_nsbtx },
	{ SEED07C, NARC_mmodel_seed07_c_nsbtx },
	{ SEED08A, NARC_mmodel_seed08_a_nsbtx },
	{ SEED08B, NARC_mmodel_seed08_b_nsbtx },
	{ SEED08C, NARC_mmodel_seed08_c_nsbtx },
	{ SEED09A, NARC_mmodel_seed09_a_nsbtx },
	{ SEED09B, NARC_mmodel_seed09_b_nsbtx },
	{ SEED09C, NARC_mmodel_seed09_c_nsbtx },
	{ SEED10A, NARC_mmodel_seed10_a_nsbtx },
	{ SEED10B, NARC_mmodel_seed10_b_nsbtx },
	{ SEED10C, NARC_mmodel_seed10_c_nsbtx },
	{ SEED11A, NARC_mmodel_seed11_a_nsbtx },
	{ SEED11B, NARC_mmodel_seed11_b_nsbtx },
	{ SEED11C, NARC_mmodel_seed11_c_nsbtx },
	{ SEED12A, NARC_mmodel_seed12_a_nsbtx },
	{ SEED12B, NARC_mmodel_seed12_b_nsbtx },
	{ SEED12C, NARC_mmodel_seed12_c_nsbtx },
	{ SEED13A, NARC_mmodel_seed13_a_nsbtx },
	{ SEED13B, NARC_mmodel_seed13_b_nsbtx },
	{ SEED13C, NARC_mmodel_seed13_c_nsbtx },
	{ SEED14A, NARC_mmodel_seed14_a_nsbtx },
	{ SEED14B, NARC_mmodel_seed14_b_nsbtx },
	{ SEED14C, NARC_mmodel_seed14_c_nsbtx },
	{ SEED15A, NARC_mmodel_seed15_a_nsbtx },
	{ SEED15B, NARC_mmodel_seed15_b_nsbtx },
	{ SEED15C, NARC_mmodel_seed15_c_nsbtx },
	{ SEED16A, NARC_mmodel_seed16_a_nsbtx },
	{ SEED16B, NARC_mmodel_seed16_b_nsbtx },
	{ SEED16C, NARC_mmodel_seed16_c_nsbtx },
	{ SEED17A, NARC_mmodel_seed17_a_nsbtx },
	{ SEED17B, NARC_mmodel_seed17_b_nsbtx },
	{ SEED17C, NARC_mmodel_seed17_c_nsbtx },
	{ SEED18A, NARC_mmodel_seed18_a_nsbtx },
	{ SEED18B, NARC_mmodel_seed18_b_nsbtx },
	{ SEED18C, NARC_mmodel_seed18_c_nsbtx },
	{ SEED19A, NARC_mmodel_seed19_a_nsbtx },
	{ SEED19B, NARC_mmodel_seed19_b_nsbtx },
	{ SEED19C, NARC_mmodel_seed19_c_nsbtx },
	{ SEED20A, NARC_mmodel_seed20_a_nsbtx },
	{ SEED20B, NARC_mmodel_seed20_b_nsbtx },
	{ SEED20C, NARC_mmodel_seed20_c_nsbtx },
	{ SEED21A, NARC_mmodel_seed21_a_nsbtx },
	{ SEED21B, NARC_mmodel_seed21_b_nsbtx },
	{ SEED21C, NARC_mmodel_seed21_c_nsbtx },
	{ SEED22A, NARC_mmodel_seed22_a_nsbtx },
	{ SEED22B, NARC_mmodel_seed22_b_nsbtx },
	{ SEED22C, NARC_mmodel_seed22_c_nsbtx },
	{ SEED23A, NARC_mmodel_seed23_a_nsbtx },
	{ SEED23B, NARC_mmodel_seed23_b_nsbtx },
	{ SEED23C, NARC_mmodel_seed23_c_nsbtx },
	{ SEED24A, NARC_mmodel_seed24_a_nsbtx },
	{ SEED24B, NARC_mmodel_seed24_b_nsbtx },
	{ SEED24C, NARC_mmodel_seed24_c_nsbtx },
	{ SEED25A, NARC_mmodel_seed25_a_nsbtx },
	{ SEED25B, NARC_mmodel_seed25_b_nsbtx },
	{ SEED25C, NARC_mmodel_seed25_c_nsbtx },
	{ SEED26A, NARC_mmodel_seed26_a_nsbtx },
	{ SEED26B, NARC_mmodel_seed26_b_nsbtx },
	{ SEED26C, NARC_mmodel_seed26_c_nsbtx },
	{ SEED27A, NARC_mmodel_seed27_a_nsbtx },
	{ SEED27B, NARC_mmodel_seed27_b_nsbtx },
	{ SEED27C, NARC_mmodel_seed27_c_nsbtx },
	{ SEED28A, NARC_mmodel_seed28_a_nsbtx },
	{ SEED28B, NARC_mmodel_seed28_b_nsbtx },
	{ SEED28C, NARC_mmodel_seed28_c_nsbtx },
	{ SEED29A, NARC_mmodel_seed29_a_nsbtx },
	{ SEED29B, NARC_mmodel_seed29_b_nsbtx },
	{ SEED29C, NARC_mmodel_seed29_c_nsbtx },
	{ SEED30A, NARC_mmodel_seed30_a_nsbtx },
	{ SEED30B, NARC_mmodel_seed30_b_nsbtx },
	{ SEED30C, NARC_mmodel_seed30_c_nsbtx },
	{ SEED31A, NARC_mmodel_seed31_a_nsbtx },
	{ SEED31B, NARC_mmodel_seed31_b_nsbtx },
	{ SEED31C, NARC_mmodel_seed31_c_nsbtx },
	{ SEED32A, NARC_mmodel_seed32_a_nsbtx },
	{ SEED32B, NARC_mmodel_seed32_b_nsbtx },
	{ SEED32C, NARC_mmodel_seed32_c_nsbtx },
	{ SEED33A, NARC_mmodel_seed33_a_nsbtx },
	{ SEED33B, NARC_mmodel_seed33_b_nsbtx },
	{ SEED33C, NARC_mmodel_seed33_c_nsbtx },
	{ SEED34A, NARC_mmodel_seed34_a_nsbtx },
	{ SEED34B, NARC_mmodel_seed34_b_nsbtx },
	{ SEED34C, NARC_mmodel_seed34_c_nsbtx },
	{ SEED35A, NARC_mmodel_seed35_a_nsbtx },
	{ SEED35B, NARC_mmodel_seed35_b_nsbtx },
	{ SEED35C, NARC_mmodel_seed35_c_nsbtx },
	{ SEED36A, NARC_mmodel_seed36_a_nsbtx },
	{ SEED36B, NARC_mmodel_seed36_b_nsbtx },
	{ SEED36C, NARC_mmodel_seed36_c_nsbtx },
	{ SEED37A, NARC_mmodel_seed37_a_nsbtx },
	{ SEED37B, NARC_mmodel_seed37_b_nsbtx },
	{ SEED37C, NARC_mmodel_seed37_c_nsbtx },
	{ SEED38A, NARC_mmodel_seed38_a_nsbtx },
	{ SEED38B, NARC_mmodel_seed38_b_nsbtx },
	{ SEED38C, NARC_mmodel_seed38_c_nsbtx },
	{ SEED39A, NARC_mmodel_seed39_a_nsbtx },
	{ SEED39B, NARC_mmodel_seed39_b_nsbtx },
	{ SEED39C, NARC_mmodel_seed39_c_nsbtx },
	{ SEED40A, NARC_mmodel_seed40_a_nsbtx },
	{ SEED40B, NARC_mmodel_seed40_b_nsbtx },
	{ SEED40C, NARC_mmodel_seed40_c_nsbtx },
	{ SEED41A, NARC_mmodel_seed41_a_nsbtx },
	{ SEED41B, NARC_mmodel_seed41_b_nsbtx },
	{ SEED41C, NARC_mmodel_seed41_c_nsbtx },
	{ SEED42A, NARC_mmodel_seed42_a_nsbtx },
	{ SEED42B, NARC_mmodel_seed42_b_nsbtx },
	{ SEED42C, NARC_mmodel_seed42_c_nsbtx },
	{ SEED43A, NARC_mmodel_seed43_a_nsbtx },
	{ SEED43B, NARC_mmodel_seed43_b_nsbtx },
	{ SEED43C, NARC_mmodel_seed43_c_nsbtx },
	{ SEED44A, NARC_mmodel_seed44_a_nsbtx },
	{ SEED44B, NARC_mmodel_seed44_b_nsbtx },
	{ SEED44C, NARC_mmodel_seed44_c_nsbtx },
	{ SEED45A, NARC_mmodel_seed45_a_nsbtx },
	{ SEED45B, NARC_mmodel_seed45_b_nsbtx },
	{ SEED45C, NARC_mmodel_seed45_c_nsbtx },
	{ SEED46A, NARC_mmodel_seed46_a_nsbtx },
	{ SEED46B, NARC_mmodel_seed46_b_nsbtx },
	{ SEED46C, NARC_mmodel_seed46_c_nsbtx },
	{ SEED47A, NARC_mmodel_seed47_a_nsbtx },
	{ SEED47B, NARC_mmodel_seed47_b_nsbtx },
	{ SEED47C, NARC_mmodel_seed47_c_nsbtx },
	{ SEED48A, NARC_mmodel_seed48_a_nsbtx },
	{ SEED48B, NARC_mmodel_seed48_b_nsbtx },
	{ SEED48C, NARC_mmodel_seed48_c_nsbtx },
	{ SEED49A, NARC_mmodel_seed49_a_nsbtx },
	{ SEED49B, NARC_mmodel_seed49_b_nsbtx },
	{ SEED49C, NARC_mmodel_seed49_c_nsbtx },
	{ SEED50A, NARC_mmodel_seed50_a_nsbtx },
	{ SEED50B, NARC_mmodel_seed50_b_nsbtx },
	{ SEED50C, NARC_mmodel_seed50_c_nsbtx },
	{ SEED51A, NARC_mmodel_seed51_a_nsbtx },
	{ SEED51B, NARC_mmodel_seed51_b_nsbtx },
	{ SEED51C, NARC_mmodel_seed51_c_nsbtx },
	{ SEED52A, NARC_mmodel_seed52_a_nsbtx },
	{ SEED52B, NARC_mmodel_seed52_b_nsbtx },
	{ SEED52C, NARC_mmodel_seed52_c_nsbtx },
	{ SEED53A, NARC_mmodel_seed53_a_nsbtx },
	{ SEED53B, NARC_mmodel_seed53_b_nsbtx },
	{ SEED53C, NARC_mmodel_seed53_c_nsbtx },
	{ SEED54A, NARC_mmodel_seed54_a_nsbtx },
	{ SEED54B, NARC_mmodel_seed54_b_nsbtx },
	{ SEED54C, NARC_mmodel_seed54_c_nsbtx },
	{ SEED55A, NARC_mmodel_seed55_a_nsbtx },
	{ SEED55B, NARC_mmodel_seed55_b_nsbtx },
	{ SEED55C, NARC_mmodel_seed55_c_nsbtx },
	{ SEED56A, NARC_mmodel_seed56_a_nsbtx },
	{ SEED56B, NARC_mmodel_seed56_b_nsbtx },
	{ SEED56C, NARC_mmodel_seed56_c_nsbtx },
	{ SEED57A, NARC_mmodel_seed57_a_nsbtx },
	{ SEED57B, NARC_mmodel_seed57_b_nsbtx },
	{ SEED57C, NARC_mmodel_seed57_c_nsbtx },
	{ SEED58A, NARC_mmodel_seed58_a_nsbtx },
	{ SEED58B, NARC_mmodel_seed58_b_nsbtx },
	{ SEED58C, NARC_mmodel_seed58_c_nsbtx },
	{ SEED59A, NARC_mmodel_seed59_a_nsbtx },
	{ SEED59B, NARC_mmodel_seed59_b_nsbtx },
	{ SEED59C, NARC_mmodel_seed59_c_nsbtx },
	{ SEED60A, NARC_mmodel_seed60_a_nsbtx },
	{ SEED60B, NARC_mmodel_seed60_b_nsbtx },
	{ SEED60C, NARC_mmodel_seed60_c_nsbtx },
	{ SEED61A, NARC_mmodel_seed61_a_nsbtx },
	{ SEED61B, NARC_mmodel_seed61_b_nsbtx },
	{ SEED61C, NARC_mmodel_seed61_c_nsbtx },
	{ SEED62A, NARC_mmodel_seed62_a_nsbtx },
	{ SEED62B, NARC_mmodel_seed62_b_nsbtx },
	{ SEED62C, NARC_mmodel_seed62_c_nsbtx },
	{ SEED63A, NARC_mmodel_seed63_a_nsbtx },
	{ SEED63B, NARC_mmodel_seed63_b_nsbtx },
	{ SEED63C, NARC_mmodel_seed63_c_nsbtx },
	{ SEED64A, NARC_mmodel_seed64_a_nsbtx },
	{ SEED64B, NARC_mmodel_seed64_b_nsbtx },
	{ SEED64C, NARC_mmodel_seed64_c_nsbtx },
	{ DELIVERY, NARC_mmodel_delivery_nsbtx },
	{ DSBOY, NARC_mmodel_dsboy_nsbtx },
	{ KOIKING, NARC_mmodel_koiking_nsbtx },
	{ POKEHERO, NARC_mmodel_pokehero_nsbtx },
	{ POKEHEROINE, NARC_mmodel_pokeheroine_nsbtx },
	{ SAVEHERO, NARC_mmodel_savehero_nsbtx },
	{ SAVEHEROINE, NARC_mmodel_saveheroine_nsbtx },
	{ BANZAIHERO, NARC_mmodel_banzaihero_nsbtx },
	{ BANZAIHEROINE, NARC_mmodel_banzaiheroine_nsbtx },
	{ DOOR, NARC_mmodel_door_nsbtx },
	{ MONUMENT, NARC_mmodel_monument_nsbtx },
	{ PATIRITUSU, NARC_mmodel_patiritusu_nsbtx },
	{ KINOCOCO, NARC_mmodel_kinococo_nsbtx },
	{ MIMITUTO, NARC_mmodel_mimituto_nsbtx },
	{ KOLUCKY, NARC_mmodel_kolucky_nsbtx },
	{ WANRIKY, NARC_mmodel_wanriky_nsbtx },
	
	{ OBJCODEMAX, 0 },
};

//==============================================================================
//	フィールドOBJ モデルまとめ
//==============================================================================
//--------------------------------------------------------------
///	モデルID,パステーブル。
///	並びは不順
//--------------------------------------------------------------
const FIELD_OBJ_RESMNARC DATA_FieldOBJ_ResmNArcTbl_Mdl[] =
{
	{ BLACT_MDLID_32x32,NARC_mmodel_billboad_nsbmd },
	{ BLACT_MDLID_16x16, NARC_mmodel_rock_nsbmd },
	{ BLACT_MDLID_16x16_1, NARC_mmodel_breakrock_nsbmd },
	{ BLACT_MDLID_SEED_ME, NARC_mmodel_seed00_a_nsbmd },
	{ BLACT_MDLID_SEED, NARC_mmodel_seed01_a_nsbmd },
	{ BLACT_MDLID_64x64, NARC_mmodel_sppoke4_nsbmd },
	{ BLACT_MDLID_FISHINGHERO, NARC_mmodel_fishinghero_nsbmd },
	{ BLACT_MDLID_16x32, NARC_mmodel_door_nsbmd },
	{ BLACT_MDLID_64x32, NARC_mmodel_monument_nsbmd },
	{ BLACT_MDLID_MAX, 0 },
};

//==============================================================================
//	フィールドOBJ アニメまとめ
//==============================================================================
//--------------------------------------------------------------
///	アニメID,パステーブル。
///	並びは不順
//--------------------------------------------------------------
const FIELD_OBJ_RESMNARC DATA_FieldOBJ_ResmNArcTbl_Anm[] =
{
	{ BLACT_ANMID_NORMAL_0, NARC_mmodel_charaobj_itpcv_dat },
	{ BLACT_ANMID_HERO_0, NARC_mmodel_hero_itpcv_dat },
	{ BLACT_ANMID_SEED, NARC_mmodel_seed00_a_itpcv_dat },
	{ BLACT_ANMID_HEROCYCLE_0, NARC_mmodel_cyclehero_itpcv_dat },
	{ BLACT_ANMID_SPHERO, NARC_mmodel_sphero_itpcv_dat },
	{ BLACT_ANMID_WATERHERO, NARC_mmodel_waterhero_itpcv_dat },
	{ BLACT_ANMID_SWIMHERO, NARC_mmodel_swimhero_itpcv_dat },
	{ BLACT_ANMID_BIRD,	NARC_mmodel_bird_itpcv_dat },
	{ BLACT_ANMID_SPPOKE,	NARC_mmodel_sppoke_itpcv_dat },
	{ BLACT_ANMID_CONTESTHERO, NARC_mmodel_contesthero_itpcv_dat },
	{ BLACT_ANMID_FISHINGHERO, NARC_mmodel_fishinghero_itpcv_dat },
	{ BLACT_ANMID_PCWOMAN, NARC_mmodel_pcwoman1_itpcv_dat },
	{ BLACT_ANMID_KOIKING, NARC_mmodel_koiking_itpcv_dat },
	{ BLACT_ANMID_POKEHERO, NARC_mmodel_pokehero_itpcv_dat },
	{ BLACT_ANMID_SAVEHERO, NARC_mmodel_savehero_itpcv_dat },
	{ BLACT_ANMID_BANZAIHERO, NARC_mmodel_banzaihero_itpcv_dat },
	{ BLACT_ANMID_SPPOKE6, NARC_mmodel_sppoke6_itpcv_dat },
	{ BLACT_ANMID_SPPOKE7, NARC_mmodel_sppoke7_itpcv_dat },
	{ BLACT_ANMID_SPPOKE9, NARC_mmodel_sppoke9_itpcv_dat },
	{ BLACT_ANMID_SPPOKE10, NARC_mmodel_sppoke10_itpcv_dat },
	{ BLACT_ANMID_SPPOKE11, NARC_mmodel_sppoke11_itpcv_dat },
	
	{ BLACT_ANMID_MAX, 0 },
};

//==============================================================================
//	フィールドOBJ アニメーションテーブル
//==============================================================================
//--------------------------------------------------------------
///	自機
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_Hero[] =
{
	{ 0, 15, BLACT_ANIM_LOOP },
	{ 16, 31, BLACT_ANIM_LOOP },
	{ 32, 47, BLACT_ANIM_LOOP },
	{ 48, 63, BLACT_ANIM_LOOP },
	
	{ 64, 79, BLACT_ANIM_LOOP },	//ダッシュ
	{ 80, 95, BLACT_ANIM_LOOP },
	{ 96, 111, BLACT_ANIM_LOOP },
	{ 112, 127, BLACT_ANIM_LOOP },
	
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	自機自転車
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_HeroCycle[] =
{
	{ 0, 15, BLACT_ANIM_LOOP },
	{ 16, 31, BLACT_ANIM_LOOP },
	{ 32, 47, BLACT_ANIM_LOOP },
	{ 48, 63, BLACT_ANIM_LOOP },
	
	{ 64, 71, BLACT_ANIM_LOOP },
	{ 72, 79, BLACT_ANIM_LOOP },
	
	{ 80, 83, BLACT_ANIM_END },
	{ 84, 87, BLACT_ANIM_END },
	{ 88, 91, BLACT_ANIM_END },
	{ 92, 95, BLACT_ANIM_END },
	
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	自機波乗り
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_SwimHero[] =
{
	{ 0, 2, BLACT_ANIM_LOOP },
	{ 3, 5, BLACT_ANIM_LOOP },
	{ 6, 9, BLACT_ANIM_LOOP },
	{ 10, 11, BLACT_ANIM_LOOP },
	
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	自機秘伝技
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_SpHero[] =
{
	{ 0, 10, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	自機水遣り
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_WaterHero[] =
{
	{ 0, 15, BLACT_ANIM_LOOP },
	{ 16, 28, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	村人普通 0
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_Normal0[] =
{
	{ 0, 15, BLACT_ANIM_LOOP },
	{ 16, 31, BLACT_ANIM_LOOP },
	{ 32, 47, BLACT_ANIM_LOOP },
	{ 48, 63, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	PCWOMAN 1
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_PcWoman[] =
{
	{ 0, 15, BLACT_ANIM_LOOP },
	{ 16, 31, BLACT_ANIM_LOOP },
	{ 32, 47, BLACT_ANIM_LOOP },
	{ 48, 63, BLACT_ANIM_LOOP },
	
	{ 64, 68, BLACT_ANIM_END},
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	木の実
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_Seed0[] =
{
	{ 0, 60, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	鳥
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_Bird[] =
{
	{ 0, 7, BLACT_ANIM_LOOP },
	{ 8, 16, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
//	@autor	tomoya takahashi
///	伝説ポケモン	イア　エア
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_Legend[] =
{
	{ 0, 16, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
//	@autor	tomoya takahashi
///	伝説ポケモン	レイアイハイ
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_ReiAiHai[] =
{
	{ 0, 16, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	釣り自機
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_FishingHero[] =
{
	{ 0, 15, BLACT_ANIM_END },
	{ 16, 31, BLACT_ANIM_END },
	{ 32, 47, BLACT_ANIM_END },
	{ 48, 64, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	コイキング
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_Koiking[] =
{
	{ 0, 32, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	POKEHERO
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_PokeHero[] =
{
	{ 0, 11, BLACT_ANIM_END },
	{ 12, 23, BLACT_ANIM_END },
	{ 24, 35, BLACT_ANIM_END },
	{ 36, 48, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	SAVEHERO
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_SaveHero[] =
{
	{ 0, 8, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	BANZAIHERO
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_BanzaiHero[] =
{
	{ 0, 20, BLACT_ANIM_END },
	{ 21, 41, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
/// SPPOKE
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_FieldOBJ_BlActAnmTbl_Sppoke[] =
{
	{ 0, 20, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//==============================================================================
//	フィールドOBJ リソースIDまとめ
//==============================================================================

//==============================================================================
//	フィールドOBJ レギュラー勢
//==============================================================================
//--------------------------------------------------------------
///	テクスチャ　レギュラー
//--------------------------------------------------------------
const int DATA_FieldOBJ_Regular_Tex[] =
{
	BABYBOY1,
	BABYGIRL1,
	BOY1,
	BOY2,
	BOY3,
	GIRL1,
	GIRL2,
	GIRL3,
	MAN1,
	MAN2,
	MAN3,
	WOMAN1,
	WOMAN2,
	WOMAN3,
	MIDDLEMAN1,
	MIDDLEWOMAN1,
	OLDMAN1,
	OLDWOMAN1,
	BIGMAN,
	MOUNT,
	
	OBJCODEMAX,
};

//--------------------------------------------------------------
///	モデル　レギュラー
//--------------------------------------------------------------
const int DATA_FieldOBJ_Regular_Mdl[] =
{
	BLACT_MDLID_32x32,
	BLACT_MDLID_16x16,
	BLACT_MDLID_16x16_1,
	BLACT_MDLID_MAX,
};

//--------------------------------------------------------------
///	アニメ　レギュラー
//--------------------------------------------------------------
const int DATA_FieldOBJ_Regular_Anm[] =
{
	BLACT_ANMID_NORMAL_0,
	BLACT_ANMID_MAX,
};

//==============================================================================
//	フィールドOBJ ビルボードアクターヘッダー
//==============================================================================
//--------------------------------------------------------------
///	フィールドOBJ　ビルボードヘッダーパス、IDテーブル
///	並びはfieldobj_code.h 表示コードに準ず←やめた。不順
//--------------------------------------------------------------
const FIELD_OBJ_BLACT_HEADER_ID DATA_FieldOBJ_BlActHeaderPathIDTbl[] =
{
	{HERO,BLACT_MDLID_32x32,BLACT_ANMID_HERO_0,DATA_FieldOBJ_BlActAnmTbl_Hero},
    {BABYBOY1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {BABYGIRL1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {BOY1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {BOY2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {BOY3,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {GIRL1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {GIRL2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {GIRL3,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {MAN1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {MAN2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {MAN3,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {WOMAN1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {WOMAN2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {WOMAN3,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {MIDDLEMAN1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {MIDDLEWOMAN1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {OLDMAN1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {OLDWOMAN1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {BIGMAN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {MOUNT,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
    {CYCLEHERO,BLACT_MDLID_32x32,BLACT_ANMID_HEROCYCLE_0,DATA_FieldOBJ_BlActAnmTbl_HeroCycle},
	{REPORTER,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{CAMERAMAN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SHOPM1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SHOPW1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{PCWOMAN1,BLACT_MDLID_32x32,BLACT_ANMID_PCWOMAN,DATA_FieldOBJ_BlActAnmTbl_PcWoman},
	{PCWOMAN2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{PCWOMAN3,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{ASSISTANTM,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{ASSISTANTW,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BADMAN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SKIERM,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SKIERW,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{POLICEMAN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{IDOL,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{GENTLEMAN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{LADY,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{CYCLEM,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{CYCLEW,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{WORKMAN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{FARMER,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{COWGIRL,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{CLOWN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{ARTIST,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SPORTSMAN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SWIMMERM,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SWIMMERW,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BEACHGIRL,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BEACHBOY,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{EXPLORE,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{FIGHTER,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{CAMPBOY,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{PICNICGIRL,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{FISHING,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{AMBRELLA,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SEAMAN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BRINGM,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BRINGW,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{WAITER,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{WAITRESS,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{VETERAN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{GORGGEOUSM,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{GORGGEOUSW,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BOY4,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{GIRL4,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MAN4,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{WOMAN4,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MAN5,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{WOMAN5,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MYSTERY,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{PIKACHU,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{PIPPI,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{PURIN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{KODUCK,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{PRASLE,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MINUN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MARIL,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{ACHAMO,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{ENECO,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{GONBE,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BABY,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MIDDLEMAN2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MIDDLEWOMAN2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{ROCK,BLACT_MDLID_16x16,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BREAKROCK,BLACT_MDLID_16x16_1,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{TREE,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MONATERBALL,BLACT_MDLID_16x16,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SHADOW,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BOUGH,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{FALLTREE,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{HEROINE,BLACT_MDLID_32x32,BLACT_ANMID_HERO_0,DATA_FieldOBJ_BlActAnmTbl_Hero},
    {CYCLEHEROINE,BLACT_MDLID_32x32,BLACT_ANMID_HEROCYCLE_0,DATA_FieldOBJ_BlActAnmTbl_HeroCycle},
	{DOCTOR,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SEED00,BLACT_MDLID_SEED_ME,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED01A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED01B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED01C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{GINGABOSS,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{GKANBU1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{GKANBU2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{GKANBU3,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{GINGAM,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{GINGAW,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{LEADER1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{LEADER2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{LEADER3,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{LEADER4,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{LEADER5,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{LEADER6,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{LEADER7,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{LEADER8,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BIGFOUR1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BIGFOUR2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BIGFOUR3,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BIGFOUR4,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{CHAMPION,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{PAPA,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MAMA,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SEVEN1,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SEVEN2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SEVEN3,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SEVEN4,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SEVEN5,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SEVEN6,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SEVEN7,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{RIVEL,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BOAT,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{TRAIN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SPPOKE1,BLACT_MDLID_32x32,BLACT_ANMID_SPPOKE,DATA_FieldOBJ_BlActAnmTbl_ReiAiHai},
	{SPPOKE2,BLACT_MDLID_32x32,BLACT_ANMID_SPPOKE,DATA_FieldOBJ_BlActAnmTbl_ReiAiHai},
	{SPPOKE3,BLACT_MDLID_32x32,BLACT_ANMID_SPPOKE,DATA_FieldOBJ_BlActAnmTbl_ReiAiHai},
	{SPPOKE4,BLACT_MDLID_64x64,BLACT_ANMID_SPPOKE,DATA_FieldOBJ_BlActAnmTbl_Legend},
	{SPPOKE5,BLACT_MDLID_64x64,BLACT_ANMID_SPPOKE,DATA_FieldOBJ_BlActAnmTbl_Legend},
	{SPPOKE6,BLACT_MDLID_64x64,BLACT_ANMID_SPPOKE6,DATA_FieldOBJ_BlActAnmTbl_Sppoke},
	{SPPOKE7,BLACT_MDLID_32x32,BLACT_ANMID_SPPOKE7,DATA_FieldOBJ_BlActAnmTbl_Sppoke},
	{SPPOKE8,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SPPOKE9,BLACT_MDLID_32x32,BLACT_ANMID_SPPOKE9,DATA_FieldOBJ_BlActAnmTbl_Sppoke},
	{SPPOKE10,BLACT_MDLID_64x64,BLACT_ANMID_SPPOKE10,DATA_FieldOBJ_BlActAnmTbl_Sppoke},
	{SPPOKE11,BLACT_MDLID_32x32,BLACT_ANMID_SPPOKE11,DATA_FieldOBJ_BlActAnmTbl_Sppoke},
	{OBAKE,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{WOMAN6,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{OLDMAN2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{OLDWOMAN2,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{OOKIDO,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MIKAN,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SUNGLASSES,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{TOWERBOSS,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SNOWCOVER,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{TREECOVER,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{ROCKCOVER,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BIRD,BLACT_MDLID_32x32,BLACT_ANMID_BIRD,DATA_FieldOBJ_BlActAnmTbl_Bird},
	{BAG,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MAID,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SPHERO,BLACT_MDLID_32x32,BLACT_ANMID_SPHERO,DATA_FieldOBJ_BlActAnmTbl_SpHero },
	{SPHEROINE,BLACT_MDLID_32x32,BLACT_ANMID_SPHERO,DATA_FieldOBJ_BlActAnmTbl_SpHero},
	{SWIMHERO,BLACT_MDLID_32x32,BLACT_ANMID_SWIMHERO,DATA_FieldOBJ_BlActAnmTbl_SwimHero},
	{SWIMHEROINE,BLACT_MDLID_32x32,BLACT_ANMID_SWIMHERO,DATA_FieldOBJ_BlActAnmTbl_SwimHero},
	{WATERHERO,BLACT_MDLID_32x32,BLACT_ANMID_WATERHERO,DATA_FieldOBJ_BlActAnmTbl_WaterHero},
	{WATERHEROINE,BLACT_MDLID_32x32,BLACT_ANMID_WATERHERO,DATA_FieldOBJ_BlActAnmTbl_WaterHero},
	{VENTHOLE,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SPPOKE12,BLACT_MDLID_64x64,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{BALLOON,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{CONTESTHERO,BLACT_MDLID_32x32,BLACT_ANMID_CONTESTHERO,DATA_FieldOBJ_BlActAnmTbl_Hero},
	{CONTESTHEROINE,BLACT_MDLID_32x32,BLACT_ANMID_CONTESTHERO,DATA_FieldOBJ_BlActAnmTbl_Hero},
	{FISHINGHERO,BLACT_MDLID_FISHINGHERO,BLACT_ANMID_FISHINGHERO,DATA_FieldOBJ_BlActAnmTbl_FishingHero},
	{FISHINGHEROINE,BLACT_MDLID_FISHINGHERO,BLACT_ANMID_FISHINGHERO,DATA_FieldOBJ_BlActAnmTbl_FishingHero},
	{MOSS,BLACT_MDLID_16x16,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{FREEZES,BLACT_MDLID_16x16,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{POLE,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{SEED02A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED02B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED02C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED03A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED03B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED03C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED04A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED04B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED04C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED05A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED05B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED05C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED06A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED06B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED06C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED07A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED07B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED07C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED08A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED08B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED08C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED09A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED09B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED09C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED10A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED10B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED10C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED11A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED11B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED11C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED12A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED12B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED12C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED13A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED13B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED13C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED14A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED14B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED14C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED15A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED15B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED15C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED16A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED16B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED16C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED17A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED17B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED17C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED18A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED18B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED18C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED19A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED19B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED19C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED20A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED20B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED20C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED21A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED21B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED21C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED22A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED22B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED22C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED23A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED23B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED23C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED24A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED24B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED24C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED25A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED25B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED25C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED26A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED26B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED26C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED27A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED27B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED27C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED28A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED28B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED28C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED29A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED29B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED29C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED30A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED30B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED30C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED31A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED31B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED31C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED32A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED32B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED32C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED33A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED33B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED33C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED34A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED34B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED34C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED35A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED35B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED35C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED36A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED36B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED36C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED37A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED37B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED37C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED38A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED38B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED38C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED39A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED39B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED39C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED40A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED40B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED40C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED41A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED41B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED41C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED42A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED42B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED42C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED43A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED43B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED43C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED44A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED44B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED44C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED45A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED45B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED45C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED46A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED46B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED46C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED47A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED47B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED47C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED48A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED48B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED48C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED49A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED49B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED49C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED50A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED50B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED50C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED51A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED51B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED51C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED52A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED52B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED52C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED53A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED53B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED53C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED54A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED54B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED54C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED55A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED55B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED55C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED56A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED56B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED56C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED57A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED57B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED57C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED58A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED58B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED58C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED59A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED59B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED59C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED60A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED60B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED60C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED61A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED61B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED61C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED62A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED62B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED62C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED63A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED63B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED63C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED64A,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED64B,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{SEED64C,BLACT_MDLID_SEED,BLACT_ANMID_SEED,DATA_FieldOBJ_BlActAnmTbl_Seed0},
	{DELIVERY,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{DSBOY,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{KOIKING,BLACT_MDLID_32x32,BLACT_ANMID_KOIKING,DATA_FieldOBJ_BlActAnmTbl_Koiking},
	{POKEHERO,BLACT_MDLID_32x32,BLACT_ANMID_POKEHERO,DATA_FieldOBJ_BlActAnmTbl_PokeHero},
	{POKEHEROINE,BLACT_MDLID_32x32,BLACT_ANMID_POKEHERO,DATA_FieldOBJ_BlActAnmTbl_PokeHero},
	{SAVEHERO,BLACT_MDLID_32x32,BLACT_ANMID_SAVEHERO,DATA_FieldOBJ_BlActAnmTbl_SaveHero },
	{SAVEHEROINE,BLACT_MDLID_32x32,BLACT_ANMID_SAVEHERO,DATA_FieldOBJ_BlActAnmTbl_SaveHero},
	{BANZAIHERO,BLACT_MDLID_32x32,BLACT_ANMID_BANZAIHERO,DATA_FieldOBJ_BlActAnmTbl_BanzaiHero },
	{BANZAIHEROINE,BLACT_MDLID_32x32,BLACT_ANMID_BANZAIHERO,DATA_FieldOBJ_BlActAnmTbl_BanzaiHero},
	{DOOR,BLACT_MDLID_16x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MONUMENT,BLACT_MDLID_64x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{PATIRITUSU,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{KINOCOCO,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{MIMITUTO,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{KOLUCKY,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	{WANRIKY,BLACT_MDLID_32x32,BLACT_ANMID_NORMAL_0,DATA_FieldOBJ_BlActAnmTbl_Normal0},
	
	{OBJCODEMAX,BLACT_MDLID_MAX,BLACT_ANMID_MAX,NULL},
};

//==============================================================================
//	OBJコードステータスデータ
//==============================================================================
//--------------------------------------------------------------
//	OBJコード別描画ステータス　並びは不順
//--------------------------------------------------------------
const OBJCODE_STATE DATA_FieldOBJCodeDrawStateTbl[] =
{
 {HERO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BABYBOY1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BABYGIRL1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BOY1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BOY2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BOY3,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GIRL1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GIRL2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GIRL3,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MAN1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MAN2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MAN3,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {WOMAN1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {WOMAN2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {WOMAN3,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MIDDLEMAN1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MIDDLEWOMAN1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {OLDMAN1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {OLDWOMAN1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BIGMAN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MOUNT,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {CYCLEHERO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_CYCLE,FLDOBJ_REFLECT_BLACT,0},
 {REPORTER,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {CAMERAMAN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SHOPM1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SHOPW1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {PCWOMAN1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {PCWOMAN2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {PCWOMAN3,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {ASSISTANTM,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {ASSISTANTW,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BADMAN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SKIERM,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SKIERW,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {POLICEMAN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {IDOL,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GENTLEMAN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {LADY,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {CYCLEM,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_CYCLE,FLDOBJ_REFLECT_BLACT,0},
 {CYCLEW,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_CYCLE,FLDOBJ_REFLECT_BLACT,0},
 {WORKMAN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {FARMER,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {COWGIRL,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {CLOWN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {ARTIST,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPORTSMAN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SWIMMERM,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SWIMMERW,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BEACHGIRL,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BEACHBOY,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {EXPLORE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {FIGHTER,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {CAMPBOY,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {PICNICGIRL,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {FISHING,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {AMBRELLA,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SEAMAN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BRINGM,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BRINGW,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {WAITER,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {WAITRESS,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {VETERAN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GORGGEOUSM,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GORGGEOUSW,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BOY4,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GIRL4,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MAN4,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {WOMAN4,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MAN5,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {WOMAN5,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MYSTERY,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {PIKACHU,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {PIPPI,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {PURIN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {KODUCK,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {PRASLE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MINUN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MARIL,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {ACHAMO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {ENECO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GONBE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BABY,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MIDDLEMAN2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MIDDLEWOMAN2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {ROCK,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BREAKROCK,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {TREE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MONATERBALL,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SHADOW,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BOUGH,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {FALLTREE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BOARD_A,FLDOBJ_DRAWTYPE_MDL,FLDOBJ_SHADOW_NON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 {BOARD_B,FLDOBJ_DRAWTYPE_MDL,FLDOBJ_SHADOW_NON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 {BOARD_C,FLDOBJ_DRAWTYPE_MDL,FLDOBJ_SHADOW_NON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 {BOARD_D,FLDOBJ_DRAWTYPE_MDL,FLDOBJ_SHADOW_NON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 {BOARD_E,FLDOBJ_DRAWTYPE_MDL,FLDOBJ_SHADOW_NON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 {BOARD_F,FLDOBJ_DRAWTYPE_MDL,FLDOBJ_SHADOW_NON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 {HEROINE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {CYCLEHEROINE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_CYCLE,FLDOBJ_REFLECT_BLACT,0},
 {DOCTOR,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SEED,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_NON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_BLACT,0},
 {SNOWBALL,FLDOBJ_DRAWTYPE_MDL,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 {GINGABOSS,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GKANBU1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GKANBU2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GKANBU3,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GINGAM,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {GINGAW,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {LEADER1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {LEADER2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {LEADER3,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {LEADER4,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {LEADER5,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {LEADER6,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {LEADER7,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {LEADER8,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BIGFOUR1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BIGFOUR2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BIGFOUR3,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BIGFOUR4,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {CHAMPION,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {PAPA,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MAMA,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SEVEN1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SEVEN2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SEVEN3,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SEVEN4,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SEVEN5,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SEVEN6,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SEVEN7,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {RIVEL,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BOAT,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {TRAIN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE1,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE3,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE4,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE5,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE6,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE7,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE8,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE9,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE10,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPPOKE11,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {OBAKE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {WOMAN6,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {OLDMAN2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {OLDWOMAN2,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {OOKIDO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MIKAN,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SUNGLASSES,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {TOWERBOSS,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SNOWCOVER,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {TREECOVER,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {ROCKCOVER,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BIRD,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BAG,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MAID,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPHERO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SPHEROINE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SWIMHERO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SWIMHEROINE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {WATERHERO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {WATERHEROINE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {VENTHOLE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BOOK,FLDOBJ_DRAWTYPE_MDL,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 {SPPOKE12,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BALLOON,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {CONTESTHERO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {CONTESTHEROINE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {FISHINGHERO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {FISHINGHEROINE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {MOSS,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {FREEZES,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {POLE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {DELIVERY,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {DSBOY,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {KOIKING,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {NONDRAW,FLDOBJ_DRAWTYPE_NON,FLDOBJ_SHADOW_NON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 {POKEHERO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {POKEHEROINE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SAVEHERO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {SAVEHEROINE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BANZAIHERO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {BANZAIHEROINE,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NORMAL,FLDOBJ_REFLECT_BLACT,0},
 {DOOR,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_NON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 {MONUMENT,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_BLACT,0},
 {PATIRITUSU,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_CYCLE,FLDOBJ_REFLECT_BLACT,0},
 {KINOCOCO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_CYCLE,FLDOBJ_REFLECT_BLACT,0},
 {MIMITUTO,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_CYCLE,FLDOBJ_REFLECT_BLACT,0},
 {KOLUCKY,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_CYCLE,FLDOBJ_REFLECT_BLACT,0},
 {WANRIKY,FLDOBJ_DRAWTYPE_BLACT,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_CYCLE,FLDOBJ_REFLECT_BLACT,0},
 {DOOR2,FLDOBJ_DRAWTYPE_MDL,FLDOBJ_SHADOW_ON,FLDOBJ_FOOTMARK_NON,FLDOBJ_REFLECT_NON,0},
 
 {OBJCODEMAX,0,0,0,0,0},
};

//==============================================================================
//	木の実データ
//==============================================================================
//--------------------------------------------------------------
///	種類、成長別木の実OBJコード
//--------------------------------------------------------------
const OBJCODE_SEEDDATA DATA_OBJCodeSeedDataTbl[] =
{
	{SEED01A,SEED01B,SEED01C},
	{SEED02A,SEED02B,SEED02C},
	{SEED03A,SEED03B,SEED03C},
	{SEED04A,SEED04B,SEED04C},
	{SEED05A,SEED05B,SEED05C},
	{SEED06A,SEED06B,SEED06C},
	{SEED07A,SEED07B,SEED07C},
	{SEED08A,SEED08B,SEED08C},
	{SEED09A,SEED09B,SEED09C},
	{SEED10A,SEED10B,SEED10C},
	{SEED11A,SEED11B,SEED11C},
	{SEED12A,SEED12B,SEED12C},
	{SEED13A,SEED13B,SEED13C},
	{SEED14A,SEED14B,SEED14C},
	{SEED15A,SEED15B,SEED15C},
	{SEED16A,SEED16B,SEED16C},
	{SEED17A,SEED17B,SEED17C},
	{SEED18A,SEED18B,SEED18C},
	{SEED19A,SEED19B,SEED19C},
	{SEED20A,SEED20B,SEED20C},
	{SEED21A,SEED21B,SEED21C},
	{SEED22A,SEED22B,SEED22C},
	{SEED23A,SEED23B,SEED23C},
	{SEED24A,SEED24B,SEED24C},
	{SEED25A,SEED25B,SEED25C},
	{SEED26A,SEED26B,SEED26C},
	{SEED27A,SEED27B,SEED27C},
	{SEED28A,SEED28B,SEED28C},
	{SEED29A,SEED29B,SEED29C},
	{SEED30A,SEED30B,SEED30C},
	{SEED31A,SEED31B,SEED31C},
	{SEED32A,SEED32B,SEED32C},
	{SEED33A,SEED33B,SEED33C},
	{SEED34A,SEED34B,SEED34C},
	{SEED35A,SEED35B,SEED35C},
	{SEED36A,SEED36B,SEED36C},
	{SEED37A,SEED37B,SEED37C},
	{SEED38A,SEED38B,SEED38C},
	{SEED39A,SEED39B,SEED39C},
	{SEED40A,SEED40B,SEED40C},
	{SEED41A,SEED41B,SEED41C},
	{SEED42A,SEED42B,SEED42C},
	{SEED43A,SEED43B,SEED43C},
	{SEED44A,SEED44B,SEED44C},
	{SEED45A,SEED45B,SEED45C},
	{SEED46A,SEED46B,SEED46C},
	{SEED47A,SEED47B,SEED47C},
	{SEED48A,SEED48B,SEED48C},
	{SEED49A,SEED49B,SEED49C},
	{SEED50A,SEED50B,SEED50C},
	{SEED51A,SEED51B,SEED51C},
	{SEED52A,SEED52B,SEED52C},
	{SEED53A,SEED53B,SEED53C},
	{SEED54A,SEED54B,SEED54C},
	{SEED55A,SEED55B,SEED55C},
	{SEED56A,SEED56B,SEED56C},
	{SEED57A,SEED57B,SEED57C},
	{SEED58A,SEED58B,SEED58C},
	{SEED59A,SEED59B,SEED59C},
	{SEED60A,SEED60B,SEED60C},
	{SEED61A,SEED61B,SEED61C},
	{SEED62A,SEED62B,SEED62C},
	{SEED63A,SEED63B,SEED63C},
	{SEED64A,SEED64B,SEED64C},
};

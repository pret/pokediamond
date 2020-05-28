//============================================================================================
/**
 * @file	ookisa.c
 * @bfief	おおきさくらべ用関数
 * @author	Tomomichi Ohta
 * @date	06.03.23
 */
//============================================================================================
#include "common.h"
#include "system/pm_str.h"
#include "system\msgdata.h"
#include "system\wordset.h"
#include "system/get_text.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/pms_data.h"

#include "fieldsys.h"
#include "fieldmap.h"
#include "fld_bmp.h"
#include "talk_msg.h"
#include "fieldobj.h"
#include "field_subproc.h"
#include "field/field.h"
#include "field/poketch_data.h"

#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"
#include "vm.h"
#include "scrcmd.h"
#include "script.h"
#include "scr_tool.h"
#include "ev_win.h"

#include "include/application/zukanlist/zkn_height_gram.h"
#include "ookisa.h"

#include "tv_topic.h"	//TVTOPIC_Entry_Record_Ookisa

//============================================================================================
//
//	extern宣言
//
//============================================================================================


//============================================================================================
//
//	定義
//
//============================================================================================


typedef struct MONS_SCALE_ST {
	u16	T1;		//基準
	u16	T2;		//個体値補正係数
	u16	T3;		//個体値基準
	u16	dummy;
} MONS_SCALE;

static const MONS_SCALE mons_scale[] =
{
	{	 290,	  1,	    0,		0 },	// 0
	{	 300,	  1,	   10,		0 },	// 1
	{	 400,	  2,	  110,		0 },	// 2
	{	 500,	  4,	  310,		0 },	// 3
	{	 600,	 20,	  710,		0 },	// 4
	{	 700,	 50,	 2710,		0 },	// 5
	{	 800,	100,	 7710,		0 },	// 6
	{	 900,	150,	17710,		0 },	// 7
	{	1000,	150,	32710,		0 },	// 8
	{	1100,	100,	47710,		0 },	// 9
	{	1200,	 50,	57710,		0 },	// 10
	{	1300,	 20,	62710,		0 },	// 11
	{	1400,	  5,	64710,		0 },	// 12
	{	1500,	  2,	65210,		0 },	// 13
	{	1600,	  1,	65410,		0 },	// 14
	{	1700,	  1,	65510,		0 },	// 15
};

//----------------------------------------------------------
//	個体値の算出
//	<引数>	pp		ポケモン構造体へのポインタ
//	<戻り値>		個体値
//----------------------------------------------------------
static int calc_size_value( POKEMON_PARAM * poke)
{
	u16 personal_rnd;
	u16 hp_rnd,pow_rnd,def_rnd;
	u16 agi_rnd,spepow_rnd,spedef_rnd;
	u16 value_A,value_B;

	personal_rnd = PokeParaGet(poke,ID_PARA_personal_rnd,NULL) & 0xffff;
	hp_rnd = PokeParaGet(poke,ID_PARA_hp_rnd,NULL) &0x0f;
	pow_rnd = PokeParaGet(poke,ID_PARA_pow_rnd,NULL) & 0x0f;
	def_rnd = PokeParaGet(poke,ID_PARA_def_rnd,NULL) & 0x0f;
	agi_rnd = PokeParaGet(poke,ID_PARA_agi_rnd,NULL) & 0x0f;
	spepow_rnd = PokeParaGet(poke,ID_PARA_spepow_rnd,NULL) & 0x0f;
	spedef_rnd = PokeParaGet(poke,ID_PARA_spedef_rnd,NULL) & 0x0f;

	value_A = ((pow_rnd^def_rnd)*hp_rnd) ^ (personal_rnd&0xff) ;
	value_B = ((spepow_rnd^spedef_rnd)*agi_rnd) ^ (personal_rnd>>8) ;

	return value_A * 256 + value_B;
}
//SYS_WORK_OOKISA_RECORD

//----------------------------------------------------------
//	使用テーブル決定
//----------------------------------------------------------
static u8 get_size_level( u16 value )
{
	u8 level;

	for (level = 1; level < NELEMS(mons_scale) - 1; level ++) {
		if (value < mons_scale[level].T3) return level - 1;
	}
	return level;
}


//----------------------------------------------------------
//	大きさ算出
//	<引数>	monsno		ポケモンナンバー
//			value		個体値
//	<戻り値>			大きさの値
//----------------------------------------------------------
static u32 get_mons_size(u16 monsno, u16 value)
{
	u64 T1, T2, T3;
	u32 zukan_size;		//大きさ係数
	u64 size;
	u8 level;			//使用テーブル指定
	ZKN_HEIGHT_GRAM_PTR		zp;

	//ZukanPokeDataGetで取得できるのは図鑑での大きさ（メートル単位）×１０の値
	zp = ZKN_HEIGHTGRAM_Alloc( HEAPID_FIELD  );
	ZKN_HEIGHTGRAM_Free( zp );
	ZKN_HEIGHTGRAM_Load( zp, ZKN_HEIGHT_GRAM_TYPE_MAN, HEAPID_FIELD );
	zukan_size = ZKN_HEIGHTGRAM_GetHeight( (CONST_ZKN_HEIGHT_GRAM_PTR)zp, monsno );	//高さ取得
	ZKN_HEIGHTGRAM_Release( zp );

	level = get_size_level(value);
	T1 = mons_scale[level].T1;
	T2 = mons_scale[level].T2;
	T3 = mons_scale[level].T3;

	size = T1 + (value - T3) / T2 ;

	/* 大きさ係数の単位 を変換 */
	return zukan_size * size / 10;
}

//--------------------------------------------------------------------------------------------
/**
 *　おおきさを比べる
 *
 * @param	fsys		FIELDSYS_WORK構造体へのポインタ
 * @param	num			選んだ手持ち番号
 *
 * @return	"0:更新せず、1:同じ、2=記録更新"
 */
//--------------------------------------------------------------------------------------------
u8 OokisaRecordChk( FIELDSYS_WORK* fsys,u16 num)
{
	POKEMON_PARAM * pp;
	vu16 value,record_value;
	u16 monsno;
	u32 now_size;
	u32 record_size;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), num);

	//ポケモンナンバー取得
	monsno = PokeParaGet( pp, ID_PARA_monsno, NULL );

	value = calc_size_value(pp);
	now_size = get_mons_size(monsno, value);

	record_value = SysWork_OokisaRecordGet(SaveData_GetEventWork(fsys->savedata));
	record_size = get_mons_size(monsno, record_value);

	if (now_size == record_size) {
		return 1;		//同じ
	}else{
		if (now_size > record_size) {
			//テレビトピック生成
			TVTOPIC_Entry_Record_Ookisa(fsys, now_size, pp);
			return 2;		//記録更新した！
		}else{
			return 0;		//更新できず
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 *　おおきさのレコード(個体値)を更新
 *
 * @param	fsys		FIELDSYS_WORK構造体へのポインタ
 * @param	num			選んだ手持ち番号
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
void OokisaRecordSet(FIELDSYS_WORK* fsys,u16 num)
{
	POKEMON_PARAM * pp;
	vu16 value;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), num);

	value = calc_size_value(pp);
	SysWork_OokisaRecordSet(SaveData_GetEventWork(fsys->savedata),value);
}

//--------------------------------------------------------------------------------------------
/**
 *　個体値＆ポケモン番号から個々の高さに変換。文字バッファへセット
 *
 * @param	buf_no1		文字バッファ１
 * @param	buf_no2		文字バッファ２
 * @param	monsno		ポケモンナンバー
 * @param	value		個体値
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static void OokisaValue2Buffer(FIELDSYS_WORK* fsys,u8 buf_no1,u8 buf_no2,u16 monsno,vu16 value)
{
	u32 size;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs(fsys, ID_EVSCR_WORDSET );

	size = get_mons_size(monsno, value);
	WORDSET_RegisterNumber(*wordset,buf_no1,size/10,3, NUMBER_DISPTYPE_LEFT,NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(*wordset,buf_no2,size%10,1, NUMBER_DISPTYPE_LEFT,NUMBER_CODETYPE_DEFAULT);

}

//--------------------------------------------------------------------------------------------
/**
 *　レコードを数字に変換して、文字バッファへセット
 *
 * @param	fsys		FIELDSYS_WORK構造体へのポインタ
 * @param	buf_no1		文字バッファ１
 * @param	buf_no2		文字バッファ２
 * @param	monsno		ポケモンナンバー
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
void OokisaRecordBufSet(FIELDSYS_WORK* fsys,u8 buf_no1,u8 buf_no2,u16 monsno)
{
	vu16 value;

	value =	SysWork_OokisaRecordGet(SaveData_GetEventWork(fsys->savedata));
	OokisaValue2Buffer(fsys,buf_no1,buf_no2,monsno,value);
}

//--------------------------------------------------------------------------------------------
/**
 *　手持ちポケモン高さを数字に変換して、文字バッファへセット
 *
 * @param	fsys		FIELDSYS_WORK構造体へのポインタ
 * @param	buf_no1		文字バッファ１
 * @param	buf_no2		文字バッファ２
 * @param	num			手持ち番号
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
void OokisaTemotiBufSet(FIELDSYS_WORK* fsys,u8 buf_no1,u8 buf_no2,u16 num)
{
	POKEMON_PARAM * pp;
	u16 monsno;
	vu16 value;

	//ポケモンナンバー取得
	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), num);
	monsno = PokeParaGet( pp, ID_PARA_monsno, NULL );

	value = calc_size_value(pp);
	OokisaValue2Buffer(fsys,buf_no1,buf_no2,monsno,value);
}

//----------------------------------------------------------
//----------------------------------------------------------

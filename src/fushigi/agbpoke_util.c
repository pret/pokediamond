#include "agbpoke_access.h"
#include "agbpoke_util.h"

static u16 agbpoke_font[] = L"　あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよらりるれろわをんぁぃぅぇぉゃゅょがぎぐげござじすぜぞだぢづでどばびぶべぼぱぴぷぺぽっアイウエオカキクケコサシスセソタチツテトナニヌネノハヒフヘホマミムメモヤユヨラリルレロワヲンァィゥェォャュョガギグゲゴザジズゼゾダヂヅデドバビブベボパピプペポッ0123456789!?。ー・…『』「」♂♀円．×／ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz→:";
#define EUFONT_START 0xf1
#define EOM_			0xff		/* 終了コード */

static u16 eufont[] = 
{
	0x00c4, /* ウムラウト大文字A */
	0x00d6, /* ウムラウト大文字O */
	0x0055, /* ウムラウト大文字U */
	0x00e4, /* ウムラウト小文字A */
	0x00f6, /* ウムラウト小文字O */
	0x00fc /* ウムラウト小文字U */
};
static u16 convPokecode(u8 code)
{
	if( code < EUFONT_START ) return agbpoke_font[code];
	return eufont[code - EUFONT_START];
	
}

void agbpoke_codeConv(u8 *src, u16 *dest, int length)
{
	int i;
	for(i = 0; i < length; i++)
	{
		if( *(src + i) == EOM_ )
		{
			dest[i] = 0;
			return;
		}
		dest[i] = convPokecode(*(src + i));
	}
	dest[length] = 0;
}


//------------------------------------------------------------------
/**
 * @brief	トレーナーのＩＤナンバーを返す
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
u32 agbpoke_GetTrainerID(void)
{
  SYS_SAVE_DATA *myd = agbpoke_GetMyDataPtr();	// MyDataへのポインタを返す
  return myd->ID[3] << 24 | myd->ID[2] << 16 | myd->ID[1] << 8 | myd->ID[0];
}

//------------------------------------------------------------------
/**
 * @brief	トレーナー名を返す
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
u8 *agbpoke_GetTrainerName(void)
{
  SYS_SAVE_DATA *myd = agbpoke_GetMyDataPtr();	// MyDataへのポインタを返す
  return myd->my_name;
}


/*  */

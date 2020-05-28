#include <nitro.h>
#include <gflib/fntequ_agb_jp.h>
#include "pokeparam.h"
#include "agbpoke_tool.h"
#include "poketool/monsno.h"
#include "poketool/poke_tool.h"
#include "battle/battle_common.h"
#include "battle/battle_server.h"
#include "itemtool/item.h"
#include "system/agb_str.h"

#include "agbpoke2dppoke.c"

//AGBポケモンのデフォルト名（海外版では、変更の必要あり）
#if PM_LANG==LANG_JAPAN
#include "monsname.h"
#endif

#include "tokuseicnv.h"

#define	OLD_WAZANO_MAX		(354)	//AGBの技ナンバーMAX

//=========================================================================
//	プロトタイプ宣言
//=========================================================================
void	AGBPPPtoDSPPP(PokemonPasoParam *agb_ppp,POKEMON_PASO_PARAM *ds_ppp);

//=========================================================================
//	ポケモンパラメータアドレス取得
//=========================================================================
typedef struct
{
  PokemonPara1	PP1;
  PokemonPara2	PP2;
  PokemonPara3	PP3;
  PokemonPara4	PP4;
}PokemonParaData11;

typedef struct
{
  PokemonPara1	PP1;
  PokemonPara2	PP2;
  PokemonPara4	PP4;
  PokemonPara3	PP3;
}PokemonParaData12;

typedef struct
{
  PokemonPara1	PP1;
  PokemonPara3	PP3;
  PokemonPara2	PP2;
  PokemonPara4	PP4;
}PokemonParaData13;

typedef struct
{
  PokemonPara1	PP1;
  PokemonPara3	PP3;
  PokemonPara4	PP4;
  PokemonPara2	PP2;
}PokemonParaData14;

typedef struct
{
  PokemonPara1	PP1;
  PokemonPara4	PP4;
  PokemonPara2	PP2;
  PokemonPara3	PP3;
}PokemonParaData15;

typedef struct
{
  PokemonPara1	PP1;
  PokemonPara4	PP4;
  PokemonPara3	PP3;
  PokemonPara2	PP2;
}PokemonParaData16;

typedef struct
{
  PokemonPara2	PP2;
  PokemonPara1	PP1;
  PokemonPara3	PP3;
  PokemonPara4	PP4;
}PokemonParaData21;

typedef struct
{
  PokemonPara2	PP2;
  PokemonPara1	PP1;
  PokemonPara4	PP4;
  PokemonPara3	PP3;
}PokemonParaData22;

typedef struct
{
  PokemonPara2	PP2;
  PokemonPara3	PP3;
  PokemonPara1	PP1;
  PokemonPara4	PP4;
}PokemonParaData23;

typedef struct
{
  PokemonPara2	PP2;
  PokemonPara3	PP3;
  PokemonPara4	PP4;
  PokemonPara1	PP1;
}PokemonParaData24;

typedef struct
{
  PokemonPara2	PP2;
  PokemonPara4	PP4;
  PokemonPara1	PP1;
  PokemonPara3	PP3;
}PokemonParaData25;

typedef struct
{
  PokemonPara2	PP2;
  PokemonPara4	PP4;
  PokemonPara3	PP3;
  PokemonPara1	PP1;
}PokemonParaData26;

typedef struct
{
  PokemonPara3	PP3;
  PokemonPara1	PP1;
  PokemonPara2	PP2;
  PokemonPara4	PP4;
}PokemonParaData31;

typedef struct
{
  PokemonPara3	PP3;
  PokemonPara1	PP1;
  PokemonPara4	PP4;
  PokemonPara2	PP2;
}PokemonParaData32;

typedef struct
{
  PokemonPara3	PP3;
  PokemonPara2	PP2;
  PokemonPara1	PP1;
  PokemonPara4	PP4;
}PokemonParaData33;

typedef struct
{
  PokemonPara3	PP3;
  PokemonPara2	PP2;
  PokemonPara4	PP4;
  PokemonPara1	PP1;
}PokemonParaData34;

typedef struct
{
  PokemonPara3	PP3;
  PokemonPara4	PP4;
  PokemonPara1	PP1;
  PokemonPara2	PP2;
}PokemonParaData35;

typedef struct
{
  PokemonPara3	PP3;
  PokemonPara4	PP4;
  PokemonPara2	PP2;
  PokemonPara1	PP1;
}PokemonParaData36;

typedef struct
{
  PokemonPara4	PP4;
  PokemonPara1	PP1;
  PokemonPara2	PP2;
  PokemonPara3	PP3;
}PokemonParaData41;

typedef struct
{
  PokemonPara4	PP4;
  PokemonPara1	PP1;
  PokemonPara3	PP3;
  PokemonPara2	PP2;
}PokemonParaData42;

typedef struct
{
  PokemonPara4	PP4;
  PokemonPara2	PP2;
  PokemonPara1	PP1;
  PokemonPara3	PP3;
}PokemonParaData43;

typedef struct
{
  PokemonPara4	PP4;
  PokemonPara2	PP2;
  PokemonPara3	PP3;
  PokemonPara1	PP1;
}PokemonParaData44;

typedef struct
{
  PokemonPara4	PP4;
  PokemonPara3	PP3;
  PokemonPara1	PP1;
  PokemonPara2	PP2;
}PokemonParaData45;

typedef struct
{
  PokemonPara4	PP4;
  PokemonPara3	PP3;
  PokemonPara2	PP2;
  PokemonPara1	PP1;
}PokemonParaData46;

static u32 AgbPokeParaAdrsGet(PokemonPasoParam *PPP,u32 rnd,u8 id)
{
  u32	ret=0;

  PokemonParaData11	*PPD11;
  PokemonParaData12	*PPD12;
  PokemonParaData13	*PPD13;
  PokemonParaData14	*PPD14;
  PokemonParaData15	*PPD15;
  PokemonParaData16	*PPD16;
  PokemonParaData21	*PPD21;
  PokemonParaData22	*PPD22;
  PokemonParaData23	*PPD23;
  PokemonParaData24	*PPD24;
  PokemonParaData25	*PPD25;
  PokemonParaData26	*PPD26;
  PokemonParaData31	*PPD31;
  PokemonParaData32	*PPD32;
  PokemonParaData33	*PPD33;
  PokemonParaData34	*PPD34;
  PokemonParaData35	*PPD35;
  PokemonParaData36	*PPD36;
  PokemonParaData41	*PPD41;
  PokemonParaData42	*PPD42;
  PokemonParaData43	*PPD43;
  PokemonParaData44	*PPD44;
  PokemonParaData45	*PPD45;
  PokemonParaData46	*PPD46;


  switch(rnd%24){
  case ID_AGB_POKEPARADATA11:
    PPD11=(PokemonParaData11 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD11->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD11->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD11->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD11->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA12:
    PPD12=(PokemonParaData12 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD12->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD12->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD12->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD12->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA13:
    PPD13=(PokemonParaData13 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD13->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD13->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD13->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD13->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA14:
    PPD14=(PokemonParaData14 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD14->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD14->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD14->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD14->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA15:
    PPD15=(PokemonParaData15 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD15->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD15->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD15->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD15->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA16:
    PPD16=(PokemonParaData16 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD16->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD16->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD16->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD16->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA21:
    PPD21=(PokemonParaData21 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD21->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD21->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD21->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD21->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA22:
    PPD22=(PokemonParaData22 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD22->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD22->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD22->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD22->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA23:
    PPD23=(PokemonParaData23 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD23->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD23->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD23->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD23->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA24:
    PPD24=(PokemonParaData24 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD24->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD24->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD24->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD24->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA25:
    PPD25=(PokemonParaData25 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD25->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD25->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD25->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD25->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA26:
    PPD26=(PokemonParaData26 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD26->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD26->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD26->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD26->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA31:
    PPD31=(PokemonParaData31 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD31->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD31->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD31->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD31->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA32:
    PPD32=(PokemonParaData32 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD32->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD32->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD32->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD32->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA33:
    PPD33=(PokemonParaData33 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD33->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD33->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD33->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD33->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA34:
    PPD34=(PokemonParaData34 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD34->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD34->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD34->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD34->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA35:
    PPD35=(PokemonParaData35 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD35->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD35->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD35->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD35->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA36:
    PPD36=(PokemonParaData36 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD36->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD36->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD36->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD36->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA41:
    PPD41=(PokemonParaData41 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD41->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD41->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD41->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD41->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA42:
    PPD42=(PokemonParaData42 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD42->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD42->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD42->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD42->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA43:
    PPD43=(PokemonParaData43 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD43->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD43->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD43->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD43->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA44:
    PPD44=(PokemonParaData44 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD44->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD44->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD44->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD44->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA45:
    PPD45=(PokemonParaData45 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD45->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD45->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD45->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD45->PP4;
      break;
    }
    break;
  case ID_AGB_POKEPARADATA46:
    PPD46=(PokemonParaData46 *)PPP->paradata;
    switch(id){
    case ID_AGB_POKEPARA1:
      ret=(u32)&PPD46->PP1;
      break;
    case ID_AGB_POKEPARA2:
      ret=(u32)&PPD46->PP2;
      break;
    case ID_AGB_POKEPARA3:
      ret=(u32)&PPD46->PP3;
      break;
    case ID_AGB_POKEPARA4:
      ret=(u32)&PPD46->PP4;
      break;
    }
    break;
  }
  return ret;
}


//=========================================================================
//	ポケモンパラメータ復号化
//=========================================================================
static void AgbPokeParaDecoded(PokemonPasoParam *PPP)
{
  int	i;
  u32	*data;

  data=(u32 *)&PPP->paradata;
  for(i=0;
      i<(sizeof(PokemonPara1)+sizeof(PokemonPara2)+sizeof(PokemonPara3)+sizeof(PokemonPara4))/4;
      i++){
    data[i]^=PPP->id_no;
    data[i]^=PPP->personal_rnd;
  }
}


//=========================================================================
//	ポケモンパラメータ暗号化
//=========================================================================
static void AgbPokeParaCoded(PokemonPasoParam *PPP)
{
  int	i;
  u32	*data;

  data=(u32 *)&PPP->paradata;
  for(i=0;
      i<(sizeof(PokemonPara1)+sizeof(PokemonPara2)+sizeof(PokemonPara3)+sizeof(PokemonPara4))/4;
      i++){
    data[i]^=PPP->personal_rnd;
    data[i]^=PPP->id_no;
  }
}


//=============================================================
//
//		ポケモンデータのチェックサムを算出
//
//=============================================================
static u16 AgbPokeParaCheckSum(PokemonPasoParam *PPP)
{
  int i;
  u16 *CP1;
  u16 *CP2;
  u16 *CP3;
  u16 *CP4;
  u16 sum=0;

  CP1=(u16 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA1);
  CP2=(u16 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA2);
  CP3=(u16 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA3);
  CP4=(u16 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA4);

  for(i=0;i<12/2;i++)
    sum+=CP1[i];
  for(i=0;i<12/2;i++)
    sum+=CP2[i];
  for(i=0;i<12/2;i++)
    sum+=CP3[i];
  for(i=0;i<12/2;i++)
    sum+=CP4[i];

  return sum;
}


u32 AgbPokePasoParaGet(PokemonPasoParam *PPP,int id,u8 *buf)
{
  int	i;
  u32	ret=0;
  PokemonPara1		*PP1=0;
  PokemonPara2		*PP2=0;
  PokemonPara3		*PP3=0;
  PokemonPara4		*PP4=0;
  u16	sum;
  u16	*wazano;

#if 0
  OS_Printf("personal_rnd = %08X %d, id=%d\n", PPP->personal_rnd, PPP->personal_rnd%24, id);
#endif

  if(id>ID_AGB_amari){
    PP1=(PokemonPara1 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA1);
    PP2=(PokemonPara2 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA2);
    PP3=(PokemonPara3 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA3);
    PP4=(PokemonPara4 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA4);

    //チェックサムでは復号をしないので、注意！！
    AgbPokeParaDecoded(PPP);
    sum=AgbPokeParaCheckSum(PPP);

    if(sum!=PPP->checksum){
      PPP->fusei_tamago_flag=1;
      PPP->egg_exist_flag=1;
      PP4->tamago_flag=1;
    }
  }

#if 0
  {
    u8 *p = (u8 *)PP1;
    for(i = 0; i < 64; i++, p++){
      if((i % 16) == 0)	OS_Printf("\n");
      OS_Printf("%02X ", *p);
    }
    OS_Printf("\n\n");
  }
#endif


  
  switch(id){
  case ID_AGB_personal_rnd:
    ret=PPP->personal_rnd;
    break;
  case ID_AGB_id_no:
    ret=PPP->id_no;
    break;

  case ID_AGB_nickname:
    if(PPP->fusei_tamago_flag){
#if 0
      for(ret=0;ret<5;ret++)
	buf[ret]=HuseiNaTamagoMsg[ret];
#else
      ret = 0;
#endif
    } else {
      for(ret = 0; ret < MONS_NAME_SIZE; ret++){
	buf[ret] = PPP->nickname[ret];
      }
    }
    buf[ret] = JP_AGB_EOM_;
    break;

  case ID_AGB_country_code:
    ret=PPP->country_code;
    break;
  case ID_AGB_fusei_tamago_flag:
    ret=PPP->fusei_tamago_flag;
    break;

  case ID_AGB_poke_exist_flag:
    ret=PPP->poke_exist_flag;
    break;

  case ID_AGB_egg_exist_flag:
    ret=PPP->egg_exist_flag;
    break;
  case ID_AGB_oyaname:
    for(ret=0;ret<PERSON_NAME_SIZE;ret++)
      buf[ret]=PPP->oyaname[ret];
    buf[ret]=EOM_;
    break;
  case ID_AGB_mark:
    ret=PPP->mark;
    break;
  case ID_AGB_checksum:
    ret=PPP->checksum;
    break;
  case ID_AGB_amari:
    ret=PPP->amari;
    break;
    

  case ID_AGB_monsno:
    if(PPP->fusei_tamago_flag)
      ret=MONSNO_AGB_TAMAGO;
    else
      ret=PP1->monsno;
    break;

    
  case ID_AGB_item:
    ret=PP1->item;
    break;

  case ID_AGB_exp:
    ret=PP1->exp;
    break;

  case ID_AGB_pp_count:
    ret=PP1->pp_count;
    break;
  case ID_AGB_friend:
    ret=PP1->friend;
    break;

  case ID_AGB_waza1:
  case ID_AGB_waza2:
  case ID_AGB_waza3:
  case ID_AGB_waza4:
    ret=PP2->waza[id-ID_AGB_waza1];
    break;
  case ID_AGB_pp1:
  case ID_AGB_pp2:
  case ID_AGB_pp3:
  case ID_AGB_pp4:
    ret=PP2->pp[id-ID_AGB_pp1];
    break;

  case ID_AGB_hp_exp:
    ret=PP3->hp_exp;
    break;
  case ID_AGB_pow_exp:
    ret=PP3->pow_exp;
    break;
  case ID_AGB_def_exp:
    ret=PP3->def_exp;
    break;
  case ID_AGB_agi_exp:
    ret=PP3->agi_exp;
    break;
  case ID_AGB_spepow_exp:
    ret=PP3->spepow_exp;
    break;
  case ID_AGB_spedef_exp:
    ret=PP3->spedef_exp;
    break;
  case ID_AGB_style:
    ret=PP3->style;
    break;
  case ID_AGB_beautiful:
    ret=PP3->beautiful;
    break;
  case ID_AGB_cute:
    ret=PP3->cute;
    break;
  case ID_AGB_clever:
    ret=PP3->clever;
    break;
  case ID_AGB_strong:
    ret=PP3->strong;
    break;
  case ID_AGB_fur:
    ret=PP3->fur;
    break;

  case ID_AGB_pokerus:
    ret=PP4->pokerus;
    break;
  case ID_AGB_get_place:
    ret=PP4->get_place;
    break;

  case ID_AGB_get_level:
    ret=PP4->get_level;
    break;

  case ID_AGB_get_cassette:
    ret=PP4->get_cassette;
    break;
  case ID_AGB_get_ball:
    ret=PP4->get_ball;
    break;
  case ID_AGB_oyasex:
    ret=PP4->oyasex;
    break;
  case ID_AGB_hp_rnd:
    ret=PP4->hp_rnd;
    break;
  case ID_AGB_pow_rnd:
    ret=PP4->pow_rnd;
    break;
  case ID_AGB_def_rnd:
    ret=PP4->def_rnd;
    break;
  case ID_AGB_agi_rnd:
    ret=PP4->agi_rnd;
    break;
  case ID_AGB_spepow_rnd:
    ret=PP4->spepow_rnd;
    break;
  case ID_AGB_spedef_rnd:
    ret=PP4->spedef_rnd;
    break;
  case ID_AGB_tamago_flag:
    ret=PP4->tamago_flag;
    break;
  case ID_AGB_speabi:
    ret=PP4->speabi;
    break;
  case	ID_AGB_stylemedal:		//12h	かっこよさ勲章
    ret=PP4->stylemedal;
    break;
  case	ID_AGB_beautifulmedal:		//13h	うつくしさ勲章
    ret=PP4->beautifulmedal;
    break;
  case	ID_AGB_cutemedal:		//14h	かわいさ勲章
    ret=PP4->cutemedal;
    break;
  case	ID_AGB_clevermedal:		//24h	かしこさ勲章
    ret=PP4->clevermedal;
    break;
  case	ID_AGB_strongmedal:		//2fh	たくましさ勲章
    ret=PP4->strongmedal;
    break;
  case	ID_AGB_champ_ribbon:			//チャンプリボン
    ret = PP4->champ_ribbon;
    break;
  case	ID_AGB_winning_ribbon:		//ウィニングリボン
    ret = PP4->winning_ribbon;
    break;
  case	ID_AGB_victory_ribbon:		//ビクトリーリボン
    ret = PP4->victory_ribbon;
    break;
  case	ID_AGB_bromide_ribbon:		//ブロマイドリボン
    ret = PP4->bromide_ribbon;
    break;
  case	ID_AGB_ganba_ribbon:			//がんばリボン
    ret = PP4->ganba_ribbon;
    break;
  case	ID_AGB_marine_ribbon:		//マリンリボン
    ret = PP4->marine_ribbon;
    break;
  case	ID_AGB_land_ribbon:			//ランドリボン
    ret = PP4->land_ribbon;
    break;
  case	ID_AGB_sky_ribbon:			//スカイリボン
    ret = PP4->sky_ribbon;
    break;
  case	ID_AGB_country_ribbon:		//カントリーリボン
    ret = PP4->country_ribbon;
    break;
  case	ID_AGB_national_ribbon:		//ナショナルリボン
    ret = PP4->national_ribbon;
    break;
  case	ID_AGB_earth_ribbon:			//アースリボン
    ret = PP4->earth_ribbon;
    break;
  case	ID_AGB_world_ribbon:			//ワールドリボン
    ret = PP4->world_ribbon;
    break;
  case	ID_AGB_amari_ribbon:			//あまり
    ret = PP4->amari_ribbon;
    break;
  case	ID_AGB_event_get_flag:			//イベントで配布されたことを示すフラグ
    ret = PP4->event_get_flag;
    break;

  case ID_AGB_monsno_egg:
    ret=PP1->monsno;
    if(ret==0)
      break;
    if((PP4->tamago_flag)||
       (PPP->fusei_tamago_flag))
      ret=MONSNO_AGB_TAMAGO;
    break;
  case ID_AGB_power_rnd:
    ret=(PP4->hp_rnd	<< 0)|
      (PP4->pow_rnd	<< 5)|
      (PP4->def_rnd	<<10)|
      (PP4->agi_rnd	<<15)|
      (PP4->spepow_rnd<<20)|
      (PP4->spedef_rnd<<25);
    break;
#if 0
  case ID_AGB_waza_have_check:
    wazano=(u16 *)buf;
    i=0;
    if((PP1->monsno)&&(PP4->tamago_flag==0)){
      while(wazano[i]!=WAZANO_MAX+1){
	if((PP2->waza[0]==wazano[i])||
	   (PP2->waza[1]==wazano[i])||
	   (PP2->waza[2]==wazano[i])||
	   (PP2->waza[3]==wazano[i]))
	  ret|=no2bittbl[i];
	i++;
      }
    }
    break;

    // リボンの総数カウント   taya
  case ID_AGB_ribbon_cnt:
    ret = 0;
    if((PP1->monsno)&&(PP4->tamago_flag==0)){
      ret += PP4->stylemedal;
      ret += PP4->beautifulmedal;
      ret += PP4->cutemedal;
      ret += PP4->clevermedal;
      ret += PP4->strongmedal;
      ret += PP4->champ_ribbon;
      ret += PP4->winning_ribbon;
      ret += PP4->victory_ribbon;
      ret += PP4->bromide_ribbon;
      ret += PP4->ganba_ribbon;
      ret += PP4->marine_ribbon;
      ret += PP4->land_ribbon;
      ret += PP4->sky_ribbon;
      ret += PP4->country_ribbon;
      ret += PP4->national_ribbon;
      ret += PP4->earth_ribbon;
      ret += PP4->world_ribbon;
    }
    break;

    // 取得リボンに応じたﾋﾞｯﾄを立てて返す  taya
  case ID_AGB_ribbon_bit:
    ret = 0;
    if((PP1->monsno)&&(PP4->tamago_flag==0)){

      ret = PP4->champ_ribbon;

      ret |= (PP4->stylemedal << 1);
      ret |= (PP4->beautifulmedal << 4);
      ret |= (PP4->cutemedal << 7);
      ret |= (PP4->clevermedal << 10);
      ret |= (PP4->strongmedal << 13);

      ret |= (PP4->winning_ribbon << 16);
      ret |= (PP4->victory_ribbon << 17);
      ret |= (PP4->bromide_ribbon << 18);
      ret |= (PP4->ganba_ribbon << 19);
      ret |= (PP4->marine_ribbon << 20);
      ret |= (PP4->land_ribbon << 21);
      ret |= (PP4->sky_ribbon << 22);
      ret |= (PP4->country_ribbon << 23);
      ret |= (PP4->national_ribbon << 24);
      ret |= (PP4->earth_ribbon << 25);
      ret |= (PP4->world_ribbon << 26);
    }
    break;
#endif
  }
  if(id>ID_AGB_amari)
    AgbPokeParaCoded(PPP);

  return ret;
}


void AgbPokePasoParaPut(PokemonPasoParam *PPP,int id,const u8 *buf)
{
  int i;
  u32 work;
  PokemonPara1 *PP1=0;
  PokemonPara2 *PP2=0;
  PokemonPara3 *PP3=0;
  PokemonPara4 *PP4=0;
  u16 sum;

  if(id>ID_AGB_amari){
    PP1=(PokemonPara1 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA1);
    PP2=(PokemonPara2 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA2);
    PP3=(PokemonPara3 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA3);
    PP4=(PokemonPara4 *)AgbPokeParaAdrsGet(PPP,PPP->personal_rnd,ID_AGB_POKEPARA4);

    //チェックサムは復号をしないので注意！！
    AgbPokeParaDecoded(PPP);
    sum = AgbPokeParaCheckSum(PPP);
	
    //不正なデータの時は書き込みをしない
    if(sum!=PPP->checksum){
      PPP->fusei_tamago_flag=1;		
      PPP->egg_exist_flag=1;		
      PP4->tamago_flag=1;
      AgbPokeParaCoded(PPP);
      return;
    }
  }

  switch(id){
#if 0
  case ID_AGB_personal_rnd:
    PPP->personal_rnd=buf[0]+(buf[1]<<8)+(buf[2]<<16)+(buf[3]<<24);
    break;
  case ID_AGB_id_no:
    PPP->id_no=buf[0]+(buf[1]<<8)+(buf[2]<<16)+(buf[3]<<24);
    break;
#endif
  case ID_AGB_nickname:
    for(i=0;i<MONS_NAME_SIZE;i++){
      PPP->nickname[i]=buf[i];
    }
    break;
  case ID_AGB_country_code:
    PPP->country_code=buf[0];		
    break;

  case ID_AGB_fusei_tamago_flag:
    PPP->fusei_tamago_flag=buf[0];		
    break;
  case ID_AGB_poke_exist_flag:
    PPP->poke_exist_flag=buf[0];
    break;
  case ID_AGB_egg_exist_flag:
    PPP->egg_exist_flag=buf[0];
    break;

  case ID_AGB_oyaname:
    for(i=0;i<PERSON_NAME_SIZE;i++)
      PPP->oyaname[i]=buf[i];
    break;
#if 0
  case ID_AGB_mark:
    PPP->mark=buf[0];		
    break;
  case ID_AGB_checksum:
    PPP->checksum=buf[0]+(buf[1]<<8);
    break;
  case ID_AGB_amari:
    PPP->amari=buf[0]+(buf[1]<<8);
    break;
#endif
    
  case ID_AGB_monsno:
    PP1->monsno=buf[0]+(buf[1]<<8);
    if(PP1->monsno)
      PPP->poke_exist_flag=1;
    else
      PPP->poke_exist_flag=0;
    break;

#if 0
  case ID_AGB_item:
    PP1->item=buf[0]+(buf[1]<<8);
    break;
  case ID_AGB_exp:
    PP1->exp=buf[0]+(buf[1]<<8)+(buf[2]<<16)+(buf[3]<<24);
    break;
  case ID_AGB_pp_count:
    PP1->pp_count=buf[0];
    break;
  case ID_AGB_friend:
    PP1->friend=buf[0];
    break;

  case ID_AGB_waza1:
  case ID_AGB_waza2:
  case ID_AGB_waza3:
  case ID_AGB_waza4:
    PP2->waza[id-ID_AGB_waza1]=buf[0]+(buf[1]<<8);
    break;
  case ID_AGB_pp1:
  case ID_AGB_pp2:
  case ID_AGB_pp3:
  case ID_AGB_pp4:
    PP2->pp[id-ID_AGB_pp1]=buf[0];
    break;

  case ID_AGB_hp_exp:
    PP3->hp_exp=buf[0];
    break;
  case ID_AGB_pow_exp:
    PP3->pow_exp=buf[0];
    break;
  case ID_AGB_def_exp:
    PP3->def_exp=buf[0];
    break;
  case ID_AGB_agi_exp:
    PP3->agi_exp=buf[0];
    break;
  case ID_AGB_spepow_exp:
    PP3->spepow_exp=buf[0];
    break;
  case ID_AGB_spedef_exp:
    PP3->spedef_exp=buf[0];
    break;
  case	ID_AGB_style:						//12h	かっこよさ
    PP3->style=buf[0];
    break;
  case	ID_AGB_beautiful:					//13h	うつくしさ
    PP3->beautiful=buf[0];
    break;
  case	ID_AGB_cute:						//14h	かわいさ
    PP3->cute=buf[0];
    break;
  case	ID_AGB_clever:						//24h	かしこさ
    PP3->clever=buf[0];
    break;
  case	ID_AGB_strong:						//2fh	たくましさ
    PP3->strong=buf[0];	
    break;
  case	ID_AGB_fur:						//30h	毛艶
    PP3->fur=buf[0];		
    break;

  case ID_AGB_pokerus:
    PP4->pokerus=buf[0];
    break;
  case ID_AGB_get_place:
    PP4->get_place=buf[0];
    break;
  case ID_AGB_get_level:
    PP4->get_level=buf[0];
    break;
  case ID_AGB_get_cassette:
    PP4->get_cassette=buf[0];
    break;
  case ID_AGB_get_ball:
    PP4->get_ball=buf[0];
    break;
  case ID_AGB_oyasex:
    PP4->oyasex=buf[0];
    break;
  case ID_AGB_hp_rnd:
    PP4->hp_rnd=buf[0];
    break;
  case ID_AGB_pow_rnd:
    PP4->pow_rnd=buf[0];
    break;
  case ID_AGB_def_rnd:
    PP4->def_rnd=buf[0];
    break;
  case ID_AGB_agi_rnd:
    PP4->agi_rnd=buf[0];
    break;
  case ID_AGB_spepow_rnd:
    PP4->spepow_rnd=buf[0];
    break;
  case ID_AGB_spedef_rnd:
    PP4->spedef_rnd=buf[0];
    break;
  case ID_AGB_tamago_flag:
    PP4->tamago_flag=buf[0];
    if(PP4->tamago_flag)
      PPP->egg_exist_flag=1;
    else
      PPP->egg_exist_flag=0;
    break;
  case ID_AGB_speabi:
    PP4->speabi=buf[0];
    break;
  case	ID_AGB_stylemedal:		//12h	かっこよさ勲章
    PP4->stylemedal=buf[0];		
    break;
  case	ID_AGB_beautifulmedal:		//13h	うつくしさ勲章
    PP4->beautifulmedal=buf[0];		
    break;
  case	ID_AGB_cutemedal:		//14h	かわいさ勲章
    PP4->cutemedal=buf[0];
    break;
  case	ID_AGB_clevermedal:		//24h	かしこさ勲章
    PP4->clevermedal=buf[0];
    break;
  case	ID_AGB_strongmedal:		//2fh	たくましさ勲章
    PP4->strongmedal=buf[0];
    break;
  case	ID_AGB_champ_ribbon:			//チャンプリボン
    PP4->champ_ribbon = buf[0];
    break;
  case	ID_AGB_winning_ribbon:		//ウィニングリボン
    PP4->winning_ribbon = buf[0];
    break;
  case	ID_AGB_victory_ribbon:		//ビクトリーリボン
    PP4->victory_ribbon = buf[0];
    break;
  case	ID_AGB_bromide_ribbon:		//ブロマイドリボン
    PP4->bromide_ribbon = buf[0];
    break;
  case	ID_AGB_ganba_ribbon:			//がんばリボン
    PP4->ganba_ribbon = buf[0];
    break;
  case	ID_AGB_marine_ribbon:		//マリンリボン
    PP4->marine_ribbon = buf[0];
    break;
  case	ID_AGB_land_ribbon:			//ランドリボン
    PP4->land_ribbon = buf[0];
    break;
  case	ID_AGB_sky_ribbon:			//スカイリボン
    PP4->sky_ribbon = buf[0];
    break;
  case	ID_AGB_country_ribbon:		//カントリーリボン
    PP4->country_ribbon = buf[0];
    break;
  case	ID_AGB_national_ribbon:		//ナショナルリボン
    PP4->national_ribbon = buf[0];
    break;
  case	ID_AGB_earth_ribbon:			//アースリボン
    PP4->earth_ribbon = buf[0];
    break;
  case	ID_AGB_world_ribbon:			//ワールドリボン
    PP4->world_ribbon = buf[0];
    break;
  case	ID_AGB_amari_ribbon:			//あまり
    PP4->amari_ribbon = buf[0];
    break;
  case	ID_AGB_event_get_flag:			//イベントで配布されたことを示すフラグ
    PP4->event_get_flag = buf[0];
    break;

  case ID_AGB_power_rnd:
    work=(buf[0]<< 0)|
      (buf[1]<< 8)|
      (buf[2]<<16)|
      (buf[3]<<24);
    PP4->hp_rnd		=(work>> 0)&0x0000001f;
    PP4->pow_rnd	=(work>> 5)&0x0000001f;
    PP4->def_rnd	=(work>>10)&0x0000001f;
    PP4->agi_rnd	=(work>>15)&0x0000001f;
    PP4->spepow_rnd	=(work>>20)&0x0000001f;
    PP4->spedef_rnd	=(work>>25)&0x0000001f;
    break;
#endif
  }

  if(id>ID_AGB_amari){
    //チェックサムは復号をしないので注意！！
    PPP->checksum = AgbPokeParaCheckSum(PPP);
    AgbPokeParaCoded(PPP);
  }
}


  //------------------------------------------------------------------
/**
 * @brief	AGBポケモン→DPポケモンへの変換
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define	MONSNO_AGB_KIMORI	277
int ChangeAGBPoke2DPPoke(int agbpoke)
{
  int i;

  // キモリ以前ならば同じモンスター番号
  if(agbpoke < MONSNO_AGB_KIMORI)
    return agbpoke;
  // キモリ～ならば変換して返す
  for(i = 0; i < sizeof(PokemonOld2NewTable) / sizeof(POKEMON_CHANGE_TABLE); i++)
    if(PokemonOld2NewTable[i].old == agbpoke)
      return PokemonOld2NewTable[i].new;
  // 未定義の場合はそのまま返す
  return agbpoke;
}


//============================================================================================
/**
 *	ボックスポケモンデータからポケモンのレベルを取得
 *
 * @param[in]	ppp	取得したいボックスポケモンパラメータ構造体のポインタ
 *
 * @return	取得したレベル
 */
//============================================================================================
u32 AgbPokePasoLevelCalc(PokemonPasoParam *ppp)
{
  int monsno;
  u32	exp;

  monsno = ChangeAGBPoke2DPPoke(AgbPokePasoParaGet(ppp, ID_AGB_monsno, 0));
  exp = AgbPokePasoParaGet(ppp, ID_AGB_exp, 0);
  return PokeLevelCalc(monsno, exp);
}

//============================================================================================
/**
 *	AGBポケモンの特性をDSポケモンの特性に変換する
 *
 * @param[in]	ds_ppp	DSPokePasoParam構造体のポインタ
 *
 * @return	特性ナンバー
 */
//============================================================================================
static	int	DSTokuseiNoGet(PokemonPasoParam *agb_ppp,POKEMON_PASO_PARAM *ds_ppp)
{
	int	i;
	int	speabino;
	u16	mons_no;
	int	speabibit;

	mons_no=PokePasoParaGet(ds_ppp,ID_PARA_monsno,NULL);
	speabibit=AgbPokePasoParaGet(agb_ppp,ID_AGB_speabi,NULL);

	speabino=PokePersonalParaGet(mons_no,ID_PER_speabi2);

	if(speabino){
		for(i=0;i<(sizeof(TokuseiCnvTable)/2);i++){
			//旧作で、特性2がなかったポケモンは、強制的に特性1にする
			if(TokuseiCnvTable[i]==mons_no){
				speabino=PokePersonalParaGet(mons_no,ID_PER_speabi1);
				break;
			}
		}
		//旧作でも、今作でも、特性が両方ある場合は、特性ビットで判断する
		if((i==(sizeof(TokuseiCnvTable)/2))&&((speabibit&1)==0)){
			speabino=PokePersonalParaGet(mons_no,ID_PER_speabi1);
		}
	}
	else{
		speabino=PokePersonalParaGet(mons_no,ID_PER_speabi1);
	}

	return speabino;
}

//============================================================================================
/**
 *	AGBPokePasoParam構造体をDSPokePasoParam構造体にコピーする
 *
 * @param[in]		agb_ppp	AGBPokePasoParam構造体のポインタ
 * @param[in/out]	ds_ppp	DSPokePasoParam構造体のポインタ
 */
//============================================================================================
void	AGBPPPtoDSPPP(PokemonPasoParam *agb_ppp,POKEMON_PASO_PARAM *ds_ppp)
{
	BOOL	flag;
	u32		work;
	int		i,j;
	int		country_code;
	u8		agb_name_buf[MONS_NAME_SIZE+EOM_SIZE];
	STRCODE	ds_name_buf[BUFLEN_POKEMON_NAME];

	//念のためds_pppを初期化
	PokePasoParaInit(ds_ppp);

	//あまり意味はないかもだけど、ds_pppを高速化モードに
	flag=PokePasoParaFastModeOn(ds_ppp);

	//個性乱数
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_personal_rnd,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_personal_rnd,(u8 *)&work);

	//ppp1系
	//モンスターナンバー
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_monsno,NULL);
	work=ChangeAGBPoke2DPPoke(work);
	PokePasoParaPut(ds_ppp,ID_PARA_monsno,(u8 *)&work);

	//所持アイテムナンバー
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_item,NULL);
	if(work)	work=ITEM_AgbItemCnv(work);
	PokePasoParaPut(ds_ppp,ID_PARA_item,(u8 *)&work);

	//IDNo
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_id_no,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_id_no,(u8 *)&work);

	//経験値
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_exp,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_exp,(u8 *)&work);

	//なつき度は、初期値に戻す
//	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_friend,NULL);
	work=70;
	PokePasoParaPut(ds_ppp,ID_PARA_friend,(u8 *)&work);

	//特殊能力
	work=DSTokuseiNoGet(agb_ppp,ds_ppp);
	PokePasoParaPut(ds_ppp,ID_PARA_speabino,(u8 *)&work);

	//ポケモンにつけるマーク（ボックス）
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_mark,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_mark,(u8 *)&work);

	//国コード
	country_code=AgbPokePasoParaGet(agb_ppp,ID_AGB_country_code,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_country_code,(u8 *)&country_code);

	//HP努力値
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_hp_exp,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_hp_exp,(u8 *)&work);
	
	//攻撃力努力値
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_pow_exp,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_pow_exp,(u8 *)&work);
	
	//防御力努力値
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_def_exp,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_def_exp,(u8 *)&work);
	
	//素早さ努力値
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_agi_exp,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_agi_exp,(u8 *)&work);
	
	//特攻努力値
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_spepow_exp,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_spepow_exp,(u8 *)&work);
	
	//特防努力値
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_spedef_exp,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_spedef_exp,(u8 *)&work);
	
	//かっこよさ
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_style,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_style,(u8 *)&work);
	
	//うつくしさ
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_beautiful,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_beautiful,(u8 *)&work);
	
	//かわいさ
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_cute,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_cute,(u8 *)&work);
	
	//かしこさ
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_clever,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_clever,(u8 *)&work);
	
	//たくましさ
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_strong,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_strong,(u8 *)&work);
	
	//毛艶
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_fur,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_fur,(u8 *)&work);

	//ppp2系
	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		//所持技
		work=AgbPokePasoParaGet(agb_ppp,ID_AGB_waza1+i,NULL);
		if(work>OLD_WAZANO_MAX){
			//本来はなんらかの処理をいれるはず
		}
		PokePasoParaPut(ds_ppp,ID_PARA_waza1+i,(u8 *)&work);

		//所持技PP_COUNT
		work=AgbPokePasoParaGet(agb_ppp,ID_AGB_pp_count,NULL);
		work=(work&(0x03<<(i*2)))>>(i*2);
		PokePasoParaPut(ds_ppp,ID_PARA_pp_count1+i,(u8 *)&work);

		//所持技PP（一応不正防止のため、技のPPMAXを代入する
		work=PokePasoParaGet(ds_ppp,ID_PARA_pp_max1+i,NULL);
		PokePasoParaPut(ds_ppp,ID_PARA_pp1+i,(u8 *)&work);
	}

	//HP乱数
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_hp_rnd,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_hp_rnd,(u8 *)&work);

	//攻撃力乱数
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_pow_rnd,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_pow_rnd,(u8 *)&work);

	//防御力乱数
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_def_rnd,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_def_rnd,(u8 *)&work);

	//素早さ乱数
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_agi_rnd,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_agi_rnd,(u8 *)&work);

	//特攻乱数
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_spepow_rnd,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_spepow_rnd,(u8 *)&work);

	//特防乱数
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_spedef_rnd,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_spedef_rnd,(u8 *)&work);

	//タマゴフラグ（0:タマゴじゃない　1:タマゴだよ）
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_tamago_flag,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_tamago_flag,(u8 *)&work);

	//海外版では、変更の必要があるかも
#if PM_LANG==LANG_JAPAN
	//ニックネームをつけたかどうかフラグ（0:つけていない　1:つけた）
	if(AgbPokePasoParaGet(agb_ppp,ID_AGB_country_code,NULL)!=CasetteLanguage){
		//カセットの言語と違う国のポケモンは、ニックネームつけている扱いにする
		work=1;
		PokePasoParaPut(ds_ppp,ID_PARA_nickname_flag,(u8 *)&work);
	}
	else{
		work=AgbPokePasoParaGet(agb_ppp,ID_AGB_monsno,NULL);
		AgbPokePasoParaGet(agb_ppp,ID_AGB_nickname,&agb_name_buf[0]);
		for(i=0;i<6;i++){
			//デフォルト名と違う場合はニックネーム扱い
			if(PokeNameData[work][i]!=agb_name_buf[i]){
				work=1;
				PokePasoParaPut(ds_ppp,ID_PARA_nickname_flag,(u8 *)&work);
				break;
			}
			//一致しているならデフォルト名
			else if(agb_name_buf[i]==EOM_){
				work=0;
				PokePasoParaPut(ds_ppp,ID_PARA_nickname_flag,(u8 *)&work);
				break;
			}
		}
	}
#endif

	//かっこよさ勲章
	j=AgbPokePasoParaGet(agb_ppp,ID_AGB_stylemedal,NULL);
	if(j<=4){
		for(i=0;i<j;i++){
			work=1;
			PokePasoParaPut(ds_ppp,ID_PARA_stylemedal_normal+i,(u8 *)&work);
		}
	}

	//うつくしさ勲章
	j=AgbPokePasoParaGet(agb_ppp,ID_AGB_beautifulmedal,NULL);
	if(j<=4){
		for(i=0;i<j;i++){
			work=1;
			PokePasoParaPut(ds_ppp,ID_PARA_beautifulmedal_normal+i,(u8 *)&work);
		}
	}

	//かわいさ勲章
	j=AgbPokePasoParaGet(agb_ppp,ID_AGB_cutemedal,NULL);
	if(j<=4){
		for(i=0;i<j;i++){
			work=1;
			PokePasoParaPut(ds_ppp,ID_PARA_cutemedal_normal+i,(u8 *)&work);
		}
	}

	//かしこさ勲章
	j=AgbPokePasoParaGet(agb_ppp,ID_AGB_clevermedal,NULL);
	if(j<=4){
		for(i=0;i<j;i++){
			work=1;
			PokePasoParaPut(ds_ppp,ID_PARA_clevermedal_normal+i,(u8 *)&work);
		}
	}

	//たくましさ勲章
	j=AgbPokePasoParaGet(agb_ppp,ID_AGB_strongmedal,NULL);
	if(j<=4){
		for(i=0;i<j;i++){
			work=1;
			PokePasoParaPut(ds_ppp,ID_PARA_strongmedal_normal+i,(u8 *)&work);
		}
	}

	//チャンプリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_champ_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_champ_ribbon,(u8 *)&work);

	//ウィニングリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_winning_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_winning_ribbon,(u8 *)&work);

//ビクトリーリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_victory_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_victory_ribbon,(u8 *)&work);

	//ブロマイドリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_bromide_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_bromide_ribbon,(u8 *)&work);

	//がんばリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_ganba_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_ganba_ribbon,(u8 *)&work);

	//マリンリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_marine_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_marine_ribbon,(u8 *)&work);

	//ランドリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_land_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_land_ribbon,(u8 *)&work);

	//スカイリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_sky_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_sky_ribbon,(u8 *)&work);

	//カントリーリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_country_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_country_ribbon,(u8 *)&work);

	//ナショナルリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_national_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_national_ribbon,(u8 *)&work);

	//アースリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_earth_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_earth_ribbon,(u8 *)&work);

	//ワールドリボン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_world_ribbon,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_world_ribbon,(u8 *)&work);

	//イベントで配布したことを示すフラグ
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_event_get_flag,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_event_get_flag,(u8 *)&work);

	//ポケモンの性別
	work=PokePasoSexGet(ds_ppp);
	PokePasoParaPut(ds_ppp,ID_PARA_sex,(u8 *)&work);

	//形状ナンバー（アンノーン、デオキシスのみ）
	if(PokePasoParaGet(ds_ppp,ID_PARA_monsno,NULL)==MONSNO_ANNOON){
		work=AgbPokePasoParaGet(agb_ppp,ID_AGB_personal_rnd,NULL);
		work=(((work&0x03000000)>>18)|((work&0x030000)>>12)|((work&0x0300)>>6)|(work&0x03))%28;
		PokePasoParaPut(ds_ppp,ID_PARA_form_no,(u8 *)&work);
	}
	if(PokePasoParaGet(ds_ppp,ID_PARA_monsno,NULL)==MONSNO_DEOKISISU){
		//ゲットしたカセットバージョンによってフォルムを変える
//		switch(AgbPokePasoParaGet(agb_ppp,ID_AGB_get_cassette,NULL)){
		//ＤＰに持ってくるときに入っていたカセットバージョンによってフォルムを変える
		switch(sys.AgbCasetteVersion){
		default:
		case VERSION_RUBY:
		case VERSION_SAPPHIRE:
			//ルビー・サファイア・未知のバージョンはノーマル
			work=FORMNO_DEOKISISU_NORMAL;
			break;
		case VERSION_RED:
			//ファイアレッドはアタック
			work=FORMNO_DEOKISISU_ATTACK;
			break;
		case VERSION_GREEN:
			//リーフグリーンはディフェンス
			work=FORMNO_DEOKISISU_DEFENCE;
			break;
		case VERSION_EMERALD:
			//エメラルドはスピード
			work=FORMNO_DEOKISISU_SPEED;
			break;
		}
		PokePasoParaPut(ds_ppp,ID_PARA_form_no,(u8 *)&work);
	}

	//ppp3系
	//ニックネーム
	AgbPokePasoParaGet(agb_ppp,ID_AGB_nickname,&agb_name_buf[0]);
	AGBSTR_to_DSSTR(&agb_name_buf[0],&ds_name_buf[0],BUFLEN_POKEMON_NAME,country_code);
	PokePasoParaPut(ds_ppp,ID_PARA_nickname,&ds_name_buf[0]);

	//捕まえたカセットバージョン
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_get_cassette,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_get_cassette,&work);

	///ppp4系
	//親の名前
	AgbPokePasoParaGet(agb_ppp,ID_AGB_oyaname,&agb_name_buf[0]);
	AGBSTR_to_DSSTR(&agb_name_buf[0],&ds_name_buf[0],BUFLEN_PERSON_NAME,country_code);
	PokePasoParaPut(ds_ppp,ID_PARA_oyaname,&ds_name_buf[0]);

	//捕まえた場所（トレーナーメモ対応のため、生まれた場所の方に値を入れておく）
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_get_place,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_birth_place,&work);

	//ポケルス
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_pokerus,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_pokerus,&work);

	//捕まえたボール
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_get_ball,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_get_ball,&work);

	//捕まえたレベル
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_get_level,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_get_level,&work);

	//親の性別
	work=AgbPokePasoParaGet(agb_ppp,ID_AGB_oyasex,NULL);
	PokePasoParaPut(ds_ppp,ID_PARA_oyasex,&work);

	//高速化モードOFF
	PokePasoParaFastModeOff(ds_ppp,flag);
}


//============================================================================================
/**
 * @file	sodateyadata.h
 * @brief	育て屋データアクセス用ヘッダ
 * @author	mori GAME FREAK inc.
 * @date	2005.12.21
 */
//============================================================================================
#ifndef __SODATEAYADATA_H__
#define __SODATEAYADATA_H__

#include "savedata/savedata_def.h"	//SAVEDATA参照のため
#include "savedata/mail_util.h"
#include "poketool\poke_tool.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------


#define SODATEYA_POKE_MAX	( 2 )

enum{
	SIOMAIL_FLAG_OYA   =0,
	SIOMAIL_FLAG_POKE,
};


typedef struct SIO_MAIL_DATA SIO_MAIL_DATA;
typedef struct SODATEYA_POKE SODATEYA_POKE;
typedef struct SODATEYA_WORK SODATEYA_WORK;



extern int SodateyaWork_GetWorkSize(void);
extern SODATEYA_WORK * SodateyaWork_AllocWork(u32 heapID);
extern void SodateyaWork_Copy(const SODATEYA_WORK * from, SODATEYA_WORK * to);
extern void SodateyaWork_Init(SODATEYA_WORK * sw);
extern SODATEYA_POKE *SodateyaWork_GetSodateyaPokePointer( SODATEYA_WORK *sw, int no);
extern POKEMON_PASO_PARAM *SodateyaPoke_GetPokePasoPointer( SODATEYA_POKE *sp );
extern SIO_MAIL_DATA *SodateyaPoke_GetSioMailPointer( SODATEYA_POKE *sp );
extern u32 SodateyaPoke_GetWalkCount( const SODATEYA_POKE *sp );
extern MAIL_DATA *SodateyaMail_GetMailPointer( SIO_MAIL_DATA *mail );
extern STRCODE *SodateyaMail_GetNamePointer( SIO_MAIL_DATA *mail, int flag );
extern int SodateyaMail_GetLanguage( SIO_MAIL_DATA *mail, int flag );
extern int SodateyaWork_GetEggFlag( const SODATEYA_WORK *sw );
extern int SodateyaWork_GetEggCount( const SODATEYA_WORK *sw );
extern void SodateyaWork_CopyPokePasoParam( SODATEYA_WORK *sw, const POKEMON_PARAM *pp, int no );
extern void SodateyaPoke_SetWalkCount( SODATEYA_POKE *sp, int num );
extern void SodateyaPoke_AddWalkCount( SODATEYA_POKE *sp, int num );
extern void SodateyaWork_SetEggFlag( SODATEYA_WORK *sw, int Flag);
extern void SodateyaWork_SetEggCount( SODATEYA_WORK *sw, int Count );
extern void SodateyaPoke_Copy( SODATEYA_POKE *des, const SODATEYA_POKE *src);
extern void SioMailDataInit( SIO_MAIL_DATA	*smd );
extern void SodateyaPoke_Init(SODATEYA_POKE *poke);
extern BOOL SodateyaWork_GetRareFlag( SODATEYA_WORK *sw );


extern SODATEYA_WORK * SaveData_GetSodateyaWork(SAVEDATA * sv);














#endif

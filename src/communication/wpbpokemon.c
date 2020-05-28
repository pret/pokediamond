/*---------------------------------------------------------------------------*
  Project:  Wireless PassBy Library
  File:     wpbpokemon.c

  2005 Ambrella
 *---------------------------------------------------------------------------*/
#include    "communication/wpbpokemon.h"

u8 WPB_ToPresentID(u8 totalItems, u8 salt, u8 itemNo)
{
	return (u8)(itemNo ? 1 + ((itemNo - 1) * 255 + salt - 1) / totalItems : 0);
}

u8 WPB_FromPresentID(u8 totalItems, u8 salt, u8 presentID)
{
	return (u8)(presentID ? 1 + (presentID - 1) * totalItems / 255 : 0);
}

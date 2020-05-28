//==============================================================================
/**
 *
 *@file		pokememo.h
 *@brief	
 *@author	
 *@data		
 *
 */
//==============================================================================
#ifndef __POKEMENMO_H__
#define __POKEMENMO_H__


// データ構造体
typedef struct TRMEMO_MSG_DATA_tag
{
	int		line;
	STRBUF*	msg;

}TRMEMO_MSG_DATA;

typedef struct TRMEMO_DATA_tag
{
	int					heapID;

	MSGDATA_MANAGER*	msg_man;
	WORDSET*			word_set;
	POKEMON_PARAM*		pp;
	BOOL				mine;

	TRMEMO_MSG_DATA		character1;
	TRMEMO_MSG_DATA		encount;
	TRMEMO_MSG_DATA		character2;
	TRMEMO_MSG_DATA		palate;
	TRMEMO_MSG_DATA		eggstatus;

}TRMEMO_DATA;

typedef enum {
	TRMEMO_POKE_PLACESET = 0,	//通常取得（捕獲等）
	TRMEMO_OFFTRADE_PLACESET,	//ゲーム内交換
	TRMEMO_POKEPARK_PLACESET,	//ポケパーク
	TRMEMO_SODATEYA_PLACESET,	//育て屋（タマゴのみ）
	TRMEMO_FUSHIGI_PLACESET,	//外部配布
	TRMEMO_ONTRADE_PLACESET,	//通信交換
	TRMEMO_EGGBIRTH_PLACESET,	//タマゴ孵化
}TRMEMO_SETID;

extern TRMEMO_DATA*	TrainerMemoGet( POKEMON_PARAM* pp, BOOL mine, int heapID );
extern void			TrainerMemoFree( TRMEMO_DATA* dat );
extern void			TrainerMemoSetPP(	POKEMON_PARAM* pp, MYSTATUS* my,
										TRMEMO_SETID setID, int placeID, int heapID );
extern void			TrainerMemoSetPPP(	POKEMON_PASO_PARAM* ppp, MYSTATUS* my,
										TRMEMO_SETID setID, int placeID, int heapID );

#endif

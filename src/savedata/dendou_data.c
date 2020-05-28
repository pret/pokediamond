//============================================================================================
/**
 * @file	dendou_data.c
 * @brief	�a������Z�[�u�f�[�^
 * @author	taya
 * @date	2006.04.20
 */
//============================================================================================
#include "common.h"
#include "savedata\savedata.h"
#include "system\gamedata.h"
#include "gflib\strbuf_family.h"
#include "poketool\pokeparty.h"

#include "savedata\dendou_data.h"


enum {
	POKENAME_BUFSIZE = MONS_NAME_SIZE+EOM_SIZE,		// 11
	OYANAME_BUFSIZE = PERSON_NAME_SIZE+EOM_SIZE,	// 8
};


//----------------------------------------------------------
/**
 *	�a������|�P�����̃f�[�^�i60 bytes�j
 */
//----------------------------------------------------------
typedef struct {
	u16	monsno;				///< �|�P�����i���o�[�i�O�Ȃ�f�[�^�S�̂������j
	u8	level;				///< ���x��
	u8	formNumber;			///< �t�H����
	u32	personalRandom;		///< �̗���
	u32	idNumber;			///< ID
	STRCODE	nickname[ POKENAME_BUFSIZE ];	///< �j�b�N�l�[��
	STRCODE	oyaname[ OYANAME_BUFSIZE ];		///< ���▼
	u16	waza[ 4 ];			///< �Z�i���o�[
}DENDOU_POKEMON_DATA_INSIDE;


//----------------------------------------------------------
/**
 *	�a������P�����R�[�h�f�[�^�i364 bytes�j
 */
//----------------------------------------------------------
typedef struct {
	DENDOU_POKEMON_DATA_INSIDE	pokemon[ TEMOTI_POKEMAX ];	///< �|�P�����f�[�^
	u16			year;				///< �a��������t�i�N�j 2006 �`
	u8			month;				///< �a��������t�i���j 1�`12
	u8			day;				///< �a��������t�i���j 1�`31
}DENDOU_RECORD;


//----------------------------------------------------------
/**
 *	�a������Z�[�u�f�[�^�{�́i10920 bytes�j
 */
//----------------------------------------------------------
struct _DENDOU_SAVEDATA {

	DENDOU_RECORD	record[ DENDOU_RECORD_MAX ];

	u32		savePoint;		///< record�z�񒆂́A���ɃZ�[�u����index
	u32		latestNumber;	///< �ŐV�f�[�^�̓a������ʎZ��
};



//==============================================================
// Prototype
//==============================================================
static int inline recIndex_to_datIndex( const DENDOU_SAVEDATA* data, int recIndex );





//------------------------------------------------------------------
/**
 * �Z�[�u�f�[�^�T�C�Y��Ԃ�
 *
 * @retval  int		
 */
//------------------------------------------------------------------
int DendouData_GetWorkSize( void )
{
	return sizeof(DENDOU_SAVEDATA);
}
//------------------------------------------------------------------
/**
 * �f�[�^������
 *
 * @param   data		
 *
 */
//------------------------------------------------------------------
void DendouData_Init( DENDOU_SAVEDATA* data )
{
	MI_CpuClear32( data, sizeof(DENDOU_SAVEDATA) );
}




//------------------------------------------------------------------
/**
 * �a�����背�R�[�h�P���ǉ�
 *
 * @param   data		�a������Z�[�u�f�[�^�|�C���^
 * @param   party		�a������p�[�e�B�[�̃f�[�^
 * @param   date		�a��������t�f�[�^�iNITRO�̃f�[�^���̂܂܁j
 *
 */
//------------------------------------------------------------------
void DendouData_AddRecord( DENDOU_SAVEDATA* data, const POKEPARTY* party, const RTCDate* date )
{
	DENDOU_RECORD*  record;
	POKEMON_PARAM*  pp;
	STRBUF*         strbuf;
	int  pokeCount, i, p;
	BOOL fastFlag;

	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);

	if( data->latestNumber >= DENDOU_NUMBER_MAX )
	{
		return;
	}

	record = &data->record[ data->savePoint ];
	pokeCount = PokeParty_GetPokeCount( party );

	strbuf = STRBUF_Create( POKENAME_BUFSIZE, HEAPID_BASE_SYSTEM );

	MI_CpuClear16( record->pokemon,  sizeof(DENDOU_POKEMON_DATA_INSIDE)*TEMOTI_POKEMAX );

	for(i=0, p=0; i<pokeCount; i++)
	{
		pp = PokeParty_GetMemberPointer( party, i );

		fastFlag = PokeParaFastModeOn( pp );

		if( PokeParaGet(pp, ID_PARA_tamago_flag, NULL) == FALSE )
		{
			record->pokemon[p].monsno = PokeParaGet( pp, ID_PARA_monsno, NULL );
			record->pokemon[p].level = PokeParaGet( pp, ID_PARA_level, NULL );
			record->pokemon[p].formNumber = PokeParaGet( pp, ID_PARA_form_no, NULL );
			record->pokemon[p].personalRandom = PokeParaGet( pp, ID_PARA_personal_rnd, NULL );
			record->pokemon[p].idNumber = PokeParaGet( pp, ID_PARA_id_no, NULL );
			record->pokemon[p].waza[0] = PokeParaGet( pp, ID_PARA_waza1, NULL );
			record->pokemon[p].waza[1] = PokeParaGet( pp, ID_PARA_waza2, NULL );
			record->pokemon[p].waza[2] = PokeParaGet( pp, ID_PARA_waza3, NULL );
			record->pokemon[p].waza[3] = PokeParaGet( pp, ID_PARA_waza4, NULL );

			if(strbuf)
			{
				PokeParaGet( pp, ID_PARA_nickname_buf, strbuf );
				STRBUF_GetStringCode( strbuf, record->pokemon[p].nickname, POKENAME_BUFSIZE );

				PokeParaGet( pp, ID_PARA_oyaname_buf, strbuf );
				STRBUF_GetStringCode( strbuf, record->pokemon[p].oyaname, OYANAME_BUFSIZE );
			}
			else
			{
				record->pokemon[p].nickname[0] = EOM_;
				record->pokemon[p].oyaname[0] = EOM_;
			}

			p++;
		}

		PokeParaFastModeOff( pp, fastFlag );
	}

	record->year = date->year;
	record->month = date->month;
	record->day = date->day;


	if(++(data->savePoint) >= DENDOU_RECORD_MAX)
	{
		data->savePoint = 0;
	}
	data->latestNumber++;


	if(strbuf)
	{
		STRBUF_Delete(strbuf);
	}

}




//------------------------------------------------------------------
/**
 * �a�����背�R�[�h������Ԃ�
 *
 * @param   data	�a������f�[�^�|�C���^
 *
 * @retval  u32		����
 */
//------------------------------------------------------------------
u32 DendouData_GetRecordCount( const DENDOU_SAVEDATA* data )
{
	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);

	if( data->latestNumber >= DENDOU_RECORD_MAX )
	{
		return DENDOU_RECORD_MAX;
	}
	return data->latestNumber;
}
//------------------------------------------------------------------
/**
 * �a�����背�R�[�h���A����ڂ̓a�����肩��Ԃ�
 *
 * @param   data		�a������f�[�^�|�C���^
 * @param   index		���R�[�h�C���f�b�N�X�i0���ŐV�ŁA���ɋ����Ȃ��Ă����j
 *
 * @retval  u32			
 */
//------------------------------------------------------------------
u32 DendouData_GetRecordNumber( const DENDOU_SAVEDATA* data, int index )
{
	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);
	GF_ASSERT(index < DENDOU_RECORD_MAX);

	return data->latestNumber - index;
}
//------------------------------------------------------------------
/**
 * �a�����背�R�[�h����A�|�P�������擾
 *
 * @param   data		�a������f�[�^�|�C���^
 * @param   index		���R�[�h�C���f�b�N�X�i0���ŐV�ŁA���ɋ����Ȃ��Ă����j
 *
 * @retval	u32		�a������p�[�e�B�[�̃|�P������
 */
//------------------------------------------------------------------
u32 DendouData_GetPokemonCount( const DENDOU_SAVEDATA* data, int index )
{
	u32 i;

	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);
	GF_ASSERT(index < DENDOU_RECORD_MAX);

	index = recIndex_to_datIndex( data, index );
	for(i=0; i<TEMOTI_POKEMAX; i++)
	{
		if(data->record[index].pokemon[i].monsno == 0)
		{
			break;
		}
	}
	return i;
}
//------------------------------------------------------------------
/**
 * �a�����背�R�[�h����A�|�P�����f�[�^�擾
 *
 * @param   data		�a������f�[�^�|�C���^
 * @param   index		���R�[�h�C���f�b�N�X�i0���ŐV�ŁA���ɋ����Ȃ��Ă����j
 * @param   poke_pos	���̖ڂ̃|�P�������i0�`5�j
 * @param   poke_data	�|�P�����f�[�^���󂯎��\���̂̃|�C���^
 */
//------------------------------------------------------------------
void DendouData_GetPokemonData( const DENDOU_SAVEDATA* data, int index, int poke_pos, DENDOU_POKEMON_DATA* poke_data )
{
	const DENDOU_POKEMON_DATA_INSIDE*  recPoke;
	int i;

	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);
	GF_ASSERT(index < DENDOU_RECORD_MAX);

	index = recIndex_to_datIndex( data, index );
	recPoke = &(data->record[index].pokemon[poke_pos]);

	poke_data->monsno = recPoke->monsno;
	poke_data->level = recPoke->level;
	poke_data->personalRandom = recPoke->personalRandom;
	poke_data->idNumber = recPoke->idNumber;
	poke_data->formNumber = recPoke->formNumber;

	STRBUF_SetStringCode( poke_data->nickname, recPoke->nickname );
	STRBUF_SetStringCode( poke_data->oyaname, recPoke->oyaname );

	for(i=0; i<4; i++)
	{
		poke_data->waza[i] = recPoke->waza[i];
	}
}
//------------------------------------------------------------------
/**
 * �a�����背�R�[�h����A�a��������t�擾
 *
 * @param   data		�a������f�[�^�|�C���^
 * @param   index		���R�[�h�C���f�b�N�X�i0���ŐV�ŁA���ɋ����Ȃ��Ă����j
 * @param   date		���t�f�[�^���󂯎��\���̂ւ̃|�C���^
 */
//------------------------------------------------------------------
void DendouData_GetDate( const DENDOU_SAVEDATA* data, int index, RTCDate* date )
{
	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);
	GF_ASSERT(index < DENDOU_RECORD_MAX);

	index = recIndex_to_datIndex( data, index );
	date->year = data->record[index].year;
	date->month = data->record[index].month;
	date->day = data->record[index].day;

	// �j���͕ۑ����Ȃ����A�ꉞ�N���A���Ă���
	date->week = 0;

}















//------------------------------------------------------------------
/**
 * ���R�[�h�C���f�b�N�X�i�V�������C���f�b�N�X�j���f�[�^�z��C���f�b�N�X�ɕϊ�
 *
 * @param   index		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int inline recIndex_to_datIndex( const DENDOU_SAVEDATA* data, int recIndex )
{
	int datIndex = (data->savePoint - 1 - recIndex);
	if( datIndex < 0 )
	{
		datIndex += DENDOU_RECORD_MAX;
	}
	return datIndex;
}

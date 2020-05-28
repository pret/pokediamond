//============================================================================================
/**
 * @file	boxdata.c
 * @brief	�|�P�����{�b�N�X�f�[�^��舵��
 * @author	taya
 * @date	2005.09.05
 */
//============================================================================================
#include "common.h"
#include "gflib\strbuf_family.h"
#include "poketool\poke_tool.h"
#include "system\pm_str.h"
#include "system\msgdata.h"
#include "savedata\savedata.h"

#include "system\arc_tool.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_boxmenu.h"
#include "poketool\boxdata.h"
#include "..\poke_tool_def.h"


struct _BOX_DATA{
	u32					currentTrayNumber;
	POKEMON_PASO_PARAM  ppp[BOX_MAX_TRAY][BOX_MAX_POS];
	STRCODE				trayName[BOX_MAX_TRAY][BOX_TRAYNAME_BUFSIZE];
	u8					wallPaper[BOX_MAX_TRAY];
	u8					daisukiBitFlag;
};


//==============================================================
// Prototype
//==============================================================
static void boxdata_init( BOX_DATA* boxdat );


//------------------------------------------------------------------
/**
 * �{�b�N�X�f�[�^������
 */
//------------------------------------------------------------------
void BOXDAT_Init( BOX_DATA* boxdat )
{
	boxdata_init(boxdat);
	SaveData_RequestTotalSave();
}
//------------------------------------------------------------------
/**
 * �{�b�N�X�f�[�^�̑��T�C�Y��Ԃ�
 *
 * @retval  u32		�{�b�N�X�f�[�^�T�C�Y
 */
//------------------------------------------------------------------
u32 BOXDAT_GetTotalSize( void )
{
	return sizeof( BOX_DATA );
}


//------------------------------------------------------------------
/**
 * �{�b�N�X�f�[�^�̈揉����
 *
 * @param   boxdat		
 *
 */
//------------------------------------------------------------------
static void boxdata_init( BOX_DATA* boxdat )
{
	u32 i, p;
	MSGDATA_MANAGER*  msgman;

	for(i = 0; i < BOX_MAX_TRAY; i++)
	{
		for(p = 0; p < BOX_MAX_POS; p++)
		{
			PokePasoParaInit( &(boxdat->ppp[i][p]) );
		}
	}

	// �ǎ��i���o�[�C���������N���u�ǎ��̎擾�t���O
	for(i = 0, p = 0; i < BOX_MAX_TRAY; i++)
	{
		boxdat->wallPaper[i] = p++;
		if(p >= BOX_NORMAL_WALLPAPER_MAX)
		{
			p = 0;
		}
	}
	boxdat->daisukiBitFlag = 0;


	// �f�t�H���g�{�b�N�X���Z�b�g
	msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_boxmenu_dat, HEAPID_BASE_SYSTEM );
	if( msgman )
	{
		for(i = 0 ; i < BOX_MAX_TRAY; i++)
		{
			MSGMAN_GetStr( msgman, mes_boxmenu_02_02+i, boxdat->trayName[i] );
		}
		MSGMAN_Delete( msgman );
	}

	boxdat->currentTrayNumber = 0;

}
//------------------------------------------------------------------
/**
 * �{�b�N�X�S�̂��炩��󂫗̈��T���ă|�P�����f�[�^���i�[
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   poke		�|�P�����f�[�^
 *
 * @retval  BOOL		TRUE=�i�[���ꂽ�^FALSE=�󂫂�����
 */
//------------------------------------------------------------------
BOOL BOXDAT_PutPokemon( BOX_DATA* box, POKEMON_PASO_PARAM* poke )
{
	u32 b;

	b = box->currentTrayNumber;
	do
	{
		PokePasoPara_RecoverPP(poke);

		if( BOXDAT_PutPokemonBox( box, b, poke ) )
		{
			SaveData_RequestTotalSave();
			return TRUE;
		}

		if( ++b >= BOX_MAX_TRAY )
		{
			b = 0;
		}

	}while( b != box->currentTrayNumber );

	return FALSE;
}

//------------------------------------------------------------------
/**
 * �{�b�N�X���w�肵�ă|�P�����f�[�^�i�[
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   trayNum		���Ԗڂ̃{�b�N�X�Ɋi�[���邩
 * @param   poke		�|�P�����f�[�^
 *
 * @retval  BOOL		TRUE=�i�[���ꂽ�^FALSE=�󂫂�����
 */
//------------------------------------------------------------------
BOOL BOXDAT_PutPokemonBox( BOX_DATA* box, u32 trayNum, POKEMON_PASO_PARAM* poke )
{
	u32 i;

	PokePasoPara_RecoverPP(poke);

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	for(i = 0; i < BOX_MAX_POS; i++)
	{
		if( PokePasoParaGet( &(box->ppp[trayNum][i]), ID_PARA_monsno, NULL  ) == 0 )
		{
			box->ppp[trayNum][i] = *poke;
			SaveData_RequestTotalSave();
			return TRUE;
		}
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * �{�b�N�X�A�ʒu���w�肵�ă|�P�����f�[�^�i�[
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   trayNum		���Ԗڂ̃{�b�N�X�Ɋi�[���邩
 * @param   pos			�{�b�N�X���̈ʒu
 * @param   poke		�|�P�����f�[�^
 *
 * @retval  BOOL		TRUE=�i�[���ꂽ�^FALSE=�󂫂�����
 */
//------------------------------------------------------------------
BOOL BOXDAT_PutPokemonPos( BOX_DATA* box, u32 trayNum, u32 pos, POKEMON_PASO_PARAM* poke )
{
	PokePasoPara_RecoverPP(poke);

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	if(	(trayNum < BOX_MAX_TRAY)
	&&	(pos < BOX_MAX_POS)
	){
		box->ppp[trayNum][pos] = *poke;
		SaveData_RequestTotalSave();
		return TRUE;
	}
	else
	{
		GF_ASSERT(0);
	}
	return FALSE;
}





//------------------------------------------------------------------
/**
 * �ʒu���w�肵�ă{�b�N�X�̃|�P�����f�[�^�N���A
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   trayNum		���Ԗڂ̃{�b�N�X��
 * @param   pos			�{�b�N�X���̈ʒu
 *
 */
//------------------------------------------------------------------
void BOXDAT_ClearPokemon( BOX_DATA* box, u32 trayNum, u32 pos )
{
	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	if( (pos < BOX_MAX_POS) && (trayNum < BOX_MAX_TRAY) )
	{
		PokePasoParaInit( &(box->ppp[trayNum][pos]) );
		SaveData_RequestTotalSave();
	}
	else
	{
		GF_ASSERT(0);
	}
}

//------------------------------------------------------------------
/**
 * �J�����g�̃g���C�i���o�[��Ԃ�
 *
 * @param   box		�{�b�N�X�f�[�^�|�C���^
 *
 * @retval  u32		�J�����g�g���C�i���o�[
 */
//------------------------------------------------------------------
u32 BOXDAT_GetCureentTrayNumber( const BOX_DATA* box )
{
	return box->currentTrayNumber;
}
//------------------------------------------------------------------
/**
 * �P�ł��󂫂̂���g���C�i���o�[��Ԃ��i�J�����g���猟���J�n����j
 *
 * @param   box		�{�b�N�X�f�[�^�|�C���^
 *
 * @retval  u32		�󂫂̂���g���C�i���o�[�^������Ȃ���� BOXDAT_TRAYNUM_ERROR
 */
//------------------------------------------------------------------
u32 BOXDAT_GetEmptyTrayNumber( const BOX_DATA* box )
{
	int tray, pos;

	tray = box->currentTrayNumber;

	while(1)
	{
		for(pos=0; pos<BOX_MAX_POS; pos++)
		{
			if( PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[tray][pos])), ID_PARA_poke_exist, NULL  ) == 0 )
			{
				return tray;
			}
		}
		if( ++tray >= BOX_MAX_TRAY )
		{
			tray = 0;
		}
		if( tray == box->currentTrayNumber )
		{
			break;
		}
	}

	return BOXDAT_TRAYNUM_ERROR;
}
//------------------------------------------------------------------
/**
 * �󂫂̂���g���C�i���o�[�ƃg���C���̈ʒu�����o
 *
 * @param   box			[in] �{�b�N�X�f�[�^�|�C���^
 * @param   trayNum		[in|out] ���o�J�n�g���C�i���o�[���w�聨�ŏ��ɋ󂫂����������g���C�i���o�[������
 * @param   pos			[in|out] ���o�J�n�ʒu���w�聨�ŏ��ɋ󂫂����������g���C���̈ʒu������
 *
 * @retval	�󂫂�����������TRUE, ������Ȃ�������FALSE
 *
 */
//------------------------------------------------------------------
BOOL BOXDAT_GetEmptyTrayNumberAndPos( const BOX_DATA* box, int* trayNum, int* pos )
{
	int t, p;

	if( *trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		*trayNum = box->currentTrayNumber;
	}

	t = *trayNum;
	p = *pos;

	while(1)
	{
		for( ; p<BOX_MAX_POS; p++)
		{
			if( PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[t][p])), ID_PARA_poke_exist, NULL  ) == 0 )
			{
				*trayNum = t;
				*pos = p;
				return TRUE;
			}
		}
		if( ++t >= BOX_MAX_TRAY )
		{
			t = 0;
		}
		if( t == (*trayNum) )
		{
			break;
		}
		p = 0;
	}

	return BOXDAT_TRAYNUM_ERROR;
}

//------------------------------------------------------------------
/**
 * �S�̂���󂫂̐����J�E���g���ĕԂ�
 *
 * @param   box		�{�b�N�X�f�[�^�|�C���^
 *
 * @retval  u32		�󂫂̐�
 */
//------------------------------------------------------------------
u32 BOXDAT_GetEmptySpaceTotal( const BOX_DATA* box )
{
	int t, pos;
	u32 cnt;

	cnt = 0;

	for(t=0; t<BOX_MAX_TRAY; t++)
	{
		for(pos=0; pos<BOX_MAX_POS; pos++)
		{
			if( PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[t][pos])), ID_PARA_poke_exist, NULL  ) != 0 )
			{
				cnt++;
			}
		}
	}

	return cnt;
}
//------------------------------------------------------------------
/**
 * �w��g���C����󂫂̐����J�E���g���ĕԂ�
 *
 * @param   box		�{�b�N�X�f�[�^�|�C���^
 * @param   trayNum	�g���C�i���o�[
 *
 * @retval  u32		�󂫂̐�
 */
//------------------------------------------------------------------
u32 BOXDAT_GetEmptySpaceTray( const BOX_DATA* box, u32 trayNum )
{
	int pos;
	u32 cnt;

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}
	GF_ASSERT( trayNum < BOX_MAX_TRAY );


	cnt = 0;

	for(pos=0; pos<BOX_MAX_POS; pos++)
	{
		if( PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[trayNum][pos])), ID_PARA_poke_exist, NULL  ) != 0 )
		{
			cnt++;
		}
	}

	return cnt;
}
//------------------------------------------------------------------
/**
 * �J�����g�̃g���C�i���o�[���Z�b�g
 *
 * @param   box		�{�b�N�X�f�[�^�|�C���^
 * @param   num		�J�����g�g���C�i���o�[
 */
//------------------------------------------------------------------
void BOXDAT_SetCureentTrayNumber( BOX_DATA* box, u32 num )
{
	if( num < BOX_MAX_TRAY )
	{
		box->currentTrayNumber = num;
		SaveData_RequestTotalSave();
	}
	else
	{
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * �w��g���C�̕ǎ��i���o�[��Ԃ�
 *
 * @param   box				�{�b�N�X�f�[�^�|�C���^
 * @param   trayNumber		�g���C�i���o�[
 *
 * @retval  u32		�ǎ��i���o�[
 */
//------------------------------------------------------------------
u32 BOXDAT_GetWallPaperNumber( const BOX_DATA* box, u32 trayNum )
{
	if( trayNum < BOX_MAX_TRAY )
	{
		return box->wallPaper[trayNum];
	}
	else
	{
		GF_ASSERT(0);
		return 0;
	}
}
//------------------------------------------------------------------
/**
 * �w��g���C�̕ǎ��i���o�[���Z�b�g
 *
 * @param   box				�{�b�N�X�f�[�^�|�C���^
 * @param   trayNum			�g���C�i���o�[
 * @param   wallPaperNumber	�ǎ��i���o�[
 *
 */
//------------------------------------------------------------------
void BOXDAT_SetWallPaperNumber( BOX_DATA* box, u32 trayNum, u32 wallPaperNumber )
{
	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	if(	(trayNum < BOX_MAX_TRAY )
	&&	(wallPaperNumber < BOX_TOTAL_WALLPAPER_MAX )
	)
	{
		box->wallPaper[trayNum] = wallPaperNumber;
		SaveData_RequestTotalSave();
	}
	else
	{
		GF_ASSERT(0);
	}
}

//------------------------------------------------------------------
/**
 * �w��g���C�̖��O�擾
 *
 * @param   box				�{�b�N�X�f�[�^�|�C���^
 * @param   trayNumber		�g���C�i���o�[
 * @param   buf				������R�s�[��o�b�t�@
 *
 */
//------------------------------------------------------------------
void BOXDAT_GetBoxName( const BOX_DATA* box, u32 trayNumber, STRBUF* buf )
{
	if( trayNumber == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNumber = box->currentTrayNumber;
	}

	if( trayNumber < BOX_MAX_TRAY )
	{
		STRBUF_SetStringCode( buf, box->trayName[trayNumber] );
	}
	else
	{
		GF_ASSERT(0);
	}
}

//------------------------------------------------------------------
/**
 * �w��g���C�̖��O�ݒ�
 *
 * @param   box				�{�b�N�X�f�[�^�|�C���^
 * @param   trayNumber		�g���C�i���o�[
 * @param   src				���O
 *
 */
//------------------------------------------------------------------
void BOXDAT_SetBoxName( BOX_DATA* box, u32 trayNumber, const STRBUF* src )
{
	if( trayNumber == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNumber = box->currentTrayNumber;
	}

	if( trayNumber < BOX_MAX_TRAY )
	{
		STRBUF_GetStringCode( src, box->trayName[trayNumber], BOX_TRAYNAME_BUFSIZE );
		SaveData_RequestTotalSave();
	}
}
//------------------------------------------------------------------
/**
 * �w��g���C�Ɋi�[����Ă���|�P��������Ԃ�
 *
 * @param   box				�{�b�N�X�f�[�^�|�C���^
 * @param   trayNumber		�g���C�i���o�[
 *
 * @retval  u32		�g���C�Ɋi�[����Ă���|�P������
 */
//------------------------------------------------------------------
u32 BOXDAT_GetPokeExistCount( const BOX_DATA* box, u32 trayNum )
{
	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	if( trayNum < BOX_MAX_TRAY )
	{
		int i;
		u32 cnt = 0;
		for(i=0; i<BOX_MAX_POS; i++)
		{
			if(PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[trayNum][i])), ID_PARA_poke_exist, NULL ))
			{
				cnt++;
			}
		}
		return cnt;
	}
	else
	{
		GF_ASSERT(0);
	}
	return 0;
}

//------------------------------------------------------------------
/**
 * �w��g���C�Ɋi�[����Ă���|�P��������Ԃ�(�^�}�S���O)
 *
 * @param   box				�{�b�N�X�f�[�^�|�C���^
 * @param   trayNumber		�g���C�i���o�[
 *
 * @retval  u32		�g���C�Ɋi�[����Ă���|�P������
 */
//------------------------------------------------------------------
u32 BOXDAT_GetPokeExistCount2( const BOX_DATA* box, u32 trayNum )
{
	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	if( trayNum < BOX_MAX_TRAY )
	{
		int i;
		u32 cnt = 0;
		for(i=0; i<BOX_MAX_POS; i++)
		{
			if(PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[trayNum][i])), ID_PARA_poke_exist, NULL ))
			{
				if(PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[trayNum][i])), ID_PARA_tamago_flag, NULL ) == 0)	//�^�}�S���O
				{
					cnt++;
				}
			}
		}
		return cnt;
	}
	else
	{
		GF_ASSERT(0);
	}
	return 0;
}

//------------------------------------------------------------------
/**
 * �{�b�N�X�S�̂Ɋ܂܂��|�P��������Ԃ�
 *
 * @param   box		�{�b�N�X�f�[�^�|�C���^
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 BOXDAT_GetPokeExistCountTotal( const BOX_DATA* box )
{
	u32 cnt, i;

	for(i=0, cnt=0; i<BOX_MAX_TRAY; i++)
	{
		cnt += BOXDAT_GetPokeExistCount( box, i );
	}
	return cnt;
}

//------------------------------------------------------------------
/**
 * �{�b�N�X�S�̂Ɋ܂܂��|�P��������Ԃ�(�^�}�S���O�Łj
 *
 * @param   box		�{�b�N�X�f�[�^�|�C���^
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 BOXDAT_GetPokeExistCount2Total( const BOX_DATA* box )
{
	u32 cnt, i;

	for(i=0, cnt=0; i<BOX_MAX_TRAY; i++)
	{
		cnt += BOXDAT_GetPokeExistCount2( box, i );
	}
	return cnt;
}

//------------------------------------------------------------------
/**
 * �{�b�N�X�i�[�|�P�����ɑ΂���PokePasoParaGet
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   trayNum		�g���C�i���o�[
 * @param   pos			�i�[�ʒu
 * @param   param		PokePasoParaGet �p�����[�^
 * @param   buf			PokePasoParaGet �o�b�t�@
 *
 * @retval  u32			PokePasoParaGet �߂�l
 */
//------------------------------------------------------------------
u32 BOXDAT_PokeParaGet( const BOX_DATA* box, u32 trayNum, u32 pos, int param, void* buf )
{
	GF_ASSERT((trayNum<BOX_MAX_TRAY)||(trayNum == BOXDAT_TRAYNUM_CURRENT));
	GF_ASSERT(pos<BOX_MAX_POS);

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	return PokePasoParaGet( (POKEMON_PASO_PARAM*)(&box->ppp[trayNum][pos]), param, buf );
}


//------------------------------------------------------------------
/**
 * �{�b�N�X�i�[�|�P�����ɑ΂���PokePasoParaPut
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   trayNum		�g���C�i���o�[
 * @param   pos			�i�[�ʒu
 * @param   param		PokePasoParaGet �p�����[�^
 * @param   buf			PokePasoParaGet �o�b�t�@
 *
 */
//------------------------------------------------------------------
void BOXDAT_PokeParaPut( BOX_DATA* box, u32 trayNum, u32 pos, int param, void* buf )
{
	GF_ASSERT((trayNum<BOX_MAX_TRAY)||(trayNum == BOXDAT_TRAYNUM_CURRENT));
	GF_ASSERT(pos<BOX_MAX_POS);

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	PokePasoParaPut( (POKEMON_PASO_PARAM*)(&box->ppp[trayNum][pos]), param, buf );
	SaveData_RequestTotalSave();
}










//------------------------------------------------------------------
/**
 * �w��ʒu�̃|�P�����f�[�^�ւ̃|�C���^��Ԃ�
 *�i���܂�g���Ăق����͂Ȃ��j
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   boxNum		�{�b�N�X�i���o�[
 * @param   pos			
 *
 * @retval  POKEMON_PASO_PARAM*		
 */
//------------------------------------------------------------------
POKEMON_PASO_PARAM* BOXDAT_GetPokeDataAddress( const BOX_DATA* box, u32 trayNum, u32 pos )
{
	GF_ASSERT_RETURN( ((trayNum<BOX_MAX_TRAY)||(trayNum == BOXDAT_TRAYNUM_CURRENT)), NULL );
	GF_ASSERT_RETURN( (pos<BOX_MAX_POS), NULL );

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	return (POKEMON_PASO_PARAM*) &(box->ppp[trayNum][pos]);
}









//==============================================================================================
// ���������N���u�ǎ�
//==============================================================================================

//------------------------------------------------------------------
/**
 * ���������N���u�ǎ����P���A�L���ɂ���
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   number		�L���ɂ���ǎ��i���o�[
 *
 */
//------------------------------------------------------------------
void BOXDAT_SetDaisukiKabegamiFlag( BOX_DATA* box, u32 number )
{
	GF_ASSERT( number < BOX_EX_WALLPAPER_MAX );

	box->daisukiBitFlag |= (1 << number);
	SaveData_RequestTotalSave();
}

//------------------------------------------------------------------
/**
 * ���������N���u�ǎ����擾���Ă��邩�`�F�b�N
 *
 * @param   box			�{�b�N�X�f�[�^�|�C���^
 * @param   number		�`�F�b�N����ǎ��i���o�[
 *
 * @retval  BOOL		TRUE�Ŏ擾���Ă���
 */
//------------------------------------------------------------------
BOOL BOXDAT_GetDaisukiKabegamiFlag( const BOX_DATA* box, u32 number )
{
	GF_ASSERT( number < BOX_EX_WALLPAPER_MAX );

	return (box->daisukiBitFlag & (1<<number)) != 0;
}

//------------------------------------------------------------------
/**
 * �擾�������������N���u�ǎ��̑������擾
 *
 * @param   box		�{�b�N�X�f�[�^�|�C���^
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 BOXDAT_GetDaiukiKabegamiCount( const BOX_DATA* box )
{
	u32 i, cnt;

	for(i=0, cnt=0; i<BOX_EX_WALLPAPER_MAX; i++)
	{
		if( BOXDAT_GetDaisukiKabegamiFlag(box, i) )
		{
			cnt++;
		}
	}
	return cnt;
}

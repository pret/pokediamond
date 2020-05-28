//============================================================================================
/**
 * @file	poke_memo.c
 * @brief	�g���[�i�[�����f�[�^�擾
 * @author	
 * @date	
 */
//============================================================================================
#include	"common.h"
#include	"poketool/poke_tool.h"
#include	"poke_tool_def.h"
#include	"system/gamedata.h"

#include	"system/arc_tool.h"
#include	"system/arc_util.h"
#include	"system/fontproc.h"
#include	"system/msgdata.h"
#include	"system/wordset.h"
#include	"system/numfont.h"
#include	"system/buflen.h"
#include	"poketool/monsno.h"
#include	"system/pm_rtc.h"

#include	"msgdata/msg.naix"
#include	"msgdata/msg_pokestatus.h"
#include	"battle/chr_def.h"

#include	"savedata/mystatus.h"
#include	"poketool/poke_memo.h"

#include	"system/placename.h"
#include	"msgdata/msg_place_name.h"
#include	"msgdata/msg_place_name_haihu.h"
#include	"msgdata/msg_place_name_tokusyu.h"


//----------------------------------------------------------
#define PLACEID_MAP( ID )	( PlaceName_IndexToParamNumber( PLACENAME_TYPE_MAP, ID ))
#define PLACEID_GEV( ID )	( PlaceName_IndexToParamNumber( PLACENAME_TYPE_GAME_EVENT, ID ))
#define PLACEID_EEV( ID )	( PlaceName_IndexToParamNumber( PLACENAME_TYPE_EXT_EVENT, ID ))

#define PLACEID_POKEPARK			( PLACEID_MAP( MAPNAME_D10POKEPARK ))

#define PLACEID_MAX					( PLACEID_GEV( MAPNAME_SODATEYA ))

#define PLACEID_SODATEYA			( PLACEID_GEV( MAPNAME_SODATEYA ))
#define PLACEID_TABI				( PLACEID_GEV( MAPNAME_TABINOOZISAN ))
#define PLACEID_GEN					( PLACEID_GEV( MAPNAME_GEN ))

#define PLACEID_NAIBUTUUSINKOUKAN	( PLACEID_GEV( MAPNAME_NAIBUTUUSINKOUKAN ))
#define PLACEID_TUUSINKOUKAN		( PLACEID_GEV( MAPNAME_TUUSINKOUKAN ))
#define PLACEID_KANTO				( PLACEID_GEV( MAPNAME_KANTO ))
#define PLACEID_ZYOTO				( PLACEID_GEV( MAPNAME_ZYOTO ))
#define PLACEID_HOUEN				( PLACEID_GEV( MAPNAME_HOUEN ))
#define PLACEID_SINOU				( PLACEID_GEV( MAPNAME_HUSEI/* MAPNAME_SINOU */ ))
#define PLACEID_HUSEI				( PLACEID_GEV( MAPNAME_HUSEI ))
#define PLACEID_TOOKUHANARETATOTI	( PLACEID_GEV( MAPNAME_TOOKUHANARETATOTI ))

#define PLACEID_RENJA				( PLACEID_EEV( MAPNAME_RENJA ))

//----------------------------------------------------------
// �g���[�i�[�����^�C�v�h�c
enum{	
	// ���̂Ŏ擾�F�e��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�ߊl�ꏊ�j
	MEMOID_POKETYPE1 = 0,
	// ���̂Ŏ擾�F�e�s��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�ߊl�ꏊ�j
	MEMOID_POKETYPE2,
	// ���̂Ŏ擾�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�Q�[���������j
	MEMOID_POKETYPE3,	
	// �^�}�S�Ŏ擾�F�ꏊ�P�i�ʐM�����j�ꏊ�Q�i�z���ꏊ�j
	MEMOID_POKETYPE4,	
	// ���̂Ŏ擾�F�ꏊ�P�i�ʐM�����j�ꏊ�Q�i�z���ꏊ�j
	MEMOID_POKETYPE5,	
	// �^�}�S�Ŏ擾�F�ꏊ�P�i��ĉ��j�ꏊ�Q�i�z���ꏊ�j
	MEMOID_POKETYPE6,	
	// ���̂Ŏ擾�F�ꏊ�P�i��ĉ��j�ꏊ�Q�i�z���ꏊ�j
	MEMOID_POKETYPE7,
	// ���̂Ŏ擾�F�e��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�O���z�z�ꏊ�j�F�O���z�z�t���O�n�m
	MEMOID_POKETYPE8,
	// ���̂Ŏ擾�F�e�s��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�O���z�z�ꏊ�j�F�O���z�z�t���O�n�m
	MEMOID_POKETYPE9,
	// �^�}�S�Ŏ擾�F�ꏊ�P�i�O���z�z�ꏊ�j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	MEMOID_POKETYPE10,
	// ���̂Ŏ擾�F�ꏊ�P�i�O���z�z�ꏊ�j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	MEMOID_POKETYPE11,
	// �^�}�S�Ŏ擾�F�ꏊ�P�i���\�t�g�j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	MEMOID_POKETYPE12,
	// ���̂Ŏ擾�F�ꏊ�P�i���\�t�g�j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	MEMOID_POKETYPE13,
	// �^�}�S�Ŏ擾�F�ꏊ�P�i�ʐM�����j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	MEMOID_POKETYPE14,
	// ���̂Ŏ擾�F�ꏊ�P�i�ʐM�����j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	MEMOID_POKETYPE15,
	// ���̂Ŏ擾�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�|�P�����ߋ��J�[�g���b�W�j
	MEMOID_POKETYPE16,

	// �^�}�S�F�e��v�F�ꏊ�P�i��ĉ��j�ꏊ�Q�i�Ȃ��j
	MEMOID_TAMAGOTYPE1,
	// �^�}�S�F�e�s��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�ʐM�����j
	MEMOID_TAMAGOTYPE2,
	// �^�}�S�F�e��v�F�ꏊ�P�i�O���z�z�ꏊ�j�ꏊ�Q�i�Ȃ��j�F�O���z�z�t���O�n�m
	MEMOID_TAMAGOTYPE3,
	// �^�}�S�F�e�s��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�ʐM�����j�F�O���z�z�t���O�n�m
	MEMOID_TAMAGOTYPE4,
	// �^�}�S�F�e��v�F�ꏊ�P�i���\�t�g�j�ꏊ�Q�i�Ȃ��j�F�O���z�z�t���O�n�m
	MEMOID_TAMAGOTYPE5,
};

// �f�[�^�Q�ƑI��
enum{	
	DATA1 = 0,	//�f�[�^�P�Q��
	DATA2,		//�f�[�^�Q�Q��
};

static int	TrainerMemoIDGet( POKEMON_PARAM* pp, BOOL mine, int heapID );

static void character1_msgGet( TRMEMO_DATA* dat );
static void encount_msgGet( TRMEMO_DATA* dat, int msgID );
static void encountPark_msgGet( TRMEMO_DATA* dat, int msgID );
static void encountEgg_msgGet( TRMEMO_DATA* dat, int msgID,int flag );
static void character2_msgGet( TRMEMO_DATA* dat ); 
static void palate_msgGet( TRMEMO_DATA* dat );
static void eggstatus_msgGet( TRMEMO_DATA* dat );

// ���b�Z�[�W������T�C�Y
#define MSGLINE_BUFSIZ	( (2*18)*2 ) // ���[�J���C�Y���l����18word*2
#define WORDSET_NUM		(9)

// �|�P�����p�����[�^�擾
#define PARAM_GET( pp, id )			(PokeParaGet( pp, id, NULL)) 
#define PARAM_GETP( ppp, id )		(PokePasoParaGet( ppp, id, NULL)) 

// �|�P�����p�����[�^�ݒ�
#define PARAM_PUT( pp, id, buf )	(PokeParaPut( pp, id, buf)) 
#define PARAM_PUTP( ppp, id, buf )	(PokePasoParaPut( ppp, id, buf)) 

//�ȉ��A�|�P�����f�[�^�\���̍��ږ��Ǝd�l���e����v���Ȃ��̂ŕϊ�
// �g���[�i�[�����p�f�[�^�P:�ꏊ
#define	ID_PARA_trMemo1place	( ID_PARA_get_place )	
#define	ID_PARA_trMemo1year		( ID_PARA_get_year )	
#define	ID_PARA_trMemo1month	( ID_PARA_get_month )	
#define	ID_PARA_trMemo1day		( ID_PARA_get_day )	
#define	ID_PARA_trMemo2place	( ID_PARA_birth_place )	
#define	ID_PARA_trMemo2year		( ID_PARA_birth_year )	
#define	ID_PARA_trMemo2month	( ID_PARA_birth_month )	
#define	ID_PARA_trMemo2day		( ID_PARA_birth_day )	

//----------------------------------------------------------
/**
 * @brief	�g���[�i�[����������̎擾
 * @param	pp		�擾�Ώۃ|�P�����f�[�^
 * @param	heapID	�擾�p�q�[�v�w��
 * @return	msgtbl	�擾���ꂽ���b�Z�[�W�e�[�u���|�C���^
 */
//----------------------------------------------------------
// ���b�Z�[�W�\���̏�����
#define MSGDATA_INIT( msgdata ){		\
	msgdata.line	= 0;				\
	msgdata.msg		= NULL;				\
}

// ���b�Z�[�W�\���̊J��
#define MSGDATA_FREE( msgdata ){			\
	if( msgdata.msg	!= NULL ){				\
		sys_FreeMemoryEz( msgdata.msg );	\
	}										\
}

// ���i���b�Z�[�W�擾
#define GET_CHARCTER1( linenum ){		\
	dat->character1.line = linenum;		\
	character1_msgGet( dat );			\
}

// �o������b�Z�[�W�擾
#define GET_ENCOUNT( linenum, msgID ){	\
	dat->encount.line = linenum;		\
	encount_msgGet( dat, msgID );		\
}

// �o����i�^�}�S�j���b�Z�[�W�擾
#define GET_ENCOUNTEGG( linenum, msgID, flag ){	\
	dat->encount.line = linenum;				\
	encountEgg_msgGet( dat, msgID, flag );		\
}

// ���i�Q���b�Z�[�W�擾
#define GET_CHARCTER2( linenum ){	\
	dat->character2.line = linenum;	\
	character2_msgGet( dat );		\
}

// ���o���b�Z�[�W�擾
#define GET_PALATE( linenum ){		\
	dat->palate.line = linenum;		\
	palate_msgGet( dat );			\
}

// �^�}�S��ԃ��b�Z�[�W�擾
#define GET_EGGSTATUS( linenum ){	\
	dat->eggstatus.line = linenum;	\
	eggstatus_msgGet( dat );		\
}

TRMEMO_DATA*	TrainerMemoGet( POKEMON_PARAM* pp, BOOL mine, int heapID )
{
	TRMEMO_DATA* dat;

	dat = sys_AllocMemory( heapID, sizeof( TRMEMO_DATA ) );
	dat->heapID = heapID;
	dat->msg_man = MSGMAN_Create
		( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_pokestatus_dat, dat->heapID );
	dat->word_set = WORDSET_CreateEx( WORDSET_NUM, WORDSET_DEFAULT_BUFLEN, dat->heapID );
	dat->pp = pp;
	dat->mine = mine;

	{
		//���b�Z�[�W�z��̏�����
		MSGDATA_INIT( dat->character1 )
		MSGDATA_INIT( dat->encount )
		MSGDATA_INIT( dat->character2 )
		MSGDATA_INIT( dat->palate )
		MSGDATA_INIT( dat->eggstatus )
	}
	
	switch( TrainerMemoIDGet( dat->pp, dat->mine, dat->heapID ) ){

	// ���̂Ŏ擾�F�e��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�ߊl�ꏊ�j
	case MEMOID_POKETYPE1:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_01_01 )
		GET_CHARCTER2( 6 )
		GET_PALATE( 7 )
		break;
	
	// ���̂Ŏ擾�F�e�s��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�ߊl�ꏊ�j
	case MEMOID_POKETYPE2:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_01_02 )
		GET_CHARCTER2( 6 )
		GET_PALATE( 7 )
		break;
	
	// ���̂Ŏ擾�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�Q�[���������j
	case MEMOID_POKETYPE3:	
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_02_01 )
		GET_CHARCTER2( 6 )
		GET_PALATE( 7 )
		break;
	
	// �^�}�S�Ŏ擾�F�ꏊ�P�i�ʐM�����j�ꏊ�Q�i�z���ꏊ�j
	case MEMOID_POKETYPE4:	
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_03_01 )
		GET_CHARCTER2( 8 )
		GET_PALATE( 9 )
		break;
	
	// ���̂Ŏ擾�F�ꏊ�P�i�ʐM�����j�ꏊ�Q�i�z���ꏊ�j
	case MEMOID_POKETYPE5:	
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_03_02 )
		GET_CHARCTER2( 8 )
		GET_PALATE( 9 )
		break;
	
	// �^�}�S�Ŏ擾�F�ꏊ�P�i��ĉ��j�ꏊ�Q�i�z���ꏊ�j
	case MEMOID_POKETYPE6:	
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_04_01 )
		GET_CHARCTER2( 8 )
		GET_PALATE( 9 )
		break;
	
	// ���̂Ŏ擾�F�ꏊ�P�i��ĉ��j�ꏊ�Q�i�z���ꏊ�j
	case MEMOID_POKETYPE7:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_04_02 )
		GET_CHARCTER2( 8 )
		GET_PALATE( 9 )
		break;
	
	// ���̂Ŏ擾�F�e��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�O���z�z�ꏊ�j�F�O���z�z�t���O�n�m
	case MEMOID_POKETYPE8:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_05_01 )
		GET_CHARCTER2( 7 )
		GET_PALATE( 8 )
		break;
	
	// ���̂Ŏ擾�F�e�s��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�O���z�z�ꏊ�j�F�O���z�z�t���O�n�m
	case MEMOID_POKETYPE9:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_05_02 )
		GET_CHARCTER2( 7 )
		GET_PALATE( 8 )
		break;
	
	// �^�}�S�Ŏ擾�F�ꏊ�P�i�O���z�z�ꏊ�j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	case MEMOID_POKETYPE10:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_06_01 )
		GET_CHARCTER2( 9 )
		break;
	
	// ���̂Ŏ擾�F�ꏊ�P�i�O���z�z�ꏊ�j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	case MEMOID_POKETYPE11:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_06_02 )
		GET_CHARCTER2( 9 )
		break;
	
	// �^�}�S�Ŏ擾�F�ꏊ�P�i���\�t�g�j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	case MEMOID_POKETYPE12:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_07_01 )
		GET_CHARCTER2( 9 )
		break;
	
	// ���̂Ŏ擾�F�ꏊ�P�i���\�t�g�j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	case MEMOID_POKETYPE13:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_07_02 )
		GET_CHARCTER2( 9 )
		break;
	
	// �^�}�S�Ŏ擾�F�ꏊ�P�i�ʐM�����j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	case MEMOID_POKETYPE14:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_08_01 )
		GET_CHARCTER2( 9 )
		break;
	
	// ���̂Ŏ擾�F�ꏊ�P�i�ʐM�����j�ꏊ�Q�i�z���ꏊ�j�F�O���z�z�t���O�n�m
	case MEMOID_POKETYPE15:
		GET_CHARCTER1( 1 )
		GET_ENCOUNT( 2, mes_status_03_03_08_02 )
		GET_CHARCTER2( 9 )
		break;
	
	// ���̂Ŏ擾�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�|�P�����ߋ��J�[�g���b�W�j
	case MEMOID_POKETYPE16:
		GET_CHARCTER1( 1 )
		dat->encount.line = 2;
		encountPark_msgGet( dat, mes_status_03_03_09_01 );
		GET_CHARCTER2( 6 )
		GET_PALATE( 7 )
		break;
	
	// �^�}�S�F�e��v�F�ꏊ�P�i��ĉ��j�ꏊ�Q�i�Ȃ��j
	case MEMOID_TAMAGOTYPE1:
		GET_ENCOUNTEGG( 1, mes_status_03_T_01_01_01, DATA1 )
		GET_EGGSTATUS( 6 )
		break;

	// �^�}�S�F�e�s��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�ʐM�����j
	case MEMOID_TAMAGOTYPE2:
		GET_ENCOUNTEGG( 1, mes_status_03_T_01_02_01, DATA2 )
		GET_EGGSTATUS( 6 )
		break;

	// �^�}�S�F�e��v�F�ꏊ�P�i�O���z�z�ꏊ�j�ꏊ�Q�i�Ȃ��j�F�O���z�z�t���O�n�m
	case MEMOID_TAMAGOTYPE3:
		GET_ENCOUNTEGG( 1, mes_status_03_T_01_03_01, DATA1 )
		GET_EGGSTATUS( 6 )
		break;

	// �^�}�S�F�e�s��v�F�ꏊ�P�i�Ȃ��j�ꏊ�Q�i�ʐM�����j�F�O���z�z�t���O�n�m
	case MEMOID_TAMAGOTYPE4:
		GET_ENCOUNTEGG( 1, mes_status_03_T_01_03_01, DATA2 )
		GET_EGGSTATUS( 6 )
		break;

	// �^�}�S�F�e��v�F�ꏊ�P�i���\�t�g�j�ꏊ�Q�i�Ȃ��j�F�O���z�z�t���O�n�m
	case MEMOID_TAMAGOTYPE5:
		GET_ENCOUNTEGG( 1, mes_status_03_T_01_04_01, DATA1 )
		GET_EGGSTATUS( 6 )
		break;
	}
	return dat;
}

//----------------------------------------------------------
/**
 * @brief	�g���[�i�[����������̊J��
 * @param	msgtbl	�擾����Ă��郁�b�Z�[�W�e�[�u���|�C���^
 */
//----------------------------------------------------------
void	TrainerMemoFree( TRMEMO_DATA* dat )
{
	MSGDATA_FREE( dat->character1 )
	MSGDATA_FREE( dat->encount )
	MSGDATA_FREE( dat->character2 )
	MSGDATA_FREE( dat->palate )
	MSGDATA_FREE( dat->eggstatus )

	WORDSET_Delete( dat->word_set );
	//���b�Z�[�W�f�[�^�j��
	MSGMAN_Delete( dat->msg_man );

	sys_FreeMemoryEz( dat );
}

//----------------------------------------------------------
/**
 * @brief	�g���[�i�[����������̍쐬
 * @param	pp		�擾�Ώۃ|�P�����f�[�^
 * @return	void*	������f�[�^
 */
//----------------------------------------------------------
static void character1_msgGet( TRMEMO_DATA* dat )
{
	int charID = PokeSeikakuGet( dat->pp );		//���i�擾

	if( charID > CHR_MAX ){
		return;
	}
	//������o�b�t�@�̊m��
	dat->character1.msg = STRBUF_Create( MSGLINE_BUFSIZ, dat->heapID );

	//������̎擾
	//���i�̒l��msg_status_03_01�i����΂��j��0�Ƃ��A���b�Z�[�W�h�c�Ɠ��ꏇ�ɂȂ��Ă���
	MSGMAN_GetString( dat->msg_man, (mes_status_03_02_01 + charID), dat->character1.msg );
}

//----------------------------------------------------------
// �ꏊ�̃��[�h�ݒ�
#define WSET_PLACE1( buf ){																\
	WORDSET_RegisterPokeGetPlace														\
		( dat->word_set, buf, PARAM_GET( dat->pp, ID_PARA_trMemo1place ) );				\
}
#define WSET_PLACE2( buf ){																\
	WORDSET_RegisterPokeGetPlace														\
		( dat->word_set, buf, PARAM_GET( dat->pp, ID_PARA_trMemo2place ) );				\
}
// �N�����̃��[�h�ݒ�
#define WSET_TIMEDATA1( yearbuf, monthbuf, daybuf ){									\
	WORDSET_RegisterNumber(	dat->word_set, yearbuf,										\
							PARAM_GET( dat->pp, ID_PARA_trMemo1year ),					\
							2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );			\
	WORDSET_RegisterNumber(	dat->word_set, monthbuf,									\
							PARAM_GET( dat->pp, ID_PARA_trMemo1month ),					\
							2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );			\
	WORDSET_RegisterNumber(	dat->word_set, daybuf,										\
							PARAM_GET( dat->pp, ID_PARA_trMemo1day ),					\
							2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );			\
}
#define WSET_TIMEDATA2( yearbuf, monthbuf, daybuf ){									\
	WORDSET_RegisterNumber(	dat->word_set, yearbuf,										\
							PARAM_GET( dat->pp, ID_PARA_trMemo2year ),					\
							2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );			\
	WORDSET_RegisterNumber(	dat->word_set, monthbuf,									\
							PARAM_GET( dat->pp, ID_PARA_trMemo2month ),					\
							2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );			\
	WORDSET_RegisterNumber(	dat->word_set, daybuf,										\
							PARAM_GET( dat->pp, ID_PARA_trMemo2day ),					\
							2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );			\
}
// ���x���̃��[�h�ݒ�
#define WSET_LEVEL( buf ){																\
	WORDSET_RegisterNumber(	dat->word_set, buf,											\
							PARAM_GET( dat->pp, ID_PARA_get_level ),					\
							3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );			\
}

#define ENCOUNT_BUFSIZ		( MSGLINE_BUFSIZ * 8 )	//�ő�W���C��

static void encount_msgGet( TRMEMO_DATA* dat, int msgID )
{
	STRBUF*	msg_tmp = STRBUF_Create( ENCOUNT_BUFSIZ, dat->heapID );

	dat->encount.msg = STRBUF_Create( ENCOUNT_BUFSIZ, dat->heapID );//�o�b�t�@�̊m��

	MSGMAN_GetString( dat->msg_man, msgID, msg_tmp );

	WSET_TIMEDATA2( 0, 1, 2 )
	WSET_LEVEL( 3 )
	WSET_PLACE2( 4 )
	WSET_TIMEDATA1( 5, 6, 7 )
	WSET_PLACE1( 8 )
	WORDSET_ExpandStr( dat->word_set, dat->encount.msg, msg_tmp );

	STRBUF_Delete( msg_tmp );
}

#define ENCOUNTPARK_BUFSIZ		( MSGLINE_BUFSIZ * 4 )	//�S���C��

static void encountPark_msgGet( TRMEMO_DATA* dat, int msgID )
{
	STRBUF*	msg_tmp = STRBUF_Create( ENCOUNTPARK_BUFSIZ, dat->heapID );

	dat->encount.msg = STRBUF_Create( ENCOUNTPARK_BUFSIZ, dat->heapID );//�o�b�t�@�̊m��

	MSGMAN_GetString( dat->msg_man, msgID, msg_tmp );

	WSET_TIMEDATA2( 0, 1, 2 )
	WSET_LEVEL( 3 )
	switch( PARAM_GET( dat->pp, ID_PARA_get_cassette ) ){
	default:
		WORDSET_RegisterPokeGetPlace( dat->word_set, 4, PLACEID_HUSEI );
		break;
	case VERSION_RED:
	case VERSION_GREEN:
		WORDSET_RegisterPokeGetPlace( dat->word_set, 4, PLACEID_KANTO );
		break;
	case VERSION_GOLD:
	case VERSION_SILVER:
		WORDSET_RegisterPokeGetPlace( dat->word_set, 4, PLACEID_ZYOTO );
		break;
	case VERSION_RUBY:
	case VERSION_SAPPHIRE:
	case VERSION_EMERALD:
		WORDSET_RegisterPokeGetPlace( dat->word_set, 4, PLACEID_HOUEN );
		break;
	case VERSION_COLOSSEUM:
		WORDSET_RegisterPokeGetPlace( dat->word_set, 4, PLACEID_TOOKUHANARETATOTI );
		break;
	case VERSION_DIAMOND:
	case VERSION_PEARL:
		WORDSET_RegisterPokeGetPlace( dat->word_set, 4, PLACEID_SINOU );
		break;
	}
	WORDSET_ExpandStr( dat->word_set, dat->encount.msg, msg_tmp );

	STRBUF_Delete( msg_tmp );
}

#define ENCOUNTEGG_BUFSIZ		( MSGLINE_BUFSIZ * 5 )	//�ő�T���C��

static void encountEgg_msgGet( TRMEMO_DATA* dat, int msgID, int flag )
{
	STRBUF*	msg_tmp = STRBUF_Create( ENCOUNTEGG_BUFSIZ, dat->heapID );

	dat->encount.msg = STRBUF_Create( ENCOUNTEGG_BUFSIZ, dat->heapID );//�o�b�t�@�̊m��

	MSGMAN_GetString( dat->msg_man, msgID, msg_tmp );

	if( flag == DATA1 ){
		WSET_TIMEDATA1( 5, 6, 7 )
		WSET_PLACE1( 8 )
	} else {
		WSET_TIMEDATA2( 5, 6, 7 )
		WSET_PLACE2( 8 )
	}
	WORDSET_ExpandStr( dat->word_set, dat->encount.msg, msg_tmp );

	STRBUF_Delete( msg_tmp );
}

//----------------------------------------------------------
#define CHR2PARAM0 ( PARAM_GET( dat->pp, ID_PARA_hp_rnd ) )
#define CHR2PARAM1 ( PARAM_GET( dat->pp, ID_PARA_pow_rnd ) )
#define CHR2PARAM2 ( PARAM_GET( dat->pp, ID_PARA_def_rnd ) )
#define CHR2PARAM3 ( PARAM_GET( dat->pp, ID_PARA_agi_rnd ) )
#define CHR2PARAM4 ( PARAM_GET( dat->pp, ID_PARA_spepow_rnd ) )
#define CHR2PARAM5 ( PARAM_GET( dat->pp, ID_PARA_spedef_rnd ) )

#define CHR2PARAM_PRI_ID ( PARAM_GET( dat->pp, ID_PARA_personal_rnd )%6 )

#define C2_TABERU_SUKI		( mes_status_03_05_01_00 )
#define C2_HIRUNE_YOKUSURU	( mes_status_03_05_01_01 )
#define C2_INEMURI_OOI		( mes_status_03_05_01_02 )
#define C2_MONO_TIRAKASU	( mes_status_03_05_01_03 )
#define C2_NONBIRI_SUKI		( mes_status_03_05_01_04 )
#define C2_TIKARA_ZIMAN		( mes_status_03_05_02_00 )
#define C2_ABARE_SUKI		( mes_status_03_05_02_01 )
#define C2_OKORIPPOI		( mes_status_03_05_02_02 )
#define C2_KENKA_SUKI		( mes_status_03_05_02_03 )
#define C2_TINOKE_OOI		( mes_status_03_05_02_04 )
#define C2_KARADA_JYOUBU	( mes_status_03_05_03_00 )
#define C2_UTARE_TUYOI		( mes_status_03_05_03_01 )
#define C2_NEBARI_TUYOI		( mes_status_03_05_03_02 )
#define C2_SINBOU_TUYOI		( mes_status_03_05_03_03 )
#define C2_GAMAN_TUYOI		( mes_status_03_05_03_04 )
#define C2_KAKEKKO_SUKI		( mes_status_03_05_04_00 )
#define C2_MONOOTO_BINKAN	( mes_status_03_05_04_01 )
#define C2_OTTYOKOTYOI		( mes_status_03_05_04_02 )
#define C2_OTYOUSIMONO		( mes_status_03_05_04_03 )
#define C2_NIGERU_HAYAI		( mes_status_03_05_04_04 )
#define C2_KOUKISIN_TUYOI	( mes_status_03_05_05_00 )
#define C2_ITAZURA_SUKI		( mes_status_03_05_05_01 )
#define C2_NUKEME_NAI		( mes_status_03_05_05_02 )
#define C2_KANGAEGOTO_OOI	( mes_status_03_05_05_03 )
#define C2_KITYOUMEN		( mes_status_03_05_05_04 )
#define C2_KI_TUYOI			( mes_status_03_05_06_00 )
#define C2_MIEPPARI			( mes_status_03_05_06_01 )
#define C2_MAKENKI_TUYOI	( mes_status_03_05_06_02 )
#define C2_MAKEZU_KIRAI		( mes_status_03_05_06_03 )
#define C2_GOUJYOU			( mes_status_03_05_06_04 )

// ���i�Q�e�[�u��
static const u16 charcter2_tbl[6][5] = {
{ C2_TABERU_SUKI,	C2_HIRUNE_YOKUSURU, C2_INEMURI_OOI,		C2_MONO_TIRAKASU,	C2_NONBIRI_SUKI },
{ C2_TIKARA_ZIMAN,	C2_ABARE_SUKI,		C2_OKORIPPOI,		C2_KENKA_SUKI,		C2_TINOKE_OOI },
{ C2_KARADA_JYOUBU, C2_UTARE_TUYOI,		C2_NEBARI_TUYOI,	C2_SINBOU_TUYOI,	C2_GAMAN_TUYOI },
{ C2_KAKEKKO_SUKI,	C2_MONOOTO_BINKAN,	C2_OTTYOKOTYOI,		C2_OTYOUSIMONO,		C2_NIGERU_HAYAI },
{ C2_KOUKISIN_TUYOI,C2_ITAZURA_SUKI,	C2_NUKEME_NAI,		C2_KANGAEGOTO_OOI,	C2_KITYOUMEN },
{ C2_KI_TUYOI,		C2_MIEPPARI,		C2_MAKENKI_TUYOI,	C2_MAKEZU_KIRAI,	C2_GOUJYOU },
};

#define	PARAM_CHECK( num ){			\
	if( param_org < param[num] ){	\
		param_ID = num;				\
		param_org = param[num];		\
	}								\
}

static void character2_msgGet( TRMEMO_DATA* dat ) 
{
	int param[6],param_ID,param_org;
	int	i,msgID;

	//������o�b�t�@�̊m��
	dat->character2.msg = STRBUF_Create( MSGLINE_BUFSIZ, dat->heapID );

	param[0] = CHR2PARAM0;
	param[1] = CHR2PARAM1;
	param[2] = CHR2PARAM2;
	param[3] = CHR2PARAM3;
	param[4] = CHR2PARAM4;
	param[5] = CHR2PARAM5;

	//�v���C�I���e�B�[�ɂ��ő�p�����[�^�h�c�̎擾�@���x�^�����܂�������
	switch( CHR2PARAM_PRI_ID ){
	default:
	case 0:
		param_ID = 0;
		param_org = param[0];
		PARAM_CHECK( 1 )
		PARAM_CHECK( 2 )
		PARAM_CHECK( 3 )
		PARAM_CHECK( 4 )
		PARAM_CHECK( 5 )
		break;
	case 1:
		param_ID = 1;
		param_org = param[1];
		PARAM_CHECK( 2 )
		PARAM_CHECK( 3 )
		PARAM_CHECK( 4 )
		PARAM_CHECK( 5 )
		PARAM_CHECK( 0 )
		break;
	case 2:
		param_ID = 2;
		param_org = param[2];
		PARAM_CHECK( 3 )
		PARAM_CHECK( 4 )
		PARAM_CHECK( 5 )
		PARAM_CHECK( 0 )
		PARAM_CHECK( 1 )
		break;
	case 3:
		param_ID = 3;
		param_org = param[3];
		PARAM_CHECK( 4 )
		PARAM_CHECK( 5 )
		PARAM_CHECK( 0 )
		PARAM_CHECK( 1 )
		PARAM_CHECK( 2 )
		break;
	case 4:
		param_ID = 4;
		param_org = param[4];
		PARAM_CHECK( 5 )
		PARAM_CHECK( 0 )
		PARAM_CHECK( 1 )
		PARAM_CHECK( 2 )
		PARAM_CHECK( 3 )
		break;
	case 5:
		param_ID = 5;
		param_org = param[5];
		PARAM_CHECK( 0 )
		PARAM_CHECK( 1 )
		PARAM_CHECK( 2 )
		PARAM_CHECK( 3 )
		PARAM_CHECK( 4 )
		break;
	}
	msgID = charcter2_tbl[ param_ID ][ (param_org % 5)];

	MSGMAN_GetString( dat->msg_man, msgID, dat->character2.msg );
}

//----------------------------------------------------------
#define PLT_KARAI	( mes_status_03_04_01 )
#define PLT_SIBUI	( mes_status_03_04_02 )
#define PLT_AMAI	( mes_status_03_04_03 )
#define PLT_NIGAI	( mes_status_03_04_04 )
#define PLT_SUPPAI	( mes_status_03_04_05 )
#define PLT_ALL		( mes_status_03_04_06 )

#define PLTTYPE_MAX	(5)
#define PLT_LIKE	(1)

// ���o�e�[�u��
static const u16 palate_tbl[6] = 
	{ PLT_ALL, PLT_KARAI, PLT_SIBUI, PLT_AMAI, PLT_NIGAI, PLT_SUPPAI };

static void palate_msgGet( TRMEMO_DATA* dat ) 
{
	int	i,pltID,msgID;

	//������o�b�t�@�̊m��
	dat->palate.msg = STRBUF_Create( MSGLINE_BUFSIZ, dat->heapID );

	pltID = 0;

	// ���o�D�ݎ擾�F�D��(=1)�͈�킵�����݂��Ȃ�
	for(i=0;i<PLTTYPE_MAX;i++){
		if( PokeParaLikeTasteCheck( dat->pp, i ) == PLT_LIKE ){
			pltID = i+1;
		}
	}
	msgID = palate_tbl[ pltID ];

	MSGMAN_GetString( dat->msg_man, msgID, dat->palate.msg );
}

//----------------------------------------------------------
#define EGGSTATUS_LIMIT1	( 5 )
#define EGGSTATUS_LIMIT2	( 10 )
#define EGGSTATUS_LIMIT3	( 40 )

#define EGGSTATUS_BUFSIZ	( MSGLINE_BUFSIZ * 4 )	//�ő�S���C��

static void eggstatus_msgGet( TRMEMO_DATA* dat ) 
{
	int status = PARAM_GET( dat->pp, ID_PARA_friend );		//�Ȃ��x�擾
	int	msgID;

	//������o�b�t�@�̊m��
	dat->eggstatus.msg = STRBUF_Create( EGGSTATUS_BUFSIZ, dat->heapID );

	if( status <= EGGSTATUS_LIMIT1 ){
		msgID = mes_status_03_T_02_01;
	} else if( status <= EGGSTATUS_LIMIT2 ){
		msgID = mes_status_03_T_02_02;
	} else if( status <= EGGSTATUS_LIMIT3 ){
		msgID = mes_status_03_T_02_03;
	} else {
		msgID = mes_status_03_T_02_04;
	}

	MSGMAN_GetString( dat->msg_man, msgID, dat->eggstatus.msg );
}


//----------------------------------------------------------
/**
 * @brief	�g���[�i�[�����^�C�v�̎擾
 * @param	pp		�擾�Ώۃ|�P�����f�[�^
 * @return	memoID	�g���[�i�[�����^�C�vID
 */
//----------------------------------------------------------
//----------------------------------------------------------
// �^�}�S���ǂ����̔���
#define if_MONSNO_neq_TAMAGO_pp( pp )	(PARAM_GET( pp, ID_PARA_tamago_flag) == 0)
#define if_MONSNO_neq_TAMAGO_ppp( ppp )	(PARAM_GETP( ppp, ID_PARA_tamago_flag) == 0)

// �|�P�������^�}�S��Ԃŕ߂܂������ǂ����i�ꏊ�f�[�^�P��0�̎��̓^�}�S����z���Ă��Ȃ��j
#define if_GETSTATUS_neq_TAMAGO	(PARAM_GET(pp, ID_PARA_trMemo1place) == 0)
// �O���z�z�t���O���n�m���ǂ���
#define if_POKEHAIFU_equ_ON		(PARAM_GET(pp, ID_PARA_event_get_flag) == 1) 
// �ꏊ�P�̈�v�m�F
#define if_POKEGET1ID_equ( placeID )	(PARAM_GET(pp, ID_PARA_trMemo1place) == placeID )
// �ꏊ�Q�̈�v�m�F
#define if_POKEGET2ID_equ( placeID )	(PARAM_GET(pp, ID_PARA_trMemo2place) == placeID )

static int	TrainerMemoIDGet( POKEMON_PARAM* pp, BOOL mine, int heapID )
{
	int		ret_code	= 0;

	//�^�}�S����
	if( if_MONSNO_neq_TAMAGO_pp( pp ) ){
		//�|�P�����p����
	
		//�|�P�������^�}�S��Ԃŕ߂܂������ǂ���
		if( if_GETSTATUS_neq_TAMAGO ){
			//���̂Ŏ擾�����|�P�����i�ꏊ�f�[�^�Q�Q�Ɓj
			
			if( if_POKEGET2ID_equ( PLACEID_POKEPARK ) ){
				// �ꏊ�Q���|�P�p�[�N�̏ꍇ
				ret_code = MEMOID_POKETYPE16;
			} else if( if_POKEHAIFU_equ_ON ){
				// �O���z�z�t���O���n�m�̏ꍇ
				if( mine == TRUE ){// �e�Ƃh�c�̈�v����
					ret_code = MEMOID_POKETYPE8;
				} else {
					ret_code = MEMOID_POKETYPE9;
				}
			} else if( if_POKEGET2ID_equ( PLACEID_NAIBUTUUSINKOUKAN ) ){
				// �ꏊ�Q���Q�[���������̏ꍇ
				ret_code = MEMOID_POKETYPE3;
			} else {
				// ���̑��ʏ�F�ߊl��
				if( mine == TRUE ){// �e�Ƃh�c�̈�v����
					ret_code = MEMOID_POKETYPE1;
				} else {
					ret_code = MEMOID_POKETYPE2;
				}
			}
		} else {
			//�^�}�S����z�����|�P�����i�ꏊ�f�[�^�P�Q�Ɓj
			if( if_POKEHAIFU_equ_ON ){
				// �O���z�z�t���O���n�m�̏ꍇ

				if( if_POKEGET1ID_equ( PLACEID_TUUSINKOUKAN ) ){
					// �ꏊ�P���g���[�h�̐ݒ肪����Ă���ꍇ
					if( mine == TRUE ){// �e�Ƃh�c�̈�v����
						ret_code = MEMOID_POKETYPE14;
					} else {
						ret_code = MEMOID_POKETYPE15;
					}
				} else if( if_POKEGET1ID_equ( PLACEID_RENJA ) ){
					// �ꏊ�P�������W���[�̐ݒ肪����Ă���ꍇ
					if( mine == TRUE ){// �e�Ƃh�c�̈�v����
						ret_code = MEMOID_POKETYPE12;
					} else {
						ret_code = MEMOID_POKETYPE13;
					}
				} else {
					// �ꏊ�P�����̑��̐ݒ肪����Ă���ꍇ�F�C�x���g��
					if( mine == TRUE ){// �e�Ƃh�c�̈�v����
						ret_code = MEMOID_POKETYPE10;
					} else {
						ret_code = MEMOID_POKETYPE11;
					}
				}
			} else {
				if( if_POKEGET1ID_equ( PLACEID_NAIBUTUUSINKOUKAN )
					||if_POKEGET1ID_equ( PLACEID_SODATEYA )
					||if_POKEGET1ID_equ( PLACEID_TABI )
					||if_POKEGET1ID_equ( PLACEID_GEN ) ){
					// �ꏊ�P���Q�[���������̏ꍇ
					if( mine == TRUE ){// �e�Ƃh�c�̈�v����
						ret_code = MEMOID_POKETYPE6;
					} else {
						ret_code = MEMOID_POKETYPE7;
					}
				} else {
					// ���̑��F�ʐM������
					if( mine == TRUE ){// �e�Ƃh�c�̈�v����
						ret_code = MEMOID_POKETYPE4;
					} else {
						ret_code = MEMOID_POKETYPE5;
					}
				}
			}
		}
		
	} else {
		//�^�}�S�p����
		
		// �e�Ƃh�c�̈�v����
		if( mine == TRUE ){// �e�Ƃh�c�̈�v����
			// �����̃^�}�S�i�ꏊ�f�[�^�P�Q�Ɓj
			if( if_POKEHAIFU_equ_ON ){
				// �O���z�z�t���O���n�m�̏ꍇ
				if( if_POKEGET1ID_equ( PLACEID_RENJA ) ){
					//�����W���[�̏ꍇ
					ret_code = MEMOID_TAMAGOTYPE5;
				} else {
					ret_code = MEMOID_TAMAGOTYPE3;
				}
			} else {
				//�ʏ�^�}�S
				ret_code = MEMOID_TAMAGOTYPE1;
			}
		} else {
			// �����������i�ꏊ�f�[�^�Q�Q�Ɓj
			if( if_POKEHAIFU_equ_ON ){
				//�O���z�z�^�}�S
				ret_code = MEMOID_TAMAGOTYPE4;
			} else {
				//�ʏ�^�}�S
				ret_code = MEMOID_TAMAGOTYPE2;
			}
		}
	}
	return ret_code;
}





//----------------------------------------------------------
/**
 * @brief	�g���[�i�[�����̐ݒ�
 * @param	pp or ppp	�ݒ�Ώۃ|�P�����f�[�^
 * @param	setID		�ݒ�h�c
 * @param	placeID		�ݒ�n���h�c�i�ߊl�̂݁H�j
 */
//----------------------------------------------------------
static void TrainerMemoOyaSet( POKEMON_PASO_PARAM* ppp, MYSTATUS* my, int heapID );
static void TrainerMemoPlaceDaySet( POKEMON_PASO_PARAM* ppp, int placeID, int datanum );
static void TrainerMemoPlaceDayClr( POKEMON_PASO_PARAM* ppp, int datanum );
static void TrainerMemoLvlSet( POKEMON_PASO_PARAM* ppp );
static void TrainerMemoEvfSet( POKEMON_PASO_PARAM* ppp );

void	TrainerMemoSetPP(	POKEMON_PARAM* pp, MYSTATUS* my, 
							TRMEMO_SETID setID, int placeID, int heapID )
{
	TrainerMemoSetPPP( &pp->ppp, my, setID, placeID, heapID );
}


void	TrainerMemoSetPPP(	POKEMON_PASO_PARAM* ppp, MYSTATUS* my, 
							TRMEMO_SETID setID, int placeID, int heapID )
{
	switch( setID ){

	//�ʏ�擾�i�ߊl���j
	case TRMEMO_POKE_PLACESET:
		if( placeID > PLACEID_MAX ){
			placeID = 0;
		}
		if( if_MONSNO_neq_TAMAGO_ppp( ppp ) ){
			//�|�P����
			TrainerMemoPlaceDayClr( ppp, DATA1 );
			TrainerMemoPlaceDaySet( ppp, placeID, DATA2 );
			TrainerMemoLvlSet( ppp );
		} else {
			//�^�}�S
			TrainerMemoPlaceDaySet( ppp, placeID, DATA1 );
			TrainerMemoPlaceDayClr( ppp, DATA2 );
		}
		TrainerMemoOyaSet( ppp, my, heapID );
		break;

	//�Q�[��������
	case TRMEMO_OFFTRADE_PLACESET:
		if( if_MONSNO_neq_TAMAGO_ppp( ppp ) ){
			//�|�P����
			TrainerMemoPlaceDayClr( ppp, DATA1 );
			TrainerMemoPlaceDaySet( ppp, PLACEID_NAIBUTUUSINKOUKAN, DATA2 );
			TrainerMemoLvlSet( ppp );
		} else {
			//�^�}�S
			TrainerMemoPlaceDayClr( ppp, DATA1 );
			TrainerMemoPlaceDaySet( ppp, PLACEID_NAIBUTUUSINKOUKAN, DATA2 );
		}
		break;

	//�|�P�p�[�N
	case TRMEMO_POKEPARK_PLACESET:
		//�|�P����
		TrainerMemoPlaceDayClr( ppp, DATA1 );
		TrainerMemoPlaceDaySet( ppp, PLACEID_POKEPARK, DATA2 );
		TrainerMemoLvlSet( ppp );
		break;

	//��ĉ��i�^�}�S�̂݁j
	case TRMEMO_SODATEYA_PLACESET:
		TrainerMemoPlaceDaySet( ppp, placeID, DATA1 );
		TrainerMemoPlaceDayClr( ppp, DATA2 );
		TrainerMemoOyaSet( ppp, my, heapID );
		break;

	//�O���z�z
	case TRMEMO_FUSHIGI_PLACESET:
		//�e�̖��O�A�h�c�A���ʂ̓Z�b�g����Ă��邱�Ƃ��O��
		if( PokemonOyaCheckPPP( ppp, my, heapID ) == TRUE ){
			if( if_MONSNO_neq_TAMAGO_ppp( ppp ) ){
				//�|�P����
				TrainerMemoPlaceDayClr( ppp, DATA1 );
				TrainerMemoPlaceDaySet( ppp, placeID, DATA2 );
				TrainerMemoLvlSet( ppp );
			} else {
				//�^�}�S
				TrainerMemoPlaceDaySet( ppp, placeID, DATA1 );
				TrainerMemoPlaceDayClr( ppp, DATA2 );
			}
		} else {
			if( if_MONSNO_neq_TAMAGO_ppp( ppp ) ){
				//�|�P����
				TrainerMemoPlaceDayClr( ppp, DATA1 );
				TrainerMemoPlaceDaySet( ppp, placeID, DATA2 );
				TrainerMemoLvlSet( ppp );
			} else {
				//�^�}�S
				TrainerMemoPlaceDayClr( ppp, DATA1 );
				TrainerMemoPlaceDaySet( ppp, placeID, DATA2 );
			}
		}
		TrainerMemoEvfSet( ppp );
		break;

	//�ʐM����
	case TRMEMO_ONTRADE_PLACESET:
		if( if_MONSNO_neq_TAMAGO_ppp( ppp ) ){
			//�|�P�����i�����Ȃ��j
		} else {
			//�^�}�S
			TrainerMemoPlaceDaySet( ppp, PLACEID_TUUSINKOUKAN, DATA2 );
		}
		break;

	//�^�}�S�z��
	case TRMEMO_EGGBIRTH_PLACESET:
		if( placeID > PLACEID_MAX ){
			placeID = 0;
		}
		if( PokemonOyaCheckPPP( ppp, my, heapID ) == FALSE ){
			{
				//������^�}�S
				int data;

				data = PARAM_GETP( ppp, ID_PARA_trMemo2place );
				PARAM_PUTP( ppp, ID_PARA_trMemo1place, &data );
				data = PARAM_GETP( ppp, ID_PARA_trMemo2year );
				PARAM_PUTP( ppp, ID_PARA_trMemo1year, &data );
				data = PARAM_GETP( ppp, ID_PARA_trMemo2month );
				PARAM_PUTP( ppp, ID_PARA_trMemo1month, &data );
				data = PARAM_GETP( ppp, ID_PARA_trMemo2day );
				PARAM_PUTP( ppp, ID_PARA_trMemo1day, &data );
			}
		}
		TrainerMemoPlaceDaySet( ppp, placeID, DATA2 );
		TrainerMemoOyaSet( ppp, my, heapID );
		break;
	}
}

//----------------------------------------------------------
// �e�̐ݒ�
static void TrainerMemoOyaSet( POKEMON_PASO_PARAM* ppp, MYSTATUS* my, int heapID )
{
	int	myID	= MyStatus_GetID( my );
	int	mysex	= MyStatus_GetMySex( my );
	STRBUF*	myname	= MyStatus_CreateNameString( my, heapID );

	PARAM_PUTP( ppp, ID_PARA_id_no, &myID );
	PARAM_PUTP( ppp, ID_PARA_oyasex, &mysex );
	PARAM_PUTP( ppp, ID_PARA_oyaname_buf, myname );

	STRBUF_Delete( myname );
}

//----------------------------------------------------------
// �ꏊ�Ɠ��t�̐ݒ�
static void TrainerMemoPlaceDaySet( POKEMON_PASO_PARAM* ppp, int placeID, int datanum )
{
	RTCDate	rtc_d;

	GF_RTC_GetDate(&rtc_d);

	//�ߊl�����Z�b�g
	if( datanum == DATA1 ){
		PARAM_PUTP( ppp, ID_PARA_trMemo1place,	&placeID );
		PARAM_PUTP( ppp, ID_PARA_trMemo1year,	&rtc_d.year );
		PARAM_PUTP( ppp, ID_PARA_trMemo1month,	&rtc_d.month );
		PARAM_PUTP( ppp, ID_PARA_trMemo1day,	&rtc_d.day ); 
	} else {
		PARAM_PUTP( ppp, ID_PARA_trMemo2place,	&placeID );
		PARAM_PUTP( ppp, ID_PARA_trMemo2year,	&rtc_d.year );
		PARAM_PUTP( ppp, ID_PARA_trMemo2month,	&rtc_d.month );
		PARAM_PUTP( ppp, ID_PARA_trMemo2day,	&rtc_d.day ); 
	}
}

//----------------------------------------------------------
// �ꏊ���t�̃N���A
static void TrainerMemoPlaceDayClr( POKEMON_PASO_PARAM* ppp, int datanum )
{
	int data = 0;

	if( datanum == DATA1 ){
		PARAM_PUTP( ppp, ID_PARA_trMemo1place,	&data );
		PARAM_PUTP( ppp, ID_PARA_trMemo1year,	&data );
		PARAM_PUTP( ppp, ID_PARA_trMemo1month,	&data );
		PARAM_PUTP( ppp, ID_PARA_trMemo1day,	&data ); 
	} else {
		PARAM_PUTP( ppp, ID_PARA_trMemo2place,	&data );
		PARAM_PUTP( ppp, ID_PARA_trMemo2year,	&data );
		PARAM_PUTP( ppp, ID_PARA_trMemo2month,	&data );
		PARAM_PUTP( ppp, ID_PARA_trMemo2day,	&data ); 
	}
}
//----------------------------------------------------------
// ���x���̐ݒ�
static void TrainerMemoLvlSet( POKEMON_PASO_PARAM* ppp )
{
	int level = PARAM_GETP( ppp, ID_PARA_level );

	PARAM_PUTP( ppp, ID_PARA_get_level, &level );
}
//----------------------------------------------------------
// �O���z�z�t���O�̐ݒ�
static void TrainerMemoEvfSet( POKEMON_PASO_PARAM* ppp )
{
	int event_get_flag = 1;

	PARAM_PUTP( ppp, ID_PARA_event_get_flag, &event_get_flag );
}


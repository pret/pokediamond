//============================================================================================
/**
 * @file	poketch_data.c
 * @bfief	�|�P�b�`�f�[�^�A�N�Z�X�p�\�[�X
 * @author	taya GAME FREAK inc.
 * @date	2005.10.27
 */
//============================================================================================

#include "system/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "common.h"
#include "gflib/system.h"
#include "system/savedata.h"
#include "poketool\pokeicon.h"

#include "field/poketch_data.h"



//============================================================================================
//============================================================================================
enum {
	APP_REGIST_MAX = 32,	///< �A�v���̍ő吔�ƍ���Ȃ����A�Z�[�u�f�[�^�T�C�Y�������肽���Ȃ��̂ł��̂܂�
	POKETCH_DEFAULT_APPNO = POKETCH_APPID_DWATCH,	// �f�t�H���g�œo�^����Ă�A�v��
};


//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�|�P�b�`�f�[�^�p�\���̒�`
 */
//----------------------------------------------------------
struct _POKETCH_DATA {
	u8		get_flag : 1;		///< �|�P�b�`���擾�����t���O
	u8		pedometer_flag : 1;	///< �A�v���w�����v�x���擾�����t���O
	u8		dotart_modified_flag : 1;	///< �A�v���w�h�b�g�A�[�g�x�ҏW�����t���O
	u8		color_type : 3;		///< �J���[�^�C�v�i0�`7�j
	u8		 : 2;

	s8		app_count;			///< �o�^����Ă���A�v����
	s8		app_index;			///< ���ݕ\�����̃A�v���i�o�^�e�[�u���C���f�b�N�X�j


	u8		app_flag[APP_REGIST_MAX];	///< �擾�����A�v��ID�o�^�e�[�u��

	u32		pedometer;			///< �w�����v�x����

	u16		alarm_switch : 1;		///< �A�v���w�A���[�����v�x�X�C�b�`
	u16		alarm_hour   : 5;		///< �A�v���w�A���[�����v�x��
	u16		alarm_minute : 6;		///< �A�v���w�A���[�����v�x��
	u16		 : 4;

	//-------------------
	u8		dotart_data[POKETCH_DOTART_DATA_BYTESIZE];	///< �w�h�b�g�A�[�g�x�ۑ��f�[�^

	//-------------------
	u32		calendar_markbit;	///< �w�J�����_�[�x�}�[�N�r�b�g�t���O
	u8		calendar_month;		///< �w�J�����_�[�x�}�[�N������

	//-------------------
	struct {
		u8   x;
		u8   y;
	}mark_map_pos[ POKETCH_MAP_MARK_MAX ];	///< �w�}�b�v�}�[�L���O�x�}�[�N�ʒu

	//--------------------
	struct {
		u16  monsno;
		u16  iconPattern;
	}poke_history[ POKETCH_POKE_HISTORY_COUNT_MAX ];

};

//============================================================================================
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//============================================================================================

//------------------------------------------------------------------
/**
 * ���[�N�T�C�Y�擾
 *
 * @retval  int		���[�N�T�C�Y
 */
//------------------------------------------------------------------
int PoketchData_GetWorkSize(void)
{
	return sizeof(POKETCH_DATA);
}
//------------------------------------------------------------------
/**
 * ���[�N�p���������A���P�[�g�����������ĕԂ�
 *
 * @param   heapID		�A���P�[�g�p�q�[�v�h�c
 *
 * @retval  POKETCH_DATA *		�������ς݃��[�N�̈�̃|�C���^
 */
//------------------------------------------------------------------
POKETCH_DATA * PoketchData_AllocWork(u32 heapID)
{
	POKETCH_DATA * pk;
	pk = sys_AllocMemory(heapID, sizeof(POKETCH_DATA));
	PoketchData_Init( pk );
	return pk;
}

//============================================================================================
//	POKETCH_DATA����̂��߂̊֐�
//============================================================================================

//------------------------------------------------------------------
/**
 * ���[�N�̈揉����
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void PoketchData_Init(POKETCH_DATA* poketch_data)
{
	enum {
		DEFAULT_APPNO = POKETCH_APPID_DWATCH,
	};

	int i;

	for(i=0; i<APP_REGIST_MAX; i++)
	{
		poketch_data->app_flag[i] = 0;
	}
	poketch_data->app_count = 0;
	poketch_data->app_index = 0;
	poketch_data->get_flag = FALSE;
	poketch_data->color_type = POKETCH_COLOR_TYPE0;

	// �����v
	poketch_data->pedometer_flag = FALSE;
	poketch_data->pedometer = 0;

	// �A���[�����v
	poketch_data->alarm_switch = FALSE;
	poketch_data->alarm_hour = 0;
	poketch_data->alarm_minute = 0;

	// �J�����_�[
	poketch_data->calendar_month = 1;
	poketch_data->calendar_markbit = 0;

	// �}�[�L���O�}�b�v
	{
		static const struct {
			u8  x;
			u8  y;
		}initialPos[POKETCH_MAP_MARK_MAX] = {
			{ 104, 152 }, { 120, 152 }, { 136, 152 },
			{ 152, 152 }, { 168, 152 }, { 184, 152 },
		};
		for(i=0; i<POKETCH_MAP_MARK_MAX; i++)
		{
			poketch_data->mark_map_pos[i].x = initialPos[i].x;
			poketch_data->mark_map_pos[i].y = initialPos[i].y;
		}
	}

	// �|�P�����q�X�g���[
	for(i=0; i<POKETCH_POKE_HISTORY_COUNT_MAX; i++)
	{
		poketch_data->poke_history[i].monsno = 0;
		poketch_data->poke_history[i].iconPattern = 0;
	}

	// �h�b�g�A�[�g
	poketch_data->dotart_modified_flag = 0;



	PoketchData_AddApplication(poketch_data, DEFAULT_APPNO);
}
//------------------------------------------------------------------
/**
 * �|�P�b�`����ɓ��ꂽ�t���O���Z�b�g����
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void PoketchData_SetPoketchGetFlag( POKETCH_DATA* poketch_data )
{
	poketch_data->get_flag = TRUE;
}
//------------------------------------------------------------------
/**
 * �|�P�b�`����ɓ��ꂽ�t���O���擾����
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
BOOL PoketchData_GetPoketchGetFlag( POKETCH_DATA* poketch_data )
{
	return poketch_data->get_flag;
}
//------------------------------------------------------------------
/**
 * �o�^����Ă���A�v���P�[�V�����̐����擾
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 * @retval  int		�o�^����Ă���A�v���P�[�V�����̐�
 */
//------------------------------------------------------------------
int PoketchData_GetApplicationCount(const POKETCH_DATA * poketch_data)
{
	return poketch_data->app_count;
}
//------------------------------------------------------------------
/**
 * ���Ƃ����A�v����o�^�ł��邩�擾
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 * @retval  int		�����o�^�ł��邩
 */
//------------------------------------------------------------------
int PoketchData_GetRestApplicationSpace( POKETCH_DATA* poketch_data )
{
	return POKETCH_APPID_MAX - poketch_data->app_count;
}
//------------------------------------------------------------------
/**
 * ���łɃA�v�����o�^����Ă��邩�`�F�b�N
 *
 * @param   poketch_data	���[�N�|�C���^
 * @param   app_id			�A�v���P�[�V����ID
 *
 * @retval  BOOL	TRUE�œo�^�ς�
 */
//------------------------------------------------------------------
BOOL PoketchData_CheckApplicationRegisterd( POKETCH_DATA* poketch_data, int app_id )
{
	return poketch_data->app_flag[app_id];
}
//------------------------------------------------------------------
/**
 * �V�����A�v���P�[�V������ǉ�
 *
 * @param   poketch_data		���[�N�|�C���^
 * @param   app_id				�A�v���P�[�V����ID
 *
 * @retval  BOOL		TRUE�œo�^�����^FALSE�Ŏ��s�i���������ς��j
 */
//------------------------------------------------------------------
BOOL PoketchData_AddApplication(POKETCH_DATA * poketch_data, int app_id)
{
	GF_ASSERT( app_id >= 0 && app_id < POKETCH_APPID_MAX );

	if( poketch_data->app_count < POKETCH_APPID_MAX )
	{
		if( poketch_data->app_flag[ app_id ] == FALSE )
		{
			poketch_data->app_flag[ app_id ] = TRUE;
			poketch_data->app_count++;

			if( app_id == POKETCH_APPID_PEDOMETER )
			{
				poketch_data->pedometer_flag = TRUE;
			}

			return TRUE;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * ���ݕ\�����̃A�v���P�[�V����ID���擾
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 * @retval  int		�A�v���P�[�V����ID
 *
 * ���A�v���P�[�V����ID = ���v�A���������A�A�v���̎�ނ����ʂ���ID.
 */
//------------------------------------------------------------------
int PoketchData_GetNowApplication(const POKETCH_DATA* poketch_data)
{
	return poketch_data->app_index;
}
//------------------------------------------------------------------
/**
 * �\�����A�v�����P�O�֐؂�ւ���
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 * @retval  int		�؂�ւ���̃A�v���P�[�V�����ԍ�
 */
//------------------------------------------------------------------
int PoketchData_SetApplicationPosNext( POKETCH_DATA* poketch_data )
{
	int  i = poketch_data->app_index;

	while(1)
	{
		if( ++i >= POKETCH_APPID_MAX )
		{
			i = 0;
		}
		if( i == poketch_data->app_index )
		{
			break;
		}
		if( poketch_data->app_flag[i] )
		{
			break;
		}
	}
	poketch_data->app_index = i;
	return poketch_data->app_index;
}
//------------------------------------------------------------------
/**
 * �\�����A�v�����P���֐؂�ւ���
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 * @retval  int		�؂�ւ���̃A�v���P�[�V�����ԍ�
 */
//------------------------------------------------------------------
int PoketchData_SetApplicationPosPrev( POKETCH_DATA* poketch_data )
{
	int  i = poketch_data->app_index;

	while(1)
	{
		if( --i < 0 )
		{
			i = POKETCH_APPID_MAX - 1;
		}
		if( i == poketch_data->app_index )
		{
			break;
		}
		if( poketch_data->app_flag[i] )
		{
			break;
		}
	}
	poketch_data->app_index = i;
	return poketch_data->app_index;
}
//------------------------------------------------------------------
/**
 * �\�����A�v�����w��o�^�ԍ��̕��ɐ؂�ւ���
 *
 * @param   poketch_data	���[�N�|�C���^
 * @param   pos				�o�^�ԍ�
 *
 */
//------------------------------------------------------------------
void PoketchData_SetApplicationPos( POKETCH_DATA* poketch_data, int pos )
{
	if( pos >= 0 && pos < poketch_data->app_count )
	{
		int i;
		for(i=0; i<POKETCH_APPID_MAX; i++)
		{
			if( poketch_data->app_flag[i] )
			{
				if( pos == 0 )
				{
					poketch_data->app_index = i;
					break;
				}
				else
				{
					pos--;
				}
			}
		}
		
	}
	else
	{
		GF_ASSERT(0);
	}
}

//------------------------------------------------------------------
/**
 * �J���[�^�C�v���擾
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 * @retval  u32		�J���[�^�C�v
 */
//------------------------------------------------------------------
u32 PoketchData_GetColorType( const POKETCH_DATA* poketch_data )
{
	GF_ASSERT(poketch_data);
	return poketch_data->color_type;
}
//------------------------------------------------------------------
/**
 * �J���[�^�C�v��ݒ�
 *
 * @param   poketch_data		���[�N�|�C���^
 */
//------------------------------------------------------------------
void PoketchData_SetColorType( POKETCH_DATA* poketch_data, u32 color_type )
{
	GF_ASSERT(poketch_data);
	GF_ASSERT(color_type < POKETCH_COLOR_TYPE_MAX);
	poketch_data->color_type = color_type;
}

//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * �w�����v�x�̕������擾
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 * @retval  u32		�����v����
 */
//------------------------------------------------------------------
u32 PoketchData_GetPedometer( const POKETCH_DATA* poketch_data )
{
	return poketch_data->pedometer;
}
//------------------------------------------------------------------
/**
 * �w�����v�x�̕������Z�b�g
 *
 * @param   poketch_data		���[�N�|�C���^
 * @param   pos					�Z�b�g�������
 */
//------------------------------------------------------------------
void PoketchData_SetPedometer( POKETCH_DATA* poketch_data, u32 count )
{
	if( poketch_data->pedometer_flag )
	{
		poketch_data->pedometer = count;
	}
}

//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * �w�A���[�����v�x�̃X�C�b�`�I���^�I�t�t���O���擾
 *
 * @param   poketch_data		���[�N�|�C���^
 *
 * @retval  BOOL			
 */
//------------------------------------------------------------------
BOOL PoketchData_GetAlarmSwitchFlag( const POKETCH_DATA* poketch_data )
{
	return poketch_data->alarm_switch;
}
//------------------------------------------------------------------
/**
 * �w�A���[�����v�x�̐ݒ莞�����擾
 *
 * @param   poketch_data		���[�N�|�C���^
 * @param   hour				�ݒ莞���i���j���󂯎��ϐ��̃|�C���^
 * @param   min					�ݒ莞���i���j���󂯎��ϐ��̃|�C���^
 *
 */
//------------------------------------------------------------------
void PoketchData_GetAlarmTime( const POKETCH_DATA* poketch_data, u32* hour, u32* min )
{
	*hour = poketch_data->alarm_hour;
	*min = poketch_data->alarm_minute;
}
//------------------------------------------------------------------
/**
 * �w�A���[�����v�x�̐ݒ�X�V
 *
 * @param   poketch_data	���[�N�|�C���^
 * @param   switch_flag		�X�C�b�`�I���^�I�t�t���O
 * @param   hour			�ݒ莞���i���j
 * @param   min				�ݒ莞���i���j
 *
 */
//------------------------------------------------------------------
void PoketchData_SetAlarm( POKETCH_DATA* poketch_data, BOOL switch_flag, u32 hour, u32 min )
{
	poketch_data->alarm_switch = switch_flag;
	poketch_data->alarm_hour = hour;
	poketch_data->alarm_minute = min;
}

//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * �J�����_�[�̓��t�r�b�g���Z�b�g
 *
 * @param   poketch_data	�|�P�b�`�f�[�^�|�C���^
 * @param   month			�Z�b�g���錎
 * @param   day				�Z�b�g�����
 *
 */
//------------------------------------------------------------------
void PoketchData_Calendar_SetMark( POKETCH_DATA* poketch_data, u32 month, u32 day )
{
	if( poketch_data->calendar_month == month )
	{
		poketch_data->calendar_markbit |= (1 << (day-1));
	}
	else
	{
		poketch_data->calendar_month = month;
		poketch_data->calendar_markbit = (1 << (day-1));
	}
}
//------------------------------------------------------------------
/**
 * �J�����_�[�̓��t�r�b�g���N���A
 *
 * @param   poketch_data	�|�P�b�`�f�[�^�|�C���^
 * @param   month			�N���A���錎
 * @param   day				�N���A�����
 *
 */
//------------------------------------------------------------------
void PoketchData_Calendar_ClearMark( POKETCH_DATA* poketch_data, u32 month, u32 day )
{
	if( poketch_data->calendar_month == month )
	{
		poketch_data->calendar_markbit &= ~(1 << (day-1));
	}
	else
	{
		poketch_data->calendar_month = month;
		poketch_data->calendar_markbit = 0;
	}
}
//------------------------------------------------------------------
/**
 * �J�����_�[�̓��t�r�b�g���擾
 *
 * @param   poketch_data	�|�P�b�`�f�[�^�|�C���^
 * @param   month			��
 * @param   day				��
 *
 * @retval  BOOL		TRUE�Ȃ�r�b�gON
 */
//------------------------------------------------------------------
BOOL PoketchData_Calendar_GetMark( const POKETCH_DATA* poketch_data, u32 month, u32 day )
{
	if( poketch_data->calendar_month == month )
	{
		return (poketch_data->calendar_markbit >> (day-1)) & 1;
	}
	else
	{
		return FALSE;
	}
}


//==============================================================================================
//==============================================================================================

void PoketchData_MarkMap_SetMarkPos( POKETCH_DATA* poketch_data, int id, u8 x, u8 y )
{
	GF_ASSERT(id < POKETCH_MAP_MARK_MAX);

	poketch_data->mark_map_pos[id].x = x;
	poketch_data->mark_map_pos[id].y = y;
}
void PoketchData_MarkMap_GetMarkPos( const POKETCH_DATA* poketch_data, int id, u8* x, u8* y )
{
	GF_ASSERT(id < POKETCH_MAP_MARK_MAX);

	*x = poketch_data->mark_map_pos[id].x;
	*y = poketch_data->mark_map_pos[id].y;
}

//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * �A�v���w�h�b�g�A�[�g�x�@��x�ł����e���ҏW���ꂽ���Ƃ����邩�H
 *
 * @param   poketch_data		�|�P�b�`�f�[�^�|�C���^
 *
 * @retval  BOOL		TRUE�ŕҏW���ꂽ���Ƃ���
 */
//------------------------------------------------------------------
BOOL PoketchData_DotArt_GetModifiedFlag( const POKETCH_DATA* poketch_data )
{
	return poketch_data->dotart_modified_flag;
}
//------------------------------------------------------------------
/**
 * �A�v���w�h�b�g�A�[�g�x	�r�b�g�f�[�^�擾
 *
 * @param   poketch_data		�|�P�b�`�f�[�^�|�C���^
 * @param   dst					�f�[�^�擾��o�b�t�@
 *
 */
//------------------------------------------------------------------
void PoketchData_DotArt_GetBitData( const POKETCH_DATA* poketch_data, u8* dst )
{
	if( poketch_data->dotart_modified_flag )
	{
		MI_CpuCopy8( poketch_data->dotart_data, dst, POKETCH_DOTART_DATA_BYTESIZE );
	}
}
//------------------------------------------------------------------
/**
 * �A�v���w�h�b�g�A�[�g�x	�ҏW�����r�b�g�f�[�^�ۑ�
 *
 * @param   poketch_data		�|�P�b�`�f�[�^�|�C���^
 * @param   src					�r�b�g�f�[�^�A�h���X
 *
 */
//------------------------------------------------------------------
void PoketchData_DotArt_SetBitData( POKETCH_DATA* poketch_data, const u8* src )
{
	MI_CpuCopy8( src, poketch_data->dotart_data, POKETCH_DOTART_DATA_BYTESIZE );
	poketch_data->dotart_modified_flag = 1;
}



//==============================================================================================
// �|�P�����q�X�g���[�i��ɓ��ꂽ�|�P�������L�^�j
//==============================================================================================


//------------------------------------------------------------------
/**
 * �w�|�P�����q�X�g���[�x�L�^�ǉ�
 *
 * @param   poketch_data		�|�P�b�`�f�[�^�|�C���^
 * @param   ppp					�|�P�����p�����[�^
 *
 */
//------------------------------------------------------------------
void PoketchData_PokeHistory_Add( POKETCH_DATA* poketch_data, const POKEMON_PASO_PARAM* ppp )
{
	int max;

	max = PoketchData_PokeHistory_GetRecordCount( poketch_data );
	if( max >= POKETCH_POKE_HISTORY_COUNT_MAX )
	{
		int i;
		for(i=0; i<(POKETCH_POKE_HISTORY_COUNT_MAX-1); i++)
		{
			poketch_data->poke_history[i] = poketch_data->poke_history[i+1];
		}
		max = POKETCH_POKE_HISTORY_COUNT_MAX - 1;
	}

	poketch_data->poke_history[max].monsno = PokePasoParaGet((POKEMON_PASO_PARAM*)ppp, ID_PARA_monsno, NULL);
	poketch_data->poke_history[max].iconPattern = PokeIconCgxPatternGet( ppp );
}

//------------------------------------------------------------------
/**
 * �w�|�P�����q�X�g���[�x�L�^������Ԃ�
 *
 * @param   poketch_data		�|�P�b�`�f�[�^�|�C���^
 *
 * @retval  int		�L�^����
 */
//------------------------------------------------------------------
int PoketchData_PokeHistory_GetRecordCount( const POKETCH_DATA* poketch_data )
{
	int i;
	for(i=0; i<POKETCH_POKE_HISTORY_COUNT_MAX; i++)
	{
		if( poketch_data->poke_history[i].monsno == 0 )
		{
			return i;
		}
	}
	return i;
}

//------------------------------------------------------------------
/**
 * �w�|�P�����q�X�g���[�x�L�^���ꂽ�f�[�^���擾
 *
 * @param   poketch_data	�|�P�b�`�f�[�^�|�C���^
 * @param   index			������ 0origin �C���f�b�N�X
 * @param   monsno			[out]�����X�^�[�i���o�[���󂯎��
 * @param   iconPattern		[out]�A�C�R���p�^�[���i���o�[���󂯎��
 *
 */
//------------------------------------------------------------------
void PoketchData_PokeHistory_GetRecord( const POKETCH_DATA* poketch_data, int index, int* monsno, int* iconPattern )
{
	GF_ASSERT(index<POKETCH_POKE_HISTORY_COUNT_MAX);
	GF_ASSERT(poketch_data->poke_history[index].monsno);

	*monsno = poketch_data->poke_history[index].monsno;
	*iconPattern = poketch_data->poke_history[index].iconPattern;
}



//============================================================================================
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//============================================================================================
POKETCH_DATA * SaveData_GetPoketchData(SAVEDATA * sv)
{
	POKETCH_DATA * pk;
	pk = SaveData_Get(sv, GMDATA_ID_POKETCH_DATA);
	return pk;
}



//============================================================================================
//	�f�o�b�O�p
//============================================================================================
#ifdef PM_DEBUG
void PoketchData_AddAllApplication( POKETCH_DATA* poketch_data )
{
	#if 1
	int i;
	for(i=0; i<POKETCH_APPID_MAX; i++)
	{
		if(i == POKETCH_DEFAULT_APPNO)
		{
			continue;
		}
		PoketchData_AddApplication(poketch_data, i);
	}
	#else
	PoketchData_AddApplication(poketch_data, POKETCH_APPID_POKELIST);
	PoketchData_AddApplication(poketch_data, POKETCH_APPID_KITCHEN_TIMER);
	PoketchData_AddApplication(poketch_data, POKETCH_APPID_PEDOMETER );
	#endif
}
#endif

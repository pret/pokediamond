
#include <nitro.h>
#include "agbpoke_access.h"
#include "agbromheader.h"
#include "rsindex.h"
//#include "AgbFlash.h"
#include "scrn_id.h"

typedef struct
{
  u32 initial_code;
  u8 version;
  u8 cas_version;
  u16 country;
} AGBSOFT_TYPE;

typedef struct {

	u8	data[SVLD_DATA_SIZE];	//�Z�[�u�f�[�^

	u16	blocknum;	//�u���b�N�i���o�[
	u16	sumcheck;	//�T���`�F�b�N�f�[�^
	u32	save_id;	//�Z�[�u���ʃf�[�^
	u32	save_count;	//�Z�[�u�J�E���^�[�i�����j
}SVLDSYS_DATA;



#define SVLD_MIRROR_SIZE	(14)
#define	SVLD_ID				(0x08012025)	//�w�b�_�X�e�[�^�X��`�i�Q�[���F�؂h�c�j
#define	SVLD_BLOCK_SIZE		(0xf80)		//�Z�N�^������̃Z�[�u�f�[�^�T�C�Y

static POKEMON_ROM_HEADER _pokeromheader;

static int check_agb(const AGBSOFT_TYPE *list, int size);
static const AGBSOFT_TYPE support_softs[30];
static u8 nintendo_logo[0xa0 - 4];

static const AGBSOFT_TYPE *_softtype = NULL;

static int _newer_sector;
static u32 _counter;
AGBPOKE_SAVEDATA *_data;

static int s_savingsector = 0;
// �O�Ԃ�����Z�N�^
static int _startsector;

static u16 LoadStatusCheck( void *buffer, int *newsector, u32 *main_counter);

static BOOL flash_init()
{
	if( CTRDG_IdentifyAgbBackup(CTRDG_BACKUP_TYPE_FLASH_1M) != 0 )
	{
		return FALSE;
	}
	return TRUE;
}

//==============================================================================
/**
 * agbpoke_*���Ăяo�����O�ɁA���̊֐����R�[�����Ă��������B
 * @retval  TRUE�c�����������@FALSE�c���������s
 */
//==============================================================================
int agbpoke_init( void *buffer )
{
	_data = (AGBPOKE_SAVEDATA *) buffer;
	if( _softtype != NULL ) 
	{
	  //		OS_Panic("agbpoke_init���ȑO�Ăяo����Ă��܂��B");
		return AGBPOKE_ERROR_OTHER;
	}
	
	{
		int ret = check_agb( support_softs, 30 );
		if( ret != AGBPOKE_ERROR_OK ) return ret;
	}
	

	if( _softtype->version == SOFTTYPE_RS  /* && _softtype->country == LANGTYPE_JP */ )
	{
		// ���r�T�t�@���{��ŁE�k�Ĕł̂݁A�����w�b�_�ɑΉ����Ă��Ȃ��B
		// �g�����̂݃R�s�[
		_pokeromheader.MyData_size = RSINDEX_MYDATASIZE;
		_pokeromheader.Fld_size	= RSINDEX_FLDSIZE;
		_pokeromheader.event_flag_offset = RSINDEX_EVENTFLAG;
		_pokeromheader.pokecen_flg = RSINDEX_SAVESTATEFLAG;
	}
	else
	{
		CTRDG_CpuCopy32( (void*)0x08000100, (void*)&_pokeromheader, sizeof(POKEMON_ROM_HEADER));
	}

	// �t���b�V���̏������B�K���C�j�V�����R�[�h���m�F���Ă���I	
	if( !flash_init() )
	{
		OS_TPrintf("�t���b�V���������Ɏ��s\n");
		return AGBPOKE_ERROR_NOFLASH;
	}
	else
	{
		OS_TPrintf("�t���b�V������������\n");
	}

	return AGBPOKE_ERROR_OK;
}

void agbpoke_preinit(void)
{
  _softtype = NULL;
}

//==============================================================================
/**
 * �������Ă���\�t�g�̃C�j�V�����R�[�h���擾���܂��B
 * @retval  TRUE�c�����������@FALSE�c���������s
 */
//==============================================================================
u32 agbpoke_getInitialCode()
{
  return _softtype->initial_code;
}

//==============================================================================
/**
 * �������Ă���|�P�����\�t�g�̃Q�[����ނ�Ԃ��܂��B
 * @retval  �J�Z�b�g�̃|�P�����^�C�v
 */
//==============================================================================
int agbpoke_getPokemonType()
{
  return _softtype->cas_version;
}

//==============================================================================
/**
 * �������Ă���|�P�����\�t�g�̌����Ԃ��B
 * @retval  �J�Z�b�g�̌���
 */
//==============================================================================
int agbpoke_getPokemonLanguage()
{
  return _softtype->country;
}

//==============================================================================
/**
 * AGB�J�[�h���������������Ă��邩�A�O����ɔ��肵�܂��B
 * AGB�X���b�g�̉��ꓙ�ŁA�f�[�^�����̊댯���Ȃ��悤�A
 * �K���������ޑO�ɂ��̊֐��Ŕ��肷�邱�ƁB
 * @param   list, �C�j�V�����R�[�h�̃��X�g�B
 * @param   size, �C�j�V�����R�[�h�̃��X�g�̍��ڐ��B
 * @retval  NULL�c���s�A����ȊO�c��v�����C�j�V�����R�[�h�ւ̃|�C���^
 */
//==============================================================================
static int check_agb(const AGBSOFT_TYPE *list, int size)
{
	u32 code;
	_softtype = NULL;
	// �J�[�g���b�W�X���b�g�ɃJ�[�g���b�W���������Ă��邩����
	if( !CTRDG_IsAgbCartridge() ) return AGBPOKE_ERROR_NOROM;
	
	// �C�j�V�����R�[�h���擾�B
	code = CTRDG_GetAgbGameCode();
	{
		int i;
		for( i = 0; i < size; i++ )
		{
			if( list[i].initial_code == code ) 
			{
				_softtype = list + i;	
				break;
			}
		}
		if( _softtype == NULL )
		{
			OS_TPrintf("�C�j�V�����R�[�h����v���܂���B\n");
			return AGBPOKE_ERROR_NOTPOKEMON;
		}
	}

	// �C�j�V�����R�[�h�Ɉ�v�����̂ŁA������ǂݏo���̋���
	CTRDG_Enable( TRUE );
	
	// �����w�b�_�����擾�B
	{
		u32 romheader[0xc0/4];
		u8 *castdata = (u8*)&(romheader[0]);
		CTRDG_CpuCopy32( (void*)0x08000000, (void*)&(romheader[0]), 0xc0);
		// �C�V�����S�`�F�b�N�B
		{
			int i;
			for(i = 0; i < sizeof(nintendo_logo); i++)
			{
				if( nintendo_logo[i] != castdata[4 + i] )
				{
					OS_TPrintf("�C�V�����S����v���܂���B\n");	
					return AGBPOKE_ERROR_READ;
				}
			}
		}
		// �␔�`�F�b�N���s���B
		{
			int i;
			u8 sum = 0;
			for( i = 0xa0; i <= 0xbc; i++)
			{
				sum += castdata[i];
			}
			sum = (u8)(-(sum + 0x19));
			if( castdata[0xbd] != sum )
			{
				OS_TPrintf("�␔�`�F�b�N�Ɏ��s���܂����B\n");
				return AGBPOKE_ERROR_READ;
			}
		}
	}
	
	return AGBPOKE_ERROR_OK;
}

//*************************************************************************
//=========================================================================
//				�T�u���[�`��
//=========================================================================
//*************************************************************************
static	u16	SumCheckCalc(u32* dat_adr, u16 size)
{
	u16	i;
	u32	sumcheck;

	sumcheck = 0;
	for(i = 0; i < (size / 4); i++){
		sumcheck += *dat_adr;
		dat_adr++;
	}
	return	(u16)(((sumcheck >> 16) & 0xffff) + (sumcheck & 0xffff));
}

static u32 loadNormalFile3(const char* path, void *dest, int index, int size) 
{
	// �t�@�C���V�X�e�����烍�[�h
	FSFile f;
	u32 l2;

	if(!FS_IsAvailable()){
		OS_Printf("file Init error!!\n");	
		return 0;
	}
	FS_InitFile(&f);
	if(!FS_OpenFile( &f, path)) {
		OS_Printf("file open error!!");	
		return 0;
	}
	
	l2 = FS_GetLength( &f );
	(void)FS_SeekFile( &f, index, FS_SEEK_SET );
	(void)FS_ReadFile( &f, dest, size );
	(void)FS_CloseFile(&f);
	
	return l2;	
}

static void LoadSector(int i, void *dest)
{
	// SDK���o���������
//	loadNormalFile3( "savedata050916_repair.bin", dest, i * SVLD_SECTOR_SIZE, SVLD_SECTOR_SIZE);
#if 0
  {
    int v;
    u8 *p = (u8 *)dest;
    OS_Printf("B: ");
    for(v = SVLD_DATA_SIZE; v < SVLD_DATA_SIZE+16; v++)	OS_Printf("%02X ", p[v]);
    OS_Printf("\n");

  CTRDG_ReadAgbFlash((u16)i, 0, dest, SVLD_SECTOR_SIZE);
    OS_Printf("A: ");
    for(v = SVLD_DATA_SIZE; v < SVLD_DATA_SIZE+16; v++)	OS_Printf("%02X ", p[v]);
    OS_Printf("\n");
  }
#else
  CTRDG_ReadAgbFlash((u16)i, 0, dest, SVLD_SECTOR_SIZE);
#endif
#pragma unused(i, dest)
}

static u16 getSectorSize(int no)
{
	if( no == 0 ) return (u16)(_pokeromheader.MyData_size);
	if( no == 4 ) return (u16)(_pokeromheader.Fld_size - SVLD_BLOCK_SIZE * 3);
	if( no == 13 ) return sizeof(POKEBOX_SAVE_DATA) - SVLD_BLOCK_SIZE * 8;
	return SVLD_BLOCK_SIZE;
}

static void *getSectorPtr(int no)
{
	if( no == 0 ) return &(_data->MyData[0]);
	if( no >= 1 && no <= 4 ) return &(_data->Fld[SVLD_BLOCK_SIZE * (no - 1)]);
	if( no >= 5 && no < 14 ) return (void*)((u8*)&(_data->pc_data) + (SVLD_BLOCK_SIZE * (no - 5)));
	return NULL;
}

//==============================================================================
/**
 * �~���[�����O�̂����ЂƂ��`�F�b�N
 * @param   mirror�c�O���P 
 * @param   counter�c�J�E���^�[�������Ă���B
 * @param   buffer   �cSVLD_SECTOR_SIZE �K�v
 * @retval  NULL�c���s�A����ȊO�c��v�����C�j�V�����R�[�h�ւ̃|�C���^
 */
//==============================================================================
static u16 check_mirror(int mirror, void *buffer, u32 *counter)
{
	u32 block_flag = 0;
	u16 null_f = 0;
	u16 sumcheck;
	SVLDSYS_DATA *data = (SVLDSYS_DATA*) buffer;
	int i;

	*counter = 0;
	s_savingsector = 0;

	for(i = 0; i < SVLD_MIRROR_SIZE; i++){
		LoadSector(i % 14 + mirror * SVLD_MIRROR_SIZE, (void *)data);
		DC_FlushRange(data, SVLD_SECTOR_SIZE);
		//�h�c�m�F
#if 0
		OS_Printf("[%2d] : %08X\n", i, data->save_id);
#endif	
		if(data->save_id == SVLD_ID){
			null_f = 1;
			//�T���`�F�b�N�m�F
			sumcheck = 
				SumCheckCalc( (u32*)data->data, getSectorSize(data->blocknum) );
			if(data->sumcheck == sumcheck){
				*counter = data->save_count;
				block_flag |= (0x00000001 << data->blocknum);	//�u���b�N�⊮���
			}
		}
	}
	//�~���[�P�⊮���m�F
	if(null_f){
		if(block_flag == ((0xffffffff << SVLD_MIRROR_SIZE) ^ 0xffffffff)){
			return SVLD_RET_OK;
		}else{
			return SVLD_RET_NG;
		}
	}else{
		return SVLD_RET_NULL;
	}
}

//==============================================================================
/**
 * ��̃~���[�����O���r
 * @param   newsector�c�V�����Z�N�^�[�̔ԍ��������Ă���(0��1)
 * @param   buffer   �cSVLD_SECTOR_SIZE �K�v
 * @retval  NULL�c���s�A����ȊO�c��v�����C�j�V�����R�[�h�ւ̃|�C���^
 */
//==============================================================================
static u16 LoadStatusCheck( void *buffer, int *newsector, u32 *main_counter)
{
	u16	f1, f2;
	u32	counter1, counter2;
	
	f1 = check_mirror(0, buffer, &counter1);
	f2 = check_mirror(1, buffer, &counter2);

#if 0
	OS_Printf("[%d] - [%d]\n", f1, f2);
#endif
	
	//��Ԕ���
	if( (f1 == SVLD_RET_OK) && (f2 == SVLD_RET_OK) )
	{
		if(((counter1 == 0xffffffff)&&(counter2 == 0x00000000))
			||((counter1 == 0x00000000)&&(counter2 == 0xffffffff))){
			//�����J���X�g�����i�Ȃ��Ǝv�����O�̂��߁j
			if( (counter1 + 1) < (counter2 + 1) ){
				*main_counter = counter2;
				*newsector = 1;
			}else{
				*main_counter = counter1;
				*newsector = 0;
			}
		}else{
			if(counter1 < counter2){
				*main_counter = counter2;
				*newsector = 1;
			}else{
				*main_counter = counter1;
				*newsector = 0;
			}
		}
		return	SVLD_RET_OK;//�~���[�P�F�����A�~���[�Q�F����
	}

	if((f1 == SVLD_RET_OK)&&(f2 != SVLD_RET_OK)){
		*main_counter	= counter1;
		if(f2 == SVLD_RET_NG){
			*newsector = 0;
			return	SVLD_RET_NG;//�~���[�P�F�����A�~���[�Q�F���S�i�x���j
		}else{
			*newsector = 0;
			return	SVLD_RET_OK;//�~���[�P�F�����A�~���[�Q�F�����i���肦�Ȃ����ꉞ�j
		}
	}
	if((f2 == SVLD_RET_OK)&&(f1 != SVLD_RET_OK)){
		*main_counter	= counter2;
		if(f1 == SVLD_RET_NG){
			*newsector = 1;
			return	SVLD_RET_NG;//�~���[�P�F���S�A�~���[�Q�F�����i�x���j
		}else{
			*newsector = 1;
			return	SVLD_RET_OK;//�~���[�P�F�����A�~���[�Q�F�����i�ŏ��͂���j
		}
	}

	if((f1 == SVLD_RET_NULL)&&(f2 == SVLD_RET_NULL)){
		*main_counter = 0;
		*newsector = 0;
		return	SVLD_RET_NULL;//�~���[�P�F�����A�~���[�Q�F����
	}

	//���̑��i���肦�Ȃ����O�̂��߁j
	//�~���[�P�F���S�A�~���[�Q�F���S
	//�~���[�P�F�����A�~���[�Q�F���S
	//�~���[�P�F���S�A�~���[�Q�F�����i�����s�ǂł��邩���H�j
	*main_counter	= 0;
	*newsector	= 0;
	return	SVLD_RET_DESTROY;
}

//==============================================================================
/**
 * �f�[�^�����[�h����B
 * @retval  ���ʁB
 */
//==============================================================================
static int _newer_sector;
static u32 _counter;
int agbpoke_LoadDATA()
{
	u16 ret = LoadStatusCheck( (void*)_data->buffer, &_newer_sector, &_counter );
	if (ret != SVLD_RET_OK) 
	{
		switch( ret )
		{
			case SVLD_RET_NG:
			return AGBPOKE_ERROR_NG;
			case SVLD_RET_NULL:
			return AGBPOKE_ERROR_NULL;
			case SVLD_RET_DESTROY:
			return AGBPOKE_ERROR_DESTROY;
		}
	}
	
	if( _newer_sector == 0 || _newer_sector == 1 )
	{
		int i;
		u32 block_flag = 0;		
		SVLDSYS_DATA *data = (SVLDSYS_DATA*) _data->buffer;
		for(i = 0; i < SVLD_MIRROR_SIZE; i++){
			LoadSector(i + _newer_sector * SVLD_MIRROR_SIZE, (void *)data);
			//�h�c�m�F
			if(data->save_id == SVLD_ID){
				//�T���`�F�b�N�m�F
				u16 sumcheck = SumCheckCalc( (u32*)data->data, getSectorSize(data->blocknum) );
				if(data->sumcheck == sumcheck){
					_counter = data->save_count;
					block_flag |= (0x00000001 << data->blocknum);	//�u���b�N�⊮���
					
					// �f�[�^���R�s�[
					MI_CpuCopy32( (u32*)data->data, getSectorPtr(data->blocknum), getSectorSize(data->blocknum) );
					
					if( data->blocknum == 0 ) _startsector = i;
				}
			}
		}
		
		if(block_flag == ((0xffffffff << SVLD_MIRROR_SIZE) ^ 0xffffffff))
		{
			return AGBPOKE_ERROR_OK;
		}else{
			// ���͓ǂ߂Ă�̂�����A�ǂݍ��݃~�X�B
			// �O�̂��߁A�����݂Ȃ����Ă�������ق��������H
			return AGBPOKE_ERROR_READ;
		}
	}
	
	return AGBPOKE_ERROR_DESTROY;  //�����ɂ��邱�Ƃ̓v���O�����̃o�O�ȊO�͂Ȃ�
}

static u8 SaveSector(u8 sector_num,u8* data)
{
	if( CTRDG_WriteAndVerifyAgbFlash(sector_num, data, SVLD_SECTOR_SIZE) )
	{
		return	SVLD_RET_NG;
	}else{
		return	SVLD_RET_OK;
	}
}


//==============================================================================
/**
 * �f�[�^���Z�[�u����BAGBPOKE_ERROR_CONTINUE�ȊO�̒l���Ԃ��܂ŌĂяo���ĉ������B
 * @retval  ���ʁB
 */
//==============================================================================

int _target_mirror = -1;

int agbpoke_saveEdit( ){
	SVLDSYS_DATA *data = (SVLDSYS_DATA*) _data->buffer;
	
	if( s_savingsector == 0 )
	{
		if(_newer_sector == 1) {
			_target_mirror = 0;
		} else {
			_target_mirror = 1;
		}
		_counter++;
	}
	
	// �����Ăяo������������
	if( _target_mirror < 0 ) return AGBPOKE_ERROR_NG;
	
	MI_CpuClear32( data, SVLD_SECTOR_SIZE );
	MI_CpuCopy32(getSectorPtr(s_savingsector), data->data, getSectorSize(s_savingsector));
	data->save_count = _counter;
	data->blocknum = (u16)s_savingsector;
	data->save_id = SVLD_ID;
	data->sumcheck = SumCheckCalc((u32 * )data->data, getSectorSize(s_savingsector));
	{
		u8 ret;
		u8 target_sec = (u8)( ((s_savingsector + _startsector + 1) % SVLD_MIRROR_SIZE) + SVLD_MIRROR_SIZE * _target_mirror );
		ret = SaveSector(target_sec, (u8 *)data);
		if( ret != SVLD_RET_OK ) return AGBPOKE_ERROR_WRITE;
	}
	
	s_savingsector++;
	if( s_savingsector >= SVLD_MIRROR_SIZE ) 
	{
		s_savingsector = 0;
		return AGBPOKE_ERROR_OK;
	}
	if( s_savingsector == SVLD_MIRROR_SIZE - 1 ) 
	  return AGBPOKE_ERROR_LAST;

	return AGBPOKE_ERROR_CONTINUE;
}

//==============================================================================
/**
 * �f�[�^��񓯊��ŃZ�[�u����B
 * AGBPOKE_ERROR_CONTINUE�ȊO�̒l���Ԃ��܂ŌĂяo���ĉ������B
 * @retval  ���ʁB
 */
//==============================================================================
enum
{
	ASYNC_STATE_STOP,
	ASYNC_STATE_WRITING,
	ASYNC_STATE_LAST,
	ASYNC_STATE_CONTINUE,
	ASYNC_STATE_WRITEERROR,
	
	ASYNC_STATE_NUM
};
static int _async_state = ASYNC_STATE_STOP;
	
static u32 saveCallback(struct CTRDGTaskInfo_tag *info);	
	
static void saveSub(int index)
{
	// �����Ăяo������������
	SVLDSYS_DATA *data = (SVLDSYS_DATA*) _data->buffer;	
	_async_state = ASYNC_STATE_WRITING;
	MI_CpuClear32( data, SVLD_SECTOR_SIZE );
	MI_CpuCopy32(getSectorPtr(index), data->data, getSectorSize(index));
	data->save_count = _counter;
	data->blocknum = (u16)index;
	data->save_id = SVLD_ID;
	data->sumcheck = SumCheckCalc((u32 * )data->data, getSectorSize(index));
	{
		u8 target_sec = (u8)( ((index + _startsector + 1) % SVLD_MIRROR_SIZE) + SVLD_MIRROR_SIZE * _target_mirror );
		CTRDG_WriteAndVerifyAgbFlashAsync(target_sec, (u8 *)data, 4, saveCallback);
	}	
}
	
static u32 saveCallback(struct CTRDGTaskInfo_tag *info)
{
//	OS_TPrintf("callback\n");
	if( info->result == 0)
	{
		// ����	
		s_savingsector++;
		if( s_savingsector >= SVLD_MIRROR_SIZE ) 
		{
			s_savingsector = 0;
//			OS_TPrintf("����\n", s_savingsector);
			_async_state = ASYNC_STATE_STOP;
			return 0;
		}
		if( s_savingsector == SVLD_MIRROR_SIZE - 1 )
		{
		  _async_state = ASYNC_STATE_LAST;
		  return 0;
		}
		else
		{
			_async_state = ASYNC_STATE_CONTINUE;
		}
	}
	else
	{
		// ���s	
		_async_state =  ASYNC_STATE_WRITEERROR;
	}
	return 0;
}

BOOL agbpoke_saveEdit_Async()
{
	if( s_savingsector == 0 )
	{
		if(_newer_sector == 1) {
			_target_mirror = 0;
		} else {
			_target_mirror = 1;
		}
		_counter++;
	}
	else
	{
		return FALSE;	
	}
	
	// �����Ăяo������������
	if( _target_mirror < 0 ) return FALSE;
	saveSub(s_savingsector);
	return TRUE;
}

int agbpoke_saveEdit_check()
{
	switch ( _async_state )
	{
	case ASYNC_STATE_LAST:
	  saveSub(s_savingsector);
	  return AGBPOKE_ERROR_OK;
		case ASYNC_STATE_CONTINUE:
			{
//				OS_TPrintf("save sector[%d]\n", s_savingsector);
				saveSub(s_savingsector);
			}
		case ASYNC_STATE_WRITING:
			return AGBPOKE_ERROR_CONTINUE;
		case ASYNC_STATE_WRITEERROR:
			return AGBPOKE_ERROR_WRITE;
		case ASYNC_STATE_STOP:
		default:
			return AGBPOKE_ERROR_OK;
	}
}

int agbpoke_check_status(void)
{
  switch(_async_state){
  case ASYNC_STATE_LAST:
    return AGBPOKE_ERROR_LAST;
  case ASYNC_STATE_CONTINUE:
    return AGBPOKE_ERROR_CONTINUE;
  case ASYNC_STATE_WRITING:
    return AGBPOKE_ERROR_WRITING;
  case ASYNC_STATE_WRITEERROR:
    return AGBPOKE_ERROR_WRITE;
  case ASYNC_STATE_STOP:
  default:
    return AGBPOKE_ERROR_OK;
  }
}

//==============================================================================
/**
 * �p�\�R���f�[�^�ւ̃|�C���^���擾����B
 * @param   newsector�c�V�����Z�N�^�[�̔ԍ��������Ă���(0��1)
 * @param   buffer   �cSVLD_SECTOR_SIZE �K�v
 * @retval  ���ʁB
 */
//==============================================================================
POKEBOX_SAVE_DATA *agbpoke_getPCdata()
{
	return &(_data->pc_data);
}

//==============================================================================
/**
 * �}�ӂ������Ă��邩����B
 * @retval  ���ʁB
 */
//==============================================================================
BOOL gbapoke_hasZukan()
{
 	// �}�ӂ������Ă���ǂ���
	if( _softtype->version == SOFTTYPE_RS ) {
		// ���r�T�t�@
		if(_data->Fld[_pokeromheader.event_flag_offset + SYSFLAG_START / 8] & 0x02) {
			return TRUE;
		} else {
			return FALSE;
		}
  	} 
  	else if( _softtype->version == SOFTTYPE_FL ) 
  	{
  		if( _data->Fld[_pokeromheader.event_flag_offset + FRLG_SYS_ZUKAN_GET / 8] & (1 << (FRLG_SYS_ZUKAN_GET % 8))  )
  		{
  			return TRUE;
  		}
  		else
  		{
  			return FALSE;
  		}
  	}  
  	else if( _softtype->version == SOFTTYPE_EM ) 
  	{
  		if( _data->Fld[_pokeromheader.event_flag_offset + 2144 / 8] & (1 << 1)  )
  		{
  			return TRUE;
  		}
  		else
  		{
  			return FALSE;
  		}  	
  	}
  	return TRUE;
}

//==============================================================================
/**
 * �|�P�����Z���^�[���ŃZ�[�u���Ă��邩�ǂ���
 * @retval  ���ʁB
 */
//==============================================================================
BOOL gbapoke_inPokemonCenter()
{
	if( _softtype->version == SOFTTYPE_RS ) {
		//Fld.MapID�͌��݂̃}�b�v���w���B�����odiv_id��map_id�ɂ����
		//�ʂ̃}�b�v�����ʂł���B
		MapID *temp;
		
		temp = (MapID *)&(_data->Fld[4]);
		
		//�g�p����}�b�v�X�N���[���f�[�^���A�|�P�Z���̏ꍇ��TRUE��Ԃ�
			if (
			// �|�P�Z���PF
				rsmap_DivisionList[temp->div_id][temp->map_id] == MAPSCRNID_PC01 ||
			// �|�P�Z���QF
				rsmap_DivisionList[temp->div_id][temp->map_id] == MAPSCRNID_PC02 ||
			// �|�P�Z���PF�i�t�G���j
				rsmap_DivisionList[temp->div_id][temp->map_id] == MAPSCRNID_PC01_1
			) {	
			return 1;
		} else {
			return 0;
		}		
	} else {
		return  (_data->MyData[_pokeromheader.pokecen_flg] & 0x02);
	}
}

void *agbpoke_GetMyDataPtr(void)
{
  return getSectorPtr(0);
}


static const AGBSOFT_TYPE support_softs[30] = {
  { 'JVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_JP },		// ���r�[���{���
  { 'EVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_US },		// ���r�[�k�Ĕ�
  { 'FVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_FR },		// ���r�[�t�����X��
  { 'DVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_GE },		// ���r�[�h�C�c��
  { 'SVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_SP },		// ���r�[�X�y�C����
  { 'IVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_IT },		// ���r�[�C�^���A��
  { 'JPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_JP },	// �T�t�@�C�A���{���
  { 'EPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_US },	// �T�t�@�C�A�k�Ĕ�
  { 'FPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_FR },	// �T�t�@�C�A�t�����X��
  { 'DPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_GE },	// �T�t�@�C�A�h�C�c��
  { 'SPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_SP },	// �T�t�@�C�A�X�y�C����
  { 'IPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_IT },	// �T�t�@�C�A�C�^���A��
  { 'JRPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_JP },		// �t�@�C�A���b�h���{���
  { 'ERPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_US },		// �t�@�C�A���b�h�k�Ĕ�
  { 'FRPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_FR },		// �t�@�C�A���b�h�t�����X��
  { 'DRPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_GE },		// �t�@�C�A���b�h�h�C�c��
  { 'SRPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_SP },		// �t�@�C�A���b�h�X�y�C����
  { 'IRPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_IT },		// �t�@�C�A���b�h�C�^���A��
  { 'JGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_JP },		// ���[�t�O���[�����{���
  { 'EGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_US },		// ���[�t�O���[���k�Ĕ�
  { 'FGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_FR },		// ���[�t�O���[���t�����X��
  { 'DGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_GE },		// ���[�t�O���[���h�C�c��
  { 'SGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_SP },		// ���[�t�O���[���X�y�C����
  { 'IGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_IT },		// ���[�t�O���[���C�^���A��
  { 'JEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_JP },	// �G�������h���{���
  { 'EEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_US },	// �G�������h�k�Ĕ�
  { 'FEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_FR },	// �G�������h�t�����X��
  { 'DEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_GE },	// �G�������h�h�C�c��
  { 'SEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_SP },	// �G�������h�X�y�C����
  { 'IEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_IT },	// �G�������h�C�^���A��
};

static u8 nintendo_logo[] = 
{
   0x24,0xff,0xae,0x51,0x69,0x9a,0xa2,0x21,
   0x3d,0x84,0x82,0x0a,0x84,0xe4,0x09,0xad,
   0x11,0x24,0x8b,0x98,0xc0,0x81,0x7f,0x21,
   0xa3,0x52,0xbe,0x19,0x93,0x09,0xce,0x20,
   0x10,0x46,0x4a,0x4a,0xf8,0x27,0x31,0xec,
   0x58,0xc7,0xe8,0x33,0x82,0xe3,0xce,0xbf,
   0x85,0xf4,0xdf,0x94,0xce,0x4b,0x09,0xc1,
   0x94,0x56,0x8a,0xc0,0x13,0x72,0xa7,0xfc,
   0x9f,0x84,0x4d,0x73,0xa3,0xca,0x9a,0x61,
   0x58,0x97,0xa3,0x27,0xfc,0x03,0x98,0x76,
   0x23,0x1d,0xc7,0x61,0x03,0x04,0xae,0x56,
   0xbf,0x38,0x84,0x00,0x40,0xa7,0x0e,0xfd,
   0xff,0x52,0xfe,0x03,0x6f,0x95,0x30,0xf1,
   0x97,0xfb,0xc0,0x85,0x60,0xd6,0x80,0x25,
   0xa9,0x63,0xbe,0x03,0x01,0x4e,0x38,0xe2,
   0xf9,0xa2,0x34,0xff,0xbb,0x3e,0x03,0x44,
   0x78,0x00,0x90,0xcb,0x88,0x11,0x3a,0x94,
   0x65,0xc0,0x7c,0x63,0x87,0xf0,0x3c,0xaf,
   0xd6,0x25,0xe4,0x8b,0x38,0x0a,0xac,0x72,
   0x21,0xd4,0xf8,0x07
};


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

	u8	data[SVLD_DATA_SIZE];	//セーブデータ

	u16	blocknum;	//ブロックナンバー
	u16	sumcheck;	//サムチェックデータ
	u32	save_id;	//セーブ識別データ
	u32	save_count;	//セーブカウンター（履歴）
}SVLDSYS_DATA;



#define SVLD_MIRROR_SIZE	(14)
#define	SVLD_ID				(0x08012025)	//ヘッダステータス定義（ゲーム認証ＩＤ）
#define	SVLD_BLOCK_SIZE		(0xf80)		//セクタ当たりのセーブデータサイズ

static POKEMON_ROM_HEADER _pokeromheader;

static int check_agb(const AGBSOFT_TYPE *list, int size);
static const AGBSOFT_TYPE support_softs[30];
static u8 nintendo_logo[0xa0 - 4];

static const AGBSOFT_TYPE *_softtype = NULL;

static int _newer_sector;
static u32 _counter;
AGBPOKE_SAVEDATA *_data;

static int s_savingsector = 0;
// ０番があるセクタ
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
 * agbpoke_*が呼び出される前に、この関数をコールしてください。
 * @retval  TRUE…初期化成功　FALSE…初期化失敗
 */
//==============================================================================
int agbpoke_init( void *buffer )
{
	_data = (AGBPOKE_SAVEDATA *) buffer;
	if( _softtype != NULL ) 
	{
	  //		OS_Panic("agbpoke_initが以前呼び出されています。");
		return AGBPOKE_ERROR_OTHER;
	}
	
	{
		int ret = check_agb( support_softs, 30 );
		if( ret != AGBPOKE_ERROR_OK ) return ret;
	}
	

	if( _softtype->version == SOFTTYPE_RS  /* && _softtype->country == LANGTYPE_JP */ )
	{
		// ルビサファ日本語版・北米版のみ、ロムヘッダに対応していない。
		// 使うものみコピー
		_pokeromheader.MyData_size = RSINDEX_MYDATASIZE;
		_pokeromheader.Fld_size	= RSINDEX_FLDSIZE;
		_pokeromheader.event_flag_offset = RSINDEX_EVENTFLAG;
		_pokeromheader.pokecen_flg = RSINDEX_SAVESTATEFLAG;
	}
	else
	{
		CTRDG_CpuCopy32( (void*)0x08000100, (void*)&_pokeromheader, sizeof(POKEMON_ROM_HEADER));
	}

	// フラッシュの初期化。必ずイニシャルコードを確認してから！	
	if( !flash_init() )
	{
		OS_TPrintf("フラッシュ初期化に失敗\n");
		return AGBPOKE_ERROR_NOFLASH;
	}
	else
	{
		OS_TPrintf("フラッシュ初期化完了\n");
	}

	return AGBPOKE_ERROR_OK;
}

void agbpoke_preinit(void)
{
  _softtype = NULL;
}

//==============================================================================
/**
 * ささっているソフトのイニシャルコードを取得します。
 * @retval  TRUE…初期化成功　FALSE…初期化失敗
 */
//==============================================================================
u32 agbpoke_getInitialCode()
{
  return _softtype->initial_code;
}

//==============================================================================
/**
 * ささっているポケモンソフトのゲーム種類を返します。
 * @retval  カセットのポケモンタイプ
 */
//==============================================================================
int agbpoke_getPokemonType()
{
  return _softtype->cas_version;
}

//==============================================================================
/**
 * ささっているポケモンソフトの言語を返す。
 * @retval  カセットの言語
 */
//==============================================================================
int agbpoke_getPokemonLanguage()
{
  return _softtype->country;
}

//==============================================================================
/**
 * AGBカードが正しくささっているか、念入りに判定します。
 * AGBスロットの汚れ等で、データ消失の危険がないよう、
 * 必ず書き込む前にこの関数で判定すること。
 * @param   list, イニシャルコードのリスト。
 * @param   size, イニシャルコードのリストの項目数。
 * @retval  NULL…失敗、それ以外…一致したイニシャルコードへのポインタ
 */
//==============================================================================
static int check_agb(const AGBSOFT_TYPE *list, int size)
{
	u32 code;
	_softtype = NULL;
	// カートリッジスロットにカートリッジがささっているか判定
	if( !CTRDG_IsAgbCartridge() ) return AGBPOKE_ERROR_NOROM;
	
	// イニシャルコードを取得。
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
			OS_TPrintf("イニシャルコードが一致しません。\n");
			return AGBPOKE_ERROR_NOTPOKEMON;
		}
	}

	// イニシャルコードに一致したので、ロムを読み出しの許可
	CTRDG_Enable( TRUE );
	
	// ロムヘッダ情報を取得。
	{
		u32 romheader[0xc0/4];
		u8 *castdata = (u8*)&(romheader[0]);
		CTRDG_CpuCopy32( (void*)0x08000000, (void*)&(romheader[0]), 0xc0);
		// 任天堂ロゴチェック。
		{
			int i;
			for(i = 0; i < sizeof(nintendo_logo); i++)
			{
				if( nintendo_logo[i] != castdata[4 + i] )
				{
					OS_TPrintf("任天堂ロゴが一致しません。\n");	
					return AGBPOKE_ERROR_READ;
				}
			}
		}
		// 補数チェックを行う。
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
				OS_TPrintf("補数チェックに失敗しました。\n");
				return AGBPOKE_ERROR_READ;
			}
		}
	}
	
	return AGBPOKE_ERROR_OK;
}

//*************************************************************************
//=========================================================================
//				サブルーチン
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
	// ファイルシステムからロード
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
	// SDKが出来次第実装
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
 * ミラーリングのうちひとつをチェック
 * @param   mirror…０か１ 
 * @param   counter…カウンターが入ってくる。
 * @param   buffer   …SVLD_SECTOR_SIZE 必要
 * @retval  NULL…失敗、それ以外…一致したイニシャルコードへのポインタ
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
		//ＩＤ確認
#if 0
		OS_Printf("[%2d] : %08X\n", i, data->save_id);
#endif	
		if(data->save_id == SVLD_ID){
			null_f = 1;
			//サムチェック確認
			sumcheck = 
				SumCheckCalc( (u32*)data->data, getSectorSize(data->blocknum) );
			if(data->sumcheck == sumcheck){
				*counter = data->save_count;
				block_flag |= (0x00000001 << data->blocknum);	//ブロック補完情報
			}
		}
	}
	//ミラー１補完情報確認
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
 * 二つのミラーリングを比較
 * @param   newsector…新しいセクターの番号が入ってくる(0か1)
 * @param   buffer   …SVLD_SECTOR_SIZE 必要
 * @retval  NULL…失敗、それ以外…一致したイニシャルコードへのポインタ
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
	
	//状態判別
	if( (f1 == SVLD_RET_OK) && (f2 == SVLD_RET_OK) )
	{
		if(((counter1 == 0xffffffff)&&(counter2 == 0x00000000))
			||((counter1 == 0x00000000)&&(counter2 == 0xffffffff))){
			//履歴カンスト処理（ないと思うが念のため）
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
		return	SVLD_RET_OK;//ミラー１：生存、ミラー２：生存
	}

	if((f1 == SVLD_RET_OK)&&(f2 != SVLD_RET_OK)){
		*main_counter	= counter1;
		if(f2 == SVLD_RET_NG){
			*newsector = 0;
			return	SVLD_RET_NG;//ミラー１：生存、ミラー２：死亡（警告）
		}else{
			*newsector = 0;
			return	SVLD_RET_OK;//ミラー１：生存、ミラー２：初期（ありえないが一応）
		}
	}
	if((f2 == SVLD_RET_OK)&&(f1 != SVLD_RET_OK)){
		*main_counter	= counter2;
		if(f1 == SVLD_RET_NG){
			*newsector = 1;
			return	SVLD_RET_NG;//ミラー１：死亡、ミラー２：生存（警告）
		}else{
			*newsector = 1;
			return	SVLD_RET_OK;//ミラー１：初期、ミラー２：生存（最初はこれ）
		}
	}

	if((f1 == SVLD_RET_NULL)&&(f2 == SVLD_RET_NULL)){
		*main_counter = 0;
		*newsector = 0;
		return	SVLD_RET_NULL;//ミラー１：初期、ミラー２：初期
	}

	//その他（ありえないが念のため）
	//ミラー１：死亡、ミラー２：死亡
	//ミラー１：初期、ミラー２：死亡
	//ミラー１：死亡、ミラー２：初期（初期不良であるかも？）
	*main_counter	= 0;
	*newsector	= 0;
	return	SVLD_RET_DESTROY;
}

//==============================================================================
/**
 * データをロードする。
 * @retval  結果。
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
			//ＩＤ確認
			if(data->save_id == SVLD_ID){
				//サムチェック確認
				u16 sumcheck = SumCheckCalc( (u32*)data->data, getSectorSize(data->blocknum) );
				if(data->sumcheck == sumcheck){
					_counter = data->save_count;
					block_flag |= (0x00000001 << data->blocknum);	//ブロック補完情報
					
					// データをコピー
					MI_CpuCopy32( (u32*)data->data, getSectorPtr(data->blocknum), getSectorSize(data->blocknum) );
					
					if( data->blocknum == 0 ) _startsector = i;
				}
			}
		}
		
		if(block_flag == ((0xffffffff << SVLD_MIRROR_SIZE) ^ 0xffffffff))
		{
			return AGBPOKE_ERROR_OK;
		}else{
			// 一回は読めてるのだから、読み込みミス。
			// 念のため、差込みなおしてもらったほうがいい？
			return AGBPOKE_ERROR_READ;
		}
	}
	
	return AGBPOKE_ERROR_DESTROY;  //ここにくることはプログラムのバグ以外はない
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
 * データをセーブする。AGBPOKE_ERROR_CONTINUE以外の値が返すまで呼び出して下さい。
 * @retval  結果。
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
	
	// 何か呼び出しがおかしい
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
 * データを非同期でセーブする。
 * AGBPOKE_ERROR_CONTINUE以外の値が返すまで呼び出して下さい。
 * @retval  結果。
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
	// 何か呼び出しがおかしい
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
		// 成功	
		s_savingsector++;
		if( s_savingsector >= SVLD_MIRROR_SIZE ) 
		{
			s_savingsector = 0;
//			OS_TPrintf("完了\n", s_savingsector);
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
		// 失敗	
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
	
	// 何か呼び出しがおかしい
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
 * パソコンデータへのポインタを取得する。
 * @param   newsector…新しいセクターの番号が入ってくる(0か1)
 * @param   buffer   …SVLD_SECTOR_SIZE 必要
 * @retval  結果。
 */
//==============================================================================
POKEBOX_SAVE_DATA *agbpoke_getPCdata()
{
	return &(_data->pc_data);
}

//==============================================================================
/**
 * 図鑑をもっているか判定。
 * @retval  結果。
 */
//==============================================================================
BOOL gbapoke_hasZukan()
{
 	// 図鑑を持っているどうか
	if( _softtype->version == SOFTTYPE_RS ) {
		// ルビサファ
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
 * ポケモンセンター内でセーブしているかどうか
 * @retval  結果。
 */
//==============================================================================
BOOL gbapoke_inPokemonCenter()
{
	if( _softtype->version == SOFTTYPE_RS ) {
		//Fld.MapIDは現在のマップを指す。メンバdiv_idとmap_idによって
		//個別のマップを識別できる。
		MapID *temp;
		
		temp = (MapID *)&(_data->Fld[4]);
		
		//使用するマップスクリーンデータが、ポケセンの場合はTRUEを返す
			if (
			// ポケセン１F
				rsmap_DivisionList[temp->div_id][temp->map_id] == MAPSCRNID_PC01 ||
			// ポケセン２F
				rsmap_DivisionList[temp->div_id][temp->map_id] == MAPSCRNID_PC02 ||
			// ポケセン１F（フエン）
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
  { 'JVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_JP },		// ルビー日本語版
  { 'EVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_US },		// ルビー北米版
  { 'FVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_FR },		// ルビーフランス版
  { 'DVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_GE },		// ルビードイツ版
  { 'SVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_SP },		// ルビースペイン版
  { 'IVXA', SOFTTYPE_RS, CASTYPE_RUBY, LANGTYPE_IT },		// ルビーイタリア版
  { 'JPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_JP },	// サファイア日本語版
  { 'EPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_US },	// サファイア北米版
  { 'FPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_FR },	// サファイアフランス版
  { 'DPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_GE },	// サファイアドイツ版
  { 'SPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_SP },	// サファイアスペイン版
  { 'IPXA', SOFTTYPE_RS, CASTYPE_SAPPHIRE, LANGTYPE_IT },	// サファイアイタリア版
  { 'JRPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_JP },		// ファイアレッド日本語版
  { 'ERPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_US },		// ファイアレッド北米版
  { 'FRPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_FR },		// ファイアレッドフランス版
  { 'DRPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_GE },		// ファイアレッドドイツ版
  { 'SRPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_SP },		// ファイアレッドスペイン版
  { 'IRPB', SOFTTYPE_FL, CASTYPE_RED, LANGTYPE_IT },		// ファイアレッドイタリア版
  { 'JGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_JP },		// リーフグリーン日本語版
  { 'EGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_US },		// リーフグリーン北米版
  { 'FGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_FR },		// リーフグリーンフランス版
  { 'DGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_GE },		// リーフグリーンドイツ版
  { 'SGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_SP },		// リーフグリーンスペイン版
  { 'IGPB', SOFTTYPE_FL, CASTYPE_GREEN, LANGTYPE_IT },		// リーフグリーンイタリア版
  { 'JEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_JP },	// エメラルド日本語版
  { 'EEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_US },	// エメラルド北米版
  { 'FEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_FR },	// エメラルドフランス版
  { 'DEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_GE },	// エメラルドドイツ版
  { 'SEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_SP },	// エメラルドスペイン版
  { 'IEPB', SOFTTYPE_EM, CASTYPE_EMERALD, LANGTYPE_IT },	// エメラルドイタリア版
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

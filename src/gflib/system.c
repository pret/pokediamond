//==============================================================================
/**
 * @file	system.c
 * @brief	システムレベルの関数をあつめたもの
 * @author	GAME FREAK Inc.
 */
//==============================================================================

#define __SYSTEM_H_GLOBAL__
#include "standard.h" 
#include "system.h"
#include "system\wordset.h"
#include "gflib_os_print.h"
#include "assert.h"
#include "rebooter.h"

//==============================================================================
//
//			定義、関数宣言
//
//==============================================================================
//#define	FS_DMA_NUMBER	DEFAULT_DMA_NUMBER
#define		FS_DMA_NUMBER		(1)



static void HBlankIntrSetMain( BOOL func_flag );

#ifdef PM_DEBUG 
extern u32 sys_GetMemoryBlockSize( const void* memBlock );
#endif

//==============================================================================
//
//			変数定義
//
//==============================================================================
SystemArea sys;						// システムリソース

//==============================================================================
//
//			関数
//
//==============================================================================

/*---------------------------------------------------------------------------*
  Name:         sys_VBlankIntr

  Description:  Vブランクのコールバックルルーチン。

  Arguments:    なし。
  Returns:      なし。
 *---------------------------------------------------------------------------*/
void sys_VBlankIntr(void)
{
	OS_SetIrqCheckFlag(OS_IE_V_BLANK);

	MI_WaitDma(GX_DEFAULT_DMAID);
	TCBSYS_Main( sys.vintrTCBSys );

	sys.vsync_flame_counter++;
}

//==============================================================================
/**
 * Vブランク中に呼び出される関数の登録
 *
 * @param   func	呼び出す関数ポインタ
 * @param	work	指定関数を呼び出すときの引数ワークへのポインタ
 *
 * @retval  none		
 */
//==============================================================================
void sys_VBlankFuncChange(INTR_FUNC func, void * work)
{
	sys.pVBlank = func;
	sys.pVBlankWork = work;
}


//==============================================================================
//
//
//			Hブランク関連
//
//
//==============================================================================
//----------------------------------------------------------------
//----------------------------------------------------------------
void sys_HBlankIntrStop( void )
{
	HBlankIntrSetMain( FALSE );
	sys.pHBlank = NULL;
	sys.pHBlankWork = NULL;
}

//----------------------------------------------------------------
/**
 * @brief	Hブランク設定
 * @param   func	呼び出す関数ポインタ
 * @param	work	割り込み中に使用するワークへのポインタ
 * @retval  "TRUE = 設定しました"
 * @retval	"FALSE = すでに設定されています"
 *
 * @li	func = NULL の場合、Hブランククリア
 */
//----------------------------------------------------------------
BOOL  sys_HBlankIntrSet( INTR_FUNC func, void * work )
{
#if 1
	if( func == NULL ){
		HBlankIntrSetMain( FALSE );
		sys.pHBlank = NULL;
		sys.pHBlankWork = NULL;
		return TRUE;
	} else {
		if( sys.pHBlank == NULL ){
			sys.pHBlankWork = work;
			sys.pHBlank = func;
			HBlankIntrSetMain( TRUE );
			return TRUE;
		} else {
			return FALSE;
		}
	}
#else
	if( sys.pHBlank == NULL ){
		if( func ){
			sys.pHBlankWork = work;
			sys.pHBlank = func;
			HBlankIntrSetMain( TRUE );
			return TRUE;
		} else {
			HBlankIntrSetMain( FALSE );
			sys.pHBlank = NULL;
			sys.pHBlankWork = NULL;
			return TRUE;
		}
	}else if( func == NULL ){
		HBlankIntrSetMain( FALSE );
		sys.pHBlank = NULL;
		sys.pHBlankWork = NULL;
		return TRUE;
	}
	return FALSE;
#endif
}

//----------------------------------------------------------------
/**
 */
//----------------------------------------------------------------
static void sys_HBlankIntr(void)
{
	if (sys.pHBlank) {
		sys.pHBlank(sys.pHBlankWork);
	}
}

//----------------------------------------------------------------
//----------------------------------------------------------------
static void HBlankIntrSetMain( BOOL func_flag )
{
	OSIrqMask irqmask;

	OS_DisableIrq( ); 	//割り込み禁止
	if(func_flag==FALSE){
		irqmask = OS_GetIrqMask();
		OS_DisableIrqMask(OS_IE_H_BLANK);
		(void)GX_HBlankIntr(FALSE);
	}else{
		irqmask = OS_GetIrqMask();
		//OS_SetIrqFunction( OS_IE_H_BLANK, func );
		OS_SetIrqFunction( OS_IE_H_BLANK, sys_HBlankIntr );
		OS_EnableIrqMask(OS_IE_H_BLANK);
	    (void)GX_HBlankIntr(TRUE);          // Rise a H-Blank interrupt
	}
	OS_EnableIrq( ); 	//割り込み許可
}


//----------------------------------------------------------------
/**
 *	基本ヒープ初期化構造体
 */
//----------------------------------------------------------------
#define HEAPSIZE_SYSTEM		(0x00d000)
#define HEAPSIZE_DEBUG		(0x001000)
#define HEAPSIZE_SAVE		(0x021000)
#define HEAPSIZE_APP		(0x106800+0x7000)	//VCT用に2000確保 7.27

// BASE_HEAPID と順番を一致させること！ 
static const HEAP_INIT_HEADER HeapInitHeader[] = {
	{ HEAPSIZE_SYSTEM,		OS_ARENA_MAIN   },
	{ HEAPSIZE_SAVE,		OS_ARENA_MAIN   },
	{ HEAPSIZE_DEBUG,		OS_ARENA_MAIN   },
	{ HEAPSIZE_APP,			OS_ARENA_MAIN   },
};


//----------------------------------------------------------------
/**
 *	TCBシステム作成パラメータ
 */
//----------------------------------------------------------------
enum {
	TCB_MAIN_MAX = 160,
	TCB_VINTR_MAX = 16,
	TCB_VWAIT_MAX = 32,
	TCB_PRINT_MAX =  4,
};


//------------------------------------------------------------------
/**
 * 起動毎にヒープ作成位置をずらして初期化する
 */
//------------------------------------------------------------------
static void InitHeapSystem( void )
{
	enum {
		HEAP_START_OFFSET_MAX = 256,
	};

	u32  led[8];
	u8   md5[MATH_MD5_DIGEST_SIZE];

	u32  offset, i;

	OS_GetLowEntropyData( led );
	MATH_CalcMD5( md5, led, sizeof(led) );

	offset = 0;
	for(i=0; i<MATH_MD5_DIGEST_SIZE; i++)
	{
		offset += md5[i];
	}
	offset %= HEAP_START_OFFSET_MAX;
	while( offset % 4 )
	{
		offset++;
	}

	sys_InitHeapSystem(HeapInitHeader, NELEMS(HeapInitHeader), HEAPID_MAX, offset);
}




/*---------------------------------------------------------------------------*
  Name:         sys_InitSystem

  Description:  NITROの初期化を行います。

  Arguments:    なし。
  Returns:      なし。
 *---------------------------------------------------------------------------*/
void sys_InitSystem(void)
{
	#ifdef PM_DEBUG
	#ifndef EXHEAP_DISABLE
	OS_EnableMainExArena();
	#endif
	#endif

    OS_Init();
    FX_Init();
	GX_SetPower(GX_POWER_ALL);
    GX_Init();
	OS_InitTick();

	// ヒープ管理システム初期化
	InitHeapSystem();

	// 各種TCBシステムの作成
	sys.mainTCBSys = TCBSYS_Create( TCB_MAIN_MAX,  OS_AllocFromMainArenaLo(TCBSYS_CalcSystemWorkSize(TCB_MAIN_MAX),4) );
	sys.vintrTCBSys = TCBSYS_Create( TCB_VINTR_MAX, OS_AllocFromMainArenaLo(TCBSYS_CalcSystemWorkSize(TCB_VINTR_MAX),4) );
	sys.vwaitTCBSys = TCBSYS_Create( TCB_VWAIT_MAX, OS_AllocFromMainArenaLo(TCBSYS_CalcSystemWorkSize(TCB_VWAIT_MAX),4) );
	sys.printTCBSys = TCBSYS_Create( TCB_PRINT_MAX, OS_AllocFromMainArenaLo(TCBSYS_CalcSystemWorkSize(TCB_PRINT_MAX),4) );


    GX_DispOff();
    GXS_DispOff();

	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
	OS_SetIrqFunction(OS_IE_V_BLANK, sys_VBlankIntr);

    (void)OS_EnableIrqMask(OS_IE_V_BLANK);
    (void)OS_EnableIrqMask(OS_IE_FIFO_RECV);
    (void)OS_EnableIrq();

    (void)GX_VBlankIntr(TRUE);         // to generate VBlank interrupt request

	FS_Init(FS_DMA_NUMBER);
	rebooter_init();
	/* always preload FS table for faster directory access. */
	{
		u32 file_table_size = FS_GetTableSize();
		void* p_table = OS_AllocFromMainArenaLo( file_table_size, 4 );

		OS_TPrintf("FileTable Size     = 0x%08x bytes.\n", file_table_size);
		OS_TPrintf("remains of MainRAM = 0x%08x bytes.\n", (u32)(OS_GetMainArenaHi())-(u32)(OS_GetMainArenaLo()));

		GF_ASSERT(p_table != NULL);
		FS_LoadTable(p_table, file_table_size);
	}

	sys.pVBlank		= NULL;		// Ｖブランク割込み内呼び出し関数ポインタ
	sys.pHBlank		= NULL;		// Ｈブランク割込み内呼び出し関数ポインタ
	sys.pVCount		= NULL;		// Ｖカウント割込み内呼び出し関数ポインタ
	sys.pSio		= NULL;		// ＳＩＯ割込み内呼び出し関数ポインタ

	sys.vsync_counter = 0;	
	sys.disp3DSW = DISP_3D_TO_MAIN;	
}

/*---------------------------------------------------------------------------*
  Name:         sys_InitVRAM

  Description:  ＶＲＡＭの初期化を行います。

  Arguments:    なし。
  Returns:      なし。
 *---------------------------------------------------------------------------*/
void sys_InitVRAM(void)
{
    // 全てのバンクをLCDCに割り当てる
    GX_SetBankForLCDC(GX_VRAM_LCDC_ALL);

    // LCDC空間全てをクリア
    MI_CpuClearFast( (void*)HW_LCDC_VRAM, HW_LCDC_VRAM_SIZE );
    
    // LCDCに割り当てられたバンクをDisable
    (void)GX_DisableBankForLCDC();

    MI_CpuFillFast ((void*)HW_OAM    , 192, HW_OAM_SIZE   );  // OAM クリア
    MI_CpuFillFast ((void*)HW_DB_OAM , 192, HW_DB_OAM_SIZE);  // clear OAM

    MI_CpuClearFast((void*)HW_PLTT   , HW_PLTT_SIZE   );      // パレット クリア
    MI_CpuClearFast((void*)HW_DB_PLTT, HW_DB_PLTT_SIZE);	  // clear the standard palette
}



//==============================================================================
//
//
//
//==============================================================================
/*---------------------------------------------------------------------------*
  Name:         sys_LoadFile

  Description:  通常ファイルの読み込み
  
  Arguments:    mode	指定ヒープ領域定義
				path	ファイルへのパス
  Returns:      ファイル読み込み先アドレス
 *---------------------------------------------------------------------------*/
void* sys_LoadFile(int mode, const char *path)
{
	FSFile file;
	void*  memory;

	FS_InitFile(&file);
	if (FS_OpenFile(&file, path)){

		u32	fileSize = FS_GetLength(&file);		
		memory = sys_AllocMemory( mode, fileSize );

		if (memory == NULL){
			OS_Printf("no enough memory.\n");
		}else{
			if(FS_ReadFile(&file, memory, fileSize) != fileSize){
				// ファイルサイズ分読み込めていない場合
				sys_FreeMemory( mode, memory );
				memory = NULL;
				OS_Printf("file reading failed.\n");
			}
		}
		(void)FS_CloseFile(&file);
	}else{
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
		memory = NULL;
	}
	return memory;
}

/*---------------------------------------------------------------------------*
  Name:         sys_LoadFileEx

  Description:  通常ファイルの読み込み + サイズ取得
  
  Arguments:    mode	指定ヒープ領域定義
				path	ファイルへのパス
				siz		データサイズ格納先
  Returns:      ファイル読み込み先アドレス
 *---------------------------------------------------------------------------*/
void * sys_LoadFileEx( int mode, const char * path, u32 * siz )
{
	FSFile file;
	void * memory;

	FS_InitFile( &file );
	if( FS_OpenFile( &file, path ) ){

		*siz = FS_GetLength( &file );		
		memory = sys_AllocMemory( mode, *siz );

		if( memory == NULL ){
			OS_Printf( "no enough memory.\n" );
		}else{
			if( FS_ReadFile( &file, memory, *siz ) != *siz ){
				// ファイルサイズ分読み込めていない場合
				sys_FreeMemory( mode, memory );
				memory = NULL;
				OS_Printf( "file reading failed.\n" );
			}
		}
		(void)FS_CloseFile( &file );
	}else{
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
	}
	return memory;
}

/*---------------------------------------------------------------------------*
  Name:         sys_LoadGraphFile

  Description:  グラフィック用ファイルの読み込み（キャッシュあり）
  
  Arguments:    path        ファイルへのパス
				side		メイン、サブ指定
  Returns:      ファイル読み込み先アドレス
 *---------------------------------------------------------------------------*/
void sys_LoadFileNoMem(const char *path, void **mem)
{
	FSFile file;
	
	FS_InitFile(&file);
	if (FS_OpenFile(&file, path)){
		u32	fileSize = FS_GetLength(&file);
#ifdef PM_DEBUG
		{
			u32 size = sys_GetMemoryBlockSize(*mem)-(0x10);
			if (fileSize>size){
				OS_Printf("fileSize=%x,allocSize=%x\n",fileSize,size);
				GF_ASSERT( 0 && "sys_LoadFileNoMem ERROR:メモリが不足してます");
			}
		}
#endif
		
#ifdef DEBUG_PRINT
		PrintAllocHeapSize(GRAPHIC_HEAP,path);
		
//		AddAllocHeapSize(GRAPHIC_HEAP);
#endif //DEBUG_PRINT
		if (*mem == NULL){
			OS_Printf("no memory.\n");
   	    }else{	// ファイルサイズ分読み込めていない場合
			if (FS_ReadFile(&file, *mem, fileSize) != fileSize){
				OS_Printf("file reading failed.\n");
			}
		}
        (void)FS_CloseFile(&file);
	}else{
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
	}
}

/*---------------------------------------------------------------------------*
  Name:         sys_LoadFileDiv

  Description:  通常ファイルの読み込み分割 
  
  Arguments:    mode	指定ヒープ領域定義
				path	ファイルへのパス
				memory	ファイル読み込み先アドレス格納ポインタ
				offset	読み込みオフセット格納ポインタ
				divsiz	読み込み分割サイズ
Returns:		0:継続、1=終了
 *---------------------------------------------------------------------------*/
int sys_LoadFileDiv( int mode, const char * path, void** memory, u32* offset, u16 divsiz )
{
	FSFile file;
	char   filename[32];

	if(path[0]=='!'){
		strcpy(filename,&path[1]);
	}else{
		strcpy(filename,path);
	}

	FS_InitFile(&file);
	if (FS_OpenFile(&file, filename))
	{
		u32	fileSize = FS_GetLength(&file);	//ファイルサイズ取得		
		u32	readSize = 0;
		if(*memory == NULL){	//memoryが既に取得されてれば継続と判断
			//初期化	
			*memory = sys_AllocMemory( mode, fileSize );//読み込みエリア確保
			if (*memory == NULL){
				// メモリ確保失敗
				OS_Printf("no enough memory.\n");
				return 1;
			} else {	
				*offset = 0;	//オフセット初期化
			}
#ifdef SYSTEM_DEBUG_PRINT_FILE_SIZE	
			OS_Printf("DIV_LOAD_PATH:%s\nDivFileSizeTotal=%x\n",path,fileSize);
#endif
		}
		if( FS_SeekFile( &file, *offset, FS_SEEK_SET ) == FALSE ){
			// ファイルオフセット変更失敗
			sys_FreeMemory( mode, memory );
			memory = NULL;
			OS_Printf("file div failed.\n");
			return 1;
		}
		{
			void*	read_p;
			read_p = &((u8*)*memory)[*offset];
			readSize = FS_ReadFile(&file, read_p, divsiz);
			(void)FS_CloseFile(&file);
			*offset = *offset + readSize;	//オフセット増加
		}
		if( *offset >= fileSize ){
			//読み込み終了
			return 1;
		}
	}else{
		if(*memory != NULL){	//memoryが既に取得されてれば開放
			sys_FreeMemory( mode, *memory );
			*memory = NULL;
		}
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",filename);
		return 1;
	}
	return 0;
}

/*---------------------------------------------------------------------------*
  Name:         sys_LoadFileDiv

  Description:  通常ファイルの読み込み分割 
  
  Arguments:    mode	指定ヒープ領域定義
				path	ファイルへのパス
				memory	ファイル読み込み先アドレス格納ポインタ
				offset	読み込みオフセット格納ポインタ
				divsiz	読み込み分割サイズ
Returns:		0:継続、1=終了
 *---------------------------------------------------------------------------*/
int sys_LoadFileDivNoMem( const char * path, void** memory, u32* offset, u16 divsiz )
{
	FSFile file;
	char   filename[32];
	
	strcpy(filename,path);
	
	FS_InitFile(&file);
	if (FS_OpenFile(&file, filename))
	{
		u32	fileSize = FS_GetLength(&file);	//ファイルサイズ取得		
		u32	readSize = 0;
		if(*memory == NULL){	//memoryが確保されていないならばエラー
			OS_Printf("NoMemory file div failed.\n");
			return 1;
		}
#ifdef PM_DEBUG
		{
			if (*offset == 0){
				u32 size = sys_GetMemoryBlockSize(*memory)-(0x10);
				if (fileSize>size){
					OS_Printf("fileSize=%x,allocSize=%x\n",fileSize,size);
					GF_ASSERT( 0 && "sys_LoadFileDivNoMem ERROR:メモリが不足してます");
				}
			}
		}
#endif
		
		if( FS_SeekFile( &file, *offset, FS_SEEK_SET ) == FALSE ){
			// ファイルオフセット変更失敗
			OS_Printf("file div failed.\n");
			return 1;
		}
		{
			void*	read_p;
			read_p = &((u8*)*memory)[*offset];
			readSize = FS_ReadFile(&file, read_p, divsiz);
			(void)FS_CloseFile(&file);
			*offset = *offset + readSize;	//オフセット増加
		}
		if( *offset >= fileSize ){
			//読み込み終了
			return 1;
		}
	}else{	//ファイルが開けない
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",filename);
		return 1;
	}
	return 0;
}

//==============================================================================
#define FILE_CACHE_MAX	(128)
typedef struct{
	void *memory;
	u32  hash;
}FILE_CACHE;

FILE_CACHE FileCache[FILE_CACHE_MAX];

u16 debugcount=0;

/**
 * ファイル名からファイルキャッシュ用のハッシュ値を取得する
 *
 * @param   path	ファイル名文字列
 *
 * @retval  u32		
 */
//==============================================================================
u32 CreateFileHash(const char *path)
{
	int i,r;
	u32 work,result;
	u16 len;
	len = strlen(path);
	
	if (len%4){					//文字列を４で割った際の繰り返し回数を取得
		len = (len /4)+1;
	}else{
		len = len/4;	
	}

	result = 0;
	for(i=0;i<len;i++){			//4文字を一つのlong型とみなして文字列の長さ／４回
		work = 0;				//XORを行う
		for(r=0;r<4;r++){
			if(path[i*4+r]!=0){
				work |= (path[i*4+r]<<(r*8));
			}else{
				break;
			}
		}
		result ^= work;
	}

	return result;
}

//==============================================================================
/**
 * 既にキャッシュとして存在しているいるか検索する
 *
 * @param   hash	ファイル名から取得したハッシュ値
 *
 * @retval  int		0～:見つかった配列の要素	-1:見つからなかった
 */
//==============================================================================
int SearchFileCache(u32 hash)
{
	int i;
	for(i=0;i<FILE_CACHE_MAX;i++){
		if(FileCache[i].hash==hash){
			if(FileCache[i].memory!=NULL){
				return i;
			}
		}
	}
	return -1;
}

//==============================================================================
/**
 * 新しく読み込んだファイルをキャッシュ情報として登録する
 *
 * @param   memory		新しく確保したメモリのアドレス
 * @param   hash		ファイル名から取得したハッシュ値
 *
 * @retval  int			登録した番号
 */
//==============================================================================
int SetBlankCache(void* memory, u32 hash)
{
	int i;
	for(i=0;i<FILE_CACHE_MAX;i++){
		if(FileCache[i].memory==NULL){
			FileCache[i].memory = memory;
			FileCache[i].hash   = hash;
			return i;
		}
	}
	return -1;
}

//==============================================================================
/**
 * キャッシュの全解放・ハッシュ情報のクリア
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void ClearFileCache(void)
{
	int i;
	for(i=FILE_CACHE_MAX-1;i>-1;i--){
		if(FileCache[i].memory!=NULL){
			//NNS_FndFreeToExpHeap(sys.appHeap,FileCache[i].memory);
			sys_FreeMemoryEz( FileCache[i].memory );
#ifdef DEBUG_PRINT
			PrintFreeHeapSize(GRAPHIC_HEAP, "キャッシュデータの開放");
			OS_Printf(	"cache:graph3DHeap = %ld\n",
						NNS_FndGetTotalFreeSizeForExpHeap(sys.graph3DHeap));
#endif //DEBUG_PRINT
			FileCache[i].memory = NULL;
			FileCache[i].hash   = 0;
		}
	}
}

//==============================================================================
/**
 * @brief	ハッシュ配列をNULL初期化する
 */
//==============================================================================
void InitFileCache(void)
{
	u8 i = 0;
//	memset(FileCache,0,sizeof(FileCache)*FILE_CACHE_MAX);
	for(i=0;i < FILE_CACHE_MAX;i++){
		FileCache[i].memory = NULL;
		FileCache[i].hash   = 0;
	}
}

//==============================================================================
/**
 * @brief	特定のハッシュをクリアする(キー指定)
 *
 * @param   hash	ファイル名から取得したハッシュ値
 *
 * @retval  int		0～:削除した要素Index	-1:削除しなかった
 */
//==============================================================================
int ClearFileCacheKey(u32 hash)
{
	int i;

	i = SearchFileCache(hash);
	if(i == -1){	//登録データが見つからなかった
		return i;
	}

	//見つかったので削除する
	NNS_G3dResDefaultRelease(FileCache[i].memory);	//リソース解放処理
	sys_FreeMemoryEz( FileCache[i].memory );
	FileCache[i].memory = NULL;
	FileCache[i].hash   = 0;
	return i;
}

//==============================================================================
/**
 * @brief	特定のハッシュをクリアする(アドレス指定)
 *
 * @param   addr	リソースのアドレス
 *
 * @retval  int		0～:削除した要素Index	-1:削除しなかった
 */
//==============================================================================
int ClearFileCacheAddr(void* addr)
{
	int	i = 0;
	
	if(addr == NULL){
		return 0xFF;
	}
	//キャッシュ内を走査する
	for(i = 0;i < FILE_CACHE_MAX;i++){	
		if(FileCache[i].memory != addr){
			continue;
		}
		//キャッシュを破棄
		NNS_G3dResDefaultRelease(FileCache[i].memory);	//リソース解放処理
		sys_FreeMemoryEz(FileCache[i].memory);
		FileCache[i].memory = NULL;
		FileCache[i].hash   = 0;
		return i;
	}
	return -1;
}

/*---------------------------------------------------------------------------*
  Name:         sys_LoadGraphFile

  Description:  グラフィック用ファイルの読み込み（キャッシュあり）
  
  Arguments:    path        ファイルへのパス
				side		メイン、サブ指定
  Returns:      ファイル読み込み先アドレス
 *---------------------------------------------------------------------------*/
void* sys_LoadGraphFile(const char *path,const u8 inMode)
{
	FSFile file;
	char   filename[32];
	void*  memory;
	u32    hash;
	int	   result,flag=0;

	if(path[0]=='!'){
		strcpy(filename,&path[1]);
		flag = 1;
	}else{
		strcpy(filename,path);
	}
	hash = CreateFileHash(filename);

//	OS_Printf("\"%s\" = %08x\n",path,hash);
	
	if((result=SearchFileCache(hash))>=0 && flag==0){
		memory = FileCache[result].memory;
//		OS_Printf("cache hit! no %d : \"%s\" = %08x\n",result,path,hash);
	}else{
		FS_InitFile(&file);
		if (FS_OpenFile(&file, filename))
		{
			u32	fileSize = FS_GetLength(&file);		

			//memory = NNS_FndAllocFromExpHeapEx(sys.graph3DHeap, fileSize, 16);
			memory = sys_AllocMemory( inMode, fileSize );
#ifdef DEBUG_PRINT
			PrintAllocHeapSize(GRAPHIC_HEAP,path);
//			AddAllocHeapSize(GRAPHIC_HEAP);
#endif //DEBUG_PRINT
			if (memory == NULL)
   		     {
				OS_Printf("no enough memory.\n");
   	    	 }
   	     	else
			{	// ファイルサイズ分読み込めていない場合
				if (FS_ReadFile(&file, memory, fileSize) != fileSize)  
				{
					//NNS_FndFreeToExpHeap(sys.graph3DHeap, memory);
					sys_FreeMemoryEz( memory );
					memory = NULL;
					OS_Printf("file reading failed.\n");
				}
			}
            (void)FS_CloseFile(&file);
            if(flag==0){
	            if(SetBlankCache(memory,hash)<0){
	                OS_Printf("file cache  over.\n");
                }
            }//			OS_Printf("cache set \"%s\" = %08x\n",path,hash);
		}
		else{
			OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
			memory = NULL;
		}
	}
	return memory;
}
#if 0
/*---------------------------------------------------------------------------*
  @brief	グラフィック用ファイルリソースの解放

  @param	addr	(void*)解放するリソースアドレス
  @param	free	TRUEならば、キャッシュ登録されているリソースでも解放する
					FALSEの場合、キャッシュ登録されていれば解放しない
  @retval	0		正常解放
  @retval	1		キャッシュから解放
  @retval	2		キャッシュ登録されているので非解放
  @retval	0xFF	パラメータが不正
 *---------------------------------------------------------------------------*/
s8 sys_FreeGraphFile(void* addr,u8 free)
{
	u8	i = 0;
	
	if(addr == NULL){
		return 0xFF;
	}
	//キャッシュ内を走査する
	for(i = 0;i < FILE_CACHE_MAX;i++){	
		if(FileCache[i].memory != addr){
			continue;
		}
		//HITした
		if(free){
			//キャッシュを破棄
			NNS_G3dResDefaultRelease(FileCache[i].memory);	//リソース解放処理
			sys_FreeMemory(GRAPHIC3D_HEAP_AREA,FileCache[i].memory);
			FileCache[i].memory = NULL;
			FileCache[i].hash   = 0;
			return 1;
		}else{
			return 2;	//キャッシュに登録されているので非解放
		}
	}
	//キャッシュに登録されていなかったので普通に解放
	NNS_G3dResDefaultRelease(FileCache[i].memory);	//リソース解放処理
	sys_FreeMemory(GRAPHIC3D_HEAP_AREA,FileCache[i].memory);
	FileCache[i].memory = NULL;
	FileCache[i].hash = 0;

	return 0;
}
#endif


/*---------------------------------------------------------------------------*
  Name:         sys_KeyRead

  Description:  キーを読み込み、トリガとリリーストリガを求めます。
				
  Arguments:    なし。
  Returns:      なし。
 *---------------------------------------------------------------------------*/

//初期化
void sys_InitKeyRead(void)
{
	TPCalibrateParam calibrate;

	sys.key_control_mode = 0;	//キー取得モード

	sys.cont_org	= 0;	// キー状態
	sys.trg_org		= 0;	// キートリガー
	sys.repeat_org	= 0;	// キーリピート
	sys.cont		= 0;	// キー状態(ゲーム設定により変換処理が入る)
	sys.trg			= 0;	// キートリガー(ゲーム設定により変換処理が入る)
	sys.repeat      = 0;	// キーリピート(ゲーム設定により変換処理が入る)
	sys.repeatWait_Count = 0;
	sys.repeatSpeed	= 8;
	sys.repeatWait	= 15;


	sys.tp_x		 = 0;	// タッチパネルX座標
	sys.tp_y		 = 0;	// タッチパネルY座標
	sys.tp_trg		 = 0;	// タッチパネル接触判定トリガ
	sys.tp_cont		 = 0;	// タッチパネル接触判定状態
	sys.tp_auto_samp = 0;	// タッチパネルのオートサンプリングを行っているかのフラグ
									
	// タッチパネルの初期化とキャリブレーションをセット
	TP_Init();

	// マシンのキャリブレーション値を取得
	if( TP_GetUserInfo( &calibrate ) == TRUE ){
		// キャリブレーション値の設定
		TP_SetCalibrateParam( &calibrate );
		OS_Printf("Get Calibration Parameter from NVRAM\n");
	}
	else{
		// 取得に失敗したのでデフォルトのキャリブレーションの設定
		calibrate.x0 = 0x02ae;
		calibrate.y0 = 0x058c;
		calibrate.xDotSize = 0x0e25;
		calibrate.yDotSize = 0x1208;
		TP_SetCalibrateParam( &calibrate );
		OS_Printf( "Warrning : TauchPanelInit( not found valid calibration data )\n" );
	}
}

/*---------------------------------------------------------------------------*
  @brief	ＡＧＢカートリッジ初期化
 *---------------------------------------------------------------------------*/
void sys_InitAgbCasetteVer(int version)
{
	sys.AgbCasetteVersion = version;
}

/*---------------------------------------------------------------------------*
  @brief	スリープ状態を禁止する
 *---------------------------------------------------------------------------*/
void sys_SleepNG(u8 sleepTypeBit)
{
	sys.DontSleep |= sleepTypeBit;
}

/*---------------------------------------------------------------------------*
  @brief	スリープ状態を許可する
 *---------------------------------------------------------------------------*/
void sys_SleepOK(u8 sleepTypeBit)
{
	sys.DontSleep &= ~(sleepTypeBit);
}

//------------------------------------------------------------------
static void KeyConvert(void);

//読み取り

void sys_MainKeyRead(void)
{
	TPData	tpTemp;
	TPData	tpDisp;
	int	keyData;

	// ふたが閉まっている場合は全ての入力をなしにする
	if(PAD_DetectFold()){
	  sys.trg	= 0;
	  sys.cont	= 0;
	  sys.repeat	= 0;
	  sys.tp_trg	= 0;
	  sys.tp_cont	= 0;
	  return;
	}

	keyData = PAD_Read();
	
	sys.trg_org		= keyData & (keyData ^ sys.cont_org);	// トリガ 入力

    sys.repeat_org	=	keyData & (keyData ^ sys.cont_org);        // リピート 入力

    if((keyData!=0)&&(sys.cont_org==keyData)){
		if(--sys.repeatWait_Count==0){
			sys.repeat_org				=	keyData;
			sys.repeatWait_Count	=	sys.repeatSpeed;
		}
	}
	else{
		sys.repeatWait_Count = sys.repeatWait;
	}


	sys.cont_org	= keyData;							// ベタ 入力

	sys.trg		= sys.trg_org;
	sys.cont	= sys.cont_org;
	sys.repeat	= sys.repeat_org;

	KeyConvert();

	// タッチパネルデータを取得
	if(sys.tp_auto_samp == 0){
		while( TP_RequestRawSampling( &tpTemp ) != 0 ){};	//サンプリングに成功するまで待つ
	}else{
		TP_GetLatestRawPointInAuto( &tpTemp );	// オートサンプリング中のデータを取得
	}

	TP_GetCalibratedPoint( &tpDisp, &tpTemp );	// 座標を画面座標（０～２５５）にする

#if 0	// 2006.07.05	座標取得失敗時処理を変更
	switch(tpDisp.validity){		// 座標の有効性をチェック
	case TP_VALIDITY_INVALID_X:
		sys.tp_x = 0xffff;
		sys.tp_y = tpDisp.y;
		break;
	case TP_VALIDITY_INVALID_Y:
		sys.tp_x = tpDisp.x;			// 座標をセット
		sys.tp_y = 0xffff;
		break;
	case TP_VALIDITY_INVALID_XY:
		sys.tp_x = 0xffff;
		sys.tp_y = 0xffff;
		break;
	default:
		sys.tp_x = tpDisp.x;
		sys.tp_y = tpDisp.y;
	}

	sys.tp_trg	= (u16)(tpDisp.touch & (tpDisp.touch ^ sys.tp_cont));	// トリガ 入力
	sys.tp_cont	= tpDisp.touch;										// ベタ 入力
	
#endif	/// 
	
	if( tpDisp.validity == TP_VALIDITY_VALID  ){		// 座標の有効性をチェック
		// タッチパネル座標有効
		sys.tp_x = tpDisp.x;
		sys.tp_y = tpDisp.y;
	}else{
		// タッチパネル座標無効
		// 1シンク前の座標が格納されているときのみ座標をそのまま受け継ぐ
		if( sys.tp_cont ){
			switch(tpDisp.validity){
			case TP_VALIDITY_INVALID_X:
				sys.tp_y = tpDisp.y;
				break;
			case TP_VALIDITY_INVALID_Y:
				sys.tp_x = tpDisp.x;
				break;
			case TP_VALIDITY_INVALID_XY:
				break;
			default:	// 正常
				break;
			}
		}else{
			// トリガのタイミングなら、
			// タッチパネルを押していないことにする
			tpDisp.touch = 0;
		}
	}
	sys.tp_trg	= (u16)(tpDisp.touch & (tpDisp.touch ^ sys.tp_cont));	// トリガ 入力
	sys.tp_cont	= tpDisp.touch;										// ベタ 入力

}

//--------------------------------------------------------------------------------------------
/**
 * キー情報の変換
 *
 * @param	none
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define KEYCONV( key, check_pat, set_pat )	{ if( key & check_pat ) key |= set_pat; }
#define KEYCONV_RESET( key, check_pat, set_pat ) {	\
	if( key & check_pat ){							\
		key |= set_pat;								\
		key &= ( check_pat^0xffff );				\
	}												\
}
#define KEYCONV_EXCHANGE( key, pat1, pat2 ) {	\
	int	tmp = 0;								\
	if( key & pat1 ){							\
		tmp |= pat2;							\
	}											\
	if( key & pat2 ){							\
		tmp |= pat1;							\
	}											\
	key &= ( (pat1 | pat2 )^0xffff );			\
	key |= tmp;									\
}
#define KEY_RESET( key, reset_pat ) {			\
	key &= ( reset_pat^0xffff );				\
}

static void KeyConvert(void)
{
	switch( sys.key_control_mode ){

	default:
	case KEYCONTROL_NORMAL:
		break;

	case KEYCONTROL_PATTERN1:

		KEYCONV( sys.trg, PAD_BUTTON_START, PAD_BUTTON_X )
		KEYCONV( sys.cont, PAD_BUTTON_START, PAD_BUTTON_X )
		KEYCONV( sys.repeat, PAD_BUTTON_START, PAD_BUTTON_X )
		break;

	case KEYCONTROL_PATTERN2:

		KEYCONV_EXCHANGE( sys.trg, PAD_BUTTON_X,PAD_BUTTON_Y )
		KEYCONV_EXCHANGE( sys.cont, PAD_BUTTON_X,PAD_BUTTON_Y )
		KEYCONV_EXCHANGE( sys.repeat, PAD_BUTTON_X,PAD_BUTTON_Y )
		break;

	case KEYCONTROL_PATTERN3:

		KEYCONV( sys.trg, PAD_BUTTON_L, PAD_BUTTON_A )
		KEYCONV( sys.cont, PAD_BUTTON_L, PAD_BUTTON_A )
		KEYCONV( sys.repeat, PAD_BUTTON_L, PAD_BUTTON_A )

		KEY_RESET( sys.trg, ( PAD_BUTTON_L | PAD_BUTTON_R ) )
		KEY_RESET( sys.cont, ( PAD_BUTTON_L | PAD_BUTTON_R ) )
		KEY_RESET( sys.repeat, ( PAD_BUTTON_L | PAD_BUTTON_R ) )
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * キーリピートの速度とウェイトをセット
 *
 * @param	speed	速度
 * @param	wait	ウェイト
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void sys_KeyRepeatSpeedSet( int speed, int wait )
{
	sys.repeatSpeed	= speed;
	sys.repeatWait	= wait;
}


/*---------------------------------------------------------------------------*
  @brief	ソフトウエアリセット状態を禁止する
 *---------------------------------------------------------------------------*/
void sys_SoftResetNG(u8 softResetBit)
{
	sys.DontSoftReset |= softResetBit;
}

/*---------------------------------------------------------------------------*
  @brief	ソフトウエアリセット状態を許可する
 *---------------------------------------------------------------------------*/
void sys_SoftResetOK(u8 softResetBit)
{
	sys.DontSoftReset &= ~(softResetBit);
}


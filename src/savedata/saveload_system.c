//============================================================================================
/**
 * @file	saveload_system.c
 * @brief	セーブロードシステム
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.12
 *
 * @li		2006.04.17	savedata.cから分離
 */
//============================================================================================

#include "common.h"
#include "gflib/system.h"

#include "savedata/savedata.h"
#include "savedata_local.h"

#include "application/backup.h"	//SaveErrorWarningCall


//=============================================================================
//=============================================================================

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#define MAGIC_NUMBER	(0x20060623)
#define	SECTOR_SIZE		(SAVE_SECTOR_SIZE)
#define SECTOR_MAX		(SAVE_PAGE_MAX)

#define	FIRST_MIRROR_START	(0)
#define	SECOND_MIRROR_START	(64)

#define MIRROR1ST	(0)
#define	MIRROR2ND	(1)
#define	MIRRORERROR	(2)

#define HEAPID_SAVE_TEMP	(HEAPID_BASE_APP)


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#define	SEC_DATA_SIZE		SECTOR_SIZE


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
typedef struct {
	u32 g_count;		///<グローバルカウンタ（MYデータ、BOXデータ共有）
	u32 b_count;		///<ブロック内カウンタ（MYデータとBOXデータとで独立）
	u32 size;			///<データサイズ（フッタサイズ含む）
	u32 magic_number;	///<マジックナンバー
	u8 blk_id;			///<対象のブロック指定ID
	u16 crc;			///<データ全体のCRC値
}SAVE_FOOTER;

//---------------------------------------------------------------------------
/**
 * @brief	セーブブロックデータ情報
 */
//---------------------------------------------------------------------------
typedef struct {
	u8 id;				///<ブロック定義ID
	u8 start_sec;		///<開始セクタ位置
	u8 use_sec;			///<占有セクタ数
	u32 start_ofs;		///<セーブデータでの開始オフセット
	u32 size;			///<セーブデータの占有サイズ
}SVBLK_INFO;

//---------------------------------------------------------------------------
/**
 * @brief	セーブデータ項目ごとの情報定義
 */
//---------------------------------------------------------------------------
typedef struct {
	GMDATA_ID gmdataID;	///<セーブデータ識別ID
	u32 size;			///<データサイズ格納
	u32 address;		///<データ開始位置
	u16 crc;			///<エラー検出用CRCコード格納
	u16 blockID;		///<所属ブロックのID
}SVPAGE_INFO;

//---------------------------------------------------------------------------
/**
 * @brief	セーブワーク構造体
 *
 * 実際のセーブされる部分の構造
 */
//---------------------------------------------------------------------------
typedef struct {
	u8 data[SECTOR_SIZE * SECTOR_MAX];	///<実際のデータ保持領域
}SAVEWORK;


//---------------------------------------------------------------------------
/**
 * @brief	分割転送制御用ワーク
 */
//---------------------------------------------------------------------------
typedef struct {
	BOOL total_save_mode;
	int block_start;
	int block_current;
	int block_end;
	s32 lock_id;
	int div_seq;
	u32 g_backup;
	u32 b_backup[SVBLK_ID_MAX];
}NEWDIVSV_WORK;


//---------------------------------------------------------------------------
/**
 * @brief	セーブデータ構造体
 *
 * セーブデータ自体と、制御用ワークをまとめたもの
 */
//---------------------------------------------------------------------------
struct _SAVEDATA {
	BOOL flash_exists;			///<バックアップFLASHが存在するかどうか
	BOOL data_exists;			///<データが存在するかどうか
	BOOL new_data_flag;			///<「さいしょから」のデータかどうか
	BOOL total_save_flag;		///<全体セーブが必要かどうかのフラグ
	LOAD_RESULT first_status;	///<一番最初のセーブデータチェック結果

	MATHCRC16Table crc_table;	///<CRC算出用テーブル

	SAVEWORK svwk;				///<セーブデータ本体

	u32 global_counter;
	u32 current_counters[SVBLK_ID_MAX];
	u8 current_side[SVBLK_ID_MAX];

	///セーブ項目データ情報
	SVPAGE_INFO pageinfo[GMDATA_ID_MAX];

	///セーブブロックデータ情報
	SVBLK_INFO blkinfo[SVBLK_ID_MAX];

	///分割転送制御用ワーク
	NEWDIVSV_WORK ndsw;

	int dendou_sector_switch;
	u32 dendou_counter;
};


//============================================================================================
//
//
//			変数
//
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	セーブデータ構造体へのポインタ
 *
 * このファイルで唯一静的確保される変数。
 * ゲーム開始時に初期化される。
 */
//---------------------------------------------------------------------------
static SAVEDATA * SvPointer = NULL;


//============================================================================================
//
//
//			公開関数
//
//
//============================================================================================
static void SVDT_Init(SAVEWORK * svwk, const SVPAGE_INFO * pageinfo);
static void SVDT_MakeIndex(SVPAGE_INFO * pageinfo);
static void SVDT_MakeBlockIndex(SVBLK_INFO * blkinfo, const SVPAGE_INFO * pageinfo);


static BOOL NewSVLD_Save(SAVEDATA * sv);
static BOOL NewSVLD_Load(SAVEDATA * sv);
static LOAD_RESULT NewCheckLoadData(SAVEDATA * sv);
static void NEWSVLD_DivSaveInit(SAVEDATA * sv, NEWDIVSV_WORK * ndsw, int block_id);
static SAVE_RESULT NEWSVLD_DivSaveMain(SAVEDATA * sv, NEWDIVSV_WORK * ndsw);
static void NEWSVLD_DivSaveEnd(SAVEDATA * sv, NEWDIVSV_WORK * ndsw, SAVE_RESULT result);
static void NEWSVLD_DivSaveCancel(SAVEDATA * sv, NEWDIVSV_WORK * ndsw);

static BOOL EraseFlashFooter(const SAVEDATA * sv, int block_id, int mirror_side);

static int GetTotalSector(const SAVEDATA * sv);

static s32 PMSVLD_DivSave_Init(u32 src, void * dst, u32 len);
static BOOL PMSVLD_DivSave_Main(s32 lock_id, BOOL * result);
static void PMSVLD_SaveError(s32 lock_id, int error_msg_id);
//---------------------------------------------------------------------------
/**
 * @brief	セーブデータ構造の初期化
 */
//---------------------------------------------------------------------------
SAVEDATA * SaveData_System_Init(void)
{
	SAVEDATA * sv;


	sv = sys_AllocMemory(HEAPID_BASE_SAVE, sizeof(SAVEDATA));
	MI_CpuClearFast(sv, sizeof(SAVEDATA));
	SvPointer = sv;
	sv->flash_exists = PMSVLD_Init();
	sv->data_exists = FALSE;			//データは存在しない
	sv->new_data_flag = TRUE;			//新規データになる
	sv->total_save_flag = TRUE;			//全体セーブの必要がある
	MATH_CRC16CCITTInitTable(&sv->crc_table);
	SVDT_MakeIndex(sv->pageinfo);
	SVDT_MakeBlockIndex(sv->blkinfo, sv->pageinfo);
	MI_CpuClearFast(sv->current_counters, sizeof(sv->current_counters));


	//データ存在チェックを行っている
	sv->first_status = NewCheckLoadData(sv);
	switch (sv->first_status) {
	case LOAD_RESULT_OK:
	case LOAD_RESULT_NG:
		//まともなデータがあるようなので読み込む
		NewSVLD_Load(sv);
		sv->data_exists = TRUE;			//データは存在する
		sv->new_data_flag = FALSE;		//新規データではない
		sv->total_save_flag = FALSE;	//全体セーブの必要はない
		break;
	case LOAD_RESULT_NULL:
	case LOAD_RESULT_BREAK:
		//新規 or データ破壊なのでクリアする
		SaveData_ClearData(sv);
		break;
	}

#ifdef	PM_DEBUG
	{
		int i, rest;
		for (i = 0; i < SVBLK_ID_MAX; i++) {
			OS_TPrintf("[%d] ",i);
			OS_TPrintf("(%04x x %02d) - %05x = %05x\n",
					SEC_DATA_SIZE,sv->blkinfo[i].use_sec,
					sv->blkinfo[i].size,
					SEC_DATA_SIZE * sv->blkinfo[i].use_sec - sv->blkinfo[i].size);
		}
		rest = SECTOR_MAX - GetTotalSector(sv);
		if (rest > 0) {
			OS_TPrintf("%2d sector(0x%05x) left.\n", rest, 0x1000 * rest);
		}
	}
#endif

	return sv;
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブデータへのポインタ取得
 * @return	SAVEDATA	セーブデータ構造へのポインタ
 *
 * 基本的にはセーブデータへのグローバル参照は避けたい。そのため、この関数を
 * 使用する箇所は厳重に制限されなければならない。できればプログラマリーダーの
 * 許可がなければ使用できないようにしたい。
 * 変なアクセスをしたら修正がかかります。使用方法には注意してください。
 */
//---------------------------------------------------------------------------
SAVEDATA * SaveData_GetPointer(void)
{
	GF_ASSERT(SvPointer != NULL);
	return SvPointer;
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブデータ（部分）のポインタを取得する
 * @param	sv			セーブデータ構造へのポインタ
 * @param	gmdataID	取得したいセーブデータのID
 * @return	必要なセーブ領域へのポインタ
 */
//---------------------------------------------------------------------------
void * SaveData_Get(SAVEDATA * sv, GMDATA_ID gmdataID)
{
	GF_ASSERT(gmdataID < GMDATA_ID_MAX);
	return &(sv->svwk.data[sv->pageinfo[gmdataID].address]);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
const void * SaveData_GetReadOnlyData(const SAVEDATA * sv, GMDATA_ID gmdataID)
{
	return SaveData_Get((SAVEDATA *)sv, gmdataID);
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブデータの消去処理
 * @param	sv			セーブデータ構造へのポインタ
 * @retval	TRUE		書き込み成功
 * @retval	FALSE		書き込み失敗
 *
 * セーブデータをクリアした上でフラッシュに書き込む。
 */
//---------------------------------------------------------------------------
BOOL SaveData_Erase(SAVEDATA * sv)
{
	int i, j;
	u8 * buf = sys_AllocMemoryLo(HEAPID_SAVE_TEMP, SECTOR_SIZE);
	sys_SleepNG(SLEEPTYPE_SAVELOAD);

	//各ブロックのフッタ部分だけを先行して削除する
	EraseFlashFooter(sv, SVBLK_ID_NORMAL, !sv->current_side[SVBLK_ID_NORMAL]);
	EraseFlashFooter(sv, SVBLK_ID_BOX, !sv->current_side[SVBLK_ID_BOX]);
	EraseFlashFooter(sv, SVBLK_ID_NORMAL, sv->current_side[SVBLK_ID_NORMAL]);
	EraseFlashFooter(sv, SVBLK_ID_BOX, sv->current_side[SVBLK_ID_BOX]);

	MI_CpuFillFast(buf, 0xffffffff, SECTOR_SIZE);
	for (i = 0; i < SECTOR_MAX * 2; i++) {
		PMSVLD_Save(SECTOR_SIZE * (i + FIRST_MIRROR_START), buf, SECTOR_SIZE);
		PMSVLD_Save(SECTOR_SIZE * (i + SECOND_MIRROR_START), buf, SECTOR_SIZE);
	}
	sys_FreeMemoryEz(buf);
	SaveData_ClearData(sv);
	sv->data_exists = FALSE;
	sys_SleepOK(SLEEPTYPE_SAVELOAD);

	return TRUE;
}

//---------------------------------------------------------------------------
/**
 * @brief	ロード処理
 * @param	sv			セーブデータ構造へのポインタ
 * @retval	TRUE		読み込み成功
 * @retval	FALSE		読み込み失敗
 */
//---------------------------------------------------------------------------
BOOL SaveData_Load(SAVEDATA * sv)
{
	BOOL result;
	if (!sv->flash_exists) {
		return FALSE;
	}

	result = NewSVLD_Load(sv);

	if (result) {
		sv->data_exists = TRUE;			//データは存在する
		sv->new_data_flag = FALSE;		//新規データではない
		return TRUE;
	} else {
		return FALSE;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブ処理
 * @param	sv			セーブデータ構造へのポインタ
 * @retval	TRUE		書き込み成功
 * @retval	FALSE		書き込み失敗
 */
//---------------------------------------------------------------------------
SAVE_RESULT SaveData_Save(SAVEDATA * sv)
{
	SAVE_RESULT result;

	if (!sv->flash_exists) {
#ifdef	DISABLE_FLASH_CHECK		//バックアップフラッシュなしでも動作
		return SAVE_RESULT_OK;
#else
		return SAVE_RESULT_NG;
#endif
	}

	result = NewSVLD_Save(sv);

	if (result == SAVE_RESULT_OK) {
		sv->data_exists = TRUE;			//データは存在する
		sv->new_data_flag = FALSE;		//新規データではない
	}
	return result;
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブ処理（部分）
 * @param	sv			セーブデータ構造へのポインタ
 * @param	id			セーブ対象のブロックID
 * @retval	TRUE		書き込み成功
 * @retval	FALSE		書き込み失敗
 *
 * id　にSVBLK_ID_MAXを指定すると全体セーブとなる
 */
//---------------------------------------------------------------------------
SAVE_RESULT SaveData_SaveParts(SAVEDATA * sv, SVBLK_ID id)
{
	SAVE_RESULT result;

	GF_ASSERT(id < SVBLK_ID_MAX);
	GF_ASSERT(sv->new_data_flag == FALSE);
	GF_ASSERT(sv->data_exists == TRUE);
	SaveData_DivSave_Init(sv, id);
	do {
		result = SaveData_DivSave_Main(sv);
	}while(result == SAVE_RESULT_CONTINUE || result == SAVE_RESULT_LAST);
	return result;
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブデータの初期化
 * @param	sv			セーブデータ構造へのポインタ
 *
 * SaveData_Eraseと違い、フラッシュに書き込まない。
 * セーブデータがある状態で「さいしょから」遊ぶ場合などの初期化処理
 */
//---------------------------------------------------------------------------
void SaveData_ClearData(SAVEDATA * sv)
{
	sv->new_data_flag = TRUE;				//新規データである
	sv->total_save_flag = TRUE;				//全体セーブする必要がある
	SVDT_Init(&sv->svwk, sv->pageinfo);
}

//---------------------------------------------------------------------------
/**
 * @brief	フラッシュ存在フラグのチェック
 * @param	sv			セーブデータ構造へのポインタ
 * @return	BOOL		TRUEのとき、フラッシュが存在する
 */
//---------------------------------------------------------------------------
BOOL SaveData_GetFlashExistsFlag(const SAVEDATA * sv)
{
	return sv->flash_exists;
}

//---------------------------------------------------------------------------
/**
 * @brief	最初の読み込み結果を返す
 * @param	sv			セーブデータ構造へのポインタ
 * @return	LOAD_RESULT	読み込み結果（savedata_def.h参照）
 */
//---------------------------------------------------------------------------
LOAD_RESULT SaveData_GetLoadResult(const SAVEDATA * sv)
{
	return sv->first_status;
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブデータ存在フラグを取得
 * @param	sv			セーブデータ構造へのポインタ
 * @return	BOOL		TRUEのとき、セーブデータが存在する
 */
//---------------------------------------------------------------------------
BOOL SaveData_GetExistFlag(const SAVEDATA * sv)
{
	return sv->data_exists;
}

//---------------------------------------------------------------------------
/**
 * @brief	新規ゲーム状態を取得
 * @param	sv			セーブデータ構造へのポインタ
 * @param	BOOL		TRUEのとき、新規ゲーム（でまだセーブしていない）
 */
//---------------------------------------------------------------------------
BOOL SaveData_GetNewDataFlag(const SAVEDATA * sv)
{
	return sv->new_data_flag;
}

//---------------------------------------------------------------------------
/**
 * @brief	データ上書きチェック
 * @param	sv			セーブデータ構造へのポインタ
 * @retval	TRUE		既にあるデータに別のデータを上書きしようとしている
 * @retval	FALSE		データがないか、既存データである
 */
//---------------------------------------------------------------------------
BOOL SaveData_IsOverwritingOtherData(const SAVEDATA * sv)
{
	if (SaveData_GetNewDataFlag(sv) && SaveData_GetExistFlag(sv)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	全体セーブが必要な状態かどうかを判定する
 * @param	sv			セーブデータ構造へのポインタ
 * @return	BOOL		TRUEのとき、全体セーブが必要（ボックスが更新されている）
 */
//---------------------------------------------------------------------------
BOOL SaveData_GetTotalSaveFlag(const SAVEDATA * sv)
{
	return sv->total_save_flag;
}

//---------------------------------------------------------------------------
/**
 * @brief	全体セーブを要求する
 */
//---------------------------------------------------------------------------
void SaveData_RequestTotalSave(void)
{
	SvPointer->total_save_flag = TRUE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static int GetTotalSector(const SAVEDATA * sv)
{
	int i;
	int total = 0;
	const SVBLK_INFO * blkinfo = sv->blkinfo;
	for (i = 0; i < SVBLK_ID_MAX; i++) {
		total += blkinfo[i].use_sec;
	}
	GF_ASSERT(total == blkinfo[SVBLK_ID_MAX-1].start_sec + blkinfo[SVBLK_ID_MAX-1].use_sec);
	return total;
}

//============================================================================================
//
//
//		メインデータセーブ処理
//
//
//============================================================================================

//---------------------------------------------------------------------------
/**
 * @brief	分割セーブ初期化
 * @param	sv			セーブデータ構造へのポインタ
 */
//---------------------------------------------------------------------------
void SaveData_DivSave_Init(SAVEDATA * sv, int BlockID)
{
	NEWSVLD_DivSaveInit(sv, &sv->ndsw, BlockID);
}

//---------------------------------------------------------------------------
/**
 * @brief	分割セーブメイン処理
 * @param	sv			セーブデータ構造へのポインタ
 * @return	SAVE_RESULT
 */
//---------------------------------------------------------------------------
SAVE_RESULT SaveData_DivSave_Main(SAVEDATA * sv)
{
	SAVE_RESULT result;
	result = NEWSVLD_DivSaveMain(sv, &sv->ndsw);
	if (result != SAVE_RESULT_CONTINUE && result != SAVE_RESULT_LAST) {
		NEWSVLD_DivSaveEnd(sv, &sv->ndsw, result);
	}
	return result;
}

//---------------------------------------------------------------------------
/**
 * @brief	分割セーブキャンセル処理
 * @param	sv			セーブデータ構造へのポインタ
 */
//---------------------------------------------------------------------------
void SaveData_DivSave_Cancel(SAVEDATA * sv)
{
	NEWSVLD_DivSaveCancel(sv, &sv->ndsw);
}

//============================================================================================
//
//
//			セーブデータ整合性チェック
//
//
//============================================================================================
typedef struct {
	BOOL IsCorrect;
	u32 g_count;
	u32 b_count;
}CHK_INFO;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
 * @brief	セーブデータの取りえる状態について
 *
 * ありえるパターンについて！
 * 上下は進行データとボックスデータ、左右はミラーの組。正常化どうかが4ビットあるので
 * 16通りのパターンとなる
 *
 *	０		１		２		３
 *	○○	○○	○○	○○
 *	○○	○×	×○	××
 *
 *	４		５		６		７
 *	○×	○×	○×	○×
 *	○○	○×	×○	××
 *
 *	８		９		１０	１１
 *	×○	×○	×○	×○
 *	○○	○×	×○	××
 *
 *	１２	１３	１４	１５
 *	××	××	××	××
 *	○○	○×	×○	××
 */

#ifdef	DEBUG_ONLY_FOR_tamada
//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
static void _DebugPutFooter(const SAVE_FOOTER * footer)
{
	OS_TPrintf("FOOTER:adrs:%08x",footer);
	OS_TPrintf(" size:%05x\n",footer->size);
	OS_TPrintf("FOOTER:GCNT:%08x",footer->g_count);
	OS_TPrintf(" BCNT:%08x\n",footer->b_count);
	//OS_TPrintf("FOOTER:MGNR:%08x\n",footer->magic_number);
	OS_TPrintf("FOOTER:BKID:%02d",footer->blk_id);
	OS_TPrintf(" CRC :%04x\n",footer->crc);
}
static void _DebugPutOX(BOOL flag)
{
	if (flag) {
		OS_PutString(" O");
	} else {
		OS_PutString(" X");
	}
}
#define	DEBUG_FOOTER_PUT(footer)	_DebugPutFooter(footer)
#define	DEBUG_OX_PUT(value)			_DebugPutOX(value)
#else
#define	DEBUG_FOOTER_PUT(footer)	/* DO NOTHING */
#define	DEBUG_OX_PUT(value)			/* DO NOTHING */
#endif

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static void _setDummyInfo(CHK_INFO * chkinfo)
{
	chkinfo->IsCorrect = FALSE;
	chkinfo->g_count = 0;
	chkinfo->b_count = 0;
}
//---------------------------------------------------------------------------
/**
 * @brief	CRCの計算
 * @param	sv		
 * @param	start	セーブデータの開始アドレス
 * @param	size	セーブデータのサイズ（フッタ部分含む）
 */
//---------------------------------------------------------------------------
static u16 _calcFooterCrc(const SAVEDATA * sv, void * start, u32 size)
{
	return MATH_CalcCRC16CCITT(&sv->crc_table, start, size - sizeof(SAVE_FOOTER));
}
//---------------------------------------------------------------------------
/**
 * @brief	セーブフラッシュへのアドレスオフセット取得
 * @param	mirror_id	対象とするミラーの指定（0 or 1)
 * @param	blkinfo		ブロック情報へのポインタ
 */
//---------------------------------------------------------------------------
static u32 _getFlashOffset(int mirror_id, const SVBLK_INFO * blkinfo)
{
	u32 base_ofs;
	if (mirror_id == MIRROR1ST) {
		base_ofs = FIRST_MIRROR_START * SECTOR_SIZE;
	} else {
		base_ofs = SECOND_MIRROR_START * SECTOR_SIZE;
	}
	base_ofs += blkinfo->start_ofs;
	return base_ofs;
}

//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
static SAVE_FOOTER * _getFooterAddress(SAVEDATA * sv, u32 svwk_adrs, int blk_id)
{
	u32 start_adr;
	const SVBLK_INFO * blkinfo = &sv->blkinfo[blk_id];

	start_adr = svwk_adrs + blkinfo->start_ofs;
	GF_ASSERT(blkinfo->size);
	start_adr += blkinfo->size;
	start_adr -= sizeof(SAVE_FOOTER);
	return (SAVE_FOOTER *)start_adr;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static BOOL _checkSaveFooter(SAVEDATA * sv, u32 svwk_adrs, int blk_id)
{
	const SVBLK_INFO * blkinfo = &sv->blkinfo[blk_id];
	SAVE_FOOTER * footer = _getFooterAddress(sv, svwk_adrs, blk_id);
	u32 start_adr = svwk_adrs + blkinfo->start_ofs;

	DEBUG_FOOTER_PUT(footer);
	if (footer->size != blkinfo->size) {
		return FALSE;
	}
	if (footer->magic_number != MAGIC_NUMBER) {
		return FALSE;
	}
	if (footer->blk_id != blk_id) {
		return FALSE;
	}
	if (footer->crc != _calcFooterCrc(sv, (void *)start_adr, blkinfo->size)) {
		return FALSE;
	}
	return TRUE;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static void _checkBlockInfo(CHK_INFO * chkinfo, SAVEDATA * sv, u32 svwk_adrs, int blk_id)
{
	SAVE_FOOTER * footer = _getFooterAddress(sv, svwk_adrs, blk_id);
	chkinfo->IsCorrect = _checkSaveFooter(sv, svwk_adrs, blk_id);
	chkinfo->g_count = footer->g_count;
	chkinfo->b_count = footer->b_count;
}
//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
static void _setSaveFooter(SAVEDATA * sv, u32 svwk_adrs, int blk_id)
{
	const SVBLK_INFO * blkinfo = &sv->blkinfo[blk_id];
	SAVE_FOOTER * footer = _getFooterAddress(sv, svwk_adrs, blk_id);
	u32 start_adr = svwk_adrs + blkinfo->start_ofs;

	footer->g_count = sv->global_counter;
	footer->b_count = sv->current_counters[blk_id];
	footer->size = blkinfo->size;
	footer->magic_number = MAGIC_NUMBER;
	footer->blk_id = blk_id;
	footer->crc = _calcFooterCrc(sv, (void *)start_adr, blkinfo->size);

	DEBUG_FOOTER_PUT(footer);
}

//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
static int _diffCounter(u32 counter1, u32 counter2)
{
	if (counter1 == 0xffffffff && counter2 == 0) {
		return -1;
	}else if (counter1 == 0 && counter2 == 0xffffffff) {
		return 1;
	} else if (counter1 > counter2) {
		return 1;
	} else if (counter1 < counter2) {
		return -1;
	}
	return 0;
}

//---------------------------------------------------------------------------
/**
 * @brief	データのカウンタを調べる
 * @param	chk1	調べるデータその１
 * @param	chk2	調べるデータその２
 * @param	res1	最新データへのオフセット
 * @param	res2	古いデータへのオフセット
 * @return	int		正常なデータの数
 */
//---------------------------------------------------------------------------
static int _getNewerData(const CHK_INFO * chk1, const CHK_INFO * chk2, int *res1, int *res2)
{
	int global, block;
	global = _diffCounter(chk1->g_count, chk2->g_count);
	block = _diffCounter(chk1->b_count, chk2->b_count);

	if (chk1->IsCorrect && chk2->IsCorrect) {
		//両方とも正常の場合
		if (global > 0) {
			//GLOBALが違う場合＝全体セーブ直後
			GF_ASSERT(block > 0);
			*res1 = MIRROR1ST;
			*res2 = MIRROR2ND;
		}
		else if (global < 0) {
			//GLOBALが違う場合＝全体セーブ直後
			GF_ASSERT(block < 0);
			*res1 = MIRROR2ND;
			*res2 = MIRROR1ST;
		}
		else if (block > 0) {
			//GLOBALが同じ場合＝部分セーブ後
			*res1 = MIRROR1ST;
			*res2 = MIRROR2ND;
		} else if (block < 0) {
			*res1 = MIRROR2ND;
			*res2 = MIRROR1ST;
		} else {
			//GLOBALが同じでブロックカウンタも同じ
			//→ありえないはずだが,２Mフラッシュのためにとりあえず機能させる
			//GF_ASSERT(0);
			*res1 = MIRROR1ST;
			*res2 = MIRROR2ND;
		}
		return 2;
	}
	else if (chk1->IsCorrect && !chk2->IsCorrect) {
		//片方のみ正常の場合
		*res1 = MIRROR1ST;
		*res2 = MIRRORERROR;
		return 1;
	}
	else if (!chk1->IsCorrect && chk2->IsCorrect) {
		*res1 = MIRROR2ND;
		*res2 = MIRRORERROR;
		return 1;
	}
	else {
		*res1 = MIRRORERROR;
		*res2 = MIRRORERROR;
		return 0;
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static void _setCurrentInfo(SAVEDATA * sv, const CHK_INFO * ndata, const CHK_INFO * bdata,
		int n_ofs, int b_ofs)
{
	sv->global_counter = ndata[n_ofs].g_count;
	sv->current_counters[SVBLK_ID_NORMAL] = ndata[n_ofs].b_count;
	sv->current_counters[SVBLK_ID_BOX] = bdata[b_ofs].b_count;
	sv->current_side[SVBLK_ID_NORMAL] = n_ofs;
	sv->current_side[SVBLK_ID_BOX] = b_ofs;
#ifdef	DEBUG_ONLY_FOR_tamada
	OS_Printf("CURRENT NORMAL NML %d  BOX %d\n",n_ofs, b_ofs);
	OS_Printf("CURRENT COUNTER NML %08x BOX %08x\n", ndata[n_ofs].b_count, bdata[b_ofs].b_count);
	OS_Printf("CURRENT GLOBAL %08x\n", sv->global_counter);
#endif
}
//---------------------------------------------------------------------------
/**
 * @brief	セーブデータのチェック
 * @param	sv			セーブデータ構造へのポインタ
 * @retval	LOAD_RESULT		チェック結果
 */
//---------------------------------------------------------------------------
static LOAD_RESULT NewCheckLoadData(SAVEDATA * sv)
{
	CHK_INFO ndata[2];
	CHK_INFO bdata[2];
	u8 * buffer1;
	u8 * buffer2;
	int nres, bres;
	int n_main, b_main, n_sub, b_sub;

	buffer1 = sys_AllocMemoryLo(HEAPID_SAVE_TEMP, SECTOR_SIZE * SECTOR_MAX);
	buffer2 = sys_AllocMemoryLo(HEAPID_SAVE_TEMP, SECTOR_SIZE * SECTOR_MAX);

	if(PMSVLD_Load(FIRST_MIRROR_START * SECTOR_SIZE, buffer1, SECTOR_SIZE * SECTOR_MAX)) {
		_checkBlockInfo(&ndata[MIRROR1ST], sv, (u32)buffer1, SVBLK_ID_NORMAL);
		_checkBlockInfo(&bdata[MIRROR1ST], sv, (u32)buffer1, SVBLK_ID_BOX);
	} else {
		_setDummyInfo(&ndata[MIRROR1ST]);
		_setDummyInfo(&bdata[MIRROR1ST]);
	}
	if(PMSVLD_Load(SECOND_MIRROR_START * SECTOR_SIZE, buffer2, SECTOR_SIZE * SECTOR_MAX)) {
		_checkBlockInfo(&ndata[MIRROR2ND], sv, (u32)buffer2, SVBLK_ID_NORMAL);
		_checkBlockInfo(&bdata[MIRROR2ND], sv, (u32)buffer2, SVBLK_ID_BOX);
	} else {
		_setDummyInfo(&ndata[MIRROR2ND]);
		_setDummyInfo(&bdata[MIRROR2ND]);
	}

	sys_FreeMemoryEz(buffer1);
	sys_FreeMemoryEz(buffer2);

	nres = _getNewerData(&ndata[MIRROR1ST], &ndata[MIRROR2ND], &n_main, &n_sub);
	bres = _getNewerData(&bdata[MIRROR1ST], &bdata[MIRROR2ND], &b_main, &b_sub);
	{
		OS_PutString("SAVE NORMAL:");
		DEBUG_OX_PUT(ndata[MIRROR1ST].IsCorrect);
		DEBUG_OX_PUT(ndata[MIRROR2ND].IsCorrect);
		OS_TPrintf("...OK=%d\n",nres);
		OS_PutString("SAVE BOX   :");
		DEBUG_OX_PUT(bdata[MIRROR1ST].IsCorrect);
		DEBUG_OX_PUT(bdata[MIRROR2ND].IsCorrect);
		OS_TPrintf("...OK=%d\n",bres);
	}
	if (nres == 0 && bres == 0) {
		//通常データもボックスデータも壊れている→単にデータがないとみなす
		return LOAD_RESULT_NULL;		//パターン１５
	}
	if (nres == 0 || bres == 0) {
		//通常データかボックスデータかのどちらかが壊れている→破壊
		return LOAD_RESULT_BREAK;	//パターン３，７，１１、１２，１３，１４
	}

	if (nres == 2 && bres == 2){
		// 正常データが2組	
		if (ndata[n_main].g_count == bdata[b_main].g_count) {
			_setCurrentInfo(sv, ndata, bdata, n_main, b_main);
			return LOAD_RESULT_OK;	//パターン０
		} else {
			//進行データとボックスデータのセーブのちょうど間で
			//電源切断した場合
			_setCurrentInfo(sv, ndata, bdata, n_sub, b_main);
			return LOAD_RESULT_NG;	//パターン０
		}
	}
	if (nres == 1 && bres == 2) {
		//部分、あるいは全体書き込み中断による進行データ破壊
		if (ndata[n_main].g_count == bdata[b_main].g_count) {
			_setCurrentInfo(sv, ndata, bdata, n_main, b_main);
			return LOAD_RESULT_NG;	//パターン４、８
		} else if (ndata[n_main].g_count == bdata[b_sub].g_count) {
			_setCurrentInfo(sv, ndata, bdata, n_main, b_sub);
			return LOAD_RESULT_NG;	//パターン４、８
		}
		//GF_ASSERT(ndata[n_main].g_count == bdata[b_main].g_count);
		//_setCurrentInfo(sv, ndata, bdata, n_main, b_main);
		return LOAD_RESULT_BREAK;	//パターン４、８
	}
	if (nres == 2 && bres == 1) {
		if (ndata[n_main].g_count == bdata[b_main].g_count) {
			//初回セーブ後一度も全体セーブを行っていない場合
			_setCurrentInfo(sv, ndata, bdata, n_main, b_main);
			return LOAD_RESULT_OK;	//パターン１，２
		} else {
			//全体書き込み中断によるボックスデータ破壊
			//データの巻き戻しが発生する
			_setCurrentInfo(sv, ndata, bdata, n_sub, b_main);
			return LOAD_RESULT_NG;	//パターン１，２
		}
	}
	if (nres == 1 && bres == 1 && n_main == b_main) {
		// 正常データが一組 →初回
		GF_ASSERT(ndata[n_main].g_count == bdata[b_main].g_count);
		_setCurrentInfo(sv, ndata, bdata, n_main, b_main);
		return LOAD_RESULT_OK;	//パターン５、あるいは１０も
	} else {
		//初回セーブ、2,3回目を進行データのみにして3回目を中断で失敗した場合
		GF_ASSERT(ndata[n_main].g_count == bdata[b_main].g_count);
		_setCurrentInfo(sv, ndata, bdata, n_main, b_main);
		return LOAD_RESULT_NG;	//パターン６、９
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static BOOL _loadBlock(int mirror_id, const SVBLK_INFO * blkinfo, u8 * svwk)
{
	u32 base_ofs;

	base_ofs = _getFlashOffset(mirror_id, blkinfo);
	svwk += blkinfo->start_ofs;
	return PMSVLD_Load(base_ofs, svwk, blkinfo->size);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
BOOL NewSVLD_Load(SAVEDATA * sv)
{
	int i;
	u32 base_ofs;
	const SVBLK_INFO * blkinfo = sv->blkinfo;

	for (i = 0; i < SVBLK_ID_MAX; i++) {
		if (_loadBlock(sv->current_side[i], &sv->blkinfo[i], sv->svwk.data) == FALSE) {
			return FALSE;
		}
		if (_checkSaveFooter(sv, (u32)sv->svwk.data, i) == FALSE) {
			return FALSE;
		}
	}
	return TRUE;
}

//============================================================================================
//
//
//			分割セーブ
//
//
//============================================================================================
#define	LAST_DATA_SIZE	sizeof(SAVE_FOOTER)
//#define	LAST_DATA_SIZE	(8)
#define	LAST_DATA2_SIZE	(8)

//---------------------------------------------------------------------------
/**
 * @brief	非同期セーブセット：データメイン部分
 * @param	sv			セーブデータ構造へのポインタ
 * @param	block_id	セーブするブロック指定ID
 * @param	mirror_side	セーブするミラーの指定（0 or 1)
 */
//---------------------------------------------------------------------------
static s32 _saveDivStartMain(SAVEDATA *sv, int block_id, u8 mirror_side)
{
	u32 base_ofs;
	BOOL result;
	u8 * svwk;
	const SVBLK_INFO * blkinfo = &sv->blkinfo[block_id];

	_setSaveFooter(sv, (u32)sv->svwk.data, block_id);
	base_ofs = _getFlashOffset(mirror_side, blkinfo);
	svwk = sv->svwk.data + blkinfo->start_ofs;

	return PMSVLD_DivSave_Init(base_ofs, svwk, blkinfo->size - LAST_DATA_SIZE);
}

//---------------------------------------------------------------------------
/**
 * @brief	非同期セーブセット：フッタ部分
 * @param	sv			セーブデータ構造へのポインタ
 * @param	block_id	セーブするブロック指定ID
 * @param	mirror_side	セーブするミラーの指定（0 or 1)
 */
//---------------------------------------------------------------------------
static s32 _saveDivStartFooter(SAVEDATA *sv, int block_id, u8 mirror_side)
{
	u32 base_ofs;
	BOOL result;
	u8 * svwk;
	const SVBLK_INFO * blkinfo = &sv->blkinfo[block_id];

	//_setSaveFooter(sv, (u32)sv->svwk.data, block_id);
	base_ofs = _getFlashOffset(mirror_side, blkinfo) + blkinfo->size - LAST_DATA_SIZE;
	svwk = sv->svwk.data + blkinfo->start_ofs + blkinfo->size - LAST_DATA_SIZE;

	return PMSVLD_DivSave_Init(base_ofs, svwk, LAST_DATA_SIZE);
}

//---------------------------------------------------------------------------
/**
 * @brief	非同期セーブセット：フッタ部分
 * @param	sv			セーブデータ構造へのポインタ
 * @param	block_id	セーブするブロック指定ID
 * @param	mirror_side	セーブするミラーの指定（0 or 1)
 */
//---------------------------------------------------------------------------
static s32 _saveDivStartFooter2(SAVEDATA *sv, int block_id, u8 mirror_side)
{
	u32 base_ofs;
	BOOL result;
	u8 * svwk;
	const SVBLK_INFO * blkinfo = &sv->blkinfo[block_id];

	//_setSaveFooter(sv, (u32)sv->svwk.data, block_id);
	base_ofs = _getFlashOffset(mirror_side, blkinfo) + blkinfo->size - LAST_DATA_SIZE + LAST_DATA2_SIZE;
	svwk = sv->svwk.data + blkinfo->start_ofs + blkinfo->size - LAST_DATA_SIZE + LAST_DATA2_SIZE;

	return PMSVLD_DivSave_Init(base_ofs, svwk, LAST_DATA2_SIZE);
}



//---------------------------------------------------------------------------
/**
 * @brief	非同期セーブ処理：初期化
 * @param	sv			セーブデータ構造へのポインタ
 * @param	ndsw		非同期セーブ制御ワークへのポインタ
 * @param	block_id	セーブするブロック指定ID
 */
//---------------------------------------------------------------------------
static void NEWSVLD_DivSaveInit(SAVEDATA * sv, NEWDIVSV_WORK * ndsw, int block_id)
{
	int i;

	for (i = 0; i < SVBLK_ID_MAX; i++) {
		ndsw->b_backup[i] = sv->current_counters[i];
		sv->current_counters[i] ++;
	}

	ndsw->div_seq = 0;
	ndsw->total_save_mode = FALSE;

	if (block_id == SVBLK_ID_MAX) {
		if (sv->total_save_flag) {
			ndsw->total_save_mode = TRUE;
			ndsw->g_backup = sv->global_counter;
			sv->global_counter ++;

			ndsw->block_start = 0;
			ndsw->block_current = 0;
			ndsw->block_end = SVBLK_ID_MAX;
		} else {
			ndsw->block_start = SVBLK_ID_NORMAL;
			ndsw->block_current = SVBLK_ID_NORMAL;
			ndsw->block_end = SVBLK_ID_NORMAL + 1;
		}
	} else {
		ndsw->block_start = block_id;
		ndsw->block_current = block_id;
		ndsw->block_end = block_id + 1;
	}
	sys_SleepNG(SLEEPTYPE_SAVELOAD);
}

//---------------------------------------------------------------------------
/**
 * @brief	非同期セーブ処理：メイン
 * @param	sv			セーブデータ構造へのポインタ
 * @param	ndsw		非同期セーブ制御ワークへのポインタ
 * @retval	SAVE_RESULT_CONTINUE	セーブ継続中
 * @retval	SAVE_RESULT_LAST		セーブ継続中、最後の部分
 * @retval	SAVE_RESULT_OK			セーブ終了、成功
 * @retval	SAVE_RESULT_NG			セーブ終了、失敗
 */
//---------------------------------------------------------------------------
static SAVE_RESULT NEWSVLD_DivSaveMain(SAVEDATA * sv, NEWDIVSV_WORK * ndsw)
{
	BOOL result;

	switch (ndsw->div_seq) {
	case 0:
		OS_TPrintf("DIV SAVE:BLOCK %d SIDE %d\n",
				ndsw->block_current, !sv->current_side[ndsw->block_current]);
		ndsw->lock_id = _saveDivStartMain(sv, ndsw->block_current, !sv->current_side[ndsw->block_current]);
		ndsw->div_seq ++;
		/* FALL THROUGH */
	case 1:
		//メインデータ部分セーブ
		if (PMSVLD_DivSave_Main(ndsw->lock_id, &result) == FALSE) {
			break;
		}
#ifndef	DISABLE_FLASH_CHECK		//バックアップフラッシュなしでも動作
		if (!result) {
			OS_TPrintf("DIV SAVE ERROR!!!!\n");
			return SAVE_RESULT_NG;
		}
#endif
		ndsw->div_seq ++;
		/* FALL THROUGH */

	case 2:
		ndsw->lock_id = _saveDivStartFooter2(sv, ndsw->block_current, !sv->current_side[ndsw->block_current]);
		ndsw->div_seq ++;
		/* FALL THROUGH */

	case 3:
		//フッタ部分セーブ
		if (PMSVLD_DivSave_Main(ndsw->lock_id, &result) == FALSE) {
			break;
		}
#ifndef	DISABLE_FLASH_CHECK		//バックアップフラッシュなしでも動作
		if (!result) {
			OS_TPrintf("DIV SAVE ERROR!!!!\n");
			return SAVE_RESULT_NG;
		}
#endif
		ndsw->div_seq ++;
		if (ndsw->block_current + 1 == ndsw->block_end) {
			//最後のブロックのセーブの場合、それを外部に知らせるために
			//SAVE_RESULT_CONTINUEでなくSAVE_RESULT_LASTを返す
			return SAVE_RESULT_LAST;
		}
		/* FALL THROUGH */

	case 4:
		ndsw->lock_id = _saveDivStartFooter(sv, ndsw->block_current, !sv->current_side[ndsw->block_current]);
		ndsw->div_seq ++;
		/* FALL THROUGH */

	case 5:
		//フッタ部分セーブ
		if (PMSVLD_DivSave_Main(ndsw->lock_id, &result) == FALSE) {
			break;
		}
#ifndef	DISABLE_FLASH_CHECK		//バックアップフラッシュなしでも動作
		if (!result) {
			OS_TPrintf("DIV SAVE ERROR!!!!\n");
			return SAVE_RESULT_NG;
		}
#endif
		ndsw->block_current ++;
		if (ndsw->block_current == ndsw->block_end) {
			OS_TPrintf("DIV SAVE OK!\n");
			return SAVE_RESULT_OK;
		}
		ndsw->div_seq = 0;
		break;
	}
	return SAVE_RESULT_CONTINUE;
}

//---------------------------------------------------------------------------
/**
 * @brief	非同期セーブ処理：終了処理
 * @param	sv			セーブデータ構造へのポインタ
 * @param	ndsw		非同期セーブ制御ワークへのポインタ
 * @param	result		セーブ結果
 */
//---------------------------------------------------------------------------
static void NEWSVLD_DivSaveEnd(SAVEDATA * sv, NEWDIVSV_WORK * ndsw, SAVE_RESULT result)
{
	int i;
	if (result == SAVE_RESULT_NG) {
		//セーブ失敗の場合
		if (ndsw->total_save_mode) {
			sv->global_counter = ndsw->g_backup;
		}
		for (i = 0; i < SVBLK_ID_MAX; i++) {
			sv->current_counters[i] = ndsw->b_backup[i];
		}
	} else {
		//今回セーブしたブロックの参照ミラーを逆転しておく
		for (i = ndsw->block_start; i < ndsw->block_end; i++) {
			sv->current_side[i] = !sv->current_side[i];
		}
		sv->data_exists = TRUE;			//データは存在する
		sv->new_data_flag = FALSE;		//新規データではない
		sv->total_save_flag = FALSE;	//全体セーブは必要ない
	}
	sys_SleepOK(SLEEPTYPE_SAVELOAD);
}

//---------------------------------------------------------------------------
/**
 * @brief	非同期セーブ処理：キャンセル処理
 * @param	sv			セーブデータ構造へのポインタ
 * @param	ndsw		非同期セーブ制御ワークへのポインタ
 */
//---------------------------------------------------------------------------
static void NEWSVLD_DivSaveCancel(SAVEDATA * sv, NEWDIVSV_WORK * ndsw)
{
	int i;
	if (ndsw->total_save_mode) {
		sv->global_counter = ndsw->g_backup;
	}
	for (i = 0; i < SVBLK_ID_MAX; i++) {
		sv->current_counters[i] = ndsw->b_backup[i];
	}
    if(!CARD_TryWaitBackupAsync()){
        CARD_CancelBackupAsync();		//非同期処理キャンセルのリクエスト

        CARD_UnlockBackup(ndsw->lock_id);
        OS_ReleaseLockID(ndsw->lock_id);
    }
	sys_SleepOK(SLEEPTYPE_SAVELOAD);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
BOOL NewSVLD_Save(SAVEDATA * sv)
{
	SAVE_RESULT result;
	NEWDIVSV_WORK ndsw;

	NEWSVLD_DivSaveInit(sv, &ndsw, SVBLK_ID_MAX);

	do {
		result = NEWSVLD_DivSaveMain(sv, &ndsw);
	}while (result == SAVE_RESULT_CONTINUE || result == SAVE_RESULT_LAST);
	NEWSVLD_DivSaveEnd(sv, &ndsw, result);
	return result;
}

//---------------------------------------------------------------------------
/**
 * @brief	指定ブロックのフッタ部分を消去する
 * @param	sv			セーブデータ構造へのポインタ
 * @param	block_id	消去するブロック指定ID
 * @param	mirror_side	消去するミラーの指定（0 or 1)
 */
//---------------------------------------------------------------------------
static BOOL EraseFlashFooter(const SAVEDATA * sv, int block_id, int mirror_side)
{
	u32 base_ofs;
	SAVE_FOOTER dmy_footer;
	const SVBLK_INFO * blkinfo = &sv->blkinfo[block_id];

	MI_CpuFill8(&dmy_footer, 0xff, sizeof(SAVE_FOOTER));
	base_ofs = _getFlashOffset(mirror_side, blkinfo) + blkinfo->size - LAST_DATA_SIZE;

	return PMSVLD_Save(base_ofs, &dmy_footer, LAST_DATA_SIZE);
}


//============================================================================================
//
//
//
//============================================================================================
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static int GetWorkSize(int id)
{
	int size;
	const SAVEDATA_TABLE * table = SaveDataTable;
	GF_ASSERT(id < SaveDataTableMax);
	size = table[id].get_size();
	size += 4 - (size % 4);
	return size;
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブ項目に関する辞書を作成する
 * @param	pageinfo	セーブ項目保持ワーク
 */
//---------------------------------------------------------------------------
static void SVDT_MakeIndex(SVPAGE_INFO * pageinfo)
{
	const SAVEDATA_TABLE * table = SaveDataTable;
	int i;
	int savedata_total_size = 0;


	GF_ASSERT(SaveDataTableMax == GMDATA_ID_MAX);

	for (i = 0; i < SaveDataTableMax; i++) {
		GF_ASSERT(table[i].gmdataID == i);
		pageinfo[i].gmdataID = table[i].gmdataID;
		pageinfo[i].size = GetWorkSize(i);
		pageinfo[i].address = savedata_total_size;
		pageinfo[i].crc = 0;
		pageinfo[i].blockID = table[i].blockID;
		savedata_total_size += pageinfo[i].size;
		if (i == SaveDataTableMax - 1 || table[i].blockID != table[i+1].blockID) {
			//一番最後、あるいはブロックが切り替わるところでは
			//フッタ用領域の分アドレスを勧めておく
			savedata_total_size += sizeof(SAVE_FOOTER);
		}
#ifdef	DEBUG_ONLY_FOR_tamada
		if (i % 4 == 0) {
			OS_TPrintf("SVDT:");
		}
		OS_TPrintf("%02d:%02d:%05x(%05x) ", pageinfo[i].gmdataID, pageinfo[i].blockID,
				pageinfo[i].address, pageinfo[i].size);
		if (i % 4 == 3) {
			OS_PutString("\n");
		}
#endif
	}
	if (i % 4 != 0) {
		OS_PutString("\n");
	}
	GF_ASSERT(savedata_total_size <= SECTOR_SIZE * SECTOR_MAX);
}


//---------------------------------------------------------------------------
/**
 * @brief	ブロックに関する辞書を作成する
 * @param	blkinfo		ブロック項目保持ワーク
 * @param	pageinfo	セーブ項目保持ワーク
 */
//---------------------------------------------------------------------------
static void SVDT_MakeBlockIndex(SVBLK_INFO * blkinfo, const SVPAGE_INFO * pageinfo)
{
	int blk_count = 0;
	int total_sec, address;
	int i, page;

	total_sec = 0;
	address = 0;
	page = 0;
	for (i = 0; i < SVBLK_ID_MAX; i ++) {
		blkinfo[i].id = i;
		//データサイズを計算
		blkinfo[i].size = 0;
		for (; pageinfo[page].blockID == i && page < SaveDataTableMax; page++) {
			blkinfo[i].size += pageinfo[page].size;
		}
		blkinfo[i].size += sizeof(SAVE_FOOTER);
		//セクタ開始ナンバーを代入
		blkinfo[i].start_sec = total_sec;
		//セーブワークでの開始アドレスを代入
		blkinfo[i].start_ofs = address;
		//使用セクタ数（切り上げ）を代入
		blkinfo[i].use_sec = (blkinfo[i].size + SEC_DATA_SIZE - 1) / SEC_DATA_SIZE;

		total_sec += blkinfo[i].use_sec;
		address += blkinfo[i].size;
#ifdef	DEBUG_ONLY_FOR_tamada
		OS_TPrintf("SVBLK:%d:%08x(%02x) size:%05x(%02x)\n",i,
				blkinfo[i].start_ofs, blkinfo[i].start_sec,
				blkinfo[i].size, blkinfo[i].use_sec);
#endif
	}

	GF_ASSERT(total_sec == blkinfo[SVBLK_ID_MAX-1].start_sec + blkinfo[SVBLK_ID_MAX-1].use_sec);
	GF_ASSERT(total_sec <= SECTOR_MAX);
}


//---------------------------------------------------------------------------
/**
 * @brief	セーブデータのクリア
 * @param	svwk	セーブワークへのポインタ
 * @param	pageinfo	セーブ項目保持ワーク
 */
//---------------------------------------------------------------------------
static void SVDT_Init(SAVEWORK * svwk, const SVPAGE_INFO * pageinfo)
{
	const SAVEDATA_TABLE * table = SaveDataTable;
	int i;
	int size;
	void * page;
	u32 adrs;


	MI_CpuClearFast(svwk->data, sizeof(svwk->data));

	for (i = 0; i <SaveDataTableMax; i++) {
		adrs = pageinfo[i].address;
		page = &svwk->data[adrs];
		size = pageinfo[i].size;
		MI_CpuClearFast(page, size);
		table[i].init_work(page);
	}

}

//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
typedef struct {
	u32 magic_number;			///<セーブデータ判別用ID
	u32 counter;				///<セーブ回数カウンタ
	u32 size;					///<使用サイズ
	u16 id;						///<特殊セーブデータID
	u16 crc;					///<整合税チェックのためのCRC値
}CHECK_TAIL_DATA;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static void MakeExtraCheckData(const SAVEDATA * sv, void * buf, EXDATA_ID id, u32 size)
{
	CHECK_TAIL_DATA * chk;
	chk = (CHECK_TAIL_DATA *)((u8*)buf+ size);
	chk->magic_number = MAGIC_NUMBER;
	chk->counter = sv->dendou_counter + 1;
	chk->size = size;
	chk->id = id;
	chk->crc = MATH_CalcCRC16CCITT(&sv->crc_table, buf, size + sizeof(CHECK_TAIL_DATA) - 2);
}

//---------------------------------------------------------------------------
/**
 * @brief
 * @param	sv			セーブデータ構造へのポインタ
 * @param	buf
 * @param	id			特殊セーブデータ指定ID
 */
//---------------------------------------------------------------------------
static BOOL IsCorrectExtraCheckData(const SAVEDATA * sv, void * buf, EXDATA_ID id, u32 size)
{
	const CHECK_TAIL_DATA * chk;
	chk = (const CHECK_TAIL_DATA *)((u8*)buf + size);
	if (chk->magic_number != MAGIC_NUMBER) {
		return FALSE;
	}
	if (chk->size != size) {
		return FALSE;
	}
	if (chk->id != id) {
		return FALSE;
	}
	if (chk->crc != MATH_CalcCRC16CCITT(&sv->crc_table, buf, size + sizeof(CHECK_TAIL_DATA) - 2)) {
		return FALSE;
	}
	return TRUE;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static u32 GetCounterFromExtraData(void * buf, u32 size)
{
	const CHECK_TAIL_DATA * chk = (const CHECK_TAIL_DATA *)((u8*)buf + size);
	return chk->counter;
}

//---------------------------------------------------------------------------
/**
 * @brief	特殊セーブデータのセーブ
 * @param	sv			セーブデータ構造へのポインタ
 * @param	id			特殊セーブデータ指定ID
 * @param	data		取得したセーブデータを載せたワークへのポインタ
 * @retval	SAVE_RESULT_OK
 * @retval	SAVE_RESULT_NG
 *
 * ここでセーブするデータは必ずSaveData_Extra_LoadAlloc経由で取得したデータであること。
 * 本来のデータに加えて整合性チェック用のエリアが追加されているため。
 */
//---------------------------------------------------------------------------
SAVE_RESULT SaveData_Extra_Save(const SAVEDATA * sv, EXDATA_ID id, void * data)
{
	const EXSAVEDATA_TABLE * extbl;
	u32 data_size;
	BOOL result;

	sys_SleepNG(SLEEPTYPE_SAVELOAD);
	GF_ASSERT(id < ExtraSaveDataTableMax);
	extbl = &ExtraSaveDataTable[id];
	GF_ASSERT(extbl->id == id);
	data_size = extbl->get_size() + sizeof(CHECK_TAIL_DATA);


	if (sv->dendou_sector_switch == 1) {
		MakeExtraCheckData(sv, data, id, extbl->get_size());
		result = PMSVLD_Save((FIRST_MIRROR_START + extbl->sector) * SECTOR_SIZE, data, data_size);
		GF_ASSERT(IsCorrectExtraCheckData(sv, data, id, extbl->get_size()) == TRUE);
		MakeExtraCheckData(sv, data, id, extbl->get_size());
		result |= PMSVLD_Save((SECOND_MIRROR_START + extbl->sector) * SECTOR_SIZE, data, data_size);
		GF_ASSERT(IsCorrectExtraCheckData(sv, data, id, extbl->get_size()) == TRUE);
	} else {
		MakeExtraCheckData(sv, data, id, extbl->get_size());
		result = PMSVLD_Save((SECOND_MIRROR_START + extbl->sector) * SECTOR_SIZE, data, data_size);
		GF_ASSERT(IsCorrectExtraCheckData(sv, data, id, extbl->get_size()) == TRUE);
		MakeExtraCheckData(sv, data, id, extbl->get_size());
		result |= PMSVLD_Save((FIRST_MIRROR_START + extbl->sector) * SECTOR_SIZE, data, data_size);
		GF_ASSERT(IsCorrectExtraCheckData(sv, data, id, extbl->get_size()) == TRUE);
	}
	if (result == TRUE) {
		sys_SleepOK(SLEEPTYPE_SAVELOAD);
		return SAVE_RESULT_OK;
	} else {
		sys_SleepOK(SLEEPTYPE_SAVELOAD);
		return SAVE_RESULT_NG;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief
 * @param	sv			セーブデータ構造へのポインタ
 * @param	heap_id		ワークを取得するヒープのID
 * @param	id			特殊セーブデータ指定ID
 * @return	void *	取得したセーブデータを載せたワークへのポインタ
 */
//---------------------------------------------------------------------------
void * SaveData_Extra_LoadAlloc(SAVEDATA *sv, int heap_id, EXDATA_ID id, LOAD_RESULT * result)
{
	const EXSAVEDATA_TABLE * extbl;
	void * buf;
	u32 data_size;
	BOOL res1, res2;
	u32 counter1, counter2;

	GF_ASSERT(id < ExtraSaveDataTableMax);
	extbl = &ExtraSaveDataTable[id];
	GF_ASSERT(extbl->id == id);
	data_size = extbl->get_size() + sizeof(CHECK_TAIL_DATA);
	buf = sys_AllocMemory(heap_id, data_size);

	PMSVLD_Load((FIRST_MIRROR_START + extbl->sector) * SECTOR_SIZE, buf, data_size);
	res1 = IsCorrectExtraCheckData(sv, buf, id, extbl->get_size());
	counter1 = GetCounterFromExtraData(buf, extbl->get_size());

	PMSVLD_Load((SECOND_MIRROR_START + extbl->sector) * SECTOR_SIZE, buf, data_size);
	res2 = IsCorrectExtraCheckData(sv, buf, id ,extbl->get_size());
	counter2 = GetCounterFromExtraData(buf, extbl->get_size());


	*result = LOAD_RESULT_OK;

	//１が正常の場合
	if (res1 == TRUE && res2 == FALSE) {
		sv->dendou_sector_switch = 0;
		sv->dendou_counter = counter1;
		PMSVLD_Load((FIRST_MIRROR_START + extbl->sector) * SECTOR_SIZE, buf, data_size);
		return buf;
	}
	//２が正常の場合
	if (res1 == FALSE && res2 == TRUE) {
		sv->dendou_sector_switch = 1;
		sv->dendou_counter = counter2;
		PMSVLD_Load((SECOND_MIRROR_START + extbl->sector) * SECTOR_SIZE, buf, data_size);
		return buf;
	}
	//両方が正常の場合
	if (res1 == TRUE && res2 == TRUE) {
		if (_diffCounter(counter1, counter2) != -1) {
			sv->dendou_sector_switch = 0;
			sv->dendou_counter = counter1;
			PMSVLD_Load((FIRST_MIRROR_START + extbl->sector) * SECTOR_SIZE, buf, data_size);
			return buf;
		} else {
			sv->dendou_sector_switch = 1;
			sv->dendou_counter = counter2;
			PMSVLD_Load((SECOND_MIRROR_START + extbl->sector) * SECTOR_SIZE, buf, data_size);
			return buf;
		}
	}
	//両方とも異常の場合
	*result = LOAD_RESULT_NG;
	sv->dendou_sector_switch = 0;
	sv->dendou_counter = 0;
	return buf;
}




//============================================================================================
//
//
//			ライブラリI/O部分
//
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	バックアップフラッシュの動作確認
 * @retval	TRUE	バックアップフラッシュが正常に動作する
 * @retval	FALSE	正常動作しない（存在しない、違う種類のバックアップデバイス等）
 */
//---------------------------------------------------------------------------
BOOL PMSVLD_Init(void)
{
	s32 lock_id;
	BOOL result;
	u32 read_buf;

	lock_id = OS_GetLockID();
	GF_ASSERT(lock_id != OS_LOCK_ID_ERROR);
	CARD_LockBackup(lock_id);

	if (CARD_IdentifyBackup(CARD_BACKUP_TYPE_FLASH_4MBITS)) {
		result = CARD_BACKUP_TYPE_FLASH_4MBITS;
	} else
	if (CARD_IdentifyBackup(CARD_BACKUP_TYPE_FLASH_2MBITS)) {
		result = CARD_BACKUP_TYPE_FLASH_2MBITS;
	} else {
		result = CARD_BACKUP_TYPE_NOT_USE;
	}

	CARD_UnlockBackup(lock_id);
	OS_ReleaseLockID(lock_id);

	if (result == CARD_BACKUP_TYPE_FLASH_4MBITS) {
		OS_TPrintf("Identified 4M FLASH\t");
	}else if (result == CARD_BACKUP_TYPE_FLASH_2MBITS) {
		OS_TPrintf("Identified 2M FLASH\t");
	}else{
		OS_TPrintf("No FLASH Identified\t");
	}

	OS_TPrintf("CardResult %d\n",CARD_GetResultCode());
	//4Mbit FLASH SectorSize == 0x10000 PageSize == 0x100 TotalSize == 0x80000
	//OS_TPrintf("SECTOR SIZE %x\n",CARD_GetBackupSectorSize());
	//OS_TPrintf("PAGE SIZE %x\n",CARD_GetBackupPageSize());
	//OS_TPrintf("TOTAL SIZE %x\n", CARD_GetBackupTotalSize());

	return (result != CARD_BACKUP_TYPE_NOT_USE);
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブ
 * @param	src		フラッシュのアドレス（０～）※セクタ指定ではない
 * @param	dst		書き込むデータのアドレス
 * @param	len		書き込むデータの長さ
 * @return	BOOL	TRUEで成功、FALSEで失敗
 */
//---------------------------------------------------------------------------
BOOL PMSVLD_Save(u32 src, void * dst, u32 len)
{
	s32 lock_id;
	BOOL result;
	lock_id = PMSVLD_DivSave_Init(src, dst, len);
	while (PMSVLD_DivSave_Main(lock_id, &result) == FALSE) {
		/* Do Nothing */
	}
	return result;
#if 0
	s32 lock_id;
	BOOL result;

	lock_id = OS_GetLockID();
	GF_ASSERT(lock_id != OS_LOCK_ID_ERROR);
	CARD_LockBackup(lock_id);

//	result = CARD_WriteAndVerifyFlash(src, dst, len);
	CARD_WriteAndVerifyFlashAsync(src, dst, len, NULL, NULL);
	result = CARD_WaitBackupAsync();

	CARD_UnlockBackup(lock_id);
	OS_ReleaseLockID(lock_id);

	return result;
#endif
}
//---------------------------------------------------------------------------
/**
 * @brief	ロード
 * @param	src		フラッシュのアドレス（０～）※セクタ指定ではない
 * @param	dst		読み込み先アドレス
 * @param	len		読み込むデータの長さ
 * @return	BOOL	TRUEで成功、FALSEで失敗
 */
//---------------------------------------------------------------------------
BOOL PMSVLD_Load(u32 src, void * dst, u32 len)
{
	s32 lock_id;
	BOOL result;

	lock_id = OS_GetLockID();
	GF_ASSERT(lock_id != OS_LOCK_ID_ERROR);
	CARD_LockBackup(lock_id);

	//result = CARD_ReadFlash(src, dst, len);
	CARD_ReadFlashAsync(src, dst, len, NULL, NULL);
	result = CARD_WaitBackupAsync();

	CARD_UnlockBackup(lock_id);
	OS_ReleaseLockID(lock_id);

#ifndef	DISABLE_FLASH_CHECK		//バックアップフラッシュなしでも動作
	if (!result) {
		sys_FreeMemoryEz(SvPointer);
		BackupErrorWarningCall(HEAPID_BASE_SAVE);
	}
#endif

	return result;
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static BOOL SaveEndFlag;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static void SaveCallBack(void * src)
{
	SaveEndFlag = TRUE;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static s32 PMSVLD_DivSave_Init(u32 src, void * dst, u32 len)
{
	s32 lock_id;
	u32 buf;
	BOOL result;

	lock_id = OS_GetLockID();
	GF_ASSERT(lock_id != OS_LOCK_ID_ERROR);
	CARD_LockBackup(lock_id);

#ifndef	DISABLE_FLASH_CHECK
	result = CARD_ReadFlash(0, &buf, sizeof(buf));
	if (!result) {
		/* セーブデータが読めない＝接触不良 */
		PMSVLD_SaveError(lock_id, SAVEERROR_MSG_DISABLE_READ);
	}
#endif
	SaveEndFlag = FALSE;
	CARD_WriteAndVerifyFlashAsync(src, dst, len, SaveCallBack, NULL);
	return lock_id;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static BOOL PMSVLD_DivSave_Main(s32 lock_id, BOOL * result)
{
	if (SaveEndFlag == TRUE) {
		CARD_UnlockBackup(lock_id);
		OS_ReleaseLockID(lock_id);

#ifdef	DISABLE_FLASH_CHECK
		*result = TRUE;
#else
		switch (CARD_GetResultCode()) {
		case CARD_RESULT_SUCCESS:
			*result = TRUE;
			break;
		default:
			GF_ASSERT(0);
		case CARD_RESULT_TIMEOUT:
			*result = FALSE;
			/* セーブデータが書き込めない＝フラッシュ寿命か故障 */
			PMSVLD_SaveError(lock_id, SAVEERROR_MSG_DISABLE_WRITE);
		case CARD_RESULT_NO_RESPONSE:
			*result = FALSE;
			/* CARD_RESULT_NO_RESPONSE＝＝接触不良 */
			PMSVLD_SaveError(lock_id, SAVEERROR_MSG_DISABLE_READ);
			break;
		}
#endif
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブ失敗によるカード異常
 * @param	lock_id		バスロックでシステムが返したID
 */
//---------------------------------------------------------------------------
static void PMSVLD_SaveError(s32 lock_id, int error_msg_id)
{
	//ロックしているバスを開放する（ロムが読めなくなるので）
	CARD_UnlockBackup(lock_id);
	OS_ReleaseLockID(lock_id);

	//セーブ失敗画面でセーブヒープを使用できるように開放する
	sys_FreeMemoryEz(SvPointer);

	//セーブ失敗画面呼び出し
	SaveErrorWarningCall(HEAPID_BASE_SAVE, error_msg_id);
}


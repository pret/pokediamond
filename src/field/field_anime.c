//=============================================================================
/**
 * @file	field_anime.c
 * @bfief	フィールドアニメ処理（主に転送アニメ)
 * @author	mori GAME FREAK inc.
 *
 *
 */
//=============================================================================

#include "common.h"
#include "calctool.h"
#include "str_tool.h"
#include "system/lib_pack.h"
#include "field_anime.h"



//==============================================================================
// 定義
//==============================================================================
#define FIELD_ANIME_MAX			( 11 )	// 地形用転送アニメの同時動作上限

#define FIELD_VRAM_ANIME_MAX	( 11 )	//フィールドVRAMアニメ数

typedef struct{						// アニメ用データ（ROMから読み込みます)
	char name[32];					// テクスチャファイル名
	u16	 AnmTbl[10][2];				// アニメ用テーブル[0]:パターン番号  [1]:wait
}FIELD_ANIME;

struct _FIELD_ANIME_WORK{
	u8  			*texadr;		// 既に転送されているテクスチャアドレス
	int 			texsize;		// 転送するテクスチャサイズ
	NNSG3dResTex 	*animetex;		// 転送するテクスチャリソースのポインタ
	void			*texfile;		// テクスチャファイルの実体
	FIELD_ANIME		*animetbl;		// アニメーション定義テーブルのポインタ
	u16				point,wait;		// 現在の表示ポインタ,ウェイト
}FIELD_ANIME_WORK;

static const char *FieldVRAMAnime[FIELD_VRAM_ANIME_MAX] = {
	"sea",
	"rhana",
	"asasea",
	"hamabe",
	"asahamabe",
	"t3_fl_b.1",
	"t3_fl_p.1",
	"t3_fl_r.1",
	"t3_fl_y.1",
	"dun_sea",
	"lakep.1",	
};

//==============================================================================
// ワーク
//==============================================================================

//FIELD_ANIME_WORK	FieldAnimeWork[FIELD_ANIME_MAX];


//==============================================================================
// 関数
//==============================================================================

//==============================================================================
/**
 * 初期化
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
FIELD_ANIME_PTR InitFieldAnime(void)
{
	int i;
	FIELD_ANIME_PTR faw=NULL;
	
	faw = sys_AllocMemory(HEAPID_FIELD,sizeof(FIELD_ANIME_WORK)*FIELD_ANIME_MAX);
	
	if(faw!=NULL){
		for(i=0;i<FIELD_ANIME_MAX;i++){
			faw[i].point = 0;
			faw[i].wait  = 0;
			faw[i].texadr  = NULL;
			faw[i].animetex  = NULL;
			faw[i].animetbl  = NULL;
			faw[i].texfile = NULL;
		}
	}
	return faw;
}


//114 892
// 34%


//------------------------------------------------------------------
/**
 * フィールド転送アニメ登録
 *
 * @param   tex			既にVRAMに転送済みのテクスチャ管理ポインタ
 * @param   Tindex		上のテクスチャの指定index
 * @param   AnimeNo		転送を行いたいテクスチャアニメ番号（これがファイル名になる)
 *
 * @retval  int 		登録できたら0-10 できなかったら-1
 */
//------------------------------------------------------------------
int FieldAnimeSets(FIELD_ANIME_PTR faw, NNSG3dResTex *tex)
{
	int i,result=0;
	for (i=0;i<FIELD_VRAM_ANIME_MAX;i++){
		if(FieldAnimeSet(faw, tex, FieldVRAMAnime[i], i)>=0){
			result++;
		}
	}
	return result;
}


//------------------------------------------------------------------
/**
 * フィールド転送アニメ登録
 *
 * @param   tex			既にVRAMに転送済みのテクスチャ管理ポインタ
 * @param   Tindex		上のテクスチャの指定index
 * @param   AnimeNo		転送を行いたいテクスチャアニメ番号（これがファイル名になる)
 *
 * @retval  int 		登録できたら0-10 できなかったら-1
 */
//------------------------------------------------------------------
int 	FieldAnimeSet(FIELD_ANIME_PTR faw, NNSG3dResTex *tex, const char *name, int AnimeNo)
{
	int  no,i;
	char filename[40];
	
	if(faw==NULL){								//確保されてないのに呼ばれてるかもしれないので
		return -1;
	}

	for(no=0;no<FIELD_ANIME_MAX;no++){				//使用していないワークを検索
		if(faw[no].texfile==NULL){
			break;
		}
	}
	if(no==FIELD_ANIME_MAX || tex==NULL){			//登録MAX もしくは地形テクスチャがNULLだったら登録中止
		return -1;
	}


	faw[no].texadr   = GetTexStartVRAMAdrByName(tex,name);	//転送済み地形テクスチャから転送対象となる場所を取得する
	if (faw[no].texadr == NULL){
		return -1;			//テクスチャがなかったら登録中止
	}

	faw[no].texsize  = GetTexByteSizeByName(tex,name);
	
	sprintf(filename,"data/fld_anime%d.bin",AnimeNo);				
	faw[no].animetbl = sys_LoadFile(HEAPID_FIELD,filename);
	
	OS_Printf("field_anime animetbl=%08x\n",faw[no].animetbl);
//	OS_Printf("texname=%s\n",FieldAnimeWork[no].animetbl->name);
//	for(i=0;i<10;i++){
//		if(FieldAnimeWork[no].animetbl->AnmTbl[i][0]!=0xffff){
//			OS_Printf("anime[i] = %d, wait = %d\n",FieldAnimeWork[no].animetbl->AnmTbl[i][0],FieldAnimeWork[no].animetbl->AnmTbl[i][1]);
//		}else{
//			break;
//		}
//	}
	
	//転送アニメテクスチャ読み込み
	faw[no].texfile   = sys_LoadGraphFile(faw[no].animetbl->name,HEAPID_FIELD);
	faw[no].animetex  = NNS_G3dGetTex((NNSG3dResFileHeader*) faw[no].texfile );

	return no;
}



//==============================================================================
/**
 * フィールド用テクスチャ転送アニメ常駐関数
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void FieldAnimeMain(FIELD_ANIME_PTR faw)
{
	int i;
	
	if(faw==NULL){								//確保されてないのに呼ばれてるかもしれないので
		return;
	}
	
	for(i=0;i<FIELD_ANIME_MAX;i++){				//使用していないワークを検索
		if(faw[i].texfile==NULL){
			continue;							//何もセットされていない場合はスルー
		}

		//>>add
		if (faw[i].animetbl == NULL){
			continue;
		}
		//<<
		
		if(faw[i].animetbl->AnmTbl[faw[i].point][1] <= faw[i].wait){	//アニメ更新タイミングの時
			faw[i].wait = 0;						//ウェイトクリア
			faw[i].point++;						//ポイント＋＋
			if(faw[i].animetbl->AnmTbl[faw[i].point][0]==0xffff){					//アニメ定義が端まできている場合はループ
				faw[i].point = 0;
			}
			AddVramTransferManager(
					NNS_GFD_DST_3D_TEX_VRAM,		//転送セット
					(u32)faw[i].texadr,
					GetTexStartAdr(faw[i].animetex,faw[i].animetbl->AnmTbl[faw[i].point][0]),
					faw[i].texsize);	
//			OS_Printf("i=%d, point=%d pat=%04x\n",i,faw[i].point,faw[i].animetbl->AnmTbl[faw[i].point][0]);
		}else{
			faw[i].wait++;			//ウェイト更新
		}
	}
}



//==============================================================================
/**
 * 個別にテクスチャ転送アニメを解放
 *
 * @param   no		faw[]の添字
 *
 * @retval  none	
 */
//==============================================================================
void FieldAnimeRelease(FIELD_ANIME_PTR faw, int no )
{
	// テクスチャファイルの解放はキャッシュに積まれているので行わない
	

	if(faw==NULL){								//確保されてないのに呼ばれてるかもしれないので
		return;
	}

	// アニメーション定義テーブルの解放
	if(faw[no].animetbl!=NULL){
//		NNS_FndCheckExpHeap((void*)faw[no].animetbl,NNS_FND_HEAP_ERROR_PRINT);
		sys_FreeMemoryEz(faw[no].animetbl);
		faw[no].animetbl = NULL;
	}
	faw[no].point = 0;	//アニメ用ワークの初期化
	faw[no].wait  = 0;
}

//==============================================================================
/**
 * テクスチャアニメ転送システム終了
 *
 * @param   none
 *
 * @retval  none
 */
//==============================================================================
void FieldAnimeAllRelease(FIELD_ANIME_PTR faw)
{
	int i;
	
	if(faw==NULL){								//確保されてないのに呼ばれてるかもしれないので
		return;
	}	
	
	for(i=0;i<FIELD_ANIME_MAX;i++){
		FieldAnimeRelease( faw, i );
	}
}

//==============================================================================
/**
 * フィールド転送アニメシステム解放
 *
 * @param   faw		
 *
 * @retval  none		
 */
//==============================================================================
void ReleaseFieldAnime(FIELD_ANIME_PTR faw)
{
	if(faw!=NULL){
		sys_FreeMemoryEz(faw);
		faw = NULL;
	}
}

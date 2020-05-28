//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		field_light.c
 *@brief	ライトコントローラ
 *@author	tomoya takahashi
 *@data		2005.04.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "common.h"
#define __LIGHT_CONT_H_GLOBAL
#include "field_light.h"
#include "field_glb_state.h"

#include "system/pm_rtc.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------

//-------------------------------------
//	
//	１日表現セット	
//	
//=====================================
typedef struct _LIGHT_CONT_SET{
	u32		DataNum;				// データ数
	LIGHT_CONT_DATA* pDataTbl;		// データテーブル
	int Light_Num;					// 今のLIGHTナンバー
	GLST_DATA_PTR	Glb;			// グローバルステートの状態保存領域
	BOOL reflect;					// 反映フラグ	TRUE反映
} LIGHT_CONT_SET;


//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
static void DataSetLightContPack(LIGHT_CONT_SET* cont);			// 今のライトデータを反映する

static u32 loadLightData( const char* str, LIGHT_CONT_DATA** ppData );			// ライトデータ読み込み
static void dellLightData(LIGHT_CONT_DATA** ppData);						// ライトデータ破棄
static char* GetLightData( char* buff, GXRgb* Color, VecFx16* Vector );		// lightデータを取得
static char* GetRgbData( char* buff, GXRgb* Color );						// 色データを取得
//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------
//アーカイブが完了したら不要
static const char *const Path[ LIGHT_TYPE_MAX ] =
{
	{"data/area00light.txt"},
	{"data/area01light.txt"},
	{"data/area02light.txt"},
};

//----------------------------------------------------------------------------
/**
 *
 *@brief	ライトシステムを初期化
 *		
 *@param	glb			グローバルステートの状態保存領域
 *@param	path		ライトテーブルパス
 *
 *@return	LIGHT_CONT_PTR	作成したライトシステムデータ
 *
 */
//-----------------------------------------------------------------------------
LIGHT_CONT_PTR InitLightCont(GLST_DATA_PTR glb, const u8 light_index/*const char* path*/)
{
	int		i;	// ループ用
	LIGHT_CONT_PTR data;
	int light_movecount;
	
	GF_ASSERT(light_index<LIGHT_TYPE_MAX && "ライトインデックスオーバー");

	data = sys_AllocMemory(HEAPID_FIELD, sizeof(LIGHT_CONT_SET));
	
	data->Glb = glb;		// グローバルステートの状態保存領域を保存
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print light = %s\n",Path[light_index]);
#endif	
	// 読み込み
	data->DataNum = loadLightData(Path[light_index], &data->pDataTbl);
	data->Light_Num = 0;

	// RTCから現在時間の取得をおこないます。
	light_movecount = GF_RTC_GetTimeBySecond() / 2;

	// 今の時間はどのライトかチェック
	// これは時間からテーブルを動かす事を考えて入れました。
	for(i = 0;i < data->DataNum; i++){
		if(data->pDataTbl[i].lightEnd > light_movecount){
			data->Light_Num = i;				// ライト数設定
			break;
		}
	}

	// 反映
	data->reflect = TRUE;

	DataSetLightContPack(data);

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ライトコントロールシステムを破棄
 *
 *@param	pLight		ライトシステムデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DellLightCont( LIGHT_CONT_PTR* pLight )
{
	GF_ASSERT(pLight);
	
	dellLightData(&(*pLight)->pDataTbl);	// データ破棄
	
	sys_FreeMemory(HEAPID_FIELD, *pLight);
	*pLight = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ライトデータを動かす
 *
 *@param	Light		ライトコントロールデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void MainLightCont(LIGHT_CONT_PTR Light)
{
	u32 num;
	int i;		// ループ用
	int light_min;	// 今のテーブルのライトカウンタ最小
	int light_max;	// 今のテーブルのライトカウンタ最大
	int light_movecount;
	
	GF_ASSERT(Light);
	
	// RTCから現在時間の取得をおこないます。
	light_movecount = GF_RTC_GetTimeBySecond() / 2;

	// ライトテーブルが１つなら変更はしない
	if( Light->DataNum > 1 ){

		// 今のライトテーブルの最小カウント値　最大カウント値を設定
		if( (Light->Light_Num - 1) >= 0 ){
			light_min = Light->pDataTbl[ Light->Light_Num - 1 ].lightEnd;
		}else{
			light_min = 0;
			
		}
		light_max = Light->pDataTbl[ Light->Light_Num ].lightEnd;

	
		// カウンタのタイミングになったら
		// 反映させる構造体を変更する
		if( ( light_movecount >= light_max ) ||		// カウント値が範囲外のときはLight_Numをカウントアップして
			( light_movecount < light_min ) ){		// カウント値が範囲内のテーブルを探す

			Light->Light_Num++;	// 設定するデータのナンバーを取得
			if( Light->Light_Num >= Light->DataNum ){	// データ以上になったらカウンタ初期化
				Light->Light_Num = 0;
			}

			if( Light->reflect ){
				DataSetLightContPack(Light);
			}
		}
	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	ライトデータ反映フラグ設定
 *
 *	@param	Light		ライトワーク
 *	@param	reflect		反映フラグ
 *	
 *	@return	none
 *	reflect 
 *		TRUE	反映させる
 *		FALSE	反映させない
 */
//-----------------------------------------------------------------------------
void SetLightContReflect( LIGHT_CONT_PTR Light, BOOL reflect )
{
	Light->reflect = reflect;

	// 反映にした場合その時点で、1度データを設定する
	if( Light->reflect ){
		DataSetLightContPack(Light);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ライトデータ反映フラグ状態取得
 *
 *	@param	Light	ライトコントローラ
 *
 *	@retval	TRUE	反映中
 *	@retval	FALSE	反映していない
 */
//-----------------------------------------------------------------------------
BOOL GetLightContReflect( CONST_LIGHT_CONT_PTR Light )
{
	return Light->reflect;
}

//----------------------------------------------------------------------------
/**
 *	@brief	1ライトデータ設定
 *
 *	@param	move	ワーク
 *	@param	pGlst	グローバルステートデータ
 *	
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void DataSetLightCont( const LIGHT_CONT_DATA* move, GLST_DATA_PTR pGlst )
{
	int i;		// ループ用
	
	// ライト設定
	for(i=0;i<4;i++){
		int check = 	(1<<i);
		if((move->lightFlag & check) != 0){
			GLST_LightVector(pGlst, i, move->lightVec[i].x, move->lightVec[i].y, move->lightVec[i].z);
			GLST_LightColor(pGlst, i,move->lightColor[i]);
		}else{
			GLST_LightVector(pGlst, i, 0, 0, 0);
			GLST_LightColor(pGlst, i,GX_RGB(0,0,0));		// ライト消灯
		}
	}
	// ディフューズ、アンビエント、スペキュラー、放射光
	GLST_MaterialDiff(pGlst, move->diffuse,FALSE,FALSE);
	GLST_MaterialAmb(pGlst, move->ambient,TRUE);
	GLST_MaterialSpec(pGlst, move->specular,FALSE,FALSE);
	GLST_MaterialEmi(pGlst, move->emission,TRUE);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	今のライトデータを反映させる
 *
 *@param	cont		ライトコントロールセット	
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void DataSetLightContPack(LIGHT_CONT_SET* cont)
{
	LIGHT_CONT_DATA* move = &cont->pDataTbl[cont->Light_Num];
	
	DataSetLightCont( move, cont->Glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	夜かチェック
 *
 *	@param	cont	ライトコントロールシステム
 *
 *	@retval	TRUE	夜
 *	@retval	FALSE	昼
 *
 *
 */
//-----------------------------------------------------------------------------
//BOOL GetLightNight( LIGHT_CONT_SET* cont )
BOOL GetLightNight( void )
{
	int light_movecount;
	light_movecount = GF_RTC_GetTimeBySecond() / 2;
	
//	if( (cont->Light_Num >= 12) || (cont->Light_Num <= 2) ){
	if( (light_movecount >= 34200) || (light_movecount < 7200) ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	モデルがライトや、マテリアルのデータはグローバルステートを
 *			使用するように変更する
 *
 *@param	Mdl		セットするモデル
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void SetGlbLightMdl(NNSG3dResMdl* Mdl)
{
	// ライト、マテリアルはグローバルステートの値を使用する
	NNS_G3dMdlUseGlbDiff(Mdl);				// ディフューズ
	NNS_G3dMdlUseGlbAmb(Mdl);				// アンビエント
	NNS_G3dMdlUseGlbSpec(Mdl);				// スペキュラー
	NNS_G3dMdlUseGlbEmi(Mdl);				// エミッション
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	モデルがライトや、マテリアルのデータはグローバルステートを
 *			使用しないように変更する
 *
 *@param	Mdl		セットするモデル
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void RemGlbLightMdl(NNSG3dResMdl* Mdl)
{
	// ライト、マテリアルはモデル値を使用する
	NNS_G3dMdlUseMdlDiff(Mdl);				// ディフューズ
	NNS_G3dMdlUseMdlAmb(Mdl);				// アンビエント
	NNS_G3dMdlUseMdlSpec(Mdl);				// スペキュラー
	NNS_G3dMdlUseMdlEmi(Mdl);				// エミッション
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	ライトデータを読み込む
 *
 *@param	str		ファイルパス
 *@param	ppData	格納先
 *
 *@return	ライトデータ数
 *
 *
 */
//-----------------------------------------------------------------------------
static u32 loadLightData( const char* str, LIGHT_CONT_DATA** ppData )
{
	int   i,j;			// ループ用
	int	  data_num;		// データ数
	void* filep;		// ファイルポインタ
	void* tmp;			// 削除用ファイルポインタ保存
	char  buff[256];	// 読み込みよう
	char* buff_work;	// バッファ操作用
	char r_b[256];		// ローカル作業用バッファ
	LIGHT_CONT_DATA* pDataWork;	// 格納作業用

	
	tmp = sys_LoadFile(HEAPID_FIELD,str);		// ファイルオープン
	filep = tmp;				// 作業用変数に代入
	
	data_num = 0;
	do
	{
		filep = StrTok(filep,buff,RETURN_CODE);
		if(!((buff[0] == 'E') &&
		   (buff[1] == 'O') &&
		   (buff[2] == 'F'))){
			
			filep = StrTok(filep,buff,RETURN_CODE);
			filep = StrTok(filep,buff,RETURN_CODE);
			filep = StrTok(filep,buff,RETURN_CODE);
			filep = StrTok(filep,buff,RETURN_CODE);
			filep = StrTok(filep,buff,RETURN_CODE);
			filep = StrTok(filep,buff,RETURN_CODE);
			filep = StrTok(filep,buff,RETURN_CODE);
			filep = StrTok(filep,buff,RETURN_CODE);
			filep = StrTok(filep,buff,RETURN_CODE);
			data_num++;
		}
	}while(!((buff[0] == 'E') &&
		   (buff[1] == 'O') &&
		   (buff[2] == 'F')));

	// データ数分の領域を確保
	*ppData = sys_AllocMemory(HEAPID_FIELD, sizeof(LIGHT_CONT_DATA)*data_num);
	MI_CpuClear8(*ppData, sizeof(LIGHT_CONT_DATA)*data_num);

	// データを格納
	filep = tmp;
	for(i=0;i<data_num;i++){

		// 格納先をセット
		pDataWork = &((*ppData)[i]);

		// タイミング
		filep = StrTok(filep,buff,RETURN_CODE);
		buff_work = buff;
		buff_work = StrTok(buff_work,r_b,',');
		pDataWork->lightEnd = AtoI(r_b);
		
		// light
		for(j=0;j<4;j++){
			// lightデータ取得
			filep = GetLightData(filep, &pDataWork->lightColor[j], &pDataWork->lightVec[j]);
			if(pDataWork->lightColor[j] != 0xffff){		// lightを使用するのかチェック
				pDataWork->lightFlag |= 1 << j;
			}else{
				pDataWork->lightColor[j] = 0;
			}
		}

		// 色
		filep = GetRgbData(filep, &pDataWork->diffuse);	// ディフューズ
		filep = GetRgbData(filep, &pDataWork->ambient);	// アンビエント
		filep = GetRgbData(filep, &pDataWork->specular);	// スペキュラー
		filep = GetRgbData(filep, &pDataWork->emission);	// エミッション	


		// 改行
		filep = StrTok(filep,buff,RETURN_CODE);
	}

	sys_FreeMemory(HEAPID_FIELD,tmp);		// ファイル破棄

	return data_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ライトデータを破棄
 *
 *@param	str		ファイルパス
 *@param	ppData	格納先
 *
 *@return	ライトデータ数
 *
 *
 */
//-----------------------------------------------------------------------------
static void dellLightData(LIGHT_CONT_DATA** ppData)
{
	sys_FreeMemory(HEAPID_FIELD, *ppData);
	*ppData = NULL;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	各ライトデータを読み込む
 *
 *@param	buff		読み込み先
 *@param	Color		ライトの色書き込み先
 *@param	Vector		ライトのベクトル書き込み先
 *
 *@return	次の読込先
 *
 *
 */
//-----------------------------------------------------------------------------
static char* GetLightData( char* buff, GXRgb* Color, VecFx16* Vector )		// lightデータを取得
{
	char work[256];			// 読み込みよう
	char work2[256];		// 切り取り用
	char* data_work;		// データワーク
	u32	flag;				// light有効チェック用
	int	i;					// ループ用
	u16	rgb[3];				// 色格納用
	s32	vec[3];				// 座標格納用
 
	
	// light
	buff = StrTok(buff,work,RETURN_CODE);
	data_work = work;
	data_work = StrTok(data_work,work2,',');
	flag = AtoI(work2);
	if(flag == 1){
		// 色
		for(i=0;i<3;i++){
			data_work = StrTok(data_work,work2,',');
			rgb[i] = AtoI(work2);
		}

		// 色を設定
		*Color = GX_RGB(rgb[0],rgb[1],rgb[2]);
		
		// ベクトル
		for(i=0;i<3;i++){
			data_work = StrTok(data_work,work2,',');
			vec[i] = AtoI(work2);
		}

		// ベクトルを設定
		Vector->x = vec[0];
		Vector->y = vec[1];
		Vector->z = vec[2];

		if(Vector->x > FX16_ONE){
			Vector->x = FX16_ONE;
		}
		if(Vector->x < -FX16_ONE){
			Vector->x = -FX16_ONE;
		}
		if(Vector->y > FX16_ONE){
			Vector->y = FX16_ONE;
		}
		if(Vector->y < -FX16_ONE){
			Vector->y = -FX16_ONE;
		}
		if(Vector->z > FX16_ONE){
			Vector->z = FX16_ONE;
		}
		if(Vector->z < -FX16_ONE){
			Vector->z = -FX16_ONE;
		}
		
	}else{

		// ダミーデータをセット
		*Color = 0xffff;
	}

	return buff;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	各色データを読み込む
 *
 *@param	buff		読み込み先
 *@param	Color		ライトの色書き込み先
 *
 *@return	次の読込先
 *
 *
 */
//-----------------------------------------------------------------------------
static char* GetRgbData( char* buff, GXRgb* Color )
{
	char work[256];			// 読み込みよう
	char work2[256];		// 切り取り用
	char* data_work;		// 作業用
	int i;
	u16	rgb[3];				// 色格納用
	
	buff = StrTok(buff,work,RETURN_CODE);
	data_work = work;
	
	// 色
	for(i=0;i<3;i++){
		data_work = StrTok(data_work,work2,',');
		rgb[i] = AtoI(work2);
	}

	// 色を設定
	*Color = GX_RGB(rgb[0],rgb[1],rgb[2]);

	return buff;
}

//============================================================================================
/**
 * @file	haight_check.c
 * @brief	高さ取得関連
 * @author	Nozomu Saito
 * @date	2005.05.06
 */
//============================================================================================
#include "common.h"
#include "height.h"
#define MAX_GET_POL	(10)

#define GRID_ENTRY_ONE_DATA	(2)	//2バイトデータが2つで4バイト
#define LINE_ONE_DATA	(5)		//2バイトデータが5つで10バイト
#define Z_VAL_OFFSET_L(data_idx)	( data_idx*LINE_ONE_DATA+1 )
#define Z_VAL_OFFSET_H(data_idx)	( data_idx*LINE_ONE_DATA+2 )

#define LINE_Z_VAL(list,idx)	( (list[Z_VAL_OFFSET_H(data_idx)]<<16) | list[Z_VAL_OFFSET_L(data_idx)] )

static BOOL	BinSearch(const u16 *inDataList,const u16 inDataSize,const fx32 inZ_Val,u16 *outIndex);

#ifdef PM_DEBUG
static const BOOL GetVertexEqualHeight(const VecFx32 *inTarget,
										const VecFx32 *inVec1,
										const VecFx32 *inVec2,
										const VecFx32 *inVec3,
										fx32 *outHeight);
static const BOOL GetEdgeEqualHeightXZFlat(	const VecFx32 *inTarget,
											const VecFx32 *inVec1,
											const VecFx32 *inVec2,
											const VecFx32 *inVec3,
											fx32 *outHeight);

u8 HC_DebugCheckHeight(const fx32 inX, const fx32 inZ, MHI_CONST_PTR inMap3DInfo, const BOOL inDetail);
#endif


//static int FirstIdx;
/**
 
*/
//---------------------------------------------------------------------------------------------------------
/**
 *	斜面を登るときの移動補正。
 *	斜面を登るときは、平地を移動するときよりも移動量が減る
 *	@param	inMoveVal		移動量
 *	@param	inNewVec		未来座標
 *	@param	inOldVec		現在座標
 *
 *	@retval	VecFx32			修正後移動量（移動方向）
*/
//---------------------------------------------------------------------------------------------------------
VecFx32 MoveRevise(fx32 inMoveVal,VecFx32 inNewVec,VecFx32 inOldVec)
{
	VecFx32 vec,dstVec;
	VecFx32 dmyVec = {0,0,0};
	
	VEC_Subtract(&inNewVec,&inOldVec,&vec);
	VEC_Normalize(&vec, &vec);
	VEC_MultAdd(inMoveVal,&vec,&dmyVec,&dstVec);
	
	return dstVec;
}

//---------------------------------------------------------------------------------------------------------
/**
 *	ポリゴンインデックスからポリゴン頂点データを取得
 *	@param	inMAp3DInfo		マップ高さ情報		
 *	@param	inIdx			ポリゴンデータインデックス
 *	@param	outVertex		頂点データ格納先ポインタ
 *	
 *	@retval	none
*/
//---------------------------------------------------------------------------------------------------------
static void GetPolygonVertex(MHI_CONST_PTR inMap3DInfo, u16 inIdx, VecFx32 *outVertex)
{
	outVertex[0] = inMap3DInfo->VertexArray[inMap3DInfo->PolygonData[inIdx].vtx_idx0];
	outVertex[1] = inMap3DInfo->VertexArray[inMap3DInfo->PolygonData[inIdx].vtx_idx1];
	outVertex[2] = inMap3DInfo->VertexArray[inMap3DInfo->PolygonData[inIdx].vtx_idx2];
}


//---------------------------------------------------------------------------------------------------------
/**
 *	ポリゴンインデックスからポリゴンの法線を取得
 *	@param	inMAp3DInfo		マップ高さ情報		
 *	@param	inIdx			ポリゴンデータインデックス
 *	@param	outVertex		法線データ格納先ポインタ
 *	
 *	@retval	none
*/
//---------------------------------------------------------------------------------------------------------
static void GetPolygonNrm(MHI_CONST_PTR inMap3DInfo, u16 inIdx, VecFx32 *outVertex)
{
	*outVertex = inMap3DInfo->NormalArray[inMap3DInfo->PolygonData[inIdx].nrm_idx];
}


/**
ソート用配列の初期化
*/
static void InitArray(HEIGHT_ARRAY *outArray)
{
	int i;
	for(i=0;i<MAX_GET_POL;i++){
		outArray[i].Height = 0;
		outArray[i].Prev = -1;
		outArray[i].Next = -1;
	}
}

/**
 高さ配列データのソート(昇順)
*/
static void SortArray(int inCount, HEIGHT_ARRAY *ioArray)
{
	int i;
	int prev;
	for(i=0;i<=inCount-1;i++){
		if (ioArray[i].Height<ioArray[inCount].Height){
			prev = ioArray[i].Prev;
			ioArray[i].Prev = inCount;
			ioArray[inCount].Next = i;
			ioArray[inCount].Prev = prev;
			if (prev>=0){
				ioArray[prev].Next = inCount;
			}
			//FirstIdx = inCount;
			return;
		}else{
			ioArray[inCount].Prev = i;
			ioArray[i].Next = inCount;
		}
	}
	if (inCount>0){
		ioArray[inCount].Next = ioArray[i].Next;
		ioArray[i].Next = inCount;
		ioArray[inCount].Prev = i;
	}
	return;
}

//
//---------------------------------------------------------------------------------------------------------
/**
 *　Zソートされているデータを2分探索
 *	@param	inDataList		データリスト		
 *	@param	inDataSize		データサイズ
 *	@param	inZ_Val			Z値
 *	@param	outIndex		データインデックス
 *	
 *	@retval	BOOL	TRUE:データあり　FALSE:データ無し
*/
//---------------------------------------------------------------------------------------------------------
static BOOL	BinSearch(const u16 *inDataList,const u16 inDataSize,const fx32 inZ_Val,u16 *outIndex)
{
	int min,max; 
	u32 data_idx;
	fx32 z_val;
	if (inDataSize == 0){
		OS_Printf("Zソートデータがありません\n");
		return FALSE;//データなしなので、探索終了
	}else if (inDataSize == 1){
		*outIndex = 0;//探索終了
		return TRUE;
	}

	min = 0;
	max = inDataSize-1;
	data_idx = max/2;
	
	do{
///OS_Printf("min_max:%d,%d\n",min,max);		
		z_val = LINE_Z_VAL(inDataList,data_idx);
///OS_Printf("%d z_val:%x\n",data_idx,z_val);
		if (z_val>inZ_Val){	//探索継続
			if (max-1 > min){
				max = data_idx;
				data_idx = (min+max)/2;
			}else{				//探索終了
				*outIndex = data_idx;
				return TRUE;
			}
		}else{					//探索継続
			if (min+1 < max){
				min = data_idx;
				data_idx = (min+max)/2;
			}else{				//探索終了
				*outIndex = data_idx+1;
				return TRUE;
			}
		}
	}while(1);

	return FALSE;
	//デバッグ：降順判定処理
	
	;
}

//---------------------------------------------------------------------------------------------------------
/**
 *	高さ取得
 *
 *	@param	inNowY			現在Y座標	
 *	@param	inX				求めたい高さのX座標
 *	@param	inZ				求めたい高さのZ座標
 *	@param	inMap3DInfo		高さ情報
 *	@param	outY			高さ格納バッファ
 *	
 *	@retval	BOOL			TRUE:高さを取得できた	FALSE:高さを取得できなかった
*/
//---------------------------------------------------------------------------------------------------------
BOOL GetHeightForBlock(const fx32 inNowY, const fx32 inX, const fx32 inZ, MHI_CONST_PTR inMap3DInfo,fx32 *outY)
{
	VecFx32 vertex[3];
	VecFx32 target,nrm;
	fx32 temp1,temp2;
	BOOL result;
	u16 i,pol_index;
	fx32 d,y;
	int pol_count;
	u32 line_num,tbl_idx,tbl_x_idx,tbl_z_idx;
	HEIGHT_ARRAY height_array[MAX_GET_POL];
	fx32 tbl_x,tbl_z;

	u32 offset_idx;

	u16 line_data_idx;
	u16 line_index;
	u16 polygon_num;

	const u16 *line_list;

	if (inMap3DInfo->DataValid == FALSE){
		return FALSE;
	}
	result = FALSE;
	//ZX平面に射影
	target.x = inX;
	target.y = 0;
	target.z = inZ;
	pol_count = 0;
	InitArray(height_array);
	//捜索テーブルを検出
	tbl_x = inX - inMap3DInfo->SplitGridData->StartX;
	if (tbl_x < 0){
		tbl_x = 0;
	}
	tbl_z = inZ - inMap3DInfo->SplitGridData->StartZ;
	if (tbl_z < 0){
		tbl_z = 0;
	}

	tbl_x = FX_Div(tbl_x, inMap3DInfo->SplitGridData->SizeX);
	tbl_x_idx = (int)(tbl_x>>12);
	if (tbl_x_idx >= inMap3DInfo->SplitGridData->NumX){
		tbl_x_idx = inMap3DInfo->SplitGridData->NumX-1;
	}
	tbl_z = FX_Div(tbl_z, inMap3DInfo->SplitGridData->SizeZ);
	tbl_z_idx = (int)(tbl_z>>12);
	if (tbl_z_idx >= inMap3DInfo->SplitGridData->NumZ){
		tbl_z_idx = inMap3DInfo->SplitGridData->NumZ-1;
	}

	tbl_idx = tbl_x_idx + (tbl_z_idx * inMap3DInfo->SplitGridData->NumZ);
	line_num = inMap3DInfo->GridDataTbl[tbl_idx*GRID_ENTRY_ONE_DATA];
	line_data_idx = inMap3DInfo->GridDataTbl[tbl_idx*GRID_ENTRY_ONE_DATA+1];
#if 1	
///OS_Printf("grid_index:%d\n",tbl_idx);
///OS_Printf("line_data_idx = %d\n",line_data_idx);
///OS_Printf("line_num = %d\n",line_num);
#endif
	line_list = &inMap3DInfo->LineDataTbl[line_data_idx*LINE_ONE_DATA];
	//高さ取得用グリッドデータに登録されているラインデータを2分探索して、自分が立っているポリゴンが存在するラインを検出
	if ( BinSearch(line_list,line_num,target.z,&line_index)==FALSE){
///OS_Printf("NOTHING\n");		
		return FALSE;
	}
///OS_Printf("line_index = %d\n",line_index);

	polygon_num = line_list[line_index*LINE_ONE_DATA];
///OS_Printf("polygon_num = %d\n",polygon_num);
	offset_idx = (line_list[(line_index*LINE_ONE_DATA)+4]<<16) | line_list[(line_index*LINE_ONE_DATA)+3];

///OS_Printf("offset_idx:%d\n",offset_idx);

	//高さ取得用グリッド内ラインデータに登録されているデータ分ループして、自分が立っているポリゴンを検出
	for(i=0;i<polygon_num;i++){
				pol_index = inMap3DInfo->PolyIDList[offset_idx+i];
///OS_Printf("pol_index:%d\n",pol_index);
		//頂点データ取得
		GetPolygonVertex(inMap3DInfo,pol_index, vertex);
		//ZX平面に射影
		vertex[0].y = 0;
		vertex[1].y = 0;
		vertex[2].y = 0;
		//三角形の内外判定
		///result = BG3D_CheckTriangleIO(&target,vertex[0],vertex[1],vertex[2]);
		result = BG3D_CheckTriangleIObyZX(target,vertex[0],vertex[1],vertex[2]);
		if (result == TRUE){//三角形内
			//法線取得
			GetPolygonNrm(inMap3DInfo,pol_index, &nrm);
			//平面の方程式に必要なデータ（原点を通る平面からのオフセット）を取得
			d = inMap3DInfo->PolygonData[pol_index].paramD;
			//平面の方程式より高さ取得
			y = -(FX_Mul(nrm.x, target.x)+FX_Mul(nrm.z, target.z)+d);
			y = FX_Div(y, nrm.y);
			height_array[pol_count].Height = y;
			//配列のソート（現行では機能してません。対応予定）<<未使用にしました。20060801
			///SortArray(pol_count,height_array);
			pol_count++;
///OS_Printf("%d\n",i);
///OS_Printf("D=%d\n",d);
			if (pol_count >= MAX_GET_POL){
				break;
			}
			///break;
		}
	}//end for
	

	if (pol_count > 1){//ポリゴンデータが複数取れたとき
///OS_Printf("!!\n");		
		pol_index = 0;
		temp1 = Max(inNowY,height_array[0].Height) - Min(inNowY,height_array[0].Height);
		//すべてのポリゴンデータの高さを求め、現在の高さに一番近い物を選出する
		for(i=1;i<pol_count;i++){
			temp2 = Max(inNowY,height_array[i].Height) - Min(inNowY,height_array[i].Height);
			if (temp1>temp2){
				temp1 = temp2;
				pol_index = i;
			}
		}
		*outY = height_array[pol_index].Height;
		return TRUE;
	}else if(pol_count == 1){
		*outY = height_array[0].Height;
		return TRUE;
	}
	OS_Printf("高さが取れなかった\n");
#if 1	
	if (pol_count != 0){
		*outY = height_array[0].Height;
		return TRUE;
	}
#endif	
	return FALSE;
}

#ifdef PM_DEBUG

#define EQ_NO	(0)
#define EQ_12	(1)
#define EQ_23	(2)
#define EQ_31	(3)

//---------------------------------------------------------------------------------------------------------
/**
 *	2D平面において、指定３点のうち、２点と同じかをチェック（同一直線上にあるかをチェック）
 *
 *	@param	inTarget			指定座標	
 *	@param	inVal1				座標1
 *	@param	inVal2				座標2
 *	@param	inVal3				座標3
 *	@param	outEqual			結果を格納するバッファ
 *	
 *	@retval	BOOL			TRUE:同一直線上		FALSE:同一直線上ではない
*/
//---------------------------------------------------------------------------------------------------------
static const BOOL Check2DLine(	const fx32 *inTarget,
								const fx32 *inVal1,
								const fx32 *inVal2,
								const fx32 *inVal3,
								u8 *outEqual){
	u8 count;
	count = 0;
	if (*inTarget == *inVal1){
		count++;
	}
	if (*inTarget == *inVal2){
		count++;
	}
	if (*inTarget == *inVal3){
		count++;
	}
	
	if (count == 2){
		//同一直線上
		if (*inVal1 == *inVal2){
			*outEqual = EQ_12;
		}else if(*inVal2 == *inVal3){
			*outEqual = EQ_23;
		}else{	//*inVal3 == *inVal1
			*outEqual = EQ_31;
		}
		return TRUE;
	}else{
		//直線状にない
		*outEqual = EQ_NO;
		return FALSE;
	}
}

//---------------------------------------------------------------------------------------------------------
/**
 *	指定点が返の上にあり、その辺を作る２点の高さが同じ場合、その高さを返す
 *
 *	@param	inTarget			指定座標	
 *	@param	inVec1				座標1
 *	@param	inVec2				座標2
 *	@param	inVec3				座標3
 *	@param	outHeight			結果を格納するバッファ
 *	
 *	@retval	BOOL			TRUE:同一高さ		FALSE:同一高さではない
*/
//---------------------------------------------------------------------------------------------------------
static const BOOL GetEdgeEqualHeightXZFlat(	const VecFx32 *inTarget,
											const VecFx32 *inVec1,
											const VecFx32 *inVec2,
											const VecFx32 *inVec3,
											fx32 *outHeight)
{
	BOOL rc;
	u8 eq;

	//頂点3つのｘｚとターゲットのｘｚを比較
	rc = Check2DLine(&inTarget->x, &inVec1->x, &inVec2->x, &inVec3->x, &eq);
	if (!rc){
		rc = Check2DLine(&inTarget->z, &inVec1->z, &inVec2->z, &inVec3->z, &eq);
	}

	if (rc){
		//同じ高さかをチェック
		if (eq == EQ_12){
			if (inVec1->y == inVec2->y){
				*outHeight = inVec1->y;
				rc = TRUE;
			}
		}else if (eq == EQ_23){
			if (inVec2->y == inVec3->y){
				*outHeight = inVec2->y;
				rc = TRUE;
			}
		}else if (eq == EQ_31){
			if (inVec3->y == inVec1->y){
				*outHeight = inVec3->y;
				rc = TRUE;
			}
		}else{	//EQ_NO
			*outHeight = 0;
			rc = FALSE;
		}
	}
	return rc;
}

//---------------------------------------------------------------------------------------------------------
/**
 *	指定点が頂点(3点)と同じ座標の場合、その高さを返す
 *
 *	@param	inTarget			指定座標	
 *	@param	inVec1				座標1
 *	@param	inVec2				座標2
 *	@param	inVec3				座標3
 *	@param	outHeight			結果を格納するバッファ
 *	
 *	@retval	BOOL			TRUE:同一高さ		FALSE:同一高さではない
*/
//---------------------------------------------------------------------------------------------------------
static const BOOL GetVertexEqualHeight(const VecFx32 *inTarget,
										const VecFx32 *inVec1,
										const VecFx32 *inVec2,
										const VecFx32 *inVec3,
										fx32 *outHeight)
{
	BOOL rc;
	if ( (inTarget->x == inVec1->x)&&(inTarget->z == inVec1->z) ){
		*outHeight = inVec1->y;
		rc = TRUE;
	}else if ( (inTarget->x == inVec2->x)&&(inTarget->z == inVec2->z) ){
		*outHeight = inVec2->y;
		rc = TRUE;
	}else if ( (inTarget->x == inVec3->x)&&(inTarget->z == inVec3->z) ){
		*outHeight = inVec3->y;
		rc = TRUE;
	}else{
		*outHeight = 0;
		rc = FALSE;
	}
	return rc;
}

//---------------------------------------------------------------------------------------------------------
/**
 *	指定された場所の高さデータを調べる
 *
 *	@param	inX			X座標
 *	@param	inZ			Z座標
 *	@param	inMap3DInfo	高さ情報
 *	@param	inDetail	詳細情報を必要とするかのフラグ
 *	
 *	@retval	u8			チェック結果
*/
//---------------------------------------------------------------------------------------------------------
u8 HC_DebugCheckHeight(const fx32 inX, const fx32 inZ, MHI_CONST_PTR inMap3DInfo, const BOOL inDetail)
{
	VecFx32 vertex[3];
	VecFx32 target,nrm;
	fx32 temp1,temp2;
	BOOL result;
	u16 i,pol_index;
	fx32 d,y;
	int pol_count;
	u32 line_num,tbl_idx,tbl_x_idx,tbl_z_idx;
	HEIGHT_ARRAY height_array[MAX_GET_POL];
	fx32 tbl_x,tbl_z;

	u32 offset_idx;

	u16 line_data_idx;
	u16 line_index;
	u16 polygon_num;

	const u16 *line_list;

	VecFx32 vec[3];

	if (inMap3DInfo->DataValid == FALSE){
		OS_Printf("高さデータ構造体ない\n");
		return 0;
	}

	result = FALSE;
	//ZX平面に射影
	target.x = inX;
	target.y = 0;
	target.z = inZ;
	pol_count = 0;
	InitArray(height_array);
	//捜索テーブルを検出
	tbl_x = inX - inMap3DInfo->SplitGridData->StartX;
	if (tbl_x < 0){
		tbl_x = 0;
	}
	tbl_z = inZ - inMap3DInfo->SplitGridData->StartZ;
	if (tbl_z < 0){
		tbl_z = 0;
	}

	tbl_x = FX_Div(tbl_x, inMap3DInfo->SplitGridData->SizeX);
	tbl_x_idx = (int)(tbl_x>>12);
	if (tbl_x_idx >= inMap3DInfo->SplitGridData->NumX){
		tbl_x_idx = inMap3DInfo->SplitGridData->NumX-1;
	}
	tbl_z = FX_Div(tbl_z, inMap3DInfo->SplitGridData->SizeZ);
	tbl_z_idx = (int)(tbl_z>>12);
	if (tbl_z_idx >= inMap3DInfo->SplitGridData->NumZ){
		tbl_z_idx = inMap3DInfo->SplitGridData->NumZ-1;
	}

	tbl_idx = tbl_x_idx + (tbl_z_idx * inMap3DInfo->SplitGridData->NumZ);
	line_num = inMap3DInfo->GridDataTbl[tbl_idx*GRID_ENTRY_ONE_DATA];
	line_data_idx = inMap3DInfo->GridDataTbl[tbl_idx*GRID_ENTRY_ONE_DATA+1];

	line_list = &inMap3DInfo->LineDataTbl[line_data_idx*LINE_ONE_DATA];
	//高さ取得用グリッドデータに登録されているラインデータを2分探索して、自分が立っているポリゴンが存在するラインを検出
	if ( BinSearch(line_list,line_num,target.z,&line_index)==FALSE){
		if (inDetail){
			OS_Printf("二分探索失敗\n");
		}
		return 3;		//高さがない
	}
	polygon_num = line_list[line_index*LINE_ONE_DATA];
	offset_idx = (line_list[(line_index*LINE_ONE_DATA)+4]<<16) | line_list[(line_index*LINE_ONE_DATA)+3];
///OS_Printf("target = %x,%x\n",target.x,target.z);	
	//高さ取得用グリッド内ラインデータに登録されているデータ分ループして、自分が立っているポリゴンを検出
	for(i=0;i<polygon_num;i++){
				pol_index = inMap3DInfo->PolyIDList[offset_idx+i];
		//頂点データ取得
		GetPolygonVertex(inMap3DInfo,pol_index, vertex);
///OS_Printf("vert:%x,%x,%x\n",vertex[0].y,vertex[1].y,vertex[2].y);
		vec[0] = vertex[0];
		vec[1] = vertex[1];
		vec[2] = vertex[2];
		//ZX平面に射影
		vertex[0].y = 0;
		vertex[1].y = 0;
		vertex[2].y = 0;
		//三角形の内外判定
		result = BG3D_CheckTriangleIObyZX(target,vertex[0],vertex[1],vertex[2]);
		if (result == TRUE){//三角形内
/**
			OS_Printf("tri_vert:%x,%x,%x %x,%x,%x %x,%x,%x\n",
		vertex[0].x,vec_y[0],vertex[0].z,
		vertex[1].x,vec_y[1],vertex[1].z,
		vertex[2].x,vec_y[2],vertex[2].z);
*/
///OS_Printf("target:%x,%x\n",target.x,target.z);
			//頂点ヒットをチェック
			if ( GetVertexEqualHeight(&target,&vec[0],&vec[1],&vec[2], &y) ){
				height_array[pol_count].Height = y;
				///OS_Printf("頂点にヒット\n");
			}
			//ＸＺ平面に平行な辺にヒットしているかチェック
			else if( GetEdgeEqualHeightXZFlat(&target,&vec[0],&vec[1],&vec[2], &y) ){
				height_array[pol_count].Height = y;
				///OS_Printf("辺にヒット\n");

			}
			//通常取得
			else{
				//法線取得
				GetPolygonNrm(inMap3DInfo,pol_index, &nrm);
///				OS_Printf("nrm:%x,%x,%x\n",nrm.x,nrm.y,nrm.z);			
				//平面の方程式に必要なデータ（原点を通る平面からのオフセット）を取得
				d = inMap3DInfo->PolygonData[pol_index].paramD;
				//平面の方程式より高さ取得
				y = -(FX_Mul(nrm.x, target.x)+FX_Mul(nrm.z, target.z)+d);
				y = FX_Div(y, nrm.y);
				height_array[pol_count].Height = y;
			}
			
			//配列のソート（現行では機能してません。対応予定）<<未使用にしました。20060801
			pol_count++;
			if (pol_count >= MAX_GET_POL){
				break;
			}
			///break;
		}
	}//end for
	
	if (pol_count > 1){//ポリゴンデータが複数取れたとき
		pol_index = 0;
		temp1 = height_array[0].Height;
		//すべてのポリゴンデータの高さを求め、現在の高さに一番近い物を選出する
		for(i=1;i<pol_count;i++){
			temp2 = height_array[i].Height;
			if (temp1!=temp2){
				if (inDetail){
					int c;
///					OS_Printf("座標:%x,%x  ",inX,inZ);
///					OS_Printf("ここのユニットは%d層です\n",pol_count);
					OS_Printf("検出した高さ：");
					for(c=0;c<pol_count;c++){
						OS_Printf("%x,", height_array[c].Height);
					}
					OS_Printf("\n");
				}
				return 1;
			}
		}
		if (inDetail){
			OS_Printf("同じ高さ%x\n",temp1);
			return 2;
		}
	}else if(pol_count == 1){
		///OS_Printf("PlaneOnly:%x\n",height_array[0].Height);
		return 0;
	}
	//高さがない
	return 3;
}


#endif	//PM_DEBUG

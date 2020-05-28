#include "user_polygon.h"
#include "player.h"

//USER_POLYGON_DATA UserPoly[64];
USER_POLYGON_DATA *UserPolyList;

static void QuadPolyDraw(USER_POLYGON_DATA	*inData);
static void TriPolyDraw(USER_POLYGON_DATA	*inData);

//リスト初期化
void InitUserPolygon(void)
{
	UserPolyList = NULL;
}

static void DefaultCallBack(USER_POLYGON_DATA *inData)
{
	// ポリゴンアトリビュート設定
	NNS_G3dGePolygonAttr(
			GX_LIGHTMASK_0,			  // ライトを反映しない
			GX_POLYGONMODE_MODULATE,	  // モジュレーションポリゴンモード
			GX_CULL_BACK,             // カリング
			//GX_CULL_NONE,             // カリング
			0,                         // ポリゴンＩＤ ０
			31,					  // アルファ値
			GX_POLYGON_ATTR_MISC_NONE );	

	NNS_G3dGeColor( inData->Color );
}

//ポリゴン作成
USER_POLYGON_DATA *AddUserPolygon(
		const VecFx32 *inPos,
		const VecFx32 *inScale,
		const VecFx32 *inRot,
		void *inWork,
		void (*inMove)(struct USER_POLYGON_DATA_tag*),
		void (*inDraw)(struct USER_POLYGON_DATA_tag*) )
{
	USER_POLYGON_DATA *temp;
	USER_POLYGON_DATA *data;
	//メモリ確保
	//data = NNS_FndAllocFromExpHeapEx(sys.appHeap, sizeof(USER_POLYGON_DATA), 16);
	data = sys_AllocMemory(HEAPID_FIELD, sizeof(USER_POLYGON_DATA));
	//初期化
	data->Next = NULL;
	data->Prev = NULL;
	data->Move = inMove;
	data->Draw = inDraw;
	data->Work = inWork;
	//↓ＮＵＬＬアサートつける？
	data->Pos = *inPos;
	data->Scale = *inScale;
	data->Rot = *inRot;
	data->Color = GX_RGB( 0, 5, 31 );

	data->BeforeCB = DefaultCallBack;
	
	//リストに追加
	temp = UserPolyList;
	if (temp == NULL){
		UserPolyList = data;
	}else{
		while(temp->Next != NULL){
			temp = temp->Next;
		}
		temp->Next = data;
		data->Prev = temp;
	}
	return data;
}
/**
BOOL DelUserPolygonFromAdr(USER_POLYGON_DATA *inData)
{
	USER_POLYGON_DATA *data;
	USER_POLYGON_DATA *next;
	USER_POLYGON_DATA *prev;
	//エントリー分動作関数を呼ぶ
	//リストから削除
	data = UserPolyList;
	while(data != NULL){
		if (data == inData){
			next = data->Next;
			prev = data->Prev;
			if (next != NULL){
				data->Next->Prev = data->Prev;
			}
			if (prev != NULL){
				data->Prev->Next = data->Next;
			}
		}
	}
	//メモリ開放(ポリゴンデータとワーク)
	return TRUE;
}
*/
void UserPolygonMoveMain()
{
	USER_POLYGON_DATA *data;
	//エントリー分動作関数を呼ぶ
	//各動作関数を実行
	data = UserPolyList;
	while(data != NULL){
		if (data->Move != NULL){
			data->Move(data);
		}
		data = data->Next;
	}
}

void UserPolygonDraw()
{
	//エントリー分ループ
	USER_POLYGON_DATA *data;
	//エントリー分描画関数を呼ぶ
	//各動作関数を実行
	data = UserPolyList;
	if (data == NULL){
		return;
	}

	{
		VecFx32		base = { 0, 0,0 };
		NNS_G3dGlbSetBaseTrans(&base);
		NNS_G3dGlbFlush();
	}
	
	while(data != NULL){
		if (data->Draw != NULL){
			data->Draw(data);
		}
		data = data->Next;
	}
	
	// 同期を取る
	//
	NNS_G3dGeFlushBuffer();
}

void TestDraw(USER_POLYGON_DATA	*inData)
{
// 描画開始
	

	//
	// 描画設定
	// 
	NNS_G3dGePushMtx();
	{
		VecFx32		scal = { FX32_ONE>>2, FX32_ONE>>2,FX32_ONE>>2 };
		
		// 座標変換
		NNS_G3dGeTranslateVec( &inData->Pos );			// 平行移動
		NNS_G3dGeScaleVec(&scal);								// 拡縮

		
		// ポリゴンアトリビュート設定
		NNS_G3dGePolygonAttr(
				   GX_LIGHTMASK_0,			  // ライトを反映しない
				   GX_POLYGONMODE_MODULATE,	  // モジュレーションポリゴンモード
				   GX_CULL_BACK,             // カリング
				   //GX_CULL_NONE,             // カリング
				   0,                         // ポリゴンＩＤ ０
				   0x31,					  // アルファ値
				   GX_POLYGON_ATTR_MISC_NONE );	

		NNS_G3dGeColor( GX_RGB( 31, 5, 0 ) );	
		// 四角形を描画開始
		NNS_G3dGeBegin( GX_BEGIN_QUADS );
		{
			// 色を変えるよう
			static int count1 = 0;
			static int count2 = 100000;
			static int count3 = 200000;
			
			// 色
			//NNS_G3dGeColor( GX_RGB( count1 / 10000, count2 / 10000, count3 / 10000 ) );
			

			// 各色の要素を変動させる
			count1 = (count1 + 5) % 160000;
			count2 = (count2 + 3) % 160000;
			count3 = (count3 + 1) % 160000;
			
			// 頂点
			NNS_G3dGeVtx( -FX32_ONE,  FX32_ONE, FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE,  FX32_ONE, FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE, -FX32_ONE, FX32_ONE );
			NNS_G3dGeVtx( -FX32_ONE, -FX32_ONE, FX32_ONE );

#if 1
			NNS_G3dGeVtx( -FX32_ONE, -FX32_ONE, -FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE, -FX32_ONE, -FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE,  FX32_ONE, -FX32_ONE );
			NNS_G3dGeVtx( -FX32_ONE,  FX32_ONE, -FX32_ONE );

			NNS_G3dGeVtx(  FX32_ONE,  FX32_ONE, -FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE, -FX32_ONE, -FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE, -FX32_ONE,  FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE,  FX32_ONE,  FX32_ONE );

			NNS_G3dGeVtx( -FX32_ONE,  FX32_ONE,  FX32_ONE );
			NNS_G3dGeVtx( -FX32_ONE, -FX32_ONE,  FX32_ONE );
			NNS_G3dGeVtx( -FX32_ONE, -FX32_ONE, -FX32_ONE );
			NNS_G3dGeVtx( -FX32_ONE,  FX32_ONE, -FX32_ONE );

			NNS_G3dGeVtx( -FX32_ONE,  FX32_ONE, -FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE,  FX32_ONE, -FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE,  FX32_ONE,  FX32_ONE );
			NNS_G3dGeVtx( -FX32_ONE,  FX32_ONE,  FX32_ONE );

			NNS_G3dGeVtx( -FX32_ONE, -FX32_ONE,  FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE, -FX32_ONE,  FX32_ONE );
			NNS_G3dGeVtx(  FX32_ONE, -FX32_ONE, -FX32_ONE );
			NNS_G3dGeVtx( -FX32_ONE, -FX32_ONE, -FX32_ONE );

#endif
		}
		// 描画終了
		NNS_G3dGeEnd();
	}
	NNS_G3dGePopMtx(1);
}

//四角形ポリゴンの登録
USER_POLYGON_DATA *AddUserQuadPolygon(
		const VecFx32 *inTrans,
		const VecFx32 *inScale,
		const VecFx32 *inRot,
		const VecFx32 *inVtx1, 
		const VecFx32 *inVtx2,
		const VecFx32 *inVtx3,
		const VecFx32 *inVtx4,
		void *inWork,
		void (*inMove)(struct USER_POLYGON_DATA_tag*) )
{
	USER_POLYGON_DATA *data;
	data = AddUserPolygon(inTrans, inScale, inRot, inWork, inMove, QuadPolyDraw );
	//data->Vtx = NNS_FndAllocFromExpHeapEx(sys.appHeap, sizeof(VecFx32)*4, 16);
	data->Vtx = sys_AllocMemory(HEAPID_FIELD, sizeof(VecFx32)*4);
	data->Vtx[0] = *inVtx1;
	data->Vtx[1] = *inVtx2;
	data->Vtx[2] = *inVtx3;
	data->Vtx[3] = *inVtx4;

	return data;
}

//三角形ポリゴンの登録
USER_POLYGON_DATA *AddUserTriPolygon(
		const VecFx32 *inTrans,
		const VecFx32 *inScale,
		const VecFx32 *inRot,
		const VecFx32 *inVtx1, 
		const VecFx32 *inVtx2,
		const VecFx32 *inVtx3,
		void *inWork,
		void (*inMove)(struct USER_POLYGON_DATA_tag*) )
{
	USER_POLYGON_DATA *data;
	data = AddUserPolygon(inTrans, inScale, inRot, inWork, inMove, TriPolyDraw );
	//data->Vtx = NNS_FndAllocFromExpHeapEx(sys.appHeap, sizeof(VecFx32)*3, 16);
	data->Vtx = sys_AllocMemory(HEAPID_FIELD, sizeof(VecFx32)*3);
	data->Vtx[0] = *inVtx1;
	data->Vtx[1] = *inVtx2;
	data->Vtx[2] = *inVtx3;

	return data;
}


static void QuadPolyDraw(USER_POLYGON_DATA	*inData)
{
// 描画開始
	//
	// 描画設定
	// 
	NNS_G3dGePushMtx();
	{
		// 座標変換
		NNS_G3dGeTranslateVec( &inData->Pos );			// 平行移動
		NNS_G3dGeScaleVec(&inData->Scale);				// 拡縮
		{
			MtxFx33 rot;
			VecFx32_to_MtxFx33( &rot, &inData->Rot);	//回転
			NNS_G3dGeMultMtx33(&rot);
		}
		inData->BeforeCB(inData);

		// 四角形を描画開始
		NNS_G3dGeBegin( GX_BEGIN_QUADS );
		{
			// 頂点
			NNS_G3dGeVtx( inData->Vtx[0].x, inData->Vtx[0].y, inData->Vtx[0].z );
			NNS_G3dGeVtx( inData->Vtx[1].x, inData->Vtx[1].y, inData->Vtx[1].z );
			NNS_G3dGeVtx( inData->Vtx[2].x, inData->Vtx[2].y, inData->Vtx[2].z );
			NNS_G3dGeVtx( inData->Vtx[3].x, inData->Vtx[3].y, inData->Vtx[3].z );
		}
		// 描画終了
		NNS_G3dGeEnd();
	}
	NNS_G3dGePopMtx(1);
}

static void TriPolyDraw(USER_POLYGON_DATA	*inData)
{
// 描画開始
	//
	// 描画設定
	// 
	NNS_G3dGePushMtx();
	{
		// 座標変換
		NNS_G3dGeTranslateVec( &inData->Pos );			// 平行移動
		NNS_G3dGeScaleVec(&inData->Scale);				// 拡縮
		{
			MtxFx33 rot;
			VecFx32_to_MtxFx33( &rot, &inData->Rot);	//回転
			NNS_G3dGeMultMtx33(&rot);
		}

		inData->BeforeCB(inData);	
		// 三角形を描画開始
		NNS_G3dGeBegin( GX_BEGIN_TRIANGLES );
		{
			// 頂点
			NNS_G3dGeVtx( inData->Vtx[0].x, inData->Vtx[0].y, inData->Vtx[0].z );
			NNS_G3dGeVtx( inData->Vtx[1].x, inData->Vtx[1].y, inData->Vtx[1].z );
			NNS_G3dGeVtx( inData->Vtx[2].x, inData->Vtx[2].y, inData->Vtx[2].z );

		}
		// 描画終了
		NNS_G3dGeEnd();
	}
	NNS_G3dGePopMtx(1);
}

void SetCallBack(USER_POLYGON_DATA *inData, void (*inCallBack)(USER_POLYGON_DATA*))
{
	inData->BeforeCB = inCallBack;
}

#ifdef DEBUG_USER_POLYGON
//----------------------------------------------------------------
//	デバッグ・テスト
//----------------------------------------------------------------
u8 PosTable[9];

static void CBDrawWireFrame(USER_POLYGON_DATA *inData)
{
	// ポリゴンアトリビュート設定
	NNS_G3dGePolygonAttr(
			GX_LIGHTMASK_0,			  // ライトを反映しない
			GX_POLYGONMODE_MODULATE,	  // モジュレーションポリゴンモード
			GX_CULL_BACK,             // カリング
			//GX_CULL_NONE,             // カリング
			0,                         // ポリゴンＩＤ ０
			0,					  // アルファ値
			GX_POLYGON_ATTR_MISC_NONE );	

	NNS_G3dGeColor( inData->Color );
}

static void GridPolyFunc(USER_POLYGON_DATA *ioData)
{
	u8 *idx;
	s8 z,x;
	VecFx32 player_vec;
	
	idx = (u8 *)ioData->Work;
	
	z = *idx/3;
	x = *idx%3;
	z += (-1);
	x += (-1); 
///	ioData->Pos = map3Ddata->actor[0].global;
	player_vec = *(Player_VecPosPtrGet(ioData->fsys->player));
	ioData->Pos = player_vec;
	ioData->Pos.y += (FX32_ONE);
	
	ioData->Pos.z += ( (FX32_ONE*16)*(z) );
	ioData->Pos.x += ( (FX32_ONE*16)*(x) );
	{
		VecFx32 vec={0,0,0};
///		VecFx32 dst;
///		MtxFx43 mat;

///		MTX_Copy44To43(NNS_G3dGlbGetInvVP(), &mat);
		
///		MTX_MultVec43(&vec, &mat, &dst);
///		OS_Printf("point=%x,%x,%x\n",dst.x,dst.y,dst.z);
/*
		vec = GetLookTarget(ioData->fsys->camera_ptr);
		OS_Printf("target_point=%x,%x,%x\n",vec.x,vec.y,vec.z);
		VEC_Subtract(&vec,&player_vec,&vec);
		vec = GetCameraPos(ioData->fsys->camera_ptr);

		OS_Printf("cam_point=%x,%x,%x\n",vec.x,vec.y,vec.z);
*/
	}
}

void TestInitPlayerGrid(FIELDSYS_WORK *fsys)
{
	USER_POLYGON_DATA *poly_data;
	u8 i;
	for(i=0;i<9;i++){	
		VecFx32 trans = {0,0,0};
		VecFx32 scale = {FX32_ONE*8,FX32_ONE,FX32_ONE*8};
		VecFx32 rot= {0,0,0};
		VecFx32 vtx1 = {FX32_ONE,0,FX32_ONE};
		VecFx32 vtx2 = {FX32_ONE,0,-FX32_ONE};
		VecFx32 vtx3 = {-FX32_ONE,0,-FX32_ONE};
		VecFx32 vtx4 = {-FX32_ONE,0,FX32_ONE};
		PosTable[i] = i;
		poly_data = AddUserQuadPolygon(
			&trans,
			&scale,
			&rot,
			&vtx1, 
			&vtx2,
			&vtx3,
			&vtx4,
			&PosTable[i],
			GridPolyFunc);
		SetCallBack(poly_data,CBDrawWireFrame);
		poly_data->fsys = fsys;
	}
}

void FreeUserPolygon(USER_POLYGON_DATA **outData)
{
	sys_FreeMemoryEz((*outData)->Vtx);
	sys_FreeMemoryEz((*outData));
	(*outData) = NULL;
}

void DelUserPolygonAll(void)
{
	USER_POLYGON_DATA *data;
	USER_POLYGON_DATA *next;
	USER_POLYGON_DATA *prev;
	//エントリー分動作関数を呼ぶ
	//リストから削除
	data = UserPolyList;
	while(data != NULL){
		next = data->Next;
		FreeUserPolygon(&data);
		data = next;
	}
	UserPolyList = NULL;
	//メモリ開放(ポリゴンデータとワーク)
	return;
}
#endif //DEBUG_USER_POLYGON

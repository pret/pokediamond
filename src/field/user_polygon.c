#include "user_polygon.h"
#include "player.h"

//USER_POLYGON_DATA UserPoly[64];
USER_POLYGON_DATA *UserPolyList;

static void QuadPolyDraw(USER_POLYGON_DATA	*inData);
static void TriPolyDraw(USER_POLYGON_DATA	*inData);

//���X�g������
void InitUserPolygon(void)
{
	UserPolyList = NULL;
}

static void DefaultCallBack(USER_POLYGON_DATA *inData)
{
	// �|���S���A�g���r���[�g�ݒ�
	NNS_G3dGePolygonAttr(
			GX_LIGHTMASK_0,			  // ���C�g�𔽉f���Ȃ�
			GX_POLYGONMODE_MODULATE,	  // ���W�����[�V�����|���S�����[�h
			GX_CULL_BACK,             // �J�����O
			//GX_CULL_NONE,             // �J�����O
			0,                         // �|���S���h�c �O
			31,					  // �A���t�@�l
			GX_POLYGON_ATTR_MISC_NONE );	

	NNS_G3dGeColor( inData->Color );
}

//�|���S���쐬
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
	//�������m��
	//data = NNS_FndAllocFromExpHeapEx(sys.appHeap, sizeof(USER_POLYGON_DATA), 16);
	data = sys_AllocMemory(HEAPID_FIELD, sizeof(USER_POLYGON_DATA));
	//������
	data->Next = NULL;
	data->Prev = NULL;
	data->Move = inMove;
	data->Draw = inDraw;
	data->Work = inWork;
	//���m�t�k�k�A�T�[�g����H
	data->Pos = *inPos;
	data->Scale = *inScale;
	data->Rot = *inRot;
	data->Color = GX_RGB( 0, 5, 31 );

	data->BeforeCB = DefaultCallBack;
	
	//���X�g�ɒǉ�
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
	//�G���g���[������֐����Ă�
	//���X�g����폜
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
	//�������J��(�|���S���f�[�^�ƃ��[�N)
	return TRUE;
}
*/
void UserPolygonMoveMain()
{
	USER_POLYGON_DATA *data;
	//�G���g���[������֐����Ă�
	//�e����֐������s
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
	//�G���g���[�����[�v
	USER_POLYGON_DATA *data;
	//�G���g���[���`��֐����Ă�
	//�e����֐������s
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
	
	// ���������
	//
	NNS_G3dGeFlushBuffer();
}

void TestDraw(USER_POLYGON_DATA	*inData)
{
// �`��J�n
	

	//
	// �`��ݒ�
	// 
	NNS_G3dGePushMtx();
	{
		VecFx32		scal = { FX32_ONE>>2, FX32_ONE>>2,FX32_ONE>>2 };
		
		// ���W�ϊ�
		NNS_G3dGeTranslateVec( &inData->Pos );			// ���s�ړ�
		NNS_G3dGeScaleVec(&scal);								// �g�k

		
		// �|���S���A�g���r���[�g�ݒ�
		NNS_G3dGePolygonAttr(
				   GX_LIGHTMASK_0,			  // ���C�g�𔽉f���Ȃ�
				   GX_POLYGONMODE_MODULATE,	  // ���W�����[�V�����|���S�����[�h
				   GX_CULL_BACK,             // �J�����O
				   //GX_CULL_NONE,             // �J�����O
				   0,                         // �|���S���h�c �O
				   0x31,					  // �A���t�@�l
				   GX_POLYGON_ATTR_MISC_NONE );	

		NNS_G3dGeColor( GX_RGB( 31, 5, 0 ) );	
		// �l�p�`��`��J�n
		NNS_G3dGeBegin( GX_BEGIN_QUADS );
		{
			// �F��ς���悤
			static int count1 = 0;
			static int count2 = 100000;
			static int count3 = 200000;
			
			// �F
			//NNS_G3dGeColor( GX_RGB( count1 / 10000, count2 / 10000, count3 / 10000 ) );
			

			// �e�F�̗v�f��ϓ�������
			count1 = (count1 + 5) % 160000;
			count2 = (count2 + 3) % 160000;
			count3 = (count3 + 1) % 160000;
			
			// ���_
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
		// �`��I��
		NNS_G3dGeEnd();
	}
	NNS_G3dGePopMtx(1);
}

//�l�p�`�|���S���̓o�^
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

//�O�p�`�|���S���̓o�^
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
// �`��J�n
	//
	// �`��ݒ�
	// 
	NNS_G3dGePushMtx();
	{
		// ���W�ϊ�
		NNS_G3dGeTranslateVec( &inData->Pos );			// ���s�ړ�
		NNS_G3dGeScaleVec(&inData->Scale);				// �g�k
		{
			MtxFx33 rot;
			VecFx32_to_MtxFx33( &rot, &inData->Rot);	//��]
			NNS_G3dGeMultMtx33(&rot);
		}
		inData->BeforeCB(inData);

		// �l�p�`��`��J�n
		NNS_G3dGeBegin( GX_BEGIN_QUADS );
		{
			// ���_
			NNS_G3dGeVtx( inData->Vtx[0].x, inData->Vtx[0].y, inData->Vtx[0].z );
			NNS_G3dGeVtx( inData->Vtx[1].x, inData->Vtx[1].y, inData->Vtx[1].z );
			NNS_G3dGeVtx( inData->Vtx[2].x, inData->Vtx[2].y, inData->Vtx[2].z );
			NNS_G3dGeVtx( inData->Vtx[3].x, inData->Vtx[3].y, inData->Vtx[3].z );
		}
		// �`��I��
		NNS_G3dGeEnd();
	}
	NNS_G3dGePopMtx(1);
}

static void TriPolyDraw(USER_POLYGON_DATA	*inData)
{
// �`��J�n
	//
	// �`��ݒ�
	// 
	NNS_G3dGePushMtx();
	{
		// ���W�ϊ�
		NNS_G3dGeTranslateVec( &inData->Pos );			// ���s�ړ�
		NNS_G3dGeScaleVec(&inData->Scale);				// �g�k
		{
			MtxFx33 rot;
			VecFx32_to_MtxFx33( &rot, &inData->Rot);	//��]
			NNS_G3dGeMultMtx33(&rot);
		}

		inData->BeforeCB(inData);	
		// �O�p�`��`��J�n
		NNS_G3dGeBegin( GX_BEGIN_TRIANGLES );
		{
			// ���_
			NNS_G3dGeVtx( inData->Vtx[0].x, inData->Vtx[0].y, inData->Vtx[0].z );
			NNS_G3dGeVtx( inData->Vtx[1].x, inData->Vtx[1].y, inData->Vtx[1].z );
			NNS_G3dGeVtx( inData->Vtx[2].x, inData->Vtx[2].y, inData->Vtx[2].z );

		}
		// �`��I��
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
//	�f�o�b�O�E�e�X�g
//----------------------------------------------------------------
u8 PosTable[9];

static void CBDrawWireFrame(USER_POLYGON_DATA *inData)
{
	// �|���S���A�g���r���[�g�ݒ�
	NNS_G3dGePolygonAttr(
			GX_LIGHTMASK_0,			  // ���C�g�𔽉f���Ȃ�
			GX_POLYGONMODE_MODULATE,	  // ���W�����[�V�����|���S�����[�h
			GX_CULL_BACK,             // �J�����O
			//GX_CULL_NONE,             // �J�����O
			0,                         // �|���S���h�c �O
			0,					  // �A���t�@�l
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
	//�G���g���[������֐����Ă�
	//���X�g����폜
	data = UserPolyList;
	while(data != NULL){
		next = data->Next;
		FreeUserPolygon(&data);
		data = next;
	}
	UserPolyList = NULL;
	//�������J��(�|���S���f�[�^�ƃ��[�N)
	return;
}
#endif //DEBUG_USER_POLYGON

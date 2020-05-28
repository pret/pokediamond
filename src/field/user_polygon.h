#ifndef _USER_POLYGON_H_
#define _USER_POLYGON_H_

#define DEBUG_USER_POLYGON

#include <nitro.h>
#include <nnsys.h>
#include "common.h"
#include "fieldsys.h"
//typedef PolygonFunc 
typedef struct USER_POLYGON_DATA_tag
{
	VecFx32 Pos;	//�ʒu���W
	VecFx32 Scale;	//�X�P�[��
	VecFx32 Rot;	//��]
	VecFx32 *Vtx;
	void *Work;		//���[�N�̈�p���H�C�h�|�C���^
	void (*Move)( struct USER_POLYGON_DATA_tag* );//����֐�
	void (*Draw)( struct USER_POLYGON_DATA_tag* );//�`��֐�
	struct USER_POLYGON_DATA_tag *Next;//�����N��
	struct USER_POLYGON_DATA_tag *Prev;//�����N��
	u32 Color;
	void (*BeforeCB)(struct USER_POLYGON_DATA_tag*);	//���_�錾�O�R�[���o�b�N

	u8 Flag;
	FIELDSYS_WORK *fsys;
}USER_POLYGON_DATA;

extern void InitUserPolygon(void);
extern USER_POLYGON_DATA *AddUserPolygon(
		const VecFx32 *inPos,
		const VecFx32 *inScale,
		const VecFx32 *inRot,
		void *inWork, 
		void (*inMove)(struct USER_POLYGON_DATA_tag*),
		void (*inDraw)(struct USER_POLYGON_DATA_tag*) );
extern void UserPolygonMoveMain();
extern void UserPolygonDraw();

extern void TestDraw(USER_POLYGON_DATA	*inData);

extern USER_POLYGON_DATA *AddUserQuadPolygon(
		const VecFx32 *inTrans,
		const VecFx32 *inScale,
		const VecFx32 *inRot,
		const VecFx32 *inVtx1, 
		const VecFx32 *inVtx2,
		const VecFx32 *inVtx3,
		const VecFx32 *inVtx4,
		void *inWork,
		void (*inMove)(struct USER_POLYGON_DATA_tag*) );

extern USER_POLYGON_DATA *AddUserTriPolygon(
		const VecFx32 *inTrans,
		const VecFx32 *inScale,
		const VecFx32 *inRot,
		const VecFx32 *inVtx1, 
		const VecFx32 *inVtx2,
		const VecFx32 *inVtx3,
		void *inWork,
		void (*inMove)(struct USER_POLYGON_DATA_tag*) );
extern void SetCallBack(	USER_POLYGON_DATA *inData, 
							void (*inCallBack)(USER_POLYGON_DATA*)
						);
extern void DelUserPolygonAll(void);
#ifdef DEBUG_USER_POLYGON
//----------------------------------------------------------------
//	�f�o�b�O�E�e�X�g
//----------------------------------------------------------------
extern void TestInitPlayerGrid(FIELDSYS_WORK *fsys);
#endif	//DEBUG_USER_POLYGON

#endif //_USER_POLYGON_H_

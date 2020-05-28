//=============================================================================================
/**
 * @file	calc3D.h
 * @brief	�a�f�`��v�Z�v���O����
 */
//=============================================================================================
#undef GLOBAL
#ifdef __CALC3D_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

/*---------------------------------------------------------------------
 *
 *
 *
 *			�����蔻��
 *
 *
 *
 *--------------------------------------------------------------------*/
////////////////////////////
GLOBAL fx32 Min(fx32 n1,fx32 n2);
GLOBAL fx32 Max(fx32 n1,fx32 n2);
// �����蔻��p�\���́F�~��
typedef struct {
	VecFx32	global;	//�O���[�o�����W�x�N�g��

	fx32	vUp;		//���S�_����́{�x�����I�t�Z�b�g
	fx32	vDown;		//���S�_����́|�x�����I�t�Z�b�g

	fx32	radius;		//���a
}HIT_CHECK_ENTYUU;

GLOBAL int  BG3D_CalcHitCheck_CylinderCylinder(HIT_CHECK_ENTYUU* object1,HIT_CHECK_ENTYUU* object2);

GLOBAL int BG3D_CalcHitCheck_SegmentSphere(const VecFx32 *inCoreVec, const fx32 inRadius, const VecFx32 *inStartVec, const VecFx32 *inEndVec);

GLOBAL BOOL BG3D_CheckTriangleIO(const VecFx32 *inTargetVtx,VecFx32 inVtx1,VecFx32 inVtx2,VecFx32 inVtx3);
GLOBAL BOOL BG3D_CheckTriangleIObyZX(const VecFx32 inT_Vtx,const VecFx32 inVtx1,const VecFx32 inVtx2,const VecFx32 inVtx3);

GLOBAL fx32 BG3D_GetPointSegmentDistance(const VecFx32 *inPoint, const VecFx32 *inStartVec, const VecFx32 *inEndVec);

GLOBAL fx32 BG3D_GetPointSegmentDistance2(const VecFx32 *inPoint, const VecFx32 *inStartVec, const VecFx32 *inEndVec);

GLOBAL fx32 BG3D_GetPointPlaneDistance(const VecFx32 *inPoint, const VecFx32 *inNrm,const fx32 inD );

GLOBAL BOOL GetCrossPointPlaneToSegment(const VecFx32 *inNrmVec, const fx32 inD, 
								const VecFx32 *inStartVec, const VecFx32 *inEndVec,
								VecFx32 *outVec);

GLOBAL BOOL HitCheckPlaneToBox2(const VecFx32 *inBoxCore, 
						const VecFx32 *inVecR,
						const VecFx32 *inVecS,
						const VecFx32 *inVecT,
						const VecFx32 *inNrm,
						const fx32 inD );

GLOBAL int GetHitPointPlaneToBox2(const VecFx32 *inBoxCore, 
						const VecFx32 *inVecR,
						const VecFx32 *inVecS,
						const VecFx32 *inVecT,
						const VecFx32 *inNrm,
						VecFx32 *outPointList);

#define	HITCHECK_TYPE_ENTYU		(1)

#define NO_HIT				(0)		//�q�b�g���Ă��Ȃ�
#define SEG_SPH_HIT_SEG		(1)		//�����Ƌ����q�b�g
#define SEG_SPH_HIT_START	(2)		//�����̎n�_�Ƌ����q�b�g
#define SEG_SPH_HIT_END		(3)		//�����̏I�_�Ƌ����q�b�g

typedef enum {
	XY_PLANE,
	YZ_PLANE,
	ZX_PLANE
}PLANE_TYPE;

////////////////////////////
// �����蔻��\����
typedef struct {
	int			type;
	const fx32*	data;

}HITCHECK_HEADER;
GLOBAL const  fx32	dummy_hitcheck_data[];
GLOBAL const  fx32	entyu1_hitcheck_data[];
GLOBAL const  fx32	entyu2_hitcheck_data[];


//---------------------------------------------------------------------------------------------------------
/**
 *	�i�s�����x�N�g���C��(�ǂ���ړ�)
 *	@param	*inMoveVec		�ړ��ʁi�ړ������j
 *	@param	*ioDirVec		�C����ړ�����
 *
 *	@retval	VecFx32			�C����ړ��ʁi�ړ������j
*/
//---------------------------------------------------------------------------------------------------------
GLOBAL	VecFx32 ChangeDirForWall(const VecFx32* inMoveVec, const VecFx32 *inDirVec);
//---------------------------------------------------------------------------------------------------------
/**
 *	�����x�N�g�������]�p���v�Z�i�y�w���ʑΉ��j
 *	@param	*inVec1		������x�N�g��
 *	@param	*inVec2		�w������x�N�g��
 *
 *	@retval	rad			��]�p
*/
//---------------------------------------------------------------------------------------------------------
GLOBAL	fx32 GetRad(const VecFx32 *inVec1, const VecFx32 *inVec2 );


//���ʂƃ{�b�N�X�̏Փ˔���
//���ʂƃ{�b�N�X�̎������a�̋��������ɁA�Փ˂����o����
//�K�v�f�[�^�F	�{�b�N�X�̒��S���W
//				�{�b�N�X�̕��A�����A���s��
//				�{�b�N�X�̉�]�s��
//				���ʂ̖@���x�N�g��
//				���ʂ̕������ɕK�v�Ȃc�u
GLOBAL BOOL HitCheckPlaneToBox(const VecFx32 *inBoxCore, 
						const VecFx32 *inBoxSize, 
						const VecFx32 *inBoxRot, 
						const VecFx32 *inNrm,
						const fx32 inD );

GLOBAL int GetHitPointPlaneToBox(const VecFx32 *inBoxCore, 
						const VecFx32 *inBoxSize, 
						const VecFx32 *inBoxRot, 
						const VecFx32 *inNrm,
						VecFx32 *outPointList);

GLOBAL BOOL HitCheckBoxToBox(const VecFx32 *inBoxCore1, 
						const VecFx32 *inBoxSize1, 
						const VecFx32 *inBoxRot1,
						const VecFx32 *inDirVec1,
						const VecFx32 *inBoxCore2, 
						const VecFx32 *inBoxSize2, 
						const VecFx32 *inBoxRot2,
						const VecFx32 *inDirVec2);

//////////////////////////////////////////////////
//2D
//////////////////////////////////////////////////

GLOBAL int BG2D_VectorSide( const VecFx32 *inS_Vec, const VecFx32 *inE_Vec, const VecFx32 *inT_Vec );
GLOBAL BOOL BG2D_CheckSegmentToSegment( const VecFx32 *inS_Vec1, const VecFx32 *inE_Vec1, const VecFx32 *inS_Vec2, const VecFx32 *inE_Vec2 );
GLOBAL BOOL GetPointLineToLine(	const VecFx32 *inS_Vec1,
									const VecFx32 *inE_Vec1,
									const VecFx32 *inS_Vec2,
									const VecFx32 *inE_Vec2,
									VecFx32 *outVec );
GLOBAL BOOL GetPointSegmentToSegment(	const VecFx32 *inS_Vec1,
									const VecFx32 *inE_Vec1,
									const VecFx32 *inS_Vec2,
									const VecFx32 *inE_Vec2,
									VecFx32 *outVec );
GLOBAL BOOL CheckHitPlaneToSegment2D(	const VecFx32 *inVtx1,
								const VecFx32 *inVtx2,
								const VecFx32 *inVtx3,
								const VecFx32 *inVtx4,
								const VecFx32 *inS_Vec,
								const VecFx32 *inE_Vec );

/*---------------------------------------------------------------------
 *
 *
 *
 *			���Z
 *
 *
 *
 *--------------------------------------------------------------------*/
/*---------------------------------------------------------------------
  Name       :�x�N�g�����R�w�R�s��ւ̕ϊ� 
  In	: dst = �s��|�C���^,dst = �x�N�g���|�C���^ 
  Out	: �Ȃ�
 *--------------------------------------------------------------------*/
GLOBAL void  VecFx32_to_MtxFx33( MtxFx33* dst, VecFx32* src );
/*---------------------------------------------------------------------
  Name       :�x�N�g�����S�w�R�s��ւ̕ϊ� 
  In	: dst = �s��|�C���^,dst = �x�N�g���|�C���^ 
  Out	: �Ȃ�
 *--------------------------------------------------------------------*/
GLOBAL void  VecFx32_to_MtxFx43( MtxFx43* dst, VecFx32* src );

/*---------------------------------------------------------------------
  @brief	360�xXYZ�̉�]�p���R�w�R�s��ւ̕ϊ� 

  @param	dst MtxFx33:���Z���ʂ��i�[����MtxFx33�^�̃|�C���^
  @param	x	��]�pX(360�x�P��,0-359�𒴂��Ȃ���)
  @param	y	��]�pY(360�x�P��)
  @param	z	��]�pZ(360�x�P��)

  @return none
 *--------------------------------------------------------------------*/
GLOBAL void  Rot360_to_MtxFx33( MtxFx33* dst,u16 x,u16 y,u16 z);

/*---------------------------------------------------------------------
  @brief	360�xXYZ�̉�]�p��4x3�s��ւ̕ϊ� 

  @param	dst MtxFx43:���Z���ʂ��i�[����MtxFx43�^�̃|�C���^
  @param	x	��]�pX(360�x�P��,0-359�𒴂��Ȃ���)
  @param	y	��]�pY(360�x�P��,0-359)
  @param	z	��]�pZ(360�x�P��,0-359)

  @return none
 *--------------------------------------------------------------------*/
GLOBAL void  Rot360_to_MtxFx43( MtxFx43* dst,u16 x,u16 y,u16 z);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�ˉe�s��̃f�[�^���獡�̍����ƕ���Ԃ�
 *
 *@param	PerspWay	����p
 *@param	Dist		�^�[�Q�b�g�܂ł̋���
 *@param	Aspect		�A�X�y�N�g��	(��/����)
 *@param	pWidth		���i�[�p
 *@param	pHeight		�����i�[�p
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void GetPerspectiveScreenSize( u16 PerspWay, fx32 Dist, fx32 Aspect, fx32* pWidth, fx32* pHeight );
#undef GLOBAL


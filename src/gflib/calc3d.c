/*---------------------------------------------------------------------------*
  Project:  
  File:     calc3d.c
 *---------------------------------------------------------------------------*/
#include <nnsys.h>

#define	__CALC3D_H_GLOBAL
#include "calctool.h"
#include "calc3D.h"

//�{�b�N�X�ƃ{�b�N�X�̏Փˌ��o(�˂���̈ʒu�ɂ���ӓ��m�̏Փ�)�Ɏg���\����
//�ʏՓ˔���ɂ����āA1���_�Փ˂����Ƃ��̓_���L�����Ă���
typedef struct VTX_DATA_tag{
	u8 Idx;			//�{�b�N�X�̏Փ˖�
	VecFx32 Vtx;	//�Փ˂������_
}VTX_DATA;

typedef struct VTX_DATA_FOR_BOXHIT_tag
{
	VTX_DATA VtxData[2];	//�˂���̈ʒu�ɂ���ӓ��m�̏Փ˂ł́A3���_�ȏ�̖ʏՓ˂͋N����Ȃ��̂ŁA�z���2�܂ŗp��
	u8 Count;	//1���_�Փ˂�����
	
}VTX_DATA_FOR_BOXHIT;


//�Е��̃{�b�N�X�������s�Ȃ�тɁA1���_�����_��ʂ�悤�ɉ�]�A�ړ������ۂ�
//�{�b�N�X�̖@���x�N�g��
static VecFx32 BoxNrm[6] = {
	{FX32_ONE ,0		,0			},
	{0		  ,FX32_ONE	,0			},
	{0		  ,0		,FX32_ONE	},
	{-FX32_ONE,0		,0			},
	{0		  ,-FX32_ONE,0			},
	{0		  ,0		,-FX32_ONE	}
};

//�Е��̃{�b�N�X�������s�Ȃ�тɁA1���_�����_��ʂ�悤�ɉ�]�A�ړ������ۂ�
//�{�b�N�X���ʂ�D�l�i�X�P�[���{����K�v����j
static fx32 BoxDBase[6] = {
	-FX32_ONE,
	-FX32_ONE,
	-FX32_ONE,
	0,
	0,
	0
};

/*---------------------------------------------------------------------
 *
 *
 *
 *			�����蔻��v�Z
 *
 *
 *
 *--------------------------------------------------------------------*/
// �O���[�o���萔 ----------------------------------------------------
#if 0
const fx32	dummy_hitcheck_data[] = {
	0x0000,0x0000,0x0000,		//r,vup,vdown
};

const fx32	entyu1_hitcheck_data[] = {
	FX32_ONE*1,0x0000,0x0000,		//r,vup,vdown
};

const fx32	entyu2_hitcheck_data[] = {
	FX32_ONE*2,0x0000,0x0000,		//r,vup,vdown
};
#endif
fx32 temp1,temp2;
// ���[�J���ϐ� ----------------------------------------------------

fx32 Min(fx32 n1,fx32 n2)
{
	if(n1 < n2){
		return n1;
	}else{
		return n2;
	}
}

fx32 Max(fx32 n1,fx32 n2)
{
	if(n1 > n2){
		return n1;
	}else{
		return n2;
	}

}

/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : �Ȃ�
 *--------------------------------------------------------------------*/
int  BG3D_CalcHitCheck_CylinderCylinder(HIT_CHECK_ENTYUU* object1,HIT_CHECK_ENTYUU* object2)
{
	fx64 r;
	fx64 x,z;

	r = (object1->radius + object2->radius);
	x = (object2->global.x - object1->global.x);
	z = (object2->global.z - object1->global.z);

	if( (r*r) < (x*x) + (z*z) ){
		return 0;
	}
	return 1;
}

//�����Ƌ��̌�������
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : �Ȃ�
 *--------------------------------------------------------------------*/
int BG3D_CalcHitCheck_SegmentSphere(const VecFx32 *inCoreVec, const fx32 inRadius, const VecFx32 *inStartVec, const VecFx32 *inEndVec)
{
	fx32 distance;
	//���Ɛ�����2�̌�_�����ꍇ�������́A�����Ƌ����ڂ��Ă���ꍇ�A���̒��S�_�Ɛ����̋��������a�ȉ��ɂȂ�
	distance = BG3D_GetPointSegmentDistance(inCoreVec, inStartVec, inEndVec);
	if (  (distance < 0) || (distance > inRadius) ){
		//���Ɛ�����1�̌�_�����ꍇ�A������1�̒[�_�Ƌ��̒��S�_�̋��������a�ȉ��ɂȂ�
		if ( (VEC_Distance(inStartVec, inCoreVec) < inRadius) ){
			return SEG_SPH_HIT_START;	//�n�_�q�b�g
		}
		else if ( (VEC_Distance(inEndVec, inCoreVec) < inRadius) ){
			return SEG_SPH_HIT_END;	//�I�_�q�b�g
		}
		else{
			return NO_HIT;//�q�b�g���ĂȂ�
		}
	}
	return SEG_SPH_HIT_SEG;//�����q�b�g
}

//�O�p�`�̓��O����
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : �Ȃ�
 *--------------------------------------------------------------------*/
BOOL BG3D_CheckTriangleIO(const VecFx32 *inTargetVtx,VecFx32 inVtx1,VecFx32 inVtx2,VecFx32 inVtx3)
{
	VecFx32	vec1,vec2,vec3,vecCross1,vecCross2;
	fx32	dot;
#if 1	
	//vector:1��2
	VEC_Subtract(&inVtx2,&inVtx1,&vec1);
	//vector:1��3
	VEC_Subtract(&inVtx3,&inVtx1,&vec2);
	//Cross
	VEC_CrossProduct(&vec1,&vec2,&vecCross1);

	//�O�ς�0�x�N�g���̂��̂́A�q�b�g���Ȃ������Ƃ݂Ȃ�
	if ( VEC_Mag(&vecCross1)==0 ){
		return FALSE;
	}

	///VEC_Normalize(&vecCross1, &vecCross1);//�O�όv�Z�Ō����ӂꂵ�Ȃ��悤�ɐ��K�����Ă���
#endif
	//vector:Target��1
	VEC_Subtract(&inVtx1,inTargetVtx,&vec1);
	//vector:Target��2
	VEC_Subtract(&inVtx2,inTargetVtx,&vec2);
	//vector:Target��3
	VEC_Subtract(&inVtx3,inTargetVtx,&vec3);
	
	//Cross
	VEC_CrossProduct(&vec1,&vec2,&vecCross2);
	if (VEC_Mag(&vecCross2)!=0/*vecCross2.y!=0*/){			//�O�ς��O�x�N�g���̂Ƃ��́A�ԏ�ɂ���̂ŁA�q�b�g�����Ƃ݂Ȃ�
		///VEC_Normalize(&vecCross2, &vecCross2);
		//Dot
		dot = VEC_DotProduct(&vecCross1,&vecCross2);
		if ( (dot) <= 0.0 ){
			return FALSE;
		}
	}

	//Cross
	VEC_CrossProduct(&vec2,&vec3,&vecCross2);
	if (VEC_Mag(&vecCross2)!=0/*vecCross2.y!=0*/){			//�O�ς��O�x�N�g���̂Ƃ��́A�ԏ�ɂ���̂ŁA�q�b�g�����Ƃ݂Ȃ�
		///VEC_Normalize(&vecCross2, &vecCross2);
		//Dot
		dot = VEC_DotProduct(&vecCross1,&vecCross2);
		if ( (dot) <= 0.0 ){
			return FALSE;
		}
	}

	//Cross
	VEC_CrossProduct(&vec3,&vec1,&vecCross2);
	if (VEC_Mag(&vecCross2)!=0/*vecCross2.y!=0*/){			//�O�ς��O�x�N�g���̂Ƃ��́A�ԏ�ɂ���̂ŁA�q�b�g�����Ƃ݂Ȃ�
		///VEC_Normalize(&vecCross2, &vecCross2);
		//Dot
		dot = VEC_DotProduct(&vecCross1,&vecCross2);
		if ( (dot) <= 0.0 ){
			return FALSE;
		}
	}
	return TRUE;
}

//�����Ɠ_�̋���(�����̊J�n�_���`�A�I�_���a�A�C�ӂ̓_���o�A�o����`�a�ɐ����ɐL�΂��������Ƃ`�a�̌�_���p�Ƃ���)
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : �Ȃ�
 *--------------------------------------------------------------------*/
fx32 BG3D_GetPointSegmentDistance(const VecFx32 *inPoint, const VecFx32 *inStartVec, const VecFx32 *inEndVec)
{
	fx32 distance;
	fx32 t;
	VecFx32 ab_Vec,ap_Vec,pq_Vec,aq_Vec;
	VecFx32 dummy = {0,0,0};
	
	
	//�����̂`�a�x�N�g�����쐬�i�x�N�g���̌��@�j
	VEC_Subtract(inEndVec, inStartVec, &ab_Vec);
	//�`�o�x�N�g���쐬�i�x�N�g���̌��@�j
	VEC_Subtract(inPoint, inStartVec, &ap_Vec);
	//�x�N�g���`�a�A�`�o�̓��ς��}��ϐ��������߁A�������ɂ��邩���ׂ�
	temp1 = VEC_DotProduct( &ab_Vec, &ap_Vec );
	temp2 = FX_Mul(ab_Vec.z, ab_Vec.z);
	
	t = FX_Div( VEC_DotProduct( &ab_Vec, &ap_Vec ), ( FX_Mul(ab_Vec.x, ab_Vec.x) + FX_Mul(ab_Vec.z, ab_Vec.z) ) );

	//�o���牺�낵��������������ɂȂ��Ȃ�q�b�g���Ȃ������Ƃ݂Ȃ�
    if( t < 0 || t > FX32_ONE )
        return -FX32_ONE;

    //�����`�a�ƌ�_�p�̃x�N�g���`�p���쐬�i�x�N�g���������j
	VEC_MultAdd(t , &ab_Vec, &dummy, &aq_Vec);

    //�o�ƌ�_�p�̃x�N�g���o�p���쐬�i�x�N�g���̌��@�j
	VEC_Subtract(&aq_Vec, &ap_Vec, &pq_Vec);

    //�x�N�g���o�p�̃X�J���[������
	distance = VEC_Mag(&pq_Vec);
	return distance;
}

//�����Ɠ_�̋���(�����̊J�n�_���`�A�I�_���a�A�C�ӂ̓_���o�A�o����`�a�ɐ����ɐL�΂��������Ƃ`�a�̌�_���p�Ƃ���)
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : �Ȃ�
 *--------------------------------------------------------------------*/
fx32 BG3D_GetPointSegmentDistance2(const VecFx32 *inPoint, const VecFx32 *inStartVec, const VecFx32 *inEndVec)
{
	fx32 distance;
	fx32 t;
	VecFx32 ab_Vec,ap_Vec,pq_Vec,aq_Vec;
	VecFx32 dummy = {0,0,0};
	
	
	//�����̂`�a�x�N�g�����쐬�i�x�N�g���̌��@�j
	VEC_Subtract(inEndVec, inStartVec, &ab_Vec);
	//�`�o�x�N�g���쐬�i�x�N�g���̌��@�j
	VEC_Subtract(inPoint, inStartVec, &ap_Vec);
	//�x�N�g���`�a�A�`�o�̓��ς��}��ϐ��������߁A�������ɂ��邩���ׂ�
	temp1 = VEC_DotProduct( &ab_Vec, &ap_Vec );
	temp2 = FX_Mul(ab_Vec.z, ab_Vec.z);
	
	t = FX_Div( VEC_DotProduct( &ab_Vec, &ap_Vec ), ( FX_Mul(ab_Vec.x, ab_Vec.x) + FX_Mul(ab_Vec.z, ab_Vec.z) ) );
/**
	//�o���牺�낵��������������ɂȂ��Ȃ�q�b�g���Ȃ������Ƃ݂Ȃ�
    if( t < 0 || t > FX32_ONE )
        return -FX32_ONE;
*/
    //�����`�a�ƌ�_�p�̃x�N�g���`�p���쐬�i�x�N�g���������j
	VEC_MultAdd(t , &ab_Vec, &dummy, &aq_Vec);

    //�o�ƌ�_�p�̃x�N�g���o�p���쐬�i�x�N�g���̌��@�j
	VEC_Subtract(&aq_Vec, &ap_Vec, &pq_Vec);

    //�x�N�g���o�p�̃X�J���[������
	distance = VEC_Mag(&pq_Vec);
	return distance;
}

//�_�ƕ��ʂ̋��� �@���x�N�g���m�A���ʂ̕������̂c�l�A�ΏۂɂȂ�_�o
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : �Ȃ�
 *--------------------------------------------------------------------*/
fx32 BG3D_GetPointPlaneDistance(const VecFx32 *inPoint, const VecFx32 *inNrm,const fx32 inD )
{
	fx32 dist;
	dist = FX_Mul(inNrm->x,inPoint->x)+FX_Mul(inNrm->y,inPoint->y)+FX_Mul(inNrm->z,inPoint->z)+inD;
	if (dist<0){
		dist *= (-1);
	}
	return dist;
}

#if 0
//���ʂւ̃x�N�g���ђʔ���
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : �Ȃ�
 *--------------------------------------------------------------------*/
//void CheckVectorHitToPlane(VecFx32 inNrmVec, inFx32 inD, inTeget)
#endif
#if 0
//���ʂƒ����̌������W�擾
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : �Ȃ�
 *--------------------------------------------------------------------*/
VecFx32	GetCrossPointPlaneToLine(VecFx32 inNrmVec, inFx32 inD, VecFx32 inDirVec, VecFx32 inStartVec)
{
	fx32 t;
	fx32	nrm_start;
	fx32 nrm_dir;
	VecFx32	dst_vec;

	nrm_start = VEC_DotProduct(&inNrmVec, &inStartVec);
	nrm_dir = VEC_DotProduct(&inNrmVec, &inDirVec);

	t = FX_Div( inD + nrm_start, nrm_dir);

	VEC_MultAdd(t, inDirVec, inStartVec, &des_vec);
	return dst_vec;
}
#endif

//���ʂƐ����̌������W�擾
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : �Ȃ�
 *--------------------------------------------------------------------*/
BOOL GetCrossPointPlaneToSegment(const VecFx32 *inNrmVec, const fx32 inD, 
								const VecFx32 *inStartVec, const VecFx32 *inEndVec,
								VecFx32 *outVec)
{
	fx32 t;
	fx32 nrm_start;
	fx32 nrm_dir;
	VecFx32 dirVec;

	//�����x�N�g���쐬(���K�����Ȃ�)
	VEC_Subtract(inEndVec,inStartVec,&dirVec);

	//�����J�n�n�_�ƕ��ʂ̖@���x�N�g���̓��ς��v�Z
	nrm_start = VEC_DotProduct(inNrmVec, inStartVec);
	//�����̕����x�N�g���ƕ��ʂ̖@���x�N�g���̓��ς��v�Z
	nrm_dir = VEC_DotProduct(inNrmVec, &dirVec);

	//�����̕����x�N�g���ƕ��ʂ̖@���x�N�g���̓��ς�0�̏ꍇ�A�����͖ʂɑ΂��ĕ��s�Ȃ̂ŁA��_�͖����Ƃ���
	if (nrm_dir == 0){
		return FALSE;
	}

	//�}��ϐ����Z�o
	t = -( FX_Div( inD + nrm_start, nrm_dir) );

	//�����ƕ��ʂ��������Ă邩��}��ϐ��̒l���画�f
	if (0<=t && t<=1*FX32_ONE){
		VEC_MultAdd(t, &dirVec, inStartVec, outVec);
		return TRUE;		//��_����
	}else{
		return FALSE;		//��_�Ȃ�
	}
}



//---------------------------------------------------------------------------------------------------------
/**
 *	�i�s�����x�N�g���C��(�ǂ���ړ�)
 *	@param	*inMoveVec		�ړ��ʁi�ړ������j
 *	@param	*ioDirVec		�C����ړ�����
 *
 *	@retval	VecFx32			�C����ړ��ʁi�ړ������j
*/
//---------------------------------------------------------------------------------------------------------
VecFx32 ChangeDirForWall(const VecFx32* inMoveVec, const VecFx32 *inDirVec)
{
	fx32 len;
	VecFx32 dir_vec,dir_vec1,dir_vec2;
	VecFx32 dumy_vec = {0,0,0};

	dir_vec1 = *inDirVec;
	dir_vec2 = *inDirVec;
	dir_vec2.x = dir_vec2.x*(-1);
	dir_vec2.z = dir_vec2.z*(-1);

	dir_vec1.y = 0x0000;
	dir_vec2.y = 0x0000;

	if ( VEC_DotProduct(&dir_vec1, inMoveVec)>0 ){
		dir_vec = dir_vec1;
	}else if( VEC_DotProduct(&dir_vec2, inMoveVec)>0 ){
		dir_vec = dir_vec2;
	}else{
		dir_vec = dumy_vec;
	}
	VEC_Normalize(&dir_vec, &dir_vec);
	len = VEC_Mag(inMoveVec);
	//�΂߂̏Փˉ���ړ��ł����Ă��A���̈ړ��ʂ͒ʏ�̏c���ړ������Ɠ����ɂ��Ă���(�{���͂��̕����x�N�g�����ˉe�����ړ�����)
	VEC_MultAdd(len,&dir_vec,&dumy_vec,&dir_vec);

	return dir_vec;
}

//---------------------------------------------------------------------------------------------------------
/**
 *	�����x�N�g�������]�p���v�Z�i�y�w���ʑΉ��j
 *	@param	*inVec1		������x�N�g��
 *	@param	*inVec2		�w������x�N�g��
 *
 *	@retval	rad			��]�p
*/
//---------------------------------------------------------------------------------------------------------
fx32 GetRad(const VecFx32 *inVec1, const VecFx32 *inVec2 )
{
	VecFx32 vec1,vec2;
	fx32 sin,cos;
	fx32 rad;
	VEC_Normalize(inVec1, &vec1);
	VEC_Normalize(inVec2, &vec2);
	//���ς��g���ăR�T�C�������߂�
	//cos = VEC_DotProduct(&vec1, &vec2);
	cos = FX_Mul(vec1.z, vec2.z) + FX_Mul(vec1.x, vec2.x); 
	//�O�ς��g���ăT�C�������߂�
	sin = FX_Mul(vec1.z, vec2.x) - FX_Mul(vec1.x, vec2.z);
	//XZ���ʏ�ł̌v�Z�Ȃ̂Ŏ��v��肪�������ƂȂ�i�����v���ɂ��邽�߁A�T�C���̌������t�ɂ���j
	///sin = FX_Mul(sin, -FX32_ONE);
	if (cos == 0){//�A�[�N�R�T�C�����g���Ȃ��ꍇ
		if (sin > 0){
			rad = 0x4000;
		}else{
			rad = 0xc000;
		}
	}else{
		//�A�[�N�^���W�F���g���g���Ċp�x�����߂�
		rad = FX_Atan2Idx(sin, cos);
	}
	return rad;
}

static void GetRST(const VecFx32 *inBoxSize, const VecFx32 *inBoxRot, VecFx32 *outR, VecFx32 *outS, VecFx32 *outT)
{
	MtxFx33 box_rot;

	VecFx32_to_MtxFx33(&box_rot,(VecFx32*)inBoxRot);
	//���A���A���̒P�ʃx�N�g�����ꂼ��ɁA�{�b�N�X�̉�]�s��������āA�q�r�s�����߂�
	{
		VecFx32 x = {FX32_ONE, 0, 0};
		VecFx32 y = {0, FX32_ONE, 0};
		VecFx32 z = {0, 0, FX32_ONE};
		
		MTX_MultVec33(&x, &box_rot, outR);
		MTX_MultVec33(&y, &box_rot, outS);
		MTX_MultVec33(&z, &box_rot, outT);
	}
	{
		VecFx32 dummy = {0, 0, 0};
		VEC_MultAdd(inBoxSize->x,outR,&dummy,outR);
		VEC_MultAdd(inBoxSize->y,outS,&dummy,outS);
		VEC_MultAdd(inBoxSize->z,outT,&dummy,outT);
	}
}

//---------------------------------------------------------------------------------------------------------
/**
 *	���ʂƃ{�b�N�X�̏Փ˔���
 *	���ʂƃ{�b�N�X�̎������a�̋��������ɁA�Փ˂����o����
 *	�K�v�f�[�^�F�{�b�N�X�̒��S���W
 *				�{�b�N�X�̕��A�����A���s��
 *				�{�b�N�X�̉�]�s��
 *				���ʂ̖@���x�N�g��
 *				���ʂ̕������ɕK�v�Ȃc�l
 *
 *	@param	*inBoxCore
 *	@param  *inBoxSize
 *	@param	*inBoxRot 
 *	@param	*inNrm
 *	@param	inD
 *
 *	@retval	BOOL
*/
//---------------------------------------------------------------------------------------------------------
BOOL HitCheckPlaneToBox(const VecFx32 *inBoxCore, 
						const VecFx32 *inBoxSize, 
						const VecFx32 *inBoxRot, 
						const VecFx32 *inNrm,
						const fx32 inD )
{
	VecFx32 vecR,vecS,vecT;
	fx32 n_s,n_r,n_t;
	fx32 radius,dist;
	
	GetRST(inBoxSize, inBoxRot, &vecR, &vecS, &vecT);
	
	//�q�r�s�A���ʂ̖@���x�N�g����p���āA�������a�����߂�
	n_r = VEC_DotProduct(inNrm,&vecR);
	n_s = VEC_DotProduct(inNrm,&vecS);
	n_t = VEC_DotProduct(inNrm,&vecT);
	if (n_r < 0){
		n_r *=(-1) ;
	}
	if (n_s < 0){
		n_s *=(-1) ;
	}
	if (n_t < 0){
		n_t *=(-1) ;
	}
	radius = (n_r + n_s + n_t) / 2;	//�������a
	
	//���ʂƁA�{�b�N�X���S�Ƃ̋��������߂�
	dist = BG3D_GetPointPlaneDistance(inBoxCore, inNrm, inD );
	//���߂��������������a�����Ȃ�A�Փ˂��Ă���
	if (radius > dist){
		return TRUE;
	}
	
	return FALSE;
}

//
//
//
//---------------------------------------------------------------------------------------------------------
/**
 *	���ʂƃ{�b�N�X�̏Փ˔���
 *	���ʂƃ{�b�N�X�̎������a�̋��������ɁA�Փ˂����o����
 *	�K�v�f�[�^�F�{�b�N�X�̒��S���W
 *				�{�b�N�X�̕��A�����A���s��(RST)
 *				���ʂ̖@���x�N�g��
 *				���ʂ̕������ɕK�v�Ȃc�u
 *
 *	@param	*inBoxCore
 *	@param  *inBoxSize
 *	@param	*inBoxRot 
 *	@param	*inNrm
 *	@param	inD
 *
 *	@retval	BOOL
*/
//---------------------------------------------------------------------------------------------------------

BOOL HitCheckPlaneToBox2(const VecFx32 *inBoxCore, 
						const VecFx32 *inVecR,
						const VecFx32 *inVecS,
						const VecFx32 *inVecT,
						const VecFx32 *inNrm,
						const fx32 inD )
{
	fx32 n_s,n_r,n_t;
	fx32 radius,dist;

	//�q�r�s�A���ʂ̖@���x�N�g����p���āA�������a�����߂�
	n_r = VEC_DotProduct(inNrm,inVecR);
	n_s = VEC_DotProduct(inNrm,inVecS);
	n_t = VEC_DotProduct(inNrm,inVecT);

	if (n_r < 0){
		n_r *=(-1) ;
	}
	if (n_s < 0){
		n_s *=(-1) ;
	}
	if (n_t < 0){
		n_t *=(-1) ;
	}
	radius = (n_r + n_s + n_t) / 2;//�������a
	
	//���ʂƁA�{�b�N�X���S�Ƃ̋��������߂�
	dist = BG3D_GetPointPlaneDistance(inBoxCore, inNrm, inD );
	//���߂��������������a�����Ȃ�A�Փ˂��Ă���
	if (radius > dist){
		return TRUE;
	}
	
	return FALSE;
}

//�l�̐����𔻒肷��֐�
static int sgn(const fx32 inVal)
{
	if (inVal>=0){
		return 1;
	}else{
		return -1;
	}
}

//---------------------------------------------------------------------------------------------------------
/**
 *	���ʂƃ{�b�N�X�̌�_
 *	���ʂƃ{�b�N�X���Փ˂����ꍇ���̌�_�����߂�
 *	�ő�ŁA������4�_�ŏՓ˂���̂ŁA�i�[�̈�́A��ɁA4�p�ӂ���悤�ɂ���
 *	�K�v�f�[�^�F�{�b�N�X�̒��S���W
 *				�{�b�N�X�̕��A�����A���s��
 *				�{�b�N�X�̉�]�s��
 *				���ʂ̖@���x�N�g��
 *				���ʂ̕������ɕK�v�Ȃc�u
 *
 *	@param	*inBoxCore
 *	@param  *inBoxSize
 *	@param	*inBoxRot 
 *	@param	*inNrm
 *
 *	@retval	BOOL
*/
//---------------------------------------------------------------------------------------------------------
int GetHitPointPlaneToBox(const VecFx32 *inBoxCore, 
						const VecFx32 *inBoxSize, 
						const VecFx32 *inBoxRot, 
						const VecFx32 *inNrm,
						VecFx32 *outPointList)
{
	VecFx32 vecR,vecS,vecT;	//RST
	fx32 n_s,n_r,n_t;	//�@���Ƃq�r�s���ꂼ��̓���
	VecFx32 *vec1[2];	//���ʂɑ΂��āA���s��RST���i�[����z��
	VecFx32 *vec2[2];	//���ʂɑ΂��āA�񕽍s��RST���i�[����z��
	fx32 * dot_prod[2];	//���ʂɑ΂��āA�񕽍s��RST�Ɩ@���x�N�g���Ƃ̓��ς��i�[����z��

	int hit_vtx_num = 0;	//�Փ˒��_�̐�
	
	int flat_num = 0;	//���ʂɑ΂��āA���s��RST�̐�
	int non_flat_num = 0;	//���ʂɑ΂��āA�񕽍s��RST�̐�
	
	//�q�r�s�����߂�
	GetRST(inBoxSize, inBoxRot, &vecR, &vecS, &vecT);
	//�q�r�s�A�@���x�N�g���̓��ς��v�Z
	n_r = VEC_DotProduct(inNrm,&vecR);
	n_s = VEC_DotProduct(inNrm,&vecS);
	n_t = VEC_DotProduct(inNrm,&vecT);
	
	if (n_r == 0){
		vec1[flat_num++] = &vecR;
	}else{
		dot_prod[non_flat_num] = &n_r;
		vec2[non_flat_num++] = &vecR;
	}
	if (n_s == 0){
		vec1[flat_num++] = &vecS;
	}else{
		dot_prod[non_flat_num] = &n_s;
		vec2[non_flat_num++] = &vecS;
	}
	if (n_t == 0){
		vec1[flat_num++] = &vecT;
	}else{
		dot_prod[non_flat_num] = &n_t;
		vec2[non_flat_num++] = &vecT;
	}

	{
		VecFx32 dummy = {0,0,0};
		VecFx32 temp1,temp2,temp3;
		if (flat_num == 0 ){	//���ʂ�1���_�ŏՓ˂���ꍇ
			//���ʂƈ�ԋ߂��ʒu�ɂ��钸�_���Z�o
			VEC_MultAdd((fx32)(sgn(n_r)*FX32_ONE),&vecR,&dummy,&temp1);
			VEC_MultAdd((fx32)(sgn(n_s)*FX32_ONE),&vecS,&dummy,&temp2);
			VEC_MultAdd((fx32)(sgn(n_t)*FX32_ONE),&vecT,&dummy,&temp3);
			VEC_Add( &temp1,&temp2,&temp1);
			VEC_Add( &temp1,&temp3,&temp1);
			VEC_MultAdd(FX32_ONE/2,&temp1,&dummy,&temp1);
			VEC_Subtract( inBoxCore,&temp1,&outPointList[0]);
			hit_vtx_num = 1;
		}else if (flat_num == 1){	//���ʂ�2���_�ŏՓ˂���ꍇ
			VEC_MultAdd(sgn(*dot_prod[0])*FX32_ONE,vec2[0],&dummy,&temp1);
			VEC_MultAdd(sgn(*dot_prod[1])*FX32_ONE,vec2[1],&dummy,&temp2);
			VEC_Add( &temp1,&temp2,&temp1);
			temp3 = *vec1[0];
			
			VEC_Add( &temp1,&temp3,&outPointList[0]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[0],&dummy,&outPointList[0]);
			VEC_Subtract( inBoxCore,&outPointList[0],&outPointList[0]);
			
			VEC_Subtract( &temp1,&temp3,&outPointList[1]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[1],&dummy,&outPointList[1]);
			VEC_Subtract( inBoxCore,&outPointList[1],&outPointList[1]);
			hit_vtx_num = 2;
		}else{	//���ʂ�4���_�ŏՓ˂���ꍇ
			VEC_MultAdd(sgn(*dot_prod[0])*FX32_ONE,vec2[0],&dummy,&temp1);
			temp2 = *vec1[0];
			temp3 = *vec1[1];
			
			//4���_�̎Z�o
			//4���_�Ɩʂ̏Փ˔���ŁA�g�p�\�ɂ��邽�߂ɁA
			//�i�[���X�g�̘A������2�̒��_���A�ׂ荇���悤�ȏ����Ŋi�[����
			//���L�̏����Ɋi�[����΁A�������ۏႳ���	
			VEC_Add( &temp1,&temp2,&outPointList[0]);
			VEC_Add( &outPointList[0],&temp3,&outPointList[0]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[0],&dummy,&outPointList[0]);
			VEC_Subtract( inBoxCore,&outPointList[0],&outPointList[0]);
			
			VEC_Subtract( &temp1,&temp2,&outPointList[1]);
			VEC_Add( &outPointList[1],&temp3,&outPointList[1]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[1],&dummy,&outPointList[1]);
			VEC_Subtract( inBoxCore,&outPointList[1],&outPointList[1]);

			VEC_Subtract( &temp1,&temp2,&outPointList[2]);
			VEC_Subtract( &outPointList[2],&temp3,&outPointList[2]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[2],&dummy,&outPointList[2]);
			VEC_Subtract( inBoxCore,&outPointList[2],&outPointList[2]);

			VEC_Add( &temp1,&temp2,&outPointList[3]);
			VEC_Subtract( &outPointList[3],&temp3,&outPointList[3]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[3],&dummy,&outPointList[3]);
			VEC_Subtract( inBoxCore,&outPointList[3],&outPointList[3]);
			hit_vtx_num = 4;
		}
	}
	return hit_vtx_num;
}

//---------------------------------------------------------------------------------------------------------
/**
 *	���ʂƃ{�b�N�X�̌�_
 *	���ʂƃ{�b�N�X���Փ˂����ꍇ���̌�_�����߂�
 *	�ő�ŁA������4�_�ŏՓ˂���̂ŁA�i�[�̈�́A��ɁA4�p�ӂ���悤�ɂ���
 *	�K�v�f�[�^�F�{�b�N�X�̒��S���W
 *				�{�b�N�X�̕��A�����A���s��
 *				�{�b�N�X�̉�]�s��
 *				���ʂ̖@���x�N�g��
 *				���ʂ̕������ɕK�v�Ȃc�u
 *
 *	@param	*inBoxCore
 *	@param  *inBoxSize
 *	@param	*inBoxRot 
 *	@param	*inNrm
 *
 *	@retval	BOOL
*/
//---------------------------------------------------------------------------------------------------------
int GetHitPointPlaneToBox2(const VecFx32 *inBoxCore, 
						const VecFx32 *inVecR,
						const VecFx32 *inVecS,
						const VecFx32 *inVecT,
						const VecFx32 *inNrm,
						VecFx32 *outPointList)
{
	fx32 n_s,n_r,n_t;	//�@���Ƃq�r�s���ꂼ��̓���
	const VecFx32 *vec1[2];	//���ʂɑ΂��āA���s��RST���i�[����z��
	const VecFx32 *vec2[2];	//���ʂɑ΂��āA�񕽍s��RST���i�[����z��
	fx32 * dot_prod[2];	//���ʂɑ΂��āA�񕽍s��RST�Ɩ@���x�N�g���Ƃ̓��ς��i�[����z��

	int hit_vtx_num = 0;	//�Փ˒��_�̐�
	
	int flat_num = 0;	//���ʂɑ΂��āA���s��RST�̐�
	int non_flat_num = 0;	//���ʂɑ΂��āA�񕽍s��RST�̐�
	
	//�q�r�s�A�@���x�N�g���̓��ς��v�Z
	n_r = VEC_DotProduct(inNrm,inVecR);
	n_s = VEC_DotProduct(inNrm,inVecS);
	n_t = VEC_DotProduct(inNrm,inVecT);
	if (n_r == 0){
		vec1[flat_num++] = inVecR;
	}else{
		dot_prod[non_flat_num] = &n_r;
		vec2[non_flat_num++] = inVecR;
	}
	if (n_s == 0){
		vec1[flat_num++] = inVecS;
	}else{
		dot_prod[non_flat_num] = &n_s;
		vec2[non_flat_num++] = inVecS;
	}
	if (n_t == 0){
		vec1[flat_num++] = inVecT;
	}else{
		dot_prod[non_flat_num] = &n_t;
		vec2[non_flat_num++] = inVecT;
	}

	{
		VecFx32 dummy = {0,0,0};
		VecFx32 temp1,temp2,temp3;
		if (flat_num == 0 ){	//���ʂ�1���_�ŏՓ˂���ꍇ
			//���ʂƈ�ԋ߂��ʒu�ɂ��钸�_���Z�o
			VEC_MultAdd((fx32)(sgn(n_r)*FX32_ONE),inVecR,&dummy,&temp1);
			VEC_MultAdd((fx32)(sgn(n_s)*FX32_ONE),inVecS,&dummy,&temp2);
			VEC_MultAdd((fx32)(sgn(n_t)*FX32_ONE),inVecT,&dummy,&temp3);
			VEC_Add( &temp1,&temp2,&temp1);
			VEC_Add( &temp1,&temp3,&temp1);
			VEC_MultAdd(FX32_ONE/2,&temp1,&dummy,&temp1);
			VEC_Subtract( inBoxCore,&temp1,&outPointList[0]);
			hit_vtx_num = 1;
		}else if (flat_num == 1){	//���ʂ�2���_�ŏՓ˂���ꍇ
			VEC_MultAdd(sgn(*dot_prod[0])*FX32_ONE,vec2[0],&dummy,&temp1);
			VEC_MultAdd(sgn(*dot_prod[1])*FX32_ONE,vec2[1],&dummy,&temp2);
			VEC_Add( &temp1,&temp2,&temp1);
			temp3 = *vec1[0];
			
			VEC_Add( &temp1,&temp3,&outPointList[0]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[0],&dummy,&outPointList[0]);
			VEC_Subtract( inBoxCore,&outPointList[0],&outPointList[0]);
			
			VEC_Subtract( &temp1,&temp3,&outPointList[1]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[1],&dummy,&outPointList[1]);
			VEC_Subtract( inBoxCore,&outPointList[1],&outPointList[1]);
			hit_vtx_num = 2;
		}else{	//���ʂ�4���_�ŏՓ˂���ꍇ
			VEC_MultAdd(sgn(*dot_prod[0])*FX32_ONE,vec2[0],&dummy,&temp1);
			temp2 = *vec1[0];
			temp3 = *vec1[1];
			
			//4���_�̎Z�o
			//4���_�Ɩʂ̏Փ˔���ŁA�g�p�\�ɂ��邽�߂ɁA
			//�i�[���X�g�̘A������2�̒��_���A�ׂ荇���悤�ȏ����Ŋi�[����
			//���L�̏����Ɋi�[����΁A�������ۏႳ���
			VEC_Add( &temp1,&temp2,&outPointList[0]);
			VEC_Add( &outPointList[0],&temp3,&outPointList[0]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[0],&dummy,&outPointList[0]);
			VEC_Subtract( inBoxCore,&outPointList[0],&outPointList[0]);
			
			VEC_Subtract( &temp1,&temp2,&outPointList[1]);
			VEC_Add( &outPointList[1],&temp3,&outPointList[1]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[1],&dummy,&outPointList[1]);
			VEC_Subtract( inBoxCore,&outPointList[1],&outPointList[1]);

			VEC_Subtract( &temp1,&temp2,&outPointList[2]);
			VEC_Subtract( &outPointList[2],&temp3,&outPointList[2]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[2],&dummy,&outPointList[2]);
			VEC_Subtract( inBoxCore,&outPointList[2],&outPointList[2]);

			VEC_Add( &temp1,&temp2,&outPointList[3]);
			VEC_Subtract( &outPointList[3],&temp3,&outPointList[3]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[3],&dummy,&outPointList[3]);
			VEC_Subtract( inBoxCore,&outPointList[3],&outPointList[3]);
			hit_vtx_num = 4;
		}
	}
	return hit_vtx_num;
}

//1���_�����_��ʂ�A�����s�ȃ{�b�N�X�̕��ʂ̖@���x�N�g����D�l���C���f�b�N�X�Ŏ擾
static void GetBoxPlaneByIdx(const u8 inBoxPlaneIdx, const VecFx32 *inBoxSize, VecFx32 *outNrmVec, fx32 *outD)
{
	*outNrmVec = BoxNrm[inBoxPlaneIdx];
	if ((inBoxPlaneIdx == 0)||(inBoxPlaneIdx == 3)){
		*outD = FX_Mul(BoxDBase[inBoxPlaneIdx],inBoxSize->x);
	}else if((inBoxPlaneIdx == 1)||(inBoxPlaneIdx == 4)){
		*outD = FX_Mul(BoxDBase[inBoxPlaneIdx],inBoxSize->y);
	}else{//((inBoxPlaneIdx == 2)||(inBoxPlaneIdx == 5))
		*outD = FX_Mul(BoxDBase[inBoxPlaneIdx],inBoxSize->z);
	}
}

//1���_�����_��ʂ�A�����s�ȃ{�b�N�X���쐬
static void MakeBoxData(VecFx32 * outNrm, fx32 * outD,VecFx32 *outVtx, const VecFx32 *inSize)
{
	u8 i;
	//�Փˌ��o�Ɏg���{�b�N�X���\������@���x�N�g���ƕ��ʂ�D�l���擾
	for(i=0;i<6;i++){
		GetBoxPlaneByIdx(i, inSize, &outNrm[i], &outD[i]);
	}
	
	//�{�b�N�X�̒��_
	VEC_Set(&outVtx[0],0		,0		  ,0		);
	VEC_Set(&outVtx[1],inSize->x,0		  ,0		);
	VEC_Set(&outVtx[2],inSize->x,inSize->y,0		);
	VEC_Set(&outVtx[3],0		,inSize->y,0		);
	VEC_Set(&outVtx[4],0		,0		  ,inSize->z);
	VEC_Set(&outVtx[5],inSize->x,0		  ,inSize->z);
	VEC_Set(&outVtx[6],inSize->x,inSize->y,inSize->z);
	VEC_Set(&outVtx[7],0		,inSize->y,inSize->z);
}

//1���_�����_��ʂ�A�����s�ȃ{�b�N�X�̕��ʂ̍��W�n���C���f�b�N�X�Ŏ擾
static u8 GetBoxPlaneFlgByIdx(const u8 inBoxPlaneIdx)
{
	if ((inBoxPlaneIdx == 0)||(inBoxPlaneIdx==3)){
		return YZ_PLANE;
	}else if ((inBoxPlaneIdx == 1)||(inBoxPlaneIdx==4)){
		return ZX_PLANE;
	}else{//(inBoxPlaneIdx == 2)||(inBoxPlaneIdx==5)
		return XY_PLANE;
	}
}


//�{�b�N�X���ʂƒ����̌�������
//���ʂ��\������4���_�A���肷������̗��[�_�A���ʂ��\������Ă�����W�n���ʃt���O
static BOOL CheckHitPlaneToLineForBox(const VecFx32 *inPlaneVtxs, const VecFx32 *inSegPoints, const u8 inFlg)
{
	//���ʂ�2���_�ŏՓ˂����ꍇ
	//�Փ˂����������ʂƌ������邩�𔻒�
	//�Փ˂����ʂ͖@���x�N�g���C���f�b�N�X���环�ʂ���
	VecFx32 vtx[4];
	VecFx32 segPoint[2];

	switch((PLANE_TYPE)inFlg){
	case XY_PLANE:
		//�������ʂōl����
		//�֐��͂������ʗp�Ȃ̂ŁA�������A�������ɕϊ�
		vtx[0].z = inPlaneVtxs[0].x;vtx[0].x = inPlaneVtxs[0].y;
		vtx[1].z = inPlaneVtxs[1].x;vtx[1].x = inPlaneVtxs[1].y;
		vtx[2].z = inPlaneVtxs[2].x;vtx[2].x = inPlaneVtxs[2].y;
		vtx[3].z = inPlaneVtxs[3].x;vtx[3].x = inPlaneVtxs[3].y;
		segPoint[0].z = inSegPoints[0].x;segPoint[0].x = inSegPoints[0].y;
		segPoint[1].z = inSegPoints[1].x;segPoint[1].x = inSegPoints[1].y;
		break;
	case YZ_PLANE:
		//�������ʂōl����
		//�֐��͂������ʗp�Ȃ̂ŁA�������A�������ɕϊ�
		vtx[0].z = inPlaneVtxs[0].y;vtx[0].x = inPlaneVtxs[0].z;
		vtx[1].z = inPlaneVtxs[1].y;vtx[1].x = inPlaneVtxs[1].z;
		vtx[2].z = inPlaneVtxs[2].y;vtx[2].x = inPlaneVtxs[2].z;
		vtx[3].z = inPlaneVtxs[3].y;vtx[3].x = inPlaneVtxs[3].z;
		segPoint[0].z = inSegPoints[0].y;segPoint[0].x = inSegPoints[0].z;
		segPoint[1].z = inSegPoints[1].y;segPoint[1].x = inSegPoints[1].z;
		break;
	case ZX_PLANE:
		//�������ʂōl����
		//�֐��͂������ʗp�Ȃ̂ŁA�ϊ��͂Ȃ�
		vtx[0].z = inPlaneVtxs[0].z;vtx[0].x = inPlaneVtxs[0].x;
		vtx[1].z = inPlaneVtxs[1].z;vtx[1].x = inPlaneVtxs[1].x;
		vtx[2].z = inPlaneVtxs[2].z;vtx[2].x = inPlaneVtxs[2].x;
		vtx[3].z = inPlaneVtxs[3].z;vtx[3].x = inPlaneVtxs[3].x;
		segPoint[0].z = inSegPoints[0].z;segPoint[0].x = inSegPoints[0].x;
		segPoint[1].z = inSegPoints[1].z;segPoint[1].x = inSegPoints[1].x;
		break;
	}
		
	//����
	if ( CheckHitPlaneToSegment2D( &vtx[0],&vtx[1],&vtx[2],&vtx[3],
						&segPoint[0],&segPoint[1] ) == TRUE ){
		OS_Printf("line_hit_OK!!\n");
		return TRUE;
	}
	return FALSE;

}

////////////////////////////////////////////////////////////////////////////////////////
//�{�b�N�X���m�̏Փ˔���
//�Е��̃{�b�N�X�i�Փ˂���鑤�j�����ɐ����ɂȂ�悤�ɉ�]���邽�߂̉�]�s����쐬����
//���s�ړ��s��쐬
//�Փ˂��鑤�̂q�r�s�A���S���W����]�s��Ɗ|�����킹��
//�Փ˖ʂ̌����A�ő��3�ʂ܂ł̔���Ō����悤�ɁA�Փ˂����Ȃ��ʂ���������
//�e�ʂɑ΂��ĉ��L�����s
//�ʂƃ{�b�N�X�̏Փ˔���i�q�r�s���o�ςݔŁj
//�q�b�g�����ꍇ�͂����̒��_�ŏՓ˂������ŕ���
//1���_�ՓˁF�Փˍ��W���ʓ����𔻒�
//2���_�ՓˁF�������ʓ��ɂ��邩����
//4���_�ՓˁF�e���_�ɑ΂��āA1���_�Փ˔�������s
//���̎��_�ŏՓ˂��Ă��Ȃ���΁A�{�b�N�X�̗�������ւ��ď�L�����s
//����ł��Փ˂��Ȃ��ꍇ�́A�ӂƕӂ��Փ˂��邩������Ȃ��̂ŁA���̔���Ɉڂ�
static BOOL HitCheckBoxToBoxSub(	const VecFx32 *inBoxCore,
									const VecFx32 *inBoxSize, 
									const VecFx32 *inBoxRot,
									const VecFx32 *inDirVec,
									const VecFx32 *inBoxCore2, 
									const VecFx32 *inBoxSize2, 
									const VecFx32 *inBoxRot2,
									VTX_DATA_FOR_BOXHIT *outVDFB)
{
	int i,j;
	MtxFx43 mat4x3;
	MtxFx33 mat3x3;

	VecFx32 vec_P;
	
	VecFx32 dirVec;
	VecFx32 vecR,vecS,vecT;
	VecFx32 vecNrmR,vecNrmS,vecNrmT;
	VecFx32 vecG;

	VecFx32 core_Q;
	VecFx32 vecR_Q,vecS_Q,vecT_Q;
	VecFx32 vtxList[4];

	VecFx32	Nrm[6];
	fx32 D[6];
	VecFx32 box_vtx[8];

	u8 plane_flg;
	
	int vtxNum = 0;	
	VecFx32 core2 = *inBoxCore2;
	VecFx32 core = *inBoxCore;


	vec_P.x = inBoxSize2->x/2;
	vec_P.y = inBoxSize2->y/2;
	vec_P.z = inBoxSize2->z/2;

	MakeBoxData(Nrm,D,box_vtx,inBoxSize2);
	
	GetRST(inBoxSize, inBoxRot, &vecR_Q, &vecS_Q, &vecT_Q);
	
	//�Е��̃{�b�N�X�i��Փˑ��j�̂q�r�s���e��(�w�x�y)�ɐ����ɂȂ�悤�ɉ�]�A���s�ړ����邽�߂̕ϊ��s����쐬����
	GetRST(inBoxSize2, inBoxRot2, &vecR, &vecS, &vecT);
	VEC_Normalize(&vecR, &vecNrmR);
	VEC_Normalize(&vecS, &vecNrmS);
	VEC_Normalize(&vecT, &vecNrmT);
	
	//���_�ֈړ�������W���Z�o
	{
		VecFx32 dummy={0,0,0};
		VecFx32 temp = {0,0,0};
		VEC_Add(&temp,&vecR,&temp);
		VEC_Add(&temp,&vecS,&temp);
		VEC_Add(&temp,&vecT,&temp);

		VEC_MultAdd(FX32_ONE/2,&temp,&dummy,&temp);

		VEC_Subtract(&core2,&temp,&vecG);
		
	}
	//�s��쐬
	mat4x3._00 = vecNrmR.x;
	mat4x3._10 = vecNrmR.y;
	mat4x3._20 = vecNrmR.z;
	mat4x3._30 = -(VEC_DotProduct(&vecNrmR, &vecG));
	mat4x3._01 = vecNrmS.x;
	mat4x3._11 = vecNrmS.y;
	mat4x3._21 = vecNrmS.z;
	mat4x3._31 = -(VEC_DotProduct(&vecNrmS, &vecG));
	mat4x3._02 = vecNrmT.x;
	mat4x3._12 = vecNrmT.y;
	mat4x3._22 = vecNrmT.z;
	mat4x3._32 = -(VEC_DotProduct(&vecNrmT, &vecG));
	
	mat3x3._00 = vecNrmR.x;
	mat3x3._10 = vecNrmR.y;
	mat3x3._20 = vecNrmR.z;
	mat3x3._01 = vecNrmS.x;
	mat3x3._11 = vecNrmS.y;
	mat3x3._21 = vecNrmS.z;
	mat3x3._02 = vecNrmT.x;
	mat3x3._12 = vecNrmT.y;
	mat3x3._22 = vecNrmT.z;
	
	//�Փˑ��{�b�N�X�̒��S���W�ƁARST�ɕϊ��s���K�p
	//��Փˑ��̕ϊ��́A1���_�����_��ʂ�A�����s�ȃ{�b�N�X���쐬���邱�ƂŁA�ϊ������Ƃ݂Ȃ�
	
	MTX_MultVec43(&core, &mat4x3, &core_Q);
	MTX_MultVec33(&vecR_Q, &mat3x3, &vecR_Q);
	MTX_MultVec33(&vecS_Q, &mat3x3, &vecS_Q);
	MTX_MultVec33(&vecT_Q, &mat3x3, &vecT_Q);
	
	//�Փ˂����Ȃ��ʂ̏���
	//�Փ˂���鑤�̃{�b�N�X�̒��S����Փ˂��鑤�̒��S�ւ̕����x�N�g���ƁA
	//��Փˑ��̊e�ʂ̖@���x�N�g���Ƃ̓��ς����A0�ȉ��̖ʂ͑Ώۂ���͂���
	//�ő��3�ʂƂ̓����蔻��
	//�����x�N�g���̎w�肪�Ȃ��ꍇ(NULL or 0�x�N�g��)��6�ʑS�ĂƔ��肷��
	for(i=0;i<6;i++){
		//�����x�N�g���ɂ��A�Ώۖʔ���
		if ( (inDirVec != NULL)&&( (inDirVec->x != 0)||(inDirVec->y != 0)||(inDirVec->z != 0) ) ){
			MTX_MultVec33(inDirVec, &mat3x3, &dirVec);
			if(VEC_DotProduct(&Nrm[i],&dirVec) >= 0){
				OS_Printf("through");
				continue;
			}
		}
		
		//�Փˑ��̒��S�_����r���ʂɑ΂��A�����ɂ���ꍇ�́A����Ώۂ���͂����Ă悢
		//����]���Ȃ���̏Փ˂����邽�ߏ������͂�������2004/12/20
/**
		if (VEC_DotProduct(&Nrm[i],&core_Q) + D[i] <= 0){
			OS_Printf("continue\n");
			continue;
		}
*/
		//�����̂���]���Ă���Ƃ��́A�ʂ������ɂ���ꍇ�ł��A�˂���̈ʒu�̏Փ˂̂��߂�1���_�f�[�^�͎擾����K�v������
		//�����ŁA�����𒆒f���Ă��܂��ƁA�f�[�^�擾�ł��Ȃ����߁A���̏����͎g���Ȃ�
		//������̏���
		//��Փ˃{�b�N�X�̒��S����Փ˃{�b�N�X�̒��S�ւ̃x�N�g���Ɩʂ̖@���x�N�g���̓��ς����0�A���̏ꍇ��
		//����Ώۂ���͂���
		{
			VEC_Subtract(&core_Q,&vec_P,&dirVec);
			if(VEC_DotProduct(&Nrm[i],&dirVec) <= 0){
				continue;
			}
		}

		//�Փˌ��o
		if ( HitCheckPlaneToBox2(&core_Q,
								&vecR_Q,
								&vecS_Q,
								&vecT_Q,
								&Nrm[i],
								D[i] )){
			vtxNum = GetHitPointPlaneToBox2(&core_Q,
											&vecR_Q,
											&vecS_Q,
											&vecT_Q,
											&Nrm[i],
											vtxList);
			OS_Printf("%d_check\n",i);
			
			plane_flg = GetBoxPlaneFlgByIdx(i);
			
			//�Փ˒��_���ɂ�蕪��
			if (vtxNum == 1){
				//�˂���̈ʒu�̕ӂǂ����̏Փˌ��o�̂��߂ɁA�Փ˒��_���L������
				if (outVDFB != NULL){
					if (outVDFB->Count<2){
						outVDFB->VtxData[outVDFB->Count].Idx = i;
						outVDFB->VtxData[outVDFB->Count].Vtx = vtxList[0];
						outVDFB->Count++;
					}
				}
				//���ʂ�1���_�ŏՓ˂����ꍇ
				//�Փ˂����_���ʓ������𔻒�
				//�Փ˂����ʂ͖@���x�N�g���C���f�b�N�X���环�ʂ���
				OS_Printf("vertex_hit\n");
				if (plane_flg == YZ_PLANE){
					if ( ((0<=vtxList[0].y)&&(vtxList[0].y<=inBoxSize2->y))&&
							((0<=vtxList[0].z)&&(vtxList[0].z<=inBoxSize2->z)) ){
						//�Փ�
						OS_Printf("hit\n");
						return TRUE;
					}
				}else if(plane_flg == ZX_PLANE){
					if ( ((0<=vtxList[0].z)&&(vtxList[0].z<=inBoxSize2->z))&&
							((0<=vtxList[0].x)&&(vtxList[0].x<=inBoxSize2->x)) ){
						//�Փ�
						OS_Printf("hit\n");
						return TRUE;
					}
				}else{//(plane_flg == XY_PLANE)
					if ( ((0<=vtxList[0].x)&&(vtxList[0].x<=inBoxSize2->x))&&
							((0<=vtxList[0].y)&&(vtxList[0].y<=inBoxSize2->y)) ){
						//�Փ�
						OS_Printf("hit\n");
						return TRUE;
					}
				}
			}else{ //((vtxNum == 2)||(vtxNum == 4))
				VecFx32 vtx[4];
				VecFx32 segPoint[2];

				if (i==0){
					//�������ʂōl����
					vtx[0] = box_vtx[6];
					vtx[1] = box_vtx[2];
					vtx[2] = box_vtx[1];
					vtx[3] = box_vtx[5];
				}else if(i==1){
					//�������ʂōl����
					vtx[0] = box_vtx[3];
					vtx[1] = box_vtx[2];
					vtx[2] = box_vtx[6];
					vtx[3] = box_vtx[7];
				}else if(i==2){
					//�������ʂōl����
					vtx[0] = box_vtx[7];
					vtx[1] = box_vtx[6];
					vtx[2] = box_vtx[5];
					vtx[3] = box_vtx[4];
				}else if(i==3){
					//�������ʂōl����
					vtx[0] = box_vtx[7];
					vtx[1] = box_vtx[3];
					vtx[2] = box_vtx[0];
					vtx[3] = box_vtx[4];
				}else if(i==4){
					//�������ʂōl����
					vtx[0] = box_vtx[0];
					vtx[1] = box_vtx[1];
					vtx[2] = box_vtx[5];
					vtx[3] = box_vtx[4];
				}else if(i==5){
					//�������ʂōl����
					vtx[0] = box_vtx[3];
					vtx[1] = box_vtx[2];
					vtx[2] = box_vtx[1];
					vtx[3] = box_vtx[0];
				}

				if (vtxNum == 2){
					//���ʂ�2���_�ŏՓ˂����ꍇ
					//�Փ˂����������ʂƌ������邩�𔻒�
					OS_Printf("segment_hit\n");
					segPoint[0] = vtxList[0];
					segPoint[1] = vtxList[1];
				
					//����
					if ( CheckHitPlaneToLineForBox(vtx, segPoint, plane_flg) == TRUE ){
						return TRUE;
					}
				}else{//(vtxNum == 4)
					//���ʂ�4���_�ŏՓ˂����ꍇ
					//�ʂƏՓ˂���4���_�ō\�������4�ӂ��ꂼ��ɑ΂��A2���_�Փˎ��̔�����s��
					OS_Printf("plane_hit\n");
					for (j=0;j<4;j++){
						if (j<3){
							segPoint[0] = vtxList[j];
							segPoint[1] = vtxList[j+1];
						}else{	//(j == 3)
							segPoint[0] = vtxList[3];
							segPoint[1] = vtxList[1];
						}
						//����
						if ( CheckHitPlaneToLineForBox(vtx, segPoint, plane_flg) == TRUE ){
							return TRUE;
						}
					}//end for
				}//end if (vtxNum == 2)
			}//end if (vtxNum == 1)
		}//end if (HitCheckPlaneToBox2)
	}//end for
	OS_Printf("change\n");
	return FALSE;	//�Փ˂��Ȃ�
}

//�{�b�N�X�ƃ{�b�N�X�̂��ꂼ��̕ӂ��˂���̈ʒu�ɂ���ꍇ�̏Փˌ��o
static BOOL HitCheckBoxSegToSegNoParallel(VTX_DATA_FOR_BOXHIT *inData, const VecFx32 *inBoxSize)
{
	VecFx32 nrm;
	fx32 d;
	VecFx32 crossPoint;
	u8 flg;
//OS_Printf("HItCount = %d\n",inData->Count);
	if (inData->Count <= 1){
		return FALSE;
	}else if (inData->Count == 2){
		OS_Printf("SegToSeg2Hit\n");
		OS_Printf("idx=%d,%d\n",inData->VtxData[0].Idx,inData->VtxData[1].Idx);
		GetBoxPlaneByIdx(inData->VtxData[0].Idx, inBoxSize, &nrm, &d);

		if ( GetCrossPointPlaneToSegment(&nrm, d, &inData->VtxData[0].Vtx, &inData->VtxData[1].Vtx, &crossPoint)==TRUE){
			//�擾���W���ʓ��ɂ��邩�𔻒�
			//�{�b�N�X�C���f�b�N�X��n���Ăǂ̖ʂŔ��肷�邩������
			flg = GetBoxPlaneFlgByIdx(inData->VtxData[0].Idx);
			if (flg == YZ_PLANE){
				if ( ((0<=crossPoint.y)&&(crossPoint.y<=inBoxSize->y))&&
						((0<=crossPoint.z)&&(crossPoint.z<=inBoxSize->z)) ){
					//�Փ�
					OS_Printf("hit_SegToSeg\n");
					return TRUE;
				}
			}else if (flg == ZX_PLANE){
				if ( ((0<=crossPoint.z)&&(crossPoint.z<=inBoxSize->z))&&
						((0<=crossPoint.x)&&(crossPoint.x<=inBoxSize->x)) ){
					//�Փ�
					OS_Printf("hit_SegToSeg\n");
					return TRUE;
				}
			}else{
				if ( ((0<=crossPoint.x)&&(crossPoint.x<=inBoxSize->x))&&
						((0<=crossPoint.y)&&(crossPoint.y<=inBoxSize->y)) ){
					//�Փ�
					OS_Printf("hit_SegToSeg\n");
					return TRUE;
				}
			}
		}
	}else { //(inData->count >= 3)
		OS_Printf("SegToSeg3PointOver:%dHit\n",inData->Count);
		SDK_MINMAX_ASSERT(inData->Count, 0, 2);
		//�����3��s��
		/*for(i=0;i<3;i++){
			GetBoxPlaneByIdx(inData->VtxData[i].Idx, &nrm, &d);
			if (i<2){
				GetCrossPontPlaneToSegment(&nrm, &d, &inData->VtxData[i]Vex, &inData->VtxData[i+1].Vtx, &crossPoint);
			}else{ //(i==2)
				GetCrossPontPlaneToSegment(&nrm, &d, &inData->VtxData[2]Vex, &inData->VtxData[0].Vtx, &crossPoint);
			}
			//�擾���W���ʓ��ɂ��邩�𔻒�
			if (1){
				;
			}
		}
		//�擾���W���ʓ��ɂ��邩�𔻒�
		if (1){
			;
		}*/
	}
	return FALSE;
}

//�{�b�N�X�ƃ{�b�N�X�̏Փˌ��o
BOOL HitCheckBoxToBox(	const VecFx32 *inBoxCore1, 
						const VecFx32 *inBoxSize1, 
						const VecFx32 *inBoxRot1,
						const VecFx32 *inDirVec1,
						const VecFx32 *inBoxCore2, 
						const VecFx32 *inBoxSize2, 
						const VecFx32 *inBoxRot2,
						const VecFx32 *inDirVec2)
{
	VTX_DATA_FOR_BOXHIT data1,data2;
	data1.Count = 0;
	data2.Count = 0;
	//�{�b�N�X�ƃ{�b�N�X�̏Փˌ��o����(��Փ˃{�b�N�X�̊e�ʂɑ΂��āA���_���ՓˁA�ӂ��ՓˁA�ʂ��Փ˂��邩�𒲂ׂ�)
	if ( HitCheckBoxToBoxSub(inBoxCore1, inBoxSize1, inBoxRot1, inDirVec1, inBoxCore2, inBoxSize2, inBoxRot2, &data1) == FALSE ){
		//�{�b�N�X�̗�������ւ��āA�Փˌ��o����
		if ( HitCheckBoxToBoxSub(inBoxCore2, inBoxSize2, inBoxRot2, inDirVec2, inBoxCore1, inBoxSize1, inBoxRot1, &data2) == FALSE ){
			//�Փ˂��闼�{�b�N�X�̕ӂ��A�ǂ̖ʂƂ����s�ł͂Ȃ��ꍇ�̏Փ˂����o����
			if ( HitCheckBoxSegToSegNoParallel(&data1,inBoxSize2) == FALSE ){
				//��������ւ��āA�Փˌ��o����
				if ( HitCheckBoxSegToSegNoParallel(&data2,inBoxSize1) == FALSE ){
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}


//�N���b�s���O����
//2�c��ԏ�̒Z�`�Ɛ����̌�������
//�K�v�f�[�^�F4���_�A�����̒[�_
//�������ʂōl����̂ŁA�K�����l��0�N���A����
BOOL CheckHitPlaneToSegment2D(	const VecFx32 *inVtx1,
								const VecFx32 *inVtx2,
								const VecFx32 *inVtx3,
								const VecFx32 *inVtx4,
								const VecFx32 *inS_Vec,
								const VecFx32 *inE_Vec )
{
	u8 i;
	u8 res1,res2;
	VecFx32 vtx[5];
	VecFx32 cross;
	VecFx32 segPoint1;
	VecFx32 segPoint2;
	
	vtx[0] = *inVtx1;
	vtx[1] = *inVtx2;
	vtx[2] = *inVtx3;
	vtx[3] = *inVtx4;
	vtx[4] = *inVtx1;
	segPoint1 = *inS_Vec;
	segPoint2 = *inE_Vec;
	//y�l��0�N���A
	for (i=0;i<5;i++){
		vtx[i].y = 0;
	}
	segPoint1.y = 0;
	segPoint2.y = 0;
	
	for (i=0;i<4;i++){
		res1 = BG2D_VectorSide( &vtx[i], &vtx[i+1], &segPoint1 );
		res2 = BG2D_VectorSide( &vtx[i], &vtx[i+1], &segPoint2 );
		//���ɕ\�̏ꍇ�́A�Փ˂��Ȃ��̂ŏI��
		if (res1 && res2){
			return FALSE;
		}
		else if (res1 ^ res2){
			//�\���ɕ����ꂽ�Ƃ��́A�\���̓_������Ƃ̌�_�ɒu�������ď����𑱍s
			if ( GetPointLineToLine( &vtx[i], &vtx[i+1], &segPoint1,&segPoint2, &cross ) == FALSE ){
				//��_���Ȃ��ꍇ�́A�������I��
				return FALSE;
			}
			(res1 == 1)? (segPoint1 = cross) : (segPoint2 = cross);
		}else{
			//���ɗ��̏ꍇ�́A���������Ɏ��̐�����
			;
		}
	}
	//��L���������Ȃ��Ă��֐��𔲂��Ȃ������ꍇ�́A�������Ă���
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
//2D
//////////////////////////////////////////////////////////////////////
//�����̌�������
//---------------------------------------------------------------------------------------------------------
/**
 *  �O�ς��g�p���Ďw����W���w��x�N�g���̍��E�ǂ���ɂ��邩�𔻒�
 *  @param  *inS_Vec        �x�N�g���n�_
 *  @param  *inE_Vec        �x�N�g���I�_
 *  @param  *inT_Vec        �w����W
 *
 *  @retval int         1:�\�i�x�N�g������܂ށj�@0:��
*/
//---------------------------------------------------------------------------------------------------------
int BG2D_VectorSide( const VecFx32 *inS_Vec, const VecFx32 *inE_Vec, const VecFx32 *inT_Vec )
{
	fx32 n;
	
	//�O�ς����߂�iVEC_CrossProduct���g�p�j
	n = FX_Mul(inT_Vec->z , (inS_Vec->x - inE_Vec->x))+FX_Mul(inS_Vec->z , (inE_Vec->x - inT_Vec->x))+FX_Mul(inE_Vec->z , (inT_Vec->x - inS_Vec->x));
	
	if      ( n >= 0 ) return  1; // �\(��)
	else  return 0; // ��(�E)
}

//---------------------------------------------------------------------------------------------------------
/**
 * �������m�̌�������
 *  @param  *inS_Vec1        �x�N�g���n�_
 *  @param  *inE_Vec1        �x�N�g���I�_
 *  @param  *inS_Vec2        �x�N�g���n�_
 *  @param  *inE_Vec2        �x�N�g���I�_
 *
 *  @retval BOOL
*/
//---------------------------------------------------------------------------------------------------------
BOOL BG2D_CheckSegmentToSegment( const VecFx32 *inS_Vec1, const VecFx32 *inE_Vec1, const VecFx32 *inS_Vec2, const VecFx32 *inE_Vec2 )
{
	if ( ((BG2D_VectorSide(inS_Vec1,inE_Vec1,inS_Vec2) ^ BG2D_VectorSide(inS_Vec1,inE_Vec1,inE_Vec2)) == 0) &&
		 ((BG2D_VectorSide(inS_Vec2,inE_Vec2,inS_Vec1) ^ BG2D_VectorSide(inS_Vec2,inE_Vec2,inE_Vec1)) == 0)	){
		return TRUE;
	}
	else  return FALSE;
}

//�������m�̌�_
//�����́A2�_�Œ�`����
//��`���ꂽ�����ɑ΂��āA�����Е��̒������`����2�_���������ɂ���ꍇ�́A��_�͊O���_�ƂȂ�A�قȂ�ꍇ�́A�����_�ƂȂ�
//�������������Ȃ��ꍇ�́AFALSE���Ԃ�
BOOL GetPointLineToLine(	const VecFx32 *inS_Vec1,
									const VecFx32 *inE_Vec1,
									const VecFx32 *inS_Vec2,
									const VecFx32 *inE_Vec2,
									VecFx32 *outVec )
{
	fx32 dist1,dist2;
	VecFx32 dirVec;
	fx32 t,len,sc;
	u8 res1,res2;
	
	dist1 = BG3D_GetPointSegmentDistance2(inS_Vec2, inS_Vec1, inE_Vec1);
	dist2 = BG3D_GetPointSegmentDistance2(inE_Vec2, inS_Vec1, inE_Vec1);

	//2�_���A���肷�钼���ɑ΂��āA�ǂ��瑤�ɂ��邩�𒲂ׂ�
	res1 = BG2D_VectorSide( inS_Vec1, inE_Vec1, inS_Vec2 );
	res2 = BG2D_VectorSide( inS_Vec1, inE_Vec1, inE_Vec2 );
	if (res1 ^ res2){
		//�قȂ鑤�ɂ���̂ŁA��_�́A�����_
		//�}��ϐ�
		t = FX_Div(dist1, (dist1+dist2));
	}else{
		//�������ɂ���̂ŁA��_�́A�O���_
		//�}��ϐ�
		if (dist1>dist2){
			t = FX_Div(dist1, (dist1-dist2));
		}else if (dist1<dist2){
			t = FX_Div(dist2, (dist2-dist1));
		}else{
			//2���������s�̂��ߌ�_�Ȃ�
			return FALSE;
		}
	}
	//�}��ϐ������_�����߂�
	//vector:start��end
	VEC_Subtract(inE_Vec2,inS_Vec2,&dirVec);
	//��������(2D)�ōl����̂Œ����Z�o��m�[�}���C�Y����O�ɂ��l��0�N���A����
	dirVec.y = 0;
	//OS_Printf("t = %x\n",t);
	{
		VEC_MultAdd(t , &dirVec, inS_Vec2, outVec);
	}
	return TRUE;
}

//�����̌�_
//�������m���������Ȃ��ꍇ�AFLASE���Ԃ�
BOOL GetPointSegmentToSegment(	const VecFx32 *inS_Vec1,
									const VecFx32 *inE_Vec1,
									const VecFx32 *inS_Vec2,
									const VecFx32 *inE_Vec2,
									VecFx32 *outVec )
{
	fx32 dist1,dist2;
	VecFx32 dirVec;
	fx32 t;

	//�������m���������邩�𔻒肷��
	if( BG2D_CheckSegmentToSegment( inS_Vec1, inE_Vec1, inS_Vec2, inE_Vec2 ) == FALSE ){
		return FALSE;	//�������Ȃ�
	}
	
	dist1 = BG3D_GetPointSegmentDistance2(inS_Vec2, inS_Vec1, inE_Vec1);
	dist2 = BG3D_GetPointSegmentDistance2(inE_Vec2, inS_Vec1, inE_Vec1);


	//�}��ϐ�
	t = FX_Div(dist1, (dist1+dist2));
	//vector:start��end
	VEC_Subtract(inE_Vec2,inS_Vec2,&dirVec);
	{
		VEC_MultAdd(t , &dirVec, inS_Vec2, outVec);
	}

	return TRUE;
}

//�O�p�`�̓��O����ZX�ˉe��
BOOL BG3D_CheckTriangleIObyZX(const VecFx32 inT_Vtx,const VecFx32 inVtx1,const VecFx32 inVtx2,const VecFx32 inVtx3)
{
	//�O�ς����߂�iVEC_CrossProduct���g�p�j
	fx32 cross;
	fx32 cross1;
	fx32 cross2;
	fx32 cross3;
	fx32 cross_total;
	cross = FX_Mul(inVtx3.z,inVtx1.x-inVtx2.x) + FX_Mul(inVtx1.z,inVtx2.x-inVtx3.x) + FX_Mul(inVtx2.z,inVtx3.x-inVtx1.x);
	cross1 = FX_Mul(inVtx2.z,inT_Vtx.x-inVtx1.x) + FX_Mul(inT_Vtx.z,inVtx1.x-inVtx2.x) + FX_Mul(inVtx1.z,inVtx2.x-inT_Vtx.x);
	cross2 = FX_Mul(inVtx3.z,inT_Vtx.x-inVtx2.x) + FX_Mul(inT_Vtx.z,inVtx2.x-inVtx3.x) + FX_Mul(inVtx2.z,inVtx3.x-inT_Vtx.x);
	cross3 = FX_Mul(inVtx1.z,inT_Vtx.x-inVtx3.x) + FX_Mul(inT_Vtx.z,inVtx3.x-inVtx1.x) + FX_Mul(inVtx3.z,inVtx1.x-inT_Vtx.x);

	if (cross < 0){
///		OS_Printf("out\n");
		return FALSE;
	}
	if (cross1 < 0){
///		OS_Printf("out1\n");
		return FALSE;
	}
	if (cross2 < 0){
///		OS_Printf("out2\n");
		return FALSE;
	}
	if (cross3 < 0){
///		OS_Printf("out3\n");
		return FALSE;
	}
#if 0
	OS_Printf("cross:%d\n",cross);
	OS_Printf("cross1:%d\n",cross1);
	OS_Printf("cross2:%d\n",cross2);
	OS_Printf("cross3:%d\n",cross3);
	OS_Printf("cross_total:%d\n",cross_total);
	OS_Printf("z:%x\n",inT_Vtx.z);
	OS_Printf("x:%x\n",inT_Vtx.x);
	OS_Printf("z1:%x\n",inVtx1.z);
	OS_Printf("x1:%x\n",inVtx1.x);
	OS_Printf("z2:%x\n",inVtx2.z);
	OS_Printf("x2:%x\n",inVtx2.x);
	OS_Printf("z3:%x\n",inVtx3.z);
	OS_Printf("x3:%x\n",inVtx3.x);
#endif	
	return TRUE;
}

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
void  VecFx32_to_MtxFx33( MtxFx33* dst, VecFx32* src )
{
	MtxFx33 tmp;

	MTX_RotX33(	dst,FX_SinIdx((u16)src->x),FX_CosIdx((u16)src->x));

	MTX_RotY33(	&tmp,FX_SinIdx((u16)src->y),FX_CosIdx((u16)src->y));
	MTX_Concat33(dst,&tmp,dst);

	MTX_RotZ33(	&tmp,FX_SinIdx((u16)src->z),FX_CosIdx((u16)src->z));
	MTX_Concat33(dst,&tmp,dst);
}

/*---------------------------------------------------------------------
  @brief	360�xXYZ�̉�]�p���R�w�R�s��ւ̕ϊ� 

  @param	dst MtxFx33:���Z���ʂ��i�[����MtxFx33�^�̃|�C���^
  @param	x	��]�pX(360�x�P��,0-359�𒴂��Ȃ���)
  @param	y	��]�pY(360�x�P��)
  @param	z	��]�pZ(360�x�P��)

  @return none
 *--------------------------------------------------------------------*/
void  Rot360_to_MtxFx33( MtxFx33* dst,u16 x,u16 y,u16 z)
{
	MtxFx33 tmp;

	MTX_RotX33(	dst,_Sin360(x),_Cos360(x));

	MTX_RotY33(	&tmp,_Sin360(y),_Cos360(y));
	MTX_Concat33(dst,&tmp,dst);

	MTX_RotZ33(	&tmp,_Sin360(z),_Cos360(z));
	MTX_Concat33(dst,&tmp,dst);
}

/*---------------------------------------------------------------------
  Name       :�x�N�g�����S�w�R�s��ւ̕ϊ� 
  In	: dst = �s��|�C���^,dst = �x�N�g���|�C���^ 
  Out	: �Ȃ�
 *--------------------------------------------------------------------*/
void  VecFx32_to_MtxFx43( MtxFx43* dst, VecFx32* src )
{
	MtxFx43 tmp;

	MTX_RotX43(	dst,FX_SinIdx((u16)src->x),FX_CosIdx((u16)src->x));

	MTX_RotY43(	&tmp,FX_SinIdx((u16)src->y),FX_CosIdx((u16)src->y));
	MTX_Concat43(dst,&tmp,dst);

	MTX_RotZ43(	&tmp,FX_SinIdx((u16)src->z),FX_CosIdx((u16)src->z));
	MTX_Concat43(dst,&tmp,dst);
}

/*---------------------------------------------------------------------
  @brief	360�xXYZ�̉�]�p��4x3�s��ւ̕ϊ� 

  @param	dst MtxFx43:���Z���ʂ��i�[����MtxFx43�^�̃|�C���^
  @param	x	��]�pX(360�x�P��,0-359�𒴂��Ȃ���)
  @param	y	��]�pY(360�x�P��,0-359)
  @param	z	��]�pZ(360�x�P��,0-359)

  @return none
 *--------------------------------------------------------------------*/
void  Rot360_to_MtxFx43( MtxFx43* dst,u16 x,u16 y,u16 z)
{
	MtxFx43 tmp;

	MTX_RotX43(	dst,_Sin360(x),_Cos360(x));

	MTX_RotY43(	&tmp,_Sin360(y),_Cos360(y));
	MTX_Concat43(dst,&tmp,dst);

	MTX_RotZ43(	&tmp,_Sin360(z),_Cos360(z));
	MTX_Concat43(dst,&tmp,dst);
}

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
void GetPerspectiveScreenSize( u16 PerspWay, fx32 Dist, fx32 Aspect, fx32* pWidth, fx32* pHeight )
{
	fx32 fovySin;
	fx32 fovyCos;
	fx32 fovyTan;

	fovySin = FX_SinIdx( PerspWay );
	fovyCos = FX_CosIdx( PerspWay );

	fovyTan = FX_Div( fovySin, fovyCos );
	
	// ���������߂�
	*pHeight = FX_Mul(Dist, fovyTan);				// (fovySin / fovyCos)*TargetDist
	*pHeight = FX_Mul(*pHeight, 2*FX32_ONE);		// �Q������Ɖ�ʂ̍����ɂȂ�
	
	// �������߂�(�A�X�y�N�g��4/3�ŌŒ�)
	*pWidth  = FX_Mul(*pHeight, Aspect );
}

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		field_light.c
 *@brief	���C�g�R���g���[��
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
 *					�萔�錾
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------

//-------------------------------------
//	
//	�P���\���Z�b�g	
//	
//=====================================
typedef struct _LIGHT_CONT_SET{
	u32		DataNum;				// �f�[�^��
	LIGHT_CONT_DATA* pDataTbl;		// �f�[�^�e�[�u��
	int Light_Num;					// ����LIGHT�i���o�[
	GLST_DATA_PTR	Glb;			// �O���[�o���X�e�[�g�̏�ԕۑ��̈�
	BOOL reflect;					// ���f�t���O	TRUE���f
} LIGHT_CONT_SET;


//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
static void DataSetLightContPack(LIGHT_CONT_SET* cont);			// ���̃��C�g�f�[�^�𔽉f����

static u32 loadLightData( const char* str, LIGHT_CONT_DATA** ppData );			// ���C�g�f�[�^�ǂݍ���
static void dellLightData(LIGHT_CONT_DATA** ppData);						// ���C�g�f�[�^�j��
static char* GetLightData( char* buff, GXRgb* Color, VecFx16* Vector );		// light�f�[�^���擾
static char* GetRgbData( char* buff, GXRgb* Color );						// �F�f�[�^���擾
//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------
//�A�[�J�C�u������������s�v
static const char *const Path[ LIGHT_TYPE_MAX ] =
{
	{"data/area00light.txt"},
	{"data/area01light.txt"},
	{"data/area02light.txt"},
};

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�V�X�e����������
 *		
 *@param	glb			�O���[�o���X�e�[�g�̏�ԕۑ��̈�
 *@param	path		���C�g�e�[�u���p�X
 *
 *@return	LIGHT_CONT_PTR	�쐬�������C�g�V�X�e���f�[�^
 *
 */
//-----------------------------------------------------------------------------
LIGHT_CONT_PTR InitLightCont(GLST_DATA_PTR glb, const u8 light_index/*const char* path*/)
{
	int		i;	// ���[�v�p
	LIGHT_CONT_PTR data;
	int light_movecount;
	
	GF_ASSERT(light_index<LIGHT_TYPE_MAX && "���C�g�C���f�b�N�X�I�[�o�[");

	data = sys_AllocMemory(HEAPID_FIELD, sizeof(LIGHT_CONT_SET));
	
	data->Glb = glb;		// �O���[�o���X�e�[�g�̏�ԕۑ��̈��ۑ�
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print light = %s\n",Path[light_index]);
#endif	
	// �ǂݍ���
	data->DataNum = loadLightData(Path[light_index], &data->pDataTbl);
	data->Light_Num = 0;

	// RTC���猻�ݎ��Ԃ̎擾�������Ȃ��܂��B
	light_movecount = GF_RTC_GetTimeBySecond() / 2;

	// ���̎��Ԃ͂ǂ̃��C�g���`�F�b�N
	// ����͎��Ԃ���e�[�u���𓮂��������l���ē���܂����B
	for(i = 0;i < data->DataNum; i++){
		if(data->pDataTbl[i].lightEnd > light_movecount){
			data->Light_Num = i;				// ���C�g���ݒ�
			break;
		}
	}

	// ���f
	data->reflect = TRUE;

	DataSetLightContPack(data);

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�R���g���[���V�X�e����j��
 *
 *@param	pLight		���C�g�V�X�e���f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DellLightCont( LIGHT_CONT_PTR* pLight )
{
	GF_ASSERT(pLight);
	
	dellLightData(&(*pLight)->pDataTbl);	// �f�[�^�j��
	
	sys_FreeMemory(HEAPID_FIELD, *pLight);
	*pLight = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�f�[�^�𓮂���
 *
 *@param	Light		���C�g�R���g���[���f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void MainLightCont(LIGHT_CONT_PTR Light)
{
	u32 num;
	int i;		// ���[�v�p
	int light_min;	// ���̃e�[�u���̃��C�g�J�E���^�ŏ�
	int light_max;	// ���̃e�[�u���̃��C�g�J�E���^�ő�
	int light_movecount;
	
	GF_ASSERT(Light);
	
	// RTC���猻�ݎ��Ԃ̎擾�������Ȃ��܂��B
	light_movecount = GF_RTC_GetTimeBySecond() / 2;

	// ���C�g�e�[�u�����P�Ȃ�ύX�͂��Ȃ�
	if( Light->DataNum > 1 ){

		// ���̃��C�g�e�[�u���̍ŏ��J�E���g�l�@�ő�J�E���g�l��ݒ�
		if( (Light->Light_Num - 1) >= 0 ){
			light_min = Light->pDataTbl[ Light->Light_Num - 1 ].lightEnd;
		}else{
			light_min = 0;
			
		}
		light_max = Light->pDataTbl[ Light->Light_Num ].lightEnd;

	
		// �J�E���^�̃^�C�~���O�ɂȂ�����
		// ���f������\���̂�ύX����
		if( ( light_movecount >= light_max ) ||		// �J�E���g�l���͈͊O�̂Ƃ���Light_Num���J�E���g�A�b�v����
			( light_movecount < light_min ) ){		// �J�E���g�l���͈͓��̃e�[�u����T��

			Light->Light_Num++;	// �ݒ肷��f�[�^�̃i���o�[���擾
			if( Light->Light_Num >= Light->DataNum ){	// �f�[�^�ȏ�ɂȂ�����J�E���^������
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
 *	@brief	���C�g�f�[�^���f�t���O�ݒ�
 *
 *	@param	Light		���C�g���[�N
 *	@param	reflect		���f�t���O
 *	
 *	@return	none
 *	reflect 
 *		TRUE	���f������
 *		FALSE	���f�����Ȃ�
 */
//-----------------------------------------------------------------------------
void SetLightContReflect( LIGHT_CONT_PTR Light, BOOL reflect )
{
	Light->reflect = reflect;

	// ���f�ɂ����ꍇ���̎��_�ŁA1�x�f�[�^��ݒ肷��
	if( Light->reflect ){
		DataSetLightContPack(Light);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C�g�f�[�^���f�t���O��Ԏ擾
 *
 *	@param	Light	���C�g�R���g���[��
 *
 *	@retval	TRUE	���f��
 *	@retval	FALSE	���f���Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL GetLightContReflect( CONST_LIGHT_CONT_PTR Light )
{
	return Light->reflect;
}

//----------------------------------------------------------------------------
/**
 *	@brief	1���C�g�f�[�^�ݒ�
 *
 *	@param	move	���[�N
 *	@param	pGlst	�O���[�o���X�e�[�g�f�[�^
 *	
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void DataSetLightCont( const LIGHT_CONT_DATA* move, GLST_DATA_PTR pGlst )
{
	int i;		// ���[�v�p
	
	// ���C�g�ݒ�
	for(i=0;i<4;i++){
		int check = 	(1<<i);
		if((move->lightFlag & check) != 0){
			GLST_LightVector(pGlst, i, move->lightVec[i].x, move->lightVec[i].y, move->lightVec[i].z);
			GLST_LightColor(pGlst, i,move->lightColor[i]);
		}else{
			GLST_LightVector(pGlst, i, 0, 0, 0);
			GLST_LightColor(pGlst, i,GX_RGB(0,0,0));		// ���C�g����
		}
	}
	// �f�B�t���[�Y�A�A���r�G���g�A�X�y�L�����[�A���ˌ�
	GLST_MaterialDiff(pGlst, move->diffuse,FALSE,FALSE);
	GLST_MaterialAmb(pGlst, move->ambient,TRUE);
	GLST_MaterialSpec(pGlst, move->specular,FALSE,FALSE);
	GLST_MaterialEmi(pGlst, move->emission,TRUE);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���̃��C�g�f�[�^�𔽉f������
 *
 *@param	cont		���C�g�R���g���[���Z�b�g	
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
 *	@brief	�邩�`�F�b�N
 *
 *	@param	cont	���C�g�R���g���[���V�X�e��
 *
 *	@retval	TRUE	��
 *	@retval	FALSE	��
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
 *@brief	���f�������C�g��A�}�e���A���̃f�[�^�̓O���[�o���X�e�[�g��
 *			�g�p����悤�ɕύX����
 *
 *@param	Mdl		�Z�b�g���郂�f��
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void SetGlbLightMdl(NNSG3dResMdl* Mdl)
{
	// ���C�g�A�}�e���A���̓O���[�o���X�e�[�g�̒l���g�p����
	NNS_G3dMdlUseGlbDiff(Mdl);				// �f�B�t���[�Y
	NNS_G3dMdlUseGlbAmb(Mdl);				// �A���r�G���g
	NNS_G3dMdlUseGlbSpec(Mdl);				// �X�y�L�����[
	NNS_G3dMdlUseGlbEmi(Mdl);				// �G�~�b�V����
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���f�������C�g��A�}�e���A���̃f�[�^�̓O���[�o���X�e�[�g��
 *			�g�p���Ȃ��悤�ɕύX����
 *
 *@param	Mdl		�Z�b�g���郂�f��
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void RemGlbLightMdl(NNSG3dResMdl* Mdl)
{
	// ���C�g�A�}�e���A���̓��f���l���g�p����
	NNS_G3dMdlUseMdlDiff(Mdl);				// �f�B�t���[�Y
	NNS_G3dMdlUseMdlAmb(Mdl);				// �A���r�G���g
	NNS_G3dMdlUseMdlSpec(Mdl);				// �X�y�L�����[
	NNS_G3dMdlUseMdlEmi(Mdl);				// �G�~�b�V����
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�f�[�^��ǂݍ���
 *
 *@param	str		�t�@�C���p�X
 *@param	ppData	�i�[��
 *
 *@return	���C�g�f�[�^��
 *
 *
 */
//-----------------------------------------------------------------------------
static u32 loadLightData( const char* str, LIGHT_CONT_DATA** ppData )
{
	int   i,j;			// ���[�v�p
	int	  data_num;		// �f�[�^��
	void* filep;		// �t�@�C���|�C���^
	void* tmp;			// �폜�p�t�@�C���|�C���^�ۑ�
	char  buff[256];	// �ǂݍ��݂悤
	char* buff_work;	// �o�b�t�@����p
	char r_b[256];		// ���[�J����Ɨp�o�b�t�@
	LIGHT_CONT_DATA* pDataWork;	// �i�[��Ɨp

	
	tmp = sys_LoadFile(HEAPID_FIELD,str);		// �t�@�C���I�[�v��
	filep = tmp;				// ��Ɨp�ϐ��ɑ��
	
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

	// �f�[�^�����̗̈���m��
	*ppData = sys_AllocMemory(HEAPID_FIELD, sizeof(LIGHT_CONT_DATA)*data_num);
	MI_CpuClear8(*ppData, sizeof(LIGHT_CONT_DATA)*data_num);

	// �f�[�^���i�[
	filep = tmp;
	for(i=0;i<data_num;i++){

		// �i�[����Z�b�g
		pDataWork = &((*ppData)[i]);

		// �^�C�~���O
		filep = StrTok(filep,buff,RETURN_CODE);
		buff_work = buff;
		buff_work = StrTok(buff_work,r_b,',');
		pDataWork->lightEnd = AtoI(r_b);
		
		// light
		for(j=0;j<4;j++){
			// light�f�[�^�擾
			filep = GetLightData(filep, &pDataWork->lightColor[j], &pDataWork->lightVec[j]);
			if(pDataWork->lightColor[j] != 0xffff){		// light���g�p����̂��`�F�b�N
				pDataWork->lightFlag |= 1 << j;
			}else{
				pDataWork->lightColor[j] = 0;
			}
		}

		// �F
		filep = GetRgbData(filep, &pDataWork->diffuse);	// �f�B�t���[�Y
		filep = GetRgbData(filep, &pDataWork->ambient);	// �A���r�G���g
		filep = GetRgbData(filep, &pDataWork->specular);	// �X�y�L�����[
		filep = GetRgbData(filep, &pDataWork->emission);	// �G�~�b�V����	


		// ���s
		filep = StrTok(filep,buff,RETURN_CODE);
	}

	sys_FreeMemory(HEAPID_FIELD,tmp);		// �t�@�C���j��

	return data_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�f�[�^��j��
 *
 *@param	str		�t�@�C���p�X
 *@param	ppData	�i�[��
 *
 *@return	���C�g�f�[�^��
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
 *@brief	�e���C�g�f�[�^��ǂݍ���
 *
 *@param	buff		�ǂݍ��ݐ�
 *@param	Color		���C�g�̐F�������ݐ�
 *@param	Vector		���C�g�̃x�N�g���������ݐ�
 *
 *@return	���̓Ǎ���
 *
 *
 */
//-----------------------------------------------------------------------------
static char* GetLightData( char* buff, GXRgb* Color, VecFx16* Vector )		// light�f�[�^���擾
{
	char work[256];			// �ǂݍ��݂悤
	char work2[256];		// �؂���p
	char* data_work;		// �f�[�^���[�N
	u32	flag;				// light�L���`�F�b�N�p
	int	i;					// ���[�v�p
	u16	rgb[3];				// �F�i�[�p
	s32	vec[3];				// ���W�i�[�p
 
	
	// light
	buff = StrTok(buff,work,RETURN_CODE);
	data_work = work;
	data_work = StrTok(data_work,work2,',');
	flag = AtoI(work2);
	if(flag == 1){
		// �F
		for(i=0;i<3;i++){
			data_work = StrTok(data_work,work2,',');
			rgb[i] = AtoI(work2);
		}

		// �F��ݒ�
		*Color = GX_RGB(rgb[0],rgb[1],rgb[2]);
		
		// �x�N�g��
		for(i=0;i<3;i++){
			data_work = StrTok(data_work,work2,',');
			vec[i] = AtoI(work2);
		}

		// �x�N�g����ݒ�
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

		// �_�~�[�f�[�^���Z�b�g
		*Color = 0xffff;
	}

	return buff;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�F�f�[�^��ǂݍ���
 *
 *@param	buff		�ǂݍ��ݐ�
 *@param	Color		���C�g�̐F�������ݐ�
 *
 *@return	���̓Ǎ���
 *
 *
 */
//-----------------------------------------------------------------------------
static char* GetRgbData( char* buff, GXRgb* Color )
{
	char work[256];			// �ǂݍ��݂悤
	char work2[256];		// �؂���p
	char* data_work;		// ��Ɨp
	int i;
	u16	rgb[3];				// �F�i�[�p
	
	buff = StrTok(buff,work,RETURN_CODE);
	data_work = work;
	
	// �F
	for(i=0;i<3;i++){
		data_work = StrTok(data_work,work2,',');
		rgb[i] = AtoI(work2);
	}

	// �F��ݒ�
	*Color = GX_RGB(rgb[0],rgb[1],rgb[2]);

	return buff;
}

/**
 *	@brief	�M�l�X�z�[���@�Z�[�u�f�[�^�A�N�Z�X
 */

#ifndef __H_GUINNESS_H__
#define __H_GUINNESS_H__

#define GNS_RECORD_NUM	(13)	//���R�[�h���̃f�[�^��
#define GNS_BLOCK_NUM	(GNS_RECORD_NUM*2)	//�u���b�N��
#define GNS_DATA_NUM	(6)		//1�u���b�N�̃f�[�^��

///�M�l�X�f�[�^�^�C�vID
typedef enum{
 GNSTYPE_BTL,		///<�o�g��
 GNSTYPE_POKE,		///<�|�P����
 GNSTYPE_CONTEST,	///<�R���e�X�g
}GNSTYPE;

///�M�l�X�u���b�N�f�[�^ID
typedef enum{
 GNSID_GLB_SINGLE,		///<�O���[�o���@�^���[�V���O���ő�A��
 GNSID_GLB_DOUBLE,		///<�O���[�o���@�^���[�_�u���ő�A��
 GNSID_GLB_MULTI,		///<�O���[�o���@�^���[AI�}���`�ő�A��
 GNSID_GLB_CMULTI,		///<�O���[�o���@�^���[�ʐM�}���`�ő�A��
 GNSID_GLB_WIFI,		///<�O���[�o���@�^���[Wifi�ő�A��
 GNSID_GLB_WIN,			///<�O���[�o���@�^���[���Ϗ���������
 GNSID_GLP_KILL,		///<�O���[�o���@�|�����|�P������
 GNSID_GLP_CAPUTURE,	///<�O���[�o���@�߂܂����|�P������
 GNSID_GLP_HATCHING,	///<�O���[�o���@�z�����|�P������
 GNSID_GLP_FISHING,		///<�O���[�o���@�ނ�グ���|�P������
 GNSID_GLC_GPX,			///<�O���[�o���@�R���e�X�g�D��
 GNSID_GLC_GPXPER,		///<�O���[�o���@�R���e�X�g�D����
 GNSID_GLC_RIBBON,		///<�O���[�o���@�R���e�X�g���{���l����
 
 GNSID_GRB_SINGLE,		///<�O���[�v�@�^���[�V���O���ő�A��
 GNSID_GRB_DOUBLE,		///<�O���[�v�@�^���[�_�u���ő�A��
 GNSID_GRB_MULTI,		///<�O���[�v�@�^���[AI�}���`�ő�A��
 GNSID_GRB_CMULTI,		///<�O���[�v�@�^���[�ʐM�}���`�ő�A��
 GNSID_GRB_WIFI,		///<�O���[�v�@�^���[Wifi�ő�A��
 GNSID_GRB_WIN,			///<�O���[�v�@�^���[���Ϗ���������
 GNSID_GRP_KILL,		///<�O���[�v�@�|�����|�P������
 GNSID_GRP_CAPUTURE,	///<�O���[�v�@�߂܂����|�P������
 GNSID_GRP_HATCHING,	///<�O���[�v�@�z�����|�P������
 GNSID_GRP_FISHING,		///<�O���[�v�@�ނ�グ���|�P������
 GNSID_GRC_GPX,			///<�O���[�v�@�R���e�X�g�D��
 GNSID_GRC_GPXPER,		///<�O���[�v�@�R���e�X�g�D����
 GNSID_GRC_RIBBON,		///<�O���[�v�@�R���e�X�g���{���l����
}GNSID;

/**
 *	@brief	�M�l�X�����L���O�f�[�^���J�f�[�^�^
 *
 *	�M�l�X�̃����L���O�f�[�^���擾����Ƃ��A���̌^�ŌX�̃f�[�^������
 */
typedef struct _GNS_RECORD{
	u32	groupID;
	u32	record;
	STRBUF	*name;
}GNS_RECORD;

typedef struct _GNS_RANKING{
	int				num;	//�L���f�[�^��
	GNS_RECORD	rank[GNS_DATA_NUM];	//�X�̃f�[�^
}GNS_RANKING;

/**
 * @brief	�M�l�X�z�[���Z�[�u�f�[�^�\���̂ւ̕s���S�^�|�C���^
 *
 * ���g�͌����܂��񂪃|�C���^�o�R�ŎQ�Ƃł��܂�
 */
typedef struct _GUINNESS_DATA	GUINNESS_DATA;
typedef struct _GUINNESS_BLOCK	GUINNESS_BLOCK;
typedef struct _GUINNESS_RECORD	GUINNESS_RECORD;
typedef struct _GUINNESS	GUINNESS;

#undef GLOBAL
#ifdef __GUINNESS_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

//===================================================================
///�M�l�X�f�[�^�֘A
//===================================================================
/**
 *	@brief	�M�l�X�f�[�^�@�N���A
 */
GLOBAL void GNS_DataClear(GUINNESS_DATA* dat);
/**
 *	@brief	�M�l�X�f�[�^���L�����ǂ����H
 *
 *	�����O������NULL������Ȃ��
 */
GLOBAL BOOL GNS_IsEnable(GUINNESS_DATA* dat);

/**
 *	@brief	�M�l�X�f�[�^�@�R�s�[
 */
GLOBAL void GNS_DataCopy(const GUINNESS_DATA* src,GUINNESS_DATA* dest);

//===================================================================
///�M�l�X�z�[���f�[�^�֘A
//===================================================================
/**
 *	@brief	�M�l�X�z�[���@�f�[�^�T�C�Y
 */
GLOBAL int	GuinnessData_GetWorkSize(void);

/**
 *	@brief	�M�l�X�z�[���@�f�[�^������
 */
GLOBAL void GuinnessData_Init(GUINNESS* dat);

/**
 *	@brief	�M�l�X�z�[���@�f�[�^�u���b�N�ւ̃|�C���^���擾
 */
GLOBAL GUINNESS* SaveData_GetGuinnessData(SAVEDATA* sv);

/**
 *	@brief	�M�l�X�@�w�肵���f�[�^����������
 */
GLOBAL void GuinnessData_DelRecord(GUINNESS* dat,GNSID id,u8 idx);

//===================================================================
///�M�l�X�@���R�[�h�f�[�^�֘A
//===================================================================
/**
 *	@brief	�M�l�X�@���R�[�h���M�f�[�^�T�C�Y�擾
 */
GLOBAL int GuinnessRecord_GetWorkSize(void);

/**
 *	@brief	�M�l�X�@���R�[�h���M�f�[�^�쐬
 */
GLOBAL void* GuinnessRecord_SendDataAlloc(SAVEDATA* sv,int heapID);

/**
 *	@brief	�M�l�X�@���R�[�hMix
 */
GLOBAL void GuinnessRecord_RecvDataMix(SAVEDATA* sv,
		int myid,u8 datanum,const void** array,int heapID);

//===================================================================
///�M�l�X�����L���O�f�[�^�֘A
//===================================================================
///�^�C�v�ʂ̃u���b�N����Ԃ�
GLOBAL u8 GNSRank_GetTypeBlockNum(GNSTYPE type);
///�^�C�v�ʂ�GNSID�I�t�Z�b�g��Ԃ�
GLOBAL u8 GNSRank_GetTypeGNSIDOfs(GNSTYPE type);

/**
 *	@brief	�M�l�X�����L���O�f�[�^�@�����̃��R�[�h���擾
 *
 *	@return	GNS_RANKING*
 *
 *	��GNS_RANKING�f�[�^�^���������m�ۂ��A�f�[�^���i�[���ĕԂ�
 *	
 *	�@GNSRank_FreeRankingData()�֐���K���p����
 *	�@�Ăяo������������ƃ�����������邱�ƁI
 *	  sys_FreeMemory�ŉ��������_��	
 */
GNS_RANKING* GNSRank_AllocMyData(SAVEDATA* sv,GNSTYPE type,int heapID);

/**
 *	@brief	�M�l�X�����L���O�f�[�^�擾
 *
 *	@return	
 *	��GNS_RANKING�f�[�^�^���������m�ۂ��f�[�^���R�s�[���ĕԂ�
 *
 *	�@GNSRank_FreeRankingData()�֐���K���p����
 *	�@�Ăяo������������ƃ�����������邱�ƁI
 *	  sys_FreeMemory�ŉ��������_��	
 */
GLOBAL GNS_RANKING* GNSRank_AllocRankingData(GUINNESS* gns,GNSID id,int heapID);

/**
 *	@brief	�M�l�X�����L���O�f�[�^���
 *
 *	��GNSRank_GetRankingData()�֐���p���Ď擾����
 *	�@�������̈���J������
 */
GLOBAL void GNSRank_FreeRankingData(GNS_RANKING* dat);

/**
 *	@brief	�M�l�X�����L���O�f�[�^�Z�b�g
 *
 *	�����L���O�\�[�g�ς݃f�[�^��GNS_RANKING�^�Ɋi�[����
 *	���n���A�Z�[�u�f�[�^�ɃZ�b�g����
 */
GLOBAL void GNSRank_SetRankingData(GUINNESS* gns,GNSID id,GNS_RANKING* dat);


#ifdef PM_DEBUG
/**
 *	@brief	�f�o�b�O��p�@�M�l�X�����L���O�f�[�^�@�_�~�[����
 */
GLOBAL void DebugGNSRank_MakeDmyRankingData(GUINNESS* gns);

#endif	//PM_DEBUG





#endif	//__H_GUINNESS_H__

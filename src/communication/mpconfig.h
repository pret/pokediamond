#ifndef ___MPCONFIG_H___
#define ___MPCONFIG_H___
/**
 * @version "$Id: mpconfig.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpconfig.h
 * @brief MP�����ʐM���C�u���� �R���t�B�O���[�V������`
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif

/* MP�ʐM�Ŏg�p����DMA�ԍ� */  
#define		MP_DMA_NO			(2)	// GX����DMA�ԍ��Əd�Ȃ�Ȃ��悤����

/* �g�p�|�[�g */ 
#define		MP_DEFAULT_PORT			(4)	// �|�[�g�ԍ�( 4�`7 )

/* �|�[�g�v���C�I���e�B */
#define		MP_DEFAULT_PORT_PRIO		(2)	// �|�[�g�̗D��x( 0�`3 )

/* �r�[�R���Ԋu */
#define		MP_DEFAULT_BEACON_PERIOD	(200)
  
/* MP�ʐM�pGGID */  
#define		MP_GGID				(0x00000178)

/* �ő�ڑ��q�@�� */  
#define		MP_CONNECT_CHILD_MAX		(9)

/* �e�@���M�f�[�^�T�C�Y */  
#define		MP_PARENT_DATA_SIZE		(64)  

/* �q�@���M�f�[�^�T�C�Y */
#define		MP_CHILD_DATA_SIZE		(64)  

  
#define		MP_SEND_DATA_SIZE		(64)  
  
/* �q�@�̍ő匟���e�@�� */
#define		MP_SIZE_RECEIVE_MP_PARENT_LIST	(8)

/* �e�@�̍ő�ڑ��q�@�� */
#define		MP_SIZE_RECEIVE_MP_CHILD_LIST	MP_SIZE_RECEIVE_MP_PARENT_LIST

  
/*  */
#define		MP_NUM_RECEIVE_MP_RETRY		(28)


/* �d�g�g�p���v�����̌v�����ԁims�j */
#define		MP_MEASURE_TIME			(30)

/* �d�g�g�p���v�����샂�[�h */
#define		MP_MEASURE_MODE			(3)	/* �L�����A�Z���X��ED�l�̘_���a */
  
/* �d�g�g�p���v�����̓d�g���x���� */  
#define		MP_MEASURE_ED_THRESHOLD		(17)

  
#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___MPCONFIG_H___

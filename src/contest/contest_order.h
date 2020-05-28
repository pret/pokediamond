//==============================================================================
/**
 * @file	contest_order.h
 * @brief	�R���e�X�g�ʐM����M�̃w�b�_
 * @author	matsuda
 * @date	2005.12.13(��)
 */
//==============================================================================
#ifndef __CONTEST_ORDER_H__
#define __CONTEST_ORDER_H__


//==============================================================================
//	�萔��`
//==============================================================================
///select_breeder�̃p�����[�^
enum{
	CSELECT_ALL = 0xff,		///<�S�����Ώ�
	CSELECT_SERVER = 0xfe,	///<�T�[�o�[���Ώ�
};

///���M�p�o�b�t�@�T�C�Y
#define CO_TRANSMIT_BUF_SIZE		(512)
///��M�p�o�b�t�@�T�C�Y
#define CO_RECEIVE_BUF_SIZE		(CO_TRANSMIT_BUF_SIZE)


//==============================================================================
//	�\���̒�`
//==============================================================================
///�R���e�X�g����M�\����
typedef struct{
	const struct _CON_ORDER_FUNC *func_tbl;		///<���߃f�[�^�e�[�u���ւ̃|�C���^
	u16 func_tbl_max;				///<func_tbl�̐�
	
	u8 my_breeder_no;
	u8 sio_flag;					///<TRUE�F�ʐM��
	u8 server_no;					///<�T�[�o�[�̃u���[�_�[�ԍ�
	
	u32 request_bit;				///<���߂��o���Ă���r�b�g
	u8 transmit_buf[CO_TRANSMIT_BUF_SIZE];	///<���M�p�o�b�t�@
	u8 receive_buf[CC_NETID_MAX][CO_RECEIVE_BUF_SIZE];	///<��M�p�o�b�t�@
	u8 transmit_flag;				///<TRUE�F���M�҂��B�@FALSE:�V���ȃf�[�^�Z�b�g�\
	u8 receive_flag[CC_NETID_MAX];				///<TRUE�F�f�[�^��M����
	u8 answer_count;				///<�Ԏ����󂯎���������J�E���g
}CONTEST_ORDER_WORK;

///�Ԏ���M�o�b�t�@���܂Ƃ߂��\����
typedef struct{
	void *data[BREEDER_MAX];
}CO_ANSDAT;

//--------------------------------------------------------------
/**
 * ���M�p�o�b�t�@�̃w�b�_
 */
//--------------------------------------------------------------
typedef struct{
	u16 data_size;			///<���M�f�[�^�T�C�Y
	u16 order_no;			///<���ߔԍ�
	u8 select_breeder;		///<���ߑΏۂ̃u���[�_�[�ԍ� or ASELECT_???
	u8 bit_no;				///<���N�G�X�g�r�b�g�ԍ�
	u8 type;				///<���M�^�C�v(TRANSMIT_TYPE_???)
	
	u8 dummy[1];
}CORDER_HEAD;

///���ߑ���M�p�֐��|�C���^�\����
typedef struct _CON_ORDER_FUNC{
	///���ߑ��M�֐�(���M��)
	int (* request_func)(CONTEST_ORDER_WORK *, void *, int, void *);
	///���ߎ�M�֐�(���M��)
	void (* receive_func)(CONTEST_ORDER_WORK *, void *, const CORDER_HEAD *, void *);
	///�Ԏ���M�֐�(���M��) �Ԏ����󂯎�邾���Ńf�[�^�̎󂯎�肪�Ȃ��Ȃ�NULL��OK
	void (* answer_func)(CONTEST_ORDER_WORK *, void *, const CORDER_HEAD *, CO_ANSDAT *, int);
}CON_ORDER_FUNC;

///����M���[�N�������f�[�^
typedef struct{
	const struct _CON_ORDER_FUNC *func_tbl;		///<���߃f�[�^�e�[�u���ւ̃|�C���^
	u16 func_tbl_max;				///<func_tbl�̐�
	
	u8 my_breeder_no;
	u8 sio_flag;					///<TRUE�F�ʐM��
	u8 server_no;					///<�T�[�o�[�̃u���[�_�[�ԍ�
}CO_INIT_DATA;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern u8 CO_RequestBitNumCheck(CONTEST_ORDER_WORK *cow);
extern BOOL CO_RequestBitCheck(CONTEST_ORDER_WORK *cow, int bit_no);
extern int CO_OrderSet(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
extern BOOL CO_TransmitCheckExe(CONTEST_ORDER_WORK *cow);
extern int CO_RecieveCheckExe(CONTEST_ORDER_WORK *cow, void *syswork);
extern int CO_REQUEST_TransmitBufferSet(CONTEST_ORDER_WORK *cow, u8 select_breeder, u16 order_no, void *data, int data_size);
extern void CO_ANSWER_TransmitBufferSet(CONTEST_ORDER_WORK *cow, const CORDER_HEAD *req_head, void *data, int data_size);
extern void CO_WorkInit(CONTEST_ORDER_WORK *cow, const CO_INIT_DATA *initdata);
extern BOOL CO_AnswerCountCheck(CONTEST_ORDER_WORK *cow, int answer_num, int my_breeder, int server_breeder);



#endif	//__CONTEST_ORDER_H__


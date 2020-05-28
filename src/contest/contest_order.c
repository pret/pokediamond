//==============================================================================
/**
 * @file	contest_order.c
 * @brief	�R���e�X�g�ʐM����M
 * @author	matsuda
 * @date	2005.12.13(��)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "battle/battle_common.h"
#include "contest_order.h"
#include "communication/communication.h"
#include "comm_command_contest.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�����ɖ��߂��o���鐔(���t���[���ɏo���閽�߂�1��)
#define CONTEST_ORDER_SAME_MAX		(32)

///���M�^�C�v
enum{
	TRANSMIT_TYPE_REQUEST,		///<����
	TRANSMIT_TYPE_ANSWER,		///<�Ԏ�
};



//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g����M���[�N������
 *
 * @param   cow				�R���e�X�g����M���[�N�ւ̃|�C���^
 * @param   initdata		�������f�[�^
 */
//--------------------------------------------------------------
void CO_WorkInit(CONTEST_ORDER_WORK *cow, const CO_INIT_DATA *initdata)
{
	MI_CpuClear8(cow, sizeof(CONTEST_ORDER_WORK));
	cow->func_tbl = initdata->func_tbl;
	cow->func_tbl_max = initdata->func_tbl_max;
	cow->my_breeder_no = initdata->my_breeder_no;
	cow->sio_flag = initdata->sio_flag;
	cow->server_no = initdata->server_no;
}


//--------------------------------------------------------------
/**
 * @brief   ���N�G�X�g�r�b�g���Z�b�g����
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static int CO_RequestBitSet(CONTEST_ORDER_WORK *cow)
{
	int bit_no;

	for(bit_no = 0; bit_no < CONTEST_ORDER_SAME_MAX; bit_no++){
		if((cow->request_bit & (1 << bit_no)) == 0){
			cow->request_bit |= 1 << bit_no;
			return bit_no;
		}
	}
	
	GF_ASSERT(0 && "�ő哯�����M���ߐ��𒴂��Ă��܂�\n");
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief   �w��̃��N�G�X�g�r�b�g�����Z�b�g����
 *
 * @param   syswork		�e����Ǘ����[�N�ւ̃|�C���^
 * @param   bit_no		�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static void CO_RequestBitReset(CONTEST_ORDER_WORK *cow, int bit_no)
{
	cow->request_bit &= 0xffffffff ^ (1 << bit_no);
}

//--------------------------------------------------------------
/**
 * @brief   ���N�G�X�g�r�b�g�����������Ă��邩�`�F�b�N����
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @retval  �����Ă���r�b�g��
 */
//--------------------------------------------------------------
u8 CO_RequestBitNumCheck(CONTEST_ORDER_WORK *cow)
{
	return MATH_CountPopulation(cow->request_bit);
}

//--------------------------------------------------------------
/**
 * @brief   �w��r�b�g�ԍ��̃��N�G�X�g�r�b�g�������Ă��邩�m�F
 *
 * @param   syswork		�e����Ǘ����[�N�ւ̃|�C���^
 * @param   bit_no		�r�b�g�ԍ�
 *
 * @retval  TRUE:�r�b�g�������Ă���B�@FALSE:�r�b�g�������Ă���
 */
//--------------------------------------------------------------
BOOL CO_RequestBitCheck(CONTEST_ORDER_WORK *cow, int bit_no)
{
	if(cow->request_bit & (1 << bit_no)){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ���M�o�b�t�@�ɑ��M�f�[�^���Z�b�g
 *
 * @param   apw					���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   select_breeder		�Ώۃu���[�_�[
 * @param   order_no			���ߔԍ�
 * @param   data				���M�f�[�^�̃|�C���^(�Ȃ��ꍇ��NULL)
 * @param   data_size			���M�f�[�^�T�C�Y
 * 
 * @retval	�o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
int CO_REQUEST_TransmitBufferSet(CONTEST_ORDER_WORK *cow, u8 select_breeder, u16 order_no, void *data, int data_size)
{
	CORDER_HEAD trans_head;
	
//	OS_TPrintf("���M�o�b�t�@�ɃZ�b�g�����f�[�^�̃T�C�Y��%d\n", data_size);
	GF_ASSERT(sizeof(CORDER_HEAD) + data_size <= CO_TRANSMIT_BUF_SIZE);
	
	//���M�o�b�t�@�N���A
	MI_CpuClear8(cow->transmit_buf, CO_TRANSMIT_BUF_SIZE);

	//�w�b�_�쐬
	trans_head.select_breeder = select_breeder;
	trans_head.order_no = order_no;
	trans_head.bit_no = CO_RequestBitSet(cow);
	trans_head.type = TRANSMIT_TYPE_REQUEST;
	trans_head.data_size = data_size + sizeof(CORDER_HEAD);
	
	//�f�[�^�Z�b�g
	MI_CpuCopy32(&trans_head, cow->transmit_buf, sizeof(CORDER_HEAD));
	MI_CpuCopy8(data, &cow->transmit_buf[sizeof(CORDER_HEAD)], data_size);
	
	cow->answer_count = 0;
	cow->transmit_flag = TRUE;
	
	return trans_head.bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���M�o�b�t�@�ɕԎ��f�[�^���Z�b�g
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head		���N�G�X�g�w�b�_�̃|�C���^
 * @param   data			���M�f�[�^�̃|�C���^(�Ȃ��ꍇ��NULL)
 * @param   data_size		���M�f�[�^�T�C�Y
 */
//--------------------------------------------------------------
void CO_ANSWER_TransmitBufferSet(CONTEST_ORDER_WORK *cow, const CORDER_HEAD *req_head, void *data, int data_size)
{
	CORDER_HEAD answer_head;
	
	GF_ASSERT(sizeof(CORDER_HEAD) + data_size <= CO_TRANSMIT_BUF_SIZE);
	
	//���M�o�b�t�@�N���A
	MI_CpuClear8(cow->transmit_buf, CO_TRANSMIT_BUF_SIZE);

	//�w�b�_�쐬
	answer_head = *req_head;
	answer_head.select_breeder = CSELECT_SERVER;
	answer_head.type = TRANSMIT_TYPE_ANSWER;
	answer_head.data_size = data_size + sizeof(CORDER_HEAD);
	
	//�f�[�^�Z�b�g
	MI_CpuCopy32(&answer_head, cow->transmit_buf, sizeof(CORDER_HEAD));
	if(data != NULL){
		MI_CpuCopy8(data, &cow->transmit_buf[sizeof(CORDER_HEAD)], data_size);
	}
	
	cow->transmit_flag = TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ��M�o�b�t�@����w�b�_�f�[�^�̃A�h���X�ƁA�f�[�^�o�b�t�@�̃A�h���X�����o��
 *
 * @param   syswork		�e����Ǘ����[�N�ւ̃|�C���^
 * @param   net_id		�擾����o�b�t�@�̃l�b�gID
 * @param   req_head	����M�w�b�_�̃|�C���^��������|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^��������|�C���^
 */
//--------------------------------------------------------------
static void CO_RECIEVE_BufferDataGet(CONTEST_ORDER_WORK *cow, int net_id, CORDER_HEAD **req_head, void **data)
{
	*req_head = (void*)cow->receive_buf[net_id];
	*data = &cow->receive_buf[net_id][sizeof(CORDER_HEAD)];
}

//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M���o�����Ԃ��`�F�b�N
 *
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 *
 * @retval  TRUE:�o����B�@FALSE:�o���Ȃ�
 */
//--------------------------------------------------------------
static BOOL COSub_OrderPossibleCheck(CONTEST_ORDER_WORK *cow)
{
	if(cow->transmit_flag == TRUE){
		return FALSE;
	}
	
	if(cow->sio_flag == FALSE){
		return TRUE;
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M�R�}���h�����s����
 *
 * @param   syswork		�e����Ǘ����[�N�ւ̃|�C���^
 * @param   order_no	���ߔԍ�(AORDER_NO_???)
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  TRUE:���M�����B�@FALSE:���M�҂�
 */
//--------------------------------------------------------------
int CO_OrderSet(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	if(COSub_OrderPossibleCheck(cow) == FALSE){
		return FALSE;
	}
	
	GF_ASSERT(order_no < cow->func_tbl_max);
	cow->func_tbl[order_no].request_func(cow, syswork, order_no, work);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   select_breeder�Ŏw�肳��Ă���̂������Ȃ̂��`�F�b�N����
 *
 * @param   my_breeder_no		�����̃u���[�_�[�ԍ�
 * @param   server_no			�T�[�o�[�̃u���[�_�[�ԍ�
 * @param   select_breeder		�I���u���[�_�[
 *
 * @retval  TRUE:�����B�@FALSE:�����ł͂Ȃ�
 */
//--------------------------------------------------------------
static BOOL COSub_SelectBreederCheck(int my_breeder_no, int server_no, int select_breeder)
{
	if(my_breeder_no == select_breeder || select_breeder == CSELECT_ALL
			|| (select_breeder == CSELECT_SERVER && server_no == my_breeder_no)){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ���M�o�b�t�@�Ƀf�[�^���i�[����Ă���Α��M���s��
 *
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 *
 * @retval  TRUE:���M�����B�@FALSE:���M���Ă��Ȃ�
 */
//--------------------------------------------------------------
BOOL CO_TransmitCheckExe(CONTEST_ORDER_WORK *cow)
{
	if(cow->transmit_flag == FALSE){
		return FALSE;
	}
	
	if(cow->sio_flag == FALSE){
		//����������M
		MI_CpuCopy8(cow->transmit_buf, cow->receive_buf[cow->my_breeder_no], CO_TRANSMIT_BUF_SIZE);
		cow->receive_flag[cow->my_breeder_no] = TRUE;

		MI_CpuClear8(cow->transmit_buf, CO_TRANSMIT_BUF_SIZE);
		cow->transmit_flag = FALSE;
		return TRUE;
	}
	else{
		CORDER_HEAD *chead;
		
		chead = (void*)cow->transmit_buf;
	#if DEBUG_SIO_WAIT
		if((gf_rand() % 10) != 0){
			return FALSE;
		}
	#endif
//		if(CommSendData(CC_NORMAL_DATA, cow->transmit_buf, chead->data_size) == TRUE){
		if(CommSendHugeData(CC_NORMAL_DATA, cow->transmit_buf, chead->data_size) == TRUE){
			OS_TPrintf("�f�[�^���M����\n");
			//��HugeData�ő��M����ꍇ�͑��M���I���܂ŕێ�����K�v������̂ŃN���A���Ȃ�
			//MI_CpuClear8(cow->transmit_buf, CO_TRANSMIT_BUF_SIZE);
			cow->transmit_flag = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ���߃R�}���h����M�������m�F���A��M���Ă���Ύ��s
 *
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 *
 * @retval  TRUE:���ߎ��s�����B�@FALSE:��M�Ȃ�
 */
//--------------------------------------------------------------
int CO_RecieveCheckExe(CONTEST_ORDER_WORK *cow, void *syswork)
{
	CORDER_HEAD *req_head;
	void *data;
	CO_ANSDAT ansdat;
	int i;
	
	MI_CpuClear8(&ansdat, sizeof(CO_ANSDAT));
	
	if(1){	//cow->sio_flag == FALSE){
		for(i = 0; i < CC_NETID_MAX; i++){
			if(cow->receive_flag[i] == TRUE){
				//��M�f�[�^�擾
				CO_RECIEVE_BufferDataGet(cow, i, &req_head, &data);
				//�������ΏۂɊ܂܂�Ă��邩�m�F
				if(COSub_SelectBreederCheck(cow->my_breeder_no, 
						cow->server_no, req_head->select_breeder) == TRUE){
					//���߃R�}���h���p�ӂ���Ă��邩�m�F
					if(req_head->order_no < cow->func_tbl_max){
						//��M���ߎ��s
						if(req_head->type == TRANSMIT_TYPE_REQUEST){
							cow->func_tbl[req_head->order_no].receive_func(cow, syswork, req_head, data);
						}
						else{
							if(cow->func_tbl[req_head->order_no].answer_func != NULL){
								ansdat.data[i] = data;
								cow->func_tbl[req_head->order_no].answer_func(cow, syswork, req_head, &ansdat, i);
							}
							//�Ԏ��������̂Ńr�b�g���Ƃ�
							CO_RequestBitReset(cow, req_head->bit_no);
							//�Ԏ��������̂ŃJ�E���g�C���N�������g
							cow->answer_count++;
						}
					}
					else{
						OS_TPrintf("�p�ӂ���Ă��Ȃ����ߔԍ�����M�����̂ŉ��������ɖ������܂�\n");
					}
				}
				
				//��M�o�b�t�@�N���A
				cow->receive_flag[i] = FALSE;
				MI_CpuClear8(cow->receive_buf[i], CO_RECEIVE_BUF_SIZE);
				return TRUE;
			}
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �Ԏ���M�J�E���g���w�萔�ɒB���Ă��邩�`�F�b�N
 *
 * @param   cow				�R���e�X�g����M���[�N�ւ̃|�C���^
 * @param   answer_num		�w���M�l��
 * @param   my_breeder		�����̃u���[�_�[�ԍ�
 * @param   server_breeder	�T�[�o�[�̃u���[�_�[�ԍ�
 *
 * @retval  TRUE:��M���Ă���B�@FALSE�F�w�萔�ɒB���Ă��Ȃ�
 *
 * �T�[�o�[��p���߂ł��B�q�@���Ă񂾏ꍇ�͏��TRUE���Ԃ�܂��B
 */
//--------------------------------------------------------------
BOOL CO_AnswerCountCheck(CONTEST_ORDER_WORK *cow, int answer_num, int my_breeder, int server_breeder)
{
	if(my_breeder != server_breeder){
		return TRUE;	//�T�[�o�[��p���߂Ȃ̂ŁA�������T�[�o�[�łȂ����͏�Ɍ��ʂ�TRUE
	}
	
	if(cow->answer_count >= answer_num){
		return TRUE;
	}
	return FALSE;
}

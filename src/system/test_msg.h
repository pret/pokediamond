/*---------------------------------------------------------------------------*
	File:    test_msg.h

	���b�Z�[�W��`�t�@�C��
	 by MessageEditor ver.4.8.5

 *---------------------------------------------------------------------------*/

#ifndef TEST_MSG_H_
#define TEST_MSG_H_

/* ���b�Z�[�WID */
#define JMS_0001             0x00000000         
#define JMS_0002             0x00000001         
#define JMS_MISHIRO_001      0x00010000         
#define JMS_MISHIRO_002      0x00010001         
#define JMS_MISHIRO_003      0x00010002         

/* �N�G��ID */

/* �t���[�m�[�h */

/* �^�O������� */

/* ���b�Z�[�W�G���g���\���� */
typedef struct JMSMesgEntry JMSMesgEntry;
struct JMSMesgEntry
{
    u32    mesgOffset;                          /* ���{�� */
};


#endif /* TEST_H_ */

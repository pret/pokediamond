/*---------------------------------------------------------------------------*
	File:    test_msg.h

	メッセージ定義ファイル
	 by MessageEditor ver.4.8.5

 *---------------------------------------------------------------------------*/

#ifndef TEST_MSG_H_
#define TEST_MSG_H_

/* メッセージID */
#define JMS_0001             0x00000000         
#define JMS_0002             0x00000001         
#define JMS_MISHIRO_001      0x00010000         
#define JMS_MISHIRO_002      0x00010001         
#define JMS_MISHIRO_003      0x00010002         

/* クエリID */

/* フローノード */

/* タグ特性情報 */

/* メッセージエントリ構造体 */
typedef struct JMSMesgEntry JMSMesgEntry;
struct JMSMesgEntry
{
    u32    mesgOffset;                          /* 日本語 */
};


#endif /* TEST_H_ */

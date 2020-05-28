#ifndef	__COMM_UNION_DEF_H__
#define	__COMM_UNION_DEF_H__

//----------------------------------------------
// Union_ConnectResultGet���Ԃ��l
//----------------------------------------------
#define UNION_CONNECT_BUSY			( 0	) ///< �r��
#define UNION_CONNECT_SUCCESS   	( 1	) ///< �ڑ�����
#define UNION_CONNECT_FAILED		( 2	) ///< �ڑ����s
#define UNION_CONNECT_PARENT		( 3 ) ///< �q�@�Ƃ��Đڑ����ɂ������̂ɐe�@�ɂȂ���

#define UNION_SELECT_EVENT			( 0 ) ///< ���j�I�����[���ōs�����e
#define UNION_YESNO_RESULT			( 1 ) ///< ���j�I�����[���ŕ������͂��E�������̌���

// �q�@�̑I�������J�n�C�x���g�����̔ԍ�
#define UNION_CHILD_SELECT_CARD		( 1 ) ///< �ڑ���̑I�����Łu�������v
#define UNION_CHILD_SELECT_BATTLE	( 2 ) ///< �ڑ���̑I�����Łu��������v
#define UNION_CHILD_SELECT_TRDE		( 3 ) ///< �ڑ���̑I�����Łu��������v
#define UNION_CHILD_SELECT_OEKAKI	( 4 ) ///< �ڑ���̑I�����Łu���������v
#define UNION_CHILD_SELECT_RECORD	( 5 ) ///< �ڑ���̑I�����Łu���R�[�h�v
#define UNION_CHILD_SELECT_GURUGURU	( 6 ) ///< �ڑ���̑I�����Łu���邮������v
#define UNION_CHILD_SELECT_CANCEL	( 7 ) ///< �ڑ���̑I�����Łu��߂�v
#define UNION_PARENT_SELECT_CANCEL	( 8 ) ///< �e�@����L�����Z��������


// �b�������J�n���̃r�[�R���m�F���ʗp��`
#define UNION_PARENT_CONNECT_OK			(  1 )	// ���j�I���ڑ��g���C�J�n
#define UNION_PARENT_OEKAKI_OK			(  2 )	// ���G���������ʐM�g���C�J�n
#define UNION_PARENT_RECORD_OK			(  3 )	// ���R�[�h�����ʐM�g���C�J�n
#define UNION_PARENT_GURUGURU_OK		(  4 )	// ���邮����������ʐM�g���C�J�n
#define UNION_PARENT_CONNECT_NG			(  5 )	// ���ɐڑ��ς݂Ȃ̂Ōq����Ȃ� �� ��b��

// �g���[�i�[����ݒ肷��Ƃ��Ɏg�p�����`		
#define UNION_TALK_CHILD				( 0 )	// �b����������̖��O�ݒ�i�����̂͘b�������鑊��̖��O�j
#define UNION_TALK_PARENT				( 1 )	// �b������������̖��O�ݒ�i�����̂͘b�������Ă�������̖��O�j

// �o�g���J�n���̃|�P�������X�g�I���̌��ʂ�Ԃ�
#define UNION_BATTLE_POKELIST_OK		( 1 )	// �|�P������I������
#define UNION_BATTLE_POKELIST_NG		( 2 )	// ��߂��I������

// �o�g���J�n���̃|�P�������X�g�I���̌��ʂ�Ԃ�
#define UNION_BATTLE_OK					( 0 )	
#define UNION_BATTLE_MY_CANCEL			( 1 )	// �������퓬���L�����Z������
#define UNION_BATTLE_PARTNER_CANCEL		( 2 )	// ���肪�퓬���L�����Z������

// �󋵂ɉ����ĉ�b�ԍ����擾���邽�߂̏󋵐ݒ��`
#define UNION_NO_CONNECT_TALK			( 0 )	// �P�Ȃ闧���b�i�ڑ��ł��Ȃ�����̘b�𕷂��j
#define UNION_CONNECTED_START_TALK		( 1 )	// �V�Ԏ��ɂȂ����̂Łu���Ⴀ�A�͂��߂悤�v�Ƃ�����b
#define UNION_CONNECT_SUCCESS_TALK		( 2 )	// �ڑ��ɐ�������
#define UNION_TALK_CANCEL_CARD			( 3 )   // �J�[�h��f��ꂽ
#define UNION_TALK_CANCEL_OEKAKI		( 4 )   // ����������f��ꂽ
#define UNION_TALK_CANCEL_BATTLE		( 5 )   // ���������f��ꂽ
#define UNION_TALK_CANCEL_TRADE			( 6 )   // ���������f��ꂽ
#define UNION_TALK_CANCEL_GURUGURU		( 7 )   // ���邮���f��ꂽ
#define UNION_TALK_CANCEL_RECORD		( 8 )   // ���R�[�h��f��ꂽ
#define UNION_CONNECT_ANSWER_WAIT		( 9 )   // �V�т����߂���A����̕Ԏ���҂�

#define UNION_JOIN_OEKAKI_TALK			( 10 )
#define UNION_JOIN_RECORD_TALK			( 11 )
#define UNION_JOIN_GURUGURU_TALK		( 12 )

#define UNION_SUCCESS_OEKAKI_JOIN		( 13 )
#define UNION_SUCCESS_RECORD_JOIN		( 14 )
#define UNION_SUCCESS_GURUGURU_JOIN		( 15 )

#define UNION_JOIN_OEKAKI_NO			( 16 )
#define UNION_JOIN_RECORD_NO			( 17 )
#define UNION_JOIN_GURUGURU_NO			( 18 )

#define UNION_CONNECT_BATTLE_REJECT		( 19 )
#define UNION_CONNECT_TRADE_REJECT		( 20 )
#define UNION_CONNECT_GURUGURU_REJECT	( 21 )

#define UNION_SELECT_NEXT_TALK			( 22 )
#define UNION_TALK_CONNECT_CANCEL		( 23 )	// �����Ŏq�@���؂����i�b�����������j
#define UNION_TALK_CONNECT_CANCELED		( 24 )	// ����ɐ؂�ꂽ�i�b�����������j

// ���j�I�����[���ŒʐM�ŗV�ԓ��e�����܂������Ƀt�F�[�h�A�E�g����܂ł̊�
#define UNION_EVNET_PRE_WAIT			( 30 )  // 1�b��



// �ʐM�J�n�������̓����ԍ�
#define UNION_SYNCHRO_CONNECTSTART		( 100 )

// �ʐM�I���̎��̓����ԍ�
#define UNION_SYNCHRO_CONNECTEND		( 101 )

// �������񂪐���������A�|�P�������X�g����߂��Ă���̂�҂��߂̓���
#define UNION_SYNCHRO_POKELIST			( 102 )

// �J�[�h��������O�̓���
#define UNION_SYNCHRO_CARDEND			( 103 )

#endif //__COMM_UNION_DEF_H__
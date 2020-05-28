#=============================================================================================
#
#	�t�B�[���h�A�C�e���X�N���v�g�R���o�[�^
#
#	_EVENT_DATA�L�q��fld_item.ev�ɏo�͂���
#
#	�t���O��`��fld_item_flag.h�ɏo�͂���
#
#	05.11.04 Satoshi Nohara
#
#=============================================================================================
BEGIN{
	#=================================================================
	#
	#�A�C�e����`�t�@�C���ǂݍ���
	#
	#=================================================================
	ITEMSYM_H = "../../../include/itemtool/itemsym.h"

	#getline = �P�s�ǂݍ���
	#�P�͖߂�l
	while ( 1 == getline < ITEMSYM_H ) {
		if ( NF == 7 && $1 =="#define" ) {
			ItemName[$7] = $2
		}
	}
	close(ITEMSYM_H)

	#�������ރt�@�C��
	file1 = "fld_item.ev"		#�X�N���v�g
	#file2 = "fld_item_flag.h"	#�t���O

	print "//====================================================================" > file1
	print "//						�t�B�[���h�A�C�e��" >> file1
	print "//" >> file1
	print "//	���t�B�[���h�A�C�e�������Ђ傤" >> file1
	print "//		fld_item.xls" >> file1
	print "//" >> file1
	print "//	���R���o�[�g���s" >> file1
	print "//		fld_item(.bat)" >> file1
	print "//" >> file1
	print "//	���X�V�����t�@�C��" >> file1
	print "//		fld_item.xls" >> file1
	print "//		fld_item.ev" >> file1
	print "//		fld_item_def.h" >> file1
	print "//" >> file1
	print "//====================================================================" >> file1
	print "" >> file1
	print "\t.text" >> file1
	print "" >> file1
	print "\t.include	\"scr_seq_def.h\"" >> file1
	print "\t.include	\"../../../include/msgdata/msg_fld_item.h\"" >> file1
	print "" >> file1
	print "//--------------------------------------------------------------------" >> file1
	print "//						�X�N���v�g�{��" >> file1
	print "//--------------------------------------------------------------------" >> file1
	print "" >> file1
	print "//--------------------------------------------------------------------" >> file1
	print "//						�X�N���v�g�e�[�u��" >> file1
	print "//--------------------------------------------------------------------" >> file1

	#fld_item_flag.h-------------------------------------------------------
	#print "//�t�B�[���h��̃A�C�e���̃t���O" > file2
	#print "#define FV_BALL_START (FV_FLAG_START+300)" > file2
}

NR >= 4{

	#���ڐ��`�F�b�N
	if( NF < 6 ) next

	#-----------------------------------------------------------------
	#
	#�t���O�}�b�N�X�𒴂��Ă�����G���[(06/01/26 MAX = 256 )
	#
	#-----------------------------------------------------------------
	if( $6 > 255 ){
		printf("�t���O�̍ő吔�𒴂��Ă��܂��I\n") >> "/dev/stderr"
		exit				#�r���ŏI��
	}

	#-----------------------------------------------------------------
	#
	#�����ԍ�(�t���O�i���o�[�̃I�t�Z�b�g)���g�p���ĂȂ����`�F�b�N
	#
	#-----------------------------------------------------------------
	if ( $6 in ID_List ) {

		#�������l���`���Ă����������ꍇ
		printf("ERROR! �����l�̒�`������܂�\n") >> "/dev/stderr"
		printf("[%s] [%s] �t���O%s\n",ID_List[$6],$1,$6) >> "/dev/stderr"

		exit				#�r���ŏI��
	}

	ID_List[$6] = $1		#�v�f�Ƃ��ēo�^

	#-----------------------------------------------------------------
	#
	#
	#
	#-----------------------------------------------------------------
	if( $1 == "�}�b�v��" )	next
	if( $1 ~ "�A�C�e��" )	next

	print "_EVENT_DATA\t\t" "ev_fld_item_" $6 >> file1

	#fld_item_flag.h--------------------------------------------------------------
	#print "#define FV_BALL_" $6 " (FV_BALL_START+" $6 ")" >> file2
}

END{
	print "_EVENT_DATA\t\t" "ev_fld_item2" >> file1
	print "_EVENT_DATA_END\t\t\t\t//�I��" >> file1
	print "" >> file1
}


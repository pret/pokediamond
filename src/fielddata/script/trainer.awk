#=============================================================================================
#
#	�g���[�i�[�X�N���v�g�R���o�[�^
#
#	_EVENT_DATA�L�q��trainer.ev�ɏo�͂���
#
#	05.12.16 Satoshi Nohara
#
#=============================================================================================
BEGIN{
	flag = 0
	count = 0

	print "//===================================================================="
	print "//"
	print "//						�g���[�i�[�f�[�^"
	print "//"
	print "//	��include/battle/trno_def.h�����ɃR���o�[�g���Ă��܂�"
	print "//"
	print "//	���R���o�[�g���s"
	print "//		trainer(.bat)"
	print "//"
	print "//	���X�V�����t�@�C��"
	print "//		trainer.ev"
	print "//		trainer_def.h"
	print "//"
	print "//===================================================================="
	print ""

	print "\t.text"
	print ""
	print "\t.include	\"scr_seq_def.h\""
	print "\t.include	\"../../../include/poketool/tr_tool.h\""
	print ""

	print "//--------------------------------------------------------------------"
	print "//					    �X�N���v�g�{��"
	print "//--------------------------------------------------------------------"
	print ""

	print "//--------------------------------------------------------------------"
	print "//					    �X�N���v�g�e�[�u��"
	print "//--------------------------------------------------------------------"
}

{
	if( NF < 2 ){
		next
	}

	if( flag == 0 ){

		#�J�n�ʒu�`�F�b�N
		if( ($1 ~ "#define") && ($2 ~ "__TRNO_DEF_H_") ){
			flag = 1
			next
		}
		next
	}

	#�I���ʒu�`�F�b�N
	if( ($1 ~ "#endif") && ($2 ~ "__TRNO_DEF_H_") ){
		print "_EVENT_DATA\tev_trainer_talk_battle"
		print "_EVENT_DATA\tev_trainer_move_battle"
		#print "_EVENT_DATA\tev_trainer_talk_after"
		print "_EVENT_DATA_END"
		exit
	}

	tmp[count] = $2
	count++
	print "_EVENT_DATA\tev_" $2
}

END{
	print ""

	for( i=0; i < count ;i++ ){
		print "ev_" tmp[i] ":"
	}

	#print ""
	#print "\t.include	\"trainer2.ev\""
	#print ""
}


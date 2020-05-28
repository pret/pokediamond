#=======================================================================================
#
#	.gmm�t�@�C������A_EASY_OBJ_MSG�`����f���o��
#
#	05.10.04 Satoshi Nohara
#
#	"sign"���܂܂�Ă�����A_EASY_BOARD_MSG�ɂ���悤�ɂ���
#
#=======================================================================================
BEGIN{
	tmp_file = FIELNAME
	sub( "../../../convert/message/src/scenario/", "", tmp_file )		#"../.."�ƈ�v����܂ō폜
}

{
	diff_file = FILENAME

	sub( "../../../convert/message/src/scenario/", "", diff_file )		#"../.."�ƈ�v����܂ō폜

	if( tmp_file != diff_file ){
		tmp_file = FILENAME
		sub( "../../../convert/message/src/scenario/", "", tmp_file )	#"../.."�ƈ�v����܂ō폜
		basic_data_write()				#���`��
	}

	if( $0 ~ "<row id=" ){
		msg = $0
		sub( "<row id=\"", "", msg )	#gmm�t�@�C������
		sub( "\t", "", msg )
		sub(/\".*$/,"",msg)				#","�ȍ~���폜

		ev = msg
		sub( "msg", "ev", ev )			#ev�ɒu������

		#print msg
		#print ev

		print "/********************************************************************/"
		print "/*							???									*/"
		print "/********************************************************************/"
		print ev ":"

		#�Ŕ�������
		if( $0 ~ "sign" ){
			print "\t_EASY_BOARD_MSG\t" msg ",BOARD_TYPE_TOWN,0"
		}else{
			print "\t_EASY_OBJ_MSG\t" msg
		}

		print "\t_END"
		print ""
	}
}

#-----------------
#	���`��
#-----------------
function basic_data_write()
{
	print "//===================================================================="
	print "//"
	print "//						" diff_file
	print "//"
	print "//===================================================================="

	file = diff_file
	sub( ".gmm", "", file )

	print "\t.text"
	print ""
	#print "\t.include	\"usescript.h\""
	print "\t.include	\"scr_seq_def.h\""
	#print "\t.include	\"../../msgdata/scenario/" file ".h\""
	print ""

	print "//--------------------------------------------------------------------"
	print "//					     �X�N���v�g�{��"
	print "//--------------------------------------------------------------------"
	print ""

	print "//--------------------------------------------------------------------"
	print "//					     �X�N���v�g�e�[�u��"
	print "//--------------------------------------------------------------------"
	print "_EVENT_DATA		ev_" file
	print "_EVENT_DATA_END						//�I��"
	print ""
}


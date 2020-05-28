#=======================================================================================
#
#	.gmmファイルから、_EASY_OBJ_MSG形式を吐き出す
#
#	05.10.04 Satoshi Nohara
#
#	"sign"が含まれていたら、_EASY_BOARD_MSGにするようにした
#
#=======================================================================================
BEGIN{
	tmp_file = FIELNAME
	sub( "../../../convert/message/src/scenario/", "", tmp_file )		#"../.."と一致するまで削除
}

{
	diff_file = FILENAME

	sub( "../../../convert/message/src/scenario/", "", diff_file )		#"../.."と一致するまで削除

	if( tmp_file != diff_file ){
		tmp_file = FILENAME
		sub( "../../../convert/message/src/scenario/", "", tmp_file )	#"../.."と一致するまで削除
		basic_data_write()				#情報描画
	}

	if( $0 ~ "<row id=" ){
		msg = $0
		sub( "<row id=\"", "", msg )	#gmmファイル検索
		sub( "\t", "", msg )
		sub(/\".*$/,"",msg)				#","以降を削除

		ev = msg
		sub( "msg", "ev", ev )			#evに置き換え

		#print msg
		#print ev

		print "/********************************************************************/"
		print "/*							???									*/"
		print "/********************************************************************/"
		print ev ":"

		#看板だったら
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
#	情報描画
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
	print "//					     スクリプト本体"
	print "//--------------------------------------------------------------------"
	print ""

	print "//--------------------------------------------------------------------"
	print "//					     スクリプトテーブル"
	print "//--------------------------------------------------------------------"
	print "_EVENT_DATA		ev_" file
	print "_EVENT_DATA_END						//終了"
	print ""
}


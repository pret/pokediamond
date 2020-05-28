#=============================================================================================
#
#	トレーナースクリプトコンバータ
#
#	_EVENT_DATA記述をtrainer.evに出力する
#
#	05.12.16 Satoshi Nohara
#
#=============================================================================================
BEGIN{
	flag = 0
	count = 0

	print "//===================================================================="
	print "//"
	print "//						トレーナーデータ"
	print "//"
	print "//	●include/battle/trno_def.hを元にコンバートしています"
	print "//"
	print "//	●コンバート実行"
	print "//		trainer(.bat)"
	print "//"
	print "//	●更新されるファイル"
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
	print "//					    スクリプト本体"
	print "//--------------------------------------------------------------------"
	print ""

	print "//--------------------------------------------------------------------"
	print "//					    スクリプトテーブル"
	print "//--------------------------------------------------------------------"
}

{
	if( NF < 2 ){
		next
	}

	if( flag == 0 ){

		#開始位置チェック
		if( ($1 ~ "#define") && ($2 ~ "__TRNO_DEF_H_") ){
			flag = 1
			next
		}
		next
	}

	#終了位置チェック
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


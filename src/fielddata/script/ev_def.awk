#===========================================================================================
#
#	050826 Satoshi Nohara
#
#	*.evファイルから、スクリプトのIDを生成して、*_def.hに書き込む
#
#===========================================================================================
BEGIN{
	#コマンドラインの引数1
	name = ARGV[1]												#ファイル名取得(例 r203.ev)
	sub(/\..*$/,"",name)										#"."以降を削除(例 r203)

	#=================================================================
	#
	#スクリプトオフセット定義ファイル読み込み
	#
	#=================================================================
	SCR_OFFSET_H = "../../field/scr_offset.h"

	offset_i = 0

	#getline = １行読み込み
	#１は戻り値
	while ( 1 == getline < SCR_OFFSET_H ) {
		if ( NF == 4 && $1 =="#define" ) {

			if( $2 ~ "_END" ){
				#何もしない
			}else{
				#スクリプトファイル名
				temp = tolower( $2 )
				sub( "id_", "", temp );
				sub( "_offset", "", temp );
				OffsetName[offset_i] = temp
	
				#オフセットID
				temp = $3
				sub( /[(]/,"", temp );
				sub( /[)]/,"", temp );
				OffsetId[offset_i]	= temp
				offset_i++
			}
		}
	}
	close(SCR_OFFSET_H)

	#多重インクルードチェック
	name2 = toupper(name)										#大文字に統一
	print "#ifndef _" name2 "_DEF_H_" > name "_def.h"
	print "#define _" name2 "_DEF_H_\n" > name "_def.h"	

	#毎回コンバートをかけると、常に差分が出るので外した！
	#print strftime( "//%Y %m %d %H:%M:%S\n" ) > name "_def.h"	#コンバートした日付
	#printf( "//2005 10 14 19:49:31\n\n" ) > name "_def.h"

	printf( "//スクリプトデータID定義 \n" ) > name "_def.h"		#タイトル

	#####################################################################################

	#該当するファイルを探す
	j = 0
	start = 1									#"0"はSCRID_NULLで使用するので1にする！(06.01.20)
	print name

	for( j=0; j < offset_i ;j++ ){

		#print OffsetName[j]
		#print OffsetId[j]

		if( name == OffsetName[j] ){
			start = OffsetId[j];
			break;
		}
	}

	count = 0 + start
}

{
	#テーブル終了をチェック
	if( $1 ~ "EVENT_DATA_END" ){
		exit	#終了
	}

	#テーブル検索
	if( $1 ~ "EVENT_DATA" ){

		#ID用の名前
		id_name = $2
		#sub(/^[ev_]*/,"",id_name)				#先頭の"ev_"を削除(ev_egg → gg になってしまう)
		sub( "ev_", "", id_name)									#先頭の"ev_"を削除

		id_name2 = toupper(id_name)									#大文字に統一
		name2 = toupper(name)										#大文字に統一

		#05.12.06
		#トレーナーはダブルバトルのためにIDを2つオフセットを変えて出力する(+2000)
		#SXYに指定する時に、双子の左右でそれぞれ使う(_2)
		if( name ~ "trainer" ){											#trainer.ev
			print "#define\tSCRID_" id_name2 "\t\t" "(" count ")" > name "_def.h"	#ID_??
			print "#define\tSCRID_" id_name2 "_2\t" "(" count+2000 ")" > name "_def.h"	#ID_??
		}else{
			print "#define\tSCRID_" id_name2 "\t\t" "(" count ")" > name "_def.h"	#ID_??
		}

		count++
	}
}

END{
	#最大数の定義を追加する
	count = count - start
	print "#define\tSCRID_" name2 "_DATA_MAX\t\t" "(" count ")\t\t\/\/最大数" > name "_def.h"#ID_??

	#多重インクルードチェック
	print "\n#endif //_" name2 "_DEF_H_" > name "_def.h"#ID_??
}


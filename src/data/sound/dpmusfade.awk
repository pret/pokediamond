#===========================================================================================
#
#	060124 Satoshi Nohara
#
#	dpmusfade.xlsをコンバートして、
#	トラックフェードデータをdpmusfade.datに書き込む
#
#===========================================================================================

BEGIN{
	print "//----------------------------------------------------"
	print "//\tトラックフェードデータ"
	print "//----------------------------------------------------"
	print "//注意！ マイナス1をして0～15トラックとして扱っている"
	print "static const TRACK_FADE_DATA track_fade_tbl[] = {"
}

{
	#行数チェック
	if( NR < 2 ){
		next
	}

	#項目数チェック
	if( NF < 4 ){
		next
	}

	#変数初期化
	noon_start	= $4
	noon_end	= $4
	night_start = $5
	night_end	= $5

	#昼start
	sub( /\,.*$/, "", noon_start )				#","以降を削除
	sub( "\"", "", noon_start )					#"を削除

	#夜start
	sub( /\,.*$/, "", night_start )				#","以降を削除
	sub( "\"", "", night_start )				#"を削除

	for( i=0; i < 16 ;i++ ){

		#昼end
		if( noon_end ~ "," ){
			sub( /^[^,]*/, "", noon_end )		#","と一致するまで削除
			sub( /[,]/, "", noon_end )			#","と一致したら削除
		}

		#夜end
		if( night_end ~ "," ){
			sub( /^[^,]*/, "", night_end )		#","と一致するまで削除
			sub( /[,]/, "", night_end )			#","と一致したら削除
		}
	}

	sub( "\"", "", noon_end )					#"を削除
	sub( "\"", "", night_end )					#"を削除

	#マイナス1をして0～15トラックとして扱う
	if( noon_start == 0 ){						#"0"はデータなし
		noon_start = "TRACK_FADE_NONE"
		noon_end = "TRACK_FADE_NONE"
	}else{
		noon_start-=1
		noon_end-=1
	}

	if( night_start == 0 ){						#"0"はデータなし
		night_start = "TRACK_FADE_NONE"
		night_end = "TRACK_FADE_NONE"
	}else{
		night_start-=1
		night_end-=1
	}

	#出力
	tmp = $3
	sub( ".mid", "", tmp )
	name = toupper( tmp )
	print "\t{ SEQ_" name ",\t" noon_start ", " noon_end ", " night_start ", " night_end " },"
}

END{
	print "};"
	print "#define TRACK_FADE_TBL_MAX ( NELEMS(track_fade_tbl) )"
}


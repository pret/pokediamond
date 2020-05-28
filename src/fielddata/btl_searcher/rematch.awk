#=============================================================================================
#
#	バトルサーチャー(再戦)データコンバータ
#
#	06.05.15 Satoshi Nohara
#
#=============================================================================================
BEGIN{
	print "//再戦トレーナーデータ"
	print "//このファイルはコンバータが自動生成したものです\n"
	print "#ifndef _REMATCH_DAT_"
	print "#define _REMATCH_DAT_\n"

	print "const REMATCH_DATA RematchDataTbl[]={"

	tr_id[0] = "REMATCH_DATA_END"
	tr_id[1] = "REMATCH_DATA_END"
	tr_id[2] = "REMATCH_DATA_END"
	tr_id[3] = "REMATCH_DATA_END"
	tr_id[4] = "REMATCH_DATA_END"
	tr_id[5] = "REMATCH_DATA_END"

	field_tbl[0] = 0
	field_tbl[1] = 0
	field_tbl[2] = 0
	field_tbl[3] = 0
	field_tbl[4] = 0
	field_tbl[5] = 0
	field_tbl[6] = 0
	#field_tbl[7] = 0
}

{
	if( NR < 3 ){
		next
	}

	#フィールド情報を格納
	field_tbl[0] = toupper($1)
	field_tbl[1] = toupper($2)
	field_tbl[2] = toupper($3)
	field_tbl[3] = toupper($4)
	field_tbl[4] = toupper($5)
	field_tbl[5] = toupper($6)
	field_tbl[6] = toupper($7)
	#field_tbl[7] = toupper($8)

	print "\t{"

	TrIDMake()

	print "\t},"
}

END{
	print "};"
	print "#define REMATCH_DATA_MAX ( NELEMS(RematchDataTbl) )"
	print "\n#endif"
}

#-----------------------------------------------------------------------------------------------
#
#	トレーナーID表示
#
#-----------------------------------------------------------------------------------------------
func TrIDMake()
{
	tr_id[0] = "REMATCH_DATA_END"
	tr_id[1] = "REMATCH_DATA_END"
	tr_id[2] = "REMATCH_DATA_END"
	tr_id[3] = "REMATCH_DATA_END"
	tr_id[4] = "REMATCH_DATA_END"
	tr_id[5] = "REMATCH_DATA_END"

	for( i=0; i < 6 ;i++ ){
		if( field_tbl[i] ~ "ZONE_ID" ){
			break
		}else if( field_tbl[i] ~ "DMY" ){
			tr_id[i] = "REMATCH_DATA_DUMMY"
		}else if( field_tbl[i] ~ "END" ){
			tr_id[i] = "REMATCH_DATA_END"
		}else{
			tr_id[i] = field_tbl[i]
		}
	}

	for( i=0; i < 6 ;i++ ){
		print "\t\t" tr_id[i] ","
	}
}


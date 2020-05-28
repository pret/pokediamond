#=============================================================================================
#
#	フィールドアイテムスクリプトコンバータ
#
#	_FLD_ITEM_EVENT記述をfld_item.evに出力する
#
#	05.11.04 Satoshi Nohara
#
#=============================================================================================
BEGIN{

	#=================================================================
	#
	#アイテム定義ファイル読み込み
	#
	#=================================================================
	ITEMSYM_H = "../../../include/itemtool/itemsym.h"

	#getline = １行読み込み
	#１は戻り値
	while ( 1 == getline < ITEMSYM_H ) {
		if ( NF == 7 && $1 =="#define" ) {
			ItemName[$7] = $2
		}
	}
	close(ITEMSYM_H)

	file1 = "fld_item.ev"		#スクリプト
}

NR >= 4{

	#項目数チェック
	if( NF < 6 ) next

	if( $1 == "マップ名" )	next
	if( $1 ~ "アイテム" )	next

	print "/********************************************************************/" >> file1
	print "//\tMAP=" $2 " X=" $3 " Y=" $4 " ITEM=" $5 " FLAG=" $6 >> file1
	print "/********************************************************************/" >> file1
	print "ev_fld_item_" $6 ":" >> file1
	print "\t_FLD_ITEM_EVENT	" ItemName[$5] ",1" >> file1
	#print "\t_LDVAL\tSCWK_TEMP0," ItemName[$5] >> file1
	#print "\t_LDVAL\tSCWK_TEMP1,1" >> file1
	#print "\t_JUMP\tev_fld_item_common" >> file1
	print "\t_END" >> file1
	print "" >> file1
}

END{
	#print "\t.include\t\"fld_item2.ev\"" >> file1
}



#===================================================================
#
#	■.evとsp_■.evの雛形ファイルを作成する
#
#	06.03.06 Satoshi Nohara
#
#===================================================================
BEGIN{
	flag = 0

	print "ファイル名を入力して下さい"
	getline name < "/dev/stdin"
}

{
	tmp = $0
	sub( "dummy", name, tmp )

	#出力先を変更する
	if( $0 == "<<CHANGE_SP_DUMMY>>" ){
		flag = 1
		next
	}

	if( flag == 0 ){
		print tmp >> name ".ev"				#■.ev
	}else{
		print tmp >> "sp_" name ".ev"		#sp_■.ev
	}
}



#===================================================================
#
#	��.ev��sp_��.ev�̐��`�t�@�C�����쐬����
#
#	06.03.06 Satoshi Nohara
#
#===================================================================
BEGIN{
	flag = 0

	print "�t�@�C��������͂��ĉ�����"
	getline name < "/dev/stdin"
}

{
	tmp = $0
	sub( "dummy", name, tmp )

	#�o�͐��ύX����
	if( $0 == "<<CHANGE_SP_DUMMY>>" ){
		flag = 1
		next
	}

	if( flag == 0 ){
		print tmp >> name ".ev"				#��.ev
	}else{
		print tmp >> "sp_" name ".ev"		#sp_��.ev
	}
}



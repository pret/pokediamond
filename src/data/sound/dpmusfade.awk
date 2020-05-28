#===========================================================================================
#
#	060124 Satoshi Nohara
#
#	dpmusfade.xls���R���o�[�g���āA
#	�g���b�N�t�F�[�h�f�[�^��dpmusfade.dat�ɏ�������
#
#===========================================================================================

BEGIN{
	print "//----------------------------------------------------"
	print "//\t�g���b�N�t�F�[�h�f�[�^"
	print "//----------------------------------------------------"
	print "//���ӁI �}�C�i�X1������0�`15�g���b�N�Ƃ��Ĉ����Ă���"
	print "static const TRACK_FADE_DATA track_fade_tbl[] = {"
}

{
	#�s���`�F�b�N
	if( NR < 2 ){
		next
	}

	#���ڐ��`�F�b�N
	if( NF < 4 ){
		next
	}

	#�ϐ�������
	noon_start	= $4
	noon_end	= $4
	night_start = $5
	night_end	= $5

	#��start
	sub( /\,.*$/, "", noon_start )				#","�ȍ~���폜
	sub( "\"", "", noon_start )					#"���폜

	#��start
	sub( /\,.*$/, "", night_start )				#","�ȍ~���폜
	sub( "\"", "", night_start )				#"���폜

	for( i=0; i < 16 ;i++ ){

		#��end
		if( noon_end ~ "," ){
			sub( /^[^,]*/, "", noon_end )		#","�ƈ�v����܂ō폜
			sub( /[,]/, "", noon_end )			#","�ƈ�v������폜
		}

		#��end
		if( night_end ~ "," ){
			sub( /^[^,]*/, "", night_end )		#","�ƈ�v����܂ō폜
			sub( /[,]/, "", night_end )			#","�ƈ�v������폜
		}
	}

	sub( "\"", "", noon_end )					#"���폜
	sub( "\"", "", night_end )					#"���폜

	#�}�C�i�X1������0�`15�g���b�N�Ƃ��Ĉ���
	if( noon_start == 0 ){						#"0"�̓f�[�^�Ȃ�
		noon_start = "TRACK_FADE_NONE"
		noon_end = "TRACK_FADE_NONE"
	}else{
		noon_start-=1
		noon_end-=1
	}

	if( night_start == 0 ){						#"0"�̓f�[�^�Ȃ�
		night_start = "TRACK_FADE_NONE"
		night_end = "TRACK_FADE_NONE"
	}else{
		night_start-=1
		night_end-=1
	}

	#�o��
	tmp = $3
	sub( ".mid", "", tmp )
	name = toupper( tmp )
	print "\t{ SEQ_" name ",\t" noon_start ", " noon_end ", " night_start ", " night_end " },"
}

END{
	print "};"
	print "#define TRACK_FADE_TBL_MAX ( NELEMS(track_fade_tbl) )"
}


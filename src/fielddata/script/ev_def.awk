#===========================================================================================
#
#	050826 Satoshi Nohara
#
#	*.ev�t�@�C������A�X�N���v�g��ID�𐶐����āA*_def.h�ɏ�������
#
#===========================================================================================
BEGIN{
	#�R�}���h���C���̈���1
	name = ARGV[1]												#�t�@�C�����擾(�� r203.ev)
	sub(/\..*$/,"",name)										#"."�ȍ~���폜(�� r203)

	#=================================================================
	#
	#�X�N���v�g�I�t�Z�b�g��`�t�@�C���ǂݍ���
	#
	#=================================================================
	SCR_OFFSET_H = "../../field/scr_offset.h"

	offset_i = 0

	#getline = �P�s�ǂݍ���
	#�P�͖߂�l
	while ( 1 == getline < SCR_OFFSET_H ) {
		if ( NF == 4 && $1 =="#define" ) {

			if( $2 ~ "_END" ){
				#�������Ȃ�
			}else{
				#�X�N���v�g�t�@�C����
				temp = tolower( $2 )
				sub( "id_", "", temp );
				sub( "_offset", "", temp );
				OffsetName[offset_i] = temp
	
				#�I�t�Z�b�gID
				temp = $3
				sub( /[(]/,"", temp );
				sub( /[)]/,"", temp );
				OffsetId[offset_i]	= temp
				offset_i++
			}
		}
	}
	close(SCR_OFFSET_H)

	#���d�C���N���[�h�`�F�b�N
	name2 = toupper(name)										#�啶���ɓ���
	print "#ifndef _" name2 "_DEF_H_" > name "_def.h"
	print "#define _" name2 "_DEF_H_\n" > name "_def.h"	

	#����R���o�[�g��������ƁA��ɍ������o��̂ŊO�����I
	#print strftime( "//%Y %m %d %H:%M:%S\n" ) > name "_def.h"	#�R���o�[�g�������t
	#printf( "//2005 10 14 19:49:31\n\n" ) > name "_def.h"

	printf( "//�X�N���v�g�f�[�^ID��` \n" ) > name "_def.h"		#�^�C�g��

	#####################################################################################

	#�Y������t�@�C����T��
	j = 0
	start = 1									#"0"��SCRID_NULL�Ŏg�p����̂�1�ɂ���I(06.01.20)
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
	#�e�[�u���I�����`�F�b�N
	if( $1 ~ "EVENT_DATA_END" ){
		exit	#�I��
	}

	#�e�[�u������
	if( $1 ~ "EVENT_DATA" ){

		#ID�p�̖��O
		id_name = $2
		#sub(/^[ev_]*/,"",id_name)				#�擪��"ev_"���폜(ev_egg �� gg �ɂȂ��Ă��܂�)
		sub( "ev_", "", id_name)									#�擪��"ev_"���폜

		id_name2 = toupper(id_name)									#�啶���ɓ���
		name2 = toupper(name)										#�啶���ɓ���

		#05.12.06
		#�g���[�i�[�̓_�u���o�g���̂��߂�ID��2�I�t�Z�b�g��ς��ďo�͂���(+2000)
		#SXY�Ɏw�肷�鎞�ɁA�o�q�̍��E�ł��ꂼ��g��(_2)
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
	#�ő吔�̒�`��ǉ�����
	count = count - start
	print "#define\tSCRID_" name2 "_DATA_MAX\t\t" "(" count ")\t\t\/\/�ő吔" > name "_def.h"#ID_??

	#���d�C���N���[�h�`�F�b�N
	print "\n#endif //_" name2 "_DEF_H_" > name "_def.h"#ID_??
}


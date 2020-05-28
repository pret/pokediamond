#=============================================================================================
#
#	�B���A�C�e���Ǘ��\�R���o�[�^
#
#	05.11.16 Satoshi Nohara
#
#	��_HIDE_ITEM_EVENT�L�q��hide_item.ev�ɏo�͂���
#
#=============================================================================================
BEGIN{

	#=================================================================
	#
	#�A�C�e����`�t�@�C���ǂݍ���
	#
	#=================================================================
	ITEMSYM_H = "../../../include/itemtool/itemsym.h"

	#getline = �P�s�ǂݍ���
	#�P�͖߂�l
	while ( 1 == getline < ITEMSYM_H ) {
		if ( NF == 7 && $1 =="#define" ) {
			ItemName[$7] = $2
		}
	}
	close(ITEMSYM_H)

	file1 = "hide_item.dat"

	print "//====================================================================" > file1
	print "//						�B���A�C�e���f�[�^" >> file1
	print "//" >> file1
	print "// 05.11.17 Satoshi Nohara" >> file1
	print "//" >> file1
	print "// ��hide_item.xls���R���o�[�g���ďo�͂��Ă��܂�" >> file1
	print "//" >> file1
	print "//====================================================================" >> file1
	print "" >> file1

	print "const HIDE_ITEM_DATA hide_item_data[] = {" >> file1
	print "\t//�A�C�e���i���o�[ �� ���� ���� �t���O�C���f�b�N�X" >> file1
}

NR >= 4{

	#���ڐ��`�F�b�N
	if( NF < 9 ) next
	if( $1 == "�}�b�v��" )	next
	if( $1 ~ "�A�C�e��" )	next

	#-----------------------------------------------------------------
	#
	#�t���O�}�b�N�X�𒴂��Ă�����G���[(06/01/26 MAX = 256 )
	#
	#-----------------------------------------------------------------
	if( $9 > 255 ){
		printf("�t���O�̍ő吔�𒴂��Ă��܂��I\n") >> "/dev/stderr"
		exit				#�r���ŏI��
	}

	#�ǉ�
	print "\t{ " ItemName[$5] ",\t" $6 ",\t" $7 ",\t" $8 ",\t" $9 " }," >> file1
}

END{
	print "};" >> file1
	print "#define HIDE_ITEM_DATA_MAX\t( NELEMS(hide_item_data) )" >> file1
}




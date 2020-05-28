#�w�肳�ꂽ�o�C�g���P�ʂɃt�@�C���̒��g�������o���V�X�e��
#�����P
#	�����o���Ƃ��̃o�C�g�P��
#		C	1byte�P��
#		S	2byte�P��
#		I	4byte�P��
#
#�����Q
#	�R���o�[�g�t�@�C���p�X
#		�t�@�C����,��؂�̃t�@�C���ł���K�v������܂��B
#		�܂��A�����P�o�C�g�ȏ�̃f�[�^�͓���Ȃ��ł��������B
#	������j
#		1,2,3,4,5,6,7,8,	comment��
#		3,5,6,7,8,5,4,23,435,	comment��
#		345,123,	comment��
#�����R
#	�R���o�[�g��t�@�C���p�X
#
#�߂�l
#	����	0
#	���s	1

#�����͂R�K�v�ł��B
#
#�����̎��͕����R�[�h��Ԃ��܂��B
if( @ARGV < 3 ){

	print( "err--�����͂R�K�v�ł��B\nparam1 byte size\nparam2 conv file path\nparam3 output file path\n" );
	print( "param1 byte size::::::::::::::::::::\n" );
	print( "C 1byte S 2byte I 4byte\n" );

	exit(1);
}

#�t�@�C���I�[�v��
open( FILEIN, $ARGV[1] );
@in_file = <FILEIN>;
if( @in_file == 0 ){
	print( "$ARGV[1]�I�[�v�����s\n" );	
	exit(1);
}
close( FILEIN );


open( FILEOUT, ">$ARGV[2]" );

binmode( FILEOUT );

#�����o���o�C�g�T�C�Y���擾���Ă���
if( $ARGV[0] eq "C" ){
	$out_byte = 1;
}elsif( $ARGV[0] eq "S" ){
	$out_byte = 2;
}elsif( $ARGV[0] eq "I" ){
	$out_byte = 4;
}

#binary�ŏ����o��
foreach $one( @in_file ){

	#���s�̑O��,������s�܂ł�r��
	$one =~ s/,[^,]*\r*\n/\n/;
	
	#�^�u�X�y�[�X��r��
	$one =~ s/\s//g;
	$one =~ s/\t//g;

	#���s�R�[�h��j��
	$one =~ s/\n//;
	
	
	@one_list = split( ",", $one );

	foreach $list_data (@one_list){
	
		#���s�R�[�h�̓X�L�b�v
		if( $list_data =~ /\d+/ ){
			#����
			print( FILEOUT pack("$ARGV[0]", $list_data) );
		}else{
			#�����̎��̓G���[
			print( "binary_conv.pl err!!!---$list_data\n�������o�C�i���ŏ����o�����Ƃ��Ă��܂��I�I\n" );
			close( FILEOUT );
			exit(1);
		}
	}
}

close( FILEOUT );
exit(0);

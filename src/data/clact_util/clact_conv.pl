#�Z���A�N�^�[�w�b�_�[�o�C�i���R���o�[�^
#
#�����P
#	�R���o�[�g�Ώۃt�@�C���p�X
#		�i�Z���A�N�^�[�w�b�_�[�j
#�����Q
#	�����o���t�@�C���p�X
#
#�����R�A�S�A�A�A�A�A
#	�Ή�������enum���L�q����Ă���w�b�_�[�ւ̃p�X
#
#�������Q�K�v
if( 2 > @ARGV ){

	print( "err---����������܂��� �K�v�Q��  ����".@ARGV."��\n" );
	print( "�����P�@�R���o�[�g�Ώۃt�@�C���p�X\n" );
	print( "�����Q�@�����o���t�@�C���p�X\n" );
	print( "�����R�A�S�A�A�A�A�@�Ή�������w�b�_�[�t�@�C���p�X\n" );
	exit(1);
}


#�����R�ȍ~���̃w�b�_�[�f�[�^�ƃt�@�C����Ή�������
for( $i = 2; $i < @ARGV; $i++ ){
	if( $i == 2 ){
		$check = system( "c:\/cygwin\/bin\/perl enum_to_num.pl $ARGV[0] $ARGV[1] $ARGV[$i]" );
	}else{
		$check = system( "c:\/cygwin\/bin\/perl enum_to_num.pl $ARGV[1] $ARGV[1] $ARGV[$i]" );
	}

	if( $check ){
		print( "enum_to_num.pl err\n" );
		exit(1);
	}
}

#�o�C�i����
$check = system( "c:\/cygwin\/bin\/perl binary_conv.pl I $ARGV[1] $ARGV[1]" );
if( $check ){
	print( "binary_conv.pl err\n" );
	exit(1);
}

exit(0);

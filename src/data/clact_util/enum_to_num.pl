#	�t�@�C���ɏ����ꂽenum��Ή�����i���o�[�ɕύX����
# �����P�@�R���o�[�g�Ώۃt�@�C��
# �����Q�@�R���o�[�g��t�@�C����
# �����R�C�S�E�E�E�E�E
#			���x�����`���Ă���t�@�C���i�����j
#			enum���`���Ă���t�@�C���͈����P�Ɏw�肷��t�@�C�����ɋL�q���邱�Ƃ��o���܂��B(��)	
#�g�p��
#perl enum_to_num.pl conv_before.txt conv_after.txt enum_file1.h enum_file2.h
#
#�����ӎ���
#10�i���ɂ����Ή����Ă��܂���B
#enum�ɂ����Ή����Ă��܂���B	define�͖����ł�
#
#
#��Link����enum�̃t�@�C�����`������@
#�����P�̃R���o�[�g�Ώۃt�@�C���̐擪��ENUM_FILE=,,,,�ƎQ�Ƃ���t�@�C���p�X���L�q���Ă��������B
#
#��
#ENUM_FILE=include/system/arc_tool.dat,include/system/clact_util_res.h,	<-','�K�v�ł��B		�R�����g��
#���e�[�[�[�[�[�[�[�[


#####################################################################
#	���C�����[�`��
#####################################################################
%h_LabelTbl;		#LABEL�f�[�^�n�b�V���e�[�u��


#�����͍Œ�R�K�v
if( @ARGV < 3 ){
	&help("���������s���ł��B�@������".@ARGV);
	exit(1);
}


#LABEL�f�[�^�e�[�u���쐬
for( $i=2; $i<@ARGV; $i++ ){
	open( IN, "$ARGV[$i]" );

	@file = <IN>;
	
	if( @file == 0 ){
		print( "$ARGV[$i]���J���܂���---0\n" );
		close( IN );
		exit(1);
	}

	#comment��j��
	@file = &comment_cut( @file );
	close( IN );

#	print( @file );


	#�n�b�V���e�[�u����LABEL�f�[�^��ǉ�
	&add_hash( \@file, \%h_LabelTbl );
}

#print( "�n�b�V���f�[�^�\\��\n" );
#while( ($key, $num) = each(%h_LabelTbl) ){
#	print( "LABEL=$key	NUM=$num\n" );
#}


#�t�@�C���ǂݍ��݂Ə����o����쐬
open( FILE_IN, "$ARGV[0]" );
@in_file = <FILE_IN>;
if( @in_file == 0 ){
	print( "$ARGV[0]���J���܂���---1\n" );
	close( FILE_IN );
	exit(1);
}
close( FILE_IN );
open( FILE_OUT, ">$ARGV[1]" );

#�P�s�ڂ�ENUM_FILE��`�����邩�`�F�b�N
if( $in_file[0] =~ s/ENUM_FILE=// ){
	
	#�R�����g�����j��
	$in_file[0] =~ s/,[^,]*\r*\n/,\n/;
	#�X�y�[�X �^�u��j��
	$in_file[0] =~ s/\s//g;
	$in_file[0] =~ s/\t//g;

	#*,�܂ł�؂���
	while( $in_file[0] =~ s/([^,]+),// ){
		open( IN, "$1" );
		@file = <IN>;
		close( IN );
		if( @file == 0 ){
			print( "$1���J���܂���---0\n" );
			close( FILE_IN );
			close( FILE_OUT );
			exit(1);
		}
		#comment��j��
		@file = &comment_cut( @file );

		#�n�b�V���e�[�u����LABEL�f�[�^��ǉ�
		&add_hash( \@file, \%h_LabelTbl );
	}

	#�P�s�ڂ𖳂���
	@in_file = @in_file[1..(@in_file-1)];
}

foreach $one_data ( @in_file ){
	
	#�n�b�V���̒��Ɠ����������������琔���ɕς���
	while( ($key, $num) = each(%h_LabelTbl) ){

		#���̃L�[�Ɠ��������񂪂��邩�`�F�b�N
		while( $one_data =~ s/(,|^)[\s\t]*$key[\s\t]*(,)/$1$num$2/ ){
#			print( "cheng $key to $num\n" );
		};
	}

	print( FILE_OUT $one_data );
#	print( $one_data );
}

close( FILE_OUT );

exit(0);

#####################################################################
#	�T�u���[�`��
#####################################################################
#�w���v�\���֐�
#param		�\��������
#return		none
sub help {
	my($str) = @_;
	print( "err $str\n" );
	print( "�����P�@�R���o�[�g�Ώۃt�@�C���p�X\n" );
	print( "�����Q�@�R���o�[�g��t�@�C���p�X\n" );
	print( "�����R�C�S�C�T�A�A�A�A�A���x����`�t�@�C���p�X�i���ł��j\n" );
	return 1;
}

#LABEL��`�����𔲂��o��
#param		����������e�[�u���̃|�C���^
#param		���݂̃n�b�V���f�[�^�̃|�C���^
#
#enum{				<=������T��
#	LABEL1,			
#	LABEL2 = 5,
#};					<=�����ŏI��肾�ƃ`�F�b�N����
sub add_hash {

	my($label_tbl, $label_hash) = @_;
	my($one, $enum_flag, $label_num, $label_check, $label_num_check);
	my($label_tmp, $label_num_tmp);

#	print( "�J�n\n" );
	
	$enum_flag = 0;
	$label_num = 0;
	$label_tmp = undef;

	foreach $one( @$label_tbl ){

		#enum�̒�`�ɓ��邩�`�F�b�N
		if( $enum_flag == 0 ){
			
			#enum��`�����邩�`�F�b�N
			if( $one =~ /^[\s\t]*enum/ ){
				$enum_flag = 1;

#				print( "enum����\n" );
			}
		}
		
		if( $enum_flag == 1 ){
			#{��T��
			if( $one =~ /{/ ){

				$enum_flag = 2;
#				print( "{����\n" );
			}
		}
		
		if( $enum_flag == 2 ){

			#LABEL��`�擾
			$label_check = &get_label( $one );
			if( $label_check ne "def_to_num_err" ){

#				print( "LABEL�擾=$label_check\n" );

				#����if��else�Őݒ肵��$label_tmp�̒��g��j��
				#�����ɓ����Ă����Ƃ������Ƃ́A��Ԃ����ł͂Ȃ��B
				$label_tmp = undef;

				#�k�`�a�d�k���̒�`�������Ă��Ȃ����`�F�b�N
				$label_num_check = &get_labelnum( $one );
				if($label_num_check ne "def_to_num_err"){
					$label_num = $label_num_check;
				}
#				print( "LABEL��=$label_num\n" );
			
				#�n�b�V���Ɋi�[
				$$label_hash{ $label_check } = $label_num;
				$label_num ++;	#�k�`�a�d�k�ɑΉ�����l���Z
				
			}else{
				
				#,���Ȃ������ŁALABEL��`���ۂ��s�����������Ă���
				#���̗L���ȍs���A}�Ȃ�LABEL�Ƃ��ēo�^����
				if( $one =~ /^[\s\t]*([^\s\t\}\;]+)/ ){
					$label_tmp = $1;			

					#������`�����邩�`�F�b�N
					$label_num_check = &get_labelnum( $one );
					if($label_num_check ne "def_to_num_err"){
						$label_num_tmp = $label_num_check;
					}else{
						$label_num_tmp = $label_num;
					}
				}
			}

			#enum�I���`�F�b�N
			#};������ΏI��
			if( $one =~ /}/ ){
				
				#label_tmp������Ƃ��͂���LABEL���n�b�V���ɑ��
				if($label_tmp){
					$$label_hash{ $label_tmp } = $label_num_tmp;
				}
				
				#���[�N������
				$enum_flag = 0;
				$label_num = 0;
#				print( "}����\n" );
			}
		}
	}
#	print( "�I��\n" );
}

#LABEL��`�̎擾
#param		LABEL����`����Ă��邩������Ȃ�������
#retval		LABEL�̖��O
#retval		err = LABEL���Ȃ�
sub get_label{

	my($str) = @_;

	#^	TEST_LABEL	,��TEST_LABEL���擾
	#^TEST_LABEL,
	#^ TEST_LABEL = 0,
	if( $str =~ /^[\s\t]*([^\s\t]+)[\s\t]*(\,|\=[\s\t]*\d+[\s\t]*\,)/ ){
		return $1;
	}

	return "def_to_num_err";
}

#LABEL����`�̎擾
#param		LABEL������`����Ă��邩������Ȃ�������
#retval		LABEL�ɑΉ�����l
#retval		err = LABEL���Ȃ�
sub get_labelnum{

	my($str) = @_;

	#^ TEST_LABEL = 0
	#,�͍ŏI�s�̃��x���ɂ͖����̂ŁA�`�F�b�N���Ȃ�
	if( $str =~ /\=[\s\t]*(\d+)/ ){
		return $1;
	}

	return "def_to_num_err";
}

#comment������r�����܂��B
sub comment_cut {

	my( @str ) = @_;
	my( $one, $com_flag );
	

	$com_flag = 0;
	foreach $one( @str ){

		if( $com_flag == 1 ){
			#��������܂ł̑S�Ă�j��
			if( $one =~ /\*\// ){
				$one =~ s/.*\*\///;
				$com_flag = 0;
			}else{
				$one =~ s/.*//;
			}
		}

		if( $com_flag == 0 ){
			#/**/��j��
			$one =~ s/\/\*.*?\*\///g;

			#//������  �O��/*���Ȃ�
			$one =~ s/(.*)\/\/.*(\r*\n)/$1$2/;

			#/*��j��
			if( $one =~ s/\/\*.*(\r*\n)/$1/ ){

				$com_flag = 1;		#�����Ȃ��̂ŒT��
			}
		}			
	}

	return @str;
}

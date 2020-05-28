#----------------------------------------------------------------------------
#
#	���̃p�[����pokemon_dp�t�H���_����Ă΂�܂��B
#
#	arc_tool.dat�Ȃ���enum�̒l������arc_tool.dat��num�̒l�ƈꏏ���`�F�b�N
#	
#----------------------------------------------------------------------------
#####################################################################
#	���C�����[�`��
#####################################################################
%h_LabelTbl_TMP;		#tmp_arc_tool.dat LABEL�f�[�^�n�b�V���e�[�u��
%h_LabelTbl_NOW;		#arc_tool.dat LABEL�f�[�^�n�b�V���e�[�u��

#����arc_tool.dat�ǂݍ���
open( IN, "../../../../include/system/arc_tool.dat" );
@now_arc = <IN>;
close( IN );
if( @now_arc == 0 ){
	print( "arc_tool.dat���J���܂���\n" );
	exit(1);
}

#�ۑ����Ă�����arc_tool.dat�ǂ݂���
open( IN, "tmp_arc_tool.dat" );
@tmp_arc = <IN>;
close( IN );
if( @tmp_arc == 0 ){
	print( "tmp_arc_tool.dat���J���܂���\n" );
	exit(0);
}

#comment��j��
@now_arc = &comment_cut( @now_arc );
@tmp_arc = &comment_cut( @tmp_arc );

#�n�b�V���e�[�u����LABEL�f�[�^��ǉ�
&add_hash( \@tmp_arc, \%h_LabelTbl_TMP );
&add_hash( \@now_arc, \%h_LabelTbl_NOW );


#h_LabelTbl_TMP�Ȃ��̃f�[�^���S��h_LabelTbl_NOW�ɂ��邩�`�F�b�N
#�n�b�V���̒��Ɠ����������������琔���ɕς���
$key_tnow = 0;	#������key�i�[�p
$num_tnow = 0;	#������num�i�[�p
while( ($key_tmp, $num_tmp) = each(%h_LabelTbl_TMP) ){

	$eq_flg = 0;
	#���̃L�[�Ɠ����L�[�����邩�`�F�b�N
	while( ($key_now, $num_now) = each(%h_LabelTbl_NOW) ){
		
		if( $key_tmp eq $key_now ){
			$eq_flg	= 1;
			$key_tnow = $key_now;
			$num_tnow = $num_now;
		}
	}

	#$eq_flg���O�̎��G���[
	if( $eq_flg == 0 ){
		print("$key_tmp �Ƃ���LABEL������܂���B\n");
		print("arc_tool.dat�̃A�[�J�C�u�t�@�C��ID���ύX���ꂽ���߁A�Z���A�N�^�[�w�b�_�[���̃A�[�J�C�u�t�@�C��ID�ƈ�v���Ȃ��ꍇ������܂��B tomoya takahashi \n" );
		system( "rm ../*.resdat" );
		system( "rm ../*.cldat" );
		exit(1);
	}

	#�l�����������`�F�b�N
	if( $h_LabelTbl_TMP{ $key_tmp } != $h_LabelTbl_NOW{ $key_tmp } ){
		print("$key_tmp=$num_tmp �� $key_tnow=$num_tnow �ɂȂ�܂����B\n");
		print( "�Z���A�N�^�[�w�b�_�[���̃A�[�J�C�u�t�@�C��ID�ƈ�v���Ȃ��ꍇ������܂��B�V�K�A�[�J�C�u�t�@�C���̒ǉ���enum�̈�ԉ��ɂ��肢�������܂��B�����͂��肢���܂��B tomoya takahashi \n" );
		system( "rm ../*.resdat" );
		system( "rm ../*.cldat" );
		exit(1);
	}
}

exit(0);

#####################################################################
#	�T�u���[�`��
#####################################################################
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

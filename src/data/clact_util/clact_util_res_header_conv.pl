#�Z���A�N�^�[���[�e�B���e�B�V�X�e��
#	���\�[�X�}�l�[�W���o�C�i���w�b�_�[��`�t�@�C���`���ɐ��`����
#	
#	���܂ł̃e�L�X�g�`���̃t�@�C�����o�C�i���ɃR���o�[�g�ł���`���ɕω�������
#
#	�����P
#		�R���o�[�g�Ώ�
#	�����Q
#		�����o���t�@�C����
#
#	�߂�l
#		����	1
#		���s	0

#�����͂Q�K�v
if( 2 > @ARGV ){

	print( "err--�����̐���".@ARGV."�ł��B\n" );
	print( "�����P�@�R���o�[�g�Ώ�\n" );
	print( "�����Q�@�����o���t�@�C����\n" );
	exit(1);
}


#	�R���o�[�g�Ώۂ̃t�@�C���`��
#
#		���\�[�X�^�C�v,�@�A�[�J�C�u�t���O,												<-�A�[�J�C�u�t�@�C���t���O������
#		�A�[�J�C�uidx,�f�[�^idx,���k�t���O,�Ǘ�ID,vram�^�C�v,�p���b�g�ǂݍ��ݖ{��,		<-���̗v�f�������\�[�X�^�C�v�ɂ���ĈႤ
#		�A�[�J�C�uidx,�f�[�^idx,���k�t���O,�Ǘ�ID,vram�^�C�v,�p���b�g�ǂݍ��ݖ{��,		<-���̗v�f�������\�[�X�^�C�v�ɂ���ĈႤ
#	<�I���R�[�h>e,e,e,e,e,e,															<-�X�̌����Ⴄ

#	�Z���A�N�^�[���[�e�B���e�B�V�X�e��
#			���\�[�X�}�l�[�W���o�C�i���w�b�_�[��`�t�@�C���`��
#��j
#*		���\�[�X�^�C�v,																	<-�A�[�J�C�u�t�@�C���t���O��p�~
#*		�A�[�J�C�uidx,�f�[�^idx,���k�t���O,�Ǘ�ID,vram�^�C�v,�p���b�g�ǂݍ��ݖ{��,		<-�v�f�����Œ�		6��
#*		�A�[�J�C�uidx,�f�[�^idx,���k�t���O,�Ǘ�ID,vram�^�C�v,�p���b�g�ǂݍ��ݖ{��,		<-�v�f�����Œ�		6��
#*	<�I���R�[�h>e,e,e,e,e,e,															<-�����Œ�		6��

#�ǂݍ��݃t�@�C���I�[�v��
#
open( FILEIN, $ARGV[0] );
@in_file = <FILEIN>;

if( @in_file == 0 ){
	print( "$ARGV[0]���J���܂���\n" );
	exit(1);
}

close( FILEIN );

#�������݃t�@�C���I�[�v��
#
open( FILEOUT, ">$ARGV[1]" );

#�f�[�^�𐮌`���Ȃ��珑���o��
$res_type_flag = 1;
foreach $one (@in_file){

	#�R�����g������j��
	$one =~ s/,[^,]*\r*\n/,\n/;
	
	
	#�^�u�@�X�y�[�X��r��
	$one =~ s/\s//g;
	$one =~ s/\t//g;

	#ENUM_FILE�̂���s�͂��̂܂܏����o��
	if( $one =~ /ENUM_FILE/ ){
		print( FILEOUT $one);
	}else{
		#���\�[�X�^�C�v�̂Ƃ�
		if( $res_type_flag ){

			#�擪����,�܂ł������o��
			$one =~ /^([^,]+,)/;

			print(FILEOUT $1);
			$res_type_flag = 0;
		}else{
			
			#�e�f�[�^�̂Ƃ�
			#6�̃f�[�^�ɌŒ�
			@one_list = split( ",", $one );
			$data_num = 0;
			foreach $list_data ( @one_list ){
				#\r\n���Ȃ����`�F�b�N
				if( !($list_data =~ /\n/) ){
					
					if( $data_num < 6 ){

						print( FILEOUT "$list_data," );
						$data_num ++;
					}
				}
			}

			#6��菬�����Ƃ��͂U�ɂȂ�܂Ń_�~�[�f�[�^�������o��
			for( ; $data_num < 6; $data_num ++ ){
				$one =~ /^([^,]+,)/;
				print( FILEOUT $1 );
			}
		}
	}
	print(FILEOUT "\r\n" );
}

close( FILEOUT );

exit(0);

##-----------------------------------------------------------------------------
#
#		
#			�}�Ӄf�[�^�R���o�[�^
#			�}�ӊ�����́@����G���J�E���g�f�[�^�e�[�u��
#
#
##-----------------------------------------------------------------------------

#------------------------------------------------------------------------------
#
#	�萔��`
#
#------------------------------------------------------------------------------
$DEF_FLD_GRID_SIZE_X = 30;
$DEF_FLD_GRID_SIZE_Y = 30;
$DEF_FLD_AREA_DATA_ARRY_OUTSIZE	= 32;
$DEF_CONV_MODE = "�_�C��";
#$DEF_CONV_MODE = "�p�[��";

$CONV_FILE_NAME	= undef;


#�O���[�o���ϐ���`
#------------------------------------------------------------------------------
#
#	�萔�f�[�^
#
#------------------------------------------------------------------------------
$ZONE_ID[ 0 ] = undef;		#�]�[��ID
$MONS_ID[ 0 ] = undef;		#�����X�^�[NO

#------------------------------------------------------------------------------
#
#			�t�@�C���f�[�^
#
#------------------------------------------------------------------------------
$DAN_FILE[ 0 ] = undef;		#�_���W�����f�[�^�t�@�C��
$FLD_FILE[ 0 ] = undef;		#�t�B�[���h�f�[�^�t�@�C��
$ENC_FILE[ 0 ] = undef;		#�G���J�E���g�f�[�^�t�@�C��

#------------------------------------------------------------------------------
#
#			���z�f�[�^
#
#			������
#	(,,,��؂�Ńf�[�^������)
#------------------------------------------------------------------------------
$RANGE_DAN_MO[ 0 ] = undef;	#�ő吔�̓����X�^�[��			�\��
$RANGE_DAN_NU[ 0 ] = undef;	#�ő吔�̓����X�^�[��		
$RANGE_DAN_NI[ 0 ] = undef;	#�ő吔�̓����X�^�[��		
$RANGE_FLD_MO[ 0 ] = undef;	#�ő吔�̓����X�^�[��
$RANGE_FLD_NU[ 0 ] = undef;	#�ő吔�̓����X�^�[��
$RANGE_FLD_NI[ 0 ] = undef;	#�ő吔�̓����X�^�[��
$RANGE_DAN_SPECIAL[ 0 ] = undef;	#�ő吔�̓����X�^�[��	�ԕ\��
$RANGE_FLD_SPECIAL[ 0 ] = undef;	#�ő吔�̓����X�^�[��

#------------------------------------------------------------------------------
#
#			�_���W�����f�[�^
#			�ő吔�̓_���W�������zID��
#------------------------------------------------------------------------------
$DAN_ID[ 0 ] = undef;				#�_���W�������zID�idefine���j
$DAN_ZONEID[ 0 ] = undef;			#�Ή�����]�[��ID�idefine���j
$DAN_GRID_X[ 0 ] = undef;			#�O���b�h���W			
$DAN_GRID_Y[ 0 ] = undef;			#�O���b�h���W
$DAN_TOKUSYUOAM[ 0 ] = undef;		#����OAM���g�p���邩

@DAN_TOKUSYUOAM_ZONEID = ( "ZONE_ID_D05" );	#����OAM�̃]�[��ID


#------------------------------------------------------------------------------
#
#			�B���}�b�v���Ƃ́@���z�f�[�^
#			
#------------------------------------------------------------------------------
@HIDEMAP_ZONEID = ( "ZONE_ID_D15", "ZONE_ID_D18", "ZONE_ID_D30", "ZONE_ID_L04" );	#�B���}�b�v

#------------------------------------------------------------------------------
#
#			�t�B�[���h�f�[�^
#			�ő吔�̓t�B�[���h���zID��
#------------------------------------------------------------------------------
$FLD_ID[ 0 ] = undef;				#�t�B�[���h���zID�idefine���j
$FLD_ZONEID[ 0 ] = undef;			#�Ή�����]�[��ID�idefine���j
$FLD_GRID_X[ 0 ] = undef;			#����O���b�h���W
$FLD_GRID_Y[ 0 ] = undef;			#����O���b�h���W
$FLD_SIZE_X[ 0 ] = undef;			#�}�b�v�O���T�C�Y��
$FLD_SIZE_Y[ 0 ] = undef;			#�}�b�v�O���T�C�Y��
$FLD_AREA_ARRY[ 0 ] = undef;		#�}�b�v�O���f�[�^	���x*y�T�C�Y�̔z�� �f�[�^��,�ŋ�؂��ē����



#------------------------------------------------------------------------------
#		���h��f�[�^
#------------------------------------------------------------------------------
@MITUNURI_ZONEID = ( "ZONE_ID_R205A",  "ZONE_ID_R205B", "ZONE_ID_R206", "ZONE_ID_R207", "ZONE_ID_R208", "ZONE_ID_R209", "ZONE_ID_R210A", "ZONE_ID_R210B", "ZONE_ID_R211B", "ZONE_ID_R212A", "ZONE_ID_R212B", "ZONE_ID_R213", "ZONE_ID_R214", "ZONE_ID_R215", "ZONE_ID_R218", "ZONE_ID_R221", "ZONE_ID_R222", "ZONE_ID_D02", "ZONE_ID_D03", "ZONE_ID_D04", "ZONE_ID_D13R0101" );		#���h��]�[��ID

$MITUNURI_ZONENUM = 21;				#���h��]�[����
@MITUNURI_POKENO = undef;		#���h��|�P�����i���o�[��
$MITUNURI_POKENUM = undef;			#���h��|�P������

#------------------------------------------------------------------------------
#		�q���o�X�f�[�^
#------------------------------------------------------------------------------
$HINBASU_POKENO[ 0 ] = "�q���o�X";	#�q���o�X�|�P�����i���o�[
$HINBASU_POKENUM	 = 1;				#�q���o�X�|�P������
$HINBASU_ZONE_ID[ 0 ] = "ZONE_ID_D05R1301";	#�q���o�X�]�[��ID
$HINBASU_ZONENUM	 = 1;				#�q���o�X�]�[����


#------------------------------------------------------------------------------
#		���R�f�[�^
#------------------------------------------------------------------------------
$URAYAMA_ZONE_ID[0] = "ZONE_ID_D23R0101";	#���R�]�[��ID
$URAYAMA_ZONENUM	 = 1;			#���R�]�[����
@URAYAMA_POKENO = undef;		#���R�|�P�����i���o�[��
$URAYAMA_POKENUM = undef;			#���R�|�P������


#------------------------------------------------------------------------------
#		�����f�[�^
#------------------------------------------------------------------------------
@SITUGEN_ZONE_ID = ("ZONE_ID_D06R0201", "ZONE_ID_D06R0202", "ZONE_ID_D06R0203", "ZONE_ID_D06R0204", "ZONE_ID_D06R0205", "ZONE_ID_D06R0206");		#�����]�[��ID

$SITUGEN_ZONENUM	 = 1;				#�����]�[����
@SITUGEN_POKENO = undef;			#�����|�P�����i���o�[��
$SITUGEN_POKENUM = undef;				#�����|�P������



#------------------------------------------------------------------------------
#
#		���C�����[�`��			
#
#------------------------------------------------------------------------------
#������DIAMOND PEARL���w�肵�Ă��炤
if( $ARGV[0] eq "DIAMOND" ){
	$DEF_CONV_MODE = "�_�C��";
	print( "�_�C��Ver\n" );
}else{
	$DEF_CONV_MODE = "�p�[��";
	print( "�p�[��Ver\n" );
}

#��2�����ɃR���o�[�g�Ώ�
$CONV_FILE_NAME = $ARGV[1];


#CSV�t�@�C���̍쐬
print( "CSV�t�@�C���̍쐬\n" );
&csv_file_make();

#�t�@�C���ǂݍ���
print( "�t�@�C���ǂݍ���\n" );
&file_load();

#�]�[��ID�擾
print( "�]�[��ID�擾\n" );
&zone_id_get();

#�����X�^�[ID�擾
print( "�����X�^�[ID�擾\n" );
&mons_no_get();

#�f�o�b�N�f�[�^�o��
#&debug_array_print( "�]�[���f�[�^", \@ZONE_ID );
#&debug_array_print( "�����X�^�[�f�[�^", \@MONS_ID );
#&debug_array_print( "�_���W�����t�@�C���f�[�^", \@DAN_FILE );
#&debug_array_print( "�t�B�[���h�f�[�^", \@FLD_FILE );
#&debug_array_print( "�G���J�E���g�f�[�^", \@ENC_FILE );

#����f�[�^�ǂݍ���
&special_file_pokenum_load();

#�G���J�E���g�f�[�^���番�zID�ƃ����X�^�[NO->���zID����쐬
print( "�G���J�E���g�f�[�^���番�zID�ƃ����X�^�[NO->���zID����쐬\n" );
&enc_data_make();
#&debug_array_print( "�_���W�������zID", \@DAN_ID );
#&debug_array_print( "�t�B�[���h���zID", \@FLD_ID );
#&debug_array_print( "�_���W�������z�Ή�ID", \@DAN_ZONEID );
#&debug_array_print( "�t�B�[���h���z�Ή�ID", \@FLD_ZONEID );
#&debug_array_print( "�_���W��������", \@RANGE_DAN_MO );
#&debug_array_print( "�_���W�����Ђ�", \@RANGE_DAN_NU );
#&debug_array_print( "�_���W�������", \@RANGE_DAN_NI );
#&debug_array_print( "�_���W��������", \@RANGE_DAN_SPECIAL );
#&debug_array_print( "�t�B�[���h����", \@RANGE_FLD_MO );
#&debug_array_print( "�t�B�[���h�Ђ�", \@RANGE_FLD_NU );
#&debug_array_print( "�t�B�[���h���", \@RANGE_FLD_NI );
#&debug_array_print( "�t�B�[���h����", \@RANGE_FLD_SPECIAL );
#&debug_array_print( "�_���W��������OAM", \@DAN_TOKUSYUOAM );

#���������o��
#
#�|�P�������z�t�����f�[�^�����o��
print( "�|�P�������z�t�����f�[�^�����o���J�n\n" );
&make_pokerangedata();
print( "�|�P�������z�t�����f�[�^�����o������\n" );

exit(0);


#------------------------------------------------------------------------------
#
#			�t�B�[���h�f�[�^
#			CSV�`���t�@�C���쐬
#------------------------------------------------------------------------------
sub csv_file_make{
	my( $system_call );

	#�t�B�[���h�O���t�B�b�N�f�[�^
	system( "ExcelSeetConv.exe -o fld_data.txt -n field_zone -s csv map_matrix.xls" );

	#�_���W�����`��ʒu�f�[�^
	system( "ExcelSeetConv.exe -o dan_data.txt -s csv poke_danzyon.xls" );

	#����f�[�^
	if( $DEF_CONV_MODE eq "�_�C��"  ){
		system( "ExcelSeetConv.exe -o ex_mitunuri.txt -p 2 -s csv encdata_ex.xls" );
	}else{
		$system_call = "ExcelSeetConv.exe -o ex_mitunuri.txt -p 3 -s csv encdata_ex.xls";
		system( $system_call );
	}
	system( "ExcelSeetConv.exe -o ex_urayama.txt -n ���R -s csv encdata_ex.xls" );
	system( "ExcelSeetConv.exe -o ex_situgen.txt -n ���� -s csv encdata_ex.xls" );
	
}

#------------------------------------------------------------------------------
#
#			�t�@�C���f�[�^�ǂݍ���
#
#------------------------------------------------------------------------------
sub file_load{
	#�t�B�[���h
	open( FILEIN, "fld_data.txt" );
	@FLD_FILE = <FILEIN>;
	close( FILEIN );
	
	#�_���W����
	open( FILEIN, "dan_data.txt" );
	@DAN_FILE = <FILEIN>;
	close( FILEIN );
	
	#�G���J�E���g
	open( FILEIN, $CONV_FILE_NAME );
	@ENC_FILE = split( "\r",<FILEIN> );
#	@ENC_FILE = <FILEIN>;
	close( FILEIN );
}

#------------------------------------------------------------------------------
#
#			����t�@�C���f�[�^�ǂݍ���
#
#------------------------------------------------------------------------------
sub special_file_pokenum_load{
	my( $skip, @file, @line, $count, $i );

	#�q���o�X
	{
		@HINBASU_POKENO = &mons_name_arry_mons_no_chg( @HINBASU_POKENO );
	}

	#���h��
	{
		open( FILEIN, "ex_mitunuri.txt" );
		@file = <FILEIN>;
		close( FILEIN );
		$skip = 0;
		$count = 0;
		foreach $one ( @file ){
			if( ($skip < 2) || ($skip > 7) ){
				#�X�L�b�v
			}else{
				@line = split( ",", $one );

				for( $i = 1; $i < 3; $i++  ){
					$MITUNURI_POKENO[ $count ] = $line[ $i ];
					$count ++;
				}
			}
			$skip ++;
		}
		$MITUNURI_POKENUM = $count;
		@MITUNURI_POKENO = &mons_name_arry_mons_no_chg(@MITUNURI_POKENO);
	}

	#����
	{
		open( FILEIN, "ex_situgen.txt" );
		@file = <FILEIN>;
		close( FILEIN );

		$skip = 0;
		$count = 0;
		foreach $one ( @file ){
			if( ($skip < 2) || ($skip > 33) ){
				#�X�L�b�v
			}else{
				@line = split( ",", $one );
				$SITUGEN_POKENO[ $count ] = $line[ 1 ];
				$count ++;
			}
			$skip ++;
		}
		$SITUGEN_POKENUM = $count;
		@SITUGEN_POKENO = &mons_name_arry_mons_no_chg(@SITUGEN_POKENO);
	}

	#���R
	{
		open( FILEIN, "ex_urayama.txt" );
		@file = <FILEIN>;
		close( FILEIN );

		$skip = 0;
		$count = 0;
		foreach $one ( @file ){
			if( ($skip < 2) || ($skip > 17) ){
				#�X�L�b�v
			}else{
				@line = split( ",", $one );
				$URAYAMA_POKENO[ $count ] = $line[ 1 ];
				$count ++;
			}
			$skip ++;
		}
		$URAYAMA_POKENUM = $count;
		@URAYAMA_POKENO = &mons_name_arry_mons_no_chg(@URAYAMA_POKENO);
	}
}

#------------------------------------------------------------------------------
#
#			�z��ƒl�𓾂ā@���̒l�̂���v�f����Ԃ�	
#
#			-1�Ȃ�
#
#------------------------------------------------------------------------------
sub arry_no_num_get{
	my( $p_arry, $num ) = @_;
	my( $count );

	for( $count=0; $count < (@$p_arry + 0); $count++ ){

		if( $num eq $$p_arry[ $count ] ){
			return $count;
		}
	}

	return -1;
}


#------------------------------------------------------------------------------
#
#			�]�[��ID�f�[�^�擾	
#
#------------------------------------------------------------------------------
sub zone_id_get{
	my( $filein, $count );

	open( FILEIN, "zone_id.h" );
	@filein = <FILEIN>;
	close( FILEIN );

	foreach $one ( @filein ){
		if( $one =~ /#define ([^ ]*) \(([0-9]*)\)/ ){
			$ZONE_ID[ $2 ] = $1;
		}
	}
}

#------------------------------------------------------------------------------
#
#			�]�[��ID->�]�[���i���o�[�R���o�[�g	
#	param	zone_id	�]�[��ID��
#	return	�]�[��ID�̃i���o�[�@-1=none
#
#------------------------------------------------------------------------------
sub zone_id_num_get{
	my( $zone_id ) =  @_;

	return &arry_no_num_get( \@ZONE_ID, $zone_id );
}

#------------------------------------------------------------------------------
#
#			������->�]�[��ID�R���o�[�g	
#
#		param	�]�[��ID�ɂ�����������
#		return	�]�[��ID��
#
#------------------------------------------------------------------------------
sub zone_id_make{
	my( $zone_name ) = @_;

	#�啶���ɂ���
	$zone_name = uc( $zone_name );
	$zone_name = "ZONE_ID_$zone_name";

	return $zone_name;
}

#------------------------------------------------------------------------------
#
#			�����X�^�[�i���o�[�擾	
#
#------------------------------------------------------------------------------
sub mons_no_get{
	my( $filein, $count );

	open( FILEIN, "monsno.h" );
	@filein = <FILEIN>;
	close( FILEIN );

	foreach $one ( @filein ){
		if( $one =~ /#define\t([^ ]*)\t\(([0-9]*)\)/ ){
			$MONS_ID[ $2 ] = $1;
		}
	}
}

#------------------------------------------------------------------------------
#
#			�����X�^�[NOID->�����X�^�[�i���o�[�R���o�[�g	
#	param	mons_id	�����X�^�[�i���o�[��
#	return	�����X�^�[�i���o�[�@-1=none
#
#------------------------------------------------------------------------------
sub monsno_num_get{
	my( $mons_id ) =  @_;

	return &arry_no_num_get( \@MONS_ID, $mons_id );
}

#------------------------------------------------------------------------------
#
#			�����񃂃��X�^�[�i���o�[ID�R���o�[�g	
#
#		param	�����X�^�[��
#		retrun	�����X�^�[ID��
#
#------------------------------------------------------------------------------
sub mona_no_id_get{
	my( $mons_name, $check );
	my( $filein, $check );

	$mons_name = @_[0];
	$check = @_[1];
	
	if( $mons_name ne $check ){
		open( FILEOUT, "> prev_mons_name.txt" );
		print( FILEOUT $mons_name );
		close( FILEOUT );
		
		system( "mons_no_make.exe prev_mons_name.txt" );

		open( FILEIN, "make_mons_name.txt" );
		$filein = <FILEIN>;
		close( FILEIN );
	}else{

		$fielin = "MONSNO_DUMMY_RANGE";
	}
	


	return $filein;
}


#------------------------------------------------------------------------------
#
#			�_���W�������zID��->�_���W�������zID
#	param	range_dan		�_���W�������zID��
#	return	�_���W�������zID�i���o�[		none=-1
#
#------------------------------------------------------------------------------
sub dan_range_num_get{
	my( $range_dan ) =  @_;
	return &arry_no_num_get( \@DAN_ID, $range_dan );
}

#------------------------------------------------------------------------------
#
#			�t�B�[���h���zID��->�t�B�[���h���zID
#	param	fld_dan		�t�B�[���h���zID��
#	return	�t�B�[���h���zID�i���o�[		none=-1
#
#------------------------------------------------------------------------------
sub fld_range_num_get{
	my( $range_fld ) =  @_;
	return &arry_no_num_get( \@FLD_ID, $range_fld );
}



#------------------------------------------------------------------------------
#
#			�|�P�����G���J�E���g�f�[�^�ǂݍ���
#
#------------------------------------------------------------------------------
sub enc_data_make{
	my( $enc_localfile );
	
	#�S�ėv�f���̓G���J�E���g�f�[�^�v�f��
	#mons~�n��,��؂�Ńf�[�^���쐬
	my( $zone_id );	
	my( $encmons_normal, $encmons_morning, $encmons_night );	#�ʏ�
	my( $encmons_special );	#����
	my( $work, $count );				#��Ɨ̈�
	my( $check );

	foreach $one ( @ENC_FILE ){
		$one =~ s/""/"dummy"/g;	#""���_�~�[�ɕύX�ύX
		$one =~ s/"//g;	#"���J�b�g�ɕύX
#		$one =~ s/\r/,\n/g;	#���s�R�[�h��,�ɕύX
	}

	#�S�G���J�E���g�f�[�^�ǂݍ��݁i�X�ł̓]�[���[�������X�^�[�z��Ƃ����f�[�^�j
	$count = 0;
	foreach $one ( @ENC_FILE ){
		@enc_localfile = split( ",", $one );

		print( "�]�[��ID".$enc_localfile[ 0 ]."\n" );

		#�]�[��ID��
		$zone_id[ $count ] = &zone_id_make( $enc_localfile[ 0 ] );

		#���̃]�[�����{���ɂ��邩�`�F�b�N
		if( &zone_id_num_get($zone_id[ $count ]) != -1 ){
			
			#����	��ꑐ
			@work = ( $enc_localfile[32], $enc_localfile[33], $enc_localfile[34],  $enc_localfile[35] );
			@work = &mons_name_arry_mons_no_chg(@work);
			$encmons_special[ $count ] = join( ',', @work );
	 
			$count ++;
		}
	}

	#���̑��̓���f�[�^�ƕ������ăf�[�^���쐬����
	#���h��
	&special_data_set( \@MITUNURI_POKENO, \@MITUNURI_ZONEID, \@encmons_special, \@zone_id );
	#�q���o�X
	&special_data_set( \@HINBASU_POKENO, \@HINBASU_ZONE_ID, \@encmons_special, \@zone_id );
	
	#���R
	&special_data_set( \@URAYAMA_POKENO, \@URAYAMA_ZONE_ID, \@encmons_special, \@zone_id );
	#����
	&special_data_set( \@SITUGEN_POKENO, \@SITUGEN_ZONE_ID, \@encmons_special, \@zone_id );


	#�]�[��ID����_���W�������zID�ƃt�B�[���h���zID���쐬
	print( "�]�[��ID����_���W�������zID�ƃt�B�[���h���zID���쐬" );
	&make_range_id( \@zone_id );	#@zone_id�̂����zID�ɕύX�����

	#�����X�^�[�i���o�[->���zID��f�[�^�ɕύX���Ă���
	for( $count=0; $count<@MONS_ID; $count++ ){
		#����		�_���W�����͂Ȃ�
		&make_mons_range_data( $count, \@encmons_special, \@zone_id, \@RANGE_DAN_SPECIAL, \@RANGE_FLD_SPECIAL );
	}
}

#����ʃf�[�^�Ɠ���f�[�^��Z��������
sub special_data_set{
	my( $sp_monsno_arry, $sp_zoneid_arry, $encmons_arry, $zoneid_arry ) = @_;
	my( $check, $count, $sp_zoneid_count, @encmons_arry_data );

	for( $sp_zoneid_count = 0; $sp_zoneid_count < @$sp_zoneid_arry; $sp_zoneid_count++ ){
		$check = 0;
		#�����]�[��ID�����邩�`�F�b�N
		for( $count = 0; $count < @$zoneid_arry; $count++ ){
			# �ꏏ�`�F�b�N
			if( $$zoneid_arry[$count] eq $$sp_zoneid_arry[$sp_zoneid_count] ){
				#�������炻�̃J�E���g�l��encmons_arry�Ƀf�[�^��ݒ�			
				@encmons_arry_data = split( ",", $$encmons_arry[ $count ] );
				@encmons_arry_data = ( @encmons_arry_data, @$sp_monsno_arry );	#���ɒǉ�
				$$encmons_arry[ $count ] = join( ",", @encmons_arry_data );	#�ǉ�����
				$check = 1;
			}
		}

		#check ��0�̂܂܂Ȃ�܂��ݒ肵�Ă��Ȃ��̂ŁAzone_id�̂��ɒǉ�����
		if( $check == 0 ){
			#�]�[��ID�ǉ�
			$$zoneid_arry[ @$zoneid_arry ] = $$sp_zoneid_arry[$sp_zoneid_count];
			#�G���J�E���g�����X�^�[�i���o�[�ɒǉ�
			$$encmons_arry[ @$encmons_arry ] = join( ",", @$sp_monsno_arry );
		}
	}
	
};

#���[�N�̒��g�������X�^�[�i���o�[�ɕύX����
sub mons_name_arry_mons_no_chg{
	my( @mons_name ) = @_;
	my( $i );

	for( $i=0; $i<(@mons_name + 0); $i++ ){
		$mons_name[$i] = &mona_no_id_get( $mons_name[$i], "dummy" );	#�|�P������->�����X�^�[ID

		$mons_name[$i] = &monsno_num_get( $mons_name[$i] );	#�����X�^�[ID->�����X�^�[�i���o�[
	}
	return @mons_name;
}

#�����X�^�[�i���o�[���܂܂ꂽ�]�[���̃��X�g���쐬
#	param	mons_no		�����X�^�[�i���o�[
#	param	p_encdata	�G���J�E���g�f�[�^
#	param	p_zone_id	���zID
#	param	p_out_dan	�_���W���������X�^�[���z�f�[�^�����o����
#	param	p_out_fld	�t�B�[���h�����X�^�[���z�f�[�^�����o����
sub make_mons_range_data{
	my( $mons_no, $p_encdata, $p_zone_id, $p_out_dan, $p_out_fld ) = @_;
	my( $one_enc_data, $enc_count, $enc_zone_id );
	my( $out_dan_l, $out_fld_l, $out_dan_count, $out_fld_count, $out_dan_flg, $out_fld_flg );

	@out_dan_l = undef;
	@out_fld_l = undef;	
	$out_dan_count = 0;
	$out_fld_count = 0;

	for( $enc_count = 0; $enc_count<@$p_encdata; $enc_count++ ){

		#�t���O�������@���������X�^�[�i���o�[���e�[�u���ɂ�������ݒ�
		$out_dan_flg = 0;
		$out_fld_flg = 0;
		$enc_zone_id = 0;

		#,�ł����Ĕz��ɂ���
		@one_enc_data = split( ",", $$p_encdata[ $enc_count ] );
		
		#���������X�^�[�i���o�[���`�F�b�N
		foreach $one ( @one_enc_data ){
			if( $one == $mons_no ){

				#���̕��zID���擾
				$enc_zone_id = $$p_zone_id[ $enc_count ];
				
				#���̕��zID���_���W�������t�B�[���h���`�F�b�N
				if( $enc_zone_id =~ /ZKN_DAN/ ){
					#�_���W����
					$out_dan_flg = 1;
				}else{
					#�t�B�[���h
					$out_fld_flg = 1;
				}
				
			}
		}

		#�����̂������t���O����������ݒ�
		if( $out_dan_flg == 1 ){
			#�ȑO�ɓ���ID���ݒ肳��Ă��Ȃ����`�F�b�N
			if( &arry_no_num_get( \@out_dan_l, $enc_zone_id ) == -1 ){
				$out_dan_l[$out_dan_count] = $enc_zone_id;
				$out_dan_count++;
			}
		}
		if( $out_fld_flg == 1 ){
			#�ȑO�ɓ���ID���ݒ肳��Ă��Ȃ����`�F�b�N
			if( &arry_no_num_get( \@out_fld_l, $enc_zone_id ) == -1 ){
				$out_fld_l[$out_fld_count] = $enc_zone_id;
				$out_fld_count++;
			}
		}
	}

	#�ŏI�s��NONE�f�[�^�ǉ�
	$out_dan_l[$out_dan_count] = "ZKN_DAN_ID_NONE";
	$out_fld_l[$out_fld_count] = "ZKN_FLD_ID_NONE";	
	

	#��������X�g��,��؂�̃f�[�^�Ƃ��ď����o��
	$$p_out_dan[ $mons_no ] = join( ",", @out_dan_l );
	$$p_out_fld[ $mons_no ] = join( ",", @out_fld_l );
}


#------------------------------------------------------------------------------
#
#			�]�[��ID����_���W�������zID�@�Ɓ@�t�B�[���h���zID���쐬	
#
#------------------------------------------------------------------------------
sub make_range_id{
	my( $p_zone_id ) = @_;
	my( $i, $zanid_num, $fldid_num, $tmp_id );

	$zanid_num = 0;
	$fldid_num = 0;

	#0�Ԗڂ̓_�~�[�f�[�^�ɂ���
	$DAN_ID[ 0 ] = "ZKN_DAN_ID_NONE";
	$DAN_TOKUSYUOAM[ 0 ] = 0;
	$FLD_ID[ 0 ] = "ZKN_FLD_ID_NONE";
	$zanid_num++;
	$fldid_num++;

	for( $i=0; $i<@$p_zone_id; $i++ ){
		#�_���W�������`�F�b�N
		if( $$p_zone_id[ $i ] =~ /ZONE_ID_([A-Z][0-9]*)[R]/ ){

			#���܂łɈꏏ�̃_���W����ID���������`�F�b�N
			if( ($tmp_id = &dan_range_num_get( "ZKN_DAN_ID_$1" )) == -1 ){	

				#�_���W����
				$DAN_ID[ $zanid_num ] = "ZKN_DAN_ID_$1";
				$DAN_ZONEID[ $zanid_num ] = $$p_zone_id[ $i ];
				#����OAM���ǂ���
				if( &make_dat_data_tokusyuoam($$p_zone_id[$i] ) == 1 ){
					$DAN_TOKUSYUOAM[ $zanid_num ] = 1;
				}else{
					$DAN_TOKUSYUOAM[ $zanid_num ] = 0;
				}

				$$p_zone_id[$i] = $DAN_ID[ $zanid_num ];
				$zanid_num ++;
			}else{

				$$p_zone_id[$i] = $DAN_ID[$tmp_id];
			}
		}else{
			#�t�B�[���h
			$$p_zone_id[ $i ] =~ /ZONE_ID_(.*)/;
			$FLD_ID[ $fldid_num ] = "ZKN_FLD_ID_$1";
			$FLD_ZONEID[ $fldid_num ] = $$p_zone_id[ $i ];

			$$p_zone_id[$i] = $FLD_ID[ $fldid_num ];
			$fldid_num ++;
		}
	}
}

#�_���W�����f�[�^�Ƃ�����OAM���ǂ���
sub make_dat_data_tokusyuoam{
	my( $zone_id ) = @_;
	my( $i );

	for( $i=0; $i<@DAN_TOKUSYUOAM_ZONEID; $i++ ){
		if( $zone_id =~ /$DAN_TOKUSYUOAM_ZONEID[$i]/ ){
			return 1;
		}
	}

	return 0;
}

#------------------------------------------------------------------------------
#
#			�_���W�����O���b�h�f�[�^�ǂݍ���
#
#------------------------------------------------------------------------------
sub load_dan_grid_data{
	my( $dan_id, $dan_gridx, $dan_girdy );
	my( $local_data, $data_count, $i, $j );

	$data_count = 0;
	
	#�f�[�^�擾
	foreach $one ( @DAN_FILE ){
		if( $one =~ /[DR][0-9]*/ ){	#�_���W�����f�[�^����
			@local_data = split( ",", $one );
			$dan_id[ $data_count ] = "ZKN_DAN_ID_".$local_data[1];	#���zID
#			print( "local�_���W����ID $dan_id[ $data_count ]\n" );
			$dan_gridx[ $data_count ] = $local_data[ 3 ];		#�O���b�hX
			$dan_gridy[ $data_count ] = $local_data[ 4 ];		#�O���b�hY

			$data_count ++;
		}
	}

	#0�̓_�~�[�f�[�^
	$DAN_GRID_X[ 0 ] = 0;
	$DAN_GRID_Y[ 0 ] = 0;
	
	#�_���W�������zID�̏��ԂɃO���b�h���W��ݒ�
	for( $i = 1; $i<@DAN_ID; $i++ ){		#0�̓_�~�[�f�[�^
		
		#�_���W�������zID�ƈꏏ�̕��zID�̂��̂����邩�`�F�b�N
		for( $j=0; $j<$data_count; $j++ ){
			
			if( $DAN_ID[ $i ] eq $dan_id[ $j ] ){
				$DAN_GRID_X[ $i ] = $dan_gridx[ $j ];
				$DAN_GRID_Y[ $i ] = $dan_gridy[ $j ];
				last;	
			}
		}

		#����������G���[��Ԃ�
		if( $j == $data_count ){
			print( "�_���W�����O���b�h���W�ɂ͖����]�[���f�[�^���G���J�E���g�f�[�^�ɂ���܂�(".$DAN_ID[ $i ].")\n" );
			exit(1);
		}
	}
}


#------------------------------------------------------------------------------
#
#			�t�B�[���h�n�`�f�[�^�R���o�[�g	
#
#			�O���b�h��30*30�̑傫��
#
#------------------------------------------------------------------------------
sub load_fld_map_data{
	my( $griddata, $split_data, $count, $skip );
	my( $i, $j, $check_word );

	#�O���b�h�f�[�^�ǂݍ���
	$count = 0;
	$skip = 2;
	foreach $one ( @FLD_FILE ){
		@split_data = split( ",", $one );

		#�ŏ��̂Q�s�X�L�b�v
		if( $skip > 0 ){
			$skip --;
			print( "�X�L�b�v�@$one\n" );
		}else{

			if( $count < $DEF_FLD_GRID_SIZE_Y ){
				$griddata[ $count ] = $split_data[1].",".$split_data[2].",".$split_data[3].",".$split_data[4].",".$split_data[5].",".$split_data[6].",".$split_data[7].",".$split_data[8].",".$split_data[9].",".$split_data[10].",".$split_data[11].",".$split_data[12].",".$split_data[13].",".$split_data[14].",".$split_data[15].",".$split_data[16].",".$split_data[17].",".$split_data[18].",".$split_data[19].",".$split_data[20].",".$split_data[21].",".$split_data[22].",".$split_data[23].",".$split_data[24].",".$split_data[25].",".$split_data[26].",".$split_data[27].",".$split_data[28].",".$split_data[29].",".$split_data[30].",";
				$count ++;
			}
		}
	}


	#0�̓_�~�[�f�[�^
	$FLD_GRID_X[0] = 0;
	$FLD_GRID_Y[0] = 0;
	$FLD_SIZE_X[0] = 1;
	$FLD_SIZE_Y[0] = 1;
	$FLD_AREA_ARRY[0] = 1;
	
	#�O���b�h���W������t�B�[���h���zID�ɑΉ�����r�b�g�̌`�𔲂��o��
	for( $i=1; $i<@FLD_ID; $i++ ){		#0�̓_�~�[�f�[�^
		#�܂�����O���b�h�Ɣ͈̓T�C�Y���擾
		$check_word = $FLD_ID[ $i ];
		$check_word =~ s/ZKN_FLD_ID_//g;
		($FLD_GRID_X[$i], $FLD_GRID_Y[$i], $FLD_SIZE_X[$i], $FLD_SIZE_Y[$i]) = &get_upleft_mat( \@griddata, $check_word );

		#����O���b�h���牡�������̃G���A�̃r�b�g�z����쐬
		$FLD_AREA_ARRY[$i] = &get_grid_arry( \@griddata, $FLD_GRID_X[$i], $FLD_GRID_Y[$i], $FLD_SIZE_X[$i], $FLD_SIZE_Y[$i], $check_word );
	}
}


#------------------------------------------------------------------------------
#
#			�O���b�h�f�[�^���獶��O���b�h�Ɣ͈̓T�C�Y���擾	
#
#------------------------------------------------------------------------------
sub get_upleft_mat{
	my( $p_griddata, $check_word ) = @_;
	my( $gridx, $gridy, $ulgridy, $ulgridx, $drgridx, $drgridy, $xgirddata );
	my( $ul_hit_flg, $sizex, $sizey, $work );

	#����Ƀq�b�g�������t���O
	$ul_hit_flg = 0;
	

	#�ŏ��Ƀq�b�g����ꏊ������		�Ō�Ƀq�b�g�����O���b�h���E��
	for( $gridy=0; $gridy<@$p_griddata; $gridy++ ){
		@xgriddata = split( ",", $$p_griddata[ $gridy ] );

		#���T�[�`
		for( $gridx=0; $gridx<@xgriddata; $gridx++ ){

			#����ID�Ȃ獶�ォ�E���O���b�h�擾
			if( $check_word eq uc( $xgriddata[ $gridx ] ) ){

				if( $ul_hit_flg == 0 ){
					($ulgridx, $ulgridy) = ($gridx, $gridy);	#������W�擾
					($drgridx, $drgridy) = ($gridx, $gridy);	#�E�����W�擾
					$ul_hit_flg = 1;
				}else{
					($drgridx, $drgridy) = ($gridx, $gridy);	#�E�����W�擾
				}
			}
		}
	}

	if( $ul_hit_flg < 1 ){
		print( "�G���J�E���g�f�[�^�ɂ���]�[����񂪃t�B�[���h�n�`�f�[�^�ɂȂ�".$check_word."\n" );
		exit(1);
	}

	$sizey = (1 + $drgridy) - $ulgridy;

	#�����ǂ������`�F�b�N
	if( $drgridx < $ulgridx ){
		$work = $drgridx;
		$drgridx = $ulgridx;
		$ulgridx = $work;
	}
	$sizex = (1+$drgridx) - $ulgridx;

	return ( $ulgridx, $ulgridy, $sizex, $sizey );
}

#------------------------------------------------------------------------------
#
#			�O���b�h�͈̓f�[�^�쐬	
#
#------------------------------------------------------------------------------
sub get_grid_arry{
	my( $p_griddata, $ulgridx, $ulgridy, $sizex, $sizey, $check_word ) = @_;
	my( $i, $j, $griddatax, $retdata, $retcount );

	$retcount = 0;
	@retdata = undef;
	
	for( $i=$ulgridy; $i<$ulgridy+$sizey; $i++ ){
			
		@griddatax = split( ",", $$p_griddata[ $i ] );
		
		for( $j=$ulgridx; $j<$ulgridx+$sizex; $j++ ){

			#�`�F�b�N���[�h�ƈꏏ�̃O���b�h�i���o�[��1����ȊO��0
			if( uc( $griddatax[ $j ] ) eq $check_word ){
				$retdata[ $retcount ] = 1;
			}else{
				$retdata[ $retcount ] = 0;
			}
			$retcount ++;
		}
	}

	return join(",", @retdata);
}



#------------------------------------------------------------------------------
#
#			�_���W�������zID�@�t�B�[���h���zID�o��
#
#------------------------------------------------------------------------------
sub make_range_id_header{
	my( $i );
	
	open( FILEOUT, ">zkn_rangeid.h" );



	print(FILEOUT "#ifndef __ZKN_RANGEID_H__\r\n" );
	print(FILEOUT "#define __ZKN_RANGEID_H_\r\n\r\n" );

	print(FILEOUT "/* �t�B�[���h���zID */\r\n" );
	#�t�B�[���h���zID
	for( $i=0; $i<@FLD_ID; $i++ ){

		print( FILEOUT "#define ".$FLD_ID[$i]." (".$i.")\r\n" );
	}
	#�Ō�ɍő吔�������o��
	print( FILEOUT "#define ZKN_FLD_ID_MAX (".$i.")\r\n" );

	print(FILEOUT "/* �_���W�������zID */\r\n" );
	#�_���W�������zID
	for( $i=0; $i<@DAN_ID; $i++ ){

		print( FILEOUT "#define ".$DAN_ID[$i]." (".$i.")\r\n" );
	}
	#�Ō�ɍő吔�������o��
	print( FILEOUT "#define ZKN_DAN_ID_MAX (".$i.")\r\n" );

	print(FILEOUT "#endif //__ZKN_RANGEID_H__\r\n" );

	close( FILEOUT );
}

#------------------------------------------------------------------------------
#
#			���zID�ƃ]�[��ID�̑Ή��\�̏����o��
#
#			���zID�̏���int�T�C�Y�������o��
#
#------------------------------------------------------------------------------
sub make_rangeid_zoneid_link{
	my( $i, $zoneid_no, $hide );
	
	open( FILEOUT, ">zkn_rangeid_zoneid_link.c" );
	open( DATFILEOUT_DAN, ">zkn_dan_id.rzidlink" );
	binmode( DATFILEOUT_DAN );
	open( DATFILEOUT_FLD, ">zkn_fld_id.rzidlink" );
	binmode( DATFILEOUT_FLD );


	print( FILEOUT "/* �t�B�[���h���zID�̑Ή��\ */\n\n" );
	print( FILEOUT "struct const u16 ZKN_FLD_RANGEID_ZONEID[] = {\n" );

	
	#�t�B�[���h���zID
	for( $i=0; $i<@FLD_ID; $i++ ){
		#�]�[��ID�̃i���o�[�擾
		$zoneid_no = &zone_id_num_get( $FLD_ZONEID[$i] );

		print( DATFILEOUT_FLD pack("I", $zoneid_no) );
		print( FILEOUT "\t".$zoneid_no.",\n" );
	}
	print( FILEOUT "};\n" );

	print( FILEOUT "/* �_���W�������zID�̑Ή��\ */ \n\n" );
	print( FILEOUT "struct const u16 ZKN_DAN_RANGEID_ZONEID[] = {\n" );


	#�_���W�������zID
	for( $i=0; $i<@DAN_ID; $i++ ){
		#�]�[��ID�̃i���o�[�擾
		$zoneid_no = &zone_id_num_get( $DAN_ZONEID[$i] );
	
		print( DATFILEOUT_DAN pack("I", $zoneid_no) );
		print( FILEOUT "\t".$zoneid_no.",\n" );
	}
	print( FILEOUT "};\n" );

	close( FILEOUT );
	close( DATFILEOUT_DAN );
	close( DATFILEOUT_FLD );
}

#------------------------------------------------------------------------------
#
#			�B���}�b�v�@�]�[��ID�ƕ��zID�̑Ή��\�̏����o��
#	
#------------------------------------------------------------------------------
sub make_hidemap_file{
	my( $i, $zoneid, $j, $count );

	$count = 0;
	
	open( FILEOUT, ">zkn_hidemap.dat" );

	#�B���}�b�v�����[�v
	for( $i=0; $i<@HIDEMAP_ZONEID; $i++ ){
		print( FILEOUT "/* $HIDEMAP_ZONEID[$i] �̃t�B�[���h���zID */\n" );
		print( FILEOUT "static const u16 ZKN_FLD_$HIDEMAP_ZONEID[$i]_IDTBL[] = {\n" );
		for( $j=0; $j<@FLD_ID; $j++ ){

			if( $FLD_ZONEID[$j] eq $HIDEMAP_ZONEID[$i] ){
				print( FILEOUT "\t".$j.",\n" );
			}
		}
		print( FILEOUT "\t0xffff,\n" );
		print( FILEOUT "};\n" );


		print( FILEOUT "/* $HIDEMAP_ZONEID[$i] �̃_���W�������zID */\n" );
		print( FILEOUT "static const u16 ZKN_DAN_$HIDEMAP_ZONEID[$i]_IDTBL[] = {\n" );
		$zoneid = $HIDEMAP_ZONEID[$i];
		for( $j=0; $j<@DAN_ID; $j++ ){
			if( $DAN_ZONEID[$j] =~ /$zoneid[R]/ ){
				print( FILEOUT "\t".$j.",\n" );
			}
		}
		print( FILEOUT "\t0xffff,\n" );
		print( FILEOUT "};\n" );
	}

	close( FILEOUT );
}

#------------------------------------------------------------------------------
#
#			�|�P�������z�f�[�^�t�����f�[�^�����o��
#
#------------------------------------------------------------------------------
sub make_pokerangedata{

	#�_���W�������ꕪ�z�t�@�C���͂Ȃ��̂ł��������Ȃ�
	&make_mons_rang_out_file_dan( \@RANGE_DAN_SPECIAL, "zkn_dan_range_special_comp_mons", "�����X�^�[�_���W�������ꕪ�zID�@�}�ӊ�����\r\n" );

	#�t�B�[���h���ꕪ�z�t�@�C��
	&make_mons_rang_out_file_fld( \@RANGE_FLD_SPECIAL, "zkn_fld_range_special_comp_mons", "�����X�^�[�t�B�[���h���ꕪ�zID�@�}�ӊ�����\r\n" );
}

#�����o�����C��
#�_���W�����p
sub make_mons_rang_out_file_dan{
	my( $range_data, $output_file, $output_txt_header ) = @_;
	my( $i, $j, $out_data, $range_id);

	for( $i=0; $i<@$range_data; $i++ ){
		@out_data = split( ",", $$range_data[ $i ] );

		if ( $i < 10 ){	
				open( OUTFILETXT, ">".$output_file."_00".$i.".txt" );
				open( OUTFILE, ">".$output_file."_00".$i.".mrang" );
		}else{
			if( $i < 100 ){
				open( OUTFILETXT, ">".$output_file."_0".$i.".txt" );
				open( OUTFILE, ">".$output_file."_0".$i.".mrang" );
			}else{
				open( OUTFILETXT, ">".$output_file."_".$i.".txt" );
				open( OUTFILE, ">".$output_file."_".$i.".mrang" );
			}
		}

		binmode( OUTFILE );

		print( OUTFILETXT $output_txt_header."\r\n" );
		for( $j=0; $j<@out_data; $j++ ){

			$range_id = &dan_range_num_get( $out_data[$j] );
			
			print( OUTFILETXT $out_data[$j].",\r\n" );	
			print( OUTFILE pack("I", $range_id) );
		}
		close( OUTFILE );
		close( OUTFILETXT );
	}
}
#�t�B�[���h�p
sub make_mons_rang_out_file_fld{
	my( $range_data, $output_file, $output_txt_header ) = @_;
	my( $i, $j, $out_data, $range_id);

	for( $i=0; $i<@$range_data; $i++ ){
		@out_data = split( ",", $$range_data[ $i ] );	
		
		if( $i < 10 ){
			open( OUTFILETXT, ">".$output_file."_00".$i.".txt" );
			open( OUTFILE, ">".$output_file."_00".$i.".mrang" );
		}else{
			if( $i < 100 ){
				open( OUTFILETXT, ">".$output_file."_0".$i.".txt" );
				open( OUTFILE, ">".$output_file."_0".$i.".mrang" );
			}else{
				open( OUTFILETXT, ">".$output_file."_".$i.".txt" );
				open( OUTFILE, ">".$output_file."_".$i.".mrang" );
			}
		}

		binmode( OUTFILE );

		print( OUTFILETXT $output_txt_header."\r\n" );
		for( $j=0; $j<@out_data; $j++ ){

			$range_id = &fld_range_num_get( $out_data[$j] );
			
			print( OUTFILETXT $out_data[$j].",\r\n" );	
			print( OUTFILE pack("I", $range_id) );
		}
		close( OUTFILE );
		close( OUTFILETXT );
	}
}


#------------------------------------------------------------------------------
#
#			�_���W�����O���b�h�f�[�^�����o��	
#			GRIDX GRIDY  ����OAM(0,1) dammy
#			ucahr	uchar uchar			uchar
#
#------------------------------------------------------------------------------
sub make_dan_grid_data{
	my( $i );

	open( OUTFILETXT, ">zkn_dan_griddata.txt" );
	open( OUTFILE, ">zkn_dan_griddata.dangri" );
	binmode( OUTFILE );
	
	print( OUTFILETXT "�_���W�����O���b�h���W����OAM�f�[�^\r\n" );
	#DAN_GRID_X��Y�͓����v�f��
	for( $i=0; $i<@DAN_GRID_X; $i++ ){
		
		print( OUTFILETXT "�_���W����ID[".$i."] x�O���b�h[".$DAN_GRID_X[$i]."] ���O���b�h[".$DAN_GRID_Y[$i]."]����OAM[".$DAN_TOKUSYUOAM[$i]."]\r\n" );
		
		print( OUTFILE pack( "C", $DAN_GRID_X[$i] ) );	
		print( OUTFILE pack( "C", $DAN_GRID_Y[$i] ) );	
		print( OUTFILE pack( "C", $DAN_TOKUSYUOAM[$i] ) );	
		print( OUTFILE pack( "C", 0 ) );	
	}

	close( OUTFILE );
	close( OUTFILETXT );
}

#------------------------------------------------------------------------------
#
#			�t�B�[���h�n�`�f�[�^	
#		
#		�O���b�hX�@�O���b�hY�@�T�C�YX�@�T�C�YY�@�z��i[$DEF_FLD_AREA_DATA_ARRY_OUTSIZE]�v�f�Œ�j
#		uchar		uchar		uchar	uchar	uchar(�z��)
#------------------------------------------------------------------------------
sub make_fld_grid_data{
	my($i);

	open(OUTFILE, ">zkn_fld_griddata.fldgri");
	binmode( OUTFILE );

	#�t�B�[���hID��FLD�S�z��͗v�f���ꏏ
	for( $i=0; $i<@FLD_ID; $i++ ){
		&output_fld_fld_data( $i, $FLD_GRID_X[$i], $FLD_GRID_Y[$i], $FLD_SIZE_X[$i], $FLD_SIZE_Y[$i], $FLD_AREA_ARRY[$i], "zkn_fld_griddata", "�t�B�[���h�n�`�f�[�^\r\n" );
	}

	close( OUTFILE );
}
#�����o��
sub output_fld_fld_data{
	my( $count, $gridx, $gridy, $sizex, $sizey, $arry, $output_file, $output_txt_header ) = @_;
	my( $i, $j, $out_data);

	if( $count < 10 ){
		open( OUTFILETXT, ">".$output_file."_00".$count.".txt" );
	}else{
		if( $count < 100 ){
			open( OUTFILETXT, ">".$output_file."_0".$count.".txt" );
		}else{
			open( OUTFILETXT, ">".$output_file."_".$count.".txt" );
		}
	}

	print( OUTFILETXT $output_txt_header."\r\n" );


	print( OUTFILETXT "�O���b�h�� [$gridx] " );
	print( OUTFILETXT "�O���b�h�� [$gridy] " );
	print( OUTFILETXT "�T�C�Y�� [$sizex] " );
	print( OUTFILETXT "�T�C�Y�� [$sizey]\r\n" );

	print( OUTFILE pack("C", $gridx) );
	print( OUTFILE pack("C", $gridy) );
	print( OUTFILE pack("C", $sizex) );
	print( OUTFILE pack("C", $sizey) );
		
	#�z��f�[�^
	@out_data = split( ",",$arry );	
	for( $i=0; $i<$sizey; $i++ ){
		
		for( $j=0; $j<$sizex; $j++ ){
			print( OUTFILETXT $out_data[($i * $sizex) + $j]."," );
			print( OUTFILE pack("C", $out_data[($i * $sizex) + $j]) );
		}
		print( OUTFILETXT "\r\n" );
	}
	#4�o�C�g�A���C�����g
	for( $i = $DEF_FLD_AREA_DATA_ARRY_OUTSIZE - ($sizex*$sizey); $i>0; $i-- ){
		print( OUTFILE pack("C", 0) );
	}
	
	close( OUTFILETXT );

}


#------------------------------------------------------------------------------
#
#			�z��f�[�^�����o��	
#
#------------------------------------------------------------------------------
sub debug_array_print{
	my( $comment, $data ) = @_;

	print( "$comment\n" );

	foreach $one ( @$data ){
		print( "$one\n" );
	}
}


#excel_form_csv.txt��excel_worldid_csv.txt
#����`ID�w�b�_�ƌ���ID�w�b�_���쐬
#
#excel_csv.txt�̒��̊Y������ID���𐔎��ɕύX


#-----------------------------------------------------------------------------
#	�O���[�o���f�[�^
#-----------------------------------------------------------------------------
@FORM_ID = undef;		#�`ID�i�[��

@FORM_FILE = undef;		#�`IDCSV�`���t�@�C���ǂݍ��݃f�[�^
@EXCEL_FILE = undef;	#EXCEL�t�@�C���ǂݍ��݃f�[�^


#-----------------------------------------------------------------------------
#	���C�����[�v	
#-----------------------------------------------------------------------------

#�t�@�C���ǂݍ���
&file_load();

#�`ID�i�[
&form_id();

#�萔�𐔎��ɕύX����
&excel_id_num_conv();

#�ύX��EXCEL�t�@�C�������o��
&excel_file_write();

#�`ID�w�b�_�[�����o��
&form_header_write();

exit(0);



#-----------------------------------------------------------------------------
#	�t�@�C���ǂݍ���
#-----------------------------------------------------------------------------
sub file_load {
	open( INFILE, "excel_form_csv.txt" );
	@FORM_FILE = <INFILE>;
	close( INFILE );

	open( INFILE, "excel_csv.txt" );
	@EXCEL_FILE = <INFILE>;
	close( INFILE );
}


#-----------------------------------------------------------------------------
#	�`ID�؂���
#-----------------------------------------------------------------------------
sub form_id{
	
	my( @one_file, $count, $skip );
	
	$count = 0;
	$skip = 0;

	foreach $one ( @FORM_FILE ){

		if( $skip == 1 ){
		
			@one_file = split( "\t", $one );

			$FORM_ID[ $count ] = $one_file[0];
			$count++;
		}else{
			$skip = 1;
		}
	}
}


#-----------------------------------------------------------------------------
#	EXCEL�萔�𐔎��ɕύX
#-----------------------------------------------------------------------------
sub excel_id_num_conv{
	my( $i, $j );
	
	for( $j = 0; $j < @EXCEL_FILE; $j++ ){
		
		#�`
		for( $i=0; $i<@FORM_ID; $i++ ){
			$EXCEL_FILE[$j] =~ s/$FORM_ID[$i]/$i/g;
		}
	}
}


#-----------------------------------------------------------------------------
#	excel�t�@�C�������o��
#-----------------------------------------------------------------------------
sub excel_file_write{
	open( FILEOUT, ">excel_csv.txt" );
	print( FILEOUT @EXCEL_FILE );
	close( FILEOUT );
}

#-----------------------------------------------------------------------------
#	�`ID�w�b�_�[�����o��
#-----------------------------------------------------------------------------
sub form_header_write{

	my( $i );
	
	open( FILEOUT, ">zkn_form_id.h" );

	print(FILEOUT "/* �`ID�@�w�b�_�[�t�@�C�� */\r\n" );
	print(FILEOUT "#ifndef __ZKN_FORM_ID_H__\r\n" );
	print(FILEOUT "#define __ZKN_FORM_ID_H__\r\n" );

	for( $i=0; $i<@FORM_ID; $i++ ){	
		print(FILEOUT "#define ".$FORM_ID[ $i ]."	(".$i.")\r\n" );
	}

	print(FILEOUT "#endif // __ZKN_FORM_ID_H__\r\n" );

	close( FILEOUT );
}

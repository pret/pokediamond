#
#			�����|�P�����f�[�^�@�R���o�[�^�[
#			�f�[�^���S�Œ�
#
@FLD_TRADE_FILE = undef;	#�f�[�^�t�@��
@MONSNO_H_FILE	= undef;	#�����X�^�[�i���o�[�f�t�@�C��
@TOKUSYU_H_FILE	= undef;	#����i���o�[�f�t�@�C��
@ITEMSYM_H_FILE = undef;	#�A�C�e���i���o�[�f�t�@�C��
@PMVER_H_FILE = undef;		#���R�[�h�i���o�[�f�t�@�C��
@OUTPUT0_FILE = undef;		#�����o���f�[�^
@OUTPUT1_FILE = undef;		#�����o���f�[�^
@OUTPUT2_FILE = undef;		#�����o���f�[�^
@OUTPUT3_FILE = undef;		#�����o���f�[�^

#############################################################
#
#	���C������
#
#############################################################

#�t�@�C���ǂݍ���
&file_open();

$count = 0;
foreach $one ( @FLD_TRADE_FILE ){

	#0���ڂ̓_�~�[�f�[�^
	if( $count > 0 ){
		@line = split( "\t", $one );

		if( $count == 1 ){		#�����X�^�[�i���o�[
			$OUTPUT0_FILE[0] = &get_monsno($line[1] );
			$OUTPUT1_FILE[0] = &get_monsno($line[4] );
			$OUTPUT2_FILE[0] = &get_monsno($line[7] );
			$OUTPUT3_FILE[0] = &get_monsno($line[10] );
		}elsif( ($count >= 3) && ($count <= 8) ){	#HP�����`���h����
			$OUTPUT0_FILE[ 1+($count - 3) ] = $line[1];
			$OUTPUT1_FILE[ 1+($count - 3) ] = $line[4];
			$OUTPUT2_FILE[ 1+($count - 3) ] = $line[7];
			$OUTPUT3_FILE[ 1+($count - 3) ] = $line[10];
		}elsif( $count == 9 ){	#����
			$OUTPUT0_FILE[ 7 ] = &get_tokusyu($line[1] );
			$OUTPUT1_FILE[ 7 ] = &get_tokusyu($line[4] );
			$OUTPUT2_FILE[ 7 ] = &get_tokusyu($line[7] );
			$OUTPUT3_FILE[ 7 ] = &get_tokusyu($line[10] );
		}elsif( ($count >= 10) && ($count <= 16) ){	#ID�`RND
			$OUTPUT0_FILE[ 8+($count - 10) ] = $line[1];
			$OUTPUT1_FILE[ 8+($count - 10) ] = $line[4];
			$OUTPUT2_FILE[ 8+($count - 10) ] = $line[7];
			$OUTPUT3_FILE[ 8+($count - 10) ] = $line[10];
		}elsif( $count == 17 ){	#�A�C�e��
			$OUTPUT0_FILE[ 15 ] = &get_item($line[1] );
			$OUTPUT1_FILE[ 15 ] = &get_item($line[4] );
			$OUTPUT2_FILE[ 15 ] = &get_item($line[7] );
			$OUTPUT3_FILE[ 15 ] = &get_item($line[10] );
		}elsif( ($count >= 19) && ($count <= 20) ){	#�e���ʁ@��
			$OUTPUT0_FILE[ 16+($count - 19) ] = $line[1];
			$OUTPUT1_FILE[ 16+($count - 19) ] = $line[4];
			$OUTPUT2_FILE[ 16+($count - 19) ] = $line[7];
			$OUTPUT3_FILE[ 16+($count - 19) ] = $line[10];
		}elsif( $count == 21 ){		#���R�[�h
			$OUTPUT0_FILE[ 18 ] = &get_pmver($line[1] );
			$OUTPUT1_FILE[ 18 ] = &get_pmver($line[4] );
			$OUTPUT2_FILE[ 18 ] = &get_pmver($line[7] );
			$OUTPUT3_FILE[ 18 ] = &get_pmver($line[10] );
		}elsif( $count == 22 ){		#��������|�P����
			$OUTPUT0_FILE[ 19 ] = &get_monsno($line[1] );
			$OUTPUT1_FILE[ 19 ] = &get_monsno($line[4] );
			$OUTPUT2_FILE[ 19 ] = &get_monsno($line[7] );
			$OUTPUT3_FILE[ 19 ] = &get_monsno($line[10] );
		}
	}
	$count ++;
}


#�����o��
open( FILEOUT_0, ">fld_trade_00.dat" );
open( FILEOUT_0_T, ">fld_trade_00.txt" );
binmode( FILEOUT_0 );
open( FILEOUT_1, ">fld_trade_01.dat" );
open( FILEOUT_1_T, ">fld_trade_01.txt" );
binmode( FILEOUT_1 );
open( FILEOUT_2, ">fld_trade_02.dat" );
open( FILEOUT_2_T, ">fld_trade_02.txt" );
binmode( FILEOUT_2 );
open( FILEOUT_3, ">fld_trade_03.dat" );
open( FILEOUT_3_T, ">fld_trade_03.txt" );
binmode( FILEOUT_3 );

for( $i=0; $i<20; $i++ ){
	print( FILEOUT_0 pack("I", $OUTPUT0_FILE[$i]) );
	print( FILEOUT_1 pack("I", $OUTPUT1_FILE[$i]) );
	print( FILEOUT_2 pack("I", $OUTPUT2_FILE[$i]) );
	print( FILEOUT_3 pack("I", $OUTPUT3_FILE[$i]) );

	print( FILEOUT_0_T $OUTPUT0_FILE[$i]."\r\n" );
	print( FILEOUT_1_T $OUTPUT1_FILE[$i]."\r\n" );
	print( FILEOUT_2_T $OUTPUT2_FILE[$i]."\r\n" );
	print( FILEOUT_3_T $OUTPUT3_FILE[$i]."\r\n" );
}

close( FILEOUT_0 );
close( FILEOUT_1 );
close( FILEOUT_2 );
close( FILEOUT_3 );

close( FILEOUT_0_T );
close( FILEOUT_1_T );
close( FILEOUT_2_T );
close( FILEOUT_3_T );


exit(0);


sub file_open{
	system( "../../../convert/exceltool/ExcelSeetConv -s tab fld_trade.xls" );
	open( FILEIN, "fld_trade.txt" );
	@FLD_TRADE_FILE = <FILEIN>;
	close( FILEIN );

	open( FILEIN, "monsno.h" );
	@MONSNO_H_FILE = <FILEIN>;
	close( FILEIN );

	open( FILEIN, "tokusyu_def.h" );
	@TOKUSYU_H_FILE = <FILEIN>;
	close( FILEIN );

	open( FILEIN, "itemsym.h" );
	@ITEMSYM_H_FILE = <FILEIN>;
	close( FILEIN );

	open( FILEIN, "pm_version.h" );
	@PMVER_H_FILE = <FILEIN>;
	close( FILEIN );
}
sub get_monsno{
	my( $key )  = @_;
	
	foreach $one ( @MONSNO_H_FILE ){

		if( $one =~ /#define\t*$key\t*\(([0-9]*)\)/ ){
			return $1;	#�q�b�g�����i���o�[��Ԃ�
		}
	}
	return 0;
}
sub get_tokusyu{
	my( $key )  = @_;
	
	foreach $one ( @TOKUSYU_H_FILE ){

		if( $one =~ /#define\t*$key\t*\(([0-9]*)\)/ ){
			return $1;	#�q�b�g�����i���o�[��Ԃ�
		}
	}
	return 0;
	
}
sub get_item{
	my( $key )  = @_;
	
	foreach $one ( @ITEMSYM_H_FILE ){

		if( $one =~ /#define $key\t*\( ([0-9]*) \)/ ){
			return $1;	#�q�b�g�����i���o�[��Ԃ�
		}
	}
	return 0;
}
sub get_pmver{
	my( $key )  = @_;
	
	foreach $one ( @PMVER_H_FILE ){

		if( $one =~ /#define\t*$key\t*([0-9]*)/ ){
			return $1;	#�q�b�g�����i���o�[��Ԃ�
		}
	}
	return 0;
}

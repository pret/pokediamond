#�G�N�Z���̉��s\r\n��\n�ɂ���
#"�𖳂���
if( @ARGV < 1 ){
	print( "���� �ϊ��t�@�C���p�X\n" );
	exit 1;
}

#�t�@�C���I�[�v��
open( INFILE, $ARGV[ 0 ] );
@file_data = <INFILE>;
close( INFILE );

$count = 0;
$flag	= 0;

#�ŏ��̂P�A�Q�s�͍��ږ��Ȃ̂Ŕj��
foreach $data( @file_data ){
	while( $data =~ s/"// ){};
	while( $data =~ s/\r\n/\t/ ){};

	#�A�����Ă���\t�͂��������̂Ŏ��
	while( $data =~ s/\t\t/\t/ ){};

	if( $flag < 2 ){
		
		$flag++;
	}else{

		$out_put[ $count ] = $data;
		$count++;
	}
}

#��ԍŌ�̓_�����
#@tmp = split( "\t", $out_put[ $count - 1 ] );
#$out_put[ $count - 1 ] = join( "\t", @tmp );


open( OUTFILE, ">$ARGV[ 0 ]" );
print( OUTFILE @out_put );
close( OUTFILE );

exit 0;


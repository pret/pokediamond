#エクセルの改行\r\nを\nにする
#"を無くす
if( @ARGV < 1 ){
	print( "引数 変換ファイルパス\n" );
	exit 1;
}

#ファイルオープン
open( INFILE, $ARGV[ 0 ] );
@file_data = <INFILE>;
close( INFILE );

$count = 0;
$flag	= 0;

#最初の１、２行は項目名なので破棄
foreach $data( @file_data ){
	while( $data =~ s/"// ){};
	while( $data =~ s/\r\n/\t/ ){};

	#連続している\tはおかしいので取る
	while( $data =~ s/\t\t/\t/ ){};

	if( $flag < 2 ){
		
		$flag++;
	}else{

		$out_put[ $count ] = $data;
		$count++;
	}
}

#一番最後の点を取る
#@tmp = split( "\t", $out_put[ $count - 1 ] );
#$out_put[ $count - 1 ] = join( "\t", @tmp );


open( OUTFILE, ">$ARGV[ 0 ]" );
print( OUTFILE @out_put );
close( OUTFILE );

exit 0;


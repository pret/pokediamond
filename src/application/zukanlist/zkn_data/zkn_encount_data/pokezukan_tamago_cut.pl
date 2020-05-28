#タマゴという言葉の含まれている
#行をカット

use Encode;

@OutPut = undef;
open( FILEIN, "pokezukan.txt" );
@PokeZukanData = <FILEIN>;
close( FILEIN );

$count = 0;
foreach $one ( @PokeZukanData ){

	$one = encode('euc-jp', decode('shiftjis', $one));

	if( $one =~ /タマゴ/ ){
		print( $one."カット\n" );
	}else{
		print( $one."イン\n" );
		$OutPut[ $count ] = $one;
		$count ++;
	}
}

open( FILEOUT, ">pokezukan.txt" );
foreach $one ( @OutPut ){
	$one = encode('shiftjis', decode('euc-jp', $one));
	print( FILEOUT $one );
}
close( FILEOUT );

#���ޥ��Ȥ������դδޤޤ�Ƥ���
#�Ԥ򥫥å�

use Encode;

@OutPut = undef;
open( FILEIN, "pokezukan.txt" );
@PokeZukanData = <FILEIN>;
close( FILEIN );

$count = 0;
foreach $one ( @PokeZukanData ){

	$one = encode('euc-jp', decode('shiftjis', $one));

	if( $one =~ /���ޥ�/ ){
		print( $one."���å�\n" );
	}else{
		print( $one."����\n" );
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

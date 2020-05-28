
use Encode;

#エクセルの改行\r\nを\nにする
#"を無くす
if( @ARGV < 1 ){
	print( "引数 変換ファイルパス\n" );
	exit 1;
}

open( OUTERRFILE, ">err.txt" );


#ファイルオープン
open( INFILE, $ARGV[ 0 ] );
#ファイルサイズ取得
$fileSize = -s $ARGV[ 0 ];
print( OUTERRFILE "file = $fileSize" );
sysread( INFILE, $file_arry, $fileSize );

close( INFILE );

#utf16->utf8		ExcelConvでUnicode書き出しだとutf16なのでutf8に変換(gmmはutf8)
$file_arry = &enc_utf16_to_utf8( $file_arry );
print( OUTERRFILE $file_arry );

#1次元から２次元へ
@file_data = split( "\r\n", $file_arry );

$count = 0;
$flag	= 0;
#最初の１、２行は項目名なので破棄
for( $flag = 0; $flag < @file_data; $flag++ ){
	while( $file_data[ $flag ] =~ s/"// ){};
#	while( $file_data[ $flag ] =~ s/\r\n/\t/ ){};
	while( $file_data[ $flag ] =~ s/\t\t/\t/ ){};

	if( $flag >= 2 ){
		$out_put[ $count ] = $file_data[ $flag ]."\t";	#splitで\r\nが排除されているのでその部分にタブを追加
		$count++;
	}
}

#
##最初の１、２行は項目名なので破棄
#foreach $data( @file_data ){
#
#	while( $data =~ s/"// ){};
#	while( $data =~ s/\r\n/\t/ ){};
#
#	if( $flag < 2 ){
#		
#		$flag++;
#	}else{
#
#		$out_put[ $count ] = $data;
#		$count++;
#	}
#}

#一番最後の点を取る
@tmp = split( "\t", $out_put[ $count - 1 ] );
$out_put[ $count - 1 ] = join( "\t", @tmp );


open( OUTFILE, ">$ARGV[ 0 ]" );
print( OUTFILE @out_put );
close( OUTFILE );


close( OUTERRFILE );

exit 0;

#======================================================
# 文字列のutf8フラグを落とし、utf16コンバートする（ヘッダ出力用）
# input : 0:文字列
# return 変換後の文字列
#======================================================
sub enc_utf16_to_utf8 {
	my $txt = shift;

	if(utf8::is_utf8($txt))
	{
		utf8::encode($txt);
	}
	
	Encode::from_to($txt, 'utf16-le', 'utf8');
	return $txt;
}


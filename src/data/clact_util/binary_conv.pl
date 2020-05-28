#指定されたバイト数単位にファイルの中身を書き出すシステム
#引数１
#	書き出すときのバイト単位
#		C	1byte単位
#		S	2byte単位
#		I	4byte単位
#
#引数２
#	コンバートファイルパス
#		ファイルは,区切りのファイルである必要があります。
#		また、引数１バイト以上のデータは入れないでください。
#	書式例）
#		1,2,3,4,5,6,7,8,	comment部
#		3,5,6,7,8,5,4,23,435,	comment部
#		345,123,	comment部
#引数３
#	コンバート後ファイルパス
#
#戻り値
#	成功	0
#	失敗	1

#引数は３つ必要です。
#
#文字の時は文字コードを返します。
if( @ARGV < 3 ){

	print( "err--引数は３つ必要です。\nparam1 byte size\nparam2 conv file path\nparam3 output file path\n" );
	print( "param1 byte size::::::::::::::::::::\n" );
	print( "C 1byte S 2byte I 4byte\n" );

	exit(1);
}

#ファイルオープン
open( FILEIN, $ARGV[1] );
@in_file = <FILEIN>;
if( @in_file == 0 ){
	print( "$ARGV[1]オープン失敗\n" );	
	exit(1);
}
close( FILEIN );


open( FILEOUT, ">$ARGV[2]" );

binmode( FILEOUT );

#書き出しバイトサイズを取得しておく
if( $ARGV[0] eq "C" ){
	$out_byte = 1;
}elsif( $ARGV[0] eq "S" ){
	$out_byte = 2;
}elsif( $ARGV[0] eq "I" ){
	$out_byte = 4;
}

#binaryで書き出す
foreach $one( @in_file ){

	#改行の前の,から改行までを排除
	$one =~ s/,[^,]*\r*\n/\n/;
	
	#タブスペースを排除
	$one =~ s/\s//g;
	$one =~ s/\t//g;

	#改行コードを破棄
	$one =~ s/\n//;
	
	
	@one_list = split( ",", $one );

	foreach $list_data (@one_list){
	
		#改行コードはスキップ
		if( $list_data =~ /\d+/ ){
			#数字
			print( FILEOUT pack("$ARGV[0]", $list_data) );
		}else{
			#文字の時はエラー
			print( "binary_conv.pl err!!!---$list_data\n文字をバイナリで書き出そうとしています！！\n" );
			close( FILEOUT );
			exit(1);
		}
	}
}

close( FILEOUT );
exit(0);

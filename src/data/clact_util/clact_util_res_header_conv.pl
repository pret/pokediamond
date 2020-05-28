#セルアクターユーティリティシステム
#	リソースマネージャバイナリヘッダー定義ファイル形式に整形する
#	
#	今までのテキスト形式のファイルをバイナリにコンバートできる形式に変化させる
#
#	引数１
#		コンバート対象
#	引数２
#		書き出すファイル名
#
#	戻り値
#		成功	1
#		失敗	0

#引数は２つ必要
if( 2 > @ARGV ){

	print( "err--引数の数が".@ARGV."個です。\n" );
	print( "引数１　コンバート対象\n" );
	print( "引数２　書き出すファイル名\n" );
	exit(1);
}


#	コンバート対象のファイル形式
#
#		リソースタイプ,　アーカイブフラグ,												<-アーカイブファイルフラグがある
#		アーカイブidx,データidx,圧縮フラグ,管理ID,vramタイプ,パレット読み込み本数,		<-この要素数がリソースタイプによって違う
#		アーカイブidx,データidx,圧縮フラグ,管理ID,vramタイプ,パレット読み込み本数,		<-この要素数がリソースタイプによって違う
#	<終了コード>e,e,e,e,e,e,															<-個々の個数が違う

#	セルアクターユーティリティシステム
#			リソースマネージャバイナリヘッダー定義ファイル形式
#例）
#*		リソースタイプ,																	<-アーカイブファイルフラグを廃止
#*		アーカイブidx,データidx,圧縮フラグ,管理ID,vramタイプ,パレット読み込み本数,		<-要素数を固定		6個
#*		アーカイブidx,データidx,圧縮フラグ,管理ID,vramタイプ,パレット読み込み本数,		<-要素数を固定		6個
#*	<終了コード>e,e,e,e,e,e,															<-個数を固定		6個

#読み込みファイルオープン
#
open( FILEIN, $ARGV[0] );
@in_file = <FILEIN>;

if( @in_file == 0 ){
	print( "$ARGV[0]を開けません\n" );
	exit(1);
}

close( FILEIN );

#書き込みファイルオープン
#
open( FILEOUT, ">$ARGV[1]" );

#データを整形しながら書き出す
$res_type_flag = 1;
foreach $one (@in_file){

	#コメント部分を破棄
	$one =~ s/,[^,]*\r*\n/,\n/;
	
	
	#タブ　スペースを排除
	$one =~ s/\s//g;
	$one =~ s/\t//g;

	#ENUM_FILEのある行はそのまま書き出す
	if( $one =~ /ENUM_FILE/ ){
		print( FILEOUT $one);
	}else{
		#リソースタイプのとき
		if( $res_type_flag ){

			#先頭から,までを書き出す
			$one =~ /^([^,]+,)/;

			print(FILEOUT $1);
			$res_type_flag = 0;
		}else{
			
			#各データのとき
			#6つのデータに固定
			@one_list = split( ",", $one );
			$data_num = 0;
			foreach $list_data ( @one_list ){
				#\r\nがないかチェック
				if( !($list_data =~ /\n/) ){
					
					if( $data_num < 6 ){

						print( FILEOUT "$list_data," );
						$data_num ++;
					}
				}
			}

			#6より小さいときは６になるまでダミーデータを書き出す
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

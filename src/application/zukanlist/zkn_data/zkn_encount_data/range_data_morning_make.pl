##-----------------------------------------------------------------------------
#
#		
#			図鑑データコンバータ
#
#
##-----------------------------------------------------------------------------

#------------------------------------------------------------------------------
#
#	定数定義
#
#------------------------------------------------------------------------------
$DEF_FLD_GRID_SIZE_X = 30;
$DEF_FLD_GRID_SIZE_Y = 30;
$DEF_FLD_AREA_DATA_ARRY_OUTSIZE	= 32;



#グローバル変数定義
$CONV_FILE_NAME	= undef;

#------------------------------------------------------------------------------
#
#	定数データ
#
#------------------------------------------------------------------------------
$ZONE_ID[ 0 ] = undef;		#ゾーンID
$MONS_ID[ 0 ] = undef;		#モンスターNO

#------------------------------------------------------------------------------
#
#			ファイルデータ
#
#------------------------------------------------------------------------------
$DAN_FILE[ 0 ] = undef;		#ダンジョンデータファイル
$FLD_FILE[ 0 ] = undef;		#フィールドデータファイル
$ENC_FILE[ 0 ] = undef;		#エンカウントデータファイル

#------------------------------------------------------------------------------
#
#			分布データ
#
#			朝昼晩
#	(,,,区切りでデータを入れる)
#------------------------------------------------------------------------------
$RANGE_DAN_MO[ 0 ] = undef;	#最大数はモンスター数			青表示
$RANGE_DAN_NU[ 0 ] = undef;	#最大数はモンスター数		
$RANGE_DAN_NI[ 0 ] = undef;	#最大数はモンスター数		
$RANGE_FLD_MO[ 0 ] = undef;	#最大数はモンスター数
$RANGE_FLD_NU[ 0 ] = undef;	#最大数はモンスター数
$RANGE_FLD_NI[ 0 ] = undef;	#最大数はモンスター数
$RANGE_DAN_SPECIAL[ 0 ] = undef;	#最大数はモンスター数	赤表示
$RANGE_FLD_SPECIAL[ 0 ] = undef;	#最大数はモンスター数

#------------------------------------------------------------------------------
#
#			ダンジョンデータ
#			最大数はダンジョン分布ID数
#------------------------------------------------------------------------------
$DAN_ID[ 0 ] = undef;				#ダンジョン分布ID（define名）
$DAN_ZONEID[ 0 ] = undef;			#対応するゾーンID（define名）
$DAN_GRID_X[ 0 ] = undef;			#グリッド座標			
$DAN_GRID_Y[ 0 ] = undef;			#グリッド座標
$DAN_TOKUSYUOAM[ 0 ] = undef;		#特殊OAMを使用するか

@DAN_TOKUSYUOAM_ZONEID = ( "ZONE_ID_D05" );	#特殊OAMのゾーンID


#------------------------------------------------------------------------------
#
#			隠しマップごとの　分布データ
#			
#------------------------------------------------------------------------------
@HIDEMAP_ZONEID = ( "ZONEID_D15", "ZONEID_D18", "ZONEID_D30", "ZONEID_L04" );	#隠しマップ

#------------------------------------------------------------------------------
#
#			フィールドデータ
#			最大数はフィールド分布ID数
#------------------------------------------------------------------------------
$FLD_ID[ 0 ] = undef;				#フィールド分布ID（define名）
$FLD_ZONEID[ 0 ] = undef;			#対応するゾーンID（define名）
$FLD_GRID_X[ 0 ] = undef;			#左上グリッド座標
$FLD_GRID_Y[ 0 ] = undef;			#左上グリッド座標
$FLD_SIZE_X[ 0 ] = undef;			#マップグラサイズｘ
$FLD_SIZE_Y[ 0 ] = undef;			#マップグラサイズｙ
$FLD_AREA_ARRY[ 0 ] = undef;		#マップグラデータ	上のx*yサイズの配列 データを,で区切って入れる


#------------------------------------------------------------------------------
#
#		メインルーチン			
#
#------------------------------------------------------------------------------
#第1引数にコンバート対象
$CONV_FILE_NAME = $ARGV[0];


#CSVファイルの作成
print( "CSVファイルの作成\n" );
&csv_file_make();

#ファイル読み込み
print( "ファイル読み込み\n" );
&file_load();

#ゾーンID取得
print( "ゾーンID取得\n" );
&zone_id_get();

#モンスターID取得
print( "モンスターID取得\n" );
&mons_no_get();

#デバックデータ出力
#&debug_array_print( "ゾーンデータ", \@ZONE_ID );
#&debug_array_print( "モンスターデータ", \@MONS_ID );
#&debug_array_print( "ダンジョンファイルデータ", \@DAN_FILE );
#&debug_array_print( "フィールドデータ", \@FLD_FILE );
#&debug_array_print( "エンカウントデータ", \@ENC_FILE );


#エンカウントデータから分布IDとモンスターNO->分布ID列を作成
print( "エンカウントデータから分布IDとモンスターNO->分布ID列を作成\n" );
&enc_data_make();
#&debug_array_print( "ダンジョン分布ID", \@DAN_ID );
#&debug_array_print( "フィールド分布ID", \@FLD_ID );
#&debug_array_print( "ダンジョン分布対応ID", \@DAN_ZONEID );
#&debug_array_print( "フィールド分布対応ID", \@FLD_ZONEID );
#&debug_array_print( "ダンジョンあさ", \@RANGE_DAN_MO );
#&debug_array_print( "ダンジョンひる", \@RANGE_DAN_NU );
#&debug_array_print( "ダンジョンよる", \@RANGE_DAN_NI );
#&debug_array_print( "ダンジョン特殊", \@RANGE_DAN_SPECIAL );
#&debug_array_print( "フィールドあさ", \@RANGE_FLD_MO );
#&debug_array_print( "フィールドひる", \@RANGE_FLD_NU );
#&debug_array_print( "フィールドよる", \@RANGE_FLD_NI );
#&debug_array_print( "フィールド特殊", \@RANGE_FLD_SPECIAL );
#&debug_array_print( "ダンジョン特殊OAM", \@DAN_TOKUSYUOAM );

#情報を書き出す
#
#ポケモン分布逆引きデータ書き出し
print( "ポケモン分布逆引きデータ書き出し開始\n" );
&make_pokerangedata();
print( "ポケモン分布逆引きデータ書き出し完了\n" );

exit(0);


#------------------------------------------------------------------------------
#
#			フィールドデータ
#			CSV形式ファイル作成
#------------------------------------------------------------------------------
sub csv_file_make{
	#フィールドグラフィックデータ
	system( "ExcelSeetConv.exe -o fld_data.txt -n field_zone -s csv map_matrix.xls" );

	#ダンジョン描画位置データ
	system( "ExcelSeetConv.exe -o dan_data.txt -s csv poke_danzyon.xls" );
}

#------------------------------------------------------------------------------
#
#			ファイルデータ読み込み
#
#------------------------------------------------------------------------------
sub file_load{
	#フィールド
	open( FILEIN, "fld_data.txt" );
	@FLD_FILE = <FILEIN>;
	close( FILEIN );
	
	#ダンジョン
	open( FILEIN, "dan_data.txt" );
	@DAN_FILE = <FILEIN>;
	close( FILEIN );
	
	#エンカウント
	open( FILEIN, $CONV_FILE_NAME );
	@ENC_FILE = split( "\r",<FILEIN> );
#	@ENC_FILE = <FILEIN>;
	close( FILEIN );
}


#------------------------------------------------------------------------------
#
#			配列と値を得て　その値のある要素数を返す	
#
#			-1なし
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
#			ゾーンIDデータ取得	
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
#			ゾーンID->ゾーンナンバーコンバート	
#	param	zone_id	ゾーンID名
#	return	ゾーンIDのナンバー　-1=none
#
#------------------------------------------------------------------------------
sub zone_id_num_get{
	my( $zone_id ) =  @_;

	return &arry_no_num_get( \@ZONE_ID, $zone_id );
}

#------------------------------------------------------------------------------
#
#			文字列->ゾーンIDコンバート	
#
#		param	ゾーンIDにしたい文字列
#		return	ゾーンID名
#
#------------------------------------------------------------------------------
sub zone_id_make{
	my( $zone_name ) = @_;

	#大文字にする
	$zone_name = uc( $zone_name );
	$zone_name = "ZONE_ID_$zone_name";

	return $zone_name;
}

#------------------------------------------------------------------------------
#
#			モンスターナンバー取得	
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
#			モンスターNOID->モンスターナンバーコンバート	
#	param	mons_id	モンスターナンバー名
#	return	モンスターナンバー　-1=none
#
#------------------------------------------------------------------------------
sub monsno_num_get{
	my( $mons_id ) =  @_;

	return &arry_no_num_get( \@MONS_ID, $mons_id );
}

#------------------------------------------------------------------------------
#
#			文字列モンスターナンバーIDコンバート	
#
#		param	モンスター名
#		retrun	モンスターID名
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
#			ダンジョン分布ID名->ダンジョン分布ID
#	param	range_dan		ダンジョン分布ID名
#	return	ダンジョン分布IDナンバー		none=-1
#
#------------------------------------------------------------------------------
sub dan_range_num_get{
	my( $range_dan ) =  @_;
	return &arry_no_num_get( \@DAN_ID, $range_dan );
}

#------------------------------------------------------------------------------
#
#			フィールド分布ID名->フィールド分布ID
#	param	fld_dan		フィールド分布ID名
#	return	フィールド分布IDナンバー		none=-1
#
#------------------------------------------------------------------------------
sub fld_range_num_get{
	my( $range_fld ) =  @_;
	return &arry_no_num_get( \@FLD_ID, $range_fld );
}



#------------------------------------------------------------------------------
#
#			ポケモンエンカウントデータ読み込み
#
#------------------------------------------------------------------------------
sub enc_data_make{
	my( $enc_localfile );
	
	#全て要素数はエンカウントデータ要素数
	#mons~系は,区切りでデータを作成
	my( $zone_id );	
	my( $encmons_normal, $encmons_morning, $encmons_night );	#通常
	my( $encmons_special );	#特殊
	my( $work, $count );				#作業領域

	foreach $one ( @ENC_FILE ){
		$one =~ s/""/"dummy"/g;	#""をダミーに変更変更
		$one =~ s/"//g;	#"をカットに変更
#		$one =~ s/\r/,\n/g;	#改行コードを,に変更
	}

	#全エンカウントデータ読み込み（個々ではゾーンー＞モンスター配列というデータ）
	$count = 0;
	foreach $one ( @ENC_FILE ){
		@enc_localfile = split( ",", $one );


		print( "ゾーンID".$enc_localfile[ 0 ]."\n" );
		#ゾーンID名
		$zone_id[ $count ] = &zone_id_make( $enc_localfile[ 0 ] );

		#朝用
		#そのゾーンが本当にあるかチェック
		if( &zone_id_num_get($zone_id[ $count ]) != -1 ){
			
			#通常エンカウントデータ
			#の中の通常
			@work = ($enc_localfile[3], $enc_localfile[5], $enc_localfile[7], $enc_localfile[9], $enc_localfile[11], $enc_localfile[13], $enc_localfile[15], $enc_localfile[17], $enc_localfile[19], $enc_localfile[21], $enc_localfile[23], $enc_localfile[25] );
			#水中
			@work = (@work, $enc_localfile[55], $enc_localfile[58], $enc_localfile[61], $enc_localfile[64], $enc_localfile[67] );
			#岩
#			@work = (@work,  $enc_localfile[71], $enc_localfile[74], $enc_localfile[77], $enc_localfile[80], $enc_localfile[83] );
			#つり１
			@work = ( @work, $enc_localfile[87], $enc_localfile[90], $enc_localfile[93], $enc_localfile[96], $enc_localfile[99] );
			#つり２
			@work = ( @work, $enc_localfile[103], $enc_localfile[106], $enc_localfile[109], $enc_localfile[112], $enc_localfile[115] );
			#つり３
			@work = ( @work, $enc_localfile[119], $enc_localfile[122], $enc_localfile[125], $enc_localfile[128], $enc_localfile[131] );
			@work = &mons_name_arry_mons_no_chg(@work);
			$encmons_morning[ $count ] = join( ',', @work );

			$count ++;
		}
	}

	#ゾーンIDからダンジョン分布IDとフィールド分布IDを作成
	print( "ゾーンIDからダンジョン分布IDとフィールド分布IDを作成" );
	&make_range_id( \@zone_id );	#@zone_idのが分布IDに変更される

	#モンスターナンバー->分布ID列データに変更していく
	for( $count=0; $count<@MONS_ID; $count++ ){
		#あさ
		&make_mons_range_data( $count, \@encmons_morning, \@zone_id, \@RANGE_DAN_MO, \@RANGE_FLD_MO );
	}
}

#ワークの中身をモンスターナンバーに変更する
sub mons_name_arry_mons_no_chg{
	my( @mons_name ) = @_;
	my( $i );

	for( $i=0; $i<(@mons_name + 0); $i++ ){
		$mons_name[$i] = &mona_no_id_get( $mons_name[$i], "dummy" );	#ポケモン名->モンスターID

		$mons_name[$i] = &monsno_num_get( $mons_name[$i] );	#モンスターID->モンスターナンバー
	}
	return @mons_name;
}

#モンスターナンバーが含まれたゾーンのリストを作成
#	param	mons_no		モンスターナンバー
#	param	p_encdata	エンカウントデータ
#	param	p_zone_id	分布ID
#	param	p_out_dan	ダンジョンモンスター分布データ書き出し先
#	param	p_out_fld	フィールドモンスター分布データ書き出し先
sub make_mons_range_data{
	my( $mons_no, $p_encdata, $p_zone_id, $p_out_dan, $p_out_fld ) = @_;
	my( $one_enc_data, $enc_count, $enc_zone_id );
	my( $out_dan_l, $out_fld_l, $out_dan_count, $out_fld_count, $out_dan_flg, $out_fld_flg );

	@out_dan_l = undef;
	@out_fld_l = undef;	
	$out_dan_count = 0;
	$out_fld_count = 0;

	for( $enc_count = 0; $enc_count<@$p_encdata; $enc_count++ ){

		#フラグ初期化　同じモンスターナンバーがテーブルにあったら設定
		$out_dan_flg = 0;
		$out_fld_flg = 0;
		$enc_zone_id = 0;

		#,できって配列にする
		@one_enc_data = split( ",", $$p_encdata[ $enc_count ] );
		
		#同じモンスターナンバーかチェック
		foreach $one ( @one_enc_data ){
			if( $one == $mons_no ){

				#その分布IDを取得
				$enc_zone_id = $$p_zone_id[ $enc_count ];
				
				#その分布IDがダンジョンかフィールドかチェック
				if( $enc_zone_id =~ /ZKN_DAN/ ){
					#ダンジョン
					$out_dan_flg = 1;
				}else{
					#フィールド
					$out_fld_flg = 1;
				}
				
			}
		}

		#同じのあったフラグが立ったら設定
		if( $out_dan_flg == 1 ){
			#以前に同じIDが設定されていないかチェック
			if( &arry_no_num_get( \@out_dan_l, $enc_zone_id ) == -1 ){
				$out_dan_l[$out_dan_count] = $enc_zone_id;
				$out_dan_count++;
			}
		}
		if( $out_fld_flg == 1 ){
			#以前に同じIDが設定されていないかチェック
			if( &arry_no_num_get( \@out_fld_l, $enc_zone_id ) == -1 ){
				$out_fld_l[$out_fld_count] = $enc_zone_id;
				$out_fld_count++;
			}
		}
	}

	#最終行にNONEデータ追加
	$out_dan_l[$out_dan_count] = "ZKN_DAN_ID_NONE";
	$out_fld_l[$out_fld_count] = "ZKN_FLD_ID_NONE";	
	

	#作ったリストを,区切りのデータとして書き出す
	$$p_out_dan[ $mons_no ] = join( ",", @out_dan_l );
	$$p_out_fld[ $mons_no ] = join( ",", @out_fld_l );
}


#------------------------------------------------------------------------------
#
#			ゾーンIDからダンジョン分布ID　と　フィールド分布IDを作成	
#
#------------------------------------------------------------------------------
sub make_range_id{
	my( $p_zone_id ) = @_;
	my( $i, $zanid_num, $fldid_num, $tmp_id );

	$zanid_num = 0;
	$fldid_num = 0;

	#0番目はダミーデータにする
	$DAN_ID[ 0 ] = "ZKN_DAN_ID_NONE";
	$DAN_TOKUSYUOAM[ 0 ] = 0;
	$FLD_ID[ 0 ] = "ZKN_FLD_ID_NONE";
	$zanid_num++;
	$fldid_num++;

	for( $i=0; $i<@$p_zone_id; $i++ ){
		#ダンジョンかチェック
		if( $$p_zone_id[ $i ] =~ /ZONE_ID_([A-Z][0-9]*)[R]/ ){

			#今までに一緒のダンジョンIDが無いかチェック
			if( ($tmp_id = &dan_range_num_get( "ZKN_DAN_ID_$1" )) == -1 ){	

				#ダンジョン
				$DAN_ID[ $zanid_num ] = "ZKN_DAN_ID_$1";
				$DAN_ZONEID[ $zanid_num ] = $$p_zone_id[ $i ];
				#特殊OAMかどうか
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
			#フィールド
			$$p_zone_id[ $i ] =~ /ZONE_ID_(.*)/;
			$FLD_ID[ $fldid_num ] = "ZKN_FLD_ID_$1";
			$FLD_ZONEID[ $fldid_num ] = $$p_zone_id[ $i ];

			$$p_zone_id[$i] = $FLD_ID[ $fldid_num ];
			$fldid_num ++;
		}
	}
}

#ダンジョンデータとくしゅOAMかどうか
sub make_dat_data_tokusyuoam{
	my( $zone_id ) = @_;
	my( $i );

	for( $i=0; $i<@DAN_TOKUSYUOAM_ZONEID; $i++ ){
		if( $DAN_TOKUSYUOAM_ZONEID[$i] eq $zone_id ){
			return 1;
		}
	}

	return 0;
}

#------------------------------------------------------------------------------
#
#			ダンジョングリッドデータ読み込み
#
#------------------------------------------------------------------------------
sub load_dan_grid_data{
	my( $dan_id, $dan_gridx, $dan_girdy );
	my( $local_data, $data_count, $i, $j );

	$data_count = 0;
	
	#データ取得
	foreach $one ( @DAN_FILE ){
		if( $one =~ /[DR][0-9]*/ ){	#ダンジョンデータ項目
			@local_data = split( ",", $one );
			$dan_id[ $data_count ] = "ZKN_DAN_ID_".$local_data[1];	#分布ID
#			print( "localダンジョンID $dan_id[ $data_count ]\n" );
			$dan_gridx[ $data_count ] = $local_data[ 3 ];		#グリッドX
			$dan_gridy[ $data_count ] = $local_data[ 4 ];		#グリッドY

			$data_count ++;
		}
	}

	#0はダミーデータ
	$DAN_GRID_X[ 0 ] = 0;
	$DAN_GRID_Y[ 0 ] = 0;
	
	#ダンジョン分布IDの順番にグリッド座標を設定
	for( $i = 1; $i<@DAN_ID; $i++ ){		#0はダミーデータ
		
		#ダンジョン分布IDと一緒の分布IDのものがあるかチェック
		for( $j=0; $j<$data_count; $j++ ){
			
			if( $DAN_ID[ $i ] eq $dan_id[ $j ] ){
				$DAN_GRID_X[ $i ] = $dan_gridx[ $j ];
				$DAN_GRID_Y[ $i ] = $dan_gridy[ $j ];
				last;	
			}
		}

		#無かったらエラーを返す
		if( $j == $data_count ){
			print( "ダンジョングリッド座標には無いゾーンデータがエンカウントデータにあります(".$DAN_ID[ $i ].")\n" );
			exit(1);
		}
	}
}


#------------------------------------------------------------------------------
#
#			フィールド地形データコンバート	
#
#			グリッドは30*30の大きさ
#
#------------------------------------------------------------------------------
sub load_fld_map_data{
	my( $griddata, $split_data, $count, $skip );
	my( $i, $j, $check_word );

	#グリッドデータ読み込み
	$count = 0;
	$skip = 2;
	foreach $one ( @FLD_FILE ){
		@split_data = split( ",", $one );

		#最初の２行スキップ
		if( $skip > 0 ){
			$skip --;
			print( "スキップ　$one\n" );
		}else{

			if( $count < $DEF_FLD_GRID_SIZE_Y ){
				$griddata[ $count ] = $split_data[1].",".$split_data[2].",".$split_data[3].",".$split_data[4].",".$split_data[5].",".$split_data[6].",".$split_data[7].",".$split_data[8].",".$split_data[9].",".$split_data[10].",".$split_data[11].",".$split_data[12].",".$split_data[13].",".$split_data[14].",".$split_data[15].",".$split_data[16].",".$split_data[17].",".$split_data[18].",".$split_data[19].",".$split_data[20].",".$split_data[21].",".$split_data[22].",".$split_data[23].",".$split_data[24].",".$split_data[25].",".$split_data[26].",".$split_data[27].",".$split_data[28].",".$split_data[29].",".$split_data[30].",";
				$count ++;
			}
		}
	}


	#0はダミーデータ
	$FLD_GRID_X[0] = 0;
	$FLD_GRID_Y[0] = 0;
	$FLD_SIZE_X[0] = 1;
	$FLD_SIZE_Y[0] = 1;
	$FLD_AREA_ARRY[0] = 1;
	
	#グリッド座標内からフィールド分布IDに対応するビットの形を抜き出す
	for( $i=1; $i<@FLD_ID; $i++ ){		#0はダミーデータ
		#まず左上グリッドと範囲サイズを取得
		$check_word = $FLD_ID[ $i ];
		$check_word =~ s/ZKN_FLD_ID_//g;
		($FLD_GRID_X[$i], $FLD_GRID_Y[$i], $FLD_SIZE_X[$i], $FLD_SIZE_Y[$i]) = &get_upleft_mat( \@griddata, $check_word );

		#左上グリッドから横高さ分のエリアのビット配列を作成
		$FLD_AREA_ARRY[$i] = &get_grid_arry( \@griddata, $FLD_GRID_X[$i], $FLD_GRID_Y[$i], $FLD_SIZE_X[$i], $FLD_SIZE_Y[$i], $check_word );
	}
}


#------------------------------------------------------------------------------
#
#			グリッドデータから左上グリッドと範囲サイズを取得	
#
#------------------------------------------------------------------------------
sub get_upleft_mat{
	my( $p_griddata, $check_word ) = @_;
	my( $gridx, $gridy, $ulgridy, $ulgridx, $drgridx, $drgridy, $xgirddata );
	my( $ul_hit_flg, $sizex, $sizey, $work );

	#左上にヒットしたかフラグ
	$ul_hit_flg = 0;
	

	#最初にヒットする場所が左上		最後にヒットしたグリッドが右下
	for( $gridy=0; $gridy<@$p_griddata; $gridy++ ){
		@xgriddata = split( ",", $$p_griddata[ $gridy ] );

		#横サーチ
		for( $gridx=0; $gridx<@xgriddata; $gridx++ ){

			#同じIDなら左上か右下グリッド取得
			if( $check_word eq uc( $xgriddata[ $gridx ] ) ){

				if( $ul_hit_flg == 0 ){
					($ulgridx, $ulgridy) = ($gridx, $gridy);	#左上座標取得
					($drgridx, $drgridy) = ($gridx, $gridy);	#右下座標取得
					$ul_hit_flg = 1;
				}else{
					($drgridx, $drgridy) = ($gridx, $gridy);	#右下座標取得
				}
			}
		}
	}

	if( $ul_hit_flg < 1 ){
		print( "エンカウントデータにあるゾーン情報がフィールド地形データにない".$check_word."\n" );
		exit(1);
	}

	$sizey = (1 + $drgridy) - $ulgridy;

	#左がどっちかチェック
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
#			グリッド範囲データ作成	
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

			#チェックワードと一緒のグリッドナンバーは1それ以外は0
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
#			ダンジョン分布ID　フィールド分布ID出力
#
#------------------------------------------------------------------------------
sub make_range_id_header{
	my( $i );
	
	open( FILEOUT, ">zkn_rangeid.h" );



	print(FILEOUT "#ifndef __ZKN_RANGEID_H__\r\n" );
	print(FILEOUT "#define __ZKN_RANGEID_H_\r\n\r\n" );

	print(FILEOUT "/* フィールド分布ID */\r\n" );
	#フィールド分布ID
	for( $i=0; $i<@FLD_ID; $i++ ){

		print( FILEOUT "#define ".$FLD_ID[$i]." (".$i.")\r\n" );
	}
	#最後に最大数を書き出す
	print( FILEOUT "#define ZKN_FLD_ID_MAX (".$i.")\r\n" );

	print(FILEOUT "/* ダンジョン分布ID */\r\n" );
	#ダンジョン分布ID
	for( $i=0; $i<@DAN_ID; $i++ ){

		print( FILEOUT "#define ".$DAN_ID[$i]." (".$i.")\r\n" );
	}
	#最後に最大数を書き出す
	print( FILEOUT "#define ZKN_DAN_ID_MAX (".$i.")\r\n" );

	print(FILEOUT "#endif //__ZKN_RANGEID_H__\r\n" );

	close( FILEOUT );
}

#------------------------------------------------------------------------------
#
#			分布IDとゾーンIDの対応表の書き出し
#
#			分布IDの順にintサイズ分書き出す
#
#------------------------------------------------------------------------------
sub make_rangeid_zoneid_link{
	my( $i, $zoneid_no, $hide );
	
	open( FILEOUT, ">zkn_rangeid_zoneid_link.c" );
	open( DATFILEOUT_DAN, ">zkn_dan_id.rzidlink" );
	binmode( DATFILEOUT_DAN );
	open( DATFILEOUT_FLD, ">zkn_fld_id.rzidlink" );
	binmode( DATFILEOUT_FLD );


	print( FILEOUT "/* フィールド分布IDの対応表 */\n\n" );
	print( FILEOUT "struct const u16 ZKN_FLD_RANGEID_ZONEID[] = {\n" );

	
	#フィールド分布ID
	for( $i=0; $i<@FLD_ID; $i++ ){
		#ゾーンIDのナンバー取得
		$zoneid_no = &zone_id_num_get( $FLD_ZONEID[$i] );

		print( DATFILEOUT_FLD pack("I", $zoneid_no) );
		print( FILEOUT "\t".$zoneid_no.",\n" );
	}
	print( FILEOUT "};\n" );

	print( FILEOUT "/* ダンジョン分布IDの対応表 */ \n\n" );
	print( FILEOUT "struct const u16 ZKN_DAN_RANGEID_ZONEID[] = {\n" );


	#ダンジョン分布ID
	for( $i=0; $i<@DAN_ID; $i++ ){
		#ゾーンIDのナンバー取得
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
#			隠しマップ　ゾーンIDと分布IDの対応表の書き出し
#	
#------------------------------------------------------------------------------
sub make_hidemap_file{
	my( $i, $zoneid, $j, $count );

	$count = 0;
	
	open( FILEOUT, ">zkn_hidemap.dat" );

	#隠しマップ分ループ
	for( $i=0; $i<@HIDEMAP_ZONEID; $i++ ){
		print( FILEOUT "/* $HIDEMAP_ZONEID[$i] のフィールド分布ID */\n" );
		print( FILEOUT "static const u16 ZKN_FLD_$HIDEMAP_ZONEID[$i]_IDTBL[] = {\n" );
		for( $j=0; $j<@FLD_ID; $j++ ){

			if( $FLD_ZONEID[$j] eq $HIDEMAP_ZONEID[$i] ){
				print( FILEOUT "\t".$j.",\n" );
			}
		}
		print( FILEOUT "\t0xffff,\n" );
		print( FILEOUT "};\n" );


		print( FILEOUT "/* $HIDEMAP_ZONEID[$i] のダンジョン分布ID */\n" );
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
#			ポケモン分布データ逆引きデータ書き出し
#
#------------------------------------------------------------------------------
sub make_pokerangedata{
	#ダンジョン朝分布ファイル
	&make_mons_rang_out_file_dan( \@RANGE_DAN_MO, "zkn_dan_range_morning_mons", "モンスターダンジョン朝分布ID\r\n" );

	#フィールド朝分布ファイル
	&make_mons_rang_out_file_fld( \@RANGE_FLD_MO, "zkn_fld_range_morning_mons", "モンスターフィールド朝分布ID\r\n" );
}

#書き出しメイン
#ダンジョン用
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
#フィールド用
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
#			ダンジョングリッドデータ書き出し	
#			GRIDX GRIDY  特殊OAM(0,1) dammy
#			ucahr	uchar uchar			uchar
#
#------------------------------------------------------------------------------
sub make_dan_grid_data{
	my( $i );

	open( OUTFILETXT, ">zkn_dan_griddata.txt" );
	open( OUTFILE, ">zkn_dan_griddata.dangri" );
	binmode( OUTFILE );
	
	print( OUTFILETXT "ダンジョングリッド座標特殊OAMデータ\r\n" );
	#DAN_GRID_XとYは同じ要素数
	for( $i=0; $i<@DAN_GRID_X; $i++ ){
		
		print( OUTFILETXT "ダンジョンID[".$i."] xグリッド[".$DAN_GRID_X[$i]."] ｙグリッド[".$DAN_GRID_Y[$i]."]特殊OAM[".$DAN_TOKUSYUOAM[$i]."]\r\n" );
		
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
#			フィールド地形データ	
#		
#		グリッドX　グリッドY　サイズX　サイズY　配列（[$DEF_FLD_AREA_DATA_ARRY_OUTSIZE]要素固定）
#		uchar		uchar		uchar	uchar	uchar(配列)
#------------------------------------------------------------------------------
sub make_fld_grid_data{
	my($i);

	open(OUTFILE, ">zkn_fld_griddata.fldgri");
	binmode( OUTFILE );

	#フィールドIDとFLD全配列は要素数一緒
	for( $i=0; $i<@FLD_ID; $i++ ){
		&output_fld_fld_data( $i, $FLD_GRID_X[$i], $FLD_GRID_Y[$i], $FLD_SIZE_X[$i], $FLD_SIZE_Y[$i], $FLD_AREA_ARRY[$i], "zkn_fld_griddata", "フィールド地形データ\r\n" );
	}

	close( OUTFILE );
}
#書き出し
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


	print( OUTFILETXT "グリッドｘ [$gridx] " );
	print( OUTFILETXT "グリッドｘ [$gridy] " );
	print( OUTFILETXT "サイズｘ [$sizex] " );
	print( OUTFILETXT "サイズｘ [$sizey]\r\n" );

	print( OUTFILE pack("C", $gridx) );
	print( OUTFILE pack("C", $gridy) );
	print( OUTFILE pack("C", $sizex) );
	print( OUTFILE pack("C", $sizey) );
		
	#配列データ
	@out_data = split( ",",$arry );	
	for( $i=0; $i<$sizey; $i++ ){
		
		for( $j=0; $j<$sizex; $j++ ){
			print( OUTFILETXT $out_data[($i * $sizex) + $j]."," );
			print( OUTFILE pack("C", $out_data[($i * $sizex) + $j]) );
		}
		print( OUTFILETXT "\r\n" );
	}
	#4バイトアライメント
	for( $i = $DEF_FLD_AREA_DATA_ARRY_OUTSIZE - ($sizex*$sizey); $i>0; $i-- ){
		print( OUTFILE pack("C", 0) );
	}
	
	close( OUTFILETXT );

}


#------------------------------------------------------------------------------
#
#			配列データ書き出し	
#
#------------------------------------------------------------------------------
sub debug_array_print{
	my( $comment, $data ) = @_;

	print( "$comment\n" );

	foreach $one ( @$data ){
		print( "$one\n" );
	}
}


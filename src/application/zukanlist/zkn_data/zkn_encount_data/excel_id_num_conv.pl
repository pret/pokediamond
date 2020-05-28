#excel_form_csv.txtとexcel_worldid_csv.txt
#から形IDヘッダと言語IDヘッダを作成
#
#excel_csv.txtの中の該当するID名を数字に変更


#-----------------------------------------------------------------------------
#	グローバルデータ
#-----------------------------------------------------------------------------
@FORM_ID = undef;		#形ID格納先

@FORM_FILE = undef;		#形IDCSV形式ファイル読み込みデータ
@EXCEL_FILE = undef;	#EXCELファイル読み込みデータ


#-----------------------------------------------------------------------------
#	メインループ	
#-----------------------------------------------------------------------------

#ファイル読み込み
&file_load();

#形ID格納
&form_id();

#定数を数字に変更する
&excel_id_num_conv();

#変更後EXCELファイル書き出し
&excel_file_write();

#形IDヘッダー書き出し
&form_header_write();

exit(0);



#-----------------------------------------------------------------------------
#	ファイル読み込み
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
#	形ID切り取り
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
#	EXCEL定数を数字に変更
#-----------------------------------------------------------------------------
sub excel_id_num_conv{
	my( $i, $j );
	
	for( $j = 0; $j < @EXCEL_FILE; $j++ ){
		
		#形
		for( $i=0; $i<@FORM_ID; $i++ ){
			$EXCEL_FILE[$j] =~ s/$FORM_ID[$i]/$i/g;
		}
	}
}


#-----------------------------------------------------------------------------
#	excelファイル書き出し
#-----------------------------------------------------------------------------
sub excel_file_write{
	open( FILEOUT, ">excel_csv.txt" );
	print( FILEOUT @EXCEL_FILE );
	close( FILEOUT );
}

#-----------------------------------------------------------------------------
#	形IDヘッダー書き出し
#-----------------------------------------------------------------------------
sub form_header_write{

	my( $i );
	
	open( FILEOUT, ">zkn_form_id.h" );

	print(FILEOUT "/* 形ID　ヘッダーファイル */\r\n" );
	print(FILEOUT "#ifndef __ZKN_FORM_ID_H__\r\n" );
	print(FILEOUT "#define __ZKN_FORM_ID_H__\r\n" );

	for( $i=0; $i<@FORM_ID; $i++ ){	
		print(FILEOUT "#define ".$FORM_ID[ $i ]."	(".$i.")\r\n" );
	}

	print(FILEOUT "#endif // __ZKN_FORM_ID_H__\r\n" );

	close( FILEOUT );
}

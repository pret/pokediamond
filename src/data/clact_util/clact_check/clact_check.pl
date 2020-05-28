#----------------------------------------------------------------------------
#
#	このパールはpokemon_dpフォルダから呼ばれます。
#
#	arc_tool.datないのenumの値が今のarc_tool.datのnumの値と一緒かチェック
#	
#----------------------------------------------------------------------------
#####################################################################
#	メインルーチン
#####################################################################
%h_LabelTbl_TMP;		#tmp_arc_tool.dat LABELデータハッシュテーブル
%h_LabelTbl_NOW;		#arc_tool.dat LABELデータハッシュテーブル

#今のarc_tool.dat読み込み
open( IN, "../../../../include/system/arc_tool.dat" );
@now_arc = <IN>;
close( IN );
if( @now_arc == 0 ){
	print( "arc_tool.datが開けません\n" );
	exit(1);
}

#保存しておいたarc_tool.dat読みこみ
open( IN, "tmp_arc_tool.dat" );
@tmp_arc = <IN>;
close( IN );
if( @tmp_arc == 0 ){
	print( "tmp_arc_tool.datが開けません\n" );
	exit(0);
}

#commentを破棄
@now_arc = &comment_cut( @now_arc );
@tmp_arc = &comment_cut( @tmp_arc );

#ハッシュテーブルにLABELデータを追加
&add_hash( \@tmp_arc, \%h_LabelTbl_TMP );
&add_hash( \@now_arc, \%h_LabelTbl_NOW );


#h_LabelTbl_TMPないのデータが全てh_LabelTbl_NOWにあるかチェック
#ハッシュの中と同じ文字があったら数字に変える
$key_tnow = 0;	#等しいkey格納用
$num_tnow = 0;	#等しいnum格納用
while( ($key_tmp, $num_tmp) = each(%h_LabelTbl_TMP) ){

	$eq_flg = 0;
	#このキーと同じキーがあるかチェック
	while( ($key_now, $num_now) = each(%h_LabelTbl_NOW) ){
		
		if( $key_tmp eq $key_now ){
			$eq_flg	= 1;
			$key_tnow = $key_now;
			$num_tnow = $num_now;
		}
	}

	#$eq_flgが０の時エラー
	if( $eq_flg == 0 ){
		print("$key_tmp というLABELがありません。\n");
		print("arc_tool.datのアーカイブファイルIDが変更されたため、セルアクターヘッダー内のアーカイブファイルIDと一致しない場合があります。 tomoya takahashi \n" );
		system( "rm ../*.resdat" );
		system( "rm ../*.cldat" );
		exit(1);
	}

	#値が等しいかチェック
	if( $h_LabelTbl_TMP{ $key_tmp } != $h_LabelTbl_NOW{ $key_tmp } ){
		print("$key_tmp=$num_tmp が $key_tnow=$num_tnow になりました。\n");
		print( "セルアクターヘッダー内のアーカイブファイルIDと一致しない場合があります。新規アーカイブファイルの追加はenumの一番下にお願いいたします。ご協力お願いします。 tomoya takahashi \n" );
		system( "rm ../*.resdat" );
		system( "rm ../*.cldat" );
		exit(1);
	}
}

exit(0);

#####################################################################
#	サブルーチン
#####################################################################
#LABEL定義部分を抜き出す
#param		検索文字列テーブルのポインタ
#param		現在のハッシュデータのポインタ
#
#enum{				<=ここを探す
#	LABEL1,			
#	LABEL2 = 5,
#};					<=ここで終わりだとチェックする
sub add_hash {

	my($label_tbl, $label_hash) = @_;
	my($one, $enum_flag, $label_num, $label_check, $label_num_check);
	my($label_tmp, $label_num_tmp);

#	print( "開始\n" );
	
	$enum_flag = 0;
	$label_num = 0;
	$label_tmp = undef;

	foreach $one( @$label_tbl ){

		#enumの定義に入るかチェック
		if( $enum_flag == 0 ){
			
			#enum定義があるかチェック
			if( $one =~ /^[\s\t]*enum/ ){
				$enum_flag = 1;

#				print( "enum発見\n" );
			}
		}
		
		if( $enum_flag == 1 ){
			#{を探す
			if( $one =~ /{/ ){

				$enum_flag = 2;
#				print( "{発見\n" );
			}
		}
		
		if( $enum_flag == 2 ){

			#LABEL定義取得
			$label_check = &get_label( $one );
			if( $label_check ne "def_to_num_err" ){

#				print( "LABEL取得=$label_check\n" );

				#このifのelseで設定した$label_tmpの中身を破棄
				#ここに入ってきたということは、一番したではない。
				$label_tmp = undef;

				#ＬＡＢＥＬ数の定義も入っていないかチェック
				$label_num_check = &get_labelnum( $one );
				if($label_num_check ne "def_to_num_err"){
					$label_num = $label_num_check;
				}
#				print( "LABEL数=$label_num\n" );
			
				#ハッシュに格納
				$$label_hash{ $label_check } = $label_num;
				$label_num ++;	#ＬＡＢＥＬに対応する値加算
				
			}else{
				
				#,がないだけで、LABEL定義っぽい行だったら取っておく
				#次の有効な行が、}ならLABELとして登録する
				if( $one =~ /^[\s\t]*([^\s\t\}\;]+)/ ){
					$label_tmp = $1;			

					#数字定義もあるかチェック
					$label_num_check = &get_labelnum( $one );
					if($label_num_check ne "def_to_num_err"){
						$label_num_tmp = $label_num_check;
					}else{
						$label_num_tmp = $label_num;
					}
				}
			}

			#enum終了チェック
			#};があれば終了
			if( $one =~ /}/ ){
				
				#label_tmpがあるときはそのLABELをハッシュに代入
				if($label_tmp){
					$$label_hash{ $label_tmp } = $label_num_tmp;
				}
				
				#ワーク初期化
				$enum_flag = 0;
				$label_num = 0;
#				print( "}発見\n" );
			}
		}
	}
#	print( "終了\n" );
}

#LABEL定義の取得
#param		LABELが定義されているかもしれない文字列
#retval		LABELの名前
#retval		err = LABELがない
sub get_label{

	my($str) = @_;

	#^	TEST_LABEL	,のTEST_LABELを取得
	#^TEST_LABEL,
	#^ TEST_LABEL = 0,
	if( $str =~ /^[\s\t]*([^\s\t]+)[\s\t]*(\,|\=[\s\t]*\d+[\s\t]*\,)/ ){
		return $1;
	}

	return "def_to_num_err";
}

#LABEL数定義の取得
#param		LABEL数が定義されているかもしれない文字列
#retval		LABELに対応する値
#retval		err = LABEL数なし
sub get_labelnum{

	my($str) = @_;

	#^ TEST_LABEL = 0
	#,は最終行のラベルには無いので、チェックしない
	if( $str =~ /\=[\s\t]*(\d+)/ ){
		return $1;
	}

	return "def_to_num_err";
}

#comment部分を排除します。
sub comment_cut {

	my( @str ) = @_;
	my( $one, $com_flag );
	

	$com_flag = 0;
	foreach $one( @str ){

		if( $com_flag == 1 ){
			#閉じがくるまでの全てを破棄
			if( $one =~ /\*\// ){
				$one =~ s/.*\*\///;
				$com_flag = 0;
			}else{
				$one =~ s/.*//;
			}
		}

		if( $com_flag == 0 ){
			#/**/を破棄
			$one =~ s/\/\*.*?\*\///g;

			#//を消す  前に/*がない
			$one =~ s/(.*)\/\/.*(\r*\n)/$1$2/;

			#/*を破棄
			if( $one =~ s/\/\*.*(\r*\n)/$1/ ){

				$com_flag = 1;		#閉じがないので探す
			}
		}			
	}

	return @str;
}

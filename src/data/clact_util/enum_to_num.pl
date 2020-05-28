#	ファイルに書かれたenumを対応するナンバーに変更する
# 引数１　コンバート対象ファイル
# 引数２　コンバート後ファイル名
# 引数３，４・・・・・
#			ラベルを定義しているファイル（複数可）
#			enumを定義しているファイルは引数１に指定するファイル内に記述することも出来ます。(■)	
#使用例
#perl enum_to_num.pl conv_before.txt conv_after.txt enum_file1.h enum_file2.h
#
#＊注意事項
#10進数にしか対応していません。
#enumにしか対応していません。	defineは無理です
#
#
#■Linkするenumのファイルを定義する方法
#引数１のコンバート対象ファイルの先頭にENUM_FILE=,,,,と参照するファイルパスを記述してください。
#
#例
#ENUM_FILE=include/system/arc_tool.dat,include/system/clact_util_res.h,	<-','必要です。		コメント部
#内容ーーーーーーーー


#####################################################################
#	メインルーチン
#####################################################################
%h_LabelTbl;		#LABELデータハッシュテーブル


#引数は最低３つ必要
if( @ARGV < 3 ){
	&help("引数数が不正です。　引数数".@ARGV);
	exit(1);
}


#LABELデータテーブル作成
for( $i=2; $i<@ARGV; $i++ ){
	open( IN, "$ARGV[$i]" );

	@file = <IN>;
	
	if( @file == 0 ){
		print( "$ARGV[$i]が開けません---0\n" );
		close( IN );
		exit(1);
	}

	#commentを破棄
	@file = &comment_cut( @file );
	close( IN );

#	print( @file );


	#ハッシュテーブルにLABELデータを追加
	&add_hash( \@file, \%h_LabelTbl );
}

#print( "ハッシュデータ表\示\n" );
#while( ($key, $num) = each(%h_LabelTbl) ){
#	print( "LABEL=$key	NUM=$num\n" );
#}


#ファイル読み込みと書き出し先作成
open( FILE_IN, "$ARGV[0]" );
@in_file = <FILE_IN>;
if( @in_file == 0 ){
	print( "$ARGV[0]が開けません---1\n" );
	close( FILE_IN );
	exit(1);
}
close( FILE_IN );
open( FILE_OUT, ">$ARGV[1]" );

#１行目にENUM_FILE定義があるかチェック
if( $in_file[0] =~ s/ENUM_FILE=// ){
	
	#コメント部分破棄
	$in_file[0] =~ s/,[^,]*\r*\n/,\n/;
	#スペース タブを破棄
	$in_file[0] =~ s/\s//g;
	$in_file[0] =~ s/\t//g;

	#*,までを切り取る
	while( $in_file[0] =~ s/([^,]+),// ){
		open( IN, "$1" );
		@file = <IN>;
		close( IN );
		if( @file == 0 ){
			print( "$1が開けません---0\n" );
			close( FILE_IN );
			close( FILE_OUT );
			exit(1);
		}
		#commentを破棄
		@file = &comment_cut( @file );

		#ハッシュテーブルにLABELデータを追加
		&add_hash( \@file, \%h_LabelTbl );
	}

	#１行目を無くす
	@in_file = @in_file[1..(@in_file-1)];
}

foreach $one_data ( @in_file ){
	
	#ハッシュの中と同じ文字があったら数字に変える
	while( ($key, $num) = each(%h_LabelTbl) ){

		#このキーと同じ文字列があるかチェック
		while( $one_data =~ s/(,|^)[\s\t]*$key[\s\t]*(,)/$1$num$2/ ){
#			print( "cheng $key to $num\n" );
		};
	}

	print( FILE_OUT $one_data );
#	print( $one_data );
}

close( FILE_OUT );

exit(0);

#####################################################################
#	サブルーチン
#####################################################################
#ヘルプ表示関数
#param		表示文字列
#return		none
sub help {
	my($str) = @_;
	print( "err $str\n" );
	print( "引数１　コンバート対象ファイルパス\n" );
	print( "引数２　コンバート後ファイルパス\n" );
	print( "引数３，４，５、、、、、ラベル定義ファイルパス（何個でも可）\n" );
	return 1;
}

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

package  make_gmm;

#===============================================================================
# gmm作成
#===============================================================================

use utf8;

%LangNameTbl = (
	'jp',	'日本語',
	'us',	'英語',
	'fr',	'フランス語',
	'ge',	'ドイツ語',
	'it',	'イタリア語',
	'sp',	'スペイン語',
);


my @IDList = ();
my @WidthList = ();
my @StrList = ();
my @FontList = ();
my $LangName = "";

my @TemplateGmm = ();
my $TemplateStartLine = 0;
my $TemplateEndLine = 0;


#----------------------------------------------
# モジュール初期化
# input  0:テンプレートファイルパス
#        1:言語コード
#----------------------------------------------
sub init {
	my $template = shift;
	my $lang = shift;

	@IDList = ();
	@WidthList = ();
	@StrList = ();
	@FontList = ();

	$LangName = $LangNameTbl{$lang};
	utf8::encode($LangName);

	if( open(TEMPLATE, "<$template") )
	{
		@TemplateGmm = <TEMPLATE>;
		for($TemplateStartLine=0; $TemplateStartLine<@TemplateGmm; $TemplateStartLine++)
		{
			if( $TemplateGmm[$TemplateStartLine] =~ '^<body' ){ last; }
		}
		for($TemplateEndLine=$TemplateStartLine+1; $TemplateEndLine<@TemplateGmm; $TemplateEndLine++)
		{
			if( $TemplateGmm[$TemplateEndLine] =~ '</lock>' ){ last; }
		}

#		print "start=$TemplateStartLine, end=$TemplateEndLine\n";

		close(TEMPLATE);
		return 1;
	}

	return 0;
}


#----------------------------------------------
# 文字列追加
# input  0:文字列ID
#        1:文字列
#        2:ウィンドウ幅
#        3:フォント
#----------------------------------------------
sub add {
	my $id = shift;
	my $str = shift;
	my $width = shift;
	my $font = shift;

	utf8::encode($str);

	push @IDList, $id;
	push @WidthList, $width;
	push @StrList, $str;
	push @FontList, $font;
}

#----------------------------------------------
# gmm出力
# input  0:出力ファイルパス
#----------------------------------------------
sub output {
	my $filename = shift;
	my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);

	$year += 1900;
	$mon += 1;


	if( open( OUTPUT_GMM, ">$filename") )
	{
		print OUTPUT_GMM "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
		print OUTPUT_GMM "<?xml-stylesheet type=\"text/xsl\" href=\"\" ?>\n";
		print OUTPUT_GMM "\n";
		print OUTPUT_GMM "<gmml version=\"4.5\">\n";
		print OUTPUT_GMM "\n";
		print OUTPUT_GMM "<head>\n";
		print OUTPUT_GMM "\t<create user=\"$ENV{'USERNAME'}\" host=\"$ENV{'COMPUTERNAME'}\"";
		printf OUTPUT_GMM " date=\"%d-%02d-%02dT%d:%02d:%02d\"/>\n", $year, $mon, $mday, $hour, $min, $seq;
		print OUTPUT_GMM  "\t<generator name=\"MessageEditor\" version=\"4.9.2.5\"/>\n";
		print OUTPUT_GMM "</head>\n\n";

		for($i=$TemplateStartLine; $i<=$TemplateEndLine; $i++)
		{
			print OUTPUT_GMM $TemplateGmm[$i];
			
		}

		print OUTPUT_GMM "\n\n";

		for($i=0; $i<@IDList; $i++)
		{
			print OUTPUT_GMM "\t<row id=\"$IDList[$i]\">\n";
			print OUTPUT_GMM "\t\t<language name=\"$LangName\" ";
			if( $FontList[$i] ne "" )
			{
				print OUTPUT_GMM "font=\" $FontList[$i]\" ";
			}
			print OUTPUT_GMM "width=\"$WidthList[$i]\">$StrList[$i]</language>\n";
			print OUTPUT_GMM "\t</row>\n\n";
		}



		print OUTPUT_GMM "\t<flowchart-group-list>\n";
		print OUTPUT_GMM "\t\t<flowchart-group japanese=\"root\" english=\"root\" group-id=\"0\" parent-id=\"-1\"/>\n";
		print OUTPUT_GMM "\t</flowchart-group-list>\n";
		print OUTPUT_GMM "</body>\n";
		print OUTPUT_GMM "\n";
		print OUTPUT_GMM "</gmml>\n";


		close(OUTPUT_GMM);
		return 1;
	}
	return 0;
}




return 1;

##########################################################
#	メッセージデータコンバート
##########################################################

SRC_TXT		= stafflist.txt
DST_DAT		= ..\..\src\demo\ending\stafflist.dat
DST_GMM		= ..\message\src\stafflist.gmm
LANG_FLAG	= jp


##########################################################
#	動作部分
##########################################################
$(DST_DAT): $(SRC_TXT)
	perl stafflist_convert.pl $(SRC_TXT) $(DST_DAT) $(DST_GMM)

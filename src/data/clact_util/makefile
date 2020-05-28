##########################################################
#	リソースマネージャ用ファイル
#	
##########################################################
RESFILES   := $(wildcard *.restxt)
			 
##########################################################
#	セルアクター用ファイル
#	
##########################################################
CLACTFILES  := $(wildcard *.cltxt)


##########################################################
#	動作部分
##########################################################
.SUFFIXES: .resdat .restxt .cldat .cltxt


#全部アーカイブさせる
clact.narc: $(RESFILES:.restxt=.resdat) $(CLACTFILES:.cltxt=.cldat)
	nnsarc -c -l -n -i clact_header.narc *.resdat *.cldat
	cp *.resdat ../
	cp *.cldat ../
	cp ../../../include/system/arc_tool.dat clact_check/tmp_arc_tool.dat


#サフィックスルール
.restxt.resdat:
	perl res_header_conv.pl $< $@ \
	../../../include/system/arc_tool.dat \
	clact_util_rom.enumfile

.cltxt.cldat:
	perl clact_conv.pl $< $@ \
	../../../include/system/arc_tool.dat \
	clact_util_rom.enumfile


##########################################################
#	clean 指定されたとき
#	
##########################################################
clean:
	rm *.resdat
	rm *.cldat
	rm *.narc
	rm *.naix

###############################################################
#
#		マップアトリビュート表コンバート用Makefile
#
#		sousuke tamada GAME FREAK inc.
#
#		2005.12.16	作成
#
#		マップアトリビュート管理表からアトリビュートの定義を
#		生成する。
#
###############################################################

DATAFILE	=	map_attr.xls
RESOURCE	=	$(DATAFILE:.xls=.txt)
TARGET		=	$(DATAFILE:.xls=.h)

#EXCEL2TAB	=	../../../convert/exceltool/exceltabconv
EXCEL2CSV	=	../../../convert/exceltool/excelcommaconv

$(TARGET):	$(DATAFILE)
	$(EXCEL2CSV)	$(DATAFILE)
	$(MAKE) convert

convert:
	ruby map_attr.rb $(RESOURCE) $(TARGET) $(TARGET:.h=.dat)

clean:
	-rm $(TARGET) $(RESOURCE)

new:
	$(MAKE) clean
	$(MAKE)

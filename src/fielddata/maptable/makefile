#
#	マップ管理表コンバート用Makefile
#
#	2005.10.25	tamada
#
#

TARGET	=	maptable.dat
DATAFILE	= zonetable.xls
OUTPUT	=	$(TARGET) zone_id.h eventlist.txt

EXCEL2TAB	=	../../../convert/exceltool/exceltabconv

$(TARGET):	$(DATAFILE)
	$(EXCEL2TAB)	$(DATAFILE)
	$(MAKE) convert

#..\..\..\convert\exceltool\exceltabconv zonetable.xls
#ruby maptable.rb zonetable.txt

convert:
	ruby maptable.rb $(DATAFILE:.xls=.txt)

clean:
	-rm $(OUTPUT)

diff:
	-cp zone_id.h zone_id.h.old
	-cp maptable.dat maptable.dat.old
	-cp eventlist.txt eventlist.txt.old
	$(MAKE) convert
	-diff zone_id.h zone_id.h.old > diff.txt
	-diff maptable.dat maptable.dat.old >> diff.txt
	-diff eventlist.txt eventlist.txt.old >> diff.txt
	cat diff.txt
	-rm $(addsuffix .old, $(OUTPUT))


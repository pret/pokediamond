

DATAFILE	=	warpdata.xls
MIDFILE		=	$(DATAFILE:.xls=.txt)
TARGET		=	warpdata.c
EXCEL2TAB	=	../../../convert/exceltool/exceltabconv

do-build:	$(TARGET)

$(TARGET):	$(MIDFILE)
	$(MAKE) convert
	
$(MIDFILE):	$(DATAFILE)
	$(EXCEL2TAB)	$(DATAFILE)

convert:
	ruby warpdata.rb $(MIDFILE)

clean:
		-rm 	$(TARGET) $(TARGET:.c=.h)	$(MIDFILE)

diff:
	-cp $(TARGET) $(TARGET).old
	-cp $(TARGET:.c=.h) $(TARGET:.c=.h).old
	$(MAKE) clean
	$(MAKE)
	-diff $(TARGET) $(TARGET).old > diff.txt
	-diff $(TARGET:.c=.h) $(TARGET:.c=.h).old >> diff.txt
	cat diff.txt


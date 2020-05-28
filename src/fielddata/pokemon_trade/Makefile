#######################################
##
##	ゲーム内ポケモン交換
##
#######################################
SUBDIRS		=


#コピーしてくるディレクトリ
MONSNO_H_DIR		= ..\\..\\..\\include\\poketool\\
ITEMSYM_H_DIR		= ..\\..\\..\\include\\itemtool\\
TOKUSYU_H_DIR		= ..\\..\\..\\include\\battle\\
PM_VER_H_DIR		= ..\\..\\..\\include\\

#コピー先
CPY_DIR	= .

#依存するファイル
MAKE_FILE	= fld_trade.xls \
			  monsno.h \
			  itemsym.h \
			  tokusyu_def.h \
			  pm_version.h

#ターゲットファイル
MAKE_TARGET = fld_trade_00.dat
DAT_FILE	= $(wildcard *.dat)


include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= $(wildcard *.narc) \
			  $(wildcard *.dat) \
			  $(wildcard *.txt)
			  

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules


do-build:file_cp $(MAKE_TARGET) fld_trade.narc

#ファイルコピー
file_cp:
	xcopy /d /y $(MONSNO_H_DIR)monsno.h $(CPY_DIR)
	xcopy /d /y $(ITEMSYM_H_DIR)itemsym.h $(CPY_DIR)
	xcopy /d /y $(TOKUSYU_H_DIR)tokusyu_def.h $(CPY_DIR)
	xcopy /d /y $(PM_VER_H_DIR)pm_version.h $(CPY_DIR)

#データコンバート
$(MAKE_TARGET):$(MAKE_FILE)
	perl conv.pl
	
#アーカイブ
fld_trade.narc:$(DAT_FILE) $(MAKE_TARGET)
	#アーカイブ
	nnsarc -c -i -n fld_trade.narc -S fld_trade_list.lst

#! make -f
#----------------------------------------------------------------------------
#	@file	makefile
#	@brief	エリア毎の動作モデルリストアーカイブ生成用makefile
#	@date	2005.11.24
#	@author	tamada GAME FREAK inc.
#
#----------------------------------------------------------------------------

DP_ROOT	=	../../..


#----------------------------------------------------------------------------
#	アセンブラ→バイナリ生成に必要な定義ファイルをインクルード
#----------------------------------------------------------------------------
#include $(DP_ROOT)/commondefs.GF
include $(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include $(NITROSYSTEM_ROOT)/build/buildtools/commondefs
include $(DP_ROOT)/modulerules.GF
#include $(NITROSYSTEM_ROOT)/build/buildtools/modulerules


#----------------------------------------------------------------------------
#
#----------------------------------------------------------------------------
RSCFILE	=	movemodel_list.xls
RSCTXT	=	$(RSCFILE:.xls=.txt)
ARCNAME	=	move_model_list.narc
ARCLIST	=	arclist.txt
ARCHEAD	=	mmlist_def.h
ASMFILES	= $(wildcard mmlid_*.s)


#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= *.s *.bin $(RSCTXT) $(ARCNAME)

#アセンブラファイルでインクルードするヘッダを探すパス指定
IPATH	=	-I$(DP_ROOT)/src/field/

#ツール定義
ELF2BIN	=	$(DP_ROOT)/convert/eventdata/elf2bin.exe
XLS2TXT	=	$(DP_ROOT)/convert/exceltool/exceltabconv
TXT2ASM	=	ruby mmodel_file.rb



do-build:  $(ARCNAME)

#----------------------------------------------------------------------------
#	*.s --> *.binへのルール定義
#----------------------------------------------------------------------------
%.bin: %.s
	@echo $<
	@cp $< temp.s
	@$(MWAS) $(IPATH) temp.s -o $*.o
	@$(MWLD) -dis -o $*.elf $*.o
	@$(ELF2BIN) $*.elf > /dev/null
	@rm $*.o
	@rm $*.elf
	@rm temp.s


#----------------------------------------------------------------------------
#	アーカイブ生成
#----------------------------------------------------------------------------
$(ARCNAME): $(ARCLIST) $(ASMFILE:.s=.bin)
	nnsarc -i -c -l -n $(ARCNAME) -S $(ARCLIST) > arc_result.txt
	@echo エリア毎動作モデルリストのアーカイブを生成しました。

#----------------------------------------------------------------------------
#	エリア毎のアセンブラファイル生成
#----------------------------------------------------------------------------


$(RSCTXT):	$(RSCFILE)
	@echo 動作モデル管理表変換処理･･･
	@$(XLS2TXT) $(RSCFILE)				#タブ区切りテキストに変換

ASMFILE:	$(ASMFILES:.s=.bin)

$(ARCLIST):	 $(RSCTXT)
	@echo エリア別データ生成処理･･･
	@$(TXT2ASM)  $(RSCTXT) $(ARCLIST) $(ARCHEAD)
	@echo 個別アセンブラファイルコンパイル･･･
	@$(MAKE) ASMFILE


test:
	echo $(wildcard mmlid_*.s)
	echo $(ASMFILES:.s=.bin)




#! make -f
#----------------------------------------------------------------------------
# Project:  技エフェクト
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------
DP_ROOT	=	../../..

SUBDIRS		=

RES_DATA_DIR	= .\\contest_data\\

include	sourcefile.lst

#----------------------------------------------------------------------------
#	Ｃソース→バイナリ変換を可能にするための設定
#----------------------------------------------------------------------------
include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#共通変数定義
include $(DP_ROOT)/commondefs.GF

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

%.bin: %.c
	echo "#include \"$(NITROSDK_ROOT)/include/nitro/types.h\"" > temp.c
	cat contype_dummy.h $< >> temp.c
	$(CC) $(CCFLAGS) $(INCLUDES)  -c temp.c -MD -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	$(ELF2BIN) $*.elf
	-rm $*.o temp.c temp.d
	-rm $*.elf


#--------------------------------------------------------------
#	
#--------------------------------------------------------------
LDIRT_CLEAN	= contest_data.narc $(CONVSRCS:.c=.bin)

LINCLUDES		= $(NITROSDK_ROOT)/include
LINCLUDES		+= $(DP_ROOT)/src/field

LINCLUDES	+= $(dir $<)

#----------------------------------------------------------------------------


#--------------------------------------------------------------
#	
#--------------------------------------------------------------
#ツール定義
ELF2BIN	=	$(DP_ROOT)/convert/eventdata/celf2bin.exe
LISTMK		= $(DP_ROOT)/convert/eventdata/listmk.exe



#-------------------------------
#	実行順
#		リソースコピー
#		リソースアーカイブ
#		技エフェクトアーカイブ
#-------------------------------
do-build: contest_data.narc


#----------- アーカイブする -----------
contest_data.narc: $(RES_DATA_DIR:\\=/)*.bin contest_data.lst
	$(MAKE) mklst				#一覧を作成して
	$(MAKE) makebin				#Ｃソース→バイナリ変換して
	$(MAKE) makearc				#アーカイブにまとめる


#対象ソース一覧作成
mklst:
	ls -1 *.c > temp
	$(LISTMK) temp sourcefile.lst CONVSRCS
	rm temp

#Ｃソース→バイナリ変換
makebin: $(CONVSRCS:.c=.bin)

#アーカイブ作成
makearc:
	nnsarc -c -l -n -i contest_data.narc -S contest_data.lst
#	nnsarc -i -c -l -n $(TARGET_ARC) *.bin > arc_result.txt

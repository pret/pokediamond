#! make -f
#----------------------------------------------------------------------------
# Project:  Cソース->バイナリー
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------
DP_ROOT	=	../../..

SUBDIRS		=
TARGET_ARC		=	enc_data.narc
D_TARGET_ARC	=	d_enc_data.narc
P_TARGET_ARC	=	p_enc_data.narc
D_ENCOUNT_DATA =	PMDencount.csv
P_ENCOUNT_DATA =	PMPencount.csv

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
	cat dummy.h $< >> temp.c
	$(CC) $(CCFLAGS) $(INCLUDES)  -c temp.c -MD -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	$(ELF2BIN) $*.elf
	-rm $*.o temp.c temp.d
	-rm $*.elf


#----------------------------------------------------------------------------
#
#----------------------------------------------------------------------------
#Makeで生成される*.binはmake cleanの削除対象にする
LDIRT_CLEAN	= $(CONVSRCS:.c=.bin) $(CONVSRCS) $(D_TARGET_ARC) $(P_TARGET_ARC) $(TARGET_ARC) $(TARGET_ARC:.narc=.naix)

LINCLUDES		= $(NITROSDK_ROOT)/include
LINCLUDES		+= $(DP_ROOT)/src/field

LINCLUDES	+= $(dir $<)

#----------------------------------------------------------------------------
#	ツールへのパス指定
#----------------------------------------------------------------------------
LISTMK		= $(DP_ROOT)/convert/eventdata/listmk.exe
ELF2BIN		= $(DP_ROOT)/convert/eventdata/celf2bin.exe
CONVERTER	= $(DP_ROOT)/convert/encountdata/EncountConverter


#----------------------------------------------------------------------------
#
#	ルール定義
#
#----------------------------------------------------------------------------
do-build: $(D_TARGET_ARC) $(P_TARGET_ARC)

$(D_TARGET_ARC): $(D_ENCOUNT_DATA)
	$(MAKE) d_convert				#ダイア コンバートして
	$(MAKE) mklst				#一覧を作成して
	$(MAKE) makebin				#Ｃソース→バイナリ変換して
	$(MAKE) d_makearc				#ダイア アーカイブにまとめる

$(P_TARGET_ARC): $(P_ENCOUNT_DATA)
	$(MAKE) p_convert				#パール コンバートして
	$(MAKE) mklst				#一覧を作成して
	$(MAKE) makebin				#Ｃソース→バイナリ変換して
	$(MAKE) p_makearc				#パール アーカイブにまとめる

#コンバータ呼び出し
d_convert:
	$(CONVERTER) $(D_ENCOUNT_DATA)

#コンバータ呼び出し
p_convert:
	$(CONVERTER) $(P_ENCOUNT_DATA)
	
#対象ソース一覧作成
mklst:
	ls -1 *enc.c > temp
	$(LISTMK) temp sourcefile.lst CONVSRCS
	rm temp

#Ｃソース→バイナリ変換
makebin: $(CONVSRCS:.c=.bin)

#アーカイブ作成
d_makearc:
	nnsarc -i -c -l -n $(TARGET_ARC) *.bin > d_arc_result.txt
	d_copy.bat
	
#アーカイブ作成
p_makearc:
	nnsarc -i -c -l -n $(TARGET_ARC) *.bin > p_arc_result.txt
	p_copy.bat



#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
test:
	echo $(LDIRT_CLEAN)

#echo $(foreach types,$(FILETYPES),$(wildcard *$(types)*))




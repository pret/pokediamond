#! make -f
#----------------------------------------------------------------------------
# Project:  技エフェクト
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------
DP_ROOT	=	../..

SUBDIRS		=

CP_RES_DIR = q:\\pokegra\\
RES_DIR	= .

include	sourcefile.lst

#----------------------------------------------------------------------------
#	Ｃソース→バイナリ変換を可能にするための設定
#----------------------------------------------------------------------------
include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#共通変数定義
include $(DP_ROOT)/commondefs.GF

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

#--------------------------------------------------------------
#	
#--------------------------------------------------------------
LDIRT_CLEAN	= pokezukan.narc $(CONVSRCS:.dat=.bin)

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

do-build: res_cp
res_cp:
	xcopy /d /y $(CP_RES_DIR)pokezukan.dat $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)pokezukan.txt $(RES_DIR)

do-build: pokezukan.bin
pokezukan.bin: pokezukan.dat
	echo "#include \"$(NITROSDK_ROOT)/include/nitro/types.h\"" > temp.c
	cat pokezukan.dat >> temp.c
	$(CC) $(CCFLAGS) $(INCLUDES)  -c temp.c -MD -o pokezukan.o
	$(MWLD) -dis -o pokezukan.elf pokezukan.o
	$(ELF2BIN) pokezukan.elf
	-rm pokezukan.o temp.c temp.d
	-rm pokezukan.elf

do-build: shinzukan.bin
shinzukan.bin: pokezukan.txt
	shincnv pokezukan.txt shinzukan.dat
	echo "#include \"$(NITROSDK_ROOT)/include/nitro/types.h\"" > temp.c
	cat shinzukan.dat >> temp.c
	$(CC) $(CCFLAGS) $(INCLUDES)  -c temp.c -MD -o shinzukan.o
	$(MWLD) -dis -o shinzukan.elf shinzukan.o
	$(ELF2BIN) shinzukan.elf
	-rm shinzukan.o temp.c temp.d
	-rm shinzukan.elf

#----------- アーカイブする -----------
do-build: pokezukan.narc
pokezukan.narc: pokezukan.bin
#	$(MAKE) mklst				#一覧を作成して
#	$(MAKE) makebin				#Ｃソース→バイナリ変換して
	$(MAKE) makearc				#アーカイブにまとめる

do-build: shinzukan.narc
shinzukan.narc: shinzukan.bin
#	$(MAKE) mklst				#一覧を作成して
#	$(MAKE) makebin				#Ｃソース→バイナリ変換して
	$(MAKE) makearc				#アーカイブにまとめる

#対象ソース一覧作成
#mklst:
#	ls -1 *.dat > temp
#	$(LISTMK) temp sourcefile.lst CONVSRCS
#	rm temp

#Ｃソース→バイナリ変換
#makebin: $(CONVSRCS:.dat=.bin)

#アーカイブ作成
makearc:
	nnsarc -c -l -n -i pokezukan.narc pokezukan.bin
	nnsarc -c -l -n -i shinzukan.narc shinzukan.bin
#	nnsarc -i -c -l -n $(TARGET_ARC) *.bin > arc_result.txt

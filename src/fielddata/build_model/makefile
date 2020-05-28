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

TARGET_ARC	=	build_model.narc
BMXLS_DATA	= build_model.xls
MSD_DATA =	build_model.txt

DATABIN		= ../../data/
DATASRC		= $(DATABIN)rsc
NSBMDFILESDIR	= nsbmd_files/
AREA_BUILD_MODEL_DIR	= ../areadata/area_build_model
ROOT_DIR = ../../../../pokemon_dp

##include	sourcefile.lst

#----------------------------------------------------------------------------
#	Ｃソース→バイナリ変換を可能にするための設定
#----------------------------------------------------------------------------
include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#共通変数定義
include $(DP_ROOT)/commondefs.GF

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

include g3_build

#----------------------------------------------------------------------------
#
#----------------------------------------------------------------------------
#アーカイブファイルをmake clean対象に設定
LDIRT_CLEAN	= $(TARGET_ARC) $(TARGET_ARC:.narc=.naix) $(MSD_DATA)

LINCLUDES		= $(NITROSDK_ROOT)/include
LINCLUDES		+= $(DP_ROOT)/src/field

LINCLUDES	+= $(dir $<)

IMDCHECKER = $(DP_ROOT)/chkimdver.rb
CHKIMDTMP = imdchk_log.txt
CHKIMDVER = 1.6.0.20051121
#----------------------------------------------------------------------------
#	ツールへのパス指定
#----------------------------------------------------------------------------
LISTMK		= ruby listmk.rb
MSCONVERTER	= $(DP_ROOT)/convert/imd2mat/imd2mat.exe
G3DCVTR	= $(NITROSYSTEM_ROOT)/tools/win/bin/g3dcvtr.exe
CSVCVTR	= $(DP_ROOT)/convert/exceltool/excelcommaconv.exe

%.nsbmd: $(@:.nsbmd=.imd) $(subst $(DATASRC)/,$(NSBMDFILESDIR),$@)
	$(G3DCVTR) $(@:.nsbmd=.imd) -o $(subst $(DATASRC)/,$(NSBMDFILESDIR),$@)
#	ruby $(IMDCHECKER) $(@:.nsbmd=.imd) $(CHKIMDVER) $(CHKIMDTMP)

#----------------------------------------------------------------------------
#
#	ルール定義
#
#----------------------------------------------------------------------------
do-build: $(MSD_DATA) $(TARGET_ARC)

$(MSD_DATA): $(BMXLS_DATA)
	$(MAKE) csvconvert			#build_model.xlsをcsvコンバート
	
$(TARGET_ARC): $(G3D_IMD) $(BMXLS_DATA)
	$(MAKE) convert				#マットシェイプコンバート
	$(MAKE) mklst				#リスト作成
	$(MAKE) imdconv				#IMD TO NSBMD
	$(MAKE) makearc				#アーカイブ
	$(MAKE) -C $(AREA_BUILD_MODEL_DIR)

#コンバータ呼び出し
convert:
	$(MSCONVERTER) $(MSD_DATA) -i $(DATASRC)/
	
#IMDをMSBNDに変換
imdconv: $(G3D_IMD:.imd=.nsbmd) 	

#ターゲットxlsをcsvファイルに変換
csvconvert:
	$(CSVCVTR) $(BMXLS_DATA)

#対象ソース一覧作成
mklst:
	$(LISTMK) $(MSD_DATA)

#アーカイブ作成
makearc:
	nnsarc -i -c -l -n $(TARGET_ARC) -S nsbmd.txt > arc_result.txt

model:
	-$(RM) $(subst $(DATASRC)/,$(NSBMDFILESDIR),$(G3D_IMD:.imd=.nsbmd))
	-$(RM) $(TARGET_ARC)
	-$(MAKE)
	touch $(DP_ROOT)/src/system/builddate.c
	-$(MAKE) -C $(DP_ROOT)

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------

#echo $(foreach types,$(FILETYPES),$(wildcard *$(types)*))




#! make -f
#----------------------------------------------------------------------------
# Project:  地形関連データ->バイナリー>アーカイブ
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------
DP_ROOT	=	../../..

SUBDIRS		=

LAND_LIST	= land_list
LAND_ARCLIST = land_arc_list
TARGET_ARC	= land_data.narc
XLS_DATA	= map_list.xls
FLDCSV		= field_list.csv
ROOMCSV		= room_list.csv
DUNCSV		= dungeon_list.csv
UNDERCSV	= under_list.csv

DATABIN		:= ../../data/
DATASRC		:= $(DATABIN)rsc
FLDMAPDATADIR	:= $(DATABIN)fld_map_data
NSBMTFILESDIR	= land_nsbmt/
ROOT_DIR = ../../../../pokemon_dp

MAPMATRIX_DIR = ../mapmatrix

ATTRIBUTE_DATA	= $(FLDMAPDATADIR)/*a.dat
MODEL_POS_DATA	= $(FLDMAPDATADIR)/*e.dat
HEIGHT_DATA	= $(FLDMAPDATADIR)/*c.bhc

DATAMAPDMY		= dmyfiles/
DATAMAPSRC		= $(DATASRC)/
DATAMAPFLST		= mkmapdmy.txt

#共通変数定義
include $(DP_ROOT)/commondefs.GF
include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

include land_model_list
include land_list
G3D_NSBMT = $(G3D_IMD:.imd=.nsbmt)
G3D_TARGET		= $(subst $(DATASRC)/,$(NSBMTFILESDIR),$(G3D_NSBMT))

#----------------------------------------------------------------------------
#
#----------------------------------------------------------------------------
#アーカイブファイルをmake clean対象に設定
#LDIRT_CLEAN	= $(LAND_LIST) 
LDIRT_CLEAN	= $(LAND_ARCLIST) $(TARGET_ARC) $(TARGET_ARC:.narc=.naix) bin/*.bin land_nsbmt/*.nsbmt

LINCLUDES		= $(NITROSDK_ROOT)/include
LINCLUDES		+= $(DP_ROOT)/src/field

LINCLUDES	+= $(dir $<)

#----------------------------------------------------------------------------
#	ツールへのパス指定
#----------------------------------------------------------------------------
G3DCVTR	= $(NITROSYSTEM_ROOT)/tools/win/bin/g3dcvtr.exe
CSVCVTR	= $(DP_ROOT)/convert/exceltool/ExcelSeetConv.exe
MK_GROUNDTOOL = mkmapdmy.rb

#%.nsbmt: $(@:.nsbmt=.imd) $(subst $(DATASRC)/,$(NSBMTFILESDIR),$@)
#	$(G3DCVTR) $(@:.nsbmt=.imd) -o $(subst $(DATASRC)/,$(NSBMTFILESDIR),$(@:.nsbmt=.nsbmd)) -emdl
#	mv $(subst $(DATASRC)/,$(NSBMTFILESDIR),$(@:.nsbmt=.nsbmd)) $(subst $(DATASRC)/,$(NSBMTFILESDIR),$@)

#%.nsbmt: $(subst $(NSBMTFILESDIR),$(DATASRC)/,$(@:.nsbmt=.imd))
%.nsbmt: ../$(DATASRC)/%.imd
	$(G3DCVTR) $(subst $(NSBMTFILESDIR),$(DATASRC)/,$(@:.nsbmt=.imd)) -o $(@:.nsbmt=.nsbmd) -emdl
	echo	$^
	mv $(@:.nsbmt=.nsbmd) $@

%.bin: ../$(FLDMAPDATADIR)/%a.dat ../$(FLDMAPDATADIR)/%e.dat ../$(FLDMAPDATADIR)/%c.bhc ../land_nsbmt/%c.nsbmt
	ruby land_file_cat.rb $@
	rm $(subst bin/,tmp/,$(@:.bin=.tmp))
#----------------------------------------------------------------------------
#
#	ルール定義
#
#----------------------------------------------------------------------------
do-build: $(TARGET_ARC)
$(LAND_ARCLIST): $(XLS_DATA)
	$(CSVCVTR) -o $(FLDCSV) -p 1 -s csv $(XLS_DATA)		#フィールド
	$(CSVCVTR) -o $(ROOMCSV) -p 2 -s csv $(XLS_DATA)	#ルーム
	$(CSVCVTR) -o $(DUNCSV) -p 3 -s csv $(XLS_DATA)		#ダンジョン
	$(CSVCVTR) -o $(UNDERCSV) -p 4 -s csv $(XLS_DATA)	#地下
	ruby land_list.rb $(FLDCSV) $(ROOMCSV) $(DUNCSV) $(UNDERCSV)		#リスト作成

#IMDをMSBNTに変換
imdconv: $(G3D_TARGET)

#データ結合
datacat: $(CONCAT_TARGET)

$(TARGET_ARC): $(CONCAT_TARGET)	$(LAND_ARCLIST)
	$(MAKE) makearc				#アーカイブ

#アーカイブ作成
makearc:
	nnsarc -i -c -l -n $(TARGET_ARC) -S $(LAND_ARCLIST) > arc_result.txt
	touch ../../system/builddate.c

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------

#echo $(foreach types,$(FILETYPES),$(wildcard *$(types)*))

#----------------------------------------------------------------------------
# 	地形関連データダミー作成コマンド	
#----------------------------------------------------------------------------
ground:
	$(MAKE) csvconvert			#map_list.xlsをcsvコンバート
	$(MAKE) grd_all
grd_all:
	ruby $(MK_GROUNDTOOL) $(DATAMAPDMY) $(FLDMAPDATADIR)/ $(DATAMAPSRC) $(DATAMAPFLST)

cvs_grd_add:
	ruby cvs_maplist.rb $(DATAMAPFLST) $(FLDMAPEDATADIR)/ $(DATAMAPSRC) log.txt 1 

cvs_grd_del:
	ruby cvs_maplist.rb $(DATAMAPFLST) $(FLDMAPEDATADIR)/ $(DATAMAPSRC) log.txt 2

#ターゲットxlsをcsvファイルに変換
old_csvconvert:
	$(CSVCVTR) -o old_$(FLDCSV) -p 1 -s csv old_$(XLS_DATA)
	$(CSVCVTR) -o old_$(ROOMCSV) -p 2 -s csv old_$(XLS_DATA)
	$(CSVCVTR) -o old_$(DUNCSV) -p 3 -s csv old_$(XLS_DATA)
	$(CSVCVTR) -o old_$(UNDERCSV) -p 4 -s csv old_$(XLS_DATA)

#ターゲットxlsをcsvファイルに変換
csvconvert:
	$(CSVCVTR) -o $(FLDCSV) -p 1 -s csv $(XLS_DATA)
	$(CSVCVTR) -o $(ROOMCSV) -p 2 -s csv $(XLS_DATA)
	$(CSVCVTR) -o $(DUNCSV) -p 3 -s csv $(XLS_DATA)
	$(CSVCVTR) -o $(UNDERCSV) -p 4 -s csv $(XLS_DATA)


#! make -f
#----------------------------------------------------------------------------
# Project:  ゾーンマトリクス作成
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------
DP_ROOT	=	../../..

SUBDIRS		=

TARGET_ARC	=	map_matrix.narc
MAPMATRIXTXT = map_matrix.txt
ARCLIST = arclist
XLS = *.xls
BINDATA	=	*.bin
ENUMHEADER	= map_matrix_id.h
FLDCSV_FOR_MAT		= field_list_for_mat.csv
ROOMCSV_FOR_MAT		= room_list_for_mat.csv
DUNCSV_FOR_MAT		= dun_list_for_mat.csv
UNDERCSV_FOR_MAT	= ug_list_for_mat.csv
LAND_XLS_DATA	= ../land_data/map_list.xls

#----------------------------------------------------------------------------
#	Ｃソース→バイナリ変換を可能にするための設定
#----------------------------------------------------------------------------
include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#共通変数定義
include $(DP_ROOT)/commondefs.GF

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

#----------------------------------------------------------------------------
#
#----------------------------------------------------------------------------
#Makeで生成される*.binはmake cleanの削除対象にする
LDIRT_CLEAN	= $(TARGET_ARC) $(ENUMHEADER) $(BINDATA)

LINCLUDES		= $(NITROSDK_ROOT)/include
LINCLUDES		+= $(DP_ROOT)/src/field

LINCLUDES	+= $(dir $<)

#----------------------------------------------------------------------------
#	ツールへのパス指定
#----------------------------------------------------------------------------
LISTMK		= listmk.rb
MAPMATRIX	= MapMatrix.exe
CSVCVTR	= $(DP_ROOT)/convert/exceltool/ExcelSeetConv.exe

#----------------------------------------------------------------------------
#
#	ルール定義
#
#----------------------------------------------------------------------------
do-build: $(TARGET_ARC)

$(TARGET_ARC): $(XLS)
	$(MAKE) mklandlst			#ランドリスト作成
	$(MAKE) convxls				#エクセルコンバート
	$(MAKE) mklst				#一覧を作成
	$(MAKE) convert				#コンバート
	$(MAKE) makearc				#アーカイブ

#ランドリスト作成
mklandlst:
	$(CSVCVTR) -o $(FLDCSV_FOR_MAT) -p 1 -s csv $(LAND_XLS_DATA)
	$(CSVCVTR) -o $(ROOMCSV_FOR_MAT) -p 2 -s csv $(LAND_XLS_DATA)
	$(CSVCVTR) -o $(DUNCSV_FOR_MAT) -p 3 -s csv $(LAND_XLS_DATA)
	$(CSVCVTR) -o $(UNDERCSV_FOR_MAT) -p 4 -s csv $(LAND_XLS_DATA)
	ruby make_land_list.rb $(FLDCSV_FOR_MAT) $(ROOMCSV_FOR_MAT) $(DUNCSV_FOR_MAT) $(UNDERCSV_FOR_MAT)

#エクセルコンバート
convxls:
	excel_conv.bat
	
#対象ソース一覧作成
mklst:
	ruby listmk.rb $(MAPMATRIXTXT)

#コンバート
convert:
	$(MAPMATRIX)
	
#アーカイブ作成
makearc:
	nnsarc -i -c -l -n $(TARGET_ARC) -S $(ARCLIST)  > arc_result.txt

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------

#echo $(foreach types,$(FILETYPES),$(wildcard *$(types)*))




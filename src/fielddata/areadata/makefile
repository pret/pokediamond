#! make -f
#----------------------------------------------------------------------------
# Project:  エリアデータ作成
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------
DP_ROOT	=	../../..

SUBDIRS		=

TARGET_ARC	=	area_data.narc
TEXSET_ARC	=	map_tex_set.narc
AREABUILD_ARC	= area_build.narc

ARCLIST	=	area_list.txt
BUILDXLSLIST	=	build_xls_list.txt
TEX_IMD_LIST	= tex_imd_list.txt
ORGAREAXLS	= org_areaxxo.xls
ORGTEXSET	= org_tex_set.imd
XLS	=	*.xls
BINDATA	=	*.bin
TXTDATA	=	*txt
ENUMHEADER	=	area_id.h

BUILD_DIR	=	area_build_model
TEXSET_DIR	=	area_map_tex
MMODEL_DIR	=	area_move_model

DATABIN		= ../../data/
DATASRC		= $(DATABIN)rsc
NSBTXFILESDIR	= $(TEXSET_DIR)/nsbtx_files
NSBTXFILES_DIR	= nsbtx_files

AREA_TABLE	= area_table.txt
AREABM_LIST = abmlst_files

TEXSET_LIST = $(TEXSET_DIR)/g3_texset
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
LDIRT_CLEAN	= $(TARGET_ARC) $(ENUMHEADER) $(BINDATA) $(TXTDATA) $(BUILD_DIR)/$(AREABUILD_ARC) $(TEXSET_DIR)/$(TEXSET_ARC) $(AREABM_LIST)

LINCLUDES		= $(NITROSDK_ROOT)/include
LINCLUDES		+= $(DP_ROOT)/src/field

LINCLUDES	+= $(dir $<)

#----------------------------------------------------------------------------
#	ツールへのパス指定
#----------------------------------------------------------------------------
LISTMK		= listmk.rb
AREACONV	= Area.exe
NEWFILE	= make_new_file.exe
ABMLIST_MK	= ruby abmlstmk.rb
TEXSET_MK	 = ruby mklst_texset.rb

#----------------------------------------------------------------------------
#	リスト作成時の読み込み元ファイル
#----------------------------------------------------------------------------
BUILD_LIST	=	build_list.txt
TEX_LIST	=	tex_list.txt
MOVE_LIST	=	move_list.txt

#----------------------------------------------------------------------------
#	中間ファイル
#----------------------------------------------------------------------------
#BUILD	=	build
#TEXSET	=	texset

#----------------------------------------------------------------------------
#
#	ルール定義
#
#----------------------------------------------------------------------------
#do-build: $(TARGET_ARC) mkabmlst 
do-build: $(TARGET_ARC) $(AREABM_LIST)

$(TARGET_ARC): $(XLS)
	$(MAKE) convxls				#エクセルコンバート
	$(MAKE) convert				#コンバート
	$(MAKE) mkabmlst			#エリア配置モデルファイルリスト作成
	$(MAKE) mktexsetlst			#テクスチャセット元データリスト作成
	$(MAKE) makearc				#エリアデータアーカイブ
	$(MAKE) addnew				#新規空データ追加
	$(MAKE) movelist			#リストファイル移動
	$(MAKE) -C $(BUILD_DIR)			#配置データアーカイブ
	$(MAKE) -C $(TEXSET_DIR)
	$(MAKE) -C $(MMODEL_DIR)	#動作モデルリストアーカイブ

#エクセルコンバート
convxls:
	area_id.bat
	
#コンバート
convert:
	$(AREACONV)
	
#アーカイブ作成
makearc:
	nnsarc -i -c -l -n $(TARGET_ARC) -S $(ARCLIST)  > arc_result.txt

#新規に空データをディレクトリに追加
addnew:
	$(NEWFILE) $(BUILDXLSLIST) $(BUILD_DIR) $(ORGAREAXLS)
	$(NEWFILE) $(TEX_IMD_LIST) $(DATASRC) $(ORGTEXSET)

#リストファイル移動
movelist:
	ruby $(LISTMK) $(BUILD_LIST) tmp $(BUILD_DIR)/$(BUILD_LIST)
	-rm $(BUILD_LIST)
	ruby $(LISTMK) $(TEX_LIST) $(NSBTXFILES_DIR) $(TEXSET_DIR)/$(TEX_LIST)
	-rm $(TEX_LIST)

#area build list作成
mkabmlst:
	$(ABMLIST_MK) $(AREA_TABLE) $(AREABM_LIST)

#マップテクスチャセットリスト作成
mktexsetlst:
	$(TEXSET_MK) $(AREA_TABLE) $(TEXSET_LIST)
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------

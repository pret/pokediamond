#! make -f
#----------------------------------------------------------------------------
# Project:  テクスチャセットデータ作成
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------
DP_ROOT	=	../../../..

SUBDIRS		=
TARGET_ARC		= map_tex_set.narc

ARCLIST			= tex_list.txt

#DATABIN			= ../../../data/
#DATASRC			= $(DATABIN)rsc
TEXSETIMDDIR		= imd_files
NSBTXFILESDIR	= nsbtx_files
AREA_TABLE		= ../area_table.txt

#----------------------------------------------------------------------------
#	Ｃソース→バイナリ変換を可能にするための設定
#----------------------------------------------------------------------------
include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#共通変数定義
include $(DP_ROOT)/commondefs.GF

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

include g3list
include g3_texset
#----------------------------------------------------------------------------
#
#----------------------------------------------------------------------------
#Makeで生成される*.binはmake cleanの削除対象にする
LDIRT_CLEAN	= $(TARGET_ARC) $(NSBTXFILESDIR)/*.nsbtx

LINCLUDES		= $(NITROSDK_ROOT)/include
LINCLUDES		+= $(DP_ROOT)/src/field

LINCLUDES	+= $(dir $<)

#----------------------------------------------------------------------------
#	ツールへのパス指定
#----------------------------------------------------------------------------
G3LISTMK	= g3listmk.rb
G3DCVTR	= $(NITROSYSTEM_ROOT)/tools/win/bin/g3dcvtr.exe
TEXIMD_CMB = texset_cmb.rb
TEX_MAG = $(DP_ROOT)/convert/tex_mag/tex_mag.exe

%.nsbtx: $(@:.nsbtx=.imd) $(subst $(TEXSETIMDDIR)/,$(NSBTXFILESDIR/),$@)
	$(G3DCVTR) $(@:.nsbtx=.imd) -o $(subst $(TEXSETIMDDIR)/,$(NSBTXFILESDIR)/,$@) -etex

#----------------------------------------------------------------------------
#
#	ルール定義
#
#----------------------------------------------------------------------------
do-build: $(TARGET_ARC)

$(TARGET_ARC): $(G3D_TEX_SET) $(ARCLIST)
	$(MAKE) mkg3list			#NSBTX変換リスト
	$(MAKE) texset_cmb			#常駐|非常駐テクスチャセットマージ
	$(MAKE) imdconv				#IMD変換
	$(MAKE) texsetarc			#テクスチャセットアーカイブ

#NSBTX変換用リスト作成
mkg3list:
	ruby $(G3LISTMK) $(ARCLIST) $(NSBTXFILESDIR)/

#常駐|非常駐テクスチャセットをマージ
texset_cmb:
	ruby $(TEXIMD_CMB) $(AREA_TABLE) $(TEXSETIMDDIR)/ $(TEX_MAG)

#IMDをNSBTXに変換
imdconv:$(G3D_TEX_IMD:.imd=.nsbtx)

#テクスチャセットのアーカイブ
texsetarc:
	nnsarc -i -c -l -n $(TARGET_ARC) -S $(ARCLIST)  > arc_result.txt

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------

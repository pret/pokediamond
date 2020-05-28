#! make -f
#----------------------------------------------------------------------------
# Project:  エリア配置データ作成
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------
DP_ROOT	=	../../../..
BM_ROOT	=	../../build_model
AREA_ROOT = ..
AREABM_ROOT = .
AREABM_TMPD = $(AREABM_ROOT)/tmp/

SUBDIRS		=

TARGET_ARC	=	area_build.narc

ARCLIST	=	build_list.txt

BUILD_MODEL	= $(BM_ROOT)/build_model.txt
BUILD_MODEL_ARC	= $(BM_ROOT)/build_model.narc
AREA_TABLE	= $(AREA_ROOT)/abmlst_files

BMTMP_DAT	= $(AREABM_LIST:.xls=.dat)
BMTMP_BLF	= $(AREABM_LIST:.xls=.blf)
BMTMP_TXT	= $(AREABM_LIST:.xls=.txt)
BMTMP_IMD	= $(AREABM_LIST:.xls=.imd)
BMTMP_BTX	= $(AREABM_LIST:.xls=.nsbtx)
BMTMP_DATP	= $(subst $(AREABM_ROOT)/,$(AREABM_TMPD),$(BMTMP_DAT))
BMTMP_BLFP	= $(subst $(AREABM_ROOT)/,$(AREABM_TMPD),$(BMTMP_BLF))
BMTMP_IMDP	= $(subst $(AREABM_ROOT)/,$(AREABM_TMPD),$(BMTMP_IMD))
BMTMP_BTXP	= $(subst $(AREABM_ROOT)/,$(AREABM_TMPD),$(BMTMP_BTX))
BMTMP_TXTP	= $(subst $(AREABM_ROOT)/,,$(BMTMP_TXT))

IMD_PATH	= $(DP_ROOT)/src/data/rsc/
TEXSET_DMY	= $(AREABM_ROOT)/dmyfiles/dmytexset.nsbtx
OBJTSET_ARC	= $(AREABM_ROOT)/areabm_texset.narc
OBJTSET_ARCI	= $(AREABM_ROOT)/areabm_texset.naix
OBJTSET_ARCLIST	= $(AREABM_ROOT)/areabm_texset.txt

OBJTMP_NSBTX	= $(OBJ_TEXSET:.imd=.nsbtx)
OBJTMP_IMDP		= $(OBJ_ARCSET:.nsbtx=_lst.txt)
OBJTMP_IMD		= $(subst tmp/,,$(OBJTMP_IMDP))


#----------------------------------------------------------------------------
#	Ｃソース→バイナリ変換を可能にするための設定
#----------------------------------------------------------------------------
include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

include g3_texlist

#共通変数定義
include $(DP_ROOT)/commondefs.GF

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

include $(AREA_TABLE) 

#----------------------------------------------------------------------------
#
#----------------------------------------------------------------------------
#Makeで生成される*.binはmake cleanの削除対象にする
LDIRT_CLEAN	= $(TARGET_ARC) $(BMTMP_DATP) $(BMTMP_BLFP) $(BMTMP_IMDP) $(BMTMP_BTXP) $(OBJTSET_ARC) $(OBJTSET_ARCI) $(OBJTSET_ARCLIST)

LINCLUDES		= $(NITROSDK_ROOT)/include
LINCLUDES		+= $(DP_ROOT)/src/field

LINCLUDES	+= $(dir $<)

#----------------------------------------------------------------------------
#	ツールへのパス指定
#----------------------------------------------------------------------------
CSVCVTR	= $(DP_ROOT)/convert/exceltool/excelcommaconv.exe
BMLISTCVTR	= $(DP_ROOT)/convert/mblist/mblistcmd.exe
AREAIMD_CVTR = mkmdl_texset.rb
TEXMAG_EXE	= $(DP_ROOT)/convert/tex_mag/tex_mag.exe
G3DCVTR	= $(NITROSYSTEM_ROOT)/tools/win/bin/g3dcvtr.exe

%.nsbtx: $(@:.nsbtx=.imd)
	$(G3DCVTR) $(@:.nsbtx=.imd) -o $@ -etex

%.msd: 
	$(CSVCVTR) $(@:.msd=.xls)

#----------------------------------------------------------------------------
#
#	ルール定義
#
#----------------------------------------------------------------------------
do-build: $(TARGET_ARC) $(OBJTSET_ARC)

$(TARGET_ARC): $(ARCLIST) $(BUILD_MODEL) $(AREABM_LIST)
	$(MAKE) csvconvert			#cvsコンバート
	$(MAKE) bmlistcvtr			#エリア配置モデルリストデータコンバート
	$(MAKE) makearc				#エリア内配置モデルアーカイブ

$(OBJTSET_ARC):	$(BMTMP_TXTP) $(BUILD_MODEL_ARC)
	$(MAKE) texset				#エリア配置モデルテクスチャセット生成
#	$(MAKE) deltmpfile			#テンポラリファイル削除

#アーカイブ作成
makearc:
	nnsarc -i -c -l -n $(TARGET_ARC) -S $(ARCLIST)  > arc_result.txt

#XLSをCSVに変換
csvconvert:	$(AREABM_LIST:.xls=.msd)

#エリア配置モデルテクスチャセット生成
areaimd_texset:
	ruby $(AREAIMD_CVTR) $(BUILD_MODEL) $(ARCLIST) $(OBJTSET_ARCLIST) $(TEXMAG_EXE) $(IMD_PATH) $(TEXSET_DMY)
#	-rm $(OBJTMP_IMD)

#エリア配置モデルテクスチャセットバイナリ変換
texset_cmv: $(OBJ_TEXSET:.imd=.nsbtx)

#エリア配置モデルテクスチャセットバイナリアーカイブ
texarc:
	nnsarc -i -c -l -n $(OBJTSET_ARC) -S $(OBJTSET_ARCLIST) > arcres_tset.txt
#	-rm $(OBJ_TEXSET) $(OBJ_ARCSET)

#エリア配置モデルテクスチャセット生成Only
texset:
	-$(RM) $(OBJTSET_ARC) $(OBJTSET_ARCI) $(OBJTSET_ARCLIST) $(BMTMP_IMDP) $(BMTMP_BTXP)
	$(MAKE) areaimd_texset
	$(MAKE) texset_cmv
	$(MAKE) texarc

#dat,blfファイル作成
bmlistcvtr:
	$(BMLISTCVTR) -m $(BUILD_MODEL) -o $(AREABM_TMPD) $(AREABM_LIST:.xls=.txt)

#テンポラリファイル削除
deltmpfile:
	-rm $(BMTMP_TXTP)	
	
#別ディレクトリbuild_modelにある依存ファイルがなければ生成
$(BUILD_MODEL):
	$(CSVCVTR) $(BUILD_MODEL:.txt=.xls)

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------





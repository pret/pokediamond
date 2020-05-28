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

ARC_ANM	=	bm_anime.narc
ARC_ANM_LIST	=	bm_anime_list.narc

DATABIN		= ../../data/
DATASRC		= $(DATABIN)rsc
G3D_ANIME_DIR	= g3d_anime_tmp/
ARC_DIR		= ../../arc/
TARGET_ARC_ANM	=	$(ARC_DIR)$(ARC_ANM)
TARGET_ARC_ANM_LIST	=	$(ARC_DIR)$(ARC_ANM_LIST)

BINFILE = bin/*.bin

ANM_ARC_LIST = anm_arc_list
ANMLST_ARC_LIST = anmlst_arc_list
ARC_LIST = $(ANM_ARC_LIST) $(ANMLST_ARC_LIST)

BUILD_MODEL_CSV = build_model.csv
ANIME_CSV = bm_anm_tbl.csv bm_anime.csv

CSV_FILE = $(BUILD_MODEL_CSV) $(ANIME_CSV)

XLS_FIEL = build_model_anime.xls ../build_model/build_model.xls

#共通変数定義
include $(DP_ROOT)/commondefs.GF
include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

include g3d_list

#----------------------------------------------------------------------------
#
#----------------------------------------------------------------------------
#アーカイブファイルをmake clean対象に設定
LDIRT_CLEAN	= $(TARGET_ARC_ANM) $(TARGET_ARC_ANM_LIST) \
	$(G3D_ANIME_DIR)*.* $(BINFILE)

LINCLUDES		= $(NITROSDK_ROOT)/include
LINCLUDES		+= $(DP_ROOT)/src/field

LINCLUDES	+= $(dir $<)

#----------------------------------------------------------------------------
#	ツールへのパス指定
#----------------------------------------------------------------------------
G3DCVTR	= $(NITROSYSTEM_ROOT)/tools/win/bin/g3dcvtr.exe

%.nsbca: $(@:.nsbca=.ica)
	$(G3DCVTR) $(subst $(G3D_ANIME_DIR),$(DATASRC)/,$(@:.nsbca=.ica)) -o $@

%.nsbta: $(@:.nsbta=.ita)
	$(G3DCVTR) $(subst $(G3D_ANIME_DIR),$(DATASRC)/,$(@:.nsbta=.ita)) -o $@

%.nsbtp: $(@:.nsbtp=.itp)
	$(G3DCVTR) $(subst $(G3D_ANIME_DIR),$(DATASRC)/,$(@:.nsbtp=.itp)) -o $@

G3D_NSBCA = $(subst $(DATASRC)/,$(G3D_ANIME_DIR),$(G3D_ICA:.ica=.nsbca))

G3D_NSBTA = $(subst $(DATASRC)/,$(G3D_ANIME_DIR),$(G3D_ITA:.ita=.nsbta))

G3D_NSBTP = $(subst $(DATASRC)/,$(G3D_ANIME_DIR),$(G3D_ITP:.itp=.nsbtp))

#----------------------------------------------------------------------------
#
#	ルール定義
#
#----------------------------------------------------------------------------
do-build: $(TARGET_ARC_ANM) $(TARGET_ARC_ANM_LIST)
$(CSV_FILE): $(XLS_FIEL)
	excel_conv.bat
	
$(ARC_LIST): $(ANIME_CSV)
	ruby bm_anime.rb
	make
	
$(BINFILE): $(ANIME_CSV)
	ruby bm_anime.rb
	
$(TARGET_ARC_ANM): $(G3D_NSBCA) $(G3D_NSBTA) $(G3D_NSBTP) $(ANM_ARC_LIST)
	$(MAKE) makeanmarc				#アニメアーカイブ

$(TARGET_ARC_ANM_LIST): $(BINFILE) $(ANMLST_ARC_LIST)
	$(MAKE) makelistarc				#リストアーカイブ

#アニメアーカイブ作成
makeanmarc:
	nnsarc -i -c -l -n $(ARC_ANM) -S $(ANM_ARC_LIST) > anm_arc_result.txt
	mv $(ARC_ANM) $(TARGET_ARC_ANM)
	
#リストアーカイブ作成
makelistarc:
	nnsarc -i -c -l -n $(ARC_ANM_LIST) -S $(ANMLST_ARC_LIST) > anmlst_arc_result.txt
	mv $(ARC_ANM_LIST) $(TARGET_ARC_ANM_LIST)

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------

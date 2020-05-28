#! make -f
#----------------------------------------------------------------------------
# Project:  技エフェクト
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

RES_DIR	= .\\resource\\

NITRO_COMP	= ./../../../../convert/nitro_comp/nitro_comp.exe

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs


#Makeで生成される*.binはmake cleanの削除対象にする
LDIRT_CLEAN	= cb_data.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

#-------------------------------
#	実行順
#		リソースコピー
#		リソースアーカイブ
#		技エフェクトアーカイブ
#-------------------------------
do-build: cb_data.narc

#----------- サーバーからコピーする -----------
res_cp:
	xcopy /d /y $(CP_RES_DIR)*.NCGR $(RES_BG_DIR)
	xcopy /d /y $(CP_RES_DIR)*.NCLR $(RES_BG_DIR)
	xcopy /d /y $(CP_RES_DIR)*.NSCR $(RES_BG_DIR)

#----------- アーカイブする -----------
cb_data.narc: $(RES_DIR:\\=/)*.N*R cb.lst
#	nnsarc -c -l -n -i cb_data.narc -S cb.lst
	$(NITRO_COMP) $(NITROSDK_ROOT) cb.lst cb_data.narc cb_data.naix


#! make -f
#----------------------------------------------------------------------------
# Project:  技エフェクト
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

CP_BG_RES_DIR = l:\\graphic\\contest_bg\\
CP_OBJ_RES_DIR = l:\\graphic\\contest_obj\\
RES_BG_DIR	= .\\contest_bg\\
RES_OBJ_DIR	= .\\contest_obj\\

NITRO_COMP	= ./../../../convert/nitro_comp/nitro_comp.exe

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs


#Makeで生成される*.binはmake cleanの削除対象にする
LDIRT_CLEAN	= contest_bg.narc contest_obj.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

#-------------------------------
#	実行順
#		リソースコピー
#		リソースアーカイブ
#		技エフェクトアーカイブ
#-------------------------------
do-build: res_cp contest_bg.narc contest_obj.narc

#----------- サーバーからコピーする -----------
res_cp:
	xcopy /d /y $(CP_BG_RES_DIR)*.NCGR $(RES_BG_DIR)
	xcopy /d /y $(CP_BG_RES_DIR)*.NCLR $(RES_BG_DIR)
	xcopy /d /y $(CP_BG_RES_DIR)*.NSCR $(RES_BG_DIR)
	xcopy /d /y $(CP_OBJ_RES_DIR)*.NCGR $(RES_OBJ_DIR)
	xcopy /d /y $(CP_OBJ_RES_DIR)*.NCER $(RES_OBJ_DIR)
	xcopy /d /y $(CP_OBJ_RES_DIR)*.NCLR $(RES_OBJ_DIR)
	xcopy /d /y $(CP_OBJ_RES_DIR)*.NANR $(RES_OBJ_DIR)

#----------- アーカイブする -----------
contest_bg.narc: $(RES_BG_DIR:\\=/)*.N*R contest_bg.lst
#	nnsarc -c -l -n -i contest_bg.narc -S contest_bg.lst
	$(NITRO_COMP) $(NITROSDK_ROOT) contest_bg.lst contest_bg.narc contest_bg.naix

contest_obj.narc: $(RES_OBJ_DIR:\\=/)*.N*R contest_obj.lst
#	nnsarc -c -l -n -i contest_obj.narc -S contest_obj.lst
	$(NITRO_COMP) $(NITROSDK_ROOT) contest_obj.lst contest_obj.narc contest_obj.naix


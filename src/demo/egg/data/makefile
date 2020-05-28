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
LDIRT_CLEAN	= egg_data.narc $(PT_DIR)egg_demo_particle.narc

PT_DIR = ./particle/

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

#-------------------------------
#	実行順
#		リソースコピー
#		リソースアーカイブ
#		技エフェクトアーカイブ
#-------------------------------
do-build: egg_data.narc $(PT_DIR)egg_demo_particle.narc

#----------- サーバーからコピーする -----------
res_cp:
	xcopy /d /y $(CP_RES_DIR)*.NCGR $(RES_BG_DIR)
	xcopy /d /y $(CP_RES_DIR)*.NCLR $(RES_BG_DIR)
	xcopy /d /y $(CP_RES_DIR)*.NSCR $(RES_BG_DIR)

#----------- アーカイブする -----------
egg_data.narc: $(RES_DIR:\\=/)*.N*R egg.lst
#	nnsarc -c -l -n -i egg_data.narc -S egg.lst
	$(NITRO_COMP) $(NITROSDK_ROOT) egg.lst egg_data.narc egg_data.naix

$(PT_DIR)egg_demo_particle.narc: $(PT_DIR)*.spa
	nnsarc -c -l -n -i $(PT_DIR)egg_demo_particle.narc -S particle\egg_demo_particle.lst


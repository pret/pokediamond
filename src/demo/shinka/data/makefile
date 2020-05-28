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
LDIRT_CLEAN	= $(PT_DIR)shinka_demo_particle.narc

PT_DIR = ./particle/

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

#-------------------------------
#	実行順
#		リソースコピー
#		リソースアーカイブ
#		技エフェクトアーカイブ
#-------------------------------
do-build: $(PT_DIR)shinka_demo_particle.narc

#----------- アーカイブする -----------
$(PT_DIR)shinka_demo_particle.narc: $(PT_DIR)*.spa
	nnsarc -c -l -n -i $(PT_DIR)shinka_demo_particle.narc -S particle\shinka_demo_particle.lst


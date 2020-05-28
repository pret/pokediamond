#! make -f
#----------------------------------------------------------------------------
# Project:  技シーケンス
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

POKEGRA:=$(wildcard *.ncg)
POKECOL:=$(wildcard *.ncl)

CP_RES_DIR = q:\\pokegra\\
CP_RES_DIR2 = l:\\tools\\gf_converter\\pmgracnv\\
RES_DIR	= .
RES_DIR2= c:\\tools\\

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= $(POKEGRA:.ncg=.NCBR) $(POKECOL:.ncl=.NCLR)

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

.suffixes:.ncg.ncl.NCBR.NCLR

do-build:res_cp
res_cp:
	xcopy /d /y $(CP_RES_DIR)deo\\*.ncg $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)deo\\*.ncl $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)unk\\*.ncg $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)unk\\*.ncl $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)powa\\*.ncg $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)powa\\*.ncl $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)otherpoke\\*.ncg $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)otherpoke\\*.ncl $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR2)ncgcnv.exe $(RES_DIR2)
	xcopy /d /y $(CP_RES_DIR2)nclcnv.exe $(RES_DIR2)

do-build: $(POKEGRA:.ncg=.NCBR)
%.NCBR: %.ncg
	ncgcnv $< 1
	cp $@ ..
	cp $*.bin ..

do-build: $(POKECOL:.ncl=.NCLR)
%.NCLR: %.ncl
	nclcnv $<
	cp $@ ..

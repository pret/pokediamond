#! make -f
#----------------------------------------------------------------------------
# Project:  技シーケンス
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

POKEGRA:=$(wildcard *_m.ncg)
POKECOL:=$(wildcard *_n.ncl)

CP_RES_DIR = q:\\pokegra\\
CP_RES_DIR2 = l:\\tools\\gf_converter\\pmgracnv\\
RES_DIR	= .
RES_DIR2= c:\\tools\\

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= $(POKEGRA:.ncg=.NCBR) $(POKECOL:.ncl=.NCLR) $(OTHERPOKE:.ncg=.NCBR) pokegra.narc otherpoke.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

.suffixes:.ncg.ncl.NCBR.NCLR

do-build:res_cp
res_cp:
	xcopy /d /y $(CP_RES_DIR)*.ncg $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)*.ncl $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)*.scr $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)*.dat $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR2)pmncgcnv.exe $(RES_DIR2)
	xcopy /d /y $(CP_RES_DIR2)pmnclcnv.exe $(RES_DIR2)

do-build: $(POKEGRA:.ncg=.NCBR)
%.NCBR: %.ncg
	pmncgcnv $< mfratio.scr

do-build: $(POKECOL:.ncl=.NCLR)
%.NCLR: %.ncl
	pmnclcnv $<

do-build: pokegra.narc
pokegra.narc: $(POKEGRA:.ncg=.NCBR) $(POKECOL:.ncl=.NCLR) pokegra.scr
	nnsarc -c -l -n -i pokegra.narc -S pokegra.scr

do-build: otherpoke.narc
otherpoke.narc: $(POKEGRA:.ncg=.NCBR) otherpoke.scr
	nnsarc -c -l -n -i otherpoke.narc -S otherpoke.scr
	
do-build: height.narc
height.narc: pokegra.narc
	nnsarc -c -l -n height.narc -S height.scr

do-build: height_o.narc
height_o.narc: otherpoke.narc
	nnsarc -c -l -n -i height_o.narc -S height_o.scr

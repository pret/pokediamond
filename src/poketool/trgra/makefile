#! make -f
#----------------------------------------------------------------------------
# Project:  トレーナーグラフィック
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

NCGFILES:=$(wildcard *.ncg)
NCLFILES:=$(wildcard *.ncl)

CP_RES_DIR = q:\\trgra\\
CP_RES_DIR2 = l:\\tools\\gf_converter\\pmgracnv\\
RES_DIR	= .
RES_DIR2= c:\\tools\\

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= *.NCBR *.NCLR trfgra.narc trbgra.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

.SUFFIXES:.ncg.ncl.NCBR.NCLR

do-build:res_cp
res_cp:
	xcopy /d /y $(CP_RES_DIR)*.ncg $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)*.ncl $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)*.scr $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR2)ncgcnv.exe $(RES_DIR2)
	xcopy /d /y $(CP_RES_DIR2)nclcnv.exe $(RES_DIR2)

do-build: $(NCGFILES:.ncg=.NCBR)
%.NCBR: %.ncg
	ncgcnv $< 0

do-build: $(NCLFILES:.ncl=.NCLR)
%.NCLR: %.ncl
	nclcnv $<

do-build: trfgra.narc
trfgra.narc: $(NCGFILES:.ncg=.NCBR) $(NCLFILES:.ncl=.NCLR) arctrf.scr
	nnsarc -c -l -n -i trfgra.narc -S arctrf.scr

do-build: trbgra.narc
trbgra.narc: $(NCGFILES:.ncg=.NCBR) $(NCLFILES:.ncl=.NCLR) arctrb.scr
	nnsarc -c -l -n -i trbgra.narc -S arctrb.scr


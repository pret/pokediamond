#! make -f
#----------------------------------------------------------------------------
# Project:  技シーケンス
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

CP_RES_DIR = q:\\pokeanime\\
CP_RES_DIR2 = q:\\pokegra\\
RES_DIR	= .
RES_DIR2= c:\\tools\\

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= $(POKEGRA:.ncg=.NCBR) $(POKECOL:.ncl=.NCLR) pokeanm.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

.suffixes:.bin

do-build:res_cp
res_cp:
	xcopy /d /y $(CP_RES_DIR)*.bin $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR2)*.dat $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)pmanmcnv.exe $(RES_DIR2)

do-build: pokeanm.narc
pokeanm.narc: *.bin
#	ls -1 *.bin>temp
	pmanmcnv pokeanm.lst pokegrano2.dat pokeanm.dat
	nnsarc -c -l -n -i pokeanm.narc pokeanm.dat

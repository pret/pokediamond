#! make -f
#----------------------------------------------------------------------------
# Project:  トレーナーデータ
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= trtbl.bin trtbl.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

.SUFFIXES: .s .bin

do-build: trtbl.narc
trtbl.narc: trtbl.bin
	trtblmk trtbl.bin trtblofs.bin
	nnsarc -c -l -n -i trtbl.narc trtbl.bin
	nnsarc -c -l -n -i trtblofs.narc trtblofs.bin

do-build: trtbl.bin
trtbl.bin:trtbl.s
	$(MWAS) $< -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	elf2bin $*.elf
	rm $*.o
	rm $*.elf


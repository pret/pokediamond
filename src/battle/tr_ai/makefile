#! make -f
#----------------------------------------------------------------------------
# Project:  トレーナーAI
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= tr_ai_seq.bin tr_ai_seq.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

do-build: tr_ai_seq.bin
tr_ai_seq.bin: tr_ai_seq.s tr_ai_seq_def.h
	$(MWAS) tr_ai_seq.s -o tr_ai_seq.o
	$(MWLD) -dis -o tr_ai_seq.elf tr_ai_seq.o
	elf2bin tr_ai_seq.elf
#	rm tr_ai_seq.o
#	rm tr_ai_seq.elf

do-build: tr_ai_seq.narc
tr_ai_seq.narc: tr_ai_seq.bin
	nnsarc -c -l -n -i tr_ai_seq.narc tr_ai_seq.bin


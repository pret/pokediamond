#! make -f
#----------------------------------------------------------------------------
# Project:  トレーナーデータ
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=
DATAFILES:=$(wildcard trdata_*.s)
POKEFILES:=$(wildcard trpoke_*.s)

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= $(DATAFILES:.s=.bin) $(POKEFILES:.s=.bin) trdata.narc trpoke.narc 

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

.SUFFIXES: .s .bin

do-build: trdata.narc
trdata.narc: $(DATAFILES:.s=.bin)
	nnsarc -c -l -n trdata.narc trdata_*.bin

do-build: trpoke.narc
trpoke.narc: $(POKEFILES:.s=.bin)
	nnsarc -c -l -n trpoke.narc trpoke_*.bin

do-build: $(DATAFILES:.s=.bin)
%.bin:%.s
	$(MWAS) $< -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	elf2bin $*.elf
	rm $*.o
	rm $*.elf

do-build: $(POKEFILES:.s=.bin)
%.bin:%.s
	$(MWAS) $< -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	elf2bin $*.elf
	rm $*.o
	rm $*.elf


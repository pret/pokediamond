#! make -f
#----------------------------------------------------------------------------
# Project:  パーソナルデータ
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

PERFILES:=$(wildcard per_*.s)
WOTFILES:=$(wildcard wot_*.s)
EVOFILES:=$(wildcard evo_*.s)
PMSFILES:=$(wildcard pms_*.bin)

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= $(PERFILES:.s=.bin) $(WOTFILES:.s=.bin) $(EVOFILES:.s=.bin) $(PMSFILES) growtbl.narc personal.narc wotbl.narc evo.narc pms.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

.SUFFIXES: .s .bin

#成長曲線テーブル生成
do-build: growtbl.narc
growtbl.narc: grow_*.bin
	nnsarc -c -l -n growtbl.narc grow_*.bin

#パーソナルデータ生成
do-build: personal.narc
personal.narc: $(PERFILES:.s=.bin)
	nnsarc -c -l -n personal.narc per_*.bin

#技覚えテーブルデータ生成
do-build: wotbl.narc
wotbl.narc: $(WOTFILES:.s=.bin)
	nnsarc -c -l -n wotbl.narc wot_*.bin

#進化テーブルデータ生成
do-build: evo.narc
evo.narc: $(EVOFILES:.s=.bin)
	nnsarc -c -l -n evo.narc evo_*.bin
	pmseed

do-build: $(PERFILES:.s=.bin)
%.bin:%.s
	$(MWAS) $< -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	elf2bin $*.elf
	rm $*.o
	rm $*.elf

do-build: $(WOTFILES:.s=.bin)
%.bin:%.s
	$(MWAS) $< -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	elf2bin $*.elf
	rm $*.o
	rm $*.elf

do-build: $(EVOFILES:.s=.bin)
%.bin:%.s
	$(MWAS) $< -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	elf2bin $*.elf
	rm $*.o
	rm $*.elf


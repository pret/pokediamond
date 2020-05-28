#! make -f
#----------------------------------------------------------------------------
# Project:  技シーケンス
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

WAZASRCS:=$(wildcard waza_*.s)
BESRCS:=$(wildcard be_*.s)
SUBSRCS:=$(wildcard sub_*.s)

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= $(WAZASRCS:.s=.bin) $(BESRCS:.s=.bin) $(SUBSRCS:.s=.bin) waza_seq.narc be_seq.narc sub_seq.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

do-build: $(WAZASRCS:.s=.bin) $(BESRCS:.s=.bin) $(SUBSRCS:.s=.bin)
%.bin: %.s waza_seq_def.h
	$(MWAS) $< -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	elf2bin $*.elf
#	rm $*.o
#	rm $*.elf

do-build: waza_seq.narc
waza_seq.narc: $(WAZASRCS:.s=.bin)
	nnsarc -c -l -n -i waza_seq.narc waza_*.bin

do-build: be_seq.narc
be_seq.narc: $(BESRCS:.s=.bin)
	nnsarc -c -l -n -i be_seq.narc be_*.bin

do-build: sub_seq.narc
sub_seq.narc: $(SUBSRCS:.s=.bin)
	nnsarc -c -l -n -i sub_seq.narc sub_*.bin



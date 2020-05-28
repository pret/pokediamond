#! make -f
#----------------------------------------------------------------------------
# Project:  バトルタワーデータ
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

PMDATA:=$(wildcard btd_pm_*.s)
TRDATA:=$(wildcard btd_tr_*.s)

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= $(PMDATA) $(TRDATA) btdpm.narc btdtr.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

do-build: $(PMDATA) $(TRDATA)
%.s: btf_pm.txt btf_tr.txt
	btdmakepm btf_pm.txt
	btdmaketr btf_tr.txt

do-build: $(PMDATA:.s=.bin) $(TRDATA:.s=.bin)
%.bin: %.s btd_data.h
	$(MWAS) $< -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	elf2bin $*.elf
#	rm tr_ai_seq.o
#	rm tr_ai_seq.elf

do-build: btdpm.narc
btdpm.narc: btd_pm_*.bin
	nnsarc -c -l -n -i btdpm.narc btd_pm_*.bin

do-build: btdtr.narc
btdtr.narc: btd_tr_*.bin
	nnsarc -c -l -n -i btdtr.narc btd_tr_*.bin

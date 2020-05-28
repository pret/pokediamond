#! make -f
#----------------------------------------------------------------------------
# Project:  技エフェクト
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------
DP_ROOT	=	../..
SUBDIRS		=

SKILLDIRS	= .

PA_SRC =$(wildcard animefile/poke_anm*.s)

TARGET_NARC = poke_anm.narc

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs


#Makeで生成される*.binはmake cleanの削除対象にする
LDIRT_CLEAN	= $(PA_SRC:.s=.bin) $(TARGET_NARC)

#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#	ツールへのパス指定
#----------------------------------------------------------------------------
ELF2BIN		= $(DP_ROOT)/convert/eventdata/elf2bin.exe

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

#-------------------------------
#	実行順
#		リソースコピー
#		リソースアーカイブ
#		技エフェクトアーカイブ
#-------------------------------
do-build: $(TARGET_NARC)

$(TARGET_NARC): $(PA_SRC:.s=.bin)
	nnsarc -i -c -l -n $(TARGET_NARC) animefile/poke_anm*.bin
	touch p_anm_sys.c
		
%.bin: %.s past.h
	$(MWAS) $< -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	$(ELF2BIN) $*.elf
	rm $*.o
	rm $*.elf

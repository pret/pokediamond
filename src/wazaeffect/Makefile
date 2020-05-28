#! make -f
#----------------------------------------------------------------------------
# Project:  技エフェクト
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

SKILLDIRS	= .

WE_SRC:=$(wildcard we_*.s)
SE_SRC:=$(wildcard se_*.s)
WESUB_SRC:=$(wildcard wesub_*.s)

//CP_RES_DIR = m:\\staff\\gotou\\we_resource\\
CP_RES_DIR	= l:\\graphic\\wazaeff_res\\
NARC_DIR	= ./effectclact/
RES_DIR		= ./effectclact/resource/
WP_DIR		= ./effectdata/
PT_DEBUG_DIR= ./pt_debug/

NITRO_COMP	= ./../../convert/nitro_comp/nitro_comp.exe
ETD	= ./../../convert/nitro_comp/etd.exe

include	srcfile.lst
include	srcfile_sub.lst

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs


#Makeで生成される*.binはmake cleanの削除対象にする
LDIRT_CLEAN	= $(WE_SRC:.s=.bin) we.arc $(WESUB_SRC:.s=.bin) we_sub.narc $(WP_DIR)waza_particle.narc $(WP_DIR)ball_particle.narc $(PT_DEBUG_DIR)debug_particle.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

#-------------------------------
#	実行順
#		リソースコピー
#		リソースアーカイブ
#		技エフェクトアーカイブ
#-------------------------------
do-build: res_cp mklst $(NARC_DIR)wechar.narc $(NARC_DIR)wepltt.narc $(NARC_DIR)wecell.narc $(NARC_DIR)wecellanm.narc $(WP_DIR)waza_particle.narc $(WP_DIR)ball_particle.narc $(PT_DEBUG_DIR)debug_particle.narc $(WE_SRC:.s=.bin) $(SE_SRC:.s=.bin) $(WESUB_SRC:.s=.bin) we.arc we_sub.narc 
%.bin: %.s west.h
	$(MWAS) $< -o $*.o
	$(MWLD) -dis -o $*.elf $*.o
	elf2bin $*.elf
	rm $*.o
	rm $*.elf
	touch we_sys.c

#---------- 技エフェクトをアーカイブする ----------
we.arc: $(wildcard *.bin)
	nnsarc -c -l -n we.arc we_*.bin

#---------- 状態異常エフェクトをアーカイブする ----------
we_sub.narc: $(wildcard *.bin)
	nnsarc -c -l -n we_sub.narc wesub_*.bin

#---------- ステータスエフェクトをアーカイブする ----------
se.narc: $(wildcard *.bin)
#	nnsarc -c -l -n se.narc se_*.bin
	
#---------- サブエフェクト ----------
#we_sub.narc: we_s*.s
#	nnsarc -c -l -n -i we_sub.narc -S we_sub.lst
#	effectclact/etd effectclact\we_sub.naix

#----------- リストの作成 ----------
mklst:
	#----- メインエフェクト -----
#	ls -1 we_*.s > temp
#	listmk temp srcfile.lst
#	rm temp

	#----- サブエフェクト -----
#	ls -1 wesub_*.s > temp
#	listmk temp srcfile_sub.lst
#	rm temp

	#----- ステータスエフェクト -----
#	ls -1 se_*.s > temp
#	listmk temp srcfile_se.lst
#	rm temp

#----------- サーバーからコピーする -----------
res_cp:
	xcopy /d /y /q $(CP_RES_DIR)*.NCGR .\\effectclact\\resource
	xcopy /d /y /q $(CP_RES_DIR)*.NCER .\\effectclact\\resource
	xcopy /d /y /q $(CP_RES_DIR)*.NCLR .\\effectclact\\resource
	xcopy /d /y /q $(CP_RES_DIR)*.NANR .\\effectclact\\resource

#----------- アーカイブする ----------- 
$(NARC_DIR)wechar.narc: $(RES_DIR)*.NCGR
#	nnsarc -c -l -n -i $(NARC_DIR)wechar.narc $(RES_DIR)*.NCGR
#	nnsarc -c -l -n -i $(NARC_DIR)wechar.narc -S effectclact\wechar.lst
#	effectclact/etd effectclact\wechar.naix
	$(NITRO_COMP) $(NITROSDK_ROOT) effectclact\wechar.lst wechar.narc wechar.naix

$(NARC_DIR)wepltt.narc: $(RES_DIR)*.NCLR
#	nnsarc -c -l -n -i $(NARC_DIR)wepltt.narc $(RES_DIR)*.NCLR
#	nnsarc -c -l -n -i $(NARC_DIR)wepltt.narc -S effectclact\wepltt.lst
#	effectclact/etd effectclact\wepltt.naix
	$(NITRO_COMP) $(NITROSDK_ROOT) effectclact\wepltt.lst wepltt.narc wepltt.naix

$(NARC_DIR)wecell.narc: $(RES_DIR)*.NCER
#	nnsarc -c -l -n -i $(NARC_DIR)wecell.narc $(RES_DIR)*.NCER
#	nnsarc -c -l -n -i $(NARC_DIR)wecell.narc -S effectclact\wecell.lst
#	effectclact/etd effectclact\wecell.naix
	$(NITRO_COMP) $(NITROSDK_ROOT) effectclact\wecell.lst wecell.narc wecell.naix

$(NARC_DIR)wecellanm.narc: $(RES_DIR)*.NANR
#	nnsarc -c -l -n -i $(NARC_DIR)wecellanm.narc $(RES_DIR)*.NANR
#	nnsarc -c -l -n -i $(NARC_DIR)wecellanm.narc -S effectclact\wecellanm.lst
#	effectclact/etd effectclact\wecellanm.naix
	$(NITRO_COMP) $(NITROSDK_ROOT) effectclact\wecellanm.lst wecellanm.narc wecellanm.naix


#---------- 技エフェクト用パーティクルをアーカイブする ----------
$(WP_DIR)waza_particle.narc: $(WP_DIR)*.spa
	nnsarc -c -l -n -i $(WP_DIR)waza_particle.narc -S effectdata\waza_particle.lst
	$(ETD) effectdata\waza_particle.naix

$(WP_DIR)ball_particle.narc: $(WP_DIR)*.spa
	nnsarc -c -l -n -i $(WP_DIR)ball_particle.narc -S effectdata\ball_particle.lst
	$(ETD) effectdata\ball_particle.naix

$(PT_DEBUG_DIR)debug_particle.narc: $(PT_DEBUG_DIR)*.spa
	nnsarc -c -l -n -i $(PT_DEBUG_DIR)debug_particle.narc -S pt_debug\debug_particle.lst
	$(ETD) effectdata\debug_particle.naix
	
#---------- SE定義更新に伴い、*.sをtouchする ----------

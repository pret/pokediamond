#! make -f
#----------------------------------------------------------------------------
# Project:  技エフェクト
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

SUBDIRS		=

SPAFILES:=$(wildcard *.spa)

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs


#Makeで生成される*.binはmake cleanの削除対象にする
LDIRT_CLEAN	= particledata.narc

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

.SUFFIXES:.spa.narc

#-------------------------------
#	実行順
#		リソースコピー
#		リソースアーカイブ
#		技エフェクトアーカイブ
#-------------------------------
do-build: particledata.narc
#---------- 技エフェクト用パーティクルをアーカイブする ----------
particledata.narc: $(SPAFILES)
	nnsarc -c -l -n -i particledata.narc -S particledata.lst

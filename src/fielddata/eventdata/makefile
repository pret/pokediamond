#! make -f
#----------------------------------------------------------------------------
# Project:  Cソース->バイナリー
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------
DP_ROOT	=	../../..

SUBDIRS		=

EVENTDATA	=	zone_event.narc

#コンバート対象ファイルのサフィックス
FILETYPES	=	evb	evc	evd	evp

HEADERS		=	evc_id.h evd_id.h script_id.h

include ../maptable/eventlist.txt
#include	sourcefile.lst

NEWSYS	=	YES

EVBFILES	= $(CONVSRCS:_total.c=.evb)
EVCFILES	= $(CONVSRCS:_total.c=.evc)
EVDFILES	= $(CONVSRCS:_total.c=.evd)
EVPFILES	= $(CONVSRCS:_total.c=.evp)

#----------------------------------------------------------------------------
#Cソース→バイナリ変換に必要な定義
#----------------------------------------------------------------------------
include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#共通変数定義
include $(DP_ROOT)/commondefs.GF

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

ELF2BIN	= $(DP_ROOT)/convert/eventdata/celf2bin.exe
LISTMK	= $(DP_ROOT)/convert/eventdata/listmk.exe
ELFPICKUP = $(DP_ROOT)/convert/eventdata/elfpickup.pl
ELFALLPICKUP = $(DP_ROOT)/convert/eventdata/elfallpickup.pl

#----------------------------------------------------------------------------
#Makeで生成される*.binはmake cleanの削除対象にする
#LDIRT_CLEAN	= $(CONVSRCS:.c=.bin) $(foreach mark, $(FILETYPES), $(CONVSRCS:_total.c=_$(mark).bin))
#LDIRT_CLEAN += $(EVENTDATA) $(EVENTDATA:.narc=.naix) $(HEADERS)
#LDIRT_CLEAN += $(CONVSRCS:_total.c=_evb.c) $(CONVSRCS:_total.c=_evc.c) \
#	$(CONVSRCS:_total.c=_evd.c) $(CONVSRCS:_total.c=_evp.c)

LDIRT_CLEAN	= *.bin *.c
LDIRT_CLEAN += $(EVENTDATA) $(EVENTDATA:.narc=.naix) $(HEADERS)

LINCLUDES		= $(NITROSDK_ROOT)/include
LINCLUDES	+= $(dir $<)


#----------------------------------------------------------------------------
#	更新ルール定義
#----------------------------------------------------------------------------

do-build: $(EVENTDATA)


CCFLAGS = -lang c


#----------------------------------------------------------------------------
# precompile
#----------------------------------------------------------------------------
QUOTE			="		#"
DEPEND_RULE	= $(QUOTE)/ARM_EABI_Support/d;s/\\\\\\([^ ]\\)/\\/\\1/g;$(QUOTE)

define MOVE_SRC_DEPEND
	-$(SED) -e $(DEPEND_RULE) $(*F).d > $(DEPENDDIR)/$(*F).d && $(RM) $(*F).d
endef

#PRECOMPILE_SRC		 =	ev_common.h	#precompile.pch
PRECOMPILE_SRC		 =	precompile.pch
PRECOMPILE_CC_MCH	 =	precompile_cc.mch
PRECOMPILE_CCFLAGS	:=	$(CCFLAGS)
#CCFLAGS			+=	-prefix $(PRECOMPILE_CC_MCH)
#INCLUDES		+=	-I$(NITROSDK_ROOT)/include

precompile: $(PRECOMPILE_CC_MCH)

#バージョン定義ファイルが更新されたらプリコンパイルヘッダも更新する
$(PRECOMPILE_CC_MCH):	$(VER_FILE)

-include $(PRECOMPILE_CC_MCH).d
$(PRECOMPILE_CC_MCH):%_cc.mch:
		$(CC) $(PRECOMPILE_CCFLAGS) $(INCLUDES) $(PRECOMPILE_SRC) -MD -precompile $(PRECOMPILE_CC_MCH)
		$(MOVE_SRC_DEPEND)
		$(MV) $(DEPENDDIR)/$(*F).d $@.d

#----------------------------------------------------------------------------

#$(EVENTDATA): $(CONVSRCS:.c=.bin)
$(EVENTDATA): all_data.bin
	nnsarc -i -c -l -n -S ../maptable/eventarc.txt $(EVENTDATA) > arc_result.txt


%_total.bin:	all_data.elf
	$(ELFPICKUP) $(@:.bin=) all_data.elf > $*_total.elf
	$(ELF2BIN) $*_total.elf > /dev/null
	rm $*_total.elf

all_data.bin:	all_data.elf
	@echo $(CONVSRCS:_total.c=) > flist
	$(ELFALLPICKUP) flist all_data.elf
	@rm -f flist
	@touch all_data.bin


all_data.elf:	ev_common.h $(EVBFILES) $(EVCFILES) $(EVDFILES) $(EVPFILES) $(HEADERS)
	@cat ev_common.h > all_data.c
	@cat $(EVBFILES) >> all_data.c
	@cat $(EVCFILES) >> all_data.c
	@cat $(EVDFILES) >> all_data.c
	@cat $(EVPFILES) >> all_data.c
	$(CC) $(CCFLAGS) $(INCLUDES) all_data.c -MD -o all_data.o
	$(MWLD) -dis -o all_data.elf all_data.o


#このディレクトリに存在する*evc.hファイルを全部インクルードするファイルevc_id.hを生成
evc_id.h:
	sed "s/evd\.h/evc\.h/" ../maptable/doorevent.h > evc_id.h

#このディレクトリに存在する*evd.hファイルを全部インクルードするファイルevd_id.hを生成
evd_id.h:
	ls -1 *evd.h |sed "s/^/#include \"/;s/$$/\"/" > evd_id.h

#scriptディレクトリに存在する*def.hファイルを全部インクルードするファイルscript_id.hを生成
script_id.h: $(wildcard ../script/*_def.h)
	ls -1 ../script/*_def.h |grep -v scr_seq_def.h |sed "s/^/#include \"/;s/$$/\"/" > script_id.h


#----------------------------------------------------------------------------
#
#		Dummy Target
#
#----------------------------------------------------------------------------
mkinclude:	$(HEADERS)

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
mkdummy:
	$(foreach target, $(CONVSRCS:_total.c=), $(shell dummyfiles/makedummy.bat $(target)))

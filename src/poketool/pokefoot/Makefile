##-----------------------------------------------------------------------------
#**
#*			足跡グラフィックデータアーカイブメイク
#**
##-----------------------------------------------------------------------------


SUBDIRS		=

POKEGRA:=$(wildcard *.nce)
POKECOL:=$(wildcard *.ncl)

CP_RES_DIR = q:\\pokefoot\\
CP_SCR_DIR = q:\\pokegra\\
RES_DIR	= .

include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= $(POKEGRA:.nce=.NCGR) \
			$(POKEGRA:.nce=.NCER) \
			$(POKEGRA:.nce=.NANR) \
			$(POKECOL:.ncl=.NCLR) \
			pokefoot.narc pokefoot.naix

#----------------------------------------------------------------------------

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules

.suffixes:.nce.ncl.NCER.NCLR

do-build:res_cp pokefoot.narc
res_cp:
	xcopy /d /y $(CP_RES_DIR)*.ncg $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)*.nce $(RES_DIR)
	xcopy /d /y $(CP_RES_DIR)*.ncl $(RES_DIR)
	xcopy /d /y $(CP_SCR_DIR)pokefoot.scr $(RES_DIR)


poke_foot_000.NCER: poke_foot_000.nce
	g2dcvtr poke_foot_000.nce
	ntrcomp -l 2 -o poke_foot_000_lzh.NCGR poke_foot_000.NCGR
	mv poke_foot_000_lzh.NCGR poke_foot_000.NCGR
	ntrcomp -l 2 -o poke_foot_000_lzh.NCER poke_foot_000.NCER
	mv poke_foot_000_lzh.NCER poke_foot_000.NCER
	ntrcomp -l 2 -o poke_foot_000_lzh.NANR poke_foot_000.NANR
	mv poke_foot_000_lzh.NANR poke_foot_000.NANR

#do-build: $(POKEGRA:.nce=.NCER)
%.NCER: %.nce
	g2dcvtr $<
	ntrcomp -l 2 -o $*_lzh.NCGR $*.NCGR
	mv $*_lzh.NCGR $*.NCGR

#do-build: $(POKECOL:.ncl=.NCLR)
%.NCLR: %.ncl
	g2dcvtr $<

#do-build: pokefoot.narc
pokefoot.narc: $(POKEGRA:.nce=.NCER) $(POKECOL:.ncl=.NCLR) pokefoot.scr
	nnsarc -c -l -n -i pokefoot.narc -S pokefoot.scr

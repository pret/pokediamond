#! make -f
#----------------------------------------------------------------------------
# Project:  �|�P�b�g�����X�^�[�@�_�C�������h���p�[��
# File:     Makefile
#
# Copyright 2005 GameFreak.inc  All rights reserved.
#
#----------------------------------------------------------------------------

#export	NITRO_DEBUG=TRUE
export MAKEROM_ROMSPEED=1TROM
#export MAKEROM_ROMSPEED=MROM

# NITROSDK3.0�t���̂̃v���R���p�C����ǂݍ��܂Ȃ�
NITRO_NO_STD_PCHDR = True

################################################################################
#
#
#		�}�N���X�C�b�`�̒�`�Ȃ�
#
#
################################################################################
#----------------------------------------------------------------------------
#	�����쐬�p��`�@�i�q�n�l��o�̍ۂ͗L���ɂ���srl�쐬�j
#----------------------------------------------------------------------------
#NITRO_FINALROM = yes

#----------------------------------------------------------------------------
#	�o�[�W������`
#----------------------------------------------------------------------------
VER_FILE	=	version

include	$(VER_FILE)

#(PM_DEBUG == yes)�̂Ƃ��̂݃f�o�b�O�o�[�W����
ifeq	($(PM_DEBUG),yes)
MACRO_FLAGS	+=	-DPM_DEBUG
endif

ifdef	PM_VERSION
MACRO_FLAGS	+=	-DPM_VERSION=$(PM_VERSION)
endif

ifdef	PM_LANG
MACRO_FLAGS	+=	-DPM_LANG=$(PM_LANG)
endif

#----------------------------------------------------------------------------
# LIBSYSCALL: Provided to every product by NINTENDO
#	�V�X�e�����C�u�����̒ǉ�
#----------------------------------------------------------------------------
ifeq	($(PM_VERSION),VERSION_DIAMOND)
LIBSYSCALL	= diamond_rs/libsyscall.a
else
LIBSYSCALL	= pearl_rs/libsyscall.a
endif

#----------------------------------------------------------------------------
#	�C���N���[�h�t�@�C���̃f�B���N�g���̒ǉ�
#----------------------------------------------------------------------------
LINCLUDES      = ./include/gflib \
				 ./include/library

#----------------------------------------------------------------------------
#	���C�u�����f�B���N�g���̒ǉ�
#----------------------------------------------------------------------------
NITRODWC_LIB_MODULES_   = bm account
NITRODWC_LIB_GSMODULES_ = 

LDEPENDS_NEF = $(NITRODWC_LIB_DEPENDS)

LLIBRARY_DIRS	= ./src/library/spl/$(NITRO_BUILDTYPE)

#�C�N�j���[�����R���|�[�l���g�̂��߂̃��C�u������ǉ� by Mori 2005.7.27
LLIBRARIES		= ./libjn_spl.a libwvr$(CODEGEN).a
#LINCLUDES      = ../gflib/include
#LLIBRARY_DIRS  = ../gflib/lib/$(NITRO_BUILDTYPE)
#LLIBRARIES     = libgf.a

# �C�V��Crypt���C�u������ǉ� by mituhara 2006.07.05
LLIBRARY_DIRS	+= ./src/library/crypto/$(NITRO_BUILDTYPE)
LLIBRARIES	+= ./libcrypto.a

#----------------------------------------------------------------------------
#	�����X�y�b�N�t�@�C���ǂݍ��݂̂��ߒǉ�
#----------------------------------------------------------------------------
ifeq	($(PM_VERSION),VERSION_DIAMOND)
#ROM_SPEC= diamond_rs/diamond_release.rsf
ROM_SPEC= diamond.rsf
else
ROM_SPEC= pearl.rsf
endif

#----------------------------------------------------------------------------
#		lsf�t�@�C���ǂݍ��݂̂��ߒǉ� by matsuda
#----------------------------------------------------------------------------
LCFILE_SPEC	=	main.lsf

MAKELCF_FLAGS	+=	-DADDRESS_MAIN=0x02000000

#ifeq	($(NITRO_PLATFORM),TEG)
#MAKELCF_FLAGS	+=	-DADDRESS_MAIN=0x02004000
#else
#MAKELCF_FLAGS	+=	-DADDRESS_MAIN=0x02000000
#endif



#------------------------------------------------------#
# �C�N�j���[�����R���|�[�l���g��ǉ� by Mori 2005.7.27
# VRAM���ɖ������C�u�������z�u�����R���|�[�l���g��` #
MY_COMPONENT_NAME	= ichneumon
MAKEROM_ARM7	= $(NITRO_COMPONENTSDIR)/$(MY_COMPONENT_NAME)/$(NITRO_BUILDTYPE_ARM7)/$(MY_COMPONENT_NAME)_sub$(TS_VERSION).nef
#------------------------------------------------------#

#----------------------------------------------------------------------------
#	�^�[�Q�b�g�t�@�C���ݒ�
#----------------------------------------------------------------------------
#TARGET_NEF	=	main.nef	TARGET_BIN��.srl���w�肷���.nef���ꏏ�ɐ��������
TARGET_BIN	=	main.srl


#----------------------------------------------------------------------------
#	�f�[�^�E�T�u�f�B���N�g���ւ̃p�X�w��
#----------------------------------------------------------------------------
DATABIN			= src/data/
DATASRC			= $(DATABIN)rsc

MSGDATA_DIR		= src/msgdata/
MSGDATA_FILENAME	= msg.narc
MSGDATA_FILEPATH	= $(MSGDATA_DIR)$(MSGDATA_FILENAME)
DATASCENARIO		= $(MSGDATA_DIR)scenario/


SOUNDDIR		= $(DATABIN)sound/

POKEGRADIR		= src/poketool/pokegra/
TRGRADIR		= src/poketool/trgra/
#�o�[�W�����ɂ���ăp�[�\�i���f�[�^��ύX
ifeq	($(PM_VERSION),VERSION_DIAMOND)
PERSONALDIR		= src/poketool/personal/
else
PERSONALDIR		= src/poketool/personal_pearl/
endif
EVOWOTDIR		= src/poketool/personal/
TRAINERDIR		= src/poketool/trainer/
TRMSGDIR		= src/poketool/trmsg/
EFFECTDATADIR	= src/wazaeffect/effectdata/
SAMPLEDATADIR	= src/wazaeffect/pt_debug/
BATTLEGRADIR	= src/battle/graphic/
WAZAEFFDIR		= src/wazaeffect/
WAZASEQDIR		= src/battle/skill/
WAZATBLDIR		= src/poketool/waza/
SCRIPTDIR		= src/fielddata/script/
EVENTDIR		= src/fielddata/eventdata/
ENCOUNTDIR		= src/fielddata/encountdata/
MAPMATRIXDIR	= src/fielddata/mapmatrix/
AREADATADIR		= src/fielddata/areadata/
AREABUILDMDLDIR	= src/fielddata/areadata/area_build_model/
AREAMAPTEXDIR	= src/fielddata/areadata/area_map_tex/
AREAMOVEMDLDIR	= src/fielddata/areadata/area_move_model/
FIELDMAPDIR		= src/fielddata/land_data/
BUILDMODELDIR	= src/fielddata/build_model/
GRAPHICDIR		= src/graphic/
ITEMDATADIR		= src/itemtool/itemdata/
POKEICONGRADIR	= src/poketool/icongra/
POKEFOOTGRADIR	= src/poketool/pokefoot/
WAZAEFFCLACTDIR	= src/wazaeffect/effectclact/
WAZAEFFCLACTRDIR= src/wazaeffect/effectclact/resource/
CONTESTGRADIR	= src/contest/graphic/
CONTESTDATADIR	= src/contest/data/
CLACTUTILDIR	= src/data/clact_util/
PARTICLEDATADIR	= src/particledata/
ZUKANDATADIR 	= src/application/zukanlist/zkn_data/
MMODELDIR		= src/data/mmodel/
WIFIEARTHDIR	= src/application/wifi_earth/
POKEANIMEDIR	= src/pokeanime/
CBDATADIR	 	= src/application/custom_ball/data/
MMLISTDIR		= src/fielddata/mm_list/
DPTITLEDIR 		= src/demo/title/
TRAIDIR 		= src/battle/tr_ai/
ARCDIR			= src/arc/
POKEZUKANDIR	= src/poketool/
POKEANMTBLDIR	= src/poketool/pokeanm/
ZONEDATADIR		= src/fielddata/maptable/
FLDTRADEDIR		= src/fielddata/pokemon_trade/
EGGDATADIR		= src/demo/egg/data/
EGGPTDIR		= src/demo/egg/data/particle/
SHINKAPTDIR		= src/demo/shinka/data/particle/
INTRODIR		= src/demo/intro/
SYOUJYOUDIR		= src/demo/syoujyou/
BTOWERDIR		= src/battle/b_tower/

#----------------------------------------------------------------------------
#	�R���o�[�g�ΏۂɂȂ�Maya�f�[�^�̎w��
#----------------------------------------------------------------------------
include	make_g3_files

G3D_NSBMD = $(G3D_IMD:.imd=.nsbmd)
G3D_NSBMT = $(G3D_IMT:.imd=.nsbmt)
#G3D_NSBMTG = $(G3D_GROUND:.imd=.nsbmt)
G3D_NSBTX = $(G3D_TX_IMD:.imd=.nsbtx)
G3D_NSBCA = $(G3D_ICA:.ica=.nsbca)
G3D_NSBVA = $(G3D_IVA:.iva=.nsbva)
G3D_NSBMA = $(G3D_IMA:.ima=.nsbma)
G3D_NSBTP = $(G3D_ITP:.itp=.nsbtp)
G3D_NSBTA = $(G3D_ITA:.ita=.nsbta)

G3D_DATA = $(G3D_NSBMD) $(G3D_NSBTX) $(G3D_NSBCA) $(G3D_NSBVA) $(G3D_NSBMA) $(G3D_NSBTP) $(G3D_NSBTA) $(G3D_NSBMT) #$(G3D_NSBMTG)

G3D_TARGETS	=$(subst rsc/,,$(G3D_DATA))


#----------------------------------------------------------------------------
#	make�T�u�f�B���N�g���w��
#
#	SUBDIRS�̒�`���s���Ă���
#----------------------------------------------------------------------------
include sub_make_files


#----------------------------------------------------------------------------
#	�R���p�C���Ώۃ\�[�X�t�@�C���w��
#
#	SRCS��SRCS_OVERLAYFILES�̒�`���s���Ă���
#----------------------------------------------------------------------------
include	make_prog_files
include overlay_files

#----------------------------------------------------------------------------
#	�����Ɋ܂܂��t�@�C���̎w��
#----------------------------------------------------------------------------
FILE_TREE	= $(DATABIN)*.* \
			  $(SOUNDDIR)sound_data.sdat \
			  $(MSGDATA_FILEPATH) \
			  $(DATASCENARIO)*.narc \
			  $(POKEGRADIR)*.narc \
			  $(TRGRADIR)*.narc \
			  $(PERSONALDIR)personal.narc \
			  $(EVOWOTDIR)evo.narc \
			  $(EVOWOTDIR)growtbl.narc \
			  $(EVOWOTDIR)pms.narc \
			  $(EVOWOTDIR)wotbl.narc \
			  $(TRAINERDIR)*.narc \
			  $(TRMSGDIR)*.narc \
			  $(BATTLEGRADIR)*.narc \
			  $(WAZAEFFDIR)we.arc \
			  $(WAZAEFFDIR)we_sub.narc \
			  $(WAZASEQDIR)*.narc \
			  $(WAZAEFFCLACTDIR)*.narc \
			  $(WAZATBLDIR)*.narc \
			  $(SCRIPTDIR)*.narc \
			  $(GRAPHICDIR)*.narc \
			  $(ITEMDATADIR)*.narc \
			  $(POKEICONGRADIR)*.narc \
			  $(POKEFOOTGRADIR)pokefoot.narc \
			  $(MMODELDIR)mmodel.narc \
			  $(MMODELDIR)fldeff.narc \
			  $(EFFECTDATADIR)*.narc \
			  $(SAMPLEDATADIR)*.narc \
			  $(EVENTDIR)*.narc \
			  $(ENCOUNTDIR)d_enc_data.narc \
			  $(ENCOUNTDIR)p_enc_data.narc \
			  $(BUILDMODELDIR)*.narc \
			  $(BUILDMODELDIR)*.dat \
			  $(MAPMATRIXDIR)*.narc \
			  $(AREADATADIR)*.narc \
			  $(AREABUILDMDLDIR)*.narc \
			  $(AREAMAPTEXDIR)*.narc \
			  $(AREAMOVEMDLDIR)*.narc \
			  $(FIELDMAPDIR)*.narc \
			  $(CONTESTGRADIR)*.narc \
			  $(CONTESTDATADIR)*.narc \
			  $(PARTICLEDATADIR)*.narc \
			  $(ZUKANDATADIR)zukan_data.narc \
			  $(WIFIEARTHDIR)*.narc \
			  $(DPTITLEDIR)titledemo.narc \
			  $(CBDATADIR)cb_data.narc \
			  $(EGGDATADIR)egg_data.narc \
			  $(EGGPTDIR)egg_demo_particle.narc \
			  $(MMLISTDIR)move_model_list.narc \
			  $(POKEANIMEDIR)poke_anm.narc \
			  $(TRAIDIR)tr_ai_seq.narc \
			  $(ARCDIR)*.narc \
			  $(ZONEDATADIR)mapname.bin \
			  $(POKEZUKANDIR)pokezukan.narc \
			  $(POKEZUKANDIR)shinzukan.narc \
			  $(POKEANMTBLDIR)pokeanm.narc \
			  $(FLDTRADEDIR)fld_trade.narc \
			  $(SHINKAPTDIR)shinka_demo_particle.narc \
			  $(INTRODIR)*.narc \
			  $(DPTITLEDIR)op_demo.narc \
			  $(SYOUJYOUDIR)syoujyou.narc \
			  $(BTOWERDIR)*.narc \
			  $(ZUKANDATADIR)zukan_enc_diamond.narc \
			  $(ZUKANDATADIR)zukan_enc_pearl.narc

#�����t�@�C���V�X�e���̃��[�g�f�B���N�g���w��
MAKEROM_ROMROOT  = ./src/

MAKEROM_ROMFILES = $(subst src/,,$(FILE_TREE))

#----------------------------------------------------------------------------
#	make clean�ŏ�������t�@�C����ǉ�
#----------------------------------------------------------------------------
LDIRT_CLEAN	= $(G3D_TARGETS) $(MSGDATA_FILEPATH) \
			  $(wildcard $(DATABIN)*.nsbmt) $(wildcard $(DATABIN)*.nsbmd) \
			  $(wildcard $(DATABIN)*.nsbta) $(wildcard $(DATABIN)*.nsbtp) \
			  $(wildcard $(DATABIN)*.nsbtx) $(wildcard $(DATABIN)*.nsbma)


#----------------------------------------------------------------------------
#	�c�[���ւ̃p�X�w��
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#	���ʕϐ���`
#----------------------------------------------------------------------------
include commondefs.GF

#----------------------------------------------------------------------------
#	�R���p�C�����[����`
#----------------------------------------------------------------------------
include modulerules.GF


#----------------------------------------------------------------------------
#	WiFi��`
#----------------------------------------------------------------------------
#include	$(NITRODWC_ROOT)/build/buildtools/commondefs
#include	$(NITRODWC_ROOT)/build/buildtools/modulerules
include	$(NITROVCT_ROOT)/build/buildtools/commondefs
include	$(NITROVCT_ROOT)/build/buildtools/modulerules

################################################################################
#
#
#		�R���p�C�����[����`
#
#
################################################################################

do-build: precompile binData msgData $(TARGETS) 

binData: $(G3D_TARGETS)


#----------------------------------------------------------------------------
# precompile
#----------------------------------------------------------------------------
PRECOMPILE_SRC		 =	include/precompile/precompile.pch
PRECOMPILE_CC_MCH	 =	$(OBJDIR)/precompile_cc.mch
PRECOMPILE_CCFLAGS	:=	$(CCFLAGS)
CCFLAGS			+=	-prefix $(PRECOMPILE_CC_MCH)
ifeq	($(USERNAME),ohno)
CCFLAGS			+=	-msgstyle gcc
endif
#DEPENDDIR		 =	$(OBJDIR)

precompile: $(PRECOMPILE_CC_MCH)

#�o�[�W������`�t�@�C�����X�V���ꂽ��v���R���p�C���w�b�_���X�V����
$(PRECOMPILE_CC_MCH):	$(VER_FILE)

-include $(PRECOMPILE_CC_MCH).d
$(PRECOMPILE_CC_MCH):%_cc.mch:
		$(CC) $(PRECOMPILE_CCFLAGS) $(INCLUDES) $(PRECOMPILE_SRC) -MD -precompile $(PRECOMPILE_CC_MCH)
		$(MOVE_SRC_DEPEND)
		$(MV) $(DEPENDDIR)/$(*F).d $@.d
$(OBJS):  $(PRECOMPILE_CC_MCH)

CCFLAGS +=	-thumb
#----------------------------------------------------------------------------
# msgdata
#----------------------------------------------------------------------------
MSG_NAIX_COPYSCRIPT	= convert/message/naixcopy.pl
MSG_CONVERTDATA_DIR	= convert/message/data/

MSG_HEADERFILE_DIR	= include/msgdata/

msgData: $(MSGDATA_FILEPATH)

$(MSGDATA_FILEPATH): $(wildcard $(MSG_CONVERTDATA_DIR)*.dat)
	nnsarc -c -l -n -i $(MSGDATA_FILENAME) $(MSG_CONVERTDATA_DIR)*.dat
	$(MV) $(MSGDATA_FILENAME) $(MSGDATA_FILEPATH)
	perl $(MSG_NAIX_COPYSCRIPT)  msg.naix $(MSG_HEADERFILE_DIR)msg.naix
	-$(RM) msg.naix

#----------------------------------------------------------------------------
#	makefile���C���N���[�h����t�@�C�����X�V���ꂽ��makelcf�����삷��悤�ɂ���
#----------------------------------------------------------------------------
$(MAKEFILE):	commondefs.GF modulerules.GF make_prog_files make_g3_files main.lsf overlay_files overlaytool.rb
	-$(RM) $(BINDIR)/$(LCFILE_SPEC:.lsf=.*)
	ruby overlaytool.rb
	touch $(MAKEFILE)

#----------------------------------------------------------------------------
#	�\�[�X�̗ނ��P�ł�builddate.c���V�����ꍇbuilddate.c��touch&�R���p�C��
#----------------------------------------------------------------------------
./src/system/builddate.c: $(SRCS) $(SRCS_OVERLAY)
	touch ./src/system/builddate.c


#----------------------------------------------------------------------------
#	�Z���A�N�^�[�w�b�_�[���̃A�[�J�C�u�t�@�C��ID��
#	arc_tool.dat���̃A�[�J�C�u�t�@�C��ID�����ꂳ��Ă��邩���`�F�b�N����
#	perl�����s����
#----------------------------------------------------------------------------
#clact_arcfile_check:
#	perl src/data/clact_util/clact_check.pl

#----------------------------------------------------------------------------
#	�����R���p�C��
#
#	builddate.c��touch���ăR���p�C�����Ă���
#----------------------------------------------------------------------------
force:
	touch ./src/system/builddate.c
	$(MAKE)

#----------------------------------------------------------------------------
#	�\�[�X�݂̂̃��R���p�C��
#----------------------------------------------------------------------------
source:
	-$(RM) $(GDIRT_CLEAN)
	-$(RM) $(DEPENDDIR)/*.d
	$(MAKE)

#----------------------------------------------------------------------------
#	����Makefile�Ǌ����̃��f�����O�f�[�^���R���p�C��
#----------------------------------------------------------------------------
model:
	-$(RM)	$(G3D_TARGETS) \
		  	$(wildcard $(DATABIN)*.nsbmt) $(wildcard $(DATABIN)*.nsbmd) \
			$(wildcard $(DATABIN)*.nsbta) $(wildcard $(DATABIN)*.nsbtp) \
			$(wildcard $(DATABIN)*.nsbtx) $(wildcard $(DATABIN)*.nsbma)
	-$(RM)	$(wildcard $(FIELDMAPDIR)/land_nsbmt/*.nsbmt) \
			$(FIELDMAPDIR)land_data.narc
	$(MAKE) model -C $(BUILDMODELDIR)

#----------------------------------------------------------------------------
#	�n�`�f�[�^�̃��f�����O�f�[�^���R���p�C��
#----------------------------------------------------------------------------
land:
	-$(RM)	$(wildcard $(FIELDMAPDIR)/land_nsbmt/*.nsbmt) \
			$(FIELDMAPDIR)land_data.narc
	$(MAKE) imdconv -C $(FIELDMAPDIR)
	$(MAKE) force

landall:
	-$(RM)	$(wildcard $(FIELDMAPDIR)/land_nsbmt/*.nsbmt) \
			$(FIELDMAPDIR)land_data.narc
	-$(MAKE) imdconv -C $(FIELDMAPDIR)
	-$(MAKE) ctex

#----------------------------------------------------------------------------
#	Build���f���݂̂̃��R���p�C��
#----------------------------------------------------------------------------
#src/fielddata/build_model/make all
bmall:
	$(MAKE) -C $(BUILDMODELDIR) clean all
	$(MAKE) force

#src/fielddata/build_model/make model 
bimd:
	$(MAKE) model -C $(BUILDMODELDIR)
	$(MAKE) force

#src/fielddata/build_model/make 
bm:
	$(MAKE) -C $(BUILDMODELDIR)
	$(MAKE) force

#src/fielddata/areadata/area_build_model/make all
abmall:
	$(MAKE) -C $(AREABUILDMDLDIR) clean all
	$(MAKE) force

#src/fielddata/areadata/area_build_model/make
abm:
	$(MAKE) -C $(AREABUILDMDLDIR)
	$(MAKE) force

#src/data/clact_util/make
clact:
	$(MAKE) -C $(CLACTUTILDIR)
	$(MAKE) force

#src/data/clact_util/make clean
clact_clean:
	$(MAKE) -C $(CLACTUTILDIR) clean

#----------------------------------------------------------------------------
# 	�n�`�`�b�v�e�N�X�`�����R���p�C��	
#----------------------------------------------------------------------------
ctex:
	$(MAKE) -C $(AREAMAPTEXDIR) clean all
	$(MAKE) force

#----------------------------------------------------------------------------
#	�o�C�i����r
#----------------------------------------------------------------------------
diff:
	cp ./bin/ARM9-TS/Release/main.srl ./bin/ARM9-TS/Release/old.srl
	$(MAKE) do-build
	$(MAKE) onlydiff

onlydiff:
	fc /b .\\bin\\ARM9-TS\\Release\\main.srl .\\bin\\ARM9-TS\\Release\\old.srl

#�ꎞ�R�}���h04/04 iwasawa ��ŏ����܂�
del_land_list:
	$(RM) $(FIELDMAPDIR)land_list

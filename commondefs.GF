#警告がたくさん出るのを抑止
CCFLAGS_WARNING = -w all,nocmdline,noerr,nopragmas,noempty,nopossible,nounused,noextracomma,nopedantic,nohidevirtual,noimplicit,noimpl_int2float,nonotinlined,unlargeargs,nostructclass,nopadding,nonotused,nounusedexpr,noptrintconv,noanyptrintconv,nofilecaps,nosysfilecaps,notokenpasting

ifeq	($(PM_DEBUG),yes)
MACRO_FLAGS += -DDEBUG_ONLY_FOR_$(USERNAME)
endif

#ソースファイルが存在するディレクトリのヘッダファイルを参照に行く
LINCLUDES	+= $(dir $<)

NITRO_LIBS		?= libfx$(NITRO_LIBSUFFIX).a		\
			   libgx$(NITRO_LIBSUFFIX).a 		\
			   libos$(TS_VERSION)$(NITRO_LIBSUFFIX).a \
			   libmi$(NITRO_LIBSUFFIX).a		\
			   libsnd$(NITRO_LIBSUFFIX).a		\
			   libpxi$(NITRO_LIBSUFFIX).a		\
			   libext$(NITRO_LIBSUFFIX).a		\
			   libfs$(NITRO_LIBSUFFIX).a		\
			   libdgt$(NITRO_LIBSUFFIX).a		\
			   libcp$(NITRO_LIBSUFFIX).a		\
			   libspi$(TS_VERSION)$(NITRO_LIBSUFFIX).a \
			   librtc$(NITRO_LIBSUFFIX).a		\
			   libprc$(NITRO_LIBSUFFIX).a		\
			   libcard$(NITRO_LIBSUFFIX).a		\
			   libwm$(NITRO_LIBSUFFIX).a		\
			   libwbt$(NITRO_LIBSUFFIX).a		\
			   libctrdg$(NITRO_LIBSUFFIX).a		\
			   libmath$(NITRO_LIBSUFFIX).a		\
			   libcht$(NITRO_LIBSUFFIX).a		\
			   libstd$(NITRO_LIBSUFFIX).a		\
			   libenv$(NITRO_LIBSUFFIX).a		\
			   $(notdir $(LIBSYSCALL_))		\
			   $(CRT0_O)

#基本となる任天堂製の変数定義ファイルをインクルード
include $(NITROSYSTEM_ROOT)/build/buildtools/commondefs

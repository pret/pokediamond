##-----------------------------------------------------------------------------
#**
#*			図鑑分布図用データ作成メイクファイル
#			作成後に必要なファイルを上の階層にコピーする
#**
##-----------------------------------------------------------------------------

SUBDIRS		=

#コピーしてくるディレクトリ
MAP_MATRIX_XLS_DIR	= ..\\..\\..\\..\\fielddata\\mapmatrix\\
MSGCNV2_DIC_DIR		= ..\\..\\..\\..\\fielddata\\encountdata\\
ENCDATA_EX_DIR		= ..\\..\\..\\..\\fielddata\\encdata_ex\\
MONSNO_H_DIR		= ..\\..\\..\\..\\..\\include\\poketool\\
ZONEID_H_DIR		= ..\\..\\..\\..\\fielddata\\maptable\\
CP_SCR_DIR 			= q:\\pokegra\\
PMDPENCOUNT_CSV_DIR	= ..\\..\\..\\..\\fielddata\\encountdata\\
GMM_CPY_DIR			= ..\\..\\..\\..\\..\\convert\\message\\src\\
GMM_TMP_DIR			= ..\\..\\..\\..\\..\\convert\\message\\
ZUKAN_DIR			= ..\\..\\
ZUKAN_DATA_DIR		= ..\\
ZUKAN_INCLUDE_DIR	= ..\\..\\..\\..\\..\\include\\application\\zukanlist\\

#エンカウントデータファイル名
ENC_DATA_FILE_DIAMOND	= PMDencount.csv
ENC_DATA_FILE_PEARL		= PMPencount.csv

#コピー先
CPY_DIR	= .

#dat_file
DAT_FILE := $(wildcard *.dat) 

#依存するファイル
MAKE_FILE	= map_matrix.xls \
			  monsno.h \
			  msgcnv2.dic \
			  poke_danzyon.xls \
			  zone_id.h \
 			  encdata_ex.xls

#図鑑ﾃﾞｰﾀコンバート依存
ZKN_MAKE_FILE = pokezukan.txt \
				zukan_data.xls	


include	$(NITROSDK_ROOT)/build/buildtools/commondefs.cctype.CW
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs

#Makeで生成される*.bin/*.narcはmake cleanの削除対象にする
LDIRT_CLEAN	= $(wildcard *.narc) \
			  zkn_rangeid.h \
			  zkn_comment_00.gmm
			  

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules


do-build:file_cp zukan_data.narc zukan_enc_diamond.narc zukan_enc_pearl.narc make_file_copy

#ファイルコピー
file_cp:
	xcopy /d /y $(MAP_MATRIX_XLS_DIR)map_matrix.xls $(CPY_DIR)
	xcopy /d /y $(MSGCNV2_DIC_DIR)msgcnv2.dic $(CPY_DIR)
	xcopy /d /y $(PMDPENCOUNT_CSV_DIR)$(ENC_DATA_FILE_DIAMOND) $(CPY_DIR)	#ダイヤ
	xcopy /d /y $(PMDPENCOUNT_CSV_DIR)$(ENC_DATA_FILE_PEARL) $(CPY_DIR)	#　パール
	xcopy /d /y $(MONSNO_H_DIR)monsno.h $(CPY_DIR)
	xcopy /d /y $(ZONEID_H_DIR)zone_id.h $(CPY_DIR)
	xcopy /d /y $(CP_SCR_DIR)pokezukan.txt $(CPY_DIR)
	xcopy /d /y $(ENCDATA_EX_DIR)encdata_ex.xls $(CPY_DIR)

#図鑑データコンバート
zukan_data.narc:$(ZKN_MAKE_FILE)
#	perl	pokezukan_tamago_cut.pl		#タマゴについての行を破棄
	zkn_excel_cnv.exe zukan_data.xls
	#メッセージﾃﾞｰﾀコンバート
	MessageEditor -nw -s zkn_comment_00.gmm -i $(GMM_TMP_DIR)template.gmt zkn_comment_00.gmm 
	MessageEditor -nw -s zkn_comment_01.gmm -i $(GMM_TMP_DIR)template.gmt zkn_comment_01.gmm 
#	MessageEditor -nw -s zkn_comment_02.gmm -i $(GMM_TMP_DIR)template.gmt zkn_comment_02.gmm 
	MessageEditor -nw -s zkn_gram.gmm -i $(GMM_TMP_DIR)template.gmt zkn_gram.gmm 
	MessageEditor -nw -s zkn_height.gmm -i $(GMM_TMP_DIR)template.gmt zkn_height.gmm 
	MessageEditor -nw -s zkn_type.gmm -i $(GMM_TMP_DIR)template.gmt zkn_type.gmm 
	MessageEditor -nw -s zkn_worldname.gmm -i $(GMM_TMP_DIR)template.gmt zkn_worldname.gmm
#	MessageEditor -nw -s zkn_worldtype.gmm -i $(GMM_TMP_DIR)template.gmt zkn_worldtype.gmm
	#外国語ﾃﾞｰﾀソースコピー
	cp zkn_worldtext.c $(ZUKAN_DIR)
	cp zkn_worldtext.h $(ZUKAN_DIR)
	#形IDヘッダ
	cp zkn_form_id.h $(ZUKAN_DATA_DIR)
	#GMMコピー
	cp zkn_comment_00.gmm $(GMM_CPY_DIR)
	cp zkn_comment_01.gmm $(GMM_CPY_DIR)
#	cp zkn_comment_02.gmm $(GMM_CPY_DIR)
	cp zkn_gram.gmm $(GMM_CPY_DIR)
	cp zkn_height.gmm $(GMM_CPY_DIR)
	cp zkn_type.gmm $(GMM_CPY_DIR)
	cp zkn_worldname.gmm $(GMM_CPY_DIR)
#	cp zkn_worldtype.gmm $(GMM_CPY_DIR)
	cp zkn_sort_akstnhmyrw_idx.h $(ZUKAN_INCLUDE_DIR)

	#アーカイブ
	nnsarc -c -i -n zukan_data.narc -S zkn_arc_list.lst

	
#分布ﾃﾞｰﾀ作成
zukan_enc_diamond.narc:$(MAKE_FILE) $(ENC_DATA_FILE_DIAMOND)
	#ダイヤ
	perl range_data_morning_make.pl $(ENC_DATA_FILE_DIAMOND)
	perl range_data_noon_make.pl $(ENC_DATA_FILE_DIAMOND)
	perl range_data_night_make.pl $(ENC_DATA_FILE_DIAMOND)
	perl range_data_special_make.pl	DIAMOND $(ENC_DATA_FILE_DIAMOND)
	perl range_data_special_zukan_conp_make.pl DIAMOND $(ENC_DATA_FILE_DIAMOND)
	nnsarc -c -i -n zukan_enc_diamond.narc -S zkn_arc_enc.lst

zukan_enc_pearl.narc:$(MAKE_FILE) $(ENC_DATA_FILE_PEARL)
	#パール
	perl range_data_morning_make.pl $(ENC_DATA_FILE_PEARL)
	perl range_data_noon_make.pl $(ENC_DATA_FILE_PEARL)
	perl range_data_night_make.pl $(ENC_DATA_FILE_PEARL)
	perl range_data_special_make.pl	PEARL $(ENC_DATA_FILE_PEARL)
	perl range_data_special_zukan_conp_make.pl PEARL $(ENC_DATA_FILE_PEARL)
	nnsarc -c -i -n zukan_enc_pearl.narc -S zkn_arc_enc.lst

make_file_copy:
	#ファイルを上位にコピー
	cp *.narc ../
	cp *.naix ../
	cp zkn_rangeid.h ../
	cp zkn_hidemap.dat ../

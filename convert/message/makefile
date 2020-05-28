##########################################################
#	メッセージデータコンバート
##########################################################

RESOURCE_LIST	= resource.list
DEPEND_LIST	= depend.list
TARGET_LIST	= target.list
DATA_DIR	= data
HEADER_DIR	= ../../include/msgdata
VERSION_FILE	= ../../version


-include $(TARGET_LIST)
-include $(VERSION_FILE)


##########################################################
#	動作部分
##########################################################
.SUFFIXES: .dat .gmm

no-rule:
	$(MAKE)	depend
	$(MAKE)	datfiles


#=========================================================
#	dat を作成
#=========================================================
datfiles: $(TARGETS)
#	perl msgconv.pl $< $(PM_LANG)


#=========================================================
#	clean
#=========================================================
clean:
	-rm $(DATA_DIR)/*.dat
	-rm $(HEADER_DIR)/*.h

#=========================================================
#	depend
#=========================================================
depend:
	$(shell find src|grep gmm$$ > $(RESOURCE_LIST)) 
	perl  makedepend.pl $(RESOURCE_LIST) $(DATA_DIR) $(DEPEND_LIST) $(TARGET_LIST) $(PM_LANG)
	rm $(RESOURCE_LIST)


-include $(DEPEND_LIST)


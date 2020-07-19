#todo data/dp_areawindow.NCGR (weirdness with size)
#todo data/graphic/bag_gra/narc_0007.NCGR (SOPC section) (width 32, palette narc_0003.NCLR)
#todo poketool/trgra/trbgra (unknown compression)

CLOBBER_SIZE_NCGR_FILES := files/data/cell0.NCGR

CLOBBER_SIZE_VERSION101_NCGR_FILES := files/graphic/bag_gra/narc_0002.NCGR \
                                      files/graphic/bag_gra/narc_0006.NCGR \
                                      files/graphic/bag_gra/narc_0034.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0002.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0004.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0006.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0008.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0010.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0012.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0014.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0016.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0018.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0020.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0021.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0023.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0024.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0026.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0030.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0033.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0038.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0040.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0041.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0043.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0045.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0047.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0049.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0051.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0053.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0056.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0058.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0063.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0065.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0071.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0073.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0076.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0078.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0083.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0085.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0090.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0092.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0095.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0100.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0105.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0107.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0109.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0112.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0115.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0117.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0119.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0121.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0123.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0125.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0127.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0128.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0130.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0132.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0133.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0135.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0136.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0138.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0140.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0142.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0144.NCGR \
                                      files/itemtool/itemdata/item_icon/narc_0146.NCGR

4BPP_NCLR_FILES := files/demo/title/titledemo/narc_0016.NCLR

IR_NCLR_FILES := files/itemtool/itemdata/item_icon/narc_0028.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0029.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0032.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0035.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0036.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0037.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0055.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0060.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0061.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0062.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0067.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0068.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0069.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0070.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0075.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0080.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0081.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0082.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0087.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0088.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0089.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0094.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0097.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0098.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0099.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0102.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0103.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0104.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0111.NCLR \
                 files/itemtool/itemdata/item_icon/narc_0114.NCLR

VERSION101_SOPC_8BPP_NCGR_FILES := files/demo/title/titledemo/narc_0001.NCGR \
                                   files/demo/title/titledemo/narc_0003.NCGR

VERSION101_SOPC_NCGR_FILES := files/demo/title/titledemo/narc_0007.NCGR \
                              files/demo/title/titledemo/narc_0011.NCGR \
                              files/demo/title/titledemo/narc_0015.NCGR

8BPP_COMP10_NOPAD_NCLR_FILES := files/poketool/trgra/trbgra/narc_0000.NCLR \
                                files/poketool/trgra/trbgra/narc_0002.NCLR \
                                files/poketool/trgra/trbgra/narc_0004.NCLR \
                                files/poketool/trgra/trbgra/narc_0006.NCLR \
                                files/poketool/trgra/trbgra/narc_0008.NCLR \
                                files/poketool/trgra/trbgra/narc_0010.NCLR \
                                files/poketool/trgra/trbgra/narc_0012.NCLR \
                                files/poketool/trgra/trbgra/narc_0014.NCLR

SCANNED_NCGR_FILES := files/poketool/trgra/trbgra/narc_0000.NCGR \
                      files/poketool/trgra/trbgra/narc_0002.NCGR \
                      files/poketool/trgra/trbgra/narc_0004.NCGR \
                      files/poketool/trgra/trbgra/narc_0006.NCGR \
                      files/poketool/trgra/trbgra/narc_0008.NCGR \
                      files/poketool/trgra/trbgra/narc_0010.NCGR \
                      files/poketool/trgra/trbgra/narc_0012.NCGR \
                      files/poketool/trgra/trbgra/narc_0014.NCGR

NCGR_CLEAN_LIST := files/data/cell0.NCGR \
                   files/demo/title/titledemo/narc_0001.NCGR \
                   files/demo/title/titledemo/narc_0003.NCGR \
                   files/demo/title/titledemo/narc_0007.NCGR \
                   files/demo/title/titledemo/narc_0011.NCGR \
                   files/demo/title/titledemo/narc_0015.NCGR \
                   files/graphic/bag_gra/narc_0002.NCGR \
                   files/graphic/bag_gra/narc_0006.NCGR \
                   files/graphic/bag_gra/narc_0034.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0002.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0004.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0006.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0008.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0010.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0012.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0014.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0016.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0018.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0020.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0021.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0023.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0024.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0026.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0030.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0033.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0038.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0040.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0041.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0043.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0045.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0047.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0049.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0051.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0053.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0056.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0058.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0063.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0065.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0071.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0073.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0076.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0078.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0083.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0085.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0090.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0092.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0095.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0100.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0105.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0107.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0109.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0112.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0115.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0117.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0119.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0121.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0123.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0125.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0127.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0128.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0130.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0132.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0133.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0135.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0136.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0138.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0140.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0142.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0144.NCGR \
                   files/itemtool/itemdata/item_icon/narc_0146.NCGR \
                   files/poketool/trgra/trbgra/narc_0000.NCGR \
                   files/poketool/trgra/trbgra/narc_0002.NCGR \
                   files/poketool/trgra/trbgra/narc_0004.NCGR \
                   files/poketool/trgra/trbgra/narc_0006.NCGR \
                   files/poketool/trgra/trbgra/narc_0008.NCGR \
                   files/poketool/trgra/trbgra/narc_0010.NCGR \
                   files/poketool/trgra/trbgra/narc_0012.NCGR \
                   files/poketool/trgra/trbgra/narc_0014.NCGR


NCLR_CLEAN_LIST := files/data/cell0.NCLR \
                   files/demo/title/titledemo/narc_0001.NCLR \
                   files/demo/title/titledemo/narc_0003.NCLR \
                   files/demo/title/titledemo/narc_0009.NCLR \
                   files/demo/title/titledemo/narc_0010.NCLR \
                   files/demo/title/titledemo/narc_0013.NCLR \
                   files/demo/title/titledemo/narc_0014.NCLR \
                   files/demo/title/titledemo/narc_0016.NCLR \
                   files/graphic/bag_gra/narc_0003.NCLR \
                   files/graphic/bag_gra/narc_0034.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0002.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0004.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0006.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0008.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0010.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0012.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0014.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0016.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0018.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0022.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0025.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0027.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0028.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0029.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0031.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0032.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0034.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0035.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0036.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0037.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0038.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0042.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0043.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0045.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0047.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0049.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0052.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0053.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0055.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0056.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0059.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0060.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0061.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0062.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0063.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0066.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0067.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0068.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0069.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0070.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0071.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0074.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0075.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0076.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0079.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0080.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0081.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0082.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0083.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0086.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0087.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0088.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0089.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0090.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0092.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0094.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0095.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0097.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0098.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0099.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0101.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0102.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0103.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0104.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0105.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0107.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0110.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0111.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0112.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0114.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0115.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0117.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0119.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0121.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0123.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0125.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0129.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0131.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0134.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0136.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0138.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0140.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0142.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0144.NCLR \
                   files/itemtool/itemdata/item_icon/narc_0146.NCLR \
                   files/poketool/trgra/trbgra/narc_0000.NCLR \
                   files/poketool/trgra/trbgra/narc_0002.NCLR \
                   files/poketool/trgra/trbgra/narc_0004.NCLR \
                   files/poketool/trgra/trbgra/narc_0006.NCLR \
                   files/poketool/trgra/trbgra/narc_0008.NCLR \
                   files/poketool/trgra/trbgra/narc_0010.NCLR \
                   files/poketool/trgra/trbgra/narc_0012.NCLR \
                   files/poketool/trgra/trbgra/narc_0014.NCLR

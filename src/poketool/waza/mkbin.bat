FOR /L %%I IN (0,1,9) DO copy /b wazatbl_00%%I.bin+conwaza_00%%I.bin wazadata_00%%I.bin
FOR /L %%I IN (10,1,99) DO copy /b wazatbl_0%%I.bin+conwaza_0%%I.bin wazadata_0%%I.bin
FOR /L %%I IN (100,1,500) DO copy /b wazatbl_%%I.bin+conwaza_%%I.bin wazadata_%%I.bin
nnsarc -c -l -n waza_tbl.narc wazadata_*.bin

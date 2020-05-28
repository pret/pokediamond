..\..\..\convert\exceltool\exceltabconv fld_item.xls
copy fld_item.ev tmp
awk -f fld_item.awk fld_item.txt
awk -f fld_item2.awk fld_item.txt
awk -f scr_copy.awk tmp >> fld_item.ev
awk -f ev_def.awk fld_item.ev
del tmp

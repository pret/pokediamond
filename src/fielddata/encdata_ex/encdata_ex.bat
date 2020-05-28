..\..\..\convert\exceltool\ExcelSeetConv -o safari_scope.csv -p 1 -s csv encdata_ex.xls
..\..\..\convert\exceltool\ExcelSeetConv -o honey_dia.csv -p 2 -s csv encdata_ex.xls
..\..\..\convert\exceltool\ExcelSeetConv -o honey_perl.csv -p 3 -s csv encdata_ex.xls
..\..\..\convert\exceltool\ExcelSeetConv -o safari.csv -p 4 -s csv encdata_ex.xls
..\..\..\convert\exceltool\ExcelSeetConv -o mnt.csv -p 5 -s csv encdata_ex.xls
..\..\..\convert\exceltool\ExcelSeetConv -o fish.csv -p 6 -s csv encdata_ex.xls
..\..\..\convert\exceltool\ExcelSeetConv -o honey_tree.csv -p 7 -s csv encdata_ex.xls
ruby mk_pokename_txt.rb
pokemon_name.exe honey_dia_nrm honey_dia_nrm.txt
pokemon_name.exe honey_dia_rare honey_dia_rare.txt
pokemon_name.exe honey_dia_s_rare honey_dia_s_rare.txt
pokemon_name.exe honey_perl_nrm honey_perl_nrm.txt
pokemon_name.exe honey_perl_rare honey_perl_rare.txt
pokemon_name.exe honey_perl_s_rare honey_perl_s_rare.txt
pokemon_name.exe safari_bef safari_bef.txt
pokemon_name.exe safari_af safari_af.txt
pokemon_name.exe mnt_bef mnt_bef.txt
pokemon_name.exe mnt_af mnt_af.txt
pokemon_name.exe fish fish.txt
ruby ss.rb
ruby mkbin.rb
ruby fishing_point.rb
nnsarc -i -c -l -n encdata_ex.narc bin/*.bin > arc_result.txt
mv encdata_ex.narc ../../arc/encdata_ex.narc
mv encdata_ex.naix ../../arc/encdata_ex.naix


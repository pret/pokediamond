#サファリ望遠鏡座標一覧作成
ss = open("bin/safari_scope.bin","w")
ss_csv_file = open("safari_scope.csv","r")

line = ss_csv_file.gets    ## 1行読み飛ばし
line = ss_csv_file.gets    ## 1行読み飛ばし

while line = ss_csv_file.gets
	column = line.split ","
	if column[7] == nil then
		printf("data_nothing\n")
		break
	end
	if line =~/^#END/ then
		printf("data_end\n")
		break
	end
	x = 32 + column[7].to_i
	ary = Array(x)
	pack_str = ary.pack("S*")
	ss.write(pack_str)

	z = 32 + column[10].to_i
	ary = Array(z)
	pack_str = ary.pack("S*")
	ss.write(pack_str)
end

printf("convert_end\n")

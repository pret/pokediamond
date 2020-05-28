#ランダムの種魚釣りポイントデータ作成
#マップマトリックスの横幅が1のとき専用の処理です

def make_data(inFile, d_ary, w_ary,block_ofs)
	idx_ary = Array.new(0)
	water = 0
	cnt = 0
	while cnt<32*32
		#下位1バイト読む
		data = inFile.read(1)
		#水アトリビュートかチェック
		attr_str_ary = data.unpack("B8")
		attr_str = attr_str_ary.shift
		attr_str.insert(0,"0b")
		attr = attr_str.to_i(0)
		if attr == 21 then
			idx_ary << (cnt+(32*32*block_ofs))
			#水ならばカウントアップ
			water = water+1
		end
		#上位１バイト読む(解釈はしない)
		data = inFile.read(1)
		cnt = cnt+1
	end
	p water
	w_ary << water

	d_ary << idx_ary
#	ary = Array(water)
#	outFile.write(ary.pack("i*"))

#	idx_ary.each {|x|
#		ary = Array(x)
#		outFile.write(ary.pack("S*"))
#		 }
	
end

fish_point = open("bin/fishing_point.bin","wb")
fish_csv = open("fish.csv","r")
## ポケモン名のところは読み飛ばす
while line = fish_csv.gets
	if line =~/^#END/ then
		break
	end
end	#while

line = fish_csv.gets    ## 1行読み飛ばし
#読むファイル数をライト
line = fish_csv.gets
column = line.split ","
file_num = column[0].chomp
ary = Array(file_num.to_i)

fish_point.write(ary.pack("i*"))

data_ary = Array.new(0)
water_num_ary = Array.new(0)
ofs = 0
while line = fish_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[0].chomp
	path = "../../data/fld_map_data/" + name
	#ファイル開く
	p path
	bin_file = open(path,"rb")

	make_data(bin_file, data_ary,water_num_ary,ofs)
	ofs = ofs+1
end	#while

	water_num_ary.each {|x|
		ary = Array(x)
		fish_point.write(ary.pack("i*"))
		 }

	data_ary.each {|a|
		a.each{ |n|
			ary = Array(n)
			fish_point.write(ary.pack("S*"))
		}
	}




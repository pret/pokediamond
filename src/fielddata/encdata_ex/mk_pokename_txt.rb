#蜜塗りエンカウント(ダイヤ)ポケモン名リスト（通常）
#蜜塗りエンカウント(ダイヤ)ポケモン名リスト（レア）
#蜜塗りエンカウント(ダイヤ)ポケモン名リスト（激レア）
honey_dia_nrm = open("honey_dia_nrm","w")
honey_dia_rare = open("honey_dia_rare","w")
honey_dia_s_rare = open("honey_dia_s_rare","w")
honey_dia_csv = open("honey_dia.csv","r")
line = honey_dia_csv.gets    ## 1行読み飛ばし
line = honey_dia_csv.gets    ## 1行読み飛ばし
while line = honey_dia_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[1].chomp
	honey_dia_nrm.puts("#{name}")		#通常
	name = column[2].chomp
	honey_dia_rare.puts("#{name}")		#レア
	name = column[3].chomp
	honey_dia_s_rare.puts("#{name}")	#激レア
end	#while

#蜜塗りエンカウント(パール)ポケモン名リスト（通常）
#蜜塗りエンカウント(パール)ポケモン名リスト（レア）
#蜜塗りエンカウント(パール)ポケモン名リスト（激レア）
honey_perl_nrm = open("honey_perl_nrm","w")
honey_perl_rare = open("honey_perl_rare","w")
honey_perl_s_rare = open("honey_perl_s_rare","w")
honey_perl_csv = open("honey_perl.csv","r")
line = honey_perl_csv.gets    ## 1行読み飛ばし
line = honey_perl_csv.gets    ## 1行読み飛ばし
while line = honey_perl_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[1].chomp
	honey_perl_nrm.puts("#{name}")		#通常
	name = column[2].chomp
	honey_perl_rare.puts("#{name}")		#レア
	name = column[3].chomp
	honey_perl_s_rare.puts("#{name}")	#激レア
end	#while

#湿原エンカウントポケモン名リスト（全国図鑑入手前）
#湿原エンカウントポケモン名リスト（全国図鑑入手後）
safari_bef = open("safari_bef","w")
safari_af = open("safari_af","w")
safari_csv = open("safari.csv","r")
line = safari_csv.gets    ## 1行読み飛ばし
line = safari_csv.gets    ## 1行読み飛ばし
while line = safari_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[0].chomp
	safari_bef.puts("#{name}")		#前
	name = column[1].chomp
	safari_af.puts("#{name}")		#後
end	#while

#裏山エンカウントポケモン名リスト（全国図鑑入手前）
#裏山エンカウントポケモン名リスト（全国図鑑入手後）
mnt_bef = open("mnt_bef","w")
mnt_af = open("mnt_af","w")
mnt_csv = open("mnt.csv","r")
line = mnt_csv.gets    ## 1行読み飛ばし
line = mnt_csv.gets    ## 1行読み飛ばし
while line = mnt_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[0].chomp
	mnt_bef.puts("#{name}")	#前
	name = column[1].chomp
	mnt_af.puts("#{name}")		#後
end	#while

#ランダムの種釣りエンカウントポケモン名リスト
fish = open("fish","w")
fish_csv = open("fish.csv","r")
line = fish_csv.gets    ## 1行読み飛ばし
line = fish_csv.gets    ## 1行読み飛ばし
while line = fish_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[0].chomp
	fish.puts("#{name}")
end	#while


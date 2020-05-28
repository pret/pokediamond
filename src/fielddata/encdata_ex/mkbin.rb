#モンスターナンバー定義を配列化

def make_bin(m_ary, op_txt, op_bin, debug_txt, debug_mes)
	txt = open(op_txt,"r")
	bin = open(op_bin,"wb")
	while line = txt.gets
		if line =~/^#END/ then
			break
		end
		name = line
		name.chomp!
		idx = m_ary.index(name)
		
		if idx == nil then
			p name + ":unknown"
			#デバッグテキストに記述
			debug_txt.printf("%s：%sは解析できません\n",debug_mes,name)
		else
			ary = Array(idx+1)
			pack_str = ary.pack("i*")
			bin.write(pack_str)
		end
	end	#while	
end

monsno_def = open("../../../include/poketool/monsno.h","r")

mons_ary = Array.new(0)
while line = monsno_def.gets
	if line =~/^#endif*/ then
		break
	end
	name = line.split "\t"
	if name[0] == "#define" then
#		p name[1]
		if name[1] != nil then
			mons_ary << name[1]
		end
	end
end	#while

#デバッグ用テキスト作成
debug = open("debug.txt","wb")

#ダイヤ蜜木のデータ作成（通常）
make_bin(mons_ary, "honey_dia_nrm.txt", "bin/honey_dia_nrm.bin", debug, "ダイヤ蜜通常")

#ダイヤ蜜木のデータ作成（レア）
make_bin(mons_ary, "honey_dia_rare.txt", "bin/honey_dia_rare.bin", debug, "ダイヤ蜜レア")

#ダイヤ蜜木のデータ作成（激レア）
make_bin(mons_ary, "honey_dia_s_rare.txt", "bin/honey_dia_s_rare.bin", debug, "ダイヤ蜜激レア")

#パール蜜木のデータ作成（通常）
make_bin(mons_ary, "honey_perl_nrm.txt", "bin/honey_perl_nrm.bin", debug, "パール蜜通常")

#パール蜜木のデータ作成（レア）
make_bin(mons_ary, "honey_perl_rare.txt", "bin/honey_perl_rare.bin", debug, "パール蜜レア")

#パール蜜木のデータ作成（激レア）
make_bin(mons_ary, "honey_perl_s_rare.txt", "bin/honey_perl_s_rare.bin", debug, "パール蜜激レア")

#サファリのデータ作成（全国図鑑前）
make_bin(mons_ary, "safari_bef.txt", "bin/safari_bef.bin", debug, "サファリ図鑑前")

#サファリのデータ作成（全国図鑑後）
make_bin(mons_ary, "safari_af.txt", "bin/safari_af.bin", debug, "サファリ図鑑後")

#裏山のデータ作成（全国図鑑前）
#make_bin(mons_ary, "mnt_bef.txt", "bin/mnt_bef.bin", debug, "裏山図鑑前")<<不要になった

#裏山のデータ作成（全国図鑑後）
make_bin(mons_ary, "mnt_af.txt", "bin/mnt_af.bin", debug, "裏山図鑑後")

#釣りのデータ作成
make_bin(mons_ary, "fish.txt", "bin/fish.bin", debug, "釣り")


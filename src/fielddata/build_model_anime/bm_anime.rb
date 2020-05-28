#アニメテーブル作成

#アニメ無しデータの書き込み
def set_none_anime_data(inAry, inStrID)
	inAry = Array(0xff)			#アニメしない
	str = inAry.pack("C*")
	inStrID.write(str)
	
	inAry = Array(0xff)			#アニメタイプ不明
	str = inAry.pack("C*")
	inStrID.write(str)

	inAry = Array(0)			#自殺しない
	str = inAry.pack("C*")
	inStrID.write(str)

	inAry = Array(0)			#4バイト境界ダミーセット
	str = inAry.pack("C*")
	inStrID.write(str)

	#アニメナンバーを書き込む4つまで
	for i in [0,1,2,3]
		inAry = Array(0xffffffff)		#コード無し
		str = inAry.pack("i*")
		inStrID.write(str)
	end
end

g3d_list = open("g3d_list","w")
anm_arc_list = open("anm_arc_list","w")
debug_txt = open("debug.txt","w")

anm_csv_file = open("bm_anm_tbl.csv","r")

line = anm_csv_file.gets    ## 1行読み飛ばし

anime_name_ary = Array.new(0)
anime_list_ary = Array.new(0)
while line = anm_csv_file.gets
	if line =~/^#END/ then
		break
	end

	column = line.split ","

	#アニメコード、アニメタイプ、自殺フラグ、アニメファイル名ｘ4を配列に格納
	anime_ary = [ column[1],column[2],column[3],column[4],column[5],column[6],column[7] ]
	anime_list_ary << anime_ary		#配列に格納
	for i in [0,1,2,3]
		if column[4+i] != "" then
			anime_name_ary << column[4+i]
		end
	end	#for
end	#while

#重複削除
anime_name_ary.uniq!
#g3dコンバーター用のリストを作成
g3d_ary = anime_name_ary
ica_ary = Array.new(0)
ita_ary = Array.new(0)
itp_ary = Array.new(0)

g3d_ary.each{|index|
	
	if index[/.ica/] != nil then
		ica_ary << index
	elsif index[/.ita/] != nil then
		ita_ary << index
	elsif index[/.itp/] != nil then
		itp_ary << index
	end
}

g3d_list.printf("G3D_ICA = \\\n");
ica_ary.each{|index|
	g3d_list.printf("\t$(DATASRC)/#{index} \\\n")
}
g3d_list.printf("\n");

g3d_list.printf("G3D_ITA = \\\n");
ita_ary.each{|index|
	g3d_list.printf("\t$(DATASRC)/#{index} \\\n")
}
g3d_list.printf("\n");

g3d_list.printf("G3D_ITP = \\\n");
itp_ary.each{|index|
	g3d_list.printf("\t$(DATASRC)/#{index} \\\n")
}

#アニメアーカイブスクリプトファイルの作成
arc_ary = anime_name_ary
arc_ary.each{|index|
	index.sub!(".ica", ".nsbca")
	index.sub!(".ita", ".nsbta")
	index.sub!(".itp", ".nsbtp")
	anm_arc_list.printf("\"g3d_anime_tmp/#{index}\"\n")
}

anm_csv_file.close


model_entry_ary = Array.new(0)
bm_anm_csv_file = open("bm_anime.csv","r")
line = bm_anm_csv_file.gets    ## 1行読み飛ばし
while line = bm_anm_csv_file.gets
	if line =~/^#END/ then
		break
	end
	
	column = line.split ","
	entry = [ column[1],column[2] ]
	model_entry_ary << entry
	p entry
end
bm_anm_csv_file.close


#アニメするモデリングデータ一覧をリード
#モデリングリスト一覧をリード
model_csv_file = open("build_model.csv","r")

#アニメリストアーカイブスクリプトファイル作成
anmlst_arc_list = open("anmlst_arc_list","w")

line = model_csv_file.gets    ## 1行読み飛ばし
while line = model_csv_file.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	
	strID = open("bin/#{column[2]}.bin","w")

	#スクリプトファイルに追記
	anmlst_arc_list.printf("\"bin/#{column[2]}.bin\"\n")

	ary = Array.new(0)

	if column[3] == "1" then
		#アニメフラグが立っている

		#ストリングＩＤがアニメリストにあるかをしらべる
		anm_itm = model_entry_ary.assoc(column[2])
#		p anm_itm
		if anm_itm != nil then
			#エントリリストがさす、アニメコードを検索
			anime = anime_list_ary.assoc(anm_itm[1])
			if anime != nil then
				#アニメフラグを立てる
				ary = Array(1)
				pack_str = ary.pack("C*")
				strID.write(pack_str)
			
				#アニメタイプを書き込む
				if anime[1] == "STATION" then
					ary = Array(0)
				elsif anime[1] == "SET_CON" then
					ary = Array(2)
				elsif anime[1] == "ALL_CON" then
					ary = Array(3)
				else
					#デバッグテキストに記入
					ary = Array(0xff)
					debug_txt.printf("#{anime[1]}:#{column[2]}のアニメーションタイプ指定が正しくありません\n")
				end
				pack_str = ary.pack("C*")
				strID.write(pack_str)
			
				#自殺フラグを書き込む
				ary = Array(anime[2].to_i)
				pack_str = ary.pack("C*")
				strID.write(pack_str)
				#4バイト境界のためのダミーデータを書き込む
				ary = Array(0)
				pack_str = ary.pack("C*")
				strID.write(pack_str)

				#アニメナンバーを書き込む4つまで
				for i in [0,1,2,3]
					anime_no = anime_name_ary.index(anime[3+i])
					if anime_no != nil then
						ary = Array(anime_no)
					else	
						ary = Array(0xffffffff)	#コード無し
					end
					pack_str = ary.pack("i*")
					strID.write(pack_str)
				end
			else
				if anm_itm[1] == "ANIME_NONE" then
					#アニメ無しとする
					set_none_anime_data(ary, strID)
					debug_txt.printf("#{column[2]}:アニメコード指定が正しくありません\n")
				else
					#判別できないアニメコードが指定されているので、デバッグテキストに記入
					#アニメ無しとする
					set_none_anime_data(ary, strID)
					debug_txt.printf("#{anm_itm[1]}:#{column[2]}のアニメコード指定が正しくありません\n")
				
				end
			end
		else 
			#アニメリストに無いので、アニメなしとみなす
			set_none_anime_data(ary, strID)
			debug_txt.printf("#{column[2]}:アニメリストに登録されていません\n")
		end
	else
		#アニメフラグが立っていない
		set_none_anime_data(ary, strID)
	end
	strID.close
end


DEFAULT_LSFFILE		= "default.lsf"
MAKE_PROG_FILE  	= "make_prog_files"
OUTPUT_LSFFILE  	= "main.lsf"
OUTPUT_OVERLAYFILES	= "overlay_files"
OUTPUT_OVERLAYTEXT  = "overlaymap.txt"

MATCH_KEYWORD	 = /\A#===>/			# 行頭が「#===>」
MATCH_LIB        = /^#LIB=>/            # ライブラリを含める場合
MATCH_OVERLAYSRC = /^SRCS_OVERLAY_.*/	# 行頭から「SRCS_OVERLAY_...」
MATCH_ENDSRC	 = /[\s\t].*\\\z/				# 行末が「\」
MATCH_ERROR      = /\\\s/

#デフォルトで読み込むファイル
default_lsf = File.read(DEFAULT_LSFFILE)


overlay_count        =  0
overlay_table_num    =  0
overlay_name         =  Array.new
overlay_name        << "main"
overlay_name        << "ITCM"
overlay_name        << "DTCM"

overlay_target       = Array.new
overlay_target      << "main"
overlay_target      << "ITCM"
overlay_target      << "DTCM"
source_name          = Array.new
lib_name          = Array.new
overlay_hash         = Hash.new
overlay_hash["main"] = 1
overlay_hash["ITCM"] = 1
overlay_hash["DTCM"] = 1
overlay_flag         = 0

line_get_flag     = 0

line_count        = 1

File.open(OUTPUT_LSFFILE,"w"){|file|
	file.puts(default_lsf)
	file.puts("#ここから下はoverlaytool.rbで自動生成されています\n\n")
}


#ターゲットになるソースコードの記述ファイルを１行ずつ処理
File.readlines(MAKE_PROG_FILE).each{ |line|
	line.chomp!

	#行末の「\」の後ろにスペースが入っていると誤動作するのでチェックする
	if line.match(MATCH_ERROR) then
		printf "%d行目： \\マークの後ろにスペースがはいっています。\n",line_count
		exit 1
	end
	line_count = line_count + 1


	#オーバーレイ定義の取得
	if line.match(MATCH_KEYWORD) then
		overlay_flag = 1
		m = MATCH_KEYWORD.match(line)
		_str = m.post_match.split(nil)[0].sub(/[\s\t]/,"")
		if overlay_hash.key?(_str) then
			overlay_target << _str
			overlay_count = overlay_count+1
		else
			printf "「%s」 というオーバーレイソ\ースは定義されていません\n",_str
			exit 1
		end
	end

	#「SRCS_OVERLAY」の後はソースコード行なので「\」がなくなるまで
	# 保存し続ける
	if line_get_flag==1 then
		if line.match(/[a-zA-Z_0-9]+\.[cs]/) then
			source_name << line
		end

		# 「\」が無い行がでてきたら終わりなので、取得終了
		# lsfファイルに書き込みを行う
		if line.match(MATCH_ENDSRC)==nil || line=="" then
#			p source_name
			line_get_flag = 0
			_count = 0
			File.open(OUTPUT_LSFFILE,"a"){|file|


				# 「SRCS_OVERLAY_???」からSRCS_OVERLAY_を削って小文字化した名前をオーバーレイ領域の
				# ターゲットにする。ただし、予約語として「main,ITCM,DTCM」という文字列が定義されているので
				# これらは避けるようにする
				_targetname = overlay_target[overlay_table_num+2]
				if _targetname != "main" && _targetname!="DTCM" && _targetname != "ITCM" then
					_targetname = _targetname.downcase.sub(/srcs_overlay_/,"")
				end
				file.printf("Overlay %s\n{\n\tAfter\t%s\n",
						overlay_name[overlay_table_num+2].downcase.sub(/srcs_overlay_/,""),
						_targetname
				)
				file.printf("\tObject")
				source_name.each{ |name|
					filename = name.slice(/[a-zA-Z_0-9]+\./)
					if _count != 0 then 
						file.printf("\t")
					end
					file.printf("\t$(OBJDIR)/%so",filename)
					if name.match(/\\\z/) then
						file.printf(" \\")
					end
					file.puts("\n")
					_count = _count+1
				}

				if lib_name.length > 0 then
					file.printf("\tLibrary")
					local_c = 0
					lib_name.each{ |name|
						local_c = local_c + 1
						filename = name
						file.printf("\t%s",filename)
						if local_c != lib_name.length  then
							file.printf(" \\")
						end
						file.puts("\n")
					}
					lib_name.clear
				end
				file.puts("}\n\n")
			}
		end
	end

	#オーバーレイソース名の取得
	if line.match(MATCH_OVERLAYSRC) then
		line_get_flag = 1

		if overlay_flag==0 then
			printf "Error!!\n"
			printf "#===>でオーバーレイアドレスを指定していないのに、\n"
			printf "オーバーレイ用のソ\ースコードが記述されています\n"
			exit 1
		end

		overlay_name << line.split(nil)[0]
		overlay_hash[line.split(nil)[0]] = 1

		source_name = Array.new(0)
		source_name << line

		overlay_table_num = overlay_table_num + 1
	end

	if line.match(MATCH_LIB) then
		line =~ /(\S+)\s+(\S+)/
		lib_name << $2
	end

}

#オーバーレイに該当するファイルがコンパルターゲットになるようにする
File.open(OUTPUT_OVERLAYFILES,"w"){|file|
	for i in 3..overlay_name.size-1
	if i==3 then
		file.printf("SRCS_OVERLAY\t=\t")
	end
	file.printf("\t\t\t$(%s)",overlay_name[i])
	if i!=overlay_name.size-1 then
		file.printf("\t\\\n",overlay_name[i])
	else
		file.printf("\n")
	end

end

}


#オーバーレイのターゲットネームとその番号をテキストに吐き出す
File.open(OUTPUT_OVERLAYTEXT,"w"){|file|
	for i in 1..overlay_count-1
		file.printf( " ID 0x%x = %s\n",i,overlay_name[i+3].downcase.sub(/srcs_overlay_/,""));
	end
}

#p overlay_count
#p overlay_table_num

if overlay_count != overlay_table_num then
	printf "'Error!!!\n"
	printf "===>            =  %d 回\n",overlay_count
	printf "SRCS_OVERLAY_?  =  %d 回\n",overlay_table_num
	printf "'===>'で指定するオーバーレイターゲットの回数と\nオーバーレイ指定のソ\ースコード群の数があっていません\n"
	exit 1
else
	printf "オーバーレイツール正常終了\n"
end



#p overlay_name
#p overlay_target


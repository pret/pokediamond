###############################################################
#
#	ワープデータ用コンバータ
#
#
#	date	2006.04.01
#	author	tamada GAME FREAK inc.
#
#
#
###############################################################

###############################################################
#
#
#
###############################################################

class OutputFile
	def initialize fname
		@fp = File.open(fname, "w")
		@name = fname
		@linecount = 0
		putHeader
	end

	def puts *content
		@fp.puts *content
	end

	def printf	*content
		@fp.printf *content
	end

	def putHeader
		@fp.puts "//#{Time.now.ctime}"
		@fp.puts "//#{@name}"
	end

	def putFooter
		@fp.puts "//#{@name}"
	end

	def close
		putFooter
		@fp.close
	end

	def filediff diff_file
		f1 = File.open(@name,"r")
		l1 = f1.read
		f1.close
		f2 = File.open(diff_file,"r")
		l2 = f2.read
		f2.close
		return (l1 != l2)
	end

	def diff_overwrite diff_file
		if FileTest.exist? diff_file then
			if filediff(diff_file) == true then
				#差分があった場合は更新
				File.delete diff_file
				File.rename @name, diff_file
			else
				#差分がなかった場合は自分のファイルを削除
				File.delete @name
			end
		else
			#diff_fileが存在しない場合は自分のファイルをdiff_fileにリネーム
			File.rename @name, diff_file
		end
	end

end

###############################################################
###############################################################
#------------------------------------------------
#------------------------------------------------
class WarpDataFile < OutputFile
	def putHeader
		puts "//=================================="
		puts "//=================================="
		puts "static const WARPDATA WarpData[] = {"
	end

	def putLine	room_id, room_x, room_z, escape, fld_id, fld_x, fld_z, arrive, arrive_id
		a_id = "FLAG_ARRIVE_" + arrive_id.upcase
		puts "\t{"
		printf "\t\t%-20s,%4d,%4d,\n", "ZONE_ID_" + room_id.upcase, room_x, room_z
		printf "\t\t%-20s,%4d,%4d,\n", "ZONE_ID_" + fld_id.upcase, fld_x, fld_z
		printf "\t\t%-5s,", if escape == true then "TRUE" else "FALSE" end
		printf "%-5s,\n", if arrive == true then "TRUE" else "FALSE" end
		printf "\t\t%-20s,\n", a_id
		printf "\t},\n"
	end

	def putFooter
		puts "};"
		puts "//=================================="
	end
end

#------------------------------------------------
#------------------------------------------------
class WarpHeaderFile < OutputFile
	def putHeader
		puts "//=================================="
		puts "//=================================="
		puts "#ifndef __WARPDATA_H__"
		puts "#define __WARPDATA_H__"
		puts "\n"
	end

	def putLine	id, number
		printf "#define	WARP_ID_%02s (%d)\n",id.upcase, number.to_i
		@current_number = number
	end

	def putFooter
		puts "\n"
		puts "#define	WARP_ID_MAX		(#{@current_number.to_i + 1})"
		puts "\n"
		puts "#endif	//__WARPDATA_H__"
		puts "//"
	end
end



###############################################################
###############################################################

def convert	infile
	#データファイル（別名で作成）
	datafile = WarpDataFile.new("temp_data.c")
	#ヘッダファイル（別名で作成）
	headerfile = WarpHeaderFile.new("temp_data.h")

	line = infile.gets	#2行読み飛ばし
	line = infile.gets

	while line = infile.gets
		if line =~/^[1-9]/ then
			cl = line.split
			datafile.putLine	cl[1],cl[2],cl[3],cl[4] == "○", cl[5],cl[6],cl[7],cl[8] == "○", cl[9]
			headerfile.putLine	cl[9],cl[0]
		else
			break
		end
	end

	datafile.close
	headerfile.close

	#もともとのデータファイルと比較、変化があれば上書きする
	datafile.diff_overwrite "warpdata.c"
	#もともとのヘッダファイルと比較、変化があれば上書きする
	headerfile.diff_overwrite "warpdata.h"
end

infile = File.open("warpdata.txt", "r")
convert infile
infile.close


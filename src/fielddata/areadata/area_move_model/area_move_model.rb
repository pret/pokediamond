#---------------------------------------------------
#
#	@brief	エリア毎の動作モデルリスト処理用スクリプト
#	@file	area_move_model.rb
#	@date	2005.11.24
#	@author	tamada GAME FREAK Inc.
#
#	@param	ARGV[0]	ターゲット定義出力先ファイル名	
#	@param	ARGV[1]	アーカイブ対象定義ファイル名
#	@param	ARGV[2]	エリア管理表ファイル名
#	@param	ARGV[3]	動作モデル管理表ファイル名
#
#---------------------------------------------------
FIELDOBJ_CODE_HEADER	=	"fieldobj_code.h"
$KCODE = "SJIS"
#---------------------------------------------------
#	エリア管理表の解釈
#---------------------------------------------------
def read_areatable	filename
	arealist = []
	count = 0
	infile = File.open(filename, "r")
	infile.gets		#2行読み飛ばし
	infile.gets
	while line = infile.gets
		if line =~ /^AREA_ID_/ then
			areaname = line.split[0].sub(/\AAREA_ID_/, "").downcase
			if arealist.include?(areaname) then
				STDERR.puts "エリアIDが多重定義されています:#{areaname}\n"
			else
				arealist[count] = areaname
				count += 1
			end
		else
			break
		end
	end
	return arealist
end

#---------------------------------------------------
#	エリア毎のアセンブラファイルを生成
#---------------------------------------------------
def make_asmfile filename, objlist
	output = ""
	output += "\#	常駐動作モデル定義リスト:#{filename}\n"
	output += "\t.text\n"
	output += "\#include	\"#{FIELDOBJ_CODE_HEADER}\"\n"
	output += "\n"
	objlist.each {|model|
		name = model.upcase
		if name != model
			STDERR.puts "小文字があります:#{filename},#{model}\n"
		end
		output += "\t.short\t#{model}\n"
	}
	output += "\n"
	output += "	.short	OBJCODEMAX\n"
	output += "\n"
end

#---------------------------------------------------
#	動作モデルリストの書かれたファイルを解釈
#---------------------------------------------------
def read_area_movemodel filename
	areadata = {}
	infile = File.open(filename, "r")

	while line = infile.gets
		#	"#end"で始まる場合、データ終端とみなす
		if line =~/^#end/ then break end
		#	"#"で始まる場合コメント行として読み飛ばす
		if line =~ /^#/ then next end

		column = line.split
		areaname = column[0].downcase
		if areadata.key? areaname
			STDERR.puts "エリア名が重複しているのでスキップします：#{areaname}\n"
			next
		end
		areadata[areaname] = make_asmfile areaname, column[1..column.length - 1]
	end

	infile.close
	return areadata
end

#---------------------------------------------------
#---------------------------------------------------
def make_listfile srcfilename, arcfilename, arealist
	srcfile = File.open(srcfilename, "w")
	arcfile = File.open(arcfilename, "w")

	srcfile.puts "#自動生成されたファイルです\n"
	srcfile.puts "SRCFILES	=	\\\n"

	arealist.each {|name|
		srcfile.puts "\t#{name}.s \\"
		arcfile.puts "\"#{name}.bin\"\n"
	}

	srcfile.puts "\n"
	srcfile.close
	arcfile.close
end

#---------------------------------------------------
#---------------------------------------------------
def make_area_asm_files arealist, areadata
	dummy_list = []
	arealist.each {|areaname|
		sfile = File.open(areaname + ".s", "w")
		if areadata.key?(areaname) then
			sfile.puts areadata[areaname]	
		else
			STDERR.puts "データがないのでダミーを生成します：#{areaname}\n"
			sfile.puts "#{make_asmfile areaname, dummy_list}\n"
		end
		sfile.close
	}
end

#---------------------------------------------------
#---------------------------------------------------
def check_entry_area arealist, areadata
	areadata.each{|key, value|
		unless arealist.include?(key) then
			puts "存在しないエリアの定義があります\t#{key}\n"
		end
	}
end
#---------------------------------------------------
#	メイン処理よびだし
#---------------------------------------------------
arealist = read_areatable ARGV[2]
areadata = read_area_movemodel ARGV[3]

make_listfile ARGV[0], ARGV[1], arealist
make_area_asm_files arealist, areadata
check_entry_area arealist, areadata


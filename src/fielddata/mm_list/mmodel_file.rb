###############################################################
#
#
#
#
###############################################################

FIELDOBJ_CODE_HEADER	=	"../../field/fieldobj_code.h"
#---------------------------------------------------
#---------------------------------------------------
def read_table infile
	mml = Array.new
	area_count = 0
	mml_count = 0
	now_id = nil
	line = infile.gets	#	読み飛ばし
	while line = infile.gets
		#puts "#{line}"
		m = /(MMLID_\w+)\W(\d+)\W([0-9A-Z]+)\W.+/.match line
		if m == nil 
			puts "NOT HIT!"
			break
		else
			areaID = m[1]
			mmlID = m[3]
			unless mmlID =~ /^[0-9A-Z]+$/
				STDERR.puts "動作モデルIDが正しくありません！：#{mmlID}\n"
				exit 1
			end
			if now_id == nil
				now_id = areaID
				mml[area_count] = Array.new
				mml[area_count][mml_count] = areaID
			elsif now_id != areaID
				area_count += 1
				mml_count = 0
				now_id = areaID
				mml[area_count] = Array.new
				mml[area_count][mml_count] = areaID
			end
			mml_count += 1
			mml[area_count][mml_count] = mmlID
		end
	end
	return mml
end
#---------------------------------------------------
#---------------------------------------------------
def make_asm_text ofile, ar
	#STDERR.puts "#{ofile.path}...#{ar}"
	ofile.puts <<HEADER
#常駐動作モデル定義リスト	#{ofile.path}

	.text

	.include	"#{FIELDOBJ_CODE_HEADER}"

HEADER

	ar.each{|id|
		ofile.printf("\t.short\t%s\n", id)
	}

	ofile.puts "\n"
	ofile.puts "\t.short\tOBJCODEMAX\n"
	ofile.puts "\n"
end

#---------------------------------------------------
#---------------------------------------------------

#入力ファイルから定義を読み込む
infile = File.open(ARGV[0],"r")
mml = read_table infile
infile.close

#ダミー用定義を追加
mml << ["mmlid_noentry"]


arclist = File.open(ARGV[1],"w")
archead = File.open(ARGV[2],"w")
archead_def = "__#{ARGV[2].upcase.gsub(/\./,"_")}__"

archead.puts <<HEADER
//	動作モデルふりわけ指定ID

\#ifndef	#{archead_def}
\#define #{archead_def}

HEADER

linecount = 0
mml.each{|ar|
	sym = ar[0].downcase

	#定義ごとにファイル生成
	outfile = File.open("#{sym}.s", "w")
	make_asm_text outfile, ar[1..ar.length - 1]
	outfile.close

	#アーカイブ指定ファイルに一行出力
	arclist.puts "\"#{sym}.bin\""

	#
	archead.printf "#define	%-20s %d\n",sym.upcase, linecount

	linecount += 1
}

archead.puts "#endif"
arclist.close
archead.close

=begin
mml.each{|value|
	puts "#{value[0]}..."
	(1 .. value.length).each{|n| printf "[%d]%s:",n,value[n]}
	puts "\n"
}
=end

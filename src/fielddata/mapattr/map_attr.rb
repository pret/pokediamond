###############################################################
#
#		マップアトリビュート表コンバータ
#
#		sousuke tamada GAME FREAK inc.
#
#		2005.12.16	作成
#
#		マップアトリビュート管理表からアトリビュートの定義を
#		生成する。
#
###############################################################


###############################################################
#
#
#
###############################################################

class Converter

	attr :define
	attr :value
	attr :water
	attr :encount
	attr :comment

	def initialize fname
		@count = 0
		@code = {}
		@defs = {}
		@fp = File.open fname, "r"
		@fp.gets		#一行目は項目名だけなので読み込み
	end

	def init_line
		@value = nil
		@define = nil
		@water = nil
		@encount = nil
		@comment = nil
	end

	#------------------------------------------------
	#
	#------------------------------------------------
	def entry_code code_str
		if !(code_str =~ /[0-9a-f][0-9a-f]h/) then
			STDERR.puts "[#{@count}][#{code_str}]Codeがない！\n"
			exit 1
		end
		val = "0x#{code_str.sub(/h$/,"")}"
		if @code.has_key? val then
			STDERR.puts "[#{@count}][#{@code[val]}][#{val}]Codeが重複しています！\n"
			exit 1
		end
		@value = val
		@code[value] = @count
	end

	#------------------------------------------------
	#
	#------------------------------------------------
	def entry_define def_str
		if def_str == "" then
			return
		end
		df = "MATTR_#{def_str.upcase}"
		if @defs.has_key? df then
			STDERR.puts "[#{@count}][#{@defs[df]}][#{df}]定義名が重複しています！\n"
			exit 1
		end
		@define = df
		@defs[df] = @count
	end

	#------------------------------------------------
	#------------------------------------------------
	def entry_water water_str
		@water = if water_str == "○" then true else false end
	end

	#------------------------------------------------
	#------------------------------------------------
	def entry_encount encount_str
		@encount = if encount_str == "○" then true else false end
	end


	#------------------------------------------------
	#
	#------------------------------------------------
	def reader 
		init_line
		@count += 1
		line = @fp.gets
		if line == nil then return nil end

		cm = line.split ","
		if cm[0] =~/^#END/ then
			return nil
		end
		entry_code cm[1]
		entry_define cm[2]
		entry_water cm[4]
		entry_encount cm[5]
		@comment = "//#{cm[6]}:#{cm[7]}".chomp
	end

	#------------------------------------------------
	#
	#------------------------------------------------
end

###############################################################
#
#
#
###############################################################

#------------------------------------------------
#------------------------------------------------
class OutputFile
	def initialize fname
		@fp = File.open(fname, "w")
		@name = fname
		putHeader
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

end
#------------------------------------------------
#------------------------------------------------
class MapAttrHeaderFile < OutputFile
	def putHeader
		@name = @fp.path.upcase.sub(/\./,"_")
		#@fp.puts "#ifndef __#{@name}__\n"
		#@fp.puts "#define __#{@name}__\n"
		#@fp.puts "\n"
	end
	def putLine conv
		if conv.define != nil then
			@fp.printf("#define %-20s %10s %s\n", conv.define, conv.value, conv.comment)
		end
	end
	def putFooter
		#@fp.puts "\n"
		#@fp.puts "#endif //__#{@name}__\n"
	end
end

#------------------------------------------------
#------------------------------------------------
class MapAttrDataFile < OutputFile
	def putHeader
		@fp.puts "//map attribute data\n"
		@fp.puts "\#define MATTR_WATER_MASK\t0x01\n"
		@fp.puts "\#define MATTR_ENCOUNT_MASK\t0x02\n"
		@fp.puts "\n"
		@fp.puts "static const u8 MapAttributeData[] = {\n"
	end

	def putLine conv
		str = if conv.water then "MATTR_WATER_MASK" else "0" end
		str += "|"
		str += if conv.encount then "MATTR_ENCOUNT_MASK" else "0" end
		@fp.puts "\t#{str},	//#{conv.value}:#{conv.define}\n"
	end

	def putFooter
		@fp.puts "};\n\n"
	end
end

#------------------------------------------------
#------------------------------------------------
###############################################################
#
#
#
###############################################################

cnv = Converter.new ARGV[0]
headerfile = MapAttrHeaderFile.new ARGV[1]
datfile = MapAttrDataFile.new ARGV[2]

while cnv.reader != nil
	headerfile.putLine cnv
	datfile.putLine cnv
end

headerfile.close
datfile.close


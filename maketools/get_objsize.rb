################################################################################
#
#
#
#		main.xMAP解析用スクリプト
#
#		2006.04.01
#		tamada GAME FREAK inc.
#
#
################################################################################
#puts "#{ARGV.length}"
#ARGV.each{|a| puts"#{a}"}


#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
def search_large_section read_file
	while line = read_file.gets
		column = line.split
		#if column[2] == ".rodata" && !(column[1] =~ /^00000/) then
		if column[2] == ".#{search}" && !(column[1] =~ /^00000[0-9]/) then
		#if column[2] == ".#{search}" && !(column[1] =~ /^000000/) then
			puts "#{line}\n"
		end
	end
end

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
def calc_overlay_size read_file
	bss = Hash.new
	text = Hash.new
	data = Hash.new

	while line = read_file.gets
		unless line =~ /^#/ then
			next
		end
		m = /^#>(.+)\W(SDK_OVERLAY)\.(.*)\.(.*SIZE).*/.match(line)
		if m == nil then next end
		case m[4]
		when "BSS_SIZE"
			bss[m[3]] = m[1].hex
		when "TEXT_SIZE"
			text[m[3]] = m[1].hex
		when "DATA_SIZE"
			data[m[3]] = m[1].hex
		end
	end

	text.each_key {|key|
		total = text[key] + data[key] + bss[key]
		printf "%8x(%6x %6x %6x)\t%s\n", total, text[key], data[key], bss[key], key
	}
end

#----------------------------------------------------------------------------
#
#		各オブジェクト（*.o)ごとの集計を行う
#
#----------------------------------------------------------------------------
def calc_object_size read_file
	bss = Hash.new
	text = Hash.new
	data = Hash.new
	rodata = Hash.new
	total = Hash.new
	overlay = Hash.new

	def count_up hs, key, value
		if hs.has_key? key then
			hs[key] += value
		else
			hs[key] = value
		end
	end

	flag = false
	while line = read_file.gets
		if line =~ /^#/ then
			m = /^# \.(.*)/.match line
			if m == nil then next end
			ol_id = line.chomp.sub(/^# \./,"").sub(/\..*$/,"")
			if ol_id == "main" then
				flag = true
			end
		end

		if flag == false then 
			next
		end

		m = /^  \w+ (\w+) (\.\w+)\W+\w+(.*)/.match line
		if m == nil then
			next
		end

		key = m[3]
		value = m[1].hex
		if overlay.has_key? key then
			if overlay[key] != ol_id then
				#STDERR.puts "ERROR!:\"#{ol_id}\" != \"#{overlay[key]}\""
				#STDERR.puts "ERROR!:#{line}\n"
				#exit 1
			end
		else
			overlay[key] = ol_id
		end

		case m[2]
		when ".text"
			count_up text, key, value
			count_up total, key, value
		when ".data"
			count_up data, key, value
			count_up total, key, value
		when ".rodata"
			count_up rodata, key, value
			count_up total, key, value
		when ".bss"
			count_up bss, key, value
			count_up total, key, value
		end

	end

	printf "total   (.text  .rodat .data  .bss)\n"
	text.each_key {|key|
		#total = text[key] + data[key] + rodata[key] + bss[key]
		printf "%8x(%6x %6x %6x %6x)\t%-32s %s\n",
		total[key], text[key], rodata[key], data[key], bss[key],
		overlay[key].upcase, key
	}
end

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
=begin
if ARGV.length < 1 then
	search = "rodata"
else
	search = ARGV[0]
end
dat = File.open("bin/ARM9-TS/Release/main.nef.xMAP","r")
search_large_section dat
dat.close
=end

if ARGV.length < 1 then
	fname = "bin/ARM9-TS/Release/main.nef.xMAP"
else
	fname = ARGV[0]
end
infile = File.open(fname, "r")
calc_object_size infile
infile.close


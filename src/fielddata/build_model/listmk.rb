nsbmd = File.open("nsbmd.txt", "w")
build = File.open("g3_build", "w")
idfile = File.open("build_model_id.h","w")

line = gets

build.puts "G3D_IMD	= \\\n"
idfile.puts "//build mode ID define table\n"

ct = 0
while line = gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	
	nsname = column[1].sub(/\.mb/,".imd")
	build.puts "\t$(DATASRC)/#{nsname} \\\n"
	
	nsname = column[1].sub(/\.mb/,".nsbmd")
	nsbmd.puts "\"nsbmd_files/#{nsname}\"\n"
	
	nsname = column[1].sub(/\.mb/,"")
	idname = nsname.upcase
	idfile.puts "#define\tBMID_#{idname}\t(#{ct})"
	ct += 1
end
puts ""

idfile.puts "#define\tBMID_MAX\t#{ct}\n"

build.close
nsbmd.close
idfile.close

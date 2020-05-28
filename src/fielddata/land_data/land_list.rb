land_list = open("land_list","w+")
land_arc_list = open("land_arc_list","w+")
land_model_list = open("land_model_list","w+")

land_list.puts "CONCAT_TARGET = \\\n"
land_model_list.puts "G3D_IMD	= \\\n"

yen_flg = 0

while f = ARGV.shift
	file_name = f
	csv_file = open(file_name,"r")
	line = csv_file.gets
	line = csv_file.gets
	line = csv_file.gets
	while line = csv_file.gets
		if line =~/^#END/ then
			break
		end
		if yen_flg != 0 then
			land_list.printf(" \\\n")
			land_model_list.printf(" \\\n")
		end
		yen_flg = 1
		column = line.split ","
		name = column[1]
		land_list.printf("\tbin/#{name}.bin")
		land_arc_list.printf("\"bin/#{name}.bin\"\n")
		land_model_list.printf("\t$(DATASRC)/#{name}c.imd")
	end
	csv_file.close
end

land_model_list.close
land_arc_list.close
land_list.close

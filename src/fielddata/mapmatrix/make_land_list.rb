land_list = open("land_list","w+")

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
		column = line.split ","
		name = column[1]
		land_list.puts "#{name}\n"
	end
	csv_file.close
end

land_list.close

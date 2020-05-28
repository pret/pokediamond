arclist = File.open("arclist", "w")

line = gets
while line = gets
	if line =~/ / then
		break
	elsif line =~/#END/ then
		break
	end
	column = line.split "\t"
	name = "tmp/"+column[0]
	sname = name.downcase
	sname.concat("_mat.bin")
	arclist.puts "\"#{sname}\"\n"
end
puts ""
arclist.close

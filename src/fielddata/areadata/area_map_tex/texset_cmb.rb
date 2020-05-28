arg = $*

area_tbl = arg[0]
imd_path = arg[1]
cmd_path = arg[2]

File.open(area_tbl,"r"){ |file|
  file.gets
  file.gets

  while line = file.gets
	column = line.split "\t"
	if column[3]=="dummy" then
	  next
	end
	tmp = column[2].sub(/\.xls/,".imd")
	dist = imd_path + tmp
	tmp = column[3].sub(/\.xls/,".imd")
	src1 = imd_path + tmp
	tmp = column[4].sub(/\.xls/,".imd")
	src2 = imd_path + tmp 
	
	#外部コマンド呼び出し
	exe_cmd = cmd_path + " -q -o " + dist + " " + src1 + " " + src2 + " imd_files/tex_griddmy.imd"
	#	exe_cmd = cmd_path + " -q -o " + dist + " " + src1 + " " + src2
	puts exe_cmd
	system(exe_cmd)
	if $? == 0x7F00 then
	  puts "Error! tex_mag.exe failed"
	  return
	end
  end
}

puts "texset_cmb Success!\n"

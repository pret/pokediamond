arg = $*
area_tbl = arg[0]
tex_list =arg[1]
tex_path = "$(TEXSETIMDDIR)"

f = open(tex_list,"w")
f.puts "G3D_TEX_SET = \\"

$file_lst = Array.new

File.open(area_tbl,"r"){ |file|
  file.gets
  file.gets

  while line = file.gets
	column = line.split "\t"
	if column[3]=="dummy" then 
		tmp = column[2].sub(/\.xls/,".imd")
		if $file_lst.include?(tmp) == FALSE then
		  f.puts "\t" + tex_path + "/" + tmp + "\t\\"
		  $file_lst << tmp
		end
	else
		tmp = column[2].sub(/\.xls/,".imd")
		if $file_lst.include?(tmp) == FALSE then
		  $file_lst << tmp
		end
		tmp = column[3].sub(/\.xls/,".imd")
		if $file_lst.include?(tmp) == FALSE then
		  f.puts "\t" + tex_path + "/" + tmp + "\t\\"
		  $file_lst << tmp
		end
		tmp = column[4].sub(/\.xls/,".imd")
		if $file_lst.include?(tmp) == FALSE then 
		  f.puts "\t" + tex_path + "/" + tmp + "\t\\"
		  $file_lst << tmp
		end
	end
  end
}

for m in $file_lst do
  puts m
end

f.puts ""
f.close


#�@�������F�ǂݎ��t�@�C��
#�@�������F�폜�����i�p�X�j
arg = $*
texlist = open(arg[0]);
del = arg[1]

list = open("g3list","w")
list.puts "G3D_TEX_IMD	= \\\n"
while line = texlist.gets
	if line =~/ / then
		break
	end
	name = line.sub(".nsbtx",".imd")
	name = name.sub(del,"")
	name = name.sub("\"","")
	name = name.sub("\"","")
	name.chomp!
	list.puts "\t$(TEXSETIMDDIR)/#{name} \\\n"
end
puts ""
list.close
texlist.close

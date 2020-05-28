#パス取得
path = open("file_path.txt","r")
nsbmt_path_str = path.gets
path_str = path.gets
nsbmt_path_str.chomp!
path_str.chomp!
path.close

arg = $*
bin_name = arg[0]

temp_name = bin_name
temp_name = temp_name.sub("bin/","tmp/")
temp_name = temp_name.sub(".bin",".tmp")

dst = open(temp_name,"wb+")
header = open(bin_name,"wb+" )

#アトリビュート
attr_name = temp_name
attr_name = attr_name.sub("tmp/","")
attr_name = attr_name.sub(".tmp","a.dat")

open(path_str+attr_name,"rb") do |f|
	dst.write(f.read)
	size = test(?s, f)
	if size == nil then
		size = 0
	end
	ary = Array(size)
	pack_str = ary.pack("i*")
	header.write(pack_str)
end

#配置
model_name = temp_name
model_name = model_name.sub("tmp/","")
model_name = model_name.sub(".tmp","e.dat")
open(path_str+model_name,"rb") do |f|
	dst.write(f.read)
	size = test(?s, f)
	if size == nil then
		size = 0
	end
	ary = Array(size)
	pack_str = ary.pack("i*")
	header.write(pack_str)
end

#地形
nsbmt_name = temp_name
nsbmt_name = nsbmt_name.sub("tmp/","")
nsbmt_name = nsbmt_name.sub(".tmp","c.nsbmt")

open(nsbmt_path_str+nsbmt_name,"rb") do |f|
	dst.write(f.read)
	size = test(?s, f)
	if size == nil then
		size = 0
	end
	ary = Array(size)
	pack_str = ary.pack("i*")
	header.write(pack_str)
end

#高さ
height_name = temp_name
height_name = height_name.sub("tmp/","")
height_name = height_name.sub(".tmp","c.bhc")

open(path_str+height_name,"rb") do |f|
	dst.write(f.read)
	size = test(?s, f)
	if size == nil then
		size = 0
	end
	ary = Array(size)
	pack_str = ary.pack("i*")
	header.write(pack_str)
end

dst.close

#ヘッダに連結
open(temp_name,"rb") do |f|
	header.write(f.read)
	size = test(?s, f)
end
	
print arg,"を連結","\n"


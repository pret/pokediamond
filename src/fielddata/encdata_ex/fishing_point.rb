#�����_���̎틛�ނ�|�C���g�f�[�^�쐬
#�}�b�v�}�g���b�N�X�̉�����1�̂Ƃ���p�̏����ł�

def make_data(inFile, d_ary, w_ary,block_ofs)
	idx_ary = Array.new(0)
	water = 0
	cnt = 0
	while cnt<32*32
		#����1�o�C�g�ǂ�
		data = inFile.read(1)
		#���A�g���r���[�g���`�F�b�N
		attr_str_ary = data.unpack("B8")
		attr_str = attr_str_ary.shift
		attr_str.insert(0,"0b")
		attr = attr_str.to_i(0)
		if attr == 21 then
			idx_ary << (cnt+(32*32*block_ofs))
			#���Ȃ�΃J�E���g�A�b�v
			water = water+1
		end
		#��ʂP�o�C�g�ǂ�(���߂͂��Ȃ�)
		data = inFile.read(1)
		cnt = cnt+1
	end
	p water
	w_ary << water

	d_ary << idx_ary
#	ary = Array(water)
#	outFile.write(ary.pack("i*"))

#	idx_ary.each {|x|
#		ary = Array(x)
#		outFile.write(ary.pack("S*"))
#		 }
	
end

fish_point = open("bin/fishing_point.bin","wb")
fish_csv = open("fish.csv","r")
## �|�P�������̂Ƃ���͓ǂݔ�΂�
while line = fish_csv.gets
	if line =~/^#END/ then
		break
	end
end	#while

line = fish_csv.gets    ## 1�s�ǂݔ�΂�
#�ǂރt�@�C���������C�g
line = fish_csv.gets
column = line.split ","
file_num = column[0].chomp
ary = Array(file_num.to_i)

fish_point.write(ary.pack("i*"))

data_ary = Array.new(0)
water_num_ary = Array.new(0)
ofs = 0
while line = fish_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[0].chomp
	path = "../../data/fld_map_data/" + name
	#�t�@�C���J��
	p path
	bin_file = open(path,"rb")

	make_data(bin_file, data_ary,water_num_ary,ofs)
	ofs = ofs+1
end	#while

	water_num_ary.each {|x|
		ary = Array(x)
		fish_point.write(ary.pack("i*"))
		 }

	data_ary.each {|a|
		a.each{ |n|
			ary = Array(n)
			fish_point.write(ary.pack("S*"))
		}
	}




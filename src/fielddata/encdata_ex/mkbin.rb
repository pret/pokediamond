#�����X�^�[�i���o�[��`��z��

def make_bin(m_ary, op_txt, op_bin, debug_txt, debug_mes)
	txt = open(op_txt,"r")
	bin = open(op_bin,"wb")
	while line = txt.gets
		if line =~/^#END/ then
			break
		end
		name = line
		name.chomp!
		idx = m_ary.index(name)
		
		if idx == nil then
			p name + ":unknown"
			#�f�o�b�O�e�L�X�g�ɋL�q
			debug_txt.printf("%s�F%s�͉�͂ł��܂���\n",debug_mes,name)
		else
			ary = Array(idx+1)
			pack_str = ary.pack("i*")
			bin.write(pack_str)
		end
	end	#while	
end

monsno_def = open("../../../include/poketool/monsno.h","r")

mons_ary = Array.new(0)
while line = monsno_def.gets
	if line =~/^#endif*/ then
		break
	end
	name = line.split "\t"
	if name[0] == "#define" then
#		p name[1]
		if name[1] != nil then
			mons_ary << name[1]
		end
	end
end	#while

#�f�o�b�O�p�e�L�X�g�쐬
debug = open("debug.txt","wb")

#�_�C�����؂̃f�[�^�쐬�i�ʏ�j
make_bin(mons_ary, "honey_dia_nrm.txt", "bin/honey_dia_nrm.bin", debug, "�_�C�����ʏ�")

#�_�C�����؂̃f�[�^�쐬�i���A�j
make_bin(mons_ary, "honey_dia_rare.txt", "bin/honey_dia_rare.bin", debug, "�_�C�������A")

#�_�C�����؂̃f�[�^�쐬�i�����A�j
make_bin(mons_ary, "honey_dia_s_rare.txt", "bin/honey_dia_s_rare.bin", debug, "�_�C���������A")

#�p�[�����؂̃f�[�^�쐬�i�ʏ�j
make_bin(mons_ary, "honey_perl_nrm.txt", "bin/honey_perl_nrm.bin", debug, "�p�[�����ʏ�")

#�p�[�����؂̃f�[�^�쐬�i���A�j
make_bin(mons_ary, "honey_perl_rare.txt", "bin/honey_perl_rare.bin", debug, "�p�[�������A")

#�p�[�����؂̃f�[�^�쐬�i�����A�j
make_bin(mons_ary, "honey_perl_s_rare.txt", "bin/honey_perl_s_rare.bin", debug, "�p�[���������A")

#�T�t�@���̃f�[�^�쐬�i�S���}�ӑO�j
make_bin(mons_ary, "safari_bef.txt", "bin/safari_bef.bin", debug, "�T�t�@���}�ӑO")

#�T�t�@���̃f�[�^�쐬�i�S���}�ӌ�j
make_bin(mons_ary, "safari_af.txt", "bin/safari_af.bin", debug, "�T�t�@���}�ӌ�")

#���R�̃f�[�^�쐬�i�S���}�ӑO�j
#make_bin(mons_ary, "mnt_bef.txt", "bin/mnt_bef.bin", debug, "���R�}�ӑO")<<�s�v�ɂȂ���

#���R�̃f�[�^�쐬�i�S���}�ӌ�j
make_bin(mons_ary, "mnt_af.txt", "bin/mnt_af.bin", debug, "���R�}�ӌ�")

#�ނ�̃f�[�^�쐬
make_bin(mons_ary, "fish.txt", "bin/fish.bin", debug, "�ނ�")


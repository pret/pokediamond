#���h��G���J�E���g(�_�C��)�|�P���������X�g�i�ʏ�j
#���h��G���J�E���g(�_�C��)�|�P���������X�g�i���A�j
#���h��G���J�E���g(�_�C��)�|�P���������X�g�i�����A�j
honey_dia_nrm = open("honey_dia_nrm","w")
honey_dia_rare = open("honey_dia_rare","w")
honey_dia_s_rare = open("honey_dia_s_rare","w")
honey_dia_csv = open("honey_dia.csv","r")
line = honey_dia_csv.gets    ## 1�s�ǂݔ�΂�
line = honey_dia_csv.gets    ## 1�s�ǂݔ�΂�
while line = honey_dia_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[1].chomp
	honey_dia_nrm.puts("#{name}")		#�ʏ�
	name = column[2].chomp
	honey_dia_rare.puts("#{name}")		#���A
	name = column[3].chomp
	honey_dia_s_rare.puts("#{name}")	#�����A
end	#while

#���h��G���J�E���g(�p�[��)�|�P���������X�g�i�ʏ�j
#���h��G���J�E���g(�p�[��)�|�P���������X�g�i���A�j
#���h��G���J�E���g(�p�[��)�|�P���������X�g�i�����A�j
honey_perl_nrm = open("honey_perl_nrm","w")
honey_perl_rare = open("honey_perl_rare","w")
honey_perl_s_rare = open("honey_perl_s_rare","w")
honey_perl_csv = open("honey_perl.csv","r")
line = honey_perl_csv.gets    ## 1�s�ǂݔ�΂�
line = honey_perl_csv.gets    ## 1�s�ǂݔ�΂�
while line = honey_perl_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[1].chomp
	honey_perl_nrm.puts("#{name}")		#�ʏ�
	name = column[2].chomp
	honey_perl_rare.puts("#{name}")		#���A
	name = column[3].chomp
	honey_perl_s_rare.puts("#{name}")	#�����A
end	#while

#�����G���J�E���g�|�P���������X�g�i�S���}�ӓ���O�j
#�����G���J�E���g�|�P���������X�g�i�S���}�ӓ����j
safari_bef = open("safari_bef","w")
safari_af = open("safari_af","w")
safari_csv = open("safari.csv","r")
line = safari_csv.gets    ## 1�s�ǂݔ�΂�
line = safari_csv.gets    ## 1�s�ǂݔ�΂�
while line = safari_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[0].chomp
	safari_bef.puts("#{name}")		#�O
	name = column[1].chomp
	safari_af.puts("#{name}")		#��
end	#while

#���R�G���J�E���g�|�P���������X�g�i�S���}�ӓ���O�j
#���R�G���J�E���g�|�P���������X�g�i�S���}�ӓ����j
mnt_bef = open("mnt_bef","w")
mnt_af = open("mnt_af","w")
mnt_csv = open("mnt.csv","r")
line = mnt_csv.gets    ## 1�s�ǂݔ�΂�
line = mnt_csv.gets    ## 1�s�ǂݔ�΂�
while line = mnt_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[0].chomp
	mnt_bef.puts("#{name}")	#�O
	name = column[1].chomp
	mnt_af.puts("#{name}")		#��
end	#while

#�����_���̎�ނ�G���J�E���g�|�P���������X�g
fish = open("fish","w")
fish_csv = open("fish.csv","r")
line = fish_csv.gets    ## 1�s�ǂݔ�΂�
line = fish_csv.gets    ## 1�s�ǂݔ�΂�
while line = fish_csv.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	name = column[0].chomp
	fish.puts("#{name}")
end	#while


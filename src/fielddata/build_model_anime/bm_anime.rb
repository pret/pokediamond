#�A�j���e�[�u���쐬

#�A�j�������f�[�^�̏�������
def set_none_anime_data(inAry, inStrID)
	inAry = Array(0xff)			#�A�j�����Ȃ�
	str = inAry.pack("C*")
	inStrID.write(str)
	
	inAry = Array(0xff)			#�A�j���^�C�v�s��
	str = inAry.pack("C*")
	inStrID.write(str)

	inAry = Array(0)			#���E���Ȃ�
	str = inAry.pack("C*")
	inStrID.write(str)

	inAry = Array(0)			#4�o�C�g���E�_�~�[�Z�b�g
	str = inAry.pack("C*")
	inStrID.write(str)

	#�A�j���i���o�[����������4�܂�
	for i in [0,1,2,3]
		inAry = Array(0xffffffff)		#�R�[�h����
		str = inAry.pack("i*")
		inStrID.write(str)
	end
end

g3d_list = open("g3d_list","w")
anm_arc_list = open("anm_arc_list","w")
debug_txt = open("debug.txt","w")

anm_csv_file = open("bm_anm_tbl.csv","r")

line = anm_csv_file.gets    ## 1�s�ǂݔ�΂�

anime_name_ary = Array.new(0)
anime_list_ary = Array.new(0)
while line = anm_csv_file.gets
	if line =~/^#END/ then
		break
	end

	column = line.split ","

	#�A�j���R�[�h�A�A�j���^�C�v�A���E�t���O�A�A�j���t�@�C������4��z��Ɋi�[
	anime_ary = [ column[1],column[2],column[3],column[4],column[5],column[6],column[7] ]
	anime_list_ary << anime_ary		#�z��Ɋi�[
	for i in [0,1,2,3]
		if column[4+i] != "" then
			anime_name_ary << column[4+i]
		end
	end	#for
end	#while

#�d���폜
anime_name_ary.uniq!
#g3d�R���o�[�^�[�p�̃��X�g���쐬
g3d_ary = anime_name_ary
ica_ary = Array.new(0)
ita_ary = Array.new(0)
itp_ary = Array.new(0)

g3d_ary.each{|index|
	
	if index[/.ica/] != nil then
		ica_ary << index
	elsif index[/.ita/] != nil then
		ita_ary << index
	elsif index[/.itp/] != nil then
		itp_ary << index
	end
}

g3d_list.printf("G3D_ICA = \\\n");
ica_ary.each{|index|
	g3d_list.printf("\t$(DATASRC)/#{index} \\\n")
}
g3d_list.printf("\n");

g3d_list.printf("G3D_ITA = \\\n");
ita_ary.each{|index|
	g3d_list.printf("\t$(DATASRC)/#{index} \\\n")
}
g3d_list.printf("\n");

g3d_list.printf("G3D_ITP = \\\n");
itp_ary.each{|index|
	g3d_list.printf("\t$(DATASRC)/#{index} \\\n")
}

#�A�j���A�[�J�C�u�X�N���v�g�t�@�C���̍쐬
arc_ary = anime_name_ary
arc_ary.each{|index|
	index.sub!(".ica", ".nsbca")
	index.sub!(".ita", ".nsbta")
	index.sub!(".itp", ".nsbtp")
	anm_arc_list.printf("\"g3d_anime_tmp/#{index}\"\n")
}

anm_csv_file.close


model_entry_ary = Array.new(0)
bm_anm_csv_file = open("bm_anime.csv","r")
line = bm_anm_csv_file.gets    ## 1�s�ǂݔ�΂�
while line = bm_anm_csv_file.gets
	if line =~/^#END/ then
		break
	end
	
	column = line.split ","
	entry = [ column[1],column[2] ]
	model_entry_ary << entry
	p entry
end
bm_anm_csv_file.close


#�A�j�����郂�f�����O�f�[�^�ꗗ�����[�h
#���f�����O���X�g�ꗗ�����[�h
model_csv_file = open("build_model.csv","r")

#�A�j�����X�g�A�[�J�C�u�X�N���v�g�t�@�C���쐬
anmlst_arc_list = open("anmlst_arc_list","w")

line = model_csv_file.gets    ## 1�s�ǂݔ�΂�
while line = model_csv_file.gets
	if line =~/^#END/ then
		break
	end
	column = line.split ","
	
	strID = open("bin/#{column[2]}.bin","w")

	#�X�N���v�g�t�@�C���ɒǋL
	anmlst_arc_list.printf("\"bin/#{column[2]}.bin\"\n")

	ary = Array.new(0)

	if column[3] == "1" then
		#�A�j���t���O�������Ă���

		#�X�g�����O�h�c���A�j�����X�g�ɂ��邩������ׂ�
		anm_itm = model_entry_ary.assoc(column[2])
#		p anm_itm
		if anm_itm != nil then
			#�G���g�����X�g�������A�A�j���R�[�h������
			anime = anime_list_ary.assoc(anm_itm[1])
			if anime != nil then
				#�A�j���t���O�𗧂Ă�
				ary = Array(1)
				pack_str = ary.pack("C*")
				strID.write(pack_str)
			
				#�A�j���^�C�v����������
				if anime[1] == "STATION" then
					ary = Array(0)
				elsif anime[1] == "SET_CON" then
					ary = Array(2)
				elsif anime[1] == "ALL_CON" then
					ary = Array(3)
				else
					#�f�o�b�O�e�L�X�g�ɋL��
					ary = Array(0xff)
					debug_txt.printf("#{anime[1]}:#{column[2]}�̃A�j���[�V�����^�C�v�w�肪����������܂���\n")
				end
				pack_str = ary.pack("C*")
				strID.write(pack_str)
			
				#���E�t���O����������
				ary = Array(anime[2].to_i)
				pack_str = ary.pack("C*")
				strID.write(pack_str)
				#4�o�C�g���E�̂��߂̃_�~�[�f�[�^����������
				ary = Array(0)
				pack_str = ary.pack("C*")
				strID.write(pack_str)

				#�A�j���i���o�[����������4�܂�
				for i in [0,1,2,3]
					anime_no = anime_name_ary.index(anime[3+i])
					if anime_no != nil then
						ary = Array(anime_no)
					else	
						ary = Array(0xffffffff)	#�R�[�h����
					end
					pack_str = ary.pack("i*")
					strID.write(pack_str)
				end
			else
				if anm_itm[1] == "ANIME_NONE" then
					#�A�j�������Ƃ���
					set_none_anime_data(ary, strID)
					debug_txt.printf("#{column[2]}:�A�j���R�[�h�w�肪����������܂���\n")
				else
					#���ʂł��Ȃ��A�j���R�[�h���w�肳��Ă���̂ŁA�f�o�b�O�e�L�X�g�ɋL��
					#�A�j�������Ƃ���
					set_none_anime_data(ary, strID)
					debug_txt.printf("#{anm_itm[1]}:#{column[2]}�̃A�j���R�[�h�w�肪����������܂���\n")
				
				end
			end
		else 
			#�A�j�����X�g�ɖ����̂ŁA�A�j���Ȃ��Ƃ݂Ȃ�
			set_none_anime_data(ary, strID)
			debug_txt.printf("#{column[2]}:�A�j�����X�g�ɓo�^����Ă��܂���\n")
		end
	else
		#�A�j���t���O�������Ă��Ȃ�
		set_none_anime_data(ary, strID)
	end
	strID.close
end


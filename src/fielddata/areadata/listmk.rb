#�@�������F�ǂݎ�茳�t�@�C��
#�@�������F�ǉ��p�X
#�@��O�����F�쐬�t�@�C��
arg = $*
f = open(arg[0]) # ���[�h�ȗ����� "r" �ŃI�[�v�������
target = open(arg[2],"w")

while line = f.gets
	if line =~/ / then
		break
	end
	
	path = "\""
	path.concat(arg[1])
	path.concat("/")
	line[0..0] = path	
	target.puts line
end

target.close
f.close


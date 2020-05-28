#
#  base_trap_info_make.rb
#
#  �g�p���@�Fruby base_trap_info_make.rb <base_trap.txt>
#         (�n���f�ޕ\ �^�u��؂�̃e�L�X�g�t�@�C��)
#

#  �����Ώۏ��i�̃f�[�^�o��
#
def _changeStoneParam(stoneName, minNum, maxNum, output, count)
  begin
    stoneNo = 0
	case stoneName
	when "���񂲂��_�}"
	  stoneNo = 1
	when "����^�}"
	  stoneNo = 2
	when "�������^�}"
	  stoneNo = 3
	when "�������^�}"
	  stoneNo = 4
	when "�݂ǂ�_�}"
	  stoneNo = 5
	when "�����_��"
	  stoneNo = 6
    when ""
	  stoneNo = 0
	else
	  print "Error: " + "not convert stone : count = #{count}" + "\n"
	  exit(-1)
    end
	if maxNum == ""
		maxNum = 0
	end
	if minNum == ""
		minNum = 0
	end
	output.printf "\t\t{ #{stoneNo} , #{minNum}, #{maxNum} },\n"
  end
end

## ���C�����[�`��

trap_list = open("trap_info.dat","w")

trap_list.printf("//���̃t�@�C���̓R���o�[�^�[�ɂ�萶������܂� base_trap_info_make.rb\n");
trap_list.printf("//�n���g���b�v�̌����Ή��f�[�^�t�@�C���ł�\n");
trap_list.puts "static const TRAP_SHOP_INFO TrapShopInfo[] = "
trap_list.puts "{"
trap_list.puts "\t\t{0,0,0},  // �_�~�["


while f = ARGV.shift
	file_name = f
	csv_file = open(file_name,"r")
	line = csv_file.gets    ## ��s�ǂݔ�΂�
	line = csv_file.gets

	count = 0;
	while line = csv_file.gets
		if line =~/^#END/ then
			break
		end
		
		column = line.split "\t"
		name = column[1]
		item = column[0]

		if item == "" then
			break
		end

		_changeStoneParam(column[3],column[4],column[5],trap_list,count)
		trap_list.puts "\t\t\t\t\t\t\t\t\t//#{count}:#{name}"
		
		count = count+1
	end
	csv_file.close
end


trap_list.puts "};"
trap_list.close

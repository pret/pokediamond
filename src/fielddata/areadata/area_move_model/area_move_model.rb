#---------------------------------------------------
#
#	@brief	�G���A���̓��샂�f�����X�g�����p�X�N���v�g
#	@file	area_move_model.rb
#	@date	2005.11.24
#	@author	tamada GAME FREAK Inc.
#
#	@param	ARGV[0]	�^�[�Q�b�g��`�o�͐�t�@�C����	
#	@param	ARGV[1]	�A�[�J�C�u�Ώے�`�t�@�C����
#	@param	ARGV[2]	�G���A�Ǘ��\�t�@�C����
#	@param	ARGV[3]	���샂�f���Ǘ��\�t�@�C����
#
#---------------------------------------------------
FIELDOBJ_CODE_HEADER	=	"fieldobj_code.h"
$KCODE = "SJIS"
#---------------------------------------------------
#	�G���A�Ǘ��\�̉���
#---------------------------------------------------
def read_areatable	filename
	arealist = []
	count = 0
	infile = File.open(filename, "r")
	infile.gets		#2�s�ǂݔ�΂�
	infile.gets
	while line = infile.gets
		if line =~ /^AREA_ID_/ then
			areaname = line.split[0].sub(/\AAREA_ID_/, "").downcase
			if arealist.include?(areaname) then
				STDERR.puts "�G���AID�����d��`����Ă��܂�:#{areaname}\n"
			else
				arealist[count] = areaname
				count += 1
			end
		else
			break
		end
	end
	return arealist
end

#---------------------------------------------------
#	�G���A���̃A�Z���u���t�@�C���𐶐�
#---------------------------------------------------
def make_asmfile filename, objlist
	output = ""
	output += "\#	�풓���샂�f����`���X�g:#{filename}\n"
	output += "\t.text\n"
	output += "\#include	\"#{FIELDOBJ_CODE_HEADER}\"\n"
	output += "\n"
	objlist.each {|model|
		name = model.upcase
		if name != model
			STDERR.puts "������������܂�:#{filename},#{model}\n"
		end
		output += "\t.short\t#{model}\n"
	}
	output += "\n"
	output += "	.short	OBJCODEMAX\n"
	output += "\n"
end

#---------------------------------------------------
#	���샂�f�����X�g�̏����ꂽ�t�@�C��������
#---------------------------------------------------
def read_area_movemodel filename
	areadata = {}
	infile = File.open(filename, "r")

	while line = infile.gets
		#	"#end"�Ŏn�܂�ꍇ�A�f�[�^�I�[�Ƃ݂Ȃ�
		if line =~/^#end/ then break end
		#	"#"�Ŏn�܂�ꍇ�R�����g�s�Ƃ��ēǂݔ�΂�
		if line =~ /^#/ then next end

		column = line.split
		areaname = column[0].downcase
		if areadata.key? areaname
			STDERR.puts "�G���A�����d�����Ă���̂ŃX�L�b�v���܂��F#{areaname}\n"
			next
		end
		areadata[areaname] = make_asmfile areaname, column[1..column.length - 1]
	end

	infile.close
	return areadata
end

#---------------------------------------------------
#---------------------------------------------------
def make_listfile srcfilename, arcfilename, arealist
	srcfile = File.open(srcfilename, "w")
	arcfile = File.open(arcfilename, "w")

	srcfile.puts "#�����������ꂽ�t�@�C���ł�\n"
	srcfile.puts "SRCFILES	=	\\\n"

	arealist.each {|name|
		srcfile.puts "\t#{name}.s \\"
		arcfile.puts "\"#{name}.bin\"\n"
	}

	srcfile.puts "\n"
	srcfile.close
	arcfile.close
end

#---------------------------------------------------
#---------------------------------------------------
def make_area_asm_files arealist, areadata
	dummy_list = []
	arealist.each {|areaname|
		sfile = File.open(areaname + ".s", "w")
		if areadata.key?(areaname) then
			sfile.puts areadata[areaname]	
		else
			STDERR.puts "�f�[�^���Ȃ��̂Ń_�~�[�𐶐����܂��F#{areaname}\n"
			sfile.puts "#{make_asmfile areaname, dummy_list}\n"
		end
		sfile.close
	}
end

#---------------------------------------------------
#---------------------------------------------------
def check_entry_area arealist, areadata
	areadata.each{|key, value|
		unless arealist.include?(key) then
			puts "���݂��Ȃ��G���A�̒�`������܂�\t#{key}\n"
		end
	}
end
#---------------------------------------------------
#	���C��������т���
#---------------------------------------------------
arealist = read_areatable ARGV[2]
areadata = read_area_movemodel ARGV[3]

make_listfile ARGV[0], ARGV[1], arealist
make_area_asm_files arealist, areadata
check_entry_area arealist, areadata


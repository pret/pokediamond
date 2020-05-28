arg = $*

$model_list = arg[0]	#�z�u���f���Ǘ��e�L�X�g�p�X
$bmarc_list = arg[1]	#�z�u���f���f�[�^�A�[�J�C�u���X�g�e�L�X�g�p�X
$tsarc_path = arg[2] #�z�u���f���e�N�X�`���Z�b�g�A�[�J�C�u���X�g�e�L�X�g�o�̓p�X
$texmag_path = arg[3]	#�e�N�X�`���}�[�W�v���O�������s�p�X
$orgimd_path = arg[4]	#�I���W�i��imd���\�[�X�p�X
$dmytex_path = arg[5]	#�_�~�[�����p�e���v���[�g�t�@�C���p�X

#���C�u����
require "fileutils"
$KCODE = "SJIS"

#�萔
$TEXSIZE_LIMIT = "71680"	#���~�b�g��70kbyte
#$TEXSIZE_LIMIT = "60000"	#���~�b�g��70kbyte

#�\���̒�`
$_imdList = Struct.new("ImdList", :num, :lst, :outpath, :imdpath)
$_bmList = Struct.new("BuildModelList", :sID, :imdName)

#�A�[�J�C�u�E�e�N�X�`���Z�b�g�������X�g�쐬
$tsArc_list = Array.new
$tsSet_list = Array.new
$bmSet_list = Array.new
File.open($bmarc_list,"r"){ |file|
  while line = file.gets
	line = line.chomp()
	tmp = line.sub(/\.dat/,".nsbtx")
	$tsArc_list << tmp
	tmp = line.gsub(/"/,"")
	tmp1 = tmp.sub(/\.dat/,".imd")
	$tsSet_list << tmp1
	tmp1 = tmp.sub(/tmp\//,"")
	tmp1 = tmp1.sub(/\.dat/,".txt")
	$bmSet_list << tmp1
  end
}

#�z�u���f���Ǘ��e�L�X�g����imd���X�g���o��
class CImdManager
  @@imd_num = 0
  @@imd_name = nil
  @@area_imd = nil
  
  def initialize fpath
	@@imd_num = 0
	@@imd_name = Array.new
	File.open(fpath){ |file|
	  file.gets	#��s�ړǂݔ�΂�
	  while @line=file.gets
		@work = @line.split(",")
		if @work[0] == "#END" then
		  break
		end
		@@imd_name << $_bmList.new
		@cr = @@imd_name.last()
		
		@nwork = @work[1]
		@cr.imdName = @nwork.sub(/\.mb/,".imd")
		@cr.imdName = @cr.imdName.chomp()
		@cr.sID = @work[2].chomp()

		@@imd_num += 1
	  end
	}
  end

  def searchID sid
	for m in @@imd_name do
	  if m.sID == sid then
		return m.imdName
	  end
	end
	return nil
  end
  
  def getImdList txtlst
	@@area_imd = Array.new

	for m in txtlst do
	  @@area_imd << $_imdList.new
	  @cr = @@area_imd.last()
	  @cr.lst = Array.new
	  @cr.num = 0
	  @cr.outpath = m.sub("\.txt","_lst.txt")
	  @cr.imdpath = "tmp/"
	  @cr.imdpath += m.sub("\.txt",".imd")
	 
	  puts m
	  File.open(m,"r"){ |file|
		file.gets
		while @line = file.gets
		  @work = @line.split(",")
		  if @work[0] == "#END" then
			break
		  end

		  @ret = searchID(@work[1].chomp())
		  if @ret == nil then
			@errmsg = "Error : StringID("
			@errmsg += @work[1]
			@errmsg += ") doesn't exists"
			puts @errmsg
			return
		  end
		  @imd = $orgimd_path + @ret
		  @cr.lst << @imd
		  @cr.num += 1
		end
	  }
	end
  end
 
  def outImdList
	for m in @@area_imd do
	  File.open(m.outpath,"w"){ |file|
		file.puts m.num.to_s()
		for n in m.lst do
		  file.puts n
		end
	  }
	end
  end

  def texMagExe
	for m in @@area_imd do
	  if m.num == 0 then
		#�_�~�[�R�s�[
		puts $dmytex_path
		puts m.imdpath
		@dmy = m.imdpath.sub(/\.imd/,".nsbtx")
		puts @dmy 
		FileUtils.cp($dmytex_path,@dmy) 
		next
	  end

	  #�}�[�W
	  @exe_cmd = $texmag_path + " -q -n -o " + m.imdpath + " -S " +  m.outpath + " -L " + $TEXSIZE_LIMIT
	  puts @exe_cmd
	  system(@exe_cmd)
	  if $? == 0x7F00 then
		puts "Error! tex_mag.exe failed"
		return
	  end
	  if $? == 0xFF00 then
		puts "Error! texture marge failed"
		return
	  end
	end
  end

  def outputList g3path,arcpath
	@f_g3 = open(g3path,"w")
	@f_arc = open(arcpath,"w")

	@f_g3.puts "OBJ_TEXSET = \\"
	for m in @@area_imd do
	  @f_arc.puts ("\"" + m.imdpath.sub(/.imd/,".nsbtx") + "\"")
	  if m.num == 0 then
		next
	  end
	  @f_g3.puts ("\t" + m.imdpath + " \\")
	end
	@f_g3.puts "\nOBJ_ARCSET= \\"
	for m in @@area_imd do
	  @buf = m.imdpath.sub(/\.imd/,".nsbtx")
	  @f_g3.puts ("\t" + @buf + " \\")
	end
	@f_g3.puts ""

	@f_g3.close
	@f_arc.close
  end
end
#end class CIMdManager

#���C�����s
def convert
  c_bmObj = CImdManager.new($model_list)
  c_bmObj.getImdList($bmSet_list)
  c_bmObj.outImdList()
  c_bmObj.texMagExe()
  c_bmObj.outputList("g3_texlist",$tsarc_path)
end
#end main
convert	#���s



arg = $*

$model_list = arg[0]	#配置モデル管理テキストパス
$bmarc_list = arg[1]	#配置モデルデータアーカイブリストテキストパス
$tsarc_path = arg[2] #配置モデルテクスチャセットアーカイブリストテキスト出力パス
$texmag_path = arg[3]	#テクスチャマージプログラム実行パス
$orgimd_path = arg[4]	#オリジナルimdリソースパス
$dmytex_path = arg[5]	#ダミー生成用テンプレートファイルパス

#ライブラリ
require "fileutils"
$KCODE = "SJIS"

#定数
$TEXSIZE_LIMIT = "71680"	#リミットは70kbyte
#$TEXSIZE_LIMIT = "60000"	#リミットは70kbyte

#構造体定義
$_imdList = Struct.new("ImdList", :num, :lst, :outpath, :imdpath)
$_bmList = Struct.new("BuildModelList", :sID, :imdName)

#アーカイブ・テクスチャセット生成リスト作成
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

#配置モデル管理テキストからimdリストを出力
class CImdManager
  @@imd_num = 0
  @@imd_name = nil
  @@area_imd = nil
  
  def initialize fpath
	@@imd_num = 0
	@@imd_name = Array.new
	File.open(fpath){ |file|
	  file.gets	#一行目読み飛ばし
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
		#ダミーコピー
		puts $dmytex_path
		puts m.imdpath
		@dmy = m.imdpath.sub(/\.imd/,".nsbtx")
		puts @dmy 
		FileUtils.cp($dmytex_path,@dmy) 
		next
	  end

	  #マージ
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

#メイン実行
def convert
  c_bmObj = CImdManager.new($model_list)
  c_bmObj.getImdList($bmSet_list)
  c_bmObj.outImdList()
  c_bmObj.texMagExe()
  c_bmObj.outputList("g3_texlist",$tsarc_path)
end
#end main
convert	#実行



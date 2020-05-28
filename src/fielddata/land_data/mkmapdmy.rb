#地形用ダミーファイル各種生成
#第一引数 ダミーデータ格納場所への相対パス
#第二引数 バイナリデータ格納場所への相対パス
#第三引数 imdデータ格納場所への相対パス
#第四引数 リストファイルネーム
#第五引数 地形モデルコンパイルリストファイルネーム

require "fileutils"
$KCODE = "SJIS"

#定数定義
ExtAttr = "a.dat"
ExtImd = "c.imd"
ExtBhc = "c.bhc"
ExtObj = "e.dat"
ExtMap = "a.map"
ExtNsbmt = "c.nsbmt"
ExtTmp = ".\."
RangeOutName = "map_tmpo"

s_fmap = "map[0123456789][0123456789]_[0123456789][0123456789]"
s_rmap = "m_*_[0123456789][0123456789]_[0123456789][0123456789]"
s_dmap = "ugmap[0123456789][0123456789]"
s_omap = "ro_*"

###############################################
$lst1
$lst2
$lst3
$lst4

$dmyimd = "map_tmp"
$dmybhc = "map_tmp"
$dmyobj = "map_tmp"
$dmyatr = "map_tmp"

###############################################
arg = $*

fname = "test"
dmypath = arg[0]
dmy_bsp = arg[1]
dmy_isp = arg[2]
file_tmp = arg[3]

if arg.length() < 4 then
  return
end

dmy_name = "map00_00"
file_dir = File.dirname(file_tmp) + "/"

$dmyimd = dmy_name + ExtImd
$dmybhc = dmy_name + ExtBhc
$dmyobj = dmy_name + ExtObj
$dmyatr = dmy_name + ExtAttr

$g3_lst = Array.new
$confList = Array.new
  
cdrive = Dir.pwd

$_idParam = Struct.new("IdParam", :fpath, :id, :no)
$_fileDat = Struct.new("FileDat", :path, :dmy, :mode, :lst, :mk_lst)

#ファイルリストデータ取得
$file_lst = Array.new
$file_ct = 0
File.open(file_tmp,"r"){ |file|
	while line = file.gets
	  tmp = line.split(",")
	  $file_lst << $_fileDat.new
	  m = $file_lst.last()
	  
	  m.path = tmp[0]
	  m.dmy = tmp[1]
	  m.mode = tmp[2].to_i
	  $file_ct += 1
	end
}

#個々のファイルリスト取得
for m in $file_lst do
  File.open(file_dir + m.path,"r"){ |file|
	file.gets
	file.gets
	file.gets

	m.lst = Array.new
	while line = file.gets
	  if line.empty? then
		break
	  end
	  line_tmp = nil
	  line_tmp = line.slice(/#END.*/)
	  if line_tmp != nil then
		break	#終了コード発見
	  end
	  line_buf = line.split(",")
	  m.lst << $_idParam.new
	  n = m.lst.last()
	  n.no = line_buf[0]
	  n.id = line_buf[1]
	  n.fpath = m.path
	end
  }
end

#リストを結合
for m in $file_lst do
  $g3_lst += m.lst
end

#ID衝突検出
$conflictFile = open("result.txt","w")
def IsConflict(name)
  cNum = 0

  for m in $g3_lst do
	if m.id == name.id then
	  if cNum == 1 then
		si = $g3_lst.index(name)
		first = $g3_lst[si]
		$conflictFile.puts first.id + " : " + first.no + " <- " + first.fpath
	  end
	  if cNum > 0 then
		$conflictFile.puts m.id + " : " + m.no + " <- " + m.fpath
		$confList << name.id
	  end
	  cNum += 1
	end
  end

  if cNum < 2 then
	return 0
  end
  return 1
end

#makeリスト作成
for m in $g3_lst do
  #過去のリストになければ衝突検索
  if $confList.include?(m.id)== FALSE then
	ret = IsConflict(m)

	if ret == 1 then
	  puts "ERROR! ID is conflict -> " + m.id + " : " + m.no + " -> " + m.fpath
	end
  end
end
$conflictFile.close

=begin
f = open(fname+"1.txt","w")
for m in $file_lst do
  for n in m.lst do
	f.puts n
  end
end
f.close
=end
=begin
f = open(fname+"1.txt","w")
for m in $g3_lst do
  f.puts m.id 
end
f.close
=end

#存在しているimdファイルリストを取得
Dir.chdir(dmy_isp){
  tmp = s_fmap+ExtImd
  $lst1 = Dir.glob(tmp)
  tmp = s_rmap+ExtImd
  $lst2 = Dir.glob(tmp)	
  tmp = s_dmap+ExtImd
  $lst3 = Dir.glob(tmp)	
  tmp = s_omap+ExtImd
  $lst4 = Dir.glob(tmp)	
}
imd_lst = $lst1+$lst2+$lst3+$lst4
imd_lst.map!{|wk| wk.sub(/#{ExtImd}/,"")}

=begin
f = open(fname+"2.txt","w")
for m in imd_lst do
  f.puts m
end
f.close
=end

#存在しないファイルをリスト
for m in $file_lst do
  m.mk_lst = Array.new
  for n in m.lst do
	if imd_lst.include?(n.id) == FALSE then
	  m.mk_lst << $_idParam.new
	  obj = m.mk_lst.last()
	  obj.id = n.id
	  obj.no = n.no
	  obj.fpath = n.fpath
	end
  end
end

=begin
$mk_lst = Array.new
for m in $g3_lst do
  if imd_lst.include?(m)==FALSE then
	  $mk_lst << m
	end
end
=end

=begin
f = open(fname+"3.txt","w")
for m in $file_lst do
  for n in m.mk_lst do
	f.puts n
  end
end
f.close
=end

#存在しないファイルを作成
for m in $file_lst do
  d_path = dmypath + m.dmy
  make_ct = 1;
  puts "Dummy creation start -> " + m.path
  puts "  range out start no ="+m.mode.to_s

  if m.mk_lst.length == 0 then
	puts "  There is no ID for dummy creation"
	next
  end
  for k in m.mk_lst do
	n = k.id
	if k.no.to_i == m.mode then
	  d_path = dmypath + RangeOutName	#範囲外ダミー
	  puts "HIT! range out start!"
	end

	#imdデータダミー
	path = dmy_isp+n+ExtImd
	if FileTest.exist?(path)==FALSE then
	  FileUtils.cp(d_path+ExtImd,path)
	  puts "new file = " + path
	end
	#高さデータダミー
	path = dmy_bsp+n+ExtBhc
	if FileTest.exist?(path)==FALSE then
	 FileUtils.cp(d_path+ExtBhc,path) 
	 puts "new file = " + path
	end
	#配置モデルデータダミー
	path = dmy_bsp+n+ExtObj
	if FileTest.exist?(path)==FALSE then
	 FileUtils.cp(d_path+ExtObj,path) 
	 puts "new file = " + path
	end
	#attrデータダミー
	path = dmy_bsp+n+ExtAttr
	if FileTest.exist?(path)==FALSE then
	 FileUtils.cp(d_path+ExtAttr,path) 
	 puts "new file = " + path
	end
  end
end

#地形用ダミーファイル各種生成
#第一引数 ダミーデータ格納場所への相対パス
#第二引数 バイナリデータ格納場所への相対パス
#第三引数 imdデータ格納場所への相対パス
#第四引数 地形モデルコンパイルリストファイルネーム

require "fileutils"

#定数定義
Dmyimd = "map_tmpc.imd"
Dmybhc = "map_tmpc.bhc"
Dmyobj = "map_tmpe.dat"

ExtAttr = "a.dat"
ExtImd = "c.imd"
ExtBhc = "c.bhc"
ExtObj = "e.dat"
ExtTmp = ".\."
s1 = "map[0123456789][0123456789]_[0123456789][0123456789]"
s2 = "m_*_[0123456789][0123456789]_[0123456789][0123456789]"

###############################################
$lst1
$lst2
###############################################
arg = $*

fname = "test"
dmypath = arg[0]
dmy_bsp = arg[1]
dmy_isp = arg[2]
map_lst = arg[3]

for m in arg do
  if m == nil then
	return
  end
end

cdrive = Dir.pwd
Dir.chdir(dmy_bsp){
  tmp = s1+ExtAttr
  $lst1 = Dir.glob(tmp)
  tmp = s2+ExtAttr
  $lst2 = Dir.glob(tmp)
}
atr_lst = $lst1+$lst2
atr_lst.map!{|wk| wk.sub(/#{ExtAttr}/,"")}

f = open(map_lst,"w")
f.puts "G3D_GROUND = \\"
for m in atr_lst do
  f.puts "\t$(DATASRC)/"+m+ExtImd+" \\"
end
f.puts "\n"
f.close

#f = open(fname+"1.txt","w")
#for m in atr_lst do
  #  f.puts m
  #end
  #f.close

Dir.chdir(dmy_isp){
  tmp = s1+ExtImd
  $lst1 = Dir.glob(tmp)
  tmp = s2+ExtImd
  $lst2 = Dir.glob(tmp)	
}
imd_lst = $lst1+$lst2
imd_lst.map!{|wk| wk.sub(/#{ExtImd}/,"")}

#f = open(fname+"2.txt","w")
#for m in imd_lst do
  # f.puts m
  #end
  #f.close

#存在しないファイルをリスト
$mk_lst = Array.new
for m in atr_lst do
  if imd_lst.include?(m)==FALSE then
	  $mk_lst << m
	end
end

#f = open(fname+"3.txt","w")
#for m in $mk_lst do
  #  f.puts m
  #end
  #f.close

#存在しないファイルを作成
for m in $mk_lst do
	#高さデータダミー
	path = dmy_bsp+m+ExtBhc
	if FileTest.exist?(path)==FALSE then
	 FileUtils.cp(dmypath+Dmybhc,path) 
	end
	#配置モデルデータダミー
	path = dmy_bsp+m+ExtObj
	if FileTest.exist?(path)==FALSE then
	 FileUtils.cp(dmypath+Dmyobj,path) 
	end
	#imdデータダミー
	path = dmy_isp+m+ExtImd
	if FileTest.exist?(path)==FALSE then
	 FileUtils.cp(dmypath+Dmyimd,path) 
	end
end


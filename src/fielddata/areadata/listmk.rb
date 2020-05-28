#　第一引数：読み取り元ファイル
#　第二引数：追加パス
#　第三引数：作成ファイル
arg = $*
f = open(arg[0]) # モード省略時は "r" でオープンされる
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


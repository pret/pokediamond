# --------------------------------------------------------------
# xMAPファイル
# --------------------------------------------------------------


if ARGV.length!=1 then
	printf "何バイト以上のモジュールを探すか数値をいれてください\n"
	printf "ruby map_check.rb サイズ"
	exit
end

# 比較するモジュールのサイズを引数から取得
objsize = ARGV[0].to_i

File.open("bin/ARM9-TS/Release/main.nef.xMAP"){|file|
#File.open(ARGV[0]){|file|
	while line = file.gets
#		p line
#		if /\A#>/ =~ line then
		if /\A\s+[0-9A-F].*\s[0-9A-F].*/ =~ line then
			temp = line.split(nil)
			size =  temp[1].hex
			if size > objsize then
				p line
			end
		end
	end
}
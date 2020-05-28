#
#  treasure_info_make.rb
#
#  使用方法：ruby treasure_info_make.rb <base_goods.txt>
#         (地下素材表 タブ区切りのテキストファイル)
#

#  交換対象商品のデータ出力
#
def _changeStoneParam(stoneName, minNum, maxNum, output, count)
  begin
    stoneNo = 0
	case stoneName
	when "こんごうダマ"
	  stoneNo = 1
	when "しらタマ"
	  stoneNo = 2
	when "あかいタマ"
	  stoneNo = 3
	when "あおいタマ"
	  stoneNo = 4
	when "みどりダマ"
	  stoneNo = 5
	when "ランダム"
	  stoneNo = 6
    when ""
	  stoneNo = 0
	else
	  stoneNo = 0
	  maxNum = 0
	  minNum = 0
    end
	if maxNum == ""
		maxNum = 0
	end
	if minNum == ""
		minNum = 0
	end
	output.printf "\t\t{ #{stoneNo} , #{minNum}, #{maxNum} },  "
  end
end

## メインルーチン

trap_list = open("treasure_info.dat","w")

trap_list.printf("//このファイルはコンバーターにより生成されます treasure_info_make.rb\n");
trap_list.printf("//地下トラップの交換対応データファイルです\n");
trap_list.puts "static const TREASURE_SHOP_INFO TreasureShopInfo[] = "
trap_list.puts "{"
trap_list.puts "\t\t{0,0,0},  // ダミー"


while f = ARGV.shift
	file_name = f
	csv_file = open(file_name,"r")
	line = csv_file.gets    ## 二行読み飛ばし
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

		_changeStoneParam(column[8],column[9],column[10],trap_list,count)
		trap_list.puts "//#{count}:#{name}"
		
		count = count+1
	end
	csv_file.close
end


trap_list.puts "};"
trap_list.close

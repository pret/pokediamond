#
#  base_goods_info_make.rb
#
#  使用方法：ruby base_goods_info_make.rb <base_goods.txt>
#         (地下素材表 タブ区切りのテキストファイル)
#


#  メッセージのデータ出力
#
def _changeMessageParam(gmmName,output,worldflg,lareflg)
  begin
	if gmmName == ""
		gmmName = "0"
	end
	if gmmName == "null"
	  gmmName = "0"
	end
	output.printf "\t\t{ #{gmmName} }, { #{worldflg} }, { #{lareflg} }\n"
  end
end

#  交換対象商品のデータ出力
#
def _changeStoneParam(stoneName, minNum, maxNum, output, count, money)
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
    when ""
	  stoneNo = 0
	else
	  stoneNo = 0
    end
	if maxNum == ""
		maxNum = 0
	end
	if minNum == ""
		minNum = 0
	end
	if money == ""
		money = 0
	end
	output.printf "\t\t{ #{stoneNo} , #{minNum}, #{maxNum} },\n"
	output.printf "\t\t{ #{money} },\n"

  end
end

## メインルーチン

goods_list = open("goods_size_info.dat","w")
goods_id_def = open("goods_id_def.h","w")

goods_list.printf("//このファイルはコンバーターにより生成されます base_goods_info_make.rb\n");
goods_list.printf("//地下秘密基地のグッズのあたりなどのデータファイルです\n");
goods_list.puts "static const GOODS_SIZE_INFO GoodsSizeInfo[] = "
goods_list.puts "{"

goods_id_def.printf("//このファイルはコンバーターにより生成されます base_goods_info_make.rb\n");
goods_id_def.printf("//地下秘密基地のグッズの種類を定義したファイルです\n");
goods_id_def.printf("#ifndef __GOODS_ID_DEF_H__\n");
goods_id_def.printf("#define __GOODS_ID_DEF_H__\n\n");

goods_id_def.printf("#define GOODS_NONE	(0)\n");

count = 0;

while f = ARGV.shift
	file_name = f
	csv_file = open(file_name,"r")
	line = csv_file.gets    ## 二行読み飛ばし
	line = csv_file.gets

	#ダミー作成
	goods_list.puts "\t{"
	goods_list.puts "\t\t0,0,"
	goods_list.printf "\t\t{"
	for i in [0,1,2,3,4,5,6,7,8]
		goods_list.printf "0, "
	end
	goods_list.printf "},\n"
	goods_list.printf "\t\t{0,0,0},\n"
	goods_list.printf "\t\t{0},\n"
	goods_list.printf "\t\t{0},{0},{0}\n"
	goods_list.puts "\t},\t\t\t\t\t\t\t\t\t//0:ダミー"
	
	while line = csv_file.gets
		if line =~/^#END/ then
			break
		end
		
		column = line.split "\t"

		name = column[1]

		goods_str_id = column[2]
		if goods_str_id != nil then
			goods_str_id.upcase!
		end
		goods_id_def.printf("#define GOODS_%s	(%d) // %s\n", goods_str_id, count+1, name);

		#縦横サイズを計算	["", "\"", "横幅", ",", "縦幅", "\""]
		size_str = column[10]
		size_str_ary = size_str.split(/(")|(,)/)
		width = size_str_ary[2].to_i
		depth = size_str_ary[4].to_i

		hit_val = []
		for i in [0,1,2,3,4,5,6,7,8]
			hit_val << column[11+i].to_i
		end

		item = column[0].to_i
		goods_list.puts "\t{"
		goods_list.puts "\t\t#{width},#{depth},"
		goods_list.printf "\t\t{"
		for i in [0,1,2,3,4,5,6,7,8]
			goods_list.printf "#{hit_val[i]}, "
		end
		goods_list.printf "},\n"
		_changeStoneParam(column[5],column[6],column[7],goods_list,count,column[20])
		_changeMessageParam(column[21], goods_list, column[23], column[24])
		goods_list.puts "\t},\t\t\t\t\t\t\t\t\t//#{count+1}:#{name}"
		
		count = count+1
	end
	csv_file.close
end

count = count+1
goods_id_def.printf("#define GOODS_TYPE_MAX	(#{count})\n");

goods_id_def.printf("\n");
goods_id_def.printf("#endif //__GOODS_ID_DEF_H__\n");
goods_id_def.close

goods_list.puts "};"
goods_list.close

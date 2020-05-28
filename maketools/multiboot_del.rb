#!/usr/bin/ruby
#
#      Nitroからmultiboot lib を除去する   2006.05.03
#
#puts "#{ARGV.length}"
#ARGV.each{|a| puts"#{a}"}


#--
# 環境変数から目的ファイルの位置を作成する
#--
def getCommondefsFileName

    fileName = ENV["NITROSDK_ROOT"]
	fileName = fileName + "\\build\\buildtools\\commondefs"
	return fileName
end

#--
# ファイルを開き、引数のlibを探す
#--
def searchTargetLib( filenName , libName )

	File.open( filenName ).each do |line|
		unless ( /#{libName}/ =~ line )
    		next
	    end
		if ( /^#/ =~ line )
    		next
	    end
		return true
	end
	return false
end


#--
# 別のファイルにライブラリが無いものを作る
#--
def createRemoveFile( filenName , libName , newFileName)

	$fs = File.new(newFileName, "w")

	File.open( filenName ).each do |line|
		unless ( /#{libName}/ =~ line )
			$fs.puts(line)
    		next
	    end
		if ( /^#/ =~ line )
			$fs.puts(line)
    		next
	    end
	end

end

#--
# ファイルを変えてしまう   前のは・・・残しておく
#--

def replaceFile(fileName, newFileName, oldFileName)

	File.rename(fileName, oldFileName)
	File.rename(newFileName, fileName)

end


begin

	$fileName = getCommondefsFileName
	if searchTargetLib($fileName, "libmb")
		$newFileName = $fileName + "__"
		$oldFileName = $fileName + "_old"
		createRemoveFile($fileName, "libmb", $newFileName)
		replaceFile($fileName, $newFileName, $oldFileName)
		p "libmb" + " delete"
    end

end

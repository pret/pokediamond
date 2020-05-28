#!/usr/bin/ruby
#
#      Nitro����multiboot lib ����������   2006.05.03
#
#puts "#{ARGV.length}"
#ARGV.each{|a| puts"#{a}"}


#--
# ���ϐ�����ړI�t�@�C���̈ʒu���쐬����
#--
def getCommondefsFileName

    fileName = ENV["NITROSDK_ROOT"]
	fileName = fileName + "\\build\\buildtools\\commondefs"
	return fileName
end

#--
# �t�@�C�����J���A������lib��T��
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
# �ʂ̃t�@�C���Ƀ��C�u�������������̂����
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
# �t�@�C����ς��Ă��܂�   �O�̂́E�E�E�c���Ă���
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

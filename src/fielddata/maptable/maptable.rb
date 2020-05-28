###############################################################
#
#
#		ゾーン管理表コンバータ
#
#		sousuke tamada	GAME FREAK Inc.
#
#		2005.10.12	仮完成
#
#
###############################################################

#------------------------------------------------
#------------------------------------------------
class ColumnID

	attr :cZONE_ID, true
	attr :cAREA_ID, true
	attr :cMOVEMODEL, true
	attr :cMATRIX, true
	attr :cEVENT, true
	attr :cSCRIPT, true
	attr :cMSG, true
	attr :cENCOUNT, true
	attr :cMAPTYPE, true
	attr :cBICYCLE, true
	attr :cDASH, true
	attr :cESCAPE, true
	attr :cFLY, true
	attr :cBGM_DAY, true
	attr :cBGM_NIGHT, true
	attr :cWEATHER, true
	attr :cCAMERA, true
	attr :cBATTLEBG, true
	attr :cNAME, true
	attr :cCOMMENT, true

	def setup column
		c_count = 0;
		column.each { |item|
			case item
			when "ID"
				@cZONE_ID = c_count
			when "MAPRESOURCE"
				@cAREA_ID = c_count
			when "MOVE_MODEL"
				@cMOVEMODEL = c_count
			when "MATRIX"
				@cMATRIX = c_count
			when "event"
				@cEVENT = c_count
			when "script"
				@cSCRIPT = c_count
			when "msg"
				@cMSG = c_count
			when "encount"
				@cENCOUNT = c_count
			when "maptype"
				@cMAPTYPE = c_count
			when "bicycle"
				@cBICYCLE = c_count
			when "dash"
				@cDASH = c_count
			when "escape"
				@cESCAPE = c_count
			when "fly"
				@cFLY = c_count
			when "BGM_DAY"
				@cBGM_DAY = c_count
			when "BGM_NIGHT"
				@cBGM_NIGHT = c_count
			when "WEATHER"
				@cWEATHER = c_count
			when "CAMERA"
				@cCAMERA = c_count
			when "BATTLE_BG"
				@cBATTLEBG = c_count
			when "PLACE_NAME"
				@cNAME = c_count
			when "備考"
				@cCOMMENT = c_count
			end
			c_count += 1
		}
	end

end




###############################################################
#
#
#
###############################################################

class OutputFile
	def initialize fname
		@fp = File.open(fname, "w")
		@name = fname
		putHeader
	end

	def putHeader
		@fp.puts "//#{Time.now.ctime}"
		@fp.puts "//#{@name}"
	end

	def putFooter
		@fp.puts "//#{@name}"
	end

	def close
		putFooter
		@fp.close
	end

end
###############################################################
#
#		ZoneData配列生成
#
###############################################################

class ZoneDataFile < OutputFile

	#------------------------------------------------
	#------------------------------------------------
	def putHeader
		@fp.puts "static const ZONE_DATA ZoneData[] = {\n"
	end

	def putFooter
		@fp.puts "};\n"
	end

	def ox2bool str, id
		case str
		when "○"
			"TRUE"
		when "×"
			"FALSE"
		else
			STDERR.puts "#{id}:#{str}:想定外の入力があります\n"
			"FALSE"
		end
	end

	#------------------------------------------------
	#
	#	ゾーンごとのデータ出力
	#
	#------------------------------------------------
	def putLine cl, linecount, column
		id = column[cl.cZONE_ID]
		if id == "END"
			return "END"
		end
		area = column[cl.cAREA_ID]
		if !(area =~ /^AREA_ID_/) then
			STDERR.puts "エリアの指定がおかしい!:#{area}:\n"
			exit 1
		end
		movemodel = column[cl.cMOVEMODEL]
		matrix = "MATRIX_ID_#{column[cl.cMATRIX]}".upcase

		event_id = if column[cl.cEVENT] != "○" then
				"NARC_zone_event_zone_dummy_total_bin" 
			else
				"NARC_zone_event_zone_#{id.downcase}_total_bin"
			end
		script = column[cl.cSCRIPT] == "○" ? "NARC_scr_seq_#{id.downcase}_bin" : "scr_dummy"
		sp_script = column[cl.cSCRIPT] == "○" ? "NARC_scr_seq_sp_#{id.downcase}_bin" : "sp_scr_dummy"
		msg = column[cl.cMSG] == "○" ? "NARC_msg_#{id.downcase}_dat" : "msg_dummy"
		bgm_day = column[cl.cBGM_DAY]
		bgm_night = column[cl.cBGM_NIGHT]
		weather = "WEATHER_SYS_#{column[cl.cWEATHER].upcase}"
		camera = "#{column[cl.cCAMERA]}"
		battle_bg = "#{column[cl.cBATTLEBG]}"
		if !(battle_bg =~ /^BG_ID_/) then
			STDERR.puts "戦闘背景の指定がおかしい！:#{battle_bg}:#{id.upcase}\n"
			exit 1
		end
		name = column[cl.cNAME].upcase
		encount_id = case column[cl.cENCOUNT]
			when "○"
				"NARC_enc_data_#{id.downcase}enc_bin"
			else
				"enc_dummy"
			end
		maptype = column[cl.cMAPTYPE]
		if !(maptype =~ /^MAPTYPE_/) then
			STDERR.puts "マップタイプの指定がおかしい!:#{maptype}:\n"
		end
		dash_flag = ox2bool column[cl.cDASH], id
		bicycle_flag = ox2bool column[cl.cBICYCLE], id
		escape_flag = ox2bool column[cl.cESCAPE], id
		fly_flag = ox2bool column[cl.cFLY], id


	@fp.puts <<DOCUMENT
	{//ZONE_ID_#{id.upcase} = #{linecount}
		#{area.upcase},
		#{movemodel.upcase},
		#{matrix},
		#{script},
		#{sp_script},	//#{sp_script},
		#{msg},
		#{bgm_day},
		#{bgm_night},
		#{encount_id},
		#{event_id},
		#{name},
		#{weather},
		#{camera},
		#{maptype},
		#{battle_bg},
		#{bicycle_flag},
		#{dash_flag},
		#{escape_flag},
		#{fly_flag},
	},
DOCUMENT
		return id.upcase
	end

end

###############################################################
#
#	ゾーン名テーブルデータ生成
#
###############################################################
class ZoneNameFile < OutputFile
	def putHeader
		@fp.puts "static const char * const ZoneName[] = {\n"
	end
	def putFooter
		@fp.puts "};\n"
	end
	def putLine zone_id
		@fp.puts "\t\"#{zone_id}\",\n"
	end
end

###############################################################
#
#	ゾーンID定義ヘッダ生成
#
###############################################################

class ZoneIDFile < OutputFile

	def putHeader
		@fp.puts "//zone id define table\n"
		#@fp.puts "//#{Time.now.ctime}"
		@fp.puts "\#ifndef __ZONE_ID_H__\n"
		@fp.puts "\#define __ZONE_ID_H__\n"
		#@fp.puts "enum {\n"
	end

	def putFooter
		#	@fp.puts "};\n"
		@fp.puts "\#endif // __ZONE_ID_H__\n"
		@fp.puts "\n"
	end

	#----------------------------------------
	#	ゾーンごとのID
	#----------------------------------------
	def putLine zone_id, linecount
		@fp.puts "\#define ZONE_ID_#{zone_id} (#{linecount})\n"
		#@fp.puts "\tZONE_ID_#{zone_id} = #{linecount},\n"
	end

end

###############################################################
#
#	ゾーン毎イベント定義生成
#
###############################################################
class ZoneEventFile < OutputFile
	def putHeader
		@fp.puts "# zone event list start\n"
		@fp.puts "CONVSRCS	=	\\\n"
		@fp.puts "	zone_dummy_total.c \\\n"
	end
	def putLine	id
		@fp.puts "	zone_#{id.downcase}_total.c \\\n"
	end
	def putFooter
		@fp.puts "\n"
		@fp.puts "# zone event list end\n"
	end
end

class ZoneEventArcFile < OutputFile
	def putHeader
		@fp.puts "\"zone_dummy_total.bin\"\n"
	end
	def putLine id
		@fp.puts "\"zone_#{id.downcase}_total.bin\"\n"
	end
	def putFooter
	end
end

###############################################################
#	マップ接続定義ヘッダのインクルード生成
###############################################################
class ZoneEventDoorHeader < OutputFile
	def putHeader
		@fp.puts "//#{@name}"
	end
	def putLine id
		@fp.puts "#include \"zone_#{id.downcase}evd.h\"\n"
	end
end

###############################################################
#
###############################################################
class ZoneMsgHeader < OutputFile
	def putHeader
		@fp.puts "/* convert header file */"
	end
	def putLine id
		@fp.puts "#include \"../../../include/msgdata/msg_#{id.downcase}.h\"\n"
	end
end

###############################################################
###############################################################
def filediff file1,file2
	f1 = File.open(file1,"r")
	l1 = f1.read
	f1.close
	f2 = File.open(file2,"r")
	l2 = f2.read
	f2.close
	return (l1 != l2)
end

def diff_overwrite new_file, old_file
	if FileTest.exist? old_file then
		if filediff(old_file,new_file) == true then
			#差分があった場合は更新
			File.delete old_file
			File.rename new_file, old_file
		else
			#差分がなかった場合はnew_fileを削除
			File.delete new_file
		end
	else
		#zone_id.hが存在しない場合はnew_fileをold_fileにリネーム
		File.rename new_file, old_file
	end
end

###############################################################
###############################################################
class ZoneNameBinaryFile < OutputFile
	def initialize fname
		@fp = File.open(fname, "w")
		@name = fname
	end

	def putHeader
	end

	def putFooter
	end

	def close
		@fp.close
	end

	def put	zone_id
		if zone_id.length <= 16 then
			@fp.syswrite zone_id
			blank = ""
			blank << 0
			blank *= (16 - zone_id.length)
			@fp.syswrite blank
		end
	end
end


###############################################################
#
#		ここからメイン
#
###############################################################
def convert
	#idfile = ZoneIDFile.new("zone_id.h")
	idfile = ZoneIDFile.new("temp_zone_id.h")
	datafile = ZoneDataFile.new("maptable.dat")
	namefile = ZoneNameFile.new("mapname.dat")
	namebinfile = ZoneNameBinaryFile.new("mapname.bin")
	eventfile = ZoneEventFile.new("eventlist.txt")
	evarcfile = ZoneEventArcFile.new("eventarc.txt")
	#doorheader = ZoneEventDoorHeader.new("doorevent.h")
	doorheader = ZoneEventDoorHeader.new("temp_doorevent.h")
	msgheader = ZoneMsgHeader.new("temp_msgheader.h")

	firstline = gets
	cl = ColumnID.new
	cl.setup firstline.split
	#setup cl, firstline.split


	linecount = 0
	while line = gets
		column = line.split
		id = column[cl.cZONE_ID].upcase
		if id == "END"
			#終端定義
			idfile.putLine "MAX", linecount
			break
		end
		datafile.putLine cl, linecount, column
		namefile.putLine id
		namebinfile.put id
		idfile.putLine id, linecount
		if column[cl.cEVENT] == "○" then
			eventfile.putLine id
			evarcfile.putLine id
			doorheader.putLine id
		end
		if column[cl.cMSG] == "○" then
			msgheader.putLine id
		end
		linecount += 1
	end


	datafile.close
	namefile.close
	namebinfile.close
	idfile.close
	eventfile.close
	evarcfile.close
	doorheader.close
	msgheader.close

	diff_overwrite "temp_zone_id.h", "zone_id.h"
	diff_overwrite "temp_doorevent.h", "doorevent.h"
	diff_overwrite "temp_msgheader.h", "msg_header.h"

	STDERR.puts "zonetable.xlsをコンバートしました\n"
end

convert


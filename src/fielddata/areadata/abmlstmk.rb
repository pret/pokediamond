arg = $*

abm = File.open(arg[1],"w")

abm.puts "AREABM_LIST = \\\n"

File.open(arg[0],"r"){ |file|
  file.gets
  file.gets
  while line = file.gets
	column = line.split "\t"
	abm.puts "\t$(AREABM_ROOT)/#{column[1]} \\\n"
  end
}
abm.puts ""
abm.close


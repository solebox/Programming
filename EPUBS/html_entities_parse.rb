require 'htmlentities'
coder = HTMLEntities.new
File.open("html_entities_parse.dat").each_line {|line| 
    puts coder.encode(coder.decode(line.chomp),:decimal)
}





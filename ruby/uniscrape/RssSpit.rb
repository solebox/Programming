#!/usr/bin/env ruby1.9.1
class RssSpit
    attr_accessor :channel,:version,:items,:filename
    def initialize(filename,version="2.0") 
        @filename = filename
        @version = version
        @channel = {:title => "default",:link => "http://channel.com/chan.xml",
                    :description => "channel description",
                    :lastBuildDate => Time.now }
        @items = []
        # item = {title=>"",link=>"",description=>"",pubDate=>"",image=>"",\
        #         lecturer=>"",course=>"",docType=""}
    end
    def makeFile
        file = File.open(@filename,"w")
        file.puts("<rss version="+'"'+@version+'"'+">")
            file.puts("\t"+"<channel>")
                file.puts("\t\t"+"<title>"+channel[:title]+"</title>")
                file.puts("\t\t"+"<link>"+channel[:link]+"</link>")
                file.puts("\t\t"+"<description>"+channel[:description]+"</description>")
                file.puts("\t\t"+"<lastBuildDate>"+channel[:lastBuildDate].to_s+"</lastBuildDate>")
                #now to the item making
                    putItems(file,2)
            file.puts("\t"+"</channel>")
        file.puts("</rss>")
        file.close
    end
    def putItems(file,indent)
        @items.each do |item|
            file.puts("\t"*indent+"<item>")
            item.each { |k,v|
                if k.class == Symbol
                    file.puts("\t"*(indent+1)+"<"+k.to_s+">"+v.to_s+"</"+k.to_s+">")
                else
                    file.puts("\t"*(indent+1)+"<"+k+">"+v+"</"+k+">")
                end
            }
            file.puts("\t"*indent+"</item>")
        end
    end
end
#usage example
rss = RssSpit.new("rss_sample.xml")
rss.channel = {:title => "My Title", 
               :link => "http://mylink.com", 
               :description => 'my description',
               :lastBuildDate => Time.now.to_s}
rss.items << {:title => "im an item", :link => "http://item.com",:description => "an item",
                  :pubDate => Time.now.to_s, :image => "http://imgr.com/dfsfe.jpg",:lecturer => "dr sus",
                  :course => "criminology", :docType => "docx"}
rss.items << {:title => "im an item", :link => "http://item.com",:description => "an item",
                  :pubDate => Time.now.to_s, :image => "http://imgr.com/dfsfe.jpg",:lecturer => "dr sus",
                  :course => "criminology", :docType => "docx"}
rss.makeFile()

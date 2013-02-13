# encoding: UTF-8
RUPIN_URL = "http://www.rup.co.il"
RUPIN_DEFAULT_RSS_FILENAME = "rupin_rss.xml"
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
class Rupin 
    PHP_GET = "/ruppin?page="
    def initialize(rssOutPutDefaultFilename=RUPIN_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
        @last_page = 0
    end
    def gatherDataFromPage(page_number)
       begin
        doc = Nokogiri::HTML(open(RUPIN_URL+PHP_GET+page_number.to_s))
        data = []
        posts = doc.xpath('//div[@class="node"]')
        posts.each do |post|
           ul = post.children[5].children[0]
           data << {:title => post.children[1].children[0].text,
                    :link => RUPIN_URL + post.children[1].children[0].attribute('href'),
                    :description => ul.children[2].text,
                    :docType => ul.children[4].text
                   }
                    if ul.children[6].text.match(/\d+/) then
                        data.last.merge!({:pubDate => ul.children[6].text})
                    else
                        data.last.merge!({:pubDate => ""})
                    end
        end
            return data
       rescue
        puts "failed to get page: "+RUPIN_URL+PHP_GET+page_number.to_s
        a = []
        return a
       end
    end
    def rupRape
       doc = Nokogiri::HTML(open(RUPIN_URL+PHP_GET+1.to_s)) 
       last_page = doc.xpath('//li[@class="pager-last last"]/a')[0].attribute("href").to_s.scan(/\d+/)[0].to_i
        (0..last_page-1).each do |page_num|
            puts "parsing page number: "+(page_num+1).to_s
            @data << gatherDataFromPage(page_num)
        end
    end
    def toRss
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Rupin Academic Archive",
                       :link => RUPIN_URL,
                       :description => "The Rupin Archive",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data.flatten
       rss.makeFile
    end
end

#shitzorz = Rupin.new
#shitzorz.rupRape
#shitzorz.toRss

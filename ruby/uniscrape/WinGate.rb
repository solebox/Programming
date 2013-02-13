# encoding: UTF-8
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
WINGATE_DEFAULT_RSS_FILENAME = "wingate_rss.xml"
WINGATE_URL = "http://www.agudawin.com"
class WinGate
    PHP_GET = "/29_"
    def initialize(rssOutPutDefaultFilename=WINGATE_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
        @post_date
    end
    def gatherDataFromPages
        doc = Nokogiri::HTML(open(WINGATE_URL+PHP_GET))
        data = []
        years = doc.xpath('//ul[@class="nav articleview"]/li')
        categories = []
        years.each do |post|
            shana = post.search("h3").text
            @post_date = post.search("small").text.gsub(%r"תאריך:","")
            parseCat(post.search("a").attribute("href")) #dig in the year super subjects
        end
    end
    def parseCat(cat)
        links = []
        begin
            doc = Nokogiri::HTML(open(cat))
            doc.xpath('//ul[@class="nav contentview"]/li/a').each do |a|
                links << a.attribute("href")
            end
        rescue
            puts "parseCat for: "+cat+" has failed miserably"
        end
        links.each {|subcat| 
            begin 
                parseSubCategories(subcat)
            rescue
                puts "parseSubCategories for: "+subcat+" has failed."
            end
        }
    end
    def parseSubCategories(subcat)
        posts = []
        doc = Nokogiri::HTML(open(subcat))
        doc.xpath('//ul[@class="nav contentview"]/li').each do |li|
            @data << {:course => li.search("a").text,
                     :description => li.search("p").text,
                     :link => subcat.to_s}
            #:date => @post_date /*but they are all the same lol */
        end
    end
    def toRss 
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Wingate Academic Archive",
                       :link => WINGATE_URL,
                       :description => "The Wingate Archive",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
end

#shitzorz = WinGate.new
#shitzorz.gatherDataFromPages
#shitzorz.toRss

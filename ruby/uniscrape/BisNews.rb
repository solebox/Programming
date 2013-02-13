# encoding: UTF-8
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
BIS_NEWS_DEFAULT_RSS_FILENAME = "bis_news_rss.xml"
BIS_NEWS_URL = 'http://www.bis.org.il/news_inc.asp?sub_topic_id='
class BisNews
    def initialize(rssOutPutDefaultFilename=BIS_NEWS_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage
        doc = Nokogiri::HTML(open(BIS_NEWS_URL),nil,'windows-1255')
        data = []
        script = doc.css('script')[0]
        script.text.scan(/^\s+messages.+/).each {|msg|
            data << msg.scan(/\<br\>.+\<br\>/)[0].to_s.gsub(/\<\/b\>/," <\/b>")
        }
        data.each { |line|
            doc = Nokogiri::HTML(line)
            lnk = doc.xpath('//a')
            @data << {:title => doc.text.gsub("מידע נוסף"," "),
                      :link =>  lnk[0] ? lnk.attribute('href') : "#"  }
        }
    end
    def toRss 
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Bis News",
                       :link => BIS_NEWS_URL,
                       :description => "The Bis News",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
end

#shitzorz = BisNews.new
#shitzorz.gatherDataFromPage
#shitzorz.toRss

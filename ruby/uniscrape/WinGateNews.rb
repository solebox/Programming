
# encoding: UTF-8
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
WINGATE_NEWS_DEFAULT_RSS_FILENAME = "wingate_news_rss.xml"
WINGATE_NEWS_URL = "http://www.agudawin.com"
class WinGateNews
    PHP_GET = "/news"
    def initialize(rssOutPutDefaultFilename=WINGATE_NEWS_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage
        doc = Nokogiri::HTML(open(WINGATE_NEWS_URL+PHP_GET))
        data = []
        news = doc.xpath('//ul[@class="nav articleview"]/li/a')
        categories = []
        news.each do |post|
            @data << {:title =>  post.search('h3').text,
                      :description =>  post.search('p').text.strip,
                      :link => post.attribute('href'),
                      :pubDate => post.search('small').text.scan(%r"\d\d\/\d\d\/\d\d")[0]}
        end
    end
    def toRss 
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Wingate News",
                       :link => WINGATE_NEWS_URL,
                       :description => "Wingate News",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
end

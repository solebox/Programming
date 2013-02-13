# encoding: UTF-8
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
RUPIN_NEWS_DEFAULT_RSS_FILENAME = "rupin_news_rss.xml"
RUPIN_NEWS_URL = 'http://www.rup.co.il'
class RupinNews
    def initialize(rssOutPutDefaultFilename=RUPIN_NEWS_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage
        doc = Nokogiri::HTML(open(RUPIN_NEWS_URL),nil,'UTF-8')
        data = []
        news_posts = doc.css('div.view-content div.node')
        news_posts.each do |post|
            ttl =  post.at_css('h2.title')
            @data << {:title => ttl.text,
                      :link => RUPIN_NEWS_URL + ttl.child.attribute('href').text }
                     # :description => post.at_css('div.content1').text }
        end
    end
    def toRss 
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Rupin News",
                       :link => RUPIN_NEWS_URL,
                       :description => "The Rupin News",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
end

#shitzorz = RupinNews.new
#shitzorz.gatherDataFromPage
#shitzorz.toRss

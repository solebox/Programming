# encoding: UTF-8
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
AGUDA_NEWS_DEFAULT_RSS_FILENAME = "aguda_org_il_news_rss.xml"
AGUDA_NEWS_URL = 'http://www.aguda.org.il'
class AgudaNews
    def initialize(rssOutPutDefaultFilename=AGUDA_NEWS_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage
        #works
        doc = Nokogiri::HTML(open(AGUDA_NEWS_URL),nil,'UTF-8')
        data = []
        news_posts = doc.xpath('//div[@class="items"]/div')
        news_posts.each do |post|
           @data << {:link => post.children[0].attribute('href').to_s,
            :image => post.children[0].child.attribute('src').to_s,
            :title => post.children[1].text}
        end
    end
    def toRss 
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Aguda News",
                       :link => AGUDA_NEWS_URL,
                       :description => "Aguda News",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
end

#shitzorz = AgudaNews.new
#shitzorz.gatherDataFromPage
#shitzorz.toRss

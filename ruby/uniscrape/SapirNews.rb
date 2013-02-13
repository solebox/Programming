# encoding: UTF-8
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
SAPIR_NEWS_DEFAULT_RSS_FILENAME = "sapir_news_rss.xml"
SAPIR_NEWS_URL = 'http://www.sapir-aguda.co.il'
class SapirNews
    def initialize(rssOutPutDefaultFilename=SAPIR_NEWS_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage
        doc = Nokogiri::HTML(open(SAPIR_NEWS_URL),nil,'UTF-8')
        data = []
        news_posts = doc.xpath('//div[@class="catItemView groupLeading catItemIsFeatured"]')
        
        news_posts.each do |post|
            image = post.children[15].children[7].children[1].children[1]
           date =  post.css('span.catItemDateCreated')
            @data << {:title => post.css('h3.catItemTitle').children[1].text,#attribute('href') #h3
                      :pubDate => date.nil? ? "" : date.text.strip,
                      :link => SAPIR_NEWS_URL + post.css('h3.catItemTitle').children[1].attribute('href'),
                      :image =>  image.nil? ? "" : image.children[1].attribute('src')
                     #post.children[17].attribute('class') #div@class itemlinks
                     }
        end
    end
    def toRss 
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Sapir News",
                       :link => SAPIR_NEWS_URL,
                       :description => "The Sapir News",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
end

#shitzorz = SapirNews.new
#shitzorz.gatherDataFromPage
#shitzorz.toRss

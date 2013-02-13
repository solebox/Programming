# encoding: UTF-8
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
ARIEL_NEWS_DEFAULT_RSS_FILENAME = "ariel_news_rss.xml"
ARIEL_NEWS_URL = "http://www.yosh4u.co.il/"
class ArielNews
    def initialize(rssOutPutDefaultFilename=ARIEL_NEWS_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage
        doc = Nokogiri::HTML(open(ARIEL_NEWS_URL),nil,'UTF-8')
        data = []
        news_posts = doc.xpath('//div[@id="TopArticles"]/div/table/tr')
        
        news_posts.each do |post|
            @data << {:image =>  ARIEL_NEWS_URL+post.child.child.next.attribute('src'),
                      :title => post.child.next.next.children[1].children[1].text,
                      :description =>  post.child.next.next.children[1].children[3].text,
                      :link =>  ARIEL_NEWS_URL+post.child.next.next.children[1].children[1].attribute("href") }
        end
    end
    def toRss 
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Ariel News",
                       :link => ARIEL_NEWS_URL,
                       :description => "The Ariel News",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
end

#shitzorz = ArielNews.new
#shitzorz.gatherDataFromPage
#shitzorz.toRss

# encoding: UTF-8
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
HAFAKULTA_NEWS_DEFAULT_RSS_FILENAME = "hafakulta_news_rss.xml"
HAFAKULTA_NEWS_URL = 'http://www.hafakulta.org'
class HafakultaNews
    def initialize(rssOutPutDefaultFilename=HAFAKULTA_NEWS_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage
        doc = Nokogiri::HTML(open(HAFAKULTA_NEWS_URL),nil,'UTF-8')
        data = []
        news_posts = doc.xpath('//div[@class="blog"]/div')
        news_posts.each do |post|
           if post.attribute('class').to_s == 'article_row cols1 clearfix'
             if !(post.css('div.article-content').children[1].children[0].name == 'a')
               @data << {:title => post.at_css('h2.contentheading a.contentpagetitle').text.strip,
                         :link => HAFAKULTA_NEWS_URL+post.at_css('h2.contentheading a.contentpagetitle').attribute('href').to_s.strip,
                         :description => post.at_css('div.article-content').text.strip }
             end
           end
        end
    end
    def toRss 
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Hafakulta News",
                       :link => HAFAKULTA_NEWS_URL,
                       :description => "Hafakulta News",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
end

#shitzorz = HafakultaNews.new
#shitzorz.gatherDataFromPage
#shitzorz.toRss


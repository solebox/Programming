# encoding: UTF-8
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
ORANIM_NEWS_DEFAULT_RSS_FILENAME = "oranim_news_rss.xml"
ORANIM_NEWS_URL = 'http://www.oranim.ac.il/sites/heb/aguda/pages/default.aspx'
class OranimNews
    def initialize(rssOutPutDefaultFilename=ORANIM_NEWS_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage
        doc = Nokogiri::HTML(open(ORANIM_NEWS_URL),nil,'UTF-8')
        data = []
        news_posts = doc.css('div.ms-WPBody')
        turk_encounters = 0
        in_range = false
        news_posts.each do |post|
           p =  post.at_css("div.AgudaTurkTitle540")
           p.nil? ? "none" : p
           if p.nil? && turk_encounters == 1 then
                if !post.at_css("td.dotBorder").nil? then
                    msg_title_n_body = post.at_css("td.dotBorder font")
                    
                    img = post.at_css("img.Aguda")
                    title = msg_title_n_body.at_css("strong").text 
                    a = ""
                    a = msg_title_n_body.at_css("a") 
                    a = a.text unless a.nil?
                    body = msg_title_n_body.text.gsub(title,"")
                    body = msg_title_n_body.text.gsub(a,"") unless a.nil? 
                    img =  img.attribute("src") unless img.nil?
                    @data << { :title => title, 
                               :link => ORANIM_NEWS_URL,
                               :description => body,
                               :image => img}
                end
           end 
           turk_encounters+=1 unless p.nil?
        end
    end
    def toRss 
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Oranim News",
                       :link => ORANIM_NEWS_URL,
                       :description => "The Oranim News",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
end

#shitzorz = OranimNews.new
#shitzorz.gatherDataFromPage
#shitzorz.toRss

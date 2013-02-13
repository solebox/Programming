# encoding: UTF-8
NUIS_URL = "http://www.nuis.co.il"
NUIS_DEFAULT_RSS_FILENAME = "nuis_newsrip_rss.xml"
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
class Nuis 
    def initialize(rssOutPutDefaultFilename=NUIS_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
    end
    def gatherDataFromPage
        doc = Nokogiri::HTML(open(NUIS_URL))
        data = []
        posts = doc.xpath('//marquee/div/a[@class="latestnews-blacknews"]')
        posts.each do |a| 
            title =  a.text.strip
            link = NUIS_URL+a.attribute('href')
            data << {:title => title,:link => link }
        end
        return data
    end
    def toRss(data)
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Nuis news",
                       :link => NUIS_URL,
                       :description => "The Nuis News",
                       :lastBuildDate => Time.now.to_s}
        rss.items = data
        rss.makeFile
    end
    def getNewsAndMakeRss
        data = gatherDataFromPage
        toRss(data)
    end
end


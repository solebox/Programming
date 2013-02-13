# encoding: UTF-8
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
HAMISHPAT_DEFAULT_RSS_FILENAME = "hamishpat_rss.xml"
HAMISHPAT_URL = 'http://hamishpat.com'
SIDE_BAR_URL = 'http://hamishpat.com/bar.html'

class Hamishpat 
    def initialize(rssOutPutDefaultFilename=HAMISHPAT_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage
        pre = HAMISHPAT_URL+'/'
        doc = Nokogiri::HTML(open(SIDE_BAR_URL),nil,'windows-1255')
        posts = doc.xpath('//table/tr/td')
        posts.each do |post|
            cat =  post.css('p')
            if cat[0] then
                sub_cat = post.at_css('table')
                sub_cat.css('td').each { |sc|
                    sc_a =  sc.at_css('a')
                    if sc_a then
                      if post.children.length == 7 then
                          @data << {:title =>  sc_a.at_css('font').text,
                                    :link => pre+sc_a.attribute('href').to_s,
                                    :category =>  cat[1].text.strip,
                                    :pubDate => fetchPubDate(sc_a.attribute('href').to_s)}
                      else
                          @data << {:title =>  sc_a.at_css('font').text,
                                    :link => pre+sc_a.attribute('href').to_s,
                                    :category => cat[0].at_css('a').at_css('font').text.strip,
                                    :pubDate => fetchPubDate(sc_a.attribute('href').to_s)}
                      end
                    end
                }
            end
        end
    end
    def toRss 
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Hamishpat Archive",
                       :link => HAMISHPAT_URL,
                       :description => "Hamishpat Archive",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
    def fetchPubDate(link) 
       begin
        doc = Nokogiri::HTML(open(HAMISHPAT_URL+'/'+link),nil,'windows-1255')
        doc.xpath('//span[@lang="he"]').each {|post|
            if post.text.match("עדכון אחרון:") then
                return post.parent.text.gsub("עדכון אחרון:","")
            end
        }
       rescue
        puts "failed to fetch date from: #{HAMISHPAT_URL+'/'+link}. it probably didnt load , lol fuck it"
       end
        return "" 
    end
end

#shitzorz = Hamishpat.new
#shitzorz.gatherDataFromPage
#shitzorz.toRss

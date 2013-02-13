# encoding: UTF-8
EMEK_URL = "http://www.emeky.co.il"; BB_DEFAULT_RSS_FILENAME = "berl_rss.xml"
BBERL_URL = "http://www.agudabb.co.il"; EMEK_DEFAULT_RSS_FILENAME = "emek_israel_rss.xml"
BERL_PHP_GET = "/berl?page="; EMEK_PHP_GET = "/classes?page="
BET_BERL = "Beit Berl" 
EMEK = "Emek Izrael"
require 'nokogiri'
require 'open-uri'
class BBEmek
    attr_reader :target
    attr_accessor :rssOutPutDefaultFileName
    def initialize(target)
        @target = target
        @data = [] 
        case target
        when BET_BERL
           @url = BBERL_URL 
           @php_get = BERL_PHP_GET
           @rssOutPutDefaultFileName = BB_DEFAULT_RSS_FILENAME
        when EMEK
           @url = EMEK_URL
           @php_get = EMEK_PHP_GET
           @rssOutPutDefaultFileName = EMEK_DEFAULT_RSS_FILENAME
        else
            raise "INVALID TARGET FOR CLASS BBEmek CANNOT INITIALIZE"
        end
    end
    def gatherDataFromPage(page_number)
        doc = Nokogiri::HTML(open(@url+@php_get+page_number.to_s))
        data = []
        posts = doc.xpath('//div[@class="node"]/div[@class="art-post"]/div/div')
        case @target
        when EMEK
            posts.each do|post| 
                data << {:title => post.children[1].children[1].attribute('title').to_s , 
                         :link => @url+post.children[1].children[1].attribute('href').to_s,
                         :description => post.children[7].text.to_s.gsub(%r"\S+:","").gsub("קובץ מצורף","").gsub("|","").strip
                        }
            end
        when BET_BERL
            posts.each do |post|
               pname =  post.children[5].children[3].children[0].text.split(":")
               pname[1].gsub!(/\n/,"")
               pname = pname[1].scan(/\S+/)
               data << {:title => post.children[1].children[1].attribute('title').to_s,
                        :link => @url+post.children[1].children[1].attribute('href').to_s,
                        :description => post.children[9].text.to_s.gsub(%r"\s+תגיות","").gsub("|","").strip,
                        :pubDate => post.children[3].text.split(",")[1].split("|")[0],#date (& poster's name)
                        :lecturer => pname.join(" ") 
                       }
            end
        else
            raise "Cannot Gather Data from Target: "+@target
        end
        return data
    end
end
bbemek = BBEmek.new(EMEK)
puts bbemek.gatherDataFromPage(0)

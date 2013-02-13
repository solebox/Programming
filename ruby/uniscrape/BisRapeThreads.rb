#!/usr/bin/env ruby1.9.1
# encoding: UTF-8 
require 'open-uri'
require 'nokogiri'
load 'RssSpit.rb'
GET_PREFIX = 'http://www.bis.org.il/search_res_bank.asp?PageId='
BIS = "http://www.bis.org.il/"
CURRENT_PAGE_AMOUNT = 81
DEFAULT_BIS_RSS_FILENAME = "bis_org_il.xml"
class BisRape
    def initialize(rssfilename=DEFAULT_BIS_RSS_FILENAME)
        @file = rssfilename
        @rss = RssSpit.new(@file) 
    end
    def rapeIt
        cum = []
        threads = [] 
        for page in (1..CURRENT_PAGE_AMOUNT)
            threads << Thread.new(page) { |mypage|
                begin
                 b = singlePageAttack(GET_PREFIX+mypage.to_s)
                 puts GET_PREFIX+mypage.to_s+" is now being parsed..."
                    if b.length != 0 then
                        cum << b
                    end
                rescue
                    puts "page number: "+mypage.to_s+" dropped."
                end
            } 
         end
         threads.each {|aThread| aThread.join}
        rssTheBitch(cum.flatten) #we dont care for pages
    end
    def singlePageAttack(url)
       doc = Nokogiri::HTML(open(url),nil,'WINDOWS-1255')
       arr = []
       elements = doc.xpath('//table[@class="tab_b"]')
       
        elements.each do |element|
            #if doclink = %r"download_Img.asp\?file_name=\d{1,20}.pdf".match(element.attribute('onclick').to_s) then
                arr << BIS + url #+ doclink.to_s
            #end
            element.search('font').to_a.each do |i|
                if !%r"\|".match(i) then
                arr << i.to_html(:encoding => 'UTF-8').to_s.gsub(%r"\<font\sclass\=\"w3\">|\<[\/]font\>","")
                end
            end
            arr << "\n"
        end
        return arr
    end
    def rssTheBitch(arr)
       @rss.channel = {:title => "Bar Ilan Feed",
                      :link => BIS,
                      :description => "I hate Windows-1255",
                      :lastBuildDate => Time.now.to_s}
        sub_arr = []
        arr.each do |entry|
            sub_arr << arr.shift
            if sub_arr.last == "\n" and sub_arr.length < 8 then
                sub_arr = []
            elsif sub_arr.last == "\n"
                @rss.items << toRss(sub_arr)
                sub_arr = []
            end
        end
        @rss.makeFile
    end
    def toRss(arr)
       items = {:title => arr[5].to_s,
                     :link => arr[0].to_s,
                     :description => "",
                     :pubDate => arr[3].to_s, 
                     :image => "",
                     :lecturer => arr[4].to_s,
                     :course => arr[5].to_s, 
                     :docType => arr[0].to_s.scan(%r"\.([pPdD][oOdD][cCfF])").flatten[0]}
      return items
    end
end
#rape = BisRape.new
#rape.rapeIt

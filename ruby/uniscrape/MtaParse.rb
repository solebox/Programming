#!/usr/bin/ruby1.9.1
#encoding: UTF-8
MTA_URL = "http://www.aguda-mta.com"
MTA_DEFAULT_RSS_FILENAME = "aguda_mta_rss.xml"
require 'nokogiri'
require 'open-uri'
load 'RssSpit.rb'
class MtaParse
    ASSAYS_LOCATION = "/site/View_Files.aspx?rowIndex=183"
    def initialize(rssOutPutDefaultFilename=MTA_DEFAULT_RSS_FILENAME)
        @rssFileName = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage
        doc = Nokogiri::HTML(open(MTA_URL+ASSAYS_LOCATION),nil,'UTF-8')
        data = []
        courseTables = doc.xpath('//table[@class="content"]/tr/td/table/tr/td/table')
        courseTables.each do |table|
            course = table.children[0].children[0].text
            li = table.children[1].children[0].children[1].children
            li.each do |li|
                data << {:course => course, :title => li.text.strip,
                         :link => MTA_URL+ASSAYS_LOCATION}
            end
        end
        @data = data
    end
    def toRss
        rss = RssSpit.new(@rssFileName)
        rss.channel = {:title => "Mta Archive",
                       :link => MTA_URL,
                       :description => "Mta Archive",
                       :lastBuildDate => Time.now.to_s}
       rss.items = @data
       rss.makeFile
    end
end

#shitzorz = MtaParse.new
#shitzorz.gatherDataFromPage
#shitzorz.toRss

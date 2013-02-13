# encoding: UTF-8
GALIL_URL = "http://www.wgalil.com"
MAAGAR = "/65064/%D7%91%D7%A0%D7%A7-%D7%A2%D7%91%D7%95%D7%93%D7%95%D7%AA"

GALIL_DEFAULT_RSS_FILENAME = "galil_rss.xml"
require 'nokogiri'
require 'open-uri'
class Galil 
    def initialize(rssOutPutDefaultFilename=GALIL_DEFAULT_RSS_FILENAME)
        @rss = rssOutPutDefaultFilename
        @data = [] 
    end
    def gatherDataFromPage#(page_number)
        doc = Nokogiri::HTML(open(GALIL_URL+MAAGAR))
        data = []
        maagar_subjects  = doc.xpath('//li[@id="MBVItem769633"]')
        maagar_subjects[0].children[1].children.each do |li|
            a = li.children[0]
            link =  a.attribute('href')
            subject = a.text
            puts subject
        end
        #maagar_subjects.each do |subject|
        #end
    end
end
galil = Galil.new
galil.gatherDataFromPage

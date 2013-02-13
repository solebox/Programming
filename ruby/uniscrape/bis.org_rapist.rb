#!/usr/bin/env ruby1.9.1
# encoding: UTF-8 
#url: http://www.bis.org.il/search_res_bank.asp?PageId=1 
#sample dl url: http://www.bis.org.il/download_Img.asp?file_name=176200826511409.PDF (some idiotic js <table class="tab_b"... onclick=download_Img...
require 'open-uri'
require 'nokogiri'
file = File.new("test_out.txt",'w')
bis = 'http://www.bis.org.il/'
doc = Nokogiri::HTML(open('http://www.bis.org.il/search_res_bank.asp?PageId=2'),nil,'WINDOWS-1255')
elements = doc.xpath('//table[@class="tab_b"]')
arr = []
elements.each do |element|
    #download_Img.asp?file_name=246200855572429.pdf
    if suff = %r"download_Img.asp\?file_name=\d{1,20}.pdf".match(element.attribute('onclick').to_s) then
        arr << bis + suff.to_s
    end
    element.search('font').to_a.each do |i|
        if !%r"\|".match(i) then
        arr << i.to_html(:encoding => 'UTF-8').to_s.gsub(%r"\<font\sclass\=\"w3\">|\<[\/]font\>","")
        end
    end
    arr << "\n"
end
puts arr
#puts elements[0].search('font')#/tr/td/font 
file.close

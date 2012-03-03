#!/usr/bin/env ruby1.9.1
require 'open-uri'
require 'nokogiri'
require 'date'
def scrape(doc)
    entry = doc.children[4].child.child.children[9]
    content_of_elements = []
    images = []
    while entry != nil do
        content_of_elements <<  entry.children[6].text
        entry = entry.next
    end
    content_of_elements.each do |content|
        images << Nokogiri::HTML(content).children[1].search("img")[0][:src]
    end
    return images
end
def getFeedDate(doc)
    str = doc.children[4].child.child.children[3].text
    last_updated =  DateTime.strptime(str,"%Y-%m-%dT%H:%M:%S")
    return last_updated
end
def getLoggedDate
   date = File.open('motifake.log','r').readline
   date = DateTime.strptime(date,"%Y-%m-%dT%H:%M:%S")
   return date
end
doc =  Nokogiri::HTML(open('http://feeds.feedburner.com/motifake'))
feedDate = getFeedDate(doc)
if feedDate > getLoggedDate then
    images = scrape(doc)
    images.each do |image|
        `wget #{image}`
    end
    File.open('motifake.log','w').puts(feedDate.to_s)
else
    puts "nothing to scrape..."
end

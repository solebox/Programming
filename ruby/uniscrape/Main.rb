#!/usr/bin/env ruby1.9.1
$LOAD_PATH << './'
require 'net/ftp'
require 'BisRape.rb'
require 'NuisNews.rb'
require 'Rupin.rb'
require 'WinGate.rb'
require 'MtaParse.rb'
require 'WinGateNews.rb'
require 'ArielNews.rb'
require 'SapirNews.rb'
require 'HafakultaNews.rb'
require 'AgudaNews.rb'
require 'Hamishpat.rb'
require 'BisNews.rb'
require 'RupinNews.rb'
require 'OranimNews.rb'
ADDRESS = "kvrt.co.il"
USER = "kobi@kvrt.co.il"
PASS = "L)t6H]fT=CJR"
 
def main 
   ## Bar Ilan Feed ## 0101 0000 0000 
   begin
    bisrape = BisRape.new
    bisrape.rapeIt
    puts "done raping.."
   rescue
    puts "Bis Parse failed"
   end
   ## Bar Ilan Feed ##
   ## Rupin Feed ## 0101 0000 0000
   begin
    rupin = Rupin.new
    rupin.rupRape
    rupin.toRss
   rescue
    puts "rupin parse failed"
   end
   ## Rupin Feed ## 
   ## Wingate Feed ## 0101 0000 0000
   begin
    wingate = WinGate.new
    wingate.gatherDataFromPages
    wingate.toRss
   rescue
    puts "wingate parse failed"
   end
   ## Wingate Feed ##
   ## Mta Archive ## 0101 0000 0000
   begin
    mta = MtaParse.new
    mta.gatherDataFromPage
    mta.toRss
   rescue
    puts "mta parse failed"
   end
   ## Mta Archive ##
   ## Nuis News ## 0001 0000 0000
   begin
    nuis = Nuis.new
    nuis.getNewsAndMakeRss
   rescue 
    puts "nuis news parse failed"
   end
   ## Nuis News ## 
   ## WinGateNews ## 0011 0000 0000 
   begin
    wingatenews = WinGateNews.new
    wingatenews.gatherDataFromPage
    wingatenews.toRss
   rescue
    puts "wingate news parse failed"
   end
   ## WinGateNews
   ## ArielNews ## 0011 0101 0000
   begin
    arielnews = ArielNews.new
    arielnews.gatherDataFromPage
    arielnews.toRss
   rescue
    puts "ariel news parse failed"
   end
   ## ArielNews
   ## SapirNews ## 0011 0101 0000
   begin
    sapirnews = SapirNews.new
    sapirnews.gatherDataFromPage
    sapirnews.toRss
   rescue
    puts "sapir news parse failed"
   end
   ## ArielNews
   ## HafakultaNews ## 0011 0101 0000
   begin
    hafakultanews = HafakultaNews.new
    hafakultanews.gatherDataFromPage
    hafakultanews.toRss
   rescue
    puts "Hafakulta news parse failed"
   end
   ## HafakultaNews ## 
   ## AgudaNews ## 0011 0101 0000 
   begin
    agudanews = AgudaNews.new
    agudanews.gatherDataFromPage
    agudanews.toRss
   rescue
    puts "Aguda news parse failed"
   end
   ## AgudaNews ## 0011 0101 0000
   ## Hamishpat ## 0100 0101 0000
   begin
    hamishpat = Hamishpat.new
    hamishpat.gatherDataFromPage
    hamishpat.toRss
   rescue
    puts "hamishpat news parse failed"
   end
   ## Hamishpat ## 
   ## BisNews ## 0100 0101 0000
   begin
    bisnews = BisNews.new
    bisnews.gatherDataFromPage
    bisnews.toRss
   rescue
    puts "bis news parse failed"
   end
   ## bis news ## 
   ## RupinNews ## 0101 0000 0000
   begin
    rupinnews = RupinNews.new
    rupinnews.gatherDataFromPage
    rupinnews.toRss
   rescue
    puts "rupin news parse failed"
   end
   ## RupinNews ## 
   ## OranimNews ## 0101 0000 0000 
   begin
    oranimnews = OranimNews.new
    oranimnews.gatherDataFromPage
    oranimnews.toRss
   rescue
    puts "oranim news parse failed"
   end
   ## OranimNews ## 
  
    ftp = Net::FTP.open(ADDRESS,USER,PASS) do |ftp|
     ftp.passive = true
     begin
        ftp.puttextfile(File.absolute_path(DEFAULT_BIS_RSS_FILENAME))
        puts "bis rss sent"
     rescue
        puts "bis rss failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(RUPIN_DEFAULT_RSS_FILENAME))
        puts "Rupin Rss Feed Sent"
     rescue
        puts "Rupin Rss failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(WINGATE_DEFAULT_RSS_FILENAME))
        puts "Wingate Rss Feed Sent"
     rescue
        puts "wingate rss failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(MTA_DEFAULT_RSS_FILENAME))
        puts "Mta Rss Feed Sent"
     rescue
        puts "Mta rss failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(NUIS_DEFAULT_RSS_FILENAME))
        puts "Nuis News rss sent"
     rescue
        puts "Nuis news failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(WINGATE_NEWS_DEFAULT_RSS_FILENAME))
        puts "WinGate News rss sent"
     rescue
        puts "WinGate news failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(ARIEL_NEWS_DEFAULT_RSS_FILENAME))
        puts "Ariel News rss sent"
     rescue
        puts "Ariel news failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(SAPIR_NEWS_DEFAULT_RSS_FILENAME))
        puts "Sapir News rss sent"
     rescue
        puts "sapir news failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(HAFAKULTA_NEWS_DEFAULT_RSS_FILENAME))
        puts "Hafakulta News rss sent"
     rescue
        puts "Hafakulta news failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(AGUDA_NEWS_DEFAULT_RSS_FILENAME))
        puts "Aguda News rss sent"
     rescue
        puts "Aguda news failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(HAMISHPAT_DEFAULT_RSS_FILENAME))
        puts "Hamishpat Archive rss sent"
     rescue
        puts "Hamishpat Archive failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(BIS_NEWS_DEFAULT_RSS_FILENAME))
        puts "bis news rss sent"
     rescue
        puts "bis news failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(RUPIN_NEWS_DEFAULT_RSS_FILENAME))
        puts "rupin news rss sent"
     rescue
        puts "rupin news failed to send"
     end
     begin
        ftp.puttextfile(File.absolute_path(ORANIM_NEWS_DEFAULT_RSS_FILENAME))
        puts "oranim news rss sent"
     rescue
        puts "oranim news failed to send"
     end
    end
end

main

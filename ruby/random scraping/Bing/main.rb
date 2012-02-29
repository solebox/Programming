#!/usr/bin/ruby
require 'rubygems'
load 'BingStalker.rb'
arr = []
File.foreach('config.ini') do |line|
	arr << line.chomp.split('::').pop
end
banger = BingStalker.new(arr[0],arr[1].to_f,arr[2],arr[3],arr[4].to_i,arr[5].to_i) #appID,probability,wordlist,datafile,resultcount=5,derivedStringCount=max  (var=value means that value is the default)
	banger.multisnd(arr[6].to_i)
print 'program finished'

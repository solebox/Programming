#!/usr/bin/ruby -w
class SearchAndParse
	attr_accessor :keyphrase
	def intialize
		array = @keyphrase.split(/\s+/)
	end
	def spit
		array.each {|i| puts i}
	end
end

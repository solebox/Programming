#!/usr/bin/ruby -w
 
def array(array)
	array.each { |num| puts num.to_s(base=2) }	
end

def number(num)
	puts num.to_s(base=2)	
end
# 	     -1 	-2 	   -3 	      -4         -5 #after left docking
array = [4294967295,4294967294,4294967294,4294967292,4294967294]
array(array)

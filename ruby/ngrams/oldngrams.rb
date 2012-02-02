#!/usr/bin/ruby1.9.1
bi_grams = Hash.new(0)
tri_grams = Hash.new(0)
quad_grams = Hash.new(0)
penta_grams = Hash.new(0)
hexa_grams = Hash.new(0)
str = File.read('sample.txt').scan(/\S+/)
num = str.length-6
num.times do |i|
    bi = str[i] + ' ' + str[i+1]
    tri = bi + ' ' + str[i+2]
    quad = tri + ' ' + str[i+3]
    penta = quad + ' ' + str[i+4]
    hexa = penta + ' ' + str[i+5]
    bi_grams[bi] += 1
    tri_grams[tri] += 1
    quad_grams[quad] += 1
    penta_grams[penta] += 1
    hexa_grams[hexa] += 1
end
bb = bi_grams.sort {|a,b| b[1] <=> a[1]}
tt = tri_grams.sort {|a,b| b[1] <=> a[1]}
qq = quad_grams.sort {|a,b| b[1] <=> a[1]}
pp = penta_grams.sort {|a,b| b[1] <=> a[1]}
hh = hexa_grams.sort {|a,b| b[1] <=> a[1]}

bb.each {|k,v|
#    puts "#{k} : #{v}"
}
tt.each {|k,v|
 #   puts "#{k} : #{v}"
}
qq.each {|k,v|
  #  puts "#{k} : #{v}"
}
pp.each {|k,v|
  #  puts "#{k} : #{v}"
}
hh.each {|k,v|
#    puts "#{k} : #{v}"
}

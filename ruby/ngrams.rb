#!/usr/bin/ruby1.9.1
#my optimized ngrams
FILENAME = 'sample.txt' #around 6000 words
def ngrams(n)
    str = File.read(FILENAME).scan(/\S+/)
    grams = []
    2.upto(n) {|i| grams[i] = Hash.new(0)}
    (str.length-n).times do |i|
        grams[2][gi = str[i]+' '+str[i+2]] += 1
        3.upto(n) { |j|
                grams[j][gi+' '+str[i+j-1]] += 1
        } 
    end
    return grams
end
ngrams(6) #returns a hexagram array in 1.83 seconds on my machine :)

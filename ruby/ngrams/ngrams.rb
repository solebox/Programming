#!/usr/bin/ruby1.9.1
#my optimized ngrams
FILENAME = 'sample.txt' #around 6000 words
#this method returns an array from 2 up to n of hashes in which reside 
#all possible ngrams and their corresponding instance count
def ngrams(n)
    str = File.read(FILENAME).scan(/\S+/)
    grams = []
    2.upto(n) {|i| grams[i] = Hash.new(0)}
    (str.length-n).times do |i|
        grams[2][gi = str[i]+' '+str[i+1]] += 1
        3.upto(n) { |j|
                grams[j][gi = gi+' '+str[i+j-1]] += 1
        } 
    end
    return grams
end
#returns one hash of just the wanted ngram without the preceeding ones
# for speed and space optimization and more specific usage
def ngram(n)
    str = File.read(FILENAME).scan(/\S+/)
    ngram = Hash.new(0)
    (str.length - n).times do |i| 
        ng = str[i..i+n-1].join(" ")
        ngram[ng] += 1
    end
    return ngram
end
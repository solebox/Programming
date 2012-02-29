#!/usr/bin/ruby
require 'rbing'

class BingStalker
	def initialize(appID,probability,wordlist,datafile,resultcount=5,derivedStringCount=0)
		@appID = appID #fixme 
		@probability = probability #probability (of 0.75^i if not specified)not to add an additional word (start string 2 words)
		@datafile = datafile#the file that hosts the resulting data
		@resultcount = resultcount #guess ;)
		@params = "" #search parameters i.e lang:en AND OR so forth (you can see the potential here no?)
		   	     # the format of the resulting query -"@params+' '+query"
		@dscount = derivedStringCount
		@wordlistarray = File.read(wordlist).split("\n")
		@maxidle = 5 #random wait in seconds from num/2.0 to num (betweed derived string searches)
	end
	def multisnd(num)
		datafile = File.new(@datafile,"a")
		num.times do 
			seekAndDestroy(RBing.new(@appID),datafile)
		end
		datafile.close
	end
	def seekAndDestroy(bing=RBing.new(@appID),datafile) #search them one by one and call the result handler for each separately 
		seed = randomString(@probability,@wordlistarray)
		derivedStrings = createDerivedStringsArray(seed,bing)
		print "your seed is rotten\n" if derivedStrings.empty?
		params = @params+" "
		until derivedStrings.empty?
			searchTerm = derivedStrings.shift
			search = params+searchTerm
		  	resultInfo = bing.web(search,:count => @resultcount)#search it
			puts "searching:#{search}..."
			destroy(seed,searchTerm,resultInfo,datafile)
			idle(@maxidle)
		end

	end
	def destroy(seed,searchTerm,resultInfo,datafile) 
		r = resultInfo['Web']
		finalResultArray = [seed,searchTerm,r['Total'],r['Offset']]
		results = r['Results'].collect {|h| h.values_at('Url','DateTime')}
		finalResultArray << results  ## finalResultArray = [seed,searchTerm,total,offset,[[url,date],[url,date]...]
		writeToFile(finalResultArray,dotComPercent(finalResultArray),datafile)
	end
	
	def randomString(probability=0.75,wordlistarray) #helper:this method creates the random string
		searchParameters = "" #lang:en (loc:US OR loc:GB) !!fixme!! might be deprecated due to irrelevance
		list = wordlistarray
		query = searchParameters+list[rand(list.size)]+" "+list[rand(list.size)]
		rand_f = rand(101)/100.0
		while rand_f > probability
			query += " "+list[rand(list.size)]	
			rand_f = rand(101)/100.0
		end
		return query
	end
	def createDerivedStringsArray(str,bing) # helper:this method creates the new strings using bing
		newstrings = []
		puts "trying to create related_search string array for seed:#{str}..."
		rsp = bing.related_search(str)
		if rsp['RelatedSearch'].nil?
			return []
		else
			rsp['RelatedSearch']['Results'][0..@dscount-1].each do |result|  #0..@dscount-1 (ruby black magic wins)
				newstrings << result['Title']
			end
		end
		return newstrings
	end
	
	def writeToFile(array,dotComPercent,file) #gets [seed,searchTerm,total,offset,[[url,date],[url,date]..] and writes it to file
			file.puts "#{array[0]} #{array[1]}  #{array[2].to_s} #{dotComPercent.to_s}%"
			arr = array[4]
			
			until arr.empty?
				url,date = *arr.shift
				file.puts("    #{url} #{date.to_s}")
			end
	end
	
	def dotComPercent(arr)
		urlarray = arr[4].collect {|v| v[0]}	
		sumOfDotCom = 0
		urlarray.each {|url| sumOfDotCom += 1 if isDotCom(url)}
		return (sumOfDotCom/urlarray.size.to_f)*100
	end
	def isDotCom(url)
		regexp = /^(((http|https):\/\/)|[Ww]{3}\.)([a-z0-9]+([\-\.]{1}[a-z0-9]+)*\.[cC][oO][mM](([0-9]{1,5})?\/.*)?)$/ #i want a rais , regex is evil i spent 10 hours just on this regex
		if url =~ regexp
			return true
		else
			return false
		end
	end
	def idle(num)
			sleep(num/2.0+rand(num-num/2.0))
	end

end

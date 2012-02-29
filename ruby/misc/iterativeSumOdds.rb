def sumodd(a)
	i = 0
	sum = 0
	while i < a.length do
		if a[i].odd?
			sum = sum +a[i]
		end
		i+=1
	end
	print sum
end

a = [1,2,3]
sumodd(a)
 #O(n)

def sort(a)
	b = a.clone
	max = max(a)
	for j in 0..b.length-1 do
		min = max+1
		for i in 0..a.length-1 do
			if a[i] < min
				min = a[i]
				mindex = i
			end
		end
		a[mindex]=max
		b[j] = min
	end
	return b
end

def max(a)
	max = a[1]
	for i in 0..a.length-1 do
		if a[i] > max
			max = a[i]
		end
	end
	return max
end
a = [2,5,4]
puts sort(a)

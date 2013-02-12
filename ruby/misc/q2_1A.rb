def sort(a)
	for j in 0..a.length do
		min = 0
		for i in j..a.length-1 do
			if a[i] < a[min]
				min = i
			end
		end
		swap(a,j,min)
	end
end

def swap(a,j,min)
	temp = a[j]
	a[j] = a[min]
	a[min] = temp
end

alba = [1,4,3,2,7,4,2,1,42,2,5,324,234,23,42,34,32,4]
sort(a)
puts a

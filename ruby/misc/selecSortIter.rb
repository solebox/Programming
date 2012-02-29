def sort(a)
	temp = 999999999
	b = a.clone
	for j in 0..b.length-1 do
			for i in 0..a.length-1 do
				if a[i] < temp 
					temp = a[i]
					z = i
				end
			end
			a[i] = 99999999
		b[j] = temp
		temp = 9999999999
	end
	return b
end

a = [5,4,3,2,1]
print sort(a)

def sort(a,i)
	if i == a.length
		return;
	else
		min = 0
		for j in i..a.length-1 do
			if a[j] < a[min]
				min = j
		end

		temp = a[i]
		a[i] = a[min]
		a[min] = temp
		sort(a,i+1)
	end
end

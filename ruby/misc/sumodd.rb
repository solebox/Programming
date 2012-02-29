
def sumodd(a,p,r)
	q = (p+r)/2
	if p < r
		return sumodd(a,p,q)+sumodd(a,q+1,r)
	else
		if a[q].odd?
			return a[q]
		else
			return 0
		end
	end
end

arr = [1,2,3,5,7,8,1,3,2,2,2,2]

puts sumodd(arr,0,arr.length-1)

	# T(1) = 1
	# T(n) = 2T(n/2)+4

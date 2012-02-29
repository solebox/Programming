def shevet(a,p,r)
	q = (p+r)/2
	if a[q]  == q
		return q
	end
	if p < r
		if a[q] > q 
			return shevet(a,p,q)
		end
		if a[q] < q
			return shevet(a,q+1,r)
		end
	else
		return nil
	end
end

a = [-20,-13,-11,-2,-0,-4,-5,-10,-12,-500,10]
puts shevet(a,0,a.length-1)

	#T(1)=1
	#T(n)=T(n/2)+3

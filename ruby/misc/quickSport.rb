def qs(a,p,r)
	if p < r-5
			q = partition(a,p,r)
			qs(a,p,q)
			qs(a,q+1,r)
	end
end

def partition(a,p,r)
	x = a[p]
	i = p 
 	j = r 
	while i<j do
		until a[j] <= x do
			j = j - 1
		end
		until a[i] >= x do
			i = i + 1
		end
			swap(a,j,i)
	end
	return j

end
def swap(a,j,i)
	temp = a[j]
	a[j] = a[i]
	a[i] = temp 
end

b = [20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1] 
a = [4.4,2,6,9,7,5,8,4,10,3] 
qs(b,0,b.length-1)
print b,"\n"

@counter = 0
def qs(a,p,r)
	if p < r
			q = partition(a,p,r)
			qs(a,p,q)
			qs(a,q+1,r)
	end
end

def partition(a,p,r)
	x = a[p]
	i = p 
 	j = r 
	while true do
		until a[j] <= x do
			j -= 1
			@counter += 1
		end
		until a[i] >= x do
			i += 1
			@counter += 1
		end
		if i<j
			swap(a,j,i)
		else
			return j
		end
	end
end
def swap(a,j,i)
	print a,"\n"
	temp = a[j]
	a[j] = a[i]
	a[i] = temp 
end
def permCounter(arr)
	innercount = 10000000
	permu = arr.permutation
	for seq in permu do
		@counter = 0
		bob = seq.clone
		qs(seq,0,seq.length-1)
		if @counter < innercount
			innercount = @counter
			@lala = bob
		end
	end
	puts innercount
	puts @lala
end

b = [2,1] 
a = [4.4,2,6,9,7,5,8,4,10,3] 
qs(b,0,b.length-1)
print @counter
#permCounter(b)

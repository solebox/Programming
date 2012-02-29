#!/usr/bin/ruby -w

def mergesort(arr)
	if arr.length <= 1
		return arr
	else
		mid = arr.length/2
		left = arr[0,mid]
		right = arr[mid,arr.length]
		left = mergesort(left)
		right = mergesort(right)
		result = merge(left,right)
	end
		return result

end

def merge(left,right)
	sorted = []
	until left.empty? or right.empty?
		if left.first <= right.first
			sorted << left.shift
		else
			sorted << right.shift
		end
	end
		sorted.concat(left).concat(right)
	return sorted
end

a = [4,4,3,2,5,6,1,0,9,3,2,1]
puts mergesort(a)

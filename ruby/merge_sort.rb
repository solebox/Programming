def merge_sort(m)
    if (m.length <= 1)
        return m
    end
    mid = m.length / 2
    len = m.length
    left = m[0..mid-1]
    right = m[mid..len]
    left = merge_sort(left)
    right = merge_sort(right)
    return merge(left,right)
end

def merge(left,right)
    result = []
    until left.empty? && right.empty? do
        if left.length > 0 and right.length > 0 
            result << ((left.first > right.first) ? right.shift : left.shift)
        elsif left.length > 0 
           result += left
           left = []
        elsif right.length > 0
            result += right
            right = []
        end
    end
    return result
end

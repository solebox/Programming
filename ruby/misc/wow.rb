def wow(arr,i)
  if i == 0
    return(arr[i].even? ? arr[i] : 0)
  else
      return(arr[i].even? ? arr[i]+wow(arr,i-1) : wow(arr,i-1))
  end
end
a = [1,2,3,4,5,6,7]
print wow(a,a.length-1)

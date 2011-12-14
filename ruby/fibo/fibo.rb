def fibo(a,n)
    if n == 0 || n == 1
       return  a[n] =  1
    else
        return a[n] = fibo(a,n-1)+fibo(a,n-2)
    end
end


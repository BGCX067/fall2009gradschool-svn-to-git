-- Program to test Reccurssion

function fact (n)
  if n == 0 then
    return 1
  else
    return n * fact(n-1)
  end
end


print("Factorial of 5 is : "..fact(5))


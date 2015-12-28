-- bisection method for solving non-linear equations

delta=1e-6	-- tolerance

-- our function
function f(x)
 return x*x*x-x-1
end

function bisect(a,b,fa,fb)
 local c=(a+b)/2
   print(n,"c=",c,"a=",a,"b=",b,"\n")
-- io.write(n," c=",c," a=",a," b=",b,"\n")
 if c==a or c==b or (a-b > -delta and a-b < delta) then return c,b-a end
 n=n+1
 local fc=f(c)
 if fa*fc<0 then return bisect(a,c,fa,fc) else return bisect(c,b,fc,fb) end
end

-- find root of f in the inverval [a,b]. needs f(a)*f(b)<0
function solve(a,b)
 n=0
 local z,e=bisect(a,b,f(a),f(b))

   print("after", n, "steps, root is", z, "with error", e, ", f=", f(z))
end

-- find zero in [1,2]
solve(1,2)

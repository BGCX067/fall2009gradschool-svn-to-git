-- A mix of all the previous test cases
-- This test case is to test the over all implementation of lexer,
-- parser and llvm generator


a = 5

do
function factorial(m,c)
	function fact (n)
  		if n == 0 then
    		return 1
 		 else
    		return n * fact(n-1)
  		end
	end
	print(c..fact(m))
end
end

repeat
	a = a-1; print("factorial ("..a..") ");
	factorial(a," = ")
until (a and a-1)

do
do
print("\nRandom numbers:");
end

for i=1,5,1 do 
	for j=1,i,1 do
		print(i*j+i-j/j%a^2)
		if(i*j == 100) then
			break
		end
	end
end

end

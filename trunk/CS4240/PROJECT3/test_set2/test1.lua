-- This is a basic test case to test print statements
-- Concatenation and function calls

function ccat(a,b)
return a,b
end

c,d = ccat("Cellar","Door")
e = 10*10

print("***************************************")
print("These are "..'strings')
print(c.." Door")
print ('Cellar'.." "..d)
print("***************************************")
print("These are integers\n",e)
print(10)
print('***************************************')
print("These are Boolean")
print(not true)
print(not nil)
print('***************************************')


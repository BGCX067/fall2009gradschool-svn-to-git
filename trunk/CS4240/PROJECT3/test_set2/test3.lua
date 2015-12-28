-- Program to test multiple level of function calls

z = 0;
function add(a,b)
return a+b
end

function addition(a,b,c)
y = add(a+b,c)
return y
end

function doAddition()
a=1
b=2
c =3
z = addition(a,b,c)
end

doAddition()
print('Answer is:')
print(z)



-- simple functions


local i = 20
while i > 0 do
	print(i)
	i = i - 1
end


local j = 1
repeat
	print(j)
	j = j + 1
until j > 20

print("j=" .. j)

local k = 1
repeat
	print("GOOD")
until k == 1


while k ~= 1 do
	print("BAD")
end




        function nonstring1(a)
        x = a
        print(x)
        return x + 4
        end


        a = nonstring1(45)



        function nonstring2(a)
        x = a
        print(x)
        return true and false
        end


        b = nonstring2(true)


        function nonnonestring(a)
        x = "bar" .. a
        print(x)
        return x
        end


        b = nonnonestring("foo")


function count(num)
    print(num)
	local nextCount = num + 1
	if nextCount < 20 then
		count(nextCount)
	end
end

function testStrCount(myStr)
	local newStr = myStr .. "hi"
	print(myStr)
	local newStrLen = #newStr
	if newStrLen < 50 then
		testStrCount(newStr)
	end
end

local a = 5 + 6
count(a)
testStrCount("aa")



        function foo(x)
        x = 45
        print(x)
        return 86
        end

        foo(45)

        f = foo(45)

        print(f)



        function cannotinf(a, b)
        return 3
        end

        -- not calling it
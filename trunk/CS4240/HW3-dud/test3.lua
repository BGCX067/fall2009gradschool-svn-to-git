-- simple functions

a = 1
b = 2
c = 3

if a < 10 then
	if b > 1 then
		if c < 1 then
			print("BAD")
		elseif c > 5 then
			print("BAD")
		else
			print("GOOD")
		end
	else
		print("BAD")
	end
else
	print("BAD")
end


        -- simple functions

        function sayhi()
        print("hi")
        end


        function sayhello()
        print("hello")
        end


        function saythis(this)
        print(this)
        end

        function saylots()
        print("asdfg")
        sayhi()
        sayhello()
        end

        sayhi()
        sayhello()
        saythis("words are cool")
        saylots()


--[[ this is to test
--multiple layers of function calls --]]

function first(a)
	function second(b)
		function third(c)
			print("The arguement passed is: "..c)
		end
		third(b)
	end
	second(a)
end

first("1234")


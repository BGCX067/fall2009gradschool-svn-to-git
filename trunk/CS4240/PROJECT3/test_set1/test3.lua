-- temperature conversion table (celsius to farenheit)

for c0=-20,50-1,10 do
  print("C")
--	io.write("C ")
	for c=c0,c0+10-1 do
	  print(c)
--		io.write(string.format("%3.0f ",c))
	end
--	io.write("\n")
	
--	io.write("F ")
  print("F")
	for c=c0,c0+10-1 do
		f=(9/5)*c+32
		print(f)
--		io.write(string.format("%3.0f ",f))
	end
--	io.write("\n\n")
end

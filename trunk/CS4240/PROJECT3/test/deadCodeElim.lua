-- This is a test case for DEAD CODE elimination
-- Some variables are defined but not used. 
-- After running the optimization, these dead code gets eliminated
-- this can be observed from the llvm

for c0=-20,50-1,10 do
	for c=c0,c0+10-1 do
	  print(c)
	  a="this is a dummy stting"
	  b=2*54/32
	  d=1e+1
	end
	
	for c=c0,c0+10-1 do
		f=(9/5)*c+32
		e=1.1-9/5
		farenheit = f
		print(farenheit)
	end
end


-- This test case demostrates CONSTANT PROPAGATION
-- This test cases calculates result from addition, subtraction
-- multiplication, division and mod operator on constants
-- inside a loop that runs 15 million times

a = {1}
var = 0

for i = 1,250,1 do
a[i] = var
var = var+1
end

b = {1}
var = 0
for i = 1,250,1 do
b[i] = var
var = var+2
end

c = {1}
var = 0
for i = 1,250,1 do
c[i] = var
var = var+5
end

for i = 1,250,1 do
for n = 1,250,1 do
for j = 1,250,1 do
var1 = 1+2
var2 = a[i]+b[i]+c[i]
var3 = 4/2
var3 = 27/3
var5 = var3*var2
var6 = 191.5%10.5
var7 = 100000.0001/25.4567
if(4>3) then
 var8 = 4563.456/3.456
else
 var8 = 123.75/2.742
end
end
end
end

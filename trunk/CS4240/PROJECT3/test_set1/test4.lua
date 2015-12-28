i = 3
while i>0 do
  print(i)
  i = i-1
end

a,b = 0,1
while true do               -- infinite loop
  print(b)
  a,b = b,a+b
  if a>500 then break end   -- exit the loop if the condition is true
end

i = 3
repeat
  print(i)
  i = i-1
until i==0

i = 1
repeat
  print(i)
  i = i+1
  if i>3 then break end
until false

for count = 1,3 do print(count) end 

if 10>2 then print("bigger") end

if 1>10 then print("bigger") else print("smaller") end

number = 3
if number < 1 then
   value = "smaller than one"
elseif number==1 then
  value = "one"
elseif number==2 then
  value = "two"
elseif number==3 then
  value = "three"
else
  value = "bigger than three"
end
print(value)

for i = 1,3 do print(i) end 

for i = 3,1 do print(i) end

for i = 3,1,-1 do print(i) end

for i=1,0,-0.25 do print(i) end

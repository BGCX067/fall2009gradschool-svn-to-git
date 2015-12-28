-- functions
function pythagorean(a, b)
  local c2 = a^2 + b^2
  return c2
end
print(pythagorean(3,4))


a,b,c=1,2,3
do
  local a2 = 2*a
  local d = (b^2 - 4*a*c)
x1 = (-b + d)/a2
x2 = (-b - d)/a2
end -- scope of 'a2' and 'd' ends here
print(x1, x2)

i = 0
repeat
  print("i is now" .. i)
  if i < 2 then
   print("small")
  elseif i < 4 then
   print("medium")
  else
   print("big")
  end
  i = i+1
until i > 5 

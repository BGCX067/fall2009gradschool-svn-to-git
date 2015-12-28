
--[==[

[==[

a comment that spans many lines

]=====]
]]

]==]

print("Hello World!")

-- A comment in Lua starts with a double-hyphen and runs to the end of the line.
--[[ Multi-line strings & comments
     are adorned with double square brackets.]]

function factorial(n)
  if n == 0 then
    return 1
  else
    return n * factorial(n - 1)
  end
end

function factorial2(n)             
  return n == 0 and 1 or n * factorial2(n - 1)
end

do
  local oldprint = print           -- Store current print function as oldprint
  function print(s)                -- Redefine print function
    if s == "foo" then
      oldprint("bar")
    else 
      oldprint(s) 
    end
  end
end

--[[

function makeaddfunc(x)
  -- Return a new function that adds x to the argument
  return function(y)
    -- When we refer to the variable x, which is outside of the current
    -- scope and whose lifetime is shorter than that of this anonymous
    -- function, Lua creates a closure.
    return x + y
  end
end
plustwo = makeaddfunc(2)
print(plustwo(5)) -- Prints 7

]]

fibs = { 1, 1 }                                -- Initial values for fibs[1] and fibs[2].
setmetatable(fibs, {                           -- Give fibs some magic behavior.
  __index = function(name, n)                  -- Call this function if fibs[n] does not exist.
    name[n] = name[n - 1] + name[n - 2]        -- Calculate and memoize fibs[n].
    return name[n]
  end
})


a_table = {}     -- Creates a new, empty table


-- Creates a new table, with one associated entry. The string x mapping to
-- the number 10.
a_table = {x = 10}
-- Prints the value associated with the string key,
-- in this case 10.
print(a_table["x"])
b_table = a_table
b_table["x"] = 20    -- The value in the table has been changed to 20.
print(a_table["x"])  -- Prints 20.
-- Prints 20, because a_table and b_table both refer to the same table.
print(b_table["x"])



point = { x = 10, y = 20 }   -- Create new table
print(point["x"])            -- Prints 10
print(point.x)               -- Has exactly the same meaning as line above




Point = {}
Point.new = function (x, y)
  return {x = x, y = y}
end
 
Point.set_x = function (point, x)
  point.x = x
end


array = { "a", "b", "c", "d" }   -- Indices are assigned automatically.
print(array[2])                  -- Prints "b". Automatic indexing in Lua starts at 1.
print(#array)                    -- Prints 4.  # is the length operator for tables and strings.
array[0] = "z"                   -- Zero is a legal index.
print(#array)                    -- Still prints 4, as Lua arrays are 1-based.




function Point(x, y)        -- "Point" object constructor
  return { x = x, y = y }   -- Creates and returns a new object (table)
end
array = { Point(10, 20), Point(30, 40), Point(50, 60) }   -- Creates array of points
print(array[2].y)    


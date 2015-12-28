
--[==[

[==[

a comment that spans many lines

]=====]
]]

]==]
-----------------------------------------------------------------------------
-- URI parsing, composition and relative URL resolution
-- LuaSocket toolkit.
-- Author: Diego Nehab
-- RCS ID: $Id: url.lua,v 1.37 2005/11/22 08:33:29 diego Exp $
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
-- Declare module
-----------------------------------------------------------------------------
local string = require("string")
local base = _G
local table = require("table")
module("socket.url")


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


print(314.16e-2)

print(0.31416E1)

print('a very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringEND')

print('5! \777 \117\143\164\141\154\40\151\163 f\165\143\153in\1471337 \a \f \y \t \\ \v apple \n\n \t = abcd')

print('string with keywords and or not do else end false function if local nil return then until while ; , ... . [ ( ) } : - ^ % <= > == ~= $')

-- a comment

print('" " " " \'') --anoter
print(" ' ' ' \"")


print([[
this is a very long

string with : " all kinds og \ kraxy stiff in it

]==] just kidding not ovver yet

]=] still no

[==[ tricked again bitches

]])

print([==================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================[

count em thats like a bunch of equals, OVER 9000!!!, in there wich means no way ]] or ]==] 
are ending this string.

]==================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================])


--[==[


a comment that spans many lines

]=====]
]]

]==]

print([[]])

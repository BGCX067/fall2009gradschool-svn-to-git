
--[==[

[==[

a comment that spans many lines

]=====]
]]

]==]


print(314.16e-2)

print(0.31416E1)
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

-----------------------------------------------------------------------------
-- Module version
-----------------------------------------------------------------------------
_VERSION = "URL 1.0"

-----------------------------------------------------------------------------
-- Encodes a string into its escaped hexadecimal representation
-- Input
--   s: binary string to be encoded
-- Returns
--   escaped representation of string binary
-----------------------------------------------------------------------------
function escape(s)
    return string.gsub(s, "([^A-Za-z0-9_])", function(c)
        return string.format("%%%02x", string.byte(c))
    end)
end

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

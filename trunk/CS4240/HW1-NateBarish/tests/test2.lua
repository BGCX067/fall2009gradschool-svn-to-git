
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

-----------------------------------------------------------------------------
-- Protects a path segment, to prevent it from interfering with the
-- url parsing.
-- Input
--   s: binary string to be encoded
-- Returns
--   escaped representation of string binary
-----------------------------------------------------------------------------
local function make_set(t)
        local s = {}
        for i,v in base.ipairs(t) do
                s[t[i]] = 1
        end
        return s
end

-- these are allowed withing a path segment, along with alphanum
-- other characters must be escaped
local segment_set = make_set {
    "-", "_", ".", "!", "~", "*", "'", "(",
        ")", ":", "@", "&", "=", "+", "$", ",",
}

local function protect_segment(s)
        return string.gsub(s, "([^A-Za-z0-9_])", function (c)
                if segment_set[c] then return c
                else return string.format("%%%02x", string.byte(c)) end
        end)
end

-----------------------------------------------------------------------------
-- Encodes a string into its escaped hexadecimal representation
-- Input
--   s: binary string to be encoded
-- Returns
--   escaped representation of string binary
-----------------------------------------------------------------------------
function unescape(s)
    return string.gsub(s, "%%(%x%x)", function(hex)
        return string.char(base.tonumber(hex, 16))
    end)
end


print('a very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringa very ver long stringEND')

print('5! \777 \117\143\164\141\154\40\151\163 f\165\143\153in\1471337 \a \f \y \t \\ \v apple \n\n \t = abcd')

print('string with keywords and or not do else end false function if local nil return then until while ; , ... . [ ( ) } : - ^ % <= > == ~= $')

-- a comment

print('" " " " \'') --anoter
print(" ' ' ' \"")

print(314.16e-2)

print(0.31416E1)

print(0xff)

print(0x56)

--woot

print(0.31416E1)

--[==[


a comment that spans many lines

]=====]
]]

]==]





--[==[

[==[

a comment that spans many lines

]=====]
]]

]==]

function factorial (n)

  if n == 0 then

    return 1

  else


	while(nil)
	do
		executeOrder66(66);
	end	

    return n * factorial(n-1)
	
  end

end


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















 

print('5! = ' .. factorial(5))

print("one line\nnext line\n\"in quotes\", 'in quotes'")
print('a backslash inside quotes: \'\\\'')
print("a simpler way: '\\'")

page = [=[
<HTML>
<HEAD>
<TITLE>An HTML Page</TITLE>
</HEAD>
<BODY>
Lua
[[a text between double brackets]]
</BODY>
</HTML>
]=]
print (page)

print("10" + 1) --> 11
print("10 + 1") --> 10 + 1
print("-5.3e-2" * "2") --> -1.06e-09

print("hello" .. "world")
print(4 and 5) --> 5
print(4 or 5) --> 4

print(not nil) --> true
print(not false) --> true
print(not 0) --> false
print(not not nil) --> false
print(#"hello")
--[[
  print(10)         -- no action (comment)
--]]

---[[
  print(10)         --> 10
--]]


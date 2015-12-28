--test constant folding and unreachable code elimination

if (3*4>1) then -- conditional branch would be replaced by unconditional branch after constant folding
  print("hello")
else
  print("you")  -- this block cannot be reached and would be removed
end


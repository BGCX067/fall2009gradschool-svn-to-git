
function unconditionalBranch(x)
 
  while x > 1 do
    if x > 1 then
      print("What") -- should end up branching to the target of the loop backedge after CFG Opti 1
    else
       -- should end up branching to the target of the loop backedge after CFG Opti 1
    end 
    
  end

  return x
end

unconditionalBranch(10)
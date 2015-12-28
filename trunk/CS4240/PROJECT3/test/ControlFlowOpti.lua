--test control flow optimization
--


-- CFG OPTI #1 from lecture.
function unconditionalBranch(x)
 
  while x > 1 do
    if x > 1 then
      print("What") -- should end up branching to the target of the loop backedge after CFG Opti 1
    else
       -- should end up branching to the target of the loop backedge after CFG Opti 1
    end 
    x = x-1 
  end

  return x
end

unconditionalBranch(10)


-- CFG OPTI #4 from lecture.
function MergeBasicBlocksWithOnlyOneBranch (x)
	
	y= 5
	print(x + y)

end


MergeBasicBlocksWithOnlyOneBranch(6)


-- CFG OPTI #5 from lecture.
function identicalToUnconditional(x)

while x > 10 do
break 
-- I had to enable CFG Opti 1 for this one to work. 
-- So once that Opti copies the branch created by the break to the true conditional branch,
-- then the two branches are identical, and Opti #4 replaces it with an unconditional branch to the return label

end


end

identicalToUnconditional(5)



 
function identicalToUnconditional(x)

while x > 10 do
break 
-- I had to enable CFG Opti 1 for this one to work. 
-- So once that Opti copies the branch created by the break to the true conditional branch,
-- then the two branches are identical, and Opti #4 replaces it with an unconditional branch to the return label

end


end

identicalToUnconditional(5)
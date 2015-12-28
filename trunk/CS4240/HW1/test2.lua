function foo ()
    x = 34
    if x > 2 then
        repeat x = x + 2 until x == 100
    elseif x < 2 then
        x = 34
    else
        x = 34
    end
    return x
end
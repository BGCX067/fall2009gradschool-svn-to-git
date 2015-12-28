-- simple functions

function sayhi()
  print("hi")
end


function sayhello()
  print("hello")
end


function saythis(this)
  print(this)
end

function saylots()
  print("asdfg")
  sayhi()
  sayhello()
end

sayhi()
sayhello()
saythis("words are cool")
saylots()

        -- simple test

        a = 5
        b = "foobar "
        c = b .. a
        print(c)

        d = a + 10 * a

        print(d)

        e = a / 3.14

        print(e)

--output:
        --  foobar 5.000000
        --  55.000000
        --  1.592357



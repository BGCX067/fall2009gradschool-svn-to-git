#!/bin/sh

lli ../test_set1/sort.bc > test.out
diff ../test_set1/sort.out test.out

lli ../test_set1/test1.bc > test.out
diff ../test_set1/test1.out  test.out

lli ../test_set1/test10.bc > test.out
diff ../test_set1/test10.out  test.out

lli ../test_set1/test2.bc > test.out
diff ../test_set1/test2.out  test.out

lli ../test_set1/test3.bc  > test.out
diff ../test_set1/test3.out   test.out

lli ../test_set1/test4.bc > test.out
diff ../test_set1/test4.out  test.out

lli ../test_set1/test5.bc > test.out
diff ../test_set1/test5.out  test.out

lli ../test_set1/test6.bc > test.out
diff ../test_set1/test6.out  test.out

lli ../test_set1/test7.bc > test.out
diff ../test_set1/test7.out  test.out

lli ../test_set1/test8.bc > test.out
diff ../test_set1/test8.out  test.out

lli ../test_set1/test9.bc > test.out
diff ../test_set1/test9.out  test.out

lli ../test_set2/test1.bc > test.out
diff ../test_set2/test1.out  test.out

lli ../test_set2/test10.bc > test.out
diff ../test_set2/test10.out  test.out

lli ../test_set2/test2.bc > test.out
diff ../test_set2/test2.out  test.out

lli ../test_set2/test3.bc > test.out
diff ../test_set2/test3.out  test.out

lli ../test_set2/test4.bc > test.out
diff ../test_set2/test4.out  test.out

lli ../test_set2/test5.bc > test.out
diff ../test_set2/test5.out   test.out

lli ../test_set2/test8.bc > test.out
diff ../test_set2/test8.out  test.out


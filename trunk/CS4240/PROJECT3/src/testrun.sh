#!/bin/sh

./luac test.lua
./luac ../test_set1/sort.lua
./luac ../test_set1/test1.lua
./luac ../test_set1/test10.lua
./luac ../test_set1/test2.lua
./luac ../test_set1/test3.lua
./luac ../test_set1/test4.lua
./luac ../test_set1/test5.lua
./luac ../test_set1/test6.lua
./luac ../test_set1/test7.lua
./luac ../test_set1/test8.lua
./luac ../test_set1/test9.lua
./luac ../test_set2/test1.lua
./luac ../test_set2/test10.lua
./luac ../test_set2/test2.lua
./luac ../test_set2/test3.lua
./luac ../test_set2/test4.lua
./luac ../test_set2/test5.lua
./luac ../test_set2/test8.lua

llvm-as -f test.ll
llvm-as -f ../test_set1/sort.ll
llvm-as -f ../test_set1/test1.ll
llvm-as -f ../test_set1/test10.ll
llvm-as -f ../test_set1/test2.ll
llvm-as -f ../test_set1/test3.ll
llvm-as -f ../test_set1/test4.ll
llvm-as -f ../test_set1/test5.ll
llvm-as -f ../test_set1/test6.ll
llvm-as -f ../test_set1/test7.ll
llvm-as -f ../test_set1/test8.ll
llvm-as -f ../test_set1/test9.ll
llvm-as -f ../test_set2/test1.ll
llvm-as -f ../test_set2/test10.ll
llvm-as -f ../test_set2/test2.ll
llvm-as -f ../test_set2/test3.ll
llvm-as -f ../test_set2/test4.ll
llvm-as -f ../test_set2/test5.ll
llvm-as -f ../test_set2/test8.ll


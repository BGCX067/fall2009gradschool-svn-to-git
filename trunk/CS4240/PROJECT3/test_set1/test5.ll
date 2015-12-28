declare i32 @printf(i8* , ...)
declare i8* @strcat(i8* , i8* )
declare i32 @strlen(i8*)
declare double @llvm.pow.f64(double, double)
declare double @atof(i8*)
declare i32 @sprintf(i8*, i8*, ...)
declare i8* @malloc(i32)
declare void @llvm.memset.i32(i8* , i8, i32, i32)
declare i8* @strcpy(i8* , i8*)
declare i32 @strcmp(i8*, i8*)
@ftoa.str = internal constant [3 x i8] c"%f\00"
@false.str = internal constant [6 x i8] c"false\00"
@true.str = internal constant [5 x i8] c"true\00"
@global.x = common global double 0.000000e+00
@print43 = constant [5 x i8] c"%f\09\0A\00"
@print44 = constant [5 x i8] c"%f\09\0A\00"
@print45 = constant [14 x i8] c"%f\09%f\09%f\09%f\09\0A\00"
@print46 = constant [5 x i8] c"%f\09\0A\00"
@print47 = constant [8 x i8] c"%f\09%f\09\0A\00"
@print48 = constant [11 x i8] c"%f\09%f\09%f\09\0A\00"
@print49 = constant [8 x i8] c"%s\09%s\09\0A\00"
@print50 = constant [8 x i8] c"%s\09%s\09\0A\00"
@print51 = constant [8 x i8] c"%s\09%s\09\0A\00"
@print52 = constant [11 x i8] c"%s\09%s\09%s\09\0A\00"
@print53 = constant [11 x i8] c"%s\09%s\09%s\09\0A\00"
@string33 = constant [4 x i8] c"abc\00"
@string34 = constant [4 x i8] c"def\00"
@print54 = constant [5 x i8] c"%s\09\0A\00"
@string35 = constant [4 x i8] c"abc\00"
@string36 = constant [4 x i8] c"def\00"
@print55 = constant [5 x i8] c"%s\09\0A\00"
@string37 = constant [4 x i8] c"abc\00"
@string38 = constant [4 x i8] c"abc\00"
@print56 = constant [5 x i8] c"%s\09\0A\00"
@string39 = constant [4 x i8] c"abc\00"
@string40 = constant [2 x i8] c"a\00"
@string41 = constant [3 x i8] c"bc\00"
@print57 = constant [5 x i8] c"%s\09\0A\00"
@string42 = constant [3 x i8] c"10\00"
@print58 = constant [5 x i8] c"%s\09\0A\00"
@print59 = constant [8 x i8] c"%s\09%s\09\0A\00"
@print60 = constant [5 x i8] c"%s\09\0A\00"
@print61 = constant [14 x i8] c"%s\09%s\09%s\09%s\09\0A\00"
@print62 = constant [5 x i8] c"%s\09\0A\00"
@string43 = constant [4 x i8] c"foo\00"
@print63 = constant [5 x i8] c"%s\09\0A\00"
@print64 = constant [5 x i8] c"%s\09\0A\00"
@print65 = constant [5 x i8] c"%s\09\0A\00"
@print66 = constant [5 x i8] c"%s\09\0A\00"
@print67 = constant [5 x i8] c"%s\09\0A\00"
@print68 = constant [5 x i8] c"%s\09\0A\00"
@string44 = constant [5 x i8] c"true\00"
@print69 = constant [5 x i8] c"%s\09\0A\00"
@string45 = constant [6 x i8] c"false\00"
@print70 = constant [5 x i8] c"%s\09\0A\00"
@string46 = constant [5 x i8] c"true\00"
@print71 = constant [5 x i8] c"%s\09\0A\00"
@string47 = constant [6 x i8] c"false\00"
@print72 = constant [5 x i8] c"%s\09\0A\00"
@string48 = constant [5 x i8] c"true\00"
@print73 = constant [5 x i8] c"%s\09\0A\00"
@string49 = constant [6 x i8] c"false\00"
@print74 = constant [5 x i8] c"%s\09\0A\00"
@print75 = constant [5 x i8] c"%s\09\0A\00"
@print76 = constant [5 x i8] c"%s\09\0A\00"
define i32 @main() {
entry:
br label %main.bb71
main.bb71:
%main.bb71.tmp448 = add double 0.000000e+00, 7.000000
%main.bb71.tmp449 = load double* @global.x
store double %main.bb71.tmp448, double* @global.x
%main.bb71.tmp450 = load double* @global.x
%main.bb71.tmp451 = bitcast [5 x i8]* @print43 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp451, double %main.bb71.tmp450)
%main.bb71.tmp452 = add double 0.000000e+00, 7.000000
%main.bb71.tmp453 = bitcast [5 x i8]* @print44 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp453, double %main.bb71.tmp452)
%main.bb71.tmp455 = add double 0.000000e+00, 2.000000
%main.bb71.tmp456 = add double 0.000000e+00, 3.000000
%main.bb71.tmp454 = add double %main.bb71.tmp455, %main.bb71.tmp456
%main.bb71.tmp458 = add double 0.000000e+00, 5.000000
%main.bb71.tmp459 = add double 0.000000e+00, 12.000000
%main.bb71.tmp457 = sub double %main.bb71.tmp458, %main.bb71.tmp459
%main.bb71.tmp461 = add double 0.000000e+00, 2.000000
%main.bb71.tmp462 = add double 0.000000e+00, 7.000000
%main.bb71.tmp460 = mul double %main.bb71.tmp461, %main.bb71.tmp462
%main.bb71.tmp464 = add double 0.000000e+00, 7.000000
%main.bb71.tmp465 = add double 0.000000e+00, 8.000000
%main.bb71.tmp463 = fdiv double %main.bb71.tmp464, %main.bb71.tmp465
%main.bb71.tmp466 = bitcast [14 x i8]* @print45 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp466, double %main.bb71.tmp454, double %main.bb71.tmp457, double %main.bb71.tmp460, double %main.bb71.tmp463)
%main.bb71.tmp470 = add double 0.000000e+00, 5.000000
%main.bb71.tmp472 = add double 0.000000e+00, 2.000000
%main.bb71.tmp473 = add double 0.000000e+00, 8.300000
%main.bb71.tmp471 = sub double %main.bb71.tmp472, %main.bb71.tmp473
%main.bb71.tmp469 = mul double %main.bb71.tmp470, %main.bb71.tmp471
%main.bb71.tmp474 = add double 0.000000e+00, 77.700000
%main.bb71.tmp468 = fdiv double %main.bb71.tmp469, %main.bb71.tmp474
%main.bb71.tmp475 = add double 0.000000e+00, 99.100000
%main.bb71.tmp467 = add double %main.bb71.tmp468, %main.bb71.tmp475
%main.bb71.tmp476 = bitcast [5 x i8]* @print46 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp476, double %main.bb71.tmp467)
%main.bb71.tmp479 = add double 0.000000e+00, 10.000000
%main.bb71.tmp478 = sub double 0.000000e+00, %main.bb71.tmp479
%main.bb71.tmp477 = sub double 0.000000e+00, %main.bb71.tmp478
%main.bb71.tmp481 = add double 0.000000e+00, 10.000000
%main.bb71.tmp480 = sub double 0.000000e+00, %main.bb71.tmp481
%main.bb71.tmp482 = bitcast [8 x i8]* @print47 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp482, double %main.bb71.tmp477, double %main.bb71.tmp480)
%main.bb71.tmp484 = add double 0.000000e+00, 7.000000
%main.bb71.tmp485 = add double 0.000000e+00, 2.000000
%main.bb71.tmp486 = call double@llvm.pow.f64(double %main.bb71.tmp484, double %main.bb71.tmp485)
%main.bb71.tmp488 = add double 0.000000e+00, 107.000000
%main.bb71.tmp489 = add double 0.000000e+00, 0.000000
%main.bb71.tmp490 = call double@llvm.pow.f64(double %main.bb71.tmp488, double %main.bb71.tmp489)
%main.bb71.tmp492 = add double 0.000000e+00, 2.000000
%main.bb71.tmp493 = add double 0.000000e+00, 8.000000
%main.bb71.tmp494 = call double@llvm.pow.f64(double %main.bb71.tmp492, double %main.bb71.tmp493)
%main.bb71.tmp495 = bitcast [11 x i8]* @print48 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp495, double %main.bb71.tmp486, double %main.bb71.tmp490, double %main.bb71.tmp494)
%main.bb71.tmp497 = add double 0.000000e+00, 1.000000
%main.bb71.tmp498 = add double 0.000000e+00, 1.000000
%main.bb71.tmp496 = fcmp ueq double %main.bb71.tmp497, %main.bb71.tmp498
%main.bb71.tmp500 = add double 0.000000e+00, 1.000000
%main.bb71.tmp501 = add double 0.000000e+00, 0.000000
%main.bb71.tmp499 = fcmp ueq double %main.bb71.tmp500, %main.bb71.tmp501
%main.bb71.tmp502 = call i8*@btoa(i1 %main.bb71.tmp496)
%main.bb71.tmp503 = call i8*@btoa(i1 %main.bb71.tmp499)
%main.bb71.tmp504 = bitcast [8 x i8]* @print49 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp504, i8* %main.bb71.tmp502, i8* %main.bb71.tmp503)
%main.bb71.tmp506 = add double 0.000000e+00, 1.000000
%main.bb71.tmp507 = add double 0.000000e+00, 1.000000
%main.bb71.tmp505 = fcmp une double %main.bb71.tmp506, %main.bb71.tmp507
%main.bb71.tmp509 = add double 0.000000e+00, 1.000000
%main.bb71.tmp510 = add double 0.000000e+00, 0.000000
%main.bb71.tmp508 = fcmp une double %main.bb71.tmp509, %main.bb71.tmp510
%main.bb71.tmp511 = call i8*@btoa(i1 %main.bb71.tmp505)
%main.bb71.tmp512 = call i8*@btoa(i1 %main.bb71.tmp508)
%main.bb71.tmp513 = bitcast [8 x i8]* @print50 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp513, i8* %main.bb71.tmp511, i8* %main.bb71.tmp512)
%main.bb71.tmp515 = add double 0.000000e+00, 2.000000
%main.bb71.tmp516 = add double 0.000000e+00, 7.000000
%main.bb71.tmp514 = fcmp ult double %main.bb71.tmp515, %main.bb71.tmp516
%main.bb71.tmp518 = add double 0.000000e+00, 2.000000
%main.bb71.tmp519 = add double 0.000000e+00, 7.000000
%main.bb71.tmp517 = fcmp ugt double %main.bb71.tmp518, %main.bb71.tmp519
%main.bb71.tmp520 = call i8*@btoa(i1 %main.bb71.tmp514)
%main.bb71.tmp521 = call i8*@btoa(i1 %main.bb71.tmp517)
%main.bb71.tmp522 = bitcast [8 x i8]* @print51 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp522, i8* %main.bb71.tmp520, i8* %main.bb71.tmp521)
%main.bb71.tmp524 = add double 0.000000e+00, 3.000000
%main.bb71.tmp525 = add double 0.000000e+00, 7.000000
%main.bb71.tmp523 = fcmp ule double %main.bb71.tmp524, %main.bb71.tmp525
%main.bb71.tmp527 = add double 0.000000e+00, 7.000000
%main.bb71.tmp528 = add double 0.000000e+00, 7.000000
%main.bb71.tmp526 = fcmp ule double %main.bb71.tmp527, %main.bb71.tmp528
%main.bb71.tmp530 = add double 0.000000e+00, 8.000000
%main.bb71.tmp531 = add double 0.000000e+00, 7.000000
%main.bb71.tmp529 = fcmp ule double %main.bb71.tmp530, %main.bb71.tmp531
%main.bb71.tmp532 = call i8*@btoa(i1 %main.bb71.tmp523)
%main.bb71.tmp533 = call i8*@btoa(i1 %main.bb71.tmp526)
%main.bb71.tmp534 = call i8*@btoa(i1 %main.bb71.tmp529)
%main.bb71.tmp535 = bitcast [11 x i8]* @print52 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp535, i8* %main.bb71.tmp532, i8* %main.bb71.tmp533, i8* %main.bb71.tmp534)
%main.bb71.tmp537 = add double 0.000000e+00, 3.000000
%main.bb71.tmp538 = add double 0.000000e+00, 7.000000
%main.bb71.tmp536 = fcmp uge double %main.bb71.tmp537, %main.bb71.tmp538
%main.bb71.tmp540 = add double 0.000000e+00, 7.000000
%main.bb71.tmp541 = add double 0.000000e+00, 7.000000
%main.bb71.tmp539 = fcmp uge double %main.bb71.tmp540, %main.bb71.tmp541
%main.bb71.tmp543 = add double 0.000000e+00, 8.000000
%main.bb71.tmp544 = add double 0.000000e+00, 7.000000
%main.bb71.tmp542 = fcmp uge double %main.bb71.tmp543, %main.bb71.tmp544
%main.bb71.tmp545 = call i8*@btoa(i1 %main.bb71.tmp536)
%main.bb71.tmp546 = call i8*@btoa(i1 %main.bb71.tmp539)
%main.bb71.tmp547 = call i8*@btoa(i1 %main.bb71.tmp542)
%main.bb71.tmp548 = bitcast [11 x i8]* @print53 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp548, i8* %main.bb71.tmp545, i8* %main.bb71.tmp546, i8* %main.bb71.tmp547)
%main.bb71.tmp550 = bitcast [4 x i8]* @string33 to i8*
%main.bb71.tmp551 = bitcast [4 x i8]* @string34 to i8*
%main.bb71.tmp549 = call i1@stringcmp(i8* %main.bb71.tmp550, i8* %main.bb71.tmp551, i32 0)
%main.bb71.tmp552 = call i8*@btoa(i1 %main.bb71.tmp549)
%main.bb71.tmp553 = bitcast [5 x i8]* @print54 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp553, i8* %main.bb71.tmp552)
%main.bb71.tmp555 = bitcast [4 x i8]* @string35 to i8*
%main.bb71.tmp556 = bitcast [4 x i8]* @string36 to i8*
%main.bb71.tmp554 = call i1@stringcmp(i8* %main.bb71.tmp555, i8* %main.bb71.tmp556, i32 1)
%main.bb71.tmp557 = call i8*@btoa(i1 %main.bb71.tmp554)
%main.bb71.tmp558 = bitcast [5 x i8]* @print55 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp558, i8* %main.bb71.tmp557)
%main.bb71.tmp560 = bitcast [4 x i8]* @string37 to i8*
%main.bb71.tmp561 = bitcast [4 x i8]* @string38 to i8*
%main.bb71.tmp559 = call i1@stringcmp(i8* %main.bb71.tmp560, i8* %main.bb71.tmp561, i32 5)
%main.bb71.tmp562 = call i8*@btoa(i1 %main.bb71.tmp559)
%main.bb71.tmp563 = bitcast [5 x i8]* @print56 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp563, i8* %main.bb71.tmp562)
%main.bb71.tmp565 = bitcast [4 x i8]* @string39 to i8*
%main.bb71.tmp567 = bitcast [2 x i8]* @string40 to i8*
%main.bb71.tmp568 = bitcast [3 x i8]* @string41 to i8*
%main.bb71.tmp569 = call i8*@stringcat(i8* %main.bb71.tmp567, i8* %main.bb71.tmp568)
%main.bb71.tmp564 = call i1@stringcmp(i8* %main.bb71.tmp565, i8* %main.bb71.tmp569, i32 5)
%main.bb71.tmp570 = call i8*@btoa(i1 %main.bb71.tmp564)
%main.bb71.tmp571 = bitcast [5 x i8]* @print57 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp571, i8* %main.bb71.tmp570)
%main.bb71.tmp573 = bitcast [3 x i8]* @string42 to i8*
%main.bb71.tmp574 = add double 0.000000e+00, 10.000000
%main.bb71.tmp572 = add i1 0, 0
%main.bb71.tmp575 = call i8*@btoa(i1 %main.bb71.tmp572)
%main.bb71.tmp576 = bitcast [5 x i8]* @print58 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp576, i8* %main.bb71.tmp575)
%main.bb71.tmp578 = add i1 0, 1
%main.bb71.tmp579 = add i1 0, 0
%main.bb71.tmp577 = icmp eq i1 %main.bb71.tmp578, %main.bb71.tmp579
%main.bb71.tmp581 = add i1 0, 1
%main.bb71.tmp582 = add i1 0, 0
%main.bb71.tmp580 = icmp ne i1 %main.bb71.tmp581, %main.bb71.tmp582
%main.bb71.tmp583 = call i8*@btoa(i1 %main.bb71.tmp577)
%main.bb71.tmp584 = call i8*@btoa(i1 %main.bb71.tmp580)
%main.bb71.tmp585 = bitcast [8 x i8]* @print59 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp585, i8* %main.bb71.tmp583, i8* %main.bb71.tmp584)
%main.bb71.tmp587 = add double 0.000000e+00, 1.000000
%main.bb71.tmp588 = add double 0.000000e+00, 0.000000
%main.bb71.tmp586 = fcmp ueq double %main.bb71.tmp587, %main.bb71.tmp588
%main.bb71.tmp589 = call i8*@btoa(i1 %main.bb71.tmp586)
%main.bb71.tmp590 = bitcast [5 x i8]* @print60 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp590, i8* %main.bb71.tmp589)
%main.bb71.tmp591 = add i1 0, 1
%main.bb71.tmp592 = add i1 0, 0
%main.bb71.tmp594 = add i1 0, 1
%main.bb71.tmp593 = sub i1 1, %main.bb71.tmp594
%main.bb71.tmp596 = add i1 0, 0
%main.bb71.tmp595 = sub i1 1, %main.bb71.tmp596
%main.bb71.tmp597 = call i8*@btoa(i1 %main.bb71.tmp591)
%main.bb71.tmp598 = call i8*@btoa(i1 %main.bb71.tmp592)
%main.bb71.tmp599 = call i8*@btoa(i1 %main.bb71.tmp593)
%main.bb71.tmp600 = call i8*@btoa(i1 %main.bb71.tmp595)
%main.bb71.tmp601 = bitcast [14 x i8]* @print61 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp601, i8* %main.bb71.tmp597, i8* %main.bb71.tmp598, i8* %main.bb71.tmp599, i8* %main.bb71.tmp600)
%main.bb71.tmp604 = add i1 0, 1
%main.bb71.tmp603 = sub i1 1, %main.bb71.tmp604
%main.bb71.tmp602 = sub i1 1, %main.bb71.tmp603
%main.bb71.tmp605 = call i8*@btoa(i1 %main.bb71.tmp602)
%main.bb71.tmp606 = bitcast [5 x i8]* @print62 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp606, i8* %main.bb71.tmp605)
%main.bb71.tmp608 = bitcast [4 x i8]* @string43 to i8*
%main.bb71.tmp607 = add i1 0, 0
%main.bb71.tmp609 = call i8*@btoa(i1 %main.bb71.tmp607)
%main.bb71.tmp610 = bitcast [5 x i8]* @print63 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp610, i8* %main.bb71.tmp609)
%main.bb71.tmp612 = add i1 0, 0
%main.bb71.tmp613 = add i1 0, 1
%main.bb71.tmp611 = and i1 %main.bb71.tmp612, %main.bb71.tmp613
%main.bb71.tmp614 = call i8*@btoa(i1 %main.bb71.tmp611)
%main.bb71.tmp615 = bitcast [5 x i8]* @print64 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp615, i8* %main.bb71.tmp614)
%main.bb71.tmp617 = add i1 0, 1
%main.bb71.tmp618 = add i1 0, 0
%main.bb71.tmp616 = and i1 %main.bb71.tmp617, %main.bb71.tmp618
%main.bb71.tmp619 = call i8*@btoa(i1 %main.bb71.tmp616)
%main.bb71.tmp620 = bitcast [5 x i8]* @print65 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp620, i8* %main.bb71.tmp619)
%main.bb71.tmp622 = add i1 0, 1
%main.bb71.tmp623 = add i1 0, 1
%main.bb71.tmp621 = and i1 %main.bb71.tmp622, %main.bb71.tmp623
%main.bb71.tmp624 = call i8*@btoa(i1 %main.bb71.tmp621)
%main.bb71.tmp625 = bitcast [5 x i8]* @print66 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp625, i8* %main.bb71.tmp624)
%main.bb71.tmp627 = add i1 0, 1
%main.bb71.tmp628 = add i1 0, 0
%main.bb71.tmp626 = or i1 %main.bb71.tmp627, %main.bb71.tmp628
%main.bb71.tmp629 = call i8*@btoa(i1 %main.bb71.tmp626)
%main.bb71.tmp630 = bitcast [5 x i8]* @print67 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp630, i8* %main.bb71.tmp629)
%main.bb71.tmp632 = add i1 0, 0
%main.bb71.tmp633 = add i1 0, 1
%main.bb71.tmp631 = or i1 %main.bb71.tmp632, %main.bb71.tmp633
%main.bb71.tmp634 = call i8*@btoa(i1 %main.bb71.tmp631)
%main.bb71.tmp635 = bitcast [5 x i8]* @print68 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb71.tmp635, i8* %main.bb71.tmp634)
%main.bb71.tmp636 = add double 0.000000e+00, 1.000000
%main.bb71.tmp637 = add i1 0, 1
br i1 %main.bb71.tmp637, label %main.bb73, label %main.bb74
main.bb73:
%main.bb73.tmp638 = bitcast [5 x i8]* @string44 to i8*
%main.bb73.tmp639 = bitcast [5 x i8]* @print69 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb73.tmp639, i8* %main.bb73.tmp638)
br label %main.bb72
main.bb74:
%main.bb74.tmp640 = bitcast [6 x i8]* @string45 to i8*
%main.bb74.tmp641 = bitcast [5 x i8]* @print70 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb74.tmp641, i8* %main.bb74.tmp640)
br label %main.bb72
main.bb72:
%main.bb72.tmp642 = add double 0.000000e+00, 0.000000
%main.bb72.tmp643 = add i1 0, 1
br i1 %main.bb72.tmp643, label %main.bb76, label %main.bb77
main.bb76:
%main.bb76.tmp644 = bitcast [5 x i8]* @string46 to i8*
%main.bb76.tmp645 = bitcast [5 x i8]* @print71 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb76.tmp645, i8* %main.bb76.tmp644)
br label %main.bb75
main.bb77:
%main.bb77.tmp646 = bitcast [6 x i8]* @string47 to i8*
%main.bb77.tmp647 = bitcast [5 x i8]* @print72 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb77.tmp647, i8* %main.bb77.tmp646)
br label %main.bb75
main.bb75:
%main.bb75.tmp649 = add double 0.000000e+00, 1.000000
%main.bb75.tmp650 = add double 0.000000e+00, 2.000000
%main.bb75.tmp648 = fcmp ueq double %main.bb75.tmp649, %main.bb75.tmp650
br i1 %main.bb75.tmp648, label %main.bb79, label %main.bb80
main.bb79:
%main.bb79.tmp651 = bitcast [5 x i8]* @string48 to i8*
%main.bb79.tmp652 = bitcast [5 x i8]* @print73 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb79.tmp652, i8* %main.bb79.tmp651)
br label %main.bb78
main.bb80:
%main.bb80.tmp653 = bitcast [6 x i8]* @string49 to i8*
%main.bb80.tmp654 = bitcast [5 x i8]* @print74 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb80.tmp654, i8* %main.bb80.tmp653)
br label %main.bb78
main.bb78:
%main.bb78.tmp656 = add double 0.000000e+00, 1.000000
%main.bb78.tmp655 = add i1 0, 0
%main.bb78.tmp657 = call i8*@btoa(i1 %main.bb78.tmp655)
%main.bb78.tmp658 = bitcast [5 x i8]* @print75 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb78.tmp658, i8* %main.bb78.tmp657)
%main.bb78.tmp660 = add double 0.000000e+00, 0.000000
%main.bb78.tmp659 = add i1 0, 0
%main.bb78.tmp661 = call i8*@btoa(i1 %main.bb78.tmp659)
%main.bb78.tmp662 = bitcast [5 x i8]* @print76 to i8*
call i32 (i8*, ...)* @printf(i8* %main.bb78.tmp662, i8* %main.bb78.tmp661)
ret i32 0
}
define i8* @ftoa(double %num) {
entry:
%num_addr = alloca double
%retval = alloca i8*
%c = alloca i8*
%0 = alloca i8*
%"alloca point" = bitcast i32 0 to i32
store double %num, double* %num_addr
%1 = call i8* @malloc(i32 256)
store i8* %1, i8** %c
%2 = load i8** %c
call void @llvm.memset.i32(i8* %2, i8 0, i32 256, i32 1)
%3 = load i8** %c
%4 = load double* %num_addr
%5 = call i32 (i8*, i8*, ...)* @sprintf(i8* %3, i8* getelementptr ([3 x i8]* @ftoa.str, i32 0, i32 0), double %4)
%6 = load i8** %c
store i8* %6, i8** %0
%7 = load i8** %0
store i8* %7, i8** %retval
br label %return
return:
%retval1 = load i8** %retval
ret i8* %retval1
}
define i8* @stringcat(i8* %s1, i8* %s2) {
entry:
%s1_addr = alloca i8*
%s2_addr = alloca i8*
%retval = alloca i8*
%s = alloca i8*
%0 = alloca i8*
%"alloca point" = bitcast i32 0 to i32
store i8* %s1, i8** %s1_addr
store i8* %s2, i8** %s2_addr
%1 = call i8* @malloc(i32 256)
store i8* %1, i8** %s
%2 = load i8** %s
call void @llvm.memset.i32(i8* %2, i8 0, i32 256, i32 1)
%3 = load i8** %s
%4 = load i8** %s1_addr
%5 = call i8* @strcpy(i8* %3, i8* %4)
%6 = load i8** %s
%7 = load i8** %s2_addr
%8 = call i8* @strcat(i8* %6, i8* %7)
%9 = load i8** %s
store i8* %9, i8** %0
%10 = load i8** %0
store i8* %10, i8** %retval
br label %return
return:
%retval1 = load i8** %retval
ret i8* %retval1
}
define i1 @stringcmp(i8* %s1, i8* %s2, i32 %op)  {
entry:
%s1_addr = alloca i8*
%s2_addr = alloca i8*
%op_addr = alloca i32	
%retval = alloca i1
%i = alloca i32
%0 = alloca i1
%"alloca point" = bitcast i32 0 to i32
store i8* %s1, i8** %s1_addr
store i8* %s2, i8** %s2_addr
store i32 %op, i32* %op_addr
%1 = load i8** %s1_addr
%2 = load i8** %s2_addr
%3 = call i32 @strcmp(i8* %1, i8* %2)
store i32 %3, i32* %i
%4 = load i32* %op_addr
switch i32 %4, label %bb6 [
i32 0, label %bb
i32 1, label %bb1
i32 2, label %bb2
i32 3, label %bb3
i32 4, label %bb4
i32 5, label %bb5
]
bb:
%5 = load i32* %i
%6 = icmp slt i32 %5, 0
store i1 %6, i1* %0
br label %bb7
bb1:
%7 = load i32* %i
%8 = icmp sgt i32 %7, 0
store i1 %8, i1* %0
br label %bb7
bb2:
%9 = load i32* %i
%10 = icmp sle i32 %9, 0
store i1 %10, i1* %0
br label %bb7
bb3:
%11 = load i32* %i
%12 = icmp sge i32 %11, 0
store i1 %12, i1* %0
br label %bb7
bb4:
%13 = load i32* %i
%14 = icmp ne i32 %13, 0
store i1 %14, i1* %0
br label %bb7
bb5:
%15 = load i32* %i
%16 = icmp eq i32 %15, 0
store i1 %16, i1* %0
br label %bb7
bb6:
br label %return
bb7:		; preds = %bb5, %bb4, %bb3, %bb2, %bb1, %bb
%17 = load i1* %0
store i1 %17, i1* %retval
br label %return
return:
%retval8 = load i1* %retval
ret i1 %retval8
}
define i8* @btoa(i1 %i) {
entry:
%i_addr = alloca i1
%retval = alloca i8*
%0 = alloca i8*
%"alloca point" = bitcast i32 0 to i32
store i1 %i, i1* %i_addr
%1 = load i1* %i_addr
%2 = icmp eq i1 %1, 0
br i1 %2, label %bb, label %bb1
bb:
store i8* getelementptr ([6 x i8]* @false.str, i32 0, i32 0), i8** %0
br label %bb2
bb1:
store i8* getelementptr ([5 x i8]* @true.str, i32 0, i32 0), i8** %0
br label %bb2
bb2:
%3 = load i8** %0
store i8* %3, i8** %retval
br label %return
return:
%retval3 = load i8** %retval
ret i8* %retval3
}

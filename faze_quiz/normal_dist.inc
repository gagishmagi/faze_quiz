<?php

function faze_quiz_gauss()
{   // N(0,1)
    // returns random number with normal distribution:
    //   mean=0
    //   std dev=1
   
    // auxilary vars
    $x=faze_quiz_random_0_1();
    $y=faze_quiz_random_0_1();
   
    // two independent variables with normal distribution N(0,1)
    $u=sqrt(-2*log($x))*cos(2*pi()*$y);
    $v=sqrt(-2*log($x))*sin(2*pi()*$y);
   
    // i will return only one, couse only one needed
    return $u;
}

function faze_quiz_gauss_ms($m=0.0,$s=1.0)
{   // N(m,s)
    // returns random number with normal distribution:
    //   mean=m
    //   std dev=s
   
    return faze_quiz_gauss()*$s+$m;
}

function faze_quiz_random_0_1()
{   // auxiliary function
    // returns random number with flat distribution from 0 to 1
    return (float)rand()/(float)getrandmax();
}
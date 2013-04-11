#!/bin/bash
n=1
while :
do
    ./inferAll $n link 0 25
    let n=n+1
done

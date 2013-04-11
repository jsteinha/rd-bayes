#!/bin/bash
seeds=(245 45 455 681 103 544 111 377 441 401 690 564 588 55 244 265 483 747 187 156 852 301 284 41 358 1 312);
for seed in "${seeds[@]}"
do
    echo "25" >> data/link.cases
    sed '1d;$d' run-link-$seed.log | sed 's/://' >> data/link.cases
done


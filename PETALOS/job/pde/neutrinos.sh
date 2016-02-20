#!/bin/bash

for i in `ls /home/jmbenlloch/next/petalo/PESOA/PETALOS/job/pde/scripts/*`
do
	echo "Sending "$i
    qsub $i
done

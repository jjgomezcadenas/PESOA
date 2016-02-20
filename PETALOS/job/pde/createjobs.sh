#!/bin/bash

N=0
FILENUMBER=0
for i in `ls /home/jmbenlloch/next/petalo/PESOA/PETALOS/job/pde/jobs/*`
do
	if [ $(($N % 5)) = 0 ]; then
		FILENUMBER=$(($FILENUMBER + 1))
		FILE="scripts/$FILENUMBER.sh"
		echo "#!/bin/bash" >> $FILE
		echo "#PBS -N petalo"$N >> $FILE
		echo "#PBS -q short" >> $FILE
		echo "#PBS -M jmbenlloch@ific.uv.es" >> $FILE
#	echo "#PBS -m bae" >> $FILE
		echo "source /data4/NEXT/sw/Releases/NEXT_v0_05_05/setup.sh" >> $FILE
	fi
	FILE="scripts/$FILENUMBER.sh"
	N=$(($N+1))
	NAME=`echo $i | cut -d'/' -f 10`
	echo "runCNTjob $i >> /home/jmbenlloch/next/petalo/work/log/pde/$NAME.log" >> $FILE
done

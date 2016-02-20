#!/bin/bash

DATAPATH="/data4/NEXT/users/paolafer/petalo_prod/tof/"
JOBPATH="/home/jmbenlloch/next/petalo/PESOA/PETALOS/job/pde/jobs/"
LOGPATH="/home/jmbenlloch/next/petalo/work/log/pde/"
HISTOSPATH="/home/jmbenlloch/next/petalo/work/histo/pde/"
TREESPATH="/home/jmbenlloch/next/petalo/work/tree/pde/"

Data[0]='LXe_VUV3mm_xy2.4cm_z5cm_PHYS.pet'
Data[1]='LXe_VUV3mm_xy2.4cm_z5cm_PHYS_noCher.pet'
Data[2]='LXe_VUV3mm_xy2.4cm_z5cm_PHYS_noScint.pet'
Data[3]='LXe_TPB3mm_xy2.4cm_z5cm_PHYS.pet'
Data[4]='LXe_TPB3mm_xy2.4cm_z5cm_PHYS_noCher.pet'
Data[5]='LXe_TPB3mm_xy2.4cm_z5cm_PHYS_noScint.pet'
Data[6]='LYSO_3mm_xy2.4cm_z5cm_PHYS.pet'
Data[7]='LYSO_3mm_xy2.4cm_z5cm_PHYS_noCher.pet'
Data[8]='LYSO_3mm_xy2.4cm_z5cm_PHYS_noScint.pet'

INDEX=0

for data in "${Data[@]}"; do
	if [ $INDEX -lt 6 ]; then
		SCINT="LXE";
	else
		SCINT="LYSO";
	fi
	if [ $(($INDEX % 3)) = 2 ]; then
		INTER="CHER";
	else
		INTER="SCINT";
	fi
	
	case "$INDEX" in
		0) TYPE="lxe"
			;;
		1) TYPE="lxe_noCher"
			;;
		2) TYPE="lxe_noScint"
			;;
		3) TYPE="lxe_tpb"
			;;
		4) TYPE="lxe_tpb_noCher"
			;;
		5) TYPE="lxe_tpb_noScint"
			;;
		6) TYPE="lyso"
			;;
		7) TYPE="lyso_noCher"
			;;
		8) TYPE="lyso_noScint"
			;;
	esac
	
	for PDE in `seq 5 5 100`; do
		QE="0`echo "scale=2; "$PDE"/100" | bc`"
		FILENAME=$TYPE"_PHYS_QE_"$QE"_SPTR_0_ASIC_0_DT300"
		JOBFILE=$JOBPATH$FILENAME".job"
		
		cp templatePDE.job $JOBFILE

		echo "CNTJob INPUT_DATA SV 1" >> $JOBFILE
		echo $DATAPATH$data >> $JOBFILE
		echo "CNTJob FLOG S "$LOGPATH$FILENAME".log" >> $JOBFILE
		echo "CNTJob FHISTOS S "$HISTOSPATH$FILENAME"_histos.root" >> $JOBFILE
		echo "CNTJob FTREES S "$TREESPATH$FILENAME"_trees.root" >> $JOBFILE
		echo "DTOF SCINTILLATOR S "$SCINT >> $JOBFILE
		echo "ATimeMap BIN D 5" >> $JOBFILE
		echo "ATimeMap SCINTILLATOR S "$SCINT >> $JOBFILE
		echo "ATimeMap QE D "$QE >> $JOBFILE
		echo "ATimeMap INTER S "$INTER >> $JOBFILE
	done
	INDEX=$(($INDEX + 1));
done
	
#0,1,2 -> LXE
#3,4,5 -> LXE
#6,7,8 -> LYSO

#0,3,6 -> SCINT
#1,4,7 -> SCINT
#2,5,8 -> CHER

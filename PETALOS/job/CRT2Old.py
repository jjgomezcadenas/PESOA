#####     ------ Parameter File -----       ###
#                                             #  
#   use:                                      #
#                                             #
#     GROUP NAME TYPE VALUE                   #
#                                             #
#     where TYPE is:                          #
#                                             #
#          I  --> INTEGER                     #
#          D  --> FLOAT                       #
#          S  --> STRING                      #
#          IV --> INTEGER VECTOR              #
#          DV --> FLOAT VECTOR                #
#          SV --> STRING VECTOR               #
#                                             #
#     For vectors:  TYPE == vector length     #
#     Each element is decleared in new line   #
#                                             #
###############################################

#--------- PATHS with modules to be used -------#
CNTJob PATHS SV 1 
/Users/jjgomezcadenas/Documents/Development/PESOA/PETALOS/py/TOF

############################ VERBOSITY LEVEL ##########################
#---------- VERBOSITY LEVEL ----------#
CNTJob LEVEL I 1

#--------- DATA -------#
CNTJob INPUT_DATA SV 1
/Users/jjgomezcadenas/Documents/Development/PETALO/DATA/LYSO_3mm_xy2.4cm_z5cm_noCher.pet

#--------- DATA READER -------#
CNTJob READER S gateReader

#--------- OUPUT DATA FORMAT -------#
CNTJob WRITER S gateWriter

#------------- log file -------------#
CNTJob LOG I 0
CNTJob FLOG S /Users/jjgomezcadenas/Documents/Development/PETALO/log/LYSO_3mm_xy2.4cm_z5cm_noCher_QE_1_SPTR_0_ASIC_0_DT300.log

#---------- histogram file ----------#
CNTJob HISTOS 1
CNTJob FHISTOS S /Users/jjgomezcadenas/Documents/Development/PETALO/histo/
LYSO_3mm_xy2.4cm_z5cm_noCher_QE_1_SPTR_0_ASIC_0_DT300.root

#---------- histogram file ----------#
CNTJob TREES 1
CNTJob FTREES S /Users/jjgomezcadenas/Documents/Development/PETALO/tree/LYSO_3mm_xy2.4cm_z5cm_noCher_QE_1_SPTR_0_ASIC_0_DT300.root

#------ SAVE EVENTS IN OUTPUT FILE ----------# 
CNTJob SAVE I 0

#---------- NUMBER OF EVENTS TO ANALYZE ----------#
CNTJob NEVENTS I 1000

#---------- FIRST EVENT TO ANALYZE ----------#
CNTJob FEVENT I 0

#---------- Print status messages after NDEBUG events ----------#
CNTJob NDEBUG I 100


#--------- ALGORITHMS -------#
CNTJob ALGOS SV 3
AFiducial
ATimeMap
DTOF


#--------- Algo PARAMS -------#
DTOF Debug I 0
DTOF SCINTILLATOR S LYSO
DTOF VLEVEL I 3

ATimeMap Debug I 0
ATimeMap VLEVEL I 1
ATimeMap SCINTILLATOR S LYSO
ATimeMap NSIPM I 5
ATimeMap QE D 1.0
ATimeMap DTMAX D 300
ATimeMap SPTR D 0
ATimeMap ASIC D 00
ATimeMap INTER S SCINT
ATimeMap HBOX I 1

ATimeMap Box1Id IV 4
0
63
2000
2063
ATimeMap Box2Id IV 4
10000
10063
12000
12063

AFiducial VLEVEL I 1
AFiducial Debug I 0
AFiducial HBOX I 1

AFiducial Box1V1 DV 3 
-12.8 
-12.8 
-100.
AFiducial Box1V2 DV 3 
-12.8 
12.8 
-100.
AFiducial Box1V3 DV 3 
12.8 
-12.8 
-100
AFiducial Box1V4 DV 3 
12.8 
12.8 
-100
AFiducial Box1V5 DV 3 
-12.8 
-12.8 
-150
AFiducial Box1V6 DV 3 
-12.8 
12.8 
-150
AFiducial Box1V7 DV 3 
12.8 
-12.8 
-150
AFiducial Box1V8 DV 3 
12.8 
12.8 
-150
AFiducial Box2V1 DV 3 
-12.8 
-12.8 
100
AFiducial Box2V2 DV 3 
-12.8 
12.8 
100
AFiducial Box2V3 DV 3 
12.8 
-12.8 
100
AFiducial Box2V4 DV 3 
12.8 
12.8 
100
AFiducial Box2V5 DV 3 
-12.8 
-12.8 
150.
AFiducial Box2V6 DV 3 
-12.8
12.8 
150. 
AFiducial Box2V7 DV 3 
12.8 
-12.8 
150.
AFiducial Box2V8 DV 3 
12.8 
12.8 
150.
AFiducial FBox1V1 DV 3 
-12.0 
-12.0 
-101.
AFiducial FBox1V2 DV 3 
-12.0 
12.0
-101.
AFiducial FBox1V3 DV 3 
12.0 
-12.0 
-101.
AFiducial FBox1V4 DV 3 
12.0
12.0 
-101.
AFiducial FBox1V5 DV 3 
-12.0 
-12.0 
-149.
AFiducial FBox1V6 DV 3 
-12.0 
12.0 
-149.
AFiducial FBox1V7 DV 3 
12.0
-12.0 
-149.
AFiducial FBox1V8 DV 3 
12.0
12.0 
-149.
AFiducial FBox2V1 DV 3 
-12.0 
-12.0 
101
AFiducial FBox2V2 DV 3 
-12.0 
12.0 
101.
AFiducial FBox2V3 DV 3 
12.0
-12.0 
101.
AFiducial FBox2V4 DV 3 
12.0 
12.0 
101.
AFiducial FBox2V5 DV 3 
-12.0 
-12.0 
149.
AFiducial FBox2V6 DV 3 
-12.0
12.0
149. 
AFiducial FBox2V7 DV 3 
12.0 
-12.0 
149.
AFiducial FBox2V8 DV 3 
12.0
12.0 
149.
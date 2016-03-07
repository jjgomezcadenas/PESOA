#!/usr/bin/env python
from Centella import centella
from Centella import paramManager
import sys
sys.path.append('/Users/jjgomezcadenas/Documents/Development/PESOA/PETALOS/py/TOF')
from AFiducial import *
from ATimeMap import *
from DTOF import *


"""This is an auto-generated python file to

        run a set of algortihms using Centella""" 
 

algos,idsts,odsts=[],[],[]
idsts.append("/Users/jjgomezcadenas/Documents/Development/PETALO/DATA/LYSO_3mm_xy2.4cm_z5cm_noCher.pet")
pman = paramManager.ParamManager()
pman.read('CRT2.job')
vlevel=1
try: store = pman['AFiducial']
except KeyError: store = paramStore(AFiducial)
vlevel=1
algos.append(AFiducial(store,vlevel,'AFiducial'))
pman = paramManager.ParamManager()
pman.read('CRT2.job')
vlevel=1
try: store = pman['ATimeMap']
except KeyError: store = paramStore(ATimeMap)
vlevel=1
algos.append(ATimeMap(store,vlevel,'ATimeMap'))
pman = paramManager.ParamManager()
pman.read('CRT2.job')
vlevel=1
try: store = pman['DTOF']
except KeyError: store = paramStore(DTOF)
vlevel=1
algos.append(DTOF(store,vlevel,'DTOF'))
tname="analysis"
max_evt= 1000
max_deb= 100
histos= 1
hfile="/Users/jjgomezcadenas/Documents/Development/PETALO/histo/lXe_refl97_VUV3mm_xy2.4cm_z5cm_n1.7_QE_1_SPTR_0_ASIC_0_DT300_histos.root"
trees= 1
tfile="/Users/jjgomezcadenas/Documents/Development/PETALO/tree/LYSO_3mm_xy2.4cm_z5cm_noCher_QE_1_SPTR_0_ASIC_0_DT300.root"
psfile="CNTAna_PS.ps"
docfile="CNT_doc.tex"
log= 0
logfile="/Users/jjgomezcadenas/Documents/Development/PETALO/log/LYSO_3mm_xy2.4cm_z5cm_noCher_QE_1_SPTR_0_ASIC_0_DT300.log"
reader="gateReader"
writer="gateWriter"
level= 1
canvas= 1
tcanvas= 0
browser= 0
doc= 0
fevent= 0
save= 0
paths= ['/Users/jjgomezcadenas/Documents/Development/PESOA/PETALOS/py/TOF']
libs= []

c= centella.centella(algos,idsts,histos,hfile,
                      trees,tfile,psfile,level,max_evt,reader,tname,
                      canvas,tcanvas,doc,docfile,browser,max_deb,
                      fevent,save,odsts,log,logfile,writer,paths,libs)
c.run()

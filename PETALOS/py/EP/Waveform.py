from Centella.AAlgo import AAlgo
from Centella.AAlgo import AAlgo
from Centella.histoDraw import *
from Util import *
import random as rnd
from ROOT import gSystem
gSystem.Load("$GATE_DIR/lib/libGATE")

from ROOT import gate


"""
This algorithm displays waveforms. 
"""


class Waveform(AAlgo):

	############################################################
	def __init__(self, param=False, level=1, label="", **kargs):

		
		self.name = 'Waveform'
		
		AAlgo.__init__(self, param, level, self.name, 0, label, kargs)

    ### PARAMETERS
		
		self.debug = self.ints["Debug"]  #used to stop program at key break points
		self.TBIN = self.ints["TBIN"] #time bin (100 ns in NEW )

		if self.debug == 1:
			wait()


	############################################################		
	def initialize(self):

		self.m.log(1, 'Initialize()')
		
		### Defining histos
		# Event energy histogram

    ### Counters:
		self.numInputEvents = 0
		self.numOutputEvents = 0
		
		return


	############################################################
	def execute(self, event=""):

		self.m.log(2, 'Execute()')		
	
		self.numInputEvents += 1 

		pmts =  event.GetHits()
		self.npmt = len(pmts)

		self.m.log(3, " number of PMTs = %d"%(self.npmt))

		if self.debug > 1:
			wait()

		names = []

		ipmt = 0

		for pmt in pmts:
			TL, AL = [],[]   # Time list and Amplitue list 

			hid = pmt.GetSensorID()
			#stype = pmt.GetSensorType()
			xh = pmt.GetPosition().x()
			yh = pmt.GetPosition().y()
			zh = pmt.GetPosition().z()
			# Ah = pmt.GetAmplitude()

			self.m.log(3, "pmt id= %d, type= %d x0 =%7.2f mm, y0 =%7.2f mm, z0 =%7.2f mm, A = %7.2f pE"%(
				hid,ipmt,xh/mm,yh/mm,zh/mm,Ah))

			
			# time first pes (MC pes, QE =1)
			wf = pmt.GetWaveform()            
			waveform = wf.GetData()

			#waveform = pmt.GetWaveform().GetData()
			
			# sw = wf.GetSampWidth()

			# self.m.log(3, " waveform for hit ID = %d, number = %d: length = %d, swidth (ns) = %d"%(
			# 	hid, ipmt, len(waveform), sw/ns))

			ipmt+=1

			if self.debug > 1:
				wait()

			# np = 0
			# tmax = 0
			# amax = 0

			# for timeBins in waveform:
			# 	tbin = timeBins.first
			# 	time = tbin*self.TBIN*ns
			# 	if time > tmax: 
			# 		tmax = time

			# 	A = timeBins.second
				
			# 	if A > amax: 
			# 		amax = A
			# 	np+=1

			self.m.log(3, " np = %d: amax = %7.2f tmax = %7.2fns"%(np,amax,tmax))
			self.hw = bookHisto1(self.label,self.hman,
			"wfm","Waveform",25,620,630)

			for timeBins in waveform:
				tbin = timeBins.first
				time = tbin*self.TBIN*ns
				A = timeBins.second
				self.hman.fetch(self.hw).Fill(time/microsecond,A)

			self.hman.draw(self.hw, option="HIST")

			nbins = self.hman.fetch(self.hw).GetNbinsX() 

			for bins in nbins:

				AL.append(self.hman.fetch(self.hw).GetBinContent(bins));
			# hd = histoDraw()
			# hd.StartCanvas()
			# hd.Draw(self.hman.fetch(self.hw), option="HIST")
			# self.c1= TCanvas(name='c1',title='Histogram Canvas',
   #                  topX=200,topY=10,sizeX=500,sizeY=500)
			# self.hman.fetch(self.hw).Draw(self.hw)
			# self.c1.Update()

			if self.debug > 1:
				wait()
				
  
		return True

############################################################
	def finalize(self):

		self.m.log(1, 'Finalize()')

		self.m.log(1, 'Input  Events: ', self.numInputEvents)
		self.m.log(1, 'Output Events: ', self.numOutputEvents)

		return




	
		
		

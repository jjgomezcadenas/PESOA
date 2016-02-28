from Centella.AAlgo import AAlgo

from Util import *
from Geometry import *
from TOF import *
from Scintillator import *

"""
This algorithm plots the first, second, third and fourth photon time.
"""


class NPhotons(AAlgo):

	############################################################
	def __init__(self, param=False, level=1, label="", **kargs):

		"""
		DTOF Algorithm
		"""
		#self.m.log(1, 'Constructor()')

		### GENERAL STUFF
		self.name = 'NPhotons'
		
		AAlgo.__init__(self, param, level, self.name, 0, label, kargs)

    ### PARAMETERS
		
		
		self.debug = self.ints["Debug"]  #used to stop program at key break points

		self.SCINT = self.strings["SCINTILLATOR"]

		#load coordinates of box and fiducial box

		if self.SCINT == "LXE":
			self.scint = LXe() #lxe properties
		elif self.SCINT == "LYSO":
			self.scint = LYSO()
		else:
			print "scintillator not yet implemented"
			sys.exit()

		if self.debug == 1:
			wait()


	############################################################		
	def initialize(self):

		self.m.log(1, 'Initialize()')
		
		### Defining histos
		# Event energy histogram

		self.Histos()

    ### Counters:
		self.numInputEvents = 0
		self.numOutputEvents = 0

		
		return


	############################################################
	def execute(self, event=""):

		self.m.log(2, 'Execute()')	

		#get time map from previous algo

		self.sortedTimeMap = self.logman["USER"].gparam["sortedTimeMap"]
                
#                print "--------------------- Event %s -------------------" % event.GetEventID()
		
		#Compute DT
		self.ComputeNPhotons()
		
		
		if self.debug == 1:
			wait()	

		
		return True

############################################################
	def finalize(self):

		self.m.log(1, 'Finalize()')

		self.m.log(1, 'Input  Events: ', self.numInputEvents)
		self.m.log(1, 'Output Events: ', self.numOutputEvents)
		

		self.logman["USER"].ints[self.alabel("InputEvents")] = self.numInputEvents
		self.logman["USER"].ints[self.alabel("OutputEvents")] = self.numOutputEvents
	
		#self.tman.save(file_name=self.FTREES)

		return


###########################################################
	def ComputeNPhotons(self):
		"""
                    Histo with number of photons in the first DT ps
		"""

		self.m.log(2," ---ComputeDTOF---")

		TimeMapBox1 = self.sortedTimeMap[0]
		TimeMapBox2 = self.sortedTimeMap[1]

                nphotons = 0
                for (time,sipm) in TimeMapBox1:
                    if time < 300:
                        nphotons+=1

                self.hman.fill(self.nPhotons,nphotons)


###########################################################
	def Histos(self):
		"""
		book the histograms for the algo 
		"""
                # Number of photons in the first 300ps
                self.histName = "NPhotons"
	        self.nPhotons = self.defineHisto(self.histName,"Number of photons in first 300ps",1,[100],[-100],[1000])

        

############################################################
	def defineHisto(self,histoName,histoTitle,histoType,nbin,xmin,xmax):

		histo_desc = histoName
		histo_name = self.alabel(histo_desc)
		if histoType == 1:
			self.hman.h1(histo_name, histo_desc,nbin[0],xmin[0],xmax[0])
		elif histoType == 2:
			self.hman.h2(histo_name, histo_desc,
				nbin[0],xmin[0],xmax[0],
				nbin[1],xmin[1],xmax[1])
		elif histoType == 3:
			self.hman.h3(histo_name, histo_desc,
				nbin[0],xmin[0],xmax[0],
				nbin[1],xmin[1],xmax[1],
				nbin[2],xmin[2],xmax[2])
		else:
			print "not implemented"
			sys.exit()
			
		self.hman.fetch(histo_name).GetXaxis().SetTitle(histoTitle)
		return histo_name
			
	
	

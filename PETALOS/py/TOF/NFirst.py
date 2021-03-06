from Centella.AAlgo import AAlgo

from Util import *
from Geometry import *
from TOF import *
from Scintillator import *

"""
This algorithm plots the Nth photon time.
"""


class NFirst(AAlgo):

	############################################################
	def __init__(self, param=False, level=1, label="", **kargs):

		"""
		DTOF Algorithm
		"""
		#self.m.log(1, 'Constructor()')

		### GENERAL STUFF
		self.name = 'NFirst'
		
		AAlgo.__init__(self, param, level, self.name, 0, label, kargs)

    ### PARAMETERS
		
		
		self.debug = self.ints["Debug"]  #used to stop program at key break points
		self.times = self.vints["TimesPE"]  #times to plot
                self.histoRange = self.doubles["Range"] #upper limits histograms

		self.SCINT = self.strings["SCINTILLATOR"]
		self.INTER = self.strings["INTER"] # cher or scint
  		self.NINDEX = self.strings["NINDEX"] # FIX or VAR refraction index

		self.profileROOT = self.strings["VELHIST"]
                if self.profileROOT != 'None':
		    rootFile = ROOT.TFile.Open(self.profileROOT, "read")
		    rootFile.PhVelTime.Rebin2D(40,40)
		    self.profileVel = rootFile.PhVelTime.ProfileX()
		    # Needed to avoid   'PyROOT_NoneType' object error
		    self.profileVel.SetDirectory(0)
                else:
                    self.profileVel = False
	
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

                self.sortedTimeMap = {}
		
		return

	############################################################
	def execute(self, event=""):

		self.m.log(2, 'Execute()')	

		#get time map from previous algo

		self.timeMap = self.logman["USER"].gparam["TimeMap"]
                
#                print "--------------------- Event %s -------------------" % event.GetEventID()
		
		#Compute DT
		self.ComputeNFirst()
		
		
		if self.debug == 1:
			wait()	

		self.logman["USER"].gparam["sortedTimeMap"] = self.sortedTimeMap
		
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
	def ComputeNFirst(self):
		"""
		Compute DT for the first PE using directly gamma information
		DTOF = (1/2)*(dt - dtg - dpg)
		where: DT is the difference in TOF
		dt = t2 -t1 difference of time stamp of first PE 
		dtg = tg2 -tg1 difference of time stamp of gamma 1 and tGamma2 
		dpg = difference of path1 and path2, where 
		path = (n/c)*d and distance is the distance between gamma and SiPM vertex. 
		"""

		self.m.log(2," ---ComputeDTOF---")

                timeMapBox1 = {}
                timeMapBox2 = {}

                #for sipmhit in self.timeMap.SiPmMapDT(1):
                for sipmhit in self.timeMap.SiPmMap(1):
                    for w in sipmhit[1].W:
                        timeMapBox1[w] = sipmhit[1]

                #for sipmhit in self.timeMap.SiPmMapDT(2):
                for sipmhit in self.timeMap.SiPmMap(2):
                    for w in sipmhit[1].W:
                        timeMapBox2[w] = sipmhit[1]

		TimeMapBox1 = sorted(timeMapBox1.items(), key=sortTimesSipm)
		TimeMapBox2 = sorted(timeMapBox2.items(), key=sortTimesSipm)

                self.sortedTimeMap = [TimeMapBox1, TimeMapBox2]

                #DTOF
		vertexBox1 =self.timeMap.InteractionVertex(box=1)
		vertexBox2 =self.timeMap.InteractionVertex(box=2)

                for i in self.times:
                    sipmHit1 = TimeMapBox1[i-1][1]
                    sipmHit2 = TimeMapBox2[i-1][1]

                    dbox1 = distance(sipmHit1.XYZ(),vertexBox1.XYZ())
                    #tpath1 = dbox1*self.scint.RefractionIndex()/c_light
                    #tpath1 = dbox1 * 1/self.vel
                    timeDiff1 = (TimeMapBox1[i-1][0] - TimeMapBox1[0][0])/ps
                    vel = photonVelocity(self.profileVel,self.SCINT, self.NINDEX, self.INTER, timeDiff1)
                    tpath1 = dbox1 * 1/vel

        	    dbox2 = distance(sipmHit2.XYZ(),vertexBox2.XYZ())
        	    #tpath2 = dbox2*self.scint.RefractionIndex()/c_light
                    #tpath2 = dbox2 * 1/self.vel
                    timeDiff2 = (TimeMapBox2[i-1][0] - TimeMapBox2[0][0])/ps
                    vel = photonVelocity(self.profileVel,self.SCINT, self.NINDEX, self.INTER, timeDiff2)
                    tpath2 = dbox2 * 1/vel

		    timePeBox1 = TimeMapBox1[i-1][0] - tpath1 - vertexBox1.t
		    timePeBox2 = TimeMapBox2[i-1][0] - tpath2 - vertexBox2.t

                    histName = "NFirst.Time_" + str(i) + "_PEBox1"
                    #self.hman.fill(histName,TimeMapBox1[i-1][0]/ps)
                    self.hman.fill(histName,timePeBox1/ps)


###########################################################
	def Histos(self):
		"""
		book the histograms for the algo 
		"""
                for i in self.times:
                    histName = "Time_" + str(i) + "_PEBox1"
	            self.defineHisto(histName,"Time first PE Box1 (ps)",1,[200],[-300],[self.histoRange])
        

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
			
	
	

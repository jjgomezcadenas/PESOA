from Centella.AAlgo import AAlgo

from Util import *
from Geometry import *
from TOF import *
from Scintillator import *

"""
This algorithm computes the Coincidence Resolution Time using AVG of N first pe or pe's in DT
"""


class AVG(AAlgo):

	############################################################
	def __init__(self, param=False, level=1, label="", **kargs):

		"""
		AVG Algorithm
		"""
		#self.m.log(1, 'Constructor()')

		### GENERAL STUFF
		self.name = 'AVG'
		
		AAlgo.__init__(self, param, level, self.name, 0, label, kargs)

    ### PARAMETERS
		
		
		self.debug = self.ints["Debug"]  #used to stop program at key break points
		self.SCINT = self.strings["SCINTILLATOR"]
		self.INTER = self.strings["INTER"] # cher or scint
  		self.NINDEX = self.strings["NINDEX"] # FIX or VAR refraction index

		self.npe = self.ints["NPE"]  #number of pe to avg

		self.xres = self.doubles["XRES"]  #X resolution
		self.yres = self.doubles["YRES"]  #X resolution
		self.zres = self.doubles["ZRES"]  #X resolution


		#load coordinates of box and fiducial box

		if self.SCINT == "LXE":
			self.scint = LXe() #lxe properties
			if self.NINDEX == "VAR":
				if self.INTER ==  "CHER":
					self.vel = 0.14/ps
				else:
					self.vel = 0.0886/ps
			else:
				self.vel = c_light/self.scint.RefractionIndex()
		elif self.SCINT == "LYSO":
			self.scint = LYSO()
                        self.vel = c_light/self.scint.RefractionIndex()
		else:
			print "scintillator not yet implemented"
			sys.exit()

		print self.scint

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

		self.timeMap = self.logman["USER"].gparam["TimeMap"]
		self.sortedTimeMap = self.logman["USER"].gparam["sortedTimeMap"]
		
		#Compute DT
		self.ComputeAVG() 
		
		
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
	def ComputeAVG(self):
		"""
		Compute DT for the first PE using directly gamma information
		AVG = (1/2)*(dt - dtg - dpg)
		where: DT is the difference in TOF
		dt = t2 -t1 difference of time stamp of first PE 
		dtg = tg2 -tg1 difference of time stamp of gamma 1 and tGamma2 
		dpg = difference of path1 and path2, where 
		path = (n/c)*d and distance is the distance between gamma and SiPM vertex. 
		"""

		self.m.log(2," ---ComputeAVG---")

                TimeMapBox1 = self.sortedTimeMap[0]
                TimeMapBox2 = self.sortedTimeMap[1]

		vertexBox1 =self.timeMap.InteractionVertex(box=1)
		vertexBox2 =self.timeMap.InteractionVertex(box=2)
    
                t1 = 0
                t2 = 0
                for i in range(self.npe):
                    dbox1 = distance(TimeMapBox1[i][1].XYZ(),vertexBox1.XYZ())
                    tpath1 = dbox1 * 1/self.vel
                    dbox2 = distance(TimeMapBox2[i][1].XYZ(),vertexBox2.XYZ())
                    tpath2 = dbox2 * 1/self.vel

                    t1 += TimeMapBox1[i][0] - tpath1
                    t2 += TimeMapBox2[i][0] - tpath2

                    t1Avg = (t1/(i+1) - vertexBox1.t)
                    t2Avg = (t2/(i+1) - vertexBox2.t)

                    dtof = 0.5*(t2Avg - t1Avg)

                    self.hman.fill(self.dtof1[i],dtof/ps)
                    self.hman.fill(self.dtof2[i],dtof/ps)
                    self.hman.fill(self.dtof3[i],dtof/ps)


	############################################################		
	def Histos(self):
		"""
		book the histograms for the algo 
		"""

                self.avgAll = self.defineHisto("avgAll","avgAll",1,[80],[-200],[200])

                self.dtof1 = []
                self.dtof2 = []
                self.dtof3 = []

                for i in range(self.npe):
                    histName = "DTOF1N" + str(i+1) 
	            self.dtof1.append(self.defineHisto(histName,histName,1,[50],[-500],[500]))
                    histName = "DTOF2N" + str(i+1) 
	            self.dtof2.append(self.defineHisto(histName,histName,1,[80],[-200],[200]))
                    histName = "DTOF3N" + str(i+1) 
	            self.dtof3.append(self.defineHisto(histName,histName,1,[80],[-100],[100]))


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
			
	
	

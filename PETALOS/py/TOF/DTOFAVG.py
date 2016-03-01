from Centella.AAlgo import AAlgo

from Util import *
from Geometry import *
from TOF import *
from Scintillator import *

"""
This algorithm computes the Coincidence Resolution Time using AVG of N first pe or pe's in DT
"""


class DTOFAVG(AAlgo):

	############################################################
	def __init__(self, param=False, level=1, label="", **kargs):

		"""
		DTOFAVG Algorithm
		"""
		#self.m.log(1, 'Constructor()')

		### GENERAL STUFF
		self.name = 'DTOFAVG'
		
		AAlgo.__init__(self, param, level, self.name, 0, label, kargs)

    ### PARAMETERS
		
		
		self.debug = self.ints["Debug"]  #used to stop program at key break points
		self.SCINT = self.strings["SCINTILLATOR"]
		self.INTER = self.strings["INTER"] # cher or scint

		self.npe = self.ints["NPE"]  #number of pe to avg
		self.dts = self.vints["DTs"]  # time windows to avg

		self.xres = self.doubles["XRES"]  #X resolution
		self.yres = self.doubles["YRES"]  #X resolution
		self.zres = self.doubles["ZRES"]  #X resolution


		#load coordinates of box and fiducial box

		if self.SCINT == "LXE":
			self.scint = LXe() #lxe properties
                        if self.INTER ==  "CHER":
                            self.vel = 0.14/ps
                        else:
                            self.vel = 0.0886/ps
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
		self.ComputeDTOFAVG() 
		
		
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
	def ComputeDTOFAVG(self):
		"""
		Compute DT for the first PE using directly gamma information
		DTOFAVG = (1/2)*(dt - dtg - dpg)
		where: DT is the difference in TOF
		dt = t2 -t1 difference of time stamp of first PE 
		dtg = tg2 -tg1 difference of time stamp of gamma 1 and tGamma2 
		dpg = difference of path1 and path2, where 
		path = (n/c)*d and distance is the distance between gamma and SiPM vertex. 
		"""

		self.m.log(2," ---ComputeDTOFAVG---")

		vertexBox1 =self.timeMap.InteractionVertex(box=1)
		vertexBox2 =self.timeMap.InteractionVertex(box=2)
		siPMHit1 = self.timeMap.SiPmHit(box=1,index=0)
		siPMHit2 = self.timeMap.SiPmHit(box=2,index=0)

		dtg = vertexBox2.t - vertexBox1.t
		
		dbox1 = distance(siPMHit1.XYZ(),vertexBox1.XYZ())
		#tpath1 = dbox1*self.scint.RefractionIndex()/c_light
                tpath1 = dbox1 * 1/self.vel
		dbox2 = distance(siPMHit2.XYZ(),vertexBox2.XYZ())
		#tpath2 = dbox2*self.scint.RefractionIndex()/c_light
                tpath2 = dbox2 * 1/self.vel

		dpg = tpath2 - tpath1

                #Smear vertex if needed
                dpgSmear = 0
                if self.xres > 0 or self.yres > 0 or self.zres > 0:
                    vertex1 = SmearVertex(vertexBox1.XYZ(),self.xres, self.yres, self.zres)
                    vertex2 = SmearVertex(vertexBox2.XYZ(),self.xres, self.yres, self.zres)

                    dbox1Smear = distance(siPMHit1.XYZ(),vertex1)
                    #tpath1Smear = dbox1Smear*self.scint.RefractionIndex()/c_light
                    tpath1Smear = dbox1Smear*1/self.vel
                    dbox2Smear = distance(siPMHit2.XYZ(),vertex2)
                    #tpath2Smear = dbox2Smear*self.scint.RefractionIndex()/c_light
                    tpath2Smear = dbox2Smear*1/self.vel

                    dpgSmear = tpath2Smear - tpath1Smear

                t1 = 0
                t2 = 0
                TimeMapBox1 = self.sortedTimeMap[0]
                TimeMapBox2 = self.sortedTimeMap[1]
                for i in range(self.npe):

                    t1 += TimeMapBox1[i][0]
                    t2 += TimeMapBox2[i][0]

                    dt  = (t2 - t1) / (i+1)
                    dtof = 0.5*(dt - dtg - dpg)

                    self.hman.fill(self.dtof1[i],dtof/ps)
                    self.hman.fill(self.dtof2[i],dtof/ps)
                    self.hman.fill(self.dtof3[i],dtof/ps)

                    if self.xres > 0 or self.yres > 0 or self.zres > 0:
                        dtofSmear = 0.5*(dt - dtg - dpgSmear)
                        self.hman.fill(self.dtof1_res[i],dtofSmear/ps)
                        self.hman.fill(self.dtof2_res[i],dtofSmear/ps)
                        self.hman.fill(self.dtof3_res[i],dtofSmear/ps)

                #Compute AVG within DT
                time0_Box1 = TimeMapBox1[0][0]
                time0_Box2 = TimeMapBox2[0][0]

                size = min(len(TimeMapBox1),len(TimeMapBox2))

                t1s = [0] * len(self.dts)
                t2s = [0] * len(self.dts)
                nphotons = [0] * len(self.dts)
                for i in range(size):
                    stop = False
                    for j in range(len(self.dts)):
                        if (TimeMapBox1[i][0] - time0_Box1) < self.dts[j]*ps and (TimeMapBox2[i][0] - time0_Box2) < self.dts[j]*ps:
                            nphotons[j]+=1
                            t1s[j] += TimeMapBox1[i][0]
                            t2s[j] += TimeMapBox2[i][0]
                        else:
                            stop = True
                    if stop:
                        break
                        
                for j in range(len(self.dts)):
                    dt  = (t2s[j] - t1s[j]) / nphotons[j]
                    dtof = 0.5*(dt - dtg - dpg)

                    self.hman.fill(self.dtof1_dt[j],dtof/ps)
                    self.hman.fill(self.dtof2_dt[j],dtof/ps)
                    self.hman.fill(self.dtof3_dt[j],dtof/ps)

                    if self.xres > 0 or self.yres > 0 or self.zres > 0:
                        dtofSmear = 0.5*(dt - dtg - dpgSmear)
                        self.hman.fill(self.dtof1_dt_res[j],dtofSmear/ps)
                        self.hman.fill(self.dtof2_dt_res[j],dtofSmear/ps)
                        self.hman.fill(self.dtof3_dt_res[j],dtofSmear/ps)
                    

	############################################################		
	def Histos(self):
		"""
		book the histograms for the algo 
		"""

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


                self.dtof1_dt = []
                self.dtof2_dt = []
                self.dtof3_dt = []

                for i in self.dts:
                    histName = "DTOF1_DT" + str(i) 
	            self.dtof1_dt.append(self.defineHisto(histName,histName,1,[50],[-500],[500]))
                    histName = "DTOF2_DT" + str(i) 
	            self.dtof2_dt.append(self.defineHisto(histName,histName,1,[80],[-200],[200]))
                    histName = "DTOF3_DT" + str(i) 
	            self.dtof3_dt.append(self.defineHisto(histName,histName,1,[80],[-100],[100]))

                if self.xres > 0 or self.yres > 0 or self.zres > 0:
                    self.dtof1_res = []
                    self.dtof2_res = []
                    self.dtof3_res = []
                    self.dtof1_dt_res = []
                    self.dtof2_dt_res = []
                    self.dtof3_dt_res = []
    
                    for i in range(self.npe):
                        histName = "SmearDTOF1N" + str(i+1) 
                        self.dtof1_res.append(self.defineHisto(histName,histName,1,[50],[-500],[500]))
                        histName = "SmearDTOF2N" + str(i+1) 
                        self.dtof2_res.append(self.defineHisto(histName,histName,1,[80],[-200],[200]))
                        histName = "SmearDTOF3N" + str(i+1) 
        	        self.dtof3_res.append(self.defineHisto(histName,histName,1,[80],[-100],[100]))

                    for i in self.dts:
                        histName = "SmearDTOF1_DT" + str(i) 
    	                self.dtof1_dt_res.append(self.defineHisto(histName,histName,1,[50],[-500],[500]))
                        histName = "SmearDTOF2_DT" + str(i) 
    	                self.dtof2_dt_res.append(self.defineHisto(histName,histName,1,[80],[-200],[200]))
                        histName = "SmearDTOF3_DT" + str(i) 
    	                self.dtof3_dt_res.append(self.defineHisto(histName,histName,1,[80],[-100],[100]))
                    

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
			
	
	

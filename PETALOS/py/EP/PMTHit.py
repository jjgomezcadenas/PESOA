###########################################################
class PMTHit(object):
	def __init__(self,nid,hid,x,y,z,T,A):
		"""
		Describes a hit in a PMT
		nid number of PMT (from 0 to 11)
		hid: id of PMT as given in reconstructoin
		x,y,z: position of PMT
		 
		"""
		self.nid = nid
		self.hid = hid
		self.xyz = Point3D(x,y,z)
		self.A = A  #total amplitude
		self.T =T # vector of times with non null amplitudes
		self.Q = sum(A) #vector of amplitudes
		

	def __str__(self):
		
		s="""PMThit\n
			nid = %d, id = %d A = %7.2f  
			x = %7.2f mm, y = %7.2f mm z = %7.2f mm 
	
			"""%(self.nid, self.hid, 
				self.hit.x/mm, self.hit.y/mm, self.hit.z/mm
				)
		s+="Waveform (ns)= %s"%(self.W)
		return s

		

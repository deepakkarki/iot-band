import bluetooth as bt
import time

devices = [0]
def connect(addr=None, name=None):
	'''
	This fuction is used to establish a connection between the computer and device.
	addr is the MAC address of the bt chip, name is name of the device
	specify either one to connect to the device, specifing addr is much faster
 	returns a socket object, which has a stream to the device
	'''
	'''devs = bt.discover_devices()
	#returns a list of addresses of visible bluetooth devices
	if addr and addr in devs:
		pass
		
	elif name:
		for dev in devs:
			if name == bt.lookup_name( dev ):
				addr = dev
				
	else : return None
	'''
	port = 1
	sock=bt.BluetoothSocket( bt.RFCOMM )
	sock.connect((addr, port))
	
	return sock
	

def main(con):
	try:
		while True:
			res = con.recv(100) #gets "1,2" => device_id 1, command 2
			if "," not in res:
				res += con.recv(100)
			
			print "recv : ", res
			res = res.split(",")
			if int(res[0]) == 1 or int(res[0]) == 3:
				devices[1].send('1')
			else:
				devices[1].send('0')
	
	except KeyboardInterrupt as e:
		print "Closing Connection"
		con.close()
		print "Good Bye!! hum hain rahi nerd ke, phir melange chalte chalte" #hindi 
		
if __name__ == '__main__':
	band = connect(addr = '00:12:12:24:16:30') 
	
	devices.append(connect(addr = '30:14:10:13:10:81'))
	
	main(band)


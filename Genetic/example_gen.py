import random
MaxTaskRange =200
MinTaskRange =1
TaskNum=200
speeds=[1,2,4]
MachineNum=40
f= open("./build/tasks.txt","w+")
#for i in range(0,TaskNum):
#	x=random.randint(MinTaskRange, MaxTaskRange);
#	f.write("%d\n" % (x*2+1))

for i in range(0,30):
	f.write("%d\n" % (3))
for i in range(0,10):
	f.write("%d\n" % (2))
for i in range(0,10):
	f.write("%d\n" % (4))
for i in range(0,10):
	f.write("%d\n" % (6))
f.close() 
f= open("./build/machines.txt","w+")
for i in range(0,MachineNum):
	x=random.randint(0, 2);
	f.write("%d\n" % speeds[x])
f.close() 


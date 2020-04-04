import random
MaxTaskRange =100
MinTaskRange =1
TaskNum=1200
speeds=[1,2,4]
MachineNum=30
f= open("./build/tasks.txt","w+")
for i in range(0,TaskNum):
	x=random.randint(MinTaskRange, MaxTaskRange);
	f.write("%d\n" % x)
f.close() 
f= open("./build/machines.txt","w+")
for i in range(0,MachineNum):
	x=random.randint(0, 2);
	f.write("%d\n" % speeds[x])
f.close() 


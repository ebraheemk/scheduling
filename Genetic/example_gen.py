import random
MaxTaskRange =111
MinTaskRange =0
TaskNum=15
speeds=[1,2,4] 
MachineNum=3
f= open("./build/tasks.txt","w+")
for i in range(0,TaskNum):
	x=random.randint(MinTaskRange, MaxTaskRange);
	f.write("%d\n" % (x*2+1))


f.close() 
f= open("./build/machines.txt","w+")
for i in range(0,MachineNum):
	x=random.randint(0, 2);
	f.write("%d\n" % speeds[x])
f.close() 


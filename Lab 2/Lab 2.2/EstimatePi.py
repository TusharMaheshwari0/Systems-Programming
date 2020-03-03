#Name: Kyle Johnson
#Class: ETEC2110
#Section: 02
#Assignment 2.2
"""
Rewrite the program above using the Python language. Be sure to add code that prints out how long the
program took to execute.
How much faster was the 'C' implementation?
Be sure to demonstrate and submit each program. Also make sure that each of your programs includes the
proper comment block at the top.
"""
import time, math, random
points_inside_circle = 0
start_time = time.time()
for i in range(100000001):
     x=random.randint(0, 1000)
     y=random.randint(0, 1000)
     d= x*x + y*y
     d=math.sqrt(d)
     if(d < 1000):
        points_inside_circle+=1
     if(i%10000 == 0 and i !=0):
        pi = ((points_inside_circle * 4) / i)
        print("Total Count: " + str(i) + ", Points inside circle: " + str(points_inside_circle) + ", Estimate of Pi: " + str(pi))

print("Total Time taken (in seconds): " + str(time.time()-start_time))

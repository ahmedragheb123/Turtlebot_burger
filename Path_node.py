#!/usr/bin/env python3
import rospy
import numpy as num
import matplotlib.pyplot as plot
import time
from geometry_msgs.msg import Twist
wheel_radius = 0.033 # in meters
wheel_base = 0.16 # in meters
dt=0.1 # time step in seconds
speed = 0
thetadot = 0
total_time = 10.0 # total simulation time in seconds
def callback(array_msg):
    #rospy.loginfo("Received array: %s", array_msg.data)
    global speed, thetadot
    speed = array_msg.linear.x * -1
    thetadot = array_msg.angular.z *-1 * 2
    if speed <= 0.04 and speed >= -0.04:
    	speed =0
    	
class DifferentialDriveRobot:
    def __init__ (self, wheel_radius, wheel_base):
        self.wheel_radius = wheel_radius
        self.wheel_base = wheel_base
        self.x =0.0 #@initial x position
        self.y=0.0 #e initial y position
        self.theta=0.0 #@initial orientation
    def move(self, V, thetadot, dt):#Compute wheel speeds
            vr = (2*speed + thetadot*self.wheel_base) / (2*self.wheel_radius)
            vl = (2*speed - thetadot*self.wheel_base) / (2*self.wheel_radius)
            #Update robot pose
            self.x += dt*(self.wheel_radius/2)*(vr +vl)*num.cos(self.theta)
            self.y += dt*(self.wheel_radius/2)* (vr +vl) * num.sin(self.theta)
            self.theta += dt* (self.wheel_radius/self.wheel_base)* (vr - vl)
    def plot_robot(self):
        #Plot robot
        plot.plot(self.x,self.y,'ro')
        plot.quiver(self.x,self.y, num.cos(self.theta), num.sin(self.theta))
        plot.axis('equal')
        plot.grid(True)
def listener():
    global speed, thetadot, wheel_radius, wheel_base, dt, total_time, Flag_recieved
    rospy.init_node('ahmed', anonymous=True)
    rospy.Subscriber("cmd_vel", Twist, callback)
    robot = DifferentialDriveRobot(wheel_radius, wheel_base)
    while not rospy.is_shutdown():
        robot.move(speed, thetadot, dt)
        robot.plot_robot()
        plot.draw()
        plot.pause(0.1)
if __name__ == '__main__':
	try:
		listener()
	except rospy.ROSInterruptException:
        	pass
    
    

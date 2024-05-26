#! /user/bin/env python 
#"""声明了一个解释器"""

import rospy

if __name__ == '__main__':
    rospy.init_node("hello-python")
    rospy.loginfo("hello world  这是python")
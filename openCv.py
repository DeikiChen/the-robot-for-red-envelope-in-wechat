# -*- coding: utf-8 -*-
#__author__="Guokr Lab & Deiki"
#注意：本实例在mac上开发完成，程序移植至其他平台时可能会遇到参数不一致的问题。
#本程序主要原理是通过opencv获取图像信息，并分辨出黄色的色块和位置，但条件符合红包的情况时，发送执行指令
#程序运行时需要将串口设置好并插上arduino,否则可能会报错

import cv2
import numpy as np
import serial, time

#'/dev/cu.usbmodem1421'为串口名字，使用前需要使用修改为执行抢红包任务，9600为串口波特率

arduino = serial.Serial('/dev/cu.usbmodem1421', 9600, timeout=.1)

time.sleep(1)

#cv2.VideoCapture(1)函数中的参数用于摄像头选择，例如当一台电脑有两个摄像头时，默认主摄像头为0，外接的摄像头为1；本实例在OS X
cap=cv2.VideoCapture(1)

count=0
while(1):
    ret,frame=cap.read()

    hsv=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

    lower_blue=np.array([0,50,50])
    upper_blue=np.array([23,255,255])

    mask=cv2.inRange(hsv,lower_blue,upper_blue)
    res=cv2.bitwise_and(frame,frame,mask=mask)

    #cv2.imshow('frame',frame)
    #cv2.imshow('mask',mask)
    #cv2.imshow('res',res)

    gray = cv2.cvtColor(res,cv2.COLOR_BGR2GRAY)
    ret, binary = cv2.threshold(gray,127,255,cv2.THRESH_BINARY)
    edges=cv2.Canny(res,100,200)
    cv2.imshow('edges',edges)
    contours, hierarchy = cv2.findContours(binary,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
    cv2.drawContours(res,contours,-1,(0,0,255),3)
    cv2.imshow("res", res)

    cont=len(contours)
    #print cont
    if cont!=0:
        for j in range(0,cont-1):
            cnt = contours[j]
            M = cv2.moments(cnt)
            #area变量为检测出来的黄色色块的面积，红包的面积大小会根据摄像头的参数和摄像头到手机的距离
            #出现不同，开始抢红包之前可以将后面的#print "area =", area  程序取消注释，运行后输出面积结果，
            #排除其他黄颜色干扰，输出来最大的数值就是红包的面积了

            area = cv2.contourArea(cnt)
            #print "area =", area

            #例如我的红包面积是6000，那就在下面这这段程序中将area的阈值设置为5000以上。
            #大家可以根据实际情况设置阈值
            if M['m10']!=0  and  M['m01']!=0 and area >5000:
                cx = int(M['m10']/M['m00'])
                cy = int(M['m01']/M['m00'])
                print cx,cy
                # print cx,cy会将大于阈值的红包的质信打印出来。从这些数值中挑选出最新的红包出现的质心
                # 根据这个数值画出一个可能区间，当有红包在这个区间内出现，就会通过串口发送一个“A”给arduino
                if cx>=835 and cx<=900 and cy>=300 and cy<=360:
                    arduino.write("A")
                    time.sleep(3)


        print count
        count=count+1

    #程序运行时，按esc可以退出
    k=cv2.waitKey(5)&0xFF
    if k==27:
        break
cv2.destroyAllWindows()
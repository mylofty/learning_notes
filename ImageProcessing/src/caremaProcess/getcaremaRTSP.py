#coding:utf-8
import cv2


# 大华摄像rtsp协议
# user: admin
# pwd: admin
# ip: 192.168.1.108
video_cap = cv2.VideoCapture("rtsp://admin:admin@192.168.1.108/cam/realmonitor?channel=1&subtype=0")#"rtsp://admin:admin@192.168.1.108/cam/realmonitor?channel=1&subtype=0")

width =  int(video_cap.get(3))
height = int(video_cap.get(4))
fps = video_cap.get(cv2.CAP_PROP_FPS)
print('video width {} and height {}, fps {} '.format(width, height, fps))
video_cap.set(cv2.CAP_PROP_BUFFERSIZE, 3)
orgin_video = cv2.VideoWriter("orgin_video.avi", cv2.VideoWriter.fourcc('M', 'J', 'P', 'G'), fps, (width, height))
modify_video = cv2.VideoWriter("modify_video.avi", cv2.VideoWriter.fourcc('M', 'J', 'P', 'G'), fps, (width, height))
# video_cap.set(3, 340)
# video_cap.set(4, 400)
print (video_cap.isOpened())

while True:
	# t1 = cv2.getTickCount()
	success, frame = video_cap.read()		# 默认video缓冲区保持38帧,read()处理不及将会丢去
	if success:
		orgin_video.write(frame)
		# cv2.imshow("live",frame)
		MAX_KERNEL_LENGTH = 31		#对图像进行均值平滑
		for i in range(1, MAX_KERNEL_LENGTH, 2):
			dst = cv2.blur(frame, (i, i))

		modify_video.write(dst)
		cv2.imshow("live",frame)
	# t2 = cv2.getTickCount()
	if cv2.waitKey(1) > 0:
		break 


    
    

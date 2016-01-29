注意，抢红包机械臂制作需要一定的技术基础！！！
机械臂使用的技术只要是arduino及外围电路、python编程、openCV视觉处理，请开始制作之前一定要先了解这些东西！

图像识别软件环境要求：较新的OS X操作系统Python 2.7.11 openCVNumpy
硬件要求：
摄像头
arduino和舵机组成的机械臂系统
火腿肠【openCV安装办法】1.安装Homebrew在mac终端执行  ruby -e "$(curl -fsSL https://raw.github.com/Homebrew/homebrew/go/install)"2.安装CMake在mac终端执行  brew install cmake3.安装openCVbrew install opencv【Numpy安装办法】1.安装pip在mac终端执行sudo easy_install pip2.安装numpy库在mac终端执行pip install numpy

技术包资料中包含一个openCV.py文件，本脚本程序用于计算机图像识别微信红包，程序执行前需要修改一些参数。程序内有详细的参数修改指导。请阅读程序中的注释。
红包机器人-机械结构.pdf 文件为简单版的抢红包机器人的机械零件，我们这边用2mm亚克力板直接切割，然后用胶粘或者螺丝紧固。【抢红包机器人硬件组成】抢红包机器人的动作执行通过三个舵机完成。开始执行抢红包之前，通过三个滑动变阻器控制舵机转动，手动执行动作，每次执行动作时按一次按钮，串口会返回当前的舵机的角度，将每个动作的角度记录下来，填写到数组data_x、data_y和data_z中，当计算机通过串口向arduino发送指令“A”时，arduino会根据已经录入的数据开始按顺序执行。



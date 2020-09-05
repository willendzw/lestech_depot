## 编译使用

firefly-rk3399-gpio.h为头文件，需要添加到编译路径中
包含头文件, include "firefly-rk3399-gpio.h"

libfireflyrk3399gpio.a为静态库文件，libfireflyrk3399gpio.so为动态库文件
编译示例：gcc -o io-test io-test.c -lfireflyrk3399gpio

执行时需要root权限
sudo ./io-test


## 函数说明

- int firefly_rk3399_initRegMap (void)
  初始化，返回执行状态，-1表示失败

- void firefly_rk3399_pinMode(int pin,int mode)
  配置引脚IO模式
  pin:引脚值，比如GPIO2_D3,因为rk3399有5组GPIO bank：GPIO0~GPIO4，每组又以 A0~A7, B0~B7, C0~C7, D0~D7共32个管脚，所以pin的值为：
  > 32 * 2 + 8 * 3(A-D) + 3 = 91
  mode:INPUT,OUTPUT

- void firefly_rk3399_digitalWrite (int pin, int value)
  设置输出引脚的输出电平值
  pin：引脚值
  value：引脚输出的电平值。值为HIGH或LOW，分别代表高低电平

- int firefly_rk3399_digitalRead (int pin)
  读取一个引脚的电平值
  pin：引脚值
  返回：引脚上的电平，值为HIGH或LOW，分别代表高低电平

- void firefly_rk3399_pullUpDnControl (int pin, int pud)
  设置输入引脚的拉电阻模式。
  pin：引脚值
  pud：拉电阻模式
  	 PUD-OFF     	关闭拉电阻
  	 PUD_UP    	 	上拉电阻
  	 PUD_DOWN    	下拉电阻
	 PUD_BUS_HOLD	Bus keeper


	

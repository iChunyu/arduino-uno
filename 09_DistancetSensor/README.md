# 09 距离传感器

本例将测试 HC-SR04 距离传感器。

## 基本原理

HC-SR04 使用超声波测距，原理是测距模块发出声波，声波遇到物体发生反射，模块接收反射声波，由时间差和声速计算得到距离。

HC-SR04 的四个引脚分别为：

- `Vcc`：电源；
- `GND`：接地；
- `Trig`：触发（Trigger）；
- `Echo`：响应。

顾名思义，`Trig` 引脚接收来自 Arduino的数字信号（高电平），该信号触发模块发射 40 kHz 的超声波；模块接收到反射的超声波之后，`Echo` 引脚输出高电平，根据 `Trig` 和 `Echo` 之间动作的时间差和声速即可计算距离。`Vcc` 接电源线，`GND` 接地。

而计算方法也不需要我们编写，`NewPing` 库里就有相关方法可以使用。

模块参数如下：

- 测量距离：2 ~ 450 cm；
- 分辨率：0.3 cm；
- 测量频率：40 Hz（最快每25 ms 测量一次）；
- 测量角度：15 deg；
- 工作电压：4.5 ~ 5.5 V；
- 工作电流：10 ~ 40 mA。

连接方式如下图所示：

![](./HC-SR04.png)


## 算法实现

在 coding 之前，先导入 `NewPing` 库，这也很简单，打开 Arduino 的 IDE，点击工具---管理库打开库管理器，搜索 `NewPing`，点击安装，然后在程序开头

```arduino
#include <NewPing.h>
```

即可。

我们定义7号端口口为触发端口，8号端口为响应端口，测量距离上限值为 400 cm，并定义一个浮点数记录距离。

```arduino
int trigPin = 7;
int echoPin = 8;
float maxDistance = 400.0;
float distance;
```

声明模块的参数

```arduino
NewPing sonar(trigPin, echoPin, maxDistance);
```

### 初始化设置

初始化时启用串口，默认 9600 波特率：

``` arduino
void setup() {
Serial.begin(9600);
}
```

### 程序主体

进入 `loop()` 函数，首先将得到的相应存储到浮点数 `distance` 中：

```arduino
distance = sonar.ping_cm();
```

当距离大于等于 400 cm 或者小于等于 2 cm 时，认为超出了距离传感器的测量范围，给出 “Out of range” 的提示，在此区间则认为可以测量并输出；输出结果到串口监视器，并保持 1000 ms：

```arduino
Serial.print("Distance = ");
if (distance >= 400 || distance <= 2)
  {
    Serial.println("Out of range");
  }
  else
  {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(1000);
```


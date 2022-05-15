# 06 舵机控制

本例将测试舵机的驱动，将涉及手动构造 PWM 波。

## 基本原理

本例使用的舵机为TIANKONGRC-TS90A，其工作电压为 4.8 V，由 PWM 波驱动。PWM 波的周期为 20 ms（50 Hz），脉冲宽度在 0.5 ms ～ 2.5 ms 之间，与驱动的角度成线性关系。

舵机的三条线分别为：

- 最外侧橙色线：PWM 信号线；
- 中间的红色线：电源线；
- 最外侧黑色线：地线。

连接方式如下图所示

<div align=center>
    <img src=./MicroServo.svg width=60% />
</div>

## 算法实现

本例中所涉及的 PWM 将自定义，因此任意选择输出接口即可，这里选为 `11` 号端口，定义

``` ardunio
int pinEngine = 11;               // PWM pin
```

由于舵机的转角与 PWM 波的脉冲宽度相关，调整转角即为调整脉冲宽度，定义每次调整的脉冲宽度（增量）为变量 `pulseDel`。对于本例所用的舵机，其固定的脉冲周期，最小、最大脉宽分别在程序的最前端进行定义：

``` arduino
// basical properties, don't modify
float pulsePeriod = 20;           // period of reference pulse (ms)
int pulseMin = 500;               // (us)
int pulseMax = 2500;              // (us)
```

注意脉宽的单位为微秒，因而在保持时应当使用 `delayMicroseconds()` 函数。

### 初始化设置

初始化时声明输出端口，并定义初始脉冲宽度：

``` arduino
void setup() {
  pinMode(pinEngine, OUTPUT);
  pulseWid = pulseMin;
}
```

### 程序主体

程序的主体部分为自定义的 PWM 波，只需要在 `pulseWid` 变量记录的脉宽范围内输出高电平，在 `pulsePeriod` 剩下的时间内维持低电平即可。为了确保舵机运转到指定位置，通常可以将指定的 PWM 波重复数次：

``` arduino
for ( int k = 0; k < Nrepeat; k++) {
    digitalWrite(pinEngine, HIGH);
    delayMicroseconds(pulseWid);
    digitalWrite(pinEngine, LOW);
    delay(pulsePeriod-pulseWid/1000);
}
```

然后，判定当前的脉宽是否达到允许限值，若达到允许限值，则改变增量的符号从而改变脉宽增大或减小，以确保其在允许范围之内。并根据增量计算下一步脉宽即可。

``` arduino
if ( (pulseWid >= pulseMax && pulseDel > 0) || (pulseWid <= pulseMin && pulseDel < 0) ) {
    pulseDel = -pulseDel;
  }
pulseWid += pulseDel;
```

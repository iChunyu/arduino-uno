# 11 ADC 模数转化

为了将模拟信号转化为数字信号以供数字计算单元进行处理，需要使用模数转换器（Analog-to-Digital Converter, ADC）。Arduino 内置 10 bit ADC，本例将展示如何使用 `analogRead()` 读取 ADC 转化后的数字信号。


## 基本原理

ADC 的量化误差由位数 $\mu$ 和最大的输入电压 $V_\mathrm{max}$ 决定。Arduino ADC 的输入范围为 0～5 V，将其量化为 0～1023 整数。量化的方式则是与分辨率 $\rho$ 进行对比，取整

$$
\rho = \frac{V_\mathrm{max}}{2^\mu} 
\quad \rightarrow \quad
V_\mathrm{dig} = \left\lfloor \frac{V_\mathrm{in}}{\rho} \right\rfloor
$$

正负供电的 ADC 可以采集“双边”信号，相应会保留一位符号位，因此计算分辨率时应当修正为

$$
\rho = \frac{V_\mathrm{max}}{2^{\mu -1}}
$$

量化之后的 $V_\mathrm{dig}$ 俗称“码值”，为了便于后续分析以及避免 ADC、DAC 位数不同而导致同一码值代表不同电压值的现象，通常可以将其乘以量化分辨率转化为对应的电压值，及

$$
\breve{V}_\mathrm{in} = \rho V_\mathrm{dig} = \rho \left\lfloor \frac{V_\mathrm{in}}{\rho} \right\rfloor
$$

由此可知 ADC 会引入量化误差

$$
\tilde{V} = \breve{V}_\mathrm{in} - V_\mathrm{in}
$$

类似于 ADC，DAC 输出时也需要根据位数将需要输出的电压值转化为码值，然后 DAC 根据码值与参考电压比对后输出模拟电压值。这里不作多讨论。

在程序中分别定义了 ADC 和 DAC 量化系数以显式地将码值转化为测量电压值。

```arduino
double PWMScale = pow(2, 8) / Vmax;         // Desired voltage to DAC(PWM) code
double ADCScale = Vmax / pow(2, 10);        // ADC code to measured voltage
```


## 实验思路

本想通过 Arduino 的 DAC 输出正弦波，然后用 ADC 采集。然而 Arduino 实际上没有 DAC，而是通过 PWM 实现类似的功能。因此 ADC 采集到的都是正负饱和的跳动（还不说高频 PWM 在给定 ADC 采样率下的混叠）。为了通过 PWM 实现正弦，需要对输出进行滤波。为此，我在小伙伴那里薅了几个电容（感谢坨师兄为本工作的贡献），构造了一个单级低通滤波器，实验装置如下

<div align=center>
    <img src=./ADC.svg width=60% />
</div>

当采用 $R=10\, \mathrm{k\Omega},\, C = 4.7\,\mathrm{\mu F}$ 参数时，经过 PWM 滤波之后的正弦可以通过 Arduino IDE 的 Serial Plotter 查看：

<div align=center>
    <img src=./SerialPlotter.jpg width=90% />
</div>

> 说明：图中的正弦信号不能理解为“方波直接滤波得到正弦”。 PWM 方波的基频很高，直接滤波应当得到数百赫兹的信号而看不到正弦（这里采样率为 10 Hz）。这里是将正弦经过 PWM 调制之后，输出方波的脉宽不同，短时间内对应的“直流”（低频）信号不同，把高频方波滤出保留低频即是想要的正弦信号。

把电阻换成 $C = 10\,\mathrm{nF}$ 后滤波效果较差，除了可以看到正弦外，还存在高频抖动，为此初步尝试了噪声整形：其基本思路为 ADC 采集后的信号与期望的输出进行对比，将误差通过控制器反馈后通过 DAC 输出（这个我会在之后 DAC 测试中详细进行介绍）。初次实验的效果如下，对于正弦输出，整形后的噪声在低频得到抑制，但高频比较突出（可能是参数没有好好设计，也可能是 PWM 调制的“非线性”影响）。


<div align=center>
    <img src=./PSD.png width=70% />
</div>

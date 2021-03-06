# 05 LED 呼吸灯

只有亮、灭不够过瘾，尝试让 LED “呼吸”吧～

在本示例中，我们将了解：

- 模拟信号输出：[`analogWrite()`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/)。


## 基本思路

LED 的亮度与其功率成正比，而 LED 通常是发光二极管，具有恒定的压降，因此改变其通过的电流即可调节 LED 的亮度。然而话说话又说回来，改变通过 LED 的电流是通过改变其接入的电压来实现的，因此我们只要 Arduino 循环输出不同的电压即可实现“呼吸”过程。


## 算法实现

### 硬件布局

Ardiuno 通常的端口只能输出高、低电平（数字信号），为了输出模拟电压，可以采用脉宽调制（PWM，Pulse Width Modulation）技术。Arduino 中支持 PWM 的端口均有 `～` 标注，例如本例使用的是 `11` 号端口。只用了一个 LED, 图就不再画了。


### 变量及端口声明

这里我定义了三个变量，分别是：

- `pinPWM` --- 使用的 PWM 端口；
- `valPWM` --- PWM 端口当前输出对应的值；
- `delPWM` --- 每个循环 `valPWM` 的增量。

端口的设置只需要在 `setup()` 里将 `pinPWM` 设置为 `OUTPUT` 即可。


### 呼吸设置

为了输出模拟电压，可以使用 `analogWrite()` 函数，该函数需要两个参数，分别是输出端口和输出值。应当注意，这里的输出值并不是输出电压，8 位 DAC 编码值（DAC 的位数是硬件决定的，Arduino 只有 8 位），即为 0～255 范围内的整数。与输出电压之间的关系为

$$
V_{\rm out} = \underbrace{\mathrm{Code}}_{\text{编码值} } \times \mathrm{LSB} , \quad \mathrm{LSB} = \frac{V_{\rm ref}}{2^M}
$$

当量化不考虑符号时，`M=N` 为 ADC/DAC 位数；考虑符号位时 `M=N-1` 扣除符号位。$V_{\rm ref}$ 为参考电压，对 Arduino 为 5 V。

这里我将编码值 `valPWM` 从 0 开始，依次变动 5，当增加到 255 或者减小到 0 时增量改变符号（由增变减或由减变增），相信代码不难看懂。


## 扩展：脉宽调制基本原理

`analogWrite()` 的本质是脉宽调制，也就是让信号输出高电平或低电平，但是占空比不一样。假设高电平占据脉冲周期的比例为 $r$ ，那么输出的直流电压就是高电平的 $r$ 倍，即 $rV_{\rm HIGH}$。

解释这个也很简单：脉款调制的信号是周期信号，因此可以使用傅立叶级数进行分析，而 PWM 通常配合低通滤波器使用，假设将正弦信号都滤除了，所以直流信号就是脉款调制信号在一个周期内的平均值，为

$$
V_{\rm out} = \frac{1}{T} \int_0^T V(t) \,\mathrm{d} t = \frac{1}{T} V_{\rm HIGH} T_{\rm HIGH} = rV_{\rm HIGH}
$$

喏，高频的我就不写了哈。

应当注意的是，滤波器不可能将单频信号信号完全滤除，所以实际上输出电压会在 $rV_{\rm HIGH}$ 附近波动，波动的大小就与滤波器阶数相关了。另一方面，由于滤波器的存在，输出电压需要经过一定时间才能达到稳定，因此使用 PWM 时候不能太快地切换，否则可能没有收敛到稳态的电压。

# 02 点亮内置 LED

让 Arduino 内置的 LED 灯按照我们的想法闪烁吧～

在本示例中，我们将了解：

- 内置变量：
    [`[constants]`](https://www.arduino.cc/reference/en/language/variables/constants/constants/)；
- 引脚设置：
    [`pinMode()`](https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/)；
- 数字信号输出：
    [`digitalWrite()`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/)。


## 基本思路

将内置的 LED 引脚设置为输出，输出高低电平控制 LED 亮灭。


## 算法实现

### 引脚设置

为了将驱动电压输出给内置的 LED，首先需要将与 LED 连接的引脚设置为输出端口。这种设置只需要在开机时执行一次，因此将放在 `setup()` 函数体内。

使用 `pinMode()` 即可对引脚进行设置，该函数接收两个参数：第一个参数为引脚号（整数），第二个参数是内置变量 `INPUT` 或 `OUTPUT`，用于声明输入端或输出端。

内置的 LED 引脚由内置变量 `LED_BUILTIN` 记录，可以直接使用。如果查阅技术手册的话，可以发现这个引脚号为 `13`。因此，`setup()` 函数内的 `pinMode(LED_BUILTIN, OUTPUT)` 也可以写成 `pinMode(13, OUTPUT)`。


### 循环开关

进一步查阅原理图的话，可以知道 `LED_BUILTIN` 引脚与内置 LED 的正极连接。这意味着输出高电平将点亮 LED，输出低电平将熄灭 LED。为了让 LED 闪烁，只需要让开关电平的控制程序放置在 `loop()` 函数体内即可。

前面设置了 `LED_BUILTIN` 为输出端口，使用 `digitalWrite()` 即可输出高低电平。该函数接收两个参数，第一个参数为输出端口的引脚号，第二个参数为内置变量 `HIGH` 或 `LOW`，分别表示高低电平。

本例程序里分别输出高、低电平并持续 500 ms，程序上传到 Arduino 后，其内置 LED 将以 1 s 为周期闪烁。

> 是不是很简单呢？
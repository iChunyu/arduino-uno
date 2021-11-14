# 01 Hello World

尝试使用 Arduino 与世界打招呼吧～

在本示例中，我们将了解：

- Ardunio 编程的基本结构：
    [`setup()`](https://www.arduino.cc/reference/en/language/structure/sketch/setup/)、
    [`loop()`](https://www.arduino.cc/reference/en/language/structure/sketch/loop/)；

- 串口设置与输出：
    [`Serial.begin()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/)、
    [`Serial.print()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/print/)、
    [`Serial.println()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/println/)；
- 控制程序运行速度：
    [`delay()`](https://www.arduino.cc/reference/en/language/functions/time/delay/)。


## 基本思路

首先对串口进行设置，然后循环输出字符串即可。


## 算法实现

### 初始化串口

硬件、程序的初始化设置可以放在 `setup()` 函数中，只会在 Arduino 开机或者重置时运行一次，其基本结构如下：

```arduino
void setup() {
    // codes
}
```

其中，双斜线 `//` 为注释符，其之后的内容不会被程序执行。

在本例中，我们需要使用串口，直接使用内置函数 `Serial.begin()` 对波特率进行设置即可。常用的波特率有 9600、19200 等，使用时应当注意硬件支持并且确保解码时候（串口调试助手等工具）的波特率设置应当保持一致。


### 循环输出

如果一串代码在 Arduino 开机并初始化完成之后需要重复执行，则应当放置在 `loop()` 函数内，基本结构为：

```arduino
void loop() {
    // codes
}
```

于是我们将把串口的输出放在这里重复执行。为了使用串口的输出，可以采用 `Serial.print()` 或者 `Serial.println()`，两者的用法完全一致，区别仅在于后者会自动插入换行符 `\r\n` 进行换行。

在本例中，使用 `Serial.print()` 输出 "Greetings from Arduino UNO: "，不会自动进行换行，因此下一个输出会接在后面（也正因此你会发现我在字符串末尾多给了个空格）。紧接着的输出使用 `Serial.println()`，在给出 "Hello World!" 之后会自动换行。因此程序运行之后你会看到：

```text
Greetings from Arduino UNO: Hello World!
Greetings from Arduino UNO: Hello World!
Greetings from Arduino UNO: Hello World!
(重复输出，直到关机)
```

默认情况下 Arduino 会以最快的速度执行 `loop()` 内的代码，但通常我们不需要这么频繁的计算。因此可以使用 `delay()` 来使程序暂停一段时间。应当注意，`delay()` 接受的参数是以毫秒 (ms) 为单位的。

> 唔，这个程序简单吧？

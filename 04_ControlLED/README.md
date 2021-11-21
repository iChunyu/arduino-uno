# 04 串口控制 LED

LED 的控制权还是应当在自己手里，那就来试试手动点亮吧～

在本示例中，我们将了解：

- 数组的使用：
    [`[array]`](https://www.arduino.cc/reference/en/language/variables/data-types/array/)、
    [`sizeof`](https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/)；
- 条件语句扩展：[`else`](https://www.arduino.cc/reference/en/language/structure/control-structure/else/)；
- 串口读取：[`Serial.read()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/read/)。


## 基本思路

从串口读取指令，分别对应三个 LED 的开关。输入指令后 LED 的状态改变，即原本熄灭的被点亮，原本点亮的被熄灭。


## 算法实现

### 硬件布局

这次可以偷懒，继承 [点亮外部 LED](../03_ExternalLED/README.md) 的布局，如下图所示。

<div align=center>
    <img src=./ControlLED.svg width=50% />
</div>


### 变量声明

这次我们使用数组来储存输出给 LED 的引脚编号，因此不需要像上图那样严格使用三个连续的端口。与定义一般的变量类似，首先是变量类型声明，然后是变量名。对于数组，需要在变量名后接中括号以提醒该变量为数组类型。数组使用花括号进行幅值，当赋予初值时，声明数组时的中括号可以置空，否则需要显示地给定数组大小，例如

```arduino
int pinLED[] = {7, 8, 9};
bool statusLED[3] = {LOW, LOW, LOW};
```

Arduino 语言实际上是封装好的 C++，因此遵循 C++ 的规则：数组索引从 `0` 开始。例如上面初始化 `pinLED` 后，有 `pinLED[0] = 7`，`pinLED[2] = 9` 而 `pinLED[3]` 不存在。

为了知道有多少 LED 有效，实际上需要知道 `pinLED` 数组的长度。遗憾的是，Arduino 并没有内置形如 `length()` 的函数。为此，我们可以通过 `sizeof()` 获取变量占据的内存大小，考虑到数组内的元素具有相同的数据类型（每个元素占据相同的内存），只要除以单个元素的大小就可以知道数组的长度。

本例定义的各变量含义如下：

- `pinLED` --- 数组，用于驱动 LED 的端口号；
- `statusLED` --- 数组，各 LED 的状态，`HIGH` 为点亮，`LOW` 为熄灭；
- `numLED` --- 整数，实验使用的 LED 数量；
- `cmd` --- 字符，用于储存串口读进来的指令。


### 端口设置

由于使用了数组储存端口号，在 `setup()` 内进行初始化设置的时候只要遍历数组各个元素，并将对应端口设置为输出、输出的值设置为初始化时 `statusLED` 的默认值即可。

为了使用串口，还需要使用 `Serial.begin()` 开启。


### 控制 LED

首先使用 `Serial.read()` 读取串口发送过来的指令，并将其储存在变量 `cmd` 中。由于我使用的 LED 分别为黄、绿、红三种颜色，因此我决定设置 `y`、 `g`、 `r` 为三个 LED 的开关指令。使用 `if` 进行判断，将相应的状态取反即可。

> `Serial.read()` 和 `else` 太顾名思义，我就不展开废话了。

然后遍历引脚数组，将各个端口的输出根据当前状态进行调整即可。

> 逻辑非常简单，代码应该比文字更有说服力～
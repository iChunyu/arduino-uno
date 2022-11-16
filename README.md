# Arduino UNO

<!-- 先整个仓库记录一下折腾 Arduino 的过程，回头万一有时间整理一个入门教程也说不定呢。

原理图可以在 [官方网站](https://content.arduino.cc/assets/UNO-TH_Rev3e_sch.pdf) 下载。 -->

本仓库简要记录 Arduino 的学习与折腾记录。

下面的目录列出了已经调试过的测试用例以及用例所涉及的核心内容。

1. [Hello World](./01_HelloWorld/README.md)

    [`setup()`](https://www.arduino.cc/reference/en/language/structure/sketch/setup/)、
    [`loop()`](https://www.arduino.cc/reference/en/language/structure/sketch/loop/)、
    [`Serial.begin()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/)、
    [`Serial.print()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/print/)、
    [`Serial.println()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/println/)、
    [`delay()`](https://www.arduino.cc/reference/en/language/functions/time/delay/)。

2. [点亮内置 LED](./02_BuiltinLED/README.md)

    [`[constants]`](https://www.arduino.cc/reference/en/language/variables/constants/constants/)、
    [`pinMode()`](https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/)、
    [`digitalWrite()`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/)。

3. [点亮外部 LED](./03_ExternalLED/README.md)

    [`for`](https://www.arduino.cc/reference/en/language/structure/control-structure/for/)、
    [`if`](https://www.arduino.cc/reference/en/language/structure/control-structure/if/)。

4. [串口控制 LED](./04_ControlLED/README.md)

    [`[array]`](https://www.arduino.cc/reference/en/language/variables/data-types/array/)、
    [`sizeof`](https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/)、
    [`else`](https://www.arduino.cc/reference/en/language/structure/control-structure/else/)、
    [`Serial.read()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/read/)。

5. [LED 呼吸灯](./05_BreathLED/README.md)

    [`analogWrite()`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/)。

9. [超声波距离传感器](./09_DistancetSensor/REAFME.md)

    调用外部库 [`NewPing`](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home)

11. [ADC 模数转化](./11_ADC/REAFME.md)

    [`analogRead()`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)。

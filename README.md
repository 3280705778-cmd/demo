# keil_proj_demo

这是一个给机器人队新人准备的 Git 操作以及 STM32 入门示例工程。
完成本教程需要你用Vscode打开GitHub上下载解压的 `keil_proj_demo` 文件夹，按顺序完成 8.6、8.7、8.8 三天的作业。
<img src="./doc/图片/download_release.png" alt="download_release" title="download_release" width="600">

其中 8.7、8.8 的作业是控制组分流后的内容，<mark style="background-color: red;"> 8.6 的 Git 与 Markdown 学习和作业练习所有人都要完成。<mark style="background-color: red;">

> 8.6的Git学习和作业练习，请直接跳转到文档末尾的**作业与参考资料**部分。

工程会循环演示下面这件事：

1. LED1 ~ LED4 依次闪烁 3 次；
2. 蜂鸣器响一声；
3. LED 亮灭速度逐渐变快；
4. 到达较快速度后恢复初始速度，然后重新开始。

工程里刻意安排了一些可以改的小地方，用来练习 Git 的分支、提交、回退等操作。

## HAL 库单片机开发流程

用 HAL 库开发单片机项目，一般不是拿到工程就直接写代码，而是先有需求、再定硬件、再生成初始化工程，最后写业务代码：

1. **明确工程需求**：确定板子要实现什么功能、需要哪些外设。本工程的需求就是“4 颗 LED 依次闪烁、蜂鸣器响一声、亮灭速度变化”，所以只需要 GPIO 和延时。
2. **设计硬件电路**：根据需求选择芯片、画原理图和 PCB。每个引脚接了什么外设要看板子原理图（[F4](./F4主控板原理图.pdf) / [H7 本工程使用](./H7原理图6串口_2026-01-18.pdf)），例如本工程 H7 板的 PB3~PB6 接 LED、PB0 接蜂鸣器，对应关系见下一节”硬件资源”。
3. **CubeMX 配置并生成工程**：打开 CubeMX（本工程已附带 `keil_proj_demo.ioc`），对照原理图选芯片、配时钟、使能外设、分配引脚，然后生成 Keil 工程。生成结果就是 `Core/`、`Drivers/` 这些目录和初始化代码。
4. **Keil 开发与验证**：用 Keil 打开工程，在 `main()` 的 `USER CODE` 区域写业务代码，编译、下载、复位观察现象。

### 本教程已配置好的部分

上面流程里”工程需求、硬件电路、CubeMX 配置”已经由本教程完成：`keil_proj_demo.ioc` 是 CubeMX 工程，`Core/Src/gpio.c` 已初始化 PB0、PB3~PB6，`SystemClock_Config()` 已配置好 550 MHz 系统时钟，HAL 库和 Keil 工程也已就绪。

### 本教程的教学重点

教程不讲怎么画板、怎么配 CubeMX，重点放在后面两步：

- **C 语言语法**：变量与作用域、函数声明/定义、形参实参、`for` / `while` / `if` / `switch`、`#define` 宏、`.h` / `.c` 分工；
- **工程应用**：在真实工程里改代码、补函数、加模块，把学到的语法用到 LED、蜂鸣器这些实际外设上；
- 同时配合 Git 提交、分支和 Markdown 学习记录，完成“能看懂工程、能改工程、能写代码”的入门闭环。

## 硬件资源

STM32H723ZETx 的 PB0、PB3~PB6 引脚连接了 4 颗 LED 和 1 个蜂鸣器，具体如下：

| 外设   | 引脚 | 说明       |
| ------ | ---- | ---------- |
| LED1   | PB3  | 高电平点亮 |
| LED2   | PB4  | 高电平点亮 |
| LED3   | PB5  | 高电平点亮 |
| LED4   | PB6  | 高电平点亮 |
| 蜂鸣器 | PB0  | 高电平响   |

引脚初始化代码在 `Core/Src/gpio.c` 的 `MX_GPIO_Init()` 中，由 STM32CubeMX 生成。

## 工程目录结构

```text
keil_proj_demo/
├── Core/
│   ├── Inc/                 # 主程序、GPIO、中断等头文件
│   └── Src/                 # main.c、gpio.c、中断服务程序等源文件
├── Drivers/
│   ├── CMSIS/               # ARM 内核相关文件
│   └── STM32H7xx_HAL_Driver/ # STM32 HAL 库
├── hardware/
│   ├── inc/                 # 自己写的 LED、蜂鸣器头文件
│   └── src/                 # 自己写的 LED、蜂鸣器实现文件
├── user/
│   ├── inc/
│   │   └── user_beep.h      # 8.7 作业：蜂鸣器长短短三声声明
│   └── src/
│       └── user_beep.c      # 8.7 作业：蜂鸣器长短短三声实现
├── doc/
│   ├── git总览.md           # Git 与 GitHub 使用说明
│   ├── vscode中git图形化操作.md  # VS Code 图形化 Git 操作
│   ├── 作业.md              # 三天的作业安排
│   └── 图片/                # 文档配图
├── MDK-ARM/                 # Keil 工程文件和编译输出
│   └── keil_proj_demo.uvprojx
├── keil_proj_demo.ioc       # CubeMX 工程配置，改引脚时用 CubeMX 打开
├── .gitignore               # Git 忽略编译输出等文件
└── README.md
```

```text
Core/Src/main.c      程序入口，主循环在这里
Core/Src/gpio.c      GPIO 初始化，配置 PB0、PB3~PB6 为输出
hardware/inc/led.h   LED 函数声明和引脚宏
hardware/src/led.c   LED 点亮/熄灭实现，里面有 switch 例子
hardware/inc/buzzer.h 蜂鸣器函数声明和引脚宏
hardware/src/buzzer.c 蜂鸣器打开/关闭实现
user/inc/user_beep.h  8.7 作业：蜂鸣器长短短三声（默认未加入工程）
user/src/user_beep.c  8.7 作业：蜂鸣器长短短三声实现
doc/git总览.md       Git 与 GitHub 使用说明
doc/vscode中git图形化操作.md  VS Code 图形化 Git 操作
doc/作业.md          三天的作业安排
doc/图片/            文档配图
MDK-ARM/keil_proj_demo.uvprojx  Keil 工程文件，双击或在 Keil 中打开
```

## 打开、编译和下载

1. 安装 Keil MDK 5，并安装 STM32H7 器件支持包；
2. 在 _文件资源管理器中_ 双击打开 `MDK-ARM/keil_proj_demo.uvprojx`；
3. 按 `F7` 编译工程；
4. 连接 ST-Link 或调试器，按 `F8` 下载；
5. 复位开发板，观察 LED 和蜂鸣器。

## 编译的原理

### 先形象化地理解

可以把 C 源码想象成给芯片写的“菜谱”或“施工图”。芯片本身不认 C 代码，只认识由 0 和 1 组成的机器指令。编译器就像翻译官：把 `main.c`、`led.c` 里人能读懂的代码翻译成芯片能执行的机器码；链接器再把分散翻译好的零件拼成一个完整程序；最后通过调试器把程序“装进”芯片的 Flash。芯片复位后，CPU 从 Flash 里读出机器码并逐条执行。

Keil 里按 `F7` 后出现的 `.o`、`.axf`、`.hex` 等文件，就是这个翻译过程的中间产物和最终产物。

### 专业一点的描述

Keil MDK 的编译下载流程通常分这几步：

1. 预处理：处理 `#include`、`#define` 宏替换、条件编译；
2. 编译：对 C 源码进行词法、语法、语义分析，生成 ARM 汇编或目标文件 `.o`；
3. 汇编：启动文件 `startup_stm32h723xx.s` 等汇编代码也被汇编成目标文件；
4. 链接：把多个 `.o` 文件和库按地址分配链接在一起，生成可执行映像 `.axf` 和烧录文件 `.hex`；
5. 下载：通过 ST-Link 等调试器把 `.hex` 写入芯片 Flash。

所以按 `F7` 完成的是“预处理 -> 编译 -> 汇编 -> 链接”这条构建链；要让程序真正跑起来，还需要“下载 -> 复位运行”。

### 为什么改完 C 要重新编译下载

芯片真正运行的是 Flash 里的机器码，不是 `.c` 源码。`main.c` 里改了一个数字，源码变了，但 Flash 里还是旧的机器码，MCU 不会自动知道。

- 重新编译：把改动后的源码重新翻译成新的机器码，并重新链接出新的 `.hex`；
- 重新下载：把新的 `.hex` 覆盖写入 Flash；
- 复位：CPU 重新从 Flash 第一条指令开始执行新程序。

如果只编译不下载，编译产物只是硬盘上新固件；如果只下载不编译，下载的仍是旧固件。**源码改完 -> 保存 -> 编译 -> 下载 -> 复位**，这五步都要走完。

## 程序运行流程

程序上电后大致按以下顺序运行：

```text
复位
  -> startup_stm32h723xx.s（启动文件，初始化栈和中断向量表）
  -> SystemInit（配置时钟树基础部分）
  -> main
      -> HAL_Init（初始化 HAL 库和 SysTick）
      -> SystemClock_Config（配置系统时钟，本工程为 550 MHz）
      -> MX_GPIO_Init（配置 PB0、PB3~PB6 为推挽输出）
      -> while (1)（无限循环，执行 LED/蜂鸣器演示）
```

`main.c` 中有 `USER CODE BEGIN ... END` 注释。CubeMX 再次生成代码时只会保留这些区域里的用户代码，所以自己的代码应该写在用户区域内。

### main.c 里的 USER CODE 分区(简单看一眼即可,记住最后一句)

`main.c` 的 USER CODE 标记是 CubeMX 生成代码时留下的固定分区，数字和缩写都有固定含义。表格里的区块是这份工程里实际出现的：

| 标记                  | 位置                 | 一般写什么                    |
| --------------------- | -------------------- | ----------------------------- |
| `Header`              | 文件最顶部           | 文件说明、版权注释            |
| `Includes`            | 头文件包含区         | 自己需要的 `#include`         |
| `PTD`                 | 私有类型定义区       | `typedef`、结构体等类型定义   |
| `PD`                  | 私有宏定义区         | `#define` 常量                |
| `PM`                  | 私有宏区             | 带参数的宏等                  |
| `PV`                  | 私有变量区           | 文件级变量                    |
| `PFP`                 | 私有函数声明区       | 自定义函数原型                |
| `0`                   | `main()` 之前        | 通用小函数、`__weak` 占位实现 |
| `1`                   | `main()` 开头        | `main()` 里的局部变量定义     |
| `Init`                | 外设初始化之前       | 自定义初始化代码              |
| `SysInit`             | 系统时钟初始化之后   | 依赖时钟的初始化代码          |
| `2`                   | 死循环之前           | 上电后只执行一次的代码        |
| `WHILE`               | 死循环开头           | 进入主循环前想先做的事        |
| `3`                   | 死循环内部           | 主循环每轮执行的代码          |
| `4`                   | `main()` 之后        | 自定义函数定义                |
| `Error_Handler_Debug` | 错误处理函数里       | 调试用的错误输出              |
| `6`                   | `assert_failed()` 里 | 断言失败时的处理              |

找不到区块时在 VS Code 里按 `Ctrl+F` 搜 `USER CODE`，配合附近的注释就能定位。原则只有一条：**自己的代码写在 `USER CODE BEGIN` 和 `USER CODE END` 之间**，写在外面可能被 CubeMX 重新生成时覆盖。

## C 文件与头文件的作用

`.h` 文件放声明，`.c` 文件放实现。

例如 `led.h` 只告诉别人“有这个函数”，不写函数体：

```c
#ifndef LED_H
#define LED_H

void led_on(uint8_t led_num);
void led_off(uint8_t led_num);

#endif
```

`led.c` 通过 `#include "led.h"` 引入声明，然后写出真正的函数体：

```c
#include "led.h"

void led_on(uint8_t led_num)
{
    /* 实现代码 */
}
```

这样写的好处：

- 谁要调用 `led_on`，只需要包含 `led.h`，不需要关心内部实现；
- `led.c` 内部怎么改，只要函数名和参数不变，调用方不用改；
- 头文件保护 `#ifndef / #define / #endif` 可以防止同一个头文件被重复包含。

## 本工程覆盖的 C 语法

### 变量类型

`main.c` 里使用了：

```c
uint8_t  current_led = 1U;   /* 8 位无符号整数 */
uint16_t blink_times = 3U;   /* 16 位无符号整数 */
uint32_t delay_ms = 250U;    /* 32 位无符号整数 */
const uint8_t led_count = 4U; /* const 表示值不能被修改 */
```

常用类型对照：

| 类型       | 说明            | 常见范围                 |
| ---------- | --------------- | ------------------------ |
| `uint8_t`  | 8 位无符号整数  | 0 ~ 255                  |
| `uint16_t` | 16 位无符号整数 | 0 ~ 65535                |
| `uint32_t` | 32 位无符号整数 | 0 ~ 4294967295           |
| `int32_t`  | 32 位有符号整数 | -2147483648 ~ 2147483647 |
| `float`    | 单精度小数      | 约 6~7 位有效数字        |

数字后面的 `U` 表示无符号数，例如 `250U`。

### 变量的定义

“定义一个变量”就是向编译器申请一块内存，并给它起一个名字。定义时写三部分：类型、名字、初始值，其中初始值可以省略。

```c
uint8_t current_led = 1U;
```

拆开看：

- `uint8_t` 是**类型**，决定这块内存能装什么数据、占多少位；
- `current_led` 是**变量名**，之后用这个名字读写这块内存；
- `= 1U` 是**初始值**，表示变量一创建就放进 `1U`；这里的 `=` 是初始化，和后面 `current_led++` 这种修改值不一样。

变量名只能由**字母、数字和下划线**组成，不能以数字开头，也不能和 `if`、`int`、`while` 这些 C 关键字重名。给名字时最好能看出用途，例如 `current_led` 表示“当前操作的 LED”。

局部变量如果没有写初始值，它里面可能是旧内存留下的随机数，所以本工程里所有变量定义时都给了初值。

### 变量的作用范围

变量的作用范围也叫作用域，指程序里哪些位置能直接使用这个名字。在 `{}` 块里定义的变量，只在这个块和它嵌套的子块里有效，离开这个块就不能再访问。

本工程里用到的变量都是局部变量：

- `current_led`、`blink_times`、`delay_ms`、`led_count` 定义在 `main()` 里，只能在 `main()` 内使用；
- `i` 定义在 `blink_led()` 里，只能在 `blink_led()` 内使用；
- `led_num`、`times`、`delay_ms` 是 `blink_led()` 的参数，作用范围同样是这个函数内部。

还有一类全局变量，定义在所有函数外面，任何函数都能用。全局变量用起来方便，但会让函数之间互相“偷改”数据，程序变大后很难查，所以这个入门工程没有使用，先理解局部变量即可。

### 函数的类型、命名与参数

一个函数由返回类型、函数名、参数列表和函数体组成。`blink_led()` 是项目里现成的例子：

```c
void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms)
{
    /* 函数体 */
}
```

逐个看：

- **返回类型**写在最前面，也叫函数类型。`void` 表示“没有返回值”，函数执行完就回到调用处；`main()` 写的是 `int main(void)`，表示按 C 标准它应该返回 `int`。如果返回类型不是 `void`，函数体里一般要有 `return 值;`。`blink_led()` 里的 `return;` 就是提前结束这个 `void` 函数。
- **函数名**用能说明用途的英文，多个单词用下划线连起来。例如 `blink_led` 是“闪烁 LED”，`buzzer_init` 是“初始化蜂鸣器”，`led_on` 是“点亮 LED”。
- **参数**写在括号里，格式是 `类型 名字`。类型决定这个参数能表示多大范围、占几位：`led_num` 用 `uint8_t`，因为 LED 编号只有 1 ~ 4；`times` 用 `uint16_t`，能表示 0 ~ 65535 次；`delay_ms` 用 `uint32_t`，毫秒数的范围更大。`led_num` 表示“第几颗 LED”，`times` 表示“闪几次”，`delay_ms` 表示“延时多少毫秒”。调用时传进去的值会按参数类型存放，类型差太多时编译器会报警告，所以写参数时要选够用又不浪费的类型。没有参数时写 `(void)`。
- **函数体**是 `{}` 里的代码，也就是这个函数真正要做的事。

参数只在函数内部有效，可以把它理解成函数自己的局部变量。调用函数时传进去的值会复制一份给参数，函数内部修改参数不会影响外面原来的变量。

### 函数的调用

调用一个函数，就是写下“函数名(实参)”，例如：

```c
blink_led(current_led, blink_times, delay_ms);
```

调用时，`current_led`、`blink_times`、`delay_ms` 这些**实际值会按顺序传给函数定义里的参数**：`current_led` 传给 `led_num`，`blink_times` 传给 `times`，`delay_ms` 传给 `delay_ms`。传给函数的值叫实参，函数定义里接收值的叫形参。

程序执行到这一行时，会先跳进 `blink_led()` 把函数体跑完，再回到 `main()` 继续执行下一行。本工程里 `main()` 还调用了 `beep(BEEP_MS)`，`blink_led()` 内部又调用了 `led_on()`、`led_off()` 和 `HAL_Delay()`，一层一层调用下去。

调用前必须能看到函数声明，否则编译器不认识这个函数名。

### 函数的声明与定义

声明（也叫函数原型）只告诉编译器“存在这样一个函数，名字、参数、返回类型是什么”，末尾有分号，不写函数体：

```c
void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms);
```

定义除了同样写出返回类型、函数名和参数，还要写上函数体：

```c
void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms)
{
    /* 函数体 */
}
```

声明和定义必须一致：返回类型、函数名、参数类型都不能改，只有参数名字可以不同。前面“C 文件与头文件的作用”一节用 `led.h` / `led.c` 演示了跨文件分工，这里再补充语法上的细节：

简单说，声明告诉编译器“这个函数存在”，定义告诉编译器“这个函数具体做什么”。

- 声明可以写在 `.h` 头文件里给别的文件用，也可以写在 `.c` 文件顶部给本文件后面的代码用；
- `main.c` 顶部 `USER CODE PFP` 区域里的是函数声明，`USER CODE 4` 区域里的是函数定义；<small>可以使用`Ctrl+F`搜索代码段</small>
- 一个函数只能定义一次，否则链接时会报重复定义；但可以有多个内容一致的声明；
- 如果声明存在、定义却没写，或者定义所在的 `.c` 文件没有加进 Keil 工程，链接时会报 `Undefined symbol` 之类的错误。

### `#define` 宏定义

`main.c` 顶部用 `#define` 给常量起名字：

```c
#define LED_COUNT   4U
#define BLINK_TIMES 3U
#define DELAY_MS    250U
```

`#define` 是预处理指令，不是变量定义。编译流程的第一步是预处理，这一步会把代码里出现的 `LED_COUNT` 原样替换成 `4U`，替换完成之后，宏名字本身就不存在了。所以宏不占内存：它不会像变量那样分配一块存储，也没有类型、地址，Keil 里也看不到它的值，只能看到替换后的数字。

`const` 则不一样。`const uint8_t led_count = LED_COUNT;` 仍然是一个真正的变量，编译时通常会为它分配一块内存，只是编译器不允许代码再去修改它的值。两者区别可以这样记：

|              | `#define` 宏           | `const` 变量             |
| ------------ | ---------------------- | ------------------------ |
| 什么时候处理 | 编译前的预处理阶段     | 编译阶段                 |
| 是否占内存   | 不占，只是文本替换     | 通常占，是一块真正的存储 |
| 有没有类型   | 没有类型               | 有类型，例如 `uint8_t`   |
| 能不能修改   | 没有“值”，不存在修改   | 定义后不能修改           |
| 什么时候用   | 纯数字常量、编译期常量 | 希望保留类型且防止被改时 |

宏定义结尾不需要分号。

### `for` 循环

`blink_led()` 中用 `for` 控制闪烁次数：

```c
for (i = 0U; i < times; i++)
{
    led_on(led_num);
    HAL_Delay(delay_ms);
    led_off(led_num);
    HAL_Delay(delay_ms);
}
```

执行顺序是：初始化 `i = 0U` -> 判断 `i < times` -> 执行循环体 -> 执行 `i++` -> 再次判断。

### `while` 循环

`main()` 中最外层是嵌入式常见的死循环：

```c
while (1)
{
    /* 程序一直在这里循环 */
}
```

`main()` 里还有一个带条件的 `while`，用来依次控制 4 颗 LED：

```c
while (current_led <= led_count)
{
    blink_led(current_led, blink_times, delay_ms);
    current_led++;
}
```

### `if` 判断

`blink_led()` 用 `if` 检查 LED 编号是否合法：
`if` 内条件为真，则执行括号内的代码，否则跳过。

```c
if (led_num > LED_COUNT)
{
    return;
}
```

`main()` 里还用 `if / else` 控制延时变化。

### `switch` 语句

`hardware/src/led.c` 的 `led_on()` 和 `led_off()` 用 `switch` 根据 LED 编号选择引脚：

```c
switch (led_num)
{
    case 1:
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_PIN, GPIO_PIN_SET);
        break;
    case 2:
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
        break;
    default:
        break;
}
```

`case` 匹配成功后，如果没有 `break`，会继续执行下一个 `case` 的代码。`default` 处理没有匹配到的情况。

### `switch` 和多个 `if` 的区别

`switch` 和多个 `if / else if` 都能做分支，区别主要是“能判断什么”和“好不好读”：

| 对比点      | `switch`                   | 多个 `if / else if`                      |
| ----------- | -------------------------- | ---------------------------------------- |
| 判断方式    | 同一个变量和几个固定值比较 | 可以比较不同变量，也可以写范围和逻辑组合 |
| `case` 限制 | 必须是整数常量，不能写范围 | 条件可以是任意表达式                     |
| 可读性      | 固定分支多时更整齐         | 分支少或条件复杂时更直接                 |
| 常见坑      | 容易漏 `break`             | 条件顺序会影响结果                       |

本工程里两种都用到了：`led_on()` / `led_off()` 用 `switch` 按 LED 编号选引脚，因为编号就是 1/2/3/4 这几个固定值；`blink_led()` 用 `if (led_num > LED_COUNT)` 做范围判断，`main()` 用 `if / else` 判断 `delay_ms` 是否还大于 `100U`，这类范围判断 `switch` 写不了。

选型可以这样记：同一个值分很多固定分支，用 `switch`；条件五花八门、要比较范围或组合条件，用 `if`。性能差别通常不大，编译器会自己优化，新手阶段先按可读性选。

## 作业与参考资料

每天的作业单独放在 [doc/作业.md](doc/作业.md)，README 只负责讲工程和语法。

- Git 基础概念：[doc/git总览.md](doc/git总览.md)；
- VS Code 图形化操作 Git ：[doc/vscode中git图形化操作.md](doc/vscode中git图形化操作.md)。
- 8.6：Git 基础操作：init、add、commit、log、diff、分支、合并、回退；C语言环境搭建机械组意向选做
- 8.7：编译烧录与工具链配置；
- 8.8：C 语言工程操作：修改 `main.c` 的现象并提交，完成一个小功能；选做流水灯报警系统；

## 暂时不展开的内容

这个版本先不展开 `struct`、`enum`、指针、数组、宏参数等进阶内容，后续单独开一个训练任务。

源码文件已保存为 UTF-8（带 BOM）编码，Keil 可以直接识别中文注释。如果仍然乱码，请用 VS Code 查看和编辑源码，用 Keil 负责编译下载，或者查阅资料调整keil的文件编码格式。

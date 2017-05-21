此为STM32F103模板
实现串口FIFO 的DEBUG功能
其中COM0做为调试口
实现DEBUG功能控制功能

USART
RX ---- PA9
TX ---- PA10

网卡芯片ENC28J60 采用SPI通信
SPI 连接
SCK  ----- PA5
MISO ----- PA6
MOSI ----- PA7
CS   ----- PA4

INT ------ PA0 
WOL ------ 未用
RST ------ 末用

本工程已经可以ping通
实现测试telnet功能

为其它工程做准备
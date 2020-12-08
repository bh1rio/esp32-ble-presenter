## ESP32 BlueTooth Presenter

#### 开发相关引用
使用TTGO的controller开发板:[TTGO-T-Controller v2.2](https://github.com/LilyGO/TTGO-T-ControllerV2.2)，外加18650锂电池一节。

蓝牙键盘库使用[ESP32 BLE Keyboard library](https://github.com/T-vK/ESP32-BLE-Keyboard)

按键事件库使用[Button2](https://github.com/LennartHennigs/Button2)

#### 使用相关
ESP32为向上方向。一共6个按键，上下左右中心五键，和boot键。上下左右分别对应pc键盘的上下左右键，中心对应pc回车键，boot键会在屏幕显示当前电池电压。电池低于2.9v会显示Low Power
。每次上下左右键，会向pc发送剩余电池电量百分比。电池剩余电量百分比，按照4.25伏到2.75伏区间的百分比计算。

使用PPT演示时，上和左会向前翻一页，下和右以及回车会向后翻一页。使用射手播放器的时候，上下调节音量，左右调节前后进度，回车退出或进入全屏模式。

安卓支持未测试。理论上也支持。

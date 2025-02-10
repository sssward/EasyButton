# EasyButton

## 简介
EasyButton是一个简单高效的事件驱动型按键检测模块。
秉持着easy的初心，一切从简，减少暴露给用户可以自由调整的参数，使用更加方便。
支持的按键事件包括：单击、双击、长按。
需要配置的参数：
| 参数名称         | 取值范围       | 默认值 | 说明                                                                 |
|------------------|----------------|--------|----------------------------------------------------------------------|
| 按键默认电平     | 0 或 1         | 0      | 按键未按下时的电平状态。0 表示低电平，1 表示高电平。                  |
| 双击间隔阈值     | 0 ~ 65535 ms     | 200    | 两次单击之间的最大时间间隔，超过该时间间隔则不视为双击。              |
| 长按阈值         | 0 ~ 65535 ms    | 1000   | 按键按下后持续的时间，超过该时间则视为长按。                          |

## 使用方法
1.注册按键
```c
Button button1;
```
2.编写获取按键值的函数
```c
uint8_t getButtonVal(void){}
```
3.初始化按键对象
```c
buttonInit(&button1,0,200,1000,getButtonVal);
```

4.根据需求编写按键响应函数
```c
void singleClickHandler(void){}
void doubleClickHandler(void){}
void longPressHandler(void){}
```
5.链接按键响应函数到指定事件
```c
buttonLink(&button1,SINGLE_CLICK,singleClickHandler);
buttonLink(&button1,DOUBLE_CLICK,doubleClickHandler);
buttonLink(&button1,LONG_PRESS,longPressHandler);
```

6.定时1ms周期执行按键扫描函数
```c
buttonScan(&button1);
```

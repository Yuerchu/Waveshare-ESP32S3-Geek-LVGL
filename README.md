# Waveshare-ESP32S3-Geek-LVGL

> 基于 Arduino 并测试通过，~~但 ESP-IDF 版本的我还在试，可正确编译和烧录，但使用会偏色+花屏~~ ESP-IDF 版本的咱不公开

## 故事背景

前几天我闲来没事想要搞一块 ESP32-S3 的开发板，就开始疯狂地刷某宝，然后我注意到这个，非常符合我的想法：

![6c231898871ff72c1771a16aedea6c7](https://github.com/user-attachments/assets/c8d0dda6-3b11-4156-b054-3cc79881669a)

但我注意到这个产品的详情页没有说支持LVGL（因为一般支持这玩意的都会当作卖点来写），所以我感到很好奇：

![079f872012477c537cf871665314596](https://github.com/user-attachments/assets/2cce7664-94f9-4648-968e-a5bd89bb1a3b)

的我又去问了问商家，商家机器人告诉我支持，但人工又说不支持：

![df4672d821236a40d03884f626fbbc0](https://github.com/user-attachments/assets/8a7d9314-062b-40b2-8044-349598b54bd0)

不信邪的我就买了一个来试试：
![766ecef4210c61a5c9c68c13e7e63b2](https://github.com/user-attachments/assets/900a18fb-3f4e-49c8-905f-47ba210dd60f)

## 效果图

时间紧迫所以我只写了个Hello World：
![3d8085541ca707f2f9dcf36ec39c248](https://github.com/user-attachments/assets/64d5fbf4-c51b-459b-8c90-67b7000b5c0e)

然后下面是在一点点地对齐偏移：
![7c9d84de8f6cfd40c5108573fe177f1](https://github.com/user-attachments/assets/77bfd0e4-f45c-4818-976f-b0ce2c6e3f58)
![4d6c88100ba3e937a0ce7c025d05218](https://github.com/user-attachments/assets/6af57428-c7b1-407d-869e-c5930ffa6195)
![c57278b70f89263304562fdb7f96a32](https://github.com/user-attachments/assets/196eca9a-5c16-4824-a4df-1329f2c42498)

ESP-IDF 版本的 还在测试 已知Bug会频繁重启
![141a9ff8ab6fc1d2fb402ae400bb3a6](https://github.com/user-attachments/assets/32666f4f-721e-41ef-a1cc-ab25e11ac76e)

## 另外提一嘴
- 这块板子虽然有 PSRAM，但并不支持 Octal 八线模式，否则会因为这个无限重启。改到 Quad 四线模式就可以了。

## 许可证
MIT

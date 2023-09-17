## 二维码生成

可以将任意给定字符串、网址等转换为对应二维码 (QR码)表示。

要求：
- 能够完成字符串(编码方式任意) 到二维码的映射生成 (40)
- 能够支持多版本版本二维码生成 (10)
- 能够支持多种纠错等级 (有遮挡时也可以识别出) (10)
- 能够支持中文字符串 (10)
- 能够生成彩色二维码(10)
- 能够生成带图片背景的二维码 (10)
- 报告和代码完整性 (10)

检查内容:
1. 按照要求检查功能
2. 提交报告和代码清晰完整
3. 代码规范程度太差会酌情扣分

---

### 彩色二维码生成
``.\src\QrToPng.cpp``中更改向量``blackPixel``的RGB值即可。

```c++
// This vector restores RGB of the purple of THU
const uint8_t blackPixel[3] = {0x74, 0x34, 0x81};
```
值得注意的是，生成二维码图像的通道数为3，即RGB图像。

<img src=".\\cmake-build-debug\\src\\NewText.png" alt="NewText" style="zoom: 25%;" />

### 带图片背景的二维码
``.\cmake-build-debug\src\``中``Back.png``为待融合的图像背景（4通道，RGBA），
需与二维码的尺寸及通道数一致，因而本项目选择将二维码图像的通道数升为4，命名为``NewText.png``。

将二维码图像与背景图像以``alpha=0.4``融合比率进行融合，新图像为``Merge.png``。

<img src=".\\cmake-build-debug\\src\\Merge.png" alt="Merge" style="zoom:25%;" />
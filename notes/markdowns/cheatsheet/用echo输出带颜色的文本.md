# 用echo输出带颜色的文本

---

案例代码：

```bash
#! /bin/bash

# 用法: echo -e "\033[字背景颜色；文字颜色m字符串\033[0m"
# 字颜色：
# 30 黑色
# 31 红色
# 32 绿色
# 33 黄色
# 34 蓝色
# 35 紫色
# 36 天蓝色
# 37 白色

# 字背景颜色：
# 40 黑色
# 41 红色
# 42 绿色
# 43 黄色
# 44 蓝色
# 45 紫色
# 46 天蓝色
# 47 白色

# 控制格式：
# 0m 关闭所有属性
# 1m 文字高亮
# 4m 下划线
# 5m 闪烁

function color_test
{
	# 颜色
	echo "default text"
	echo -e "\033[47;30mBlack text\033[0m"
	echo -e "\033[31mRed text\033[0m"
	echo -e "\033[32mGreen text\033[0m"
	echo -e "\033[33mYellow text\033[0m"
	echo -e "\033[34mBlue text\033[0m"
	echo -e "\033[35mPurple text\033[0m"
	echo -e "\033[36mSky Blue text\033[0m"
	echo -e "\033[37mWhite text\033[0m"

	# 控制格式
	echo -e "\033[1m\033[37mHigh light White text\033[0m"
	echo -e "\033[1m\033[31mHigh light Red text\033[0m"
	echo -e "\033[1m\033[32mHigh light Green text\033[0m"
	echo -e "\033[4mUnderline text\033[0m"
	echo -e "\033[5m\033[31mBlink Red text\033[0m"
}
color_test $@
```
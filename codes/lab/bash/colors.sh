#! /bin/bash

#! /bin/bash

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

# set default
set_color_default()
{
    echo -e "\033[0m\c"
}

# set black text, white bg
set_black_text_white_bg()
{
    echo -e "\033[30;47m\c"
}

# set red text
set_red_text()
{
    echo -e "\033[31m\c"
}

# set green text
set_green_text()
{
    echo -e "\033[32m\c"
}

# set yellow text
set_yellow_text()
{
    echo -e "\033[33m\c"
}

# set blue text
set_blue_text()
{
    echo -e "\033[34m\c"
}

# set purple text
set_purple_text()
{
    echo -e "\033[35m\c"
}

# set sky blue text
set_sky_blue_text()
{
    echo -e "\033[36m\c"
}

# set white text
set_white_text()
{
    echo -e "\033[37m\c"
}

# set white text, high light
set_white_text_high_light()
{
    echo -e "\033[37;1m\c"
}

# set white text, underline
set_white_text_under_line()
{
    echo -e "\033[37;4m\c"
}

# set red text, blink
set_red_text_blink()
{
    echo -e "\033[31;5m\c"
}

main()
{
    set_black_text_white_bg
	echo -e "Black text, White bg\c"
    set_color_default
    echo

    set_red_text
	echo "Red text"

    set_green_text
	echo "Green text"

    set_yellow_text
	echo "Yellow text"

    set_blue_text
	echo "Blue text"

    set_purple_text
	echo -e "Purple text"

    set_sky_blue_text
	echo "Sky Blue text"

    set_white_text
	echo "White text"

    set_white_text_high_light
	echo "White text High light"

    set_white_text_under_line
	echo "White text Underline"

    set_red_text_blink
	echo "Red text Blink"

    set_color_default
	echo "default text"
}

main
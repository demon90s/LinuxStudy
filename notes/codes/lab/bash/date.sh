# /bin/bash

# date 命令可以显示或设置系统时间。
# 显示的格式由一个加号加标记组成，这些标记可以有：

# %c - 直接显示日期与时间（年月日 星期 时分秒）
# %D - 直接显示日期（mm/dd/yy）
# %x - 直接显示日期（文字描述）
# %T - 直接显示时间（24小时制）

# %Y - 完整年份
# %m - 月份
# %d - 日
# %H - 时
# %M - 分
# %S - 秒

# %s - 时间戳

# 相关选项：
# -d 字符串 根据字符串来显示时间，见案例
# -s 字符串 根据字符串来设定时间，见案例

Test1()
{
    # 显示当前时间

    # 默认格式
    echo -e "data: \c" && date

    # 测试各种格式
    echo -e "data +%c: \c" && date +'%c'

    echo -e "data +%D: \c" && date +'%D'

    echo -e "data +%x: \c" && date +'%x'

    echo -e "data +%T: \c" && date +'%T'

    echo -e "data +%Y-%m-%d: \c" && date +'%Y-%m-%d'

    echo -e "data +%H:%M:%S: \c" && date +'%H:%M:%S'

    echo -e "data +%s: \c" && date +'%s'
}

Test2()
{
    # 显示某一天的时间

    echo -e "+1 day: \c" && date -d "+1 day" +"%c"
    echo -e "-1 day: \c" && date -d "-1 day" +"%c"
    echo -e "+1 month: \c" && date -d "+1 month" +"%c"
    echo -e "-1 month: \c" && date -d "-1 month" +"%c"
    echo -e "+1 year: \c" && date -d "+1 year" +"%c"
    echo -e "-1 year: \c" && date -d "-1 year" +"%c"

    echo -e "+1 day -1 month: \c" && date -d "+1 day -1 month" +"%c"

    echo -e "+30 second: \c" && date -d "+30 second" +"%c"
    echo -e "+30 minute: \c" && date -d "+30 minute" +"%c"
    echo -e "+10 hour: \c" && date -d "+10 hour" +"%c"

    # 时间戳 -> 时间描述
    echo -e "@1000000000: \c" && date -d "@1000000000"
}

Test3()
{
    # 设置时间，会修改系统时间！！！需要 root 权限
    # Ubuntu下面，使用此命令校准实际时间：sudo ntpdate ntp.ubuntu.com
    #echo -e "set to 2012-12-12 12:12:12 \c" && date -s "2012-12-12 12:12:12"

    #echo -e "set to +1 day: \c" && date -s "+1 day"

    echo -e "set to +1 day zero time: \c" && date -s "+1 day 0:0:0"
}

main()
{
    #Test1
    Test2

    #Test3
}

main
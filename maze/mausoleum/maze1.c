// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit VRM_SERVER;

void create()
{
        //迷宫房间所继承的物件的档案名称。
        set_inherit_room( ROOM );

        //唯一房间
        set_unique_room( ({
                "/maze/mausoleum/unique_room/goldman_room",
                "/maze/mausoleum/unique_room/goldman_room2",
                "/maze/mausoleum/unique_room/goldman_room3",
                "/maze/mausoleum/unique_room/goldman_room4",
        }) );

        //中心房间
        set_center_room("/maze/mausoleum/unique_room/king_room");

        set_lonely_create(1);

        set_maze_boxs(1);

        set_maze_traps(2);

        //迷宫的单边长
        set_maze_long(10);

        //入口方向(出口在对面)
        set_entry_dir("east");

        //入口与区域的连接方向
        set_link_entry_dir("east");

        //入口与区域的连接档案名
        set_link_entry_room(__DIR__"eastgate");

        //出口与区域的连接方向
        set_link_exit_dir("west");

        //出口与区域的连接档案名
        set_link_exit_room("/d/luoyang/wenmiao");


        //普通房间描述
        set_maze_room_short(HIY "秦陵内宫" NOR);

        set_maze_room_desc(@LONG
自己站在长长的白玉石阶之底，石阶直通向上方那六丈来高、十里
来宽的巨大平台。仰头望去，广阔的黑色顶穹缀满了千万颗宝石、明珠，
光彩夺目，璀璨似星河，浩瀚如夜空，将四周照得一片皎皎明亮。在那
瑰丽的顶穹下方，赫然竟是一座拔地而起、连天入穹的雄伟宫城。那巍
峨壮丽的城楼殿宇，钩心斗角的流檐飞瓦，绵延雄矗于白玉石台上，如
泰山压顶，竟比长安城楼还要气势磅礴、雄奇瑰丽！石阶两边的广场上，
密密麻麻竟全是列成方阵的兵俑。铜人、陶俑、石雕……交相陈杂，少
说也有几万之众，军姿雄壮，威风凛凛。广场上，一条条银带蜿蜒交错，
闪耀着炫目的光泽，就像是江河汇集，一齐朝东面一个白光闪闪的水池
流去。
LONG);

        //入口房间短描述
        set_entry_short(HIR "秦陵内宫入口" NOR);

        //入口房间描述
        set_entry_desc(@LONG
自己站在长长的白玉石阶之底，石阶直通向上方那六丈来高、十里
来宽的巨大平台。仰头望去，广阔的黑色顶穹缀满了千万颗宝石、明珠，
光彩夺目，璀璨似星河，浩瀚如夜空，将四周照得一片皎皎明亮。在那
瑰丽的顶穹下方，赫然竟是一座拔地而起、连天入穹的雄伟宫城。那巍
峨壮丽的城楼殿宇，钩心斗角的流檐飞瓦，绵延雄矗于白玉石台上，如
泰山压顶，竟比长安城楼还要气势磅礴、雄奇瑰丽！石阶两边的广场上，
密密麻麻竟全是列成方阵的兵俑。铜人、陶俑、石雕……交相陈杂，少
说也有几万之众，军姿雄壮，威风凛凛。广场上，一条条银带蜿蜒交错，
闪耀着炫目的光泽，就像是江河汇集，一齐朝东面一个白光闪闪的水池
流去。
LONG);

        //出口房间短描述
        set_exit_short(HIW "秦陵内宫出口" NOR);

        //出口房间描述
        set_exit_desc(@LONG
自己站在长长的白玉石阶之底，石阶直通向上方那六丈来高、十里
来宽的巨大平台。仰头望去，广阔的黑色顶穹缀满了千万颗宝石、明珠，
光彩夺目，璀璨似星河，浩瀚如夜空，将四周照得一片皎皎明亮。在那
瑰丽的顶穹下方，赫然竟是一座拔地而起、连天入穹的雄伟宫城。那巍
峨壮丽的城楼殿宇，钩心斗角的流檐飞瓦，绵延雄矗于白玉石台上，如
泰山压顶，竟比长安城楼还要气势磅礴、雄奇瑰丽！石阶两边的广场上，
密密麻麻竟全是列成方阵的兵俑。铜人、陶俑、石雕……交相陈杂，少
说也有几万之众，军姿雄壮，威风凛凛。广场上，一条条银带蜿蜒交错，
闪耀着炫目的光泽，就像是江河汇集，一齐朝东面一个白光闪闪的水池
流去。
LONG);
}

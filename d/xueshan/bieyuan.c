inherit ROOM;

void create()
{
        set("short", "雪山别院");
        set("long", @LONG
这里是雪山寺的分部，当年贡唐仓大喇嘛不远万里进京面圣，被
封为国师，就在此处宣扬佛法。
LONG );
        set("exits", ([
                "east" : "/d/beijing/road5",
        ]));
        set("objects" , ([
                __DIR__"npc/seng-bing1" : 4,
                __DIR__"npc/zhike" : 1,
                CLASS_D("xueshan") + "/guoshi" : 1 ,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if( query("id", me) == "sengbing"
           && dir == "east")
                return 0;

        return ::valid_leave(me, dir);
}
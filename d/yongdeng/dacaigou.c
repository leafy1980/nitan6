// Room: /huanghe/dacaigou.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
��񹵵��Ʋ���������������Ҫ���Ƚ�ƽ̹���ٵ�����ȫ�����֣�
ʱ�����Է򿳲�����������д�����
LONG );
        set("exits", ([
                "southwest" : __DIR__"gulang",
                "north"     : __DIR__"wuqiao",
        ]));
        set("objects", ([
                __DIR__"npc/qiaofu" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16100);
	set("coor/y", 4220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
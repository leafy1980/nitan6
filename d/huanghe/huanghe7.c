// Room: /huanghe/huanghe7.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "�ƺӰ���");
        set("long", @LONG
�����ǻƺӰ��ߡ��ƺ����ʵ�����Ӵ���������ɫ�ĺ�ˮ�ھ���
������ȥ��ʹ������������ˮʱ�Ŀ�����
LONG );
        set("exits", ([
                "northeast" : __DIR__"huanghe8",
                "southwest" : __DIR__"huanghe6",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", 500);
        set("coor/y", 1000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
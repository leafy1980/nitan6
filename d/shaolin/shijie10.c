// Room: /d/shaolin/shijie10.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
�����������ƺ�������һ�����������⵽�����ø�������ֻ��
�������°߲�����Ӱ��������Զ�����һ����������֦�����������
LONG );
        set("exits", ([
                "southdown" : __DIR__"shijie9",
                "northup" : __DIR__"shijie11",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
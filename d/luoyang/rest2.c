inherit ROOM;

void create()
{
        set("short", "Ů��Ϣ��");
        set("long", @LONG
�����ǹ�ϴ����Ŀ�����Ϣ�ĵط�����������������࣬�д���ķ�
�������࿿�Σ��Ա߷�����ë�����Լ�ȡ�ã��������ﻹ�ṩ��ˮ����
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"nvyuchi",
                "down" : __DIR__"yuchi",
        ]));

	set("coor/x", -6980);
	set("coor/y", 2150);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
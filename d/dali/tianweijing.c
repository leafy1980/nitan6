//Room: /d/dali/tianweijing.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","������");
        set("long",@LONG
�˴���˵������ʱ�����������ߴ����ϻ�֮�����ϻ�Ի����
��������Ҳ����Ƚ������˲�����Ҳ�������ʴ˵���������һ����ͨ
�ϱ��Ĵ�·����ȥʮ����ϲ�ݳǣ�����Լ��ʮ��ɴ�����ǡ�
LONG);
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"road4",
            "south"      : __DIR__"xizhou",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19130);
	set("coor/y", -6940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
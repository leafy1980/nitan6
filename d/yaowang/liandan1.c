inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������ҩ���ȵ�����������Χǽ�ڶ�����ʯ�����ɵģ���ש�̵أ�
�����������һ����ͭ���ɵĴ�¯��
LONG );
        set("no_fight", 1);
        set("exits", ([
                "south" : __DIR__"yuemen",
        ]));
        set("objects", ([
                __DIR__"npc/obj/danlu1" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
//gebitan5.c

inherit ROOM;

void create()
{
        set("short", "���̲");
        set("long", @LONG
��ǰ��һ���޼ʵĸ��̲��û��·�꣬Ҳû��һ�����ˣ����Ե�
�ܸߣ�Զɽ��ѩ����ӥ���裬������ãã���֮�ϣ����ƺ���·�ˡ�
LONG );
         set("outdoors", "mingjiao");
         set("exits",([
            "east" : __DIR__"gebitan5",
            "west" : __DIR__"shanjiao",        
            "north" : __DIR__"gebitan5",
            "south" : __DIR__"gebitan4",                                  
        ]));
        set("objects", ([
                __DIR__"obj/xiaohuangshi": random(3),
                "/clone/npc/walker"  : 1,
        ]));
        setup();
        replace_program(ROOM);
}
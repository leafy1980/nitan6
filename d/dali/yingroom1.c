// Code of ShenZhou
inherit ROOM;

void create()
{
        set("short", "��̶");
        set("long", @LONG
������һ��Ƭ����̶����ǰ��ȥ����ǰһ��ãã��������һ��һ
Բ����é�ݣ�����ԼԼ�еƹ�ӷ������������é�������޻�������
����û��һ������֪����ǽ(wall)�Ǳ���Щʲô��
LONG );
        set("item_desc",([
                "wall" : "һ�¿��������Ǻܸߵ���ǽ��\n",
                ]));
        set("no_clean_up", 0);
        set("no_magic", 1);
        set("outdoors", "dalic" );
        set("exits", ([
                "north" : "/d/dali/maze1",
                ]));
        set("cost", 4);
        set("coor/x", -38000);
        set("coor/y", -72000);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();

        if ( !arg || arg != "wall")
                return notify_fail( "ʲô��\n");

        message_vision("$N��������ǽ����ȥ��\n", me);
        if ( me->query_skill("dodge",1) <= 50) {
                message_vision("$Nͨ��һ��ˤ������̶������������\n", me);
                me->receive_wound("qi", 100);
        }
        if ( me->query_skill("dodge",1) > 50 ) {
                me->move("/d/dali/yingroom2");
                message("vision", me->name() + "������ǽ�����˹�����\n",environment(me), 
                        ({me}) );
        }
        return 1;
} 
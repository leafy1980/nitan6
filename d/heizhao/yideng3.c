//Cracked by Kafei
// yideng quest room 3

inherit ROOM;
int do_jump(string);

void create()
{
        set("short", "�ٲ���");
        set("long", @LONG
�������ٲ�ˮ�ף�ˮ������ֱ�£���˫��ʹ�����ԡ�ǧ��׹����
��������վ�ȣ�ǡ����������������������
LONG );
        set("objects", ([
                __DIR__"npc/gfish" : 1,
        ]));

        set("invalid_startroom", 1);
        set("coor/x", -38000);
        set("coor/y", -80010);
        set("coor/z", -20);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();

        if ( !arg || arg != "bank" )
                return notify_fail( "ʲô��\n");

        message_vision("$N������������ȥ��\n", me);
        me->move(__DIR__"yideng1");
        return 1;
}
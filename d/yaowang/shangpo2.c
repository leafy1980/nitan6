inherit ROOM;

void create()
{
        set("short", "��ɽС·");
        set("long", @LONG
����һ�����͵���ɽС·�����Զ��Ǵ��̵ľ�����������ϡ
�ɵĻ�����Сʯ�ӣ�һ��С��׼ˤ������
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "northup" : __DIR__"shangpo3",
  "southdown" : __DIR__"shangpo1",
]));

        set("outdoors", "yaowang");
        setup();
}

int valid_leave(object me, string dir)
{
        int sk;

        if(!userp(me) || (dir != "northup"))
                return ::valid_leave(me, dir);

        sk = me->query_skill("dodge", 1);

        if(random(40) > sk)
        {
                me->receive_damage("qi", 25);
                return notify_fail("��һ��������ˤ�˸���������\n");
        }

        return ::valid_leave(me, dir);
}
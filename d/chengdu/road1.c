//Room: road1.c
//Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short","��ʯ���");
        set("long", @LONG
����һ��ͨ���ɶ��Ĵ���ʯ��������������Σ�����ʮ�����¡�
�ɶ�ƽԭ����츮֮��������������Ұ���˹�����ƽƽչչ�Ĵ���ϣ�
ż�������һ��Դ���Ũ��ϸϸ��ȥ�������˼ҾӴ���
LONG );
        set("outdoors", "emei");
        set("exits",([ /* sizeof() == 1 */
            "east"       : "/d/emei/qsjie1",
            "southwest"  : __DIR__"road2",
            "northwest"  : __DIR__"liangting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15160);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣���߲�·ͨ��ĥ��̨�������塣��������Զ��
���������ˡ�
LONG );
        set("exits", ([ 
                "east"       : __DIR__"shanlu001",
                "west"       : __DIR__"shanlu6",
                "northwest"  : __DIR__"shanlu13",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6940);
	set("coor/y", -5540);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
//Room: /d/dali/chahua6.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�軨԰");
        set("long", @LONG
�����軨�ھ����£����������Ĳ軨��Ȼ���Ƿ�Ʒ����վ�ڲ軨
԰�У������Ǵ��̵Ĺ�ľ�������ŵ��Ǳ��������ĺ���һ���峹
��СϪ�������������С�����м���һ�轿�޵Ĳ軨��
LONG );
        set("objects", ([
           "/d/dali/obj/chahua5": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/chahua3",
            "north"  : "/d/dali/chahua7",
        ]));
	set("coor/x", -19071);
	set("coor/y", -6831);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}
//Room: /d/dali/milin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","����");
        set("long",@LONG
�˴�ɽ����խ����ľ�ر�ï�ܣ�ɽ��̤������С�����ݺύ����
��ľ�ڵ��谭�ţ���·�߲�ͣ���õ�������·������˳��ǰ��������
��ɽ������������ʱ�������޾��ߣ�ż�����ܿ��������Ŀ�ȸ�ɹ���
LONG);
        set("objects", ([
                "/clone/beast/qingshe": 1,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : __DIR__"yangzong",
            "southup"    : __DIR__"shanjian",
        ]));
	set("coor/x", -19030);
	set("coor/y", -6890);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
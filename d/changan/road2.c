//  Room:  /d/changan/road2.c

inherit  ROOM;

void  create  ()
{
        set("short",  "��ٵ�");
        set("long",  @LONG
����һ��������ֱ�Ĺٵ�������ݵ���ʮ�����ۡ�����ͨ�򺯹ȹأ�
������ֱ�ﳤ���ǡ�������һ��С·ͨ��ɽ�
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"  :  "/d/village/hsroad1",
                "east"   :  __DIR__"hanguguan",
                "west"   :  __DIR__"zhongnan",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/mingjiao/yuan/zhou5" : 1,
                "/d/mingjiao/yuan/wu6" : 1,
                "/d/mingjiao/yuan/zheng7" : 1,
                "/d/mingjiao/yuan/wang8" : 1,
        ]));
        set("outdoors", "guanzhong");
        set("no_clean_up", 0);
        set("coor/x", -10620);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
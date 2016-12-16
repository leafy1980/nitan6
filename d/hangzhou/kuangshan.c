// /d/hangzhou/kuangshan.c

#include <ansi.h>
#include <room.h>

inherit PRODUCING_ROOM;

void create()
{
        set("short", "ͭ��ɽ");
        set("long", @LONG
������ɽ�ţ�ɽ�����Ѳ������ͣ��ܶ�ط��ڿ���һЩ���ڣ���
���˳������롢�����������ڰ���һЩ�������㿴���������Ų���ʯ
ͷ����ɫ��Ө�������Ǳ�ʯһ�㣬�ƺ��ʵز��Ǻܴ�����Щ�ط�����
�׻��������ʡ�
LONG );
        set("exits", ([
                "west" : __DIR__"kslu2",
        ]));

        set("objects", ([
                __DIR__"npc/jiangong" : 1,
        ]));

        set("no_fight", 1);

        set("product/cuprum_ore", ([ "name" : "ͭ��ʯ",
                                     "rate" : 100,
                                     "max"  : 10000, ]));

        set("outdoors", "hangzhou");
	set("coor/x", 800);
	set("coor/y", -2110);
	set("coor/z", 0);
	setup();
        replace_program(PRODUCING_ROOM);
        set_heart_beat(120);
}
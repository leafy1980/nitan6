// Room: /d/kunlun/shanlin5.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��ɼ��");
        set("long",@long
����һƬ�����޾��Ĵ��̵����֣����ܵ���ɼ�����ľ�ɡ������
������֦Ѿ��ֻ©�°߰ߵ��ϸ�����Ӱ������ʮ���ľ�������ȸҲ��
������ֻż��������Զ���ļ���������
long);
        set("exits",([
                "north" : __DIR__"conglinggu",
                "east"  : __DIR__"shanlin6",
                "south" : __DIR__"shanlin"+(random(5)+1),
                "west"  : __DIR__"shanlin"+ (random(5)+1),
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -119990);
        set("coor/y", 40140);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
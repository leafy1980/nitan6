// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

#include "maze.h"

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����һ����ԼĪ���˶�ߵĴ�ʯ�鹹�ɵ���ʯ�󣬹�ģ�ƺ����󣬵�
̧����ȥ�����ܾ������ص�������Ᾱ�ʯ����ȫ��������·ͨ��ʯ��֮�⣬
��֮���г�������������������������ͷ����ʯ������һ��б����ʯ��(s
hibei)�������ڸ����С�
LONG );

        set("exits", ([
                "east"  : __DIR__"maze42",
                "south" : __DIR__"maze60",
                "west"  : __DIR__"maze53",
                "north" : __DIR__"maze54",
        ]));

        set("item_desc", ([
                "shibei" : "
�������ڣ����㼪������󴨣����ꡣ
�������ţ��ݼ����������ࡣ
�����Ŷ����������������Ӻ�֮�����кþ����������֮��
�����������õУ���Ļ�գ�������衣
�������ģ��¼�������ƥ�����޾̡�
�������壺�������磬�޾̡�
�����Ͼţ����������죬���ס�
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 61, me);
        check_count(me, 61);
        return;
}
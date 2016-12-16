// Code of JHSH
// didao.h 
// zhangchi 7/00

#include <ansi.h>

int get_room(string);
int do_dig(string);

void reset()
{
        ::reset();
        
}

int get_room(string dir)
{
        object center;
        int num;

        if (!(center=find_object("/d/mingjiao/mj_center.c")))
                center=load_object("/d/mingjiao/mj_center.c");

        num=query("didao/"+dir, center);

        return num;
}

int do_dig(string dir)
{
        object center;
        object me=this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���أ�\n");

        if (!dir || dir!=query("valid_dig"))
                return notify_fail("��Ҫ�����ڣ�\n");

        if (!present("tie qiao",me))
                return notify_fail("��û�г��ֵĹ��ߡ�\n");

        if( !query("mingjiao/job", me) || query("mingjiao/job", me) != "tu_didao" )
                return notify_fail("�㲢û���ڵص��Ĺ�����\n");

        if( query_temp("didao_done", me) )
                return notify_fail("���Ѿ���������ˣ��Ͽ��ȥ�����ɣ�\n");

        if (query("exits/"+dir))
                return notify_fail("��εص��Ѿ���ͨ�ˡ�\n");

        if (get_room(dir) >= 5)
                return notify_fail("����ô��Ҳ�ڲ����ˡ�\n");

        if( query("jing", me)<50 || query("qi", me)<30 )
                return notify_fail("���Ѿ���ƣ�����ˡ�\n");

        message_vision("$N�Ӷ����£���ǰʹ�������š�\n",me);
        addn("jing", -20, me);
        addn("qi", -30, me);
        addn_temp("wa_times", 1, me);
        me->start_busy(3);
        if( query_temp("wa_times", me)>10+random(10) )
        {
                tell_object(me,HIG"�ܵ���������ǰ�ڽ���һ����\n"NOR);
                delete_temp("wa_times", me);
                set_temp("didao_done", 1, me);
                addn("improved",1);
                if (query("improved") >= 5)
                {
                        if (!(center=find_object("/d/mingjiao/mj_center.c")))
                                center=load_object("/d/mingjiao/mj_center.c");
                        addn("didao/"+dir, 1, center);
                        tell_object(me,HIG"��ϲ��������ͨ��һ�εص���\n"NOR);
                        addn("combat_exp", 200, me);
                        tell_object(me,HIG"��ľ�������200�㣡\n"NOR);
                        load_object(__FILE__);
                }
        }

        return 1;
}
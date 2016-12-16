// by Lonely

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int i;
        object *ob;     

        if (duration == 1)
        {
                set_temp("die_reason", "�綾��������", me);
                tell_object(me, HIB "��Ȼȫ����Ѫ�������綾���ģ������Ѿ�û���ˣ�\n" NOR );
                message("vision", me->name() +"������һ����ɫ��ɢ�����Ͽ�ʼ������Ѫ��\n", environment(me), me);
                me->receive_wound("jing",query("max_jing", me)*4);
                me->receive_damage("qi",query("max_qi", me)*4);
        }
        if (! living(me) && (duration != 1)) 
        {
                message("vision", me->name() + "ʹ��غ���һ����\n", environment(me), me);
        } else 
        {
                if (duration > 1 && random(10) > 6) 
                {
                        switch(random(2)) 
                        {
                        case(0):       
                                tell_object(me, HIB "�����ڶ���������������ɢ���ж����ܿ���\n" NOR );
                                message("vision", me->name() + "��Ŀ��ɢ�ң���ɫ�쳣�����µ�Ц��һ�¡�\n",
                                        environment(me), me);
                                ob = all_inventory(environment(me));
                                for(i = 0; i < sizeof(ob); i++) 
                                {
                                        if( query("race", ob[i]) == "����" && ob[i] != me )
                                        {
                                                message_vision(HIR "$N�����ƵĴ��һ����ʧ�����ǵĹ���������\n" NOR, me);
                                                me->want_kill(ob[i]);
                                                me->kill_ob(ob[i]);
                                                ob[i]->fight_ob(me);
                                        }       
                                }
                                break;
                        case(1):
                                set_temp("die_reason", "�綾��������", me);
                                tell_object(me, HIB "��Ȼ�θ�һ���ʹ�������ڵĶ��������ˣ�\n" NOR );
                                message("vision",  me->name() +"��Ŀ��ɢ�ң���ɫ�쳣�����Ϸ���һ�������\n", environment(me), me);
                                me->receive_damage("qi", 50);
                                me->receive_wound("jing", 30);
                                break;

                        }
                }
 
        }
        me->apply_condition("hua_poison", duration - 1);

        if (duration < 1) return 0;

        return CND_CONTINUE;
}
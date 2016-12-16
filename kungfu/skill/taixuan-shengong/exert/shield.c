// shield.c ̫��������

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ����̫�����������Լ��ķ�������\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("taixuan-shengong", 1) < 100)
                return notify_fail("���̫���񹦵����⻹̫��ǳ��\n");

        if( query_temp("shield", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIR "$N" HIR "���������뵤�˫��һ�񣬶�ʱһ��"
                        HIR "���������ܷ������ۣ���$P"
                        HIR "ȫ�����֡�\n" NOR, me);

        addn_temp("apply/armor", skill*2, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other,__FILE__, "remove_effect", me, skill * 2 :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("shield", me) )
        {
                addn_temp("apply/armor", -amount, me);
                delete_temp("shield", me);
                tell_object(me, "���̫����������ϣ��������ջص��\n");
        }
}
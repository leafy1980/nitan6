// powerup.c 海天一啸

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount, int amount1);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用怒海狂涛来提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "仰天长啸，气势如山洪爆发，丹田内力迅速游遍全身！！\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        addn_temp("apply/unarmed", skill*1/3, me);
        addn_temp("apply/strike", skill*1/3, me);
        addn_temp("apply/cuff", skill*1/3, me);
        addn_temp("apply/claw", skill*1/3, me);
        addn_temp("apply/hand", skill*1/3, me);

        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill * 2 / 5, skill * 1 / 3 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount, int amount1)       
{
        if (!me) return;
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                addn_temp("apply/unarmed", -amount1, me);
                addn_temp("apply/strike", -amount1, me);
                addn_temp("apply/claw", -amount1, me);
                addn_temp("apply/hand", -amount1, me);
                addn_temp("apply/cuff", -amount1, me);
                
                delete_temp("powerup", me);
                tell_object(me, "你的怒海狂涛运行完毕，将内力收回丹田。\n");
        }
}

#include <ansi.h>
#include <combat.h>

string name() { return HIR "燃木真焰" NOR; }

inherit F_SSERVER;

void remove_effect(object me, int skill);

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail(name() + "你必须用刀法施展。\n");

        if( query_temp("zhen_yan", me) )
                return notify_fail(name() + "无法连续施展。\n");

        if ((int)me->query_skill("ranmu-daofa", 1) < 180)
                return notify_fail("你的燃木刀法修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "ranmu-daofa")
                return notify_fail("你没有激发燃木刀法为刀法，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");


        msg = HIY "$N" HIY "双手持刀，对天咆哮，所施正是燃木刀法绝学「"
              HIR "燃木真焰" HIY "」。霎时呼啸声大作，但见一股澎湃无比的罡劲"

              "至$N" HIY "刀间涌出，云贯向$N" HIY "而去。\n" NOR;
        message_combatd(sort_msg(msg), me);
        if (me->is_fighting())
                me->start_busy(2);
        skill = me->query_skill("ranmu-daofa",1);
        set_temp("zhen_yan", 1, me);
        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        addn_temp("apply/weapon_damage", skill/4, me);
        addn("neili", -400, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
        return 1;
}

void remove_effect(object me, int skill)
{
        if( query_temp("zhen_yan", me) )
        {
                addn_temp("apply/attack", -(skill*2/5), me);
                addn_temp("apply/defense", -(skill*2/5), me);
                addn_temp("apply/weapon_damage", -(skill/4), me);
                delete_temp("zhen_yan", me);

                tell_object(me, "你经过调气养息，又可以继续施展「" HIR "燃木真焰" NOR "」了。\n");
        }
}


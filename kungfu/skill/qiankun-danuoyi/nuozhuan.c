// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return MAG "挪转乾坤" NOR; }

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;
        int level;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未转世重生，无法施展" + name() + "。\n" NOR);

        if( (level = me->query_skill("qiankun-danuoyi", 1)) < 1000 )
                return notify_fail("你的乾坤大挪移还不够熟练，难以施展" + name() + "。\n" NOR);

        if( (int)query("jingli", me) < 2000 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n" NOR);

        if( (int)query("neili", me) < 5000 )
                return notify_fail("你现在内力不够，难以施展" + name() + "。\n" NOR);

        if (query_temp("nuozhuan", me))
                return notify_fail("你已经运起" + name() + "。\n" NOR);

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);
        set_temp("nuozhuan", 1, me);
        msg = MAG "\n$N" MAG "提起真气，默念" + name() + "心法，心中卸力拆招的法门已达发乎自然之境。\n" NOR;

        message_combatd(msg, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), level/60);

        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if ((int)query_temp("nuozhuan", me))
        {
                delete_temp("nuozhuan", me);
                tell_object(me, "你的「挪转乾坤」运功完毕，将内力收回丹田。\n");
        }
}

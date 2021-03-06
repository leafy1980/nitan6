// richu.c 日月光华 之 日出东方
// By haiyan

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
    int skill;

        if( query("gender", me) != "无性" && !query("reborn/times", me))
                return notify_fail("你的性别与日月内功相斥，无法使用此绝招！\n");  

    if (target != me)
        return notify_fail("你只能用日月光华来提升自己的潜力。\n");

    if ((int)me->query_skill("riyue-guanghua",1) < 100)
        return notify_fail("你的日月光华修为太低，无法施展「日出东方」。\n");

    if( query("neili", me)<200 )
        return notify_fail("你的内力不够。\n");

    if( query_temp("richu", me) )
        return notify_fail("你已经在运功中了。\n");

    skill = me->query_skill("force");
    addn("neili", -120, me);
    me->receive_damage("qi", 0);
    message_combatd(HIR "$N" HIR "一声怪啸，双目变得赤红，双足一点，身子腾空而起，"
                    "四周顿时热浪翻涌，灸热难当。\n" NOR, me);
    addn_temp("apply/attack", skill/3, me);
    addn_temp("apply/dodge", skill/3, me);
    addn_temp("apply/parry", skill/3, me);
    addn_temp("apply/damage", skill*3, me);
    addn_temp("apply/dex", skill/20, me);

    set_temp("richu", 1, me);

    me->start_call_out((:call_other, __FILE__, "remove_effect", me,
                         skill:), skill);
    if (me->is_fighting()) me->start_busy(3);

    return 1;
}

void remove_effect(object me, int amount)
{
    if( query_temp("richu", me) )
    {
        addn_temp("apply/attack", -amount/3, me);
        addn_temp("apply/dodge", -amount/3, me);
        addn_temp("apply/parry", -amount/3, me);
        addn_temp("apply/damage", -amount*3, me);
        addn_temp("apply/dex", -amount/20, me);
        delete_temp("richu", me);
        tell_object(me, "你的日出东方运行完毕，将内力收回丹田。\n");
    }
}

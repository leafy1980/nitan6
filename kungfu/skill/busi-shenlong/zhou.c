//zhou.c

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int exert(object me)
{
        string msg;
        object target;
        int skill, ap, dp, attack_decrease,dodge_decrease;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("busi-shenlong",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「咒法」只能在战斗中使用。\n");
        if( me->is_busy() )
                return notify_fail("你正忙着呢。\n");
        if( (int)me->query_skill("busi-shenlong", 1) < 200)
                return notify_fail(HIM "你的不死神龙心法修为不足，还无法用内力念出真言! \n" NOR);
        if( query("neili", me)<1000 || query("max_neili", me)<2000 )
                return notify_fail("你的内力不够，无法念出真言。\n");

        message_vision(HIR "\n$N突然向后一跃，双臂向上伸展，口中喃喃有词......\n
                       万年不老!永享仙福!寿与天齐!文武仁圣！\n
                       万年不老!永享仙福!寿与天齐!文武仁圣！\n
                       万年不老!永享仙福!寿与天齐!文武仁圣！\n\n" NOR, me);

        ap=query("combat_exp", me)/1000+skill*5;
        if(living(target))
                dp=query("combat_exp", target)/4000;
        else    dp = 0;

        if( random(ap) > dp * 2 )
        {
                if(userp(me))
                        addn("neili", -500, me);
                msg = HIM "$n听到$N口中的咒语，突感神经错乱，全身失去知觉一般！\n"NOR;
                attack_decrease=query("apply/attack", target)/6;
                dodge_decrease=query("apply/defense", target)/6;
                addn_temp("apply/attack", -attack_decrease, target);
                addn_temp("apply/defense", -dodge_decrease, target);
                if (! target->is_busy())
                        target->start_busy(2);
                me->start_busy(random(3));
        }
        else
        if( random(ap) > dp )
        {
                if(userp(me))
                        addn("neili", -500, me);
                msg = HIR "$n听到$N口中的咒语，突感精神恍惚，手脚顿时不听使唤！\n"NOR;
                attack_decrease=query("apply/attack", target)/9;
                dodge_decrease=query("apply/defense", target)/9;
                addn_temp("apply/attack", -attack_decrease, target);
                addn_temp("apply/defense", -dodge_decrease, target);
                if (! target->is_busy())
                target->start_busy(2);
                me->start_busy(random(3));
        }
        else
        {
                msg = CYN "$n眼观鼻，鼻观心，抱元守一，终于脱离了邪咒控制！\n"NOR;
                if(userp(me))
                        addn("neili", -400, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
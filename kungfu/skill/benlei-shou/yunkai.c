// yunkai.c 云开雾阖
// Last Modified by winder on Sep. 12 2001

#include <ansi.h>;
inherit F_SSERVER;
#define PNAME "「云开雾阖」"
int perform(object me,object target)
{
        string msg;
        object weapon;
        int skill, ap, dp, neili_wound, qi_wound;

        int flag;
        string fskill,sskill,bskill,pfname;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname))
   return notify_fail("你所使用的外功中没有这种功能。\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能对战斗中的对手使用。\n");
                
        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用"PNAME"！\n");
                
        fskill = "honghua-shengong";
        bskill = "hand";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }
        if( (int)me->query_skill(fskill, 1) < 60 )
                return notify_fail("你的"+to_chinese(fskill)+"等级不够，不能使用"+PNAME+"。\n");
        if( (int)me->query_skill(sskill, 1) < 60 )
                return notify_fail("你的"+to_chinese(sskill)+"等级不够，不能使用"+PNAME+"。\n");
        if( query("max_neili", me)<200 )
                return notify_fail("你的内力修为不够，无法使"PNAME"！\n");
        if( query("neili", me)<150 )
                return notify_fail("你的内力不够，无法运用"PNAME"！\n");
 
        msg = HIC "$N"HIC"潜运「云开雾阖」，双掌挟着阵阵的风雷之声向$n"HIC"击去。\n"NOR;
        message_combatd(msg, me, target);
        skill = me->query_skill(bskill, 1);
 
        ap=query("combat_exp", me)+skill*400;
        dp=query("combat_exp", target)/2;
        if( dp < 1 ) dp = 1;
        if( random(ap) > dp )
        {
                msg=HIR"$n"HIR"只觉得胸前一阵剧痛，“哇”的一声喷出一口鲜血！\n"NOR;
                neili_wound = 100 + random(skill);
                qi_wound = neili_wound * 2;
                if( qi_wound>query("qi", target) )
                        qi_wound=query("qi", target);
                if( neili_wound>query("neili", target) )
                        neili_wound=query("neili", target);
                if( userp(me))addn("neili", -(100+neili_wound/2), me);
                
                addn("neili", -neili_wound, target);
                target->receive_damage("qi", qi_wound,me);
                target->start_busy(2);
                me->start_busy(random(2));
        }
        else
        {
                msg = HIG"只见$n不慌不忙，轻轻一闪，躲过了$N的必杀一击！\n"NOR;
                if( userp(me))addn("neili", -100, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                伤害对方气血和内力

        出手要求：
                红花神功60级
                奔雷手60级
                内力修为200
                内力150
HELP
        );
        return 1;
}
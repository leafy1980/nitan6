#include <ansi.h>
#include <combat.h>

string name() { return HIW "̫������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 80)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill("wudang-jian", 1) < 60)
                return notify_fail("����䵱������Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "wudang-jian")
                return notify_fail("��û�м����䵱����������ʩչ" + name() + "��\n");

        if( query("neili", me)<50 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "�������������" + weapon->name() +
              HIW "��ת������һ�������Ľ�Ȧ������$n" HIW "��ȥ��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -30, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "����������һ����������ʱ��$N"
                                           HIR "���У���Ѫֱ����\n" NOR);
        } else
        {
                addn("neili", -20, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "΢΢һЦ������񵲿���$P"
                       CYN "�Ľ��С�\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
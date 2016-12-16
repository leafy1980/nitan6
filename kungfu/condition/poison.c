// Inherit: condiction:poison

#include <ansi.h>
#include <condition.h>

// Notify here:
// If someone try to dispel all condition, he must dispel
// one by one.
// If the dispel function of a condition was null, then
// the condition will be ignore from dispel, BUT, IF THE
// DISPEL FUNCTION RETURN BY ONE, the object will stop
// to dispel next condition.
// Or, the condition may not ill or poison, only for other
// purpose, so the dispel function of the condition should
// return by -1 to indicate it.

// Here is the base of poison-condition. If you want to
// design a non-poison condition, just don't inherit me.

// -----------------------------------------------------------

// Some creature may be poison, or some drug, medice, when
// other one has been ... So the caller doesn't want to call
// 'apply_condition' but do_effect.

// Description of the poison:
// level : the poison's level, refer the force skill
// remain: how much poison left, -1 will be non-limit
// id    : who make this poison
// name  : the name of the poison, defulat:"nature poison"

string chinese_name() { return "��"; }

string update_msg_others()
{
        return HIG "$N" HIG "ʹ���������һ����\n" NOR;
}

string update_msg_self()
{
        return HIG "���е�$?" HIG "�����ˡ�\n" NOR;
}

string die_msg_others()
{
        return RED "$N" RED "˻���Ž����������Ͳ��ٴ����ˡ�\n" NOR;
}

mapping mixed_poison(mapping p1, mapping p2)
{
        mapping p;
        int r;

        if (! p1 && ! p2)
                return 0;

        p = allocate_mapping(4);

        // calculate the remain poison
        if (p1) r = (p1["remain"] ? p1["remain"] : (int)p1["level"] * (int)p1["duration"]);
        else    r = 0;

        if (p2) r += (p2["remain"] ? p2["remain"] : (int)p2["level"] * (int)p2["duration"]);

        if (! p2)
        {
                p["level"]  = p1["level"];
                p["id"]     = p1["id"];
                p["name"]   = p1["name"];
                p["remain"] = r;
                return p;
        }        

        if (! p1)
        {
                p["level"]  = p2["level"];
                p["id"]     = p2["id"];
                p["name"]   = p2["name"];
                p["remain"] = r;
                return p;
        }

        // generate the new id
        if (! p1["id"]) p1["id"] = p2["id"]; else
        if (! p2["id"]) p2["id"] = p1["id"];

        if (! p1["id"] || p1["id"] != p2["id"])
                // poison made by two man mixed
                p["id"] = "...";
        else
                p["id"] = p1["id"];

        // compare & decide the new level
        p["level"] = p1["level"];
        if (p["level"] < p2["level"])
                p["level"] = p2["level"];

        // generate the new poison name
        if (! p1["name"]) p1["name"] = p2["name"]; else
        if (! p2["name"]) p2["name"] = p1["name"];
        if (! p1["name"] || p1["name"] != p2["name"])
        {
                // two poison mixed
                if (p["level"] >= 100)
                        p["name"] = "�綾";
                else
                        p["name"] = "��";
        } else
                p["name"] = p1["name"];

        // decide the remain of poison
        p["remain"] = r;

        return p;
}

int do_effect(object ob, string cnd, mapping p)
{
        mapping cnd_info;
        int d;

        if (! objectp(ob))return 0;
        
        if (! p || ! intp(p["level"]) || ! intp(p["duration"]) ||
            ! stringp(p["id"]))
                return 0;

        if (! stringp(p["name"])) p["name"] = this_object()->chinese_name();

        cnd_info = mixed_poison(ob->query_condition(cnd), p);
        ob->apply_condition(cnd, cnd_info);
        return 1;
}

int dispel(object me, object ob, mapping cnd)
{
        int my_lvl;
        int need_lvl;
        int cost_neili;
        int power;
        int dis;
        string pos;

        if (! cnd || ! intp(cnd["level"]) || ! intp(cnd["remain"]) ||
            ! stringp(cnd["id"]))
                return 0;

        if (! stringp(cnd["name"]))
                cnd["name"] = "��";

        pos = cnd["name"];
        if( query("neili", me)<200 )
        {
                tell_object(me, "���������㣬�޷���ɢ" + pos + "��\n");
                return -1;
        }

        need_lvl = cnd["level"] + 10;
        if( query("breakup", ob) )
                need_lvl = need_lvl * 7 / 10;

        if( query("immune/poison", ob) == -1 )
                need_lvl = 1;
        else
                need_lvl-=query("immune/poison", ob);
        if (need_lvl < 1) need_lvl = 1;

        if (me != ob)
                need_lvl += need_lvl / 5;

        if( cnd["id"] == query("id", me) )
                need_lvl = 50;

        my_lvl = me->query_skill("force") +
                 me->query_skill("poison") / 5 +
                 me->query_skill("dispel-poison", 1) +
                 query_temp("apply/dispel-poison", me);

        // �ƾ�������ǿ�ƶ�Ч��
        if( query("special_skill/divine", me) )
                my_lvl += (int)me->query_con() * 3;
                
        // ���������ǿ�ƶ�Ч����Ч��Ϊ�ƾ�����2��
       if( query("special_skill/qigu", me) )
                my_lvl += (int)me->query_con() * 6;
        
        if( query("reborn/times", me) )
                my_lvl = my_lvl * 120 / 100;
        else
                my_lvl = my_lvl * 110 / 100;

        if (need_lvl > my_lvl)
        {
                if (me == ob)
                {
                        tell_object(me, MAG "�������ڹ���ɢ" + pos +
                                    "��Ȼ���ƺ�û�а��Ч����\n" NOR);
                        me->start_busy(1);
                        return -1;
                } else
                {
                        tell_object(me, MAG "�������ڹ�����" + ob->name() +
                                    "��ɢ" + pos + "��Ȼ���ƺ�û�а��Ч����"
                                    "\n" NOR);
                        tell_object(ob, MAG + me->name() + "��������������"
                                    "����������������һ����ģ�����Ż�¡�"
                                    "\n" NOR);
                        me->start_busy(1);
                        ob->start_busy(1);
                        return -1;
                }
        }

        // ȥ������
        power = my_lvl + me->query_skill("dispel-poison", 1)  +
                query_temp("apply/dispel-poison", me);
        if( query("breakup", ob) )
                power += power * 3 / 10;
        if (me == ob)
        {
                if( cnd["id"] == query("id", me) )
                {
                        tell_object(me, WHT "�������ڹ�����" + pos +
                                    "������ɢ��\n" NOR);
                        addn("neili", -100, me);
                        cnd["remain"] = 0;
                        me->start_busy(1);
                } else
                {
                        cost_neili=query("neili", me);
                        dis=query("neili", me)*power/(cnd["level"]+1)/2;
                        if (cnd["remain"] == -1)
                                cnd["remain"] = 10000;
                        if (dis >= cnd["remain"])
                        {
                                dis = cnd["remain"];
                                cost_neili = cnd["remain"] * 2 * (cnd["level"] + 1) /
                                             power;
                                tell_object(me, WHT "�������ڹ�����" + pos +
                                            "������ɢ��\n" NOR);
                        } else
                        {
                                tell_object(me, WHT "�������ڹ�����ɢ��һЩ" + pos +
                                            "��\n" NOR);
                        }
                        cnd["remain"] -= dis;
                        if (cnd["remain"] < 0)
                                cnd["remain"] = 0;
                        addn("neili", -cost_neili, me);
                        me->start_busy(2 + random(2));
                }
        } else
        {
                if( cnd["id"] == query("id", me) )
                {
                        tell_object(me, WHT "�������ڹ�������" + ob->name() +
                                    "��" + pos + "������ɢ��\n" NOR);
                        addn("neili", -150, me);
                        cnd["remain"] = 0;
                        me->start_busy(2);
                        ob->start_busy(1);
                } else
                {
                        cost_neili=query("neili", me);
                        dis=query("neili", me)*power/(cnd["level"]+1)/4;
                        if (cnd["remain"] == -1)
                                cnd["remain"] = 10000;
                        if (dis >= cnd["remain"])
                        {
                                dis = cnd["remain"];
                                cost_neili = cnd["remain"] * 4 * (cnd["level"] + 1) /
                                             power;
                                tell_object(me, WHT "�������ڹ�������" + ob->name() +
                                            "��" + pos + "������ɢ��\n" NOR);
                        } else
                        {
                                tell_object(me, WHT "�������ڹ�������" + ob->name() +
                                            "��ɢ��һЩ" + pos + "��\n" NOR);
                        }
                        cnd["remain"] -= dis;
                        if (cnd["remain"] < 0)
                                cnd["remain"] = 0;
                        addn("neili", -cost_neili, me);
                        me->start_busy(4 + random(4));
                        ob->start_busy(2 + random(2));
                }
        }

        if ( cnd["remain"] == 0)
                ob->clear_condition(this_object()->name());

        return 1;
}

// calucate the damage of jing per heart beaten
int jing_damage(object me, mapping cnd)
{
        int d;

        d = cnd["level"];

        if (d >= 64)
                d = 24 + (d - 64) / 8;
        else
        if (d >= 32)
                d = 16 + (d - 32 ) / 4;
        else
                d /= 2;
        if (d < 10) d = 10;

        return d / 2 + random(d);
}

// calucate the damage of qi per heart beaten
int qi_damage(object me, mapping cnd)
{
        int d;

        d = cnd["level"];

        if (d > 300 )
                d = 100 + (d - 300) / 12;
        else
        if (d > 60)
                d = 60 + (d - 60 ) / 6;
        if (d < 10) d = 10;

        return d / 2 + random(d);
}

// die reason
string die_reason(string name)
{
        if (! name || name == "��")
                return "����������";
        else
                return name + HIM "����������";
}

int update_condition(object me, mapping cnd)
{
        int jd;
        int qd;
        int jw;
        int qw;
        int improve;

        if( query_temp("fengxue", me) )
              return CND_NO_HEAL_UP | CND_CONTINUE;

        if( !mapp(cnd) || query_temp("nopoison", me))return 0;

        if (! intp(cnd["level"]) ||
            ! intp(cnd["remain"] ||
            ! stringp(cnd["id"])))
                return 0;

        jd = this_object()->jing_damage(me, cnd);
        qd = this_object()->qi_damage(me, cnd);

        if( !living(me) && (query("jing", me)<jd || query("qi", me)<qd) )
        {
                set_temp("die_reason", die_reason(cnd["name"]), me);
                message_vision(die_msg_others(), me);
                me->die();
                return 1;
        }

        jw = jd / 2;
        qw = qd / 2;
        if( jw>query("eff_jing", me) )
        {
                jw=query("eff_jing", me);
                if (jw < 0) jw = 0;
        }

        if( qw>query("eff_qi", me) )
        {
                qw=query("eff_qi", me);
                if (qw < 0) qw = 0;
        }
        
        qd *= 3;
        qw *= 3;

        improve=query("immune/poison", me);
        if (improve != -1)
        {
                me->receive_damage("jing", jd);
                me->receive_wound("jing",  jw);
                me->receive_damage("qi",   qd);
                me->receive_wound("qi",    qw);
        }

        //if (cnd["id"] == "nature poison" || improve == -1 ||
            if (cnd["id"] == "poison" || improve == -1 ||
            cnd["level"] / 2 + random(cnd["level"]) < (int)me->query_skill("force") + improve)
        {
                // ����������������
                if (improve == -1)
                        cnd["remain"] = 0;
                else
                        cnd["remain"] -= improve;

                if (cnd["remain"] <= cnd["level"])
                {
                        message("vision", HIM + me->name() + "��������"
                                "��һ��������������ɫ�ö��ˡ�\n" NOR,
                                environment(me), ({ me }));
                        tell_object(me, HIM "��������ϵ�" + cnd["name"] +
                                    HIM "��ס�����ˣ��о��Ϻö��ˣ���"
                                    "������������һ������\n" NOR);
                        return 0;
                }

                // ����ȥ��
                cnd["remain"] -= cnd["level"];
                me->apply_condition(this_object()->name(), cnd);
        }

        message("vision", replace_string(update_msg_others(), "$N",
                          me->name()), environment(me), ({ me }));
        tell_object(me, replace_string(update_msg_self(), "$?", cnd["name"]));

        return CND_NO_HEAL_UP | CND_CONTINUE;
}
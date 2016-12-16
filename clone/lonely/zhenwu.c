#include <weapon.h>
#include <ansi.h>

inherit SWORD;

string do_wield();
string do_unwield();

void create()
{
        set_name(HIY "���佣" NOR,({ "zhenwu jian", "jian", "sword", "zhenwu" }) );
        set_weight(1500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", @LONG
����һ�����������ı����������䵱�����˳ִ˽�������ħ��ɨ��Ⱥ��
������С�����˽��޲��ĵ���ҡ��
LONG );
                set("unit", "��");
                set("value", 800000);
                set("no_sell", 1);
                set("unique", 1);
                set("material", "steel");
                set("wield_msg", (: do_wield :));
                set("unwield_msg", (: do_unwield :));
                set("stable", 80);
        }
        init_sword(200);
        setup();
}

string do_wield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        call_out("check_npc", 0, me, environment(me));
        if( query("shen", me)>10000 )
        {
                return HIC "$Nһ����Х����$n" HIC "�������ʣ���ʱ��ؼ������Ȼ��\n" NOR;
        } else
        if( query("shen", me) >= 0 )
        {
                return HIC "$Nһ���֣���Ȼ��$n" HIC "�������С�\n" NOR;
        } else
        if( query("shen", me)>-10000 )
        {
                return HIG "$Nսս����������һ��$n" HIG "��\n" NOR;
        } else
        {
                return HIG "$Nһ����Ц����ৡ���һ��������$n" HIG "��\n" NOR;
        }
}

string do_unwield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        if( query("shen", me) >= 0 )
                return HIC "$Nһ���֣��������ʡ�\n" NOR;
        else
        if( query("shen", me)>-10000 )
                return HIG "$N��$n" HIG "��ؽ��ʣ�Ĩ��Ĩͷ�ϵĺ���\n" NOR;
        else
                return HIG "$Nһɹ����$n" HIG "��ؽ��ʡ�\n" NOR;
}

void check_npc(object me, object env)
{
        object *ob;
        int i;

        if (! objectp(me) || ! living(me))
                return;

        if (environment(me) != env)
                return;

        ob = all_inventory(env);
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character() || ob[i] == me ||                    
                    !living(ob[i]) || query("not_living", ob[i]) || 
                    query("id", ob[i]) == "zhang sanfeng" )
                        continue;

                if (me->is_bad())
                {
                        if (userp(ob[i]))
                                continue;

                        if( query("shen", ob[i])>10000 )
                        {
                                message_vision("$N��ŭ�ȵ��������" + RANK_D->query_rude(me) +
                                               "����Ȼ�ҵ������佣��\n", ob[i]);
                                if( !query("on_fight", env) )
                                        ob[i]->kill_ob(me);
                        } else
                        if (ob[i]->is_bad())
                        {
                                message_vision(random(2) ? "$N������Ц����$n�����ɵúã��ɵúá�\n" :
                                                           "$Nƴ�����ƣ���$n�����ֵܼ��͸ɰ���",
                                               ob[i], me);
                        }
                        continue;
                }

                if (me->is_not_good())
                        continue;

                if( query("shen", ob[i])>10000 && !userp(ob[i]) )
                {
                        message_vision(random(2) ? "$N�޵����ý����ý���\n" :
                                                   "$N̾�������˽�������������˰���\n",
                                       ob[i]);
                } else
                if( query("shen", ob[i])<-10 && !userp(ob[i]) )
                {
                        mixed ob_exp, my_exp;
                        ob_exp=query("combat_exp", ob[i]);
                        my_exp=query("combat_exp", me);
                        if (ob_exp > my_exp * 2 || ob_exp > 1500000)
                        {
                                message_vision(random(2) ? "$N��$n���������������������ǰ��Ū��\n" :
                                                           "$Nһ����Ц����$n��������Ϊ����˭�������᣿����������\n",
                                               ob[i], me);
                        } else
                        if (ob_exp > 20000)
                        {
                                message_vision(random(2) ? "$N��ɫ��Щ���Ծ���\n" :
                                                           "$N¶�����µ���ɫ��\n",
                                               ob[i]);
                                if( query("no_fight", env) )
                                        continue;
                                message_vision(random(2) ? "$Nŭ��һ��������Ҷ���Ҫ���ˣ���\n" :
                                                           "$Nһ�Բ�������������$n�����μ��졣\n",
                                               ob[i], me);
                                ob[i]->kill_ob(me);
                        } else
                        {
                                message_vision(random(2) ? "$N��ͨһ����̱���ڵأ�˫�ּ�ҡ�����������ң���Ĳ����ң���\n" :
                                                           "$Nһ�����£����Ͱ͵�ʲôҲ˵��������\n",
                                               ob[i], me);
                                if( !query("no_fight", env) )
                                        ob[i]->unconcious();
                        }
                }
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->is_bad() || victim->is_good())
                return - damage_bonus / 2;

        if (me->is_not_good() || victim->is_not_bad())
                return 0;

        if (me->query_skill_mapped("sword") != "taiji-jian" ||
            me->query_skill("taiji-jian", 1) < 100)
                // only increase damage
                return damage_bonus / 2;

        switch (random(4))
        {
        case 0:
                if (! victim->is_busy())
                        victim->start_busy(me->query_skill("sword") / 10 + 2);
                return HIC "$N��ǰһ�������е�" NOR+HIY "���佣" NOR+HIC "�û�������ԲȦ��"
                       "��$n��ȥ������ϸ��֮����$n���һ\n"
                       "������֪��εֵ���ֻ���������ˡ�\n" NOR;

        case 1:
                n = me->query_skill("sowrd");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                n=query("eff_jing", victim);
                n /= 2;
                victim->receive_damage("jing", n, me);
                victim->receive_wound("jing", n / 2, me);
                return random(2) ? HIY "$Nһ�����������е����佣����һ�����磬��ৡ���ɨ��$n��\n" NOR:
                                   HIY "$NͻȻ�����ȵ�����аħ������������������������佣"
                                   HIY "����һ����$n��ʱ������ǰһ����\n" NOR;
        }

        // double effect
        return damage_bonus;
}

void start_borrowing()
{
        remove_call_out("return_to_zhang");
        call_out("return_to_zhang", 7200 + random(600));
}

void return_to_zhang()
{
        object me;

        me = environment();
        if (! objectp(me))
                return;

        while (objectp(environment(me)) && ! playerp(me))
                me = environment(me);
 
        if (playerp(me))
        {
                if (me->is_fight())
                {
                        call_out("return_to_zhang", 1);
                        return;
                }

                message_vision("��Ȼһ���䵱�������˹���������$N��æ�к������������������������û�"
                               "���佣�������ڲ�����ô����\n"
                               "$N���������ˣ����ˣ�����û�ȥ�ɡ���\n"
                               "$N���������䵱���Ӵ��ߡ�\n", me);
        } else
        {
                message("visoin", "��Ȼһ���䵱�������˹������������佣��̾�˿�����ҡҡͷ���ˡ�\n",
                        me);
        }

        destruct(this_object());
}
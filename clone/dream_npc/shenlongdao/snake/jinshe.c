inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}

void create()
{
        set_name(NOR + YEL "金环蛇" NOR, ({ "jinhuan she", "jinhuan", "she" }));
        set("long", YEL "这是一只让人看了起毛骨悚然的金环蛇。\n" NOR);

        set("age", 1);
        set("str", 15);
        set("dex", 40);
        set("max_qi", 6000);
        set("max_jing", 6000);
                set("max_neili", 25000);
                set("neili", 25000);                
        set("combat_exp", 50000000);

        set("snake_poison", ([
                "level"  : 400,
                "perhit" : 200,
                "remain" : 400,
                "maximum": 400,
                "supply" : 20,
        ]));

        set("power", 10);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/dodge", 280);
        set_temp("apply/defense", 80);
        set_temp("apply/unarmed_damage", 1000);

                set("gift/exp", 20);
                set("gift/pot", 12);
                set("oblist", ([
                        "/clone/fam/gift/str2" : 200,
                        "/clone/fam/gift/str3" : 5,
                        "/clone/armor/shangu-zhixing" : 50,
                        "/clone/armor/shangu-zhixing2" : 30,
                        "/clone/armor/shangu-zhixing3" : 20,                        
                        "/clone/armor/huangtoujin":60,
                        "/clone/armor/huangtoujin2":40,
                        "/clone/armor/huangtoujin3":30,                                        
                        "/clone/armor/jinsi-beixin":20,
                        "/clone/armor/jinsi-beixin2":10,
                        "/clone/armor/jinsi-beixin3":8,        
                ]));

        setup();
                add_money("silver", 2 + random(4));
}

mixed hit_ob(object me, object ob, int damage)
{
        mapping p;
        string  msg;
        int force;
        int dur;

        p=query("snake_poison", me);
        if (! p) return;
        if (damage / 3 + random(damage * 2 / 3) <
            query_temp("apply/armor", ob) )
        {
                // Defeated by armor
                return;
        }

        msg = "";
        dur = p["perhit"];
        if (dur > (int)p["remain"]) dur = p["remain"];
        p["remain"] = (int)p["remain"] - dur;
        this_object()->apply_condition("poison-supply", 1);
        if (! dur) return;


        force = (int)ob->query_skill("force");
        if (random(force / 2) + force / 2 >= (int)p["level"] &&
            query("neili", ob)>damage/5 )
        {
                if( query("qi", ob)<150 )
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时体力不支，难以施为。\n" NOR;
                } else
                if( query("jing", ob)<60 )
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时精神不济，难以施为。\n" NOR;
                } else
                if( query("neili", ob)<damage/5+50 )
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时内力不足，难以施为。\n" NOR;
                } else
                {
                        addn("neili", -damage/5, ob);
                        ob->receive_damage("qi", 20);
                        ob->receive_damage("jing", 10);
                        return HIM "你觉得被咬中的地方有些发麻，连忙运功"
                               "化解毒性。\n" NOR;
                }
        }

        if (ob->affect_by("poison", ([ "level" : (int)p["level"] / 2,
                                       "name"  : "蛇毒",
                                       "id"    : "nature poison",
                                       "duration" : dur / 2, ])))
        {
                msg += HIR "$n" HIR "脸色一变，只觉被咬中的地方一阵麻木。\n" NOR;
        }
        return msg;
}
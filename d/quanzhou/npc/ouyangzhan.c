// ouyangzhan.c ŷ��ղ

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("ŷ��ղ", ({ "ouyang zhan", "zhan", "ouyang" }));
        set("long",
"ŷ��ղ��Ȫ����ʿ��\n");
        set("gender", "����");
        set("age", 65);
        set("no_get", 1);
        set_skill("literate", 300);

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 4000);
        set("shen_type", 1);
        setup();
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/��", ob))return 0;
        addn_temp("mark/��", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_player();
        if( !query_temp("mark/��", who) )
                set_temp("mark/��", 0, who);
        if( query("money_id", ob) && ob->value() >= 1000 )
        {
                message_vision("ŷ��ղͬ��ָ��$NһЩ����д�ֵ����⡣\n", who);
                addn_temp("mark/��", ob->value()/50, who);
                return 1;
        }
}
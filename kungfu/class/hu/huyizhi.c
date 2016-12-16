// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>;

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("����֮", ({ "hu yizhi", "hu", "yizhi" }));
        set("gender", "����");
        set("nickname", HIR "������" NOR);
        set("character", "��������");
        set("age", 37);
        set("long", @LONG
���˺������꣬ͷ�Ϲ���һΧ�׽�����������
һ˫��Ь��ȫȻһ����ũģ����
LONG);
        set("attitude", "peaceful");
        set("str", 36);
        set("int", 28);
        set("con", 31);
        set("dex", 33);

        set("qi", 6500);
        set("max_qi", 6500);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 160);
        set("level", 40);
        set("combat_exp", 2000000);

        set_skill("force", 640);
        set_skill("lengyue-shengong", 640);
        set_skill("blade", 660);
        set_skill("baisheng-daofa", 660);
        set_skill("hujia-daofa", 640);
        set_skill("dodge", 640);
        set_skill("sixiang-bufa", 640);
        set_skill("parry", 640);
        set_skill("strike", 640);
        set_skill("tianchang-zhang", 640);
        set_skill("cuff", 640);
        set_skill("hujia-quan", 640);
        set_skill("throwing", 650);
        set_skill("mantian-xing", 650);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
        set_skill("daojian-xiaotianwai", 800);

        map_skill("force", "lengyue-shengong");
        map_skill("blade", "baisheng-daofa");
        map_skill("dodge", "sixiang-bufa");
        map_skill("parry", "baisheng-daofa");
        map_skill("strike", "tianchang-zhang");
        map_skill("cuff", "hujia-quan");
        map_skill("throwing", "mantian-xing");

        prepare_skill("strike", "tianchang-zhang");
        prepare_skill("cuff",   "hujia-quan");

        create_family("�������", 13, "����");

        set("inquiry", ([
                "��ʤ����" : (: ask_me :),
                "������"   : "�������Ѿ����ˣ�������������",
                "��ԲԲ"   : "������Ҳû�ܺ���˵�ϼ��仰��",
                "��԰԰"   : "������Ҳû�ܺ���˵�ϼ��仰��",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.heng" :),
                (: perform_action, "cuff.kuai" :),
                (: perform_action, "strike.huang" :),
                (: perform_action, "dodge.fei" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("master_ob",5);
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

string ask_me()
{
        object ob, me;

        me = this_player();
        if( query("family/family_name", me) != "�������" )
                return "���������ó��ı��£���Ҫ��Ҫ����������\n";

        return "�ܺ�... �ܺ�... ��Ȼ�Ǻ��ҵ��ӣ���û����Ȥѧѧ�ҵİ�ʤ������";
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "�������" )
        {
                command("say ��͵ѧ���Ǻ��Ҿ������ٺ�...");
                return -1;
        }

        if (skill != "baisheng-daofa")
        {
                command("say ��ֻ�����ʤ������������������ʦ��ȥѧ�ɡ�");
                return -1;
        }

        if( !query_temp("can_learn/huyizhi/baisheng-daofa", ob) )
        {
                command("say �ã��㿴����ˣ�");
                set_temp("can_learn/huyizhi/baisheng-daofa", 1, ob);
        }

        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "��ɨǧ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/baisheng-daofa/heng",
                           "name"    : "��ɨǧ��",
                           "sk1"     : "baisheng-daofa",
                           "msg1"    : "$N΢΢���˵�ͷ����$n��������"
                                       "�ֹ��˼��䣬�漴������������"
                                       "������ն�Ȼ���ʾ�˰��졣$n��"
                                       "һ��Ĭ��������ֱ��$N��ʾ����"
                                       "��ͻȻ˫��һ�����ƺ�����ѧ��"
                                       "�������µ�ͻ�ơ�",
                           "msg2"    : "�������������������������"
                                       "������ͬС�ɡ�",
                           "lv1"     : 150,
                           "force"   : 200,
                           "gongxian": 600,
                           "shen"    : 8000, ]));
                break;

        default:
                return 0;
        }
}
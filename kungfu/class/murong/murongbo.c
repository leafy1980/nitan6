// This program is a part of NT MudLIB
// murongbo.c Ľ�ݲ�

#include <ansi.h>
#include "murong.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_me();
mixed try_learn_sk();
int try_learn_chz();
string ask_book1();
string ask_book2();
mixed ask_wuxue();

#define HUPO "/clone/unique/hupohuan"

void create()
{
        set_name("Ľ�ݲ�", ({ "murong bo", "murong", "bo" }));
        set("long", @LONG
���ǹ���Ľ�ݵĴ��ˣ�����˵����Ľ�����������书��Ϊ�ܳ�
֮�ˡ������ܹ�ͨ���°ټ�֮����������Ϊ��ͨĽ�ݼҾ�����
LONG );
        set("nickname", HIM "�Ա�֮�� ��ʩ����" NOR);
        set("gender", "����");
        set("age", 54);
        set("shen_type",-1);
        set("attitude", "peaceful");

        set("str", 31);
        set("int", 37);
        set("con", 34);
        set("dex", 33);

        set("qi", 5700);
        set("max_qi", 5700);
        set("jing", 2800);
        set("max_jing", 2800);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 145);
        set("level", 40);
        set("combat_exp", 2650000);

        // base skill
        set_skill("force", 650);
        set_skill("jingluo-xue", 650);
        set_skill("literate", 650);
        set_skill("unarmed", 650);
        set_skill("cuff", 650);
        set_skill("finger", 650);
        set_skill("strike", 650);
        set_skill("hand", 650);
        set_skill("claw", 650);
        set_skill("club", 650);
        set_skill("sword", 650);
        set_skill("blade", 650);
        set_skill("staff", 650);
        set_skill("dodge", 650);
        set_skill("parry", 650);

        // shaolin skill. No teach
        set_skill("banruo-zhang", 600);
        set_skill("cibei-dao", 600);
        set_skill("damo-jian", 600);
        set_skill("fengyun-shou", 600);
        set_skill("fumo-jian", 600);
        set_skill("hunyuan-yiqi", 600);
        set_skill("shaolin-xinfa", 600);
        set_skill("jingang-quan", 600);
        set_skill("longzhua-gong", 600);
        set_skill("luohan-quan", 600);
        set_skill("nianhua-zhi", 600);
        set_skill("pudu-zhang", 600);
        set_skill("qianye-shou", 600);
        set_skill("sanhua-zhang", 600);
        set_skill("riyue-bian", 600);
        set_skill("shaolin-shenfa", 600);
        set_skill("weituo-gun", 600);
        set_skill("wuchang-zhang", 600);
        set_skill("xiuluo-dao", 600);
        set_skill("yingzhua-gong", 600);
        set_skill("yizhi-chan", 600);
        set_skill("zui-gun", 600);

        // murong skill
        set_skill("zihui-xinfa", 650);
        set_skill("shenyuan-gong", 650);
        set_skill("douzhuan-xingyi", 650);
        set_skill("beidou-xianzong", 650);
        set_skill("canhe-zhi", 650);
        set_skill("xingyi-zhang", 650);
        set_skill("qixing-quan", 650);
        set_skill("murong-daofa", 650);
        set_skill("murong-jianfa",650);
        set_skill("huitong-tianxia", 600); 
        set_skill("martial-cognize", 600);

        map_skill("force", "zihui-xinfa");
        map_skill("dodge", "beidou-xianzong");
        map_skill("cuff",  "qixing-quan");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("finger", "canhe-zhi");
        map_skill("strike", "xingyi-zhang");
        map_skill("blade", "murong-daofa");
        map_skill("sword", "murong-jianfa");

        prepare_skill("finger", "canhe-zhi");
        prepare_skill("cuff", "qixing-quan");

        set("no_teach", ([
                "banruo-zhang"  : (: try_learn_sk :),
                "cibei-dao"     : (: try_learn_sk :),
                "damo-jian"     : (: try_learn_sk :),
                "fengyun-shou"  : (: try_learn_sk :),
                "fumo-jian"     : (: try_learn_sk :),
                "hunyuan-yiqi"  : (: try_learn_sk :),
                "shaolin-xinfa" : (: try_learn_sk :),
                "jingang-quan"  : (: try_learn_sk :),
                "longzhua-gong" : (: try_learn_sk :),
                "luohan-quan"   : (: try_learn_sk :),
                "nianhua-zhi"   : (: try_learn_sk :),
                "pudu-zhang"    : (: try_learn_sk :),
                "qianye-shou"   : (: try_learn_sk :),
                "sanhua-zhang"  : (: try_learn_sk :),
                "riyue-bian"    : (: try_learn_sk :),
                "shaolin-shenfa": (: try_learn_sk :),
                "weituo-gun"    : (: try_learn_sk :),
                "wuchang-zhang" : (: try_learn_sk :),
                "xiuluo-dao"    : (: try_learn_sk :),
                "yingzhua-gong" : (: try_learn_sk :),
                "yizhi-chan"    : (: try_learn_sk :),
                "zui-gun"       : (: try_learn_sk :),
                "canhe-zhi"     : (: try_learn_chz :),
        ]));

        create_family("Ľ������", 15, "ׯ��");
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "finger.canhe" :),
                (: perform_action, "parry.yi" :),
                (: perform_action, "finger.lian" :),
                (: perform_action, "finger.zhi" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 120);
        set_temp("apply/armor", 200);

        set("inquiry", ([
                "����"   : (: ask_me :),
                "����"   : (: ask_me :),
                "��ת����": (: ask_me :),
                "�ϻ��ķ�": (: ask_book1 :),
        "��ת������": (: ask_book2 :),
                "��ѧ����": (: ask_wuxue :),
        ]));

        set("zihui_count", 1);
        set("douzhuan_count", 1);

        set("master_ob",5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 100);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-36000 )
        {
                command("say ��Ľ�ݲ���������������Щ��ν������ʿ������");
                command("say �㻹����ذɣ�");
                return;
        }
        if( query("combat_exp", ob)<500000 )
        {
                command("say �����ھ�����ǳ�����Ƕ��ڽ��������߰ɡ�");
                return;
        }
        if ((int)ob->query_skill("douzhuan-xingyi", 1) < 130)
        {
                command("say ��ת��������Ľ�����Ҿ������㲻�ú���ϰ����������������");
                return;
        }
        if ((int)ob->query_skill("shenyuan-gong", 1) < 120)
        {
                command("say ��Ľ�������书���������һ�������ӻ����ķ���");
                command("say �����Ԫ����������������ȥ���������ɡ�");
                return;
        }
        if ((int)ob->query_skill("dodge") < 200)
        {
                command("say ��Ľ�������书��������ɵ�������");
                command("say ���Ƿ�Ӧ�����Ṧ��Ϊ�϶��µ㹦��");
                return;
        }

        command("haha");
        command("pat"+query("id", ob));
        command("recruit "+query("id", ob));
        message_vision("Ľ�ݲ���ϲ������Ľ�ݼ�����Ӣ�ŵ�����������������\n",
                       this_object());
}

mixed try_learn_sk()
{
        object me;

        me = this_player();
        if( query_temp("has_asked/murongbo", me) )
                return "�㻹�ǰ���ѧ���Ź���ɡ�";

        command("shake");
        command("say ��˵���ֵ��书ѧ�˶������к�����Ͳ�Ҫѧ�ˡ�");
        set_temp("has_asked/murongbo", 1, me);
        return -1;
}
// ������120��������20���󷽿�ѧϰ��
int try_learn_chz()
{
       object me = this_player();

       if( query("shen", me)>0 )
       {
                command("heng");
                command("��������������Щ��ν������ʿ���㻹����ذɣ�");
                return -1;
       }
/*
       if( query("born_family", me) != "Ľ������" && !query("reborn/times", me) ) 
       {
                command("sneer");
                command("say �㲻������Ľ�ݼҵ��ˣ�����������ָ�㡣");
                command("say ���»�����ذɣ�");
                return -1;
       }
*/
       if( query("family/master_id", me) != query("id", this_object()) )
       {
            command("shake");
                command("say �������Һ��޹ϸ�����������ָ�㣿");
                return -1;
       }
       /*
       if (me->query_skill("canhe-zhi", 1) < 150)
       {
                command("shake");
                command("say ��κ�ָ��򻹲�����������ȥ�����ϰ��");
                return -1;
       }
       */

       return 0;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "����ָ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/lian",
                           "name"    : "����ָ",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 160,
                           "sk2"     : "shenyuan-gong",
                           "lv2"     : 180,
                           "force"   : 160,
                           "gongxian": 900,
                           "shen"    : -60000, ]));
                break;

        case "����ָѨ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/zhi",
                           "name"    : "����ָѨ",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 140,
                           "dodge"   : 140,
                           "force"   : 140,
                           "gongxian": 600,
                           "shen"    : -75000, ]));
                break;

        case "��ڤ����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/you",
                           "name"    : "��ڤ����",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 140,
                           "force"   : 150,
                           "gongxian": 800,
                           "shen"    : -80000, ]));
                break;

        case "��ս���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/jin",
                           "name"    : "��ս���",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 160,
                           "force"   : 160,
                           "gongxian": 1000,
                           "shen"    : -95000, ]));
                break;

        case "�κϽ���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/canhe",
                           "name"    : "�κϽ���",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 160,
                           "force"   : 180,
                           "gongxian": 1200,
                           "shen"    : -160000, ]));
                break;

        case "�κ�һָ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/ci",
                           "name"    : "�κ�һָ",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 160,
                           "force"   : 180,
                           "gongxian": 1200,
                           "shen"    : -160000, ]));
                break;
        case "���̽���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/canshang",
                           "name"    : "���̽���",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 120,
                           "force"   : 120,
                           "gongxian": 300,
                           "shen"    : -16000, ]));
                break;
        case "���ǻ���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/douzhuan-xingyi/huan",
                           "name"    : "���ǻ���",
                           "sk1"     : "douzhuan-xingyi",
                           "lv1"     : 1000,
                           "force"   : 1200,
                           "gongxian": 10000,
                           "reborn"  : 1,
                           "shen"    : -16000, ]));
                break;
        /*
        case "������" :
                return MASTER_D->give_item(me, this_object(),
                        ([ "item"    : HUPO,
                           "master"  : 1,
                           "sk1"     : "zihui-xinfa",
                           "lv1"     : 180,
                           "shen"    : -50000, ]));
                break;
        */

        default:
                return 0;
        }
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/douzhuan-xingyi/yi", me) )
                return "�㻹����ȥ����ȥ���⸴���಻�ǿ�����˵�ģ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "����ʲô�ˣ��кξ��ģ�";

        if (me->query_skill("douzhuan-xingyi", 1) < 100)
                return "��ת����������Ľ�ݼҵľ�ѧ��������û�У�";

        message_vision(HIY "$n" HIY "����$N" HIY "��ʾ��$N"
                       HIY "���Լ�һ�У�$N" HIY "���ɻ���"
                       "�ĳ�һ�ƣ�ֻ��$n" HIY "��������һ����"
                       HIY "$N����ʽ����\n��Ȼ��䣬����������"
                       "�������һ����һ�ƽ��ʵʵ�Ĵ�����$P"
                       HIY "�Լ��ļ�ͷ��\n" NOR,
                       me, this_object());
        command("nod");
        command("say �����еİ����������������ʽ�����"
                "Ľ�ݼҵ��ϻ��ķ�����Ҫ�ú���ᣬȥ�ɣ�");
        tell_object(me, HIG "��ѧ���˶�ת���ơ�\n" NOR);
        if (me->can_improve_skill("douzhuan-xingyi"))
                me->improve_skill("douzhuan-xingyi", 90000);
        if (me->can_improve_skill("zihui-xinfa"))
                me->improve_skill("zihui-xinfa", 90000);
        set("can_perform/douzhuan-xingyi/yi", 1, me);
        return 1;
}

string ask_book1()
{
        mapping fam;
        object ob;
        object me;

        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(this_player()) +
                       "����Ľ�ݼ�������������֪�˻��Ӻ�̸��";

        if (me->query_skill("zihui-xinfa", 1) < 100)
                return "����ϻ��ķ�ˮƽ�����������ò����Ȿ�ؼ���";

        if (query("zihui_count") < 1)
                return "�������ˣ��ϻ��ؼ����Ѿ����ȥ�ˡ�";

        addn("zihui_count", -1);
        ob = new("/clone/book/zihui-book");
        ob->move(this_player());
        return "�ðɣ��Ȿ�ϻ��ķ�����ȥ�ú��ж���";
}

string ask_book2()
{
        mapping fam;
        object ob;
        object me;

        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(this_player()) +
                       "����Ľ�ݼ�������������֪�˻��Ӻ�̸��";

        if (me->query_skill("douzhuan-xingyi", 1) < 100)
                return "��Ķ�ת�������Ļ������ң��һ����ܸ����Ȿ�ؼ���";

        if (query("douzhuan_count") < 1)
                return "�������ˣ��ؼ����Ѿ����ȥ�ˡ�";

        addn("douzhuan_count", -1);
        ob = new("/clone/book/douzhuan-book");
        ob->move(this_player());
        return "�Ȿ��ת����������պ��ˡ�";
}

mixed ask_wuxue()
{
        object me = this_player(), ob = this_object();

        if( query("family/family_name", me) != "Ľ������" )
        {
                write(ob->name() + "˵�����㲻����Ľ�����ҵ��ˣ����ҹ�һ��ȥ��\n");
                return 1;
        }

        if (me->is_busy() || me->is_fighting())
        {
                write(ob->name() + "˵��������æ���ء�\n");
                return 1;
        }

        // write("����" + ob->name() + "��̹��ڡ���ѧ�����������ʡ�\n");

        if( query("potential", me)-query("learned_points", me)<20 )
        {
                write(ob->name()+"˵�������Ǳ�ܲ�����������ѧ�������ľ������ڡ�\n");
                return 1;
        }

        if( query("jing", me)<50 )
        {
                write(ob->name()+"˵����" + RANK_D->query_respect(me) + "����Ϣһ�°ɡ�\n");
                return 1;
        }

        if (me->query_skill("martial-cognize") > 800)
        {
                write(ob->name()+"˵����" + RANK_D->query_respect(me) +
                        "�ġ���ѧ�����������Ѿ��ܸ��ˣ����Ѳ���ָ�������һ�㡣\n");
                return 1;
        }
        write("������" + ob->name() + "��ָ�㣬�ԡ���ѧ�����������������һ�㡣\n");

        me->receive_damage("jing", 50);
        addn("learned_points", random(20), me);
        me->improve_skill("martial-cognize", me->query_int() * 10);
        me->start_busy(1 + random(2));
        return 1;
}

void reset()
{
        set("zihui_count", 1);
        set("douzhuan_count", 1);
}

/*
void unconcious()
{
        die();
}

*/
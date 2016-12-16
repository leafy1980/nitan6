#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

#define ZHIHUAN    "/clone/lonely/zhihuan"

mixed ask_zhihuan();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();

void create()
{
        object ob;
        set_name("������", ({ "wuya zi", "wuya", "zi" }));
        set("title", "��ң�ɿ�ɽ��ʦ");
        set("long", @LONG
��ǰ������ü�԰ף��������ж��ϡ���������
ң�ɿ�ɽ��ʦ�����ӡ�Ȼ���ƺ���Ⱦ�ؼ�����
�����㡣��Ȼ��ˣ���ü����Ȼ���ó����˵�
���Ȼ��һλ�������ε������ӡ��벻������
���䵽����ز��������������ϡ�
LONG );
        set("gender", "����");
        set("age", 95);
        set("class", "scholar");
        set("attitude", "friendly");
        set("shen_type", 1);

        set("str", 36);
        set("int", 41);
        set("con", 37);
        set("dex", 38);

        set("max_qi", 7500);
        set("max_jing", 5000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);
        set("combat_exp", 5000000);

        set_skill("force", 460);
        set_skill("xiaoyao-xinfa", 440);
        set_skill("beiming-shengong", 460);
        set_skill("xiaowuxiang", 460);
        set_skill("dodge", 460);
        set_skill("lingbo-weibu", 460);
        set_skill("feiyan-zoubi", 440);
        set_skill("strike", 460);
        set_skill("panyang-zhang", 440);
        set_skill("liuyang-zhang", 460);
        set_skill("hand", 460);
        set_skill("qingyun-shou", 440);
        set_skill("zhemei-shou", 460);
        set_skill("parry", 460);
        set_skill("sword", 440);
        set_skill("liuyue-jian", 440);
        set_skill("blade", 440);
        set_skill("ruyi-dao", 440);
        set_skill("literate", 460);
        set_skill("medical", 460);
        set_skill("xiaoyao-qixue", 460);
        set_skill("mathematics", 460);
        set_skill("qimen-wuxing", 460);
        set_skill("drawing",   460);
        set_skill("chuixiao-jifa", 460);
        set_skill("tanqin-jifa", 460);
        set_skill("chess", 460);
        set_skill("calligraphy", 460);
        set_skill("martial-cognize", 440);

        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("hand", "zhemei-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "zhemei-jian");
        map_skill("sword", "liuyue-jian");
        map_skill("blade", "ruyi-dao");
        map_skill("medical", "xiaoyao-qixue");

        prepare_skill("hand", "zhemei-shou");
        prepare_skill("strike", "liuyang-zhang");

        create_family("��ң��", 1, "��ɽ��ʦ");
        set("class", "taoist");

        set("inquiry", ([
                "���½���"   : (: ask_skill1 :),
                "��������"   : (: ask_skill2 :),
                "�����貨"   : (: ask_skill3 :),
                "������"     : (: ask_skill4 :),
                "���ʽ"     : (: ask_skill5 :),
                "��÷ʽ"     : (: ask_skill6 :),
                "��Ԩʽ"     : (: ask_skill7 :),
                "������"     : (: ask_skill8 :),
                "��ң���ɻ�" : (: ask_zhihuan :),
                "����������" : (: ask_zhihuan :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhe" :),
                (: perform_action, "hand.hai" :),
                (: perform_action, "hand.hua" :),
                (: perform_action, "dodge.ling" :),
                (: perform_action, "strike.huan" :),
                (: perform_action, "strike.zhong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();

        if (clonep())
        {
                ob = find_object(ZHIHUAN);
                if (! ob) ob = load_object(ZHIHUAN);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wear();
                }
        }

        carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if( query_temp("pass_zhenlong", ob) )
        {
                int btimes;
                delete_temp("pass_zhenlong", ob);
                if( query("betrayer/times", ob) )
                {
                        command("sigh");
                        command("say ���������磬��������Ե�ˣ�������"
                                "������ʦ��ȴ�������㡣");
                        return;
                }

                command("haha");
                command("say ���������磬��������Ե�ˣ���һ��Ҫ����Ϊ"
                        "ͽ��");
                btimes=query("betrayer/times", ob);
                command("recruit "+query("id", ob));
                set("betryer/times", btimes, ob);

                if( query("max_neili", ob)<500 )
                {
                        command("say ����������̫��š�Ҳ�ã����Ҵ������㣡");
                        set("max_neili", 500+random(100), ob);
                        if (ob->query_skill("force", 1) < 50)
                                ob->set_skill("force", 50 + random(10));

                        if (ob->query_skill("beiming-shengong", 1) < 50)
                                ob->set_skill("beiming-shengong", 50 + random(10));

                        message_vision(HIC "$N" HIC "�����İ���$n" HIC "������ϣ�˫��΢"
                                       "�գ����Ʋ�ס�Ĳ������������£����������ã��ã�\n" NOR,
                                       this_object(), ob);
                }

                return;
        }

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("xiaoyao-xinfa", 1) < 130 &&
            (int)ob->query_skill("xiaowuxiang", 1) < 130 &&
            (int)ob->query_skill("beiming-shengong", 1) < 130)
        {
                command("say ����ң�ɵı����ڹ����㶼û��ѧ��������̸ʲô��");
                return;
        }

        if ((int)ob->query_skill("force", 1) < 130)
        {
                command("say ����ң�ɵĵ��书���������ڹ������Ȱ��ڹ�������á�");
                return;
        }

        if ((int)ob->query_skill("dodge", 1) < 130)
        {
                command("say ��ң��ң�����Ṧ������ô���̸��ң��");
                return;
        }

        if (ob->query_int() < 40)
        {
                command("say ����ң�����ľ����򣬵���" + RANK_D->query_respect(ob) +
                        "�������ƺ����д���߰���");
                return;
        }

        if( query("combat_exp", ob)<500000 )
        {
                command("say ��ľ���Ҳ߯���˵㣬�úö���������˵�ɡ�");
                return;
        }

        command("haha");
        command("say �벻���������Ͼ�Ȼ�����˿��Լ̳�����ң�ɵ��²���");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyue-jian/liu", me) )
                return "�Ҳ����Ѿ��̹�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("liuyue-jian", 1) < 1)
                return "�������½��趼δ��ѧ�����������У�";

        if( query("family/gongji", me)<400 )
                return "����������ң���£�ȴ������Ϊ���������Ȳ�æ���㡣";

        if (me->query_skill("force") < 180)
                return "����ڹ�����㣬ѧ�������С�";

        if (me->query_skill("liuyue-jian", 1) < 120)
                return "������½�����δ�������ö���ϰ��ϰ��";

        message_vision(HIY "$n" HIY "���˵�ͷ���ӻ�������ȡ����һ��"
                       "���ף�ָ�����е�һ�ζ�\n$N" HIY "�����䷳��"
                       "ϸ˵���ã�$N" HIY "һ����һ�ߵ�ͷ��\n" NOR,
                       me, this_object());

        command("nod");
        command("say ���еı仯���ƺܷ�������ʵ���ѣ�����ϰ��ɡ�");
        tell_object(me, HIC "��ѧ���ˡ����½�������\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("liuyue-jian"))
                me->improve_skill("liuyue-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyue-jian/liu", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyue-jian/sheng", me) )
                return "�Ҳ����Ѿ��̹�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("liuyue-jian", 1) < 1)
                return "�������½��趼δ��ѧ�����������У�";

        if( query("family/gongji", me)<500 )
                return "����������ң���£�ȴ������Ϊ���������Ȳ�æ���㡣";

        if (me->query_skill("force") < 200)
                return "����ڹ�����㣬ѧ�������С�";

        if (me->query_skill("liuyue-jian", 1) < 140)
                return "������½�����δ�������ö���ϰ��ϰ��";

        message_vision(HIY "$n" HIY "Ц��Ц��������$N" HIY "���нӹ�"
                       "��������������ʾ���У�$N" HIY "����\nʽ������"
                       "������ӯ�鶯��ʵ��ǰ��ν�ţ���ʱ��������\n"
                       NOR, me, this_object());

        command("say ���еĹؼ������鶯���֣�����ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�������������\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("liuyue-jian"))
                me->improve_skill("liuyue-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyue-jian/sheng", 1, me);
        addn("family/gongji", -500, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/lingbo-weibu/ling", me) )
                return "�Ҳ����Ѿ��̹�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("lingbo-weibu", 1) < 1)
                return "�����貨΢����δ�����������������貨��";

        if( query("family/gongji", me)<600 )
                return "����������ң���£�ȴ������Ϊ���������Ȳ�æ���㡣";

        if (me->query_skill("force") < 180)
                return "����ڹ�����㣬ѧ�������С�";

        if (me->query_skill("lingbo-weibu", 1) < 120)
                return "����貨΢�����δ�������ö���ϰ��ϰ��";

        message_vision(HIY "$n" HIY "��$N" HIY "΢Ц�������벻��"
                       "��������Ṧ����������裬�ұ㴫\n�����"
                       "�������ˣ���˵��ֻ��$n" HIY "������������"
                       "�����������ʮ\n���Խ��貨΢����ͷ��βѸ"
                       "���ޱȵ�����һ�Ρ�����$n" HIY "��̬Ʈ\n��"
                       "��Ӱ���ҷɣ��������ң���ַ��ӵ����쾡��"
                       "��\n" NOR, me, this_object());

        command("haha");
        command("say �㿴���˶��٣�");
        tell_object(me, HIC "��ѧ���ˡ������貨����\n" NOR);

        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("lingbo-weibu"))
                me->improve_skill("lingbo-weibu", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingbo-weibu/ling", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/zhong", me) )
                return "�����Ҳ����Ѿ��̻�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "������ɽ�����ƶ�δ��ѧ�����������У�";

        if( query("family/gongji", me)<600 )
                return "����������ң���£�ȴ������Ϊ���������Ȳ�æ���㡣";

        if (me->query_skill("force") < 200)
                return "����ڹ�����㣬ѧ�������С�";

        if (me->query_skill("liuyang-zhang", 1) < 150)
                return "�����ɽ�����ƻ��δ��������ѧ������һ�С�";

        message_vision(HIY "$n" HIY "���˿�$N" HIY "��΢΢һЦ���漴"
                       "����˵�ͷ����$N" HIY "�������ߣ���\n���Ե���"
                       "ϸ˵���ã�$N" HIY "������ĵ�һЦ������������"
                       "��\n" NOR, me, this_object());

        command("haha");
        command("say �Ը���Щ���Ͻ���֮�ˣ�����������ʲ�����");
        tell_object(me, HIC "��ѧ���ˡ�����������\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/zhong", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/huan", me) )
                return "�����Ҳ����Ѿ��̻�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "������ɽ�����ƶ�δ��ѧ�����������У�";

        if( query("family/gongji", me)<900 )
                return "����������ң���£�ȴ������Ϊ���������Ȳ�æ���㡣";

        if (me->query_skill("force") < 200)
                return "����ڹ�����㣬ѧ�������С�";

        if (me->query_skill("liuyang-zhang", 1) < 130)
                return "�����ɽ�����ƻ��δ��������ѧ������һ�С�";

        message_vision(HIY "$n" HIY "΢΢һЦ�����������һ�ƣ�����"
                       "��$N" HIY "�����֮�ϣ�$N" HIY "����\n���죬"
                       "��ʱֻ��$n" HIY "����ԴԴ��������ӿ���룬��"
                       "������ע����\n�ڣ�ȫ�����ƿ�Ҫը�ѿ���������"
                       "��ʧɫ��\n" NOR, me, this_object());

        command("say �㶮����");
        tell_object(me, HIC "��ѧ���ˡ����ʽ����\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/huan", 1, me);
        addn("family/gongji", -900, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/zhe", me) )
                return "�����Ҳ����Ѿ��̻�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "������ң��÷�ֶ�δ��ѧ�����������У�";

        if( query("family/gongji", me)<400 )
                return "����������ң���£�ȴ������Ϊ���������Ȳ�æ���㡣";

        if (me->query_skill("force") < 120)
                return "����ڹ�����㣬ѧ�������С�";

        if (me->query_skill("zhemei-shou", 1) < 80)
                return "�����ң��÷�ֻ��δ��������ѧ������һ�С�";

        message_vision(HIY "$n" HIY "���˿�$N" HIY "��΢΢һЦ������"
                       "һ����Х������ң��÷������\n��Ϊһʽ������"
                       "����ӳ�����������ʵʵ��ɷ�Ǿ��ֱ����$N"
                       HIY "��\n�����ң�Ŀ�ɿڴ���\n" NOR, me,
                       this_object());

        command("nod");
        command("say ��ʽ������ˣ�ʣ�µľͿ����Լ��ˡ�");
        tell_object(me, HIC "��ѧ���ˡ���÷ʽ����\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/zhe", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/hai", me) )
                return "�����Ҳ����Ѿ��̻�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "������ң��÷�ֶ�δ��ѧ�����������У�";

        if( query("family/gongji", me)<900 )
                return "����������ң���£�ȴ������Ϊ���������Ȳ�æ���㡣";

        if (me->query_skill("force") < 200)
                return "����ڹ�����㣬ѧ�������С�";

        if (me->query_skill("zhemei-shou", 1) < 130)
                return "�����ң��÷�ֻ��δ��������ѧ������һ�С�";

        message_vision(HIY "$n" HIY "��$N" HIY "���˵�ͷ������Ҳ����"
                       "������������һ�Ӷ������ֳ���\n�磬���ƶ�ʱ��"
                       "����������Ӱ������ʵʵ�����ص��������Ǽ�����"
                       "\nס$N" HIY "����Ѩ����$n" HIY "����Ӱȴֻ��"
                       "һմ������δ��$N" HIY "���������\n֮�����"
                       "��ֻ���á��޿ɱ��⡱�������ݡ�\n" NOR, me,
                       this_object());

        command("nod");
        command("say ���б��纣֮��嫣�Ԩ֮�������Ҫ�ڼ���ϰ��");
        tell_object(me, HIC "��ѧ���ˡ���Ԩʽ����\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/hai", 1, me);
        addn("family/gongji", -900, me);
        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/hua", me) )
                return "���Լ���ȥ��ϰ�ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "������ң��÷�ֶ�δ��ѧ�����������У�";

        if( query("family/gongji", me)<2500 )
                return "����������ң���£�ȴ������Ϊ���������Ȳ�æ���㡣";

        if ((int)me->query_skill("beiming-shengong", 1) < 220)
                return "��ı�ڤ�񹦻���㣬ѧ�������С�";

        if (me->query_skill("zhemei-shou", 1) < 220)
                return "�����ң��÷�ֻ��δ��������ѧ������һ�С�";

        if( query("max_neili", me)<3500 )
                return "���������Ϊ������ǿ�����л�������������Ԫ��";

        message_vision(HIY "$n" HIY "��$N" HIY "΢΢һЦ��ģ����Ϊ��"
                       "����˵�������������������ʾ\nһ�飬�ܷ�����"
                       "��ȫ����������ˡ����������䣬ֻ��$n" HIY "��"
                       "��\n����������һ�ӣ���Ե��ʱ�������ϼ�⣬$n"
                       HIY "�������ģ�����\nϼ��Ҳ��֮������$n" HIY
                       "���Ŵ߶����������Ǽ䣬����ϼ�⾹����\n��죬"
                       "�ɺ�ת�ס����������ó�������ɫ��������һ����"
                       "������\n����֮�ϡ���ʱ��$n" HIY "һ���Ϻȣ�"
                       "��ɫ�ƾ���̱ų����ġ�ֻ��\n�á�������������"
                       "�ꡱ�������죬$N" HIY "�����ʯ�ھ���$n" HIY
                       "����ɫ\n�ƾ��ᴩ���߸���ڴֵ���Ѩ��\n" NOR,
                       me, this_object());

        command("haha");
        command("say ���������ұ��������������ղŲ�����һ�ɵ��������ˡ�");
        command("say �ǵ���������������������ʩչ���С�");
        tell_object(me, HIC "��ѧ���ˡ�����������\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("beiming-shengong"))
                me->improve_skill("beiming-shengong", 1500000);
        if (me->can_improve_skill("beiming-shengong"))
                me->improve_skill("beiming-shengong", 1500000);
        if (me->can_improve_skill("beiming-shengong"))
                me->improve_skill("beiming-shengong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/hua", 1, me);
        addn("family/gongji", -2500, me);
        return 1;
}

mixed ask_zhihuan()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "��ң��" )
                return "���ҹ�����";

        if( query("family/master_id", me) != query("id") )
                return "�㻹���䣡";

        if (me->query_skill("zhemei-shou", 1) < 200 &&
           me->query_skill("liuyang-zhang", 1) < 200)
                return "����ȥҲû�á�";

        ob = find_object(ZHIHUAN);
        if (! ob) ob = load_object(ZHIHUAN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "���ŵ����ﲻ������������";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "�������ˣ���ң���ɻ����ڲ��������С�";

                if( query("family/family_name", owner) == "��ң��" )
                        return "��ң���ɻ��������ڱ���"+query("name", owner)+
                               "���У���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "����Ϊ���µ����أ�������������������"+query("name", owner)+
                               "֮�֣���Ͽ�ȥ����ɱ�ˣ���ָ��ȡ������";
        }

        ob->move(this_object());
        message_vision(CYN "$N" CYN "΢΢һЦ������������ң���ɻ������ȥ��ϣ"
                       "���պ����ܼ̳��ҵ��²�����\n" NOR, this_object(), me);
        command("giveshenxianhuanto"+query("id", me));
        return 1;
}

int accept_ask(object me,string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "�Ų�ʽ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhemei-shou/jiubu",
                           "name"    : "�Ų�ʽ",
                           "sk1"     : "zhemei-shou",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "free"    : 1,
                           "gongxian": 1000,
                           "shen"    : 24000, ]));
                break;

        case "�ҷ�����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhemei-shou/hui",
                           "name"    : "�ҷ�����",
                           "sk1"     : "zhemei-shou",
                           "lv1"     : 150,
                           "sk2"     : "liuyang-zhang",
                           "lv2"     : 150,
                           "neili"   : 2000,
                           "gongxian": 800,
                           "shen"    : 20000, ]));
                break;

        case "���������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhemei-shou/duo",
                           "name"    : "���������",
                           "sk1"     : "zhemei-shou",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "free"    : 1,
                           "shen"    : 28000, ]));
                break;

        case "�׺�����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/baihong",
                           "name"    : "�׺�����",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 100,
                           "free"    : 1,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000,
                           "shen"    : 24000, ]));
                break;

        case "����ʽ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/jiutian",
                           "name"    : "����ʽ",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "free"    : 1,
                           "gongxian": 600,
                           "neili"   : 1400,
                           "shen"    : 28000, ]));
                break;

        case "�����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/po",
                           "name"    : "�����",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "free"    : 1,
                           "lv2"     : 120,
                           "gongxian": 600,
                           "neili"   : 1400,
                           "shen"    : 28000, ]));
                break;

        default:
                return 0;
        }
}
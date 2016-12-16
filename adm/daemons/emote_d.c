// This program is a part of NT MudLIB

#include <ansi.h>
#include <net/macros.h>
#include <emotion.h>

#define MSG             1
#define RAW             2
#define EMTMSG          "EMTMSG"

#define DATA            "/data/emotion/emotion"+ __SAVE_EXTENSION__

mapping emotions;

string help = @HELP
��Ϊ����ָ���ʹ��ָ�� semote �����ı���ָ���б���ʹ�÷�����
HELP;
varargs string do_emote(object me, string verb, string arg, int option);

int is_emote(string emt)
{
        return member_array(emt, keys(emotions)) != -1;
}

string multi_emote(object me, string arg, int option)
{
        string *args;

        if( option == RAW ) return arg;

        if( sizeof(args = explode(arg, " ")) > 1 )
                arg = do_emote(me, args[0], implode(args[1..], " "), RAW) || arg;
        else
                arg = do_emote(me, arg, 0, RAW) || arg;

        return arg;
}

varargs mixed do_emote(object me, string verb, string arg, int option)
{
        object you;
        string *emotion;
        string emotion_msg, your_name, argument;

        if( !me || !verb || !(emotion = emotions[verb]) ) return 0;

        if( !environment(me) )
                return 0;

        if( me->ban_say() ) return 0;

        if( query("doing", me) == "scheme" )
        {
                if( query("jing", me) < 100 )
                        return notify_fail("�����ڵľ��񲻼ã���һ����ɡ�\n");
                addn("jing", -50, me);
        }

        /* �޶��� && �޸������� */
        if ( !arg || !arg[0] )
                emotion_msg = emotion[NONE_ALL];

        /* ���� arg ��������� */
        else if( sscanf(arg, "%s %s", your_name, argument) == 2 )
        {
                int which;

                // ��鸴��Ŀ��
                if( sscanf(argument, "%d", which) && which > 1 && objectp(you = present(your_name+" "+which, me) || present(your_name+" "+which, environment(me))) )
                {
                        your_name += " "+which;
                        argument = trim(argument)[strlen(which+"")+1..];
                }

                if( !objectp(you) )
                        you =  present(your_name, environment(me)) || find_player(your_name);

                /* �ҵ����� && �и������� */
                if( objectp(you) && me->visible(you) )
                {
                        /* �������Լ� */
                        if( you == me )
                        {
                                emotion_msg = argument == "" ? emotion[ME_ALL] : emotion[ME_ALL_ARG];
                                you = 0;
                        }
                        else
                                emotion_msg = argument == "" ? emotion[YOU_ALL] : emotion[YOU_ALL_ARG];

                        emotion_msg = replace_string(emotion_msg, "$T", multi_emote(me, argument, option));
                }
                /* �޶��� && �и������� */
                else
                        emotion_msg = replace_string(emotion[NONE_ALL_ARG], "$T", multi_emote(me, arg, option));
        }
        /* �ҵ����� && �޸������� */
        else if( objectp(you = present(arg, environment(me)) || find_player(arg)) && me->visible(you) )
        {
                if( you == me )
                {
                        emotion_msg = emotion[ME_ALL];
                        you = 0;
                }
                else
                        emotion_msg = emotion[YOU_ALL];
        }

        /* �޶��� && �и������� */
        else
                emotion_msg = replace_string(emotion[NONE_ALL_ARG], "$T", multi_emote(me, arg, option));

        if( objectp(you) && interactive(you) && !wizardp(me) && me->visible(you) )
        {
                string *ignore = query("ignore", you);
                /*
                string no_emote, can_emote;

                no_emote=query("env/no_emote", target);
                // if (! wizardp(me) && userp(me) &&
                if (! wizardp(me) &&
                    query("couple/couple_id", me) != query("id", target) &&
                    (no_emote == "all" || no_emote == "ALL" ||
                    is_sub(query("id", me),no_emote)) )
                {
                        can_emote=query("env/can_emote", target);
                        if (! is_sub(query("id", me), can_emote))
                                tell_object(me, "����˲��������Ķ�����\n");
                }
                */
                if( arrayp(ignore) && member_array( me->query_id(1), ignore ) != -1 )
                {
                        tell(me, HIY+pnoun(2, me)+"Ŀǰ�޷���"+you->query_idname()+HIY"ʹ���κα���ָ�\n"NOR);
                        return 0;
                }
        }

        // ����ʹ�ô���
        emotion[USE] = count(emotion[USE],"+",1);

        if( option == MSG )
        {
                emotion_msg = replace_string(emotion_msg, "$ME", me->query_idname());

                if( objectp(you) && you->is_character() && me->visible(you) )
                        emotion_msg = replace_string(emotion_msg, "$YOU", you->query_idname());

                return emotion_msg+"\n";
        }
        else if( option == RAW )
        {
                if( objectp(you) )
                        emotion_msg = replace_string(emotion_msg, "$YOU", you->query_idname());

                return emotion_msg;
        }
        else
        {       
                if( !objectp(you) || same_environment(me, you) || !me->visible(you) )
                        msg(CYN+emotion_msg+"\n", me, you, 1, EMTMSG);
                else
                        msg(HIB"Զ��"NOR"-"+CYN+emotion_msg+"\n", me, you, 1, EMTMSG);
        }
        
        // Let NPC know we are doing emote on him.
        if (objectp(you)) you->relay_emote(me, verb);
        me->ban_say(1);

        return 1;
}

mapping query_emotions_fpointer()
{
        mapping m = allocate_mapping(sizeof(emotions));

        if( previous_object() != load_object(COMMAND_D) )
                return 0;

        foreach( string c in keys(emotions) )
        m[c] = (: do_emote($1, $(c), $2, $3) :);

        return m;
}

int set_emotion(string emotion, string *info)
{
        /*
                if( sizeof(info) != 8 || !is_command(previous_object()) ) return 0;
        */

        emotions[emotion] = info;

        return save_object(DATA);
}

string *query_emotions()
{
        return keys(emotions);
}

string *query_emotion(string m)
{
        return copy(emotions[m]);
}

int delete_emotion(string m)
{
        map_delete(emotions, m);
        return save_object(DATA);
}

private void create()
{
        if( clonep() ) return;

        emotions = allocate_mapping(0);

        if( !restore_object(DATA) )
        {
                log_file("static/emote","�޷�����浵��\n");
                destruct(this_object());
        }
}

void save()
{
        save_object(DATA);
}

int remove()
{
        return save_object(DATA);
}

string query_name()
{
        return "����ϵͳ(EMOTE_D)";
}
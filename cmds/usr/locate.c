 // by Tie@fy3
 
#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_DBASE;

#define MAX_DIS 7
#define MAX_ALT  2
#define MAX_DIR  8  

mapping *quests;
string locate_obj(object me, string strr);
object find_env(object ob);

int main(object me, string str)
{
        string output = "";
        object room;
        int    x0, y0, z0;
        
        room = environment(me);
        x0=query("coor/x", room);
        y0=query("coor/y", room);
        z0=query("coor/z", room);
   
        if (! x0 && ! y0 && ! z0 && base_name(room) != "/d/city/guangchang") 
                return notify_fail(WHT "这个地方不能使用locate指令，只有在有task发布的地区才可以使用！\n" NOR);
                
        if (! str) 
                return notify_fail("指令格式: locate <物品>\n");

/*
        if( query("reborn/times", me) )
                return notify_fail("转世玩家不可以做使命任务。\n");
*/

        if( query("qi", me)<30 )
                return notify_fail("你的气不足以查寻位置。\n");
                
        me->receive_damage("qi", 20);
        output = TASK_D->locate_ob(me, str);
        // if(output=="")
        // output = QUESTNPC_D->locate_obj(me, str);
        
        if (output == "")
                return notify_fail("确定不了" + str + "的大概位置。\n");
        
        write(output);
        return 1;
}  

object find_env(object ob)
{
        while(ob)
        {
                if( query("coor", ob) )
                        return ob;
                else 
                        ob = environment(ob);        
        }
        return ob;
}        

int help(object me)
{
        write(@HELP
指令格式: locate <物品> 
这个指令是用来得知使命物品的大概位置。
朝廷官员还可以用此指令查寻人物的大概位置。 
HELP
        );
        return 1;
} 

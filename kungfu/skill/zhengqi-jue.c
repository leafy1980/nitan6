// zhengqi-jue.c

inherit SKILL;

#include <ansi.h>

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int practice_skill(object me)
{
        return notify_fail("������ֻ�ܿ�ѧ(learn)����ߡ�\n");
}
void skill_improved(object me)
{
        tell_object(me, HIR "������ĵ���һ������֮����\n" NOR );
        addn("shen", 200, me);
}


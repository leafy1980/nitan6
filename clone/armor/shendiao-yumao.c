
#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(NOR + YEL"�����ë" NOR, ({ "shendiao yumao", "shendiao", "yumao" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "��");
                set("long", HIM "����һ��������ϵ���ë��Խһ��������\n" NOR);
                set("value", 35000);
                set("limit", ([
                        "exp"    :   100000,
                ]));
                set("armor_prop/dex", 1);
                set("armor_prop/int", 1);
                set("armor_prop/con", 1);
                set("armor_prop/str", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
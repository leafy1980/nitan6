#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "战衣之魂" NOR, ({"cloth soul2", "cloth", "soul2"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "这是一个战衣之魂。\n" NOR);
                set("unit", "个");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "cloth");
        set("status", 2);
        set("auto_load", 1);
        
        setup();
}


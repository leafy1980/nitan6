inherit ITEM;
inherit F_FOOD;


void create()
{
        set_name("素饼", ({"su bing","bing"}));
        set_weight(150);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一块松软的素饼。\n");
                set("unit", "块");
                set("value", 4);//很便宜，（基本食物都应该很便宜）.
		set("food_remaining", 10);
		set("food_supply", 60);
        }
}

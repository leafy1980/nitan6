// liuyun-jian.c
// 	nerd     Dec 9,1996 create

inherit SKILL;

mapping	* action=({
	([	"action":
        "$N使一招「仙人拱手」，手中$w幻一条疾光刺向$n的$l",
        "lian" :
        "$N使一招「仙人拱手」，手中$w幻一条疾光刺向左前方......",
                "jibie":7,
                "zhaoshi":"「仙人拱手」",
                "sen"  :8  ,
		"dodge":		20  ,
		"damage":		40   ,
		"damage_type":	"刺伤"
	]),
	([	"action":
        "$N一招「日月辉煌」，纵身飘开数尺，手中$w斩向$n的$l",
                "lian":
        "$N一招「日月辉煌」，纵身飘开数尺，手中$w大开大阙，挥洒飘逸......",
                "jiebie":30,
                "zhaoshi":"「日月辉煌」",
                "sen" : 10,
		"dodge":		30,
		"damage":		50 ,
		"damage_type":	"割伤"
	]),
	([	"action":
        "$N手中$w中宫直进，一式「白蛇吐信」对准$n的肩井穴刺出一剑",
                "lian":
        "$N手中$w中宫直进，一式「白蛇吐信」对准左前方斜刺一剑......",
                "jibie":40,
                "limb":"肩头",
                "zhaoshi":"白蛇吐信",
                "sen": 12,
		"dodge":30 ,
                "damage":50,
		"damage_type":	"刺伤"
	]),
	([	"action":
        "$N的$w凭空一指，一招「金针指南」，$w跳动着刺向$n的颈部.......",
                "lian":
        "$N的$w凭空一指，一招「金针指南」，$w跳动着刺向上方.......",
                "jibie":62,
                "zhaoshi":"「金针指南」",
                "sen": 10,
                "limb":"颈部",
		"dodge":		20,
		"damage":		70,
		"damage_type":	"刺伤"
	]),
    ([  "action":"$N左手捏了个剑诀，右手一招「二郎担山」，手中$w对准$n一点",
        "lian"  :"$N左手捏了个剑诀，右手一招「二郎担山」，手中$w轻轻一点。",
        "sen"   :4,
        "jibie" :20,
        "dodge" :40,
        "parry" :30,
        "zhaoshi":"「二郎担山」",
        "damage":5,
        "damage_type":"刺伤"    ]),
    ([  "action":"只见$N弓步上前，双手紧握$w，一招「凤凰展翼」，向$n的头部由下而上一撩",
        "lian"  :"$N一个弓步，使出一招「凤凰展翼」，手中$w往上一撩。",
        "sen"   :5,
        "jibie" :30,
        "dodge" :30,
        "parry" :30,
        "zhaoshi":"「凤凰展翼」",
        "damage":50,
        "damage_type":"割伤"    ]),
    ([  "action":"$N手拿$w，一招「猛虎摆尾」，向$n的$l飞速一击",
        "lian"  :"$N手拿$w，一招「猛虎摆尾」，快速击出。",
        "sen"   :5,
        "jibie" :40,
        "dodge" :10,
        "parry" :10,
        "zhaoshi":"「猛虎摆尾」",
        "damage":60,
        "damage_type":"割伤"    ]),
});

string *parry_msg = ({
    "$n使出一招「顺风扫叶」，手中的$v化作一条长虹，磕开了$N的$w。\n",
    "$n使出一招「左右提炉」，手中的$v化做漫天雪影，荡开了$N的$w。\n",
    "$n手中的$v一抖，一招「云雀飞空」，向$N拿$w的手腕削去。\n",
    "$n使出一招「跪跳扑虎」，$w直刺$N的双手。\n",
});

string *unarmed_parry_msg = ({
    "$n双手舞得密不透风，使出「顺风扫叶」，封住了$N的攻势。\n",
    "$n反手一招「左右提炉　梗芸�$N的这一招。\n",
    "$n使出一招「云雀飞空」，架住了$N的攻势。\n",
    "但见$n一招「跪跳扑虎」，迫得$N连连后退。\n",
});

int valid_learn(object me)
{
    return 1;
}

int valid_lian( object me )
{   
    object ob = me->query_temp("weapon");
    if ( !ob || (string)ob->query("weapon_type") != "sword" )
    {   
        write("你必须先找一把剑才能练剑法。\n");
        return 0;
    }
    return 1;
}

mapping query_action(int jibie)
{
	int i, size;

	size = sizeof( action );
	for ( i = 0; i < sizeof( action ); i++ )
		if ( action[ i ][ "jibie" ] > jibie )
		{
			size = i;
			break;
		}
    return action[ random( size ) ];
}

string query_parry_msg(object weapon)
{   
    if ( weapon )
        return parry_msg[random(sizeof(parry_msg))];
    else
        return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

string query_xiuwei_type() { return "sword"; }      
string query_weapon_type() { return "sword"; }

int query_dengji() { return 2; }

int query_youxiao_jibie() { return 9; }

int query_parry_ratio() { return 12; }

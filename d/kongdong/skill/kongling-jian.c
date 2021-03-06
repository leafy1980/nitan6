// kongling-jian.c
//  空灵剑法
inherit SKILL;

mapping *action = ({
    ([  "action":"$N一招「匪神之灵」，高举手中$w，向$n迎头一劈",
        "lian"  :"$N一招「匪神之灵」，手中$w凌空一劈。",
        "sen"   :3,
        "jibie" :5,
        "dodge" :20,
        "parry" :30,
        "zhaoshi":"「匪神之灵」",
        "damage":20,
        "damage_type":"割伤"    ]),
    ([  "action":"$N反手一招「匪机之微」，手中$w向$n的$l一抹",
        "lian"  :"$N手握$w，使出一招「匪机之微」向前顺势一抹。",
        "sen"   :10,
        "jibie" :10,
        "dodge" :10,
        "parry" :0,
        "zhaoshi":"「匪机之微」",
        "damage":40,
        "damage_type":"割伤" ]),
    ([  "action":"只见$N弓步上前，双手紧握$w，一招「乱山乔木」，向$n的头部由下而上一撩",
        "lian"  :"$N一个弓步，使出一招「乱山乔木」，手中$w往上一撩。",
        "sen"   :5,
        "jibie" :30,
        "dodge" :30,
        "parry" :30,
        "zhaoshi":"「乱山乔木」",
        "damage":50,
        "damage_type":"割伤"    ]),
    ([  "action":"$N手拿$w，一招「碧苔芳晖」，向$n的$l飞速一击",
        "lian"  :"$N手拿$w，一招「碧苔芳晖」，快速击出。",
        "sen"   :5,
        "jibie" :40,
        "dodge" :10,
        "parry" :10,
        "zhaoshi":"「碧苔芳晖」",
        "damage":60,
        "damage_type":"割伤"    ]),
	([	"action":
"$N使出「清风与归」，$w连挥剑光霍霍斩向$n的$l",
                "lian" :
"$N使出「清风与归」，$w连挥，只见剑光霍霍，煞是惊人......",
                "zhaoshi":"「清风与归」",
                "jibie":20,
                "sen" :12,
		"dodge":		30    ,
		"damage":		30,
		"damage_type":	"割伤"
	]),
	([	"action":
"$N一招「诵之思之」，纵身飘开数尺，手中$w斩向$n的$l",
                "lian":
"$N一招「诵之思之」，纵身飘开数尺，手中$w大开大阙，挥洒飘逸......",
                "jiebie":30,
                "zhaoshi":"「诵之思之」",
                "sen" : 10,
		"dodge":		30,
		"damage":		50 ,
		"damage_type":	"割伤"
	]),
	([	"action":
"$N纵身一跃，手中$w一招「终与俗违」，对准$n的气海斜斜刺出一剑",
                "lian" :
"$N纵身一跃，手中$w一招「终与俗违」，斜斜地向右下方刺去......",
                "jibie":50,
                "zhaoshi":"「终与俗违」",
                "sen"  :13,
		"dodge":40,
                "limb":"小腹",
                "damage":80,
		"damage_type":	"刺伤",
	]),
});

string *parry_msg = ({
        "$n使出一招「如将白云」，手中的$v化做漫天雪影，封住了全身。。\n",
        "$n使出「反手」诀，身形拔起，$w反手刺出，登时瓦解了$N的攻势。。\n",
        "$n使出一招「脱帽看诗」，手中的$v飘忽不定，照出点点剑花，晃得$N睁不开眼睛。。\n",
        "$n手中的$v一抖，一招「但知旦暮」，向$N的左肩反削上去。\n",
});

string *unarmed_parry_msg = ({
        "$n使出一招「如将白云」，封住了$N的攻势。\n",
        "$n反手一招「脱帽看诗」，整个人化做一团幻影。\n",
        "$n使出一招「但知旦暮」，化掌为剑，拍向$N左肩。。\n",
        "$n双掌一挥，内力逼出，迫得$N连连后退。\n",
});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 50 )
		return notify_fail("你的内力不够，没有办法练空灵剑法。\n");
	return 1;
}

int valid_lian( object me )
{
	object weapon;

	weapon = me->query_temp( "weapon" );
    if ( !weapon || weapon->query("weapon_type") != "sword" )
        return notify_fail("你必须先找一把剑才能练习剑法。\n");

	return 1;
}
string query_xiuwei_type() { return "sword";}      
string query_weapon_type() { return "sword"; }

int query_dengji() { return 3; } //1~~ 10

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

string query_zhaoshi( int jibie )
{
    int i;
    for ( i = 0; i < sizeof(action); i++ )
    {
        if ( action[ i ][ "jibie" ] >= jibie )
            return action[ i ][ "zhaoshi" ];
    }
    return "";
}

int query_youxiao_jibie() { return 12;}

int query_parry_ratio() { return 12; }

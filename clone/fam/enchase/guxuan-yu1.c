inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIB "������1����" NOR, ({"guxuan yu1", "yu1"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIB "����һ��ͨ���ɫ�Ĺ���ֻ�в���СĴָһ��Ĵ�С��ӵ�б�а�����ã�\n"
                                "�������ֳƺ���ͨ�������ڻ�����֮�ϣ�������а���֣�����������ӡ�\n" HIY
                                "ʹ�÷�ʽ����Ƕ�ڻ������ϣ��������� +1\n " NOR);
                set("value", 500000);
                set("enchase/name", "������1����");
                set("enchase/qy", 1);
                set("enchase/point", 1);
                set("enchase/type", "myheart");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );
        }
        setup();
}

int query_autoload()
{
        return 1;
}

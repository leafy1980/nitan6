inherit F_CLEAN_UP;

#include <ansi.h>
#include <net/dns.h>
int help(object me);

void create(){  seteuid(getuid());}
protected int check_multilogin();

int main(object me,string arg)
{
        string status;

        status = wizhood(me);
        if (!SECURITY_D->valid_grant(me, "(wizard)"))  
                 return 0; 
        if( me!=this_player(1) ||wiz_level(me) <wiz_level(status) )
                return notify_fail("��û��Ȩ��ʹ�����ָ�\n");
        if(arg)
                return help(me);
        return check_multilogin();
}

protected int check_multilogin()
{
        object *ob;
        string *ip_addr;
        string *temp;
        mixed *multy;
        int *count;
        string t;
        int i,j,s,s1;
        ob=users();
        s = sizeof(ob);
        ip_addr=allocate(s);
        ip_addr[0]=query_ip_number(ob[0]);
        temp=allocate(1);
        for (i=0;i<s;i++) {
                if( !environment(ob[i]) ) continue;
                temp[0]=query_ip_number(ob[i]);
                ip_addr=ip_addr-temp;
                ip_addr=ip_addr+temp;
        }
        ip_addr=ip_addr-({0});
        s1=sizeof(ip_addr);
        write ("----------------------------------------------------------------\n");
        count=allocate(s1);
        multy=allocate(s1);
        for (i=0;i<s1;i++)
                multy[i]=allocate(s);
        for (i=0;i<s;i++) {
                t=query_ip_number(ob[i]);
                for (j=0;j<s1;j++)
                        if (ip_addr[j]==t)  {
                                multy[j][count[j]]=query("id", ob[i]);
                                count[j]++;
                        }
        }
        for (i=0;i<s1;i++)
                multy[i]=multy[i]-({0});
        printf(BBLU HIW"%s\t\t%s    %s\t\t\t\t\n" NOR,"IP ��ַ","����", "�����ʶID");
        write ("----------------------------------------------------------------\n");
        for (i=0;i<s1;i++) {
                printf("%s\t%d\t",ip_addr[i],count[i]);
                for (j=0;j<sizeof(multy[i]);j++)
                        printf("%s ",multy[i][j]);
                printf("\n");
        }
        write ("----------------------------------------------------------------\n");
        printf ("���ڹ���"+ HIC +"%s"+ NOR +"����ң�" + HIC "%s" + NOR + "����ͬ��IP��ַ��\n",
                chinese_number(s), chinese_number(s1));

        return 1;
}

int help(object me)
{
        write(@TEXT

ָ���ʽ��ip

���ָ����������Ŀǰ��Ϸ�й��ж��ٸ���ͬ��IP�����
ָ�mcheck��

TEXT);
        return 1;
}

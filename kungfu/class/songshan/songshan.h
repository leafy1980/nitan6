int permit_recruit(object ob)
{
        command("say ��ɽ���ݲ����š�");
        return 0;           
        if( query("detach/��ɽ��", ob) || query("betrayer/��ɽ��", ob) )
        {
                command("say �㵱�궼�Ѿ��뿪����ɽ�ɣ��α���Ҫ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ������ɽ�����������ɣ���������ʦ֮ͽ��");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "��ɽ��" )
        {
                command("say ���Ȼ�Ѿ�������ʦָ�㣬���ú�ѧϰ����������ɽ��������");
                return 0;
        }

        return 1;
}
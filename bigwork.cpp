#include<stdio.h>
#include<stdlib.h>           
#include<string.h>           //ʹ�õ��ַ�����ʱ��Ҫʹ��
#include<conio.h>            //������ͨ������̨���������������������ĺ�������Ҫ��һЩ�û�ͨ�������̲����Ķ�Ӧ����
#include<windows.h>          //windowsͼ�ν������

FILE *fp1;               //ָ�� "����Ա��Ϣ" �ļ���ָ��
FILE *fp2;              //ָ�� "���ݿ�" ��ָ��
char administor[50],passward[50];//�����˻���������
struct note             //����һ����¼
{
	char time[9];      //��¼����ʱ��
	char xiangmu[20];  //��¼��Ŀ
	char money[16];     //��֧���
	char name[25];      //����������
};

//��Ҫ���ܺ�������

int Welcome();       //1.ע���¼����
int Menu();         //2.���˵�
int Outlook();      //3.�����ʾ
int Insert();       //4.��Ӱ����֧��Ϣ
int Output();       //5.������а����֧��Ϣ
int Delete();       //6.ɾ�������֧��Ϣ
int Search();       //7.��ѯ�����֧��Ϣ
int Modify();       //8.�޸İ����֧��Ϣ
int Change();       //9.�޸��˻�������
int Clean();        //10.������ݿ�

//������            
int main()
{
	system("color 50"); //�����ɫ
	if(Welcome())
	{
		while(1)
		{
			system("cls"); //��������
			Menu();
		}
	}
	return 0;
}



//��Ҫ���ܺ���


//1.ע���¼
int Welcome()
{
	fflush(stdin);  //������뻺������ͨ����Ϊ��ȷ����Ӱ���������ݶ�ȡ
    int i=0;
	int num=3;             //ͳ���������
	int sign=2;            //��Ǵ�������
	char F_administor[50],F_passward[50];//��ȡ�ļ��д�����˻�������
	printf("\t\t\t��ӭʹ������������֧����ϵͳ \n\n");
	printf("------------------------------�û���½����-----------------------------------\n\n");
	if((fp1=fopen("����Ա��Ϣ.txt","rb+"))==NULL)           //�˻��������������,����һ�����д˳���ʱ��ע��һ�����˻�
	{
		printf("\t��������һ��ʹ�ø�ϵͳ����ע��һ������Ա�˻�\n\n");
		printf("\t\t���������Ա������");
		scanf("%s",administor);
		getchar();
		printf("\n\t\t���������룺");
		while((passward[i]=getch())!='\r')
		{
		    if(i==0&&passward[i]=='\b')
		    {
		    }
		    else if(passward[i]=='\b')
		    {
		        printf("\b");
		        printf(" ");
		        printf("\b");
		        i--;
		    }
		    else
		    {
		        printf("*");
		        i++;
		    }
		}
		passward[i]='\0';
		if((fp1=fopen("����Ա��Ϣ.txt","wb+"))==NULL)
		{
			printf("\nע��ʧ�ܣ��������Ժ�����\n");
			return 0;
		}
		else
		{
			fprintf(fp1,"%50s%50s",administor,passward);//������Ա�˻�����������ļ�
			fclose(fp1);
			printf("\n\n\tע��ɹ����밴���������...");
			getch();
		}
		return 1;
	}
	fclose(fp1);
	if((fp1=fopen("����Ա��Ϣ.txt","rb+"))==NULL) //���ļ����ж�������˻��������Ƿ���ȷ
	{
		printf("�ļ���ʧ�ܣ����Ժ����ԣ���");
		return 0;
	}
	else
	{
		while(num)            //�жϴ������ͣ���������Ӧ��ʾ��3�δ������˳�ϵͳ
		{
		    i=0;
			if(sign==1)
			{
				printf("\n\n\t�ù���Ա�˻������ڣ�������%d���������\n\n",num);
			}
			else if(sign==0)
			{
				printf("\n\n\t�����������������%d���������\n\n",num);
			}
			printf("\n\t���������Ա������");
			scanf("%s",administor);
			getchar();
			printf("\n\t���������룺");
			while((passward[i]=getch())!='\r')
			{
			    if(i==0&&passward[i]=='\b')
			    {
			    }
			    else if(passward[i]=='\b')
			    {
			      printf("\b");
			      printf(" ");
			      printf("\b");
			      i--;
			    }
			    else
			    {
			        printf("*");
			        i++;
			    }
			}
			passward[i]='\0';
			fscanf(fp1,"%50s%50s",F_administor,F_passward);
			if(stricmp(F_administor,administor)==0)
			{
				if(strcmp(F_passward,passward)==0)
				{
				    fclose(fp1);
					return 1;
				}
				else
				{
					sign=0;
				}
			}
			else
			{
				sign=1;
			}
			num--;
		}
		printf("\n\t������������������3�Σ�ϵͳ����3����Զ��رգ�\n");
		fclose(fp1);
		Sleep(3000);
		return 0;
	}
}


//2.���˵�
int Menu()
{
	fflush(stdin);
	char choose;
	Outlook();       //����Outlook������ʾ�˵���
	scanf("%c",&choose);
	getchar();
	switch(choose)   //�ж�Ҫִ�еĲ���
	{
	case 'A': Insert(); break;
	case 'B': Output(); break;
	case 'C': Delete(); break;
	case 'D': Search(); break;
	case 'E': Modify(); break;
	case 'F': Change(); break;
	case 'G': Clean();  break;
	case 'Q': exit(0);  break;
	default:
		{
			Outlook();
			break;
		}
	}
	return 0;
}


//3.UI����
//����printf��������������������
int Outlook()               //��ʾ�˵���
{
	printf("                         ����������֧����ϵͳ\n\n");
	printf("------------------------------����ѡ�����-------------------------------------\n\n");
	printf("\t��ѡ���ܣ�\n\n");
	printf("\t\t[A] ��Ӱ����֧��Ϣ\n");
	printf("\t\t[B] ������а����֧��Ϣ\n");
	printf("\t\t[C] ɾ�������֧��Ϣ\n");
	printf("\t\t[D] ��ѯ�����֧��Ϣ\n");
	printf("\t\t[E] �޸İ����֧��Ϣ\n");
	printf("\t\t[F] �޸��˻�������\n");
	printf("\t\t[G] ������ݿ�\n");
	printf("\t\t[Q] ��ȫ�˳�\n\n");
	printf("\t��Ȩ���У��δ��\t����ؾ�\n\n");
	printf("\t��ѡ��Ҫ���еĲ�����");
	return 0;
}


//4.��Ӱ����֧��Ϣ
int Insert()
{
	system("cls");
	fflush(stdin);

	//�жϸ����ݿ��Ƿ����
    if((fp2=fopen("����������֧����ϵͳ.txt","rb+"))==NULL)
    {
        fp2=fopen("����������֧����ϵͳ.txt","wb+");
    }
    fclose(fp2);

	struct note one;

	//������ݿ����м�¼����׷�ӷ�ʽ��
	printf("                          ����������֧����ϵͳ\n\n");
	printf("------------------------------����¼�¼����-----------------------------------\n\n");
	printf("\t����¼�¼��\n");
	if((fp2=fopen("����������֧����ϵͳ.txt","ab+"))==NULL)
	{
		printf("\n\t�Բ��𣬲��ܴ򿪸����ݿ⣡");
		return 0;
	}

	 //����ʽ�������
	printf("\n\t\t�밴�˸�ʽ���뵱ǰ����(20180303)��");
	scanf("%s",one.time);
	getchar();
	while(strlen(one.time)!=8)
	{
	    printf("\t\t��ʽ����������������������(20180303):");
	    scanf("%s",one.time);
        getchar();
	}
	printf("\n\t\t�������¼��Ŀ(������20���ַ�)��");
	scanf("%s",one.xiangmu);
	getchar();
	printf("\n\t\t��������֧�����������ʾ���룬���ű�ʾ֧������");
	scanf("%s",one.money);
	getchar();
	printf("\n\t\t�����뾭��������(������25���ַ�)��");
	scanf("%s",one.name);
	getchar();
	fprintf(fp2,"%10s%25s%20s%30s",one.time,one.xiangmu,one.money,one.name);
	fclose(fp2);
	printf("\n\t�����ɹ����밴���������...");
	//getch();
	return 0;
}

//5.������а����֧��Ϣ
int Output()
{
    system("cls");
	fflush(stdin);

	//�жϸ����ݿ��Ƿ����
    if((fp2=fopen("����������֧����ϵͳ.txt","rb+"))==NULL)
    {
		printf("                          ����������֧����ϵͳ\n\n");
		printf("-------------------------------������ʾ----------------------------------------\n\n");
        printf("\t����δ¼���κμ�¼�����������������ѡ��.");
        getch();
        return 0;
    }

    double sum=0;            //ͳ���ܵ���֧���
    double sum1=0;           //ͳ���ܵ��������
    double sum2=0;           //ͳ���ܵ�֧�����
    double number;           //���ַ�����ʱת��Ϊ��������
	struct note one;
	if((fp2=fopen("����������֧����ϵͳ.txt","rb+"))==NULL)
	{
		printf("\t�Բ��𣬲��ܴ򿪸����ݿ⣡�밴���������...");
		getch();
		return 0;
	}
	printf("                          ����������֧����ϵͳ\n\n");
	printf("------------------------------�����¼������ʾ------------------------------\n\n");
	printf("  ʱ��                  ��Ŀ            ��֧                  ������\n");
	while(!feof(fp2))//ѭ�������¼
	{
	    fscanf(fp2,"%10s%25s%20s%30s",one.time,one.xiangmu,one.money,one.name);

        printf("%10s%20s%16s%23s\n\n",one.time,one.xiangmu,one.money,one.name);
        number=atof(one.money);
        if(number>0)
        {
            sum1+=number;
        }
        else
        {
            sum2+=number;
        }

	}
	//���ͳ��
	sum=sum1+sum2;
	printf("\n\t���������Ϊ��%.2lfԪ",sum1);
	printf("\n\t�����֧��Ϊ��%.2lfԪ",sum2);
	printf("\n\t������Ϊ��%.2lfԪ",sum);
	printf("\n\n\t�����ɹ����밴���������...");
    getch();
	fclose(fp2);
	return 0;
}

//6.ɾ�������֧��Ϣ
int Delete()
{
    system("cls");
	fflush(stdin);
	//�жϸ����ݿ��Ƿ����
    if((fp2=fopen("����������֧����ϵͳ.txt","rb+"))==NULL)
    {
		printf("                          ����������֧����ϵͳ\n\n");
		printf("-------------------------------������ʾ----------------------------------------\n\n");
        printf("����δ¼���κμ�¼�����������������ѡ��.");
        getch();
        return 0;
    }
	fclose(fp2);
	char choose;   //�ж��Ƿ����ɾ��
	int i=1;
	int num;
	long locate[100];//��Ǽ�¼���ļ��е�λ��
	char timekey[10];
	struct note one;
	printf("                          ����������֧����ϵͳ\n\n");
	printf("-------------------------------ɾ����¼����------------------------------------\n\n");
	printf("\tɾ����¼��\n");

	 //�������ڣ����ҵ���Ӧ��¼��
	printf("\n\t\t�밴�θ�ʽ����Ҫɾ����¼������(20180303)��");
	scanf("%s",timekey);
    getchar();
    while(strlen(timekey)!=8)
    {
        printf("\t\t��ʽ����������������������(20180303):");
        scanf("%s",timekey);
        getchar();
    }
	if((fp2=fopen("����������֧����ϵͳ.txt","rb+"))==NULL)
	{
		printf("\n\t�Բ��𣬲��ܴ򿪸����ݿ⣡�밴���������...");
		getch();
		return 0;
	}
	locate[0]=ftell(fp2);
	while(!feof(fp2))//ѭ������
	{
		fscanf(fp2,"%10s%25s%20s%30s",one.time,one.xiangmu,one.money,one.name);
		if(!strcmp(one.time,timekey))
		{
		    locate[i]=ftell(fp2);
			printf("<%d>\n  ʱ��                  ��Ŀ            ��֧                  ������\n",i);
			printf("%10s%20s%16s%23s",one.time,one.xiangmu,one.money,one.name);
			i++;
			printf("\n");
		}
	}
	if(i-1)
	{
		printf("\n\t���ҵ�%d�����������ļ�¼\n",i-1);
	    //ѡ��Ҫɾ���ļ�¼���
	    printf("\n\t\t��ѡ��Ҫɾ���ļ�¼��ţ�");
	    scanf("%d",&num);
	    getchar();
		//ȷ������
		printf("\n\tȷʵҪɾ���ü�¼��?<y/n>");
		scanf("%c",&choose);
		getchar();
		if((choose=='y')||(choose=='Y'))
		{
			fseek(fp2,locate[num-1],0);
			fprintf(fp2,"%10s%25s%20s%30s","","","","");
			fclose(fp2);
			if(i==2)
			{
				remove("����������֧����ϵͳ.txt");
			}
			printf("\t�����ɹ����밴���������...");
            getch();
			return 0;
		}
	}
	else
	{
		printf("\t�Բ������ݿ����޴˼�¼���밴���������...");
		getch();
	}
	fclose(fp2);
	return 0;
}


//7.��ѯ�����֧��Ϣ
int Search()
{
    system("cls");
	fflush(stdin);

	//�жϸ����ݿ��Ƿ����
    if((fp2=fopen("����������֧����ϵͳ.txt","rb+"))==NULL)
    {
		printf("                          ����������֧����ϵͳ\n\n");
		printf("-------------------------------������ʾ----------------------------------------\n\n");
        printf("\t\t����δ¼���κμ�¼�����������������ѡ��.");
        getch();
        return 0;
    }
	fclose(fp2);

	int num=0;         //���ڼ�¼���м�����������ļ�¼
	char timekey[10];
	struct note one;

	//����ʱ����Ҽ�¼
	printf("                          ����������֧����ϵͳ\n\n");
	printf("------------------------------���Ҽ�¼����-------------------------------------\n\n");
	printf("\t���Ҽ�¼��\n");
    printf("\n\t\t�밴�θ�ʽ����Ҫ���ҵļ�¼������(20180303)��");
    scanf("%s",timekey);
    getchar();
    while(strlen(timekey)!=8)
    {
        printf("\n\t\t��ʽ����������������������(20180303):");
        scanf("%s",timekey);
        getchar();
    }
	if((fp2=fopen("����������֧����ϵͳ.txt","rb+"))==NULL)
	{
		printf("\n\t�Բ��𣬲��ܴ򿪸����ݿ⣡");
		return 0;
	}
	while(!feof(fp2))  //ѭ������
	{
		fscanf(fp2,"%10s%25s%20s%30s",one.time,one.xiangmu,one.money,one.name);
		if(!strcmp(one.time,timekey))
		{
			printf("\n  ʱ��                  ��Ŀ            ��֧                  ������\n");
			printf("%10s%20s%16s%23s",one.time,one.xiangmu,one.money,one.name);
			num++;
			printf("\n");
		}
	}
	if(!num)
	{
		printf("\n\t�Բ������ݿ����޴˼�¼���밴���������...");
		getch();
	}
	else
	{
	  printf("\n\n\t���ҵ�%d�����������ļ�¼",num);
	  printf(",�����������...");
	  getch();
	}
	fclose(fp2);
	return 0;
}


//8.�޸İ����֧��Ϣ
int Modify()
{
    system("cls");
	fflush(stdin);

	//�ж����ݿ����Ƿ��м�¼
    if((fp2=fopen("����������֧����ϵͳ.txt","rb+"))==NULL)
    {
		printf("                          ����������֧����ϵͳ\n\n");
		printf("-------------------------------������ʾ----------------------------------------\n\n");
        printf("\t����δ¼���κμ�¼�����������������ѡ��.");
        getch();
        return 0;
    }
	fclose(fp2);
    int i=1;     //��Ǽ�¼����
	long locate[100];//��Ǽ�¼��λ��
	char timekey[10];
	struct note one;
	printf("                          ����������֧����ϵͳ\n\n");
	printf("-------------------------------�޸ļ�¼����------------------------------------\n\n");
	printf("\t�޸ļ�¼��\n");

	 //�������ڣ����ҵ���Ӧ��¼��
	printf("\n\t\t�밴�˸�ʽ����Ҫ�޸ļ�¼������(20180303)��");
	scanf("%s",timekey);
    getchar();
    while(strlen(timekey)!=8)
    {
        printf("\t\t��ʽ����������������������(20180303):");
        scanf("%s",timekey);
        getchar();
    }
	if((fp2=fopen("����������֧����ϵͳ.txt","rb+"))==NULL)
	{
		printf("\t�Բ��𣬲��ܴ򿪸����ݿ⣡");
		return 0;
	}
	locate[0]=ftell(fp2);
	while(!feof(fp2))          //ѭ������
	{
		fscanf(fp2,"%10s%25s%20s%30s",one.time,one.xiangmu,one.money,one.name);
		if(!strcmp(one.time,timekey))
		{
		    locate[i]=ftell(fp2);
			printf("<%d>\n  ʱ��                  ��Ŀ            ��֧                  ������\n",i);
			printf("%10s%20s%16s%23s",one.time,one.xiangmu,one.money,one.name);
			printf("\n");
			i++;
		}
	}
	if(i-1)
	{
		printf("\n\t���ҵ�%d�����������ļ�¼\n",i-1);
	    //ѡ��Ҫ�޸ĵļ�¼
	    printf("\n\t��ѡ��Ҫ�޸ĵĵļ�¼��ţ��˳�������0����");
	    scanf("%d",&i);
	    getchar();
		if(i==0)
		{
			return 0;
		}
        fseek(fp2,locate[i-1],0);

	    //����������
	    printf("\n\t\t�밴�θ�ʽ����������(20180303)��");
        scanf("%s",timekey);
        getchar();
        while(strlen(timekey)!=8)
        {
            printf("\t\t��ʽ������������������������(20180303):");
            scanf("%s",timekey);
            getchar();
        }
		printf("\n\t\t�������¼�¼��Ŀ(������20���ַ�)��");
		scanf("%s",one.xiangmu);
		getchar();
		printf("\n\t\t����������֧�����������ʾ���룬���ű�ʾ֧������");
		scanf("%s",one.money);
		getchar();
		printf("\n\t\t�������¾���������(������25���ַ�)��");
		scanf("%s",one.name);
		getchar();
		fprintf(fp2,"%10s%25s%20s%30s",timekey,one.xiangmu,one.money,one.name);
		printf("\n\t�����ɹ����밴���������...");
        getch();
	}
	else
	{
	    printf("\n\t�Բ������ݿ����޴˼�¼���밴���������...");
		getch();
	}
	fclose(fp2);
	return 0;
}





//9.�޸��˻�������
int Change()
{
    system("cls");
	fflush(stdin);
	//�ж��ļ��Ƿ����
    if((fp1=fopen("����Ա��Ϣ.txt","rb+"))==NULL)
    {
		printf("                          ����������֧����ϵͳ\n\n");
		printf("-------------------------------������ʾ----------------------------------------\n\n");
        printf("\t�ļ���ʧ�ܣ����Ժ����ԡ�");
        Sleep(3000);
        return 0;
    }

  //����ҵ��ļ���ִ��������޸����
  int i=0;
  char F_administor[40],F_passward[50];//�ļ��д������Ϣ
  char administor[40],passward[50];    //�û��������Ϣ
  printf("                          ����������֧����ϵͳ\n\n");
  printf("-------------------------------�����޸Ľ���------------------------------------\n\n");
  printf("\t�����޸�:\n");
  printf("\n\t\t������ԭ����Ա������");//����ԭ��Ϣ
  scanf("%s",administor);
  getchar();
  printf("\n\t\t������ԭ���룺");
  while((passward[i]=getch())!='\r')
  {
      if(i==0&&passward[i]=='\b')
      {
      }
      else if(passward[i]=='\b')
      {
          printf("\b");
          printf(" ");
          printf("\b");
          i--;
          }
          else
          {
              printf("*");
              i++;
          }
  }
  passward[i]='\0';
  fscanf(fp1,"%40s%50s",F_administor,F_passward);
  if((strcmp(F_administor,administor)==0)&&(strcmp(F_passward,passward)==0))//�ж�������û����������Ƿ���ȷ
  {
      fclose(fp1);
      i=0;
      if((fp1=fopen("����Ա��Ϣ.txt","wb+"))==NULL)
      {
          printf("\n\t����ʧ�ܣ������������...");
          getch();
      }
      else
      {
		  //��������Ϣ
          printf("\n\n\n\t\t�������¹���Ա���ƣ�");
          scanf("%s",administor);
          getchar();
          printf("\n\t\t�����������룺");
          while((passward[i]=getch())!='\r')
          {
              if(i==0&&passward[i]=='\b')
              {
              }
              else if(passward[i]=='\b')
              {
                  printf("\b");
                  printf(" ");
                  printf("\b");
                  i--;
              }
              else
              {
                  printf("*");
                  i++;
              }
          }
          passward[i]='\0';
          fprintf(fp1,"%40s%50s",administor,passward);//���µĹ���Ա�˻�����������ļ�
          fclose(fp1);
          printf("\n\n\t�����ɹ����밴���������...");
          getch();
      }
  }
  else
  {
     printf("\n\n\t����ʧ�ܣ������������...");
     getch();
  }
  return 0;
}

//10.������ݿ⺯��
int Clean()
{
	system("cls");
	fflush(stdin);
	char choose;     //�ж��Ƿ�ɾ��
	printf("                          ����������֧����ϵͳ\n\n");
	printf("-------------------------------������ݿ����----------------------------------\n\n");
	printf("\t������ݿ�:\n\n");
	printf("\t\t���ݿ���պ��޷��ָ�����ȷ��ô��<Y/�����ַ�����>");
	scanf("%c",&choose);
	if((fp2=fopen("����������֧����ϵͳ.txt","rb+"))==NULL)
	{
	    printf("\n\t��δ��¼�κ����ݣ������������...");
	    getch();
	    return 0;
	}
	fclose(fp2);
	if(choose=='Y')
	{
		if(remove("����������֧����ϵͳ.txt"))
		{
			printf("\n\t����ʧ�ܣ������������...");
			getch();
		}
		else
		{
			printf("\n\t�����ɹ��������������...");
			getch();
		}
	}
	return 0;
}

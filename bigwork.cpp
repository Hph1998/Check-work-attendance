#include<stdio.h>
#include<stdlib.h>           
#include<string.h>           //使用到字符数组时需要使用
#include<conio.h>            //定义了通过控制台进行数据输入和数据输出的函数，主要是一些用户通过按键盘产生的对应操作
#include<windows.h>          //windows图形界面相关

FILE *fp1;               //指向 "管理员信息" 文件的指针
FILE *fp2;              //指向 "数据库" 的指针
char administor[50],passward[50];//储存账户名和密码
struct note             //定义一条记录
{
	char time[9];      //记录创建时间
	char xiangmu[20];  //记录项目
	char money[16];     //收支情况
	char name[25];      //经办人姓名
};

//主要功能函数声明

int Welcome();       //1.注册登录界面
int Menu();         //2.主菜单
int Outlook();      //3.外观显示
int Insert();       //4.添加班费收支信息
int Output();       //5.浏览所有班费收支信息
int Delete();       //6.删除班费收支信息
int Search();       //7.查询班费收支信息
int Modify();       //8.修改班费收支信息
int Change();       //9.修改账户和密码
int Clean();        //10.清空数据库

//主函数            
int main()
{
	system("color 50"); //软件颜色
	if(Welcome())
	{
		while(1)
		{
			system("cls"); //用于清屏
			Menu();
		}
	}
	return 0;
}



//主要功能函数


//1.注册登录
int Welcome()
{
	fflush(stdin);  //清空输入缓冲区，通常是为了确保不影响后面的数据读取
    int i=0;
	int num=3;             //统计输入次数
	int sign=2;            //标记错误类型
	char F_administor[50],F_passward[50];//读取文件中储存的账户和密码
	printf("\t\t\t欢迎使用软工三班班费收支管理系统 \n\n");
	printf("------------------------------用户登陆界面-----------------------------------\n\n");
	if((fp1=fopen("管理员信息.txt","rb+"))==NULL)           //账户和密码输入界面,当第一次运行此程序时需注册一个新账户
	{
		printf("\t这是您第一次使用该系统，请注册一个管理员账户\n\n");
		printf("\t\t请输入管理员姓名：");
		scanf("%s",administor);
		getchar();
		printf("\n\t\t请输入密码：");
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
		if((fp1=fopen("管理员信息.txt","wb+"))==NULL)
		{
			printf("\n注册失败！！！请稍后重试\n");
			return 0;
		}
		else
		{
			fprintf(fp1,"%50s%50s",administor,passward);//将管理员账户和密码存入文件
			fclose(fp1);
			printf("\n\n\t注册成功，请按任意键继续...");
			getch();
		}
		return 1;
	}
	fclose(fp1);
	if((fp1=fopen("管理员信息.txt","rb+"))==NULL) //打开文件，判断输入的账户和密码是否正确
	{
		printf("文件打开失败，请稍后重试！！");
		return 0;
	}
	else
	{
		while(num)            //判断错误类型，并给出相应提示，3次错误则退出系统
		{
		    i=0;
			if(sign==1)
			{
				printf("\n\n\t该管理员账户不存在，您还有%d次输入机会\n\n",num);
			}
			else if(sign==0)
			{
				printf("\n\n\t密码输入错误，您还有%d次输入机会\n\n",num);
			}
			printf("\n\t请输入管理员姓名：");
			scanf("%s",administor);
			getchar();
			printf("\n\t请输入密码：");
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
		printf("\n\t您的输入错误次数超过3次，系统将在3秒后自动关闭！\n");
		fclose(fp1);
		Sleep(3000);
		return 0;
	}
}


//2.主菜单
int Menu()
{
	fflush(stdin);
	char choose;
	Outlook();       //调用Outlook函数显示菜单项
	scanf("%c",&choose);
	getchar();
	switch(choose)   //判断要执行的操作
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


//3.UI界面
//除了printf出来，还有其他方法？
int Outlook()               //显示菜单项
{
	printf("                         软工三班班费收支管理系统\n\n");
	printf("------------------------------功能选择界面-------------------------------------\n\n");
	printf("\t请选则功能：\n\n");
	printf("\t\t[A] 添加班费收支信息\n");
	printf("\t\t[B] 浏览所有班费收支信息\n");
	printf("\t\t[C] 删除班费收支信息\n");
	printf("\t\t[D] 查询班费收支信息\n");
	printf("\t\t[E] 修改班费收支信息\n");
	printf("\t\t[F] 修改账户和密码\n");
	printf("\t\t[G] 清空数据库\n");
	printf("\t\t[Q] 安全退出\n\n");
	printf("\t版权所有：何大大\t盗版必究\n\n");
	printf("\t请选着要进行的操作：");
	return 0;
}


//4.添加班费收支信息
int Insert()
{
	system("cls");
	fflush(stdin);

	//判断该数据库是否存在
    if((fp2=fopen("软工三班班费收支管理系统.txt","rb+"))==NULL)
    {
        fp2=fopen("软工三班班费收支管理系统.txt","wb+");
    }
    fclose(fp2);

	struct note one;

	//如果数据库里有记录则以追加方式打开
	printf("                          软工三班班费收支管理系统\n\n");
	printf("------------------------------添加新记录界面-----------------------------------\n\n");
	printf("\t添加新记录：\n");
	if((fp2=fopen("软工三班班费收支管理系统.txt","ab+"))==NULL)
	{
		printf("\n\t对不起，不能打开该数据库！");
		return 0;
	}

	 //按格式添加数据
	printf("\n\t\t请按此格式输入当前日期(20180303)：");
	scanf("%s",one.time);
	getchar();
	while(strlen(one.time)!=8)
	{
	    printf("\t\t格式输入有误，请重新输入日期(20180303):");
	    scanf("%s",one.time);
        getchar();
	}
	printf("\n\t\t请输入记录项目(不多于20个字符)：");
	scanf("%s",one.xiangmu);
	getchar();
	printf("\n\t\t请输入收支情况（正数表示收入，负号表示支出）：");
	scanf("%s",one.money);
	getchar();
	printf("\n\t\t请输入经办人姓名(不多于25个字符)：");
	scanf("%s",one.name);
	getchar();
	fprintf(fp2,"%10s%25s%20s%30s",one.time,one.xiangmu,one.money,one.name);
	fclose(fp2);
	printf("\n\t操作成功，请按任意键继续...");
	//getch();
	return 0;
}

//5.浏览所有班费收支信息
int Output()
{
    system("cls");
	fflush(stdin);

	//判断该数据库是否存在
    if((fp2=fopen("软工三班班费收支管理系统.txt","rb+"))==NULL)
    {
		printf("                          软工三班班费收支管理系统\n\n");
		printf("-------------------------------错误提示----------------------------------------\n\n");
        printf("\t您尚未录入任何记录，按任意键返回重新选择.");
        getch();
        return 0;
    }

    double sum=0;            //统计总的收支情况
    double sum1=0;           //统计总的收入情况
    double sum2=0;           //统计总的支出情况
    double number;           //将字符串临时转化为整形数据
	struct note one;
	if((fp2=fopen("软工三班班费收支管理系统.txt","rb+"))==NULL)
	{
		printf("\t对不起，不能打开该数据库！请按任意键继续...");
		getch();
		return 0;
	}
	printf("                          软工三班班费收支管理系统\n\n");
	printf("------------------------------财务记录总账显示------------------------------\n\n");
	printf("  时间                  项目            收支                  经办人\n");
	while(!feof(fp2))//循环输出记录
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
	//班费统计
	sum=sum1+sum2;
	printf("\n\t班费总收入为：%.2lf元",sum1);
	printf("\n\t班费总支出为：%.2lf元",sum2);
	printf("\n\t班费余额为：%.2lf元",sum);
	printf("\n\n\t操作成功，请按任意键继续...");
    getch();
	fclose(fp2);
	return 0;
}

//6.删除班费收支信息
int Delete()
{
    system("cls");
	fflush(stdin);
	//判断该数据库是否存在
    if((fp2=fopen("软工三班班费收支管理系统.txt","rb+"))==NULL)
    {
		printf("                          软工三班班费收支管理系统\n\n");
		printf("-------------------------------错误提示----------------------------------------\n\n");
        printf("您尚未录入任何记录，按任意键返回重新选择.");
        getch();
        return 0;
    }
	fclose(fp2);
	char choose;   //判断是否决定删除
	int i=1;
	int num;
	long locate[100];//标记记录在文件中的位置
	char timekey[10];
	struct note one;
	printf("                          软工三班班费收支管理系统\n\n");
	printf("-------------------------------删除记录界面------------------------------------\n\n");
	printf("\t删除记录：\n");

	 //输入日期，查找到相应记录项
	printf("\n\t\t请按次格式输入要删除记录的日期(20180303)：");
	scanf("%s",timekey);
    getchar();
    while(strlen(timekey)!=8)
    {
        printf("\t\t格式输入有误，请重新输入日期(20180303):");
        scanf("%s",timekey);
        getchar();
    }
	if((fp2=fopen("软工三班班费收支管理系统.txt","rb+"))==NULL)
	{
		printf("\n\t对不起，不能打开该数据库！请按任意键继续...");
		getch();
		return 0;
	}
	locate[0]=ftell(fp2);
	while(!feof(fp2))//循环查找
	{
		fscanf(fp2,"%10s%25s%20s%30s",one.time,one.xiangmu,one.money,one.name);
		if(!strcmp(one.time,timekey))
		{
		    locate[i]=ftell(fp2);
			printf("<%d>\n  时间                  项目            收支                  经办人\n",i);
			printf("%10s%20s%16s%23s",one.time,one.xiangmu,one.money,one.name);
			i++;
			printf("\n");
		}
	}
	if(i-1)
	{
		printf("\n\t共找到%d条符合条件的记录\n",i-1);
	    //选择要删除的记录编号
	    printf("\n\t\t请选择要删除的记录编号：");
	    scanf("%d",&num);
	    getchar();
		//确定界面
		printf("\n\t确实要删除该记录吗?<y/n>");
		scanf("%c",&choose);
		getchar();
		if((choose=='y')||(choose=='Y'))
		{
			fseek(fp2,locate[num-1],0);
			fprintf(fp2,"%10s%25s%20s%30s","","","","");
			fclose(fp2);
			if(i==2)
			{
				remove("软工三班班费收支管理系统.txt");
			}
			printf("\t操作成功，请按任意键继续...");
            getch();
			return 0;
		}
	}
	else
	{
		printf("\t对不起，数据库中无此记录！请按任意键继续...");
		getch();
	}
	fclose(fp2);
	return 0;
}


//7.查询班费收支信息
int Search()
{
    system("cls");
	fflush(stdin);

	//判断该数据库是否存在
    if((fp2=fopen("软工三班班费收支管理系统.txt","rb+"))==NULL)
    {
		printf("                          软工三班班费收支管理系统\n\n");
		printf("-------------------------------错误提示----------------------------------------\n\n");
        printf("\t\t您尚未录入任何记录，按任意键返回重新选择.");
        getch();
        return 0;
    }
	fclose(fp2);

	int num=0;         //用于记录共有几项符合条件的记录
	char timekey[10];
	struct note one;

	//根据时间查找记录
	printf("                          软工三班班费收支管理系统\n\n");
	printf("------------------------------查找记录界面-------------------------------------\n\n");
	printf("\t查找记录：\n");
    printf("\n\t\t请按次格式输入要查找的记录的日期(20180303)：");
    scanf("%s",timekey);
    getchar();
    while(strlen(timekey)!=8)
    {
        printf("\n\t\t格式输入有误，请重新输入日期(20180303):");
        scanf("%s",timekey);
        getchar();
    }
	if((fp2=fopen("软工三班班费收支管理系统.txt","rb+"))==NULL)
	{
		printf("\n\t对不起，不能打开该数据库！");
		return 0;
	}
	while(!feof(fp2))  //循环查找
	{
		fscanf(fp2,"%10s%25s%20s%30s",one.time,one.xiangmu,one.money,one.name);
		if(!strcmp(one.time,timekey))
		{
			printf("\n  时间                  项目            收支                  经办人\n");
			printf("%10s%20s%16s%23s",one.time,one.xiangmu,one.money,one.name);
			num++;
			printf("\n");
		}
	}
	if(!num)
	{
		printf("\n\t对不起，数据库中无此记录！请按任意键继续...");
		getch();
	}
	else
	{
	  printf("\n\n\t共找到%d条符合条件的记录",num);
	  printf(",按任意键继续...");
	  getch();
	}
	fclose(fp2);
	return 0;
}


//8.修改班费收支信息
int Modify()
{
    system("cls");
	fflush(stdin);

	//判断数据库里是否有记录
    if((fp2=fopen("软工三班班费收支管理系统.txt","rb+"))==NULL)
    {
		printf("                          软工三班班费收支管理系统\n\n");
		printf("-------------------------------错误提示----------------------------------------\n\n");
        printf("\t您尚未录入任何记录，按任意键返回重新选择.");
        getch();
        return 0;
    }
	fclose(fp2);
    int i=1;     //标记记录条数
	long locate[100];//标记记录的位置
	char timekey[10];
	struct note one;
	printf("                          软工三班班费收支管理系统\n\n");
	printf("-------------------------------修改记录界面------------------------------------\n\n");
	printf("\t修改记录：\n");

	 //输入日期，查找到相应记录项
	printf("\n\t\t请按此格式输入要修改记录的日期(20180303)：");
	scanf("%s",timekey);
    getchar();
    while(strlen(timekey)!=8)
    {
        printf("\t\t格式输入有误，请重新输入日期(20180303):");
        scanf("%s",timekey);
        getchar();
    }
	if((fp2=fopen("软工三班班费收支管理系统.txt","rb+"))==NULL)
	{
		printf("\t对不起，不能打开该数据库！");
		return 0;
	}
	locate[0]=ftell(fp2);
	while(!feof(fp2))          //循环查找
	{
		fscanf(fp2,"%10s%25s%20s%30s",one.time,one.xiangmu,one.money,one.name);
		if(!strcmp(one.time,timekey))
		{
		    locate[i]=ftell(fp2);
			printf("<%d>\n  时间                  项目            收支                  经办人\n",i);
			printf("%10s%20s%16s%23s",one.time,one.xiangmu,one.money,one.name);
			printf("\n");
			i++;
		}
	}
	if(i-1)
	{
		printf("\n\t共找到%d条符合条件的记录\n",i-1);
	    //选择要修改的记录
	    printf("\n\t请选择要修改的的记录编号（退出请输入0）：");
	    scanf("%d",&i);
	    getchar();
		if(i==0)
		{
			return 0;
		}
        fseek(fp2,locate[i-1],0);

	    //输入新数据
	    printf("\n\t\t请按次格式输入新日期(20180303)：");
        scanf("%s",timekey);
        getchar();
        while(strlen(timekey)!=8)
        {
            printf("\t\t格式输入有误，请重新输入新日期(20180303):");
            scanf("%s",timekey);
            getchar();
        }
		printf("\n\t\t请输入新记录项目(不多于20个字符)：");
		scanf("%s",one.xiangmu);
		getchar();
		printf("\n\t\t请输入新收支情况（正数表示收入，负号表示支出）：");
		scanf("%s",one.money);
		getchar();
		printf("\n\t\t请输入新经办人姓名(不多于25个字符)：");
		scanf("%s",one.name);
		getchar();
		fprintf(fp2,"%10s%25s%20s%30s",timekey,one.xiangmu,one.money,one.name);
		printf("\n\t操作成功，请按任意键继续...");
        getch();
	}
	else
	{
	    printf("\n\t对不起，数据库中无此记录！请按任意键继续...");
		getch();
	}
	fclose(fp2);
	return 0;
}





//9.修改账户和密码
int Change()
{
    system("cls");
	fflush(stdin);
	//判断文件是否存在
    if((fp1=fopen("管理员信息.txt","rb+"))==NULL)
    {
		printf("                          软工三班班费收支管理系统\n\n");
		printf("-------------------------------错误提示----------------------------------------\n\n");
        printf("\t文件打开失败，请稍后重试。");
        Sleep(3000);
        return 0;
    }

  //如果找到文件则执行下面的修改语句
  int i=0;
  char F_administor[40],F_passward[50];//文件中储存的信息
  char administor[40],passward[50];    //用户输入的信息
  printf("                          软工三班班费收支管理系统\n\n");
  printf("-------------------------------密码修改界面------------------------------------\n\n");
  printf("\t密码修改:\n");
  printf("\n\t\t请输入原管理员姓名：");//输入原信息
  scanf("%s",administor);
  getchar();
  printf("\n\t\t请输入原密码：");
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
  if((strcmp(F_administor,administor)==0)&&(strcmp(F_passward,passward)==0))//判断输入的用户名和密码是否正确
  {
      fclose(fp1);
      i=0;
      if((fp1=fopen("管理员信息.txt","wb+"))==NULL)
      {
          printf("\n\t操作失败！按任意键继续...");
          getch();
      }
      else
      {
		  //输入新信息
          printf("\n\n\n\t\t请输入新管理员名称：");
          scanf("%s",administor);
          getchar();
          printf("\n\t\t请输入新密码：");
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
          fprintf(fp1,"%40s%50s",administor,passward);//将新的管理员账户和密码存入文件
          fclose(fp1);
          printf("\n\n\t操作成功，请按任意键继续...");
          getch();
      }
  }
  else
  {
     printf("\n\n\t操作失败！按任意键继续...");
     getch();
  }
  return 0;
}

//10.清空数据库函数
int Clean()
{
	system("cls");
	fflush(stdin);
	char choose;     //判断是否删除
	printf("                          软工三班班费收支管理系统\n\n");
	printf("-------------------------------清空数据库界面----------------------------------\n\n");
	printf("\t清空数据库:\n\n");
	printf("\t\t数据库清空后将无法恢复，您确定么？<Y/任意字符返回>");
	scanf("%c",&choose);
	if((fp2=fopen("软工三班班费收支管理系统.txt","rb+"))==NULL)
	{
	    printf("\n\t您未记录任何数据，按任意键返回...");
	    getch();
	    return 0;
	}
	fclose(fp2);
	if(choose=='Y')
	{
		if(remove("软工三班班费收支管理系统.txt"))
		{
			printf("\n\t操作失败，按任意键继续...");
			getch();
		}
		else
		{
			printf("\n\t操作成功，按任意键继续...");
			getch();
		}
	}
	return 0;
}

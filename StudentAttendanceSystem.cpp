#include<stdio.h>
#include<string.h>
#include<windows.h>          //windowsͼ�ν������

int opt;//����ѡ�����
int count=0;//���ڼ�¼����

//������-�������¼
typedef struct node *pointer;
struct node{
	char order[20];
	char id[20];
	char name[20];
	char week[20];
	char day[20];
	char part[20];
	char course[20];
	char reason[20];
	pointer next;
};
typedef pointer lklist;

lklist head;

typedef struct nnode *ppointer;
struct nnode{
	char id[20];
	char name[20];
	char week[20];
	int cishu;
	ppointer next;
};
typedef ppointer llklist;

//������-���༶��Ա
typedef struct nodes * pointers;
struct nodes{
	char account[20];
	char password[20];
	char power[20];
	pointers lchild,rchild;
};
typedef pointers bitree;

bitree t;

//���У������������
const int maxsize=100;
typedef struct{
	bitree data[maxsize];
	int front,rear;
}sqqueue;

//��Ҫ���ܺ�������
bitree level_creat();
int login(char no[20],char pwd[20]);
int administrator();
void classattendance();
void classpeople();
int modifypeople(bitree t);
int deletepeople(bitree t);
int insertpeople();
void levelorder(bitree t);
int committee();
void sta(lklist head,int k);
void all(lklist head);
void modify(lklist head,int k);
int updata(pointer p);
int deletes(lklist head,int k);
insert(lklist head,int i);
pointer get(lklist head,int i);
int student(char no[20]);
void stuweek();
void weekall();
void data();
void mwlocate(lklist head,char no[20],int week);
void swlocate(lklist head,char name[20],int week);
void walocate(lklist head,int week);
lklist creat();
lklist initlist();
int de_sqqueue(sqqueue *sq,bitree *x);
int empty_sqqueue(sqqueue *sq);
int en_sqqueue(sqqueue *sq,bitree x);
void init_sqqueue(sqqueue *sq);
void bubbleSort(llklist mylist);

//����������������༶��Ա��Ϣ
bitree level_creat(){
	char str[20];
	pointers Q[100];
	int front,rear;
	pointers root,s;
	root=NULL;
	front=rear=0;
	int dept=1;
	FILE *fp6;
	if ((fp6=fopen("�û���Ϣ�ļ�.txt","r"))==NULL){	
        printf("�û���Ϣ�ļ�������\n");
        return 0;
	}
	while(!feof(fp6)){
		s=new nodes;
		fscanf(fp6,"%s",str);
		strcpy(s->account,str);
		fscanf(fp6,"%s",str);
		strcpy(s->password,str);
		fscanf(fp6,"%s",str);
		strcpy(s->power,str);
		s->lchild=s->rchild=NULL;
		rear++;
		Q[rear]=s;
		if(rear==1){
			root=s;
			front=1;
		}
		else{
			if(s&&Q[front])
				if(rear%2==0)
					Q[front]->lchild=s;
				else
					Q[front]->rchild=s;
			if(rear%2==1)
				front++;
		}
	}
	fclose(fp6);
	return root;
}

//��ʼ������
void init_sqqueue(sqqueue *sq){
	sq->front=sq->rear=0;
}

//����
int en_sqqueue(sqqueue *sq,bitree x){
	if((sq->rear+1)%maxsize==sq->front){
		printf("������������ӣ�\n");
		return 0;
	}
	sq->rear=(sq->rear+1)%maxsize;
	sq->data[sq->rear]=x;
	return 1;
}
//�п�
int empty_sqqueue(sqqueue *sq){
	if(sq->rear==sq->front)
		return 1;
	else
		return 0;
}
//����
int de_sqqueue(sqqueue *sq,bitree *x){
	if(sq->rear==sq->front){
		printf("�ӿգ����ܳ��ӣ�\n");
		return 0;
	}
	sq->front=(sq->front+1)%maxsize;
	*x=sq->data[sq->front];
	return 1;
}

//�������ʼ��
lklist initlist(){
	pointer head;
	head = new node;
	head->next = NULL;
	return head;
}

//��������������ѧ��������Ϣ
lklist creat(){
	count=0;
	pointer rear,s;
	head = new node;
	rear = head;
	FILE *fp2;
    char str[20];
    if ((fp2=fopen("ѧ���������.txt","r"))==NULL){	
        printf("ѧ���������������\n");
        return 0;
	}
	while(!feof(fp2)){
		s = new node;
		fscanf(fp2,"%s",str);
		strcpy(s->order,str);
		fscanf(fp2,"%s",str);
		strcpy(s->id,str);
		fscanf(fp2,"%s",str);
		strcpy(s->name,str);
		fscanf(fp2,"%s",str);
		strcpy(s->week,str);
		fscanf(fp2,"%s",str);
		strcpy(s->day,str);
		fscanf(fp2,"%s",str);
		strcpy(s->part,str);
		fscanf(fp2,"%s",str);
		strcpy(s->course,str);
		fscanf(fp2,"%s",str);
		strcpy(s->reason,str);
		rear->next = s;
		rear = s;
		count++;
	}
	rear->next = NULL;
	fclose(fp2);
	return head;
}

//ĳ������ѧ������
void walocate(lklist head,int week){
	printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
	int sign=0;
	pointer p;
	p=head->next;
	char wk[20];
	sprintf(wk,"��%d��",week);
	while(p!=NULL){
		if(strcmp(p->week,wk)==0){
			printf("%s\t",p->order);
			printf("%s\t",p->id);
			printf("%s\t",p->name);
			printf("%s\t",p->week);
			printf("%s\t",p->day);
			printf("%s\t",p->part);
			printf("%s\t",p->course);
			printf("%s\n",p->reason);
			sign++;
		}
		p=p->next;
	}
	if(sign==0)
		printf("%s�޿��ڼ�¼\n",wk);
}

//ĳѧ��ĳ�ܿ������
void swlocate(lklist head,char name[20],int week){
	printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
	int sign=0;
	pointer p;
	p=head->next;
	char wk[20];
	sprintf(wk,"��%d��",week);
	while(p!=NULL){
		if(strcmp(p->week,wk)==0&&strcmp(p->name,name)==0){
			printf("%s\t",p->order);
			printf("%s\t",p->id);
			printf("%s\t",p->name);
			printf("%s\t",p->week);
			printf("%s\t",p->day);
			printf("%s\t",p->part);
			printf("%s\t",p->course);
			printf("%s\n",p->reason);
			sign++;
		}
		p=p->next;
	}
	if(sign==0)
		printf("%s%s�޿��ڼ�¼\n",name,wk);
}

//��¼�˺�ĳ�ܿ���
void mwlocate(lklist head,char no[20],int week){
	printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
	int sign=0;
	pointer p;
	p=head->next;
	char wk[20];
	sprintf(wk,"��%d��",week);
	while(p!=NULL){
		if(strcmp(p->week,wk)==0&&strcmp(p->id,no)==0){
			printf("%s\t",p->order);
			printf("%s\t",p->id);
			printf("%s\t",p->name);
			printf("%s\t",p->week);
			printf("%s\t",p->day);
			printf("%s\t",p->part);
			printf("%s\t",p->course);
			printf("%s\n",p->reason);
			sign++;
		}
		p=p->next;
	}
	if(sign==0)
		printf("��%s�޿��ڼ�¼\n",wk);
}

//��ʼ���������������濼��
void data(){
	initlist();
	creat();
}

//ĳ������ѧ���������
void weekall(){
	printf("��������Ҫ��ѯ��������");
	scanf("%d",&opt);
	walocate(head,opt);
}

//ĳѧ��ĳ�ܿ������
void stuweek(){
	char name[20];
	printf("��������Ҫ��ѯ��������");
	scanf("%s",&name);
	printf("��������Ҫ��ѯ��������");
	scanf("%d",&opt);
	swlocate(head,name,opt);
}

//��¼�˺�ĳ�ܿ������
void myweek(char no[20]){
	printf("��������Ҫ��ѯ��������");
	scanf("%d",&opt);
	mwlocate(head,no,opt);
}

//ѧ������
int student(char no[20]){
	printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
	data();
	printf("ѧ������\n");
	printf("1��ĳ��ȫ�࿼�ڲ�ѯ\n");
	printf("2��ĳѧ��ĳ�ܿ��ڲ�ѯ\n");
	printf("3���ҵĿ��ڲ�ѯ\n");
	printf("���������ַ��˳�\n");
	printf("�������Ӧ����ѡ���ܣ�");
	scanf("%d",&opt);
	switch(opt){
	case 1:{
		fflush(stdin);
		system("cls");
		printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
		weekall();
		return 1;
		   }
	case 2:{
		fflush(stdin);
		system("cls");
		printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
		stuweek();
		return 1;
		   }
	case 3:{
		fflush(stdin);
		system("cls");
		printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
		myweek(no);
		return 1;
		   }
	default : return 0;
	}
}

//������λ
pointer get(lklist head,int i){
	int j;
	pointer p;
	if(i==0)
		return head;
	if(i<0)
		return NULL;
	j=0;
	p=head->next;
	while(p!=NULL){
		j++;
		if(j==i)
			break;
		p=p->next;
	}
	return p;
}

//���ӿ��ڼ�¼
int insert(lklist head,int i){
	FILE *fp3;
	if((fp3=fopen("ѧ���������.txt","at+"))==NULL)
		fp3=fopen("ѧ���������.txt","wb+");
    fclose(fp3);
	pointer q,s;
	q = get(head,i-1);
	if(q==NULL)
		printf("�Ƿ�����λ�ã�\n");
	s = new node;
	printf("������ѧ��ѧ�ţ�");
	scanf("%s",s->id);
	printf("������ѧ��������");
	scanf("%s",s->name);
	printf("�����뿼��������");
	scanf("%s",s->week);
	printf("�����뿼�����ڣ�");
	scanf("%s",s->day);
	printf("������γ̽�����");
	scanf("%s",s->part);
	printf("������γ����ƣ�");
	scanf("%s",s->course);
	printf("�����뿼��ԭ��");
	scanf("%s",s->reason);
	if((fp3=fopen("ѧ���������.txt","at+"))==NULL)
	{
		printf("���ܴ򿪸����ݿ⣡");
		return 0;
	}
	fprintf(fp3,"\r\n %d",++i);
	fprintf(fp3," %s",s->id);
	fprintf(fp3," %s",s->name);
	char connect[20];
	sprintf(connect,"��%s��",s->week);
	fprintf(fp3," %s",connect);
	sprintf(connect,"����%s",s->day);
	fprintf(fp3," %s",connect);
	sprintf(connect,"��%s��",s->part);
	fprintf(fp3," %s",connect);
	fprintf(fp3," %s",s->course);
	fprintf(fp3," %s",s->reason);
	fclose(fp3);
	s->next = q->next;
	q->next = s;
	printf("���ӿ��ڼ�¼�ɹ�\n");
	return 1;
}

//ɾ�����ڼ�¼
int deletes(lklist head,int k){
	pointer p,q;
	q = get(head,k-1);
	if(q==NULL||q->next == NULL)
		printf("�Ƿ�ɾ��λ��\n");
	p=q->next;
	q->next = p->next;
	delete p;
	FILE *fp4,*fp5;
	if ((fp4=fopen("ѧ���������.txt","r"))==NULL){	
        printf("ѧ���������������\n");
        return 0;
	}
	fp5=fopen("������ʱ�ļ�.txt","w");
	p=head->next;
	while(p!=NULL){
		if(strcmp(p->order,"1")!=0)
			fprintf(fp5,"\r\n");
		int i,j;
		int sum=0;
		for(i=strlen(p->order)-1,j=1;i>=0;i--){ 
			p->order[i]=p->order[i]-'0'; 
			sum+=p->order[i]*j;
			j=j*10;
		}
		if(sum<k)
			fprintf(fp5," %d",sum);
		else
			fprintf(fp5," %d",--sum);
		fprintf(fp5," %s",p->id);
		fprintf(fp5," %s",p->name);
		fprintf(fp5," %s",p->week);
		fprintf(fp5," %s",p->day);
		fprintf(fp5," %s",p->part);
		fprintf(fp5," %s",p->course);
		fprintf(fp5," %s",p->reason);
		p=p->next;
	}
	fclose(fp4);
    fclose(fp5);
    remove("ѧ���������.txt");
    rename("������ʱ�ļ�.txt","ѧ���������.txt");
	printf("ɾ�����ڼ�¼�ɹ�\n");
	return 1;
}

//�޸Ŀ��ڣ�����ʱ�ļ������ɾ��ԭ�ļ����ٸ���
int updata(pointer p){
	FILE *fp4,*fp5;
	if ((fp4=fopen("ѧ���������.txt","r"))==NULL){	
        printf("ѧ���������������\n");
        return 0;
	}
	fp5=fopen("������ʱ�ļ�.txt","w");
	p=head->next;
	while(p!=NULL){
		if(strcmp(p->order,"1")!=0)
			fprintf(fp5,"\r\n");
		fprintf(fp5," %s",p->order);
		fprintf(fp5," %s",p->id);
		fprintf(fp5," %s",p->name);
		fprintf(fp5," %s",p->week);
		fprintf(fp5," %s",p->day);
		fprintf(fp5," %s",p->part);
		fprintf(fp5," %s",p->course);
		fprintf(fp5," %s",p->reason);
		p=p->next;
	}
	fclose(fp4);
    fclose(fp5);
    remove("ѧ���������.txt");
    rename("������ʱ�ļ�.txt","ѧ���������.txt");
	printf("�޸Ŀ��ڼ�¼�ɹ�\n");
	return 1;
}

//�޸Ŀ��ڼ�¼
void modify(lklist head,int k){
	pointer p,q;
	char connect[20];
	q = get(head,k-1);
	if(q==NULL||q->next == NULL)
		printf("�Ƿ��޸�λ��\n");
	p=q->next;
	printf("1��ѧ��\n");
	printf("2������\n");
	printf("3������\n");
	printf("4������\n");
	printf("5������\n");
	printf("6���γ�\n");
	printf("7��ԭ��\n");
	printf("���������ַ��˳��޸�\n");
	printf("��ѡ����Ҫ�޸ĵ����ݣ�");
	scanf("%d",&opt);
	switch(opt){
	case 1:{
		printf("�������޸ĺ��ѧ�ţ�");
		scanf("%s",p->id);
		updata(p);
		break;
		   }
	case 2:{
		printf("�������޸ĺ��������");
		scanf("%s",p->name);
		updata(p);
		break;
		   }
	case 3:{
		printf("�������޸ĺ��������");
		scanf("%s",connect);
		sprintf(p->week,"��%s��",connect);
		updata(p);
		break;
		   }
	case 4:{
		printf("�������޸ĺ�����ڣ�");
		scanf("%s",connect);
		sprintf(p->day,"����%s",connect);
		updata(p);
		break;
		   }
	case 5:{
		printf("�������޸ĺ�Ľ�����");
		scanf("%s",connect);
		sprintf(p->part,"��%s��",connect);
		updata(p);
		break;
		   }
	case 6:{
		printf("�������޸ĺ�Ŀγ̣�");
		scanf("%s",p->course);
		updata(p);
		break;
		   }
	case 7:{
		printf("�������޸ĺ��ԭ��");
		scanf("%s",p->reason);
		updata(p);
		break;
		   }
	default: break;
	}
}

//���п��ڼ���
void all(lklist head){
	printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
	int sign=0;
	char connect[20];
	char input[20];
	pointer p;
	p=head->next;
	while(p!=NULL){
		printf("%s\t",p->order);
		printf("%s\t",p->id);
		printf("%s\t",p->name);
		printf("%s\t",p->week);
		printf("%s\t",p->day);
		printf("%s\t",p->part);
		printf("%s\t",p->course);
		printf("%s\n",p->reason);
		sign++;
		p=p->next;
	}
	if(sign==0)
		printf("�޿��ڼ�¼\n");
	printf("1�����ӿ��ڼ�¼\n");
	printf("2��ɾ�����ڼ�¼\n");
	printf("3���޸Ŀ��ڼ�¼\n");
	printf("4�����ҿ��ڼ�¼\n");
	printf("���������ַ�����\n");
	printf("�������Ӧ����ѡ���ܣ�");
	scanf("%d",&opt);
	switch(opt){
	case 1:{
		insert(head,count);
		break;
		   }
	case 2:{
		printf("������ɾ�����ڵ���ţ�");
		scanf("%d",&opt);
		deletes(head,opt);
		break;
		   }
	case 3:{
		printf("�������޸Ŀ��ڵ���ţ�");
		scanf("%d",&opt);
		modify(head,opt);
		break;
		   }
	case 4:{
		printf("1��ѧ��\n");
		printf("2������\n");
		printf("3������\n");
		printf("4������\n");
		printf("5������\n");
		printf("6���γ�\n");
		printf("7��ԭ��\n");
		printf("�������ѯ���ڵ�������");
		scanf("%d",&opt);
		switch(opt){
		case 1:{
			printf("������ѧ�ţ�");
			scanf("%s",input);
			printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
			pointer p;
			p=head->next;
			while(p!=NULL){
				if(strcmp(input,p->id)==0){
					printf("%s\t",p->order);
					printf("%s\t",p->id);
					printf("%s\t",p->name);
					printf("%s\t",p->week);
					printf("%s\t",p->day);
					printf("%s\t",p->part);
					printf("%s\t",p->course);
					printf("%s\n",p->reason);
				}
				p=p->next;
			}
			break;
			   }
		case 2:{
			printf("������������");
			scanf("%s",input);
			printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
			pointer p;
			p=head->next;
			while(p!=NULL){
				if(strcmp(input,p->name)==0){
					printf("%s\t",p->order);
					printf("%s\t",p->id);
					printf("%s\t",p->name);
					printf("%s\t",p->week);
					printf("%s\t",p->day);
					printf("%s\t",p->part);
					printf("%s\t",p->course);
					printf("%s\n",p->reason);
				}
				p=p->next;
			}
			break;
			   }
		case 3:{
			printf("������������");
			scanf("%s",input);
			sprintf(connect,"��%s��",input);
			printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
			pointer p;
			p=head->next;
			while(p!=NULL){
				if(strcmp(connect,p->week)==0){
					printf("%s\t",p->order);
					printf("%s\t",p->id);
					printf("%s\t",p->name);
					printf("%s\t",p->week);
					printf("%s\t",p->day);
					printf("%s\t",p->part);
					printf("%s\t",p->course);
					printf("%s\n",p->reason);
				}
				p=p->next;
			}
			break;
		   }
		case 4:{
			printf("���������ڣ�");
			scanf("%s",input);
			sprintf(connect,"����%s",input);
			printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
			pointer p;
			p=head->next;
			while(p!=NULL){
				if(strcmp(connect,p->day)==0){
					printf("%s\t",p->order);
					printf("%s\t",p->id);
					printf("%s\t",p->name);
					printf("%s\t",p->week);
					printf("%s\t",p->day);
					printf("%s\t",p->part);
					printf("%s\t",p->course);
					printf("%s\n",p->reason);
				}
				p=p->next;
			}
			break;
			   }
		case 5:{
			printf("�����������");
			scanf("%s",input);
			sprintf(connect,"��%s��",input);
			printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
			pointer p;
			p=head->next;
			while(p!=NULL){
				if(strcmp(connect,p->part)==0){
					printf("%s\t",p->order);
					printf("%s\t",p->id);
					printf("%s\t",p->name);
					printf("%s\t",p->week);
					printf("%s\t",p->day);
					printf("%s\t",p->part);
					printf("%s\t",p->course);
					printf("%s\n",p->reason);
				}
				p=p->next;
			}
			break;
			   }
		case 6:{
			printf("������γ̣�");
			scanf("%s",input);
			printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
			pointer p;
			p=head->next;
			while(p!=NULL){
				if(strcmp(input,p->course)==0){
					printf("%s\t",p->order);
					printf("%s\t",p->id);
					printf("%s\t",p->name);
					printf("%s\t",p->week);
					printf("%s\t",p->day);
					printf("%s\t",p->part);
					printf("%s\t",p->course);
					printf("%s\n",p->reason);
				}
				p=p->next;
			}
			break;
			   }
		case 7:{
			printf("������ԭ��");
			scanf("%s",input);
			printf("���\tѧ��\t����\t����\t����\t����\t�γ�\tԭ��\n");
			pointer p;
			p=head->next;
			while(p!=NULL){
				if(strcmp(input,p->reason)==0){
					printf("%s\t",p->order);
					printf("%s\t",p->id);
					printf("%s\t",p->name);
					printf("%s\t",p->week);
					printf("%s\t",p->day);
					printf("%s\t",p->part);
					printf("%s\t",p->course);
					printf("%s\n",p->reason);
				}
				p=p->next;
			}
			break;
			   }
		default: break;
		}
		break;
		   }
	default : break;
	}
}

//�����ʼ���
void sta(lklist head,int k){
	printf("ѧ��\t����\t����\t������\n");
	pointer p,s;
	p=head->next;
	s=head->next;
	char wk[20];
	char add[20];
	char refuse[20][20];
	ppointer rear,ss;
	llklist hhead = new nnode;
	rear = hhead;
	sprintf(wk,"��%d��",k);
	int n=0,m=0;
	while(p!=NULL){
		int k=0;
		for(int i=0;i<=m;i++){
			if(strcmp(refuse[i],p->name)!=0)
				k++;
		}
		if(k-1==m){
			if(strcmp(wk,p->week)==0){
				strcpy(add,p->id);
				while(s!=NULL){
					if(strcmp(add,s->id)==0&&strcmp(wk,s->week)==0){
						if(n==0){
							ss = new nnode;
							strcpy(ss->id,s->id);
							strcpy(ss->name,s->name);
							strcpy(refuse[m],s->name);
							strcpy(ss->week,s->week);
							rear->next = ss;
							rear = ss;
						}
						n++;
						s=s->next;
					}
					else
						s=s->next;
				}
				m++;
				ss->cishu = n;
				n=0;
			}
		}
		rear->next = NULL;
		s=head->next;
		p=p->next;
	}
	//�������
	bubbleSort(hhead);
	int sign=0;
	ppointer pp;
	pp=hhead->next;
	while(pp!=NULL){
		printf("%s\t",pp->id);
		printf("%s\t",pp->name);
		printf("%s\t",pp->week);
		printf("%.0f%%\n",(1-pp->cishu/5.0)*100);
		sign++;
		pp=pp->next;
	}
	if(sign==0)
		printf("�޿��ڼ�¼\n");
}

//ð������
void bubbleSort(llklist mylist)
{
    if((mylist -> next == NULL) || (mylist -> next -> next == NULL))
    {
        return;
    }

    nnode *hhead, * pre, * cur, *next, * end, * temp;
    hhead = mylist;
    end = NULL;
    //������ͷ��ʼ���ϴ�ֵ�����
    while(hhead -> next != end)
    {
        for(pre = hhead, cur = pre -> next, next = cur -> next; next != end; pre = pre -> next, cur = cur -> next, next = next -> next)
        {
            //���ڵĽڵ�Ƚ�
            if(cur -> cishu < next -> cishu)
            {
                cur -> next = next -> next;
                pre -> next = next;
                next -> next = cur;
                temp = next;
                next = cur;
                cur = temp;
            }
        }
        end = cur;
    }
}

//��ί����
int committee(){
	printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
	data();
	printf("��ί����\n");
	printf("1���༶���ڼ�¼\n");
	printf("2���ܳ���������\n");
	printf("���������ַ��˳�\n");
	printf("�������Ӧ����ѡ���ܣ�");
	scanf("%d",&opt);
	switch(opt){
	case 1:{
		fflush(stdin);
		system("cls");
		printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
		all(head);
		return 1;
		   }
	case 2:{
		fflush(stdin);
		system("cls");
		printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
		printf("����������������������");
		scanf("%d",&opt);
		sta(head,opt);
		return 1;
		   }
	default : return 0;
	}
}

//�����������ӡ�༶��Ա��Ϣ
void levelorder(bitree t){
	pointers p;
	sqqueue Q;
	if(t==NULL)
		return;
	init_sqqueue(&Q);
	en_sqqueue(&Q,t);
	while(!empty_sqqueue(&Q)){
		de_sqqueue(&Q,&p);
		printf("%s\t",p->account);
		printf("%s\t",p->password);
		printf("%s\n",p->power);
		if(p->lchild!=NULL)
			en_sqqueue(&Q,p->lchild);
		if(p->rchild!=NULL)
			en_sqqueue(&Q,p->rchild);
	}
}

//���Ӱ༶��Ա
int insertpeople(){
	FILE *fp7;
	if((fp7=fopen("�û���Ϣ�ļ�.txt","ab+"))==NULL)
		fp7=fopen("�û���Ϣ�ļ�.txt","wb+");
    fclose(fp7);
	if((fp7=fopen("�û���Ϣ�ļ�.txt","ab+"))==NULL)
	{
		printf("���ܴ򿪸����ݿ⣡");
		return 0;
	}
	char account[20];
	char password[20];
	char power[20];
	printf("�������˺ţ�");
	scanf("%s",&account);
	printf("���������룺");
	scanf("%s",&password);
	printf("������Ȩ�ޣ�");
	scanf("%s",&power);
	fprintf(fp7,"\r\n %s",account);
	fprintf(fp7," %s",password);
	fprintf(fp7," %s",power);
	fclose(fp7);
	printf("���Ӱ༶��Ա�ɹ�\n");
	return 1;
}

//ɾ���༶��Ա
int deletepeople(bitree t){
	char str[20];
	bool k=false;
	printf("��������Ҫɾ�����˺ţ�");
	scanf("%s",&str);
	FILE *fp10,*fp11;
	if ((fp10=fopen("�û���Ϣ�ļ�.txt","r"))==NULL){	
        printf("�û���Ϣ�ļ�������\n");
        return 0;
	}
	fp11=fopen("�û���ʱ�ļ�.txt","w");
	pointers p;
	sqqueue Q;
	if(t==NULL)
		return 1;
	init_sqqueue(&Q);
	en_sqqueue(&Q,t);
	while(!empty_sqqueue(&Q)){
		de_sqqueue(&Q,&p);
		if(strcmp(p->account,str)==0){
			k=true;
		}
		else{
			if(strcmp(p->account,"000")!=0)
				fprintf(fp11,"\r\n");
			fprintf(fp11," %s",p->account);
			fprintf(fp11," %s",p->password);
			fprintf(fp11," %s",p->power);
		}
		if(p->lchild!=NULL)
			en_sqqueue(&Q,p->lchild);
		if(p->rchild!=NULL)
			en_sqqueue(&Q,p->rchild);
	}
	if(k==false)
		printf("û�д��˻�\n");
	fclose(fp10);
    fclose(fp11);
    remove("�û���Ϣ�ļ�.txt");
    rename("�û���ʱ�ļ�.txt","�û���Ϣ�ļ�.txt");
	printf("ɾ���༶��Ա�ɹ�\n");
	return 1;
}

//�޸İ༶��Ա
int modifypeople(bitree t){
	char str[20];
	bool k=false;
	printf("��������Ҫ���ĵ��˺ţ�");
	scanf("%s",&str);
	FILE *fp8,*fp9;
	if ((fp8=fopen("�û���Ϣ�ļ�.txt","r"))==NULL){	
        printf("�û���Ϣ�ļ�������\n");
        return 0;
	}
	fp9=fopen("�û���ʱ�ļ�.txt","w");
	pointers p;
	sqqueue Q;
	if(t==NULL)
		return 1;
	init_sqqueue(&Q);
	en_sqqueue(&Q,t);
	while(!empty_sqqueue(&Q)){
		de_sqqueue(&Q,&p);
		if(strcmp(p->account,str)==0){
			printf("��������ĺ���˺ţ�");
			scanf("%s",p->account);
			printf("��������ĺ�����룺");
			scanf("%s",p->password);
			printf("��������ĺ��Ȩ�ޣ�");
			scanf("%s",p->power);
			k=true;
		}
		if(strcmp(p->account,"000")!=0)
			fprintf(fp9,"\r\n");
		fprintf(fp9," %s",p->account);
		fprintf(fp9," %s",p->password);
		fprintf(fp9," %s",p->power);
		if(p->lchild!=NULL)
			en_sqqueue(&Q,p->lchild);
		if(p->rchild!=NULL)
			en_sqqueue(&Q,p->rchild);
	}
	if(k==false)
		printf("û�д��˻�\n");
	fclose(fp8);
    fclose(fp9);
    remove("�û���Ϣ�ļ�.txt");
    rename("�û���ʱ�ļ�.txt","�û���Ϣ�ļ�.txt");
	printf("�޸İ༶��Ա�ɹ�\n");
	return 1;
}

//�༶��Ա
void classpeople(){
	printf("�û���\t����\tȨ��\n");
	levelorder(t);
	printf("1�����Ӱ༶��Ա\n");
	printf("2��ɾ���༶��Ա\n");
	printf("3���޸ĳ�ԱȨ��\n");
	printf("���������ַ�����\n");
	printf("�������Ӧ����ѡ���ܣ�");
	scanf("%d",&opt);
	switch(opt){
	case 1:{
		insertpeople();
		break;
		   }
	case 2:{
		deletepeople(t);
		break;
		   }
	case 3:{
		modifypeople(t);
		break;
		   }
	default : break;
	}
}

void classattendance(){
	all(head);
}

//����Աҳ��
int administrator(){
	printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
	data();
	t=level_creat();
	printf("����Ա����\n");
	printf("1���༶��Ա����\n");
	printf("2���༶���ڹ���\n");
	printf("���������ַ��˳�\n");
	printf("�������Ӧ����ѡ���ܣ�");
	scanf("%d",&opt);
	switch(opt){
	case 1:{
		fflush(stdin);
		system("cls");
		printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
		classpeople();
		return 1;
		   }
	case 2:{
		fflush(stdin);
		system("cls");
		printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
		classattendance();
		return 1;
		   }
	default : return 0;
	}
}

//��¼�ж��û���Ϣ
int login(char no[20],char pwd[20]){
	fflush(stdin);
    FILE *fp1;
	int ok=1;
    char str[20];
    if ((fp1=fopen("�û���Ϣ�ļ�.txt","r"))==NULL){	
        printf("�û���Ϣ�ļ�������\n");
        return 0;
	}
	while(!feof(fp1)){
		fscanf(fp1,"%s",str);
		if(strcmp(str,no)==0){
			fscanf(fp1,"%s",str);
			if(strcmp(str,pwd)==0){
				system("cls");
				fscanf(fp1,"%s",str);
				if(strcmp(str,"1")==0){
					fclose(fp1);
					while(ok){
						ok=administrator();
					}
					return 1;
				}
				if(strcmp(str,"2")==0){
					fclose(fp1);
					while(ok){
						ok=committee();
					}
					return 2;
				}
				if(strcmp(str,"3")==0){
					fclose(fp1);
					while(ok){
						ok=student(no);
					}
					return 3;
				}
			}
			else{
				fclose(fp1);
				return 0;
			}
		}
		fscanf(fp1,"%s",str);
		fscanf(fp1,"%s",str);
	}
	fclose(fp1);
	return 0;
}

//��ӭҳ��
void welcome(){
	printf("--------------------�༶���ڹ���ϵͳ----------------------\n");
	char no[20];
	char pwd[20];
	printf("�������˺ţ�");
	scanf("%s",&no);
	printf("���������룺");
	scanf("%s",&pwd);
	if((login(no,pwd))==0){
		printf("�������������û�����������Ӧ��\n",pwd);
	}
}

int main(){
	system("color B0"); //�����ɫ
	welcome();
	return 0;
}

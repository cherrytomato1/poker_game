#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define COL 4
#define NUM 13
#define PLY 5
#define HN 7

typedef struct
{
        int patt;
        int numb;
        int stat;
}ocd ;
typedef struct
{
        int dc[COL][NUM];                       //덱카드
//      int hc[PLY][COL][NUM];                  //핸드카드
//      int pl;                                 //플레이어
//      int nu;                                 //카드 숫자
//      int co;                                 //카드 패턴
        int cn;
        int cheat;                              //개발자용
        int res[PLY];
        int std_res[PLY];
        int pl_stat[PLY];
}data ;
int distribute(data *dat,ocd **pc)
{
        int p,rnu,rpa;
        for(p=0;p<PLY;p++)
        {
                if(dat->pl_stat[p]==1)
                {
                        rnu=rand()%NUM;
                        rpa=rand()%COL;
                        while(dat->dc[rpa][rnu]==0)
                        {
                                rnu=rand()%NUM;
                                rpa=rand()%COL;
                        }
                        dat->dc[rpa][rnu]=0;
//                      dat->hc[p][rpa][rnu]=1;
//                      while(dat->pc[p][i].stat!=0)            //제대로 동작안하는반복문
//                                      i++;
                        pc[p][dat->cn].patt=rpa;                        //여기는 -> .
                        pc[p][dat->cn].numb=rnu;
                        pc[p][dat->cn].stat=1;
//                      printf("플레이어 %d이 %d 번째로 받은카드 %d %d \n",p+1,dat->cn,dat->pc[p][dat->cn].patt,dat->pc[p][dat->cn].numb);
                        if(dat->cn==HN-1)
                                pc[p][dat->cn].stat++;
                }
        }
        dat->cn++;
}
int print(data *dat,ocd **pc,int p)
{
        int i,j;
        printf("         ▶ 플레이어 %d",p+1);
//      for(i=0;i<dat->cn;i++) //cn??의 값
//      {
//              printf("%d",dat->pc[p][dat->hn].stat);
//      {
        printf("\n        ");
        for(j=0;j<dat->cn;j++)
        {
                if(pc[p][j].stat==0)
                        break;
                printf("┌");
                printf("───");
                printf("┐");
        }
        printf("\n        ");
        for(j=0;j<dat->cn;j++)
        {
                if(pc[p][j].stat==0)
                        break;
                printf("│");
                if(dat->pl_stat[p]!=2)
                {
                        if((pc[p][j].stat==1||p==0)||dat->cheat==2)
                        {
                                print_pat(pc[p][j].patt);
                                printf("  │");
                        }
                        else if(pc[p][j].stat==2)
                        {
//                              printf("%d번째카드:",i+1);
                                printf("***");
                                printf("│");
                        }
                }
                else
                {
                        printf("xxx");
                        printf("│");
                }
        }
        printf("\n        ");
        for(j=0;j<dat->cn;j++)
        {
                if(pc[p][j].stat==0)
                        break;
                if(dat->pl_stat[p]!=2)
                {
                        if((pc[p][j].stat==1||p==0)||dat->cheat==2)
                        {
                                printf("│ ");
                                print_num(pc[p][j].numb);
                                printf("│");
                        }
                        else if(pc[p][j].stat==2)
                        {
//                              printf("%d번째카드:",i+1);
                                printf("│");
                                printf("***");
                                printf("│");
                        }
                }
                else
                {
                        printf("│");
                        printf("xxx");
                        printf("│");
                }
        }
        printf("\n        ");
        for(j=0;j<dat->cn;j++)
        {
                if(pc[p][j].stat==0)
                        break;
                printf("└");
                printf("───");
                printf("┘");
        }
        printf("\n");
}
int print_pat(int pat)
{
        switch(pat)
        {
                case 0 :
                        printf("♣");
                        break;
                case 1 :
                        printf("♡");
                        break;
                case 2 :
                        printf("◇");
                        break;
                case 3 :
                        printf("♠");
                        break;
                default :
                        break;
        }
}
int print_num(int num)
{
        switch(num)
        {
                case 9 :
                        printf(" J");
                        break;
                case 10 :
                        printf(" Q");
                        break;
                case 11 :
                        printf(" K");
                        break;
                case 12 :
                        printf(" A");
                        break;
                default :
                        printf("%2d",num+2);
                        break;
        }
}
int set(data *dat,ocd **pc)
{
        int i,j,k,l;
        srand(time(NULL));


        for(i=0;i<PLY;i++)
        {
                for(j=0;j<COL;j++)
                {
                        for(k=0;k<NUM;k++)
                        {
                                dat->dc[j][k]=1;
//                              printf("%d ",dat.pc[i]->stat);
                        }
                }
                for(l=0;l<HN;l++)
                {
                        pc[i][l].numb=-1;               // . . 하니까 에러남 여기는  -> ->해도 에러안남
                        pc[i][l].patt=-1;
                        pc[i][l].stat=0;
                }
                dat->pl_stat[i]=1;
        }
        dat->cn=0;
        dat->cheat=0;
}
int sort(data *dat,ocd **pc)
{
        int i,temp,p;
        for(p=0;p<PLY;p++)
        {
                for(i=0;i<HN-1;i++) //cn??의 값
                {
                        if(pc[p][i].stat==0)
                        {
                                pc[p][i].patt=pc[p][i+1].patt;                  //여기는 -> .
                                pc[p][i].numb=pc[p][i+1].numb;
                                pc[p][i].stat=pc[p][i+1].stat;
                                pc[p][i+1].patt=-1;                     //여기는 -> .
                                pc[p][i+1].numb=-1;
                                pc[p][i+1].stat=0;
                        }
                        if(pc[p][i].stat==1&&pc[p][i+1].stat==2)
                        {
                                temp=pc[p][i].patt;                     //여기는 -> .
                                pc[p][i].patt=pc[p][i+1].patt;                  //여기는 -> .
                                pc[p][i+1].patt=temp;
                                temp=pc[p][i].numb;                     //여기는 -> .
                                pc[p][i].numb=pc[p][i+1].numb;                  //여기는 -> .
                                pc[p][i+1].numb=temp;
                                temp=pc[p][i].stat;                     //여기는 -> .
                                pc[p][i].stat=pc[p][i+1].stat;                  //여기는 -> .
                                pc[p][i+1].stat=temp;
                        }
                }
        }
}
int discard(data *dat,ocd **pc)
{
        int dscd,p;
        printf("버릴 카드를 선택하세요 숫자 1~4\n");
        scanf("%d",&dscd);
        pc[0][dscd-1].stat=0;
        for(p=1;p<PLY;p++)
        {
                dscd=rand()%4;
                pc[p][dscd].stat=0;
        }
        dat->cn--;
//      printf("%d",dat->pc[p][dscd-1].stat);
}

int open(data *dat,ocd **pc)
{
        int opcd,p;
        printf("보여줄 카드를 선택하세요 숫자 1~3\n");
        scanf("%d",&opcd);
        pc[0][opcd-1].stat=1;
        for(p=1;p<PLY;p++)
        {
                opcd=rand()%3;
                pc[p][opcd].stat=1;
        }
}
int check(data *dat,ocd **pc,int i,int opc)                             //세그멘테이션 오류(오버플로우?)
{
        int j,nu,nu2,rs,rs2;
        ocd num[HN],pat[HN];
        for(j=0;j<HN;j++)
        {
                pat[j].patt=pc[i][j].patt;
                pat[j].numb=pc[i][j].numb;
                pat[j].stat=pc[i][j].stat;
                num[j].patt=pc[i][j].patt;
                num[j].numb=pc[i][j].numb;
                num[j].stat=pc[i][j].stat;
        }
        if(opc==0)
        {
                for(j=0;j<HN;j++)
                {
                        if(pat[j].stat==2)
                        {
                                pat[j].patt=-1;
                                pat[j].numb=-1;
                        }

                        if(num[j].stat==2)
                        {
                                num[j].patt=-1;
                                num[j].numb=-1;
                        }
                }
        }
        if(dat->pl_stat[i]==2)
        {
                for(j=0;j<HN;j++)
                {
                                pat[j].patt=-1;
                                pat[j].numb=-1;
                                num[j].patt=-1;
                                num[j].numb=-1;
                }
        }
//      printf("P%d, %d %d %d %d %d %d %d \n",i,pat[0],pat[1],pat[2],pat[3],pat[4],pat[5],pat[6]);
//      printf("플레이어%d ",i+1);
        check_sortnum(num);
        check_sortpat(pat);
//      printf("p%d %d %d %d %d %d %d %d\n",i+1,num[0],num[1],num[2],num[3],num[4],num[5],num[6]);
        rs=pair(num);
        rs=triple(num,rs);
        rs=fullhouse(num,rs);
        rs=fourcard(num,rs);
        rs2=straight(num,0);
        rs2=rs2>70000?rs2:flush(pat,rs2);
        dat->res[i]=rs>rs2?rs:rs2;
        if(opc!=1)
                res_sort(dat);
//      if(dat->res[i]>=20000)
//              dat->res[i]=twopair(num,pat,dat->res[i]);
}
int check_print(data *dat,ocd **pc,int i)
{
        int nu,nu2;
        nu=(dat->res[i]%10000)/100;                             //1**00
        nu2=dat->res[i]%100;                                    //100**
//      printf(" %d ",dat->res[i]);
        if(dat->res[i]<10000)
        {
                print_pat(nu2);
                print_num(nu);
                printf(" top");
        }
        else if(dat->res[i]>=10000&&dat->res[i]<30000)
        {
//              print_pat(nu2);
                print_num(nu2);
                printf(" Onepair");
        }
        else if(dat->res[i]>=40000&&dat->res[i]<50000)
        {
                print_num(nu);
                print_num(nu2);
                printf(" Twopair");
        }
        else if(dat->res[i]>=50000&&dat->res[i]<60000)
        {
//              print_num(nu);
                print_num(nu2);
                printf(" Triple");
        }
        else if(dat->res[i]>=60000&&dat->res[i]<63000)
        {
                print_num(nu);
//              print_num(nu2);
                printf(" Straight");
        }
        else if(dat->res[i]>=63000&&dat->res[i]<66000)
        {
//              print_num(nu);
//              print_pat(nu2);
                printf(" Back Straight");
        }
        else if(dat->res[i]>=66000&&dat->res[i]<70000)
        {
//              print_num(nu);
//              print_pat(nu2);
                printf(" Mountain");
        }
        else if(dat->res[i]>=70000&&dat->res[i]<80000)
        {
//              print_num(nu);
                print_pat(nu2);
                printf(" Flush");
        }
        else if(dat->res[i]>=80000&&dat->res[i]<90000)
        {
                print_num(nu);
                print_num(nu2);
                printf(" Full House");
        }
        else if(dat->res[i]>=90000&&dat->res[i]<100000)
        {
//              print_num(nu);
                print_num(nu2);
                printf(" Four Card");
        }
        else if(dat->res[i]>=130000&&dat->res[i]<133000)
        {
                print_pat(nu2);
                print_num(nu);
                printf(" Straight Flush");
        }
        else if(dat->res[i]>=133000&&dat->res[i]<136000)
        {
                print_pat(nu2);
//              print_num(nu);
                printf("Back Straight Flush");
        }
        else if(dat->res[i]>=136000&&dat->res[i]<146000)
        {
                print_pat(nu2);
//              print_num(nu);
                printf("Royal Straight Flush");
        }
}
//int check_print(int res)
int check_sortnum(ocd num[HN])
{
        int i,j,temp;
        for(i=0;i<HN;i++)
        {
                for(j=i+1;j<HN;j++)
                {
                        if(num[i].numb>num[j].numb)
                        {
                                temp=num[i].numb;
                                num[i].numb=num[j].numb;
                                num[j].numb=temp;
                                temp=num[i].patt;
                                num[i].patt=num[j].patt;
                                num[j].patt=temp;
                                temp=num[i].stat;
                                num[i].stat=num[j].stat;
                                num[j].stat=temp;
                        }
                }
        }
}
int check_sortpat(ocd num[HN])
{
        int i,j,temp;
        for(i=0;i<HN;i++)
        {
                for(j=i+1;j<HN;j++)
                {
                        if(num[i].patt>num[j].patt)
                        {
                                temp=num[i].numb;
                                num[i].numb=num[j].numb;
                                num[j].numb=temp;
                                temp=num[i].patt;
                                num[i].patt=num[j].patt;
                                num[j].patt=temp;
                                temp=num[i].stat;
                                num[i].stat=num[j].stat;
                                num[j].stat=temp;
                        }
                }
        }
}
int pair(ocd num[HN])
{
        int i,j;
        for(i=1;i<HN;i++)
        {
                if(num[i].numb==num[i-1].numb&&num[i].numb!=-1)
                {
                        for(j=i+1;j<HN;j++)
                        {
                                if(num[j].numb==num[j-1].numb&&num[j].numb!=-1&&num[j].numb!=num[i].numb)
                                        return (40000+(num[j].numb*100)+num[i].numb);
                        }
                        return (10000+num[i].numb);
                }
        }
        return (num[HN-1].numb*100)+num[HN-1].patt;
}
//      for(i=0;i<HN;i++)
//              printf("pair check2 : %d\n",num[i]);
int triple(ocd num[HN],int res)
{
        int i,j;
        for(i=2;i<HN;i++)
        {
                if(num[i].numb==num[i-1].numb&&num[i].numb==num[i-2].numb&&num[i].numb!=-1)
                        return 50000+num[i].numb;
        }
        return res;
}
int fullhouse(ocd num[HN],int res)
{
        int i,j;
        for(i=2;i<HN;i++)
        {
                if(num[i].numb==num[i-1].numb&&num[i].numb==num[i-2].numb&&num[i].numb!=-1)
                {
                        for(j=i+2;j<HN;j++)
                        {
                                if(num[j].numb==num[j-1].numb&&num[j].numb!=-1)
                                        return 80000+(num[i].numb*100)+num[j].numb;
                        }
                }
        }
        for(j=1;j<HN;j++)
        {
                if(num[j].numb==num[j-1].numb&&num[j].numb!=-1)
                {
                        for(i=j+3;i<HN;i++)
                        {
                                if(num[i].numb==num[i-1].numb&&num[i].numb==num[i-2].numb&&num[i].numb!=-1)
                                        return 80000+(num[i].numb*100)+num[j].numb;
                        }
                }
        }
        return res;
}
int fourcard(ocd num[HN],int res)
{
        int i,j;
        for(i=3;i<HN;i++)
        {
                if(num[i].numb==num[i-1].numb&&num[i].numb==num[i-2].numb&&num[i].numb==num[i-3].numb&&num[i].numb!=-1)
                        return 90000+num[i].numb;
        }
        return res;
}
int straight(ocd num[HN],int res)
{
        int i,j;
        for(i=0;i<HN-1;i++)
        {
                if(num[i].numb==num[i+1].numb&&num[i].numb!=-1)
                        num[i].numb=-1;
        }
        check_sortnum(num);

        for(i=4;i<HN;i++)
        {
                if(num[i].numb-1==num[i-1].numb&&num[i].numb-2==num[i-2].numb&&num[i].numb-3==num[i-3].numb&&num[i].numb-4==num[i-4].numb&&num[i-4].numb!=-1)
                {
                        if(num[i].numb==12)
                        {
                                if(num[i].patt==num[i-1].patt&&num[i].patt==num[i-2].patt&&num[i].patt==num[i-3].patt&&num[i].patt==num[i-4].patt&&num[i].patt!=-1)
                                        return 136000+(num[i].patt);
                                return 66000+(num[i].patt);
                        }
                        if(num[i].patt==num[i-1].patt&&num[i].patt==num[i-2].patt&&num[i].patt==num[i-3].patt&&num[i].patt==num[i-4].patt&&num[i].patt!=-1)
                                return 130000+(num[i].numb*100+num[i].patt);
                        return 60000+(num[i].numb*100);
                }
                if(num[i].numb==3&&num[i].numb-1==num[i-1].numb&&num[i].numb-2==num[i-2].numb&&num[i].numb-3==num[i-3].numb&&num[HN-1].numb==12)
                {
                        if(num[i].patt==num[i-1].patt&&num[i].patt==num[i-2].patt&&num[i].patt==num[i-3].patt&&num[i].patt==num[HN-1].patt&&num[i].patt!=-1)
                                        return 133000+(num[i].patt);
                        return 63000+(num[i].patt);
                }
        }
        return res;
}
//      printf("straight check : ");
//      for(i=0;i<HN;i++)
//              printf("%d ",num[i]);
int flush(ocd num[HN],int res)
{
        int i,j;
        for(i=4;i<HN;i++)
        {
                if(num[i].patt==num[i-1].patt&&num[i].patt==num[i-2].patt&&num[i].patt==num[i-3].patt&&num[i].patt==num[i-4].patt&&num[i].patt!=-1)
                        return 70000+num[HN-1].patt;
        }
        return res;
}
int res_sort(data *dat)
{
        int i,temp,j,temp_score[PLY];
//      printf("res sor t check");
        for(i=0;i<PLY;i++)
        {
                dat->std_res[i]=i;
                temp_score[i]=dat->res[i];
        }
        for(i=0;i<PLY;i++)
        {
                for(j=i+1;j<PLY;j++)
                {

                        if(temp_score[i]>temp_score[j])
                        {
                                temp=dat->std_res[j];
                                dat->std_res[j]=dat->std_res[i];
                                dat->std_res[i]=temp;
                                temp=temp_score[j];
                                temp_score[j]=temp_score[i];
                                temp_score[i]=temp;
                        }
                }
        }
}
int final(data *dat,ocd **pc)
{
        dat->cheat=2;
        tprint(dat,pc,2);
        printf("승자는 ");
        printf("플레이어 %d , 족보는 [",dat->std_res[PLY-1]+1);
        check(dat,pc,dat->std_res[PLY-1],2);
        check_print(dat,pc,dat->std_res[PLY-1]);
        printf(" ] 입니다~\n");
}
int tprint(data *dat,ocd **pc,int opc)
{
        int p;
        enter();
        if(opc>=0)
        {
                for(p=PLY-1;p>=0;p--)
                {
                        print(dat,pc,p);
                        if(dat->pl_stat[p]!=2)
                        {
                                printf("        ");
                                check(dat,pc,p,opc);
                                check_print(dat,pc,p);
                                printf("\n");
                                if(p==0&&opc!=2)
                                {
                                        printf("        ▶ 내 족보 :    ");
                                        check(dat,pc,p,1);
                                        check_print(dat,pc,p);
                                        printf("\n");
                                }
                        }
                        else
                        {
                                printf("        포기");
                                printf("\n");
                        }
                        printf("\n");
                }
        }
        else
        {
                for(p=PLY-1;p>=0;p--)
                {
                        print(dat,pc,p);
                        printf("\n");
                        printf("\n");
                }
        }
}
int batting(data *dat,ocd **pc,int opc)
{
        int i,j,p,dp,cp;
        p=dat->std_res[PLY-1];
//      for(i=0;i<PLY;i++)
//              printf("%d  ",dat->std_res[i]);
        for(i=0;i<PLY;i++)
        {
//              printf("%d  ",p);
                if(p==PLY)
                        p-=PLY;
                if(dat->pl_stat[p]!=2)
                {
                        tprint(dat,pc,opc);
                        printf("플레이어 %d 배팅 ",p+1);
                        if(p==0)
                        {
                                printf("(콜 :1 다이 : 2)   ");
                                scanf("%d",&dat->pl_stat[p]);
                                getchar();
                                fflush(stdin);
                        }
                        else
                        {
                                check(dat,pc,p,2);
                                dp=rand()%100;
                                cp=100-(dat->cn-3)*(dat->cn<7?10:20)+(dat->res[p]/850)+dp/10;
                                printf("cp:%d dp: %d",cp,dp);
                                usleep(1000000);
                                if(cp<dp)
                                {
                                        printf("   다이");
                                        dat->pl_stat[p]=2;
                                }
                                else
                                {
                                        printf("   콜");
                                        dat->pl_stat[p]=1;
                                }
                                getchar();
                        }
                }
                p++;
                if(dat->pl_stat[0]+dat->pl_stat[1]+dat->pl_stat[2]+dat->pl_stat[3]+dat->pl_stat[4]==9)
                {
                        for(j=0;j<PLY;j++)
                        {
                                if(dat->pl_stat[j]==1)
                                        die_end(j);
                        }
                }
        }
}
int die_end(int j)
{
        printf("플레이어 %d를 제외한 모든 플레이어가 포기했습니다. \n 승자는 플레이어 %d 입니다! \n\n",j+1,j+1);
        exit(0);
}
int progress1(data *dat,ocd **pc)
{
        int i,j,opc=-1;
        for(i=0;i<4;i++)
        {
                distribute(dat,pc);
                for(j=0;j<PLY;j++)
                        pc[j][i].stat++;
        }
        tprint(dat,pc,opc);

        discard(dat,pc);
        sort(dat,pc);
        tprint(dat,pc,opc);
        open(dat,pc);
        sort(dat,pc);
        dat->cheat=1;
        tprint(dat,pc,opc);
        getchar();
}
int progress2(data *dat,ocd **pc)
{
        int i,opc=0,p;
        for(i=0;i<3;i++)
        {
                printf("\n%d장 째 카드받기",dat->cn+1);
                getchar();
                distribute(dat,pc);
                tprint(dat,pc,opc);
                batting(dat,pc,opc);
//              check(dat,pc);
                tprint(dat,pc,opc);
        }
        printf("마지막 카드받기");
        getchar();
        distribute(dat,pc);
        tprint(dat,pc,opc);
        batting(dat,pc,opc);
        final(dat,pc);
}
int enter()
{
        int i;
        for(i=0;i<100;i++)
                printf("\n");
}
int main()
{
        int i,p;
        data dat;
        ocd **pc;
        pc=(ocd **)malloc(sizeof(ocd)*PLY);
        for(i=0;i<PLY;i++)
                pc[i]=(ocd *)malloc(sizeof(ocd)*HN);
        set(&dat,pc);
        progress1(&dat,pc);
        progress2(&dat,pc);
        free(pc);
760 }
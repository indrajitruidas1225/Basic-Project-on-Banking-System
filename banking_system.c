#include<stdio.h>
#include<stdlib.h>
struct dob
{
    int date;
    int month;
    int year;
}db;
struct register_new
{
    char name[30];
    long long int mobile;
    long long int acc_no;
    long long int aadhar;
    int password;
    float balance;
    struct dob db;
};
typedef struct register_new regis;
void mini_statement();
int create_account();
void forget_password();
int deposit();
int withdraw();
int check_balance();
int main()
{
    int n;
    system("cls");
    while(1)
    {
        printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
        printf("   HDFC BANK\n");
        printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
        printf("\n1.Create a new account\n2.Deposit\n3.Withdraw\n4.Statement\n5.Balance Check\n6.Forget Password\nAnything else to exit\n");
        printf("\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:create_account();
            break;
            case 2:deposit();
            break;
            case 3:withdraw();
            break;
            case 4:mini_statement();
            break;
            case 5:check_balance();
            break;
            case 6:forget_password();
            break;
            default:exit(0);
        }
    }
}
int create_account()
{
    FILE *fp;
    regis reg;
    regis k;
    static int ac_no=4000321;
    long long int mobile,aadhar;
    int flag=0;
    fp=fopen("program.txt","rb");
    printf("Enter your name :\n");
    fflush(stdin);
    gets(reg.name);
    printf("Enter your aadhar number:\n");
    fflush(stdin);
    scanf("%lld",&aadhar);
    printf("Create a password :\n");
    scanf("%d",&reg.password);
    printf("Enter birth date:\n");
    scanf("%d",&reg.db.date);
    printf("Enter birth month:\n");
    scanf("%d",&reg.db.month);
    printf("Enter year:\n");
    scanf("%d",&reg.db.year);
    printf("Enter mobile number:\n");
    scanf("%lld",&mobile);
    while(fread(&k,sizeof(k),1,fp)>0)
    {
    	ac_no=k.acc_no;
	}
	ac_no++;
    reg.acc_no=ac_no;
    rewind(fp);
    while(fread(&k,sizeof(k),1,fp)>0)
    {
        if((mobile==k.mobile) || (aadhar==k.aadhar))
        {
            if(mobile==k.mobile)
            printf("This number is already registered !\nTry with different one\n");
            if(aadhar==k.aadhar)
            printf("This aadhar is already registered !\nTry with different one\n");
            flag=1;
            int m;
            printf("1.To Main Menu\n2.To Retry Creating account\nAnything else to exit\n");
            scanf("%d",&m);
            if(m==1)
            {
			    fclose(fp);
                main();
                return 0;
            }
            else if(m==2)
            {
                fclose(fp);
				create_account();
				return 0;
		    }
            else
            exit(0);
        }
    }
    fclose(fp);
    if(flag==0)
    {
        reg.mobile=mobile;
        reg.aadhar=aadhar;
        fp=fopen("program.txt","ab");
        fwrite(&reg,sizeof(reg),1,fp);
        printf("Account Created Successfully !\n");
        fclose(fp);
    }
}
void mini_statement()
{
    FILE *fp;
    long long int mobile;
    int passcode,flag=0;
    fp=fopen("program.txt","rb");
    rewind(fp);
    printf("Enter mobile :\n");
    scanf("%lld",&mobile);
    printf("Enter password:\n");
    scanf("%d",&passcode);
    regis rg;
    while(fread(&rg,sizeof(rg),1,fp)>0)
    {
        if(mobile==rg.mobile && passcode==rg.password)
        {
            system("cls");
            printf("Logged in Successfully !!!\n\n");
            printf("Name : %s\n",rg.name);
            printf("Account number : %lld\n",rg.acc_no);
            printf("DOB : %02d-%02d-%02d\n",rg.db.date,rg.db.month,rg.db.year);
            printf("Aadhar number : %lld\n",rg.aadhar);
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("Wrong id or password !\n");
        printf("1.To reset your password\n2.To Retry\nAnything else to exit\n");
        int k;
        scanf("%d",&k);
        if(k==1)
        forget_password();
        if(k==2)
        mini_statement();
        else
        exit(0);
    }
    fclose(fp);
}
void forget_password()
{
    long long int acc,aadhar;
    int date,month,year,flag=0;
    printf("Enter your account number :\n");
    scanf("%lld",&acc);
    printf("Enter your aadhar :\n");
    scanf("%lld",&aadhar);
    printf("Enter birth date : \n");
    scanf("%d",&date);
    printf("Enter birth month : \n");
    scanf("%d",&month);
    printf("Enter birth year : \n");
    scanf("%d",&year);
    FILE *fp;
    fp=fopen("program.txt","rb+");
    regis rg;
    while(fread(&rg,sizeof(rg),1,fp)>0)
    {
        if(acc==rg.acc_no && aadhar==rg.aadhar)
        {
            printf("Enter your new password:\n");
            fseek(fp,sizeof(rg)*(-1),SEEK_CUR);
            scanf("%d",&rg.password);
            fwrite(&rg,sizeof(rg),1,fp);
            printf("Password Changed Successfully !!!\n");
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("Something went wrong  ! Try again\n");
        printf("1.To retry password change\n2.To main menu\nAnything else to exit\n");
        int n;
        scanf("%d",&n);
        switch(n)
        {
            case 1:forget_password();
            break;
            case 2:main();
            break;
            default:exit(0);
        }
    }
    fclose(fp);
}
int deposit()
{
    FILE *fp;
    fp=fopen("program.txt","rb+");
    printf("Enter your account number :\n");
    long long int acc;
    scanf("%lld",&acc);
    printf("Enter your password : \n");
    int pass,f=0;
    scanf("%d",&pass);
    regis rg;
    while(fread(&rg,sizeof(rg),1,fp)>0)
    {
        if(acc==rg.acc_no && pass==rg.password)
        {
            printf("Enter amount to deposit : \n");
            float bal;
            scanf("%f",&bal);
            if(bal<=0)
            {
                printf("Amount can't be less than or equal to 0\n");
                printf("1.To retry deposit\n2.To main menu\nAnything else to exit\n");
                int n;
                scanf("%d",&n);
                if(n==1)
                {
                    fclose(fp);
                    deposit();
                    return 0;
                }
                else if(n==2)
                {
                    fclose(fp);
                    main();
                    return 0;
                }
                else
                exit(0);
            }
            fseek(fp,sizeof(rg)*(-1),SEEK_CUR);
            rg.balance=rg.balance+bal;
            fwrite(&rg,sizeof(rg),1,fp);
            printf("Amount deposited successfully !!!\n");
            f=1;
            break;
        }
    }
    if(f==0)
    {
        printf("Account number or password went wrong!\n");
        printf("1.To retry\n2.To main menu\nAnything else to exit\n");
        int n;
        scanf("%d",&n);
        if(n==1)
        {
            fclose(fp);
            deposit();
            return 0;
        }
        else if(n==2)
        {
            fclose(fp);
            main();
            return 0;
        }
        else
        exit(0);
    }
    fclose(fp);
}
int withdraw()
{
    FILE *fp;
    fp=fopen("program.txt","rb+");
    printf("Enter your account number :\n");
    long long int acc;
    scanf("%lld",&acc);
    printf("Enter your password : \n");
    int pass,f=0;
    scanf("%d",&pass);
    regis rg;
    while(fread(&rg,sizeof(rg),1,fp)>0)
    {
        if(acc==rg.acc_no && pass==rg.password)
        {
            printf("Enter amount to withdraw : \n");
            float bal;
            scanf("%f",&bal);
            if(bal<=0)
            {
                printf("Amount can't be less than or equal to 0\n");
                printf("1.To retry withdraw\n2.To main menu\nAnything else to exit\n");
                int n;
                scanf("%d",&n);
                if(n==1)
                {
                    fclose(fp);
                    withdraw();
                    return 0;
                }
                else if(n==2)
                {
                    fclose(fp);
                    main();
                    return 0;
                }
                else
                exit(0);
            }
            if(bal>rg.balance)
            {
                printf("Insufficient Balance !\n");
                printf("1.To retry withdraw\n2.To main menu\nAnything else to exit\n");
                int n;
                scanf("%d",&n);
                if(n==1)
                {
                    fclose(fp);
                    withdraw();
                    return 0;
                }
                else if(n==2)
                {
                    fclose(fp);
                    main();
                    return 0;
                }
                else
                exit(0);
            }
            fseek(fp,sizeof(rg)*(-1),SEEK_CUR);
            rg.balance=rg.balance-bal;
            fwrite(&rg,sizeof(rg),1,fp);
            printf("Amount withdrawn successfully !!!\n");
            f=1;
            break;
        }
    }
    if(f==0)
    {
        printf("Account number or password went wrong!\n");
        printf("1.To retry\n2.To main menu\nAnything else to exit\n");
        int n;
        scanf("%d",&n);
        if(n==1)
        {
            fclose(fp);
            withdraw();
            return 0;
        }
        else if(n==2)
        {
            fclose(fp);
            main();
            return 0;
        }
        else
        exit(0);
    }
    fclose(fp);
}
int check_balance()
{
    printf("Enter account number:\n");
    long long int ac;
    scanf("%lld",&ac);
    printf("Enter password:\n");
    int pass;
    scanf("%d",&pass);
    FILE *fp;
    regis rg;
    int f=0;
    fp=fopen("program.txt","rb");
    while(fread(&rg,sizeof(rg),1,fp)>0)
    {
        if(ac==rg.acc_no && pass==rg.password)
        {
            printf("Your balance is : %f\n",rg.balance);
            f=1;
            break;
        }
    }
    if(f==0)
    {
        printf("Account number or password went wrong!\n");
        printf("1.To retry\n2.To main menu\nAnything else to exit\n");
        int n;
        scanf("%d",&n);
        if(n==1)
        {
            fclose(fp);
            check_balance();
            return 0;
        }
        else if(n==2)
        {
            fclose(fp);
            main();
            return 0;
        }
        else
        exit(0);

    }
    fclose(fp);
}

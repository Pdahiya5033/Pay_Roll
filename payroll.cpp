#include<iostream>
#include<ctype.h>
#include<string.h>
#include<iomanip>
#include<fstream>
using namespace std;
class Employee
{
    private:
    char name[30],uniqueid[40],addr[80],dob[10];
    int age,expe;
    long unsigned int mobno;
    
    class Salary
    {
        public:
        long long unsigned int accno;
        char bank[30];
        float regular,bonus,referral,overtime;
        Salary()
        {
            regular=0;
            bonus=0;
            referral=0;
            overtime=0;
        }
    }s1;
    class Life
    {
        public:
        int status,plan;
        Life()
        {
            status=0;
            plan=0;
            
        }
    }l1;
    class Attendance
    {
        public:
        int entry,exit,day,month,year;
        Attendance()
        {
            entry=0;
            exit=0;
            day=0;
            month=0;
            year=0;
        }
    }att[30];
    public:
    void write(ofstream &os)
    {
        int x=0;
        os.write(name,strlen(name));
        os<<ends;
        os.write(dob,strlen(dob));
        os<<ends;
        strcat(dob,name);
        strcpy(uniqueid,dob);
        os.write(uniqueid,strlen(uniqueid));
        os<<ends;
        os.write((char*)&age,sizeof(age));
        os.write((char*)&expe,sizeof(expe));
        os.write((char*)&mobno,sizeof(mobno));
        os.write(addr,strlen(addr));
        os<<ends;
        os.write(s1.bank,strlen(s1.bank));
        os<<ends;
        os.write((char*)&s1.accno,sizeof(s1.accno));
        os.write((char*)&s1.regular,sizeof(s1.regular));
        os.write((char*)&s1.referral,sizeof(s1.referral));
        os.write((char*)&s1.overtime,sizeof(s1.overtime));
        os.write((char*)&s1.bonus,sizeof(s1.bonus));
        os.write((char*)&l1.status,sizeof(l1.status));
        os.write((char*)&l1.plan,sizeof(l1.plan));
        while(x<30)
        {
            os.write((char*)&att[x].entry,sizeof(att[x].entry));
            os.write((char*)&att[x].exit,sizeof(att[x].exit));
            os.write((char*)&att[x].day,sizeof(att[x].day));
            os.write((char*)&att[x].month,sizeof(att[x].month));
            os.write((char*)&att[x].year,sizeof(att[x].year));
            x++;
        }
    }
    int read(ifstream &is)
    {
        int x=0;
        is.get(name,30,0);
        name[is.gcount()]=0;
        is.ignore(1);
        is.get(dob,10,0);
        dob[is.gcount()]=0;
        is.ignore(1);
        is.get(uniqueid,40,0);
        uniqueid[is.gcount()]=0;
        is.ignore(1);
        is.read((char*)&age,sizeof(age));
        is.read((char*)&expe,sizeof(expe));
        is.read((char*)&mobno,sizeof(mobno));
        is.get(addr,80,0);
        addr[is.gcount()]=0;
        is.ignore(1);
        is.get(s1.bank,30,0);
        s1.bank[is.gcount()]=0;
        is.ignore(1);
        is.read((char*)&s1.accno,sizeof(s1.accno));
        is.read((char*)&s1.regular,sizeof(s1.regular));
        is.read((char*)&s1.referral,sizeof(s1.referral));
        is.read((char*)&s1.overtime,sizeof(s1.overtime));
        is.read((char*)&s1.bonus,sizeof(s1.bonus));
        is.read((char*)&l1.status,sizeof(l1.status));
        
        is.read((char*)&l1.plan,sizeof(l1.plan));
        
        while(x<30)
        {
            is.read((char*)&att[x].entry,sizeof(att[x].entry));
            is.read((char*)&att[x].exit,sizeof(att[x].exit));
            is.read((char*)&att[x].day,sizeof(att[x].day));
            is.read((char*)&att[x].month,sizeof(att[x].month));
            is.read((char*)&att[x].year,sizeof(att[x].year));
            x++;
        }
        return is.good();
    }
    
    friend istream & operator >> (istream &is,Employee &b);
    friend ofstream & operator << (ofstream &fos,Employee &b)
    {
        int i=0;
        b.write(fos);
        i++;
        return fos;
    }
    friend ifstream & operator >> (ifstream &fos,Employee &b)
    {
        int i=0;
        b.read(fos);
        i++;
        return fos;
    }
    friend int dele();
    friend int slip();
    friend int enex();
    friend void showatt();
    friend int readatt();
    friend int status_insu();
    friend int edit_info();
    friend int regi_insu();
};
istream & operator >> (istream &is,Employee &b)
{
    cout << "Name : ";
    is>>ws;
    is.get(b.name,30);
    cout << "Date of birth in format dd/mm/yy : ";
    is>>ws;
    is.get(b.dob,10);
    cout << "Age:";
    is>>ws>>b.age;
    cout << "Experience : ";
    is>>ws>>b.expe;
    cout << "Contact number :";
    is>>ws>>b.mobno;
    cout << "Address : ";
    is>>ws;
    is.get(b.addr,80);
    cout << "Bank name : ";
    is>>ws;
    is.get(b.s1.bank,30);
    cout << "Account number : ";
    is>>ws;
    is>>b.s1.accno;
    return is;
}

int dele()
{
    int k=0,j=0;
            char arr[30],ed_ch;
            Employee em[50];
            ifstream i_del("employees_data.txt",ios::binary);
            while(1)
            {
                i_del>>em[k];
                if(i_del.fail())
                break;
                k++;
            }
                do
                {
                    cout << "Enter uniqueid of employee whose account is to be deleted : ";
                    cin >> arr;
                    cout << "Want to edit choice? ";
                    cin >> ed_ch;
                } while (toupper(ed_ch)!='N');
                ofstream o_del("employees_data.txt",ios::trunc|ios::binary);
                for(int j=0;j<k;j++)
                {
                    if(strcmp(arr,em[j].uniqueid)!=0)
                    {
                        o_del << em[j];
                    }
                    
                } 
            if(j==k)
            return 1;
            else
            return 0;
}
int slip()
{
    char uniq[30],ed_ch;
    Employee em[50];
    int i=0,flag=0,k=0,total=0;
    do
    {
        cout << "Enter uniqueid : ";
        cin >> uniq;
        cout << "Want to edit your credentials?(y/n) ";
        cin >> ed_ch;
    } while (toupper(ed_ch)!='N');
    ifstream i_slip("employees_data.txt",ios::binary);
    while(1)
    {
        i_slip>>em[i];
        if(strcmp(em[i].uniqueid,uniq)==0)
        {
            cout << "Your total salary is Rs ";
            while(k<30)
            {
                int diff1,diff2;
                diff1=em[i].att[k].exit-em[i].att[k].entry;
                diff2=em[i].expe-3;
                if(diff1>8&&diff2>3)
                {
                    total+=(250+(diff2*50))*8+(diff1-8)*150;
                }
                else if(diff1>8&&diff2<3)
                {
                    total+=250*8+(diff1-8)*150;
                }
                else if(diff1<=8&&diff2>3)
                {
                    total+=(250+(diff2*50))*diff1;
                }
                else
                {
                    total+=250*diff1;
                }
                k++;
            }
            if(em[i].l1.plan==1)
            {
                total=total-2000;
            }
            else if(em[i].l1.plan==2)
            {
                total=total-4000;
            }
            else if(em[i].l1.plan==3)
            {
                total=total-8000;
            }
            cout << total << endl;
            flag=1;
            break;
        }
        if(i_slip.fail())
        break;
        i++;
    }
    
    if(flag==1)
    return 1;
    else
    return 0;

}
int enex()
{
    char uniq[30],ed_ch;
    Employee em[50];
    int i=0,flag=0;
    do
    {
        cout << "Enter your unique id : ";
        cin >> uniq;
        cout << "Want to edit your id?(y/n) ";
        cin >> ed_ch;
    } while (toupper(ed_ch)!='N');
    ifstream i_en("employees_data.txt",ios::binary);
    
    while(1)
    {
        i_en >> em[i];
        if(strcmp(em[i].uniqueid,uniq)==0)
        {
            int k=0,enexi;
            time_t ttime=time(0);
            tm *local_time=localtime(&ttime);
            cout << "Enter 1 if you are entering and 2 if you are leaving : ";
            cin >> enexi;
            k=0;
            while(k<=30)
            {
                if(em[i].att[k].day==0)
                {
                    if(enexi==1)
                    {
                        em[i].att[k].day=local_time->tm_mday;
                        em[i].att[k].month=1+local_time->tm_mon;
                        em[i].att[k].year=1990+local_time->tm_year;
                        em[i].att[k].entry=local_time->tm_hour;
                        
                    }
                    else if(enexi==2)
                    {
                        em[i].att[k].day=local_time->tm_mday;
                        em[i].att[k].month=1+local_time->tm_mon;
                        em[i].att[k].year=1990+local_time->tm_year;
                        em[i].att[k].exit=local_time->tm_hour;
                    }
                    flag=1;
                    break;
                }
                k++;
            }
            
            break;
            
            
            
        }
        if(i_en.fail())
        break;
        i++;
    }
    i_en.close();
    ofstream o_enex("employees_data.txt",ios::trunc|ios::binary);
    for(int j=0;j<=i;j++)
    o_enex << em[j];
    if(flag==1)
    return 1;
    else
    return 0;
}
void showatt()
{
    Employee em[50];
    int i=0,k=0,j=0;
    time_t ttime=time(0);
    tm *local_t=localtime(&ttime);
    ifstream i_show("employees_data.txt",ios::binary);
    while(1)
    {
        i_show >> em[i];
        while(k<30)
        {
            if(em[i].att[k].exit==0)
            {
                if(em[i].att[k-1].exit<local_t->tm_hour)
                break;
                else
                {
                    cout << em[i].name << endl;
                    j++;
                }
                
            }
            k++;
            
        }
        
        if(i_show.fail())
        {
            break;
        }
        i++;
    }
    i_show.close();
    if(j==0)
    cout << "Not even a single employee is present at this time." << endl;
}
int readatt()
{
    Employee em[50];
    int i=0,k=0,flag=0;
    char uniq[30],edit;
    do
    {
        cout << "Enter your uniqueid :";
        cin >> uniq;
        cout << "Want to edit ?(y/n) ";
        cin >> edit;
    } while (toupper(edit)!='N');
    
    ifstream i_readatt("employees_data.txt",ios::binary);
    while(1)
    {
        i_readatt >> em[i];
        
        if(strcmp(em[i].uniqueid,uniq)==0)
        {
            do
            {
                
                cout << em[i].att[k].day << " " << em[i].att[k].entry << " " << em[i].att[k].exit << endl;
                k++;
            }while(em[i].att[k].day!=0);
            flag=1;
            break;
        }
        if(i_readatt.fail())
        break;
        i++;
    }
    if(flag==1)
    return 1;
    else
    return 0;
}
int status_insu()
{
    char arr[30],edit;
    Employee em[50];
    int i=0,flag=0;
    do
    {
        cout <<  "Enter your uniqueid : ";
        cin >> arr;
        cout << "Do you want to edit your id?(y/n) ";
        cin >> edit;
    } while (toupper(edit)!='N');
    
    
    ifstream i_insu("employees_data.txt",ios::binary);
    while(1)
    {
        i_insu >> em[i];
        if(strcmp(em[i].uniqueid,arr)==0)
        {
            flag=1;
            if(em[i].l1.status==0)
            cout << "You don't have any active plan!" << endl;
            else
            {
                cout << "Your " << em[i].l1.plan << " active." << endl;
                
            }
            break;
        }
        if(i_insu.fail())
        break;
        i++;
    }
    if(flag==1)
    return 1;
    else
    return 0;
}
int edit_info()
{
    char arr[30],ed_id;
    Employee em[50],em1;
    int i=0,flag=0;
    do
    {
        cout << "Enter your uniqueid : ";
        cin >> arr;
        cout << "Want to edit your id?(y/n) ";
        cin >> ed_id;
    } while (toupper(ed_id)!='N');
    ifstream i_edit("employees_data.txt",ios::binary);
    
    while(1)
    {
        i_edit >> em[i];
        if(strcmp(arr,em[i].uniqueid)==0)
        {
            cout << "You can only edit following credentials : " << endl;
            flag=1;
            int ed_choice;
            cout << "Enter 1 for editing your name. " << endl;
            cout << "Enter 2 for editing your your cantact number." << endl;
            cout << "Enter 3 for editing your Address." << endl;
            cout << "Enter 4 for editing your Bank name and account number." << endl;
            cin >> ed_choice;
            if(ed_choice==1)
            {
                cout << "Enter your new name : ";
                cin >> em1.name;
                strcpy(em[i].name,em1.name);
                strcat(em[i].dob,em1.name);
                strcpy(em[i].uniqueid,em[i].dob);
                cout << "Your name has been edited successfully 😊" << endl;
            }
            else if(ed_choice==2)
            {
                cout << "Enter your new contact number : ";
                cin >> em1.mobno;
                em[i].mobno=em1.mobno;
                cout << "Your contact number has been edited successfully 😊" << endl;
            }
            else if(ed_choice==3)
            {
                cout << "Enter your new address " << endl;
                cin >> em1.addr;
                strcpy(em[i].addr,em1.addr);
                cout << "Your address has been edited successfully 😊" << endl;
            }
            else if(ed_choice==4)
            {
                cout << "Enter your new Bank name : ";
                cin >> em1.s1.bank;
                cout << "Enter your new account number : ";
                cin >> em1.s1.accno;
                strcpy(em[i].s1.bank,em1.s1.bank);
                em[i].s1.accno=em1.s1.accno;
                cout << "Your bank name and account number has been edited successfully 😊" << endl;
            }
        }
        if(i_edit.fail())
        break;
        i++;

    }
    ofstream o_edit("employees_data.txt",ios::trunc|ios::binary);
    for(int j=0;j<=i;j++)
    o_edit<<em[j];
    if(flag==1)
    return 1;
    else
    return 0;
}
int regi_insu()
{
    Employee em[50];
    char arr[30],ed_id,ed_insu;
    int i=0,flag=0,insu_ch;
    do
    {
        cout << "Enter your uniqueid : ";
        cin >> arr;
        cout << "Want to edit your id?(y/n) ";
        cin >> ed_id;
    } while (toupper(ed_id)!='N');
    ifstream i_regi("employees_data.txt",ios::binary);
    while(1)
    {
        i_regi >> em[i];
        if(strcmp(em[i].uniqueid,arr)==0)
        {
            flag=1;
            cout << "Here are the details of various insurance plans : " << endl;
            cout << "1. Rs 50 Lakhs insurance and monthly installment is Rs 2000." << endl;
            cout << "2. Rs 1 Crore insurance and monthly installment is Rs 4000." << endl;
            cout << "3. Rs 2 Crores insurance and monthly installment is Rs 8000." << endl;
            do
            {
                cout << "Enter your choice as per index in front of each choice : ";
                cin >> insu_ch;
                cout << "Do you want to edit your choice?(y/n) ";
                cin >> ed_insu;
            } while (toupper(ed_insu)!='N');
            if(insu_ch==1)
            {
                cout << "You have chosen Rs 50 Lakhs insurance plan." << endl;
                cout << "Rs 2000 will be automatically debited from your account monthly." << endl;
                em[i].l1.plan=1;
                em[i].l1.status=1;
            }
            else if(insu_ch==2)
            {
                cout << "You have chosen Rs 1 Crore insurance plan." << endl;
                cout << "Rs 4000 will be automatically debited from your account monthly." << endl;
                em[i].l1.plan=2;
                em[i].l1.status=1;
            }
            else if(insu_ch==3)
            {
                cout << "You have chosen Rs 2 Crores insurance plan." << endl;
                cout << "Rs 8000 will be automatically debited from your account monthly." << endl;
                em[i].l1.plan=3;
                em[i].l1.status=1;
            }
        }
        if(i_regi.fail())
        break;
        i++;
    }
    ofstream o_regi("employees_data.txt",ios::trunc|ios::binary);
    for(int j=0;j<=i;j++)
    o_regi << em[j];
    if(flag==1)
    return 1;
    else
    return 0;
}
int main()
{
    Employee em[10];
    int start_ch1,start_ch2,start_ch,i=0;
    cout << "Enter 1 for entering employees portal abd 2 for entering officials portal." << endl;
    cin >> start_ch;
    if(start_ch==1)
    {
        cout << "Enter 1 for printing your salary slip." << endl;
        cout << "Enter 2 for knowing your attendance." << endl;
        cout << "Enter 3 for knowing status of term life insurance." << endl;
        cout << "Enter 4 for editing your details." << endl;
        cout << "Enter 5 for registering in TERM LIFE INSURANCE." << endl;
        cout << "Enter 6 for marking your entry or leaving time." << endl;
        cout << "Enter 7 for knowing about salary terms and conditions." << endl;
        cin >> start_ch1;
        if(start_ch1==1)
        {
            int y=0;
            do
            {
                y=slip();
                if(y!=1)
                cout << "Please enter correct id! " << endl;
            } while (y!=1);
            
        }
        else if(start_ch1==2)
        {
            int y=0;
            do
            {
                y=readatt();
                if(y!=1)
                cout << "Please enter correct id!" << endl;
            } while (y!=1);
            
        }
        else if(start_ch1==3)
        {
            int y=0;
            do
            {
                y=status_insu();
                if(y!=1)
                cout << "Please enter correct id!" << endl;
            } while (y!=1);
        }
        else if(start_ch1==4)
        {
            int y=0;
            do
            {
                y=edit_info();
                if(y!=1)
                cout << "Please enter correct id!" << endl;
            } while (y!=1);
        }
        else if(start_ch1==5)
        {
            int y=0;
            do
            {
                y=regi_insu();
                if(y!=1)
                cout << "Please enter correct id!" << endl;
            } while (y!=1);
        }
        else if(start_ch1==6)
        {
            int y=0;
            do
            {
                y=enex();
                if(y!=1)                  
                cout << "Please enter correct id! " << endl;

            } while (y!=1);
            
            
        }
        else if(start_ch1==7)
        {
            cout << "Basic pay scale for each employee is Rs 250 per hour." << endl;
            cout << "Employees who have working experience greater than 3 years will get additional salary with increase by Rs 50 per hour for every passing year." << endl;
            cout << "It means that if an employee has experience of 4 years then he will be paid Rs 300 per hour as basic salary and next year he will be paid Rs 350 per hour." << endl;
            cout << "Additionally if any employee works for extra time he will get Rs 150 per hour." << endl;
        }
    }
    
    if(start_ch==2)
    {
        cout << "Enter 1 for adding new employee." << endl;
        cout << "Enter 2 for deleting employee record." << endl;
        cout << "Enter 3 for finding number of employees present." << endl;
        cin >> start_ch2;
        if(start_ch2==1)
        {
            char ano1;
            Employee em[10];
            ofstream op_file("employees_data.txt",ios::app|ios::binary);
            do
            {
                Employee em[10];
                cin >> em[i];
                op_file << em[i];
                i++;
                cout << "Want to add another record?(y/n) ";
                cin >> ano1;
            } while (toupper(ano1)=='Y');
            op_file.close();
        }
        else if(start_ch2==2)
        {
            int x=0;
            do
            {
                x=dele();
                if(x==1)
                cout << "Please enter correct id! " << endl;
                dele();
            } while (x==1);
            cout << "Record has been deleted successfully." << endl;
        }
        else if(start_ch2==3)
        {
            showatt();
        }
    }
    return 0;
}

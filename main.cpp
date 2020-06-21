/****************************************************************************************************************
**  Created: June 21st 2020                                                                                	*
**  Author: Sysadmin												*
** How much will I earn in a year depending on what happens.							*
** 1) Monthly earnings - fixed income 4500 USD - normal distribution						*
** 2) Monthly expenses - distribution by interval - Gaussian distribution, average value 2000, deviation 1500	*
** 3) Termination of the employment contract - discrete distribution						*
** 4) Additional salary - on call (business phone from work in case of emergency             			*
** - taking action e.g. at night or at the weekend), overtime - a discrete distribution				*
** 5) Change of the job - low probability (large earnings in the current company) / large change in salary,	*
** when it changes - 9000 USD - discrete distribution. 								*
** 6) Change of the department in current work - high probability 5000 USD  - discrete distribution		*
** 7) Graduation - very high probability - discrete distribution                                                *
** 8) Bank loan - average probability - discrete distribution				                        *
** 9) Jackpot win - low probability - discrete distribution                                 			*
** Time: 12 months = 1 year	    										*
** Measurements are made for 5000 samples.									*
** Maximum earnings are calculated for a value less than the minimum jackpot win.	        		*
** Classes quantity = 30											*
****************************************************************************************************************/

#include <iostream>
/** #include <stdio.h>  /// standard input/output in linux. **/
#include <cstdlib>
#include <cmath>
#include <fstream>

int change_of_department=0;
int change_of_the_job=0;
double probability_of_department_change=0.2;
double probability_of_graduation=0.9;
double probability_of_loan=0.5;
bool change1=false;
double Generator();
double MonthlyEarnings(int month); ///point number 1
double MonthlyExpenses(); ///point number 2
double ContractTermination(); ///point number 3
double AdditionalSalary(); ///point number 4
bool JobChange(); ///point number 5
bool DepartmentChange(); ///point number 6
bool Graduation(); ///point number 7
bool BankLoan(); ///point number 8
double JackpotWin(); ///point number 9
double GaussDistribution(double AverageEarnings, double deviation);

int main()
{
    int ClassesQuantity=30;
    double ClassesWidth;
    int l;
    int quantity[30];
    double Earnings[5000];

    for (int i=0; i<5000; i++)
    {
        change_of_department=0;
        change_of_the_job=0;
        probability_of_department_change=0.2;
        probability_of_graduation=0.9;
        probability_of_loan=0.5;

        Earnings[i]=Generator();
        std::cout<<"My earnings after a year: "<<Earnings[i]<<std::endl;
    }
    double minimum = Earnings[0];
    double maximum = Earnings[0];
    for(int i=1;i<5000;i++)
    {
      if(minimum>Earnings[i])
      minimum = Earnings[i];
      if(maximum<Earnings[i]&&Earnings[i]<5000000.0)
      maximum = Earnings[i];
    }
    ClassesWidth=(maximum-minimum)/ClassesQuantity;
    for (int j=0;j<5000; j++)
    {
        if (Earnings[j]<5000000.0)
        {
            l=int((Earnings[j]-minimum)/ClassesWidth);
            quantity[l]++;
        }
        else
        {
            quantity[30]++;
        }

    }
    std::ofstream file("results.csv", std::ofstream::out);

    for (int t=0; t<30; t++)
    {
        file<<"Class: "<<t<<"; "<<quantity[t]<<std::endl;
        std::cout<<"Class: "<<t<<" quantity: "<<quantity[t]<<std::endl;

    }
    std::cout <<"The End."<<std::endl;
    std::cout<<"File results.csv contains simulated quantity of numbers in each class."<<std::endl;


    return 0;
}

double Generator ()
{
    double Earnings=0.0;

    for (int i=0; i<12; i++)
    {
        Earnings=Earnings+MonthlyEarnings(i)+AdditionalSalary()+Graduation();
        Earnings=Earnings-MonthlyExpenses()-ContractTermination()-BankLoan();

        for (int j=0; j<4; j++)
        {
            Earnings=Earnings+JackpotWin();
        }
    }
 return Earnings;
}

///point number 1
double MonthlyEarnings(int month)
{
    double salary=4500.0+2000.0*change_of_department+5000.0*change_of_the_job;

    if(month%12==0 && month>0){
    bool change=true;
       if(change==true)
       {
           change1=JobChange();
          if(change1==true)
          {
              change=false;
              change_of_the_job++;
              change_of_department=0;
          }
       }
       if(DepartmentChange()==true&&change==true)
       {
          change_of_department++;
       }
     }
    return salary;
}

///point number 2
double MonthlyExpenses()
{
    double expenses=GaussDistribution(2000.0,1500.0);
    return expenses;
}

///point number 3
double ContractTermination()
{
    double contract_termination=0.0;
    double probability_of_termination=0.6;
    double r1=0.0;
    r1=rand()/double(RAND_MAX);
    if(r1<probability_of_termination)
    {
        contract_termination=rand()/double(RAND_MAX)*(4500.0-600.0)+600.0;
    }
    return contract_termination;
}

///point number 4
double AdditionalSalary()
{
    double onCall=0.0;
    double probability_of_additional_salary=0.3;
    double r2=0.0;
    r2=rand()/double(RAND_MAX);
    if(r2<probability_of_additional_salary)
    {
        onCall=rand()/double(RAND_MAX)*(2500.0-1200.0)+1200.0;
    }
    return onCall;
}

///point number 5
bool JobChange()
{
    bool JobChange=false;
    double probability_of_change=0.01;
    double r3=0.0;
    r3=rand()/double(RAND_MAX);
    if(r3<probability_of_change)
    {
        JobChange=true;
    }
    return JobChange;
}

///point number 6
bool DepartmentChange()
{
    bool change_of_the_department=false;
    double r4=0.0;
    r4=rand()/double(RAND_MAX);

    if(r4<probability_of_department_change)
    {
        probability_of_department_change=0.2;
        change_of_the_department=true;
    }
    else
    {
        probability_of_department_change=probability_of_department_change+0.1;
    }
    return change_of_the_department;
}

///point number 7
bool Graduation()
{
    bool Graduation=false;
    double r5=0.0;
    r5=rand()/double(RAND_MAX);

    if(r5<probability_of_graduation)
    {
        probability_of_graduation=0.9;
        Graduation=true;
    }
    else
    {
        probability_of_graduation=probability_of_graduation+0.1;
    }
    return Graduation;
}

///point number 8
bool BankLoan()
{
    bool loan=false;
    double r6=0.0;
    r6=rand()/double(RAND_MAX);

    if(r6<probability_of_loan)
    {
        probability_of_loan=0.5;
        loan=true;
    }
    else
    {
        probability_of_loan=probability_of_loan+0.1;
    }
    return loan;
}

///point number 9
double JackpotWin()
{
    double win=0.0;
    double probability_of_win=0.000001;
    double r7=0.0;
    r7=rand()/double(RAND_MAX);
    if(r7<probability_of_win)
    {
        win=rand()/double(RAND_MAX)*(15000000.0-5000000.0)+5000000.0;
    }
    return win;
}

double GaussDistribution(double AverageEarnings, double deviation)
{
    double pii=3.1415927;
    double r_max=RAND_MAX;
    return (double)round(deviation*sqrt(-2.0*log((rand()+1.0)/r_max))*sin(2.0*pii*rand()/r_max)+AverageEarnings);
}

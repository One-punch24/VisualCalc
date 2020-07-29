#include <iostream>
#include<cmath>
using namespace std;

/*����Ĵ�С,�������Ĵ�С*/
const int n = 5;

/*ͨ������������������ֵ���������*/
double MAX(double a[n])
{
    double max = 0;
    int i;
    double abs_value;
    for (i = 0; i<n; i++)
    {	
    	abs_value = fabs(a[i]);
        if (abs_value > max)
            max = abs_value;
    }
    return max;
}


 /*��˹-���¶�������*/
void Gauss_Seidel(double a[n][n], double b[n])
{
    int num = 0; /*��������*/
    double accuracy = 0.0000001; /*����*/
    double c;
    int i, j;
    double g;
    int count = 0;
    
    double diff; /*��*/
    int flag; /*ѭ��������־*/
    double x0[n];
    double x1[n] = { 0 };
    
    /*�ж�ϵ�������Ƿ��ϸ�Խ�ռ��*/
    for(i = 0;i < n;i++)
	{
		g = 0.0;
		
		for(j = 0;j < n;j++)
		{
			if(i != j)
			g += fabs(a[i][j]);
			}	
		if(g >= fabs(a[i][i]))
			count++;
	 } 
    
    if(count != 0)
    	{
		cout<<"ϵ�������ϸ�Խ�ռ�ţ����Է�������ܲ��������޽�."<<endl;
		
		}
	/*��������*/
    do {
        num++;          
        /*��������*/
        for (j = 0; j<n; j++)
            {
			x0[j] = x1[j];	
        }
        /*�����������*/
        for (i = 0; i<n; i++)
        {
            double sum = 0;
            double sum_new = 0;
            for (j = 0; j<=i - 1; j++)
            {
                sum += a[i][j] * x1[j];
            }
            for (j = i + 1; j<n; j++)
                sum_new += a[i][j] * x0[j];

            x1[i] = (b[i] - sum - sum_new) / a[i][i];
       
        }

        c = fabs(MAX(x1) - MAX(x0));    /*������*/                            
    
        diff = fabs(c - accuracy);    /*�뾫�Ƚ��бȽ�*/                       
    
        if (diff < accuracy||num >= 10000)
            flag = 0;
        else
            flag = 1;
    } while (flag);                                 

    /*������*/
   cout<<"���Է�����Ľ��ƽ����£�"<<endl;  
 	for(i = 0; i < n; i++)
	 {
	 	cout<< "x" << i + 1 << " = " << x1[i] << endl;
	  } 
}



/*��˹��Ԫ��*/
void Gauss_Eliminate(double a[n][n],double b[n])
{
	int i,j,k;
	double x0[n];/*�洢�����б任��ϵ�������������*/
	double x[n];/*�洢��*/ 
	/*�ж��Ƿ����ʹ�ø�˹��Ԫ��*/
	for(i = 0;i < n;i++)
	{
		if(a[i][i]==0)
		{
			cout<<"�÷����鲻��ʹ�ø�˹��Ԫ��"<<endl;
			return;
		}
	}
	
	/*��Ԫ����*/
	for(k = 0;k < n - 1;k++)
	{
		/*�����k���б任��ϵ��*/
		for(i = k + 1;i < n;i++)
		{
			x0[i] = a[i][k] / a[k][k];
		}
		
		/*��k����Ԫ*/
		for(i = k + 1;i < n;i++)
		{
			for(j = 0;j < n;j++)
			{
				a[i][j] = a[i][j] - x0[i] * a[k][j];
			}
			b[i] = b[i] - x0[i] * b[k];
		}
	}
	
	x[n - 1] = b[n - 1] / a[n - 1][n - 1];
	for(i = n -2;i >= 0;i--)
	{
		double sum = 0;
		for(j = i + 1;j < n;j++)
		{
			sum = sum + a[i][j] * x[j];
		}
		x[i] = (b[i] - sum) / a[i][i];
	}
	
	cout<<"���Է�����Ľ��ƽ����£�"<<endl;
	for(i = 0;i < n;i++)
	{
		cout<<"x"<<i + 1<<" = "<<x[i]<<endl;
	}
 } 
 
 
 
 /*���ռ��㺯��*/
void linesolve(double a[n][n],double b[n])
{
	int i,j;
	double flag;
	int count = 0;
	for(i=0;i<n;i++)
	{
		flag = 0.0;
		for(j=0;j<n;j++)
		{
			if(i!=j)
			{
				flag = flag + fabs(a[i][j]);
			}
			
		}
		if(flag>=fabs(a[i][i]))
		count++;
	 } 
	 
	if(count==0)
    	Gauss_Seidel(a, b);
    else if(count!=0)
    	Gauss_Eliminate(a,b);
    cout<<endl;
 } 
 
 
 
// int main()
// {
//     double a[n][n] = {7,3,4,6,4,8,3,3,-1,-9,-66.322,1,30,52,-90,20,5,6,9,8,0,1,36,5,-6};
//  	double b[n]= {-5,-6,81,70,99};
//  	
//     linesolve(a,b);
//    
//     return 0;
// }


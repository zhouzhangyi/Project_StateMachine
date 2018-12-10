#include<iostream>
#include<sys/time.h>
#include<sys/select.h>
#include<time.h>
#include<stdio.h>
#include"StateMachine.h"
#include"StateInfo.h"
using namespace std;

/*******************************
  @功能：定时器，通过调用select延时，实现定时器功能
  @入参：seconds---延时的时间（秒），数据类型为int
         mseconds----延时的时间(毫秒)，数据类型为int
  @返回值：无
*******************************/
void setTimer(int seconds,int mseconds)
{
	struct timeval temp;

	temp.tv_sec = seconds;
	temp.tv_usec = mseconds;

	select(0,NULL,NULL,NULL,&temp);

	return ;
}

/*******************************
@名称：main
@功能：
@入参：无
@返回值：0
*******************************/

int main(void)
{
	unsigned int i = 0;
	
    StateMachine MyStateMachine(MyStateTable,5,MyTransitionTable,4);
	
	cout<<"......这是一个状态机设计和演示如何调用状态机的例子......"<<endl;
	cout<<"状态机的总状态个数为："<<MyStateMachine.Number_State<<endl;
	cout<<"状态机的总转移个数为："<<MyStateMachine.Number_Trans<<endl;
    
	//此例中设置为运行20个周期
	for(i = 0;i<20;i++)
	{
		setTimer(1,0);
		cout<<"\n当前运行周期为："<<i<<endl;
		MyStateMachine.StateMachine_Schedule();
	}
    
	cout<<"......已演示完毕......"<<endl;
	
	return 0;
}

#include"StateMachine.h"
#include<iostream>
using namespace std;

/********************************
@名称: Init_To_Stand_ConditionFunc
@功能：初始状态至待机状态转移条件函数
@入参: 无
@返回值:是否切换判断结果（true表示切换，false表示不切换）
********************************/
bool Init_To_Stand_ConditionFunc()
{
	static unsigned int cnt = 0; 
	//5个周期后切换到Stand状态
	if(cnt++ >= 4)
	{
		cout<<"已满足从初始状态至待机状态的切换条件"<<endl;
	    return true;
	}
	else
	{
		cout<<"未满足从初始状态至待机状态的切换条件"<<endl;
		return false;
	}
}

/********************************
@名称: Init_To_Stand_ActionFunc
@功能：初始状态至待机状态转移动作函数
@入参: 无
@返回值:无
********************************/
void Init_To_Stand_ActionFunc()
{
	cout<<"即将由初始状态切换至待机状态"<<endl;
}

/********************************
@名称: InitState_RunFunc
@功能：初始状态运行函数
@入参: 无
@返回值:无
********************************/
void InitState_RunFunc()
{
	cout<<"当前状态为初始状态"<<endl;
}

/********************************
@名称: Init_To_Start_ConditionFunc
@功能：初始状态至起动状态转移条件函数
@入参: 无
@返回值:是否切换判断结果（true表示切换，false表示不切换）
********************************/
bool Init_To_Start_ConditionFunc()
{
	static unsigned int cnt = 0; 
    //5个周期后切换到Stand状态
	if(cnt++ >= 4)
	{
		cout<<"已满足从初始状态至起动状态的切换条件"<<endl;
		return true;
	}
    else
	{
		cout<<"未满足从初始状态至起动状态的切换条件"<<endl;
		return false;
	}
}

/********************************
@名称: Init_To_Start_ActionFunc
@功能：初始状态至起动状态转移动作函数
@入参: 无
@返回值:无
********************************/
void Init_To_Start_ActionFunc()
{
	cout<<"即将由初始状态切换至起动状态"<<endl;
}   

/********************************
@名称: StartState_RunFunc
@功能：起动状态运行函数
@入参: 无
@返回值:无
********************************/
void StartState_RunFunc()
{
	cout<<"当前状态为起动状态"<<endl;
}

/********************************
@名称: StandState_RunFunc
@功能：待机状态运行函数
@入参: 无
@返回值:无
********************************/
void StandState_RunFunc()
{
	cout<<"当前状态为待机状态"<<endl;
}

/********************************
@名称: Start_To_Steady_ConditionFunc
@功能：起动状态至稳定状态转移条件函数
@入参: 无
@返回值:是否切换判断结果（true表示切换，false表示不切换）
********************************/
bool Start_To_Steady_ConditionFunc()
{
	static unsigned int cnt = 0; 
	
	//5个周期后切换到Stand状态
	if(cnt++ >= 4)
	{
		cout<<"已满足从起动状态至稳定状态的切换条件"<<endl;
		return true;
	}
	else
	{
		cout<<"未满足从起动状态至稳定状态的切换条件"<<endl;
		return false;
	}
} 

/********************************
@名称: Start_To_Steady_ActionFunc
@功能：起动状态至稳定状态转移动作函数
@入参: 无
@返回值:无
********************************/
void Start_To_Steady_ActionFunc()
{
	cout<<"即将由起动状态切换至稳定状态"<<endl;
}

/********************************
@名称: SteadyState_RunFunc
@功能：稳定状态运行函数
@入参: 无
@返回值:无
********************************/
void SteadyState_RunFunc()
{
	cout<<"当前状态为稳定状态"<<endl;
}

/********************************
@名称: Start_To_Stop_ConditionFunc
@功能：起动状态至停止状态转移条件函数
@入参: 无
@返回值:是否切换判断结果（true表示切换，false表示不切换）
********************************/
bool Start_To_Stop_ConditionFunc()
{
	static unsigned int cnt = 0;
    
	//运行5个周期后切换至停止状态
	if(cnt++ >= 4)
	{
		cout<<"已满足从起动状态至停止状态的切换条件"<<endl;
		return true;
	}
	else
	{
		cout<<"未满足从起动状态至停止状态的切换条件"<<endl;
		return false;
	}
}

/********************************
@名称: Start_To_Stop_ActionFunc
@功能：起动状态至停止状态转移动作函数
@入参: 无
@返回值:无
********************************/
void Start_To_Stop_ActionFunc()
{
	cout<<"即由起动状态将切换至停止状态"<<endl;
}

/********************************
@名称: StopState_RunFunc
@功能：停止状态运行函数
@入参: 无
@返回值:无
********************************/
void StopState_RunFunc()
{
	cout<<"当前状态为停止状态"<<endl;
}

/*外部输入的转移表，各个状态对应的转移应按优先级进排序，如果此处不排序，可以通过调用
 状态机类中的排序函数也能保证状态表是有序的。但作者认为在设计这个状态表时设计人员应该
 要对每个状态对应的转移有的优先级概念，优先级是设计出来的，是确定的*/		  
Ts_TransTable MyTransitionTable[4]=
{
	{Init_To_Start_ConditionFunc,Init_To_Start_ActionFunc,e_State_Init,e_State_Start,1},
	{Init_To_Stand_ConditionFunc,Init_To_Stand_ActionFunc,e_State_Init,e_State_Stand,2},
	
	{Start_To_Stop_ConditionFunc,Start_To_Stop_ActionFunc,e_State_Start,e_State_Stop,1},
	{Start_To_Steady_ConditionFunc,Start_To_Steady_ActionFunc,e_State_Start,e_State_Steady,2}
 
};

/*外部输入的状态表，状态机默认此表的的第一个状态为系统的初始状态，因此在设计时要注意第一
 个元素的选择*/
Ts_StateTable MyStateTable[5]=
{
	{e_State_Init,InitState_RunFunc},
	{e_State_Stand,StandState_RunFunc},
	{e_State_Start,StartState_RunFunc},
	{e_State_Steady,SteadyState_RunFunc},
	{e_State_Stop,StopState_RunFunc}
};

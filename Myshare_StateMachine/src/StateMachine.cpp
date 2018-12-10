#include"StateMachine.h"
#include<iostream>
#include<cstring>

using namespace std;

/********************************
@功能：构造函数，在构造对象时根据输入参数完成转移表（TransTable）和状态机表(StateMachineTable)的初始化，构建一个状态机
@入参：StateTable_In---构造对象用的状态表指针，数据类型为Ts_StateTable，该参数在实例化对象前需定义好
       TransTable_In---构造对象用的转移表指针，数据类型为Ts_TransTable，该参数在实例化对象前需定义好
@返回值:类的对象
********************************/
StateMachine::StateMachine(const Ts_StateTable *StateTable_In,const unsigned int StateNumber_In,const Ts_TransTable *TransTable_In,const unsigned int TransNumber_In)
{
    int i,j,k,t;

    /*初始化类中的成员初值为0*/
 	this->Number_Trans = 0u;
    this->Number_State = 0u;
    memset(this->TransTable,0,TransNumber_In);
    memset(this->StateMachineTable,0,StateNumber_In);
  
    /*将类中的转移表TransTable为入参TransTable_In，
	 转移表TransTable中的元素个数也与TransTable_In的元素个数相同*/
    while((i<NUMBER_MAX_TRANSITION)&&(this->Number_Trans<TransNumber_In)
		&&(TransTable_In[i].ConditionFunc != NULL))
    {
        Ts_TransTable *pTrans = NULL;
	    pTrans = &this->TransTable[this->Number_Trans++];
            
        if(pTrans != NULL)
        {
			pTrans->ConditionFunc = TransTable_In[i].ConditionFunc;
            pTrans->ActionFunc = TransTable_In[i].ActionFunc;
			pTrans->SourceState = TransTable_In[i].SourceState;
			pTrans->TargetState = TransTable_In[i].TargetState;
            pTrans->Priority = TransTable_In[i].Priority;				
      	}

        i++;
    }
    
    /*通过类自身的转移表TransTable和入参StatTable_In初始化状态机表，
	  状态机表的元素个数与StateTable_In的元素个数相同*/
	while((j<NUMBER_MAX_STATE)&&(this->Number_State<StateNumber_In))
	{
	    Ts_StateMachine_Table  *pState = NULL;
		pState = &this->StateMachineTable[this->Number_State++];

		if(pState != NULL)
		{
			pState->CurState = StateTable_In[j].State;
			pState->RunFunc = StateTable_In[j].RunningFunc;
            
			/*遍历转移表，当状态机表的当前状态与转移表的某条转移的源状态相同时，
			  将该转移表挂接到状态机中，同时更新状态机中该状态对应的转移个数*/
			for(k = 0;k < this->Number_Trans;k++)
			{
				if(this->TransTable[k].SourceState == pState->CurState)
				{
					pState->pTrans[pState->Internal_TransNumber++] = &this->TransTable[k];
				}
			}
		}

		j++;
	}

    /*对每个状态完成转移挂接后，对每个状态的转移拥有的所有转移进行排序，得到
	  每个状态的升序形式的转移条件*/
	for(t = 0;t < this->Number_State;t++)
	{
		if(this->StateMachineTable[t].pTrans != NULL)
		{
			this->InsertSort(this->StateMachineTable[t].pTrans,this->StateMachineTable[t].Internal_TransNumber);
		}
	}

    /*完成对象状态机表构建建后，将状态机系统的初始状态置为状态机表中的第一个状态，
	  因此，在配置状态表时要注意将初始状态放在第一个元素中 */
	this->CurrentState = this->StateMachineTable[0].CurState;
}

/*******************************
@名称：~StateMachine
@功能：析构函数
@入参：无
@返回值： 无
********************************/
StateMachine::~StateMachine()
{

}

/********************************
@名称:StateMachine_Schedule
@功能：状态机调度，通过每周期调用该函数，实现状态的判断和切换
@入参：无
@返回值:无
********************************/
void StateMachine::StateMachine_Schedule()
{
	unsigned int i,j;
    
	/*该运行周期内遍历状态机中的所有状态，当当前状态与状态机中的某个状态相同时，
	  则执行当前状态对应的运行函数*/
	for(i = 0;i<this->Number_State;i++)
	{
		if(this->CurrentState == this->StateMachineTable[i].CurState)
		{
			if(this->StateMachineTable[i].RunFunc != NULL)
			{
				this->StateMachineTable[i].RunFunc();
			}				
			
			/*当当前状态与状态机中的某状态相同时，执行完该状态对应的运行函数后，
			  遍历该状态对应的所有转移条件，若条件为真，则状态转至该转移对应的目标
			  状态，且执行转移动作函数*/
			for(j = 0;j<this->StateMachineTable[i].Internal_TransNumber;j++)
			{
			    if(this->StateMachineTable[i].pTrans[j]->ConditionFunc != NULL)
				{
					if(this->StateMachineTable[i].pTrans[j]->ConditionFunc())
					{
						this->CurrentState = this->StateMachineTable[i].pTrans[j]->TargetState;
						this->StateMachineTable[i].pTrans[j]->ActionFunc();
					
						break;
					}
				}
			}
			break;
		}
	}
}

/********************************
@名称: GetCurrentState
@功能：获取该状态机的当前状态,
       若要获取当前状态，则该函数的调用应放在StateMachine_Schedule之前
@入参：无
@返回值:状态机的当前状态
********************************/
Te_State StateMachine:: GetCurrentState()
{
    return this->CurrentState;
}

/********************************
@名称: InsertSort
@功能：折半插入排序
@入参: pTranTable---待排序的数组指针，数据类型为转移表指针数组
       Number---待排序数组的元素个数，数据类型为无符号整型
@返回值:无
********************************/
void StateMachine::InsertSort(pTs_TransTable *TransTable,const unsigned int Number)
{
	signed int i,j,Temp_Prio;

	pTs_TransTable Temp_Table = NULL;
	
    for(i = 1;i<Number;i++)
	{   
		Temp_Prio = TransTable[i]->Priority;
		Temp_Table = TransTable[i];
        j = i-1;

		while((j>=0) && (Temp_Prio < TransTable[j]->Priority))
		{
			TransTable[j+1] = TransTable[j];
			j--;
		}
	}

	TransTable[j+1] = Temp_Table;
}

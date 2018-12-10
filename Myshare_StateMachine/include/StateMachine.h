#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

#define NUMBER_MAX_STATE 1000  //定义最大状态数
#define NUMBER_MAX_TRANSITION 10000   //定义最多转移数
#define NUMBER_MAX_TRANSITION_PER_STATE 100   //定义每个状态所对应的转移数

typedef void (*VOIDFUNCTION)();
typedef bool (*BOOLFUNCTION)();

//自定义枚举类型，五个状态（此处与文档中的状态数相同，具体的状态个数设计者可以根据需要扩充）
typedef enum tag_State
{
    e_State_Init,
    e_State_Stand,
    e_State_Start,
    e_State_Steady,
    e_State_Stop
}Te_State;

//定义转移表结构体类型
typedef struct tag_Transition_Table
{
    BOOLFUNCTION ConditionFunc;    //转移条件函数
    VOIDFUNCTION ActionFunc;       //转移动作函数
    Te_State SourceState;          //源状态
    Te_State TargetState;          //目标状态
    unsigned int Priority;         //优先级
}Ts_TransTable,*pTs_TransTable;

//定义状态表
typedef struct tag_State_Table
{
    Te_State State;               //状态
    VOIDFUNCTION RunningFunc;     //该状态对应的运行函数
}Ts_StateTable;

//定义状态机表
typedef struct tag_StateMachine_Table
{
    Te_State CurState;                                       //当前状态
    VOIDFUNCTION RunFunc;                                    //当前状态的运行函数
    pTs_TransTable pTrans[NUMBER_MAX_TRANSITION_PER_STATE];  //当前状态所对应的转移
    unsigned int Internal_TransNumber;                                 //当前状态所对应的转移的个数
}Ts_StateMachine_Table;
 
class StateMachine
{
	public:
		StateMachine(const Ts_StateTable *StateTable_In,const unsigned int StateNumber_In,const Ts_TransTable *TransTable_In,const unsigned int TransNumber_In);
		~StateMachine();

	   	unsigned int Number_Trans;
	    unsigned int Number_State;
	    Ts_TransTable TransTable[NUMBER_MAX_TRANSITION];
	    Ts_StateMachine_Table  StateMachineTable[NUMBER_MAX_STATE];
		Te_State CurrentState;

		void StateMachine_Schedule();
		Te_State GetCurrentState();
		void InsertSort(pTs_TransTable *TransTable,const unsigned int Number);
};

#endif

//************************************************************
//  Data        :   2019/04/17
//  Programmer  :   Garfield.Lin
//  Function    :   Subprogram
//  MCU         :   MSP430G2553IPW28
//  Oscillator  :   Internal DOC 12MHZ
//  Battery     :   SDI INR18650-25R 7S1P
//  Version     :   V0.1
//
//
//****************************************************************

#include "system.h"
#include "Subprogram.h"
#include "initial.h"
/*
 const UINT16  Breathing[]={0xF50A, 0xEC13, 0xE01F, 0xD12E, 0xBF40,
 0xAA55, 0x926D, 0x7788, 0x59A6, 0x38C7,
 0x14EB, 0x38C7, 0x59A6, 0x7788, 0x926D,
 0xAA55, 0xBF40, 0xD12E, 0xE01F, 0xEC13};*/
/*
 const UINT16  Breathing[]={ 0xF000, 0xE01F, 0xD12E, 0xBF40,
 0xAA55, 0x926D, 0x7788, 0x59A6, 0x38C7,
 0x14EB, 0x38C7, 0x59A6, 0x7788, 0x926D,
 0xAA55, 0xBF40, 0xD12E, 0xE01F, 0xF000, 0xFFFF,};*/

const UINT16 BreathingTable_1200[] = { 575, 855, 1275, 1835, 2535, 3375, 4355,
                                       5475, 6735, 8135, 9675, 11355, 13175,
                                       15135, 17235, 19475, 21855, 24375, 27035,
                                       29835, 32775, 35855, 39075, 42435, 45935,
                                       49575, 53355, 57275, 61335, 65535, 61335,
                                       57275, 53355, 49575, 45935, 42435, 39075,
                                       35855, 32775, 29835, 27035, 24375, 21855,
                                       19475, 17235, 15135, 13175, 11355, 9675,
                                       8135, 6735, 5475, 4355, 3375, 2535, 1835,
                                       1275, 855, 575, 435 };// 可以优化

const UINT16 BreathingTable_800[] = {  575, 855, 1275, 1835, 5475, 8135,
                                       9675, 15135, 17235, 19475, 25000, 27035,
                                       39075, 49575, 53355, 57275, 61335, 65535,
                                       65535, 65535, 61335, 57275, 53355, 49575,
                                       45935, 42435, 39075, 27035, 25000, 19475,
                                       17235, 15135, 9675, 8135, 5475, 1835,
                                       1275, 855, 575, 455};// 可以优化



const UINT16 BreathingTable_1600[] = { 15, 175, 415, 735, 1135, 1615, 2175,     //7
                                       2815, 3535, 4335, 5215, 6175, 7215, 8335, //7
                                       9535, 10815, 12175, 13615, 15135, 16735,  //6
                                       18415, 20175, 22015, 23935, 25935, 28015,  //6
                                       30175, 32415, 34735, 37135, 39615, 42175,//6
                                       44815, 47535, 50335, 53215, 56175, 59215,//6
                                       62335, 65535, 65535,62335, 59215, 56175,       //5
                                       53215, 50335, 47535, 44815, 42175, 39615,//6
                                       37135, 34735, 32415, 30175, 28015, 25935,//6
                                       23935, 22015, 20175, 18415, 16735, 15135,//6
                                       13615, 12175, 10815, 9535, 8335, 7215,   //6
                                       6175, 5215, 4335, 3535, 2815, 2175, 1615,  //7
                                       1135, 735, 415, 175, 15 };// 可以优化   //5
//
//const UINT16 ChargeCapacity_2A[] = {  3100, 3150, 3185, 3220, 3255, 3290, 3325, 3360, 3395, 3430,
//                                      3465, 3500, 3508, 3516, 3524, 3532, 3540, 3548, 3556, 3564,
//                                      3572, 3580, 3587, 3594, 3601, 3608, 3615, 3622, 3627, 3632,
//                                      3637, 3642, 3647, 3652, 3657, 3662, 3667, 3672, 3677, 3682,
//                                      3687, 3692, 3697, 3702, 3707, 3712, 3717, 3722, 3727, 3732,
//                                      3737, 3742, 3750, 3758, 3766, 3774, 3782, 3790, 3798, 3806,
//                                      3814, 3822, 3830, 3838, 3846, 3854, 3862, 3870, 3878, 3886,
//                                      3894, 3902, 3910, 3918, 3926, 3934, 3942, 3950, 3958, 3966,
//                                      3974, 3982, 3992, 4002, 4012, 4022, 4032, 4042, 4052, 4062,
//                                      4072, 4082, 4092, 4102, 4112, 4122, 4132, 4139, 4146, 4153, 4160 };
//
//const UINT16 DischargeCapacity_10A[] = { 3075, 3090, 3105, 3120, 3135, 3150, 3165, 3180, 3195, 3210,
//                                         3225, 3231, 3237, 3243, 3249, 3255, 3261, 3267, 3273, 3279,
//                                         3285, 3291, 3297, 3303, 3309, 3315, 3321, 3327, 3333, 3339,
//                                         3345, 3351, 3357, 3363, 3369, 3375, 3381, 3387, 3393, 3399,
//                                         3405, 3413, 3421, 3429, 3437, 3445, 3453, 3461, 3469, 3477,
//                                         3485, 3493, 3501, 3509, 3517, 3525, 3533, 3541, 3549, 3557,
//                                         3565, 3573, 3581, 3589, 3597, 3605, 3613, 3621, 3629, 3637,
//                                         3645, 3653, 3661, 3669, 3677, 3685, 3693, 3701, 3709, 3717,
//                                         3725, 3733, 3741, 3749, 3757, 3765, 3773, 3781, 3789, 3797,
//                                         3805, 3825, 3845, 3865, 3885, 3905, 3925, 3945, 3965, 3985, 4005
//                                         };




RegisterGroup BQ76930Data;
_BatteryData BatteryData;
//_FlashData BQ76930ProtectData;

extern UINT16 RT3_AD;
extern unsigned char deta_cap_cnt;
extern uchar RS485_MODE;
extern union _LED_CTRL LED_CTRL;
//extern unsigned char  power_first_flag;

union FW_PF FW_PF_Status;       //  三级保护？

union HW_PT HW_PT_Status;       //BQ76930       二级保护
union FW_PT FW_PT_Status;       //CPU           一级保护

union _SW SW_Status;

UINT8 BreathingCycleCount = 0;
UINT8 SystemBootUpCount = 0;
UINT8 SystemMode = 0;
UINT16 SW_PressCount = 0;
UINT16 SW_ReleaseCount = 0;

UINT8 SystemFirstBoostUpCount = 0;
UINT8 BQ76930LoadFrequency = 0;
char BQ76930ADCOffset = 0;
signed short iGain = 0;

UINT16 Current_0A = 0;
UINT16 Cell_PF_UV_Count = 0;                                    //permanent fail safety under voltage
UINT16 Cell_PF_OV_Count = 0;            //4.23mV    -   8s      //permanent fail safety over voltage
UINT16 PF_OCC_Count = 0;                                         //permanent fail  over current in charges
UINT16 PF_OCD_Count = 0;                                         //permanent fail  over current in discharge
UINT16 PF_OTC_Count = 0;                                         //permanent fail safety over temperature cell
UINT16 PF_OTM_Count = 0;                                         //permanent fail safety over  temperature MOSFET
UINT16 PT_UV_Count = 0;
UINT16 PT_OV_Count = 0;
UINT16 PT_OCP_Count = 0;                                         //over charge current protection
UINT16 PT_ODP_Count = 0;                                         //over discharge current protection
UINT16 PT_OTCP_Count = 0;                                        //over temperature charge protection
UINT16 PT_OTDP_Count = 0;                                        //over temperature discharge protection
UINT16 PT_UTCP_Count = 0;                                        //under temperature charge protection
UINT16 PT_UTDP_Count = 0;                                        //under temperature discharge protection
UINT16 AL_OTDA_Count =0;
UINT16 AL_UTDA_Count =0;
UINT16 AL_OTMA_Count =0;
UINT16 PT_ODP_AutoReleaseCount = 0;
UINT16 HW_PT_OCD_SCD_AutoReleaseCount = 0;

extern UINT16 SleepCount;
//extern UINT8 SysRunCount;

//UINT16 BatteryModeChangeDelayCount = 0;
UINT16 BatteryCapacityRefreshCount = 0;
UINT16 DC_IN_Count = 0;
UINT16 DC_IN_Release_Count = 0;
UINT8 LED_Mode = 0;
UINT8 ChargeLED_Mode2_3_Count = 0;
UINT8 BatteryCapacity = 0;

UINT16 CellMiniVoltage = 0;
UINT16 CellMAXiVoltage = 0;
uchar MAXVoltage_Num = 0;                                   //fenglong 20190619
uchar Alert_count=0;

UINT8 TEST_1;

extern UINT16 Sleep_delay;

extern union SW_ALARM ALARM_PT_Status;        //警告值状态

UINT8 MosStatus = 0;


extern UINT16 his_data[FLASH_DATA_NUM];

#if 1     //fenglong 20190617

void Falsh_Write_Arr(unsigned int *Addr,unsigned int nValue[],unsigned char n)//向指定地址连续写一个数组,n代表字节数,不能超过32
{
    unsigned char i;
    FCTL1 = FWKEY+ERASE;
    FCTL3 = FWKEY;
    *Addr=0;                             //随便写入一个值进行清除，段A的操作比较特别，一般不对段A进行操作,因为段A中包含一些校验数据

    FCTL1 = FWKEY+WRT;                            // 允许写
    FCTL3 = FWKEY;                                // 解锁
    while((FCTL3&BUSY) == BUSY);                  //检测Flash是否在操作，连续写入时最好检测

    if(n>32)
    {
        return;
    }
    for( i=0;i<n;i++)
    {
        *Addr++ = nValue[i];
    }
    FCTL1 = FWKEY;                                //清除WRT，不能写
    FCTL3 = FWKEY+LOCK;                           // 锁定
    while((FCTL3&BUSY) == BUSY);
}
unsigned int Flash_Read_int(unsigned int *start_addr,uint8_t index)   //read one word
{
    unsigned int *flash_ptr = ((unsigned int *) start_addr) + index;
    return *flash_ptr;
}

#endif

//void Write_Flash(UINT16 Address, UINT8 value)
//{
//    char *Flash_ptr;                          // Flash pointer
//    unsigned int i;
//
//    Flash_ptr = (char *) Address;              // Initialize Flash pointer
//    FCTL1 = FWKEY + ERASE;                    // Set Erase bit
//    FCTL3 = FWKEY;                            // Clear Lock bit
//    *Flash_ptr = 0;                        // Dummy write to erase Flash segment
//
//    FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation
//
//    for (i = 0; i < 64; i++)
//    {
//        *Flash_ptr++ = value;                   // Write value to flash
//    }
//
//    FCTL1 = FWKEY;                     // Clear WRT bit (Clear Flash Write mode)
//    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit (LOCK Flash)
//}

//void LoadFlash(UINT8 *SourceAddr, UINT8 *SAVEAddr, UINT8 Length)        //copy
//{
//    UINT8 *SaveAddr;                         // Segment C pointer
//    UINT8 *Flash_ptrD;                         // Segment D pointer
//    UINT8 i;
//
//    //    Flash_ptrD = (char *) Segment_D;             // Initialize Flash segment D pointer
//    Flash_ptrD = SourceAddr;             // Initialize Flash segment D pointer
//    SaveAddr = SAVEAddr;
//
//    for (i = 0; i < Length; i++)
//    {
//        *SaveAddr = *Flash_ptrD;          // copy value segment C to segment D
//        Flash_ptrD = Flash_ptrD + 1;
//        SaveAddr = SaveAddr + 1;
//    }
//}



void SWInit(void)
{
    SW_Status.byte=0;


    P1IES &= ~BIT3;     // 上升沿触发        按键

//    P1IES |= BIT5;      // 下降沿触发
    P1IFG &= ~BIT3;     //清除IO口中断标志
    P1IE  |= BIT3;      // 中断使能

}

void ReadKey(void)
{
//    ALARM_PT_Status.Bits.AL_GLINT=1;                    //fenglong 20190702 测试用，测完删

    //    if((P1IN&=BIT3)!=BIT3)
//    uchar temp;
    UINT8 Buff_0, Buff_1;

        if(KEY_UP)
        {
            SW_PressCount = 0;
            SW_Status.bits.SW_Action = 0;

//            if( (SW_ReleaseCount>=TA0_2s) && ( (SystemMode == SystemBootUpWait)  || (SystemMode == SystemChargeMode)  ) )

            if(  (SW_ReleaseCount>=TA0_4s) && (SystemMode == SystemBootUpWait) )
            {
                SystemMode = SystemSleepMode;
                SW_Status.bits.SW_CKSOC=0;
            }
        }

        //fenglong 20190703
        if( (SW_PressCount>=TA0_40ms) && (RS485_MODE==1) && (SW_Status.bits.SW_Action ==0 ) && (SystemMode == SystemDischargeMode) )
        {
            RS485_MODE=0;
            SystemMode = SystemBootUpWait;
            SystemBootUpCount = 0;
            SW_Status.bits.SW_Action = 1;
            SW_Status.bits.SW_CKSOC=1;
            SW_PressCount=0;
        }


        if ((SW_PressCount>=TA0_40ms)&&(SystemMode == SystemSleepMode)&&(SW_Status.bits.SW_Action ==0 ))    //fenglong 20190621 按键100ms改40ms
        {
            SystemMode = SystemBootUpWait;
            SystemBootUpCount = 0;
            SW_Status.bits.SW_Action = 1;
            SW_Status.bits.SW_CKSOC=1;
            SW_PressCount=0;
//            ALARM_PT_Status.Bits.AL_GLINT=0;                    //fenglong 20190702 报警闪烁
        }

        if ((SW_PressCount>=TA0_1s5)&&(SystemMode == SystemBootUpWait)&&(SW_Status.bits.SW_Action ==0 ))
        {
            SystemMode = SystemBootUp;
//            SleepCount=0;
            SystemBootUpCount = 0;
            SW_Status.bits.SW_Action = 1;
            SW_Status.bits.SW_CKSOC=0;
            SW_PressCount=0;
        }


        if ((SW_PressCount>=TA0_1s5)&&(SystemMode == SystemDischargeMode)&&(SW_Status.bits.SW_Action ==0 ))
        {
            SystemMode = SystemSleepMode;
            SystemBootUpCount = 0;
            SW_Status.bits.SW_Action = 1;
            SW_PressCount=0;

            LED_CTRL.Word =0;
            LED_OFF();
            close_timer1();

//fenglong 20190729
            FW_PT_Status.Bits.PT_OCP =0;
			FW_PT_Status.Bits.PT_ODP =0;
			while (((HW_PT_Status.Bits.HW_OCD == 1) || (HW_PT_Status.Bits.HW_SCD == 1)))
			{
				Buff_1 = HW_PT_Status.Byte;
				BQ76930Data.SysStatus.StatusByte =0;
				//HW_PT_Status.Byte = 0x00;
				//HW_PT_Status.Bits.HW_OCD = 1;           //放电过流2级保护
				//HW_PT_Status.Bits.HW_SCD = 1;           //short current detection  短路监测电流
				if(HW_PT_Status.Bits.HW_OCD == 1)
				{
				  BQ76930Data.SysStatus.StatusBit.OCD = 1;
				}
				if(HW_PT_Status.Bits.HW_SCD == 1)
				{
				  BQ76930Data.SysStatus.StatusBit.SCD = 1;
				}
				Buff_0 = I2C_Master_TransmitByte(BQ76930_SysState_Addr,
											   BQ76930Data.SysStatus.StatusByte);

				if (Buff_0 == 0)
				{
				  HW_PT_Status.Byte = Buff_1;
				  HW_PT_Status.Bits.HW_OCD = 0;       //放电过流2级保护
				  HW_PT_Status.Bits.HW_SCD = 0;       //short current detection  短路监测电流
	//			  BQ76930Data.SysStatus.StatusByte =0;
				  BQ76930Data.SysStatus.StatusByte = HW_PT_Status.Byte;
				}
				WDTCTL = WDT_ARST_1000;
			}

        }

}

// 以上T0_COUNTER


// 以上T0_COUNTER

void SystemPF_Detect(void)
{
    UINT8 Buff_0, Buff_1;
    UINT16 crc16;
//=============PF Detect==============================
    if (Cell_PF_UV_Count >= TA0_8s)
        FW_PF_Status.Bits.PF_UV = 1;            //permanent fail safety under voltage

    if (Cell_PF_OV_Count >= TA0_8s)
        FW_PF_Status.Bits.PF_OV = 1;            //4.23mV    -   8s      //permanent fail safety over voltage

    if (PF_OCC_Count >= TA0_2s)
        FW_PF_Status.Bits.PF_OCC = 1;           //permanent fail  over current in charge

    if (PF_OCD_Count >= TA0_4s)                 //permanent fail  over current in discharge
        FW_PF_Status.Bits.PF_OCD = 1;           //fenglong 20190607

    if (PF_OTC_Count >= TA0_4s)
        FW_PF_Status.Bits.PF_OTC = 1;

    if (PF_OTM_Count >= TA0_4s)                 //permanent fail safety over  temperature MOSFET
        FW_PF_Status.Bits.PF_OTM = 1;





    if (FW_PF_Status.Word != 0)
    {
        if(his_data[PF_STATE_ADDR] != FW_PF_Status.Word)
        {
            crc16 =0;
            his_data[PF_STATE_ADDR] = FW_PF_Status.Word;
            his_data[FLASH_CYCLES_ADDR] = sys_cap.val.bat_cycle_cnt;
            his_data[CHG_CAP_CNT] = sys_cap.val.chg_cap_cnt;

            for(Buff_0 =0;Buff_0<FLASH_DATA_NUM-1;Buff_0++)                             //fenglong 20190615
            {
                crc16+= his_data[Buff_0];
            }
            his_data[HIS_CRC16] = crc16;
            __bic_SR_register(  GIE);       // Enter LPM3 w/ interrupt
            Falsh_Write_Arr((unsigned int *)Segment_C,his_data,FLASH_DATA_NUM);         //fenglong 20190615
            Falsh_Write_Arr((unsigned int *)Segment_D,his_data,FLASH_DATA_NUM);         //fenglong 20190615

            Falsh_Write_Arr((unsigned int *)Segment_C,his_data,FLASH_DATA_NUM);         //fenglong 20190615
            Falsh_Write_Arr((unsigned int *)Segment_D,his_data,FLASH_DATA_NUM);         //fenglong 20190615
            __bis_SR_register(  GIE);       // Enter LPM3 w/ interrupt
        }
    }

    if (FW_PF_Status.Word != 0)
        MCU_SAFE_High;
    else
        MCU_SAFE_Low;


//    if (SW_PressCount >= TA0_8s)        //Engineer Mode
//    {
//        CLR_PF();           //fenglong 20190708
//    }

//================PT Detect=======================

//1111111111111111111111111111
//因时间短先进SHIPPING,导致无法进PF_UV，故时间有2S延长到6s   20190704 fenglong
    if (PT_UV_Count >= TA0_2s)
    {
        FW_PT_Status.Bits.PT_UV = 1;
        if (SystemMode != SystemChargeMode)
        {
            SystemMode = SystemShipMode;
        }

    }
    if (PT_OV_Count >= TA0_2s)
    {
        FW_PT_Status.Bits.PT_OV = 1;

    }
    if((FW_PT_Status.Bits.PT_OV == 1) && (CellMAXiVoltage <= PT_OV_Release))
    {
        FW_PT_Status.Bits.PT_OV =0;
        PT_OV_Count =0;
    }

    if (PT_OCP_Count >= TA0_2s)
        FW_PT_Status.Bits.PT_OCP = 1;       //over charge current protection

    //over charge current protection
    if ((FW_PT_Status.Bits.PT_OCP == 1) && (DC_IN_Release_Count >= TA0_2s))
    {
        FW_PT_Status.Bits.PT_OCP = 0;       //over charge current protection
        PT_OCP_Count = 0;
    }

    if (PT_ODP_Count >= TA0_6s)
        FW_PT_Status.Bits.PT_ODP = 1;       //over discharge current protection
    //20190704
//    if ((FW_PT_Status.Bits.PT_ODP == 1) && (PT_ODP_AutoReleaseCount >= TA0_10s))        //fenglong 20190607
//    {
//        FW_PT_Status.Bits.PT_ODP = 0;       //over discharge current protection
//        PT_ODP_Count = 0;
//        PT_ODP_AutoReleaseCount = 0;
//    }

    if ( (PT_OTCP_Count >= TA0_2s) && (SystemMode == SystemChargeMode) )     //fenglong 20190705
        FW_PT_Status.Bits.PT_OTCP = 1;                          //over temperature charge protection

    if ((FW_PT_Status.Bits.PT_OTCP == 1)                        //over temperature charge protection
            && (BatteryData.TS1.TS1Word >= PT_OTCP_Release) && (RT3_AD <= PT_OTCP_Rel_RT3))//190902 wk(增加RT3)
    {
        FW_PT_Status.Bits.PT_OTCP = 0;
        FW_PT_Status.Bits.PT_OTSCP=0;
        PT_OTCP_Count = 0;
    }

    // 65温度告警
    if (AL_OTDA_Count >= TA0_1s)
    {
        ALARM_PT_Status.Bits.AL_OTDA=1;
    }
    if( (ALARM_PT_Status.Bits.AL_OTDA == 1) && (BatteryData.TS1.TS1Word > ALARM_OTDA_Default ) )    //fenglong 20190612
    {
        ALARM_PT_Status.Bits.AL_OTDA=0;
        AL_OTDA_Count=0;
    }
//    else                  //fenglong 20190612
//    {
//        ALARM_PT_Status.Bits.AL_OTDA=0;
//    }

    //-11GAOJING
    if (AL_UTDA_Count >= TA0_1s)
    {
        ALARM_PT_Status.Bits.AL_UTDA=1;
    }
    if( (ALARM_PT_Status.Bits.AL_UTDA == 1) && (BatteryData.TS1.TS1Word < ALARM_UTDA_Default) )      //fenglong 20190612
    {
        ALARM_PT_Status.Bits.AL_UTDA=0;
        AL_UTDA_Count=0;
    }
//    else                  //fenglong 20190612
//    {
//        ALARM_PT_Status.Bits.AL_UTDA=0;
//    }
    //82C MOS OTMA
    if (AL_OTMA_Count >= TA0_1s)
    {
        ALARM_PT_Status.Bits.AL_OTMA=1;
    }
    if( (ALARM_PT_Status.Bits.AL_OTMA == 1) && (BatteryData.TS2.TS2Word > ALARM_OTMA_Default) )
    {
        ALARM_PT_Status.Bits.AL_OTMA=0;
        AL_OTMA_Count=0;
    }
//    else
//    {
//        ALARM_PT_Status.Bits.AL_OTMA=0;
//    }

    if ( (PT_UTCP_Count >= TA0_2s) && (SystemMode == SystemChargeMode) )    //fenglong 20190705
    {
        FW_PT_Status.Bits.PT_UTCP = 1;                      //under temperature charge protection
    }


    if ((FW_PT_Status.Bits.PT_UTCP == 1)
            && (BatteryData.TS1.TS1Word <= PT_UTCP_Release) && (RT3_AD >= PT_UTCP_Rel_RT3))//190902 wk(增加RT3)
    {
        FW_PT_Status.Bits.PT_UTCP = 0;                      //under temperature charge protection
        FW_PT_Status.Bits.PT_UTSCP=0;
        PT_UTCP_Count = 0;
    }

    if (PT_OTDP_Count >= TA0_2s)
        FW_PT_Status.Bits.PT_OTDP = 1;                      //over temperature discharge protection

    if ((FW_PT_Status.Bits.PT_OTDP == 1)                    //over temperature discharge protection
            && (BatteryData.TS1.TS1Word >= PT_OTDP_Release) && (RT3_AD <= PT_OTDP_Rel_RT3))//190902 wk(增加RT3)
    {
        FW_PT_Status.Bits.PT_OTDP = 0;                      //over temperature discharge protection
        PT_OTDP_Count = 0;
    }

    if (PT_UTDP_Count >= TA0_2s)
        FW_PT_Status.Bits.PT_UTDP = 1;          //under temperature discharge protection

    if ((FW_PT_Status.Bits.PT_UTDP == 1)
            && (BatteryData.TS1.TS1Word <= PT_UTDP_Release) && (RT3_AD >= PT_UTDP_Rel_RT3))//190902 wk(增加RT3)
    {
        FW_PT_Status.Bits.PT_UTDP = 0;          //under temperature discharge protection
        PT_UTDP_Count = 0;
    }

//    11111111111111111111111111111111111

//=========Clear BQ76930 IC Error==================================???????????????????????

    if (BQ76930Data.SysStatus.StatusBit.DEVICE_XREADY == 1)
    {
//      LED_1_High;
        Buff_1 = BQ76930Data.SysStatus.StatusByte;
        BQ76930Data.SysStatus.StatusByte = 0x00;
        BQ76930Data.SysStatus.StatusBit.DEVICE_XREADY = 1;

        Buff_0 = I2C_Master_TransmitByte(BQ76930_SysState_Addr,
                                         BQ76930Data.SysStatus.StatusByte);
        if (Buff_0 == 0)
        {
            BQ76930Data.SysStatus.StatusByte = Buff_1;
            BQ76930Data.SysStatus.StatusBit.DEVICE_XREADY = 0;
        }
    }
    if (BQ76930Data.SysStatus.StatusBit.OVRD_ALERT == 1)
    {
        Buff_1 = BQ76930Data.SysStatus.StatusByte;
        BQ76930Data.SysStatus.StatusByte = 0x00;
        BQ76930Data.SysStatus.StatusBit.OVRD_ALERT = 1;

        Buff_0 = I2C_Master_TransmitByte(BQ76930_SysState_Addr,
                                         BQ76930Data.SysStatus.StatusByte);
        if (Buff_0 == 0)
        {
            BQ76930Data.SysStatus.StatusByte = Buff_1;
            BQ76930Data.SysStatus.StatusBit.OVRD_ALERT = 0;
        }
    }

//=============BQ76930 PT====================
            //cell over voltage 单体过压
    if ((HW_PT_Status.Bits.HW_OV == 1) && (CellMAXiVoltage <= PT_OV_Release))  // 过压保护恢复
    {
        Buff_1 = HW_PT_Status.Byte;
        //HW_PT_Status.Byte = 0x00;
        //HW_PT_Status.Bits.HW_OV = 1;        //cell over voltage 单体过压
        BQ76930Data.SysStatus.StatusByte =0x04;
        //BQ76930Data.SysStatus.StatusBit.OV = 1;
        Buff_0 = I2C_Master_TransmitByte(BQ76930_SysState_Addr,
                                         BQ76930Data.SysStatus.StatusByte);

        if (Buff_0 == 0)
        {
            HW_PT_Status.Byte = Buff_1;
            HW_PT_Status.Bits.HW_OV = 0;            //cell over voltage 单体过压

            BQ76930Data.SysStatus.StatusBit.OV =0;
        }
    }
            //cell under voltage 单节欠压恢复
    if ((HW_PT_Status.Bits.HW_UV == 1) && (CellMiniVoltage >= PT_UV_Release)
            && (SystemMode == SystemChargeMode))
    {
        Buff_1 = HW_PT_Status.Byte;
        //HW_PT_Status.Byte = 0x00;
        //HW_PT_Status.Bits.HW_UV = 1;        // cell under voltage
        BQ76930Data.SysStatus.StatusByte =0;
        BQ76930Data.SysStatus.StatusBit.UV = 1;
        Buff_0 = I2C_Master_TransmitByte(BQ76930_SysState_Addr,
                                         BQ76930Data.SysStatus.StatusByte);

        if (Buff_0 == 0)
        {
            HW_PT_Status.Byte = Buff_1;
            HW_PT_Status.Bits.HW_UV = 0;            //cell under voltage 单体过流
            BQ76930Data.SysStatus.StatusBit.UV =0;
        }
    }

}
void MosStatusDetect(void)
{
    UINT8 Buff_0,Buff_1;
    UINT8 SysCtrl2_Data;

    SystemPF_Detect();

    HW_PT_Status.Byte = BQ76930Data.SysStatus.StatusByte;
    Buff_1 = BQ76930Data.SysCtrl2.SysCtrl2Byte;             //MOS Status
    SysCtrl2_Data = Buff_1 & 0xF0;

    if (FW_PF_Status.Word == 0)
    {
        if (SystemMode == SystemChargeMode)
        {
            if ((HW_PT_Status.Bits.HW_OV == 0)              //cell over voltage 单体过压
                    && (FW_PT_Status.Bits.PT_OCP == 0)      //over charge current protection
                    && (FW_PT_Status.Bits.PT_OTCP == 0)     //over temperature charge protection
                    && (FW_PT_Status.Bits.PT_UTCP == 0)     //under temperature charge protection
                    &&(ALARM_PT_Status.Bits.HW_OTM == 0)
                    && (FW_PT_Status.Bits.PT_OV == 0)               // fenglong 20190605
                    && (FW_PT_Status.Bits.PT_OTSCP == 0)
                    && (FW_PT_Status.Bits.PT_UTSCP == 0)
                    && (HW_PT_Status.Bits.HW_OV == 0 )
//                  && (ALARM_PT_Status.Bits.AL_OV == 0)        //fenglong 20190621
                    )
            {
                SysCtrl2_Data = SysCtrl2_Data + BQ76930_CHG_ON;
            }
            else
            {
                _nop();
            }
        }
        if(SystemMode == SystemDischargeMode)
        {
            if ((HW_PT_Status.Bits.HW_UV == 0)          //cell under voltage 单体过流
                    && (FW_PT_Status.Bits.PT_UV == 0)     //fenglong 20190612
                    && (HW_PT_Status.Bits.HW_OCD == 0)      //放电过流2级保护
                    && (HW_PT_Status.Bits.HW_SCD == 0)      //short current detection  短路监测电流
                    && (FW_PT_Status.Bits.PT_ODP == 0)      //over discharge current protection
                    && (FW_PT_Status.Bits.PT_OTDP == 0)     //over temperature discharge protection
                    && (FW_PT_Status.Bits.PT_UTDP == 0)    //under temperature discharge protection
                    //&& (ALARM_PT_Status.Bits.HW_UV == 0)
//					&&(FW_PT_Status.Bits.PT_OTSDP == 0)
                    &&(ALARM_PT_Status.Bits.HW_OTM == 0)
                    )
            {
                SysCtrl2_Data = SysCtrl2_Data + BQ76930_DSG_ON;
            }
            else
            {
                _nop();
            }
        }
    }

    if (Buff_1 != SysCtrl2_Data)
    {
        Buff_0 = I2C_Master_TransmitByte(BQ76930_SYS_CTRL2_Addr, SysCtrl2_Data);
        if (Buff_0 == 0)
        {
            BQ76930Data.SysCtrl2.SysCtrl2Byte = SysCtrl2_Data;
        }
    }


}

void Update_BQ_Data(void)
{
    uchar result,s_state;
    unsigned int iTemp = 0;
    unsigned long lTemp = 0;
    result = I2C_Load_BQ76930(&BQ76930Data.VCell1.VCell1Byte.VC1_HI, VC1_HI_BYTE, 10);
    if(result ==0)
    {
        CellMiniVoltage = 0xffff;
        CellMAXiVoltage = 0x0000;
        iTemp = BQ76930Data.VCell1.VCell1Byte.VC1_HI;
        iTemp <<=8;
        iTemp += BQ76930Data.VCell1.VCell1Byte.VC1_LO;
        lTemp = ((unsigned long)iTemp * iGain)/1000;
        lTemp += BQ76930Data.ADCOffset;
        BatteryData.VCell1.VCell1Word = lTemp;//*382/1000;
        if(BatteryData.VCell1.VCell1Word<CellMiniVoltage)
        {
            CellMiniVoltage=BatteryData.VCell1.VCell1Word;
        }
        if(BatteryData.VCell1.VCell1Word>CellMAXiVoltage)
        {
            CellMAXiVoltage=BatteryData.VCell1.VCell1Word;
            MAXVoltage_Num=1;                                   //fenglong 20190619
        }

        if(BatteryData.VCell1.VCell1Word<his_data[HIS_Cell1MiniVoltage])                  //fenglong 20190617
        {
            his_data[HIS_Cell1MiniVoltage]=BatteryData.VCell1.VCell1Word;
        }
        if(BatteryData.VCell1.VCell1Word>his_data[HIS_Cell1MAXiVoltage])                  //fenglong 20190617
        {
            his_data[HIS_Cell1MAXiVoltage]=BatteryData.VCell1.VCell1Word;
        }

        iTemp = BQ76930Data.VCell2.VCell2Byte.VC2_HI;
        iTemp <<=8;
        iTemp += BQ76930Data.VCell2.VCell2Byte.VC2_LO;
        lTemp = ((unsigned long)iTemp * iGain)/1000;
        lTemp += BQ76930Data.ADCOffset;
        BatteryData.VCell2.VCell2Word = lTemp;//*382/1000;

        if(BatteryData.VCell2.VCell2Word<CellMiniVoltage)
        {
            CellMiniVoltage=BatteryData.VCell2.VCell2Word;
        }
        if(BatteryData.VCell2.VCell2Word>CellMAXiVoltage)
        {
            CellMAXiVoltage=BatteryData.VCell2.VCell2Word;
            MAXVoltage_Num=2;                                   //fenglong 20190619
        }

        if(BatteryData.VCell2.VCell2Word<his_data[HIS_Cell2MiniVoltage])                  //fenglong 20190617
        {
            his_data[HIS_Cell2MiniVoltage]=BatteryData.VCell2.VCell2Word;
        }
        if(BatteryData.VCell2.VCell2Word>his_data[HIS_Cell2MAXiVoltage])                  //fenglong 20190617
        {
            his_data[HIS_Cell2MAXiVoltage]=BatteryData.VCell2.VCell2Word;
        }

        iTemp = BQ76930Data.VCell3.VCell3Byte.VC3_HI;
        iTemp <<=8;
        iTemp += BQ76930Data.VCell3.VCell3Byte.VC3_LO;
        lTemp = ((unsigned long)iTemp * iGain)/1000;
        lTemp += BQ76930Data.ADCOffset;
        BatteryData.VCell3.VCell3Word = lTemp;//*382/1000;
        if(BatteryData.VCell3.VCell3Word<CellMiniVoltage)
        {
            CellMiniVoltage=BatteryData.VCell3.VCell3Word;
        }
        if(BatteryData.VCell3.VCell3Word>CellMAXiVoltage)
        {
            CellMAXiVoltage=BatteryData.VCell3.VCell3Word;
            MAXVoltage_Num=3;                                   //fenglong 20190619
        }

        if(BatteryData.VCell3.VCell3Word<his_data[HIS_Cell3MiniVoltage])                  //fenglong 20190617
        {
            his_data[HIS_Cell3MiniVoltage]=BatteryData.VCell3.VCell3Word;
        }
        if(BatteryData.VCell3.VCell3Word>his_data[HIS_Cell3MAXiVoltage])                  //fenglong 20190617
        {
            his_data[HIS_Cell3MAXiVoltage]=BatteryData.VCell3.VCell3Word;
        }

        iTemp = BQ76930Data.VCell5.VCell5Byte.VC5_HI;
        iTemp <<=8;
        iTemp += BQ76930Data.VCell5.VCell5Byte.VC5_LO;
        lTemp = ((unsigned long)iTemp * iGain)/1000;
        lTemp += BQ76930Data.ADCOffset;
        BatteryData.VCell4.VCell4Word = lTemp;//*382/1000;
        if(BatteryData.VCell4.VCell4Word<CellMiniVoltage)
        {
            CellMiniVoltage=BatteryData.VCell4.VCell4Word;
        }
        if(BatteryData.VCell4.VCell4Word>CellMAXiVoltage)
        {
            CellMAXiVoltage=BatteryData.VCell4.VCell4Word;
            MAXVoltage_Num=4;                                   //fenglong 20190619
        }

        if(BatteryData.VCell4.VCell4Word<his_data[HIS_Cell4MiniVoltage])                  //fenglong 20190617
        {
            his_data[HIS_Cell4MiniVoltage]=BatteryData.VCell4.VCell4Word;
        }
        if(BatteryData.VCell4.VCell4Word>his_data[HIS_Cell4MAXiVoltage])                  //fenglong 20190617
        {
            his_data[HIS_Cell4MAXiVoltage]=BatteryData.VCell4.VCell4Word;
        }

        result = I2C_Load_BQ76930(&BQ76930Data.VCell6.VCell6Byte.VC6_HI, VC6_HI_BYTE, 10);
        if(result ==0)
        {
            iTemp = BQ76930Data.VCell6.VCell6Byte.VC6_HI;
            iTemp <<=8;
            iTemp += BQ76930Data.VCell6.VCell6Byte.VC6_LO;
            lTemp = ((unsigned long)iTemp * iGain)/1000;
            lTemp += BQ76930Data.ADCOffset;
            BatteryData.VCell5.VCell5Word = lTemp;//*382/1000;
            if(BatteryData.VCell5.VCell5Word<CellMiniVoltage)
            {
                CellMiniVoltage=BatteryData.VCell5.VCell5Word;
            }
            if(BatteryData.VCell5.VCell5Word>CellMAXiVoltage)
            {
                CellMAXiVoltage=BatteryData.VCell5.VCell5Word;
                MAXVoltage_Num=5;                                   //fenglong 20190619
            }

            if(BatteryData.VCell5.VCell5Word<his_data[HIS_Cell5MiniVoltage])                  //fenglong 20190617
            {
                his_data[HIS_Cell5MiniVoltage]=BatteryData.VCell5.VCell5Word;
            }
            if(BatteryData.VCell5.VCell5Word>his_data[HIS_Cell5MAXiVoltage])                  //fenglong 20190617
            {
                his_data[HIS_Cell5MAXiVoltage]=BatteryData.VCell5.VCell5Word;
            }

            iTemp = BQ76930Data.VCell7.VCell7Byte.VC7_HI;
            iTemp <<=8;
            iTemp += BQ76930Data.VCell7.VCell7Byte.VC7_LO;
            lTemp = ((unsigned long)iTemp * iGain)/1000;
            lTemp += BQ76930Data.ADCOffset;
            BatteryData.VCell6.VCell6Word = lTemp;//*382/1000;
            if(BatteryData.VCell6.VCell6Word<CellMiniVoltage)
            {
                CellMiniVoltage=BatteryData.VCell6.VCell6Word;
            }
            if(BatteryData.VCell6.VCell6Word>CellMAXiVoltage)
            {
                CellMAXiVoltage=BatteryData.VCell6.VCell6Word;
                MAXVoltage_Num=6;                                   //fenglong 20190619
            }

            if(BatteryData.VCell6.VCell6Word<his_data[HIS_Cell6MiniVoltage])                  //fenglong 20190617
            {
                his_data[HIS_Cell6MiniVoltage]=BatteryData.VCell6.VCell6Word;
            }
            if(BatteryData.VCell6.VCell6Word>his_data[HIS_Cell6MAXiVoltage])                  //fenglong 20190617
            {
                his_data[HIS_Cell6MAXiVoltage]=BatteryData.VCell6.VCell6Word;
            }

            iTemp = BQ76930Data.VCell10.VCell10Byte.VC10_HI;
            iTemp <<=8;
            iTemp += BQ76930Data.VCell10.VCell10Byte.VC10_LO;
            lTemp = ((unsigned long)iTemp * iGain)/1000;
            lTemp += BQ76930Data.ADCOffset;
            BatteryData.VCell7.VCell7Word = lTemp;//*382/1000;
            if(BatteryData.VCell7.VCell7Word<CellMiniVoltage)
            {
                CellMiniVoltage=BatteryData.VCell7.VCell7Word;
            }
            if(BatteryData.VCell7.VCell7Word>CellMAXiVoltage)       //fenglong 20190525
            {
                CellMAXiVoltage=BatteryData.VCell7.VCell7Word;
                MAXVoltage_Num=7;                                   //fenglong 20190619
            }

            if(BatteryData.VCell7.VCell7Word<his_data[HIS_Cell7MiniVoltage])                  //fenglong 20190617
            {
                his_data[HIS_Cell7MiniVoltage]=BatteryData.VCell7.VCell7Word;
            }
            if(BatteryData.VCell7.VCell7Word>his_data[HIS_Cell7MAXiVoltage])                  //fenglong 20190617
            {
                his_data[HIS_Cell7MAXiVoltage]=BatteryData.VCell7.VCell7Word;
            }
        }
    }

    result = I2C_Load_BQ76930(&(BQ76930Data.SysStatus.StatusByte), SYS_STAT, 1);
    if(result ==0)
    {
        PT_ProtectRenew();
    }

    I2C_Load_BQ76930(&(BQ76930Data.SysCtrl1.SysCtrl1Byte),SYS_CTRL1,1);
    I2C_Load_BQ76930(&(BQ76930Data.SysCtrl2.SysCtrl2Byte),SYS_CTRL2,1);
    //VBAT TS
    result = I2C_Load_BQ76930(&(BQ76930Data.VBat.VBatByte.BAT_HI),BAT_HI_BYTE,2);
    if(result ==0)
    {
        iTemp = BQ76930Data.VBat.VBatByte.BAT_HI;
        iTemp <<=8;
        iTemp&=0xff00;
        iTemp |= BQ76930Data.VBat.VBatByte.BAT_LO;

        BatteryData.VBat.VBatWord = (unsigned long)iTemp*1532/1000 + BQ76930Data.ADCOffset;
    }
    result = I2C_Load_BQ76930(&(BQ76930Data.TS1.TS1Byte.TS1_HI),TS1_HI_BYTE,4);
    if(result ==0)
    {
        iTemp = BQ76930Data.TS1.TS1Byte.TS1_HI;
        iTemp <<=8;
        iTemp&=0xff00;
        iTemp |= BQ76930Data.TS1.TS1Byte.TS1_LO;
        BatteryData.TS1.TS1Word = iTemp;

        iTemp = BQ76930Data.TS2.TS2Byte.TS2_HI;
        iTemp <<=8;
        iTemp&=0xff00;
        iTemp |= BQ76930Data.TS2.TS2Byte.TS2_LO;

        BatteryData.TS2.TS2Word = iTemp;


        if(BatteryData.TS2.TS2Word<his_data[HIS_MOSFET_MAXTEMP])                  //fenglong 20190617
        {
            his_data[HIS_MOSFET_MAXTEMP]=BatteryData.TS2.TS2Word;
        }

    }
    //均衡读取
    I2C_Load_BQ76930(&(BQ76930Data.CellBal1.CellBal1Byte),CELLBAL1,1);
    I2C_Load_BQ76930(&(BQ76930Data.CellBal2.CellBal2Byte),CELLBAL2,1);

    if(BQ76930Data.SysStatus.StatusBit.CC_READY == 1)
    {
        result = I2C_Load_BQ76930(&(BQ76930Data.CC.CCByte.CC_HI), CC_HI_BYTE, 2);
        if(result ==0)
        {
            iTemp = BQ76930Data.CC.CCByte.CC_HI;
            iTemp <<=8;
            iTemp&=0xff00;
            iTemp |= BQ76930Data.CC.CCByte.CC_LO;
            if(iTemp >0x8000)
            {
                iTemp = 0-iTemp;
                BatteryData.CC.CCWord = (long)iTemp*844/250;
                BatteryData.CC.CCWord = 0-BatteryData.CC.CCWord;
            }
            else
            {
                BatteryData.CC.CCWord = (long)iTemp*844/250;
            }
        }
        s_state = 0x80;
        I2C_Master_TransmitByte(BQ76930_SysState_Addr, s_state);
    }
}


void PT_ProtectRenew(void)
{
    if(BQ76930Data.SysStatus.StatusBit.OV)
    {
        HW_PT_Status.Bits.HW_OV = 1;
    }
    else
    {
        HW_PT_Status.Bits.HW_OV = 0;
    }
    if(BQ76930Data.SysStatus.StatusBit.UV)
    {
        HW_PT_Status.Bits.HW_UV = 1;
    }
    else
    {
        HW_PT_Status.Bits.HW_UV =0;
    }
    if(BQ76930Data.SysStatus.StatusBit.OCD)
    {
        HW_PT_Status.Bits.HW_OCD =1;
    }
    else
    {
        HW_PT_Status.Bits.HW_OCD =0;
    }
    if(BQ76930Data.SysStatus.StatusBit.SCD)
    {
        HW_PT_Status.Bits.HW_SCD =1;
    }
    else
    {
        HW_PT_Status.Bits.HW_SCD =0;
    }
}

void GetADCGainOffset()
{
    I2C_Load_BQ76930(&(BQ76930Data.ADCGain1.ADCGain1Byte), ADCGAIN1,1);
    I2C_Load_BQ76930(&(BQ76930Data.ADCGain2.ADCGain2Byte), ADCGAIN2,1);
    I2C_Load_BQ76930(&(BQ76930Data.ADCOffset), ADCOFFSET,1);
}



void LoadFlashData(void)
{
    uchar s_status,s_ctrl,result;
    uchar bq_tmp[1];
    result = I2C_Load_BQ76930(&(BQ76930Data.SysCtrl1.SysCtrl1Byte),SYS_CTRL1,2);
    if(result ==0)
    {
        s_ctrl = BQ76930Data.SysCtrl1.SysCtrl1Byte&0x18;
        s_status = BQ76930Data.SysCtrl2.SysCtrl2Byte&0x40;  // 20190521
        if((s_ctrl != 0x18)||(s_status != 0x40)||(BQ76930Data.CCCfg!= 0x19))
        {
            BQ76930Data.SysCtrl1.SysCtrl1Byte =  BQ76930_SYS_CTRL1_Default;
            BQ76930Data.SysCtrl2.SysCtrl2Byte = BQ76930_SYS_CTRL2_Default;
            BQ76930Data.Protect1.Protect1Bit.RSNS=1;
            BQ76930Data.Protect1.Protect1Bit.SCD_DELAY = SCD_DEALY_200us;
            BQ76930Data.Protect1.Protect1Bit.SCD_THRESH = SCD_THRESH_200mV_100mV; 	//应客户要求修改 20190801 fenglong SCD_TRHESH_155mV_68mV;
            BQ76930Data.Protect1.Protect1Bit.RSVD=0;
            BQ76930Data.Protect2.Protect2Bit.RSVD=0;
            BQ76930Data.Protect3.Protect3Bit.RSVD=0;
            BQ76930Data.Protect2.Protect2Bit.OCD_DELAY = OCD_DELAY_40ms;
            BQ76930Data.Protect2.Protect2Bit.OCD_THRESH = OCD_THRESH_67mV_33mV;
            BQ76930Data.Protect3.Protect3Bit.OV_DELAY = OV_DELAY_1s;     //OV_DELAY_2s;      fenglong 20190612
            BQ76930Data.Protect3.Protect3Bit.UV_DELAY =  UV_DELAY_4s;      //fenglong 20190705
            BQ76930Data.CCCfg = 0x19;


            TEST_1 = I2C_Master_TransmitByte(
                    BQ76930_SYS_CTRL1_Addr,
                    BQ76930Data.SysCtrl1.SysCtrl1Byte);
            TEST_1 = I2C_Master_TransmitByte(
                    BQ76930_SYS_CTRL1_Addr + 1,
                    BQ76930Data.SysCtrl2.SysCtrl2Byte);
            TEST_1 = I2C_Master_TransmitByte(
                    BQ76930_SYS_CTRL1_Addr + 2,
                    BQ76930Data.Protect1.Protect1Byte);
            TEST_1 = I2C_Master_TransmitByte(
                    BQ76930_SYS_CTRL1_Addr + 3,
                    BQ76930Data.Protect2.Protect2Byte);
            TEST_1 = I2C_Master_TransmitByte(
                    BQ76930_SYS_CTRL1_Addr + 4,
                    BQ76930Data.Protect3.Protect3Byte);
            BQ76930Data.OVTrip = 0xB7;//4.22v
            BQ76930Data.UVTrip = 0x9E;//2.6v
            TEST_1 = I2C_Master_TransmitByte(BQ76930_SYS_CTRL1_Addr + 5,
                                             BQ76930Data.OVTrip);
            TEST_1 = I2C_Master_TransmitByte(BQ76930_SYS_CTRL1_Addr + 6,
                                             BQ76930Data.UVTrip);
            TEST_1 = I2C_Master_TransmitByte(
                                BQ76930_SYS_CTRL1_Addr + 7,
                                BQ76930Data.CCCfg);


            result = I2C_Load_BQ76930(&bq_tmp[0],BQ76930_SYS_CTRL1_Addr, 1);//C_CCFG
            if(result ==0)
            {
                if(bq_tmp[0] != BQ76930Data.SysCtrl1.SysCtrl1Byte)
                {
                    BQ76930Data.CCCfg =0;
                }
            }
            result = I2C_Load_BQ76930(&bq_tmp[0],BQ76930_SYS_CTRL1_Addr+1, 1);//C_CCFG
            if(result ==0)
            {
                if(bq_tmp[0] != BQ76930Data.SysCtrl2.SysCtrl2Byte)
                {
                    BQ76930Data.CCCfg =0;
                }
            }
            result = I2C_Load_BQ76930(&bq_tmp[0],BQ76930_SYS_CTRL1_Addr+2, 1);//C_CCFG
            if(result ==0)
            {
                if(bq_tmp[0] != BQ76930Data.Protect1.Protect1Byte)
                {
                    BQ76930Data.CCCfg =0;
                }
            }
            result = I2C_Load_BQ76930(&bq_tmp[0],BQ76930_SYS_CTRL1_Addr+3, 1);//C_CCFG
            if(result ==0)
            {
                if(bq_tmp[0] != BQ76930Data.Protect2.Protect2Byte)
                {
                    BQ76930Data.CCCfg =0;
                }
            }
            result = I2C_Load_BQ76930(&bq_tmp[0],BQ76930_SYS_CTRL1_Addr+4, 1);//C_CCFG
            if(result ==0)
            {
               if(bq_tmp[0] != BQ76930Data.Protect3.Protect3Byte)
               {
                   BQ76930Data.CCCfg =0;
               }
            }
            result = I2C_Load_BQ76930(&bq_tmp[0],BQ76930_SYS_CTRL1_Addr+5, 1);//C_CCFG
            if(result ==0)
            {
               if(bq_tmp[0] != BQ76930Data.OVTrip)
               {
                   BQ76930Data.CCCfg =0;
               }
            }
            result = I2C_Load_BQ76930(&bq_tmp[0],BQ76930_SYS_CTRL1_Addr+6, 1);//C_CCFG
            if(result ==0)
            {
               if(bq_tmp[0] != BQ76930Data.UVTrip)
               {
                   BQ76930Data.CCCfg =0;
               }
            }
            GetADCGainOffset();

            iGain = 365 + ((BQ76930Data.ADCGain1.ADCGain1Byte & 0x0C) << 1) + ((BQ76930Data.ADCGain2.ADCGain2Byte & 0xE0)>> 5);
        }
    }
}

void BQ_Shutdown(void)
{
    BQ76930Data.SysCtrl1.SysCtrl1Bit.SHUT_A=0;
    BQ76930Data.SysCtrl1.SysCtrl1Bit.SHUT_B=1;
    I2C_Master_TransmitByte(SYS_CTRL1, BQ76930Data.SysCtrl1.SysCtrl1Byte);
    _delay_cycles(250);
    BQ76930Data.SysCtrl1.SysCtrl1Bit.SHUT_A=1;
    BQ76930Data.SysCtrl1.SysCtrl1Bit.SHUT_B=0;
    I2C_Master_TransmitByte(SYS_CTRL1, BQ76930Data.SysCtrl1.SysCtrl1Byte);
}


//char DetectChargeCapacity(void)         //Battery  life
//{
//    UINT8 i;
//
//    for (i = 0; i <= 100; i++)
//    {
//        if (ChargeCapacity_2A[i] >= CellMiniVoltage)
//            return i;
//    }
//    return 100;
//}

//
//char DetectDischargeCapacity(void)
//{
//    UINT8 i;
//
//    for (i = 0; i <= 100; i++)
//    {
//        if (DischargeCapacity_10A[i] >= CellMiniVoltage)
//            return i;
//    }
//    return 100;
//}
void LED_DisplayRenew(void)
{
//    LED_Mode = Charge_LED_Mode_3;
    if ((SystemMode == SystemDischargeMode)||(SystemMode == SystemBootUpWait))
    {
        switch (LED_Mode)
        {
        case Discharge_LED_Mode_1:
            LED_1_Low;
            LED_2_Low;
            LED_3_Low;
//            LED_4_Low;
            LED_5_Low;
            LED_6_Low;

            EN_PWM_LID_4_P32;

            EN_LED_1_P21;
            EN_LED_2_P22;
            EN_LED_3_P33;
            EN_LED_5_P24;
            EN_LED_6_P25;

            break;

        case Discharge_LED_Mode_2:
            LED_1_High;
            LED_2_Low;
            LED_3_Low;
            LED_4_Low;
            LED_5_Low;
            LED_6_Low;

            EN_LED_1_P21;
            EN_LED_2_P22;
            EN_LED_3_P33;
            EN_LED_4_P32;
            EN_LED_5_P24;
            EN_LED_6_P25;

            break;

        case Discharge_LED_Mode_3:
            LED_1_High;
            //     LED_2_Low;
            LED_3_Low;
            LED_4_Low;
            LED_5_Low;
            LED_6_Low;

            EN_PWM_LID_2_P22;

            EN_LED_1_P21;
            // EN_LED_2_P22;
            EN_LED_3_P33;
            EN_LED_4_P32;
            EN_LED_5_P24;
            EN_LED_6_P25;

            break;

        case Discharge_LED_Mode_4:
            LED_1_High;
            LED_2_High;
            LED_3_Low;
            LED_4_Low;
            LED_5_Low;
            LED_6_Low;

            EN_LED_1_P21;
            EN_LED_2_P22;
            EN_LED_3_P33;
            EN_LED_4_P32;
            EN_LED_5_P24;
            EN_LED_6_P25;

            break;

        case Discharge_LED_Mode_5:
            LED_1_High;
            LED_2_High;
//            LED_3_Low;
            LED_4_Low;
            LED_5_Low;
            LED_6_Low;

            EN_PWM_LID_3_P33;
            EN_LED_1_P21;
            EN_LED_2_P22;
//            EN_LED_3_P32;
            EN_LED_4_P32;
            EN_LED_5_P24;
            EN_LED_6_P25;

            break;

        case Discharge_LED_Mode_6:
            LED_1_High;
            LED_2_High;
            LED_3_High;
            LED_4_Low;
            LED_5_Low;
            LED_6_Low;

            EN_LED_1_P21;
            EN_LED_2_P22;
            EN_LED_3_P33;
            EN_LED_4_P32;
            EN_LED_5_P24;
            EN_LED_6_P25;

            break;

        default:
         //   LED_OFF();
            break;
        }
    }

    else if (SystemMode == SystemChargeMode)
    {
        switch (LED_Mode)
        {
        case Charge_LED_Mode_1:
            //    LED_1_Low;
            LED_2_Low;
            LED_3_Low;
            LED_4_Low;
            LED_5_Low;
            LED_6_Low;

            EN_PWM_LID_1_P21;

            //   EN_LED_1_P21;
            EN_LED_2_P22;
            EN_LED_3_P33;
            EN_LED_4_P32;
            EN_LED_5_P24;
            EN_LED_6_P25;

            break;
            /*
             case    Charge_LED_Mode_2:
             break;

             case    Charge_LED_Mode_3:
             break;*/

        case Charge_LED_Mode_4:
            LED_1_High;
            LED_2_High;
            LED_3_High;
            LED_4_Low;
            LED_5_Low;
            LED_6_Low;

            EN_LED_1_P21;
            EN_LED_2_P22;
            EN_LED_3_P33;
            EN_LED_4_P32;
            EN_LED_5_P24;
            EN_LED_6_P25;

            break;

        default:
           // LED_OFF();
            break;
        }
    }
}

//FENGLONG 20190710  V1.83
//void BatteryCapacityRenew(void)         //SOC renew
//{
//    UINT8 z1;
//
//    if ((SystemMode == SystemChargeMode)
//            && (BatteryModeChangeDelayCount >= TA0_1m)
//            && (BatteryCapacityRefreshCount >= TA0_1s))
//    {
//        z1 = DetectChargeCapacity();
//        if ((z1 + 2) >= BatteryCapacity)
//            BatteryCapacity++;
//        else
//        {
//            if (z1 >= BatteryCapacity)
//                BatteryCapacity = z1;
//        }
//
//        BatteryCapacityRefreshCount = 0;
//    }
//
//    else if ((SystemMode == SystemDischargeMode)
//            && (BatteryModeChangeDelayCount >= TA0_1m)
//            && (BatteryCapacityRefreshCount >= TA0_1s))
//    {
//        z1 = DetectDischargeCapacity();
//        if (BatteryCapacity >= (z1 + 2))
//            BatteryCapacity--;
//        else
//        {
//            if (z1 <= BatteryCapacity)
//                BatteryCapacity = z1;
//        }
//
//        BatteryCapacityRefreshCount = 0;
//    }
//}

void LED_ModeDetect(void)
{
    if ( (SystemMode == SystemDischargeMode) || (SystemMode == SystemBootUpWait) )
    {

        if(sys_cap.val.re_cap_rate > 85)
        {
            LED_Mode = Discharge_LED_Mode_6;
        }
        else if(sys_cap.val.re_cap_rate > 70)
        {
            LED_Mode = Discharge_LED_Mode_5;
        }
        else if(sys_cap.val.re_cap_rate > 50)
        {
            LED_Mode = Discharge_LED_Mode_4;
        }
        else if(sys_cap.val.re_cap_rate > 30)
        {
            LED_Mode = Discharge_LED_Mode_3;
        }
        else if(sys_cap.val.re_cap_rate > 15)
        {
            LED_Mode = Discharge_LED_Mode_2;
        }
        else
        {
            LED_Mode = Discharge_LED_Mode_1;
        }
    }
    else if( SystemMode == SystemChargeMode )       //20190525 fenglong
    {
        LED_Mode = Charge_LED_Mode_1;
        if (sys_cap.val.re_cap_rate > 30)
            LED_Mode = Charge_LED_Mode_2;
        if (sys_cap.val.re_cap_rate > 70)
            LED_Mode = Charge_LED_Mode_3;
        if (sys_cap.val.re_cap_rate > 93)
            LED_Mode = Charge_LED_Mode_4;

//20190525 fenglong
        //        if( ((BatteryData.VBat.VBatWord >=CHG_VOL_FULL) && (BatteryData.CC.CCWord < CHG_CC_FULL)) || ( HW_PT_Status.Bits.HW_OV == 1 ) || (HW_PT_Status.Bits.HW_OV == 1) )
        if(        ((BatteryData.VBat.VBatWord >=CHG_VOL_FULL) && (BatteryData.CC.CCWord < CHG_CC_FULL))
                || ( HW_PT_Status.Bits.HW_OV == 1 )
                || (FW_PT_Status.Bits.PT_OV == 1)
          )                                     //fenglong 20190708
        {
            LED_Mode = Charge_LED_Mode_4;
        }

    }
}



void SystemStatusDetect(void)
{
    //????
//    BatteryModeChangeDelayCount = TA0_1m;           //refresh per minute  //FENGLONG 20190710  V1.83
//    BatteryCapacity = DetectChargeCapacity();                             //FENGLONG 20190710  V1.83
//    BatteryCapacityRefreshCount = 0;                                      //FENGLONG 20190710  V1.83

    if (DC_IN_Count >= TA0_3s)  //适配在位检测
    {
        if(SystemMode != SystemChargeMode )
        {
            SystemMode = SystemChargeMode;
            RS485_MODE =0;
//            BatteryModeChangeDelayCount = 0;//FENGLONG 20190710  V1.83

//            BatteryCapacityRefreshCount = 0;//FENGLONG 20190714  V1.87
            if ((FW_PT_Status.Bits.PT_UTSCP==0) && (FW_PT_Status.Bits.PT_UTCP==0))//wk
            {
                LED_CTRL.Word =0;           //fenglong20190713
                LED_OFF();
                close_timer1();
            }
            deta_cap_cnt = sys_cap.val.re_cap_rate;

        }

    }
    else
    {
        if(DC_IN_Release_Count >= TA0_1s)
        {
                FW_PT_Status.Bits.PT_UTSCP=0;
                FW_PT_Status.Bits.PT_OTSCP=0;
                FW_PT_Status.Bits.PT_UTCP = 0;    //非充电状态，与充电控制相关的标志位都应该清掉//wk
                if(SystemMode == SystemChargeMode)
            {
                SystemMode = SystemSleepMode;
                his_data[CHG_CAP_CNT] = sys_cap.val.chg_cap_cnt;
            }
//            BatteryModeChangeDelayCount = 0;//FENGLONG 20190710  V1.83
//            BatteryCapacityRefreshCount = 0;//FENGLONG 20190710  V1.83

        }
    }

    //????
//    BatteryCapacityRenew();  //SOC容量      fenglong 20190710 V1.83
    if( (SystemMode == SystemChargeMode) || (SystemMode == SystemDischargeMode) || (SystemMode == SystemBootUpWait) )// && (SystemMode != SystemBootUpWait) && (SystemMode != SystemBootUp) )
    {
        if( ALARM_PT_Status.Bits.AL_GLINT == 1)        //fenglong 20190702
        {

        	if( FW_PF_Status.Word != 0 )
        	{
                if(Alert_count==0)
                {
                    Alert_count =1;
                    LED_ALARM();
                }
        	}
        	else if(SystemMode == SystemChargeMode)
        	{
        		if( (FW_PT_Status.Bits.PT_OTDP == 1) || (FW_PT_Status.Bits.PT_OTSCP == 1) || (FW_PT_Status.Bits.PT_OTCP == 1))
        		{
                    Alert_count =0;
                    LED_ModeDetect();  //LED状态切换
                    LED_DisplayRenew();  //LED显示函数
        		}
        		else
        		{
                    if(Alert_count==0)
                    {
                        Alert_count =1;
                        LED_ALARM();
                    }
        		}
        	}
        	else
        	{
                if(Alert_count==0)
                {
                    Alert_count =1;
                    LED_ALARM();
                }
        	}
        }
        else if(RS485_MODE == 1)
        {
            Alert_count =0;
            LED_OFF();
        }
        else
        {
            Alert_count =0;
            LED_ModeDetect();  //LED状态切换
            LED_DisplayRenew();  //LED显示函数
        }
    }
    else
    {
        Alert_count =0;
    }
//    else
//    {
//        if(SystemMode == SystemSleepMode)
//        {
//            if( ALARM_PT_Status.Bits.AL_GLINT == 1 )       //fenglong 20190702
//            {
//                LED_ALARM();
//            }
//        }
//    }
}

void Charge_Mode2_LED_Display(void)
{
    switch (ChargeLED_Mode2_3_Count)
    {
    case 1:
        LED_2_Low;
        LED_3_Low;
        LED_4_Low;
        LED_5_Low;
        LED_6_Low;

        EN_LED_2_P22;
        EN_LED_3_P33;
        EN_LED_4_P32;
        EN_LED_5_P24;
        EN_LED_6_P25;

        BreathingCycleCount = 40;
        TA1CCR1 = BreathingTable_1600[BreathingCycleCount];
        EN_PWM_LID_1_P21;
        break;

    case 40:
        LED_1_High;
//        LED_2_Low;
        LED_3_Low;
        LED_4_Low;
        LED_5_Low;
        LED_6_Low;

        EN_LED_1_P21;
        EN_LED_3_P33;
        EN_LED_4_P32;
        EN_LED_5_P24;
        EN_LED_6_P25;


        BreathingCycleCount = 40;
        TA1CCR1 = BreathingTable_1600[BreathingCycleCount];
        EN_PWM_LID_2_P22;
        break;

    case 80:
        LED_1_High;
        LED_2_High;
        LED_3_Low;
        LED_4_Low;
        LED_5_Low;
        LED_6_Low;

        EN_LED_1_P21;
        EN_LED_2_P22;
        EN_LED_3_P33;
        EN_LED_4_P32;
        EN_LED_5_P24;
        EN_LED_6_P25;

        break;

    case 100:

        LED_3_Low;
        LED_4_Low;
        LED_5_Low;
        LED_6_Low;

        EN_LED_3_P33;
        EN_LED_4_P32;
        EN_LED_5_P24;
        EN_LED_6_P25;


        BreathingCycleCount = 0;
        TA1CCR1 = BreathingTable_1600[BreathingCycleCount];
        EN_PWM_LID_1_P21;
        EN_PWM_LID_2_P22;
        //   EN_PWM_LID_3_P32;
        break;

    case 140:
        LED_OFF();

        break;

    case 160:
        ChargeLED_Mode2_3_Count = 0;
        // BreathingCycleCount = 0;
        break;

    default:

        break;
    }
}
void Charge_Mode3_LED_Display(void)
{
    switch (ChargeLED_Mode2_3_Count)
    {
    case 1:
        LED_2_Low;
        LED_3_Low;
        LED_4_Low;
        LED_5_Low;
        LED_6_Low;

        EN_LED_2_P22;
        EN_LED_3_P33;
        EN_LED_4_P32;
        EN_LED_5_P24;
        EN_LED_6_P25;

        BreathingCycleCount = 40;
        TA1CCR1 = BreathingTable_1600[BreathingCycleCount];
        EN_PWM_LID_1_P21;
        break;

    case 40:
        LED_1_High;
        LED_2_Low;
        LED_3_Low;
        LED_4_Low;
        LED_5_Low;
        LED_6_Low;

        EN_LED_1_P21;
        EN_LED_3_P33;
        EN_LED_4_P32;
        EN_LED_5_P24;
        EN_LED_6_P25;

        BreathingCycleCount = 40;
        TA1CCR1 = BreathingTable_1600[BreathingCycleCount];
        EN_PWM_LID_2_P22;
        break;

    case 80:
        LED_1_High;
        LED_2_High;
        LED_3_Low;
        LED_4_Low;
        LED_5_Low;
        LED_6_Low;

        EN_LED_1_P21;
        EN_LED_2_P22;
        EN_LED_4_P32;
        EN_LED_5_P24;
        EN_LED_6_P25;

        BreathingCycleCount = 40;
        TA1CCR2 = BreathingTable_1600[BreathingCycleCount];//20190718  AID
        EN_PWM_LID_3_P33;
        break;

    case 120:
        LED_1_High;
        LED_2_High;
        LED_3_High;
        LED_4_Low;
        LED_5_Low;
        LED_6_Low;

        EN_LED_1_P21;
        EN_LED_2_P22;
        EN_LED_3_P33;
        EN_LED_4_P32;
        EN_LED_5_P24;
        EN_LED_6_P25;

        break;

    case 140:

        LED_4_Low;
        LED_5_Low;
        LED_6_Low;

        EN_LED_4_P32;
        EN_LED_5_P24;
        EN_LED_6_P25;

        BreathingCycleCount = 0;
        TA1CCR1 = BreathingTable_1600[BreathingCycleCount];
        TA1CCR2 = BreathingTable_1600[BreathingCycleCount];//20190718  AID
        EN_PWM_LID_1_P21;
        EN_PWM_LID_2_P22;
        EN_PWM_LID_3_P33;
        break;

    case 180:
        LED_OFF();

        break;

    case 200:
        ChargeLED_Mode2_3_Count = 0;
        // BreathingCycleCount = 0;
        break;

    default:

        break;
    }
}
//LED  AID 20190703
void TA11_Breathing(void)
{
    UINT8 Buff;

    if( ALARM_PT_Status.Bits.AL_GLINT == 1)
    {

    	if(SystemMode == SystemChargeMode)
    	{
    		if( FW_PF_Status.Word != 0 )
    		{
    	        Buff=40;

    	        BreathingCycleCount = BreathingCycleCount + 1;
    	        if (BreathingCycleCount >= Buff)
    	        {
    	            BreathingCycleCount = 0;
    	        }
    	        TA1CCR1 = BreathingTable_800[BreathingCycleCount];// 20190718  AID
    	        TA1CCR2 = BreathingTable_800[BreathingCycleCount];
    		}
    		else if( (FW_PT_Status.Bits.PT_OTDP == 1) || (FW_PT_Status.Bits.PT_OTSCP == 1) || (FW_PT_Status.Bits.PT_OTCP == 1) )
    		{
    	        if (LED_Mode == Charge_LED_Mode_2)
    	            Charge_Mode2_LED_Display();
    	        if (LED_Mode == Charge_LED_Mode_3)
    	            Charge_Mode3_LED_Display();

    	        TA1CCR1 = BreathingTable_1600[BreathingCycleCount];
    	        TA1CCR2 = BreathingTable_1600[BreathingCycleCount];// 20190719  AID
    	        ChargeLED_Mode2_3_Count = ChargeLED_Mode2_3_Count + 1;
    	        BreathingCycleCount = BreathingCycleCount + 1;

    	        if ((LED_Mode == Charge_LED_Mode_1)
    	                && (BreathingCycleCount >= Breathing_1600))
    	            BreathingCycleCount = 0;
    		}
    		else
    		{
    	        Buff=40;

    	        BreathingCycleCount = BreathingCycleCount + 1;
    	        if (BreathingCycleCount >= Buff)
    	        {
    	            BreathingCycleCount = 0;
    	        }
    	        TA1CCR1 = BreathingTable_800[BreathingCycleCount];// 20190718  AID
    	        TA1CCR2 = BreathingTable_800[BreathingCycleCount];
    		}
    	}
    	else
    	{
            Buff=40;

            BreathingCycleCount = BreathingCycleCount + 1;
            if (BreathingCycleCount >= Buff)
            {
                BreathingCycleCount = 0;
            }
            TA1CCR1 = BreathingTable_800[BreathingCycleCount];// 20190718  AID
            TA1CCR2 = BreathingTable_800[BreathingCycleCount];
    	}
    }
    else if ( (SystemMode == SystemDischargeMode) || (SystemMode == SystemBootUpWait) )
    {
        if (LED_Mode == Discharge_LED_Mode_1)
            Buff = Breathing_1200;              // 20190719  AID  Breathing_1200
        else
            Buff = Breathing_1600;

        TA1CCR1 = BreathingTable_1600[BreathingCycleCount];
        TA1CCR2 = BreathingTable_1600[BreathingCycleCount];// 20190719  AID

        BreathingCycleCount = BreathingCycleCount + 1;

        if (BreathingCycleCount >= Buff)
        {
            BreathingCycleCount = 0;
        }
    }
    else if(SystemMode == SystemChargeMode)
    {
        if (LED_Mode == Charge_LED_Mode_2)
            Charge_Mode2_LED_Display();
        if (LED_Mode == Charge_LED_Mode_3)
            Charge_Mode3_LED_Display();

        TA1CCR1 = BreathingTable_1600[BreathingCycleCount];
        TA1CCR2 = BreathingTable_1600[BreathingCycleCount];// 20190719  AID
        ChargeLED_Mode2_3_Count = ChargeLED_Mode2_3_Count + 1;
        BreathingCycleCount = BreathingCycleCount + 1;

        if ((LED_Mode == Charge_LED_Mode_1)
                && (BreathingCycleCount >= Breathing_1600))
            BreathingCycleCount = 0;
    }
    else
    {
        //????
        _nop();
    }
}

void LED_ALARM(void)
{
    LED_OFF();


    //    BreathingCycleCount = 20;
    //    if(BreathingCycleCount>=79)
    //    {
    //        BreathingCycleCount=0;
    //    }
    //    BreathingCycleCount++;

    //    TA1CCR1 = BreathingTable_1600[BreathingCycleCount];
    //    TA1CCR2 = BreathingTable_1600[BreathingCycleCount];
    //    TA1CCR2 = BreathingCycleCount;
    //    EN_PWM_LID_1_P21;       //绿灯
    //    EN_PWM_LID_2_P22;       //绿灯
    //    EN_PWM_LID_3_P32;       //绿灯
        EN_PWM_LID_4_P32;       //红灯
        EN_PWM_LID_5_P24;       //LED1位置蓝色
        EN_PWM_LID_6_P25;         //LED2位置蓝色

}

void His_DataRenew(void)
{
    static uchar his_save_delay=0,wait_2_write =0;
    //UINT8 i;
    UINT16 cur_tmp;
    if(his_data[HIS_MINVOLT]  ==0)
    {
        his_data[HIS_MINVOLT] = CellMiniVoltage;
    }
    if(his_data[HIS_MINVOLT] > CellMiniVoltage)
    {
        his_data[HIS_MINVOLT] = CellMiniVoltage;
        wait_2_write =1;
    }
    if(his_data[HIS_MAXVOLT] < CellMAXiVoltage)
    {
        his_data[HIS_MAXVOLT] = CellMAXiVoltage;
        wait_2_write =1;
    }
    if((his_data[HIS_CHG_MAXCURRENT] < BatteryData.CC.CCWord)&&(BatteryData.CC.CCWord <0x8000))
    {
        his_data[HIS_CHG_MAXCURRENT] = BatteryData.CC.CCWord;
        wait_2_write =1;
    }
    if(BatteryData.CC.CCWord > 0x8000)
    {
        cur_tmp = 0-BatteryData.CC.CCWord;
    }
    if(his_data[HIS_DSG_MAXCURRENT] <cur_tmp)
    {
        his_data[HIS_DSG_MAXCURRENT] = cur_tmp;
        wait_2_write =1;
    }
    if(his_data[HIS_CHG_MAXTEMP] ==0)
    {
        his_data[HIS_CHG_MAXTEMP] = BatteryData.TS1.TS1Word;
    }
    if(his_data[HIS_CHG_MAXTEMP] > BatteryData.TS1.TS1Word)
    {
        his_data[HIS_CHG_MAXTEMP] = BatteryData.TS1.TS1Word;
        wait_2_write =1;
    }
    if(his_data[HIS_DSG_MAXTEMP] ==0)
    {
        his_data[HIS_DSG_MAXTEMP] = BatteryData.TS2.TS2Word;
    }
    if(his_data[HIS_DSG_MAXTEMP] > BatteryData.TS2.TS2Word)
    {
        his_data[HIS_DSG_MAXTEMP] = BatteryData.TS2.TS2Word;
        wait_2_write =1;
    }
    his_save_delay++;
    if(his_save_delay > 20)
    {
        his_save_delay =0;
        if(wait_2_write == 1)
        {
            wait_2_write =0;
            cur_tmp = 0;
            //以下屏蔽 fenglong 20190802
//            for(i=0;i<FLASH_DATA_NUM-1;i++)                                                 //fenglong 20190615
//            {
//                cur_tmp+= his_data[i];
//            }
//            his_data[HIS_CRC16] = cur_tmp;
//            __bic_SR_register(  GIE);       // Enter LPM3 w/ interrupt
//            Falsh_Write_Arr((unsigned int *)Segment_C,his_data,FLASH_DATA_NUM);             //fenglong 20190615
//            Falsh_Write_Arr((unsigned int *)Segment_D,his_data,FLASH_DATA_NUM);             //fenglong 20190615
//            __bis_SR_register(  GIE);       // Enter LPM3 w/ interrupt
        }
    }
}

void CLR_PF(void)
{
    uint crc16;
    uchar Buff_0;

    his_data_init();
//    if(FW_PF_Status.Word != 0)
//    {
        FW_PF_Status.Word = 0;
        his_data[PF_STATE_ADDR] = FW_PF_Status.Word;
        crc16 =0;
        for(Buff_0 =0;Buff_0<FLASH_DATA_NUM-1;Buff_0++)                                     //fenglong 20190615
        {
            crc16+= his_data[Buff_0];
        }
        his_data[HIS_CRC16] = crc16;
        Falsh_Write_Arr((unsigned int *)Segment_C,his_data,FLASH_DATA_NUM);                 //fenglong 20190615
        Falsh_Write_Arr((unsigned int *)Segment_D,his_data,FLASH_DATA_NUM);                 //fenglong 20190615
//    }

    Cell_PF_UV_Count = 0;               //permanent fail safety under voltage
    Cell_PF_OV_Count = 0;               //4.23mV    -   8s      //permanent fail safety over voltage
    PF_OCC_Count = 0;                   //permanent fail  over current in charge
    PF_OCD_Count = 0;                   //permanent fail  over current in discharge
    PF_OTC_Count = 0;
    PF_OTM_Count = 0;                   //permanent fail safety over  temperature MOSFET
}


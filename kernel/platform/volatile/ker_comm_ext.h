
#ifndef KER_COMM_EXT_H
#define KER_COMM_EXT_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../../../common/common.h"

#define KER_COMM_RX_EXT_RING_QUEUE_SIZE 32
#define KER_COMM_RX_EXT_PARSE_BUFFER_SIZE 128
#define COMM_RX_EXT_TIMEOUT_MS    100

#define COMM_RX_EXT_ACK_TIMEOUT_MS 100
#define COMM_RX_EXT_ACK_RETRY_COUNTS 2
//5min(5*60*1000)
#define COMM_TX_EXT_SEND_INTERVAL_MS    300000
 

/* communication command from pc */
typedef enum{    

    E_KER_COMM_CMD_RX_EXT_WriteAllParams,
    E_KER_COMM_CMD_RX_EXT_ReadAllParams,
    E_KER_COMM_CMD_RX_EXT_ShakeHands,
    
    E_KER_COMM_CMD_RX_EXT_COUNT 

}TE_KER_COMM_CMD_RX_EXT;

//ctl send to dwin cmd
typedef enum{
    E_COMM_CMD_TX_WriteAllParam,
    E_COMM_CMD_TX_ReadAllParam,
    E_COMM_CMD_TX_ShakeHands,
    E_COMM_CMD_TX_AlarmOcclusion,
    E_COMM_CMD_TX_AlarmAirBubble,
    E_COMM_CMD_TX_AlarmBatteryExhaustion,
    E_COMM_CMD_TX_AlarmInfusionComplete,
    E_COMM_CMD_TX_AlarmMachineFaultCodeError,
    E_COMM_CMD_TX_AlarmMachineFaultDirtctionError,
    E_COMM_CMD_TX_AlarmMachineFaultRunError,
    E_COMM_CMD_TX_AlarmLimitingArriving,
    E_COMM_CMD_TX_AlarmClampError,
    E_COMM_CMD_TX_AlarmShutDown,
    E_COMM_CMD_TX_ValidPca,
    E_COMM_CMD_TX_InvalidPca,
    E_COMM_CMD_TX_KeyStop,
    E_COMM_CMD_TX_NormalRun,
    E_COMM_CMD_TX_COUNT

}TE_COMM_CMD_TX_EXT;

void KerCommExtInit(void);



#ifdef __cplusplus
}
#endif

#endif


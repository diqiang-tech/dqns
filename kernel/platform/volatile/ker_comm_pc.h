#ifndef KER_COMM_PC_H
#define KER_COMM_PC_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../../../common/common.h"

/*<dqns_gen_comm_some_defines_begin>*/
#define KER_COMM_RX_PC_RING_QUEUE_SIZE 8
#define KER_COMM_RX_PC_PARSE_BUFFER_SIZE 32
#define KER_COMM_RX_PC_RX_TIMEOUT_MS 10
#define KER_COMM_RX_PC_WAIT_ACK_TIMEOUT_MS 200
#define KER_COMM_RX_PC_WAIT_ACK_RETRY_TIMES 3
/*<dqns_gen_comm_some_defines_end>*/

typedef enum{
    /*<dqns_gen_comm_rx_cmd_begin>*/
    E_KER_COMM_CMD_RX_PC_NotAvailable,
    E_KER_COMM_CMD_RX_PC_RunStop,
    E_KER_COMM_CMD_RX_PC_GetStatus,
    /*<dqns_gen_comm_rx_cmd_end>*/
    E_KER_COMM_CMD_RX_PC_COUNT
}TE_KER_COMM_CMD_RX_PC;

typedef enum{
    /*<dqns_gen_comm_tx_cmd_begin>*/
    E_KER_COMM_CMD_TX_PC_NotAvailable,
    E_KER_COMM_CMD_TX_PC_RunStop,
    E_KER_COMM_CMD_TX_PC_GetStatus,
    /*<dqns_gen_comm_tx_cmd_end>*/
    E_KER_COMM_CMD_TX_PC_COUNT
}TE_KER_COMM_CMD_TX_PC;

void KerCommPcInit(void);

#ifdef __cplusplus
}
#endif

#endif

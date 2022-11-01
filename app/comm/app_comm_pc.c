#include "../../kernel/platform/volatile/ker_comm_pc.h"
#include "../../kernel/platform/stable/ker_comm.h"
#include "../../kernel/platform/stable/ker_timer.h"
#include "../../app/comm/app_comm_pc.h"
/*<dqns_gen_app_comm_cmd_handle_declaration_begin>*/
static TE_COMM_RET_CODE AppCommPcRxNotAvailable(T_U8 cmd,T_U8* p_data,T_U16 data_len);
static TE_COMM_RET_CODE AppCommPcRxRunStop(T_U8 cmd,T_U8* p_data,T_U16 data_len);
static TE_COMM_RET_CODE AppCommPcRxGetStatus(T_U8 cmd,T_U8* p_data,T_U16 data_len);
/*<dqns_gen_app_comm_cmd_handle_declaration_end>*/

void AppCommPcInit(void){
    /*<dqns_gen_app_comm_cmd_handle_set_begin>*/
    M_KerCommSetParseHandle(E_KER_COMM_ID_PC,(T_U8)E_KER_COMM_CMD_RX_PC_NotAvailable,AppCommPcRxNotAvailable);
    M_KerCommSetParseHandle(E_KER_COMM_ID_PC,(T_U8)E_KER_COMM_CMD_RX_PC_RunStop,AppCommPcRxRunStop);
    M_KerCommSetParseHandle(E_KER_COMM_ID_PC,(T_U8)E_KER_COMM_CMD_RX_PC_GetStatus,AppCommPcRxGetStatus);
    /*<dqns_gen_app_comm_cmd_handle_set_end>*/
}


/*<dqns_gen_app_comm_cmd_handle_definition_begin>*/
static TE_COMM_RET_CODE AppCommPcRxNotAvailable(T_U8 cmd,T_U8* p_data,T_U16 data_len){
    M_Assert(p_data);

    return E_COMM_RET_OK;

}

static TE_COMM_RET_CODE AppCommPcRxRunStop(T_U8 cmd,T_U8* p_data,T_U16 data_len){
    M_Assert(p_data);

    return E_COMM_RET_OK;

}

static TE_COMM_RET_CODE AppCommPcRxGetStatus(T_U8 cmd,T_U8* p_data,T_U16 data_len){
    M_Assert(p_data);

    return E_COMM_RET_OK;

}

/*<dqns_gen_app_comm_cmd_handle_definition_end>*/


#include "../../common/common.h"
#include "udm_device_tbl.h"

/*<dqns_gen_device_extern_begin>*/
extern TS_UDM_DEVICE gg_udm_key;    //key device
extern TS_UDM_DEVICE gg_udm_led;    //led device
extern TS_UDM_DEVICE gg_udm_dig;    //数码管
extern TS_UDM_DEVICE gg_udm_pump;    //vacumm extractor pump
/*<dqns_gen_device_extern_end>*/


TS_UDM_DEVICE * gg_udm_device_tbl[E_UDM_DEVICE_CNT]={
    /*<dqns_gen_device_tbl_begin>*/
    &gg_udm_key,    //key device
    &gg_udm_led,    //led device
    &gg_udm_dig,    //数码管
    &gg_udm_pump,    //vacumm extractor pump
    /*<dqns_gen_device_tbl_end>*/
};

TS_UDM_DEVICE * UdmDeviceObj(TE_UDM_DEVICE_ID e_device_id){
    M_Assert(e_device_id < E_UDM_DEVICE_CNT);
    return (gg_udm_device_tbl[e_device_id]);
}


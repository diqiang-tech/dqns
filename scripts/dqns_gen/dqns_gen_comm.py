import os
import dqns_gen_utility

def getCommIDFromXML(comm_config,prefix_str,tail,need_to_upper=True):
    xml_list = []
    
    for item in comm_config:
        if item.tag == 'comm_id':
            if need_to_upper:
                item_str = prefix_str+item.attrib['ID'].upper()+tail+'\n'
            else:
                item_str = prefix_str+item.attrib['ID']+tail+'\n'
            xml_list.append(item_str)
    
    return xml_list
    
def getCommIDList(comm_config):

    comm_id_list = []
    
    for item in comm_config:
        if item.tag == 'comm_id':
            item_str = item.attrib['ID']
            comm_id_list.append(item_str)
    
    return comm_id_list

def getCommRxCmdList(comm_config,comm_id):
    comm_rx_cmd_list = []
    for item in comm_config:
        if item.tag == 'comm_id' and item.attrib['ID'] == comm_id:
            for item1 in item:
                if item1.tag == 'RX_CMD_ID_LIST':
                    for item2 in item1:
                        if item2.tag == 'RX_CMD':
                            comm_rx_cmd_list.append(item2.text)
    return comm_rx_cmd_list
    
def getCommRxCmdEnumList(comm_config,comm_id):
    comm_rx_cmd_list = getCommRxCmdList(comm_config,comm_id)
    comm_rx_cmd_enum_list = []
    for item in comm_rx_cmd_list:        
        rx_cmd_enum_str = '    E_KER_COMM_CMD_RX_'+comm_id.upper()+'_'+item+',\n'
        comm_rx_cmd_enum_list.append(rx_cmd_enum_str)
    return comm_rx_cmd_enum_list
    
def getCommTxCmdList(comm_config,comm_id):
    comm_tx_cmd_list = []
    for item in comm_config:
        if item.tag == 'comm_id' and item.attrib['ID'] == comm_id:
            for item1 in item:
                if item1.tag == 'TX_CMD_ID_LIST':
                    for item2 in item1:
                        if item2.tag == 'TX_CMD':
                            comm_tx_cmd_list.append(item2.text)
    return comm_tx_cmd_list   

def getCommTxCmdEnumList(comm_config,comm_id):
    comm_tx_cmd_list = getCommTxCmdList(comm_config,comm_id)
    comm_tx_cmd_enum_list = []
    for item in comm_tx_cmd_list:
        tx_cmd_enum_str = '    E_KER_COMM_CMD_TX_'+comm_id.upper()+'_'+item+',\n'
        comm_tx_cmd_enum_list.append(tx_cmd_enum_str)  

    return comm_tx_cmd_enum_list

def getCommDefinitionsList(comm_config,comm_id):
    comm_definitions_list = []
    for item in comm_config:
        if item.tag == 'comm_id' and item.attrib['ID'] == comm_id:
            for item1 in item:
                if item1.tag == 'SOME_DEFINES':
                    definition_str = '#define KER_COMM_RX_'+comm_id.upper()+'_'+item1.text+' '+item1.attrib['VALUE']+'\n'
                    comm_definitions_list.append(definition_str)
                    
    return comm_definitions_list
                    
def getCommRxCmdHandleDeclarationList(comm_config,comm_id):
    cmd_handle_declaration_list = []
    rx_cmd_list = getCommRxCmdList(comm_config,comm_id)
    comm_id_first_upper = dqns_gen_utility.DqnsGenFirstToUpper(comm_id)
    for rx_cmd in rx_cmd_list:            
        cmd_handle_declaration_list.append('static TE_COMM_RET_CODE AppComm'+comm_id_first_upper+'Rx'+rx_cmd+'(T_U8 cmd,T_U8* p_data,T_U16 data_len);\n')
    
    return cmd_handle_declaration_list
    
def getCommRxCmdHandleSetList(comm_config,comm_id):
    cmd_handle_set_list = []
    rx_cmd_list = getCommRxCmdList(comm_config,comm_id)
    comm_id_first_upper = dqns_gen_utility.DqnsGenFirstToUpper(comm_id)
    for rx_cmd in rx_cmd_list:            
        cmd_handle_set_list.append('    M_KerCommSetParseHandle(E_KER_COMM_ID_'+comm_id.upper()+',(T_U8)E_KER_COMM_CMD_RX_'+comm_id.upper()+'_'+rx_cmd+',AppComm'+comm_id_first_upper+'Rx'+rx_cmd+');\n')
    
    return cmd_handle_set_list
    
def getCommRxCmdHandleDefinitionList(comm_config,comm_id):
    cmd_handle_definition_list = []
    rx_cmd_list = getCommRxCmdList(comm_config,comm_id)
    comm_id_first_upper = dqns_gen_utility.DqnsGenFirstToUpper(comm_id)
    
    c_path_name = r'..\..\app\comm\app_comm_'+comm_id+'.c'
    begin_str = '<dqns_gen_app_comm_cmd_handle_definition_begin>'
    end_str = '<dqns_gen_app_comm_cmd_handle_definition_end>'
    crch_definition_list = dqns_gen_utility.DqnsGenGetListFromFile(begin_str,end_str,c_path_name)
    
    for rx_cmd in rx_cmd_list:
        rx_cmd_handle_name = 'AppComm'+comm_id_first_upper+'Rx'+rx_cmd
        if not dqns_gen_utility.DqnsGenIsTextInList(crch_definition_list, rx_cmd_handle_name):
            cmd_handle_definition_list.append('static TE_COMM_RET_CODE AppComm'+comm_id_first_upper+'Rx'+rx_cmd+'(T_U8 cmd,T_U8* p_data,T_U16 data_len){\n')
            cmd_handle_definition_list.append('    M_Assert(p_data);\n')
            cmd_handle_definition_list.append('\n')
            cmd_handle_definition_list.append('    return E_COMM_RET_OK;\n')
            cmd_handle_definition_list.append('\n')
            cmd_handle_definition_list.append('}\n')
            cmd_handle_definition_list.append('\n')
    
    return cmd_handle_definition_list+crch_definition_list

def genKerCommFileInit(comm_config,comm_id,is_head_file=True):
    path_name = r'..\..\kernel\platform\volatile\ker_comm_'+comm_id
    ker_comm_file_list = []   
    comm_id_first_upper = dqns_gen_utility.DqnsGenFirstToUpper(comm_id)
    comm_rx_cmd_list = getCommRxCmdList(comm_config,comm_id)
    comm_tx_cmd_list = getCommTxCmdList(comm_config,comm_id)
    comm_definitions_list = getCommDefinitionsList(comm_config,comm_id)
    if is_head_file:
        path_name += '.h'
        ker_comm_file_list.append('#ifndef KER_COMM_'+comm_id.upper()+'_H\n')
        ker_comm_file_list.append('#define KER_COMM_'+comm_id.upper()+'_H\n')
        ker_comm_file_list.append('\n')
        ker_comm_file_list.append('#ifdef __cplusplus\n')
        ker_comm_file_list.append('extern "C"{\n')
        ker_comm_file_list.append('#endif\n')
        ker_comm_file_list.append('\n')
        
        ker_comm_file_list.append('#include "../../../common/common.h"\n')
        ker_comm_file_list.append('\n')
        
        ker_comm_file_list.append('/*<dqns_gen_comm_some_defines_begin>*/\n')
        for definition_str in comm_definitions_list:
            ker_comm_file_list.append(definition_str+'\n')
        ker_comm_file_list.append('/*<dqns_gen_comm_some_defines_end>*/\n')
        ker_comm_file_list.append('\n')
        
        ker_comm_file_list.append('typedef enum{\n')
        ker_comm_file_list.append('    /*<dqns_gen_comm_rx_cmd_begin>*/\n')
        for rx_cmd in comm_rx_cmd_list:
            ker_comm_file_list.append('    E_KER_COMM_CMD_RX_'+comm_id.upper()+'_'+rx_cmd+',\n')
        ker_comm_file_list.append('    /*<dqns_gen_comm_rx_cmd_end>*/\n')
        ker_comm_file_list.append('    E_KER_COMM_CMD_RX_'+comm_id.upper()+'_COUNT\n')
        ker_comm_file_list.append('}TE_KER_COMM_CMD_RX_'+comm_id.upper()+';\n')
        ker_comm_file_list.append('\n')
        
        ker_comm_file_list.append('typedef enum{\n')
        ker_comm_file_list.append('    /*<dqns_gen_comm_tx_cmd_begin>*/\n')
        for tx_cmd in comm_tx_cmd_list:
            ker_comm_file_list.append('    E_KER_COMM_CMD_TX_'+comm_id.upper()+'_'+tx_cmd+',\n')
        ker_comm_file_list.append('    /*<dqns_gen_comm_tx_cmd_end>*/\n')
        ker_comm_file_list.append('    E_KER_COMM_CMD_TX_'+comm_id.upper()+'_COUNT\n')
        ker_comm_file_list.append('}TE_KER_COMM_CMD_TX_'+comm_id.upper()+';\n')
        ker_comm_file_list.append('\n')
        
        ker_comm_file_list.append('void KerComm'+comm_id_first_upper+'Init(void);\n')
        ker_comm_file_list.append('\n')
        
        ker_comm_file_list.append('#ifdef __cplusplus\n')
        ker_comm_file_list.append('}\n')
        ker_comm_file_list.append('#endif\n')
        ker_comm_file_list.append('\n')
        ker_comm_file_list.append('#endif\n')      
        
    else:
        path_name += '.c'        
        ker_comm_file_list.append('#include "ker_comm_'+comm_id+'.h"\n')
        ker_comm_file_list.append('#include "../stable/ker_comm.h"\n')
        ker_comm_file_list.append('#include "../stable/ker_timer.h"\n')
        ker_comm_file_list.append('\n')          
        
        ker_comm_file_list.append('/* ------ rx '+comm_id+' ring queue buffer ------ */\n')
        ker_comm_file_list.append('static T_U8 g_rx_'+comm_id+'_buffer[KER_COMM_RX_'+comm_id.upper()+'_RING_QUEUE_SIZE];\n') 
        ker_comm_file_list.append('/* ------ ring queue ------ */\n')
        ker_comm_file_list.append('static TS_RING_QUEUE g_rx_'+comm_id+'_ring_queue;\n')
        ker_comm_file_list.append('\n')        
        
        ker_comm_file_list.append('/* ------ rx '+comm_id+' parse buffer ------ */\n')
        ker_comm_file_list.append('static T_U8 g_rx_'+comm_id+'_parse_buffer[KER_COMM_RX_'+comm_id.upper()+'_PARSE_BUFFER_SIZE];\n') 
        ker_comm_file_list.append('\n')        
        
        ker_comm_file_list.append('/* ------ rx '+comm_id+' cmd parse table ------ */\n')
        ker_comm_file_list.append('static TFP_KER_COMM_PARSE_HANDLE g_rx_'+comm_id+'_parse_handle_table[E_KER_COMM_CMD_RX_'+comm_id.upper()+'_COUNT];\n')
        ker_comm_file_list.append('\n')        
        
        ker_comm_file_list.append('/* ------ '+comm_id+' comm information structure ------ */\n')
        ker_comm_file_list.append('TS_KER_COMM_INFO gg_comm_'+comm_id+';\n')
        ker_comm_file_list.append('\n')
        
        ker_comm_file_list.append('/* ------ rx handle ------ */\n')
        ker_comm_file_list.append('static void KerComm'+comm_id_first_upper+'RxHandle(T_U8 uch);\n')
        ker_comm_file_list.append('\n')        
        
        ker_comm_file_list.append('/* ------ parse handle ------ */\n')
        ker_comm_file_list.append('static TE_COMM_RET_CODE KerComm'+comm_id_first_upper+'ParseHandle(T_U8 cmd,T_U8* p_data,T_U16 data_len);\n')
        ker_comm_file_list.append('\n')        
        
        ker_comm_file_list.append('/* ------ send func ------ */\n')
        ker_comm_file_list.append('static void KerComm'+comm_id_first_upper+'Send(T_U8 cmd,T_U8* p_data,T_U16 data_len,TE_BOOL need_ack);\n')
        ker_comm_file_list.append('\n')
        
        ker_comm_file_list.append('/* ------ rx timeout timer handle ------ */\n')
        ker_comm_file_list.append('static void KerComm'+comm_id_first_upper+'RxTimeout(TE_KER_TIMER_ID e_time_id);\n')
        ker_comm_file_list.append('\n')        
        
        ker_comm_file_list.append('/* ------ wait ack timeout timer handle ------ */\n')
        ker_comm_file_list.append('static void KerComm'+comm_id_first_upper+'WaitAckTimeout(TE_KER_TIMER_ID e_time_id);\n')
        ker_comm_file_list.append('\n')            
        
        
        ker_comm_file_list.append('void KerComm'+comm_id_first_upper+'Init(void){\n')
        ker_comm_file_list.append('    /* init ring queue */\n')
        ker_comm_file_list.append('    RingQueueInit(&g_rx_'+comm_id+'_ring_queue,(void*)g_rx_'+comm_id+'_buffer,KER_COMM_RX_'+comm_id.upper()+'_RING_QUEUE_SIZE);\n')
        ker_comm_file_list.append('\n')
        ker_comm_file_list.append('    /* init comm obj */\n')
        ker_comm_file_list.append('    gg_comm_'+comm_id+'.p_ring_queue = (&g_rx_'+comm_id+'_ring_queue);\n')
        ker_comm_file_list.append('    gg_comm_'+comm_id+'.parse_buffer = g_rx_'+comm_id+'_parse_buffer;\n')
        ker_comm_file_list.append('    gg_comm_'+comm_id+'.p_parse_handle_table = g_rx_'+comm_id+'_parse_handle_table;\n')
        ker_comm_file_list.append('    gg_comm_'+comm_id+'.ReceiveByteFunc = KerComm'+comm_id_first_upper+'RxHandle;\n')
        ker_comm_file_list.append('    gg_comm_'+comm_id+'.CommParseFunc = KerComm'+comm_id_first_upper+'ParseHandle;\n')
        ker_comm_file_list.append('    gg_comm_'+comm_id+'.CommSendFunc = KerComm'+comm_id_first_upper+'Send;\n')
        ker_comm_file_list.append('    gg_comm_'+comm_id+'.write_idx_of_parse_buffer = 0;\n')
        ker_comm_file_list.append('    gg_comm_'+comm_id+'.comm_status.comm_status_bits = 0;\n')
        ker_comm_file_list.append('\n')
        ker_comm_file_list.append('    /* bind rx timeout timer handle */\n')
        ker_comm_file_list.append('    KerTimerBind(E_KER_TIMER_RX_'+comm_id.upper()+'_TIMEOUT,KerComm'+comm_id_first_upper+'RxTimeout);\n')
        ker_comm_file_list.append('    /* bind rx ack timeout timer handle */\n')
        ker_comm_file_list.append('    KerTimerBind(E_KER_TIMER_WAIT_'+comm_id.upper()+'_ACK_TIMEOUT,KerComm'+comm_id_first_upper+'WaitAckTimeout);\n')
        ker_comm_file_list.append('}\n')
        
        ker_comm_file_list.append('\n')        
        ker_comm_file_list.append('static void KerComm'+comm_id_first_upper+'RxHandle(T_U8 uch){\n')
        ker_comm_file_list.append('    \n') 
        ker_comm_file_list.append('}\n') 
        
        ker_comm_file_list.append('\n')         
        ker_comm_file_list.append('static TE_COMM_RET_CODE KerComm'+comm_id_first_upper+'ParseHandle(T_U8 cmd,T_U8* p_data,T_U16 data_len){\n')
        ker_comm_file_list.append('    return E_COMM_RET_OK;\n')
        ker_comm_file_list.append('    \n') 
        ker_comm_file_list.append('}\n') 
        
        ker_comm_file_list.append('\n')
        ker_comm_file_list.append('static void KerComm'+comm_id_first_upper+'Send(T_U8 cmd,T_U8* p_data,T_U16 data_len,TE_BOOL need_ack){\n')
        ker_comm_file_list.append('    \n') 
        ker_comm_file_list.append('}\n')         
        
        ker_comm_file_list.append('\n')
        ker_comm_file_list.append('static void KerComm'+comm_id_first_upper+'RxTimeout(TE_KER_TIMER_ID e_time_id){\n')
        ker_comm_file_list.append('    (void)e_time_id;\n')
        ker_comm_file_list.append('    \n') 
        ker_comm_file_list.append('}\n')        
        
        ker_comm_file_list.append('\n')
        ker_comm_file_list.append('static void KerComm'+comm_id_first_upper+'WaitAckTimeout(TE_KER_TIMER_ID e_time_id){\n')
        ker_comm_file_list.append('    (void)e_time_id;\n')
        ker_comm_file_list.append('    \n') 
        ker_comm_file_list.append('}\n')
        
        
        
    dqns_gen_utility.DqnsGenListToFile(ker_comm_file_list,path_name) 

def genKerCommFiles(comm_config):
    #get comm id list from xml
    comm_id_list = getCommIDList(comm_config)    
    
    for comm_id in comm_id_list:
        h_path_name = r'..\..\kernel\platform\volatile\ker_comm_'+comm_id+'.h'
        c_path_name = r'..\..\kernel\platform\volatile\ker_comm_'+comm_id+'.c'
        #头文件不存在，先初始化
        if os.path.exists(h_path_name) == False:
            genKerCommFileInit(comm_config,comm_id)
        #源文件不存在，先初始化
        if os.path.exists(c_path_name) == False:
            genKerCommFileInit(comm_config,comm_id,False)
                    
        #刷新ker_comm_xxx.h, ker_comm_xxx.c不需要刷新了，genKerCommFileInit生成就可以了。
        # 1. 刷新<dqns_gen_comm_some_defines_begin> <dqns_gen_comm_some_defines_end>之间的宏定义
        some_definitions_list = getCommDefinitionsList(comm_config,comm_id)
        begin_str = '<dqns_gen_comm_some_defines_begin>'
        end_str = '<dqns_gen_comm_some_defines_end>'
        dqns_gen_utility.DqnsGenInsertListToFile(h_path_name,begin_str,end_str,some_definitions_list)
        
        # 2. 刷新<dqns_gen_comm_rx_cmd_begin> <dqns_gen_comm_rx_cmd_end>之间的cmd 枚举
        comm_rx_cmd_enum_list = getCommRxCmdEnumList(comm_config,comm_id)
        begin_str = '<dqns_gen_comm_rx_cmd_begin>'
        end_str = '<dqns_gen_comm_rx_cmd_end>'
        dqns_gen_utility.DqnsGenInsertListToFile(h_path_name,begin_str,end_str,comm_rx_cmd_enum_list)
        
        # 3. 刷新<dqns_gen_comm_tx_cmd_begin> <dqns_gen_comm_tx_cmd_end>之间的cmd 枚举
        comm_tx_cmd_enum_list = getCommTxCmdEnumList(comm_config,comm_id)
        begin_str = '<dqns_gen_comm_tx_cmd_begin>'
        end_str = '<dqns_gen_comm_tx_cmd_end>'
        dqns_gen_utility.DqnsGenInsertListToFile(h_path_name,begin_str,end_str,comm_tx_cmd_enum_list)
    
def genAppCommFileInit(comm_config,comm_id,is_head_file=True):
    path_name = r'..\..\app\comm\app_comm_'+comm_id
    app_comm_file_list = []   
    comm_id_first_upper = dqns_gen_utility.DqnsGenFirstToUpper(comm_id)
    if is_head_file:
        path_name += '.h'           
        app_comm_file_list.append('#ifndef APP_COMM_'+comm_id.upper()+'_H\n')
        app_comm_file_list.append('#define APP_COMM_'+comm_id.upper()+'_H\n')
        app_comm_file_list.append('\n')        
        app_comm_file_list.append('#ifdef __cplusplus\n')
        app_comm_file_list.append('extern "C"{\n')
        app_comm_file_list.append('#endif\n')
        app_comm_file_list.append('\n') 
        app_comm_file_list.append('void AppComm'+comm_id_first_upper+'Init(void);\n') 
        app_comm_file_list.append('\n')        
        app_comm_file_list.append('#ifdef __cplusplus\n')
        app_comm_file_list.append('}\n') 
        app_comm_file_list.append('#endif\n')
        app_comm_file_list.append('#endif\n') 
        
    else:
        path_name += '.c'
        app_comm_file_list.append('#include "../../kernel/platform/volatile/ker_comm_'+comm_id+'.h"\n')
        app_comm_file_list.append('#include "../../kernel/platform/stable/ker_comm.h"\n')
        app_comm_file_list.append('#include "../../kernel/platform/stable/ker_timer.h"\n')
        app_comm_file_list.append('#include "../../app/comm/app_comm_'+comm_id+'.h"\n')
        
        #声明，命令回调函数
        rx_cmd_list = getCommRxCmdList(comm_config,comm_id)
        app_comm_file_list.append('/*<dqns_gen_app_comm_cmd_handle_declaration_begin>*/\n')
        for rx_cmd in rx_cmd_list:            
            app_comm_file_list.append('static TE_COMM_RET_CODE AppComm'+comm_id_first_upper+'Rx'+rx_cmd+'(T_U8 cmd,T_U8* p_data,T_U16 data_len);\n')
        app_comm_file_list.append('/*<dqns_gen_app_comm_cmd_handle_declaration_end>*/\n')
        
        #初始化函数中，挂载命令回调函数
        app_comm_file_list.append('\n')
        app_comm_file_list.append('void AppComm'+comm_id_first_upper+'Init(void){\n')
        app_comm_file_list.append('    /*<dqns_gen_app_comm_cmd_handle_set_begin>*/\n')
        for rx_cmd in rx_cmd_list:
            app_comm_file_list.append('    M_KerCommSetParseHandle(E_KER_COMM_ID_'+comm_id.upper()+',(T_U8)E_KER_COMM_CMD_RX_'+comm_id.upper()+'_'+rx_cmd+',AppComm'+comm_id_first_upper+'Rx'+rx_cmd+');\n')
        app_comm_file_list.append('    /*<dqns_gen_app_comm_cmd_handle_set_end>*/\n')
        app_comm_file_list.append('}\n')        
        
        #定义，命令回调函数
        for rx_cmd in rx_cmd_list:
            app_comm_file_list.append('static TE_COMM_RET_CODE AppComm'+comm_id_first_upper+'Rx'+rx_cmd+'(T_U8 cmd,T_U8* p_data,T_U16 data_len){\n')
            app_comm_file_list.append('    M_Assert(p_data);\n')
            app_comm_file_list.append('\n')
            app_comm_file_list.append('    return E_COMM_RET_OK;\n')
            app_comm_file_list.append('\n')
            app_comm_file_list.append('}\n')
            app_comm_file_list.append('\n')
        
        #这里用脚本生成的回调函数框架（非初始化时），请移出去实现，防止被脚本冲掉。
        app_comm_file_list.append('\n')
        #app_comm_file_list.append('/*这里用脚本生成的回调函数框架（非初始化时），请移出去实现，防止被脚本冲掉。*/\n')
        #app_comm_file_list.append('/*如果已经在外面实现，请删除。*/\n')
        app_comm_file_list.append('/*<dqns_gen_app_comm_cmd_handle_definition_begin>*/\n')
        app_comm_file_list.append('\n')
        app_comm_file_list.append('/*<dqns_gen_app_comm_cmd_handle_definition_end>*/\n')
        app_comm_file_list.append('\n')

    dqns_gen_utility.DqnsGenListToFile(app_comm_file_list,path_name)

def genAppCommFiles(comm_config):
    #get comm id list from xml
    comm_id_list = getCommIDList(comm_config)   
    
    for comm_id in comm_id_list:
        h_path_name = r'..\..\app\comm\app_comm_'+comm_id+'.h'
        c_path_name = r'..\..\app\comm\app_comm_'+comm_id+'.c'
        #头文件不存在，先初始化
        if os.path.exists(h_path_name) == False:
            genAppCommFileInit(comm_config,comm_id)
        #源文件不存在，先初始化
        if os.path.exists(c_path_name) == False:
            genAppCommFileInit(comm_config,comm_id,False)
        
        #刷新app_comm_xxx.c, app_comm_xxx.h不需要刷新了
        # 1. 刷新命令回调函数的声明
        cmd_handle_declaration_list = getCommRxCmdHandleDeclarationList(comm_config,comm_id)
        begin_str = '<dqns_gen_app_comm_cmd_handle_declaration_begin>'
        end_str = '<dqns_gen_app_comm_cmd_handle_declaration_end>'
        print('c_path_name:'+c_path_name+'\n')
        dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,cmd_handle_declaration_list)
        
        # 2. 刷新初始化函数中，命令回调函数的set
        cmd_handle_set_list = getCommRxCmdHandleSetList(comm_config,comm_id)
        begin_str = '<dqns_gen_app_comm_cmd_handle_set_begin>'
        end_str = '<dqns_gen_app_comm_cmd_handle_set_end>'
        dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,cmd_handle_set_list)
        
        # 3. 刷新命令回调函数的定义
        cmd_handle_definition_list = getCommRxCmdHandleDefinitionList(comm_config,comm_id)
        begin_str = '<dqns_gen_app_comm_cmd_handle_definition_begin>'
        end_str = '<dqns_gen_app_comm_cmd_handle_definition_end>'
        dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,cmd_handle_definition_list)
            
                    
def CommGen(comm_config):

    comm_user_h = r'..\..\kernel\platform\volatile\ker_comm_user.h'
    comm_user_c = r'..\..\kernel\platform\volatile\ker_comm_user.c'

    # #include "ker_comm_xxx.h" 写入ker_comm_user.h，---------------------------------------  begin
    #在文件"ker_comm_user.h"的<dqns_gen_comm_head_begin>,<dqns_gen_comm_head_end>段落插入内容
    #把文件"ker_comm_user.h"按行读入list
    user_comm_head_prefix_str = '#include "ker_comm_'
    user_comm_head_begin = '<dqns_gen_include_comm_head_begin>'
    user_comm_head_end = '<dqns_gen_include_comm_head_end>'
    #comm_user_h_list = dqns_gen_utility.DqnsGenGetFileList(comm_user_h)
    #xml中找到comm id，稍作处理加入list并返回    
    xml_list = getCommIDFromXML(comm_config,user_comm_head_prefix_str,'.h"',False)
    #把xml list中的内容覆盖掉 begin和end之间的内容，并返回list
    #write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(user_comm_head_begin,user_comm_head_end,comm_user_h_list,xml_list)
    #将上面得到的list，write_to_file_list，写入文件"ker_comm_user.h"
    #dqns_gen_utility.DqnsGenListToFile(write_to_file_list,comm_user_h) 
    dqns_gen_utility.DqnsGenInsertListToFile(comm_user_h,user_comm_head_begin,user_comm_head_end,xml_list)
    
    # #include "ker_comm_xxx.h" 写入ker_comm_user.h，---------------------------------------  end
    
    

    #comm id 写入ker_comm_user.h，-------------------------------------------------------------  begin          
    user_comm_id_prefix_str = '    E_KER_COMM_ID_'
    user_comm_id_begin = '<dqns_gen_comm_id_begin>'
    user_comm_id_end = '<dqns_gen_comm_id_end>'
    
    #在文件"ker_comm_user.h"的<dqns_gen_comm_id_begin>,<dqns_gen_comm_id_end>段落插入内容
    #把文件"ker_comm_user.h"按行读入list
    comm_user_h_list = dqns_gen_utility.DqnsGenGetFileList(comm_user_h)
    #xml中找到comm id，稍作处理加入list并返回    
    xml_list = getCommIDFromXML(comm_config,user_comm_id_prefix_str,',')
    #把xml list中的内容覆盖掉 begin和end之间的内容，并返回list
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(user_comm_id_begin,user_comm_id_end,comm_user_h_list,xml_list)
    #将上面得到的list，write_to_file_list，写入文件"ker_comm_user.h"
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,comm_user_h)    
    #comm id 写入ker_comm_user.h，-------------------------------------------------------------  end
    
    #comm obj 声明， 写入ker_comm_user.c，-------------------------------------------------------------  begin
    user_comm_declaration_begin = '<dqns_gen_comm_obj_begin>'
    user_comm_declaration_end = '<dqns_gen_comm_obj_end>'
    user_comm_declaration_prefix_str = 'extern TS_KER_COMM_INFO gg_comm_'
    #把文件"ker_comm_user.c"按行读入list
    comm_user_c_list = dqns_gen_utility.DqnsGenGetFileList(comm_user_c)
    xml_list = getCommIDFromXML(comm_config,user_comm_declaration_prefix_str,';',False)
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(user_comm_declaration_begin,user_comm_declaration_end,comm_user_c_list,xml_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,comm_user_c) 
    #comm obj 声明， 写入ker_comm_user.c，-------------------------------------------------------------  end
    
    #comm object table， 写入ker_comm_user.c，-------------------------------------------------------------  begin
    user_comm_obj_tbl_begin = '<dqns_gen_comm_obj_tbl_begin>'
    user_comm_obj_tbl_end = '<dqns_gen_comm_obj_tbl_end>'
    user_comm_obj_tbl_prefix_str = '    &gg_comm_'
    #把文件"ker_comm_user.c"按行读入list
    comm_user_c_list = dqns_gen_utility.DqnsGenGetFileList(comm_user_c)
    xml_list = getCommIDFromXML(comm_config,user_comm_obj_tbl_prefix_str,',',False)
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(user_comm_obj_tbl_begin,user_comm_obj_tbl_end,comm_user_c_list,xml_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,comm_user_c) 
    #comm object table， 写入ker_comm_user.c，-------------------------------------------------------------  end
    
    #'    KerCommExtInit();'，写入ker_comm_user.c，------------------------------begin
    user_comm_init_begin = '<dqns_gen_comm_user_init_begin>'    
    user_comm_init_end = '<dqns_gen_comm_user_init_end>'
    comm_id_list = getCommIDList(comm_config)
    comm_init_list = []
    for comm_id in comm_id_list:
        first_upper_comm_id = dqns_gen_utility.DqnsGenFirstToUpper(comm_id)
        comm_init_list.append('    KerComm'+first_upper_comm_id+'Init();\n')
    dqns_gen_utility.DqnsGenInsertListToFile(comm_user_c,user_comm_init_begin,user_comm_init_end,comm_init_list)
    
    #'    KerCommExtInit();'，写入ker_comm_user.c，------------------------------end
    
    #生成ker_comm_xxx.h, ker_comm_xxx.c
    genKerCommFiles(comm_config)
    
    #生成app_comm_xxx.h, app_comm_xxx.c
    genAppCommFiles(comm_config)
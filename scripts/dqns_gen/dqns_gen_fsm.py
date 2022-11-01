import os
import dqns_gen_utility

def getStateIDFromXML(fsm_config,prefix_str,tail,need_to_upper=True):
    xml_list = []
    
    for item in fsm_config:
        if item.tag == 'state_id':
            if need_to_upper:
                item_str = prefix_str+item.attrib['ID'].upper()+tail+'\n'
            else:
                item_str = prefix_str+item.attrib['ID']+tail+'\n'
            xml_list.append(item_str)
    
    return xml_list
    
def getStateIDList(fsm_config):

    state_id_list = []
    
    for item in fsm_config:
        if item.tag == 'state_id':
            item_str = item.attrib['ID']
            state_id_list.append(item_str)
    
    return state_id_list
    
def genAppStateFileInit(state_id,is_head_file=True): 
    
    path_name = r'..\..\app\state\app_state_'+state_id
    app_state_file_list = []   
    state_id_first_upper = dqns_gen_utility.DqnsGenFirstToUpper(state_id)
    camel_state_id = dqns_gen_utility.DqnsGenCamelStr(state_id)
    if is_head_file:  
        path_name += '.h'
        app_state_file_list.append('#ifndef APP_STATE_'+state_id.upper()+'_H\n')
        app_state_file_list.append('#define APP_STATE_'+state_id.upper()+'_H\n')
        app_state_file_list.append('\n')
        app_state_file_list.append('#ifdef __cplusplus\n')
        app_state_file_list.append('extern "C"{\n')
        app_state_file_list.append('#endif\n')
        app_state_file_list.append('\n')
        app_state_file_list.append('#include "../../common/common.h"\n')
        app_state_file_list.append('#include "../../kernel/platform/stable/ker_timer.h"\n')
        app_state_file_list.append('#include "../../kernel/platform/stable/ker_msg.h"\n')
        app_state_file_list.append('#include "../../kernel/platform/stable/ker_fsm.h"\n')
        app_state_file_list.append('#include "../../kernel/platform/stable/ker_key.h"\n')
        app_state_file_list.append('#include "../../kernel/platform/stable/ker_pin.h"\n')
        app_state_file_list.append('\n')
        app_state_file_list.append('void AppState'+camel_state_id+'Init(void);\n')
        app_state_file_list.append('\n')
        app_state_file_list.append('#ifdef __cplusplus\n')
        app_state_file_list.append('}\n')
        app_state_file_list.append('#endif\n')
        app_state_file_list.append('\n')
        app_state_file_list.append('#endif\n')        
        
    else:
        path_name += '.c'
        #app_state_file_list.append('#include "../../kernel/platform/stable/ker_fsm.h"\n')
        app_state_file_list.append('#include "app_state_'+state_id+'.h"\n')
        app_state_file_list.append('\n')        
        app_state_file_list.append('extern TS_KER_STATE gg_app_state_'+state_id+';\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('static void AppState'+camel_state_id+'Enter(void* param);\n') 
        app_state_file_list.append('static void AppState'+camel_state_id+'Leave(void);\n') 
        app_state_file_list.append('\n') 
        
        app_state_file_list.append('/*<dqns_gen_timer_handle_declare_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_timer_handle_declare_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('/*<dqns_gen_key_press_handle_declare_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_press_handle_declare_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('/*<dqns_gen_key_lp1_handle_declare_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_lp1_handle_declare_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('/*<dqns_gen_key_lp2_handle_declare_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_lp2_handle_declare_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('/*<dqns_gen_key_lp3_handle_declare_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_lp3_handle_declare_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('/*<dqns_gen_key_release_handle_declare_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_release_handle_declare_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('/*<dqns_gen_key_combine_handle_declare_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_combine_handle_declare_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('/*<dqns_gen_user_msg_handle_declare_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_user_msg_handle_declare_end>*/\n')
        app_state_file_list.append('\n') 
        
        app_state_file_list.append('void AppState'+camel_state_id+'Init(void){\n')
        app_state_file_list.append('    KerFSMStateBind(E_KER_STATE_ID_'+state_id.upper()+',AppState'+camel_state_id+'Enter,AppState'+camel_state_id+'Leave);\n')
        app_state_file_list.append('}\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('static void AppState'+camel_state_id+'Enter(void* param){\n')
        app_state_file_list.append('    (void)param;\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('    /*<dqns_gen_timer_handle_tbl_begin>*/\n')
        app_state_file_list.append('    /*<dqns_gen_timer_handle_tbl_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('    /*<dqns_gen_key_press_handle_tbl_begin>*/\n')
        app_state_file_list.append('    /*<dqns_gen_key_press_handle_tbl_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('    /*<dqns_gen_key_lp1_handle_tbl_begin>*/\n')
        app_state_file_list.append('    /*<dqns_gen_key_lp1_handle_tbl_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('    /*<dqns_gen_key_lp2_handle_tbl_begin>*/\n')
        app_state_file_list.append('    /*<dqns_gen_key_lp2_handle_tbl_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('    /*<dqns_gen_key_lp3_handle_tbl_begin>*/\n')
        app_state_file_list.append('    /*<dqns_gen_key_lp3_handle_tbl_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('    /*<dqns_gen_key_release_handle_tbl_begin>*/\n')
        app_state_file_list.append('    /*<dqns_gen_key_release_handle_tbl_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('    /*<dqns_gen_key_combine_handle_tbl_begin>*/\n')
        app_state_file_list.append('    /*<dqns_gen_key_combine_handle_tbl_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('    /*<dqns_gen_user_msg_handle_tbl_begin>*/\n')
        app_state_file_list.append('    /*<dqns_gen_user_msg_handle_tbl_end>*/\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('}\n')
        app_state_file_list.append('static void AppState'+camel_state_id+'Leave(void){\n')
        app_state_file_list.append('\n') 
        app_state_file_list.append('}\n') 
        app_state_file_list.append('\n') 
        
        #app_state_file_list.append('/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/\n')
        app_state_file_list.append('/*<dqns_gen_timer_handle_definition_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_timer_handle_definition_end>*/\n')
        app_state_file_list.append('\n') 
        #app_state_file_list.append('/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/\n')
        app_state_file_list.append('/*<dqns_gen_key_press_handle_definition_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_press_handle_definition_end>*/\n')
        app_state_file_list.append('\n') 
        #app_state_file_list.append('/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/\n')
        app_state_file_list.append('/*<dqns_gen_key_lp1_handle_definition_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_lp1_handle_definition_end>*/\n')
        app_state_file_list.append('\n') 
        #app_state_file_list.append('/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/\n')
        app_state_file_list.append('/*<dqns_gen_key_lp2_handle_definition_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_lp2_handle_definition_end>*/\n')
        app_state_file_list.append('\n') 
        #app_state_file_list.append('/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/\n')
        app_state_file_list.append('/*<dqns_gen_key_lp3_handle_definition_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_lp3_handle_definition_end>*/\n')
        app_state_file_list.append('\n') 
        #app_state_file_list.append('/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/\n')
        app_state_file_list.append('/*<dqns_gen_key_release_handle_definition_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_release_handle_definition_end>*/\n')
        app_state_file_list.append('\n')
        #app_state_file_list.append('/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/\n')
        app_state_file_list.append('/*<dqns_gen_key_combine_handle_definition_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_key_combine_handle_definition_end>*/\n')
        app_state_file_list.append('\n')
        #app_state_file_list.append('/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/\n')
        app_state_file_list.append('/*<dqns_gen_user_msg_handle_definition_begin>*/\n')
        app_state_file_list.append('/*<dqns_gen_user_msg_handle_definition_end>*/\n')
        app_state_file_list.append('\n') 
        
    dqns_gen_utility.DqnsGenListToFile(app_state_file_list,path_name)        

#基于已经生成的app_state_xxx.c 的基础上，声明timer handle，定义timer handle，以及在enter里面设置timer handle
def genTimerHandle(state_id,timer_handle_map):
    c_path_name = r'..\..\app\state\app_state_'+state_id+'.c'
    timer_handle_declare_list = []
    timer_handle_definition_list = []
    timer_handle_tbl_list = []
    
    begin_str = '<dqns_gen_timer_handle_definition_begin>'
    end_str = '<dqns_gen_timer_handle_definition_end>'
    th_definition_list = dqns_gen_utility.DqnsGenGetListFromFile(begin_str,end_str,c_path_name)
    
    for item in timer_handle_map:
        timer_handle_declare_str = 'static void '+item[1]+'(TE_KER_TIMER_ID e_timer_id);\n'
        timer_handle_declare_list.append(timer_handle_declare_str)
        
        if not dqns_gen_utility.DqnsGenIsTextInList(th_definition_list, item[1]):
            timer_handle_definition_str = 'static void '+item[1]+'(TE_KER_TIMER_ID e_timer_id){\n\n}\n'        
            timer_handle_definition_list.append(timer_handle_definition_str)
        
        timer_handle_tbl_str = '    KerTimerBind('+item[0]+','+item[1]+');\n'
        timer_handle_tbl_list.append(timer_handle_tbl_str)
        
    
    #timer handle 声明写入 app_state_xxx.c
    begin_str = '<dqns_gen_timer_handle_declare_begin>'
    end_str = '<dqns_gen_timer_handle_declare_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,timer_handle_declare_list)
    
    #timer handle 定义写入 app_state_xxx.c
    begin_str = '<dqns_gen_timer_handle_definition_begin>'
    end_str = '<dqns_gen_timer_handle_definition_end>'
    timer_handle_definition_list += th_definition_list
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,timer_handle_definition_list)
    
    #timer id, timer handle 绑定写入 app_state_xxx.c
    begin_str = '<dqns_gen_timer_handle_tbl_begin>'
    end_str = '<dqns_gen_timer_handle_tbl_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,timer_handle_tbl_list)
    
    
#基于已经生成的app_state_xxx.c 的基础上，声明key press handle，定义key press handle，以及在enter里面设置key press handle
def genKeyPressHandle(state_id,key_press_handle_map):
    c_path_name = r'..\..\app\state\app_state_'+state_id+'.c'
    key_press_handle_declare_list = []
    key_press_handle_definition_list = []
    key_press_handle_tbl_list = []
    
    begin_str = '<dqns_gen_key_press_handle_definition_begin>'
    end_str = '<dqns_gen_key_press_handle_definition_end>'
    kph_definition_list = dqns_gen_utility.DqnsGenGetListFromFile(begin_str,end_str,c_path_name)
    
    for item in key_press_handle_map:
        key_press_handle_declare_str = 'static TE_BOOL '+item[1]+'(void);\n'
        key_press_handle_declare_list.append(key_press_handle_declare_str)
        
        if not dqns_gen_utility.DqnsGenIsTextInList(kph_definition_list, item[1]):
            key_press_handle_definition_str = 'static TE_BOOL '+item[1]+'(void){\n    return E_FALSE;\n}\n'
            key_press_handle_definition_list.append(key_press_handle_definition_str)
        
        key_press_handle_tbl_str = '    KerKeyBind('+item[0]+','+'E_KEY_MSG_TYPE_PRESS,'+item[1]+');\n'
        key_press_handle_tbl_list.append(key_press_handle_tbl_str)
        
    
    #key press handle 声明写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_press_handle_declare_begin>'
    end_str = '<dqns_gen_key_press_handle_declare_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_press_handle_declare_list)
    
    #key press handle 定义写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_press_handle_definition_begin>'
    end_str = '<dqns_gen_key_press_handle_definition_end>'
    key_press_handle_definition_list += kph_definition_list
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_press_handle_definition_list)
    
    #key id, key press handle 绑定写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_press_handle_tbl_begin>'
    end_str = '<dqns_gen_key_press_handle_tbl_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_press_handle_tbl_list)
    

#基于已经生成的app_state_xxx.c 的基础上，声明long press 1 handle，定义long press 1 handle，以及在enter里面设置long press 1 handle
def genKeyLp1Handle(state_id,key_lp1_handle_map):
    c_path_name = r'..\..\app\state\app_state_'+state_id+'.c'
    key_lp1_handle_declare_list = []
    key_lp1_handle_definition_list = []
    key_lp1_handle_tbl_list = []
    
    begin_str = '<dqns_gen_key_lp1_handle_definition_begin>'
    end_str = '<dqns_gen_key_lp1_handle_definition_end>'
    lp1h_definition_list = dqns_gen_utility.DqnsGenGetListFromFile(begin_str,end_str,c_path_name)

    for item in key_lp1_handle_map:
        key_lp1_handle_declare_str = 'static TE_BOOL '+item[1]+'(void);\n'
        key_lp1_handle_declare_list.append(key_lp1_handle_declare_str)
        
        if not dqns_gen_utility.DqnsGenIsTextInList(lp1h_definition_list, item[1]):
            key_lp1_handle_definition_str = 'static TE_BOOL '+item[1]+'(void){\n    return E_FALSE;\n}\n'
            key_lp1_handle_definition_list.append(key_lp1_handle_definition_str)
        
        key_lp1_handle_tbl_str = '    KerKeyBind('+item[0]+','+'E_KEY_MSG_TYPE_LONG_PRESS_1,'+item[1]+');\n'
        key_lp1_handle_tbl_list.append(key_lp1_handle_tbl_str)
        
    
    #long press handle 1 声明写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_lp1_handle_declare_begin>'
    end_str = '<dqns_gen_key_lp1_handle_declare_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_lp1_handle_declare_list)
    
    #long press handle 1 定义写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_lp1_handle_definition_begin>'
    end_str = '<dqns_gen_key_lp1_handle_definition_end>'
    key_lp1_handle_definition_list += lp1h_definition_list
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_lp1_handle_definition_list)
    
    #key id, long press handle 1 绑定写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_lp1_handle_tbl_begin>'
    end_str = '<dqns_gen_key_lp1_handle_tbl_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_lp1_handle_tbl_list)

#基于已经生成的app_state_xxx.c 的基础上，声明long press 2 handle，定义long press 2 handle，以及在enter里面设置long press 2 handle
def genKeyLp2Handle(state_id,key_lp2_handle_map):
    c_path_name = r'..\..\app\state\app_state_'+state_id+'.c'
    key_lp2_handle_declare_list = []
    key_lp2_handle_definition_list = []
    key_lp2_handle_tbl_list = []
    
    begin_str = '<dqns_gen_key_lp2_handle_definition_begin>'
    end_str = '<dqns_gen_key_lp2_handle_definition_end>'
    lp2h_definition_list = dqns_gen_utility.DqnsGenGetListFromFile(begin_str,end_str,c_path_name)
    
    for item in key_lp2_handle_map:
        key_lp2_handle_declare_str = 'static TE_BOOL '+item[1]+'(void);\n'
        key_lp2_handle_declare_list.append(key_lp2_handle_declare_str)
        
        if not dqns_gen_utility.DqnsGenIsTextInList(lp2h_definition_list, item[1]):
            key_lp2_handle_definition_str = 'static TE_BOOL '+item[1]+'(void){\n    return E_FALSE;\n}\n'
            key_lp2_handle_definition_list.append(key_lp2_handle_definition_str)
        
        key_lp2_handle_tbl_str = '    KerKeyBind('+item[0]+','+'E_KEY_MSG_TYPE_LONG_PRESS_2,'+item[1]+');\n'
        key_lp2_handle_tbl_list.append(key_lp2_handle_tbl_str)
        
    
    #long press handle 2 声明写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_lp2_handle_declare_begin>'
    end_str = '<dqns_gen_key_lp2_handle_declare_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_lp2_handle_declare_list)
    
    #long press handle 2 定义写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_lp2_handle_definition_begin>'
    end_str = '<dqns_gen_key_lp2_handle_definition_end>'
    key_lp2_handle_definition_list += lp2h_definition_list
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_lp2_handle_definition_list)
    
    #key id, long press handle 2 绑定写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_lp2_handle_tbl_begin>'
    end_str = '<dqns_gen_key_lp2_handle_tbl_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_lp2_handle_tbl_list)
    
    
#基于已经生成的app_state_xxx.c 的基础上，声明long press 3 handle，定义long press 3 handle，以及在enter里面设置long press 3 handle
def genKeyLp3Handle(state_id,key_lp3_handle_map):
    c_path_name = r'..\..\app\state\app_state_'+state_id+'.c'
    key_lp3_handle_declare_list = []
    key_lp3_handle_definition_list = []
    key_lp3_handle_tbl_list = []
    
    begin_str = '<dqns_gen_key_lp3_handle_definition_begin>'
    end_str = '<dqns_gen_key_lp3_handle_definition_end>'
    lp3h_definition_list = dqns_gen_utility.DqnsGenGetListFromFile(begin_str,end_str,c_path_name)
    
    for item in key_lp3_handle_map:
        key_lp3_handle_declare_str = 'static TE_BOOL '+item[1]+'(void);\n'
        key_lp3_handle_declare_list.append(key_lp3_handle_declare_str)
        
        if not dqns_gen_utility.DqnsGenIsTextInList(lp3h_definition_list, item[1]):
            key_lp3_handle_definition_str = 'static TE_BOOL '+item[1]+'(void){\n    return E_FALSE;\n}\n'
            key_lp3_handle_definition_list.append(key_lp3_handle_definition_str)
        
        key_lp3_handle_tbl_str = '    KerKeyBind('+item[0]+','+'E_KEY_MSG_TYPE_LONG_PRESS_3,'+item[1]+');\n'
        key_lp3_handle_tbl_list.append(key_lp3_handle_tbl_str)
        
    
    #long press handle 3 声明写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_lp3_handle_declare_begin>'
    end_str = '<dqns_gen_key_lp3_handle_declare_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_lp3_handle_declare_list)
    
    #long press handle 3 定义写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_lp3_handle_definition_begin>'
    end_str = '<dqns_gen_key_lp3_handle_definition_end>'
    key_lp3_handle_definition_list += lp3h_definition_list
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_lp3_handle_definition_list)
    
    #key id, long press handle 3 绑定写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_lp3_handle_tbl_begin>'
    end_str = '<dqns_gen_key_lp3_handle_tbl_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_lp3_handle_tbl_list)
    
    
#基于已经生成的app_state_xxx.c 的基础上，声明key release handle，定义key release handle，以及在enter里面设置key release handle
def genKeyReleaseHandle(state_id,key_release_handle_map):
    c_path_name = r'..\..\app\state\app_state_'+state_id+'.c'
    key_release_handle_declare_list = []
    key_release_handle_definition_list = []
    key_release_handle_tbl_list = []
    
    begin_str = '<dqns_gen_key_release_handle_definition_begin>'
    end_str = '<dqns_gen_key_release_handle_definition_end>'
    krh_definition_list = dqns_gen_utility.DqnsGenGetListFromFile(begin_str,end_str,c_path_name)
    
    for item in key_release_handle_map:
        key_release_handle_declare_str = 'static TE_BOOL '+item[1]+'(void);\n'
        key_release_handle_declare_list.append(key_release_handle_declare_str)
        
        if not dqns_gen_utility.DqnsGenIsTextInList(krh_definition_list, item[1]):
            key_release_handle_definition_str = 'static TE_BOOL '+item[1]+'(void){\n    return E_FALSE;\n}\n'
            key_release_handle_definition_list.append(key_release_handle_definition_str)
        
        key_release_handle_tbl_str = '    KerKeyBind('+item[0]+','+'E_KEY_MSG_TYPE_RELEASE,'+item[1]+');\n'
        key_release_handle_tbl_list.append(key_release_handle_tbl_str)
        
    
    #key release handle 声明写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_release_handle_declare_begin>'
    end_str = '<dqns_gen_key_release_handle_declare_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_release_handle_declare_list)
    
    #key release handle 定义写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_release_handle_definition_begin>'
    end_str = '<dqns_gen_key_release_handle_definition_end>'
    key_release_handle_definition_list += krh_definition_list
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_release_handle_definition_list)
    
    #key id, key release handle 绑定写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_release_handle_tbl_begin>'
    end_str = '<dqns_gen_key_release_handle_tbl_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_release_handle_tbl_list)



#基于已经生成的app_state_xxx.c 的基础上，声明key combine handle，定义key combine handle，以及在enter里面设置combine key handle
def genKeyCombineHandle(state_id,key_combine_handle_map):
    c_path_name = r'..\..\app\state\app_state_'+state_id+'.c'
    key_combine_handle_declare_list = []
    key_combine_handle_definition_list = []
    key_combine_handle_tbl_list = []
    
    begin_str = '<dqns_gen_key_combine_handle_definition_begin>'
    end_str = '<dqns_gen_key_combine_handle_definition_end>'
    kch_definition_list = dqns_gen_utility.DqnsGenGetListFromFile(begin_str,end_str,c_path_name)
    
    for item in key_combine_handle_map:
        key_combine_handle_declare_str = 'static TE_BOOL '+item[1]+'(void);\n'
        key_combine_handle_declare_list.append(key_combine_handle_declare_str)
        
        if not dqns_gen_utility.DqnsGenIsTextInList(kch_definition_list, item[1]):
            key_combine_handle_definition_str = 'static TE_BOOL '+item[1]+'(void){\n    return E_FALSE;\n}\n'
            key_combine_handle_definition_list.append(key_combine_handle_definition_str)
        
        key_combine_handle_tbl_str = '    KerKeyCombineBind('+item[0]+','+item[1]+');\n'
        key_combine_handle_tbl_list.append(key_combine_handle_tbl_str)
        
    
    #combine key  handle 声明写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_combine_handle_declare_begin>'
    end_str = '<dqns_gen_key_combine_handle_declare_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_combine_handle_declare_list)
    
    #key combine handle 定义写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_combine_handle_definition_begin>'
    end_str = '<dqns_gen_key_combine_handle_definition_end>'
    key_combine_handle_definition_list += kch_definition_list
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_combine_handle_definition_list)
    
    #combine key id, combine key handle 绑定写入 app_state_xxx.c
    begin_str = '<dqns_gen_key_combine_handle_tbl_begin>'
    end_str = '<dqns_gen_key_combine_handle_tbl_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,key_combine_handle_tbl_list)


#基于已经生成的app_state_xxx.c 的基础上，声明user message handle，定义user message handle，以及在enter里面设置user message handle
def genUserMsgHandle(state_id,user_msg_handle_map):
    c_path_name = r'..\..\app\state\app_state_'+state_id+'.c'
    user_msg_handle_declare_list = []
    user_msg_handle_definition_list = []
    user_msg_handle_tbl_list = []
    
    begin_str = '<dqns_gen_user_msg_handle_definition_begin>'
    end_str = '<dqns_gen_user_msg_handle_definition_end>'
    umh_definition_list = dqns_gen_utility.DqnsGenGetListFromFile(begin_str,end_str,c_path_name)
       
    for item in user_msg_handle_map:
        user_msg_handle_declare_str = 'static TE_BOOL '+item[1]+'(void* param);\n'
        user_msg_handle_declare_list.append(user_msg_handle_declare_str)
        
        if not dqns_gen_utility.DqnsGenIsTextInList(umh_definition_list, item[1]):                        
            user_msg_handle_definition_str = 'static TE_BOOL '+item[1]+'(void* param){\n    return E_FALSE;\n}\n'
            user_msg_handle_definition_list.append(user_msg_handle_definition_str)
        
        user_msg_handle_tbl_str = '    KerMsgBind('+item[0]+','+item[1]+');\n'
        user_msg_handle_tbl_list.append(user_msg_handle_tbl_str)
        
    
    #user message  handle 声明写入 app_state_xxx.c
    begin_str = '<dqns_gen_user_msg_handle_declare_begin>'
    end_str = '<dqns_gen_user_msg_handle_declare_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,user_msg_handle_declare_list)
    
    #user message handle 定义写入 app_state_xxx.c
    begin_str = '<dqns_gen_user_msg_handle_definition_begin>'
    end_str = '<dqns_gen_user_msg_handle_definition_end>'
    user_msg_handle_definition_list += umh_definition_list
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,user_msg_handle_definition_list)
    
    #user message id, user message handle 绑定写入 app_state_xxx.c
    begin_str = '<dqns_gen_user_msg_handle_tbl_begin>'
    end_str = '<dqns_gen_user_msg_handle_tbl_end>'
    dqns_gen_utility.DqnsGenInsertListToFile(c_path_name,begin_str,end_str,user_msg_handle_tbl_list)


    
def genAppStateFiles(fsm_config):
    #get state id list from xml
    state_id_list = getStateIDList(fsm_config)
    
    timer_handle_map = []
    key_press_handle_map = []
    key_lp1_handle_map = []
    key_lp2_handle_map = []
    key_lp3_handle_map = []
    key_release_handle_map = []
    key_combine_handle_map = []
    user_msg_handle_map = []
    
    timer_handle_config = None
    key_press_handle_config = None
    lp1_handle_config = None
    lp2_handle_config = None
    lp3_handle_config = None
    key_release_handle_config = None
    key_combine_handle_config = None
    user_msg_handle_config = None
    state_id_config = None
    
    for state_id in state_id_list:
        h_path_name = r'..\..\app\state\app_state_'+state_id+'.h'
        c_path_name = r'..\..\app\state\app_state_'+state_id+'.c'
        #头文件不存在，先初始化
        if os.path.exists(h_path_name) == False:
            genAppStateFileInit(state_id)
        #源文件不存在，先初始化
        if os.path.exists(c_path_name) == False:
            genAppStateFileInit(state_id,False)
        
        first_upper_state_id = dqns_gen_utility.DqnsGenFirstToUpper(state_id)
        camel_state_id = dqns_gen_utility.DqnsGenCamelStr(state_id)
        
        for item in fsm_config:
            if item.attrib['ID'] == state_id:
                
                timer_handle_config = None
                key_press_handle_config = None
                key_lp1_handle_config = None
                key_lp2_handle_config = None
                key_lp3_handle_config = None
                key_release_handle_config = None
                key_combine_handle_config = None
                user_msg_handle_config = None
                state_id_config = None
                
                timer_handle_map = []
                key_press_handle_map = []
                key_lp1_handle_map = []
                key_lp2_handle_map = []
                key_lp3_handle_map = []
                key_release_handle_map = []
                key_combine_handle_map = []
                user_msg_handle_map = []
            
                #寻找 timer_bind_tbl
                for item1 in item:
                    if item1.tag == 'timer_bind_tbl':
                        timer_handle_config = item1
                        break
                if timer_handle_config != None:
                    for timer_bind in timer_handle_config:
                        if timer_bind.tag == 'TIMER_BIND':
                            timer_id = 'E_KER_TIMER_'+timer_bind.attrib['ID'].upper()
                            #first_upper_state_id = dqns_gen_utility.DqnsGenFirstToUpper(state_id)
                            camel_timer_id = dqns_gen_utility.DqnsGenCamelStr(timer_bind.attrib['ID'])
                            timer_handle = 'AppState'+camel_state_id+camel_timer_id+'TimerHandle'
                            timer_handle_map.append((timer_id,timer_handle)) 
                    #把timer handle相关的声明、定义，以及timer id和timer handle的映射关系写入 app_state_xxx.c                            
                    genTimerHandle(state_id,timer_handle_map)   
                    
                            
                #寻找 key_press_tbl
                for item1 in item:
                    if item1.tag == 'key_press_tbl':
                        key_press_handle_config = item1
                        break
                if key_press_handle_config != None:
                    for key_press_bind in key_press_handle_config:
                        if key_press_bind.tag == 'KEY_PRESS_BIND':
                            key_id = 'E_KER_KEY_'+key_press_bind.attrib['ID'].upper()
                            camel_key_id = dqns_gen_utility.DqnsGenCamelStr(key_press_bind.attrib['ID'])
                            key_press_handle = 'AppState'+camel_state_id+'Key'+camel_key_id+'PressHandle'
                            key_press_handle_map.append((key_id,key_press_handle))
                    #把key press handle相关的声明、定义，以及key id和key press handle的映射关系写入 app_state_xxx.c   
                    #if len(key_press_handle_map) > 0:
                    genKeyPressHandle(state_id,key_press_handle_map)  
                    
                    
                #寻找 key_lp1_tbl
                for item1 in item:
                    if item1.tag == 'key_lp1_tbl':
                        key_lp1_handle_config = item1
                        break
                if key_lp1_handle_config != None:
                    for key_lp1_bind in key_lp1_handle_config:
                        if key_lp1_bind.tag == 'KEY_LP1_BIND':
                            key_id = 'E_KER_KEY_'+key_lp1_bind.attrib['ID'].upper()
                            camel_key_id = dqns_gen_utility.DqnsGenCamelStr(key_lp1_bind.attrib['ID'])
                            key_lp1_handle = 'AppState'+camel_state_id+'Key'+camel_key_id+'Lp1Handle'
                            key_lp1_handle_map.append((key_id,key_lp1_handle))
                    #把key lp1 handle相关的声明、定义，以及key id和key lp1 handle的映射关系写入 app_state_xxx.c   
                    #if len(key_lp1_handle_map) > 0:
                    genKeyLp1Handle(state_id,key_lp1_handle_map)
                
                #寻找 key_lp2_tbl
                for item1 in item:
                    if item1.tag == 'key_lp2_tbl':
                        key_lp2_handle_config = item1
                        break
                if key_lp2_handle_config != None:
                    for key_lp2_bind in key_lp2_handle_config:
                        if key_lp2_bind.tag == 'KEY_LP2_BIND':
                            key_id = 'E_KER_KEY_'+key_lp2_bind.attrib['ID'].upper()
                            camel_key_id = dqns_gen_utility.DqnsGenCamelStr(key_lp2_bind.attrib['ID'])
                            key_lp2_handle = 'AppState'+camel_state_id+'Key'+camel_key_id+'Lp2Handle'
                            key_lp2_handle_map.append((key_id,key_lp2_handle))
                    #把key lp2 handle相关的声明、定义，以及key id和key lp2 handle的映射关系写入 app_state_xxx.c   
                    #if len(key_lp2_handle_map) > 0:
                    genKeyLp2Handle(state_id,key_lp2_handle_map)
                
                            
                #寻找 key_lp3_tbl
                for item1 in item:
                    if item1.tag == 'key_lp3_tbl':
                        key_lp3_handle_config = item1
                        break
                if key_lp3_handle_config != None:
                    for key_lp3_bind in key_lp3_handle_config:
                        if key_lp3_bind.tag == 'KEY_LP3_BIND':
                            key_id = 'E_KER_KEY_'+key_lp3_bind.attrib['ID'].upper()
                            camel_key_id = dqns_gen_utility.DqnsGenCamelStr(key_lp3_bind.attrib['ID'])
                            key_lp3_handle = 'AppState'+camel_state_id+'Key'+camel_key_id+'Lp3Handle'
                            key_lp3_handle_map.append((key_id,key_lp3_handle))
                    #把key lp3 handle相关的声明、定义，以及key id和key lp3 handle的映射关系写入 app_state_xxx.c   
                    #if len(key_lp3_handle_map) > 0:
                    genKeyLp3Handle(state_id,key_lp3_handle_map)
                        
                
                
                #寻找 key_release_tbl
                for item1 in item:
                    if item1.tag == 'key_release_tbl':
                        key_release_handle_config = item1
                        break
                if key_release_handle_config != None:
                    for key_release_bind in key_release_handle_config:
                        if key_release_bind.tag == 'KEY_RELEASE_BIND':
                            key_id = 'E_KER_KEY_'+key_release_bind.attrib['ID'].upper()
                            camel_key_id = dqns_gen_utility.DqnsGenCamelStr(key_release_bind.attrib['ID'])
                            key_release_handle = 'AppState'+camel_state_id+'Key'+camel_key_id+'ReleaseHandle'
                            key_release_handle_map.append((key_id,key_release_handle))
                    #把key release handle相关的声明、定义，以及key id和key release handle的映射关系写入 app_state_xxx.c   
                    #if len(key_release_handle_map) > 0:
                    genKeyReleaseHandle(state_id,key_release_handle_map)
                        
                        
                    
                #寻找 key_combine_tbl
                for item1 in item:
                    if item1.tag == 'key_combine_tbl':
                        key_combine_handle_config = item1
                        break
                if key_combine_handle_config != None:
                    for key_combine_bind in key_combine_handle_config:
                        if key_combine_bind.tag == 'KEY_COMBINE_BIND':
                            key_id = 'E_KER_KEY_COMBINE_'+key_combine_bind.attrib['ID'].upper()
                            camel_key_id = dqns_gen_utility.DqnsGenCamelStr(key_combine_bind.attrib['ID'])
                            key_combine_handle = 'AppState'+camel_state_id+'KeyCombine'+camel_key_id+'Handle'
                            key_combine_handle_map.append((key_id,key_combine_handle))
                    #把key combine handle相关的声明、定义，以及combine key id和combine key handle的映射关系写入 app_state_xxx.c   
                    #if len(key_combine_handle_map) > 0:
                    genKeyCombineHandle(state_id,key_combine_handle_map)
                        
                        
                #寻找 user_msg_tbl
                for item1 in item:
                    if item1.tag == 'user_msg_tbl':
                        user_msg_handle_config = item1
                        break
                if user_msg_handle_config != None:
                    for user_msg_bind in user_msg_handle_config:
                        if user_msg_bind.tag == 'USER_MSG_BIND':
                            user_msg_id = 'E_KER_MSG_'+user_msg_bind.attrib['ID'].upper()
                            camel_msg_id = dqns_gen_utility.DqnsGenCamelStr(user_msg_bind.attrib['ID'])
                            user_msg_handle = 'AppState'+camel_state_id+camel_msg_id+'MsgHandle'
                            user_msg_handle_map.append((user_msg_id,user_msg_handle))
                    #把user msg handle相关的声明、定义，以及user msg id和user msg handle的映射关系写入 app_state_xxx.c   
                    #if len(user_msg_handle_map) > 0:
                    genUserMsgHandle(state_id,user_msg_handle_map) 
                        
            
                    
def FSMGen(fsm_config):

    #state id 写入ker_fsm_user.h，-------------------------------------------------------------  begin
    fsm_user_h = r'..\..\kernel\platform\volatile\ker_fsm_user.h'      
    user_state_id_prefix_str = '    E_KER_STATE_ID_'
    user_state_id_begin = '<dqns_gen_state_id_begin>'
    user_state_id_end = '<dqns_gen_state_id_end>'
    
    #在文件"ker_fsm_user.h"的<dqns_gen_state_id_begin>,<dqns_gen_state_id_end>段落插入内容
    #把文件"ker_fsm_user.h"按行读入list
    fsm_user_h_list = dqns_gen_utility.DqnsGenGetFileList(fsm_user_h)
    #xml中找到state id，稍作处理加入list并返回
    #xml_list = dqns_gen_utility.DqnsGenGetListFromXML(timer_config,user_timer_id_tag,user_timer_id_prefix_str)
    xml_list = getStateIDFromXML(fsm_config,user_state_id_prefix_str,',')
    #把xml list中的内容覆盖掉 begin和end之间的内容，并返回list
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(user_state_id_begin,user_state_id_end,fsm_user_h_list,xml_list)
    #将上面得到的list，write_to_file_list，写入文件"ker_fsm_user.h"
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,fsm_user_h)    
    #state id 写入ker_fsm_user.h，-------------------------------------------------------------  end
    
    #state 定义， 写入ker_fsm_user.c，-------------------------------------------------------------  begin
    fsm_user_c = r'..\..\kernel\platform\volatile\ker_fsm_user.c'
    user_state_definition_begin = '<dqns_gen_state_definition_begin>'
    user_state_definition_end = '<dqns_gen_state_definition_end>'
    user_state_definition_prefix_str = 'TS_KER_STATE gg_app_state_'
    #把文件"ker_fsm_user.c"按行读入list
    fsm_user_c_list = dqns_gen_utility.DqnsGenGetFileList(fsm_user_c)
    xml_list = getStateIDFromXML(fsm_config,user_state_definition_prefix_str,';',False)
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(user_state_definition_begin,user_state_definition_end,fsm_user_c_list,xml_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,fsm_user_c) 
    #state 定义， 写入ker_fsm_user.c，-------------------------------------------------------------  end
    
    #state object table， 写入ker_fsm_user.c，-------------------------------------------------------------  begin
    fsm_user_c = r'..\..\kernel\platform\volatile\ker_fsm_user.c'
    user_state_obj_tbl_begin = '<dqns_gen_state_tbl_begin>'
    user_state_obj_tbl_end = '<dqns_gen_state_tbl_end>'
    user_state_obj_tbl_prefix_str = '    &gg_app_state_'
    #把文件"ker_fsm_user.c"按行读入list
    fsm_user_c_list = dqns_gen_utility.DqnsGenGetFileList(fsm_user_c)
    xml_list = getStateIDFromXML(fsm_config,user_state_obj_tbl_prefix_str,',',False)
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(user_state_obj_tbl_begin,user_state_obj_tbl_end,fsm_user_c_list,xml_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,fsm_user_c) 
    #state object table， 写入ker_fsm_user.c，-------------------------------------------------------------  end
    
    #生成app_state_xxx.h, app_state_xxx.c
    genAppStateFiles(fsm_config)
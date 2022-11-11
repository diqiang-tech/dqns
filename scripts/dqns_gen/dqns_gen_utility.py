   
def DqnsGenGetFileList(file_path_name):
    file_list = []
    file = None
    
    try:           
        file = open(file_path_name,mode='r',encoding='utf-8')        
        for line in file:
            file_list.append(line)             
    except IOError as my_errors:        
        pass
    finally:
        file.close()
        
    return file_list

def DqnsFnMask(fn_list,fn_name):
    begin_idx = -1
    end_idx = -1
    idx = 0
    brace_list = []
    for line in fn_list:
        if (line[0] != '/') and (fn_name in line) and ('{' in line):
            begin_idx = idx
            brace_list.append('{')
        elif ('{' in line) and (begin_idx != -1):
            brace_list.append('{')
        elif ('}' in line) and (begin_idx != -1):
            brace_list.pop()
            
def DqnsGenGetListFromFile(begin_str,end_str,file_path_name):
    ret_list = []
    file_list = DqnsGenGetFileList(file_path_name)
    
    begin_idx = 0
    end_idx = 0    
    idx = 0
    
    #寻找原始列表的起始和结束位置
    for item in file_list:
        if begin_str in item:
            begin_idx = idx
        elif end_str in item:
            end_idx = idx
            
        idx += 1
        
    if end_idx > begin_idx:
        cnt = end_idx - begin_idx
        if cnt > 1:
            for i in range(cnt-1):
                ret_list.append(file_list[begin_idx+1+i])
                
    return ret_list
def DqnsGenIsTextInList(original_list, line_text):  
    for item in original_list:
        if line_text in item:            
            return True
    
    return False
    
def DqnsGenInsertList2List(begin_str,end_str,original_list,insert_list):
    
    begin_idx = 0
    end_idx = 0    
    idx = 0
    
    #寻找原始列表的起始和结束位置
    for item in original_list:
        if begin_str in item:
            begin_idx = idx
        elif end_str in item:
            end_idx = idx
            
        idx += 1
        
    if end_idx > begin_idx:
        cnt = end_idx - begin_idx
        if cnt > 1:
            for i in range(cnt-1):
                original_list.pop(begin_idx+1)
        idx = 0
        for item in insert_list:            
            original_list.insert(begin_idx+1+idx,item)
            idx += 1
            
    return original_list

def DqnsGenListToFile(my_list,file_path_name):
    file = None
    try:
        file = open(file_path_name,mode='w',encoding='utf-8')
        for line in my_list:
            file.write(line)
    except:
        pass
    finally:
        file.close()

def DqnsGenInsertListToFile(file_path_name,begin_str,end_str,insert_list):
    file_list = DqnsGenGetFileList(file_path_name)
    origin_list = DqnsGenInsertList2List(begin_str,end_str,file_list,insert_list)
    DqnsGenListToFile(origin_list,file_path_name)
        
def DqnsGenGetRawListFromXML(config,tag,attrib_str):
    xml_list = []
    
    for item in config:
        if item.tag == tag:
            xml_list.append((item.attrib[attrib_str],item.text))
    
    return xml_list

def DqnsGenGetListFromXML(config,tag,prefix_str,need_to_upper=True,end_symbol=',',need_annotation=True,attrib_str='ID'):
    ret_list = []
    xml_list = []
    
    '''
    for item in config:
        if item.tag == tag:
            xml_list.append((item.attrib[attrib_str],item.text))   
    '''
    xml_list = DqnsGenGetRawListFromXML(config,tag,attrib_str)
            
    for item in xml_list:
            if need_to_upper:
                if need_annotation:
                    insert_str = prefix_str+item[0].upper()+end_symbol+'    //'+item[1]+'\n'
                else:
                    insert_str = prefix_str+item[0].upper()+end_symbol+'\n'
            else:
                if need_annotation:
                    insert_str = prefix_str+item[0]+end_symbol+'    //'+item[1]+'\n'
                else:
                    insert_str = prefix_str+item[0]+end_symbol+'\n'
            ret_list.append(insert_str)
    return ret_list

def DqnsGenFirstToUpper(original_str):    
    
    ret_str = original_str[0].upper()+original_str[1:]
    
    return ret_str    
def DqnsGenCamelStr(original_str,split_chr='_'):
    split_str_list = original_str.split('_')
    camel_str = ''
    for item in split_str_list:
        camel_str += (item[0].upper()+item[1:])
    return camel_str
    
def DqnsGenDeviceToPathName(device_str,is_h_file=True):
    path_name = r'..\..\udm\volatile\udm_'
    path_name += device_str
    if is_h_file:
        path_name += r'.h'
    else:
        path_name += r'.c'
        
    return path_name
    
def DqnsGenUdmDeviceFileIni(device_name,path_name,is_h_file=True):
    device_file_list = []
    #device_name_first_upper = DqnsGenFirstToUpper(device_name)
    device_name_camel = DqnsGenCamelStr(device_name,'_')
    #初始化udm设备头文件
    if is_h_file == True:
        device_file_list.append('#ifndef UDM_'+device_name.upper()+'_H\n')
        device_file_list.append('#define UDM_'+device_name.upper()+'_H\n')
        device_file_list.append('\n')
        device_file_list.append('#ifdef __cplusplus\n')
        device_file_list.append('extern "C"{\n')
        device_file_list.append('#endif\n')
        device_file_list.append('\n')
        device_file_list.append('#include "udm_types.h"\n')
        device_file_list.append('#include "udm_device_tbl.h"\n')
        device_file_list.append('\n')
        device_file_list.append('typedef T_U32 T_UDM_'+device_name.upper()+'_IOCTL;\n')
        device_file_list.append('\n')
        device_file_list.append('static void Udm'+device_name_camel+'Init(void);\n')
        device_file_list.append('static TE_UDM_RET_CODE Udm'+device_name_camel+'Open(T_UDM_OPEN_MODE open_mode);\n')
        device_file_list.append('static TE_UDM_RET_CODE Udm'+device_name_camel+'Close(void);\n')
        device_file_list.append('static TE_UDM_RET_CODE Udm'+device_name_camel+'Read(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);\n')
        device_file_list.append('static TE_UDM_RET_CODE Udm'+device_name_camel+'Write(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);\n')
        device_file_list.append('static TE_UDM_RET_CODE Udm'+device_name_camel+'IOCtl(void * p_data);\n')
        device_file_list.append('\n')
        device_file_list.append('#ifdef __cplusplus\n')
        device_file_list.append('}\n')
        device_file_list.append('#endif\n')
        device_file_list.append('\n')
        device_file_list.append('#endif\n')        
        
    #初始化udm设备源文件
    elif is_h_file == False:
        device_file_list.append('#include "udm_'+device_name+'.h"\n')
        device_file_list.append('\n')
        device_file_list.append('TS_UDM_DEVICE gg_udm_'+device_name+';\n')
        device_file_list.append('static T_UDM_'+device_name.upper()+'_IOCTL udm_'+device_name+'_ioctl_data;\n')
        device_file_list.append('\n')
        device_file_list.append('static void Udm'+device_name_camel+'Init(void){\n')
        device_file_list.append('    gg_udm_'+device_name+'.e_device_id = E_UDM_DEVICE_'+device_name.upper()+';\n')
        device_file_list.append('    gg_udm_'+device_name+'.e_already_open = E_FALSE;\n')
        device_file_list.append('    gg_udm_'+device_name+'.p_ioctl_data = &udm_'+device_name+'_ioctl_data;\n')
        #device_file_list.append('    gg_udm_'+device_name+'.p_fn_init = Udm'+device_name_camel+'Init;\n')
        device_file_list.append('    gg_udm_'+device_name+'.p_fn_open = Udm'+device_name_camel+'Open;\n')
        device_file_list.append('    gg_udm_'+device_name+'.p_fn_close = Udm'+device_name_camel+'Close;\n')
        device_file_list.append('    gg_udm_'+device_name+'.p_fn_read = Udm'+device_name_camel+'Read;\n')
        device_file_list.append('    gg_udm_'+device_name+'.p_fn_write = Udm'+device_name_camel+'Write;\n')
        device_file_list.append('    gg_udm_'+device_name+'.p_fn_ioctl = Udm'+device_name_camel+'IOCtl;\n')
        device_file_list.append('}\n')
        device_file_list.append('\n')
        device_file_list.append('static TE_UDM_RET_CODE Udm'+device_name_camel+'Open(T_UDM_OPEN_MODE open_mode){\n')
        device_file_list.append('    return E_UDM_OK;\n')
        device_file_list.append('}\n')
        device_file_list.append('\n')
        device_file_list.append('static TE_UDM_RET_CODE Udm'+device_name_camel+'Close(void){\n')
        device_file_list.append('    return E_UDM_OK;\n')
        device_file_list.append('}\n')
        device_file_list.append('\n')
        device_file_list.append('static TE_UDM_RET_CODE Udm'+device_name_camel+'Read(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){\n')
        device_file_list.append('    return E_UDM_OK;\n')
        device_file_list.append('}\n')
        device_file_list.append('\n')
        device_file_list.append('static TE_UDM_RET_CODE Udm'+device_name_camel+'Write(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){\n')
        device_file_list.append('    return E_UDM_OK;\n')
        device_file_list.append('}\n')
        device_file_list.append('\n')
        device_file_list.append('static TE_UDM_RET_CODE Udm'+device_name_camel+'IOCtl(void * p_data){\n')
        device_file_list.append('    return E_UDM_OK;\n')
        device_file_list.append('}\n')
        device_file_list.append('\n')
        
    DqnsGenListToFile(device_file_list,path_name)
        
        

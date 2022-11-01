import os
import dqns_gen_utility

def UdmGen(udm_config):

    udm_device_tbl_h = r'..\..\udm\volatile\udm_device_tbl.h'  
    udm_device_tbl_c = r'..\..\udm\volatile\udm_device_tbl.c'    
    
    device_id_tag = 'DEVICE'
    
    device_id_prefix_str = '    E_UDM_DEVICE_'    
    device_id_begin = '<dqns_gen_device_id_begin>'
    device_id_end = '<dqns_gen_device_id_end>'    
    #在文件"udm_device_tbl.h"的<dqns_gen_device_id_begin>,<dqns_gen_device_id_end>段落插入内容
    #把文件"udm_device_tbl.h"按行读入list
    device_tbl_h_list = dqns_gen_utility.DqnsGenGetFileList(udm_device_tbl_h)
    #xml中找到device id段，稍作处理加入list并返回
    xml_list = dqns_gen_utility.DqnsGenGetListFromXML(udm_config,device_id_tag,device_id_prefix_str)
    #把xml list中的内容覆盖掉 begin和end之间的内容，并返回list
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(device_id_begin,device_id_end,device_tbl_h_list,xml_list)
    #将上面得到的list，write_to_file_list，写入文件"udm_device_tbl.h"
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,udm_device_tbl_h)
    
    #添加udm头文件
    device_h_begin = '<dqns_gen_device_h_begin>'
    device_h_end = '<dqns_gen_device_h_end>'    
    device_h_prefix_str = '#include "udm_'
    device_h_list = dqns_gen_utility.DqnsGenGetListFromXML(udm_config,device_id_tag,device_h_prefix_str,False,'.h"',False)
    dqns_gen_utility.DqnsGenInsertListToFile(udm_device_tbl_h,device_h_begin,device_h_end,device_h_list)
    
    device_extern_prefix_str = 'extern TS_UDM_DEVICE gg_udm_'
    device_extern_begin_str = '<dqns_gen_device_extern_begin>'
    device_extern_end_str = '<dqns_gen_device_extern_end>'
    #在"udm_device_tbl.c"的<dqns_gen_device_extern_begin>，<dqns_gen_device_extern_end>段落插入内容
    #把文件"udm_device_tbl.c"按行读入list
    device_tbl_c_list = dqns_gen_utility.DqnsGenGetFileList(udm_device_tbl_c)
    #xml中找到device id段，稍作处理加入list并返回
    xml_list = dqns_gen_utility.DqnsGenGetListFromXML(udm_config,device_id_tag,device_extern_prefix_str,False,';')
    #把xml list中的内容覆盖掉 begin和end之间的内容，并返回list
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(device_extern_begin_str,device_extern_end_str,device_tbl_c_list,xml_list)
    #将上面得到的list，write_to_file_list，写入文件"udm_device_tbl.c"
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,udm_device_tbl_c)
    
    device_tbl_prefix_str = '    &gg_udm_'
    device_tbl_begin_str = '<dqns_gen_device_tbl_begin>'
    device_tbl_end_str = '<dqns_gen_device_tbl_end>'
    #在"udm_device_tbl.c"的<dqns_gen_device_tbl_begin>，<dqns_gen_device_tbl_end>段落插入内容
    #把文件"udm_device_tbl.c"按行读入list
    device_tbl_c_list = dqns_gen_utility.DqnsGenGetFileList(udm_device_tbl_c)
    #xml中找到device id段，稍作处理加入list并返回
    xml_list = dqns_gen_utility.DqnsGenGetListFromXML(udm_config,device_id_tag,device_tbl_prefix_str,False)
    #把xml list中的内容覆盖掉 begin和end之间的内容，并返回list
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(device_tbl_begin_str,device_tbl_end_str,device_tbl_c_list,xml_list)
    #将上面得到的list，write_to_file_list，写入文件"udm_device_tbl.c"
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,udm_device_tbl_c) 
    
    
    #initialize udm device files in volatile folder
    udm_device_file_prefix = r'..\..\udm\volatile\udm_'  
    #get device list    
    device_list = dqns_gen_utility.DqnsGenGetRawListFromXML(udm_config,'DEVICE','ID')    
    for device in device_list:
        device_h_file_path_name = udm_device_file_prefix + device[0] + '.h'
        device_c_file_path_name = udm_device_file_prefix + device[0] + '.c'
        if os.path.exists(device_h_file_path_name) == False:
            dqns_gen_utility.DqnsGenUdmDeviceFileIni(device[0],device_h_file_path_name,is_h_file=True)
        if os.path.exists(device_c_file_path_name) == False:
            dqns_gen_utility.DqnsGenUdmDeviceFileIni(device[0],device_c_file_path_name,is_h_file=False)
            
    

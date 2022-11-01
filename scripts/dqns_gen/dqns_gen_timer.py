import dqns_gen_utility

def TimerGen(timer_config):

    timer_user_h = r'..\..\kernel\platform\volatile\ker_timer_user.h'     
    
    user_timer_id_tag = 'USER_TIMER'
    user_timer_id_prefix_str = '    E_KER_TIMER_'
    user_timer_id_begin = '<dqns_gen_user_timer_id_begin>'
    user_timer_id_end = '<dqns_gen_user_timer_id_end>'
    
    #在文件"ker_timer_user.h"的<dqns_gen_user_timer_id_begin>,<dqns_gen_user_timer_id_end>段落插入内容
    #把文件"ker_timer_user.h"按行读入list
    timer_user_h_list = dqns_gen_utility.DqnsGenGetFileList(timer_user_h)
    #xml中找到user timer id段，稍作处理加入list并返回
    xml_list = dqns_gen_utility.DqnsGenGetListFromXML(timer_config,user_timer_id_tag,user_timer_id_prefix_str)
    #把xml list中的内容覆盖掉 begin和end之间的内容，并返回list
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(user_timer_id_begin,user_timer_id_end,timer_user_h_list,xml_list)
    #将上面得到的list，write_to_file_list，写入文件"udm_device_tbl.h"
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,timer_user_h)    
    

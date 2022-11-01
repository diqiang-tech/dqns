
import dqns_gen_utility

def MsgGen(msg_config):
       
    msg_user_h = r'..\..\kernel\platform\volatile\ker_msg_user.h'      
    
    ring_queue_prefix_str = '#define KER_MSG_RING_QUEUE_SIZE '
    ring_queue_tag = 'RING_QUEUE_SIZE'
    ring_queue_begin_str = '<dqns_gen_ring_queue_size_begin>'
    ring_queue_end_str = '<dqns_gen_ring_queue_size_end>'    
    #在文件"ker_msg_user.h"的<dqns_gen_ring_queue_size_begin>,<dqns_gen_ring_queue_size_end>段落插入内容
    #把文件"ker_msg_user.h"按行读入list
    msg_user_h_list = dqns_gen_utility.DqnsGenGetFileList(msg_user_h)
    #xml中找到ring queue size 段，稍作处理加入list并返回
    xml_list = dqns_gen_utility.DqnsGenGetListFromXML(msg_config,ring_queue_tag,ring_queue_prefix_str,need_to_upper=False,end_symbol='',need_annotation=False,attrib_str='SIZE')
    #把xml list中的内容覆盖掉 begin和end之间的内容，并返回list
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(ring_queue_begin_str,ring_queue_end_str,msg_user_h_list,xml_list)
    #将上面得到的list，write_to_file_list，写入文件"ker_msg_user.h"
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,msg_user_h)
    
    
    user_msg_id_prefix_str = '    E_KER_MSG_'
    user_msg_id_tag = 'USER_MSG'
    user_msg_id_begin_str = '<dqns_gen_user_msg_id_begin>'
    user_msg_id_end_str = '<dqns_gen_user_msg_id_end>'
    #在文件"ker_msg_user.h"的<dqns_gen_user_msg_id_begin>,<dqns_gen_user_msg_id_end>段落插入内容
    #把文件"ker_msg_user.h"按行读入list
    msg_user_h_list = dqns_gen_utility.DqnsGenGetFileList(msg_user_h)
    #xml中找到user msg id 段，稍作处理加入list并返回
    xml_list = dqns_gen_utility.DqnsGenGetListFromXML(msg_config,user_msg_id_tag,user_msg_id_prefix_str,need_to_upper=True,end_symbol=',',need_annotation=True)
    #把xml list中的内容覆盖掉 begin和end之间的内容，并返回list
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(user_msg_id_begin_str,user_msg_id_end_str,msg_user_h_list,xml_list)
    #将上面得到的list，write_to_file_list，写入文件"ker_msg_user.h"
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,msg_user_h)
    
    

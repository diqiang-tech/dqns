# dqns_gen_key.py
import os
import dqns_gen_utility

def keyUserInit(init_list,key,combine_with='',need_care_lp_stuck_flag=('0','0','0','0')):
    init_list.append('    /* '+key+ ' key initialization */ \n')
    init_list.append('    gg_key_'+key+'.press_counter = 0;\n')
    init_list.append('    gg_key_'+key+'.release_counter = 0;\n')
    init_list.append('    gg_key_'+key+'.filter_counts = KER_FILTER_COUNT_MAX;\n')
    init_list.append('    gg_key_'+key+'.key_bit = UDM_KEY_BITx_'+key.upper()+';\n') 
    if combine_with == '':
        init_list.append('    gg_key_'+key+'.key_combine_bits = UDM_KEY_BITx_'+key.upper()+';\n')  
    else:
        init_list.append('    gg_key_'+key+'.key_combine_bits = UDM_KEY_BITx_'+key.upper()+'|UDM_KEY_BITx_'+combine_with.upper()+';\n')    
    
    init_list.append('    gg_key_'+key+'.key_flag.key_flags = 0;\n')
    init_list.append('    gg_key_'+key+'.key_flag.key_flags_struct.need_care_long_press1_flag = '+need_care_lp_stuck_flag[0]+';\n')
    init_list.append('    gg_key_'+key+'.key_flag.key_flags_struct.need_care_long_press2_flag = '+need_care_lp_stuck_flag[1]+';\n')
    init_list.append('    gg_key_'+key+'.key_flag.key_flags_struct.need_care_long_press3_flag = '+need_care_lp_stuck_flag[2]+';\n')
    init_list.append('    gg_key_'+key+'.key_flag.key_flags_struct.need_care_stuck_flag = '+need_care_lp_stuck_flag[3]+';\n')
    init_list.append('\n')
    
def keybitsNA(key_bits_type,key_counts):
    if key_bits_type == 'T_U8':
        if key_counts < 8:
            return (str(8-key_counts))
    elif key_bits_type == 'T_U16':
        if key_counts < 16:
            return (str(16-key_counts))
    elif key_bits_type == 'T_U32':
        if key_counts < 32:
            return (str(32-key_counts))
            
    return '0'
            
def genUnionKeyBitsList(key_config,key_bits_type_str):    
    
    #get raw key id list from xml
    raw_key_id_list = []
    raw_key_id_list = dqns_gen_utility.DqnsGenGetRawListFromXML(key_config[1],'USER_KEY','ID')
    
    key_bits_union_list = []
    for key in raw_key_id_list:
        key_bits_union_str = '        T_KER_KEY_BITS '+key[0]+':1;'+'\t'+r'//'+key[1]+'\n'
        key_bits_union_list.append(key_bits_union_str)
    
    na_str = keybitsNA(key_bits_type_str,len(raw_key_id_list))
    if na_str != '0':
        key_bits_union_str = '        T_KER_KEY_BITS na:'+na_str+';\n'
        key_bits_union_list.append(key_bits_union_str)
    
    return key_bits_union_list
    
    

def KeyGen(key_config): 
       
    key_user_h = r'..\..\kernel\platform\volatile\ker_key_user.h' 
    key_user_c = r'..\..\kernel\platform\volatile\ker_key_user.c'
          
    #??????"ker_key_user.c"????????????
    key_user_c_file_list = []    
    
    udm_key_h = r'..\..\udm\volatile\udm_key.h'
    #??????udm ??????key?????????,key gen???????????????udm key
    if os.path.exists(udm_key_h) == False:
        print("need generate key device drive of udm first")
        return         
        
    #get raw key id list from xml
    raw_key_id_list = []
    raw_key_id_list = dqns_gen_utility.DqnsGenGetRawListFromXML(key_config[1],'USER_KEY','ID')
    
    #??????key bits type ????????????key?????????
    key_count = len(raw_key_id_list)
    key_types_list = dqns_gen_utility.DqnsGenGetRawListFromXML(key_config[0],'KEY_BITS_TYPE','type')
    key_bits_type_str = key_types_list[0][0]
    if key_bits_type_str == 'T_U8':
        if key_count > 8:
            print('Key bits type is not reasonable,please check it!\n')
            return 
    elif key_bits_type_str == 'T_U16':
        if key_count > 16:
            print('Key bits type is not reasonable,please check it!\n')
            return 
    elif key_bits_type_str == 'T_U32':
        if key_count > 32:
            print('Key bits type is not reasonable,please check it!\n')
            return 
            
        
    #this list will insert to section <dqns_gen_udm_key_bits_begin> <dqns_gen_udm_key_bits_end> in file "udm_key.h"
    #????????????udm_key.h"???<dqns_gen_udm_key_bits_begin>???<dqns_gen_udm_key_bits_end>?????????key bit?????????
    #key bits ??????????????????udm_key.h"--------------------------begin
    key_bits_list = []
    prefix_str = '#define UDM_KEY_BITx_'
    bit_value = 1
    for key in raw_key_id_list:
        key_bitx_define_str = prefix_str+key[0].upper()+'\t'+str(bit_value)+'\n'
        key_bits_list.append(key_bitx_define_str)
        bit_value *= 2
    
    udm_key_begin_str = '<dqns_gen_udm_key_bits_begin>'
    udm_key_end_str = '<dqns_gen_udm_key_bits_end>'
    udm_key_file_list = dqns_gen_utility.DqnsGenGetFileList(udm_key_h)
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(udm_key_begin_str,udm_key_end_str,udm_key_file_list,key_bits_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,udm_key_h)
    #key bits ??????????????????udm_key.h"--------------------------end   
    
    
    #key bits type ??????"ker_key_user.h"----------------------begin
    key_bits_type_list = []
    key_bits_type_define = 'typedef '+key_bits_type_str+' T_KER_KEY_BITS;\n'
    key_bits_type_list.append(key_bits_type_define)
    
    key_bits_type_begin_str = '<dqns_gen_key_bits_type_begin>'
    key_bits_type_end_str = '<dqns_gen_key_bits_type_end>'
    
    #??????"ker_key_user.h"????????????
    key_user_h_file_list = dqns_gen_utility.DqnsGenGetFileList(key_user_h)
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(key_bits_type_begin_str,key_bits_type_end_str,key_user_h_file_list,key_bits_type_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,key_user_h)
    #key bits type ??????"ker_key_user.h"----------------------end
    
    
    
    #key id???????????? ???ker_key_user.h",<dqns_gen_key_id_begin>???<dqns_gen_key_id_end>??????"----------------------begin
    key_id_list = dqns_gen_utility.DqnsGenGetListFromXML(key_config[1],'USER_KEY','    E_KER_KEY_')
    key_user_h_file_list = dqns_gen_utility.DqnsGenGetFileList(key_user_h)
    
    key_id_begin_str = '<dqns_gen_key_id_begin>'
    key_id_end_str = '<dqns_gen_key_id_end>'
    
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(key_id_begin_str,key_id_end_str,key_user_h_file_list,key_id_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,key_user_h)
    #key id???????????? ???ker_key_user.h",<dqns_gen_key_id_begin>???<dqns_gen_key_id_end>??????"----------------------end
    
    
    #key bits ???????????? key_bits_struc,<dqns_gen_union_key_bits_begin>???<dqns_gen_union_key_bits_end>??????-----------begin
    union_key_bits_begin = '<dqns_gen_union_key_bits_begin>'
    union_key_bits_end = '<dqns_gen_union_key_bits_end>'
    key_user_h_file_list = dqns_gen_utility.DqnsGenGetFileList(key_user_h)
    key_bits_union_list = genUnionKeyBitsList(key_config,key_bits_type_str)
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(union_key_bits_begin,union_key_bits_end,key_user_h_file_list,key_bits_union_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,key_user_h)
    #key bits ???????????? key_bits_struc,<dqns_gen_union_key_bits_begin>???<dqns_gen_union_key_bits_end>??????-----------end
    
    #combine key id???????????????"ker_dqns_key_user.h",<dqns_gen_combine_key_id_begin>???<dqns_gen_combine_key_id_end>??????------begin    
    combine_key_id_begin_str = '<dqns_gen_combine_key_id_begin>'
    combine_key_id_end_str = '<dqns_gen_combine_key_id_end>'
    combine_key_id_list = dqns_gen_utility.DqnsGenGetListFromXML(key_config[3],'COMBINE_KEY','    E_KER_KEY_COMBINE_')
    key_user_h_file_list = dqns_gen_utility.DqnsGenGetFileList(key_user_h)
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(combine_key_id_begin_str,combine_key_id_end_str,key_user_h_file_list,combine_key_id_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,key_user_h)
    #combine key id???????????????"ker_key_user.h",<dqns_gen_combine_key_id_begin>???<dqns_gen_combine_key_id_end>??????------end
    
    #key obj ???????????????"ker_key_user.c"???<dqns_gen_key_obj_begin>???<dqns_gen_key_obj_end>??????-------------begin
    key_obj_define_prefix_str = 'TS_KER_KEY gg_key_'
    key_obj_begin_str = '<dqns_gen_key_obj_begin>'
    key_obj_end_str = '<dqns_gen_key_obj_end>'
    key_obj_define_list = dqns_gen_utility.DqnsGenGetListFromXML(key_config[1],'USER_KEY',key_obj_define_prefix_str,False,';')
    key_user_c_file_list = dqns_gen_utility.DqnsGenGetFileList(key_user_c)
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(key_obj_begin_str,key_obj_end_str,key_user_c_file_list,key_obj_define_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,key_user_c)
    #key obj ???????????????"ker_key_user.c"???<dqns_gen_key_obj_begin>???<dqns_gen_key_obj_end>??????-------------end
    
    #key obj tbl???????????????"ker_key_user.c"???<dqns_gen_key_obj_tbl_begin>???<dqns_gen_key_obj_tbl_end>??????-------------begin
    key_obj_tbl_define_prefix_str = '    &gg_key_'
    key_obj_tbl_begin_str = '<dqns_gen_key_obj_tbl_begin>'
    key_obj_tbl_end_str = '<dqns_gen_key_obj_tbl_end>'
    key_obj_tbl_define_list = dqns_gen_utility.DqnsGenGetListFromXML(key_config[1],'USER_KEY',key_obj_tbl_define_prefix_str,False)
    key_user_c_file_list = dqns_gen_utility.DqnsGenGetFileList(key_user_c)
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(key_obj_tbl_begin_str,key_obj_tbl_end_str,key_user_c_file_list,key_obj_tbl_define_list)
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,key_user_c)
    #key obj tbl???????????????"ker_key_user.c"???<dqns_gen_key_obj_tbl_begin>???<dqns_gen_key_obj_tbl_end>??????-------------end
    
    #combine key bits map ???????????????"ker_key_user.c",<dqns_gen_combine_key_bits_map_begin>???<dqns_gen_combine_key_bits_map_end>??????--------begin
    combine_key_bits_begin_str = 'dqns_gen_combine_key_bits_map_begin'
    combine_key_bits_end_str = 'dqns_gen_combine_key_bits_map_end'
    combine_key_bits_raw_list = dqns_gen_utility.DqnsGenGetRawListFromXML(key_config[3],'COMBINE_KEY','ID')
    combine_key_bits_list = []
    for item in combine_key_bits_raw_list:
        line = '    {E_KER_KEY_COMBINE_'+item[0].upper()+','
        bit_list = item[1].split('+')
        bit_list_len = len(bit_list)
        i = 0
        for bit in bit_list:
            line += 'UDM_KEY_BITx_'
            line += bit.upper()
            if i < (bit_list_len - 1):
                line += '+'
            elif i == (bit_list_len - 1):
                line += '},\n'
            
            i += 1
        combine_key_bits_list.append(line)
    key_user_c_file_list = dqns_gen_utility.DqnsGenGetFileList(key_user_c)
    
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(combine_key_bits_begin_str,combine_key_bits_end_str,key_user_c_file_list,combine_key_bits_list)
    
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,key_user_c)
    #combine key bits map ???????????????"ker_key_user.c",<dqns_gen_combine_key_bits_map_begin>???<dqns_gen_combine_key_bits_map_end>??????--------end
    
    #key user init,---------------------------------------begin
    key_user_init_begin_str = '<dqns_gen_key_initialization_begin>'
    key_user_init_end_str = '<dqns_gen_key_initialization_end>'
    key_user_init_list = []
    for key_item in key_config[2]:
        key = key_item.tag
        combine_with = key_item[0].attrib['BITS']
        need_care_lp1 = key_item[1].attrib['VALUE']
        need_care_lp2 = key_item[2].attrib['VALUE']
        need_care_lp3 = key_item[3].attrib['VALUE']
        need_care_stuck = key_item[4].attrib['VALUE']
        
        need_care_flag = (need_care_lp1,need_care_lp2,need_care_lp3,need_care_stuck)
        keyUserInit(key_user_init_list,key,combine_with,need_care_flag)
    
    key_user_c_file_list = dqns_gen_utility.DqnsGenGetFileList(key_user_c)  
    
    write_to_file_list = dqns_gen_utility.DqnsGenInsertList2List(key_user_init_begin_str,key_user_init_end_str,key_user_c_file_list,key_user_init_list)
    
    dqns_gen_utility.DqnsGenListToFile(write_to_file_list,key_user_c)
    #key user init,---------------------------------------end
    
    
    
    
    
    
    
    
    
    
    
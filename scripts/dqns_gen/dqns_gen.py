import xml.etree.ElementTree as ET
import dqns_gen_msg
import dqns_gen_timer
import dqns_gen_udm
import dqns_gen_key
import dqns_gen_fsm
import dqns_gen_comm

tree = ET.parse('dqns_gen_config.xml')
root = tree.getroot()

print(root[0][0][0])

print("[M]--- message pump module's volatile data generation.")
print("[T]--- timer module's volatile data generation.")
print("[U]--- udm's volatile data generation.")
print("[K]--- kernel key module volatile data generation.")
print("[F]--- fsm module's volatile data generation.")
print("[C]--- communication module's volatile data generation.")
print("[A]--- all dqns modules' volatile data generation.")
print("[X]--- exit,do nothing!")

select_cmd = input("please select:")        
if select_cmd == 'M' or select_cmd == 'm':
    dqns_gen_msg.MsgGen(root[0][0])
elif select_cmd == 'T' or select_cmd == 't':
    dqns_gen_timer.TimerGen(root[0][1])
elif select_cmd == 'U' or select_cmd == 'u':
    dqns_gen_udm.UdmGen(root[1][0])
elif select_cmd == 'K' or select_cmd == 'k':
    dqns_gen_key.KeyGen(root[0][2])
elif select_cmd == 'F' or select_cmd == 'f':
    dqns_gen_fsm.FSMGen(root[0][4])
elif select_cmd == 'C' or select_cmd == 'c':
    dqns_gen_comm.CommGen(root[0][5])
elif select_cmd == 'A' or select_cmd == 'a':
    dqns_gen_msg.MsgGen(root[0][0])
    dqns_gen_timer.TimerGen(root[0][1])
    dqns_gen_udm.UdmGen(root[1][0])
    dqns_gen_key.KeyGen(root[0][2])
    dqns_gen_fsm.FSMGen(root[0][4])
    dqns_gen_comm.CommGen(root[0][5])
elif select_cmd == 'X' or select_cmd == 'x':
    print("Exit,do nothing!\n")
else:
    print("Exit,do nothing!\n")
    

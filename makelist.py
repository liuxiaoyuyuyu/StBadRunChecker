import numpy as np

f_injection = open("Dummy_BadRun_Run19_19p6_injection.list", "r")
content_injection = f_injection.read()
injection_list = content_injection.split("\n")
f_tpc = open("Dummy_BadRun_Run19_19p6_tpc.list", "r")
content_tpc = f_tpc.read()
tpc_list = content_tpc.split("\n")
bad_run=list(set(injection_list + tpc_list))

injection_array=np.array(injection_list)
tpc_array=np.array(tpc_list)
bad_run_array=np.array(bad_run)

bad_run_sub=np.zeros((len(bad_run_array),12))
bad_run_sub[:,0]=np.in1d(bad_run_array,injection_array)
bad_run_sub[:,1]=np.in1d(bad_run_array,tpc_array)
np.set_printoptions(threshold=np.inf)

bad_run_str=np.array2string(bad_run_array.astype(int))
tmp=bad_run_str.replace("\n ",",")
tmp2=tmp.replace(" ",",")
tmp3=tmp2.replace("[","{")
bad_run_cpp=tmp3.replace("]","}")

bad_run_sub_str=np.array2string(bad_run_sub.astype(int))
tmp=bad_run_sub_str.replace("\n ",",")
tmp2=tmp.replace(" ",",")
tmp3=tmp2.replace("[","{")
bad_run_sub_cpp=tmp3.replace("]","}")

with open("badrun_sub.txt", "w") as output:
    output.write(str("const Int_t nBadRun_run19_19p6 ="+str(len(bad_run_array))+";\n"))
    output.write(str("const Int_t badrun_run19_19p6_all[nBadRun_run19_19p6]="+bad_run_cpp+";\n"))
    output.write(str("const Int_t badrun_run19_19p6_sub[nBadRun_run19_19p6][12]="+bad_run_sub_cpp+";"))
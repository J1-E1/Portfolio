from model_generator import assemble_mesh_root, assemble_mesh_root_method_2
import time
from data_plot import method_points_compare, method_compare, bar_chart_root

# Data collect
data_root_id_1 = []
data_root_element_1 = []
data_root_total_1 = 0

data_root_id_2 = []
data_root_element_2 = []
data_root_total_2 = 0

data_root_id_3 = []
data_root_element_3 = []
data_root_total_3 = 0

data_filesize_collcetion = []

# Function with simplify
start_time = time.time()
data_root_id_1, data_root_element_1, data_root_total_1, size_1 = assemble_mesh_root()
endtime = time.time()
duration = endtime - start_time
"""
# Function with no simplify
start_time_2 = time.time()
data_root_id_2, data_root_element_2, data_root_total_2, size_2 = assemble_mesh_root_method_2()
endtime_2 = time.time()
duration_2 = endtime_2 - start_time_2

# Function with no simplify
start_time_3 = time.time()
data_root_id_3, data_root_element_3, data_root_total_3, size_3 = assemble_mesh_root(is_simplify=False)
endtime_3 = time.time()
duration_3 = endtime_3 - start_time_3
"""

print("\n------------------------------------------------------------------")
print("Time cost: {:.2f}s".format(duration))
# print("Time cost 2: {:.2f}s".format(duration_2))
# print("Time cost for no simply: {:.2f}s".format(duration_3))

print("\n------------------------------------------------------------------")
# method_points_compare(root_id=data_root_id_1, method_1_root=data_root_element_1, method_2_root=data_root_element_2,
# method_3_root=data_root_element_3) bar_chart_root(data_root_id=data_root_id_1, m1=data_root_element_1,
# m2=data_root_element_2, m3=data_root_element_3)

print("\n------------------------------------------------------------------")
time_formatt = "{:.2f}s"
formatt_1 = time_formatt.format(duration)
# formatt_2 = time_formatt.format(duration_2)
# formatt_3 = time_formatt.format(duration_3)

"""
method_name = ['method_1', 'method_2', 'method_3']
method_time = [duration, duration_2, duration_3]
method_time_format = [formatt_1, formatt_2, formatt_3]
method_points = [data_root_total_1, data_root_total_2, data_root_total_3]
data_filesize_collcetion = [size_1, size_2, size_3]
method_compare(method_name=method_name, method_time=method_time_format, method_points=method_points,
               file_size=data_filesize_collcetion)

"""

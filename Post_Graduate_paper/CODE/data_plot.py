"""
pyechart    ===     1.2.0
"""
import pandas as pd
import os
import matplotlib.pyplot as plt
from rsml import csv_data
import xml.etree.ElementTree as ET

from openpyxl import load_workbook

filename = "/Users/zhouxuhao/PycharmProjects/RMSL2obj/data/0414_roots/0414_roots.rsml"


def method_compare(method_name, method_time, method_points, file_size):
    dataset = {
        'Method': method_name,
        'Time_cost': method_time,
        'Points': method_points,
        'File_size': file_size
    }
    datavar = pd.DataFrame(dataset)
    path = os.getcwd() + '/xlsx/method_compare.xlsx'
    writer = pd.ExcelWriter(path, engine='openpyxl')
    datavar.to_excel(writer, sheet_name='table1')
    writer.save()
    writer.close()
    print(datavar)


def method_points_compare(root_id, method_1_root, method_2_root, method_3_root):
    dataset = {
        'root_id': root_id,
        'method_1': method_1_root,
        'method_2': method_2_root,
        'method_3': method_3_root,
    }

    datavar = pd.DataFrame(dataset)
    print(datavar)


def csv_data_pos(data_root_id, csv_root_pos):
    # for csv data
    list_x = []
    list_y = []
    list_z = []
    for point in csv_root_pos:
        list_x.append(point[0])
        list_y.append(point[1])
        list_z.append(point[2])

    csv_data_convert(root_id=data_root_id, pos_x=list_x, pos_y=list_y, pos_z=list_z)
    return csv_root_pos


def csv_data_convert(root_id, pos_x, pos_y, pos_z):
    """
    param root_id: each sector of the root

    param inf: the information of each root
    :return:
    """
    root_label, root_inf = csv_data()
    # convert int to str type
    list(map(str, pos_x))
    list(map(str, pos_y))
    list(map(str, pos_z))
    dataset = {
        'root_id': root_id,
        'root_label': root_label,
        'pos_x': pos_x,
        'pos_y': pos_y,
        'pos_z': pos_z,
        'information': root_inf,
    }

    df = pd.DataFrame(dataset)
    df.to_csv('./csv/rootInf.csv', na_rep='', index=False, encoding='utf-8', header=False)
    print(df)


# The part that handles the file size
def convert_bytes(num):
    """
    this function will convert bytes to MB.... GB... etc
    """
    for x in ['bytes', 'KB', 'MB', 'GB', 'TB']:
        if num < 1024.0:
            return "%3.1f %s" % (num, x)
        num /= 1024.0


def file_size(file_path):
    """
    this function will return the file size
    """
    if os.path.isfile(file_path):
        file_info = os.stat(file_path)
        return convert_bytes(file_info.st_size)


def bar_chart_root(data_root_id, m1, m2, m3):
    name_list = data_root_id
    list(map(int, m1))
    list(map(int, m2))
    list(map(int, m3))
    x = list(range(len(name_list)))
    total_width, n = 1, 3
    bin_width = total_width / n

    plt.bar(x, m1, width=bin_width, label='mtehod_1', fc='y')
    for i in range(len(x)):
        x[i] = x[i] + bin_width
    plt.bar(x, m2, width=bin_width, label='method_2', tick_label=name_list, fc='r')
    for i in range(len(x)):
        x[i] = x[i] + bin_width
    plt.bar(x, m3, width=bin_width, label='method_3', tick_label=name_list, fc='b')
    plt.xlabel('root_index', fontsize=9)
    plt.ylabel('points', fontsize=9)

    ax = plt.gca()

    plt.xticks(name_list, name_list)
    plt.legend()
    plt.show()

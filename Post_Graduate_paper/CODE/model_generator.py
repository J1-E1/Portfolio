"""
Runnable version pair
# torch  -   pytorch3d -version
# 1.7.0  -   0.4.0
# 1.9.1  -    0.6.1 / 0.6.2
"""
import os
from math import ceil

import numpy as np
import torch
from pytorch3d.io import IO
from pytorch3d.structures import join_meshes_as_scene
from pytorch3d.structures.meshes import Meshes
from scipy import spatial
from rsml import *

from model_cylinder import cylinder, cylinder_csg
from rsml import simplify_root_data
from data_plot import file_size, csv_data_pos

if torch.cuda.is_available():
    device = torch.device("cuda:0")
    torch.cuda.set_device(device)
else:
    device = torch.device("cpu")

with_grad = False


# The CSG function

def create_mesh_root_element_CSG(vertics):
    mesh_collection = []
    vertics_array = np.array(vertics)
    for index in range(len(vertics) - 1):
        if index == (len(vertics) - 1):
            break
        p0 = np.array(vertics[index])
        p1 = np.array(vertics[index + 1])

        mesh_item = cylinder_csg(point_0=p0, point_1=p1, radius=3)
        # add each cylinder in root
        mesh_collection.append(mesh_item)
    return mesh_collection


def create_mesh_root_element(vertics, mesh_collection):
    vertics_array = np.array(vertics)
    for index in range(len(vertics) - 1):
        if index == (len(vertics) - 1):
            break
        p0 = np.array(vertics[index])
        p1 = np.array(vertics[index + 1])
        host_verts = cylinder(point_0=p0, point_1=p1, radius=3)
        if not np.isnan(host_verts).any():
            verts = torch.tensor(
                host_verts,
                device=device,
                dtype=torch.float32,
                requires_grad=with_grad,
            )

            hull = spatial.ConvexHull(host_verts)
            faces = torch.tensor(
                hull.simplices,
                device=device,
                dtype=torch.int64,
            )
        mesh_item = Meshes(verts=[verts], faces=[faces])
        # add each cylinder in root
        mesh_collection.append(mesh_item)
    return mesh_collection


def assemble_mesh_root_method_2():
    sxml = rsml_file_r()
    tree = ET.fromstring(sxml)
    file_name_list = ['./obj/']

    # space for two different vertices
    vertices = []
    mesh_root_collection = []

    # get all the <root> link from file
    links_root = list(tree.iter('root'))

    # List for data collect
    data_root_id = []
    data_root_element_index = []
    data_root_amount = 0

    for i in links_root:
        # extract the point from <geometry><polyline><point>，which is the <point>
        # element_index : index for root element sequence
        element_index = 0
        vertices_point = []
        for point in i.findall("./geometry/polyline/point"):
            element_index = element_index + 1
            x = int(point.attrib.get('x'))
            y = int(point.attrib.get('y'))
            z = int(point.attrib.get('z'))
            pt = rsimplify.Point(element_index, x, y, z)
            vertices_point.append(pt)
            vertices_point_2 = simplify_root_dat_with_step(root_vertics_point=vertices_point, step=3)
            # vertices_point_2 = simplify_root_data(root_vertics_point=vertices_point, tolerance=2)

        lat_id = int(i.attrib.get('id'))
        print("Message: root part NO: " + str(lat_id) + " is finished, " + str(element_index) + " vertices")
        mesh_root_collection = create_mesh_root_element(vertics=vertices_point_2, mesh_collection=mesh_root_collection)
        # mesh_root_collection = create_mesh_root_element_CSG(vertices_point)

        # Data collect
        data_root_id.append(lat_id)
        data_root_element_index.append(len(vertices_point_2))
        data_root_amount += len(vertices_point_2)

    file_name_list.append(obj_filename() + '_simplfy_2.obj')
    filename = ''.join(str(e) for e in file_name_list)
    mesh = join_meshes_as_scene(mesh_root_collection)
    print("Message: assemble and create root structure")
    IO().save_mesh(data=mesh, path=filename)
    path = os.getcwd() + filename
    size = file_size(file_path=path)
    print("Message: the file has already been created")

    return data_root_id, data_root_element_index, data_root_amount, size


def assemble_mesh_root(is_simplify: bool = True):
    sxml = rsml_file_r()
    tree = ET.fromstring(sxml)
    file_name_list = ['./obj/']

    # space for two different vertices
    vertices = []
    mesh_root_collection = []

    csv_root_pos = []

    # get all the <root> link from file
    links_root = list(tree.iter('root'))

    # List for data collect
    data_root_id = []
    data_root_element_index = []
    data_root_amount = 0
    # go through whole list
    for i in links_root:
        # extract the point from <geometry><polyline><point>，which is the <point>
        # element_index : index for root element sequence
        element_index = 0
        vertices_point = []
        for point in i.findall("./geometry/polyline/point"):
            element_index = element_index + 1
            x = int(point.attrib.get('x'))
            y = int(point.attrib.get('y'))
            z = int(point.attrib.get('z'))
            if is_simplify:
                pt = rsimplify.Point(element_index, x, y, z)
                vertices_point.append(pt)
            else:
                vertices_point.append([x, y, z])
        if is_simplify:
            vertices_simplify_id = []
            vertices_point, vertices_simplify_id = simplify_root_data(root_vertics_point=vertices_point, tolerance=2)

        lat_id = int(i.attrib.get('id'))
        print("Message: root part NO: " + str(lat_id) + " is finished, " + str(len(vertices_point)) + " vertices")
        mesh_root_collection = create_mesh_root_element(vertics=vertices_point, mesh_collection=mesh_root_collection)

        # csv data
        len_points = len(vertices_point)
        if len_points == 0:
            csv_root_pos.append([0, 0, 0])
        else:
            vertice_len = int(len_points / 2)
            csv_root_pos.append(vertices_point[vertice_len])

        # Data collect
        data_root_id.append(lat_id)
        data_root_element_index.append(len(vertices_point))
        data_root_amount += len(vertices_point)

    if is_simplify:
        mesh = join_meshes_as_scene(mesh_root_collection)
        print("\n------------------------------------------------------------------")
        print("Message: assemble and create root structure")

        # file name
        file_name_list.append(obj_filename() + '_simplfy.obj')
        filename = ''.join(str(e) for e in file_name_list)
        IO().save_mesh(data=mesh, path=filename)

        # file size
        path = os.getcwd() + filename
        size = file_size(file_path=path)

        # csv
        csv_data_pos(data_root_id, csv_root_pos)

        print("Message: the file has already been created")
        print("\n------------------------------------------------------------------")
    else:
        mesh = join_meshes_as_scene(mesh_root_collection)
        print("\n------------------------------------------------------------------")
        print("Message: assemble and create root structure")

        # file name
        file_name_list.append(obj_filename() + '.obj')
        filename = ''.join(str(e) for e in file_name_list)
        IO().save_mesh(data=mesh, path=filename)

        # file size
        path = os.getcwd() + filename
        size = file_size(file_path=path)

        # csv
        csv_data_pos(data_root_id, csv_root_pos)

        print("Message: the file has already been created")
        print("\n------------------------------------------------------------------")

    return data_root_id, data_root_element_index, data_root_amount, size

import math

import numpy as np
from _cython_csg import CSG
from mathutils import Vector


def rotation_matrix_from_vectors(vec1, vec2):
    """ Find the rotation matrix that aligns vec1 to vec2
    :param vec1: A 3d "source" vector
    :param vec2: A 3d "destination" vector
    :return mat: A transform matrix (3x3) which when applied to vec1, aligns it with vec2.
    """
    # np.seterr(invalid='ignore')
    try:
        a, b = np.divide(vec1, np.linalg.norm(vec1)), np.divide(vec2, np.linalg.norm(vec2))
    except ZeroDivisionError:
        print("Error: zero division")
        print(a, b)
    except ValueError:
        print("the value error")
        print(a, b)
    except (RuntimeError, TypeError, NameError):
        print(a, b)

    a = a.reshape(3)
    b = b.reshape(3)
    v = np.cross(a, b)
    if any(v):  # if not all zeros then
        c = np.dot(a, b)
        s = np.linalg.norm(v)
        kmat = np.array([[0, -v[2], v[1]], [v[2], 0, -v[0]], [-v[1], v[0], 0]])
        return np.eye(3) + kmat + kmat.dot(kmat) * ((1 - c) / (s ** 2))
    else:

        return np.eye(3)  # cross of all zeros only occurs on identical directions


def circle(radius):
    circle_vertices = []
    for angle in range(0, 360, 10):
        angle_radius = math.radians(angle)
        x = radius * math.cos(angle_radius)
        y = radius * math.sin(angle_radius)
        circle_vertices.append([x, y, 0])
    return circle_vertices


def cylinder(point_0, point_1, radius):
    rot = rotation_matrix_from_vectors(np.array([0, 0, 1]), point_0 - point_1)
    base_circle = np.array(circle(radius=radius))
    circle_vertices_0 = np.transpose(rot @ np.array(circle(radius=radius)).T) + point_0
    circle_vertices_1 = np.transpose(rot @ np.array(circle(radius=radius)).T) + point_1
    cylinder_vertices = np.concatenate((circle_vertices_0, circle_vertices_1), axis=0)

    return cylinder_vertices


def cylinder_csg(point_0, point_1, radius):
    point_0 = list(point_0)
    point_1 = list(point_1)
    # start , end , radius , slice
    cylinder = CSG.cylinder(start=point_0, end=point_1, radius=3, slice=16)
    print(cylinder)
    mesh = []
    # try to get the mesh from csg
    print(mesh)

    return mesh


# Return degrees of rotation
def angle_from_vector(point_0, point_1):
    vec = Vector(point_1) - Vector(point_0)
    vec_oth = vec.orthogonal()
    vec_z = Vector((0, 0, -1))
    angle_radius = vec_oth.angle(vec_z)

    print(vec_oth)
    print(angle_radius)

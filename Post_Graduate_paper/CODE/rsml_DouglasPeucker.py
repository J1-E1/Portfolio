import numpy as np
from numpy import *

import math


class Point(object):
    def __init__(self, root_id, x, y, z):
        self.root_id = root_id
        self.x = x
        self.y = y
        self.z = z


class DPCompress(object):
    def __init__(self, point_list, tolerance):
        self.Compressed = list()
        self.point_list = point_list
        self.tolerance = tolerance
        self.runDP(point_list, tolerance)

    def calc_height(self, point1, point2, point):
        """
        A, B , P
        ab = b - a
        ap = p - a
        bp = p - b
        """
        ab = [point2.x - point1.x, point2.y - point1.y, point2.z - point1.z]
        ap = [point.x - point1.x, point.y - point1.y, point.z - point1.z]
        bp = [point.x - point2.x, point.y - point2.y, point.z - point2.z]

        #
        r = np.dot(ap, ab) / (np.linalg.norm(ab)) ** 2

        # 3 different cases
        if 0 < r < 1:
            # some point conbination may cause the dis <0 ===> sqrt abort
            dis = (np.linalg.norm(ap)) ** 2 - (r * np.linalg.norm(ab)) ** 2
            if dis < 0:
                dis = 0

            height = math.sqrt(dis)
        elif r >= 1:
            height = np.linalg.norm(bp)
        else:
            height = np.linalg.norm(ap)

        return height
        # dis即为所求

    def DouglasPeucker(self, point_list, first_point, last_point, tolerance):
        """
        计算通过的内容
        DP算法
        :param point_list: point list
        :param first_point: first point
        :param last_point: last point
        :param tolerance: tolerance
        :return:
        """
        maxdistance = 0.0
        indexfarthest = 0
        for i in range(first_point, last_point):
            distance = self.calc_height(point_list[first_point], point_list[last_point], point_list[i])
            if distance > maxdistance:
                maxdistance = distance
                indexfarthest = i
        #    print('max_dis=', maxDistance)

        if maxdistance > tolerance and indexfarthest != 0:
            self.Compressed.append(point_list[indexfarthest])
            self.DouglasPeucker(point_list, first_point, indexfarthest, tolerance)
            self.DouglasPeucker(point_list, indexfarthest, last_point, tolerance)

    def runDP(self, point_list, tolerance):
        """
        主要运行结果
        :param point_list: Point 列表
        :param tolerance: 值越小，压缩后剩余的越多
        :return:
        """
        if point_list is None or point_list.__len__() < 3:
            return point_list

        firspoint = 0
        lastpoint = len(point_list) - 1

        self.Compressed.append(point_list[firspoint])
        self.Compressed.append(point_list[lastpoint])

        while point_list[firspoint] == point_list[lastpoint]:
            lastpoint -= 1
        self.DouglasPeucker(point_list, firspoint, lastpoint, tolerance)

    def getCompressed(self):
        # while remove some point -- > then sort the list by id
        self.Compressed.sort(key=lambda point: int(point.root_id))
        return self.Compressed

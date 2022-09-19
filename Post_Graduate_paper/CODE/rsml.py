import xml.etree.ElementTree as ET
import rsml_DouglasPeucker as rsimplify

# filename = "/Users/zhouxuhao/PycharmProjects/RMSL2obj/data/0414_roots/0414_roots.rsml"
filename = "/Users/zhouxuhao/PycharmProjects/RMSL2obj/data/0380_roots/0380_roots.rsml"


def rsml_file_r():
    """open and read rsml file , return string data"""
    rsml_file = open(filename, mode="r", encoding="utf-8")
    rsml_file_data = rsml_file.read()
    rsml_file.close()
    return rsml_file_data


def csv_data():
    sxml = rsml_file_r()
    tree = ET.fromstring(sxml)
    root_label = []
    root_inf = []
    links_tag_root = list(tree.iter('root'))
    links_tage_root = list(tree.iter('annotations'))

    for i in links_tag_root:
        label = i.attrib.get('label')
        root_label.append(label)
        inf_name = 'name:' + ''
        inf_point = 'point:' + ''
        inf_value = 'value:' + ''
        for anno in i.findall('annotations'):
            for inf in anno.findall('annotation'):
                if inf.attrib['name'] is not None:
                    inf_name = 'name:'.join(inf.attrib.get('name'))

                # point : [x,y,z]
                x = inf.find('point').attrib.get('x')
                y = inf.find('point').attrib.get('y')
                z = inf.find('point').attrib.get('z')
                inf_point = 'point: '.join(str([x, y, z]))

                # value
                inf_value = "value: ".join(inf.find('value').text)
        root_inf.append([inf_name, inf_point, inf_value])

    return root_label, root_inf


def obj_filename():
    filename_list = filename.split('/')

    for value in filename_list:
        if value.find('.rsml') != -1:
            value = value.replace('.rsml', '')
            return value


def metadata_show():
    """ show the metadata"""
    sxml = rsml_file_r()
    tree = ET.fromstring(sxml)
    for el in tree.findall('metadata'):
        print('-------------------')
        for ch in list(el):
            if ch.text is None:
                ch.text = ""
            print('{:>15}: {:<30}'.format(ch.tag, ch.text))


def extrate_root_inf():
    sxml = rsml_file_r()
    tree = ET.fromstring(sxml)

    """show the scane data"""
    for el in tree.findall('scene'):
        print('-------------------')
        for ch in list(el):
            if ch.text is None:
                ch.text = ""
            print('{:>15}: {:<5}: {:<5}'.format(ch.tag, ch.attrib.get('id'), ch.attrib.get('label')))


def extrate_point_data():
    """
    Extract the root coordination data from the Rsml(XML) file
    :return: List: vertices, id == a four-argument list of coordinates
    :return: List: vertices_point: a list of point structs
    """

    sxml = rsml_file_r()
    tree = ET.fromstring(sxml)

    # space for two different vertices
    vertices = []
    vertices_point = []
    # get all the <root> link from file
    links_root = list(tree.iter('root'))

    # go through whole list
    for i in links_root:
        # extract the point from <geometry><polyline><point>
        # which is the <point>
        for point in i.findall("./geometry/polyline/point"):
            id = int(i.attrib.get('id'))
            x = int(point.attrib.get('x'))
            y = int(point.attrib.get('y'))
            z = int(point.attrib.get('z'))
            pt = rsimplify.Point(id, x, y, z)
            vertices_point.append(pt)
            vertices.append([id, x, y, z])
    return vertices, vertices_point


def simplify_root_dat_with_step(root_vertics_point, step):
    points = []
    for index in range(0, len(root_vertics_point) - 1, step):
        x = root_vertics_point[index].x
        y = root_vertics_point[index].y
        z = root_vertics_point[index].z
        points.append([x, y, z])

    # points.sort(key=lambda point: point[0])
    return points


def simplify_root_data(root_vertics_point, tolerance):
    points = []
    points_re = []
    points_re_id = []
    dp = rsimplify.DPCompress(root_vertics_point, tolerance)
    points = dp.getCompressed()
    for point in points:
        points_re.append([point.x, point.y, point.z])
        points_re_id.append([point.root_id, point.x, point.y, point.z])

    # See what the content of specific coordinates is
    # same line as for
    # print(points_re_id)

    return points_re, points_re_id


# root_label, root_inf = csv_data()
# print(root_inf)
# Test: for extrate_root_data()
'''
vertice, vertice_point = extrate_root_data()
print(vertice)
'''

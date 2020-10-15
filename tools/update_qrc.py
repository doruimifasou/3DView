from lxml import etree
import os


def recursive_add_elements(path_name, root_path, ele_qresource):
    with os.scandir(path_name) as it:
        for file in it:
            if not file.name.startswith('.'):
                if file.is_file():
                    relative_fname = 'assets' + file.path[len(root_path):]
                    # print(file.name, file.path, relative_fname)
                    ele_file = etree.SubElement(ele_qresource, 'file')
                    ele_file.text = relative_fname
                else:
                    recursive_add_elements(file.path, root_path, ele_qresource)


# create the file structure
RCC = etree.Element('RCC')
RCC.set('version', "1.0")
qresource = etree.SubElement(RCC, 'qresource')
recursive_add_elements("./modules/pointcloud_viewer/src/assets", "./modules/pointcloud_viewer/src/assets", qresource)
# create a new XML file with the results
# mydata = ET.tostring(data)
# myfile = open("./items2.xml", "w")
tree = etree.ElementTree(RCC)
tree.write("./modules/pointcloud_viewer/src/ui_resources.qrc", encoding="UTF-8", pretty_print=True,
           doctype='<!DOCTYPE RCC>')

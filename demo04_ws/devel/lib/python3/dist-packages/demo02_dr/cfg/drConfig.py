## *********************************************************
##
## File autogenerated for the demo02_dr package
## by the dynamic_reconfigure package.
## Please do not edit.
##
## ********************************************************/

from dynamic_reconfigure.encoding import extract_params

inf = float('inf')

config_description = {'name': 'Default', 'type': '', 'state': True, 'cstate': 'true', 'id': 0, 'parent': 0, 'parameters': [{'name': 'int_param', 'type': 'int', 'default': 50, 'level': 0, 'description': '整型参数', 'min': 0, 'max': 100, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'double_param', 'type': 'double', 'default': 1.57, 'level': 0, 'description': '浮点参数', 'min': 0.0, 'max': 3.14, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'string_param', 'type': 'str', 'default': 'hello world ', 'level': 0, 'description': '字符串参数', 'min': '', 'max': '', 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}, {'name': 'bool_param', 'type': 'bool', 'default': True, 'level': 0, 'description': 'bool参数', 'min': False, 'max': True, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'bool', 'cconsttype': 'const bool'}, {'name': 'list_param', 'type': 'int', 'default': 0, 'level': 0, 'description': '列表参数', 'min': 0, 'max': 2, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': "{'enum': [{'name': 'small', 'type': 'int', 'value': 0, 'srcline': 25, 'srcfile': '/home/qinghuan/env_cv/demo04_ws/src/demo02_dr/cfg/dr.cfg', 'description': 'a small size', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'mediun', 'type': 'int', 'value': 1, 'srcline': 26, 'srcfile': '/home/qinghuan/env_cv/demo04_ws/src/demo02_dr/cfg/dr.cfg', 'description': 'a medium size', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'big', 'type': 'int', 'value': 2, 'srcline': 27, 'srcfile': '/home/qinghuan/env_cv/demo04_ws/src/demo02_dr/cfg/dr.cfg', 'description': 'a big size', 'ctype': 'int', 'cconsttype': 'const int'}], 'enum_description': 'a car size set'}", 'ctype': 'int', 'cconsttype': 'const int'}], 'groups': [], 'srcline': 246, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'class': 'DEFAULT', 'parentclass': '', 'parentname': 'Default', 'field': 'default', 'upper': 'DEFAULT', 'lower': 'groups'}

min = {}
max = {}
defaults = {}
level = {}
type = {}
all_level = 0

#def extract_params(config):
#    params = []
#    params.extend(config['parameters'])
#    for group in config['groups']:
#        params.extend(extract_params(group))
#    return params

for param in extract_params(config_description):
    min[param['name']] = param['min']
    max[param['name']] = param['max']
    defaults[param['name']] = param['default']
    level[param['name']] = param['level']
    type[param['name']] = param['type']
    all_level = all_level | param['level']

dr_small = 0
dr_mediun = 1
dr_big = 2
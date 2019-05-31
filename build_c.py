import sys
import os
import subprocess
#Why not custom build system?

def determine_path_to_dependency(own_path, dep_rel_path):
    path = own_path
    if "\\" in path:
        path = path.replace("\\", "/")
    
    rel_dir_parts = path.split("/")[0:-1]
    rel_dir = "/".join(rel_dir_parts)
    dep_rel_source = dep_rel_path.replace(".h", ".c")
    rel_path = rel_dir + "/" + dep_rel_source
    if rel_path.startswith("/"):
        rel_path = "." + rel_path
    return rel_path
    
def determine_file_name(path):
    if "\\" in path:
        path = path.replace("\\", "/")
    filename = path.split("/")[-1]
    return filename

class SourceFile:
    def __init__(self, path):
        self.path = path
        self.filename = determine_file_name(path)
        self.dependencies = []
        with open(path, 'r') as source:
            for code_line in source:
                if code_line.startswith("#include"):
                    _, __, dep_rel_path = code_line.partition("#include")
                    dep_rel_path = dep_rel_path.strip()
                    if dep_rel_path.startswith("<"):
                        continue
                    elif dep_rel_path.startswith("\""):
                        dep_rel_path = dep_rel_path.replace("\"", "")
                        dep_path = determine_path_to_dependency(path, dep_rel_path)
                        dep_name = determine_file_name(dep_path)
                        if dep_name.replace(".h", ".c") == self.filename:
                            continue
                        dep = SourceFile(dep_path)
                        self.dependencies.append(dep)

    def get_build_order(self):
        build_order = list()
        def add_to_build_order(source_file):
            for dep in source_file.dependencies:
                add_to_build_order(dep)
            build_order.append(source_file.path)
        add_to_build_order(self)
        
        #Convert build_order to absolute paths.
        build_order_unique = set(map(os.path.abspath, build_order))
        
        return build_order_unique

def determine_build_order(path_to_main):
    #By definition, a main file, aka any file with a main-method must have references to all dependencies.
    main = SourceFile(path_to_main)
    build_order = main.get_build_order()
    return build_order

def build(path_to_main, output_path):
    print("Building source: '{}' to {}.".format(path_to_main, output_path))    
    build_order = " ".join(determine_build_order(path_to_main))
    command = "gcc -ggdb -pedantic -Wall -Wextra -rdynamic -Wno-unknown-pragmas " + build_order + " -o " + output_path
    print("Running command:", command)
    subprocess_args = command.split(' ')
    output = subprocess.run(subprocess_args, stdout=subprocess.PIPE).stdout.decode('utf-8')
    if len(output.strip()) > 1:
        print(output)
    print("Exiting build process...")    

def main(argv):
    if len(argv) != 3:
        print("Usage of this program:\npython build_c.py <main file> <output path>")
        return
    path_to_main = argv[1]
    output_path = argv[2]
    build(path_to_main, output_path)

if __name__ == '__main__':
    main(sys.argv)

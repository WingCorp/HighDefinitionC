import sys

def load_file(file_path):
    libs = []
    lines = []
    try:
        with open(file_path, 'r') as content:
            for line in content:
                if line.startswith("#include") and ('<' not in line and '>' not in line):
                    continue
                if line.startswith("#include"):
                    libs.append(line)
                    continue
                lines.append(line)
    except FileNotFoundError as _:
        print("Warning, file not found: '{}'".format(file_path))
        pass
    return (libs, ''.join(lines))

def remove_unused(single_source):
    lines = single_source.splitlines
    main_start = 0
    main_end = 0
    for i, line in enumerate(lines):
        if "int" in line and "main(" in line:
            main_start = i
    for i, line in enumerate(lines):
        block_depth = -1
        if line <= main_start:
            if "{" in line:
                block_depth += 1
            if "}" in line:
                block_depth -= 1
            if block_depth == 0:
                main_end = i
    
    main_method = lines[main_start:main_end + 1]
    #fuckit, i'm not gonna make it.
    pass

def monolithize(hdc_header_path, output_path):

    single_source = ""
    std_libs = []
    with open(hdc_header_path) as header:
        for line in header:
            line = str(line)
            if line.startswith("#include") and ('<' not in line and '>' not in line):
                h_path = './' + line.split(' ')[1].replace('"', '').strip()
                c_path = h_path.replace('.h', '.c')
                print("including header '{}' and corresponding source.".format(h_path))
                (libs, code) = load_file(h_path)
                std_libs += libs
                single_source += code
                (libs, code) = load_file(c_path)
                std_libs += libs
                single_source += code
                single_source += '\n'
                continue
            if line.startswith("#include"):
                std_libs.append(line)
                continue
            if line.startswith("#"):
                continue
            single_source += line
    
    std_libs = reversed(list(set(std_libs)))
    for lib in std_libs:
        single_source = lib + '\n' + single_source

    with open(output_path, 'w') as output:
        output.write(single_source)

def main(argv):
    if len(argv) != 3:
        print("Usage of this program:\npython monolithize.py <hdc header path> <output path>")
        return
    hdc_header_path = argv[1]
    output_path = argv[2]
    print("Monolithizing code: '{}' to '{}'.".format(hdc_header_path, output_path))
    monolithize(hdc_header_path, output_path)
    print("Done.")


if __name__ == "__main__":
    main(sys.argv)
    pass
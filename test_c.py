import sys
from os import listdir, walk
from os.path import isfile, join, split
import subprocess

def get_files_in_dir(path):
    return [join(path, f) for f in listdir(path) if isfile(join(path, f)) and f.endswith(".o")]

def get_test_results(output):
    passed = 0
    failed_tests = []
    current_test = None
    
    print(output)
    
    for l in output.splitlines(False):
        if "Running test:" in l:
            current_test = l.split("'")[1]
        elif "Test failed!" in l:
            if current_test is not None:
                failed_tests.append(current_test)
            else:
                failed_tests.append("unknown test")
        elif "Test passed!" in l:
            passed = passed + 1
    return (failed_tests, len(failed_tests) + passed)

def run_tests(test_suite):
    _, test_name = split(test_suite)
    print("Tests in {}:\n".format(test_name))
    cmd = [test_suite]
    sp = subprocess.run(cmd, stdout=subprocess.PIPE)
    try:
        sp.check_returncode()
    except:
        print("Tests in {} caused a segmentation fault!\n".format(test_name))
        return (0, 1)
    output = sp.stdout.decode("utf-8")
    failed_tests, total = get_test_results(output)
    failed_len = len(failed_tests)
    if failed_len is 0:
        print("All tests in {} passed!\n".format(test_name))
    else:
        print("{} out of {} tests failed in {}!\nFailed tests were:".format(failed_len, total, test_name))
        for f in failed_tests:
            print(f)
    return (total - failed_len), failed_len

def run_tests_suites(files):
    print("Running {} tests suites!\n".format(len(files)))
    passed_total = 0
    failed_total = 0
    for test_suite in files:
        passed, failed = run_tests(test_suite)
        print("testing in {} returned {} passed and {} failed".format(test_suite, passed, failed))
        passed_total += passed
        failed_total += failed
    print("{} tests failed, {} tests passed, ran in total {} tests.".format(failed_total, passed_total, failed_total + passed_total))

def main(argv):
    if len(argv) != 2:
        print("Usage of this program:\npython3 test_c.py <test directory path>")
        return
    pass
    path = argv[1]
    test_files = get_files_in_dir(path)
    run_tests_suites(test_files)

if __name__ == '__main__':
    main(sys.argv)
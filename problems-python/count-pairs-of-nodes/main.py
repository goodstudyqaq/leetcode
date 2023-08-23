import os
import sys
# Get the current directory of the script (subpackage1)
current_dir = os.path.dirname(os.path.abspath(__file__))

# Get the parent directory (my_package)
parent_dir = os.path.dirname(current_dir)

# Add the parent directory to sys.path
sys.path.append(parent_dir)
from solution import *

if __name__ == '__main__':
    sol: Solution = Solution()
    # Read data from file
    current_dir = os.path.dirname(os.path.abspath(__file__))
    f = open(f"{current_dir}/data", "r")
    data = f.readlines()
    data = [line.strip() for line in data]

    input_number = 3
    output_number = 1
    one_test_number = input_number + output_number
    if len(data) % one_test_number:
        print("The format of test data is incorrect")
        exit(1)

    test_number = len(data) // one_test_number
    all_test = test_number
    fail_test = 0

    for i in range(test_number):
        print(f"Case {i + 1} testing...")
        n: int = convert_params(data[i * one_test_number + 0], 'int')
        edges: List[List[int]] = convert_params(data[i * one_test_number + 1], 'List[List[int]]')
        queries: List[int] = convert_params(data[i * one_test_number + 2], 'List[int]')
        real_res: List[int] = convert_params(data[i * one_test_number + 3], 'List[int]')

        my_res: List[int] = sol.countPairs(n, edges, queries)

        check_result = compare_result(f"{i + 1}", my_res, real_res, 'List[int]')
        if not check_result:
            fail_test += 1

    print("The number of test cases: ", all_test)
    print("The number of test cases failed: ", fail_test)

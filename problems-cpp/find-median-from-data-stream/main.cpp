#include "./solution.h"

int main() {
    ifstream infile;
    infile.open("./data", ios::in);
    string strLine;
    int one_test_number = 3;  // It has 3 rows: function, input, output
    vector<string> data;
    while (getline(infile, strLine)) {
        if (strLine.size()) {
            data.push_back(strLine);
        }
    }
    if (data.size() % (one_test_number)) {
        cerr << "The format of test data is incorrect" << endl;
        return 0;
    }
    int all_test = 0, fail_test = 0;
    int test_number = data.size() / one_test_number;
    for (int i = 0; i < test_number; i++) {
        cerr << "Case " << to_string(i + 1) + " testing..." << endl;
        vector<string> function_names = split_str_to_func(data[i * one_test_number + 0]);
        vector<string> input_params = split_str_to_params(data[i * one_test_number + 1]);
        vector<string> output_params = split_str_to_params(data[i * one_test_number + 2]);
        vector<string> input_param;

        // The first one is usually initialization
        input_param = split_str_to_params(input_params[0]);
        int func_num = function_names.size();
        MedianFinder sol = MedianFinder();

        for (int j = 1; j < func_num; j++) {
            input_param = split_str_to_params(input_params[j]);
            if (function_names[j] == "addNum") {
                int num;
                convert_params(input_param[0], num);
                sol.addNum(num);
            }
            if (function_names[j] == "findMedian") {
                double real_res;
                convert_params(output_params[j], real_res);
                double my_res = sol.findMedian();
                bool check_result = compare_result(to_string(i + 1) + "-" + to_string(j), my_res, real_res);
                all_test++;
                if (!check_result) fail_test++;
            }
        }
    }

    cerr << "The number of test cases: " << test_number << endl;
    cerr << "The number of test cases failed: " << fail_test << endl;
    return 0;
}

#include "./solution.h"

int main() {
    Solution sol = Solution();
    // Read data from file
    ifstream infile;
    infile.open("./data", ios::in);
    string strLine;

    int input_number = 4;
    int output_number = 1;
    int one_test_number = input_number + output_number;
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
    int test_number = data.size() / one_test_number;

    int all_test = test_number;
    int fail_test = 0;

    for (int i = 0; i < test_number; i++) {
        cerr << "Case " << to_string(i + 1) + " testing..." << endl;

        int n;
        convert_params(data[i * one_test_number + 0], n);
        int minProfit;
        convert_params(data[i * one_test_number + 1], minProfit);
        vector<int> group;
        convert_params(data[i * one_test_number + 2], group);
        vector<int> profit;
        convert_params(data[i * one_test_number + 3], profit);
        int real_res;
        convert_params(data[i * one_test_number + 4], real_res);

        int my_res = sol.profitableSchemes(n, minProfit, group, profit);

        bool check_result = compare_result(to_string(i + 1), my_res, real_res);
        if (!check_result) {
            fail_test++;
        }
    }
    cerr << "The number of test cases: " << test_number << endl;
    cerr << "The number of test cases failed: " << fail_test << endl;
    return 0;
}
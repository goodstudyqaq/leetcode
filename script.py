"""
This script will read problem directory and flush the data to data.json and then modify the readme.md file
"""
import json
import os
from datetime import datetime
import pytz
# read data.json
current_dir = os.path.dirname(os.path.realpath(__file__))
with open(f'{current_dir}/data.json', "r") as f:
    datas = json.load(f)


problem_cpp = set()
problem_python = set()
problems = set()
for problem in os.listdir(f'{current_dir}/problems-cpp'):
    if problem == "utils":
        continue
    problem_cpp.add(problem)
    problems.add(problem)

for problem in os.listdir(f'{current_dir}/problems-python'):
    if problem == "utils":
        continue
    problem_python.add(problem)
    problems.add(problem)

target_timezone = pytz.timezone('Asia/Shanghai')

for problem in problems:
    cpp_url = f"https://github.com/goodstudyqaq/leetcode/blob/main/problems-cpp/{problem}/solution.h" if problem in problem_cpp else ""
    python_url = f"https://github.com/goodstudyqaq/leetcode/blob/main/problems-python/{problem}/solution.py" if problem in problem_python else ""
    tutorial_url = f"https://github.com/goodstudyqaq/leetcode/blob/main/problems-cpp/{problem}/README.md" if os.path.exists(f'{current_dir}/problems-cpp/{problem}/README.md') else ""
    # utc+8
    now = datetime.now(tz=target_timezone).strftime("%d/%m/%Y %H:%M:%S")
    problem_data = {
        "name": problem,
        "url": f"https://leetcode.com/problems/{problem}/",
        "date": now if problem not in datas["problem"] else datas["problem"][problem]["date"],
        "cpp": cpp_url,
        "python": python_url,
        "tutorial": tutorial_url,
    }
    datas["problem"][problem] = problem_data


# sort problem by date time 
datas["problem"] = dict(sorted(datas["problem"].items(), key=lambda x: x[1]["date"], reverse=True))


# write data.json
with open(f'{current_dir}/data.json', "w") as f:
    json.dump(datas, f, indent=4)

# write readme.md
with open(f'{current_dir}/README.md', "w") as f:
    f.write(f"# Leetcode\n")
    f.write(f"## Contest\n")
    data = datas["contest"]
    f.write("| # | Date | Rank | Solved | \n")
    f.write("|---|---|---|---|\n")
    for contest in data:
        f.write(f"| [{contest}]({data[contest]['url']}) | {data[contest]['date']} | {data[contest]['rank']} | {data[contest]['solved']} |\n")
    f.write(f"## Problem\n")
    data = datas["problem"]
    f.write("| # | Date | C++ | Python | Tutorial | \n")
    f.write("|---|---|---|---|---|\n")
    for problem in data:
        cpp_text = f"[✅]({data[problem]['cpp']})" if data[problem]["cpp"] else "❌"
        python_text = f"[✅]({data[problem]['python']})" if data[problem]["python"] else "❌"
        tutorial_text = f"[✅]({data[problem]['tutorial']})" if data[problem]["tutorial"] else "❌"
        f.write(f"| [{problem}]({data[problem]['url']}) | {data[problem]['date']} | {cpp_text} | {python_text} | {tutorial_text} |\n")




---
title: Cantor expansion
date: '2023-08-26'
tags: ['math']
draft: false
summary: Introduction to Cantor expansion
---

When I tried to solve the [leetcode problem](https://leetcode.com/problems/permutation-sequence/description/), I suddenly remembered that I had learned a method to solve this problem in my college. It is called Cantor expansion. However I forgot the details of this method. So I decided to write this blog to record the details of this method.

## Cantor expansion

What is cantor expansion? It is a method to convert a permutation to a number based on the order of the permutation. So the question is that how we can know a permutation has how many permutations before it. Let's begin to solve that. The thought is like `digital dp`. We can fix the prefix number of the permutation and calculate the number of permutations that have the same prefix and are smaller than the permutation we have. Firstly, we assume the length of the same prefix number is 0. Then we need to know how many number are smaller than the first number of the permutation. For example, if the permutation is $[3, 1, 4, 2]$. We can set the first number to 1 or 2, and the left number we can set in any order. So the contribution of this case is $2 * 3!$. Let's continue the process and calculate the contribution that the length of the same prefix number is 1, which means the first number must be 3 and the second number must be smaller than 1. It is obvious that the contribution is 0. We continue the process until the length is $ n - 1 $. So we can easily write the code to solve this problem.

```cpp
const int maxn = 10;
long long fact[maxn];
void init() {
    fact[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fact[i] = fact[i - 1] * i;
    }
}
int p[maxn];
int A[maxn]; // A[i] means how many numbers in [i + 1, n) are smaller than p[i]
long long cantor() {
    long long res = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = i + 1; j < n; j++) {
            if (p[j] < p[i]) {
                cnt++;
            }
        }
        A[i] = cnt;
    }

    for (int i = 0; i < n; i++) {
        res += A[i] * fact[n - i - 1];
    }
    return res;
}
```

## Inverse Cantor expansion
Based on the introduction above, we can write the formula:
$$
\begin{equation}
\begin{aligned}
\text{cnt} &= \sum_{i = 0}^{n - 1} A[i] * (n - i - 1)! \\
\end{aligned}
\end{equation}
$$

But how can we get the permutation based on the cnt? Firstly, we know:
$$
\begin{equation}
\begin{aligned}
n! &= n * (n - 1)! \\
&= (n - 1) * (n - 1)! + (n - 1)! \\
&= \sum_{i = 0}^{n - 1} i * i! + 1
\end{aligned}
\end{equation}
$$

Then, let's calculate the max number of the permutation from $[j, n)$:
$$
\begin{equation}
\begin{aligned}
\sum_{i = j} ^ {n - 1} A[i] * (n - i - 1)! &\leq \sum_{i = j} ^ {n - 1} (n - i - 1) * (n - i - 1)! \\
&\leq \sum_{i = 0} ^ {n - j - 1} i * i! \\
&\leq (n - j)! - 1
\end{aligned}
\end{equation}
$$

So we can get the max number of the permutation from $[j, n)$. It is $(n - j)! - 1$. The number is smaller than the weight in `j - 1`, which is $(n - j)!$ What does that means? It means it is like a binary or other base number. We can get each digit only by divided the weight. Now, we can get `A`. It is easily to get the permutation from `A`. We just need to for loop `A` from 0 to n - 1, and keep the remain number. So we can get the permutation by the following code:

```cpp
const int maxn = 10;
long long fact[maxn];
void inverse_cantor(long long cnt) {
    vector<int> remain_number;
    for (int i = 1; i <= n; i++) {
        nums.push_back(i);
    }
    for (int i = 0; i < n; i++) {
        int weight = fact[n - i - 1];
        int pos = cnt / weight;
        cnt %= weight;
        p[i] = nums[pos];
        nums.erase(nums.begin() + pos);
    }
}
```

## Summary
To be honest, I don't know the principle of this method when I was in college. I just copy the code when I need to use it. But now, I know the principle of this method. It is easy to understand.
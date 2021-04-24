#pragma once

template<const int N>
constexpr int getElem(const std::array<std::array<int, N>, N>& matr, int i, int j)
{
    return matr[i][j];
}

template<const int N>
constexpr int det(const std::array<std::array<int, N>, N>& matr, const int rowNum, const int colNum, const bool columns[N])
{
    if(rowNum >= N && colNum >= N)
        return 1;

    bool columns2[N] = {false};
    for(int i = 0; i < N; i++)
        columns2[i] = columns[i];
    int sum = 0;
    int columnNum = 0;
    for(int i = 0; i < N; i++)
    {
        if(columns[i]==false)
            continue;

        int a = getElem<N>(matr, rowNum, i);
        if(columnNum%2 != 0)
            a=-a;
        columnNum++;

        columns2[i] = false;
        sum += a*det<N>(matr, rowNum+1, colNum+1, columns2);
        columns2[i] = true;
    }
    return sum;
}

template<const int N>
constexpr int determinant(const std::array<std::array<int, N>, N>& matr)
{
    if(N <= 1)
        return matr[0][0];
    bool columns[N] = {true};
    for(int i = 0; i < N ;i++)
    {
            columns[i] = true;
    }
    return det<N>(matr, 0, 0, columns);
}

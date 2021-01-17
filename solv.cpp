int a[N];//твой массив стоимостей
int dp[N][k];//какую максимальную прибыль мы можем получить за первые N дней, причем мы покупали-продавали акции k раз и последнее наше действие-продажа
int dp2[N][k];//тоже самое, но последнее действие-покупка акции
const int inf = 1e9;
int p[N][k];//массив для восстановления ответа.храним когда мы в последний раз купили акцию
int p2[N][k];
for (int i = 0; i < N; ++i) {
    for (int j = 0; j <= k; ++j) {
        if (j == 0) {
            dp[i][j] = 0;
            dp2[i][j] = -inf;
            p[i][j] = -1;
            p2[i][j] = -1;
        } else {
            //пересчитаем dp
            if (i != 0) {
                dp[i][j] = dp[i - 1][j];//типа в день i мы чиллим
                p[i][j] = p[i - 1][j];
                if (dp[i][j] < dp2[i - 1][j] + a[i]) {
                    dp[i][j] = dp2[i - 1][j - 1] + a[i];
                    p[i][j] = i;
                }
            } 
            //пересчитываем dp2
            if (i != 0) {
                dp2[i][j] = dp2[i - 1][j];
                p2[i][j] = p2[i - 1][j];
                if (dp2[i][j] < dp[i - 1][j - 1] - a[i]) {
                    dp2[i][j] = dp[i - 1][j - 1] - a[i];
                    p2[i][j] = i;
                }
            }
        }
    }
}
int type = 2;
int day = p[N - 1][k];
int curcnt = k;
vector<pair<int, int>> ans;//храним ответ в формате: 1 day-купили акциюm 2 day-продали акцию
while (day != -1) {
    ans.push_back({ type,day + 1 });
    if (type == 2) {
        day = p2[day - 1][curcnt];
        type = 1;
    } else {
        day = p[day - 1][curcnt - 1];
        type = 2;
        curcnt -= 1;
    }
}
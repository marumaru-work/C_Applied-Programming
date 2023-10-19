#include <stdio.h>
#include <math.h> // pow 用

int main(int argc, char const *argv[])
{
    char hexes[] = "78"; // 1111000
    // char hexes[] = "FF"; // 11111111
    // char hexes[] = "00"; // 0
    size_t n = sizeof(hexes) - 1;          // 配列のサイズ
    char hex_table[] = "0123456789ABCDEF"; // 16進数への変換用テーブル
    size_t n_hex_table = sizeof(hex_table);
    int b = 0; // 2進数用の変数

    int sum[n];    // 10進数から2進数に変換した、int型の配列 (ex : {111, 1000})
    int count = 0; // 2進数の桁をカウントするための変数

    // ■ 16進数 → 10進数
    for (int i = 0; i < n; i++)                     // hexes配列のサイズ分、繰り返す
    {
        for (int j = 0; j < n_hex_table - 1; j++)   // 16進数テーブルから一つずつ調べる
        {
            if (hexes[i] == hex_table[j])           // hexes配列のi番目の文字と16進数テーブルのj番目の文字が同じなら、if文の中身を実行。このとき、i番目の文字(16進数) = j(10進数)である。
            {
                // ■ 10進数 → 2進数
                sum[i] = 0;                         // 初期化
                for (int k = 0; j != 0; k++)        // j(10進数)が0になるまで繰り返す (ex: 3 / 2 = 1 → 1 / 2 = 0 ← ここで2進数の変換が全て終わった)
                {
                    sum[i] += (j % 2) * pow(10, k); // (j % 2) * 10^k = 2進数の数字を生成 (k = 0, 1, 2, ...)
                    j /= 2;                         // 次の桁の計算のため (ex: 7 / 2 = 3 → 「3 % 2」で使用するため)
                    count++;                        // 2進数の桁をカウントしている
                }
                break;                              // i番目の文字(16進数)は2進数に変換されたため、for文(for (int j = 0; j < n_hex_table - 1; j++))を抜ける
            }
        }
    }

    int group = count / 4;                          // 3 / 4 = 0, 4 / 4 = 1, 7 / 4 = 1 , 8 / 4 = 2 ... sum配列のグループ数。 (ex: {111, 1000}なら1、{1111, 1111}なら2)
    int num = count % 4;                            // 3 % 4 = 3, 4 % 4 = 0, 7 % 4 = 3 , 8 % 4 = 0 ... sum配列の0番目にある数字の数。数字が4つある場合はグループにカウントされる(ex: {111, 1000}なら3、{1111, 1111}なら0)
    
    // ◇2進数の桁に応じて10^nする処理
    // ■sum配列の0番目
    if (num != 0)                                   // sum配列の0番目にある数字の数が0ではない → sum[0](num桁の2進数) * 10^(count(sum配列全ての合計桁) - num(0番目にある数字のnum桁))
    {
        b = sum[0] * pow(10, count - num);          // (ex : 111 * 10^(7 - 3) = 1110000(変数b))
    }
    else                                            // sum配列の0番目にある数字の数が0である → sum[0](num桁の2進数) * 10^(count(sum配列全ての合計桁) - 4(0番目にある数字の桁数))
    {
        b = sum[0] * pow(10, count - 4);            // (ex : 1111 * 10^4 = 11110000(変数b))
        group--;                                    // 1グループ分(4)を計算に使用したため、グループから1引く
    }
    
    // ■sum配列の0番目以降
    int digit = group * 4;                          // nグループ * 4 → 残りの数字の数が「n」つある（sum配列の0番目に格納されている数字以外は残りn桁ある）
    for (int i = 1; i <= group; i++)                // sum[1]からグループ分だけ繰り返す
    {
        b += sum[i] * pow(10, digit - 4);           // (ex : 1000 * 10^(4 - 4) + 1110000(変数b) = 1111000(変数b))
        digit -= 4;                                 // 1グループ分(4)を計算に使用したため、変数digitから4を引く
    }

    printf("%s %d\n", hexes, b); // 変換前と変換後の表示
    return 0;
}

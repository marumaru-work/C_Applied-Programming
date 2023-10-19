#include <stdio.h>

int main(int argc, char const *argv[])
{
    char bits[] = "00110101";    // 2進数を表す文字列
    size_t n = sizeof(bits) - 1; // 変数 bits のサイズ
    for(int i = 0; i < n; i++)
    {
        printf("%c", bits[i]); // char型の数字を表示（アスキー）
    }
    return 0;
}

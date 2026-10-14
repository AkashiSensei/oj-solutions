/*
 * Multiply large nonnegative integers represented as decimal strings
 * using a custom complex-number FFT, inverse FFT, and decimal carry propagation.
 */

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>

#define MAX_SIZE 0x20005
#define DATA_TYPE double

using namespace std;

struct Complex {
    DATA_TYPE real;
    DATA_TYPE image;

    Complex(DATA_TYPE real, DATA_TYPE image) : real(real), image(image) {}
    Complex() {}

    inline Complex operator+(const Complex &c) {
        return Complex(real + c.real, image + c.image);
    }
    inline Complex operator-(const Complex &c) {
        return Complex(real - c.real, image - c.image);
    }
    inline Complex operator*(const Complex &c) {
        return Complex(real * c.real - image * c.image, real * c.image + image * c.real);
    }
    inline Complex operator*(const int &i) {
        return Complex(real * i, image * i);
    } 
};

char A[MAX_SIZE];
char B[MAX_SIZE];
Complex LIST0[MAX_SIZE * 2];
Complex LIST1[MAX_SIZE * 2];

void pecursive_fft(char * src, Complex * result, int length_a, int n);
void pecursive_inverse_fft(Complex * src, Complex * result, int n);

int main() {
    int t, n, lena, lenb, maxLen;
    int carry;
    scanf("%d", &t);
    while (t--) {
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        scanf("%s %s", A, B);
        lena = strlen(A);
        lenb = strlen(B);

        for(n = 1; n < lena || n < lenb; n = n << 1);
        n = n << 1;

        pecursive_fft(A, LIST0, lena, n);
        pecursive_fft(B, LIST1, lenb, n);

        for(int i = 0; i < n; i++) {
            LIST0[i] = LIST0[i] * LIST1[i];
        }

        pecursive_inverse_fft(LIST0, LIST1, n);

        int ch_int;
        int carry = 0;
        memset(B, 0, sizeof(B));
        for(int out_inx = n - 1, src_inx = 0; ~out_inx; out_inx--, src_inx++) {
            ch_int = int(LIST1[src_inx].real / n + 0.5) + carry;
            carry = ch_int / 10;
            B[out_inx] = char(ch_int % 10) + '0';
        }
        int high_bit;
        for(high_bit = 0; !B[high_bit]; high_bit++);
        for(; B[high_bit] == '0'; high_bit++);
        puts(B + high_bit);
    }
}

void pecursive_fft(char * src, Complex * result, int length_a, int n) {
    double pi_2 = M_PI * 2;
    double n_double = n;
    int layer_cnt = 0, layer;
    int group_cnt, group;
    int symmetry_shift;
    int cal_in_group;
    int reverse_inx, inx, k;
    Complex omega, odd;
    for(int i = n; i > 1; i = i >> 1, layer_cnt++);
    
    
    memset(result, 0, sizeof(Complex) * n);
    for(inx = 0; inx < length_a; inx++) {
        reverse_inx = 0;
        for(int bit_num = 0; bit_num < layer_cnt; bit_num++) {
            reverse_inx = reverse_inx | ((inx & (1 << bit_num))?1: 0);
            reverse_inx = reverse_inx << 1;
        }        
        result[reverse_inx >> 1] = Complex(double(src[length_a - inx - 1] - '0'), 0);
    }
    

    /*
    for(int i = 0, j = length_a - 1; ~j; j--, i++) {
        result[i].real = double(src[j] - '0');
        result[i].image = 0;
    }
    for(int i = length_a; i < n; i++) {
        result[i].image = 0;
        result[i].real = 0;
    }
    */


    for(layer = 0; layer < layer_cnt; layer++) {
        group_cnt = 1 << (layer_cnt - layer - 1);
        symmetry_shift = 1 << layer;
        for(group = 0; group < group_cnt; group++) {
            for(cal_in_group = 0; cal_in_group < symmetry_shift; cal_in_group++) {
                inx = 2 * group * symmetry_shift + cal_in_group;
                k = group_cnt * cal_in_group;
                omega.real = cos(pi_2 * k / n_double);
                omega.image = sin(pi_2 * k / n_double);
                //printf("%d %lf %lf\n", k,  omega.real, omega.image);
                odd = omega * result[inx + symmetry_shift];
                //printf("%lf %lf  %lf %lf -> %lf %lf\n", omega.real, omega.image, result[inx + symmetry_shift].real, result[inx + symmetry_shift].image, odd.real, odd.image);
                result[inx + symmetry_shift] = result[inx] - odd;
                result[inx] = result[inx] + odd;
                //printf("%d %lf %lf\n%d %lf %lf\n", inx, result[inx].real, result[inx].image, inx + symmetry_shift, result[inx + symmetry_shift].real, result[inx + symmetry_shift].image);
            }
            //printf("\n");
        }
    }
}

void pecursive_inverse_fft(Complex * src, Complex * result, int n) {
    double pi_2 = M_PI * 2;
    double n_double = n;
    int layer_cnt = 0, layer;
    int group_cnt, group;
    int symmetry_shift;
    int cal_in_group;
    int reverse_inx, inx, k;
    Complex omega, odd;
    for(int i = n; i > 1; i = i >> 1, layer_cnt++);
    
    
    for(int inx = 0; inx < n; inx++) {
        reverse_inx = 0;
        for(int bit_num = 0; bit_num < layer_cnt; bit_num++) {
            reverse_inx = reverse_inx | ((inx & (1 << bit_num))?1: 0);
            reverse_inx = reverse_inx << 1;
        }
        result[reverse_inx >> 1] = src[inx];
    }

    for(layer = 0; layer < layer_cnt; layer++) {
        group_cnt = 1 << (layer_cnt - layer - 1);
        symmetry_shift = 1 << layer;
        for(group = 0; group < group_cnt; group++) {
            for(cal_in_group = 0; cal_in_group < symmetry_shift; cal_in_group++) {
                inx = 2 * group * symmetry_shift + cal_in_group;
                k = group_cnt * cal_in_group;
                omega.real = cos(pi_2 * k / n_double);
                omega.image = - sin(pi_2 * k / n_double);
                //printf("%d %lf %lf\n", k,  omega.real, omega.image);
                odd = omega * result[inx + symmetry_shift];
                result[inx + symmetry_shift] = result[inx] - odd;
                result[inx] = result[inx] + odd;
            }
            //printf("\n");
        }
    }
}
#include <bits/stdc++.h>

#ifdef __GNUC__
# define __rdtsc __builtin_ia32_rdtsc
#else
# include<intrin.h>
#endif
typedef unsigned long long u64;
using namespace std;


u64 hex_bin(const char*data)
{
	u64 b = 0;
	for (;;++data)
	{
		unsigned char d = *data - '0';
		if (d < 10)
			b = b << 4 | d;
		else
		{
			unsigned char u = (*data & 0xDF) - 'A';
			if (u > 5)
				break;
			b = b << 4 | u + 10;
		}
	}
	return b;
}
u64 permutation_fn(u64 in, int n_in, int n_out, int* array)
{
	u64 op = 0;
	for (int i = 0;i < n_out;++i)
	{
		op |= (in >> (n_in - array[n_out - 1 - i]) & 1) << i;
	}
	return op;
}
u64 sbox_permutation(u64 x)
{
	int s_box_[512]= {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
		0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
		4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
		15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
		15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
		3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
		0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
		13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
		10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
		13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
		13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
		1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
		7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
		13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
		2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
		14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
		4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
		11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
		12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
		10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
		9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
		4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
		4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
		13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
		1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
		6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
		13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
		1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
		7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
		2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};


	u64 op = 0;
	int box_1[64];
	int id;
	for (int i = 0;i < 8;++i)
	{
		for (int j = 0;j < 64;++j)
		{
			box_1[j] = s_box_[j + (i * 64)];
		}
		id = x >> (7 - i)*6 & 0x3F;
		id = id >> 1 & 15 | (id & 1) << 4 | id & 0x20;
		op |= box_1[id] << (7 - i) * 4;
	}
	return op;
}

u64 encrypt_decrypt(u64 text, u64* r_key)
{
	// Initial Permutation Table
	int initial_permutation[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7 };

	// Expansion Table
	int expansion[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
		6, 7, 8, 9, 8, 9, 10, 11,
		12, 13, 12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21, 20, 21,
		22, 23, 24, 25, 24, 25, 26, 27,
		28, 29, 28, 29, 30, 31, 32, 1 };

	// Permutation Table
	int perm[32] = { 16, 7, 20, 21,
		29, 12, 28, 17,
		1, 15, 23, 26,
		5, 18, 31, 10,
		2, 8, 24, 14,
		32, 27, 3, 9,
		19, 13, 30, 6,
		22, 11, 4, 25 };
	// Final Permutation Table
	int final_permutation[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25 };

	text = permutation_fn(text, 64, 64, initial_permutation);
	u64 text_right = text & 0x00000000FFFFFFFF;
	u64 text_left = (text >> 32) & 0x00000000FFFFFFFF;

	for (int i = 0; i < 16; i++) {
		u64 exp_text = permutation_fn(text_right,32,48, expansion);
		u64 xor_text = r_key[i] ^ exp_text;
		u64 sbox_op = sbox_permutation(xor_text);
		u64 per_text = permutation_fn(sbox_op, 32, 32, perm);
		u64 xor_result = text_left ^ per_text;
		text_left = xor_result;
		if (i < 15) { swap(text_left, text_right); }

	}
	u64 op = (text_right & 0x00000000FFFFFFFF) | ((text_left << 32) & 0xFFFFFFFF00000000);
	u64 final_op = permutation_fn(op, 64, 64, final_permutation);
	return final_op;
}



int main(int argc, char** argv)
{
	u64 key;
	u64 text;
	key = hex_bin(argv[3]);
	text = hex_bin(argv[2]);
	u64 encrypt_key[16];
	u64 decrypt_key[16];

	int Per_C_1[56] = { 57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4 };

	int Per_C_2[48] = { 14, 17, 11, 24, 1, 5,
		3, 28, 15, 6, 21, 10,
		23, 19, 12, 4, 26, 8,
		16, 7, 27, 20, 13, 2,
		41, 52, 31, 37, 47, 55,
		30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53,
		46, 42, 50, 36, 29, 32 };

	int shift_array[16] = { 1, 1, 2, 2,
		2, 2, 2, 2,
		1, 2, 2, 2,
		2, 2, 2, 1 };
	u64 p_key;
	u64 R_key;
	u64 total_key;
	p_key = permutation_fn(key, 64, 56, Per_C_1);
	
	u64 left_key = (p_key >> 28) & 0x0000000FFFFFFF;
	u64 right_key = p_key & 0x0000000FFFFFFF;

	for (int i = 0;i < 16;++i)
	{
		left_key=(left_key << shift_array[i]) | (left_key >> (28 - shift_array[i]));
		right_key = (right_key << shift_array[i]) | (right_key >> (28 - shift_array[i]));
		total_key = (right_key & 0x000000000FFFFFFF) | ((left_key<<28)& 0x00FFFFFFF0000000);
		R_key = permutation_fn(total_key, 56, 48, Per_C_2);
		encrypt_key[i] = R_key;
	}

	long long t1,t2;
	if (argc == 4)
	{
		if (strcmp("encrypt", argv[1]) == 0)
		{
			t1 = __rdtsc();
			u64 data = encrypt_decrypt(text, encrypt_key);
			t2 = __rdtsc();
			printf("cipher: %016llX\n", data);
		}
		else if (strcmp("decrypt", argv[1]) == 0)
		{
			for (int i = 0;i < 16;i++)
			{
				decrypt_key[i] = encrypt_key[15 - i];
			}
			t1 = __rdtsc();
			u64 data = encrypt_decrypt(text, decrypt_key);
			t2 = __rdtsc();
			printf("plain: %016llX\n", data);
		}
	}
	
	printf("Cycles: %lld\n", t2 - t1);


	return 0;
}
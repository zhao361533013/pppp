#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ELEM_SIZE  (256)
#define BUFF_SIZE  (2 * ELEM_SIZE - 1)

typedef struct _HTNode
{
	int 	weight;
	int 	parent;
	int 	LChild;
	int 	RChild;
}HTNode;

HTNode g_huffman_tree[BUFF_SIZE+1];
int g_weight[ELEM_SIZE+1];

char *g_huffman_code[ELEM_SIZE+1];

void compress(char *input_file, char *output_file);
void decompress(char *input_file, char *output_file);
void printUsage(char *str);
void makeHuffmanTree(HTNode *HuffmanTree, int tree_size, int *weight, int size);

void makeHuffmanCode(HTNode *HuffmanTree, int tree_size, int max_code_size);

void freeHuffmanCode(int code);

int StrToNum(char *str, int size);
int main(int c, char *v[])
{	
	int choice = 3;
	char path1[256], path2[256];
	do {
		printf("************************\n");
		printf("1.compress\n");
		printf("2.decompress\n");
		printf("3.exit\n");
		printf("************************\n");
		printf("please input choice£∫");
		scanf("%d", &choice);
		switch(choice){
		case 1:
			printf("input file name£∫");
			scanf("%s", path1);
			printf("output file name£∫");
			scanf("%s", path2);
			compress(path1, path2);
			break;
		case 2:
			printf("input file name£∫");
			scanf("%s", path1);
			printf("output file name£∫");
			scanf("%s", path2);
			decompress(path1, path2);
			break;
		case 3:
			return 0;
		default:
			break;
		}
	} while (1);
	return 0;
}
void compress(char *input_file, char *output_file)
{
	int 		i, ch;
	int 		input_file_size, output_file_size;
	FILE 		*fp_input, *fp_tmp, *fp_output;
	char 		tmp_file[PATH_MAX];
	char 		code_cover[9];
	unsigned int 	add_zero_num;

	memset(tmp_file, 0, (sizeof(char)*PATH_MAX));
	strcpy(tmp_file, input_file);
	strcat(tmp_file, ".tmp");
	
	
	if ((fp_input = fopen(input_file, "rb")) == NULL ) {
		fprintf(stderr, "Cannot open file %s !\n", input_file);
		exit(0);
	}
	
	while ((ch = fgetc(fp_input)) != EOF)
	{
		g_weight[ch+1]++;
	}

	input_file_size = ftell(fp_input);
	
	makeHuffmanTree(g_huffman_tree, BUFF_SIZE, g_weight, ELEM_SIZE);
	
	
	makeHuffmanCode(g_huffman_tree, ELEM_SIZE, 50);
 
	if ((fp_tmp = fopen(tmp_file, "wb+")) == NULL ) {
		fprintf(stderr, "Cannot open file %s !\n", tmp_file);
		exit(0);
	}

	fseek(fp_input, 0, SEEK_SET);
	while ((ch = fgetc(fp_input)) != EOF)
	{
		fprintf(fp_tmp, "%s", g_huffman_code[ch+1]);
	}

	fclose(fp_input);

	fseek(fp_tmp, 0, SEEK_SET);

	if ((fp_output = fopen(output_file, "wb")) == NULL ) {
		fprintf(stderr, "Cannot open file %s !\n", output_file);
		exit(0);
	}

	
	fwrite(&add_zero_num, sizeof(add_zero_num), 1, fp_output);

	
	fwrite(g_huffman_tree, sizeof(g_huffman_tree), 1, fp_output);

	code_cover[8] = '\0';
	while ((i = fread(code_cover, sizeof(char), 8, fp_tmp)) == 8)
	{
		code_cover[8] = '\0';
		ch = StrToNum(code_cover, 8);
		fputc(ch, fp_output);
	}
	if ( i > 0)
	{
		add_zero_num = i;
		while (i != 8)
		{
			code_cover[i++] = '0';
		}
		code_cover[8] = '\0';
		ch = StrToNum(code_cover, i);
		fputc(ch, fp_output);
	}

	output_file_size = ftell(fp_output);

	
	fseek(fp_output, 0, SEEK_SET);
	fwrite(&add_zero_num, sizeof(add_zero_num), 1, fp_output);
	
	fclose(fp_output);

	printf("compressed file %s done \n", output_file);


	fclose(fp_tmp);
	remove(tmp_file);
	
	freeHuffmanCode(ELEM_SIZE);
}

void NumToStr(int num, char *str);
void decompress(char *input_file, char *output_file)
{
	int 		i, ch, old_ch, tag = 0, huffman_root;
	FILE 		*fp_input, *fp_tmp, *fp_output;
	char 		tmp_file[PATH_MAX];
	char 		code_str[9];
	unsigned int 	add_zero_num;

	memset(tmp_file, 0, (sizeof(char)*PATH_MAX));
	strcpy(tmp_file, input_file);
	strcat(tmp_file, ".tmp");
	
	if ((fp_input = fopen(input_file, "rb")) == NULL ) {
		fprintf(stderr, "Cannot open file %s !\n", input_file);
		exit(0);
	}

	
	fread(&add_zero_num, sizeof(add_zero_num), 1, fp_input);

	
	fread(g_huffman_tree, sizeof(g_huffman_tree), 1, fp_input);

	for (i = 1; i < BUFF_SIZE + 1; i++)
	{
		if (g_huffman_tree[i].parent == 0 && g_huffman_tree[i].weight != 0)
		{
			huffman_root = i;
		}
	}

	if ((fp_tmp = fopen(tmp_file, "wb+")) == NULL ) {
		fprintf(stderr, "Cannot open file %s !\n", tmp_file);
		exit(0);
	}

	old_ch = fgetc(fp_input);
	while ((ch = fgetc(fp_input)) != EOF)
	{
		NumToStr(old_ch, code_str);
		code_str[8] = '\0';
		fprintf(fp_tmp, "%s", code_str);
		old_ch = ch;
	}
	
	NumToStr(old_ch, code_str);
	code_str[add_zero_num] = '\0';
	fprintf(fp_tmp, "%s", code_str);

	fclose(fp_input);

	if ((fp_output = fopen(output_file, "wb")) == NULL ) {
		fprintf(stderr, "Cannot open file %s !\n", output_file);
		exit(0);
	}
	
	fseek(fp_tmp, 0, SEEK_SET);
	
	while (1)
	{
		i = huffman_root;
		while (g_huffman_tree[i].LChild != 0 && (ch = fgetc(fp_tmp)) != EOF)
		{
			tag++;
			if (ch == '1')
			{
				i = g_huffman_tree[i].RChild;
			}
			else if (ch == '0')
			{
				i = g_huffman_tree[i].LChild;
			}
			else
			{
				fprintf(stderr, "failed£°\n");
				exit(0);
			}
		}
		if (ch == EOF)
			break;
		fputc(i-1, fp_output);
	}

	fclose(fp_output);

	printf("decompressed file %s done\n", output_file);

	fclose(fp_tmp);
	remove(tmp_file);
}

void getMinWeightNode(HTNode *HuffmanTree, int size, int *node1, int *node2);
void makeHuffmanTree(HTNode *HuffmanTree, int tree_size, int *weight, int size)
{
	int i, elem_size = 0, node1 = 1, node2 = 2;

	for (i = 1; i < size + 1; i++)
	{
		HuffmanTree[i].weight = weight[i];
		if(weight[i] != 0)
		{
			elem_size++;
		}
	}

	for (i = size + 1; i < size + elem_size; i++)
	{
		getMinWeightNode(HuffmanTree, i-1, &node1, &node2);
		HuffmanTree[i].weight = HuffmanTree[node1].weight + HuffmanTree[node2].weight;
		HuffmanTree[node1].parent = i;
		HuffmanTree[node2].parent = i;
		HuffmanTree[i].LChild = node1;
		HuffmanTree[i].RChild = node2;
	}
}
void getMinWeightNode(HTNode *HuffmanTree, int size, int *node1, int *node2)
{
	int i;
	int weight1 = INT_MAX, weight2 = INT_MAX;
	
	for(i = 1; i < size + 1; i++)
	{
		if (HuffmanTree[i].weight != 0 && HuffmanTree[i].weight < weight2 && HuffmanTree[i].parent == 0 )
		{
			if (HuffmanTree[i].weight < weight1)
			{
				*node2 = *node1;
				*node1 = i;
				weight2 = weight1;
				weight1 = HuffmanTree[i].weight;
			}
			else
			{
				*node2 = i;
				weight2 = HuffmanTree[i].weight;
			}
		}
	}
}

void makeHuffmanCode(HTNode *HuffmanTree, int elem_size, int max_code_size)
{
	char  	*strtmp;
	int 	i, p_tag, start, code_tmp;

	strtmp = (char *)malloc(max_code_size*sizeof(char));
	strtmp[max_code_size-1] = '\0';

	for (i = 1; i < elem_size + 1; i++)
	{
		start = max_code_size - 1;
		code_tmp = i;
		p_tag = HuffmanTree[i].parent;
		while (p_tag != 0)
		{
			start--;
			if (code_tmp == HuffmanTree[p_tag].LChild)
			{
				strtmp[start] = '0';
			}
			else
			{
				strtmp[start] = '1';
			}
			code_tmp = p_tag;
			p_tag = HuffmanTree[p_tag].parent;
		}
		g_huffman_code[i] = (char *)malloc((max_code_size-start)*sizeof(char));
		strcpy(g_huffman_code[i], strtmp + start);
	}
	free(strtmp);	
}

void freeHuffmanCode(int size)
{
	int i;
	
	for (i = 1; i < size + 1; i++)
	{
		if (g_huffman_code[i] != NULL)
		{
			free(g_huffman_code[i]);
		}
	}
}

int StrToNum(char *str, int size)
{
	int sum = 0, i;

	for (i = 0; i < size; i++)
	{
		sum = sum * 2 + (*(char *)str - '0');
		str++;
	}

	return sum;
}

void NumToStr(int num, char *str)
{ 
	int i = 7, tmp;

	memset(str, '0', 8);
	for (tmp = num; tmp != 0; tmp /= 2) 
	{ 
		str[i--]= tmp % 2 + '0';
	}
}

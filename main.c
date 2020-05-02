#include <stdio.h>
int obeb(int, int);

int main()
{
	char message[100], output[100], m_sel, l_cont = 'y';
	int n_mes[100], n_out[100], key[2], i, mes_size;
	while (l_cont == 'y')
	{
		mod_sel:
		printf("Select a mode:\n1-Encryption(e)\n2-Decryption(d)\n");
		scanf("%c", &m_sel);
		if(m_sel == '\n')
			scanf("%c", &m_sel);
		switch (m_sel)
		{
		case('e'):
		mes_check:
			printf("Message(with big letters):");
			scanf("%s", message);
			if(message == '\n')
				scanf("%s", message);

			for (mes_size = 0; message[mes_size] != '\0'; mes_size++)
				*(n_mes + mes_size) = *(message + mes_size) - 64;

			for ( i = 0;  i < mes_size;  i++)
			{
				if (n_mes[i] < 1 || n_mes[i] > 26)
				{
					printf("Enter a valid message!\n");
					goto mes_check;
				}
			}
			
			for (i = 0; i < sizeof(key)/sizeof(int); i++)
			{
				printf("Key %d(Pick a number between 0-25):", i+1);
				scanf("%d", &key[i]);
				if (key[i] >= 26 && key[i] < 0)
				{
					printf("Enter a valid key!\n");
					i--;
					continue;
				}
				if (obeb(key[0], 26))
				{
					printf("obeb(key[0], 26) should be equal to 1!\n");
					i--;
					continue;
				}
			}

			for ( i = 0; i < mes_size; i++)
				n_out[i] = key[0] * n_mes[i] + key[1] + 64;

			for ( i = 0; i < mes_size; i++)
				*(output + i) = *(n_out + i);

			output[i] = '\0';
			printf("Your output is %s\n", output);
			break;
		case('d'):
			printf("Message:");
			scanf("%s", message);
			if (message == '\n')
				scanf("%s", message);
			for (i = 0; i < sizeof(key) / sizeof(int); i++)
			{
				printf("Key %d(Pick a number between 0-25):", i + 1);
				scanf("%d", &key[i]);
				if (key[i] >= 26 && key[i] < 0)
				{
					printf("Enter a valid key!\n");
					i--;
					continue;
				}
				if (obeb(key[0], 26))
				{
					printf("obeb(key[0], 26) should be equal to 1!\n");
					i--;
					continue;
				}
			}

			for (mes_size = 0; message[mes_size] != '\0'; mes_size++)
				*(n_mes + mes_size) = *(message + mes_size) - 64;

			for (i = 0; i < mes_size; i++)
				n_out[i] = (n_mes[i] - key[1]) / key[0] + 64;

			for (i = 0; i < mes_size; i++)
				*(output + i) = *(n_out + i);

			output[i] = '\0';
			printf("Your output is %s\n", output);
			break;
		default:
			printf("Enter a valid mode!\n");
			goto mod_sel;
			break;
		}
		printf("Continue?(y/n):");
		scanf("%c", &l_cont);
		if(l_cont == '\n')
			scanf("%c", &l_cont);
	}
}

int obeb(int num1, int num2)
{
	int counter = 2, div1, div2, rem1, rem2, sum1 = 1, sum2 = 1;
start:
	div1 = num1 / counter;
	div2 = num2 / counter;
	rem1 = num1 % counter;
	rem2 = num2 % counter;
	if (num1 > 1 && num2 > 1)
	{
		if (rem1 == 0 && rem2 == 0)
		{
			sum1 = sum1 * counter;
			sum2 = sum2 * counter;
			num1 = div1;
			num2 = div2;
		}
		else
		{
			if (rem1 == 0)
			{
				sum2 = sum2 * counter;
				num1 = div1;
			}
			else if (rem2 == 0)
			{
				sum2 = sum2 * counter;
				num2 = div2;
			}
			else
			{
				counter++;
				goto start;
			}

		}
		goto start;
	}
	else if (num1 > 1)
	{
		if (rem1 == 0)
		{
			sum2 = sum2 * counter;
			num1 = div1;
		}
		else
		{
			counter++;
			goto start;
		}
		goto start;
	}
	else if (num2 > 1)
	{
		if (rem2 == 0)
		{
			sum2 = sum2 * counter;
			num2 = div2;
		}
		else
		{
			counter++;
			goto start;
		}
		goto start;
	}
	else
	{
		if (sum1 != 1)
			return 1;
		else
			return 0;
	}
}
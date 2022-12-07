#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#define BHCYN "\e[1;96m"
#define BHMAG "\e[1;95m"
#define BHRED "\e[1;91m"
#define reset "\e[0m"

int	main(void)
{
	int		fd_1;
	char	*line;
	unsigned long total_count;
	unsigned long tmp;
	unsigned long count;
	int read_flag = 0;
	int dir_flag = 0;
	int end_flag = 0;
	
	total_count = 0;
	tmp = 0;
	count = 0;
	fd_1 = open("input.txt", O_RDONLY);

	while (line = get_next_line(fd_1))
	{	
		if (line[0] == '$' && line[2] == 'l')
		{
			read_flag = 1;
			end_flag= 1;
		}
		if (read_flag)
		{
			count += (unsigned long)atoi(line);
			if (count > 100000)
			{
				count = 0;
				tmp = 0;
				read_flag = 0;
			}
			else if ((count + tmp) > 100000)
			{
				count -= tmp;
			}
		}
		if (line[0] == 'd')
			dir_flag = 1;
		if (line[0] == '$' && line[2] == 'c' && end_flag)
		{
			printf("%lu\n", count);
			if ((count + tmp) <= 100000 && dir_flag)
				tmp += count;

			if (!dir_flag)
			{
				count += tmp * 2;
				total_count += count;
			}
			dir_flag = 0;
			end_flag = 0;
			count = 0;
		}
	}
	//printf("%lu", tmp);
	printf("%lu", total_count);
}